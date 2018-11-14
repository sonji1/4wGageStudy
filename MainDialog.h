// MainDialog.h : header file
//

#if !defined(AFX_ACE400GageDLG_H__A60D6315_99C4_46C0_A323_42C7B357B0A2__INCLUDED_)
#define AFX_ACE400GageDLG_H__A60D6315_99C4_46C0_A323_42C7B357B0A2__INCLUDED_

#include "GageDialog.h"	// Added by ClassView
#include "ConfigDialog.h"		

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMainDialog dialog

class CMainDialog : public CDialog
{
// Construction
public:
	CGageDialog			m_GageDlg;
	CConfigDialog		m_ConfigDlg;

	CMainDialog(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMainDialog)
	enum { IDD = IDD_MAIN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainDialog)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMainDialog)
	virtual BOOL 	OnInitDialog();
	afx_msg void 	OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void 	OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void 	OnCheckGage();
	afx_msg void 	OnCheckConfig();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACE400GageDLG_H__A60D6315_99C4_46C0_A323_42C7B357B0A2__INCLUDED_)
