///////////////////////////////////////////////////////////////////////////
// ActionProperty, welche Ident/Objekttypen auswählt und zusammenstellt -------
// File: DELOBPRP.HXX

#if !defined(_DELOBPRP_HXX__0E7FBA35_4D26_11d1_96E7_00A024D6F582__INCLUDED_)
#define _DELOBPRP_HXX__0E7FBA35_4D26_11d1_96E7_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <propactn.h>
#include <DelObPrp.h>

#include "multipi.h"
#include "propactb.hxx"		// CPropertyAction

class CDelObjPropAct : 
	public CPropertyAction,
	public CComObjectRoot,
	public CComCoClass<CDelObjPropAct, &CLSID_DeleteObjects>
{
private:
	string m_strDesc;
	WProgressIndicator2 m_Progress;

	bool m_fIsInitialized;	// ist fertig initialisiert

public:
	BEGIN_COM_MAP(CDelObjPropAct)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStream)
		COM_INTERFACE_ENTRY(IPropertyInfo)
	END_COM_MAP()

	DECLARE_AGGREGATABLE(CDelObjPropAct)		// class factory
	DECLARE_STATIC_REGISTRY_RESOURCEID(IDR_PROPINFO_DELOBJECT)

		CDelObjPropAct (void);
		~CDelObjPropAct (void);

static HRESULT CreateInstance (IClassProperty **ppIClsProp)
	{ return _CreatorClass::CreateInstance(NULL, IID_IClassProperty, (LPVOID *)ppIClsProp); }

// IClassProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
						LPSTR pHelpFile, ULONG *pulHelpCtx);

// IPropertyAction methods
	STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
				LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt);
	STDMETHOD (BeginAction) (THIS_ IProgressIndicator *pIProgInd);
	STDMETHOD (DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
	STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

// IPropertyInfo specific functions 
	STDMETHOD(SetPropInfo) (THIS_ LPCSTR pBuffer, DWORD dwFlags);

// IPersist methods
	STDMETHOD(GetClassID)(THIS_ LPCLSID lpClassID);

// IPersistStreamInit methods
	STDMETHOD(IsDirty)(THIS);
	STDMETHOD(Load)(THIS_ LPSTREAM pStm);
	STDMETHOD(InitNew)(THIS);
};

#endif // !defined(_DELOBPRP_HXX__0E7FBA35_4D26_11d1_96E7_00A024D6F582__INCLUDED_)
