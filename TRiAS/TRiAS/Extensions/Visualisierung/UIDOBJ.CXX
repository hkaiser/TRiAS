// Implementation der typspezifischen TreeKlasse ------------------------------
// Assoziativer Speicher lONr's <--> UIdent
// Generiert aus CTTREE.CTT

#include "visobjp.hxx"

#include <containr.hxx>
#include <strdupx.hxx>

#include "uidobj.hxx"	// KlassenDeklarationen
#include "uidobj.inl"	// Inline-Funktionen

/////////////////////////////////////////////////////////////////////////////
// evtl. BezugsText finden
extern "C" 
BOOL PASCAL _XTENSN_EXPORT DependendObject (long lONr, long, short iRTyp, void *pData)
{
	if (iRTyp == RTBegleitO) {
		*(long *)pData = lONr;		// BegleitText gefunden
		return false;				// Enumeration abbrechen
	}
	return true;	// weitermachen
}

long AssocTextObject (long lONr)
{
ENUMRELATIONOBJS ERO;
long lTONr = -1L;

	INITSTRUCT (ERO, ENUMRELATIONOBJS);
	ERO.lONr = lONr;	// TextObjekt
	ERO.lRCode = -1L;	// kein RCode
	ERO.iRTyp = RTBegleitO;	// es wird Begleittext gesucht
	ERO.eFcn = (ENUMRELOBJPROC)DependendObject;
	ERO.pData = &lTONr;
	DEX_EnumRelationObjects (ERO);
	return lTONr;
}

// Konstruktor der typspezifischen TrreKlasse ---------------------------------
typedef struct tagENUMDOCDATA {
	CUIdentObjects *m_pUIObjs;
	ULONG m_lMCode;
	char *m_pMWert;
} ENUMDOCDATA;

extern "C" 
BOOL PASCAL _XTENSN_EXPORT GetObjectsFromIdentDoc (long lONr, DWORD dwOTyp, void *pData)
{
ENUMDOCDATA *pEOD = (ENUMDOCDATA *)pData;
	
// Merkmal abfragen
	if (!ReadTextMerkmal (TT_Objekt, lONr, pEOD -> m_lMCode, pEOD -> m_pMWert))
		return TRUE;	//  hat keine UIdent, weitermachen

// in Baum reinhängen
	pEOD -> m_pUIObjs -> FAddItem (pEOD -> m_pMWert, lONr, short(dwOTyp));

// zusätzlich feststellen, ob BezugsText da ist
	if (OTText == dwOTyp)
		return TRUE;		// Texte nicht mehr behandeln

long lTONr = AssocTextObject (lONr);

	if (-1 == lTONr)
		return TRUE;				// kein Begleittext vorhanden

// auch in Baum reinhängen
string str ('$');

	str += pEOD -> m_pMWert;
	return pEOD -> m_pUIObjs -> FAddItem ((char *)str.c_str(), lTONr, short(OTText));
}

extern "C" 
BOOL PASCAL _XTENSN_EXPORT GetIdentsFromDoc (long lIdent, BOOL, void *pData)
{
	if (DEX_GetROModeIdent (lIdent))
		return TRUE;	// Tabelle ist schreibgeschützt (kann keine Attribute schreiben)

ENUMLONGKEYEX ELK;

	ELK.eKey = lIdent;
	ELK.eFcn = (ENUMLONGKEYEXPROC)GetObjectsFromIdentDoc;
	ELK.ePtr = pData;
	ELK.eData = (OTPunkt|OTLinie|OTFlaeche|OTText);
	return DEX_EnumIdentObjectsEx (ELK);
}


// Konstruktor/Destruktor -----------------------------------------------------
CUIdentObjects :: CUIdentObjects (void)
: COptTree ((CTTREEGETKEYFCN)FCTTreeGetLPUIDENT, (CTTREECMPKEYFCN)FCTTreeCmpLPUIDENT)
{
	m_pActItem = NULL;
	m_fFilled = false;
}


bool FillTree (HPROJECT hPr, CUIdentObjects *pThis)
{
	if (DEX_GetROModeEx(hPr))
		return true;		// Datenquelle schreibgeschützt

// Baum füllen
ENUMDOCDATA EDD;
LONG lMCode = DEX_GetUniqueIdentMCodeEx (hPr);

	if (0 != lMCode) {
		EDD.m_lMCode = lMCode;
		EDD.m_pUIObjs = pThis;
		EDD.m_pMWert = new char [_MAX_PATH];
		if (EDD.m_pMWert != NULL) {
		ENUMNOKEY ENK;
		
			ENK.eFcn = (ENUMNOKEYPROC)GetIdentsFromDoc;	// zu rufende Funktion
			ENK.ePtr = &EDD;							// durchzureichende Daten
			DEX_EnumClasses (hPr, ENK);					// mit Idents füllen
			DELETE_OBJ (EDD.m_pMWert);
		}
	}
	return true;		// immer weiter machen
}

extern "C"
BOOL CALLBACK EnumDataSources (HPROJECT hPr, BOOL, void *pData)
{
	return FillTree (hPr, (CUIdentObjects *)pData);
}

// sämtliche Datenquellen durchgehen
bool CUIdentObjects::FillTree (ULONG /*lMCode*/)
{
ENUMNOKEYLONG ENK;

	m_fFilled = true;

	ENK.eFcn = (ENUMNOKEYLONGPROC)EnumDataSources;
	ENK.ePtr = this;
	return DEX_EnumDataSourceHandles (ENK);
}

// Destruktor, zerlegt alle Elemente des Baumes -------------------------------
CUIdentObjects :: ~CUIdentObjects (void)
{
	EveryDelete();
	DELETE_OBJ (m_pActItem);
}

// Funktion, die ein neues Element in den Baum einhängt -----------------------
bool CUIdentObjects :: FAddItem (LPUIDENT pUIDent, ULONG lONr, short iOType)
{
CObjUIdentCreator Cr (*this);

	return (ContCreate (Cr, CObjUIdent)(pUIDent, lONr, iOType) != NULL);
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


