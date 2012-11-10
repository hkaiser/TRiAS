#include "stdafx.h"

#include "libTopoMap/LibTopoMapRes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

void DDX_Control(CDataExchange* pDX, int nIDC, CMapTreeCtrl& rControl)
{
	if (rControl.m_hWnd == NULL)    // not subclassed yet
	{
		ASSERT(!pDX->m_bSaveAndValidate);
		HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
		if (!rControl.SubclassWindow(hWndCtrl))
		{
			ASSERT(FALSE);      // possibly trying to subclass twice?
			AfxThrowNotSupportedException();
		}
		rControl.InitTree();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMapTreeCtrl

static char buf[128];
static char buf2[128];

static ostrstream os( buf, sizeof( buf ) );

static char *_pszMapTypeAS = "AS";
static char *_pszMapTypeAV = "AV";
static char *_pszMapTypeN = "N";

CMapTreeCtrl::CMapTreeCtrl()
{
	m_ptBtmLeft = GEOPOINT();
	m_szMap = GEOSIZE();
	m_scale = -1;
}

CMapTreeCtrl::~CMapTreeCtrl()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMapTreeCtrl Diagnostics

#ifdef DEBUG
void CMapTreeCtrl::AssertValid( ) const			{ CTreeCtrl::AssertValid(); }
#endif

void CMapTreeCtrl::DoDataExchange(CDataExchange* pDX) 
{
	CTreeCtrl::DoDataExchange(pDX);
	if( pDX->m_bSaveAndValidate )
	{
		CString	strMapType;

		TV_ITEM tvi;
		tvi.hItem = GetSelectedItem();
		tvi.mask = TVIF_HANDLE | TVIF_TEXT;
		tvi.pszText = buf2;
		tvi.cchTextMax = sizeof( buf2 ) - 1;
		GetItem( &tvi );
		m_strMapIdent = buf2;

		HTREEITEM hTi;
		while( hTi = GetParentItem( tvi.hItem ) )
			tvi.hItem = hTi;
		GetItem( &tvi );
		::AfxExtractSubString( strMapType, buf2, 0, ' ' );

		m_ptBtmLeft = GEOPOINT();
		m_szMap = GEOSIZE();
		m_scale = -1;

		if( _pszMapTypeAS == strMapType )
		{
			ParserForASMap::ParseMapName( m_strMapIdent, m_ptBtmLeft, m_szMap, m_scale );
			m_mapType = MPT_AS;
		}
		else if( _pszMapTypeN == strMapType )
		{
			ParserForNMap::ParseMapName( m_strMapIdent, m_ptBtmLeft, m_szMap, m_scale );
			m_mapType = MPT_N;
		}
		else if( _pszMapTypeAV == strMapType )
		{
			ParserForAVMap::ParseMapName( m_strMapIdent, m_ptBtmLeft, m_szMap, m_scale );
			m_mapType = MPT_AV;
		}
		else
			m_mapType = MPT_UNKNOWN;
	}
}

BEGIN_MESSAGE_MAP(CMapTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CMapTreeCtrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapTreeCtrl operations

void CMapTreeCtrl::InitTree()
{
	TV_INSERTSTRUCT	tvi;
	CString	S;

	tvi.item.mask = TVIF_HANDLE | TVIF_TEXT;

	VERIFY( S.LoadString( IDS_MAPTYPE_AS ) );
	tvi.hParent = TVI_ROOT;
	tvi.hInsertAfter = TVI_LAST;
	tvi.item.pszText = (char*) (LPCTSTR) S;
	tvi.hParent = InsertItem( &tvi );
	S += "#";
	S += _pszMapTypeAS;
	S += "#1";
	tvi.item.pszText = (char*) (LPCTSTR) S;
	InsertItem( &tvi );

	VERIFY( S.LoadString( IDS_MAPTYPE_AV ) );
	tvi.hParent = TVI_ROOT;
	tvi.hInsertAfter = TVI_LAST;
	tvi.item.pszText = (char*) (LPCTSTR) S;
	tvi.hParent = InsertItem( &tvi );
	S += "#";
	S += _pszMapTypeAV;
	S += "#1";
	tvi.item.pszText = (char*) (LPCTSTR) S;
	InsertItem( &tvi );

	VERIFY( S.LoadString( IDS_MAPTYPE_N ) );
	tvi.hParent = TVI_ROOT;
	tvi.hInsertAfter = TVI_LAST;
	tvi.item.pszText = (char*) (LPCTSTR) S;
	tvi.hParent = InsertItem( &tvi );
	S += "#";
	S += _pszMapTypeN;
	S += "#1";
	tvi.item.pszText = (char*) (LPCTSTR) S;
	InsertItem( &tvi );
}

void CMapTreeCtrl::ExpandAVMap( HTREEITEM hTi, int level )
{
}

void CMapTreeCtrl::ExpandNMap( HTREEITEM hTi, int level )
{
	CString	S;
	HTREEITEM	hTiParent = GetParentItem( hTi );
	HTREEITEM	hTiSelect = NULL;
	TV_INSERTSTRUCT	tvi;
	tvi.hInsertAfter = TVI_LAST;
	tvi.item.mask = TVIF_HANDLE | TVIF_TEXT;
	TV_ITEM	tvParent;
	if( level > 1 )
	{
		tvParent.hItem = GetParentItem( hTi );
		tvParent.mask = TVIF_HANDLE | TVIF_TEXT;
		tvParent.pszText = buf2;
		tvParent.cchTextMax = sizeof( buf2 ) - 1;
		GetItem( &tvParent );
	}
	DeleteItem( hTi );
	switch( level )
	{
	case 1 :
		{
			for( int row = 7; row < 88; row += 8 )
			{
				tvi.hParent = hTiParent;
				os.seekp(0);
				os << "CC" << " - ";
				os.width(2); os.fill( '0' );
				os << row << " ..." << ends;
				tvi.item.pszText = os.str();
				if( NULL == hTiSelect )
					hTiSelect = hTiParent;

				tvi.hParent = InsertItem( &tvi );
				os.seekp( os.tellp() - 1 );
				os << '#' << _pszMapTypeN << '#' << level + 1 << ends;
				tvi.item.pszText = os.str();
				InsertItem( &tvi );
			}
		}
		break;
	case 2 :
		{
			long	row;
			::AfxExtractSubString( S, buf2, 2, ' ' );
			row = atol( S );
			for( int col = 2; col < 51; col += 8 )
			{
				tvi.hParent = hTiParent;
				os.seekp( 0 );
				os << "CC - ";
				os.width(2); os.fill('0'); os << row;
				os.width(2); os.fill('0'); os << col;
				os << ends;
				tvi.item.pszText = os.str();
				if( NULL == hTiSelect )
					hTiSelect = hTiParent;
				tvi.hParent = InsertItem( &tvi );
				os.seekp( os.tellp() - 1 );
				os << '#' << _pszMapTypeN << '#' << level + 1 << ends;
				tvi.item.pszText = os.str();
				InsertItem( &tvi );
			}
		}
		break;
	case 3 :
		{
			long	row, col, newRow, newCol;
			::AfxExtractSubString( S, buf2, 2, ' ' );
			row = atol( S );
			col = row % 100;
			row /= 100;
			for( int quad = 0; quad < 4; quad++ )
			{
				tvi.hParent = hTiParent;
				switch( quad )		// !!! 'kartographisch' zählen
				{
				case 0 : newRow = row - 4; newCol = col; break;
				case 1 : newRow = row - 4; newCol = col + 4; break;
				case 2 : newRow = row; newCol = col; break;
				case 3 : newRow = row; newCol = col + 4; break;
				}
				os.seekp( 0 );
				os << "C - ";
				os.width(2); os.fill('0'); os << newRow;
				os.width(2); os.fill('0'); os << newCol;
				os << ends;
				tvi.item.pszText = os.str();
				if( NULL == hTiSelect )
					hTiSelect = hTiParent;
				tvi.hParent = InsertItem( &tvi );
				os.seekp( os.tellp() - 1 );
				os << '#' << _pszMapTypeN << '#' << level + 1 << ends;
				tvi.item.pszText = os.str();
				InsertItem( &tvi );
			}
		}
		break;
	case 4 :
		{
			long	row, col, newRow, newCol;
			::AfxExtractSubString( S, buf2, 2, ' ' );
			row = atol( S );
			col = row % 100;
			row /= 100;
			for( int quad = 0; quad < 4; quad++ )
			{
				tvi.hParent = hTiParent;
				switch( quad )		// !!! 'kartographisch' zählen
				{
				case 0 : newRow = row - 2; newCol = col; break;
				case 1 : newRow = row - 2; newCol = col + 2; break;
				case 2 : newRow = row; newCol = col; break;
				case 3 : newRow = row; newCol = col + 2; break;
				}
				os.seekp( 0 );
				os << "L - ";
				os.width(2); os.fill('0'); os << newRow;
				os.width(2); os.fill('0'); os << newCol;
				os << ends;
				tvi.item.pszText = os.str();
				if( NULL == hTiSelect )
					hTiSelect = hTiParent;
				tvi.hParent = InsertItem( &tvi );
				os.seekp( os.tellp() - 1 );
				os << '#' << _pszMapTypeN << '#' << level + 1 << ends;
				tvi.item.pszText = os.str();
				InsertItem( &tvi );
			}
		}
		break;
	case 5 :
		{
			long	row, col, newRow, newCol;
			::AfxExtractSubString( S, buf2, 2, ' ' );
			row = atol( S );
			col = row % 100;
			row /= 100;
			for( int quad = 0; quad < 4; quad++ )
			{
				tvi.hParent = hTiParent;
				switch( quad )		// !!! 'kartographisch' zählen
				{
				case 0 : newRow = row - 1; newCol = col; break;
				case 1 : newRow = row - 1; newCol = col + 1; break;
				case 2 : newRow = row; newCol = col; break;
				case 3 : newRow = row; newCol = col + 1; break;
				}
				os.seekp( 0 );
				os << "";
				os.width(2); os.fill('0'); os << newRow;
				os.width(2); os.fill('0'); os << newCol;
				os << ends;
				tvi.item.pszText = os.str();
				if( NULL == hTiSelect )
					hTiSelect = hTiParent;
				tvi.hParent = InsertItem( &tvi );
				os.seekp( os.tellp() - 1 );
				os << '#' << _pszMapTypeN << '#' << level + 1 << ends;
				tvi.item.pszText = os.str();
				InsertItem( &tvi );
			}
		}
		break;
	case 6 :
		{
			for( int quad = 0; quad < 4; quad++ )
			{
				tvi.hParent = hTiParent;
				os.seekp( 0 );
				os << buf2;
				switch( quad )		// !!! 'kartographisch' zählen
				{
				case 0 : os << " - NW"; break;
				case 1 : os << " - NO"; break;
				case 2 : os << " - SW"; break;
				case 3 : os << " - SO"; break;
				}
				os << ends;
				tvi.item.pszText = os.str();
				if( NULL == hTiSelect )
					hTiSelect = hTiParent;
				tvi.hParent = InsertItem( &tvi );
			}
		}
		break;
	}
}

void CMapTreeCtrl::ExpandASMap( HTREEITEM hTi, int level )
{
	HTREEITEM	hTiParent = GetParentItem( hTi );
	HTREEITEM	hTiSelect = NULL;

	TV_INSERTSTRUCT	tvi;
	tvi.hInsertAfter = TVI_LAST;
	tvi.item.mask = TVIF_HANDLE | TVIF_TEXT;

	TV_ITEM			tvParent;

	if( level > 1 )
	{
		tvParent.hItem = GetParentItem( hTi );
		tvParent.mask = TVIF_HANDLE | TVIF_TEXT;
		tvParent.pszText = buf2;
		tvParent.cchTextMax = sizeof( buf2 ) - 1;
		GetItem( &tvParent );
	}

	DeleteItem( hTi );

	switch( level )
	{
	case 1 :
		{
			for( int row = 'L'; row < 'P'; row++ )
			{
				for( int col = 32; col < 35; col++ )
				{
					tvi.hParent = hTiParent;
					os.seekp(0);
					os << (char) row << '-' << col << ends;
					tvi.item.pszText = os.str();
					if( NULL == hTiSelect )
						hTiSelect = hTiParent;

					tvi.hParent = InsertItem( &tvi );
					os.seekp( os.tellp() - 1 );
					os << '#' << _pszMapTypeAS << '#' << level + 1 << ends;
					tvi.item.pszText = os.str();
					InsertItem( &tvi );
				}
			}
			SelectItem( hTiSelect );
		}
		break;

	/////////////////////////////////////////////////////////////////////////
	// ein 1:1.000.000 - Blatt enthält (12x12) 1:100.000 Blätter
	// damit nicht 144 Blätter untereinander stehen wird in 12x12 aufgeteilt ...
	// ... entspricht auch der Anordnung im 1:1.000.000 - Blatt ...

	case 2 :
		{
			for( int row = 1; row < 145; row += 12 )
			{
				tvi.hParent = hTiParent;
				os.seekp(0);
				os << buf2 << '-' << row << " ... " << row + 11 << ends;
				tvi.item.pszText = os.str();

				tvi.hParent = InsertItem( &tvi );
				os.seekp( os.tellp() - 1 );
				os << '#' << _pszMapTypeAS << '#' << level + 1 << ends;
				tvi.item.pszText = os.str();
				InsertItem( &tvi );
			}
		}
		break;
	case 3 :
		{
			CString	strCol;
			::AfxExtractSubString( strCol, buf2, 0, ' ' );
			::AfxExtractSubString( strCol, strCol, 2, '-' );
			int col = atoi( strCol );
			int colEnd = col + 12;
			tvParent.hItem = GetParentItem( hTiParent );
			tvParent.mask = TVIF_HANDLE | TVIF_TEXT;
			tvParent.pszText = buf2;
			tvParent.cchTextMax = sizeof( buf2 ) - 1;
			GetItem( &tvParent );

			for( ; col < colEnd; col++ )
			{
				tvi.hParent = hTiParent;
				os.seekp(0);
				os << buf2 << '-' << col << ends;
				tvi.item.pszText = os.str();
				if( NULL == hTiSelect )
					hTiSelect = hTiParent;

				tvi.hParent = InsertItem( &tvi );
				os.seekp( os.tellp() - 1 );
				os << '#' << _pszMapTypeAS << '#' << level + 1 << ends;
				tvi.item.pszText = os.str();
				InsertItem( &tvi );
			}
			SelectItem( hTiSelect );
		}
		break;
	case 4 :
		{
			for( int quad = 'A'; quad < 'E'; quad++ )
			{
				tvi.hParent = hTiParent;
				os.seekp(0);
				os << buf2 << '-' << (char) quad << ends;
				tvi.item.pszText = os.str();
				if( NULL == hTiSelect )
					hTiSelect = hTiParent;

				tvi.hParent = InsertItem( &tvi );
				os.seekp( os.tellp() - 1 );
				os << '#' << _pszMapTypeAS << '#' << level + 1 << ends;
				tvi.item.pszText = os.str();
				InsertItem( &tvi );
			}
			SelectItem( hTiSelect );
		}
		break;
	case 5 :
		{
			for( int quad = 'a'; quad < 'e'; quad++ )
			{
				tvi.hParent = hTiParent;
				os.seekp(0);
				os << buf2 << '-' << (char) quad << ends;
				tvi.item.pszText = os.str();
				if( NULL == hTiSelect )
					hTiSelect = hTiParent;

				tvi.hParent = InsertItem( &tvi );
				os.seekp( os.tellp() - 1 );
				os << '#' << _pszMapTypeAS << '#' << level + 1 << ends;
				tvi.item.pszText = os.str();
				InsertItem( &tvi );
			}
			SelectItem( hTiSelect );
		}
		break;
	case 6 :
		{
			for( int quad = 1; quad < 5; quad++ )
			{
				tvi.hParent = hTiParent;
				os.seekp(0);
				os << buf2 << '-' << quad << ends;
				tvi.item.pszText = os.str();
				if( NULL == hTiSelect )
					hTiSelect = hTiParent;

				InsertItem( &tvi );
			}
			SelectItem( hTiSelect );
		}
		break;
	default :
		return;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMapTreeCtrl message handlers

BOOL CMapTreeCtrl::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult) 
{
	TV_ITEM	tvi;
	CString	strMapType, strMapLevel;
	int	mapLevel;

	if( WM_NOTIFY == message )
	{
		LPNM_TREEVIEW lpnmtv = (LPNM_TREEVIEW) lParam;
		register UINT action = lpnmtv->hdr.code;
		switch( action )
		{
		case TVN_ITEMEXPANDING :
			{
				tvi.hItem = lpnmtv->itemNew.hItem;
				tvi.mask = TVIF_HANDLE | TVIF_TEXT;
				tvi.pszText = buf;
				tvi.cchTextMax = sizeof( buf ) - 1;
				GetItem( &tvi );
				tvi.hItem = GetNextItem( lpnmtv->itemNew.hItem, TVGN_CHILD );
				tvi.mask = TVIF_HANDLE | TVIF_TEXT;
				tvi.pszText = buf2;
				tvi.cchTextMax = sizeof( buf2 ) - 1;
				GetItem( &tvi );
				if( '#' == buf2[ strlen( buf ) ] )		// Item noch nicht benutzt ... expandieren
				{
					::AfxExtractSubString( strMapType, buf2, 1, '#' );
					::AfxExtractSubString( strMapLevel, buf2, 2, '#' );
					mapLevel = atoi( strMapLevel );

					if( _pszMapTypeAS == strMapType )
						ExpandASMap( tvi.hItem, mapLevel );
					else if( _pszMapTypeAV == strMapType )
						ExpandAVMap( tvi.hItem, mapLevel );
					else if( _pszMapTypeN == strMapType )
						ExpandNMap( tvi.hItem, mapLevel );
					else
					;
				}
			}					// fall trough TV_SELCHANGED
		case TVN_SELCHANGED :
			{
				UpdateData();
			}
			break;
		}
	}
	return CTreeCtrl::OnChildNotify(message, wParam, lParam, pLResult);
}

#define	BORDERSIZE	10

void CMapTreeCtrl::MoveWindow( int x, int y, int nWidth, int nHeight, BOOL bRepaint )
{
	CRect rc( x, y, x + nWidth, y + nHeight );
	CWnd::MoveWindow( &rc, bRepaint );
}

void CMapTreeCtrl::MoveWindow( LPCRECT lpRect, BOOL bRepaint )
{
	CRect rc = *lpRect;
	rc.InflateRect( -BORDERSIZE, -BORDERSIZE );
	CWnd::MoveWindow( &rc, bRepaint );
}
