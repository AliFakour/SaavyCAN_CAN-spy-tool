#include "StdAfx.h"
#include ".\pcanlight.h"

// PCANLight Constructor
//
PCANLight::PCANLight()
{
	bWasLoaded = false;
	hCANLightDll = NULL;
}

// PCANLight Constructor with initialization
// "HWType" = Hardware to be used
//
PCANLight::PCANLight(HardwareType HWType)
{
	bWasLoaded = false;
	hCANLightDll = NULL;

	InitializeAPI(HWType);
}

// PCANLight Destructor
//
PCANLight::~PCANLight()
{
	UnloadAPI();
}

// Initializes the PCANLight for a specific hardware
// "HWType" = Hardware to be used
//
bool PCANLight::InitializeAPI(HardwareType HWType)
{
	// Unloads the current DLL
	//
	UnloadAPI();
	// Sets the new Hardware
	//
	hwType = HWType;
	// Loads the API for the new Hardware
	//
	LoadAPI();

	return bWasLoaded;
}

// Initializes the pointers for the PCANLight functions
//
void PCANLight::InitializePointers()
{
	pInitPaP = NULL;
	pInitNPaP = NULL;
	pClose = NULL;
	pStatus = NULL;
	pWrite = NULL;
	pRead = NULL;
	pReadEx = NULL;
	pVersionInfo = NULL;
	pDllVersionInfo = NULL;
	pResetClient = NULL;
	pMsgFilter = NULL;
	pResetFilter = NULL;
	pSetUSBDeviceNr = NULL;
	pGetUSBDeviceNr = NULL;
	pSetRcvEvent = NULL;
}

// Loads the DLL for the configured hardware
//
bool PCANLight::LoadDllHandle()
{   
	// IT will be loaded
	//
	if(!bWasLoaded)		
		switch(hwType)
		{
			case ISA_1CH:
				hCANLightDll = LoadLibrary("PCAN_ISA");
				break;            

			case ISA_2CH:
				hCANLightDll = LoadLibrary("PCAN_2ISA");
				break;

			case PCI_1CH:
				hCANLightDll = LoadLibrary("PCAN_PCI");
				break;

			case PCI_2CH:
				hCANLightDll = LoadLibrary("PCAN_2PCI");
				break;

			case PCC_1CH:
				hCANLightDll = LoadLibrary("PCAN_PCC");
				break;

			case PCC_2CH:
				hCANLightDll = LoadLibrary("PCAN_2PCC");
				break;

			case USB_1CH:
				hCANLightDll = LoadLibrary("PCAN_USB");
				break;

			case USB_2CH:
				hCANLightDll = LoadLibrary("PCAN_2USB");
				break;

			case DNP:
				hCANLightDll = LoadLibrary("PCAN_DNP");
				break;

			case DNG:
				hCANLightDll = LoadLibrary("PCAN_DNG");
				break;

			// Hardware is not valid for this function
			//
			default:
				hCANLightDll = NULL;
				break;
		}

	// Return if the DLL was loaded or not
	//
	return (hCANLightDll != NULL);
}

// Gets the address of a given function name in a loaded DLL
//
FARPROC PCANLight::GetFunction(char* strName)
{
	// There is no DLL loaded
	//
	if(hCANLightDll == NULL)
		return NULL;

	// Gets the address of the given function in the loeaded DLL
	//
	return GetProcAddress(hCANLightDll, strName);
}

// Instanciates/loads all functions within a loaded DLL
//
void PCANLight::LoadAPI()
{
	// Initializes pointers
	//
	InitializePointers();
	// Loads the DLL
	//
	if(!LoadDllHandle())
		return;
	
	// Loads the Init function
	//
	switch(hwType)
	{
		// No PlugAndPlay - Channel One
		//
		case ISA_1CH:
		case DNP:
		case DNG:
			pInitNPaP = (InitNPAP)GetFunction("CAN_Init");
			bWasLoaded = pInitNPaP != NULL;
			break;
		// No PlugAndPlay - Channel Two
		//
		case ISA_2CH:
			pInitNPaP = (InitNPAP)GetFunction("CAN2_Init");
			bWasLoaded = pInitNPaP != NULL;
			break;
		// PlugAndPlay - Channel Two
		//
		case PCI_2CH:
		case PCC_2CH:		
		case USB_2CH:
			pInitPaP = (InitPAP)GetFunction("CAN2_Init");
			bWasLoaded = pInitPaP != NULL;
			break;
		// PlugAndPlay - Channel One
		//
		default:
			pInitPaP = (InitPAP)GetFunction("CAN_Init");
			bWasLoaded = pInitPaP != NULL;
			break;
	}

	// Loads the common functions
	//
	switch(hwType)
	{
		// Channel One
		//
		case ISA_1CH:
		case PCI_1CH:
		case PCC_1CH:
		case USB_1CH:
		case DNG:
		case DNP:
			pClose = (C_S_RC_RF)GetFunction("CAN_Close");
			pStatus = (C_S_RC_RF)GetFunction("CAN_Status");
			pWrite = (ReadWrite)GetFunction("CAN_Write");
			pRead = (ReadWrite)GetFunction("CAN_Read");
			pReadEx = (ReadExtra)GetFunction("CAN_ReadEx");
			pSetRcvEvent = (ReceiveEvent)GetFunction("CAN_SetRcvEvent");
			pVersionInfo = (GetInfo)GetFunction("CAN_VersionInfo");
			pDllVersionInfo = (GetInfo)GetFunction("CAN_DLLVersionInfo");
			pResetClient = (C_S_RC_RF)GetFunction("CAN_ResetClient");
			pMsgFilter = (MessageFilter)GetFunction("CAN_MsgFilter");
			pResetFilter = (C_S_RC_RF)GetFunction("CAN_ResetFilter");
			break;
		// Channel Two
		//
		case PCI_2CH:
		case ISA_2CH:
		case PCC_2CH:		
		case USB_2CH:
			pClose = (C_S_RC_RF)GetFunction("CAN2_Close");
			pStatus = (C_S_RC_RF)GetFunction("CAN2_Status");
			pWrite = (ReadWrite)GetFunction("CAN2_Write");
			pRead = (ReadWrite)GetFunction("CAN2_Read");
			pReadEx = (ReadExtra)GetFunction("CAN2_ReadEx");
			pVersionInfo = (GetInfo)GetFunction("CAN2_VersionInfo");
			pDllVersionInfo = (GetInfo)GetFunction("CAN2_DLLVersionInfo");
			pResetClient = (C_S_RC_RF)GetFunction("CAN2_ResetClient");
			pMsgFilter = (MessageFilter)GetFunction("CAN2_MsgFilter");
			pResetFilter = (C_S_RC_RF)GetFunction("CAN2_ResetFilter");
			pSetRcvEvent = (ReceiveEvent)GetFunction("CAN2_SetRcvEvent");
	}

	bWasLoaded = bWasLoaded && pClose && pStatus && pWrite && pRead && pReadEx
		&& pVersionInfo && pDllVersionInfo && pResetClient && pMsgFilter
		&& pMsgFilter && pResetFilter && pSetRcvEvent;
	
	// Loads USB specific functions for Channel One
	//
	if(hwType == USB_1CH)		
	{
		pSetUSBDeviceNr = (USBSDevNr)GetFunction("SetUSBDeviceNr");
		pGetUSBDeviceNr = (USBGDevNr)GetFunction("GetUSBDeviceNr");
		bWasLoaded = bWasLoaded && pSetUSBDeviceNr && pGetUSBDeviceNr;
	}
	// Loads USB specific functions for Channel Two
	//
	if(hwType == USB_2CH)
	{
		pSetUSBDeviceNr = (USBSDevNr)GetFunction("SetUSB2DeviceNr");
		pGetUSBDeviceNr = (USBGDevNr)GetFunction("GetUSB2DeviceNr");
		bWasLoaded = bWasLoaded && pSetUSBDeviceNr && pGetUSBDeviceNr;
	}

	// If the API was not loaded (Wrong version), an error message is shown. 
	//
	if(!bWasLoaded)
		::MessageBox(NULL,"Error: \"DLL could not be loaded!\"","Error!",MB_ICONERROR);
}

// Releases a loaded API
//
void PCANLight::UnloadAPI()
{
	// Frees the DLL
	//
	FreeCANLightAPI();
	// Resets the API data
	//
	hCANLightDll = NULL;
	InitializePointers();
	// Set the load status to false
	//
	bWasLoaded = false;
}

// Frees a loaded DLL
//
bool PCANLight::FreeCANLightAPI()
{
	if(hCANLightDll == NULL)
		return false;

	return FreeLibrary(hCANLightDll) > 0;
}

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
CANResult PCANLight::Init(Baudrates BTR0BTR1, FramesType MsgType, DWORD IO_Port, WORD Interrupt)
{
	// DLL for the current HardwareType is not loaded
	//
	if(!bWasLoaded)
		return ERR_NO_DLL;

	switch(hwType)
	{
		case ISA_1CH:
			return (CANResult)pInitNPaP(BTR0BTR1, MsgType, HW_ISA_SJA, IO_Port, Interrupt);
		case ISA_2CH:
			return (CANResult)pInitNPaP(BTR0BTR1, MsgType, HW_ISA_SJA, IO_Port, Interrupt);
		case DNG:
			return (CANResult)pInitNPaP(BTR0BTR1, MsgType, HW_DONGLE_SJA, IO_Port, Interrupt);
		case DNP:
			return (CANResult)pInitNPaP(BTR0BTR1, MsgType, HW_DONGLE_PRO, IO_Port, Interrupt);
		default:
			// Current HardwareType doesn't support this function
			//
			return ERR_ILLHW;
	}
}

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
CANResult PCANLight::Init(Baudrates BTR0BTR1, FramesType MsgType)
{
	// DLL for the current HardwareType is not loaded
	//
	if(!bWasLoaded)
		return ERR_NO_DLL;

	switch(hwType)
	{
		case PCI_1CH:
		case PCI_2CH:
		case PCC_1CH:
		case PCC_2CH:
		case USB_1CH:
		case USB_2CH:
			// Function CAN_Init/CAN2_Init for PlugAndPlay Hardware is called
			//
			return (CANResult)pInitPaP(BTR0BTR1,MsgType);
		default:
			// Current HardwareType doesn't support this function
			//
			return ERR_ILLHW;
	}
}

// PCANLight Close function.
// This function terminate and release all resources and the configured hardware:
//
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
CANResult PCANLight::Close()
{
	// DLL for the current HardwareType is not loaded
	//
	if(!bWasLoaded)
		return ERR_NO_DLL;

	// Function CAN_Close/CAN2_Close is called
	//
	return (CANResult)pClose();
}

// PCANLight Status Function
// This function request the current status of the hardware (b.e. BUS-OFF)
//
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
CANResult PCANLight::Status()
{
	// DLL for the current HardwareType is not loaded
	//
	if(!bWasLoaded)
		return ERR_NO_DLL;

	// Function CAN_Status/CAN2_Status is called
	//
	return (CANResult)pStatus();    
}

// PCANLight Write function
// This function Place a CAN message into the Transmit Queue of the CAN Hardware
//
// "MsgToSend" = The TPCANMsg message to be written
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
CANResult PCANLight::Write(TPCANMsg *MsgToSend)
{
	// DLL for the current HardwareType is not loaded
	//
	if(!bWasLoaded)
		return ERR_NO_DLL;

	// Function CAN_Write/CAN2_Write is called
	//
	return (CANResult)pWrite(MsgToSend);       
}

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
CANResult PCANLight::Read(TPCANMsg *MsgBuffer)
{
	// DLL for the current HardwareType is not loaded
	//
	if(!bWasLoaded)
		return ERR_NO_DLL;

	// Function CAN_Read/CAN2_Read is called
	//
	return (CANResult)pRead(MsgBuffer);   
}

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
CANResult PCANLight::ReadEx(TPCANMsg *MsgBuffer, TPCANTimestamp *RcvTime)
{
	// DLL for the current HardwareType is not loaded
	//
	if(!bWasLoaded)
		return ERR_NO_DLL;

	// Function CAN_ReadEx/CAN2_ReadEx is called
	//
	return (CANResult)pReadEx(MsgBuffer, RcvTime);   
}

// PCANLight VersionInfo function
// This function get the Version and copyright of the hardware as text
// (max. 255 characters)
//
// "strInfo" = String buffer to return the hardware information
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
CANResult PCANLight::VersionInfo(char *strInfo)
{
	// DLL for the current HardwareType is not loaded
	//
	if(!bWasLoaded)
		return ERR_NO_DLL;

	// Function CAN_VersionInfo/CAN2_VersionInfo is called
	//
	return (CANResult)pVersionInfo(strInfo);     
}

// PCANLight DllVersionInfo function
// Gets the version information of the used PCAN-Light DLL.
// (max. 255 characters)
//
// "strInfo" = String variable to return the hardware information
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
CANResult PCANLight::DllVersionInfo(char *strInfo)
{
	// DLL for the current HardwareType is not loaded
	//
	if(!bWasLoaded)
		return ERR_NO_DLL;

	// Function CAN_DllVersionInfo/CAN2_DllVersionInfo is called
	//
	return (CANResult)pDllVersionInfo(strInfo);  
}

// PCANLight ResetClient function
// This function delete the both queues (Transmit,Receive) of the CAN Controller
// using a RESET
//
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
CANResult PCANLight::ResetClient()
{
	// DLL for the current HardwareType is not loaded
	//
	if(!bWasLoaded)
		return ERR_NO_DLL;

	// Function CAN_ResetClient/CAN2_ResetClient is called
	//
	return (CANResult)pResetClient();     
}

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
CANResult PCANLight::MsgFilter(DWORD From, DWORD To, MsgTypes MsgType)
{
	// DLL for the current HardwareType is not loaded
	//
	if(!bWasLoaded)
		return ERR_NO_DLL;

	// Function CAN_MsgFilter/CAN2_MsgFilter is called
	//
	return (CANResult)pMsgFilter(From, To, MsgType);  
}

// PCANLigth ResetFilter function
// This function close completely the Message Filter of the Hardware.
// They will be no more messages received.
//
// RETURN = A CANResult value - Error/status of the hardware after execute the function</returns>
//
CANResult PCANLight::ResetFilter()
{
	// DLL for the current HardwareType is not loaded
	//
	if(!bWasLoaded)
		return ERR_NO_DLL;

	// Function CAN_ResetFilter/CAN2_ResetFilter is called
	//
	return (CANResult)pResetFilter();
}

// PCANLight SetUSBDeviceNr function
// This function set an identification number to the USB CAN hardware
//
// "DeviceNumber" = Value to be set as Device Number
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
CANResult PCANLight::SetUSBDeviceNr(DWORD DeviceNumber)
{
	// DLL for the current HardwareType is not loaded
	//
	if(!bWasLoaded)
		return ERR_NO_DLL;

	switch(hwType)
	{
		case USB_1CH:
		case USB_2CH:
			// Function SetUSBDeviceNr/SetUSB2DeviceNr is called
			//
			return (CANResult)pSetUSBDeviceNr(DeviceNumber);
		default:
			// Current HardwareType doesn't support this function
			//
			return ERR_ILLHW;
	}
}

// PCANLight GetUSBDeviceNr function
// This function read the device number of a USB CAN Hardware
//
// "HWType" = Hardware to get the Device Number
// "DeviceNumber" = Variable to return the Device Number value
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
CANResult PCANLight::GetUSBDeviceNr(DWORD *DeviceNumber)
{
	// DLL for the current HardwareType is not loaded
	//
	if(!bWasLoaded)
		return ERR_NO_DLL;

	switch(hwType)
	{
		case USB_1CH:
		case USB_2CH:
			// Function GetUSBDeviceNr/GetUSB2DeviceNr is called
			//
			return (CANResult)pGetUSBDeviceNr(DeviceNumber);
		default:
			// Current HardwareType doesn't support this function
			//
			return ERR_ILLHW;
	}
}

// PCANLight SetRcvEvent function
// Sets the handle of the Receive-Event.
//
// "hEvent" = Handle to be set
// RETURN = A CANResult value - Error/status of the hardware after execute the function
//
CANResult PCANLight::SetRcvEvent(HANDLE hEvent)
{
	// DLL for the current HardwareType is not loaded
	//
	if(!bWasLoaded)
		return ERR_NO_DLL;

	// Function CAN_SetRcvEvent/CAN2_SetRcvEvent is called
	//
	return (CANResult)pSetRcvEvent(hEvent);  
}
