// OBJS_EDBS.h : Deklaration von COBJS_EDBS

#ifndef __OBJS_EDBS_H_
#define __OBJS_EDBS_H_

#include "resource.h"       // Hauptsymbole

#include "EDBS_Objekt.h"

/////////////////////////////////////////////////////////////////////////////
// COBJS_EDBS
class ATL_NO_VTABLE CEDBS_Objekte : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEDBS_Objekte, &CLSID_EDBS_Objekte>,
	public IDispatchImpl<IEDBS_Objekte, &IID_IEDBS_Objekte, &LIBID_TRiAS_EDBS>
{
public:
	CEDBS_Objekte();
	~CEDBS_Objekte();

DECLARE_REGISTRY_RESOURCEID(IDR_EDBS_Objekte)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEDBS_Objekte)
	COM_INTERFACE_ENTRY(IEDBS_Objekte)
//DEL 	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY2(IDispatch, IEDBS_Objekte)
END_COM_MAP()

// IOBJS_EDBS
public:
	STDMETHOD(get_Object)(/*[in]*/BSTR Objektnummer, /*[out, retval]*/ IDispatch* *pVal);
	CMapStringToOb mmapObjects;

// prototyp für internen Datenaustausch
public:
//	STDMETHOD(get_Item)(/*[in, out]*/ VARIANT* vntIndexKey, /*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(get_Item)(/*[in, out]*/ VARIANT* vntIndexKey, /*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get__NewEnum)(/*[out, retval]*/ IUnknown* *pVal);
	STDMETHOD(get_Count)(/*[out, retval]*/ long *pVal);
	CComObject<CEDBS_Objekt> *GetObjekt(CString strKey);
	IEDBS_Objekt *GetObjEDBS(CString strKey);
};

#endif //__OBJS_EDBS_H_
