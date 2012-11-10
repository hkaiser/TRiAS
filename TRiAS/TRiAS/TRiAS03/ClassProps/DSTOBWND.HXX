// PropertyAction, welche Objekte aus RechercheFenster auswählt und zusammenstellt
// File: DSTOBWND.HXX

#if !defined(_DSTOBWND_HXX)
#define _DSTOBWND_HXX

#include <propactn.h>
#include <dstobwnd.h>

#include "propactb.hxx"
#include "dstobdlg.hxx"

class CDestObjWndPropAct : 
	public CPropertyAction,
	public CComObjectBase<&CLSID_DestinationObjectWindow>
{
private:
	CDestObjWndDlg *m_pCfgDlg;
	string m_strDesc;

	bool m_fIsDirty;		// DirtyFlag
	bool m_fIsInitialized;	// ist fertig initialisiert

public:
	BEGIN_COM_MAP(CDestObjWndPropAct)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersist)
		COM_INTERFACE_ENTRY(IPropertyInfo)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CDestObjWndPropAct)		// class factory

		CDestObjWndPropAct (void);
		~CDestObjWndPropAct (void);

static HRESULT CreateInstance (IClassProperty **ppIClsProp)
	{ return _CreatorClass::CreateInstance(NULL, IID_IClassProperty, (LPVOID *)ppIClsProp); }

// *** IPropertyAction methods
	STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
				LPARAM lParam, DWORD dwFlags, LPCSTR pcDesc, UINT *puiCnt);
	STDMETHOD (DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
	STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

// *** IClassProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
						LPSTR pHelpFile, ULONG *pulHelpCtx);

// *** IClassProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(Reset)(THIS);
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile, ULONG *pulHelpCtx);

// *** IPropertyInfo specific functions 
	STDMETHOD(SetPropName) (THIS_ LPCSTR pBuffer);

// *** IPersist methods
	STDMETHOD(GetClassID)(THIS_ LPCLSID lpClassID);

// *** IPersistStreamInit methods
	STDMETHOD(IsDirty)(THIS);
	STDMETHOD(Load)(THIS_ LPSTREAM pStm);
	STDMETHOD(InitNew)(THIS);

// sonstiges
	void SetDirty (bool fDirty = true);
};

#endif // _DSTOBWND_HXX
