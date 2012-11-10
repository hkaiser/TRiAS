// Definitionen: Dialog zu PropertyAction für Mengenoperationen von GeoObjekten
// File: SetsOperatDlg.cpp
// W. Mörtl

#include "ObjOperP.hxx"

#include "ObjOperR.h"		// IDC_OROPERAT, ...

#include "ObjOper.hxx"		// ObjektOpExtension
#include "DlgFunctions.h"	// GetStartTolerances()
#include "SetsOperatPropAct.h"
#include "SetsOperatDlg.h"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


///////////////////////////////////////////////////////////////////////////////////////////////
// Testen, ob alle beteiligten Objekte aus ein und derselben Objektklasse sind, dann ist der
// return-Wert "true"
BOOL _OBJOPER_EXPORT FAR PASCAL ObjectClassTest (long lONr, BOOL, void* pvIdent)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

ulong ulIdent = DEX_GetObjIdent (lONr);

	if (0 == (*(ulong*)pvIdent))
	{
		*(ulong*)pvIdent = ulIdent;
		return TRUE;
	}

	if (ulIdent == (*(ulong*)pvIdent))
		return TRUE;
	return FALSE;
}


// --------------------------------------------------------------------------------------------
// Ermittlung der größten Breite und -höhe der ObjektContainer aller recherchierten
// Linienobjekte (die größte Breite bzw. Höhe muß nicht vom gleichen Objekt stammen)
BOOL _OBJOPER_EXPORT FAR PASCAL GreatestObjectContainer (long lONr, BOOL, void* pvCont)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

	if (OT_KANTE != DEX_GetObjectType (lONr))
		return TRUE;

ObjRechteck* pOR = (ObjRechteck*)pvCont;
long lCO[4];	// Containerkoordinaten eines Objektes
				// lCO[0] = xmin, lCO[1] = xmax, lCO[2] = ymin, lCO[3] = ymax

	DEX_GetObjContainer (lONr, lCO);
	if (pOR->XMax() - pOR->XMin() < lCO[1] - lCO[0])
	{
		pOR->XMax() = lCO[1];
		pOR->XMin() = lCO[0];
	}
	if (pOR->YMax() - pOR->YMin() < lCO[3] - lCO[2])
	{
		pOR->YMax() = lCO[3];
		pOR->YMin() = lCO[2];
	}

	return TRUE;
}



///////////////////////////////////////////////////////////////////////////////////////////////
CSetsOperatDlg::CSetsOperatDlg (ResID uiDlg, LPCSTR pcCaption, CSetsOperatPropAct* pSOPA,
								SETSOPERATRESULT caSelInfo)
			  : CPropertyPage (uiDlg, pcCaption),
				m_dwFlags (0L), 
				m_RBttnOr (this, IDC_OROPERAT),
				m_RBttnAnd (this, IDC_ANDOPERAT),
				m_RBttnXOr (this, IDC_XOROPERAT),
				m_TextFuzzy (this, IDT_FUZZY1),
				m_EditFuzzy (this, IDE_FUZZY1),
				m_Descript (this, IDT_SETSDESCRIPT)
{
	m_OpMode = caSelInfo.OpMode;
	m_dFuzzy = caSelInfo.dFuzzy;
	m_pSOPA = pSOPA;
	m_fHasInitData = false;
}


// --------------------------------------------------------------------------------------------
CSetsOperatDlg::~CSetsOperatDlg (void)
{
}


// --------------------------------------------------------------------------------------------
CSetsOperatDlg* CSetsOperatDlg::CreateInstance (UINT uiDlg, LPCSTR pcCaption, 
					  CSetsOperatPropAct* pSOPA, SETSOPERATRESULT caSelInfo, ResourceFile& rRF)
{
	try
	{
	CSetsOperatDlg* pDlg = NULL;
	
		pDlg = new CSetsOperatDlg (ResID (uiDlg, &rRF), pcCaption, pSOPA, caSelInfo);
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
bool CSetsOperatDlg::FInit (void)
{
	return true;
}
	

///////////////////////////////////////////////////////////////////////////////////////////////
// EventHandler 
// Call-Back-Funktion für die Initialisierung der Controls
void CSetsOperatDlg::WindowInit (Event)
{
    // explizite Initialisierung der Controls
	m_RBttnOr.FInit();
	m_RBttnAnd.FInit();
	m_RBttnXOr.FInit();
	m_TextFuzzy.FInit();
	m_EditFuzzy.FInit();
	m_Descript.FInit();

	if (!m_fHasInitData)
		GetStartTolerances (m_dFuzzy);	// Startwert für Fangbereich ermitteln
	m_EditFuzzy.SetValue (m_dFuzzy);

	// Windows scheint beim Aktivieren der Page standardmäßig den 1. Button einer Gruppe zu
	// aktivieren. Will man eine andere Einstellung, unterläßt also den Befehl
	// "RadioButton1.SetState (true)", wird von Windows automatisch ein Pseudo-ButtonClick auf
	// diesen 1. Button ausgelöst. Um dies zu unterbinden, die nachfolgende Zeile. In
	// OnSetMyMessage() wird dann die eigentlich von mir gewollte Einstellung vorgenommen
	// (05.01.99).
	m_RBttnOr.SetState (true);

} // WindowInit


// --------------------------------------------------------------------------------------------
// Reaktion auf Click eines Buttons
void CSetsOperatDlg::ButtonClick (ControlEvt e)
{
	switch ((uint) e.GetControlID())
	{
		case IDC_OROPERAT:
			if (m_lNumber[2] >= 2)
			{
				m_TextFuzzy.Enable();
				m_EditFuzzy.Enable();
			}
			else
			{
				m_TextFuzzy.Disable();
				m_EditFuzzy.Disable();
			}
			m_Descript.SetText (ResString (ResID (IDS_KOMM10, pRF), 250).Addr());
			break;

		case IDC_ANDOPERAT:
			m_TextFuzzy.Disable();
			m_EditFuzzy.Disable();
			m_Descript.SetText (ResString (ResID (IDS_KOMM11, pRF), 250).Addr());
			break;

		case IDC_XOROPERAT:
			m_TextFuzzy.Disable();
			m_EditFuzzy.Disable();
			m_Descript.SetText (ResString (ResID (IDS_KOMM12, pRF), 250).Addr());
			break;
	}

	AdjustSheetWizardBttns (this, m_dwFlags);

	// die nachfolgende  Zeile ist erforderlich, weil nicht immer OnKillActive() kommt
	PrepareResult();

} // ButtonClick


// --------------------------------------------------------------------------------------------
// Reaktion auf Eingabe in das Editierfelder
void CSetsOperatDlg::EditChange (ControlEvt e)
{
	if (IDE_FUZZY1 == (uint) e.GetControlID())
	{
		if (NumEditToDouble (&m_EditFuzzy, m_dFuzzy) && m_dFuzzy >= 0.)
			AdjustSheetWizardBttns (this, m_dwFlags);
		else
			AdjustSheetWizardBttns (this, m_dwFlags, true);
	}
} // EditChange


// --------------------------------------------------------------------------------------------
// eines der Editierfelder erhält den Focus
void CSetsOperatDlg::EditFocusChg (EditFocusChgEvt e)
{
	if (!e.gotFocus())
		return;		// Focus wurde entfernt

	if (IDE_FUZZY1 == (uint) e.GetControlID())
		m_Descript.SetText (ResString (ResID (IDS_KOMM20, pRF), 250).Addr());
} // EditFocusChg


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn diese Page aktiviert werden soll (i. a. dann, wenn in der vorangehenden
// Page der Button "Weiter" bzw. in der nachfolgenden Page der Button "Zurück" gedrückt wurde)
BOOL CSetsOperatDlg::OnSetActive (NotifyEvt e)
{
	if (m_RBttnOr.GetState())
		m_Descript.SetText (ResString (ResID (IDS_KOMM10, pRF), 250).Addr());
	else if (m_RBttnAnd.GetState())
		m_Descript.SetText (ResString (ResID (IDS_KOMM11, pRF), 250).Addr());
	else if (m_RBttnXOr.GetState())
		m_Descript.SetText (ResString (ResID (IDS_KOMM12, pRF), 250).Addr());

	_ASSERTE (m_RBttnOr.GetState() || m_RBttnAnd.GetState() || m_RBttnXOr.GetState());

	// Mit nachfolgendem Befehl wird ein RadioButton und der Focus über eine PostMessage
	// gesetzt. Das hat zur Folge, daß diese Aktion erst dann ausgeführt wird, wenn Windows mit
	// seinem Kram fertig ist.
	// Dieser Umweg wurde erforderlich, weil durch Windows beim Aktivieren der Page automatisch
	// ein Pseudo-ButtonClick auf den 1. RadioButton auslöst wird, wenn ein SCHON IN
	// WindowInit() gesetzter RadioButton nicht der 1. RadioButton der Gruppe ist.
	// Außerdem wurde ein in WindowInit() gesetzter Focus (aus unklaren Gründen) durch Windows
	// wieder gelöscht. 
	PostEvent (WM_SETMYMESSAGE);

	AdjustSheetWizardBttns (this, m_dwFlags);
	return FALSE;	// bei Gültigkeit "FALSE" sonst "TRUE" (???)
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn die diese Page deaktiviert werden soll; deshalb wird hier die Gültigkeit
// der Daten dieser Page überprüft (bei Gültigkeit "return FALSE" sonst "return TRUE")
BOOL CSetsOperatDlg::OnKillActive (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern
	return FALSE;
}


// --------------------------------------------------------------------------------------------
// Reaktion auf WindowsMessages
LRESULT CSetsOperatDlg::Dispatch (Event e)
{
	if (WM_SETMYMESSAGE == e.Msg())
		return OnSetMyMessage();
	return CPropertyPage::Dispatch (e);
}


// --------------------------------------------------------------------------------------------
// RadioButton und Focus im Dialog setzen
LRESULT CSetsOperatDlg::OnSetMyMessage (void)
{
	TypeCounter (m_lNumber);

	if (m_lNumber[1] < 2 && m_lNumber[2] < 2)
	{
		m_RBttnOr.Disable();
		m_RBttnAnd.Disable();
		m_RBttnXOr.Disable();
		m_TextFuzzy.Disable();
		m_EditFuzzy.Disable();
		m_Descript.SetText (ResString (ResID (IDS_KOMM13, pRF), 250).Addr());
		AdjustSheetWizardBttns (this, m_dwFlags, true);
//		return FALSE;
		return TRUE;
	}

	// Aufheben der in WindowInit() (siehe dort) notgedrungenermaßen eingefügten Aktivierung
	// des 1. RadioButtons
	m_RBttnOr.SetState (false);

	if (m_lNumber[1] >= 2 &&	// Durchschnitt vorübergehend nur für Flächen !!!
		m_lNumber[2] < 2)
		m_RBttnAnd.Enable();
	else
	{
		m_RBttnAnd.Disable();
		if (DURCHSCHNITT == m_OpMode)
			m_OpMode = SUBTRAKTION;
	}

	if (2 == m_lNumber[1] &&	// Exklusiv-Oder vorübergehend nur für genau 2 Flächen !!!
		m_lNumber[2] < 2)
		m_RBttnXOr.Enable();
	else
	{
		m_RBttnXOr.Disable();
		if (SUBTRAKTION == m_OpMode)
			m_OpMode = VEREINIGUNG;
	}

	m_TextFuzzy.Disable();
	m_EditFuzzy.Disable();

	if (VEREINIGUNG == m_OpMode)
	{
		m_RBttnOr.SetState (true);
		m_RBttnOr.SetFocus();
		m_Descript.SetText (ResString (ResID (IDS_KOMM10, pRF), 250).Addr());

		if (m_lNumber[2] >= 2)
		{
			m_TextFuzzy.Enable();
			m_EditFuzzy.Enable();
		}
	}

	else if (DURCHSCHNITT == m_OpMode)
	{
		m_RBttnAnd.SetState (true);
		m_RBttnAnd.SetFocus();
		m_Descript.SetText (ResString (ResID (IDS_KOMM11, pRF), 250).Addr());
	}

	else if (SUBTRAKTION == m_OpMode)
	{
		m_RBttnXOr.SetState (true);
		m_RBttnXOr.SetFocus();
		m_Descript.SetText (ResString (ResID (IDS_KOMM12, pRF), 250).Addr());
//		m_bKnowOC = true;	(s.u.)
	}

	else
		_ASSERTE (m_OpMode == VEREINIGUNG || m_OpMode == DURCHSCHNITT ||
				   m_OpMode == SUBTRAKTION);

	if (NoReadOnlyAll())
	{
		if (VEREINIGUNG == m_OpMode || DURCHSCHNITT == m_OpMode)
		{
		ENUMLONGKEY ELK;	// Enumeration aller selektierten Objekte
		ulong ulIdent = 0;

			ELK.eKey = (DWORD) 0;	// Suchschlüssel (Fenster-Handle von allen Recherchefenstern)
			ELK.eFcn = (ENUMLONGKEYPROC) ObjectClassTest;	// zu rufende Funktion
			ELK.ePtr = (void*) &ulIdent;					// durchgereichte Daten
			m_bKnowOC = DEX_EnumSelectedObjects (ELK);
		}
		else
			m_bKnowOC = true;
	}
	else
		m_bKnowOC = false;

	AdjustSheetWizardBttns (this, m_dwFlags);
//	return TRUE;
	return FALSE;
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn der Button "Zurück" gedrückt wurde
// -1: cancel
int CSetsOperatDlg::OnWizBack (NotifyEvt)
{
	if (PrepareResult())	// Ergebnisse zwischenspeichern
		return 0;
	return -1;
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn der Button "Weiter" gedrückt wurde
// -1: cancel
int CSetsOperatDlg::OnWizNext (NotifyEvt)
{
#if _TRiAS_VER >= 0x0300

	// in der ModifyIdent-Page die CheckBox zur Auswahl einer Objektklasse nicht anzeigen
	// (CheckMode=0), wenn bei Vereinigung bzw. Durchschnitt die beteiligten Objekte aus
	// verschiedenen Objektklassen stammen, da in in diesem Fall für die Ergbnisobjekte eine
	// neue Objektklasse ausgewählt werden muß; in allen anderen Fällen kann eine neue
	// Objektklasse ausgewählt werden, muß aber nicht
	try
	{
	WPropertyActionSequence wSeq;
	WDataObject wDO;
	CComVariant vClKey;

		THROW_FAILED_HRESULT (m_pSOPA->GetSite (IID_IPropertyActionSequence, wSeq.ppv()));		
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

	if (PrepareResult())	// Ergebnisse zwischenspeichern
		return 0;
	return -1;
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn Button "Fertig stellen" gedrückt wurde
// true: cancel
BOOL CSetsOperatDlg::OnWizFinish (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern
	return FALSE;
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn Button "Abbrechen" gedrückt wurde
void CSetsOperatDlg::OnCancel (NotifyEvt)
{
	// evtl. Aufräumarbeiten durchführen
}


// --------------------------------------------------------------------------------------------
// Ergebnisdaten aus Controls lesen und zwischenspeichern
bool CSetsOperatDlg::PrepareResult (void)
{
	m_OpMode = LEER;	// für den Fehlerfall

	if (m_RBttnOr.GetState())
		m_OpMode = VEREINIGUNG;
	else if (m_RBttnAnd.GetState())
		m_OpMode = DURCHSCHNITT;
	else if (m_RBttnXOr.GetState())
//	{
		m_OpMode = SUBTRAKTION;
//		m_bKnowOC = true;
//	}

	_ASSERTE (m_OpMode != LEER);

//	m_bKnowOC = NoReadOnlyAll();	siehe OnKillActive()

	NumEditToDouble (&m_EditFuzzy, m_dFuzzy);

	return true;

} // PrepareResult


// --------------------------------------------------------------------------------------------
// die dem Dialog übergebenen Objekte bearbeiten
HRESULT CSetsOperatDlg::ExecuteOperation (HPROJECT hPr, IEnumLONG* pEnumIn, DWORD dwOptions,
										  IEnumLONG** ppEnumOut, IProgressIndicator2* pPI)
{
	if (0 == pEnumIn || 0 == ppEnumOut)
		return E_POINTER; // ohne Daten und Rückgabemöglichkeit hat's nicht viel Zweck

	*ppEnumOut = 0;		// für Fehlerfall

// Eingangsobjekte in Flächen- und Linienobjekte aufteilen
WEnumLONG wAreaEnumIn (CLSID_EnumObjectsByNumber);
WEnumLONG wLineEnumIn (CLSID_EnumObjectsByNumber);
long lONr = 0;

	for (pEnumIn->Reset(); S_OK == pEnumIn->Next (1, &lONr, NULL); )
	{
	int iOT = DEX_GetObjectType (lONr);

		if (OT_FLAECHE == iOT)
			((IEnum<LONG>*)(IEnumLONG*)wAreaEnumIn)->AddItem (lONr);

		if (OT_KANTE == iOT)
			((IEnum<LONG>*)(IEnumLONG*)wLineEnumIn)->AddItem (lONr);
	}

bool bCopyFeat = dwOptions & FEAT;	// Merkmale der Originalobjekte evtl. vererben
WEnumLONG wEnumOut;		// durch Objektoperation erzeuget neue Objekte
WEnumLONG wOrigEnum;	// Originalobjekte, die zu den neuen Objekten beigetragen haben
HRESULT hr = S_OK;
ObjektOpExtension* pOOE = (ObjektOpExtension*)g_pTE;

	_ASSERTE (0 != pOOE);

	switch (m_OpMode)	// ausgewählte Objektoperation
	{
		case VEREINIGUNG:
			// Flächenvereinigung
			if (((IEnumLONG*)wAreaEnumIn)->Count() >= 2)
			{
			// default-Name für Objektklasse der Ergebnisobjekte für den Fall, daß Anwender
			// keine Objektklasse für die Ergebnisobjekte auswählt (wenn z.B. Ursprungsobjekte
			// und Ergebnisobjekte zur gleichen Objektklasse gehören sollen)
			string sOCName;

				if (m_bKnowOC)
				{
					// Objektnummer des 1. Objektes ermitteln
					wAreaEnumIn->Reset();

					if (SUCCEEDED (wAreaEnumIn->Next (1, &lONr, NULL)))
					{
					// Identifikator des 1. Objektes ermitteln
					ulong ulIdent = DEX_GetObjIdentEx (lONr);

						if (!GetKurzText (ulIdent, 'i', sOCName))
							sOCName = sUnionName;
					}
					else
						sOCName = sUnionName;

					// in der ModifyIdent-Page wurde nichts ausgewählt bzw. diese Seite ist gar
					// nicht da
					if (0 == hPr)
						hPr = DEX_GetObjectProject (lONr);
				}
				else
					sOCName = sUnionName;

				HRESULT hr = pOOE->AreasUniting (hPr, wAreaEnumIn, sOCName,
                    bCopyFeat, wOrigEnum.ppi(), wEnumOut.ppi(), pPI);
                if (FAILED(hr))
                    return hr;
            }


			// Linienvereinigung
			if (((IEnumLONG*)wLineEnumIn)->Count() >= 2) {
			bool bAsArea = false;	// vereinigte Linien nicht in Flächen umwandeln
			WEnumLONG wOEnum;		// die neu erzeugten zusammengefaßten Linien
			CEierUhr Wait (this);	// es kann dauern bis der ProgressIndicator angezeigt wird
			ulong ulIdent = 0;

				// in der ModifyIdent-Page wurde nichts ausgewählt bzw. diese Seite ist gar
				// nicht da, dann default-Identifikator für die Ergebnisobjekte vorgeben
				if (0 == hPr)
				{
					GetDefaultIdent (m_bKnowOC, wLineEnumIn, sUnionName, ulIdent);
					hPr = DEX_GetObjectsProject (ulIdent);
				}


				// nicht mit RETURN_FAILED_HRESULT(), um eine unnötige Assertion zu unterbinden
				hr = pOOE->LinesUniting (hPr, wLineEnumIn, m_dFuzzy, bCopyFeat,
										 bAsArea, ulIdent, wOrigEnum.ppi(), wOEnum.ppi(), pPI);

				if (FAILED (hr) || ERROR_WRITE_PROTECT == hr)
					return hr;

			ulong ulCnt = 0;	// Anzahl der evtl. schon vorhandenen Ergebnisobjekte

				if (wEnumOut.IsValid())
					ulCnt = ((IEnumLONG*)wEnumOut)->Count();

				if (0 == ulCnt)
					wEnumOut = wOEnum;
				else if (wOEnum.IsValid())
				{
					for (wOEnum->Reset(); S_OK == wOEnum->Next (1, &lONr, NULL); )
						((IEnum<LONG>*)(IEnumLONG*)wEnumOut)->AddItem (lONr);
				}
			}

			if (!wEnumOut.IsValid() || 0 == wEnumOut->Count()) {
			ResString resTitel (ResID (IDS_LONGCLASSNAME, pRF), 50);
			ResString resText (ResID (IDS_BOXTEXT2, pRF), 200);
	
				MessageBox (__hWndM, resText.Addr(), resTitel.Addr(),
							MB_ICONINFORMATION | MB_OK);
			}

			break;


		case DURCHSCHNITT:
			if (((IEnumLONG*)wAreaEnumIn)->Count() >= 2)
			{
			ulong ulIdent = 0;

				// in der ModifyIdent-Page wurde nichts ausgewählt bzw. diese Seite ist gar
				// nicht da, dann default-Identifikator für die Ergebnisobjekte vorgeben
				if (0 == hPr)
				{
					if (m_bKnowOC)
					{
						// Identifikator des 1. Objektes vorgeben
						wAreaEnumIn->Reset();
						RETURN_FAILED_HRESULT (wAreaEnumIn->Next (1, &lONr, NULL));
						ulIdent = DEX_GetObjIdent (lONr);
					}
					else
					{
						ulIdent = DEX_GetIdentFromClassName (sMeaningName.c_str());
						if (0 == ulIdent)	// dieser Identifikator ist noch nicht in der PBD
						{
							ulIdent = DEX_GetUniqueICode();
							IdentNachtragen (ulIdent, sMeaningName, false);
						}
					}
				}

			SpForm sfSForm = SFORM_PERM;	// Speicherform: permanent
			bool bFortAnz = true;			// mit Fortschrittsanzeige

				hr = pOOE->DurchschnittsFlaeche (hPr, wAreaEnumIn, ulIdent, bCopyFeat, sfSForm,
												 bFortAnz, wEnumOut.ppi());
			}

			if (((IEnumLONG*)wLineEnumIn)->Count() >= 2)
				hr = E_NOTIMPL;		// LinienDurchschnitt noch nicht implementiert
			break;


		case SUBTRAKTION:
		{
		bool bOrigZeigen = false, bNeuZeigen = false;

			if (!pOOE->ExklusivOder (hPr, bCopyFeat, bOrigZeigen, bNeuZeigen,
									 wOrigEnum.ppi(), wEnumOut.ppi()))
			{
			ResString resTitel (ResID (IDS_LONGCLASSNAME, pRF), 50);
			ResString resText (ResID (IDS_BOXTEXT4, pRF), 200);

				MessageBox (__hWndM, resText.Addr(), resTitel.Addr(), MB_ICONINFORMATION | MB_OK);
			}
			break;
		}

		default:
			_ASSERTE (false);
			return E_UNEXPECTED;

	} // switch

	if (wEnumOut.IsValid() && wEnumOut->Count() > 0)
	{
		pOOE->OptionsAnalyse (dwOptions);

		// Ergebnisobjekte zurückgeben
		*ppEnumOut = wEnumOut.detach();
	}
	
	return hr;

} // ExecuteOperation


// --------------------------------------------------------------------------------------------
// Initialisierungsdaten für den Dialog aus pSelInfo übernehmen
HRESULT CSetsOperatDlg::SetSelectedInfo (SETSOPERATRESULT* pSelInfo, bool bNoShow)
{
	if (NULL == pSelInfo) return E_POINTER;

	m_OpMode = pSelInfo->OpMode;
	m_dFuzzy = pSelInfo->dFuzzy;
	m_fHasInitData = true;

	return S_OK;

} // SetSelectedInfo


// --------------------------------------------------------------------------------------------
// Zustand des Dialogs für evtl. Save() zwischenspeichern
HRESULT CSetsOperatDlg::GetSelectedInfo (SETSOPERATRESULT* pSelInfo, bool& bIsDirty)
{
	if (0 == pSelInfo) return E_POINTER;

	if (pSelInfo->OpMode != m_OpMode ||
		pSelInfo->dFuzzy != m_dFuzzy)
	{
		pSelInfo->OpMode = m_OpMode;
		pSelInfo->dFuzzy = m_dFuzzy;
		bIsDirty = true;	// Änderungen im Dialog
	}
	else
		bIsDirty = false;	// keine Änderungen

	return S_OK;

} // GetSelectedInfo
