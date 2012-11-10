// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 18.12.2002 11:47:29 
//
// @doc
// @module ManageConnectionFilters.cpp | Definition of the <c CManageConnectionFilters> class

#include "fakemfcp.hxx"

#include <Com/Thunk.h>

#include "fakemfc.h"
#include "Strings.h"

#include "fakemfc.hxx"
#include "MainFrm.h"
#include "ManageConnectionFilters.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Listview hat nur eine Spalte
#define NAME_COLUMN			0

#define IMG_CONNECTFILTER	0

///////////////////////////////////////////////////////////////////////////////
// diesen Dialog anzeiegn
void CMainFrame::OnManageConnectFilters()
{
CTRiASView *pView = (CTRiASView *)GetActiveView();

	ASSERT_KINDOF(CTRiASView, pView);

CManageConnectionFilters Dlg (pView);

	Dlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CManageConnectionFilters dialog

CManageConnectionFilters::CManageConnectionFilters(CWnd* pParent /*=NULL*/)
	: CDialog(CManageConnectionFilters::IDD, pParent)
{
	//{{AFX_DATA_INIT(CManageConnectionFilters)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CManageConnectionFilters::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManageConnectionFilters)
	DDX_Control(pDX, IDC_CONNECTFILTERS, m_lvConnectFilters);
	//}}AFX_DATA_MAP
}

void CManageConnectionFilters::AdjustButtons()
{
// wenn nichts selektiert ist, dann Löschen und Properties grau
BOOL fHasSelection = (0 == m_lvConnectFilters.GetSelectedCount()) ? FALSE : TRUE;
	
	GetDlgItem(IDC_DELETE) -> EnableWindow(fHasSelection);
	GetDlgItem(IDC_PROPERTIES) -> EnableWindow(fHasSelection);

	if (0 == m_lvConnectFilters.GetItemCount())
		((CButton *)GetDlgItem(IDC_SHOWCONNECTFILTERS)) -> SetCheck(FALSE);

	GetDlgItem(IDC_SHOWCONNECTFILTERS) -> EnableWindow(
		m_lvConnectFilters.GetItemCount() > 0 ? TRUE : FALSE);
}

BEGIN_MESSAGE_MAP(CManageConnectionFilters, CDialog)
	//{{AFX_MSG_MAP(CManageConnectionFilters)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_CONNECTFILTERS, OnItemchangedConnectfilters)
	ON_BN_CLICKED(IDC_NEW, OnNew)
	ON_BN_CLICKED(IDC_SHOWCONNECTFILTERS, OnShowconnectfilters)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_PROPERTIES, OnProperties)
	ON_NOTIFY(NM_DBLCLK, IDC_CONNECTFILTERS, OnDblclkConnectfilters)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManageConnectionFilters message handlers

BOOL CManageConnectionFilters::EnumConnectionFilters(char *pName, BOOL, void *pData)
{
LV_ITEM lvi;

	memset (&lvi, 0, sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT|LVIF_IMAGE;
	lvi.iItem = m_lvConnectFilters.GetItemCount();
	lvi.iSubItem = NAME_COLUMN;
	lvi.pszText = pName;
	lvi.iImage = IMG_CONNECTFILTER;
	m_lvConnectFilters.InsertItem (&lvi);

	return TRUE;
}

BOOL CManageConnectionFilters::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_lvConnectFilters.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP);

CBitmap bmpIcons;
CBitmap bmpMask;

	if (!bmpIcons.LoadBitmap(IDB_CONNECTFILTER_DLG) || 
		!bmpMask.LoadBitmap(IDB_CONNECTFILTER_DLG_MASK)) 
	{
		TRACE0("Could not load bitmaps for CManageConnectionFilters\r\n");
		return FALSE;
	} 
	else {
		if (!m_ilImages.Create(16, 16, ILC_COLOR|ILC_MASK, 1, 1) ||
			-1 == m_ilImages.Add(&bmpIcons, &bmpMask)) 
		{
			TRACE0("Could not create imagelist for CManageConnectionFilters\r\n");
			return FALSE;
		} 
		else 
			m_lvConnectFilters.SetImageList(&m_ilImages, LVSIL_SMALL);
	}

CString strHead;

	VERIFY(strHead.LoadString(IDS_CONNECTFILTERNAME));
	VERIFY(-1 != m_lvConnectFilters.InsertColumn (NAME_COLUMN, strHead, 
		LVCFMT_LEFT, -1, NAME_COLUMN));

// existierende Filternamen in ListView füllen	
CStdThunkImpl<CManageConnectionFilters, ENUMNOKEYPROC> 
	Thunk(this, &CManageConnectionFilters::EnumConnectionFilters);
ENUMNOKEY ENK;

	ENK.eFcn = Thunk.GetThunk();
	ENK.ePtr = NULL;
	DEX_EnumConnectionFilters(ENK);

	m_lvConnectFilters.SetColumnWidth (NAME_COLUMN, LVSCW_AUTOSIZE_USEHEADER);

BOOL fShownFilters = FALSE;

	DEX_ConnectionFiltersShown(fShownFilters);
	((CButton *)GetDlgItem(IDC_SHOWCONNECTFILTERS)) -> SetCheck(fShownFilters);

	AdjustButtons();
	CenterWindow(GetParent());
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CManageConnectionFilters::OnItemchangedConnectfilters(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	AdjustButtons();	
	*pResult = 0;
}

void CManageConnectionFilters::OnNew() 
{
CREATECONNECTIONFILTER CCF;
char cbBuffer[_MAX_PATH];

	cbBuffer[0] = '\0';

	INITSTRUCT(CCF, CREATECONNECTIONFILTER);
	CCF.hWndParent = GetSafeHwnd();
	CCF.iMode = CF_Rectangle_OverlappedObjects;
	CCF.pName = cbBuffer;
	CCF.iLen = sizeof(cbBuffer);
	CCF.fApplySettings = true;
	CCF.fShowApplyAllConnections = true;
	DEX_ShowCreateConnectionFilterDlg(CCF);

	if (IDOK == CCF.iRetVal) {
	// neu zur Liste hinzufügen und selektieren
	LV_ITEM lvi;

		memset (&lvi, 0, sizeof(LV_ITEM));
		lvi.mask = LVIF_TEXT|LVIF_IMAGE|LVIF_STATE;
		lvi.iItem = m_lvConnectFilters.GetItemCount();
		lvi.iSubItem = NAME_COLUMN;
		lvi.pszText = CCF.pName;
		lvi.iImage = IMG_CONNECTFILTER;
		lvi.state = LVIS_SELECTED;
		lvi.stateMask = LVIS_SELECTED;
		m_lvConnectFilters.InsertItem (&lvi);
		AdjustButtons();
	}
}

void CManageConnectionFilters::OnShowconnectfilters() 
{
BOOL fShow = ((CButton *)GetDlgItem(IDC_SHOWCONNECTFILTERS)) -> GetCheck();

	DEX_ShowConnectionFilters(fShow);
	DEX_RePaint();
}

namespace {
	typedef struct tagENUMDETACHDATA {
		char const *pcFilterName;
		BOOL fDetachedOne;
	} ENUMDETACHDATA;
}

BOOL CManageConnectionFilters::EnumConnectionsForDetach(long hPr, BOOL, void *pData)
{
char cbDataSourceName[_MAX_PATH];

	if (!DEX_GetDataSourceShortName(reinterpret_cast<HPROJECT>(hPr), cbDataSourceName))
		return FALSE;

ENUMDETACHDATA *pEDD = reinterpret_cast<ENUMDETACHDATA *>(pData);
GETATTACHEDCONNECTIONFILTER GACF;
char cbBuffer[_MAX_PATH];

	INITSTRUCT(GACF, GETATTACHEDCONNECTIONFILTER);
	GACF.pcConnName = cbDataSourceName;
	GACF.pName = cbBuffer;
	GACF.iLen = sizeof(cbBuffer);

ATTACHCONNECTIONFILTER ACF;

	INITSTRUCT(ACF, ATTACHCONNECTIONFILTER);
	ACF.pcConnName = cbDataSourceName;
	ACF.pcName = pEDD->pcFilterName;

// allen das Filter rücksetzen setzen
	if (SUCCEEDED(DEX_GetAttachedConnectionFilter(GACF)) && 
		!strcmp(pEDD->pcFilterName, GACF.pName)) 
	{
		if (SUCCEEDED(DEX_DetachConnectionFilter(ACF)))	// bestehenden Filter herauslösen
			pEDD->fDetachedOne = TRUE;
	}
	return TRUE;
}

void CManageConnectionFilters::OnDelete() 
{
// alle Connections durchgehen, und alle die abklemmen, die diesen Filter haben
int iIndex = m_lvConnectFilters.GetNextItem(-1, LVNI_SELECTED);

	_ASSERTE(-1 != iIndex);

CString strFilterName = m_lvConnectFilters.GetItemText(iIndex, NAME_COLUMN);
ENUMNOKEYLONG ENK;
CStdThunkImpl<CManageConnectionFilters, ENUMNOKEYLONGPROC> 
	Thunk(this, &CManageConnectionFilters::EnumConnectionsForDetach);
ENUMDETACHDATA EDD;

	EDD.pcFilterName = strFilterName;
	EDD.fDetachedOne = FALSE;
	ENK.eFcn = Thunk.GetThunk();
	ENK.ePtr = &EDD;
	
	if (DEX_EnumDataSourceHandles(ENK)) {
	// jetzt ConnectFilter löschen
	CONNECTIONFILTER CF;

		INITSTRUCT(CF, CONNECTIONFILTER);
		CF.pcName = strFilterName;
		CF.iMode = CF_Unknown;
		if (S_OK == DEX_DeleteConnectionFilter(CF)) {
		BOOL fShownFilters = FALSE;

			DEX_ConnectionFiltersShown(fShownFilters);
			if (EDD.fDetachedOne) {
			// alles neu einlesen
				DEX_RemoveAllORWnds();
				DEXN_ReReadIdents();
				DEXN_ReReadContainer();
				DEXN_ReScale();
				if (!DEX_RebuildSight())
					DEX_PostRebuildSight();
			}
			else if (fShownFilters) {
			// ansonsten nur neu zeichnen
				DEX_RePaint();
			}

		// Item aus der Liste rausnehemen
			m_lvConnectFilters.DeleteItem(iIndex);
			AdjustButtons();
		}
	}
}

void CManageConnectionFilters::OnProperties() 
{
int iIndex = m_lvConnectFilters.GetNextItem(-1, LVNI_SELECTED);

	_ASSERTE(-1 != iIndex);

CString strFilterName = m_lvConnectFilters.GetItemText(iIndex, NAME_COLUMN);
CONNECTIONFILTER CF;

	INITSTRUCT(CF, CONNECTIONFILTER);
	CF.pcName = strFilterName;
	DEX_GetConnectionFilter(CF);
	if (NULL != CF.pIGeometry)
		CF.pIGeometry -> Release();

CREATECONNECTIONFILTER CCF;

	INITSTRUCT(CCF, CREATECONNECTIONFILTER);
	CCF.hWndParent = GetSafeHwnd();
	CCF.iMode = CF.iMode;
	CCF.pName = (char *)(char const *)strFilterName;
	CCF.iLen = strFilterName.GetLength();
	CCF.fApplySettings = true;
	CCF.fShowApplyAllConnections = true;
	CCF.fShowPropertiesOnly = true;
	DEX_ShowCreateConnectionFilterDlg(CCF);
}

void CManageConnectionFilters::OnDblclkConnectfilters(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnProperties();
	*pResult = 0;
}
