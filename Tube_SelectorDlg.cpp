// Tube_SelectorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tube_Selector.h"
#include "Tube_SelectorDlg.h"
#include ".\tube_selectordlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTube_SelectorDlg dialog



CTube_SelectorDlg::CTube_SelectorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTube_SelectorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	////m_pTips=NULL;	//////////////////////////////////////////////////////////////////////////
}

//CTube_SelectorDlg::~CTube_SelectorDlg()	/////////////////////////////////////////////////
//{
//	if (m_pTips!=NULL) delete m_pTips;
//}


void CTube_SelectorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_SELECT, m_select);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl1);
	DDX_Control(pDX, IDC_LIST2, m_ListCtrl2);
	DDX_Control(pDX, IDC_EDIT_ROD_NUMBER, m_rod_number);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_add);
	DDX_Control(pDX, IDC_BUTTON_SUBSTRACT, m_substract);
	DDX_Control(pDX, IDC_EDIT_FILE_NAME, m_file_name);
	DDX_Control(pDX, IDC_EDIT_SORTAMENT_FILE_NAME, m_sortament_file_name);
	DDX_Control(pDX, IDC_EDIT_STANDART, m_standart);
	DDX_Control(pDX, IDC_EDIT_LAMBDA, m_lambda);
}

BEGIN_MESSAGE_MAP(CTube_SelectorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)

	ON_COMMAND(ID_FILE_OPEN32771, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE32772, OnFileSaveAs)
	ON_COMMAND(ID_FILE_CLOSE32774, OnFileClose)
	ON_COMMAND(ID_FILE_SAVE32775, OnFileSave)
	ON_COMMAND(ID_HELP_ABOUTPROGRAM, OnAboutProgram)
	ON_COMMAND(ID_HELP_INFORMATION, OnHelp)

	ON_COMMAND(ID_BUTTON32779, OnButtonOpen)
	ON_COMMAND(ID_BUTTON32780, OnButtonSave)
	ON_COMMAND(ID_BUTTON32781, OnButtonClose)
	ON_COMMAND(ID_BUTTON32782, OnButtonSelect)
	ON_COMMAND(ID_BUTTON32785, OnButtonHelp)
	ON_COMMAND(ID_BUTTON32789, OnButtonDraw)

	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_SELECT, OnBnClickedButtonSelect)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SUBSTRACT, OnBnClickedButtonSubstract)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CTube_SelectorDlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// CTube_SelectorDlg message handlers

BOOL CTube_SelectorDlg::OnInitDialog()
{

	CDialog::OnInitDialog();


	ha = LoadAccelerators( AfxGetResourceHandle(),
		MAKEINTRESOURCE( IDR_ACCELERATOR1 ) );

	////if (!m_pTips)	/////////////////////////////////////////////////////////////////////////
	////{
	////	m_pTips =new CToolTipCtrl;
	////	m_pTips->Create(this);
	////	m_pTips->AddTool(&m_add,"Button 1");
	////	m_pTips->AddTool(&m_substract,"Button 2");
	////	m_pTips->Activate(TRUE); 
	////}

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

			ToolBar2.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS |
		CBRS_FLYBY | CBRS_BORDER_BOTTOM);
	ToolBar2.LoadToolBar(IDR_TOOLBAR2);

	CRect rcClientStart;
	CRect rcClientNow;
	GetClientRect(rcClientStart);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST,
		0, reposQuery, rcClientNow);
	CPoint ptOffset(rcClientNow.left - rcClientStart.left,
		rcClientNow.top - rcClientStart.top);

	CRect rcChild;
	CWnd* pwndChild = GetWindow(GW_CHILD);
	while (pwndChild)
	{
		pwndChild->GetWindowRect(rcChild);
		ScreenToClient(rcChild);
		rcChild.OffsetRect(ptOffset);
		pwndChild->MoveWindow(rcChild, FALSE);
		pwndChild = pwndChild->GetNextWindow();
	}

	CRect rcWindow;
	GetWindowRect(rcWindow);
	rcWindow.right += rcClientStart.Width() - rcClientNow.Width();
	rcWindow.bottom += rcClientStart.Height() - rcClientNow.Height();
	MoveWindow(rcWindow, FALSE);	

	// Положение панелей
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

  int	iCountOfTable = 0;
	int iCountOfColumn = 0;
	int iCountOfRec = 0;
	int iPrePosition = 0;

		//	установка неактивного состояния кнопок панели управления
	ToolBar2.SetButtonStyle(1, TBBS_DISABLED);
	ToolBar2.SetButtonStyle(2, TBBS_DISABLED);
	ToolBar2.SetButtonStyle(3, TBBS_DISABLED);
	ToolBar2.SetButtonStyle(4, TBBS_DISABLED);


	//	Инициализация модели
	Tube_Selector.Init();
	Tube_Selector.SetTimeStep(DELAY_TIMER_MODEL);

	
	//	Запуск таймера
	SetTimer(ID_TIMER_MODEL, DELAY_TIMER_MODEL, NULL);
	SetTimer(ID_TIMER_DISPLAY, DELAY_TIMER_DISPLAY, NULL);

	memset(&Tube_SelectorInData, 0, sizeof(TTube_SelectorIn));
	memset(&Tube_SelectorOutData, 0, sizeof(TTube_SelectorOut));
	memset(&Tube_SelectorDebugData, 0, sizeof(TTube_SelectorDebug));
	csTemp.Format("");
	csTemp1.Format("");
	filepos1 = 0;
	filepos2 = 0;
	b_eof = false;
	memset(&Line, '0', sizeof(Line));
	for (iTemp = 0; iTemp < 255; iTemp++)	{CSLine[iTemp].Format("");}
	for (iTemp = 0; iTemp < 255; iTemp++)	{CSLine2[iTemp].Format("");}
	memset(&NesMoment, 0, sizeof(NesMoment)*_ROD_QUANTITY);
	memset(&GivenArea, 0, sizeof(GivenArea) * _ROD_QUANTITY);
	StringLenght = 0;
	pos1 = 0;
	pos2 = 0;
	iTemp = 0; jTemp = 0;
	memset(&HelpMassive, '0', sizeof(HelpMassive));
	memset(&HelpMassive1, '0', sizeof(HelpMassive1));
	b_List1 = 0;
	StringLenght = 0;
	memset(chCurDir1,0,_MAX_LINE_LEN);
	memset(chCurDir2,0,_MAX_LINE_LEN);


	NewWindow.Create(HIDD_DIALOG1, this);

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTube_SelectorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

//--------------------------------------------------------------------------------------------
//	DESTROY WINDOW
//--------------------------------------------------------------------------------------------
void CTube_SelectorDlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
		////if (m_pTips!=NULL) delete m_pTips;	//////////////////////////////////////////
	//	CDialog::OnDestroy();

	CDialog::OnDestroy();

	//	Остановка таймера модели
	KillTimer(ID_TIMER_DISPLAY);
	KillTimer(ID_TIMER_MODEL);
}

void CTube_SelectorDlg::OnPaint() 
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
HCURSOR CTube_SelectorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CTube_SelectorDlg::PreTranslateMessage(MSG* pMsg) 
{
	////if (NULL != m_pTips)	///////////////////////////////////////////////
	////	m_pTips->RelayEvent(pMsg);	

	// TODO: Add your specialized code here and/or call the base class
	if ( TranslateAccelerator( m_hWnd, ha, pMsg ) ) return TRUE;


	return CDialog::PreTranslateMessage(pMsg);
}


//--------------------------------------------------------------------------------------------
//	ТАЙМЕР
//--------------------------------------------------------------------------------------------

void CTube_SelectorDlg::OnTimer(UINT nIDEvent)
{
	switch(nIDEvent)
	{
	case ID_TIMER_MODEL:
		{
			if(!b_List1)
			{
				CRect rect;
				m_ListCtrl1.GetClientRect(&rect);
				int nColInterval = rect.Width()/7;    // состоит из 3-х столбцов

				m_ListCtrl1.InsertColumn(0, _T("№"), LVCFMT_LEFT, nColInterval);						
				m_ListCtrl1.InsertColumn(1, _T("Площади"), LVCFMT_LEFT, 5*nColInterval/2);						
				m_ListCtrl1.InsertColumn(2, _T("Мом.Инерции"), LVCFMT_LEFT, 3.5*nColInterval);

				rect = 0;
				m_ListCtrl2.GetClientRect(&rect);
				nColInterval = rect.Width()/4;    // состоит из 4-и столбцов

				m_ListCtrl2.InsertColumn(0, _T("№"), LVCFMT_LEFT, 0.5*nColInterval);    
				m_ListCtrl2.InsertColumn(1, _T("Размеры"), LVCFMT_LEFT, 1.2*nColInterval);   
				m_ListCtrl2.InsertColumn(2, _T("Площади"), LVCFMT_LEFT, 1.1*nColInterval);   
				m_ListCtrl2.InsertColumn(3, _T("М. инерции"), LVCFMT_LEFT, 1.2*nColInterval);

				b_List1 = true;
			}
		}
	case ID_TIMER_DISPLAY:
		{
		}
		CDialog::OnTimer(nIDEvent);
	}
}

//--------------------------------------------------------------------------------------------
//	Открытие файла
//--------------------------------------------------------------------------------------------
void CTube_SelectorDlg::OnFileOpen()
{
	OpenFermaFile();
}
//--------------------------------------------------------------------------------------------
//	Сохранение файла как новый проект
//--------------------------------------------------------------------------------------------
void CTube_SelectorDlg::OnFileSaveAs()
{
	SaveAsFermaFile();
}
//////--------------------------------------------------------------------------------------------
//////	Сохранить файл под текущим именем
//////--------------------------------------------------------------------------------------------
void CTube_SelectorDlg::OnFileSave()
{
	SaveFermaFile();
}
//--------------------------------------------------------------------------------------------
//	Подбор стержней
//--------------------------------------------------------------------------------------------
void CTube_SelectorDlg::OnBnClickedButtonSelect()
{
	SelectFerma();
}
//--------------------------------------------------------------------------------------------
//	Увеличение площади стержня
//--------------------------------------------------------------------------------------------
void CTube_SelectorDlg::OnBnClickedButtonAdd()
{
	m_rod_number.GetWindowText(csTemp);
	Tube_SelectorInData.i_Rod_Num = (int)atof(csTemp)-1;

	Tube_Selector.NewSelection(Tube_SelectorInData.i_Rod_Num);
	Tube_SelectorOutData = Tube_Selector.GetOutputData();

	if(strcmp(Tube_SelectorOutData.ParamMassiveOut[Tube_SelectorInData.i_Rod_Num], "") == 0) 
	{
		m_ListCtrl2.SetItemText(Tube_SelectorInData.i_Rod_Num, 1, "#####");
		m_ListCtrl2.SetItemText(Tube_SelectorInData.i_Rod_Num, 2, "#####");
		m_ListCtrl2.SetItemText(Tube_SelectorInData.i_Rod_Num, 3, "#####");
	}
	else 
	{
		m_ListCtrl2.SetItemText(Tube_SelectorInData.i_Rod_Num, 1, Tube_SelectorOutData.ParamMassiveOut[Tube_SelectorInData.i_Rod_Num]);
		csTemp.Format("%f", Tube_SelectorOutData.AreaOut[Tube_SelectorInData.i_Rod_Num]);
		m_ListCtrl2.SetItemText(Tube_SelectorInData.i_Rod_Num, 2, csTemp);
		csTemp.Format("%f", Tube_SelectorOutData.MomentOut[Tube_SelectorInData.i_Rod_Num]);
		m_ListCtrl2.SetItemText(Tube_SelectorInData.i_Rod_Num, 3, csTemp);
	}
}
//--------------------------------------------------------------------------------------------
//	Уменьшение площади стержня
//--------------------------------------------------------------------------------------------
void CTube_SelectorDlg::OnBnClickedButtonSubstract()
{
	m_rod_number.GetWindowText(csTemp);
	Tube_SelectorInData.i_Rod_Num = (int)atof(csTemp)-1;

	Tube_Selector.SubstractSelection(Tube_SelectorInData.i_Rod_Num);
	Tube_SelectorOutData = Tube_Selector.GetOutputData();

//		m_ListCtrl2.SetItemText(iTemp, 1, Tube_SelectorOutData.ParamMassiveOut[Tube_SelectorInData.i_Rod_Num]);
	if(strcmp(Tube_SelectorOutData.ParamMassiveOut[Tube_SelectorInData.i_Rod_Num], "") == 0) 
	{
		m_ListCtrl2.SetItemText(Tube_SelectorInData.i_Rod_Num, 1, "#####");
		m_ListCtrl2.SetItemText(Tube_SelectorInData.i_Rod_Num, 2, "#####");
		m_ListCtrl2.SetItemText(Tube_SelectorInData.i_Rod_Num, 3, "#####");
	}
	else 
	{
		m_ListCtrl2.SetItemText(Tube_SelectorInData.i_Rod_Num, 1, Tube_SelectorOutData.ParamMassiveOut[Tube_SelectorInData.i_Rod_Num]);
		csTemp.Format("%f", Tube_SelectorOutData.AreaOut[Tube_SelectorInData.i_Rod_Num]);
		m_ListCtrl2.SetItemText(Tube_SelectorInData.i_Rod_Num, 2, csTemp);
		csTemp.Format("%f", Tube_SelectorOutData.MomentOut[Tube_SelectorInData.i_Rod_Num]);
		m_ListCtrl2.SetItemText(Tube_SelectorInData.i_Rod_Num, 3, csTemp);
	}
}

//--------------------------------------------------------------------------------------------
// Закрытие файла
//--------------------------------------------------------------------------------------------
void CTube_SelectorDlg::OnFileClose()
{
	CloseFermaFile();
}
//--------------------------------------------------------------------------------------------
//	Открытие файла
//--------------------------------------------------------------------------------------------
void CTube_SelectorDlg::OnButtonOpen()
{
	OpenFermaFile();
}
//--------------------------------------------------------------------------------------------
//	Сохранение файла под текущим именем
//--------------------------------------------------------------------------------------------
void CTube_SelectorDlg::OnButtonSave()
{
	SaveFermaFile();
}
//--------------------------------------------------------------------------------------------
//	Закрытие файла
//--------------------------------------------------------------------------------------------
void CTube_SelectorDlg::OnButtonClose()
{
	CloseFermaFile();
}
//--------------------------------------------------------------------------------------------
//	Подбор стержней
//--------------------------------------------------------------------------------------------
void CTube_SelectorDlg::OnButtonSelect() 
{
	SelectFerma();
}
//--------------------------------------------------------------------------------------------
//	Вызов справки
//--------------------------------------------------------------------------------------------
void CTube_SelectorDlg::OnButtonHelp()
{
	WinHelp(0L, HELP_CONTENTS);
}
//--------------------------------------------------------------------------------------------
//	О программе
//--------------------------------------------------------------------------------------------
void CTube_SelectorDlg::OnAboutProgram()
{
    CDialog dlg(IDD_ABOUTBOX);
    dlg.DoModal();
}
//--------------------------------------------------------------------------------------------
//	Вызов справки
//--------------------------------------------------------------------------------------------
void CTube_SelectorDlg::OnHelp()
{
	WinHelp(0L, HELP_CONTENTS);
}
//--------------------------------------------------------------------------------------------
//	Получение данных из диалога
//--------------------------------------------------------------------------------------------
CString CTube_SelectorDlg::GetDraw(int iRod) 
{ 
	Tube_Selector.GetOutputData();
	csTemp2.Format("%f", Tube_SelectorOutData.ParamMassiveOut[iRod]);
	return csTemp2; 
}
//--------------------------------------------------------------------------------------------
//	Отображение файла результатов
//--------------------------------------------------------------------------------------------
void CTube_SelectorDlg::OnButtonDraw()
{
	STARTUPINFO cif;
	ZeroMemory(&cif,sizeof(STARTUPINFO));
	PROCESS_INFORMATION pi;
	char pname1[500];
	strcpy(pname1, "c:\\windows\\notepad.exe");
	strcat(pname1, " ");
	strcat(pname1, Tube_SelectorOutData.CloseSortFileName);
	if( CreateProcess( NULL,pname1,NULL,NULL,FALSE,0,NULL,NULL,&cif,&pi ) == TRUE)	{	}
}


void CTube_SelectorDlg::ErrorExit(char *string){/* Обработка ошибок */
	MessageBox(string,"Ошибка",MB_ICONEXCLAMATION);
	ExitProcess(0);
}
//--------------------------------------------------------------------------------------------
//	Открыть файл
//--------------------------------------------------------------------------------------------
void CTube_SelectorDlg::OpenFermaFile()
{
	m_ListCtrl1.DeleteAllItems();
	m_ListCtrl2.DeleteAllItems();

	CFileDialog fileDialog(TRUE,NULL,"*.frm");
	int result = (int)fileDialog.DoModal();
	if (result==IDOK)
	{
		ToolBar2.SetButtonStyle(2, WS_VISIBLE);
		ToolBar2.SetButtonStyle(3, WS_VISIBLE);
		ToolBar2.SetButtonStyle(4, TBBS_DISABLED);

		csTemp = fileDialog.m_ofn.lpstrFile;// fileDialog.GetPathName();
		strcpy(Tube_SelectorInData.OpenFileName, csTemp);
		pos1 = 0;
		memset(&sym, 0, 2);
		sym[0] = Tube_SelectorInData.OpenFileName[2];
		for (iTemp = _MAX_LINE_LEN; iTemp > 0; iTemp--)
		{
			if(Tube_SelectorInData.OpenFileName[iTemp] == sym[0])
			{
				pos1 = iTemp;
				break;
			}
		}

		for(iTemp = 0; iTemp < _MAX_LINE_FILE_LEN; iTemp++)
		{
			Tube_SelectorDebugData.OpenFileShortName[iTemp] = Tube_SelectorInData.OpenFileName[iTemp+pos1+1];
		}
		pos1 = 0;
		memset(&sym, 0, 2);
		m_file_name.SetWindowText(Tube_SelectorDebugData.OpenFileShortName);

		memset(&Line, '0', sizeof(Line));
		b_eof = false;
		for (iTemp = 0; iTemp < _MAX_LINE_LEN; iTemp++)	{ CSLine[iTemp].Format(""); }
		//	Открытие файла *.frm
		Tube_SelectorInData.FileLen = 5;	//	Задаём минимальную длину файла, которая позволит получить всю необходимую информацию
		for(iTemp = 0; iTemp < Tube_SelectorInData.FileLen; iTemp++)
		{

			stream = fopen(csTemp,"r");
			fsetpos(stream, &filepos1);
			fgets(Line, _MAX_LINE_LEN, stream);
			CSLine[iTemp] = Line;
			fgetpos(stream,&filepos1);
			if(iTemp == 4)
			{
				//	Количество стержней в конструкции
				Tube_SelectorInData.TotalRod = (int)atoi(CSLine[0]);
				//	Количество узлов в конструкции
				Tube_SelectorInData.TotalKnot = (int)atoi(CSLine[1]);
				//	Количество случаев нагружения
				Tube_SelectorInData.LoadCase = (int)atoi(CSLine[4]);
				//	Длина файла
				Tube_SelectorInData.FileLen = 11+3*Tube_SelectorInData.TotalRod + Tube_SelectorInData.TotalKnot*(4+2*Tube_SelectorInData.LoadCase);
			}
			fclose(stream);
		}
		filepos1 = 0;
		for (iTemp = 0; iTemp < _MAX_LINE_LEN; iTemp++)	{CSLine2[iTemp].Format("");}
		for(iTemp = 0; iTemp < Tube_SelectorInData.TotalRod; iTemp++)
		{
			Tube_SelectorInData.GivenArea[iTemp] = (float)atof(CSLine[7+Tube_SelectorInData.TotalRod * 2 + Tube_SelectorInData.TotalKnot * 2 + iTemp]);
		}
		//	Копирование содержимого файла
		for (iTemp = 0; iTemp < _MAX_LINE_LEN; iTemp++)
		{
			strcpy(Tube_SelectorInData.OpenFile[iTemp], CSLine[iTemp]);
		}

		if(Tube_SelectorInData.TotalRod > 0)
		{
			for (iTemp = 0; iTemp < Tube_SelectorInData.TotalRod; iTemp++)
			{
				m_ListCtrl1.DeleteAllItems();
			}
		}
	}
	filepos1 = 0;
	//	открытие файла nmi
	memset (&Tube_SelectorDebugData.NMIfileName, 0, _MAX_LINE_LEN);
	memset(&Tube_SelectorDebugData.STDfileName, 0, _MAX_LINE_LEN);
	strcpy(Tube_SelectorDebugData.NMIfileName, Tube_SelectorInData.OpenFileName);
	for(iTemp = 0; iTemp < _MAX_LINE_LEN; iTemp++)
	{
		if((Tube_SelectorDebugData.NMIfileName[iTemp] == '\n') || (Tube_SelectorDebugData.NMIfileName[iTemp] == NULL))
		{
			pos2 = iTemp;
			break;
		}
	}
	for(iTemp = pos2-3; iTemp < pos2; iTemp++)
	{
		Tube_SelectorDebugData.NMIfileName[iTemp] = NULL;
	}
	strcpy(Tube_SelectorDebugData.STDfileName, Tube_SelectorDebugData.NMIfileName);
	strcat(Tube_SelectorDebugData.NMIfileName, "nmi");
	if(fopen(Tube_SelectorDebugData.NMIfileName, "r") == 0) 
	{	
		ToolBar2.SetButtonStyle(3, TBBS_DISABLED);
		return;	
	}
	strcat(Tube_SelectorDebugData.STDfileName, "std");
	memset(&Line, '0', sizeof(Line));
	for (iTemp = 0; iTemp < _MAX_LINE_LEN; iTemp++)	{ CSLine[iTemp].Format(""); }

	for(iTemp = 0; iTemp < (Tube_SelectorInData.LoadCase*Tube_SelectorInData.TotalRod + 3); iTemp++)
	{
		stream = fopen(Tube_SelectorDebugData.NMIfileName,"r");
		fsetpos(stream, &filepos1);
		fgets(Line, _MAX_LINE_LEN, stream);
		for(jTemp = 0; jTemp < _MAX_LINE_LEN; jTemp ++)
		{
			if(Line[jTemp] == ',')
			{
				Line[jTemp] = '.';
			}
		}
		CSLine[iTemp] = Line;
		if(iTemp == 1)	{ Tube_SelectorDebugData.Lambda = (int)atoi(Line); }
		if(iTemp >= 3)	{	Tube_SelectorDebugData.NMIfile[iTemp - 3] = (float)atof(Line);	}
		fgetpos(stream,&filepos1);
		fclose(stream);
	}
	filepos1 = 0;

	for(iTemp = 0; iTemp < Tube_SelectorInData.TotalRod * Tube_SelectorInData.LoadCase; iTemp = iTemp + 3)
	{
		if((fabs(Tube_SelectorDebugData.NMIfile[iTemp+1]) >= fabs(Tube_SelectorDebugData.NMIfile[iTemp])) && (fabs(Tube_SelectorDebugData.NMIfile[iTemp+1]) >= fabs(Tube_SelectorDebugData.NMIfile[iTemp+2])))
		{
			Tube_SelectorInData.NesMoment[iTemp/3] = fabs(Tube_SelectorDebugData.NMIfile[iTemp+1]);
		}
		else if((fabs(Tube_SelectorDebugData.NMIfile[iTemp+2]) >= fabs(Tube_SelectorDebugData.NMIfile[iTemp])) && (fabs(Tube_SelectorDebugData.NMIfile[iTemp+2]) >= fabs(Tube_SelectorDebugData.NMIfile[iTemp+1])))
		{
			Tube_SelectorInData.NesMoment[iTemp/3] = fabs(Tube_SelectorDebugData.NMIfile[iTemp+2]);
		}
		else  Tube_SelectorInData.NesMoment[iTemp/3] = fabs(Tube_SelectorDebugData.NMIfile[iTemp]);
	}

	//	Заполнение таблицы входных данных
	for (iTemp = 0; iTemp < Tube_SelectorInData.TotalRod; iTemp++)
	{
		csTemp.Format("%i",iTemp+1);
		m_ListCtrl1.InsertItem(iTemp, csTemp, 0);
		csTemp.Format("%f", Tube_SelectorInData.GivenArea[iTemp]);
		m_ListCtrl1.SetItemText(iTemp, 1, csTemp);
		csTemp.Format("%f", Tube_SelectorInData.NesMoment[iTemp]);
		m_ListCtrl1.SetItemText(iTemp, 2, csTemp);
	}
	csTemp.Format("%i", Tube_SelectorDebugData.Lambda);
	m_lambda.SetWindowText(csTemp);

	memset(Line, 0, _MAX_LINE_LEN);
	//	Открытие файла *.std
	for(iTemp = 0; iTemp < Tube_SelectorInData.TotalRod + 2; iTemp++)
	{

		if(fopen(Tube_SelectorDebugData.STDfileName,"r") != NULL) 
		{
			stream = fopen(Tube_SelectorDebugData.STDfileName,"r");
			fsetpos(stream, &filepos1);
			fgets(Line, _MAX_LINE_LEN, stream);
			CSLine[iTemp] = Line;
			fgetpos(stream,&filepos1);
			if(iTemp >= 2)
			{
				Tube_SelectorDebugData.OldMomentOut[iTemp - 2] = (float)atof(CSLine[iTemp]);
				Tube_SelectorOutData.MomentOut[iTemp - 2] = Tube_SelectorDebugData.OldMomentOut[iTemp - 2];
			}
			fclose(stream);
		}
	}
	filepos1 = 0;
	filepos2 = 0;
}
//--------------------------------------------------------------------------------------------
//	Закрыть файл
//--------------------------------------------------------------------------------------------
void CTube_SelectorDlg::CloseFermaFile()
{
	m_ListCtrl1.DeleteAllItems();
	m_ListCtrl2.DeleteAllItems();

	int ii, jj;
	for(ii=0; ii < _ROD_QUANTITY; ii++) {Tube_SelectorInData.GivenArea[ii]=0;}
	for(ii=0; ii < _ROD_QUANTITY; ii++) {Tube_SelectorInData.NesMoment[ii]=0;}
	for(ii=0; ii < _MAX_LINE_LEN; ii++) {Tube_SelectorInData.OpenFileName[ii]=0;}
	for(ii=0; ii < _MAX_LINE_LEN; ii++) {for(jj=0; jj < _MAX_LINE_LEN; jj++) {Tube_SelectorInData.OpenFile[ii][jj] = 0;} }
	Tube_SelectorInData.TotalRod = 0;
	Tube_SelectorInData.TotalKnot = 0;
	Tube_SelectorInData.FileLen = 0;
	Tube_SelectorInData.LoadCase = 0;

	memset(&Tube_SelectorOutData, 0, sizeof(TTube_SelectorOut));

	for(ii=0; ii < _MAX_LINE_FILE_LEN; ii++) {Tube_SelectorDebugData.OpenFileShortName[ii]=0;}
	for(ii=0; ii < _NMI_LEN - 3; ii++) {Tube_SelectorDebugData.NMIfile[ii]=0;}
	for(ii=0; ii < _MAX_LINE_LEN; ii++) {Tube_SelectorDebugData.NMIfileName[ii]=0;}
	for(ii=0; ii < _MAX_LINE_LEN; ii++) {Tube_SelectorDebugData.STDfileName[ii]=0;}
	for(ii=0; ii < _STD_FILE_LEN; ii++) {for(jj=0; jj < _MAX_LINE_FILE_LEN; jj++) {Tube_SelectorDebugData.STDfile[ii][jj] = 0;} }
	for(ii=0; ii < _ROD_QUANTITY; ii++) {Tube_SelectorDebugData.OldMomentOut[ii]=0;}
	Tube_SelectorDebugData.Lambda = 0;

	csTemp.Format("");
	m_file_name.SetWindowText(csTemp);
	m_rod_number.SetWindowText(csTemp);
	m_lambda.SetWindowText(csTemp);

	filepos1 = 0;
	filepos2 = 0;

	ToolBar2.SetButtonStyle(1, TBBS_DISABLED);
	ToolBar2.SetButtonStyle(2, TBBS_DISABLED);
	ToolBar2.SetButtonStyle(3, TBBS_DISABLED);
	ToolBar2.SetButtonStyle(4, TBBS_DISABLED);

	csTemp1.Format("");
	b_eof = false;
	memset(&Line, '0', sizeof(Line));
	for (iTemp = 0; iTemp < 255; iTemp++)	{CSLine[iTemp].Format("");}
	for (iTemp = 0; iTemp < 255; iTemp++)	{CSLine2[iTemp].Format("");}
	for(ii=0; ii<_ROD_QUANTITY; ii++) {NesMoment[ii] = 0;}
	for(ii=0; ii<_ROD_QUANTITY; ii++) {GivenArea[ii] = 0;}
	StringLenght = 0;
	pos1 = 0;
	pos2 = 0;
	iTemp = 0; jTemp = 0;
	for(ii=0; ii<_MAX_LINE_LEN; ii++) {HelpMassive[ii] = 0;}
	for(ii=0; ii<_MAX_LINE_LEN; ii++) {HelpMassive1[ii] = 0;}
	StringLenght = 0;
}
//--------------------------------------------------------------------------------------------
//	Сохранить файл
//--------------------------------------------------------------------------------------------
void CTube_SelectorDlg::SaveFermaFile()
{
	{
		if(Tube_SelectorInData.OpenFileName[0] == 0)	 { return; }
		strcpy(Tube_SelectorOutData.CloseFileName, Tube_SelectorInData.OpenFileName);
		strcpy(Tube_SelectorOutData.CloseSortFileName, Tube_SelectorInData.OpenFileName);
		for(iTemp = 0; iTemp < _MAX_LINE_LEN; iTemp++)
		{
			if((Tube_SelectorOutData.CloseSortFileName[iTemp] == '\n') || (Tube_SelectorOutData.CloseSortFileName[iTemp] == NULL))
			{
				pos2 = iTemp;
				break;
			}
		}
		for(iTemp = pos2-3; iTemp < pos2; iTemp++)
		{
			Tube_SelectorOutData.CloseSortFileName[iTemp] = NULL;
		}
		strcat(Tube_SelectorOutData.CloseSortFileName, "txt");

		ToolBar2.SetButtonStyle(4, WS_VISIBLE);
		memset(HelpMassive,0,_MAX_LINE_LEN);
		filepos2 = 0;
		//	Запись таблицы подобранных стержней в файл *.txt
		stream = fopen(Tube_SelectorOutData.CloseSortFileName, "w");

		for (iTemp = 0; iTemp < Tube_SelectorInData.TotalRod; iTemp++)
		{
			memset(HelpMassive, 0, _MAX_LINE_LEN);
			fsetpos(stream, &filepos2);
			for(jTemp = 0; jTemp < _MAX_LINE_LEN; jTemp++)
			{
				if((Tube_SelectorOutData.ParamMassiveOut[iTemp][jTemp] == '\t') || (Tube_SelectorOutData.ParamMassiveOut[iTemp][jTemp] == '\n') || (Tube_SelectorOutData.ParamMassiveOut[iTemp][jTemp] == NULL))
				{break;}
				else
				{
					HelpMassive[jTemp] = Tube_SelectorOutData.ParamMassiveOut[iTemp][jTemp];
				}
			}
			HelpMassive[jTemp] = '\t';
			pos2 = jTemp+1;
			csTemp1.Format("%f", Tube_SelectorOutData.AreaOut[iTemp]);
			for(jTemp = pos2; jTemp < _MAX_LINE_LEN; jTemp++)
			{
				strcpy(HelpMassive1, csTemp1);
				if((HelpMassive1[jTemp - pos2] == '\t') || (HelpMassive1[jTemp - pos2] == '\n') || (HelpMassive1[jTemp - pos2] == NULL))
				{break;}
				else
				{
					HelpMassive[jTemp] = HelpMassive1[jTemp - pos2];
				}
			}

			HelpMassive[jTemp] = '\t';
			pos2 = jTemp+1;
			csTemp1.Format("%f", Tube_SelectorOutData.MomentOut[iTemp]);
			for(jTemp = pos2; jTemp < _MAX_LINE_LEN; jTemp++)
			{
				strcpy(HelpMassive1, csTemp1);
				if((HelpMassive1[jTemp - pos2] == '\t') || (HelpMassive1[jTemp - pos2] == '\n') || (HelpMassive1[jTemp - pos2] == NULL))
				{break;}
				else
				{
					HelpMassive[jTemp] = HelpMassive1[jTemp - pos2];
				}
			}
			HelpMassive[jTemp] = '\n';
			csTemp.Format("%s", HelpMassive);

			fprintf(stream, "%s", csTemp);
			fgetpos(stream,&filepos2);
		}
		fclose(stream);


		filepos2 = 0;
		//	Запись данных в файл *.frm на выходе
		for(iTemp = 0; iTemp < Tube_SelectorInData.FileLen; iTemp++)
		{
			strcpy(Tube_SelectorOutData.CloseFile[iTemp], Tube_SelectorInData.OpenFile[iTemp]);
		}
		for(iTemp = 0; iTemp < Tube_SelectorInData.TotalRod; iTemp++)
		{
			csTemp.Format("%f", Tube_SelectorOutData.AreaOut[iTemp]);
			csTemp += '\n';
			strcpy(Tube_SelectorOutData.CloseFile[7+Tube_SelectorInData.TotalRod * 2 + Tube_SelectorInData.TotalKnot * 2 + iTemp], csTemp);
		}

		stream = fopen(Tube_SelectorOutData.CloseFileName, "w");

		for (iTemp = 0; iTemp < _MAX_LINE_LEN; iTemp++)
		{
			fsetpos(stream, &filepos2);
			csTemp.Format("%s", Tube_SelectorOutData.CloseFile[iTemp]);

			fprintf(stream, "%s", csTemp);
			fgetpos(stream,&filepos2);
		}
		fclose(stream);
	}
	filepos2 = 0;
	stream = fopen(Tube_SelectorDebugData.STDfileName, "w");
	for(iTemp = 0; iTemp < Tube_SelectorInData.TotalRod + 2; iTemp++)
	{
		fsetpos(stream, &filepos2);
		if(iTemp == 0)
		{
			csTemp.Format("%i", Tube_SelectorDebugData.Lambda);
		}
		else if(iTemp == 1)
		{
			csTemp.Format("%i", Tube_SelectorInData.TotalRod);
		}
		else
		{
			csTemp.Format("%f", Tube_SelectorOutData.MomentOut[iTemp - 2]);
		}
		csTemp = csTemp + '\n';
		fprintf(stream, "%s", csTemp);
		fgetpos(stream,&filepos2);
	}
	fclose(stream);
	// }
	filepos2 = 0;
	ToolBar2.SetButtonStyle(4, WS_VISIBLE);
}
//--------------------------------------------------------------------------------------------
//	Сохранить файл как
//--------------------------------------------------------------------------------------------
void CTube_SelectorDlg::SaveAsFermaFile()
{
	if(Tube_SelectorInData.OpenFileName[0] == 0)
	{ return; }
	CFileDialog fileDialog(FALSE,NULL,"*.frm");
	int result = (int)fileDialog.DoModal();
	if (result==IDOK)
	{
		csTemp = fileDialog.GetPathName();

		ToolBar2.SetButtonStyle(4, WS_VISIBLE);

		strcpy(Tube_SelectorOutData.CloseFileName, csTemp);
		for(iTemp = 0; iTemp < _MAX_LINE_LEN; iTemp++)
		{
			if(Tube_SelectorOutData.CloseFileName[iTemp] == '.') break;
			else if (Tube_SelectorOutData.CloseFileName[iTemp] == NULL) 
			{
				strcat(Tube_SelectorOutData.CloseFileName, ".frm");
				break;
			}
		}

		strcpy(Tube_SelectorOutData.CloseSortFileName, csTemp);
		for(iTemp = 0; iTemp < _MAX_LINE_LEN; iTemp++)
		{
			if(Tube_SelectorOutData.CloseSortFileName[iTemp] == '.') break;
			else if (Tube_SelectorOutData.CloseSortFileName[iTemp] == NULL)
			{
				strcat(Tube_SelectorOutData.CloseSortFileName, ".frm");
				break;
			}
		}

		////////////////////////////////////////
		int pos3 = 0, iii = 0;
		for(iTemp = _MAX_LINE_LEN; iTemp > 0; iTemp--)
		{
			if(Tube_SelectorOutData.CloseFileName[iTemp] == '\\') 
			{
				pos3 = iTemp;
				break;
			}
		}
		for(iTemp = pos3+1; iTemp < _MAX_LINE_LEN; iTemp++)
		{
			Tube_SelectorDebugData.OpenFileShortName[iii] = Tube_SelectorOutData.CloseFileName[iTemp];
			iii++;
		}



		for(iTemp = 0; iTemp < _MAX_LINE_LEN; iTemp++)
		{
			if((Tube_SelectorOutData.CloseSortFileName[iTemp] == '\n') || (Tube_SelectorOutData.CloseSortFileName[iTemp] == NULL))
			{
				pos2 = iTemp;
				break;
			}
		}
		for(iTemp = pos2-3; iTemp < pos2; iTemp++)
		{
			Tube_SelectorOutData.CloseSortFileName[iTemp] = NULL;
		}
		strcat(Tube_SelectorOutData.CloseSortFileName, "txt");

		memset(HelpMassive,0,_MAX_LINE_LEN);
		filepos2 = 0;
		//	Запись таблицы подобранных стержней в файл *.txt
		stream = fopen(Tube_SelectorOutData.CloseSortFileName, "w");

		for (iTemp = 0; iTemp < Tube_SelectorInData.TotalRod; iTemp++)
		{
			memset(HelpMassive, 0, _MAX_LINE_LEN);
			fsetpos(stream, &filepos2);
			for(jTemp = 0; jTemp < _MAX_LINE_LEN; jTemp++)
			{
				if((Tube_SelectorOutData.ParamMassiveOut[iTemp][jTemp] == '\t') || (Tube_SelectorOutData.ParamMassiveOut[iTemp][jTemp] == '\n') || (Tube_SelectorOutData.ParamMassiveOut[iTemp][jTemp] == NULL))
				{break;}
				else
				{
					HelpMassive[jTemp] = Tube_SelectorOutData.ParamMassiveOut[iTemp][jTemp];
				}
			}
			HelpMassive[jTemp] = '\t';
			pos2 = jTemp+1;
			csTemp1.Format("%f", Tube_SelectorOutData.AreaOut[iTemp]);
			for(jTemp = pos2; jTemp < _MAX_LINE_LEN; jTemp++)
			{
				strcpy(HelpMassive1, csTemp1);
				if((HelpMassive1[jTemp - pos2] == '\t') || (HelpMassive1[jTemp - pos2] == '\n') || (HelpMassive1[jTemp - pos2] == NULL))
				{break;}
				else
				{
					HelpMassive[jTemp] = HelpMassive1[jTemp - pos2];
				}
			}

			HelpMassive[jTemp] = '\t';
			pos2 = jTemp+1;
			csTemp1.Format("%f", Tube_SelectorOutData.MomentOut[iTemp]);
			for(jTemp = pos2; jTemp < _MAX_LINE_LEN; jTemp++)
			{
				strcpy(HelpMassive1, csTemp1);
				if((HelpMassive1[jTemp - pos2] == '\t') || (HelpMassive1[jTemp - pos2] == '\n') || (HelpMassive1[jTemp - pos2] == NULL))
				{break;}
				else
				{
					HelpMassive[jTemp] = HelpMassive1[jTemp - pos2];
				}
			}
			HelpMassive[jTemp] = '\n';
			csTemp.Format("%s", HelpMassive);

			fprintf(stream, "%s", csTemp);
			fgetpos(stream,&filepos2);
		}
		fclose(stream);


		filepos2 = 0;
		//	Запись данных в файл *.frm на выходе
		for(iTemp = 0; iTemp < Tube_SelectorInData.FileLen; iTemp++)
		{
			strcpy(Tube_SelectorOutData.CloseFile[iTemp], Tube_SelectorInData.OpenFile[iTemp]);
		}
		for(iTemp = 0; iTemp < Tube_SelectorInData.TotalRod; iTemp++)
		{
			csTemp.Format("%f", Tube_SelectorOutData.AreaOut[iTemp]);
			csTemp += '\n';
			strcpy(Tube_SelectorOutData.CloseFile[7+Tube_SelectorInData.TotalRod * 2 + Tube_SelectorInData.TotalKnot * 2 + iTemp], csTemp);
		}

		stream = fopen(Tube_SelectorOutData.CloseFileName, "w");

		for (iTemp = 0; iTemp < _MAX_LINE_LEN; iTemp++)
		{
			fsetpos(stream, &filepos2);
			csTemp.Format("%s", Tube_SelectorOutData.CloseFile[iTemp]);

			fprintf(stream, "%s", csTemp);
			fgetpos(stream,&filepos2);
		}
		fclose(stream);
	}

	//	создание файла *.std
	memset(&Tube_SelectorDebugData.STDfileName, 0, _MAX_LINE_LEN);
	strcpy(Tube_SelectorDebugData.STDfileName, Tube_SelectorOutData.CloseFileName);
	for(iTemp = 0; iTemp < _MAX_LINE_LEN; iTemp++)
	{
		if((Tube_SelectorDebugData.STDfileName[iTemp] == '\n') || (Tube_SelectorDebugData.STDfileName[iTemp] == NULL))
		{
			pos2 = iTemp;
			break;
		}
	}
	for(iTemp = pos2-3; iTemp < pos2; iTemp++)
	{
		Tube_SelectorDebugData.STDfileName[iTemp] = NULL;
	}
	strcat(Tube_SelectorDebugData.STDfileName, "std");
	//	запись данных в файл *.std
	filepos2 = 0;
	stream = fopen(Tube_SelectorDebugData.STDfileName, "w");
	for(iTemp = 0; iTemp < Tube_SelectorInData.TotalRod + 2; iTemp++)
	{
		fsetpos(stream, &filepos2);
		if(iTemp == 0)
		{
			csTemp.Format("%i", Tube_SelectorDebugData.Lambda);
		}
		else if(iTemp == 1)
		{
			csTemp.Format("%i", Tube_SelectorInData.TotalRod);
		}
		else
		{
			csTemp.Format("%f", Tube_SelectorOutData.MomentOut[iTemp - 2]);
		}
		csTemp = csTemp + '\n';
		fprintf(stream, "%s", csTemp);
		fgetpos(stream,&filepos2);
	}
	fclose(stream);
	filepos2 = 0;
	filepos1 = 0;

	strcpy(Tube_SelectorInData.OpenFileName, Tube_SelectorOutData.CloseFileName);
	m_file_name.SetWindowText(Tube_SelectorDebugData.OpenFileShortName);

	char cMas[_MAX_LINE_LEN];
	int iPos = 0, iPos1 = 0;
	strcpy(cMas, Tube_SelectorOutData.CloseFileName);
	for(iPos = _MAX_LINE_LEN; iPos > 0; iPos--)	
	{ 
		if(cMas[iPos] == NULL) 
		{ 
			iPos = iPos - 1;
			break; 
		}	
	}
	for(iPos1 = iPos; iPos1 > iPos-3; iPos1--) {cMas[iPos1] = NULL;}
	strcat(cMas, "nmi");
	CopyFile(Tube_SelectorDebugData.NMIfileName ,cMas,false);

	ToolBar2.SetButtonStyle(4, WS_VISIBLE);
}
//--------------------------------------------------------------------------------------------
//	Подбор стержней
//--------------------------------------------------------------------------------------------
void CTube_SelectorDlg::SelectFerma()
{
if(Tube_SelectorDebugData.OpenFileShortName[0] == 0) {return;}
  if(Tube_SelectorDebugData.SortamentShortFileName[0] == NULL)
	{	//////////////////////////////////////////////
	
	CFileDialog fileDialog(TRUE,NULL,"*.txt");

 int result = (int)fileDialog.DoModal();
 if (result != IDOK) { return; } 
 else if (result==IDOK)
 {

csTemp = fileDialog.m_ofn.lpstrFile;
strcpy(Tube_SelectorDebugData.SortamentFileName, csTemp);

ToolBar2.SetButtonStyle(4, TBBS_DISABLED);

pos1 = 0;
memset(&sym, 0, 2);
sym[0] = Tube_SelectorDebugData.SortamentFileName[2];
for (iTemp = _MAX_LINE_LEN; iTemp > 0; iTemp--)
{
	if(Tube_SelectorDebugData.SortamentFileName[iTemp] == sym[0])
	{
		pos1 = iTemp;
		break;
	}
}
for(iTemp = 0; iTemp < _MAX_LINE_FILE_LEN; iTemp++)
{
	Tube_SelectorDebugData.SortamentShortFileName[iTemp] = Tube_SelectorDebugData.SortamentFileName[iTemp+pos1+1];
}
pos1 = 0;
memset(&sym, 0, 2);

m_sortament_file_name.SetWindowText(Tube_SelectorDebugData.SortamentShortFileName);

 	memset(&Line, '0', sizeof(Line));
	b_eof = false;
	filepos1 = 0;
	for (iTemp = 0; iTemp < _MAX_LINE_LEN; iTemp++)	{ CSLine[iTemp].Format(""); }

	//	Открытие файла сортамента
 	for(iTemp = 0; iTemp < _SORTAMENT_SIZE+1; iTemp++)
	{
		stream = fopen(Tube_SelectorDebugData.SortamentFileName,"r");
		fsetpos(stream, &filepos1);
		fgets(Line, _MAX_LINE_LEN, stream);
		CSLine[iTemp] = Line;
		fgetpos(stream,&filepos1);
		fclose(stream);
		if(strcmp(CSLine[iTemp],CSLine[iTemp-1]) == 0) { break; }

		if(iTemp ==0) {strcpy(Tube_SelectorDebugData.SortamentName, CSLine[iTemp]);}
		else
		{
		strcpy(Tube_SelectorInData.ParamMassive[iTemp-1], (CSLine[iTemp].Left(CSLine[iTemp].Find('\t'))));
		StringLenght = (int)strlen(Tube_SelectorInData.ParamMassive[iTemp]);
		Tube_SelectorInData.Area[iTemp-1] = (float)atof(CSLine[iTemp].Mid(CSLine[iTemp].Find('\t')));
		for(jTemp = _MAX_LINE_LEN; jTemp > 0; jTemp--)
			{
				if(Line[jTemp] == '\t') 
				{
					pos1 = jTemp+1; 
					jTemp = 0;
				}
			}
		for (jTemp = pos1; jTemp < _MAX_LINE_LEN; jTemp++) 
		{
			HelpMassive[jTemp-pos1] = Line[jTemp];
		}
		Tube_SelectorInData.Moment[iTemp-1] = (float)atof(HelpMassive);
		}
	}
	filepos1 = 0;
 }

 for(iTemp = 0; iTemp < _MAX_LINE_FILE_LEN; iTemp++)
{
	if((Tube_SelectorDebugData.SortamentName[iTemp] == '\n') || (Tube_SelectorDebugData.SortamentName[iTemp] == '\0'))
	{	Tube_SelectorDebugData.SortamentName[iTemp] = 0; }
}
	} ///////////////////////////////////////
//	вывод стандарта сортамента
 m_standart.SetWindowText(Tube_SelectorDebugData.SortamentName);

		Tube_Selector.PreTube_SelectorIn = Tube_SelectorInData;
	for (iTemp = 0; iTemp < Tube_SelectorInData.TotalRod; iTemp++)
	{
			Tube_Selector.FirstSelection(iTemp);
	}
	Tube_SelectorOutData = Tube_Selector.GetOutputData();

    CString cSpName;
		m_ListCtrl2.DeleteAllItems();
		//	Заполнение таблицы выходных данных
		for (int i = 0; i < Tube_SelectorInData.TotalRod; i++)
    {
			cSpName.Format("%i",i+1);
			m_ListCtrl2.InsertItem(i, cSpName, 0);
			if(strcmp(Tube_SelectorOutData.ParamMassiveOut[i], "") == 0) 
			{
				m_ListCtrl2.SetItemText(i, 1, "#####");
				m_ListCtrl2.SetItemText(i, 2, "#####");
				m_ListCtrl2.SetItemText(i, 3, "#####");
			}
			else 
			{
			m_ListCtrl2.SetItemText(i, 1, Tube_SelectorOutData.ParamMassiveOut[i]); 
			cSpName.Format("%f", Tube_SelectorOutData.AreaOut[i]);
			m_ListCtrl2.SetItemText(i, 2, cSpName);
			cSpName.Format("%f", Tube_SelectorOutData.MomentOut[i]);
			m_ListCtrl2.SetItemText(i, 3, cSpName);
		}
    }
		 	 	ToolBar2.SetButtonStyle(1, WS_VISIBLE);
}
//--------------------------------------------------------------------------------------------
//	Вызов справки
//--------------------------------------------------------------------------------------------
void CTube_SelectorDlg::FermaHelp() { }

void CTube_SelectorDlg::OnBnClickedOk() {	/*OnOK(); */ }
void CTube_SelectorDlg::OnBnClickedCancel() {	OnCancel(); }






void CTube_SelectorDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: добавьте свой код обработчика уведомлений
	*pResult = 0;
}
