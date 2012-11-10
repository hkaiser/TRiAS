#include "stdafx.h"
#include "mapmgr.h"

#include "MapMgrDoc.h"
#include "mainfrm.h"

#include "UpdtHint.h"
#include "ViewPict.h"
#include "DlgMapSpecial.h"
#include "DlgMapProperties.h"

#include <io.h> // _access

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPictView

IMPLEMENT_DYNCREATE(CPictView, CScrollView)

#define ENABLE_ADD	m_fEnable |= 0x0001
#define ENABLE_EDT	m_fEnable |= 0x0002
#define	ENABLE_DEL	m_fEnable |= 0x0004
#define ENABLE_MOD	m_fEnable |= 0x0007
#define	ENABLE_OBJ	m_fEnable |= 0x8000

#define DISABLE_ADD	m_fEnable &= ~0x0001
#define	DISABLE_EDT	m_fEnable &= ~0x0002
#define	DISABLE_DEL	m_fEnable &= ~0x0004
#define	DISABLE_MOD	m_fEnable &= ~0x0007
#define	DISABLE_OBJ	m_fEnable &= ~0x8000

#define IS_ADD	(m_fEnable & 0x0001)
#define IS_EDT	(m_fEnable & 0x0002)
#define IS_DEL	(m_fEnable & 0x0004)
#define	IS_OBJ	(m_fEnable & 0x8000)

static TCHAR g_szPOINT[] = TEXT("POINT");

CPictView::CPictView() {
	m_nMode = -1;
	m_nObject = -1;
	DISABLE_MOD;
	DISABLE_OBJ;
	m_pPicture = NULL;
	m_pStatusBar = NULL;
	m_pTrackObject = NULL;
	m_nChannel = -1;
	m_bRGB = TRUE;
	m_pExpandColorChannel = new CExpandColorChannel;
	m_pRGBtoHSB = new CRGBtoHSB;
	CTrackObject *pTC = new CTrackPoint();
	m_listOfTrackObjects.SetAt( g_szPOINT, (CObject*&) pTC );
}

CPictView::~CPictView() {
	CString	key;
	CObject	*pObject;
	POSITION	pos;
	for( pos = m_mapOfPictures.GetStartPosition(); NULL != pos; ) {
		m_mapOfPictures.GetNextAssoc( pos, key, pObject );
		if( m_pPicture == pObject )
			m_pPicture = NULL;
		delete pObject;
		m_mapOfPictures.RemoveKey(key);
	}
	for( pos = m_listOfTrackObjects.GetStartPosition(); NULL != pos; ) {
		m_listOfTrackObjects.GetNextAssoc( pos, key, pObject );
		delete pObject;
		m_listOfTrackObjects.RemoveKey(key);
	}
	delete m_pExpandColorChannel;
	delete m_pRGBtoHSB;
	if( NULL != m_pPicture )
		delete m_pPicture;
}

void CPictView::RecalcScrollSizes() {
	CRect	rcClient;
	GetClientRect( rcClient );
	CSize	szScroll( 0, 0 );
	CSize	szLine( 0, 0 );
	CSize	szPage( 0, 0 );
	if( m_pPicture ) {
		CRect	rcPict = m_pPicture->GetPictRect();
		szScroll.cx = rcPict.Width() - 1;
		szScroll.cy = rcPict.Height() - 1;
		szPage.cx = ::MulDiv( rcClient.Width(), 2, 3 );
		szPage.cy = ::MulDiv( rcClient.Height(), 2, 3 );
		szLine.cx = ::MulDiv( szPage.cx, 1, 3 );
		szLine.cy = ::MulDiv( szPage.cy, 1, 3 );
	}
	m_pStatusBar->UpdateSize( &szScroll );
	SetScrollSizes( MM_TEXT, szScroll, szPage, szLine );
}

void CPictView::MakeTrackObjectVisible() {
	CDRect rcD = m_pTrackObject->GetBoundingRect();
	CRect rcTrack( froundl( rcD.left ), froundl( rcD.top ), froundl( rcD.right ), froundl( rcD.bottom ) );
	CRect rcClient;
	CRect rcIS;
	GetClientRect(rcClient);
	rcClient += GetScrollPosition();
	rcIS.IntersectRect( rcTrack, rcClient );
	if( rcIS.Width() != rcTrack.Width() || rcIS.Height() != rcTrack.Height() ) {
		ScrollToPosition( rcTrack.TopLeft() );
	}
}

BOOL CPictView::ChangePicture() {
	CPictException	excPict;

	for(;;) {
		CMapMgrDoc	*pDoc = GetDocument();
		ASSERT_VALID( pDoc );

		CRuntimeClass	*pCurrRTC = NULL;
		CObject			*pObject = NULL;
		if( NULL != m_pPicture ) {
			pCurrRTC = m_pPicture->GetRuntimeClass();
			if( !m_mapOfPictures.Lookup( pCurrRTC->m_lpszClassName, pObject ) )
				m_mapOfPictures.SetAt( pCurrRTC->m_lpszClassName, m_pPicture );
			m_pPicture->Detach();
			m_pPicture = NULL;
		}
		m_fileOfPicture.Abort();

		CMapInfo	*pMapInfo = pDoc->m_pCurrMapInfo;
		CInfoList	*pInfoList = &pDoc->m_listOfMapInfos;
		if( NULL == pMapInfo ) {
			break;
		}

		ASSERT_VALID( pMapInfo );
		CString strPictFile = pMapInfo->m_strBmpPath;
		if( strPictFile.IsEmpty() )
			break;
		
		BOOL	bHaveFound = FALSE;
		UINT	nOldErrMode = ::SetErrorMode( SEM_FAILCRITICALERRORS );
		bHaveFound = 0 == _access( strPictFile, 04 ) ? TRUE : FALSE;
		::SetErrorMode( nOldErrMode );

		if( !bHaveFound ) {
			CString	strPictPath;
			for( int i = 0; i < GetDocument()->m_strPictDirs.GetSize(); i++ ) {
				strPictPath = GetDocument()->m_strPictDirs[i] + strPictFile;
				if( MatchMapName( pMapInfo->GetIdent(), strPictPath ) ) {
					strPictFile = strPictPath;
					bHaveFound = TRUE;
					break;
				}
			}
		}
		if( !bHaveFound )
			break;

		if( !m_fileOfPicture.Open( strPictFile, CFile::modeRead | CFile::typeBinary ) )
			break;

		CRuntimeClass *pNewRTC = GetPictureType( &m_fileOfPicture );

		if( NULL == pNewRTC )
			break;		// not a known picture
	
		if( !m_mapOfPictures.Lookup( pNewRTC->m_lpszClassName, (CObject*&) m_pPicture ) )
			m_pPicture = (CPicture*) pNewRTC->CreateObject();

		VERIFY( m_pPicture->Attach( &m_fileOfPicture ) );

		if( !m_pPicture->ReadHeader( &excPict ) ) {
			m_pPicture->Detach();
			m_fileOfPicture.Abort();
			lpictdll::ReportPictException( &excPict );
			break;
		}

		m_pPicture->SetPictName( m_fileOfPicture.GetFilePath() );
		int	w = (int) m_pPicture->GetPictRect().Width();
		int	h = (int) m_pPicture->GetPictRect().Height();

		pMapInfo->m_sizeOfPict.cx = w;
		pMapInfo->m_sizeOfPict.cy = h;

		GEOPOINT *pt;
		pt = &pMapInfo->m_gcpArray[0].m_ptPictPoint;
		if( -1 == pt->X )
			pt->X = pDoc->m_szJump.cx;
		if( -1 == pt->Y )
			pt->Y = h - 1 - pDoc->m_szJump.cy;

		pt = &pMapInfo->m_gcpArray[1].m_ptPictPoint;
		if( -1 == pt->X )
			pt->X = w - 1 - pDoc->m_szJump.cx;
		if( -1 == pt->Y )
			pt->Y = h - 1 - pDoc->m_szJump.cy;

		pt = &pMapInfo->m_gcpArray[2].m_ptPictPoint;
		if( -1 == pt->X )
			pt->X = w - 1 - pDoc->m_szJump.cx;
		if( -1 == pt->Y )
			pt->Y = pDoc->m_szJump.cy;

		pt = &pMapInfo->m_gcpArray[3].m_ptPictPoint;
		if( -1 == pt->X )
			pt->X = pDoc->m_szJump.cx;
		if( -1 == pt->Y )
			pt->Y = pDoc->m_szJump.cy;

		break;
	}
	RecalcScrollSizes();
	Invalidate();
	return m_pPicture != NULL;
}

BEGIN_MESSAGE_MAP(CPictView, CScrollView)
	//{{AFX_MSG_MAP(CPictView)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_MODE_ADD, OnUpdateModeAdd)
	ON_UPDATE_COMMAND_UI(ID_MODE_DEL, OnUpdateModeDel)
	ON_UPDATE_COMMAND_UI(ID_MODE_EDT, OnUpdateModeEdit)
	ON_COMMAND(ID_MODE_ADD, OnModeAdd)
	ON_COMMAND(ID_MODE_DEL, OnModeDel)
	ON_COMMAND(ID_MODE_EDT, OnModeEdit)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_GCP_BL, OnGcpBl)
	ON_UPDATE_COMMAND_UI(ID_GCP_BL, OnUpdateGcpBl)
	ON_COMMAND(ID_GCP_BR, OnGcpBr)
	ON_UPDATE_COMMAND_UI(ID_GCP_BR, OnUpdateGcpBr)
	ON_COMMAND(ID_GCP_TL, OnGcpTl)
	ON_UPDATE_COMMAND_UI(ID_GCP_TL, OnUpdateGcpTl)
	ON_COMMAND(ID_GCP_TR, OnGcpTr)
	ON_UPDATE_COMMAND_UI(ID_GCP_TR, OnUpdateGcpTr)
	ON_COMMAND(ID_OBJ_LINE, OnObjLine)
	ON_UPDATE_COMMAND_UI(ID_OBJ_LINE, OnUpdateObjLine)
	ON_UPDATE_COMMAND_UI(ID_OBJ_POINT, OnUpdateObjPoint)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_GCP, OnGcp)
	ON_UPDATE_COMMAND_UI(ID_GCP, OnUpdateGcp)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_OBJ_POINT, OnObjPoint)
	ON_COMMAND(ID_REDRAW, OnRedraw)
	ON_UPDATE_COMMAND_UI(ID_REDRAW, OnUpdateRedraw)
	ON_COMMAND(ID_COLORCMD_SHOWR, OnColorcmdShowr)
	ON_UPDATE_COMMAND_UI(ID_COLORCMD_SHOWR, OnUpdateColorcmdShowr)
	ON_COMMAND(ID_COLORCMD_SHOWG, OnColorcmdShowg)
	ON_UPDATE_COMMAND_UI(ID_COLORCMD_SHOWG, OnUpdateColorcmdShowg)
	ON_COMMAND(ID_COLORCMD_SHOWB, OnColorcmdShowb)
	ON_UPDATE_COMMAND_UI(ID_COLORCMD_SHOWB, OnUpdateColorcmdShowb)
	ON_COMMAND(ID_COLORCMD_SHOWRGB, OnColorcmdShowrgb)
	ON_UPDATE_COMMAND_UI(ID_COLORCMD_SHOWRGB, OnUpdateColorcmdShowrgb)
	ON_COMMAND(ID_COLORCMD_SHOWHUE, OnColorcmdShowhue)
	ON_UPDATE_COMMAND_UI(ID_COLORCMD_SHOWHUE, OnUpdateColorcmdShowhue)
	ON_COMMAND(ID_COLORCMD_SHOWSAT, OnColorcmdShowsat)
	ON_UPDATE_COMMAND_UI(ID_COLORCMD_SHOWSAT, OnUpdateColorcmdShowsat)
	ON_COMMAND(ID_COLORCMD_SHOWBRI, OnColorcmdShowbri)
	ON_UPDATE_COMMAND_UI(ID_COLORCMD_SHOWBRI, OnUpdateColorcmdShowbri)
	ON_COMMAND(ID_MAP_PROPERTIES, OnMapProperties)
	//}}AFX_MSG_MAP
	ON_CHANGE_MAP()
	ON_WM_INITSTATUSBAR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPictView drawing

void CPictView::OnInitialUpdate() {
	CScrollView::OnInitialUpdate();
	if( ChangePicture() ) {
		ENABLE_OBJ;
		OnGcpTl();
	} else {
		m_nObject = -1;
		m_nMode = -1;
		DISABLE_MOD;
		DISABLE_OBJ;
	}
}

void CPictView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if( 0 == lHint || pSender == this )
		return;

	CMapMgrDoc	*pDoc = GetDocument();
	ASSERT_VALID( pDoc );
	CMapInfo	*pInfo = pDoc->m_pCurrMapInfo;
	CMainFrame	*pFrame = (CMainFrame*) GetParentFrame();
	ASSERT_VALID( pFrame );
	switch( lHint ) {
	case ON_UPDATE_CHGPICTNAME :
		if( ChangePicture() ) {
			if( !IS_OBJ )
				ENABLE_OBJ;
			if( -1 == m_nObject )
				m_nObject = ID_GCP_TL;
			SendMessage( WM_COMMAND, (WPARAM) m_nObject );
		} else {
			DISABLE_MOD;
			DISABLE_OBJ;
		}
		break;
	case ON_UPDATE_DELPICTNAME :
	case ON_UPDATE_ADDPICTNAME :
	case ON_UPDATE_POSTLOADING : {
			LPCTSTR pStrSelection = pInfo ? (LPCTSTR) pInfo->GetIdent() : NULL;
			pFrame->LoadMapIdents( pDoc,  pStrSelection);
		}
		break;
	}
}

void CPictView::OnInitStatusBar( CFrameStatus* pStatusBar )
	{ m_pStatusBar = pStatusBar; }

static void MarkGCP( CDC *pDC, DPOINT *pPt ) {
	CPen		pen, *oldPen;
	int	width = 3;
	COLORREF	color = RGB( 255, 0, 0 );
	
	pen.CreatePen( PS_SOLID, width, color );
	oldPen = pDC->SelectObject( &pen );
	
	pDC->MoveTo( (int) pPt->x + 10, (int) pPt->y ); 
	pDC->LineTo( (int) pPt->x - 10, (int) pPt->y );
	pDC->MoveTo( (int) pPt->x, (int) pPt->y + 10 ); 
	pDC->LineTo( (int) pPt->x, (int) pPt->y - 10 );
	
	pDC->SelectObject( oldPen );
	pen.DeleteObject( );
}

void CPictView::OnDraw(CDC* pDC) {
	CDocument* pDoc = GetDocument();
	CMapInfo	*pMapInfo = GetDocument()->m_pCurrMapInfo;
	// TODO: add draw code here
	if( NULL == m_pPicture )
		return;
	ASSERT_VALID( m_pPicture );

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
		m_pPicture->Draw( pDC, 	rcPict, rcClient, TRUE );
	} CATCH( CPictException, e ) {
		lpictdll::ReportPictException( e );
		DELETE_EXCEPTION( e );
	} END_CATCH
	DPOINT		dp;
	GEOPOINT	gp;
	for( int i = 0; i < pMapInfo->m_gcpArray.GetSize(); i++ ) {
		gp = pMapInfo->m_gcpArray[i].m_ptPictPoint;
		dp.x = froundl( gp.X );
		dp.y = froundl( gp.Y );
		MarkGCP( pDC, &dp );
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPictView diagnostics

#ifdef _DEBUG
void CPictView::AssertValid() const				{ CScrollView::AssertValid(); }
void CPictView::Dump(CDumpContext& dc) const	{ CScrollView::Dump(dc); }
CMapMgrDoc* CPictView::GetDocument() const		{ return (CMapMgrDoc*)m_pDocument; }
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPictView message handlers

int CPictView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CRect	rcClientStart, rcClientNow;
	GetClientRect( rcClientStart );
	RepositionBars( AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0, reposQuery, rcClientNow );
	CPoint	ptOffset( rcClientStart.left - rcClientNow.left, rcClientStart.top - rcClientNow.top );
	CRect	rcChild;
	CWnd* pChild = GetWindow( GW_CHILD );
	while( pChild ) {
		pChild->GetWindowRect(rcChild);
		rcChild.OffsetRect(ptOffset);
		pChild->MoveWindow(rcChild,FALSE);
		pChild = pChild->GetNextWindow();
	}
	CRect	rcWindow;
	GetWindowRect( rcWindow );
	rcWindow.right += rcClientStart.Width() - rcClientNow.Width();
	rcWindow.bottom += rcClientStart.Height() - rcClientNow.Height();
	MoveWindow( rcWindow, FALSE );
	RepositionBars( AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0 );
	return 0;
}

void CPictView::OnMapProperties()  {
	CMapMgrDoc	*pDoc = GetDocument();
	ASSERT_VALID( pDoc );
	CMapInfo	*pInfo = pDoc->m_pCurrMapInfo;

	CDlgMapProperties	dlg;

	dlg.m_pgComm.m_mapType = pInfo->GetType();
	dlg.m_pgComm.m_ptBtmLeft = pInfo->GetBtmLeft();
	dlg.m_pgComm.m_ptTopRight.X = pInfo->GetBtmLeft().X + pInfo->GetSize().dX;
	dlg.m_pgComm.m_ptTopRight.Y = pInfo->GetBtmLeft().Y + pInfo->GetSize().dY;

	for( int i = 0; i < pInfo->m_gcpArray.GetSize(); i++ )
		dlg.m_pgComm.m_gcpArray.Add( pInfo->m_gcpArray.GetAt( i ) );

	dlg.m_pgPictProp.Attach( m_pPicture );

	if( IDOK == dlg.DoModal() ) {
		const MAPTYPE	*pMT = GetTypeFromType( pInfo->GetType() );

		if( NULL == pMT || FALSE == pMT->m_bHaveParser ) {
			pInfo->SetCoord( dlg.m_pgComm.m_ptBtmLeft, dlg.m_pgComm.m_ptTopRight );
		}
	}
}

void CPictView::OnChangeMap( LPCTSTR lpszMapIdent ) {
}

void CPictView::OnRedraw() 
	{ Invalidate(); }

void CPictView::OnUpdateRedraw(CCmdUI* pCmdUI) 
	{ pCmdUI->Enable( NULL != m_pPicture ); }


void CPictView::LoadFilters()
{
	if( NULL == m_pPicture )
		return;
	m_pPicture->RemoveColorFilters();
	if( !m_bRGB ) {
		m_pPicture->AddColorFilter( m_pRGBtoHSB );
	}
	if( m_bRGB && -1 != m_nChannel || !m_bRGB ) {
		m_pPicture->AddColorFilter( m_pExpandColorChannel );
		COLOREXPANDPARAM	p;
		INIT_FILTERSTRUCT( &p, CExpandColorChannel );
		p.nChannel = m_nChannel;
		m_pExpandColorChannel->SetFilterData( &p.p );
	}
}

void CPictView::OnColorcmdShowrgb() {
	m_bRGB = TRUE;
	m_nChannel = -1;
	LoadFilters();
	Invalidate();
}

void CPictView::OnUpdateColorcmdShowrgb(CCmdUI* pCmdUI) {
	pCmdUI->Enable( NULL != m_pPicture && 0 != m_pPicture->GetUsedColors() );
	pCmdUI->SetCheck( m_bRGB && -1 == m_nChannel );
}

void CPictView::OnColorcmdShowr() {
	m_bRGB = TRUE;
	m_nChannel = 0;
	LoadFilters();
	Invalidate();
}

void CPictView::OnUpdateColorcmdShowr(CCmdUI* pCmdUI) {
	pCmdUI->Enable( NULL != m_pPicture && 0 != m_pPicture->GetUsedColors() );
	pCmdUI->SetCheck( m_bRGB && 0 == m_nChannel );
}

void CPictView::OnColorcmdShowg() {
	m_bRGB = TRUE;
	m_nChannel = 1;
	LoadFilters();
	Invalidate();
}

void CPictView::OnUpdateColorcmdShowg(CCmdUI* pCmdUI) {
	pCmdUI->Enable( NULL != m_pPicture && 0 != m_pPicture->GetUsedColors() );
	pCmdUI->SetCheck( m_bRGB && 1 == m_nChannel );
}

void CPictView::OnColorcmdShowb() {
	m_bRGB = TRUE;
	m_nChannel = 2;
	LoadFilters();
	Invalidate();
}

void CPictView::OnUpdateColorcmdShowb(CCmdUI* pCmdUI) {
	pCmdUI->Enable( NULL != m_pPicture && 0 != m_pPicture->GetUsedColors() );
	pCmdUI->SetCheck( m_bRGB && 2 == m_nChannel );
}

void CPictView::OnColorcmdShowhue() {
	m_bRGB = FALSE;
	m_nChannel = 0;
	LoadFilters();
	Invalidate();
}

void CPictView::OnUpdateColorcmdShowhue(CCmdUI* pCmdUI) {
	pCmdUI->Enable( NULL != m_pPicture && 0 != m_pPicture->GetUsedColors() );
	pCmdUI->SetCheck( !m_bRGB && 0 == m_nChannel );
}

void CPictView::OnColorcmdShowsat() {
	m_bRGB = FALSE;
	m_nChannel = 1;
	LoadFilters();
	Invalidate();
}

void CPictView::OnUpdateColorcmdShowsat(CCmdUI* pCmdUI) {
	pCmdUI->Enable( NULL != m_pPicture && 0 != m_pPicture->GetUsedColors() );
	pCmdUI->SetCheck( !m_bRGB && 1 == m_nChannel );
}

void CPictView::OnColorcmdShowbri() {
	m_bRGB = FALSE;
	m_nChannel = 2;
	LoadFilters();
	Invalidate();
}

void CPictView::OnUpdateColorcmdShowbri(CCmdUI* pCmdUI) {
	pCmdUI->Enable( NULL != m_pPicture && 0 != m_pPicture->GetUsedColors() );
	pCmdUI->SetCheck( !m_bRGB && 2 == m_nChannel );
}

////////////////////////////////////////////////////////////////////////////
// Modusumschaltung

void CPictView::OnModeAdd()		{ m_nMode = ID_MODE_ADD; }
void CPictView::OnModeDel()		{ m_nMode = ID_MODE_DEL; }
void CPictView::OnModeEdit()	{ m_nMode = ID_MODE_EDT; }

////////////////////////////////////////////////////////////////////////////
// feste Referenzpunkte

void CPictView::OnGcpBl() {
	m_nObject = ID_GCP_BL;
	DISABLE_MOD; ENABLE_EDT;
	OnModeEdit();
	CMapInfo	*pInfo = GetDocument()->m_pCurrMapInfo;
	if( NULL == pInfo )
		return;
	m_listOfTrackObjects.Lookup( g_szPOINT, (CObject*&) m_pTrackObject );
	GEOPOINT *pt = &pInfo->m_gcpArray[0].m_ptPictPoint;
	m_pTrackObject->Attach( (LPVOID) pt );
	MakeTrackObjectVisible();
}

void CPictView::OnGcpBr() {
	m_nObject = ID_GCP_BR; 
	DISABLE_MOD; ENABLE_EDT;
	OnModeEdit();
	CMapInfo	*pInfo = GetDocument()->m_pCurrMapInfo;
	if( NULL == pInfo )
		return;
	m_listOfTrackObjects.Lookup( g_szPOINT, (CObject*&) m_pTrackObject );
	GEOPOINT *pt = &pInfo->m_gcpArray[1].m_ptPictPoint;
	m_pTrackObject->Attach( (LPVOID) pt );
	MakeTrackObjectVisible();
}

void CPictView::OnGcpTr() {
	m_nObject = ID_GCP_TR; 
	DISABLE_MOD; ENABLE_EDT;
	OnModeEdit();
	CMapInfo	*pInfo = GetDocument()->m_pCurrMapInfo;
	if( NULL == pInfo )
		return;
	m_listOfTrackObjects.Lookup( g_szPOINT, (CObject*&) m_pTrackObject );
	GEOPOINT *pt = &pInfo->m_gcpArray[2].m_ptPictPoint;
	m_pTrackObject->Attach( (LPVOID) pt );
	MakeTrackObjectVisible();
}

void CPictView::OnGcpTl() {
	m_nObject = ID_GCP_TL; 
	DISABLE_MOD; ENABLE_EDT;
	OnModeEdit();
	CMapInfo	*pInfo = GetDocument()->m_pCurrMapInfo;
	if( NULL == pInfo )
		return;
	m_listOfTrackObjects.Lookup( g_szPOINT, (CObject*&) m_pTrackObject );
	GEOPOINT *pt = &pInfo->m_gcpArray[3].m_ptPictPoint;
	m_pTrackObject->Attach( (LPVOID) pt );
	MakeTrackObjectVisible();
}

////////////////////////////////////////////////////////////////////////////
// variable Referenzpunkte

void CPictView::OnGcp() {
	m_nObject = ID_GCP; 
	ENABLE_MOD;
	m_pTrackObject = NULL;
}

////////////////////////////////////////////////////////////////////////////
// Punkt

void CPictView::OnObjPoint() {
	m_nObject = ID_OBJ_POINT; 
	ENABLE_MOD;
	m_pTrackObject = NULL;
}

////////////////////////////////////////////////////////////////////////////
// Linie

void CPictView::OnObjLine() { 
	m_nObject = ID_OBJ_LINE; 
	ENABLE_MOD;
	m_pTrackObject = NULL;
}

void CPictView::OnUpdateModeAdd(CCmdUI* pCmdUI) 
	{ pCmdUI->Enable(IS_ADD); pCmdUI->SetCheck( m_nMode == ID_MODE_ADD ? 1 : 0 ); }

void CPictView::OnUpdateModeDel(CCmdUI* pCmdUI) 
	{ pCmdUI->Enable(IS_DEL); pCmdUI->SetCheck( m_nMode == ID_MODE_DEL ? 1 : 0 ); }

void CPictView::OnUpdateModeEdit(CCmdUI* pCmdUI) 
	{ pCmdUI->Enable(IS_EDT); pCmdUI->SetCheck( m_nMode == ID_MODE_EDT ? 1 : 0 ); }

void CPictView::OnUpdateGcpBl(CCmdUI* pCmdUI) 
	{ pCmdUI->Enable(IS_OBJ); pCmdUI->SetCheck( m_nObject == ID_GCP_BL ? 1 : 0 ); }

void CPictView::OnUpdateGcpBr(CCmdUI* pCmdUI) 
	{ pCmdUI->Enable(IS_OBJ); pCmdUI->SetCheck( m_nObject == ID_GCP_BR ? 1 : 0 ); }

void CPictView::OnUpdateGcpTl(CCmdUI* pCmdUI) 
	{ pCmdUI->Enable(IS_OBJ); pCmdUI->SetCheck( m_nObject == ID_GCP_TL ? 1 : 0 ); }

void CPictView::OnUpdateGcpTr(CCmdUI* pCmdUI) 
	{ pCmdUI->Enable(IS_OBJ); pCmdUI->SetCheck( m_nObject == ID_GCP_TR ? 1 : 0 ); }

void CPictView::OnUpdateGcp(CCmdUI* pCmdUI) 
	{ pCmdUI->Enable(IS_OBJ); pCmdUI->SetCheck( m_nObject == ID_GCP ? 1 : 0 ); }

void CPictView::OnUpdateObjLine(CCmdUI* pCmdUI) 
	{ pCmdUI->Enable(IS_OBJ); pCmdUI->SetCheck( m_nObject == ID_OBJ_LINE ? 1 : 0 ); }

void CPictView::OnUpdateObjPoint(CCmdUI* pCmdUI) 
	{ pCmdUI->Enable(IS_OBJ); pCmdUI->SetCheck( m_nObject == ID_OBJ_POINT ? 1 : 0 ); }

void CPictView::OnLButtonDblClk(UINT nFlags, CPoint point) {
	if( NULL != m_pTrackObject ) {
		CDC *pDC = GetDC();
		m_pTrackObject->StartTracking(pDC,&point);
		ReleaseDC( pDC );
	}
}

void CPictView::OnLButtonDown(UINT nFlags, CPoint point) {
	if( NULL != m_pTrackObject ) {
		CDC *pDC = GetDC();
		CRect	rc;
		GetClientRect( rc );
		ClientToScreen( &rc );
		::ClipCursor( &rc );
		CDPoint ptTD = m_pTrackObject->GetTrackPoint();
		CPoint	ptTL( froundl(ptTD.x), froundl(ptTD.y) );

		m_pTrackObject->StartTracking(pDC,&ptTL);

		ptTL -= GetScrollPosition();
		ClientToScreen( &ptTL );
		::SetCursorPos( ptTL.x, ptTL.y );
		ReleaseDC( pDC );
	}
}

void CPictView::OnLButtonUp(UINT nFlags, CPoint point) {
	if( NULL != m_pTrackObject ) {
		CDC *pDC = GetDC();
		m_pTrackObject->StopTracking(pDC,&point);
		::ClipCursor( NULL );
		ReleaseDC( pDC );
		point += GetScrollPosition();
		m_pTrackObject->StopTracking(&point);
		Invalidate();
		GetDocument()->SetModifiedFlag();
	}
}

void CPictView::OnMouseMove(UINT nFlags, CPoint point) {
	if( NULL != m_pTrackObject ) {
		CDC *pDC = GetDC();
		m_pTrackObject->Track(pDC,&point);
		ReleaseDC( pDC );
	}
	ASSERT_VALID( m_pStatusBar );
	point += GetScrollPosition();
	m_pStatusBar->UpdatePos( &point );
}
