// Definitionen: Dialog zu PropertyAction für Operationen von GeoObjekten mit Bezugsobjekt(en)
// File: OptionsDlg.cpp

#include "ObjOperP.hxx"

#include "ObjOperR.h"		// IDC_FEATFROMORIGIN, ...

#include "ObjOper.hxx"		// ObjektOpExtension
#include "DlgFunctions.h"	// AdjustSheetWizardBttns()
#include "OptionsDlg.h"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif




///////////////////////////////////////////////////////////////////////////////////////////////
COptionsDlg::COptionsDlg (ResID uiDlg, LPCSTR pcCaption, OPTIONSRESULT caSelInfo)
		   : CPropertyPage (uiDlg, pcCaption), 
			 m_dwFlags (0L), 
			 m_CBoxFeature (this, IDC_FEATFROMORIGIN),
			 m_CBoxDelete (this, IDC_ORIGINDEL),
			 m_CBoxMark (this, IDC_ORIGINMARK),
			 m_CBoxShowNew (this, IDC_SHOWNEW),
			 m_CBoxShowOrig (this, IDC_SHOWORIG),
			 m_Descript (this, IDT_OPTDESCRIPT)
{
	m_OR = caSelInfo;
}


// --------------------------------------------------------------------------------------------
COptionsDlg::~COptionsDlg (void)
{
}


// --------------------------------------------------------------------------------------------
COptionsDlg* COptionsDlg::CreateInstance (UINT uiDlg, LPCSTR pcCaption,
										  OPTIONSRESULT caSelInfo, ResourceFile& rRF)
{
	try
	{
	COptionsDlg* pDlg = NULL;
	
		pDlg = new COptionsDlg (ResID (uiDlg, &rRF), pcCaption, caSelInfo);
		if (NULL == pDlg || !pDlg->FInit())
		{
			DELETE_OBJ (pDlg);
			return NULL;
		}
		return pDlg;

	}
	catch (...)
	{
		return NULL;
	}
}


// --------------------------------------------------------------------------------------------
bool COptionsDlg::FInit (void)
{
	return true;
}
	

///////////////////////////////////////////////////////////////////////////////////////////////
// EventHandler 
// Call-Back-Funktion für die Initialisierung der Controls
void COptionsDlg::WindowInit (Event)
{
    // explizite Initialisierung der Controls
	m_CBoxFeature.FInit();
	m_CBoxDelete.FInit();
	m_CBoxMark.FInit();
	m_CBoxShowNew.FInit();
	m_CBoxShowOrig.FInit();
	m_Descript.FInit();

	m_OR.bFeat ? m_CBoxFeature.SetChecked (true) : m_CBoxFeature.SetChecked (false);
	m_OR.bDelete ? m_CBoxDelete.SetChecked (true) : m_CBoxDelete.SetChecked (false);
	m_OR.bMark ? m_CBoxMark.SetChecked (true) : m_CBoxMark.SetChecked (false);

	if (m_OR.bDelete) _ASSERTE (m_OR.bMark == false);
	if (m_OR.bMark) _ASSERTE (m_OR.bDelete == false);

	m_OR.bShowNew ? m_CBoxShowNew.SetChecked (true) : m_CBoxShowNew.SetChecked (false);
	m_OR.bShowOrig ? m_CBoxShowOrig.SetChecked (true) : m_CBoxShowOrig.SetChecked (false);

	m_Descript.SetText (ResString (ResID (IDS_KOMM21, pRF), 250).Addr());

	AdjustSheetWizardBttns (this, m_dwFlags);

} // WindowInit


// --------------------------------------------------------------------------------------------
// Reaktion auf Click eines Buttons
void COptionsDlg::ButtonClick (ControlEvt e)
{
	switch ((uint) e.GetControlID())
	{
		case IDC_FEATFROMORIGIN:
			m_Descript.SetText (ResString (ResID (IDS_KOMM22, pRF), 250).Addr());
			break;

		case IDC_ORIGINDEL:
			m_CBoxMark.SetChecked (false);
			m_CBoxShowOrig.SetChecked (false);
			m_Descript.SetText (ResString (ResID (IDS_KOMM23, pRF), 250).Addr());
			break;

		case IDC_ORIGINMARK:
			m_CBoxDelete.SetChecked (false);
			m_Descript.SetText (ResString (ResID (IDS_KOMM24, pRF), 250).Addr());
			break;

		case IDC_SHOWNEW:
			m_Descript.SetText (ResString (ResID (IDS_KOMM25, pRF), 250).Addr());
			break;

		case IDC_SHOWORIG:
			m_CBoxDelete.SetChecked (false);
			m_Descript.SetText (ResString (ResID (IDS_KOMM26, pRF), 250).Addr());
			break;
	}
	
	AdjustSheetWizardBttns (this, m_dwFlags);

	// die nachfolgende  Zeile ist erforderlich, weil nicht immer OnKillActive() kommt
	PrepareResult();

} // ButtonClick


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn diese Page aktiviert werden soll (i. a. dann, wenn in der vorangehenden
// Page der Button "Weiter" bzw. in der nachfolgenden Page der Button "Zurück" gedrückt wurde)
BOOL COptionsDlg::OnSetActive (NotifyEvt e)
{
	m_Descript.SetText (ResString (ResID (IDS_KOMM21, pRF), 250).Addr());
	AdjustSheetWizardBttns (this, m_dwFlags);

	return FALSE;		// bei Gültigkeit "FALSE" sonst "TRUE" (???)
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn die diese Page deaktiviert werden soll; deshalb wird hier die Gültigkeit
// der Daten dieser Page überprüft (bei Gültigkeit "return FALSE" sonst "return TRUE")
BOOL COptionsDlg::OnKillActive (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern
	return FALSE;
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn der Button "Zurück" gedrückt wurde
// -1: cancel
int COptionsDlg::OnWizBack (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern
	return 0;
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn der Button "Weiter" gedrückt wurde
// -1: cancel
int COptionsDlg::OnWizNext (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern
	return 0;
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn Button "Fertig stellen" gedrückt wurde
// TRUE: cancel
BOOL COptionsDlg::OnWizFinish (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern
	return FALSE;
}


// --------------------------------------------------------------------------------------------
// Ergebnisdaten aus Controls lesen und zwischenspeichern
void COptionsDlg::PrepareResult (void)
{
	m_CBoxFeature.isChecked() ? (m_OR.bFeat = true) : (m_OR.bFeat = false);
	m_CBoxDelete.isChecked() ? (m_OR.bDelete = true) : (m_OR.bDelete = false);
	m_CBoxMark.isChecked() ? (m_OR.bMark = true) : (m_OR.bMark = false);
	m_CBoxShowNew.isChecked() ? (m_OR.bShowNew = true) : (m_OR.bShowNew = false);
	m_CBoxShowOrig.isChecked() ? (m_OR.bShowOrig = true) : (m_OR.bShowOrig = false);

} // PrepareResult


// --------------------------------------------------------------------------------------------
// Initialisierungsdaten für den Dialog aus pSelInfo übernehmen
HRESULT COptionsDlg::SetSelectedInfo (OPTIONSRESULT* pSelInfo, bool bNoShow)
{
	if (NULL == pSelInfo) return E_POINTER;

	m_OR = *pSelInfo;

	return S_OK;

} // SetSelectedInfo


// --------------------------------------------------------------------------------------------
// Zustand des Dialogs für evtl. Save() zwischenspeichern
HRESULT COptionsDlg::GetSelectedInfo (OPTIONSRESULT* pSelInfo, bool& bIsDirty)
{
	if (0 == pSelInfo) return E_POINTER;

	if (pSelInfo->bFeat != (BOOL)m_OR.bFeat ||
		pSelInfo->bDelete != (BOOL)m_OR.bDelete ||
		pSelInfo->bMark != (BOOL)m_OR.bMark ||
		pSelInfo->bShowNew != (BOOL)m_OR.bShowNew ||
		pSelInfo->bShowOrig != (BOOL)m_OR.bShowOrig)
	{
		*pSelInfo = m_OR;
		bIsDirty = true;	// Änderungen im Dialog
	}
	else
		bIsDirty = false;	// keine Änderungen

	return S_OK;

} // GetSelectedInfo
