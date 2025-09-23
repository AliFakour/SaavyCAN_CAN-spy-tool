object Form1: TForm1
  Left = 266
  Top = 110
  Width = 520
  Height = 610
  Caption = 'I CAN Do It! - Light'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    0000010004000000000000020000000000000000000000000000000000000000
    0000000080000080000000808000800000008000800080800000C0C0C0008080
    80000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    007700000000000000000000000000000FF70000000000000000000000000000
    08F7088888888888000000000000033338F7087777777777800000000000030B
    B8F7087777777777780000000000037BB8F7087FFFFFF777778000000000030B
    B8F70870F000F777777800000000037BB8F70870F0FFF777777780000000030B
    B8F7087000FFF7778F7778000000037BB8F7087FFFFFF7778F78F7800000030B
    B8F708700000F7778F78F780B300037BB8F70870F0F0F7778F78F780B300030B
    B8F70870FFF0F7178F78F780B300037BB8F7087FFFFFF9918F78F780B300030B
    B8F7087F0000F7978F78F780B300037BB8F70870F0FFF7778F78F780B300030B
    B8F7087F0000F7778F78F780B300037BB8F7087FFFFFF7778F78F780F300030B
    B8F708700000F7778F7778008800037BB8F7087FF0FFF777777780000000030B
    B8F708700F00F77777780000000003BBB8F7087FFFFFF77777800000000003FF
    F8F7087777777777780000000000008888F708F7F7F7F7F78000000000000000
    88F708FFFFFFFFF800000000000000008F880888888888880000000000000000
    888800000000000000000000000000000880000000000000000000000000FFFF
    1FC7FFFE078FFFFCE01FFCF9F87FF879FFFFF0000FFFC00007FF800003FF8000
    01FF800000FF8000007F8000003F8000001F8000000380000003800000038000
    00038000000380000003800000038000000380000003800000038000003F8000
    007F800000FF800001FFC00003FFF00007FFF0000FFFF0FFFFFFF9FFFFFF}
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 498
    Height = 137
    Caption = 'Connection'
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 16
      Width = 49
      Height = 13
      Caption = 'Hardware:'
    end
    object Label2: TLabel
      Left = 120
      Top = 16
      Width = 46
      Height = 13
      Caption = 'Baudrate:'
    end
    object Label3: TLabel
      Left = 224
      Top = 16
      Width = 50
      Height = 13
      Caption = 'Msg Type:'
    end
    object Label4: TLabel
      Left = 320
      Top = 16
      Width = 60
      Height = 13
      Caption = 'I/O Address:'
    end
    object Label5: TLabel
      Left = 400
      Top = 16
      Width = 42
      Height = 13
      Caption = 'Interrupt:'
    end
    object cbbHws: TComboBox
      Left = 8
      Top = 32
      Width = 105
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 0
      OnChange = cbbHwsChange
      Items.Strings = (
        'ISA'
        'ISA 2-CH'
        'PCI'
        'PCI 2-CH'
        'PCC'
        'PCC 2-CH'
        'USB 1-CH'
        'USB 2-CH'
        'DONGLE PRO'
        'DONGLE')
    end
    object btnInfo: TButton
      Left = 232
      Top = 96
      Width = 88
      Height = 23
      Cursor = crHandPoint
      Caption = 'Get info'
      Enabled = False
      TabOrder = 1
      OnClick = btnInfoClick
    end
    object btnInit: TButton
      Left = 432
      Top = 64
      Width = 56
      Height = 23
      Cursor = crHandPoint
      Caption = 'Initialize'
      TabOrder = 2
      OnClick = btnInitClick
    end
    object btnRelease: TButton
      Left = 432
      Top = 96
      Width = 56
      Height = 23
      Cursor = crHandPoint
      Caption = 'Release'
      Enabled = False
      TabOrder = 3
      OnClick = btnReleaseClick
    end
    object cbbBaudrates: TComboBox
      Left = 120
      Top = 32
      Width = 96
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 4
      OnChange = cbbBaudratesChange
      Items.Strings = (
        '1 MBit/sec'
        '500 KBit/sec'
        '250 KBit/sec'
        '125 KBit/sec'
        '100 KBit/sec'
        '50 KBit/sec'
        '20 KBit/sec'
        '10 KBit/sec'
        '5 KBit/sec')
    end
    object cbbMsgType: TComboBox
      Left = 224
      Top = 32
      Width = 88
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 5
      Items.Strings = (
        'Standard'
        'Extended')
    end
    object cbbIO: TComboBox
      Left = 320
      Top = 32
      Width = 73
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 6
      Items.Strings = (
        '0100'
        '0120'
        '0140'
        '0200'
        '0220'
        '0240'
        '0260'
        '0278'
        '0280'
        '02A0'
        '02C0'
        '02E0'
        '02E8'
        '02F8'
        '0300'
        '0320'
        '0340'
        '0360'
        '0378'
        '0380'
        '03BC'
        '03E0'
        '03E8'
        '03F8')
    end
    object cbbInterrupt: TComboBox
      Left = 400
      Top = 32
      Width = 88
      Height = 21
      Style = csDropDownList
      ItemHeight = 13
      TabOrder = 7
      Items.Strings = (
        '3'
        '4'
        '5'
        '7'
        '9'
        '10'
        '11'
        '12'
        '15')
    end
    object btnGetDeviceNumber: TButton
      Left = 8
      Top = 64
      Width = 138
      Height = 25
      Caption = 'Get USB Device Number'
      Enabled = False
      TabOrder = 8
      OnClick = btnGetDeviceNumberClick
    end
    object btnSetDeviceNumber: TButton
      Left = 8
      Top = 96
      Width = 138
      Height = 25
      Caption = 'Set USB Device Number'
      Enabled = False
      TabOrder = 9
      OnClick = btnSetDeviceNumberClick
    end
    object ediDeviceNumber: TEdit
      Left = 152
      Top = 97
      Width = 73
      Height = 21
      Enabled = False
      MaxLength = 10
      TabOrder = 10
      Text = '0'
      OnExit = ediDeviceNumberExit
      OnKeyPress = ediDeviceNumberKeyPress
    end
    object btnDllInfo: TButton
      Left = 328
      Top = 96
      Width = 97
      Height = 23
      Cursor = crHandPoint
      Caption = 'Get Dll Version'
      Enabled = False
      TabOrder = 11
      OnClick = btnDllInfoClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 150
    Width = 498
    Height = 94
    Caption = 'Write Messages'
    TabOrder = 1
    object Label6: TLabel
      Left = 8
      Top = 16
      Width = 42
      Height = 13
      Caption = 'ID (Hex):'
    end
    object Label7: TLabel
      Left = 96
      Top = 16
      Width = 36
      Height = 13
      Caption = 'Length:'
    end
    object Label8: TLabel
      Left = 144
      Top = 16
      Width = 53
      Height = 13
      Caption = 'Data (0..7):'
    end
    object txtID: TEdit
      Left = 8
      Top = 40
      Width = 80
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 3
      TabOrder = 0
      Text = '0'
      OnExit = txtIDExit
      OnKeyPress = txtIDKeyPress
    end
    object nudLength: TUpDown
      Left = 121
      Top = 40
      Width = 16
      Height = 21
      Associate = txtLength
      Min = 0
      Max = 8
      Position = 8
      TabOrder = 1
      Thousands = False
      Wrap = False
      OnClick = nudLengthClick
    end
    object txtLength: TEdit
      Left = 96
      Top = 40
      Width = 25
      Height = 21
      ReadOnly = True
      TabOrder = 2
      Text = '8'
    end
    object txtData0: TEdit
      Left = 144
      Top = 40
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 2
      TabOrder = 3
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIDKeyPress
    end
    object txtData1: TEdit
      Left = 176
      Top = 40
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 2
      TabOrder = 4
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIDKeyPress
    end
    object txtData2: TEdit
      Left = 208
      Top = 40
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 2
      TabOrder = 5
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIDKeyPress
    end
    object txtData3: TEdit
      Left = 240
      Top = 40
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 2
      TabOrder = 6
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIDKeyPress
    end
    object txtData4: TEdit
      Left = 272
      Top = 40
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 2
      TabOrder = 7
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIDKeyPress
    end
    object txtData5: TEdit
      Left = 304
      Top = 40
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 2
      TabOrder = 8
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIDKeyPress
    end
    object txtData6: TEdit
      Left = 336
      Top = 40
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 2
      TabOrder = 9
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIDKeyPress
    end
    object txtData7: TEdit
      Left = 368
      Top = 40
      Width = 24
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 2
      TabOrder = 10
      Text = '00'
      OnExit = txtData0Exit
      OnKeyPress = txtIDKeyPress
    end
    object chbExtended: TCheckBox
      Left = 8
      Top = 69
      Width = 97
      Height = 17
      Caption = 'Extended Frame'
      TabOrder = 11
      OnClick = chbExtendedClick
    end
    object chbRemote: TCheckBox
      Left = 112
      Top = 69
      Width = 97
      Height = 17
      Caption = 'Remote Request'
      TabOrder = 12
      OnClick = chbRemoteClick
    end
    object btnWrite: TButton
      Left = 400
      Top = 40
      Width = 88
      Height = 23
      Cursor = crHandPoint
      Caption = 'Write Message'
      Enabled = False
      TabOrder = 13
      OnClick = btnWriteClick
    end
  end
  object GroupBox5: TGroupBox
    Left = 8
    Top = 246
    Width = 498
    Height = 60
    Caption = 'Information'
    TabOrder = 2
    object Label9: TLabel
      Left = 168
      Top = 11
      Width = 26
      Height = 13
      Caption = 'From:'
    end
    object Label10: TLabel
      Left = 264
      Top = 11
      Width = 16
      Height = 13
      Caption = 'To:'
    end
    object rdbStandard: TRadioButton
      Left = 8
      Top = 29
      Width = 89
      Height = 17
      Caption = 'Standard'
      Checked = True
      TabOrder = 0
      TabStop = True
      OnClick = rdbStandardClick
    end
    object rdbExtended: TRadioButton
      Left = 80
      Top = 29
      Width = 89
      Height = 17
      Caption = 'Extended'
      TabOrder = 1
      OnClick = rdbStandardClick
    end
    object txtIdFrom: TEdit
      Left = 168
      Top = 26
      Width = 90
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 3
      TabOrder = 2
      Text = '0'
      OnExit = txtIdFromExit
      OnKeyPress = txtIDKeyPress
    end
    object txtIdTo: TEdit
      Left = 264
      Top = 26
      Width = 90
      Height = 21
      CharCase = ecUpperCase
      MaxLength = 3
      TabOrder = 3
      Text = '0'
      OnExit = txtIdFromExit
      OnKeyPress = txtIDKeyPress
    end
    object btnSetFilter: TButton
      Left = 368
      Top = 26
      Width = 56
      Height = 23
      Cursor = crHandPoint
      Caption = 'Set'
      Enabled = False
      TabOrder = 4
      OnClick = btnSetFilterClick
    end
    object btnResetFilter: TButton
      Left = 432
      Top = 26
      Width = 56
      Height = 23
      Cursor = crHandPoint
      Caption = 'Reset'
      Enabled = False
      TabOrder = 5
      OnClick = btnResetFilterClick
    end
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 312
    Width = 498
    Height = 153
    Caption = 'Read Messages'
    TabOrder = 3
    object labelReadMethod: TLabel
      Left = 8
      Top = 16
      Width = 68
      Height = 13
      Caption = 'Read Method:'
    end
    object lstMessages: TListView
      Left = 8
      Top = 36
      Width = 481
      Height = 88
      Columns = <
        item
          Caption = 'Type'
          Width = 69
        end
        item
          Caption = 'ID'
          Width = 73
        end
        item
          Caption = 'Length'
        end
        item
          Caption = 'Data'
          Width = 138
        end
        item
          Caption = 'Count'
          Width = 49
        end
        item
          Caption = 'Rcv Time'
          Width = 90
        end>
      ReadOnly = True
      RowSelect = True
      TabOrder = 0
      ViewStyle = vsReport
      OnDblClick = lstMessagesDblClick
    end
    object chbTimeStamp: TCheckBox
      Left = 8
      Top = 128
      Width = 129
      Height = 17
      Caption = 'Show Time Stamp'
      Checked = True
      Enabled = False
      State = cbChecked
      TabOrder = 1
      OnClick = chbTimeStampClick
    end
    object rdbTimer: TRadioButton
      Left = 80
      Top = 16
      Width = 73
      Height = 17
      Caption = 'By Timer'
      Checked = True
      Enabled = False
      TabOrder = 2
      TabStop = True
      OnClick = rdbTimerClick
    end
    object rdbEvent: TRadioButton
      Left = 152
      Top = 16
      Width = 73
      Height = 17
      Caption = 'By Event'
      Enabled = False
      TabOrder = 3
      OnClick = rdbTimerClick
    end
  end
  object GroupBox4: TGroupBox
    Left = 8
    Top = 467
    Width = 498
    Height = 72
    Caption = 'Information'
    TabOrder = 4
    object txtInfo: TMemo
      Left = 8
      Top = 16
      Width = 481
      Height = 48
      Cursor = crArrow
      TabStop = False
      Lines.Strings = (
        
          'Select a Hardware and a configuration for it. Then click "Initia' +
          'lize" button')
      ReadOnly = True
      ScrollBars = ssVertical
      TabOrder = 0
      OnDblClick = txtInfoDblClick
    end
  end
  object btnClose: TButton
    Left = 448
    Top = 547
    Width = 56
    Height = 23
    Cursor = crHandPoint
    Caption = 'Close'
    TabOrder = 5
    OnClick = btnCloseClick
  end
  object tmrRead: TTimer
    Enabled = False
    Interval = 50
    OnTimer = tmrReadTimer
    Left = 248
    Top = 392
  end
end
