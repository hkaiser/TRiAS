// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.09.2000 08:52:33
//
// @doc
// @module DeleteObjectPropertyDlg.cpp | Implementation of the <c CDeleteObjectPropertyDlg> class

#include "trias03p.hxx"
#include "trias03.h"

#include "Strings.h"
#include "DeleteObjectPropertyDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// externes
extern char g_pDLLName[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(EnumObjProps);

/////////////////////////////////////////////////////////////////////////////
// CDeleteObjectPropertyDlg

CDeleteObjectPropertyDlg* CDeleteObjectPropertyDlg::CreateInstance (ResID resID, LPCSTR pcCaption)
{
CDeleteObjectPropertyDlg *pCfgDlg = NULL;

// Dialog erzeugen
	TX_TRY(pCfgDlg = new CDeleteObjectPropertyDlg(resID, pcCaption));
	if (NULL == pCfgDlg || !pCfgDlg -> FInit()) {
		DELETE_OBJ(pCfgDlg);
		return NULL;
	}
	return pCfgDlg; 
}

CDeleteObjectPropertyDlg::CDeleteObjectPropertyDlg(ResID resID, LPCSTR pcCaption) :
	CPropertyPage(resID, pcCaption),
	m_ftDesc(this, IDC_OBJPROP_DESCRIPTION)
{
	m_dwFlags = 0;
	m_pObjProps = NULL;
}

CDeleteObjectPropertyDlg::~CDeleteObjectPropertyDlg()
{
	DELETE_OBJ(m_pObjProps);
}

BOOL CDeleteObjectPropertyDlg::FInit()
{
// Liste der Objekteigenschaften initialisieren
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

	TX_TRY(m_pObjProps = new CSelObjPropTree (this, IDC_OBJECTPROPERTIES, ObjProps, IncludeWritable, false, true, true));
	if (NULL == m_pObjProps) return FALSE;

	return TRUE;
}

BOOL CDeleteObjectPropertyDlg::AdjustSheetButtons()
{
// Knöpfe des Dialoges richten (Next, Previous, Finish)
DWORD dwBttns = 0;

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns = PSWIZB_BACK;			// nicht erste Seite

	if (!GetDisableNextPage()) {
		if (m_dwFlags & ADDPAGES_LASTPAGE) 
			dwBttns |= PSWIZB_FINISH;	// letzte Seite
		else 
			dwBttns |= PSWIZB_NEXT;		// nicht letzte Seite
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	SetSheetWizardButtons(dwBttns);
	return true;
}

BOOL CDeleteObjectPropertyDlg::GetDisableNextPage()
{
	if (0 == m_pObjProps -> CountSelectedItems())
		return TRUE;	// nichts selektierts
	return FALSE;
}

HRESULT CDeleteObjectPropertyDlg::DoUpdate()
{
	if (0 == m_pObjProps -> CountSelectedItems())
		return S_FALSE;		// nichts selektierts

	m_lstObjProps.clear();
	return m_pObjProps -> GetSelectedObjProps(m_lstObjProps);
}

HRESULT CDeleteObjectPropertyDlg::GetObjectProperty (IObjectProperty **ppIObjProp)
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

/////////////////////////////////////////////////////////////////////////////
// CDeleteObjectPropertyDlg message handlers

int CDeleteObjectPropertyDlg::OnSetActive(NotifyEvt e) 
{
	AdjustSheetButtons();
	return 0;
}

void CDeleteObjectPropertyDlg::OnSelChanged (NotifyEvt e)
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
	} else
		m_ftDesc.SetText(g_cbNil);

// Knöpfchen richten
	AdjustSheetButtons();
}

void CDeleteObjectPropertyDlg::WindowInit (Event e)
{
	if (!m_ftDesc.FInit())
		return;

	if (NULL == m_pObjProps || !m_pObjProps -> InitControl(m_lstObjProps))
		return;

	AdjustSheetButtons();
}

void CDeleteObjectPropertyDlg::OnCancel (NotifyEvt e)
{
}

int CDeleteObjectPropertyDlg::OnWizNext (NotifyEvt e)
{
	DoUpdate();
	return 0;
}

BOOL CDeleteObjectPropertyDlg::OnWizFinish (NotifyEvt e)
{
	DoUpdate();
	return FALSE;
}

void CDeleteObjectPropertyDlg::OnItemExpanded (NotifyEvt e)
{
	_ASSERTE(NULL != m_pObjProps);
	m_pObjProps -> OnItemExpanded(e);		// Bildchen richten
}
