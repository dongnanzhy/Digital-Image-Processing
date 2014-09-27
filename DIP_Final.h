// DIP_Final.h : main header file for the DIP_FINAL application
//

#if !defined(AFX_DIP_FINAL_H__33281186_94C6_46B1_9CC0_FD41E9BCF7D3__INCLUDED_)
#define AFX_DIP_FINAL_H__33281186_94C6_46B1_9CC0_FD41E9BCF7D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDIP_FinalApp:
// See DIP_Final.cpp for the implementation of this class
//

class CDIP_FinalApp : public CWinApp
{
public:
	CDIP_FinalApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDIP_FinalApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDIP_FinalApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIP_FINAL_H__33281186_94C6_46B1_9CC0_FD41E9BCF7D3__INCLUDED_)
