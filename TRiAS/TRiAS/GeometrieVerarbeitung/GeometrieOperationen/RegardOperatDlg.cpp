// Definitionen: Dialog zu PropertyAction für Operationen von GeoObjekten mit Bezugsobjekt(en)
// File: RegardOperatDlg.cpp
// W. Mörtl

#include "ObjOperP.hxx"

#include "ObjOperR.h"		// IDC_INTER, ...

#include "ObjOper.hxx"		// ObjektOpExtension
#include "DlgFunctions.h"	// NoReadOnlySel()
#include "RegOperatPropAct.h"
#include "RegardOperatDlg.h"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif




///////////////////////////////////////////////////////////////////////////////////////////////
CRegardOperatDlg::CRegardOperatDlg (ResID uiDlg, LPCSTR pcCaption, CRegOperatPropAct* pROPA,
									REGOPERATRESULT caSelInfo)
				: CPropertyPage (uiDlg, pcCaption), 
				  m_dwFlags (0L),
//				  m_CBoxClassKey (this, IDC_CLASSKEY),
				  m_Location (this, IDT_LOCATION),
				  m_CBoxInter (this, IDC_INTER),
				  m_CBoxExter (this, IDC_EXTER),
				  m_CBoxBound (this, IDC_BOUND),
				  m_Descript (this, IDT_REGDESCRIPT)
{
	m_bClassKey = caSelInfo.bClassKey;
	m_bInter = caSelInfo.bInter;
	m_bExter = caSelInfo.bExter;
	m_bBound = caSelInfo.bBound;
	m_lRegObjONr = 0;
	m_iRegObjOT = OT_UNKNOWN;
	m_pROPA = pROPA;
}


// --------------------------------------------------------------------------------------------
CRegardOperatDlg::~CRegardOperatDlg (void)
{
}


// --------------------------------------------------------------------------------------------
CRegardOperatDlg* CRegardOperatDlg::CreateInstance (UINT uiDlg, LPCSTR pcCaption,
						CRegOperatPropAct* pROPA, REGOPERATRESULT caSelInfo, ResourceFile& rRF)
{
	try
	{
	CRegardOperatDlg* pDlg = NULL;
	
		pDlg = new CRegardOperatDlg (ResID (uiDlg, &rRF), pcCaption, pROPA, caSelInfo);
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
bool CRegardOperatDlg::FInit (void)
{
	return true;
}
	

///////////////////////////////////////////////////////////////////////////////////////////////
// EventHandler 
// Call-Back-Funktion für die Initialisierung der Controls
void CRegardOperatDlg::WindowInit (Event)
{
    // explizite Initialisierung der Controls
//	m_CBoxClassKey.FInit();
	m_Location.FInit();
	m_CBoxInter.FInit();
	m_CBoxExter.FInit();
	m_CBoxBound.FInit();
	m_Descript.FInit();

	m_Location.Disable();
	m_CBoxInter.Disable();
	m_CBoxExter.Disable();
	m_CBoxBound.Disable();

	// wenn sich unter den selektierten Objekten auch Objekte aus schreibgeschützten
	// Datenquellen bzw. Objektkklassen befinden, dann muß für die Zielobjekte eine neue
	// Objektklasse ausgewählt werden
//	m_bClassKey ? m_CBoxClassKey.SetChecked (true) : m_CBoxClassKey.SetChecked (false);
	if (NoReadOnlySel())
	{
//		m_CBoxClassKey.Enable();
		m_bClassKeyEnable = true;
	}
	else
	{
//		m_CBoxClassKey.Disable();
		m_bClassKeyEnable = false;
	}

	m_bInter ? m_CBoxInter.SetChecked (true) : m_CBoxInter.SetChecked (false);
	m_bBound ? m_CBoxBound.SetChecked (true) : m_CBoxBound.SetChecked (false);
	m_bExter ? m_CBoxExter.SetChecked (true) : m_CBoxExter.SetChecked (false);

	if (OT_FLAECHE == m_iRegObjOT)
	{
		m_Location.Enable();
		m_CBoxInter.Enable();
		m_CBoxExter.Enable();
		m_CBoxBound.Enable();
		m_Descript.SetText (ResString (ResID (IDS_KOMM1, pRF), 250).Addr());
	}
	else if (OT_KANTE == m_iRegObjOT)
		m_Descript.SetText (ResString (ResID (IDS_KOMM2, pRF), 250).Addr());
	else if (OT_PUNKT == m_iRegObjOT)
		m_Descript.SetText (ResString (ResID (IDS_KOMM3, pRF), 250).Addr());
	else
	{
		_ASSERTE (OT_PUNKT == m_iRegObjOT || OT_KANTE == m_iRegObjOT || OT_FLAECHE == m_iRegObjOT);

//		m_CBoxClassKey.Disable();
		m_Descript.SetText (ResString (ResID (IDS_KOMM4, pRF), 250).Addr());
		AdjustSheetWizardBttns (this, m_dwFlags, true);
		return;
	}


#if _TRiAS_VER < 0x0300
	// die Steuerung der ModifyIdent-Page ist nur in TRiAS300 möglich
//	m_CBoxClassKey.SetChecked (false);
//	m_CBoxClassKey.Disable();
#endif // _TRiAS_VER < 0x0300

} // WindowInit


// --------------------------------------------------------------------------------------------
// Reaktion auf Click eines Buttons bzw. einer ComboBox
void CRegardOperatDlg::ButtonClick (ControlEvt e)
{
	switch ((uint) e.GetControlID())
	{
		case IDC_CLASSKEY:
			m_Descript.SetText (ResString (ResID (IDS_KOMM5, pRF), 250).Addr());
			break;

		case IDC_INTER:
			m_Descript.SetText (ResString (ResID (IDS_KOMM6, pRF), 250).Addr());
			break;

		case IDC_EXTER:
			m_Descript.SetText (ResString (ResID (IDS_KOMM7, pRF), 250).Addr());
			break;

		case IDC_BOUND:
			m_Descript.SetText (ResString (ResID (IDS_KOMM8, pRF), 250).Addr());
			break;
	}

	if (m_CBoxInter.isChecked() || m_CBoxBound.isChecked() || m_CBoxExter.isChecked())
		AdjustSheetWizardBttns (this, m_dwFlags);
	else
	{
		m_Descript.SetText (ResString (ResID (IDS_KOMM9, pRF), 250).Addr());
		AdjustSheetWizardBttns (this, m_dwFlags, true);
	}

	// die nachfolgende  Zeile ist erforderlich, weil nicht immer OnKillActive() kommt
	PrepareResult();

} // ButtonClick


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn diese Page aktiviert werden soll (i. a. dann, wenn in der vorangehenden
// Page der Button "Weiter" bzw. in der nachfolgenden Page der Button "Zurück" gedrückt wurde)
BOOL CRegardOperatDlg::OnSetActive (NotifyEvt e)
{
	if (OT_FLAECHE == m_iRegObjOT)
		m_Descript.SetText (ResString (ResID (IDS_KOMM1, pRF), 250).Addr());
	else if (OT_KANTE == m_iRegObjOT)
		m_Descript.SetText (ResString (ResID (IDS_KOMM2, pRF), 250).Addr());
	else if (OT_PUNKT == m_iRegObjOT)
		m_Descript.SetText (ResString (ResID (IDS_KOMM3, pRF), 250).Addr());
	else
	{
		_ASSERTE (OT_PUNKT == m_iRegObjOT || OT_KANTE == m_iRegObjOT || OT_FLAECHE == m_iRegObjOT);
		m_Descript.SetText (ResString (ResID (IDS_KOMM4, pRF), 250).Addr());
	}

	if (m_bInter || m_bBound || m_bExter)
		AdjustSheetWizardBttns (this, m_dwFlags);
	else
		AdjustSheetWizardBttns (this, m_dwFlags, true);
	return FALSE;		// bei Gültigkeit "FALSE" sonst "TRUE" (???)
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn die diese Page deaktiviert werden soll; deshalb wird hier die Gültigkeit
// der Daten dieser Page überprüft (bei Gültigkeit "return FALSE" sonst "return TRUE")
BOOL CRegardOperatDlg::OnKillActive (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern
	return FALSE;
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn der Button "Zurück" gedrückt wurde
// -1: cancel
int CRegardOperatDlg::OnWizBack (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern
	return 0;
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn der Button "Weiter" gedrückt wurde
// -1: cancel
int CRegardOperatDlg::OnWizNext (NotifyEvt)
{
#if _TRiAS_VER >= 0x0300

	// in der ModifyIdent-Page die CheckBox zur Auswahl einer Objektklasse anzeigen
	// (CheckMode=1), wenn für die Ergebnisobjekte der Schnittoperation eine Objektklasse
	// ausgewählt werden kann aber nicht muß (Normalfall);
	// Ausnahme: die zu schneidenden Objekte stammen aus einer schreibgeschützten Datenquelle
	// bzw. Objektklasse, hier MUß für die Ergebnisobjekte der Schnittoperation eine neue
	// (beschreibbare) Objektklasse ausgewählt werden
	try
	{
	WPropertyActionSequence wSeq;
	WDataObject wDO;
	CComVariant vClKey;

		THROW_FAILED_HRESULT (m_pROPA->GetSite (IID_IPropertyActionSequence, wSeq.ppv()));		
		THROW_FAILED_HRESULT (wSeq->GetSequenceContext (wDO.ppi()));		

		// CheckBox in der ModifyIdent-Page wird in Abhängigkeit von m_CBoxClassKey gesetzt
		if (m_bClassKeyEnable)
		{
//			if (m_CBoxClassKey.isChecked())
//				vClKey = CComVariant ("CheckMode=1;Checked=0;");
//			else
				vClKey = CComVariant ("CheckMode=1;Checked=1;");
		}
		else	// für Ergebnisobjekte muß neue Objektklasse ausgewählt werden
			vClKey = CComVariant ("CheckMode=0;");

		THROW_FAILED_HRESULT (SetVariantData (vClKey, wDO, &c_feModifyIdent));
	}
	catch (_com_error&)
	{
		return -1;
	}

#endif // _TRiAS_VER >= 0x0300

	PrepareResult();	// Ergebnisse zwischenspeichern
	return 0;
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn Button "Fertig stellen" gedrückt wurde
// TRUE: cancel
BOOL CRegardOperatDlg::OnWizFinish (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern
	return FALSE;
}


// --------------------------------------------------------------------------------------------
// Ergebnisdaten aus Controls lesen und zwischenspeichern
void CRegardOperatDlg::PrepareResult (void)
{
//	m_CBoxClassKey.isChecked() ? (m_bClassKey = true) : (m_bClassKey = false);
	m_CBoxInter.isChecked() ? (m_bInter = true) : (m_bInter = false);
	m_CBoxExter.isChecked() ? (m_bExter = true) : (m_bExter = false);
	m_CBoxBound.isChecked() ? (m_bBound = true) : (m_bBound = false);

} // PrepareResult


// --------------------------------------------------------------------------------------------
// die dem Dialog übergebenen Objekte bearbeiten
HRESULT CRegardOperatDlg::ExecuteOperation (HPROJECT hPr, IEnumLONG* pEnumIn, DWORD dwOptions,
											IEnumLONG** ppEnumOut, IProgressIndicator2* pPI)
{
	if (0 == pEnumIn || 0 == ppEnumOut)
		return E_POINTER; // ohne Daten und Rückgabemöglichkeit hat's nicht viel Zweck

	*ppEnumOut = 0;		// für Fehlerfall

WEnumLONG wEnumRegard, wEnumUsed;	// Objektnummern der Bezugs- bzw. der verwendeten Objekte

	try
	{
	WEnumLONG wEnumReg (CLSID_EnumObjectsByNumber);
	WEnumLONG wEnumUse (CLSID_EnumObjectsByNumber);

		wEnumRegard = wEnumReg;
		wEnumUsed = wEnumUse;
	}
	catch (_com_error& e) 
	{
		return _COM_ERROR (e);
	}

	((IEnum<LONG>*)(IEnumLONG*)wEnumRegard)->AddItem (m_lRegObjONr);

DWORD dwLageAusw = 0x00;

	if (m_bInter)
		dwLageAusw |= LINN;
	if (m_bBound)
		dwLageAusw |= LKONT;
	if (m_bExter)
		dwLageAusw |= LAUSS;

bool bFortAnz = true;	// mit Fortschrittsanzeige
bool bCopyFeat;

	(dwOptions & FEAT) ? (bCopyFeat = true) : (bCopyFeat = false);

ObjektOpExtension* pOOE = (ObjektOpExtension*)g_pTE;

	_ASSERTE (0 != pOOE);

HRESULT hrRet = pOOE->ObjectSection (hPr, wEnumRegard, pEnumIn, dwLageAusw, bCopyFeat,
									 bFortAnz, wEnumUsed.ppi(), ppEnumOut);

	pOOE->OptionsAnalyse (dwOptions);

	return hrRet;

} // ExecuteOperation


// --------------------------------------------------------------------------------------------
// Initialisierungsdaten für den Dialog aus pSelInfo übernehmen
HRESULT CRegardOperatDlg::SetSelectedInfo (REGOPERATRESULT* pSelInfo, bool bNoShow)
{
	if (NULL == pSelInfo) return E_POINTER;

	m_bClassKey = pSelInfo->bClassKey;
	m_bInter = pSelInfo->bInter;
	m_bExter = pSelInfo->bExter;
	m_bBound = pSelInfo->bBound;

	return S_OK;

} // SetSelectedInfo


// --------------------------------------------------------------------------------------------
// Zustand des Dialogs für evtl. Save() zwischenspeichern
HRESULT CRegardOperatDlg::GetSelectedInfo (REGOPERATRESULT* pSelInfo, bool& bIsDirty)
{
	if (0 == pSelInfo) return E_POINTER;

	if (pSelInfo->bClassKey != (BOOL)m_bClassKey ||
		pSelInfo->bInter != (BOOL)m_bInter ||
		pSelInfo->bExter != (BOOL)m_bExter ||
		pSelInfo->bBound != (BOOL)m_bBound)
	{
		pSelInfo->bClassKey = (BOOL)m_bClassKey;
		pSelInfo->bInter = (BOOL)m_bInter;
		pSelInfo->bExter = (BOOL)m_bExter;
		pSelInfo->bBound = (BOOL)m_bBound;
		bIsDirty = true;	// Änderungen im Dialog
	}
	else
		bIsDirty = false;	// keine Änderungen

	return S_OK;

} // GetSelectedInfo
