// Verwaltung einer Abfolge von IPropertyActions ------------------------------
// File: PROPSEQ.HXX

#include "featurep.hxx"
#include "feature.h"

#if _MSC_VER >= 1000
#pragma warning (disable:4786)	// truncation of identifier name in browser database
#endif // _MSC_VER

#include <eieruhr.hxx>

#include <propguid.h>
#include "propseq.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DefineSmartInterface(DataObject);

#define IMPL_AND_FAILED(hr)	(FAILED(hr)&&!(E_NOTIMPL==GetScode(hr)))

// Erzeugen einer Instanz dieses Objektes -------------------------------------
HRESULT PActCreateInstance (REFIID riid, LPVOID *ppvObj)
{
CPropertySequence *pSeq = CPropertySequence::CreateInstance();
		
	if (NULL == pSeq)
		return ResultFromScode (E_OUTOFMEMORY);
	
HRESULT	hr = pSeq -> QueryInterface (riid, ppvObj);

	pSeq -> Release();

return hr;
}

// sonstige HelperFunktionen --------------------------------------------------
// Liefert Enumerator mit allen registrierten KlassenEigenschaften ------------
HRESULT GetEnumClassProps (ITriasXtensionSite *pIXtnSite, IEnumClassProps **ppIEnum)
{
// alle Objekt- und sonstigen Eigenschaften von TRiAS besorgen
WObjectProps IProps = pIXtnSite;
HRESULT hr = GetLastHRESULT();

	if (FAILED(hr)) return hr;

	hr = IProps -> OnNewReferenceClass (NULL);	// initialisieren 
	if (SUCCEEDED(hr))
		hr = IProps -> EnumClassProps (ppIEnum);

return hr;
}

// Fehler beim erzeugen einer PropertyAction: Fehler melden und weiteres ------
// Vorgehen abfragen
static bool ReportAddError (LPCSTR pcName)
{
ResString resCap (ResID (IDS_GENERRORCAP, &g_pTE -> RF()), 64);
ResString resText (ResID (IDS_ADDERROR, &g_pTE -> RF()), 64);
ResString resQuery (ResID (IDS_QUERYCONTINUE, &g_pTE -> RF()), 64);
char cbBuffer[256];

	wsprintf (cbBuffer, resText, pcName);

string str = cbBuffer;

	str += resQuery;

MessBox mb (resCap, str.c_str(), g_pTE -> MWind());

	mb.SetType (YesNoButtons|QuestionMarkIcon);
	if (YesReply == mb.Show())
		return false;	// weitermachen

return true;	// Abbrechen und nicht weitermachen
}

// Fügt eine PropertyAction zur AktionsFolge hinzu ----------------------------
HRESULT AddPropertyAction (IPropertyActionSequence *pISeq, 
			   IEnumClassProps *pIEnumCls, LPCSTR pcName)
{
// Suchen (und Finden) der ClassProperty über den Namen
WClassProperty IClsP;
HRESULT	hr = pIEnumCls -> FindByName (pcName, IClsP.ppi());

	if (FAILED(hr)) return hr;

// wir brauchen aber das IPropertyAction-Interface
WPropertyAction IAct = IClsP;

	hr = GetLastHRESULT();
	if (FAILED(hr)) return hr;

return pISeq -> AddAction (IAct);		// ...und hinzufügen
}

// Erzeugen und initialisieren einer PropertyActionSequence, welche die
// vorgegebenen PropertyActions enthält
HRESULT InitPropertyActionSequence (ITriasXtensionSite *pIXtnSite,
	    LPCSTR pcbActs[], int iCnt, IPropertyActionSequence **ppISeq)
{
	*ppISeq = NULL;		// für alle Fälle

WPropertyActionSequence ISeq;
HRESULT hr = PActCreateInstance (IID_IPropertyActionSequence, ISeq.ppv());

	if (FAILED(hr)) return hr;

// aktivieren der gewünschten AktionsFolge
WEnumClassProps IEnumCls;
	
	hr = GetEnumClassProps (pIXtnSite, IEnumCls.ppi());
	if (FAILED(hr))	return hr;

// Rücksetzen der AktionsFolge
	ISeq -> Reset();

// hinzufügen der einzelnen Aktionen
	for (int i = 0; i < iCnt; i++) {
		hr = AddPropertyAction (ISeq, IEnumCls, pcbActs[i]);
		if (FAILED(hr) && ReportAddError (pcbActs[i])) 
			return hr;
	}

	*ppISeq = ISeq.detach();	

return NOERROR;
}


// Konstruktor/Destruktor/Initialisierung -------------------------------------
CPropertySequence *CPropertySequence :: CreateInstance (void)
{
	try {
	CPropertySequence *pSeq = new CPropertySequence();

		if (NULL == pSeq || !pSeq -> FInit()) {
			DELETE(pSeq);
			return NULL;
		}
		pSeq -> AddRef();
		return pSeq;
	} catch (...) {
		return NULL;
	}
}

CPropertySequence :: CPropertySequence (void)
{
	m_dwRefCnt = 0;
}

CPropertySequence :: ~CPropertySequence (void)
{
}

bool CPropertySequence :: FInit (void)
{
	return true;
}

// *** IUnknown methods -------------------------------------------------------
STDMETHODIMP CPropertySequence :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	*ppvObj = NULL;
	if (riid == IID_IUnknown || riid == IID_IPropertyActionSequence)
		*ppvObj = this;

	if (*ppvObj) {
		LPUNKNOWN(*ppvObj) -> AddRef();
		return NOERROR;
	}

return ResultFromScode (E_NOINTERFACE);
}

STDMETHODIMP_ (ULONG) CPropertySequence :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_ (ULONG) CPropertySequence :: Release (void)
{
	TX_ASSERT(m_dwRefCnt > 0);

	if (--m_dwRefCnt == 0) {
		delete this;
		return 0L;
	}

return m_dwRefCnt;
}


// *** IPropertyActionSequence methods ----------------------------------------
//
// Rücksetzen des internen Status. Sollte am Anfang einer Aktion gerufen werden,
// insbesondere, wenn das Objekt mehrfach benutzt wird.
//
STDMETHODIMP CPropertySequence :: Reset (void)
{
	m_Actions.erase();
	return NOERROR;
}

//
// Fügt jeweils eine auszuführende Aktion zu der internen Liste hinzu. Die 
// Reihenfolge, in der die Aktionen hinzugefügt werden muß dabei der Reihenfolge
// der auszuführenden Aktionen entsprechen.
//
STDMETHODIMP CPropertySequence :: AddAction (IPropertyAction *pIAct)
{
	try {
		m_Actions.push_back (WPropertyAction(pIAct));
		return NOERROR;
	} catch (...) {
		TX_ASSERT(false);
		return ResultFromScode (E_FAIL);
	}
}

STDMETHODIMP CPropertySequence :: AddActionByName (LPCSTR pcPropName)
{
	return ResultFromScode (E_NOTIMPL);
}

// Callback-Funktion, die von den IPropertyActions gerufen wird, um ihre
// PropertyPages in unseren Dialog reinzuhängen
bool __stdcall AddConfigPropertyPage (HPROPSHEETPAGE hPage, LPARAM lParam)
{
	return UINT_MAX != ((CPropertySheet *)lParam) -> AddPage (hPage);
}

// Besorgen der Flags von einer PropertyAction. Diese geben Aufschluß über 
// die Möglichkeiten und den notwendigen Umgang mit dieser PropertyAction
static HRESULT GetFlags (IPropertyAction *pAct, DWORD *pdwFlags)
{
WClassProperty IProp = pAct;
HRESULT hr = GetLastHRESULT();

	if (FAILED(hr)) return hr;
	hr = IProp -> GetPropInfo (NULL, 0, pdwFlags);

return hr;
}

//
// Führt die bis hierhin über 'AddAction' hinzugefügten Aktionen aus, indem
// evtl. ein KonfigurationsDialog angezeigt wird (in dem die Aktionen ihre
// PropertyPages einhängen können) - hierfür der Parameter hParent, und an-
// schließend nacheinander die einzelnen Aktionen gerufen werden. Der ersten
// dieser Aktionen wird dabei pIEnum übergeben (als Objekt-Startmenge). Die 
// Ausgabe einer Aktion wird dabei als Eingabe für die jeweils nächste Aktion 
// verwendet. Erzeugt eine Aktion mehrere Objektmengen (s. Flags), dann wird 
// die jeweils nächste Aktion entsprechend oft gerufen.
//
STDMETHODIMP CPropertySequence :: DoActions (
		HWND hParent, IProgressIndicator *pIStatus, 
		IDataObject *pIData, IDataObject **ppResult)
{
// wenn keine Actions gegeben sind, dann gleich wieder raus
	if (0 == m_Actions.size()) 
		return ResultFromScode (E_UNEXPECTED);

// Fenster (CPropertySheet) erzeugen
UINT uiCntA = 0;
DWORD dwAddPageFlags = ADDPAGES_FIRSTPAGE;
Window wndP (hParent);		// Parent-Fenster

	{
	CPropertySheet CfgDlg (NULL, &wndP, PSH_WIZARD);

		{
		CEierUhr Wait (&wndP);

			for (CActionList::iterator it = m_Actions.begin(); 
			     it != m_Actions.end(); it++) 
			{
			UINT uiCnt = 0;
		
				{	// wenn letzte PropertyAction, dann Flags richten
				CActionList::iterator iNext = it;

					if (++iNext == m_Actions.end())	
						dwAddPageFlags |= ADDPAGES_LASTPAGE;
				}
				if (it != m_Actions.begin())	// wenn nicht Erste, ebenfalls
					dwAddPageFlags &= ~ADDPAGES_FIRSTPAGE;

			// PropertyAction auffordern, ihre ConfigPages hinzuzufügen
				(*it) -> AddConfigPages (AddConfigPropertyPage, (LPARAM)&CfgDlg, 
							 dwAddPageFlags, &uiCnt);
				uiCntA += uiCnt;
			}
		} // end of CEierUhr

		if (0 != uiCntA) {	// Fenster anzeigen und Config vornehmen
			CfgDlg.Show (Centre);
			if (0 == CfgDlg.Result())
				return ResultFromScode (E_UNEXPECTED);	// abgebrochen
		}
	} // end of CfgDlg

// jetzt eigentliche Aktionen ausführen
DWORD dwFlags = PROPCAPS_NONE;

	try {
	CEierUhr Wait (&wndP);
	CActionList::iterator itr = m_Actions.begin();
	WPropertyAction ICurrAct (*itr);
	WDataObject IDataObj (pIData);

	// die erste Action bekommt genau ein DoAction
	HRESULT hrC = ICurrAct -> BeginAction (pIStatus);

		if (!IMPL_AND_FAILED(hrC))
			hrC = ICurrAct -> DoAction (IDataObj, 0L);
		if (IMPL_AND_FAILED(hrC)) throw hrC;

	// die weiteren Aktionen können mehrere Listen erzeugen
		while (++itr != m_Actions.end()) {
		WPropertyAction INextAct (*itr);
		HRESULT hrN = INextAct -> BeginAction (pIStatus);

			if (IMPL_AND_FAILED(hrN)) 
				throw hrN;	// wirklicher Fehler
			do {
				hrC = ICurrAct -> EndAction (0L, IDataObj.ppi());
				if (IMPL_AND_FAILED(hrC)) throw hrC;
			
				if (!IDataObj) 
					break;	// ok fertig

				hrN = INextAct -> DoAction (IDataObj, 0L);
				if (IMPL_AND_FAILED(hrN)) throw hrN;

			} while (S_FALSE == GetScode(hrC));

			ICurrAct = INextAct;	// der nächste ist jetzt der aktuelle
		}

	// der letzte Aktion bekommt ein EndAction
		hrC = ICurrAct -> EndAction (0L, IDataObj.ppi());
		if (IMPL_AND_FAILED(hrC)) throw hrC;

	// die ErgebnisListe an Aufrufer liefern
		if (ppResult) {
			*ppResult = IDataObj.detach();
		} 

	} catch (HRESULT hr) {
		return hr;
	}

return NOERROR;
}

