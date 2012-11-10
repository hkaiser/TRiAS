// Basisklasse für IPropertyAction - Objekt -----------------------------------
// File: PROPACTB.CXX

#include "bscriptp.hxx"

#include "propactb.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods 
STDMETHODIMP CPropertyAction::AddConfigPages (
	LPFNADDPROPSHEETPAGE, LPARAM, LPCSTR, UINT *)
{
	return E_NOTIMPL;
}

STDMETHODIMP CPropertyAction::PreConfigPages (IDataObject *, DWORD)
{
	return E_NOTIMPL;
}

STDMETHODIMP CPropertyAction::BeginAction (IProgressIndicator *)
{
	return E_NOTIMPL;
}

STDMETHODIMP CPropertyAction::DoAction (IDataObject *, DWORD)
{
	return E_NOTIMPL;
}

STDMETHODIMP CPropertyAction::EndAction (DWORD, IDataObject **)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions 
STDMETHODIMP CPropertyAction::Reset (void)
{
	return E_NOTIMPL;
}

STDMETHODIMP_(ULONG) CPropertyAction::Count (void)
{
	return 0L;
}

STDMETHODIMP CPropertyAction::HelpInfo (LPSTR, ULONG, LPSTR, ULONG *)
{
	return E_NOTIMPL;
}

STDMETHODIMP CPropertyAction::Eval (IEnumLONG *, LPSTR, ULONG, ULONG *) 
{
	return E_NOTIMPL;
}

STDMETHODIMP CPropertyAction::Cumulation (LPSTR, ULONG, ULONG *)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CPropertyAction::Load (LPSTREAM pStm)
{
ULONG ulLen = 0;
HRESULT hr = pStm -> Read (&ulLen, sizeof(ULONG), NULL);

	if (S_OK != hr) return hr;

	TX_ASSERT(ulLen <= _MAX_PATH);

char cbBuffer[_MAX_PATH];

	hr = pStm -> Read (cbBuffer, ulLen, NULL);
	if (S_OK != hr) return hr;

	return SetPropInfo (cbBuffer, PROPCAPS_ACTION_SOURCE|PROPCAPS_ACTION_SINK);
}

// BasisKlasse schreib lediglich den Bezeichner weg 
STDMETHODIMP CPropertyAction::Save (LPSTREAM pStm, BOOL fClearDirty)
{
// Bezeichner wegschreiben
char cbBuffer[_MAX_PATH];
HRESULT hr = GetPropInfo (cbBuffer, sizeof(cbBuffer), NULL);

	if (FAILED(hr)) return hr;

ULONG ulLen = strlen(cbBuffer)+1;

	hr = pStm -> Write (&ulLen, sizeof(ULONG), NULL);
	if (FAILED(hr)) return hr;
	hr = pStm -> Write (cbBuffer, ulLen, NULL);
	if (FAILED(hr)) return hr;

return NOERROR;
}

STDMETHODIMP CPropertyAction::GetSizeMax (ULARGE_INTEGER FAR* pcbSize)
{
char cbBuffer[_MAX_PATH];
HRESULT  hr = GetPropInfo (cbBuffer, sizeof(cbBuffer), NULL);

	if (FAILED(hr)) return hr;

	LISet32(*pcbSize, strlen(cbBuffer)+1);

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CPropertyAction::SetHelpInfo (LPCSTR pBuffer, LPCSTR pHelpFile, ULONG ulHelpCtx)
{
	return E_NOTIMPL;
}


