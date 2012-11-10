#include "stdafx.h"
#include "MapMgrApp.h"

#include "dialogs.h"

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: dialogs.cpp 1.1 1996/07/12 10:48:53 andy Exp andy $";
/* $Log: dialogs.cpp $
// Revision 1.1  1996/07/12  10:48:53  andy
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

#pragma warning( disable : 4270 )

/////////////////////////////////////////////////////////////////////////////
// CMapSelectDialog dialog

CMapSelectDialog::CMapSelectDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMapSelectDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMapSelectDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CMapSelectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMapSelectDialog)
	DDX_Control(pDX, IDC_TREE_OF_MAPS, m_treeOfMapTypes);
	//}}AFX_DATA_MAP
}

static char buf[128];
static ostrstream os(buf,sizeof(buf));

BOOL CMapSelectDialog::UpdateData( BOOL bSaveAndValidate )
{
	CDialog::UpdateData( bSaveAndValidate );
	if( !bSaveAndValidate )
	{
		os.seekp(0);
		os << m_treeOfMapTypes.m_strMapIdent;

		if( -1 != m_treeOfMapTypes.m_scale )
		{
			TOPOMAPTYPE	t = m_treeOfMapTypes.m_mapType;
			CString strMapType = MPT_UNKNOWN == t ? "???" :
				MPT_AS == t ? "AS" :
				MPT_AV == t ? "AV" :
				MPT_N == t ? "N" :
				"???";

			os << " (" << strMapType << ") ";
			os << " 1:" << m_treeOfMapTypes.m_scale << endl;
	
			os << DMS( "[$d°$m\'$s\"", m_treeOfMapTypes.m_ptBtmLeft.X );
			os << " , ";
			os << DMS( "$d°$m\'$s\"]", m_treeOfMapTypes.m_ptBtmLeft.Y );

			os << DMS( "[$d°$m\'$s\"", m_treeOfMapTypes.m_szMap.dX );
			os << " x ";
			os << DMS( "$d°$m\'$s\"]", m_treeOfMapTypes.m_szMap.dY );
		}
		os << ends;
		GetDlgItem( IDC_MAPDESCR )->SetWindowText( os.str() );
	}
	return TRUE;
}

BEGIN_MESSAGE_MAP(CMapSelectDialog, CDialog)
	//{{AFX_MSG_MAP(CMapSelectDialog)
	ON_BN_CLICKED(IDC_BTN_APPLY, OnBtnApply)
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_TREE_OF_MAPS, OnItemexpandedTreeOfMaps)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_OF_MAPS, OnSelchangedTreeOfMaps)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapSelectDialog message handlers

void CMapSelectDialog::OnBtnApply() 
{
}

void CMapSelectDialog::OnItemexpandedTreeOfMaps(NMHDR* pNMHDR, LRESULT* pResult) 
	{ UpdateData(FALSE); *pResult = 0; }

void CMapSelectDialog::OnSelchangedTreeOfMaps(NMHDR* pNMHDR, LRESULT* pResult) 
	{ UpdateData(FALSE); *pResult = 0; }

BOOL CMapSelectDialog::OnInitDialog() 
	{ return CDialog::OnInitDialog(); }

/////////////////////////////////////////////////////////////////////////////
// CDlgMapName dialog

CDlgMapName::CDlgMapName(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMapName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMapName)
	m_mapType = -1;
	m_strMapIdent = _T("");
	//}}AFX_DATA_INIT
}

void CDlgMapName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMapName)
	DDX_Radio(pDX, IDC_MAP_AS, m_mapType);
	DDX_Text(pDX, IDC_EDIT_MAPNAME, m_strMapIdent);
	//}}AFX_DATA_MAP
}

BOOL CDlgMapName::UpdateData( BOOL bSaveAndValidate )
{
	return CDialog::UpdateData( bSaveAndValidate );
}

BEGIN_MESSAGE_MAP(CDlgMapName, CDialog)
	//{{AFX_MSG_MAP(CDlgMapName)
	ON_BN_CLICKED(IDC_BTN_TREE, OnBtnTree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMapName message handlers

BOOL CDlgMapName::OnInitDialog() 
{
	return CDialog::OnInitDialog();
}

void CDlgMapName::OnBtnTree() 
{
	CMapSelectDialog	dlg( this );
	if( IDOK == dlg.DoModal() )
	{
		m_strMapIdent = dlg.m_treeOfMapTypes.m_strMapIdent;
		m_mapType = dlg.m_treeOfMapTypes.m_mapType;
		UpdateData( FALSE );
	}
}
