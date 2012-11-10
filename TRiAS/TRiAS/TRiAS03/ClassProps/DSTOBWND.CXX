// PropertyAction, welche Objekte in RechercheFenster anzeigt -----------------
// File: DSTOBWND.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <xtsnguid.h>
#include <eonrguid.h>

#include <pdataobj.hxx>
#include <funcs03.h>

#include "dstobwnd.hxx"

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

extern char g_pDLLName[];		// dieser Modul


CDestObjWndPropAct :: CDestObjWndPropAct (void)
{
	m_pCfgDlg = NULL;
	m_fIsDirty = false;
	m_fIsInitialized = false;

	try {
	ResourceFile RF (g_pDLLName);
	ResString resPropInfo (ResID (IDS_PROPINFO_ORWNDDEST, &RF), 64);

		m_strDesc = resPropInfo;
	} catch (...) {
		TX_ASSERT(false);
	}
}

CDestObjWndPropAct :: ~CDestObjWndPropAct (void)
{
	DELETE(m_pCfgDlg);
}

// *** IClassProperty specific functions *** ----------------------------------
STDMETHODIMP CDestObjWndPropAct :: GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Namen der Property kopieren
		ResString resPropInfo (ResID (IDS_PROPINFO_DESTOBJWND, &g_pTE -> RF()), 64);
		ULONG ulLen = tmin ((size_t)(wLen-1), strlen(resPropInfo));

			strncpy (pBuffer, resPropInfo, ulLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return ResultFromScode (E_FAIL);
	}

// wenn gewünscht, Flags übergeben
	if (pdwFlags) *pdwFlags = PROPCAPS_ACTION_SINK;

return NOERROR;
}

STDMETHODIMP CSelIDPropAct::HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Beschreibung übergeben
		ResourceFile RF (g_pDLLName);
		ResString resHelp (ResID (IDS_HELPDESC_DESTOBJWND, &RF), 128);
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

// *** IPropertyAction methods ------------------------------------------------
STDMETHODIMP CDestObjWndPropAct::AddConfigPages (
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
		m_pCfgDlg = CDestObjWndDlg::CreateInstance (
				ResID (IDD_DESTOBJWND_WIZ, &RF), cbCaption, dwFlags);
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

STDMETHODIMP CDestObjWndPropAct::DoAction (IDataObject *pIDataObj, DWORD)
{
WEnumLONG IEnumObj;
HRESULT hr = GetEnumLONGData (pIDataObj, CLSID_EnumObjectsByNumber, IEnumObj.ppi());

	if (FAILED(hr)) return hr;
	return m_pCfgDlg -> SetEnumLONG (IEnumObj);
}

STDMETHODIMP CDestObjWndPropAct::EndAction (DWORD, IDataObject **ppDataObj)
{
	DELETE (m_pCfgDlg);	// DialogPage freigeben
	*ppDataObj = NULL;	// kein output

return NOERROR;		// nicht nochmal rufen
}

///////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit specific functions 
STDMETHODIMP CSelIDPropAct::InitNew (void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_fIsInitialized = true;
	m_fIsDirty = false;

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CSelIDPropAct::GetClassID (LPCLSID lpClassID)
{
	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_DestinationObjectWindow;
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPersistStream methods
STDMETHODIMP CSelIDPropAct::IsDirty (void)
{
	return m_fIsDirty;
}

STDMETHODIMP CSelIDPropAct::Load (LPSTREAM pStm)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

HRESULT hr = CPropertyAction::Load (pStm);

	if (FAILED(hr)) return hr;

	m_fIsInitialized = true;
	m_fIsDirty = false;

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CSelIDPropAct::SetPropName (LPCSTR pcBuffer) 
{
	if (NULL == pcBuffer) return E_POINTER;

	m_strDesc = pcBuffer;
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CSelIDPropAct::SetDirty (bool fDirty) { m_fIsDirty = fDirty; }
