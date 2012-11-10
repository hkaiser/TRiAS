// Implementation der typspezifischen TreeKlasse ------------------------------
// Generiert aus CTTREE.CTT
// File: MSTRSTR.CXX

#include "bscriptp.hxx"

#include <mmsystem.h>

#include "mstrstr.hxx"	// KlassenDeklarationen
#include "mstrstr.inl"	// Inline-Funktionen


// Member der StringStringKlasse ----------------------------------------------
DWORD CStringString :: AddRef (void)
{
	return ++m_dwRefCnt;
}

DWORD CStringString :: Release (void)
{
	if (--m_dwRefCnt <= 0) {
		delete this;
		return 0L;
	}
	
return m_dwRefCnt;
}

// Konstruktor der typspezifischen TrreKlasse ---------------------------------
CMapStringString :: CMapStringString (void)
: CTree ((CTTREEGETKEYFCN)FCTTreeGetLPCTSTR, (CTTREECMPKEYFCN)FCTTreeCmpLPCTSTR,
	 CONTFLAG(CFNoSpecial|CFSyncThreads))
{
	m_dwRefCnt = 0;
	m_dwOpt = 1;
	m_dwInsert = 0;
}

CMapStringString *CMapStringString :: CreateInstance (void)
{
CMapStringString *pMap = new CMapStringString();

	if (pMap) pMap -> AddRef();
	
return pMap;
}

// Destruktor, zerlegt alle Elemente des Baumes -------------------------------
CMapStringString :: ~CMapStringString (void)
{
	EveryDelete();
}

DWORD CMapStringString :: AddRef (void)
{
	return ++m_dwRefCnt;
}

DWORD CMapStringString :: Release (void)
{
	if (--m_dwRefCnt <= 0) {
		delete this;
		return 0L;
	}
	
return m_dwRefCnt;
}

// Funktion, die ein neues Element in den Baum einhängt -----------------------
bool CMapStringString :: FAddItem (LPCTSTR pKey, LPCTSTR pData)
{
DWORD dwT = GetCurrentTime();
bool fResult = false;

	{
	CStringStringCreator Cr (*this);

		fResult = (ContCreate (Cr, CStringString)(pKey, pData) != NULL);
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

bool CMapStringString :: FAddItem (CStringString *pItem)
{
DWORD dwT = GetCurrentTime();
bool fResult = false;

	{
	CStringStringCreator Cr (*this);

		fResult = Cr.InsertPtr (pItem) != NULL;
	}	// wirklich einfügen
	m_dwInsert = (GetCurrentTime() - dwT) / 10;

	if (fResult) pItem -> AddRef();		// festhalten

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
bool CMapStringString :: FDeleteItem (LPCTSTR rKT)
{
CTable t(*this);

	if (t.Find ((LPVOID)rKT)) return t.Delete();

return false;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CStringString *CMapStringString :: FFindItem (LPCTSTR rKT)
{
CTable t(*this);

	if (t.Find ((LPVOID)rKT)) {
	CStringStringLock l(t);

		if (l) return l;
	}

return NULL;	// nicht gefunden
}

// Diese Funktion zerlegt ein Element des Baumes ------------------------------
void _XTENSN_EXPORT CMapStringString :: UserDelete (void *pObj)
{
	((CStringString *)pObj) -> Release();
}

// Funktion, die Pointer auf den Suchschlüssel liefert ------------------------
LPCTSTR FCTTreeGetLPCTSTR (CStringString *pObj)
{
	return ((CStringString *)pObj) -> FGetLPCTSTR();
}

// Funktion, die zwei SuchSchlüssel miteinander vergleicht --------------------
int FCTTreeCmpLPCTSTR (LPCTSTR pObj1, LPCTSTR pObj2)
{
	return FCmpLPCTSTR (pObj1, pObj2);
}

