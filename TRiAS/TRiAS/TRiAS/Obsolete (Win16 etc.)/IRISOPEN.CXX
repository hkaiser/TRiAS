// Code fuer OpenBox (Eroeffnen einer Datenbasis)
// File: IRISOPEN.CXX

#include "triaspre.hxx"

#include <dbd.h>
#include <dbd.hxx>
#include <dirisole.h>

#if defined(WIN32)
#include <fnamestr.h>
#include <registry.hxx>
#endif // WIN32

#include "pwdialog.hxx"
#include "coords.hxx"
#include "legdinfo.hxx"
#include "prlayout.hxx"
#include "legende.hxx"
#include "legwind.hxx"
#if defined(OLD_MASSTAB)
#include "masstab.hxx"
#endif // OLD_MASSTAB
#if defined(OLD_TOOLBOX)
#include "tools.hxx"
#endif // OLD_TOOLBOX
#include "opendb.hxx"
#include "overview.hxx"

#if !defined(WIN32)
#include "nomenkl.hxx"
#include "schrank.hxx"
#endif // WIN32

#include "triasres.h"

#define MAXOLDNUM	4

//long GetGeoDBVersion (void);
void ResetGeoDBVersion (void);
void ReadIniPathes (void);

extern Window *CurrActW;
extern CoordsDlg *pCoords;
extern CLegendeWindow *pLegende;
extern MasstabDlg *pMasstab;
extern HelpDisplay *IrisHD;
extern ToolWind *pToolBox;
extern TextRechercheDlg *pTextSearch;   // TextSuchfenster
extern COverView *pOverView;

#if !defined(WIN32)
extern NomenklaturDlg *pNomenkl;
extern SchrankSchnulli *pSchrank;
#endif // WIN32

extern short GCancelFlag;

extern char PbdDBDir[_MAX_PATH+1];
extern char cbDefaultDir[_MAX_PATH+1];	// StandardWurzelVerzeichnis der Projekte

extern short g_iTicks;
extern bool g_fPendingSave;
extern HINSTANCE hInstance;

// globale Flags -------------------------------------------------------------
#if !defined(NOPROJEKTION)
extern bool GeographicCFlag;    // geografische Koordinaten
extern bool WorldCFlag;         // Weltprojektion
#endif

extern bool inzFlag;            // aktuelle Datenbasis ist verschnitten
extern short CopyRightFlag;	// CopyrightSensitivity

// Enable-Fags für MenuPunkte -------------------------------------------------
extern bool CloseEFlag;         // Projekt schlieáen
extern bool EditHeaderEFlag;    // DB-Header editieren
extern bool DrawEFlag;          // Geometrie neu zeichnen
extern bool IdentSelEFlag;      // IdentifikatorSelektion
extern bool CoordsEFlag;        // KoordinatenAnzeige
extern bool CoordsCFlag;
extern bool MasstabCFlag;
extern bool ToolBoxCFlag;

extern bool LegendeCFlag;	// Legende eingeblendet
extern bool OverViewCFlag;	// Übersichtsfenster

extern bool DrawTextObjs;

#if !defined(WIN32)
extern bool Nomen25CFlag;       // Nomenklaturanzeige
extern bool Nomen50CFlag;
extern bool Nomen10CFlag;
extern bool SchrankCFlag;	// SchrankSchnulli
#endif // WIN32

extern bool g_fMenu;		// Menu's anzeigen

// Funktion, die DB eröffnet -------------------------------------------------
extern ErrCode MainInitPbd (GeoDB &, uint resID = 0, bool = false, long = -1L);
extern char *ReadResource (HINSTANCE hInstance, int ResID, DWORD &dwResSize);

char *GenerateFullPath (LPCSTR pDBName, bool fMakeSubDir = true);

ErrCode IrisWind :: OpenDB (char *DBName, char *UserName, char *PassWord, short gfMode) 
{
ErrCode RC;

// wenn Fenster Icone ist, dann hochholen
	if (!(gfMode & OM_HideWindow)) {	// nur wenn anzuzeigen ist
		if (isIconic()) 
			Show (Iconized);	// Anzeigen und hochholen
		else 
			ToTop();		// nur hochholen
	}

// Sensibilität gegenüber anderen Versionen setzen
	SetCopyrightFlag (CopyRightFlag);
	ResetGeoDBVersion();
	g_fPendingSave = false;

	if (m_pDBOs == NULL) return EC_NOMEMORY;

// evtl. vollen VerzeichnisPfad generieren (aus StandardVerzeichnis)
char *pFullDB = GenerateFullPath (DBName);
short iIndex = -1;
			
// neue DB eröffnen
	g_iTicks = 0;			// Reset AutoSave
	if ((iIndex = m_pDBOs -> FAddItem(false)) == -1) {	// neues DBObjekt erzeugen
		DELETE (pFullDB);
		return (ErrCode)db_error (EC_NOMEMORY, RC_OpenDB);
	}

DatenBasisObjekt &rDBO = DBO(iIndex);
GeoDB &rDB = rDBO.DB();
	
	rDB.SetDBName (pFullDB ? pFullDB : DBName);
	DELETE (pFullDB);		// Speicher freigeben
	rDBO.SetMarker (MARKER13);	// Default-PunktForm festlegen
	rDB.SetROMode (gfMode & OM_RO);

	RC = rDB.Open (UserName, PassWord);
	if (RC != EC_OKAY) {
		m_pDBOs -> FDelItem (iIndex);	// aus Baum herauslöschen
		return RC;
	}

// Testen, ob die Version der Datenbank von uns unterstützt wird
	if (GetGeoDBVersion() > LASTDBVERSION) {
		rDB.Close();			// wieder schließen
		m_pDBOs -> FDelItem (iIndex);	// aus Baum herauslöschen
		return (ErrCode)db_error (WC_BADDBVERSION, RC_OpenDB);
	}
	
// Bitmaps für Punktobjekte laden 
//	rDBO.LoadBitmapBars();	// in ReReadheader

// Fensterkopf modifizieren
//	ReReadCaption();	// wird später gemacht
	
// diese DB in Liste der vorhergehenden DB's merken
#if !defined(WIN32)
	LastDB ((char *)rDB.GetDBName(), UserName, 
		PassWord && *PassWord != '\0', gfMode & OM_RO);
	InitOldDBMenu (false, &IrisMenu, IRISMENUPOS);
	InitOldDBMenu (false, &StartMenu, STARTMENUPOS);
#else
	AddNewItem (m_pMRU, rDB.GetDBName(), gfMode & OM_RO);
	PlaceMenuMRUItem (m_pMRU, ::GetSubMenu(IrisMenu.Handle(), 0), IDM_EXIT);
#endif // WIN32

// System auf geöffnete DB einstellen
	rDBO.SetPaintFlag (PF_NOTDRAWED);
	rDBO.ReReadIdents();             // Identifikatoren aufsammeln

// Koordinatensystem setzen
	rDBO.ReScale(this);

// Menüpunkte aktivieren/deaktivieren
//      OpenEFlag = false;
	CloseEFlag = true;
	EditHeaderEFlag = true;
	DrawEFlag = true;
	IdentSelEFlag = true;
	CoordsEFlag = true;

// Projektionsfunktion setzen
	rDBO.SetPrjFcn (NULL, NULL);   // geografische Koord.
#if !defined(NOPROJEKTION)
	WorldCFlag = false;
	GeographicCFlag = true;
#endif
// DatenBasisObjekt Ausschnitt definieren
ObjContainer ocT = rDB.DBCont(true).InflateCont(10);

	rDBO.SetExtend (this, ocT, AspectRatio);

// DBVersion bestimmen, um Textobjekte richtig behandeln zu können
	DrawTextObjs = (GetGeoDBVersion() >= NEWDBVERSION);

	ReReadHeader (rDBO, rDB);	// GeoDBHeaderEinträge einlesen

// dieses DatenBasisObjekt als aktuelles aktivieren
	if (iIndex == 0 || gfMode & OM_ActivateDBO)
		m_pDBOs -> FActivateItem (iIndex);
		
// zugehörige PBD-DB initialisieren
	rDBO.InitPbd (PbdDBDir);

// interne MerkmalsCodes in PBD nachtragen
	MainInitPbd (rDB);

// ToolFenster neu bilden
	if (!pToolBox) pToolBox = new ToolWind (this);       

// ToolBox erst anzeigen, wenn alle ihr Werkzeug eingehängt haben
	if (pToolBox) {
		ToolBoxCFlag = true;            // Fenster ist angezeigt
		pToolBox -> Show ();
		pToolBox -> Update();
	}

// die Welt von diesem hervoragenden Ereignis in Kenntnis setzen
	DEXN_OpenProject (rDB.DBDesc());

// SightMenu initialisieren, StandardSicht einstellen, wenn gefordert
	if (rDBO.InitSightMenu (MainMenu(), !(gfMode & OM_NoStandard)))
		DrawMenuBar (Handle (API_WINDOW_HWND));

return EC_OKAY;
}

#if defined(WIN32)
ErrCode IrisWind :: OpenDB (LPSTORAGE pIStorage, short gfMode, LPCSTR pcName) 
{
ErrCode RC;

// wenn Fenster Icone ist, dann hochholen
	if (!(gfMode & OM_HideWindow)) {	// nur wenn anzuzeigen ist
		if (isIconic()) 
			Show (Zoomed);		// Anzeigen und hochholen
		else 
			ToTop();	// nur hochholen
	}

// Sensibilität gegenüber anderen Versionen setzen
	SetCopyrightFlag (CopyRightFlag);
	ResetGeoDBVersion();
	g_fPendingSave = false;

	if (m_pDBOs == NULL) return EC_NOMEMORY;

string strFullDB;

	if (NULL == pcName) {
	// evtl. vollen VerzeichnisPfad generieren (aus StandardVerzeichnis)
	STATSTG stg;

		if (FAILED(pIStorage -> Stat (&stg, STATFLAG_DEFAULT))) 
			return (ErrCode)db_error (EC_NOMEMORY, RC_OpenDB);

		strFullDB = AnsiString(stg.pwcsName);
		CoTaskMemFree (stg.pwcsName);
	} else
		strFullDB = pcName;

	if (StgIsStorageFile(WideString (strFullDB.c_str())) &&
	    !(gfMode & OM_DeleteOnClose))
	{	// Datei im FileSystem, aber nicht temporär
		strFullDB = GenerateFullPath (strFullDB.c_str());
	}

short iIndex = -1;

// neue DB eröffnen
	g_iTicks = 0;			// Reset AutoSave
	if ((iIndex = m_pDBOs -> FAddItem(false)) == -1)	// neues DBObjekt erzeugen
		return (ErrCode)db_error (EC_NOMEMORY, RC_OpenDB);

DatenBasisObjekt &rDBO = DBO(iIndex);
GeoDB &rDB = rDBO.DB();
	
	rDB.SetDBName ((LPSTR)strFullDB.c_str());
	rDBO.SetMarker (MARKER13);	// Default-PunktForm festlegen
	rDB.SetROMode (gfMode & OM_RO ? true : false);
	rDB.SetTempMode (gfMode & OM_DeleteOnClose ? true : false);

	DBASSERT (rDB.Open (pIStorage));

// Testen, ob die Version der Datenbank von uns unterstützt wird
	if (GetGeoDBVersion() > LASTDBVERSION) {
		rDB.Close();			// wieder schließen
		m_pDBOs -> FDelItem (iIndex);	// ausBaum herauslöschen
		return (ErrCode)db_error (WC_BADDBVERSION, RC_OpenDB);
	}
	
// Bitmaps für Punktobjekte laden 
//	rDBO.LoadBitmapBars();		// in ReReadHeader

// diese DB in Liste der vorhergehenden DB's merken
	if (!(gfMode & OM_DeleteOnClose) && rDB.GetDBName()) {
#if !defined(WIN32)
		LastDB ((char *)rDB.GetDBName(), TEXT(""), false, gfMode & OM_RO);
		InitOldDBMenu (false, &IrisMenu, IRISMENUPOS);
		InitOldDBMenu (false, &StartMenu, STARTMENUPOS);
#else
		AddNewItem (m_pMRU, rDB.GetDBName(), gfMode & OM_RO);
		PlaceMenuMRUItem (m_pMRU, ::GetSubMenu(IrisMenu.Handle(), 0), IDM_EXIT);
#endif // WIN32	
	}

// System auf geöffnete DB einstellen
	rDBO.SetPaintFlag (PF_NOTDRAWED);
	rDBO.ReReadIdents();             // Identifikatoren aufsammeln

// Koordinatensystem setzen
	rDBO.ReScale();

// Menüpunkte aktivieren/deaktivieren
	CloseEFlag = true;
	EditHeaderEFlag = true;
	DrawEFlag = true;
	IdentSelEFlag = true;
	CoordsEFlag = true;

// Projektionsfunktion setzen
	rDBO.SetPrjFcn (NULL, NULL);   // geografische Koord.
#if !defined(NOPROJEKTION)
	WorldCFlag = false;
	GeographicCFlag = true;
#endif
// DatenBasisObjekt Ausschnitt definieren
ObjContainer ocT = rDB.DBCont(true).InflateCont(10);

	rDBO.SetExtend (ocT, AspectRatio);

// zugehörige PBD-DB initialisieren
	rDBO.InitPbd (PbdDBDir);

// ToolFenster neu bilden
	if (!pToolBox) pToolBox = new ToolWind (this);       

// ToolBox erst anzeigen, wenn alle ihr Werkzeug eingehängt haben
	if (pToolBox) {
		ToolBoxCFlag = true;            // Fenster ist angezeigt
		pToolBox -> Show ();
		pToolBox -> Update();
	}

// interne MerkmalsCodes in PBD nachtragen
	MainInitPbd (rDB);

// DBVersion bestimmen, um Textobjekte richtig behandeln zu können
	DrawTextObjs = (GetGeoDBVersion() >= NEWDBVERSION);

	ReReadHeader (rDBO, rDB);	// GeoDBHeaderEinträge einlesen

// dieses DatenBasisObjekt als aktuelles aktivieren
	if (iIndex == 0 || gfMode & OM_ActivateDBO)
		m_pDBOs -> FActivateItem (iIndex);
		
// die Welt von diesem hervoragenden Ereignis in Kenntnis setzen
	DEXN_OpenProject (rDB.DBDesc());

// SightMenu initialisieren, StandardSicht einstellen, wenn gefordert
	if (rDBO.InitSightMenu (MainMenu(), !(gfMode & OM_NoStandard)))
		DrawMenuBar (Handle (API_WINDOW_HWND));

return EC_OKAY;
}
#endif // WIN32

// Diverse HeaderEinträge einlesen --------------------------------------------
void IrisWind :: ReReadHeader (DatenBasisObjekt &rDBO, GeoDB &rDB)
{
// DB auffordern, sich neu zu initialisieren
	rDB.ReReadHeader();

// Verschnitt der DB feststellen
	{
	HeaderEntry Inz (rDB, IDS_INZIDENZ);

		if (Inz.Status() != HE_INVALID)
			inzFlag = !strcmp (Inz.EntryText(), ResString (IDS_YES, 3));
		else
			inzFlag = true;         // default: verschnitten
	}

// Zahlenbasis der Idents holen
	{
	HeaderEntry IdBase (rDB, IDS_IDENTBASE);
	short sBase = (short)IdBase.EntryLong (10);

		if (sBase != 10 && sBase != 16) sBase = 10;
		rDBO.SetIdBase (sBase);
	}

// Zahlenbasis der MCodes holen (default: IdBase)
	{
	HeaderEntry MkBase (rDB, IDS_MCODEBASE);
	short sBase = (short)MkBase.EntryLong (10/*rDBO.GetIdBase()*/);

		if (sBase != 10 && sBase != 16) sBase = 10;
		rDBO.SetMkBase (sBase);
	}

// ScrollMode holen
	{
	HeaderEntry ScMode (rDB, IDS_SCROLLMODE);
	
		m_fFullRedrawOnScroll = (ScMode.EntryLong (0) != 0L);
	}

// Bitmaps für Punktobjekte laden 
	rDBO.LoadBitmapBars();

// HintergrundFarbe einlesen und setzen
	{
	HeaderEntry bkColor (rDB, IDS_BACKGROUNDCOLOR);
	Color C ((ColorVal)192, (ColorVal)192, (ColorVal)192);
	long cBkColor = bkColor.EntryLong ((DWORD &)C, 16);
	Brush *pB = new Brush ((Color &)cBkColor);

		rDBO.SetBkColor ((Color &)cBkColor);
		if (NULL != pB) {
			pB = ChangeBackground (pB);
			if (NULL != pB && pB != _IrisBGBrush)
				delete pB;
		}
	}
}

// eine der vorhergehenden DB's eröffnen
ErrCode IrisWind :: OpenOld (short uiMenuItem) 
{
CEierUhr Wait (this);
ErrCode RC;

// wenn bereits eine DB eröffnet ist, dann alte schließen
	if (m_pDBOs -> Count() && DBO().DB().isOpened()) {
		DBASSERT (CloseDB());
		DELETE (DRO);
	}

#if !defined(WIN32)
// alte DB eröffnen
register int i = uiMenuItem - IDM_OPENOLD1;
char *PassWord = NULL;
ProFile PF(ResString (IDS_PROFILE, 10));

// wenn PassWord gefordert wird, dann abfragen
	if (PF.GetOldPWDMode (i)) {
	PassWordDlg PWDlg (this, IDS_PWDFIRST);

		PWDlg.Show();
		PassWord = PWDlg.GetPassWord();
	}

// DB eröffnen, EierUhr einschalten
ErrCode EC = OpenDB (PF.GetOldDBName(i), PF.GetOldUserName(i), PassWord, 
		     PF.GetOldROMode(i) ? 
		     	OM_RO|OM_ActivateDBO : OM_Normal|OM_ActivateDBO);
#else
string strF (_MAX_PATH, default_size);
bool fRO = false;
ErrCode EC = EC_NOOPEN;

	if (GetMenuItem (m_pMRU, uiMenuItem, true, strF, fRO)) {
		strF.adjustlen();

	string strUser = get_name(strF);

		strlwr ((char *)strUser.c_str());
		EC = OpenDB ((char *)strF.c_str(), (char *)strUser.c_str(), NULL, 
						 fRO ? OM_RO|OM_ActivateDBO : OM_Normal|OM_ActivateDBO);
	} else
		MessageBeep (MB_ICONEXCLAMATION);

	if (EC_OKAY != EC) {
	// diesen Eintrag erstmal aus StartMenu rausnehmen
		DelMenuItem (m_pMRU, uiMenuItem, true);
		PlaceMenuMRUItem (m_pMRU, ::GetSubMenu(StartMenu.Handle(), 0), IDM_EXIT);
	}

#endif // !WIN32

return EC;
}

#if !defined(WIN32)
// DB in Liste der vorhergehenden DB's einspeichern
void IrisWind :: LastDB (char *DB, char *UN, bool PWDMode, bool ROMode) 
{
ProFile PF(ResString (IDS_PROFILE, 10));
char OldDBs[MAXOLDNUM-1][_MAX_PATH];    	// die letzten 3 DB-Namen
register int i, j;

// DB-Namen aus ProfileDatei einlesen
char toWriteDB[_MAX_PATH];

	wsprintf (toWriteDB, "%s,%s", DB, UN);
	for (i = 0, j = 0; i < MAXOLDNUM -1 && j < MAXOLDNUM; i++, j++) {
	// Eintrag einlesen
		PF.GetOldDBEntry (j, OldDBs[i], 140);            
		
	// Eintrag mit zu schreibender Info vergleichen
	char *cptr = strchr (OldDBs[i], ',');

		if (!cptr) continue;    // Fehler, falsches Trennzeichen
		cptr = strchr (cptr+1, ',');
		if (!cptr) continue;
		*cptr = '\0';           // 2. Komma ausblenden
		if (!strcmp (OldDBs[i], toWriteDB))
			i--;            // wenn gleich, Eintrag überspringen
		*cptr = ',';            // Komma wiederherstellen
	}
// neu Namen schreiben
	PF.SetOldDB (0, DB, UN, PWDMode, ROMode);
	
// alte Namen neu wegschreiben
	for (i = 1; i < MAXOLDNUM; i++)
		PF.SetOldDBEntry (i, OldDBs[i-1]);
}
#endif // !WIN32

#if !defined(WIN32)
void IrisWind :: InitOldDBMenu (bool Insert, pMenu pM, short Pos) 
{
ProFile PF(ResString (IDS_PROFILE, 10));
char MenuEntry[_MAX_PATH];
char *DBN;
char *UserN;
register int i;

// Alle evtl. Einträge aus dem Menu löschen
	if (!Insert) {
		for (i = 0; i < MAXOLDNUM; i++) 
			pM -> DeleteItem (IDM_OPENOLD1+i);
	
	HMENU hSubMenu = GetSubMenu (pM -> Handle (API_MENU_HMENU), 0);

		DeleteMenu (hSubMenu, Pos, MF_BYPOSITION);	// Separator rauslöschen
	}

// neue MenuEinträge bilden
	i = 0;
	while ((DBN = PF.GetOldDBName(i)) != NULL) { 
	// alle verfügbaren Einträge im Menu            
		UserN = PF.GetOldUserName (i);          // NutzerNamen
		
	// DB-namen aus Dateinamen extrahieren
	char DBNm[_MAX_FNAME];

		_splitpath (DBN, NULL, NULL, DBNm, NULL);
		wsprintf (MenuEntry, ResString(IDS_OLDOPENMENU, 40), i+1, DBNm, UserN);
		
	// neuen MenuEintrag setzen
		pM -> InsertItem (IDM_OPENOLD1+i, MenuEntry, IDM_EXIT);
		++i;                                    // nächster Eintrag
	}
	if (i)                  // wenn neue Einträge generiert worden sind
		pM -> InsertSeparator (IDM_EXIT);
}
#endif // !WIN32

// DatenBasis abschließen -----------------------------------------------------
ErrCode IrisWind :: CloseDB (bool fFlag, HPROJECT hDesc) 
{
	if (m_iDrawSem > 0) {		// zeichnet gerade: nicht schließen
	MessBox mb (ResString (IDS_SESSIONENDCAP, 40), 
		    ResString (IDS_PROJECTCLOSEPAINTING, 200),
		    this);

		mb.SetType (ExclamationIcon | OkayButton);
		mb.Show();
		return WC_RETURN;
	}

// Legende speichern
	DEX_SaveLegend();

ErrCode RC;
short iIndex = -1;
CEierUhr Wait (this);

	if (m_pDBOs == NULL) return EC_NOMEMORY;
	
	if (hDesc == 0) { 	// aktuelle GeoDB schließen
		iIndex = m_pDBOs -> FActiveDBO();
		if (iIndex == -1) // keine aktive DBO
			iIndex = 0;	// die erste nehmen
		if (short(m_pDBOs -> Count()) > iIndex && DBO().DB().isOpened())
			hDesc = DBO().DB().DBDesc();
		else
			return (ErrCode)db_error (EC_NOOPEN, RC_CloseDB);
	}
	iIndex = m_pDBOs -> FFindItem (hDesc);
	if (iIndex == -1)
		return (ErrCode)db_error (EC_NOOPEN, RC_CloseDB);

	if (!(short(m_pDBOs -> Count()) > iIndex && DBO(iIndex).DB().isOpened()))
		return (ErrCode)db_error (EC_NOOPEN, RC_CloseDB);
	
DatenBasisObjekt &rDBO = DBO(iIndex);
bool fCommit = true;

#if defined(WIN32)
	if (rDBO.DB().isDirty()) {
		if (rDBO.isComFile() && isVisible()) {	// kein Embedding
			if (rDBO.DB().GetROMode()) {		// 'echter' Schreibschutz
			// SaveAs machen, da nicht auf geöffnete Datei Commit'ed werden kann
			// %%TODO: MsgBox
				if (!SaveAsGeoDB())
					return WC_RETURN;		// abgebrochen
				fCommit = false;
			} else if (rDBO.DB().isCopy()) {
			// Datei ist Kopie der OriginalDatei
			// %%TODO: MsgBox
				if (!SaveAsGeoDB())
					return WC_RETURN;		// abgebrochen
				fCommit = false;
			} else {
			// Datei mit normalen Schreibrechten eröffnet
			string strText (512, default_size);

				wsprintf ((char *)strText.c_str(), ResString (IDS_SESSIONEND, 120), rDBO.DB().GetDBName());

			MessBox mb (ResString (IDS_SESSIONENDCAP, 40), 
					strText.c_str(), this);

				mb.SetType (QuestionMarkIcon | YesNoCancelButtons);
				switch (mb.Show()) {
				case YesReply:
					fCommit = true;		// auf jeden Fall speichern
					break;

				case NoReply:
					fCommit = false;	// nicht speichern
					break;

				case CancelReply:
					return WC_RETURN;	// abgebrochen
				}
			}
		} else
			fCommit = fFlag;
	} else // if (!rDBO.DB().GetTempMode())
		fCommit = false;	// nicht speichern

	if (rDBO.DB().GetTempMode()) {	// noch kein Dateiname
		if (fCommit) {
			if (!ExportAsGeoDB())
				return WC_RETURN;		// abgebrochen
			fCommit = false;		// aktuelle DB nicht speichern
		}
	}

#else
	fCommit = fFlag;
#endif // WIN32

// Rundruf zum letzten Speichern
	if (fCommit) {
	IStorage *pIStg = NULL;

		if (DEX_GetProjectStorage (pIStg)) {
			DEXN_SaveSameStorage (pIStg);
			DEXN_SaveCompleted (NULL);
			pIStg -> Release();
		}
	}

// nachfragen, ob wirklich geschlossen werden soll
	if (DEXN_CloseProject (hDesc) == true) 
	// jemand will, daß dieses Projekt nicht abgeschlossen wird
		return WC_RETURN;

// Synchronisation mit einer evtl. Zeichenoperation
	if (DEXI_isDrawing()) 
		GCancelFlag |= GCFAbort;		// Zeichnen abbrechen

	rDBO.toClose();						// soll geschlossen werden

// KoordinatenFenster ausblenden
	if (pCoords) {
		pCoords -> Hide();
		delete pCoords;
		pCoords = NULL;
		CoordsCFlag = false;
	}
	CoordsEFlag = false;

#if !defined(WIN32)
// Nomenklaturfenster ausblenden
	if (pNomenkl) {
		pNomenkl -> Hide();
		delete pNomenkl;
		pNomenkl = NULL;
		Nomen10CFlag = Nomen25CFlag = Nomen50CFlag = false;
	}

// SchrankSchnulli ausblenden
	if (pSchrank) {
		pSchrank -> Hide();
		delete pSchrank;
		pSchrank = NULL;
		SchrankCFlag = false;
	}
#endif // !WIN32

// Legende ausblenden
	if (pLegende) {
		pLegende -> Hide();
		delete pLegende;
		pLegende = NULL;
		LegendeCFlag = false;
	}

// Masstab ausblenden
	if (pMasstab) {
		pMasstab -> Hide();
		delete pMasstab;
		pMasstab = NULL;
		MasstabCFlag = false;
	}

// Werkzeugfenster löschen
	if (pToolBox && ToolBoxCFlag) {
		pToolBox -> Hide();
		ToolBoxCFlag = false;
//		delete pToolBox;
//		pToolBox = NULL;
	}
	if (pTextSearch) {
		pTextSearch -> Hide();  // nicht mehr anzeigen
		delete pTextSearch;     // Speicher freigeben
		pTextSearch = NULL;
	}
	if (pOverView) {
		pOverView -> Hide();
		OverViewCFlag = false;
		delete pOverView;
		pOverView = NULL;
	}

#if !defined(WIN32)
// OldDBMenu aktualisieren
	InitOldDBMenu (false, &IrisMenu, IRISMENUPOS);
	InitOldDBMenu (false, &StartMenu, STARTMENUPOS);
#endif // WIN32

	rDBO.DeleteAllSightItems (MainMenu());

// RechercheFenster freigeben
	if (ObjInfoListe.Count() > 0) 
		ObjInfoListe.EveryDelete();

// Bildschirm löschen, Menu/Accel richten
Brush *pB = ChangeBackground (_IrisBGBrush);

	if (NULL != pB && pB != _IrisBGBrush)
		delete pB;

// Rollbalken ausblenden
	if (m_pWHS) m_pWHS -> Hide();
	if (m_pWHS) m_pWHS -> SetRange (Range (0, 0));

	m_pWHS = EnableHScroll (false);
	m_kSX = 1;

	if (m_pWVS) m_pWVS -> Hide();
	if (m_pWVS) m_pWVS -> SetRange (Range (0, 0));

	m_pWVS = EnableVScroll (false);
	m_kSY = 1;

	CanvasErase ();
	InitMenues();

// FensterCaption wieder initialisieren
	SetCaption (ResString (IDS_CAPTION, 120));

// Notification absetzen, daß keine Sicht mehr aktiv ist
	DEXN_SightSelected (NULL);

	DELETE (rDBO.pCT())

// ObjektListe löschen
	rDBO.EveryDelete ();
	rDBO.SetPaintFlag (PF_INVALID); 

// PBD - Bäume freigeben
//	pbdDB.EveryDelete();	// wird jetzt in DBO().EveryDelete() erledigt
	
	DBASSERT (rDBO.CloseDB (fCommit));
	m_pDBOs -> FDelItem (iIndex);	// aus Baum herauslösen

	// DB geschlossen und ObjektListe leer

// MenuPunkte aktivieren/deaktivieren
	CloseEFlag = false;
	EditHeaderEFlag = false;
	DrawEFlag = false;
	IdentSelEFlag = false;

// ObjContainerStack rücksetzen
	while (actClip.Top().isValid())
		actClip.Pop();

// letzten Ident rücksetzen
	m_lLastIdent = -1L;

// VisInfoIgnoreTree freigeben
	CIdentifikator :: ReleaseIgnoreTree();

return EC_OKAY;
}


// Caption generieren ---------------------------------------------------------
bool GenerateStandardCaption (string &str, const char *pDBName, bool fFullHeader)
{
char *pDrive = new char [_MAX_DRIVE];
char *pPath= new char [_MAX_PATH];
char *pName = new char [_MAX_FNAME];
bool fResult = false;

	if (pDrive && pPath && pName) {
		if (fFullHeader) {
			str = ResString (IDS_SHORTCAPTION, 120).Addr();
			str += '[';
		}

		if (pDBName) {
			_splitpath (pDBName, pDrive, pPath, pName, NULL);
			str += pDrive;
			str += pPath;
			str += pName;
		} else 
			str = ResString (IDS_NOVIEWNAME, 30).Addr();

		if (fFullHeader) str += ']';
		fResult = true;
	}
	DELETE_VEC (pDrive);
	DELETE_VEC (pPath);
	DELETE_VEC (pName);

return fResult;
}

char *IrisWind :: GenerateCaptionText (char *pTemplate)
{
	if (pTemplate == NULL) return NULL;

char *pView = new char [_MAX_PATH];
char *pCaption = new char [_MAX_PATH];
char *pT = NULL;

	if (pView == NULL || pCaption == NULL) {
		DELETE_VEC (pView);
		return NULL;
	}

// %v durch SichtNamen ersetzen
	if ((pT = strstr(pTemplate, "%v")) != NULL) {
	// Sicht dazugenerieren
		DEX_GetActiveSight (pView);
		if (*pView == '\0') {
		// keine Sicht oder temporär
		ResString rsNoName (IDS_NOVIEWNAME, 30);

			strcpy (pView, rsNoName);
		}

	short iLen = pT-pTemplate;

		strncpy (pCaption, pTemplate, iLen);	// Anfang kopieren
		strcpy (&pCaption[iLen], pView);		// SichtNamen
		strcat (pCaption, pT+2);				// Rest kopieren
	} else
		strcpy (pCaption, pTemplate);
		
// %p durch Pfad und Dateinamen ersetzen
	if ((pT = strstr(pCaption, "%p")) != NULL) {
	string str (pCaption, pT-pCaption);

		GenerateStandardCaption (str, DBO().DB().GetDBName(), false);
		str += pT+2;		// Rest kopieren
		strcpy (pCaption, str.c_str());
	} 

	DELETE_VEC (pView);

return pCaption;
}

bool IrisWind :: ReReadCaption (void)
{
// als erstes an der aktuellen Sicht nachsehen, ob BeschreibungsInfo da ist
GeoDB &rDB = DBO().DB();
VIEWDESC VD;
string strText;

	VD.m_dwSize = sizeof(VIEWDESC);
	VD.m_pView = NULL;	// aktuelle Sicht verwenden
	VD.m_pDesc = new char [_MAX_PATH];
	VD.m_iLen = _MAX_PATH;
	
	if (VD.m_pDesc != NULL) {		// SichtBeschreibung
		if (DEX_GetViewDescription (VD)) {
			strText = VD.m_pDesc;
			delete [] VD.m_pDesc;
			goto labelShowCaption;
		} 
		delete [] VD.m_pDesc;
	} 

// ansonsten den normalen SuchPfad einhalten
	{
	HeaderEntry Caption (rDB, IDS_CAPTIONTEXT);

		if (Caption.Status() != HE_INVALID) {
		// Fensterkopftext im DB-Header definiert
		char *pT = GenerateCaptionText (Caption.EntryText());
			
			strText = pT ? pT : "";
			DELETE (pT);
		} else {
		// Fensterkopftext nicht definiert, Namen der DB in 
		// Fensterkopf eintragen
			if (!GenerateStandardCaption (strText, rDB.GetDBName(), true)) 
				return false;		// altes Caption beibehalten
		}
	}

labelShowCaption:

	if (rDB.GetROMode())		// Schreibschutz (echter)
		strText += ResString (IDS_READONLYPROJECT, 30);
	else if (rDB.isCopy())		// Projekt ist iene Kopie
		strText += ResString (IDS_PROJECTISCOPY, 30);
	
	if (rDB.isDirty())
		strText += " *";

	SetCaption (strText.c_str());
	
return true;
}                       


// Vollen GeoDBNamen erzeugen -------------------------------------------------
// Der volle GeoDBName wird erzeugt, in dem die im gegebenen DateiNamen fehlenden
// Bestandteile des vollen DateiNamens durch die Teile aus den StandardPfad
// (aus der TRIAS.INI) ergänzt werden. Wenn nur der Name des Projektes vorgegeben
// ist, so wird folgender Name erzeugt
//		StandardPfad\Projekt\Projekt.ris.
static char *GenerateFullPath (LPCSTR pDBName, bool fMakeSubDir)
{
	if (pDBName == NULL) return NULL;	// temporäre Datei erzeugen

char *pODrive = new char [_MAX_DRIVE];
char *pOPath= new char [_MAX_PATH];
char *pName = new char [_MAX_FNAME];
char *pExt = new char [_MAX_EXT];
char *pNew = new char [_MAX_PATH];
char *pDefDrive = new char [_MAX_DRIVE];
char *pDefPath= new char [_MAX_PATH];

	if (pNew && pODrive && pOPath && pExt) {
	ResString rsExt (IDS_RISEXT, 5);
	
		if ('\0' == cbDefaultDir[0])
			ReadIniPathes();

		_splitpath (pDBName, pODrive, pOPath, pName, pExt);
		_splitpath (cbDefaultDir, pDefDrive, pDefPath, NULL, NULL);
		if (fMakeSubDir && NULL != pDefPath && NULL != pName) 
			strcat (pDefPath, pName);
		_makepath (pNew, *pODrive ? pODrive : pDefDrive,
				 *pOPath ? pOPath : pDefPath,
				 pName, 
				 *pExt ? pExt : rsExt.Addr());
	}

// Speicher wieder freigeben
	DELETE (pODrive);
	DELETE (pDefDrive);
	DELETE (pOPath);
	DELETE (pDefPath);
	DELETE (pName);
	DELETE (pExt);
				 
return pNew;
}

// Neue Datenbasis erzeugen ---------------------------------------------------
int ShowCreateNewDBDialog (pWindow pW, string &strDBName, 
			   string &strUserName, string &strPWD)
{
	if ('\0' == cbDefaultDir[0]) ReadIniPathes();

string strInitDir = cbDefaultDir;
int iIndex = -1;

	{	// es dürfen nicht gleichzeitig 2 Dialoge aktiv sein
	CNewDBDlg ODlg (pW);
	
		ODlg.SetInitialDir (strInitDir.c_str());
	
	// Dialogfenster Anzeigen
		ODlg.AddFlags (OFN_OVERWRITEPROMPT);
#if defined(WIN32)
		if (IsWin40())
			ODlg.AddFlags (OFN_EXPLORER);
#endif // WIN32
		ODlg.Show();
	
	// Resultate verarbeiten
		if (!ODlg.Result ()) return -1;
	
	// DB neu generieren
	char *pT = NULL; 
		
		iIndex = ODlg.GetFilterIndex();

		strDBName.resize(_MAX_PATH);
		ODlg.GetFileSpec ((LPSTR)strDBName.c_str(), _MAX_PATH);
		strDBName.adjustlen();
		strUserName = (pT = ODlg.GetUserName()) ? pT : "";
		strPWD = (pT = ODlg.GetPassWord()) ? pT : "";
	}

return iIndex;
}

#if defined(WIN32)

bool IrisWind :: CreateNewGeoDB (void)
{
string strDBName = ResString (IDS_NONAME, 32).Addr();	// erstmal "keinen" Namen

// evtl. offene DB schließen
	if (m_pDBOs -> Count() && DBO().DB().isOpened()) {
		if (CloseDB() != EC_OKAY) 
			return false;	// Fehler oder warten
		DELETE (DRO);
	}

// EierUhr anzeigen
CEierUhr Wait (this);
LPSTORAGE pIStorage = NULL;

	if (!::CreateNewGeoDB (NULL, &pIStorage))	// temporär erzeugen
		return false;

// Strukturen für eröffnete GeoDb anlegen
ErrCode	EC = OpenDB (pIStorage, OM_Normal|OM_ActivateDBO|OM_DeleteOnClose,
					 strDBName.c_str());

	if (EC == EC_OKAY)
		DEXN_isCreatedProject(pIStorage);			// Projekt erzeugt
	
	pIStorage -> Release();
	if (EC != EC_OKAY) return false;

// alles ok, Nutzerinterface richten
	InitProjectMenu();

	ReReadCaption();	// Caption richten
	RePaint ();		// neue DB zeichnen

return true;
}

// lediglich GeoDB anlegen ----------------------------------------------------
bool CreateNewGeoDB (LPCSTR pFileName, LPSTORAGE *ppIStorage,
		     LPCSTR pUser, LPCSTR pPWD)
{
//	if (ppIStorage != NULL)
//		*ppIStorage = NULL;		// für alle Fälle 

CREATEDBEX cDB;
ErrCode EC = EC_OKAY;

	INITSTRUCT (cDB, CREATEDBEX);
	cDB.m_pName = (char *)pFileName;
	cDB.m_pUser = (pUser && strlen(pUser) > 0) ? (char *)pUser : NULL;
	cDB.m_pPassWd = (pPWD && strlen(pPWD) > 0) ? (char *)pPWD : NULL;

	if (ppIStorage) {
		cDB.m_pIStorage = *ppIStorage;
		if (cDB.m_pIStorage) cDB.m_pIStorage -> AddRef();

		cDB.m_iMode |= DBVCompFile;
		cDB.m_pClsID = &CLSID_DirisProject;

	ResString resClass (IDS_TRIASFULLNAME130, 30);

		cDB.m_pCFStr = resClass.Addr();
		EC = CreateNewDB ((CREATEDB *)&cDB, DBD050B);
	} else {
		cDB.m_iMode |= DBVNormal;
		EC = CreateNewDB ((CREATEDB *)&cDB, DBD050A);
	}

	if (EC != EC_OKAY) {
		if (cDB.m_pIStorage) 
			cDB.m_pIStorage -> Release();
		db_error (EC, RC_CreateNewGeoDB);
		return false;
	}

	if (ppIStorage != NULL) {
		if (NULL != *ppIStorage) 
			(*ppIStorage) -> Release();
		*ppIStorage = cDB.m_pIStorage;
	}

return true;
}

int ShowSaveAsDBDialog (pWindow pW, string &strDBName)
{
	if ('\0' == cbDefaultDir[0]) ReadIniPathes();

string strInitDir = cbDefaultDir;
int iIndex = -1;

	{	// es dürfen nicht gleichzeitig 2 Dialoge aktiv sein
	CSaveAsDBDlg ODlg (pW);
	
		ODlg.SetInitialDir (strInitDir.c_str());
		if (0 < strDBName.length()) {
		// Dateinamen voreinstellen
		string str = get_name (strDBName);

			str += get_ext (strDBName);
			ODlg.SetFileName (str.c_str());
		}

	// Dialogfenster Anzeigen
		ODlg.AddFlags (OFN_OVERWRITEPROMPT);
#if defined(WIN32)
		if (IsWin40())
			ODlg.AddFlags (OFN_EXPLORER);
#endif // WIN32
		ODlg.Show();
	
	// Resultate verarbeiten
		if (!ODlg.Result ()) return -1;
	
	// DB neu generieren
	char *pT = NULL; 
		
		iIndex = ODlg.GetFilterIndex();

		strDBName.resize(_MAX_PATH);
		ODlg.GetFileSpec ((LPSTR)strDBName.c_str(), _MAX_PATH);
		strDBName.adjustlen();
	}

return iIndex;
}

bool IrisWind :: ExportAsGeoDB (void)
{
string strDBName;
int iIndex = 0;		// FilterIndex 

// evtl. aktuellen Dateinamen voreinstellen
	if (!DBO().DB().GetTempMode())
		strDBName = DBO().DB().GetDBName();

// Namen erfragen 
	iIndex = ShowSaveAsDBDialog (this, strDBName);
	if (iIndex < 0)	return false;

CEierUhr Wait (this);

// wenn Dateiname identisch ist, dann lediglich speichern
	if (!DBO().DB().GetTempMode() && strDBName == DBO().DB().GetDBName()) 
	{
		DBO().PbdDB().Flush (false);
		return (EC_OKAY == DBO().DB().Flush (false));	// alles wegschreiben
	}

// unter neuem Namen speichern
	if (!DBO().ExportAsGeoDB (strDBName.c_str()))
		return false;

// in Menu eintragen
	AddNewItem (m_pMRU, strDBName.c_str(), false);
	PlaceMenuMRUItem (m_pMRU, ::GetSubMenu(IrisMenu.Handle(), 0), IDM_EXIT);

return true;
}

bool IrisWind :: SaveAsGeoDB (void)
{
string strDBName;
int iIndex = 0;		// FilterIndex 

// evtl. aktuellen Dateinamen voreinstellen
	if (!DBO().DB().GetTempMode())
		strDBName = DBO().DB().GetDBName();

// Namen erfragen 
	iIndex = ShowSaveAsDBDialog (this, strDBName);
	if (iIndex < 0)	return false;

CEierUhr Wait (this);

// wenn Dateiname identisch ist, dann lediglich speichern
	if (!DBO().DB().GetTempMode() && strDBName == DBO().DB().GetDBName()) 
	{
		DBO().PbdDB().Flush (false);
		return (EC_OKAY == DBO().DB().Flush (false));	// alles wegschreiben
	}

// unter neuem Namen speichern
	if (!DBO().SaveAsGeoDB (strDBName.c_str())) 
		return false;

// in Menu eintragen
	AddNewItem (m_pMRU, strDBName.c_str(), false);
	PlaceMenuMRUItem (m_pMRU, ::GetSubMenu(IrisMenu.Handle(), 0), IDM_EXIT);

	ReReadCaption();	// Caption richten

return true;
}

bool IrisWind :: SaveGeoDB (void)
{
CEierUhr Wait (this);
bool fCommit = true;

#if defined(WIN32)
	if (DBO().DB().GetROMode()) {		// 'echter' Schreibschutz
	// SaveAs machen, da nicht auf geöffnete Datei Commit'ed werden kann
	// %%TODO: MsgBox: 'Dieses Projekt ist schreibgeschützt ...
		if (!SaveAsGeoDB())
			return WC_RETURN;		// abgebrochen
		fCommit = false;
	} else if (DBO().DB().isCopy()) {
	// Datei ist Kopie der OriginalDatei
	// %%TODO: MsgBox: 'Dieses Projekt wird gerade von einem anderen Nutzer bearbeitet ...
	//			 oder: 'Das Projekt wurde in einer anderen TRiAS-Arbeitssitzung bearbeitet ...
		if (!SaveAsGeoDB())
			return WC_RETURN;		// abgebrochen
		fCommit = false;
	}
#endif // WIN32

	if (DBO().PbdDB().isOpened())
		DBO().PbdDB().Flush (fCommit);

ErrCode EC = DBO().DB().Flush (fCommit);

#if defined(WIN32)
	if (EC_OKAY == EC) {	// alles wegschreiben
	IStorage *pIStg = NULL;

		if (DBO().DB().GetProjectStorage(&pIStg)) {
			DEXN_SaveSameStorage (pIStg);
			DEXN_SaveCompleted (NULL);

			if (DBO().DB().isDirty()) {		// noch mal speichern
				if (fCommit) {
				HRESULT hr = pIStg -> Commit (STGC_DEFAULT);

					if (FAILED(hr) && (STG_E_MEDIUMFULL == GetScode(hr)))
						db_error (EC_NOSPACE, RC_CloseDB, DBO().DB().GetDBName());
				}
				DEX_SetDirtyGeoDB (false);
			}

			pIStg -> Release();
		}
	}
#endif // WIN32

return (EC_OKAY == EC);
}

#else // WIN32

bool IrisWind :: CreateNewGeoDB (void)
{
string strDBName;
string strUserName;
string strPWD;
int iIndex = 0;		// FilterIndex 

// 1. Namen erfragen 
	iIndex = ShowCreateNewDBDialog (this, strDBName, strUserName, strPWD);
	if (iIndex < 0)	return false;

// evtl. offene DB schließen
	if (m_pDBOs -> Count() && DBO().DB().isOpened()) {
		if (CloseDB() != EC_OKAY) 
			return false;	// Fehler oder warten
		DELETE (DRO);
	}

// EierUhr anzeigen
CEierUhr Wait (this);

	if (!::CreateNewGeoDB (strDBName.c_str(), strUserName.c_str(), 
			       strPWD.c_str(), iIndex == 1))
		return false;

// neue GeoDB eröffnen
char cbBuffer[_MAX_PATH+1];

	if (strUserName.length() == 0) {
	// StandardNutzer generieren
		_splitpath (strDBName.c_str(), NULL, NULL, cbBuffer, NULL);
		strlwr (cbBuffer);
		strUserName = cbBuffer;
	}

// neu anglegete GeoDB eröffnen
ErrCode	EC = OpenDB ((char *)strDBName.c_str(), (char *)strUserName.c_str(), 
		     strPWD.length() > 0 ? (char *)strPWD.c_str() : NULL, 
		     OM_Normal|OM_ActivateDBO);
	if (EC != EC_OKAY) return false;

// alles ok, Nutzerinterface richten
	if (g_fMenu) {
		ChangeMenu (&IrisMenu);
		ChangeAccel (&IrisAcc);
	}

// neue DB zeichnen
	RePaint ();

return true;
}

// lediglich GeoDB anlegen ----------------------------------------------------
bool CreateNewGeoDB (LPCSTR pFileName, LPCSTR pUser, LPCSTR pPWD, bool fNew)
{
CREATEDB cDB;

	INITSTRUCT (cDB, CREATEDB);
	cDB.m_pName = (char *)pFileName;
	cDB.m_pUser = (pUser && strlen(pUser) > 0) ? (char *)pUser : NULL;
	cDB.m_pPassWd = (pPWD && strlen(pPWD) > 0) ? (char *)pPWD : NULL;

	if (!fNew) cDB.m_iMode |= DBVNormal;
	else	   cDB.m_iMode |= DBVCompFile;
		
ErrCode EC = CreateNewDB ((CREATEDB *)&cDB, fNew ? DBD050B : DBD050A);

	if (EC != EC_OKAY) {
		db_error (EC, RC_CreateNewGeoDB);
		return false;
	}

return true;
}

// Anlegen einer neuen Datenbasis ---------------------------------------------
/* ----------------------------------------------------------------------------
ErrCode CreateNewDB (CREATEDB *pCDB, unsigned short iRes)
{
DWORD dwResSize;
LPBYTE lpRes = (LPBYTE)ReadResource (hInstance, iRes, dwResSize);
ErrCode EC = EC_NOMEMORY;
char *pFullDB = GenerateFullPath (pCDB -> m_pName);
CDBDict *pDBDict = NULL;

	switch (pCDB -> m_iMode & DBVFlags) {
	default:
	case DBVNormal:
		{
			pDBDict = CDBDictDOSFiles :: CreateInstance (lpRes);
			if (pDBDict == NULL) break;
			EC = pDBDict -> CreateDB (
				pFullDB, pCDB -> m_pUser, pCDB -> m_pPassWd, fPbd);
		}
		break;
		
	case DBVCompFile:
		pDBDict = CDBDictCompoundFile :: CreateInstance (lpRes);
		if (pDBDict == NULL) break;
		EC = pDBDict -> CreateDB (pFullDB, pCDB -> m_pUser, pCDB -> m_pPassWd, fPbd);
		break;
	}	
		
	DELETE (pFullDB);				 
	DELETE (lpRes);
	DELETE (pDBDict);

return EC;
}
---------------------------------------------------------------------------- */

bool IrisWind :: SaveGeoDB (void)
{
CEierUhr Wait (this);

	DBO().PbdDB().Flush();

return EC_OKAY == DBO().DB().Flush();
}

#endif // WIN32

// Anlegen einer neuen Datenbasis ---------------------------------------------
ErrCode CreateNewDB (CREATEDB *pCDB, unsigned short iRes)
{
DWORD dwResSize;
LPBYTE lpRes = (LPBYTE)ReadResource (hInstance, iRes, dwResSize);
ErrCode EC = EC_NOMEMORY;
char *pFullDB;
CDBDict *pDBDict = NULL;

	switch (pCDB -> m_iMode & DBVFlags) {
	default:
	case DBVNormal:
		{
			pFullDB = GenerateFullPath (pCDB -> m_pName);
			pDBDict = CDBDictDOSFiles :: CreateInstance (lpRes);
			if (pDBDict == NULL) break;
			EC = pDBDict -> CreateDB (
				pFullDB, pCDB -> m_pUser, pCDB -> m_pPassWd);
		}
		break;
		
	case DBVCompFile:
		if (pCDB -> dwSize == sizeof(CREATEDB)) {
			pFullDB = GenerateFullPath (pCDB -> m_pName);
			pDBDict = CDBDictCompoundFile :: CreateInstance (lpRes);
			if (pDBDict == NULL) break;
			EC = pDBDict -> CreateDB (
				pFullDB, pCDB -> m_pUser, pCDB -> m_pPassWd);
		} else {	// neue Variante
		CDBDictCompoundFile *pDBCDict = CDBDictCompoundFile :: CreateInstance (lpRes);

			if (pDBCDict == NULL) break;
			pDBDict = pDBCDict;		// für's freigeben

		CREATEDBEX *pCDBEx = (CREATEDBEX *)pCDB;

			pFullDB = GenerateFullPath (pCDB -> m_pName, false);
			EC = pDBCDict -> CreateDBEx (
				pFullDB, pCDB -> m_pUser, pCDB -> m_pPassWd,
				&pCDBEx -> m_pIStorage, pCDBEx -> m_pClsID,
				pCDBEx -> m_pCFStr);
		}
		break;
	}	
		
	DELETE (pFullDB);				 
	DELETE (lpRes);
	DELETE (pDBDict);

return EC;
}


