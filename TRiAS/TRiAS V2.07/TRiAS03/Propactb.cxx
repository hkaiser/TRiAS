// Basisklasse für IPropertyAction - Objekt -----------------------------------
// File: PROPACTB.CXX

#include "trias03p.hxx"

#include <Helper_i.c>
#include <propactn.h>
#include <funcs03.h>

#include <statguid.h>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Strings.h"
#include "propactb.hxx"

///////////////////////////////////////////////////////////////////////////////
// SmartIF'S
DefineSmartInterface(ParseStringPairs);

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
	CComVariant vData;

		THROW_FAILED_HRESULT(GetVariantData (pIDO, &c_feInitPropAct, &vData));
		THROW_FAILED_HRESULT(vData.ChangeType(VT_BSTR));

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
		THROW_FAILED_HRESULT(Bag -> Parse (V_BSTR(&vData), &lCount));
		THROW_FAILED_HRESULT(Bag -> InitObject (GetUnknown(), v));

	} COM_CATCH;
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
	if (dwVersion > PROPACTB_ACTVERSION)
		return STG_E_OLDDLL;	// File was written with a newer version

// Daten einlesen
ULONG ulLen = 0;
char cbBuffer[_MAX_PATH];

	RETURN_FAILED_HRESULT(pStm -> Read (&ulLen, sizeof(ULONG), NULL));

	TX_ASSERT(ulLen <= _MAX_PATH);
	RETURN_FAILED_HRESULT(pStm -> Read (cbBuffer, ulLen, NULL));

DWORD dwFlags = 0;

	RETURN_FAILED_HRESULT(pStm -> Read (&dwFlags, sizeof(DWORD), NULL));
	return SetPropInfo (cbBuffer, dwFlags);
}

// BasisKlasse schreibt lediglich den Bezeichner weg 
STDMETHODIMP CPropertyAction::Save (LPSTREAM pStm, BOOL fClearDirty)
{
// Versionsnummer wegschreiben
DWORD dwVersion = PROPACTB_VERSION_1_0_0;

	RETURN_FAILED_HRESULT(pStm -> Write (&dwVersion, sizeof(DWORD), NULL));
	
// Bezeichner wegschreiben
char cbBuffer[_MAX_PATH];
DWORD dwFlags = 0L;

	RETURN_FAILED_HRESULT(GetPropInfo (cbBuffer, sizeof(cbBuffer), &dwFlags));

ULONG ulLen = strlen(cbBuffer)+1;

	RETURN_FAILED_HRESULT(pStm -> Write (&ulLen, sizeof(ULONG), NULL));
	RETURN_FAILED_HRESULT(pStm -> Write (cbBuffer, ulLen, NULL));
	RETURN_FAILED_HRESULT(pStm -> Write (&dwFlags, sizeof(DWORD), NULL));
	return S_OK;
}

STDMETHODIMP CPropertyAction::GetSizeMax (ULARGE_INTEGER FAR* pcbSize)
{
char cbBuffer[_MAX_PATH];

	RETURN_FAILED_HRESULT(GetPropInfo (cbBuffer, sizeof(cbBuffer), NULL));
	LISet32(*pcbSize, 2*sizeof(DWORD)+sizeof(ULONG)+strlen(cbBuffer)+1);
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