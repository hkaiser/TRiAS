// Funktionen zur Selektion der zu zeichnenden Objekte
// File: IDENTSEL.CXX

#include "triaspre.hxx"

#if !defined(WIN16)
#include <dirisole.h>
#include "extmain3.hxx"
#endif

#include <Com/Thunk.h>

#include "strings.h"

#include "identsel.hxx"
#include "legdinfo.hxx"
#include "prlayout.hxx"
#include "legende.hxx"
#include "legwind.hxx"
#include "minitpbd.hxx"

#include "triasres.h"

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// globale Variablen ----------------------------------------------------------
extern ExtDirisWindow *CurrActDirisW;
extern HelpDisplay *IrisHD;
extern CLegendeClientWindow *pLegende;
extern bool LegendToRepaint;
extern HPALETTE hPalette;
extern DWORD g_dwMenu;

#define ID_RESULT_NEWVIEW		10
#define ID_RESULT_NEWACTVIEW	11

#if _TRiAS_VER < 0x0510
extern DWORD g_dwVer51;
#endif // _TRiAS_VER < 0x0510

///////////////////////////////////////////////////////////////////////////////
// OBJECTTYPE zu TRiAS-Objektbits konvertieren
DWORD OBJECTTYPEToBits (OBJECTTYPE rgType)
{
DWORD dwResult = 0L;

	if (rgType & OBJECTTYPE_Point) 
		dwResult |= OTPunkt;
	if (rgType & OBJECTTYPE_Line)
		dwResult |= OTLinie;
	if (rgType & OBJECTTYPE_Area)
		dwResult |= OTFlaeche;
	if (rgType & OBJECTTYPE_Text)
		dwResult |= OTText;
	if (rgType & OBJECTTYPE_Complex)
		dwResult |= OTKO;

	return dwResult;
}

///////////////////////////////////////////////////////////////////////////////
//
bool IrisWind::ShowIdentSel (void) 
{
char cbBuffer[MAXVIEWNAMESIZE+1];
char cbConnFilter[_MAX_PATH] = { 0 };

	DBO().GetActiveSightName (cbBuffer, sizeof(cbBuffer));
	DBO().GetViewConnectFilter(cbBuffer, cbConnFilter, sizeof(cbConnFilter));

// Dialogfenster generieren
//long CObj = ObjInfoListe.GetSelectedObject();
//
//	if (CObj == -1L) {
//	// kein Objekt selektiert
//		if (DBO().ClipRegionONr() != -1L) 
//			CObj = DBO().ClipRegionONr();
//	}

ResID resID = IDD_IDENTSELEKTION;

#if _TRiAS_VER < 0x0510
	if (0 == g_dwVer51) 
		resID = IDENTSELEKTION;		// alten Dialog verwenden
#endif // _TRiAS_VER < 0x0510

CIdentSelektion *pISDlg = new CIdentSelektion (this, DBO(), cbBuffer, cbConnFilter, resID);

// Dialogfenster anzeigen
	pISDlg -> Show (Centre);          // Idents auswählen

int fResult = pISDlg -> Result();

	if (ID_RESULT_NEWVIEW == fResult || ID_RESULT_NEWACTVIEW == fResult) {
		if (pISDlg -> GetNewSightName (cbBuffer, sizeof(cbBuffer))) {
		CEierUhr Wait (this);
		ExtDirisWindow *pFrame = GetFrame();

			cbConnFilter[0] = '\0';
			pISDlg -> GetConnectionFilter(cbConnFilter, sizeof(cbConnFilter));

			if (pFrame && DBO().AddItemToSightMenu (pFrame, 
					pFrame -> MainMenu(), cbBuffer, cbConnFilter) && 
				!(g_dwMenu & HANDLEMENU_MainMenu))
			{
				::DrawMenuBar (pFrame -> Handle (API_WINDOW_HWND));
			}

		// Sicht wurde umbenannt, wieder als aktuelle setzen
			if (ID_RESULT_NEWACTVIEW == fResult) 
				DBO().ProcessMenuEvent (cbBuffer, false, true);
		}
	}

	DELETE_OBJ (pISDlg);
	if (fResult) {
		DEX_ReReadCaption();		// Caption neu einlesen
		DEX_RePaint();
	}
	return fResult;
}

namespace {

	extern "C"
	BOOL EXPORTTRIAS WINAPI FillViewList (char *pPtr, BOOL, void *pCB)
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

CIdentSelektion::CIdentSelektion (pWindow pW, DatenBasisObjekt &rDBO,
		char const *actualSight, char const *pcConnFilter, ResID resID) 
:	OwnerDrawDialogWindow (pW, resID),    // Dialogfenster
	m_NewViewName (this, IDC_NEWSIGHT),     // Ressourcen
	m_NewSightButton (this, IDOK),
	m_SelBox (this, IDL_LISTSEL),
	m_pbTempView (this, IDB_SELOK),
#if defined(WIN16)
	m_HelpButton (this, IDB_SELHELP),
#endif // WIN16
	m_SelAllButton (this, IDB_SELALL),
	m_Standard (this, IDB_STANDARD),         // CheckBox
	m_ActVisInfo (this, IDB_ACTVISINFO),
	m_RenameView (this, IDCB_RENAMEVIEW),
	m_BMasstab (this, IDE_IDENTSELMASSTAB),
	m_sleDesc (this, IDE_DESCRIPTION),
	m_cbApplyConnectFilter(this, IDC_APPLY_CONNECT_FILTER),
	m_cbeConnFilters(this, IDC_CONNECTFILTER),
	m_rDBO (rDBO)
{
// EierUhr anzeigen
CEierUhr Wait (pW);

#if _TRiAS_VER < 0x0510
	if (0 == g_dwVer51) {
		m_cbApplyConnectFilter.Hide();
		m_cbApplyConnectFilter.Disable();
		m_cbeConnFilters.Hide();
		m_cbeConnFilters.Disable();
	}
#endif // _TRiAS_VER < 0x0510

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

	short iOTypes = l -> InitOTypes();	// liest ggf. in GeoDB

/*		if (iOTypes == 0) {	// Objekte noch nie geladen
			DB().FindId (lIdent, NULL, &iOTypes);
			if (iOTypes == 0)
			// wenn keine GeoObjekte mit diesem Ident existieren
				continue;	// mit nächstem weitermachen
		}
*/
	// wenn keine GeoObjekte mit diesem Ident existieren
		if (iOTypes == 0) continue;	// mit nächstem weitermachen
			
	CIdentSelData *pISD = NULL;
//	LPCSTR pcDataSrc = (rDBO.GetOpenCount() > 1) ? l -> GetDataSource() : NULL;

		TX_TRY(pISD = new CIdentSelData (l -> Id(), l -> GetKurzText (TRUE)));
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
	m_NewViewName.ForwardEvent (CB_LIMITTEXT, 128);		// sicherheitshalber auf die halbe Länge begrenzen

// CheckBox's initialisieren
	m_Standard.SetChecked(false);
	m_fStandard = false;

	m_RenameView.SetChecked (false);
	m_RenameView.Disable();			// erst zuschalten bei neuem Namen
	
	m_sleDesc.SetTextLimit (_MAX_PATH);	// Windows kann Captions nur 80 Zeichen lang machen
	
	if (*actualSight) {
	// aktuelle Sicht existiert
		TX_TRY(m_actSight = new char [strlen (actualSight) +1]);
		if (m_actSight == NULL) {
			m_ActVisInfo.SetChecked (false);
			m_ActVisInfo.Disable();
		} else {
			strcpy (m_actSight, actualSight);
			m_ActVisInfo.SetChecked (true);
		}

	// BezugsMaßstab vorhanden ?
		m_lMasstab = GetBMasstab();
		
	// SichtBeschreibung besorgen
	VIEWDESC VD;
	
		VD.m_dwSize = sizeof(VIEWDESC);
		VD.m_pView = m_actSight;
		TX_TRY(VD.m_pDesc = new char [_MAX_PATH]);
		VD.m_iLen = _MAX_PATH;
		if (DEX_GetViewDescription (VD)) {
			m_sleDesc.SetText (VD.m_pDesc);
			m_fHadDesc = true;
		} else
			m_sleDesc.SetText ("");
		DELETE_OBJ (VD.m_pDesc);

	// StandardAnsicht beachten
	char cbBuffer[64];

		if (DEX_GetDefaultView(cbBuffer) && !strcmp (cbBuffer, actualSight)) {
			m_Standard.SetChecked(true);
			m_fStandard = true;
		}
	} else {
		TX_TRY(m_actSight = new char [strlen (actualSight) +1]);
//		if (m_actSight == NULL) 

		if (NULL != m_actSight)
			m_actSight[0] = '\0';
		m_ActVisInfo.SetChecked (false);
		m_ActVisInfo.Disable();
	}

// Control aktivieren
	m_BMasstab.SetNumEditMode (NumEdit::NEM_NoTest);
	if (-1 != m_lMasstab && 0 != m_lMasstab)
		m_BMasstab.SetValue (m_lMasstab);

// Connectionfilter initialisieren
	InitConnectFilters(pcConnFilter);

// Knöpfe richten
	AdjustOK();
}

#pragma warning (default: 4355)

// Destruktor -----------------------------------------------------------------
CIdentSelektion::~CIdentSelektion (void) 
{
	DELETE_OBJ (m_actSight);
#if _TRiAS_VER < 0x0510
	if (0 != g_dwVer51)
#endif
	{
	// ImageList wird vom Destruktor ~CImageList freigegeben, hier 
	// doppeltes Freigeben verhindern
	CImageList *pIL = m_cbeConnFilters.SetImageList (NULL);
		
		if (pIL) delete pIL;
	}
}

long CIdentSelektion::GetBMasstab (void) 
{
	return (long)DBO().GetViewBMasstab (m_actSight);
}

///////////////////////////////////////////////////////////////////////////////
// Eventhandler 
void EXPORTTRIAS CIdentSelektion::ButtonClick (ControlEvt e) 
{
	switch ((uint)e.GetControlID ()) {
	case IDB_SELOK:				// temporäre Sicht
#if defined(_FORCE_LEGACY_CODE)
		EndDlg (OKButtonSelected() == EC_OKAY);
#else
		{
		bool fNew = false;
		CEierUhr Wait (this);
		ResString resTempView (IDS_TEMPVIEWNAME, 64);

			m_NewViewName.SetText (resTempView);
			if (!WriteNewSight(fNew, resTempView)) {
				EndDlg();	// Fehler und raus
				break;
			}
			EndDlg (ID_RESULT_NEWACTVIEW);	// raus
		}
#endif // defined(_FORCE_LEGACY_CODE)
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
		// Namen der neuen Ansicht holen
		char cbSight[SIGHTMENUITEM+1];

			m_NewViewName.GetText (cbSight, SIGHTMENUITEM+1);
			if (!WriteNewSight(fNew, cbSight)) {
				EndDlg();	// Fehler und raus
				break;
			}
			EndDlg (fNew ? ID_RESULT_NEWACTVIEW : ID_RESULT_NEWVIEW);	// raus
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
				m_SelAllButton.SetText (ResString (IDS_SELALL, 32));
				ForgetInitialSelection();
				AdjustData ();
			} else {
			// alles markieren
				m_fSetAllStatus = true;
				m_SelBox.ChangeSelected (Range (0, n-1));
				m_SelAllButton.SetText (ResString (IDS_UNSELALL, 32));
				AdjustData (false);
			} 
			AdjustOK();
		}
		break;

	case IDC_APPLY_CONNECT_FILTER:
		{
			AdjustOK();
		}
		break;
	}
}

#if defined(_FORCE_LEGACY_CODE)

// OKButton gedrückt (temporäre Sicht generieren) -----------------------------
#define pPVI	(pVI[0])
#define pLVI	(pVI[1])
#define pFVI	(pVI[2])
#define pTVI	(pVI[3])

ErrCode CIdentSelektion::OKButtonSelected (void)
{
// Anzahl der selektierten Items
register int iCount = m_SelBox.GetNoSelected ();
int *lpFeld = NULL; TX_TRY(lpFeld = new int [iCount]);
HPALETTE hPal = 0;

// Fehler: Kein Speicherplatz.
	if (lpFeld == NULL) return (ErrCode)db_error (EC_NOMEMORY, RC_IdSelBClk);

// Alles selektierte löschen
	Idents().IdentTree().Every (ResetPaintFlag);
	Idents().PrioTree().EveryDelete();		// Prioritäten werden neu aufgebaut

bool fActVisInfo = true;
char SightName[SIGHTMENUITEM+1] = { '\0' };

	if (!m_ActVisInfo.isChecked()) {	// Farben von Platte
	// temporäre (Bezugs-)Sicht generieren
	char SightName[SIGHTMENUITEM+1];

		if (m_NewViewName.GetTextLen() > 0) 	// SichtName ist vorgegeben
			m_NewViewName.GetText (SightName, SIGHTMENUITEM+1);
		else				// DefaultSicht
			strcpy (SightName, ResString (IDS_DEFAULTVISINFO, SIGHTMENUITEM+1));

		fActVisInfo = false;
		hPal = DBO().GetViewPalette(SightName);
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

			DELETE_OBJ(pObjs);
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

				if (!fActVisInfo) {
				// VisInfos aus BezugsSicht holen
				int iNewSpec = 0;

					TX_ASSERT(strlen(SightName) > 0);
					if (DBO().GetCompleteVisInfo (SightName, Id, (VisInfo **)pVI, pISD -> GetBits(), hPal, NULL, &iNewSpec))
						fSpec |= iNewSpec;
				} else if (oldTempInfo || m_ActVisInfo.isChecked()) {
				// VisInfos aus aktueller Sicht im Speicher holen
					fSpec = pId -> GetCompleteVisInfo ((VisInfo **)pVI, pISD -> GetBits());
				}
			} else
				continue;
		} else
			continue;

	// Rest in DefaultSicht suchen
		if (!oldTempInfo) 
			DBO().GetCompleteDefaultVisInfo (Id, (VisInfo **)pVI, pISD -> GetBits(), hPal);

	// wenn was sein soll und nichts gegeben ist, dann Standard generieren
		fSpec |= MakeCompleteNewVisInfo ((VisInfo **)pVI, pISD -> GetBits(), false);

	// alten Ident löschen, um Platz für neuen zu schaffen
		if (!Idents().DeleteIdent (Id)) continue;	// Fehler: weiter

	// neuen Satz generieren
		if (!Idents().AddIdent (DB(Id), Id, pVI, fSpec, hPal)) 
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
			DELETE_OBJ (lpFeld);	// Fehler
			continue;
		}
	}	// for (;;)
	DELETE_OBJ (pObjs);

// evtl. alte Palette freigeben und neue setzen
	if (!fActVisInfo || hPal != hPalette) {
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
	DELETE_OBJ (lpFeld);

// wenn Legende aktiv ist, dann diese neu zeichnen
	LegendToRepaint = true;

//ResString rsNoName (IDS_NOVIEWNAME, 30);
//
//	if (pLegende) 
//		pLegende -> SetCaption ((char *)rsNoName.Addr());

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

#endif // defined(_FORCE_LEGACY_CODE)

// EditControl hat Focus erhalten/verloren ------------------------------------
void EXPORTTRIAS CIdentSelektion::EditFocusChg (EditFocusChgEvt) 
{
	return;
}

// ListBox angeklickt ---------------------------------------------------------
void EXPORTTRIAS CIdentSelektion::ListBoxSel (ControlEvt e)
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

void CIdentSelektion::AdjustData (BOOL fRestore)
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
				} 
				else if (0 == pISD -> GetBits()) {
				// Info aus DefaultSicht holen, wenn nicht schon was vordefiniert ist
				short iTypes = 0;
				
					if (!pISD -> ReadAll())
						iTypes = pISD -> GetOTypes();	// Typen aus CIdentifikator
					else
						pISD -> SetReadAll (false);

					if (iTypes == 0) 	// Objekte noch nie geladen
						DBO().Idents().FindId (pISD -> FIdent(), NULL, &iTypes);

				OBJECTTYPE rgTypes = OBJECTTYPE_Unknown;

					if (SUCCEEDED(DBO().GetDefaultObjectTypes (pISD -> FIdent(), &rgTypes)))
						iTypes |= OBJECTTYPEToBits (rgTypes);

					pISD -> SetBits (iTypes);
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
void CIdentSelektion::ForgetInitialSelection (void)
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

bool CIdentSelektion::GetNewSightName (LPSTR pBuffer, int iLen)
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
bool CIdentSelektion::WriteNewSight (bool &rfNew, LPCSTR pcNewView) 
{
	rfNew = false;		// für alle Fälle

// Anzahl der selektierten Items
register int iCount = m_SelBox.GetNoSelected();
int *lpFeld = new int [iCount];
long *IDs = new long [iCount];
short *pTypInfo = new short [iCount];

	if (lpFeld == NULL || IDs == NULL || pTypInfo == NULL) { 
	// Fehler: Kein Speicherplatz.
		DELETE_OBJ (lpFeld);
		DELETE_OBJ (IDs);

		db_error (EC_NOMEMORY, RC_IdSelBClk);
		return false;
	}

// Itemnummern liefern lassen
	m_SelBox.GetSelectedItems (iCount, lpFeld);
	for (register int i = 0; i < iCount; i++) {
	CIdentSelData *pISD = (CIdentSelData *)m_SelBox.GetItem (lpFeld[i]);
	
		IDs[i] = pISD -> FIdent();
		pTypInfo[i] = pISD -> GetBits();
	}

// Id's in ProFile wegschreiben
long CObj = DBO().ClipRegionONr();
bool fRebuild = false;			// neue Sicht sofort aktivieren
int fFlags = 0;

	if (m_ActVisInfo.isChecked()) fFlags |= WSActVis;
	if (m_RenameView.isChecked()) {
		fFlags |= WSDelView;
		DBO().DeleteSightMenuItem (NULL, NULL, m_actSight);
	}
	
ErrCode EC = DBO().WriteSightIDs (pcNewView, IDs, iCount, pTypInfo, m_actSight, fFlags, CObj);
	
// evtl. neuen Standard setzen
	if (m_fStandard) 
		DEX_SetDefaultView(pcNewView);

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
	
// wenn BMasstab sich geändert hat oder andere Sicht, dann wegschreiben
	if (lVar != m_lMasstab || NULL == m_actSight || strcmp (m_actSight, pcNewView)) {
		if (lVar == -1L)			// Merkmal löschen
			DBO().DelViewBMasstab (pcNewView);
		else						// neu schreiben
			DBO().SetViewBMasstab (lVar, pcNewView);
	}  

// evtl. SichtBeschreibung speichern
char *pDesc = new char [_MAX_PATH];
	
	if (pDesc) {
		m_sleDesc.GetText (pDesc, _MAX_PATH);
		
	VIEWDESC VD;
	short iLen = strlen (pDesc);
		
		VD.m_dwSize = sizeof(VIEWDESC);
		VD.m_pView = (LPSTR)pcNewView;
		VD.m_pDesc = iLen > 0 ? pDesc : NULL;
		VD.m_iLen = iLen;
		DEX_SetViewDescription (VD);
		delete [] pDesc;
	} 
	
// Speicher wieder freigeben
	DELETE_OBJ (lpFeld);
	DELETE_OBJ (IDs);
	DELETE_OBJ (pTypInfo);

// wenn lediglich eine alte Sicht modifiziert wurde, dann neu zeichnen
	if (EC == WC_RETURN) {  	// RebuildSight
		if (fFlags & WSDelView)
			DBO().ProcessMenuEvent (pcNewView, false, true);
		else {
		// if the connection filter has changed, remove the actual filter
		char cbConnFilter[_MAX_PATH];

			if (GetConnectionFilter(cbConnFilter, sizeof(cbConnFilter))) {
				if (m_strConnFilter != cbConnFilter) {
					DBO().SetAllConnectionFilters(NULL);
					DBO().SetConnectFilter(pcNewView, cbConnFilter);
					DEXN_ReReadIdents();
					DEXN_ReReadContainer();
					DEXN_ReScale();
				}
			}
			else if (m_strConnFilter.size() > 0) {
				DBO().SetAllConnectionFilters(NULL);
				DBO().SetConnectFilter(pcNewView, cbConnFilter);
				DEXN_ReReadIdents();
				DEXN_ReReadContainer();
				DEXN_ReScale();
			}

		// switch to the new view
			DBO().ProcessMenuEvent (pcNewView, true, true);
		}
		RePaint();
	}

// wenn alte Sicht umbenannt wurde, dann muß weiter oben alles gemacht werden
	if (fFlags & WSDelView) 
		rfNew = true;			// neue Ansicht ist aktuelle Ansicht 
	return true;
}


// EditControl wird verändert ------------------------------------------------
void EXPORTTRIAS CIdentSelektion::EditChange (ControlEvt e) 
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


LRESULT EXPORTTRIAS CIdentSelektion::Dispatch (Event e)
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

return OwnerDrawDialogWindow::Dispatch (e);
}

// MenuKommandos aus der ListBox (PullDown je Entry) --------------------------
void EXPORTTRIAS CIdentSelektion::MenuInit (MenuInitEvt)
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

void EXPORTTRIAS CIdentSelektion::MenuCommand (MenuCommandEvt e)
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


void CIdentSelektion::ShowMenu (short iIndex, short X, short Y)
{
// Menu generieren und anzeigen
Menu ISelMenu (VISTYPEMENU);
Point Pt (X, Y);

	if (iIndex < 0) iIndex = 0;
	if (iIndex >= m_SelBox.GetCount())
		iIndex = m_SelBox.GetCount()-1;
		 
#if defined(WIN16)
	m_SelBox.SetCaretIndex (iIndex);		// in 16 Bit hier, damit während des PostMessage neu gezeichnet werden kann
#endif
	m_hMenu = GetSubMenu (ISelMenu.Handle(API_MENU_HMENU), 0);		// SubMenu holen
	ClientToScreen (m_SelBox.Handle (API_CLIENT_HWND), (LPPOINT)&Pt);
	m_iActIndex = iIndex;
	TrackPopupMenu (m_hMenu, 0, Pt.X(), Pt.Y(), 0, Handle (API_CLIENT_HWND), NULL);
	m_hMenu = 0;
}


// MouseEvents von ListBox ----------------------------------------------------
void EXPORTTRIAS CMultipleListBoxWindow::MouseButtonDn (MouseEvt e)
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
			OwnerDrawListBoxEx::MouseButtonDn (e);
	} else 
		OwnerDrawListBoxEx::MouseButtonDn (e);
}


short CMultipleListBoxWindow::CalcIndex (CoOrd Y, CoOrd &posX, CoOrd &posY)
{
int iItemHeight = ListBox_GetItemHeight (GetHandle(), 0);
int iFirst = ListBox_GetTopIndex (GetHandle());
Rectangle Rc = CanvasRect();			// Größe der ListBox
int iIndex = 0;

#if !defined(WIN16)
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
#endif // WIN16

	if (iIndex < 0 || iIndex > GetCount()) 
		return -1;	// Index größer als letzter Eintrag
		
RECT rcItem;

#if !defined(WIN16)
	SetCaretIndex (iIndex);		// jetzt hier, da Inhalt verschoben werden könnte
#endif
	ListBox_GetItemRect (GetHandle(), iIndex, &rcItem);
	posX = rcItem.right -5;
	posY = ((rcItem.bottom + rcItem.top) / 2);

return iIndex;
}

///////////////////////////////////////////////////////////////////////////////
// ListBoxFunktionen 
CMultipleListBoxWindow::CMultipleListBoxWindow (pDialogWindow pDW, ResID rsc)
	: OwnerDrawListBoxEx (pDW, rsc)
{
	LocControl() -> InitListboxExtents();
}

CMultipleListBoxWindow::~CMultipleListBoxWindow (void)
{
	LocControl() -> FreeListboxExtents();
}

int CMultipleListBoxWindow::GetSelectedItems (int iMaxItems, int *pItems)
{
	return ListBox_GetSelItems (GetHandle(), iMaxItems, pItems);
}

///////////////////////////////////////////////////////////////////////////////
//
CIdentSelData::CIdentSelData (long lIdent, LPCSTR pcKText, LPCSTR pcDataSrc)
{
	m_lIdent = lIdent;
	m_pText = new char [_MAX_PATH];
	if (m_pText && SUCCEEDED(ClassFromIdent (lIdent, m_pText, _MAX_PATH)))
	{
	char cbBuffer[_MAX_PATH];

		if (NULL != pcDataSrc)
			wsprintf (cbBuffer, "%s:%s (%s)", m_pText, pcKText, pcDataSrc);
		else
			wsprintf (cbBuffer, "%s:%s", m_pText, pcKText);
		strcpy (m_pText, cbBuffer);
	}

// Flags rücksetzen
	m_bfTypInfo = m_fTypInfo = 0;
	m_fSel = false;
	m_fwasSel = false;
	m_fReadAll = false;
}

CIdentSelData::~CIdentSelData (void)
{
	DELETE_OBJ (m_pText);
}

// Routinen für OwnerDrawListBox ----------------------------------------------
BOOL EXPORTTRIAS CIdentSelektion::DrawEntireItem (DrawItemEvt e)
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

	if (e.hasFocus()) 
		DrawFocusRect (hDC, (RECT *)&Rc);
	return TRUE;
}

BOOL EXPORTTRIAS CIdentSelektion::DrawItemFocus (DrawItemEvt e)
{
Rectangle Rc = e.ItemSize();			// aktuellen Bereich holen
HDC hDC = (HDC)e.Handle (API_CONTROL_HDC);		// DC holen

	DrawFocusRect (hDC, (RECT *)&Rc);
	return TRUE;
}

BOOL EXPORTTRIAS CIdentSelektion::DrawItemSelect (DrawItemEvt e)
{
Rectangle Rc = e.ItemSize();			// aktueller Bereich
HDC hDC = (HDC)e.Handle (API_CONTROL_HDC);		// DC holen
CIdentSelData *pISD = (CIdentSelData *)e.GetItemData();
char *pText = pISD -> FText();

	if (!pText) return FALSE;

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

	return TRUE;
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

BOOL EXPORTTRIAS CIdentSelektion::MeasureItem (MeasureItemEvt e)
{
TEXTMETRIC tm;
HWND hDlg = e.Handle (API_DLGWINDOW_HWND);
HDC hDC = GetDC (hDlg);

	GetTextMetrics (hDC, &tm);
	e.SetItemHeight (tm.tmHeight);
	ReleaseDC (hDlg, hDC);
	return TRUE;
}

BOOL EXPORTTRIAS CIdentSelektion::DeleteItem (DeleteItemEvt e)
{
CIdentSelData *pISD = (CIdentSelData *)e.GetItemData();

	TX_ASSERT(NULL != pISD);
	TX_ASSERT(pISD -> FText());

	m_SelBox.LocControl() -> RemoveExtentEntry (pISD -> FText());

	DELETE_OBJ (pISD);
	return TRUE;
}

void EXPORTTRIAS CMultipleListBoxWindow::FocusChange (FocusChangeEvt e)
{
	ControlWindow::FocusChange (e);
}

// Wrapper für Listbox-HorzExtend-Verwaltung
long CMultipleListBoxWindow::AddItem (CIdentSelData *pData, int iIndex)
{
	TX_ASSERT(NULL != pData);
	TX_ASSERT(NULL != pData -> FText());

	LocControl() -> AddExtentEntry (pData -> FText());
	return OwnerDrawListBoxEx::AddItem (pData, iIndex);
}

// Knöpfe richten -------------------------------------------------------------
void CIdentSelektion::AdjustOK (void)
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
			iLen = strlen (inBuff);
		}

		if ('\0' != m_actSight[0] && strcmp (m_actSight, inBuff))
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

	if (0 == iLen && -1 == iIndex)
		m_ActVisInfo.Disable();
	else
		m_ActVisInfo.Enable();

	if (fEnable) 
		m_RenameView.Enable();
	else {
		m_RenameView.SetChecked (false);
		m_RenameView.Disable();
	}

#if _TRiAS_VER < 0x0510
	if (0 == g_dwVer51)
		return;
#endif

// erstmal prüfen, ob überhaupt etwas auswählbar ist
	if (m_cbeConnFilters.GetCount() > 0) {
		m_cbApplyConnectFilter.Enable();
		if (m_cbApplyConnectFilter.isChecked())
			m_cbeConnFilters.Enable();
		else {
			m_cbeConnFilters.ChangeCurrentIndex(-1);
			m_cbeConnFilters.Disable();
		}
	}
	else {
		m_cbeConnFilters.Disable();
		m_cbApplyConnectFilter.SetChecked(FALSE);
		m_cbApplyConnectFilter.Disable();
	}
}

///////////////////////////////////////////////////////////////////////////////
// Connectionfilter verwalten
#define IMG_CONNECTFILTER	0

BOOL CIdentSelektion::EnumConnectionFilters(char *pName, BOOL, void *pData)
{
COMBOBOXEXITEM cbItem;

	memset(&cbItem, '\0', sizeof(COMBOBOXEXITEM));
	cbItem.mask = CBEIF_TEXT|CBEIF_IMAGE|CBEIF_SELECTEDIMAGE;
	cbItem.pszText = pName;
	cbItem.iImage = cbItem.iSelectedImage = IMG_CONNECTFILTER;

int iIndex = m_cbeConnFilters.InsertItem(&cbItem);

	if (-1 != iIndex && !strcmp(reinterpret_cast<char *>(pData), pName)) {
		m_cbeConnFilters.ChangeCurrentIndex(iIndex);
		m_cbApplyConnectFilter.SetChecked(TRUE);
	}
	return TRUE;
}

bool CIdentSelektion::InitConnectFilters(LPCSTR pcConnFilter)
{
#if _TRiAS_VER < 0x0510
	if (0 == g_dwVer51)
		return false;
#endif

// imagelists laden
Bitmap bmpIcons(IDB_CONNECTFILTER_DLG);
Bitmap bmpMask(IDB_CONNECTFILTER_DLG_MASK);

	if (!m_ilImages.CreateList(16, 16, ILC_COLOR|ILC_MASK, 1, 1) ||
		-1 == m_ilImages.Add(&bmpIcons, &bmpMask)) 
	{
		return false;
	} 
	else {
	CImageList *pIL = m_cbeConnFilters.SetImageList(&m_ilImages);

		if (NULL != pIL)
			delete pIL;
	}

// existierende Filternamen in ComboBox füllen	
CStdThunkImpl<CIdentSelektion, ENUMNOKEYPROC> 
	Thunk(this, &CIdentSelektion::EnumConnectionFilters);
ENUMNOKEY ENK;

	ENK.eFcn = Thunk.GetThunk();
	ENK.ePtr = (void *)pcConnFilter;
	DEX_EnumConnectionFilters(ENK);

	if (NULL != pcConnFilter)
		m_strConnFilter = pcConnFilter;
	return true;
}

bool CIdentSelektion::GetConnectionFilter(LPSTR pBuffer, int iLen)
{
	pBuffer[0] = '\0';
	if (-1 == m_cbeConnFilters.GetCurrentIndex()) 
		return false;

	return m_cbeConnFilters.GetCurrentString(pBuffer, iLen);
}


