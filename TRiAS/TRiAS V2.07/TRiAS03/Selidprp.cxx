// PropertyAction, welche Ident/Objekttypen auswählt und zusammenstellt -------
// File: SELIDPRP.CXX

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
DefineEnumIIDWrapper(LONG);		// CIID_LONGEnum
DefineSmartEnumerator(LONG);	// WEnumLONG

extern char g_pDLLName[_MAX_PATH];		// dieser Modul

// 0E54C9E0-20DE-11CF-BA55-00AA0018497C	
// DEFINE_GUID(CLSID_SelectIdentObjTyp, 0x0E54C9E0L, 0x20DE, 0x11CF, 0xBA, 0x55, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// 'CLSPROP_ROOT\TRiAS® (allgemein)\Objektauswahl nach Identifikator und Objekttyp'
CSelIDPropAct::CSelIDPropAct (void)
{
	m_pCfgDlg = NULL;
	m_fIsDirty = false;
	m_fIsInitialized = false;
	m_fHasInitData = false;

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
		*pdwFlags = PROPCAPS_ACTION_SOURCE;
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

	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
	ResourceFile RF (g_pDLLName);

		DELETE_OBJ(m_pCfgDlg);	// evtl. vorherigen freigeben
		m_pCfgDlg = CSelectIdentDlg::CreateInstance (this, 
						ResID (IDD_SELECTIDS_WIZ, &RF), cbCaption);
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

STDMETHODIMP CSelIDPropAct::EndAction (DWORD, IDataObject **ppDataObj)
{
WEnumLONG IEnumObj;
// JG 980915 um PI zu handlen
	m_pCfgDlg -> SetAction(this);

HRESULT hr = m_pCfgDlg -> GetEnumLONG (IEnumObj.ppi());
	
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
		DELETE_OBJ (m_pCfgDlg);	// DialogPage freigeben
		return _COM_ERROR(hr_result);
	}

	if (S_FALSE != GetScode(hr)) {
	// letzter Enumerator
		m_caSelInfo.Tidy();
		hr = m_pCfgDlg -> GetSelectedInfo (&m_caSelInfo);
		if (FAILED(hr)) _com_issue_error(hr);

		DELETE_OBJ (m_pCfgDlg);	// DialogPage freigeben
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
	return NOERROR;
}

// IPersistStreamInit methods
STDMETHODIMP CSelIDPropAct::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

#if 0
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
#endif // 0

STDMETHODIMP CSelIDPropAct::Load (LPSTREAM pStm)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

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
	
	if (FAILED(hr)) return hr;

	m_fIsInitialized = true;
	m_fIsDirty = false;

return NOERROR;
}

STDMETHODIMP CSelIDPropAct::Save (LPSTREAM pStm, BOOL fClearDirty)
{
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

	if (fClearDirty) m_fIsDirty = false;
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

LARGE liOwnSize ((UINT)(caSelInfo.cElems*sizeof(SELIDRESULT)+sizeof(m_caSelInfo.cElems)));

	liOwnSize = liOwnSize + LARGE(cbSize);
	*pcbSize = liOwnSize;
	
	return S_OK;
}

STDMETHODIMP CSelIDPropAct::InitNew (void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_fIsInitialized = true;
	m_fIsDirty = false;

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
STDMETHODIMP CSelIDPropAct::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyAction::Load (pBag, pLog));

	m_caSelInfo.Tidy();

// sonstige Werte Analysieren
CComVariant vSelectFrom;
HRESULT hr = pBag -> Read (CComBSTR("SelectFrom"), &vSelectFrom, pLog);

	if (S_OK == hr && SUCCEEDED(vSelectFrom.ChangeType(VT_BSTR)))
	{
		m_caSelInfo.ulSelectFrom = SELIDMODE_SINGLETYPE;
		if( 0 == strcmp("Document", OLE2A(V_BSTR(&vSelectFrom))) )
			m_caSelInfo.ulSelectFrom = SELIDMODE_ALLIDENTSPBD;
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
			if( SELIDMODE_SINGLETYPE == m_caSelInfo.ulSelectFrom ) {
				THROW_FAILED_HRESULT(Pairs -> put_Pattern (L",\\[%1\\]:%2"));
			}
			else {
				THROW_FAILED_HRESULT(Pairs -> put_Pattern (L",\\[%1\\]%2"));
			}
			THROW_FAILED_HRESULT(Pairs -> Parse (bstr, &lCnt));

		WEnumString Enum;

			THROW_FAILED_HRESULT(Pairs -> GetKeyStrings (Enum.ppu()));
		
		// Key's durchgehen
		SELIDRESULT *data = (SELIDRESULT *)CoTaskMemAlloc( lCnt * sizeof(SELIDRESULT) );
		LPOLESTR poleOKS = NULL;
		HRESULT hr;

			for (lCnt = 0, Enum -> Reset();
				S_OK == Enum -> Next (1, &poleOKS, NULL); /**/) 
			{
			CComBSTR bstrOTyp;
			unsigned long ulIdent;

				hr = IdentFromClass (OLE2A(poleOKS), &ulIdent, FALSE);
				if (S_OK == hr) {
					 data[lCnt].m_lIdent = ulIdent;
					if( SELIDMODE_SINGLETYPE == m_caSelInfo.ulSelectFrom ) {
						THROW_FAILED_HRESULT(Pairs -> get_Value (CComBSTR(poleOKS), &bstrOTyp));
						data[lCnt++].m_iOTyp = (short)wcstol (bstrOTyp, NULL, 16);
					}
					else
						data[lCnt++].m_iOTyp = OTPunkt|OTLinie|OTFlaeche|OTText;
				}
				::CoTaskMemFree (poleOKS);
			}

			if (lCnt > 0) 
				m_caSelInfo.SetData (lCnt, data);

		} COM_CATCH;
	}
	m_fHasInitData = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CSelIDPropAct::SetDirty (bool fDirty) { m_fIsDirty = fDirty; }
