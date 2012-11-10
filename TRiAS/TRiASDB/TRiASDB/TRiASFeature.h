///////////////////////////////////////////////////////////////////////////
// TRiASFeature.h : Declaration of the CTRiASFeature

#if !defined(_TRIASFEATURE_H__7C8CB9B9_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
#define _TRIASFEATURE_H__7C8CB9B9_2EA9_11d1_969E_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

#include <Atl/Ciid.h>
#include <Atl/AtlCtlEx.h>
#include <Com/OleObjectNotImpl.h>

#import "tlb/TRiASUI.tlb"	\
	raw_interfaces_only		\
	raw_dispinterfaces		\
	no_namespace			\
	named_guids

#include "CPTRiASPropertyEvents.h"		// connection point

#include "TRiASDBDispIds.h"
#include "TRiASProperties.h"
#include "PropertySupport.h"
#include "PropertyBase.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASFeature

class ATL_NO_VTABLE CTRiASFeature : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public ISupportErrorInfo,
	public IOleObjectNotImpl,
	public IPersistStreamInit,
	public CManagePropertySupport<CTRiASFeature>,
	public CManagePropertyBase<CTRiASFeature>,
	public CProxyITRiASPropertyEvents<CTRiASFeature>,
	public IConnectionPointContainerImpl<CTRiASFeature>,
	public CReportErrorComCoClass<CTRiASFeature, &CLSID_TRiASFeature, &IID_ITRiASFeature>,
	public ISpecifyPropertyPagesExImpl<CTRiASFeature>,
#if defined(_DUMP_PENDING_OBJECTS)
	public IDumpObjectImpl<CTRiASFeature>,
#endif // defined(_DUMP_PENDING_OBJECTS)
	public IProvideClassInfo2Impl<&CLSID_TRiASFeature, &IID_ITRiASPropertyEvents, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public IDispatchImpl<ITRiASFeature, &IID_ITRiASFeature, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	typedef IConnectionPointContainerImpl<CTRiASFeature> CPC;

	CTRiASFeature()
		: m_pICallback(NULL), m_hFeature(NULL), m_rgType(FEATURETYPE_Unknown), m_lLength(255),
		  m_fIsDirty(false), m_fIsInitialized(false),
		  m_bstrName(g_cbNil), m_bstrDesc(g_cbNil)
	{
	}

	_COMX_PERF_OBJECTCOUNT_IMPL(CTRiASFeature)

	DECLARE_ONE_SIZE_PRIVATE_HEAP2(CTRiASFeature);
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASFEATURE)
	DECLARE_AGGREGATABLE_EX2(CTRiASFeature)

	BEGIN_COM_MAP(CTRiASFeature)
		COM_INTERFACE_ENTRY(ITRiASFeature)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASFeature)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IOleObject)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
		COM_INTERFACE_ENTRY(ITRiASPropertySupport)		// --> CManagePropertySupport
		COM_INTERFACE_ENTRY(ITRiASPropertyMapHandler)	// --> CManagePropertySupport
		COM_INTERFACE_ENTRY(ITRiASPropertyBase)
		COM_INTERFACE_ENTRY(ITRiASBase)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY_IID(_ATL_IIDOF(IPersistStream), IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersist)
		COM_INTERFACE_ENTRY_IID(IID_ISpecifyPropertyPages, ISpecifyPropertyPagesExImpl<CTRiASFeature>)
		COM_INTERFACE_ENTRY_DUMPOBJECT()
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CTRiASFeature)
		CONNECTION_POINT_ENTRY(IID_ITRiASPropertyEvents)
	END_CONNECTION_POINT_MAP()

	BEGIN_PROPERTYSUPPORT_MAP(CTRiASFeature)
		PROPERTYSUPPORT_ENTRY_DEFAULT(CLSID_TRiASAutoSaveProperty)
	END_PROPERTYSUPPORT_MAP()

///////////////////////////////////////////////////////////////////////////////
// PropertyPageSupport

// PropertyPages für Editierung der Parameter der Objekteigenschaft
	BEGIN_PROPERTY_MAP_DESIGN(CTRiASFeature)
		PROP_PAGE(CLSID_EditFeatureParamDlg)
	END_PROPERTY_MAP()

	BEGIN_PROPERTY_MAP_RUNTIME(CTRiASFeature)
	END_PROPERTY_MAP()

///////////////////////////////////////////////////////////////////////////////
// 
	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	void FinalRelease (void);

	IDispatch *GetDispatch() { return static_cast<ITRiASFeature *>(this); }

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID);

// IPersistStream
	STDMETHOD(IsDirty)();
	STDMETHOD(Load)(LPSTREAM pStm);
	STDMETHOD(Save)(LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(ULARGE_INTEGER *pcbSize);

// IPersistStreamInit
	STDMETHOD(InitNew)();

// IOleObject
	STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASFeature
public:
	STDMETHOD(Clone)(/*[out, retval]*/ ITRiASFeature **ppIFeat);

	STDMETHOD(Eval)(/*[in]*/ ITRiASObject *Obj, /*[out, retval]*/ VARIANT *Val);
	STDMETHOD(EvalEx)(/*[in]*/ ITRiASObject *Obj, /*[in, out]*/ SAFEARRAY **ppConstraints, /*[out, retval]*/ VARIANT *Val);
	STDMETHOD(Update)(/*[in]*/ ITRiASObject *Obj, /*[in]*/ VARIANT Val);

	STDMETHOD(get_Updatable)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_Updatable)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(get_Length)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Length)(/*[in]*/ long newVal);
	STDMETHOD(get_Type)(/*[out, retval]*/ FEATURETYPE *pVal);
	STDMETHOD(put_Type)(/*[in]*/ FEATURETYPE newVal);
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Description)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);

	STDMETHOD(get_Handle)(/*[out, retval]*/ INT_PTR *pVal);
	STDMETHOD(put_Handle)(/*[in]*/ INT_PTR newVal);

	STDMETHOD(get_Parent)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Parent)(/*[in]*/ IDispatch *newVal);
	STDMETHOD(get_Application)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Application)(/*[in]*/ IDispatch *newVal);

	STDMETHOD(putref_FeatureCallback)(ITRiASFeatureCallback *pICB);

// ITRiASPropertySupport
	STDMETHOD(CreateProperty)(/*[in]*/ BSTR Name, /*[out, retval]*/ ITRiASProperty **Property);
	STDMETHOD(RemoveProperty)(/*[in]*/ BSTR Name);

// ITRiASPropertyBase
	HRESULT IsInitialized()
	{
		if (m_fIsInitialized) 
			return S_OK;
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	}

protected:
	HRESULT Fire_ModifyingFeature (IDispatch *pIViewItem, VARIANT_BOOL *pVal);
	HRESULT Fire_FeatureToModify (IDispatch *pIViewItem);
	HRESULT Fire_FeatureModified (BSTR Name);

	HRESULT EnsureFeatureHandle (OBJECTMAPMODE rgMode, HFEATURE hFeatNew = NULL);
	HRESULT GetMkName (BSTR *pbstrMkName, OBJECTMAPMODE rgMode);
	HRESULT GetContainerMoniker (IMoniker **ppIMk);
	HRESULT GetThisMoniker (DWORD dwWhich, IMoniker **ppIMk, OBJECTMAPMODE rgMode = OBJECTMAPMODE_UsePredefinedHandle);

public:
static HRESULT GetFeatureMoniker (INT_PTR hFeature, BSTR bstrName, IMoniker *pIContMk, DWORD dwWhich, IMoniker **ppIMk, OBJECTMAPMODE rgMode = OBJECTMAPMODE_UsePredefinedHandle);

private:
	CComPtr<IDispatch> m_Application;
	CComPtr<IDispatch> m_Parent;

	CComBSTR m_bstrName;		// Name dieser Objekteigenschaft
	CComBSTR m_bstrDesc;		// BeschreibungsInfo dieser Objekteigenschaft

	HFEATURE m_hFeature;
	FEATURETYPE m_rgType;
	long m_lLength;

	bool m_fIsDirty;
	bool m_fIsInitialized;

	ITRiASFeatureCallback *m_pICallback;

#if defined(_IMPLEMENT_LOCKFEATURE)
	WTRiASObject m_LockedObj;	// support for ITRiASLockFeature
#endif // defined(_IMPLEMENT_LOCKFEATURE)
};

///////////////////////////////////////////////////////////////////////////////
// Versionen des PersistStream-Formates
const long FEATURE_SIGNATURE = 0x54414546L;		// "FEAT"
const long FEATURE_VERSION_MINOR_MASK = 0xff;
const long FEATURE_VERSION_100 = 0x0100L;
const long LASTKNOWN_FEATURE_VERSION = FEATURE_VERSION_100;

#endif // !defined(_TRIASFEATURE_H__7C8CB9B9_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
