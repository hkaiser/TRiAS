// PropertyAction, welche Objekte auf einen auszuwählenden Ident umklassifiziert
// File: MODIDPRP.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <xtsnguid.h>
#include <eonrguid.h>

#include <pdataobj.hxx>
#include <funcs03.h>

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

extern char g_pDLLName[];		// dieser Modul

// 0E54C9ED-20DE-11CF-BA55-00AA0018497C	
// DEFINE_GUID(CLSID_ModifyIdent, 0x0E54C9EDL, 0x20DE, 0x11CF, 0xBA, 0x55, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// const char c_cbModPrpName[] = "CLSPROP_ROOT\\TRiAS® (allgemein)\\Modifikation der Objektklasse";

CModIDPropAct :: CModIDPropAct (void)
{
	m_pCfgDlg = NULL;
	m_fIsDirty = false;
	m_fIsInitialized = false;
}

CModIDPropAct :: ~CModIDPropAct (void)
{
	DELETE(m_pCfgDlg);
}

///////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions 
STDMETHODIMP CModIDPropAct::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Namen der Property kopieren
		ResourceFile RF (g_pDLLName);
		ResString resPropInfo (ResID (IDS_PROPINFO_MODIDENT, &RF), 64);
		ULONG ulLen = tmin ((size_t)(wLen-1), strlen(resPropInfo));

			strncpy (pBuffer, resPropInfo, ulLen);
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
			    DWORD dwFlags, LPCSTR pcDesc, UINT *puiCnt)
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
		m_pCfgDlg = CModifyIdentDlg::CreateInstance (
				ResID (IDD_MODIFYIDS_WIZ, &RF), cbCaption, dwFlags);
		if (NULL == m_pCfgDlg) throw E_OUTOFMEMORY;

	//
	// Achtung MFC-Falle !
	// Normalerweise müßte an dieser Stelle lpfnAddPage mit unserem 
	// HPROPERTYPAGE gerufen werden, wir aber wissen (darf man das ?), daß
	// sich hinter dem eigentlich durchzureichendem lParam der Pointer auf
	// unsern PropertySheet verbirgt.
	//
		if (UINT_MAX == ((CPropertySheet *)lParam) -> AddPage (m_pCfgDlg))
			throw E_UNEXPECTED;

		if (puiCnt) *puiCnt = 1;

	} catch (HRESULT hr_result) {
		DELETE (m_pCfgDlg);
		if (puiCnt) *puiCnt = 0;
		return hr_result;
	}
	
return NOERROR;
}

STDMETHODIMP CModIDPropAct::DoAction (IDataObject *pIDataObj, DWORD)
{
WEnumLONG IEnumObj;
HRESULT hr = GetEnumLONGData (pIDataObj, CLSID_EnumObjectsByNumber, IEnumObj.ppi());

	if (FAILED(hr)) return hr;

return m_pCfgDlg -> SetEnumLONG (IEnumObj);
}

STDMETHODIMP CModIDPropAct::EndAction (DWORD, IDataObject **ppDataObj)
{
WEnumLONG IEnumObj;
HRESULT hr = m_pCfgDlg -> GetEnumLONG (IEnumObj.ppi());
	
	if (FAILED(hr)) return hr;

// DataObject generieren
	*ppDataObj = NULL;

	try {
	WDataObject IDO;
	
		hr = DataObjectCreateInstance (NULL, IID_IDataObject, IDO.ppv());
		if (FAILED(hr)) throw hr;

	HRESULT hr2 = SetEnumLONGData (IEnumObj, CLSID_EnumObjectsByNumber, IDO);
		
		if (FAILED(hr2)) throw hr2;

		*ppDataObj = IDO.detach();

	} catch (HRESULT hr_result) {
		DELETE (m_pCfgDlg);	// DialogPage freigeben
		return hr_result;
	}

// letzter Enumerator/PropAction erzeugt lediglich eine Objektmenge
	DELETE (m_pCfgDlg);		// DialogPage freigeben

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
	return m_fIsDirty;
}

STDMETHODIMP CModIDPropAct::Load (LPSTREAM pStm)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

	m_fIsInitialized = true;
	m_fIsDirty = false;

return NOERROR;
}

STDMETHODIMP CModIDPropAct::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	return E_NOTIMPL;
}

STDMETHODIMP CModIDPropAct::GetSizeMax (ULARGE_INTEGER FAR* pcbSize)
{
	return E_NOTIMPL;
}

STDMETHODIMP CModIDPropAct::InitNew (void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_fIsInitialized = true;
	m_fIsDirty = false;

return NOERROR;
}
