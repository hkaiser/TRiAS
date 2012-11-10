// PropertyAction, welche Objekte aus RechercheFenster auswählt und zusammenstellt
// File: SELOBWND.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <xtsnguid.h>
#include <eonrguid.h>
#include <statguid.h>
#include <dirisole.h>

#include <pdataobj.hxx>
#include <funcs03.h>
#include <ipropseq.hxx>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Strings.h"
#include "DataHelp.h"
#include "selobwnd.hxx"

///////////////////////////////////////////////////////////////////////////////
// Min-Funktion, da Macro aus stdlib offensichtlich überladen ist
template<class T>
inline T tmin (T a, T b) { return (a > b) ? b : a; }

///////////////////////////////////////////////////////////////////////////////
// benötigte InterfaceWrapper
DefineSmartInterface(DataObject);
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(ObjectWithSite);
DefineSmartInterface(ClassProperty);
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

	m_rgMode = SELECTMODE_Selected;
	m_fCloseWhenReady = false;
	m_fDisableCloseWhenReady = false;
	m_fShowConfigAlways = false;
	m_fWindowWasShown = false;

	m_lMinWindowCount = 2;
	m_hWndIgnore = NULL;

	m_fMakePackets = false;
	m_ulPacket = 0;

	m_fAllowForOneObjectSelection = false;

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
	if (pdwFlags) 
		*pdwFlags = PROPCAPS_ACTION_SOURCE;
	return S_OK;
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
	
	return S_OK;
}

HRESULT CSelObjWndPropAct::GetWindowToIgnore (HWND *phWnd)
{
	COM_TRY {
	WDataObject DOCtx;
	WPropertyActionSequence Seq;
	HRESULT hr = WObjectWithSite(GetUnknown()) -> GetSite (IID_IPropertyActionSequence, Seq.ppv());

		if (SUCCEEDED(hr)) {
			THROW_FAILED_HRESULT(Seq -> GetSequenceContext (DOCtx.ppi()));

		HWND hWnd = NULL;

			if (S_OK != GetHWND (DOCtx, &c_feIgnoreWindow, &hWnd))
				return S_FALSE;
			if (NULL != phWnd)
				*phWnd = hWnd;
		}
		else {
		// während OleLoadFromStream ist context noch nicht bekannt, also 
		// gehen wir davon aus, daß kein Fenster ignoriert werden soll (im
		// Zweifelsfall zeigen wir das Auswahlfenster eben an)
			return S_FALSE;
		}

	} COM_CATCH;
	return S_OK;
}

long CSelObjWndPropAct::GetRealMinCount()
{
	// window is ignored only, if ShowConfigAlway isn't specified
	if (!m_fShowConfigAlways && S_OK == GetWindowToIgnore())
		return m_lMinWindowCount+1;
	return m_lMinWindowCount;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods 
STDMETHODIMP CSelObjWndPropAct::AddConfigPages (
				LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, 
			    LPCSTR pcDesc, UINT *puiCnt)
{
// wenn lediglich ein Objekt in einem Fenster selektiert ist,
// dann Dialog nicht anzeigen
	if (WindowShouldBeHidden()) 
	{
		m_fWindowWasShown = false;
		DELETE_OBJ(m_pCfgDlg);	// evtl. vorherigen freigeben
		if (puiCnt) 
			*puiCnt = 0;		// keine Page !
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

	// Kontext des Dialoges feststellen
	WClassProperty Cls;
	bool fChoice = false;

		if (SUCCEEDED(GetSite (IID_IClassProperty, Cls.ppv()))) {
		// Kontext ist entweder PropertyChoice oder PropertySequence 
		DWORD dwFlags = 0;

			if (SUCCEEDED(Cls -> GetPropInfo (NULL, 0, &dwFlags)))
				fChoice = (dwFlags & PROPCAPS_CONTAINER_IS_CHOICE) ? true : false;
		}

	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
	HWND hWndToIgnore = NULL;

		if (!m_fShowConfigAlways) {
		// ignore the given window only, if ShowConfigAlways isn't specified
			hWndToIgnore = m_hWndIgnore;		// preset to loaded value
			GetWindowToIgnore(&hWndToIgnore);	// overwrite with value from context
		}

		DELETE_OBJ(m_pCfgDlg);	// evtl. vorherigen freigeben
		m_pCfgDlg = CSelectObjWndDlg::CreateInstance (this, 
			ResID(fChoice ? IDD_SELECTOBJWND_WIZPP : IDD_SELECTOBJWND_WIZ, &RF), 
			cbCaption, hWndToIgnore);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);

	HPROPSHEETPAGE hPSP = this -> CreatePage(m_pCfgDlg);

		if (NULL == hPSP || !lpfnAddPage(hPSP, lParam))
			_com_issue_error(E_UNEXPECTED);

		if (m_fHasInitData) {
			m_pCfgDlg -> SetHWND (m_hWnd);
			m_pCfgDlg -> SetFlags (m_dwFlags);
			m_pCfgDlg -> SetMode (m_rgMode);
			m_pCfgDlg -> SetCloseWhenReady(m_fCloseWhenReady);
			m_pCfgDlg -> SetDisableCloseWhenReady(m_fDisableCloseWhenReady);
			m_pCfgDlg -> SetAllowForOneObjectSelection(m_fAllowForOneObjectSelection);
		}

	// wir haben eine (1) Page hinzugefügt
		if (puiCnt) *puiCnt = 1;

		m_fWindowWasShown = true;

	} catch (_com_error& hr_result) {
		DELETE_OBJ (m_pCfgDlg);
		if (puiCnt) *puiCnt = 0;
		return _COM_ERROR(hr_result);
	}
	return S_OK;
}

STDMETHODIMP CSelObjWndPropAct::PreConfigPages (IDataObject *pIDataObj, DWORD dwFlags)
{
HWND hORWnd = NULL;

	if (NULL != pIDataObj)					// evtl. RechercheFensterhandle besorgen
		GetHWNDData (pIDataObj, &hORWnd);

	if (NULL == hORWnd)
		hORWnd = DEX_GetActiveORWnd();		// letztes aktiuves ORWnd voreinstellen

	m_hWnd = hORWnd;
	m_dwFlags = dwFlags;
	
	if (NULL != m_pCfgDlg) {
		m_pCfgDlg -> SetHWND (m_hWnd);
		m_pCfgDlg -> SetFlags (m_dwFlags);
		m_pCfgDlg -> SetMode (m_rgMode);
		m_pCfgDlg -> SetCloseWhenReady(m_fCloseWhenReady);
		m_pCfgDlg -> SetDisableCloseWhenReady(m_fDisableCloseWhenReady);
		m_pCfgDlg -> SetAllowForOneObjectSelection(m_fAllowForOneObjectSelection);
	}
	m_fHasInitData = true;
	return S_OK;
}

STDMETHODIMP CSelObjWndPropAct::BeginAction (IProgressIndicator *pPI)
{
	if (NULL != m_pCfgDlg)
		m_ulPacket = m_pCfgDlg -> GetCountSelected();
	else
		m_ulPacket = 0;

	return S_OK;
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

			if (!FillTrees (m_rgMode, m_hWnd, IObjs))
				_com_issue_error(E_FAIL);

			IEnumObj = IObjs;
		} 
		catch (_com_error& hr) {
			return _COM_ERROR(hr);
		}
	} 
	else {
		m_pCfgDlg -> SetAction(this);	// JG 980916
		hr = m_pCfgDlg -> GetEnumLONG (IEnumObj.ppi());
	}
	if (FAILED(hr)) return hr;
	if (!IEnumObj) return S_OK;

// DataObject generieren, welches Info's über unser Ereignis enthält
	*ppDataObj = NULL;
	try {
	WDataObject IDO (CLSID_DataTransferObject);
	
		THROW_FAILED_HRESULT(SetEnumLONGData (IEnumObj, IDO));	// schreiben des EnumLONG ins DataObject
		if (m_fMakePackets && m_ulPacket != 0) {
		// Paketnummer dranhängen
			THROW_FAILED_HRESULT(SetPacketNumber (IDO, m_ulPacket--));
		}

	// Resultat an nächste PropertyAction weiterzureichen
		*ppDataObj = IDO.detach();
	} 
	catch (_com_error& hr_result) {
		DELETE_OBJ (m_pCfgDlg);	// DialogPage freigeben
		return _COM_ERROR(hr_result);
	}

// S_FALSE heißt, daß GetEnumLONG weiter gerufen werden muß
	if (S_FALSE != hr) {	// letzter Enumerator
		if (NULL != m_pCfgDlg) {
			m_rgMode = m_pCfgDlg -> GetMode();
			m_fCloseWhenReady = m_pCfgDlg -> GetCloseWhenReady();
		} 
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
	return S_OK;
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

DWORD dwSignature = 0;
DWORD dwVersion = 0;

	LoadData(pStm, dwSignature);
	if (dwSignature != SRCWINDPA_SIGNATURE)
		return E_UNEXPECTED;
	LoadData(pStm, dwVersion);
	if ((dwVersion & ~SRCWINDPA_MINORVERSIONMASK) > SRCWINDPA_LASTKNOWNVERSION)
		return STG_E_OLDDLL;

HRESULT hr = CPropertyAction::Load (pStm);
bool fWasShown = true;

	if (FAILED(hr)) return hr;

	RETURN_FAILED_HRESULT(LoadData (pStm, m_rgMode));
	RETURN_FAILED_HRESULT(LoadData (pStm, m_fCloseWhenReady));
	RETURN_FAILED_HRESULT(LoadData (pStm, m_fShowConfigAlways));
	RETURN_FAILED_HRESULT(LoadData (pStm, m_lMinWindowCount));

	if (dwVersion >= SRCWINDPA_VERSION_0101)
	{
		RETURN_FAILED_HRESULT(LoadData (pStm, m_fDisableCloseWhenReady));
		if (dwVersion >= SRCWINDPA_VERSION_0102)
		{
			RETURN_FAILED_HRESULT(LoadData (pStm, m_fMakePackets));
			RETURN_FAILED_HRESULT(LoadData (pStm, m_fAllowForOneObjectSelection));
			if (dwVersion >= SRCWINDPA_VERSION_0103)
			{
				RETURN_FAILED_HRESULT(LoadData (pStm, fWasShown));
			}
		}
	}

// Wenn das Fenster angezeigt war und diesmal nicht mehr angezeigt werden soll,
// dann muß die gesamte Sequence neu geladen werden!
	if (WindowShouldBeHidden() && fWasShown)
	{
		return E_FAIL;	// neu laden
	}

	m_fHasInitData = true;
	m_fIsInitialized = true;
	m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CSelObjWndPropAct::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	SaveData(pStm, SRCWINDPA_SIGNATURE);
	SaveData(pStm, SRCWINDPA_LASTKNOWNVERSION);

	RETURN_FAILED_HRESULT(CPropertyAction::Save (pStm, fClearDirty));
	RETURN_FAILED_HRESULT(SaveData (pStm, m_rgMode));
	RETURN_FAILED_HRESULT(SaveData (pStm, m_fCloseWhenReady));
	RETURN_FAILED_HRESULT(SaveData (pStm, m_fShowConfigAlways));
	RETURN_FAILED_HRESULT(SaveData (pStm, m_lMinWindowCount));
	RETURN_FAILED_HRESULT(SaveData (pStm, m_fDisableCloseWhenReady));
	RETURN_FAILED_HRESULT(SaveData (pStm, m_fMakePackets));
	RETURN_FAILED_HRESULT(SaveData (pStm, m_fAllowForOneObjectSelection));
	RETURN_FAILED_HRESULT(SaveData (pStm, m_fWindowWasShown));

	return S_OK;
}

STDMETHODIMP CSelObjWndPropAct::InitNew (void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_rgMode = SELECTMODE_Selected;
	m_fCloseWhenReady = false;
	m_fDisableCloseWhenReady = false;
	m_fShowConfigAlways = false;
	m_lMinWindowCount = 2;
	m_fMakePackets = false;
	m_fAllowForOneObjectSelection = false;
	m_ulPacket = 0;
	m_fWindowWasShown = false;
	m_fIsInitialized = true;
	m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CSelObjWndPropAct::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyAction::GetSizeMax (pcbSize));

	pcbSize -> QuadPart += sizeof(SELECTMODE) + sizeof(m_fCloseWhenReady) 
		+ sizeof(m_fShowConfigAlways) + 3*sizeof(long)
		+ sizeof(m_fDisableCloseWhenReady) + sizeof(m_fAllowForOneObjectSelection)
		+ sizeof(m_fMakePackets) + sizeof(m_fWindowWasShown);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CSelObjWndPropAct::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags)  
{
	if (NULL == pcBuffer) 
		return E_POINTER;

	m_strDesc = pcBuffer;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CSelObjWndPropAct::SetDirty (bool fDirty) { m_fIsDirty = fDirty; }

/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
STDMETHODIMP CSelObjWndPropAct::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyActionExt::Load (pBag, pLog));

	m_lMinWindowCount = 2;
	m_hWndIgnore = NULL;
	m_fMakePackets = false;
	m_ulPacket = 0;
	m_fAllowForOneObjectSelection = false;
	m_fCloseWhenReady = false;
	m_fDisableCloseWhenReady = false;
	m_fShowConfigAlways = false;

// Parameter auswerten
// SelectObjs=
CComVariant vSelect;
HRESULT hr = pBag -> Read (CComBSTR(g_cbSelectObjs), &vSelect, pLog);

	if (S_OK == hr && SUCCEEDED(vSelect.ChangeType(VT_BSTR))) {
		if (!_wcsicmp (V_BSTR(&vSelect), g_cbActivated))
			m_rgMode = SELECTMODE_Activated;
		else if (!_wcsicmp (V_BSTR(&vSelect), g_cbSelected))
			m_rgMode = SELECTMODE_Selected;
		else 
			m_rgMode = SELECTMODE_All;
	}

// CloseWhenReady=
CComVariant vCloseWhenReady;

	hr = pBag ->Read (CComBSTR(g_cbCloseWhenReady), &vCloseWhenReady, pLog);
	if (S_OK == hr && SUCCEEDED(vCloseWhenReady.ChangeType(VT_BOOL))) 
		m_fCloseWhenReady = V_BOOL(&vCloseWhenReady) ? true : false;

// DisableCloseWhenReady=
CComVariant vDisableCloseWhenReady;

	hr = pBag ->Read (CComBSTR(g_cbDisableCloseWhenReady), &vDisableCloseWhenReady, pLog);
	if (S_OK == hr && SUCCEEDED(vDisableCloseWhenReady.ChangeType(VT_BOOL))) 
		m_fDisableCloseWhenReady = V_BOOL(&vDisableCloseWhenReady) ? true : false;

// ShowConfigAlways=
CComVariant vShowConfigAlways;

	hr = pBag ->Read (CComBSTR(g_cbShowConfigAlways), &vShowConfigAlways, pLog);
	if (S_OK == hr && SUCCEEDED(vShowConfigAlways.ChangeType(VT_BOOL))) 
		m_fShowConfigAlways = V_BOOL(&vShowConfigAlways) ? true : false;

// MinWindowCount=
CComVariant vCount;

	hr = pBag -> Read (CComBSTR("MinWindowCount"), &vCount, pLog);
	if (S_OK == hr && SUCCEEDED(vCount.ChangeType(VT_I4))) 
		m_lMinWindowCount = V_I4(&vCount);

// IgnoreWindows=
CComVariant vHwnd;

	hr = pBag -> Read (CComBSTR("IgnoreWindows"), &vHwnd, pLog);
	if (S_OK == hr && SUCCEEDED(vHwnd.ChangeType(VT_UI4))) 
		m_hWndIgnore = reinterpret_cast<HWND>(V_UI4(&vHwnd));

// MakePackets=
CComVariant vMakePackets;

	hr = pBag -> Read (CComBSTR("MakePackets"), &vMakePackets, pLog);
	if (S_OK == hr && SUCCEEDED(vMakePackets.ChangeType(VT_BOOL))) 
		m_fMakePackets = V_BOOL(&vMakePackets);

// AllowForOneObjectSelection=
CComVariant vAllowForOneObjectSelection;

	hr = pBag -> Read (CComBSTR("AllowForOneObjectSelection"), &vAllowForOneObjectSelection, pLog);
	if (S_OK == hr && SUCCEEDED(vAllowForOneObjectSelection.ChangeType(VT_BOOL))) 
		m_fAllowForOneObjectSelection = V_BOOL(&vAllowForOneObjectSelection);

	m_fHasInitData = true;
	return S_OK;
}
