// cptvw.cpp : implementation file
//

#include "bscriptp.hxx"
#include "bscript.h"
#include "cptvw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCaptionView

IMPLEMENT_DYNCREATE(CCaptionView, CView)

CCaptionView::CCaptionView()
{
}

CCaptionView::~CCaptionView()
{
}


BEGIN_MESSAGE_MAP(CCaptionView, CView)
	//{{AFX_MSG_MAP(CCaptionView)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaptionView drawing

void CCaptionView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here	
	CRect rect;
	GetClientRect(rect);	
	// Andere Backroundfarbe einstellen
	CBrush Brush(GetSysColor(COLOR_BTNFACE));
	CBrush *poldBrush = pDC -> SelectObject(&Brush);
	// Anderen Font einstellen
	CFont Font;	Font.Attach ((HFONT)GetStockObject (ANSI_VAR_FONT));
	CFont* pFontOld = pDC -> SelectObject(&Font);
	Font.Detach();

	// WindowRect füllen	
	pDC -> FillRect(rect, &Brush);						
	// Backroundfarbe für Text setzen
	pDC -> SetBkColor(GetSysColor(COLOR_BTNFACE));		
	// Text setzen
	pDC	-> DrawText	(m_strCaption, -1, rect, 
				DT_LEFT | DT_VCENTER | DT_SINGLELINE);		
	// Rücksetzen der alten Objekte
	pDC -> SelectObject(&poldBrush);
	pDC -> SelectObject(&pFontOld);
}

/////////////////////////////////////////////////////////////////////////////
// CCaptionView diagnostics

#ifdef _DEBUG
void CCaptionView::AssertValid() const
{
	CView::AssertValid();
}

void CCaptionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCaptionView message handlers

BOOL CCaptionView::OnEraseBkgnd(CDC* pDC) 
{
	return CView::OnEraseBkgnd(pDC);
}

BOOL CCaptionView::PreCreateWindow(CREATESTRUCT& cs) 
{
	bool f = CView::PreCreateWindow(cs);
	cs.style &= ~(WS_BORDER);	
	return f;
}

bool CCaptionView::SetCaption(LPCSTR lpcstrCaption)
{
	ASSERT(lpcstrCaption);
	if (NULL == lpcstrCaption) return false;
	m_strCaption = lpcstrCaption;
	return true;
}
