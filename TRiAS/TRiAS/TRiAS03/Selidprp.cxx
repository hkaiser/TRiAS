// PropertyAction, welche Ident/Objekttypen auswählt und zusammenstellt -------
// File: SELIDPRP.CXX

#include "trias03p.hxx"
#include "trias03.h"

//#include <int64.h>
#include <xtsnguid.h>
#include <eonrguid.h>
#include <statguid.h>
#include <dirisole.h>

#include <pdataobj.hxx>
#include <funcs03.h>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "selidprp.hxx"

///////////////////////////////////////////////////////////////////////////////
// Min-Funktion, da Macro aus stdlib offensichtlich überladen ist
template<class T>
inline T tmin (T a, T b) { return (a > b) ? b : a; }

///////////////////////////////////////////////////////////////////////////////
// benötigte InterfaceWrapper
DefineSmartInterface(DataObject);
DefineSmartInterface(ParseStringPairs);
DefineSmartInterface(EnumString);
DefineSmartInterface(ClassProperty);

extern char g_pDLLName[_MAX_PATH];		// dieser Modul

// 0E54C9E0-20DE-11CF-BA55-00AA0018497C	
// DEFINE_GUID(CLSID_SelectIdentObjTyp, 0x0E54C9E0L, 0x20DE, 0x11CF, 0xBA, 0x55, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// 'CLSPROP_ROOT\TRiAS® (allgemein)\Objektauswahl nach Identifikator und Objekttyp'
CSelIDPropAct::CSelIDPropAct (void)
	: m_AddEntryThunk(this)
{
	m_pCfgDlg = NULL;
	m_fIsDirty = false;
	m_fIsInitialized = false;
	m_fHasInitData = false;
	m_pCB = NULL;
	m_fMakePackets = false;
	m_ulPacket = 0;

	try {
	ResourceFile RF (g_pDLLName);
	ResString resPropInfo (ResID (IDS_PROPINFO_IDENTOTYP, &RF), 64);

		m_strDesc = resPropInfo;
	} catch (...) {
		TX_ASSERT(false);
	}
}

CSelIDPropAct::~CSelIDPropAct (void)
{
	DELETE_OBJ(m_pCfgDlg);
}

///////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions 
STDMETHODIMP CSelIDPropAct::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
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
		*pdwFlags = PROPCAPS_ACTION_SOURCE|PROPCAPS_ACTION_SINK;
	return NOERROR;
}

STDMETHODIMP CSelIDPropAct::HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Beschreibung übergeben
		ResourceFile RF (g_pDLLName);
		ResString resHelp (ResID (IDS_HELPDESC_IDENTOTYP, &RF), 128);
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
// Callback-Wrapper
DWORD __stdcall CSelIDPropAct::AddEntryCB (INT_PTR lIdent, DWORD dwTypes, UINT_PTR dwData)
{
DWORD dwNewTypes = dwTypes;

	if (NULL != m_pCB) {
	DWORD dwNewTypes = dwTypes;
	HRESULT hr = m_pCB -> AddEntry (lIdent, dwTypes, &dwNewTypes);

		if (SUCCEEDED(hr))
			dwTypes = dwNewTypes;
	}
	return dwTypes;
}

HRESULT CSelIDPropAct::putref_AddEntryCallback (IAddEntryCallback *pAddEntryCB)
{
	m_pCB = pAddEntryCB;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods 
STDMETHODIMP CSelIDPropAct::AddConfigPages (
				LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, 
				LPCSTR pcDesc, UINT *puiCnt)
{
char cbCaption[128];

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

	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
	ResourceFile RF (g_pDLLName);

		DELETE_OBJ(m_pCfgDlg);	// evtl. vorherigen freigeben
		m_pCfgDlg = CSelectIdentDlg::CreateInstance (this, 
						ResID (fChoice ? IDD_SELECTIDS_WIZPP : IDD_SELECTIDS_WIZ, &RF), cbCaption, 
						reinterpret_cast<ADDENTRYPROC>(m_AddEntryThunk.GetThunk()));
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);

		if (!IsNoShow()) {
		HPROPSHEETPAGE hPSP = this -> CreatePage(m_pCfgDlg);

			if (NULL == hPSP || !lpfnAddPage(hPSP, lParam))
				_com_issue_error(E_UNEXPECTED);
		}

		if (NULL != puiCnt) 
			*puiCnt = IsNoShow() ? 0 : 1;

		if (m_fHasInitData) {
		HRESULT	hr = m_pCfgDlg -> SetSelectedInfo (&m_caSelInfo, IsNoShow());

			if (FAILED(hr)) _com_issue_error(hr);
		}

	} catch (_com_error& hr_result) {
		DELETE_OBJ (m_pCfgDlg);
		if (puiCnt) *puiCnt = 0;
		return _COM_ERROR(hr_result);
	}
	
return NOERROR;
}

STDMETHODIMP  CSelIDPropAct::PreConfigPages (IDataObject *, DWORD dwFlags)
{
	m_pCfgDlg -> SetFlags (dwFlags);
	return NOERROR;
}

STDMETHODIMP CSelIDPropAct::BeginAction (IProgressIndicator *pPI)
{
	if (NULL != m_pCfgDlg)
		m_ulPacket = m_pCfgDlg -> GetSelectedPacketCount();
	else
		m_ulPacket = 0;

	return S_OK;
}

STDMETHODIMP CSelIDPropAct::DoAction (IDataObject *pIDataObj, DWORD)
{
WEnumLONG IEnumObj;
HRESULT hr = GetEnumLONGData (pIDataObj, IEnumObj.ppi());

	if (S_OK == hr && NULL != m_pCfgDlg) {
		m_pCfgDlg -> SetAction(this);	
		return m_pCfgDlg -> SetEnumLONG (IEnumObj);
	}
	return S_OK;	// dieses GeoObjekt braucht keine Eingabemenge
}

STDMETHODIMP CSelIDPropAct::EndAction (DWORD, IDataObject **ppDataObj)
{
	if (NULL == ppDataObj) return E_POINTER;
	*ppDataObj = NULL;

WEnumLONG IEnumObj;
HRESULT hr = E_FAIL;

	if (NULL != m_pCfgDlg) {
		m_pCfgDlg -> SetAction(this);	// JG 980915 um PI zu handlen
		RETURN_FAILED_HRESULT(hr = m_pCfgDlg -> 
			GetEnumLONG (IEnumObj.ppi(), m_fMakePackets));
		m_LastObjs = IEnumObj;
	} 
	else {
		_ASSERTE(m_LastObjs.IsValid());
		IEnumObj = m_LastObjs;
		hr = S_OK;
	}

// DataObject generieren
	COM_TRY {
	WDataObject IDO (CLSID_DataTransferObject);
	
		THROW_FAILED_HRESULT(SetEnumLONGData (IEnumObj, IDO));

		if (m_fMakePackets && 0 != m_ulPacket) {
		// Objektklassen/Typen sind sortiert, also Paketnummer dranhängen
			THROW_FAILED_HRESULT(SetPacketNumber(IDO, m_ulPacket--));
		}

		*ppDataObj = IDO.detach();

	} COM_CATCH_OP((delete m_pCfgDlg, m_pCfgDlg = NULL));

	if (S_FALSE != GetScode(hr)) {
	// letzter Enumerator
		if (NULL != m_pCfgDlg) {
			m_caSelInfo.Tidy();
			RETURN_FAILED_HRESULT(m_pCfgDlg -> GetSelectedInfo (&m_caSelInfo));
			DELETE_OBJ (m_pCfgDlg);	// DialogPage freigeben
		}
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CSelIDPropAct::GetClassID (LPCLSID lpClassID)
{
	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_SelectIdentObjTyp;
	return S_OK;
}

// IPersistStreamInit methods
STDMETHODIMP CSelIDPropAct::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CSelIDPropAct::Load (LPSTREAM pStm)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

DWORD dwSignature = 0;
DWORD dwVersion = 0;

	LoadData(pStm, dwSignature);
	if (dwSignature != SRCIDENTPA_SIGNATURE)
		return E_UNEXPECTED;
	LoadData(pStm, dwVersion);
	if ((dwVersion & ~SRCIDENTPA_MINORVERSIONMASK) > SRCIDENTPA_LASTKNOWNVERSION)
		return STG_E_OLDDLL;

CCaSelIdResult caSelInfo;
HRESULT hr = E_FAIL;

// zuerst Bezeichner einlesen
	hr = CPropertyAction::Load (pStm);
	if (FAILED(hr)) return hr;

// dann selektierte Info der letzten Auswahl
	{
		hr = pStm -> Read (&caSelInfo.cElems, sizeof(caSelInfo.cElems), NULL);
		if (FAILED(hr)) return hr;
		
		if (0 < caSelInfo.cElems) {
			caSelInfo.pElems = (SELIDRESULT *)CoTaskMemAlloc (caSelInfo.cElems*sizeof(SELIDRESULT));
			if (NULL == caSelInfo.pElems)
				return E_OUTOFMEMORY;

			hr = pStm -> Read (caSelInfo.pElems, caSelInfo.cElems*sizeof(SELIDRESULT), NULL);
			if (FAILED(hr)) return hr;
		}
	}

	if (NULL == m_pCfgDlg) {
		try {
		// Dialog ist noch nicht initialisiert
			m_caSelInfo = caSelInfo;		// throws hr
			m_fHasInitData = true;
			hr = S_OK;
		} catch (_com_error& catched_hr) {
			m_fHasInitData = false;
			hr = _COM_ERROR(catched_hr);
		}
	} else
		hr = m_pCfgDlg -> SetSelectedInfo (&caSelInfo);
	
	if (FAILED(hr)) 
		return hr;

	RETURN_FAILED_HRESULT(LoadData (pStm, m_fMakePackets));

	m_fIsInitialized = true;
	m_fIsDirty = false;
	return NOERROR;
}

STDMETHODIMP CSelIDPropAct::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	SaveData(pStm, SRCIDENTPA_SIGNATURE);
	SaveData(pStm, SRCIDENTPA_LASTKNOWNVERSION);

// zuerst Bezeichner wegschreiben
HRESULT hr = CPropertyAction::Save (pStm, fClearDirty);

	if (FAILED(hr)) return hr;

// dann selektierte Info der letzten Auswahl
	hr = pStm -> Write (&m_caSelInfo.cElems, sizeof(m_caSelInfo.cElems), NULL);
	if (FAILED(hr)) return hr;

	if (0 < m_caSelInfo.cElems) {
		TX_ASSERT(NULL != m_caSelInfo.pElems);

		hr = pStm -> Write (m_caSelInfo.pElems, m_caSelInfo.cElems*sizeof(SELIDRESULT), NULL);
		if (FAILED(hr)) return hr;
	}

	RETURN_FAILED_HRESULT(SaveData (pStm, m_fMakePackets));

	if (fClearDirty) 
		m_fIsDirty = false;
	return NOERROR;
}

STDMETHODIMP CSelIDPropAct::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) return E_POINTER;

ULARGE_INTEGER cbSize;
HRESULT hr = CPropertyAction::GetSizeMax (&cbSize);

	if (FAILED(hr)) return hr;

CCaSelIdResult caSelInfo;

	hr = m_pCfgDlg -> GetSelectedInfo (&caSelInfo);
	if (FAILED(hr)) return hr;

ULARGE_INTEGER liOwnSize;

	liOwnSize.QuadPart = ((UINT)(caSelInfo.cElems*sizeof(SELIDRESULT)+sizeof(m_caSelInfo.cElems)));
	liOwnSize.QuadPart += cbSize.QuadPart + 2*sizeof(int);
	*pcbSize = liOwnSize;
	return S_OK;
}

STDMETHODIMP CSelIDPropAct::InitNew (void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_fIsInitialized = true;
	m_fIsDirty = false;
	m_fMakePackets = false;
	m_ulPacket = 0;
	m_caSelInfo.Tidy();

	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CSelIDPropAct::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags) 
{
	if (NULL == pcBuffer) return E_POINTER;

	m_strDesc = pcBuffer;
	return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
namespace {

	typedef struct tagENUMPROJECTSDATA {
		long lCnt;
		SELIDRESULT *Ids;
		DWORD ulSelectFromMode;
		WParseStringPairs Pairs;
	} ENUMPROJECTSDATA;

	extern "C"
	BOOL CALLBACK EnumProjects (HPROJECT hPr, LPCSTR pcClass, UINT_PTR dwData)
	{
	ENUMPROJECTSDATA *pData = reinterpret_cast<ENUMPROJECTSDATA *>(dwData);

		COM_TRY {
		CComBSTR bstrOTyp;
		unsigned long ulIdent;
		HRESULT hr = IdentFromClass (hPr, pcClass, &ulIdent, FALSE);

			if (S_OK == hr) {
				pData -> Ids[pData -> lCnt].m_lIdent = ulIdent;
				if (SELIDMODE_SINGLETYPE & pData -> ulSelectFromMode) {
					THROW_FAILED_HRESULT(pData -> Pairs -> get_Value (CComBSTR(pcClass), CLEARED(&bstrOTyp)));
					pData -> Ids[pData -> lCnt++].m_iOTyp = (short)wcstol (bstrOTyp, NULL, 16);
				}
				else
					pData -> Ids[pData -> lCnt++].m_iOTyp = OTPunkt|OTLinie|OTFlaeche|OTText;
			}
		} COM_CATCH_IGNORE;
		return TRUE;	// immer weiter enumerieren
	}
}

STDMETHODIMP CSelIDPropAct::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyAction::Load (pBag, pLog));

	m_caSelInfo.Tidy();

// sonstige Werte Analysieren
CComVariant vSelectFrom;
HRESULT hr = pBag -> Read (CComBSTR("SelectFrom"), &vSelectFrom, pLog);
LONG lConnCnt = DEX_GetOpenConnectionCount (QDCAllOpen|QDCCountQueryDefs);

	if (S_OK == hr && SUCCEEDED(vSelectFrom.ChangeType(VT_BSTR)))
	{
		m_caSelInfo.ulSelectFrom = SELIDMODE_SINGLETYPE;
		if (lConnCnt > 1) 
			m_caSelInfo.ulSelectFrom |= SELIDMODE_SHOWCONNECTIONS;

		if (0 == strcmp ("Document", OLE2A(V_BSTR(&vSelectFrom))))
			m_caSelInfo.ulSelectFrom |= SELIDMODE_ALLIDENTSPBD;
	}

CComVariant vSelect;

	hr = pBag -> Read (CComBSTR("Select"), &vSelect, pLog);
	if (S_OK == hr && SUCCEEDED(vSelect.ChangeType(VT_BSTR)))
	{
		COM_TRY {
		WParseStringPairs Pairs (CLSID_ParseStringPairs);
		CComBSTR bstr (",");
		long lCnt = 0;
		
			bstr += V_BSTR(&vSelect);
			if (SELIDMODE_SINGLETYPE & m_caSelInfo.ulSelectFrom) {
				THROW_FAILED_HRESULT(Pairs -> put_Pattern (L",\\[%1\\]:%2"));
			}
			else {
				THROW_FAILED_HRESULT(Pairs -> put_Pattern (L",\\[%1\\]%2"));
			}
			THROW_FAILED_HRESULT(Pairs -> Parse (bstr, &lCnt));

		WEnumString Enum;

			THROW_FAILED_HRESULT(Pairs -> GetKeyStrings (Enum.ppu()));
		
		// Key's durchgehen
		SELIDRESULT *data = (SELIDRESULT *)CoTaskMemAlloc (lConnCnt*lCnt * sizeof(SELIDRESULT));	// Anzahl der Conn's berücksichtigen
		LPOLESTR poleOKS = NULL;

			if (NULL == data)
				THROW_FAILED_HRESULT(E_OUTOFMEMORY);

		ENUMPROJECTSDATA Data;

			Data.Ids = data;
			Data.ulSelectFromMode = m_caSelInfo.ulSelectFrom;
			Data.Pairs = Pairs;

			for (Data.lCnt = 0, Enum -> Reset(); S_OK == Enum -> Next (1, &poleOKS, NULL); /**/) 
			{
			// alle Idents (Projekte) dieses OKS enumerieren
			ENUMTEXTKEY ETK;

				ETK.eKey = OLE2A(poleOKS);
				ETK.eFcn = (ENUMLONGKEYPROC)EnumProjects;
				ETK.ePtr = &Data; 
				DEX_EnumClassProjects (ETK);

				::CoTaskMemFree (poleOKS);
			}

			if (Data.lCnt > 0) 
				m_caSelInfo.SetData (Data.lCnt, data);

		} COM_CATCH;
	}

	if (m_caSelInfo.ulSelectFrom & SELIDMODE_ALLIDENTSPBD) 
		m_caSelInfo.dwHideTypes = 0;
	else {
	CComVariant vHideTypes, vArg;

		hr = pBag -> Read (CComBSTR("HideTypes"), &vHideTypes, pLog);	// muß Hexzahl sein
		if (S_OK == hr && SUCCEEDED(vHideTypes.ChangeType(VT_BSTR)))
		{
			m_caSelInfo.dwHideTypes = wcstol (V_BSTR(&vHideTypes), NULL, 16);
		}
	}

CComVariant vFailIfEmpty;

	hr = pBag -> Read (CComBSTR("FailIfEmpty"), &vFailIfEmpty, pLog);
	if (S_OK == hr && SUCCEEDED(vFailIfEmpty.ChangeType(VT_BOOL)))
		m_caSelInfo.fFailIfEmpty = V_BOOL(&vFailIfEmpty);
		
// MakePackets=
CComVariant vMakePackets;

	m_ulPacket = 0;
	m_fMakePackets = false;
	hr = pBag -> Read (CComBSTR("MakePackets"), &vMakePackets, pLog);
	if (S_OK == hr && SUCCEEDED(vMakePackets.ChangeType(VT_BOOL))) 
		m_fMakePackets = V_BOOL(&vMakePackets);

	m_fHasInitData = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CSelIDPropAct::SetDirty (bool fDirty) { m_fIsDirty = fDirty; }
