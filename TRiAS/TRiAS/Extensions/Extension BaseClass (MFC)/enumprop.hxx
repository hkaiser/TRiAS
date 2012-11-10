// Enumerator der ObjektProperties einer Erweiterung --------------------------
// File ENUMPROP.HXX

#if !defined(_ENUMPROP_HXX)
#define _ENUMPROP_HXX

// Referenz auf eine Objekteigenschaft, häng im Baum des Enumerators ----------
class CObjPropCreator;

class CObjProp {
private:
	string m_strName;
	ULONG m_ulID;
	LPOBJECTPROPERTY m_pIObjProp;

protected:
		CObjProp (void);

public:
		CObjProp (CObjProp &rOProp);
		~CObjProp (void);

static CObjProp *CreateInstance (ULONG uiID, LPOBJECTPROPERTY pIObjProp);

	bool FInit (ULONG uiID, LPOBJECTPROPERTY pIObjProp);

inline	void GetObjProp (LPOBJECTPROPERTY *ppIObjProp)
	{ *ppIObjProp = m_pIObjProp; (*ppIObjProp) -> AddRef(); }
inline	string *GetPropName (void) { return &m_strName; }
inline	DWORD GetPropID (void) { return m_ulID; }

friend	void *GetPropName (void *pObj);
friend	void *GetPropID (void *pObj);
friend	int StringCmp (void *pStr1, void *pStr2);
friend	int ULongCmp (void *pUL1, void *pUL2);
};

// Baum der Objekteigenschaften, die im Enumerator enthalten sind -------------
class CObjPropsName : public CTree {
protected:
	void UserDelete (void *pObj);

public:
		CObjPropsName (void) : CTree (GetPropName, StringCmp) {}
		~CObjPropsName (void);

	CObjProp *AddProp (ULONG uiID, LPOBJECTPROPERTY pIObjProp);
	bool FindProp (LPCSTR pName, LPOBJECTPROPERTY *ppIObjProp);
	bool DeleteProp (LPCSTR pName);
};
DeclareLock (CObjPropsName, CObjProp);

class CObjPropsID : public CTree {	// ohne Löschen
protected:
	void UserDelete (void *pObj);

public:
		CObjPropsID (void) : 
			CTree (GetPropID, ULongCmp, CONTFLAG(CFSyncThreads)) {}
		~CObjPropsID (void);

	bool AddProp (CObjProp *pObjProp);
	bool FindProp (ULONG ulID, LPOBJECTPROPERTY *ppIObjProp);
	bool DeleteProp (ULONG ulID);
};
typedef CObjProp CObjProp1;
DeclareLock (CObjPropsID, CObjProp1);

class CObjProps {	// enthält DoppelBaum auf ObjProps
private:
	CObjPropsName m_PropsName;	// Baum der ObjProperties (nach Namen)
	CObjPropsID m_PropsID;		// nach FuncID

public:
		CObjProps (void) {}
		~CObjProps (void) {}

	DWORD AddProp (ULONG uiID, LPOBJECTPROPERTY pIObjProp);
	bool FindProp (LPCSTR pName, LPOBJECTPROPERTY *ppIObjProp)
		{ return m_PropsName.FindProp (pName, ppIObjProp); }
	bool FindProp (ULONG ulID, LPOBJECTPROPERTY *ppIObjProp)
		{ return m_PropsID.FindProp (ulID, ppIObjProp); }
	bool DeleteProp (ULONG ulID);
	bool EveryDelete (void);
	
inline	ULONG Count (void) { return m_PropsID.Count(); }

friend class CEnumObjectProperties;
};
	
// Enumerator aller Objekteigenschaften einer Erweiterung ---------------------
class CEnumObjectProperties : public IEnumObjProps {
private:
	DWORD m_dwRefCnt;		// reference count

	DWORD m_dwCookie;		// next cookie for next ObjProp
	CObjProps m_Props;		// ObjectProperties
	CTable m_tCurr;			// current Objprop
	ULONG m_ulCurr;			// counter

	ULONG GetCookie (void);		// get next cookie thread save

protected:
	inline bool FInit (void) { return true; }

public:
		CEnumObjectProperties (void);
		~CEnumObjectProperties (void);

static CEnumObjectProperties *CreateInstance (void);

// *** IUnknown methods
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj);
	STDMETHOD_ (ULONG, AddRef) (THIS);
	STDMETHOD_ (ULONG, Release) (THIS);
	
// *** IEnumUnknown methods
	STDMETHOD (Next) (THIS_ ULONG celt, LPUNKNOWN *rgelt, ULONG *pceltFetched);
	STDMETHOD (Skip) (THIS_ ULONG celt);
	STDMETHOD (Reset) (THIS);
	STDMETHOD (Clone) (THIS_ IEnumUnknown ** ppenm);
	
// *** IEnumObjProps methods
	STDMETHOD (FindByID) (THIS_ ULONG ulFuncID, IObjectProperty **ppOProp);
	STDMETHOD (FindByName) (THIS_ LPCSTR pKeyName, IObjectProperty **ppOProp);

inline	DWORD AddProp (LPOBJECTPROPERTY pIObjProp) { return m_Props.AddProp (GetCookie(), pIObjProp); }
inline	DWORD AddProp (DWORD dwCookie, LPOBJECTPROPERTY pIObjProp) { return m_Props.AddProp (dwCookie, pIObjProp); }
inline	bool DeleteProp (ULONG ulID) { return m_Props.DeleteProp (ulID); }
inline	bool EveryDelete (void) { return m_Props.EveryDelete(); }
};

#endif // _ENUMPROP_HXX

