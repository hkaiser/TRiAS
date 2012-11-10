// Implementation der typspezifischen TreeKlasse ------------------------------
// Assoziativer Speicher lONr's <--> UIdent
// Generiert aus CTTREE.CTT

#include "featurep.hxx"

#include <mmsystem.h>

#include "uidobj.hxx"	// KlassenDeklarationen
#include "uidobj.inl"	// Inline-Funktionen

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Konstruktor der typspezifischen TreeKlasse ---------------------------------
// Konstruktor/Destruktor -----------------------------------------------------
CUIdentObjects :: CUIdentObjects (void)
: CTree ((CTTREEGETKEYFCN)FCTTreeGetLPUIDENT, (CTTREECMPKEYFCN)FCTTreeCmpLPUIDENT)
{
	m_pActItem = NULL;
	m_fFilled = false;
	m_dwOpt = 1;
	m_dwInsert = 0;
}

// Destruktor, zerlegt alle Elemente des Baumes -------------------------------
CUIdentObjects :: ~CUIdentObjects (void)
{
	EveryDelete();
	DELETE (m_pActItem);
}

// Funktion, die ein neues Element in den Baum einhängt -----------------------
bool CUIdentObjects :: FAddItem (LPUIDENT pUIDent, ULONG lONr, short iOType)
{
DWORD dwT = timeGetTime();
bool fResult = false;

	{
	CObjUIdentCreator Cr (*this);

		fResult = (Create (Cr, CObjUIdent)(pUIDent, lONr, iOType) != NULL);
	}	// wirklich einfügen
	m_dwInsert = (timeGetTime() - dwT) / 10;

// bei Bedarf optimieren
	if (m_dwInsert > m_dwOpt) {
		dwT = timeGetTime();
		Optimize();
		m_dwOpt = timeGetTime() - dwT;
		if (m_dwOpt == 0) m_dwOpt = 1;
	}
	
return fResult;
}

// Funktion, die ein Element aus dem Baum löscht -----------------------------
bool CUIdentObjects :: FDeleteItem (const LPUIDENT &rKT)
{
CTable t(*this);

	if (t.Find ((LPVOID)&rKT)) return t.Delete();

return false;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CObjUIdent *CUIdentObjects :: FFindItem (const LPUIDENT &rKT)
{
CTable t(*this);

	if (t.Find ((LPVOID)&rKT)) {
	CObjUIdentLock l(t);

		TX_ASSERT(NULL != (CObjUIdent *)l);
		return (CObjUIdent *)l;
	}

return NULL;	// nicht gefunden
}


// Funktion, die Pointer auf erstes gesuchtes Item liefert --------------------
CObjUIdent *CUIdentObjects :: FFindFirstItem (const LPUIDENT &rKT)
{
	if (m_pActItem == NULL) {
		m_pActItem = new CTable (*this);
		if (m_pActItem == NULL) return NULL;
	}
	
	if (m_pActItem -> FindFirst ((LPVOID)&rKT)) {
	CObjUIdentLock l(*m_pActItem);

		TX_ASSERT(NULL != (CObjUIdent *)l);
		return (CObjUIdent *)l;
	}

return NULL;	// nicht gefunden
}


// Funktion, die Pointer auf nächstes gesuchtes Item liefert ------------------
CObjUIdent *CUIdentObjects :: FFindNextItem (const LPUIDENT &rKT)
{
	if (m_pActItem == NULL) return NULL;
	
	if (m_pActItem -> FindNext ((LPVOID)&rKT)) {
	CObjUIdentLock l (*m_pActItem);

		TX_ASSERT(NULL != (CObjUIdent *)l);
		return (CObjUIdent *)l;
	}

return NULL;	// nicht gefunden
}

// Diese Funktion zerlegt ein Element des Baumes ------------------------------
void _XTENSN_EXPORT CUIdentObjects :: UserDelete (void *pObj)
{
	TX_ASSERT(NULL != pObj);
	((CObjUIdent *)pObj) -> ~CObjUIdent();
}

// Funktion, die Pointer auf den Suchschlüssel liefert ------------------------
LPUIDENT *FCTTreeGetLPUIDENT (CObjUIdent *pObj)
{
	TX_ASSERT(NULL != pObj);

	return & ((CObjUIdent *)pObj) -> FGetLPUIDENT();
}

// Funktion, die zwei SuchSchlüssel miteinander vergleicht --------------------
int FCTTreeCmpLPUIDENT (LPUIDENT *pObj1, LPUIDENT *pObj2)
{
	TX_ASSERT(NULL != pObj1);
	TX_ASSERT(NULL != pObj2);

	return FCmpLPUIDENT (*pObj1, *pObj2);
}


Bool CUIdentObjects :: FEnumItems (const LPUIDENT &rKey, CObjUIdentEnumFunc pFcn, void *pEData)
{
CTable t(*this);

	for (t.FindFirst ((LPVOID)&rKey); t.Valid(); t.FindNext ((LPVOID)&rKey)) {
	CObjUIdentLock l(t);

		TX_ASSERT(NULL != (CObjUIdent *)l);

		if (pFcn (*(CObjUIdent *)l, pEData) == FALSE)
			return FALSE;
	}

return TRUE;
}

LONG CUIdentObjects :: GetCount (const LPUIDENT &rKT)
{
CObjUIdent *pObj = FFindItem (rKT);

	if (pObj != NULL) return pObj -> Count();

return 0L;	// nicht gefunden
}

