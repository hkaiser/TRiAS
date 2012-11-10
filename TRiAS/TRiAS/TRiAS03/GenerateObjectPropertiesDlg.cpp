// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.10.2000 19:50:54 
//
// @doc
// @module GenerateObjectPropertiesDlg.cpp | Definition of the <c CGenerateObjectPropertiesDlg> class

#include "trias03p.hxx"
#include "trias03.h"

#include <eieruhr.hxx>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Strings.h"
#include "GenerateObjectPropertiesDlg.h"

///////////////////////////////////////////////////////////////////////////////
// globale variablen
extern TCHAR g_pDLLName[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ObjectProps);
DefineSmartInterface(EnumObjProps);
DefineSmartInterface(ConfigObjectProperty);

/////////////////////////////////////////////////////////////////////////////
// CGenerateObjectPropertiesSelectDlg

CGenerateObjectPropertiesSelectDlg* CGenerateObjectPropertiesSelectDlg::CreateInstance (
	CGenerateObjectProperties *pParent, LPCSTR pcCaption)
{
CGenerateObjectPropertiesSelectDlg *pCfgDlg = NULL;

	COM_TRY {
	// Dialog erzeugen
	ResourceFile RF (g_pDLLName);

		pCfgDlg = new CGenerateObjectPropertiesSelectDlg(pParent, ResID(IDD, &RF), pcCaption);
		if (NULL == pCfgDlg || !pCfgDlg -> FInit()) {
			DELETE_OBJ(pCfgDlg);
			return NULL;
		}

	} COM_CATCH_OP_RETURN(delete pCfgDlg, NULL);
	return pCfgDlg; 
}

CGenerateObjectPropertiesSelectDlg::CGenerateObjectPropertiesSelectDlg(
		CGenerateObjectProperties *pParent, ResID uiResID, LPCSTR pcCaption) :
	CPropertyPage(uiResID, pcCaption), m_pParent(pParent),
	m_ftDesc(this, IDC_OBJPROP_DESCRIPTION),
	m_pbConfig(this, IDC_CONFIG_PROP)
{
	m_dwFlags = 0;
	m_pObjProps = NULL;
	m_fChangedPropList = false;
}

CGenerateObjectPropertiesSelectDlg::~CGenerateObjectPropertiesSelectDlg()
{
	DELETE_OBJ(m_pObjProps);
}

BOOL CGenerateObjectPropertiesSelectDlg::FInit (void)
{
// Liste der Objekteigenschaften initialisieren
CEierUhr Wait (this);		// EierUhr anzeigen
WObjectProps ObjProps;
BOOL fMustReInit = DEX_GetObjectProps (ObjProps.ppi());

	if (ObjProps.IsValid()) {
	// evtl. alle ObjProps installieren
		if (fMustReInit) {
			ObjProps -> OnNewReferenceObject (-1L);	// alles bisherige löschen
			if (FAILED(ObjProps -> OnNewReferenceObject (0L))) 
				return FALSE;
			DEX_SetMustInitOPFs(FALSE);
		}
	}

	TX_TRY(m_pObjProps = new CSelObjPropTree (this, IDC_OBJECTPROPERTIES, ObjProps, IncludeAll, false, true, true));
	if (NULL == m_pObjProps) return FALSE;

	return TRUE;
}

void CGenerateObjectPropertiesSelectDlg::AdjustSheetButtons()
{
DWORD dwBttns = 0;

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns = PSWIZB_BACK;			// nicht erste Seite

	if (!GetDisableNextPage()) {
		if (m_dwFlags & ADDPAGES_LASTPAGE) 
			dwBttns |= PSWIZB_FINISH;	// letzte Seite
		else 
			dwBttns |= PSWIZB_NEXT;		// nicht letzte seite
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	SetSheetWizardButtons(dwBttns);
}

BOOL CGenerateObjectPropertiesSelectDlg::GetDisableNextPage()
{
	if (0 == m_pObjProps -> CountSelectedItems())
		return TRUE;	// nichts selektiert

	return FALSE;
}

HRESULT CGenerateObjectPropertiesSelectDlg::PrepareResult (void)
{
	if (0 == m_pObjProps -> CountSelectedItems())
		return S_FALSE;		// nichts selektiert

	m_lstObjProps.clear();
	return m_pObjProps -> GetSelectedObjProps(m_lstObjProps);
}

/////////////////////////////////////////////////////////////////////////////
// CGenerateObjectPropertiesSelectDlg message handlers

void CGenerateObjectPropertiesSelectDlg::WindowInit (Event e)
{
CEierUhr Wait (this);		// EierUhr anzeigen

	if (!m_ftDesc.FInit() || !m_pbConfig.FInit())
		return;
	m_pbConfig.Disable();	

	if (NULL == m_pObjProps || !m_pObjProps -> InitControl(m_lstObjProps))
		return;
	m_fChangedPropList = false;		// ab jetzt zählt es
	AdjustSheetButtons();
}

int CGenerateObjectPropertiesSelectDlg::OnWizNext (NotifyEvt)
{
	if (SUCCEEDED(PrepareResult()))		// Ergebnisse zwischenspeichern
		return (m_lstObjProps.size() > 1) ? 0 : IDD_GENERATEOBJECTPROPERTIES_OPTIONS;
	return -1;
}

// Finish wurde gedrückt 
int CGenerateObjectPropertiesSelectDlg::OnWizFinish (NotifyEvt)
{
	PrepareResult(); 					// Ergebnisse zwischenspeichern
	return 0;
}

int CGenerateObjectPropertiesSelectDlg::OnSetActive (NotifyEvt e)
{
	AdjustSheetButtons();
	return 0;
}

void CGenerateObjectPropertiesSelectDlg::OnItemExpanded (NotifyEvt e)
{
	_ASSERTE(NULL != m_pObjProps);
	m_pObjProps -> OnItemExpanded(e);		// Bildchen richten
}

LRESULT CGenerateObjectPropertiesSelectDlg::Dispatch (Event e)
{
	if (WM_NOTIFY == e.Msg()) {
		if (OnNotify ((NotifyEvt &)e))
			return true;
	}
	return CPropertyPage::Dispatch(e);
}

BOOL CGenerateObjectPropertiesSelectDlg::OnNotify (NotifyEvt e)
{
NMHDR *pNMHDR = e.GetNotifyInfo();

	switch (pNMHDR -> code) {
	case TVN_CHECKSTATECHANGED:
		m_fChangedPropList = true;
		AdjustSheetButtons();
		return true;
	}
	return false;
}

HRESULT CGenerateObjectPropertiesSelectDlg::GetObjectProperty (IObjectProperty **ppIObjProp)
{
// Beschreibungstext setzen
os_string strObjProp(g_cbNil), strObjPropFull(g_cbNil);

	if (S_OK == m_pObjProps -> GetSelectedObjProp(strObjProp, &strObjPropFull)) {
	// derzeit selektierte Objekteigenschaft näher beschreiben
	WObjectProps Props (GetObjectProps());
	WEnumObjProps Enum;
	WObjectProperty ObjProp;

		if (SUCCEEDED(Props -> EnumObjectProps(Enum.ppi())) &&
			SUCCEEDED(Enum -> FindByName(strObjPropFull.c_str(), ppIObjProp)))
		{
			return S_OK;
		}
	}
	return S_FALSE;
}

void CGenerateObjectPropertiesSelectDlg::OnSelChanged (NotifyEvt e)
{
// Messagereflection
	_ASSERTE(NULL != m_pObjProps);

NMTREEVIEW *pnmtv = (NMTREEVIEW *)e.GetNotifyInfo();

	if ((TVC_BYMOUSE|TVC_BYKEYBOARD) & pnmtv -> action)		// verhindern, daß erstes Element ggf. gehakt wird
		m_pObjProps -> OnSelChanged(e);

// Beschreibungstext setzen
WObjectProperty ObjProp;

	if (S_OK == GetObjectProperty(ObjProp.ppi())) {
	// derzeit selektierte Objekteigenschaft näher beschreiben
	char cbBuffer[_MAX_PATH];
	
		if (SUCCEEDED(ObjProp -> HelpInfo(cbBuffer, sizeof(cbBuffer), NULL, NULL)))
			m_ftDesc.SetText(cbBuffer);

	DWORD dwFlags = 0;

		if (SUCCEEDED(ObjProp -> GetPropInfo(NULL, 0, &dwFlags)) && PROPCAPS_INTERACTIVE_INIT & dwFlags)
			m_pbConfig.Enable();
		else
			m_pbConfig.Disable();

	} else {
		m_ftDesc.SetText(g_cbNil);
		m_pbConfig.Disable();
	}

// Knöpfchen richten
	AdjustSheetButtons();
}

void CGenerateObjectPropertiesSelectDlg::ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDC_CONFIG_PROP:
		{
		// ObjProp konfigurieren
		WObjectProperty ObjProp;
		HRESULT hr = S_OK;

			if (S_OK == GetObjectProperty(ObjProp.ppi())) {
			WConfigObjectProperty Cfg;

				if (SUCCEEDED(ObjProp -> QueryInterface (Cfg.ppi())))
					hr = Cfg -> ConfigObjectProperty (::GetParent(Handle(API_WINDOW_HWND)));		// liefert Sheet
			}

			if (S_OK == hr) {	// cancel liefert S_FALSE
			HTREEITEM hItem = m_pObjProps->GetSelectedItem();

				if (NULL != hItem) {
				// nach configure ist Item selektiert
					m_pObjProps->SetCheckState(hItem, TV_CHECK_ON);
				}
			}
		}
		break;

	default:
		break;
	}
}
