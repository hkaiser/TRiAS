// File: WHEREPRP.HPP

#if !defined(_WHEREPRP_HPP)
#define _WHEREPRP_HPP

class CWherePage;
class CWhereKlauselPropAct : 
	public CPropertyAction,
	public CComObjectRoot,
	public CComCoClass<CWhereKlauselPropAct, &CLSID_WhereKlauselPropAct>,
	public IObjectWithSite
{
private:
	WUnknown m_objSite;
	CWherePage *m_pCfgDlg;
	CString m_strDesc;

	BOOL m_bIsDirty;		//	DirtyFlag
	BOOL m_bIsInitialized;	//	ist fertig initialisiert
	BOOL m_bHasInitData;	//	hat init. Daten
	
//	Nutzer eingaben
	CString m_strWhereKlausel;
	CString m_strDataSource;
	CString m_strTable;
	DataSourceType m_tpDataSource;

public:
	BEGIN_COM_MAP(CWhereKlauselPropAct)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPropertyInfo)
		COM_INTERFACE_ENTRY(IObjectWithSite)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CWhereKlauselPropAct)		// class factory
	DECLARE_REGISTRY_RESOURCEID(IDR_WHERE_PROPACT_RGS)
	
	CWhereKlauselPropAct (void);
	~CWhereKlauselPropAct (void);

// static HRESULT CreateInstance (IClassProperty **ppIClsProp)
// { return _CreatorClass::CreateInstance(NULL, IID_IClassProperty, (LPVOID *)ppIClsProp); }

//	IClassProperty specific functions 
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
					    LPSTR pHelpFile, ULONG *pulHelpCtx);

//	IPropertyAction methods
	STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
				LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt);
	STDMETHOD (PreConfigPages) (THIS_ IDataObject *pIDataObject, DWORD dwFlags);
	STDMETHOD (DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
	STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

//	IPropertyInfo specific functions 
	STDMETHOD(SetPropInfo) (THIS_ LPCSTR pBuffer, DWORD dwFlags);

//	IPersist methods
	STDMETHOD(GetClassID)(THIS_ LPCLSID lpClassID);

//	IPersistStreamInit methods
	STDMETHOD(InitNew)(THIS);

//	IPersistStream methods
	STDMETHOD(GetSizeMax)(ULARGE_INTEGER *pcbSize);
	STDMETHOD(IsDirty)(THIS);
	STDMETHOD(Load)(THIS_ LPSTREAM pStm);
	STDMETHOD(Save)(LPSTREAM pStm, BOOL fClearDirty);

//	IObjectWithSite
	STDMETHOD(SetSite)(/*[in]*/IUnknown * pUnkSite);
	STDMETHOD(GetSite)(/*[in]*/REFIID riid,
					   /*[out, iid_is(riid)]*/void ** ppvSite);
	
//	sonstiges
	void SetDirty (BOOL bDirty = TRUE);
};

#endif	// _WHEREPRP_HPP


