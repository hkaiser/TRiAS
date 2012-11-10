// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.07.2000 14:01:07
//
// @doc
// @module ViewPrintPreview.cpp | Implementation of the <c CViewPrintPreview> class

#include "stdafx.h"

#if defined(_USE_PRINT_PREVIEW)

#include "fakemfc.h"

#include "TRiASDoc.h"
#include "TRiASPreviewView.h"
#include "ViewPrintPreview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewPrintPreview

IMPLEMENT_DYNCREATE(CViewPrintPreview, CView)

CViewPrintPreview::CViewPrintPreview()
{
	m_pOldFrame = NULL;
	m_pTarget = NULL;
}

CViewPrintPreview::~CViewPrintPreview()
{
}

BEGIN_MESSAGE_MAP(CViewPrintPreview, CView)
	//{{AFX_MSG_MAP(CViewPrintPreview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewPrintPreview drawing

void CViewPrintPreview::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CViewPrintPreview diagnostics

#ifdef _DEBUG
void CViewPrintPreview::AssertValid() const
{
	CView::AssertValid();
}

void CViewPrintPreview::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewPrintPreview message handlers

void CViewPrintPreview::OnFilePrintPreview()
{
CPrintPreviewState* pState = new CPrintPreviewState;

	if (!DoPrintPreview(IDD_PREVIEW, this, RUNTIME_CLASS(CTRiASPreviewView), pState))
	{
		TRACE0("Error: OnFilePrintPreview failed.\n");
		AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
		delete pState;      // preview failed to initialize, delete State now
	}
}

// Rückverkettung von der TRiASView zur TRiASPreviewView herstellen, um bei der Vorschau
// Zugriff auf die Parameter der derzeit auszugebeneden Seite zu haben (Größe, Lage etc.)
void CViewPrintPreview::EstablishViewConnection (CPreviewView *pPreviewView)
{
	ASSERT(pPreviewView->IsKindOf(RUNTIME_CLASS(CTRiASPreviewView)));
	ASSERT_VALID(m_pTarget);
	
	m_pTarget -> m_pPreviewView = (CTRiASPreviewView *)pPreviewView;
}

BOOL CViewPrintPreview::OnPreparePrinting(CPrintInfo* pInfo) 
{
	return DoPreparePrinting(pInfo);
}

void CViewPrintPreview::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	m_pTarget -> OnBeginPrinting(pDC, pInfo);
}

void CViewPrintPreview::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	m_pTarget -> OnPrint(pDC, pInfo);
}

void CViewPrintPreview::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	m_pTarget -> OnEndPrinting(pDC, pInfo);
}

void CViewPrintPreview::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView) 
{
// restore (modified) position and size 
CRect rcFrame;

	GetParentFrame() -> GetWindowRect (rcFrame);

// end print preview
	CView::OnEndPrintPreview(pDC, pInfo, point, pView);

// Show the original frame
	m_pOldFrame -> SetWindowPos (&wndTop, rcFrame.left, rcFrame.top, rcFrame.Width(), rcFrame.Height(), SWP_SHOWWINDOW);
	AfxGetApp() -> m_pMainWnd = m_pOldFrame;		// Restore main frame pointer
	m_pTarget -> m_bPrintPreview = FALSE;

// Kill parent frame and itself
	GetParentFrame() -> DestroyWindow();
}

void CViewPrintPreview::HasConfig()
{
	_ASSERTE(NULL != m_pTarget);
	m_pTarget -> HasConfig();
}

BOOL CViewPrintPreview::GetHasConfig()
{
	_ASSERTE(NULL != m_pTarget);
	return m_pTarget -> GetHasConfig();
}

#endif // defined(_USE_PRINT_PREVIEW)