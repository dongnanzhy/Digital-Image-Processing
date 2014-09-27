#if !defined(AFX_HGDLG_H__08745820_77F9_41DD_A985_DF26EB60B132__INCLUDED_)
#define AFX_HGDLG_H__08745820_77F9_41DD_A985_DF26EB60B132__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Hgdlg.h : header file
//
#include "Dib.h"

/////////////////////////////////////////////////////////////////////////////
// CHgdlg dialog

class CHgdlg : public CDialog
{
// Construction
public:
	CHgdlg(CDib *m_pDib,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHgdlg)
	enum { IDD = IDD_DIALOG2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHgdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHgdlg)
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	long *m_pData;
	int m_count;
	CDib *m_pDib;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HGDLG_H__08745820_77F9_41DD_A985_DF26EB60B132__INCLUDED_)
