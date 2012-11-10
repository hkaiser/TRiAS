///////////////////////////////////////////////////////////////////////////
// TRiASProjects.h : Declaration of the CTRiASProjects

#if !defined(_TRIASPROJECTS_H__7C8CB9BE_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
#define _TRIASPROJECTS_H__7C8CB9BE_2EA9_11d1_969E_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// SmartIF's etc. 
// {422FB8C2-39C3-11d1-96B9-00A024D6F582}
extern "C" const IID __declspec(selectany) IID_IEnumTRiASProject = 
	{0x422fb8c2,0x39c3,0x11d1,{0x96,0xb9,0x00,0xa0,0x24,0xd6,0xf5,0x82}};

DefineEnumerator2(WTRiASProject, IID_IEnumTRiASProject);		// NEnumWTRiASProject
DefineSmartEnumerator2(WTRiASProject, IID_IEnumTRiASProject);	// WEnumWTRiASProject

/////////////////////////////////////////////////////////////////////////////
// CTRiASProjects
class ATL_NO_VTABLE CTRiASProjects : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public ISupportErrorInfo,
	public CReportErrorComCoClass<CTRiASProjects, &CLSID_TRiASProjects, &IID_ITRiASProjects>,
	public ITRiASProjectEvents,
	public IDispatchImpl<ITRiASProjects, &IID_ITRiASProjects, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	typedef ITRiASProjects interface_t;
	typedef ITRiASProject controlled_t;

	CTRiASProjects()
		: m_dwCookie(0), m_pIParent(NULL)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASProjects)
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASPROJECTS)

	BEGIN_COM_MAP(CTRiASProjects)
		COM_INTERFACE_ENTRY(ITRiASProjectEvents)
		COM_INTERFACE_ENTRY(ITRiASProjects)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASProjects)
		COM_INTERFACE_ENTRY(ITRiASBase)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	HRESULT FinalConstruct (void);
	void FinalRelease();
	HRESULT InitEnum (IEnum<WTRiASProject> *pTarget)
	{ 
		return pTarget -> Clone (m_Enum.ppi()); 
	}

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASProjects
public:
	STDMETHOD(RemoveProject)(/*[in]*/ ITRiASProject *Project);
	STDMETHOD(SetEventSink)(/*[in]*/ IUnknown *pIUnk, /*[in]*/ VARIANT_BOOL fAdvise);
	STDMETHOD(_Clone)(/*[out, retval]*/ ITRiASProjects **Projects);
	STDMETHOD(_Add)(/*[in]*/ ITRiASProject *Project, /*[in, optional, defaultvalue(VARIANT_TRUE)]*/ VARIANT_BOOL FullAdd);

	STDMETHOD(_NewEnum)(/*[out, retval]*/ IUnknown **ppIEnum);
	STDMETHOD(Remove)(/*[in]*/ VARIANT Index);
	STDMETHOD(Item)(/*[in]*/ VARIANT Index, /*[out, retval]*/ ITRiASProject **Project);
	STDMETHOD(Add)(/*[in]*/ BSTR Name, /*[out, retval]*/ ITRiASProject **Project);

	STDMETHOD(get_ActiveProject)(/*[out, retval]*/ ITRiASProject **pVal);
	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Parent)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Parent)(/*[in]*/ IDispatch *newVal);
	STDMETHOD(get_Application)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Application)(/*[in]*/ IDispatch *newVal);

// *** ITRiASProjectEvents methods
	STDMETHOD(ProjectToCreate)(BSTR Name);
	STDMETHOD(ProjectCreated)(IDispatch *pIPrj);
	STDMETHOD(OpeningProject)(BSTR Name, VARIANT_BOOL *pVal);
	STDMETHOD(ProjectToOpen)(BSTR Name);
	STDMETHOD(ProjectIsOpening)(IDispatch *pIPrj);
	STDMETHOD(ProjectOpened)(IDispatch *pIPrj);
	STDMETHOD(ClosingProject)(IDispatch *pIPrj, VARIANT_BOOL *pVal);
	STDMETHOD(ProjectToClose)(IDispatch *pIPrj);
	STDMETHOD(ProjectClosed)(BSTR Name);
	STDMETHOD(Save)(IDispatch *pIPrj, IUnknown *Stg, VARIANT_BOOL fSameAsLoad);
	STDMETHOD(SaveCompleted)(IDispatch *pIPrj, VARIANT Stg);
	STDMETHOD(HandsOffStorage)(IDispatch *pIPrj);
	STDMETHOD(ErrorOpeningProject)(IDispatch *pIPrj);

private:
	WEnumWTRiASProject m_Enum;	// eigener Enumerator

	CComPtr<IDispatch> m_Application;
	IDispatch *m_pIParent;			// no AddRef (fully contained)

	DWORD m_dwCookie;
};

#endif // !defined(_TRIASPROJECTS_H__7C8CB9BE_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
