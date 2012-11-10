// Basisklasse für IPropertyAction - Objekt -----------------------------------
// File: PropActBase.cpp

#include "FakeMfcp.hxx"

#include "PropActBase.h"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods 
STDMETHODIMP CPropertyActionBase::AddConfigPages (
	LPFNADDPROPSHEETPAGE, LPARAM, LPCSTR, UINT *)
{
	return E_NOTIMPL;
}

STDMETHODIMP CPropertyActionBase::PreConfigPages (IDataObject *, DWORD)
{
	return E_NOTIMPL;
}

STDMETHODIMP CPropertyActionBase::BeginAction (IProgressIndicator *)
{
	return E_NOTIMPL;
}

STDMETHODIMP CPropertyActionBase::DoAction (IDataObject *, DWORD)
{
	return E_NOTIMPL;
}

STDMETHODIMP CPropertyActionBase::EndAction (DWORD, IDataObject **)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyAction2 methods
STDMETHODIMP CPropertyActionBase::InitFromData (IDataObject *pIDO, BOOL fCreate, DWORD)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions 
STDMETHODIMP CPropertyActionBase::Reset (void)
{
	return E_NOTIMPL;
}

STDMETHODIMP_(ULONG) CPropertyActionBase::Count (void)
{
	return 0L;
}

STDMETHODIMP CPropertyActionBase::HelpInfo (LPSTR, ULONG, LPSTR, ULONG *)
{
	return E_NOTIMPL;
}

STDMETHODIMP CPropertyActionBase::Eval (IEnumLONG *, LPSTR, ULONG, ULONG *) 
{
	return E_NOTIMPL;
}

STDMETHODIMP CPropertyActionBase::Cumulation (LPSTR, ULONG, ULONG *)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CPropertyActionBase::Load (LPSTREAM pStm)
{
ULONG ulLen = 0;
HRESULT hr = pStm -> Read (&ulLen, sizeof(ULONG), NULL);

	if (S_OK != hr) return hr;

	TX_ASSERT(ulLen <= _MAX_PATH);

char cbBuffer[_MAX_PATH];

	hr = pStm -> Read (cbBuffer, ulLen, NULL);
	if (S_OK != hr) return hr;

return SetPropName (cbBuffer);
}

// BasisKlasse schreib lediglich den Bezeichner weg 
STDMETHODIMP CPropertyActionBase::Save (LPSTREAM pStm, BOOL fClearDirty)
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

STDMETHODIMP CPropertyActionBase::GetSizeMax (ULARGE_INTEGER FAR* pcbSize)
{
char cbBuffer[_MAX_PATH];
HRESULT  hr = GetPropInfo (cbBuffer, sizeof(cbBuffer), NULL);

	if (FAILED(hr)) return hr;

	LISet32(*pcbSize, strlen(cbBuffer)+1);

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CPropertyActionBase::SetHelpInfo (LPCSTR pBuffer, LPCSTR pHelpFile, ULONG ulHelpCtx)
{
	return E_NOTIMPL;
}


