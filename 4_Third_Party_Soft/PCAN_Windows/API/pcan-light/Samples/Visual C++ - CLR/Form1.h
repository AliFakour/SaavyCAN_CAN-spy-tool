#pragma once


namespace ICDILight {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace Peak::Can::Light;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	#pragma region Structures
	/// <summary>
	/// Message Status structure used to show CAN Messages
	/// in a ListView
	/// </summary>
	ref struct MessageStatus
	{
		private: TCLightMsg^ Msg;
		private: int iIndex;

		public: MessageStatus()
		{
			Msg = gcnew TCLightMsg();
			iIndex = -1;
		}

		public: MessageStatus(TCLightMsg^ CanMsg,int Index)
		{
			Msg = CanMsg;
			iIndex = Index;
		}

		public: property TCLightMsg^ CANMessage
		{
			TCLightMsg^ get() { return Msg; }
		}

		public: property int Position
		{
			int get() { return iIndex; }
		}
	};
	#pragma endregion
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			// We set the variable to know which hardware is 
			// currently selected (none!)
			//
			ActiveHardware = (HardwareType)(-1);
			// Create a list to store the displayed mesasges 
			//
			LastMsgsList = gcnew ArrayList();
			// Create Delegates to use invoke() function
			//
			ReadDelegate = gcnew ReadDelegateHandler(this, &Form1::ReadMessage);
			// Create AutoResetEvent to use PCLight SetRcvEvent() function
			//
			RcvEvent = gcnew AutoResetEvent(false);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	/// <summary>
	/// Save the current initiated hardware type
	/// </summary>
	private: HardwareType ActiveHardware;

	/// <summary>
	/// CAN messages Array. Store the Message Status for its display
	/// </summary>
	private: ArrayList^ LastMsgsList;

	/// <summary>
	/// Read Delegate Handler
	/// </summary>
	private: delegate void ReadDelegateHandler();

	/// <summary>
	/// Read Delegate in order to call "ReadMessage" function
	/// using .NET invoke function
	/// </summary>
	private: ReadDelegateHandler^ ReadDelegate;

	/// <summary>
	/// Receive-Event
	/// </summary>
	private: AutoResetEvent^ RcvEvent;

	/// <summary>
	/// Thread in order to read messages using Received-Event method
	/// </summary>
	private: Thread^ ReadThread;

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  btnClose;
	private: System::Windows::Forms::Button^  btnRelease;
	private: System::Windows::Forms::Button^  btnInit;
	private: System::Windows::Forms::Button^  btnInfo;
	private: System::Windows::Forms::ComboBox^  cbbInterrupt;
	private: System::Windows::Forms::ComboBox^  cbbIO;
	private: System::Windows::Forms::ComboBox^  cbbMsgType;
	private: System::Windows::Forms::ComboBox^  cbbBaudrates;
	private: System::Windows::Forms::ComboBox^  cbbHws;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  txtData0;
	private: System::Windows::Forms::NumericUpDown^  nudLength;
	private: System::Windows::Forms::TextBox^  txtID;
	private: System::Windows::Forms::TextBox^  txtData7;
	private: System::Windows::Forms::TextBox^  txtData6;
	private: System::Windows::Forms::TextBox^  txtData5;
	private: System::Windows::Forms::TextBox^  txtData4;
	private: System::Windows::Forms::TextBox^  txtData3;
	private: System::Windows::Forms::TextBox^  txtData2;
	private: System::Windows::Forms::TextBox^  txtData1;
	private: System::Windows::Forms::CheckBox^  chbRemote;
	private: System::Windows::Forms::CheckBox^  chbExtended;
	private: System::Windows::Forms::Button^  btnWrite;
	private: System::Windows::Forms::ListView^  lstMessages;
	private: System::Windows::Forms::ColumnHeader^  clhType;
	private: System::Windows::Forms::ColumnHeader^  clhID;
	private: System::Windows::Forms::ColumnHeader^  clhLength;
	private: System::Windows::Forms::ColumnHeader^  clhData;
	private: System::Windows::Forms::ColumnHeader^  clhCount;
	private: System::Windows::Forms::TextBox^  txtInfo;
	private: System::Windows::Forms::Timer^  tmrRead;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::RadioButton^  rdbStandard;
	private: System::Windows::Forms::RadioButton^  rdbExtended;
	private: System::Windows::Forms::TextBox^  txtIdTo;
	private: System::Windows::Forms::TextBox^  txtIdFrom;
	private: System::Windows::Forms::Button^  btnResetFilter;
	private: System::Windows::Forms::Button^  btnSetFilter;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label9;

	private: System::Windows::Forms::Button^  btnGetDevNumber;
	private: System::Windows::Forms::Button^  btnSetDevNumber;
	private: System::Windows::Forms::Button^  btnDllInfo;
	private: System::Windows::Forms::ColumnHeader^  clhRcvTime;
	private: System::Windows::Forms::CheckBox^  chbTimeStamp;
	private: System::Windows::Forms::Label^  labelReadMethod;
	private: System::Windows::Forms::RadioButton^  rdbEvent;
	private: System::Windows::Forms::RadioButton^  rdbTimer;
private: System::Windows::Forms::TextBox^  txtDevNumber;
	private: System::ComponentModel::IContainer^  components;

	#pragma region Windows Form Designer generated code
	/// <summary>
	/// Required method for Designer support - do not modify
	/// the contents of this method with the code editor.
	/// </summary>
	void InitializeComponent(void)
	{
		this->components = (gcnew System::ComponentModel::Container());
		System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
		this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
		this->txtDevNumber = (gcnew System::Windows::Forms::TextBox());
		this->btnDllInfo = (gcnew System::Windows::Forms::Button());
		this->btnGetDevNumber = (gcnew System::Windows::Forms::Button());
		this->btnSetDevNumber = (gcnew System::Windows::Forms::Button());
		this->btnRelease = (gcnew System::Windows::Forms::Button());
		this->btnInit = (gcnew System::Windows::Forms::Button());
		this->btnInfo = (gcnew System::Windows::Forms::Button());
		this->cbbInterrupt = (gcnew System::Windows::Forms::ComboBox());
		this->cbbIO = (gcnew System::Windows::Forms::ComboBox());
		this->cbbMsgType = (gcnew System::Windows::Forms::ComboBox());
		this->cbbBaudrates = (gcnew System::Windows::Forms::ComboBox());
		this->cbbHws = (gcnew System::Windows::Forms::ComboBox());
		this->label5 = (gcnew System::Windows::Forms::Label());
		this->label4 = (gcnew System::Windows::Forms::Label());
		this->label3 = (gcnew System::Windows::Forms::Label());
		this->label2 = (gcnew System::Windows::Forms::Label());
		this->label1 = (gcnew System::Windows::Forms::Label());
		this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
		this->btnWrite = (gcnew System::Windows::Forms::Button());
		this->chbRemote = (gcnew System::Windows::Forms::CheckBox());
		this->chbExtended = (gcnew System::Windows::Forms::CheckBox());
		this->txtData7 = (gcnew System::Windows::Forms::TextBox());
		this->txtData6 = (gcnew System::Windows::Forms::TextBox());
		this->txtData5 = (gcnew System::Windows::Forms::TextBox());
		this->txtData4 = (gcnew System::Windows::Forms::TextBox());
		this->txtData3 = (gcnew System::Windows::Forms::TextBox());
		this->txtData2 = (gcnew System::Windows::Forms::TextBox());
		this->txtData1 = (gcnew System::Windows::Forms::TextBox());
		this->txtData0 = (gcnew System::Windows::Forms::TextBox());
		this->nudLength = (gcnew System::Windows::Forms::NumericUpDown());
		this->txtID = (gcnew System::Windows::Forms::TextBox());
		this->label8 = (gcnew System::Windows::Forms::Label());
		this->label7 = (gcnew System::Windows::Forms::Label());
		this->label6 = (gcnew System::Windows::Forms::Label());
		this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
		this->labelReadMethod = (gcnew System::Windows::Forms::Label());
		this->rdbEvent = (gcnew System::Windows::Forms::RadioButton());
		this->rdbTimer = (gcnew System::Windows::Forms::RadioButton());
		this->chbTimeStamp = (gcnew System::Windows::Forms::CheckBox());
		this->lstMessages = (gcnew System::Windows::Forms::ListView());
		this->clhType = (gcnew System::Windows::Forms::ColumnHeader());
		this->clhID = (gcnew System::Windows::Forms::ColumnHeader());
		this->clhLength = (gcnew System::Windows::Forms::ColumnHeader());
		this->clhData = (gcnew System::Windows::Forms::ColumnHeader());
		this->clhCount = (gcnew System::Windows::Forms::ColumnHeader());
		this->clhRcvTime = (gcnew System::Windows::Forms::ColumnHeader());
		this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
		this->txtInfo = (gcnew System::Windows::Forms::TextBox());
		this->btnClose = (gcnew System::Windows::Forms::Button());
		this->tmrRead = (gcnew System::Windows::Forms::Timer(this->components));
		this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
		this->rdbStandard = (gcnew System::Windows::Forms::RadioButton());
		this->rdbExtended = (gcnew System::Windows::Forms::RadioButton());
		this->txtIdTo = (gcnew System::Windows::Forms::TextBox());
		this->txtIdFrom = (gcnew System::Windows::Forms::TextBox());
		this->btnResetFilter = (gcnew System::Windows::Forms::Button());
		this->btnSetFilter = (gcnew System::Windows::Forms::Button());
		this->label10 = (gcnew System::Windows::Forms::Label());
		this->label9 = (gcnew System::Windows::Forms::Label());
		this->groupBox1->SuspendLayout();
		this->groupBox2->SuspendLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->nudLength))->BeginInit();
		this->groupBox3->SuspendLayout();
		this->groupBox4->SuspendLayout();
		this->groupBox5->SuspendLayout();
		this->SuspendLayout();
		// 
		// groupBox1
		// 
		this->groupBox1->Controls->Add(this->txtDevNumber);
		this->groupBox1->Controls->Add(this->btnDllInfo);
		this->groupBox1->Controls->Add(this->btnGetDevNumber);
		this->groupBox1->Controls->Add(this->btnSetDevNumber);
		this->groupBox1->Controls->Add(this->btnRelease);
		this->groupBox1->Controls->Add(this->btnInit);
		this->groupBox1->Controls->Add(this->btnInfo);
		this->groupBox1->Controls->Add(this->cbbInterrupt);
		this->groupBox1->Controls->Add(this->cbbIO);
		this->groupBox1->Controls->Add(this->cbbMsgType);
		this->groupBox1->Controls->Add(this->cbbBaudrates);
		this->groupBox1->Controls->Add(this->cbbHws);
		this->groupBox1->Controls->Add(this->label5);
		this->groupBox1->Controls->Add(this->label4);
		this->groupBox1->Controls->Add(this->label3);
		this->groupBox1->Controls->Add(this->label2);
		this->groupBox1->Controls->Add(this->label1);
		this->groupBox1->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->groupBox1->Location = System::Drawing::Point(8, 8);
		this->groupBox1->Name = L"groupBox1";
		this->groupBox1->Size = System::Drawing::Size(498, 124);
		this->groupBox1->TabIndex = 0;
		this->groupBox1->TabStop = false;
		this->groupBox1->Text = L"Connection";
		// 
		// txtDevNumber
		// 
		this->txtDevNumber->Enabled = false;
		this->txtDevNumber->Location = System::Drawing::Point(157, 90);
		this->txtDevNumber->MaxLength = 10;
		this->txtDevNumber->Name = L"txtDevNumber";
		this->txtDevNumber->Size = System::Drawing::Size(72, 20);
		this->txtDevNumber->TabIndex = 51;
		this->txtDevNumber->Text = L"0";
		this->txtDevNumber->Leave += gcnew System::EventHandler(this, &Form1::txtDevNumber_Leave);
		this->txtDevNumber->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::txtDevNumber_KeyPress);
		// 
		// btnDllInfo
		// 
		this->btnDllInfo->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnDllInfo->Enabled = false;
		this->btnDllInfo->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->btnDllInfo->Location = System::Drawing::Point(330, 89);
		this->btnDllInfo->Name = L"btnDllInfo";
		this->btnDllInfo->Size = System::Drawing::Size(89, 23);
		this->btnDllInfo->TabIndex = 11;
		this->btnDllInfo->Text = L"Get Dll Version";
		this->btnDllInfo->UseVisualStyleBackColor = true;
		this->btnDllInfo->Click += gcnew System::EventHandler(this, &Form1::btnDllInfo_Click);
		// 
		// btnGetDevNumber
		// 
		this->btnGetDevNumber->Location = System::Drawing::Point(8, 60);
		this->btnGetDevNumber->Name = L"btnGetDevNumber";
		this->btnGetDevNumber->Size = System::Drawing::Size(140, 23);
		this->btnGetDevNumber->TabIndex = 9;
		this->btnGetDevNumber->Text = L"Get USB Device Number";
		this->btnGetDevNumber->UseVisualStyleBackColor = true;
		this->btnGetDevNumber->Click += gcnew System::EventHandler(this, &Form1::btnGetDevNumber_Click);
		// 
		// btnSetDevNumber
		// 
		this->btnSetDevNumber->Location = System::Drawing::Point(8, 89);
		this->btnSetDevNumber->Name = L"btnSetDevNumber";
		this->btnSetDevNumber->Size = System::Drawing::Size(140, 23);
		this->btnSetDevNumber->TabIndex = 8;
		this->btnSetDevNumber->Text = L"Set USB Device Number";
		this->btnSetDevNumber->UseVisualStyleBackColor = true;
		this->btnSetDevNumber->Click += gcnew System::EventHandler(this, &Form1::btnSetDevNumber_Click);
		// 
		// btnRelease
		// 
		this->btnRelease->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnRelease->Enabled = false;
		this->btnRelease->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->btnRelease->Location = System::Drawing::Point(425, 89);
		this->btnRelease->Name = L"btnRelease";
		this->btnRelease->Size = System::Drawing::Size(65, 23);
		this->btnRelease->TabIndex = 3;
		this->btnRelease->Text = L"Release";
		this->btnRelease->UseVisualStyleBackColor = true;
		this->btnRelease->Click += gcnew System::EventHandler(this, &Form1::btnRelease_Click);
		// 
		// btnInit
		// 
		this->btnInit->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnInit->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->btnInit->Location = System::Drawing::Point(425, 60);
		this->btnInit->Name = L"btnInit";
		this->btnInit->Size = System::Drawing::Size(65, 23);
		this->btnInit->TabIndex = 2;
		this->btnInit->Text = L"Initialize";
		this->btnInit->UseVisualStyleBackColor = true;
		this->btnInit->Click += gcnew System::EventHandler(this, &Form1::btnInit_Click);
		// 
		// btnInfo
		// 
		this->btnInfo->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnInfo->Enabled = false;
		this->btnInfo->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->btnInfo->Location = System::Drawing::Point(236, 89);
		this->btnInfo->Name = L"btnInfo";
		this->btnInfo->Size = System::Drawing::Size(88, 23);
		this->btnInfo->TabIndex = 1;
		this->btnInfo->Text = L"Get Info";
		this->btnInfo->UseVisualStyleBackColor = true;
		this->btnInfo->Click += gcnew System::EventHandler(this, &Form1::btnInfo_Click);
		// 
		// cbbInterrupt
		// 
		this->cbbInterrupt->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cbbInterrupt->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->cbbInterrupt->Items->AddRange(gcnew cli::array< System::Object^  >(9) {L"3", L"4", L"5", L"7", L"9", L"10", L"11", 
			L"12", L"15"});
		this->cbbInterrupt->Location = System::Drawing::Point(402, 32);
		this->cbbInterrupt->Name = L"cbbInterrupt";
		this->cbbInterrupt->Size = System::Drawing::Size(88, 21);
		this->cbbInterrupt->TabIndex = 7;
		// 
		// cbbIO
		// 
		this->cbbIO->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cbbIO->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->cbbIO->Items->AddRange(gcnew cli::array< System::Object^  >(24) {L"0100", L"0120", L"0140", L"0200", L"0220", L"0240", 
			L"0260", L"0278", L"0280", L"02A0", L"02C0", L"02E0", L"02E8", L"02F8", L"0300", L"0320", L"0340", L"0360", L"0378", L"0380", 
			L"03BC", L"03E0", L"03E8", L"03F8"});
		this->cbbIO->Location = System::Drawing::Point(322, 32);
		this->cbbIO->Name = L"cbbIO";
		this->cbbIO->Size = System::Drawing::Size(74, 21);
		this->cbbIO->TabIndex = 6;
		// 
		// cbbMsgType
		// 
		this->cbbMsgType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cbbMsgType->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->cbbMsgType->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Standard", L"Extended"});
		this->cbbMsgType->Location = System::Drawing::Point(228, 32);
		this->cbbMsgType->Name = L"cbbMsgType";
		this->cbbMsgType->Size = System::Drawing::Size(88, 21);
		this->cbbMsgType->TabIndex = 5;
		// 
		// cbbBaudrates
		// 
		this->cbbBaudrates->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cbbBaudrates->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->cbbBaudrates->Items->AddRange(gcnew cli::array< System::Object^  >(9) {L"1 MBit/sec", L"500 KBit/sec", L"250 KBit/sec", 
			L"125 KBit/sec", L"100 KBit/sec", L"50 KBit/sec", L"20 KBit/sec", L"10 KBit/sec", L"5 KBit/sec"});
		this->cbbBaudrates->Location = System::Drawing::Point(126, 32);
		this->cbbBaudrates->Name = L"cbbBaudrates";
		this->cbbBaudrates->Size = System::Drawing::Size(96, 21);
		this->cbbBaudrates->TabIndex = 4;
		this->cbbBaudrates->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cbbBaudrates_SelectedIndexChanged);
		// 
		// cbbHws
		// 
		this->cbbHws->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cbbHws->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->cbbHws->Items->AddRange(gcnew cli::array< System::Object^  >(10) {L"ISA", L"ISA 2-CH", L"PCI", L"PCI 2-CH", L"PCC", 
			L"PCC 2-CH", L"USB 1-CH", L"USB 2-CH", L"DONGLE PRO", L"DONGLE"});
		this->cbbHws->Location = System::Drawing::Point(8, 32);
		this->cbbHws->Name = L"cbbHws";
		this->cbbHws->Size = System::Drawing::Size(112, 21);
		this->cbbHws->TabIndex = 0;
		this->cbbHws->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cbbHws_SelectedIndexChanged);
		// 
		// label5
		// 
		this->label5->AutoSize = true;
		this->label5->Location = System::Drawing::Point(402, 16);
		this->label5->Name = L"label5";
		this->label5->Size = System::Drawing::Size(49, 13);
		this->label5->TabIndex = 4;
		this->label5->Text = L"Interrupt:";
		// 
		// label4
		// 
		this->label4->AutoSize = true;
		this->label4->Location = System::Drawing::Point(322, 16);
		this->label4->Name = L"label4";
		this->label4->Size = System::Drawing::Size(67, 13);
		this->label4->TabIndex = 3;
		this->label4->Text = L"I/O Address:";
		// 
		// label3
		// 
		this->label3->AutoSize = true;
		this->label3->Location = System::Drawing::Point(228, 16);
		this->label3->Name = L"label3";
		this->label3->Size = System::Drawing::Size(57, 13);
		this->label3->TabIndex = 2;
		this->label3->Text = L"Msg Type:";
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->Location = System::Drawing::Point(126, 16);
		this->label2->Name = L"label2";
		this->label2->Size = System::Drawing::Size(53, 13);
		this->label2->TabIndex = 1;
		this->label2->Text = L"Baudrate:";
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Location = System::Drawing::Point(7, 16);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(56, 13);
		this->label1->TabIndex = 0;
		this->label1->Text = L"Hardware:";
		// 
		// groupBox2
		// 
		this->groupBox2->Controls->Add(this->btnWrite);
		this->groupBox2->Controls->Add(this->chbRemote);
		this->groupBox2->Controls->Add(this->chbExtended);
		this->groupBox2->Controls->Add(this->txtData7);
		this->groupBox2->Controls->Add(this->txtData6);
		this->groupBox2->Controls->Add(this->txtData5);
		this->groupBox2->Controls->Add(this->txtData4);
		this->groupBox2->Controls->Add(this->txtData3);
		this->groupBox2->Controls->Add(this->txtData2);
		this->groupBox2->Controls->Add(this->txtData1);
		this->groupBox2->Controls->Add(this->txtData0);
		this->groupBox2->Controls->Add(this->nudLength);
		this->groupBox2->Controls->Add(this->txtID);
		this->groupBox2->Controls->Add(this->label8);
		this->groupBox2->Controls->Add(this->label7);
		this->groupBox2->Controls->Add(this->label6);
		this->groupBox2->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->groupBox2->Location = System::Drawing::Point(8, 138);
		this->groupBox2->Name = L"groupBox2";
		this->groupBox2->Size = System::Drawing::Size(498, 91);
		this->groupBox2->TabIndex = 1;
		this->groupBox2->TabStop = false;
		this->groupBox2->Text = L"Write Messages";
		// 
		// btnWrite
		// 
		this->btnWrite->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnWrite->Enabled = false;
		this->btnWrite->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->btnWrite->Location = System::Drawing::Point(398, 38);
		this->btnWrite->Name = L"btnWrite";
		this->btnWrite->Size = System::Drawing::Size(92, 23);
		this->btnWrite->TabIndex = 16;
		this->btnWrite->Text = L"Write Message";
		this->btnWrite->UseVisualStyleBackColor = true;
		this->btnWrite->Click += gcnew System::EventHandler(this, &Form1::btnWrite_Click);
		// 
		// chbRemote
		// 
		this->chbRemote->Cursor = System::Windows::Forms::Cursors::Hand;
		this->chbRemote->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->chbRemote->Location = System::Drawing::Point(112, 64);
		this->chbRemote->Name = L"chbRemote";
		this->chbRemote->Size = System::Drawing::Size(112, 24);
		this->chbRemote->TabIndex = 15;
		this->chbRemote->Text = L"Remote Request";
		this->chbRemote->UseVisualStyleBackColor = true;
		this->chbRemote->CheckedChanged += gcnew System::EventHandler(this, &Form1::chbRemote_CheckedChanged);
		// 
		// chbExtended
		// 
		this->chbExtended->Cursor = System::Windows::Forms::Cursors::Hand;
		this->chbExtended->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->chbExtended->Location = System::Drawing::Point(8, 64);
		this->chbExtended->Name = L"chbExtended";
		this->chbExtended->Size = System::Drawing::Size(112, 24);
		this->chbExtended->TabIndex = 14;
		this->chbExtended->Text = L"Extended Frame";
		this->chbExtended->UseVisualStyleBackColor = true;
		this->chbExtended->CheckedChanged += gcnew System::EventHandler(this, &Form1::chbExtended_CheckedChanged);
		// 
		// txtData7
		// 
		this->txtData7->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
		this->txtData7->Location = System::Drawing::Point(368, 40);
		this->txtData7->MaxLength = 2;
		this->txtData7->Name = L"txtData7";
		this->txtData7->Size = System::Drawing::Size(24, 20);
		this->txtData7->TabIndex = 13;
		this->txtData7->Text = L"00";
		this->txtData7->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		this->txtData7->Leave += gcnew System::EventHandler(this, &Form1::txtData0_Leave);
		this->txtData7->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::txtID_KeyPress);
		// 
		// txtData6
		// 
		this->txtData6->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
		this->txtData6->Location = System::Drawing::Point(336, 40);
		this->txtData6->MaxLength = 2;
		this->txtData6->Name = L"txtData6";
		this->txtData6->Size = System::Drawing::Size(24, 20);
		this->txtData6->TabIndex = 12;
		this->txtData6->Text = L"00";
		this->txtData6->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		this->txtData6->Leave += gcnew System::EventHandler(this, &Form1::txtData0_Leave);
		this->txtData6->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::txtID_KeyPress);
		// 
		// txtData5
		// 
		this->txtData5->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
		this->txtData5->Location = System::Drawing::Point(304, 40);
		this->txtData5->MaxLength = 2;
		this->txtData5->Name = L"txtData5";
		this->txtData5->Size = System::Drawing::Size(24, 20);
		this->txtData5->TabIndex = 11;
		this->txtData5->Text = L"00";
		this->txtData5->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		this->txtData5->Leave += gcnew System::EventHandler(this, &Form1::txtData0_Leave);
		this->txtData5->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::txtID_KeyPress);
		// 
		// txtData4
		// 
		this->txtData4->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
		this->txtData4->Location = System::Drawing::Point(272, 40);
		this->txtData4->MaxLength = 2;
		this->txtData4->Name = L"txtData4";
		this->txtData4->Size = System::Drawing::Size(24, 20);
		this->txtData4->TabIndex = 10;
		this->txtData4->Text = L"00";
		this->txtData4->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		this->txtData4->Leave += gcnew System::EventHandler(this, &Form1::txtData0_Leave);
		this->txtData4->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::txtID_KeyPress);
		// 
		// txtData3
		// 
		this->txtData3->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
		this->txtData3->Location = System::Drawing::Point(240, 40);
		this->txtData3->MaxLength = 2;
		this->txtData3->Name = L"txtData3";
		this->txtData3->Size = System::Drawing::Size(24, 20);
		this->txtData3->TabIndex = 9;
		this->txtData3->Text = L"00";
		this->txtData3->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		this->txtData3->Leave += gcnew System::EventHandler(this, &Form1::txtData0_Leave);
		this->txtData3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::txtID_KeyPress);
		// 
		// txtData2
		// 
		this->txtData2->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
		this->txtData2->Location = System::Drawing::Point(208, 40);
		this->txtData2->MaxLength = 2;
		this->txtData2->Name = L"txtData2";
		this->txtData2->Size = System::Drawing::Size(24, 20);
		this->txtData2->TabIndex = 8;
		this->txtData2->Text = L"00";
		this->txtData2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		this->txtData2->Leave += gcnew System::EventHandler(this, &Form1::txtData0_Leave);
		this->txtData2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::txtID_KeyPress);
		// 
		// txtData1
		// 
		this->txtData1->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
		this->txtData1->Location = System::Drawing::Point(176, 40);
		this->txtData1->MaxLength = 2;
		this->txtData1->Name = L"txtData1";
		this->txtData1->Size = System::Drawing::Size(24, 20);
		this->txtData1->TabIndex = 7;
		this->txtData1->Text = L"00";
		this->txtData1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		this->txtData1->Leave += gcnew System::EventHandler(this, &Form1::txtData0_Leave);
		this->txtData1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::txtID_KeyPress);
		// 
		// txtData0
		// 
		this->txtData0->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
		this->txtData0->Location = System::Drawing::Point(144, 40);
		this->txtData0->MaxLength = 2;
		this->txtData0->Name = L"txtData0";
		this->txtData0->Size = System::Drawing::Size(24, 20);
		this->txtData0->TabIndex = 6;
		this->txtData0->Text = L"00";
		this->txtData0->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		this->txtData0->Leave += gcnew System::EventHandler(this, &Form1::txtData0_Leave);
		this->txtData0->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::txtID_KeyPress);
		// 
		// nudLength
		// 
		this->nudLength->BackColor = System::Drawing::Color::White;
		this->nudLength->Location = System::Drawing::Point(96, 40);
		this->nudLength->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {8, 0, 0, 0});
		this->nudLength->Name = L"nudLength";
		this->nudLength->ReadOnly = true;
		this->nudLength->Size = System::Drawing::Size(40, 20);
		this->nudLength->TabIndex = 5;
		this->nudLength->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {8, 0, 0, 0});
		this->nudLength->ValueChanged += gcnew System::EventHandler(this, &Form1::nudLength_ValueChanged);
		// 
		// txtID
		// 
		this->txtID->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
		this->txtID->Location = System::Drawing::Point(8, 40);
		this->txtID->MaxLength = 3;
		this->txtID->Name = L"txtID";
		this->txtID->Size = System::Drawing::Size(80, 20);
		this->txtID->TabIndex = 4;
		this->txtID->Text = L"0";
		this->txtID->Leave += gcnew System::EventHandler(this, &Form1::txtID_Leave);
		this->txtID->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::txtID_KeyPress);
		// 
		// label8
		// 
		this->label8->AutoSize = true;
		this->label8->Location = System::Drawing::Point(144, 16);
		this->label8->Name = L"label8";
		this->label8->Size = System::Drawing::Size(60, 13);
		this->label8->TabIndex = 3;
		this->label8->Text = L"Data (0..7):";
		// 
		// label7
		// 
		this->label7->AutoSize = true;
		this->label7->Location = System::Drawing::Point(96, 16);
		this->label7->Name = L"label7";
		this->label7->Size = System::Drawing::Size(43, 13);
		this->label7->TabIndex = 2;
		this->label7->Text = L"Length:";
		// 
		// label6
		// 
		this->label6->AutoSize = true;
		this->label6->Location = System::Drawing::Point(8, 16);
		this->label6->Name = L"label6";
		this->label6->Size = System::Drawing::Size(49, 13);
		this->label6->TabIndex = 1;
		this->label6->Text = L"ID (Hex):";
		// 
		// groupBox3
		// 
		this->groupBox3->Controls->Add(this->labelReadMethod);
		this->groupBox3->Controls->Add(this->rdbEvent);
		this->groupBox3->Controls->Add(this->rdbTimer);
		this->groupBox3->Controls->Add(this->chbTimeStamp);
		this->groupBox3->Controls->Add(this->lstMessages);
		this->groupBox3->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->groupBox3->Location = System::Drawing::Point(8, 306);
		this->groupBox3->Name = L"groupBox3";
		this->groupBox3->Size = System::Drawing::Size(498, 163);
		this->groupBox3->TabIndex = 2;
		this->groupBox3->TabStop = false;
		this->groupBox3->Text = L"Read Messages";
		// 
		// labelReadMethod
		// 
		this->labelReadMethod->AutoSize = true;
		this->labelReadMethod->Location = System::Drawing::Point(6, 16);
		this->labelReadMethod->Name = L"labelReadMethod";
		this->labelReadMethod->Size = System::Drawing::Size(75, 13);
		this->labelReadMethod->TabIndex = 3;
		this->labelReadMethod->Text = L"Read Method:";
		// 
		// rdbEvent
		// 
		this->rdbEvent->AutoSize = true;
		this->rdbEvent->Enabled = false;
		this->rdbEvent->Location = System::Drawing::Point(159, 14);
		this->rdbEvent->Name = L"rdbEvent";
		this->rdbEvent->Size = System::Drawing::Size(68, 17);
		this->rdbEvent->TabIndex = 2;
		this->rdbEvent->Text = L"By Event";
		this->rdbEvent->UseVisualStyleBackColor = true;
		// 
		// rdbTimer
		// 
		this->rdbTimer->AutoSize = true;
		this->rdbTimer->Checked = true;
		this->rdbTimer->Enabled = false;
		this->rdbTimer->Location = System::Drawing::Point(89, 14);
		this->rdbTimer->Name = L"rdbTimer";
		this->rdbTimer->Size = System::Drawing::Size(66, 17);
		this->rdbTimer->TabIndex = 2;
		this->rdbTimer->TabStop = true;
		this->rdbTimer->Text = L"By Timer";
		this->rdbTimer->UseVisualStyleBackColor = true;
		this->rdbTimer->CheckedChanged += gcnew System::EventHandler(this, &Form1::rdbTimer_CheckedChanged);
		// 
		// chbTimeStamp
		// 
		this->chbTimeStamp->AutoSize = true;
		this->chbTimeStamp->Checked = true;
		this->chbTimeStamp->CheckState = System::Windows::Forms::CheckState::Checked;
		this->chbTimeStamp->Enabled = false;
		this->chbTimeStamp->Location = System::Drawing::Point(8, 140);
		this->chbTimeStamp->Name = L"chbTimeStamp";
		this->chbTimeStamp->Size = System::Drawing::Size(112, 17);
		this->chbTimeStamp->TabIndex = 1;
		this->chbTimeStamp->Text = L"Show Time Stamp";
		this->chbTimeStamp->UseVisualStyleBackColor = true;
		this->chbTimeStamp->CheckedChanged += gcnew System::EventHandler(this, &Form1::chbTimeStamp_CheckedChanged);
		// 
		// lstMessages
		// 
		this->lstMessages->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {this->clhType, this->clhID, 
			this->clhLength, this->clhData, this->clhCount, this->clhRcvTime});
		this->lstMessages->FullRowSelect = true;
		this->lstMessages->Location = System::Drawing::Point(8, 37);
		this->lstMessages->MultiSelect = false;
		this->lstMessages->Name = L"lstMessages";
		this->lstMessages->Size = System::Drawing::Size(482, 97);
		this->lstMessages->TabIndex = 0;
		this->lstMessages->UseCompatibleStateImageBehavior = false;
		this->lstMessages->View = System::Windows::Forms::View::Details;
		this->lstMessages->DoubleClick += gcnew System::EventHandler(this, &Form1::lstMessages_DoubleClick);
		// 
		// clhType
		// 
		this->clhType->Text = L"Type";
		this->clhType->Width = 69;
		// 
		// clhID
		// 
		this->clhID->Text = L"ID";
		this->clhID->Width = 73;
		// 
		// clhLength
		// 
		this->clhLength->Text = L"Length";
		this->clhLength->Width = 50;
		// 
		// clhData
		// 
		this->clhData->Text = L"Data";
		this->clhData->Width = 138;
		// 
		// clhCount
		// 
		this->clhCount->Text = L"Count";
		this->clhCount->Width = 49;
		// 
		// clhRcvTime
		// 
		this->clhRcvTime->Text = L"Rcv Time";
		this->clhRcvTime->Width = 98;
		// 
		// groupBox4
		// 
		this->groupBox4->Controls->Add(this->txtInfo);
		this->groupBox4->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->groupBox4->Location = System::Drawing::Point(8, 475);
		this->groupBox4->Name = L"groupBox4";
		this->groupBox4->Size = System::Drawing::Size(498, 72);
		this->groupBox4->TabIndex = 3;
		this->groupBox4->TabStop = false;
		this->groupBox4->Text = L"Information";
		// 
		// txtInfo
		// 
		this->txtInfo->BackColor = System::Drawing::Color::White;
		this->txtInfo->Cursor = System::Windows::Forms::Cursors::Arrow;
		this->txtInfo->Location = System::Drawing::Point(8, 16);
		this->txtInfo->Multiline = true;
		this->txtInfo->Name = L"txtInfo";
		this->txtInfo->ReadOnly = true;
		this->txtInfo->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		this->txtInfo->Size = System::Drawing::Size(484, 48);
		this->txtInfo->TabIndex = 0;
		this->txtInfo->TabStop = false;
		this->txtInfo->Text = L"Select a Hardware and a configuration for it. Then click \"Initialize\" button";
		this->txtInfo->DoubleClick += gcnew System::EventHandler(this, &Form1::txtInfo_DoubleClick);
		// 
		// btnClose
		// 
		this->btnClose->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnClose->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->btnClose->Location = System::Drawing::Point(450, 553);
		this->btnClose->Name = L"btnClose";
		this->btnClose->Size = System::Drawing::Size(56, 23);
		this->btnClose->TabIndex = 4;
		this->btnClose->Text = L"Close";
		this->btnClose->UseVisualStyleBackColor = true;
		this->btnClose->Click += gcnew System::EventHandler(this, &Form1::btnClose_Click);
		// 
		// tmrRead
		// 
		this->tmrRead->Interval = 50;
		this->tmrRead->Tick += gcnew System::EventHandler(this, &Form1::tmrRead_Tick);
		// 
		// groupBox5
		// 
		this->groupBox5->Controls->Add(this->rdbStandard);
		this->groupBox5->Controls->Add(this->rdbExtended);
		this->groupBox5->Controls->Add(this->txtIdTo);
		this->groupBox5->Controls->Add(this->txtIdFrom);
		this->groupBox5->Controls->Add(this->btnResetFilter);
		this->groupBox5->Controls->Add(this->btnSetFilter);
		this->groupBox5->Controls->Add(this->label10);
		this->groupBox5->Controls->Add(this->label9);
		this->groupBox5->Location = System::Drawing::Point(8, 235);
		this->groupBox5->Name = L"groupBox5";
		this->groupBox5->Size = System::Drawing::Size(498, 65);
		this->groupBox5->TabIndex = 47;
		this->groupBox5->TabStop = false;
		this->groupBox5->Text = L"Message Filter";
		// 
		// rdbStandard
		// 
		this->rdbStandard->AutoSize = true;
		this->rdbStandard->Checked = true;
		this->rdbStandard->Location = System::Drawing::Point(11, 36);
		this->rdbStandard->Name = L"rdbStandard";
		this->rdbStandard->Size = System::Drawing::Size(68, 17);
		this->rdbStandard->TabIndex = 71;
		this->rdbStandard->TabStop = true;
		this->rdbStandard->Text = L"Standard";
		this->rdbStandard->UseVisualStyleBackColor = true;
		this->rdbStandard->CheckedChanged += gcnew System::EventHandler(this, &Form1::rdbStandard_CheckedChanged);
		// 
		// rdbExtended
		// 
		this->rdbExtended->AutoSize = true;
		this->rdbExtended->Location = System::Drawing::Point(85, 36);
		this->rdbExtended->Name = L"rdbExtended";
		this->rdbExtended->Size = System::Drawing::Size(70, 17);
		this->rdbExtended->TabIndex = 70;
		this->rdbExtended->Text = L"Extended";
		this->rdbExtended->UseVisualStyleBackColor = true;
		// 
		// txtIdTo
		// 
		this->txtIdTo->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
		this->txtIdTo->Location = System::Drawing::Point(264, 35);
		this->txtIdTo->MaxLength = 3;
		this->txtIdTo->Name = L"txtIdTo";
		this->txtIdTo->Size = System::Drawing::Size(90, 20);
		this->txtIdTo->TabIndex = 67;
		this->txtIdTo->Text = L"0";
		this->txtIdTo->Leave += gcnew System::EventHandler(this, &Form1::txtIdFrom_Leave);
		this->txtIdTo->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::txtID_KeyPress);
		// 
		// txtIdFrom
		// 
		this->txtIdFrom->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
		this->txtIdFrom->Location = System::Drawing::Point(168, 35);
		this->txtIdFrom->MaxLength = 3;
		this->txtIdFrom->Name = L"txtIdFrom";
		this->txtIdFrom->Size = System::Drawing::Size(90, 20);
		this->txtIdFrom->TabIndex = 66;
		this->txtIdFrom->Text = L"0";
		this->txtIdFrom->Leave += gcnew System::EventHandler(this, &Form1::txtIdFrom_Leave);
		this->txtIdFrom->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::txtID_KeyPress);
		// 
		// btnResetFilter
		// 
		this->btnResetFilter->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnResetFilter->Enabled = false;
		this->btnResetFilter->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->btnResetFilter->Location = System::Drawing::Point(434, 33);
		this->btnResetFilter->Name = L"btnResetFilter";
		this->btnResetFilter->Size = System::Drawing::Size(56, 23);
		this->btnResetFilter->TabIndex = 64;
		this->btnResetFilter->Text = L"Reset";
		this->btnResetFilter->Click += gcnew System::EventHandler(this, &Form1::btnResetFilter_Click);
		// 
		// btnSetFilter
		// 
		this->btnSetFilter->Cursor = System::Windows::Forms::Cursors::Hand;
		this->btnSetFilter->Enabled = false;
		this->btnSetFilter->FlatStyle = System::Windows::Forms::FlatStyle::System;
		this->btnSetFilter->Location = System::Drawing::Point(372, 33);
		this->btnSetFilter->Name = L"btnSetFilter";
		this->btnSetFilter->Size = System::Drawing::Size(56, 23);
		this->btnSetFilter->TabIndex = 63;
		this->btnSetFilter->Text = L"Set";
		this->btnSetFilter->Click += gcnew System::EventHandler(this, &Form1::btnSetFilter_Click);
		// 
		// label10
		// 
		this->label10->Location = System::Drawing::Point(264, 16);
		this->label10->Name = L"label10";
		this->label10->Size = System::Drawing::Size(56, 23);
		this->label10->TabIndex = 62;
		this->label10->Text = L"To:";
		// 
		// label9
		// 
		this->label9->Location = System::Drawing::Point(165, 16);
		this->label9->Name = L"label9";
		this->label9->Size = System::Drawing::Size(56, 23);
		this->label9->TabIndex = 61;
		this->label9->Text = L"From:";
		// 
		// Form1
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(514, 584);
		this->Controls->Add(this->groupBox5);
		this->Controls->Add(this->btnClose);
		this->Controls->Add(this->groupBox4);
		this->Controls->Add(this->groupBox3);
		this->Controls->Add(this->groupBox2);
		this->Controls->Add(this->groupBox1);
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
		this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
		this->MaximizeBox = false;
		this->Name = L"Form1";
		this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
		this->Text = L"I CAN Do It! - Light";
		this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
		this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
		this->groupBox1->ResumeLayout(false);
		this->groupBox1->PerformLayout();
		this->groupBox2->ResumeLayout(false);
		this->groupBox2->PerformLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->nudLength))->EndInit();
		this->groupBox3->ResumeLayout(false);
		this->groupBox3->PerformLayout();
		this->groupBox4->ResumeLayout(false);
		this->groupBox4->PerformLayout();
		this->groupBox5->ResumeLayout(false);
		this->groupBox5->PerformLayout();
		this->ResumeLayout(false);

	}
	#pragma endregion

	#pragma region Miscellaneous Functions
	private: void ModifyMsgEntry(MessageStatus^ LastMsg, TCLightMsg^ NewMsg, TCLightTimestamp^ MyTimeStamp)
	{
		String^ strLastData, ^strNewData;
		MessageStatus^ NewStatus;
		ListViewItem^ CurrItem;
		unsigned int iLen;
		int iCount;

		strNewData = strLastData = "";

		// Values from the last messages
		//
		CurrItem = lstMessages->Items[LastMsg->Position];
		iCount = Convert::ToInt32(CurrItem->SubItems[4]->Text);
		strLastData = CurrItem->SubItems[3]->Text;
		iLen = LastMsg->CANMessage->Len;

		// New values 
		//
		if((NewMsg->MsgType & MSGTYPE_RTR) != 0)
			strNewData = "Remote Request";
		else
			for(int i=0; i< NewMsg->Len; i++)
				strNewData += String::Format("{0:X2} ",NewMsg->Data[i]);
		
		// Count and Time are updated
		//
		iCount += 1;

		// Set the changes
		//
		if(iLen != NewMsg->Len)
		{
			iLen = NewMsg->Len;		
			CurrItem->SubItems[2]->Text = iLen.ToString();
		}

		if(strLastData != strNewData)
			CurrItem->SubItems[3]->Text = strNewData;

		CurrItem->SubItems[4]->Text = iCount.ToString();

		// Update time stamp information if need be
		//
		if(MyTimeStamp != nullptr)
		{
			String^ timeStamp = MyTimeStamp->millis.ToString() + "." + MyTimeStamp->micros.ToString();
			
			// Add new SubItem if it doesn't exists
			//
			if(CurrItem->SubItems->Count == 5)
				CurrItem->SubItems->Add(timeStamp);
			// Else update existing SubItem
			//
			else
				CurrItem->SubItems[5]->Text = timeStamp;
		}

		// Save the new Status of the message
		// NOTE: The objects are saved in the same index position which 
		// they use in the Listview
		//
		NewStatus = gcnew MessageStatus(NewMsg,LastMsg->Position);
		LastMsgsList->RemoveAt(LastMsg->Position);
		LastMsgsList->Insert(LastMsg->Position,NewStatus);
	}

	private: void InsertMsgEntry(TCLightMsg^ NewMsg, TCLightTimestamp^ MyTimeStamp)
	{
		String^ strNewData,^strTemp;
		ListViewItem^ CurrItem;
		MessageStatus^ CurrMsg;

		strTemp = strNewData = "";

		// Add the new ListView Item with the Type of the message
		//	
		if((NewMsg->MsgType & MSGTYPE_EXTENDED) != 0)
			strTemp = "EXTENDED";
		else
			strTemp = "STANDARD";

		if((NewMsg->MsgType & MSGTYPE_RTR) == MSGTYPE_RTR)
			strTemp += "/RTR";

		CurrItem = lstMessages->Items->Add(strTemp);
		
		
		// We format the ID of the message and show it
		//
		if((NewMsg->MsgType & MSGTYPE_EXTENDED) != 0)
			CurrItem->SubItems->Add(String::Format("{0:X8}h",NewMsg->ID));
		else
			CurrItem->SubItems->Add(String::Format("{0:X3}h",NewMsg->ID));
			
		// We set the length of the Message
		//
		CurrItem->SubItems->Add(NewMsg->Len.ToString());

		// We format the data of the message. Each data is one 
		// byte of Hexadecimal data			
		//
		if((NewMsg->MsgType & MSGTYPE_RTR) == MSGTYPE_RTR)
			strNewData = "Remote Request";
		else
			for(int i=0; i< NewMsg->Len; i++)
				strNewData += String::Format("{0:X2} ",NewMsg->Data[i]);
		
		CurrItem->SubItems->Add(strNewData);

		// The message is the First, so count is 1 and there 
		// is not any time difference between messages.
		//
		CurrItem->SubItems->Add("1");

		// Add time stamp information if need be
		//
		if(MyTimeStamp != nullptr)
			CurrItem->SubItems->Add(MyTimeStamp->millis.ToString() + "." + MyTimeStamp->micros.ToString());
			
		// We add this status in the last message list
		//
		CurrMsg = gcnew MessageStatus(NewMsg,CurrItem->Index);
		LastMsgsList->Add(CurrMsg); 
	}

	private: System::Void ProcessMessage(TCLightMsg^ MyMsg, TCLightTimestamp^ MyTimeStamp)
	{
		bool bFound = false;
		MessageStatus^ CurrMessage;

		// Initialization
		//
		CurrMessage = gcnew MessageStatus();

		// We search if a message (Smae ID and Type) is 
		// already received or if this is a new message
		//
		for(int i=0; i< LastMsgsList->Count; i++)
		{
			CurrMessage = safe_cast<MessageStatus^>(LastMsgsList[i]);
			if(CurrMessage->CANMessage->ID == MyMsg->ID)
				if(CurrMessage->CANMessage->MsgType == MyMsg->MsgType)
				{
					bFound = true;
					break;
				}
		}
		if(bFound)
			// Messages of this kind are already received; we make an update
			//
			ModifyMsgEntry(CurrMessage,MyMsg, MyTimeStamp);
		else
			// Messages of this kind are not received; we make a new entry
			//
			InsertMsgEntry(MyMsg, MyTimeStamp);
	}
	private: System::Void CANReadThreadFunc() 
	{
		// Sets the handle of the Receive-Event.
		//
		PCANLight::SetRcvEvent(ActiveHardware, RcvEvent);

		// While this mode is selected
		while(rdbEvent->Checked)
		{
			// Waiting for Receive-Event
			// 
			RcvEvent->WaitOne();

			// Process Receive-Event using .NET Invoke function
			// in order to interact with Winforms UI
			// 
			this->Invoke(ReadDelegate);
		}
	}

	private: System::Void ReadMessage() 
	{
		TCLightMsg^ MyMsg;
		TCLightTimestamp^ MyTimeStamp;
		CANResult Res;
	
		// We read at least one time the queue looking for messages.
		// If a message is found, we look again trying to find more.
		// If the queue is empty or an error occurr, we get out from
		// the dowhile statement.
		//			
		do
		{
			// We read the queue looking for messages.
			//
			if(chbTimeStamp->Checked)
				// We execute the "ReadEx" function of the PCANLight
				// if "Show Time Stamp" checkbox is selected
				//
				Res = PCANLight::ReadEx(ActiveHardware,MyMsg,MyTimeStamp);
			else
				// We execute the "Read" function of the PCANLight
				// if "Show Time Stamp" checkbox isn't selected
				//
				Res = PCANLight::Read(ActiveHardware,MyMsg);

			// A message was received
			// We process the message(s)
			//
			if(Res == ERR_OK)
				ProcessMessage(MyMsg, MyTimeStamp);

		}while((ActiveHardware != -1) && !(Res & ERR_QRCVEMPTY));
	}

	// This helper function retrieve active Dll Major version number
	//
	private: CANResult DllMajorVersion(HardwareType hType, interior_ptr<int> majorVersion)
	{
		CANResult Res;
		String^ dllVersionStr = "";

		// We execute the "DllVersionInfo" function of the PCANLight
		// using as parameter the Hardware type and a string
		// variable to get the info like "x.xx"
		//
		Res = PCANLight::DllVersionInfo(hType, dllVersionStr);

		// We retrieve major version number 
		// spliting versionNumberStr based on "." decimal symbol
		//
		array<String^ >^ versionTabInfo = dllVersionStr->Split('.');
		if(versionTabInfo->Length > 0)
			Int32::TryParse(safe_cast<String^>(versionTabInfo->GetValue(0)), *majorVersion);
		return Res;
	}
	#pragma endregion

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
		{
			// Set the standard values in the interface
			//
			cbbHws->SelectedIndex = 0;
			cbbBaudrates->SelectedIndex = 0;
			cbbIO->Text = "0378";
			cbbInterrupt->Text = "7";
			cbbMsgType->SelectedIndex = 0;	
		}
	private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) 
		{
			if(btnRelease->Enabled)
				btnRelease_Click(this,gcnew EventArgs());

			// If we are reading, we stop to read
			//
			tmrRead->Enabled = false;
		}
	private: System::Void cbbHws_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
		{
			bool bShowIO;
			int current;

			current = cbbHws->SelectedIndex;

			// According with the selection in the Hardware list, 
			// we show/hide the input controls for I/O Address and 
			// Interrupt. (This parameters are NOT necessary for all 
			// hardware types) .
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

			cbbIO->Enabled = bShowIO;
			cbbInterrupt->Enabled = bShowIO;

			// According with the selection in the Hardware list, we 
			// Enable/Disable the controls for Get/Set the USB device Number.
			//
			btnGetDevNumber->Enabled = ((current == USB_1CH) || (current == USB_2CH)) && btnWrite->Enabled;
			btnSetDevNumber->Enabled = (btnGetDevNumber->Enabled);
			txtDevNumber->Enabled = (btnGetDevNumber->Enabled);
		}
	private: System::Void cbbBaudrates_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
		{
			// We save the corresponding Baudrate enumeration 
			// type value for every selected Baudrate from the 
			// list.
			//
			switch(cbbBaudrates->SelectedIndex)
			{
				case 0:
					cbbBaudrates->Tag = (int)BAUD_1M;
					break;
				case 1:
					cbbBaudrates->Tag = (int)BAUD_500K;
					break;
				case 2:
					cbbBaudrates->Tag = (int)BAUD_250K;
					break;				
				case 3:
					cbbBaudrates->Tag = (int)BAUD_125K;
					break;				
				case 4:
					cbbBaudrates->Tag = (int)BAUD_100K;
					break;				
				case 5:
					cbbBaudrates->Tag = (int)BAUD_50K;
					break;				
				case 6:
					cbbBaudrates->Tag = (int)BAUD_20K;					
					break;				
				case 7:					
					cbbBaudrates->Tag = (int)BAUD_10K;
					break;				
				case 8:
					cbbBaudrates->Tag = (int)BAUD_5K;
					break;		
				default:
					cbbBaudrates->Tag = safe_cast<System::Object^>(0);
					break;
			}
		}
	private: System::Void txtID_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) 
		{
			wchar_t chCheck;

			// We convert the Character to its Upper case equivalent
			//			
			chCheck = wchar_t::ToUpper(e->KeyChar);

			// The Key is the Delete (Backspace) Key
			//
			if(chCheck == 8)
				return;
			// The Key is a number between 0-9
			//
			if((chCheck > 47)&&(chCheck < 58))
				return;
			// The Key is a character between A-F
			//
			if((chCheck > 64)&&(chCheck < 71))
				return;

			// Is neither a number nor a character between A(a) and F(f)
			//
			e->Handled = true;
		}
	private: System::Void txtID_Leave(System::Object^  sender, System::EventArgs^  e) 
		{
			int TextLength;
			int MaxValue;

			// calculate the text length and Maximum ID value according
			// with the Message Type
			//
			TextLength = (chbExtended->Checked) ? 8 : 3;
			MaxValue = (chbExtended->Checked) ? 0x1FFFFFF : 0x7FF;

			// The Textbox for the ID is represented with 3 characters for 
			// Standard and 8 characters for extended messages.
			// Therefore if the Length of the text is smaller than TextLength,  
			// we add "0"
			//
			while(txtID->Text->Length != TextLength)
				txtID->Text = ("0" + txtID->Text);
			// Because in this example will be sent only Standard messages
			// we check that the ID is not bigger than 0x7FF
			//
			if(Convert::ToInt32(txtID->Text,16) > MaxValue)
				txtID->Text = String::Format("{0:X"+TextLength.ToString()+"}",MaxValue);
		}
	private: System::Void nudLength_ValueChanged(System::Object^  sender, System::EventArgs^  e) 
		{
			TextBox^ CurrentTextBox;

			CurrentTextBox = txtData0;

			// We enable so much TextBox Data fields as the length of the
			// message will be, that is the value of the UpDown control
			//
			for(int i=0; i< 8; i++)
			{
				CurrentTextBox->Enabled = (i < nudLength->Value)? true : false;
				if(i < 7)
					CurrentTextBox = (TextBox^)this->GetNextControl(CurrentTextBox,true);
			}
		}
	private: System::Void txtData0_Leave(System::Object^  sender, System::EventArgs^  e) 
		{
			TextBox^ CurrentTextbox;
			
			// all the Textbox Data fields are represented with 2 characters.
			// Therefore if the Length of the text is smaller than 2, we add
			// a "0"
			//
			if(sender->GetType()->Name == "TextBox")
			{				
				CurrentTextbox = (TextBox^)sender;
				while(CurrentTextbox->Text->Length != 2)
					CurrentTextbox->Text = ("0" + CurrentTextbox->Text);	
			}
		}
	private: System::Void chbExtended_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		{
			unsigned int uiTemp;

			txtID->MaxLength = (chbExtended->Checked)? 8: 3;
			
			// the only way that the text length can be bigger als MaxLength
			// is when the change is from Extended to Standard message Type.
			// We have to handle this and set an ID not bigger than the Maximum
			// ID value for a Standard Message (0x7FF)
			//
			if(txtID->Text->Length > txtID->MaxLength)
			{
				uiTemp = Convert::ToInt32(txtID->Text,16);
				txtID->Text = (uiTemp < 0x7FF) ?  String::Format("{0:X3}",uiTemp): "7FF";
			}

			txtID_Leave(this,gcnew EventArgs());
		}
	private: System::Void chbRemote_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		{
			TextBox^ CurrentTextBox;

			CurrentTextBox = txtData0;

			// We make visible so much TextBox Data fields as the length of the
			// message will be, that is the value of the UpDown control.
			// 
			for(int i=0; i< 8; i++)
			{
				CurrentTextBox->Visible = !chbRemote->Checked;
				if(i < 7)
					CurrentTextBox = (TextBox^)this->GetNextControl(CurrentTextBox,true);
			}
		}
	private: System::Void txtInfo_DoubleClick(System::Object^  sender, System::EventArgs^  e) 
		{
			// We clear the Information edit box
			//
			txtInfo->Text = "";	
		}
	private: System::Void lstMessages_DoubleClick(System::Object^  sender, System::EventArgs^  e) 
		{
			lstMessages->Items->Clear();
			LastMsgsList->Clear();
		}
	private: System::Void tmrRead_Tick(System::Object^  sender, System::EventArgs^  e) 
	{
			this->Invoke(ReadDelegate);
	}
	private: System::Void btnInfo_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			String^ strInfo;
			CANResult Res;

			// We execute the "VersionInfo" function of the PCANLight 
			// using as parameter the Hardware type and a string 
			// variable to get the info.
			// 
			Res = PCANLight::VersionInfo(safe_cast<HardwareType>(cbbHws->SelectedIndex),strInfo);
			strInfo = strInfo->Replace("\n","\r\n");

			// The function was successfully executed
			//			
			if(Res == ERR_OK)
				// We show the Version Information
				//
				txtInfo->Text = strInfo;
				// An error occurred.  We show the error.
				//			
			else
				txtInfo->Text  = "Error: " + String::Format("{0:X4}",(int)Res);	
		}
	private: System::Void btnInit_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			CANResult Res;
			int majorVersionNumber = 0;

			// Check version 2.x Dll is available
			//
			Res = DllMajorVersion(safe_cast<HardwareType>(cbbHws->SelectedIndex), &majorVersionNumber);
			if(Res == ERR_OK)
			{
				// Sample must ONLY work if a 2.x or later version of the
				// PCAN-Light is installed
				//
				if(majorVersionNumber < 2)
				{
					MessageBox::Show("DLL 2.x or later are required to run this program" +
						"\r\nPlease, download lastest DLL version on http://www.peak-system.com or refer to the documentation for more information.", 
						"DLL Version", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
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
						Res = PCANLight::Init(safe_cast<HardwareType>(cbbHws->SelectedIndex),
							safe_cast<Baudrates>((int)cbbBaudrates->Tag),
							safe_cast<FramesType>(cbbMsgType->SelectedIndex),
							Convert::ToInt32(cbbIO->Text,16),
							Convert::ToByte(cbbInterrupt->Text));
					else
						// P&P Hardware
						//
						Res = PCANLight::Init(safe_cast<HardwareType>(cbbHws->SelectedIndex),
							safe_cast<Baudrates>((int)cbbBaudrates->Tag),
							safe_cast<FramesType>(cbbMsgType->SelectedIndex));

					// The Hardware was successfully initiated
					//
					if(Res == ERR_OK)
					{
						ActiveHardware = safe_cast<HardwareType>(cbbHws->SelectedIndex);

						// We start to read from the CAN Queue
						//
						tmrRead->Enabled = true;
						
						// We set UI enable
						//
						btnInit->Enabled = false;
						btnWrite->Enabled = true; 
						btnRelease->Enabled = true;
						btnSetFilter->Enabled = true;
						btnResetFilter->Enabled = true;
						btnInfo->Enabled = true;
						btnDllInfo->Enabled = true;
						rdbTimer->Enabled = true;
						rdbEvent->Enabled = true;
						chbTimeStamp->Checked = true;
						chbTimeStamp->Enabled = true;
						cbbHws_SelectedIndexChanged(this,gcnew EventArgs());
						
						// We show the information of the configured 
						// and initiated hardware
						//
						txtInfo->Text = "Active Hardware: " + cbbHws->Text;
						txtInfo->Text += "\r\nBaud Rate: " + cbbBaudrates->Text;
						txtInfo->Text += "\r\nFrame Type: " + cbbMsgType->Text;
						// If was a no P&P Hardware, we show additional information
						//
						if(cbbIO->Enabled)
						{
							txtInfo->Text += "\r\nI/O Addr.: " + cbbIO->Text + "h";
							txtInfo->Text += "\r\nInterrupt: " + cbbInterrupt->Text;
						}
					}
						// An error occurred.  We show the error.
						//
					else
						txtInfo->Text  = "Error: " + String::Format("{0:X4}",(int)Res);
				}
			}
			else
				txtInfo->Text  = "Error: " + String::Format("{0:X4}",(int)Res);	
		}
	private: System::Void btnRelease_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			CANResult Res;
			// We choose Timer method by default
			//
			rdbTimer->Checked = true;

			// We stopt to read from tehe CAN Queue
			//
			tmrRead->Enabled = false;

			// We close the active hardware using the 
			// "Close" function of the PCANLight using 
			// as parameter the Hardware type.
			//
			Res = PCANLight::Close(ActiveHardware);

			// The Hardware was successfully closed
			//
			if(Res == ERR_OK)
				txtInfo->Text = "Hardware was successfully Released.\r\n";
				// An error occurred.  We show the error.
				//			
			else
				txtInfo->Text = "Error: " + String::Format("{0:X4}",(int)Res);
			
			// We set the varibale of active hardware to None
			// and activate/deactivate the corresponding buttons
			//
			ActiveHardware = (HardwareType)(-1);
			btnInit->Enabled = true;
			btnWrite->Enabled = false;
			btnRelease->Enabled = false;	
			btnSetFilter->Enabled = false;
			btnResetFilter->Enabled = false;
			btnInfo->Enabled = false;
			btnDllInfo->Enabled = false;
			rdbTimer->Enabled = false;
			rdbEvent->Enabled = false;
			chbTimeStamp->Checked = false;
			chbTimeStamp->Enabled = false;
			cbbHws_SelectedIndexChanged(this,gcnew EventArgs());
		}
	private: System::Void btnWrite_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			TCLightMsg^ MsgToSend;
			TextBox^ CurrentTextBox;		
			CANResult Res;

			// We create a TCLightMsg message structure 
			//
			MsgToSend = gcnew TCLightMsg();

			// We configurate the Message.  The ID (max 0x1FF),
			// Length of the Data, Message Type (Standard in 
			// this example) and die data
			//
			MsgToSend->ID = Convert::ToInt32(txtID->Text,16);
			MsgToSend->Len = Convert::ToByte(nudLength->Value);
			MsgToSend->MsgType = (chbExtended->Checked) ? MSGTYPE_EXTENDED : MSGTYPE_STANDARD;
			// If a remote frame will be sent, the data bytes are not important.
			//
			if(chbRemote->Checked)
				MsgToSend->MsgType = (MsgTypes)(MsgToSend->MsgType | MSGTYPE_RTR);
			else
			{
				// We get so much data as the Len of the message
				//
				CurrentTextBox = txtData0;
				for(int i=0; i < MsgToSend->Len; i++)
				{
					MsgToSend->Data[i] = Convert::ToByte(CurrentTextBox->Text,16);
					if(i < 7)
						CurrentTextBox = (TextBox^)this->GetNextControl(CurrentTextBox,true);
				}
			}

			// The message is sent to the configured hardware
			//
			Res = PCANLight::Write(ActiveHardware,MsgToSend);
			
			// The Hardware was successfully sent
			//
			if(Res == ERR_OK)
				txtInfo->Text = "Message was successfully SENT.\r\n";
				// An error occurred.  We show the error.
				//			
			else
				txtInfo->Text = "Error: " + String::Format("{0:X4}",(int)Res);	
		}
	private: System::Void btnClose_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			// We terminate the application
			//
			Close();
		}
	private: System::Void rdbStandard_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
		{
			unsigned int uiTemp;

			txtIdFrom->MaxLength = (rdbExtended->Checked)? 8: 3;
			txtIdTo->MaxLength = txtIdFrom->MaxLength;
			
			// the only way that the text length can be bigger als MaxLength
			// is when the change is from Extended to Standard message Type.
			// We have to handle this and set an ID not bigger than the Maximum
			// ID value for a Standard Message (0x7FF)
			//
			if(txtIdFrom->Text->Length > txtIdFrom->MaxLength)
			{
				uiTemp = Convert::ToInt32(txtIdFrom->Text,16);
				txtIdFrom->Text = (uiTemp < 0x7FF) ?  String::Format("{0:X3}",uiTemp): "7FF";
			}
			if(txtIdTo->Text->Length > txtIdTo->MaxLength)
			{
				uiTemp = Convert::ToInt32(txtIdTo->Text,16);
				txtIdTo->Text = (uiTemp < 0x7FF) ?  String::Format("{0:X3}",uiTemp): "7FF";
			}
		}
	private: System::Void txtIdFrom_Leave(System::Object^  sender, System::EventArgs^  e) 
		{
            int TextLength;
            unsigned int MaxValue;
            TextBox^ IdBox;

			IdBox = (TextBox^)sender;

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
            while (IdBox->Text->Length != TextLength)
                IdBox->Text = ("0" + IdBox->Text);

            // Because in this example will be sent only Standard messages
            // we check that the ID is not bigger than 0x7FF
            //
			if (Convert::ToUInt32(IdBox->Text,16) > MaxValue)
				IdBox->Text = String::Format("{0:X" + TextLength.ToString() + "}", MaxValue);
		}
	private: System::Void btnSetFilter_Click(System::Object^  sender, System::EventArgs^  e) 
		{
            unsigned int FromID, ToID;
            CANResult Res;

            // The range IDs is read
            //
			FromID = Convert::ToUInt32(txtIdFrom->Text,16);
			ToID = Convert::ToUInt32(txtIdTo->Text,16);
            
            // The desired Filter is set on the configured Hardware
            //
			Res = PCANLight::MsgFilter(ActiveHardware,FromID,ToID,(rdbStandard->Checked) ? MSGTYPE_STANDARD : MSGTYPE_EXTENDED);

            // The Filter was successfully set
            //
			if (Res == ERR_OK)
                txtInfo->Text = "Filter was successfully SET.\r\n";
            // An error occurred.  We show the error.
            //			
            else
				txtInfo->Text = "Error: " + String::Format("{0:X4}",(int)Res);
		}
	private: System::Void btnResetFilter_Click(System::Object^  sender, System::EventArgs^  e) 
		{
            CANResult Res;

            // The current Filter on the configured Hardware is reset 
            //
			Res = PCANLight::ResetFilter(ActiveHardware);

            // The Filter was successfully reset
            //
			if (Res == ERR_OK)
				txtInfo->Text = "Filter was successfully RESET.\r\n";
            // An error occurred.  We show the error.
            //			
            else
				txtInfo->Text = "Error: " + String::Format("{0:X4}",(int)Res);	
		}
	private: System::Void btnGetDevNumber_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			unsigned int iDevNum;
			CANResult Res;

			// The USB Device Number will asked 
			//
			Res = PCANLight::GetUSBDeviceNr((HardwareType)cbbHws->SelectedIndex, iDevNum);

			// The Device number was got successfully
			//
			if(Res == ERR_OK)
				txtInfo->Text = "USB Device Number is: " +  iDevNum.ToString() + ".\r\n";
				// An error occurred.  We show the error.
				//
			else
				txtInfo->Text = "Error: " + String::Format("{0:X4}", (unsigned int)Res);
		}
	private: System::Void btnSetDevNumber_Click(System::Object^  sender, System::EventArgs^  e) 
		{
			CANResult Res;

			// The USB Device Number will set
			//
			Res = PCANLight::SetUSBDeviceNr((HardwareType)cbbHws->SelectedIndex, Convert::ToUInt32(txtDevNumber->Text));

			// The Device number was set successfully
			//
			if(Res == ERR_OK)
				txtInfo->Text  = "USB Device Number was set";
				// An error occurred.  We show the error.
				//
			else
				txtInfo->Text  = "Set USB Device Number failed: " + String::Format("{0:X4}",(int)Res);
		}
	private: System::Void btnDllInfo_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			String^ strInfo;
			CANResult Res;

			// We execute the "VersionInfo" function of the PCANLight 
			// using as parameter the Hardware type and a string 
			// variable to get the info.
			// 
			Res = PCANLight::DllVersionInfo((HardwareType)cbbHws->SelectedIndex, strInfo);

			// The function was successfully executed
			//			
			if(Res == ERR_OK)
			{
				// We show the Version Information
				//
				strInfo = strInfo->Replace("\n","\r\n");
				strInfo = cbbHws->SelectedItem->ToString() + " Dll Version: " + strInfo;
				txtInfo->Text = strInfo;
			}
			// An error occurred.  We show the error.
			//			
			else
				txtInfo->Text  = "Error: " + String::Format("{0:X4}",(int)Res);
		 }
	private: System::Void chbTimeStamp_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		if(chbTimeStamp->Checked)
		{
			// Add Rcv Time column
			//
			if(!lstMessages->Columns->Contains(clhRcvTime))
				lstMessages->Columns->Add(clhRcvTime);
		}
		else
		{
			// Remove Rcv Time column
			//
			if(lstMessages->Columns->Contains(clhRcvTime))
				lstMessages->Columns->Remove(clhRcvTime);
		}
	}
	private: System::Void rdbTimer_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		ThreadStart^ threadDelegate;

		if(rdbTimer->Checked)
		{
			// Abort Read Thread if it exists
			//
			if(ReadThread != nullptr)
			{
				ReadThread->Abort();
				ReadThread->Join();
				ReadThread = nullptr;
			}

			// Enable Timer
			//
			tmrRead->Enabled = true;
		}
		else
		{
			// Disable Timer
			//
			tmrRead->Enabled = false;
			// Create and start the tread to read CAN Message using SetRcvEvent()
			threadDelegate = gcnew ThreadStart(this, &Form1::CANReadThreadFunc );
			ReadThread = gcnew Thread( threadDelegate );
			ReadThread->Start();
		}
	}
	private: System::Void txtDevNumber_Leave(System::Object^  sender, System::EventArgs^  e) 
		{
            if(txtDevNumber->Text == "")
                txtDevNumber->Text = "0";
			if (Convert::ToUInt64(txtDevNumber->Text) > UInt32::MaxValue)
				txtDevNumber->Text = UInt32::MaxValue.ToString();
		}
	private: System::Void txtDevNumber_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) 
		{
            // The Key is the Delete (Backspace) Key
            //
            if (e->KeyChar == 8)
                return;
            // The Key is a number between 0-9
            //
            if ((e->KeyChar > 47) && (e->KeyChar < 58))
                return;

            // Is neither a number nor a character between A(a) and F(f)
            //
            e->Handled = true;	
		}
};
}

