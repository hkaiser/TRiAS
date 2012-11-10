// Basisklasse für IPropertyAction - Objekt -----------------------------------
// File: PROPACTB.CXX

#include "trias03p.hxx"

#include "propactb.hxx"

///////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods 
STDMETHODIMP CPropertyAction::AddConfigPages (
	LPFNADDPROPSHEETPAGE, LPARAM, DWORD, LPCSTR, UINT *)
{
	return E_NOTIMPL;
}

STDMETHODIMP CPropertyAction::PreConfigPages (IDataObject *)
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

