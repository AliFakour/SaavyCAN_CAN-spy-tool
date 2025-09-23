'//////////////////////////////////////////////////////////////////////////////
'  Based on:
'  PCAN_ISA.vb
'  PCAN_2ISA.vb
'  PCAN_PCI.vb
'  PCAN_2PCI.vb
'  PCAN_PCC.vb
'  PCAN_2PCC.vb
'  PCAN_DNG.vb
'  PCAN_DNP.vb
'  PCAN_USB.vb
'  PCAN_2USB.vb
'
'  Version 2.0
'
'  ~~~~~~~~~~~~
'
'  Idea:
'
'  ~~~~~~~~~~
'
'  PCANLight is a namespace used to make the managing of the different PCAN Hardware using the 
'  PCANLight Dlls: pcan_isa,pcan_2isa,pcan_pci,pcan_2pci,pcan_pcc,pcan_2pcc,pcan_dng,pcan_dnp,
'  pcan_usb, pcan_2usb
'
'  In order  to offer  a simple  interface, some constant valuest were converted  to enumerate 
'  types.  The class CANLight  make use of all Dlls and gives  an unique interface for all the 
'  hardware types.  A TCLightMsg class is implemented too.  This class will  be used to make a 
'  bridge between the definition of the TCANMsg structure in every *.vb file.  In this way, in 
'  this high level,  will  exists  only  one  kind of CAN  message and  one occurrence of each 
'  PCANLIGHT function.
'
'  ~~~~~~~~~~~~
'
'  PCAN-Light -API
'
'  ~~~~~~~~~~~~
'
'   Init() (Two versions, for P&P and Non P&P)
'   Close() 
'   Status()
'   Write() 
'   Read()  
'   ReadEx()
'   VersionInfo() 
'   DllVersionInfo()
'   ResetClient()
'   MsgFilter()
'	ResetFilter()
'	SetUSBDeviceNr()
'   GetUSBDeviceNr()
'   SetRcvEvent()
'
'  ------------------------------------------------------------------
'
'  Author  : Keneth Wagner
'  Sprache: Visual Basic .Net
'  Last Modified: Wagner (23.09.2009)
'
'  ------------------------------------------------------------------
'  Copyright (C) 2006-2009  PEAK-System Technik GmbH, Darmstadt
'
Imports System
Imports System.Text

Namespace Peak.Can.Light
#Region "Types definition"
    ' Kind of Frame - Message Type
    '
    Public Enum FramesType As Integer
        INIT_TYPE_ST = &H0  ' Standart Frame 
        INIT_TYPE_EX = &H1  ' Extended Frame
    End Enum

    ' Maximal values for the ID of a CAN Message
    '
    Public Enum MaxIDValues As Integer
        MAX_STANDARD_ID = &H7FF
        MAX_EXTENDED_ID = &H1FFFFFFF
    End Enum

    ' Kind of CAN Message
    '    
    <Flags()> Public Enum MsgTypes
        MSGTYPE_STANDARD = &H0   ' Standard Frame (11 bit ID)
        MSGTYPE_RTR = &H1     ' Remote request
        MSGTYPE_EXTENDED = &H2   ' CAN 2.0 B Frame (29 Bit ID)
        MSGTYPE_STATUS = &H80   ' Status Message
    End Enum

    ' PCAN Hardware enumeration
    '
    Public Enum Hardware As Integer
        HW_ISA = 1
        HW_DONGLE_SJA = 5
        HW_DONGLE_SJA_EPP = 6
        HW_DONGLE_PRO = 7
        HW_DONGLE_PRO_EPP = 8
        HW_ISA_SJA = 9
        HW_PCI = 10
    End Enum

    ' Hardware type corresponding to the different PCAN Light Dlls
    '
    Public Enum HardwareType As Short
        ISA_1CH = 0  ' ISA 1 Channel
        ISA_2CH = 1  ' ISA 2 Channels
        PCI_1CH = 2  ' PCI 1 Channel
        PCI_2CH = 3  ' PCI 2 Channels
        PCC_1CH = 4  ' PCC 1 Channel
        PCC_2CH = 5  ' PCC 2 Channels
        USB_1CH = 6  ' USB 1st Channel
        USB_2CH = 7  ' USB 2nd Channel
        DNP = 8   ' DONGLE PRO
        DNG = 9   ' DONGLE
    End Enum

    ' CAN Baudrates
    '
    Public Enum Baudrates As Short
        BAUD_1M = &H14     '   1 MBit/s
        BAUD_500K = &H1C    ' 500 kBit/s 
        BAUD_250K = &H11C   ' 250 kBit/s
        BAUD_125K = &H31C   ' 125 kBit/s
        BAUD_100K = &H432F  ' 100 kBit/s
        BAUD_50K = &H472F  '  50 kBit/s
        BAUD_20K = &H532F  '  20 kBit/s
        BAUD_10K = &H672F  '  10 kBit/s
        BAUD_5K = &H7F7F   '   5 kBit/s
    End Enum

    ' CAN Error and status values
    '
    <Flags()> Public Enum CANResult
        ERR_OK = &H0
        ERR_XMTFULL = &H1          ' Send buffer of the Controller ist full
        ERR_OVERRUN = &H2          ' CAN-Controller was read to late 
        ERR_BUSLIGHT = &H4         ' Bus error: an Error count reached the limit
        ERR_BUSHEAVY = &H8         ' Bus error: an Error count reached the limit
        ERR_BUSOFF = &H10          ' Bus error: CAN_Controller went to 'Bus-Off'
        ERR_QRCVEMPTY = &H20       ' RcvQueue is empty
        ERR_QOVERRUN = &H40        ' RcvQueue was read to late
        ERR_QXMTFULL = &H80        ' Send queue is full
        ERR_REGTEST = &H100        ' RegisterTest of the 82C200/SJA1000 failed
        ERR_NOVXD = &H200          ' Problem with Localization of the VxD
        ERRMASK_ILLHANDLE = &H1C00 ' Mask for all Handle errors
        ERR_HWINUSE = &H400        ' Hardware is occupied by a net
        ERR_NETINUSE = &H800       ' The Net is attached to a Client
        ERR_ILLHW = &H1400         ' Invalid Hardware handle
        ERR_ILLNET = &H1800        ' Invalid Net handle 
        ERR_ILLCLIENT = &H1C00     ' Invalid Client handle 
        ERR_RESOURCE = &H2000      ' Not generatably Resource (FIFO, Client, Timeout)
        ERR_PARMTYP = &H4000       ' Parameter not permitted
        ERR_PARMVAL = &H8000       ' Invalid Parameter value
        ERR_ANYBUSERR = ERR_BUSLIGHT Or ERR_BUSHEAVY Or ERR_BUSOFF  ' All others error status <> 0 please ask by PEAK ......intern Driver errors..... 
        ERR_NO_DLL = &HFFFFFFFF    ' A Dll could not be loaded or a function was not found into the Dll
    End Enum
#End Region

#Region "Classes definition"
    ' Class to managing the multiple definition of a TCANMsg structure 
    ' between the different PCANLIGHT Classes/Dlls
    ' 
    Public Class TCLightMsg
#Region "Properties"
        ' 11/29-Bit CAN-ID
        '
        Public ID As Integer
        ' Kind of Message
        '
        Public MsgType As MsgTypes
        ' Lenght of the Message
        '
        Public Len As Byte
        ' Data Bytes (0...7)
        '
        Public DATA() As Byte
#End Region

#Region "Methodes"
#Region "Constructors, destructors, initialations"
        ' TCLightMsg standard constructor
        '
        Public Sub New()
            DATA = CType(Array.CreateInstance(GetType(Byte), 8), Byte())
        End Sub

        ' TCLightMsg constructor
        ' "Msg" = TCANMsg structure defined in the PCAN_ISA Class
        '
        Public Sub New(ByVal Msg As PCAN_ISA.TPCANMsg)
            ID = Msg.ID
            MsgType = CType(Msg.MSGTYPE, MsgTypes)
            Len = Msg.LEN
            DATA = Msg.DATA
        End Sub

        ' TCLightMsg constructor
        ' "Msg" = A TCANMsg structure defined in the PCAN_2ISA Class
        '
        Public Sub New(ByVal Msg As PCAN_2ISA.TPCANMsg)
            ID = Msg.ID
            MsgType = CType(Msg.MSGTYPE, MsgTypes)
            Len = Msg.LEN
            DATA = Msg.DATA
        End Sub

        ' TCLightMsg constructor
        ' "Msg" = A TCANMsg structure defined in the PCAN_PCI Class
        '
        Public Sub New(ByVal Msg As PCAN_PCI.TPCANMsg)
            ID = Msg.ID
            MsgType = CType(Msg.MSGTYPE, MsgTypes)
            Len = Msg.LEN
            DATA = Msg.DATA
        End Sub

        ' TCLightMsg constructor
        ' "Msg" = A TCANMsg structure defined in the PCAN_2PCI Class
        '
        Public Sub New(ByVal Msg As PCAN_2PCI.TPCANMsg)
            ID = Msg.ID
            MsgType = CType(Msg.MSGTYPE, MsgTypes)
            Len = Msg.LEN
            DATA = Msg.DATA
        End Sub

        ' TCLightMsg constructor
        ' "Msg" = A TCANMsg structure defined in the PCAN_PCC Class
        '
        Public Sub New(ByVal Msg As PCAN_PCC.TPCANMsg)
            ID = Msg.ID
            MsgType = CType(Msg.MSGTYPE, MsgTypes)
            Len = Msg.LEN
            DATA = Msg.DATA
        End Sub

        ' TCLightMsg constructor
        ' "Msg" = A TCANMsg structure defined in the PCAN_2PCC Class
        '
        Public Sub New(ByVal Msg As PCAN_2PCC.TPCANMsg)
            ID = Msg.ID
            MsgType = CType(Msg.MSGTYPE, MsgTypes)
            Len = Msg.LEN
            DATA = Msg.DATA
        End Sub

        ' TCLightMsg constructor
        ' "Msg" = A TCANMsg structure defined in the PCAN_USB Class
        '
        Public Sub New(ByVal Msg As PCAN_USB.TPCANMsg)
            ID = Msg.ID
            MsgType = CType(Msg.MSGTYPE, MsgTypes)
            Len = Msg.LEN
            DATA = Msg.DATA
        End Sub

        ' TCLightMsg constructor
        ' "Msg" = A TCANMsg structure defined in the PCAN_USB Class
        '
        Public Sub New(ByVal Msg As PCAN_2USB.TPCANMsg)
            ID = Msg.ID
            MsgType = CType(Msg.MSGTYPE, MsgTypes)
            Len = Msg.LEN
            DATA = Msg.DATA
        End Sub

        ' TCLightMsg constructor
        ' "Msg" = A TCANMsg structure defined in the PCAN_DNG Class
        '
        Public Sub New(ByVal Msg As PCAN_DNG.TPCANMsg)
            ID = Msg.ID
            MsgType = CType(Msg.MSGTYPE, MsgTypes)
            Len = Msg.LEN
            DATA = Msg.DATA
        End Sub

        ' TCLightMsg standard constructor
        ' "Msg" = A TCANMsg structure defined in the PCAN_DNP Class
        '
        Public Sub New(ByVal Msg As PCAN_DNP.TPCANMsg)
            ID = Msg.ID
            MsgType = CType(Msg.MSGTYPE, MsgTypes)
            Len = Msg.LEN
            DATA = Msg.DATA
        End Sub
#End Region

#Region "Casting functions"
        ' Overloaded Type Casting to a TCANMsg structure defined in the PCAN_ISA class
        ' "Msg" = A corresponding TCANMsg structure, defined in PCAN_ISA Class
        '
        Public Sub Fill(ByRef Msg As PCAN_ISA.TPCANMsg)
            Msg.ID = ID
            Msg.LEN = Len
            Msg.MSGTYPE = CByte(MsgType)
            Msg.DATA = DATA
        End Sub

        ' Overloaded Type Casting to a TCANMsg structure defined in the PCAN_2ISA class
        ' "Msg" = A corresponding TCANMsg structure, defined in PCAN_2ISA Class
        '
        Public Sub Fill(ByRef Msg As PCAN_2ISA.TPCANMsg)
            Msg.ID = ID
            Msg.LEN = Len
            Msg.MSGTYPE = CByte(MsgType)
            Msg.DATA = DATA
        End Sub

        ' Overloaded Type Casting to a TCANMsg structure defined in the PCAN_PCI class
        ' "Msg" = A corresponding TCANMsg structure, defined in PCAN_PCI Class
        '
        Public Sub Fill(ByRef Msg As PCAN_PCI.TPCANMsg)
            Msg.ID = ID
            Msg.LEN = Len
            Msg.MSGTYPE = CByte(MsgType)
            Msg.DATA = DATA
        End Sub

        ' Overloaded Type Casting to a TCANMsg structure defined in the PCAN_2PCI class
        ' "Msg" = A corresponding TCANMsg structure, defined in PCAN_2PCI Class
        '
        Public Sub Fill(ByRef Msg As PCAN_2PCI.TPCANMsg)
            Msg.ID = ID
            Msg.LEN = Len
            Msg.MSGTYPE = CByte(MsgType)
            Msg.DATA = DATA
        End Sub

        ' Overloaded Type Casting to a TCANMsg structure defined in the PCAN_PCC class
        ' "Msg" = A corresponding TCANMsg structure, defined in PCAN_PCC Class
        '
        Public Sub Fill(ByRef Msg As PCAN_PCC.TPCANMsg)
            Msg.ID = ID
            Msg.LEN = Len
            Msg.MSGTYPE = CByte(MsgType)
            Msg.DATA = DATA
        End Sub

        ' Overloaded Type Casting to a TCANMsg structure defined in the PCAN_2PCC class
        ' "Msg" = A corresponding TCANMsg structure, defined in PCAN_2PCC Class
        '
        Public Sub Fill(ByRef Msg As PCAN_2PCC.TPCANMsg)
            Msg.ID = ID
            Msg.LEN = Len
            Msg.MSGTYPE = CByte(MsgType)
            Msg.DATA = DATA
        End Sub

        ' Overloaded Type Casting to a TCANMsg structure defined in the PCAN_USB class
        ' "Msg" = A corresponding TCANMsg structure, defined in PCAN_USB Class
        '
        Public Sub Fill(ByRef Msg As PCAN_USB.TPCANMsg)
            Msg.ID = ID
            Msg.LEN = Len
            Msg.MSGTYPE = CByte(MsgType)
            Msg.DATA = DATA
        End Sub

        ' Overloaded Type Casting to a TCANMsg structure defined in the PCAN_USB class
        ' "Msg" = A corresponding TCANMsg structure, defined in PCAN_USB Class
        '
        Public Sub Fill(ByRef Msg As PCAN_2USB.TPCANMsg)
            Msg.ID = ID
            Msg.LEN = Len
            Msg.MSGTYPE = CByte(MsgType)
            Msg.DATA = DATA
        End Sub

        ' Overloaded Type Casting to a TCANMsg structure defined in the PCAN_DNG class
        ' "Msg" = A corresponding TCANMsg structure, defined in PCAN_DNG Class
        '
        Public Sub Fill(ByRef Msg As PCAN_DNG.TPCANMsg)
            Msg.ID = ID
            Msg.LEN = Len
            Msg.MSGTYPE = CByte(MsgType)
            Msg.DATA = DATA
        End Sub

        ' Overloaded Type Casting to a TCANMsg structure defined in the PCAN_DNP class
        ' "Msg" = A corresponding TCANMsg structure, defined in PCAN_DNP Class
        '
        Public Sub Fill(ByRef Msg As PCAN_DNP.TPCANMsg)
            Msg.ID = ID
            Msg.LEN = Len
            Msg.MSGTYPE = CByte(MsgType)
            Msg.DATA = DATA
        End Sub
#End Region
#End Region
    End Class

    ' Class to managing the multiple definition of a TPCANTimestamp structure 
    ' between the different PCANLIGHT Classes/Dlls
    ' 
    Public Class TCLightTimestamp
#Region "Properties"
        '  Base-value: milliseconds: 0.. 2^32-1
        '
        Public millis As Integer
        ' Roll-arounds of milliseconds
        '
        Public millis_overflow As Short
        ' Microseconds: 0..999 
        '
        Public micros As Short
#End Region

#Region "Methodes"
#Region "Constructors, destructors, initialations"
        ' TCLightTimestamp standard constructor
        '
        Public Sub New()
            millis = 0
            millis_overflow = 0
            micros = 0
        End Sub

        ' TCLightTimestamp constructor
        ' "RcvTime" = TPCANTimestamp structure defined in the PCAN_ISA Class
        '
        Public Sub New(ByVal RcvTime As PCAN_ISA.TPCANTimestamp)
            millis = RcvTime.millis
            millis_overflow = RcvTime.millis_overflow
            micros = RcvTime.micros
        End Sub

        ' TCLightTimestamp constructor
        ' "RcvTime" = TPCANTimestamp structure defined in the PCAN_2ISA Class
        '
        Public Sub New(ByVal RcvTime As PCAN_2ISA.TPCANTimestamp)
            millis = RcvTime.millis
            millis_overflow = RcvTime.millis_overflow
            micros = RcvTime.micros
        End Sub

        ' TCLightTimestamp constructor
        ' "RcvTime" = TPCANTimestamp structure defined in the PCAN_PCI Class
        '
        Public Sub New(ByVal RcvTime As PCAN_PCI.TPCANTimestamp)
            millis = RcvTime.millis
            millis_overflow = RcvTime.millis_overflow
            micros = RcvTime.micros
        End Sub

        ' TCLightTimestamp constructor
        ' "RcvTime" = TPCANTimestamp structure defined in the PCAN_2PCI Class
        '
        Public Sub New(ByVal RcvTime As PCAN_2PCI.TPCANTimestamp)
            millis = RcvTime.millis
            millis_overflow = RcvTime.millis_overflow
            micros = RcvTime.micros
        End Sub

        ' TCLightTimestamp constructor
        ' "RcvTime" = TPCANTimestamp structure defined in the PCAN_PCC Class
        '
        Public Sub New(ByVal RcvTime As PCAN_PCC.TPCANTimestamp)
            millis = RcvTime.millis
            millis_overflow = RcvTime.millis_overflow
            micros = RcvTime.micros
        End Sub

        ' TCLightTimestamp constructor
        ' "RcvTime" = TPCANTimestamp structure defined in the PCAN_2PCC Class
        '
        Public Sub New(ByVal RcvTime As PCAN_2PCC.TPCANTimestamp)
            millis = RcvTime.millis
            millis_overflow = RcvTime.millis_overflow
            micros = RcvTime.micros
        End Sub

        ' TCLightTimestamp constructor
        ' "RcvTime" = TPCANTimestamp structure defined in the PCAN_USB Class
        '
        Public Sub New(ByVal RcvTime As PCAN_USB.TPCANTimestamp)
            millis = RcvTime.millis
            millis_overflow = RcvTime.millis_overflow
            micros = RcvTime.micros
        End Sub

        ' TCLightTimestamp constructor
        ' "RcvTime" = TPCANTimestamp structure defined in the PCAN_2USB Class
        '
        Public Sub New(ByVal RcvTime As PCAN_2USB.TPCANTimestamp)
            millis = RcvTime.millis
            millis_overflow = RcvTime.millis_overflow
            micros = RcvTime.micros
        End Sub

        ' TCLightTimestamp constructor
        ' "RcvTime" = TPCANTimestamp structure defined in the PCAN_DNG Class
        '
        Public Sub New(ByVal RcvTime As PCAN_DNG.TPCANTimestamp)
            millis = RcvTime.millis
            millis_overflow = RcvTime.millis_overflow
            micros = RcvTime.micros
        End Sub

        ' TCLightTimestamp constructor
        ' "RcvTime" = TPCANTimestamp structure defined in the PCAN_DNP Class
        '
        Public Sub New(ByVal RcvTime As PCAN_DNP.TPCANTimestamp)
            millis = RcvTime.millis
            millis_overflow = RcvTime.millis_overflow
            micros = RcvTime.micros
        End Sub
#End Region

#Region "Casting functions"
        ' Overloaded Type Casting to a TPCANTimestamp structure defined in the PCAN_ISA class
        ' "RcvTime" = TPCANTimestamp structure, defined in PCAN_ISA Class
        '
        Public Sub Fill(ByRef RcvTime As PCAN_ISA.TPCANTimestamp)
            RcvTime.millis = millis
            RcvTime.millis_overflow = millis_overflow
            RcvTime.micros = micros
        End Sub

        ' Overloaded Type Casting to a TPCANTimestamp structure defined in the PCAN_2ISA class
        ' "RcvTime" = TPCANTimestamp structure, defined in PCAN_2ISA Class
        '
        Public Sub Fill(ByRef RcvTime As PCAN_2ISA.TPCANTimestamp)
            RcvTime.millis = millis
            RcvTime.millis_overflow = millis_overflow
            RcvTime.micros = micros
        End Sub

        ' Overloaded Type Casting to a TPCANTimestamp structure defined in the PCAN_PCI class
        ' "RcvTime" = TPCANTimestamp structure, defined in PCAN_PCI Class
        '
        Public Sub Fill(ByRef RcvTime As PCAN_PCI.TPCANTimestamp)
            RcvTime.millis = millis
            RcvTime.millis_overflow = millis_overflow
            RcvTime.micros = micros
        End Sub

        ' Overloaded Type Casting to a TPCANTimestamp structure defined in the PCAN_2PCI class
        ' "RcvTime" = TPCANTimestamp structure, defined in PCAN_2PCI Class
        '
        Public Sub Fill(ByRef RcvTime As PCAN_2PCI.TPCANTimestamp)
            RcvTime.millis = millis
            RcvTime.millis_overflow = millis_overflow
            RcvTime.micros = micros
        End Sub

        ' Overloaded Type Casting to a TPCANTimestamp structure defined in the PCAN_PCC class
        ' "RcvTime" = TPCANTimestamp structure, defined in PCAN_PCC Class
        '
        Public Sub Fill(ByRef RcvTime As PCAN_PCC.TPCANTimestamp)
            RcvTime.millis = millis
            RcvTime.millis_overflow = millis_overflow
            RcvTime.micros = micros
        End Sub

        ' Overloaded Type Casting to a TPCANTimestamp structure defined in the PCAN_2PCC class
        ' "RcvTime" = TPCANTimestamp structure, defined in PCAN_2PCC Class
        '
        Public Sub Fill(ByRef RcvTime As PCAN_2PCC.TPCANTimestamp)
            RcvTime.millis = millis
            RcvTime.millis_overflow = millis_overflow
            RcvTime.micros = micros
        End Sub

        ' Overloaded Type Casting to a TPCANTimestamp structure defined in the PCAN_USB class
        ' "RcvTime" = TPCANTimestamp structure, defined in PCAN_USB Class
        '
        Public Sub Fill(ByRef RcvTime As PCAN_USB.TPCANTimestamp)
            RcvTime.millis = millis
            RcvTime.millis_overflow = millis_overflow
            RcvTime.micros = micros
        End Sub

        ' Overloaded Type Casting to a TPCANTimestamp structure defined in the PCAN_2USB class
        ' "RcvTime" = TPCANTimestamp structure, defined in PCAN_2USB Class
        '
        Public Sub Fill(ByRef RcvTime As PCAN_2USB.TPCANTimestamp)
            RcvTime.millis = millis
            RcvTime.millis_overflow = millis_overflow
            RcvTime.micros = micros
        End Sub

        ' Overloaded Type Casting to a TPCANTimestamp structure defined in the PCAN_DNG class
        ' "RcvTime" = TPCANTimestamp structure, defined in PCAN_DNG Class
        '
        Public Sub Fill(ByRef RcvTime As PCAN_DNG.TPCANTimestamp)
            RcvTime.millis = millis
            RcvTime.millis_overflow = millis_overflow
            RcvTime.micros = micros
        End Sub

        ' Overloaded Type Casting to a TPCANTimestamp structure defined in the PCAN_DNP class
        ' "RcvTime" = TPCANTimestamp structure, defined in PCAN_DNP Class
        '
        Public Sub Fill(ByRef RcvTime As PCAN_DNP.TPCANTimestamp)
            RcvTime.millis = millis
            RcvTime.millis_overflow = millis_overflow
            RcvTime.micros = micros
        End Sub
#End Region
#End Region
    End Class

    ' Interfacing class to the PCAN Light Dlls
    '
    Public Class PCANLight
#Region "Methodes"
#Region "PCANLight Functions"
        ' PCANLight Init function for non Plug and Play Hardware.  
        ' This function make the following:
        '   - Activate a Hardware
        '   - Make a Register Test of 82C200/SJA1000
        '   - Allocate a Send buffer and a Hardware handle
        '   - Programs the configuration of the transmit/receive driver
        '   - Set the Baudrate register
        '   - Set the Controller in RESET condition
        ' "HWType" = Which hardware should be initialized
        ' "BTR0BTR1" = BTR0-BTR1 baudrate register
        ' "MsgType" = If the frame type is standard or extended
        ' "IO_Port" = Input/output Port Address of the hardware
        ' "Interrupt" = Interrupt number
        ' RETURN = A CANResult value - Error/status of the hardware after execute the function
        ' 
        Public Shared Function Init(ByVal HWType As HardwareType, ByVal BTR0BTR1 As Baudrates, ByVal MsgType As FramesType, ByVal IO_Port As Integer, ByVal Interrupt As Short) As CANResult
            Try
                Select Case HWType
                    Case HardwareType.ISA_1CH
                        Return CType(PCAN_ISA.Init(BTR0BTR1, MsgType, Hardware.HW_ISA_SJA, IO_Port, Interrupt), CANResult)

                    Case HardwareType.ISA_2CH
                        Return CType(PCAN_2ISA.Init(BTR0BTR1, MsgType, Hardware.HW_ISA_SJA, IO_Port, Interrupt), CANResult)

                    Case HardwareType.DNG
                        Return CType(PCAN_DNG.init(BTR0BTR1, MsgType, Hardware.HW_DONGLE_SJA, IO_Port, Interrupt), CANResult)

                    Case HardwareType.DNP
                        Return CType(PCAN_DNP.init(BTR0BTR1, MsgType, Hardware.HW_DONGLE_PRO, IO_Port, Interrupt), CANResult)

                    Case Else
                        ' Hardware is not valid for this function
                        '
                        Return CANResult.ERR_ILLHW
                End Select
            Catch ex As Exception
                ' Error: Dll does not exists or the Init function is not available
                '
                System.Windows.Forms.MessageBox.Show("Error: """ + ex.Message + """")
                Return CANResult.ERR_NO_DLL
            End Try
        End Function

        ' PCANLight Init function for Plug and Play Hardware.  
        ' This function make the following:
        '   - Activate a Hardware
        '   - Make a Register Test of 82C200/SJA1000
        '   - Allocate a Send buffer and a Hardware handle
        '   - Programs the configuration of the transmit/receive driver
        '   - Set the Baudrate register
        '   - Set the Controller in RESET condition
        ' "HWType" = Which hardware should be initialized
        ' "BTR0BTR1" = BTR0-BTR1 baudrate register
        ' "MsgType" = If the frame type is standard or extended
        ' RETURN = A CANResult value - Error/status of the hardware after execute the function
        ' 
        Public Shared Function Init(ByVal HWType As HardwareType, ByVal BTR0BTR1 As Baudrates, ByVal MsgType As FramesType) As CANResult
            Try
                Select Case HWType
                    Case HardwareType.PCI_1CH
                        Return CType(PCAN_PCI.init(BTR0BTR1, MsgType), CANResult)

                    Case HardwareType.PCI_2CH
                        Return CType(PCAN_2PCI.init(BTR0BTR1, MsgType), CANResult)

                    Case HardwareType.PCC_1CH
                        Return CType(PCAN_PCC.init(BTR0BTR1, MsgType), CANResult)

                    Case HardwareType.PCC_2CH
                        Return CType(PCAN_2PCC.init(BTR0BTR1, MsgType), CANResult)

                    Case HardwareType.USB_1CH
                        Return CType(PCAN_USB.Init(BTR0BTR1, MsgType), CANResult)

                    Case HardwareType.USB_2CH
                        Return CType(PCAN_2USB.Init(BTR0BTR1, MsgType), CANResult)

                    Case Else
                        ' Hardware is not valid for this function
                        '
                        Return CANResult.ERR_ILLHW
                End Select
            Catch ex As Exception
                ' Error: Dll does not exists or the Init function is not available
                '
                System.Windows.Forms.MessageBox.Show("Error: """ + ex.Message + """")
                Return CANResult.ERR_NO_DLL
            End Try
        End Function

        ' PCANLight Close Function  
        ' This function terminate and release all resources and the configured hardware
        ' "HWType" = Which hardware should be finished
        ' RETURN = A CANResult value - Error/status of the hardware after execute the function
        ' 
        Public Shared Function Close(ByVal HWType As HardwareType) As CANResult
            Try
                Select Case HWType
                    Case HardwareType.ISA_1CH
                        Return CType(PCAN_ISA.Close(), CANResult)

                    Case HardwareType.ISA_2CH
                        Return CType(PCAN_2ISA.Close(), CANResult)

                    Case HardwareType.PCI_1CH
                        Return CType(PCAN_PCI.Close(), CANResult)

                    Case HardwareType.PCI_2CH
                        Return CType(PCAN_2PCI.Close(), CANResult)

                    Case HardwareType.PCC_1CH
                        Return CType(PCAN_PCC.Close(), CANResult)

                    Case HardwareType.PCC_2CH
                        Return CType(PCAN_2PCC.Close(), CANResult)

                    Case HardwareType.USB_1CH
                        Return CType(PCAN_USB.Close(), CANResult)

                    Case HardwareType.USB_2CH
                        Return CType(PCAN_2USB.Close(), CANResult)

                    Case HardwareType.DNP
                        Return CType(PCAN_DNP.Close(), CANResult)

                    Case HardwareType.DNG
                        Return CType(PCAN_DNG.Close(), CANResult)

                    Case Else
                        ' Hardware is not valid for this function
                        '
                        Return CANResult.ERR_ILLHW
                End Select
            Catch ex As Exception
                ' Error: Dll does not exists or the Init function is not available
                '
                System.Windows.Forms.MessageBox.Show("Error: """ + ex.Message + """")
                Return CANResult.ERR_NO_DLL
            End Try
        End Function

        ' PCANLight Status Function  
        ' This function request the current status of the hardware (b.e. BUS-OFF)
        ' "HWType" = Which hardware should be asked for its Status
        ' RETURN = A CANResult value - Error/status of the hardware after execute the function
        ' 
        Public Shared Function Status(ByVal HWType As HardwareType) As CANResult
            Try
                Select Case HWType
                    Case HardwareType.ISA_1CH
                        Return CType(PCAN_ISA.Status(), CANResult)

                    Case HardwareType.ISA_2CH
                        Return CType(PCAN_2ISA.Status(), CANResult)

                    Case HardwareType.PCI_1CH
                        Return CType(PCAN_PCI.Status(), CANResult)

                    Case HardwareType.PCI_2CH
                        Return CType(PCAN_2PCI.Status(), CANResult)

                    Case HardwareType.PCC_1CH
                        Return CType(PCAN_PCC.Status(), CANResult)

                    Case HardwareType.PCC_2CH
                        Return CType(PCAN_2PCC.Status(), CANResult)

                    Case HardwareType.USB_1CH
                        Return CType(PCAN_USB.Status(), CANResult)

                    Case HardwareType.USB_2CH
                        Return CType(PCAN_2USB.Status(), CANResult)

                    Case HardwareType.DNP
                        Return CType(PCAN_DNP.Status(), CANResult)

                    Case HardwareType.DNG
                        Return CType(PCAN_DNG.Status(), CANResult)

                    Case Else
                        ' Hardware is not valid for this function
                        '
                        Return CANResult.ERR_ILLHW
                End Select
            Catch ex As Exception
                ' Error: Dll does not exists or the Init function is not available
                '
                System.Windows.Forms.MessageBox.Show("Error: """ + ex.Message + """")
                Return CANResult.ERR_NO_DLL
            End Try
        End Function

        ' PCANLight Write Function  
        ' This function Place a CAN message into the Transmit Queue of the CAN Hardware
        ' "HWType" = In which hardware should be written the CAN Message
        ' "MsgToSend" = The TCLightMsg message to be written
        ' RETURN = A CANResult value - Error/status of the hardware after execute the function
        '
        Public Shared Function Write(ByVal HWType As HardwareType, ByVal MsgToSend As TCLightMsg) As CANResult
            Dim MsgIsa As PCAN_ISA.TPCANMsg
            Dim MsgIsa2 As PCAN_2ISA.TPCANMsg
            Dim MsgPci As PCAN_PCI.TPCANMsg
            Dim MsgPci2 As PCAN_2PCI.TPCANMsg
            Dim MsgPcc As PCAN_PCC.TPCANMsg
            Dim MsgPcc2 As PCAN_2PCC.TPCANMsg
            Dim MsgUsb As PCAN_USB.TPCANMsg
            Dim MsgUsb2 As PCAN_2USB.TPCANMsg
            Dim MsgDnp As PCAN_DNP.TPCANMsg
            Dim MsgDng As PCAN_DNG.TPCANMsg

            Try
                Select Case HWType
                    Case HardwareType.ISA_1CH
                        MsgIsa = Nothing
                        MsgToSend.Fill(MsgIsa)
                        Return CType(PCAN_ISA.Write(MsgIsa), CANResult)

                    Case HardwareType.ISA_2CH
                        MsgIsa2 = Nothing
                        MsgToSend.Fill(MsgIsa2)
                        Return CType(PCAN_2ISA.Write(MsgIsa2), CANResult)

                    Case HardwareType.PCI_1CH
                        MsgPci = Nothing
                        MsgToSend.Fill(MsgPci)
                        Return CType(PCAN_PCI.Write(MsgPci), CANResult)

                    Case HardwareType.PCI_2CH
                        MsgPci2 = Nothing
                        MsgToSend.Fill(MsgPci2)
                        Return CType(PCAN_2PCI.Write(MsgPci2), CANResult)

                    Case HardwareType.PCC_1CH
                        MsgPcc = Nothing
                        MsgToSend.Fill(MsgPcc)
                        Return CType(PCAN_PCC.Write(MsgPcc), CANResult)

                    Case HardwareType.PCC_2CH
                        MsgPcc2 = Nothing
                        MsgToSend.Fill(MsgPcc2)
                        Return CType(PCAN_2PCC.Write(MsgPcc2), CANResult)

                    Case HardwareType.USB_1CH
                        MsgUsb = Nothing
                        MsgToSend.Fill(MsgUsb)
                        Return CType(PCAN_USB.Write(MsgUsb), CANResult)

                    Case HardwareType.USB_2CH
                        MsgUsb2 = Nothing
                        MsgToSend.Fill(MsgUsb2)
                        Return CType(PCAN_2USB.Write(MsgUsb2), CANResult)

                    Case HardwareType.DNP
                        MsgDnp = Nothing
                        MsgToSend.Fill(MsgDnp)
                        Return CType(PCAN_DNP.Write(MsgDnp), CANResult)

                    Case HardwareType.DNG
                        MsgDng = Nothing
                        MsgToSend.Fill(MsgDng)
                        Return CType(PCAN_DNG.Write(MsgDng), CANResult)

                    Case Else
                        ' Hardware is not valid for this function
                        '
                        Return CANResult.ERR_ILLHW
                End Select
            Catch ex As Exception
                ' Error: Dll does not exists or the Init function is not available
                '
                System.Windows.Forms.MessageBox.Show("Error: """ + ex.Message + """")
                Return CANResult.ERR_NO_DLL
            End Try
        End Function

        ' PCANLight Read function
        ' This function get the next message or the next error from the Receive Queue of 
        ' the CAN Hardware.  
        ' REMARK:
        '		- Check always the type of the received Message (MSGTYPE_STANDARD,MSGTYPE_RTR,
        '		  MSGTYPE_EXTENDED,MSGTYPE_STATUS)
        '		- The function will return ERR_OK always that you receive a CAN message successfully 
        '		  although if the messages is a MSGTYPE_STATUS message.  
        '		- When a MSGTYPE_STATUS mesasge is got, the ID and Length information of the message 
        '		  will be treated as indefined values. Actually information of the received message
        '		  should be interpreted using the first 4 data bytes as follow:
        '				Data0	Data1	Data2	Data3	Kind of Error
        '				0x00	0x00	0x00	0x02	CAN_ERR_OVERRUN		0x0002	CAN Controller was read to late
        '				0x00	0x00	0x00	0x04	CAN_ERR_BUSLIGHT	0x0004  Bus Error: An error counter limit reached (96)
        '				0x00	0x00	0x00	0x08	CAN_ERR_BUSHEAVY	0x0008	Bus Error: An error counter limit reached (128)
        '				0x00	0x00	0x00	0x10	CAN_ERR_BUSOFF		0x0010	Bus Error: Can Controller went "Bus-Off"
        '		- If a CAN_ERR_BUSOFF status message is received, the CAN Controller must to be 
        '		  initialized again using the Init() function.  Otherwise, will be not possible 
        '		  to send/receive more messages.
        ' "HWType" = From which hardware should be read a CAN Message
        ' "Msg" = The TCLightMsg structure to store the CAN message
        ' RETURN = A CANResult value - Error/status of the hardware after execute the function
        '
        Public Shared Function Read(ByVal HWType As HardwareType, ByRef Msg As TCLightMsg) As CANResult
            Dim MsgIsa As PCAN_ISA.TPCANMsg
            Dim MsgIsa2 As PCAN_2ISA.TPCANMsg
            Dim MsgPci As PCAN_PCI.TPCANMsg
            Dim MsgPci2 As PCAN_2PCI.TPCANMsg
            Dim MsgPcc As PCAN_PCC.TPCANMsg
            Dim MsgPcc2 As PCAN_2PCC.TPCANMsg
            Dim MsgUsb As PCAN_USB.TPCANMsg
            Dim MsgUsb2 As PCAN_2USB.TPCANMsg
            Dim MsgDnp As PCAN_DNP.TPCANMsg
            Dim MsgDng As PCAN_DNG.TPCANMsg
            Dim resTemp As CANResult

            Try
                Select Case HWType
                    Case HardwareType.ISA_1CH
                        MsgIsa = Nothing
                        resTemp = CType(PCAN_ISA.Read(MsgIsa), CANResult)
                        Msg = New TCLightMsg(MsgIsa)
                        Return resTemp

                    Case HardwareType.ISA_2CH
                        MsgIsa2 = Nothing
                        resTemp = CType(PCAN_2ISA.Read(MsgIsa2), CANResult)
                        Msg = New TCLightMsg(MsgIsa2)
                        Return resTemp

                    Case HardwareType.PCI_1CH
                        MsgPci = Nothing
                        resTemp = CType(PCAN_PCI.Read(MsgPci), CANResult)
                        Msg = New TCLightMsg(MsgPci)
                        Return resTemp

                    Case HardwareType.PCI_2CH
                        MsgPci2 = Nothing
                        resTemp = CType(PCAN_2PCI.Read(MsgPci2), CANResult)
                        Msg = New TCLightMsg(MsgPci2)
                        Return resTemp

                    Case HardwareType.PCC_1CH
                        MsgPcc = Nothing
                        resTemp = CType(PCAN_PCC.Read(MsgPcc), CANResult)
                        Msg = New TCLightMsg(MsgPcc)
                        Return resTemp

                    Case HardwareType.PCC_2CH
                        MsgPcc2 = Nothing
                        resTemp = CType(PCAN_2PCC.Read(MsgPcc2), CANResult)
                        Msg = New TCLightMsg(MsgPcc2)
                        Return resTemp

                    Case HardwareType.USB_1CH
                        MsgUsb = Nothing
                        resTemp = CType(PCAN_USB.Read(MsgUsb), CANResult)
                        Msg = New TCLightMsg(MsgUsb)
                        Return resTemp

                    Case HardwareType.USB_2CH
                        MsgUsb2 = Nothing
                        resTemp = CType(PCAN_2USB.Read(MsgUsb2), CANResult)
                        Msg = New TCLightMsg(MsgUsb2)
                        Return resTemp

                    Case HardwareType.DNP
                        MsgDnp = Nothing
                        resTemp = CType(PCAN_DNP.Read(MsgDnp), CANResult)
                        Msg = New TCLightMsg(MsgDnp)
                        Return resTemp

                    Case HardwareType.DNG
                        MsgDng = Nothing
                        resTemp = CType(PCAN_DNG.Read(MsgDng), CANResult)
                        Msg = New TCLightMsg(MsgDng)
                        Return resTemp

                    Case Else
                        ' Hardware is not valid for this function
                        '
                        Return CANResult.ERR_ILLHW
                End Select
            Catch ex As Exception
                ' Error: Dll does not exists or the Init function is not available
                '
                System.Windows.Forms.MessageBox.Show("Error: """ + ex.Message + """")
                Return CANResult.ERR_NO_DLL
            End Try
        End Function

        ' PCANLight ReadEx function
        ' This function get the next message or the next error from the Receive Queue of 
        ' the CAN Hardware and the time when the message arrived.  
        ' REMARK:
        '		- Check always the type of the received Message (MSGTYPE_STANDARD,MSGTYPE_RTR,
        '		  MSGTYPE_EXTENDED,MSGTYPE_STATUS)
        '		- The function will return ERR_OK always that you receive a CAN message successfully 
        '		  although if the messages is a MSGTYPE_STATUS message.  
        '		- When a MSGTYPE_STATUS mesasge is got, the ID and Length information of the message 
        '		  will be treated as indefined values. Actually information of the received message
        '		  should be interpreted using the first 4 data bytes as follow:
        '				Data0	Data1	Data2	Data3	Kind of Error
        '				0x00	0x00	0x00	0x02	CAN_ERR_OVERRUN		0x0002	CAN Controller was read to late
        '				0x00	0x00	0x00	0x04	CAN_ERR_BUSLIGHT	0x0004  Bus Error: An error counter limit reached (96)
        '				0x00	0x00	0x00	0x08	CAN_ERR_BUSHEAVY	0x0008	Bus Error: An error counter limit reached (128)
        '				0x00	0x00	0x00	0x10	CAN_ERR_BUSOFF		0x0010	Bus Error: Can Controller went "Bus-Off"
        '		- If a CAN_ERR_BUSOFF status message is received, the CAN Controller must to be 
        '		  initialized again using the Init() function.  Otherwise, will be not possible 
        '		  to send/receive more messages.
        '
        ' "HWType" = From which hardware should be read a CAN Message
        ' "Msg" = The TCLightMsg structure to store the CAN message
        ' "RcvTime" = The TCLightTimestamp structure to store the timestamp of the CAN message
        ' RETURN = A CANResult value - Error/status of the hardware after execute the function
        '
        Public Shared Function ReadEx(ByVal HWType As HardwareType, ByRef Msg As TCLightMsg, ByRef RcvTime As TCLightTimestamp) As CANResult
            Dim MsgIsa As PCAN_ISA.TPCANMsg
            Dim MsgIsa2 As PCAN_2ISA.TPCANMsg
            Dim MsgPci As PCAN_PCI.TPCANMsg
            Dim MsgPci2 As PCAN_2PCI.TPCANMsg
            Dim MsgPcc As PCAN_PCC.TPCANMsg
            Dim MsgPcc2 As PCAN_2PCC.TPCANMsg
            Dim MsgUsb As PCAN_USB.TPCANMsg
            Dim MsgUsb2 As PCAN_2USB.TPCANMsg
            Dim MsgDnp As PCAN_DNP.TPCANMsg
            Dim MsgDng As PCAN_DNG.TPCANMsg

            Dim RcvTimeIsa As PCAN_ISA.TPCANTimestamp
            Dim RcvTimeIsa2 As PCAN_2ISA.TPCANTimestamp
            Dim RcvTimePci As PCAN_PCI.TPCANTimestamp
            Dim RcvTimePci2 As PCAN_2PCI.TPCANTimestamp
            Dim RcvTimePcc As PCAN_PCC.TPCANTimestamp
            Dim RcvTimePcc2 As PCAN_2PCC.TPCANTimestamp
            Dim RcvTimeUsb As PCAN_USB.TPCANTimestamp
            Dim RcvTimeUsb2 As PCAN_2USB.TPCANTimestamp
            Dim RcvTimeDnp As PCAN_DNP.TPCANTimestamp
            Dim RcvTimeDng As PCAN_DNG.TPCANTimestamp

            Dim resTemp As CANResult

            Try
                Select Case HWType
                    Case HardwareType.ISA_1CH
                        MsgIsa = Nothing
                        RcvTimeIsa = Nothing
                        resTemp = CType(PCAN_ISA.ReadEx(MsgIsa, RcvTimeIsa), CANResult)
                        Msg = New TCLightMsg(MsgIsa)
                        RcvTime = New TCLightTimestamp(RcvTimeIsa)
                        Return resTemp

                    Case HardwareType.ISA_2CH
                        MsgIsa2 = Nothing
                        RcvTimeIsa2 = Nothing
                        resTemp = CType(PCAN_2ISA.ReadEx(MsgIsa2, RcvTimeIsa2), CANResult)
                        Msg = New TCLightMsg(MsgIsa2)
                        RcvTime = New TCLightTimestamp(RcvTimeIsa2)
                        Return resTemp

                    Case HardwareType.PCI_1CH
                        MsgPci = Nothing
                        RcvTimePci = Nothing
                        resTemp = CType(PCAN_PCI.ReadEx(MsgPci, RcvTimePci), CANResult)
                        Msg = New TCLightMsg(MsgPci)
                        RcvTime = New TCLightTimestamp(RcvTimePci)
                        Return resTemp

                    Case HardwareType.PCI_2CH
                        MsgPci2 = Nothing
                        RcvTimePci2 = Nothing
                        resTemp = CType(PCAN_2PCI.ReadEx(MsgPci2, RcvTimePci2), CANResult)
                        Msg = New TCLightMsg(MsgPci2)
                        RcvTime = New TCLightTimestamp(RcvTimePci2)
                        Return resTemp

                    Case HardwareType.PCC_1CH
                        MsgPcc = Nothing
                        RcvTimePcc = Nothing
                        resTemp = CType(PCAN_PCC.ReadEx(MsgPcc, RcvTimePcc), CANResult)
                        Msg = New TCLightMsg(MsgPcc)
                        RcvTime = New TCLightTimestamp(RcvTimePcc)
                        Return resTemp

                    Case HardwareType.PCC_2CH
                        MsgPcc2 = Nothing
                        RcvTimePcc2 = Nothing
                        resTemp = CType(PCAN_2PCC.ReadEx(MsgPcc2, RcvTimePcc2), CANResult)
                        Msg = New TCLightMsg(MsgPcc2)
                        RcvTime = New TCLightTimestamp(RcvTimePcc2)
                        Return resTemp

                    Case HardwareType.USB_1CH
                        MsgUsb = Nothing
                        RcvTimeUsb = Nothing
                        resTemp = CType(PCAN_USB.ReadEx(MsgUsb, RcvTimeUsb), CANResult)
                        Msg = New TCLightMsg(MsgUsb)
                        RcvTime = New TCLightTimestamp(RcvTimeUsb)
                        Return resTemp

                    Case HardwareType.USB_2CH
                        MsgUsb2 = Nothing
                        RcvTimeUsb2 = Nothing
                        resTemp = CType(PCAN_2USB.ReadEx(MsgUsb2, RcvTimeUsb2), CANResult)
                        Msg = New TCLightMsg(MsgUsb2)
                        RcvTime = New TCLightTimestamp(RcvTimeUsb2)
                        Return resTemp

                    Case HardwareType.DNP
                        MsgDnp = Nothing
                        RcvTimeDnp = Nothing
                        resTemp = CType(PCAN_DNP.ReadEx(MsgDnp, RcvTimeDnp), CANResult)
                        Msg = New TCLightMsg(MsgDnp)
                        RcvTime = New TCLightTimestamp(RcvTimeDnp)
                        Return resTemp

                    Case HardwareType.DNG
                        MsgDng = Nothing
                        RcvTimeDng = Nothing
                        resTemp = CType(PCAN_DNG.ReadEx(MsgDng, RcvTimeDng), CANResult)
                        Msg = New TCLightMsg(MsgDng)
                        RcvTime = New TCLightTimestamp(RcvTimeDng)
                        Return resTemp

                    Case Else
                        ' Hardware is not valid for this function
                        '
                        Return CANResult.ERR_ILLHW
                End Select
            Catch ex As EntryPointNotFoundException
                ' Function is not available in the loaded Dll
                '
                System.Windows.Forms.MessageBox.Show("Error: Wrong Version. """ + ex.Message + """")
                Return CANResult.ERR_NO_DLL
            Catch ex As Exception
                ' Error: Dll does not exists or the Init function is not available
                '
                System.Windows.Forms.MessageBox.Show("Error: """ + ex.Message + """")
                Return CANResult.ERR_NO_DLL
            End Try
        End Function

        ' PCANLight VersionInfo function
        ' This function get the Version and copyright of the hardware as text (max. 255 characters)
        ' "HWType" = Which hardware should be asked for its Version information
        ' "strInfo" = String variable to return the hardware information
        ' RETURN = A CANResult value - Error/status of the hardware after execute the function
        '
        Public Shared Function VersionInfo(ByVal HWType As HardwareType, ByRef strInfo As String) As CANResult
            Dim stbTemp As StringBuilder
            Dim resTemp As CANResult

            strInfo = ""

            Try
                stbTemp = New StringBuilder(256)

                Select Case HWType
                    Case HardwareType.ISA_1CH
                        resTemp = CType(PCAN_ISA.VersionInfo(stbTemp), CANResult)

                    Case HardwareType.ISA_2CH
                        resTemp = CType(PCAN_2ISA.VersionInfo(stbTemp), CANResult)

                    Case HardwareType.PCI_1CH
                        resTemp = CType(PCAN_PCI.VersionInfo(stbTemp), CANResult)

                    Case HardwareType.PCI_2CH
                        resTemp = CType(PCAN_2PCI.VersionInfo(stbTemp), CANResult)

                    Case HardwareType.PCC_1CH
                        resTemp = CType(PCAN_PCC.VersionInfo(stbTemp), CANResult)

                    Case HardwareType.PCC_2CH
                        resTemp = CType(PCAN_2PCC.VersionInfo(stbTemp), CANResult)

                    Case HardwareType.USB_1CH
                        resTemp = CType(PCAN_USB.VersionInfo(stbTemp), CANResult)

                    Case HardwareType.USB_2CH
                        resTemp = CType(PCAN_2USB.VersionInfo(stbTemp), CANResult)

                    Case HardwareType.DNP
                        resTemp = CType(PCAN_DNP.VersionInfo(stbTemp), CANResult)

                    Case HardwareType.DNG
                        resTemp = CType(PCAN_DNG.VersionInfo(stbTemp), CANResult)

                    Case Else
                        ' Hardware is not valid for this function
                        '
                        stbTemp = New StringBuilder("")
                        resTemp = CANResult.ERR_ILLHW
                End Select
                strInfo = stbTemp.ToString()
                Return resTemp
            Catch ex As Exception
                ' Error: Dll does not exists or the Init function is not available
                '
                System.Windows.Forms.MessageBox.Show("Error: """ + ex.Message + """")
                Return CANResult.ERR_NO_DLL
            End Try
        End Function

        ' PCANLight DllVersionInfo function
        ' This function get the Version information of the used PCAN-Light DLL. (max. 255 characters)
        ' "HWType" = Which DLL (Hardware implementation) should be asked for its Version information
        ' "strInfo" = String variable to return the DLL information
        ' RETURN = A CANResult value generated after execute the function
        '
        Public Shared Function DllVersionInfo(ByVal HWType As HardwareType, ByRef strInfo As String) As CANResult
            Dim stbTemp As StringBuilder
            Dim resTemp As CANResult

            strInfo = ""

            Try
                stbTemp = New StringBuilder(256)

                Select Case HWType
                    Case HardwareType.ISA_1CH
                        resTemp = CType(PCAN_ISA.DLLVersionInfo(stbTemp), CANResult)

                    Case HardwareType.ISA_2CH
                        resTemp = CType(PCAN_2ISA.DLLVersionInfo(stbTemp), CANResult)

                    Case HardwareType.PCI_1CH
                        resTemp = CType(PCAN_PCI.DLLVersionInfo(stbTemp), CANResult)

                    Case HardwareType.PCI_2CH
                        resTemp = CType(PCAN_2PCI.DLLVersionInfo(stbTemp), CANResult)

                    Case HardwareType.PCC_1CH
                        resTemp = CType(PCAN_PCC.DLLVersionInfo(stbTemp), CANResult)

                    Case HardwareType.PCC_2CH
                        resTemp = CType(PCAN_2PCC.DLLVersionInfo(stbTemp), CANResult)

                    Case HardwareType.USB_1CH
                        resTemp = CType(PCAN_USB.DLLVersionInfo(stbTemp), CANResult)

                    Case HardwareType.USB_2CH
                        resTemp = CType(PCAN_2USB.DLLVersionInfo(stbTemp), CANResult)

                    Case HardwareType.DNP
                        resTemp = CType(PCAN_DNP.DLLVersionInfo(stbTemp), CANResult)

                    Case HardwareType.DNG
                        resTemp = CType(PCAN_DNG.DLLVersionInfo(stbTemp), CANResult)

                    Case Else
                        ' Hardware is not valid for this function
                        '
                        stbTemp = New StringBuilder("")
                        resTemp = CANResult.ERR_ILLHW
                End Select
                strInfo = stbTemp.ToString()
                Return resTemp
            Catch ex As EntryPointNotFoundException
                ' Function is not available in the loaded Dll
                '
                System.Windows.Forms.MessageBox.Show("Error: Wrong Version. """ + ex.Message + """")
                Return CANResult.ERR_NO_DLL
            Catch ex As Exception
                ' Error: Dll does not exists or the Init function is not available
                '
                System.Windows.Forms.MessageBox.Show("Error: """ + ex.Message + """")
                Return CANResult.ERR_NO_DLL
            End Try
        End Function

        ' PCANLight ResetClient function
        ' This function delete the both queues (Transmit,Receive) of the CAN Controller
        ' using a RESET
        ' "HWType" = Hardware to reset
        ' RETURN = A CANResult value - Error/status of the hardware after execute the function
        '
        Public Shared Function ResetClient(ByVal HWType As HardwareType) As CANResult
            Try
                Select Case HWType
                    Case HardwareType.ISA_1CH
                        Return CType(PCAN_ISA.ResetClient(), CANResult)

                    Case HardwareType.ISA_2CH
                        Return CType(PCAN_2ISA.ResetClient(), CANResult)

                    Case HardwareType.PCI_1CH
                        Return CType(PCAN_PCI.ResetClient(), CANResult)

                    Case HardwareType.PCI_2CH
                        Return CType(PCAN_2PCI.ResetClient(), CANResult)

                    Case HardwareType.PCC_1CH
                        Return CType(PCAN_PCC.ResetClient(), CANResult)

                    Case HardwareType.PCC_2CH
                        Return CType(PCAN_2PCC.ResetClient(), CANResult)

                    Case HardwareType.USB_1CH
                        Return CType(PCAN_USB.ResetClient(), CANResult)

                    Case HardwareType.USB_2CH
                        Return CType(PCAN_2USB.ResetClient(), CANResult)

                    Case HardwareType.DNP
                        Return CType(PCAN_DNP.ResetClient(), CANResult)

                    Case HardwareType.DNG
                        Return CType(PCAN_DNG.ResetClient(), CANResult)

                    Case Else
                        ' Hardware is not valid for this function
                        '
                        Return CANResult.ERR_ILLHW
                End Select
            Catch ex As Exception
                ' Error: Dll does not exists or the Init function is not available
                '
                System.Windows.Forms.MessageBox.Show("Error: """ + ex.Message + """")
                Return CANResult.ERR_NO_DLL
            End Try
        End Function

        ' PCANLigth MsgFilter function
        ' This function set the receive message filter of the CAN Controller.
        ' REMARK:
        '   - A quick register of all messages is possible using the parameters From and To as 0
        ' 	- Every call of this function maybe cause an extention of the receive filter of the 
        '	  CAN controller, which one can go briefly to RESET
        '	- New in Ver 2.x:
        '		* Standard frames will be put it down in the acc_mask/code as Bits 28..13
        '		* Hardware driver for 82C200 must to be moved to Bits 10..0 again!
        ' WARNING:
        '		It is not guaranteed to receive ONLY the registered messages.
        ' "HWType" = Hardware which applay the filter to
        ' "FromId" = First/Start Message ID - It muss be smaller than the "To" parameter
        ' "ToId" = Last/Finish Message ID - It muss be bigger than the "From" parameter
        ' "MsgType" = Kind of Frame - Standard or Extended
        ' RETURN = A CANResult value - Error/status of the hardware after execute the function
        '
        Public Shared Function MsgFilter(ByVal HWType As HardwareType, ByVal FromId As Integer, ByVal ToId As Integer, ByVal MsgType As MsgTypes) As CANResult
            Try
                Select Case HWType
                    Case HardwareType.ISA_1CH
                        Return CType(PCAN_ISA.MsgFilter(FromId, ToId, MsgType), CANResult)

                    Case HardwareType.ISA_2CH
                        Return CType(PCAN_2ISA.MsgFilter(FromId, ToId, MsgType), CANResult)

                    Case HardwareType.PCI_1CH
                        Return CType(PCAN_PCI.MsgFilter(FromId, ToId, MsgType), CANResult)

                    Case HardwareType.PCI_2CH
                        Return CType(PCAN_2PCI.MsgFilter(FromId, ToId, MsgType), CANResult)

                    Case HardwareType.PCC_1CH
                        Return CType(PCAN_PCC.MsgFilter(FromId, ToId, MsgType), CANResult)

                    Case HardwareType.PCC_2CH
                        Return CType(PCAN_2PCC.MsgFilter(FromId, ToId, MsgType), CANResult)

                    Case HardwareType.USB_1CH
                        Return CType(PCAN_USB.MsgFilter(FromId, ToId, MsgType), CANResult)

                    Case HardwareType.USB_2CH
                        Return CType(PCAN_2USB.MsgFilter(FromId, ToId, MsgType), CANResult)

                    Case HardwareType.DNP
                        Return CType(PCAN_DNP.MsgFilter(FromId, ToId, MsgType), CANResult)

                    Case HardwareType.DNG
                        Return CType(PCAN_DNG.MsgFilter(FromId, ToId, MsgType), CANResult)

                    Case Else
                        ' Hardware is not valid for this function
                        '
                        Return CANResult.ERR_ILLHW
                End Select
            Catch ex As Exception
                ' Error: Dll does not exists or the Init function is not available
                '
                System.Windows.Forms.MessageBox.Show("Error: """ + ex.Message + """")
                Return CANResult.ERR_NO_DLL
            End Try
        End Function

        ' PCANLigth ResetFilter function
        ' This function close completely the Message Filter of the Hardware.
        ' They will be no more messages received.
        ' "HWType" = Hardware to reset its filter
        ' RETURN = A CANResult value - Error/status of the hardware after execute the function
        '
        Public Shared Function ResetFilter(ByVal HWType As HardwareType) As CANResult
            Try
                Select Case HWType
                    Case HardwareType.ISA_1CH
                        Return CType(PCAN_ISA.ResetFilter(), CANResult)

                    Case HardwareType.ISA_2CH
                        Return CType(PCAN_2ISA.ResetFilter(), CANResult)

                    Case HardwareType.PCI_1CH
                        Return CType(PCAN_PCI.ResetFilter(), CANResult)

                    Case HardwareType.PCI_2CH
                        Return CType(PCAN_2PCI.ResetFilter(), CANResult)

                    Case HardwareType.PCC_1CH
                        Return CType(PCAN_PCC.ResetFilter(), CANResult)

                    Case HardwareType.PCC_2CH
                        Return CType(PCAN_2PCC.ResetFilter(), CANResult)

                    Case HardwareType.USB_1CH
                        Return CType(PCAN_USB.ResetFilter(), CANResult)

                    Case HardwareType.USB_2CH
                        Return CType(PCAN_2USB.ResetFilter(), CANResult)

                    Case HardwareType.DNP
                        Return CType(PCAN_DNP.ResetFilter(), CANResult)

                    Case HardwareType.DNG
                        Return CType(PCAN_DNG.ResetFilter(), CANResult)

                    Case Else
                        ' Hardware is not valid for this function
                        '
                        Return CANResult.ERR_ILLHW
                End Select
            Catch ex As Exception
                ' Error: Dll does not exists or the Init function is not available
                '
                System.Windows.Forms.MessageBox.Show("Error: """ + ex.Message + """")
                Return CANResult.ERR_NO_DLL
            End Try
        End Function

        ' PCANLight SetUSBDeviceNr function
        ' This function set an identification number to the USB CAN hardware
        ' "HWType" = Hardware to set its Device Number
        ' "DeviceNumber" = Value to be set as Device Number
        ' RETURN = A CANResult value - Error/status of the hardware after execute the function
        '
        Public Shared Function SetUSBDeviceNr(ByVal HWType As HardwareType, ByVal DeviceNumber As Integer) As CANResult
            Try
                Select Case HWType
                    Case HardwareType.USB_1CH
                        Return CType(PCAN_USB.SetUSBDeviceNr(DeviceNumber), CANResult)
                    Case HardwareType.USB_2CH
                        Return CType(PCAN_2USB.SetUSBDeviceNr(DeviceNumber), CANResult)
                    Case Else
                        ' Hardware is not valid for this function
                        '
                        Return CANResult.ERR_ILLHW
                End Select

            Catch ex As Exception
                ' Error: Dll does not exists or the Init function is not available
                '
                System.Windows.Forms.MessageBox.Show("Error: """ + ex.Message + """")
                Return CANResult.ERR_NO_DLL
            End Try
        End Function

        ' PCANLight GetUSBDeviceNr function
        ' This function read the device number of a USB CAN Hardware
        ' "HWType" = Hardware to get the Device Number
        ' "DeviceNumber" = Variable to return the Device Number value
        ' RETURN = A CANResult value - Error/status of the hardware after execute the function
        '
        Public Shared Function GetUSBDeviceNr(ByVal HWType As HardwareType, ByRef DeviceNumber As Integer) As CANResult
            Try
                Select Case HWType
                    Case HardwareType.USB_1CH
                        Return CType(PCAN_USB.GetUSBDeviceNr(DeviceNumber), CANResult)
                    Case HardwareType.USB_2CH
                        Return CType(PCAN_2USB.GetUSBDeviceNr(DeviceNumber), CANResult)
                    Case Else
                        ' Hardware is not valid for this function
                        '
                        Return CANResult.ERR_ILLHW
                End Select
            Catch ex As Exception
                ' Error: Dll does not exists or the Init function is not available
                '
                System.Windows.Forms.MessageBox.Show("Error: """ + ex.Message + """")
                Return CANResult.ERR_NO_DLL
            End Try
        End Function

        ' PCANLight SetRcvEvent function
        ' This function is used to set the Event for the Event Handler
        ' "HWType" = Hardware that will set the Event
        ' "EventHandle" = The handle (ID) of the event to be set
        ' RETURN = A CANResult value - Error/status of the hardware after execute the function
        '
        Public Shared Function SetRcvEvent(ByVal HWType As HardwareType, ByVal EventHandle As System.Threading.EventWaitHandle) As Integer
            Dim hHandle As IntPtr

            Try
                ' If the EventHandle parameter is Nothing, a value of IntPtr::Zero is set in order to clear 
                ' the Event on the driver. Otherwise we get the internal Handle value representing the
                ' Receive-Event
                '
                If CType(EventHandle, Object) Is Nothing Then
                    hHandle = IntPtr.Zero
                Else
                    hHandle = EventHandle.SafeWaitHandle.DangerousGetHandle()
                End If

                Select Case HWType
                    Case HardwareType.ISA_1CH
                        Return CType(PCAN_ISA.SetRcvEvent(hHandle), CANResult)

                    Case HardwareType.ISA_2CH
                        Return CType(PCAN_2ISA.SetRcvEvent(hHandle), CANResult)

                    Case HardwareType.PCI_1CH
                        Return CType(PCAN_PCI.SetRcvEvent(hHandle), CANResult)

                    Case HardwareType.PCI_2CH
                        Return CType(PCAN_2PCI.SetRcvEvent(hHandle), CANResult)

                    Case HardwareType.PCC_1CH
                        Return CType(PCAN_PCC.SetRcvEvent(hHandle), CANResult)

                    Case HardwareType.PCC_2CH
                        Return CType(PCAN_2PCC.SetRcvEvent(hHandle), CANResult)

                    Case HardwareType.USB_1CH
                        Return CType(PCAN_USB.SetRcvEvent(hHandle), CANResult)

                    Case HardwareType.USB_2CH
                        Return CType(PCAN_2USB.SetRcvEvent(hHandle), CANResult)

                    Case HardwareType.DNP
                        Return CType(PCAN_DNP.SetRcvEvent(hHandle), CANResult)

                    Case HardwareType.DNG
                        Return CType(PCAN_DNG.SetRcvEvent(hHandle), CANResult)

                    Case Else
                        ' Hardware is not valid for this function
                        '
                        Return CANResult.ERR_ILLHW
                End Select
            Catch ex As EntryPointNotFoundException
                ' Function is not available in the loaded Dll
                '
                System.Windows.Forms.MessageBox.Show("Error: Wrong Version. """ + ex.Message + """")
                Return CANResult.ERR_NO_DLL
            Catch ex As Exception
                ' Error: Dll does not exists or the Init function is not available
                '
                System.Windows.Forms.MessageBox.Show("Error: """ + ex.Message + """")
                Return CANResult.ERR_NO_DLL
            End Try
        End Function
#End Region
#End Region
    End Class
#End Region
End Namespace

