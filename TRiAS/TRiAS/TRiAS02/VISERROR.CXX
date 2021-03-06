// Implementation der typspezifischen TreeKlasse ------------------------------
// Generiert aus TTREE.CTT

#include "trias02p.hxx"

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

// Funktion, die ein neues Element in den Baum einh�ngt -----------------------
Bool CIgnoreVisErrorTree :: FAddItem (long lIdent, short iVTyp, char *pView)
{
CVisErrorItemCreator Cr (*this);

	return (ContCreate (Cr, CVisErrorItem)(lIdent, iVTyp, pView) != NULL);
}

// Funktion, die ein Element aus dem Baum l�scht -----------------------------
Bool CIgnoreVisErrorTree :: FDeleteItem (CVisError &rKT)
{
CTable t(*this);

	if (t.Find (&rKT)) return t.Delete();

return FALSE;
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
void EXPORT02 CIgnoreVisErrorTree :: UserDelete (void *pObj)
{
	((CVisErrorItem *)pObj) -> /*CVisErrorItem ::*/ ~CVisErrorItem();
}

// Funktion, die Pointer auf den Suchschl�ssel liefert ------------------------
CVisError *FTTreeGetVisError (CVisErrorItem *pObj)
{
	return & ((CVisErrorItem *)pObj) -> FGetVisError();
}

// Funktion, die zwei SuchSchl�ssel miteinander vergleicht --------------------
int FTTreeCmpVisError (CVisError *pObj1, CVisError *pObj2)
{
	return FCmpVisError (*pObj1, *pObj2);
}


// Enumeration aller Items in dem Baum ----------------------------------------
Bool CIgnoreVisErrorTree :: FEnumAllItems (VisErrorItemEnumFunc pFcn, void *pEData)
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CVisErrorItemLock l(t);

		if (l && pFcn (*(CVisErrorItem *)l, pEData) == FALSE)
			return FALSE;
	}

return TRUE;
}

// Enumeration aller Objekte mit einem bestimmten SuchSchl�ssel ---------------
Bool CIgnoreVisErrorTree  :: FEnumItems (CVisError &rKey, VisErrorItemEnumFunc pFcn, void *pEData)
{
CTable t(*this);

	for (t.FindFirst (&rKey); t.Valid(); t.FindNext (&rKey)) {
	CVisErrorItemLock l(t);

		if (l && pFcn (*(CVisErrorItem *)l, pEData) == FALSE)
			return FALSE;
	}

return TRUE;
}

Bool CIgnoreVisErrorTree  :: FReInsert (CVisError &roldKey, CVisError &rnewKey)
{
CTable t(*this);

	if (t.Find (&roldKey)) 
		return t.ReInsert (&rnewKey, sizeof (rnewKey));

return FALSE;
}


// HilfsFunktion f�r die Konstruktion von CVisError ---------------------------
//void CVisError :: SetViewName (char *pView)
//{
//	if (pView == NULL) {
//		m_pView = NULL;
//		return;
//	}
//	m_pView = new char [strlen (pView) +1];
//	if (m_pView) strcpy (m_pView, pView);
//}

///////////////////////////////////////////////////////////////////////////////
// VisInfo related stuff

// Helper f�r VisInfo

VisInfo *MakeNewVI (VisType iVTyp) 
{
VisInfo *pNewVI = NULL;

	switch (iVTyp) {
	case VT_Punkt:
		pNewVI = new CDefaultPVisInfo();
		break;

	case VT_Linie:
		pNewVI = new CDefaultLVisInfo();
		break;

	case VT_Flaeche:
		pNewVI = new CDefaultFVisInfo();
		break;

	case VT_Text:
		pNewVI = new CDefaultTVisInfo();
		break;

	case VT_Default:
		pNewVI = new CDefaultVisInfo();
		break;
	}
	return pNewVI;
}


short MakeCompleteNewVisInfo (VisInfo **ppVI, short iBits, BOOL fSpecial)
{
// wenn alle gebraucht werden, aber keiner da ist, dann EINEN DefaultSatz 
// generieren
short fRet = 0;

	if (iBits == TPAll && fSpecial &&
	    ppVI[0] == NULL && ppVI[1] == NULL &&
	    ppVI[2] == NULL && ppVI[3] == NULL)
	{
		ppVI[0] = MakeNewVI (VT_Default);
		return TPAll;		// ACHTUNG: SonderFall
	} 
	if (ppVI[0] == NULL && iBits & TPPunkt) {
		ppVI[0] = MakeNewVI (VT_Punkt);
		fRet |= TPPunkt;
	}
	if (ppVI[1] == NULL && iBits & TPLinie) {
		ppVI[1] = MakeNewVI (VT_Linie);
		fRet |= TPLinie;
	}
	if (ppVI[2] == NULL && iBits & TPFlaeche) {
		ppVI[2] = MakeNewVI (VT_Flaeche);
		fRet |= TPFlaeche;
	}
	if (ppVI[3] == NULL && iBits & TPText) {
		ppVI[3] = MakeNewVI (VT_Text);
		fRet |= TPText;
	}
	return fRet;	// normaler Verlauf
}

