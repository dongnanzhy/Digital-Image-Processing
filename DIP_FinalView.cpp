// DIP_FinalView.cpp : implementation of the CDIP_FinalView class
//

#include "stdafx.h"
#include "DIP_Final.h"

#include "DIP_FinalDoc.h"
#include "DIP_FinalView.h"
#include "LinerTrans.h"
#include "Hgdlg.h"
#include "suofang1.h"
#include "xuan.h"
#include "pingyi.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIP_FinalView

IMPLEMENT_DYNCREATE(CDIP_FinalView, CView)

BEGIN_MESSAGE_MAP(CDIP_FinalView, CView)
	//{{AFX_MSG_MAP(CDIP_FinalView)
	ON_COMMAND(ID_Invert, OnInvert)
	ON_COMMAND(ID_Liner, OnLiner)
	ON_COMMAND(ID_Hgdlg, OnHgdlg)
	ON_COMMAND(ID_Histoave, OnHistoave)
	ON_COMMAND(ID_Peppernoise, OnPeppernoise)
	ON_COMMAND(ID_Randomnoise, OnRandomnoise)
	ON_COMMAND(ID_Gradsharp, OnGradsharp)
	ON_COMMAND(ID_Lapchange, OnLapchange)
	ON_COMMAND(ID_Midchange, OnMidchange)
	ON_COMMAND(ID_Suofang, OnSuofang)
	ON_COMMAND(ID_Mirror, OnMirror)
	ON_COMMAND(ID_Mirror2, OnMirror2)
	ON_COMMAND(ID_Xuanzhuan, OnXuanzhuan)
	ON_COMMAND(ID_Pingyi, OnPingyi)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_Erzhi, OnErzhi)
	ON_COMMAND(ID_Fushi, OnFushi)
	ON_COMMAND(ID_Pengzhang, OnPengzhang)
	ON_COMMAND(ID_Tiqu, OnTiqu)
	ON_COMMAND(ID_Jiabianjie, OnJiabianjie)
	ON_COMMAND(ID_Tiqu2, OnTiqu2)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_Weicai, OnWeicai)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_Colortogrey, OnColortogrey)
	ON_COMMAND(ID_TiquLap, OnTiquLap)
	ON_COMMAND(ID_TiquSobel, OnTiquSobel)
	ON_COMMAND(ID_Pinghua, OnPinghua)
	ON_COMMAND(ID_RegionGrow, OnRegionGrow)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDIP_FinalView construction/destruction

CDIP_FinalView::CDIP_FinalView()
{
	m_IsSelected=FALSE;

}

CDIP_FinalView::~CDIP_FinalView()
{
}

BOOL CDIP_FinalView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDIP_FinalView drawing

void CDIP_FinalView::OnDraw(CDC* pDC)
{
	CDIP_FinalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if (pDoc->m_pDib!=NULL)
	{
		pDoc->m_pDib->Draw(pDC);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDIP_FinalView printing

BOOL CDIP_FinalView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDIP_FinalView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDIP_FinalView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDIP_FinalView diagnostics

#ifdef _DEBUG
void CDIP_FinalView::AssertValid() const
{
	CView::AssertValid();
}

void CDIP_FinalView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDIP_FinalDoc* CDIP_FinalView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDIP_FinalDoc)));
	return (CDIP_FinalDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDIP_FinalView message handlers
/***********************************************************************
* 函数名称：
* OnInvert()
*说明：负片
***********************************************************************/
void CDIP_FinalView::OnInvert() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc* pDoc = GetDocument();
	// TODO: add draw code for native data here
	if (pDoc->m_pDib!=NULL)
	{
		pDoc->m_pDib->Invert();
	}
	Invalidate(NULL);
}
/***********************************************************************
* 函数名称：
* OnLiner()
*说明：线性变换
***********************************************************************/
void CDIP_FinalView::OnLiner() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc* pDoc = GetDocument();
	
	if (pDoc->m_pDib!= NULL)
	{
		CLinerTrans dlg;
		if (dlg.DoModal()==IDOK)
		{
			pDoc->m_pDib->Liner(dlg.m_X1,dlg.m_X3,dlg.m_X2,dlg.m_X4);
			Invalidate(TRUE);
		}
	}
}
/***********************************************************************
* 函数名称：
* OnHgdlg()
*说明：显示直方图
***********************************************************************/
void CDIP_FinalView::OnHgdlg() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc* pDoc = GetDocument();	
	if (pDoc->m_pDib!=NULL)
	{	
		CHgdlg dlg(pDoc->m_pDib);
		dlg.DoModal() ;
	}
}

void CDIP_FinalView::OnHistoave() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc* pDoc = GetDocument();
	// TODO: add draw code for native data here
	if (pDoc->m_pDib!=NULL)
	{
		pDoc->m_pDib->Histave();
	}
	Invalidate(NULL);
}

void CDIP_FinalView::OnPeppernoise() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc *pDoc=GetDocument();
	if (pDoc->m_pDib!=NULL)
	{
		pDoc->m_pDib->AddPepperSaltNoise();
	}
	Invalidate(NULL);
}

void CDIP_FinalView::OnRandomnoise() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc *pDoc=GetDocument();
	if (pDoc->m_pDib!=NULL)
	{
		pDoc->m_pDib->AddRandomNoise();
	}
	Invalidate(NULL);
}

void CDIP_FinalView::OnGradsharp() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc *pDoc=GetDocument();
	if (pDoc->m_pDib!=NULL)
	{
		pDoc->m_pDib->GradSharp();
	}
	Invalidate(NULL);
}

void CDIP_FinalView::OnLapchange() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc *pDoc=GetDocument();
	if (pDoc->m_pDib!=NULL)
	{
		pDoc->m_pDib->Lapchange();
	}
	Invalidate(NULL);
}

void CDIP_FinalView::OnMidchange() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc *pDoc=GetDocument();
	if (pDoc->m_pDib!=NULL)
	{
		pDoc->m_pDib->Midchange();
	}
	Invalidate(NULL);
}

void CDIP_FinalView::OnSuofang() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc *pDoc =GetDocument();
	if (pDoc->m_pDib != NULL)
	{
		Csuofang dlg;
		if (dlg.DoModal()==IDOK)
		{
			if(dlg.m_insert==0)
				pDoc->m_pDib->Suoxiao(dlg.m_Xratio,dlg.m_Yratio);
			else
				pDoc->m_pDib->Suoxiao2(dlg.m_Xratio,dlg.m_Yratio);
			//dlg.DoModal();
			Invalidate(TRUE);
		}
	}
}

void CDIP_FinalView::OnMirror() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc *pDoc=GetDocument();
	if (pDoc->m_pDib!=NULL)
	{
		pDoc->m_pDib->MirrorHori();
	}
	Invalidate(NULL);
}

void CDIP_FinalView::OnMirror2() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc *pDoc=GetDocument();
	if (pDoc->m_pDib!=NULL)
	{
		pDoc->m_pDib->MirrorVerti();
	}
	Invalidate(NULL);
}

void CDIP_FinalView::OnXuanzhuan() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc *pDoc =GetDocument();
	if (pDoc->m_pDib != NULL)
	{
		Cxuan dlg;
		if (dlg.DoModal()==IDOK)
		{
			if(dlg.m_insert==0)
				pDoc->m_pDib->Xuanzhuan(dlg.m_angle);
			else
				pDoc->m_pDib->Xuanzhuan2(dlg.m_angle);
			//dlg.DoModal();
			Invalidate(TRUE);
		}
	}
}

void CDIP_FinalView::OnPingyi() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc *pDoc=GetDocument();
	if (pDoc->m_pDib!=NULL)
	{
		Cpingyi dlg;
		if (dlg.DoModal()==IDOK)
		{
			pDoc->m_pDib->Pingyi(dlg.m_X,dlg.m_Y);
			Invalidate(TRUE);
		}
	}
}

void CDIP_FinalView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_LRchoose=true;
	CDIP_FinalDoc *pDoc=GetDocument();
	
	if (pDoc->m_pDib != NULL && pDoc->m_pDib->PointInRect(point))
	{
		m_IsSelected = true;
		m_point = point;
	}
	CView::OnLButtonDown(nFlags, point);
}

void CDIP_FinalView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_IsSelected)
	{
		m_IsSelected = false;
	}
	CView::OnLButtonUp(nFlags, point);
}

void CDIP_FinalView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_IsSelected)
	{
		CSize size;
		size.cx = point.x-m_point.x;
		size.cy = point.y-m_point.y;
		CPoint point2;

		point2=point;
		point=m_point;
		m_point=point2;
/*		swap(point,m_point);*/
		
		CDIP_FinalDoc *pDoc = GetDocument();		
		pDoc->m_pDib->SetDestRect(size);	
		Invalidate(TRUE);
	}	
	
	CView::OnMouseMove(nFlags, point);
}

void CDIP_FinalView::OnErzhi() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc *pDoc=GetDocument();
	if (pDoc->m_pDib!=NULL)
	{
		pDoc->m_pDib->Erzhi();
	}
	Invalidate(NULL);
}

void CDIP_FinalView::OnFushi() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc *pDoc=GetDocument();
	if (pDoc->m_pDib!=NULL)
	{
		pDoc->m_pDib->Fushi();
	}
	Invalidate(NULL);
}

void CDIP_FinalView::OnPengzhang() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc *pDoc=GetDocument();
	if (pDoc->m_pDib!=NULL)
	{
		pDoc->m_pDib->Pengzhang();
	}
	Invalidate(NULL);
}

void CDIP_FinalView::OnTiqu() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc *pDoc=GetDocument();
	if (pDoc->m_pDib!=NULL)
	{
		pDoc->m_pDib->TiquRobert();
	}
	Invalidate(NULL);
}

void CDIP_FinalView::OnJiabianjie() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc *pDoc=GetDocument();
	if (pDoc->m_pDib!=NULL)
	{
		pDoc->m_pDib->Jiabianjie();
	}
	Invalidate(NULL);
}

void CDIP_FinalView::OnTiqu2() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc *pDoc=GetDocument();
	if (pDoc->m_pDib!=NULL)
	{
		pDoc->m_pDib->Tiqu2();
	}
	Invalidate(NULL);
}

void CDIP_FinalView::OnFileSave() 
{
	// TODO: Add your command handler code here
	CFileDialog dlg(FALSE,_T("BMP"),_T("*.BMP"),
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("位图文件(*.BMP)|*.BMP|"));	
	
	if(dlg.DoModal() == IDOK)
	{
		CDIP_FinalDoc *pDoc = GetDocument();
		pDoc->m_pDib->SaveFile(dlg.GetPathName());  //GetPathName()--得到完整的文件名，包括目录名和扩展名
	}
}

void CDIP_FinalView::OnWeicai() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc *pDoc=GetDocument();
	if (pDoc->m_pDib!=NULL)
	{
		pDoc->m_pDib->PseuColor();
	}
	Invalidate(NULL);
}

BOOL CDIP_FinalView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	CDIP_FinalDoc *pDoc = GetDocument();
	
	const double ratio = 0.01;
	
	short Delta = zDelta/WHEEL_DELTA;
	
	if (pDoc->m_pDib != NULL )
	{
		if (Delta > 0)
		{
			pDoc->m_pDib->Zoom(ratio);
		} else
		{
			pDoc->m_pDib->Zoom(ratio*(-1));
		}
		Invalidate(TRUE);
	}	
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CDIP_FinalView::OnColortogrey() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc *pDoc=GetDocument();
	if (pDoc->m_pDib!=NULL)
	{
		pDoc->m_pDib->Colortogrey();
	}
	Invalidate(NULL);
}

void CDIP_FinalView::OnTiquLap() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc *pDoc=GetDocument();
	if (pDoc->m_pDib!=NULL)
	{
		pDoc->m_pDib->TiquLaplacian();
	}
	Invalidate(NULL);
}

void CDIP_FinalView::OnTiquSobel() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc *pDoc=GetDocument();
	if (pDoc->m_pDib!=NULL)
	{
		pDoc->m_pDib->TiquSobel();
	}
	Invalidate(NULL);
}

void CDIP_FinalView::OnPinghua() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc *pDoc=GetDocument();
	if (pDoc->m_pDib!=NULL)
	{
		pDoc->m_pDib->Pinghua();
	}
	Invalidate(NULL);	
}

void CDIP_FinalView::OnRegionGrow() 
{
	// TODO: Add your command handler code here
	CDIP_FinalDoc *pDoc=GetDocument();
	if (pDoc->m_pDib!=NULL)
	{
		pDoc->m_pDib->RegionGrow();
	}
	Invalidate(NULL);
}
