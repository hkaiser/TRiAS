// PropertyAction, welche Objekte aus RechercheFenster auswählt und zusammenstellt
// File: FILTSCR.H

#if !defined(_FILTSCR_H)
#define _FILTSCR_H

#include "propactb.hxx"		// CPropertyAction

class CFilterScriptPropAct : 
	public CPropertyAction,
	public CComObjectRoot,
	public IObjectWithSiteImpl<CFilterScriptPropAct>,
	public CComCoClass<CFilterScriptPropAct,&CLSID_FilterScript>
{
private:
	CFilterScriptDlg2 *m_pFilterScriptDlg;
	CString m_strDesc;
	CString m_strScriptName;
	BOOL m_fIsDirty;		// DirtyFlag
	BOOL m_fIsInitialized;	// ist fertig initialisiert
	HPROJECT m_hPrCtx;

	HRESULT LoadName (LPSTREAM pStm);
	HRESULT SaveName (LPSTREAM pStm, BOOL fClearDirty);

public:
	BEGIN_COM_MAP(CFilterScriptPropAct)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistPropertyBag)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPropertyInfo)
		COM_INTERFACE_ENTRY(IObjectWithSite)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CFilterScriptPropAct)		// class factory
	DECLARE_REGISTRY_RESOURCEID(IDR_FILTERSCRIPT_REG)

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
	STDMETHOD(IsDirty)	();
	STDMETHOD(Load)		(LPSTREAM pStm);
	STDMETHOD(InitNew)	();
	STDMETHOD(Save)		(LPSTREAM pStm, BOOL fClearDirty);

// IPersistPropertyBag
	STDMETHOD(Load)(THIS_ IPropertyBag *pBag, IErrorLog *pLog);

// sonstiges
	void SetDirty (BOOL fDirty = true);
};

#endif // _FILTSCR_H
