// MainDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ACE400Gage.h"
#include "MainDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDialog dialog

CMainDialog::CMainDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMainDialog, CDialog)
	//{{AFX_MSG_MAP(CMainDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_GAGE, 		OnCheckGage)
	ON_BN_CLICKED(IDC_CHECK_CONFIG, 	OnCheckConfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDialog message handlers

BOOL CMainDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	

	// TODO: Add extra initialization here
	m_GageDlg.Create(IDD_GAGE_DIALOG, this);
	m_GageDlg.ShowWindow(SW_SHOW);
	m_ConfigDlg.Create(IDD_CONFIG_DIALOG, this);
	m_ConfigDlg.ShowWindow(SW_HIDE);

	((CButton*)GetDlgItem(IDC_CHECK_GAGE))->SetCheck(1);	// 해당 check 버튼을 눌린 상태로 유지
	((CButton*)GetDlgItem(IDC_CHECK_CONFIG))->SetCheck(0);

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMainDialog::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMainDialog::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMainDialog::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



void CMainDialog::OnCheckGage() 
{
	// TODO: Add your control notification handler code here
	((CButton*)GetDlgItem(IDC_CHECK_GAGE))->SetCheck(1);	// 해당 check 버튼을 눌린 상태로 유지
	((CButton*)GetDlgItem(IDC_CHECK_CONFIG))->SetCheck(0);
	
	m_ConfigDlg.ShowWindow(SW_HIDE);
	m_GageDlg.ShowWindow(SW_SHOW);
	
	UpdateData(FALSE);
}

void CMainDialog::OnCheckConfig() 
{
	// TODO: Add your control notification handler code here
	((CButton*)GetDlgItem(IDC_CHECK_GAGE))->SetCheck(0);	
	((CButton*)GetDlgItem(IDC_CHECK_CONFIG))->SetCheck(1); // 해당 check 버튼을 눌린 상태로 유지
	
	m_GageDlg.ShowWindow(SW_HIDE);
	m_ConfigDlg.ShowWindow(SW_SHOW);

	UpdateData(FALSE);
}

BOOL CMainDialog::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_GageDlg.DestroyWindow();

	MyTrace(PRT_BASIC, "\"4W GageStudy SW\" GageDlg Destroyed...\n\n\n\n\n" );
	
	return CDialog::DestroyWindow();
}
