// Basisklasse für IPropertyAction - Objekt -----------------------------------
// File: PROPACTB.CXX

#include "trias03p.hxx"

#include <propactn.h>
#include <funcs03.h>

#include <statguid.h>
#include <ciid.h>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Strings.h"
#include "propactb.hxx"

#if _TRiAS_VER < 0x0300
const IID IID_DMatchString = {0x079638B4,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
const IID IID_IMatchPlainText = {0xC3BF0D41,0x7DF6,0x11D2,{0x9E,0xF6,0x00,0x60,0x08,0x44,0x78,0x00}};
const IID IID_IMatchRegExpr = {0xC3BF0D42,0x7DF6,0x11D2,{0x9E,0xF6,0x00,0x60,0x08,0x44,0x78,0x00}};
const IID IID_IMatchFuzzy = {0xC3BF0D43,0x7DF6,0x11D2,{0x9E,0xF6,0x00,0x60,0x08,0x44,0x78,0x00}};
const IID IID_ICookieHelper = {0xBED66F39,0x7351,0x11D2,{0x9E,0xF1,0x00,0x60,0x08,0x44,0x78,0x00}};
const IID IID_IComposeStringPairs = {0x6B77F344,0xA121,0x11D1,{0xBA,0x21,0x08,0x00,0x36,0xD6,0x38,0x03}};
const IID IID_IParseStringPairs = {0xC21AAF95,0x2DE5,0x11D1,{0x96,0x9A,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
const IID IID_IParseRegularExpression = {0xC21AAF92,0x2DE5,0x11D1,{0x96,0x9A,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
const CLSID CLSID_ParseStringPairs = {0xC21AAF96,0x2DE5,0x11D1,{0x96,0x9A,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
const CLSID CLSID_MatchPlainTextExakt = {0xC3BF0D37,0x7DF6,0x11D2,{0x9E,0xF6,0x00,0x60,0x08,0x44,0x78,0x00}};
const CLSID CLSID_MatchRegExprExakt = {0xC3BF0D3B,0x7DF6,0x11D2,{0x9E,0xF6,0x00,0x60,0x08,0x44,0x78,0x00}};
const CLSID CLSID_MatchFuzzy = {0xC3BF0D3E,0x7DF6,0x11D2,{0x9E,0xF6,0x00,0x60,0x08,0x44,0x78,0x00}};
const CLSID CLSID_CookieHelper = {0xBED66F3A,0x7351,0x11D2,{0x9E,0xF1,0x00,0x60,0x08,0x44,0x78,0x00}};
const CLSID CLSID_ParseRegularExpression = {0xC21AAF93,0x2DE5,0x11D1,{0x96,0x9A,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
const IID LIBID_TRiASSupport = {0xC21AAF85,0x2DE5,0x11D1,{0x96,0x9A,0x00,0xA0,0x24,0xD6,0xF5,0x82}};
#endif // _TRiAS_VER < 0x0300

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ParseStringPairs);
DefineSmartInterface(Persist);

///////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods 
STDMETHODIMP CPropertyAction::AddConfigPages (
	LPFNADDPROPSHEETPAGE, LPARAM, LPCSTR, UINT *)
{
	ATLTRACENOTIMPL("CPropertyAction::AddConfigPages");
}

STDMETHODIMP CPropertyAction::PreConfigPages (IDataObject *, DWORD)
{
	ATLTRACENOTIMPL("CPropertyAction::PreConfigPages");
}

STDMETHODIMP CPropertyAction::BeginAction (IProgressIndicator *)
{
	ATLTRACENOTIMPL("CPropertyAction::BeginAction");
}

STDMETHODIMP CPropertyAction::DoAction (IDataObject *, DWORD)
{
	ATLTRACENOTIMPL("CPropertyAction::DoAction");
}

STDMETHODIMP CPropertyAction::EndAction (DWORD, IDataObject **)
{
	ATLTRACENOTIMPL("CPropertyAction::EndAction");
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyAction2 methods
STDMETHODIMP CPropertyAction::InitFromData (IDataObject *pIDO, BOOL fCreate, DWORD)
{
	if (NULL == pIDO) {
		if (fCreate)
			return S_OK;	// can attempt to initialize it self
		else
			return S_FALSE;	// can't attempt to replace internal data
	}

	COM_TRY {
	// evtl. liegt objektbezogene Initialisierungsinfo vor, ClipBoardFormat zusammenstellen
	CIID Guid;
	WPersist Persist;
	HRESULT hr = E_FAIL;

		if (SUCCEEDED(GetControllingUnknown() -> QueryInterface(Persist.ppi())) && 
			SUCCEEDED(Persist -> GetClassID (&Guid))) 
		{
		FORMATETC c_feProgID = 	{
				RegisterClipboardFormat (Guid.ProgID().c_str()),	// CLIPFORMAT cf
				NULL,											// DVTARGETDEVICE *ptd
				DVASPECT_CONTENT,								// DWORD dwAspect
				-1,												// LONG lindex	
				TYMED_ISTREAM,									// DWORD tymed
			};
			hr = InitFromDataFormatETC (pIDO, &c_feProgID);	// Fehler ignorieren
		}

	// Versuchen aus globaler Initialisierungsinformation zu initialisieren
		if (S_OK != hr)
			InitFromDataFormatETC (pIDO, &c_feInitPropAct);
	} COM_CATCH;
	return S_OK;
}

HRESULT CPropertyAction::InitFromDataFormatETC (IDataObject *pIDO, const FORMATETC *pcfmt)
{
	COM_TRY {
	CComVariant vData;

		if (SUCCEEDED(GetVariantData (pIDO, pcfmt, &vData))) {
			THROW_FAILED_HRESULT(vData.ChangeType (VT_BSTR));

			if (0 == SysStringLen (V_BSTR(&vData)))
				return S_FALSE;

		WParseStringPairs Bag (CLSID_ParseStringPairs);
		CComVariant v (DISP_E_PARAMNOTFOUND, VT_ERROR);	// no error log
		LONG lCount = 0;
		CComBSTR bstrData;

			if (*V_BSTR(&vData) != L';') {		// Data müssen mit ";PropActData" anfangen
				bstrData = g_cbPAPrefix;
				bstrData += ";";
			}
			bstrData += V_BSTR(&vData);

			THROW_FAILED_HRESULT(Bag -> put_Pattern (CComBSTR(g_cbPattern)));
			THROW_FAILED_HRESULT(Bag -> Parse (bstrData, &lCount));
			THROW_FAILED_HRESULT(Bag -> InitObject (GetUnknown(), v));
		}
	} COM_CATCH;
	return S_OK;
}

// ***IPropertyAction3 methods
HRESULT CPropertyAction::GetHeaderTitle (LPSTR pBuffer, ULONG wLen)
{
	COM_TRY {
		if (NULL != pBuffer && wLen > 0) {
		// Namen der Property kopieren
		ULONG ulLen = min((size_t)(wLen-1), m_strHeaderTitle.size());

			strncpy (pBuffer, m_strHeaderTitle.c_str(), ulLen);
			pBuffer[ulLen] = '\0';
		}
	} COM_CATCH;
	return S_OK;
}

HRESULT CPropertyAction::SetHeaderTitle (LPCSTR pcHeaderTitle)
{
	if (NULL == pcHeaderTitle)
		return E_INVALIDARG;
	ATLTRY(m_strHeaderTitle = pcHeaderTitle);
	return S_OK;
}

HRESULT CPropertyAction::GetHeaderSubTitle (LPSTR pBuffer, ULONG wLen)
{
	COM_TRY {
		if (NULL != pBuffer && wLen > 0) {
		// Namen der Property kopieren
		ULONG ulLen = min((size_t)(wLen-1), m_strHeaderSubTitle.size());

			strncpy (pBuffer, m_strHeaderSubTitle.c_str(), ulLen);
			pBuffer[ulLen] = '\0';
		}
	} COM_CATCH;
	return S_OK;
}

HRESULT CPropertyAction::SetHeaderSubTitle (LPCSTR pcHeaderSubTitle)
{
	if (NULL == pcHeaderSubTitle)
		return E_INVALIDARG;
	ATLTRY(m_strHeaderSubTitle = pcHeaderSubTitle);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions 
STDMETHODIMP CPropertyAction::Reset (void)
{
	ATLTRACENOTIMPL("CPropertyAction::Reset");
}

STDMETHODIMP_(ULONG) CPropertyAction::Count (void)
{
	return 0L;
}

STDMETHODIMP CPropertyAction::HelpInfo (LPSTR, ULONG, LPSTR, ULONG *)
{
	ATLTRACENOTIMPL("CPropertyAction::HelpInfo");
}

STDMETHODIMP CPropertyAction::Eval (IEnumLONG *, LPSTR, ULONG, ULONG *) 
{
	ATLTRACENOTIMPL("CPropertyAction::Eval");
}

STDMETHODIMP CPropertyAction::Cumulation (LPSTR, ULONG, ULONG *)
{
	ATLTRACENOTIMPL("CPropertyAction::Cumulation");
}

///////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CPropertyAction::Load (LPSTREAM pStm)
{
// Version lesen und überprüfen
DWORD dwVersion = 0;

	RETURN_FAILED_HRESULT(pStm -> Read (&dwVersion, sizeof(DWORD), NULL));
	if ((dwVersion & ~PROPACTB_VERSION_MINOR_MASK) > PROPACTB_ACTVERSION)
		return STG_E_OLDDLL;	// File was written with a newer version

// Daten einlesen
ULONG ulLen = 0;
char cbBuffer[_MAX_PATH];

	RETURN_FAILED_HRESULT(pStm -> Read (&ulLen, sizeof(ULONG), NULL));

	TX_ASSERT(ulLen <= _MAX_PATH);
	RETURN_FAILED_HRESULT(pStm -> Read (cbBuffer, ulLen, NULL));

DWORD dwFlags = 0;

	RETURN_FAILED_HRESULT(pStm -> Read (&dwFlags, sizeof(DWORD), NULL));
	RETURN_FAILED_HRESULT(SetPropInfo (cbBuffer, dwFlags));

	if (dwVersion >= PROPACTB_VERSION_1_0_1) {
	BOOL fNoShow = FALSE;

		RETURN_FAILED_HRESULT(pStm -> Read (&fNoShow, sizeof(BOOL), NULL));
		SetNoShow(fNoShow ? true : false);
	}
	return S_OK;
}

// BasisKlasse schreibt lediglich den Bezeichner weg 
STDMETHODIMP CPropertyAction::Save (LPSTREAM pStm, BOOL fClearDirty)
{
// Versionsnummer wegschreiben
DWORD dwVersion = PROPACTB_ACTVERSION;

	RETURN_FAILED_HRESULT(pStm -> Write (&dwVersion, sizeof(DWORD), NULL));
	
// Bezeichner wegschreiben
char cbBuffer[_MAX_PATH];
DWORD dwFlags = 0L;

	RETURN_FAILED_HRESULT(GetPropInfo (cbBuffer, sizeof(cbBuffer), &dwFlags));

ULONG ulLen = strlen(cbBuffer)+1;
BOOL fNoShow = IsNoShow();

	RETURN_FAILED_HRESULT(pStm -> Write (&ulLen, sizeof(ULONG), NULL));
	RETURN_FAILED_HRESULT(pStm -> Write (cbBuffer, ulLen, NULL));
	RETURN_FAILED_HRESULT(pStm -> Write (&dwFlags, sizeof(DWORD), NULL));
	RETURN_FAILED_HRESULT(pStm -> Write (&fNoShow, sizeof(BOOL), NULL));
	return S_OK;
}

STDMETHODIMP CPropertyAction::GetSizeMax (ULARGE_INTEGER FAR* pcbSize)
{
char cbBuffer[_MAX_PATH];

	RETURN_FAILED_HRESULT(GetPropInfo (cbBuffer, sizeof(cbBuffer), NULL));
	LISet32(*pcbSize, sizeof(BOOL)+2*sizeof(DWORD)+sizeof(ULONG)+strlen(cbBuffer)+1);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CPropertyAction::SetHelpInfo (LPCSTR pBuffer, LPCSTR pHelpFile, ULONG ulHelpCtx)
{
	ATLTRACENOTIMPL("CPropertyAction::SetHelpInfo");
}

/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
STDMETHODIMP CPropertyAction::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;

	m_fNoShow = false;

// wenigstens den Namen der PropertyAction einlesen
CComVariant vName;
HRESULT hr = pBag -> Read (CComBSTR(g_cbPAName), &vName, pLog);

	if (S_OK == hr && SUCCEEDED(vName.ChangeType (VT_BSTR)))
	{
		RETURN_FAILED_HRESULT(SetPropInfo (OLE2A(V_BSTR(&vName)), 0L));
	}

// und noch einlesen, ob der Dialog evtl. _nicht_ angezeigt werden soll
CComVariant vNoShow;

	hr = pBag -> Read (CComBSTR(g_cbPANoShow), &vNoShow, pLog);
	if (S_OK == hr && SUCCEEDED(vNoShow.ChangeType (VT_BOOL)))
		m_fNoShow = V_BOOL(&vNoShow) ? true : false;
	return hr;
}

STDMETHODIMP CPropertyAction::Save (IPropertyBag *pBag, BOOL fClearDirty, BOOL fSaveAllProperties)
{
	return E_NOTIMPL;	// Save wird hier (noch) nicht gebraucht
}

STDMETHODIMP CPropertyAction::PersistPropertyBag_InitNew (void)
{
	return S_OK;	// tut einfach nichts
}

//////////////////////////////////////////////////////////
// CPropertyActionExt
STDMETHODIMP CPropertyActionExt::BeginAction (THIS_ IProgressIndicator *pIProgInd)
{
// 	speichern des PI's
	COM_TRY	{
		m_pProgressIndicator = pIProgInd;
	} COM_CATCH

	return S_OK;
}

HRESULT CPropertyActionExt::Tick()
{
	// wenn noch möglich, dann weiterschalten
	if ((m_pProgressIndicator != NULL) 
	&& (m_aktTick < m_maxTick))
	{
		// noch'n Tick
		++m_aktTick;
		return m_pProgressIndicator -> SetPosition(m_aktTick);
	}
	// auch nicht schlimm, dann eben ohne ProgInd
	return S_OK;
}