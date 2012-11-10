//////////////////////////////////////////////////////////////////////
// GDODBEngine.h: Definition of the CGDODBEngine class
//

#if !defined(AFX_GDODBENGINE_H__36D78AF5_2F23_11D1_969F_00A024D6F582__INCLUDED_)
#define AFX_GDODBENGINE_H__36D78AF5_2F23_11D1_969F_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CGDODBEngine

// EnumeratorObjekt für LPOLESTR's
typedef CComEnum<IEnumString, &IID_IEnumString, LPOLESTR, _Copy<LPOLESTR> > CEnumString;
typedef	map< CComBSTR, DGDOServerRegEntry* > mapOfDataServers;

class CGDODBEngine : 
	public CComCoClass<CGDODBEngine, &CLSID_GDODBEngine>,
	public CErrSupport<CGDODBEngine, &IID_IGDODBEngine>,
	public IDispatchImpl<IGDODBEngine, &IID_IGDODBEngine, TLB_TRiASGDO_SIGNAT>,
	public IDispatchImpl<ITRiASDBEngine, &IID_ITRiASDBEngine, TLB_TRiASDB_SIGNAT>,
	public IConnectionPointContainerImpl<CGDODBEngine>,
	public CComObjectRootEx<CComObjectThreadModel>
{
private:
	bool m_bStarted;

public:
	CGDODBEngine()
		: m_bStarted(false)
	{
	}

	DECLARE_DEBUG_FUNCENTRY_0(CGDODBEngine,FinalConstruct);
	DECLARE_DEBUG_FUNCENTRY_0(CGDODBEngine,FinalRelease);

	DECLARE_REGISTRY_RESOURCEID(IDR_GDODBENGINE)
	DECLARE_CLASSFACTORY_SINGLETON(CGDODBEngine)	// DBEngines existieren nur einmal

	_ATLX_DEBUG_ADDREF_RELEASE_IMPL(CGDODBEngine)
	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CGDODBEngine)
	BEGIN_COM_MAP(CGDODBEngine)
		COM_INTERFACE_ENTRY2(IDispatch,IGDODBEngine)
		COM_INTERFACE_ENTRY(IGDODBEngine)
		COM_INTERFACE_ENTRY(ITRiASDBEngine)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CGDODBEngine)
	END_CONNECTION_POINT_MAP()

public:
// IGDODBEngine
// ITRiASDBEngine
	DECLARE_DEBUG_FUNCENTRY_1(CGDODBEngine,put_UserName,/*[in]*/ BSTR, newVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODBEngine,put_Password,/*[in]*/ BSTR, newVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODBEngine,get_Version,/*[out, retval]*/ BSTR*, pVal);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODBEngine,get_Description,/*[out, retval]*/ BSTR *, pVal);

	DECLARE_DEBUG_FUNCENTRY_1(CGDODBEngine,Start,/*[in]*/ STARTMODE, Mode);
	DECLARE_DEBUG_FUNCENTRY_0(CGDODBEngine,Stop);
	DECLARE_DEBUG_FUNCENTRY_1(CGDODBEngine,EnumDataBaseTypes,/*[out, retval]*/ IUnknown **, ppIEnum);

// globale Funktionen
	DGMServerTransService *GetGMServerTransService() const { return m_pDGMServerTransService; }
	DGMGeometryStorageService * GetGMGeometryStorageService() const { return m_pDGMGeometryStorageService; }

private:
	WDGMServerTransService m_pDGMServerTransService;
	WDGMGeometryStorageService m_pDGMGeometryStorageService;
};

extern CGDODBEngine *g_pDBEngine;		// globale Instanz dieser Engine

#endif // !defined(AFX_GDODBENGINE_H__36D78AF5_2F23_11D1_969F_00A024D6F582__INCLUDED_)
