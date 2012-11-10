// EDBS_CfgImpObj.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "MetaData.h"
#include "EDBS_CfgImpObj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Eigenschaftenseite EDBS_CfgImpObj 

IMPLEMENT_DYNCREATE(CEDBS_CfgImpObj, CPropertyPage)

CEDBS_CfgImpObj::CEDBS_CfgImpObj() : CPropertyPage(CEDBS_CfgImpObj::IDD)
{
	//{{AFX_DATA_INIT(EDBS_CfgImpObj)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
}

CEDBS_CfgImpObj::~CEDBS_CfgImpObj()
{
}

void CEDBS_CfgImpObj::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEDBS_CfgImpObj)
	DDX_Control(pDX, IDC_SEP1, m_Sep1);
	DDX_Control(pDX, IDC_BTNSELECT, m_btnSelect);
	DDX_Control(pDX, IDC_lvObjects, m_lvObjects);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEDBS_CfgImpObj, CPropertyPage)
	//{{AFX_MSG_MAP(CEDBS_CfgImpObj)
	ON_NOTIFY(NM_CLICK, IDC_lvObjects, OnClicklvObjects)
	ON_BN_CLICKED(IDC_BTNSELECT, OnClickBtnSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten EDBS_CfgImpObj 

void CEDBS_CfgImpObj::SetWizardButtons()
{
	CPropertySheet* pPropertySheet = (CPropertySheet*) GetParent();   
//	int iActivePage = pPropertySheet->GetActiveIndex();
//	if( 0 == iActivePage ) {
//		if( iActivePage == pPropertySheet->GetPageCount() - 1 )
//			pPropertySheet->SetWizardButtons(PSWIZB_FINISH);
//		else
//			pPropertySheet->SetWizardButtons(PSWIZB_NEXT);
//	}
//	else if( iActivePage == pPropertySheet->GetPageCount() - 1 )
		pPropertySheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
//	else
//		pPropertySheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
}

void CEDBS_CfgImpObj::InitImageList(void)
{
	HIMAGELIST hWndImageList, hWndImageListState;

	// normal images and overlay image
	m_cIList.Create(16, 16, ILC_COLOR | ILC_MASK, 6, 8);

	hWndImageList = m_cIList.m_hImageList;
	if(!hWndImageList)
		return ;

	HBITMAP hBitmap1;
	hBitmap1 = ::LoadBitmap (g_hInstance, MAKEINTRESOURCE(IDB_FOLDERS));
	m_idiFolderClosed = m_cIList.Add( CBitmap::FromHandle(hBitmap1), RGB(255,0,0));

/*
	// add an overlay image form an icon
	HICON hIcon;
	hIcon = ::LoadIcon (g_hInstance, MAKEINTRESOURCE(IDI_OVERLAY));
	ASSERT( hIcon );
	int iImage = m_cIList.Add(hIcon);
	m_idiOverlay = 1;
	m_cIList.SetOverlayImage( iImage, m_idiOverlay );
*/
	// state images
	m_cIListState.Create(16, 16, ILC_COLOR | ILC_MASK, 3, 0);
	hWndImageListState = m_cIListState.m_hImageList;
	if(!hWndImageListState)
		return ;

	HBITMAP hBitmap2;
	hBitmap2 = ::LoadBitmap (g_hInstance, MAKEINTRESOURCE(IDB_CHKBOXS));
	m_idiFolderClosed = m_cIListState.Add( CBitmap::FromHandle(hBitmap2), RGB(255,0,0));

	m_idiFolderOpen = m_idiFolderClosed+1;
	m_idiText = m_idiFolderClosed+2;

//	m_lvObjects.SetImageList(&m_cIListState , LVSIL_STATE);
	m_lvObjects.SetImageList(&m_cIList , LVSIL_SMALL);

	
	return;

}

BOOL CEDBS_CfgImpObj::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	CRect rect;
	LVCOLUMN lvcol;
	CxString strButton;

	m_tBtnSelect = true;
	strButton.LoadString(IDS_CFGOBJSELALL);
	SetDlgItemText( IDC_BTNSELECT, strButton );

	m_lvObjects.GetClientRect( rect );

//	m_lvObjects.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES | LVS_EX_SUBITEMIMAGES);
	m_lvObjects.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);

	memset(&lvcol,0,sizeof(LVCOLUMN));

	lvcol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvcol.fmt = LVCFMT_LEFT;
//	lvcol.cx = (int)((rect.Width()-20) * .20);
	lvcol.cx = 48;
	lvcol.pszText = "Folie";
	lvcol.iSubItem = 0;
	m_lvObjects.InsertColumn( 0, &lvcol );

	lvcol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lvcol.fmt = LVCFMT_LEFT;
	lvcol.cx = (int)(rect.Width() - 48);
	lvcol.pszText = "Kurztext";
	lvcol.iSubItem = 1;
	m_lvObjects.InsertColumn( 2, &lvcol );

	InitImageList();

	SetWizardButtons();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

BOOL CEDBS_CfgImpObj::OnSetActive() 
{
	LoadConfig();	
	SetWizardButtons();
	return CPropertyPage::OnSetActive();
}

LRESULT CEDBS_CfgImpObj::OnWizardNext() 
{
	SaveConfig();
	
	return CPropertyPage::OnWizardNext();
}

BOOL CEDBS_CfgImpObj::OnWizardFinish() 
{
	SaveConfig();
	
	m_pConfiguration->Save();

	return CPropertyPage::OnWizardFinish();
}


void CEDBS_CfgImpObj::LoadConfig()
{
	POSITION	pos;
	CString		key;
	CRule_Layer	*pRule_Layer;
	CString strFolie;
	CString strKurztext;
	CString strText;
	CDBVariant vImportmodus;

	m_lvObjects.DeleteAllItems();

	LVITEM			lvi;
	int				iItem;

	for ( pos = g_pMetaData->m_Rules_Layer.GetStartPosition(); pos != NULL; ) {
		g_pMetaData->m_Rules_Layer.GetNextAssoc( pos, key, (CObject*&)pRule_Layer );

//		lvi.mask = LVIF_STATE;
		lvi.mask = LVIF_TEXT;
		lvi.iItem = m_lvObjects.GetItemCount();
		lvi.pszText = pRule_Layer->Folie().GetBuffer(pRule_Layer->Folie().GetLength());
		lvi.iSubItem = 0;
/*
		if( 0 != pRule_Layer->ImportMode() )
			lvi.state = INDEXTOSTATEIMAGEMASK(2);
		else
			lvi.state = INDEXTOSTATEIMAGEMASK(1);
		lvi.stateMask = LVIS_SELECTED | LVIS_STATEIMAGEMASK;
*/
		iItem = m_lvObjects.InsertItem( &lvi );
		if( iItem >= 0 ) {
			m_lvObjects.SetItemText( iItem, 1, pRule_Layer->Kurztext() );
		}
		pRule_Layer->Folie().ReleaseBuffer();

		lvi.mask = LVIF_IMAGE;
		lvi.iItem = iItem;
		lvi.iSubItem = 0;
		if( 0 != pRule_Layer->ImportMode() )
			lvi.iImage = 5;
		else
			lvi.iImage = 4;
		m_lvObjects.SetItem(&lvi);

		lvi.mask = LVIF_IMAGE;
		lvi.iItem = iItem;
		lvi.iSubItem = 1;
		if( pRule_Layer->Resolve() )
			lvi.iImage = 2;
		else
			lvi.iImage = 1;
		m_lvObjects.SetItem( &lvi );
	}

	UpdateData(false);
}

void CEDBS_CfgImpObj::SaveConfig()
{

}

/////////////// overlay image helpers
void CEDBS_CfgImpObj::SetItemOverlayImage( HTREEITEM hti, int iImage )
{
	TV_ITEM tvi;
	::ZeroMemory(&tvi, sizeof(TV_ITEM));
	tvi.hItem = hti;
	tvi.mask = TVIF_HANDLE | TVIF_STATE;
	tvi.stateMask = TVIS_OVERLAYMASK;
	tvi.state = INDEXTOOVERLAYMASK( iImage );
//	m_trObjects.SetItem( &tvi );
}

void CEDBS_CfgImpObj::OnClicklvObjects(NMHDR* pNMHDR, LRESULT* pResult) 
{
//	BOOL result;
//	static HTREEITEM  ghtiPrevItem = NULL;

	UINT			state;
	DWORD			dwpos;
	LV_HITTESTINFO	lvhti;
	POINT			point;
	LVITEM			lvi;

//	CRect rect;
//	result = ::GetWindowRect( m_trObjects.m_hWnd, (LPRECT)rect );

	// find out where the cursor was
	dwpos = GetMessagePos();
	point.x = LOWORD(dwpos);
	point.y = HIWORD(dwpos);

	::MapWindowPoints(HWND_DESKTOP, m_lvObjects.m_hWnd, &point, 1);

	lvhti.pt = point;
	if( -1 != m_lvObjects.SubItemHitTest(&lvhti) ) {
		CString strLayer;
		CRule_Layer	*pRule_Layer;
		int iNumItems;
		int iItem;

		strLayer = m_lvObjects.GetItemText(lvhti.iItem, 0);
		pRule_Layer = g_pMetaData->GetRule_Layer(strLayer);

		if( lvhti.iSubItem == 0 && (lvhti.flags & LVHT_ONITEMSTATEICON) ) {
			lvi.iItem = lvhti.iItem;
			lvi.iSubItem = 0;
			lvi.mask = LVIF_STATE;
			lvi.stateMask = LVIS_STATEIMAGEMASK;
			m_lvObjects.GetItem(&lvi);
			state = lvi.state & LVIS_STATEIMAGEMASK;
			if( state == INDEXTOSTATEIMAGEMASK(1) ) {
				pRule_Layer->ImportMode() = EDBS_IMPORTALWAYS;
				lvi.state = INDEXTOSTATEIMAGEMASK(2);
			}
			else {
				pRule_Layer->ImportMode() = EDBS_IMPORTNEVER;
				lvi.state = INDEXTOSTATEIMAGEMASK(1);
			}
			m_lvObjects.SetItem(&lvi);
		}
		else if( lvhti.iSubItem == 0 && (lvhti.flags & LVHT_ONITEMICON) ) {
/*
			lvi.iItem = lvhti.iItem;
			lvi.iSubItem = 0;
			lvi.mask = LVIF_IMAGE;
			m_lvObjects.GetItem(&lvi);
			if( 4 == lvi.iImage ) {
				pRule_Layer->ImportMode() = EDBS_IMPORTALWAYS;
				lvi.iImage = 5;
			}
			else {
				pRule_Layer->ImportMode() = EDBS_IMPORTNEVER;
				lvi.iImage = 4;
			}
			m_lvObjects.SetItem(&lvi);
*/
			iNumItems = m_lvObjects.GetItemCount();

			for( iItem = 0; iItem < iNumItems; iItem++ ) {
				lvi.mask = LVIF_STATE | LVIF_IMAGE;
				lvi.iItem = iItem;
				lvi.iSubItem = 0;
				lvi.stateMask = LVIS_SELECTED;
				m_lvObjects.GetItem(&lvi);
				
				if( lvi.state & LVIS_SELECTED ) {
					lvi.mask = LVIF_IMAGE;
					lvi.iItem = iItem;
					lvi.iSubItem = 0;
					strLayer = m_lvObjects.GetItemText(iItem, 0);
					pRule_Layer = g_pMetaData->GetRule_Layer(strLayer);
					if( 4 == lvi.iImage ) {
						pRule_Layer->ImportMode() = EDBS_IMPORTALWAYS;
						lvi.iImage = 5;
					}
					else {
						pRule_Layer->ImportMode() = EDBS_IMPORTNEVER;
						lvi.iImage = 4;
					}
					m_lvObjects.SetItem(&lvi);
				}
			}	
		}
		else if( lvhti.iSubItem == 1 && (lvhti.flags & LVHT_ONITEMICON) ) {
			LVITEM   lvi;

			lvi.iItem = lvhti.iItem;
			lvi.iSubItem = 1;
			lvi.mask = LVIF_IMAGE;
			m_lvObjects.GetItem(&lvi);
			if( lvi.iImage == 1 ) {
				pRule_Layer->Resolve(true);
				lvi.iImage = 2;
			}
			else {
				pRule_Layer->Resolve(false);
				lvi.iImage = 1;
			}
			m_lvObjects.SetItem(&lvi);
		}
		UpdateData(false);
	}
	*pResult = 0;
}

void CEDBS_CfgImpObj::OnClickBtnSelect() 
{
	int iNumItems;
	int iItem;
	CxString strButton;
	LVITEM   lvi;

	if( m_tBtnSelect ) {
		strButton.LoadString(IDS_CFGOBJSELNONE);
		m_tBtnSelect = false;
	}
	else {
		strButton.LoadString(IDS_CFGOBJSELALL);
		m_tBtnSelect = true;
	}
	SetDlgItemText( IDC_BTNSELECT, strButton );
	
	iNumItems = m_lvObjects.GetItemCount();

	for( iItem = 0; iItem < iNumItems; iItem++ ) {
		lvi.mask = LVIF_STATE;
		lvi.iItem = iItem;
		lvi.iSubItem = 0;
		lvi.state = LVIS_SELECTED;
		lvi.stateMask = LVIS_SELECTED;
		if( !m_tBtnSelect ) {	// stand vorher also aus "Alle Auswählen"
			lvi.state = LVIS_SELECTED;
		}
		else {
			lvi.state = 0;
		}
		m_lvObjects.SetItemState(iItem, &lvi);
	}	
}

