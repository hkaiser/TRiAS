#include "stdafx.h"
#include "LinesigImpl.h"

#include "lsignat.h"
#include "dlglines.h"
#include "metafile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////

BOOL CLineSigCtrl::OnQueryParameters(
						CWnd* pParentWnd,
						const DWORD lONr, 
						class VisInfo * pVI, 
						LPCTSTR pszVisStr, 
						LPSTR pBuffer, 
						short iLen,
						short * piOTypes)
{
	CDlgLinesigParam	dlg( pParentWnd );

	dlg.m_bAdminMode = m_bAdminMode;

	dlg.m_pageSelectSig.m_pMapOfSignatures = &m_mapOfSignatures;

	//////////////////////////////////////////////////////////////////////////////////////
	// Geometrie: in den Dialog rein geht's mit Breiten und Höhen; rauszu wird in ein RECT umgerechnet

	long	l, t, r, b, dx, dy;
	l = t = r = b = 0L;

	if( !ParseVisInfoString( pszVisStr, dlg.m_pageSelectSig.m_strSigname, dx, dy, l, t, r, b, dlg.m_pageGeometry.m_bSwapX, dlg.m_pageGeometry.m_bSwapY ) ) {
		if( dlg.m_pageSelectSig.m_strSigname.IsEmpty( ) ) {
			// mit sinvollen Werten vorbesetzen
			l = 0;
			t = -100;
			r = 1000;
			b = 100;
			dlg.m_pageGeometry.m_bSwapX = dlg.m_pageGeometry.m_bSwapY = FALSE;
			dlg.m_pageGeometry.m_nSigOffsetX = dlg.m_pageGeometry.m_nSigOffsetY = 0;
		}
	}
	dlg.m_sigColor = (COLORREF) pVI->PrimColor();

	dlg.m_pageGeometry.m_nSigOffsetX = dx;
	dlg.m_pageGeometry.m_nSigOffsetY = dy;
	dlg.m_pageGeometry.m_nSigWidth	= r - l;
	dlg.m_pageGeometry.m_nSigHeight	= b - t;

	dlg.m_pageDebug.m_scale = m_scale;
	dlg.m_pageDebug.m_arc = m_arc;
	dlg.m_pageDebug.m_bClipExtended = m_bClipExtended;
	dlg.m_pageDebug.m_bMarkSegments = m_bMarkSegments;

	dlg.m_pageGeometry.m_nSigOffsetY	= ( t + b ) / 2;
	if( IDOK == dlg.DoModal( ) ) {
		CString	S;
		S.Format( _T("t=10,\"\"; z=\"linesig\":\"%s;%d,%d;%d;%d;%d;%d;%d;%d\";")
			, dlg.m_pageSelectSig.m_strSigname
			, dlg.m_pageGeometry.m_nSigOffsetX, dlg.m_pageGeometry.m_nSigOffsetY
			, 0
			, -( dlg.m_pageGeometry.m_nSigHeight / 2 )
			, dlg.m_pageGeometry.m_nSigWidth
			, ( dlg.m_pageGeometry.m_nSigHeight / 2 )
			, dlg.m_pageGeometry.m_bSwapX
			, dlg.m_pageGeometry.m_bSwapY
			);
		if( iLen > S.GetLength() + 1 ) {
			strcpy( pBuffer, S );
		}
		*piOTypes = (OTLinie);
		m_scale = dlg.m_pageDebug.m_scale;
		m_arc = dlg.m_pageDebug.m_arc;
		m_bClipExtended = dlg.m_pageDebug.m_bClipExtended;
		m_bMarkSegments = dlg.m_pageDebug.m_bMarkSegments;

		return TRUE;
	}
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CPageGeometry property page

IMPLEMENT_DYNCREATE(CPageGeometry, CPropertyPage)

CPageGeometry::CPageGeometry() : CPropertyPage(CPageGeometry::IDD) {
	//{{AFX_DATA_INIT(CPageGeometry)
	m_bSwapX = FALSE;
	m_bSwapY = FALSE;
	m_nSigHeight = 0;
	m_nSigWidth = 0;
	m_nSigOffsetY = 0;
	m_nSigOffsetX = 0;
	//}}AFX_DATA_INIT
}

CPageGeometry::~CPageGeometry() {
}

void CPageGeometry::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageGeometry)
	DDX_Control(pDX, IDC_SPIN_SIGYOFFSET, m_sigOffsetY);
	DDX_Control(pDX, IDC_SPIN_SIGXOFFSET, m_sigOffsetX);
	DDX_Control(pDX, IDC_SPIN_SIGWIDTH, m_sigWidth);
	DDX_Control(pDX, IDC_SPIN_SIGHEIGHT, m_sigHeight);
	DDX_Check(pDX, IDC_CHECKSWAPX, m_bSwapX);
	DDX_Check(pDX, IDC_CHECKSWAPY, m_bSwapY);
	DDX_Text(pDX, IDC_EDITSIGHEIGHT, m_nSigHeight);
	DDX_Text(pDX, IDC_EDITSIGWIDTH, m_nSigWidth);
	DDX_Text(pDX, IDC_EDITSIGYOFFSET, m_nSigOffsetY);
	DDV_MinMaxInt(pDX, m_nSigOffsetY, -50, 50);
	DDX_Text(pDX, IDC_EDITSIGXOFFSET, m_nSigOffsetX);
	DDV_MinMaxInt(pDX, m_nSigOffsetX, 0, 100);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageGeometry, CPropertyPage)
	//{{AFX_MSG_MAP(CPageGeometry)
	ON_BN_CLICKED(IDC_BTNFROMHEIGHT, OnBtnfromheight)
	ON_BN_CLICKED(IDC_BTNFROMWIDTH, OnBtnfromwidth)
	ON_BN_CLICKED(IDC_CHECKSWAPX, OnCheckswapx)
	ON_BN_CLICKED(IDC_CHECKSWAPY, OnCheckswapy)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SIGXOFFSET, OnDeltaposSpinSigxoffset)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SIGYOFFSET, OnDeltaposSpinSigyoffset)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SIGHEIGHT, OnDeltaposSpinSigheight)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SIGWIDTH, OnDeltaposSpinSigwidth)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*
void CPageGeometry::UpdatePreview( ) {
	GetParent()->UpdatePreviewSize( CSize( m_nSigWidth, m_nSigHeight ) );
	GetParent()->UpdatePreviewOffset( CPoint( m_nSigOffsetX, m_nSigOffsetY) );
	GetParent()->UpdatePreviewSwap( m_bSwapX, m_bSwapY );
}
*/
/////////////////////////////////////////////////////////////////////////////
// CPageGeometry message handlers

BOOL CPageGeometry::OnInitDialog() {
	CPropertyPage::OnInitDialog();

	m_sigHeight.SetRange( 5, SHRT_MAX - 1 );
	m_sigHeight.SetBase( 10 );
	m_sigHeight.SetPos( m_nSigHeight );

	m_sigWidth.SetRange( 50, SHRT_MAX - 1 );
	m_sigWidth.SetBase( 10 );
	m_sigWidth.SetPos( m_nSigWidth );

	m_sigOffsetX.SetBase( 10 );
	m_sigOffsetX.SetRange( 0, 100 );
	m_sigOffsetY.SetBase( 10 );
	m_sigOffsetY.SetRange( -50, 50 );

	UpdateData( FALSE );		// Initialwerte rückschreiben

	return TRUE;
}

void CPageGeometry::OnDeltaposSpinSigyoffset(NMHDR* pNMHDR, LRESULT* pResult)  {
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	int	pos = pNMUpDown->iPos + pNMUpDown->iDelta;
	if( pos >= -50 && pos <= 50 ) {
		m_nSigOffsetY = pos;
		GetParent()->UpdatePreviewOffset( CPoint( m_nSigOffsetX, m_nSigOffsetY) );
		*pResult = 0;
	} else {
		*pResult = 1;
	}
}

void CPageGeometry::OnDeltaposSpinSigheight(NMHDR* pNMHDR, LRESULT* pResult)  {
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	int	pos = pNMUpDown->iPos + pNMUpDown->iDelta;
	if( pos >= 50 ) {
		m_nSigHeight = pos;
		int keyState = ::GetKeyState( VK_CONTROL ) & 0x8000;
		if( 0 == keyState ) {
			CRect	rcShape;
			if( GetParent()->GetPictureRect( &rcShape ) ) {
				m_nSigWidth = ::MulDiv( (short) m_nSigHeight, rcShape.Width(), rcShape.Height() );
				UpdateData(FALSE);
			}
		}
		GetParent()->UpdatePreviewSize( CSize( m_nSigWidth, m_nSigHeight ) );
		*pResult = 0;
	} else {
		*pResult = 1;
	}
}

void CPageGeometry::OnDeltaposSpinSigwidth(NMHDR* pNMHDR, LRESULT* pResult)  {
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	int	pos = pNMUpDown->iPos + pNMUpDown->iDelta;
	if( pos >= 5 ) {
		m_nSigWidth = pos;
		GetParent()->UpdatePreviewSize( CSize( m_nSigWidth, m_nSigHeight ) );
		*pResult = 0;
	} else {
		*pResult = 1;
	}
}


void CPageGeometry::OnDeltaposSpinSigxoffset(NMHDR* pNMHDR, LRESULT* pResult) {
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	int pos = pNMUpDown->iPos + pNMUpDown->iDelta;
	if( pos >= 0 && pos <= 100 ) {
		m_nSigOffsetX = pos;
		GetParent()->UpdatePreviewOffset( CPoint( m_nSigOffsetX, m_nSigOffsetY) );
		*pResult = 0;
	} else {
		*pResult = 1;
	}
}

void CPageGeometry::OnBtnfromheight() {
	CRect	rcShape;
	if( GetParent()->GetPictureRect( &rcShape ) ) {
		m_nSigWidth = ::MulDiv( (short) m_nSigHeight, rcShape.Width(), rcShape.Height() );
		UpdateData(FALSE);
		GetParent()->UpdatePreviewSize( CSize( m_nSigWidth, m_nSigHeight ) );
	}
}

void CPageGeometry::OnBtnfromwidth() {
	CRect	rcShape;
	if( GetParent()->GetPictureRect( &rcShape ) ) {
		m_nSigHeight = ::MulDiv( (short) m_nSigWidth, rcShape.Height(), rcShape.Width() );
		UpdateData(FALSE);
		GetParent()->UpdatePreviewSize( CSize( m_nSigWidth, m_nSigHeight ) );
	}
}

void CPageGeometry::OnCheckswapx() 
	{ UpdateData(); GetParent()->UpdatePreviewSwap( m_bSwapX, m_bSwapY ); }

void CPageGeometry::OnCheckswapy() 
	{ UpdateData(); GetParent()->UpdatePreviewSwap( m_bSwapX, m_bSwapY ); }

/////////////////////////////////////////////////////////////////////////////
// CPageSelectSig property page

IMPLEMENT_DYNCREATE(CPageSelectSig, CPropertyPage)

CPageSelectSig::CPageSelectSig() : CPropertyPage(CPageSelectSig::IDD) {
	//{{AFX_DATA_INIT(CPageSelectSig)
	//}}AFX_DATA_INIT
	m_strSigname = _T("");
	m_imgList.Create( IDB_TREEITEMS, 16, 0, RGB( 255, 0, 255 ) );
	m_imgList.SetBkColor( ::GetSysColor( COLOR_WINDOW ) );
}

CPageSelectSig::~CPageSelectSig()
	{ }

void CPageSelectSig::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageSelectSig)
	DDX_Control(pDX, IDC_TREE_LINESIG, m_treeSig);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageSelectSig, CPropertyPage)
	//{{AFX_MSG_MAP(CPageSelectSig)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_LINESIG, OnSelchangedTreeLinesig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CPageSelectSig::UpdatePreview( ) {
	MetafileMap::const_iterator i = m_pMapOfSignatures->find(StrToASCII(m_strSigname));
	GetParent()->UpdatePreviewPict( i == m_pMapOfSignatures->end() ? NULL : (*i).second, TRUE );
}

BOOL CPageSelectSig::OnSetActive() {
	// TODO: Add your specialized code here and/or call the base class
	UpdatePreview();
	return CPropertyPage::OnSetActive();
}

/////////////////////////////////////////////////////////////////////////////
// CPageSelectSig message handlers		   '

BOOL CPageSelectSig::OnInitDialog() {
	CPropertyPage::OnInitDialog();
	
	ASSERT_VALID( &m_imgList );

	m_treeSig.SetImageList( &m_imgList );

	CString	key;
	CMetaFile	*pMetafile = NULL;

	CTreeCursor bmkRoot, bmkNode, bmkCurr, bmkSel;
	bmkRoot = m_treeSig.GetRootItem();
	bmkNode = bmkRoot.AddTail( _T("Forstwirtschaft"), 0);
	bmkNode.SetData( 0L );
	CString strSigname = StrToASCII( m_strSigname );
	MetafileMap::const_iterator i;
	for( i = m_pMapOfSignatures->begin(); i != m_pMapOfSignatures->end(); ++i ) {
		key = (*i).first;
		pMetafile = (*i).second;
		if( NULL != pMetafile ) {
			bmkCurr = bmkNode.AddTail( pMetafile->GetName(), 1 );
			bmkCurr.SetData( (DWORD) pMetafile );
			if( StrToASCII( pMetafile->GetName() ) == strSigname )
				bmkSel = bmkCurr;
		}
	}

	if( NULL != (HTREEITEM) bmkSel )
		m_treeSig.SelectItem( bmkSel );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageSelectSig::OnSelchangedTreeLinesig(NMHDR* pNMHDR, LRESULT* pResult) {
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	CTreeCursor bmk = m_treeSig.GetSelectedItem();
	if( 0L != bmk.GetData() ) {
		m_strSigname = bmk.GetText();
		UpdatePreview( );
	}
	*pResult = 0;
}

/////////////////////////////////////////////////////////////////////////////
// CPageDebug dialog

CPageDebug::CPageDebug() : CPropertyPage(CPageDebug::IDD) {
	//{{AFX_DATA_INIT(CPageDebug)
	m_scale = 0;
	m_arc = 0;
	m_bClipExtended = FALSE;
	m_bMarkSegments = FALSE;
	//}}AFX_DATA_INIT
}

void CPageDebug::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageDebug)
	DDX_Control(pDX, IDC_SPIN_SCALE, m_spinScale);
	DDX_Control(pDX, IDC_SPIN_ARC, m_spinArc);
	DDX_Text(pDX, IDC_EDITSCALE, m_scale);
	DDX_Text(pDX, IDC_EDITARC, m_arc);
	DDX_Check(pDX, IDC_CHECK_CLIPEXTENDED, m_bClipExtended);
	DDX_Check(pDX, IDC_CHECK_MARKSEGMENTS, m_bMarkSegments);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageDebug, CPropertyPage)
	//{{AFX_MSG_MAP(CPageDebug)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageDebug message handlers

BOOL CPageDebug::OnInitDialog() {
	CPropertyPage::OnInitDialog();

	m_spinScale.SetRange( 10, 1000 );
	m_spinScale.SetBase( 10 );
	m_spinScale.SetPos( m_scale );
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDlgLinesigParam

IMPLEMENT_DYNAMIC(CDlgLinesigParam, CPropertySheet)

CDlgLinesigParam::CDlgLinesigParam(CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(CDlgLinesigParam::IDD, pParentWnd, iSelectPage)
{
	CreateCommon();
	m_bFirstDraw = TRUE;
}

void CDlgLinesigParam::CreateCommon() {
	AddPage( &m_pageSelectSig );
	AddPage( &m_pageGeometry );
#if defined(_RDEBUG)
	AddPage( &m_pageDebug );
#endif
}

CDlgLinesigParam::~CDlgLinesigParam()
	{ }

BEGIN_MESSAGE_MAP(CDlgLinesigParam, CPropertySheet)
	//{{AFX_MSG_MAP(CDlgLinesigParam)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDlgLinesigParam::UpdatePreviewPict( CMetaFile *pMF, BOOL bInvalidate /*= FALSE*/ ) {
	if( NULL != pMF ) { 
		pMF->BrushColor(m_sigColor); 
	}
	m_wmfShape.SetMetaFile( pMF, bInvalidate );
}

void CDlgLinesigParam::UpdatePreviewSize( const CSize& rSizePict, BOOL bInvalidate /*= FALSE*/  )
	{ m_wmfShape.SetDrawRect( rSizePict, bInvalidate ); }

void CDlgLinesigParam::UpdatePreviewOffset( const CPoint& rPtOffset, BOOL bInvalidate /*= FALSE*/  )
	{  m_wmfShape.SetOffset( rPtOffset, bInvalidate ); }

void CDlgLinesigParam::UpdatePreviewSwap( BOOL swapX, BOOL swapY, BOOL bInvalidate /*= FALSE*/  )
	{ m_wmfShape.SetSwap( swapX, swapY, bInvalidate ); }

BOOL CDlgLinesigParam::GetPictureRect( LPRECT pRect ) const {
	return m_wmfShape.GetPictureRect( pRect );
}

/////////////////////////////////////////////////////////////////////////////
// CDlgLinesigParam message handlers
/////////////////////////////////////////////////////////////////////////////

static const cyMargin = 10;

BOOL CDlgLinesigParam::OnInitDialog() {
	CPropertySheet::OnInitDialog();

	CRect	rcWnd;
	CRect	rcWmf;

	/////////////////////////////////////////////////////////////////////////////
	// Das WMF - Bildchen zurechtschieben

	GetTabControl()->GetWindowRect( rcWnd );
	ScreenToClient( rcWnd );

	rcWmf = rcWnd;

	rcWmf.bottom = rcWmf.top + ::MulDiv( rcWmf.Height(), 2, 3 );
	rcWmf.OffsetRect( 0, rcWnd.Height() + 10 );
	m_wmfShape.SetWindowPos( NULL, rcWmf.left, rcWmf.top, rcWmf.Width(), rcWmf.Height(), SWP_NOZORDER | SWP_NOACTIVATE );

	/////////////////////////////////////////////////////////////////////////////
	// Buttons positionieren

	CRect	rcO, rcC, rcA, rcH;		// OK, CANCEL, APPLY, HELP

	GetDlgItem( IDOK )->GetWindowRect( rcO ); ScreenToClient( rcO );
	GetDlgItem( IDCANCEL )->GetWindowRect( rcC ); ScreenToClient( rcC );
	GetDlgItem( ID_APPLY_NOW )->GetWindowRect( rcA ); ScreenToClient( rcA );
	GetDlgItem( IDHELP )->GetWindowRect( rcH ); ScreenToClient( rcH );

	GetDlgItem( ID_APPLY_NOW )->ShowWindow( SW_HIDE );

	GetDlgItem( IDOK )->SetWindowPos( NULL, rcC.left, rcWmf.bottom + cyMargin, rcO.Width(), rcO.Height(), SWP_NOZORDER | SWP_NOACTIVATE  );
	GetDlgItem( IDCANCEL )->SetWindowPos( NULL, rcA.left, rcWmf.bottom + cyMargin, rcC.Width(), rcC.Height(), SWP_NOZORDER | SWP_NOACTIVATE  );
	GetDlgItem( IDHELP )->SetWindowPos( NULL, rcH.left, rcWmf.bottom + cyMargin, rcH.Width(), rcH.Height(), SWP_NOZORDER | SWP_NOACTIVATE  );

	/////////////////////////////////////////////////////////////////////////////
	// Dialoggröße anpassen

	GetWindowRect( rcWnd );
	SetWindowPos( NULL, 0, 0, rcWnd.Width(), rcWnd.Height() + rcWmf.Height() + rcO.Height(), SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE );

	m_wmfShape.SetDrawRect( CSize( m_pageGeometry.m_nSigWidth, m_pageGeometry.m_nSigHeight ), FALSE );
	m_wmfShape.SetOffset( CPoint( m_pageGeometry.m_nSigOffsetX, m_pageGeometry.m_nSigOffsetY ), FALSE );
	m_wmfShape.SetSwap( m_pageGeometry.m_bSwapX, m_pageGeometry.m_bSwapY, FALSE );
	m_wmfShape.Invalidate();
	m_wmfShape.SetOffset( CPoint( m_pageGeometry.m_nSigOffsetX, m_pageGeometry.m_nSigOffsetY ), TRUE );

	return TRUE;
}

int CDlgLinesigParam::OnCreate(LPCREATESTRUCT lpCreateStruct)  {
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;
	if( !m_wmfShape.Create( CRect(0,0,100,100), this, IDC_EDITPICTURE ) )
		return -1;
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CWmfShape

CWmfShape::CWmfShape() {
	m_rcDraw.SetRectEmpty( );
	m_szPict = CSize(0,0);
	m_ptOffset = CPoint(0,0);
	m_bSwapX = m_bSwapY = FALSE;
}

CWmfShape::~CWmfShape() {
}

BEGIN_MESSAGE_MAP(CWmfShape, CStatic)
	//{{AFX_MSG_MAP(CWmfShape)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CWmfShape::Create( const RECT& rect, CWnd* pParent, UINT nID )
	{ return CStatic::Create( "", WS_CHILD | WS_VISIBLE | WS_DISABLED | SS_USERITEM, rect, pParent, nID ); }

BOOL CWmfShape::GetPictureRect( LPRECT pRect ) const {
	CRect	R(0,0,0,0);
	if( m_pMetaFile ) {
		R = m_pMetaFile ->GetFigureRect( );
		*pRect = R;
		return TRUE;
	} else {
		return FALSE;
	}
}

void CWmfShape::SetMetaFile( CMetaFile *pMetaFile, BOOL bInvalidate /*= FALSE*/ ) {
	ASSERT( NULL == pMetaFile || pMetaFile->IsKindOf( RUNTIME_CLASS( CMetaFile ) ) );
	m_pMetaFile = pMetaFile;
	if( bInvalidate )
		Invalidate( );
}

void CWmfShape::SetDrawRect( const CSize& rSzPict, BOOL bInvalidate /*= FALSE*/ ) {
	m_szPict = rSzPict;

	CRect	rcClient;
	CDRect	rcDraw;

	GetClientRect( &rcClient );

	double	ratioDraw = (double) m_szPict.cy / (double) m_szPict.cx;
	double	ratioClient = (double) rcClient.Height() / (double) rcClient.Width();

	if( ratioDraw > ratioClient )
		rcDraw.SetRect( rcClient.left, 0, (int) ( (double) rcClient.Height() / ratioDraw ), rcClient.Height() );
	else
		rcDraw.SetRect( rcClient.left, 0, rcClient.Width(), (int) ( (double) rcClient.Width() * ratioDraw ) );

	rcDraw.OffsetRect( 0, ( ( rcClient.bottom + rcClient.top ) - ( rcDraw.bottom + rcDraw.top ) ) / 2 );

	if( rcDraw != m_rcDraw )
		m_rcDraw = rcDraw;
	if( bInvalidate )
		Invalidate( );
}

void CWmfShape::SetOffset( const CPoint& rPtOffset, BOOL bInvalidate /*= FALSE*/ ) {
	if( m_ptOffset.x == rPtOffset.x && m_ptOffset.y == rPtOffset.y )
		return;
	if( bInvalidate ) {
		CClientDC	dc( this );
		DrawOffset( &dc );
		m_ptOffset = rPtOffset;
		DrawOffset( &dc );
	}
}

void CWmfShape::SetSwap( BOOL swapX, BOOL swapY, BOOL bInvalidate /*= FALSE*/ ) {
	if( m_bSwapX == swapX && m_bSwapY == swapY )
		return;
	m_bSwapX = swapX;
	m_bSwapY = swapY;
	if( bInvalidate )
		Invalidate( );
}

void CWmfShape::GetClientRect( LPRECT lpRect ) const
	{ CWnd::GetClientRect( lpRect ); ::InflateRect( lpRect, -5, -5 ); }

void CWmfShape::DrawOffset( CDC *pDC ) {
	CRect	rcClient;
	GetClientRect( &rcClient );

	double	x = ( (double) m_szPict.cx * (double) m_ptOffset.x ) / 100;
	double	y = ( (double) m_szPict.cy * (double) m_ptOffset.y ) / 100;

	x *= (double) m_rcDraw.Width() / (double) m_szPict.cx;
	y *= (double) m_rcDraw.Height() / (double) m_szPict.cy;
	CPoint	ptOff( frounds(x), frounds(y) );
	ptOff.x += rcClient.left;
	ptOff.y += rcClient.Height() / 2 + rcClient.top;

	//////////////////////////////////////////////////////////////////////////////
	// aktuell selektierten Punkt zeichnen

	CPen	pen( PS_DOT, 1, RGB(0,0,0)), *pOldPen;
	int oldROP2 = pDC->SetROP2( R2_NOTXORPEN );

	pOldPen = pDC->SelectObject( &pen );
	pDC->MoveTo( rcClient.left, ptOff.y );
	pDC->LineTo( rcClient.right , ptOff.y );
	pDC->MoveTo( ptOff.x, rcClient.top );
	pDC->LineTo( ptOff.x, rcClient.bottom );
	pDC->SelectObject( pOldPen );
	pen.DeleteObject();

	pDC->SetROP2( oldROP2 );
}

/////////////////////////////////////////////////////////////////////////////
// CWmfShape message handlers

BOOL CWmfShape::OnEraseBkgnd(CDC* pDC)  {
	HDC hDC = pDC->GetSafeHdc();
	CRect rc; CWnd::GetClientRect( rc );
	rc.right -= 1;
	rc.bottom -= 1;

	HGDIOBJ	hB = ::SelectObject( hDC, ::GetStockObject( LTGRAY_BRUSH ) );
	HGDIOBJ	hP = ::SelectObject( hDC, ::GetStockObject( WHITE_PEN ) );

	::Rectangle( hDC, rc.left, rc.top, rc.right, rc.bottom );
	rc.OffsetRect( 1, 1 );
	::FrameRect( hDC, &rc, (HBRUSH) ::GetStockObject( BLACK_BRUSH ) );
	::SelectObject( hDC, hP );
	::SelectObject( hDC, hB );
	return TRUE;
}

void CWmfShape::OnPaint()  {
	CPaintDC dc(this); // device context for painting
	CRect	rcClient;
	CRgn	rgClip;

	GetClientRect( &rcClient );
	rgClip.CreateRectRgnIndirect( &rcClient );
	dc.SelectClipRgn( &rgClip, RGN_AND );
	
	if( NULL != m_pMetaFile ) {
		CPoint	ptZero( rcClient.left, ( rcClient.bottom + rcClient.top ) / 2 );
		CDRect	rcDraw( 0, 0, m_szPict.cx, m_szPict.cy );
		m_pMetaFile->Play( &dc, m_rcDraw, &ptZero, m_bSwapX, m_bSwapY );
	}
	DrawOffset( &dc );

	// Do not call CStatic::OnPaint() for painting messages
}

//#include "lmfcx/LafxCtrl.inl"
