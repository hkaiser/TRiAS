// Datenstrukturen zur Verwaltung der Relationen innerhalb des BNAPARSERS
// File: RELCONT.HPP

#if !defined(_RELCONT_HPP)
#define _RELCONT_HPP

// Baumstruktur, die die Zuordnung von SatzNummer in der QuellDatei mit der
// ObjektNummer in der GeoDB nach dem Einspeichern realisiert
class CONr_SNr {
private:
	long m_lONr;	// ObjektNummer
	long m_lSNr;	// SatzNummer

public:
// Konstruktor/Destruktor
		CONr_SNr (long lONr, long lSNr);
		~CONr_SNr (void) {}

	long &ONr (void) { return m_lONr; }
	long &SNr (void) { return m_lSNr; }

friend int SNrCmp (void *pObj1, void *pObj2);
friend void *SNrGet (void *pObj);
};

class CRelTree : public CTree {
protected:
	void UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
		CRelTree (void);
		~CRelTree (void); 
};
DeclareLock (CRelTree, CONr_SNr);

extern CRelTree *g_pRTree;		// globaler RelationsBaum

// ListenStruktur, in der die Relationen eines Objektes gespeichert werden
class CRelData {
private:
	long m_lONr;		// BezugsObjektNummer
	long m_lRCode;		// RelationsCode
	short m_iRTyp;		// RelationsTyp

public:
// Konstruktor/Destruktor
		CRelData (long lONr, long lRCode, short iRTyp);
		~CRelData (void) {}

	long &ONr (void) { return m_lONr; }
	long &RCode (void) { return m_lRCode; }
	short &RTyp (void) { return m_iRTyp; }
};

class CRelList : public CListContainer {
protected:
	void UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
		CRelList (void);
		~CRelList (void);
};
DeclareLock (CRelList, CRelData);

class CRelListIterator : public CRing {
public:
// Konstruktor/Destruktor
		CRelListIterator (CRelList &RL);
		~CRelListIterator (void) {}

	int RetrieveNext (long &rlONr, long &rlRCode, short &riRTyp);
	int Reset (void) { return First(); }
};

extern CRelList *g_pRList;		// globale RelationsListe;
extern CRelListIterator *g_pRIter;	// globaler Iterator

#endif // _RELCONT_HPP

