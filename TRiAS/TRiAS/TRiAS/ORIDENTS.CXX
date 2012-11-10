// Implementation der typspezifischen TreeKlasse ------------------------------
// Generiert aus CTTREE.CTT
// File: ORIDENTS.CXX

#include "triaspre.hxx"

#include "oridents.hxx"	// KlassenDeklarationen
#include "oridents.inl"	// Inline-Funktionen

// Konstruktor der typspezifischen TrreKlasse ---------------------------------
CORIdents :: CORIdents (void)
: CTree ((CTTREEGETKEYFCN)FCTTreeGetULONG, (CTTREECMPKEYFCN)FCTTreeCmpULONG)
{
	// nothing else to do
}

// Destruktor, zerlegt alle Elemente des Baumes -------------------------------
CORIdents :: ~CORIdents (void)
{
	EveryDelete();
}

// Funktion, die ein neues Element in den Baum einhängt -----------------------
Bool CORIdents :: FAddItem (ULONG &ulKey, short iOType)
{
CORIdentCreator Cr (*this);

	return (ContCreate (Cr, CORIdent)(ulKey, iOType) != NULL);
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CORIdent *CORIdents :: FFindItem (ULONG &rKT)
{
CTable t(*this);

	if (t.Find (&rKT)) {
	CORIdentLock l(t);

		if (l) return l;
	}

return NULL;	// nicht gefunden
}

// Diese Funktion zerlegt ein Element des Baumes ------------------------------
void EXPORTTRIAS CORIdents :: UserDelete (void *pObj)
{
	((CORIdent *)pObj) -> ~CORIdent();
}

// Funktion, die Pointer auf den Suchschlüssel liefert ------------------------
ULONG *FCTTreeGetULONG (CORIdent *pObj)
{
	return & ((CORIdent *)pObj) -> FGetULONG();
}

// Funktion, die zwei SuchSchlüssel miteinander vergleicht --------------------
int FCTTreeCmpULONG (ULONG *pObj1, ULONG *pObj2)
{
	return FCmpULONG (*pObj1, *pObj2);
}


