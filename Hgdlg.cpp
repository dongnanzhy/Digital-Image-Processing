// Hgdlg.cpp : implementation file
//

#include "stdafx.h"
#include "DIP_Final.h"
#include "Hgdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Dib.h"
/////////////////////////////////////////////////////////////////////////////
// CHgdlg dialog


CHgdlg::CHgdlg(CDib *m_pDib,CWnd* pParent /*=NULL*/)
	: CDialog(CHgdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHgdlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	if (m_pDib!=NULL)
	{
		m_pData =m_pDib->GetGreyCountNumber();	
        m_count=m_pDib->GetPaletteEntries();
	}
}


void CHgdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHgdlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHgdlg, CDialog)
	//{{AFX_MSG_MAP(CHgdlg)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHgdlg message handlers

void CHgdlg::OnPaint() 
{
	if (m_pData == NULL)
	{
		return;
	}
	CPaintDC dc(this);
	CRect rect;
	
	CWnd *pWnd = GetDlgItem(IDC_Histogram);
	pWnd->GetWindowRect(&rect);
	ScreenToClient(&rect);
	
	CDC *pDC = &dc;
	
	
	// 	CBrush BrushBlue(RGB(0,255,0));
	// 	CBrush *pOldBrush = pDC->SelectObject(&BrushBlue);
	
	CPen *pPen = new CPen;
	pPen->CreatePen(PS_SOLID,2,RGB(255,0,0));
	CPen *pOldPen = pDC->SelectObject(pPen);
	
	CPen *pBluePen = new CPen;
	pBluePen->CreatePen(PS_SOLID,2,RGB(0,0,255));
	
	
	rect.DeflateRect(20, 20);
	
	/*	pDC->Rectangle(&rect);*/
	
	pDC->MoveTo(rect.left,rect.bottom);
	pDC->LineTo(rect.left,rect.top);
	pDC->LineTo(rect.left-5,rect.top + 5);
	pDC->MoveTo(rect.left,rect.top);
	pDC->LineTo(rect.left+5,rect.top + 5);
	
	pDC->MoveTo(rect.left,rect.bottom);
	pDC->LineTo(rect.right,rect.bottom);
	pDC->LineTo(rect.right-5,rect.bottom - 5);
	pDC->MoveTo(rect.right,rect.bottom);
	pDC->LineTo(rect.right-5,rect.bottom + 5);
	
	
	int DeltaCount = rect.Width()/m_count;
	CString Str;
	
	Str.Format("0");
	pDC->TextOut(rect.left,rect.bottom+10,Str );
	
	Str.Format("25");
	pDC->TextOut(rect.left + 25 * DeltaCount,rect.bottom +10, Str);
	
	
	
	pDC->SelectObject(pBluePen);
	
	long GreyNumberMax = 0;
	
	for (int i=0; i< m_count; i++)
	{
		if (GreyNumberMax < *(m_pData+i))
		{
			GreyNumberMax = *(m_pData+i);
		}
	}
	for (i=0; i< m_count; i++)
	{
		if (GreyNumberMax != 0)
		{
			double Ratio = (( double )m_pData[i])/GreyNumberMax;
			pDC->MoveTo(rect.left + i* DeltaCount+10, rect.bottom);
			pDC->LineTo(rect.left + i* DeltaCount+10, rect.bottom - (int)(Ratio * rect.Height()));
		}
	}
	
	
	pDC->SelectObject(pOldPen);
	// 	pDC->SelectObject(pOldBrush);
	
	delete pPen;
	delete pBluePen;
	// device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CHgdlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
