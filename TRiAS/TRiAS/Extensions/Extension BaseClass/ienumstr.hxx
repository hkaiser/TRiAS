// Enumeration aller Strings in irgend einem Zusammenhang ---------------------
// File: IENUMSTR.HXX

#if !defined(_IENUMSTR_HXX)
#define _IENUMSTR_HXX

#if !defined(_STRDUP_HXX)
#include <strdup.hxx>
#endif

#if !defined(WIN32)
#define LPWSTR	LPTSTR
#endif // WIN32

// ----------------------------------------------------------------------------
// Item in CStringArray (String) ----------------------------------------------
class CStringItem {
private:
	LPWSTR m_pItem;
	
public:
#if defined(WIN32)
		CStringItem (LPCWSTR pStr) { m_pItem = StrDupW ((LPCWSTR)pStr, 0); }
#endif // WIN32
		CStringItem (LPCSTR pStr) { m_pItem = StrDupW ((LPSTR)pStr); }
		~CStringItem (void) { if (m_pItem) StrFreeW (m_pItem); }

	LPWSTR FString (void) const { return m_pItem; }
};

// ArrayContainer, der die ObjektNummern eines Enumerators enthält ------------
class CStringArray : public CArrayContainer {
protected:
	void UserDelete (void *pObj);
	
public:
		CStringArray (void);
		~CStringArray (void);
};
DeclareLock (CStringArray, CStringItem);


// BasisKlasse zur Enumeration von Strings ------------------------------------
class CImpIEnumStrings : public IEnumString {
private:
	ULONG		m_cRef;         // Interface reference count.

protected:
	CStringArray	*m_pacStrings;	// ArrayContainer der Objekte
	unsigned long	m_ulCur;	// aktuelle Position
	
	bool 		Init (void);	// Initialisierungen

public:
#if defined(WIN32)
	bool 		AddString (LPCWSTR pStr);	// String hinzufügen
#endif // WIN32
	bool 		AddString (LPCSTR pStr);		// String hinzufügen
		
		CImpIEnumStrings (void);
	virtual ~CImpIEnumStrings (void);

static CImpIEnumStrings *CreateInstance (void);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG,AddRef) (THIS);
	STDMETHOD_(ULONG,Release) (THIS);

// *** IEnumString methods ***
	STDMETHOD(Next) (THIS_ ULONG celt, LPWSTR *rgelt, ULONG *pceltFetched);
	STDMETHOD(Skip) (THIS_ ULONG celt);
	STDMETHOD(Reset) (THIS);
	STDMETHOD(Clone) (THIS_ IEnumString **ppenm);
};
typedef CImpIEnumStrings *LPIMPIENUMSTRINGS;


#endif //_IENUMSTR_HXX
