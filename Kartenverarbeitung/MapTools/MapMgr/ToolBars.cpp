#include "stdafx.h"
#include "mapmgr.h"
#include "ToolBars.h"

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: toolbars.cpp 1.1 1996/07/12 10:49:39 andy Exp andy $";
/* $Log: toolbars.cpp $
// Revision 1.1  1996/07/12  10:49:39  andy
// initial version
//
//
*/
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CBaseToolBar

CBaseToolBar::CBaseToolBar()
{
}

CBaseToolBar::~CBaseToolBar()
{
}

const DWORD dwBaseStyle = WS_CHILD|WS_VISIBLE|CBRS_FLOATING|CBRS_FLYBY|CBRS_TOOLTIPS;

BOOL CBaseToolBar::Create( CWnd* pParent, DWORD dwAddStyle, UINT nID, UINT *pIDS, int sizeIDS )
{
	if( !CToolBar::Create( pParent, dwBaseStyle | dwAddStyle, nID )
		|| !LoadBitmap(nID)
		|| !SetButtons(pIDS, sizeIDS/sizeof(UINT) ) )
	{
		ASSERT( FALSE );
		return FALSE;
	}
	CString	S, strWin;
	VERIFY( S.LoadString( nID ) );
	::AfxExtractSubString( strWin, S, 0, '\n' );

	return TRUE;
}

void CBaseToolBar::ResetState()
	{}

BEGIN_MESSAGE_MAP(CBaseToolBar, CToolBar)
	//{{AFX_MSG_MAP(CBaseToolBar)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_MESSAGE(WM_IDLEUPDATECMDUI, OnIdleUpdateCmdUI)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseToolBar message handlers

LRESULT CBaseToolBar::OnIdleUpdateCmdUI(WPARAM wParam, LPARAM) 
{
	if (IsWindowVisible()) 
	{
		CFrameWnd *pParent = (CFrameWnd *)GetOwner();
		if (pParent)
			OnUpdateCmdUI(pParent, (BOOL)wParam);
	}
	return 0L;
}

/////////////////////////////////////////////////////////////////////////////
// CTBModes

CTBModes::CTBModes()
{
}

CTBModes::~CTBModes()
{
}

static UINT nTbID[] = {
	ID_MODE_ADD,
	ID_MODE_EDT,
	ID_MODE_DEL
};

BOOL CTBModes::Create( CWnd* pParent )
{
	return CBaseToolBar::Create( pParent, CBRS_TOP, IDD, nTbID, sizeof( nTbID ) );
}

BEGIN_MESSAGE_MAP(CTBModes, CBaseToolBar)
	//{{AFX_MSG_MAP(CTBModes)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTBModes message handlers

/////////////////////////////////////////////////////////////////////////////
// CTBObjects

CTBObjects::CTBObjects()
{
}

CTBObjects::~CTBObjects()
{
}

static UINT nTbObjects[] = {
	ID_GCP_TL,
	ID_GCP_TR,
	ID_GCP_BR,
	ID_GCP_BL,
	ID_SEPARATOR,
	ID_GCP,
	ID_SEPARATOR,
	ID_OBJ_POINT,
	ID_SEPARATOR,
	ID_OBJ_LINE
};

BOOL CTBObjects::Create( CWnd* pParent )
{
	return CBaseToolBar::Create( pParent, CBRS_LEFT, IDD, nTbObjects, sizeof(nTbObjects) );
}

BEGIN_MESSAGE_MAP(CTBObjects, CBaseToolBar)
	//{{AFX_MSG_MAP(CTBObjects)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTBObjects message handlers

/////////////////////////////////////////////////////////////////////////////
// CTBMaps

CTBMaps::CTBMaps()
{
}

CTBMaps::~CTBMaps()
{
}

static UINT nTbMaps[] = {
	ID_SEPARATOR,
	ID_SEPARATOR,
	ID_ADD_MAP,
	ID_DEL_MAP,
	ID_MAP_PROPERTIES
};

const int nDropHeight = 100;

BOOL CTBMaps::Create( CWnd* pParent )
{
	if( !CBaseToolBar::Create( pParent, CBRS_TOP, IDD, nTbMaps, sizeof( nTbMaps ) ) )
		{ return FALSE; }

	SetButtonInfo(0, ID_MAP_SELECT, TBBS_SEPARATOR, 130);
	SetButtonInfo(1, ID_SEPARATOR, TBBS_SEPARATOR, 12);

	CRect rect;
	GetItemRect(0, &rect);
	rect.top = 3;
	rect.bottom = rect.top + nDropHeight;

	VERIFY( m_cbMapNames.Create(CBS_DROPDOWNLIST|WS_VISIBLE|WS_TABSTOP|WS_VSCROLL, rect, this, ID_MAP_SELECT));

	CFont	font;
	font.Attach(::GetStockObject(ANSI_VAR_FONT));
	m_cbMapNames.SetFont(&font);

	return TRUE;
}

void CTBMaps::AddMapName( LPCTSTR lpszMapName )
{
	m_cbMapNames.AddString( lpszMapName );
}

void CTBMaps::DelMapName( LPCTSTR lpszMapName )
{
	int idx = m_cbMapNames.FindStringExact( -1, lpszMapName );
	ASSERT( LB_ERR != idx );
	m_cbMapNames.DeleteString( idx );
}

void CTBMaps::GetCurSel( CString& S )
{
	S.Empty();
	int	idx = m_cbMapNames.GetCurSel();
	if( LB_ERR != idx )
		m_cbMapNames.GetLBText( idx, S );
}

void CTBMaps::SetCurSel( LPCTSTR lpszCurSel )
{
	m_cbMapNames.SetCurSel( m_cbMapNames.FindStringExact( -1, lpszCurSel ) );
	OnSelchangeMap();
}

BEGIN_MESSAGE_MAP(CTBMaps, CBaseToolBar)
	//{{AFX_MSG_MAP(CTBMaps)
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(ID_MAP_SELECT, OnSelchangeMap)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTBMaps message handlers

void CTBMaps::OnSelchangeMap()
{
	CString	S;
	int	idx = m_cbMapNames.GetCurSel();
	if( LB_ERR != idx )
		m_cbMapNames.GetLBText( idx, S );
	CWnd* pParent = GetOwner();
	ASSERT_VALID( pParent );
	pParent->SendMessage( DOC_CHGMAP, (WPARAM) 0, (LPARAM) (LPCTSTR) S );
}

void CTBMaps::ResetState()
{
	m_cbMapNames.ResetContent();
}
