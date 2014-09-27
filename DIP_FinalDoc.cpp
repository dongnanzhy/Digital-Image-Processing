// DIP_FinalDoc.cpp : implementation of the CDIP_FinalDoc class
//

#include "stdafx.h"
#include "DIP_Final.h"

#include "DIP_FinalDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIP_FinalDoc

IMPLEMENT_DYNCREATE(CDIP_FinalDoc, CDocument)

BEGIN_MESSAGE_MAP(CDIP_FinalDoc, CDocument)
	//{{AFX_MSG_MAP(CDIP_FinalDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDIP_FinalDoc construction/destruction

CDIP_FinalDoc::CDIP_FinalDoc()
{
	// TODO: add one-time construction code here
    m_pDib=NULL;
}

CDIP_FinalDoc::~CDIP_FinalDoc()
{
	if (m_pDib!=NULL)
	{
		delete []m_pDib;
	}
}

BOOL CDIP_FinalDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDIP_FinalDoc serialization

void CDIP_FinalDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDIP_FinalDoc diagnostics

#ifdef _DEBUG
void CDIP_FinalDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDIP_FinalDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDIP_FinalDoc commands

BOOL CDIP_FinalDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	m_pDib=new CDib;
	if (m_pDib!=NULL)
	{
		m_pDib->LoadFile(lpszPathName);
		UpdateWindow(NULL);
	}
	
	return TRUE;
}
