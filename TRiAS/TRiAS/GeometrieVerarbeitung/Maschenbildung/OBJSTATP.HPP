// PropertyAction: Zeigt Anzahl der Objekte (Flächen, Linien, Punkte, Text)
// File: OBJSTATP.HPP

#if !defined(_OBJSTATP_HPP)
#define _OBJSTATP_HPP

class CObjStatDlg;

class CResultPropAction : public CPropertyAction,
						  public CComObjectRoot,
						  public CComCoClass<CResultPropAction, &CLSID_ResultPropAction>
{
private:
	CObjStatDlg *m_pCfgDlg;
	CString m_strDesc;

	BOOL m_bIsDirty;		// DirtyFlag
	BOOL m_bIsInitialized;	// ist fertig initialisiert
	HDEX m_hDex;

public:
	BEGIN_COM_MAP(CResultPropAction)
		COM_INTERFACE_ENTRY2 (IPropertyAction, IPropertyAction2)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPropertyInfo)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CResultPropAction)		// class factory
	DECLARE_REGISTRY_RESOURCEID(IDR_RESULT_PROPACT_RGS)

	CResultPropAction (void);
	~CResultPropAction (void);

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
protected:
	void FinalRelease (void);
};

#endif	// _OBJSTATP_HPP

