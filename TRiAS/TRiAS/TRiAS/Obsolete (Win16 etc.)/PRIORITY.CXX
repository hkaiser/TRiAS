// Dialogfenster zur Einstellung der Prioritaeten -----------------------------
// File: PRIORITY.CXX

#include "triaspre.hxx"

#include "priority.h"
#include "priority.hxx"

extern ExtDirisWindow *CurrActDirisW;

extern char cVisType (VisType iVTyp);
extern VisType FGetVisTyp (char *);

// Konstruktor für lokalen Prioritätsbaum, der IdentBeschreibungen enthält ----
PriorityTree :: PriorityTree (void)
	      : CTree (EntryIdent, ULongCmp) 
{
	// nothing else to do 
}

PriorityTree :: ~PriorityTree (void) 
{
	EveryDelete ();
}

void *EntryIdent (void *pObj) 
{
	return & (((PriorityEntry *)pObj) -> Ident());
}

void EXPORTTRIAS PriorityTree :: UserDelete (void *pObj) 
{
	((PriorityEntry *)pObj) -> /*PriorityEntry ::*/ ~PriorityEntry ();
}

// Memberfunktionen für das, was im Baum hängt --------------------------------
PriorityEntry :: PriorityEntry (short Priority, long Ident, 
				VisType iVTyp, char *pKText)
{
	m_Priority = Priority;
	m_Ident = Ident;
	m_iVTyp = iVTyp;
	if (pKText != NULL)
		m_pMText = StrDup (pKText, RC_ctPriorityEntry);
	else
		m_pMText = NULL;
}

PriorityEntry :: ~PriorityEntry (void) 
{
	DELETE (m_pMText);
}

char *PriorityEntry :: GetString (char *pBuff, short len) 
{
static char locBuff[_MAX_PATH+1];
char cT = cVisType (m_iVTyp);

	if (cT == '\0') cT = 'U';
	if (DEX_GetIdBase() == 10) {
		wsprintf (locBuff, "%03d:%08ld:%c:%-45s", m_Priority, m_Ident,
						cT, m_pMText ? m_pMText : "");
	} else {
		wsprintf (locBuff, "%03d:%08lx:%c:%-45s", m_Priority, m_Ident,
						cT, m_pMText ? m_pMText : "");
	}
	if (pBuff != NULL) {
		strncpy (pBuff, locBuff, len-1);
		pBuff[len-1] = '\0';
		return pBuff;
	}

return locBuff;
}

// globale Funktion, die von IRISMAIN aus gerufen wird ------------------------
short doPrioritySelect (pWindow pW, CIdTree &IDs, char *pActSight)
{
PrioritySelDlg PSDlg (pW, IDs);
int iResult;

	PSDlg.Show (Centre);
	if ((iResult = PSDlg.Result()) != 0) 
		IDs.WriteBack (pActSight);

return iResult;
}

// lokale Daten, die Werte an FriendFunktionen übergeben ----------------------
typedef struct tagFILLPRIOTREEDATA {
	PriorityEntryCreator *pPECr;
	PrioritySelDlg *pPrioritySel;
} FILLPRIOTREEDATA;

// Memberfunktionen für die eigentliche DialogBox -----------------------------
#pragma warning (disable:4355)

PrioritySelDlg :: PrioritySelDlg (pWindow pParent, CIdTree &Ids)
	        : DialogWindow (pParent, SELPRIORITY),
		  OKButton (this, IDOK),
		  CancelButton (this, IDCANCEL),
		  TestButton (this, IDB_APPLY),
		  Priorities (this, IDL_PRIORITY),
		  PrioritySel (this, IDE_PRIORITY, IDMS_PRIORITY, Range (0, 999)),
		  _Idents (Ids)
{
// EierUhr anzeigen
CEierUhr Wait (this);

// Controls initialisieren
	OKButton.Disable();
	TestButton.Disable();
	PrioritySel.Disable();

// SpinControl ist noch nicht angefaßt
	SpinHasChanged (FALSE);
	OldIndex() = -1;		// nichts selektiert
	iChanged = FALSE;		// nichts verändert

// Baum für Prioritäten (ListBox) anlegen
	pPT = new PriorityTree ();
	pPTRes = new PriorityTree ();
	if (pPT == NULL || pPTRes == NULL) {
		db_error (EC_NOMEMORY, RC_ctPrioritySelDlg);
		return;
	}

	{
	// lokale Pointer setzen
	PriorityEntryCreator PECr (*pPT);
	FILLPRIOTREEDATA FPD;

		FPD.pPECr = &PECr;
		FPD.pPrioritySel = this;

	// Baum aufbauen und ListBox füllen
		Idents().PrioTree().Every (FillWithPriorities, &FPD);
	}
	{
	// SicherheitsKopie der Prioritäten anlegen
	PriorityEntryCreator PECr (*pPTRes);
	FILLPRIOTREEDATA FPD;

		FPD.pPECr = &PECr;	
		FPD.pPrioritySel = NULL;
		Idents().PrioTree().Every (FillResPrioTree, &FPD);
	}

// alles richtig initialisieren
	if (pPT -> Count() > 0) {
		OKButton.Enable();
		TestButton.Enable();
		PrioritySel.Enable();

		Priorities.ChangeCurrentIndex (0);
		doWork();
	}
}

#pragma warning (default:4355)

bool EXPORTTRIAS FillResPrioTree (void *pObj, void *pData) 
{
// wenn dieser Identifikator nicht zur aktuellen Sicht gehört, dann wieder raus
FILLPRIOTREEDATA *pFPD = (FILLPRIOTREEDATA *)pData;
CIdentifikator *pId = & ((CIdRef *)pObj) -> rCId();
VisType iVTyp = ((CIdRef *)pObj) -> FVisTyp();

//	if (!pId -> isCustomized (VTypToBits (iVTyp))) return;	
	// Ident/ObjektTyp ist nicht in aktueller Sicht oder nicht visualisiert
	{
	// In Baum einhängen
	PriorityEntry *pPE = Create (*(pFPD -> pPECr), PriorityEntry)(
				pId -> Priority (iVTyp), pId -> Id(), iVTyp
			     );

		if (pPE == NULL) {
			db_error (EC_NOMEMORY, RC_FillResPrioTree);
			return false;
		}
	}

return true;
}


// Aufbauen des lokalen Prioritätsbaumes und füllen der Listbox ---------------
bool EXPORTTRIAS FillWithPriorities (void *pObj, void *pData) 
{
// wenn dieser Identifikator nicht zur aktuellen Sicht gehört, dann wieder raus
FILLPRIOTREEDATA *pFPD = (FILLPRIOTREEDATA *)pData;
CIdentifikator *pId = & ((CIdRef *)pObj) -> rCId();
VisType iVTyp = ((CIdRef *)pObj) -> FVisTyp();

//	if (!pId -> isCustomized (VTypToBits (iVTyp))) return;
	{
	PBD_Ident Id (&(CurrActDirisW -> DBO().PbdDB()), pId -> Id());

	// In Baum einhängen
	PriorityEntry *pPE = Create (*(pFPD -> pPECr), PriorityEntry)(
					pId -> Priority (iVTyp), 
					pId -> Id(), iVTyp,
					Id.GetKurzText()
			     );
		if (pPE == NULL) {
			db_error (EC_NOMEMORY, RC_FillWithPriorities);
			return false;
		}

	// in ListBox reinhängen
		pFPD -> pPrioritySel -> Priorities.AddString (pPE -> GetString());
	}

return true;
}


PrioritySelDlg :: ~PrioritySelDlg (void) 
{
	DELETE (pPT);
	DELETE (pPTRes);
}

void PrioritySelDlg :: ButtonClick (ControlEvt e) 
{
	switch ((unsigned int)e.GetControlID()) {
	case IDOK:
		if (SpinHasChanged()) { // aktuellen Wert des SpinControls holen
			PrioritySel.CopyToSpin();
			doWork();
		}
		EndDlg (ApplyPriorities());	// Prioritäten neu einstellen
		break;

	case IDCANCEL:
		EndDlg (ApplyPriorities (TRUE));	// abbrechen
		break;

	case IDB_APPLY:
		if (SpinHasChanged()) { // aktuellen Wert des SpinControls holen
			PrioritySel.CopyToSpin();
			doWork();
		}
		ApplyPriorities();	// Prioritäten neu einstellen
		break;
	}
}


void PrioritySelDlg :: ListBoxSel (ControlEvt e)
{
// wenn nicht für uns, dann wieder raus
	if (e.GetControlID() != IDL_PRIORITY) return;

// Gesamte Austauscharbeit in Listbox und Baum ausführen
short iCurrPrio = doWork();

	if (iCurrPrio != -1)	// neuen Wert in SpinControl kopieren
		PrioritySel.SetValue (iCurrPrio);
}


short PrioritySelDlg :: doWork (void)
{
// Wert aus Spin neu in ListBox einhängen
short iCurrIndex = Priorities.GetCurrentIndex();	// neue Selektion
short newIndex = -1;				// neuer Index des alten Items

// Daten der neuen Selektion lesen
short iCurrPrio = -1;

	if (iCurrIndex != -1) {
	char pBuff[80];

		Priorities.GetString (pBuff, iCurrIndex, sizeof(pBuff));
		iCurrPrio = atoi (pBuff);	
	} else
		return -1;	// nichts selektiert

	if (!SpinHasChanged()) {	// wenn nichts geändert wurde
		OldIndex() = iCurrIndex;
		return iCurrPrio;
	}

// Eintrag im Baum Finden und austauschen
	Priorities.Hide();	// ListBox ausblenden
	if (OldIndex() != -1) {
		newIndex = ReInsertEntry (OldIndex());
		if (newIndex == -1) {
			Priorities.Show();
			return -1;		// Fehler
		}
		iChanged = TRUE;
	}

// Selektion in der ListBox richten
	if (newIndex != -1) {
	// nur wenn nicht erste Selektion 
		if (OldIndex() > iCurrIndex && newIndex <= iCurrIndex)
			iCurrIndex++;
		else if (OldIndex() < iCurrIndex && newIndex >= iCurrIndex)
			iCurrIndex--;
	}

//	iCurrIndex = newIndex;		// Eintrag bleibt aktiv

// neuer aktueller Eintrag
	OldIndex() = iCurrIndex;
	Priorities.ChangeCurrentIndex (iCurrIndex);
	Priorities.Show();	// ListBox wieder einblenden

// SpinControl wieder jungfräulich
	SpinHasChanged (FALSE);

return iCurrPrio;	// Priorität des neuen Eintrages liefern
}

void PrioritySelDlg :: VertScroll (ScrollEvt e) 
{
	if ((uint)e.GetScrollBar() -> GetID() == IDMS_PRIORITY) {
	// SpinControl betätigt
		PrioritySel.CopyToEdit ();
		SpinHasChanged (TRUE);
	}
}

void PrioritySelDlg :: EditFocusChg (EditFocusChgEvt e) 
{
	if (!e.gotFocus() && (uint)e.GetControlID() == IDE_PRIORITY) {
		if (PrioritySel.isModified()) {
			PrioritySel.CopyToSpin();
			SpinHasChanged (TRUE);
			doWork();
		}
	}

// weiterleiten
	DialogWindow :: EditFocusChg (e);
}

short PrioritySelDlg :: ApplyPriorities (Bool iRestore) 
{
// wenn überhaupt nichts geändert wurde, dann wieder raus
	if (!iChanged) return 0;

// wenn kein Baum existiert, dann raus
	if (pPT == NULL || pPTRes == NULL) return 0;

// für alle Identifikatoren der aktuellen Sicht Prioritäten neu einstellen
PriorityTree *pLocPT = iRestore ? pPTRes : pPT;
CTable t(*pLocPT);
BOOL ifRO = DEX_GetROMode();

	for (t.First(); t.Valid(); t.Next()) {
	PriorityEntryLock l(t);

		if (!l) continue;
		Idents().ChangePriority (l -> Ident(), l -> Priority(), 
					 l -> FVisTyp(), !iRestore && !ifRO);
	}

// Hauptfenster neu zeichnen
	DEX_RePaint();

return 1;	// alles OK
}


// in ListBox und Baum Eintrag modifizieren -----------------------------------
short PrioritySelDlg :: ReInsertEntry (short iIndex) 
{
// wenn kein Baum da ist, dann mit Fehler raus
	if (pPT == NULL) return -1;

CTable t(*pPT);
char pBuff[80];

// Eintrag aus ListBox lesen und anschließend löschen
	Priorities.GetString (pBuff, iIndex, sizeof(pBuff));
	Priorities.DelString (iIndex);

short oldPrio = atoi (strtok (pBuff, ":"));	// alte Priorität lesen
long lIdent = strtoul (strtok (NULL, ":"), NULL, DEX_GetIdBase());	// Identifikator lesen
VisType iVTyp = FGetVisTyp (strtok (NULL, ":"));

	for (t.FindFirst (&lIdent); t.Valid(); t.FindNext (&lIdent)) {
	// neue Priorität reinschreiben
	PriorityEntryLock l(t);

		if (l && l -> FVisTyp() == iVTyp) {
		// neuen Wert im Baum setzen
			l -> Priority() = PrioritySel.GetValue();
		
		// Eintrag neu in ListBox einhängen
			return Priorities.AddString (l -> GetString());
		}
	}

return -1;
}
