// DynQueryObjEnums.h: Definition of the DynQueryObjEnums class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DYNQUERYOBJENUMS_H__DAC01788_E30C_11D0_95FE_00A024D6F582__INCLUDED_)
#define AFX_DYNQUERYOBJENUMS_H__DAC01788_E30C_11D0_95FE_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "DynQueryRes.h"       // main symbols
#include <ospace/uss/std/map.h>

/////////////////////////////////////////////////////////////////////////////
// DynQueryObjEnums

class CDynQueryObjEnums : 
	public IPersistStreamInit,
	public IDynQueryObjEnums,
	public CComObjectRoot,
	public CComCoClass<CDynQueryObjEnums, &CLSID_DynQueryObjEnums>
{
private:
	typedef map<os_string, CVisEnum, less<os_string> > CEnumList;
	CEnumList m_mapEnums;
	os_string m_strView;

	bool m_fInitialized;
	bool m_fIsDirty;

public:
		CDynQueryObjEnums() { m_fInitialized = false; m_fIsDirty = false; }
		~CDynQueryObjEnums() {}

	BEGIN_COM_MAP(CDynQueryObjEnums)
		COM_INTERFACE_ENTRY(IDynQueryObjEnums)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	END_COM_MAP()

	DECLARE_REGISTRY_RESOURCEID(IDS_DYNQUERYOBJENUMS);

// IDynQueryObjEnums
public:
	STDMETHOD(get_ViewName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ViewName)(/*[in]*/ BSTR newVal);

	STDMETHOD(Find)(/*[in]*/ long lONr, /*[in, out]*/ BSTR *pbstrName, /*[in, out]*/ DVisInfo **ppIVis);
	STDMETHOD(Erase)(BSTR bstrName);
	STDMETHOD(Insert)(/*[in]*/ BSTR bstrName, /*[in]*/ IEnumObjectsByNumber *pIObjs, /*[in]*/ DVisInfo *pIVis);
	STDMETHOD(ClassFromIdent) (/*[in]*/ long lIdent, /*[out, retval]*/ BSTR *pbstrOKS);
	STDMETHOD(IdentFromClass) (/*[in]*/ BSTR bstrOKS, /*[out, retval]*/ long *plIdent);
	STDMETHOD(EnumIdents) (/*[out]*/ IUnknown **pIIdents);

// *** IPersist methods ***
	STDMETHOD(GetClassID)(THIS_ CLSID *pClsID);

// *** IPersistStream methods ***
	STDMETHOD(IsDirty)(THIS);
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER * pcbSize);

// *** IPersistStreamInit methods ***
	STDMETHOD(InitNew)(THIS);
};

#define DYNQUERYOBJENUMS_PERSISTVERSION		0x01000000L

#endif // !defined(AFX_DYNQUERYOBJENUMS_H__DAC01788_E30C_11D0_95FE_00A024D6F582__INCLUDED_)
