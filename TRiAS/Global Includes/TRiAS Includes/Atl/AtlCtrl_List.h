													 //////////////////////////////////////////////////////////////////////////////////////
// ListView-Control Template

#define	TVC_PFX(pT)	T* pT = static_cast<T*>(this); _ASSERTE(::IsWindow(pT->m_hWnd));

typedef struct Z_LVCOLUMN : LVCOLUMN {
	Z_LVCOLUMN() { memset(this,0x00,sizeof(*this)); }
} Z_LVCOLUMN;

template <class T, class S>
class TListViewCtrl {
public:
	TListViewCtrl() {}
	~TListViewCtrl() {}
	HIMAGELIST SetImageList(HIMAGELIST hImageList, int nImageListType = LVSIL_NORMAL) {
		TVC_PFX(pT);
		return ListView_SetImageList( pT->m_hWnd, hImageList, nImageListType );
	}
	HIMAGELIST GetImageList(int nImageListType = LVSIL_NORMAL) {
		TVC_PFX(pT);
		return ListView_GetImageList( pT->m_hWnd, nImageListType );
	}
	BOOL SetColumnText( int nColumn, LPCTSTR lpszHeaderText ) {
		TVC_PFX(pT);
		Z_LVCOLUMN	lvc;
		lvc.mask = LVCF_FMT | LVCF_TEXT;
		lvc.fmt = LVCFMT_LEFT;
		lvc.pszText = (LPTSTR) lpszHeaderText;
		return ListView_SetColumn( pT->m_hWnd, nColumn, &lvc );
	}
	BOOL SetItemText( int iItem, int iSubItem, LPCTSTR lpszText ) {
		TVC_PFX(pT);
		return ListView_SetItemText( pT->m_hWnd, iItem, iSubItem, &lpszText );
	}
	S GetItemText( int iItem, int iSubItem ) {
		TVC_PFX(pT);
		TCHAR	sz[_MAX_PATH];
		int cchTextMax = sizeof(sz)/sizeof(sz[0]);
		ListView_GetItemText( pT->m_hWnd, iItem, iSubItem, sz, cchTextMax );
		return S(sz);
	}
	BOOL DeleteColumn( int nColumn ) {
		TVC_PFX(pT);
		return ListView_DeleteColumn( pT->m_hWnd, nColumn );
	}
	int InsertColumn( int nColumn, LPCTSTR lpszHeaderText, int width = 20 ) {
		TVC_PFX(pT);
		Z_LVCOLUMN	lvc;
		lvc.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		lvc.fmt = LVCFMT_LEFT;
		lvc.cx = width;
		lvc.pszText = (LPTSTR) lpszHeaderText;
		return ListView_InsertColumn( pT->m_hWnd, nColumn, &lvc );
	}
	int GetColumnWidth( int nColumn ) {
		TVC_PFX(pT);
		Z_LVCOLUMN	lvc;
		lvc.mask = LVCF_WIDTH;
		ListView_GetColumn( pT->m_hWnd, nColumn, &lvc );
		return lvc.cx;
	}
	BOOL SetColumnWidth( int nColumn, int width ) {
		TVC_PFX(pT);
		Z_LVCOLUMN	lvc;
		lvc.mask = LVCF_WIDTH;
		lvc.cx = width;
		return ListView_SetColumn( pT->m_hWnd, nColumn, &lvc );
	}
};

class AtlListViewCtrl
	: public CContainedWindow
	, public TListViewCtrl<AtlListViewCtrl,CComBSTR>
{
public:
	AtlListViewCtrl( LPTSTR lpszClassName, CMessageMap* pObject, DWORD dwMsgMapID = 0 )
		: CContainedWindow( lpszClassName, pObject, dwMsgMapID )
	{ }
	AtlListViewCtrl( CMessageMap* pObject, DWORD dwMsgMapID = 0 )
		: CContainedWindow( pObject, dwMsgMapID )
	{ }
};
