// Implementation der typspezifischen TreeKlasse ------------------------------
// Generiert aus TTREE.CTT

#include "visobjp.hxx"

#include <viserror.hxx>		// KlassenDeklarationen

// Konstruktor der typspezifischen TrreKlasse ---------------------------------
CIgnoreVisErrorTree :: CIgnoreVisErrorTree (void)
: CTree ((TTREEGETKEYFCN)FTTreeGetVisError, (TTREECMPKEYFCN)FTTreeCmpVisError)
{
	// nothing else to do
}

// Destruktor, zerlegt alle Elemente des Baumes -------------------------------
CIgnoreVisErrorTree :: ~CIgnoreVisErrorTree (void)
{
	EveryDelete();
}

// Funktion, die ein neues Element in den Baum einhängt -----------------------
BOOL CIgnoreVisErrorTree :: FAddItem (long lIdent, short iVTyp, char *pView)
{
CVisErrorItemCreator Cr (*this);

	return (ContCreate (Cr, CVisErrorItem)(lIdent, iVTyp, pView) != NULL);
}

// Funktion, die ein Element aus dem Baum löscht -----------------------------
BOOL CIgnoreVisErrorTree :: FDeleteItem (CVisError &rKT)
{
CTable t(*this);

	if (t.Find (&rKT)) return t.Delete();

return false;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CVisErrorItem *CIgnoreVisErrorTree :: FFindItem (long lIdent, short iVTyp, char *pView)
{
CTable t(*this);
CVisError VE (lIdent, iVTyp, pView);

	if (t.Find (&VE)) {
	CVisErrorItemLock l(t);

		if (l) return l;
	}

return NULL;	// nicht gefunden
}

// Diese Funktion zerlegt ein Element des Baumes ------------------------------
void CIgnoreVisErrorTree :: UserDelete (void *pObj)
{
	((CVisErrorItem *)pObj) -> ~CVisErrorItem();
}

// Funktion, die Pointer auf den Suchschlüssel liefert ------------------------
CVisError *FTTreeGetVisError (CVisErrorItem *pObj)
{
	return & ((CVisErrorItem *)pObj) -> FGetVisError();
}

// Funktion, die zwei SuchSchlüssel miteinander vergleicht --------------------
int FTTreeCmpVisError (CVisError *pObj1, CVisError *pObj2)
{
	return FCmpVisError (*pObj1, *pObj2);
}


// Enumeration aller Items in dem Baum ----------------------------------------
BOOL CIgnoreVisErrorTree :: FEnumAllItems (VisErrorItemEnumFunc pFcn, void *pEData)
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CVisErrorItemLock l(t);

		if (l && pFcn (*(CVisErrorItem *)l, pEData) == false)
			return false;
	}

return true;
}

// Enumeration aller Objekte mit einem bestimmten SuchSchlüssel ---------------
BOOL CIgnoreVisErrorTree  :: FEnumItems (CVisError &rKey, VisErrorItemEnumFunc pFcn, void *pEData)
{
CTable t(*this);

	for (t.FindFirst (&rKey); t.Valid(); t.FindNext (&rKey)) {
	CVisErrorItemLock l(t);

		if (l && pFcn (*(CVisErrorItem *)l, pEData) == false)
			return false;
	}

return true;
}

BOOL CIgnoreVisErrorTree  :: FReInsert (CVisError &roldKey, CVisError &rnewKey)
{
CTable t(*this);

	if (t.Find (&roldKey)) 
		return t.ReInsert (&rnewKey, sizeof (rnewKey));

return false;
}

