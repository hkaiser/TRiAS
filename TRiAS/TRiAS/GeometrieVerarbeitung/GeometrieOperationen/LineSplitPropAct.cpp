// Definitionen: PropertyAction für Splitten von Linienobjekten
// File: LineSplitPropAct.cpp

#include "ObjOperP.hxx"

#include <Com/MkHelper.h>

#include "LineSplitPropAct.h"
#include "MonikerHelper.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////
// externe Variablen
extern ResourceFile* pRF;

///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor wird durch AddAction "TRiASEx.LinesSplitting.1" gerufen
CLineSplitPropAct::CLineSplitPropAct (void)
{
// ggf. Erweiterung ObjOper.ext laden
	m_hDex = NULL;
	if (NULL == g_pTE) {
	LOADEXTENSIONEX le;

		memset (&le, 0, sizeof (LOADEXTENSIONEX));
		le.m_pDesc = 0;
		le.m_pName = "TRiAS.Operationen.1";
		le.m_iMode = LEFullLoad;
		le.m_fGlobal = TRUE;		
		m_hDex = DEX_ExternalLoadExtensionEx (le);
		_ASSERTE(m_hDex != 0);
	}

// Member initialisieren
	m_pLineSplitDlg = 0;
	m_bIsDirty = false;			// Dialogparameter wurden (noch) nicht verändert
	m_bIsInitialized = false;	// Page ist noch nicht initialisiert
	m_bHasInitData = false;		// (noch) keine Initialisierungsdaten für den Dialog von Load()
								// bereitgestellt bzw. schon an diesen weitergereicht
	try
	{
	ResString resPropInfo (ResID (IDS_SPLITCAPT, pRF), 30);

		m_sDesc = resPropInfo;
	}
	catch (...)
	{
		_ASSERTE (false);
	}
}


// --------------------------------------------------------------------------------------------
CLineSplitPropAct::~CLineSplitPropAct (void)
{
	DELETE_OBJ (m_pLineSplitDlg);
}


// --------------------------------------------------------------------------------------------
void CLineSplitPropAct::FinalRelease (void)
{
	if (m_hDex)
	{
	//	Erweiterung ObjOper.ext entladen
	LOADEXTENSIONEX le;

		memset (&le, 0, sizeof (LOADEXTENSIONEX));
		le.m_pDesc = NULL;
		le.m_pName = "TRiAS.Operationen.1";
		le.m_iMode = LENoLoad;
		le.m_fGlobal = TRUE;		
		DEX_ExternalUnLoadExtensionEx (le);
		m_hDex = 0;
	}

	m_wOperOptions.Assign (NULL);
	m_mkOperOptions.Assign(NULL);
}



///////////////////////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions
// kürzere Beschreibung (Standardtext oder mit SetPropInfo() gesetzter Text wird in pBuffer
// (der Länge wLen) zurückgegeben
STDMETHODIMP CLineSplitPropAct::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	try
	{
		if (NULL != pBuffer && wLen > 0)
		{
		// Namen der Property kopieren
		ULONG ulLen = min ((size_t)(wLen-1), m_sDesc.length());

			strncpy (pBuffer, m_sDesc.c_str(), ulLen);
			pBuffer[ulLen] = '\0';
		}
	}
	catch (...)
	{
		return E_FAIL;
	}

// wenn gewünscht, Flags übergeben
	if (pdwFlags) 
		*pdwFlags = PROPCAPS_ACTION_SINK|PROPCAPS_ACTION_SOURCE_MULTI;
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// längere Beschreibung wird in pBuffer (der Länge wLen) zurückgegeben
STDMETHODIMP CLineSplitPropAct::HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile,
										  ULONG *pulHelpCtx)
{
	try
	{
		if (NULL != pBuffer && wLen > 0)
		{
		// Beschreibung übergeben
		ResString resHelp (ResID (IDS_HELPINFO_LINESPLIT, pRF), 128);
		ULONG ulLen = min (size_t(wLen-1), strlen(resHelp));

			strncpy (pBuffer, resHelp, ulLen);
			pBuffer[ulLen] = '\0';
		}
	}
	catch (...)
	{
		return E_FAIL;
	}

// HelpFileInfo übergeben
	if (pHelpFile) pHelpFile[0] = '\0';
	if (pulHelpCtx) *pulHelpCtx = 0L;
	return S_OK;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods
// PropertyPages einhängen
// diese Stelle wird bei DoActions() erreicht
STDMETHODIMP CLineSplitPropAct::AddConfigPages (LPFNADDPROPSHEETPAGE lpfnAddPage,
												LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{
char cbCaption[_MAX_PATH];

	try
	{
		if (NULL != pcDesc)		// Caption ist gegeben
			strcpy (cbCaption, pcDesc);
		else	// von zugehöriger ClassProperty unseren Namen besorgen
			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

		// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
		DELETE_OBJ (m_pLineSplitDlg);	// evtl. vorherigen freigeben
		m_pLineSplitDlg = CLinesSplittingDlg::CreateInstance (ResID(IDD_LINESPLITPROPACT, pRF),
														   cbCaption, this, m_caSelInfo, *pRF);
		if (NULL == m_pLineSplitDlg) _com_issue_error (E_OUTOFMEMORY);

		if (!IsNoShow())
		{
		// Seite hinzufügen, wenn selbige angezeigt werden soll
		HPROPSHEETPAGE hPSP = m_pLineSplitDlg -> CreatePage();

			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_UNEXPECTED;
		}

		// Initialisierungsdaten für den Dialog wurden von Load() bereitgestellt, konnten aber
		// noch nicht an diesen weitergereicht werden
		if (m_bHasInitData) {
		// Initialisierungsdaten jetzt an den Dialog weiterreichen
		HRESULT	hr = m_pLineSplitDlg->SetSelectedInfo (&m_caSelInfo, IsNoShow());

			if (FAILED(hr)) _com_issue_error(hr);
		}

		if (NULL != puiCnt) 
			*puiCnt = IsNoShow() ? 0 : 1;	// "1" ist die Anzahl der einzuhängenden Pages

	}
	catch (_com_error& e)
	{
		DELETE_OBJ (m_pLineSplitDlg);
		if (puiCnt) *puiCnt = 0;
		return _COM_ERROR (e);
	}

	return S_OK;

} // AddConfigPages


// --------------------------------------------------------------------------------------------
// Info, ob es sich um die erste bzw. letzte Seite handelt, damit in Abhängigkeit davon die
// Buttons modifiziert werden können
STDMETHODIMP CLineSplitPropAct::PreConfigPages (IDataObject* pIDataObj, DWORD dwFlags)
{
	m_pLineSplitDlg->SetFlags (dwFlags);
	EnsureOptionsIF();

	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CLineSplitPropAct::BeginAction (IProgressIndicator* pIProgInd)
{
#if _TRiAS_VER < 0x0300
	m_hPr = 0;
#else
	COM_TRY
	{
	// Zieldatenquelle aus KontextObjekt herausfinden
	WPropertyActionSequence wSeq;
	WDataObject CtxDO;
	CComVariant vData;

		m_hPr = 0;

		THROW_FAILED_HRESULT (GetSite (IID_IPropertyActionSequence, wSeq.ppv()));
		THROW_FAILED_HRESULT (wSeq->GetSequenceContext (CtxDO.ppi()));
		if (SUCCEEDED (GetVariantData (CtxDO, &c_feDataSourceHandle, &vData)) &&
			SUCCEEDED (vData.ChangeType (VT_I4))) 
		{
			m_hPr = reinterpret_cast<HPROJECT>(V_I4(&vData));
		}
	}
	COM_CATCH;
#endif // _TRiAS_VER < 0x0300

	// Zustand des Dialogs retten (für evtl. späteres Save())
	m_pLineSplitDlg->GetSelectedInfo (&m_caSelInfo, m_bIsDirty);

	// Liste für Objekte, die an die PropertyPage übergeben werden, initialisieren
	m_InObjs.clear();				// Liste sicher leeren
	m_ObjsIter = m_InObjs.begin();	// auf Anfang stellen

	m_wEnumOutNotTouched.Assign(NULL);
	m_lPacket = 0;

	return S_OK;

} // BeginAction


// --------------------------------------------------------------------------------------------
STDMETHODIMP CLineSplitPropAct::DoAction (IDataObject* pDataObj, DWORD)
{
WEnumLONG wEnumObj;
HRESULT hr = GetEnumLONGData (pDataObj, (IEnum<LONG>**)(IEnumLONG**)wEnumObj.ppi());

	if (FAILED(hr)) return hr;

	// Enumerator (an PropertyPage übergebene Objekte) in Liste speichern
	m_InObjs.push_back (wEnumObj);		// Enumerator am Ende der Liste anfügen
	if (1 == m_InObjs.size())
		m_ObjsIter = m_InObjs.begin();	// Iterator zeigt auf das 1. Element der Liste

	if (m_caSelInfo.fReturnNotTouched)
		m_lPacket = 2 * m_InObjs.size();
	return hr;

} // DoAction


// --------------------------------------------------------------------------------------------
STDMETHODIMP CLineSplitPropAct::EndAction (DWORD, IDataObject** ppDataOut)
{
	*ppDataOut = 0;

HRESULT hr = S_OK;

	COM_TRY {
		if (m_wEnumOutNotTouched.IsValid()) {
		// einfach die nicht berühreten Objekte liefern
		WDataObject IDO (CLSID_DataTransferObject);

		// Ergebnisobjekte im DataObjekt IDO speichern
			THROW_FAILED_HRESULT (SetEnumLONGData (
				(IEnum<LONG>*)(IEnumLONG*)m_wEnumOutNotTouched, IDO));

			_ASSERTE(m_lPacket > 0);
			THROW_FAILED_HRESULT(SetPacketNumber(IDO, m_lPacket--));
			m_wEnumOutNotTouched.Assign(NULL);

		// Resultat setzen
			*ppDataOut = IDO.detach();
			if (m_ObjsIter != m_InObjs.end())	// es kommen noch weitere Daten
				hr = S_FALSE;
		}
		else {
			_ASSERTE(m_ObjsIter != m_InObjs.end());

		// nächste Objektmenge bearbeiten
		WEnumLONG wEnumInObj (*m_ObjsIter);	// die zu bearbeitenden Objekte
		WEnumLONG wEnumOutObj;				// Ergebnisobjekte der ausgewählten Operation
		WEnumLONG wEnumOutNotUsed;			// Ausgangsobjekte die nicht bearbeitet wurden

	//	ulong ulMinPos = 1;
	//	ulong ulMaxPos = wEnumInObj->Count();

	//		THROW_FAILED_HRESULT (m_wProgInd->Restart (ulMinPos, ulMaxPos, m_rgFlags));

		// Optionen abfragen
		DWORD dwOptions = 0x00;

			if (SUCCEEDED(EnsureOptionsIF())) {
				_ASSERTE(m_wOperOptions.IsValid());
				m_wOperOptions->GetOptions (&dwOptions);
			}

			// im Dialog ausgewählte Operation ausführen
			THROW_FAILED_HRESULT (m_pLineSplitDlg->ExecuteOperation (
				m_hPr, wEnumInObj, dwOptions, wEnumOutObj.ppi(), wEnumOutNotUsed.ppi()));

			m_ObjsIter++;
			if (wEnumOutObj.IsValid()) {
			// IDataObject abfragen
			WDataObject IDO (CLSID_DataTransferObject);

			// Ergebnisobjekte im DataObjekt IDO speichern
				THROW_FAILED_HRESULT (SetEnumLONGData (
					(IEnum<LONG>*)(IEnumLONG*)wEnumOutObj, IDO));
				
				if (m_caSelInfo.fReturnNotTouched) {
				// Paketnummer setzen
					_ASSERTE(m_lPacket > 0);
					THROW_FAILED_HRESULT(SetPacketNumber(IDO, m_lPacket--));
				}

			// Resultat setzen
				*ppDataOut = IDO.detach();

				if (0 == wEnumOutObj->Count()) {
				ResString resTitel (ResID (IDS_LONGCLASSNAME, pRF), 50);
				ResString resText (ResID (IDS_BOXTEXT5, pRF), 200);
		
					MessageBox (__hWndM, resText.Addr(), resTitel.Addr(),
								MB_ICONINFORMATION | MB_OK);
				}
				else if (m_caSelInfo.fReturnNotTouched) {
				// ggf. nicht benutzte Objekte speichern
					m_wEnumOutNotTouched = wEnumOutNotUsed;
					hr = S_FALSE;		// es kommen noch weitere Daten
				}
				else if (m_ObjsIter != m_InObjs.end())
					hr = S_FALSE;		// es kommen noch weitere Daten
			}
		}
			
	} COM_CATCH_OP(delete m_pLineSplitDlg);

	if (S_FALSE != hr) {
		DELETE_OBJ (m_pLineSplitDlg);		// es kommen keine Daten mehr
	}
	return hr;

} // EndAction


///////////////////////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CLineSplitPropAct::GetClassID (LPCLSID lpClassID)
{
	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_LineSplitPropAct;
	return S_OK;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit methods
// m_bIsDirty == true, wenn die Dialogparameter verändert wurden und somit Save() sinnvoll ist
STDMETHODIMP CLineSplitPropAct::IsDirty (void)
{
	return m_bIsDirty ? S_OK : S_FALSE;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CLineSplitPropAct::Load (LPSTREAM pStm)
{
	if (m_bIsInitialized)		// m_bIsInitialized == true, wenn Page schon durch InitNew()
		return E_UNEXPECTED;	// initialisiert wurde

// Daten einlesen
// zuerst Bezeichner einlesen
HRESULT hr = CPropertyAction::Load (pStm);

	if (FAILED(hr)) return hr;

// meine Versionsnummer und Signatur lesen und überprüfen
DWORD dwSignature = 0;
DWORD dwVersion = 0;

	RETURN_FAILED_HRESULT(pStm->Read (&dwSignature, sizeof(DWORD), NULL));
	if (LINESPLITPROPACT_SIGNATURE != dwSignature)
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(pStm->Read (&dwVersion, sizeof(DWORD), NULL));
	if ((dwVersion & ~MINOR_VERSION_MASK) > LINESPLITPROPACT_ACTVERSION)
		return STG_E_OLDDLL;	// File was written with a newer version

// dann selektierte Info der letzten Auswahl
	RETURN_FAILED_HRESULT (pStm->Read (&m_caSelInfo.dFuzzy, sizeof(double), NULL));
	RETURN_FAILED_HRESULT (pStm->Read (&m_caSelInfo.dDangle, sizeof(double), NULL));
	if (dwVersion >= LINESPLITPROPACT_VERSION_1_0_2) {
		RETURN_FAILED_HRESULT (pStm->Read (&m_caSelInfo.fForceTolerances, sizeof(BOOL), NULL));

		if (dwVersion >= LINESPLITPROPACT_VERSION_1_0_3) {
		// zusätzliche Flags einlesen
			RETURN_FAILED_HRESULT (pStm->Read (&m_caSelInfo.fReturnNotTouched, sizeof(BOOL), NULL));
			RETURN_FAILED_HRESULT (pStm->Read (&m_caSelInfo.fForceSelectObjClass, sizeof(BOOL), NULL));
		}

	// ggf. Moniker einlesen
	BOOL fHasMoniker = TRUE;

		RETURN_FAILED_HRESULT (pStm->Read (&fHasMoniker, sizeof(BOOL), NULL));
		if (fHasMoniker) {
			RETURN_FAILED_HRESULT (OleLoadFromStream(pStm, IID_IMoniker, m_mkOperOptions.ppv()));
		}
	}
	else {
		m_caSelInfo.fForceTolerances = FALSE;
		m_caSelInfo.fReturnNotTouched = FALSE;
		m_caSelInfo.fForceSelectObjClass = FALSE;
	}

	if (0 == m_pLineSplitDlg)
		// Initialisierungsdaten für den Dialog wurden zwar soeben von Load() bereitgestellt,
		// können hier aber noch nicht an diesen weitergereicht werden
		m_bHasInitData = true;
	else
		// Initialisierungsdaten an den Dialog weiterreichen
		m_pLineSplitDlg->SetSelectedInfo (&m_caSelInfo);
	
	m_bIsInitialized = true;	// Page wurde jetzt durch Load() initialisiert
	m_bIsDirty = false;			// Dialogparameter wurden (noch) nicht verändert
	return S_OK;

} // Load


// --------------------------------------------------------------------------------------------
// fClearDirty: Zustand im aktuellen Projekt und dessen Abspeicherung ist identisch (true) bzw.
//              stimmt nicht überein (false); letzterer Fall tritt bei SaveAs() auf
STDMETHODIMP CLineSplitPropAct::Save (LPSTREAM pStm, BOOL fClearDirty)
{
// Bezeichner wegschreiben
HRESULT hr = CPropertyAction::Save (pStm, fClearDirty);

	if (FAILED(hr)) return hr;

// Signatur und Version wegschreiben
DWORD dwSignature = LINESPLITPROPACT_SIGNATURE;
DWORD dwVersion = LINESPLITPROPACT_VERSION_1_0_3;

	RETURN_FAILED_HRESULT (pStm->Write (&dwSignature, sizeof(DWORD), NULL));
	RETURN_FAILED_HRESULT (pStm->Write (&dwVersion, sizeof(DWORD), NULL));

// dann selektierte Info der letzten Auswahl
	// nachfolgende if-Bedingung für den Fall, daß m_pLineSplitDlg-Seite "am Schluß" nicht oben
	// lag, also BeginAction() und damit auch GetSelectedInfo() nicht ausgeführt wurden
	if (m_pLineSplitDlg)
		m_pLineSplitDlg->GetSelectedInfo (&m_caSelInfo, m_bIsDirty);

	RETURN_FAILED_HRESULT (pStm->Write (&m_caSelInfo.dFuzzy, sizeof(double), NULL));
	RETURN_FAILED_HRESULT (pStm->Write (&m_caSelInfo.dDangle, sizeof(double), NULL));
	RETURN_FAILED_HRESULT (pStm->Write (&m_caSelInfo.fForceTolerances, sizeof(BOOL), NULL));
	RETURN_FAILED_HRESULT (pStm->Write (&m_caSelInfo.fReturnNotTouched, sizeof(BOOL), NULL));
	RETURN_FAILED_HRESULT (pStm->Write (&m_caSelInfo.fForceSelectObjClass, sizeof(BOOL), NULL));

	if (!m_mkOperOptions.IsValid() && m_wOperOptions.IsValid()) {
	// ggf. Moniker geben lassen
		RETURN_FAILED_HRESULT (MkGetMoniker(m_wOperOptions, 
			OLEGETMONIKER_FORCEASSIGN, OLEWHICHMK_OBJFULL, m_mkOperOptions.ppi()));
	}

// und Moniker wegschreiben
BOOL fHasMoniker;

	if (m_mkOperOptions.IsValid()) {
		fHasMoniker = TRUE;
		RETURN_FAILED_HRESULT (pStm->Write (&fHasMoniker, sizeof(BOOL), NULL));
		RETURN_FAILED_HRESULT (OleSaveToStream(WPersistStream(m_mkOperOptions), pStm));
	}
	else {
		fHasMoniker = FALSE;
		RETURN_FAILED_HRESULT (pStm->Write (&fHasMoniker, sizeof(BOOL), NULL));
	}

	if (fClearDirty) m_bIsDirty = false;
	return S_OK;

} // Save


// --------------------------------------------------------------------------------------------
// Bestimmen der benötigten Speichergröße für Save()
STDMETHODIMP CLineSplitPropAct::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) return E_POINTER;

ULARGE_INTEGER cbSize;
HRESULT hr = CPropertyAction::GetSizeMax (&cbSize);

	if (FAILED(hr)) return hr;

ULARGE_INTEGER liOwnSize;

	if (!m_mkOperOptions.IsValid()) {
	// ggf. Moniker geben lassen
		RETURN_FAILED_HRESULT (MkGetMoniker(m_wOperOptions, 
			OLEGETMONIKER_FORCEASSIGN, OLEWHICHMK_OBJFULL, m_mkOperOptions.ppi()));
	}
	RETURN_FAILED_HRESULT(WPersistStream(m_mkOperOptions) -> GetSizeMax(&liOwnSize));

	liOwnSize.QuadPart += 2 * sizeof(double) + 4 * sizeof(BOOL);
	liOwnSize.QuadPart += cbSize.QuadPart;
	*pcbSize = liOwnSize;
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CLineSplitPropAct::InitNew (void)
{
	if (m_bIsInitialized)		// m_bIsInitialized == true, wenn Page schon durch Load()
		return E_UNEXPECTED;	// initialisiert wurde

	m_caSelInfo.dFuzzy = 0.1;	// ???
	m_caSelInfo.dDangle = 0.05;	// ???
	m_caSelInfo.fForceTolerances = FALSE;
	m_caSelInfo.fReturnNotTouched = FALSE;
	m_caSelInfo.fForceSelectObjClass = FALSE;

	m_bIsInitialized = true;	// Page wurde jetzt durch InitNew() initialisiert
	m_bIsDirty = false;			// Dialogparameter wurden noch nicht verändert
	return S_OK;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
// mit pBuffer die standardmäßige kürzere Beschreibung überschreiben
STDMETHODIMP CLineSplitPropAct::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags)  
{
	if (NULL == pcBuffer) return E_POINTER;

	m_sDesc = pcBuffer;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ISetGeoOperatOptionsTarget
// Verbindung zur COptionsPropAct-Klasse über deren Interface IGetGeoOperatOptions herstellen
STDMETHODIMP CLineSplitPropAct::SetOperatOptionsSite (IGetGeoOperatOptions* pOperOptions)
{
	try
	{
		m_wOperOptions = pOperOptions;
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CLineSplitPropAct::SetDirty (bool bDirty) 
{ 
	m_bIsDirty = bDirty; 
}

/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
STDMETHODIMP CLineSplitPropAct::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyAction::Load (pBag, pLog));

	m_caSelInfo.dFuzzy = 0.1;	// ???
	m_caSelInfo.dDangle = 0.05;	// ???
	m_caSelInfo.fForceTolerances = FALSE;
	m_caSelInfo.fReturnNotTouched = FALSE;
	m_caSelInfo.fForceSelectObjClass = FALSE;

// sonstige Werte Analysieren

// ForceTolerances=
CComVariant vParam;
HRESULT hr = pBag -> Read (CComBSTR(L"ForceTolerances"), &vParam, pLog);

	if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_BOOL))) 
		m_caSelInfo.fForceTolerances = V_BOOL(&vParam) ? TRUE : FALSE;

// FuzzyTolerance=
CComVariant vFuzzy;

	hr = pBag -> Read (CComBSTR(L"FuzzyTolerance"), &vFuzzy, pLog);
	if (S_OK == hr && SUCCEEDED(vFuzzy.ChangeType (VT_R8))) 
		m_caSelInfo.dFuzzy = V_R8(&vFuzzy);

// DanglingTolerance=
CComVariant vDangle;

	hr = pBag -> Read (CComBSTR(L"DanglingTolerance"), &vDangle, pLog);
	if (S_OK == hr && SUCCEEDED(vDangle.ChangeType (VT_R8))) 
		m_caSelInfo.dDangle = V_R8(&vDangle);

// ReturnNotTouched=
CComVariant vNotTouched;

	hr = pBag -> Read (CComBSTR(L"ReturnNotTouched"), &vNotTouched, pLog);
	if (S_OK == hr && SUCCEEDED(vNotTouched.ChangeType (VT_BOOL))) 
		m_caSelInfo.fReturnNotTouched = V_BOOL(&vNotTouched) ? TRUE : FALSE;

// ForceSelectObjClass=
CComVariant vForceOC;

	hr = pBag -> Read (CComBSTR(L"ForceSelectObjClass"), &vForceOC, pLog);
	if (S_OK == hr && SUCCEEDED(vForceOC.ChangeType (VT_BOOL))) 
		m_caSelInfo.fForceSelectObjClass = V_BOOL(&vForceOC) ? TRUE : FALSE;

	m_bHasInitData = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Sicherstellen des Verweises auf die Optionenseite
HRESULT CLineSplitPropAct::EnsureOptionsIF()
{
	if (m_wOperOptions.IsValid())
		return S_OK;

	if (!m_mkOperOptions.IsValid())
		return E_UNEXPECTED;

#if defined(_DEBUG)
CComBSTR bstrMk;

	MkGetDisplayName(m_mkOperOptions, &bstrMk, NULL);
#endif // defined(_DEBUG)

	RETURN_FAILED_HRESULT(MkBindToObjectLocal(m_mkOperOptions, m_wOperOptions.ppi()));
	return S_OK;
}

