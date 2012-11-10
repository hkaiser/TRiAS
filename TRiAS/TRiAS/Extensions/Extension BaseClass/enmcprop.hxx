// Enumerator der ObjektClassProperties einer Erweiterung ---------------------
// File ENMCPROP.HXX

#if !defined(_ENMCPROP_HXX)
#define _ENMCPROP_HXX

// referenz auf eine Objekteigenschaft, häng im Baum des Enumerators ----------
class CClsProp {
private:
	string m_strName;
	ULONG m_ulID;
	LPCLASSPROPERTY m_pIClsProp;

public:
		CClsProp (ULONG uiID, LPCLASSPROPERTY pIClsProp);
		~CClsProp (void);

inline	void GetClsProp (LPCLASSPROPERTY *ppIClsProp)
	{ *ppIClsProp = m_pIClsProp; (*ppIClsProp) -> AddRef(); }
inline	string *GetPropName (void) { return &m_strName; }
inline	DWORD GetPropID (void) { return m_ulID; }

friend	void *GetClsPropName (void *pObj);
friend	void *GetClsPropID (void *pObj);
friend	int StringCmp (void *pStr1, void *pStr2);
friend	int ULongCmp (void *pUL1, void *pUL2);
};

// Baum der ObjektKlasseneigenschaften, die im Enumerator enthalten sind ------
class CClsPropsName : public CTree {
protected:
	void UserDelete (void *pObj);

public:
		CClsPropsName (void) : CTree (GetClsPropName, StringCmp) {}
		~CClsPropsName (void);

	CClsProp *AddProp (ULONG uiID, LPCLASSPROPERTY pIClsProp);
	bool FindProp (LPCSTR pName, LPCLASSPROPERTY *ppIClsProp);
	bool DeleteProp (LPCSTR pName);
};
DeclareLock (CClsPropsName, CClsProp);

class CClsPropsID : public CTree {	// ohne Löschen
protected:
	void UserDelete (void *pObj);

public:
		CClsPropsID (void) : 
			CTree (GetClsPropID, ULongCmp, CONTFLAG(CFSyncThreads)) {}
		~CClsPropsID (void);

	bool AddProp (CClsProp *pClsProp);
	bool FindProp (ULONG ulID, LPCLASSPROPERTY *ppIClsProp);
	bool DeleteProp (ULONG ulID);
};
typedef CClsProp CClsProp1;
DeclareLock (CClsPropsID, CClsProp1);

class CClsProps {	// enthält DoppelBaum auf ClsProps
private:
	CClsPropsName m_PropsName;	// Baum der ClsProperties (nach Namen)
	CClsPropsID m_PropsID;		// nach FuncID

public:
		CClsProps (void) {}
		~CClsProps (void) {}

	DWORD AddProp (ULONG uiID, LPCLASSPROPERTY pIClsProp);
	bool FindProp (LPCSTR pName, LPCLASSPROPERTY *ppIClsProp)
		{ return m_PropsName.FindProp (pName, ppIClsProp); }
	bool FindProp (ULONG ulID, LPCLASSPROPERTY *ppIClsProp)
		{ return m_PropsID.FindProp (ulID, ppIClsProp); }
	bool DeleteProp (ULONG ulID);
	bool EveryDelete (void);
	
inline	ULONG Count (void) { return m_PropsID.Count(); }

friend class CEnumClassProperties;
};
	
// Enumerator aller Objekteigenschaften einer Erweiterung ---------------------
class CEnumClassProperties : public IEnumClassProps {
private:
	DWORD m_dwRefCnt;		// reference count

	DWORD m_dwCookie;		// next cookie for next ClsProp
	CClsProps m_Props;		// ObjectProperties
	CTable m_tCurr;			// current ClsProp
	ULONG m_ulCurr;			// counter

	ULONG GetCookie (void);		// get next cookie thread save

protected:
	inline bool FInit (void) { return true; }

public:
		CEnumClassProperties (void);
		~CEnumClassProperties (void);

static CEnumClassProperties *CreateInstance (void);

// *** IUnknown methods
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj);
	STDMETHOD_ (ULONG, AddRef) (THIS);
	STDMETHOD_ (ULONG, Release) (THIS);
	
// *** IEnumUnknown methods
	STDMETHOD (Next) (THIS_ ULONG celt, LPUNKNOWN *rgelt, ULONG *pceltFetched);
	STDMETHOD (Skip) (THIS_ ULONG celt);
	STDMETHOD (Reset) (THIS);
	STDMETHOD (Clone) (THIS_ IEnumUnknown ** ppenm);
	
// *** IEnumClsProps methods
	STDMETHOD (FindByID) (THIS_ ULONG ulFuncID, IClassProperty **ppOProp);
	STDMETHOD (FindByName) (THIS_ LPCSTR pKeyName, IClassProperty **ppOProp);

inline	DWORD AddProp (LPCLASSPROPERTY pIClsProp) { return m_Props.AddProp (GetCookie(), pIClsProp); }
inline	DWORD AddProp (DWORD dwCookie, LPCLASSPROPERTY pIClsProp) { return m_Props.AddProp (dwCookie, pIClsProp); }
inline	bool DeleteProp (ULONG ulID) { return m_Props.DeleteProp (ulID); }
inline	bool EveryDelete (void) { return m_Props.EveryDelete(); }
};

#endif // _ENMCPROP_HXX

