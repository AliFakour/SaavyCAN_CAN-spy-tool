using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using Peak.Can.Light;
using System.Threading;

namespace ICLRead
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public partial class Form1 : Form
	{
		#region Structures
		/// <summary>
		/// Message Status structure used to show CAN Messages
		/// in a ListView
		/// </summary>
		private struct MessageStatus
		{
			private TCLightMsg Msg;
			private int iIndex;

			public MessageStatus(TCLightMsg CanMsg,int Index)
			{
				Msg = CanMsg;
				iIndex = Index;
			}

			public TCLightMsg CANMessage
			{
				get { return Msg; }
			}

			public int Position
			{
				get { return iIndex; }
			}
		}	
		#endregion

		/// <summary>
		/// Save the current initiated hardware type
		/// </summary>
		private HardwareType ActiveHardware;

		/// <summary>
		/// CAN messages Array. Store the Message Status for its display
		/// </summary>
		private ArrayList LastMsgsList;

        /// <summary>
	    /// Read Delegate Handler
	    /// </summary>
	    private delegate void ReadDelegateHandler();

	    /// <summary>
	    /// Read Delegate in order to call "ReadMessage" function
	    /// using .NET invoke function
	    /// </summary>
	    private ReadDelegateHandler ReadDelegate;

	    /// <summary>
	    /// Receive-Event
	    /// </summary>
	    private AutoResetEvent RcvEvent;

	    /// <summary>
	    /// Thread in order to read messages using Received-Event method
	    /// </summary>
	    private Thread ReadThread;

		public Form1()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();
			// We set the variable to know which hardware is 
			// currently selected (none!)
			//
			ActiveHardware = (HardwareType)(-1);
			// Create a list to store the displayed mesasges 
			//
			LastMsgsList = new ArrayList();
		}

		#region Miscellaneus Help Functions
		private void ModifyMsgEntry(MessageStatus LastMsg, TCLightMsg NewMsg, TCLightTimestamp MyTimeStamp)
		{
			string strLastData, strNewData;
			MessageStatus NewStatus;
			ListViewItem CurrItem;
			uint iLen;
			int iCount;

			strNewData = strLastData = "";

			// Values from the last messages
			//
			CurrItem = lstMessages.Items[LastMsg.Position];
			iCount = Convert.ToInt32(CurrItem.SubItems[4].Text);
			strLastData = CurrItem.SubItems[3].Text;
			iLen = LastMsg.CANMessage.Len;

			// New values 
			//
			if((NewMsg.MsgType & MsgTypes.MSGTYPE_RTR) != 0)
				strNewData = "Remote Request";
			else
				for(int i=0; i< NewMsg.Len; i++)
					strNewData += string.Format("{0:X2} ",NewMsg.Data[i]);
				
			// Count is updated
			//
			iCount += 1;

			// Set the changes
			//
			if(iLen != NewMsg.Len)
			{
				iLen = NewMsg.Len;		
				CurrItem.SubItems[2].Text = iLen.ToString();
			}

			if(strLastData != strNewData)
				CurrItem.SubItems[3].Text = strNewData;

			CurrItem.SubItems[4].Text = iCount.ToString();

            // Update time stamp information if need be
            //
            if (MyTimeStamp != null)
            {
                String timeStamp = MyTimeStamp.millis.ToString() + "." + MyTimeStamp.micros.ToString();

                // Add new SubItem if it doesn't exists
                //
                if (CurrItem.SubItems.Count == 5)
                    CurrItem.SubItems.Add(timeStamp);
                // Else update existing SubItem
                //
                else
                    CurrItem.SubItems[5].Text = timeStamp;
            }

			
			// Save the new Status of the message
			// NOTE: The objects are saved in the same index position which 
			// they use in the Listview
			//
			NewStatus = new MessageStatus(NewMsg,LastMsg.Position);
			LastMsgsList.RemoveAt(LastMsg.Position);
			LastMsgsList.Insert(LastMsg.Position,NewStatus);			
		}

        private void InsertMsgEntry(TCLightMsg NewMsg, TCLightTimestamp MyTimeStamp)
		{
			string strNewData,strTemp;
			ListViewItem CurrItem;
			MessageStatus CurrMsg;

			strTemp = strNewData = "";

			// Add the new ListView Item with the Type of the message
			//	
			if((NewMsg.MsgType & MsgTypes.MSGTYPE_EXTENDED) != 0)
				strTemp = "EXTENDED";
			else
				strTemp = "STANDARD";

			if((NewMsg.MsgType & MsgTypes.MSGTYPE_RTR) == MsgTypes.MSGTYPE_RTR)
				strTemp += "/RTR";

			CurrItem = lstMessages.Items.Add(strTemp);
			
			
			// We format the ID of the message and show it
			//
			if((NewMsg.MsgType & MsgTypes.MSGTYPE_EXTENDED) != 0)
				CurrItem.SubItems.Add(string.Format("{0:X8}h",NewMsg.ID));
			else
				CurrItem.SubItems.Add(string.Format("{0:X3}h",NewMsg.ID));
				
			// We set the length of the Message
			//
			CurrItem.SubItems.Add(NewMsg.Len.ToString());

			// We format the data of the message. Each data is one 
			// byte of Hexadecimal data			
			//
			if((NewMsg.MsgType & MsgTypes.MSGTYPE_RTR) == MsgTypes.MSGTYPE_RTR)
				strNewData = "Remote Request";
			else
				for(int i=0; i< NewMsg.Len; i++)
					strNewData += string.Format("{0:X2} ",NewMsg.Data[i]);
			
			CurrItem.SubItems.Add(strNewData);

			// The message is the First, so count is 1 and there 
			// is not any time difference between messages.
			//
			CurrItem.SubItems.Add("1");

            // Add time stamp information if need be
            //
            if (MyTimeStamp != null)
                CurrItem.SubItems.Add(MyTimeStamp.millis.ToString() + "." + MyTimeStamp.micros.ToString());
				
			// We add this status in the last message list
			//
			CurrMsg = new MessageStatus(NewMsg,CurrItem.Index);
			LastMsgsList.Add(CurrMsg); 
		}

		private void ProcessMessage(TCLightMsg MyMsg, TCLightTimestamp MyTimeStamp)
		{
			bool bFound = false;
			MessageStatus CurrMessage;

			// Initialization
			//
			CurrMessage = new MessageStatus();

			// We search if a message (Smae ID and Type) is 
			// already received or if this is a new message
			//
			for(int i=0; i< LastMsgsList.Count; i++)
			{
				CurrMessage = (MessageStatus)LastMsgsList[i];
				if(CurrMessage.CANMessage.ID == MyMsg.ID)
					if(CurrMessage.CANMessage.MsgType == MyMsg.MsgType)
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

        // This helper function retrieve active Dll Major version number
	    //
	    private CANResult DllMajorVersion(HardwareType hType, out int majorVersion)
	    {
            CANResult Res;
		    String dllVersionStr = "";

		    // We execute the "DllVersionInfo" function of the PCANLight
		    // using as parameter the Hardware type and a string
		    // variable to get the info like "x.xx"
		    //
            Res = PCANLight.DllVersionInfo(hType, out dllVersionStr);

		    // We retrieve major version number 
		    // spliting versionNumberStr based on "." decimal symbol
		    //
            String[] versionTabInfo = dllVersionStr.Split('.');
            if (versionTabInfo.Length > 0)
                Int32.TryParse(versionTabInfo[0].ToString(), out majorVersion);
            else
                majorVersion = 0;
		    return Res;
	    }

        private void CANReadThreadFunc() 
	    {
		    // Sets the handle of the Receive-Event.
		    //
            PCANLight.SetRcvEvent(ActiveHardware, RcvEvent);

		    // While this mode is selected
		    while(rdbEvent.Checked)
		    {
			    // Waiting for Receive-Event
			    // 
			    RcvEvent.WaitOne();

			    // Process Receive-Event using .NET Invoke function
			    // in order to interact with Winforms UI
			    // 
			    this.Invoke(ReadDelegate);
		    }
	    }
        private void ReadMessage() 
	    {
		    TCLightMsg MyMsg;
            TCLightTimestamp MyTimeStamp = null;
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
			    if(chbTimeStamp.Checked)
				    // We execute the "ReadEx" function of the PCANLight
				    // if "Show Time Stamp" checkbox is selected
				    //
                    Res = PCANLight.ReadEx(ActiveHardware, out MyMsg, out MyTimeStamp);
			    else
				    // We execute the "Read" function of the PCANLight
				    // if "Show Time Stamp" checkbox isn't selected
				    //
                    Res = PCANLight.Read(ActiveHardware, out MyMsg);

			    // A message was received
			    // We process the message(s)
			    //
			    if(Res == CANResult.ERR_OK)
				    ProcessMessage(MyMsg, MyTimeStamp);

            } while (((int)ActiveHardware != -1) && (!Convert.ToBoolean(Res & CANResult.ERR_QRCVEMPTY)));
	    }
		#endregion

		private void Form1_Load(object sender, System.EventArgs e)
		{
			// Set the standard values in the interface
			//
			cbbHws.SelectedIndex = 0;
			cbbBaudrates.SelectedIndex = 0;
			cbbIO.Text = "0378";
			cbbInterrupt.Text = "7";
			cbbMsgType.SelectedIndex = 0;
			
            // Create Delegates to use invoke() function
			//
			ReadDelegate = new ReadDelegateHandler(this.ReadMessage);
			// Create AutoResetEvent to use PCLight SetRcvEvent() function
			//
			RcvEvent = new AutoResetEvent(false);
		}

		private void Form1_Closing(object sender, System.ComponentModel.CancelEventArgs e)
		{
			// If we are reading, we stop to read
			//
			tmrRead.Enabled = false;
		}

		private void cbbHws_SelectedIndexChanged(object sender, System.EventArgs e)
		{
            bool bShowIO;
            HardwareType current;

            current = (HardwareType)cbbHws.SelectedIndex;

            // According with the selection in the Hardware list, 
            // we Enable/Disable the input controls for I/O Address and 
            // Interrupt. (This parameters are NOT necessary for all 
            // hardware types) .
            //
            switch (current)
            {
                case HardwareType.DNG:
                    bShowIO = true;
                    break;
                case HardwareType.DNP:
                    bShowIO = true;
                    break;
                case HardwareType.ISA_1CH:
                    bShowIO = true;
                    break;
                case HardwareType.ISA_2CH:
                    bShowIO = true;
                    break;
                default:
                    bShowIO = false;
                    break;
            }
            cbbIO.Enabled = bShowIO;
            cbbInterrupt.Enabled = bShowIO;

            // According with the selection in the Hardware list, we 
            // Enable/Disable the controls for Get/Set the USB device Number.
            //
            btnGetUsbDevNumber.Enabled = ((current == HardwareType.USB_1CH) || (current == HardwareType.USB_2CH)) && btnWrite.Enabled;
            btnSetUsbDevNumber.Enabled = btnGetUsbDevNumber.Enabled;
            txtDevNumber.Enabled = btnGetUsbDevNumber.Enabled;
		}

		private void cbbBaudrates_SelectedIndexChanged(object sender, System.EventArgs e)
		{
			// We save the corresponding Baudrate enumeration 
			// type value for every selected Baudrate from the 
			// list.
			//
			switch(cbbBaudrates.SelectedIndex)
			{
				case 0:
					cbbBaudrates.Tag = Baudrates.BAUD_1M;
					break;
				case 1:
					cbbBaudrates.Tag = Baudrates.BAUD_500K;
					break;
				case 2:
					cbbBaudrates.Tag = Baudrates.BAUD_250K;
					break;				
				case 3:
					cbbBaudrates.Tag = Baudrates.BAUD_125K;
					break;				
				case 4:
					cbbBaudrates.Tag = Baudrates.BAUD_100K;
					break;				
				case 5:
					cbbBaudrates.Tag = Baudrates.BAUD_50K;
					break;				
				case 6:
					cbbBaudrates.Tag = Baudrates.BAUD_20K;					
					break;				
				case 7:					
					cbbBaudrates.Tag = Baudrates.BAUD_10K;
					break;				
				case 8:
					cbbBaudrates.Tag = Baudrates.BAUD_5K;
					break;		
				default:
					cbbBaudrates.Tag = 0;
					break;
			}		
		}

		private void txtID_KeyPress(object sender, System.Windows.Forms.KeyPressEventArgs e)
		{
			char chCheck;

			// We convert the Character to its Upper case equivalent
			//
			chCheck = char.ToUpper(e.KeyChar);

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
			e.Handled = true;			
		}

		private void txtID_Leave(object sender, System.EventArgs e)
		{
			int TextLength;
			uint MaxValue;

			// calculate the text length and Maximum ID value according
			// with the Message Type
			//
			TextLength = (chbExtended.Checked) ? 8 : 3;
			MaxValue = (chbExtended.Checked) ? (uint)0x1FFFFFF : (uint)0x7FF;

			// The Textbox for the ID is represented with 3 characters for 
			// Standard and 8 characters for extended messages.
			// Therefore if the Length of the text is smaller than TextLength,  
			// we add "0"
			//
            while (txtID.Text.Length != TextLength)
                txtID.Text = ("0" + txtID.Text);

			// Because in this example will be sent only Standard messages
			// we check that the ID is not bigger than 0x7FF
			//
            if (Convert.ToUInt32(txtID.Text,16) > MaxValue)
                txtID.Text = string.Format("{0:X" + TextLength.ToString() + "}", MaxValue);				
		}

		private void nudLength_ValueChanged(object sender, System.EventArgs e)
		{
			TextBox CurrentTextBox;

			CurrentTextBox = txtData0;

			// We enable so much TextBox Data fields as the length of the
			// message will be, that is the value of the UpDown control.
			// 
			for(int i=0; i< 8; i++)
			{
				CurrentTextBox.Enabled = (i < nudLength.Value)? true : false;
				if(i < 7)
					CurrentTextBox = (TextBox)this.GetNextControl(CurrentTextBox,true);
			}				
		}

		private void txtData0_Leave(object sender, System.EventArgs e)
		{
			TextBox CurrentTextbox;
			
			// all the Textbox Data fields are represented with 2 characters.
			// Therefore if the Length of the text is smaller than 2, we add
			// a "0"
			//
			if(sender.GetType().Name == "TextBox")
			{				
				CurrentTextbox = (TextBox)sender;
				while(CurrentTextbox.Text.Length != 2)
					CurrentTextbox.Text = ("0" + CurrentTextbox.Text);			
			}				
		}

		private void chbExtended_CheckedChanged(object sender, System.EventArgs e)
		{
			uint uiTemp;

			txtID.MaxLength = (chbExtended.Checked)? 8: 3;
			
			// the only way that the text length can be bigger als MaxLength
			// is when the change is from Extended to Standard message Type.
			// We have to handle this and set an ID not bigger than the Maximum
			// ID value for a Standard Message (0x7FF)
			//
			if(txtID.Text.Length > txtID.MaxLength)
			{
				uiTemp = Convert.ToUInt32(txtID.Text,16);
				txtID.Text = (uiTemp < 0x7FF) ?  string.Format("{0:X3}",uiTemp): "7FF";
			}

			txtID_Leave(this,new EventArgs());			
		}

		private void chbRemote_CheckedChanged(object sender, System.EventArgs e)
		{
			TextBox CurrentTextBox;

			CurrentTextBox = txtData0;

			// We enable so much TextBox Data fields as the length of the
			// message will be, that is the value of the UpDown control.
			// 
			for(int i=0; i< 8; i++)
			{
				CurrentTextBox.Visible = !chbRemote.Checked;
				if(i < 7)
					CurrentTextBox = (TextBox)this.GetNextControl(CurrentTextBox,true);
			}			
		}

        private void rdbStandard_CheckedChanged(object sender, EventArgs e)
        {
            uint uiTemp;

            txtIdFrom.MaxLength = (rdbExtended.Checked) ? 8 : 3;
            txtIdTo.MaxLength = txtIdFrom.MaxLength;

            // the only way that the text length can be bigger als MaxLength
            // is when the change is from Extended to Standard message Type.
            // We have to handle this and set an ID not bigger than the Maximum
            // ID value for a Standard Message (0x7FF)
            //
            if (txtIdFrom.Text.Length > txtIdFrom.MaxLength)
            {
                uiTemp = Convert.ToUInt32(txtIdFrom.Text,16);
                txtIdFrom.Text = (uiTemp < 0x7FF) ? string.Format("{0:X3}", uiTemp) : "7FF";
            }
            if (txtIdTo.Text.Length > txtIdTo.MaxLength)
            {
                uiTemp = Convert.ToUInt32(txtIdTo.Text,16);
                txtIdTo.Text = (uiTemp < 0x7FF) ? string.Format("{0:X3}", uiTemp) : "7FF";
            }
        }

        private void txtIdFrom_Leave(object sender, EventArgs e)
        {
            int TextLength;
            uint MaxValue;
            TextBox IdBox;

            IdBox = sender as TextBox;
            // calculate the text length and Maximum ID value according
            // with the Message Type
            //
            TextLength = (rdbExtended.Checked) ? 8 : 3;
            MaxValue = (rdbExtended.Checked) ? (uint)0x1FFFFFFF : (uint)0x7FF;

            // The Textbox for the ID is represented with 3 characters for 
            // Standard and 8 characters for extended messages.
            // Therefore if the Length of the text is smaller than TextLength,  
            // we add "0"
            //
            while (IdBox.Text.Length != TextLength)
                IdBox.Text = ("0" + IdBox.Text);

            // Because in this example will be sent only Standard messages
            // we check that the ID is not bigger than 0x7FF
            //
            if (Convert.ToUInt32(IdBox.Text,16) > MaxValue)
                IdBox.Text = string.Format("{0:X" + TextLength.ToString() + "}", MaxValue);
        }

		private void txtInfo_DoubleClick(object sender, System.EventArgs e)
		{
			// We clear the Information edit box
			//
			txtInfo.Text = "";		
		}

		private void lstMessages_DoubleClick(object sender, System.EventArgs e)
		{
			lock(this)
			{
				lstMessages.Items.Clear();
				LastMsgsList.Clear();
			}		
		}

		private void tmrRead_Tick(object sender, System.EventArgs e)
		{
            ReadMessage();
		}

		private void btnInfo_Click(object sender, System.EventArgs e)
		{
			string strInfo;
			CANResult Res;

			// We execute the "VersionInfo" function of the PCANLight 
			// using as parameter the Hardware type and a string 
			// variable to get the info.
			// 
            Res = PCANLight.VersionInfo((HardwareType)cbbHws.SelectedIndex, out strInfo);
			strInfo = strInfo.Replace("\n","\r\n");

			// The function was successfully executed
			//			
			if(Res == CANResult.ERR_OK)
				// We show the Version Information
				//
				txtInfo.Text = strInfo;
				// An error occurred.  We show the error.
				//			
			else
				txtInfo.Text  = "Error: " + Res.ToString();			
		}

		private void btnInit_Click(object sender, System.EventArgs e)
		{
			CANResult Res;
            int majorVersion = 0;

            // Check version 2.x Dll is available
            //
			Res = DllMajorVersion((HardwareType)cbbHws.SelectedIndex, out majorVersion);
            if (Res == CANResult.ERR_OK)
            {
                // Sample must ONLY work if a 2.x or later version of the
				// PCAN-Light is installed
				//
                if (majorVersion < 2)
                {
                    MessageBox.Show("DLL 2.x or later are required to run this program" +
                        "\r\nPlease, download lastest DLL version on http://www.peak-system.com or refer to the documentation for more information.",
                        "DLL Version", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                else
                {
                    // According with the active parameters/hardware, we
                    // use one of the two possible "Init" PCANLight functions.
                    // One is for Plug And Play hardware, and the other for
                    // Not P&P.
                    //
                    if (cbbIO.Enabled)
                        // Not P&P Hardware
                        //
                        Res = PCANLight.Init((HardwareType)cbbHws.SelectedIndex,
                            (Baudrates)cbbBaudrates.Tag,
                            (FramesType)cbbMsgType.SelectedIndex,
                            Convert.ToUInt32(cbbIO.Text, 16),
                            Convert.ToByte(cbbInterrupt.Text));
                    else
                        // P&P Hardware
                        //
                        Res = PCANLight.Init((HardwareType)cbbHws.SelectedIndex,
                            (Baudrates)cbbBaudrates.Tag,
                            (FramesType)cbbMsgType.SelectedIndex);

                    // The Hardware was successfully initiated
                    //
                    if (Res == CANResult.ERR_OK)
                    {
                        // We save the hardware type which is currently 
                        // initiated
                        //
                        ActiveHardware = (HardwareType)cbbHws.SelectedIndex;

                        // We start to read from the CAN Queue
                        //
                        tmrRead.Enabled = true;

                        // Set UI enable
                        btnInit.Enabled = !(btnWrite.Enabled = btnSetFilter.Enabled = btnResetFilter.Enabled = btnRelease.Enabled = btnInfo.Enabled = btnDllInfo.Enabled = true);
                        rdbTimer.Enabled = true;
                        rdbEvent.Enabled = true;
                        chbTimeStamp.Enabled = true;
                        cbbHws_SelectedIndexChanged(this, new EventArgs());

                        // We show the information of the configured 
                        // and initiated hardware
                        //
                        txtInfo.Text = "Active Hardware: " + cbbHws.Text;
                        txtInfo.Text += "\r\nBaud Rate: " + cbbBaudrates.Text;
                        txtInfo.Text += "\r\nFrame Type: " + cbbMsgType.Text;
                        // If was a no P&P Hardware, we show additional information
                        //
                        if (cbbIO.Enabled)
                        {
                            txtInfo.Text += "\r\nI/O Addr.: " + cbbIO.Text + "h";
                            txtInfo.Text += "\r\nInterrupt: " + cbbInterrupt.Text;
                        }
                    }
                    // An error occurred.  We show the error.
                    //
                    else
                        txtInfo.Text = "Error: " + Res.ToString();
                }
            }
            else
                txtInfo.Text = "Error: " + Res.ToString();
		}

		private void btnRelease_Click(object sender, System.EventArgs e)
		{
			CANResult Res;

            // We choose Timer method by default
            //
            rdbTimer.Checked = true;

			// We stopt to read from tehe CAN Queue
			//
			tmrRead.Enabled = false;

			// We close the active hardware using the 
			// "Close" function of the PCANLight using 
			// as parameter the Hardware type.
			//
            Res = PCANLight.Close(ActiveHardware);

			// The Hardware was successfully closed
			//
			if(Res == CANResult.ERR_OK)
				txtInfo.Text = "Hardware was successfully Released.\r\n";
				// An error occurred.  We show the error.
				//			
			else
				txtInfo.Text = "Error: " + Res.ToString();
			
			// We set the varibale of active hardware to None
			// and activate/deactivate the corresponding buttons
			//
			ActiveHardware = (HardwareType)(-1);
            btnInit.Enabled = !(btnWrite.Enabled = btnSetFilter.Enabled = btnResetFilter.Enabled = btnRelease.Enabled = btnInfo.Enabled = btnDllInfo.Enabled = false);
            rdbTimer.Enabled = false;
            rdbEvent.Enabled = false;
            chbTimeStamp.Enabled = false;
            cbbHws_SelectedIndexChanged(this, new EventArgs());
		}

		private void btnWrite_Click(object sender, System.EventArgs e)
		{
			TCLightMsg MsgToSend;
			TextBox CurrentTextBox;		
			CANResult Res;

			// We create a TCLightMsg message structure 
			//
			MsgToSend = new TCLightMsg();

			// We configurate the Message.  The ID (max 0x1FF),
			// Length of the Data, Message Type (Standard in 
			// this example) and die data
			//
			MsgToSend.ID = Convert.ToUInt32(txtID.Text,16);
			MsgToSend.Len = Convert.ToByte(nudLength.Value);
			MsgToSend.MsgType = (chbExtended.Checked) ? MsgTypes.MSGTYPE_EXTENDED : MsgTypes.MSGTYPE_STANDARD;
			// If a remote frame will be sent, the data bytes are not important.
			//
			if(chbRemote.Checked)
				MsgToSend.MsgType |= MsgTypes.MSGTYPE_RTR;
			else
			{
				// We get so much data as the Len of the message
				//
				CurrentTextBox = txtData0;
				for(int i=0; i < MsgToSend.Len; i++)
				{
					MsgToSend.Data[i] = Convert.ToByte(CurrentTextBox.Text,16);
					if(i < 7)
						CurrentTextBox = (TextBox)this.GetNextControl(CurrentTextBox,true);
				}
			}

			// The message is sent to the configured hardware
			//
            Res = PCANLight.Write(ActiveHardware, MsgToSend);
			
			// The Hardware was successfully sent
			//
			if(Res == CANResult.ERR_OK)
				txtInfo.Text = "Message was successfully SENT.\r\n";
				// An error occurred.  We show the error.
				//			
			else
				txtInfo.Text = "Error: " + Res.ToString();		
		}

		private void btnClose_Click(object sender, System.EventArgs e)
		{
			// We terminate the application
			//
			Close();
		}

        private void btnSetFilter_Click(object sender, EventArgs e)
        {
            uint FromID, ToID;
            CANResult Res;

            // The range IDs is read
            //
            FromID = Convert.ToUInt32(txtIdFrom.Text,16);
            ToID = Convert.ToUInt32(txtIdTo.Text,16);
            
            // The desired Filter is set on the configured Hardware
            //
            Res = PCANLight.MsgFilter(ActiveHardware, FromID, ToID, (rdbStandard.Checked) ? MsgTypes.MSGTYPE_STANDARD : MsgTypes.MSGTYPE_EXTENDED);

            // The Filter was successfully set
            //
            if (Res == CANResult.ERR_OK)
                txtInfo.Text = "Filter was successfully SET.\r\n";
            // An error occurred.  We show the error.
            //			
            else
                txtInfo.Text = "Error: " + Res.ToString();		
        }

        private void btnResetFilter_Click(object sender, EventArgs e)
        {
            CANResult Res;

            // The current Filter on the configured Hardware is reset 
            //
            Res = PCANLight.ResetFilter(ActiveHardware);

            // The Filter was successfully reset
            //
            if (Res == CANResult.ERR_OK)
                txtInfo.Text = "Filter was successfully RESET.\r\n";
            // An error occurred.  We show the error.
            //			
            else
                txtInfo.Text = "Error: " + Res.ToString();		
        }

        private void btnGetUsbDevNumber_Click(object sender, EventArgs e)
        {
            uint iDevNum;
            CANResult Res;

            // The USB Device Number will asked 
            //
            Res = PCANLight.GetUSBDeviceNr((HardwareType)cbbHws.SelectedIndex, out iDevNum);

            // The Device number was got successfully
            //
            if (Res == CANResult.ERR_OK)
                MessageBox.Show("USB Device Number is: " + iDevNum, "GetUSBDevNr");
            // An error occurred.  We show the error.
            //			
            else
                MessageBox.Show("Get USB Device Number failed: " + Res.ToString(), "GetUSBDevNr"); 	
        }

        private void btnSetUsbDevNumber_Click(object sender, EventArgs e)
        {
            CANResult Res;

            // The USB Device Number will set 
            //
            Res = PCANLight.SetUSBDeviceNr((HardwareType)cbbHws.SelectedIndex, Convert.ToUInt32(txtDevNumber.Text));

            // The Device number was set successfully
            //
            if (Res == CANResult.ERR_OK)
                MessageBox.Show("USB Device Number was set", "SetUSBDevNr");
            // An error occurred.  We show the error.
            //
            else
                MessageBox.Show("Set USB Device Number failed: " + Res.ToString(), "SetUSBDevNr");	
        }

        private void btnDllInfo_Click(object sender, EventArgs e)
        {
            String strInfo = "";
            CANResult Res;

            // We execute the "VersionInfo" function of the PCANLight 
            // using as parameter the Hardware type and a string 
            // variable to get the info.
            // 
            Res = PCANLight.DllVersionInfo((HardwareType)cbbHws.SelectedIndex, out strInfo);

            // The function was successfully executed
            //			
            if (Res == CANResult.ERR_OK)
            {
                // We show the Version Information
                //
                strInfo = strInfo.Replace("\n", "\r\n");
                strInfo = cbbHws.SelectedItem.ToString() + " Dll Version: " + strInfo;
                txtInfo.Text = strInfo;
            }
            // An error occurred.  We show the error.
            //			
            else
                txtInfo.Text = "Error: " + String.Format("{0:X4}", (int)Res);
        }

        private void rdbTimer_CheckedChanged(object sender, EventArgs e)
        {
            if(rdbTimer.Checked)
		    {
			    // Abort Read Thread if it exists
			    //
			    if(ReadThread != null)
			    {
				    ReadThread.Abort();
				    ReadThread.Join();
				    ReadThread = null;
			    }

			    // Enable Timer
			    //
			    tmrRead.Enabled = true;
		    }
		    else
		    {
			    // Disable Timer
			    //
			    tmrRead.Enabled = false;
			    // Create and start the tread to read CAN Message using SetRcvEvent()
			    ThreadStart threadDelegate = new ThreadStart(this.CANReadThreadFunc);
			    ReadThread = new Thread(threadDelegate);
			    ReadThread.Start();
		    }
        }

        private void chbTimeStamp_CheckedChanged(object sender, EventArgs e)
        {
            if (chbTimeStamp.Checked)
            {
                // Add Rcv Time column
                //
                if (!lstMessages.Columns.Contains(clhRcvTime))
                    lstMessages.Columns.Add(clhRcvTime);
            }
            else
            {
                // Remove Rcv Time column
                //
                if (lstMessages.Columns.Contains(clhRcvTime))
                    lstMessages.Columns.Remove(clhRcvTime);
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if(btnRelease.Enabled)
				btnRelease_Click(this,new EventArgs());

			// If we are reading, we stop to read
			//
			tmrRead.Enabled = false;
        }

        private void txtDevNumber_Leave(object sender, EventArgs e)
        {
            if(txtDevNumber.Text == "")
                txtDevNumber.Text = "0";
            if (Convert.ToUInt64(txtDevNumber.Text) > uint.MaxValue)
                txtDevNumber.Text = uint.MaxValue.ToString();
        }

        private void txtDevNumber_KeyPress(object sender, KeyPressEventArgs e)
        {
            // The Key is the Delete (Backspace) Key
            //
            if (e.KeyChar == 8)
                return;
            // The Key is a number between 0-9
            //
            if ((e.KeyChar > 47) && (e.KeyChar < 58))
                return;

            // Is neither a number nor a character between A(a) and F(f)
            //
            e.Handled = true;	
        }
	}
}
