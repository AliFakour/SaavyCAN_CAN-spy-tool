namespace ICLRead
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.txtInfo = new System.Windows.Forms.TextBox();
            this.btnClose = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.chbRemote = new System.Windows.Forms.CheckBox();
            this.btnWrite = new System.Windows.Forms.Button();
            this.chbExtended = new System.Windows.Forms.CheckBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.txtID = new System.Windows.Forms.TextBox();
            this.txtData7 = new System.Windows.Forms.TextBox();
            this.txtData6 = new System.Windows.Forms.TextBox();
            this.txtData5 = new System.Windows.Forms.TextBox();
            this.txtData4 = new System.Windows.Forms.TextBox();
            this.txtData3 = new System.Windows.Forms.TextBox();
            this.txtData2 = new System.Windows.Forms.TextBox();
            this.txtData1 = new System.Windows.Forms.TextBox();
            this.txtData0 = new System.Windows.Forms.TextBox();
            this.nudLength = new System.Windows.Forms.NumericUpDown();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnDllInfo = new System.Windows.Forms.Button();
            this.cbbHws = new System.Windows.Forms.ComboBox();
            this.cbbMsgType = new System.Windows.Forms.ComboBox();
            this.btnSetUsbDevNumber = new System.Windows.Forms.Button();
            this.cbbInterrupt = new System.Windows.Forms.ComboBox();
            this.btnGetUsbDevNumber = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.cbbIO = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.cbbBaudrates = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.btnInfo = new System.Windows.Forms.Button();
            this.btnRelease = new System.Windows.Forms.Button();
            this.btnInit = new System.Windows.Forms.Button();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.chbTimeStamp = new System.Windows.Forms.CheckBox();
            this.labelReadMethod = new System.Windows.Forms.Label();
            this.rdbEvent = new System.Windows.Forms.RadioButton();
            this.lstMessages = new System.Windows.Forms.ListView();
            this.clhType = new System.Windows.Forms.ColumnHeader();
            this.clhID = new System.Windows.Forms.ColumnHeader();
            this.clhLength = new System.Windows.Forms.ColumnHeader();
            this.clhData = new System.Windows.Forms.ColumnHeader();
            this.clhCount = new System.Windows.Forms.ColumnHeader();
            this.clhRcvTime = new System.Windows.Forms.ColumnHeader();
            this.rdbTimer = new System.Windows.Forms.RadioButton();
            this.tmrRead = new System.Windows.Forms.Timer(this.components);
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.rdbStandard = new System.Windows.Forms.RadioButton();
            this.rdbExtended = new System.Windows.Forms.RadioButton();
            this.txtIdTo = new System.Windows.Forms.TextBox();
            this.txtIdFrom = new System.Windows.Forms.TextBox();
            this.btnResetFilter = new System.Windows.Forms.Button();
            this.btnSetFilter = new System.Windows.Forms.Button();
            this.label10 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.txtDevNumber = new System.Windows.Forms.TextBox();
            this.groupBox3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudLength)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.txtInfo);
            this.groupBox3.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.groupBox3.Location = new System.Drawing.Point(8, 475);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(498, 72);
            this.groupBox3.TabIndex = 44;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Information";
            // 
            // txtInfo
            // 
            this.txtInfo.BackColor = System.Drawing.Color.White;
            this.txtInfo.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.txtInfo.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.txtInfo.Location = new System.Drawing.Point(8, 16);
            this.txtInfo.Multiline = true;
            this.txtInfo.Name = "txtInfo";
            this.txtInfo.ReadOnly = true;
            this.txtInfo.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtInfo.Size = new System.Drawing.Size(482, 48);
            this.txtInfo.TabIndex = 38;
            this.txtInfo.TabStop = false;
            this.txtInfo.Text = "Select a Hardware and a configuration for it. Then click \"Initialize\" button";
            this.txtInfo.DoubleClick += new System.EventHandler(this.txtInfo_DoubleClick);
            // 
            // btnClose
            // 
            this.btnClose.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btnClose.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.btnClose.Location = new System.Drawing.Point(450, 553);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(56, 23);
            this.btnClose.TabIndex = 43;
            this.btnClose.Text = "Close";
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.chbRemote);
            this.groupBox2.Controls.Add(this.btnWrite);
            this.groupBox2.Controls.Add(this.chbExtended);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.label7);
            this.groupBox2.Controls.Add(this.label8);
            this.groupBox2.Controls.Add(this.txtID);
            this.groupBox2.Controls.Add(this.txtData7);
            this.groupBox2.Controls.Add(this.txtData6);
            this.groupBox2.Controls.Add(this.txtData5);
            this.groupBox2.Controls.Add(this.txtData4);
            this.groupBox2.Controls.Add(this.txtData3);
            this.groupBox2.Controls.Add(this.txtData2);
            this.groupBox2.Controls.Add(this.txtData1);
            this.groupBox2.Controls.Add(this.txtData0);
            this.groupBox2.Controls.Add(this.nudLength);
            this.groupBox2.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.groupBox2.Location = new System.Drawing.Point(8, 139);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(498, 91);
            this.groupBox2.TabIndex = 42;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Write Messages";
            // 
            // chbRemote
            // 
            this.chbRemote.Cursor = System.Windows.Forms.Cursors.Hand;
            this.chbRemote.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.chbRemote.Location = new System.Drawing.Point(112, 64);
            this.chbRemote.Name = "chbRemote";
            this.chbRemote.Size = new System.Drawing.Size(112, 24);
            this.chbRemote.TabIndex = 33;
            this.chbRemote.Text = "Remote Request";
            this.chbRemote.CheckedChanged += new System.EventHandler(this.chbRemote_CheckedChanged);
            // 
            // btnWrite
            // 
            this.btnWrite.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btnWrite.Enabled = false;
            this.btnWrite.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.btnWrite.Location = new System.Drawing.Point(398, 38);
            this.btnWrite.Name = "btnWrite";
            this.btnWrite.Size = new System.Drawing.Size(92, 23);
            this.btnWrite.TabIndex = 36;
            this.btnWrite.Text = "Write Message";
            this.btnWrite.Click += new System.EventHandler(this.btnWrite_Click);
            // 
            // chbExtended
            // 
            this.chbExtended.Cursor = System.Windows.Forms.Cursors.Hand;
            this.chbExtended.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.chbExtended.Location = new System.Drawing.Point(8, 64);
            this.chbExtended.Name = "chbExtended";
            this.chbExtended.Size = new System.Drawing.Size(112, 24);
            this.chbExtended.TabIndex = 34;
            this.chbExtended.Text = "Extended Frame";
            this.chbExtended.CheckedChanged += new System.EventHandler(this.chbExtended_CheckedChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(144, 16);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(60, 13);
            this.label6.TabIndex = 32;
            this.label6.Text = "Data (0..7):";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(96, 16);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(43, 13);
            this.label7.TabIndex = 31;
            this.label7.Text = "Length:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(8, 16);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(49, 13);
            this.label8.TabIndex = 30;
            this.label8.Text = "ID (Hex):";
            // 
            // txtID
            // 
            this.txtID.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.txtID.Location = new System.Drawing.Point(8, 40);
            this.txtID.MaxLength = 3;
            this.txtID.Name = "txtID";
            this.txtID.Size = new System.Drawing.Size(80, 20);
            this.txtID.TabIndex = 20;
            this.txtID.Text = "0";
            this.txtID.Leave += new System.EventHandler(this.txtID_Leave);
            this.txtID.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtID_KeyPress);
            // 
            // txtData7
            // 
            this.txtData7.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.txtData7.Location = new System.Drawing.Point(368, 40);
            this.txtData7.MaxLength = 2;
            this.txtData7.Name = "txtData7";
            this.txtData7.Size = new System.Drawing.Size(24, 20);
            this.txtData7.TabIndex = 29;
            this.txtData7.Text = "00";
            this.txtData7.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.txtData7.Leave += new System.EventHandler(this.txtData0_Leave);
            this.txtData7.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtID_KeyPress);
            // 
            // txtData6
            // 
            this.txtData6.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.txtData6.Location = new System.Drawing.Point(336, 40);
            this.txtData6.MaxLength = 2;
            this.txtData6.Name = "txtData6";
            this.txtData6.Size = new System.Drawing.Size(24, 20);
            this.txtData6.TabIndex = 28;
            this.txtData6.Text = "00";
            this.txtData6.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.txtData6.Leave += new System.EventHandler(this.txtData0_Leave);
            this.txtData6.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtID_KeyPress);
            // 
            // txtData5
            // 
            this.txtData5.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.txtData5.Location = new System.Drawing.Point(304, 40);
            this.txtData5.MaxLength = 2;
            this.txtData5.Name = "txtData5";
            this.txtData5.Size = new System.Drawing.Size(24, 20);
            this.txtData5.TabIndex = 27;
            this.txtData5.Text = "00";
            this.txtData5.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.txtData5.Leave += new System.EventHandler(this.txtData0_Leave);
            this.txtData5.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtID_KeyPress);
            // 
            // txtData4
            // 
            this.txtData4.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.txtData4.Location = new System.Drawing.Point(272, 40);
            this.txtData4.MaxLength = 2;
            this.txtData4.Name = "txtData4";
            this.txtData4.Size = new System.Drawing.Size(24, 20);
            this.txtData4.TabIndex = 26;
            this.txtData4.Text = "00";
            this.txtData4.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.txtData4.Leave += new System.EventHandler(this.txtData0_Leave);
            this.txtData4.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtID_KeyPress);
            // 
            // txtData3
            // 
            this.txtData3.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.txtData3.Location = new System.Drawing.Point(240, 40);
            this.txtData3.MaxLength = 2;
            this.txtData3.Name = "txtData3";
            this.txtData3.Size = new System.Drawing.Size(24, 20);
            this.txtData3.TabIndex = 25;
            this.txtData3.Text = "00";
            this.txtData3.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.txtData3.Leave += new System.EventHandler(this.txtData0_Leave);
            this.txtData3.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtID_KeyPress);
            // 
            // txtData2
            // 
            this.txtData2.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.txtData2.Location = new System.Drawing.Point(208, 40);
            this.txtData2.MaxLength = 2;
            this.txtData2.Name = "txtData2";
            this.txtData2.Size = new System.Drawing.Size(24, 20);
            this.txtData2.TabIndex = 24;
            this.txtData2.Text = "00";
            this.txtData2.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.txtData2.Leave += new System.EventHandler(this.txtData0_Leave);
            this.txtData2.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtID_KeyPress);
            // 
            // txtData1
            // 
            this.txtData1.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.txtData1.Location = new System.Drawing.Point(176, 40);
            this.txtData1.MaxLength = 2;
            this.txtData1.Name = "txtData1";
            this.txtData1.Size = new System.Drawing.Size(24, 20);
            this.txtData1.TabIndex = 23;
            this.txtData1.Text = "00";
            this.txtData1.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.txtData1.Leave += new System.EventHandler(this.txtData0_Leave);
            this.txtData1.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtID_KeyPress);
            // 
            // txtData0
            // 
            this.txtData0.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.txtData0.Location = new System.Drawing.Point(144, 40);
            this.txtData0.MaxLength = 2;
            this.txtData0.Name = "txtData0";
            this.txtData0.Size = new System.Drawing.Size(24, 20);
            this.txtData0.TabIndex = 22;
            this.txtData0.Text = "00";
            this.txtData0.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.txtData0.Leave += new System.EventHandler(this.txtData0_Leave);
            this.txtData0.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtID_KeyPress);
            // 
            // nudLength
            // 
            this.nudLength.BackColor = System.Drawing.Color.White;
            this.nudLength.Location = new System.Drawing.Point(96, 40);
            this.nudLength.Maximum = new decimal(new int[] {
            8,
            0,
            0,
            0});
            this.nudLength.Name = "nudLength";
            this.nudLength.ReadOnly = true;
            this.nudLength.Size = new System.Drawing.Size(40, 20);
            this.nudLength.TabIndex = 21;
            this.nudLength.Value = new decimal(new int[] {
            8,
            0,
            0,
            0});
            this.nudLength.ValueChanged += new System.EventHandler(this.nudLength_ValueChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.txtDevNumber);
            this.groupBox1.Controls.Add(this.btnDllInfo);
            this.groupBox1.Controls.Add(this.cbbHws);
            this.groupBox1.Controls.Add(this.cbbMsgType);
            this.groupBox1.Controls.Add(this.btnSetUsbDevNumber);
            this.groupBox1.Controls.Add(this.cbbInterrupt);
            this.groupBox1.Controls.Add(this.btnGetUsbDevNumber);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.cbbIO);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.cbbBaudrates);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.btnInfo);
            this.groupBox1.Controls.Add(this.btnRelease);
            this.groupBox1.Controls.Add(this.btnInit);
            this.groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.groupBox1.Location = new System.Drawing.Point(8, 8);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(498, 125);
            this.groupBox1.TabIndex = 41;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Connection";
            // 
            // btnDllInfo
            // 
            this.btnDllInfo.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btnDllInfo.Enabled = false;
            this.btnDllInfo.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.btnDllInfo.Location = new System.Drawing.Point(331, 88);
            this.btnDllInfo.Name = "btnDllInfo";
            this.btnDllInfo.Size = new System.Drawing.Size(88, 23);
            this.btnDllInfo.TabIndex = 49;
            this.btnDllInfo.Text = "Get Dll Version";
            this.btnDllInfo.UseVisualStyleBackColor = true;
            this.btnDllInfo.Click += new System.EventHandler(this.btnDllInfo_Click);
            // 
            // cbbHws
            // 
            this.cbbHws.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbbHws.Items.AddRange(new object[] {
            "ISA",
            "ISA 2-CH",
            "PCI",
            "PCI 2-CH",
            "PCC",
            "PCC 2-CH",
            "USB 1-CH",
            "USB 2-CH",
            "DONGLE PRO",
            "DONGLE"});
            this.cbbHws.Location = new System.Drawing.Point(8, 32);
            this.cbbHws.Name = "cbbHws";
            this.cbbHws.Size = new System.Drawing.Size(112, 21);
            this.cbbHws.TabIndex = 32;
            this.cbbHws.SelectedIndexChanged += new System.EventHandler(this.cbbHws_SelectedIndexChanged);
            // 
            // cbbMsgType
            // 
            this.cbbMsgType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbbMsgType.Items.AddRange(new object[] {
            "Standard",
            "Extended"});
            this.cbbMsgType.Location = new System.Drawing.Point(230, 32);
            this.cbbMsgType.Name = "cbbMsgType";
            this.cbbMsgType.Size = new System.Drawing.Size(88, 21);
            this.cbbMsgType.TabIndex = 37;
            // 
            // btnSetUsbDevNumber
            // 
            this.btnSetUsbDevNumber.Location = new System.Drawing.Point(8, 88);
            this.btnSetUsbDevNumber.Name = "btnSetUsbDevNumber";
            this.btnSetUsbDevNumber.Size = new System.Drawing.Size(143, 23);
            this.btnSetUsbDevNumber.TabIndex = 46;
            this.btnSetUsbDevNumber.Text = "Set USB Device Number";
            this.btnSetUsbDevNumber.UseVisualStyleBackColor = true;
            this.btnSetUsbDevNumber.Click += new System.EventHandler(this.btnSetUsbDevNumber_Click);
            // 
            // cbbInterrupt
            // 
            this.cbbInterrupt.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbbInterrupt.Items.AddRange(new object[] {
            "3",
            "4",
            "5",
            "7",
            "9",
            "10",
            "11",
            "12",
            "15"});
            this.cbbInterrupt.Location = new System.Drawing.Point(404, 32);
            this.cbbInterrupt.Name = "cbbInterrupt";
            this.cbbInterrupt.Size = new System.Drawing.Size(86, 21);
            this.cbbInterrupt.TabIndex = 39;
            // 
            // btnGetUsbDevNumber
            // 
            this.btnGetUsbDevNumber.Location = new System.Drawing.Point(8, 59);
            this.btnGetUsbDevNumber.Name = "btnGetUsbDevNumber";
            this.btnGetUsbDevNumber.Size = new System.Drawing.Size(140, 23);
            this.btnGetUsbDevNumber.TabIndex = 45;
            this.btnGetUsbDevNumber.Text = "Get USB Device Number";
            this.btnGetUsbDevNumber.UseVisualStyleBackColor = true;
            this.btnGetUsbDevNumber.Click += new System.EventHandler(this.btnGetUsbDevNumber_Click);
            // 
            // label5
            // 
            this.label5.Location = new System.Drawing.Point(404, 16);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(72, 23);
            this.label5.TabIndex = 44;
            this.label5.Text = "Interrupt:";
            // 
            // cbbIO
            // 
            this.cbbIO.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbbIO.Items.AddRange(new object[] {
            "0100",
            "0120",
            "0140",
            "0200",
            "0220",
            "0240",
            "0260",
            "0278",
            "0280",
            "02A0",
            "02C0",
            "02E0",
            "02E8",
            "02F8",
            "0300",
            "0320",
            "0340",
            "0360",
            "0378",
            "0380",
            "03BC",
            "03E0",
            "03E8",
            "03F8"});
            this.cbbIO.Location = new System.Drawing.Point(326, 32);
            this.cbbIO.Name = "cbbIO";
            this.cbbIO.Size = new System.Drawing.Size(72, 21);
            this.cbbIO.TabIndex = 38;
            // 
            // label4
            // 
            this.label4.Location = new System.Drawing.Point(326, 16);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(72, 23);
            this.label4.TabIndex = 43;
            this.label4.Text = "I/O Address:";
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(230, 16);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(64, 23);
            this.label3.TabIndex = 42;
            this.label3.Text = "Msg Type:";
            // 
            // cbbBaudrates
            // 
            this.cbbBaudrates.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbbBaudrates.Items.AddRange(new object[] {
            "1 MBit/sec",
            "500 KBit/sec",
            "250 KBit/sec",
            "125 KBit/sec",
            "100 KBit/sec",
            "50 KBit/sec",
            "20 KBit/sec",
            "10 KBit/sec",
            "5 KBit/sec"});
            this.cbbBaudrates.Location = new System.Drawing.Point(126, 32);
            this.cbbBaudrates.Name = "cbbBaudrates";
            this.cbbBaudrates.Size = new System.Drawing.Size(96, 21);
            this.cbbBaudrates.TabIndex = 36;
            this.cbbBaudrates.SelectedIndexChanged += new System.EventHandler(this.cbbBaudrates_SelectedIndexChanged);
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(126, 16);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(56, 23);
            this.label2.TabIndex = 41;
            this.label2.Text = "Baudrate:";
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(7, 16);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(56, 23);
            this.label1.TabIndex = 40;
            this.label1.Text = "Hardware:";
            // 
            // btnInfo
            // 
            this.btnInfo.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btnInfo.Enabled = false;
            this.btnInfo.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.btnInfo.Location = new System.Drawing.Point(235, 88);
            this.btnInfo.Name = "btnInfo";
            this.btnInfo.Size = new System.Drawing.Size(88, 23);
            this.btnInfo.TabIndex = 33;
            this.btnInfo.Text = "Get Info";
            this.btnInfo.Click += new System.EventHandler(this.btnInfo_Click);
            // 
            // btnRelease
            // 
            this.btnRelease.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btnRelease.Enabled = false;
            this.btnRelease.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.btnRelease.Location = new System.Drawing.Point(425, 88);
            this.btnRelease.Name = "btnRelease";
            this.btnRelease.Size = new System.Drawing.Size(65, 23);
            this.btnRelease.TabIndex = 35;
            this.btnRelease.Text = "Release";
            this.btnRelease.Click += new System.EventHandler(this.btnRelease_Click);
            // 
            // btnInit
            // 
            this.btnInit.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btnInit.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.btnInit.Location = new System.Drawing.Point(425, 59);
            this.btnInit.Name = "btnInit";
            this.btnInit.Size = new System.Drawing.Size(65, 23);
            this.btnInit.TabIndex = 34;
            this.btnInit.Text = "Initialize";
            this.btnInit.Click += new System.EventHandler(this.btnInit_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.chbTimeStamp);
            this.groupBox4.Controls.Add(this.labelReadMethod);
            this.groupBox4.Controls.Add(this.rdbEvent);
            this.groupBox4.Controls.Add(this.lstMessages);
            this.groupBox4.Controls.Add(this.rdbTimer);
            this.groupBox4.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.groupBox4.Location = new System.Drawing.Point(8, 307);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(498, 162);
            this.groupBox4.TabIndex = 45;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Read Messages";
            // 
            // chbTimeStamp
            // 
            this.chbTimeStamp.AutoSize = true;
            this.chbTimeStamp.Checked = true;
            this.chbTimeStamp.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chbTimeStamp.Enabled = false;
            this.chbTimeStamp.Location = new System.Drawing.Point(8, 139);
            this.chbTimeStamp.Name = "chbTimeStamp";
            this.chbTimeStamp.Size = new System.Drawing.Size(112, 17);
            this.chbTimeStamp.TabIndex = 75;
            this.chbTimeStamp.Text = "Show Time Stamp";
            this.chbTimeStamp.UseVisualStyleBackColor = true;
            this.chbTimeStamp.CheckedChanged += new System.EventHandler(this.chbTimeStamp_CheckedChanged);
            // 
            // labelReadMethod
            // 
            this.labelReadMethod.AutoSize = true;
            this.labelReadMethod.Location = new System.Drawing.Point(7, 16);
            this.labelReadMethod.Name = "labelReadMethod";
            this.labelReadMethod.Size = new System.Drawing.Size(75, 13);
            this.labelReadMethod.TabIndex = 74;
            this.labelReadMethod.Text = "Read Method:";
            // 
            // rdbEvent
            // 
            this.rdbEvent.AutoSize = true;
            this.rdbEvent.Enabled = false;
            this.rdbEvent.Location = new System.Drawing.Point(159, 14);
            this.rdbEvent.Name = "rdbEvent";
            this.rdbEvent.Size = new System.Drawing.Size(68, 17);
            this.rdbEvent.TabIndex = 73;
            this.rdbEvent.Text = "By Event";
            this.rdbEvent.UseVisualStyleBackColor = true;
            // 
            // lstMessages
            // 
            this.lstMessages.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.clhType,
            this.clhID,
            this.clhLength,
            this.clhData,
            this.clhCount,
            this.clhRcvTime});
            this.lstMessages.FullRowSelect = true;
            this.lstMessages.Location = new System.Drawing.Point(8, 37);
            this.lstMessages.MultiSelect = false;
            this.lstMessages.Name = "lstMessages";
            this.lstMessages.Size = new System.Drawing.Size(482, 96);
            this.lstMessages.TabIndex = 28;
            this.lstMessages.UseCompatibleStateImageBehavior = false;
            this.lstMessages.View = System.Windows.Forms.View.Details;
            this.lstMessages.DoubleClick += new System.EventHandler(this.lstMessages_DoubleClick);
            // 
            // clhType
            // 
            this.clhType.Text = "Type";
            this.clhType.Width = 69;
            // 
            // clhID
            // 
            this.clhID.Text = "ID";
            this.clhID.Width = 73;
            // 
            // clhLength
            // 
            this.clhLength.Text = "Length";
            this.clhLength.Width = 50;
            // 
            // clhData
            // 
            this.clhData.Text = "Data";
            this.clhData.Width = 138;
            // 
            // clhCount
            // 
            this.clhCount.Text = "Count";
            this.clhCount.Width = 49;
            // 
            // clhRcvTime
            // 
            this.clhRcvTime.Text = "Rcv Time";
            this.clhRcvTime.Width = 97;
            // 
            // rdbTimer
            // 
            this.rdbTimer.AutoSize = true;
            this.rdbTimer.Checked = true;
            this.rdbTimer.Enabled = false;
            this.rdbTimer.Location = new System.Drawing.Point(89, 14);
            this.rdbTimer.Name = "rdbTimer";
            this.rdbTimer.Size = new System.Drawing.Size(66, 17);
            this.rdbTimer.TabIndex = 72;
            this.rdbTimer.TabStop = true;
            this.rdbTimer.Text = "By Timer";
            this.rdbTimer.UseVisualStyleBackColor = true;
            this.rdbTimer.CheckedChanged += new System.EventHandler(this.rdbTimer_CheckedChanged);
            // 
            // tmrRead
            // 
            this.tmrRead.Interval = 50;
            this.tmrRead.Tick += new System.EventHandler(this.tmrRead_Tick);
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.rdbStandard);
            this.groupBox5.Controls.Add(this.rdbExtended);
            this.groupBox5.Controls.Add(this.txtIdTo);
            this.groupBox5.Controls.Add(this.txtIdFrom);
            this.groupBox5.Controls.Add(this.btnResetFilter);
            this.groupBox5.Controls.Add(this.btnSetFilter);
            this.groupBox5.Controls.Add(this.label10);
            this.groupBox5.Controls.Add(this.label9);
            this.groupBox5.Location = new System.Drawing.Point(8, 236);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(498, 65);
            this.groupBox5.TabIndex = 46;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Message Filter";
            // 
            // rdbStandard
            // 
            this.rdbStandard.AutoSize = true;
            this.rdbStandard.Checked = true;
            this.rdbStandard.Location = new System.Drawing.Point(11, 37);
            this.rdbStandard.Name = "rdbStandard";
            this.rdbStandard.Size = new System.Drawing.Size(68, 17);
            this.rdbStandard.TabIndex = 71;
            this.rdbStandard.TabStop = true;
            this.rdbStandard.Text = "Standard";
            this.rdbStandard.UseVisualStyleBackColor = true;
            this.rdbStandard.CheckedChanged += new System.EventHandler(this.rdbStandard_CheckedChanged);
            // 
            // rdbExtended
            // 
            this.rdbExtended.AutoSize = true;
            this.rdbExtended.Location = new System.Drawing.Point(89, 37);
            this.rdbExtended.Name = "rdbExtended";
            this.rdbExtended.Size = new System.Drawing.Size(70, 17);
            this.rdbExtended.TabIndex = 70;
            this.rdbExtended.Text = "Extended";
            this.rdbExtended.UseVisualStyleBackColor = true;
            // 
            // txtIdTo
            // 
            this.txtIdTo.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.txtIdTo.Location = new System.Drawing.Point(265, 36);
            this.txtIdTo.MaxLength = 3;
            this.txtIdTo.Name = "txtIdTo";
            this.txtIdTo.Size = new System.Drawing.Size(90, 20);
            this.txtIdTo.TabIndex = 67;
            this.txtIdTo.Text = "0";
            this.txtIdTo.Leave += new System.EventHandler(this.txtIdFrom_Leave);
            this.txtIdTo.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtID_KeyPress);
            // 
            // txtIdFrom
            // 
            this.txtIdFrom.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.txtIdFrom.Location = new System.Drawing.Point(169, 36);
            this.txtIdFrom.MaxLength = 3;
            this.txtIdFrom.Name = "txtIdFrom";
            this.txtIdFrom.Size = new System.Drawing.Size(90, 20);
            this.txtIdFrom.TabIndex = 66;
            this.txtIdFrom.Text = "0";
            this.txtIdFrom.Leave += new System.EventHandler(this.txtIdFrom_Leave);
            this.txtIdFrom.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtID_KeyPress);
            // 
            // btnResetFilter
            // 
            this.btnResetFilter.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btnResetFilter.Enabled = false;
            this.btnResetFilter.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.btnResetFilter.Location = new System.Drawing.Point(434, 34);
            this.btnResetFilter.Name = "btnResetFilter";
            this.btnResetFilter.Size = new System.Drawing.Size(56, 23);
            this.btnResetFilter.TabIndex = 64;
            this.btnResetFilter.Text = "Reset";
            this.btnResetFilter.Click += new System.EventHandler(this.btnResetFilter_Click);
            // 
            // btnSetFilter
            // 
            this.btnSetFilter.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btnSetFilter.Enabled = false;
            this.btnSetFilter.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.btnSetFilter.Location = new System.Drawing.Point(372, 34);
            this.btnSetFilter.Name = "btnSetFilter";
            this.btnSetFilter.Size = new System.Drawing.Size(56, 23);
            this.btnSetFilter.TabIndex = 63;
            this.btnSetFilter.Text = "Set";
            this.btnSetFilter.Click += new System.EventHandler(this.btnSetFilter_Click);
            // 
            // label10
            // 
            this.label10.Location = new System.Drawing.Point(265, 17);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(56, 23);
            this.label10.TabIndex = 62;
            this.label10.Text = "To:";
            // 
            // label9
            // 
            this.label9.Location = new System.Drawing.Point(166, 17);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(56, 23);
            this.label9.TabIndex = 61;
            this.label9.Text = "From:";
            // 
            // txtDevNumber
            // 
            this.txtDevNumber.Enabled = false;
            this.txtDevNumber.Location = new System.Drawing.Point(157, 90);
            this.txtDevNumber.MaxLength = 10;
            this.txtDevNumber.Name = "txtDevNumber";
            this.txtDevNumber.Size = new System.Drawing.Size(72, 20);
            this.txtDevNumber.TabIndex = 50;
            this.txtDevNumber.Text = "0";
            this.txtDevNumber.Leave += new System.EventHandler(this.txtDevNumber_Leave);
            this.txtDevNumber.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtDevNumber_KeyPress);
            // 
            // Form1
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(514, 584);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.btnClose);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "I CAN Do It! - Light";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.Closing += new System.ComponentModel.CancelEventHandler(this.Form1_Closing);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudLength)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.ResumeLayout(false);

        }
        #endregion

        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TextBox txtInfo;
        private System.Windows.Forms.Button btnClose;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button btnWrite;
        private System.Windows.Forms.CheckBox chbExtended;
        private System.Windows.Forms.CheckBox chbRemote;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox txtID;
        private System.Windows.Forms.TextBox txtData7;
        private System.Windows.Forms.TextBox txtData6;
        private System.Windows.Forms.TextBox txtData5;
        private System.Windows.Forms.TextBox txtData4;
        private System.Windows.Forms.TextBox txtData3;
        private System.Windows.Forms.TextBox txtData2;
        private System.Windows.Forms.TextBox txtData1;
        private System.Windows.Forms.TextBox txtData0;
        private System.Windows.Forms.NumericUpDown nudLength;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ComboBox cbbHws;
        private System.Windows.Forms.ComboBox cbbMsgType;
        private System.Windows.Forms.ComboBox cbbInterrupt;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox cbbIO;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox cbbBaudrates;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnInfo;
        private System.Windows.Forms.Button btnRelease;
        private System.Windows.Forms.Button btnInit;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.ListView lstMessages;
        private System.Windows.Forms.ColumnHeader clhType;
        private System.Windows.Forms.ColumnHeader clhID;
        private System.Windows.Forms.ColumnHeader clhLength;
        private System.Windows.Forms.ColumnHeader clhData;
        private System.Windows.Forms.ColumnHeader clhCount;
        private System.Windows.Forms.Timer tmrRead;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.TextBox txtIdTo;
        private System.Windows.Forms.TextBox txtIdFrom;
        private System.Windows.Forms.Button btnResetFilter;
        private System.Windows.Forms.Button btnSetFilter;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.RadioButton rdbStandard;
        private System.Windows.Forms.RadioButton rdbExtended;
        private System.Windows.Forms.Button btnSetUsbDevNumber;
        private System.Windows.Forms.Button btnGetUsbDevNumber;
        private System.Windows.Forms.Button btnDllInfo;
        private System.Windows.Forms.CheckBox chbTimeStamp;
        private System.Windows.Forms.Label labelReadMethod;
        private System.Windows.Forms.RadioButton rdbEvent;
        private System.Windows.Forms.RadioButton rdbTimer;
        private System.Windows.Forms.ColumnHeader clhRcvTime;
        private System.Windows.Forms.TextBox txtDevNumber;
    }
}