// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.07.2000 22:49:44
//
// @doc
// @module TRiASPreviewView.cpp | Implementation of the <c CTRiASPreviewView> class

//
// Replaces MFC print preview toolbar with a prettier one
//
// Copyright (c) 1999 Robin J. Leatherbarrow, Erithacus Software Limited
// 
// Use and distribute freely, except: don't remove my name from the
// source or documentation; mark your changes; don't alter
// or remove this notice.
// No warranty of any kind, express or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Send bug reports, bug fixes, enhancements, requests, etc.,
// and I'll try to keep a version up to date.  I can be reached at:
//    robin@erithacus.com
//
// Resource Requirements:
//		Bitmap resources: IDB_PREV_* (see resource file)
//		Dialog resource:  IDD_PREVIEW
//		String resources: AFX_ID_PREVIEW_* (see resource file)
//
// Other requirements:
//		MappedBitmapButton.cpp, .h
//
// Usage: 
//		1. #include "MyPreviewView.h" into your view class
//		2. Add MyPreviewView.cpp and MappedBitmapButton.cpp to your project
//		3. Copy the above resources to your .RC file
//		4. Add the following message handler to your view class
//		   When called you get the improved print preview
//
//void CYourView::OnFileImprovedprintpreview() 
//{
//	// need to use CMyPreviewView class
//	CPrintPreviewState* pState = new CPrintPreviewState;
//
//	if (!DoPrintPreview(IDD_PREVIEW, this, RUNTIME_CLASS(CMyPreviewView), pState))
//	{
//		TRACE0("Error: OnFileImprovedprintpreview failed.\n");
//		AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
//		delete pState;      // preview failed to initialize, delete State now
//	}
//}
//
// Known issues
// ------------
// The version of CMappedBitmapButton supplied in this sample code uses
// CBitmap::LoadMappedBitmap to map system colors, which in turn uses ::CreateMappedBitmap
// to do the mapping.
// We have found that calls to ::CreateMappedBitmap can very occasionally cause NT4 to crash for
// no good reason, and so in our production code we use a "home made" LoadMappedBitmap
// replacement. 


#include "StdAfx.h"

#if defined(_USE_PRINT_PREVIEW)

#include "AfxPriv.h"
#include "AfxRes.h"

#include "fakemfc.h"

#include "TRiASDoc.h"
#include "TRiASPreviewView.h"
#include "ViewPrintPreview.h"

IMPLEMENT_DYNCREATE(CTRiASPreviewView, CPreviewView)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTRiASPreviewView
CTRiASPreviewView::CTRiASPreviewView()
{
	INITSTRUCT(m_PL, PRINTLAYOUT);
	INITSTRUCT(m_PD, PRINTLAYOUTDIALOG);
	INITSTRUCT(m_PP, PRINTPREVIEW);

	m_PL.m_pHeadline = m_cbBuffer;
	m_PL.m_lHeadlineLen = sizeof(m_cbBuffer);

	m_PD.m_pLayout = &m_PL;
	m_PP.pLayout = &m_PL;

	m_hAccel = LoadAccelerators (g_hInstance, MAKEINTRESOURCE(IDR_PRINTPREVIEW_FRAME));
}

CTRiASPreviewView::~CTRiASPreviewView()
{
	DEX_EndPrintPreview (m_PP);
}

void CTRiASPreviewView::OnDisplayPageNumber(UINT nPage, UINT nPagesDisplayed)
{
	CPreviewView::OnDisplayPageNumber( nPage, nPagesDisplayed );
}

BEGIN_MESSAGE_MAP(CTRiASPreviewView, CPreviewView)
	//{{AFX_MSG_MAP(CTRiASPreviewView)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_COMMAND(ID_PREVIEW_REPAINT, OnPreviewRepaint)
	//}}AFX_MSG_MAP
	ON_COMMAND(AFX_ID_PREVIEW_PRINT, OnPreviewPrint)
	ON_COMMAND(AFX_ID_PREVIEW_CLOSE, OnPreviewClose)
	ON_COMMAND(ID_PREVIEW_CONFIG, OnPreviewConfig)
	ON_UPDATE_COMMAND_UI(AFX_ID_PREVIEW_NUMPAGE, OnUpdateNumPageChange)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPreviewView drawing

/////////////////////////////////////////////////////////////////////////////
// CMyPreviewView diagnostics

#ifdef _DEBUG
void CTRiASPreviewView::AssertValid() const
{
	CPreviewView::AssertValid();
}

void CTRiASPreviewView::Dump(CDumpContext& dc) const
{
	CPreviewView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyPreviewView message handlers

void CTRiASPreviewView::OnUpdateNumPageChange(CCmdUI* pCmdUI)
{
	UINT nPages = m_nZoomState == ZOOM_OUT ? m_nPages : m_nZoomOutPages;

	if (m_bOne) {
		if (nPages == 1) {
			// need to swap to show 2 pages
			m_onetwo.LoadBitmap(IDB_PREV_TWO);
			m_bOne = FALSE;
			m_onetwo.Invalidate();
			}
		}
	else {
		if (nPages != 1) {
			// need to swap to show 1 page
			m_onetwo.LoadBitmap(IDB_PREV_ONE);
			m_bOne = TRUE;
			m_onetwo.Invalidate();
			}
		}

	// enable it only if valid to display another page and not zoomed
	pCmdUI->Enable(m_nZoomState == ZOOM_OUT && m_nMaxPages != 1 &&
		(m_pPreviewInfo->GetMaxPage() > 1 || m_nPages > 1));
}

int CTRiASPreviewView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPreviewView::OnCreate(lpCreateStruct) == -1)
		return -1;

// Rückverkettung zwisch TRiASView und TRiASPreviewView herstellen
CCreateContext *pContext = (CCreateContext *)lpCreateStruct -> lpCreateParams;
CViewPrintPreview *pPreviewView = (CViewPrintPreview *)pContext -> m_pLastView;

	ASSERT_VALID(pPreviewView);
	ASSERT(pPreviewView -> IsKindOf(RUNTIME_CLASS(CViewPrintPreview)));
	pPreviewView -> EstablishViewConnection(this);

// sonstige Controls fertig initialisieren
	m_pToolBar -> EnableToolTips(TRUE);

	m_bOne = FALSE;		 // the default is to show 2 pages, set in the dialog text

	m_print.AutoLoad (AFX_ID_PREVIEW_PRINT, m_pToolBar, IDB_PREV_PRINT);
	m_config.AutoLoad (ID_PREVIEW_CONFIG, m_pToolBar, IDB_PREV_CONFIG);
	m_next.AutoLoad (AFX_ID_PREVIEW_NEXT, m_pToolBar, IDB_PREV_NEXT);
	m_previous.AutoLoad (AFX_ID_PREVIEW_PREV, m_pToolBar, IDB_PREV_PREVIOUS);
	m_onetwo.AutoLoad (AFX_ID_PREVIEW_NUMPAGE, m_pToolBar, IDB_PREV_TWO);
	m_zoomIn.AutoLoad (AFX_ID_PREVIEW_ZOOMIN, m_pToolBar, IDB_PREV_ZOOMIN);
	m_zoomOut.AutoLoad (AFX_ID_PREVIEW_ZOOMOUT, m_pToolBar, IDB_PREV_ZOOMOUT);
	m_repaint.AutoLoad (ID_PREVIEW_REPAINT, m_pToolBar, IDB_PREV_REPAINT);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Schließen mit anschließendem Drucken
void CTRiASPreviewView::OnPreviewPrint()
{
	OnPreviewClose();               // force close of Preview

// cause print (can be overridden by catching the command)
CWnd* pMainWnd = AfxGetThread()->m_pMainWnd;

	ASSERT_VALID(pMainWnd);
	pMainWnd -> PostMessage(WM_COMMAND, IDM_FILE_PRINT);	// Drucken auslösen
}

void CTRiASPreviewView::OnPreviewClose()
{
// während dem Zeichnen darf nicht geschlossen werden
CViewPrintPreview *pView = (CViewPrintPreview *)m_pOrigView;

	ASSERT_VALID(pView);
	ASSERT(pView -> IsKindOf(RUNTIME_CLASS(CViewPrintPreview)));

CTRiASView *pTView = (CTRiASView *)(pView -> m_pTarget);

	ASSERT_VALID(pTView);
	ASSERT(pTView -> IsKindOf(RUNTIME_CLASS(CTRiASView)));

	if (pTView -> m_fPreviewing) {
	CWnd* pMainWnd = AfxGetThread()->m_pMainWnd;

		ASSERT_VALID(pMainWnd);
		pMainWnd -> PostMessage (WM_COMMAND, IDM_CANCEL);	// Zeichnen abbrechen
		return;		// Fenster nicht schließen
	}

// wenn wirklich schließen, dann wirklich schließen
	CPreviewView::OnPreviewClose();
}

///////////////////////////////////////////////////////////////////////////////
// Seite einrichten (PrintLayout-Dialog anzeigen und auswerten)
void CTRiASPreviewView::OnPreviewConfig()
{
	m_PD.m_hWndParent = m_pPrintView -> GetSafeHwnd();
	m_PD.m_pLayout -> m_lHeadlineLen = sizeof(m_cbBuffer);

CViewPrintPreview *pPreview = (CViewPrintPreview *)m_pOrigView;

	ASSERT_VALID(pPreview);
	ASSERT(pPreview -> IsKindOf(RUNTIME_CLASS(CViewPrintPreview)));
	if (DEX_ShowPrintLayoutDlg(m_PD)) {
	// Neuinitialisierung veranlassen
		m_PP.pRenderDb = NULL;
		DEX_EndPrintPreview (m_PP);
		
		m_dcPrint.Detach();         // print DC is deleted by CPrintInfo destructor
		DELETE_OBJ(m_pPreviewInfo);	// get rid of preview info
		DELETE_OBJ(m_pPreviewDC);	// Get rid of preview DC object
		
		SetPrintView (m_pPrintView);
		
	// fertig melden
		pPreview -> HasConfig();
	} 
	else if (!pPreview -> GetHasConfig()) {
	// Dialog abgebrochen --> Druckvorschau schließen
	CWnd* pMainWnd = AfxGetThread()->m_pMainWnd;

		ASSERT_VALID(pMainWnd);
		pMainWnd -> PostMessage (WM_COMMAND, AFX_ID_PREVIEW_CLOSE);	// Zeichnen abbrechen
	}
}

void CTRiASPreviewView::OnPaint() 
{
CViewPrintPreview *pView = (CViewPrintPreview *)m_pOrigView;

	ASSERT_VALID(pView);
	ASSERT(pView -> IsKindOf(RUNTIME_CLASS(CViewPrintPreview)));

CTRiASView *pTView = (CTRiASView *)(pView -> m_pTarget);

	ASSERT_VALID(pTView);
	ASSERT(pTView -> IsKindOf(RUNTIME_CLASS(CTRiASView)));

	if (!pTView -> m_fPreviewing)
		CPreviewView::OnPaint();	// nur zeichnen, wenn nicht bereits gezeichnet wird
	else {
	CPaintDC dc(this);	// CPaintDC needed for initialization purposes of hDC

		;
	}
}

void CTRiASPreviewView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
CViewPrintPreview *pView = (CViewPrintPreview *)m_pOrigView;

	ASSERT_VALID(pView);
	ASSERT(pView -> IsKindOf(RUNTIME_CLASS(CViewPrintPreview)));

CTRiASView *pTView = (CTRiASView *)(pView -> m_pTarget);

	ASSERT_VALID(pTView);
	ASSERT(pTView -> IsKindOf(RUNTIME_CLASS(CTRiASView)));

	if (pTView -> m_fPreviewing)
		pInfo -> m_bContinuePrinting = FALSE;	
	CPreviewView::OnPrepareDC(pDC, pInfo);
}

void CTRiASPreviewView::OnPreviewRepaint() 
{
	InvalidateRect(NULL);		// alles neu zeichnen
}

///////////////////////////////////////////////////////////////////////////////
// Accels behandeln

BOOL CTRiASPreviewView::PreTranslateMessage(MSG* pMsg) 
{
	if (::TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
		return TRUE;
	return CPreviewView::PreTranslateMessage(pMsg);
}

#endif // defined(_USE_PRINT_PREVIEW)


