// DIP_FinalView.h : interface of the CDIP_FinalView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIP_FINALVIEW_H__5DB508F8_7AB4_40FF_8296_B24D92766628__INCLUDED_)
#define AFX_DIP_FINALVIEW_H__5DB508F8_7AB4_40FF_8296_B24D92766628__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDIP_FinalView : public CView
{
protected: // create from serialization only
	CDIP_FinalView();
	DECLARE_DYNCREATE(CDIP_FinalView)

// Attributes
public:
	CDIP_FinalDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDIP_FinalView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDIP_FinalView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDIP_FinalView)
	afx_msg void OnInvert();
	afx_msg void OnLiner();
	afx_msg void OnHgdlg();
	afx_msg void OnHistoave();
	afx_msg void OnPeppernoise();
	afx_msg void OnRandomnoise();
	afx_msg void OnGradsharp();
	afx_msg void OnLapchange();
	afx_msg void OnMidchange();
	afx_msg void OnSuofang();
	afx_msg void OnMirror();
	afx_msg void OnMirror2();
	afx_msg void OnXuanzhuan();
	afx_msg void OnPingyi();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnErzhi();
	afx_msg void OnFushi();
	afx_msg void OnPengzhang();
	afx_msg void OnTiqu();
	afx_msg void OnJiabianjie();
	afx_msg void OnTiqu2();
	afx_msg void OnFileSave();
	afx_msg void OnWeicai();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnColortogrey();
	afx_msg void OnTiquLap();
	afx_msg void OnTiquSobel();
	afx_msg void OnPinghua();
	afx_msg void OnRegionGrow();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool m_IsSelected;
	bool m_LRchoose;
	CPoint m_point;
};

#ifndef _DEBUG  // debug version in DIP_FinalView.cpp
inline CDIP_FinalDoc* CDIP_FinalView::GetDocument()
   { return (CDIP_FinalDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIP_FINALVIEW_H__5DB508F8_7AB4_40FF_8296_B24D92766628__INCLUDED_)
