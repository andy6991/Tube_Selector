#pragma once
#include "afxwin.h"
//#include "Tube_SelectorDlg.h"


// CTest dialog

class CTest : public CDialog
{
	DECLARE_DYNAMIC(CTest)

public:
	CTest(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTest();

// Dialog Data
	enum { IDD = HIDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


	DECLARE_MESSAGE_MAP()
public:
	CString csTemp;
	int iRodNum;
	CButton m_select;
	CEdit m_rod_num;
	afx_msg void OnBnClickedButtonSelect();
};
