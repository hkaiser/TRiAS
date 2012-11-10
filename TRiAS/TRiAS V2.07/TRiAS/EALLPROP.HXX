// Enumerator der Aller ObjektProperties aller Erweiterung --------------------
// File EALLPROP.HXX

#if !defined(_EALLPROP_HXX)
#define _ENUMPROP_HXX

#include "propname.hxx"

// Der Enumerator muß Objekteigenschaften zur Verfügung stellen, deren Name ---
// nicht nur den eigenen Bezeichner liefert, sondern den vollen CPropertyName.
// Daher werden in diesem Enumerator die eigentlichen Objekteigenschaften 
// in eine übergeordnete OE embedded.

// ACHTUNG: Die Sache hat eine Haken: das Interface, welches im Enumerator hängt 
// ist nicht über QueryInterface erreichbar !

// Referenz auf eine Objekteigenschaft, hängt im Baum des Enumerators ---------
class CObjProp : 
	public IObjectProperty 
{
private:
	DWORD m_dwRefCnt;		// reference count

	CPropertyName m_strName;	// Name der Objekteigenschaft
	LPOBJECTPROPERTY m_pIObjProp;

public:
		CObjProp (LPOBJECTPROPERTY pIObjProp, LPCSTR pcGroup);
		~CObjProp (void);

inline	CPropertyName *GetPropName (void) { return &m_strName; }
inline	string &GetPropGroup (void) { return m_strName.GetGroup(); }

inline	void GetObjProp (LPOBJECTPROPERTY *ppIObjProp)
		{ *ppIObjProp = this; (*ppIObjProp) -> AddRef(); }

static	void *GetPropName (void *pObj);
static	int StringCmp (void *pStr1, void *pStr2);

public:
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IObjectProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);

	STDMETHOD(Reset)(THIS);
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile, ULONG *pulHelpCtx);

	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, 
			ULONG *pulWritten);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
};

// Baum der Objekteigenschaften, die im Enumerator enthalten sind -------------
class CObjProps : 
	public CTree 
{
protected:
	void UserDelete (void *pObj);

public:
		CObjProps (void) : CTree (CObjProp::GetPropName, 
					  CObjProp::StringCmp, CFSyncThreads) {}
		~CObjProps (void);

	bool AddProp (LPOBJECTPROPERTY pIObjProp, LPCSTR pcGroup = NULL);
	bool FindProp (LPCSTR pName, LPOBJECTPROPERTY *ppIObjProp);
	bool DeleteProp (LPCSTR pName);
	
friend class CEnumAllObjectProperties;
};
DeclareLock (CObjProps, CObjProp);
	
// Enumerator aller Objekteigenschaften einer Erweiterung ---------------------
class CEnumAllObjectProperties : 
	public IEnumObjProps 
{
private:
	DWORD m_dwRefCnt;		// reference count

	CObjProps m_Props;		// ObjectProperties
	CTable m_tCurr;			// current ObjProp
	ULONG m_ulCurr;			// counter

protected:
	inline bool FInit (void) { return true; }

public:
		CEnumAllObjectProperties (void);
		~CEnumAllObjectProperties (void);

static CEnumAllObjectProperties *CreateInstance (void);

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
	STDMETHOD (FindByName) (THIS_ LPCSTR pKeyName, IObjectProperty **ppOProp);

inline	bool AddProp (LPOBJECTPROPERTY pIObjProp, LPCSTR pcGroup = NULL) 
	{ return m_Props.AddProp (pIObjProp, pcGroup); }

inline	bool DeleteProp (LPCSTR pName) { return m_Props.DeleteProp (pName); }
inline	bool EveryDelete (void) { return m_Props.EveryDelete(); }
};

#endif // _EALLPROP_HXX

