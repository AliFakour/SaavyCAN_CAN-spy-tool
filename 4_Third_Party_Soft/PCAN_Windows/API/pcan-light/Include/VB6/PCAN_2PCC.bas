Attribute VB_Name = "PCAN_2PCC"
'//////////////////////////////////////////////////////////////////////////////
'  PCAN-Light
'  PCAN_2PCC.bas
'
'  Version 1.5
'
'  ~~~~~~~~~~
'
'  Basic Idea:
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
'  - Init(ByVal BTR0BTR1 As Integer, ByVal CANMsgtype As Long)
'  - Close()
'  - Status()
'  - Write(ByRef msg As TPCANMsg)
'  - Read(ByRef msg As TPCANMsg)
'  - VersionInfo(ByVal buffer As String)
'  - ResetClient()
'  - MsgFilter(ByVal FromID As Long, ByVal ToID As Long, ByVal Type As Long)
'  - ResetFilter()
'
'  ------------------------------------------------------------------
'  Author : Hoppe, Wilhelm
'  Modified By: Wagner (20.08.2008)
'
'  Language: Visual Basic 6.0
'  ------------------------------------------------------------------
'
'  Copyright (C) 1999-2008  PEAK-System Technik GmbH, Darmstadt
'

' Constants definitions - Frame Type
Public Const CAN_INIT_TYPE_EX As Long = &H1     ' Extended Frame
Public Const CAN_INIT_TYPE_ST As Long = &H0     ' Standart Frame


' Constants definitions - ID
Public Const CAN_MAX_STANDARD_ID As Long = &H7FF
Public Const CAN_MAX_EXTENDED_ID As Long = &H1FFFFFFF


' Constants definitions  - CAN message types
Public Const MSGTYPE_STANDARD As Long = &H0    ' Standard Frame (11 bit ID)() As 0x00
Public Const MSGTYPE_RTR As Long = &H1         ' 1, if Remote Request frame
Public Const MSGTYPE_EXTENDED As Long = &H2    ' 1, if Extended Data frame (CAN 2.0B, 29-bit ID)
Public Const MSGTYPE_STATUS As Long = &H80     ' 1, if Status information


' BTR0BTR1 register
' Baudrate code = register value BTR0/BTR1
Public Const CAN_BAUD_1M As Long = &H14        '   1 MBit / s
Public Const CAN_BAUD_500K As Long = &H1C      ' 500 kBit / s
Public Const CAN_BAUD_250K As Long = &H11C     ' 250 kBit / s
Public Const CAN_BAUD_125K As Long = &H31C     ' 125 kBit / s
Public Const CAN_BAUD_100K As Long = &H432F    ' 100 kBit / s
Public Const CAN_BAUD_50K As Long = &H472F     '  50 kBit / s
Public Const CAN_BAUD_20K As Long = &H532F     '  20 kBit / s
Public Const CAN_BAUD_10K As Long = &H672F     '  10 kBit / s
Public Const CAN_BAUD_5K As Long = &H7F7F      '   5 kBit / s

' You can define your own Baudrate for the BTROBTR1 register.
' Take a look at www.peak-system.com for our software BAUDTOOL to
' calculate the BTROBTR1 register for every baudrate and sample point.


' Error codes (bit code)
Public Const CAN_ERR_OK As Long = &H0           ' No error
Public Const CAN_ERR_XMTFULL As Long = &H1      ' Transmit buffer in CAN controller is full
Public Const CAN_ERR_OVERRUN As Long = &H2      ' CAN controller was read too late
Public Const CAN_ERR_BUSLIGHT As Long = &H4     ' Bus error: an error counter reached the 'light' limit
Public Const CAN_ERR_BUSHEAVY As Long = &H8     ' Bus error: an error counter reached the 'heavy' limit
Public Const CAN_ERR_BUSOFF As Long = &H10      ' Bus error: the CAN controller is in bus-off state
Public Const CAN_ERR_QRCVEMPTY As Long = &H20   ' Receive queue is empty
Public Const CAN_ERR_QOVERRUN As Long = &H40    ' Receive queue was read too late
Public Const CAN_ERR_QXMTFULL As Long = &H80    ' Transmit queue ist full
Public Const CAN_ERR_REGTEST As Long = &H100    ' Test of the CAN controller hardware registers failed (no hardware found)
Public Const CAN_ERR_NOVXD As Long = &H200      ' Driver not loaded
Public Const CAN_ERR_NODRIVER As Long = &H200   ' Driver not loaded
Public Const CAN_ERRMASK_ILLHANDLE As Long = &H1C00  ' Mask for all handle errors
Public Const CAN_ERR_HWINUSE As Long = &H400    ' Hardware already in use by a Net
Public Const CAN_ERR_NETINUSE As Long = &H800   ' a Client is already connected to the Net
Public Const CAN_ERR_ILLHW As Long = &H1400     ' Hardware handle is invalid
Public Const CAN_ERR_ILLNET As Long = &H1800    ' Net handle is invalid
Public Const CAN_ERR_ILLCLIENT As Long = &H1C00 ' Client handle is invalid
Public Const CAN_ERR_RESOURCE As Long = &H2000  ' Resource (FIFO, Client, timeout) cannot be created
Public Const CAN_ERR_ILLPARAMTYPE As Long = &H4000 ' Invalid parameter
Public Const CAN_ERR_ILLPARAMVAL As Long = &H8000  ' Invalid parameter value
Public Const CAN_ERR_UNKNOWN As Long = &H10000  ' Unknown error
Public Const CAN_ERR_ANYBUSERR = (CAN_ERR_BUSLIGHT Or CAN_ERR_BUSHEAVY Or CAN_ERR_BUSOFF)
' All further error conditions <> 0 please ask PEAK when required.......internal driver failure ........


' CAN message
Public Type TPCANMsg
    ID As Long          ' 11/29 bit identifier
    MsgType As Byte     ' Bits from MSGTYPE_*
    LEN As Byte         ' Data Length Code of the Msg (0..8)
    DATA(7) As Byte     ' Data 0 .. 7
End Type



'/////////////////////////////////////////////////////////////////////////////
'  Init()
'  This function make the following:
'   - Activate a Hardware
'   - Make a Register Test of 82C200/SJA1000
'   - Allocate a Send buffer and a Hardware handle
'   - Programs the configuration of the transmit/receive driver
'   - Set the Baudrate register
'   - Set the Controller in RESET condition
'
'  If CANMsgType=0  ---> ID 11Bit
'  If CANMsgType=1  ---> ID 11/29Bit
'
'  Possible Errors: NOVXD ILLHW REGTEST RESOURCE
'
Public Declare Function CAN2_Init Lib "pcan_2pcc" _
    (ByVal wBTR0BTR1 As Integer, _
    ByVal CANMsgType As Long) As Long



'/////////////////////////////////////////////////////////////////////////////
'  Close()
'  This function terminate and release the configured hardware and all
'  allocated resources
'
'  Possible Errors: NOVXD
'
Public Declare Function CAN2_Close Lib "pcan_2pcc" _
    () As Long



'/////////////////////////////////////////////////////////////////////////////
'  Status()
'  This function request the current status of the hardware (b.e. BUS-OFF)
'
'  Possible Errors: NOVXD BUSOFF BUSHEAVY OVERRUN
'
Public Declare Function CAN2_Status Lib "pcan_2pcc" _
    () As Long



'//////////////////////////////////////////////////////////////////////////////
'  Write()
'  This function Place a CAN message into the Transmit Queue of the CAN Hardware
'
'  Possible Errors: NOVXD RESOURCE BUSOFF QXMTFULL
'
Public Declare Function CAN2_Write Lib "pcan_2pcc" _
    (ByRef msg As TPCANMsg) As Long



'//////////////////////////////////////////////////////////////////////////////
'  Read()
'  This function get the next message or the next error from the Receive Queue of
'  the CAN Hardware.
'  REMARK:
'       - Check always the type of the received Message (MSGTYPE_STANDARD,MSGTYPE_RTR,
'         MSGTYPE_EXTENDED,MSGTYPE_STATUS)
'       - The function will return ERR_OK always that you receive a CAN message successfully
'         although if the messages is a MSGTYPE_STATUS message.
'       - When a MSGTYPE_STATUS mesasge is got, the ID and Length information of the message
'         will be treated as indefined values. Actually information of the received message
'         should be interpreted using the first 4 data bytes as follow:
'           *   Data0   Data1   Data2   Data3   Kind of Error
'               0x00    0x00    0x00    0x02    CAN_ERR_OVERRUN     0x0002  CAN Controller was read to late
'               0x00    0x00    0x00    0x04    CAN_ERR_BUSLIGHT    0x0004  Bus Error: An error counter limit reached (96)
'               0x00    0x00    0x00    0x08    CAN_ERR_BUSHEAVY    0x0008  Bus Error: An error counter limit reached (128)
'               0x00    0x00    0x00    0x10    CAN_ERR_BUSOFF      0x0010  Bus Error: Can Controller went "Bus-Off"
'       - If a CAN_ERR_BUSOFF status message is received, the CAN Controller must to be
'         initialized again using the Init() function.  Otherwise, will be not possible
'         to send/receive more messages.
'       - The message will be written to 'msgbuff'.
'
'  Possible Errors: NOVXD  QRCVEMPTY
'
Public Declare Function CAN2_Read Lib "pcan_2pcc" _
    (ByRef msg As TPCANMsg) As Long



'//////////////////////////////////////////////////////////////////////////////
'  VersionInfo()
'  This function get the Version and copyright of the hardware as text
'  (max. 255 characters)
'
'  Possible Errors:  NOVXD
'
Public Declare Function CAN2_VersionInfo Lib "pcan_2pcc" _
    (ByVal buffer As String) As Long



'/////////////////////////////////////////////////////////////////////////////
'  ResetClient()
'  This function delete the both queues (Transmit,Receive) of the CAN Controller
'  using a RESET
'
'  Possible Errors: ERR_ILLCLIENT ERR_NOVXD
'
Public Declare Function CAN2_ResetClient Lib "pcan_2pcc" _
    () As Long



'//////////////////////////////////////////////////////////////////////////////
'  MsgFilter(FromID, ToID, int Type)
'  This function set the receive message filter of the CAN Controller.
'  REMARK:
'       - A quick register of all messages is possible using the parameters FromID and ToID = 0
'       - Every call of this function maybe cause an extention of the receive filter of the
'         CAN controller, which one can go briefly to RESET
'       - New in Ver 2.x:
'           * Standard frames will be put it down in the acc_mask/code as Bits 28..13
'           * Hardware driver for 82C200 must to be moved to Bits 10..0 again!
'   WARNING:
'       It is not guaranteed to receive ONLY the registered messages.
'
'  Possible Errors: NOVXD ILLCLIENT ILLNET REGTEST
'
Public Declare Function CAN2_MsgFilter Lib "pcan_2pcc" _
    (ByVal FromID As Long, _
    ByVal ToID As Long, _
    ByVal MsgType As Long) As Long
         


'//////////////////////////////////////////////////////////////////////////////
'  ResetFilter()
'  This function close completely the Message Filter of the Hardware.
'  They will be no more messages received.
'
'  Possible Errors: NOVXD
'
Public Declare Function CAN2_ResetFilter Lib "pcan_2pcc" _
    () As Long
        
'//////////////////////////////////////////////////////////////////////////////
'  CAN2_DLLVersionInfo()
'  This function is used to get 
'  the Version and copyright of the DLL as text (max. 255 characters)
'
'  Possible Errors: -1 for NULL-Pointer parameters :-)
'
Public Declare Function CAN2_DLLVersionInfo Lib "pcan_2pcc" _
    (ByVal buffer As String) As Long
