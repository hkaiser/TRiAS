// DatabaseBase.h : Declaration of the CDatabaseBase

#ifndef __DATABASEBASE_H_
#define __DATABASEBASE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDatabaseBase
class ATL_NO_VTABLE CDatabaseBase : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CDatabaseBase, &CLSID_DatabaseBase>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITRiASDatabase, &IID_ITRiASDatabase, &LIBID_TRIASIMPORTLib>,
	public ITriasXtensionSite,
	public ITRiASServiceProvider
{
protected:
	WTriasXtension	m_ImportXtension;
	CPDB			m_PDB;

	BOOL	m_bCanImpGeometry;
	BOOL	m_bCanImpFeatures;
	BOOL	m_bCanImpRelations;
	BOOL	m_bCanImpVisu;
	BOOL	m_bCanImpAnsiOEM;
	BOOL	m_bCanImpAll;
	BOOL	m_bOptImpGeometry;
	BOOL	m_bOptImpFeatures;
	BOOL	m_bOptImpRelations;
	BOOL	m_bOptImpVisu;
	BOOL	m_bOptImpAnsiOEM;
	BOOL	m_bOptImpAll;
	BOOL	m_bImpMultiFiles;
	BOOL	m_bImpShouldConfig;
	BOOL	m_bDynConfigInfo;

public:
	CDatabaseBase()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DATABASEBASE)

BEGIN_COM_MAP(CDatabaseBase)
	COM_INTERFACE_ENTRY(ITRiASDatabase)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(ITriasXtensionSite)
	COM_INTERFACE_ENTRY(ITRiASServiceProvider)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITriasXtensionSite
//	HRESULT CreateInstance([in] IUnknown *pUnkOuter, [in] REFCLSID rClsID, [in] REFIID riid, [out, iid_is(riid)] void **ppvObject);
//	HRESULT GetXtension([in] REFCLSID rClsID, [in] REFIID riid, [out, iid_is(riid)] void **ppvObject);
	STDMETHOD(CreateInstance)(/*[in]*/IUnknown *pUnkOuter,/*[in]*/REFCLSID rClsID,/*[in]*/REFIID riid,/*[out, iid_is(riid)]*/void **ppvObject);
	STDMETHOD(GetXtension)(/*[in]*/REFCLSID rClsID,/*[in]*/REFIID riid,/*[out, iid_is(riid)]*/void **ppvObject);

// ITRiASServiceProvider
public:
	STDMETHOD(DexExtensionProc)(WPARAM wParam, LPARAM lParam); 
	STDMETHOD(DexExtensionProc2)(HPROJECT hPr, WPARAM wParam, LPARAM lParam); 
	STDMETHOD(DexNotificationProc)(WPARAM wParam, LPARAM lParam, BOOL fPost); 
	STDMETHOD(DexDispatchProc)(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam); 

// ITRiASDatabase
public:
	STDMETHOD(get_Parent)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Parent)(/*[in]*/ IDispatch *newVal);
	STDMETHOD(get_Application)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Application)(/*[in]*/ IDispatch *newVal);
	STDMETHOD(get_TemporaryName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Temporary)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_Temporary)(/*[in]*/ VARIANT_BOOL newVal);

	STDMETHOD(get_Property)(BSTR Which, /*[out, retval]*/ ITRiASProperty * *pVal);
	STDMETHOD(get_Properties)(/*[out, retval]*/ ITRiASProperties * *pVal);

	STDMETHOD(get_IsDirty)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_IsDirty)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_Handle)(/*[out, retval]*/ LONG *pVal);
	STDMETHOD(get_VersionLong)(/*[out, retval]*/ LONG *pVal);
    STDMETHOD(get_Version)(BSTR *Version);

	STDMETHOD(get_SchemaUpdatable)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);

	STDMETHOD(OpenDatabase)(/*[in]*/ BSTR Name, /*[in, optional, defaultvalue]*/ VARIANT_BOOL Exclusive, /*[in, optional, defaultvalue]*/ VARIANT_BOOL ReadOnly, /*[in, optional, defaultvalue]*/ VARIANT_BOOL ModTrack, /*[in, optional, defaultvalue]*/ BSTR Source);
	STDMETHOD(OpenFilesAsDatabase)(/*[in]*/ IUnknown *pEnum, /*[in, optional, defaultvalue]*/ VARIANT_BOOL /*Exclusive*/, /*[in, optional, defaultvalue]*/ VARIANT_BOOL fReadOnly, /*[in, optional, defaultvalue]*/ VARIANT_BOOL /*ModTrack*/, /*[in, optional, defaultvalue]*/ BSTR Source);
	STDMETHOD(Close)(void);

    STDMETHOD(get_CollatingOrder)(long *pCollatingOrder);
    STDMETHOD(get_Connect)(BSTR *Connect);
    STDMETHOD(get_Transactions)(VARIANT_BOOL *Transactions);

    STDMETHOD(BeginTrans)(void);
    STDMETHOD(ClearModificationLog)(/*[in, optional, defaultvalue]*/ LONG Entry);
    STDMETHOD(CommitTrans)(void);
    STDMETHOD(Rollback)(void);

	STDMETHOD(CreateProperty)(/*[in]*/ BSTR Name, /*[out, retval]*/ ITRiASProperty **Property);
	STDMETHOD(RemoveProperty)(/*[in]*/ BSTR Name);

	STDMETHOD(CreateDatabase)(/*[in]*/ BSTR Name, /*[in]*/ BSTR Locale);
	STDMETHOD(CreateDatabaseFromFiles)(/*[in]*/  IUnknown *pEnum, /*[in]*/ BSTR Locale);
	STDMETHOD(SaveAs)(/*[in]*/ BSTR NewName);
	STDMETHOD(Save)();

	STDMETHOD(get_OpenedAsCopy)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_CouldOpenTarget)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_Updatable)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_Type)(/*[out, retval]*/ BSTR *pVal);

	STDMETHOD(_PreventGP)(BSTR) { return E_NOTIMPL; }

protected:
	long m_lUIDMCode;
	HRESULT DeleteHeader( LPARAM );
	HRESULT ModifyHeader( LPARAM );
	HRESULT ReadHeader( LPARAM );
	HRESULT QueryPBDData( LPARAM );
	HRESULT ModPBDData( LPARAM );
	DWORD m_dwImportFlags;
	BOOL UnLoadImportExtension();
	STDMETHOD(ImportData)( BSTR );
	STDMETHOD(ImportData)( IUnknown* );
	STDMETHOD(LoadImportExtension)( BSTR );
	STDMETHOD(EnumFileNames)( BSTR, IUnknown** );

	CComPtr<IDispatch> m_Application;
	CComPtr<IDispatch> m_Parent;

	CComBSTR m_bstrName;
};

#endif //__DATABASEBASE_H_
