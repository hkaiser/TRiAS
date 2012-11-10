// Definitionen: Dialog zu PropertyAction für Bilden von Flächen und Linien aus Linienelementen
// File: AreasBuildingDlg.cpp
// W. Mörtl

#include "ObjOperP.hxx"

#include <resstrg.h>		// IDS_UIFORMAT

#include "ObjOperR.h"		// IDS_BEARB_OBJEKT, ...

#include "ObjOper.hxx"		// ObjektOpExtension
#include "DlgFunctions.h"	// AdjustSheetWizardBttns()
#include "AreaBuildPropAct.h"
#include "AreasBuildingDlg.h"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif




///////////////////////////////////////////////////////////////////////////////////////////////
CAreasBuildingDlg::CAreasBuildingDlg (ResID uiDlg, LPCSTR pcCaption, CAreaBuildPropAct* pABPA,
									  AREABUILDRESULT caSelInfo)
				 : CPropertyPage (uiDlg, pcCaption), 
				   m_dwFlags (0L),
				   m_CBoxLines (this, IDC_LINESUNION),
				   m_TextFuzzy (this, IDT_FUZZY3),
				   m_EditFuzzy (this, IDE_FUZZY3),
				   m_Descript (this, IDT_AREADESCRIPT)
{
	m_bLines = caSelInfo.bLines;
	m_dFuzzy = caSelInfo.dFuzzy;
	m_pABPA = pABPA;
}


// --------------------------------------------------------------------------------------------
CAreasBuildingDlg::~CAreasBuildingDlg (void)
{
}


// --------------------------------------------------------------------------------------------
CAreasBuildingDlg* CAreasBuildingDlg::CreateInstance (UINT uiDlg, LPCSTR pcCaption,
						CAreaBuildPropAct* pABPA, AREABUILDRESULT caSelInfo, ResourceFile& rRF)
{
	try
	{
	CAreasBuildingDlg* pDlg = NULL;
	
		pDlg = new CAreasBuildingDlg (ResID (uiDlg, &rRF), pcCaption, pABPA, caSelInfo);
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
bool CAreasBuildingDlg::FInit (void)
{
	return true;
}
	

///////////////////////////////////////////////////////////////////////////////////////////////
// EventHandler 
// Call-Back-Funktion für die Initialisierung der Controls
void CAreasBuildingDlg::WindowInit (Event)
{
    // explizite Initialisierung der Controls
	m_CBoxLines.FInit();
	m_TextFuzzy.FInit();
	m_EditFuzzy.FInit();
	m_Descript.FInit();

long lNumber[4];	// lNumber[0]: Anzahl der selektierten (markierten) Objekte
					// (ausschließlich dem aktivierten, d.h. blinkenden Objekt)
					// lNumber[1]: Anzahl der selektierten Flächen (einschl. der aktivierten Fläche)
					// lNumber[2]: Anzahl der selektierten Kanten (einschl. der aktivierten Kante)
					// lNumber[3]: Anzahl der selektierten Punkte (einschl. des aktivierten Punktes)

	TypeCounter (lNumber);

	if (lNumber[2] >= 2)
	{
		GetStartTolerances (m_dFuzzy);	// Startwert für Toleranz ermitteln
		m_EditFuzzy.SetValue (m_dFuzzy);

		m_CBoxLines.Enable();
		m_CBoxLines.SetChecked (true);
		m_TextFuzzy.Enable();
		m_EditFuzzy.Enable();
	}
	else
	{
		m_CBoxLines.Disable();
		m_TextFuzzy.Disable();
		m_EditFuzzy.Disable();

		m_Descript.SetText (ResString (ResID (IDS_KOMM28, pRF), 250).Addr());
	}

	NoReadOnlyAll() ? (m_bKnowOC = true) : (m_bKnowOC = false);

} // WindowInit


// --------------------------------------------------------------------------------------------
// Reaktion auf Click eines Buttons
void CAreasBuildingDlg::ButtonClick (ControlEvt e)
{
	if (IDC_LINESUNION == (uint) e.GetControlID())
		m_Descript.SetText (ResString (ResID (IDS_KOMM19, pRF), 250).Addr());

	if (m_CBoxLines.isChecked())
	{
		m_TextFuzzy.Enable();
		m_EditFuzzy.Enable();
		if (NumEditToDouble (&m_EditFuzzy, m_dFuzzy) && m_dFuzzy >= 0.)
			AdjustSheetWizardBttns (this, m_dwFlags);
		else
			AdjustSheetWizardBttns (this, m_dwFlags, true);
	}
	else
	{
		m_TextFuzzy.Disable();
		m_EditFuzzy.Disable();
		AdjustSheetWizardBttns (this, m_dwFlags);
	}

	// die nachfolgende  Zeile ist erforderlich, weil nicht immer OnKillActive() kommt
	PrepareResult();

} // ButtonClick


// --------------------------------------------------------------------------------------------
// Reaktion auf Eingabe in das Editierfelder
void CAreasBuildingDlg::EditChange (ControlEvt e)
{
	if (IDE_FUZZY3 == (uint) e.GetControlID())
	{
		if (NumEditToDouble (&m_EditFuzzy, m_dFuzzy) && m_dFuzzy >= 0.)
			AdjustSheetWizardBttns (this, m_dwFlags);
		else
			AdjustSheetWizardBttns (this, m_dwFlags, true);
	}
} // EditChange


// --------------------------------------------------------------------------------------------
// das Editierfelder erhält den Focus
void CAreasBuildingDlg::EditFocusChg (EditFocusChgEvt e)
{
	if (!e.gotFocus())
		return;		// Focus wurde entfernt

	if (IDE_FUZZY3 == (uint) e.GetControlID())
		m_Descript.SetText (ResString (ResID (IDS_KOMM20, pRF), 250).Addr());
} // EditFocusChg


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn diese Page aktiviert werden soll (i. a. dann, wenn in der vorangehenden
// Page der Button "Weiter" bzw. in der nachfolgenden Page der Button "Zurück" gedrückt wurde)
BOOL CAreasBuildingDlg::OnSetActive (NotifyEvt e)
{
	m_Descript.SetText (ResString (ResID (IDS_KOMM18, pRF), 250).Addr());

	if (NumEditToDouble (&m_EditFuzzy, m_dFuzzy) && m_dFuzzy >= 0.)
		AdjustSheetWizardBttns (this, m_dwFlags);
	else
		AdjustSheetWizardBttns (this, m_dwFlags, true);

	return FALSE;	// bei Gültigkeit "FALSE" sonst "TRUE" (???)
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn die diese Page deaktiviert werden soll; deshalb wird hier die Gültigkeit
// der Daten dieser Page überprüft (bei Gültigkeit "return FALSE" sonst "return TRUE")
BOOL CAreasBuildingDlg::OnKillActive (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern
	return FALSE;
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn der Button "Zurück" gedrückt wurde
// -1: cancel
int CAreasBuildingDlg::OnWizBack (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern
	return 0;
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn der Button "Weiter" gedrückt wurde
// -1: cancel
int CAreasBuildingDlg::OnWizNext (NotifyEvt)
{
#if _TRiAS_VER >= 0x0300

	// in der ModifyIdent-Page die CheckBox zur Auswahl einer Objektklasse anzeigen
	// (CheckMode=1), wenn für die Ergebnisobjekte der Flächenbildung (und evtl. Linienbildung)
	// eine Objektklasse ausgewählt werden kann aber nicht muß (Normalfall);
	// Ausnahme: die zu vereinigenden Objekte stammen aus einer schreibgeschützten Datenquelle
	// bzw. Objektklasse, hier MUß für die Ergebnisobjekte der Vereinigung eine neue
	// (beschreibbare) Objektklasse ausgewählt werden
	try
	{
	WPropertyActionSequence wSeq;
	WDataObject wDO;
	CComVariant vClKey;

		THROW_FAILED_HRESULT (m_pABPA->GetSite (IID_IPropertyActionSequence, wSeq.ppv()));		
		THROW_FAILED_HRESULT (wSeq->GetSequenceContext (wDO.ppi()));		

		if (m_bKnowOC)
			vClKey = CComVariant ("CheckMode=1;Checked=0;");
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
BOOL CAreasBuildingDlg::OnWizFinish (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern
	return FALSE;
}


// --------------------------------------------------------------------------------------------
// Ergebnisdaten aus Controls lesen und zwischenspeichern
void CAreasBuildingDlg::PrepareResult (void)
{
	m_CBoxLines.isChecked() ? (m_bLines = true) : (m_bLines = false);
	NumEditToDouble (&m_EditFuzzy, m_dFuzzy);
} // PrepareResult


// --------------------------------------------------------------------------------------------
// die dem Dialog übergebenen Objekte bearbeiten
HRESULT CAreasBuildingDlg::ExecuteOperation (HPROJECT hPr, IEnumLONG* pEnumIn, DWORD dwOptions,
											 IEnumLONG** ppEnumOut, IProgressIndicator2* pPI)
{
	if (0 == pEnumIn || 0 == ppEnumOut)
		return E_POINTER; // ohne Daten und Rückgabemöglichkeit hat's nicht viel Zweck

	*ppEnumOut = NULL;			// für Fehlerfall

bool bNoModify = false;		// in der ModifyIdent-Page wurde eine Objektklasse ausgewählt
ulong ulIdent = (ulong)0;	// Identifikator des 1. Objektes
long lONr = 0;

	// in der ModifyIdent-Page wurde nichts ausgewählt bzw. diese Seite ist gar nicht da, dann
	// Zieldatenquelle aus dem 1. Objekt ableiten
	if (0 == hPr)
	{
		pEnumIn->Reset();
		RETURN_FAILED_HRESULT (pEnumIn->Next (1, &lONr, NULL));
		hPr = DEX_GetObjectProject (lONr);
		ulIdent = DEX_GetObjIdent (lONr);
		bNoModify = true;
	}

bool bCopyFeat;

	(dwOptions & FEAT) ? (bCopyFeat = true) : (bCopyFeat = false);


HRESULT hrRet = S_OK;
// Objektnummern der neu gebildeten Linien- bzw. Flächenobjekte
WEnumObjectsByNumber wEnumOut1, wEnumOut2;
// alle bzw. die zur Linien- bzw. Flächenbildung beigetragenden Original-Objekte
WEnumLONG wEnumUsed, wEnumUsed1, wEnumUsed2;
											
	try
	{
	WProgressIndicator2 wPI (pPI);

		if (! wPI.IsValid())
		{
			wPI = WProgressIndicator2(CLSID_ProgressIndicator);	// throws_com_error

		HWND hWnd = NULL;

			THROW_FAILED_HRESULT (wPI->InitNew ((INT_PTR)g_pTE->MWind()->Handle(), 0L,
												(LONG *)&hWnd));
		}

	// ProgressIndicator pPI in Struktur varPI speichern
	VARIANT varPI;
	
		VariantInit (&varPI);
		V_VT (&varPI) = VT_UNKNOWN;
		V_UNKNOWN (&varPI) = wPI;

	// Objektnummern der Originalobjekte, die zu einer Vereinigung beigetragen haben
	VARIANT varUsed;

		VariantInit (&varUsed);

#if _TRiAS_VER < 0x0300

	WExtLinienVerfolgung LinVer (CLSID_ExtLinienVerfolgung);	// CLSID aus imaschen.h
	
		hrRet = LinVer->LinesUnion (
				(WEnumObjectsByNumber)pEnumIn,	// zu vereinigende Objekte
				m_dFuzzy,			// Fangbereich zweier Stützpunkte
				bCopyFeat,			// Merkmale der Vereinigten vererben
				TRUE,				// vereinigte Linien in Flächen umwandeln (TRUE)
				varPI,				// Fortschrittsanzeige (optional)
				&varUsed,			// Objektnummern der zur Vereinigung beitragenden (optional)
				wEnumOut2.ppi());	// Objektnummern der Vereinigten
#else

	WExtLinienVerfolgungEx LinVer (CLSID_ExtLinienVerfolgung);	// CLSID aus imaschen.h

		hrRet = LinVer->LinesUnion (
				reinterpret_cast<INT_PTR>(hPr),
				(WEnumObjectsByNumber)pEnumIn,	// zu vereinigende Objekte
				m_dFuzzy,			// Fangbereich zweier Stützpunkte
				bCopyFeat,			// Merkmale der Vereinigten vererben
				TRUE,				// vereinigte Linien in Flächen umwandeln (TRUE)
				varPI,				// Fortschrittsanzeige (optional)
				&varUsed,			// Objektnummern der zur Vereinigung beitragenden (optional)
				wEnumOut2.ppi());	// Objektnummern der Vereinigten

#endif // _TRiAS_VER < 0x0300

	ulong ulCnt = 0;	// Anzahl der neu gebildeten Flächen

		if (!wEnumOut2.IsValid() || FAILED(wEnumOut2->GetCount (&ulCnt)))
			ulCnt = 0;

		if (0 == ulCnt)		// keine Fläche gebildet
		{
		ResString resTitel (ResID (IDS_LONGCLASSNAME, pRF), 50);
		ResString resText (ResID (IDS_BOXTEXT6, pRF), 200);
				
			MessageBox (__hWndM, resText.Addr(), resTitel.Addr(), MB_ICONINFORMATION | MB_OK);
		}

		if (NULL != varUsed.punkVal)	// die zur Vereinigung beigetragenen Original-Objekte
			wEnumUsed2 = varUsed.punkVal;

		RestLinesUnion (hPr, pEnumIn, wEnumUsed2, bCopyFeat, varPI, wEnumUsed1.ppi(),
						wEnumOut1.ppi());

		// gebildete Flächen- bzw. Linienobjekte zurückgeben
		if (wEnumOut2.IsValid())
		{
			*ppEnumOut = (WEnumLONG)wEnumOut2.detach();		// Flächen
			wEnumUsed = wEnumUsed2;

			if (wEnumOut1.IsValid())
			{
				for (wEnumOut1->Reset(); S_OK == wEnumOut1->Next (1, &lONr, NULL);)	// Linien
					((IEnum<LONG>*)*ppEnumOut)->AddItem (lONr);

				for (wEnumUsed1->Reset(); S_OK == wEnumUsed1->Next (1, &lONr, NULL);)
					((IEnum<LONG>*)(IEnumLONG*)wEnumUsed)->AddItem (lONr);
			}
		}
		else if (wEnumOut1.IsValid())
		{
			*ppEnumOut = (WEnumLONG)wEnumOut1.detach();		// Linien
			wEnumUsed = wEnumUsed1;
		}
	}

	catch (_com_error& e)
	{
		// Anbindung an Erweiterung "maschbld.ext" ist nicht gelungen
		if (HRESULT_FROM_WIN32(ERROR_DLL_NOT_FOUND) == _COM_ERROR(e))
		{
		ResString resTitel (ResID (IDS_LONGCLASSNAME, pRF), 50);
		ResString resText (ResID (IDS_NOMASCHBLD, pRF), 250);

			MessageBox (__hWndM, resText.Addr(), resTitel.Addr(), MB_ICONEXCLAMATION | MB_OK);
		}

		return _COM_ERROR (e);
	}


ulong ulCnt = 0;	// Anzahl der neu gebildeten Objekte

	if (NULL != *ppEnumOut && (ulCnt = (*ppEnumOut)->Count()) > 0)
	{
		if (bNoModify)	// in der ModifyIdent-Page wurde keine Objektklasse ausgewählt
			SetDefaultIdent ((WEnumLONG)(*ppEnumOut), ulIdent, ulCnt);

	ObjektOpExtension* pOOE = (ObjektOpExtension*)g_pTE;

		_ASSERTE (NULL != pOOE);

		pOOE->SetMembers (wEnumUsed, (WEnumLONG)(*ppEnumOut));
		pOOE->OptionsAnalyse (dwOptions);


// auf Grund eines Fehlers in CreateMaschen() in maschbil.cpp werden im "alten" TRiAS entweder
// der neue UniqueIdent ODER die anderen Merkmale an die neuen Objekte weggeschrieben; deshalb
// hier noch das Wegschreiben des UniqueIdent
#if _TRiAS_VER < 0x0300
	string sUIdent;
	ResString UniqueIdent (ResID (IDS_UIFORMAT, pRF), 20);

		for ((*ppEnumOut)->Reset(); S_OK == (*ppEnumOut)->Next (1, &lONr, NULL);)
		{
			Format (sUIdent, (char*)UniqueIdent.Addr(), lONr);
			WriteFeatureText (lONr, DEX_GetUniqueIdentMCode(), TT_Objekt, sUIdent);
		}
#endif // _TRiAS_VER < 0x0300
	}

	return hrRet;

} // ExecuteOperation


// --------------------------------------------------------------------------------------------
// Vereinigung der restlichen Linien, aus denen sich keine Flächen bilden ließen, zu Linien
HRESULT CAreasBuildingDlg::RestLinesUnion (HPROJECT hPr, IEnumLONG* pEnumIn,
								 IEnumLONG* pEnumUsedA, bool bCopyFeat, VARIANT varPI,
								 IEnumLONG** ppEnumUsedL, IEnumObjectsByNumber** ppEnumOutRest)
{
	if (!m_bLines)
		return S_FALSE;

	_ASSERTE (NULL != pEnumIn);
	_ASSERTE (NULL != pEnumUsedA);
//	_ASSERTE (NULL != pEnumUsedL);

// Objektnummern der restlichen Originalobjekte, die zur Linienvereinigung beigetragen haben
VARIANT varUsed;

	VariantInit (&varUsed);

long lONr1 = 0, lONr2 = 0;
HRESULT hr;

	COM_TRY
	{
	WEnumObjectsByNumber wEnumInRest (CLSID_EnumObjectsByNumber);

		for (pEnumIn->Reset(); S_OK == pEnumIn->Next (1, &lONr1, NULL); )
		{
			for (pEnumUsedA->Reset(); S_OK == (hr = pEnumUsedA->Next (1, &lONr2, NULL)); )
			{
				if (lONr1 == lONr2)
					break;
			}
			if (S_OK != hr)
				THROW_FAILED_HRESULT (wEnumInRest->AddItem (lONr1));
		}

#if _TRiAS_VER < 0x0300

	WExtLinienVerfolgung LinVer (CLSID_ExtLinienVerfolgung);	// CLSID aus imaschen.h
		
		THROW_FAILED_HRESULT (LinVer->LinesUnion (wEnumInRest, m_dFuzzy, bCopyFeat, FALSE,
												  varPI, &varUsed, ppEnumOutRest));
#else

	WExtLinienVerfolgungEx LinVer (CLSID_ExtLinienVerfolgung);	// CLSID aus imaschen.h

		THROW_FAILED_HRESULT (LinVer->LinesUnion (reinterpret_cast<INT_PTR>(hPr), wEnumInRest,
								  m_dFuzzy, bCopyFeat, FALSE, varPI, &varUsed, ppEnumOutRest));
#endif // _TRiAS_VER < 0x0300

	if (NULL != varUsed.punkVal)	// die zur Linienbildung beigetragenen Original-Objekte
		*ppEnumUsedL = (IEnumLONG*)varUsed.punkVal;
	}
	COM_CATCH;

	return S_OK;

} // RestLinesUnion


// --------------------------------------------------------------------------------------------
// Initialisierungsdaten für den Dialog aus pSelInfo übernehmen
HRESULT CAreasBuildingDlg::SetSelectedInfo (AREABUILDRESULT* pSelInfo, bool bNoShow)
{
	if (NULL == pSelInfo) return E_POINTER;

	m_bLines = pSelInfo->bLines;
	m_dFuzzy = pSelInfo->dFuzzy;

	return S_OK;

} // SetSelectedInfo


// --------------------------------------------------------------------------------------------
// Zustand des Dialogs für evtl. Save() zwischenspeichern
HRESULT CAreasBuildingDlg::GetSelectedInfo (AREABUILDRESULT* pSelInfo, bool& bIsDirty)
{
	if (NULL == pSelInfo) return E_POINTER;

	if (pSelInfo->bLines != (BOOL)m_bLines ||
		pSelInfo->dFuzzy != m_dFuzzy)
	{
		pSelInfo->bLines = (BOOL)m_bLines;
		pSelInfo->dFuzzy = m_dFuzzy;
		bIsDirty = true;	// Änderungen im Dialog
	}
	else
		bIsDirty = false;	// keine Änderungen

	return S_OK;

} // GetSelectedInfo
