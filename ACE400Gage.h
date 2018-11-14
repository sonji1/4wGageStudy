// ACE400Gage.h : main header file for the ACE400Gage application
//

#if !defined(AFX_ACE400Gage_H__CB3F7139_0C6D_46B6_A240_563945A8EA0D__INCLUDED_)
#define AFX_ACE400Gage_H__CB3F7139_0C6D_46B6_A240_563945A8EA0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CACE400GageApp:
// See ACE400Gage.cpp for the implementation of this class
//

class CACE400GageApp : public CWinApp
{
public:
	CACE400GageApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CACE400GageApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CACE400GageApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACE400Gage_H__CB3F7139_0C6D_46B6_A240_563945A8EA0D__INCLUDED_)
