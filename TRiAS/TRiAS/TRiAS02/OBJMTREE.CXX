// Implementation der typspezifischen TreeKlasse ------------------------------
// Generiert aus CTTREE.CTT

#include "trias02p.hxx"

#include "objmtree.hxx"	// KlassenDeklarationen
#include "objmtree.inl"	// Inline-Funktionen

// Konstruktor der typspezifischen TrreKlasse ---------------------------------
CFeatureTree :: CFeatureTree (void)
: CTree ((CTTREEGETKEYFCN)FCTTreeGetMCODE, (CTTREECMPKEYFCN)FCTTreeCmpMCODE)
{
	// nothing else to do
}

// Destruktor, zerlegt alle Elemente des Baumes -------------------------------
CFeatureTree :: ~CFeatureTree (void)
{
	EveryDelete();
}

// Funktion, die ein neues Element in den Baum einhängt -----------------------
Bool CFeatureTree :: FAddItem (long lMCode, char *pMWert)
{
CFeatureCreator Cr (*this);

	return (ContCreate (Cr, CFeature)(lMCode, pMWert) != NULL);
}

// Funktion, die ein Element aus dem Baum löscht -----------------------------
Bool CFeatureTree :: FDeleteItem (MCODE &rKT)
{
CTable t(*this);

	if (t.Find (&rKT)) return t.Delete();

return FALSE;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CFeature *CFeatureTree :: FFindItem (MCODE &rKT)
{
CTable t(*this);

	if (t.Find (&rKT)) {
	CFeatureLock l(t);

		if (l) return l;
	}

return NULL;	// nicht gefunden
}

// Diese Funktion zerlegt ein Element des Baumes ------------------------------
void EXPORT02 CFeatureTree :: UserDelete (void *pObj)
{
	((CFeature *)pObj) -> ~CFeature();
}

// Funktion, die Pointer auf den Suchschlüssel liefert ------------------------
MCODE *FCTTreeGetMCODE (CFeature *pObj)
{
	return & ((CFeature *)pObj) -> FGetMCODE();
}

// Funktion, die zwei SuchSchlüssel miteinander vergleicht --------------------
int FCTTreeCmpMCODE (MCODE *pObj1, MCODE *pObj2)
{
	return FCmpMCODE (*pObj1, *pObj2);
}


// Enumeration aller Items in dem Baum ----------------------------------------
Bool CFeatureTree :: FEnumAllItems (CFeatureEnumFunc pFcn, void *pEData)
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CFeatureLock l(t);

		if (l && pFcn (*(CFeature *)l, pEData) == FALSE)
			return FALSE;
	}

return TRUE;
}

// Enumeration aller Objekte mit einem bestimmten SuchSchlüssel ---------------
Bool CFeatureTree  :: FEnumItems (MCODE &rKey, CFeatureEnumFunc pFcn, void *pEData)
{
CTable t(*this);

	for (t.FindFirst (&rKey); t.Valid(); t.FindNext (&rKey)) {
	CFeatureLock l(t);

		if (l && pFcn (*(CFeature *)l, pEData) == FALSE)
			return FALSE;
	}

return TRUE;
}

Bool CFeatureTree  :: FReInsert (MCODE &roldKey, MCODE &rnewKey)
{
CTable t(*this);

	if (t.Find (&roldKey)) 
		return t.ReInsert (&rnewKey, sizeof (rnewKey));

return FALSE;
}

