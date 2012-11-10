// dbfrmvw.cpp : implementation file
//

#include "bscriptp.hxx"
#include "bscript.h"

#include <iobjman.h>
#include <registrx.hxx>

#include "macrguid.h"

#include "iscrprop.h"

#include "projscr.h"
#include "strinfo.h"
#include "dummypar.h"
#include "conststr.h"
#include "fndrpld.h"
#include "toolbarx.h"
#include "runscorg.h"
#include "relscrpt.h"
#include "runerr.h"
#include "runebobs.h"
#include "DebCtrl.h"
#include "projscr.h"
#include "spltree.h"
#include "splitter.h"
#include "split.h"
#include "editctrl.h"
#include "dbfrmvw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TAB_GENERAL 0
#define	TAB_FILTER	1
#define	TAB_OBJFEAT 2

BOOL	LoadString(CString & str, int IDS);

/////////////////////////////////////////////////////////////////////////////
// CDebFormView

IMPLEMENT_DYNCREATE(CDebFormView, CFormView)

CDebFormView::CDebFormView()
	: CFormView(CDebFormView::IDD)
{
	//{{AFX_DATA_INIT(CDebFormView)
	//}}AFX_DATA_INIT
	m_iInitialTabItemsWidth = 0;
	m_iSelect = TAB_GENERAL;
}

CDebFormView::~CDebFormView()
{
}

void CDebFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX); 
	//{{AFX_DATA_MAP(CDebFormView)
	DDX_Control(pDX, IDC_TABPROJECT, m_tabProject);
//	DDX_Control(pDX, IDC_TREECAPTION, m_stTreeCaption);
	DDX_Control(pDX, IDC_TREE, m_treeRelMacros);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDebFormView, CFormView)
	//{{AFX_MSG_MAP(CDebFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABPROJECT, OnSelchangeTabproject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDebFormView diagnostics

#ifdef _DEBUG
void CDebFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDebFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDebFormView message handlers


int CDebFormView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}


void CDebFormView::OnSize(UINT nType, int cx, int cy) 
{	
	if (::IsWindow(m_tabProject.m_hWnd) && ::IsWindow(m_treeRelMacros.m_hWnd)) 
	{
	// TabsGröße setzen
		if (FAILED(SetTabsOnSize(cx-8*SIZE_XBORDER))) 
			return;

		m_tabProject.MoveWindow(4*SIZE_XBORDER, 4*SIZE_YBORDER, cx-8*SIZE_XBORDER, cy-8*SIZE_YBORDER);

	CRect rectTab, rectTabItem;

		m_tabProject.GetClientRect(&rectTab);
		m_tabProject.GetItemRect(TAB_GENERAL, &rectTabItem);

	// Version der ComCtrl überprüfen (neue Version Tabs unten)
	int iTabItemsHeight = rectTabItem.bottom-rectTabItem.top;

		if (iTabItemsHeight > (rectTabItem.top - rectTab.top))
			m_treeRelMacros.MoveWindow(rectTab.left + 6*SIZE_XBORDER, rectTab.top + iTabItemsHeight + 8*SIZE_YBORDER, rectTab.right - 5*SIZE_XBORDER, rectTab.bottom - iTabItemsHeight - 7*SIZE_YBORDER, true);
		else 
			m_treeRelMacros.MoveWindow(rectTab.left + 6*SIZE_XBORDER, rectTab.top + 6*SIZE_YBORDER, rectTab.right - 5*SIZE_XBORDER, rectTab.bottom - iTabItemsHeight - 7*SIZE_YBORDER, true);

	// Scrollbalken abschalten
		SetScrollSizes(m_nMapMode, CSize(cx, cy));
	}
	CFormView::OnSize(nType, cx, cy);
}

void CDebFormView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();	
	// Imageliste und Tabs erzeugen
	InitialTabs(); 
}

void CDebFormView::OnSelchangeTabproject(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int iSel = m_tabProject.GetCurSel();	
	if (iSel == -1) return;

	switch (iSel)
	{
	case TAB_GENERAL:
		::SendMessage(GetParent() -> GetSafeHwnd(), WM_COMMAND, ID_SELGENERALPROJECT, 0);
		break;

	case TAB_FILTER:
		::SendMessage(GetParent() -> GetSafeHwnd(), WM_COMMAND, ID_SELFILTERPROJECT, 0);
		break;

	case TAB_OBJFEAT:
		::SendMessage(GetParent() -> GetSafeHwnd(), WM_COMMAND, ID_SELOBJFEATPROJECT, 0);
		break;
	}
	// Merken, damit bei OnSize richtiger selektiert wird
	m_iSelect = iSel;

	*pResult = 0;
}

BOOL CDebFormView::Init (UINT uiManID)
{
	switch (uiManID)
	{
	case MANID_GENERAL:
		m_iSelect = TAB_GENERAL; 
		break;
	case MANID_FILTER:
		m_iSelect = TAB_FILTER; 
		break;
	case MANID_OBJFEAT:
		m_iSelect = TAB_OBJFEAT;
		break;
	default:
		return false;
	}
	// Selektion gleich setzen
	m_tabProject.SetCurSel(m_iSelect);
	m_tabProject.EnableWindow(true);
	return true;
}

UINT CDebFormView::GetManID()
{
	UINT uiManID = 0; 
	switch (m_iSelect)
	{
	case TAB_GENERAL:
		uiManID = MANID_GENERAL; 
		break;
	case TAB_FILTER:
		uiManID = MANID_FILTER; 
		break;
	case TAB_OBJFEAT:
		uiManID = MANID_OBJFEAT;
		break;
	default:
		return 0;
	}
	return uiManID;
}

BOOL CDebFormView::ResetIfOnClose (UINT & uiManID)
{
	uiManID = GetManID(); 
	m_tabProject.EnableWindow(false);
	return true;
}

HRESULT CDebFormView::InitialTabs() 
{
	if (!::IsWindow(m_tabProject.m_hWnd)) return S_FALSE;

	// Imageliste erzeugen und für Tab setzen 
	if (!m_ImageList.Create(IDR_TREEIMAGES, 16, 0, RGB(128, 0, 128))) return E_FAIL; 
	m_tabProject.SetImageList(&m_ImageList);

	TC_ITEM TabCtrlItem;
	CString strItemEntry; 
	
	TabCtrlItem.mask = TCIF_TEXT|TCIF_IMAGE; 	

	if (!::LoadString(strItemEntry, IDS_GENERALITEMENTRY)) return E_OUTOFMEMORY;
	TabCtrlItem.pszText = (LPSTR)(LPCSTR)strItemEntry;
	TabCtrlItem.iImage = IMAGE_GENERALKEY;

	if (-1 == m_tabProject.InsertItem(TAB_GENERAL, &TabCtrlItem)) return E_FAIL;

	if (!::LoadString(strItemEntry, IDS_FILTERITEMENTRY)) return E_OUTOFMEMORY;
	TabCtrlItem.pszText = (LPSTR)(LPCSTR)strItemEntry;
	TabCtrlItem.iImage = IMAGE_FILTERKEY;
	if (-1 == m_tabProject.InsertItem(TAB_FILTER, &TabCtrlItem)) return E_FAIL;

	if (!::LoadString(strItemEntry, IDS_OBJFEATITEMENTRY)) return E_OUTOFMEMORY;
	TabCtrlItem.pszText = (LPSTR)(LPCSTR)strItemEntry;
	TabCtrlItem.iImage = IMAGE_OBJECTFEATUREKEY;

	if (-1 == m_tabProject.InsertItem(TAB_OBJFEAT, &TabCtrlItem)) return E_FAIL;
	
	CRect Rect;
	if (!m_tabProject.GetItemRect(TAB_GENERAL, &Rect)) return E_FAIL;
	m_iInitialTabItemsWidth = 3*Rect.right;

	// Platz um einzelne Items
	m_tabProject.SetPadding(CSize(3,3));
	return S_OK;
}

HRESULT CDebFormView::SetTabsOnSize(int iViewWindowWidth) 
{
	if (!::IsWindow(m_tabProject.m_hWnd)) return S_FALSE;
	// Rect der einzelnen Items geben lassen

	if (!m_tabProject.DeleteAllItems()) return E_FAIL;

	TC_ITEM TabCtrlItem;

	if (iViewWindowWidth < m_iInitialTabItemsWidth)
	{// Items ohne Bildchen darstellen
		TabCtrlItem.mask = TCIF_IMAGE; 
		TabCtrlItem.iImage = IMAGE_GENERALKEY;
		if (-1 == m_tabProject.InsertItem(TAB_GENERAL, &TabCtrlItem)) return E_FAIL;

		TabCtrlItem.iImage = IMAGE_FILTERKEY;
		if (-1 == m_tabProject.InsertItem(TAB_FILTER, &TabCtrlItem)) return E_FAIL;

		TabCtrlItem.iImage = IMAGE_OBJECTFEATUREKEY;		
		if (-1 == m_tabProject.InsertItem(TAB_OBJFEAT, &TabCtrlItem)) return E_FAIL;

		m_tabProject.ModifyStyle(TCS_RIGHTJUSTIFY, TCS_FIXEDWIDTH);
		// Platz um einzelne Items
		m_tabProject.SetPadding(CSize(3,3));
		m_tabProject.SetItemSize(CSize(23,23));
	} 
	else
	{// Items mit Bildchen darstellen
		CString strItemEntry; 

		TabCtrlItem.mask = TCIF_TEXT|TCIF_IMAGE; 

		if (!::LoadString(strItemEntry, IDS_GENERALITEMENTRY)) return E_OUTOFMEMORY;
		TabCtrlItem.pszText = (LPSTR)(LPCSTR)strItemEntry;
		TabCtrlItem.iImage = IMAGE_GENERALKEY;
		if (-1 == m_tabProject.InsertItem(TAB_GENERAL, &TabCtrlItem)) return E_FAIL;

		if (!::LoadString(strItemEntry, IDS_FILTERITEMENTRY)) return E_OUTOFMEMORY;
		TabCtrlItem.pszText = (LPSTR)(LPCSTR)strItemEntry;
		TabCtrlItem.iImage = IMAGE_FILTERKEY;		
		if (-1 == m_tabProject.InsertItem(TAB_FILTER, &TabCtrlItem)) return E_FAIL;

		if (!::LoadString(strItemEntry, IDS_OBJFEATITEMENTRY)) return E_OUTOFMEMORY;
		TabCtrlItem.pszText = (LPSTR)(LPCSTR)strItemEntry;
		TabCtrlItem.iImage = IMAGE_OBJECTFEATUREKEY;
		if (-1 == m_tabProject.InsertItem(TAB_OBJFEAT, &TabCtrlItem)) return E_FAIL;

		m_tabProject.ModifyStyle(TCS_FIXEDWIDTH, TCS_RIGHTJUSTIFY);

		m_tabProject.SetPadding(CSize(3,3));
	}
	// Selektion rücksetzen
	m_tabProject.SetCurSel(m_iSelect);
	
	return S_OK;
}