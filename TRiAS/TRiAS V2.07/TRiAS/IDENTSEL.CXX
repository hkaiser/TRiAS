// Funktionen zur Selektion der zu zeichnenden Objekte
// File: IDENTSEL.CXX

#include "triaspre.hxx"

#if defined(WIN32)
#include <dirisole.h>
#include "extmain3.hxx"
#endif

#include "strings.h"

#include "identsel.hxx"
#include "legdinfo.hxx"
#include "prlayout.hxx"
#include "legende.hxx"
#include "legwind.hxx"
#include "minitpbd.hxx"

#include "triasres.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// globale Variablen ----------------------------------------------------------
extern ExtDirisWindow *CurrActDirisW;
extern HelpDisplay *IrisHD;
extern CLegendeWindow *pLegende;
extern bool LegendToRepaint;
extern HPALETTE hPalette;

#define ID_RESULT_NEWVIEW		10
#define ID_RESULT_NEWACTVIEW	11

// ---------------------------------------------------------------------------
bool IrisWind :: ShowIdentSel (void) 
{
char cbBuffer[MAXVIEWNAMESIZE+1];

	DBO().GetActiveSightName (cbBuffer, sizeof(cbBuffer));

// Dialogfenster generieren
long CObj = ObjInfoListe.GetSelectedObject();

	if (CObj == -1L) {
	// kein Objekt selektiert
		if (DBO().ClipRegionONr() != -1L) 
			CObj = DBO().ClipRegionONr();
	}

CIdentSelektion *pISDlg = new CIdentSelektion (this, DBO(), cbBuffer, CObj);

// Dialogfenster anzeigen
	pISDlg -> Show (Centre);          // Idents auswählen

int fResult = pISDlg -> Result();

	if (ID_RESULT_NEWVIEW == fResult || ID_RESULT_NEWACTVIEW == fResult) {
		if (pISDlg -> GetNewSightName (cbBuffer, sizeof(cbBuffer))) {
#if defined(WIN32)
		CEierUhr Wait (this);
		ExtDirisWindow *pFrame = GetFrame();

			if (pFrame && DBO().AddItemToSightMenu (pFrame -> MainMenu(), cbBuffer))
				DrawMenuBar (pFrame -> Handle (API_WINDOW_HWND));
			
		// Sicht wurde umbennant, wieder als aktuelle setzen
			if (ID_RESULT_NEWACTVIEW == fResult) {
				DBO().ProcessMenuEvent (cbBuffer, false);
				RePaint();
			}
#else
			if (DBO().AddItemToSightMenu (MainMenu(), cbBuffer))
				DrawMenuBar (Handle (API_WINDOW_HWND));
#endif
		}
	}

	DELETE (pISDlg)
	if (fResult) {
	// Caption neu einlesen
		DEX_ReReadCaption();
		RePaint();
	}

return fResult;
}

extern "C" {

bool EXPORTTRIAS WINAPI FillViewList (char *pPtr, bool, void *pCB)
{
	if (pCB && pPtr) {
		((ComboBox *)pCB) -> AddString (pPtr);
		return true;
	}
	
return false;
}

}

// Konstruktor für Dialogfenster ----------------------------------------------
#pragma warning (disable: 4355)

CIdentSelektion :: CIdentSelektion (pWindow pW, DatenBasisObjekt &rDBO,
				    char *actualSight, long) 
		 : OwnerDrawDialogWindow (pW, IDENTSELEKTION),    // Dialogfenster
		   m_NewViewName (this, IDC_NEWSIGHT),     // Ressourcen
		   m_NewSightButton (this, IDOK),
		   m_SelBox (this, IDL_LISTSEL),
		   m_pbTempView (this, IDB_SELOK),
#if !defined(WIN32)
		   m_HelpButton (this, IDB_SELHELP),
#endif // WIN32
		   m_SelAllButton (this, IDB_SELALL),
		   m_Standard (this, IDB_STANDARD),         // CheckBox
		   m_ActVisInfo (this, IDB_ACTVISINFO),
		   m_RenameView (this, IDCB_RENAMEVIEW),
		   m_BMasstab (this, IDE_IDENTSELMASSTAB),
		   m_sleDesc (this, IDE_DESCRIPTION),
		   m_rDBO (rDBO)
{
// EierUhr anzeigen
CEierUhr Wait (pW);

	m_actSight = NULL;		// für alle Fälle
	m_lMasstab = -1L;
	m_iActIndex = -1;
	m_fShowMenu = 0;
	m_fHadDesc = false;
	
// Ressourcen initialisieren
CTable t (Idents().IdentTree());

	for (t.First(); t.Valid(); t.Next()) {
	CIdentifikatorLock l(t);

		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (!l) continue;

	short iOTypes = l -> GetOTypes (DB());	// liest ggf. in GeoDB

/*		if (iOTypes == 0) {	// Objekte noch nie geladen
			DB().FindId (lIdent, NULL, &iOTypes);
			if (iOTypes == 0)
			// wenn keine GeoObjekte mit diesem Ident existieren
				continue;	// mit nächstem weitermachen
		}
*/
	// wenn keine GeoObjekte mit diesem Ident existieren
		if (iOTypes == 0) continue;	// mit nächstem weitermachen
			
	long lIdent = l -> Id();		// Id aus Node lesen
	PBD_Ident Id (&(DBO().PbdDB()), lIdent);	// KurzText lesen
	CIdentSelData *pISD = new CIdentSelData (lIdent, Id.GetKurzText());

		if (!pISD) continue;
	
	// PLFT setzen
		if (l -> toPaint (TPPunkt)) pISD -> setP ();
		if (l -> toPaint (TPLinie)) pISD -> setL ();
		if (l -> toPaint (TPFlaeche)) pISD -> setF ();
		if (l -> toPaint (TPText)) pISD -> setT ();
		pISD -> FBackupBits();
		pISD -> SetOTypes (iOTypes);

	// in SelBox einhängen
	short iIndex = (short)m_SelBox.AddItem (pISD);

		if (iIndex >= 0 && pISD -> hasOne()) {
			m_SelBox.ChangeSelected (iIndex);
			pISD -> setSel();
			pISD -> SetInitSel();
		}
	}

// SetAllButton initialisieren
	m_fSetAllStatus = true;

// ComboBox mit allen SichtNamen füllen
	{
	ENUMNOKEY ENK;

		ENK.eFcn = (ENUMNOKEYPROC)FillViewList;
		ENK.ePtr = &m_NewViewName;
		DEX_EnumSights (ENK);
	}
	
// Namen der aktuellen Ansicht aus Menu holen
	if (*actualSight) {
	short iIndex = m_NewViewName.FindString (actualSight);

		if (iIndex != -1) 	// Anzeige des AnsichtNamens
			m_NewViewName.ChangeCurrentIndex (iIndex); 
	} else
		m_NewSightButton.Disable();	// Neu & Löschen inaktiv

// CheckBox's initialisieren
	m_Standard.SetChecked(false);
	m_fStandard = false;

	m_RenameView.SetChecked (false);
	m_RenameView.Disable();		// erst zuschalten bei neuem Namen
	
	m_sleDesc.SetTextLimit (80);	// Windows kann Captions nur 80 Zeichen lang machen
	
	if (*actualSight) {
	// aktuelle Sicht existiert
		m_actSight = new char [strlen (actualSight) +1];
		if (m_actSight == NULL) {
			m_ActVisInfo.SetChecked (false);
			m_ActVisInfo.Disable();
		} else {
			strcpy (m_actSight, actualSight);
			m_ActVisInfo.SetChecked (true);
		}

	// BezugsMaßstab vorhanden ?
		m_lMasstab = GetBMasstab ();
		
	// SichtBeschreibung besorgen
	VIEWDESC VD;
	
		VD.m_dwSize = sizeof(VIEWDESC);
		VD.m_pView = m_actSight;
		VD.m_pDesc = new char [_MAX_PATH];
		VD.m_iLen = _MAX_PATH;
		if (DEX_GetViewDescription (VD)) {
			m_sleDesc.SetText (VD.m_pDesc);
			m_fHadDesc = true;
		} else
			m_sleDesc.SetText ("");
		DELETE (VD.m_pDesc);
	} else {
		m_actSight = new char [strlen (actualSight) +1];
		if (m_actSight == NULL) 
			m_ActVisInfo.Disable();
		m_ActVisInfo.SetChecked (false);
	}

// Control aktivieren
	m_BMasstab.SetNumEditMode (NumEdit :: NEM_NoTest);

// Knöpfe richten
	AdjustOK();
}

#pragma warning (default: 4355)

// Destruktor -----------------------------------------------------------------
CIdentSelektion :: ~CIdentSelektion (void) 
{
	DELETE (m_actSight);
}


long CIdentSelektion :: GetBMasstab (void) 
{
// Daten initialisieren
long lMasstab = -1L;		// für alle Fälle

	if (DB().GetDBVersion() < VERSION05000008 || m_actSight == NULL) {
		m_BMasstab.Disable();
		return -1L;
	}

// Sichten haben Merkmale
HeaderEntry HE (DB(), IDS_HDRSICHTBMASSTAB);
long lVar = HE.EntryLong (-1L);

	if (lVar == -1L) {
	// nicht gegeben: neuen Wert abspeichern
		MainInitPbd (DB(), IDS_HDRSICHTBMASSTAB, true);
		return -1L;
	}

	{
	CActDB ActDB (DB());		// #ActDB
	Sicht S (DB(), m_actSight);
	char *pMText = NULL;
	ErrInstall EI (WC_NOTFOUND);

		S.GetMiText (lVar, &pMText);
		if (pMText == NULL) return -1L;

		lMasstab = atol (pMText);
		if (lMasstab != 0) 
			m_BMasstab.SetText (pMText);
		DELETE (pMText);
	}

return lMasstab;
}


// Eventhandler ---------------------------------------------------------------
void EXPORTTRIAS CIdentSelektion :: ButtonClick (ControlEvt e) 
{
	switch ((uint)e.GetControlID ()) {
	case IDB_SELOK:			// temporäre Sicht
		EndDlg (OKButtonSelected() == EC_OKAY);
		break;

	case IDCANCEL:
		EndDlg ();              // abbrechen --> raus
		break;

	case IDB_SELHELP:
		IrisHD -> Show (IDB_SELHELP);
		break;

	case IDOK:              // neue Ansicht definieren
		{
		bool fNew = false;
		CEierUhr Wait (this);

			if (!WriteNewSight(fNew)) {
				EndDlg();	// Fehler und raus
				break;
			}
			EndDlg (fNew ? ID_RESULT_NEWACTVIEW : ID_RESULT_NEWVIEW);	// Raus
		}
		break;

	case IDB_STANDARD:
		m_fStandard = m_Standard.isChecked();
		break;

	case IDB_SELALL:
		{
		register int n = m_SelBox.GetCount();     // Anzahl der Einträge

			if (m_fSetAllStatus) {
			// alles UnMarkieren
				m_fSetAllStatus = false;
				m_SelBox.Hide ();
				m_SelBox.ChangeSelected (Range (0, n-1), false);
				m_SelBox.Show ();
				m_SelAllButton.SetText (ResString (IDS_SELALL, 15));
				ForgetInitialSelection();
				AdjustData ();
			} else {
			// alles markieren
				m_fSetAllStatus = true;
				m_SelBox.ChangeSelected (Range (0, n-1));
				m_SelAllButton.SetText (ResString (IDS_UNSELALL, 15));
				AdjustData (false);
			} 
			AdjustOK();
		}
		break;
	}
}


// OKButton gedrückt (temporäre Sicht generieren) -----------------------------
#define pPVI	(pVI[0])
#define pLVI	(pVI[1])
#define pFVI	(pVI[2])
#define pTVI	(pVI[3])

ErrCode CIdentSelektion :: OKButtonSelected (void)
{
// Anzahl der selektierten Items
register int iCount = m_SelBox.GetNoSelected ();
int *lpFeld = new int [iCount];
HPALETTE hPal = 0;

// Fehler: Kein Speicherplatz.
	if (lpFeld == NULL) return (ErrCode)db_error (EC_NOMEMORY, RC_IdSelBClk);

// Alles selektierte löschen
	Idents().IdentTree().Every (ResetPaintFlag);
	Idents().PrioTree().EveryDelete();		// Prioritäten werden neu aufgebaut

Sicht *pS = NULL;	// evtl. BezugsSicht

	if (!m_ActVisInfo.isChecked()) {	// Farben von Platte
	// temporäre (Bezugs-)Sicht generieren
	char SightName[SIGHTMENUITEM+1];

		if (m_NewViewName.GetTextLen() > 0) 	// SichtName ist vorgegeben
			m_NewViewName.GetText (SightName, SIGHTMENUITEM+1);
		else				// DefaultSicht
			strcpy (SightName, ResString (IDS_DEFAULTVISINFO, SIGHTMENUITEM+1));

		pS = new Sicht (DB(), SightName);
		if (pS == NULL) {
			DELETE (lpFeld);
			return (ErrCode)db_error (EC_NOMEMORY, RC_IdSelBClk);
		}
		hPal = pS -> GetPalette();
	} else
		hPal = hPalette;

// Itemnummern liefern lassen
	m_SelBox.GetSelectedItems (iCount, lpFeld);

CTable tID (Idents().IdentTree());	// ID-Baum
VisInfo *pVI[4];		// Feld der 4 VisInfo's
CIdentObjects *pObjs = NULL;

	for (register int i = 0; i < iCount; i++) {
	CIdentSelData *pISD = (CIdentSelData *)m_SelBox.GetItem (lpFeld[i]);
	long Id = pISD -> FIdent();        // IdNr holen
	bool oldLoadInfo = false;
	bool oldTempInfo = false;
	bool fAllLoaded = false;
	bool fMovedAway = false;
	short oldDrawType = DT_Normal;
	short fSpec = 0;
	short iOldOTypes = 0;
	long lPCnt = 0, lLCnt = 0, lFCnt = 0, lTCnt = 0, lKCnt = 0;

	// alte LadeInfo aus CIdTree holen
		memset (pVI, '\0', 4*sizeof (VisInfo *));  // neue VisInfo' s
		pObjs = NULL;
		if (tID.Find (&Id)) {
		CIdentifikatorLock l(tID);

			DELETE(pObjs);
			if (l) {	// Priorität holen
			CIdentifikator *pId = (CIdentifikator *)l;
			
				oldLoadInfo = pId -> loaded();
				oldDrawType = pId -> DType();
				oldTempInfo = pId -> isTemp();
				iOldOTypes = pId -> GetOTypes();
				fAllLoaded = pId -> AreAllLoaded();
				fMovedAway = pId -> MovedAway();

				lPCnt = pId -> GetPointCount();
				lLCnt = pId -> GetLineCount();
				lFCnt = pId -> GetAreaCount();
				lTCnt = pId -> GetTextCount();
				lKCnt = pId -> GetComplexCount();
				pObjs = pId -> DetachObjList();

				if (pS != NULL) {
				// VisInfos aus BezugsSicht holen
					fSpec = pS -> GetCompleteVisInfo (
							Id, hPal, (VisInfo **)pVI, 
							pISD -> GetBits());
//					continue;
				} else if (oldTempInfo || m_ActVisInfo.isChecked()) {
				// VisInfos aus aktueller Sicht im Speicher holen
					fSpec = pId -> GetCompleteVisInfo (
							(VisInfo **)pVI, 
							pISD -> GetBits()
					);
				}
			} else
				continue;
		} else
			continue;

	// Rest in DefaultSicht suchen
		if (!oldTempInfo) 
			GetCompleteDefaultVisInfo (DB(), Id, hPal, (VisInfo **)pVI, pISD -> GetBits());

	// wenn was sein soll und nichts gegeben ist, dann Standard generieren
		fSpec |= MakeCompleteNewVisInfo ((VisInfo **)pVI, pISD -> GetBits(), false);

	// alten Ident löschen, um Platz für neuen zu schaffen
		if (!Idents().DeleteIdent (Id)) continue;	// Fehler: weiter

	// neuen Satz generieren
		if (!Idents().AddIdent (Id, pVI, fSpec, hPal)) 
			continue;
		
		if (tID.Find (&Id)) {	// wiederfinden
		CIdentifikatorLock l(tID);

			if (l) {
			CIdentifikator *pId = (CIdentifikator *)l;
			
			// alte Informationen beibehalten
				if (oldLoadInfo)
					pId -> Load();
				else
					pId -> UnLoad();
				if (oldTempInfo)
					pId -> Temp();
				else
					pId -> Perm();
				if (fAllLoaded)
					pId -> AllLoaded();
				else
					pId -> NotAllLoaded();
				
				if (fMovedAway) pId -> NotAllLoaded();

				pId -> DType() = oldDrawType;
				pId -> SetOTypes (iOldOTypes);

				pId -> InitPointCount (lPCnt);
				pId -> InitLineCount (lLCnt);
				pId -> InitAreaCount (lFCnt);
				pId -> InitTextCount (lTCnt);
				pId -> InitComplexCount (lKCnt);
				TX_VERIFY(NULL == pId -> AttachObjList(pObjs));
				pObjs = NULL;
			}
		} else {
			DELETE (lpFeld);	// Fehler
			DELETE (pS);
			continue;
		}
	}	// for (;;)
	DELETE (pObjs);

// evtl. alte Palette freigeben und neue setzen
	if (!m_ActVisInfo.isChecked() || hPal != hPalette) {
	// Farben von Platte oder Palette hat sich geändert
		if (hPalette != 0) DeleteObject (hPalette);
		hPalette = hPal;
	}

// evtl aktivierte Ansicht unCheck'n
	DBO().ActivateSight ((char *)g_cbNil);		// temporäre Ansicht ist aktiv
//	DBO().UnCheckItemAsActive();		// passiert in 'ActivateSight()'

// Identifikatorbaum von nicht mehr benötigten temporären
// Idents bereinigen
	DBO().RemoveTempIdents();

// Speicher wieder freigeben
	DELETE (lpFeld);
	DELETE (pS);

// wenn Legende aktiv ist, dann diese neu zeichnen
	LegendToRepaint = true;

ResString rsNoName (IDS_NOVIEWNAME, 30);

	if (pLegende) pLegende -> SetCaption ((char *)rsNoName.Addr());

// Notification absetzen
char cbView[SIGHTMENUITEM+1];

	cbView[0] = '\0';
	strcpy (&cbView[1], rsNoName);
	DEXN_SightSelected (cbView);	// temporäre Sicht

return EC_OKAY;		// Fertig --> raus
}


#undef pPVI
#undef pLVI
#undef pFVI
#undef pTVI


// EditControl hat Focus erhalten/verloren ------------------------------------
void EXPORTTRIAS CIdentSelektion :: EditFocusChg (EditFocusChgEvt) 
{
	return;
}

// ListBox angeklickt ---------------------------------------------------------
void EXPORTTRIAS CIdentSelektion :: ListBoxSel (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDL_LISTSEL:
		AdjustData();
		AdjustOK();
		break;

	case IDC_NEWSIGHT:
		AdjustOK();
		break;
	}		
}

void CIdentSelektion :: AdjustData (bool fRestore)
{
short iCnt = m_SelBox.GetCount();
ErrInstall EI (WC_NOTFOUND);

// für alle ListboxEinträge
CEierUhr Wait (GetParent());

	for (short iIndex = 0; iIndex < iCnt; iIndex++) {
	bool fSel = m_SelBox.GetSelection (iIndex);
	CIdentSelData *pISD = (CIdentSelData *)m_SelBox.GetItem (iIndex);

		if (fSel) {	// jetzt selektiert
			if (!pISD -> isSelected()) {
				if (pISD -> wasSelected() && fRestore) {
				// war bei Beginn der DlgBox selektiert
					pISD -> FRestoreBits();
				} else {
				// Info aus DefaultSicht holen
				short iTypes = 0;
				
					if (!pISD -> ReadAll())
						iTypes = pISD -> GetOTypes();	// Typen aus CIdentifikator
					else
						pISD -> SetReadAll (false);

					if (iTypes == 0) 	// Objekte noch nie geladen
						DBO().Idents().FindId (DB(), pISD -> FIdent(), NULL, &iTypes);

					pISD -> SetBits (GetDefaultTypes (DB(), pISD -> FIdent()) | iTypes);
					if (!pISD -> hasOne())
						pISD -> SetBits();	// alles oder nichts
				}
				pISD -> setSel();
			}
		} else {	// jetzt nicht mehr selektiert
			if (pISD -> isSelected()) {
			// jetzt alles abschalten
				pISD -> SetBits (0);
				pISD -> setSel (false);
			}
		}
	}
}

// vergessen der AnfangsSelektion ---------------------------------------------
void CIdentSelektion :: ForgetInitialSelection (void)
{
// für alle ListboxEinträge
short iCnt = m_SelBox.GetCount();

	for (short iIndex = 0; iIndex < iCnt; iIndex++) {
	CIdentSelData *pISD = (CIdentSelData *)m_SelBox.GetItem (iIndex);

		pISD -> SetInitSel (false);
		pISD -> SetReadAll (true);
	}
}

// Rücksetzen des Flags, löschen der VisInformation ---------------------------
void EXPORTTRIAS ResetPaintFlag (void *pObj) 
{
	TX_ASSERT(NULL != pObj);

	((CIdentifikator *)pObj) -> DisablePainting();	// PaintFlag rücksetzen
	((CIdentifikator *)pObj) -> ResetInit();		// OTypes nicht mehr gültig
}

bool CIdentSelektion :: GetNewSightName (LPSTR pBuffer, int iLen)
{
	if (m_NewViewName.GetTextLen() > 0) {
		m_NewViewName.GetText (pBuffer, iLen);
		return true;
	}

return false;
}

///////////////////////////////////////////////////////////////////////////////
// Neue Sicht erzeugen 
// Result: bool rfNew : Neue Ansicht ist gleichzeitig aktuelle Ansicht
bool CIdentSelektion :: WriteNewSight (bool &rfNew) 
{
	rfNew = false;		// für alle Fälle

// Anzahl der selektierten Items
register int iCount = m_SelBox.GetNoSelected();
int *lpFeld = new int [iCount];
long *IDs = new long [iCount];
short *pTypInfo = new short [iCount];

	if (lpFeld == NULL || IDs == NULL || pTypInfo == NULL) { 
	// Fehler: Kein Speicherplatz.
		DELETE (lpFeld);
		DELETE (IDs);

		db_error (EC_NOMEMORY, RC_IdSelBClk);
		return false;
	}

// Namen der neuen Ansicht holen
char Sight[SIGHTMENUITEM+1];

	m_NewViewName.GetText (Sight, SIGHTMENUITEM+1);

// Itemnummern liefern lassen
	m_SelBox.GetSelectedItems (iCount, lpFeld);
	for (register int i = 0; i < iCount; i++) {
	CIdentSelData *pISD = (CIdentSelData *)m_SelBox.GetItem (lpFeld[i]);
	
		IDs[i] = pISD -> FIdent();
		pTypInfo[i] = pISD -> GetBits();
	}

// Id's in ProFile wegschreiben
Sicht *pS = m_actSight ? new Sicht (DB(), m_actSight) : NULL;
long CObj = DBO().ClipRegionONr();
bool fRebuild = false;			// neue Sicht sofort aktivieren
int fFlags = 0;

	if (m_ActVisInfo.isChecked()) fFlags |= WSActVis;
	if (m_RenameView.isChecked()) {
		fFlags |= WSDelView;
		DBO().DeleteSightMenuItem (NULL, m_actSight);
	}
	
ErrCode EC = DBO().WriteSightIDs (Sight, IDs, iCount, pTypInfo, pS, fFlags, CObj);
	
	DELETE (pS);	// Speicher wieder freigeben

// evtl. neuen Standard setzen
	if (m_fStandard) {
		ProFile (DB().GetDBName()).SetStandardSight (Sight);
		DBO().SetDefaultSightName(Sight);
	}

// Sight in Menu aufnehmen
//int newIndex = DBO().AddItemToSightMenu (Sight);

// BezugsMasstab setzen
long lVar = -1L;
char InBuff[20];

	if (m_BMasstab.GetTextLen() > 0) {
	// BezugsMasstab eingegeben
		m_BMasstab.GetText (InBuff, 20);
		lVar = atol (InBuff);
		if (lVar == 0) lVar = -1L;
	}
	
long lMCode = HeaderEntry (DB(), IDS_HDRSICHTBMASSTAB).EntryLong (-1L);

	if (lMCode == -1) {	// nicht gegeben: neuen Wert abspeichern
		MainInitPbd (DB(), IDS_HDRSICHTBMASSTAB, true);
		lMCode = HeaderEntry (DB(), IDS_HDRSICHTBMASSTAB).EntryLong (-1L);
	}

// wenn BMasstab sich geändert hat oder andere Sicht, dann wegschreiben
	if (lVar != m_lMasstab || 
	    m_actSight == NULL || strcmp (m_actSight, Sight)) 
	{
	Sicht S (DB(), Sight);

		if (lVar == -1L)		// Merkmal löschen
			S.DelMiText (lMCode);
		else if (lMCode != -1L)		// neu schreiben
			S.PutMiText (lMCode, InBuff);
	}  

// evtl. SichtBeschreibung speichern
char *pDesc = new char [_MAX_PATH];
	
	if (pDesc) {
		m_sleDesc.GetText (pDesc, _MAX_PATH);
		
	VIEWDESC VD;
	short iLen = strlen (pDesc);
		
		VD.m_dwSize = sizeof(VIEWDESC);
		VD.m_pView = Sight;
		VD.m_pDesc = iLen > 0 ? pDesc : NULL;
		VD.m_iLen = iLen;
		DEX_SetViewDescription (VD);
		delete [] pDesc;
	} 
	
// Speicher wieder freigeben
	DELETE (lpFeld);
	DELETE (IDs);
	DELETE (pTypInfo);

// wenn lediglich eine alte Sicht modifiziert wurde, dann neu zeichnen
	if (EC == WC_RETURN) {  	// RebuildSight
		DBO().ProcessMenuEvent (Sight, (fFlags & WSDelView) ? false : true);
		RePaint();
	}

// wenn alte Sicht umbenannt wurde, dann muß weiter oben alles gemacht werden
	if (fFlags & WSDelView) 
		rfNew = true;			// neue Ansicht ist aktuelle Ansicht 

return true;
}


// EditControl wird verändert ------------------------------------------------
void EXPORTTRIAS CIdentSelektion :: EditChange (ControlEvt e) 
{
	if ((uint)e.GetControlID() == IDC_NEWSIGHT) {      // nur HeaderKey auswerten
		AdjustOK();
/*
		if (m_NewViewName.GetTextLen()) {  // Name vorhanden: Button's freigeben
			m_NewSightButton.Enable();

		char inBuff[SIGHTMENUITEM+1];
		
			m_NewViewName.GetText (inBuff, SIGHTMENUITEM+1);
			if (strcmp (m_actSight, inBuff))
				m_RenameView.Enable();
			else {
				m_RenameView.SetChecked (false);
				m_RenameView.Disable();
			}
		} else {           // Button's sperren
			m_NewSightButton.Disable();
		}
*/
	}
}


LRESULT EXPORTTRIAS CIdentSelektion :: Dispatch (Event e)
{
static short m_fShowMenu = 0;

	switch (e.Msg()) {
	case WM_SHOWTYPEMENU:
		if (!m_fShowMenu) {
#if defined(_DEBUG)
		short iIndex = e.WParam();
#endif // _DEBUG

			m_fShowMenu++;
			ShowMenu (e.WParam(), 
				  LOWORD(e.LParam()), HIWORD(e.LParam()));
			m_fShowMenu--;
		}
		return true;

	default:
		break;
	}

return OwnerDrawDialogWindow :: Dispatch (e);
}

// MenuKommandos aus der ListBox (PullDown je Entry) --------------------------
void EXPORTTRIAS CIdentSelektion :: MenuInit (MenuInitEvt)
{
	if (m_iActIndex < 0 || m_hMenu == 0) return;

CIdentSelData *pISD = (CIdentSelData *)m_SelBox.GetItem (m_iActIndex);
short iOTypes = pISD -> GetOTypes();		// Objekttypen besorgen

	if (iOTypes & TIPunkt) {
		CheckMenuItem (m_hMenu, IDM_VISTYPEPUNKT, 
			       MF_BYCOMMAND | (pISD -> hasP() ? MF_CHECKED : MF_UNCHECKED));
		EnableMenuItem (m_hMenu, IDM_VISTYPEPUNKT, MF_BYCOMMAND|MF_ENABLED);
	} else {
		CheckMenuItem (m_hMenu, IDM_VISTYPEPUNKT, MF_BYCOMMAND|MF_UNCHECKED);
		EnableMenuItem (m_hMenu, IDM_VISTYPEPUNKT, MF_BYCOMMAND|MF_GRAYED);
	}
	if (iOTypes & TILinie) {
		CheckMenuItem (m_hMenu, IDM_VISTYPELINIE, 
			       MF_BYCOMMAND | (pISD -> hasL() ? MF_CHECKED : MF_UNCHECKED));
		EnableMenuItem (m_hMenu, IDM_VISTYPELINIE, MF_BYCOMMAND|MF_ENABLED);
	} else {
		CheckMenuItem (m_hMenu, IDM_VISTYPELINIE, MF_BYCOMMAND|MF_UNCHECKED);
		EnableMenuItem (m_hMenu, IDM_VISTYPELINIE, MF_BYCOMMAND|MF_GRAYED);
	}
	if (iOTypes & TIFlaeche) {
		CheckMenuItem (m_hMenu, IDM_VISTYPEFLAECHE, 
			       MF_BYCOMMAND | (pISD -> hasF() ? MF_CHECKED : MF_UNCHECKED));
		EnableMenuItem (m_hMenu, IDM_VISTYPEFLAECHE, MF_BYCOMMAND|MF_ENABLED);
	} else {
		CheckMenuItem (m_hMenu, IDM_VISTYPEFLAECHE, MF_BYCOMMAND|MF_UNCHECKED);
		EnableMenuItem (m_hMenu, IDM_VISTYPEFLAECHE, MF_BYCOMMAND|MF_GRAYED);
	}
	if (iOTypes & TIText) {
		CheckMenuItem (m_hMenu, IDM_VISTYPETEXT, 
			       MF_BYCOMMAND | (pISD -> hasT() ? MF_CHECKED : MF_UNCHECKED));
		EnableMenuItem (m_hMenu, IDM_VISTYPETEXT, MF_BYCOMMAND|MF_ENABLED);
	} else {
		CheckMenuItem (m_hMenu, IDM_VISTYPETEXT, MF_BYCOMMAND|MF_UNCHECKED);
		EnableMenuItem (m_hMenu, IDM_VISTYPETEXT, MF_BYCOMMAND|MF_GRAYED);
	}
}

void EXPORTTRIAS CIdentSelektion :: MenuCommand (MenuCommandEvt e)
{
	if (m_iActIndex < 0) return;

CIdentSelData *pISD = (CIdentSelData *)m_SelBox.GetItem (m_iActIndex);

	switch (e.GetItemID()) {
	case IDM_VISTYPEPUNKT:
		pISD -> setP (pISD -> hasP() ? false : true);
		break;
		
	case IDM_VISTYPELINIE:
		pISD -> setL (pISD -> hasL() ? false : true);
		break;
		
	case IDM_VISTYPEFLAECHE:
		pISD -> setF (pISD -> hasF() ? false : true);
		break;
		
	case IDM_VISTYPETEXT:
		pISD -> setT (pISD -> hasT() ? false : true);
		break;

	case IDM_CANCELMENU:
		return;
	}
	if (pISD -> hasOne()) 
		m_SelBox.ChangeSelected (m_iActIndex);
	else
		m_SelBox.ChangeSelected (m_iActIndex, false);
	
	m_iActIndex = -1;	// keine MenuSelektion mehr
	AdjustData();		// Info's abstimmen
	AdjustOK();
}


void CIdentSelektion :: ShowMenu (short iIndex, short X, short Y)
{
// Menu generieren und anzeigen
Menu ISelMenu (VISTYPEMENU);
Point Pt (X, Y);

#if !defined(WIN32)
	m_SelBox.SetCaretIndex (iIndex);		// in 16 Bit hier, damit während des PostMessage neu gezeichnet werden kann
#endif
	m_hMenu = GetSubMenu (ISelMenu.Handle(API_MENU_HMENU), 0);		// SubMenu holen
	ClientToScreen (m_SelBox.Handle (API_CLIENT_HWND), (LPPOINT)&Pt);
	m_iActIndex = iIndex;
	TrackPopupMenu (m_hMenu, 0, Pt.X(), Pt.Y(), 0, 
			Handle (API_CLIENT_HWND), NULL);
	m_hMenu = 0;
}


// MouseEvents von ListBox ----------------------------------------------------
void EXPORTTRIAS CMultipleListBoxWindow :: MouseButtonDn (MouseEvt e)
{
	if (e.isRightButton()) {
	// Index des getroffenen ListBoxItems berechnen
	CoOrd X = 0, Y = 0;
	short iIndex = CalcIndex (e.Where().Y(), X, Y);

		if (iIndex >= 0) {
//			SetCaretIndex (iIndex);		// jetzt in CalcIndex, da SetCaretIndex den Inhalt verschieben kann
			PostMessage (GetParent() -> Handle (API_WINDOW_HWND), 
				     WM_SHOWTYPEMENU, iIndex, MAKELONG (X, Y));
		} else
			OwnerDrawListBoxEx :: MouseButtonDn (e);
	} else 
		OwnerDrawListBoxEx :: MouseButtonDn (e);
}


short CMultipleListBoxWindow :: CalcIndex (CoOrd Y, CoOrd &posX, CoOrd &posY)
{
int iItemHeight = ListBox_GetItemHeight (GetHandle(), 0);
int iFirst = ListBox_GetTopIndex (GetHandle());
Rectangle Rc = CanvasRect();			// Größe der ListBox
int iIndex = 0;

#if defined(WIN32)
// in WindowsKoord umrechnen, ListBox hat links-unten ihren (0, 0) - Punkt

	Y = Rc.Top()-Rc.Bottom()-Y;
	iIndex = short(iFirst + ((Y+iItemHeight) / iItemHeight) -1);
#else
// ListBox hat links-oben ihren (0, 0) - Punkt
	if (Y < 0) 
		Y = -Y;
	else
		Y = Rc.Top()-Rc.Bottom()-Y;			// ????
	iIndex = short(iFirst + ((Y+iItemHeight) / iItemHeight) -1);
#endif // WIN32

	if (iIndex < 0 || iIndex > GetCount()) 
		return -1;	// Index größer als letzter Eintrag
		
RECT rcItem;

#if defined(WIN32)
	SetCaretIndex (iIndex);		// jetzt hier, da Inhalt verschoben werden könnte
#endif
	ListBox_GetItemRect (GetHandle(), iIndex, &rcItem);
	posX = rcItem.right -5;
	posY = ((rcItem.bottom + rcItem.top) / 2);

return iIndex;
}


// ListBoxFunktionen ----------------------------------------------------------
CMultipleListBoxWindow :: CMultipleListBoxWindow (pDialogWindow pDW, ResID rsc)
			: OwnerDrawListBoxEx (pDW, rsc)
{
	// nothing to do
}

CMultipleListBoxWindow :: ~CMultipleListBoxWindow (void)
{
	// nothing to do
}


int CMultipleListBoxWindow :: GetSelectedItems (int iMaxItems, int *pItems)
{
	return ListBox_GetSelItems (GetHandle(), iMaxItems, pItems);
}


CIdentSelData :: CIdentSelData (long lIdent, char *pKText)
{
	m_lIdent = lIdent;
	m_pText = new char [_MAX_PATH];
	if (m_pText && 
		SUCCEEDED(ClassFromIdent (lIdent, m_pText, _MAX_PATH)))
	{
		strcat (m_pText, g_cbColon);
		strcat (m_pText, pKText);
	}

// Flags rücksetzen
	m_bfTypInfo = m_fTypInfo = 0;
	m_fSel = false;
	m_fwasSel = false;
	m_fReadAll = false;
}

CIdentSelData :: ~CIdentSelData (void)
{
	DELETE (m_pText);
}

// Routinen für OwnerDrawListBox ----------------------------------------------
bool EXPORTTRIAS CIdentSelektion :: DrawEntireItem (DrawItemEvt e)
{
Rectangle Rc = e.ItemSize();			// aktueller Bereich
HDC hDC = (HDC)e.Handle (API_CONTROL_HDC);		// DC holen
CIdentSelData *pISD = (CIdentSelData *)e.GetItemData();
char *pText = pISD -> FText();

	if (!pText) return false;

	if (e.isSelected()) {
		SetBkColor(hDC,GetSysColor(COLOR_HIGHLIGHT));
		SetTextColor(hDC,GetSysColor(COLOR_HIGHLIGHTTEXT));
	} else {
		SetBkColor(hDC,GetSysColor(COLOR_WINDOW));
		SetTextColor(hDC,GetSysColor(COLOR_WINDOWTEXT));
	}
		
	ExtTextOut (hDC, Rc.Left()+1, Rc.Top()+1, 
			ETO_CLIPPED|ETO_OPAQUE, (const RECT *)&Rc, 
			pText, strlen (pText), 
			NULL
		   );

	if (e.hasFocus()) DrawFocusRect (hDC, (RECT *)&Rc);
	
return true;
}

bool EXPORTTRIAS CIdentSelektion :: DrawItemFocus (DrawItemEvt e)
{
Rectangle Rc = e.ItemSize();			// aktuellen Bereich holen
HDC hDC = (HDC)e.Handle (API_CONTROL_HDC);		// DC holen

	DrawFocusRect (hDC, (RECT *)&Rc);

return true;
}

bool EXPORTTRIAS CIdentSelektion :: DrawItemSelect (DrawItemEvt e)
{
Rectangle Rc = e.ItemSize();			// aktueller Bereich
HDC hDC = (HDC)e.Handle (API_CONTROL_HDC);		// DC holen
CIdentSelData *pISD = (CIdentSelData *)e.GetItemData();
char *pText = pISD -> FText();

	if (!pText) return false;

	if (e.isSelected()) {
		SetBkColor (hDC, GetSysColor(COLOR_HIGHLIGHT));
		SetTextColor (hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
	} else {
		SetBkColor (hDC,GetSysColor(COLOR_WINDOW));
		SetTextColor (hDC,GetSysColor(COLOR_WINDOWTEXT));
	}
		
	ExtTextOut (hDC, Rc.Left()+1, Rc.Top()+1, 
			ETO_CLIPPED|ETO_OPAQUE, (const RECT *)&Rc, 
			pText, strlen (pText), 
			NULL
		   );

return true;
}

int EXPORTTRIAS CIdentSelektion::CompareItem (OwnerDrawEvt, void *pItem1, void *pItem2)
{	// Vergleichsfunktion
unsigned long lIdent1 = (unsigned long)((CIdentSelData *)pItem1) -> FIdent();
unsigned long lIdent2 = (unsigned long)((CIdentSelData *)pItem2) -> FIdent();
char cbBuffer1[MAX_OKS_LEN];
char cbBuffer2[MAX_OKS_LEN];

// bei Fehler Reihenfolge beibehalten
	if (FAILED(ClassFromIdent(lIdent1, cbBuffer1)))
		return -1;
	if (FAILED(ClassFromIdent(lIdent2, cbBuffer2)))
		return -1;

	return strcmp (cbBuffer1, cbBuffer2);
}

bool EXPORTTRIAS CIdentSelektion :: MeasureItem (MeasureItemEvt e)
{
TEXTMETRIC tm;
HWND hDlg = e.Handle (API_DLGWINDOW_HWND);
HDC hDC = GetDC (hDlg);

	GetTextMetrics (hDC, &tm);
	e.SetItemHeight (tm.tmHeight);
	ReleaseDC (hDlg, hDC);

return true;
}


bool EXPORTTRIAS CIdentSelektion :: DeleteItem (DeleteItemEvt e)
{
CIdentSelData *pISD = (CIdentSelData *)e.GetItemData();

	DELETE (pISD);

return true;
}

void EXPORTTRIAS CMultipleListBoxWindow :: FocusChange (FocusChangeEvt e)
{
	ControlWindow :: FocusChange (e);
}

// Knöpfe richten -------------------------------------------------------------
void CIdentSelektion :: AdjustOK (void)
{
short iIndex = m_NewViewName.GetCurrentIndex();
int iLen = m_NewViewName.GetTextLen();
bool fEnable = false;

	if (0 < iLen || -1 != iIndex) {		// Name vorhanden: Vorraussetzung für 'Sicht löschen'
	char inBuff[SIGHTMENUITEM+1];

		if (0 < iLen) 
			m_NewViewName.GetText (inBuff, SIGHTMENUITEM+1);
		else {
			TX_ASSERT(-1 != iIndex);
			m_NewViewName.GetString (inBuff, iIndex, SIGHTMENUITEM+1);
		}

		if (strcmp (m_actSight, inBuff))
			fEnable = true;
	} 

	if (0 == iLen || m_SelBox.GetNoSelected() <= 0) {
//		m_pbTempView.Disable();		// temporäre Ansichten brauchen keinen Namen
		m_NewSightButton.Disable();

		fEnable = false;
	} else {
//		m_pbTempView.Enable();
		m_NewSightButton.Enable();
	}

	if (fEnable) 
		m_RenameView.Enable();
	else {
		m_RenameView.SetChecked (false);
		m_RenameView.Disable();
	}
}
