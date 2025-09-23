Imports ICLRead.Peak.Can.Light
Imports System.Threading


Public Class Form1
    Inherits System.Windows.Forms.Form
    '  Save the current initiated hardware type
    '
    Dim ActiveHardware As HardwareType

    ' Thread in order to read messages using Received-Event method
    '
    Dim ReadThread As Thread

    '  Receive-Event
    '
    Dim RcvEvent As AutoResetEvent

    ' Read Delegate in order to call "ReadMessage" function
    ' using .NET invoke function
    Public Delegate Sub ReadDelegateHandler()

    ' Read Delegate in order to call "ReadMessage" function
    ' using .NET invoke function
    Dim ReadDelegate As ReadDelegateHandler


    Private WithEvents groupBox5 As System.Windows.Forms.GroupBox
    Private WithEvents rdbStandard As System.Windows.Forms.RadioButton
    Private WithEvents rdbExtended As System.Windows.Forms.RadioButton
    Private WithEvents txtIdTo As System.Windows.Forms.TextBox
    Private WithEvents txtIdFrom As System.Windows.Forms.TextBox
    Private WithEvents btnResetFilter As System.Windows.Forms.Button
    Private WithEvents btnSetFilter As System.Windows.Forms.Button
    Private WithEvents label10 As System.Windows.Forms.Label
    Private WithEvents label9 As System.Windows.Forms.Label
    Friend WithEvents btnSetUsbDevNumber As System.Windows.Forms.Button
    Friend WithEvents btnGetUsbDevNumber As System.Windows.Forms.Button
    Private WithEvents btnDllInfo As System.Windows.Forms.Button
    Private WithEvents chbTimeStamp As System.Windows.Forms.CheckBox
    Private WithEvents labelReadMethod As System.Windows.Forms.Label
    Private WithEvents rdbEvent As System.Windows.Forms.RadioButton
    Private WithEvents rdbTimer As System.Windows.Forms.RadioButton
    Friend WithEvents clhTime As System.Windows.Forms.ColumnHeader
    Private WithEvents txtDevNumber As System.Windows.Forms.TextBox
    ' CAN messages Array. Store the Message Status for its display
    '
    Dim LastMsgsList As ArrayList


#Region "Structures"
    ' Message Status structure used to show CAN Messages
    ' in a ListView
    '
    Structure MessageStatus
        Private Msg As TCLightMsg
        Private iIndex As Integer

        Public Sub New(ByVal CanMsg As TCLightMsg, ByVal Index As Integer)
            Msg = CanMsg
            iIndex = Index
        End Sub

        Public ReadOnly Property CANMessage() As TCLightMsg
            Get
                Return Msg
            End Get
        End Property

        Public ReadOnly Property Position() As Integer
            Get
                Return iIndex
            End Get
        End Property
    End Structure
#End Region

#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        Application.EnableVisualStyles()
        'This call is required by the Windows Form Designer.
        InitializeComponent()

        ' We set the variable to know which hardware is 
        ' currently selected (none!)
        '
        ActiveHardware = CType(-1, HardwareType)
        ' Create a list to store the displayed mesasges 
        '
        LastMsgsList = New ArrayList

    End Sub

    'Form overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    Friend WithEvents groupBox4 As System.Windows.Forms.GroupBox
    Friend WithEvents lstMessages As System.Windows.Forms.ListView
    Friend WithEvents clhType As System.Windows.Forms.ColumnHeader
    Friend WithEvents clhID As System.Windows.Forms.ColumnHeader
    Friend WithEvents clhLength As System.Windows.Forms.ColumnHeader
    Friend WithEvents clhData As System.Windows.Forms.ColumnHeader
    Friend WithEvents clhCount As System.Windows.Forms.ColumnHeader
    Friend WithEvents groupBox3 As System.Windows.Forms.GroupBox
    Friend WithEvents txtInfo As System.Windows.Forms.TextBox
    Friend WithEvents btnClose As System.Windows.Forms.Button
    Friend WithEvents groupBox2 As System.Windows.Forms.GroupBox
    Friend WithEvents chbRemote As System.Windows.Forms.CheckBox
    Friend WithEvents btnWrite As System.Windows.Forms.Button
    Friend WithEvents chbExtended As System.Windows.Forms.CheckBox
    Friend WithEvents label6 As System.Windows.Forms.Label
    Friend WithEvents label7 As System.Windows.Forms.Label
    Friend WithEvents label8 As System.Windows.Forms.Label
    Friend WithEvents txtID As System.Windows.Forms.TextBox
    Friend WithEvents txtData7 As System.Windows.Forms.TextBox
    Friend WithEvents txtData6 As System.Windows.Forms.TextBox
    Friend WithEvents txtData5 As System.Windows.Forms.TextBox
    Friend WithEvents txtData4 As System.Windows.Forms.TextBox
    Friend WithEvents txtData3 As System.Windows.Forms.TextBox
    Friend WithEvents txtData2 As System.Windows.Forms.TextBox
    Friend WithEvents txtData1 As System.Windows.Forms.TextBox
    Friend WithEvents txtData0 As System.Windows.Forms.TextBox
    Friend WithEvents nudLength As System.Windows.Forms.NumericUpDown
    Friend WithEvents groupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents cbbHws As System.Windows.Forms.ComboBox
    Friend WithEvents cbbMsgType As System.Windows.Forms.ComboBox
    Friend WithEvents cbbInterrupt As System.Windows.Forms.ComboBox
    Friend WithEvents label5 As System.Windows.Forms.Label
    Friend WithEvents cbbIO As System.Windows.Forms.ComboBox
    Friend WithEvents label4 As System.Windows.Forms.Label
    Friend WithEvents label3 As System.Windows.Forms.Label
    Friend WithEvents cbbBaudrates As System.Windows.Forms.ComboBox
    Friend WithEvents label2 As System.Windows.Forms.Label
    Friend WithEvents label1 As System.Windows.Forms.Label
    Friend WithEvents btnInfo As System.Windows.Forms.Button
    Friend WithEvents btnRelease As System.Windows.Forms.Button
    Friend WithEvents btnInit As System.Windows.Forms.Button
    Friend WithEvents tmrRead As System.Windows.Forms.Timer
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form1))
        Me.groupBox4 = New System.Windows.Forms.GroupBox
        Me.chbTimeStamp = New System.Windows.Forms.CheckBox
        Me.labelReadMethod = New System.Windows.Forms.Label
        Me.rdbEvent = New System.Windows.Forms.RadioButton
        Me.lstMessages = New System.Windows.Forms.ListView
        Me.clhType = New System.Windows.Forms.ColumnHeader
        Me.clhID = New System.Windows.Forms.ColumnHeader
        Me.clhLength = New System.Windows.Forms.ColumnHeader
        Me.clhData = New System.Windows.Forms.ColumnHeader
        Me.clhCount = New System.Windows.Forms.ColumnHeader
        Me.clhTime = New System.Windows.Forms.ColumnHeader
        Me.rdbTimer = New System.Windows.Forms.RadioButton
        Me.groupBox3 = New System.Windows.Forms.GroupBox
        Me.txtInfo = New System.Windows.Forms.TextBox
        Me.btnClose = New System.Windows.Forms.Button
        Me.groupBox2 = New System.Windows.Forms.GroupBox
        Me.chbRemote = New System.Windows.Forms.CheckBox
        Me.btnWrite = New System.Windows.Forms.Button
        Me.chbExtended = New System.Windows.Forms.CheckBox
        Me.label6 = New System.Windows.Forms.Label
        Me.label7 = New System.Windows.Forms.Label
        Me.label8 = New System.Windows.Forms.Label
        Me.txtID = New System.Windows.Forms.TextBox
        Me.txtData7 = New System.Windows.Forms.TextBox
        Me.txtData6 = New System.Windows.Forms.TextBox
        Me.txtData5 = New System.Windows.Forms.TextBox
        Me.txtData4 = New System.Windows.Forms.TextBox
        Me.txtData3 = New System.Windows.Forms.TextBox
        Me.txtData2 = New System.Windows.Forms.TextBox
        Me.txtData1 = New System.Windows.Forms.TextBox
        Me.txtData0 = New System.Windows.Forms.TextBox
        Me.nudLength = New System.Windows.Forms.NumericUpDown
        Me.groupBox1 = New System.Windows.Forms.GroupBox
        Me.btnDllInfo = New System.Windows.Forms.Button
        Me.btnSetUsbDevNumber = New System.Windows.Forms.Button
        Me.btnGetUsbDevNumber = New System.Windows.Forms.Button
        Me.cbbHws = New System.Windows.Forms.ComboBox
        Me.cbbMsgType = New System.Windows.Forms.ComboBox
        Me.cbbInterrupt = New System.Windows.Forms.ComboBox
        Me.label5 = New System.Windows.Forms.Label
        Me.cbbIO = New System.Windows.Forms.ComboBox
        Me.label4 = New System.Windows.Forms.Label
        Me.label3 = New System.Windows.Forms.Label
        Me.cbbBaudrates = New System.Windows.Forms.ComboBox
        Me.label2 = New System.Windows.Forms.Label
        Me.label1 = New System.Windows.Forms.Label
        Me.btnInfo = New System.Windows.Forms.Button
        Me.btnRelease = New System.Windows.Forms.Button
        Me.btnInit = New System.Windows.Forms.Button
        Me.tmrRead = New System.Windows.Forms.Timer(Me.components)
        Me.groupBox5 = New System.Windows.Forms.GroupBox
        Me.rdbStandard = New System.Windows.Forms.RadioButton
        Me.rdbExtended = New System.Windows.Forms.RadioButton
        Me.txtIdTo = New System.Windows.Forms.TextBox
        Me.txtIdFrom = New System.Windows.Forms.TextBox
        Me.btnResetFilter = New System.Windows.Forms.Button
        Me.btnSetFilter = New System.Windows.Forms.Button
        Me.label10 = New System.Windows.Forms.Label
        Me.label9 = New System.Windows.Forms.Label
        Me.txtDevNumber = New System.Windows.Forms.TextBox
        Me.groupBox4.SuspendLayout()
        Me.groupBox3.SuspendLayout()
        Me.groupBox2.SuspendLayout()
        CType(Me.nudLength, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.groupBox1.SuspendLayout()
        Me.groupBox5.SuspendLayout()
        Me.SuspendLayout()
        '
        'groupBox4
        '
        Me.groupBox4.Controls.Add(Me.chbTimeStamp)
        Me.groupBox4.Controls.Add(Me.labelReadMethod)
        Me.groupBox4.Controls.Add(Me.rdbEvent)
        Me.groupBox4.Controls.Add(Me.lstMessages)
        Me.groupBox4.Controls.Add(Me.rdbTimer)
        Me.groupBox4.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.groupBox4.Location = New System.Drawing.Point(8, 305)
        Me.groupBox4.Name = "groupBox4"
        Me.groupBox4.Size = New System.Drawing.Size(498, 164)
        Me.groupBox4.TabIndex = 50
        Me.groupBox4.TabStop = False
        Me.groupBox4.Text = "Read Messages"
        '
        'chbTimeStamp
        '
        Me.chbTimeStamp.AutoSize = True
        Me.chbTimeStamp.Checked = True
        Me.chbTimeStamp.CheckState = System.Windows.Forms.CheckState.Checked
        Me.chbTimeStamp.Enabled = False
        Me.chbTimeStamp.Location = New System.Drawing.Point(8, 141)
        Me.chbTimeStamp.Name = "chbTimeStamp"
        Me.chbTimeStamp.Size = New System.Drawing.Size(112, 17)
        Me.chbTimeStamp.TabIndex = 32
        Me.chbTimeStamp.Text = "Show Time Stamp"
        Me.chbTimeStamp.UseVisualStyleBackColor = True
        '
        'labelReadMethod
        '
        Me.labelReadMethod.AutoSize = True
        Me.labelReadMethod.Location = New System.Drawing.Point(7, 16)
        Me.labelReadMethod.Name = "labelReadMethod"
        Me.labelReadMethod.Size = New System.Drawing.Size(75, 13)
        Me.labelReadMethod.TabIndex = 31
        Me.labelReadMethod.Text = "Read Method:"
        '
        'rdbEvent
        '
        Me.rdbEvent.AutoSize = True
        Me.rdbEvent.Enabled = False
        Me.rdbEvent.Location = New System.Drawing.Point(159, 14)
        Me.rdbEvent.Name = "rdbEvent"
        Me.rdbEvent.Size = New System.Drawing.Size(68, 17)
        Me.rdbEvent.TabIndex = 30
        Me.rdbEvent.Text = "By Event"
        Me.rdbEvent.UseVisualStyleBackColor = True
        '
        'lstMessages
        '
        Me.lstMessages.Columns.AddRange(New System.Windows.Forms.ColumnHeader() {Me.clhType, Me.clhID, Me.clhLength, Me.clhData, Me.clhCount, Me.clhTime})
        Me.lstMessages.FullRowSelect = True
        Me.lstMessages.Location = New System.Drawing.Point(8, 37)
        Me.lstMessages.MultiSelect = False
        Me.lstMessages.Name = "lstMessages"
        Me.lstMessages.Size = New System.Drawing.Size(482, 98)
        Me.lstMessages.TabIndex = 28
        Me.lstMessages.UseCompatibleStateImageBehavior = False
        Me.lstMessages.View = System.Windows.Forms.View.Details
        '
        'clhType
        '
        Me.clhType.Text = "Type"
        Me.clhType.Width = 69
        '
        'clhID
        '
        Me.clhID.Text = "ID"
        Me.clhID.Width = 73
        '
        'clhLength
        '
        Me.clhLength.Text = "Length"
        Me.clhLength.Width = 50
        '
        'clhData
        '
        Me.clhData.Text = "Data"
        Me.clhData.Width = 138
        '
        'clhCount
        '
        Me.clhCount.Text = "Count"
        Me.clhCount.Width = 49
        '
        'clhTime
        '
        Me.clhTime.Text = "Rcv Time"
        Me.clhTime.Width = 97
        '
        'rdbTimer
        '
        Me.rdbTimer.AutoSize = True
        Me.rdbTimer.Checked = True
        Me.rdbTimer.Enabled = False
        Me.rdbTimer.Location = New System.Drawing.Point(89, 14)
        Me.rdbTimer.Name = "rdbTimer"
        Me.rdbTimer.Size = New System.Drawing.Size(66, 17)
        Me.rdbTimer.TabIndex = 29
        Me.rdbTimer.TabStop = True
        Me.rdbTimer.Text = "By Timer"
        Me.rdbTimer.UseVisualStyleBackColor = True
        '
        'groupBox3
        '
        Me.groupBox3.Controls.Add(Me.txtInfo)
        Me.groupBox3.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.groupBox3.Location = New System.Drawing.Point(8, 475)
        Me.groupBox3.Name = "groupBox3"
        Me.groupBox3.Size = New System.Drawing.Size(498, 72)
        Me.groupBox3.TabIndex = 49
        Me.groupBox3.TabStop = False
        Me.groupBox3.Text = "Information"
        '
        'txtInfo
        '
        Me.txtInfo.BackColor = System.Drawing.Color.White
        Me.txtInfo.Cursor = System.Windows.Forms.Cursors.Arrow
        Me.txtInfo.ImeMode = System.Windows.Forms.ImeMode.NoControl
        Me.txtInfo.Location = New System.Drawing.Point(8, 16)
        Me.txtInfo.Multiline = True
        Me.txtInfo.Name = "txtInfo"
        Me.txtInfo.ReadOnly = True
        Me.txtInfo.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.txtInfo.Size = New System.Drawing.Size(482, 48)
        Me.txtInfo.TabIndex = 38
        Me.txtInfo.TabStop = False
        Me.txtInfo.Text = "Select a Hardware and a configuration for it. Then click ""Initialize"" button"
        '
        'btnClose
        '
        Me.btnClose.Cursor = System.Windows.Forms.Cursors.Hand
        Me.btnClose.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnClose.Location = New System.Drawing.Point(450, 553)
        Me.btnClose.Name = "btnClose"
        Me.btnClose.Size = New System.Drawing.Size(56, 23)
        Me.btnClose.TabIndex = 48
        Me.btnClose.Text = "Close"
        '
        'groupBox2
        '
        Me.groupBox2.Controls.Add(Me.chbRemote)
        Me.groupBox2.Controls.Add(Me.btnWrite)
        Me.groupBox2.Controls.Add(Me.chbExtended)
        Me.groupBox2.Controls.Add(Me.label6)
        Me.groupBox2.Controls.Add(Me.label7)
        Me.groupBox2.Controls.Add(Me.label8)
        Me.groupBox2.Controls.Add(Me.txtID)
        Me.groupBox2.Controls.Add(Me.txtData7)
        Me.groupBox2.Controls.Add(Me.txtData6)
        Me.groupBox2.Controls.Add(Me.txtData5)
        Me.groupBox2.Controls.Add(Me.txtData4)
        Me.groupBox2.Controls.Add(Me.txtData3)
        Me.groupBox2.Controls.Add(Me.txtData2)
        Me.groupBox2.Controls.Add(Me.txtData1)
        Me.groupBox2.Controls.Add(Me.txtData0)
        Me.groupBox2.Controls.Add(Me.nudLength)
        Me.groupBox2.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.groupBox2.Location = New System.Drawing.Point(8, 137)
        Me.groupBox2.Name = "groupBox2"
        Me.groupBox2.Size = New System.Drawing.Size(498, 91)
        Me.groupBox2.TabIndex = 47
        Me.groupBox2.TabStop = False
        Me.groupBox2.Text = "Write Messages"
        '
        'chbRemote
        '
        Me.chbRemote.Cursor = System.Windows.Forms.Cursors.Hand
        Me.chbRemote.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.chbRemote.Location = New System.Drawing.Point(112, 64)
        Me.chbRemote.Name = "chbRemote"
        Me.chbRemote.Size = New System.Drawing.Size(112, 24)
        Me.chbRemote.TabIndex = 33
        Me.chbRemote.Text = "Remote Request"
        '
        'btnWrite
        '
        Me.btnWrite.Cursor = System.Windows.Forms.Cursors.Hand
        Me.btnWrite.Enabled = False
        Me.btnWrite.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnWrite.Location = New System.Drawing.Point(398, 38)
        Me.btnWrite.Name = "btnWrite"
        Me.btnWrite.Size = New System.Drawing.Size(92, 23)
        Me.btnWrite.TabIndex = 36
        Me.btnWrite.Text = "Write Message"
        '
        'chbExtended
        '
        Me.chbExtended.Cursor = System.Windows.Forms.Cursors.Hand
        Me.chbExtended.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.chbExtended.Location = New System.Drawing.Point(8, 64)
        Me.chbExtended.Name = "chbExtended"
        Me.chbExtended.Size = New System.Drawing.Size(112, 24)
        Me.chbExtended.TabIndex = 34
        Me.chbExtended.Text = "Extended Frame"
        '
        'label6
        '
        Me.label6.AutoSize = True
        Me.label6.Location = New System.Drawing.Point(144, 16)
        Me.label6.Name = "label6"
        Me.label6.Size = New System.Drawing.Size(60, 13)
        Me.label6.TabIndex = 32
        Me.label6.Text = "Data (0..7):"
        '
        'label7
        '
        Me.label7.AutoSize = True
        Me.label7.Location = New System.Drawing.Point(96, 16)
        Me.label7.Name = "label7"
        Me.label7.Size = New System.Drawing.Size(43, 13)
        Me.label7.TabIndex = 31
        Me.label7.Text = "Length:"
        '
        'label8
        '
        Me.label8.AutoSize = True
        Me.label8.Location = New System.Drawing.Point(8, 16)
        Me.label8.Name = "label8"
        Me.label8.Size = New System.Drawing.Size(49, 13)
        Me.label8.TabIndex = 30
        Me.label8.Text = "ID (Hex):"
        '
        'txtID
        '
        Me.txtID.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtID.Location = New System.Drawing.Point(8, 40)
        Me.txtID.MaxLength = 3
        Me.txtID.Name = "txtID"
        Me.txtID.Size = New System.Drawing.Size(80, 20)
        Me.txtID.TabIndex = 20
        Me.txtID.Text = "000"
        '
        'txtData7
        '
        Me.txtData7.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData7.Location = New System.Drawing.Point(368, 40)
        Me.txtData7.MaxLength = 2
        Me.txtData7.Name = "txtData7"
        Me.txtData7.Size = New System.Drawing.Size(24, 20)
        Me.txtData7.TabIndex = 29
        Me.txtData7.Text = "00"
        Me.txtData7.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData6
        '
        Me.txtData6.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData6.Location = New System.Drawing.Point(336, 40)
        Me.txtData6.MaxLength = 2
        Me.txtData6.Name = "txtData6"
        Me.txtData6.Size = New System.Drawing.Size(24, 20)
        Me.txtData6.TabIndex = 28
        Me.txtData6.Text = "00"
        Me.txtData6.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData5
        '
        Me.txtData5.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData5.Location = New System.Drawing.Point(304, 40)
        Me.txtData5.MaxLength = 2
        Me.txtData5.Name = "txtData5"
        Me.txtData5.Size = New System.Drawing.Size(24, 20)
        Me.txtData5.TabIndex = 27
        Me.txtData5.Text = "00"
        Me.txtData5.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData4
        '
        Me.txtData4.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData4.Location = New System.Drawing.Point(272, 40)
        Me.txtData4.MaxLength = 2
        Me.txtData4.Name = "txtData4"
        Me.txtData4.Size = New System.Drawing.Size(24, 20)
        Me.txtData4.TabIndex = 26
        Me.txtData4.Text = "00"
        Me.txtData4.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData3
        '
        Me.txtData3.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData3.Location = New System.Drawing.Point(240, 40)
        Me.txtData3.MaxLength = 2
        Me.txtData3.Name = "txtData3"
        Me.txtData3.Size = New System.Drawing.Size(24, 20)
        Me.txtData3.TabIndex = 25
        Me.txtData3.Text = "00"
        Me.txtData3.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData2
        '
        Me.txtData2.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData2.Location = New System.Drawing.Point(208, 40)
        Me.txtData2.MaxLength = 2
        Me.txtData2.Name = "txtData2"
        Me.txtData2.Size = New System.Drawing.Size(24, 20)
        Me.txtData2.TabIndex = 24
        Me.txtData2.Text = "00"
        Me.txtData2.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData1
        '
        Me.txtData1.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData1.Location = New System.Drawing.Point(176, 40)
        Me.txtData1.MaxLength = 2
        Me.txtData1.Name = "txtData1"
        Me.txtData1.Size = New System.Drawing.Size(24, 20)
        Me.txtData1.TabIndex = 23
        Me.txtData1.Text = "00"
        Me.txtData1.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'txtData0
        '
        Me.txtData0.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtData0.Location = New System.Drawing.Point(144, 40)
        Me.txtData0.MaxLength = 2
        Me.txtData0.Name = "txtData0"
        Me.txtData0.Size = New System.Drawing.Size(24, 20)
        Me.txtData0.TabIndex = 22
        Me.txtData0.Text = "00"
        Me.txtData0.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
        '
        'nudLength
        '
        Me.nudLength.BackColor = System.Drawing.Color.White
        Me.nudLength.Location = New System.Drawing.Point(96, 40)
        Me.nudLength.Maximum = New Decimal(New Integer() {8, 0, 0, 0})
        Me.nudLength.Name = "nudLength"
        Me.nudLength.ReadOnly = True
        Me.nudLength.Size = New System.Drawing.Size(40, 20)
        Me.nudLength.TabIndex = 21
        Me.nudLength.Value = New Decimal(New Integer() {8, 0, 0, 0})
        '
        'groupBox1
        '
        Me.groupBox1.Controls.Add(Me.txtDevNumber)
        Me.groupBox1.Controls.Add(Me.btnDllInfo)
        Me.groupBox1.Controls.Add(Me.btnSetUsbDevNumber)
        Me.groupBox1.Controls.Add(Me.btnGetUsbDevNumber)
        Me.groupBox1.Controls.Add(Me.cbbHws)
        Me.groupBox1.Controls.Add(Me.cbbMsgType)
        Me.groupBox1.Controls.Add(Me.cbbInterrupt)
        Me.groupBox1.Controls.Add(Me.label5)
        Me.groupBox1.Controls.Add(Me.cbbIO)
        Me.groupBox1.Controls.Add(Me.label4)
        Me.groupBox1.Controls.Add(Me.label3)
        Me.groupBox1.Controls.Add(Me.cbbBaudrates)
        Me.groupBox1.Controls.Add(Me.label2)
        Me.groupBox1.Controls.Add(Me.label1)
        Me.groupBox1.Controls.Add(Me.btnInfo)
        Me.groupBox1.Controls.Add(Me.btnRelease)
        Me.groupBox1.Controls.Add(Me.btnInit)
        Me.groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.groupBox1.Location = New System.Drawing.Point(8, 8)
        Me.groupBox1.Name = "groupBox1"
        Me.groupBox1.Size = New System.Drawing.Size(498, 123)
        Me.groupBox1.TabIndex = 46
        Me.groupBox1.TabStop = False
        Me.groupBox1.Text = "Connection"
        '
        'btnDllInfo
        '
        Me.btnDllInfo.Cursor = System.Windows.Forms.Cursors.Hand
        Me.btnDllInfo.Enabled = False
        Me.btnDllInfo.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnDllInfo.Location = New System.Drawing.Point(332, 89)
        Me.btnDllInfo.Name = "btnDllInfo"
        Me.btnDllInfo.Size = New System.Drawing.Size(87, 23)
        Me.btnDllInfo.TabIndex = 48
        Me.btnDllInfo.Text = "Get Dll Version"
        Me.btnDllInfo.UseVisualStyleBackColor = True
        '
        'btnSetUsbDevNumber
        '
        Me.btnSetUsbDevNumber.Location = New System.Drawing.Point(8, 89)
        Me.btnSetUsbDevNumber.Name = "btnSetUsbDevNumber"
        Me.btnSetUsbDevNumber.Size = New System.Drawing.Size(140, 23)
        Me.btnSetUsbDevNumber.TabIndex = 46
        Me.btnSetUsbDevNumber.Text = "Set USB Device Number"
        Me.btnSetUsbDevNumber.UseVisualStyleBackColor = True
        '
        'btnGetUsbDevNumber
        '
        Me.btnGetUsbDevNumber.Location = New System.Drawing.Point(8, 60)
        Me.btnGetUsbDevNumber.Name = "btnGetUsbDevNumber"
        Me.btnGetUsbDevNumber.Size = New System.Drawing.Size(140, 23)
        Me.btnGetUsbDevNumber.TabIndex = 45
        Me.btnGetUsbDevNumber.Text = "Get USB Device Number"
        Me.btnGetUsbDevNumber.UseVisualStyleBackColor = True
        '
        'cbbHws
        '
        Me.cbbHws.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cbbHws.Items.AddRange(New Object() {"ISA", "ISA 2-CH", "PCI", "PCI 2-CH", "PCC", "PCC 2-CH", "USB 1-CH", "USB 2-CH", "DONGLE PRO", "DONGLE"})
        Me.cbbHws.Location = New System.Drawing.Point(8, 32)
        Me.cbbHws.Name = "cbbHws"
        Me.cbbHws.Size = New System.Drawing.Size(112, 21)
        Me.cbbHws.TabIndex = 32
        '
        'cbbMsgType
        '
        Me.cbbMsgType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cbbMsgType.Items.AddRange(New Object() {"Standard", "Extended"})
        Me.cbbMsgType.Location = New System.Drawing.Point(228, 33)
        Me.cbbMsgType.Name = "cbbMsgType"
        Me.cbbMsgType.Size = New System.Drawing.Size(88, 21)
        Me.cbbMsgType.TabIndex = 37
        '
        'cbbInterrupt
        '
        Me.cbbInterrupt.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cbbInterrupt.Items.AddRange(New Object() {"3", "4", "5", "7", "9", "10", "11", "12", "15"})
        Me.cbbInterrupt.Location = New System.Drawing.Point(402, 34)
        Me.cbbInterrupt.Name = "cbbInterrupt"
        Me.cbbInterrupt.Size = New System.Drawing.Size(88, 21)
        Me.cbbInterrupt.TabIndex = 39
        '
        'label5
        '
        Me.label5.Location = New System.Drawing.Point(402, 18)
        Me.label5.Name = "label5"
        Me.label5.Size = New System.Drawing.Size(72, 23)
        Me.label5.TabIndex = 44
        Me.label5.Text = "Interrupt:"
        '
        'cbbIO
        '
        Me.cbbIO.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cbbIO.Items.AddRange(New Object() {"0100", "0120", "0140", "0200", "0220", "0240", "0260", "0278", "0280", "02A0", "02C0", "02E0", "02E8", "02F8", "0300", "0320", "0340", "0360", "0378", "0380", "03BC", "03E0", "03E8", "03F8"})
        Me.cbbIO.Location = New System.Drawing.Point(322, 34)
        Me.cbbIO.Name = "cbbIO"
        Me.cbbIO.Size = New System.Drawing.Size(74, 21)
        Me.cbbIO.TabIndex = 38
        '
        'label4
        '
        Me.label4.Location = New System.Drawing.Point(322, 18)
        Me.label4.Name = "label4"
        Me.label4.Size = New System.Drawing.Size(72, 23)
        Me.label4.TabIndex = 43
        Me.label4.Text = "I/O Address:"
        '
        'label3
        '
        Me.label3.Location = New System.Drawing.Point(228, 17)
        Me.label3.Name = "label3"
        Me.label3.Size = New System.Drawing.Size(64, 23)
        Me.label3.TabIndex = 42
        Me.label3.Text = "Msg Type:"
        '
        'cbbBaudrates
        '
        Me.cbbBaudrates.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cbbBaudrates.Items.AddRange(New Object() {"1 MBit/sec", "500 KBit/sec", "250 KBit/sec", "125 KBit/sec", "100 KBit/sec", "50 KBit/sec", "20 KBit/sec", "10 KBit/sec", "5 KBit/sec"})
        Me.cbbBaudrates.Location = New System.Drawing.Point(126, 33)
        Me.cbbBaudrates.Name = "cbbBaudrates"
        Me.cbbBaudrates.Size = New System.Drawing.Size(96, 21)
        Me.cbbBaudrates.TabIndex = 36
        '
        'label2
        '
        Me.label2.Location = New System.Drawing.Point(126, 17)
        Me.label2.Name = "label2"
        Me.label2.Size = New System.Drawing.Size(56, 23)
        Me.label2.TabIndex = 41
        Me.label2.Text = "Baudrate:"
        '
        'label1
        '
        Me.label1.Location = New System.Drawing.Point(7, 16)
        Me.label1.Name = "label1"
        Me.label1.Size = New System.Drawing.Size(56, 23)
        Me.label1.TabIndex = 40
        Me.label1.Text = "Hardware:"
        '
        'btnInfo
        '
        Me.btnInfo.Cursor = System.Windows.Forms.Cursors.Hand
        Me.btnInfo.Enabled = False
        Me.btnInfo.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnInfo.Location = New System.Drawing.Point(238, 89)
        Me.btnInfo.Name = "btnInfo"
        Me.btnInfo.Size = New System.Drawing.Size(88, 23)
        Me.btnInfo.TabIndex = 33
        Me.btnInfo.Text = "Get Info"
        '
        'btnRelease
        '
        Me.btnRelease.Cursor = System.Windows.Forms.Cursors.Hand
        Me.btnRelease.Enabled = False
        Me.btnRelease.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnRelease.Location = New System.Drawing.Point(425, 89)
        Me.btnRelease.Name = "btnRelease"
        Me.btnRelease.Size = New System.Drawing.Size(65, 23)
        Me.btnRelease.TabIndex = 35
        Me.btnRelease.Text = "Release"
        '
        'btnInit
        '
        Me.btnInit.Cursor = System.Windows.Forms.Cursors.Hand
        Me.btnInit.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnInit.Location = New System.Drawing.Point(425, 61)
        Me.btnInit.Name = "btnInit"
        Me.btnInit.Size = New System.Drawing.Size(65, 23)
        Me.btnInit.TabIndex = 34
        Me.btnInit.Text = "Initialize"
        '
        'tmrRead
        '
        Me.tmrRead.Interval = 50
        '
        'groupBox5
        '
        Me.groupBox5.Controls.Add(Me.rdbStandard)
        Me.groupBox5.Controls.Add(Me.rdbExtended)
        Me.groupBox5.Controls.Add(Me.txtIdTo)
        Me.groupBox5.Controls.Add(Me.txtIdFrom)
        Me.groupBox5.Controls.Add(Me.btnResetFilter)
        Me.groupBox5.Controls.Add(Me.btnSetFilter)
        Me.groupBox5.Controls.Add(Me.label10)
        Me.groupBox5.Controls.Add(Me.label9)
        Me.groupBox5.Location = New System.Drawing.Point(8, 234)
        Me.groupBox5.Name = "groupBox5"
        Me.groupBox5.Size = New System.Drawing.Size(498, 65)
        Me.groupBox5.TabIndex = 51
        Me.groupBox5.TabStop = False
        Me.groupBox5.Text = "Message Filter"
        '
        'rdbStandard
        '
        Me.rdbStandard.AutoSize = True
        Me.rdbStandard.Checked = True
        Me.rdbStandard.Location = New System.Drawing.Point(8, 34)
        Me.rdbStandard.Name = "rdbStandard"
        Me.rdbStandard.Size = New System.Drawing.Size(68, 17)
        Me.rdbStandard.TabIndex = 71
        Me.rdbStandard.TabStop = True
        Me.rdbStandard.Text = "Standard"
        Me.rdbStandard.UseVisualStyleBackColor = True
        '
        'rdbExtended
        '
        Me.rdbExtended.AutoSize = True
        Me.rdbExtended.Location = New System.Drawing.Point(82, 34)
        Me.rdbExtended.Name = "rdbExtended"
        Me.rdbExtended.Size = New System.Drawing.Size(70, 17)
        Me.rdbExtended.TabIndex = 70
        Me.rdbExtended.Text = "Extended"
        Me.rdbExtended.UseVisualStyleBackColor = True
        '
        'txtIdTo
        '
        Me.txtIdTo.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtIdTo.Location = New System.Drawing.Point(260, 34)
        Me.txtIdTo.MaxLength = 3
        Me.txtIdTo.Name = "txtIdTo"
        Me.txtIdTo.Size = New System.Drawing.Size(90, 20)
        Me.txtIdTo.TabIndex = 67
        Me.txtIdTo.Text = "0"
        '
        'txtIdFrom
        '
        Me.txtIdFrom.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper
        Me.txtIdFrom.Location = New System.Drawing.Point(164, 34)
        Me.txtIdFrom.MaxLength = 3
        Me.txtIdFrom.Name = "txtIdFrom"
        Me.txtIdFrom.Size = New System.Drawing.Size(90, 20)
        Me.txtIdFrom.TabIndex = 66
        Me.txtIdFrom.Text = "0"
        '
        'btnResetFilter
        '
        Me.btnResetFilter.Cursor = System.Windows.Forms.Cursors.Hand
        Me.btnResetFilter.Enabled = False
        Me.btnResetFilter.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnResetFilter.Location = New System.Drawing.Point(434, 31)
        Me.btnResetFilter.Name = "btnResetFilter"
        Me.btnResetFilter.Size = New System.Drawing.Size(56, 23)
        Me.btnResetFilter.TabIndex = 64
        Me.btnResetFilter.Text = "Reset"
        '
        'btnSetFilter
        '
        Me.btnSetFilter.Cursor = System.Windows.Forms.Cursors.Hand
        Me.btnSetFilter.Enabled = False
        Me.btnSetFilter.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.btnSetFilter.Location = New System.Drawing.Point(372, 31)
        Me.btnSetFilter.Name = "btnSetFilter"
        Me.btnSetFilter.Size = New System.Drawing.Size(56, 23)
        Me.btnSetFilter.TabIndex = 63
        Me.btnSetFilter.Text = "Set"
        '
        'label10
        '
        Me.label10.Location = New System.Drawing.Point(260, 15)
        Me.label10.Name = "label10"
        Me.label10.Size = New System.Drawing.Size(56, 23)
        Me.label10.TabIndex = 62
        Me.label10.Text = "To:"
        '
        'label9
        '
        Me.label9.Location = New System.Drawing.Point(161, 15)
        Me.label9.Name = "label9"
        Me.label9.Size = New System.Drawing.Size(56, 23)
        Me.label9.TabIndex = 61
        Me.label9.Text = "From:"
        '
        'txtDevNumber
        '
        Me.txtDevNumber.Enabled = False
        Me.txtDevNumber.Location = New System.Drawing.Point(157, 91)
        Me.txtDevNumber.MaxLength = 10
        Me.txtDevNumber.Name = "txtDevNumber"
        Me.txtDevNumber.Size = New System.Drawing.Size(72, 20)
        Me.txtDevNumber.TabIndex = 51
        Me.txtDevNumber.Text = "0"
        '
        'Form1
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(514, 584)
        Me.Controls.Add(Me.groupBox5)
        Me.Controls.Add(Me.groupBox4)
        Me.Controls.Add(Me.groupBox3)
        Me.Controls.Add(Me.btnClose)
        Me.Controls.Add(Me.groupBox2)
        Me.Controls.Add(Me.groupBox1)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MaximizeBox = False
        Me.Name = "Form1"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "I CAN Do It! - Light"
        Me.groupBox4.ResumeLayout(False)
        Me.groupBox4.PerformLayout()
        Me.groupBox3.ResumeLayout(False)
        Me.groupBox3.PerformLayout()
        Me.groupBox2.ResumeLayout(False)
        Me.groupBox2.PerformLayout()
        CType(Me.nudLength, System.ComponentModel.ISupportInitialize).EndInit()
        Me.groupBox1.ResumeLayout(False)
        Me.groupBox1.PerformLayout()
        Me.groupBox5.ResumeLayout(False)
        Me.groupBox5.PerformLayout()
        Me.ResumeLayout(False)

    End Sub

#End Region

#Region "Miscellaneous Help Functions"
    Private Sub ModifyMsgEntry(ByVal LastMsg As MessageStatus, ByVal NewMsg As TCLightMsg, ByVal MyTimeStamp As TCLightTimestamp)
        Dim strLastData, strNewData As String
        Dim NewStatus As MessageStatus
        Dim CurrItem As ListViewItem
        Dim iLen, iCount As Integer
        Dim timeStampInfo As String

        strNewData = ""
        strLastData = ""

        ' Values from the last Messages
        '
        CurrItem = lstMessages.Items.Item(LastMsg.Position)
        iCount = Convert.ToInt32(CurrItem.SubItems.Item(4).Text)
        strLastData = CurrItem.SubItems.Item(3).Text
        iLen = LastMsg.CANMessage.Len

        ' New values
        '
        If (NewMsg.MsgType And MsgTypes.MSGTYPE_RTR) <> 0 Then
            strNewData = "Remote Request"
        Else
            For I As Integer = 0 To NewMsg.Len - 1
                strNewData += String.Format("{0:X2} ", NewMsg.DATA(I))
            Next
        End If

        ' Count and Time are updated
        '
        iCount += 1

        ' Set the changes
        '
        If iLen <> NewMsg.Len Then
            iLen = NewMsg.Len
            CurrItem.SubItems.Item(2).Text = iLen.ToString()
        End If

        If strLastData <> strNewData Then
            CurrItem.SubItems.Item(3).Text = strNewData
        End If

        CurrItem.SubItems.Item(4).Text = iCount.ToString()

        ' Update time stamp information if need be
        '
        If (MyTimeStamp IsNot Nothing) Then

            timeStampInfo = MyTimeStamp.millis.ToString() & "." & MyTimeStamp.micros.ToString()

            ' Add new SubItem if it doesn't exists
            '
            If (CurrItem.SubItems.Count = 5) Then
                CurrItem.SubItems.Add(timeStampInfo)
            Else
                CurrItem.SubItems(5).Text = timeStampInfo
            End If
        End If

        ' Save the new Status of the message
        ' NOTE: The objects are saved in the same index position which
        ' they use in the Listview
        '
        NewStatus = New MessageStatus(NewMsg, LastMsg.Position)
        LastMsgsList.RemoveAt(LastMsg.Position)
        LastMsgsList.Insert(LastMsg.Position, NewStatus)
    End Sub

    Private Sub InsertMsgEntry(ByVal NewMsg As TCLightMsg, ByVal MyTimeStamp As TCLightTimestamp)
        Dim strNewData, strTemp As String
        Dim CurrItem As ListViewItem
        Dim CurrMsg As MessageStatus
        Dim timeStampInfo As String

        strTemp = ""
        strNewData = ""

        ' Add the new ListView Item with the Type of the message
        '
        If CBool(NewMsg.MsgType And CInt(MsgTypes.MSGTYPE_EXTENDED <> 0)) Then
            strTemp = "EXTENDED"
        Else
            strTemp = "STANDARD"
        End If

        If CBool(NewMsg.MsgType And CInt(MsgTypes.MSGTYPE_RTR = MsgTypes.MSGTYPE_RTR)) Then
            strTemp += "/RTR"
        End If

        CurrItem = lstMessages.Items.Add(strTemp)

        ' We format the ID of the message and show it
        '
        If CBool(NewMsg.MsgType And CInt(MsgTypes.MSGTYPE_EXTENDED <> 0)) Then
            CurrItem.SubItems.Add(String.Format("{0:X8}h", NewMsg.ID))
        Else
            CurrItem.SubItems.Add(String.Format("{0:X3}h", NewMsg.ID))
        End If

        ' We set the length of the Message
        '
        CurrItem.SubItems.Add(NewMsg.Len.ToString())

        ' We format the data of the message. Each data is one
        ' byte of Hexadecimal data
        ' 
        If CBool((NewMsg.MsgType And MsgTypes.MSGTYPE_RTR) = MsgTypes.MSGTYPE_RTR) Then
            strNewData = "Remote Request"
        Else
            For I As Integer = 0 To NewMsg.Len - 1
                strNewData += String.Format("{0:X2} ", NewMsg.DATA(I))
            Next
        End If

        CurrItem.SubItems.Add(strNewData)

        ' The message is the First, so count is 1 and there
        ' is not any time difference between messages.
        '
        CurrItem.SubItems.Add("1")

        ' Update time stamp information if need be
        '
        If (MyTimeStamp IsNot Nothing) Then
            timeStampInfo = MyTimeStamp.millis.ToString() & "." & MyTimeStamp.micros.ToString()
            CurrItem.SubItems.Add(timeStampInfo)
        End If

        ' We add this status in the last message list
        '
        CurrMsg = New MessageStatus(NewMsg, CurrItem.Index)
        LastMsgsList.Add(CurrMsg)
    End Sub

    Private Sub ProcessMessage(ByVal MyMsg As TCLightMsg, ByVal MyTimeStamp As TCLightTimestamp)
        Dim bFound As Boolean = False
        Dim CurrMessage As MessageStatus

        ' Initialization
        '
        CurrMessage = New MessageStatus

        ' We search if a message (Smae ID, Type and same Net) is
        ' already received or if this is a new message
        '
        For I As Integer = 0 To LastMsgsList.Count - 1
            CurrMessage = CType(LastMsgsList(I), MessageStatus)
            If CurrMessage.CANMessage.ID = MyMsg.ID Then
                If CurrMessage.CANMessage.MsgType = MyMsg.MsgType Then
                    bFound = True
                    Exit For
                End If
            End If
        Next

        If bFound Then
            ' Messages of this kind are already received; we make an update
            '
            ModifyMsgEntry(CurrMessage, MyMsg, MyTimeStamp)
        Else
            ' Messages of this kind are not received; we make a new entry
            '
            InsertMsgEntry(MyMsg, MyTimeStamp)
        End If
    End Sub

    ' This helper function retrieve active Dll Major version number
    '
    Private Function DllMajorVersion(ByVal HWType As HardwareType, ByRef majorVersion As Integer) As CANResult
        Dim Res As CANResult
        Dim dllVersionStr As String = ""
        Dim versionTabInfo As String()
        ' We execute the "DllVersionInfo" function of the PCANLight
        ' using as parameter the Hardware type and a string
        ' variable to get the info like "x.xx"
        '

        Res = PCANLight.DllVersionInfo(HWType, dllVersionStr)

        ' We retrieve major version number 
        ' spliting versionNumberStr based on "." decimal symbol
        '
        versionTabInfo = dllVersionStr.Split("."c)
        If (versionTabInfo.Length > 0) Then
            Integer.TryParse(versionTabInfo(0), majorVersion)
        End If

        Return Res
    End Function

    ' This helper function retrieve active Dll Major version number
    '
    Private Sub CANReadThreadFunc()
        ' Sets the handle of the Receive-Event.
        '
        PCANLight.SetRcvEvent(ActiveHardware, RcvEvent)

        ' While this mode is selected
        '
        While (rdbEvent.Checked)

            ' Waiting for Receive-Event
            ' 
            RcvEvent.WaitOne()

            ' Process Receive-Event using .NET Invoke function
            ' in order to interact with Winforms UI
            ' 
            Me.Invoke(ReadDelegate)
        End While
    End Sub

    Private Sub ReadMessage()

        Dim MyMsg As TCLightMsg = Nothing
        Dim MyTimeStamp As TCLightTimestamp = Nothing
        Dim Res As CANResult

        ' We read at least one time the queue looking for messages.
        ' If a message is found, we look again trying to find more.
        ' If the queue is empty or an error occurr, we get out from
        ' the dowhile statement.
        '			
        Do
            ' We read the queue looking for messages.
            '
            If (chbTimeStamp.Checked) Then
                ' We execute the "ReadEx" function of the PCANLight
                ' if "Show Time Stamp" checkbox is selected
                '
                Res = PCANLight.ReadEx(ActiveHardware, MyMsg, MyTimeStamp)
            Else
                ' We execute the "Read" function of the PCANLight
                ' if "Show Time Stamp" checkbox isn't selected
                '
                Res = PCANLight.Read(ActiveHardware, MyMsg)

                ' A message was received
                ' We process the message(s)
                '
            End If

            ' Process Message
            '
            If (Res = CANResult.ERR_OK) Then
                ProcessMessage(MyMsg, MyTimeStamp)
            End If
        Loop While ((ActiveHardware <> 1) And ((Res And CANResult.ERR_QRCVEMPTY) = 0))
    End Sub

    ' This help function assign the same function to the PressKey 
    ' event of the Data fields
    '
    Private Sub AssignEvents()
        AddHandler txtData0.KeyPress, AddressOf Me.txtID_KeyPress
        AddHandler txtData1.KeyPress, AddressOf Me.txtID_KeyPress
        AddHandler txtData2.KeyPress, AddressOf Me.txtID_KeyPress
        AddHandler txtData3.KeyPress, AddressOf Me.txtID_KeyPress
        AddHandler txtData4.KeyPress, AddressOf Me.txtID_KeyPress
        AddHandler txtData5.KeyPress, AddressOf Me.txtID_KeyPress
        AddHandler txtData6.KeyPress, AddressOf Me.txtID_KeyPress
        AddHandler txtData7.KeyPress, AddressOf Me.txtID_KeyPress
        AddHandler txtData1.Leave, AddressOf Me.txtData0_Leave
        AddHandler txtData2.Leave, AddressOf Me.txtData0_Leave
        AddHandler txtData3.Leave, AddressOf Me.txtData0_Leave
        AddHandler txtData4.Leave, AddressOf Me.txtData0_Leave
        AddHandler txtData5.Leave, AddressOf Me.txtData0_Leave
        AddHandler txtData6.Leave, AddressOf Me.txtData0_Leave
        AddHandler txtData7.Leave, AddressOf Me.txtData0_Leave
        AddHandler rdbTimer.CheckedChanged, AddressOf Me.rdbTimer_CheckedChanged
        AddHandler chbTimeStamp.CheckedChanged, AddressOf Me.chbTimeStamp_CheckedChanged
    End Sub
#End Region

    Private Sub Form1_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles MyBase.Load
        ' Set the standard values in the interface
        '
        cbbHws.SelectedIndex = 0
        cbbBaudrates.SelectedIndex = 0
        cbbIO.Text = "0378"
        cbbInterrupt.Text = "7"
        cbbMsgType.SelectedIndex = 0

        ' Set common event handlers
        '
        AssignEvents()

        ' Create Delegates to use invoke() function
        '
        ReadDelegate = New ReadDelegateHandler(AddressOf ReadMessage)

        ' Create AutoResetEvent to use PCLight SetRcvEvent() function
        '
        RcvEvent = New AutoResetEvent(False)
    End Sub

    Private Sub Form1_Closing(ByVal sender As Object, ByVal e As System.ComponentModel.CancelEventArgs) Handles MyBase.Closing
        ' If we are reading, we stop to read
        '
        tmrRead.Enabled = False
    End Sub

    Private Sub cbbHws_SelectedIndexChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles cbbHws.SelectedIndexChanged
        Dim bShowIO As Boolean
        Dim current As HardwareType

        current = CType(cbbHws.SelectedIndex, HardwareType)

        ' According with the selection in the Hardware list, 
        ' we show/hide the input controls for I/O Address and 
        ' Interrupt. (This parameters are NOT necessary for all 
        ' hardware types) .
        '
        Select Case current
            Case HardwareType.DNG
                bShowIO = True
            Case HardwareType.DNP
                bShowIO = True
            Case HardwareType.ISA_1CH
                bShowIO = True
            Case HardwareType.ISA_2CH
                bShowIO = True
            Case Else
                bShowIO = False
        End Select

        cbbIO.Enabled = bShowIO
        cbbInterrupt.Enabled = bShowIO

        ' According with the selection in the Hardware list, we 
        ' Enable/Disable the controls for Get/Set the USB device Number.
        '
        btnGetUsbDevNumber.Enabled = ((current = HardwareType.USB_1CH) Or (current = HardwareType.USB_2CH)) And btnWrite.Enabled
        btnSetUsbDevNumber.Enabled = btnGetUsbDevNumber.Enabled
        txtDevNumber.Enabled = btnGetUsbDevNumber.Enabled
    End Sub

    Private Sub cbbBaudrates_SelectedIndexChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles cbbBaudrates.SelectedIndexChanged
        ' We save the corresponding Baudrate enumeration 
        ' type value for every selected Baudrate from the 
        ' list.
        '
        Select Case cbbBaudrates.SelectedIndex
            Case 0
                cbbBaudrates.Tag = Baudrates.BAUD_1M
            Case 1
                cbbBaudrates.Tag = Baudrates.BAUD_500K
            Case 2
                cbbBaudrates.Tag = Baudrates.BAUD_250K
            Case 3
                cbbBaudrates.Tag = Baudrates.BAUD_125K
            Case 4
                cbbBaudrates.Tag = Baudrates.BAUD_100K
            Case 5
                cbbBaudrates.Tag = Baudrates.BAUD_50K
            Case 6
                cbbBaudrates.Tag = Baudrates.BAUD_20K
            Case 7
                cbbBaudrates.Tag = Baudrates.BAUD_10K
            Case 8
                cbbBaudrates.Tag = Baudrates.BAUD_5K
            Case Else
                cbbBaudrates.Tag = 0
        End Select
    End Sub

    Private Sub txtID_KeyPress(ByVal sender As Object, ByVal e As System.Windows.Forms.KeyPressEventArgs) Handles txtID.KeyPress, txtIdFrom.KeyPress, txtIdTo.KeyPress
        Dim iCheck As Byte

        ' We convert the Character to its Upper case equivalent and 
        ' get its numeric value
        '
        iCheck = Convert.ToByte(Char.ToUpper(e.KeyChar))

        ' The Key is the Delete (Backspace) Key
        '
        If iCheck = 8 Then
            Exit Sub
        End If

        ' The Key is a number between 0-9
        '
        If iCheck > 47 And iCheck < 58 Then
            Return
        End If

        ' The Key is a character between A-F
        '
        If iCheck > 64 And iCheck < 71 Then
            Return
        End If

        ' Is neither a number nor a character between A(a) and F(f)
        '
        e.Handled = True
    End Sub

    Private Sub txtID_Leave(ByVal sender As Object, ByVal e As System.EventArgs) Handles txtID.Leave
        Dim TextLength, MaxValue As Integer

        ' Calculate the text length and Maximum ID value according
        ' with the Message Type
        '
        If chbExtended.Checked Then
            TextLength = 8
            MaxValue = &H1FFFFFFF
        Else
            TextLength = 3
            MaxValue = &H7FF
        End If

        ' The Textbox for the ID is represented with 3 characters for 
        ' Standard and 8 characters for extended messages.
        ' Therefore if the Length of the text is smaller than TextLength,  
        ' we add "0"
        '
        While txtID.Text.Length <> TextLength
            txtID.Text = "0" + txtID.Text
        End While

        ' Because in this example will be sent only Standard messages
        ' we check that the ID is not bigger than 0x7FF
        '
        If Convert.ToInt32(txtID.Text, 16) > MaxValue Then
            txtID.Text = String.Format("{0:X" + TextLength.ToString() + "}", MaxValue)
        End If
    End Sub

    Private Sub txtData0_Leave(ByVal sender As Object, ByVal e As System.EventArgs) Handles txtData0.Leave
        Dim CurrentTextbox As TextBox

        ' All the Textbox Data fields are represented with 2 characters.
        ' Therefore if the Length of the text is smaller than 2, we add
        ' a "0"
        '
        If sender.GetType().Name = "TextBox" Then
            CurrentTextbox = CType(sender, TextBox)
            While CurrentTextbox.Text.Length <> 2
                CurrentTextbox.Text = "0" + CurrentTextbox.Text
            End While
        End If
    End Sub

    Private Sub nudLength_ValueChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles nudLength.ValueChanged
        Dim CurrentTextBox As TextBox

        CurrentTextBox = txtData0

        ' We enable so much TextBox Data fields as the length of the
        ' message will be, that is the value of the UpDown control
        '
        For I As Integer = 0 To 7
            CurrentTextBox.Enabled = I < nudLength.Value
            If I < 7 Then
                CurrentTextBox = CType(Me.GetNextControl(CurrentTextBox, True), TextBox)
                If CurrentTextBox Is Nothing Then
                    Exit For
                End If
            End If
        Next
    End Sub

    Private Sub chbExtended_CheckedChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles chbExtended.CheckedChanged
        Dim iTemp As Integer

        If chbExtended.Checked Then
            txtID.MaxLength = 8
        Else
            txtID.MaxLength = 3
        End If

        If txtID.Text.Length > txtID.MaxLength Then
            iTemp = Convert.ToInt32(txtID.Text, 16)
            If iTemp < &H7FF Then
                txtID.Text = String.Format("{0:X3}", iTemp)
            Else
                txtID.Text = "7FF"
            End If
        End If

        txtID_Leave(txtID, New EventArgs)
    End Sub

    Private Sub chbRemote_CheckedChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles chbRemote.CheckedChanged
        Dim CurrentTextBox As TextBox

        CurrentTextBox = txtData0

        ' We enable so much TextBox Data fields as the length of the
        ' message will be, that is the value of the UpDown control.
        '
        For I As Integer = 0 To 7
            CurrentTextBox.Visible = Not chbRemote.Checked
            If I < 7 Then
                CurrentTextBox = CType(Me.GetNextControl(CurrentTextBox, True), TextBox)
                If CurrentTextBox Is Nothing Then
                    Exit Sub
                End If
            End If
        Next
    End Sub

    Private Sub txtInfo_DoubleClick(ByVal sender As Object, ByVal e As System.EventArgs) Handles txtInfo.DoubleClick
        ' We clear the Information edit box
        '
        txtInfo.Text = ""
    End Sub

    Private Sub lstMessages_DoubleClick(ByVal sender As Object, ByVal e As System.EventArgs) Handles lstMessages.DoubleClick
        lstMessages.Items.Clear()
        LastMsgsList.Clear()
    End Sub

    Private Sub tmrRead_Tick(ByVal sender As Object, ByVal e As System.EventArgs) Handles tmrRead.Tick
        ReadMessage()
    End Sub

    Private Sub btnInfo_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnInfo.Click
        Dim strInfo As String
        Dim Res As CANResult

        ' We execute the "VersionInfo" function of the PCANLight 
        ' using as parameter the Hardware type and a string 
        ' variable to get the info.
        ' 
        strInfo = String.Empty
        Res = PCANLight.VersionInfo(CType(cbbHws.SelectedIndex, HardwareType), strInfo)
        strInfo = strInfo.Replace(vbLf, vbCrLf)

        ' The function was successfully executed
        '			
        If (Res = CANResult.ERR_OK) Then
            ' We show the Version Information
            '
            txtInfo.Text = strInfo
        Else
            ' An error occurred.  We show the error.
            '
            txtInfo.Text = "Error: " + Res.ToString()
        End If

    End Sub

    Private Sub btnInit_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnInit.Click
        Dim Res As CANResult
        Dim majorVersion As Integer = 0

        ' Check version 2.x Dll is available
        '
        Res = DllMajorVersion(CType(cbbHws.SelectedIndex, HardwareType), majorVersion)
        If (Res = CANResult.ERR_OK) Then
            ' Sample must ONLY work if a 2.x or later version of the
            ' PCAN-Light is installed
            '
            If (majorVersion < 2) Then
                MessageBox.Show("DLL 2.x or later are required to run new features available since PCAN-Light version 2.0." _
                & vbCrLf & "Please, download lastest DLL version or refer to the documentation for more information.", "DLL Version", MessageBoxButtons.OK, MessageBoxIcon.Warning)
            Else

                ' According with the active parameters/hardware, we
                ' use one of the two possible "Init" PCANLight functions.
                ' One is for Plug And Play hardware, and the other for
                ' Not P&P.
                '
                If (cbbIO.Enabled) Then
                    ' Not P&P Hardware
                    '
                    Res = PCANLight.Init(CType(cbbHws.SelectedIndex, HardwareType), CType(cbbBaudrates.Tag(), Baudrates), CType(cbbMsgType.SelectedIndex, FramesType), Convert.ToInt32(cbbIO.Text, 16), Convert.ToByte(cbbInterrupt.Text))
                Else
                    ' Not P&P Hardware
                    '
                    Res = PCANLight.Init(CType(cbbHws.SelectedIndex, HardwareType), CType(cbbBaudrates.Tag(), Baudrates), CType(cbbMsgType.SelectedIndex, FramesType))
                End If


                ' The Hardware was successfully initiated
                '
                If (Res = CANResult.ERR_OK) Then
                    ' We save the hardware type which is currently 
                    ' initiated
                    '
                    ActiveHardware = CType(cbbHws.SelectedIndex, HardwareType)

                    ' We start to read from the CAN Queue
                    '
                    tmrRead.Enabled = True

                    ' We set UI enable
                    '
                    rdbTimer.Enabled = True
                    rdbEvent.Enabled = True
                    chbTimeStamp.Checked = True
                    chbTimeStamp.Enabled = True
                    btnWrite.Enabled = True
                    btnRelease.Enabled = True
                    btnInit.Enabled = False
                    btnSetFilter.Enabled = True
                    btnResetFilter.Enabled = True
                    btnInfo.Enabled = True
                    btnDllInfo.Enabled = True
                    cbbHws_SelectedIndexChanged(Me, New EventArgs())

                    ' We show the information of the configured 
                    ' and initiated hardware
                    '
                    txtInfo.Text = "Active Hardware: " + cbbHws.Text
                    txtInfo.Text += vbCrLf + "Baud Rate: " + cbbBaudrates.Text
                    txtInfo.Text += vbCrLf + "Frame Type: " + cbbMsgType.Text
                    ' If was a no P&P Hardware, we show additional information
                    '
                    If (cbbIO.Enabled) Then
                        txtInfo.Text += vbCrLf + "I/O Addr.: " + cbbIO.Text + "h"
                        txtInfo.Text += vbCrLf + "Interrupt: " + cbbInterrupt.Text
                    End If
                Else
                    ' An error occurred.  We show the error.
                    '
                    txtInfo.Text = "Error: " + Res.ToString()
                End If
            End If
        Else
            txtInfo.Text = "Error: " + Res.ToString()
        End If
    End Sub

    Private Sub btnRelease_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles btnRelease.Click
        Dim Res As CANResult

        ' We choose Timer method by default
        '
        rdbTimer.Checked = True

        ' We stopt to read from tehe CAN Queue
        '
        tmrRead.Enabled = False

        ' We close the active hardware using the 
        ' "Close" function of the PCANLight using 
        ' as parameter the Hardware type.
        '
        Res = PCANLight.Close(ActiveHardware)

        If (Res = CANResult.ERR_OK) Then
            ' The Hardware was successfully closed
            '
            txtInfo.Text = "Hardware was successfully Released." + vbCrLf
        Else
            ' An error occurred.  We show the error.
            '
            txtInfo.Text = "Error: " + Res.ToString()
        End If

        ' We set the varibale of active hardware to None
        ' and activate/deactivate the corresponding buttons
        '
        ActiveHardware = CType(-1, HardwareType)
        btnInit.Enabled = True
        btnWrite.Enabled = False
        btnRelease.Enabled = False
        btnSetFilter.Enabled = False
        btnResetFilter.Enabled = False
        btnInfo.Enabled = False
        btnDllInfo.Enabled = False
        rdbTimer.Enabled = False
        rdbEvent.Enabled = False
        chbTimeStamp.Checked = False
        chbTimeStamp.Enabled = False
        cbbHws_SelectedIndexChanged(Me, New EventArgs())
    End Sub

    Private Sub btnWrite_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles btnWrite.Click
        Dim Res As CANResult
        Dim CurrentTextBox As TextBox
        Dim MsgToSend As TCLightMsg

        MsgToSend = New TCLightMsg

        ' We configurate the Message.  The ID (max 0x1FF),
        ' Length of the Data, Message Type (Standard in 
        ' this example) and die data
        '
        MsgToSend.ID = Convert.ToInt32(txtID.Text, 16)
        MsgToSend.Len = Convert.ToByte(nudLength.Value)
        If (chbExtended.Checked) Then
            MsgToSend.MsgType = MsgTypes.MSGTYPE_EXTENDED
        Else
            MsgToSend.MsgType = MsgTypes.MSGTYPE_STANDARD
        End If

        ' If a remote frame will be sent, the data bytes are not important.
        '
        If (chbRemote.Checked) Then
            MsgToSend.MsgType = MsgToSend.MsgType Or MsgTypes.MSGTYPE_RTR
        Else
            ' We get so much data as the Len of the message
            '
            CurrentTextBox = txtData0
            For I As Integer = 0 To MsgToSend.Len - 1
                MsgToSend.DATA(I) = Convert.ToByte(Convert.ToInt32(CurrentTextBox.Text, 16))
                If (I < 7) Then
                    CurrentTextBox = CType(Me.GetNextControl(CurrentTextBox, True), TextBox)
                End If
            Next
        End If

        ' The message is sent to the configured hardware
        '
        Res = PCANLight.Write(ActiveHardware, MsgToSend)


        If (Res = CANResult.ERR_OK) Then
            ' The Hardware was successfully sent
            '
            txtInfo.Text = "Message was successfully SENT." + vbCrLf
        Else
            ' An error occurred.  We show the error.
            '
            txtInfo.Text = "Error: " + Res.ToString()
        End If
    End Sub

    Private Sub btnClose_Click(ByVal sender As Object, ByVal e As System.EventArgs) Handles btnClose.Click
        ' We terminate the application
        '
        Close()
    End Sub

    Private Sub rdbStandard_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles rdbStandard.CheckedChanged
        Dim uiTemp As UInteger

        If rdbExtended.Checked Then
            txtIdFrom.MaxLength = 8
        Else
            txtIdFrom.MaxLength = 3
        End If

        txtIdTo.MaxLength = txtIdFrom.MaxLength

        ' the only way that the text length can be bigger als MaxLength
        ' is when the change is from Extended to Standard message Type.
        ' We have to handle this and set an ID not bigger than the Maximum
        ' ID value for a Standard Message (0x7FF)
        '
        If txtIdFrom.Text.Length > txtIdFrom.MaxLength Then
            uiTemp = Convert.ToUInt32(txtIdFrom.Text, 16)
            If uiTemp < &H7FF Then
                txtIdFrom.Text = String.Format("{0:X3}", uiTemp)
            Else
                txtIdFrom.Text = "7FF"
            End If
        End If
        If txtIdTo.Text.Length > txtIdTo.MaxLength Then
            uiTemp = Convert.ToUInt32(txtIdTo.Text, 16)
            If uiTemp < &H7FF Then
                txtIdTo.Text = String.Format("{0:X3}", uiTemp)
            Else
                txtIdTo.Text = "7FF"
            End If
        End If
    End Sub

    Private Sub txtIdFrom_Leave(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtIdFrom.Leave, txtIdTo.Leave
        Dim TextLength As Integer
        Dim MaxValue As UInteger
        Dim IdBox As TextBox

        IdBox = CType(sender, TextBox)
        ' calculate the text length and Maximum ID value according
        ' with the Message Type
        '
        If rdbExtended.Checked Then
            TextLength = 8
            MaxValue = &H1FFFFFFF
        Else
            TextLength = 3
            MaxValue = &H7FF
        End If

        ' The Textbox for the ID is represented with 3 characters for 
        ' Standard and 8 characters for extended messages.
        ' Therefore if the Length of the text is smaller than TextLength,  
        ' we add "0"
        '
        While Not (IdBox.Text.Length = TextLength)
            IdBox.Text = "0" + IdBox.Text
        End While

        ' Because in this example will be sent only Standard messages
        ' we check that the ID is not bigger than 0x7FF
        '
        If Convert.ToUInt32(IdBox.Text, 16) > MaxValue Then
            IdBox.Text = String.Format("{0:X" + TextLength.ToString() + "}", MaxValue)
        End If
    End Sub

    Private Sub btnSetFilter_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnSetFilter.Click
        Dim FromId, ToId As Integer
        Dim Res As CANResult

        ' The range IDs is read
        '
        FromId = Convert.ToInt32(txtIdFrom.Text, 16)
        ToId = Convert.ToInt32(txtIdTo.Text, 16)

        ' The desired Filter is set on the configured Hardware
        '
        If rdbStandard.Checked Then
            Res = PCANLight.MsgFilter(ActiveHardware, FromId, ToId, MsgTypes.MSGTYPE_STANDARD)
        Else
            Res = PCANLight.MsgFilter(ActiveHardware, FromId, ToId, MsgTypes.MSGTYPE_EXTENDED)
        End If

        ' The Filter was successfully set
        '
        If Res = CANResult.ERR_OK Then
            txtInfo.Text = "Filter was successfully SET." + vbCrLf
        Else
            ' An error occurred.  We show the error.
            '			
            txtInfo.Text = "Error: " + Res.ToString()
        End If
    End Sub

    Private Sub btnResetFilter_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnResetFilter.Click
        Dim Res As CANResult

        ' The current Filter on the configured Hardware is reset 
        '
        Res = PCANLight.ResetFilter(ActiveHardware)

        ' The Filter was successfully reset
        '
        If Res = CANResult.ERR_OK Then
            txtInfo.Text = "Filter was successfully RESET." + vbCrLf
        Else
            ' An error occurred.  We show the error.
            '			
            txtInfo.Text = "Error: " + Res.ToString()
        End If
    End Sub

    Private Sub btnGetUsbDevNumber_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnGetUsbDevNumber.Click
        Dim i As Integer
        Dim Res As CANResult

        ' The USB Device Number will asked 
        '
        Res = PCANLight.GetUSBDeviceNr(CType(cbbHws.SelectedIndex, HardwareType), i)

        ' The Device number was got successfully
        '
        If Res = CANResult.ERR_OK Then
            MessageBox.Show("USB Device Number is: " + i.ToString(), "GetUSBDevNr")
            ' An error occurred.  We show the error.
            '			
        Else
            MessageBox.Show("Get USB Device Number failed: " + Res.ToString(), "GetUSBDevNr")
        End If
    End Sub

    Private Sub btnSetUsbDevNumber_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnSetUsbDevNumber.Click
        Dim Res As CANResult

        ' The USB Device Number will asked 
        '
        Res = PCANLight.SetUSBDeviceNr(CType(cbbHws.SelectedIndex, HardwareType), CInt(txtDevNumber.Text))

        ' The Device number was got successfully
        '
        If Res = CANResult.ERR_OK Then
            MessageBox.Show("USB Device Number was set", "GetUSBDevNr")
            ' An error occurred.  We show the error.
            '			
        Else
            MessageBox.Show("Set USB Device Number failed: " + Res.ToString(), "GetUSBDevNr")
        End If
    End Sub

    Private Sub btnDllInfo_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnDllInfo.Click
        Dim strInfo As String
        Dim Res As CANResult

        ' We execute the "VersionInfo" function of the PCANLight 
        ' using as parameter the Hardware type and a string 
        ' variable to get the info.
        ' 
        strInfo = String.Empty
        Res = PCANLight.DllVersionInfo(CType(cbbHws.SelectedIndex, HardwareType), strInfo)

        ' The function was successfully executed
        '			
        If (Res = CANResult.ERR_OK) Then
            ' We show the Version Information
            '
            strInfo = strInfo.Replace(vbLf, vbCrLf)
            txtInfo.Text = cbbHws.SelectedItem.ToString() & " Dll Version: " & strInfo
        Else
            ' An error occurred.  We show the error.
            '
            txtInfo.Text = "Error: " + Res.ToString()
        End If
    End Sub

    Private Sub rdbTimer_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs)

        ' Thread Start
        '
        Dim threadDelegate As ThreadStart

        If (rdbTimer.Checked) Then
            ' Abort Read Thread if it exists
            '
            If (ReadThread IsNot Nothing) Then
                ReadThread.Abort()
                ReadThread.Join()
                ReadThread = Nothing
            End If

            ' Enable Timer
            '
            tmrRead.Enabled = True
        Else
            ' Disable Timer
            '
            tmrRead.Enabled = False
            ' Create and start the tread to read CAN Message using SetRcvEvent()
            '
            threadDelegate = New ThreadStart(AddressOf CANReadThreadFunc)
            ReadThread = New Thread(threadDelegate)
            ReadThread.Start()
        End If
    End Sub

    Private Sub chbTimeStamp_CheckedChanged(ByVal sender As System.Object, ByVal e As System.EventArgs)

        If (chbTimeStamp.Checked) Then

            ' Add Rcv Time column
            '
            If (Not (lstMessages.Columns.Contains(clhTime))) Then
                lstMessages.Columns.Add(clhTime)
            End If
        Else
            ' Remove Rcv Time column
            '
            If (lstMessages.Columns.Contains(clhTime)) Then
                lstMessages.Columns.Remove(clhTime)
            End If
        End If
    End Sub

    Private Sub Form1_FormClosing(ByVal sender As System.Object, ByVal e As System.Windows.Forms.FormClosingEventArgs) Handles MyBase.FormClosing
        ' Clean Up
        '
        If (btnRelease.Enabled) Then
            btnRelease_Click(Nothing, Nothing)
        End If

        ' If we are reading, we stop to read
        '
        tmrRead.Enabled = False
    End Sub

    Private Sub txtDevNumber_Leave(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles txtDevNumber.Leave
        If (txtDevNumber.Text = "") Then
            txtDevNumber.Text = "0"
        End If
        If (Convert.ToUInt64(txtDevNumber.Text) > Int32.MaxValue) Then
            txtDevNumber.Text = Int32.MaxValue.ToString()
        End If
    End Sub

    Private Sub txtDevNumber_KeyPress(ByVal sender As System.Object, ByVal e As System.Windows.Forms.KeyPressEventArgs) Handles txtDevNumber.KeyPress
        ' The Key is the Delete (Backspace) Key
        '
        If AscW(e.KeyChar) = 8 Then
            Exit Sub
        End If

        ' The Key is a number between 0-9
        '
        If (AscW(e.KeyChar) > 47) And (AscW(e.KeyChar) < 58) Then
            Return
        End If

        ' Is neither a number nor a character between A(a) and F(f)
        '
        e.Handled = True
    End Sub
End Class
