// suofang1.cpp : implementation file
//

#include "stdafx.h"
#include "DIP_Final.h"
#include "suofang1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Csuofang dialog


Csuofang::Csuofang(CWnd* pParent /*=NULL*/)
	: CDialog(Csuofang::IDD, pParent)
{
	//{{AFX_DATA_INIT(Csuofang)
	m_Xratio = 0.0f;
	m_Yratio = 0.0f;
	m_choose = _T("");
	m_insert = -1;
	//}}AFX_DATA_INIT
}


void Csuofang::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Csuofang)
	DDX_Text(pDX, IDC_EDIT1, m_Xratio);
	DDX_Text(pDX, IDC_EDIT2, m_Yratio);
	DDX_Radio(pDX, IDC_RADIO1, m_insert);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Csuofang, CDialog)
	//{{AFX_MSG_MAP(Csuofang)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Csuofang message handlers
