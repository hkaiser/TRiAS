// PropertyAction, welche Objekte aus RechercheFenster auswählt und zusammenstellt
// File: SELOBWND.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <xtsnguid.h>
#include <eonrguid.h>
#include <statguid.h>

#include <pdataobj.hxx>
#include <funcs03.h>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "selobwnd.hxx"

///////////////////////////////////////////////////////////////////////////////
// Min-Funktion, da Macro aus stdlib offensichtlich überladen ist
template<class T>
inline T tmin (T a, T b) { return (a > b) ? b : a; }

///////////////////////////////////////////////////////////////////////////////
// benötigte InterfaceWrapper
DefineSmartInterface(DataObject);
DefineEnumIIDWrapper(LONG);
DefineSmartEnumerator(LONG);

extern char g_pDLLName[_MAX_PATH];		// dieser Modul

// 0E54C9EA-20DE-11CF-BA55-00AA0018497C	
// DEFINE_GUID(CLSID_SelectFromObjectWindow, 0x0E54C9EAL, 0x20DE, 0x11CF, 0xBA, 0x55, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// 'CLSPROP_ROOT\TRiAS® (allgemein)\Objektauswahl aus Recherchefenster'

CSelObjWndPropAct :: CSelObjWndPropAct (void)
{
	m_pCfgDlg = NULL;
	m_fIsDirty = false;
	m_fIsInitialized = false;

	m_hWnd = NULL;
	m_dwFlags = 0L;
	m_fHasInitData = false;

	try {
	ResourceFile RF (g_pDLLName);
	ResString resPropInfo (ResID (IDS_PROPINFO_OBJWND, &RF), 64);

		m_strDesc = resPropInfo;
	} catch (...) {
		TX_ASSERT(false);
	}
}

CSelObjWndPropAct :: ~CSelObjWndPropAct (void)
{
	DELETE_OBJ (m_pCfgDlg);
}

///////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions 
STDMETHODIMP CSelObjWndPropAct::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
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
	if (pdwFlags) *pdwFlags = PROPCAPS_ACTION_SOURCE;

return NOERROR;
}

STDMETHODIMP CSelObjWndPropAct::HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Beschreibung übergeben
		ResourceFile RF (g_pDLLName);
		ResString resHelp (ResID (IDS_HELPDESC_OBJWND, &RF), 128);
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
STDMETHODIMP CSelObjWndPropAct::AddConfigPages (
				LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, 
			    LPCSTR pcDesc, UINT *puiCnt)
{
// wenn lediglich ein Objekt in einem Fenster selektiert ist,
// dann Dialog nicht anzeigen
	if (1 == DEX_ActiveObjectsCount()) {
		DELETE_OBJ(m_pCfgDlg);	// evtl. vorherigen freigeben

		if (puiCnt) *puiCnt = 0;		// keine Page !
		return S_OK;
	}

// Dialog erzeugen
	try {
	char cbCaption[_MAX_PATH];
	ResourceFile RF (g_pDLLName);

		if (NULL != pcDesc)		// Caption ist gegeben
			strcpy (cbCaption, pcDesc);
		else	// von zugehöriger ClassProperty unseren Namen besorgen
			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
		DELETE_OBJ(m_pCfgDlg);	// evtl. vorherigen freigeben
		m_pCfgDlg = CSelectObjWndDlg::CreateInstance (this, 
						ResID(IDD_SELECTOBJWND_WIZ, &RF), cbCaption);
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
			m_pCfgDlg -> SetHWND (m_hWnd);
			m_pCfgDlg -> SetFlags (m_dwFlags);
		}

	// wir haben eine (1) Page hinzugefügt
		if (puiCnt) *puiCnt = 1;

	} catch (_com_error& hr_result) {
		DELETE_OBJ (m_pCfgDlg);
		if (puiCnt) *puiCnt = 0;
		return _COM_ERROR(hr_result);
	}
	
return NOERROR;
}

STDMETHODIMP CSelObjWndPropAct::PreConfigPages (IDataObject *pIDataObj, DWORD dwFlags)
{
HWND hORWnd = NULL;

	if (NULL != pIDataObj)		// evtl. RechercheFensterhandle besorgen
		GetHWNDData (pIDataObj, &hORWnd);

	m_hWnd = hORWnd;
	m_dwFlags = dwFlags;
	m_fHasInitData = true;

return NOERROR;
}

STDMETHODIMP CSelObjWndPropAct::EndAction (DWORD, IDataObject **ppDataObj)
{
	*ppDataObj = NULL;

WEnumLONG IEnumObj;
HRESULT hr = S_OK;

	if (NULL == m_pCfgDlg) {		// Page nicht angezeigt
		try {
		WEnumLONG IObjs (CLSID_EnumObjectsByNumber);	// Enumerator generieren
			// JG 980916
			SetMaxTicks(1);			// ProgInd so gut es eben geht handeln

			if (!FillTrees (true, false, m_hWnd, IObjs))
				_com_issue_error(E_FAIL);

			IEnumObj = IObjs;
		} catch (_com_error& hr) {
			return _COM_ERROR(hr);
		}
	} 
	else
	{
		m_pCfgDlg -> SetAction(this);	// JG 980916
		hr = m_pCfgDlg -> GetEnumLONG (IEnumObj.ppi());
	}
	if (FAILED(hr)) return hr;
	if (!IEnumObj) return NOERROR;

// DataObject generieren, welches Info's über unser Ereignis enthält
	*ppDataObj = NULL;
	try {
	WDataObject IDO;
	
		hr = DataObjectCreateInstance (NULL, IID_IDataObject, IDO.ppv());
		if (FAILED(hr)) _com_issue_error(hr);

	// schreiben des EnumLONG ins DataObject
	HRESULT hr2 = SetEnumLONGData (IEnumObj, IDO);

		if (FAILED(hr2)) _com_issue_error(hr2);

	// Resultat an nächste PropertyAction weiterzureichen
		*ppDataObj = IDO.detach();

	} catch (_com_error& hr_result) {
		DELETE_OBJ (m_pCfgDlg);	// DialogPage freigeben
		return _COM_ERROR(hr_result);
	}

// S_FALSE heißt, daß GetEnumLONG nicht mehr gerufen werden muß
	if (S_FALSE != GetScode(hr)) {	// letzter Enumerator
		DELETE_OBJ (m_pCfgDlg);	// DialogPage freigeben

	// JG 980916
		TickToEnd();			// ProgInd handeln
	}

return hr;
}

///////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CSelObjWndPropAct::GetClassID (LPCLSID lpClassID)
{
	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_SelectFromObjectWindow;
	return NOERROR;
}

// IPersistStreamInit methods
STDMETHODIMP CSelObjWndPropAct::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CSelObjWndPropAct::Load (LPSTREAM pStm)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

HRESULT hr = CPropertyAction::Load (pStm);

	if (FAILED(hr)) return hr;

	m_fIsInitialized = true;
	m_fIsDirty = false;

return NOERROR;
}

STDMETHODIMP CSelObjWndPropAct::InitNew (void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_fIsInitialized = true;
	m_fIsDirty = false;

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CSelObjWndPropAct::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags)  
{
	if (NULL == pcBuffer) return E_POINTER;

	m_strDesc = pcBuffer;
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CSelObjWndPropAct::SetDirty (bool fDirty) { m_fIsDirty = fDirty; }
