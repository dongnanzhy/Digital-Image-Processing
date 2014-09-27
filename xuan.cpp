// xuan.cpp : implementation file
//

#include "stdafx.h"
#include "DIP_Final.h"
#include "xuan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cxuan dialog


Cxuan::Cxuan(CWnd* pParent /*=NULL*/)
	: CDialog(Cxuan::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cxuan)
	m_angle = 0;
	m_insert = -1;
	//}}AFX_DATA_INIT
}


void Cxuan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cxuan)
	DDX_Text(pDX, IDC_EDIT1, m_angle);
	DDX_Radio(pDX, IDC_RADIO1, m_insert);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cxuan, CDialog)
	//{{AFX_MSG_MAP(Cxuan)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cxuan message handlers
