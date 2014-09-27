#if !defined(AFX_XUAN_H__A1DF0EE8_E5C2_4597_9FBC_89636FEF7070__INCLUDED_)
#define AFX_XUAN_H__A1DF0EE8_E5C2_4597_9FBC_89636FEF7070__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// xuan.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cxuan dialog

class Cxuan : public CDialog
{
// Construction
public:
	Cxuan(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cxuan)
	enum { IDD = IDD_DIALOG4 };
	int		m_angle;
	int		m_insert;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cxuan)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cxuan)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XUAN_H__A1DF0EE8_E5C2_4597_9FBC_89636FEF7070__INCLUDED_)
