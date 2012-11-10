// PropertyAction, welche Linienobjekte verbindet
// File: VERSCHNT.HPP

#ifndef _VERSCHNT_HPP
#define _VERSCHNT_HPP

class CVerschnittPage;

class CVerschnittPropAct : public CPropertyAction,
						   public CComObjectRoot,
						   public CComCoClass<CVerschnittPropAct, &CLSID_VerschnittPropAct>
{
private:
	CVerschnittPage *m_pCfgDlg;
	CString m_strDesc;

	BOOL m_bIsDirty;		//	DirtyFlag
	BOOL m_bIsInitialized;	//	ist fertig initialisiert
	BOOL m_bHasInitData;	//	hat init. Daten
	HDEX m_hDex;			//	Handle der Erweiterung
	HRESULT m_hResult;		//	Handle steuert UNDO

	double m_dFuzzy,
		   m_dDangleLen;	
	BOOL   m_bDeleteOldLines;	
	BOOL   m_bMarkObjects;

public:
	BEGIN_COM_MAP(CVerschnittPropAct)
		COM_INTERFACE_ENTRY2 (IPropertyAction, IPropertyAction2)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPropertyInfo)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CVerschnittPropAct)		// class factory
	DECLARE_REGISTRY_RESOURCEID(IDR_VERSCHNITT_PROPACT_RGS)
	
	CVerschnittPropAct (void);
	~CVerschnittPropAct (void);

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
	
//	sonstiges
	void SetDirty (BOOL bDirty = TRUE);
	BOOL HasInitData (void) { return m_bHasInitData;}

protected:
	void FinalRelease (void);
};

#endif	// _VERSCHNT_HPP


