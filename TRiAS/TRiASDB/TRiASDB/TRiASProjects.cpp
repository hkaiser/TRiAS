// TRiASProjects.cpp : Implementation of CTRiASProjects

#include "stdafx.h"

#include <ospace/file/path.h>

#include "Strings.h"
#include "Wrapper.h"

#include "TRiASProjects.h"
#include "MakeEnumVariant.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TRiASProjects, CTRiASProjects)

/////////////////////////////////////////////////////////////////////////////
// CTRiASProjects

STDMETHODIMP CTRiASProjects::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASProjects,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CTRiASProjects::FinalConstruct (void)
{
	ATLTRY(m_Enum = new NEnumWTRiASProject());
	if (!m_Enum) 
		return E_OUTOFMEMORY;

	m_Enum -> Release();	// Konstruktor hinterl‰ﬂt RefCnt==1
	return S_OK;
}

void CTRiASProjects::FinalRelease()
{
	m_Enum.Assign(NULL);	// Enumerator freigeben
	m_pIParent = NULL;
	m_Application = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// Properties
STDMETHODIMP CTRiASProjects::get_Application(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProjects::get_Application");

	*pVal = m_Application;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();
	return S_OK;
}

STDMETHODIMP CTRiASProjects::put_Application(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Application = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASProjects::get_Parent(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProjects::get_Parent");

	*pVal = m_pIParent;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();

	return S_OK;
}

STDMETHODIMP CTRiASProjects::put_Parent(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_pIParent = newVal;		// no AddRef !
	return S_OK;
}

STDMETHODIMP CTRiASProjects::get_Count(long * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProjects::get_Count");

	*pVal = m_Enum -> Count();
	return S_OK;
}

STDMETHODIMP CTRiASProjects::get_ActiveProject(ITRiASProject **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProjects::get_ActiveProject");

	COM_TRY {
	WEnumWTRiASProject Enum;
	WTRiASProject Prj;

		THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, &Prj, NULL); /**/)
		{
		VARIANT_BOOL fActive = VARIANT_FALSE;

			THROW_FAILED_HRESULT(Prj -> get_Activated (&fActive));
			if (fActive) {
				*pVal = Prj.detach();
				return S_OK;
			}
		}
	} COM_CATCH;

	return REPORT_DBERROR(TRIASDB_E_NO_ACTIVE_PROJECT);
}

/////////////////////////////////////////////////////////////////////////////
// Methods
STDMETHODIMP CTRiASProjects::Add(BSTR Name, ITRiASProject **ppIProject)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASProjects::Item(VARIANT Index, ITRiASProject **ppIProject)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

CComVariant vIndex;
bool fFound = false;

	*ppIProject = NULL;
	COM_TRY {
	WEnumWTRiASProject Enum;
	WTRiASProject Prj;

	// Verhindern, daﬂ als Nummern als Zeichenkette falsch interpretiert werden
		if (VT_BSTR != V_VT(&Index) && SUCCEEDED(vIndex.ChangeType (VT_I4, &Index))) {
			if (V_I4(&vIndex) <= 0 || (ULONG)V_I4(&vIndex) > m_Enum -> Count())
				return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProjects::Item");

			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
			THROW_FAILED_HRESULT(Enum -> Reset());

			if (V_I4(&vIndex) > 1)
			{
				THROW_FAILED_HRESULT(Enum -> Skip (V_I4(&vIndex)-1));
			}
			if (S_OK == Enum -> Next (1, &Prj, NULL))
			{
				*ppIProject = Prj.detach();
				fFound = true;
			}

		} else if (SUCCEEDED(vIndex.ChangeType (VT_BSTR, &Index))) {

			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &Prj, NULL); /**/)
			{
			CComBSTR bstrName;

				THROW_FAILED_HRESULT(Prj -> get_Name (CLEARED(&bstrName)));
				if (!wcsicmp (bstrName, V_BSTR(&vIndex))) {
					*ppIProject = Prj.detach();
					fFound = true;
					break;
				}
			}
			_ASSERTE(NULL != *ppIProject);

		} else
			return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProjects::Item");

	} COM_CATCH;

	if (!fFound)
		return REPORT_DBERROR(TRIASDB_E_UNKNOWN_PROJECT);

	return S_OK;
}

STDMETHODIMP CTRiASProjects::Remove(VARIANT Index)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return E_NOTIMPL;
}

STDMETHODIMP CTRiASProjects::_NewEnum (IUnknown **ppIEnum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIEnum) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProjects::_NewItem");

	return MakeEnumVARIANT (m_Enum, GetUnknown(), ppIEnum);
}

STDMETHODIMP CTRiASProjects::_Add(ITRiASProject *Project, VARIANT_BOOL fFullAdd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// testen, ob dieses Objekt noch nicht in der collection enthalten ist
	_ASSERTE(IsFirstOccurence (m_Enum, Project, ITRiASProject::get_Name, (CComBSTR *)NULL));

	return m_Enum -> AddItem (Project);
}

HRESULT CTRiASProjects::RemoveProject (ITRiASProject *pIPrj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	USES_CONVERSION;
	COM_TRY {
	CComBSTR bstrName;

		THROW_FAILED_HRESULT(pIPrj -> get_Name(CLEARED(&bstrName)));

	os_path target (OLE2A(bstrName));

	// Enumerator umkopieren und betreffendes Projekt rauswerfen
	WTRiASProject Prj;
	WEnumWTRiASProject Enum;

		THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
		THROW_FAILED_HRESULT(m_Enum -> Clear());

		for (Enum -> Reset(); S_OK == Enum -> Next (1, &Prj, NULL); /**/)
		{
			THROW_FAILED_HRESULT(Prj -> get_Name(CLEARED(&bstrName)));
			if (target != os_path(OLE2A(bstrName)))
				m_Enum -> AddItem (Prj);
		}
		_ASSERTE(0 == Enum -> Count() || Enum -> Count() == m_Enum -> Count() +1);

	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASProjects::_Clone(ITRiASProjects **ppIPrjs)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIPrjs) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProjects::_Clone");

CComObject<CTRiASProjects> *pNew = NULL;

	COM_TRY {
		THROW_FAILED_HRESULT(CComObject<CTRiASProjects>::CreateInstance (&pNew));
		THROW_FAILED_HRESULT(pNew -> InitEnum (m_Enum));

		THROW_FAILED_HRESULT(pNew -> put_Application (m_Application));
		THROW_FAILED_HRESULT(pNew -> put_Parent (m_pIParent));

	WTRiASProjects Prjs (pNew);		// pending AddRef

		*ppIPrjs = Prjs.detach();

	} COM_CATCH_OP(delete pNew);

	return S_OK;
}

STDMETHODIMP CTRiASProjects::SetEventSink (IUnknown *pIUnk, VARIANT_BOOL fAdvise)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (fAdvise) {
		_ASSERTE(m_dwCookie == 0);
		return AtlAdvise (pIUnk, GetUnknown(), IID_ITRiASProjectEvents, &m_dwCookie);
	} else {
		_ASSERTE(m_dwCookie != 0);

	DWORD dwCookie = m_dwCookie;

		m_dwCookie = 0L;
		return AtlUnadvise (pIUnk, IID_ITRiASProjectEvents, dwCookie);
	}
}

///////////////////////////////////////////////////////////////////////////////
// *** ITRiASProjectEvents methods
STDMETHODIMP CTRiASProjects::ProjectToCreate (BSTR Name)
{ 
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASProjects::ProjectCreated (IDispatch *pIPrj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
	WTRiASProject Prj (pIPrj);

		THROW_FAILED_HRESULT(_Add(Prj, VARIANT_TRUE));
	
	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASProjects::OpeningProject (BSTR Name, VARIANT_BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASProjects::ProjectToOpen (BSTR Name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASProjects::ProjectIsOpening (IDispatch *pIPrj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASProjects::ProjectOpened (IDispatch *pIPrj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
	WTRiASProject Prj (pIPrj);

		THROW_FAILED_HRESULT(_Add(Prj, VARIANT_TRUE));
	
	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASProjects::ClosingProject (IDispatch *pIPrj, VARIANT_BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASProjects::ProjectToClose (IDispatch *pIPrj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	USES_CONVERSION;
	COM_TRY {
	WTRiASProject Prj (pIPrj);

		THROW_FAILED_HRESULT(RemoveProject(Prj));
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASProjects::ProjectClosed (BSTR Name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASProjects::Save (IDispatch *pIPrj, IUnknown *Stg, VARIANT_BOOL fSameAsLoad)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASProjects::SaveCompleted (IDispatch *pIPrj, VARIANT Stg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASProjects::HandsOffStorage (IDispatch *pIPrj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASProjects::ErrorOpeningProject (IDispatch *pIPrj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

