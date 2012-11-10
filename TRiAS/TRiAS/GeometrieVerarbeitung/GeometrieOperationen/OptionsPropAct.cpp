// Definitionen: PropertyAction für Optionen der Objektoperationen
// File: OptionsPropAct.cpp

#include "ObjOperP.hxx"

#include <Com/MkHelper.h>
#include <Atl/Ciid.h>

#include "OptionsPropAct.h"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////////////////////
// externe Variablen
extern ResourceFile* pRF;

///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor wird durch AddAction "TRiASEx.GeoOperatOptions.1" gerufen
COptionsPropAct::COptionsPropAct (void)
{
// Member initialisieren
	m_pOptionsDlg = 0;
	m_bIsDirty = false;			// Dialogparameter wurden (noch) nicht verändert
	m_bIsInitialized = false;	// Page ist noch nicht initialisiert
	m_bHasInitData = false;		// (noch) keine Initialisierungsdaten für den Dialog von Load()
								// bereitgestellt bzw. schon an diesen weitergereicht
	try {
	ResString resPropInfo (ResID (IDS_OPTIONSCAPT, pRF), 30);

		m_sDesc = resPropInfo;
	}
	catch (...)
	{
		_ASSERTE (false);
	}
}

// --------------------------------------------------------------------------------------------
COptionsPropAct::~COptionsPropAct (void)
{
	DELETE_OBJ (m_pOptionsDlg);
}

///////////////////////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions
// kürzere Beschreibung (Standardtext oder mit SetPropInfo() gesetzter Text wird in pBuffer
// (der Länge wLen) zurückgegeben
STDMETHODIMP COptionsPropAct::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
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
STDMETHODIMP COptionsPropAct::HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile,
										ULONG *pulHelpCtx)
{
	try
	{
		if (NULL != pBuffer && wLen > 0)
		{
		// Beschreibung übergeben
		ResString resHelp (ResID (IDS_HELPINFO_OPTIONS, pRF), 128);
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
STDMETHODIMP COptionsPropAct::AddConfigPages (LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam,
											  LPCSTR pcDesc, UINT *puiCnt)
{
char cbCaption[_MAX_PATH];

	try
	{
		if (NULL != pcDesc)		// Caption ist gegeben
			strcpy (cbCaption, pcDesc);
		else	// von zugehöriger ClassProperty unseren Namen besorgen
			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

		// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
		DELETE_OBJ (m_pOptionsDlg);	// evtl. vorherigen freigeben
		m_pOptionsDlg = COptionsDlg::CreateInstance (ResID(IDD_OPTIONSPROPACT, pRF), cbCaption,
													 m_caSelInfo, *pRF);

		if (NULL == m_pOptionsDlg) _com_issue_error (E_OUTOFMEMORY);

		if (!IsNoShow())
		{
		// Seite hinzufügen, wenn selbige angezeigt werden soll
		HPROPSHEETPAGE hPSP = m_pOptionsDlg -> CreatePage();

			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_UNEXPECTED;
		}

		// Initialisierungsdaten für den Dialog wurden von Load() bereitgestellt, konnten aber
		// noch nicht an diesen weitergereicht werden
		if (m_bHasInitData)
		{
		// Initialisierungsdaten jetzt an den Dialog weiterreichen
		HRESULT	hr = m_pOptionsDlg->SetSelectedInfo (&m_caSelInfo, IsNoShow());

			if (FAILED(hr)) _com_issue_error(hr);
		}

		if (NULL != puiCnt) 
			*puiCnt = IsNoShow() ? 0 : 1;	// "1" ist die Anzahl der einzuhängenden Pages

	}
	catch (_com_error& e)
	{
		DELETE_OBJ (m_pOptionsDlg);
		if (puiCnt) *puiCnt = 0;
		return _COM_ERROR (e);
	}

	return S_OK;

} // AddConfigPages

// --------------------------------------------------------------------------------------------
// Info, ob es sich um die erste bzw. letzte Seite handelt, damit in Abhängigkeit davon die
// Buttons modifiziert werden können
STDMETHODIMP COptionsPropAct::PreConfigPages (IDataObject* pIDataObj, DWORD dwFlags)
{
	m_pOptionsDlg->SetFlags (dwFlags);
	return S_OK;
}

// --------------------------------------------------------------------------------------------
STDMETHODIMP COptionsPropAct::BeginAction (IProgressIndicator* pIProgInd)
{
	// Zustand des Dialogs retten (für evtl. späteres Save())
	m_pOptionsDlg->GetSelectedInfo (&m_caSelInfo, m_bIsDirty);

	// Liste für Objekte, die an die PropertyPage übergeben werden, initialisieren
	m_PassObjs.clear();					// Liste sicher leeren
	m_ObjsIter = m_PassObjs.begin();	// auf Anfang stellen

	return S_OK;

} // BeginAction

// --------------------------------------------------------------------------------------------
STDMETHODIMP COptionsPropAct::DoAction (IDataObject* pDataObj, DWORD)
{
WEnumLONG wEnumObj;
HRESULT hr = GetEnumLONGData (pDataObj, (IEnum<LONG>**)(IEnumLONG**)wEnumObj.ppi());

	if (FAILED(hr)) return hr;

	// Enumerator (an PropertyPage übergebene Objekte) in Liste speichern
	m_PassObjs.push_back (wEnumObj);		// Enumerator am Ende der Liste anfügen
	if (1 == m_PassObjs.size())
		m_ObjsIter = m_PassObjs.begin();	// Iterator zeigt auf das 1. Element der Liste

	return hr;

} // DoAction

// --------------------------------------------------------------------------------------------
// Daten nur durchreichen
STDMETHODIMP COptionsPropAct::EndAction (DWORD, IDataObject** ppDataOut)
{
	if (NULL == ppDataOut)
		return E_POINTER;

	if (m_PassObjs.empty())
		return S_OK;

	*ppDataOut = NULL;
	COM_TRY {
	WEnumLONG wEnumObj (*m_ObjsIter);	// die durchzureichenden Objekte
	WDataObject IDO (CLSID_DataTransferObject);

		THROW_FAILED_HRESULT (SetEnumLONGData ((IEnum<LONG>*)(IEnumLONG*)wEnumObj, IDO));
		*ppDataOut = IDO.detach();

	} COM_CATCH;
	return S_OK;	// es ist nichts weiter zu machen
} // EndAction

///////////////////////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP COptionsPropAct::GetClassID (LPCLSID lpClassID)
{
	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_OptionsPropAct;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit methods
// m_bIsDirty == true, wenn die Dialogparameter verändert wurden und somit Save() sinnvoll ist
STDMETHODIMP COptionsPropAct::IsDirty (void)
{
	return m_bIsDirty ? S_OK : S_FALSE;
}

// --------------------------------------------------------------------------------------------
STDMETHODIMP COptionsPropAct::Load (LPSTREAM pStm)
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
	if (OPTIONSPROPACT_SIGNATURE != dwSignature)
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(pStm->Read (&dwVersion, sizeof(DWORD), NULL));
	if ((dwVersion & ~ MINOR_VERSION_MASK) > OPTIONSPROPACT_ACTVERSION)
		return STG_E_OLDDLL;	// File was written with a newer version

// dann selektierte Info der letzten Auswahl
	RETURN_FAILED_HRESULT (pStm->Read (&m_caSelInfo.bFeat, sizeof(BOOL), NULL));
	RETURN_FAILED_HRESULT (pStm->Read (&m_caSelInfo.bDelete, sizeof(BOOL), NULL));
	RETURN_FAILED_HRESULT (pStm->Read (&m_caSelInfo.bMark, sizeof(BOOL), NULL));
	RETURN_FAILED_HRESULT (pStm->Read (&m_caSelInfo.bShowNew, sizeof(BOOL), NULL));
	RETURN_FAILED_HRESULT (pStm->Read (&m_caSelInfo.bShowOrig, sizeof(BOOL), NULL));

	if (0 == m_pOptionsDlg)
		// Initialisierungsdaten für den Dialog wurden zwar soeben von Load() bereitgestellt,
		// können hier aber noch nicht an diesen weitergereicht werden
		m_bHasInitData = true;
	else
		// Initialisierungsdaten an den Dialog weiterreichen
		m_pOptionsDlg->SetSelectedInfo (&m_caSelInfo);
	
	m_bIsInitialized = true;	// Page wurde jetzt durch Load() initialisiert
	m_bIsDirty = false;			// Dialogparameter wurden (noch) nicht verändert
	return S_OK;

} // Load

// --------------------------------------------------------------------------------------------
// fClearDirty: Zustand im aktuellen Projekt und dessen Abspeicherung ist identisch (true) bzw.
//              stimmt nicht überein (false); letzterer Fall tritt bei SaveAs() auf
STDMETHODIMP COptionsPropAct::Save (LPSTREAM pStm, BOOL fClearDirty)
{
// Bezeichner wegschreiben
HRESULT hr = CPropertyAction::Save (pStm, fClearDirty);

	if (FAILED(hr)) return hr;

// meine Versionsnummer wegschreiben
DWORD dwSignature = OPTIONSPROPACT_SIGNATURE;
DWORD dwVersion = OPTIONSPROPACT_VERSION_1_0_1;

	RETURN_FAILED_HRESULT (pStm->Write (&dwSignature, sizeof(DWORD), NULL));
	RETURN_FAILED_HRESULT (pStm->Write (&dwVersion, sizeof(DWORD), NULL));

// dann selektierte Info der letzten Auswahl
	RETURN_FAILED_HRESULT (pStm->Write (&m_caSelInfo.bFeat, sizeof(BOOL), NULL));
	RETURN_FAILED_HRESULT (pStm->Write (&m_caSelInfo.bDelete, sizeof(BOOL), NULL));
	RETURN_FAILED_HRESULT (pStm->Write (&m_caSelInfo.bMark, sizeof(BOOL), NULL));
	RETURN_FAILED_HRESULT (pStm->Write (&m_caSelInfo.bShowNew, sizeof(BOOL), NULL));
	RETURN_FAILED_HRESULT (pStm->Write (&m_caSelInfo.bShowOrig, sizeof(BOOL), NULL));

	if (fClearDirty) m_bIsDirty = false;
	return S_OK;

} // Save

// --------------------------------------------------------------------------------------------
// Bestimmen der benötigten Speichergröße für Save()
STDMETHODIMP COptionsPropAct::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) return E_POINTER;

ULARGE_INTEGER cbSize;
HRESULT hr = CPropertyAction::GetSizeMax (&cbSize);

	if (FAILED(hr)) return hr;

ULARGE_INTEGER liOwnSize;

	liOwnSize.QuadPart = 5 * sizeof(BOOL) + 2 * sizeof(DWORD);
	liOwnSize.QuadPart = liOwnSize.QuadPart + cbSize.QuadPart;
	*pcbSize = liOwnSize;
	return S_OK;
}

// --------------------------------------------------------------------------------------------
STDMETHODIMP COptionsPropAct::InitNew (void)
{
	if (m_bIsInitialized)		// m_bIsInitialized == true, wenn Page schon durch Load()
		return E_UNEXPECTED;	// initialisiert wurde

	m_caSelInfo.bFeat = TRUE;
	m_caSelInfo.bDelete = FALSE;
	m_caSelInfo.bMark = FALSE;
	m_caSelInfo.bShowNew = TRUE;
	m_caSelInfo.bShowOrig = TRUE;

	m_bIsInitialized = true;	// Page wurde jetzt durch InitNew() initialisiert
	m_bIsDirty = false;			// Dialogparameter wurden noch nicht verändert
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
// mit pBuffer die standardmäßige kürzere Beschreibung überschreiben
STDMETHODIMP COptionsPropAct::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags)  
{
	if (NULL == pcBuffer) return E_POINTER;

	m_sDesc = pcBuffer;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
// Laden mit "Key = Value"-Vorgaben
STDMETHODIMP COptionsPropAct::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// IGetGeoOperatOptions
// IGetGeoOperatOptions ist das Interface, das COptionsPropAct für die CRegOperatPropAct- bzw.
// CSetsOperatPropAct-Klasse bereitstellt, d.h. das Interface, über das diese Klassen
// COptionsPropAct rufen können
STDMETHODIMP COptionsPropAct::GetOptions (DWORD* pdwOptions)
{
	*pdwOptions = 0x00;
	if (m_caSelInfo.bFeat) *pdwOptions |= FEAT;
	if (m_caSelInfo.bDelete) *pdwOptions |= DELET;
	if (m_caSelInfo.bMark) *pdwOptions |= MARK;
	if (m_caSelInfo.bShowNew) *pdwOptions |= SHNEW;
	if (m_caSelInfo.bShowOrig) *pdwOptions |= SHORIG;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// Sonstiges
void COptionsPropAct::SetDirty (bool bDirty) 
{ 
	m_bIsDirty = bDirty; 
}

///////////////////////////////////////////////////////////////////////////////
// IOleClientSite
STDMETHODIMP COptionsPropAct::GetMoniker (DWORD dwAssign, DWORD dwWhichMoniker, 
	IMoniker **ppmk)
{
	if (NULL == ppmk)
		return E_POINTER;

	*ppmk = NULL;
	_ASSERTE(m_mkSite.IsValid());

WMoniker mk (m_mkSite);

	*ppmk = mk.detach();
	return S_OK;
}

HRESULT COptionsPropAct::GetThisMoniker(DWORD dwWhichMoniker, IMoniker **ppmk)
{
	switch (dwWhichMoniker) {
	case OLEWHICHMK_OBJFULL:
	case OLEWHICHMK_OBJREL:
		{
		WPropertyActionSequence Seq;
		WMoniker mk;

			RETURN_FAILED_HRESULT(GetSite(Seq.GetIID(), Seq.ppv()));
			RETURN_FAILED_HRESULT(MkGetMoniker(Seq, OLEGETMONIKER_FORCEASSIGN, 
				OLEWHICHMK_OBJFULL, mk.ppi()));

		CIID Guid (CLSID_OptionsPropAct);
		WMoniker mkThis;
		CComBSTR bstrMk (L"MkPropAct:");

			bstrMk.AppendBSTR(CComBSTR(Guid));
			RETURN_FAILED_HRESULT(CreateItemMoniker(L"!", bstrMk, mkThis.ppi()));
			RETURN_FAILED_HRESULT(mk -> ComposeWith(mkThis, FALSE, ppmk));
		}
		break;

	case OLEWHICHMK_CONTAINER:
	default:
		break;
	}
	return (NULL == *ppmk) ? E_FAIL : S_OK;
}


///////////////////////////////////////////////////////////////////////////////
// IObjectWithSite
STDMETHODIMP COptionsPropAct::SetSite (IUnknown *pUnkSite)
{
	RETURN_FAILED_HRESULT(IObjectWithSiteImpl<COptionsPropAct>::SetSite(pUnkSite));
	if (NULL != pUnkSite) {
		RETURN_FAILED_HRESULT(GetThisMoniker(OLEWHICHMK_OBJFULL, m_mkSite.ppi()));
	}
	return S_OK;
}



