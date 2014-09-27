// pingyi.cpp : implementation file
//

#include "stdafx.h"
#include "DIP_Final.h"
#include "pingyi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cpingyi dialog


Cpingyi::Cpingyi(CWnd* pParent /*=NULL*/)
	: CDialog(Cpingyi::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cpingyi)
	m_X = 0;
	m_Y = 0;
	//}}AFX_DATA_INIT
}


void Cpingyi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cpingyi)
	DDX_Text(pDX, IDC_EDIT1, m_X);
	DDX_Text(pDX, IDC_EDIT2, m_Y);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cpingyi, CDialog)
	//{{AFX_MSG_MAP(Cpingyi)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cpingyi message handlers
