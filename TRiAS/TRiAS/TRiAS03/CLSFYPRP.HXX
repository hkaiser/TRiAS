///////////////////////////////////////////////////////////////////////////
// @doc
// @module CLSFYPRP.HXX | PropertyAction für Classifikation nach Objekteigenschaft 

#if !defined(_CLSFYPRP_HXX__1E709224_67C1_11D1_B9EA_080036D63803__INCLUDED_)
#define _CLSFYPRP_HXX__1E709224_67C1_11D1_B9EA_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include <propactn.h>
#include <clsfyprp.h>
#if _TRiAS_VER < 0x0300
#include <xtsnguid.h>
#endif // _TRiAS_VER < 0x0300

#include "propactb.hxx"		// CPropertyAction
#include "seloprop.h"


class CClsfyPropAct :
	public CPropertyActionExt,	// JG980914	(+ext)
	public CComObjectRoot,
	public IObjectWithSiteImpl<CClsfyPropAct>,
	public CComCoClass<CClsfyPropAct, &CLSID_ClassifyByObjProp>
{
private:
	class CClassifyDlg *m_pCfgDlg;
	string m_strDesc;

	bool m_fIsDirty;		// DirtyFlag
	bool m_fIsInitialized;	// ist fertig initialisiert

	bool m_fHasInitData;	// InitialisierungsDaten sind gesetzt
	OBJPROPRESULT m_caSelInfo;

	long m_lPacket;

public:
	BEGIN_COM_MAP(CClsfyPropAct)
		COM_INTERFACE_ENTRY_EX(IPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IPropertyAction3)
		COM_INTERFACE_ENTRY(IPersistPropertyBag)
		COM_INTERFACE_ENTRY_EX(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY_EX(IPropertyInfo)
		COM_INTERFACE_ENTRY(IObjectWithSite)
	END_COM_MAP()

	DECLARE_AGGREGATABLE(CClsfyPropAct)		// class factory
	DECLARE_STATIC_REGISTRY_RESOURCEID(IDR_PROPINFO_CLASSIFYBYOBJPROP)

		CClsfyPropAct ();
		~CClsfyPropAct (void);

// IClassProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
						LPSTR pHelpFile, ULONG *pulHelpCtx);

// IPropertyAction methods
	STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
				LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt);
	STDMETHOD (PreConfigPages) (THIS_ IDataObject *pIDataObject, DWORD dwFlags);
	STDMETHOD (DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
	STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

// IPropertyInfo specific functions 
	STDMETHOD(SetPropInfo) (THIS_ LPCSTR pBuffer, DWORD dwFlags);

// IPersist methods
	STDMETHOD(GetClassID)(THIS_ LPCLSID lpClassID);

// IPersistStreamInit methods
	STDMETHOD(IsDirty)(THIS);
	STDMETHOD(Load)(THIS_ LPSTREAM pStm);
	STDMETHOD(Save)(THIS_ LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER *pcbSize);
	STDMETHOD(InitNew)(THIS);

// IPersistPropertyBag
	STDMETHOD(Load)(THIS_ IPropertyBag *pBag, IErrorLog *pLog);

// sonstiges
	void SetDirty (bool fDirty = true);
};

#endif // !defined(_CLSFYPRP_HXX__1E709224_67C1_11D1_B9EA_080036D63803__INCLUDED_)
