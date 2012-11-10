// Alle ObjektPropertyExtensions aller Erweiterungen --------------------------
// File: ALLOPROP.HXX

#if !defined(_ALLOPROP_HXX)
#define _ALLOPROP_HXX

class CEnumObjectProperties;		// forward declaration

class CAllProperties : 
	public IObjectProps,
	public IObjectProps2 
{
private:
#if defined(_DEBUG)
	DWORD 			m_dwRefCnt;	// reference count (debugging purposes only)
#endif // _DEBUG
	ExtensionList *		m_pEL;		// back pointer
	CEnumAllObjectProperties *m_pObjEnum;	// ObjectProps
	CEnumAllClassProperties *m_pClsEnum;	// ObjectProps

	LONG m_lRefONr;

protected:
	bool FInit (void);

public:
		CAllProperties (ExtensionList *pEL);
		~CAllProperties (void);

static CAllProperties *CreateInstance (ExtensionList *pEL);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IObjectProps specific functions ***
	STDMETHOD(EnumObjectProps) (THIS_ IEnumObjProps **ppEnumProp);
	STDMETHOD(EnumClassProps) (THIS_ IEnumClassProps **ppEnumProp);

// Funktionen, welche gerufen werden, wenn BezugsObjekt/BezugsKlasse geändert wurde
	STDMETHOD(OnNewReferenceObject) (THIS_ LONG lRefONr);
	STDMETHOD(OnNewReferenceClass) (THIS_ IEnumLONG *pEnumObjs);
	STDMETHOD(GetGroupInfo) (THIS_ LPSTR pGroupName, WORD ulLen, DWORD *pdwFlags);

// *** IObjectProps2 specific functions ***
	STDMETHOD(CreateNewProp) (THIS_ LPCSTR pcName, DWORD dwFlags, LONG lONr, VARIANT vOptData, REFIID riid, LPVOID *ppIObjProp);
	STDMETHOD(DeleteProp) (THIS_ LPCSTR pcName, LONG lONr);

// Definieren einer ObjProperty 
	bool AddPropertyFunction (LPOBJECTPROPERTY pIObjProp, LPCSTR pcGroup = NULL);
	bool AddPropertyFunction (LPCLASSPROPERTY pIObjProp, LPCSTR pcGroup = NULL);
	
	bool RemovePropertyFunction (LPCSTR pcName);
	bool RemoveAllObjPropertyFunctions (void);		
	bool RemoveAllClsPropertyFunctions (void);		

	HRESULT CopyObjPropsToEnum (COleExtension *pExt, LONG lRefONr = 0L);
	HRESULT CopyClsPropsToEnum (COleExtension *pExt, IEnumLONG *pIEnum = NULL);

	bool AddInternalObjProperties (LONG lRefONr);
	bool AddInternalClsProperties (void);

	HRESULT CreateNewInternalProp (LPCSTR pcName, DWORD dwFlags, LONG lONr, VARIANT vOptData, REFIID riid, LPVOID *ppIObjProp);

};

#endif // _ALLOPROP_HXX

