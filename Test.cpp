// Test.cpp : implementation file
//

#include "stdafx.h"
#include "Tube_Selector.h"
#include "Test.h"
#include "Tube_SelectorDlg.h"
#include ".\test.h"


// CTest dialog

IMPLEMENT_DYNAMIC(CTest, CDialog)
CTest::CTest(CWnd* pParent /*=NULL*/)
	: CDialog(CTest::IDD, pParent)
{
}

CTest::~CTest()
{
}


void CTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_SELECT, m_select);
	DDX_Control(pDX, IDC_EDIT_ROD_NUM, m_rod_num);
}


BEGIN_MESSAGE_MAP(CTest, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SELECT, OnBnClickedButtonSelect)
END_MESSAGE_MAP()


// CTest message handlers

void CTest::OnBnClickedButtonSelect()
{
	CTube_SelectorDlg dlg;
  m_rod_num.GetWindowText(csTemp);
	iRodNum = (int)atoi(csTemp);
	csTemp = dlg.GetDraw(iRodNum);

	CDC* dc;
	dc=GetDC();
	dc->SelectStockObject(LTGRAY_BRUSH);
	dc->Ellipse(250,250,40,40);
	dc->SelectStockObject(WHITE_BRUSH);
	dc->Ellipse(220,220,70,70);

	dc->MoveTo(5,50);
	dc->LineTo(50,50);
	dc->LineTo(100,100);

	dc->MoveTo(40,140);
	dc->LineTo(40,290);
	dc->MoveTo(250,140);
	dc->LineTo(250,290);
	dc->MoveTo(40,280);
	dc->LineTo(250,280);
	dc->TextOut(10,30,"fignya moya!!!!");
	dc->TextOut(130,260,"zczcz");
}
