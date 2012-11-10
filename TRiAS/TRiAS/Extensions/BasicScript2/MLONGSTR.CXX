// Implementation der typspezifischen TreeKlasse ------------------------------
// Generiert aus CTTREE.CTT

#include "bscriptp.hxx"

#include <mmsystem.h>

#include "mlongstr.hxx"	// KlassenDeklarationen
#include "mlongstr.inl"	// Inline-Funktionen

// Konstruktor der typspezifischen TrreKlasse ---------------------------------
CMapLongString :: CMapLongString (void)
: CTree ((CTTREEGETKEYFCN)FCTTreeGetLONG, (CTTREECMPKEYFCN)FCTTreeCmpLONG)
{
	m_dwRefCnt = 0;
	m_dwOpt = 1;
	m_dwInsert = 0;
}

CMapLongString *CMapLongString :: CreateInstance (void)
{
CMapLongString *pMap = new CMapLongString();

	if (pMap) pMap -> AddRef();
	
return pMap;
}

DWORD CMapLongString :: AddRef (void)
{
	return ++m_dwRefCnt;
}

DWORD CMapLongString :: Release (void)
{
	if (--m_dwRefCnt <= 0) {
		delete this;
		return 0L;
	}
	
return m_dwRefCnt;
}

// Destruktor, zerlegt alle Elemente des Baumes -------------------------------
CMapLongString :: ~CMapLongString (void)
{
	EveryDelete();
}

// Funktion, die ein neues Element in den Baum einhängt -----------------------
bool CMapLongString :: FAddItem (LONG lKey, LPCTSTR pData)
{
DWORD dwT = GetCurrentTime();
bool fResult = false;

	{
	CLongStringCreator Cr (*this);

		fResult = (ContCreate (Cr, CLongString)(lKey, pData) != NULL);
	}	// wirklich einfügen
	m_dwInsert = (GetCurrentTime() - dwT) / 10;

// bei Bedarf optimieren
	if (m_dwInsert > m_dwOpt) {
		dwT = GetCurrentTime();
		Optimize();
		m_dwOpt = GetCurrentTime() - dwT;
		if (m_dwOpt == 0) m_dwOpt = 1;
	}
	
return fResult;
}

// Funktion, die ein Element aus dem Baum löscht -----------------------------
bool CMapLongString :: FDeleteItem (LONG &rKT)
{
CTable t(*this);

	if (t.Find (&rKT)) return t.Delete();

return FALSE;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CLongString *CMapLongString :: FFindItem (LONG &rKT)
{
CTable t(*this);

	if (t.Find (&rKT)) {
	CLongStringLock l(t);

		if (l) return l;
	}

return NULL;	// nicht gefunden
}

// Diese Funktion zerlegt ein Element des Baumes ------------------------------
void _XTENSN_EXPORT CMapLongString :: UserDelete (void *pObj)
{
	((CLongString *)pObj) -> ~CLongString();
}

// Funktion, die Pointer auf den Suchschlüssel liefert ------------------------
LONG *FCTTreeGetLONG (CLongString *pObj)
{
	return & ((CLongString *)pObj) -> FGetLONG();
}

// Funktion, die zwei SuchSchlüssel miteinander vergleicht --------------------
int FCTTreeCmpLONG (LONG *pObj1, LONG *pObj2)
{
	return FCmpLONG (*pObj1, *pObj2);
}


