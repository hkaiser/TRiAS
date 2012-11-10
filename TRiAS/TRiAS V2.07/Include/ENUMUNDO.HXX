// Enumeration aller IUnknown's in UndoListe ----------------------------------
// File: ENUMUNDO.HXX

#if !defined(_ENUMUNDO_HXX)
#define _ENUMUNDO_HXX

// ----------------------------------------------------------------------------
#if !defined(_DEFINED_UNDOCNT)

const int DEFAULTUNDOCNT = 100;		// StandardAnzahl der gespeicherten Undo's

#define _DEFINED_UNDOCNT
#endif // _DEFINED_UNDOCNT

class CUnknownItem {
private:
	LPUNKNOWN m_pIUnk;

public:
		CUnknownItem (LPUNKNOWN pIUnk) { m_pIUnk = pIUnk; m_pIUnk -> AddRef(); }
		~CUnknownItem (void) { m_pIUnk -> Release(); }

	LPUNKNOWN FUnknown (void) { return m_pIUnk; }
};

// ArrayContainer, der die IUnknowns eines Enumerators enthält ----------------
class CUnknownArray : public CArrayContainer {
protected:
	void UserDelete (void *pObj);
	
public:
		CUnknownArray (int lCnt = DEFAULTUNDOCNT);
		~CUnknownArray (void);

	bool DeleteFirst (void);
	bool DeleteLast (void);
};
DeclareLock (CUnknownArray, CUnknownItem);


// BasisKlasse zur Enumeration von IUnknown's ------------------------------------
class CEnumUndoRedo : public IEnumUnknown {
private:
	ULONG		m_cRef;         // Interface reference count.
	LPUNKNOWN 	m_pIUnk;	// controlling unknown
	int 		m_iUndoCnt;	// Anzahl der möglichen Undo's

protected:
	CUnknownArray	m_Unks;		// ArrayContainer der Objekte
	unsigned long	m_ulCur;	// aktuelle Position
	
	bool FInit (void);	// Initialisierungen

public:
	bool AddUnknown (LPUNKNOWN pUnk);	// IUnknown hinzufügen
		
		CEnumUndoRedo (LPUNKNOWN pUnk, int iCnt);
	virtual ~CEnumUndoRedo (void);

static CEnumUndoRedo *CreateInstance (LPUNKNOWN pUnk, int iCnt = DEFAULTUNDOCNT);

	ULONG Count (void) { return m_Unks.Count(); }
	void EveryDelete (void) { m_Unks.EveryDelete(); }
	bool DeleteLast (void) { return m_Unks.DeleteLast(); }

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG,AddRef) (THIS);
	STDMETHOD_(ULONG,Release) (THIS);

// *** IEnumUnknown methods ***
	STDMETHOD(Next) (THIS_ ULONG celt, LPUNKNOWN *rgelt, ULONG *pceltFetched);
	STDMETHOD(Skip) (THIS_ ULONG celt);
	STDMETHOD(Reset) (THIS);
	STDMETHOD(Clone) (THIS_ IEnumUnknown **ppenm);

friend class CManageUndoRedo;
};

#endif //_ENUMUNDO_HXX
