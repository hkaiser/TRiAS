// Fuktionen, die bei externen Messages gerufen werden ------------------------
// File: EXTFCNS2.CXX
// @doc

#include "triaspre.hxx"

#include <shellapi.h>
#include <tchar.h>
#include <registry.hxx>
#include <konsobj.hxx>

#if defined(WIN32)
#include <dirisole.h>
#include "copystr.h"
#include "extmain3.hxx"
#endif

#if defined(OLD_TOOLBOX)
#include "tools.hxx"
#endif // OLD_TOOLBOX
#include "overview.hxx"
#include "legdinfo.hxx"
#include "legwind.hxx"
#include "minitpbd.hxx"

#include "triasres.h"
#include "strings.h"

#if defined(WIN32)
#include <funcs03.h>

#include <xtsnguid.h>		// GUID's
#include <undoguid.h>
#include <iunredo.hxx>

#include <undohelp.hxx>
#endif // WIN32

extern pApp g_pCurrApp;		// aktuelle App
extern HINSTANCE hInstance;	// aktuelles InstanceHandle
extern HPALETTE hPalette;	// aktive Farbpalette

extern bool LegendeCFlag;	// Legende angezeigt
extern bool OverViewCFlag;
extern bool LegendToRepaint;
extern bool PrintEFlag;		// Drucken !aktiv
extern bool g_fMenu;		// Menu's anzeigen
extern bool g_fUser;		// durch Nutzer gestartet

extern short GCancelFlag;       // General Cancel Flag

#if defined(OLD_TOOLBOX)
extern class ToolWind *pToolBox;	// ToolBox
#else
extern int g_iActTool;		// aktives Tool
#endif // OLD_TOOLBOX

extern class COverView *pOverView;	// Gesamtübersicht
extern class CLegendeWindow *pLegende;	// Legende

extern char cbDefaultDir[_MAX_PATH+1];

extern bool g_fDiagnostics;		// DiagnosticNotifications ausgeben
extern bool g_fAutomation;	// durch OLE Automation gestartet
extern bool g_fStartByOle;	// mit /Embedding gestartet
extern bool g_fTip;			// mit -t gestartet

extern bool g_fSystemAdm;	// SystemAdministratorMode
extern bool g_fShowSysFeatures;	// systeminterne Merkmale anzeigen

#if defined(_DEBUG) && defined(WIN32)
extern short g_iKonsFlags;
#endif // _DEBUG

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// sonstige FunktionsPrototypen -----------------------------------------------
ErrCode CreateNewDB (CREATEDB *pCDB, unsigned short iRes);
short OTypToBits (ObjTyp iOTyp);
ErrCode MainInitPbd (GeoDB &DB, uint resID, Bool iEnterNewCode, long lNewCode);

#if !defined(WIN32)
bool IsWin32s (void);
#endif

// DEX_RENDERGEODB: GeoDB in hDC abbilden -------------------------------------
LRESULT ExtDirisWindow :: OnRenderGeoDB (HPROJECT hPr, LPARAM lParam)
{	
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
#if defined(_DEBUG)
RENDERGEODB *pRG = (RENDERGEODB *)lParam;

	TX_ASSERT_POINTER(pRG, RENDERGEODB);
	TX_ASSERT(sizeof(RENDERGEODB) == pRG -> dwSize);
#endif // _DEBUG

	return LRESULT(RenderGeoDB ((RENDERGEODB *)lParam));
}

// DEX_QUERYEXPOSEDOC: neu zu zeichnenden GeoDB-Bereich liefern ---------------
LRESULT ExtDirisWindow :: OnQueryExposedOC (HPROJECT hPr, LPARAM lParam)
{	
	if (!IsValidActiveView())
		return LRESULT(false);
		
	TX_ASSERT(TIsValidAddress((void *)lParam, sizeof(ObjContainer), true));
	return LRESULT(DBO().QueryExposedOC ((ObjContainer *)lParam));
}

// DEX_QUERYEXPOSEDAREA: neu zu zeichnenden Bildschirmbereich liefern ---------
LRESULT ExtDirisWindow :: OnQueryExposedArea (HPROJECT hPr, LPARAM lParam)
{	
	if (!IsValidActiveView())
		return LRESULT(false);
		
	TX_ASSERT(TIsValidAddress((void *)lParam, sizeof(Rectangle), true));
	return LRESULT(DBO().QueryExposedArea ((Rectangle *)lParam));
}

// DEX_QUERYPROJECTSTORAGE: LPSTORAGE für dieses Projekt liefern --------------
LRESULT ExtDirisWindow :: OnQueryIStorage (HPROJECT hPr, LPARAM lParam)
{		
	if (!DBO().DB().isOpened())		// evtl. während der SchließPhase
		return LRESULT(false);
		
	TX_ASSERT(TIsValidAddress((void *)lParam, sizeof(LPSTORAGE), true));

	return LRESULT(DBO().DB().GetProjectStorage ((LPSTORAGE *)lParam));
}

// DEX_QUERYACTIVEPALETTE: aktuelle Palette abfragen --------------------------
LRESULT ExtDirisWindow :: OnQueryActPalette (HPROJECT hPr, LPARAM lParam)
{	
	return (LPARAM)(void *)hPalette;
}
		
// DEX_SHOWMAINWINDOW: Hauptfenster anzeigen ----------------------------------
LRESULT ExtDirisWindow :: OnShowMainWindow (HPROJECT hPr, LPARAM lParam)
{		
	Show ((ShowState)lParam);
	App :: Exec (ExecWhileEvent);
	ToTop();		// #HK960920

return LRESULT(true);
}

// DEX_HIDEMAINWINDOW: Hauptfenster ausblenden --------------------------------
LRESULT ExtDirisWindow :: OnHideMainWindow (HPROJECT hPr, LPARAM lParam)
{	
	Show (HideWindow);
	App :: Exec (ExecWhileEvent);

return LRESULT(true);
}

// DEX_QUERYMAINWINDOWVISIBLE: Hauptfenster sichtbar ? ------------------------
LRESULT ExtDirisWindow :: OnQueryMainWindowVisible (HPROJECT hPr, LPARAM lParam)
{		
	return (LPARAM)isVisible();
}
		
// DEX_QUITAPP: TRiAS beenden -------------------------------------------------
LRESULT ExtDirisWindow::OnQuit (HPROJECT hPr, LPARAM)
{
Event eQuit;

	eQuit.Msg() = WM_CLOSE;
	eQuit.WParam() = 0L;
	eQuit.LParam() = 0L;
	PostEvent (eQuit);

return LRESULT(false);	// nicht geschlossen
}
		
// DEX_QUERYDEFAULTDATAPATH: StandardDatenPfad liefern --------------------------
LRESULT ExtDirisWindow :: OnQueryDefaultDataPath (HPROJECT hPr, LPARAM lParam)
{	
	TX_ASSERT(TIsValidAddress((void *)lParam, _MAX_PATH, true));
	if (lParam) strcpy ((char *)lParam, cbDefaultDir);

return LRESULT(lParam);
}		

// DEX_MODDEFAULTDATAPATH: Standard-datenPfad modifizieren --------------------
LRESULT ExtDirisWindow :: OnModDefaultDataPath (HPROJECT hPr, LPARAM lParam)
{		
	TX_ASSERT(TIsValidString((char *)lParam));
	if (lParam) strcpy (cbDefaultDir, (char *)lParam);

return LRESULT(lParam);
}

// DEX_REMOVEORWND: ORFenster schließen ---------------------------------------
LRESULT ExtDirisWindow :: OnCloseORWindows (HPROJECT hPr, LPARAM lParam)
{
	if (NULL == lParam)
		CloseAllORWindows();	
	else {
		TX_ASSERT(IsWindow((HWND)lParam) && NULL != GetORWindow((HWND)lParam));

		CloseORWindow ((HWND)lParam);
	}

return LRESULT(true);
}

// DEX_ACTIVATEALLORWNDS: alle ORFenster schließen ----------------------------
LRESULT ExtDirisWindow :: OnActivateAllORWnds (HPROJECT hPr, LPARAM lParam)
{	
	TX_ASSERT(NULL == (HWND)lParam ||
		  (IsWindow((HWND)lParam) && NULL != GetORWindow((HWND)lParam)));
	
return LRESULT(ActivateAllObj ((HWND)lParam));
}

// DEX_QUERYOPENPROJECTS: Anzahl der geöffneten Projekte abfragen -------------
LRESULT ExtDirisWindow :: OnNumOfOpenProjects (HPROJECT hPr, LPARAM lParam)
{
	return IsValidActiveView() ? 1 : 0;		// ehrlich aber wahr
}

// DEX_GETVIEWDESCRIPTION: BeschreibungsText für eine Sicht liefern -----------
LRESULT ExtDirisWindow :: OnQueryViewDescription (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(NULL);

#if defined(_DEBUG)
VIEWDESC *pVD = (VIEWDESC *)lParam;

	TX_ASSERT(TIsValidAddress(pVD, sizeof(VIEWDESC), true));
	TX_ASSERT(sizeof(VIEWDESC) == pVD -> m_dwSize);
	TX_ASSERT(NULL == pVD -> m_pView || TIsValidString(pVD -> m_pView));
	TX_ASSERT(TIsValidAddress(pVD -> m_pDesc, pVD -> m_iLen, true));
#endif // _DEBUG

return LRESULT(DBO().QueryViewDesc ((VIEWDESC *)lParam));
}

// DEX_MODVIEWDESCRIPTION: BeschreibungsText einer Sicht setzen ---------------
LRESULT ExtDirisWindow :: OnSetViewDescription (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(NULL);
		
#if defined(_DEBUG)
VIEWDESC *pVD = (VIEWDESC *)lParam;

	TX_ASSERT_POINTER(pVD, VIEWDESC);
	TX_ASSERT(sizeof(VIEWDESC) == pVD -> m_dwSize);
	TX_ASSERT(NULL == pVD -> m_pView || TIsValidString(pVD -> m_pView));
	TX_ASSERT(NULL == pVD -> m_pDesc || TIsValidString(pVD -> m_pDesc));
#endif // _DEBUG

	DBO().DB().SetDirty();

return LRESULT(DBO().SetViewDesc ((VIEWDESC *)lParam));
}

// DEX_CANCELMODE: Blinken aller ORFenster beeinflussen -----------------------
LRESULT ExtDirisWindow :: OnCancelMode (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
return LRESULT(HandleCancelMode ((lParam != 0) ? true : false));
}

// DEX_QUERYPROJECTCONT: liefert DB-Container ---------------------------------
LRESULT ExtDirisWindow :: OnQueryProjectCont (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView() || lParam == 0)
		return LRESULT(false);

	TX_ASSERT(TIsValidAddress((void *)lParam, sizeof(ObjContainer), true));
	*(ObjContainer *)lParam = DBO().DB().DBCont();
	
return LRESULT(true);
}

long RetrieveObjNameMCodeIdent (DatenBasisObjekt &rDBO, long lIdent)
{
	TX_ASSERT(IsValidIdent(lIdent));

ProFile PF (rDBO.DB().GetDBName());
char outBuff[MAX_OKS_LEN];

	ClassFromIdent (lIdent, outBuff);

long lMCode = PF.GetObjNameCode (outBuff);

	if (-1L != lMCode)
		MainInitPbd (rDBO.DB(), IDS_OBJNAME, true, lMCode);

	return lMCode;
}

long RetrieveObjNameMCode (DatenBasisObjekt &rDBO, long lONr)
{
	TX_ASSERT(IsValidONr(rDBO.DB().DBDesc(), lONr));
	return RetrieveObjNameMCodeIdent (rDBO, rDBO.RetrieveIdent (lONr));
}

// DEX_QUERYOBJECTNAME: Lesen eines Objektnamens ------------------------------
// @msg DEX_QUERYOBJECTNAME | Diese Message wird an <tr> geschickt, um den Namen 
// eines Objektes abzufragen. In dem Fall, wenn kein Objektname für dieses Objekt 
// existiert, wird der Unique Ident geliefert.
// @parm OBJECTFEATURE * | pObjFeature | lParam enthält einen Pointer auf
// eine Struktur vom Typ <t OBJECTFEATURE>.
// @rdesc <tr> liefert den Pointer auf die Zeichenkette <e OBJECTFEATURE.m_pMText>
// wenn kein Fehler aufgetreten ist, ansonsten ist der Rückgabewert NULL.<nl>Diese Message
// kann außerdem dazu verwendet werden, abzufragen, ob das gegebene Objekt einen 
// Objektnamen besitzt. In diesem Fall ist der Rückgabewert <t true>, wenn ein Objektname 
// für dieses Objekt existiert, anderenfalls <t false>.
// @comm Der Objektname eines Objektes ist ein Merkmalswert, welcher für ein Objekt
// unter einem speziellen Merkmalscode abgelegt ist. Dieser Merkmalscode wird z.Zt.
// spezifisch für den Identifikator eines Objektes über die Initialisierungsdatei 
// des aktuellen Projektes festgelegt. Der Objektname eines Objektes kann mit der 
// Message <m DEX_SETOBJECTNAME> geschrieben bzw. gelöscht werden.<nl>Diese Message 
// wird durch die Funktion <f DEX_GetObjectName> ausgelöst.
// @xref <m DEX_SETOBJECTNAME>, <f DEX_GetObjectName>
LRESULT ExtDirisWindow :: OnQueryObjectFeatureSpec (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(NULL);

// MerkmalsCode des Objektnamens besorgen und Merkmal schreiben
TARGETMERKMAL TM;
OBJECTFEATURE *pOF = (OBJECTFEATURE *)lParam;

	TX_ASSERT_POINTER(pOF, OBJECTFEATURE);

	INITSTRUCT (TM, TARGETMERKMAL);
	TM.lTarget = pOF -> m_lONr;
	TM.lMCode = RetrieveObjNameMCode (DBO(), pOF -> m_lONr);
	TM.imaxLen = pOF -> m_iLen;
	TM.pMText = pOF -> m_pMText;
	TM.iTTyp = TT_Objekt;

LRESULT lRes = 0L;

	if ((lRes = OnQueryTextMerkmal (hPr, LPARAM(&TM))) == 0L) {
	// dieses Objekt hat keinen Objektnamen, UniqueIdent verwenden
		TM.lMCode = DEX_GetUniqueIdentMCode();
		TM.imaxLen = pOF -> m_iLen;	// Länge neu setzen
		lRes = OnQueryTextMerkmal (hPr, LPARAM(&TM));
	} 
	if (lRes)	// Erfolg
		pOF -> m_iLen = TM.imaxLen;		// realen Wert zurückschreiben
	return lRes;	
}

// DEX_SETOBJECTNAME: Setzen/Löschen eines Objektnamens -----------------------
// @msg DEX_SETOBJECTNAME | Diese Message wird an <tr> geschickt, um den Namen 
// eines Objektes zu setzen oder zu löschen.
// @parm OBJECTFEATURE * | pObjFeature | lParam enthält einen Pointer auf
// eine Struktur vom Typ <t OBJECTFEATURE>.
// @rdesc <tr> liefert einen <t ErrCode>. D.h. EC_OKAY wenn kein Fehler 
// aufgetreten ist bzw. anderenfalls einen den Fehler beschreibendenden <t ErrCode>.
// @comm Der Objektname eines Objektes ist ein Merkmalswert, welcher für ein Objekt
// unter einem speziellen Merkmalscode abgelegt ist. Dieser Merkmalscode wird z.Zt.
// spezifisch für den Identifikator eines Objektes über die Initialisierungsdatei 
// des aktuellen Projektes festgelegt.<nl>Der Objektname wird gelöscht, wenn der Wert
// des Feldes <e OBJECTFEATURE.m_pMText> gleich NULL ist.<nl>Der Objektname eines 
// Objektes kann mit der Message <m DEX_QUERYOBJECTNAME> abgefragt werden.
// <nl>Diese Message wird durch die Funktion <f DEX_ModObjectName> ausgelöst.
// @xref <m DEX_QUERYOBJECTNAME>, <f DEX_ModObjectName>
LRESULT ExtDirisWindow :: OnSetObjectFeatureSpec (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);

// MerkmalsCode des Objektnamens besorgen und Merkmal schreiben
TARGETMERKMAL TM;
OBJECTFEATURE *pOF = (OBJECTFEATURE *)lParam;

	TX_ASSERT_POINTER(pOF, OBJECTFEATURE);

	INITSTRUCT(TM, TARGETMERKMAL);
	TM.lTarget = pOF -> m_lONr;
	TM.lMCode = RetrieveObjNameMCode (DBO(), pOF -> m_lONr);
	TM.imaxLen = pOF -> m_iLen;
	TM.pMText = pOF -> m_pMText;
	TM.iTTyp = TT_Objekt;

return OnModTextMerkmal (hPr, LPARAM(&TM));
}

// DEX_DIAGNOSTICSENABLE: Ein- und Ausschalten der DiagnoseNotifikationen ----
// @msg DEX_DIAGNOSTICSENABLE | Mit dieser Message an <tr> können die 
// Diagnose-Notifikationen ein- bzw. ausgeschaltet werden.
// @parm bool | fDiagnostics | lParam ist ein Wert vom Typ <t bool>, der angibt, ob
// im weiteren Diagnose-Notifikationen verschickt werden sollen.
// @rdesc Der Rückgabewert enthält den bisherigen DiagnoseMode, der dazu verwendet 
// werden kann den ursprünglichen wert wieder einzustellen.
// <nl>Diese Message wird durch die Funktionen <f DEX_EnableDiagnostics> und
// <f DEX_DisableDiagnostics> ausgelöst.
// @comm Um die Diagnose-Notifikation auch wirklich zu erhalten, genügt es nicht,
// diese mit dieser Message einzuschalten. Diese Message schaltet lediglich die
// Generierung der Diagnose-Notifikationen zu. Zusätzlich muß jede der gewünschten
// Notifikationen einzeln registriert werden <mf CTriasExtension::RegisterNotification>.
// Gleiches gilt für die Nutzung dieser Message zum Abschalten der Diagnose-Notifikationen.
// Es genügt nicht, lediglich diese Message abzuschicken, auf jeden Fall müssen alle
// vorher registrierten Notifikationen mit <mf CTriasExtension::UnRegisterNotification>
// wieder abgemeldet werden.
// @xref <f DEX_EnableDiagnostics>, <f DEX_DisableDiagnostics>, 
// <mf CTriasExtension::RegisterNotification>, 
// <mf CTriasExtension::UnRegisterNotification>
LRESULT ExtDirisWindow :: OnEnableDiagnostics (HPROJECT hPr, LPARAM lParam)
{
bool fOldDiag = g_fDiagnostics;

	g_fDiagnostics = (bool)lParam;

return LRESULT(fOldDiag);
}

// DEX_QUERYUNKNOWNIDENT: Ein- und Ausschalten der DiagnoseNotifikationen ----
// @msg DEX_QUERYUNKNOWNIDENT | Mit dieser Message an <tr> kann der Identifikator
// für nicht klassifizierte Objekte des aktuellen Projektes abgefragt werden.
// @rdesc Der Rückgabewert enthält den gewünschten Identifikator bzw. Null im 
// Fehlerfall.
// <nl>Diese Message wird durch die Funktion <f DEX_GetUnknownIdent> ausgelöst.
// @comm Der Identifikator für die Objektklasse der nicht klassifizierten Objekte ist
// eine projektbezogener Wert, der durch <tr> generiert wird. Dieser Wert wird im
// Datenbasis-Header unter dem Schlüssel 'UnknownIdent' eingetragen.
// @xref <f DEX_GetUnknownIdent>
LRESULT ExtDirisWindow :: OnQueryUnknownIdent (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(0L);

	return LRESULT(DBO().QueryUnknownIdent());
}

// DEX_FINDOBJFROMNAME: Auffinden eines Objektes über Objektnamen -------------
// @msg DEX_FINDOBJFROMNAME | Mit dieser Message an <tr> kann ein Objekt über seinen
// Objektnamen gesucht werden.
// @parm char * | pObjName | Der Objektname des gesuchten Objektes.
// @rdesc Der Rückgabewert enthält Objeknummer des gesuchten Objektes bzw. -1L im 
// Fehlerfall.<nl>Diese Message wird durch die Funktion <f DEX_GetONrFromObjName>
// ausgelöst.
// @comm Existieren mehrere Objekte mit diesem Objektnamen, so wird das erste gefundene 
// geliefert. Existiert kein Objekt mit diesem Objektnamen, so wird die übergebene
// Zeichenkette als Unique Ident interpretiert und das Objekt mit diesem Unique Ident
// gesucht. Auch hier wird das jeweils erste gefundene Objekte geliefert.
// @xref <f DEX_GetONrFromObjName>
LRESULT ExtDirisWindow :: OnFindObjFromName (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(-1L);

	TX_ASSERT(TIsValidString((char *)lParam));
	return LRESULT(DBO().FindObjFromName ((char *)lParam));
}

// DEX_QUERYOBJNAMEMCODE: Liefert MCode für Objektnamen für Objektes eines Idents
// @msg DEX_QUERYOBJNAMEMCODE | Mit dieser Message an <tr> kann der Merkmalscode 
// abgefragt werden, unter dem für alle Objekte des gegebenen Identifikators der
// Objektname abgelegt ist.
// @parm ULONG | lIdent | Identifikator, für dessen Objekte der Merkmalscode gesucht 
// wird.
// @rdesc Der Rückgabewert enthält den gesuchten Merkmalscode bzw. Null im 
// Fehlerfall.<nl>Diese Message wird durch die Funktion <f DEX_GetObjNameMCode>
// ausgelöst.
// @comm Der Objektname ist ein spezielles (Text-)Merkmal eines Objektes, welches ein Objekt 
// im allgemeinen eineindeutig beschreibt. Es kann zur nutzerfreundlichen Identifikation
// eines Objektes eingestzt werden. Dieses Merkmal wird für alle Objekte eines 
// Identifikators unter einem einheitlichen Merkmalscode abgelegt. Dieser Merkmalscode
// wird durch die Funktion <f DEX_GetObjNameMCode> geliefert.
// @xref <f DEX_GetObjNameMCode>
LRESULT ExtDirisWindow :: OnQueryObjNameMCode (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(0L);

	TX_ASSERT(IsValidIdent(lParam));

return LRESULT (RetrieveObjNameMCodeIdent (DBO(), lParam));
}

// DEX_QUERYUNIQUEIDENTMCODE: Abfragen des MCodes der Unique Idents -----------
// @msg DEX_QUERYUNIQUEIDENTMCODE | Mit dieser Message an <tr> kann der Merkmalscode 
// abgefragt werden, unter dem für alle Objekte der Unique Ident abgelegt ist.
// @rdesc Der Rückgabewert enthält den gesuchten Merkmalscode bzw. Null im 
// Fehlerfall.
// @comm Der Unique Ident ist ein eineindeutiges (Text-)Merkmal, welches automatisiert für
// jedes Objekt bei dessen Erfassung generiert wird. Dieses Merkmal wird für alle 
// Objekte unter einem einheitlichen Merkmalscode abgelegt.<nl>Diese Message wird 
// durch die Funktion <f DEX_GetUniqueIdentMCode> ausgelöst.
// @xref <f DEX_GetUniqueIdentMCode>
LRESULT ExtDirisWindow :: OnQueryUniqueIdentMCode (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(0L);

long lMCode = HeaderEntry (DBO().DB(), IDS_UNIQUEIDENT).EntryLong(0L);

	if (0L == lMCode) {
		if (10 == DBO().GetMkBase())
			lMCode = 51200000L;
		else
			lMCode = 0x51200000L;
		MainInitPbd (DBO().DB(), IDS_UNIQUEIDENT, true, lMCode);
	}

return LRESULT(lMCode);
}

// DEX_QUERYOLDUNIQUEIDENTMCODE: Abfragen des MCodes der ursprünglichen Unique Idents -----------
LRESULT ExtDirisWindow :: OnQueryOldUniqueIdentMCode (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(0L);

long lMCode = HeaderEntry (DBO().DB(), IDS_OLDUNIQUEIDENT).EntryLong(0L);

	if (0L == lMCode) {
		if (10 == DBO().GetMkBase())
			lMCode = 51300000L;
		else
			lMCode = 0x51300000L;
		MainInitPbd (DBO().DB(), IDS_OLDUNIQUEIDENT, true, lMCode);
	}

return LRESULT(lMCode);
}


// Diverse HeaderEinträge neu einlesen ----------------------------------------
// @msg DEX_HEADERREREAD | Mit dieser Message an <tr> werden diverse Einträge des 
// aktuellen Projektes neu eingelesen. 
// @rdesc Diese Message liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @comm Diese Message sollte gerufen werden, wenn ein Headereintrag verändert 
// wurde.<nl>Diese Message wird durch die Funktion <f DEX_ReReadHeader> ausgelöst.
// @xref <f DEX_ReReadHeader>
LRESULT ExtDirisWindow :: OnReReadHeader (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	ReReadHeader();
	ReReadCaption();

return TRUE;
}

// DEX_FINDIDENTFROMNAME: Ident über PBDNamen finden --------------------------
typedef struct tagFINDIDENTKTEXT {
	char *m_pText;
	ULONG m_lIdent;
	ExtDirisWindow *m_pW;
	bool m_fIgnoreCase;
	HPROJECT m_hPr;
} FINDIDENTKTEXT;

extern "C" bool EXPORTTRIAS PASCAL FindIdentKText (long lIdent, bool, void *pData)
{
PBDDATA pbdData;
char cbKText[33];
FINDIDENTKTEXT *pFIT = (FINDIDENTKTEXT *)pData;

	memset (cbKText, '\0', sizeof(cbKText));

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = cbKText;
	pbdData.pbdKTextLen = sizeof (cbKText);
	if ((pFIT -> m_pW -> OnQueryPBDData (pFIT -> m_hPr, (DWORD)&pbdData) == EC_OKAY)) {
		if (pFIT -> m_fIgnoreCase) {
			if (!stricmp (cbKText, pFIT -> m_pText)) {
				pFIT -> m_lIdent = lIdent;
				return FALSE;		// gefunden, also abbrechen
			}
		} else if (!strcmp (cbKText, pFIT -> m_pText)) {
			pFIT -> m_lIdent = lIdent;
			return FALSE;		// gefunden, also abbrechen
		}
	}
			
return TRUE;	// immer weiter suchen
}

LRESULT ExtDirisWindow :: OnFindIdentFromNameHelper (HPROJECT hPr, char *pName, bool fIgnoreCase)
{
	if (!IsValidActiveView())
		return LRESULT(0L);

	TX_ASSERT(TIsValidString(pName));

// Pbd enumerieren und nach den gegeben KurzText suchen
CActDB ActPBD (DBO().PbdDB());

	if (!ActPBD) return 0L;		// keine PBD gegeben

FINDIDENTKTEXT FIT;

	FIT.m_pText = pName;
	FIT.m_lIdent = 0L;
	FIT.m_pW = this;
	FIT.m_fIgnoreCase = fIgnoreCase;
	FIT.m_hPr = hPr;
	DBO().PbdDB().EnumPBDData ('i', (ENUMLONGKEYPROC)FindIdentKText, 
				   (void *)&FIT);

return LRESULT(FIT.m_lIdent);
}

// @msg DEX_FINDIDENTFROMNAME | Mit dieser Message an <tr> ist es möglich über 
// einen Objektklassennamen (Kurztext) den zugehörigen Identifikator (Schlüssel)
// zu finden.
// @parm char * | pClassName | Zeichenkette, die den Namen der Objektklasse
// (Kurztext) enthält, für die der Identifikator (Schlüssel) gesucht wird.
// @rdesc Liefert den gesuchten Identifikator oder Null, wenn kein entsprechender
// Identifikator gefunden werden konnte.
// @comm Diese Message enumeriert intern alle Identifikatoren der aktuellen
// Beschreibungsdatenbasis und versucht über den gegebenen Text den zugehörigen 
// Identifikator zu finden.
// @comm Diese Message wird durch die Funktion <f DEX_GetIdentFromClassName> ausgelöst.
// @xref <f DEX_GetIdentFromClassName>
LRESULT ExtDirisWindow :: OnFindIdentFromName (HPROJECT hPr, LPARAM lParam)
{
	return OnFindIdentFromNameHelper (hPr, (char *)lParam, false);
}

// @msg DEX_FINDIDENTFROMNAMECI | Mit dieser Message an <tr> ist es möglich über 
// einen Objektklassennamen (Kurztext) den zugehörigen Identifikator (Schlüssel)
// zu finden. Bei der Suche wird Groß-/Kleinschreibung ignoriert.
// @parm char * | pClassName | Zeichenkette, die den Namen der Objektklasse
// (Kurztext) enthält, für die der Identifikator (Schlüssel) gesucht wird.
// @rdesc Liefert den gesuchten Identifikator oder Null, wenn kein entsprechender
// Identifikator gefunden werden konnte.
// @comm Diese Message enumeriert intern alle Identifikatoren der aktuellen
// Beschreibungsdatenbasis und versucht über den gegebenen Text den zugehörigen 
// Identifikator zu finden. Groß-/Kleinschreibung des Namens der Objektklasse
// wird dabei ignoriert.
// @comm Diese Message wird durch die Funktion <f DEX_GetIdentFromClassNameCI> ausgelöst.
// @xref <f DEX_GetIdentFromClassNameCI>, <f DEX_GetIdentFromClassName>
LRESULT ExtDirisWindow :: OnFindIdentFromNameCI (HPROJECT hPr, LPARAM lParam)
{
	return OnFindIdentFromNameHelper (hPr, (char *)lParam, true);
}

// DEX_FINDMCODEFROMNAME: MCode über PBDNamen finden --------------------------
typedef struct tagFINDMCODEKTEXT {
	char *m_pText;
	ULONG m_lMCode;
	ExtDirisWindow *m_pW;
	bool m_fIgnoreCase;
	HPROJECT m_hPr;
} FINDMCODEKTEXT;

extern "C" bool EXPORTTRIAS PASCAL FindMCodeKText (long lMCode, bool, void *pData)
{
PBDDATA pbdData;
char cbKText[33];
FINDMCODEKTEXT *pFIT = (FINDMCODEKTEXT *)pData;

	memset (cbKText, '\0', sizeof(cbKText));

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = lMCode;
	pbdData.pbdKText = cbKText;
	pbdData.pbdKTextLen = sizeof (cbKText);
	if ((pFIT -> m_pW -> OnQueryPBDData (pFIT -> m_hPr, (DWORD)&pbdData) == EC_OKAY)) {
		if (pFIT -> m_fIgnoreCase) {
			if (!stricmp (cbKText, pFIT -> m_pText)) {
				pFIT -> m_lMCode = lMCode;
				return FALSE;		// gefunden, also abbrechen
			}
		} else if (!strcmp (cbKText, pFIT -> m_pText)) {
			pFIT -> m_lMCode = lMCode;
			return FALSE;		// gefunden, also abbrechen
		}
	}
		
return TRUE;	// immer weiter suchen
}

LRESULT ExtDirisWindow :: OnFindMCodeFromNameHelper (HPROJECT hPr, char *pName, bool fIgnoreCase)
{
	if (!IsValidActiveView())
		return LRESULT(0L);

	TX_ASSERT(TIsValidString(pName));

// Pbd enumerieren und nach den gegeben KurzText suchen
CActDB ActPBD (DBO().PbdDB());

	if (!ActPBD) return 0L;		// keine PBD gegeben

FINDMCODEKTEXT FIT;

	FIT.m_pText = pName;
	FIT.m_lMCode = 0L;
	FIT.m_pW = this;
	FIT.m_fIgnoreCase = fIgnoreCase;
	FIT.m_hPr = hPr;
	DBO().PbdDB().EnumPBDData ('m', (ENUMLONGKEYPROC)FindMCodeKText, 
				   (void *)&FIT);

return LRESULT(FIT.m_lMCode);
}

// @msg DEX_FINDMCODEFROMNAME | Mit dieser Message an <tr> ist es möglich über 
// einen Merkmalsnamen (Kurztext) den zugehörigen Merkmalscode (Schlüssel)
// zu finden.
// @parm char * | pFeatureName | Zeichenkette, die den Merkmalsnamen
// (Kurztext) enthält, für die der Merkmalscode (Schlüssel) gesucht wird.
// @rdesc Liefert den gesuchten Merkmalscode oder Null, wenn kein entsprechendes
// Merkmal gefunden werden konnte.
// @comm Diese Message enumeriert intern alle Merkmalsbeschreibungen der aktuellen
// Beschreibungsdatenbasis und versucht über den gegebenen Text den zugehörigen 
// Merkmalscode zu finden.
// @comm Diese Message wird durch die Funktion <f DEX_GetMCodeFromFeatureName> ausgelöst.
// @xref <f DEX_GetMCodeFromFeatureName>
LRESULT ExtDirisWindow :: OnFindMCodeFromName (HPROJECT hPr, LPARAM lParam)
{
	return OnFindMCodeFromNameHelper (hPr, (char *)lParam, false);
}

// @msg DEX_FINDMCODEFROMNAMECI | Mit dieser Message an <tr> ist es möglich über 
// einen Merkmalsnamen (Kurztext) den zugehörigen Merkmalscode (Schlüssel)
// zu finden. Bei der Suche wird Groß-/Kleinschreibung ignoriert.
// @parm char * | pFeatureName | Zeichenkette, die den Merkmalsnamen
// (Kurztext) enthält, für die der Merkmalscode (Schlüssel) gesucht wird.
// @rdesc Liefert den gesuchten Merkmalscode oder Null, wenn kein entsprechendes
// Merkmal gefunden werden konnte.
// @comm Diese Message enumeriert intern alle Merkmalsbeschreibungen der aktuellen
// Beschreibungsdatenbasis und versucht über den gegebenen Text den zugehörigen 
// Merkmalscode zu finden. Groß-/Kleinschreibung des Merkmalsnamens
// wird dabei ignoriert.
// @comm Diese Message wird durch die Funktion <f DEX_GetMCodeFromFeatureNameCI> ausgelöst.
// @xref <f DEX_GetMCodeFromFeatureNameCI>, <f DEX_GetMCodeFromFeatureName>
LRESULT ExtDirisWindow :: OnFindMCodeFromNameCI (HPROJECT hPr, LPARAM lParam)
{
	return OnFindMCodeFromNameHelper (hPr, (char *)lParam, true);
}

// DEX_DELETEIDENT: Alle Objekte eines Idents löschen -------------------------
// @msg DEX_DELETEIDENT | Mit dieser Message an <tr> werden alle Objekte mit
// einem gegebenen Identifikator physisch aus der Datenbasis gelöscht.
// @parm ULONG | lIdent | Identifikator, dessen Objekte aus der datenbasis gelöscht 
// werden sollen.
// @rdesc Diese Message liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.<nl>Das Löschen der Objekte erfolgt vollständig und ist
// nicht rückgängig zu machen. Es erfolgt keine weitere Rückfrage über die
// Nutzeroberfläche.
// @comm Diese Message wird durch die Funktion <f DEX_DeleteAllIdentObjects> ausgelöst.
// @xref <f DEX_DeleteAllIdentObjects>

bool AddObjects (ObjFeld &rObjs, long lIdent, short iOTyp);

LRESULT ExtDirisWindow :: OnDeleteIdent (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	TX_ASSERT(IsValidIdent((LONG)lParam));

	if (DEXN_DeletingIdent (lParam)) return LRESULT(false);

CActDB ActDB (DBO().DB());
ObjFeld Objs;

	if (!AddObjects (Objs, lParam, OTPunkt|OTLinie|OTFlaeche|OTText))
		return LRESULT(false);

	if (Objs.Count()) {
	CRing r(Objs);
		
		for (r.First(); r.Valid(); r.Next()) {
		ObjNummerLock l(r);
			
			TX_ASSERT(NULL != (ObjNummer *)l);
			DEX_DeleteObject (l -> _ON);
		}
		DEX_RefreshLegend();
	}
	DEXN_IdentDeleted (lParam);

return LRESULT(true);
}

// DEX_VIEWCREATE: Leere Sicht erzeugen ---------------------------------------
// @msg DEX_VIEWCREATE | Mit dieser Message an <tr> kann eine Ansicht erzeugt 
// werden. 
// @parm char * | pViewName | Der Name der neu zu erzeugenden Sicht.
// @rdesc Diese Message liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.Wenn die gegebene Ansicht bereits im aktuellen 
// Projekt existiert, dann wird diese Ansicht gelöscht und durch eine leere 
// neue Ansicht mit diesem Namen ersetzt.
// Diese Message wird durch die Funktion <f DEX_CreateView> ausgelöst.
// @xref <f DEX_CreateView>, <f DEX_CreateViewOpt>
LRESULT ExtDirisWindow :: OnViewCreate (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	TX_ASSERT(TIsValidString((char *)lParam));

CActDB ActDB (DBO().DB());
Sicht S (DBO().DB(), (char *)lParam);

	if (EC_OKAY == S.CreateView()) {
	// neue Ansicht ins Menu einhängen
		if (DBO().AddItemToSightMenu (MainMenu(), (char *)lParam))
			DrawMenuBar (Handle (API_WINDOW_HWND));

	// Die Welt von diesem Ereignis in Kenntnis setzen
	VIEWCREATED VC;

		INITSTRUCT (VC, VIEWCREATED);
		VC.m_pTarget = g_cbNil;
		VC.m_pNewName = (char *)lParam;
		DEXN_SightCreated(VC);

		return (CVCreated);
	}

	return LRESULT(CVError);
}

// DEX_VIEWCREATEOPT: Leere Sicht erzeugen ---------------------------------------
// @msg DEX_VIEWCREATEOPT | Mit dieser Message an <tr> kann eine Ansicht erzeugt 
// werden. 
// @parm char * | pViewName | Der Name der neu zu erzeugenden Sicht.
// @rdesc Diese Message liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>. Wenn die gegebene Ansicht bereits im aktuellen 
// Projekt existiert, dann macht diese Message garnichts.
// @comm Diese Message wird durch die Funktion <f DEX_CreateViewOpt> ausgelöst.
// @xref <f DEX_CreateViewOpt>, <f DEX_CreateView>
LRESULT ExtDirisWindow :: OnViewCreateOpt (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	TX_ASSERT(TIsValidString((char *)lParam));

CActDB ActDB (DBO().DB());
Sicht S (DBO().DB(), (char *)lParam);
ErrCode RC = S.CreateView(false);

	if (RC == WC_EXISTS) return LRESULT(CVExists);
	if (RC == EC_OKAY) {
	// neue Ansicht ins Menu einhängen
		if (DBO().AddItemToSightMenu (MainMenu(), (char *)lParam))
			DrawMenuBar (Handle (API_WINDOW_HWND));

	// Die Welt von diesem Ereignis in Kenntnis setzen
	VIEWCREATED VC;

		INITSTRUCT (VC, VIEWCREATED);
		VC.m_pTarget = g_cbNil;
		VC.m_pNewName = (char *)lParam;
		DEXN_SightCreated(VC);

		return LRESULT(CVCreated);
	}
	
return LRESULT(CVError);
}

// DEX_DELETEIDENTFROMVIEW: Ident aus der Sicht herauslösen -------------------
// @msg DEX_DELETEIDENTFROMVIEW | Mit dieser Message an <tr> können einzelne
// Identifikator/Objekttyp-Kombinationen aus einer Sicht herausgelöscht werden.
// @parm VIEWIDENTOBJECT * | pViewIdentObject | Ein Zeiger auf eine Struktur vom
// Typ <t VIEWIDENTOBJECT>. Das Feld <e VIEWIDENTOBJECT.m_pView> enthält die zu bearbeitende Ansicht
// (bzw. NULL, für die aktuelle Ansicht), das Feld <e VIEWIDENTOBJECT.m_lIdent> den zu löschenden 
// Identifikator und das Feld <e VIEWIDENTOBJECT.m_iOTyp> eine Kombination der zu behandelnden 
// Objekttypen. Das Feld <e VIEWIDENTOBJECT.m_lONr> wird ignoriert.
// @rdesc Diese Message liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @comm Diese Message wird durch die Funktion <f DEX_RemoveIdentFromView> ausgelöst.
// @xref <f DEX_RemoveIdentFromView>, <t VIEWIDENTOBJECT>
LRESULT ExtDirisWindow :: OnRemoveIdentFromView (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

VIEWIDENTOBJECT *pVIO = (VIEWIDENTOBJECT *)lParam;

	TX_ASSERT_POINTER(pVIO, VIEWIDENTOBJECT);
	TX_ASSERT(sizeof(VIEWIDENTOBJECT) == pVIO -> dwSize);
	TX_ASSERT(NULL == pVIO -> m_pView || TIsValidString(pVIO -> m_pView));
	TX_ASSERT(IsValidIdent((LONG)pVIO -> m_lIdent));
	TX_ASSERT(0L == pVIO -> m_lONr);	// to be ignored

char cbView[64];

	if (pVIO -> m_pView == NULL) {
	// aktuelle Sicht verwenden
		if (!DBO().GetActiveSightName (cbView)) 
			return LRESULT(false);
		pVIO -> m_pView = cbView;
	}

CActDB ActDB (DBO().DB());
ErrInstall EI (WC_NOTFOUND);
Sicht S (DBO().DB(), pVIO -> m_pView);
bool fResult = S.SatzNr() > 0;		// Sicht existiert
ErrCode RC = EC_OKAY;

	if (fResult && pVIO -> m_iOTyp & OTPunkt) {
		RC = S.DelIDfromSight (pVIO -> m_lIdent, VTPunkt);
		fResult = (RC == EC_OKAY) || (RC == WC_NOTFOUND);
	}
	if (fResult && pVIO -> m_iOTyp & OTLinie) {
		RC = S.DelIDfromSight (pVIO -> m_lIdent, VTLinie);
		fResult = (RC == EC_OKAY) || (RC == WC_NOTFOUND);
	}
	if (fResult && pVIO -> m_iOTyp & OTFlaeche) {
		RC = S.DelIDfromSight (pVIO -> m_lIdent, VTFlaeche);
		fResult = (RC == EC_OKAY) || (RC == WC_NOTFOUND);
	}
	if (fResult && pVIO -> m_iOTyp & OTText) {
		RC = S.DelIDfromSight (pVIO -> m_lIdent, VTText);
		fResult = (RC == EC_OKAY) || (RC == WC_NOTFOUND);
	}

return LRESULT(fResult);
}

// DEX_VIEWRENAME: Sicht umbenennen -------------------------------------------
// @msg DEX_VIEWRENAME | Mit dieser Message an <tr> kann eine existierende
// Ansicht umbenannt werden.
// @parm RENAMEVIEW * | pRenameView | Ein Zeiger auf eine Struktur vom 
// Typ <t RENAMEVIEW>.
// @rdesc Liefert einen <t bool> -Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @comm Diese Message wird durch die Funktion <f DEX_RenameView> ausgelöst.
// @xref <f DEX_RenameView>, <t RENAMEVIEW>
LRESULT ExtDirisWindow :: OnViewRename (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

RENAMEVIEW *pRV = (RENAMEVIEW *)lParam;

	TX_ASSERT_POINTER(pRV, RENAMEVIEW);
	TX_ASSERT(sizeof(RENAMEVIEW) == pRV -> dwSize);
	TX_ASSERT(NULL == pRV -> m_pOldName || TIsValidString(pRV -> m_pOldName));
	TX_ASSERT(TIsValidString(pRV -> m_pNewName));

char cbView[64];
const char *pView = pRV -> m_pOldName;

	if (pView == NULL) {
	// aktuelle Sicht verwenden
		if (!DBO().GetActiveSightName (cbView)) 
			return LRESULT(false);
		pView = cbView;
	}

CActDB ActDB (DBO().DB());
ErrInstall EI (WC_NOTFOUND);
Sicht S (DBO().DB(), pView);

	return LRESULT(S.SatzNr() > 0 && S.Rename (pRV -> m_pNewName) == EC_OKAY);
}

// DEX_HASVIEWIDENT: Testen, ob Ident zu dieser Sicht gehört ------------------
// @msg DEX_HASVIEWIDENT | Diese Message an <tr> wird dazu verwendet, um 
// abzufragen, ob eine bestimmte Identifikator/Objekttyp-Kombination zu einer 
// Ansicht gehört.
// @parm VIEWIDENTOBJECT * | pViewIdentObject | Ein Zeiger auf eine Struktur vom
// Typ <t VIEWIDENTOBJECT>. Das Feld <e VIEWIDENTOBJECT.m_pView> enthält die zu bearbeitende Ansicht
// (bzw. NULL, für die aktuelle Ansicht), das Feld <e VIEWIDENTOBJECT.m_lIdent> den zu untersuchenden
// Identifikator und das Feld <e VIEWIDENTOBJECT.m_iOTyp> eine Kombination der zu behandelnden 
// Objekttypen. Das Feld <e VIEWIDENTOBJECT.m_lONr> wird ignoriert.
// @rdesc Diese Message liefert einen <t bool> - Wert, wenn Objekte der gegebenen
// Objekttypen und des gegebenen Identifikators zur Sicht gehören <t true>, 
// anderenfalls und im Fehlerfall <t false>.
// @comm Diese Message wird durch die Funktion <f DEX_ViewHasIdent> ausgelöst.
// @xref <f DEX_ViewHasIdent>, <t VIEWIDENTOBJECT>
LRESULT ExtDirisWindow :: OnHasViewIdent (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

VIEWIDENTOBJECT *pVIO = (VIEWIDENTOBJECT *)lParam;

	TX_ASSERT_POINTER(pVIO, VIEWIDENTOBJECT);
	TX_ASSERT(sizeof(VIEWIDENTOBJECT) == pVIO -> dwSize);
	TX_ASSERT(NULL == pVIO -> m_pView || TIsValidString(pVIO -> m_pView));
	TX_ASSERT(IsValidIdent((LONG)pVIO -> m_lIdent));
	TX_ASSERT(0L == pVIO -> m_lONr);	// to be ignored

char cbView[64];
char *pView = pVIO -> m_pView;

	if (pView == NULL) {
	// aktuelle Sicht verwenden
		if (!DBO().GetActiveSightName (cbView)) 
			return LRESULT(false);
		pView = cbView;
	}

CActDB ActDB (DBO().DB());
ErrInstall EI (WC_NOTFOUND);
Sicht S (DBO().DB(), pView);
bool fResult = S.SatzNr() > 0;		// Sicht existiert

	if (!fResult) return LPARAM(false);
	
ErrCode RC = EC_OKAY;

	fResult = false;	
	if (pVIO -> m_iOTyp & OTPunkt) {
		RC = S.GetIDfromSight (pVIO -> m_lIdent, NULL, VTPunkt);
		fResult = (RC == EC_OKAY);
	}
	if (!fResult && pVIO -> m_iOTyp & OTLinie) {
		RC = S.GetIDfromSight (pVIO -> m_lIdent, NULL, VTLinie);
		fResult = (RC == EC_OKAY);
	}
	if (!fResult && pVIO -> m_iOTyp & OTFlaeche) {
		RC = S.GetIDfromSight (pVIO -> m_lIdent, NULL, VTFlaeche);
		fResult = (RC == EC_OKAY);
	}
	if (!fResult && pVIO -> m_iOTyp & OTText) {
		RC = S.GetIDfromSight (pVIO -> m_lIdent, NULL, VTText);
		fResult = (RC == EC_OKAY);
	}

return LRESULT(fResult);
}

// DEX_HASVIEWOBJECT: Testen, ob Objekt zu dieser Sicht gehört ----------------
// @msg DEX_HASVIEWOBJECT | Diese Message an <tr> wird dazu verwendet, um 
// abzufragen, ob ein bestimmtes Objekt zu einer Ansicht gehört.
// @parm VIEWIDENTOBJECT * | pViewIdentObject | Ein Zeiger auf eine Struktur vom
// Typ <t VIEWIDENTOBJECT>. Das Feld <e VIEWIDENTOBJECT.m_pView> enthält die zu bearbeitende Ansicht
// (bzw. NULL, für die aktuelle Ansicht), das Feld <e VIEWIDENTOBJECT.m_lONr> die ObjektNummer
// des zu untersuchenden Objektes. Die Felder <e VIEWIDENTOBJECT.m_lIdent> und <e VIEWIDENTOBJECT.m_iOTyp> 
// werden ignoriert.
// @rdesc Diese Message liefert einen <t bool> - Wert, wenn das gegebene Objekt 
// zur Sicht gehört <t true>, anderenfalls und im Fehlerfall <t false>.
// @comm Diese Message wird durch die Funktion <f DEX_ViewHasObject> ausgelöst.
// @xref <f DEX_ViewHasObject>, <t VIEWIDENTOBJECT>
LRESULT ExtDirisWindow :: OnHasViewObject (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

VIEWIDENTOBJECT *pVIO = (VIEWIDENTOBJECT *)lParam;

	TX_ASSERT_POINTER(pVIO, VIEWIDENTOBJECT);
	TX_ASSERT(sizeof(VIEWIDENTOBJECT) == pVIO -> dwSize);
	TX_ASSERT(NULL == pVIO -> m_pView || TIsValidString(pVIO -> m_pView));
	TX_ASSERT(0L == pVIO -> m_lIdent);	// not given
	TX_ASSERT(IsValidONr(DBO().DB().DBDesc(), pVIO -> m_lONr));

	pVIO -> m_lIdent = DBO().RetrieveIdent (pVIO -> m_lONr);
	pVIO -> m_iOTyp =  OTypToBits (DBO().RetrieveObjTyp (pVIO -> m_lONr));

return OnHasViewIdent(hPr, lParam);
}

// @msg DEX_HASPROJECTVIEW | Diese Message an <tr> wird dazu verwendet, zu testen, 
// ob eine gegebene Ansicht im aktuellen Projekt definiert ist.
// @parm char * | pViewName | Zeiger auf den Namen der Ansicht, deren Existenz im 
// aktuelle Projekt überprüft werden soll.
// @rdesc Diese Message liefert einen <t bool> - Wert, wenn das gegebene Objekt 
// zur Sicht gehört <t true>, anderenfalls und im Fehlerfall <t false>.
// @comm Diese Message wird durch die Funktion <f DEX_ProjectHasView> ausgelöst.
// @xref <f DEX_ProjectHasView>
LRESULT ExtDirisWindow :: OnHasProjectView (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	TX_ASSERT(TIsValidString((char *)lParam));

ErrInstall EI (WC_NOTFOUND);
Sicht S (DBO().DB(), (char *)lParam);

	return LRESULT(S.SatzNr() > 0);		// Sicht existiert
}

// @msg DEX_IDENTADDTOVIEW | Diese Message an <tr> wird dazu verwendet, um einen 
// Identifikator zu einer Ansicht hinzuzufügen.
// @rdesc Liefert einen <t bool> -Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @parm VIEWIDENTOBJECT * | pViewIdentOTyp | Pointer auf eine Struktur vom 
// Typ <t VIEWIDENTOBJECT>, die die notwendigen Informationen enthält.
// Das Feld <e VIEWIDENTOBJECT.m_pView> enthält die zu bearbeitende Ansicht
// (bzw. NULL, für die aktuelle Ansicht), das Feld <e VIEWIDENTOBJECT.m_lIdent> den zu untersuchenden
// Identifikator und das Feld <e VIEWIDENTOBJECT.m_iOTyp> eine Kombination der zu behandelnden 
// Objekttypen. Das Feld <e VIEWIDENTOBJECT.m_lONr> wird ignoriert.
// @comm Diese Message wird durch die Funktion <f DEX_AddIdentToView> ausgelöst.
// @xref <f DEX_AddIdentToView>
LRESULT ExtDirisWindow :: OnAddIdentToView (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

VIEWIDENTOBJECT *pVIO = (VIEWIDENTOBJECT *)lParam;

	TX_ASSERT_POINTER(pVIO, VIEWIDENTOBJECT);
	TX_ASSERT(sizeof(VIEWIDENTOBJECT) == pVIO -> dwSize);
	TX_ASSERT(NULL == pVIO -> m_pView || TIsValidString(pVIO -> m_pView));
	TX_ASSERT(IsValidIdent((LONG)pVIO -> m_lIdent));
	TX_ASSERT(0L == pVIO -> m_lONr);	// to be ignored

char cbView[64];
char *pView = pVIO -> m_pView;

	if (pView == NULL) {
	// aktuelle Sicht verwenden
		if (!DBO().GetActiveSightName (cbView)) 
			return LRESULT(false);
		pView = cbView;
	}

CActDB ActDB (DBO().DB());
ErrInstall EI (WC_NOTFOUND);
Sicht S (DBO().DB(), pView);
bool fResult = false;
ErrCode RC = EC_OKAY;

	if (pVIO -> m_iOTyp & OTPunkt) {
		RC = S.AddIDtoSight (pVIO -> m_lIdent, NULL, VTPunkt);
		fResult = (RC == EC_OKAY);
	}
	if (fResult && pVIO -> m_iOTyp & OTLinie) {
		RC = S.AddIDtoSight (pVIO -> m_lIdent, NULL, VTLinie);;
		fResult = (RC == EC_OKAY);
	}
	if (fResult && pVIO -> m_iOTyp & OTFlaeche) {
		RC = S.AddIDtoSight (pVIO -> m_lIdent, NULL, VTFlaeche);
		fResult = (RC == EC_OKAY);
	}
	if (fResult && pVIO -> m_iOTyp & OTText) {
		RC = S.AddIDtoSight (pVIO -> m_lIdent, NULL, VTText);
		fResult = (RC == EC_OKAY);
	}

return LRESULT(fResult);
}

// DEX_RCTOOC -----------------------------------------------------------------
LRESULT ExtDirisWindow :: OnRCtoOC (HPROJECT, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

COORDTRANSFORM *pCTF = (COORDTRANSFORM *)lParam;

	TX_ASSERT_POINTER(pCTF, COORDTRANSFORM);
	TX_ASSERT(sizeof(COORDTRANSFORM) == pCTF -> dwSize);
	TX_ASSERT(TIsValidAddress(pCTF -> m_Pts, 2*sizeof(long), true));
	TX_ASSERT(TIsValidAddress(pCTF -> m_rcPts, 2*sizeof(double)));

	return LRESULT(DBO().ConvertRCToOC (pCTF -> m_rcPts[0], pCTF -> m_rcPts[1], pCTF -> m_Pts[0], pCTF -> m_Pts[1]));
}

// DEX_OCTORC -----------------------------------------------------------------
LRESULT ExtDirisWindow :: OnOCtoRC (HPROJECT, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

COORDTRANSFORM *pCTF = (COORDTRANSFORM *)lParam;

	TX_ASSERT_POINTER(pCTF, COORDTRANSFORM);
	TX_ASSERT(sizeof(COORDTRANSFORM) == pCTF -> dwSize);
	TX_ASSERT(TIsValidAddress(pCTF -> m_Pts, 2*sizeof(long)));
	TX_ASSERT(TIsValidAddress(pCTF -> m_rcPts, 2*sizeof(double), true));

	return LRESULT(DBO().ConvertOCToRC (pCTF -> m_Pts[0], pCTF -> m_Pts[1], pCTF -> m_rcPts[0], pCTF -> m_rcPts[1]));
}

// DEX_ISOBJWINDOW ------------------------------------------------------------
// @msg DEX_ISOBJWINDOW | Diese Message an <tr> wird dazu verwendet, um 
// festzustellen, ob das Fenster, dessen Handle (HWND) übergeben wurde ein 
// gültiges Objektrecherche-Fenster ist.
// @rdesc Liefert einen <t bool> -Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @parm HWND | hORWnd | Zu untersuchendes Fensterhandle
// @comm Diese Message wird durch die Funktion <f DEX_IsORWindow> ausgelöst.
// @xref <f DEX_IsORWindow>
LRESULT ExtDirisWindow :: OnIsORWindow (HPROJECT hPr, LPARAM lParam)
{
	TX_ASSERT(IsWindow((HWND)lParam));

	return LRESULT(GetORWindow (HWND(lParam)) != NULL ? true : false);
}

// DEX_OBJECTREPAINT ----------------------------------------------------------
LRESULT ExtDirisWindow :: OnRePaintObject (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	TX_ASSERT(IsValidONr(DBO().DB().DBDesc(), (LONG)lParam));

CTable t(DBO().Shapes().ObjNumTree());
VisInfo *pVI = (VisInfo *)DEX_SetAttributes (lParam);
bool fResult = false;

	if (t.Find (&lParam)) {		// nur zeichnen, wenn geladen
	ExtShapeObjectLock l(t);

		TX_ASSERT(NULL != (ExtShapeObject *)l);

	short iOldDCInit = l -> FullDCInit();

		l -> FullDCInit() = FDC_FullInit; // | FDC_ActivateOnly;
		DrawEx (l, (DWORD)&DBO());
		l -> FullDCInit() = iOldDCInit;
		fResult = true;		// Erfolg melden
	}

// Attribute wieder rücksetzen
RESETATTRDATA RAD;

	RAD.lONr = lParam;
	RAD.pVI = pVI;
	DEX_ResetAttributes (&RAD);

return LRESULT(fResult);
}

// DEX_ENUMIDENTVIEWSEX -------------------------------------------------------
LRESULT ExtDirisWindow :: OnEnumIdentViewsEx (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

#if defined(_DEBUG)
ENUMLONGKEYEX *pELK = (ENUMLONGKEYEX *)lParam;

	TX_ASSERT_POINTER(pELK, ENUMLONGKEYEX);
	TX_ASSERT(TIsValidAddress(pELK -> eFcn, 1, false));
	TX_ASSERT(IsValidIdent(pELK -> eKey));
#endif // _DEBUG

return LRESULT(DBO().EnumIdentViewsEx ((ENUMLONGKEYEX *)lParam));
}


// @msg DEX_QUERYADMINMODE | Diese Message an <tr> wird dazu verwendet, um die
// erweiterten Zugriffsrechte des aktuellen Nutzers abzufragen.
// @rdesc Liefert einen <t bool> -Wert, der angibt, ob der aktuelle Nutzer über 
// erweiterte Zugriffsrechte verfügt über nicht.
// @comm Diese Message wird durch die Funktion <f DEX_QueryMode> ausgelöst und
// ist nur unter WindowsNT und Windows 95 verfügbar.
// @xref <f DEX_QueryMode>, <m DEX_SETADMINMODE>
LRESULT ExtDirisWindow :: OnQueryAdminMode (HPROJECT, LPARAM)
{
DWORD dwResult = g_fSystemAdm ? QMSysAdmin : 0;

	dwResult |= g_fAutomation ? QMAutomation : 0;
	dwResult |= g_fStartByOle ? QMEmbedding : 0;
	dwResult |= g_fTip ? QMTipOfTheDay : 0;
	dwResult |= g_fShowSysFeatures ? QMShowSysFeatures : 0;

return dwResult;
}

// @msg DEX_SETADMINMODE | Diese Message an <tr> wird dazu verwendet, um die
// erweiterten Zugriffsrechte des aktuellen Nutzers zu setzen.
// @parm bool | fAdminFlag | Enthält den neuen Wert, der dem SystemAdminFlag des
// aktuellen Nutzers zugewiesen werden soll.
// @rdesc Liefert einen <t bool> -Wert, der angibt, ob der aktuelle Nutzer über 
// erweiterte Zugriffsrechte verfügt hatte über nicht.
// @comm Diese Message wird durch die Funktion <f DEX_SetMode> ausgelöst und
// ist nur unter WindowsNT und Windows 95 verfügbar.
// @comm Jetzt ist diese Funktion auch unter Win31 und Win32s verfügbar greift 
// jedoch nicht wie unter Windows95/WindowsNT auf die Registry, sondern 
// auf die TRIAS.INI (Section [Parameters], Key SystemAdministration=1).
// @xref <f DEX_SetMode>, <m DEX_QUERYADMINMODE>
LRESULT ExtDirisWindow :: OnSetAdminMode (HPROJECT hPr, LPARAM lParam)
{
bool fOldFlag = g_fSystemAdm;

	g_fSystemAdm = (lParam & QMSysAdmin) ? true : false;
	g_fShowSysFeatures = (lParam & QMShowSysFeatures) ? true : false;

#if defined(WIN32)
#if defined(ENABLE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
	{
	CCurrentUser regCfg (g_cbRegConfig);

		if (regCfg.isValid()) {
		DWORD dwData = g_fSystemAdm;

			regCfg.SetDWORD (g_cbSysAdmin, dwData);
			
			dwData = g_fShowSysFeatures;
			regCfg.SetDWORD (g_cbShowSysFeatures, dwData);
		}
	} 
#if defined(ENABLE_WIN32S_CODE)
	else
#endif // ENABLE_WIN32S_CODE
#endif // WIN32
#if defined(ENABLE_WIN32S_CODE)
	{
	ResString Profile (IDS_PROFILE, 13);
	ResString IrisPars (IDS_IRISPARS, 13);

		if (g_fSystemAdm) {	// Eintrag setzen
			WritePrivateProfileString (IrisPars, 
				g_cbSysAdmin, "1", Profile);
		} else {		// Eintrag löschen
			WritePrivateProfileString (IrisPars, 
				g_cbSysAdmin, NULL, Profile);
		}
	}
#endif // ENABLE_WIN32S_CODE

return fOldFlag;
}

// DEX_ONSETGEODBDIRTY
LRESULT ExtDirisWindow :: OnSetDirtyGeoDB (HPROJECT hPr, LPARAM lParam)
{
	if (!DBO().DB().isOpened())		// evtl. während der SchließPhase
		return LRESULT(false);
	DBO().DB().SetDirty (lParam ? true : false);

return (LRESULT)true;	// makes no sense
}

// DEX_ENUMALLPROJECTS
LRESULT ExtDirisWindow :: OnEnumProjects  (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView()) 
		return LRESULT(false);

ENUMNOKEY *pK = (ENUMNOKEY *)lParam;

	TX_ASSERT_POINTER(pK, ENUMNOKEY);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));

return EnumProjects (pK);
}

// DEX_PROJECTHANDLEFROMNAME
LRESULT ExtDirisWindow :: OnGetProjectHandle  (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(NULL);

	TX_ASSERT(TIsValidString((char *)lParam));

	return (LRESULT)(void *)GetProjectHandle ((LPCSTR)lParam);
}

// DEX_PROJECTMAKEACTIVE
LRESULT ExtDirisWindow :: OnMakeProjectActive  (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(NULL);

	TX_ASSERT(NULL != (HPROJECT)lParam);

return (LRESULT)(void *)MakeProjectActive ((HPROJECT)lParam);
}

// DEX_ENUMOBJRECHWNDS
LRESULT ExtDirisWindow :: OnEnumORWindows (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMNOKEYLONG *pK = (ENUMNOKEYLONG *)lParam;

	TX_ASSERT_POINTER(pK, ENUMNOKEYLONG);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));

CActDB ActDB (DBO().DB());

	return EnumORWindows (pK);
}

// DEX_ENUMSELECTEDOBJECTSEX: alle recherchierten Objekte enumerieren -----------
LRESULT ExtDirisWindow :: OnEnumSelObjectsEx (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);
		
ENUMLONGKEYEX *pK = (ENUMLONGKEYEX *)lParam;

	TX_ASSERT_POINTER(pK, ENUMLONGKEYEX);
	TX_ASSERT(TIsValidAddress(pK -> eFcn, 1, false));

// entweder alle ORFenster (eKey == NULL oder gültiges ORFenster
	TX_ASSERT(NULL == pK -> eKey || 
	         (IsWindow((HWND)pK -> eKey) && NULL != GetORWindow((HWND)pK -> eKey)));

	return (LRESULT)EnumSelectedObjectsEx (
			(ENUMNOKEYLONGEXPROC)pK -> eFcn, pK -> ePtr, 
			pK -> eData, (HWND)pK -> eKey
		);
}

// DEX_QUERYIDENTOBJTYPESACTVIEW: liefert Objekttypen eines Idents in der aktuellen Ansicht
LRESULT ExtDirisWindow :: OnGetIdentObjTypesActView (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(0);

return DBO().GetActIdentObjTypes (lParam);
}

// DEX_CAPTIONREREAD: Caption neu generieren ----------------------------------
LRESULT ExtDirisWindow :: OnReReadCaption (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

return ReReadCaption();
}

// DEX_GETGEODBDIRTY: Abfragen, ob gespeichert werden muß ---------------------
LRESULT ExtDirisWindow :: OnIsGeoDBDirty (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

return LRESULT(DBO().DB().isDirty());
}

// DEX_QUERYLEGENDACTIVE
LRESULT ExtDirisWindow :: OnIsLegendActive (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	return LRESULT(LegendeCFlag);
}

// DEX_QUERYOVERVIEWACTIVE
LRESULT ExtDirisWindow::OnIsOverviewActive (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	return LRESULT(OverViewCFlag);
}

// DEX_QUERYCOMPATIBILITYMODE 
LRESULT ExtDirisWindow::OnIsCompatible (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	return LRESULT(DBO().Compatibility());
}

// DEX_MODACTVIEWCONTAINER
LRESULT ExtDirisWindow :: OnSetViewContainer (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	if (0L != lParam) {
		TX_ASSERT(TIsValidAddress((void *)lParam, sizeof(ObjContainer), true));
		return (EC_OKAY == DBO().SetActSichtCont (*(ObjContainer *)lParam));
	}
	return (EC_OKAY == DBO().DelActSichtCont());
}

// DEX_QUERYACTVIEWCONTAINER
LRESULT ExtDirisWindow :: OnGetViewContainer (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	if (0L != lParam) {
		TX_ASSERT(TIsValidAddress((void *)lParam, sizeof(ObjContainer), false));
		return (EC_OKAY == DBO().GetActSichtCont ((ObjContainer *)lParam));
	}

return (LRESULT)DBO().hasSichtCont();
}

#if defined(WIN32)

// DEX_ADDUNDOREDOITEM
LRESULT ExtDirisWindow :: OnAddUndoRedo (HPROJECT hPr, LPARAM lParam)
{
	TX_ASSERT(TIsValidIUnknown((LPUNKNOWN)lParam));
	return (LRESULT)m_pUndoRedo -> AddUndo ((LPUNKNOWN)lParam);
}

// DEX_UNDOLEVELBEGIN 
LRESULT ExtDirisWindow :: OnBeginUndoLevel (HPROJECT hPr, LPARAM lParam)
{
	TX_ASSERT(TIsValidString((char *)lParam));
	return (LRESULT)m_pUndoRedo -> BeginUndoLevel ((LPCTSTR)lParam);
}

// DEX_UNDOLEVELEND 
LRESULT ExtDirisWindow :: OnEndUndoLevel (HPROJECT, LPARAM)
{
	return (LRESULT)m_pUndoRedo -> EndUndoLevel();
}

// DEX_UNDOLEVELCANCEL
LRESULT ExtDirisWindow :: OnCancelUndoLevel (HPROJECT hPr, LPARAM lParam)
{
	return (LRESULT)m_pUndoRedo -> CancelUndoLevel (lParam ? true : false);
}

// DEX_QUERYCANUNDO
LRESULT ExtDirisWindow :: OnQueryCanUndo (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(S_FALSE);

	TX_ASSERT(NULL != m_pUndoRedo);

LPSTR pDesc = NULL;
HRESULT hr = S_FALSE;

	if (m_pUndoRedo -> GetNextUndoDesc(&pDesc) & UNDOREDOCAPS_CANUNDO) {
		if (0L != lParam) {
		LPSTR pAnsi = strtok (pDesc, g_cbUndoDel);	// nur erste Phrase

			if (pAnsi == NULL) pAnsi = pDesc;

			TX_ASSERT(TIsValidAddress((LPSTR)lParam, strlen(pAnsi), false));
			if (pAnsi) strcpy ((LPSTR)lParam, pAnsi);
			else	   strcpy ((LPSTR)lParam, ResString (IDS_UNDOUNKNOWN, 30));
		}
		hr = NOERROR;
	}
	if (pDesc) {
		CoTaskMemFree (pDesc);
		pDesc = NULL;
	}

return LRESULT(hr);
}

// DEX_QUERYCANREDO
LRESULT ExtDirisWindow :: OnQueryCanRedo (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(S_FALSE);

	TX_ASSERT(NULL != m_pUndoRedo);

LPSTR pDesc = NULL;
HRESULT hr = S_FALSE;

	if (m_pUndoRedo -> GetNextRedoDesc(&pDesc) & UNDOREDOCAPS_CANREDO) {
		if (0L != lParam) {
		LPSTR pAnsi = strtok (pDesc, g_cbUndoDel);	// nur erste Phrase

			if (pAnsi == NULL) pAnsi = pDesc;

			TX_ASSERT(TIsValidAddress((LPSTR)lParam, strlen(pAnsi), false));
			if (pAnsi) strcpy ((LPSTR)lParam, pAnsi);
			else	   strcpy ((LPSTR)lParam, ResString (IDS_UNDOUNKNOWN, 30));
		}
		hr = NOERROR;
	}
	if (pDesc) {
		CoTaskMemFree (pDesc);
		pDesc = NULL;
	}

return LRESULT(hr);
}

// DEX_N_SAVESAMESTORAGE
LRESULT ExtDirisWindow :: OnSaveSameStorage (HPROJECT hPr, LPARAM lParam)
{
	return LRESULT(ResultFromScode (E_NOTIMPL));
}

// DEX_N_SAVEOTHERSTORAGE
LRESULT ExtDirisWindow :: OnSaveOtherStorage (HPROJECT hPr, LPARAM lParam)
{
	return LRESULT(ResultFromScode (E_NOTIMPL));
}

// DEX_N_HANDSOFFSTORAGE
LRESULT ExtDirisWindow :: OnHandsOffStorage (HPROJECT hPr, LPARAM lParam)
{
	return LRESULT(ResultFromScode (E_NOTIMPL));
}

// DEX_N_SAVECOMPLETED
LRESULT ExtDirisWindow :: OnSaveCompleted (HPROJECT hPr, LPARAM lParam)
{
	return LRESULT(ResultFromScode (E_NOTIMPL));
}

// DEX_ATTACHPRETRANSLATEMSGPROC
LRESULT ExtDirisWindow :: OnAttachPreTranslateMsgProc (HPROJECT hPr, LPARAM lParam)
{
	return (LRESULT)g_pCurrApp -> AttachPreTranslateProc ((bool (*)(MSG *))lParam);
}

// DEX_ATTACHIDLEPROC
LRESULT ExtDirisWindow :: OnAttachIdleProc (HPROJECT hPr, LPARAM lParam)
{
	return (LRESULT)g_pCurrApp -> AttachIdleProc ((bool (*)(LONG))lParam);
}

LRESULT ExtDirisWindow :: OnQueryActViewWindow (HPROJECT, LPARAM)
{
	if (!IsValidActiveView())
		return LPARAM(NULL);

return LRESULT(m_pView -> Handle (API_WINDOW_HWND));
}

// DEX_MODOBJIDENTEX: Ident eines Objektes ändern (mit Undo) ------------------
LRESULT ExtDirisWindow :: OnModObjectIdentEx (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(EC_NOOPEN);
		
MODOBJIDENT *pMOI = (MODOBJIDENT *)lParam;

	TX_ASSERT_POINTER(pMOI, MODOBJIDENT);
	TX_ASSERT(3*sizeof(long) == pMOI -> dwSize || sizeof(MODOBJIDENT) == pMOI -> dwSize);
	TX_ASSERT(IsValidONr(DBO().DB().DBDesc(), pMOI -> lONr));
	TX_ASSERT(IsValidIdent(pMOI -> lNewIdent));

short iMode = pMOI -> dwSize > 3*sizeof(long) ? pMOI -> iMode : 0;
LPUNDOREDOMODIDENT pIUndo = NULL;
HRESULT hr = UndoCreateInstance (IID_IUndoRedoModIdent, (LPVOID *)&pIUndo);
bool fResult = false;

	if (SUCCEEDED(hr)) 
		hr = pIUndo -> Init (pMOI -> lONr, pMOI -> lNewIdent, 0L, iMode);

	DBO().DB().SetDirty();

long lMCodeNew = RetrieveObjNameMCodeIdent (DBO(), pMOI -> lNewIdent);
long lMCodeOld = RetrieveObjNameMCode (DBO(), pMOI -> lONr);

	if (DBO().ModIdent (pMOI -> lONr, pMOI -> lNewIdent, -1, iMode)) {
	// evtl. Objektnamen umhängen
		if (lMCodeNew != lMCodeNew) {
		char cbBuffer[4096];

			ReadTextMerkmal (TT_Objekt, pMOI -> lONr, lMCodeOld, cbBuffer, sizeof(cbBuffer));
			WriteTextMerkmal (TT_Objekt, pMOI -> lONr, lMCodeOld, NULL);
			WriteTextMerkmal (TT_Objekt, pMOI -> lONr, lMCodeNew, cbBuffer);
		}

		if (hr == NOERROR)
			DEX_AddUndoRedo (pIUndo);
		fResult = true;
	} 
	if (pIUndo) pIUndo -> Release();

return fResult;
}

// DEX_QUERYOBJECTPROPS
LRESULT ExtDirisWindow :: OnGetObjectProps (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	TX_ASSERT(TIsValidAddress ((void *)lParam, sizeof(IUnknown *), true));

// wenn QI schiefgeht, dann ist *lParam sowieso NULL
	m_pEL -> QueryInterface (IID_IObjectProps, (LPVOID *)lParam);

// liefert, ob neu initialisiert werden muß
	return (LPARAM)(m_fMustInitOPFs ? true : false);	
}

// DEX_SETSTRINGMESSAGE
#define WM_SETMESSAGESTRING	0x362	// AFXPRIV.H

LRESULT ExtDirisWindow :: OnSetMessageString (HPROJECT hPr, LPARAM lParam)
{
// an MFC (FakeMFC) weiterleiten
LRESULT lRes = ::SendMessage (Handle(API_WINDOW_HWND), WM_SETMESSAGESTRING, 0, lParam);

	App::Exec(ExecWhileEventWithIdle);	// WM_KICKIDLE
	return lRes;
}

LRESULT ExtDirisWindow::OnSetMessageStringNoKickIdle (HPROJECT hPr, LPARAM lParam)
{
// an MFC (FakeMFC) weiterleiten
	return ::SendMessage (Handle(API_WINDOW_HWND), WM_SETMESSAGESTRING, 0, lParam);
}

// DEX_CANCTFCONFIG
LRESULT ExtDirisWindow::OnCanCTFConfig (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return FALSE;

	return LRESULT(DBO().pCT() -> CanConfig());
}

// DEX_KICKIDLE: IdleLoop rufen
LRESULT ExtDirisWindow::OnKickIdle (HPROJECT hPr, LPARAM lParam)
{
	App::Exec (lParam ? ExecWhileEventWithIdle : ExecIdleOnly);
	return LRESULT(true);
}

// DEX_PROJECTNAMEFROMHANDLE
LRESULT ExtDirisWindow::OnProjectNameFromHandle (HPROJECT, LPARAM lParam)
{
LPSTR pName = (LPSTR)CoTaskMemAlloc (_MAX_PATH+1);

	if (NULL != pName) {
	LPCSTR pcDBName = DBO((HPROJECT)lParam).DB().GetDBName();

		if (NULL != pcDBName)
			strcpy (pName, pcDBName);
		else {
			CoTaskMemFree (pName);
			pName = NULL;
		}
	}

return LRESULT(pName);
}

#endif // WIN32

// DEX_SETACTSCALING: Darstellungsmaßstab setzen
LRESULT ExtDirisWindow::OnSetActiveScaling (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	return LRESULT(m_pView -> SetActiveScaling (lParam));
}

// DEX_ACTIVEPROJECTTEST
// @msg DEX_ACTIVEPROJECTTEST | Diese Message wird an <tr> geschickt, um abzufragen, 
// ob eine aktuelles Projekt existiert. (Mindestens ein Projekt geöffnet ist)
// @rdesc Diese Message liefert <t true>, wenn mindestens ein Projekt geöffnet ist, 
// ansonsten <t false>.
// @comm <tr> kann zur Zeit gleichzeitig lediglich ein Projekt geöffnet halten
// <m DEX_PROJECTOPEN>.<nl>Diese Message wird durch die Funktion 
// <f DEX_OpenProject> ausgelöst.
// Dieses Projekt ist somit auch das aktive Projekt. 
// @xref <m DEX_PROJECTOPEN>, <f DEX_OpenProject>, <f DEX_TestActiveProject>
LRESULT ExtDirisWindow::OnTestActiveProject (HPROJECT hPr, LPARAM lParam)
{
	return LRESULT(IsValidActiveView() && !DBO().isOpeningOrClosing());
}

// DEX_ERASEVIEWCANVAS
// @msg DEX_ERASEVIEWCANVAS | Diese Message wird an <tr> geschickt, um den 
// Fensterinhalt des aktuellen ViewFensters zu löschen.
// @rdesc Diese Message liefert <t true>, wenn mindestens ein Projekt geöffnet ist, 
// ansonsten <t false>.
LRESULT ExtDirisWindow::OnCanvasErase (HPROJECT, LPARAM)
{
	if (!IsValidActiveView())
		return LRESULT(false);

	m_pView -> CanvasErase();
	return LRESULT(true);
}

// DEX_QUERYOBJECTCOUNT
// @msg DEX_QUERYOBJECTCOUNT | Diese Message wird an <tr> geschickt, um die Anzahl
// der Objekte im angegebenen Projekt zu erhalten.
// @rdesc Diese Message liefert die Anzahl der Objekte des Projektes.
LRESULT ExtDirisWindow::OnGetObjectCount (HPROJECT, LPARAM)
{
	if (!IsValidActiveView())
		return LRESULT(0);

	return LRESULT(DBO().CountObjects());
}

// DEX_QUERYIDENTOBJECTCOUNT
// @msg DEX_QUERYIDENTOBJECTCOUNT | Diese Message wird an <tr> geschickt, um die Anzahl
// der Objekte eines Identifikators/Objekttypes im angegebenen Projekt zu erhalten.
// @rdesc Diese Message liefert die Anzahl der Objekte eines Identifikators
// bzw. Objekttypes im Projekt.
// @comm Diese Message liefert zur Zeit nicht unbedingt den richtigen Wert.
// Es wird der Wert der derzeit bekannten Objekte dieses Idents/Objekttypes geliefert.
LRESULT ExtDirisWindow::OnGetIdentObjectCount (HPROJECT, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(0);

IDENTOBJECTCOUNT *pData = (IDENTOBJECTCOUNT *)lParam;

	TX_ASSERT_POINTER(pData, IDENTOBJECTCOUNT);
	TX_ASSERT(sizeof(IDENTOBJECTCOUNT) == pData -> dwSize);
	TX_ASSERT(IsValidIdent(pData -> ulIdent));

	return LRESULT(DBO().GetIdentObjectCount (pData));
}


// DEX_QUERYCLASSCOUNT
// @msg DEX_QUERYCLASSCOUNT | Diese Message wird an <tr> geschickt, um die Anzahl
// der Objektklassen im angegebenen Projekt zu erhalten.
// @rdesc Diese Message liefert die Anzahl der Objektklassen des Projektes.
LRESULT ExtDirisWindow::OnGetClassCount (HPROJECT, LPARAM)
{
	if (!IsValidActiveView())
		return LRESULT(0);

return LRESULT(DBO().DB().CountClasses());
}

// DEX_QUERYVIEWCOUNT
// @msg DEX_QUERYVIEWCOUNT | Diese Message wird an <tr> geschickt, um die Anzahl
// der Ansichten im angegebenen Projekt zu erhalten.
// @rdesc Diese Message liefert die Anzahl der Ansichten des Projektes.
LRESULT ExtDirisWindow::OnGetViewCount (HPROJECT, LPARAM)
{
	if (!IsValidActiveView())
		return LRESULT(0);

return LRESULT(DBO().DB().CountViews());
}

// DEX_QUERYHOLDZOOM
LRESULT ExtDirisWindow::OnIsHoldZoomActive (HPROJECT, LPARAM)
{
	return LRESULT (m_fHoldZoom ? true : false);
}

// DEX_HOLDZOOMSET
LRESULT ExtDirisWindow::OnSetHoldZoom (HPROJECT, LPARAM lParam)
{
bool fOldFlag = m_fHoldZoom ? true : false;

	m_fHoldZoom = lParam ? true : false;

return LRESULT(fOldFlag);
}

// DEX_QUERYCLIPOBJECT
LRESULT ExtDirisWindow::OnGetClipObject (HPROJECT, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(0);

	return DBO().GetClipRegionONr ((LPCSTR)lParam);
}

// DEX_CLIPOBJECTSET
LRESULT ExtDirisWindow::OnSetClipObject (HPROJECT, LPARAM lParam)
{
	if (!IsValidActiveView())
		return LRESULT(false);

#if defined(_DEBUG)
CLIPOBJECTSET *pCOS = (CLIPOBJECTSET *)lParam;

	TX_ASSERT_POINTER(pCOS, CLIPOBJECTSET);
	TX_ASSERT(sizeof(CLIPOBJECTSET) == pCOS -> dwSize);
	TX_ASSERT(NULL == pCOS -> m_pcView || TIsValidString(pCOS -> m_pcView));
	TX_ASSERT(0 == pCOS -> m_lONr || IsValidONr(DBO().DB().DBDesc(), pCOS -> m_lONr));
#endif // _DEBUG

	return DBO().SetClipRegionONr ((CLIPOBJECTSET *)lParam);
}

// DEX_QUERYACTIVEPROJECTHANDLE
LRESULT ExtDirisWindow::OnGetActiveProjectHandle (HPROJECT, LPARAM)
{
	if (!IsValidActiveView())
		return NULL;	// keine DB eröffnet

	return LRESULT(DBO().DB().DBDesc());
}

#if defined(WIN32)
// DEX_QUERYINTERACTIVE
LRESULT ExtDirisWindow::OnQueryInteractive (HPROJECT, LPARAM)
{
	return g_fUser ? true : false;
}

// DEX_IDENTFROMCLASS
LRESULT ExtDirisWindow::OnIdentFromClass (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return E_UNEXPECTED;	// keine DB eröffnet

#if defined(_DEBUG)
IDENTFROMCLASS *pData = (IDENTFROMCLASS *)lParam;

	TX_ASSERT_POINTER(pData, IDENTFROMCLASS);
	TX_ASSERT(sizeof(IDENTFROMCLASS) == pData -> dwSize);
	TX_ASSERT(TIsValidString(pData->pcClass));
#endif // _DEBUG

	return DBO().IdentFromClass((IDENTFROMCLASS *)lParam);
}

// DEX_CLASSFROMIDENT
LRESULT ExtDirisWindow::OnClassFromIdent (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return E_UNEXPECTED;	// keine DB eröffnet

#if defined(_DEBUG)
CLASSFROMIDENT *pData = (CLASSFROMIDENT *)lParam;

	TX_ASSERT_POINTER(pData, CLASSFROMIDENT);
	TX_ASSERT(sizeof(CLASSFROMIDENT) == pData -> dwSize);
	TX_ASSERT(IsValidIdent(pData -> ulIdent));
	TX_ASSERT(TIsValidAddress(pData->pClass, pData->iBuffLen, true));
#endif // _DEBUG

	return DBO().ClassFromIdent ((CLASSFROMIDENT *)lParam);
}

// DEX_MODOBJCLASSCODE
LRESULT ExtDirisWindow::OnModObjClassCode (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return E_UNEXPECTED;	// keine DB eröffnet

#if defined(_DEBUG)
MODOBJCLASSCODE *pData = (MODOBJCLASSCODE *)lParam;

	TX_ASSERT_POINTER(pData, MODOBJCLASSCODE);
	TX_ASSERT(sizeof(MODOBJCLASSCODE) == pData -> dwSize);
	TX_ASSERT(IsValidIdent(pData -> ulIdent));
	TX_ASSERT(TIsValidString(pData->pcClass));
#endif // _DEBUG

	return DBO().ModObjClassCode ((MODOBJCLASSCODE *)lParam);
}

// DEX_SHOWOBJPROP
LRESULT ExtDirisWindow::OnShowObjProp (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return FALSE;	// keine DB eröffnet

	TX_ASSERT(TIsValidString((LPCSTR)lParam));
	m_pEL -> SetActObjProp ((LPCSTR)lParam);
	return TRUE;
}

// DEX_GETSHOWOBJPROP
LRESULT ExtDirisWindow::OnGetShowObjProp (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return FALSE;	// keine DB eröffnet

	TX_ASSERT(TIsValidAddress((LPVOID)lParam, 64, true));	// writeable

string actProp = m_pEL -> GetActOProp();

	strcpy ((char *)lParam, actProp.c_str());
	return TRUE;
}

// DEX_QUERYTRIASVERSION
LRESULT ExtDirisWindow::OnGetTRiASVersion (HPROJECT hPr, LPARAM lParam)
{
	if (0 == lParam) return FALSE;

ResString resVersion (IDS_SIGNONVERSION_MODAL, 128);

	TX_ASSERT(TIsValidAddress((LPVOID)lParam, 128, true));	// writeable
	strcpy ((char *)lParam, resVersion);
	return TRUE;	
}

// DEX_QUERYTRIASCAPTION
LRESULT ExtDirisWindow::OnGetTRiASCaption (HPROJECT hPr, LPARAM lParam)
{
	if (0 == lParam) return FALSE;
	
	TX_ASSERT(TIsValidAddress((LPVOID)lParam, 128, true));	// writeable

string strCaption;
bool fOK = RetrieveBasicCaption (strCaption);

	strncpy ((char *)lParam, strCaption.c_str(), 128);
	((char *)lParam)[min(strCaption.length(), (size_t)127)] = '\0';
	return fOK;
}
	
// DEX_MODIFYTRIASCAPTION
LRESULT ExtDirisWindow::OnSetTRiASCaption (HPROJECT hPr, LPARAM lParam)
{
	return E_NOTIMPL;
}

// DEX_QUERYIDENTPRIORITY
LRESULT ExtDirisWindow::OnGetIdentPriority (HPROJECT hPr, LPARAM lParam)
{
#if defined(_DEBUG)
IDENTPRIORITY *pData = (IDENTPRIORITY *)lParam;

	TX_ASSERT_POINTER(pData, IDENTPRIORITY);
	TX_ASSERT(sizeof(IDENTPRIORITY) == pData -> dwSize);
	TX_ASSERT(IsValidIdent(pData -> ulIdent) || IsValidONr(DBO().DB().DBDesc(), pData -> lONr));
	TX_ASSERT(NULL == pData->pcView || TIsValidString(pData->pcView));
#endif // _DEBUG

	return DBO().GetIdentPriority ((IDENTPRIORITY *)lParam);
}

// DEX_MODIFYIDENTPRIORITY
LRESULT ExtDirisWindow::OnSetIdentPriority (HPROJECT hPr, LPARAM lParam)
{
#if defined(_DEBUG)
IDENTPRIORITY *pData = (IDENTPRIORITY *)lParam;

	TX_ASSERT_POINTER(pData, IDENTPRIORITY);
	TX_ASSERT(sizeof(IDENTPRIORITY) == pData -> dwSize);
	TX_ASSERT(IsValidIdent(pData -> ulIdent) || IsValidONr(DBO().DB().DBDesc(), pData -> lONr));
	TX_ASSERT(NULL == pData->pcView || TIsValidString(pData->pcView));
#endif //_DEBUG

	return DBO().SetIdentPriority ((IDENTPRIORITY *)lParam);
}

// DEX_QUERYACTOBJPROP
LRESULT ExtDirisWindow::OnGetActObjProp (HPROJECT hPr, LPARAM lParam)
{
	return EL().QueryActObjProp ((IObjectProperty **)lParam);
}

// DEX_OBJECTSELECTED
LRESULT ExtDirisWindow::OnSelectObject (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return FALSE;	// keine DB eröffnet

ACTIVATEOBJECT *pData = (ACTIVATEOBJECT *)lParam;

	TX_ASSERT_POINTER(pData, ACTIVATEOBJECT);
	TX_ASSERT(sizeof(ACTIVATEOBJECT) == pData -> dwSize || sizeof(ACTIVATEOBJECTEX) == pData -> dwSize);
	TX_ASSERT(IsValidONr(DBO().DB().DBDesc(), pData -> lONr));

bool fAssoc = false;

	if (sizeof(ACTIVATEOBJECTEX) == pData -> dwSize) {
		TX_ASSERT_POINTER(pData, ACTIVATEOBJECTEX);
		fAssoc = ((ACTIVATEOBJECTEX *)pData) -> fAssoc ? true : false;
	}

	return (LRESULT)DBO().ActivateObj (m_pView, pData->lONr, pData->crAct, fAssoc); 
}

// DEX_OBJECTUNSELECTED
LRESULT ExtDirisWindow::OnDeSelectObject (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return FALSE;	// keine DB eröffnet

	return (LRESULT)DBO().DeActivateObj (m_pView, (LONG)lParam, true);
}

// DEX_QUERYOBJECTGUID
LRESULT ExtDirisWindow::OnGetObjectGuid (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return E_FAIL;	// keine DB eröffnet

OBJECTGUID *pData = (OBJECTGUID *)lParam;

	TX_ASSERT_POINTER(pData, OBJECTGUID);
	TX_ASSERT(sizeof(OBJECTGUID) == pData -> dwSize);
	TX_ASSERT(IsValidONr(DBO().DB().DBDesc(), pData -> lONr));

	return (LRESULT)DBO().GetObjectGuid (pData);
}

// DEX_FINDOBJECTGUID
LRESULT ExtDirisWindow::OnFindObjectFromGuid (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return E_FAIL;	// keine DB eröffnet

OBJECTGUID *pData = (OBJECTGUID *)lParam;

	TX_ASSERT_POINTER(pData, OBJECTGUID);
	TX_ASSERT(sizeof(OBJECTGUID) == pData -> dwSize);

	return (LRESULT)DBO().FindObjectFromGuid (pData);
}

// DEX_SETOBJECTGUID
LRESULT ExtDirisWindow::OnSetObjectGuid (HPROJECT hPr, LPARAM lParam)
{
	if (!IsValidActiveView())
		return E_FAIL;	// keine DB eröffnet

OBJECTGUID *pData = (OBJECTGUID *)lParam;

	TX_ASSERT_POINTER(pData, OBJECTGUID);
	TX_ASSERT(sizeof(OBJECTGUID) == pData -> dwSize);
	TX_ASSERT(IsValidONr(DBO().DB().DBDesc(), pData -> lONr));

	return (LRESULT)DBO().SetObjectGuid (pData);
}

#endif // WIN32

