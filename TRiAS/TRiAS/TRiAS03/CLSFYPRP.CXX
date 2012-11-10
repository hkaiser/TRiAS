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

DefineSmartInterface(ClassProperty);

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
	
	m_caSelInfo.m_strObjProp.empty();
	m_caSelInfo.m_fSelectAll = true;
	m_caSelInfo.m_fIgnoreCase = false;
	m_caSelInfo.m_fMatchBOB = false;
	m_caSelInfo.m_iCntMatch = 0;

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

	// Kontext des Dialoges feststellen
	WClassProperty Cls;
	bool fChoice = false;

		if (SUCCEEDED(GetSite (IID_IClassProperty, Cls.ppv()))) {
		// Kontext ist entweder PropertyChoice oder PropertySequence 
		DWORD dwFlags = 0;

			if (SUCCEEDED(Cls -> GetPropInfo (NULL, 0, &dwFlags)))
				fChoice = (dwFlags & PROPCAPS_CONTAINER_IS_CHOICE) ? true : false;
		}

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
		m_pCfgDlg = CClassifyDlg::CreateInstance (this,
						ResID(fChoice ? IDD_OBJECTROP_WIZPP : IDD_OBJECTROP_WIZ, &RF), cbCaption, RF, Props);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);

	HPROPSHEETPAGE hPSP = this -> CreatePage(m_pCfgDlg);

		if (!IsNoShow() && !lpfnAddPage(hPSP, lParam))
			_com_issue_error(E_UNEXPECTED);

	HRESULT	hr = m_pCfgDlg -> SetSelectedInfo (&m_caSelInfo, IsNoShow());

		if (FAILED(hr))
			_com_issue_error(hr);

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

	if (S_OK != hr) 
		return S_OK;		// nothing to do

// JG980914: hier findet die Verarbeitung statt
	m_pCfgDlg -> SetAction(this);
	return m_pCfgDlg -> SetEnumLONG (IEnumObj);
}


STDMETHODIMP CClsfyPropAct::EndAction (DWORD, IDataObject **ppDataOut)
{
	*ppDataOut = NULL;

WEnumLONG IEnumObj;
os_string strObjProp;
long lPacket = 0;
HRESULT hr = m_pCfgDlg -> GetNextEnumLONG (IEnumObj.ppi(), strObjProp, lPacket);

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
		SetObjPropTemplate (m_caSelInfo.m_strObjProp, strObjProp, IDO);	// evtl Fehler ignorieren
		SetVariantData(CComVariant(strObjProp.c_str()), IDO, &c_feClassifyValue);

	// 3. Paketnummer mitgeben (Fehler ignorieren)
		SetPacketNumber(IDO, lPacket);

	// 4. Caption für ORWnd mitgeben
	ResourceFile RF (g_pDLLName);
	ResString resClfyCap (ResID (IDS_CLASSIFYCAPTION, &RF), 64);
	char cbBuffer[128];

		wsprintf (cbBuffer, resClfyCap, strObjProp.c_str());
		SetVariantData(CComVariant(cbBuffer), IDO, &c_feORWndCaption);
	
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
	RETURN_FAILED_HRESULT(LoadString (pStm, m_caSelInfo.m_strObjProp));
	RETURN_FAILED_HRESULT(LoadData (pStm, m_caSelInfo.m_fSelectAll));
	RETURN_FAILED_HRESULT(LoadData (pStm, m_caSelInfo.m_fIgnoreCase));
	RETURN_FAILED_HRESULT(LoadData (pStm, m_caSelInfo.m_fMatchBOB));
	RETURN_FAILED_HRESULT(LoadData (pStm, m_caSelInfo.m_iCntMatch));

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
	RETURN_FAILED_HRESULT(SaveString (pStm, m_caSelInfo.m_strObjProp));
	RETURN_FAILED_HRESULT(SaveData (pStm, m_caSelInfo.m_fSelectAll));
	RETURN_FAILED_HRESULT(SaveData (pStm, m_caSelInfo.m_fIgnoreCase));
	RETURN_FAILED_HRESULT(SaveData (pStm, m_caSelInfo.m_fMatchBOB));
	RETURN_FAILED_HRESULT(SaveData (pStm, m_caSelInfo.m_iCntMatch));

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

	liOwnSize.QuadPart = sizeof(LONG) + ::GetSizeMax(m_caSelInfo.m_strObjProp) + sizeof(int) + 3*sizeof(BOOL);

	liOwnSize.QuadPart = liOwnSize.QuadPart + cbSize.QuadPart;
	*pcbSize = liOwnSize;
	return S_OK;
}

STDMETHODIMP CClsfyPropAct::InitNew (void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_caSelInfo.m_strObjProp.empty();
	m_caSelInfo.m_fSelectAll = true;
	m_caSelInfo.m_fIgnoreCase = false;
	m_caSelInfo.m_fMatchBOB = false;
	m_caSelInfo.m_iCntMatch = 0;
	
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

// IgnoreCase=
	vValue.Clear();
	hr = pBag -> Read (CComBSTR("IgnoreCase"), &vValue, pLog);
	if (S_OK == hr && SUCCEEDED(vValue.ChangeType (VT_BOOL)))
	{
		m_caSelInfo.m_fIgnoreCase = V_BOOL(&vValue) ? true : false;
	}

// CountMatch=
	vValue.Clear();
	hr = pBag -> Read (CComBSTR("CountMatch"), &vValue, pLog);
	if (S_OK == hr && SUCCEEDED(vValue.ChangeType (VT_I4)))
	{
		m_caSelInfo.m_iCntMatch = V_I4(&vValue);
		if (m_caSelInfo.m_iCntMatch != 0)
			m_caSelInfo.m_fMatchBOB = true;
		else
			m_caSelInfo.m_fMatchBOB = false;
	}

	if (NULL == m_pCfgDlg)		// Dialog ist noch nicht initialisiert
		m_fHasInitData = true;
	else
		m_pCfgDlg -> SetSelectedInfo (&m_caSelInfo);
	return S_OK;
}
