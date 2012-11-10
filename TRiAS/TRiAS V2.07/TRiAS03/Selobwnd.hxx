// PropertyAction, welche Objekte aus RechercheFenster auswählt und zusammenstellt
// File: SELOBWND.HXX

#if !defined(_SELOBWND_HXX)
#define _SELOBWND_HXX

#include <propactn.h>
#include <selobwnd.h>

#include "propactb.hxx"		// CPropertyAction
#include "selobdlg.hxx"		// CSelectObjWndDlg

class CSelObjWndPropAct : 
	public CPropertyActionExt,	// JG 980916
	public CComObjectRoot,
	public CComCoClass<CSelObjWndPropAct, &CLSID_SelectFromObjectWindow>
{
private:
	class CSelectObjWndDlg *m_pCfgDlg;
	string m_strDesc;

	bool m_fIsDirty;		// DirtyFlag
	bool m_fIsInitialized;	// ist fertig initialisiert

	HWND m_hWnd;
	DWORD m_dwFlags;
	bool m_fHasInitData;
	LONG m_lActObj;

protected:
	HRESULT GetEnumLONG (LONG lONr, IEnum<LONG> **ppIEnum);

public:
	BEGIN_COM_MAP(CSelObjWndPropAct)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStream)
		COM_INTERFACE_ENTRY(IPropertyInfo)
	END_COM_MAP()

	DECLARE_AGGREGATABLE(CSelObjWndPropAct)		// class factory
	DECLARE_STATIC_REGISTRY_RESOURCEID(IDR_PROPINFO_OBJWND)

		CSelObjWndPropAct (void);
		~CSelObjWndPropAct (void);

static HRESULT CreateInstance (IClassProperty **ppIClsProp)
	{ return _CreatorClass::CreateInstance(NULL, IID_IClassProperty, (LPVOID *)ppIClsProp); }

// IClassProperty specific functions 
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
					    LPSTR pHelpFile, ULONG *pulHelpCtx);

// IPropertyAction methods
	STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
					LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt);
	STDMETHOD (PreConfigPages) (THIS_ IDataObject *pIDataObj, DWORD dwFlags);
	STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

// IPropertyInfo specific functions 
	STDMETHOD(SetPropInfo) (THIS_ LPCSTR pBuffer, DWORD dwFlags);

// IPersist methods
	STDMETHOD(GetClassID)(THIS_ LPCLSID lpClassID);

// IPersistStreamInit methods
	STDMETHOD(IsDirty)(THIS);
	STDMETHOD(Load)(THIS_ LPSTREAM pStm);
	STDMETHOD(InitNew)(THIS);

// sonstiges
	void SetDirty (bool fDirty = true);
};

#endif // _SELOBWND_HXX
