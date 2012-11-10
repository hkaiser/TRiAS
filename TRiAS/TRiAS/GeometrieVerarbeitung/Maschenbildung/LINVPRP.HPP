// PropertyAction, welche Linienobjekte verbindet
// File: LINVPRP.HPP

#if !defined(_LINVPRP_HPP)
#define _LINVPRP_HPP

class CParamDialog;

class CLinVerPropAct : public CPropertyAction,
					   public CComObjectRoot,
					   public IObjectWithSiteImpl<CLinVerPropAct>,
					   public CComCoClass<CLinVerPropAct, &CLSID_LinienVerfolgungsPropAct>
{
private:
	CParamDialog *m_pCfgDlg;
	CString m_strDesc;

	BOOL m_bIsDirty;		//	DirtyFlag
	BOOL m_bIsInitialized;	//	ist fertig initialisiert
	BOOL m_bHasInitData;	//	hat init. Daten
	HDEX m_hDex;			//	Handle der Erweiterung
	HRESULT m_hResult;		//	Handle steuert UNDO

	double m_dFuzzy;
	BOOL m_bUnionMaschen, m_bUnionLines, m_bDeleteOldLines, m_bOutputMerkmal;
	BOOL m_bMarkObjects;	// #HK971218

public:
	BEGIN_COM_MAP(CLinVerPropAct)
		COM_INTERFACE_ENTRY2 (IPropertyAction, IPropertyAction2)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IPersistPropertyBag)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPropertyInfo)
		COM_INTERFACE_ENTRY(IObjectWithSite)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CLinVerPropAct)		// class factory
	DECLARE_REGISTRY_RESOURCEID(IDR_MASCHEN_PROPACT_RGS)
	
	CLinVerPropAct (void);
	~CLinVerPropAct (void);

static HRESULT CreateInstance (IClassProperty **ppIClsProp)
	{ return _CreatorClass::CreateInstance(NULL, IID_IClassProperty, (LPVOID *)ppIClsProp); }

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
//fje
// IPersistPropertyBag
	STDMETHOD(Load)(THIS_ IPropertyBag *pBag, IErrorLog *pLog);
	
//	sonstiges
	void SetDirty (BOOL bDirty = TRUE);

protected:
	void FinalRelease (void);
	HRESULT EnsureOptionsIF();
};

#endif	// _LINVPRP_HPP

