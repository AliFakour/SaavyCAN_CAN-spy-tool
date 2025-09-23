unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ComCtrls, PCANLight, ExtCtrls;

type
    MessageStatuspointer = ^MessageStatus;
    MessageStatus = record
        Msg : TPCANMsg;
        iIndex : integer;
    end;
    
    ProcMsgRead = procedure of object;
    
    TCANReadThread = class(TThread)
    private
        objCANLight: PPCANLight;
        ReadMessage: procedure of object;

    protected
        // Run function for the thread
        //
        procedure Execute; override;
        // Function Pointer for CAN reading
        //
        procedure DoReadMessage;
        
    public
        constructor Create(CANLightObj: PPCANLight; ReadMsgFunction: ProcMsgRead);
        destructor Destroy; override;
    end;
   
  TForm1 = class(TForm)
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    cbbHws: TComboBox;
    btnInfo: TButton;
    btnInit: TButton;
    btnRelease: TButton;
    cbbBaudrates: TComboBox;
    cbbMsgType: TComboBox;
    cbbIO: TComboBox;
    cbbInterrupt: TComboBox;
    btnGetDeviceNumber: TButton;
    btnSetDeviceNumber: TButton;
    ediDeviceNumber: TEdit;
    GroupBox2: TGroupBox;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    txtID: TEdit;
    nudLength: TUpDown;
    txtLength: TEdit;
    txtData0: TEdit;
    txtData1: TEdit;
    txtData2: TEdit;
    txtData3: TEdit;
    txtData4: TEdit;
    txtData5: TEdit;
    txtData6: TEdit;
    txtData7: TEdit;
    chbExtended: TCheckBox;
    chbRemote: TCheckBox;
    btnWrite: TButton;
    GroupBox5: TGroupBox;
    Label9: TLabel;
    Label10: TLabel;
    rdbStandard: TRadioButton;
    rdbExtended: TRadioButton;
    txtIdFrom: TEdit;
    txtIdTo: TEdit;
    btnSetFilter: TButton;
    btnResetFilter: TButton;
    GroupBox3: TGroupBox;
    lstMessages: TListView;
    GroupBox4: TGroupBox;
    txtInfo: TMemo;
    btnClose: TButton;
    btnDllInfo: TButton;
    chbTimeStamp: TCheckBox;
    rdbTimer: TRadioButton;
    rdbEvent: TRadioButton;
    labelReadMethod: TLabel;
    tmrRead: TTimer;
    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure cbbHwsChange(Sender: TObject);
    procedure cbbBaudratesChange(Sender: TObject);
    procedure txtIDKeyPress(Sender: TObject; var Key: Char);
    procedure txtIDExit(Sender: TObject);
    procedure nudLengthClick(Sender: TObject; Button: TUDBtnType);
    procedure txtData0Exit(Sender: TObject);
    procedure chbExtendedClick(Sender: TObject);
    procedure chbRemoteClick(Sender: TObject);
    procedure txtInfoDblClick(Sender: TObject);
    procedure lstMessagesDblClick(Sender: TObject);
    procedure tmrReadTimer(Sender: TObject);
    procedure btnInfoClick(Sender: TObject);
    procedure btnDllInfoClick(Sender: TObject);
    procedure btnInitClick(Sender: TObject);
    procedure btnReleaseClick(Sender: TObject);
    procedure btnWriteClick(Sender: TObject);
    procedure btnCloseClick(Sender: TObject);
    procedure rdbStandardClick(Sender: TObject);
    procedure txtIdFromExit(Sender: TObject);
    procedure btnSetFilterClick(Sender: TObject);
    procedure btnResetFilterClick(Sender: TObject);
    procedure btnGetDeviceNumberClick(Sender: TObject);
    procedure btnSetDeviceNumberClick(Sender: TObject);
    procedure chbTimeStampClick(Sender: TObject);
    procedure rdbTimerClick(Sender: TObject);
    procedure ediDeviceNumberExit(Sender: TObject);
    procedure ediDeviceNumberKeyPress(Sender: TObject; var Key: Char);
  private  
  	// Variables to store the current CAN Light instance
	//
    ActiveCANLight: PPCANLight;
    CurrBaud: Baudrates;

    // Variables for reading with event
    //
    hThread: TCANReadThread;
    
    // CAN messages Array. Store the Message Status for its display
    //
    LastMsgsList : TList;

    procedure ModifyMsgEntry(LastMsg : MessageStatus; NewMsg : TPCANMsg; MyTimeStamp: TPCANTimestamp);
    procedure InsertMsgEntry(NewMsg : TPCANMsg; MyTimeStamp: TPCANTimestamp);
    procedure ProcessMessage(MyMsg : TPCANMsg; MyTimeStamp: TPCANTimestamp);
    procedure ReadMessage();
    procedure ReadingModeChanged();
    
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

{ TCANReadThread }

constructor TCANReadThread.Create(CANLightObj: PPCANLight; ReadMsgFunction: ProcMsgRead);
begin
    objCANLight:= CANLightObj;
    ReadMessage:= ReadMsgFunction;        
    inherited Create(False);
end;

destructor TCANReadThread.Destroy;
begin
    if Not Terminated then
        Terminate();
end;

procedure TCANReadThread.DoReadMessage;
begin
    ReadMessage();
end;

procedure TCANReadThread.Execute; 
var
    hWaitEvent: THandle;
    Res: CANResult;
begin   
    hWaitEvent:= CreateEvent(nil,false,false,nil);
    Res:= objCANLight.SetRcvEvent(hWaitEvent);
    if Not((Res = ERR_OK) AND (hWaitEvent <> 0)) then
    begin
        MessageBox(0, 'Create CANRead-Thread failed','Error!',MB_ICONERROR);
        exit;
    end;
    
    while Not Terminated do
    begin
        if WaitForSingleObject(hWaitEvent, 50) = WAIT_OBJECT_0 then
            Synchronize(DoReadMessage);
    end;

    CloseHandle(hWaitEvent);    
    objCANLight.SetRcvEvent(0);        
end;
        
{ TForm1 }

procedure TForm1.InsertMsgEntry(NewMsg: TPCANMsg; MyTimeStamp: TPCANTimestamp);
var
    strNewData,strTemp, msgTimeStamp : string;
    CurrItem : TListItem;
    ToInsert : MessageStatusPointer;
    I : integer;
begin

    strTemp := '';
    strNewData := '';

    // Add the new ListView Item with the Type of the message
    //
    if((NewMsg.MSGTYPE AND Byte(MSGTYPE_EXTENDED)) <> 0)then
        strTemp := 'EXTENDED'
    else
        strTemp := 'STANDARD';

    if((NewMsg.MSGTYPE AND Byte(MSGTYPE_RTR)) = Byte(MSGTYPE_RTR))then
        strTemp := (strTemp + '/RTR');

    CurrItem := lstMessages.Items.Add();
    CurrItem.Caption:= strTemp;

    // We format the ID of the message and show it
    //
    if((NewMsg.MSGTYPE AND Byte(MSGTYPE_EXTENDED)) <> 0)then
        CurrItem.SubItems.Add(IntToHex(NewMsg.ID,8) + 'h')
    else
        CurrItem.SubItems.Add(IntToHex(NewMsg.ID,3) + 'h');

    // We set the length of the Message
    //
    CurrItem.SubItems.Add(IntToStr(NewMsg.LEN));

    // We format the data of the message. Each data is one
    // byte of Hexadecimal data
    //
    if((NewMsg.MSGTYPE AND Byte(MSGTYPE_RTR)) = Byte(MSGTYPE_RTR))then
        strNewData := 'Remote Request'
    else
        for I:=0 To NewMsg.LEN-1 do
            strNewData := (strNewData + IntToHex(NewMsg.DATA[I],2) + ' ');

    CurrItem.SubItems.Add(strNewData);

    // The message is the First, so count is 1
    //
    CurrItem.SubItems.Add('1');

	// Add Rcv Time information if need
	//
    if(chbTimeStamp.Checked)then
    begin
        msgTimeStamp:= Format('%d.%d',[MyTimeStamp.millis, MyTimeStamp.micros]);
        CurrItem.SubItems.Add(msgTimeStamp);        
    end;
    
    // We add this status in the last message list
    //
    New(ToInsert);
    ToInsert.Msg := NewMsg;
    ToInsert.iIndex := CurrItem.Index;
    LastMsgsList.Add(ToInsert);
end;

procedure TForm1.ModifyMsgEntry(LastMsg: MessageStatus; NewMsg: TPCANMsg; MyTimeStamp: TPCANTimestamp);
var
    strLastData, strNewData, msgTimeStamp : string;
    NewStatus,ToDelete : MessageStatusPointer;
    CurrItem : TListItem;
    I, iLen, iCount : Integer;
begin
    strNewData := '';
    strLastData := '';

    // Values from the last messages
    //
    CurrItem := lstMessages.Items.Item[LastMsg.iIndex];
    iCount := StrToInt(CurrItem.SubItems.Strings[3]);
    strLastData := CurrItem.SubItems.Strings[2];;
    iLen := LastMsg.Msg.LEN;

    // New values
    //
    if((NewMsg.MSGTYPE AND byte(MSGTYPE_RTR)) <> 0)then
        strNewData := 'Remote Request'
    else
        for I:=0 To NewMsg.LEN-1 do
            strNewData := (strNewData + IntToHex(NewMsg.DATA[I],2) + ' ');

    // Count is updated
    //
    iCount := iCount + 1;

    // Set the changes
    //
    if(iLen <> NewMsg.LEN)then
    begin
        iLen := NewMsg.LEN;
        CurrItem.SubItems.Strings[1] := IntToStr(iLen);
    end;

    if(strLastData <> strNewData)then
        CurrItem.SubItems.Strings[2] := strNewData;

    CurrItem.SubItems.Strings[3] := IntToStr(iCount);

    if(chbTimeStamp.Checked)then
    begin
        msgTimeStamp:= Format('%d.%d',[MyTimeStamp.millis,MyTimeStamp.micros]);
        CurrItem.SubItems.Strings[4] := msgTimeStamp;
    end;
    
    // Save the new Status of the message
    // NOTE: The objects are saved in the same index position which
    // they use in the Listview
    //
    New(NewStatus);
    NewStatus.Msg := NewMsg;
    NewStatus.iIndex := LastMsg.iIndex;

    ToDelete := LastMsgsList.Items[LastMsg.iIndex];
    LastMsgsList.Delete(LastMsg.iIndex);
    Dispose(ToDelete);
    LastMsgsList.Insert(LastMsg.iIndex,NewStatus);
end;

procedure TForm1.ProcessMessage(MyMsg: TPCANMsg; MyTimeStamp: TPCANTimestamp);
var
    bFound : boolean;
    CurrMessage : MessageStatusPointer;
    I : Integer;
begin
    bFound := false;
    CurrMessage := nil;

    // We search if a message (Smae ID, Type and same Net) is
    // already received or if this is a new message
    //
    for I:=0 To LastMsgsList.Count-1 do
    begin
        CurrMessage := LastMsgsList.Items[i];
        if(CurrMessage.Msg.ID = MyMsg.ID)then
            if(CurrMessage.Msg.MSGTYPE = MyMsg.MSGTYPE)then
            begin
                bFound := true;
                break;
            end;
    end;

    if(bFound)then
        // Messages of this kind are already received; we make an update
        //
        ModifyMsgEntry(CurrMessage^,MyMsg, MyTimeStamp)
    else
        // Messages of this kind are not received; we make a new entry
        //
        InsertMsgEntry(MyMsg, MyTimeStamp);
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
	// We set the variables for the 
	// CAN Light to use it
	//
    ActiveCANLight:= PPCANlight.Create();
    CurrBaud:= BAUD_1M;

	// Thread variable is initialized to null. Default is timer reading
	//
    hThread:= nil;
    
	// Create a list to store the displayed mesasges
	//
    LastMsgsList := TList.Create;

    // Set the standard values in the interface
    //
    cbbHws.ItemIndex:= 0;
    cbbBaudrates.ItemIndex:= 0;
    cbbIO.ItemIndex:= 18;
    cbbInterrupt.ItemIndex:= 3;
    cbbMsgType.ItemIndex:= 0;

    cbbBaudratesChange(self);
end;

procedure TForm1.FormClose(Sender: TObject; var Action: TCloseAction);
begin
	// Release Hardware if it is needed
	//
    if btnRelease.Enabled then
        btnRelease.Click;

    while (LastMsgsList.Count > 0) do
    begin
        Dispose(LastMsgsList.First);
        LastMsgsList.Delete(0);
    end;

    ActiveCANLight.Free;
       
    LastMsgsList.Free;
end;

procedure TForm1.cbbHwsChange(Sender: TObject);
var
    bShowIO: Boolean;
    current : HardwareType;
begin

    current := HardwareType(cbbHws.ItemIndex);

    // According with the selection in the Hardware list,
    // we show/hide the input controls for I/O Address and
    // Interrupt. (This parameters are NOT necessary for all
    // hardware types) .
    //
    Case current of
        DNG:
            bShowIO:= true;
        DNP:
            bShowIO:= true;
        ISA_1CH:
            bShowIO:= true;
        ISA_2CH:
            bShowIO:= true;
        else
            bShowIO:= false;
    end;

    cbbIO.Enabled:= bShowIO;
    cbbInterrupt.Enabled:= bShowIO;

	// According with the selection in the Hardware list, we 
	// Enable/Disable the controls for Get/Set the USB device Number.
	//
	btnGetDeviceNumber.Enabled := ((current = USB_1CH) Or (current = USB_2CH)) AND btnWrite.Enabled;
	btnSetDeviceNumber.Enabled := (btnGetDeviceNumber.Enabled);
    ediDeviceNumber.Enabled := (btnGetDeviceNumber.Enabled);
end;

procedure TForm1.cbbBaudratesChange(Sender: TObject);
begin
    // We save the corresponding Baudrate enumeration
    // type value for every selected Baudrate from the
    // list.
    //
    Case cbbBaudrates.ItemIndex Of
        0:
            CurrBaud:= BAUD_1M;
        1:
            CurrBaud:= BAUD_500K;
        2:
            CurrBaud:= BAUD_250K;
        3:
            CurrBaud:= BAUD_125K;
        4:
            CurrBaud:= BAUD_100K;
        5:
            CurrBaud:= BAUD_50K;
        6:
            CurrBaud:= BAUD_20K;
        7:
            CurrBaud:= BAUD_10K;
        8:
            CurrBaud:= BAUD_5K;
        else
            CurrBaud:= Baudrates(0);
    end;
end;

procedure TForm1.txtIDKeyPress(Sender: TObject; var Key: Char);
begin
    // We convert the Character to its Upper case equivalent
    //
    Key := (UpperCase(Key))[1];

    // The Key is the Delete (Backspace) Key
    //
    if(Ord(Key) = 8)then
        exit;
    // The Key is a number between 0-9
    //
    if((Ord(Key) > 47)AND(Ord(Key) < 58))then
        exit;
    // The Key is a character between A-F
    //
    if((Ord(Key) > 64)AND(Ord(Key) < 71))then
        exit;

    // Is neither a number nor a character between A(a) and F(f)
    //
    Key := #0;
end;

procedure TForm1.txtIDExit(Sender: TObject);
var
    TextLength, MaxValue : Integer;
begin
    // calculate the text length and Maximum ID value according
    // with the Message Type
    //
    if(chbExtended.Checked)then
      TextLength := 8
    else
      TextLength := 3;
    if(chbExtended.Checked)then
      MaxValue := $1FFFFFF
    else
      MaxValue := $7FF;
         
    // The Textbox for the ID is represented with 3 characters for
    // Standard and 8 characters for extended messages.
    // Therefore if the Length of the text is smaller than TextLength,
    // we add "0"
    //
    while(Length(txtID.Text) <> TextLength)do
        txtID.Text := ('0' + txtID.Text);

    // Because in this example will be sent only Standard messages
    // we check that the ID is not bigger than 0x7FF
    //
    if(StrToInt('$' + txtID.Text) > MaxValue)then
        txtID.Text := IntToHex(MaxValue,TextLength);
end;

procedure TForm1.nudLengthClick(Sender: TObject; Button: TUDBtnType);
var
    CurrentTextBox : TEdit;
    I : Integer;
begin
    // We enable so much TextBox Data fields as the length of the
    // message will be, that is the value of the UpDown control
    //
    for I:=0 to 7 do
    begin
        CurrentTextBox := TEdit(FindComponent('txtData'+IntToStr(I)));
        if(I < nudLength.Position)then
          CurrentTextBox.Enabled := true
        else
          CurrentTextBox.Enabled := false;
    end;
end;

procedure TForm1.txtData0Exit(Sender: TObject);
var
  CurrentEdit : TEdit;
begin
    if(String(Sender.ClassName) = 'TEdit')then
    begin
        CurrentEdit := TEdit(Sender);
        while(Length(CurrentEdit.Text) <> 2)do
            CurrentEdit.Text := ('0' + CurrentEdit.Text);
    end;
end;

procedure TForm1.chbExtendedClick(Sender: TObject);
var
    iTemp : Integer;
begin
    if(chbExtended.Checked)then
      txtID.MaxLength := 8
    else
      txtID.MaxLength := 3;

    // the only way that the text length can be bigger als MaxLength
    // is when the change is from Extended to Standard message Type.
    // We have to handle this and set an ID not bigger than the Maximum
    // ID value for a Standard Message (0x7FF)
    //
    if(Length(txtID.Text) > txtID.MaxLength)then
    begin
        iTemp := StrToInt('$' + txtID.Text);
        if(iTemp < $7FF)then
          txtID.Text := IntToHex(iTemp,3)
         else
           txtID.Text := '7FF';
    end;

    txtIDExit(txtID);
end;

procedure TForm1.chbRemoteClick(Sender: TObject);
var
    CurrentTextBox : TEdit;
    I : Integer;
begin
    // We enable so much TextBox Data fields as the length of the
    // message will be, that is the value of the UpDown control.
    //
    for I:=0 To 7 do
    begin
        CurrentTextBox := TEdit(FindComponent('txtData' + IntToStr(I)));
        CurrentTextBox.Visible := Not chbRemote.Checked;
    end;
end;

procedure TForm1.txtInfoDblClick(Sender: TObject);
begin
    // We clear the Information edit box
    //
    txtInfo.Text:= '';
end;

procedure TForm1.lstMessagesDblClick(Sender: TObject);
begin
    lstMessages.Items.Clear();
    while(LastMsgsList.Count >0)do
    begin
        Dispose(LastMsgsList.First);
        LastMsgsList.Delete(0);
    end;
end;

procedure TForm1.tmrReadTimer(Sender: TObject);
begin
    ReadMessage();
end;

procedure TForm1.btnInfoClick(Sender: TObject);
var
    strInfo: string;
    Res: CANResult;
    I: Integer;
begin
    I:= 1;
    // We execute the "VersionInfo" function of the PCANLight
    // using as parameter the Hardware type and a string
    // variable to get the info.
    //
    Res:= ActiveCANLight.VersionInfo(strInfo);
    while I < Length(strInfo) do
    begin
        if IsDelimiter(#10,strInfo,I) then
        begin
            Delete(strInfo,I,1);
            Insert(#13#10,strInfo,I);
            i:= I + 2;
        end
        else
            I:= I + 1;
    end;

    // The function was successfully executed
    //
    if Res = ERR_OK then
        // We show the Version Information
        //
        txtInfo.Text:= strInfo
        // An error occurred.  We show the error.
        //
    else
        txtInfo.Text:= 'Error Number: ' + IntToHex(Integer(Res),4) + 'h';
end;

procedure TForm1.btnDllInfoClick(Sender: TObject);
var
    strInfo: string;
    Res: CANResult;
begin
    // We execute the "VersionInfo" function of the PCANLight
    // using as parameter the Hardware type and a string
    // variable to get the info.
    //
    Res:= ActiveCANLight.DllVersionInfo(strInfo);

    // The function was successfully executed
    //
    if Res = ERR_OK then
        // We show the Version Information
        //
        txtInfo.Text:= cbbHws.Text + ' Dll Version: ' + strInfo
        // An error occurred.  We show the error.
        //
    else
        txtInfo.Text:= 'Error Number: ' + IntToHex(Integer(Res),4) + 'h';
end;

procedure TForm1.btnInitClick(Sender: TObject);
var
    Res: CANResult;
begin
    if(Not ActiveCANLight.InitializeAPI(HardwareType(cbbHws.ItemIndex)))then
        MessageBox(0,'DLL 2.x or later are required to run this program. Please, download lastest DLL version on ' +#13#10 +
        'http://www.peak-system.com or refer to the documentation for more information.', 
        'Dl Version', MB_ICONERROR)
    else
    begin
        // According with the active parameters/hardware, we
        // use one of the two possible "Init" PCANLight functions.
        // One is for Plug And Play hardware, and the other for
        // Not P&P.
        //
        if cbbIO.Enabled then
            // Not P&P Hardware
            //
            Res:= ActiveCANLight.Init(CurrBaud,            
                FramesType(cbbMsgType.ItemIndex),
                StrToInt('$' + cbbIO.Text),
                StrToInt(cbbInterrupt.Text))
        else
            // P&P Hardware
            //
            Res:= ActiveCANLight.Init(CurrBaud,
                FramesType(cbbMsgType.ItemIndex));

        // The Hardware was successfully initiated
        //
        if Res = ERR_OK then
        begin
            // We start to read from the CAN Queue
            //
            ReadingModeChanged();

            // We show the information of the configured
            // and initiated hardware
            //
            btnWrite.Enabled:= true;
            btnRelease.Enabled:= true;
            btnSetFilter.Enabled := true;
            btnResetFilter.Enabled := true;
            btnInfo.Enabled := true;
            btnDllInfo.Enabled := true;            
            btnInit.Enabled:= false;
            cbbHws.Enabled := false;
            rdbTimer.Enabled := true;
            rdbEvent.Enabled := true;
            chbTimeStamp.Enabled := true;            
            cbbHwsChange(self);
            txtInfo.Text:= 'Active Hardware: ' + cbbHws.Text;
            txtInfo.Text:= txtInfo.Text + #13#10 + 'Baud Rate: ' + cbbBaudrates.Text;
            txtInfo.Text:= txtInfo.Text + #13#10 + 'Frame Type: ' + cbbMsgType.Text;
            // If was a no P&P Hardware, we show additional information
            //
            if cbbIO.Enabled then
            begin
                txtInfo.Text:= txtInfo.Text + #13#10 + 'I/O Addr.: ' + cbbIO.Text + 'h';
                txtInfo.Text:= txtInfo.Text + #13#19 + 'Interrupt: ' + cbbInterrupt.Text;
            end;
        end
        // An error occurred.  We show the error.
        //
        else
            txtInfo.Text:= 'Error Number: ' + IntToHex(Integer(Res),4) + 'h';
    end;
end;

procedure TForm1.btnReleaseClick(Sender: TObject);
var
    Res: CANResult;
begin
    // We stopt to read from the CAN Queue
    //     
    tmrRead.Enabled:= false;

	// Terminate Read Thread if it exists
	//
    if hThread <> nil then
    begin
		// Causes the thread to terminate
		// and wai for termination
		//    
        hThread.Terminate;
        hThread.WaitFor();
        hThread.Destroy();
        hThread:= nil;             
    end;    

    // We close the active hardware using the
    // "Close" function of the PCANLight using
    // as parameter the Hardware type.
    //
    Res:= ActiveCANLight.Close();

    // The Hardware was successfully closed
    //
    if Res = ERR_OK then
        txtInfo.Text:= 'Hardware was successfully Released.' + #13#10
    // An error occurred.  We show the error.
    //
    else
        txtInfo.Text:= 'Error Number: ' + IntToHex(Integer(Res),4) + 'h';

    // We activate/deactivate the corresponding buttons
    //
    btnInit.Enabled:= true;
    cbbHws.Enabled := true;
    btnWrite.Enabled:= false;
    btnRelease.Enabled:= false;
    btnSetFilter.Enabled := false;
    btnResetFilter.Enabled := false;
    btnInfo.Enabled := false;
    btnDllInfo.Enabled := false;
    rdbTimer.Enabled := false;
    rdbEvent.Enabled := false;
    chbTimeStamp.Enabled := false;
    cbbHwsChange(self);
end;

procedure TForm1.btnWriteClick(Sender: TObject);
var
    MsgToSend : TPCANMsg;
    CurrentTextBox : TEdit;
    I : Integer;
    Res: CANResult;
begin
    // We configurate the Message.  The ID (max 0x1FF),
    // Length of the Data, Message Type (Standard in
    // this example) and die data
    //
    MsgToSend.ID := StrToInt('$' + txtID.Text);
    MsgToSend.LEN := nudLength.Position;

    if(chbExtended.Checked)then
      MsgToSend.MSGTYPE := Byte(MSGTYPE_EXTENDED)
    else
      MsgToSend.MSGTYPE := Byte(MSGTYPE_STANDARD);

    if(chbRemote.Checked)then
      MsgToSend.MSGTYPE := Byte(MsgToSend.MSGTYPE) OR Byte(MSGTYPE_RTR)
    else
      // We get so much data as the Len of the message
      //
      for I:=0 To MsgToSend.LEN-1 do
      begin
        CurrentTextBox := TEdit(FindComponent('txtData'+IntToStr(I)));
        MsgToSend.DATA[i] := StrToInt('$' + CurrentTextBox.Text);
      end;


    Res := ActiveCANLight.Write(MsgToSend);

    // The Hardware was successfully sent
    //
    if Res = ERR_OK then
        txtInfo.Text:= 'Message was successfully SENT.'+#13#10
    // An error occurred.  We show the error.
    //
    else
        txtInfo.Text:= 'Error Number: ' + IntToHex(Integer(Res),4) + 'h';
end;

procedure TForm1.btnCloseClick(Sender: TObject);
begin
    // We terminate the application
    //
    Close;
end;

procedure TForm1.rdbStandardClick(Sender: TObject);
var
    uiTemp : integer;
begin
    if (rdbExtended.Checked) then
        txtIdFrom.MaxLength := 8
    else
        txtIdFrom.MaxLength := 3;

    txtIdTo.MaxLength := txtIdFrom.MaxLength;

    // the only way that the text length can be bigger als MaxLength
    // is when the change is from Extended to Standard message Type.
    // We have to handle this and set an ID not bigger than the Maximum
    // ID value for a Standard Message (0x7FF)
    //
    if (Length(txtIdFrom.Text) > txtIdFrom.MaxLength) then
    begin
        uiTemp :=  StrToInt('0x' + txtIdFrom.Text);
        if (uiTemp < $7FF) then
            txtIdFrom.Text := IntToHex(uiTemp,3)
        else
            txtIdFrom.Text := '7FF';
    end;
    if (Length(txtIdTo.Text) > txtIdTo.MaxLength) then
    begin
        uiTemp := StrToInt('0x' + txtIdTo.Text);
        if(uiTemp < $7FF) then
            txtIdTo.Text := IntToHex(uiTemp,3)
        else
            txtIdTo.Text := '7FF';
    end;
end;

procedure TForm1.txtIdFromExit(Sender: TObject);
var
    TextLength, MaxValue : integer;
    IdBox : TEdit;
begin
    IdBox := TEdit(Sender);

    // calculate the text length and Maximum ID value according
    // with the Message Type
    //
    if (rdbExtended.Checked) then
    begin
        TextLength := 8;
        MaxValue := $1FFFFFFF;
    end
    else
    begin
        TextLength := 3;
        MaxValue := $7FF;
    end;


    // The Textbox for the ID is represented with 3 characters for
    // Standard and 8 characters for extended messages.
    // Therefore if the Length of the text is smaller than TextLength,
    // we add "0"
    //
    while(Length(IdBox.Text) <> TextLength) do
        IdBox.Text := ('0' + IdBox.Text);

    // Because in this example will be sent only Standard messages
    // we check that the ID is not bigger than 0x7FF
    //
    if (StrToInt('$' + IdBox.Text) > MaxValue) then
        IdBox.Text := IntToHex(MaxValue,TextLength);
end;

procedure TForm1.btnSetFilterClick(Sender: TObject);
var
    FromID, ToID : LongWord;
    Res : CANResult;
begin
    // The range IDs is read
    //
    FromID := StrToInt('$' + txtIdFrom.Text);
    ToID := StrToInt('$' + txtIdTo.Text);

    // The desired Filter is set on the configured Hardware
    //
    if (rdbStandard.Checked) then
        Res := ActiveCANLight.MsgFilter(FromID,ToID,MSGTYPE_STANDARD)
    else
        Res := ActiveCANLight.MsgFilter(FromID,ToID,MSGTYPE_EXTENDED);

    // The Filter was successfully set
    //
    if(Res = ERR_OK)then
        txtInfo.Text := 'Filter was successfully SET.'+#13#10
        // An error occurred.  We show the error.
        //
    else
        txtInfo.Text := 'Error Number: ' + IntToHex(Integer(Res),4) + 'h';
end;

procedure TForm1.btnResetFilterClick(Sender: TObject);
var
    Res : CANResult;
begin
    // The current Filter on the configured Hardware is reset
    //
    Res := ActiveCANLight.ResetFilter();

    // The Filter was successfully reset
    //
    if (Res = ERR_OK) then
        txtInfo.Text := 'Filter was successfully RESET.' + #13#10
    // An error occurred.  We show the error.
    //
    else
        txtInfo.Text := 'Error Number: ' + IntToHex(Integer(Res),4) + 'h';
end;

procedure TForm1.btnGetDeviceNumberClick(Sender: TObject);
var
    DevNum : LongWord;
    Res : CANResult;
begin
	// The USB Device Number will asked
	//
	Res := ActiveCANLight.GetUSBDeviceNr(DevNum);

	// The Device number was got successfully
	//
	if(Res = ERR_OK) then
		txtInfo.Text := 'USB Device Number is: ' +  IntToStr(DevNum) + #13#10
		// An error occurred.  We show the error.
		//
	else
		txtInfo.Text := 'Error Number: 0x' + IntToHex(Integer(Res),4);
end;

procedure TForm1.btnSetDeviceNumberClick(Sender: TObject);
var
	Res : CANResult;
begin
	// The USB Device Number will set
	//
	Res := ActiveCANLight.SetUSBDeviceNr(StrToInt64(ediDeviceNumber.Text));

	// The Device number was set successfully
	//
	if(Res = ERR_OK) then
		txtInfo.Text  := 'USB Device Number was set'
		// An error occurred.  We show the error.
		//
	else
		txtInfo.Text := 'Set USB Device Number failed: 0x' + IntToHex(Integer(Res),4);
end;

procedure TForm1.chbTimeStampClick(Sender: TObject);
var
    RcvColumn: TListColumn;
begin
	// If Show Time Stamp is selected
	//
    if chbTimeStamp.Checked then
    begin
		// Add "Rcv Time" column in List
		//    
        if lstMessages.Columns.Count = 5 then
        begin
            RcvColumn:= lstMessages.Columns.Add();
            RcvColumn.Caption:= 'Rcv Time';
            RcvColumn.Width := 90;
        end;
    end
    else
		// Remove "Rcv Time" column in List
		//    
        if lstMessages.Columns.Count = 6 then
            lstMessages.Columns.Delete(5);
end;

procedure TForm1.ReadMessage();
var
    Res: CANResult;
    MyMsg: TPCANMsg;
    MyTimeStamp: TPCANTimestamp;
begin
    Res:= ERR_OK;
    
	// We read the queue at least once, looking for messages.
	// If a message is found, we look again trying to find more.
	// If the queue is empty or if an error occurred, we exit
	// the while statement.
	//
    while CANResult((Integer(Res) AND Integer(ERR_QRCVEMPTY))) <> ERR_QRCVEMPTY do
    begin
		// We read the queue looking for ...
		//
        if chbTimeStamp.Checked then 
            // a message and its timestamp
            //
            Res:= ActiveCANLight.ReadEx(MyMsg, MyTimeStamp)
        else
            // a message
            //
            Res:= ActiveCANLight.Read(MyMsg);

        // A message was received
		// We process the message
		//	
        if Res = ERR_OK then
            ProcessMessage(MyMsg, MyTimeStamp);
    end;
end;

procedure TForm1.ReadingModeChanged();
begin
	// We are changing to Timer mode 
	//
    if rdbTimer.Checked then
    begin
		// An existing Thread will deleted
		//    
        if hThread <> nil then
        begin      
		    // Causes the thread to terminate
	    	// and wai for termination
    		//      
            hThread.Terminate;
            hThread.WaitFor();
            hThread.Destroy();
            hThread:= nil;
        end;
		// We start to read with timer
        //        
        tmrRead.Enabled:= true;        
    end
    else 
    begin
        tmrRead.Enabled:= false;
        if hThread = nil then
            hThread:= TCANReadThread.Create(ActiveCANLight, ReadMessage);
    end;
end;
    
procedure TForm1.rdbTimerClick(Sender: TObject);
begin
	// check for a ReadMode change 
	//
    ReadingModeChanged();
end;

procedure TForm1.ediDeviceNumberExit(Sender: TObject);
begin
    // Check that the number to set is 4 byte in length
    //
    if(ediDeviceNumber.Text = '')then
        ediDeviceNumber.Text:= '0';
        
    // Check that the number to set is 4 byte in length
    //
    if(StrToInt64(ediDeviceNumber.Text) > 4294967295)then
        ediDeviceNumber.Text:= '4294967295';
end;

procedure TForm1.ediDeviceNumberKeyPress(Sender: TObject; var Key: Char);
begin
    // The Key is the Delete (Backspace) Key
    //
    if(Ord(Key) = 8)then
        exit;
        
    // The Key is a number between 0-9
    //
    if((Ord(Key) > 47)AND(Ord(Key) < 58))then
        exit;
        
    // Is neither a number nor a character between A(a) and F(f)
    //
    Key := #0;
end;

end.
 