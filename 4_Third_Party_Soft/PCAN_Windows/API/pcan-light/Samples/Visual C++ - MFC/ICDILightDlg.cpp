// ICDILightDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ICDILight.h"
#include "ICDILightDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

volatile bool bRunning; 

// CICDILightDlg dialog
CICDILightDlg::CICDILightDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CICDILightDlg::IDD, pParent)
	, txtID(_T(""))
	, txtLength(_T(""))
	, txtData0(_T(""))
	, txtData1(_T(""))
	, txtData2(_T(""))
	, txtData3(_T(""))
	, txtData4(_T(""))
	, txtData5(_T(""))
	, txtData6(_T(""))
	, txtData7(_T(""))
	, chbExtended(FALSE)
	, chbRemote(FALSE)
	, txtInfo(_T(""))
	, txtIdFrom(_T(""))
	, txtIdTo(_T(""))
	, txtDeviceNumber(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CICDILightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CBBHWS, cbbHws);
	DDX_Control(pDX, IDC_BTNINFO, btnInfo);
	DDX_Control(pDX, IDC_BTNDLLINFO, btnDllInfo);
	DDX_Control(pDX, IDC_BTNINIT, btnInit);
	DDX_Control(pDX, IDC_BTNRELEASE, btnRelease);
	DDX_Control(pDX, IDC_CBBBAUDRATES, cbbBaudrates);
	DDX_Control(pDX, IDC_CBBMSGTYPE, cbbMsgType);
	DDX_Control(pDX, IDC_CBBIO, cbbIO);
	DDX_Control(pDX, IDC_CBBINTERRUPT, cbbInterrupt);
	DDX_Control(pDX, IDC_NUDLENGTH, nudLength);
	DDX_Text(pDX, IDC_TXTID, txtID);
	DDV_MaxChars(pDX, txtID, 8);
	DDX_Text(pDX, IDC_TXTLENGTH, txtLength);
	DDV_MaxChars(pDX, txtLength, 1);
	DDX_Text(pDX, IDC_TXTDATA0, txtData0);
	DDV_MaxChars(pDX, txtData0, 2);
	DDX_Text(pDX, IDC_TXTDATA1, txtData1);
	DDV_MaxChars(pDX, txtData1, 2);
	DDX_Text(pDX, IDC_TXTDATA2, txtData2);
	DDV_MaxChars(pDX, txtData2, 2);
	DDX_Text(pDX, IDC_TXTDATA3, txtData3);
	DDV_MaxChars(pDX, txtData3, 2);
	DDX_Text(pDX, IDC_TXTDATA4, txtData4);
	DDV_MaxChars(pDX, txtData4, 2);
	DDX_Text(pDX, IDC_TXTDATA5, txtData5);
	DDV_MaxChars(pDX, txtData5, 2);
	DDX_Text(pDX, IDC_TXTDATA6, txtData6);
	DDV_MaxChars(pDX, txtData6, 2);
	DDX_Text(pDX, IDC_TXTDATA7, txtData7);
	DDV_MaxChars(pDX, txtData7, 2);
	DDX_Check(pDX, IDC_CHBEXTENDED, chbExtended);
	DDX_Check(pDX, IDC_CHBREMOTE, chbRemote);
	DDX_Control(pDX, IDC_LSTMESSAGES, lstMessages);
	DDX_Control(pDX, IDC_BTNCLOSE, btnClose);
	DDX_Text(pDX, IDC_TXTINFO, txtInfo);
	DDX_Text(pDX, IDC_TXTIDFROM, txtIdFrom);
	DDV_MaxChars(pDX, txtIdFrom, 8);
	DDX_Text(pDX, IDC_TXTIDTO, txtIdTo);
	DDV_MaxChars(pDX, txtIdTo, 8);
	DDX_Control(pDX, IDC_BTNWRITE, btnWrite);
	DDX_Control(pDX, IDC_BTNSETFILTER, btnSetFilter);
	DDX_Control(pDX, IDC_BTNRESETFILTER, btnResetFilter);
	DDX_Control(pDX, IDC_BTNDEVGET, btnGetDeviceNumber);
	DDX_Control(pDX, IDC_BTNDEVSET, btnSetDeviceNumber);
	DDX_Text(pDX, IDC_TXTDEVNUMBER, txtDeviceNumber);
	DDV_MaxChars(pDX, txtDeviceNumber, 10);
	DDX_Control(pDX, IDC_CHBTIMESTAMP, chbTimeStamp);
	DDX_Control(pDX, IDC_RDBSTANDARD, rdbStandard);
	DDX_Control(pDX, IDC_RDBEXTENDED, rdbExtended);
	DDX_Control(pDX, IDC_RDBTIMER, rdbTimer);
	DDX_Control(pDX, IDC_RDBEVENT, rdbEvent);	
}

BEGIN_MESSAGE_MAP(CICDILightDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_CBBHWS, OnCbnSelchangeCbbhws)
	ON_CBN_SELCHANGE(IDC_CBBBAUDRATES, OnCbnSelchangeCbbbaudrates)
	ON_EN_KILLFOCUS(IDC_TXTID, OnEnKillfocusTxtid)
	ON_EN_KILLFOCUS(IDC_TXTDATA0, OnEnKillfocusTxtdata0)
	ON_EN_KILLFOCUS(IDC_TXTDATA1, OnEnKillfocusTxtdata1)
	ON_EN_KILLFOCUS(IDC_TXTDATA2, OnEnKillfocusTxtdata2)
	ON_EN_KILLFOCUS(IDC_TXTDATA3, OnEnKillfocusTxtdata3)
	ON_EN_KILLFOCUS(IDC_TXTDATA4, OnEnKillfocusTxtdata4)
	ON_EN_KILLFOCUS(IDC_TXTDATA5, OnEnKillfocusTxtdata5)
	ON_EN_KILLFOCUS(IDC_TXTDATA6, OnEnKillfocusTxtdata6)
	ON_EN_KILLFOCUS(IDC_TXTDATA7, OnEnKillfocusTxtdata7)
	ON_NOTIFY(UDN_DELTAPOS, IDC_NUDLENGTH, OnDeltaposNudlength)
	ON_BN_CLICKED(IDC_CHBEXTENDED, OnBnClickedChbextended)
	ON_BN_CLICKED(IDC_CHBREMOTE, OnBnClickedChbremote)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_DBLCLK, IDC_LSTMESSAGES, OnNMDblclkLstmessages)
	ON_BN_CLICKED(IDC_BTNINFO, OnBnClickedBtninfo)
	ON_BN_CLICKED(IDC_BTNINIT, OnBnClickedBtninit)
	ON_BN_CLICKED(IDC_BTNRELEASE, OnBnClickedBtnrelease)
	ON_BN_CLICKED(IDC_BTNWRITE, OnBnClickedBtnwrite)
	ON_BN_CLICKED(IDC_BTNCLOSE, OnBnClickedBtnclose)
	ON_BN_CLICKED(IDC_RDBSTANDARD, OnBnClickedRdbstandard)
	ON_BN_CLICKED(IDC_RDBEXTENDED, OnBnClickedRdbextended)
	ON_EN_KILLFOCUS(IDC_TXTIDFROM, OnEnKillfocusTxtidfrom)
	ON_EN_KILLFOCUS(IDC_TXTIDTO, OnEnKillfocusTxtidto)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTNSETFILTER, OnBnClickedBtnsetfilter)
	ON_BN_CLICKED(IDC_BTNRESETFILTER, OnBnClickedBtnresetfilter)
	ON_NOTIFY(UDN_DELTAPOS, IDC_NUDDEVNUMBER, OnDeltaposNuddevnumber)
	ON_BN_CLICKED(IDC_BTNDEVGET, OnBnClickedBtndevget)
	ON_BN_CLICKED(IDC_BTNDEVSET, OnBnClickedBtndevset)
	ON_BN_CLICKED(IDC_RDBTIMER, &CICDILightDlg::OnBnClickedRdbtimer)
	ON_BN_CLICKED(IDC_RDBEVENT, &CICDILightDlg::OnBnClickedRdbevent)
	ON_BN_CLICKED(IDC_CHBTIMESTAMP, &CICDILightDlg::OnBnClickedChbtimestamp)
	ON_BN_CLICKED(IDC_BTNDLLINFO, &CICDILightDlg::OnBnClickedBtndllinfo)
	ON_EN_KILLFOCUS(IDC_TXTDEVNUMBER, &CICDILightDlg::OnEnKillfocusTxtdevnumber)
END_MESSAGE_MAP()


// CICDILightDlg message handlers

BOOL CICDILightDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	InitializeControls();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CICDILightDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CICDILightDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// String conversion functions
//
CString CICDILightDlg::IntToStr(int iValue)
{
	char chToReceive[20];
	
	_itoa_s(iValue, chToReceive, 20, 10);

	return  chToReceive;
}

CString CICDILightDlg::IntToHex(int iValue, short iDigits)
{	
	CString strTemp, strtest;

	strTemp.Format("%0" + IntToStr(iDigits) + "X",iValue);

	return strTemp;
}
DWORD CICDILightDlg::HexTextToInt(CString ToConvert)
{
    DWORD iToReturn = 0;
    int iExp = 0;
    char chByte;

    // The string to convert is empty
    //
    if(ToConvert == "")
        return 0;
    // The string have more than 8 character (the equivalent value
    // exeeds the DWORD capacity
    //
    if(ToConvert.GetLength() > 8)
        return 0;
    // We convert any character to its Upper case
    //
	ToConvert = ToConvert.MakeUpper();

    try
    {
        // We calculate the number using the Hex To Decimal formula
        //
        for(int i= ToConvert.GetLength()-1; i >= 0; i--){
            chByte = ToConvert[i];
            switch(int(chByte)){
                case 65:
                    iToReturn += (DWORD)(10*pow(16.0f,iExp));
                    break;
                case 66:
                    iToReturn += (DWORD)(11*pow(16.0f,iExp));
                    break;
                case 67:
                    iToReturn += (DWORD)(12*pow(16.0f,iExp));
                    break;
                case 68:
                    iToReturn += (DWORD)(13*pow(16.0f,iExp));
                    break;
                case 69:
                    iToReturn += (DWORD)(14*pow(16.0f,iExp));
                    break;
                case 70:
                    iToReturn += (DWORD)(15*pow(16.0f,iExp));
                    break;
                default:
                    if((int(chByte) <48)||(int(chByte)>57))
                        return -1;
                    iToReturn += (DWORD)(atoi(&chByte)*pow(16.0f,iExp));
                    break;

            }
            iExp++;
        }
    }
    catch(...)
    {
        // Error, return 0
        //
        return 0;
    }

    return iToReturn;
}
void CICDILightDlg::InitializeControls(void)
{
	// List Control
	//
	lstMessages.InsertColumn(0,"Type",LVCFMT_LEFT,69,1);
	lstMessages.InsertColumn(1,"ID",LVCFMT_LEFT,73,2);
	lstMessages.InsertColumn(2,"Length",LVCFMT_LEFT,50,3);		
	lstMessages.InsertColumn(3,"Data",LVCFMT_LEFT,138,4);		
	lstMessages.InsertColumn(4,"Count",LVCFMT_LEFT,49,5);			
	
	lstMessages.SetExtendedStyle(lstMessages.GetExtendedStyle()|LVS_EX_FULLROWSELECT);

	// UpDown Controls
	//
	nudLength.SetRange(0,8);
	nudLength.SetPos(8);

	// Edit Controls
	//
	txtID = "000";
	txtIdFrom = "000";
	txtIdTo = "000";
	txtLength = "8";
	txtDeviceNumber = "0";
	txtData0 = "00";
	txtData1 = "00";
	txtData2 = "00";
	txtData3 = "00";
	txtData4 = "00";
	txtData5 = "00";	
	txtData6 = "00";
	txtData7 = "00";
	UpdateData(FALSE);

	// We set the variable for the current 
	// CAN Light instance to use it
	//
	ActiveCANLight = new PCANLight();

	// Thread variable is initialized to null. Default is timer reading
	//
	hThread = NULL;
	bRunning = false;

	// Create a list to store the displayed messages
	//
	LastMsgsList = new CPtrList();

    // Set the standard values in the interface
    //
    cbbHws.SetCurSel(0);
    cbbBaudrates.SetCurSel(0);
    cbbIO.SetCurSel(18);
    cbbInterrupt.SetCurSel(3);
    cbbMsgType.SetCurSel(0);

	CurrBaud = BAUD_1M;
}

void CICDILightDlg::CheckHexEditBox(CString* txtData)
{
	int iTest;

	txtData->MakeUpper();
	
	// We test if the given ID is a valid hexadecimal number.
    // 
	iTest = HexTextToInt(*txtData);
	if(iTest > 0)
		*txtData = IntToHex(iTest,2);
	else
		*txtData = "00";
}

int CICDILightDlg::AddLVItem(CString Caption)
{
	LVITEM NewItem;

	NewItem.mask = LVIF_TEXT;
	NewItem.iSubItem = 0;	
	NewItem.pszText = Caption.GetBuffer();
	NewItem.iItem = lstMessages.GetItemCount();

	lstMessages.InsertItem(&NewItem);
		 
	return NewItem.iItem;	
}

void CICDILightDlg::SetTimerRead(bool bEnable)
{
	if(bEnable)
		tmrRead = SetTimer(1, 50, 0);
	else
	{
		KillTimer(tmrRead);
		tmrRead = 0;
	}
}

void CICDILightDlg::ModifyMsgEntry(MessageStatus LastMsg,TPCANMsg NewMsg, TPCANTimestamp MyTimeStamp)
{
    CString strLastData, strNewData, msgTimeStamp;;
    MessageStatus *NewStatus,*ToDelete;
	POSITION pos;
	int iCurrItem;
    int iLen;
    int iCount;

    strNewData = strLastData = "";

    // Values of the last messages
    //
	iCurrItem = LastMsg.Position();
	iCount = atoi(lstMessages.GetItemText(iCurrItem,MSG_COUNT));

    strLastData = lstMessages.GetItemText(iCurrItem,MSG_DATA);
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
		lstMessages.SetItemText(iCurrItem,MSG_LENGTH,IntToStr(iLen));
    }

    if(strLastData != strNewData)
		lstMessages.SetItemText(iCurrItem,MSG_DATA,strNewData);

	lstMessages.SetItemText(iCurrItem,MSG_COUNT,IntToStr(iCount));

	// Update Rcv Time information if need
	//
	if(chbTimeStamp.GetCheck())
	{		
		msgTimeStamp.Format("%d.%d", MyTimeStamp.millis, MyTimeStamp.micros);
		lstMessages.SetItemText(iCurrItem, MSG_TIME, msgTimeStamp);
	}

    // Save the new Status of the message
    // NOTE: The objects are saved in the same index position which
    // they use in the Listview
    //
    NewStatus = new MessageStatus(&NewMsg,LastMsg.Position());
	pos = LastMsgsList->FindIndex(LastMsg.Position());
	ToDelete = (MessageStatus*)LastMsgsList->GetAt(pos);
	LastMsgsList->InsertAfter(pos,NewStatus);
	LastMsgsList->RemoveAt(pos);
    delete ToDelete;
}

void CICDILightDlg::InsertMsgEntry(TPCANMsg NewMsg, TPCANTimestamp MyTimeStamp)
{
    CString  strNewData, strTemp, msgTimeStamp;
    int iCurrItem;
    MessageStatus *ToInsert;

    strTemp = strNewData = "";

    // Add the new ListView Item with the type of the message
    //
    if((NewMsg.MSGTYPE & MSGTYPE_EXTENDED) != 0)
        strTemp = "EXTENDED";
    else
        strTemp = "STANDARD";

    if((NewMsg.MSGTYPE & MSGTYPE_RTR) == MSGTYPE_RTR)
        strTemp = (strTemp + "/RTR");
    
	iCurrItem = AddLVItem(strTemp);

    // We format the ID of the message and show it
    //
    if((NewMsg.MSGTYPE & MSGTYPE_EXTENDED) != 0)
		lstMessages.SetItemText(iCurrItem,MSG_ID,IntToHex((int)NewMsg.ID,8) + "h");
    else
        lstMessages.SetItemText(iCurrItem,MSG_ID,IntToHex((int)NewMsg.ID,3) + "h");

    // We set the length of the message
    //
	lstMessages.SetItemText(iCurrItem,MSG_LENGTH,IntToStr(NewMsg.LEN));

    // We format the data of the message. Each data is one
    // byte of Hexadecimal data
    //
    if((NewMsg.MSGTYPE & MSGTYPE_RTR) == MSGTYPE_RTR)
        strNewData = "Remote Request";
    else
        for(int i=0; i< NewMsg.LEN; i++)
            strNewData = (strNewData + IntToHex(NewMsg.DATA[i],2) + " ");

    lstMessages.SetItemText(iCurrItem,MSG_DATA,strNewData);

    // The message is the first one, so count is 1
    //
	lstMessages.SetItemText(iCurrItem,MSG_COUNT,"1");

	// Add Rcv Time information if need
	//
	if(chbTimeStamp.GetCheck())
	{
		msgTimeStamp.Format("%d.%d", MyTimeStamp.millis, MyTimeStamp.micros);
		lstMessages.SetItemText(iCurrItem, MSG_TIME, msgTimeStamp);
	}

    // We add this status in the last message list
    //
    ToInsert = new MessageStatus(&NewMsg,iCurrItem);
    LastMsgsList->AddTail(ToInsert);
}

void CICDILightDlg::ProcessMessage(TPCANMsg MyMsg, TPCANTimestamp MyTimeStamp)
{
    bool bFound = false;
    MessageStatus *CurrMessage;
	POSITION pos;

    // We search if a message (same ID, type, and Net) was
    // already received, or if this is a new message
    //
	pos = LastMsgsList->GetHeadPosition();
    for(int i=0; i< LastMsgsList->GetCount(); i++)
    {
		CurrMessage = (MessageStatus*)LastMsgsList->GetNext(pos);
        if(CurrMessage->CANMessage().ID == MyMsg.ID)
            if(CurrMessage->CANMessage().MSGTYPE == MyMsg.MSGTYPE)
            {
                bFound = true;
                break;
            }
    }

    if(bFound)
        // Messages of this kind were already received; we make an update
        //
        ModifyMsgEntry(*CurrMessage,MyMsg, MyTimeStamp);
    else
        // Messages of this kind were not received; we make a new entry
        //
        InsertMsgEntry(MyMsg, MyTimeStamp);	
}
void CICDILightDlg::ReadMessage()
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
		if(chbTimeStamp.GetCheck())
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


void CICDILightDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == 1)
		// Read Pending Message
		//
		ReadMessage();
	CDialog::OnTimer(nIDEvent);
}

void CICDILightDlg::OnCbnSelchangeCbbhws()
{
	bool bShowIO;
	int current;

	current = cbbHws.GetCurSel();

    // According to the selection in the Hardware list,
    // we show/hide the input controls for I/O Address and
    // Interrupt (these parameters are NOT necessary for all
    // hardware types).
    //
	switch (current)
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

	cbbIO.EnableWindow(bShowIO);
    cbbInterrupt.EnableWindow(bShowIO);

	// According to the selection in the Hardware list, we 
	// enable/disable the controls for get/set the USB device number.
	//
	btnGetDeviceNumber.EnableWindow(((current == USB_1CH) || (current == USB_2CH)) &&  btnWrite.IsWindowEnabled());
	btnSetDeviceNumber.EnableWindow(btnGetDeviceNumber.IsWindowEnabled());	
	((CEdit*)GetDlgItem(IDC_TXTDEVNUMBER))->EnableWindow(btnGetDeviceNumber.IsWindowEnabled());	
}

void CICDILightDlg::OnCbnSelchangeCbbbaudrates()
{
    // We save the corresponding Baudrate enumeration
    // type value for every selected Baudrate from the
    // list.
    //
    switch(cbbBaudrates.GetCurSel())
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

void CICDILightDlg::OnEnKillfocusTxtid()
{
    int iTest;

	UpdateData(TRUE);
	txtID.MakeUpper();
	
	iTest = HexTextToInt(txtID);

	if(chbExtended)
	{		
		if(iTest > 0)
			txtID = IntToHex(iTest,8);
		else
			txtID = "00000000";
	}
	else
	{
		if(iTest > 0x7FF)
			txtID = "7FF";
		else
		{
			// We test if the given ID is a valid hexadecimal number.
			// 
			iTest = HexTextToInt(txtID);
			if(iTest > 0)
				txtID = IntToHex(iTest,3);
			else
				txtID = "000";
		}
	}

	UpdateData(FALSE);
}

void CICDILightDlg::OnEnKillfocusTxtdata0()
{
	UpdateData(TRUE);
	CheckHexEditBox(&txtData0);
	UpdateData(FALSE);
}

void CICDILightDlg::OnEnKillfocusTxtdata1()
{
	UpdateData(TRUE);
	CheckHexEditBox(&txtData1);
	UpdateData(FALSE);
}

void CICDILightDlg::OnEnKillfocusTxtdata2()
{
	UpdateData(TRUE);
	CheckHexEditBox(&txtData2);
	UpdateData(FALSE);
}

void CICDILightDlg::OnEnKillfocusTxtdata3()
{
	UpdateData(TRUE);
	CheckHexEditBox(&txtData3);
	UpdateData(FALSE);
}

void CICDILightDlg::OnEnKillfocusTxtdata4()
{
	UpdateData(TRUE);
	CheckHexEditBox(&txtData4);
	UpdateData(FALSE);
}

void CICDILightDlg::OnEnKillfocusTxtdata5()
{
	UpdateData(TRUE);
	CheckHexEditBox(&txtData5);
	UpdateData(FALSE);
}

void CICDILightDlg::OnEnKillfocusTxtdata6()
{
	UpdateData(TRUE);
	CheckHexEditBox(&txtData6);
	UpdateData(FALSE);
}

void CICDILightDlg::OnEnKillfocusTxtdata7()
{
	UpdateData(TRUE);
	CheckHexEditBox(&txtData7);
	UpdateData(FALSE);
}

void CICDILightDlg::OnEnKillfocusTxtidfrom()
{
    int iTest;

	UpdateData(TRUE);
	txtIdFrom.MakeUpper();
	
	iTest = HexTextToInt(txtIdFrom);

	//if(rdbExtended)
	if(rdbExtended.GetCheck())
	{		
		if(iTest > 0)
			txtIdFrom = IntToHex(iTest,8);
		else
			txtIdFrom = "00000000";
	}
	else
	{
		if(iTest > 0x7FF)
			txtIdFrom = "7FF";
		else
		{
			// We test if the given ID is a valid hexadecimal number.
			// 
			iTest = HexTextToInt(txtIdFrom);
			if(iTest > 0)
				txtIdFrom = IntToHex(iTest,3);
			else
				txtIdFrom = "000";
		}
	}

	UpdateData(FALSE);
}

void CICDILightDlg::OnEnKillfocusTxtidto()
{
    int iTest;

	UpdateData(TRUE);
	txtIdTo.MakeUpper();
	
	iTest = HexTextToInt(txtIdTo);

	//if(rdbExtended)
	if(rdbExtended.GetCheck())
	{		
		if(iTest > 0)
			txtIdTo = IntToHex(iTest,8);
		else
			txtIdTo = "00000000";
	}
	else
	{
		if(iTest > 0x7FF)
			txtIdTo = "7FF";
		else
		{
			// We test if the given ID is a valid hexadecimal number.
			// 
			iTest = HexTextToInt(txtIdTo);
			if(iTest > 0)
				txtIdTo = IntToHex(iTest,3);
			else
				txtIdTo = "000";
		}
	}

	UpdateData(FALSE);
}

void CICDILightDlg::OnDeltaposNudlength(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	int iNewVal;

	iNewVal =  pNMUpDown->iPos + ((pNMUpDown->iDelta > 0) ? 1 : -1);
	if(iNewVal > 8){
		iNewVal = 8;
		pNMUpDown->iPos -= 1;
	}
	if(iNewVal < 0)
		iNewVal = 0;
	txtLength = IntToStr(iNewVal);
	UpdateData(FALSE);

	*pResult = 0;

	((CEdit*)GetDlgItem(IDC_TXTDATA0))->EnableWindow(0 < iNewVal);
	((CEdit*)GetDlgItem(IDC_TXTDATA1))->EnableWindow(1 < iNewVal);
	((CEdit*)GetDlgItem(IDC_TXTDATA2))->EnableWindow(2 < iNewVal);
	((CEdit*)GetDlgItem(IDC_TXTDATA3))->EnableWindow(3 < iNewVal);
	((CEdit*)GetDlgItem(IDC_TXTDATA4))->EnableWindow(4 < iNewVal);
	((CEdit*)GetDlgItem(IDC_TXTDATA5))->EnableWindow(5 < iNewVal);
	((CEdit*)GetDlgItem(IDC_TXTDATA6))->EnableWindow(6 < iNewVal);
	((CEdit*)GetDlgItem(IDC_TXTDATA7))->EnableWindow(7 < iNewVal);
}

void CICDILightDlg::OnBnClickedChbextended()
{
	OnEnKillfocusTxtid();
}

void CICDILightDlg::OnBnClickedChbremote()
{
	UpdateData(TRUE);

	((CEdit*)GetDlgItem(IDC_TXTDATA0))->ShowWindow((chbRemote) ? SW_HIDE : SW_SHOW);
	((CEdit*)GetDlgItem(IDC_TXTDATA1))->ShowWindow((chbRemote) ? SW_HIDE : SW_SHOW);
	((CEdit*)GetDlgItem(IDC_TXTDATA2))->ShowWindow((chbRemote) ? SW_HIDE : SW_SHOW);
	((CEdit*)GetDlgItem(IDC_TXTDATA3))->ShowWindow((chbRemote) ? SW_HIDE : SW_SHOW);
	((CEdit*)GetDlgItem(IDC_TXTDATA4))->ShowWindow((chbRemote) ? SW_HIDE : SW_SHOW);
	((CEdit*)GetDlgItem(IDC_TXTDATA5))->ShowWindow((chbRemote) ? SW_HIDE : SW_SHOW);
	((CEdit*)GetDlgItem(IDC_TXTDATA6))->ShowWindow((chbRemote) ? SW_HIDE : SW_SHOW);
	((CEdit*)GetDlgItem(IDC_TXTDATA7))->ShowWindow((chbRemote) ? SW_HIDE : SW_SHOW);
}

void CICDILightDlg::OnClose()
{
	// Release Hardware if it is needed
	//
	if(btnRelease.IsWindowEnabled())
		OnBnClickedBtnrelease();

    while(LastMsgsList->GetCount())
		delete LastMsgsList->RemoveHead();
    delete LastMsgsList;

	delete ActiveCANLight;

	CDialog::DestroyWindow();
}

void CICDILightDlg::OnNMDblclkLstmessages(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	lstMessages.DeleteAllItems();
	
    while(LastMsgsList->GetCount())
		delete LastMsgsList->RemoveHead();
}

void CICDILightDlg::OnBnClickedBtninfo()
{
	char versionInfoResult[255];    
	CString strInfo;
    CANResult Res;

    // We execute the "VersionInfo" function of the PCANLight
    // using as parameter the Hardware type and a string
    // variable to get the info.
    //
    Res = ActiveCANLight->VersionInfo(versionInfoResult);
	strInfo = versionInfoResult;
	strInfo.Replace("\n","\r\n");

    // The function was successfully executed
    //
    if(Res == ERR_OK)
        // We show the Version Information
        //
        txtInfo = strInfo;
        // An error occurred.  We show the error.
        //
    else
        txtInfo  = "Error Number: 0x" + IntToHex(Res,4);
	UpdateData(FALSE);
}

void CICDILightDlg::OnBnClickedBtndllinfo()
{
	char dllVersionInfoResult[255];
	CString strInfo;
	CString hardwareLabel;
    CANResult Res;

    // We execute the "DllVersionInfo" function of the PCANLight
    // using as parameter the Hardware type and a string
    // variable to get the info.
    //
    Res = ActiveCANLight->DllVersionInfo(dllVersionInfoResult);
	strInfo = dllVersionInfoResult;	

    // The function was successfully executed
    //
    if(Res == ERR_OK)
	{
        // We show the Dll Version Information
        //
		cbbHws.GetLBText(cbbHws.GetCurSel(), hardwareLabel);
		txtInfo = hardwareLabel + " Dll Version: " + strInfo;
	}
        // An error occurred.  We show the error.
        //
    else
        txtInfo  = "No DLL Info Available.";
	UpdateData(FALSE);
}
void CICDILightDlg::OnBnClickedBtninit()
{
    CANResult Res;
	CString strIO, strInterrupt, strTemp;

	// We try to initialize selected Hardware Type
	//
	if(!ActiveCANLight->InitializeAPI((HardwareType)cbbHws.GetCurSel()))
	{
		::MessageBox(NULL,"DLL 2.x or later are required to run this program.\r\nPlease, download lastest DLL version on http://www.peak-system.com or refer to the documentation for more information.", 
			"Dll Version", MB_ICONERROR);
	}
	else
	{

		// According to the active parameters/hardware, we
		// use one of the two possible "Init" PCANLight functions.
		// One is for Plug-and-Play hardware, and the other for
		// Non-P&P.
		//
		if(cbbIO.IsWindowEnabled())
		{
			// Non-P&P Hardware
			//
			cbbIO.GetWindowText(strIO);
			cbbInterrupt.GetWindowText(strInterrupt);
			Res = ActiveCANLight->Init(CurrBaud,
				(FramesType)cbbMsgType.GetCurSel(),
				HexTextToInt(strIO),
				atoi(strInterrupt));
		}
		else
			// P&P Hardware
			//
			Res = ActiveCANLight->Init(CurrBaud,
				(FramesType)cbbMsgType.GetCurSel());

		// The Hardware was successfully initiated
		//
		if(Res == ERR_OK)
		{
            // We start to read from the CAN Queue
            //
            ReadingModeChanged();

			// We set UI enable
			//
			btnInfo.EnableWindow(true);
			btnDllInfo.EnableWindow(true);
			btnResetFilter.EnableWindow(true);
			btnWrite.EnableWindow(true);
			btnRelease.EnableWindow(true);
			btnSetFilter.EnableWindow(true);
			btnResetFilter.EnableWindow(true);
			btnInit.EnableWindow(false);
			OnCbnSelchangeCbbhws();
			cbbHws.EnableWindow(false);
			rdbTimer.EnableWindow(true);
			rdbEvent.EnableWindow(true);
			chbTimeStamp.EnableWindow(true);

			// We show the information of the configured
			// and initiated hardware
			//
			cbbHws.GetWindowText(strTemp);
			txtInfo = "Active Hardware: " + strTemp;
			cbbBaudrates.GetWindowText(strTemp);
			txtInfo += "\r\nBaud Rate: " + strTemp;
			cbbMsgType.GetWindowText(strTemp);
			txtInfo += "\r\nFrame Type: " + strTemp;
			// If hardware is a Non-P&P hardware, we show additional information
			//
			if(cbbIO.IsWindowEnabled())
			{
				cbbIO.GetWindowText(strTemp);
				txtInfo += "\r\nI/O Addr.: " + strTemp + "h";
				cbbInterrupt.GetWindowText(strTemp);
				txtInfo += "\r\nInterrupt: " + strTemp;
			}
		}
			// An error occurred.  We show the error.
			//
		else
			txtInfo  = "Error Number: 0x" + IntToHex(Res,4);

		UpdateData(FALSE);
	}
}

void CICDILightDlg::OnBnClickedBtnrelease()
{
    CANResult Res;

    // We stop to read from the CAN queue
    //
    SetTimerRead(false);

	// Terminate Read Thread if it exists
	//
	if(hThread != NULL)
		// Causes the thread to terminate
		// and wai for termination
		//
		bRunning = false;

    // We close the active hardware using the
    // "Close" function of the PCANLight API using
    // the hardware type as parameter.
    //
    Res = ActiveCANLight->Close();

    // The hardware was successfully closed
    //
    if(Res == ERR_OK)
        txtInfo = "Hardware was successfully Released.\r\n";
        // An error occurred.  We show the error.
        //
    else
        txtInfo = "Error Number: 0x" + IntToHex(Res,4);

	UpdateData(FALSE);

    // We activate/deactivate the corresponding buttons
    //
	btnInfo.EnableWindow(false);
	btnDllInfo.EnableWindow(false);
    btnInit.EnableWindow(true);
    btnWrite.EnableWindow(false);
    btnRelease.EnableWindow(false);
	btnSetFilter.EnableWindow(false);
	btnResetFilter.EnableWindow(false);
	cbbHws.EnableWindow(true);
	rdbTimer.EnableWindow(false);
	rdbEvent.EnableWindow(false);
	chbTimeStamp.EnableWindow(false);
	OnCbnSelchangeCbbhws();
}

void CICDILightDlg::OnBnClickedBtnwrite()
{
    TPCANMsg MsgToSend;
    CANResult Res;

	UpdateData(TRUE);
    // We configure the message.  The ID (max 0x7FF),
    // Length of the Data, Message Type (Standard in
    // this example), and the data
    //
    MsgToSend.ID = HexTextToInt(txtID);
    MsgToSend.LEN = nudLength.GetPos();
    MsgToSend.MSGTYPE = (chbExtended) ? MSGTYPE_EXTENDED : MSGTYPE_STANDARD;

    // If a remote frame will be sent, the data bytes are not important.
    //
    if(chbRemote)
        MsgToSend.MSGTYPE |= MSGTYPE_RTR;
    else
	{
        // We get the data of the message
        //
		MsgToSend.DATA[0] = BYTE(HexTextToInt(txtData0));
		MsgToSend.DATA[1] = BYTE(HexTextToInt(txtData1));
		MsgToSend.DATA[2] = BYTE(HexTextToInt(txtData2));
		MsgToSend.DATA[3] = BYTE(HexTextToInt(txtData3));
		MsgToSend.DATA[4] = BYTE(HexTextToInt(txtData4));
		MsgToSend.DATA[5] = BYTE(HexTextToInt(txtData5));
		MsgToSend.DATA[6] = BYTE(HexTextToInt(txtData6));
		MsgToSend.DATA[7] = BYTE(HexTextToInt(txtData7));
    }

    // The message is sent to the configured hardware
    //
    Res = ActiveCANLight->Write(&MsgToSend);

    // The hardware was successfully sent
    //
    if(Res == ERR_OK)
        txtInfo = "Message was successfully SENT.\r\n";
        // An error occurred.  We show the error.
        //
    else
        txtInfo = "Error Number: 0x" + IntToHex(Res,4);
	UpdateData(FALSE);
}

void CICDILightDlg::OnBnClickedBtnclose()
{
	// Close This Application
	//
	OnClose();
}

void CICDILightDlg::OnBnClickedRdbstandard()
{
	OnEnKillfocusTxtidfrom();
	OnEnKillfocusTxtidto();
}

void CICDILightDlg::OnBnClickedRdbextended()
{
	OnEnKillfocusTxtidfrom();
	OnEnKillfocusTxtidto();
}

void CICDILightDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	rdbStandard.SetCheck(true);
	rdbTimer.SetCheck(true);
	chbTimeStamp.SetCheck(true);
	OnBnClickedChbtimestamp();
}

void CICDILightDlg::OnBnClickedBtnsetfilter()
{
    DWORD FromID, ToID;
    CANResult Res;

	UpdateData(TRUE);

	// The range IDs is read
    //
    FromID = HexTextToInt(txtIdFrom); 
    ToID = HexTextToInt(txtIdTo);
            
    // The desired filter is set on the configured hardware
    //
	Res = ActiveCANLight->MsgFilter(FromID,ToID,rdbStandard.GetCheck() ? MSGTYPE_STANDARD : MSGTYPE_EXTENDED);

    // The filter was successfully set
    //
    if (Res == ERR_OK)
        txtInfo = "Filter was successfully SET.\r\n";
    // An error occurred.  We show the error.
    //			
    else
        txtInfo = "Error Number: 0x" + IntToHex(Res,4);

	UpdateData(FALSE);
}

void CICDILightDlg::OnBnClickedBtnresetfilter()
{
    CANResult Res;

	UpdateData(TRUE);
    // The current filter on the configured hardware is reset 
    //
	Res = ActiveCANLight->ResetFilter();

    // The filter was successfully reset
    //
    if (Res == ERR_OK)
        txtInfo = "Filter was successfully RESET.\r\n";
    // An error occurred.  We show the error.
    //			
    else
        txtInfo = "Error Number: 0x" + IntToHex(Res,4);
	UpdateData(FALSE);
}

void CICDILightDlg::OnDeltaposNuddevnumber(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	DWORD iNewVal;

	iNewVal =  pNMUpDown->iPos + ((pNMUpDown->iDelta > 0) ? 1 : -1);
	if(iNewVal > 4294967295){
		iNewVal = 4294967295;
		pNMUpDown->iPos -= 1;
	}
	if(iNewVal < 0)
		iNewVal = 0;
	txtDeviceNumber = IntToStr(iNewVal);
	UpdateData(FALSE);

	*pResult = 0;
}

void CICDILightDlg::OnBnClickedBtndevget()
{
	DWORD iDevNum;
	CANResult Res;

	// Get the USB Device Number
	//
	Res = ActiveCANLight->GetUSBDeviceNr(&iDevNum);

	// The Device number was gotten successfully
	//
	if(Res == ERR_OK)
		txtInfo = "USB Device Number is: " +  IntToStr(iDevNum) + ".\r\n";
		// An error occurred.  We show the error.
		//			
	else
		txtInfo = "Error Number: 0x" + IntToHex(Res,4);

	UpdateData(FALSE);
}

void CICDILightDlg::OnBnClickedBtndevset()
{
	char *StopStr;
	CANResult Res;
	
	UpdateData(TRUE);

	// Set the USB Device Number
	//		
	StopStr = "\r\n";	
	Res = ActiveCANLight->SetUSBDeviceNr(strtoul(txtDeviceNumber,&StopStr,10));

	// The Device number was set successfully
	//
	if(Res == ERR_OK)
		txtInfo = "USB Device Number was set";
		// An error occurred.  We show the error.
		//
	else
		txtInfo = "Set USB Device Number failed: 0x" + IntToHex(Res,4);	

	UpdateData(FALSE);
}

void CICDILightDlg::OnBnClickedRdbtimer()
{
	// Check for a ReadMode change 
	//
	ReadingModeChanged();
}

void CICDILightDlg::OnBnClickedRdbevent()
{
	// Check for a ReadMode change 
	//
	ReadingModeChanged();
}

// This function is used to call 
//
DWORD WINAPI CICDILightDlg::CallCANReadThreadFunc(LPVOID lpParam) 
{
	// Cast lpParam argument to CICDILightDlg*
	CICDILightDlg* dialog = (CICDILightDlg*)lpParam;

	// Call CICDILightDlg Thread member function
	//
	return dialog->CANReadThreadFunc(NULL);
}

DWORD WINAPI CICDILightDlg::CANReadThreadFunc(LPVOID lpParam) 
{
	CANResult Res;
	HANDLE hEvent;

	// Create Event to use Received-event
	//
	hEvent = CreateEvent(NULL, FALSE, FALSE, "");
	bRunning = true;

	// We execute the "SetRcvEvent" function of the PCANLight
	// using as parameter the Hardware type and a HANDLE
	// variable to set the Received-Event.
	//
	Res = ActiveCANLight->SetRcvEvent(hEvent);

	// The function was successfully executed
	//
	if(Res != ERR_OK)
	{
		txtInfo  = "Error Number: 0x" + IntToHex(Res,4);
		return 1;
	}

	// Looks for messages until the user terminates the thread
	//
	while(bRunning)
 	{
		//Wait for CAN Data...
		//
		if(WaitForSingleObject(hEvent, 50) == WAIT_OBJECT_0)
			ReadMessage();
	}

	ActiveCANLight->SetRcvEvent(0);
	CloseHandle(hEvent);

	return 0;	
}

void CICDILightDlg::ReadingModeChanged()
{
	// If active reading mode is By Timer
	//
	if(rdbTimer.GetCheck())
	{
		// if the Thread exists, we are changing to Timer mode 
		//
		if(bRunning)
			// Causes the thread to terminate
			// and wai for termination
			//
			bRunning = false;

		// We start to read with timer
		//
		SetTimerRead(true);
	}
	// If active reading mode is By Event
	//
	else
	{
		// We stop reading with timer
		//
		SetTimerRead(false);

		// If the Thread doens't exists, we are changing to Event mode
		//
		if(!bRunning)
		{			
			if(hThread != NULL)
			{
				CloseHandle(hThread);
				hThread = NULL;
			}

			// Create Reading Thread ....
			//
			hThread = CreateThread(NULL, NULL, CICDILightDlg::CallCANReadThreadFunc, (LPVOID)this, NULL, NULL);

			if(hThread == NULL)
				::MessageBox(NULL,"Create CANRead-Thread failed","Error!",MB_ICONERROR);
		}
	}
}

void CICDILightDlg::OnBnClickedChbtimestamp()
{
	// If Show Time Stamp is selected
	//
	if(chbTimeStamp.GetCheck())
	{
		// Add "Rcv Time" column in List
		//
		if(lstMessages.GetHeaderCtrl()->GetItemCount() < 6)
			lstMessages.InsertColumn(5,"Rcv Time",LVCFMT_LEFT,100,5);
	}
	else
	{
		// Remove "Rcv Time" column in List
		//
		if(lstMessages.GetHeaderCtrl()->GetItemCount() == 6)
			lstMessages.DeleteColumn(5);
	}
}

void CICDILightDlg::OnEnKillfocusTxtdevnumber()
{
	char *StopStr;
	DWORD dwValue;
	char tempText[12];

	UpdateData(TRUE);

	// Get the desired Device Number in text
	// and convert it to DWORD.
	//
	StopStr = "\r\n";	
	dwValue = strtoul(txtDeviceNumber,&StopStr,10);	

	// Now we convert the value back to string. 
	// The convertion check automatic for a wrong value.
	//
	_ultoa_s(dwValue, tempText,12,10);
	txtDeviceNumber = tempText;
	UpdateData(FALSE);
}
