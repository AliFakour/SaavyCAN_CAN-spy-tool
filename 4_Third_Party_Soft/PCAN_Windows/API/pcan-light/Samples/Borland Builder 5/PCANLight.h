///////////////////////////////////////////////////////////////////////////////
//  Based on:
//  PCAN_ISA.h
//  PCAN_2ISA.h
//  PCAN_PCI.h
//  PCAN_2PCI.h
//  PCAN_PCC.h
//  PCAN_2PCC.h
//  PCAN_DNG.h
//  PCAN_DNP.h
//  PCAN_USB.h
//  PCAN_2USB.h
//
//  Version 2.0
//
//  ~~~~~~~~~~~~
//
//  Idea:
//
//  ~~~~~~~~~~
//
//  PCANLight is a Unit in charge of make the managing of the different PCAN Hardware using the 
//  PCANLight Dlls: pcan_isa,pcan_2isa,pcan_pci,pcan_2pci,pcan_pcc,pcan_2pcc,pcan_dng,pcan_dnp,
//  pcan_usb, pcan_2usb
//
//  In order  to offer  a simple  interface, some constant valuest were converted  to enumerate 
//  types.  The class CANLight  make use of all Dlls and gives  an unique interface for all the 
//  hardware types.  In this way, in this high level,  will  exists  only  one  occurrence of each 
//  PCANLIGHT function.
//
//  ~~~~~~~~~~~~
//
//  PCAN-Light -API
//
//  ~~~~~~~~~~~~
//
//   Init() (Two versions, for P&P and Non P&P)
//   Close()
//   Status()
//   Write()
//   Read()
//   ReadEx()
//   VersionInfo()
//   DllVersionInfo()
//   ResetClient()
//   MsgFilter()
//   ResetFilter()
//   SetUSBDeviceNr()
//   GetUSBDeviceNr()
//   SetRcvEvent()
//
//  ------------------------------------------------------------------
//
//  Autor  : Keneth Wagner
//  Language: C++ (Borland C++ Builder 5)
//  Last Modified: Wagner - 22.09.2009
//
//  ------------------------------------------------------------------
//  Copyright (C) 2006-2009  PEAK-System Technik GmbH, Darmstadt
//
#ifndef PCANLightH
#define PCANLightH

#pragma region Type definitions
// Kind of Frame - Message Type
//
enum FramesType
{
    INIT_TYPE_ST	= 0x00,	//Standart Frame
    INIT_TYPE_EX	= 0x01,	//Extended Frame
};

// Maximal values for the ID of a CAN Message
//
enum MaxIDValues
{
    MAX_STANDARD_ID	= 0x7FF,
    MAX_EXTENDED_ID	= 0x1FFFFFFF,
};

// Kind of CAN Message
//
enum MsgTypes
{
    MSGTYPE_STANDARD	= 0x00,		// Standard Frame (11 bit ID)
    MSGTYPE_RTR			= 0x01,		// Remote request
    MSGTYPE_EXTENDED	= 0x02,		// CAN 2.0 B Frame (29 Bit ID)
    MSGTYPE_STATUS		= 0x80,		// Status Message
};

// PCAN Hardware enumeration
//
enum Hardware
{
    HW_INTERN          = 0,
    HW_ISA             = 1,
    HW_DONGLE	       = 2,	
    HW_DONGLE_EPP	   = 3,	
    HW_PHYT_ISA        = 4,
    HW_DONGLE_SJA      = 5,
    HW_DONGLE_SJA_EPP  = 6,
    HW_DONGLE_PRO      = 7,
    HW_DONGLE_PRO_EPP  = 8,
    HW_ISA_SJA         = 9,
};

// Hardware type corresponding to the different PCAN Light Dlls
//
enum HardwareType
{
    ISA_1CH	= 0,		// ISA 1 Channel
	ISA_2CH = 1,		// ISA 2 Channels
	PCI_1CH = 2,		// PCI 1 Channel
	PCI_2CH = 3,		// PCI 2 Channels
	PCC_1CH = 4,		// PCC 1 Channel
	PCC_2CH = 5,		// PCC 2 Channels
	USB_1CH	= 6,		// USB 1st Channel
	USB_2CH = 7,		// USB 2nd Channel		
	DNP		= 8,		// DONGLE PRO
	DNG		= 9,		// DONGLE
};

// CAN Baudrates
//
enum Baudrates
{
    BAUD_1M		= 0x0014,  //   1 MBit/s
    BAUD_500K	= 0x001C,  // 500 kBit/s
    BAUD_250K	= 0x011C,  // 250 kBit/s
    BAUD_125K	= 0x031C,  // 125 kBit/s
    BAUD_100K	= 0x432F,  // 100 kBit/s
    BAUD_50K	= 0x472F,  //  50 kBit/s
    BAUD_20K	= 0x532F,  //  20 kBit/s
    BAUD_10K	= 0x672F,  //  10 kBit/s
    BAUD_5K		= 0x7F7F,  //   5 kBit/s
};

// CAN Error and status values
//
enum CANResult
{
    ERR_OK				= 0x0000,	// No error
    ERR_XMTFULL			= 0x0001,   // Send buffer of the Controller ist full
    ERR_OVERRUN			= 0x0002,   // CAN-Controller was read to late
    ERR_BUSLIGHT		= 0x0004,   // Bus error: an Error count reached the limit
    ERR_BUSHEAVY		= 0x0008,   // Bus error: an Error count reached the limit
    ERR_BUSOFF			= 0x0010,   // Bus error: CAN_Controller went to 'Bus-Off'
    ERR_QRCVEMPTY		= 0x0020,   // RcvQueue is empty
    ERR_QOVERRUN		= 0x0040,   // RcvQueue was read to late
    ERR_QXMTFULL		= 0x0080,   // Send queue is full
    ERR_REGTEST			= 0x0100,   // RegisterTest of the 82C200/SJA1000 failed
    ERR_NOVXD			= 0x0200,   // Problem with Localization of the VxD    
    ERR_ILLHW			= 0x1400,   // Invalid Hardware handle
    ERR_RESOURCE		= 0x2000,   // Not generatably Resource (FIFO, Client, Timeout)
    ERR_PARMTYP			= 0x4000,   // Parameter not permitted
    ERR_PARMVAL			= 0x8000,   // Invalid Parameter value
	ERRMASK_ILLHANDLE	= 0x1C00,   // Mask for all Handle errors
    ERR_ANYBUSERR		= ERR_BUSLIGHT | ERR_BUSHEAVY | ERR_BUSOFF, // All others error status <> 0 please ask by PEAK ......intern Driver errors.....
    ERR_NO_DLL			= 0xFFFFFFFF// A Dll could not be loaded or a function was not found into the Dll
};

// A CAN Message
//
typedef struct {
    DWORD ID;        // 11/29 Bit-ID
    BYTE  MSGTYPE;   // Kind of Message
    BYTE  LEN;       // Number of Data bytes (0..8)
    BYTE  DATA[8];   // Data bytes 0..7
} TPCANMsg;

// A TPCANTimestamp structure 
//
typedef struct {
	unsigned int millis;			// Base-value: milliseconds: 0.. 2^32-1
	unsigned short millis_overflow; // Roll-arounds of millis
	unsigned short micros;          // Microseconds: 0..999
} TPCANTimestamp;

// Function pointers to load PCANLight functions
//
typedef DWORD (__stdcall *InitPAP)(WORD, int);											// Init Plug And Play
typedef DWORD (__stdcall *InitNPAP)(WORD, int, int, DWORD, WORD);						// Init Non Plug And Play
typedef DWORD (__stdcall *C_S_RC_RF)();                                                 // Close,Status,ResetClient,ResetFilter
typedef DWORD (__stdcall *ReadWrite)(TPCANMsg*);                                        // CAN_Read CAN_Write
typedef DWORD (__stdcall *ReadExtra)(TPCANMsg*, TPCANTimestamp*);                       // CAN_ReadEx
typedef DWORD (__stdcall *USBSDevNr)(unsigned int);			                                    // SetUSBDeviceNumber
typedef DWORD (__stdcall *USBGDevNr)(unsigned int*);				                                // GetUSBDeviceNumber
typedef DWORD (__stdcall *MessageFilter)(DWORD, DWORD, int);							// SetMsgFilter
typedef DWORD (__stdcall *GetInfo)(char*);                                              // DllVersionInfo, VersionInfo
typedef DWORD (__stdcall *ReceiveEvent)(HANDLE);									    // SetRcvEvent
//---------------------------------------------------------------------------
#pragma endregion

#pragma region Classes definition
class PCANLight
{
    private:
		HINSTANCE hCANLightDll;
		HardwareType hwType;
		bool bWasLoaded;

        InitPAP pInitPaP;
        InitNPAP pInitNPaP;
        C_S_RC_RF pClose;
        C_S_RC_RF pStatus;
        ReadWrite pWrite;
        ReadWrite pRead;
		ReadExtra pReadEx;
        GetInfo pVersionInfo;
		GetInfo pDllVersionInfo;
        C_S_RC_RF pResetClient;
        MessageFilter pMsgFilter;
        C_S_RC_RF pResetFilter;
        USBSDevNr pSetUSBDeviceNr;
        USBGDevNr pGetUSBDeviceNr;
		ReceiveEvent pSetRcvEvent;

		void InitializePointers();
        bool LoadDllHandle();
		FARPROC GetFunction(LPSTR szName);

		void LoadAPI();
		void UnloadAPI();
		bool FreeCANLightAPI();

    public:
		PCANLight();
		PCANLight(HardwareType HWType);
		~PCANLight();
		bool InitializeAPI(HardwareType HWType);

        CANResult Init(Baudrates BTR0BTR1, FramesType MsgType);
        CANResult Init(Baudrates BTR0BTR1, FramesType MsgType, DWORD IO_Port, WORD Interupt);
        CANResult Close();
        CANResult Status();
        CANResult Write(TPCANMsg *MsgToSend);
        CANResult Read(TPCANMsg *MsgToSend);
		CANResult ReadEx(TPCANMsg *MsgToSend, TPCANTimestamp *RcvTime);
        CANResult VersionInfo(char* strInfo);
		CANResult DllVersionInfo(char* strInfo);
        CANResult ResetClient();
        CANResult MsgFilter(DWORD From, DWORD To, MsgTypes MsgTypes);
        CANResult ResetFilter();
        CANResult SetUSBDeviceNr(unsigned int DeviceNumber);
        CANResult GetUSBDeviceNr(unsigned int *DeviceNumber);
		CANResult SetRcvEvent(HANDLE hEvent);
};
#pragma endregion
#endif


