// Tube_SelectorDlg.h : header file
//

#pragma once


#include "MMTube_Selector.h"
#include <afxwin.h>
#include <stdio.h>
#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "HtmlHelp.h"
#include <Math.h>
#include "Test.h"
//#pragma comment(lib,"hhctrl.lib") 
#pragma comment(lib,"htmlhelp.lib")


//
const int ID_TIMER_MODEL = 100001;		//	ID таймера работы системы
const int DELAY_TIMER_MODEL = 50;			//	задержка таймера работы системы
//
//
const int ID_TIMER_DISPLAY = 100002;		//	ID таймера индикации
const int DELAY_TIMER_DISPLAY = 50;			//	задержка таймера индикации
//

// CTube_SelectorDlg dialog
class CTube_SelectorDlg : public CDialog
{
// Construction
public:
	////CToolTipCtrl* m_pTips;	//////////////////////////////////////////////////
	CTube_SelectorDlg(CWnd* pParent = NULL);	// standard constructor
//	~CTube_SelectorDlg();	//////////////////////////////////////////////////////////////////////////


// Dialog Data
	enum { IDD = IDD_TUBE_SELECTOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	CTest NewWindow;
		LPOFSTRUCT lalala;
		CToolBar ToolBar2;
		int iTemp, jTemp;
		CString csTemp, csTemp1, csTemp2;
    CString CSLine[_MAX_LINE_LEN], CSLine2[_MAX_LINE_LEN];
		FILE *stream;
		char Line[_MAX_LINE_LEN];
		fpos_t filepos1, filepos2;
		int StringLenght;
		int pos1;
		char HelpMassive[_MAX_LINE_LEN];
		char HelpMassive1[_MAX_LINE_LEN];
		bool b_eof;							//	проверка на наличие символа EOF
		bool b_List1;
		int pos2;
		char sym[2];
//		int StringLenght;

		char chCurDir1[_MAX_LINE_LEN];
		char chCurDir2[_MAX_LINE_LEN];

		float GivenArea[_ROD_QUANTITY];
		float NesMoment[_ROD_QUANTITY];

	TTube_SelectorIn Tube_SelectorInData;
	TTube_SelectorOut Tube_SelectorOutData;
	TTube_SelectorDebug Tube_SelectorDebugData;
	CTube_Selector Tube_Selector;

public:

	// Generated message map functions

	virtual BOOL OnInitDialog();


	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL PreTranslateMessage(MSG *pMsg);

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

    void OnFileOpen();
	void OnFileSaveAs();
	void OnFileClose();
	void OnFileSave();
	void OnAboutProgram();
	void OnHelp();

	void 	SelectFerma();
	void OpenFermaFile();
	void SaveFermaFile();
	void SaveAsFermaFile();
	void CloseFermaFile();
	void FermaHelp();

	afx_msg void OnButtonOpen();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonClose();
	afx_msg void OnButtonSelect();
	afx_msg void OnButtonHelp();
	afx_msg void OnButtonDraw();


	afx_msg void ErrorExit(char *string);

	DECLARE_MESSAGE_MAP()
public:
	CString GetDraw(int iRod);
	CButton m_select;
	CListCtrl m_ListCtrl1;
	CListCtrl m_ListCtrl2;
	afx_msg void OnBnClickedButtonSelect();
	CEdit m_rod_number;
	CButton m_add;
	CButton m_substract;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonSubstract();
	CEdit m_file_name;
	CEdit m_sortament_file_name;
	CEdit m_standart;
	CEdit m_lambda;
	HACCEL ha;
};
