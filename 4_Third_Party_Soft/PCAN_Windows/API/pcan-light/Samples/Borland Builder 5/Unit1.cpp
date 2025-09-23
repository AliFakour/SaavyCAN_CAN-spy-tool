//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TCANReadThread::TCANReadThread(
    PCANLight *CANLightObj,
    ProcMsgRead ReadMsgFunction
) : TThread(false)

{
    objCANLight = CANLightObj;
    ReadMessage = ReadMsgFunction;
}

__fastcall TCANReadThread::~TCANReadThread()
{
    if(!Terminated)
        Terminate();
}

void __fastcall TCANReadThread::DoReadMessage()
{
    ReadMessage();
}

void __fastcall TCANReadThread::Execute()
{
    HANDLE hWaitEvent;
    CANResult Res;

    hWaitEvent = CreateEvent(NULL,false,false,NULL);
    Res = objCANLight->SetRcvEvent(hWaitEvent);

    if(!((Res == ERR_OK) && (hWaitEvent != 0)))
    {
        MessageBox(NULL, "Create CANRead-Thread failed","Error!",MB_ICONERROR);
        return;
    }
    
    while(!Terminated)
        if(WaitForSingleObject(hWaitEvent, 50) == WAIT_OBJECT_0)
            Synchronize(DoReadMessage);

    CloseHandle(hWaitEvent);
    objCANLight->SetRcvEvent(0);
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
	// We set the variable for the current 
	// CAN Light instance to use it
	//
	ActiveCANLight = new PCANLight();

	// Thread variable is initialized to null. Default is timer reading
	//
	hThread = NULL;

	// Create a list to store the displayed mesasges
	//
    LastMsgsList = new TList();

    // Set the standard values in the interface
    //
    cbbHws->ItemIndex = 0;
    cbbBaudrates->ItemIndex = 0;
    cbbIO->ItemIndex = 18;
    cbbInterrupt->ItemIndex = 3;
    cbbMsgType->ItemIndex = 0;

    CurrBaud = BAUD_1M;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	// Release Hardware if it is needed
	//
    if(btnRelease->Enabled)
        btnRelease->Click();

    while(LastMsgsList->Count)
    {
        delete LastMsgsList->First();
        LastMsgsList->Delete(0);
    }
    delete LastMsgsList;

    delete ActiveCANLight;
}
//---------------------------------------------------------------------------

void TForm1::InsertMsgEntry(TPCANMsg NewMsg, TPCANTimestamp MyTimeStamp)
{
    AnsiString strNewData,strTemp, msgTimeStamp;
    TListItem *CurrItem;
    MessageStatus *ToInsert;

    strTemp = strNewData = "";

    // Add the new ListView Item with the Type of the message
    //
    if((NewMsg.MSGTYPE & MSGTYPE_EXTENDED) != 0)
        strTemp = "EXTENDED";
    else
        strTemp = "STANDARD";

    if((NewMsg.MSGTYPE & MSGTYPE_RTR) == MSGTYPE_RTR)
        strTemp = (strTemp + "/RTR");

    CurrItem = lstMessages->Items->Add();
    CurrItem->Caption = strTemp;

    // We format the ID of the message and show it
    //
    if((NewMsg.MSGTYPE & MSGTYPE_EXTENDED) != 0)
        CurrItem->SubItems->Add(IntToHex((int)NewMsg.ID,8) + "h");
    else
        CurrItem->SubItems->Add(IntToHex((int)NewMsg.ID,3) + "h");

    // We set the length of the Message
    //
    CurrItem->SubItems->Add(IntToStr(NewMsg.LEN));

    // We format the data of the message. Each data is one
    // byte of Hexadecimal data
    //
    if((NewMsg.MSGTYPE & MSGTYPE_RTR) == MSGTYPE_RTR)
        strNewData = "Remote Request";
    else
        for(int i=0; i< NewMsg.LEN; i++)
            strNewData = (strNewData + IntToHex(NewMsg.DATA[i],2) + " ");

    CurrItem->SubItems->Add(strNewData);

    // The message is the First, so count is 1
    //
    CurrItem->SubItems->Add("1");

	// Add Rcv Time information if need
	//
    if(chbTimeStamp->Checked)
    {
        msgTimeStamp = AnsiString::Format("%d.%d", ARRAYOFCONST(((int)MyTimeStamp.millis, (int)MyTimeStamp.micros)));
        CurrItem->SubItems->Add(msgTimeStamp);
    }

    // We add this status in the last message list
    //
    ToInsert = new MessageStatus(&NewMsg,CurrItem->Index);
    LastMsgsList->Add(ToInsert);
}
//---------------------------------------------------------------------------

void TForm1::ModifyMsgEntry(MessageStatus LastMsg,TPCANMsg NewMsg, TPCANTimestamp MyTimeStamp)
{
    AnsiString strLastData, strNewData, msgTimeStamp;
    MessageStatus *NewStatus,*ToDelete;
    TListItem *CurrItem;
    int iLen;
    int iCount;

    strNewData = strLastData = "";

    // Values from the last messages
    //
    CurrItem = lstMessages->Items->Item[LastMsg.Position()];
    iCount = StrToInt(CurrItem->SubItems->Strings[3]);
    strLastData = CurrItem->SubItems->Strings[2];;
    iLen = (LastMsg.CANMessage()).LEN;

    // New values
    //
    if((NewMsg.MSGTYPE & MSGTYPE_RTR) != 0)
        strNewData = "Remote Request";
    else
        for(int i=0; i< NewMsg.LEN; i++)
            strNewData = (strNewData + IntToHex(NewMsg.DATA[i],2) + " ");

    // Count is updated
    //
    iCount += 1;


    // Set the changes
    //
    if(iLen != NewMsg.LEN)
    {
        iLen = NewMsg.LEN;
        CurrItem->SubItems->Strings[1] = IntToStr(iLen);
    }

    if(strLastData != strNewData)
        CurrItem->SubItems->Strings[2] = strNewData;

    CurrItem->SubItems->Strings[3] = IntToStr(iCount);

	// Update Rcv Time information if need
	//
	if(chbTimeStamp->Checked)
	{
		msgTimeStamp = AnsiString::Format("%d.%d", ARRAYOFCONST(((int)MyTimeStamp.millis, (int)MyTimeStamp.micros)));
		CurrItem->SubItems->Strings[4] = (msgTimeStamp);
	}

    // Save the new Status of the message
    // NOTE: The objects are saved in the same index position which
    // they use in the Listview
    //
    NewStatus = new MessageStatus(&NewMsg,LastMsg.Position());
    ToDelete = (MessageStatus*)LastMsgsList->Items[LastMsg.Position()];
    LastMsgsList->Delete(LastMsg.Position());
    delete ToDelete;
    LastMsgsList->Insert(LastMsg.Position(),NewStatus);
}
//---------------------------------------------------------------------------

void TForm1::ProcessMessage(TPCANMsg MyMsg, TPCANTimestamp RcvTime)
{
    bool bFound = false;
    MessageStatus *CurrMessage;

    // We search if a message (Smae ID, Type and same Net) is
    // already received or if this is a new message
    //
    for(int i=0; i< LastMsgsList->Count; i++)
    {
        CurrMessage = (MessageStatus*)LastMsgsList->Items[i];
        if(CurrMessage->CANMessage().ID == MyMsg.ID)
            if(CurrMessage->CANMessage().MSGTYPE == MyMsg.MSGTYPE)
            {
                bFound = true;
                break;
            }
    }

    if(bFound)
        // Messages of this kind are already received; we make an update
        //
        ModifyMsgEntry(*CurrMessage,MyMsg, RcvTime);
    else
        // Messages of this kind are not received; we make a new entry
        //
        InsertMsgEntry(MyMsg, RcvTime);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::cbbHwsChange(TObject *Sender)
{
    bool bShowIO;
    int current;

    current = cbbHws->ItemIndex;

    // According with the selection in the Hardware list,
    // we show/hide the input controls for I/O Address and
    // Interrupt. (This parameters are NOT necessary for all
    // hardware types) .
    //
    switch (cbbHws->ItemIndex)
    {
        case DNG:
            bShowIO = true;
            break;
        case DNP:
            bShowIO = true;
            break;
        case ISA_1CH:
            bShowIO = true;
            break;
        case ISA_2CH:
            bShowIO = true;
            break;
        default:
            bShowIO = false;
            break;
    }

    cbbIO->Enabled = bShowIO;
    cbbInterrupt->Enabled = bShowIO;

	// According with the selection in the Hardware list, we
	// Enable/Disable the controls for Get/Set the USB device Number.
	//
	btnGetDeviceNumber->Enabled = ((current == USB_1CH) || (current == USB_2CH)) && btnWrite->Enabled;
	btnSetDeviceNumber->Enabled = (btnGetDeviceNumber->Enabled);
    ediDeviceNumber->Enabled = (btnGetDeviceNumber->Enabled);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::cbbBaudratesChange(TObject *Sender)
{
    // We save the corresponding Baudrate enumeration
    // type value for every selected Baudrate from the
    // list.
    //
    switch(cbbBaudrates->ItemIndex)
    {
        case 0:
            CurrBaud = BAUD_1M;
            break;
        case 1:
            CurrBaud = BAUD_500K;
            break;
        case 2:
            CurrBaud = BAUD_250K;
            break;
        case 3:
            CurrBaud = BAUD_125K;
            break;
        case 4:
            CurrBaud = BAUD_100K;
            break;
        case 5:
            CurrBaud = BAUD_50K;
            break;
        case 6:
            CurrBaud = BAUD_20K;
            break;
        case 7:
            CurrBaud = BAUD_10K;
            break;
        case 8:
            CurrBaud = BAUD_5K;
            break;
        default:
            CurrBaud = (Baudrates)0;
            break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::txtIDKeyPress(TObject *Sender, char &Key)
{
    // We convert the Character to its Upper case equivalent
    //
    Key = *(UpperCase((AnsiString)Key)).c_str();

    // The Key is the Delete (Backspace) Key
    //
    if(Key == 8)
        return;
    // The Key is a number between 0-9
    //
    if((Key > 47)&&(Key < 58))
        return;
    // The Key is a character between A-F
    //
    if((Key > 64)&&(Key < 71))
        return;

    // Is neither a number nor a character between A(a) and F(f)
    //
    Key = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::txtIDExit(TObject *Sender)
{
    int TextLength, MaxValue;

    // calculate the text length and Maximum ID value according
    // with the Message Type
    //
    TextLength = (chbExtended->Checked) ? 8 : 3;
    MaxValue = (chbExtended->Checked) ? 0x1FFFFFFF : 0x7FF;

    // The Textbox for the ID is represented with 3 characters for
    // Standard and 8 characters for extended messages.
    // Therefore if the Length of the text is smaller than TextLength,
    // we add "0"
    //
    while(txtID->Text.Length() != TextLength)
        txtID->Text = ("0" + txtID->Text);

    // Because in this example will be sent only Standard messages
    // we check that the ID is not bigger than 0x7FF
    //
    if(StrToInt("0x" + txtID->Text) > MaxValue)
        txtID->Text = IntToHex(MaxValue,TextLength);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::nudLengthClick(TObject *Sender, TUDBtnType Button)
{
    TEdit *CurrentTextBox;

    // We enable so much TextBox Data fields as the length of the
    // message will be, that is the value of the UpDown control
    //
    for(int i=0; i< 8; i++)
    {
        CurrentTextBox = (TEdit*)FindComponent("txtData"+IntToStr(i));
        CurrentTextBox->Enabled = (i < nudLength->Position)? true : false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::txtData0Exit(TObject *Sender)
{
    TEdit *CurrentEdit;

    if(String(Sender->ClassName()) == "TEdit"){
        CurrentEdit = (TEdit*)Sender;
        while(CurrentEdit->Text.Length() != 2)
            CurrentEdit->Text = ("0" + CurrentEdit->Text);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::chbExtendedClick(TObject *Sender)
{
    int iTemp;

    txtID->MaxLength = (chbExtended->Checked)? 8: 3;

    // the only way that the text length can be bigger als MaxLength
    // is when the change is from Extended to Standard message Type.
    // We have to handle this and set an ID not bigger than the Maximum
    // ID value for a Standard Message (0x7FF)
    //
    if(txtID->Text.Length() > txtID->MaxLength)
    {
        iTemp = StrToInt("0x" + txtID->Text);
        txtID->Text = (iTemp < 0x7FF) ?  IntToHex(iTemp,3) : AnsiString("7FF");
    }

    txtIDExit(txtID);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::chbRemoteClick(TObject *Sender)
{
    TEdit *CurrentTextBox;

    // We enable so much TextBox Data fields as the length of the
    // message will be, that is the value of the UpDown control.
    //
    for(int i=0; i< 8; i++)
    {
        CurrentTextBox = (TEdit*)FindComponent("txtData" + IntToStr(i));
        CurrentTextBox->Visible = !chbRemote->Checked;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::txtInfoDblClick(TObject *Sender)
{
    // We clear the Information edit box
    //
    txtInfo->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::lstMessagesDblClick(TObject *Sender)
{
    lstMessages->Items->Clear();
    while(LastMsgsList->Count)
    {
        delete LastMsgsList->First();
        LastMsgsList->Delete(0);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::tmrReadTimer(TObject *Sender)
{
    ReadMessage();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnInfoClick(TObject *Sender)
{
    char versionInfoResult[255];
    AnsiString strInfo;
    CANResult Res;
    int i=1;

    // We execute the "VersionInfo" function of the PCANLight
    // using as parameter the Hardware type and a string
    // variable to get the info.
    //
    Res = ActiveCANLight->VersionInfo(versionInfoResult);
    strInfo = versionInfoResult;


    while(i < strInfo.Length())
    {
        if(IsDelimiter('\n',strInfo,i)){
            strInfo.Delete(i,1);
            strInfo.Insert("\r\n",i);
            i+=2;
        }
        else
            i+=1;
    }

    // The function was successfully executed
    //
    if(Res == ERR_OK)
        // We show the Version Information
        //
        txtInfo->Text = strInfo;
        // An error occurred.  We show the error.
        //
    else
        txtInfo->Text  = "Error Number: 0x" + IntToHex(int(Res),4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnDllInfoClick(TObject *Sender)
{
    char versionInfoResult[255];
    AnsiString strInfo;
    CANResult Res;

    // We execute the "VersionInfo" function of the PCANLight
    // using as parameter the Hardware type and a string
    // variable to get the info.
    //
    Res = ActiveCANLight->DllVersionInfo(versionInfoResult);
    strInfo = versionInfoResult;

    // The function was successfully executed
    //
    if(Res == ERR_OK)
        // We show the Version Information
        //
        txtInfo->Text = cbbHws->Text + " Dll Version: " + strInfo;
        // An error occurred.  We show the error.
        //
    else
        txtInfo->Text = "Error Number: " + IntToHex((int)Res,4) + "h";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnInitClick(TObject *Sender)
{
    CANResult Res;

    if(!ActiveCANLight->InitializeAPI(HardwareType(cbbHws->ItemIndex)))
        MessageBox(0,((AnsiString)"DLL 2.x or later are required to run this program. Please, download lastest DLL version on \r\n" +
        "http://www.peak-system.com or refer to the documentation for more information.").c_str(),
        "Dl Version", MB_ICONERROR);
    else
    {
        // According with the active parameters/hardware, we
        // use one of the two possible "Init" PCANLight functions.
        // One is for Plug And Play hardware, and the other for
        // Not P&P.
        //
        if(cbbIO->Enabled)
            // Not P&P Hardware
            //
            Res = ActiveCANLight->Init(CurrBaud,
                FramesType(cbbMsgType->ItemIndex),
                StrToInt("0x" + cbbIO->Text),
                StrToInt(cbbInterrupt->Text));
        else
            // P&P Hardware
            //
            Res = ActiveCANLight->Init(CurrBaud,
                FramesType(cbbMsgType->ItemIndex));

        // The Hardware was successfully initiated
        //
        if(Res == ERR_OK)
        {
            // We start to read from the CAN Queue
            //
            ReadingModeChanged();

            // We show the information of the configured
            // and initiated hardware
            //
            btnWrite->Enabled = true;
            btnRelease->Enabled = true;
            btnSetFilter->Enabled = true;
            btnResetFilter->Enabled = true;
            btnInfo->Enabled = true;
            btnDllInfo->Enabled = true;
            btnInit->Enabled = false;
            cbbHws->Enabled = false;
            rdbTimer->Enabled = true;
            rdbEvent->Enabled = true;
            chbTimeStamp->Enabled = true;
            cbbHwsChange(this);
            txtInfo->Text = "Active Hardware: " + cbbHws->Text;
            txtInfo->Text = txtInfo->Text + "\r\nBaud Rate: " + cbbBaudrates->Text;
            txtInfo->Text = txtInfo->Text + "\r\nFrame Type: " + cbbMsgType->Text;
            // If was a no P&P Hardware, we show additional information
            //
            if(cbbIO->Enabled)
            {
                txtInfo->Text = txtInfo->Text +"\r\nI/O Addr.: " + cbbIO->Text + "h";
                txtInfo->Text = txtInfo->Text + "\r\nInterrupt: " + cbbInterrupt->Text;
            }
        }
        // An error occurred.  We show the error.
        //
        else
            txtInfo->Text = "Error Number: " + IntToHex(Integer(Res),4) + "h";
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnReleaseClick(TObject *Sender)
{
    CANResult Res;

    // We stopt to read from the CAN Queue
    //
    tmrRead->Enabled = false;

	// Terminate Read Thread if it exists
	//
    if(hThread != NULL)
    {
		// Causes the thread to terminate
		// and wai for termination
		//
		hThread->Terminate();
		hThread->WaitFor();
        delete hThread;
		hThread = NULL;
    }

    // We close the active hardware using the
    // "Close" function of the PCANLight using
    // as parameter the Hardware type.
    //
    Res = ActiveCANLight->Close();

    // The Hardware was successfully closed
    //
    if(Res == ERR_OK)
        txtInfo->Text = "Hardware was successfully Released.\r\n";
    // An error occurred.  We show the error.
    //
    else
        txtInfo->Text = "Error Number: " + IntToHex((int)Res,4) + "h";

    // We activate/deactivate the corresponding buttons
    //
    btnInit->Enabled = true;
    cbbHws->Enabled = true;
    btnWrite->Enabled = false;
    btnRelease->Enabled = false;
    btnSetFilter->Enabled = false;
    btnResetFilter->Enabled = false;
    btnInfo->Enabled = false;
    btnDllInfo->Enabled = false;
    rdbTimer->Enabled = false;
    rdbEvent->Enabled = false;
    chbTimeStamp->Enabled = false;
    cbbHwsChange(this);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnWriteClick(TObject *Sender)
{
    TPCANMsg MsgToSend;
    TEdit *CurrentTextBox;
    CANResult Res;

    // We configurate the Message.  The ID (max 0x1FF),
    // Length of the Data, Message Type (Standard in
    // this example) and die data
    //
    MsgToSend.ID = StrToInt("0x" + txtID->Text);
    MsgToSend.LEN = nudLength->Position;
    MsgToSend.MSGTYPE = (chbExtended->Checked) ? MSGTYPE_EXTENDED : MSGTYPE_STANDARD;

    // If a remote frame will be sent, the data bytes are not important.
    //
    if(chbRemote->Checked)
        MsgToSend.MSGTYPE |= MSGTYPE_RTR;
    else
        // We get so much data as the Len of the message
        //
        for(int i=0; i < MsgToSend.LEN; i++)
        {
            CurrentTextBox = (TEdit*)FindComponent("txtData"+IntToStr(i));
            MsgToSend.DATA[i] = StrToInt("0x" + CurrentTextBox->Text);
        }

    // The message is sent to the configured hardware
    //
    Res = ActiveCANLight->Write(&MsgToSend);

    // The Hardware was successfully sent
    //
    if(Res == ERR_OK)
        txtInfo->Text = "Message was successfully SENT.\r\n";
        // An error occurred.  We show the error.
        //
    else
        txtInfo->Text = "Error Number: 0x" + IntToHex(int(Res),4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnCloseClick(TObject *Sender)
{
    // We terminate the application
    //
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::rdbStandardClick(TObject *Sender)
{
    int uiTemp;

    txtIdFrom->MaxLength = (rdbExtended->Checked) ? 8 : 3;
    txtIdTo->MaxLength = txtIdFrom->MaxLength;

    // the only way that the text length can be bigger als MaxLength
    // is when the change is from Extended to Standard message Type.
    // We have to handle this and set an ID not bigger than the Maximum
    // ID value for a Standard Message (0x7FF)
    //
    if (txtIdFrom->Text.Length() > txtIdFrom->MaxLength)
    {
        uiTemp =  StrToInt("0x" + txtIdFrom->Text);
        txtIdFrom->Text = (uiTemp < 0x7FF) ? IntToHex(uiTemp,3) : (AnsiString)"7FF";
    }
    if (txtIdTo->Text.Length() > txtIdTo->MaxLength)
    {
        uiTemp = StrToInt("0x" + txtIdTo->Text);
        txtIdTo->Text = (uiTemp < 0x7FF) ? IntToHex(uiTemp,3) : (AnsiString)"7FF";
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::txtIdFromExit(TObject *Sender)
{
    int TextLength, MaxValue;
    TEdit *IdBox;

    IdBox = (TEdit*)Sender;

    // calculate the text length and Maximum ID value according
    // with the Message Type
    //
    TextLength = (rdbExtended->Checked) ? 8 : 3;
    MaxValue = (rdbExtended->Checked) ? 0x1FFFFFFF : 0x7FF;

    // The Textbox for the ID is represented with 3 characters for
    // Standard and 8 characters for extended messages.
    // Therefore if the Length of the text is smaller than TextLength,
    // we add "0"
    //
    while(IdBox->Text.Length() != TextLength)
        IdBox->Text = ("0" + IdBox->Text);

    // Because in this example will be sent only Standard messages
    // we check that the ID is not bigger than 0x7FF
    //
    if(StrToInt("0x" + IdBox->Text) > MaxValue)
        IdBox->Text = IntToHex(MaxValue,TextLength);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnSetFilterClick(TObject *Sender)
{
    unsigned long FromID, ToID;
    CANResult Res;

    // The range IDs is read
    //
    FromID = StrToInt("0x" + txtIdFrom->Text);
    ToID = StrToInt("0x" + txtIdTo->Text);

    // The desired Filter is set on the configured Hardware
    //
    Res = ActiveCANLight->MsgFilter(FromID,ToID,(rdbStandard->Checked) ? MSGTYPE_STANDARD : MSGTYPE_EXTENDED);

    // The Filter was successfully set
    //
    if(Res == ERR_OK)
        txtInfo->Text = "Filter was successfully SET.\r\n";
        // An error occurred.  We show the error.
        //
    else
        txtInfo->Text = "Error Number: 0x" + IntToHex(int(Res),4);    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnResetFilterClick(TObject *Sender)
{
    CANResult Res;

    // The current Filter on the configured Hardware is reset
    //
    Res = ActiveCANLight->ResetFilter();

    // The Filter was successfully reset
    //
    if (Res == ERR_OK)
        txtInfo->Text = "Filter was successfully RESET.\r\n";
    // An error occurred.  We show the error.
    //
    else
        txtInfo->Text = "Error Number: 0x" + IntToHex(int(Res),4);    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnGetDeviceNumberClick(TObject *Sender)
{
	unsigned int iDevNum;
	CANResult Res;

	// The USB Device Number will asked 
	//
	Res = ActiveCANLight->GetUSBDeviceNr(&iDevNum);

	// The Device number was got successfully
	//
	if(Res == ERR_OK)
		txtInfo->Text = "USB Device Number is: " +  IntToStr(iDevNum) + ".\r\n";
		// An error occurred.  We show the error.
		//
	else
		txtInfo->Text = "Error Number: 0x" + IntToHex((int)Res,4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnSetDeviceNumberClick(TObject *Sender)
{
	CANResult Res;

	// The USB Device Number will set
	//
    Res = ActiveCANLight->SetUSBDeviceNr(StrToInt64(ediDeviceNumber->Text));

	// The Device number was set successfully
	//
	if(Res == ERR_OK)
		txtInfo->Text  = "USB Device Number was set";
		// An error occurred.  We show the error.
		//
	else
		txtInfo->Text  = "Set USB Device Number failed: 0x" + IntToHex((int)Res,4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::chbTimeStampClick(TObject *Sender)
{
    TListColumn *RcvColumn;

	// If Show Time Stamp is selected
	//
    if(chbTimeStamp->Checked)
    {
		// Add "Rcv Time" column in List
		//
        if(lstMessages->Columns->Count == 5)
        {
            RcvColumn = lstMessages->Columns->Add();
            RcvColumn->Caption = "Rcv Time";
            RcvColumn->Width = 90;
        }
    }
    else
		// Remove "Rcv Time" column in List
		//
        if(lstMessages->Columns->Count == 6)
            lstMessages->Columns->Delete(5);
}
//---------------------------------------------------------------------------

void TForm1::ReadMessage()
{
	TPCANMsg MyMsg;
	TPCANTimestamp MyTimeStamp = {0,0,0};
	CANResult Res;

	// We read the queue at least once, looking for messages.
	// If a message is found, we look again trying to find more.
	// If the queue is empty or if an error occurred, we exit
	// the do-while statement.
	//
	do
	{
		// We read the queue looking for ...
		//
		if(chbTimeStamp->Checked)
			// a message and its timestamp
			//
			Res = ActiveCANLight->ReadEx(&MyMsg,&MyTimeStamp);
		else
			// a message
			//
			Res = ActiveCANLight->Read(&MyMsg);

		// A message was received
		// We process the message
		//
		if(Res == ERR_OK)
			ProcessMessage(MyMsg, MyTimeStamp);
	}while(!(Res & ERR_QRCVEMPTY));
}
//---------------------------------------------------------------------------

void TForm1::ReadingModeChanged()
{
	// If active reading mode is By Timer
	//
	if(rdbTimer->Checked)
	{
		// if the Thread exists, we stop it (we are changing to Timer mode)
		//
		if(hThread != NULL)
		{
			// Causes the thread to terminate
			//
            hThread->Terminate();
            hThread->WaitFor();
            delete hThread;
            hThread = NULL;
		}
		// We start to read with timer
		//
		tmrRead->Enabled = true;
	}
	// If active reading mode is By Event
	//
	else
	{
        // We stop reading with timer
        //
        tmrRead->Enabled = false;

		// If the Thread doens't exists, we are changing to Event mode
		//
		if(hThread == NULL)
			// Create Reading Thread ....
			//
			hThread = new TCANReadThread(ActiveCANLight, &ReadMessage);
	}                                                     
}
//---------------------------------------------------------------------------

void __fastcall TForm1::rdbTimerClick(TObject *Sender)
{
	// Check for a ReadMode change
	//
	ReadingModeChanged();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ediDeviceNumberKeyPress(TObject *Sender, char &Key)
{
    // The Key is the Delete (Backspace) Key
    //
    if(Key == 8)
        return;

    // The Key is a number between 0-9
    //
    if((Key > 47)&&(Key < 58))
        return;

    // Is neither a number nor a character between A(a) and F(f)
    //
    Key = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ediDeviceNumberExit(TObject *Sender)
{
    // Check that the number to set is 4 byte in length
    //
    if(ediDeviceNumber->Text == "")
        ediDeviceNumber->Text = "0";
    
    if(StrToInt64(ediDeviceNumber->Text) > 4294967295)
        ediDeviceNumber->Text = "4294967295";
}
//---------------------------------------------------------------------------

