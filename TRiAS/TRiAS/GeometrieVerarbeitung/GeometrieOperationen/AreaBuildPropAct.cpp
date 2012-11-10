// Definitionen: PropertyAction für Bilden von Flächen und Linien aus Linienelementen
// File: AreaBuildPropAct.cpp

#include "ObjOperP.hxx"

#include <Com/MkHelper.h>

#include "AreaBuildPropAct.h"
#include "MonikerHelper.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////
// externe Variablen
extern ResourceFile* pRF;

///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor wird durch AddAction "TRiASEx.AreasBuilding.1" gerufen
CAreaBuildPropAct::CAreaBuildPropAct (void)
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
	m_pAreaBuildDlg = NULL;
	m_bIsDirty = false;			// Dialogparameter wurden (noch) nicht verändert
	m_bIsInitialized = false;	// Page ist noch nicht initialisiert
	m_bHasInitData = false;		// (noch) keine Initialisierungsdaten für den Dialog von Load()
								// bereitgestellt bzw. schon an diesen weitergereicht
	COM_TRY {
	ResString resPropInfo (ResID (IDS_AREACAPT, pRF), 30);

		m_sDesc = resPropInfo;
	} COM_CATCH_NORETURN;
}


// --------------------------------------------------------------------------------------------
CAreaBuildPropAct::~CAreaBuildPropAct (void)
{
	DELETE_OBJ (m_pAreaBuildDlg);
}


// --------------------------------------------------------------------------------------------
void CAreaBuildPropAct::FinalRelease (void)
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
STDMETHODIMP CAreaBuildPropAct::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
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
STDMETHODIMP CAreaBuildPropAct::HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile,
										  ULONG *pulHelpCtx)
{
	try
	{
		if (NULL != pBuffer && wLen > 0)
		{
		// Beschreibung übergeben
		ResString resHelp (ResID (IDS_HELPINFO_AREABUILD, pRF), 128);
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
STDMETHODIMP CAreaBuildPropAct::AddConfigPages (LPFNADDPROPSHEETPAGE lpfnAddPage,
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
		DELETE_OBJ (m_pAreaBuildDlg);	// evtl. vorherigen freigeben
		m_pAreaBuildDlg = CAreasBuildingDlg::CreateInstance (ResID(IDD_AREABUILDPROPACT, pRF),
														   cbCaption, this, m_caSelInfo, *pRF);
		if (NULL == m_pAreaBuildDlg) _com_issue_error (E_OUTOFMEMORY);

		if (!IsNoShow())
		{
		// Seite hinzufügen, wenn selbige angezeigt werden soll
		HPROPSHEETPAGE hPSP = m_pAreaBuildDlg -> CreatePage();

			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_UNEXPECTED;
		}

		// Initialisierungsdaten für den Dialog wurden von Load() bereitgestellt, konnten aber
		// noch nicht an diesen weitergereicht werden
		if (m_bHasInitData)
		{
		// Initialisierungsdaten jetzt an den Dialog weiterreichen
		HRESULT	hr = m_pAreaBuildDlg->SetSelectedInfo (&m_caSelInfo, IsNoShow());

			if (FAILED(hr)) _com_issue_error(hr);
		}

		if (NULL != puiCnt) 
			*puiCnt = IsNoShow() ? 0 : 1;	// "1" ist die Anzahl der einzuhängenden Pages

	}
	catch (_com_error& e)
	{
		DELETE_OBJ (m_pAreaBuildDlg);
		if (puiCnt) *puiCnt = 0;
		return _COM_ERROR (e);
	}

	return S_OK;

} // AddConfigPages


// --------------------------------------------------------------------------------------------
// Info, ob es sich um die erste bzw. letzte Seite handelt, damit in Abhängigkeit davon die
// Buttons modifiziert werden können
STDMETHODIMP CAreaBuildPropAct::PreConfigPages (IDataObject* pIDataObj, DWORD dwFlags)
{
	m_pAreaBuildDlg->SetFlags (dwFlags);
	EnsureOptionsIF();

	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CAreaBuildPropAct::BeginAction (IProgressIndicator* pIProgInd)
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
	m_pAreaBuildDlg->GetSelectedInfo (&m_caSelInfo, m_bIsDirty);

	// Liste für Objekte, die an die PropertyPage übergeben werden, initialisieren
	m_InObjs.clear();				// Liste sicher leeren
	m_ObjsIter = m_InObjs.begin();	// auf Anfang stellen

	return S_OK;

} // BeginAction


// --------------------------------------------------------------------------------------------
STDMETHODIMP CAreaBuildPropAct::DoAction (IDataObject* pDataObj, DWORD)
{
WEnumLONG wEnumObj;
HRESULT hr = GetEnumLONGData (pDataObj, (IEnum<LONG>**)(IEnumLONG**)wEnumObj.ppi());

	if (FAILED(hr)) return hr;

	// Enumerator (an PropertyPage übergebene Objekte) in Liste speichern
	m_InObjs.push_back (wEnumObj);		// Enumerator am Ende der Liste anfügen
	if (1 == m_InObjs.size())
		m_ObjsIter = m_InObjs.begin();	// Iterator zeigt auf das 1. Element der Liste

	return hr;

} // DoAction


// --------------------------------------------------------------------------------------------
STDMETHODIMP CAreaBuildPropAct::EndAction (DWORD, IDataObject** ppDataOut)
{
	_ASSERTE (m_ObjsIter != m_InObjs.end());

	*ppDataOut = 0;

	COM_TRY {
	WEnumLONG wEnumInObj (*m_ObjsIter);	// die zu bearbeitenden Objekte
	WEnumLONG wEnumOutObj;				// Ergebnisobjekte der ausgewählten Operation

	// Optionen abfragen
	DWORD dwOptions = 0x00;

		if (m_wOperOptions.IsValid())
			m_wOperOptions->GetOptions (&dwOptions);

		// im Dialog ausgewählte Operation ausführen
		THROW_FAILED_HRESULT (m_pAreaBuildDlg->ExecuteOperation (m_hPr, wEnumInObj, dwOptions,
																 wEnumOutObj.ppi()));

		m_ObjsIter++;

		if (wEnumOutObj.IsValid()) {
		// IDataObject abfragen
		WDataObject IDO (CLSID_DataTransferObject);

		// Ergebnisobjekte im DataObjekt IDO speichern
			THROW_FAILED_HRESULT (SetEnumLONGData ((IEnum<LONG>*)(IEnumLONG*)wEnumOutObj,
												   IDO));
		// Resultat setzen
			*ppDataOut = IDO.detach();

			if (0 == wEnumOutObj->Count()) {
			ResString resTitel (ResID (IDS_LONGCLASSNAME, pRF), 50);
			ResString resText (ResID (IDS_BOXTEXT7, pRF), 200);
	
				MessageBox (__hWndM, resText.Addr(), resTitel.Addr(),
							MB_ICONINFORMATION | MB_OK);
			}
		}
	}
	COM_CATCH_OP(
		delete m_pAreaBuildDlg;	// bei Fehler Dialog wieder freigeben
    );

	if (m_ObjsIter != m_InObjs.end())	// es kommen noch weitere Daten
		return S_FALSE;

	DELETE_OBJ (m_pAreaBuildDlg);		// es kommen keine Daten mehr
	return S_OK;

} // EndAction


///////////////////////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CAreaBuildPropAct::GetClassID (LPCLSID lpClassID)
{
	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_AreaBuildPropAct;
	return S_OK;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit methods
// m_bIsDirty == true, wenn die Dialogparameter verändert wurden und somit Save() sinnvoll ist
STDMETHODIMP CAreaBuildPropAct::IsDirty (void)
{
	return m_bIsDirty ? S_OK : S_FALSE;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CAreaBuildPropAct::Load (LPSTREAM pStm)
{
	if (m_bIsInitialized)		// m_bIsInitialized == true, wenn Page schon durch InitNew()
		return E_UNEXPECTED;	// initialisiert wurde

// Daten einlesen
// zuerst Bezeichner einlesen
HRESULT hr = CPropertyAction::Load (pStm);

	if (FAILED(hr)) return hr;

// meine Versionsnummer lesen und überprüfen
DWORD dwSignature = 0;
DWORD dwVersion = 0;

	RETURN_FAILED_HRESULT(pStm->Read (&dwSignature, sizeof(DWORD), NULL));
	if (AREABUILDPROPACT_SIGNATURE != dwSignature)
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(pStm->Read (&dwVersion, sizeof(DWORD), NULL));
	if ((dwVersion & ~ MINOR_VERSION_MASK) > AREABUILDPROPACT_ACTVERSION)
		return STG_E_OLDDLL;	// File was written with a newer version

// dann selektierte Info der letzten Auswahl
	RETURN_FAILED_HRESULT (pStm->Read (&m_caSelInfo.bLines, sizeof(BOOL), NULL));
	RETURN_FAILED_HRESULT (pStm->Read (&m_caSelInfo.dFuzzy, sizeof(double), NULL));

// ggf. Moniker einlesen
BOOL fHasMoniker = TRUE;

	if (dwVersion >= AREABUILDPROPACT_VERSION_1_0_2) {
		RETURN_FAILED_HRESULT (pStm->Read (&fHasMoniker, sizeof(BOOL), NULL));
	}
	if (fHasMoniker) {
		RETURN_FAILED_HRESULT (OleLoadFromStream(pStm, IID_IMoniker, m_mkOperOptions.ppv()));
	}

	if (0 == m_pAreaBuildDlg)
		// Initialisierungsdaten für den Dialog wurden zwar soeben von Load() bereitgestellt,
		// können hier aber noch nicht an diesen weitergereicht werden
		m_bHasInitData = true;
	else
		// Initialisierungsdaten an den Dialog weiterreichen
		m_pAreaBuildDlg->SetSelectedInfo (&m_caSelInfo);
	
	m_bIsInitialized = true;	// Page wurde jetzt durch Load() initialisiert
	m_bIsDirty = false;			// Dialogparameter wurden (noch) nicht verändert
	return S_OK;

} // Load


// --------------------------------------------------------------------------------------------
// fClearDirty: Zustand im aktuellen Projekt und dessen Abspeicherung ist identisch (true) bzw.
//              stimmt nicht überein (false); letzterer Fall tritt bei SaveAs() auf
STDMETHODIMP CAreaBuildPropAct::Save (LPSTREAM pStm, BOOL fClearDirty)
{
// Bezeichner wegschreiben
HRESULT hr = CPropertyAction::Save (pStm, fClearDirty);

	if (FAILED(hr)) return hr;

// Signatur und Version wegschreiben
DWORD dwSignature = AREABUILDPROPACT_SIGNATURE;
DWORD dwVersion = AREABUILDPROPACT_VERSION_1_0_2;

	RETURN_FAILED_HRESULT (pStm->Write (&dwSignature, sizeof(DWORD), NULL));
	RETURN_FAILED_HRESULT (pStm->Write (&dwVersion, sizeof(DWORD), NULL));

// dann selektierte Info der letzten Auswahl
	// nachfolgende if-Bedingung für den Fall, daß m_pAreaBuildDlg-Seite "am Schluß" nicht oben
	// lag, also BeginAction() und damit auch GetSelectedInfo() nicht ausgeführt wurden
	if (m_pAreaBuildDlg)
		m_pAreaBuildDlg->GetSelectedInfo (&m_caSelInfo, m_bIsDirty);

	RETURN_FAILED_HRESULT (pStm->Write (&m_caSelInfo.bLines, sizeof(BOOL), NULL));
	RETURN_FAILED_HRESULT (pStm->Write (&m_caSelInfo.dFuzzy, sizeof(double), NULL));

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
STDMETHODIMP CAreaBuildPropAct::GetSizeMax (ULARGE_INTEGER *pcbSize)
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

	liOwnSize.QuadPart += 2*sizeof(DWORD) + 2* sizeof(BOOL) + sizeof(double);
	liOwnSize.QuadPart += cbSize.QuadPart;
	*pcbSize = liOwnSize;
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CAreaBuildPropAct::InitNew (void)
{
	if (m_bIsInitialized)		// m_bIsInitialized == true, wenn Page schon durch Load()
		return E_UNEXPECTED;	// initialisiert wurde

	m_caSelInfo.bLines = TRUE;
	m_caSelInfo.dFuzzy = 0.1;	// ???

	m_bIsInitialized = true;	// Page wurde jetzt durch InitNew() initialisiert
	m_bIsDirty = false;			// Dialogparameter wurden noch nicht verändert
	return S_OK;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
// mit pBuffer die standardmäßige kürzere Beschreibung überschreiben
STDMETHODIMP CAreaBuildPropAct::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags)  
{
	if (NULL == pcBuffer) return E_POINTER;

	m_sDesc = pcBuffer;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
// Laden mit "Key = Value"-Vorgaben
STDMETHODIMP CAreaBuildPropAct::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// ISetGeoOperatOptionsTarget
// Verbindung zur COptionsPropAct-Klasse über deren Interface IGetGeoOperatOptions herstellen
STDMETHODIMP CAreaBuildPropAct::SetOperatOptionsSite (IGetGeoOperatOptions* pOperOptions)
{
	COM_TRY {
		m_wOperOptions = pOperOptions;
		m_mkOperOptions.Assign(NULL);
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CAreaBuildPropAct::SetDirty (bool bDirty) 
{ 
	m_bIsDirty = bDirty; 
}

///////////////////////////////////////////////////////////////////////////////
// Sicherstellen des Verweises auf die Optionenseite
HRESULT CAreaBuildPropAct::EnsureOptionsIF()
{
	if (m_wOperOptions.IsValid())
		return S_OK;

	if (!m_mkOperOptions.IsValid())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(MkBindToObjectLocal(m_mkOperOptions, m_wOperOptions.ppi()));
	return S_OK;
}

