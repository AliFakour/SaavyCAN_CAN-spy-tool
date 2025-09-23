///////////////////////////////////////////////////////////////////////////////
//  Based on:
//  PCAN_ISA_CLR.h
//  PCAN_2ISA_CLR.h
//  PCAN_PCI_CLR.h
//  PCAN_2PCI_CLR.h
//  PCAN_PCC_CLR.h
//  PCAN_2PCC_CLR.h
//  PCAN_DNG_CLR.h
//  PCAN_DNP_CLR.h
//  PCAN_USB_CLR.h
//  PCAN_2USB_CLR.h
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
//  pcan_usb,pcan_2usb
//
//  In order  to offer  a simple  interface, some constant valuest were converted  to enumerate 
//  types.  The class CANLight  make use of all Dlls and gives  an unique interface for all the 
//  hardware types.  A TCLightMsg class is implemented too.  This class will  be used to make a 
//  bridge between the definition of the TPCANMsg structure in every *.h file.  In this way, in 
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
//	 ReadEx()
//   VersionInfo() 
//	 DllVersionInfo()
//   ResetClient()
//   MsgFilter()
//	 ResetFilter()
//	 SetUSBDeviceNr()
//   GetUSBDeviceNr()
//	 SetRcvEvent()
//
//  ------------------------------------------------------------------
//
//  Author  : Keneth Wagner
//  Language : C++/CLR
//	Modified by: J. Urban (14.09.2009)
//
//  Last Modified: Wagner (28.09.2009)
//
//  ------------------------------------------------------------------
//  Copyright (C) 2006-2009  PEAK-System Technik GmbH, Darmstadt
//
#pragma once

// Include of all PCAN-Light headers
//
#include ".\PCAN Includes\Pcan_Dng_Clr.h"
#include ".\PCAN Includes\Pcan_Dnp_Clr.h"
#include ".\PCAN Includes\Pcan_isa_Clr.h"
#include ".\PCAN Includes\Pcan_2Isa_Clr.h"
#include ".\PCAN Includes\Pcan_Usb_Clr.h"
#include ".\PCAN Includes\Pcan_2Usb_Clr.h"
#include ".\PCAN Includes\Pcan_Pci_Clr.h"
#include ".\PCAN Includes\Pcan_2Pci_Clr.h"
#include ".\PCAN Includes\Pcan_Pcc_Clr.h"
#include ".\PCAN Includes\Pcan_2Pcc_Clr.h"

namespace Peak
{
	namespace Can
	{
		namespace Light
		{
			#pragma region Types definition
			/// <summary>
			/// Kind of Frame - Message Type
			/// </summary>
			static enum FramesType
			{
				INIT_TYPE_ST	= 0x00,	//Standart Frame 
				INIT_TYPE_EX	= 0x01,	//Extended Frame
			};

			/// <summary>
			/// Maximal values for the ID of a CAN Message
			/// </summary>
			static enum MaxIDValues
			{
				MAX_STANDARD_ID	= 0x7FF,
				MAX_EXTENDED_ID	= 0x1FFFFFFF,
			};

			/// <summary>
			/// Kind of CAN Message
			/// </summary>
			static enum MsgTypes
			{
				MSGTYPE_STANDARD	= 0x00,		// Standard Frame (11 bit ID)
				MSGTYPE_RTR			= 0x01,		// Remote request
				MSGTYPE_EXTENDED	= 0x02,		// CAN 2.0 B Frame (29 Bit ID)
				MSGTYPE_STATUS		= 0x80,		// Status Message
			};


			/// <summary>
			/// PCAN Hardware enumeration
			/// </summary>
			static enum Hardware
			{
				HW_ISA				= 1,
				HW_DONGLE_SJA		= 5,
				HW_DONGLE_SJA_EPP	= 6,
				HW_DONGLE_PRO		= 7,
				HW_DONGLE_PRO_EPP	= 8,
				HW_ISA_SJA			= 9,
				HW_PCI				= 10,
			};

			/// <summary>
			/// Hardware type corresponding to the different PCAN Light Dlls
			/// </summary>
			static enum HardwareType
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

			/// <summary>
			/// CAN Baudrates
			/// </summary>
			static enum Baudrates
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

			/// <summary>
			/// CAN Error and status values
			/// </summary>
			static enum CANResult 
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
			#pragma endregion	

			#pragma region Classes definition
			/// <summary>
			/// Class to managing the multiple definition of a TCANMsg structure 
			/// between the different PCANLIGHT Classes/Dlls
			/// </summary>

			public ref class TCLightMsg 
			{
				public:
					#pragma region Properties
					/// <summary>
					/// 11/29-Bit CAN-ID
					/// </summary>
					unsigned int ID;    
					/// <summary>
					/// Kind of Message
					/// </summary>
					MsgTypes  MsgType; 
					/// <summary>
					/// Lenght of the Message
					/// </summary>
					unsigned char Len;     
					/// <summary>
					/// Data Bytes (0...7)
					/// </summary>
					array<unsigned char>^ Data;   
					#pragma endregion

					#pragma region Methodes
					#pragma region Constructors, destructors, initialations
					/// <summary>
					/// TCLightMsg standard constructor
					/// </summary>
					TCLightMsg()
					{
						Data = gcnew array<unsigned char>(8);
					}

					/// <summary>
					/// TCLightMsg constructor
					/// </summary>
					/// <param name="Msg">A TCANMsg structure defined in the PCAN_ISA Class</param>
					TCLightMsg(PCAN_ISA::TPCANMsg^ Msg)
					{
						ID = Msg->ID;
						MsgType = (MsgTypes)Msg->MSGTYPE; 
						Len = Msg->LEN;     
						Data = Msg->DATA;
					}

					/// <summary>
					/// TCLightMsg constructor
					/// </summary>
					/// <param name="Msg">A TCANMsg structure defined in the PCAN_2ISA Class</param>
					TCLightMsg(PCAN_2ISA::TPCANMsg^ Msg)
					{
						ID = Msg->ID;
						MsgType = (MsgTypes)Msg->MSGTYPE; 
						Len = Msg->LEN;     
						Data = Msg->DATA;
					}

					/// <summary>
					/// TCLightMsg constructor
					/// </summary>
					/// <param name="Msg">A TCANMsg structure defined in the PCAN_PCI Class</param>
					TCLightMsg(PCAN_PCI::TPCANMsg^ Msg)
					{
						ID = Msg->ID;
						MsgType = (MsgTypes)Msg->MSGTYPE; 
						Len = Msg->LEN;     
						Data = Msg->DATA;
					}

					/// <summary>
					/// TCLightMsg constructor
					/// </summary>
					/// <param name="Msg">A TCANMsg structure defined in the PCAN_2PCI Class</param>
					TCLightMsg(PCAN_2PCI::TPCANMsg^ Msg)
					{
						ID = Msg->ID;
						MsgType = (MsgTypes)Msg->MSGTYPE; 
						Len = Msg->LEN;     
						Data = Msg->DATA;
					}

					/// <summary>
					/// TCLightMsg constructor
					/// </summary>
					/// <param name="Msg">A TCANMsg structure defined in the PCAN_PCC Class</param>
					TCLightMsg(PCAN_PCC::TPCANMsg^ Msg)
					{
						ID = Msg->ID;
						MsgType = (MsgTypes)Msg->MSGTYPE; 
						Len = Msg->LEN;     
						Data = Msg->DATA;
					}

					/// <summary>
					/// TCLightMsg constructor
					/// </summary>
					/// <param name="Msg">A TCANMsg structure defined in the PCAN_2PCC Class</param>
					TCLightMsg(PCAN_2PCC::TPCANMsg^ Msg)
					{
						ID = Msg->ID;
						MsgType = (MsgTypes)Msg->MSGTYPE; 
						Len = Msg->LEN;     
						Data = Msg->DATA;
					}

					/// <summary>
					/// TCLightMsg constructor
					/// </summary>
					/// <param name="Msg">A TCANMsg structure defined in the PCAN_USB Class</param>
					TCLightMsg(PCAN_USB::TPCANMsg^ Msg)
					{
						ID = Msg->ID;
						MsgType = (MsgTypes)Msg->MSGTYPE; 
						Len = Msg->LEN;     
						Data = Msg->DATA;
					}

					/// <summary>
					/// TCLightMsg constructor
					/// </summary>
					/// <param name="Msg">A TCANMsg structure defined in the PCAN_2USB Class</param>
					TCLightMsg(PCAN_2USB::TPCANMsg^ Msg)
					{
						ID = Msg->ID;
						MsgType = (MsgTypes)Msg->MSGTYPE; 
						Len = Msg->LEN;     
						Data = Msg->DATA;
					}

					/// <summary>
					/// TCLightMsg constructor
					/// </summary>
					/// <param name="Msg">A TCANMsg structure defined in the PCAN_DNG Class</param>
					TCLightMsg(PCAN_DNG::TPCANMsg^ Msg)
					{
						ID = Msg->ID;
						MsgType = (MsgTypes)Msg->MSGTYPE; 
						Len = Msg->LEN;     
						Data = Msg->DATA;
					}

					/// <summary>
					/// TCLightMsg constructor
					/// </summary>
					/// <param name="Msg">A TCANMsg structure defined in the PCAN_DNP Class</param>
					TCLightMsg(PCAN_DNP::TPCANMsg^ Msg)
					{
						ID = Msg->ID;
						MsgType = (MsgTypes)Msg->MSGTYPE; 
						Len = Msg->LEN;     
						Data = Msg->DATA;
					}
					#pragma endregion

					#pragma region Casting functions
					/// <summary>
					/// Overloaded Type Casting to a TCANMsg structure defined in the PCAN_ISA class
					/// </summary>
					/// <param name="Msg">Instance of the TCLightMsg Class to cast</param>
					/// <returns>A corresponding TCANMsg structure, defined in PCAN_ISA Class</returns>
					static operator PCAN_ISA::TPCANMsg^ (TCLightMsg^ Msg)
					{
						PCAN_ISA::TPCANMsg^ toReturn;

						toReturn = gcnew PCAN_ISA::TPCANMsg(); 
						toReturn->ID = Msg->ID;
						toReturn->LEN = Msg->Len;
						toReturn->MSGTYPE = Msg->MsgType;
						toReturn->DATA = Msg->Data;

						return  toReturn;
					}

					/// <summary>
					/// Overloaded Type Casting to a TCANMsg structure defined in the PCAN_2ISA class
					/// </summary>
					/// <param name="Msg">Instance of the TCLightMsg Class to cast</param>
					/// <returns>A corresponding TCANMsg structure, defined in PCAN_2ISA Class</returns>
					static operator PCAN_2ISA::TPCANMsg^ (TCLightMsg^ Msg)
					{
						PCAN_2ISA::TPCANMsg^ toReturn;

						toReturn = gcnew PCAN_2ISA::TPCANMsg();

						toReturn->ID = Msg->ID;
						toReturn->LEN = Msg->Len;
						toReturn->MSGTYPE = Msg->MsgType;
						toReturn->DATA = Msg->Data;

						return  toReturn;
					}

					/// <summary>
					/// Overloaded Type Casting to a TCANMsg structure defined in the PCAN_PCI class
					/// </summary>
					/// <param name="Msg">Instance of the TCLightMsg Class to cast</param>
					/// <returns>A corresponding TCANMsg structure, defined in PCAN_PCI Class</returns>
					static operator PCAN_PCI::TPCANMsg^(TCLightMsg^ Msg)
					{
						PCAN_PCI::TPCANMsg^ toReturn;

						toReturn = gcnew PCAN_PCI::TPCANMsg();
						toReturn->ID = Msg->ID;
						toReturn->LEN = Msg->Len;
						toReturn->MSGTYPE = Msg->MsgType;
						toReturn->DATA = Msg->Data;

						return  toReturn;
					}

					/// <summary>
					/// Overloaded Type Casting to a TCANMsg structure defined in the PCAN_2PCI class
					/// </summary>
					/// <param name="Msg">Instance of the TCLightMsg Class to cast</param>
					/// <returns>A corresponding TCANMsg structure, defined in PCAN_2PCI Class</returns>
					static operator PCAN_2PCI::TPCANMsg^(TCLightMsg^ Msg)
					{
						PCAN_2PCI::TPCANMsg^ toReturn;
						
						toReturn = gcnew PCAN_2PCI::TPCANMsg();
						toReturn->ID = Msg->ID;
						toReturn->LEN = Msg->Len;
						toReturn->MSGTYPE = Msg->MsgType;
						toReturn->DATA = Msg->Data;

						return  toReturn;
					}

					/// <summary>
					/// Overloaded Type Casting to a TCANMsg structure defined in the PCAN_PCC class
					/// </summary>
					/// <param name="Msg">Instance of the TCLightMsg Class to cast</param>
					/// <returns>A corresponding TCANMsg structure, defined in PCAN_PCC Class</returns>
					static operator PCAN_PCC::TPCANMsg^(TCLightMsg^ Msg)
					{
						PCAN_PCC::TPCANMsg^ toReturn;
						
						toReturn = gcnew PCAN_PCC::TPCANMsg();
						toReturn->ID = Msg->ID;
						toReturn->LEN = Msg->Len;
						toReturn->MSGTYPE = Msg->MsgType;
						toReturn->DATA = Msg->Data;

						return  toReturn;
					}

					/// <summary>
					/// Overloaded Type Casting to a TCANMsg structure defined in the PCAN_2PCC class
					/// </summary>
					/// <param name="Msg">Instance of the TCLightMsg Class to cast</param>
					/// <returns>A corresponding TCANMsg structure, defined in PCAN_2PCC Class</returns>
					static operator PCAN_2PCC::TPCANMsg^(TCLightMsg^ Msg)
					{
						PCAN_2PCC::TPCANMsg^ toReturn;

						toReturn = gcnew PCAN_2PCC::TPCANMsg();
						toReturn->ID = Msg->ID;
						toReturn->LEN = Msg->Len;
						toReturn->MSGTYPE = Msg->MsgType;
						toReturn->DATA = Msg->Data;

						return  toReturn;
					}

					/// <summary>
					/// Overloaded Type Casting to a TCANMsg structure defined in the PCAN_USB class
					/// </summary>
					/// <param name="Msg">Instance of the TCLightMsg Class to cast</param>
					/// <returns>A corresponding TCANMsg structure, defined in PCAN_USB Class</returns>
					static operator PCAN_USB::TPCANMsg^(TCLightMsg^ Msg)
					{
						PCAN_USB::TPCANMsg^ toReturn;

						toReturn = gcnew PCAN_USB::TPCANMsg();
						toReturn->ID = Msg->ID;
						toReturn->LEN = Msg->Len;
						toReturn->MSGTYPE = Msg->MsgType;
						toReturn->DATA = Msg->Data;

						return  toReturn;
					}

					/// <summary>
					/// Overloaded Type Casting to a TCANMsg structure defined in the PCAN_2USB class
					/// </summary>
					/// <param name="Msg">Instance of the TCLightMsg Class to cast</param>
					/// <returns>A corresponding TCANMsg structure, defined in PCAN_2USB Class</returns>
					static operator PCAN_2USB::TPCANMsg^(TCLightMsg^ Msg)
					{
						PCAN_2USB::TPCANMsg^ toReturn;

						toReturn = gcnew PCAN_2USB::TPCANMsg();
						toReturn->ID = Msg->ID;
						toReturn->LEN = Msg->Len;
						toReturn->MSGTYPE = Msg->MsgType;
						toReturn->DATA = Msg->Data;

						return  toReturn;
					}

					/// <summary>
					/// Overloaded Type Casting to a TCANMsg structure defined in the PCAN_DNG class
					/// </summary>
					/// <param name="Msg">Instance of the TCLightMsg Class to cast</param>
					/// <returns>A corresponding TCANMsg structure, defined in PCAN_DNG Class</returns>
					static operator PCAN_DNG::TPCANMsg^(TCLightMsg^ Msg)
					{
						PCAN_DNG::TPCANMsg^ toReturn;

						toReturn = gcnew PCAN_DNG::TPCANMsg();
						toReturn->ID = Msg->ID;
						toReturn->LEN = Msg->Len;
						toReturn->MSGTYPE = Msg->MsgType;
						toReturn->DATA = Msg->Data;

						return  toReturn;
					}

					/// <summary>
					/// Overloaded Type Casting to a TCANMsg structure defined in the PCAN_DNP class
					/// </summary>
					/// <param name="Msg">Instance of the TCLightMsg Class to cast</param>
					/// <returns>A corresponding TCANMsg structure, defined in PCAN_DNP Class</returns>
					static operator PCAN_DNP::TPCANMsg^(TCLightMsg^ Msg)
					{
						PCAN_DNP::TPCANMsg^ toReturn;

						toReturn = gcnew PCAN_DNP::TPCANMsg();
						toReturn->ID = Msg->ID;
						toReturn->LEN = Msg->Len;
						toReturn->MSGTYPE = Msg->MsgType;
						toReturn->DATA = Msg->Data;

						return  toReturn;
					}
					#pragma endregion
					#pragma endregion
			};

			/// <summary>
			/// Class to managing the multiple definition of a TPCANTimestamp structure 
			/// between the different PCANLIGHT Classes/Dlls
			/// </summary>
			public ref class TCLightTimestamp 
			{
				public:
					#pragma region Properties
					/// <summary>
					/// Base-value: milliseconds: 0.. 2^32-1 
					/// </summary>
					unsigned int millis;
					/// <summary>
					/// Roll-arounds of milliseconds
					/// </summary>
					unsigned short millis_overflow; 
					/// <summary>
					/// Microseconds: 0..999  
					/// </summary>
					unsigned short micros; 
					#pragma endregion

					#pragma region Methodes
					#pragma region Constructors, destructors, initialations
					/// <summary>
					/// TCLightTimestamp standard constructor
					/// </summary>
					TCLightTimestamp()
					{

					}

					/// <summary>
					/// TCLightTimestamp constructor
					/// </summary>
					/// <param name="RcvTime">A TPCANTimestamp structure defined in the PCAN_ISA Class</param>
					TCLightTimestamp(PCAN_ISA::TPCANTimestamp^ RcvTime)
					{
						millis = RcvTime->millis;
						millis_overflow = RcvTime->millis_overflow;
						micros = RcvTime->micros;
					}

					/// <summary>
					/// TCLightTimestamp constructor
					/// </summary>
					/// <param name="Msg">A TPCANTimestamp structure defined in the PCAN_2ISA Class</param>
					TCLightTimestamp(PCAN_2ISA::TPCANTimestamp^ RcvTime)
					{
						millis = RcvTime->millis;
						millis_overflow = RcvTime->millis_overflow;
						micros = RcvTime->micros;
					}

					/// <summary>
					/// TCLightTimestamp constructor
					/// </summary>
					/// <param name="RcvTime">A TPCANTimestamp structure defined in the PCAN_PCI Class</param>
					TCLightTimestamp(PCAN_PCI::TPCANTimestamp^ RcvTime)
					{
						millis = RcvTime->millis;
						millis_overflow = RcvTime->millis_overflow;
						micros = RcvTime->micros;
					}

					/// <summary>
					/// TCLightTimestamp constructor
					/// </summary>
					/// <param name="RcvTime">A TPCANTimestamp structure defined in the PCAN_2PCI Class</param>
					TCLightTimestamp(PCAN_2PCI::TPCANTimestamp^ RcvTime)
					{
						millis = RcvTime->millis;
						millis_overflow = RcvTime->millis_overflow;
						micros = RcvTime->micros;
					}

					/// <summary>
					/// TCLightTimestamp constructor
					/// </summary>
					/// <param name="RcvTime">A TPCANTimestamp structure defined in the PCAN_PCC Class</param>
					TCLightTimestamp(PCAN_PCC::TPCANTimestamp^ RcvTime)
					{
						millis = RcvTime->millis;
						millis_overflow = RcvTime->millis_overflow;
						micros = RcvTime->micros;
					}

					/// <summary>
					/// TCLightTimestamp constructor
					/// </summary>
					/// <param name="RcvTime">A TPCANTimestamp structure defined in the PCAN_2PCC Class</param>
					TCLightTimestamp(PCAN_2PCC::TPCANTimestamp^ RcvTime)
					{
						millis = RcvTime->millis;
						millis_overflow = RcvTime->millis_overflow;
						micros = RcvTime->micros;
					}

					/// <summary>
					/// TCLightTimestamp constructor
					/// </summary>
					/// <param name="RcvTime">A TPCANTimestamp structure defined in the PCAN_USB Class</param>
					TCLightTimestamp(PCAN_USB::TPCANTimestamp^ RcvTime)
					{
						millis = RcvTime->millis;
						millis_overflow = RcvTime->millis_overflow;
						micros = RcvTime->micros;
					}

					/// <summary>
					/// TCLightTimestamp constructor
					/// </summary>
					/// <param name="RcvTime">A TPCANTimestamp structure defined in the PCAN_2USB Class</param>
					TCLightTimestamp(PCAN_2USB::TPCANTimestamp^ RcvTime)
					{
						millis = RcvTime->millis;
						millis_overflow = RcvTime->millis_overflow;
						micros = RcvTime->micros;
					}

					/// <summary>
					/// TCLightTimestamp constructor
					/// </summary>
					/// <param name="RcvTime">A TPCANTimestamp structure defined in the PCAN_DNG Class</param>
					TCLightTimestamp(PCAN_DNG::TPCANTimestamp^ RcvTime)
					{
						millis = RcvTime->millis;
						millis_overflow = RcvTime->millis_overflow;
						micros = RcvTime->micros;
					}

					/// <summary>
					/// TCLightTimestamp constructor
					/// </summary>
					/// <param name="RcvTime">A TPCANTimestamp structure defined in the PCAN_DNP Class</param>
					TCLightTimestamp(PCAN_DNP::TPCANTimestamp^ RcvTime)
					{
						millis = RcvTime->millis;
						millis_overflow = RcvTime->millis_overflow;
						micros = RcvTime->micros;
					}
					#pragma endregion

					#pragma region Casting functions
					/// <summary>
					/// Overloaded Type Casting to a TPCANTimestamp structure defined in the PCAN_ISA class
					/// </summary>
					/// <param name="RcvTime">Instance of the TCLightTimestamp Class to cast</param>
					/// <returns>A corresponding TPCANTimestamp structure, defined in PCAN_ISA Class</returns>
					static operator PCAN_ISA::TPCANTimestamp^ (TCLightTimestamp^ RcvTime)
					{
						PCAN_ISA::TPCANTimestamp^ toReturn;

						toReturn = gcnew PCAN_ISA::TPCANTimestamp(); 
						toReturn->millis = RcvTime->millis;
						toReturn->millis_overflow = RcvTime->millis_overflow;
						toReturn->micros = RcvTime->micros;

						return  toReturn;
					}

					/// <summary>
					/// Overloaded Type Casting to a TPCANTimestamp structure defined in the PCAN_2ISA class
					/// </summary>
					/// <param name="RcvTime">Instance of the TCLightTimestamp Class to cast</param>
					/// <returns>A corresponding TPCANTimestamp structure, defined in PCAN_2ISA Class</returns>
					static operator PCAN_2ISA::TPCANTimestamp^ (TCLightTimestamp^ RcvTime)
					{
						PCAN_2ISA::TPCANTimestamp^ toReturn;

						toReturn = gcnew PCAN_2ISA::TPCANTimestamp(); 
						toReturn->millis = RcvTime->millis;
						toReturn->millis_overflow = RcvTime->millis_overflow;
						toReturn->micros = RcvTime->micros;

						return  toReturn;
					}

					/// <summary>
					/// Overloaded Type Casting to a TPCANTimestamp structure defined in the PCAN_PCI class
					/// </summary>
					/// <param name="RcvTime">Instance of the TCLightTimestamp Class to cast</param>
					/// <returns>A corresponding TPCANTimestamp structure, defined in PCAN_PCI Class</returns>
					static operator PCAN_PCI::TPCANTimestamp^ (TCLightTimestamp^ RcvTime)
					{
						PCAN_PCI::TPCANTimestamp^ toReturn;

						toReturn = gcnew PCAN_PCI::TPCANTimestamp(); 
						toReturn->millis = RcvTime->millis;
						toReturn->millis_overflow = RcvTime->millis_overflow;
						toReturn->micros = RcvTime->micros;

						return  toReturn;
					}

					/// <summary>
					/// Overloaded Type Casting to a TPCANTimestamp structure defined in the PCAN_2PCI class
					/// </summary>
					/// <param name="RcvTime">Instance of the TCLightTimestamp Class to cast</param>
					/// <returns>A corresponding TPCANTimestamp structure, defined in PCAN_2PCI Class</returns>
					static operator PCAN_2PCI::TPCANTimestamp^ (TCLightTimestamp^ RcvTime)
					{
						PCAN_2PCI::TPCANTimestamp^ toReturn;

						toReturn = gcnew PCAN_2PCI::TPCANTimestamp(); 
						toReturn->millis = RcvTime->millis;
						toReturn->millis_overflow = RcvTime->millis_overflow;
						toReturn->micros = RcvTime->micros;

						return  toReturn;
					}

					/// <summary>
					/// Overloaded Type Casting to a TPCANTimestamp structure defined in the PCAN_PCC class
					/// </summary>
					/// <param name="RcvTime">Instance of the TCLightTimestamp Class to cast</param>
					/// <returns>A corresponding TPCANTimestamp structure, defined in PCAN_PCC Class</returns>
					static operator PCAN_PCC::TPCANTimestamp^ (TCLightTimestamp^ RcvTime)
					{
						PCAN_PCC::TPCANTimestamp^ toReturn;

						toReturn = gcnew PCAN_PCC::TPCANTimestamp(); 
						toReturn->millis = RcvTime->millis;
						toReturn->millis_overflow = RcvTime->millis_overflow;
						toReturn->micros = RcvTime->micros;

						return  toReturn;
					}

					/// <summary>
					/// Overloaded Type Casting to a TPCANTimestamp structure defined in the PCAN_2PCC class
					/// </summary>
					/// <param name="RcvTime">Instance of the TCLightTimestamp Class to cast</param>
					/// <returns>A corresponding TPCANTimestamp structure, defined in PCAN_2PCC Class</returns>
					static operator PCAN_2PCC::TPCANTimestamp^ (TCLightTimestamp^ RcvTime)
					{
						PCAN_2PCC::TPCANTimestamp^ toReturn;

						toReturn = gcnew PCAN_2PCC::TPCANTimestamp(); 
						toReturn->millis = RcvTime->millis;
						toReturn->millis_overflow = RcvTime->millis_overflow;
						toReturn->micros = RcvTime->micros;

						return  toReturn;
					}

					/// <summary>
					/// Overloaded Type Casting to a TPCANTimestamp structure defined in the PCAN_USB class
					/// </summary>
					/// <param name="RcvTime">Instance of the TCLightTimestamp Class to cast</param>
					/// <returns>A corresponding TPCANTimestamp structure, defined in PCAN_USB Class</returns>
					static operator PCAN_USB::TPCANTimestamp^ (TCLightTimestamp^ RcvTime)
					{
						PCAN_USB::TPCANTimestamp^ toReturn;

						toReturn = gcnew PCAN_USB::TPCANTimestamp(); 
						toReturn->millis = RcvTime->millis;
						toReturn->millis_overflow = RcvTime->millis_overflow;
						toReturn->micros = RcvTime->micros;

						return  toReturn;
					}

					/// <summary>
					/// Overloaded Type Casting to a TPCANTimestamp structure defined in the PCAN_2USB class
					/// </summary>
					/// <param name="RcvTime">Instance of the TCLightTimestamp Class to cast</param>
					/// <returns>A corresponding TPCANTimestamp structure, defined in PCAN_2USB Class</returns>
					static operator PCAN_2USB::TPCANTimestamp^ (TCLightTimestamp^ RcvTime)
					{
						PCAN_2USB::TPCANTimestamp^ toReturn;

						toReturn = gcnew PCAN_2USB::TPCANTimestamp(); 
						toReturn->millis = RcvTime->millis;
						toReturn->millis_overflow = RcvTime->millis_overflow;
						toReturn->micros = RcvTime->micros;

						return  toReturn;
					}

					/// <summary>
					/// Overloaded Type Casting to a TPCANTimestamp structure defined in the PCAN_DNG class
					/// </summary>
					/// <param name="RcvTime">Instance of the TCLightTimestamp Class to cast</param>
					/// <returns>A corresponding TPCANTimestamp structure, defined in PCAN_DNG Class</returns>
					static operator PCAN_DNG::TPCANTimestamp^ (TCLightTimestamp^ RcvTime)
					{
						PCAN_DNG::TPCANTimestamp^ toReturn;

						toReturn = gcnew PCAN_DNG::TPCANTimestamp(); 
						toReturn->millis = RcvTime->millis;
						toReturn->millis_overflow = RcvTime->millis_overflow;
						toReturn->micros = RcvTime->micros;

						return  toReturn;
					}

					/// <summary>
					/// Overloaded Type Casting to a TPCANTimestamp structure defined in the PCAN_DNP class
					/// </summary>
					/// <param name="RcvTime">Instance of the TCLightTimestamp Class to cast</param>
					/// <returns>A corresponding TPCANTimestamp structure, defined in PCAN_DNP Class</returns>
					static operator PCAN_DNP::TPCANTimestamp^ (TCLightTimestamp^ RcvTime)
					{
						PCAN_DNP::TPCANTimestamp^ toReturn;

						toReturn = gcnew PCAN_DNP::TPCANTimestamp(); 
						toReturn->millis = RcvTime->millis;
						toReturn->millis_overflow = RcvTime->millis_overflow;
						toReturn->micros = RcvTime->micros;

						return  toReturn;
					}
					#pragma endregion
					#pragma endregion
			};

			/// <summary>
			/// Interfacing class to the PCAN Light Dlls
			/// </summary>
			public ref class PCANLight
			{
				public:
					#pragma region Methodes
					#pragma region PCANLight Functions
					/// <summary>
					/// PCANLight Init function for non Plug and Play Hardware.  
					/// This function make the following:
					///		- Activate a Hardware
					///		- Make a Register Test of 82C200/SJA1000
					///		- Allocate a Send buffer and a Hardware handle
					///		- Programs the configuration of the transmit/receive driver
					///		- Set the Baudrate register
					///		- Set the Controller in RESET condition
					/// </summary>
					/// <param name="HWType">Which hardware should be initialized</param>
					/// <param name="BTR0BTR1">BTR0-BTR1 baudrate register</param>
					/// <param name="MsgType">If the frame type is standard or extended</param>
					/// <param name="IO_Port">Input/output Port Address of the hardware</param>
					/// <param name="Interrupt">Interrupt number</param>
					/// <returns>A CANResult value - Error/status of the hardware after execute the function</returns>
					static CANResult Init(HardwareType HWType,Baudrates BTR0BTR1, FramesType MsgType, unsigned int IO_Port, unsigned short Interrupt)
					{
						try
						{
							switch(HWType)
							{
								case ISA_1CH:
									return (CANResult)PCAN_ISA::Init(BTR0BTR1,MsgType,HW_ISA_SJA,IO_Port,Interrupt);

								case ISA_2CH:
									return (CANResult)PCAN_2ISA::Init(BTR0BTR1,MsgType,HW_ISA_SJA,IO_Port,Interrupt);

								case DNG:
									return (CANResult)PCAN_DNG::Init(BTR0BTR1,MsgType,HW_DONGLE_SJA,IO_Port,Interrupt);

								case DNP:
									return (CANResult)PCAN_DNP::Init(BTR0BTR1,MsgType,HW_DONGLE_PRO,IO_Port,Interrupt);
								
								// Hardware is not valid for this function
								//
								default:
									return ERR_ILLHW;
							}
						}
						catch(Exception^ Ex)
						{
							// Error: Dll does not exists or the function is not available
							//
							System::Windows::Forms::MessageBox::Show("Error: \"" + Ex->Message + "\"");
							return ERR_NO_DLL;
						}
					}

					/// <summary>
					/// PCANLight Init function for Plug and Play Hardware.
					/// This function make the following:
					///		- Activate a Hardware
					///		- Make a Register Test of 82C200/SJA1000
					///		- Allocate a Send buffer and a Hardware handle
					///		- Programs the configuration of the transmit/receive driver
					///		- Set the Baudrate register
					///		- Set the Controller in RESET condition
					/// </summary>
					/// <param name="HWType">Which hardware should be initialized</param>
					/// <param name="BTR0BTR1">BTR0-BTR1 baudrate register</param>
					/// <param name="MsgType">f the frame type is standard or extended</param>
					/// <returns>A CANResult value - Error/status of the hardware after execute the function</returns>
					static CANResult Init(HardwareType HWType,Baudrates BTR0BTR1, FramesType MsgType)
					{
						try
						{
							switch(HWType)
							{
								case PCI_1CH:
									return (CANResult)PCAN_PCI::Init(BTR0BTR1,MsgType);

								case PCI_2CH:
									return (CANResult)PCAN_2PCI::Init(BTR0BTR1,MsgType);

								case PCC_1CH:
									return (CANResult)PCAN_PCC::Init(BTR0BTR1,MsgType);

								case PCC_2CH:
									return (CANResult)PCAN_2PCC::Init(BTR0BTR1,MsgType);

								case USB_1CH:
									return (CANResult)PCAN_USB::Init(BTR0BTR1,MsgType);

								case USB_2CH:
									return (CANResult)PCAN_2USB::Init(BTR0BTR1,MsgType);

								// Hardware is not valid for this function
								//
								default:
									return ERR_ILLHW;
							}
						}
						catch(Exception^ Ex)
						{
							// Error: Dll does not exists or the function is not available
							//
							System::Windows::Forms::MessageBox::Show("Error: \"" + Ex->Message + "\"");
							return ERR_NO_DLL;
						}
					}

					/// <summary>
					/// PCANLight Close function.
					/// This function terminate and release all resources and the configured hardware:
					/// </summary>
					/// <param name="HWType">Which hardware should be finished</param>
					/// <returns>A CANResult value - Error/status of the hardware after execute the function</returns>
					static CANResult Close(HardwareType HWType)
					{
						try
						{
							switch(HWType)
							{
								case ISA_1CH:
									return (CANResult)PCAN_ISA::Close();

								case ISA_2CH:
									return (CANResult)PCAN_2ISA::Close();

								case PCI_1CH:
									return (CANResult)PCAN_PCI::Close();

								case PCI_2CH:
									return (CANResult)PCAN_2PCI::Close();

								case PCC_1CH:
									return (CANResult)PCAN_PCC::Close();

								case PCC_2CH:
									return (CANResult)PCAN_2PCC::Close();

								case USB_1CH:
									return (CANResult)PCAN_USB::Close();

								case USB_2CH:
									return (CANResult)PCAN_2USB::Close();

								case DNP:
									return (CANResult)PCAN_DNP::Close();

								case DNG:
									return (CANResult)PCAN_DNG::Close();

								// Hardware is not valid for this function
								//
								default:
									return ERR_ILLHW;
							}
						}
						catch(Exception^ Ex)
						{
							// Error: Dll does not exists or the function is not available
							//
							System::Windows::Forms::MessageBox::Show("Error: \"" + Ex->Message + "\"");
							return ERR_NO_DLL;
						}
					}

					/// <summary>
					/// PCANLight Status Function
					/// This function request the current status of the hardware (b.e. BUS-OFF)
					/// </summary>
					/// <param name="HWType">Which hardware should be asked for it Status</param>
					/// <returns>A CANResult value - Error/status of the hardware after execute the function</returns>
					static CANResult Status(HardwareType HWType)
					{
						try
						{
							switch(HWType)
							{
								case ISA_1CH:
									return (CANResult)PCAN_ISA::Status();

								case ISA_2CH:
									return (CANResult)PCAN_2ISA::Status();

								case PCI_1CH:
									return (CANResult)PCAN_PCI::Status();

								case PCI_2CH:
									return (CANResult)PCAN_2PCI::Status();

								case PCC_1CH:
									return (CANResult)PCAN_PCC::Status();

								case PCC_2CH:
									return (CANResult)PCAN_2PCC::Status();

								case USB_1CH:
									return (CANResult)PCAN_USB::Status();

								case USB_2CH:
									return (CANResult)PCAN_2USB::Status();

								case DNP:
									return (CANResult)PCAN_DNP::Status();

								case DNG:
									return (CANResult)PCAN_DNG::Status();

								// Hardware is not valid for this function
								//
								default:
									return ERR_ILLHW;
							}
						}
						catch(Exception^ Ex)
						{
							// Error: Dll does not exists or the function is not available
							//
							System::Windows::Forms::MessageBox::Show("Error: \"" + Ex->Message + "\"");
							return ERR_NO_DLL;
						}
					}

					/// <summary>
					/// PCANLight Write function
					/// This function Place a CAN message into the Transmit Queue of the CAN Hardware
					/// </summary>
					/// <param name="HWType">In which hardware should be written the CAN Message</param>3
					/// <param name="MsgToSend">The TCLightMsg message to be written</param>
					/// <returns>A CANResult value - Error/status of the hardware after execute the function</returns>
					static CANResult Write(HardwareType HWType, TCLightMsg^ MsgToSend)
					{
						PCAN_ISA::TPCANMsg^ MsgIsa;
						PCAN_2ISA::TPCANMsg^ MsgIsa2;
						PCAN_PCI::TPCANMsg^ MsgPci;
						PCAN_2PCI::TPCANMsg^ MsgPci2;
						PCAN_PCC::TPCANMsg^ MsgPcc;
						PCAN_2PCC::TPCANMsg^ MsgPcc2;
						PCAN_USB::TPCANMsg^ MsgUsb;
						PCAN_2USB::TPCANMsg^ MsgUsb2;
						PCAN_DNP::TPCANMsg^ MsgDnp;
						PCAN_DNG::TPCANMsg^ MsgDng;

						try
						{
							switch(HWType)
							{
								case ISA_1CH:
									MsgIsa = MsgToSend;
									return (CANResult)PCAN_ISA::Write(*MsgIsa);

								case ISA_2CH:
									MsgIsa2 = MsgToSend;
									return (CANResult)PCAN_2ISA::Write(*MsgIsa2);

								case PCI_1CH:
									MsgPci = MsgToSend;
									return (CANResult)PCAN_PCI::Write(*MsgPci);

								case PCI_2CH:
									MsgPci2 = MsgToSend;
									return (CANResult)PCAN_2PCI::Write(*MsgPci2);

								case PCC_1CH:
									MsgPcc = MsgToSend;
									return (CANResult)PCAN_PCC::Write(*MsgPcc);

								case PCC_2CH:
									MsgPcc2 = MsgToSend;
									return (CANResult)PCAN_2PCC::Write(*MsgPcc2);

								case USB_1CH:
									MsgUsb = MsgToSend;
									return (CANResult)PCAN_USB::Write(*MsgUsb);

								case USB_2CH:
									MsgUsb2 = MsgToSend;
									return (CANResult)PCAN_2USB::Write(*MsgUsb2);

								case DNP:
									MsgDnp = MsgToSend;
									return (CANResult)PCAN_DNP::Write(*MsgDnp);

								case DNG:
									MsgDng = MsgToSend;
									return (CANResult)PCAN_DNG::Write(*MsgDng);

								// Hardware is not valid for this function
								//					
								default:
									return ERR_ILLHW;
							}
						}
						catch(Exception^ Ex)
						{
							// Error: Dll does not exists or the function is not available
							//
							System::Windows::Forms::MessageBox::Show("Error: \"" + Ex->Message + "\"");
							return ERR_NO_DLL;
						}
					}

					/// <summary>
					/// PCANLight Read function
					/// This function get the next message or the next error from the Receive Queue of 
					/// the CAN Hardware.  
					/// REMARK:
					///		- Check always the type of the received Message (MSGTYPE_STANDARD,MSGTYPE_RTR,
					///		  MSGTYPE_EXTENDED,MSGTYPE_STATUS)
					///		- The function will return ERR_OK always that you receive a CAN message successfully 
					///		  although if the messages is a MSGTYPE_STATUS message.  
					///		- When a MSGTYPE_STATUS mesasge is got, the ID and Length information of the message 
					///		  will be treated as indefined values. Actually information of the received message
					///		  should be interpreted using the first 4 data bytes as follow:
					///			*	Data0	Data1	Data2	Data3	Kind of Error
					///				0x00	0x00	0x00	0x02	CAN_ERR_OVERRUN		0x0002	CAN Controller was read to late
					///				0x00	0x00	0x00	0x04	CAN_ERR_BUSLIGHT	0x0004  Bus Error: An error counter limit reached (96)
					///				0x00	0x00	0x00	0x08	CAN_ERR_BUSHEAVY	0x0008	Bus Error: An error counter limit reached (128)
					///				0x00	0x00	0x00	0x10	CAN_ERR_BUSOFF		0x0010	Bus Error: Can Controller went "Bus-Off"
					///		- If a CAN_ERR_BUSOFF status message is received, the CAN Controller must to be 
					///		  initialized again using the Init() function.  Otherwise, will be not possible 
					///		  to send/receive more messages.
					/// </summary>
					/// <param name="HWType">From which hardware should be read a CAN Message</param>
					/// <param name="Msg">The TCLightMsg structure to store the CAN message</param>
					/// <returns>A CANResult value - Error/status of the hardware after execute the function</returns>
					static CANResult Read(HardwareType HWType, TCLightMsg^ %Msg)
					{
						PCAN_ISA::TPCANMsg MsgIsa;
						PCAN_2ISA::TPCANMsg MsgIsa2;
						PCAN_PCI::TPCANMsg MsgPci;
						PCAN_2PCI::TPCANMsg MsgPci2;
						PCAN_PCC::TPCANMsg MsgPcc;
						PCAN_2PCC::TPCANMsg MsgPcc2;
						PCAN_USB::TPCANMsg MsgUsb;
						PCAN_2USB::TPCANMsg MsgUsb2;
						PCAN_DNP::TPCANMsg MsgDnp;
						PCAN_DNG::TPCANMsg MsgDng;
						CANResult resTemp;

						try
						{
							switch(HWType)
							{
								case ISA_1CH:
									resTemp = (CANResult)PCAN_ISA::Read(MsgIsa);
									Msg = gcnew TCLightMsg(%MsgIsa);
									return resTemp;

								case ISA_2CH:
									resTemp = (CANResult)PCAN_2ISA::Read(MsgIsa2);
									Msg = gcnew TCLightMsg(%MsgIsa2);
									return resTemp;

								case PCI_1CH:
									resTemp = (CANResult)PCAN_PCI::Read(MsgPci);
									Msg = gcnew TCLightMsg(%MsgPci);
									return resTemp;

								case PCI_2CH:
									resTemp = (CANResult)PCAN_2PCI::Read(MsgPci2);
									Msg = gcnew TCLightMsg(%MsgPci2);
									return resTemp;

								case PCC_1CH:
									resTemp = (CANResult)PCAN_PCC::Read(MsgPcc);
									Msg = gcnew TCLightMsg(%MsgPcc);
									return resTemp;

								case PCC_2CH:
									resTemp = (CANResult)PCAN_2PCC::Read(MsgPcc2);
									Msg = gcnew TCLightMsg(%MsgPcc2);
									return resTemp;

								case USB_1CH:
									resTemp = (CANResult)PCAN_USB::Read(MsgUsb);
									Msg = gcnew TCLightMsg(%MsgUsb);
									return resTemp;

								case USB_2CH:
									resTemp = (CANResult)PCAN_2USB::Read(MsgUsb2);
									Msg = gcnew TCLightMsg(%MsgUsb2);
									return resTemp;

								case DNP:
									resTemp = (CANResult)PCAN_DNP::Read(MsgDnp);
									Msg = gcnew TCLightMsg(%MsgDnp);
									return resTemp;

								case DNG:
									resTemp = (CANResult)PCAN_DNG::Read(MsgDng);
									Msg = gcnew TCLightMsg(%MsgDng);
									return resTemp;

								// Hardware is not valid for this function
								//
								default:
									Msg = nullptr;
									return ERR_ILLHW;
							}
						}
						catch(Exception^ Ex)
						{
							// Error: Dll does not exists or the function is not available
							//
							Msg = nullptr;
							System::Windows::Forms::MessageBox::Show("Error: \"" + Ex->Message + "\"");
							return ERR_NO_DLL;
						}
					}

					/// <summary>
					/// PCANLight ReadEx function
					/// This function get the next message or the next error from the Receive Queue of 
					/// the CAN Hardware and the time when the message arrived.   
					/// REMARK:
					///		- Check always the type of the received Message (MSGTYPE_STANDARD,MSGTYPE_RTR,
					///		  MSGTYPE_EXTENDED,MSGTYPE_STATUS)
					///		- The function will return ERR_OK always that you receive a CAN message successfully 
					///		  although if the messages is a MSGTYPE_STATUS message.  
					///		- When a MSGTYPE_STATUS mesasge is got, the ID and Length information of the message 
					///		  will be treated as indefined values. Actually information of the received message
					///		  should be interpreted using the first 4 data bytes as follow:
					///			*	Data0	Data1	Data2	Data3	Kind of Error
					///				0x00	0x00	0x00	0x02	CAN_ERR_OVERRUN		0x0002	CAN Controller was read to late
					///				0x00	0x00	0x00	0x04	CAN_ERR_BUSLIGHT	0x0004  Bus Error: An error counter limit reached (96)
					///				0x00	0x00	0x00	0x08	CAN_ERR_BUSHEAVY	0x0008	Bus Error: An error counter limit reached (128)
					///				0x00	0x00	0x00	0x10	CAN_ERR_BUSOFF		0x0010	Bus Error: Can Controller went "Bus-Off"
					///		- If a CAN_ERR_BUSOFF status message is received, the CAN Controller must to be 
					///		  initialized again using the Init() function.  Otherwise, will be not possible 
					///		  to send/receive more messages.
					/// </summary>
					/// <param name="HWType">From which hardware should be read a CAN Message</param>
					/// <param name="Msg">The TCLightMsg structure to store the CAN message</param>
					/// <param name="RcvTime">The TCLightTimestamp structure to store the timestamp of the CAN message</param>
					/// <returns>A CANResult value - Error/status of the hardware after execute the function</returns>
					/// <exception>Throws a EntryPointNotFoundException if function isn't available in loaded DLL</exception>
					static CANResult ReadEx(HardwareType HWType, TCLightMsg^ %Msg, TCLightTimestamp^ %RcvTime)
					{
						PCAN_ISA::TPCANMsg MsgIsa;
						PCAN_2ISA::TPCANMsg MsgIsa2;
						PCAN_PCI::TPCANMsg MsgPci;
						PCAN_2PCI::TPCANMsg MsgPci2;
						PCAN_PCC::TPCANMsg MsgPcc;
						PCAN_2PCC::TPCANMsg MsgPcc2;
						PCAN_USB::TPCANMsg MsgUsb;
						PCAN_2USB::TPCANMsg MsgUsb2;
						PCAN_DNP::TPCANMsg MsgDnp;
						PCAN_DNG::TPCANMsg MsgDng;

						PCAN_ISA::TPCANTimestamp RcvTimeIsa;
						PCAN_2ISA::TPCANTimestamp RcvTimeIsa2;
						PCAN_PCI::TPCANTimestamp RcvTimePci;
						PCAN_2PCI::TPCANTimestamp RcvTimePci2;
						PCAN_PCC::TPCANTimestamp RcvTimePcc;
						PCAN_2PCC::TPCANTimestamp RcvTimePcc2;
						PCAN_USB::TPCANTimestamp RcvTimeUsb;
						PCAN_2USB::TPCANTimestamp RcvTimeUsb2;
						PCAN_DNP::TPCANTimestamp RcvTimeDnp;
						PCAN_DNG::TPCANTimestamp RcvTimeDng;

						CANResult resTemp;

						try
						{
							Msg = nullptr;
							RcvTime = nullptr;

							switch(HWType)
							{
								case ISA_1CH:
									resTemp = (CANResult)PCAN_ISA::ReadEx(MsgIsa, RcvTimeIsa);
									Msg = gcnew TCLightMsg(%MsgIsa);
									RcvTime = gcnew TCLightTimestamp(%RcvTimeIsa);
									return resTemp;

								case ISA_2CH:
									resTemp = (CANResult)PCAN_2ISA::ReadEx(MsgIsa2, RcvTimeIsa2);
									Msg = gcnew TCLightMsg(%MsgIsa2);
									RcvTime = gcnew TCLightTimestamp(%RcvTimeIsa2);
									return resTemp;

								case PCI_1CH:
									resTemp = (CANResult)PCAN_PCI::ReadEx(MsgPci, RcvTimePci);
									Msg = gcnew TCLightMsg(%MsgPci);
									RcvTime = gcnew TCLightTimestamp(%RcvTimePci);
									return resTemp;

								case PCI_2CH:
									resTemp = (CANResult)PCAN_2PCI::ReadEx(MsgPci2, RcvTimePci2);
									Msg = gcnew TCLightMsg(%MsgPci2);
									RcvTime = gcnew TCLightTimestamp(%RcvTimePci2);
									return resTemp;

								case PCC_1CH:
									resTemp = (CANResult)PCAN_PCC::ReadEx(MsgPcc, RcvTimePcc);
									Msg = gcnew TCLightMsg(%MsgPcc);
									RcvTime = gcnew TCLightTimestamp(%RcvTimePcc);
									return resTemp;

								case PCC_2CH:
									resTemp = (CANResult)PCAN_2PCC::ReadEx(MsgPcc2, RcvTimePcc2);
									Msg = gcnew TCLightMsg(%MsgPcc2);
									RcvTime = gcnew TCLightTimestamp(%RcvTimePcc2);
									return resTemp;

								case USB_1CH:
									resTemp = (CANResult)PCAN_USB::ReadEx(MsgUsb, RcvTimeUsb);
									Msg = gcnew TCLightMsg(%MsgUsb);
									RcvTime = gcnew TCLightTimestamp(%RcvTimeUsb);
									return resTemp;

								case USB_2CH:
									resTemp = (CANResult)PCAN_2USB::ReadEx(MsgUsb2, RcvTimeUsb2);
									Msg = gcnew TCLightMsg(%MsgUsb2);
									RcvTime = gcnew TCLightTimestamp(%RcvTimeUsb2);
									return resTemp;

								case DNP:
									resTemp = (CANResult)PCAN_DNP::ReadEx(MsgDnp, RcvTimeDnp);
									Msg = gcnew TCLightMsg(%MsgDnp);
									RcvTime = gcnew TCLightTimestamp(%RcvTimeDnp);
									return resTemp;

								case DNG:
									resTemp = (CANResult)PCAN_DNG::ReadEx(MsgDng, RcvTimeDng);
									Msg = gcnew TCLightMsg(%MsgDng);
									RcvTime = gcnew TCLightTimestamp(%RcvTimeDng);
									return resTemp;

								// Hardware is not valid for this function
								//
								default:
									return ERR_ILLHW;
							}
						}
						catch(EntryPointNotFoundException^ Ex)
						{
							// Function is not available in the loaded Dll
							//
							System::Windows::Forms::MessageBox::Show("Error: Wrong Version. \"" + Ex->Message + "\"");
							return ERR_NO_DLL;
						}
						catch(Exception^ Ex)
						{
							// Error: Dll does not exists or the function is not available
							//
							System::Windows::Forms::MessageBox::Show("Error: \"" + Ex->Message + "\"");
							return ERR_NO_DLL;
						}
					}

					/// <summary>
					/// PCANLight VersionInfo function
					/// This function get the Version and copyright of the hardware as text 
					/// (max. 255 characters)
					/// </summary>
					/// <param name="HWType">Which hardware should be asked for its Version information</param>
					/// <param name="strInfo">String variable to return the hardware information</param>
					/// <returns>A CANResult value - Error/status of the hardware after execute the function</returns>
					static CANResult VersionInfo(HardwareType HWType, String^ %strInfo)
					{
						StringBuilder^ stbTemp;
						CANResult resTemp;

						try
						{
							stbTemp = gcnew StringBuilder(256);
							switch(HWType)
							{
								case ISA_1CH:
									resTemp = (CANResult)PCAN_ISA::VersionInfo(stbTemp);
									break;

								case ISA_2CH:
									resTemp = (CANResult)PCAN_2ISA::VersionInfo(stbTemp);
									break;

								case PCI_1CH:
									resTemp =  (CANResult)PCAN_PCI::VersionInfo(stbTemp);
									break;

								case PCI_2CH:
									resTemp =  (CANResult)PCAN_2PCI::VersionInfo(stbTemp);
									break;

								case PCC_1CH:
									resTemp =  (CANResult)PCAN_PCC::VersionInfo(stbTemp);
									break;

								case PCC_2CH:
									resTemp =  (CANResult)PCAN_2PCC::VersionInfo(stbTemp);
									break;

								case USB_1CH:
									resTemp =  (CANResult)PCAN_USB::VersionInfo(stbTemp);
									break;

								case USB_2CH:
									resTemp =  (CANResult)PCAN_2USB::VersionInfo(stbTemp);
									break;

								case DNP:
									resTemp =  (CANResult)PCAN_DNP::VersionInfo(stbTemp);
									break;

								case DNG:
									resTemp =  (CANResult)PCAN_DNG::VersionInfo(stbTemp);
									break;

								// Hardware is not valid for this function
								//
								default:
									stbTemp = gcnew StringBuilder("");
									resTemp =  ERR_ILLHW;
									break;
							}
							strInfo = stbTemp->ToString();
							return resTemp;
						}
						catch(Exception^ Ex)
						{
							// Error: Dll does not exists or the function is not available
							//
							System::Windows::Forms::MessageBox::Show("Error: \"" + Ex->Message + "\"");
							strInfo = "";
							return ERR_NO_DLL;
						}
					}
					/// <summary>
					/// PCANLight DllVersionInfo function
					/// This function get the Version information of the used PCAN-Light DLL. (max. 255 characters)
					/// </summary>
					/// <param name="strInfo">String buffer to return the DLL information</param>
					/// <returns>A CANResult value - Error/status of the hardware after execute the function</returns>
					/// <exception>Throws a EntryPointNotFoundException if function isn't available in loaded DLL</exception>
					static CANResult DllVersionInfo(HardwareType HWType, String^ %strInfo)
					{
						StringBuilder^ stbTemp;
						CANResult resTemp;

						try
						{
							strInfo = "";
							stbTemp = gcnew StringBuilder(256);
							switch(HWType)
							{
								case ISA_1CH:
									resTemp = (CANResult)PCAN_ISA::DLLVersionInfo(stbTemp);
									break;

								case ISA_2CH:
									resTemp = (CANResult)PCAN_2ISA::DLLVersionInfo(stbTemp);
									break;

								case PCI_1CH:
									resTemp =  (CANResult)PCAN_PCI::DLLVersionInfo(stbTemp);
									break;

								case PCI_2CH:
									resTemp =  (CANResult)PCAN_2PCI::DLLVersionInfo(stbTemp);
									break;

								case PCC_1CH:
									resTemp =  (CANResult)PCAN_PCC::DLLVersionInfo(stbTemp);
									break;

								case PCC_2CH:
									resTemp =  (CANResult)PCAN_2PCC::DLLVersionInfo(stbTemp);
									break;

								case USB_1CH:
									resTemp =  (CANResult)PCAN_USB::DLLVersionInfo(stbTemp);
									break;

								case USB_2CH:
									resTemp =  (CANResult)PCAN_2USB::DLLVersionInfo(stbTemp);
									break;

								case DNP:
									resTemp =  (CANResult)PCAN_DNP::DLLVersionInfo(stbTemp);
									break;

								case DNG:
									resTemp =  (CANResult)PCAN_DNG::DLLVersionInfo(stbTemp);
									break;

								// Hardware is not valid for this function
								//
								default:
									stbTemp = gcnew StringBuilder("");
									resTemp =  ERR_ILLHW;
									break;
							}
							strInfo = stbTemp->ToString();
							return resTemp;
						}
						catch(EntryPointNotFoundException^ Ex)
						{
							// Function is not available in the loaded Dll
							//
							System::Windows::Forms::MessageBox::Show("Error: Wrong Version. \"" + Ex->Message + "\"");
							return ERR_NO_DLL;
						}
						catch(Exception^ Ex)
						{
							// Error: Dll does not exists or the function is not available
							//
							System::Windows::Forms::MessageBox::Show("Error: \"" + Ex->Message + "\"");
							return ERR_NO_DLL;
						}
					}	

					/// <summary>
					/// PCANLight ResetClient function
					/// This function delete the both queues (Transmit,Receive) of the CAN Controller 
					/// using a RESET
					/// </summary>
					/// <param name="HWType">Hardware to reset</param>
					/// <returns>A CANResult value - Error/status of the hardware after execute the function</returns>
					static CANResult ResetClient(HardwareType HWType)
					{
						try
						{
							switch(HWType)
							{
								case ISA_1CH:
									return (CANResult)PCAN_ISA::ResetClient();

								case ISA_2CH:
									return (CANResult)PCAN_2ISA::ResetClient();

								case PCI_1CH:
									return (CANResult)PCAN_PCI::ResetClient();

								case PCI_2CH:
									return (CANResult)PCAN_2PCI::ResetClient();

								case PCC_1CH:
									return (CANResult)PCAN_PCC::ResetClient();

								case PCC_2CH:
									return (CANResult)PCAN_2PCC::ResetClient();

								case USB_1CH:
									return (CANResult)PCAN_USB::ResetClient();

								case USB_2CH:
									return (CANResult)PCAN_2USB::ResetClient();

								case DNP:
									return (CANResult)PCAN_DNP::ResetClient();

								case DNG:
									return (CANResult)PCAN_DNG::ResetClient();

								// Hardware is not valid for this function
								//
								default:
									return ERR_ILLHW;
							}
						}
						catch(Exception^ Ex)
						{
							// Error: Dll does not exists or the function is not available
							//
							System::Windows::Forms::MessageBox::Show("Error: \"" + Ex->Message + "\"");
							return ERR_NO_DLL;
						}
					}

					/// <summary>
					/// PCANLigth MsgFilter function
					/// This function set the receive message filter of the CAN Controller.
					/// REMARK:
					///		- A quick register of all messages is possible using the parameters From and To as 0
					///		- Every call of this function maybe cause an extention of the receive filter of the 
					///		  CAN controller, which one can go briefly to RESET
					///		- New in Ver 2.x:
					///			* Standard frames will be put it down in the acc_mask/code as Bits 28..13
					///			* Hardware driver for 82C200 must to be moved to Bits 10..0 again!
					///	WARNING: 
					///		It is not guaranteed to receive ONLY the registered messages.
					/// </summary>
					/// <param name="HWType">Hardware which applay the filter to</param>
					/// <param name="From">First/Start Message ID - It muss be smaller than the "To" parameter</param>
					/// <param name="To">Last/Finish Message ID - It muss be bigger than the "From" parameter</param>
					/// <param name="MsgType">Kind of Frame - Standard or Extended</param>
					/// <returns>A CANResult value - Error/status of the hardware after execute the function</returns>
					static CANResult MsgFilter(HardwareType HWType,unsigned int From, unsigned int To, MsgTypes MsgType)
					{
						try
						{
							switch(HWType)
							{
								case ISA_1CH:
									return (CANResult)PCAN_ISA::MsgFilter(From,To,MsgType);

								case ISA_2CH:
									return (CANResult)PCAN_2ISA::MsgFilter(From,To,MsgType);

								case PCI_1CH:
									return (CANResult)PCAN_PCI::MsgFilter(From,To,MsgType);

								case PCI_2CH:
									return (CANResult)PCAN_2PCI::MsgFilter(From,To,MsgType);

								case PCC_1CH:
									return (CANResult)PCAN_PCC::MsgFilter(From,To,MsgType);

								case PCC_2CH:
									return (CANResult)PCAN_2PCC::MsgFilter(From,To,MsgType);

								case USB_1CH:
									return (CANResult)PCAN_USB::MsgFilter(From,To,MsgType);

								case USB_2CH:
									return (CANResult)PCAN_2USB::MsgFilter(From,To,MsgType);

								case DNP:
									return (CANResult)PCAN_DNP::MsgFilter(From,To,MsgType);

								case DNG:
									return (CANResult)PCAN_DNG::MsgFilter(From,To,MsgType);

								// Hardware is not valid for this function
								//
								default:
									return ERR_ILLHW;
							}
						}
						catch(Exception^ Ex)
						{
							// Error: Dll does not exists or the function is not available
							//
							System::Windows::Forms::MessageBox::Show("Error: \"" + Ex->Message + "\"");
							return ERR_NO_DLL;
						}
					}

					/// <summary>
					/// PCANLigth ResetFilter function
					/// This function close completely the Message Filter of the Hardware.
					/// They will be no more messages received.
					/// </summary>
					/// <param name="HWType">Hardware to reset its filter</param>
					/// <returns>A CANResult value - Error/status of the hardware after execute the function</returns>
					static CANResult ResetFilter(HardwareType HWType)
					{
						try
						{
							switch(HWType)
							{
								case ISA_1CH:
									return (CANResult)PCAN_ISA::ResetFilter();

								case ISA_2CH:
									return (CANResult)PCAN_2ISA::ResetFilter();

								case PCI_1CH:
									return (CANResult)PCAN_PCI::ResetFilter();

								case PCI_2CH:
									return (CANResult)PCAN_2PCI::ResetFilter();

								case PCC_1CH:
									return (CANResult)PCAN_PCC::ResetFilter();

								case PCC_2CH:
									return (CANResult)PCAN_2PCC::ResetFilter();

								case USB_1CH:
									return (CANResult)PCAN_USB::ResetFilter();

								case USB_2CH:
									return (CANResult)PCAN_2USB::ResetFilter();

								case DNP:
									return (CANResult)PCAN_DNP::ResetFilter();

								case DNG:
									return (CANResult)PCAN_DNG::ResetFilter();

								// Hardware is not valid for this function
								//
								default:
									return ERR_ILLHW;
							}
						}
						catch(Exception^ Ex)
						{
							// Error: Dll does not exists or the function is not available
							//
							System::Windows::Forms::MessageBox::Show("Error: \"" + Ex->Message + "\"");
							return ERR_NO_DLL;
						}
					}

					/// <summary>
					/// PCANLight SetUSBDeviceNr function 
					/// This function set an identification number to the USB CAN hardware 
					/// </summary>
					/// <param name="HWType">Hardware to set its Device Number</param>
					/// <param name="DeviceNumber">Value to be set as Device Number</param>
					/// <returns>A CANResult value - Error/status of the hardware after execute the function</returns>
					static CANResult SetUSBDeviceNr(HardwareType HWType, unsigned int DeviceNumber)
					{
						try
						{
							switch(HWType)
							{
								case USB_1CH:
									return (CANResult)PCAN_USB::SetUSBDeviceNr(DeviceNumber);
								case USB_2CH:
									return (CANResult)PCAN_2USB::SetUSBDeviceNr(DeviceNumber);
								default:
									return ERR_ILLHW;
							}
						}
						catch(Exception^ Ex)
						{
							// Error: Dll does not exists or the function is not available
							//
							System::Windows::Forms::MessageBox::Show("Error: \"" + Ex->Message + "\"");
							return ERR_NO_DLL;
						}
					}

					/// <summary>
					/// PCANLight GetUSBDeviceNr function
					/// This function read the device number of a USB CAN Hardware
					/// </summary>
					/// <param name="HWType">Hardware to get the Device Number</param>
					/// <param name="DeviceNumber">Variable to return the Device Number value</param>
					/// <returns>A CANResult value - Error/status of the hardware after execute the function</returns>
					static CANResult GetUSBDeviceNr(HardwareType HWType, unsigned int %DeviceNumber)
					{
						try
						{
							switch(HWType)
							{
								case USB_1CH:
									return (CANResult)PCAN_USB::GetUSBDeviceNr(DeviceNumber);
								case USB_2CH:
									return (CANResult)PCAN_2USB::GetUSBDeviceNr(DeviceNumber);
								default:
									return ERR_ILLHW;
							}
						}
						catch(Exception^ Ex)
						{
							// Error: Dll does not exists or the function is not available
							//
							DeviceNumber = -1;
							System::Windows::Forms::MessageBox::Show("Error: \"" + Ex->Message + "\"");
							return ERR_NO_DLL;
						}
					}

					/// <summary>
					/// PCANLight SetRcvEvent function
					/// Sets the handle of the Receive-Event.
					/// </summary>
					/// <param name="hEvent">Handle to be set</param>CANResult
					/// <returns>A CANResult value - Error/status of the hardware after execute the function</returns>
					/// <exception>Throws a EntryPointNotFoundException if function isn't available in loaded DLL</exception>
					static CANResult SetRcvEvent(HardwareType HWType, System::Threading::EventWaitHandle^ EventHandle)
					{
						IntPtr hHandle;

						try
						{
							// If the EventHandle parameter is null, a value of IntPtr::Zero is set in order to clear 
							// the Event on the driver. Otherwise we get the internal Handle value representing the
							// Receive-Event
							//
							hHandle = (EventHandle == nullptr) ? IntPtr::Zero : EventHandle->SafeWaitHandle->DangerousGetHandle();

							switch(HWType)
							{
								case ISA_1CH:
									return (CANResult)PCAN_ISA::SetRcvEvent(hHandle);

								case ISA_2CH:
									return (CANResult)PCAN_2ISA::SetRcvEvent(hHandle);

								case PCI_1CH:
									return (CANResult)PCAN_PCI::SetRcvEvent(hHandle);

								case PCI_2CH:
									return (CANResult)PCAN_2PCI::SetRcvEvent(hHandle);

								case PCC_1CH:
									return (CANResult)PCAN_PCC::SetRcvEvent(hHandle);

								case PCC_2CH:
									return (CANResult)PCAN_2PCC::SetRcvEvent(hHandle);

								case USB_1CH:
									return (CANResult)PCAN_USB::SetRcvEvent(hHandle);

								case USB_2CH:
									return (CANResult)PCAN_2USB::SetRcvEvent(hHandle);

								case DNP:
									return (CANResult)PCAN_DNP::SetRcvEvent(hHandle);

								case DNG:
									return (CANResult)PCAN_DNG::SetRcvEvent(hHandle);

								// Hardware is not valid for this function
								//
								default:
									return ERR_ILLHW;
							}
						}
						catch(EntryPointNotFoundException^ Ex)
						{
							// Function is not available in the loaded Dll
							//
							System::Windows::Forms::MessageBox::Show("Error: Wrong Version. \"" + Ex->Message + "\"");
							return ERR_NO_DLL;
						}
						catch(Exception^ Ex)
						{
							// Error: Dll does not exists or the function is not available
							//
							System::Windows::Forms::MessageBox::Show("Error: \"" + Ex->Message + "\"");
							return ERR_NO_DLL;
						}
					}
					#pragma endregion
					#pragma endregion
				};
			#pragma endregion
		}
	}
}
