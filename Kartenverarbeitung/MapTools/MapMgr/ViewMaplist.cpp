#include "stdafx.h"
#include "MapMgrApp.h"

#include "UpdtHint.h"
#include "MapMgrDoc.h"
#include "ViewMaplist.h"

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: viewmaplist.cpp 1.1 1996/07/12 10:50:06 andy Exp andy $";
/* $Log: viewmaplist.cpp $
// Revision 1.1  1996/07/12  10:50:06  andy
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
// CViewMapList

IMPLEMENT_DYNCREATE(CViewMapList, CFormView)

CViewMapList::CViewMapList()
	: CFormView(CViewMapList::IDD)
{
	//{{AFX_DATA_INIT(CViewMapList)
	m_strMapIdent = _T("");
	//}}AFX_DATA_INIT
}

CViewMapList::~CViewMapList()
{
}

void CViewMapList::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewMapList)
	DDX_Control(pDX, IDC_MAPLIST, m_lbMapIdents);
	DDX_LBString(pDX, IDC_MAPLIST, m_strMapIdent);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CViewMapList diagnostics

#ifdef _DEBUG
void CViewMapList::AssertValid() const				{ CFormView::AssertValid(); }
void CViewMapList::Dump(CDumpContext& dc) const		{ CFormView::Dump(dc); }
CMapMgrDoc* CViewMapList::GetDocument() const		{ return (CMapMgrDoc*) CFormView::GetDocument(); }
#endif //_DEBUG

void CViewMapList::ReloadListBox()
{
	m_lbMapIdents.ResetContent();
	CInfoList	*pInfoList = &GetDocument()->m_listOfMapInfos;
	CMapInfo	*pMapInfo;
	CString	S;
	for( POSITION pos = pInfoList->GetHeadPosition(); NULL != pos; )
	{
		pMapInfo = pInfoList->GetNext( pos );
		S = pMapInfo->GetIdent() + '\t';
		S += pMapInfo->m_strBmpPath;
		m_lbMapIdents.AddString( S );
	}
	if( NULL != ( pMapInfo = GetDocument()->m_pCurrMapInfo ) )
		m_lbMapIdents.SetCurSel( m_lbMapIdents.FindString( -1, pMapInfo->GetIdent() ) );
	OnSelchangeMaplist();
}

void CViewMapList::ChangePicture()
{

}

/////////////////////////////////////////////////////////////////////////////
// CViewMapList message map

BEGIN_MESSAGE_MAP(CViewMapList, CFormView)
	//{{AFX_MSG_MAP(CViewMapList)
	ON_LBN_SELCHANGE(IDC_MAPLIST, OnSelchangeMaplist)
	ON_LBN_DBLCLK(IDC_MAPLIST, OnDblclkMaplist)
	//}}AFX_MSG_MAP
	ON_LBN_MOVEUP( IDC_MAPLIST, OnMoveUp )
	ON_LBN_MOVEDOWN( IDC_MAPLIST, OnMoveDown )
	ON_LBN_ADDITEM( IDC_MAPLIST, OnAddItem )
	ON_LBN_DELITEM( IDC_MAPLIST, OnDelItem )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewMapList message handlers

void CViewMapList::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	ReloadListBox();
}

void CViewMapList::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) {
	if( 0 == lHint || pSender == this )
		return;

	switch( lHint ) {
	case ON_UPDATE_ADDPICTNAME :
		ReloadListBox();
		break;
	case ON_UPDATE_DELPICTNAME :
		ReloadListBox();
		break;
	case ON_UPDATE_CHGPICTNAME : {
			CString	S, strIdent, strPath;
			CMapInfo	*pMapInfo = GetDocument()->m_pCurrMapInfo;
			if( NULL == pMapInfo ) {
				m_lbMapIdents.ResetContent();
				return;
			}
			ASSERT_VALID( pMapInfo );
			int idx = m_lbMapIdents.FindString(-1,pMapInfo->GetIdent());
			if( LB_ERR != idx ) {
				m_lbMapIdents.GetText( idx, S );
				::AfxExtractSubString(strIdent,S,0,'\t');
				::AfxExtractSubString(strPath,S,1,'\t');
				if( strIdent != pMapInfo->GetIdent() || strPath != pMapInfo->m_strBmpPath ) {
					strIdent = pMapInfo->GetIdent();
					strIdent += '\t';
					strIdent += pMapInfo->m_strBmpPath;
					m_lbMapIdents.DeleteString(idx);
					m_lbMapIdents.InsertString( idx, strIdent );
					m_lbMapIdents.SetCurSel( idx );
				}
			}
			else
				ReloadListBox();
		}
		break;
	}
}

void CViewMapList::OnSelchangeMaplist() {
	CString	S, strMapIdent;
	int idx = m_lbMapIdents.GetCurSel();
	if( LB_ERR != idx ) {
		m_lbMapIdents.GetText( idx, S );
		::AfxExtractSubString(strMapIdent,S,0,'\t');
	}
	LPCTSTR pStrMapIdent = strMapIdent.IsEmpty() ? NULL : (LPCTSTR) strMapIdent;
	GetDocument()->ChangeMapIdent( pStrMapIdent );
}

void CViewMapList::OnAddItem() {
	GetParent()->SendMessage( WM_COMMAND, (WPARAM) ID_ADD_MAP );
	OnSelchangeMaplist();
}

void CViewMapList::OnDelItem() {
	GetParent()->SendMessage( WM_COMMAND, (WPARAM) ID_DEL_MAP );
	OnSelchangeMaplist();
}

void CViewMapList::OnMoveUp()
	{ }

void CViewMapList::OnMoveDown()
	{ }

void CViewMapList::OnDblclkMaplist() {
	GetParent()->SendMessage( WM_COMMAND, (WPARAM) ID_MAP_MODIFY_FILENAME, (LPARAM) 0 );
}
