// PreviewDialog.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"

#include <AfxPriv.h>
#include "PrintAnlage.h"
#include "PreviewDialog.h"

#include "RectDlg.h"
#include "ViewPortDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreviewDialog dialog


CPreviewDialog::CPreviewDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPreviewDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPreviewDialog)
	m_strPageText = _T("");
	//}}AFX_DATA_INIT
	m_bCreated = FALSE;
	m_pPreviewDC = NULL;
	m_pPreviewInfo = NULL;
	m_pPageInfo = m_pageInfoArray;
	m_nMaxPages = 2;
	m_cxPixelsPerInch = 0;
	m_cyPixelsPerInch = 0;
	m_nZoomState = ZOOM_OUT;
	m_pPA = NULL;

	m_rclClipBox.left   = -1L;
	m_rclClipBox.right  = -1L;
	m_rclClipBox.top    = -1L;
	m_rclClipBox.bottom = -1L;
	m_rclFrame     = m_rclClipBox;
	m_rclPage      = m_rclClipBox;
	m_rclRectangle = m_rclClipBox;

	m_bUseMetaFile = FALSE;
	m_hdcMetaFile = NULL;

	m_bWithOptionDialog = FALSE;
}

CPreviewDialog::~CPreviewDialog()
{
	ASSERT( m_pPreviewDC );
	ASSERT( m_pPreviewInfo );
	delete m_pPreviewDC;
	delete m_pPreviewInfo;
	if ( m_pPA )	delete m_pPA;
	m_pPA = NULL;
	if ( m_hdcMetaFile )	DeleteEnhMetaFile( m_hdcMetaFile );
	m_hdcMetaFile = NULL;
}

void CPreviewDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreviewDialog)
	DDX_Control(pDX, IDC_PREV_PAGE, m_btnPrevPage);
	DDX_Control(pDX, IDC_NEXT_PAGE, m_btnNextPage);
	DDX_Control(pDX, IDC_RECT, m_btnRect);
	DDX_Control(pDX, IDC_SEITEN, m_txtPageText);
	DDX_Control(pDX, IDC_2SEITEN, m_btn2Seiten);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_COMBO1, m_cbSeiten);
	DDX_Control(pDX, IDC_FRAME0, m_wndFrame0);
	DDX_Text(pDX, IDC_SEITEN, m_strPageText);
	//}}AFX_DATA_MAP
	m_bCreated = TRUE;
}


BEGIN_MESSAGE_MAP(CPreviewDialog, CDialog)
	//{{AFX_MSG_MAP(CPreviewDialog)
	ON_WM_GETMINMAXINFO()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, OnOk)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangePage)
	ON_BN_CLICKED(IDC_2SEITEN, OnZweiSeiten)
	ON_BN_CLICKED(IDC_RECT, OnRect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreviewDialog message handlers

void CPreviewDialog::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	if ( m_cxPixelsPerInch == 0 )
	{
		m_cxPixelsPerInch = dc.GetDeviceCaps( LOGPIXELSX );
		m_cyPixelsPerInch = dc.GetDeviceCaps( LOGPIXELSY );
	}

	CRect	rectFrame, rectBlatt;
	double	f1, f2;
	int		dx, dy;

	m_wndFrame0.GetWindowRect( &rectFrame );
	ScreenToClient( rectFrame );
	rectFrame.left   += 5;
	rectFrame.right  -= 5;
	rectFrame.top    += 5;
	rectFrame.bottom -= 5;

	dc.SetMapMode( MM_TEXT );

	rectBlatt.top    = 0;
	rectBlatt.left   = 0;
	rectBlatt.bottom = m_dcPrint.GetDeviceCaps( VERTRES );
	rectBlatt.right  = m_dcPrint.GetDeviceCaps( HORZRES );

	f1 = ( 0.9 * rectFrame.Width()) / rectBlatt.Width();
	f2 = ( 0.9 * rectFrame.Height()) / rectBlatt.Height();
	if ( f1 > f2 )	f1 = f2;

	rectBlatt.bottom = int( rectBlatt.bottom * f1 );
	rectBlatt.right  = int( rectBlatt.right * f1 );
	rectBlatt.top    = 0;
	rectBlatt.left   = 0;

	dx = rectFrame.left + int(( rectFrame.Width() - rectBlatt.Width()) / 2 );
	dy = rectFrame.top + int(( rectFrame.Height() - rectBlatt.Height()) / 2 );

	rectBlatt.bottom += dy;
	rectBlatt.left   += dx;
	rectBlatt.top    += dy;
	rectBlatt.right  += dx;

//	dc.Rectangle( &rectBlatt );
	dc.SetMapMode( MM_LOMETRIC );

	OnDraw( &dc );

	EndWaitCursor();
}

void CPreviewDialog::OnGetMinMaxInfo( MINMAXINFO FAR* lpMMI )
{
	CDialog::OnGetMinMaxInfo( lpMMI );

//	POINT ptReserved;
//	POINT ptMaxSize;
//	POINT ptMaxPosition;
//	POINT ptMinTrackSize;
//	POINT ptMaxTrackSize;
	lpMMI -> ptMinTrackSize.x = 350;
	lpMMI -> ptMinTrackSize.y = 300;
}	// OnGetMinMaxInfo

void CPreviewDialog::OnOk() 
{
	CDialog::OnOK();
}

void CPreviewDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize( nType, cx, cy );

	// wenn Dialog noch nicht komplett, war's das
	if ( !m_bCreated ) return;

	// CScrollView handles everything if zoomed in.
	if (m_nZoomState == ZOOM_OUT)
	{
		// Force recalc of scale ratios on next draw
		for (UINT i = 0; i < m_nMaxPages; i++)
			m_pPageInfo[i].sizeScaleRatio.cx = 0;	// zero scale ratios

//		CView::OnSize(nType, cx, cy);       // No scroll functionality
	}
//	else
//	{
//		// adjust scroll size to size of page
//		m_pageDev.cx = cx;
//		m_pageDev.cy = cy;
//		m_lineDev.cx = cx / 10;
//		m_lineDev.cy = cy / 10;
//		CScrollView::OnSize(nType, cx, cy);
//	}

	int		x, y, h, w, dx;
	int		offsetX = 0;
	CRect	rect, rect1;

	m_btnOK.GetWindowRect( &rect );
	x = 2;
	y = rect.Height() + 6;
	h = cy - y - rect.Height();		// -2
	w = cx - x - 2;
	m_wndFrame0.SetWindowPos( NULL, x, y, w, h, SWP_NOZORDER );

	m_cbSeiten.GetWindowRect( &rect1 );
	dx = rect.Width() + rect1.Width() + 2 * rect.Width();
	if ( dx < cx )	offsetX = rect.Height();
	else			offsetX = 0;

	x = cx - rect.Width() - 2 - offsetX;
	y = 3;
	h = rect.Height();
	w = rect.Width();
	m_btnOK.SetWindowPos( NULL, x, y, w, h, SWP_NOZORDER );

	x = cx - rect.Width() * 2 - 10 - offsetX;
	y = 3;
	h = rect.Height();
	w = rect.Width();
	m_btnRect.SetWindowPos( NULL, x, y, w, h, SWP_NOZORDER );

	x = 2 + offsetX;
	y = 3;
	h = rect1.Height();
	w = rect1.Width();
	m_cbSeiten.SetWindowPos( NULL, x, y, w, h, SWP_NOZORDER );

	m_txtPageText.GetWindowRect( &rect1 );
	x = 3;
	y = cy - rect.Height() + 2;
	h = rect1.Height();
	w = rect1.Width();
	m_txtPageText.SetWindowPos( NULL, x, y, w, h, SWP_NOZORDER );

	if ( offsetX > 0 )		m_btn2Seiten.ShowWindow( SW_SHOW );
	else					m_btn2Seiten.ShowWindow( SW_HIDE );

	RedrawWindow();
}	// OnSize

BOOL CPreviewDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if ( m_bWithOptionDialog )	m_btnRect.ShowWindow( SW_SHOW );

	int				i;
	CxString		text, ide, enr;
	CPrintAnlage	*pPA;
	char			c;

	ShowWindow( SW_SHOWMAXIMIZED );

	m_strEqIDE.Empty();
	if ( m_pPrintListe )
	{
		for ( i = 0; i < m_pPrintListe -> GetSize(); i++ )
		{
			pPA = NULL;
			m_pArray.SetAtGrow( i, (void*)pPA );
			text = m_pPrintListe -> GetAt( i );
			if ( !text.IsEmpty())
			{
				ide = text.Mid( 2 );
				c = text[0];
				ide.Teilen( enr, ide, ')' );
				text.Empty();

				if ( m_strEqIDE.IsEmpty())	m_strEqIDE = ide;
				else						m_strEqIDE = Identisch( ide, m_strEqIDE );
				switch ( c )
				{
				case '1':
					text = " Erfassungsblatt Seite 1";
					pPA = new CPrintAnlage1( ide, enr.Long());
					break;
				case '2':
					text = " Erfassungsblatt Seite 2";
					pPA = new CPrintAnlage2( ide, enr.Long());
					break;
				case '3':
					text = " Erfassungsblatt Seite 3";
					pPA = new CPrintAnlage3( ide, enr.Long());
					break;
				case '4':
					text = " Beitragsbescheid";
					pPA = new CPrintAnlage7( ide, enr.Long());
					pPA -> m_cKennung = '7';
					break;
				case '5':
					text = " InfoBrief Beitragsbescheid";
					pPA = new CPrintAnlage7( ide, enr.Long());
					pPA -> m_cKennung = '8';
					break;
				case '6':
					text = " Anlage Beitragsbescheid";
					pPA = new CPrintAnlage4( ide, enr.Long());
					break;
				case '7':
					text = " Bescheid Niederschlagswassergebühr";
					pPA = new CPrintAnlage7( ide, enr.Long());
					pPA -> m_cKennung = '9';
					break;
				case '8':
					text = " InfoBrief Gebührenbescheid";
					pPA = new CPrintAnlage7( ide, enr.Long());
					pPA -> m_cKennung = 'A';
					break;
				case '9':
					text = " Anlage Gebührenbescheid";
					pPA = new CPrintAnlage5( ide, enr.Long());
					break;
				case 'A':
					text = " Anlage - öffentliche Flächen -";
					pPA = new CPrintAnlage6( ide, enr.Long());
					break;
				case 'B':
					text = " Massstabsgerechte Lageskizze -";
					pPA = new CPrintAnlage8( ide, enr.Long());
					break;
				}
				ide += text;
				m_cbSeiten.AddString( ide );
				if ( pPA != NULL )		m_pArray.SetAtGrow( i, (void*)pPA );
			}
		}
	}

	if ( m_cbSeiten.GetCount())		m_cbSeiten.SetCurSel( 0 );

	m_pPreviewDC = new CPreviewDC;		// must be created before any
										// possible error returns
	if ( m_pPreviewInfo == NULL )
	{
		// allocate preview info
		m_pPreviewInfo = new CPrintInfo;
		m_pPreviewInfo -> m_pPD -> SetHelpID(AFX_IDD_PRINTSETUP);
		m_pPreviewInfo -> m_pPD -> m_pd.Flags |= PD_PRINTSETUP;
		m_pPreviewInfo -> m_pPD -> m_pd.Flags &= ~PD_RETURNDC;

		m_pPreviewInfo -> m_bPreview = TRUE;	// signal that this is preview
		ASSERT( m_pPreviewInfo -> m_pPD != NULL );
	}

	if ( !OnPreparePrinting( m_pPreviewInfo ))	return FALSE;

#ifdef _DEBUG
	if ( m_pPreviewInfo -> m_pPD -> m_pd.hDC == NULL)
	{
		TRACE0("Error: hDC not set for printing --\n");
		TRACE0("\tDid you remember to call DoPreparePrinting?\n");
		ASSERT(FALSE);		// common mistake gets trapped here
	}
#endif //_DEBUG

	m_dcPrint.Attach( m_pPreviewInfo -> m_pPD -> m_pd.hDC );
	m_pPreviewDC -> SetAttribDC( m_pPreviewInfo -> m_pPD -> m_pd.hDC );
	m_pPreviewDC -> m_bPrinting = TRUE;
	m_dcPrint.m_bPrinting = TRUE;

	m_dcPrint.SaveDC();		// Save pristine state of DC

	HDC hDC = ::GetDC( m_hWnd );
	m_pPreviewDC -> SetOutputDC( hDC );
//	m_pPrintView -> OnBeginPrinting( m_pPreviewDC, m_pPreviewInfo );
	OnBeginPrinting( m_pPreviewDC, m_pPreviewInfo );
	m_pPreviewDC -> ReleaseOutputDC();
	::ReleaseDC( m_hWnd, hDC );

	m_dcPrint.RestoreDC( -1 );	// restore to untouched state

	// Get Pixels per inch from Printer
	m_sizePrinterPPI.cx = m_dcPrint.GetDeviceCaps( LOGPIXELSX );
	m_sizePrinterPPI.cy = m_dcPrint.GetDeviceCaps( LOGPIXELSY );

	m_nPages = m_pPreviewInfo -> m_nNumPreviewPages;
	if ( m_nPages == 0 )
		m_nPages = 1;
	else if ( m_nPages > m_nMaxPages )
		m_nPages = m_nMaxPages;		// Sanity Check!

	m_nZoomOutPages = m_nPages;

//	SetScrollSizes( MM_TEXT, CSize( 1, 1 ));	// initialize mapping mode only

//	if ( m_pPreviewInfo -> GetMaxPage() < 0x8000 &&
//		m_pPreviewInfo -> GetMaxPage() - m_pPreviewInfo -> GetMinPage() <= 32767U )
//		SetScrollRange( SB_VERT, m_pPreviewInfo -> GetMinPage(),
//						m_pPreviewInfo -> GetMaxPage(), FALSE );
//	else
//		ShowScrollBar( SB_VERT, FALSE );	// if no range specified, or too
//											// large don't show

	SetCurrentPage( m_pPreviewInfo -> m_nCurPage, TRUE );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPreviewDialog::DestroyWindow() 
{
//	m_pToolBar -> DestroyWindow();
//	m_pToolBar = NULL;

	m_pPreviewInfo -> m_nCurPage = m_nCurrentPage;
	OnEndPrintPreview( m_pPreviewDC, m_pPreviewInfo, CPoint(0, 0));

	return CDialog::DestroyWindow();
}

#define PREVIEW_MARGIN  8
#define PREVIEW_PAGEGAP 8

BOOL CPreviewDialog::OnPreparePrinting( CPrintInfo* pInfo )
{
	ASSERT( pInfo != NULL );
	ASSERT( pInfo -> m_pPD != NULL );

	// don't prompt the user if we're doing print preview, printing directly,
	// or printing via IPrint and have been instructed not to ask

	CWinApp* pApp = AfxGetApp();
	if ( pInfo -> m_bPreview || pInfo -> m_bDirect ||
		( pInfo -> m_bDocObject && !( pInfo -> m_dwFlags & PRINTFLAG_PROMPTUSER )))
	{
		if ( pInfo -> m_pPD -> m_pd.hDC == NULL )
		{
			// if no printer set then, get default printer DC and create DC without calling
			// print dialog.
			if ( !pApp -> GetPrinterDeviceDefaults( &pInfo -> m_pPD -> m_pd ))
			{
				// bring up dialog to alert the user they need to install a printer.
				if ( !pInfo -> m_bDocObject || ( pInfo -> m_dwFlags & PRINTFLAG_MAYBOTHERUSER ))
					if ( pApp -> DoPrintDialog( pInfo -> m_pPD ) != IDOK )
						return FALSE;
			}

			if ( pInfo -> m_pPD -> m_pd.hDC == NULL )
			{
				// call CreatePrinterDC if DC was not created by above
				if ( pInfo -> m_pPD -> CreatePrinterDC() == NULL )
					return FALSE;
			}
		}

		// set up From and To page range from Min and Max
		pInfo -> m_pPD -> m_pd.nFromPage = (WORD)pInfo -> GetMinPage();
		pInfo -> m_pPD -> m_pd.nToPage = (WORD)pInfo -> GetMaxPage();
	}
	else
	{
		// otherwise, bring up the print dialog and allow user to change things
		// preset From-To range same as Min-Max range
		pInfo -> m_pPD -> m_pd.nFromPage = (WORD)pInfo -> GetMinPage();
		pInfo -> m_pPD -> m_pd.nToPage = (WORD)pInfo -> GetMaxPage();

		if ( pApp -> DoPrintDialog( pInfo -> m_pPD ) != IDOK )
			return FALSE;       // do not print
	}

	ASSERT( pInfo -> m_pPD != NULL );
	ASSERT( pInfo -> m_pPD -> m_pd.hDC != NULL );

	pInfo -> m_nNumPreviewPages = pApp -> m_nNumPreviewPages;
	VERIFY( pInfo -> m_strPageDesc.LoadString( AFX_IDS_PREVIEWPAGEDESC ));
	return TRUE;
}

void CPreviewDialog::OnBeginPrinting( CDC* pDC, CPrintInfo* pInfo )
{
	ASSERT( m_pPA == NULL );
	m_pPA = new CPrintAnlage1( "XX", 0L );
	m_pPA -> CreateStaticMembers( pDC, m_strEqIDE );

	if ( pInfo )
	{
		pInfo -> SetMaxPage( m_pPrintListe -> GetSize());
		pInfo -> m_strPageDesc.LoadString( IDS_PREV_PAGE_DESC );

		if ( m_pPrintListe -> GetSize() == 0 )	pInfo -> SetMaxPage( 1 );
	}
}

void CPreviewDialog::OnEndPrinting( CDC* pDC, CPrintInfo* pInfo )
{
/*	Die Freigabe erfolgt erst beim beenden des Programmes
	m_pPA -> DeleteStaticMembers();
	delete m_pPA;
*/
	m_pPA = NULL;
}

void CPreviewDialog::OnEndPrintPreview( CDC* pDC, CPrintInfo* pInfo, POINT point )
{
	ASSERT_VALID(pDC);

	OnEndPrinting( pDC, pInfo );
}

void CPreviewDialog::SetCurrentPage( UINT nPage, BOOL bClearRatios )
{
	m_nCurrentPage = nPage;
	if ( m_nCurrentPage > m_pPreviewInfo -> GetMaxPage())
		 m_nCurrentPage = m_pPreviewInfo -> GetMaxPage();
	if ( m_nCurrentPage < m_pPreviewInfo -> GetMinPage())
		 m_nCurrentPage = m_pPreviewInfo -> GetMinPage();

//	if ( m_nZoomState == ZOOM_OUT )
//		SetScrollPos(SB_VERT, m_nCurrentPage);

	if ( bClearRatios )
	{
		// Force Recalc of layout
		for ( UINT i = 0; i < m_nMaxPages; i++ )
			m_pPageInfo[i].sizeScaleRatio.cx = 0;	// zero scale ratios
	}

	Invalidate( TRUE );
}

static BOOL	g_bBreak = FALSE;

void CPreviewDialog::OnDraw( CDC* pDC )
{
	ASSERT_VALID( pDC );

	// don't do anything if not fully initialized
	if ( m_dcPrint.m_hDC == NULL )	return;
	if ( g_bBreak )					return;
	g_bBreak = TRUE;

	CPoint	ViewportOrg = pDC -> GetViewportOrg();

	CPen	rectPen;
	rectPen.CreatePen( PS_SOLID, 2, GetSysColor( COLOR_WINDOWFRAME ));
	CPen	shadowPen;
	shadowPen.CreatePen( PS_SOLID, 3, GetSysColor( COLOR_BTNSHADOW ));

	m_pPreviewInfo -> m_bContinuePrinting = TRUE;	// do this once each paint

	for ( UINT nPage = 0; nPage < m_nPages; nPage++ )
	{
		int	nSavedState = m_dcPrint.SaveDC();	// Save pristine state of DC

		// Use paint DC for print preview output
		m_pPreviewDC -> SetOutputDC( pDC -> GetSafeHdc());

		m_pPreviewInfo -> m_nCurPage = m_nCurrentPage + nPage;

		// Only call PrepareDC if within page range, otherwise use default
		// rect to draw page rectangle
		if ( m_nCurrentPage + nPage <= m_pPreviewInfo -> GetMaxPage())
//			m_pPrintView -> OnPrepareDC( m_pPreviewDC, m_pPreviewInfo );
			OnPrepareDC( m_pPreviewDC, m_pPreviewInfo );

		// Set up drawing rect to entire page (in logical coordinates)
		m_pPreviewInfo -> m_rectDraw.SetRect(0, 0,
				m_pPreviewDC -> GetDeviceCaps(HORZRES),
				m_pPreviewDC -> GetDeviceCaps(VERTRES));
		m_pPreviewDC -> DPtoLP( &m_pPreviewInfo -> m_rectDraw );

		// Draw empty page on screen

		pDC -> SaveDC();		// save the output dc state

		CSize*	pRatio = &m_pPageInfo[nPage].sizeScaleRatio;
		CRect*	pRect = &m_pPageInfo[nPage].rectScreen;

		if ( pRatio -> cx == 0 )
		{	// page position has not been determined
			PositionPage( nPage );		// compute page position
			if ( m_nZoomState != ZOOM_OUT )
				ViewportOrg = -GetDeviceScrollPosition();
		}

		pDC -> SetMapMode( MM_TEXT );	// Page Rectangle is in screen device coords
		pDC -> SetViewportOrg( ViewportOrg );
		pDC -> SetWindowOrg( 0, 0 );

		pDC -> SelectStockObject( HOLLOW_BRUSH );
		pDC -> SelectObject( &rectPen );
		pDC -> Rectangle( pRect );

		pDC -> SelectObject( &shadowPen );

		pDC -> MoveTo( pRect -> right + 1, pRect -> top + 3 );
		pDC -> LineTo( pRect -> right + 1, pRect -> bottom + 1 );
		pDC -> MoveTo( pRect -> left + 3, pRect -> bottom + 1 );
		pDC -> LineTo( pRect -> right + 1, pRect -> bottom + 1 );

		// erase background to white (most paper is white)
		CRect	rectFill = *pRect;
		rectFill.left += 1;
		rectFill.top += 1;
		rectFill.right -= 2;
		rectFill.bottom -= 2;
		::FillRect( pDC -> m_hDC, rectFill, (HBRUSH)GetStockObject( WHITE_BRUSH ));

		pDC -> RestoreDC( -1 );		// restore to synchronized state

		if ( !m_pPreviewInfo -> m_bContinuePrinting ||
			m_nCurrentPage + nPage > m_pPreviewInfo -> GetMaxPage())
		{
			m_pPreviewDC -> ReleaseOutputDC();
			m_dcPrint.RestoreDC( nSavedState );	// restore to untouched state

			// if the first page is not displayable, back up one page
			// but never go below 1
			if ( nPage == 0 && m_nCurrentPage > 1 )
				SetCurrentPage( m_nCurrentPage - 1, TRUE );
			break;
		}

		// Display page number
		OnDisplayPageNumber( m_nCurrentPage, nPage + 1 );

		// Set scale ratio for this page
		m_pPreviewDC -> SetScaleRatio( pRatio -> cx, pRatio -> cy );

		CSize	PrintOffset;
		VERIFY( m_pPreviewDC -> Escape( GETPRINTINGOFFSET, 0, NULL, (LPVOID)&PrintOffset ));
		m_pPreviewDC -> PrinterDPtoScreenDP((LPPOINT)&PrintOffset );
		PrintOffset += (CSize)pRect -> TopLeft();
		PrintOffset += CSize( 1, 1 );
		PrintOffset += (CSize)ViewportOrg;		// For Scrolling

		m_pPreviewDC -> SetTopLeftOffset( PrintOffset );
		m_sizeTopLeftOffset = PrintOffset;

		CPrintAnlage	*pPA;

		for ( int i = 0; i < m_pArray.GetSize(); i++ )
		{
			pPA = (CPrintAnlage*)m_pArray[i];
			if ( pPA )
				pPA -> SetTopLeftOffset( &m_sizeTopLeftOffset );
		}

		m_pPreviewDC -> ClipToPage();
//		m_pPrintView -> OnPrint( m_pPreviewDC, m_pPreviewInfo );
		PrintPage( m_pPreviewDC, m_pPreviewInfo, nPage );

		m_pPreviewDC -> ReleaseOutputDC();

		m_dcPrint.RestoreDC( nSavedState );		// restore to untouched state

	}

	rectPen.DeleteObject();
	shadowPen.DeleteObject();

	g_bBreak = FALSE;
}	// OnDraw

void CPreviewDialog::OnPrepareDC( CDC* pDC, CPrintInfo* pInfo )
{
	ASSERT_VALID(pDC);

//	if (m_nZoomState == ZOOM_OUT)
//		CView::OnPrepareDC(pDC, pInfo);
//	else if (m_pPageInfo[0].sizeScaleRatio.cx != 0)
//		CScrollView::OnPrepareDC(pDC, pInfo);

// CView::OnPrepareDC
	ASSERT_VALID(pDC);
	UNUSED(pDC);	// unused in release builds

	// Default to one page printing if doc length not known
	if (pInfo != NULL)
		pInfo -> m_bContinuePrinting =
			( pInfo -> GetMaxPage() != 0xffff || ( pInfo -> m_nCurPage == 1 ));
}	// OnPrepareDC

// Position Page...
// Generate a Screen MM_TEXT rectangle to enclose each page.  Dimensions
// of the rectangle must be 1 pixel Above and Left of the top/left corner
// of the page and the rectangle width and height must be THREE pixels
// larger than page in order to provide the correct placement of the
// two pixel border.
//
// This routine is called once for each page with the preview DC set up for
// that page

void CPreviewDialog::PositionPage( UINT nPage )
{
	CSize windowSize = CalcPageDisplaySize();

	VERIFY( m_dcPrint.Escape(GETPHYSPAGESIZE, 0, NULL,
		(LPVOID)&m_pPageInfo[nPage].sizeUnscaled ));

	CSize* pSize = &m_pPageInfo[nPage].sizeUnscaled;

	// Convert page size to screen coordinates
	pSize -> cx = MulDiv( pSize -> cx, m_cxPixelsPerInch, m_sizePrinterPPI.cx );
	pSize -> cy = MulDiv( pSize -> cy, m_cyPixelsPerInch, m_sizePrinterPPI.cy );

	m_pPageInfo[nPage].sizeZoomOutRatio = CalcScaleRatio( windowSize, *pSize );

	SetScaledSize( nPage );
}

CSize CPreviewDialog::CalcPageDisplaySize()
	// calculate the current page size
	//  set 'm_nSecondPageOffset' to start of second page
	// return size of current page less margins
{
	CSize	windowSize, scrollSize;
//	GetTrueClientSize( windowSize, scrollSize );
	CRect	rect;
//	GetClientRect( &rect );
//	ASSERT( rect.top == 0 && rect.left == 0 );
//	windowSize.cx = rect.right;
//	windowSize.cy = rect.bottom;
	m_wndFrame0.GetWindowRect( &rect );
	ScreenToClient( rect );
	windowSize.cx = rect.Width();
	windowSize.cy = rect.Height();
	scrollSize.cx = 0;
	scrollSize.cy = 0;
	m_nHeadRoom = rect.top;

	// subtract out vertical scrollbar if zoomed out and page range is known
	// and there is more than one page.
	if ( m_nZoomState == ZOOM_OUT && ( m_pPreviewInfo -> GetMaxPage() != 0xffff ) &&
		( m_pPreviewInfo -> GetMaxPage() - m_pPreviewInfo -> GetMinPage() != 0 ))
		windowSize.cx -= scrollSize.cx;

	m_nSecondPageOffset = ( windowSize.cx - PREVIEW_MARGIN ) / 2;

	windowSize.cx = ( m_nPages == 2 ) ? ( windowSize.cx - 3*PREVIEW_MARGIN ) / 2 :
										( windowSize.cx - 2*PREVIEW_MARGIN );

	windowSize.cy -= 2*PREVIEW_MARGIN;
	return windowSize;
}
/*
BOOL CScrollView::GetTrueClientSize(CSize& size, CSize& sizeSb)
        // return TRUE if enough room to add scrollbars if needed
{
        CRect rect;
        GetClientRect(&rect);
        ASSERT(rect.top == 0 && rect.left == 0);
        size.cx = rect.right;
        size.cy = rect.bottom;
        DWORD dwStyle = GetStyle();

        // first get the size of the scrollbars for this window
        GetScrollBarSizes(sizeSb);

        // first calculate the size of a potential scrollbar
        // (scroll bar controls do not get turned on/off)
        if (sizeSb.cx != 0 && (dwStyle & WS_VSCROLL))
        {
                // vert scrollbars will impact client area of this window
                size.cx += sizeSb.cx;   // currently on - adjust now
        }
        if (sizeSb.cy != 0 && (dwStyle & WS_HSCROLL))
        {
                // horz scrollbars will impact client area of this window
                size.cy += sizeSb.cy;   // currently on - adjust now
        }

        // return TRUE if enough room
        return (size.cx > sizeSb.cx && size.cy > sizeSb.cy);
}
*/
void CPreviewDialog::SetScaledSize( UINT nPage )
{
	CSize*	pSize = &m_pPageInfo[nPage].sizeUnscaled;
	CSize*	pRatio = &m_pPageInfo[nPage].sizeScaleRatio;
	CSize*	pZoomOutRatio = &m_pPageInfo[nPage].sizeZoomOutRatio;
	CSize	windowSize = CalcPageDisplaySize();
	BOOL	bPaperLarger = pZoomOutRatio -> cx < pZoomOutRatio -> cy;
	// whether the paper is larger than the screen, or vice versa

	switch ( m_nZoomState )
	{
	case ZOOM_OUT:
		*pRatio = *pZoomOutRatio;
		break;

	case ZOOM_MIDDLE:
		// the middle zoom state is a ratio between cx/cy and
		// 1/1 (or cy/cy).  It is, therefore:
		//
		// (cx + cy)/2
		// -----------
		//     cy
		//
		// if the paper is larger than the screen, or
		//
		// (3*cx - cy)/2
		// -------------
		//      cy
		//
		// if the paper is smaller than the screen.
		if ( bPaperLarger )
		{
			pRatio -> cy = pZoomOutRatio -> cy;
			pRatio -> cx = ( pZoomOutRatio -> cx + pRatio -> cy ) / 2;
		}
		else
		{
			pRatio -> cy = pZoomOutRatio -> cy;
			pRatio -> cx = ( 3*pZoomOutRatio -> cx - pRatio -> cy ) / 2;
		}
		break;

	case ZOOM_IN:
		if (bPaperLarger)
			pRatio -> cx = pRatio -> cy = 1;
		else
		{
			// if the paper is smaller than the screen space we're displaying
			// it in, then using a ratio of 1/1 will result in a smaller image
			// on the screen, not a larger one. To get a larger image in this
			// case we double the zoom out ratio.
			pRatio -> cy = pZoomOutRatio -> cy;
			pRatio -> cx = 2*pZoomOutRatio -> cx - pZoomOutRatio -> cy;
		}
		break;

	default:
		ASSERT(FALSE);
	}

	// Convert to scaled size
	CSize	scaledSize;
	scaledSize.cx = MulDiv( pSize -> cx, pRatio -> cx, pRatio -> cy );
	scaledSize.cy = MulDiv( pSize -> cy, pRatio -> cx, pRatio -> cy );

	CRect*	pRect = &m_pPageInfo[nPage].rectScreen;
	pRect -> SetRect( PREVIEW_MARGIN, PREVIEW_MARGIN + m_nHeadRoom,
					scaledSize.cx + PREVIEW_MARGIN + 3,
					scaledSize.cy + PREVIEW_MARGIN + m_nHeadRoom + 3 );

	if ( m_nZoomState == ZOOM_OUT )
	{
		pRect -> OffsetRect(( windowSize.cx - pRect -> Size().cx ) / 2 - 1,
							( windowSize.cy - pRect -> Size().cy) / 2 - 1 );

		if ( nPage == 1 )
			pRect -> OffsetRect( m_nSecondPageOffset, 0 );
	}
	else
	{
		// set up scroll size

//		SetScrollSizes( MM_TEXT, pRect->Size() +
//				CSize(PREVIEW_MARGIN * 2, PREVIEW_MARGIN * 2 ), windowSize );
	}
}

// Return is actually the fraction cx/cy. Simply using CSize for convenience
CSize CPreviewDialog::CalcScaleRatio( CSize screenSize, CSize actualSize )
{
	// Test ratio based on vertical dimension to see if it is the one to use
	int	nNum = screenSize.cy;
	int	nDen = actualSize.cy;

	// If scaled width too large, choose width as primary dimension
	if ( MulDiv( actualSize.cx, nNum, nDen ) > screenSize.cx )
	{
		// wrong ratio--base on width
		nNum = screenSize.cx;
		nDen = actualSize.cx;
	}
	CSize ratio( nNum, nDen );
	return ratio;
}

CPoint CPreviewDialog::GetDeviceScrollPosition() const
{
//	CPoint	pt( GetScrollPos( SB_HORZ ), GetScrollPos( SB_VERT ));
	CPoint	pt( 0, 0 );
	ASSERT( pt.x >= 0 && pt.y >= 0 );

//	if ( m_bCenter )
	{
		CRect rect;
		GetClientRect( &rect );

		// if client area is larger than total device size,
		// the scroll positions are overridden to place origin such that
		// output is centered in the window
		// GetDeviceScrollPosition() must reflect this

//		if ( m_totalDev.cx < rect.Width())
//			pt.x = -((rect.Width() - m_totalDev.cx) / 2 );
//		if ( m_totalDev.cy < rect.Height())
//			pt.y = -((rect.Height() - m_totalDev.cy) / 2);
	}

	return pt;
}

void CPreviewDialog::PrintPage( CPreviewDC* pDC, CPrintInfo* pInfo, UINT offset )
{
	UINT			idx = m_nCurrentPage - 1 + offset;
	CString			text;
	CPrintAnlage	*pPA;

	if ( idx < (UINT)m_pPrintListe -> GetSize())
	{
		text = m_pPrintListe -> GetAt( idx );

		ASSERT( idx < (UINT)m_pArray.GetSize());
		pPA = (CPrintAnlage*)m_pArray[idx];
		if ( pPA )
		{
			if ( NULL == pPA -> m_pNF_PG1 )
				pPA -> CreateStaticMembers( pDC, m_strEqIDE );

			pPA -> Print( pDC );
		}
	}
	else
		RenderGeoDB( pDC );
}

void CPreviewDialog::OnSelchangePage() 
{
	int		idx = m_cbSeiten.GetCurSel();

	if ( g_bBreak )
	{
		idx = m_pPreviewInfo -> m_nCurPage - 1;
		if ( idx >= 0 )
			m_cbSeiten.SetCurSel( idx );
		::MessageBeep( -1 );
		return;
	}

	if ( idx != CB_ERR )
	{
		EnableWindow( FALSE );
		idx++;
		m_pPreviewInfo -> m_nCurPage = idx;
		SetCurrentPage( idx, TRUE );
		EnableWindow( TRUE );
	}
}	// OnSelchangePage

void CPreviewDialog::OnZweiSeiten() 
{
	if ( g_bBreak )
	{
		::MessageBeep( -1 );
		return;
	}

	if ( m_nPages == 1 )
	{
		m_nPages = 2;
		m_btn2Seiten.SetWindowText( "Eine Seite" );
	}
	else
	{
		m_nPages = 1;
		m_btn2Seiten.SetWindowText( "Zwei Seiten" );
	}

	EnableWindow( FALSE );
	// Just do this to set the status correctly and invalidate
	SetCurrentPage( m_nCurrentPage, TRUE );
	EnableWindow( TRUE );
}

void CPreviewDialog::OnDisplayPageNumber( UINT nPage, UINT nPagesDisplayed )
{
	CString		s;
	UINT		nEndPage = nPage + nPagesDisplayed - 1;

	if ( AfxExtractSubString( s, m_pPreviewInfo -> m_strPageDesc, nPagesDisplayed - 1 ))
	{
//		TCHAR	szBuf[80];
//		wsprintf( szBuf, s, nPage, nEndPage );
		CxString	text;
		text.printf( s, nPage, nEndPage );
		m_strPageText = text;
		UpdateData( FALSE );
	}
}

CString CPreviewDialog::Identisch( const char* ide1, const char* ide2 )
{
	ASSERT( AfxIsValidString( ide1 ));
	ASSERT( AfxIsValidString( ide2 ));

	CString		result;
	BOOL		fertig = FALSE;

	while ( !fertig )
	{
		fertig = (( *ide1 == '\0' ) || ( *ide2 == '\0' ));
		if ( !fertig )
		{
			if ( *ide1 == *ide2 )	result += *ide1;
			else					fertig = TRUE;
			ide1++;
			ide2++;
		}
	}

	return result;
}

void CPreviewDialog::RenderGeoDB( CPreviewDC* pDC )
{
	BOOL	abbruch = FALSE;
	long	c[4];

	CRect	rcDest, rcPict;
	CSize	size;
	CPoint	pt;
	CSize	sz;

	// get size of printer page (in pixels)
	int cxPage = pDC->GetDeviceCaps(HORZRES);
	int cyPage = pDC->GetDeviceCaps(VERTRES);
	// get printer pixels per inch
	int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
	int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);

// Hauptrahmen
	rcDest.top = cyInch / 2;				// oben 1/2 Zoll
	rcDest.bottom = cyPage - cyInch / 2;	// unten ebenso
	rcDest.left = cxInch * 3 / 4;			// links 3/4 Zoll
	rcDest.right = cxPage - cxInch / 2;		// rechts 1/2 Zoll
	pDC -> Rectangle( rcDest );

	rcDest.top    += 2;
	rcDest.bottom -= 2;
	rcDest.left   += 2;
	rcDest.right  -= 2;
	rcPict = rcDest;

	if ( m_rclClipBox.left == m_rclClipBox.right )
	{
		m_rclRectangle.left   = rcDest.left;
		m_rclRectangle.right  = rcDest.right;
		m_rclRectangle.top    = rcDest.top;
		m_rclRectangle.bottom = rcDest.bottom;

		m_rclPage.left   = 0;
		m_rclPage.right  = cxPage;
		m_rclPage.top    = 0;
		m_rclPage.bottom = cyPage;

		size.cx = rcDest.left;
		size.cy = rcDest.top;
		pDC -> LPtoHIMETRIC( &size );
		rcDest.left = size.cx;
		rcDest.top  = size.cy;
		size.cx = rcDest.right;
		size.cy = rcDest.bottom;
		pDC -> LPtoHIMETRIC( &size );
		rcDest.right  = size.cx;
		rcDest.bottom = size.cy;

		m_rclFrame.left   = rcDest.left;
		m_rclFrame.right  = rcDest.right;
		m_rclFrame.top    = - rcDest.top;
		m_rclFrame.bottom = - rcDest.bottom;

		size.cx = cxPage;
		size.cy = cyPage;
		pDC -> LPtoHIMETRIC( &size );

//		m_rclClipBox.left   = 100;
//		m_rclClipBox.right  = size.cx;
//		m_rclClipBox.top    = 100;
//		m_rclClipBox.bottom = size.cy;
		m_rclClipBox.left   = m_rclFrame.left + 100;
		m_rclClipBox.right  = m_rclFrame.right - 100;
		m_rclClipBox.top    = m_rclFrame.top - 100;
		m_rclClipBox.bottom = m_rclFrame.bottom + 100;
	}

	RECTL		cont;

	DEX_GetActiveSightContainer( c );

	if ( !abbruch )
	{
		cont.left   = c[0];
		cont.top    = c[3];
		cont.right  = c[1];
		cont.bottom = c[2];
	}

	if ( !abbruch )
	{
		if ( m_bUseMetaFile )
		{
			if ( m_hdcMetaFile == NULL )
			{
				RENDERGEODB		sRend;
				CViewPortDlg	vpDlg;
				RECTL			rectl;
				HDC				hdcMetaFile;

				SaveDC( pDC -> m_hAttribDC );

				::SetMapMode( pDC -> m_hAttribDC, MM_HIMETRIC );
//				::DPtoLP( pDC -> m_hAttribDC, (POINT*)&rectl, 2 );

				rectl.bottom = labs( m_rclFrame.bottom - m_rclFrame.top );
				rectl.top    = 0L;
				rectl.right  = labs( m_rclFrame.right - m_rclFrame.left );
				rectl.left   = 0L;
				rcPict.top    = rectl.top;
				rcPict.bottom = rectl.bottom;
				rcPict.left   = rectl.left;
				rcPict.right  = rectl.right;

				hdcMetaFile = CreateEnhMetaFile( pDC -> m_hAttribDC, "C:\\TEMP\\MetaFile.TMP", &rcPict, NULL );
//				hdcMetaFile = CreateEnhMetaFile( pDC -> m_hAttribDC, NULL, (RECT *)&rcMF, g_cbTRiASPict);

				sRend.dwSize              = sizeof( RENDERGEODB );
				sRend.m_hDC               = hdcMetaFile;
				sRend.m_hTargetDC         = pDC -> m_hAttribDC;

				sRend.m_rclFrame.left     = 0L;
				sRend.m_rclFrame.top      = rectl.bottom;
				sRend.m_rclFrame.right    = rectl.right;
				sRend.m_rclFrame.bottom   = 0L;
				sRend.m_rclClipBox        = sRend.m_rclFrame;

				sRend.m_rclGeoDB.left     = cont.left;
				sRend.m_rclGeoDB.top      = cont.top;
				sRend.m_rclGeoDB.right    = cont.right;
				sRend.m_rclGeoDB.bottom   = cont.bottom;

				::SetMapMode( hdcMetaFile, MM_HIMETRIC );
				::SetWindowOrgEx( hdcMetaFile, 0, (int)( sRend.m_rclFrame.top - sRend.m_rclFrame.bottom ), NULL );

				if ( hdcMetaFile )
				{
					DexExtensionProc((WPARAM)DEX_RENDERGEODB, (LPARAM)&sRend );
					m_hdcMetaFile = CloseEnhMetaFile( hdcMetaFile );
				}
				else
					AfxMessageBox( "Kein MetaFile verfügbar!" );

				::RestoreDC( pDC -> m_hAttribDC, -1 );
			}

			if ( m_hdcMetaFile )
			{
				CRgn	rgn;
				CRect	DestRect;
				POINT	pt1, pt2;

				DestRect.bottom = m_rclFrame.bottom;
				DestRect.top    = m_rclFrame.top;
				DestRect.left   = m_rclFrame.left;
				DestRect.right  = m_rclFrame.right;
				pDC -> SetMapMode( MM_HIMETRIC );
				pt1.x = m_rclClipBox.left;
				pt1.y = m_rclClipBox.top;
				pt2.x = m_rclClipBox.right;
				pt2.y = m_rclClipBox.bottom;
				::LPtoDP( pDC -> m_hAttribDC, &pt1, 1 );
				::LPtoDP( pDC -> m_hAttribDC, &pt2, 1 );
				pDC -> PrinterDPtoScreenDP( &pt1 );
				pDC -> PrinterDPtoScreenDP( &pt2 );
				pt1.x += m_sizeTopLeftOffset.cx;
				pt1.y += m_sizeTopLeftOffset.cy;
				pt2.x += m_sizeTopLeftOffset.cx;
				pt2.y += m_sizeTopLeftOffset.cy;
				::DPtoLP( pDC -> m_hDC, &pt1, 1 );
				::DPtoLP( pDC -> m_hDC, &pt2, 1 );

				::IntersectClipRect( pDC -> m_hDC, pt1.x, pt1.y, pt2.x, pt2.y );
//				pDC -> PlayMetaFile( m_hdcMetaFile, &DestRect );
			}
		}
		else
		{
			CRgn			rgn;
			RENDERGEODB		sRend;

			sRend.dwSize            = sizeof( RENDERGEODB );
			sRend.m_hDC             = pDC -> m_hDC;
			sRend.m_hTargetDC       = pDC -> m_hAttribDC;
			sRend.m_rclFrame   = m_rclFrame;
			sRend.m_rclClipBox = m_rclClipBox;

			sRend.m_rclGeoDB.left   = cont.left;
			sRend.m_rclGeoDB.top    = cont.top;
			sRend.m_rclGeoDB.right  = cont.right;
			sRend.m_rclGeoDB.bottom = cont.bottom;

			if ( rgn.CreateRectRgn( rcPict.left, rcPict.top, rcPict.right, rcPict.bottom ))
			{
				pDC -> SelectClipRgn( &rgn, SIMPLEREGION );
				pDC -> SetMapMode( MM_LOMETRIC );
				DexExtensionProc((WPARAM)DEX_RENDERGEODB, (LPARAM)&sRend );
				rgn.DeleteObject();
			}
		}
	}
}

void CPreviewDialog::OnRect() 
{
	CRectDlg	dlg( this );

	dlg.m_lFrameLeft   = m_rclFrame.left;
	dlg.m_lFrameRight  = m_rclFrame.right;
	dlg.m_lFrameTop    = m_rclFrame.top;
	dlg.m_lFrameBottom = m_rclFrame.bottom;
	dlg.m_lPageLeft    = m_rclPage.left;
	dlg.m_lPageRight   = m_rclPage.right;
	dlg.m_lPageTop     = m_rclPage.top;
	dlg.m_lPageBottom  = m_rclPage.bottom;
	dlg.m_lRectLeft    = m_rclRectangle.left;
	dlg.m_lRectRight   = m_rclRectangle.right;
	dlg.m_lRectTop     = m_rclRectangle.top;
	dlg.m_lRectBottom  = m_rclRectangle.bottom;
	dlg.m_lClipLeft    = m_rclClipBox.left;
	dlg.m_lClipRight   = m_rclClipBox.right;
	dlg.m_lClipTop     = m_rclClipBox.top;
	dlg.m_lClipBottom  = m_rclClipBox.bottom;
	dlg.m_bUseMetaFile = m_bUseMetaFile;

	if ( dlg.DoModal() == IDOK )
	{
		m_rclFrame.left       = dlg.m_lFrameLeft;
		m_rclFrame.right      = dlg.m_lFrameRight;
		m_rclFrame.top        = dlg.m_lFrameTop;
		m_rclFrame.bottom     = dlg.m_lFrameBottom;
		m_rclPage.left        = dlg.m_lPageLeft;
		m_rclPage.right       = dlg.m_lPageRight;
		m_rclPage.top         = dlg.m_lPageTop;
		m_rclPage.bottom      = dlg.m_lPageBottom;
		m_rclRectangle.left   = dlg.m_lRectLeft;
		m_rclRectangle.right  = dlg.m_lRectRight;
		m_rclRectangle.top    = dlg.m_lRectTop;
		m_rclRectangle.bottom = dlg.m_lRectBottom;
		m_rclClipBox.left     = dlg.m_lClipLeft;
		m_rclClipBox.right    = dlg.m_lClipRight;
		m_rclClipBox.top      = dlg.m_lClipTop;
		m_rclClipBox.bottom   = dlg.m_lClipBottom;
		m_bUseMetaFile        = dlg.m_bUseMetaFile;

//		if ( m_hdcMetaFile )	DeleteEnhMetaFile( m_hdcMetaFile );
//		m_hdcMetaFile = NULL;

		RedrawWindow();
	}
}
