// Verwaltung einer Abfolge von IPropertyActions ------------------------------
// File: PROPSEQ.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <eieruhr.hxx>

#include <xtsnguid.h>
#include <statguid.h>
#include <funcs03.h>

#include "propseq.hxx"
#include "selidprp.hxx"		// PropertyAction's
// #include "modidprp.hxx"
// #include "selobwnd.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Min-Funktion, da Macro aus stdlib offensichtlich überladen ist
template<class T>
inline T tmin (T a, T b) { return (a > b) ? b : a; }

///////////////////////////////////////////////////////////////////////////////
// Name dieses Modules 
extern char g_pDLLName[];
extern "C" HWND __hWndM;

///////////////////////////////////////////////////////////////////////////////
// benötigte Interface-Wrapper 
DefineSmartInterface(DataObject);
DefineSmartInterface(ObjectProps);
DefineSmartInterface(ClassProperty);
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(EnumClassProps);
DefineSmartInterface(PersistStream);
DefineSmartInterface(PersistStreamInit);

///////////////////////////////////////////////////////////////////////////////
// lokal verwendete Funktionen 
inline bool IMPL_AND_FAILED (HRESULT hr)
{
	return (FAILED(hr)&&!(E_NOTIMPL==GetScode(hr)));
}

///////////////////////////////////////////////////////////////////////////////
// Erzeugen einer Instanz dieses Objektes 
HRESULT PActCreateInstance (LPCSTR pcDesc, REFIID riid, LPVOID *ppvObj)
{
IPropertyActionSequence *pISeq = NULL;
HRESULT hr = CPropertySequence::_CreatorClass::CreateInstance (NULL, IID_IPropertyActionSequence, (LPVOID *)&pISeq);

	if (FAILED(hr)) return hr;

	pISeq -> SetDescription (pcDesc);

	hr = pISeq -> QueryInterface (riid, ppvObj);
	pISeq -> Release();

return hr;
}

///////////////////////////////////////////////////////////////////////////////
// sonstige HelperFunktionen 

// Liefert Enumerator mit allen registrierten KlassenEigenschaften ------------
HRESULT GetEnumClassProps (IEnumClassProps **ppIEnum)
{
// alle Objekt- und sonstigen Eigenschaften von TRiAS besorgen
WObjectProps IProps;
HRESULT hr = DEX_GetObjectProps (IProps.ppi());

	if (FAILED(hr)) return hr;

	hr = IProps -> OnNewReferenceClass (NULL);	// initialisieren 
	if (SUCCEEDED(hr))
		hr = IProps -> EnumClassProps (ppIEnum);

return hr;
}

// Fehler beim Erzeugen einer PropertyAction: Fehler melden und weiteres ------
// Vorgehen abfragen
static bool ReportAddError (LPCSTR pcName)
{
ResourceFile RF (g_pDLLName);
ResString resCap (ResID (IDS_GENERRORCAP, &RF), 64);
ResString resText (ResID (IDS_ADDERROR, &RF), 64);
ResString resQuery (ResID (IDS_QUERYCONTINUE, &RF), 64);
char cbBuffer[256];

	wsprintf (cbBuffer, resText, pcName);

string str = cbBuffer;

	str += resQuery;
	if (IDYES == MessageBox (__hWndM, str.c_str(), resCap, MB_ICONEXCLAMATION|MB_YESNO))
		return false;	// weitermachen

return true;	// Abbrechen und nicht weitermachen
}

// Fügt eine PropertyAction zur AktionsFolge hinzu ----------------------------
HRESULT AddPropertyAction (IPropertyActionSequence *pISeq, 
			   IEnumClassProps *pIEnumCls, LPCSTR pcName)
{
HRESULT	hr = NOERROR;

	try {
	// Suchen (und Finden) der ClassProperty über den Namen
	WClassProperty IClsP;
	
		hr = pIEnumCls -> FindByName (pcName, IClsP.ppi());
		if (FAILED(hr)) throw hr;

	// wir brauchen aber das IPropertyAction-Interface
	WPropertyAction IAct = IClsP;		// throws hr

		hr = pISeq -> AddAction (IAct);		// ...und hinzufügen

	} catch (HRESULT hr) {
		return hr;
	} 

return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Erzeugen und initialisieren einer PropertyActionSequence, welche die
// vorgegebenen PropertyActions enthält
HRESULT InitPropertyActionSequence (
	LPCSTR pcDesc, CALPCSTR *pcbActs, IPropertyActionSequence **ppISeq)
{
	*ppISeq = NULL;		// für alle Fälle

WPropertyActionSequence ISeq;
HRESULT hr = PActCreateInstance (pcDesc, IID_IPropertyActionSequence, ISeq.ppv());

	if (FAILED(hr)) return hr;

// aktivieren der gewünschten AktionsFolge
WEnumClassProps IEnumCls;
	
	hr = GetEnumClassProps (IEnumCls.ppi());
	if (FAILED(hr))	return hr;

// Rücksetzen der AktionsFolge
	try {
	WPersistStreamInit Init = ISeq;		// throws hr

		hr = Init -> InitNew();
		if (FAILED(hr)) throw hr;
	
	} catch (HRESULT hr) {
		return hr;
	}

// hinzufügen der einzelnen Aktionen
	for (ULONG i = 0; i < pcbActs -> cElems; i++) {
		hr = AddPropertyAction (ISeq, IEnumCls, pcbActs -> pElems[i]);
		if (FAILED(hr) && ReportAddError (pcbActs -> pElems[i])) 
			return hr;
	}

	*ppISeq = ISeq.detach();

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Ausführen einer Folge von PropertyActions
HRESULT RunPropertyActionSequence (
	HWND hWnd, LPCSTR pcDesc, CALPCSTR *pcbActs, IProgressIndicator *pIStatus,
	IDataObject *pIInData, IDataObject **ppIOutData)
{
WPropertyActionSequence ISeq;
HRESULT hr = InitPropertyActionSequence (pcDesc, pcbActs, ISeq.ppi());

	if (FAILED(hr)) return hr;

// durchführen der gewünschten Aktion
	return ISeq -> DoActions (hWnd, pIStatus, pIInData, ppIOutData);
}

///////////////////////////////////////////////////////////////////////////////
// Registrieren aller hier definierten PropertyActions
HRESULT RegisterPropertyActions (REGPROPACTPROC pFcnReg, DWORD dwData)
{
// Objekteigenschaften installieren
ResourceFile RF (g_pDLLName);
ResString resGroup (ResID(IDS_PROPGROUPNAME, &RF), 32);
IClassProperty *pIProp = NULL;
HRESULT hr = CSelIDPropAct::CreateInstance(&pIProp);

	if (SUCCEEDED(hr)) {
		pFcnReg (pIProp, resGroup, dwData);		// Fehler ist nicht fatal
		pIProp -> Release();
	}
/*
	pIProp = CModIDPropAct::CreateInstance();
	if (NULL != pIProp) {
		pFcnReg (pIProp, resGroup, dwData);		// Fehler ist nicht fatal
		pIProp -> Release();
	}				

	pIProp = CSelObjWndPropAct::CreateInstance();
	if (NULL != pIProp) {
		pFcnReg (pIProp, resGroup, dwData);		// Fehler ist nicht fatal
		pIProp -> Release();
	}				

	pProp = CClsfyPropAct::CreateInstance (m_pXtnSite);
	if (NULL != pProp) {
		pProps -> AddPropertyFunction (pProp);	// Fehler ist nicht fatal
		pProp -> Release();
	}				

	pProp = CGenKomplexObj::CreateInstance (m_pXtnSite);
	if (NULL != pProp) {
		pProps -> AddPropertyFunction (pProp);	// Fehler ist nicht fatal
		pProp -> Release();
	}				

	pIProp = CDestObjWndPropAct::CreateInstance();
	if (NULL != pIProp) {
		pFcnReg (pIProp, resGroup, dwData);		// Fehler ist nicht fatal
		pIProp -> Release();
	}				
*/
return NOERROR;
}


///////////////////////////////////////////////////////////////////////////////
// CPropertySequence: InterfaceImplementationen
///////////////////////////////////////////////////////////////////////////////

CPropertySequence::CPropertySequence (void)
{
	m_fIsDirty = false;
	m_fIsInitialized = false;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyActionSequence methods 
STDMETHODIMP CPropertySequence::SetDescription (LPCSTR pcDesc)
{
	if (NULL == pcDesc) return E_POINTER;
	
	m_strDesc = pcDesc;
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
		m_fIsDirty = true;

	} catch (...) {
		TX_ASSERT(false);
		return E_FAIL;
	}

return NOERROR;
}

STDMETHODIMP CPropertySequence :: AddActionByName (LPCSTR pcPropName)
{
	m_fIsDirty = true;
	return E_NOTIMPL;
}

// Callback-Funktion, die von den IPropertyActions gerufen wird, um ihre
// PropertyPages in unseren Dialog reinzuhängen
bool __stdcall AddConfigPropertyPage (HPROPSHEETPAGE hPage, LPARAM lParam)
{
	return UINT_MAX != ((CPropertySheet *)lParam) -> AddPage (hPage);
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
STDMETHODIMP CPropertySequence::DoActions (
		HWND hParent, IProgressIndicator *pIStatus, 
		IDataObject *pIData, IDataObject **ppResult)
{
// wenn keine Actions gegeben sind, dann gleich wieder raus
	if (0 == m_Actions.size()) 
		return E_UNEXPECTED;

// Fenster (CPropertySheet) erzeugen
UINT uiCntA = 0;			// Gesamtanzahl der zu erwartenden Pages
DWORD dwAddPageFlags = ADDPAGES_FIRSTPAGE|ADDPAGES_LASTPAGE;
Window wndP (hParent);		// Parent-Fenster

	{
	CPropertySheet CfgDlg (NULL, &wndP, PSH_WIZARD);

		{
		CEierUhr Wait (&wndP);
		LPCSTR pcDesc = (m_strDesc.length() > 0) ? m_strDesc.c_str() : NULL;
		HRESULT hr = AddConfigPages (AddConfigPropertyPage, (LPARAM)&CfgDlg, 
									 dwAddPageFlags, pcDesc, &uiCntA);

		// im Vorfeld schon mal die Ausgangsdaten vorbeischicken
			if (SUCCEEDED(hr)) PreConfigPages (pIData);
		} // end of CEierUhr

		if (0 != uiCntA) {	// Fenster anzeigen und Config vornehmen
			CfgDlg.Show (Centre);
			if (0 == CfgDlg.Result())
				return E_UNEXPECTED;	// abgebrochen
		}
	} // end of CfgDlg

// jetzt eigentliche Aktionen ausführen
DWORD dwFlags = PROPCAPS_NONE;

	try {
	CEierUhr Wait (&wndP);
	HRESULT hr = BeginAction (pIStatus);
	WDataObject IDataObj (pIData);

		if (!IMPL_AND_FAILED(hr))
			hr = DoAction (IDataObj, 0L);
		if (IMPL_AND_FAILED(hr)) throw hr;
		
	// die letzte Aktion bekommt ein EndAction
		hr = EndAction (0L, IDataObj.ppi());
		if (IMPL_AND_FAILED(hr)) throw hr;

	// die ErgebnisListe an Aufrufer liefern
		if (ppResult) *ppResult = IDataObj.detach();

	// Flags der gesamten AktionsFolge geben lassen
		GetPropInfo (NULL, 0, &dwFlags);

	} catch (HRESULT hr) {
		return hr;
	}
/*
	CActionList::iterator itr = m_Actions.begin();
	WPropertyAction ICurrAct (*itr);
	WDataObject IDataObj (pIData);

		{	// Flags der 1. PropertyAction aufsammeln
		WClassProperty IProp = ICurrAct;	// throws hr

			IProp -> GetPropInfo (NULL, 0, &dwFlags);
		}

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

			{	// Flags aufsammeln
			WClassProperty IProp = ICurrAct;	// throws hr
			DWORD dw = 0;

				if (SUCCEEDED(IProp -> GetPropInfo (NULL, 0, &dw)))
					dwFlags |= dw;
			}
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
*/
// evtl. neuzeichnen, wenn eine der Actions das verlangt hat
	if (dwFlags & PROPCAPS_ACTION_MUSTREPAINTLEGEND) {
		DEX_RefreshLegend();
		DEX_RepaintLegend();
	}
	if (dwFlags & PROPCAPS_ACTION_MUSTREPAINT)
		DEX_RePaint();

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods
STDMETHODIMP CPropertySequence::AddConfigPages (
		LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, DWORD dwAddPageFlags, 
		LPCSTR pcDesc, UINT *puiCnt)
{
UINT uiCntA = 0;

	for (CActionList::iterator it = m_Actions.begin(); 
		 it != m_Actions.end(); it++) 
	{
	UINT uiCnt = 0;
	DWORD dwFlags = dwAddPageFlags & ~(ADDPAGES_FIRSTPAGE|ADDPAGES_LASTPAGE);

		{	// wenn letzte PropertyAction, dann Flags richten
		CActionList::iterator itNext = it;

			if (++itNext == m_Actions.end() && dwAddPageFlags & ADDPAGES_LASTPAGE)
				dwFlags |= ADDPAGES_LASTPAGE;
		}
	// wenn Erste, ebenfalls
		if (0 == uiCntA && dwAddPageFlags & ADDPAGES_FIRSTPAGE)
			dwFlags |= ADDPAGES_FIRSTPAGE;

	// PropertyAction auffordern, ihre ConfigPages hinzuzufügen
		(*it) -> AddConfigPages (lpfnAddPage, lParam, dwFlags, pcDesc, &uiCnt);
		uiCntA += uiCnt;
	}

	if (NULL != puiCnt)		// Gesamtanzahl der installierten Pages liefer
		*puiCnt = uiCntA;

return NOERROR;
}

// Im Vorfeld schon mal die Ausgangsdaten vorbeigeschickt bekommen ------------
STDMETHODIMP CPropertySequence::PreConfigPages (IDataObject *pIDataObject)
{
	for (CActionList::iterator it = m_Actions.begin(); 
		 it != m_Actions.end(); it++) 
	{
	HRESULT hr = (*it) -> PreConfigPages (pIDataObject);

		if (IMPL_AND_FAILED(hr)) return hr;
	}

return NOERROR;
}

// Beginnen der gespeicherten AktionsFolge, dazu der ersten Aktion ein 
// BeginAction vorbeischicken und die internen Variablen initialisieren
STDMETHODIMP CPropertySequence::BeginAction (IProgressIndicator *pIProgInd)
{
HRESULT hr = NOERROR;

	try {
		m_itr = m_Actions.begin();
		if (m_itr == m_Actions.end())
			return E_UNEXPECTED;

		m_ICurrAct = *m_itr;

	// die erste Action bekommt erstmal ein BeginAction
		m_IProgInd = pIProgInd;
		hr = m_ICurrAct -> BeginAction (pIProgInd);

	} catch (HRESULT hr) {
		return hr;
	}

return hr;
}

// Hier geschieht die eigentliche Arbeit. Die gesamte AktionsFolge wird 
// erledigt.
STDMETHODIMP CPropertySequence::DoAction (IDataObject *pDataObj, DWORD)
{
	try {
	WDataObject IDataObj (pDataObj);
	HRESULT	hrC = m_ICurrAct -> DoAction (IDataObj, 0L);

		if (IMPL_AND_FAILED(hrC)) throw hrC;

	// die weiteren Aktionen können mehrere Listen erzeugen
		while (++m_itr != m_Actions.end()) {
		WPropertyAction INextAct (*m_itr);
		HRESULT hrN = INextAct -> BeginAction (m_IProgInd);

			if (IMPL_AND_FAILED(hrN)) 
				throw hrN;	// wirklicher Fehler

			do {
				hrC = m_ICurrAct -> EndAction (0L, IDataObj.ppi());
				if (IMPL_AND_FAILED(hrC)) throw hrC;
			
				if (!IDataObj) 
					break;	// ok fertig

				hrN = INextAct -> DoAction (IDataObj, 0L);
				if (IMPL_AND_FAILED(hrN)) throw hrN;

			} while (S_FALSE == GetScode(hrC));

			m_ICurrAct = INextAct;	// der nächste ist jetzt der aktuelle
		}
	
	} catch (HRESULT hr) {
		return hr;
	}

return NOERROR;
}

// Zum Abschluß kriegt die letzte Aktion der Aktionsfolge noch ein EndAction.
STDMETHODIMP CPropertySequence::EndAction (DWORD, IDataObject **ppOutObj)
{
	try {
	// der letzte Aktion bekommt ein EndAction
	WDataObject IDataObj;
	HRESULT hrC = m_ICurrAct -> EndAction (0L, IDataObj.ppi());

		if (IMPL_AND_FAILED(hrC)) throw hrC;

	// die ErgebnisListe an Aufrufer liefern
		if (ppOutObj) 
			*ppOutObj = IDataObj.detach();

		m_ICurrAct.Assign(NULL);		// Freigeben der InterfacePointers
		m_IProgInd.Assign(NULL);

	} catch (HRESULT hr) {
		m_ICurrAct.Assign(NULL);
		m_IProgInd.Assign(NULL);
		return hr;
	}

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CPropertySequence::GetClassID (LPCLSID lpClassID)
{
	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_PropertyActionSequence;
	return NOERROR;
}

// IPersistStreamInit methods
STDMETHODIMP CPropertySequence::IsDirty (void)
{
	return m_fIsDirty;
}

STDMETHODIMP CPropertySequence::Load (LPSTREAM pStm)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

// alles wieder einlesen: zuerst Version überprüfen
DWORD dwVersion = 0L;
HRESULT hr = pStm -> Read (&dwVersion, sizeof(dwVersion), NULL);

	if (S_OK != hr) return hr;
	if (PROPERTYACTION_FORMATVERSION < dwVersion)
		return STG_E_OLDDLL;	// File was written with a newer version

// BeschreibungsString einlesen
ULONG ulCount = 0;

	hr = pStm -> Read (&ulCount, sizeof(ulCount), NULL);
	if (S_OK != hr) return hr;

	try {
		m_strDesc.resize (ulCount+1);
		hr = pStm -> Read ((void *)m_strDesc.c_str(), ulCount, NULL);
		if (S_OK != hr) return hr;

	} catch (...) {
		return E_OUTOFMEMORY;
	}
	
// Anzahl der Aktionen lesen
	hr = pStm -> Read (&ulCount, sizeof(ulCount), NULL);
	if (S_OK != hr) return hr;

// Aktionen instantiieren
	for (ULONG ul = 0; ul < ulCount; ul++) {
	WPropertyAction PropAct;

		hr = OleLoadFromStream (pStm, IID_IPropertyAction, PropAct.ppv());
		if (SUCCEEDED(hr))
			hr = AddAction (PropAct);
		if (FAILED(hr))
			return hr;
	}

// ok, fertig initialisiert
	m_fIsInitialized = true;
	m_fIsDirty = false;

return NOERROR;
}

STDMETHODIMP CPropertySequence::Save (LPSTREAM pStm, BOOL fClearDirty)
{
// Version des Formates schreiben
DWORD dwVersion = PROPERTYACTION_FORMATVERSION;
HRESULT hr = pStm -> Write (&dwVersion, sizeof(dwVersion), NULL);

	if (FAILED(hr)) return hr;
	
// Schreiben des BeschreibungsStrings
LONG ulCount = m_strDesc.length() +1;	// Länge des Namens

	hr = pStm -> Write (&ulCount, sizeof(ulCount), NULL);
	if (FAILED(hr)) return hr;
	hr = pStm -> Write (m_strDesc.c_str(), ulCount, NULL);
	if (FAILED(hr)) return hr;

// Schreiben der AktionsFolge
	ulCount = m_Actions.size();	// Anzahl der Aktionen
	hr = pStm -> Write (&ulCount, sizeof(ulCount), NULL);
	if (FAILED(hr)) return hr;

	for (CActionList::iterator it = m_Actions.begin(); 
		 it != m_Actions.end(); it++) 
	{
		try {
		WPersistStream StmInit (*it);		// throws hr

			hr = OleSaveToStream (StmInit, pStm);
			if (FAILED(hr)) throw hr;

		} catch (HRESULT hr) {
			if (E_NOINTERFACE != hr) 
				return hr;		// sonstiger Fehler, abbrechen
		}
	}

// DirtyFlag entsprechend Anforderungen behandeln
	if (fClearDirty)
		m_fIsDirty = false;

return NOERROR;
}

STDMETHODIMP CPropertySequence::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) return E_POINTER;

ULONG ulSize = sizeof(DWORD) + 2*sizeof(ULONG) + m_strDesc.length()+1;
 
	for (CActionList::iterator it = m_Actions.begin(); 
		 it != m_Actions.end(); it++) 
	{
		try {
		WPersistStream StmInit (*it);		// throws hr
		ULARGE_INTEGER uli;

			ULISet32 (uli, 0L);

		HRESULT hr = StmInit -> GetSizeMax (&uli);

			if (FAILED(hr)) throw hr;
			ulSize += uli.LowPart;

		} catch (HRESULT hr) {
			if (E_NOINTERFACE != hr) 
				return hr;		// sonstiger Fehler, abbrechen
		}
	}

	ULISet32(*pcbSize, ulSize);

return NOERROR;
}

STDMETHODIMP CPropertySequence::InitNew (void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_Actions.erase();
	m_fIsInitialized = true;
	m_fIsDirty = false;
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions
STDMETHODIMP CPropertySequence::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Namen der Property kopieren
		ULONG ulLen = tmin ((size_t)(wLen-1), m_strDesc.length());

			strncpy (pBuffer, m_strDesc.c_str(), ulLen);
			pBuffer[ulLen] = '\0';
		}
	
	// wenn gewünscht, Flags aufsammeln und übergeben
		if (pdwFlags) {
		DWORD dwFlags = 0;

			for (CActionList::iterator it = m_Actions.begin(); 
				 it != m_Actions.end(); it++) 
			{
			WClassProperty IProp = (*it);	// throws hr
			DWORD dw = 0;

				if (SUCCEEDED(IProp -> GetPropInfo (NULL, 0, &dw)))
					dwFlags |= dw;
			}

			*pdwFlags = dwFlags;
		}

	} catch (HRESULT hr) {
		return hr;
	} catch (...) {
		return E_FAIL;
	}

return NOERROR;
}

STDMETHODIMP CPropertySequence::Reset (void)
{
	return E_NOTIMPL;
}

STDMETHODIMP_(ULONG) CPropertySequence::Count (void)
{
	return 0L;
}

STDMETHODIMP CPropertySequence::HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Beschreibung übergeben
		ResourceFile RF (g_pDLLName);
		ResString resHelp (ResID (IDS_HELPDESC_PROPSEQUENCE, &RF), 128);
		ULONG ulLen = tmin ((size_t)(wLen-1), strlen(resHelp));

			strncpy (pBuffer, resHelp, ulLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return E_OUTOFMEMORY;
	}

// HelpFileInfo übergeben
	if (pHelpFile) pHelpFile[0] = '\0';
	if (pulHelpCtx) *pulHelpCtx = 0L;
	
return NOERROR;
}

STDMETHODIMP CPropertySequence::Eval (IEnumLONG *pEnumObj, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	return E_NOTIMPL;
}

STDMETHODIMP CPropertySequence::Cumulation(LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	return E_NOTIMPL;
}

