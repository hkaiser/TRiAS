///////////////////////////////////////////////////////////////////////////
// TRiASViewItem.h : Declaration of the CTRiASViewItem

#if !defined(_TRIASVIEWITEM_H__7C8CB9B7_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
#define _TRIASVIEWITEM_H__7C8CB9B7_2EA9_11d1_969E_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Atl/CieThis.h>

#include "CPTRiASPropertyEvents.h"		// connection point

#include "resource.h"					// main symbols

#include "TRiASDBEngine.h"
#include "TRiASProperties.h"
#include "PropertySupport.h"
#include "PropertyBase.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface2(DVisInfo, IID_DVisInfo);

const int OBJSHANDLECOUNT = 5;		// Punkt, Linie, Fläche, Text, Komplex

/////////////////////////////////////////////////////////////////////////////
// CTRiASViewItem
class ATL_NO_VTABLE CTRiASViewItem : 
	public CReportErrorComCoClass<CTRiASViewItem, &CLSID_TRiASViewItem, &IID_ITRiASViewItem>,
	public CProxyITRiASPropertyEvents<CTRiASViewItem>,
	public CManagePropertySupport<CTRiASViewItem>,
	public CManagePropertyBase<CTRiASViewItem>,
	public ISupportErrorInfo,
	public IPersistStreamInit,
	public IConnectionPointContainerImpl<CTRiASViewItem>,
	public CComObjectRootEx<CComObjectThreadModel>,
	public ITRiASPropertyEvents,
	public ITRiASObjectsEvents,
	public IProvideClassInfo2Impl<&CLSID_TRiASViewItem, &IID_ITRiASPropertyEvents, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public IDispatchImpl<ITRiASViewItem, &IID_ITRiASViewItem, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	CTRiASViewItem() :
		m_fIsInitialized(false), m_fIsDirty(false), m_fShouldRemoved(false),
		m_bstrDesc(g_cbNil), m_bstrMkName(g_cbNil),
		m_dwObjsCookie(0L)
	{
		m_rgTypes = OBJECTTYPE_Unknown;
		m_rgDefTypes = OBJECTTYPE_Unknown;
		m_rgPreDefinedTypes = OBJECTTYPE_Unknown;
		memset (m_ObjsHandles, '\0', sizeof(INT_PTR)*_countof(m_ObjsHandles));
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASViewItem)
//	_ATLX_DEBUG_ADDREF_RELEASE_IMPL(CTRiASViewItem)
	DECLARE_ONE_SIZE_PRIVATE_HEAP()
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASVIEWITEM)

	BEGIN_COM_MAP(CTRiASViewItem)
		COM_INTERFACE_ENTRY(ITRiASViewItem)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASViewItem)
		COM_INTERFACE_ENTRY(ITRiASBase)
		COM_INTERFACE_ENTRY(ITRiASPropertySupport)		// --> CManagePropertySupport
		COM_INTERFACE_ENTRY(ITRiASPropertyMapHandler)	// --> CManagePropertySupport
		COM_INTERFACE_ENTRY(ITRiASPropertyBase)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY_IID(_ATL_IIDOF(IPersistStream), IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersist)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
		COM_INTERFACE_ENTRY(ITRiASPropertyEvents)
		COM_INTERFACE_ENTRY(ITRiASObjectsEvents)
		COM_INTERFACE_ENTRY_THIS()
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CTRiASViewItem)
		CONNECTION_POINT_ENTRY(IID_ITRiASPropertyEvents)
	END_CONNECTION_POINT_MAP()

	BEGIN_PROPERTYSUPPORT_MAP(CTRiASViewItem)
		PROPERTYSUPPORT_ENTRY_DEFAULT(CLSID_TRiASAutoSaveProperty)
	END_PROPERTYSUPPORT_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	void FinalRelease (void)
	{
		for (int i = 0; i < _countof(m_VisInfo); i++) 
			m_VisInfo[i].Assign (NULL);

		m_Parent = NULL;
		m_Application = NULL;
	}
	IDispatch *GetDispatch() { return static_cast<ITRiASViewItem *>(this); }

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID);

// IPersistStream
	STDMETHOD(IsDirty)();
	STDMETHOD(Load)(LPSTREAM pStm);
	STDMETHOD(Save)(LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(ULARGE_INTEGER *pcbSize);

// IPersistStreamInit
	STDMETHOD(InitNew)();

// ITRiASPropertySupport
	STDMETHOD(CreateProperty)(/*[in]*/ BSTR Name, /*[out, retval]*/ ITRiASProperty **Property);
	STDMETHOD(RemoveProperty)(/*[in]*/ BSTR Name);

// ITRiASPropertyEvents
	STDMETHOD(CreatingProperty)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(PropertyToCreate)(/*[in]*/ BSTR Name);
	STDMETHOD(PropertyCreated)(/*[in]*/ IDispatch *pIProp);
	STDMETHOD(ModifyingProperty)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(PropertyToModify)(/*[in]*/ BSTR Name);
	STDMETHOD(PropertyModified)(/*[in]*/ BSTR Name);
	STDMETHOD(DeletingProperty)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(PropertyToDelete)(/*[in]*/ BSTR Name);
	STDMETHOD(PropertyDeleted)(/*[in]*/ BSTR Name);

// ITRiASObjectsEvents
	STDMETHOD(CreatingObjects)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ObjectsToCreate)(/*[in]*/ BSTR Name);
	STDMETHOD(ObjectsCreated)(/*[in]*/ IDispatch *pIProp);
	STDMETHOD(ModifyingObjects)(/*[in]*/ CHANGEDOBJECTS rgMode, /*[in]*/ IDispatch *Objects, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ObjectsToModify)(/*[in]*/ CHANGEDOBJECTS rgMode, /*[in]*/ IDispatch *Objects);
	STDMETHOD(ObjectsModified)(/*[in]*/ CHANGEDOBJECTS rgMode, /*[in]*/ BSTR Name);
	STDMETHOD(DeletingObjects)(/*[in]*/ IDispatch *Objects, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ObjectsToDelete)(/*[in]*/ IDispatch *Objects);
	STDMETHOD(ObjectsDeleted)(/*[in]*/ BSTR Name);

// ITRiASViewItem
public:
	STDMETHOD(get_ObjectsMoniker)(/*[in]*/ OBJECTTYPE rgType, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ObjectsMoniker)(/*[in]*/ OBJECTTYPE rgType, /*[in]*/ BSTR newVal);
	STDMETHOD(get_Objects)(/*[in]*/ OBJECTTYPE rgType, /*[out, retval]*/ ITRiASObjects * *pVal);
	STDMETHOD(put_Objects)(/*[in]*/ OBJECTTYPE rgType, /*[in]*/ ITRiASObjects * newVal);
	STDMETHOD(get_VisInfo)(/*[in, optional, defaultvalue]*/ OBJECTTYPE rgType, /*[out, retval]*/ DVisInfo * *pVal);
	STDMETHOD(put_VisInfo)(/*[in, optional, defaultvalue]*/ OBJECTTYPE rgType, /*[in]*/ DVisInfo * newVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Description)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Types)(/*[out, retval]*/ OBJECTTYPE *pVal);
	STDMETHOD(put_Types)(/*[in]*/ OBJECTTYPE newVal);
	STDMETHOD(get_ObjectTypes)(/*[out, retval]*/ OBJECTTYPE *pVal);
	STDMETHOD(put_ObjectTypes)(/*[in]*/ OBJECTTYPE newVal);
	STDMETHOD(get_DefaultTypes)(/*[out, retval]*/ OBJECTTYPE *pVal);
	STDMETHOD(put_DefaultTypes)(/*[in]*/ OBJECTTYPE newVal);
	STDMETHOD(get_ItemCount)(/*[out, retval]*/ LONG *pVal);

	STDMETHOD(get_Parent)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Parent)(/*[in]*/ IDispatch *newVal);
	STDMETHOD(get_Application)(/*[out, retval]*/ IDispatch **pVal);
	STDMETHOD(put_Application)(/*[in]*/ IDispatch *newVal);

	HRESULT IsInitialized()
	{
		if (m_fIsInitialized) 
			return S_OK;
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	}

	bool GetShouldRemoved() { return m_fShouldRemoved; }
	void SetShouldRemoved(bool fFlag) { m_fShouldRemoved = fFlag; }

protected:
	int HasObjectsCollection (void)
	{
		for (int i = 0; i < _countof(m_ObjsHandles); i++) {
			if (NULL != m_ObjsHandles[i] || m_mkName[i].IsValid())
				return i;
		}
		return -1;	// keine ObjectsCollection gegeben
	}

	HRESULT Fire_ModifyingViewItem (IDispatch *pIViewItem, VARIANT_BOOL *pVal);
	HRESULT Fire_ViewItemToModify (IDispatch *pIViewItem);
	HRESULT Fire_ViewItemModified (BSTR Name);

	HRESULT RefreshNameOrOKS (BSTR bstrOldName);

private:
// allgemeine Daten
	CComPtr<IDispatch> m_Application;
	CComPtr<IDispatch> m_Parent;

	CComBSTR m_bstrDesc;
	CComBSTR m_bstrMkName;						// Moniker als Name, wenn keine Vis/Objs definiert sind

	OBJECTTYPE m_rgTypes;
	OBJECTTYPE m_rgDefTypes;
	OBJECTTYPE m_rgPreDefinedTypes;

	bool m_fIsDirty;
	bool m_fIsInitialized;
	bool m_fShouldRemoved;					// beim nächsten ConnectionToRemove aus der Ansicht werfen

	WMoniker m_mkName[OBJSHANDLECOUNT];			// Moniker auf ein evtl. später zu bindendes TRiASObjects- Objekt
	WDVisInfo m_VisInfo[OBJSHANDLECOUNT];		// VisualisierungsInfos für 4 Objekttypen + dont care
	HOBJECTS m_ObjsHandles[OBJSHANDLECOUNT];	// Zugehörige Objektmengen

	DWORD m_dwObjsCookie;						// Events von Objektmenge

friend class CTRiASObjectsWrapper;
};

///////////////////////////////////////////////////////////////////////////////
// Wrapper, der den Kontext für die Auflösung der HOBJECTS zu ITRiASObjects
// festlegt
extern const OBJECTTYPE __declspec(selectany) g_cbObjectTypes[] = {
	OBJECTTYPE_Point,
	OBJECTTYPE_Line,
	OBJECTTYPE_Area,
	OBJECTTYPE_Text,
};

class CTRiASObjectsWrapper
{
public:
	typedef HOBJECTS OBJSHANDLES[OBJSHANDLECOUNT];

	CTRiASObjectsWrapper (CTRiASViewItem *pItem) : 
		m_rHandles(pItem -> m_ObjsHandles), m_rrgTypes(pItem -> m_rgPreDefinedTypes) {}
	~CTRiASObjectsWrapper() {}

protected:
// Proxy ist für die Unterscheidung des lvalue/rvalue Einsatzes des operator[]
// notwendig
	class WTRiASObjectsProxy
	{
	public:
		WTRiASObjectsProxy (CTRiASObjectsWrapper &wrp, int iIndex) : 
			m_rObjs(wrp.m_Objects[iIndex]), m_rhObjs(wrp.m_rHandles[iIndex]),
			m_rrgTypes(wrp.m_rrgTypes), m_iIndex(iIndex)
		{}

	// assignment ops for use as lvalue
		WTRiASObjectsProxy &operator= (const WTRiASObjectsProxy &rhs)
		{
		HOBJECTS hObjs = rhs.m_rhObjs;

			m_rObjs = rhs.m_rObjs;
			if (m_rObjs.IsValid() && NULL == hObjs)
				m_rObjs -> get_Handle (reinterpret_cast<INT_PTR *>(&hObjs));
			m_rhObjs = hObjs;
			return *this;
		}
		WTRiASObjectsProxy &operator= (ITRiASObjects *rhs)
		{
			m_rObjs = rhs;
			if (m_rObjs.IsValid()) {
				if (SUCCEEDED(m_rObjs -> get_Handle (reinterpret_cast<INT_PTR *>(&m_rhObjs))))
					ClearType (m_rrgTypes, g_cbObjectTypes[m_iIndex]);
			} else
				m_rhObjs = NULL;
			return *this;
		}

	// op for use as rvalue
		operator WTRiASObjects& () const			// Objekt wird nicht wirklich verändert
		{
			return const_cast<WTRiASObjectsProxy *>(this) -> EnsureObjsObject();	// evtl. existierendes TRiASObjects Objekt besorgen
		}

	// overloading required functions of WTRiASObjects
		bool IsValid() { return EnsureObjsObject().IsValid(); }
		operator ITRiASObjects *() { return EnsureObjsObject().operator ITRiASObjects *(); }
		ITRiASObjects *operator-> () { _ASSERT(m_rObjs.IsValid()); return m_rObjs; }	// wird nur nach IsValid verwendet

	protected:
		WTRiASObjects &EnsureObjsObject()
		{
			if (!m_rObjs.IsValid() && NULL != m_rhObjs) {
			// beim ersten Mal muß das Handle über die globale Map aufgelöst werden
				COM_TRY {
				WUnknown Unk;

					THROW_FAILED_HRESULT(g_pDBEngine -> GetObjsObject (m_rhObjs, Unk.ppi()));
					return m_rObjs = Unk;
				} COM_CATCH_IGNORE;
				SetType (m_rrgTypes, g_cbObjectTypes[m_iIndex]);
			}
			return m_rObjs;		// wenn's nicht da ist, ist's eben nicht da
		}

	private:
		HOBJECTS &m_rhObjs;
		OBJECTTYPE &m_rrgTypes;
		int m_iIndex;
		WTRiASObjects &m_rObjs;
	};
	friend class WTRiASObjectsProxy;

public:
// assignment op for the const case
	const WTRiASObjectsProxy operator[] (int iIndex) const 
	{
		_ASSERTE(0 <= iIndex && iIndex < OBJSHANDLECOUNT);
		return WTRiASObjectsProxy(const_cast<CTRiASObjectsWrapper &>(*this), iIndex);
	}

// assignment op for the nonconst case
	WTRiASObjectsProxy operator[] (int iIndex)
	{
		_ASSERTE(0 <= iIndex && iIndex < OBJSHANDLECOUNT);
		return WTRiASObjectsProxy(*this, iIndex);
	}

private:
	OBJSHANDLES &m_rHandles;					// Referenz auf die ObjsHandles 
	OBJECTTYPE &m_rrgTypes;						// Referenz auf vordefinierte Objekttypen
	WTRiASObjects m_Objects[OBJSHANDLECOUNT];	// Zugehörige Objektmengen
};

///////////////////////////////////////////////////////////////////////////////
// Version des PersistStream-Formates
const long VIEWITEM_SIGNATURE = 0x4D544956L;	// "VITM"
const long VIEWITEM_VERSION_MINOR_MASK = 0xff;
const long VIEWITEM_VERSION_100 = 0x0100L;
const long VIEWITEM_VERSION_101 = 0x0101L;
const long VIEWITEM_VERSION_102 = 0x0102L;
const long VIEWITEM_VERSION_103 = 0x0103L;
const long VIEWITEM_VERSION_104 = 0x0104L;		// #HK990710
const long LASTKNOWN_VIEWITEM_VERSION = VIEWITEM_VERSION_104;

///////////////////////////////////////////////////////////////////////////////
// Mode in dem ObjectsDef gespeichert wurde
typedef enum tagSAVEMODE {
	SAVEMODE_UNKNOWN = 0,
	SAVEMODE_SAVEOBJECTMONIKER = 1,
	SAVEMODE_SAVEOBJECTDIRECTLY = 2,
} SAVEMODE;

#endif // !defined(_TRIASVIEWITEM_H__7C8CB9B7_2EA9_11d1_969E_00A024D6F582__INCLUDED_)
