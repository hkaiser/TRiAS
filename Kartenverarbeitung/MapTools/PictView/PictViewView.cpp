#include "stdafx.h"
#include "PictView.h"

#include "PictViewDoc.h"
#include "PictViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPictViewView

IMPLEMENT_DYNCREATE(CPictViewView, CScrollView)

BEGIN_MESSAGE_MAP(CPictViewView, CScrollView)
	//{{AFX_MSG_MAP(CPictViewView)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_WM_CREATE()
	ON_COMMAND(ID_REDRAW, OnRedraw)
	ON_UPDATE_COMMAND_UI(ID_REDRAW, OnUpdateRedraw)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPictViewView construction/destruction

CPictViewView::CPictViewView()
{
	// TODO: add construction code here
}

CPictViewView::~CPictViewView() {
}

/////////////////////////////////////////////////////////////////////////////
// CPictViewView drawing

void CPictViewView::OnDraw(CDC* pDC) {
	CPictViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here

	CPicture	*p;
	if( NULL == ( p = pDoc->m_pPicture ) )
		return;

	ASSERT_VALID( p );

	CRect	rcClient, rcPict;
	GetClientRect( rcClient );

	CPoint	ptScrollPos = GetScrollPosition();

//	rcClient.right = ( ( rcClient.right + 3 ) / 4 ) * 4 - 4;	// DWORD - boundary
	rcClient += ptScrollPos;
	rcPict.left = ptScrollPos.x;
	rcPict.right = rcPict.left + rcClient.Width();
	rcPict.top = ptScrollPos.y;
	rcPict.bottom = rcPict.top + rcClient.Height();

	TRY {
		const int nBandsize = 10;
		if( pDoc->IsBanding( ) ) {
			CRect	rcBand = rcClient;
			rcBand.bottom = rcBand.top + nBandsize;
			rcPict.left = ptScrollPos.x;
			rcPict.right = rcPict.left + rcClient.Width();
			rcPict.top = ptScrollPos.y;
			rcPict.bottom = rcPict.top + nBandsize;
			while( rcBand.top < rcClient.bottom ) {
				p->Draw( pDC, rcPict, rcBand, TRUE );
				rcBand.OffsetRect( 0, nBandsize - 1 );
				rcBand.bottom = min( rcBand.bottom, rcClient.bottom );
				rcPict.OffsetRect( 0, nBandsize - 1 );
				rcPict.bottom = rcPict.top + rcBand.Height();
			}
		} else {
			p->Draw( pDC, rcPict, rcClient, TRUE );
		}
	} CATCH( CPictException, e ) {
		lpictdll::ReportPictException( e );
		DELETE_EXCEPTION( e );
	}
	END_CATCH
}

/////////////////////////////////////////////////////////////////////////////
// CPictViewView printing

BOOL CPictViewView::OnPreparePrinting(CPrintInfo* pInfo) {
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPictViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) {
	// TODO: add extra initialization before printing
}

void CPictViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/) {
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// OLE Server support

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the server (not the container) causes the deactivation.
void CPictViewView::OnCancelEditSrvr() {
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CPictViewView diagnostics

#ifdef _DEBUG
void CPictViewView::AssertValid() const {
	CScrollView::AssertValid();
}

void CPictViewView::Dump(CDumpContext& dc) const {
	CScrollView::Dump(dc);
}

CPictViewDoc* CPictViewView::GetDocument() { // non-debug version is inline 
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPictViewDoc)));
	return (CPictViewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPictViewView message handlers

void CPictViewView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)  {
	// TODO: Add your specialized code here and/or call the base class
	switch( lHint ) {
	case PICT_OPENED : {
			CPicture	*pPict = GetDocument()->m_pPicture;

			CRect	rcClient;
			GetClientRect( rcClient );
			CSize	szScroll( 0, 0 );
			CSize	szLine( 0, 0 );
			CSize	szPage( 0, 0 );
			if( pPict ) {
				CRect	rcPict = pPict->GetPictRect();
				szScroll.cx = rcPict.Width() - 1;
				szScroll.cy = rcPict.Height() - 1;
				szPage.cx = ::MulDiv( rcClient.Width(), 2, 3 );
				szPage.cy = ::MulDiv( rcClient.Height(), 2, 3 );
				szLine.cx = ::MulDiv( szPage.cx, 1, 3 );
				szLine.cy = ::MulDiv( szPage.cy, 1, 3 );
			}
			SetScrollSizes( MM_TEXT, szScroll, szPage, szLine );
		}
		break;
	case PICT_PROPCHANGED : {
			Invalidate();
		}
		break;
	}
}

void CPictViewView::OnInitialUpdate()  {
	CScrollView::OnInitialUpdate();
}

int CPictViewView::OnCreate(LPCREATESTRUCT lpCreateStruct)  {
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	SetScrollSizes( MM_TEXT, CSize( 0, 0 ) );
	
	return 0;
}

void CPictViewView::OnRedraw()  {
	Invalidate();
}

void CPictViewView::OnUpdateRedraw(CCmdUI* pCmdUI)  {
	pCmdUI->Enable( NULL != GetDocument()->m_pPicture );
}
