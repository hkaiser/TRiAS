/////////////////////////////////////////////////////////////////////////////
// CPictView view

#include "TrackObject.h"

class CPictView : public CScrollView
{
protected:
	CRGBtoHSB* m_pRGBtoHSB;
	CExpandColorChannel* m_pExpandColorChannel;
	BOOL m_bRGB;
	int m_nChannel;
	void LoadFilters();
	BOOL ChangePicture();
	CFile			m_fileOfPicture;	// Bilddatei
	CMapStringToOb	m_mapOfPictures;	// benutzte Bilddateitypen
	CPicture*		m_pPicture;			// das aktuelle Bild

	int				m_nMode;			// Add,Edit,Delete
	int				m_fEnable;			// Statusflags f. A,E,D (in Implementierung)
	int				m_nObject;			// Objekttyp (GCP,Punkt,...)
	CFrameStatus*	m_pStatusBar;

	CMapStringToOb	m_listOfTrackObjects;
	CTrackObject	*m_pTrackObject;

	CPictView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CPictView)

// Attributes
public:

// Operations
protected:
	CMapMgrDoc*	GetDocument() const;
	void		RecalcScrollSizes();
	void		MakeTrackObjectVisible();
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPictView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPictView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CPictView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateModeAdd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateModeDel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateModeEdit(CCmdUI* pCmdUI);
	afx_msg void OnModeAdd();
	afx_msg void OnModeDel();
	afx_msg void OnModeEdit();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnGcpBl();
	afx_msg void OnUpdateGcpBl(CCmdUI* pCmdUI);
	afx_msg void OnGcpBr();
	afx_msg void OnUpdateGcpBr(CCmdUI* pCmdUI);
	afx_msg void OnGcpTl();
	afx_msg void OnUpdateGcpTl(CCmdUI* pCmdUI);
	afx_msg void OnGcpTr();
	afx_msg void OnUpdateGcpTr(CCmdUI* pCmdUI);
	afx_msg void OnObjLine();
	afx_msg void OnUpdateObjLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateObjPoint(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnGcp();
	afx_msg void OnUpdateGcp(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnObjPoint();
	afx_msg void OnRedraw();
	afx_msg void OnUpdateRedraw(CCmdUI* pCmdUI);
	afx_msg void OnColorcmdShowr();
	afx_msg void OnUpdateColorcmdShowr(CCmdUI* pCmdUI);
	afx_msg void OnColorcmdShowg();
	afx_msg void OnUpdateColorcmdShowg(CCmdUI* pCmdUI);
	afx_msg void OnColorcmdShowb();
	afx_msg void OnUpdateColorcmdShowb(CCmdUI* pCmdUI);
	afx_msg void OnColorcmdShowrgb();
	afx_msg void OnUpdateColorcmdShowrgb(CCmdUI* pCmdUI);
	afx_msg void OnColorcmdShowhue();
	afx_msg void OnUpdateColorcmdShowhue(CCmdUI* pCmdUI);
	afx_msg void OnColorcmdShowsat();
	afx_msg void OnUpdateColorcmdShowsat(CCmdUI* pCmdUI);
	afx_msg void OnColorcmdShowbri();
	afx_msg void OnUpdateColorcmdShowbri(CCmdUI* pCmdUI);
	afx_msg void OnMapProperties();
	//}}AFX_MSG
	afx_msg void OnInitStatusBar( CFrameStatus* pStatusbar );
	afx_msg void OnChangeMap( LPCTSTR lpszMapIdent );
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG
inline CMapMgrDoc* CPictView::GetDocument() const
	{ return (CMapMgrDoc*) m_pDocument; }
#endif
