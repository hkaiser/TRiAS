// Implementation der typspezifischen TreeKlasse ------------------------------
// Generiert aus CTTREE.CTT
// File: VIEWTREE.CXX

#include "triaspre.hxx"
#include "triasres.h"

#include <containr.hxx>
#include "viewtree.hxx"	// KlassenDeklarationen

extern short SystemSightFlag;

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Konstruktor der typspezifischen TreeKlasse ---------------------------------
CViewsTree *CViewsTree :: CreateInstance (GeoDB &rDB)
{
CViewsTree *pViews = new CViewsTree(rDB);

	if (NULL == pViews || !pViews -> FInit()) {
		DELETE (pViews);
		return NULL;
	}

return pViews;
}

CViewsTree :: CViewsTree (GeoDB &rDB)
: CTree ((CTTREEGETKEYFCN)FCTTreeGetstring, (CTTREECMPKEYFCN)FCTTreeCmpstring),
  m_rDB (rDB)
{
	n_fTempViewActive = false;
}

// Destruktor, zerlegt alle Elemente des Baumes -------------------------------
CViewsTree :: ~CViewsTree (void)
{
	EveryDelete();
}

// Funktion, die ein neues Element in den Baum einhängt -----------------------
CViewEntry *CViewsTree :: FAddItem (LPCSTR pcView)
{
CViewEntry *pVE = FFindItem (pcView);

	if (NULL != pVE) return pVE;	// bereits im Baum

// ansonsten hinzufügen
CViewEntryCreator Cr (*this);

	return ContCreate (Cr, CViewEntry)(pcView);
}

// Funktion, die ein Element aus dem Baum löscht -----------------------------
bool CViewsTree :: FDeleteItem (LPCSTR pcView)
{
string rKT = pcView;
CTable t(*this);

	if (t.Find ((LPVOID)&rKT)) return t.Delete();

return false;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CViewEntry *CViewsTree :: FFindItem (LPCSTR pcView)
{
string rKT = pcView;
CTable t(*this);

	if (t.Find ((LPVOID)&rKT)) {
	CViewEntryLock l(t);

		TX_ASSERT(NULL != (CViewEntry *)l);
		return (CViewEntry *)l;
	}

return NULL;	// nicht gefunden
}

// Diese Funktion zerlegt ein Element des Baumes ------------------------------
void EXPORTTRIAS CViewsTree :: UserDelete (void *pObj)
{
	TX_ASSERT(NULL != pObj);
	((CViewEntry *)pObj) -> ~CViewEntry();
}

// Funktion, die Pointer auf den Suchschlüssel liefert ------------------------
string *FCTTreeGetstring (CViewEntry *pObj)
{
	TX_ASSERT(NULL != pObj);
	return & ((CViewEntry *)pObj) -> FGetstring();
}

// Funktion, die zwei SuchSchlüssel miteinander vergleicht --------------------
int FCTTreeCmpstring (string *pObj1, string *pObj2)
{
	TX_ASSERT(NULL != pObj1);
	TX_ASSERT(NULL != pObj2);
	return FCmpstring (*pObj1, *pObj2);
}


// Enumeration aller Items in dem Baum ----------------------------------------
bool CViewsTree :: FEnumAllItems (CViewEntryEnumFunc pFcn, void *pEData)
{
CTable t(*this);

	for (t.First(); t.Valid(); /**/) {
	CViewEntryLock l(t);
	bool fNotLast = t.Next();

		TX_ASSERT(NULL != (CViewEntry *)l);
		if (pFcn (*(CViewEntry *)l, fNotLast, pEData) == false)
			return false;
	}

return true;
}

// Enumeration aller Objekte mit einem bestimmten SuchSchlüssel ---------------
bool CViewsTree  :: FEnumItems (const string &rKey, CViewEntryEnumFunc pFcn, void *pEData)
{
CTable t(*this);

	for (t.FindFirst ((LPVOID)&rKey); t.Valid(); /**/) {
	CViewEntryLock l(t);
	bool fNotLast = t.FindNext ((LPVOID)&rKey);

		TX_ASSERT(NULL != (CViewEntry *)l);
		if (pFcn (*(CViewEntry *)l, fNotLast, pEData) == false)
			return false;
	}

return true;
}

bool CViewsTree  :: FReInsert (const string &roldKey, const string &rnewKey)
{
CTable t(*this);

	if (t.Find ((LPVOID)&roldKey)) 
		return t.ReInsert ((LPVOID)&rnewKey, sizeof (rnewKey));

return false;
}

// alle Sichten einlesen ------------------------------------------------------
bool CViewsTree :: FInit (void)
{
CActDB ActDB (DB());
ErrCode EC;
DB_ADDR dba (DB().DBDesc());
ErrInstall EI (WC_NOTFOUND);

// ersten SichtNamen suchen
	EC = (ErrCode)z_keyfirst (&dba, SICHTNAME);
	if (EC != EC_OKAY) {
	// Fehler aufgetreten
		if (EC == WC_NOTFOUND) EC = EC_OKAY; 	// nichts gefunden: OK
		return (EC_OKAY == EC) ? true : false;	// sonstiger Fehler
	}

// für alle weiteren ID's
char cbSichtName[MAXVIEWNAMESIZE+1];
ResString resDefaultView (IDS_DEFAULTVISINFO, 40);
ProFile PF (DB().GetDBName());

	do {
	// ID aus Schlüsseldatei lesen
		EC = (ErrCode)z_keyread (DB().DBDesc(), cbSichtName);
		if (EC != EC_OKAY) break;

		cbSichtName[MAXVIEWNAMESIZE] = '\0';

	// wenn nicht DefaultVisInfo oder evtl. SystemSicht, dann bearbeiten
		if (strcmp (cbSichtName, resDefaultView) &&
		    (SystemSightFlag || strncmp (cbSichtName, "__", 2))) 
		{
		// Sichtnamen merken
		CViewEntry *pVE = NULL;

			OemToAnsi (cbSichtName, cbSichtName);	// Zeichensatzkonvertierung
			if (NULL == (pVE = FAddItem (cbSichtName)))
				return (Count() > 0) ? true : false;	// bis hierhin alles ok

			if (!strcmp (cbSichtName, PF.GetStandardSight())) 
				pVE -> SetDefault();
		}

	// nächsten Schlüssel suchen
	} while (EC_OKAY == (ErrCode)z_keynext (&dba, SICHTNAME));

	if (EC == WC_NOTFOUND) 
		EC = EC_OKAY;           // nichts mehr gefunden: OK

	Optimize();		// Baum optimieren

return (EC_OKAY == EC) ? true : false;
}

// Verwaltung von Standard- und aktueller Ansicht -----------------------------
bool CViewsTree :: isDefaultView (LPCSTR pcView)
{
CViewEntry *pVE = FFindItem (pcView);

	if (NULL != pVE) return pVE -> isDefaultView();

return false;
}

bool CViewsTree :: isActView (LPCSTR pcView)
{
CViewEntry *pVE = FFindItem (pcView);

	if (NULL != pVE) return pVE -> isActView();

return false;
}

bool CViewsTree :: GetDefaultView (LPSTR cbView, int iLen)
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CViewEntryLock l(t);

		TX_ASSERT(NULL != (CViewEntry *)l);

		if (l -> isDefaultView()) {
			strncpy (cbView, (l -> FGetstring()).c_str(), iLen);
			cbView[iLen-1] = '\0';
			return true;
		}
	}
	
	cbView[0] = '\0';	// keine aktuelle Sicht

return false;
}

bool CViewsTree :: GetActView (LPSTR cbView, int iLen)
{
	if (n_fTempViewActive) {
		cbView[0] = '\0';

	ResString rsNoName (IDS_NOVIEWNAME, 30);

		strncpy (&cbView[1], rsNoName, iLen-2);
		cbView[iLen-1] = '\0';
		return true;
	}
		
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CViewEntryLock l(t);

		TX_ASSERT(NULL != (CViewEntry *)l);

		if (l -> isActView()) {
			strncpy (cbView, (l -> FGetstring()).c_str(), iLen);
			cbView[iLen-1] = '\0';
			return true;
		}
	}
	
	cbView[0] = '\0';	// keine aktuelle Sicht

return false;
}

bool CViewsTree :: SetDefaultView (LPCSTR pcView)
{
	TX_ASSERT(NULL != pcView);

CTable t(*this);
bool fFound = false;

	for (t.First(); t.Valid(); t.Next()) {
	CViewEntryLock l(t);

		TX_ASSERT(NULL != (CViewEntry *)l);

		if (l -> FGetstring() == pcView) {
			fFound = true;
			l -> SetDefault (true);
		} else
			l -> SetDefault (false);	// andere rücksetzen
	}

return fFound;
}

bool CViewsTree :: SetActView (LPCSTR pcView, bool fAct)
{
	TX_ASSERT(NULL != pcView);

CTable t(*this);
bool fFound = false;

	for (t.First(); t.Valid(); t.Next()) {
	CViewEntryLock l(t);

		TX_ASSERT(NULL != (CViewEntry *)l);

		if (l -> FGetstring() == pcView) {
			fFound = true;
			l -> SetActive (fAct);
		} else if (fAct)
			l -> SetActive (false);	// andere rücksetzen
	}

	if ('\0' == *pcView)
		n_fTempViewActive = true;		// temp. Sicht ist derzeit aktiv
	else
		n_fTempViewActive = false;

return fFound;
}

bool CViewsTree :: SetInMenu (LPCSTR pcView, bool fInMenu)
{
CViewEntry *pVE = FFindItem (pcView);

	if (NULL != pVE) {
		pVE -> SetInMenu (fInMenu);
		return true;
	}

return false;
}

bool CViewsTree :: isInMenu (LPCSTR pcView)
{
CViewEntry *pVE = FFindItem (pcView);

	if (NULL != pVE) return pVE -> isInMenu();

return false;
}

// nächsten Eintrag aus Baum holen, der nicht im Menu ist ---------------------
bool CViewsTree :: GetNext (string &rstr)
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CViewEntryLock l(t);

		TX_ASSERT(NULL != (CViewEntry *)l);
		if (!l -> isInMenu()) {
			rstr = l -> FGetstring();
			return true;
		}
	}

return false;	// nicht gefunden
}



