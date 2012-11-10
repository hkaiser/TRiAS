// Code fuer OpenBox (Eroeffnen einer Datenbasis)
// File: IRISOPN2.CXX

#include "triaspre.hxx"

#include <dbd.h>
#include <dbd.hxx>
#include <dirisole.h>

#include <fnamestr.h>
#include <registry.hxx>

#include "extmain3.hxx"
//#include "pwdialog.hxx"
#if defined(OLD_COORDS)
#include "coords.hxx"
#endif // OLD_COORDS
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

#include "triasres.h"
#include "strings.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

void ResetGeoDBVersion (void);
void ReadIniPathes (void);
bool IsLegalRegisteredVersion (Window *pW);

extern CLegendeWindow *pLegende;
extern HelpDisplay *IrisHD;

extern int g_iActTool;
extern short g_iHideFlags;	// was soll ausgeblendet werden

extern COverView *pOverView;

extern short GCancelFlag;

extern char PbdDBDir[_MAX_PATH+1];
extern char cbDefaultDir[_MAX_PATH+1];	// StandardWurzelVerzeichnis der Projekte

extern short g_iTicks;
extern bool g_fPendingSave;
extern bool g_fPendingReReadCaption;
extern HINSTANCE hInstance;

// globale Flags -------------------------------------------------------------
#if !defined(NOPROJEKTION)
extern bool GeographicCFlag;    // geografische Koordinaten
extern bool WorldCFlag;         // Weltprojektion
#endif

extern bool inzFlag;            // aktuelle Datenbasis ist verschnitten
extern short CopyRightFlag;		// CopyrightSensitivity

// Enable-Fags für MenuPunkte -------------------------------------------------
extern bool CloseEFlag;         // Projekt schlieáen
extern bool EditHeaderEFlag;    // DB-Header editieren
extern bool DrawEFlag;          // Geometrie neu zeichnen
extern bool IdentSelEFlag;      // IdentifikatorSelektion
#if defined(OLD_COORDS)
extern bool CoordsEFlag;        // KoordinatenAnzeige
extern bool CoordsCFlag;
#endif // OLD_COORDS
#if defined(OLD_MASSTAB)
extern bool MasstabCFlag;
#endif // OLD_MASSTAB

extern bool LegendeCFlag;		// Legende eingeblendet
extern bool OverViewCFlag;		// Übersichtsfenster

extern bool DrawTextObjs;
extern bool g_fMenu;		// Menu's anzeigen

// Funktion, die DB eröffnet -------------------------------------------------
extern ErrCode MainInitPbd (GeoDB &, uint resID = 0, bool = false, long = -1L);
extern char *ReadResource (HINSTANCE hInstance, int ResID, DWORD &dwResSize);

char *GenerateFullPath (LPCSTR pDBName, bool fMakeSubDir = true);

ErrCode IrisWind::OpenDB (
	LPCSTR DBName, LPCSTR UserName, LPCSTR PassWord, short gfMode, DWORD dwMode) 
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

	rDBO.isOpening (true);
	rDBO.SetMarker (MARKER13);	// Default-PunktForm festlegen

GeoDB &rDB = rDBO.DB();
	
	rDB.SetDBName (pFullDB ? (char *)pFullDB : (char *)DBName);
	rDB.SetROMode (gfMode & OM_RO);
	DELETE (pFullDB);		// Speicher freigeben

	RC = rDB.Open ((char *)UserName, (char *)PassWord, dwMode);
	if (RC != EC_OKAY) {
		m_pDBOs -> FDelItem (iIndex);	// aus Baum herauslöschen
		return RC;
	}

// Testen, ob die Version der Datenbank von uns unterstützt wird
	if (GetGeoDBVersion (&rDB) > LASTDBVERSION) {
		rDB.Close();					// wieder schließen
		m_pDBOs -> FDelItem (iIndex);	// aus Baum herauslöschen
		return (ErrCode)db_error (WC_BADDBVERSION, RC_OpenDB);
	}
	
// diese DB in Liste der vorhergehenden DB's merken
ExtDirisWindow *pFrame = GetFrame();

	if (NULL != pFrame)
		pFrame -> AddNewItem (false, rDB.GetDBName(), gfMode & OM_RO);

// System auf geöffnete DB einstellen
	rDBO.AttachViewWindow (this);
	rDBO.SetPaintFlag (PF_NOTDRAWED);
	rDBO.ReReadIdents();             // Identifikatoren aufsammeln

// Koordinatensystem setzen
	rDBO.ReScale (this);

// Menüpunkte aktivieren/deaktivieren
//      OpenEFlag = false;
	CloseEFlag = true;
	EditHeaderEFlag = true;
	DrawEFlag = true;
	IdentSelEFlag = true;
#if defined(OLD_COORDS)
	CoordsEFlag = true;
#endif // OLD_COORDS

// Projektionsfunktion setzen
	rDBO.SetPrjFcn (NULL, NULL);   // geografische Koord.
#if !defined(NOPROJEKTION)
	WorldCFlag = false;
	GeographicCFlag = true;
#endif
// DatenBasisObjekt Ausschnitt definieren
ObjContainer ocT = rDB.DBCont(true).InflateCont(10);

	rDBO.SetExtend (this, ocT, AspectRatio);

// zugehörige PBD-DB initialisieren
	rDBO.InitPbd (PbdDBDir);

// DBVersion bestimmen, um Textobjekte richtig behandeln zu können
	MainInitPbd (rDB);
	DrawTextObjs = (GetGeoDBVersion (&rDB) >= NEWDBVERSION);

// interne MerkmalsCodes in PBD nachtragen
	ReReadHeader (rDBO, rDB);	// GeoDBHeaderEinträge einlesen (_nach_ MainInitPbd)

// dieses DatenBasisObjekt als aktuelles aktivieren
	if (iIndex == 0 || gfMode & OM_ActivateDBO)
		m_pDBOs -> FActivateItem (iIndex);
		
// ToolFenster neu bilden
#if defined(OLD_TOOLBOX)
	if (!pToolBox) pToolBox = new ToolWind (this);       

// ToolBox erst anzeigen, wenn alle ihr Werkzeug eingehängt haben
	if (pToolBox) {
		ToolBoxCFlag = true;            // Fenster ist angezeigt
		pToolBox -> Show ();
		pToolBox -> Update();
	}
#endif // OLD_TOOLBOX

// SightMenu initialisieren, StandardSicht einstellen, wenn gefordert
	if (pFrame && rDBO.InitSightMenu (pFrame -> MainMenu(), !(gfMode & OM_NoStandard)))
		DrawMenuBar (pFrame -> Handle (API_WINDOW_HWND));

// die Welt von diesem hervoragenden Ereignis in Kenntnis setzen
	rDBO.isOpening(false);
	DEXN_OpenProject (rDB.DBDesc());
	App::Exec(ExecIdleOnly);

return EC_OKAY;
}

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

	rDBO.isOpening (true);
	rDBO.SetMarker (MARKER13);	// Default-PunktForm festlegen

GeoDB &rDB = rDBO.DB();
	
	rDB.SetDBName ((LPSTR)strFullDB.c_str());
	rDB.SetROMode (gfMode & OM_RO ? true : false);
	rDB.SetTempMode (gfMode & OM_DeleteOnClose ? true : false);
	DBASSERT (rDB.Open (pIStorage));

// Testen, ob die Version der Datenbank von uns unterstützt wird
	if (GetGeoDBVersion (&rDB) > LASTDBVERSION) {
		rDB.Close();			// wieder schließen
		m_pDBOs -> FDelItem (iIndex);	// ausBaum herauslöschen
		return (ErrCode)db_error (WC_BADDBVERSION, RC_OpenDB);
	}
	
// Bitmaps für Punktobjekte laden 
//	rDBO.LoadBitmapBars();		// in ReReadHeader

// diese DB in Liste der vorhergehenden DB's merken
ExtDirisWindow *pFrame = GetFrame();

	if (!(gfMode & OM_DeleteOnClose) && rDB.GetDBName()) {
		if (NULL != pFrame)
			pFrame -> AddNewItem (false, rDB.GetDBName(), gfMode & OM_RO);
	}

// System auf geöffnete DB einstellen
	rDBO.AttachViewWindow (this);
	rDBO.SetPaintFlag (PF_NOTDRAWED);
	rDBO.ReReadIdents();             // Identifikatoren aufsammeln

// Koordinatensystem setzen
	rDBO.ReScale (this);

// Menüpunkte aktivieren/deaktivieren
	CloseEFlag = true;
	EditHeaderEFlag = true;
	DrawEFlag = true;
	IdentSelEFlag = true;
#if defined(OLD_COORDS)
	CoordsEFlag = true;
#endif // OLD_COORDS

// Projektionsfunktion setzen
	rDBO.SetPrjFcn (NULL, NULL);   // geografische Koord.
#if !defined(NOPROJEKTION)
	WorldCFlag = false;
	GeographicCFlag = true;
#endif
// DatenBasisObjekt Ausschnitt definieren
ObjContainer ocT = rDB.DBCont(true).InflateCont(10);

	rDBO.SetExtend (this, ocT, AspectRatio);

// zugehörige PBD-DB initialisieren
	rDBO.InitPbd (PbdDBDir);

#if defined(OLD_TOOLBOX)
// ToolFenster neu bilden
	if (!pToolBox) pToolBox = new ToolWind (this);       

// ToolBox erst anzeigen, wenn alle ihr Werkzeug eingehängt haben
	if (pToolBox) {
		ToolBoxCFlag = true;            // Fenster ist angezeigt
		pToolBox -> Show ();
		pToolBox -> Update();
	}
#endif // OLD_TOOLBOX

// interne MerkmalsCodes in PBD nachtragen
	MainInitPbd (rDB);

// DBVersion bestimmen, um Textobjekte richtig behandeln zu können
	DrawTextObjs = (GetGeoDBVersion (&rDB) >= NEWDBVERSION);
	ReReadHeader (rDBO, rDB);	// GeoDBHeaderEinträge einlesen

// dieses DatenBasisObjekt als aktuelles aktivieren
	if (iIndex == 0 || gfMode & OM_ActivateDBO)
		m_pDBOs -> FActivateItem (iIndex);

// SightMenu initialisieren, StandardSicht einstellen, wenn gefordert
	if (pFrame && rDBO.InitSightMenu (pFrame -> MainMenu(), !(gfMode & OM_NoStandard)))
		DrawMenuBar (pFrame -> Handle (API_WINDOW_HWND));

// die Welt von diesem hervoragenden Ereignis in Kenntnis setzen
	rDBO.isOpening(false);
	DEXN_OpenProject (rDB.DBDesc());
	App::Exec(ExecIdleOnly);

return EC_OKAY;
}

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

IStorage *pIStg = NULL;
bool fStorage = false;

	if (rDB.GetProjectStorage (&pIStg)) {
		pIStg -> Release();
		fStorage = true;
	}

// Zahlenbasis der Idents holen
	{
	HeaderEntry IdBase (rDB, IDS_IDENTBASE);
	short sBase = (short)IdBase.EntryLong (fStorage ? 16 : 10);

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

#if defined(ENABLE_WIN32S_CODE)
		if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
		{
		CCurrentUser resBkColor (g_cbRegConfig);
		DWORD dwColor = 0x00C0C0C0L;

			resBkColor.GetDWORD ("BackGroundColor", dwColor);
			C = (Color &)dwColor;
		} 

	long cBkColor = bkColor.EntryLong ((DWORD &)C, 16);
	Brush *pB = new Brush ((Color &)cBkColor);

		rDBO.SetBkColor ((Color &)cBkColor);
		if (NULL != pB) {
			pB = ChangeBackground (pB);
			if (NULL != pB && pB != _IrisBGBrush)
				delete pB;
		}
	}

// Positionierung von Textobjekten (default: untere Kante)
	{
	HeaderEntry PosTxt (rDB, IDS_POSTEXTATBASELINE);
	
		DBO().PosTextAtBaseLine(PosTxt.EntryLong(0) ? true : false);
	}

// HideFlags/ShowObjProp einlesen
	{
	CCurrentUser regCfg (g_cbRegConfig);
	DWORD dwData = DWORD(ROSortObjNr|ROHideIdent);

		regCfg.GetDWORD (g_cbHideFlags, dwData);

	HeaderEntry HideFlags (rDB, g_cbHideFlags);

		g_iHideFlags = (short)HideFlags.EntryLong (dwData);
	
	char cbBuffer[64];
	DWORD dwLen = sizeof(cbBuffer);

		regCfg.GetSubSZ (g_cbShowObjProp, cbBuffer, dwLen);

	HeaderEntry ShowOP (rDB, g_cbShowObjProp);

		if (NULL != ShowOP.EntryText())
			strcpy (cbBuffer, ShowOP.EntryText());

		DEX_SetActObjPropName (cbBuffer);
	}

// 16Bit Kompatibilität gewährleisten ? (OKS <--> Ident)
	{
	HeaderEntry Comp16 (rDB, IDS_COMPATIBILITY_16BIT);
	
		DBO().Compatibility(Comp16.EntryLong(0) ? true : false);
	}
}

// diverse Headereinträge wegscheiben
bool DatenBasisObjekt::SaveHeader (void)
{
// HideFlags/ShowObjProp wegschreiben
char cbBuffer[64];
GeoDB &rDB = DB();

	{
	HeaderEntry HideFlags (rDB, g_cbHideFlags);

		ltoa (g_iHideFlags, cbBuffer, 10);
		HideFlags.SetEntryText (cbBuffer);
		HideFlags.WriteBack();
	}
	{
	HeaderEntry ShowOP (rDB, g_cbShowObjProp);

		if (DEX_GetActObjPropName (cbBuffer)) {
			ShowOP.SetEntryText (cbBuffer);
			ShowOP.WriteBack();
		}
	}
	return true;
}

// Aktuelles Dokument schließen -----------------------------------------------
bool IrisWind :: CloseDocument (void)
{
	if (m_pDBOs -> Count() && DBO().DB().isOpened()) {
	bool fCommit = true;

		if (EC_OKAY != AskUserToClose (fCommit))
			return false;
		if (EC_OKAY != CloseDB (fCommit))
			return false;
		DELETE(DRO);
	}

return true;
}

///////////////////////////////////////////////////////////////////////////////
// Für diverse Fälle nochmal rückfragen ---------------------------------------
bool AskToSaveNormal (Window *pW, LPCSTR pcName, bool &rfCommit)
{
StdMessBoxReply rgReply = VMessageBox (pW, 
		FakeTRiASName (IDS_SESSIONENDCAP, g_cbTRiAS).c_str(), 
		QuestionMarkIcon|YesNoCancelButtons, IDS_SESSIONEND, pcName);

	switch (rgReply) {
	case YesReply:
		rfCommit = true;	// auf jeden Fall speichern
		break;

	case NoReply:
		rfCommit = false;	// nicht speichern
		break;

	case CancelReply:
		return false;		// abgebrochen
	}

return true;		// ok schließen
}

// Fragen, ob der Originalname der Datei verwendet werden soll ----------------
bool AskToSaveDirectly (Window *pW, LPCSTR pcName, bool &rfNewName)
{
StdMessBoxReply rgReply = VMessageBox (pW, 
		FakeTRiASName (IDS_SAVEPROJECTCAP, g_cbTRiAS).c_str(),
		QuestionMarkIcon|YesNoCancelButtons, IDS_CHANGEDBYOTHERS, pcName, g_cbTRiAS);

	switch (rgReply) {
	case YesReply:
		rfNewName = false;	// auf jeden Fall unter OriginalNamen speichern
		break;

	case NoReply:
		rfNewName = true;	// unter neuem Namen Speichern
		break;

	case CancelReply:
		rfNewName = true;
		return false;		// abgebrochen
	}

return true;
}

// mitteilen, daß die zu speichernde Datei gerade von einem anderen genutzt wird
void TellThatCannotSaveDirectly (Window *pW, LPCSTR pcName, UINT resID)
{
	VMessageBox (pW, 
			FakeTRiASName (IDS_SAVEPROJECTCAP, g_cbTRiAS).c_str(),
			ExclamationIcon|OkayButton, resID, pcName);
}

ErrCode CantCloseWhenDrawing (Window *pW)
{
	VMessageBox (pW, 
		FakeTRiASName (IDS_SESSIONENDCAP, g_cbTRiAS).c_str(),
		ExclamationIcon|OkayButton, IDS_PROJECTCLOSEPAINTING, g_cbTRiAS);
	return WC_RETURN;
}

// Testen, ob die Datei jetzt wieder beschreibbar ist -------------------------
bool IsNowWriteAble (LPCSTR pcName)
{
IStorage *pIStg = NULL;
HRESULT hr = StgOpenStorage (WideString(pcName), NULL, 
							 STGM_TRANSACTED|STGM_READWRITE, 0, 0, &pIStg);

	if (SUCCEEDED(hr)) {
		pIStg -> Release();
		return true;
	}

return false;
}

// Den Fall abfragen und behandeln, wenn das Projekt schreibgeschützt ist.
ErrCode IrisWind :: HandleSaveRO (LPCSTR pcName, bool &rfCommit, bool fSave)
{
// Im SaveModus muß rfCommit auf true gesetzt sein
	TX_ASSERT(!fSave || rfCommit);

// erstmal fragen, ob überhaupt gespeichert werden soll
	if (!fSave && !AskToSaveNormal (this, pcName, rfCommit))
		return WC_RETURN;
		
	if (rfCommit) {
		TellThatCannotSaveDirectly (this, pcName, IDS_ISREADONLY);

	ResString resCopy (IDS_PROJECTISCOPY, 32);

		if (!SaveAsGeoDB (resCopy))
			return WC_RETURN;		// abgebrochen
		rfCommit = false;
	}

return EC_OKAY;
}

// Den Fall abfragen und behandeln, wenn das Projekt eine Kopie des Originales 
// ist. Datei kann das Original noch im anderen TRiAS offen sein, dann erfolgt 
// ein normales SaveAs. Ist das Original schon wieder geschossen, dann wird 
// nochmal gefragt, ob der OriginalName weiterverwendet werden soll und
// dann entsprechend gehandlet.
ErrCode IrisWind :: HandleSaveCopy (LPCSTR pcName, bool &rfCommit, bool fSave)
{
// Im SaveModus muß rfCommit auf true gesetzt sein
	TX_ASSERT(!fSave || rfCommit);

// erstmal fragen, ob überhaupt gespeichert werden soll
	if (!fSave && !AskToSaveNormal (this, pcName, rfCommit))
		return WC_RETURN;	// abgebrochen

	if (rfCommit) {
		if (IsNowWriteAble (pcName)) {
		// Projekt wieder beschreibbar
		bool fNewName = true;			// default: neuer Name

			if (!AskToSaveDirectly (this, pcName, fNewName))
				return WC_RETURN;		// abgebrochen

			if (!fNewName) {
			// unter OriginalNamen speichern
			string strNameCopy = pcName;

				if (!DBO().SaveAsGeoDB (pcName)) 
					return EC_NOOPEN;

			// in Menu eintragen
			ExtDirisWindow *pFrame = GetFrame();

				if (pFrame) {
					pFrame -> AddNewItem (true, strNameCopy.c_str(), false);
					DEX_ReReadCaption();	// Caption richten
				}
				rfCommit = false;	// nicht mehr speichern
				return EC_OKAY;
			}
		// ansonsten normales SaveAs
		// ... durchfallen
		} else
			TellThatCannotSaveDirectly (this, pcName, IDS_USEDBYOTHERS);

	ResString resCopy (IDS_PROJECTISCOPY, 32);
	
		if (!SaveAsGeoDB (resCopy))
			return WC_RETURN;		// abgebrochen
		rfCommit = false;
	}

return EC_OKAY;
}

ErrCode IrisWind::AskUserToClose (bool &rfCommit, bool fFlag, HPROJECT hDesc)
{
	if (m_iDrawSem > 0) {		// zeichnet gerade: nicht schließen
	// Synchronisation mit einer evtl. Zeichenoperation
		GCancelFlag |= GCFAbort;		// Zeichnen abbrechen
		return CantCloseWhenDrawing (this);
	}

ErrCode RC;
short iIndex = -1;
CEierUhr Wait (this, CursorPath(g_cbCursorSave));

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
	
// nachfragen, ob wirklich geschlossen werden soll, gibt letzte Gelegenheit
// DirtyFlag zu setzen
	if (DEXN_CloseProject (hDesc) == true) 
		return WC_RETURN;	// jemand will, daß dieses Projekt nicht abgeschlossen wird

// für alle Fälle noch mal Legende speichern
	DEX_SaveLegend();
	DEX_SaveOverview();

DatenBasisObjekt &rDBO = DBO(iIndex);

	if (IsLegalRegisteredVersion(this)) {
	// nur, wenn registrierte Version
		if (rDBO.DB().isDirty()) {
		// diverse projektbezogene Einstellungen wegschreiben
			rDBO.SaveHeader();
			if (rDBO.isComFile() && isVisible()) {	// kein Embedding
				if (rDBO.DB().GetROMode()) {		// 'echter' Schreibschutz
				// SaveAs machen, da nicht auf geöffnete Datei Commit'ed werden kann
					DBASSERT(HandleSaveRO (rDBO.DB().GetDBName(), rfCommit, false));

				} else if (rDBO.DB().isCopy()) {
				// Datei ist Kopie der OriginalDatei
					DBASSERT(HandleSaveCopy (rDBO.DB().GetDBName(), rfCommit, false));

				} else {
				// Datei mit normalen Schreibrechten eröffnet
					if (!AskToSaveNormal (this, rDBO.DB().GetDBName(), rfCommit))
						return WC_RETURN;
				}
			} else
				rfCommit = fFlag;
		} else // if (!rDBO.DB().GetTempMode())
			rfCommit = false;	// nicht speichern

		if (rDBO.DB().GetTempMode()) {	// noch kein Dateiname
			if (rfCommit) {
				if (!ExportAsGeoDB())
					return WC_RETURN;		// abgebrochen
				rfCommit = false;			// aktuelle DB nicht speichern
			}
		}
	} else 
		rfCommit = false;

// Jetzt alle davon in Kenntnis setzen, daß das Projekt wirklich 
// geschlossen wird. Wichtig, damit während der (unter Umständen)
// längeren Schließphase, das Nutzerinterface bereits auf 'geschlossen'
// umgestellt werden kann
	DEXN_ProjectToClose(hDesc);
	rDBO.toClose();						// soll geschlossen werden
	App::Exec(ExecIdleOnly);			// UI richten

// Rundruf zum letzten Speichern
	if (rfCommit) {
	IStorage *pIStg = NULL;

		if (DEX_GetProjectStorage (pIStg)) {
			DEXN_SaveSameStorage (pIStg);
			DEXN_SaveCompleted (NULL);
			pIStg -> Release();
		}
	}

	return EC_OKAY;						// bereits gespeichert
}

// DatenBasis abschließen -----------------------------------------------------
ErrCode IrisWind :: CloseDB (bool fCommit, HPROJECT hDesc) 
{
// DBO wiederfinden
int iIndex = -1;

	if (NULL == hDesc) { 	// aktuelle GeoDB schließen
		iIndex = m_pDBOs -> FActiveDBO();
		if (iIndex == -1) // keine aktive DBO
			iIndex = 0;	// die erste nehmen
		if (int(m_pDBOs -> Count()) > iIndex && DBO().DB().isOpened())
			hDesc = DBO().DB().DBDesc();
		else
			return (ErrCode)db_error (EC_NOOPEN, RC_CloseDB);
	}

	iIndex = m_pDBOs -> FFindItem (hDesc);
	if (iIndex == -1)
		return (ErrCode)db_error (EC_NOOPEN, RC_CloseDB);

DatenBasisObjekt &rDBO = DBO(iIndex);
ErrCode RC;

// Legende ausblenden
	if (pLegende) {
		pLegende -> Hide();
		LegendeCFlag = false;
		delete pLegende;
		pLegende = NULL;
	}
	if (pOverView) {
		pOverView -> Hide();
		OverViewCFlag = false;
		delete pOverView;
		pOverView = NULL;
	}

ExtDirisWindow *pFrame = GetFrame();

	if (NULL != pFrame) 
		rDBO.DeleteAllSightItems (pFrame -> MainMenu());

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

	CanvasErase();
	if (NULL != pFrame) 
		pFrame -> InitMenues();

// Notification absetzen, daß keine Sicht mehr aktiv ist
	DEXN_SightSelected (NULL);

// ObjektListe löschen
	DELETE (rDBO.pCT())
	rDBO.DetachViewWindow();
	rDBO.SetPaintFlag (PF_INVALID); 
	rDBO.EveryDelete();

	DBASSERT (rDBO.CloseDB (fCommit));	// das eigentliche Schließen
	m_pDBOs -> FDelItem (iIndex);		// aus Baum herauslösen

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
char *pDrive = NULL; TX_TRY(pDrive = new char [_MAX_DRIVE]);
char *pPath = NULL; TX_TRY(pPath = new char [_MAX_PATH]);
char *pName = NULL; TX_TRY(pName = new char [_MAX_FNAME]);
bool fResult = false;

	if (pDrive && pPath && pName) {
		if (fFullHeader) {
			str = g_cbTRiAS;
			str += g_cbSpaceDashSpace;	// #HK970808: ADDED: '-' for new captionstyle
			str += "[";		
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

char *pView = NULL; TX_TRY(pView = new char [_MAX_PATH]);
char *pCaption = NULL; TX_TRY(pCaption = new char [_MAX_PATH]);
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

bool IrisWind::RetrieveBasicCaption (string &strText, bool fExpand, bool fPureCaption)
{
// als erstes an der aktuellen Sicht nachsehen, ob BeschreibungsInfo da ist
VIEWDESC VD;

	VD.m_dwSize = sizeof(VIEWDESC);
	VD.m_pView = NULL;	// aktuelle Sicht verwenden
	TX_TRY(VD.m_pDesc = new char [_MAX_PATH]);
	VD.m_iLen = _MAX_PATH;
	
// #HK970808: ADDED: 'TRiAS® - ' for new captionstyle
	if (!fPureCaption) {
		strText = g_cbTRiAS;
		strText += g_cbSpaceDashSpace;
	}

// jetzt alles andere dranhängen
bool fCaptionOK = false;

	if (NULL != VD.m_pDesc) {		// SichtBeschreibung
		if (DEX_GetViewDescription (VD)) {
		// Fensterkopftext in Ansicht definiert
			if (fExpand) {
			char *pT = GenerateCaptionText (VD.m_pDesc);
			
				if (NULL != pT) {
					strText += pT;
					fCaptionOK = true;
					delete pT;
				}
			} else {
			// %v, %p nicht expandieren
				strText += VD.m_pDesc;
				fCaptionOK = true;
			}
		} 
		delete [] VD.m_pDesc;
	} 

// ansonsten den normalen SuchPfad einhalten
GeoDB &rDB = DBO().DB();

	if (!fCaptionOK) {
	HeaderEntry Caption (rDB, IDS_CAPTIONTEXT);

		if (HE_INVALID != Caption.Status()) {
			if (fExpand) {
			// Fensterkopftext im DB-Header definiert
			char *pT = GenerateCaptionText (Caption.EntryText());
				
				if (NULL != pT) {
					strText += pT;
					fCaptionOK = true;
					delete pT;
				}
			} else {
			// %v, %p nicht expandieren
				strText += Caption.EntryText();	
				fCaptionOK = true;
			}
		} 
	}
		
// Fensterkopftext nicht definiert, Namen der DB in 
// Fensterkopf eintragen
	if (!fCaptionOK)	// bei Fehler altes Caption beibehalten
		fCaptionOK = GenerateStandardCaption (strText, rDB.GetDBName(), true); 

	return fCaptionOK;
}

bool IrisWind::ReReadCaption (string &rStrCaption, bool fDelay)
{
	if (fDelay) {	// Caption später richten, wenn Zeit ist
		m_fReReadCaption = true;
		g_fPendingReReadCaption = true;
		return true;
	}
	m_fReReadCaption = false;
	g_fPendingReReadCaption = false;

string strText;

	if (!RetrieveBasicCaption (strText))
		return false;

GeoDB &rDB = DBO().DB();
bool fAppend = true;

	if (rDB.GetROMode()) {		// Schreibschutz (echter)
		strText += ResString (IDS_READONLYPROJECT, 30);
		fAppend = false;
	} else if (rDB.isCopy()) { 		// Projekt ist eine Kopie
		strText += ResString (IDS_PROJECTISCOPY, 30);
		fAppend = false;
	}

	if (DBO().Compatibility()) {
		if (fAppend)
			strText += TEXT(" ");
		strText += ResString (IDS_PROJECTISCOMPATIBEL, 64);
	}

	if (rDB.isDirty())
		strText += TEXT(" *");

	rStrCaption = strText;
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

// wenn UNC vorliegt, dann nichts machen
char *pNew = NULL; TX_TRY(pNew = new char [_MAX_PATH]);

	if (pNew && '\\' == *pDBName && '\\' == *(pDBName+1)) {
		strcpy (pNew, pDBName);
		return pNew;
	}

char *pODrive = NULL; TX_TRY(pODrive = new char [_MAX_DRIVE]);
char *pOPath = NULL; TX_TRY(pOPath = new char [_MAX_PATH]);
char *pName = NULL; TX_TRY(pName = new char [_MAX_FNAME]);
char *pExt = NULL; TX_TRY(pExt = new char [_MAX_EXT]);
char *pDefDrive = NULL; TX_TRY(pDefDrive = new char [_MAX_DRIVE]);
char *pDefPath = NULL; TX_TRY(pDefPath = new char [_MAX_PATH]);

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

// evtl. letztes OpenVerzeichnis aus Registry lesen
// einlesen sonstiger RegistryInfos
#if defined(ENABLE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
	{
	CCurrentUser regCfg (g_cbRegOpenMRU);
	char cbBuffer[_MAX_PATH];
	DWORD dwLen = sizeof(cbBuffer);

		if (regCfg.GetSubSZ (g_cbLastOpenDir, cbBuffer, dwLen))
			strInitDir = cbBuffer;
	}

	{	// es dürfen nicht gleichzeitig 2 Dialoge aktiv sein
	CNewDBDlg ODlg (pW, FakeTRiASName(IDS_DBCREATETEMPLATE, g_cbTRiAS, g_cbTRiAS).c_str());
	
		ODlg.SetInitialDir (strInitDir.c_str());
	
	// Dialogfenster Anzeigen
		ODlg.AddFlags (OFN_OVERWRITEPROMPT|OFN_LONGNAMES);
		if (IsWin40())
			ODlg.AddFlags (OFN_EXPLORER);

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

#if defined(ENABLE_WIN32S_CODE)
		if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
		{
		CCurrentUser regCfg (g_cbRegOpenMRU);
		string strPath (get_drive(strDBName) + get_path(strDBName)); 

			regCfg.SetSubSZ (g_cbLastOpenDir, strPath.c_str());
		}
	}

return iIndex;
}

bool IrisWind :: CreateNewGeoDB (int rgMode)
{
string strDBName = ResString (IDS_NONAME, 32).Addr();	// erstmal "keinen" Namen

// evtl. offene DB schließen
	if (m_pDBOs -> Count() && DBO().DB().isOpened()) {
	bool fCommit = true;

		if (EC_OKAY != AskUserToClose(fCommit))
			return false;	// Abbrechen oder Fehler
		if (EC_OKAY != CloseDB(fCommit)) 
			return false;	// Fehler oder warten
		DELETE (DRO);
	}

// EierUhr anzeigen
CEierUhr Wait (this, CursorPath(g_cbCursorLoad));
LPSTORAGE pIStorage = NULL;

	if (!::CreateNewGeoDB (NULL, &pIStorage, rgMode))	// temporär erzeugen
		return false;

// Strukturen für eröffnete GeoDb anlegen
ErrCode	EC = OpenDB (pIStorage, OM_Normal|OM_ActivateDBO|OM_DeleteOnClose,
					 strDBName.c_str());

	if (EC == EC_OKAY)
		DEXN_isCreatedProject(pIStorage);			// Projekt erzeugt
	
	pIStorage -> Release();
	if (EC != EC_OKAY) return false;

// alles ok, Nutzerinterface richten
ExtDirisWindow *pFrame = GetFrame();

	if (pFrame)	{
		pFrame -> InitProjectMenu();
		DEX_ReReadCaption();	// Caption richten
	}
	RePaint();				// neue DB zeichnen

return true;
}

// lediglich GeoDB anlegen ----------------------------------------------------
bool CreateNewGeoDB (LPCSTR pFileName, LPSTORAGE *ppIStorage, int rgMode,
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

	int iTempl = DBD050E;

// #HK980113: quick hack for V2.08
		rgMode |= OM_16BitCompatible;		// immer 5.00.00.0B erzeugen
// #HK980113: quick hack for V2.08

		if (rgMode & OM_16BitCompatible) {
			cDB.m_iMode |= DBVCompatible;
			iTempl = DBD050B;
		}

	ResString resClass (IDS_TRIASFULLNAME130, 30);

		cDB.m_pCFStr = resClass.Addr();
		EC = CreateNewDB ((CREATEDB *)&cDB, iTempl);
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

int ShowSaveAsDBDialog (pWindow pW, string &strDBName, bool fSaveAsCopy)
{
	if ('\0' == cbDefaultDir[0]) ReadIniPathes();

string strInitDir = cbDefaultDir;
int iIndex = -1;

// evtl. letztes OpenVerzeichnis aus Registry lesen
// einlesen sonstiger RegistryInfos
	if (
#if defined(ENABLE_WIN32S_CODE)
		!IsWin32s() && 
#endif // ENABLE_WIN32S_CODE
		!fSaveAsCopy) 
	{
	CCurrentUser regCfg (g_cbRegOpenMRU);
	char cbBuffer[_MAX_PATH];
	DWORD dwLen = sizeof(cbBuffer);

		if (regCfg.GetSubSZ (g_cbLastOpenDir, cbBuffer, dwLen))
			strInitDir = cbBuffer;
	}

	{	// es dürfen nicht gleichzeitig 2 Dialoge aktiv sein
	CSaveAsDBDlg ODlg (pW, fSaveAsCopy, FakeTRiASName(IDS_DBSAVEASTEMPLATE, g_cbTRiAS).c_str());
	
		ODlg.SetInitialDir (strInitDir.c_str());
		if (0 < strDBName.length()) {
		// Dateinamen voreinstellen
		string str = get_name (strDBName);

			str += get_ext (strDBName);
			ODlg.SetFileName (str.c_str());
		}

	// Dialogfenster Anzeigen
		ODlg.AddFlags (OFN_OVERWRITEPROMPT|OFN_LONGNAMES);
		if (IsWin40())
			ODlg.AddFlags (OFN_EXPLORER);

		ODlg.Show();
	
	// Resultate verarbeiten
		if (!ODlg.Result ()) return -1;
	
	// DB neu generieren
	char *pT = NULL; 
		
		iIndex = ODlg.GetFilterIndex();

		strDBName.resize(_MAX_PATH);
		ODlg.GetFileSpec ((LPSTR)strDBName.c_str(), _MAX_PATH);
		strDBName.adjustlen();

		if (
#if defined(ENABLE_WIN32S_CODE)
			!IsWin32s() && 
#endif // ENABLE_WIN32S_CODE
			!fSaveAsCopy) 
		{
		CCurrentUser regCfg (g_cbRegOpenMRU);
		string strPath (get_drive(strDBName) + get_path(strDBName)); 

			regCfg.SetSubSZ (g_cbLastOpenDir, strPath.c_str());
		}
	}

return iIndex;
}

bool IrisWind :: ExportAsGeoDB (void)
{
string strDBName;
int iIndex = 0;		// FilterIndex 

// evtl. aktuellen Dateinamen voreinstellen
DatenBasisObjekt &rDBO = DBO();
GeoDB &rDB = rDBO.DB();

	if (!rDB.GetTempMode()) {
		strDBName = rDB.GetDBName();

		if (IsWin40()) {	// wenn lange Dateinamen verfügbar sind
		ResString resCopy (IDS_PROJECTISCOPY, 32);
		string str = get_name(strDBName) + resCopy + get_ext(strDBName);

			strDBName = str;
		}
	}

// Namen erfragen 
	iIndex = ShowSaveAsDBDialog (this, strDBName, true);
	if (iIndex < 0)	return false;

CEierUhr Wait (this, CursorPath(g_cbCursorSave));

// wenn Dateiname identisch ist, dann lediglich speichern
	if (rDB.isDirty())
		rDBO.SaveHeader();
	if (!rDB.GetTempMode() && strDBName == rDB.GetDBName()) 
	{
		rDBO.PbdDB().Flush (false);
		return (EC_OKAY == rDB.Flush (false));	// alles wegschreiben
	}

// unter neuem Namen speichern
	if (!rDBO.ExportAsGeoDB (strDBName.c_str()))
		return false;

// FIX: ExportAs darf Projekt eben nicht im MRUMenu anzeigen
// in Menu eintragen
// ExtDirisWindow *pFrame = GetFrame();

//	if (pFrame) 
//		pFrame -> AddNewItem (true, strDBName.c_str(), false);

return true;
}

bool IrisWind :: SaveAsGeoDB (LPCSTR pcAppend)
{
string strDBName;
int iIndex = 0;		// FilterIndex 

// evtl. aktuellen Dateinamen voreinstellen
DatenBasisObjekt &rDBO = DBO();
GeoDB &rDB = rDBO.DB();

	if (!rDB.GetTempMode()) {
		strDBName = rDB.GetDBName();
		
		if (IsWin40() && NULL != pcAppend) {
		// nur wenn lange Dateinamen verfügbar sind
		string str = get_name(strDBName) + pcAppend + get_ext(strDBName);
			
			strDBName = str;
		}
	}

// Namen erfragen 
	iIndex = ShowSaveAsDBDialog (this, strDBName, false);
	if (iIndex < 0)	return false;

CEierUhr Wait (this, CursorPath(g_cbCursorSave));

// wenn Dateiname identisch ist, dann lediglich speichern
	if (rDB.isDirty())
		rDBO.SaveHeader();
	if (!rDB.GetTempMode() && strDBName == rDB.GetDBName()) 
	{
		rDBO.PbdDB().Flush (false);
		return (EC_OKAY == rDB.Flush (false));	// alles wegschreiben
	}

// unter neuem Namen speichern
	if (!rDBO.SaveAsGeoDB (strDBName.c_str())) 
		return false;

// in Menu eintragen
ExtDirisWindow *pFrame = GetFrame();

	if (pFrame) {
		pFrame -> AddNewItem (true, strDBName.c_str(), false);
		DEX_ReReadCaption();	// Caption richten
	}

return true;
}

bool IrisWind :: SaveGeoDB (void)
{
CEierUhr Wait (this, CursorPath(g_cbCursorSave));
bool fCommit = true;
DatenBasisObjekt &rDBO = DBO();
GeoDB &rDB = rDBO.DB();
LPCSTR pcName = rDB.GetDBName();
ErrCode RC;

	if (rDB.GetROMode()) {		// 'echter' Schreibschutz
	// SaveAs machen, da nicht auf geöffnete Datei Commit'ed werden kann
		DBASSERT(HandleSaveRO (pcName, fCommit, true));
	} else if (rDB.isCopy()) {
	// Datei ist Kopie der OriginalDatei
		DBASSERT(HandleSaveCopy (pcName, fCommit, true));
	}

// jetzt wirklich speichern (s. fCommit)
	if (rDBO.PbdDB().isOpened())
		rDBO.PbdDB().Flush (fCommit);

ErrCode EC = rDB.Flush (fCommit);

	if (fCommit && EC_OKAY == EC) {	// alles wegschreiben
	IStorage *pIStg = NULL;

		if (rDB.GetProjectStorage(&pIStg)) {
			DEXN_SaveSameStorage (pIStg);
			DEXN_SaveCompleted (NULL);

			if (rDB.isDirty()) {		// noch mal speichern
				rDBO.SaveHeader();
				if (fCommit) {
					rDB.Flush();		// noch mal flush'n

				HRESULT hr = pIStg -> Commit (STGC_DEFAULT);

					if (FAILED(hr) && (STG_E_MEDIUMFULL == GetScode(hr)))
						db_error (EC_NOSPACE, RC_CloseDB, pcName);
				}
				DEX_SetDirtyGeoDB (false);
			}

			pIStg -> Release();
		}
	}

return (EC_OKAY == EC);
}

// Anlegen einer neuen Datenbasis ---------------------------------------------
ErrCode CreateNewDB (CREATEDB *pCDB, unsigned short iRes)
{
DWORD dwResSize;
LPBYTE lpRes = (LPBYTE)ReadResource (hInstance, iRes, dwResSize);
ErrCode EC = EC_NOMEMORY;
char *pFullDB;
CDBDict *pDBDict = NULL;

	switch (pCDB -> m_iMode & (DBVNormal|DBVCompFile)) {
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
			pDBDict = CDBDictCompoundFile::CreateInstance (lpRes);
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


