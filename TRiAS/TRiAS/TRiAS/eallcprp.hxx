// Enumerator der Aller ObjektProperties aller Erweiterung --------------------
// File EALLCPRP.HXX

#if !defined(_EALLCPRP_HXX)
#define _ENUMCPRP_HXX

#include "propname.hxx"

// Der Enumerator muß Objekteigenschaften zur Verfügung stellen, deren Name ---
// nicht nur den eigenen Bezeichner liefert, sondern den vollen CPropertyName.
// Daher werden in diesem Enumerator die eigentlichen Objekteigenschaften 
// in eine übergeordnete OE embedded.

// ACHTUNG: Die Sache hat eine Haken: das Interface, welches im Enumerator hängt 
// ist nicht über QueryInterface erreichbar !

// Referenz auf eine Objekteigenschaft, hängt im Baum des Enumerators ---------
class CClsProp : public IClassProperty {
private:
	DWORD m_dwRefCnt;

	CPropertyName m_strName;	// voller Name der Objekteigenschaft
	LPCLASSPROPERTY m_pIClsProp;

public:
		CClsProp (LPCLASSPROPERTY pIClsProp, LPCSTR pcGroup);
		~CClsProp (void);

inline	CPropertyName *GetPropName (void) { return &m_strName; }
inline	string const &GetPropGroup (void) const { return m_strName.GetGroup(); }

inline	void GetClsProp (LPCLASSPROPERTY *ppIClsProp)
		{ *ppIClsProp = this; (*ppIClsProp) -> AddRef(); }

static	void *GetPropName (void *pObj);
static	int StringCmp (void *pStr1, void *pStr2);

public:
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IClassProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);

	STDMETHOD(Reset)(THIS);
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile, ULONG *pulHelpCtx);

	STDMETHOD(Eval)(THIS_ IEnumLONG *pEnumObj, LPSTR pBuffer, 
			ULONG ulLen, ULONG *pulWritten);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
};

// Baum der Objekteigenschaften, die im Enumerator enthalten sind -------------
class CClsProps : public CTree {
protected:
	void UserDelete (void *pObj);

public:
		CClsProps (void) : CTree (CClsProp::GetPropName, 
					  CClsProp::StringCmp, CFSyncThreads) {}
		~CClsProps (void);

	bool AddProp (LPCLASSPROPERTY pIClsProp, LPCSTR pcGroup = NULL);
	bool FindProp (LPCSTR pName, LPCLASSPROPERTY *ppIClsProp);
	bool DeleteProp (LPCSTR pName);
	
friend class CEnumAllClassProperties;
};
DeclareLock (CClsProps, CClsProp);
	
// Enumerator aller Objekteigenschaften einer Erweiterung ---------------------
class CEnumAllClassProperties : public IEnumClassProps {
private:
	DWORD m_dwRefCnt;		// reference count

	CClsProps m_Props;		// ObjectProperties
	CTable m_tCurr;			// current ClsProp
	ULONG m_ulCurr;			// counter

protected:
	inline bool FInit (void) { return true; }

public:
		CEnumAllClassProperties (void);
		~CEnumAllClassProperties (void);

static CEnumAllClassProperties *CreateInstance (void);

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
	STDMETHOD (FindByName) (THIS_ LPCSTR pKeyName, IClassProperty **ppOProp);

inline	bool AddProp (LPCLASSPROPERTY pIClsProp, LPCSTR pcGroup = NULL) 
	{ return m_Props.AddProp (pIClsProp, pcGroup); }

inline	bool DeleteProp (LPCSTR pName) { return m_Props.DeleteProp (pName); }
inline	bool EveryDelete (void) { return m_Props.EveryDelete(); }
};

#endif // _EALLCPRP_HXX

