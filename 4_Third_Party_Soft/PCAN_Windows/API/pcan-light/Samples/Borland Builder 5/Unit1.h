//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "PCANLight.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------

/// Message Status structure used to show CAN Messages
/// in a ListView
//
typedef struct ListViewMessageStatus
{
    private:
        TPCANMsg Msg;
        int iIndex;

    public:
        ListViewMessageStatus(TPCANMsg *CanMsg,int Index)
        {
            Msg = *CanMsg;
            iIndex = Index;
        }

        TPCANMsg CANMessage(void)
        {
            return Msg;
        }

        int Position(void)
        {
            return iIndex;
        }
}MessageStatus;

typedef void (__closure *ProcMsgRead)();

class TCANReadThread: public TThread
{
    private:
        PCANLight *objCANLight;
        ProcMsgRead ReadMessage;

    protected:
        // Run function for the thread
        //
        void __fastcall  Execute();
        // Function Pointer for CAN reading
        //
        void __fastcall DoReadMessage();

    public:
        __fastcall TCANReadThread(PCANLight *CANLightObj, ProcMsgRead ReadMsgFunction);
        __fastcall ~TCANReadThread();
};

class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TComboBox *cbbHws;
    TButton *btnInfo;
    TButton *btnInit;
    TButton *btnRelease;
    TComboBox *cbbBaudrates;
    TComboBox *cbbMsgType;
    TComboBox *cbbIO;
    TComboBox *cbbInterrupt;
    TButton *btnGetDeviceNumber;
    TButton *btnSetDeviceNumber;
    TEdit *ediDeviceNumber;
    TButton *btnDllInfo;
    TGroupBox *GroupBox2;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label8;
    TEdit *txtID;
    TUpDown *nudLength;
    TEdit *txtLength;
    TEdit *txtData0;
    TEdit *txtData1;
    TEdit *txtData2;
    TEdit *txtData3;
    TEdit *txtData4;
    TEdit *txtData5;
    TEdit *txtData6;
    TEdit *txtData7;
    TCheckBox *chbExtended;
    TCheckBox *chbRemote;
    TButton *btnWrite;
    TGroupBox *GroupBox5;
    TLabel *Label9;
    TLabel *Label10;
    TRadioButton *rdbStandard;
    TRadioButton *rdbExtended;
    TEdit *txtIdFrom;
    TEdit *txtIdTo;
    TButton *btnSetFilter;
    TButton *btnResetFilter;
    TGroupBox *GroupBox3;
    TLabel *labelReadMethod;
    TListView *lstMessages;
    TCheckBox *chbTimeStamp;
    TRadioButton *rdbTimer;
    TRadioButton *rdbEvent;
    TGroupBox *GroupBox4;
    TMemo *txtInfo;
    TButton *btnClose;
    TTimer *tmrRead;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall cbbHwsChange(TObject *Sender);
    void __fastcall cbbBaudratesChange(TObject *Sender);
    void __fastcall txtIDKeyPress(TObject *Sender, char &Key);
    void __fastcall txtIDExit(TObject *Sender);
    void __fastcall nudLengthClick(TObject *Sender, TUDBtnType Button);
    void __fastcall txtData0Exit(TObject *Sender);
    void __fastcall chbExtendedClick(TObject *Sender);
    void __fastcall chbRemoteClick(TObject *Sender);
    void __fastcall txtIdFromExit(TObject *Sender);
    void __fastcall btnSetFilterClick(TObject *Sender);
    void __fastcall btnResetFilterClick(TObject *Sender);
    void __fastcall btnGetDeviceNumberClick(TObject *Sender);
    void __fastcall btnSetDeviceNumberClick(TObject *Sender);
    void __fastcall rdbTimerClick(TObject *Sender);
    void __fastcall chbTimeStampClick(TObject *Sender);
    void __fastcall btnInitClick(TObject *Sender);
    void __fastcall btnReleaseClick(TObject *Sender);
    void __fastcall btnInfoClick(TObject *Sender);
    void __fastcall btnDllInfoClick(TObject *Sender);
    void __fastcall btnWriteClick(TObject *Sender);
    void __fastcall rdbStandardClick(TObject *Sender);
    void __fastcall lstMessagesDblClick(TObject *Sender);
    void __fastcall txtInfoDblClick(TObject *Sender);
    void __fastcall tmrReadTimer(TObject *Sender);
    void __fastcall btnCloseClick(TObject *Sender);
    void __fastcall ediDeviceNumberKeyPress(TObject *Sender, char &Key);
    void __fastcall ediDeviceNumberExit(TObject *Sender);
private:
	// Variables to store the current CAN Light instance
	//
	PCANLight *ActiveCANLight;
	Baudrates CurrBaud;

    // Variables for reading with event
    //
	TCANReadThread *hThread;

    // CAN messages Array. Store the Message Status for its display
    //
    TList *LastMsgsList;

    void ModifyMsgEntry(MessageStatus LastMsg,TPCANMsg NewMsg, TPCANTimestamp RcvTime);
    void InsertMsgEntry(TPCANMsg NewMsg, TPCANTimestamp RcvTime);
    void ProcessMessage(TPCANMsg MyMsg, TPCANTimestamp RcvTime);
    void ReadingModeChanged();
    void ReadMessage();


public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};

//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
