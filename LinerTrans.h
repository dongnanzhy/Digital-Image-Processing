#if !defined(AFX_LINERTRANS_H__C1219985_BF1B_4F78_B0FC_CB145D9BFFB1__INCLUDED_)
#define AFX_LINERTRANS_H__C1219985_BF1B_4F78_B0FC_CB145D9BFFB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LinerTrans.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLinerTrans dialog

class CLinerTrans : public CDialog
{
// Construction
public:
	CLinerTrans(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLinerTrans)
	enum { IDD = IDD_DIALOG1 };
	int		m_X1;
	int		m_X2;
	int		m_X3;
	int		m_X4;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLinerTrans)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLinerTrans)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINERTRANS_H__C1219985_BF1B_4F78_B0FC_CB145D9BFFB1__INCLUDED_)
