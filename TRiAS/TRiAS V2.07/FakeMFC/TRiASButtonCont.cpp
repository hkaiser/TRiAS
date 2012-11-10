// TRiASButtonCont.cpp : Implementation CTRiASButtonCont

#include "fakemfcp.hxx"
#include "fakemfc.h"
#include "TRiASButtonCont.h"

/////////////////////////////////////////////////////////////////////////////
// *** ISupportErrorInfo
STDMETHODIMP CTRiASButtonCont::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_DTRiASBaseClass,
		&IID_DTRiASCollection,
		&IID_DControlToolBarButtons,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CTRiASButtonCont::get_isA (LONG *plRTTI)
{
	if (NULL == plRTTI) return E_POINTER;

	*plRTTI = RTTI_ToolBarButtons;
	return NOERROR;
}

STDMETHODIMP CTRiASButtonCont::get_Parent (IDispatch **ppIBase)
{
	if (NULL != (IUnknown *)m_Parent) 
		return m_Parent -> QueryInterface (IID_IDispatch, (LPVOID *)ppIBase); 
	return E_UNEXPECTED;
}

STDMETHODIMP CTRiASButtonCont::put_Parent (IDispatch *pIBase)
{
	m_Parent = pIBase; 
	return NOERROR;
}

STDMETHODIMP CTRiASButtonCont::get_Application (IDispatch **ppIApp)
{
	if (NULL != (IUnknown *)m_App) 
		return m_App -> QueryInterface (IID_IDispatch, (LPVOID *)ppIApp); 
	return E_UNEXPECTED;
}

STDMETHODIMP CTRiASButtonCont::put_Application (IDispatch *pIApp)
{
	m_App = pIApp; 
	return NOERROR;
}

STDMETHODIMP CTRiASButtonCont::get_Count (LONG *plCnt)
{
	ATLTRACENOTIMPL("CTRiASButtonCont::get_Count");
}

STDMETHODIMP CTRiASButtonCont::Item (VARIANT vItem, IDispatch **ppIDisp)
{
	ATLTRACENOTIMPL("CTRiASButtonCont::Item");
}

STDMETHODIMP CTRiASButtonCont::_NewEnum (IUnknown **pvEnum)
{
	ATLTRACENOTIMPL("CTRiASButtonCont::_NewEnum");
}

STDMETHODIMP CTRiASButtonCont::Add (VARIANT vAdd, IDispatch **ppIDisp)
{
	ATLTRACENOTIMPL("CTRiASButtonCont::Add");
}

STDMETHODIMP CTRiASButtonCont::Remove (VARIANT vRemove)
{
	ATLTRACENOTIMPL("CTRiASButtonCont::Remove");
}

STDMETHODIMP CTRiASButtonCont::Refresh (void)
{
	ATLTRACENOTIMPL("CTRiASButtonCont::Refresh");
}

