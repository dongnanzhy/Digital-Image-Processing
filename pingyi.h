#if !defined(AFX_PINGYI_H__92014E87_E627_4AAA_8CE1_38D54D43DD96__INCLUDED_)
#define AFX_PINGYI_H__92014E87_E627_4AAA_8CE1_38D54D43DD96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// pingyi.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cpingyi dialog

class Cpingyi : public CDialog
{
// Construction
public:
	Cpingyi(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cpingyi)
	enum { IDD = IDD_DIALOG5 };
	int		m_X;
	int		m_Y;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cpingyi)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cpingyi)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PINGYI_H__92014E87_E627_4AAA_8CE1_38D54D43DD96__INCLUDED_)
