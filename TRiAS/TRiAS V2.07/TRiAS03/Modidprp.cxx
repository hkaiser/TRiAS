// PropertyAction, welche Objekte auf einen auszuwählenden Ident umklassifiziert
// File: MODIDPRP.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <int64.h>
#include <xtsnguid.h>
#include <eonrguid.h>
#include <statguid.h>

#include <pdataobj.hxx>
#include <funcs03.h>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Strings.h"
#include "DataHelp.h"
#include "modidprp.hxx"

///////////////////////////////////////////////////////////////////////////////
// Min-Funktion, da Macro aus stdlib offensichtlich überladen ist
template<class T>
inline T tmin (T a, T b) { return (a > b) ? b : a; }

///////////////////////////////////////////////////////////////////////////////
// benötigte InterfaceWrapper
DefineSmartInterface(DataObject);
DefineEnumIIDWrapper(LONG);		// CIID_LONGEnum
DefineSmartEnumerator(LONG);	// WEnumLONG

extern char g_pDLLName[_MAX_PATH];		// dieser Modul

// 0E54C9ED-20DE-11CF-BA55-00AA0018497C	
// DEFINE_GUID(CLSID_ModifyIdent, 0x0E54C9EDL, 0x20DE, 0x11CF, 0xBA, 0x55, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// const char c_cbModPrpName[] = "CLSPROP_ROOT\\TRiAS® (allgemein)\\Modifikation der Objektklasse";

CModIDPropAct :: CModIDPropAct (void)
{
	m_pCfgDlg = NULL;
	m_fIsDirty = false;
	m_fIsInitialized = false;

	m_fHasInitData = false;
	m_fAddToView = false;
	m_lIdent = 0L;
	
	m_fCheckMode = FALSE;
	m_fCheckModeChecked = FALSE;

	try {
	ResourceFile RF (g_pDLLName);
	ResString resPropInfo (ResID (IDS_PROPINFO_MODIDENT, &RF), 64);

		m_strDesc = resPropInfo;
	} catch (...) {
		TX_ASSERT(false);
	}
}

CModIDPropAct :: ~CModIDPropAct (void)
{
	DELETE_OBJ(m_pCfgDlg);
}

///////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions 
STDMETHODIMP CModIDPropAct::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Namen der Property kopieren
		ULONG ulLen = tmin ((size_t)(wLen-1), m_strDesc.length());

			strncpy (pBuffer, m_strDesc.c_str(), ulLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return E_FAIL;
	}

// wenn gewünscht, Flags übergeben
	if (pdwFlags) {
		*pdwFlags = PROPCAPS_ACTION_SINK_MULTI|PROPCAPS_ACTION_SOURCE|
					PROPCAPS_ACTION_MUSTREPAINT|PROPCAPS_ACTION_MUSTREPAINTLEGEND;
	}

return NOERROR;
}

STDMETHODIMP CModIDPropAct::HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Beschreibung übergeben
		ResourceFile RF (g_pDLLName);
		ResString resHelp (ResID (IDS_HELPDESC_MODIDENT, &RF), 128);
		ULONG ulLen = tmin ((size_t)(wLen-1), strlen(resHelp));

			strncpy (pBuffer, resHelp, ulLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return E_FAIL;
	}

// HelpFileInfo übergeben
	if (pHelpFile) pHelpFile[0] = '\0';
	if (pulHelpCtx) *pulHelpCtx = 0L;
	
return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods 
STDMETHODIMP CModIDPropAct::AddConfigPages (
				LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, 
			    LPCSTR pcDesc, UINT *puiCnt)
{
char cbCaption[128];

	try {
		if (NULL != pcDesc)		// Caption ist gegeben
			strcpy (cbCaption, pcDesc);
		else	// von zugehöriger ClassProperty unseren Namen besorgen
			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
	ResourceFile RF (g_pDLLName);

		DELETE_OBJ(m_pCfgDlg);	// evtl. vorherigen freigeben
		m_pCfgDlg = CModifyIdentDlg::CreateInstance (this, ResID (IDD_MODIFYIDS_WIZ, &RF), cbCaption);
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
			m_pCfgDlg -> SetSelectedIdent (m_lIdent);
			m_pCfgDlg -> SetAddToView (m_fAddToView);
			m_pCfgDlg -> SetCheckMode (m_fCheckMode, m_fCheckModeChecked);
		}

		if (NULL != puiCnt) 
			*puiCnt = IsNoShow() ? 0 : 1;

	} catch (_com_error& hr_result) {
		DELETE_OBJ (m_pCfgDlg);
		if (puiCnt) *puiCnt = 0;
		return _COM_ERROR(hr_result);
	}
	
return NOERROR;
}

STDMETHODIMP CModIDPropAct::PreConfigPages (IDataObject *, DWORD dwFlags)
{
	m_pCfgDlg -> SetFlags (dwFlags);
	return NOERROR;
}

STDMETHODIMP CModIDPropAct::DoAction (IDataObject *pIDataObj, DWORD)
{
WEnumLONG IEnumObj;
HRESULT hr = GetEnumLONGData (pIDataObj, IEnumObj.ppi());

	if (FAILED(hr)) return hr;

	//
	// JG
	// hier findet die Verarbeitung statt
	m_pCfgDlg -> SetAction(this);	
	return m_pCfgDlg -> SetEnumLONG (IEnumObj);
}

STDMETHODIMP CModIDPropAct::EndAction (DWORD, IDataObject **ppDataObj)
{
	if (NULL == ppDataObj) return E_POINTER;

	m_pCfgDlg -> GetCheckMode (m_fCheckMode, m_fCheckModeChecked);

HRESULT hr = S_OK;
WEnumLONG IEnumObj;
	
	if (!m_fCheckMode || m_fCheckModeChecked) 
		hr = m_pCfgDlg -> GetEnumLONG (IEnumObj.ppi());			// verarbeiten
	else
		hr = m_pCfgDlg -> GetInputEnumLONG (IEnumObj.ppi());	// lediglich weiterreichen
	if (FAILED(hr)) return hr;

// DataObject generieren
	*ppDataObj = NULL;
	try {
	WDataObject IDO;
	
		hr = DataObjectCreateInstance (NULL, IID_IDataObject, IDO.ppv());
		if (FAILED(hr)) _com_issue_error(hr);

	HRESULT hr2 = SetEnumLONGData (IEnumObj, IDO);
		
		if (FAILED(hr2)) _com_issue_error(hr2);

		*ppDataObj = IDO.detach();

	} catch (_com_error& hr_result) {
		hr = _COM_ERROR(hr_result);
	// hier durchfallen
	}

// letzter Enumerator/PropAction erzeugt lediglich eine Objektmenge
	m_lIdent = m_pCfgDlg -> GetSelectedIdent();
	m_fAddToView = m_pCfgDlg -> GetAddToView();

	DELETE_OBJ (m_pCfgDlg);		// DialogPage freigeben

	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CModIDPropAct::GetClassID (LPCLSID lpClassID)
{
	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_ModifyIdent;
	return NOERROR;
}

// IPersistStreamInit methods
STDMETHODIMP CModIDPropAct::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CModIDPropAct::Load (LPSTREAM pStm)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

// zuerst Bezeichner einlesen
HRESULT hr = CPropertyAction::Load (pStm);

	if (FAILED(hr)) return hr;

// dann selektierte Info der letzten Auswahl
LONG lIdent = 0L;
LONG lAddToView = 0L;

	hr = pStm -> Read (&lIdent, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;
	
	hr = pStm -> Read (&lAddToView, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;


	TX_ASSERT(sizeof(long) == sizeof(BOOL));
	RETURN_FAILED_HRESULT(LoadLong(pStm, (long &)m_fCheckMode));
	RETURN_FAILED_HRESULT(LoadLong(pStm, (long &)m_fCheckModeChecked));

	if (NULL == m_pCfgDlg) {
	// Dialog ist noch nicht initialisiert
		m_lIdent = lIdent;
		m_fAddToView = lAddToView ? true : false;
		m_fHasInitData = true;
	} else {
		m_pCfgDlg -> SelectIdent (lIdent);
		m_pCfgDlg -> SetAddToView (lAddToView ? true : false);
		m_pCfgDlg -> SetCheckMode (m_fCheckMode, m_fCheckModeChecked);
	}
	
	m_fIsInitialized = true;
	m_fIsDirty = false;

return NOERROR;
}

STDMETHODIMP CModIDPropAct::Save (LPSTREAM pStm, BOOL fClearDirty)
{
// zuerst Bezeichner wegschreiben
HRESULT hr = CPropertyAction::Save (pStm, fClearDirty);

	if (FAILED(hr)) return hr;

// dann selektierte Info der letzten Auswahl
	hr = pStm -> Write (&m_lIdent, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;

LONG lAddToView = m_fAddToView ? true : false;

	hr = pStm -> Write (&lAddToView, sizeof(LONG), NULL);
	if (FAILED(hr)) return hr;

	RETURN_FAILED_HRESULT(SaveLong(pStm, m_fCheckMode));
	RETURN_FAILED_HRESULT(SaveLong(pStm, m_fCheckModeChecked));

	if (fClearDirty) m_fIsDirty = false;
	return NOERROR;
}

STDMETHODIMP CModIDPropAct::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) return E_POINTER;

ULARGE_INTEGER cbSize;
HRESULT hr = CPropertyAction::GetSizeMax (&cbSize);

	if (FAILED(hr)) return hr;

LARGE liOwnSize (UINT(4*sizeof(LONG)));

	liOwnSize = liOwnSize + LARGE(cbSize);
	*pcbSize = liOwnSize;
	
	return S_OK;
}

STDMETHODIMP CModIDPropAct::InitNew (void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_lIdent = 0L;
	m_fAddToView = false;
	m_fHasInitData = false;

	m_fIsInitialized = true;
	m_fIsDirty = false;

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CModIDPropAct::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags)  
{
	if (NULL == pcBuffer) return E_POINTER;

	m_strDesc = pcBuffer;
	return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
STDMETHODIMP CModIDPropAct::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyAction::Load (pBag, pLog));

	m_lIdent = 0L;
	m_fAddToView = false;

// sonstige Werte Analysieren
CComVariant vModifyTo;
HRESULT hr = pBag -> Read (CComBSTR("ModifyTo"), &vModifyTo, pLog);

	if (S_OK == hr && SUCCEEDED(vModifyTo.ChangeType(VT_BSTR))) {
	ULONG ulIdent = 0;

		hr = IdentFromClass (OLE2A(V_BSTR(&vModifyTo)), &ulIdent, FALSE);
		if (S_OK == hr)
			m_lIdent = ulIdent;
	}

// CheckMode=
CComVariant vParam;

	hr = pBag -> Read (CComBSTR(g_cbCheckMode), &vParam, pLog);
	if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_BOOL)))
	{
		m_fCheckMode = V_BOOL(&vParam) ? TRUE : FALSE;
	}

// Checked=
	if (m_fCheckMode) {
		vParam.Clear();
		hr = pBag -> Read (CComBSTR(g_cbCheckModeChecked), &vParam, pLog);
		if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_BOOL)))
		{
			m_fCheckModeChecked = V_BOOL(&vParam) ? TRUE : FALSE;
		}
	} else
		m_fCheckModeChecked = FALSE;

CComVariant vAddToView;

	hr = pBag -> Read (CComBSTR("AddToView"), &vAddToView, pLog);
	if (S_OK == hr && SUCCEEDED(vAddToView.ChangeType (VT_BOOL)))
		m_fAddToView = V_BOOL(&vAddToView) ? true : false;

	m_fHasInitData = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CModIDPropAct::SetDirty (bool fDirty) { m_fIsDirty = fDirty; }
