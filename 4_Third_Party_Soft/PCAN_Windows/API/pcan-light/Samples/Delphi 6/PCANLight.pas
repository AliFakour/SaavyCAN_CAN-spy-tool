///////////////////////////////////////////////////////////////////////////////
//  Based on:
//  PCAN_ISA.pas
//  PCAN_2ISA.pas
//  PCAN_PCI.pas
//  PCAN_2PCI.pas
//  PCAN_PCC.pas
//  PCAN_2PCC.pas
//  PCAN_DNG.pas
//  PCAN_DNP.pas
//  PCAN_USB.pas
//  PCAN_2USB.pas
//
//  Version 2.0
//
//  ~~~~~~~~~~~~
//
//  Idea:
//
//  ~~~~~~~~~~
//
//  PCANLight is a namespace used to make the managing of the different PCAN Hardware using the 
//  PCANLight Dlls: pcan_isa,pcan_2isa,pcan_pci,pcan_2pci,pcan_pcc,pcan_2pcc,pcan_dng,pcan_dnp,
//  pcan_usb, pcan_2usb
//
//  In order  to offer  a simple  interface, some constant valuest were converted  to enumerate 
//  types.  The class CANLight  make use of all Dlls and gives  an unique interface for all the 
//  hardware types.  A TCLightMsg class is implemented too.  This class will  be used to make a 
//  bridge between the definition of the TCANMsg structure in every *.cs file.  In this way, in 
//  this high level,  will  exists  only  one  kind of CAN  message and  one occurrence of each 
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
//   DLLVersionInfo()
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
//  Language: Pascal OO (Delphi)
//  Modified: Wagner - 24.09.2009
//
//  ------------------------------------------------------------------
//  Copyright (C) 2006-2009  PEAK-System Technik GmbH, Darmstadt
//
unit PCANLight;

interface

uses
    SysUtils, Dialogs, WinTypes, WinProcs, Math;

Type
    
// Kind of Frame - Message Type
//
FramesType = (
    INIT_TYPE_ST	= $00,	//Standart Frame
    INIT_TYPE_EX	= $01	//Extended Frame
);

// Maximal values for the ID of a CAN Message
//
MaxIDValues = (
    MAX_STANDARD_ID	= $7FF,
    MAX_EXTENDED_ID	= $1FFFFFFF
);

// Kind of CAN Message
//
MsgTypes = (
    MSGTYPE_STANDARD	= $00,		// Standard Frame (11 bit ID)
    MSGTYPE_RTR			= $01,		// Remote request
    MSGTYPE_EXTENDED	= $02,		// CAN 2.0 B Frame (29 Bit ID)
    MSGTYPE_STATUS		= $80		// Status Message
);

// PCAN Hardware enumeration
//
Hardware =
(
    HW_INTERN          = 0,
    HW_ISA             = 1,
    HW_DONGLE	       = 2,	//82C200 version
    HW_DONGLE_EPP	   = 3,	//82C200 version
    HW_PHYT_ISA        = 4,
    HW_DONGLE_SJA      = 5,
    HW_DONGLE_SJA_EPP  = 6,
    HW_DONGLE_PRO      = 7,
    HW_DONGLE_PRO_EPP  = 8,
    HW_ISA_SJA         = 9
);

// Hardware type corresponding to the different PCAN Light Dlls
//
HardwareType = (
    ISA_1CH	= 0,		// ISA 1 Channel
	ISA_2CH = 1,		// ISA 2 Channels
	PCI_1CH = 2,		// PCI 1 Channel
	PCI_2CH = 3,		// PCI 2 Channels
	PCC_1CH = 4,		// PCC 1 Channel
	PCC_2CH = 5,		// PCC 2 Channels
	USB_1CH	= 6,		// USB 1st Channel
    USB_2CH = 7,        // USB 2nd Channel
	DNP		= 8,		// DONGLE PRO
	DNG		= 9		// DONGLE
);

// CAN Baudrates
//
Baudrates = (
    BAUD_1M		= $0014,  //   1 MBit/s
    BAUD_500K	= $001C,  // 500 kBit/s
    BAUD_250K	= $011C,  // 250 kBit/s
    BAUD_125K	= $031C,  // 125 kBit/s
    BAUD_100K	= $432F,  // 100 kBit/s
    BAUD_50K	= $472F,  //  50 kBit/s
    BAUD_20K	= $532F,  //  20 kBit/s
    BAUD_10K	= $672F,  //  10 kBit/s
    BAUD_5K		= $7F7F  //   5 kBit/s
);

// CAN Error and status values
//
CANResult = (
    ERR_OK				= $0000,   // No error
    ERR_XMTFULL			= $0001,   // Send buffer of the Controller ist full
    ERR_OVERRUN			= $0002,   // CAN-Controller was read to late
    ERR_BUSLIGHT		= $0004,   // Bus error: an Error count reached the limit
    ERR_BUSHEAVY		= $0008,   // Bus error: an Error count reached the limit
    ERR_BUSOFF			= $0010,   // Bus error: CAN_Controller went to 'Bus-Off'
    ERR_QRCVEMPTY		= $0020,   // RcvQueue is empty
    ERR_QOVERRUN		= $0040,   // RcvQueue was read to late
    ERR_QXMTFULL		= $0080,   // Send queue is full
    ERR_REGTEST			= $0100,   // RegisterTest of the 82C200/SJA1000 failed
    ERR_NOVXD			= $0200,   // Problem with Localization of the VxD
    ERR_ILLHW			= $1400,   // Invalid Hardware handle
    ERR_RESOURCE		= $2000,   // Not generatably Resource (FIFO, Client, Timeout)
    ERR_PARMTYP			= $4000,   // Parameter not permitted
    ERR_PARMVAL			= $8000,   // Invalid Parameter value
    ERRMASK_ILLHANDLE	= $1C00,   // Mask for all Handle errors    
    ERR_ANYBUSERR		= LongWord(ERR_BUSLIGHT) OR LongWord(ERR_BUSHEAVY) OR LongWord(ERR_BUSOFF), // All others error status <> 0 please ask by PEAK ......intern Driver errors.....
    ERR_NO_DLL			= $7FFFFFFF// A Dll could not be loaded or a function was not found into the Dll
);

// A CAN Message
//
TPCANMsg = record
    ID: LongWord;       // 11/29 Bit-Kennung
    MSGTYPE: Byte;      // Bits aus MSGTYPE_*
    LEN: Byte;          // Anzahl der gueltigen Daten-Bytes (1..8)
    DATA: array[0..7] of Byte;    // Daten-Bytes 0..7
end;

// Timestamp of a receive/transmit event
// Total microseconds = micros + 1000 * millis + 0xFFFFFFFF * 1000 * millis_overflow
//    
TPCANTimestamp = record
    millis: LongWord;           // Base-value: milliseconds: 0.. 2^32-1
    millis_overflow: Word;      // Roll-arounds of millis
    micros: Word;               // Microseconds: 0..999
end; 

// Function pointers to load PCANLight functions
//
InitPAP = function (BR: Word; FT: Integer): LongWord; stdcall;                            // init Plug And Play
InitNPAP = function (BR: Word; FT: Integer;
                     HW: Integer; IOP: LongWord; Itr: Word): LongWord; stdcall;           // init Non Plug And Play
C_S_RC_RF = function (): LongWord; stdcall;                                               // Close,Status,ResetClient,ResetFilter
ReadWrite = function (var Msg: TPCANMsg): LongWord; stdcall;                              // CAN_Read CAN_Write
ReadExtra = function (var Msg: TPCANMsg; var RcvTime: TPCANTimestamp): LongWord; stdcall; // CAN_ReadEx
USBSDevNr = function (DN: LongWord): LongWord; stdcall;                                   // SetUSBDeviceNumber
USBGDevNr = function (var DN: LongWord): LongWord; stdcall;                               // GetUSBDeviceNumber
MessageFilter = function (FI, TI : LongWord; TY: Integer): LongWord; stdcall;             // Set MsgFilter
GetInfo = function (lpszTextBuff: PChar) : LongWord; stdcall;                             // DllGetVersion, VersionInfo
ReceiveEvent = function (hEvent: THandle): LongWord; stdcall;                             // SetRcvEvent
//---------------------------------------------------------------------------

PPCANLight = Class
    private
        hCANLightDll: THandle;
        currHwType: HardwareType;
        bWasLoaded: Boolean;

        pInitPap: InitPAP;
        pInitNPaP: InitNPAP;
        pClose: C_S_RC_RF;
        pStatus: C_S_RC_RF;
        pWrite: ReadWrite;
        pRead: ReadWrite;
		pReadEx: ReadExtra;
        pVersionInfo: GetInfo;
		pDllVersionInfo: GetInfo;
        pResetClient: C_S_RC_RF;
        pMsgFilter: MessageFilter;
        pResetFilter: C_S_RC_RF;
        pSetUSBDeviceNr: USBSDevNr;
        pGetUSBDeviceNr: USBGDevNr;		
		pSetRcvEvent: ReceiveEvent;

        procedure InitializePointers();
        function LoadDllHandle(): Boolean;
        function GetFunction(strName: string): Pointer;
        
        procedure LoadAPI();
        procedure UnloadAPI();
        function FreeCANLightAPI(): Boolean; 

    public
        constructor Create(); overload;
        constructor Create(HWType: HardwareType); overload;   
        destructor Destroy(); override;
        function InitializeAPI(HWType: HardwareType): Boolean;
        
        function Init(BTR0BTR1: Baudrates; MsgType: FramesType) : CANResult; Overload;
        function Init(BTR0BTR1: Baudrates; MsgType: FramesType; IO_Port: LongWord; Interrupt: Word) : CANResult; Overload;
        function Close(): CANResult;
        function Status(): CANResult;
        function Write(var MsgToSend: TPCANMsg): CANResult;
        function Read(var MsgBuffer: TPCANMsg) : CANResult;
        function ReadEx(var MsgBuffer: TPCANMsg; var RcvTime: TPCANTimestamp) : CANResult;
        function VersionInfo(var strInfo: string): CANResult;
        function DllVersionInfo(var strInfo: string): CANResult;
        function ResetClient(): CANResult;
        function MsgFilter(FromId, ToId: LongWord; MsgType: MsgTypes): CANResult;
        function ResetFilter(): CANResult;
        function SetUSBDeviceNr(DeviceNumber: LongWord): CANResult;
        function GetUSBDeviceNr(var DeviceNumber: LongWord): CANResult;
        function SetRcvEvent(hEvent: THandle): CANResult;        
end;

implementation

{ PPCANLight }

// PCANLight Constructor
//
constructor PPCANLight.Create(); 
begin
	bWasLoaded:= false;
	hCANLightDll:= 0;
end;

// PCANLight Constructor with initialization
// "HWType" = Hardware to be used
//
constructor PPCANLight.Create(HWType: HardwareType); 
begin
	bWasLoaded:= false;
	hCANLightDll:= 0;

    InitializeAPI(HWType);
end;

// PCANLight Destructor
//
destructor PPCANLight.Destroy();
begin
    UnloadAPI();
end;

// Initializes the PCANLight for a specific hardware
// "HWType" = Hardware to be used
//
function PPCANLight.InitializeAPI(HWType: HardwareType): Boolean;
begin
	// Unloads the current DLL
	//
    UnloadAPI();
	// Sets the new Hardware
	//    
    currHwType:= HWType;
	// Loads the API for the new Hardware
	//    
    LoadAPI();

    Result:= bWasLoaded;
end;

// Initializes the pointers for the PCANLight functions
//
procedure PPCANLight.InitializePointers();
begin
	pInitPaP:= nil;
	pInitNPaP:= nil;
	pClose:= nil;
	pStatus:= nil;
	pWrite:= nil;
	pRead:= nil;
	pReadEx:= nil;
	pVersionInfo:= nil;
	pDllVersionInfo:= nil;
	pResetClient:= nil;
	pMsgFilter:= nil;
	pResetFilter:= nil;
	pSetUSBDeviceNr:= nil;
	pGetUSBDeviceNr:= nil;
	pSetRcvEvent:= nil;
end;

// Loads the DLL for the configured hardware
//
function PPCANLight.LoadDllHandle(): Boolean;
begin
	// It will be loaded
	//
    if Not bWasLoaded then
    begin 
        Case currHwType Of
            ISA_1CH:
               hCANLightDll:= LoadLibrary('PCAN_ISA');           
            ISA_2CH:
                hCANLightDll:= LoadLibrary('PCAN_2ISA');
            PCI_1CH:
                hCANLightDll:= LoadLibrary('PCAN_PCI');
            PCI_2CH:
                hCANLightDll:= LoadLibrary('PCAN_2PCI');
            PCC_1CH:
                hCANLightDll:= LoadLibrary('PCAN_PCC');
            PCC_2CH:
                hCANLightDll:= LoadLibrary('PCAN_2PCC');
            USB_1CH:
                hCANLightDll:= LoadLibrary('PCAN_USB');
            USB_2CH:
                hCANLightDll:= LoadLibrary('PCAN_2USB');
            DNP:
                hCANLightDll:= LoadLibrary('PCAN_DNP');
            DNG:
                hCANLightDll:= LoadLibrary('PCAN_DNG');
        // Hardware is not valid for this function
        //
        else
            hCANLightDll:= 0;
        end;            
   end;

     // Return if the DLL was loaded or not
	//
    Result:= (hCANLightDll <> 0);
end;

// Gets the address of a given function name in a loaded DLL
//
function PPCANLight.GetFunction(strName: string): Pointer;
begin
	// There is no DLL loaded
	//
	if (hCANLightDll = 0) then
		Result:= nil
    else
    	// Gets the address of the given function in the loeaded DLL
    	//
	    Result:= GetProcAddress(hCANLightDll, PChar(strName));
end;
        
 // Instanciates/loads all functions within a loaded DLL
//
procedure PPCANLight.LoadAPI();
begin
	// Initializes pointers
	//
	InitializePointers();
	// Loads the DLL
	//
	if(not LoadDllHandle()) then
		exit;

    Case currHwType Of
		// No PlugAndPlay - Channel One
		//    
        ISA_1CH, DNP, DNG:
        begin
            pInitNPaP:= GetFunction('CAN_Init');
            bWasLoaded:= Assigned(pInitNPaP);
        end;
		// No PlugAndPlay - Channel Two
		//
        ISA_2CH:
        begin
			pInitNPaP:= GetFunction('CAN2_Init');
			bWasLoaded:= Assigned(pInitNPaP);
        end;
		// PlugAndPlay - Channel Two
		//
        PCI_2CH, PCC_2CH, USB_2CH:
        begin
			pInitPaP:= GetFunction('CAN2_Init');
			bWasLoaded:= Assigned(pInitPaP);
        end
    // PlugAndPlay - Channel One
	//        
    else
		pInitPaP:= GetFunction('CAN_Init');
        bWasLoaded:= Assigned(pInitPaP);
    end; 

	// Loads the common functions
	//    
    Case currHwType Of    
		// Channel One
		//
		ISA_1CH, PCI_1CH, PCC_1CH, USB_1CH, DNG, DNP:    
        begin
			pClose:= GetFunction('CAN_Close');
			pStatus:= GetFunction('CAN_Status');
			pWrite:= GetFunction('CAN_Write');
			pRead:= GetFunction('CAN_Read');
			pReadEx:= GetFunction('CAN_ReadEx');
			pSetRcvEvent:= GetFunction('CAN_SetRcvEvent');
			pVersionInfo:= GetFunction('CAN_VersionInfo');
			pDllVersionInfo:= GetFunction('CAN_DLLVersionInfo');
			pResetClient:= GetFunction('CAN_ResetClient');
			pMsgFilter:= GetFunction('CAN_MsgFilter');
			pResetFilter:= GetFunction('CAN_ResetFilter');        
        end;
		// Channel Two
        //
		PCI_2CH, ISA_2CH, PCC_2CH, USB_2CH:
        begin
			pClose:= GetFunction('CAN2_Close');
			pStatus:= GetFunction('CAN2_Status');
			pWrite:= GetFunction('CAN2_Write');
			pRead:= GetFunction('CAN2_Read');
			pReadEx:= GetFunction('CAN2_ReadEx');
			pVersionInfo:= GetFunction('CAN2_VersionInfo');
			pDllVersionInfo:= GetFunction('CAN2_DLLVersionInfo');
			pResetClient:= GetFunction('CAN2_ResetClient');
			pMsgFilter:= GetFunction('CAN2_MsgFilter');
			pResetFilter:= GetFunction('CAN2_ResetFilter');
			pSetRcvEvent:= GetFunction('CAN2_SetRcvEvent');
        end
    end;

    bWasLoaded:= bWasLoaded AND Assigned(pClose) AND Assigned(pStatus)
        AND Assigned(pWrite) AND Assigned(pRead) AND Assigned(pReadEx)
        AND Assigned(pVersionInfo) AND Assigned(pDllVersionInfo)
        AND Assigned(pResetClient) AND Assigned(pMsgFilter) 
        AND Assigned(pMsgFilter) AND Assigned(pResetFilter) 
        AND (@pSetRcvEvent <> nil);         
	
	// Loads USB specific functions for Channel One
	//
	if (currHwType = USB_1CH) then
	begin
		pSetUSBDeviceNr:= GetFunction('SetUSBDeviceNr');
		pGetUSBDeviceNr:= GetFunction('GetUSBDeviceNr');
		bWasLoaded:= bWasLoaded AND Assigned(pSetUSBDeviceNr) AND Assigned(pGetUSBDeviceNr);
	end;
	// Loads USB specific functions for Channel Two
	//
	if (currHwType = USB_2CH) then
	begin
		pSetUSBDeviceNr:= GetFunction('SetUSB2DeviceNr');
		pGetUSBDeviceNr:= GetFunction('GetUSB2DeviceNr');
		bWasLoaded:= bWasLoaded AND Assigned(pSetUSBDeviceNr) AND Assigned(pGetUSBDeviceNr);
	end;

    if Not bWasLoaded then
        MessageBox(0, 'Error: "DLL could not be loaded!"','Error!', MB_ICONERROR);
end;

// Releases a loaded API
//
procedure PPCANLight.UnloadAPI();
begin
	// Frees the DLL
	//
	FreeCANLightAPI();
	// Resets the API data
	//
	hCANLightDll:= 0;
	InitializePointers();
	// Set the load status to false
	//
	bWasLoaded:= false;
end;

// Frees a loaded DLL
//
function PPCANLight.FreeCANLightAPI(): Boolean; 
begin
	if (hCANLightDll = 0) then
		Result:= false
    else
    	Result:= FreeLibrary(hCANLightDll);
end;

// PCANLight Init function for non Plug and Play Hardware.
// This function make the following:
//		- Activate a Hardware
//		- Make a Register Test of 82C200/SJA1000
//		- Allocate a Send buffer and a Hardware handle
//		- Programs the configuration of the transmit/receive driver
//		- Set the Baudrate register
//		- Set the Controller in RESET condition
//
// "BTR0BTR1" = BTR0-BTR1 baudrate register
// "MsgType" = If the frame type is standard or extended
// "IO_Port" = Input/output Port Address of the hardware
// "Interrupt" = Interrupt number
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
function PPCANLight.Init(BTR0BTR1: Baudrates; MsgType: FramesType; IO_Port: LongWord; Interrupt: Word) : CANResult;
begin
	// DLL for the current HardwareType is not loaded
	//
	if Not bWasLoaded then
		Result:= ERR_NO_DLL
    else
    	Case currHwType of
		    ISA_1CH: 
			    Result:= CANResult(pInitNPaP(Word(BTR0BTR1), Integer(MsgType),Integer(HW_ISA_SJA), LongWord(IO_Port), Word(Interrupt)));            
            ISA_2CH: 
			    Result:= CANResult(pInitNPaP(Word(BTR0BTR1), Integer(MsgType),Integer(HW_ISA_SJA), LongWord(IO_Port), Word(Interrupt)));            
            DNG:
			    Result:= CANResult(pInitNPaP(Word(BTR0BTR1), Integer(MsgType),Integer(HW_DONGLE_SJA), LongWord(IO_Port), Word(Interrupt)));
            DNP: 
			    Result:= CANResult(pInitNPaP(Word(BTR0BTR1), Integer(MsgType),Integer(HW_DONGLE_PRO), LongWord(IO_Port), Word(Interrupt)));            
		else
			// Current HardwareType doesn't support this function
			//
			Result:= ERR_ILLHW;
	    end;
end;

// PCANLight Init function for Plug and Play Hardware.
// This function make the following:
//		- Activate a Hardware
//		- Make a Register Test of 82C200/SJA1000
//		- Allocate a Send buffer and a Hardware handle
//		- Programs the configuration of the transmit/receive driver
//		- Set the Baudrate register
//		- Set the Controller in RESET condition
//
// "BTR0BTR1" = BTR0-BTR1 baudrate register
// "MsgType" = If the frame type is standard or extended
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
function PPCANLight.Init(BTR0BTR1: Baudrates; MsgType: FramesType) : CANResult;
begin
	// DLL for the current HardwareType is not loaded
	//
	if Not bWasLoaded then
		Result:= ERR_NO_DLL
    else
    	Case currHwType of
            PCI_1CH, PCI_2CH, PCC_1CH, PCC_2CH, USB_1CH, USB_2CH:
	    		// Function CAN_Init/CAN2_Init for No-PlugAndPlay Hardware is called
    			//
			    Result:= CANResult(pInitPaP(Word(BTR0BTR1), Integer(MsgType)));
		else
			// Current HardwareType doesn't support this function
			//
			Result:= ERR_ILLHW;
	    end;
end;

// PCANLight Close function.
// This function terminate and release all resources and the configured hardware:
//
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
function PPCANLight.Close(): CANResult;
begin
	// DLL for the current HardwareType is not loaded
	//
	if Not bWasLoaded then
		Result:= ERR_NO_DLL
    else
    	// Function CAN_Close/CAN2_Close is called
    	//
	    Result:= CANResult(pClose());
end;

// PCANLight Status Function
// This function request the current status of the hardware (b.e. BUS-OFF)
//
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
function PPCANLight.Status(): CANResult;
begin
	// DLL for the current HardwareType is not loaded
	//
	if Not bWasLoaded then
		Result:= ERR_NO_DLL
    else
    	// Function CAN_Status/CAN2_Status is called
	    //
    	Result:= CANResult(pStatus()); 
end;

// PCANLight Write function
// This function Place a CAN message into the Transmit Queue of the CAN Hardware
//
// "MsgToSend" = The TPCANMsg message to be written
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
function PPCANLight.Write(var MsgToSend: TPCANMsg): CANResult;
begin
	// DLL for the current HardwareType is not loaded
	//
	if Not bWasLoaded then
		Result:= ERR_NO_DLL
    else
    	// Function CAN_Write/CAN2_Write is called
	    //
    	Result:= CANResult(pWrite(MsgToSend));
end;

// PCANLight Read function
// This function get the next message or the next error from the Receive Queue of
// the CAN Hardware.
// REMARK:
//		- Check always the type of the received Message (MSGTYPE_STANDARD,MSGTYPE_RTR,
//		  MSGTYPE_EXTENDED,MSGTYPE_STATUS)
//		- The function will return ERR_OK always that you receive a CAN message successfully
//		  although if the messages is a MSGTYPE_STATUS message.
//		- When a MSGTYPE_STATUS mesasge is got, the ID and Length information of the message
//		  will be treated as indefined values. Actually information of the received message
//		  should be interpreted using the first 4 data bytes as follow:
//			*	Data0	Data1	Data2	Data3	Kind of Error
//				0x00	0x00	0x00	0x02	CAN_ERR_OVERRUN		0x0002	CAN Controller was read to late
//				0x00	0x00	0x00	0x04	CAN_ERR_BUSLIGHT	0x0004  Bus Error: An error counter limit reached (96)
//				0x00	0x00	0x00	0x08	CAN_ERR_BUSHEAVY	0x0008	Bus Error: An error counter limit reached (128)
//				0x00	0x00	0x00	0x10	CAN_ERR_BUSOFF		0x0010	Bus Error: Can Controller went "Bus-Off"
//		- If a CAN_ERR_BUSOFF status message is received, the CAN Controller must to be
//		  initialized again using the Init() function.  Otherwise, will be not possible
//		  to send/receive more messages.
//
// "MsgBufer" = The TPCANMsg structure to store the CAN message
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
function PPCANLight.Read(var MsgBuffer: TPCANMsg) : CANResult;
begin
	// DLL for the current HardwareType is not loaded
	//
	if Not bWasLoaded then
		Result:= ERR_NO_DLL
    else
    	// Function CAN_Read/CAN2_Read is called
	    //
    	Result:= CANResult(pRead(MsgBuffer));
end;

// PCANLight ReadEx function
// This function get the next message or the next error from the Receive Queue of
// the CAN Hardware and the time when the message arrived.
// REMARK:
//		- Check always the type of the received Message (MSGTYPE_STANDARD,MSGTYPE_RTR,
//		  MSGTYPE_EXTENDED,MSGTYPE_STATUS)
//		- The function will return ERR_OK always that you receive a CAN message successfully
//		  although if the messages is a MSGTYPE_STATUS message.
//		- When a MSGTYPE_STATUS mesasge is got, the ID and Length information of the message
//		  will be treated as indefined values. Actually information of the received message
//		  should be interpreted using the first 4 data bytes as follow:
//			*	Data0	Data1	Data2	Data3	Kind of Error
//				0x00	0x00	0x00	0x02	CAN_ERR_OVERRUN		0x0002	CAN Controller was read to late
//				0x00	0x00	0x00	0x04	CAN_ERR_BUSLIGHT	0x0004  Bus Error: An error counter limit reached (96)
//				0x00	0x00	0x00	0x08	CAN_ERR_BUSHEAVY	0x0008	Bus Error: An error counter limit reached (128)
//				0x00	0x00	0x00	0x10	CAN_ERR_BUSOFF		0x0010	Bus Error: Can Controller went "Bus-Off"
//		- If a CAN_ERR_BUSOFF status message is received, the CAN Controller must to be
//		  initialized again using the Init() function.  Otherwise, will be not possible
//		  to send/receive more messages.
//
// "MsgBufer" = The TPCANMsg structure to store the CAN message
// "RcvTime" = The TPCANTimestamp structure for the message's timestamp
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
function PPCANLight.ReadEx(var MsgBuffer: TPCANMsg; var RcvTime: TPCANTimestamp) : CANResult;
begin
	// DLL for the current HardwareType is not loaded
	//
	if Not bWasLoaded then
		Result:= ERR_NO_DLL
    else
    	// Function CAN_ReadEx/CAN2_ReadEx is called
	    //
    	Result:= CANResult(pReadEx(MsgBuffer, RcvTime)); 
end;

// PCANLight VersionInfo function
// This function get the Version and copyright of the hardware as text
// (max. 255 characters)
//
// "strInfo" = String buffer to return the hardware information
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
function PPCANLight.VersionInfo(var strInfo: string): CANResult;
var 
    ToRead: array [0..254] of Char;
begin
	// DLL for the current HardwareType is not loaded
	//
	if Not bWasLoaded then 
		Result:= ERR_NO_DLL
    else
    begin
    	// Function CAN_VersionInfo/CAN2_VersionInfo is called
	    //
        Result:= CANResult(pVersionInfo(ToRead)); 
        strInfo:= ToRead;
    end;
end;

// PCANLight DllVersionInfo function
// Gets the version information of the used PCAN-Light DLL.
// (max. 255 characters)
//
// "strInfo" = String variable to return the hardware information
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
function PPCANLight.DllVersionInfo(var strInfo: string): CANResult;
var 
    ToRead: array [0..254] of Char;
begin
	// DLL for the current HardwareType is not loaded
	//
	if Not bWasLoaded then
		Result:= ERR_NO_DLL
    else
    begin
        // Function CAN_DllVersionInfo/CAN2_DllVersionInfo is called
    	//
	    Result:= CANResult(pDllVersionInfo(ToRead)); 
        strInfo:= ToRead;
    end;
end;

// PCANLight ResetClient function
// This function delete the both queues (Transmit,Receive) of the CAN Controller
// using a RESET
//
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
function PPCANLight.ResetClient(): CANResult;
begin
	// DLL for the current HardwareType is not loaded
	//
	if Not bWasLoaded then
		Result:= ERR_NO_DLL
    else
    	// Function CAN_ResetClient/CAN2_ResetClient is called
	    //
    	Result:= CANResult(pResetClient());  
end;

// PCANLigth MsgFilter function
// This function set the receive message filter of the CAN Controller.
// REMARK:
//		- A quick register of all messages is possible using the parameters From and To as 0
//		- Every call of this function maybe cause an extention of the receive filter of the
//		  CAN controller, which one can go briefly to RESET
//		- New in Ver 2.x:
//			* Standard frames will be put it down in the acc_mask/code as Bits 28..13
//			* Hardware driver for 82C200 must to be moved to Bits 10..0 again!
//	WARNING:
//		It is not guaranteed to receive ONLY the registered messages.
//
// "From" = First/Start Message ID - It muss be smaller than the "To" parameter
// "To" = Last/Finish Message ID - It muss be bigger than the "From" parameter
// "MsgType" = Kind of Frame - Standard or Extended
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
function PPCANLight.MsgFilter(FromId, ToId: LongWord; MsgType: MsgTypes): CANResult;
begin
	// DLL for the current HardwareType is not loaded
	//
	if Not bWasLoaded then
		Result:= ERR_NO_DLL
    else
    	// Function CAN_MsgFilter/CAN2_MsgFilter is called
	    //
    	Result:= CANResult(pMsgFilter(FromId, ToId, Integer(MsgType))); 
end;

// PCANLigth ResetFilter function
// This function close completely the Message Filter of the Hardware.
// They will be no more messages received.
//
// RETURN = A CANResult value - Error/status of the hardware after execute the function</returns>
//
function PPCANLight.ResetFilter(): CANResult;
begin
	// DLL for the current HardwareType is not loaded
	//
	if Not bWasLoaded then
		Result:= ERR_NO_DLL
    else    
    	// Function CAN_ResetFilter/CAN2_ResetFilter is called
    	//
	    Result:= CANResult(pResetFilter());
end;

// PCANLight SetUSBDeviceNr function
// This function set an identification number to the USB CAN hardware
//
// "DeviceNumber" = Value to be set as Device Number
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
function PPCANLight.SetUSBDeviceNr(DeviceNumber: LongWord): CANResult;
begin
	// DLL for the current HardwareType is not loaded
	//
	if Not bWasLoaded then
		Result:= ERR_NO_DLL
    else
    	case currHwType of
    		USB_1CH, USB_2CH:
    			// Function SetUSBDeviceNr/SetUSB2DeviceNr is called
	    		//
		    	Result:= CANResult(pSetUSBDeviceNr(DeviceNumber))
        else
			// Current HardwareType doesn't support this function
			//
			Result:= ERR_ILLHW;
        end;
end;

// PCANLight GetUSBDeviceNr function
// This function read the device number of a USB CAN Hardware
//
// "HWType" = Hardware to get the Device Number
// "DeviceNumber" = Variable to return the Device Number value
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
function PPCANLight.GetUSBDeviceNr(var DeviceNumber: LongWord): CANResult;
begin
	// DLL for the current HardwareType is not loaded
	//
	if Not bWasLoaded then
		Result:= ERR_NO_DLL
    else
    	Case currHwType of
		    USB_1CH, USB_2CH:
    			// Function GetUSBDeviceNr/GetUSB2DeviceNr is called
	    		//
		    	Result:= CANResult(pGetUSBDeviceNr(DeviceNumber))
    else
		// Current HardwareType doesn't support this function
		//
	    Result:=  ERR_ILLHW;
    end;
end;

// PCANLight SetRcvEvent function
// Sets the handle of the Receive-Event.
//
// "hEvent" = Handle to be set
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
function PPCANLight.SetRcvEvent(hEvent: THandle): CANResult;
begin
	// DLL for the current HardwareType is not loaded
	//
	if Not bWasLoaded then
        Result:= ERR_NO_DLL
    else
    	// Function CAN_SetRcvEvent/CAN2_SetRcvEvent is called
	    //
    	Result:= CANResult(pSetRcvEvent(hEvent));
end;
 
end.
