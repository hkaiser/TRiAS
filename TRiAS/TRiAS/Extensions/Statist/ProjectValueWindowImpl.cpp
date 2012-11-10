// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 28.08.2001 23:03:17 
//
// @doc
// @module ProjectValueWindowImpl.cpp | Definition of the <c CProjectValueWindowImpl> class

#include "StdAfx.h"

#include <SidManageTabs.h>
#include <Com/ComBool.h>
#include <Atl/Ciid.h>

#include <DllBindx.hxx>

#include "Statist.h"
#include "StatistApp.h"

#if defined(_USE_PROJECTVALUES)

#include "ProjectValuesCallback.h"
#include "ProjectValueWindowImpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// gecachete GUIDs der StatValues
CProjectValueWindowImpl::CEnumGuids CProjectValueWindowImpl::s_StatValueContGUIDs;

///////////////////////////////////////////////////////////////////////////////
// StatFuncConts Guids in cache speichern
HRESULT CProjectValueWindowImpl::
CEnumGuids::InitGuids (REFGUID rGuid, bool fForce)
{
	if (!m_fIsInitialized || fForce) {
		Clear();					// alles bisherige vergessen
		m_fIsInitialized = false;
		
	// neu füllen
		COM_TRY {
		WEnumGUID EnumGuids;		// Enumerator der StatistValueContainer Objekte
		WCatInformation CatInfo (CLSID_CatSimpleCache);	// throws hr
		GUID guid, guidImpl[1]; 

			guidImpl[0] = rGuid;
			THROW_FAILED_HRESULT(CatInfo -> EnumClassesOfCategories (1, guidImpl, 0, NULL, EnumGuids.ppi()));

		// alle Guids umkopieren
			for (EnumGuids -> Reset(); S_OK == EnumGuids -> Next (1, &guid, NULL); /**/)
				THROW_FAILED_HRESULT(AddItem (guid));

		} COM_CATCH;
		m_fIsInitialized = true;
	} 
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Daten, die an den ComboBoxItems hängen

// Control anzeigen und dazu ggf. neu erzeugen
HRESULT CProjectValueWindowImpl::
CProjectCategory::ShowControl(HWND hWndParent, CRect rcPos)
{
	_ASSERTE(NULL == ::GetDlgItem(hWndParent, IDC_VALUES));

	if (NULL == m_hWnd) {
		m_hWnd = ::CreateWindow(
			CAxWindow::GetWndClassName(),	// Style
			os_string(m_Guid).c_str(),		// Name == Guid
			WS_CHILD|WS_TABSTOP|WS_GROUP|DS_CONTROL,
			rcPos.left, rcPos.top, rcPos.Width(), rcPos.Height(),
			hWndParent, (HMENU)IDC_VALUES,
			_Module.GetModuleInstance(),
			NULL);

		_ASSERTE(NULL != m_hWnd);
	}
	else {
	// set new ChildId
	UINT uiOrgId = (UINT)::SetWindowLong(m_hWnd, GWL_ID, IDC_VALUES);

		_ASSERTE(m_uiOrgId == uiOrgId);	
	}

WUnknown OleObj;

	RETURN_FAILED_HRESULT(AtlAxGetControl(m_hWnd, OleObj.ppi()));
	RETURN_FAILED_HRESULT(WOleObject(OleObj) -> DoVerb(OLEIVERB_SHOW, NULL, NULL, 0, m_hWnd, &rcPos));
	::ShowWindow(m_hWnd, SW_SHOWNOACTIVATE);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// derzeit angezeigtes Control ausblenden
HRESULT CProjectValueWindowImpl::
CProjectCategory::HideControl()
{
	if (NULL != m_hWnd) {
		::SetWindowLong(m_hWnd, GWL_ID, m_uiOrgId);

	WUnknown OleObj;

		RETURN_FAILED_HRESULT(AtlAxGetControl(m_hWnd, OleObj.ppi()));
		RETURN_FAILED_HRESULT(WOleObject(OleObj) -> DoVerb(OLEIVERB_HIDE, NULL, NULL, 0, m_hWnd, NULL));
        ::ShowWindow(m_hWnd, SW_HIDE);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Verwalten des Fensters im Dockingbereich
/*static*/
HRESULT CProjectValueWindowImpl::RegisterTabWindow(CStatist *pXtsn)
{
	_ASSERTE(NULL != pXtsn);
	COM_TRY {
	WTriasXtensionSite Site;
	WServiceProvider SP;
	WManageTabWindows Tabs;

		if (SUCCEEDED(pXtsn -> GetXtensionSite(Site.ppi())) &&
			SUCCEEDED(Site -> QueryInterface(SP.ppi())) &&
			SUCCEEDED(SP -> QueryService(SID_ManageProjectTabs, __uuidof(IManageTabWindows), Tabs.ppv()))) 
		{
		CComObject<CProjectValuesCallback> *pValuesCB = NULL;

			THROW_FAILED_HRESULT(CComObject<CProjectValuesCallback>::CreateInstance(&pValuesCB));

		WUnknown Unk (pValuesCB -> GetUnknown());		// pending AddRef
		CComBSTR bstrValues;
		
			bstrValues.LoadString(IDS_PROJECTVALUES);
			pValuesCB -> SetCmdTarget (pXtsn);
			THROW_FAILED_HRESULT(Tabs -> AddTabWindowDelayed(bstrValues, pValuesCB));
		}
	} COM_CATCH;
	return S_OK;
}

/*static*/
CProjectValueWindowImpl *CProjectValueWindowImpl::CreateInstance(CStatist *pXtsn) 
{
CProjectValueWindowImpl *pClient = NULL;

	_ASSERTE(NULL != pXtsn);
	COM_TRY {
	// ProjectValueFenster erzeugen
	CWaitCursor Wait;

	WTriasXtensionSite Site;
	WServiceProvider SP;
	WManageTabWindows Tabs;

		if (SUCCEEDED(pXtsn -> GetXtensionSite(Site.ppi())) &&
			SUCCEEDED(Site -> QueryInterface(SP.ppi())) &&
			SUCCEEDED(SP -> QueryService(SID_ManageProjectTabs, __uuidof(IManageTabWindows), Tabs.ppv()))) 
		{
		// Anzeige erfolgt im DockingTab
		INT_PTR hHandle = NULL;
		CComBSTR bstrValues;
		
			bstrValues.LoadString(IDS_PROJECTVALUES);
			pClient = new CProjectValueWindowImpl();

		INT_PTR hParent = NULL;

			THROW_FAILED_HRESULT(Tabs -> get_ParentWindow(&hParent));

		HWND hWnd = pClient -> Create(reinterpret_cast<HWND>(hParent));

			_ASSERTE(NULL != hWnd);
			THROW_FAILED_HRESULT(Tabs -> AddTabWindow(reinterpret_cast<INT_PTR>(hWnd), bstrValues, pClient -> GetIcon(), &hHandle));
			_ASSERTE(reinterpret_cast<HWND>(hHandle) == HWND(*pClient));

			THROW_FAILED_HRESULT(Tabs -> ActivateTabWindow(hHandle));

		// ggf. Tabfenster anzeigen
		CComBool fVisible;

			THROW_FAILED_HRESULT(Tabs -> get_Visible(&fVisible));
			if (!fVisible)
				THROW_FAILED_HRESULT(Tabs -> put_Visible(VARIANT_TRUE));
		}
	} COM_CATCH_RETURN(NULL);
	return pClient;
}

bool CProjectValueWindowImpl::ReShow(CStatist *pXtsn)
{
	COM_TRY {
	// Projektfenster wieder anzeigen
	CWaitCursor Wait;

	// ProjektStatistics muß im DockingFenster angezeigt sein
	WTriasXtensionSite Site;
	WServiceProvider SP;
	WManageTabWindows Tabs;

		THROW_FAILED_HRESULT(pXtsn -> GetXtensionSite(Site.ppi()));
		THROW_FAILED_HRESULT(Site -> QueryInterface(SP.ppi()));
		THROW_FAILED_HRESULT(SP -> QueryService(SID_ManageProjectTabs, __uuidof(IManageTabWindows), Tabs.ppv()));

	INT_PTR hHandle = NULL;
	CComBSTR bstrValues;
	
		bstrValues.LoadString(IDS_PROJECTVALUES);
		THROW_FAILED_HRESULT(Tabs -> FindTabWindow(bstrValues, &hHandle));
		THROW_FAILED_HRESULT(Tabs -> ActivateTabWindow(hHandle));

	// ggf. Tabfenster anzeigen
#if defined(_DEBUG)
	CComBool fVisible;

		THROW_FAILED_HRESULT(Tabs -> get_Visible(&fVisible));
		_ASSERTE(!fVisible);
#endif // defined(_DEBUG)
		THROW_FAILED_HRESULT(Tabs -> put_Visible(VARIANT_TRUE));

	} COM_CATCH_RETURN(false);
	return true;
}

void CProjectValueWindowImpl::DeleteInstance(CStatist *pXtsn, CProjectValueWindowImpl *& pValues)
{
	COM_TRY {
	// ProjektStatistics muß im DockingFenster angezeigt sein
	WTriasXtensionSite Site;
	WServiceProvider SP;
	WManageTabWindows Tabs;

		THROW_FAILED_HRESULT(pXtsn -> GetXtensionSite(Site.ppi()));
		THROW_FAILED_HRESULT(Site -> QueryInterface(SP.ppi()));
		THROW_FAILED_HRESULT(SP -> QueryService(SID_ManageProjectTabs, __uuidof(IManageTabWindows), Tabs.ppv()));

		THROW_FAILED_HRESULT(Tabs -> DeleteTabWindow(reinterpret_cast<INT_PTR>(HWND(*pValues))));

	// Fenster und Objekt zerlegen
		pValues -> DestroyWindow();
		DELETE_OBJ(pValues);

	// ggf. TabFenster ausblenden (wenns die letzte TabLasche war)
	int iCount = 0;

		THROW_FAILED_HRESULT(Tabs -> get_Count(&iCount));
		if (0 == iCount) {
		CComBool fVisible;

			THROW_FAILED_HRESULT(Tabs -> get_Visible(&fVisible));
			if (fVisible) 
				THROW_FAILED_HRESULT(Tabs -> put_Visible(VARIANT_FALSE));
		}
	} COM_CATCH_NORETURN;
}

bool CProjectValueWindowImpl::EnsureIcon()
{
	if (NULL == m_hIcon) {
		m_hIcon = AtlLoadIcon(IDI_STATISTICS);
		_ASSERTE(NULL != m_hIcon);
	}
	return (NULL != m_hIcon) ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
// 
typedef list<CProjectValueWindowImpl::CProjectCategory *> CValueConts;

LRESULT CProjectValueWindowImpl::OnInitDialog(HWND /*hWnd*/, LPARAM /*lParam*/)
{
// Imagelist laden und im Tree setzen
CBitmap bmpIcons;
CBitmap bmpMask;

	if (!bmpIcons.LoadBitmap(IDB_STATVALUES) || !bmpMask.LoadBitmap(IDB_STATVALUES_MASK)) {
		ATLTRACE("Could not load bitmaps for CProjectValuesView\r\n");
		return false;
	} 
	else if (!m_ValueContBmps.Create(16, 16, ILC_COLOR|ILC_MASK, 20, 0) ||
			-1 == m_ValueContBmps.Add(bmpIcons, bmpMask)) 
	{
		ATLTRACE("Could not create imagelist for CProjectValuesView\r\n");
		return false;
	} 
	_ASSERTE(NULL != HIMAGELIST(m_ValueContBmps));

	m_ValueConts.SubclassWindow(GetDlgItem(IDC_CATEGORIES));

// ComboBox mit allen existierenden ContainerControls bestücken
CValueConts ValueConts;
CIID guid;
int iCnt = 1;

	s_StatValueContGUIDs.InitGuids(CATID_TRiASStatistValuesContainer);		// sicher initialisieren
	for (s_StatValueContGUIDs.Reset(); S_OK == s_StatValueContGUIDs.Next(1, &guid, NULL); ++iCnt)
	{
	char cbName[_MAX_PATH];
	DWORD dwLen = sizeof(cbName);
	CRegKey regCtrl;
	
		if (ERROR_SUCCESS != regCtrl.Open(HKEY_CLASSES_ROOT, "CLSID") ||
			ERROR_SUCCESS != regCtrl.Open(regCtrl, os_string(guid).c_str()))
		{
			_ASSERTE(FALSE);
			continue;
		}

	// Namen des Containers aus Regsitry bestimmen
		if (ERROR_SUCCESS != regCtrl.QueryValue(cbName, NULL, &dwLen))
		{
			_ASSERTE(FALSE);
			continue;
		}

	// zu verwendende Bitmap aus Registry bestimmen
	char cbPath[_MAX_PATH];
	UINT uiBmp = PROJECTVALUE_DEFAULT;

		dwLen = sizeof(cbPath);
		if (ERROR_SUCCESS == regCtrl.Open(regCtrl, "ToolboxBitmap32") &&
			ERROR_SUCCESS == regCtrl.QueryValue(cbPath, NULL, &dwLen))
		{
		os_string strPath (cbPath);
		size_t iPos = strPath.find_last_of(",;");

			if (os_npos != iPos)	// Position in ResourceFile
				uiBmp = (UINT)strtoul (strPath.substr(iPos+1).c_str(), NULL, 10);

		// Bitmap zur ImageList hinzufügen
			{
			CDllBindX dll (strPath.substr(0, iPos).c_str(), IsWinNT() ? LOAD_LIBRARY_AS_DATAFILE : 0);

				if (NULL != dll.hLib()) {
				HBITMAP hBitmap = ::LoadBitmap (dll.hLib(), MAKEINTRESOURCE(uiBmp));

					if (NULL != hBitmap) {
					int iIndex = m_ValueContBmps.Add(hBitmap, RGB(255, 255, 255));

						if (0 != iIndex)
							uiBmp = (UINT)iIndex;
					}
				}
			}
		}

	// diesem Eintrag erstmal zwischenspeichern
		ATLTRY(ValueConts.push_back(new CProjectCategory(guid, cbName, uiBmp, IDC_VALUES + iCnt)));
	}

// die gefundenen Container in ComboBox eintragen
	m_ValueConts.SetImageList(m_ValueContBmps);		// Imagelist an Combobox dranhängen

	for (CValueConts::iterator it = ValueConts.begin(); it != ValueConts.end(); ++it) {
	COMBOBOXEXITEM item;

		memset (&item, 0, sizeof(COMBOBOXEXITEM));
		item.mask = CBEIF_IMAGE|CBEIF_SELECTEDIMAGE|CBEIF_TEXT|CBEIF_LPARAM;
		item.iImage = (*it) -> GetImageId();
		item.iSelectedImage = (*it) -> GetSelectedImageId();
		item.pszText = const_cast<char *>((*it) -> GetText());
		item.lParam = reinterpret_cast<DWORD_PTR>(*it);

		m_ValueConts.InsertItem(&item);
	}

// ggf. nichts installiert
	if (0 == m_ValueConts.GetCount()) {
		m_ValueConts.EnableWindow(FALSE);
		::ShowWindow(GetDlgItem(IDC_NOMODULES), SW_SHOW);
	}
	else {
		m_ValueConts.SetCurSel(0);		// das erste Item aktivieren
		PostMessage (WM_COMMAND, MAKELONG(IDC_CATEGORIES, CBN_SELCHANGE), LPARAM(HWND(m_ValueConts)));
	}

// AutoResize initialisieren
	DlgResize_Init(false, true, 0);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Ein Item wurde gelöscht
LRESULT CProjectValueWindowImpl::OnItemDeleted(LPNMHDR pNmHdr)
{
NMCOMBOBOXEX *pCBEx = (NMCOMBOBOXEX *)pNmHdr;
CProjectCategory *pData = reinterpret_cast<CProjectCategory *>(m_ValueConts.GetItemData(pCBEx -> ceItem.iItem));

	m_ValueConts.SetItemData(pCBEx->ceItem.iItem, NULL);
	
	DELETE_OBJ(pData);		// angehängte Daten freigeben
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Ein neues Item wurde ausgewählt
void CProjectValueWindowImpl::OnItemSelected(UINT uiCode, int iItemId, HWND hCtrl)
{
	_ASSERTE(uiCode == CBN_SELCHANGE && iItemId == IDC_CATEGORIES);

int iNewItem = m_ValueConts.GetCurSel();

	if (CB_ERR != iNewItem && iNewItem != m_iCurrItem) {
	// neues Item ausgewählt
	CProjectCategory *pNewData = reinterpret_cast<CProjectCategory *>(m_ValueConts.GetItemData(iNewItem));
	CProjectCategory *pOldData = NULL;
	CRect rcPos;
		
		if (CB_ERR != m_iCurrItem) 
			pOldData = reinterpret_cast<CProjectCategory *>(m_ValueConts.GetItemData(m_iCurrItem));
		
	// neues Control einblenden, altes ausblenden
		::GetWindowRect(GetDlgItem(IDC_VALUES), &rcPos);
		ScreenToClient(&rcPos);

		if (NULL == pOldData) {
		// das erste mal (noch kein Control angezeigt)
			::SetWindowLong(GetDlgItem(IDC_VALUES), GWL_ID, IDC_VALUESFRAME);
			::ShowWindow(GetDlgItem(IDC_NOMODULES), SW_HIDE);
			::ShowWindow(GetDlgItem(IDC_VALUESFRAME), SW_HIDE);
		} 
		else {
		// das derzeit aktive Control ausblenden
			pOldData -> HideControl();
		}

		if (NULL == pNewData) {
			m_ValueConts.EnableWindow(FALSE);

		HWND hFrame = GetDlgItem(IDC_VALUESFRAME);

			if (NULL != hFrame && ::IsWindow(hFrame))
				::SetWindowLong(hFrame, GWL_ID, IDC_VALUES);
			::ShowWindow(GetDlgItem(IDC_NOMODULES), SW_SHOW);
		}
		else 
			pNewData -> ShowControl(m_hWnd, rcPos);

		m_iCurrItem = iNewItem;
	}
}

#endif // defined(_USE_PROJECTVALUES)

