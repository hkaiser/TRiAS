// Definitionen: PropertyAction für Mengenoperationen von GeoObjekten
// File: SetsOperatPropAct.cpp

#include "ObjOperP.hxx"

#include <Com/MkHelper.h>

#include "SetsOperatPropAct.h"
#include "MonikerHelper.h"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// externe Variablen
extern ResourceFile* pRF;


///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor wird durch AddAction "TRiASEx.ObjSetsOperations.1" gerufen
CSetsOperatPropAct::CSetsOperatPropAct (void)
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
	m_pSetsOperDlg = 0;
	m_bIsDirty = false;			// Dialogparameter wurden (noch) nicht verändert
	m_bIsInitialized = false;	// Page ist noch nicht initialisiert
	m_bHasInitData = false;		// (noch) keine Initialisierungsdaten für den Dialog von Load()
								// bereitgestellt bzw. schon an diesen weitergereicht
	COM_TRY {
	ResString resPropInfo (ResID (IDS_SETSCAPT, pRF), 30);

		m_sDesc = resPropInfo;
	} COM_CATCH_NORETURN;
}


// --------------------------------------------------------------------------------------------
CSetsOperatPropAct::~CSetsOperatPropAct (void)
{
	DELETE_OBJ (m_pSetsOperDlg);
}


// --------------------------------------------------------------------------------------------
void CSetsOperatPropAct::FinalRelease (void)
{
	if (m_hDex) {
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
STDMETHODIMP CSetsOperatPropAct::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
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
STDMETHODIMP CSetsOperatPropAct::HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile,
										   ULONG *pulHelpCtx)
{
	try
	{
		if (NULL != pBuffer && wLen > 0)
		{
		// Beschreibung übergeben
		ResString resHelp (ResID (IDS_HELPINFO_SETSOPERAT, pRF), 128);
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
STDMETHODIMP CSetsOperatPropAct::AddConfigPages (LPFNADDPROPSHEETPAGE lpfnAddPage,
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
		DELETE_OBJ (m_pSetsOperDlg);	// evtl. vorherigen freigeben
		m_pSetsOperDlg = CSetsOperatDlg::CreateInstance (ResID(IDD_SETSOPERATPROPACT, pRF),
														 cbCaption, this, m_caSelInfo, *pRF);
		if (NULL == m_pSetsOperDlg) _com_issue_error (E_OUTOFMEMORY);

		if (!IsNoShow())
		{
		// Seite hinzufügen, wenn selbige angezeigt werden soll
		HPROPSHEETPAGE hPSP = m_pSetsOperDlg -> CreatePage();

			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_UNEXPECTED;
		}

		// Initialisierungsdaten für den Dialog wurden von Load() bereitgestellt, konnten aber
		// noch nicht an diesen weitergereicht werden
		if (m_bHasInitData)
		{
		// Initialisierungsdaten jetzt an den Dialog weiterreichen
		HRESULT	hr = m_pSetsOperDlg->SetSelectedInfo (&m_caSelInfo, IsNoShow());

			if (FAILED(hr)) _com_issue_error(hr);
		}

		if (NULL != puiCnt) 
			*puiCnt = IsNoShow() ? 0 : 1;	// "1" ist die Anzahl der einzuhängenden Pages

	}
	catch (_com_error& e)
	{
		DELETE_OBJ (m_pSetsOperDlg);
		if (puiCnt) *puiCnt = 0;
		return _COM_ERROR(e);
	}

	return S_OK;

} // AddConfigPages


// --------------------------------------------------------------------------------------------
// Info, ob es sich um die erste bzw. letzte Seite handelt, damit in Abhängigkeit davon die
// Buttons modifiziert werden können
STDMETHODIMP CSetsOperatPropAct::PreConfigPages (IDataObject* pIDataObj, DWORD dwFlags)
{
	m_pSetsOperDlg->SetFlags (dwFlags);
	EnsureOptionsIF();

	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CSetsOperatPropAct::BeginAction (IProgressIndicator* pIProgInd)
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
	m_pSetsOperDlg->GetSelectedInfo (&m_caSelInfo, m_bIsDirty);

	// Liste für Objekte, die an die PropertyPage übergeben werden, initialisieren
	m_InObjs.clear();				// Liste sicher leeren
	m_ObjsIter = m_InObjs.begin();	// auf Anfang stellen

	return S_OK;

} // BeginAction


// --------------------------------------------------------------------------------------------
STDMETHODIMP CSetsOperatPropAct::DoAction (IDataObject* pDataObj, DWORD)
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
STDMETHODIMP CSetsOperatPropAct::EndAction (DWORD, IDataObject** ppDataOut)
{
	_ASSERTE (m_ObjsIter != m_InObjs.end());

	*ppDataOut = 0;

	COM_TRY {
	WEnumLONG wEnumInObj (*m_ObjsIter);	// die zu bearbeitenden Objekte
	WEnumLONG wEnumOutObj;				// Ergebnisobjekte der ausgewählten Operation

	ulong ulMaxPos = wEnumInObj->Count();

		if (ulMaxPos > 1) {	// sonst hat's nicht viel Zweck
		// Optionen abfragen
		DWORD dwOptions = 0x00;

			if (SUCCEEDED(EnsureOptionsIF())) {
				_ASSERTE(m_wOperOptions.IsValid());
				m_wOperOptions->GetOptions (&dwOptions);
			}

			// im Dialog ausgewählte Operation ausführen
		HRESULT hr = m_pSetsOperDlg->ExecuteOperation (m_hPr, wEnumInObj, dwOptions,
													   wEnumOutObj.ppi());
			if (ERROR_WRITE_PROTECT == hr)		// Datenquelle schreibgeschützt
			{
				DELETE_OBJ (m_pSetsOperDlg);	// bei Fehler Dialog wieder freigeben
				return S_OK;					// es kommen keine Daten mehr
			}
			if (FAILED (hr)) {
				DELETE_OBJ (m_pSetsOperDlg);	// bei Fehler Dialog wieder freigeben
                return hr;
            }
		}

		m_ObjsIter++;

		if (wEnumOutObj.IsValid()) {
		// IDataObject abfragen
		WDataObject IDO (CLSID_DataTransferObject);

		// Ergebnisobjekte im DataObjekt IDO speichern
			THROW_FAILED_HRESULT (SetEnumLONGData ((IEnum<LONG>*)(IEnumLONG*)wEnumOutObj,
												   IDO));
		// Resultat setzen
			*ppDataOut = IDO.detach();

			if (0 == wEnumOutObj->Count())
			{
			ResString resTitel (ResID (IDS_LONGCLASSNAME, pRF), 50);
			ResString resText (ResID (IDS_BOXTEXT7, pRF), 200);
	
				MessageBox (__hWndM, resText.Addr(), resTitel.Addr(),
							MB_ICONINFORMATION | MB_OK);
			}
		}

	} COM_CATCH_OP_NOASSERT_ON(delete m_pSetsOperDlg, E_ABORT);

	if (m_ObjsIter != m_InObjs.end())	// es kommen noch weitere Daten
		return S_FALSE;

	DELETE_OBJ (m_pSetsOperDlg);		// es kommen keine Daten mehr
	return S_OK;

} // EndAction


///////////////////////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CSetsOperatPropAct::GetClassID (LPCLSID lpClassID)
{
	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_SetsOperatPropAct;
	return S_OK;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit methods
// m_bIsDirty == true, wenn die Dialogparameter verändert wurden und somit Save() sinnvoll ist
STDMETHODIMP CSetsOperatPropAct::IsDirty (void)
{
	return m_bIsDirty ? S_OK : S_FALSE;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CSetsOperatPropAct::Load (LPSTREAM pStm)
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
	if (SETSOPERATPROPACT_SIGNATURE != dwSignature)
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(pStm->Read (&dwVersion, sizeof(DWORD), NULL));
	if ((dwVersion & ~MINOR_VERSION_MASK) > SETSOPERATPROPACT_ACTVERSION)
		return STG_E_OLDDLL;	// File was written with a newer version

// dann selektierte Info der letzten Auswahl
	RETURN_FAILED_HRESULT (pStm->Read (&m_caSelInfo.OpMode, sizeof(ObjOp), NULL));
	RETURN_FAILED_HRESULT (pStm->Read (&m_caSelInfo.dFuzzy, sizeof(double), NULL));

// ggf. Moniker einlesen
BOOL fHasMoniker = TRUE;

	if (dwVersion >= SETSOPERATPROPACT_VERSION_1_0_2) {
		RETURN_FAILED_HRESULT (pStm->Read (&fHasMoniker, sizeof(BOOL), NULL));
	}
	if (fHasMoniker) {
		RETURN_FAILED_HRESULT (OleLoadFromStream(pStm, IID_IMoniker, m_mkOperOptions.ppv()));
	}

	if (0 == m_pSetsOperDlg)
		// Initialisierungsdaten für den Dialog wurden zwar soeben von Load() bereitgestellt,
		// können hier aber noch nicht an diesen weitergereicht werden
		m_bHasInitData = true;
	else
		// Initialisierungsdaten an den Dialog weiterreichen
		m_pSetsOperDlg->SetSelectedInfo (&m_caSelInfo);
	
	m_bIsInitialized = true;	// Page wurde jetzt durch Load() initialisiert
	m_bIsDirty = false;			// Dialogparameter wurden (noch) nicht verändert
	return S_OK;

} // Load


// --------------------------------------------------------------------------------------------
// fClearDirty: Zustand im aktuellen Projekt und dessen Abspeicherung ist identisch (true) bzw.
//              stimmt nicht überein (false); letzterer Fall tritt bei SaveAs() auf
STDMETHODIMP CSetsOperatPropAct::Save (LPSTREAM pStm, BOOL fClearDirty)
{
// Bezeichner wegschreiben
HRESULT hr = CPropertyAction::Save (pStm, fClearDirty);

	if (FAILED(hr)) return hr;

// Signatur und Version wegschreiben
DWORD dwSignature = SETSOPERATPROPACT_SIGNATURE;
DWORD dwVersion = SETSOPERATPROPACT_VERSION_1_0_2;

	RETURN_FAILED_HRESULT (pStm->Write (&dwSignature, sizeof(DWORD), NULL));
	RETURN_FAILED_HRESULT (pStm->Write (&dwVersion, sizeof(DWORD), NULL));

// dann selektierte Info der letzten Auswahl
	// nachfolgende if-Bedingung für den Fall, daß m_pSetsOperDlg-Seite "am Schluß" nicht oben
	// lag, also BeginAction() und damit auch GetSelectedInfo() nicht ausgeführt wurden
	if (m_pSetsOperDlg)
		m_pSetsOperDlg->GetSelectedInfo (&m_caSelInfo, m_bIsDirty);

	RETURN_FAILED_HRESULT (pStm->Write (&m_caSelInfo.OpMode, sizeof(ObjOp), NULL));
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
STDMETHODIMP CSetsOperatPropAct::GetSizeMax (ULARGE_INTEGER *pcbSize)
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

	liOwnSize.QuadPart += sizeof(BOOL) + 2*sizeof(DWORD) + sizeof(ObjOp) + sizeof(double);
	liOwnSize.QuadPart += cbSize.QuadPart;
	*pcbSize = liOwnSize;
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CSetsOperatPropAct::InitNew (void)
{
	if (m_bIsInitialized)		// m_bIsInitialized == true, wenn Page schon durch Load()
		return E_UNEXPECTED;	// initialisiert wurde

	m_caSelInfo.OpMode = VEREINIGUNG;
	m_caSelInfo.dFuzzy = 0.0;

	m_bIsInitialized = true;	// Page wurde jetzt durch InitNew() initialisiert
	m_bIsDirty = false;			// Dialogparameter wurden noch nicht verändert
	return S_OK;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
// mit pBuffer die standardmäßige kürzere Beschreibung überschreiben
STDMETHODIMP CSetsOperatPropAct::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags)  
{
	if (NULL == pcBuffer) return E_POINTER;

	m_sDesc = pcBuffer;
	return S_OK;
}



///////////////////////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
// Laden mit "Key = Value"-Vorgaben
STDMETHODIMP CSetsOperatPropAct::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	return E_NOTIMPL;
}



///////////////////////////////////////////////////////////////////////////////////////////////
// ISetGeoOperatOptionsTarget
// Verbindung zur COptionsPropAct-Klasse über deren Interface IGetGeoOperatOptions herstellen
STDMETHODIMP CSetsOperatPropAct::SetOperatOptionsSite (IGetGeoOperatOptions* pOperOptions)
{
	COM_TRY {
		m_wOperOptions = pOperOptions;
		m_mkOperOptions.Assign(NULL);
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CSetsOperatPropAct::SetDirty (bool bDirty) 
{ 
	m_bIsDirty = bDirty; 
}

///////////////////////////////////////////////////////////////////////////////
// Sicherstellen des Verweises auf die Optionenseite
HRESULT CSetsOperatPropAct::EnsureOptionsIF()
{
	if (m_wOperOptions.IsValid())
		return S_OK;

	if (!m_mkOperOptions.IsValid())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(MkBindToObjectLocal(m_mkOperOptions, m_wOperOptions.ppi()));
	return S_OK;
}

