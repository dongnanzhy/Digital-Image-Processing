#if !defined(AFX_SUOFANG1_H__96406124_B0C0_40DF_9D1D_79C29B6B048E__INCLUDED_)
#define AFX_SUOFANG1_H__96406124_B0C0_40DF_9D1D_79C29B6B048E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// suofang1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Csuofang dialog

class Csuofang : public CDialog
{
// Construction
public:
	Csuofang(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Csuofang)
	enum { IDD = IDD_DIALOG3 };
	float	m_Xratio;
	float	m_Yratio;
	CString	m_choose;
	int		m_insert;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Csuofang)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Csuofang)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUOFANG1_H__96406124_B0C0_40DF_9D1D_79C29B6B048E__INCLUDED_)
