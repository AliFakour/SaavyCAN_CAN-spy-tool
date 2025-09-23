///////////////////////////////////////////////////////////////////////////////
//	PCAN-Light
//  PCAN-ISA-CLR.h
//
//  Version 2.x
//
//  ~~~~~~~~~~
//
//  Basic Idea:
//
//  ~~~~~~~~~~
//
//  Definition of the PCAN-Light API. 
//	The Driver support a Hardware and a Software who want to communicate with CAN-busses 
//
//  ~~~~~~~~~~~~
//
//  PCAN-Light -API
//
//  ~~~~~~~~~~~~
//
//	- Init(unsigned short BTR0BTR1, int CANMsgType, int CANHwType, unsigned int IO_Port, unsigned short Interupt)
//  - Close()  
//  - Status() 
//  - Write(TPCANMsg %msg) 
//  - Read([Out]TPCANMsg %msg)  
//  - ReadExt([Out]TPCANMsg %msg, [Out]TPCANTimestamp %timestamp)
//  - VersionInfo(StringBuilder^ buffer) 
//  - DLLVersionInfo(StringBuilder^ buffer)
//  - ResetClient()
//  - MsgFilter(unsigned int FromID, unsigned int ToID, int Type)
//  - ResetFilter()
//  - SetRcvEvent(IntPtr hEvent)
//
//  ------------------------------------------------------------------
//  Author : Hoppe, Wilhelm
//  Modified By: Wagner (28.09.2009)
//
//  Language: C++/CLR
//  ------------------------------------------------------------------
//
//  Copyright (C) 1999-2009  PEAK-System Technik GmbH, Darmstadt
//
using namespace System;
using namespace System::Text;
using namespace System::Runtime::InteropServices;

namespace Peak
{
	namespace Can
	{
		namespace Light
		{
			public ref class PCAN_ISA
			{
				public:
					// HardwareType
					// Only SJA 1000 Dongles are supported  !!
					//
					static const int HW_ISA     = 1;
					static const int HW_ISA_SJA = 9;

					#pragma region Frames, IDs and CAN Message types
					// Constants definitions - Frame Type
					//
					static const unsigned int CAN_INIT_TYPE_EX = 1;     // Extended Frames
					static const unsigned int CAN_INIT_TYPE_ST = 0;     // Standard Frames

					// Constants definitions - ID
					//
					static const int CAN_MAX_STANDARD_ID = 0x7FF;    
					static const int CAN_MAX_EXTENDED_ID = 0x1FFFFFFF;

					// Constants definitions  - CAN message types
					//
					static const unsigned char MSGTYPE_STANDARD       = 0x00; // Standard Data frame (11-bit ID)
					static const unsigned char MSGTYPE_RTR            = 0x01; // 1, if Remote Request frame
					static const unsigned char MSGTYPE_EXTENDED       = 0x02; // 1, if Extended Data frame (CAN 2.0B, 29-bit ID)
					static const unsigned char MSGTYPE_STATUS         = 0x80; // 1, if Status information
					#pragma endregion
			    
					#pragma region Baurate Codes
					// Baud rate codes = BTR0/BTR1 register values for the CAN controller
					//
					static const int BAUD_1M           = 0x0014;  //   1 MBit/s
					static const int BAUD_500K         = 0x001C;  // 500 kBit/s 
					static const int BAUD_250K         = 0x011C;  // 250 kBit/s
					static const int BAUD_125K         = 0x031C;  // 125 kBit/s
					static const int BAUD_100K         = 0x432F;  // 100 kBit/s
					static const int BAUD_50K          = 0x472F;  //  50 kBit/s
					static const int BAUD_20K          = 0x532F;  //  20 kBit/s
					static const int BAUD_10K          = 0x672F;  //  10 kBit/s
					static const int BAUD_5K           = 0x7F7F;  //   5 kBit/s
					// you can define your own Baudrate with the BTROBTR1 register !!
					// take a look at www.peak-system.com for our software BAUDTOOL to
					// calculate the BTROBTR1 register for every baudrate and sample point.
					#pragma endregion

					#pragma region Error Codes
					static const int ERR_OK            = 0x0000;  // No error
					static const int ERR_XMTFULL       = 0x0001;  // Transmit buffer in CAN controller is full
					static const int ERR_OVERRUN       = 0x0002;  // CAN controller was read too late
					static const int ERR_BUSLIGHT      = 0x0004;  // Bus error: an error counter reached the 'light' limit
					static const int ERR_BUSHEAVY      = 0x0008;  // Bus error: an error counter reached the 'heavy' limit  
					static const int ERR_BUSOFF        = 0x0010;  // Bus error: the CAN controller is in bus-off state
					static const int ERR_ANYBUSERR     = ERR_BUSLIGHT | ERR_BUSHEAVY | ERR_BUSOFF;
					static const int ERR_QRCVEMPTY     = 0x0020;  // Receive queue is empty
					static const int ERR_QOVERRUN      = 0x0040;  // Receive queue was read too late
					static const int ERR_QXMTFULL      = 0x0080;  // Transmit queue ist full
					static const int ERR_REGTEST       = 0x0100;  // Test of the CAN controller hardware registers failed (no hardware found)
					static const int ERR_NODRIVER      = 0x0200;  // Driver not loaded
					static const int ERR_HWINUSE       = 0x0400; // Hardware already in use by a Net
					static const int ERR_NETINUSE      = 0x0800; // A Client is already connected to the Net
					static const int ERR_ILLHW         = 0x1400; // Hardware handle is invalid
					static const int ERR_ILLNET        = 0x1800; // Net handle is invalid
					static const int ERR_ILLCLIENT     = 0x1C00; // Client handle is invalid
					static const int ERR_ILLHANDLE     = ERR_ILLHW | ERR_ILLNET | ERR_ILLCLIENT;  // Mask for all handle errors
					static const int ERR_RESOURCE      = 0x2000;  // Resource (FIFO, Client, timeout) cannot be created
					static const int ERR_ILLPARAMTYPE  = 0x4000;  // Invalid parameter
					static const int ERR_ILLPARAMVAL   = 0x8000;  // Invalid parameter value
					static const int ERR_UNKNOWN       = 0x10000; // Unknow error
					// All further error conditions <> 0 please ask PEAK when required.......internal driver failure ........
					#pragma endregion

					#pragma region Structures
					// A CAN message
					//
					[StructLayoutAttribute(LayoutKind::Sequential,Pack=1)]
					ref struct TPCANMsg 
					{
						unsigned int ID;             // 11-/29-Bit CAN-ID
						unsigned char MSGTYPE;       // Bits from MSGTYPE_...
						unsigned char LEN;           // Data Length Code (0..8)
						[MarshalAs(UnmanagedType::ByValArray,SizeConst=8)]
						array<unsigned char>^ DATA;  // Data bytes 0..7
					};


					// Timestamp of a receive/transmit event
					// Total microseconds = micros + 1000 * millis + 0xFFFFFFFF * 1000 * millis_overflow
					[StructLayoutAttribute(LayoutKind::Sequential,Pack=1)]
					ref struct TPCANTimestamp
					{
						unsigned int millis;            // Base-value: milliseconds: 0.. 2^32-1
						unsigned short millis_overflow; // Roll-arounds of millis
						unsigned short micros;          // Microseconds: 0..999
					};
					#pragma endregion

					///////////////////////////////////////////////////////////////////////////////
					//  Init()
					//  This function make the following:
					//		- Activate a Hardware
					//		- Make a Register Test of 82C200/SJA1000
					//		- Allocate a Send buffer and a Hardware handle
					//		- Programs the configuration of the transmit/receive driver
					//		- Set the Baudrate register
					//		- Set the Controller in RESET condition	
					//		
					//  If CANMsgType=0  ---> ID 11Bit
					//  If CANMsgType=1  ---> ID 11/29Bit 
					//
					//  CANHw Type:  (Only new SJA Dongle !!!)
					//	HW_ISA             1
					//	HW_DONGLE_SJA      5
					//	HW_DONGLE_SJA_EPP  6
					//	HW_DONGLE_PRO      7
					//	HW_DONGLE_PRO_EPP  8
					//	HW_ISA_SJA         9
					//	HW_PCI		       10
					//
					//  Possible Errors: NOVXD ILLHW REGTEST RESOURCE
					//
					[DllImport("PCAN_ISA.dll", EntryPoint = "CAN_Init")]
					static unsigned int Init(unsigned short BTR0BTR1, int CANMsgType, int CANHwType, unsigned int IO_Port, unsigned short Interupt);

					///////////////////////////////////////////////////////////////////////////////
					//  Close()
					//  This function terminate and release the configured hardware and all 
					//  allocated resources
					//
					//  Possible Errors: NOVXD
					//
					[DllImport("PCAN_ISA.dll", EntryPoint = "CAN_Close")]
					static unsigned int Close();

					///////////////////////////////////////////////////////////////////////////////
					//  Status()
					//  This function request the current status of the hardware (b.e. BUS-OFF)
					//
					//  Possible Errors: NOVXD BUSOFF BUSHEAVY OVERRUN
					//
					[DllImport("PCAN_ISA.dll", EntryPoint = "CAN_Status")]
					static unsigned int Status();

					///////////////////////////////////////////////////////////////////////////////
					//  Write()
					//  This function Place a CAN message into the Transmit Queue of the CAN Hardware
					//
					//  Possible Errors: NOVXD RESOURCE BUSOFF QXMTFULL
					//
					[DllImport("PCAN_ISA.dll", EntryPoint = "CAN_Write")]
					static unsigned int Write(TPCANMsg %msg);

					///////////////////////////////////////////////////////////////////////////////
					//  Read()
					//  This function get the next message or the next error from the Receive Queue of 
					//  the CAN Hardware.  
					//  REMARK:
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
					//		- The message will be written to 'msgbuff'.
					//
					//  Possible Errors: NOVXD  QRCVEMPTY
					//
					[DllImport("PCAN_ISA.dll", EntryPoint = "CAN_Read")]
					static unsigned int Read([Out]TPCANMsg %msg);

					///////////////////////////////////////////////////////////////////////////////
					//  ReadEx()
					//  This function get the next message or the next error from the Receive Queue of 
					//  the CAN Hardware and the time when the message arrived.   
					//  REMARK:
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
					//		- The message will be written to 'msgbuff'.
					//		Since Version 2.x the Ext. Version is available - new Parameter:
					//		-  Receive timestamp
					//
					//  Possible Errors: NOVXD  QRCVEMPTY
					//
					[DllImport("PCAN_ISA.dll", EntryPoint="CAN_ReadEx")]
					static unsigned int ReadEx([Out]TPCANMsg %msg, [Out]TPCANTimestamp %timestamp);

					///////////////////////////////////////////////////////////////////////////////
					//  VersionInfo()
					//  This function get the Version and copyright of the hardware as text 
					//  (max. 255 characters)
					//
					//  Possible Errors:  NOVXD
					//
					[DllImport("PCAN_ISA.dll", EntryPoint = "CAN_VersionInfo")]
					static unsigned int VersionInfo(StringBuilder^ buffer);

					///////////////////////////////////////////////////////////////////////////////
					//  DLLVersionInfo()
					//  This function is used to get the Version and copyright of the 
					//  DLL as text (max. 255 characters)
					//
					//  Possible Errors: -1 for NULL-Pointer parameters :-)
					//
					[DllImport("PCAN_ISA.dll", EntryPoint="CAN_DLLVersionInfo")]
					static unsigned int DLLVersionInfo(StringBuilder^ buffer);

					//////////////////////////////////////////////////////////////////////////////
					//  ResetClient()
					//  This function delete the both queues (Transmit,Receive) of the CAN Controller 
					//  using a RESET
					//
					//  Possible Errors: ERR_ILLCLIENT ERR_NOVXD
					//
					[DllImport("PCAN_ISA.dll", EntryPoint = "CAN_ResetClient")]
					static unsigned int ResetClient();

					///////////////////////////////////////////////////////////////////////////////
					//  MsgFilter(FromID, ToID, int Type)
					//  This function set the receive message filter of the CAN Controller.
					//  REMARK:
					//		- A quick register of all messages is possible using the parameters FromID and ToID = 0
					//		- Every call of this function maybe cause an extention of the receive filter of the 
					//		  CAN controller, which one can go briefly to RESET
					//		- New in Ver 2.x:
					//			* Standard frames will be put it down in the acc_mask/code as Bits 28..13
					//			* Hardware driver for 82C200 must to be moved to Bits 10..0 again!
					//	WARNING: 
					//		It is not guaranteed to receive ONLY the registered messages.
					//
					//  Possible Errors: NOVXD ILLCLIENT ILLNET REGTEST
					//
					[DllImport("PCAN_ISA.dll", EntryPoint = "CAN_MsgFilter")]
					static unsigned int MsgFilter(unsigned int FromID, unsigned int ToID, int Type);

					///////////////////////////////////////////////////////////////////////////////
					//  ResetFilter()
					//  This function close completely the Message Filter of the Hardware.
					//  They will be no more messages received.
					//
					//  Possible Errors: NOVXD
					//
					[DllImport("PCAN_ISA.dll", EntryPoint = "CAN_ResetFilter")]
					static unsigned int ResetFilter();

					///////////////////////////////////////////////////////////////////////////////
					//  SetRcvEvent()
					//  This function is used to set the Event for the Event Handler
					//
					//  Possible Errors: ILLCLIENT, ILLPARAMTYPE, ILLPARAMVAL, ,NOVXD
					//
					[DllImport("PCAN_ISA.DLL", EntryPoint="CAN_SetRcvEvent")]
					static unsigned int SetRcvEvent(IntPtr hEvent);
			};
		}
	}
}