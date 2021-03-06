// Code fuer OpenBox (Eroeffnen einer Datenbasis)
// File: IRISOPN2.CXX

#include "triaspre.hxx"

#include <ospace/file/path.h>

#include <dbd.h>
#include <dbd.hxx>
#include <dirisole.h>

#include <fnamestr.h>
#include <registry.hxx>
#include <ScopeVar.h>
#include <TRiASMode.h>
#include <funcs03.h>

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
#include "tools.hxx"
#include "opendb.hxx"
#include "overview.hxx"

#include "triasres.h"
#include "strings.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if defined(_FORCE_LEGACY_CODE)
void ResetGeoDBVersion (void);
#endif // defined(_FORCE_LEGACY_CODE)

void ReadIniPathes (void);
bool IsLegalRegisteredVersion (Window *pW, UINT uiCaption);

extern CLegendeClientWindow *pLegende;
extern HelpDisplay *IrisHD;

extern int g_iActTool;
extern DWORD g_iHideFlags;	// was soll ausgeblendet werden

extern COverViewClientWindow *pOverView;

extern short GCancelFlag;

extern char PbdDBDir[_MAX_PATH+1];
extern char cbDefaultDir[_MAX_PATH+1];	// StandardWurzelVerzeichnis der Projekte

extern short g_iTicks;
extern bool g_fPendingSave;
extern bool g_fPendingReReadCaption;
extern HINSTANCE hInstance;
extern DWORD g_dwMenu;

//////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASConnections);

//////////////////////////////////////////////////////////////////////////////
// globale Flags 
#if !defined(NOPROJEKTION)
extern bool GeographicCFlag;    // geografische Koordinaten
extern bool WorldCFlag;         // Weltprojektion
#endif

//extern bool inzFlag;            // aktuelle Datenbasis ist verschnitten
extern short CopyRightFlag;		// CopyrightSensitivity

// Enable-Fags f�r MenuPunkte -------------------------------------------------
extern bool g_fCloseEFlag;		// Projekt schlie�en
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

extern bool LegendToRepaint;
extern bool LegendeCFlag;		// Legende eingeblendet
extern bool OverViewCFlag;		// �bersichtsfenster

extern bool g_fDrawTextObjs;

// Funktion, die DB er�ffnet -------------------------------------------------
char *GenerateFullPath (LPCSTR pDBName, bool fMakeSubDir = true);

#if defined(_USE_LEGACY_CODE)
ErrCode IrisWind::OpenDB (
	LPCSTR DBName, LPCSTR UserName, LPCSTR PassWord, short gfMode, DWORD dwMode) 
{
ErrCode RC;

// wenn Fenster Icone ist, dann hochholen
	if (!(gfMode & OM_HideWindow)) {	// nur wenn anzuzeigen ist
		if (isIconic()) 
			Show (Normal);	// Anzeigen und hochholen
		else 
			ToTop();		// nur hochholen
	}

// Sensibilit�t gegen�ber anderen Versionen setzen
	SetCopyrightFlag (CopyRightFlag);
#if defined(_FORCE_LEGACY_CODE)
	ResetGeoDBVersion();
#endif // defined(_FORCE_LEGACY_CODE)
	g_fPendingSave = false;

	if (m_pDBOs == NULL) return EC_NOMEMORY;

// evtl. vollen VerzeichnisPfad generieren (aus StandardVerzeichnis)
char *pFullDB = GenerateFullPath (DBName);
short iIndex = -1;
			
// neue DB er�ffnen
	g_iTicks = 0;			// Reset AutoSave
	if ((iIndex = m_pDBOs -> FAddItem(false)) == -1) {	// neues DBObjekt erzeugen
		DELETE_OBJ (pFullDB);
		return (ErrCode)db_error (EC_NOMEMORY, RC_OpenDB);
	}

DatenBasisObjekt &rDBO = DBO(iIndex);

	rDBO.isOpening (true);

GeoDB &rDB = rDBO.DB();
	
	rDB.SetDBName (pFullDB ? (char *)pFullDB : (char *)DBName);
	rDB.SetROMode (gfMode & OM_RO);
	DELETE_OBJ (pFullDB);		// Speicher freigeben

	RC = rDB.Open ((char *)UserName, (char *)PassWord, dwMode);
	if (RC != EC_OKAY) {
		m_pDBOs -> FDelItem (iIndex);	// aus Baum herausl�schen
		return RC;
	}

// Testen, ob die Version der Datenbank von uns unterst�tzt wird
	if (rDB.GetDBVersion() > LASTDBVERSION) {
		rDB.Close();					// wieder schlie�en
		m_pDBOs -> FDelItem (iIndex);	// aus Baum herausl�schen
		return (ErrCode)db_error (WC_BADDBVERSION, RC_OpenDB);
	}
	
// diese DB in Liste der vorhergehenden DB's merken
ExtDirisWindow *pFrame = GetFrame();

	if (NULL != pFrame) {
	char cbBuffer[_MAX_PATH];

		pFrame -> AddNewItem (false, rDBO.GetDBName(cbBuffer), gfMode & OM_RO);
	}

// System auf ge�ffnete DB einstellen
	rDBO.AttachViewWindow (this);
//	rDBO.SetPaintFlag (PF_NOTDRAWED);
	rDBO.ReReadIdents();             // Identifikatoren aufsammeln

// Koordinatensystem setzen
	rDBO.ReScale (this);

// Men�punkte aktivieren/deaktivieren
//      OpenEFlag = false;
	g_fCloseEFlag = true;
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
ObjContainer ocT = rDBO.DBCont(true).InflateCont(10);

	SetExtend (ocT);

// zugeh�rige PBD-DB initialisieren
	rDBO.InitPbd (PbdDBDir);
	rDBO.MainInitPbd (rDB);		// interne MerkmalsCodes in PBD nachtragen

// DBVersion bestimmen, um Textobjekte richtig behandeln zu k�nnen
	g_fDrawTextObjs = (rDB.GetDBVersion() >= NEWDBVERSION);

// interne MerkmalsCodes in PBD nachtragen
	ReReadHeader (rDBO, rDB);	// GeoDBHeaderEintr�ge einlesen (_nach_ MainInitPbd)

// dieses DatenBasisObjekt als aktuelles aktivieren
	if (iIndex == 0 || gfMode & OM_ActivateDBO)
		m_pDBOs -> FActivateItem (iIndex);
		
// ToolFenster neu bilden
#if defined(OLD_TOOLBOX)
	if (!pToolBox) pToolBox = new ToolWind (this);       

// ToolBox erst anzeigen, wenn alle ihr Werkzeug eingeh�ngt haben
	if (pToolBox) {
		ToolBoxCFlag = true;            // Fenster ist angezeigt
		pToolBox -> Show ();
		pToolBox -> Update();
	}
#endif // OLD_TOOLBOX

// SightMenu initialisieren, StandardSicht einstellen, wenn gefordert
	if (pFrame && rDBO.InitSightMenu (pFrame -> MainMenu(), !(gfMode & OM_NoStandard)) &&
		!(g_dwMenu & HANDLEMENU_MainMenu))
	{
		::DrawMenuBar (pFrame -> Handle (API_WINDOW_HWND));
	}

// die Welt von diesem hervoragenden Ereignis in Kenntnis setzen
	rDBO.isOpening(false);
	DEXN_OpenProject (rDB.DBDesc());
	App::Exec(ExecIdleOnly);

return EC_OKAY;
}

ErrCode IrisWind::OpenDB (LPSTORAGE pIStorage, short gfMode, LPCSTR pcName) 
{
ErrCode RC;

// wenn Fenster Icone ist, dann hochholen
	if (!(gfMode & OM_HideWindow)) {	// nur wenn anzuzeigen ist
		if (isIconic()) 
			Show (Normal);	// Anzeigen und hochholen
		else 
			ToTop();		// nur hochholen
	}

// Sensibilit�t gegen�ber anderen Versionen setzen
	SetCopyrightFlag (CopyRightFlag);
#if defined(_FORCE_LEGACY_CODE)
	ResetGeoDBVersion();
#endif // defined(_FORCE_LEGACY_CODE)
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
	{	// Datei im FileSystem, aber nicht tempor�r
		strFullDB = GenerateFullPath (strFullDB.c_str());
	}

short iIndex = -1;

// neue DB er�ffnen
	g_iTicks = 0;			// Reset AutoSave
	if ((iIndex = m_pDBOs -> FAddItem(false)) == -1)	// neues DBObjekt erzeugen
		return (ErrCode)db_error (EC_NOMEMORY, RC_OpenDB);

DatenBasisObjekt &rDBO = DBO(iIndex);

	rDBO.isOpening (true);

GeoDB &rDB = rDBO.DB();
	
	rDB.SetDBName ((LPSTR)strFullDB.c_str());
	rDB.SetROMode (gfMode & OM_RO ? true : false);
	rDB.SetTempMode (gfMode & OM_DeleteOnClose ? true : false);
	DBASSERT (rDB.Open (pIStorage));

// Testen, ob die Version der Datenbank von uns unterst�tzt wird
	if (rDB.GetDBVersion() > LASTDBVERSION) {
		rDB.Close();			// wieder schlie�en
		m_pDBOs -> FDelItem (iIndex);	// ausBaum herausl�schen
		return (ErrCode)db_error (WC_BADDBVERSION, RC_OpenDB);
	}
	
// Bitmaps f�r Punktobjekte laden 
//	rDBO.LoadBitmapBars();		// in ReReadHeader

// diese DB in Liste der vorhergehenden DB's merken
ExtDirisWindow *pFrame = GetFrame();
char cbBuffer[_MAX_PATH];

	if (!(gfMode & OM_DeleteOnClose) && NULL != rDBO.GetDBName(cbBuffer)) {
		if (NULL != pFrame)
			pFrame -> AddNewItem (false, cbBuffer, gfMode & OM_RO);
	}

// System auf ge�ffnete DB einstellen
	rDBO.AttachViewWindow (this);
//	rDBO.SetPaintFlag (PF_NOTDRAWED);
	rDBO.ReReadIdents();             // Identifikatoren aufsammeln

// Koordinatensystem setzen
	rDBO.ReScale (this);

// Men�punkte aktivieren/deaktivieren
	g_fCloseEFlag = true;
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
ObjContainer ocT = rDBO.DBCont(true).InflateCont(10);

	SetExtend (ocT);

// zugeh�rige PBD-DB initialisieren
	rDBO.InitPbd (PbdDBDir);
	rDBO.MainInitPbd (rDB);		// interne MerkmalsCodes in PBD nachtragen

#if defined(OLD_TOOLBOX)
// ToolFenster neu bilden
	if (!pToolBox) pToolBox = new ToolWind (this);       

// ToolBox erst anzeigen, wenn alle ihr Werkzeug eingeh�ngt haben
	if (pToolBox) {
		ToolBoxCFlag = true;            // Fenster ist angezeigt
		pToolBox -> Show ();
		pToolBox -> Update();
	}
#endif // OLD_TOOLBOX

// DBVersion bestimmen, um Textobjekte richtig behandeln zu k�nnen
	g_fDrawTextObjs = (rDB.GetDBVersion() >= NEWDBVERSION);
	ReReadHeader (rDBO, rDB);	// GeoDBHeaderEintr�ge einlesen

// dieses DatenBasisObjekt als aktuelles aktivieren
	if (iIndex == 0 || gfMode & OM_ActivateDBO)
		m_pDBOs -> FActivateItem (iIndex);

// SightMenu initialisieren, StandardSicht einstellen, wenn gefordert
	if (pFrame && rDBO.InitSightMenu (pFrame -> MainMenu(), !(gfMode & OM_NoStandard)) &&
		!(g_dwMenu & HANDLEMENU_MainMenu))
	{
		::DrawMenuBar (pFrame -> Handle (API_WINDOW_HWND));
	}

// die Welt von diesem hervoragenden Ereignis in Kenntnis setzen
	rDBO.isOpening(false);
	DEXN_OpenProject (rDB.DBDesc());
	App::Exec(ExecIdleOnly);

	return EC_OKAY;
}
#endif // _USE_LEGACY_CODE

///////////////////////////////////////////////////////////////////////////////
// 
HRESULT IrisWind::OpenDB (ITRiASProject *pIPrj, OPENMODE rgMode) 
{
	TX_ASSERT(NULL != m_pDBOs);

// wenn Fenster Icone ist, dann hochholen
	if (!(rgMode & OPENMODE_HideDocument)) {	// nur wenn anzuzeigen ist
		if (isIconic()) 
			Show (Normal);				// Anzeigen und hochholen
		else 
			ToTop();					// nur hochholen
	}
#if defined(_FORCE_LEGACY_CODE)
	ResetGeoDBVersion();				// ??? mu� weg
#endif // defined(_FORCE_LEGACY_CODE)

// diverse Variablen richtig initialisieren
	g_fPendingSave = false;	
	g_iTicks = 0;						// Reset AutoSave
	g_fCloseEFlag = true;
	EditHeaderEFlag = true;
	DrawEFlag = true;
	IdentSelEFlag = true;
#if defined(OLD_COORDS)
	CoordsEFlag = true;
#endif // OLD_COORDS
#if !defined(NOPROJEKTION)
	WorldCFlag = false;
	GeographicCFlag = true;
#endif

// evtl. vollen VerzeichnisPfad generieren (aus StandardVerzeichnis)
int iIndex = m_pDBOs -> FAddItem(false);
			
// neue DB er�ffnen
	if (-1 == iIndex) {					// neues DBObjekt erzeugen
		db_error (EC_NOMEMORY, RC_OpenDB);
		return E_OUTOFMEMORY;
	}

DatenBasisObjekt &rDBO = DBO(iIndex);

	rDBO.isOpening (true);
	rDBO.AttachViewWindow (this);
//	rDBO.SetPaintFlag (PF_NOTDRAWED);
	rDBO.SetPrjFcn (NULL, NULL);		// Projektionsfunktion setzen
	if (!rDBO.LoadBitmapBars (false))	// Bitmaps f�r Punktobjekte laden 
		return E_OUTOFMEMORY;

HRESULT hr = rDBO.AttachTRiASProject (pIPrj);

	if (FAILED(hr)) return hr;
	rDBO.ReReadHeader();

// jetzt alle existierenden Connections dieses Projektes durchgehen und 
// hier einbauen
	hr = OpenConnections (pIPrj, rDBO);
	if (FAILED(hr)) return hr;

// System auf ge�ffnete DB einstellen
	if (S_OK == hr) 
		rDBO.RePrepareDBO (this, GetAspectRatio());

// dieses DatenBasisObjekt als aktuelles aktivieren
	if (0 == iIndex || rgMode & OPENMODE_Activate)
		m_pDBOs -> FActivateItem (iIndex);

// beim 'Connections'-ConPnt registrieren, damit alles weitere nicht an uns
// vorr�ber geht
	TX_ASSERT(0L == m_dwCookie);
	hr = AtlAdvise (pIPrj, static_cast<ITRiASConnectionEvents *>(&rDBO), IID_ITRiASConnectionEvents, &m_dwCookie);
	if (FAILED(hr)) return hr;

// beim 'Views'-ConPnt registrieren, damit alles weitere nicht an uns
// vorr�ber geht
	TX_ASSERT(0L == m_dwCookieViews);
	hr = AtlAdvise (pIPrj, static_cast<ITRiASViewEvents *>(&rDBO), IID_ITRiASViewEvents, &m_dwCookieViews);
	if (FAILED(hr)) return hr;

// diese DB in Liste der vorhergehenden DB's merken
ExtDirisWindow *pFrame = GetFrame();

	if (NULL != pFrame && !(OPENMODE_DoNotAddToMRU & rgMode)) {
	string str (rDBO.GetProjectName());

		if (0 < str.size())		// wenn DateiName existiert
			pFrame -> AddNewItem (false, str.c_str(), rgMode & OPENMODE_ReadOnly);
	}

// SightMenu initialisieren, StandardSicht einstellen, wenn gefordert
	if (pFrame && rDBO.InitSightMenu (pFrame -> MainMenu(), !(rgMode & OPENMODE_NoDefaultView)) &&
		!(g_dwMenu & HANDLEMENU_MainMenu))
	{
		::DrawMenuBar (pFrame -> Handle (API_WINDOW_HWND));
	}

	rDBO.isOpening(false);
	DEXN_OpenProject (rDBO.DBDesc());
	App::Exec(ExecIdleOnly);

	return S_OK;
}

HRESULT IrisWind::OpenConnections (ITRiASProject *pIPrj, DatenBasisObjekt &rDBO)
{
	try {
	WTRiASConnections Conns;

		THROW_FAILED_HRESULT(pIPrj -> get_Connections (Conns.ppi()));

	long lCnt = 0L;
	
		THROW_FAILED_HRESULT(Conns -> get_Count(&lCnt));
		if (0 == lCnt) return S_FALSE;		// no open connections

		for (long i = 1; i <= lCnt; i++) {
		CComVariant vIndex (i);
		WTRiASConnection Conn;

			THROW_FAILED_HRESULT(Conns -> Item (vIndex, Conn.ppi()));
			THROW_FAILED_HRESULT(rDBO.AddConnection (Conn));		// Event simulieren
		}

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Diverse HeaderEintr�ge einlesen
void IrisWind::ReReadHeader (DatenBasisObjekt &rDBO, GeoDB &rDB)
{
// DB auffordern, sich neu zu initialisieren
#if defined(_USE_LEGACY_CODE)
	if (!rDBO.IsTRiASDBBased()) {
		if (rDB.ReReadHeader()) {
	//		inzFlag = rDB.GetInzMode();
			rDBO.SetIdBase (rDB.GetIdentBase());
			rDBO.SetMkBase (rDB.GetMkBase());
			rDBO.PosTextAtBaseLine (rDB.GetPosAtBaseLine());
			rDBO.Compatibility (rDB.GetCompatibleMode());
		}

	// ScrollMode holen
		{
		HeaderEntry ScMode (rDB, IDS_SCROLLMODE);
		
			SetFullRedrawOnScroll (ScMode.EntryLong (0) != 0L);
		}

	// Bitmaps f�r Punktobjekte laden 
		rDBO.LoadBitmapBars();

	// HintergrundFarbe einlesen und setzen
		{
		HeaderEntry bkColor (rDB, g_cbBackGroundColor);
		Color C ((ColorVal)192, (ColorVal)192, (ColorVal)192);

	#if defined(ENABLE_WIN32S_CODE)
			if (!IsWin32s()) 
	#endif // ENABLE_WIN32S_CODE
				{
			CCurrentUser resBkColor (g_cbRegConfig);
			DWORD dwColor = 0x00C0C0C0L;

				resBkColor.GetDWORD (g_cbBackGroundColor, dwColor);
				C = (Color &)dwColor;
			} 

		long cBkColor = bkColor.EntryLong ((DWORD &)C, 16);
		Brush *pB = new Brush ((Color &)cBkColor);

			rDBO.SetBkColor ((Color &)cBkColor);
			if (NULL != pB) SetBackground (pB);
		}

	// HideFlags/ShowObjProp einlesen
		{
		CCurrentUser regCfg (g_cbRegConfig);
		DWORD dwData = DWORD(RODefaultFlags);

			regCfg.GetDWORD (g_cbHideFlags, dwData);

		HeaderEntry HideFlags (rDB, g_cbHideFlags);

			g_iHideFlags = (DWORD)HideFlags.EntryLong (dwData);
		
		char cbBuffer[64];
		DWORD dwLen = sizeof(cbBuffer);

			regCfg.GetSubSZ (g_cbShowObjProp, cbBuffer, dwLen);

		HeaderEntry ShowOP (rDB, g_cbShowObjProp);

			if (NULL != ShowOP.EntryText())
				strcpy (cbBuffer, ShowOP.EntryText());

			DEX_SetActObjPropName (cbBuffer);
		}
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(rDBO.IsTRiASDBBased());
		rDBO.ReReadHeader();
	}
}

// diverse Headereintr�ge wegscheiben
bool DatenBasisObjekt::SaveHeader (void)
{
// HideFlags/ShowObjProp wegschreiben
char cbBuffer[64];
GeoDB &rDB = DB();

	{
	CPrjHeaderEntry HideFlags (rDB, g_cbHideFlags);

		ltoa (g_iHideFlags, cbBuffer, 10);
		HideFlags.SetEntryText (cbBuffer);
		HideFlags.WriteBack();
	}
	{
	CPrjHeaderEntry ShowOP (rDB, g_cbShowObjProp);

		if (DEX_GetActObjPropName (cbBuffer)) {
			ShowOP.SetEntryText (cbBuffer);
			ShowOP.WriteBack();
		}
	}
	return true;
}

// Aktuelles Dokument schlie�en -----------------------------------------------
bool IrisWind::CloseDocument (void)
{
#if defined(_FORCE_LEGACY_CODE)
	if (m_pDBOs -> Count() && (DBO().IsTRiASDBBased() || DBO().DB().isOpened()))	// �berhaupt was ge�ffnet
#else
	if (m_pDBOs -> Count() > 0)	// �berhaupt was ge�ffnet
#endif // defined(_FORCE_LEGACY_CODE)
	{
		if (!m_fIsClosing) {
		CScopeVar<bool> fClosing (m_fIsClosing, true);
		bool fCommit = true;

			if (EC_OKAY != AskUserToClose (fCommit))
				return false;

			if (EC_OKAY != CloseDB (fCommit))
				return false;
		}
		DELETE_OBJ(m_pDRO);
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// F�r diverse F�lle nochmal r�ckfragen ---------------------------------------
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

return true;		// ok schlie�en
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

// mitteilen, da� die zu speichernde Datei gerade von einem anderen genutzt wird
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

// Den Fall abfragen und behandeln, wenn das Projekt schreibgesch�tzt ist.
ErrCode IrisWind::HandleSaveRO (LPCSTR pcName, bool &rfCommit, bool fSave)
{
// Im SaveModus mu� rfCommit auf true gesetzt sein
	TX_ASSERT(!fSave || rfCommit);

// erstmal fragen, ob �berhaupt gespeichert werden soll
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
ErrCode IrisWind::HandleSaveCopy (LPCSTR pcName, bool &rfCommit, bool fSave)
{
// Im SaveModus mu� rfCommit auf true gesetzt sein
	TX_ASSERT(!fSave || rfCommit);

// erstmal fragen, ob �berhaupt gespeichert werden soll
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

ErrCode IrisWind::AskUserToClose (bool &rfCommit, bool fForceCleanUp, bool fDefaultCommit, HPROJECT hDesc)
{
	if (m_iDrawSem > 0) {		// zeichnet gerade: nicht schlie�en
	// Synchronisation mit einer evtl. Zeichenoperation
		GCancelFlag |= GCFAbort;		// Zeichnen abbrechen
		return CantCloseWhenDrawing (this);
	}

ErrCode RC;
short iIndex = -1;
CEierUhr Wait (this, CursorPath(g_cbCursorSave));

	if (m_pDBOs == NULL) return EC_NOMEMORY;
	
	if (hDesc == 0) { 	// aktuelles Projekt schlie�en
		iIndex = m_pDBOs -> FActiveDBO();
		if (iIndex == -1) // keine aktive DBO
			iIndex = 0;	// die erste nehmen

#if defined(_FORCE_LEGACY_CODE)
		if (m_pDBOs -> Count() > 0 && (DBO().IsTRiASDBBased() || DBO().DB().isOpened()))	// �berhaupt was ge�ffnet
#else
		if (m_pDBOs -> Count() > 0)	// �berhaupt was ge�ffnet
#endif // defined(_FORCE_LEGACY_CODE)
		{
			hDesc = DBO().DBDesc();
		}
		else
			return (ErrCode)db_error (EC_NOOPEN, RC_CloseDB);
	}

// jetzt feststellen, welches Projekt geschlossen werden soll
	iIndex = m_pDBOs -> FFindItem (hDesc);
	if (iIndex == -1)
		return (ErrCode)db_error (EC_NOOPEN, RC_CloseDB);

	if (!(m_pDBOs -> Count() > iIndex &&
		  (DBO(iIndex).IsTRiASDBBased() || DBO(iIndex).DB().isOpened())))	// �berhaupt was ge�ffnet
	{
		return (ErrCode)db_error (EC_NOOPEN, RC_CloseDB);
	}

// nachfragen, ob wirklich geschlossen werden soll, gibt letzte Gelegenheit
// DirtyFlag zu setzen
	if (DEXN_CloseProject (hDesc)) 
		return WC_RETURN;	// jemand will, da� dieses Projekt nicht abgeschlossen wird

// f�r alle F�lle noch mal Legende speichern
	DEX_SaveLegend();
	DEX_SaveOverview();

DatenBasisObjekt &rDBO = DBO(iIndex);

	if (IsLegalRegisteredVersion(this, IDS_LICENCE_SAVEDB)) {
	// nur, wenn registrierte Version
		if ((rDBO.isDirty() || rDBO.GetTempMode()) && !fForceCleanUp) {
		// diverse projektbezogene Einstellungen wegschreiben
			rDBO.SaveHeader();
			if (rDBO.isComFile() && isVisible()) {	// kein Embedding
			char cbBuffer[_MAX_PATH];

				rDBO.GetDBName(cbBuffer);
				if (rDBO.GetROMode()) {			// 'echter' Schreibschutz
				// SaveAs machen, da nicht auf ge�ffnete Datei Commit'ed werden kann
					DBASSERT(HandleSaveRO (cbBuffer, rfCommit, false));

				} else if (rDBO.isCopy()) {
				// Datei ist Kopie der OriginalDatei
					DBASSERT(HandleSaveCopy (cbBuffer, rfCommit, false));

				} else {
				// Datei mit normalen Schreibrechten er�ffnet
					if (!AskToSaveNormal (this, cbBuffer, rfCommit))
						return WC_RETURN;
				}
			} else
				rfCommit = fDefaultCommit;
		} else // if (!rDBO.DB().GetTempMode())
			rfCommit = false;	// nicht speichern

		if (rDBO.GetTempMode()) {	// noch kein Dateiname
			if (rfCommit) {
				if (!SaveAsGeoDB())
					return WC_RETURN;		// abgebrochen
				rfCommit = false;			// aktuelle DB nicht speichern
			}
		}
	} else 
		rfCommit = false;

// Jetzt alle davon in Kenntnis setzen, da� das Projekt wirklich 
// geschlossen wird. Wichtig, damit w�hrend der (unter Umst�nden)
// l�ngeren Schlie�phase, das Nutzerinterface bereits auf 'geschlossen'
// umgestellt werden kann
	DEXN_ProjectToClose(hDesc);
	rDBO.toClose();						// soll geschlossen werden
	App::Exec(ExecIdleOnly);			// UI richten

#if defined(_USE_LEGACY_CODE)
// Rundruf zum letzten Speichern
	if (rfCommit && !rDBO.IsTRiASDBBased()) {
	IStorage *pIStg = NULL;

		if (DEX_GetProjectStorage (pIStg)) {
			DEXN_SaveSameStorage (pIStg);
			DEXN_SaveCompleted (NULL);
			pIStg -> Release();
		}
	}
#endif // _USE_LEGACY_CODE
	return EC_OKAY;						// bereits gespeichert
}

// DatenBasis abschlie�en -----------------------------------------------------
ErrCode IrisWind::CloseDB (bool fCommit, HPROJECT hDesc) 
{
// DBO wiederfinden
int iIndex = -1;

	if (NULL == hDesc) { 	// aktuelle GeoDB schlie�en
		iIndex = m_pDBOs -> FActiveDBO();
		if (iIndex == -1) 
			iIndex = 0;		// keine aktive DBO: die erste nehmen

		if (int(m_pDBOs -> Count()) > iIndex
#if defined(_FORCE_LEGACY_CODE)
			&& (DBO().IsTRiASDBBased() || DBO().DB().isOpened())
#endif // defined(_FORCE_LEGACY_CODE)
			)
		{
			hDesc = DBO().DBDesc();
		}
		else
			return (ErrCode)db_error (EC_NOOPEN, RC_CloseDB);
	}

// zu schlie�endes Projekt wiederfinden
	iIndex = m_pDBOs -> FFindItem (hDesc);
	if (iIndex == -1)
		return (ErrCode)db_error (EC_NOOPEN, RC_CloseDB);

ErrCode RC;

// Legende ausblenden
	if (pLegende) {
		pLegende -> Hide();			// nicht mehr anzeigen
		LegendToRepaint = false;
		LegendeCFlag = false;
		CLegendeWindow::DeleteInstance(pLegende);         // Speicher freigeben
		_ASSERTE(NULL == pLegende);
	}
	if (pOverView) {
		pOverView -> Hide();
		OverViewCFlag = false;
		COverView::DeleteInstance(pOverView);
		_ASSERTE(NULL == pOverView);
	}

// SelektionsPfeil als aktives Tool voreinstellen
	DEX_ChangeActiveTool(NUMARROW);

	{
	ExtDirisWindow *pFrame = GetFrame();
	DatenBasisObjekt &rDBO = DBO(iIndex);

		if (NULL != pFrame) 
			rDBO.DeleteAllSightItems (pFrame, pFrame -> MainMenu());

	// RechercheFenster freigeben
		if (ObjInfoListe.Count() > 0) 
			ObjInfoListe.EveryDelete();

	// Bildschirm l�schen, Menu/Accel richten
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

	// Notification absetzen, da� keine Sicht mehr aktiv ist
		DEXN_SightSelected (NULL);

	// ObjektListe l�schen
		if (NULL != rDBO.pCT()) {
			rDBO.pCT() -> UnAdvise();
			delete rDBO.pCT();
			rDBO.pCT() = NULL;
		}
		rDBO.DetachViewWindow();
		rDBO.SetPaintFlag (PF_INVALID); 
		rDBO.EveryDelete();

		DBASSERT (rDBO.CloseDB (fCommit));	// das eigentliche Schlie�en

	// ITRiASProject behandeln
		if (0 != m_dwCookie) {
			TX_ASSERT(rDBO.IsTRiASDBBased());

		WTRiASProject Prj;
		HRESULT hr = rDBO.GetTRiASProject (Prj.ppi());

			TX_ASSERT(SUCCEEDED(hr));
			AtlUnadvise (Prj, IID_ITRiASConnectionEvents, m_dwCookie);
			m_dwCookie = 0L;

			TX_ASSERT(0L != m_dwCookieViews);
			AtlUnadvise (Prj, IID_ITRiASViewEvents, m_dwCookieViews);
			m_dwCookieViews = 0L;
		}

		m_pDBOs -> FActivateItem(-1);	// nichts mehr aktiv
		rDBO.DetachTRiASProject();
	} // rDBO goes out of scope

	m_pDBOs -> FDelItem (iIndex);		// aus Baum herausl�sen

// DB geschlossen und ObjektListe leer

// MenuPunkte aktivieren/deaktivieren
	g_fCloseEFlag = false;
	EditHeaderEFlag = false;
	DrawEFlag = false;
	IdentSelEFlag = false;

// ObjContainerStack r�cksetzen
	while (actClip.Top().isValid())
		actClip.Pop();

// letzten Ident r�cksetzen
	m_lLastIdent = -1L;

// VisInfoIgnoreTree freigeben
	CIdentifikator::ReleaseIgnoreTree();
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
		os_string strName (pDBName);
		os_path path (strName);
		int iLevels = path.levels();

			if (strName.size() > 32 && iLevels > 2) {
			// Pfad verk�rzen, lediglich den letzten Teil drinlassen
			os_path shortPath ("c:\\1\\2\\3.4");

				if (path.has_drive())
					shortPath.drive (*(path.drive().c_str()));
				else if (path.has_unc())
					shortPath.unc (path.server(), path.share());
				shortPath.filename (path.filename());
				shortPath.extension (os_string(g_cbNil));	// Erweiterung ausblenden

				shortPath.section (0, os_string("..."));
				shortPath.section (1, path[iLevels-1]);
				
				str += os_string(shortPath);
			} else {
				path.extension (os_string(g_cbNil));		// Erweiterung ausblenden
				str += os_string(path);
			}
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

char *IrisWind::GenerateCaptionText (char *pTemplate)
{
	if (pTemplate == NULL) return NULL;

char *pView = NULL; TX_TRY(pView = new char [_MAX_PATH]);
char *pCaption = NULL; TX_TRY(pCaption = new char [_MAX_PATH]);
char *pT = NULL;

	if (pView == NULL || pCaption == NULL) {
		DELETE_VEC (pView);
		return NULL;
	}

// %v durch SichtNamen/Sichtbeschreibung ersetzen
	if ((pT = strstr(pTemplate, "%v")) != NULL) {
	// als erstes an der aktuellen Sicht nachsehen, ob BeschreibungsInfo da ist
	VIEWDESC VD;

		VD.m_dwSize = sizeof(VIEWDESC);
		VD.m_pView = NULL;	// aktuelle Sicht verwenden
		VD.m_pDesc = pView;
		VD.m_iLen = _MAX_PATH;
		
		if (!DEX_GetViewDescription (VD)) {
		// wenn nicht da, dann Sichtnamen verwenden
			DEX_GetActiveSight (pView);
			if (*pView == '\0') {
			// keine Sicht oder tempor�r
			ResString rsNoName (IDS_NOVIEWNAME, 30);

				strcpy (pView, rsNoName);
			}
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
	char cbBuffer[_MAX_PATH];

		GenerateStandardCaption (str, DBO().GetDBName(cbBuffer), false);
		str += pT+2;		// Rest kopieren
		strcpy (pCaption, str.c_str());
	} 

	DELETE_VEC (pView);
	return pCaption;
}

bool IrisWind::RetrieveBasicCaption (string &strText, bool fExpand, bool fPureCaption)
{
// #HK970808: ADDED: 'TRiAS� - ' for new captionstyle
	if (!fPureCaption) {
		strText = g_cbTRiAS;
		strText += g_cbSpaceDashSpace;
	}

// jetzt alles andere dranh�ngen
bool fCaptionOK = false;

// ansonsten den normalen SuchPfad einhalten
	{
	GeoDB &rDB = DBO().DB();
	CPrjHeaderEntry Caption (rDB, IDS_CAPTIONTEXT);

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
		
// Fensterkopftext nicht definiert, Namen der DB in Fensterkopf eintragen
	if (!fCaptionOK) {	// bei Fehler altes Caption beibehalten
	char cbBuffer[_MAX_PATH];

		fCaptionOK = GenerateStandardCaption (strText, DBO().GetDBName(cbBuffer), true); 
	}
	return fCaptionOK;
}

bool IrisWind::ReReadCaption (string &rStrCaption, bool fDelay)
{
	if (fDelay) {	// Caption sp�ter richten, wenn Zeit ist
		m_fReReadCaption = true;
		g_fPendingReReadCaption = true;
		return true;
	}
	m_fReReadCaption = false;
	g_fPendingReReadCaption = false;

string strText;

	if (!RetrieveBasicCaption (strText))
		return false;

DatenBasisObjekt &rDBO = DBO();
bool fAppend = true;

	if (rDBO.GetROMode()) {			// Schreibschutz (echter)
		strText += ResString (IDS_READONLYPROJECT, 30);
		fAppend = false;
	} 
	else if (rDBO.isCopy()) { 		// Projekt ist eine Kopie
		strText += ResString (IDS_PROJECTISCOPY, 30);
		fAppend = false;
	}

	if (rDBO.Compatibility()) {
		if (fAppend)
			strText += TEXT(" ");
		strText += ResString (IDS_PROJECTISCOMPATIBEL, 64);
	}

// Caption rumschicken
char cbBuffer[2*_MAX_PATH];

	strcpy (cbBuffer, strText.c_str());
	DEXN_ReReadCaption(cbBuffer);
	strText = cbBuffer;

	if (rDBO.isDirty())
		strText += TEXT(" *");

	rStrCaption = strText;
	return true;
}                       


// Vollen GeoDBNamen erzeugen -------------------------------------------------
// Der volle GeoDBName wird erzeugt, in dem die im gegebenen DateiNamen fehlenden
// Bestandteile des vollen DateiNamens durch die Teile aus den StandardPfad
// (aus der TRIAS.INI) erg�nzt werden. Wenn nur der Name des Projektes vorgegeben
// ist, so wird folgender Name erzeugt
//		StandardPfad\Projekt\Projekt.ris.
static char *GenerateFullPath (LPCSTR pDBName, bool fMakeSubDir)
{
	if (pDBName == NULL) return NULL;	// tempor�re Datei erzeugen

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
	DELETE_OBJ (pODrive);
	DELETE_OBJ (pDefDrive);
	DELETE_OBJ (pOPath);
	DELETE_OBJ (pDefPath);
	DELETE_OBJ (pName);
	DELETE_OBJ (pExt);
				 
return pNew;
}

// Neue Datenbasis erzeugen ---------------------------------------------------
int ShowCreateNewDBDialog (pWindow pW, string &strDBName, string &strUserName, string &strPWD)
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

	{	// es d�rfen nicht gleichzeitig 2 Dialoge aktiv sein
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
	char cbBuffer[_MAX_PATH];
			
		iIndex = ODlg.GetFilterIndex();

		ODlg.GetFileSpec (cbBuffer, _MAX_PATH);

		strDBName = cbBuffer;
		strUserName = (pT = ODlg.GetUserName()) ? pT : g_cbNil;
		strPWD = (pT = ODlg.GetPassWord()) ? pT : g_cbNil;

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

#if defined(_USE_LEGACY_CODE)
bool IrisWind::CreateNewGeoDB (int rgMode)
{
string strDBName = ResString (IDS_NONAME, 32).Addr();	// erstmal "keinen" Namen

// evtl. offene DB schlie�en
#if defined(_FORCE_LEGACY_CODE)
	if (m_pDBOs -> Count() && (DBO().IsTRiASDBBased() || DBO().DB().isOpened())) 
#else
	if (m_pDBOs -> Count() > 0) 
#endif // defined(_FORCE_LEGACY_CODE)
	{
	bool fCommit = true;

		if (EC_OKAY != AskUserToClose(fCommit))
			return false;	// Abbrechen oder Fehler
		if (EC_OKAY != CloseDB(fCommit)) 
			return false;	// Fehler oder warten
		DELETE_OBJ (m_pDRO);
	}

// EierUhr anzeigen
CEierUhr Wait (this, CursorPath(g_cbCursorLoad));
LPSTORAGE pIStorage = NULL;

	if (!::CreateNewGeoDB (NULL, &pIStorage, rgMode))	// tempor�r erzeugen
		return false;

// Strukturen f�r er�ffnete GeoDb anlegen
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
#endif // defined(_USE_LEGACY_CODE)

// lediglich GeoDB anlegen ----------------------------------------------------
bool CreateNewGeoDB (
	LPCSTR pFileName, LPSTORAGE *ppIStorage, int rgMode, LPCSTR pUser, LPCSTR pPWD)
{
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

	int iTempl = (g_dwTRiASMode & TRIASMODE_GDO) ? DBD050E : DBD050B;

		if (rgMode & OM_16BitCompatible) {
			cDB.m_iMode |= DBVCompatible;
			iTempl = DBD050B;
		}

	ResString resClass (IDS_TRIASFULLNAME130, 30);

		cDB.m_pCFStr = resClass.Addr();
		EC = CreateNewDB ((CREATEDB *)&cDB, iTempl);
	} 
	else {
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

///////////////////////////////////////////////////////////////////////////////
// Namen f�r zu speicherndes Projekt abfragen
int ShowSaveAsDBDialog (pWindow pW, string &strDBName, bool fSaveAsCopy)
{
	if ('\0' == cbDefaultDir[0]) 
		ReadIniPathes();

string strInitDir (cbDefaultDir);
int iIndex = -1;
char cbBuffer[_MAX_PATH];

// evtl. letztes OpenVerzeichnis aus Registry lesen
// einlesen sonstiger RegistryInfos
	if (
#if defined(ENABLE_WIN32S_CODE)
		!IsWin32s() && 
#endif // ENABLE_WIN32S_CODE
		!fSaveAsCopy) 
	{
	CCurrentUser regCfg (g_cbRegOpenMRU);
	DWORD dwLen = sizeof(cbBuffer);

		if (regCfg.GetSubSZ (g_cbLastOpenDir, cbBuffer, dwLen))
			strInitDir = cbBuffer;
	}

	{	// es d�rfen nicht gleichzeitig 2 Dialoge aktiv sein
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
		if (!ODlg.Result ()) 
			return -1;
	
	// Dateiendung pr�fen
		ODlg.GetFileSpec (cbBuffer, _MAX_PATH);

	os_path path = os_string(cbBuffer);

		strDBName = cbBuffer;
		if (strcmp (path.extension().c_str(), g_cbRiw+1)) 
			strDBName += g_cbRiw;		// einfach immer '.ris' dranh�ngen, wenns nicht schon da ist

	// DB neu generieren
		iIndex = ODlg.GetFilterIndex();
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

// an dieser Stelle ist der Dateiname g�ltig
	return iIndex;
}

bool IrisWind::ExportAsGeoDB (void)
{
string strDBName;
int iIndex = 0;		// FilterIndex 

// evtl. aktuellen Dateinamen voreinstellen
DatenBasisObjekt &rDBO = DBO();
GeoDB &rDB = rDBO.DB();
char cbBuffer[_MAX_PATH];

	if (!rDB.GetTempMode()) {
		strDBName = rDBO.GetDBName(cbBuffer);
		if (IsWin40()) {	// wenn lange Dateinamen verf�gbar sind
		ResString resCopy (IDS_PROJECTISCOPY, 32);
		string str (get_name(strDBName));
		
			str += resCopy;
			str += get_ext(strDBName);
			strDBName = str;
		}
	}

// Namen erfragen 
	iIndex = ShowSaveAsDBDialog (this, strDBName, true);
	if (iIndex < 0)	return false;

CEierUhr Wait (this, CursorPath(g_cbCursorSave));

#if defined(_FORCE_LEGACY_CODE)
	if (!rDBO.IsTRiASDBBased()) {
	// wenn Dateiname identisch ist, dann lediglich speichern
		if (rDB.isDirty())
			rDBO.SaveHeader();
		if (!rDB.GetTempMode() && strDBName == rDBO.GetDBName(cbBuffer)) 
		{
			rDBO.PbdDB().Flush (false);
			return (EC_OKAY == rDB.Flush (false));	// alles wegschreiben
		}
	} else
#endif // _FORCE_LEGACY_CODE

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

bool IrisWind::SaveAsGeoDB (LPCSTR pcAppend)
{
string strDBName;
int iIndex = 0;		// FilterIndex 

// evtl. aktuellen Dateinamen voreinstellen
DatenBasisObjekt &rDBO = DBO();
GeoDB &rDB = rDBO.DB();
char cbBuffer[_MAX_PATH];

	if (!rDBO.GetTempMode()) {
		strDBName = rDBO.GetDBName(cbBuffer);
		if (IsWin40() && NULL != pcAppend) {
		// nur wenn lange Dateinamen verf�gbar sind
		string str = get_name(strDBName) + pcAppend + get_ext(strDBName);
			
			strDBName = str;
		}
	}

// Namen erfragen 
	iIndex = ShowSaveAsDBDialog (this, strDBName, false);
	if (iIndex < 0)	return false;

CEierUhr Wait (this, CursorPath(g_cbCursorSave));

#if defined(_FORCE_LEGACY_CODE)
	if (!rDBO.IsTRiASDBBased()) {
	// wenn Dateiname identisch ist, dann lediglich speichern
		if (rDB.isDirty())
			rDBO.SaveHeader();

		if (!rDB.GetTempMode() && strDBName == rDBO.GetDBName(cbBuffer)) 
		{
			rDBO.PbdDB().Flush (false);
			return (EC_OKAY == rDB.Flush (false));	// alles wegschreiben
		}

	} 
#endif // _FORCE_LEGACY_CODE

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

bool IrisWind::SaveGeoDB (bool fAutoSave)
{
CEierUhr Wait (this, CursorPath(g_cbCursorSave));

bool fCommit = true;
DatenBasisObjekt &rDBO = DBO();
char cbBuffer[_MAX_PATH];
LPCSTR pcName = rDBO.GetDBName(cbBuffer);
ErrCode RC;

	if (rDBO.GetROMode()) {		// 'echter' Schreibschutz
	// SaveAs machen, da nicht auf ge�ffnete Datei Commit'ed werden kann
		DBASSERT(HandleSaveRO (pcName, fCommit, true));
	} 
	else if (rDBO.isCopy()) {
	// Datei ist Kopie der OriginalDatei
		DBASSERT(HandleSaveCopy (pcName, fCommit, true));
	}

#if defined(_FORCE_LEGACY_CODE)
	if (!rDBO.IsTRiASDBBased()) {
	GeoDB &rDB = rDBO.DB();

	// jetzt wirklich speichern (s. fCommit)
		if (rDBO.PbdDB().isOpened())
			rDBO.PbdDB().Flush (fCommit);

	ErrCode EC = rDB.Flush (fCommit);

		if (fCommit && EC_OKAY == EC) {	// alles wegschreiben
		IStorage *pIStg = NULL;

			if (SUCCEEDED(rDB.GetProjectStorage(&pIStg))) {
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
		return (EC_OKAY == EC) ? true : false;
	} else
#endif // _FORCE_LEGACY_CODE)
	{
		return rDBO.SaveGeoDB(fAutoSave);
	}
}

// Anlegen einer neuen Datenbasis ---------------------------------------------
ErrCode CreateNewDB (CREATEDB *pCDB, unsigned short iRes)
{
#if defined(_FORCE_LEGACY_CODE)
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
			pDBDict = CDBDictDOSFiles::CreateInstance (lpRes);
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
		CDBDictCompoundFile *pDBCDict = CDBDictCompoundFile::CreateInstance (lpRes);

			if (pDBCDict == NULL) break;
			pDBDict = pDBCDict;		// f�r's freigeben

		CREATEDBEX *pCDBEx = (CREATEDBEX *)pCDB;

			pFullDB = GenerateFullPath (pCDB -> m_pName, false);
			EC = pDBCDict -> CreateDBEx (
				pFullDB, pCDB -> m_pUser, pCDB -> m_pPassWd,
				&pCDBEx -> m_pIStorage, pCDBEx -> m_pClsID,
				pCDBEx -> m_pCFStr);
		}
		break;
	}	
		
	DELETE_OBJ (pFullDB);				 
	DELETE_OBJ (lpRes);
	DELETE_OBJ (pDBDict);
	return EC;
#else
	return DEX_CreateNewGeoDB(*pCDB);		// einfach weiterreichen (FakeMFC)
#endif // defined(_FORCE_LEGACY_CODE)
}


