// PropertyAction, welche Objekte aus RechercheFenster auswählt und zusammenstellt
// File: FILTSCR.H

#if !defined(_FILTSCR_H)
#define _FILTSCR_H

#include "propactb.hxx"		// CPropertyAction

class CFilterScriptPropAct : 
	public CPropertyAction,
	public CComObjectRoot,
	public CComCoClass<CFilterScriptPropAct, &CLSID_FilterScript>
{
private:
	CFilterScriptDlg *m_pFilterScriptDlg;
	string m_strDesc;

	bool m_fIsDirty;		// DirtyFlag
	bool m_fIsInitialized;	// ist fertig initialisiert

public:
	BEGIN_COM_MAP(CFilterScriptPropAct)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersist)
		COM_INTERFACE_ENTRY(IPropertyInfo)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CFilterScriptPropAct)		// class factory
	DECLARE_REGISTRY_RESOURCEID(IDR_FILTERSCRIPT_REG);	// registry

		CFilterScriptPropAct (void);
		~CFilterScriptPropAct (void);

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
	STDMETHOD (BeginAction) (THIS_ IProgressIndicator * pIProgInd);
	STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);
	STDMETHOD (DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);

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

#endif // _FILTSCR_H
