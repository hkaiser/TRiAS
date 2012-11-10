// PropertyAction, welche Textobjekte mit Objekteigenschaft erzeugt
// File: TXTOBPRP.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <int64.h>
#include <xtsnguid.h>
#include <eonrguid.h>

#include <pdataobj.hxx>
#include <funcs03.h>

#include "strings.h"
#include "DataHelp.h"
#include "TxtObPrp.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

// 079638DF-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(CLSID_CreateTextObjects, 0x079638DFL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// const char c_cbModPrpName[] = "CLSPROP_ROOT\\TRiAS® (allgemein)\\Erzeugen von Textobjekten über Objekteigenschaft";

CCreateTextObjectsPropAct :: CCreateTextObjectsPropAct (void)
{
	m_pCfgDlg = NULL;
	m_fIsDirty = false;
	m_fIsInitialized = false;
	m_fHasInitData = false;

	m_fCreateDependend = false;
	m_fDeleteExistent = false;
	m_fDoNotMove = false;

	try {
	ResourceFile RF (g_pDLLName);
	ResString resPropInfo (ResID (IDS_PROPINFO_CREATETEXT, &RF), 64);

		m_strDesc = resPropInfo;
	} catch (...) {
		TX_ASSERT(false);
	}
}

CCreateTextObjectsPropAct :: ~CCreateTextObjectsPropAct (void)
{
	DELETE(m_pCfgDlg);
}

///////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions 
STDMETHODIMP CCreateTextObjectsPropAct::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
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

STDMETHODIMP CCreateTextObjectsPropAct::HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Beschreibung übergeben
		ResourceFile RF (g_pDLLName);
		ResString resHelp (ResID (IDS_HELPDESC_CREATETEXT, &RF), 128);
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
	
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods 
STDMETHODIMP CCreateTextObjectsPropAct::AddConfigPages (
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

		DELETE(m_pCfgDlg);	// evtl. vorherigen freigeben
		m_pCfgDlg = CCreateTextObjectsDlg::CreateInstance (this, ResID (IDD_MODIFYIDS_WIZ, &RF), cbCaption);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);
	//
	// Achtung MFC-Falle !
	// Normalerweise müßte an dieser Stelle lpfnAddPage mit unserem 
	// HPROPERTYPAGE gerufen werden, wir aber wissen (darf man das ?), daß
	// sich hinter dem eigentlich durchzureichendem lParam der Pointer auf
	// unsern PropertySheet verbirgt.
	//
		if (UINT_MAX == ((CPropertySheet *)lParam) -> AddPage (m_pCfgDlg))
			_com_issue_error(E_UNEXPECTED);

		if (m_fHasInitData) {
			m_pCfgDlg -> SetObjProp (m_strObjProp);
			m_pCfgDlg -> SetCreateDependend (m_fCreateDependend);
			m_pCfgDlg -> SetDeleteExistent (m_fDeleteExistent);
			m_pCfgDlg -> SetReplaceExistent (m_fDoNotMove);
		}

		if (puiCnt) *puiCnt = 1;

	} catch (_com_error& hr_result) {
		DELETE (m_pCfgDlg);
		if (puiCnt) *puiCnt = 0;
		return _COM_ERROR(hr_result);
	}
	
return NOERROR;
}

STDMETHODIMP CCreateTextObjectsPropAct::PreConfigPages (IDataObject *, DWORD dwFlags)
{
	m_pCfgDlg -> SetFlags (dwFlags);
	return NOERROR;
}

STDMETHODIMP CCreateTextObjectsPropAct::DoAction (IDataObject *pIDataObj, DWORD)
{
WEnumLONG IEnumObj;
HRESULT hr = GetEnumLONGData (pIDataObj, IEnumObj.ppi());

	if (S_OK != hr) 
		return S_OK;		// nothing to do

WEnumObjectsByNumber Objects;

	return m_pCfgDlg -> SetEnumLONG (Objects);
}

STDMETHODIMP CCreateTextObjectsPropAct::EndAction (DWORD, IDataObject **ppDataObj)
{
	if (NULL == ppDataObj) return E_POINTER;

WEnumObjectsByNumber Objects;
HRESULT hr = m_pCfgDlg -> GetEnumLONG (Objects.ppi());
	
	if (FAILED(hr)) return hr;

// DataObject generieren
	*ppDataObj = NULL;

	try {
	WDataObject IDO (CLSID_DataTransferObject);
	WEnumLONG IEnumObj (Objects);
	
		THROW_FAILED_HRESULT(SetEnumLONGData (IEnumObj, IDO));
		*ppDataObj = IDO.detach();

	} catch (_com_error& hr_result) {
		hr = _COM_ERROR(hr_result);
	// hier durchfallen
	}

// letzter Enumerator/PropAction erzeugt lediglich eine Objektmenge
	m_strObjProp = m_pCfgDlg -> GetObjProp();
	m_fCreateDependend = m_pCfgDlg -> GetCreateDependend();
	m_fDeleteExistent = m_pCfgDlg -> GetDeleteExistent();
	m_fDoNotMove = m_pCfgDlg -> GetDoNotMove();

	DELETE (m_pCfgDlg);		// DialogPage freigeben

	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CCreateTextObjectsPropAct::GetClassID (LPCLSID lpClassID)
{
	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_CreateTextObjects;
	return NOERROR;
}

// IPersistStreamInit methods
STDMETHODIMP CCreateTextObjectsPropAct::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CCreateTextObjectsPropAct::Load (LPSTREAM pStm)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

// zuerst Bezeichner einlesen
HRESULT hr = CPropertyAction::Load (pStm);

	if (FAILED(hr)) return hr;

// dann selektierte Info der letzten Auswahl
os_string strObjProp;
LONG lCreateDependend = 0L;
LONG lDeleteExistent = 0L;
LONG lDoNotMove = 0L;

	hr = LoadString(strObjProp);
	if (FAILED(hr)) return hr;
	
	hr = LoadLong (pStm, lCreateDependend);
	if (FAILED(hr)) return hr;
	hr = LoadLong (pStm, lDeleteExistent);
	if (FAILED(hr)) return hr;
	hr = LoadLong (pStm, lDoNotMove);
	if (FAILED(hr)) return hr;
	
	if (NULL == m_pCfgDlg) {
	// Dialog ist noch nicht initialisiert
		m_strObjProp = strObjProp;
		m_fCreateDependend = lCreateDependend ? true : false;
		m_fDeleteExistent = lDeleteExistent ? true : false;
		m_fDoNotMove = lDoNotMove ? true : false;
	} else {
		m_pCfgDlg -> SetObjProp (strObjProp);
		m_pCfgDlg -> SetCreateDependend (lCreateDependend ? true : false);
		m_pCfgDlg -> SetDeleteExistent (lDeleteExistent ? true : false);
		m_pCfgDlg -> SetDoNotMove (lDoNotMove ? true : false);
	}
	
	m_fIsInitialized = true;
	m_fIsDirty = false;

	return S_OK;
}

STDMETHODIMP CCreateTextObjectsPropAct::Save (LPSTREAM pStm, BOOL fClearDirty)
{
// zuerst Bezeichner wegschreiben
HRESULT hr = CPropertyAction::Save (pStm, fClearDirty);

	if (FAILED(hr)) return hr;

// dann selektierte Info der letzten Auswahl
LONG lCreateDependend = m_fCreateDependend;
LONG lDeleteExistent = m_fDeleteExistent;
LONG lDoNotMove = m_fDoNotMove;

	hr = SaveString (pStm, m_strObjProp);
	if (FAILED(hr)) return hr;

	hr = SaveLong (pStm, lCreateDependend);
	if (FAILED(hr)) return hr;
	hr = SaveLong (pStm, lDeleteExistent);
	if (FAILED(hr)) return hr;
	hr = SaveLong (pStm, lDoNotMove);
	if (FAILED(hr)) return hr;

	if (fClearDirty) m_fIsDirty = false;
	return NOERROR;
}

STDMETHODIMP CCreateTextObjectsPropAct::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) return E_POINTER;

ULARGE_INTEGER cbSize;
HRESULT hr = CPropertyAction::GetSizeMax (&cbSize);

	if (FAILED(hr)) return hr;

LARGE liOwnSize (UINT(3*sizeof(LONG)));

	liOwnSize = liOwnSize + LARGE(GetSizeMax(m_strObjProp)) + LARGE(cbSize);
	*pcbSize = liOwnSize;
	
	return S_OK;
}

STDMETHODIMP CCreateTextObjectsPropAct::InitNew (void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_strObjProp = g_cbNil;
	m_fCreateDependend = false;
	m_fDeleteExistent = false;
	m_fDoNotMove = false;
	m_fHasInitData = false;

	m_fIsInitialized = true;
	m_fIsDirty = false;

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CCreateTextObjectsPropAct::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags)  
{
	if (NULL == pcBuffer) return E_POINTER;

	m_strDesc = pcBuffer;
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CCreateTextObjectsPropAct::SetDirty (bool fDirty) { m_fIsDirty = fDirty; }
