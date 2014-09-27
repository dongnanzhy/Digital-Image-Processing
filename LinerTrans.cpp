// LinerTrans.cpp : implementation file
//

#include "stdafx.h"
#include "DIP_Final.h"
#include "LinerTrans.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinerTrans dialog


CLinerTrans::CLinerTrans(CWnd* pParent /*=NULL*/)
	: CDialog(CLinerTrans::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLinerTrans)
	m_X1 = 0;
	m_X2 = 0;
	m_X3 = 0;
	m_X4 = 0;
	//}}AFX_DATA_INIT
}


void CLinerTrans::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLinerTrans)
	DDX_Text(pDX, IDC_EDIT1, m_X1);
	DDX_Text(pDX, IDC_EDIT2, m_X2);
	DDX_Text(pDX, IDC_EDIT3, m_X3);
	DDX_Text(pDX, IDC_EDIT4, m_X4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLinerTrans, CDialog)
	//{{AFX_MSG_MAP(CLinerTrans)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLinerTrans message handlers
