// Implementation der typspezifischen TreeKlasse ------------------------------
// Generiert aus CTTREE.CTT
// File: VIEWTREE.CXX

#include "triaspre.hxx"
#include "triasres.h"

#include <containr.hxx>
#include "viewtree.hxx"	// KlassenDeklarationen

extern bool g_fSystemSightFlag;

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASView);
DefineSmartInterface(TRiASViews);
DefineSmartInterface(EnumVARIANT);

///////////////////////////////////////////////////////////////////////////////
// Konstruktor der typspezifischen TreeKlasse 

#if defined(_USE_LEGACY_CODE)
CViewsTree *CViewsTree::CreateInstance (GeoDB &rDB)
{
CViewsTree *pViews = new CViewsTree(rDB);

	if (NULL == pViews || !pViews -> FInit()) {
		DELETE_OBJ (pViews);
		return NULL;
	}
	return pViews;
}

CViewsTree::CViewsTree (GeoDB &rDB)
	: CTree ((CTTREEGETKEYFCN)FCTTreeGetstring, (CTTREECMPKEYFCN)FCTTreeCmpstring),
	  m_pDB (&rDB)
{
	n_fTempViewActive = false;
}
#endif // _USE_LEGACY_CODE

CViewsTree *CViewsTree::CreateInstance (ITRiASProject *pIPrj)
{
CViewsTree *pViews = NULL;

	TX_TRY(pViews = new CViewsTree(pIPrj));
	if (NULL == pViews || !pViews -> FInit()) {
		DELETE_OBJ (pViews);
		return NULL;
	}
	return pViews;
}

CViewsTree::CViewsTree (ITRiASProject *pIPrj)
	: CTree ((CTTREEGETKEYFCN)FCTTreeGetstring, (CTTREECMPKEYFCN)FCTTreeCmpstring),
	  m_Prj (pIPrj)
{
	n_fTempViewActive = false;
#if defined(_USE_LEGACY_CODE)
	m_pDB = NULL;
#endif // defined(_USE_LEGACY_CODE)
}

///////////////////////////////////////////////////////////////////////////////
// Destruktor, zerlegt alle Elemente des Baumes 
CViewsTree::~CViewsTree (void)
{
	EveryDelete();
}

// Funktion, die ein neues Element in den Baum einhängt -----------------------
CViewEntry *CViewsTree::FAddItem (LPCSTR pcView)
{
CViewEntry *pVE = FFindItem (pcView);

	if (NULL != pVE) return pVE;	// bereits im Baum

// ansonsten hinzufügen
CViewEntryCreator Cr (*this);

	return ContCreate (Cr, CViewEntry)(pcView);
}

// Funktion, die ein Element aus dem Baum löscht -----------------------------
bool CViewsTree::FDeleteItem (LPCSTR pcView)
{
string rKT = pcView;
CTable t(*this);

	if (t.Find ((LPVOID)&rKT)) return t.Delete();

return false;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CViewEntry *CViewsTree::FFindItem (LPCSTR pcView)
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
void EXPORTTRIAS CViewsTree::UserDelete (void *pObj)
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
bool CViewsTree::FEnumAllItems (CViewEntryEnumFunc pFcn, void *pEData)
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
bool CViewsTree ::FEnumItems (const string &rKey, CViewEntryEnumFunc pFcn, void *pEData)
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

bool CViewsTree ::FReInsert (const string &roldKey, const string &rnewKey)
{
CTable t(*this);

	if (t.Find ((LPVOID)&roldKey)) 
		return t.ReInsert ((LPVOID)&rnewKey, sizeof (rnewKey));

return false;
}

bool CViewsTree::FAddView (LPCSTR pcViewName)
{
	TX_ASSERT(!!m_Prj);		// Projekt muß existieren

WTRiASViews Views;
WTRiASView View;

	if (FAILED(m_Prj -> get_Views (Views.ppi())) ||
		FAILED(Views -> Item (CComVariant(pcViewName), View.ppi())))
	{
		return false;
	}

	if (ShouldAddView (pcViewName)) {
	// Sichtnamen merken
		if (NULL == FAddItem (pcViewName))
			return true;		// bis hierhin alles ok

	VARIANT_BOOL fIsStartView = VARIANT_FALSE;

		THROW_FAILED_HRESULT(View -> get_IsStartView (&fIsStartView));
		if (fIsStartView) 
			SetDefaultView(pcViewName);		// diese Ansicht die die  StartAnsicht

	CComBSTR bstrConnFilter;

		THROW_FAILED_HRESULT(View -> get_ConnectionFilter(&bstrConnFilter));
		if (bstrConnFilter.Length() > 0) {
			USES_CONVERSION;
			SetConnectionFilter(pcViewName, OLE2A(bstrConnFilter));
		}
		return true;
	}
	return false;
}

// Testet, ob die gegebene Ansicht die Startansicht oder eine Systemansicht ist
bool CViewsTree::ShouldAddView (LPCSTR pcView)
{
ResString resDefaultView (IDS_DEFAULTVISINFO, 64);
ResString resTempView (IDS_TEMPVIEWNAME, 64);

	return (strcmp (pcView, resDefaultView) && strcmp (pcView, resTempView) && 
		   (g_fSystemSightFlag || strncmp (pcView, "__", 2)));
}

///////////////////////////////////////////////////////////////////////////////
// alle Sichten einlesen 
bool CViewsTree::FInit (void)
{
#if defined(_USE_LEGACY_CODE)
	if (!m_Prj) {
		TX_ASSERT(NULL != m_pDB);

	GeoDB &rDB = DB();

		if (!rDB.isOpened()) return false;

	CActDB ActDB (rDB);
	ErrCode EC;
	DB_ADDR dba (rDB.DBDesc());
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
	char cbBuffer[MAXVIEWNAMESIZE+1];

		DEX_GetDefaultView(cbBuffer);
		do {
		// ID aus Schlüsseldatei lesen
			EC = (ErrCode)z_keyread (rDB.DBDesc(), cbSichtName);
			if (EC != EC_OKAY) break;

			cbSichtName[MAXVIEWNAMESIZE] = '\0';

		// wenn nicht DefaultVisInfo oder evtl. SystemSicht, dann bearbeiten
			if (ShouldAddView (cbSichtName)) {
			// Sichtnamen merken
			CViewEntry *pVE = NULL;

				OemToAnsi (cbSichtName, cbSichtName);	// Zeichensatzkonvertierung
				if (NULL == (pVE = FAddItem (cbSichtName)))
					return (Count() > 0) ? true : false;	// bis hierhin alles ok

				if (!strcmp (cbSichtName, cbBuffer)) 
					pVE -> SetDefault();
			}

		// nächsten Schlüssel suchen
		} while (EC_OKAY == (ErrCode)z_keynext (&dba, SICHTNAME));

		if (EC == WC_NOTFOUND) 
			EC = EC_OKAY;           // nichts mehr gefunden: OK

		Optimize();		// Baum optimieren
		return (EC_OKAY == EC) ? true : false;
	} else 
#endif // _USE_LEGACY_CODE
	{
		USES_CONVERSION;
		try {
		WTRiASViews Views;

			THROW_FAILED_HRESULT(m_Prj -> get_Views (Views.ppi()));

		WEnumVARIANT Enum;
		CComVariant v;
		bool fHasStartView = false;

			THROW_FAILED_HRESULT(Views -> _NewEnum (Enum.ppu()));
			for (Enum -> Reset(); S_OK == Enum -> Next(1, CLEARED(&v), NULL); /**/)
			{
				if (FAILED(v.ChangeType (VT_UNKNOWN)))
					continue;

			WTRiASView View (V_UNKNOWN (&v));		// throws hr
			CComBSTR bstrName;

				if (SUCCEEDED(View -> get_Name (CLEARED(&bstrName)))) {
				// wenn nicht DefaultVisInfo oder evtl. SystemSicht, dann bearbeiten
				LPCSTR pcViewName = OLE2A(bstrName);

					if (ShouldAddView (pcViewName)) {
					// Sichtnamen merken
					CViewEntry *pVE = NULL;

						if (NULL == (pVE = FAddItem (pcViewName)))
							return (Count() > 0) ? true : false;	// bis hierhin alles ok

					VARIANT_BOOL fIsStartView = VARIANT_FALSE;

						THROW_FAILED_HRESULT(View -> get_IsStartView (&fIsStartView));
						if (fIsStartView) {
							TX_ASSERT(!fHasStartView);	// nur eine darf die StartAnsicht sein

							fHasStartView = true;
							pVE -> SetDefault();		// diese Ansicht die die  StartAnsicht
						}

					CComBSTR bstrConnFilter;

						THROW_FAILED_HRESULT(View -> get_ConnectionFilter(&bstrConnFilter));
						if (bstrConnFilter.Length() > 0) 
							pVE -> SetConnectionFilter(OLE2A(bstrConnFilter));
					}
				}
			}

		} catch (_com_error &e) {
			return _COM_ERROR(e);
		}
	}

	Optimize();		// Baum optimieren
	return true;
}

// Verwaltung von Standard- und aktueller Ansicht -----------------------------
bool CViewsTree::isDefaultView (LPCSTR pcView)
{
CViewEntry *pVE = FFindItem (pcView);

	if (NULL != pVE) return pVE -> isDefaultView();

return false;
}

bool CViewsTree::isActView (LPCSTR pcView)
{
CViewEntry *pVE = FFindItem (pcView);

	if (NULL != pVE) 
		return pVE -> isActView();
	
	return false;
}

bool CViewsTree::GetDefaultView (LPSTR cbView, int iLen)
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CViewEntryLock l(t);

		TX_ASSERT(NULL != (CViewEntry *)l);

		if (l -> isDefaultView()) {
			if (NULL != cbView) {
			int iRealLen = l -> FGetstring().size();
			int iToCopy = min(iLen-1, iRealLen);

				strncpy (cbView, (l -> FGetstring()).c_str(), iToCopy);
				cbView[iToCopy] = '\0';
			}
			return true;
		}
	}
	if (NULL !=  cbView)
		cbView[0] = '\0';	// keine aktuelle Sicht
	return false;
}

bool CViewsTree::GetActView (LPSTR pcView, int iLen)
{
	if (n_fTempViewActive) {
		pcView[0] = '\0';

	ResString rsNoName (IDS_NOVIEWNAME, 30);
	int iRealLen = strlen(rsNoName);
	int iToCopy = min(iLen-1, iRealLen);

		strncpy (&pcView[1], rsNoName, iToCopy);
		pcView[iToCopy] = '\0';
		return true;
	}
		
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CViewEntryLock l(t);

		TX_ASSERT(NULL != (CViewEntry *)l);

		if (l -> isActView()) {
		int iRealLen = l -> FGetstring().size();
		int iToCopy = min(iLen-1, iRealLen);

			strncpy (pcView, (l -> FGetstring()).c_str(), iToCopy);
			pcView[iToCopy] = '\0';
			return true;
		}
	}
	pcView[0] = '\0';	// keine aktuelle Sicht
	return false;
}

bool CViewsTree::HasActView()
{
	if (n_fTempViewActive) 
		return true;	// temporäre Ansicht aktiv

// versuchen aktive Ansicht zu finden
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CViewEntryLock l(t);

		TX_ASSERT(NULL != (CViewEntry *)l);

		if (l -> isActView()) 
			return true;
	}

// keine aktuelle Sicht
	return false;
}

bool CViewsTree::SetDefaultView (LPCSTR pcView)
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

// evtl. auch im angehängten Workspace die Startansicht ändern
	if (!!m_Prj) {
	WTRiASViews Views;
	CComBSTR bstrName (pcView);

		if (SUCCEEDED(m_Prj -> get_Views (Views.ppi())))
			Views -> put_StartViewName (bstrName);
	}
	return fFound;
}

bool CViewsTree::SetActView (LPCSTR pcView, bool fAct)
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

bool CViewsTree::SetInMenu (LPCSTR pcView, bool fInMenu)
{
CViewEntry *pVE = FFindItem (pcView);

	if (NULL != pVE) {
		pVE -> SetInMenu (fInMenu);
		return true;
	}

return false;
}

bool CViewsTree::isInMenu (LPCSTR pcView)
{
CViewEntry *pVE = FFindItem (pcView);

	if (NULL != pVE) return pVE -> isInMenu();

return false;
}

// nächsten Eintrag aus Baum holen, der nicht im Menu ist ---------------------
bool CViewsTree::GetNext (string &rstr)
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

///////////////////////////////////////////////////////////////////////////////
// ConnectionFilter verwalten
bool CViewsTree::SetConnectionFilter (LPCSTR pcView, LPCSTR pcConnFilter)
{
	TX_ASSERT(NULL != pcView);

CTable t(*this);
bool fFound = false;

	for (t.First(); t.Valid(); t.Next()) {
	CViewEntryLock l(t);

		TX_ASSERT(NULL != (CViewEntry *)l);

		if (l -> FGetstring() == pcView) {
			fFound = true;
			l -> SetConnectionFilter (NULL != pcConnFilter ? pcConnFilter : "");
		} 
	}

// evtl. auch angehängtes Workspace nachziehen
	if (!!m_Prj) {
	WTRiASViews Views;
	WTRiASView View;

		if (SUCCEEDED(m_Prj -> get_Views (Views.ppi())) &&
			SUCCEEDED(Views -> Item (CComVariant(pcView), View.ppi())))
		{
			if (NULL != pcConnFilter)
				View -> put_ConnectionFilter(CComBSTR(pcConnFilter));
			else
				View -> put_ConnectionFilter(CComBSTR(""));
		}
	}
	return fFound;
}

bool CViewsTree::GetConnectionFilter (LPCSTR pcView, LPSTR pConnFilter, int iLen)
{
	TX_ASSERT(NULL != pcView);

CTable t(*this);
bool fFound = false;

	for (t.First(); t.Valid(); t.Next()) {
	CViewEntryLock l(t);

		TX_ASSERT(NULL != (CViewEntry *)l);

		if (l -> FGetstring() == pcView) {
		string const &str = l -> GetConnectionFilter();

			if (NULL != pConnFilter) {
			int iToCopy = min((int)str.size(), iLen-1);

				strncpy(pConnFilter, str.c_str(), iToCopy);
				pConnFilter[iToCopy] = '\0';
			}
			fFound = (str.size() > 0) ? true : false;
		} 
	}
	return fFound;
}

