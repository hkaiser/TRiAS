// PropertyAction für Classifikation nach Objekteigenschaft -------------------
// File: CLSFYPRP.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <funcs03.h>

#include <xtsnguid.h>
#include <eonrguid.h>
#include <propguid.h>
#include <statguid.h>
#include <dirisole.h>

#include <pdataobj.hxx>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "clsfyprp.hxx"

/////////////////////////////////////////////////////////////////////////////
// externes
extern char g_pDLLName[_MAX_PATH];

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(DataObject);
#if !defined(_DEFINED_OBJECTPROPS)
DefineSmartInterface(ObjectProperty);
DefineSmartInterface(ObjectProps);
#define _DEFINED_OBJECTPROPS
#endif // _DEFINED_OBJECTPROPS

DefineEnumIIDWrapper(LONG);		// CIID_LONGEnum
DefineSmartEnumerator(LONG);	// WEnumLONG

// 0E54C9E1-20DE-11CF-BA55-00AA0018497C	
// DEFINE_GUID(CLSID_ClassifyByObjProp, 0x0E54C9E1L, 0x20DE, 0x11CF, 0xBA, 0x55, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// 'CLSPROP_ROOT\Recherche\Gruppieren von Objekten'

#pragma warning (disable: 4355)

CClsfyPropAct::CClsfyPropAct (void)
{
	m_pCfgDlg = NULL;
	m_fIsDirty = false;
	m_fIsInitialized = false;
	m_fHasInitData = false;

	try {
	ResourceFile RF (g_pDLLName);
	ResString resPropInfo (ResID (IDS_PROPINFO_CLASSIFYOBJ, &RF), 64);

		m_strDesc = resPropInfo;
	} catch (...) {
		TX_ASSERT(false);
	}
}

#pragma warning (default: 4355)

CClsfyPropAct::~CClsfyPropAct (void)
{
	DELETE_OBJ(m_pCfgDlg);
}

// *** IClassProperty specific functions *** ----------------------------------
STDMETHODIMP CClsfyPropAct::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Namen der Property kopieren
		ULONG ulLen = min ((size_t)(wLen-1), m_strDesc.length());

			strncpy (pBuffer, m_strDesc.c_str(), ulLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return E_FAIL;
	}

// wenn gewünscht, Flags übergeben
	if (pdwFlags) 
		*pdwFlags = PROPCAPS_ACTION_SINK|PROPCAPS_ACTION_SOURCE_MULTI;
	return S_OK;
}

STDMETHODIMP CClsfyPropAct::HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Beschreibung übergeben
		ResourceFile RF (g_pDLLName);
		ResString resHelp (ResID (IDS_HELPDESC_CLASSIFYOBJ, &RF), 128);
		ULONG ulLen = min (size_t(wLen-1), strlen(resHelp));

			strncpy (pBuffer, resHelp, ulLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return ResultFromScode (E_FAIL);
	}

// HelpFileInfo übergeben
	if (pHelpFile) pHelpFile[0] = '\0';
	if (pulHelpCtx) *pulHelpCtx = 0L;
	return S_OK;
}

// *** IPropertyAction methods ------------------------------------------------
STDMETHODIMP CClsfyPropAct::AddConfigPages (
	LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{
char cbCaption[_MAX_PATH];

	try {
		if (NULL != pcDesc)		// Caption ist gegeben
			strcpy (cbCaption, pcDesc);
		else	// von zugehöriger ClassProperty unseren Namen besorgen
			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

	// Liste der Objekteigenschaften initialisieren
	WObjectProps Props;
	BOOL fMustReInit = DEX_GetObjectProps (Props.ppi());

		if (Props.IsValid()) {
		// evtl. alle ObjProps installieren
			if (fMustReInit) {
				Props -> OnNewReferenceObject (-1L);	// alles bisherige löschen
				THROW_FAILED_HRESULT(Props -> OnNewReferenceObject (0L));
				DEX_SetMustInitOPFs(FALSE);
			}
		}

	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
	ResourceFile RF (g_pDLLName);

		DELETE_OBJ(m_pCfgDlg);	// evtl. vorherigen freigeben
		m_pCfgDlg = CClassifyDlg::CreateInstance (
						ResID(IDD_OBJECTROP_WIZ, &RF), cbCaption, RF, Props);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);

	//
	// Achtung MFC-Falle !
	// Normalerweise müßte an dieser Stelle lpfnAddPage mit unserem 
	// HPROPERTYPAGE gerufen werden, wir aber wissen (darf man das ?), daß
	// sich hinter dem eigentlich durchzureichendem lParam der Pointer auf
	// unsern PropertySheet verbirgt.
	//
		if (!IsNoShow() && UINT_MAX == ((CPropertySheet *)lParam) -> AddPage (m_pCfgDlg))
			_com_issue_error(E_UNEXPECTED);

		if (m_fHasInitData) {
		HRESULT	hr = m_pCfgDlg -> SetSelectedInfo (&m_caSelInfo, IsNoShow());

			if (FAILED(hr)) _com_issue_error(hr);
		}

		if (NULL != puiCnt) 
			*puiCnt = IsNoShow() ? 0 : 1;

	} catch (_com_error &e) {
		DELETE_OBJ (m_pCfgDlg);
		if (puiCnt) *puiCnt = 0;
		return _COM_ERROR(e);
	}
	return S_OK;
}

STDMETHODIMP CClsfyPropAct::PreConfigPages (IDataObject *, DWORD dwFlags)
{
	m_pCfgDlg -> SetFlags (dwFlags);
	return S_OK;
}

STDMETHODIMP CClsfyPropAct::DoAction (IDataObject *pDataObj, DWORD)
{
WEnumLONG IEnumObj;
HRESULT hr = GetEnumLONGData (pDataObj, IEnumObj.ppi());

	if (FAILED(hr)) 
		return hr;

	// JG980914
	// hier findet die Verarbeitung statt
	m_pCfgDlg -> SetAction(this);

	return m_pCfgDlg -> SetEnumLONG (IEnumObj);
}


STDMETHODIMP CClsfyPropAct::EndAction (DWORD, IDataObject **ppDataOut)
{
	*ppDataOut = NULL;

WEnumLONG IEnumObj;
os_string strObjProp;
HRESULT hr = m_pCfgDlg -> GetNextEnumLONG (IEnumObj.ppi(), strObjProp);

	if (FAILED(hr)) return hr;
	if (!IEnumObj) return S_OK;

	try {
	// IDataObject abfragen
	WDataObject IDO (CLSID_DataTransferObject);

	// Daten und Formate im DataObjekt speichern
	// 1. Liste aller Objekte
	HRESULT hr2 = SetEnumLONGData (IEnumObj, IDO);
		
		if (FAILED(hr2)) throw hr2;

	// 2. zu Grunde gelegte Objekteigenschaft
	os_string strObjPropName;

		m_pCfgDlg -> GetObjProp (strObjPropName);
		SetObjPropTemplate (strObjPropName, strObjProp, IDO);	// evtl Fehler ignorieren

	// Resultat setzen
		*ppDataOut = IDO.detach();

	} catch (HRESULT hr_result) {
		DELETE_OBJ (m_pCfgDlg);	// DialogPage freigeben
		return hr_result;
	}

	if (S_FALSE != hr) {
	// nur wenn's noch weiter geht, nicht löschen
		DELETE_OBJ(m_pCfgDlg);
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CClsfyPropAct::GetClassID (LPCLSID lpClassID)
{
	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_ClassifyByObjProp;
	return S_OK;
}

// IPersistStreamInit methods
STDMETHODIMP CClsfyPropAct::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CClsfyPropAct::Load (LPSTREAM pStm)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

// zuerst Bezeichner einlesen
HRESULT hr = CPropertyAction::Load (pStm);

	if (FAILED(hr)) return hr;

// dann selektierte Info der letzten Auswahl
char cbBuffer[_MAX_PATH];
LONG lLen = 0;

	RETURN_FAILED_HRESULT(pStm -> Read (&lLen, sizeof(LONG), NULL));
	RETURN_FAILED_HRESULT(pStm -> Read (cbBuffer, lLen, NULL));
	m_caSelInfo.m_strObjProp = cbBuffer;

	if (NULL == m_pCfgDlg) 
	// Dialog ist noch nicht initialisiert
		m_fHasInitData = true;
	else
		m_pCfgDlg -> SetSelectedInfo (&m_caSelInfo);
	
	m_fIsInitialized = true;
	m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CClsfyPropAct::Save (LPSTREAM pStm, BOOL fClearDirty)
{
// zuerst Bezeichner wegschreiben
HRESULT hr = CPropertyAction::Save (pStm, fClearDirty);

	if (FAILED(hr)) return hr;

// dann selektierte Info der letzten Auswahl
LONG lLen = m_caSelInfo.m_strObjProp.size()+1;

	RETURN_FAILED_HRESULT(pStm -> Write (&lLen, sizeof(LONG), NULL));
	RETURN_FAILED_HRESULT(pStm -> Write (m_caSelInfo.m_strObjProp.c_str(), lLen, NULL));

	if (fClearDirty) m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CClsfyPropAct::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) return E_POINTER;

ULARGE_INTEGER cbSize;
HRESULT hr = CPropertyAction::GetSizeMax (&cbSize);

	if (FAILED(hr)) return hr;

ULARGE_INTEGER liOwnSize;

	liOwnSize.QuadPart = sizeof(LONG) + m_caSelInfo.m_strObjProp.size()+1;

	liOwnSize.QuadPart = liOwnSize.QuadPart + cbSize.QuadPart;
	*pcbSize = liOwnSize;
	return S_OK;
}

STDMETHODIMP CClsfyPropAct::InitNew (void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_caSelInfo.m_strObjProp.empty();
	m_fIsInitialized = true;
	m_fIsDirty = false;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CClsfyPropAct::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags)  
{
	if (NULL == pcBuffer) return E_POINTER;

	m_strDesc = pcBuffer;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
STDMETHODIMP CClsfyPropAct::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyAction::Load (pBag, pLog));

	m_caSelInfo.m_strObjProp.empty();
	m_caSelInfo.m_fSelectAll = FALSE;

// ClassifyBy=
CComVariant vValue;
HRESULT hr = pBag -> Read (CComBSTR("ClassifyBy"), &vValue, pLog);

	if (S_OK == hr && SUCCEEDED(vValue.ChangeType(VT_BSTR)))
	{
		m_caSelInfo.m_strObjProp = OLE2A(V_BSTR(&vValue));
	}

// UseAll=
	vValue.Clear();
	hr = pBag -> Read (CComBSTR("UseAll"), &vValue, pLog);
	if (S_OK == hr && SUCCEEDED(vValue.ChangeType (VT_BOOL)))
	{
		m_caSelInfo.m_fSelectAll = V_BOOL(&vValue) ? true : false;
	}

	if (NULL == m_pCfgDlg)		// Dialog ist noch nicht initialisiert
		m_fHasInitData = true;
	else
		m_pCfgDlg -> SetSelectedInfo (&m_caSelInfo);
	return S_OK;
}
