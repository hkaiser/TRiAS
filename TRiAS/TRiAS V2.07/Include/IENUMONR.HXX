// Enumeration aller ObjektNummern einer gegebenen Liste ----------------------
// File: IENUMONR.HXX

#if !defined(_IENUMONR_HXX)
#define _IENUMONR_HXX

#include <ienumobj.hxx>		// Interfacedeklaration

// ----------------------------------------------------------------------------
#if !defined(_DEFINED_ONRCNT)

const int DEFAULTONRCNT = 100;		// StandardAnzahl der gespeicherten Objekte

#define _DEFINED_ONRCNT
#endif // _DEFINED_ONRCNT

class CONrItem {
private:
	LONG m_lONr;

public:
		CONrItem (LONG lONr) : m_lONr (lONr) {}
		~CONrItem (void) {}

	LONG FONr (void) { return m_lONr; }
};

// ArrayContainer, der die ObjektNummern eines Enumerators enthält ------------
class CObjectArray : public CArrayContainer {
protected:
	void UserDelete (void *pObj);
	
public:
		CObjectArray (int iCnt = DEFAULTONRCNT);
		~CObjectArray (void);

	bool AddObject (LONG lONr);
};
DeclareLock (CObjectArray, CONrItem);


// BasisKlasse zur Enumeration von IUnknown's ------------------------------------
class CEnumObjectsByNumber : public IEnumLONG {
private:
	ULONG		m_dwRefCnt;     // Interface reference count.
	int 		m_iCnt;		// Anzahl der möglichen Undo's

protected:
	CObjectArray	m_Objs;		// ArrayContainer der Objekte
	ULONG		m_ulCur;	// aktuelle Position
	
	bool FInit (void);		// Initialisierungen

		CEnumObjectsByNumber (int iCnt);	// nicht direkt rufen

public:
	bool AddObject (LONG lONr);	// ObjektNummer hinzufügen
		
		~CEnumObjectsByNumber (void);

static CEnumObjectsByNumber *CreateInstance (int iCnt = DEFAULTONRCNT);

	void EveryDelete (void) { m_Objs.EveryDelete(); }

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG,AddRef) (THIS);
	STDMETHOD_(ULONG,Release) (THIS);

// *** IEnumXXX methods ***
	STDMETHOD(Next) (THIS_ ULONG celt, LONG *rgelt, ULONG *pceltFetched);
	STDMETHOD(Skip) (THIS_ ULONG celt);
	STDMETHOD(Reset) (THIS);
	STDMETHOD(Clone) (THIS_ IEnumLONG **ppenm);

// *** IEnumLONG methods ***
	STDMETHOD_(ULONG, Count) (THIS);
};

#endif //_IENUMONR_HXX
