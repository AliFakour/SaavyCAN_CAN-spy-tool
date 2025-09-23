// ICDILightDlg.h : header file
//

#pragma once
#include "PCANLight.h"
#include "afxwin.h"
#include "afxcmn.h"
#include <Math.h>

// Constant values to make the code more comprehensible
// to add and read items from the List view
//
#define MSG_TYPE		0
#define MSG_ID			1
#define MSG_LENGTH		2
#define MSG_DATA		3
#define MSG_COUNT		4
#define MSG_TIME		5

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

// CICDILightDlg dialog
class CICDILightDlg : public CDialog
{
// Construction
public:
	CICDILightDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog data
	enum { IDD = IDD_ICDILIGHT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map function
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	// Variables to store the current CAN Light instance
	//
	PCANLight *ActiveCANLight;
	Baudrates CurrBaud;

	// Variables for reading with event
    //
	HANDLE hThread;

	// Timer identifier
	//
	UINT_PTR tmrRead;

    // CAN messages array. Store the message status for its display
    //
    CPtrList *LastMsgsList;

	CString IntToStr(int iValue);
	CString IntToHex(int iValue, short iDigits);
	void InitializeControls(void);
	void CheckHexEditBox(CString* txtData);
	int AddLVItem(CString Caption);
	void SetTimerRead(bool bEnable);
    void ModifyMsgEntry(MessageStatus LastMsg,TPCANMsg NewMsg, TPCANTimestamp MyTimeStamp);
    void InsertMsgEntry(TPCANMsg NewMsg, TPCANTimestamp MyTimeStamp);
    void ProcessMessage(TPCANMsg MyMsg, TPCANTimestamp MyTimeStamp);
	static DWORD WINAPI CallCANReadThreadFunc(LPVOID lpParam);
	DWORD WINAPI CANReadThreadFunc(LPVOID lpParam);
	void ReadingModeChanged();
	void ReadMessage();
	DWORD HexTextToInt(CString ToConvert);

public:
	CComboBox cbbHws;
	CButton btnInfo;
	CButton btnDllInfo;
	CButton btnInit;
	CButton btnRelease;
	CButton btnWrite;
	CButton btnClose;
	CButton btnSetFilter;
	CButton btnResetFilter;
	CComboBox cbbBaudrates;
	CComboBox cbbMsgType;
	CComboBox cbbIO;
	CComboBox cbbInterrupt;
	CSpinButtonCtrl nudLength;
	CString txtID;
	CString txtLength;
	CString txtData0;
	CString txtData1;
	CString txtData2;
	CString txtData3;
	CString txtData4;
	CString txtData5;
	CString txtData6;
	CString txtData7;
	BOOL chbExtended;
	BOOL chbRemote;
	CListCtrl lstMessages;
	CString txtInfo;
	CString txtIdFrom;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnCbnSelchangeCbbhws();
	afx_msg void OnCbnSelchangeCbbbaudrates();
	afx_msg void OnEnKillfocusTxtid();
	afx_msg void OnEnKillfocusTxtdata0();
	afx_msg void OnEnKillfocusTxtdata1();
	afx_msg void OnEnKillfocusTxtdata2();
	afx_msg void OnEnKillfocusTxtdata3();
	afx_msg void OnEnKillfocusTxtdata4();
	afx_msg void OnEnKillfocusTxtdata5();
	afx_msg void OnEnKillfocusTxtdata6();
	afx_msg void OnEnKillfocusTxtdata7();
	afx_msg void OnDeltaposNudlength(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedChbextended();
	afx_msg void OnBnClickedChbremote();
	afx_msg void OnClose();
	afx_msg void OnNMDblclkLstmessages(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtninfo();
	afx_msg void OnBnClickedBtninit();
	afx_msg void OnBnClickedBtnrelease();
	afx_msg void OnBnClickedBtnwrite();
	afx_msg void OnBnClickedBtnclose();
	CString txtIdTo;
	afx_msg void OnBnClickedRdbstandard();
	CButton rdbStandard;
	CButton rdbExtended;
	afx_msg void OnBnClickedRdbextended();
	afx_msg void OnEnKillfocusTxtidfrom();
	afx_msg void OnEnKillfocusTxtidto();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnsetfilter();
	afx_msg void OnBnClickedBtnresetfilter();
	CButton btnGetDeviceNumber;
	CButton btnSetDeviceNumber;
	CString txtDeviceNumber;
	afx_msg void OnDeltaposNuddevnumber(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtndevget();
	afx_msg void OnBnClickedBtndevset();
	afx_msg void OnBnClickedRdbtimer();
	afx_msg void OnBnClickedRdbevent();
	afx_msg void OnBnClickedChbtimestamp();
	afx_msg void OnBnClickedBtndllinfo();
	CButton chbTimeStamp;
	CButton rdbTimer;
	CButton rdbEvent;
	afx_msg void OnEnKillfocusTxtdevnumber();
};
