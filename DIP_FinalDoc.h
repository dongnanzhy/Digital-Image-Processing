// DIP_FinalDoc.h : interface of the CDIP_FinalDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIP_FINALDOC_H__F6016AAC_646C_4EA8_9632_C6E5957DCE49__INCLUDED_)
#define AFX_DIP_FINALDOC_H__F6016AAC_646C_4EA8_9632_C6E5957DCE49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Dib.h"

class CDIP_FinalDoc : public CDocument
{
protected: // create from serialization only
	CDIP_FinalDoc();
	DECLARE_DYNCREATE(CDIP_FinalDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDIP_FinalDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDIP_FinalDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDIP_FinalDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CDib *m_pDib;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIP_FINALDOC_H__F6016AAC_646C_4EA8_9632_C6E5957DCE49__INCLUDED_)
