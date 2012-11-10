// Definitionen: Dialog zu PropertyAction für Splitten von Linienobjekten
// File: LinesSplittingDlg.cpp
// W. Mörtl

#include "ObjOperP.hxx"

#include "ObjOperR.h"		// IDS_BEARB_OBJEKT, ...

#include "ObjOper.hxx"		// ObjektOpExtension
#include "DlgFunctions.h"	// GetStartTolerances()
#include "LineSplitPropAct.h"
#include "LinesSplittingDlg.h"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif




///////////////////////////////////////////////////////////////////////////////////////////////
CLinesSplittingDlg::CLinesSplittingDlg (ResID uiDlg, LPCSTR pcCaption,
										CLineSplitPropAct* pLSPA, LINESPLITRESULT caSelInfo)
				  : CPropertyPage (uiDlg, pcCaption), 
					m_dwFlags (0L),
					m_TextFuzzy (this, IDT_FUZZY2),
					m_EditFuzzy (this, IDE_FUZZY2),
					m_TextDangle (this, IDT_DANGLE),
					m_EditDangle (this, IDE_DANGLE),
					m_Descript (this, IDT_LINEDESCRIPT)
{
	m_dFuzzy = caSelInfo.dFuzzy;
	m_dDangle = caSelInfo.dDangle;
	m_fForceTolerances = false;
	m_fForceSelectObjClass = false;

	m_fHasInitData = false;

	m_pLSPA = pLSPA;
}


// --------------------------------------------------------------------------------------------
CLinesSplittingDlg::~CLinesSplittingDlg (void)
{
}


// --------------------------------------------------------------------------------------------
CLinesSplittingDlg* CLinesSplittingDlg::CreateInstance (UINT uiDlg, LPCSTR pcCaption,
						CLineSplitPropAct* pLSPA, LINESPLITRESULT caSelInfo, ResourceFile& rRF)
{
	try
	{
	CLinesSplittingDlg* pDlg = NULL;
	
		pDlg = new CLinesSplittingDlg (ResID (uiDlg, &rRF), pcCaption, pLSPA, caSelInfo);
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
bool CLinesSplittingDlg::FInit (void)
{
	return true;
}
	

///////////////////////////////////////////////////////////////////////////////////////////////
// EventHandler 
// Call-Back-Funktion für die Initialisierung der Controls
void CLinesSplittingDlg::WindowInit (Event)
{
    // explizite Initialisierung der Controls
	m_TextFuzzy.FInit();
	m_EditFuzzy.FInit();
	m_TextDangle.FInit();
	m_EditDangle.FInit();
	m_Descript.FInit();

long lNumber[4];	// lNumber[0]: Anzahl der selektierten (markierten) Objekte
					// (ausschließlich dem aktivierten, d.h. blinkenden Objekt)
					// lNumber[1]: Anzahl der selektierten Flächen (einschl. der aktivierten Fläche)
					// lNumber[2]: Anzahl der selektierten Kanten (einschl. der aktivierten Kante)
					// lNumber[3]: Anzahl der selektierten Punkte (einschl. des aktivierten Punktes)

	TypeCounter (lNumber);

	if (lNumber[2] >= 2 || m_fForceTolerances)
	{
		if (!m_fHasInitData)
			GetStartTolerances (m_dFuzzy, &m_dDangle);	// Startwerte für Toleranzen ermitteln
		m_EditFuzzy.SetValue (m_dFuzzy);
		m_EditDangle.SetValue (m_dDangle);

		m_TextFuzzy.Enable();
		m_EditFuzzy.Enable();
		m_TextDangle.Enable();
		m_EditDangle.Enable();
	}
	else
	{
		m_TextFuzzy.Disable();
		m_EditFuzzy.Disable();
		m_TextDangle.Disable();
		m_EditDangle.Disable();

		m_Descript.SetText (ResString (ResID (IDS_KOMM27, pRF), 250).Addr());
	}

	m_bKnowOC = NoReadOnlyAll();

} // WindowInit


// --------------------------------------------------------------------------------------------
// Reaktion auf Eingabe in eines der Editierfelder
void CLinesSplittingDlg::EditChange (ControlEvt e)
{
	switch ((uint) e.GetControlID())
	{
		case IDE_FUZZY2:
			if (NumEditToDouble (&m_EditFuzzy, m_dFuzzy) && m_dFuzzy >= 0.)
				AdjustSheetWizardBttns (this, m_dwFlags);
			else
				AdjustSheetWizardBttns (this, m_dwFlags, true);
			break;

		case IDE_DANGLE:
			if (NumEditToDouble (&m_EditDangle, m_dDangle) && m_dDangle >= 0.)
				AdjustSheetWizardBttns (this, m_dwFlags);
			else
				AdjustSheetWizardBttns (this, m_dwFlags, true);
			break;
	}
} // EditChange


// --------------------------------------------------------------------------------------------
// eines der Editierfelder erhält den Focus
void CLinesSplittingDlg::EditFocusChg (EditFocusChgEvt e)
{
	if (!e.gotFocus())
		return;		// Focus wurde entfernt

	switch ((uint) e.GetControlID())
	{
		case IDE_FUZZY2:
			m_Descript.SetText (ResString (ResID (IDS_KOMM16, pRF), 250).Addr());
			break;

		case IDE_DANGLE:
			m_Descript.SetText (ResString (ResID (IDS_KOMM17, pRF), 250).Addr());
			break;
	}
} // EditFocusChg


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn diese Page aktiviert werden soll (i. a. dann, wenn in der vorangehenden
// Page der Button "Weiter" bzw. in der nachfolgenden Page der Button "Zurück" gedrückt wurde)
BOOL CLinesSplittingDlg::OnSetActive (NotifyEvt e)
{
	m_Descript.SetText (ResString (ResID (IDS_KOMM15, pRF), 250).Addr());

	if (NumEditToDouble (&m_EditFuzzy, m_dFuzzy) && m_dFuzzy >= 0. &&
		NumEditToDouble (&m_EditDangle, m_dDangle) && m_dDangle >= 0.)
		AdjustSheetWizardBttns (this, m_dwFlags);
	else
		AdjustSheetWizardBttns (this, m_dwFlags, true);

	return FALSE;	// bei Gültigkeit "FALSE" sonst "TRUE" (???)
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn die diese Page deaktiviert werden soll; deshalb wird hier die Gültigkeit
// der Daten dieser Page überprüft (bei Gültigkeit "return FALSE" sonst "return TRUE")
BOOL CLinesSplittingDlg::OnKillActive (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern
	return FALSE;
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn der Button "Zurück" gedrückt wurde
// -1: cancel
int CLinesSplittingDlg::OnWizBack (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern
	return 0;
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn der Button "Weiter" gedrückt wurde
// -1: cancel
int CLinesSplittingDlg::OnWizNext (NotifyEvt)
{
#if _TRiAS_VER >= 0x0300

	// in der ModifyIdent-Page die CheckBox zur Auswahl einer Objektklasse anzeigen
	// (CheckMode=1), wenn für die Ergebnisobjekte der Splittoperation eine Objektklasse
	// ausgewählt werden kann aber nicht muß (Normalfall);
	// Ausnahme: die zu schneidenden Objekte stammen aus einer schreibgeschützten Datenquelle
	// bzw. Objektklasse, hier MUß für die Ergebnisobjekte der Schnittoperation eine neue
	// (beschreibbare) Objektklasse ausgewählt werden
	try
	{
	WPropertyActionSequence wSeq;
	WDataObject wDO;
	CComVariant vClKey;

		THROW_FAILED_HRESULT (m_pLSPA->GetSite (IID_IPropertyActionSequence, wSeq.ppv()));		
		THROW_FAILED_HRESULT (wSeq->GetSequenceContext (wDO.ppi()));		

		if (m_bKnowOC && !m_fForceSelectObjClass)
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
BOOL CLinesSplittingDlg::OnWizFinish (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern
	return FALSE;
}


// --------------------------------------------------------------------------------------------
// Ergebnisdaten aus Controls lesen und zwischenspeichern
void CLinesSplittingDlg::PrepareResult (void)
{
	NumEditToDouble (&m_EditFuzzy, m_dFuzzy);
	NumEditToDouble (&m_EditDangle, m_dDangle);
} // PrepareResult


// --------------------------------------------------------------------------------------------
// die dem Dialog übergebenen Objekte bearbeiten
HRESULT CLinesSplittingDlg::ExecuteOperation (HPROJECT hPr, IEnumLONG* pEnumIn,
	DWORD dwOptions, IEnumLONG** ppEnumOut, IEnumLONG** ppEnumNotUsed, 
	IProgressIndicator2* pPI)
{
	if (0 == pEnumIn || 0 == ppEnumOut)
		return E_POINTER; // ohne Daten und Rückgabemöglichkeit hat's nicht viel Zweck

	*ppEnumOut = 0;		// für Fehlerfall

ObjektOpExtension* pOOE = (ObjektOpExtension*)g_pTE;

	_ASSERTE (0 != pOOE);

KoOrd lFuzzyX, lFuzzyY, lDangle;	// Toleranzen im DB-Format

	CalculateTolerances (pEnumIn, lFuzzyX, lFuzzyY, lDangle);

WEnumLONG wEnumUsed;	// Objektnummern der verwendeten Objekte
HRESULT hrRet = pOOE->SplittingBase (hPr, pEnumIn, lFuzzyX, lFuzzyY, lDangle,
	ppEnumOut, wEnumUsed.ppi(), ppEnumNotUsed);

	pOOE->OptionsAnalyse (dwOptions);
	return hrRet;
} // ExecuteOperation


// --------------------------------------------------------------------------------------------
// Initialisierungsdaten für den Dialog aus pSelInfo übernehmen
HRESULT CLinesSplittingDlg::SetSelectedInfo (LINESPLITRESULT* pSelInfo, bool bNoShow)
{
	if (NULL == pSelInfo) return E_POINTER;

	m_dFuzzy = pSelInfo->dFuzzy;
	m_dDangle = pSelInfo->dDangle;
	m_fForceTolerances = pSelInfo->fForceTolerances;
	m_fForceSelectObjClass = pSelInfo->fForceSelectObjClass;

	m_fHasInitData = true;

	return S_OK;

} // SetSelectedInfo


// --------------------------------------------------------------------------------------------
// Zustand des Dialogs für evtl. Save() zwischenspeichern
HRESULT CLinesSplittingDlg::GetSelectedInfo (LINESPLITRESULT* pSelInfo, bool& bIsDirty)
{
	if (0 == pSelInfo) return E_POINTER;

	if (pSelInfo->dFuzzy != m_dFuzzy ||
		pSelInfo->dDangle != m_dDangle)
	{
		pSelInfo->dFuzzy = m_dFuzzy;
		pSelInfo->dDangle = m_dDangle;
		bIsDirty = true;	// Änderungen im Dialog
	}
	else
		bIsDirty = false;	// keine Änderungen

	return S_OK;

} // GetSelectedInfo


// --------------------------------------------------------------------------------------------
// Berechnung der Fuzzy- und Dangle-Toleranz im DB-Format
HRESULT CLinesSplittingDlg::CalculateTolerances (IEnumLONG* pEnumIn, KoOrd& lFuzzyX,
												 KoOrd& lFuzzyY, KoOrd& lDangle)
{
	_ASSERTE (0 != pEnumIn);

// einen Bezugspunkt ermitteln; dazu wird der Anfangspunkt der 1. Linie genutzt
WObjektGeometrie wObj;		// ObjektGeometrie und
long lONr = -1;				// Parameter der 1. Linie
KoOrd* plXK; KoOrd* plYK;

    COM_TRY
    {
   		pEnumIn->Reset();

	HRESULT hr = pEnumIn->Next (1, &lONr, NULL);

		_ASSERTE (lONr != 0);
		_ASSERTE (lONr != -1);

    	if (S_OK == hr)
		{
		WInitObjektGeometrie wIObj (CLSID_ObjektGeometrie);

			THROW_FAILED_HRESULT (wIObj->InitObjGeometry (lONr));

			wObj = wIObj;
			wObj->GetX ((void**)&plXK);
			wObj->GetY ((void**)&plYK);
		}
		else _com_issue_error (hr);
    }
	COM_CATCH;	// enthält eine Assertion

// Fuzzy-Toleranzen berechnen
CoordTransX CTX;
DoublePair dpKoord, dpInFuzzy (m_dFuzzy, m_dFuzzy), dpOutFuzzy;

	// Skalierung von DB-Koordinaten entfernen
	if (! CTX.UnScale (plXK[0], plYK[0], &dpKoord.X(), &dpKoord.Y()))
		return E_FAIL;

	// einen um Fuzzy-Toleranz entfernten Punkt ermitteln
	if (! CTX.CoordTransRectangle (&dpKoord, &dpInFuzzy, &dpOutFuzzy))
		return E_FAIL;

// Skalierung wieder hinzufügen
KoOrd lNewKoordX, lNewKoordY;

	if (! CTX.Scale (dpOutFuzzy.X(), dpOutFuzzy.Y(), &lNewKoordX, &lNewKoordY))
		return E_FAIL;

	lFuzzyX = abs (lNewKoordX - plXK[0]);
	lFuzzyY = abs (lNewKoordY - plYK[0]);

//	Dangle-Länge berechnen
DoublePair dpInDangle (sqrt(2.)/2.*m_dDangle, sqrt(2.)/2.*m_dDangle), dpOutDangle;

	// einen um Dangle-Länge entfernten Punkt ermitteln
	if (! CTX.CoordTransRectangle (&dpKoord, &dpInDangle, &dpOutDangle))
		return E_FAIL;

	// Skalierung wieder hinzufügen
	if (! CTX.Scale (dpOutDangle.X(), dpOutDangle.Y(), &lNewKoordX, &lNewKoordY))
		return E_FAIL;

double dLen = sqrt ((double)(lNewKoordX-plXK[0]) * (double)(lNewKoordX-plXK[0]) +
					(double)(lNewKoordY-plYK[0]) * (double)(lNewKoordY-plYK[0]));

	_ASSERTE (dLen + 0.5 < (double)ULONG_MAX);

	lDangle = (ULONG) (dLen + 0.5);

	return S_OK;

} // CalculateTolerances
