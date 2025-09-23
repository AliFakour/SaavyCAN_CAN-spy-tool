'//////////////////////////////////////////////////////////////////////////////
'  PCAN-Light
'  PCAN-DNG.vb
'
'  Version 2.x
'
'  ~~~~~~~~~~
'
'  Definition of the PCAN-Light API. 
'  The Driver support a Hardware and a Software who want to communicate with CAN-busses 
'
'  ~~~~~~~~~~~~
'
'  PCAN-Light -API
'
'  ~~~~~~~~~~~~
'
'  - Init(ByVal BTR0BTR1 As Short, ByVal CANMsgtype As Integer, ByVal CANHwType As Integer, ByVal IO_Port As Integer, ByVal Interrupt As Short)
'  - Close()  
'  - Status() 
'  - Write(ByRef msg As TPCANMsg) 
'  - Read(ByRef msg As TPCANMsg)  
'  - ReadEx(ByRef msg As TPCANMsg, ByRef timestamp As TPCANTimestamp)   
'  - VersionInfo(ByVal buffer As StringBuilder) 
'  - DLLVersionInfo(ByVal buffer As StringBuilder)
'  - SpecialFunktion(ByVal distributorcode As Integer, ByVal codenumber As Integer)
'  - ResetClient()
'  - MsgFilter(ByVal FromID As UInt32, ByVal ToID As UInt32, ByVal Type As Integer)
'  - ResetFilter()
'  - SetRcvEvent(ByVal hEvent As IntPtr)
'
'  ------------------------------------------------------------------
'  Author : Hoppe, Wilhelm
'  Modified By: Wagner (23.09.2009)
'
'  Language: Visual Basic .Net
'  ------------------------------------------------------------------
'
'  Copyright (C) 1999-2009  PEAK-System Technik GmbH, Darmstadt
'
Imports System
Imports System.Text
Imports System.Runtime.InteropServices

Namespace Peak.Can.Light
    Public Class PCAN_DNG

        ' HardwareType 
        ' Only SJA 1000 Dongles are supported  !!
        Public Const HW_DONGLE_SJA As Integer = 5
        Public Const HW_DONGLE_SJA_EPP As Integer = 6

#Region "Frames, ID's und CAN message types"

        ' Constants definitions - Frame Type
        Public Const CAN_INIT_TYPE_EX As Integer = 1 ' Extended Frames
        Public Const CAN_INIT_TYPE_ST As Integer = 0 ' Standard Frames

        ' Constants definitions - ID
        Public Const CAN_MAX_STANDARD_ID As Integer = &H7FF
        Public Const CAN_MAX_EXTENDED_ID As Integer = &H1FFFFFFF

        ' Constants definitions  - CAN message types
        Public Const MSGTYPE_STANDARD As Integer = &H0  ' Standard Frame (11 bit ID)() As 0x00
        Public Const MSGTYPE_RTR As Integer = &H1       ' 1, if Remote Request frame 
        Public Const MSGTYPE_EXTENDED As Integer = &H2  ' 1, if Extended Data frame (CAN 2.0B, 29-bit ID)
        Public Const MSGTYPE_STATUS As Integer = &H80   ' 1, if Status information
#End Region

#Region "Baudrate Codes"
        ' BTR0BTR1 register
        ' Baudrate code = register value BTR0/BTR1
        Public Const CAN_BAUD_1M As Integer = &H14      '   1 MBit/sec
        Public Const CAN_BAUD_500K As Integer = &H1C    ' 500 KBit/sec
        Public Const CAN_BAUD_250K As Integer = &H11C   ' 250 KBit/sec
        Public Const CAN_BAUD_125K As Integer = &H31C   ' 125 KBit/sec
        Public Const CAN_BAUD_100K As Integer = &H432F  ' 100 KBit/sec 
        Public Const CAN_BAUD_50K As Integer = &H472F   '  50 KBit/sec
        Public Const CAN_BAUD_20K As Integer = &H532F   '  20 KBit/sec
        Public Const CAN_BAUD_10K As Integer = &H672F   '  10 KBit/sec
        Public Const CAN_BAUD_5K As Integer = &H7F7F    '   5 KBit/sec

        ' You can define your own Baudrate for the BTROBTR1 register.
        ' Take a look at www.peak-system.com for our software BAUDTOOL to
        ' calculate the BTROBTR1 register for every baudrate and sample point.
#End Region

#Region "Error Codes"
        ' Error codes
        Public Const ERR_OK As Integer = &H0           ' No error
        Public Const ERR_XMTFULL As Integer = &H1      ' Transmit buffer in CAN controller is full
        Public Const ERR_OVERRUN As Integer = &H2      ' CAN controller was read too late
        Public Const ERR_BUSLIGHT As Integer = &H4     ' Bus error: an error counter reached the 'light' limit
        Public Const ERR_BUSHEAVY As Integer = &H8     ' Bus error: an error counter reached the 'heavy' limit
        Public Const ERR_BUSOFF As Integer = &H10      ' Bus error: the CAN controller is in bus-off state
        Public Const ERR_QRCVEMPTY As Integer = &H20   ' Receive queue is empty
        Public Const ERR_QOVERRUN As Integer = &H40    ' Receive queue was read too late
        Public Const ERR_QXMTFULL As Integer = &H80    ' Transmit queue ist full
        Public Const ERR_REGTEST As Integer = &H100    ' Test of the CAN controller hardware registers failed (no hardware found)
        Public Const ERR_NOVXD As Integer = &H200      ' Driver not loaded
        Public Const ERR_NODRIVER As Integer = &H200   ' Driver not loaded
        Public Const ERRMASK_ILLHANDLE As Integer = &H1C00  ' Mask for all handle errors
        Public Const ERR_HWINUSE As Integer = &H400    ' Hardware already in use by a Net
        Public Const ERR_NETINUSE As Integer = &H800   ' a Client is already connected to the Net
        Public Const ERR_ILLHW As Integer = &H1400     ' Hardware handle is invalid
        Public Const ERR_ILLNET As Integer = &H1800    ' Net handle is invalid
        Public Const ERR_ILLCLIENT As Integer = &H1C00 ' Client handle is invalid
        Public Const ERR_RESOURCE As Integer = &H2000  ' Resource (FIFO, Client, timeout) cannot be created
        Public Const ERR_ILLPARAMTYPE As Integer = &H4000 ' Invalid parameter
        Public Const ERR_ILLPARAMVAL As Integer = &H8000  ' Invalid parameter value
        Public Const ERR_UNKNOWN As Integer = &H10000  ' Unknown error
        Public Const ERR_ANYBUSERR As Integer = (ERR_BUSLIGHT Or ERR_BUSHEAVY Or ERR_BUSOFF)
#End Region

#Region "Structures"
        ' CAN message
        '
        <StructLayout(LayoutKind.Sequential, Pack:=1)> Public Structure TPCANMsg
            Public ID As Integer   ' 11/29 bit identifier
            Public MSGTYPE As Byte ' Bits from MSGTYPE_*
            Public LEN As Byte     ' Data Length Code of the Msg (0..8)
            <MarshalAs(UnmanagedType.ByValArray, sizeconst:=8)> _
            Public DATA As Byte()  ' Data 0 .. 7
        End Structure

        ' Timestamp of a receive/transmit event
        ' Total microseconds = micros + 1000 * millis + 0xFFFFFFFF * 1000 * millis_overflow
        '
        <StructLayout(LayoutKind.Sequential, Pack:=1)> Public Structure TPCANTimestamp
            Public millis As Integer        ' Base-value: milliseconds: 0.. 2^32-1
            Public millis_overflow As Short ' Roll-arounds of millis
            Public micros As Short          ' Microseconds: 0..999
        End Structure
#End Region

        '//////////////////////////////////////////////////////////////////////////////
        '  Init()
        '  This function make the following:
        '		- Activate a Hardware
        '		- Make a Register Test of 82C200/SJA1000
        '		- Allocate a Send buffer and a Hardware handle
        '		- Programs the configuration of the transmit/receive driver
        '		- Set the Baudrate register
        '		- Set the Controller in RESET condition	
        '		
        '  If CANMsgType=0  ---> ID 11Bit
        '  If CANMsgType=1  ---> ID 11/29Bit 
        '
        '  CANHw Type:  (Only new SJA Dongle !!!)
        '	HW_ISA             1
        '	HW_DONGLE_SJA      5
        '	HW_DONGLE_SJA_EPP  6
        '	HW_DONGLE_PRO      7
        '	HW_DONGLE_PRO_EPP  8
        '	HW_ISA_SJA         9
        '	HW_PCI		       10
        '
        '  Possible Errors: NOVXD ILLHW REGTEST RESOURCE
        '
        <DllImport("PCAN_DNG.dll", EntryPoint:="CAN_Init")> _
        Public Shared Function init( _
            ByVal BTR0BTR1 As Short, _
            ByVal CANMsgtype As Integer, _
            ByVal CANHwType As Integer, _
            ByVal IO_Port As Integer, _
            ByVal Interrupt As Short) As Integer
        End Function

        '/////////////////////////////////////////////////////////////////////////////
        '  Close()
        '  This function terminate and release the configured hardware and all 
        '  allocated resources 
        '
        '  Possible Errors: NOVXD
        '
        <DllImport("PCAN_DNG.dll", EntryPoint:="CAN_Close")> _
        Public Shared Function Close() As Integer
        End Function

        '/////////////////////////////////////////////////////////////////////////////
        '  Status()
        '  This function request the current status of the hardware (b.e. BUS-OFF)
        '
        '  Possible Errors: NOVXD BUSOFF BUSHEAVY OVERRUN
        '
        <DllImport("PCAN_DNG.dll", EntryPoint:="CAN_Status")> _
        Public Shared Function Status() As Integer
        End Function

        '//////////////////////////////////////////////////////////////////////////////
        '  Write()
        '  This function Place a CAN message into the Transmit Queue of the CAN Hardware
        '
        '  Possible Errors: NOVXD RESOURCE BUSOFF QXMTFULL
        '
        <DllImport("PCAN_DNG.dll", EntryPoint:="CAN_Write")> _
        Public Shared Function Write(ByRef msg As TPCANMsg) As Integer
        End Function

        '//////////////////////////////////////////////////////////////////////////////
        '  Read()
        '  This function get the next message or the next error from the Receive Queue of 
        '  the CAN Hardware.  
        '  REMARK:
        '		- Check always the type of the received Message (MSGTYPE_STANDARD,MSGTYPE_RTR,
        '		  MSGTYPE_EXTENDED,MSGTYPE_STATUS)
        '		- The function will return ERR_OK always that you receive a CAN message successfully 
        '		  although if the messages is a MSGTYPE_STATUS message.  
        '		- When a MSGTYPE_STATUS mesasge is got, the ID and Length information of the message 
        '		  will be treated as indefined values. Actually information of the received message
        '		  should be interpreted using the first 4 data bytes as follow:
        '			*	Data0	Data1	Data2	Data3	Kind of Error
        '				0x00	0x00	0x00	0x02	CAN_ERR_OVERRUN		0x0002	CAN Controller was read to late
        '				0x00	0x00	0x00	0x04	CAN_ERR_BUSLIGHT	0x0004  Bus Error: An error counter limit reached (96)
        '				0x00	0x00	0x00	0x08	CAN_ERR_BUSHEAVY	0x0008	Bus Error: An error counter limit reached (128)
        '				0x00	0x00	0x00	0x10	CAN_ERR_BUSOFF		0x0010	Bus Error: Can Controller went "Bus-Off"
        '		- If a CAN_ERR_BUSOFF status message is received, the CAN Controller must to be 
        '		  initialized again using the Init() function.  Otherwise, will be not possible 
        '		  to send/receive more messages. 
        '		- The message will be written to 'msgbuff'.
        '
        '  Possible Errors: NOVXD  QRCVEMPTY
        '
        <DllImport("PCAN_DNG.dll", EnTryPoint:="CAN_Read")> _
        Public Shared Function Read(ByRef msg As TPCANMsg) As Integer
        End Function

        '//////////////////////////////////////////////////////////////////////////////
        '  ReadEx()
        '  This function get the next message or the next error from the Receive Queue of 
        '  the CAN Hardware and the time when the message arrived.   
        '  REMARK:
        '		- Check always the type of the received Message (MSGTYPE_STANDARD,MSGTYPE_RTR,
        '		  MSGTYPE_EXTENDED,MSGTYPE_STATUS)
        '		- The function will return ERR_OK always that you receive a CAN message successfully 
        '		  although if the messages is a MSGTYPE_STATUS message.  
        '		- When a MSGTYPE_STATUS mesasge is got, the ID and Length information of the message 
        '		  will be treated as indefined values. Actually information of the received message
        '		  should be interpreted using the first 4 data bytes as follow:
        '			*	Data0	Data1	Data2	Data3	Kind of Error
        '				0x00	0x00	0x00	0x02	CAN_ERR_OVERRUN		0x0002	CAN Controller was read to late
        '				0x00	0x00	0x00	0x04	CAN_ERR_BUSLIGHT	0x0004  Bus Error: An error counter limit reached (96)
        '				0x00	0x00	0x00	0x08	CAN_ERR_BUSHEAVY	0x0008	Bus Error: An error counter limit reached (128)
        '				0x00	0x00	0x00	0x10	CAN_ERR_BUSOFF		0x0010	Bus Error: Can Controller went "Bus-Off"
        '		- If a CAN_ERR_BUSOFF status message is received, the CAN Controller must to be 
        '		  initialized again using the Init() function.  Otherwise, will be not possible 
        '		  to send/receive more messages. 
        '		- The message will be written to 'msgbuff'.
        '       Since Version 2.x the Ext. Version is available - new Parameter:
        '		-  Receive timestamp
        '
        '  Possible Errors: NOVXD  QRCVEMPTY
        '
        <DllImport("PCAN_DNG.dll", EnTryPoint:="CAN_ReadEx")> _
        Public Shared Function ReadEx(ByRef msg As TPCANMsg, ByRef timestamp As TPCANTimestamp) As Integer
        End Function

        '//////////////////////////////////////////////////////////////////////////////
        '  VersionInfo()
        '  This function get the Version and copyright of the hardware as text 
        '  (max. 255 characters)
        '
        '  Possible Errors:  NOVXD
        '
        <DllImport("PCAN_DNG.dll", EntryPoint:="CAN_VersionInfo")> _
        Public Shared Function VersionInfo(ByVal buffer As StringBuilder) As Integer
        End Function

        '//////////////////////////////////////////////////////////////////////////////
        '  DLLVersionInfo()
        '  This function is used to get the Version and copyright of the 
        '  DLL as text (max. 255 characters)
        '
        '  Possible Errors: -1 for NULL-Pointer parameters :-)
        '
        <DllImport("PCAN_DNG.dll", EntryPoint:="CAN_DLLVersionInfo")> _
        Public Shared Function DLLVersionInfo(ByVal buffer As StringBuilder) As Integer
        End Function

        '//////////////////////////////////////////////////////////////////////////////
        '  SpecialFunktion()
        '  This function is an special function to be used "ONLY" for distributors
        '  Return: 1 - the given parameters and the parameters in the hardware agree 
        '   	   0 - otherwise
        '
        '  Possible Errors:  NOVXD
        '
        <DllImport("PCAN_DNG.dll", EntryPoint:="CAN_SpecialFunktion")> _
        Public Shared Function SpecialFunktion(ByVal distributorcode As Integer, ByVal codenumber As Integer) As Integer
        End Function

        '/////////////////////////////////////////////////////////////////////////////
        '  ResetClient()
        '  This function delete the both queues (Transmit,Receive) of the CAN Controller 
        '  using a RESET
        '
        '  Possible Errors: ERR_ILLCLIENT ERR_NOVXD
        ' 
        <DllImport("PCAN_DNG.dll", EntryPoint:="CAN_ResetClient")> _
        Public Shared Function ResetClient() As Integer
        End Function

        '//////////////////////////////////////////////////////////////////////////////
        '  MsgFilter(FromID, ToID, int Type)
        '  This function set the receive message filter of the CAN Controller.
        '  REMARK:
        '		- A quick register of all messages is possible using the parameters FromID and ToID = 0
        '		- Every call of this function maybe cause an extention of the receive filter of the 
        '		  CAN controller, which one can go briefly to RESET
        '		- New in Ver 2.x:
        '			* Standard frames will be put it down in the acc_mask/code as Bits 28..13
        '			* Hardware driver for 82C200 must to be moved to Bits 10..0 again!
        '	WARNING: 
        '		It is not guaranteed to receive ONLY the registered messages.
        '
        '  Possible Errors: NOVXD ILLCLIENT ILLNET REGTEST
        '
        <DllImport("PCAN_DNG.dll", EntryPoint:="CAN_MsgFilter")> _
        Public Shared Function MsgFilter(ByVal FromID As Integer, ByVal ToID As Integer, ByVal Type As Integer) As Integer
        End Function

        '//////////////////////////////////////////////////////////////////////////////
        '  ResetFilter()
        '  This function close completely the Message Filter of the Hardware.
        '  They will be no more messages received.
        '
        '  Possible Errors: NOVXD
        '
        <DllImport("PCAN_DNG.dll", EntryPoint:="CAN_ResetFilter")> _
        Public Shared Function ResetFilter() As Integer
        End Function

        '//////////////////////////////////////////////////////////////////////////////
        '  SetRcvEvent()
        '  This function is used to set the Event for the Event Handler
        '
        '  Possible Errors: ILLCLIENT ILLPARAMTYPE ILLPARAMVAL NOVXD
        '
        <DllImport("PCAN_DNG.dll", EntryPoint:="CAN_SetRcvEvent")> _
        Public Shared Function SetRcvEvent(ByVal hEvent As IntPtr) As Integer
        End Function
    End Class
End Namespace
