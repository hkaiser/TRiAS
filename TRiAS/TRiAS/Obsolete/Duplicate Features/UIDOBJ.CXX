// Implementation der typspezifischen TreeKlasse ------------------------------
// Assoziativer Speicher lONr's <--> UIdent
// Generiert aus CTTREE.CTT

#include "featurep.hxx"

#include <mmsystem.h>

#include "uidobj.hxx"	// KlassenDeklarationen
#include "uidobj.inl"	// Inline-Funktionen

// Konstruktor der typspezifischen TreeKlasse ---------------------------------
typedef struct tagENUMDOCDATA {
	CUIdentObjects *m_pUIObjs;
	CUIdentObjects *m_pDupObjs;
	ULONG m_lMCode;
	char *m_pMWert;
} ENUMDOCDATA;

extern "C" bool PASCAL _XTENSN_EXPORT GetObjectsFromIdentDoc (
				long lONr, DWORD dwOTyp, void *pData)
{
ENUMDOCDATA *pEOD = (ENUMDOCDATA *)pData;
	
// Merkmal abfragen
	if (!ReadTextMerkmal (TT_Objekt, lONr, pEOD -> m_lMCode, pEOD -> m_pMWert, _MAX_PATH))
		return true;	//  hat keine UIdent, weitermachen

// wenn dieser UIdent bereits im Baum ist, dann beide Objekte speichern
CObjUIdent *pObj = pEOD -> m_pUIObjs -> FFindItem (pEOD -> m_pMWert);

	if (pObj != NULL) {
	// UIdent ist nicht zum ersten mal da
		if (!pEOD -> m_pDupObjs -> FFindItem (pEOD -> m_pMWert)) 
		// gefundenes Objekt in doppelte Liste einhängen, da erstes doppeltes
			pEOD -> m_pDupObjs -> FAddItem (pEOD -> m_pMWert, pObj -> ObjNr(), pObj -> OTyp());

	// jetzt noch neues Objekt in doppelte Liste reinhängen
		return pEOD -> m_pDupObjs -> FAddItem (pEOD -> m_pMWert, lONr, short(dwOTyp));
	}

// lediglich in Baum reinhängen
return pEOD -> m_pUIObjs -> FAddItem (pEOD -> m_pMWert, lONr, short(dwOTyp));
}

extern "C" bool PASCAL _XTENSN_EXPORT GetIdentsFromDoc (
				long lIdent, bool, void *pData)
{
ENUMLONGKEYEX ELK;

	ELK.eKey = lIdent;
	ELK.eFcn = (ENUMLONGKEYEXPROC)GetObjectsFromIdentDoc;
	ELK.ePtr = pData;
	ELK.eData = (OTPunkt|OTLinie|OTFlaeche|OTText);
	
return DEX_EnumIdentObjectsEx (ELK);
}


// Konstruktor/Destruktor -----------------------------------------------------
CUIdentObjects :: CUIdentObjects (void)
: CTree ((CTTREEGETKEYFCN)FCTTreeGetLPUIDENT, (CTTREECMPKEYFCN)FCTTreeCmpLPUIDENT)
{
	m_pActItem = NULL;
	m_fFilled = false;
	m_dwOpt = 1;
	m_dwInsert = 0;
}

// dopelte Merkmale für alle Objekte suchen -----------------------------------
bool FillTrees (ULONG lMCode, CUIdentObjects &rAllObjs, CUIdentObjects &rDupObjs)
{
// Bäume füllen
ENUMDOCDATA EDD;

	EDD.m_lMCode = lMCode;
	EDD.m_pUIObjs = &rAllObjs;
	EDD.m_pDupObjs = &rDupObjs;
	EDD.m_pMWert = new char [_MAX_PATH];

	if (EDD.m_pMWert != NULL) {
	ENUMNOKEY ENK;
	
		ENK.eFcn = (ENUMNOKEYPROC)GetIdentsFromDoc;	// zu rufende Funktion
		ENK.ePtr = &EDD;				// durchzureichende Daten
		DEX_EnumIdents (ENK);			// mit Idents füllen
		DELETE (EDD.m_pMWert);
		return true;
	}

return false;
}

// doppelte Merkmale für eine Ident/OTyp-Kombination suchen -------------------
bool FillTrees (long lIdent, short iOTyp, long lMCode, 
		CUIdentObjects &rAllObjs, CUIdentObjects &rDupObjs)
{
// Bäume füllen
ENUMDOCDATA EDD;

	EDD.m_lMCode = lMCode;
	EDD.m_pUIObjs = &rAllObjs;
	EDD.m_pDupObjs = &rDupObjs;
	EDD.m_pMWert = new char [_MAX_PATH];

ENUMLONGKEYEX ELK;

	ELK.eKey = lIdent;
	ELK.eFcn = (ENUMLONGKEYEXPROC)GetObjectsFromIdentDoc;
	ELK.ePtr = &EDD;
	ELK.eData = (DWORD)iOTyp;
	
return DEX_EnumIdentObjectsEx (ELK);
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
bool CUIdentObjects :: FDeleteItem (LPUIDENT &rKT)
{
CTable t(*this);

	if (t.Find (&rKT)) return t.Delete();

return false;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CObjUIdent *CUIdentObjects :: FFindItem (LPUIDENT &rKT)
{
CTable t(*this);

	if (t.Find (&rKT)) {
	CObjUIdentLock l(t);

		if (l) return l;
	}

return NULL;	// nicht gefunden
}


// Funktion, die Pointer auf erstes gesuchtes Item liefert --------------------
CObjUIdent *CUIdentObjects :: FFindFirstItem (LPUIDENT &rKT)
{
	if (m_pActItem == NULL) {
		m_pActItem = new CTable (*this);
		if (m_pActItem == NULL) return NULL;
	}
	
	if (m_pActItem -> FindFirst (&rKT)) {
	CObjUIdentLock l(*m_pActItem);

		if (l) return l;
	}

return NULL;	// nicht gefunden
}


// Funktion, die Pointer auf nächstes gesuchtes Item liefert ------------------
CObjUIdent *CUIdentObjects :: FFindNextItem (LPUIDENT &rKT)
{
	if (m_pActItem == NULL) return NULL;
	
	if (m_pActItem -> FindNext (&rKT)) {
	CObjUIdentLock l (*m_pActItem);

		if (l) return l;
	}

return NULL;	// nicht gefunden
}

// Diese Funktion zerlegt ein Element des Baumes ------------------------------
void _XTENSN_EXPORT CUIdentObjects :: UserDelete (void *pObj)
{
	((CObjUIdent *)pObj) -> ~CObjUIdent();
}

// Funktion, die Pointer auf den Suchschlüssel liefert ------------------------
LPUIDENT *FCTTreeGetLPUIDENT (CObjUIdent *pObj)
{
	return & ((CObjUIdent *)pObj) -> FGetLPUIDENT();
}

// Funktion, die zwei SuchSchlüssel miteinander vergleicht --------------------
int FCTTreeCmpLPUIDENT (LPUIDENT *pObj1, LPUIDENT *pObj2)
{
	return FCmpLPUIDENT (*pObj1, *pObj2);
}


