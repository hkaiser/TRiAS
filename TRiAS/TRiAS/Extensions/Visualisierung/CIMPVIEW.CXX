// Implementation der typspezifischen TreeKlasse ------------------------------
// Generiert aus TTREE.CTT

#include "visobjp.hxx"

#include "cimpview.hxx"	// KlassenDeklarationen
#include "cimpview.inl"	// Inline-Funktionen

// Konstruktor der typspezifischen TrreKlasse ---------------------------------
CImpViewTree :: CImpViewTree (void)
: CTree ((TTREEGETKEYFCN)FTTreeGetpChar, (TTREECMPKEYFCN)FTTreeCmppChar)
{
	// nothing else to do
}

// Destruktor, zerlegt alle Elemente des Baumes -------------------------------
CImpViewTree :: ~CImpViewTree (void)
{
	EveryDelete();
}

// Funktion, die ein neues Element in den Baum einhängt -----------------------
bool CImpViewTree :: FAddItem (char *pView, short cnCnt)
{
CImpViewCreator Cr (*this);

	return (ContCreate (Cr, CImpView)(pView, cnCnt) != NULL);
}

// Funktion, die ein Element aus dem Baum löscht -----------------------------
bool CImpViewTree :: FDeleteItem (pChar &rKT)
{
CTable t(*this);

	if (t.Find (&rKT)) return t.Delete();

return false;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CImpView *CImpViewTree :: FFindItem (pChar &rKT)
{
CTable t(*this);

	if (t.Find (&rKT)) {
	CImpViewLock l(t);

		if (l) return l;
	}

return NULL;	// nicht gefunden
}

// Diese Funktion zerlegt ein Element des Baumes ------------------------------
void CImpViewTree :: UserDelete (void *pObj)
{
	((CImpView *)pObj) -> ~CImpView();
}

// Funktion, die Pointer auf den Suchschlüssel liefert ------------------------
pChar *FTTreeGetpChar (CImpView *pObj)
{
	return & ((CImpView *)pObj) -> FGetpChar();
}

// Funktion, die zwei SuchSchlüssel miteinander vergleicht --------------------
int FTTreeCmppChar (pChar *pObj1, pChar *pObj2)
{
	return FCmppChar (*pObj1, *pObj2);
}


// Enumeration aller Items in dem Baum ----------------------------------------
bool CImpViewTree :: FEnumAllItems (CImpViewEnumFunc pFcn, void *pEData)
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CImpViewLock l(t);

		if (l && pFcn (*(CImpView *)l, pEData) == false)
			return false;
	}

return true;
}

// Enumeration aller Objekte mit einem bestimmten SuchSchlüssel ---------------
bool CImpViewTree  :: FEnumItems (pChar &rKey, CImpViewEnumFunc pFcn, void *pEData)
{
CTable t(*this);

	for (t.FindFirst (&rKey); t.Valid(); t.FindNext (&rKey)) {
	CImpViewLock l(t);

		if (l && pFcn (*(CImpView *)l, pEData) == false)
			return false;
	}

return true;
}

bool CImpViewTree  :: FReInsert (pChar &roldKey, pChar &rnewKey)
{
CTable t(*this);

	if (t.Find (&roldKey)) 
		return t.ReInsert (&rnewKey, sizeof (rnewKey));

return false;
}

short CImpViewTree :: CountIdents (void)
{
CTable t(*this);
short cnIdents = 0;

	for (t.First(); t.Valid(); t.Next()) {
	CImpViewLock l(t);

		if (!l) continue;
		cnIdents += l -> IdCount();
	}

return cnIdents;
}
