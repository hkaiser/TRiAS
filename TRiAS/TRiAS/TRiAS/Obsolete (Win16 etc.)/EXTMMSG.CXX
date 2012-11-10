// Ausfuehren verschiedener Anforderungen aus einer Extension -----------------
// File: EXTMMSG.CXX

#include "triaspre.hxx"

#if defined(WIN32)
#include <dirisole.h>
#include "extmain3.hxx"
#endif

#include "tools.hxx"
#include "overview.hxx"
#include "legdinfo.hxx"
#include "legwind.hxx"
#include "coords.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern pApp CurrApp;		// aktuelle App
extern HINSTANCE hInstance;	// aktuelles InstanceHandle
extern HPALETTE hPalette;	// aktive Farbpalette
extern HelpDisplay *IrisHD;	// HilfeFile

extern CoordsDlg *pCoords;
extern COverView *pOverView;
extern CLegendeWindow *pLegende;	// Legende

extern bool LegendToRepaint;
extern bool PrintEFlag;		// Drucken !aktiv
extern bool OverViewCFlag;

extern bool g_fMenu;		// Menu's anzeigen

extern char cbDefaultDir[_MAX_PATH+1];

// sonstige FunktionsPrototypen ------------------------------------------------
ErrCode CreateNewDB (CREATEDB *pCDB, unsigned short iRes);
short OTypToBits (ObjTyp iOTyp);

// Funktion, wo alle Anforderungen aus einer Extension an Diris ankommen ------
LRESULT ExtDirisWindow :: FullFillWill (WPARAM wParam, LPARAM lParam)
{
	if (m_cbDexProcs) {	// über Sprungverteiler abwickeln
	register UINT uiMsg = wParam-m_i1stDexProc;
	
		if (uiMsg >= 0 && uiMsg < m_iDexProcsNum)
			return (this ->* m_cbDexProcs[uiMsg])(lParam);
	}	

#if defined(_DEBUG)		
// ansonsten nach dem üblichen Schema
	switch (wParam) {
	case DEX_MENUITEMINSTALL:	return OnDexInstallMenuItem (lParam);
	case DEX_MENUITEMREMOVE:	return OnDexRemoveMenuItem (lParam);
	case DEX_TOOLINSTALL:		return OnDexInstallTool (lParam);
	case DEX_TOOLREMOVE:		return OnDexRemoveTool (lParam);
	case DEX_QUERYACTIVEPROJECT:	return OnDexQueryActiveProject (lParam);
	case DEX_QUERYACTIVEUSER:	return OnDexQueryActiveUser (lParam);
	case DEX_QUERYROMODE:		return OnDexQueryROMode (lParam);
	case DEX_QUERYGEODBVERSION:	return OnDexQueryGeoDBVersion (lParam);
	case DEX_QUERYACTIVEPBD:	return OnQueryActivePBD (lParam);
	case DEX_MODIFYPBDNAME:		return OnModifyPBDName (lParam);
	case DEX_QUERYMAINININAME:	return OnQueryMainIniName (lParam);
	case DEX_QUERYACTIVEOBJECT:	return OnQueryActiveObject (lParam);
	case DEX_QUERYACTIVEORWINDOW:	return OnQueryActiveORWindow (lParam);
	case DEX_QUERYCNTACTIVEOBJECTS:	return OnQueryCountORWindows (lParam);
	case DEX_QUERYCNTRECHERCHEDOBJECTS:	return OnQueryCountORObjects (lParam);
	case DEX_QUERYALLACTIVEOBJECTS:	return OnQueryAllActiveObjects (lParam);
	case DEX_QUERYACTIVESIGHT:	return OnQueryActiveView (lParam);
	case DEX_GETLASTIDENT:		return OnGetLastIdent (lParam);
	case DEX_SETLASTIDENT:		return OnSetLastIdent (lParam);
	case DEX_QUERYOBJIDENT:		return OnRetrieveIdent (lParam);
	case DEX_QUERYTEXTMERKMAL:	return OnQueryTextMerkmal (lParam);
	case DEX_QUERYOBJMERKMAL:	return OnQueryObjectFeature (lParam);
	case DEX_QUERYIDENTVISINFO:	return OnQueryIdentVisInfo (lParam);
	case DEX_QUERYOBJCOLOR:		return OnQueryObjectColor (lParam);
	case DEX_QUERYOBJTYPE:		return OnRetrieveOTyp (lParam);
	case DEX_QUERYOBJSTATUS:	return OnQueryObjectStatus (lParam);
	case DEX_QUERYOBJSTATISTIK:	return OnQueryObjectStatistics (lParam);
	case DEX_QUERYOBJGEOMETRIE:	return OnQueryObjectGeometry (lParam);
	case DEX_MODIFYOBJGEOMETRIE:	return OnModObjectGeometry (lParam);
	case DEX_QUERYKOBJECTRCODE:	return OnQueryKObjectRCode (lParam);
	case DEX_QUERYOBJCONTAINER:	return OnQueryObjContainer (lParam);
	case DEX_QUERYACTSIGHTCONTAINER:	return OnQueryActViewContainer (lParam);
	case DEX_SETACTSIGHTCONTAINER:	return OnSetActViewContainer (lParam);
	case DEX_QUERYACTIVESELECTION:	return OnQueryActSelection (lParam);
	case DEX_ADDNEWIDENT:		return OnAddNewIdent (lParam);
	case DEX_USEDIDENT:		return OnQueryIdentUsage (lParam);
	case DEX_USEDMCODE:		return OnQueryMCodeUsage (lParam);
	case DEX_USEDRCODE:		return OnQueryRCodeUsage (lParam);
	case DEX_DELOBJECT:		return OnDeleteObject (lParam);
	case DEX_MODOBJIDENT:		return OnModObjectIdent (lParam);
	case DEX_MODIFYMERKMAL:		return OnModTextMerkmal (lParam);
	case DEX_MODIFYIDENTVISINFO:	return OnModObjectVisInfo (lParam);
	case DEX_MODIFYVISINFODIALOG:	return OnVisInfoDialog (lParam);
	case DEX_MERGEKOBJECTS:		return OnMergeKObjects (lParam);
	case DEX_DELETEOBJFROMKOBJECT:	return OnDelObjectFromKObject (lParam);
	case DEX_FLUSHALLMODIFICATIONS:	return OnFlushModifications (lParam);
	case DEX_REBUILDVIEW:		return OnRebuildView (lParam);
	case DEX_REPAINTALL:		return OnRePaintAll (lParam);
	case DEX_REPAINTRECT:		return OnRePaintRect (lParam);
	case DEX_SELNEWSIGHT:		return OnSelectView (lParam);
	case DEX_DELETEVIEW:		return OnDeleteView (lParam);
	case DEX_CREATEOBJEKTINFO:	return OnCreateORWindow (lParam);
	case DEX_READHEADER:		return OnReadHeader (lParam);
	case DEX_MODIFYHEADER:		return OnModifyHeader (lParam);
	case DEX_DELETEHEADER:		return OnDeleteHeader (lParam);
	case DEX_ENUMHEADER:		return OnEnumHeader (lParam);
	case DEX_GETUNIQUEICODE:	return OnGetUniqueICode (lParam);
	case DEX_GETUNIQUEMCODE:	return OnGetUniqueMCode (lParam);
	case DEX_GETUNIQUERCODE:	return OnGetUniqueRCode (lParam);
	case DEX_GETUNIQUETEMPON:	return OnGetUniqueTempONr (lParam);
	case DEX_QUERYACTSCALING:	return OnQueryActScaling (lParam);
	case DEX_QUERYACTMASSTAB:	return OnQueryActMasstab (lParam);
	case DEX_CHANGEACTIVECOLOR:	return OnModActiveColor (lParam);
	case DEX_ENUMALLSIGHTS:		return OnEnumViews (lParam);
	case DEX_ENUMSIGHTOBJECTS:	return OnEnumViewObjects (lParam);
	case DEX_ENUMVIEWIDENTS:	return OnEnumSightIdents (lParam);
	case DEX_ENUMVIEWIDENTSEX:	return OnEnumSightIdentsEx (lParam);
	case DEX_ENUMMERKMALE:		return OnEnumObjectFeatures (lParam);
	case DEX_ENUMMERKMALEIDENT:	return OnEnumIdentFeatures (lParam);
	case DEX_ENUMMERKMALESICHT:	return OnEnumViewFeatures (lParam);
	case DEX_ENUMALLMCODES:		return OnEnumFeatureCodes (lParam);
	case DEX_ENUMSELECTEDOBJECTS:	return OnEnumSelObjects (lParam);
	case DEX_RECHERCHEDOBJECTS:	return OnEnumAllORObjects (lParam);
	case DEX_ENUMKOMPLOBJECTS:	return OnEnumKObjectMember (lParam);
	case DEX_ENUMIDENTOBJS:		return OnEnumIdentObjects (lParam);
	case DEX_ENUMIDENTOBJSEX:	return OnEnumIdentObjectsEx (lParam);
	case DEX_ENUMALLIDENTS:		return OnEnumIdents (lParam);
	case DEX_ENUMALLIDENTSEX:	return OnEnumIdentsEx (lParam);
	case DEX_ENUMTEXTMERKMALRECH:	return OnEnumTextMerkmal (lParam);
	case DEX_ENUMRECHGEOMETRIE:	return OnEnumGeometrie (lParam);
	case DEX_PROJECTOPEN:		return OnOpenProject (lParam);
	case DEX_PROJECTCLOSE:		return OnCloseProject (0);
	case DEX_PROJECTCLOSEEX:	return OnCloseProject (lParam);
	case DEX_SETATTRIBUTES:		return OnSetAttributes (lParam);
	case DEX_RESETATTRIBUTES:	return OnResetAttributes (lParam);
	case DEX_BEGINPBDTRANSACTION:	return OnBeginPBDTransaction (lParam);
	case DEX_BREAKPBDTRANSACTION:	return OnBreakPBDTransaction (lParam);
	case DEX_ENDPBDTRANSACTION:	return OnEndPBDTransaction (lParam);
	case DEX_QUERYPBDVERSION:	return OnQueryPBDVersion (lParam);
	case DEX_QUERYPBDDATA:		return OnQueryPBDData (lParam);
	case DEX_MODPBDDATA:		return OnModPBDData (lParam);
	case DEX_DELPBDDATA:		return OnDelPBDData (lParam);
	case DEX_ENUMPBDDATA:		return OnEnumPBDData (lParam);
	case DEX_QUERYDRAWINGSTATUS:	return OnQueryDrawingStatus (lParam);
	case DEX_QUERYISPRINTING:	return OnQueryPrintingStatus (lParam);
	case DEX_OCTODCEX:		return OnOCtoDCEx (lParam);
	case DEX_OCTODC:		return OnOCtoDC (lParam);
	case DEX_DCTOOCEX:		return OnDCtoOCEx (lParam);
	case DEX_DCTOOC:		return OnDCtoOC (lParam);
	case DEX_QUERYACTIVETOOL:	return OnQueryActTool (lParam);
	case DEX_SETACTIVETOOL:		return OnSetActTool (lParam);
	case DEX_FINDOBJECT:		return OnEnumFoundObjects (lParam);
	case DEX_MODRELATION:		return OnModRelation (lParam);
	case DEX_DELRELATION:		return OnDelRelation (lParam);
	case DEX_ENUMRELATIONS:		return OnEnumRelations (lParam);
	case DEX_ENUMRELATIONOBJS:	return OnEnumObjectRelations (lParam);
	case DEX_QUERYIDENTBASE:	return OnQueryIdentBase (lParam);
	case DEX_QUERYMCODEBASE:	return OnQueryMCodeBase (lParam);
	case DEX_QUERYIDENTOBJTYPES:	return OnQueryIdentObjectTypes (lParam);
	case DEX_CREATENEWGEODB:	return OnCreateGeoDB (lParam);
	case DEX_CREATENEWIDENTSDB:	return OnCreatePBD (lParam);
	case DEX_SETERROR:		return OnSetError (lParam);
	case DEX_ERRINSTALL:		return OnErrInstall (lParam);
	case DEX_EXTERRINSTALL:		return OnExtErrInstall (lParam);
	case DEX_LOADEXTENSION:		return OnLoadExtension (lParam);
	case DEX_LOADEXTENSIONEX:	return OnExtLoadExtension (lParam);
	case DEX_UNLOADEXTENSION:	return OnUnLoadExtension (lParam);
	case DEX_UNLOADEXTENSIONEX:	return OnExtUnLoadExtension (lParam);
	case DEX_RENDERGEODB:		return OnRenderGeoDB (lParam);
	case DEX_QUERYEXPOSEDOC:	return OnQueryExposedOC (lParam);
	case DEX_QUERYEXPOSEDAREA:	return OnQueryExposedArea (lParam);
	case DEX_QUERYPROJECTSTORAGE:	return OnQueryIStorage (lParam);
	case DEX_QUERYACTIVEPALETTE:	return OnQueryActPalette (lParam);
	case DEX_SHOWMAINWINDOW:	return OnShowMainWindow (lParam);
	case DEX_HIDEMAINWINDOW:	return OnHideMainWindow (lParam);
	case DEX_QUERYMAINWINDOWVISIBLE:	return OnQueryMainWindowVisible (lParam);
	case DEX_QUITAPP:		return OnQuit (lParam);
	case DEX_QUERYDEFAULTDATAPATH:	return OnQueryDefaultDataPath (lParam);
	case DEX_MODDEFAULTDATAPATH:	return OnModDefaultDataPath (lParam);
	case DEX_REMOVEORWND:		return OnCloseORWindows (lParam);
	case DEX_SAVELEGEND:		return OnSaveLegend (lParam);
	case DEX_RESETLEGEND:		return OnResetLegend (lParam);
	case DEX_REFRESHLEGEND:		return OnRefreshLegend (lParam);
	case DEX_ADDOBJECTTOLEGEND:	return OnAddObjectToLegend (lParam);
	case DEX_REPAINTLEGEND:		return OnRepaintLegend (lParam);
	case DEX_GETTEXTOBJECTTEXT:	return OnGetTextObjectText (lParam);
	case DEX_OBJECTISVISIBLE:	return OnIsObjectVisible (lParam);
	case DEX_ENUMTOPRELATIONS:	return OnEnumTopRelations (lParam);
	case DEX_QUERYOPENPROJECTS:	return OnNumOfOpenProjects (lParam);
	case DEX_QUERYVIEWDESCRIPTION:	return OnQueryViewDescription (lParam);
	case DEX_MODVIEWDESCRIPTION:	return OnSetViewDescription (lParam);
	case DEX_CANCELMODE:		return OnCancelMode (lParam);
	case DEX_QUERYPROJECTCONT:	return OnQueryProjectCont (lParam);
	case DEX_QUERYOBJECTNAME:	return OnQueryObjectFeatureSpec (lParam);
	case DEX_SETOBJECTNAME:		return OnSetObjectFeatureSpec (lParam);
	case DEX_DIAGNOSTICSENABLE:	return OnEnableDiagnostics (lParam);
	case DEX_ENUMMERKMALEEX:	return OnEnumObjectFeaturesEx (lParam);
	case DEX_ENUMMERKMALEIDENTEX:	return OnEnumIdentFeaturesEx (lParam);
	case DEX_ENUMMERKMALESICHTEX:	return OnEnumViewFeaturesEx (lParam);
	case DEX_QUERYUNKNOWNIDENT:	return OnQueryUnknownIdent (lParam);
	case DEX_FINDOBJFROMNAME:	return OnFindObjFromName (lParam);	
	case DEX_QUERYOBJNAMEMCODE:	return OnQueryObjNameMCode (lParam);
	case DEX_QUERYUNIQUEIDENTMCODE:	return OnQueryUniqueIdentMCode (lParam);
	case DEX_HEADERREREAD:		return OnReReadHeader (lParam);
	case DEX_FINDIDENTFROMNAME:	return OnFindIdentFromName (lParam);
	case DEX_DELETEIDENT:		return OnDeleteIdent (lParam);
	case DEX_VIEWCREATE:		return OnViewCreate (lParam);
	case DEX_VIEWCREATEOPT:		return OnViewCreateOpt (lParam);
	case DEX_DELETEIDENTFROMVIEW:	return OnRemoveIdentFromView (lParam);
	case DEX_VIEWRENAME:		return OnViewRename (lParam);
	case DEX_HASVIEWIDENT:		return OnHasViewIdent (lParam);
	case DEX_HASVIEWOBJECT:		return OnHasViewObject (lParam);
	case DEX_HASPROJECTVIEW:	return OnHasProjectView (lParam);
	case DEX_IDENTADDTOVIEW:	return OnAddIdentToView (lParam);
	case DEX_QUERYADMINMODE:	return OnQueryAdminMode (lParam);
	case DEX_SETADMINMODE:		return OnSetAdminMode (lParam);
#if defined(WIN32)
	case DEX_ADDUNDOREDOITEM:	return OnAddUndoRedo (lParam);
	case DEX_UNDOLEVELBEGIN:	return OnBeginUndoLevel (lParam);
	case DEX_UNDOLEVELEND:		return OnEndUndoLevel (lParam);
	case DEX_UNDOLEVELCANCEL:	return OnCancelUndoLevel (lParam);
	case DEX_DELOBJECTEX:		return OnDeleteObjectEx (lParam);
	case DEX_N_SAVESAMESTORAGE:	return OnSaveSameStorage (lParam);
	case DEX_N_SAVEOTHERSTORAGE:	return OnSaveOtherStorage (lParam);
	case DEX_N_HANDSOFFSTORAGE:	return OnHandsOffStorage (lParam);
	case DEX_N_SAVECOMPLETED:	return OnSaveCompleted (lParam);
	case DEX_ATTACHPRETRANSLATEMSGPROC: return OnAttachPreTranslateMsgProc (lParam);
	case DEX_ATTACHIDLEPROC:	return OnAttachIdleProc (lParam);
	case DEX_MODOBJIDENTEX:		return OnModObjectIdentEx (lParam);
	case DEX_QUERYOBJECTPROPS:	return OnGetObjectProps (lParam);
	case DEX_QUERYCANUNDO:		return OnQueryCanUndo (lParam);
	case DEX_QUERYCANREDO:		return OnQueryCanRedo (lParam);
#else
	case DEX_DELOBJECTEX:		return OnDeleteObject (lParam);
#endif // WIN32
	case DEX_RCTOOC:		return OnRCtoOC (lParam);
	case DEX_OCTORC:		return OnOCtoRC (lParam);
	case DEX_ISOBJWINDOW:		return OnIsORWindow (lParam);
	case DEX_OBJECTREPAINT:		return OnRePaintObject (lParam);
	case DEX_ENUMIDENTVIEWSEX:	return OnEnumIdentViewsEx (lParam);
	case DEX_ACTIVATEALLORWNDS:	return OnActivateAllORWnds (lParam);
	case DEX_ENUMALLMCODESEX:	return OnEnumFeatureCodesEx (lParam);
	case DEX_FINDFEATUREFROMNAME:	return OnFindMCodeFromName(lParam);
	case DEX_SETGEODBDIRTY:		return OnSetDirtyGeoDB (lParam);
	case DEX_ENUMALLPROJECTS:	return OnEnumProjects (lParam);
	case DEX_PROJECTHANDLEFROMNAME:	return OnGetProjectHandle (lParam);
	case DEX_PROJECTMAKEACTIVE:	return OnMakeProjectActive (lParam);
	case DEX_ENUMOBJRECHWNDS:	return OnEnumORWindows (lParam);
	case DEX_ENUMSELECTEDOBJECTSEX:	return OnEnumSelObjectsEx (lParam);
	case DEX_QUERYIDENTOBJTYPESACTVIEW:	return OnGetIdentObjTypesActView (lParam);
	case DEX_CAPTIONREREAD:		return OnReReadCaption (lParam);
	case DEX_GETGEODBDIRTY:		return OnIsGeoDBDirty(lParam);
	case DEX_QUERYLEGENDACTIVE:	return OnIsLegendActive(lParam);
	case DEX_QUERYACTVIEWCONTAINER:	return OnSetViewContainer (lParam);	
	case DEX_MODACTVIEWCONTAINER:	return OnGetViewContainer (lParam);	
	default:
		break;
	}
#endif // _DEBUG

// alle, die nicht implementiert sind, piepsen
//	MessageBeep(0);
return OnNotDefinedMessage (lParam);
}

// Aktuell aktives Projekt liefern ---------------------------------------------
char *ExtDirisWindow :: RetrieveActiveProject (char *pBuffer) 
{
	if (!IsValidActiveView())
		return NULL;	// keine DB eröffnet

	if (pBuffer == NULL)
		pBuffer = new char [strlen (DBO().DB().GetDBName()) +1];
	if (pBuffer) {
		TX_ASSERT(TIsValidAddress(pBuffer, strlen (DBO().DB().GetDBName()), true));
		strcpy (pBuffer, DBO().DB().GetDBName());	// DBNamen kopieren
	}

return pBuffer;
}

// Zentrale INI-Datei liefern -------------------------------------------------
char *ExtDirisWindow :: RetrieveMainProFile (char *pBuffer)
{
	if (pBuffer == NULL)
		pBuffer = new char [13];
	if (pBuffer)
		strcpy (pBuffer, ResString (IDS_PROFILE, 13));

return pBuffer;
}

// CPP - spezifische Anfragen -------------------------------------------------
LRESULT ExtDirisWindow :: FullFillCPPWill (WPARAM wParam, LPARAM lParam)
{
	switch (wParam) {
	case DEXX_MAINWINDOW:
		return (LRESULT)(pWindow)this;

	case DEXX_ORWINDOW:
		return (LRESULT)GetORWindow ((HWND)lParam);

	case DEXX_MAINHELPDISPLAY:
		return (LRESULT)IrisHD;

	case DEXX_GETACTIVEPBD:
		return (LRESULT)&DBO().PbdDB();

	case DEXX_CREATEOBJEKTINFO:
		return (LRESULT)(void *)CreateObjektInfo ((DEXXCREATEOBJEKTINFO *)lParam);

#if defined(WIN32)
	case DEX_QUERYACTIVEVIEWWINDOW:
		return (LRESULT)(void *)m_pView;
#endif // WIN32

	default:
		return EC_OKAY;
	}

// return EC_OKAY;	// unreachable code
}

bool ExpandPalette (HPALETTE hPal, Color C)
{
int iNumEntries;

// 1. Größe der Palette festellen
	if (!hPal) return 0;
	GetObject (hPal, sizeof(int), (LPSTR)&iNumEntries);
	if (iNumEntries == 0) return FALSE;

PALETTEENTRY PalEntry;
int iNewEntries = iNumEntries;

// 2. übergebene Farbe testen
PALETTEENTRY &rCRef = (PALETTEENTRY &)C;
int iIndex = GetNearestPaletteIndex (hPal, (COLORREF &)rCRef);

	GetPaletteEntries (hPal, iIndex, 1, &PalEntry);
	if ((COLORREF &)rCRef != (COLORREF &)PalEntry) {
		iNewEntries++;
		(COLORREF &)PalEntry = (COLORREF &)rCRef;
	}

	if (iNewEntries > iNumEntries) {
	// Palette vergrößern
		ResizePalette (hPal, iNewEntries);
		SetPaletteEntries (hPal, iNumEntries, 
				   iNewEntries-iNumEntries, &PalEntry);
		return true;
	}

return false;	// Palette wurde nicht erweitert
}

// Verteilen der intern zu verarbeitenden Notifikationen ----------------------
LRESULT ExtDirisWindow::DispatchNotification (WPARAM wParam, LPARAM lParam)
{
	if (m_cbDexProcsNfy) {	// über Sprungverteiler abwickeln
	register UINT uiMsg = wParam-m_i1stDexProcNfy;
	
		if (uiMsg >= 0 && uiMsg < m_iDexProcsNumNfy)
			return (this ->* m_cbDexProcsNfy[uiMsg])(lParam);
	}	

#if defined(_DEBUG)
	switch (wParam) {
	case DEX_SETNEWPALETTE:		return doNfySetNewPalette (lParam);
	case DEX_RESCALE:			return doNfyReScale (lParam);
	case DEX_REREADIDENTS:		return doNfyReReadIdents (lParam);
	case DEX_REREADCONTAINER:	return doNfyReReadContainer (lParam);
	case DEX_REREADSIGHTS:		return doNfyReReadViews (lParam);
	case DEX_HEADERREREAD:		return OnReReadHeader (lParam);
	case DEX_SETACTIVETOOL:		return doNfyHandleDeleteMenu (lParam);
	case DEX_OBJECTTODELETE:	return doNfyHandleDeleteObject (lParam);
	case DEX_IDENTWASMODIFIED:	return doNfyIdentModified (lParam);
	case DEX_QUERYRECHOBJECT:	return doNfyQueryRechObject (lParam);
	case DEX_TXICHANGED:		return doNfyTXIChanged (lParam);
	case DEX_TXMCHANGED:		return doNfyTXMChanged (lParam);
	case DEX_TXRCHANGED:		return doNfyTXRChanged (lParam);


	case DEX_DELETEVIEW:	// Sicht soll gelöscht werden
#if defined(WIN32)
		if (S_FALSE == m_pEL -> GeoViewEvent (GEOVIEWEVT_DeletingView, (LPVOID)lParam))
			return true;		// jamand hat was dagegen
#endif // WIN32
		if (pLegende) pLegende -> ResetLegend();
		break;

#if defined(WIN32)
	case DEX_SIGHTDELETED:	// Sicht wurde gelöscht
		m_pEL -> GeoViewEvent (GEOVIEWEVT_ViewDeleted, (LPVOID)lParam);
		break;

	case DEX_VIEWCREATED:	// neue Sicht wurde erzeugt
		m_pEL -> GeoViewEvent (GEOVIEWEVT_ViewCreated, (LPVOID)lParam);
		break;
#endif // WIN32

// Merken des letzten aktiven Fensters
#if defined(WIN32)
	case DEX_GOTOBJWNDFOCUS:
		SetLastActive ((HWND)lParam);
		break;
#else
	case DEX_OBJWNDFOCUSCHANGED:
		if (LOWORD(lParam))
			SetLastActive ((HWND)HIWORD(lParam));
		break;
#endif

	case DEX_COORDFORMATWASCHANGED:	
	// wenn Koordinatenanzeige aktiv ist, dann Koordinatenanzeige refreshen
		if (pCoords != NULL) pCoords -> RefreshCoords();
		break;
	
	case DEX_SETGEODBDIRTY:	// GeoDB als Dirty bzw. nicht dirty gekennzeichnet
#if defined(WIN32)
		{
		char cbName[_MAX_PATH];

			RetrieveActiveProject(cbName);
			if (lParam)	m_pEL -> ProjectEvent -> (PROJECTEVT_ProjectIsDirty, cbName);
			else		m_pEL -> ProjectEvent -> (PROJECTEVT_ProjectIsNotDirty, cbName);
		}
#endif // WIN32
		ReReadCaption();	// Caption richten
		break;

#if defined(WIN32)
	case DEX_INITIALIZEDSERVER:
		m_pEL -> ServerEvent (SERVEREVT_InitializedServer);
		break;

	case DEX_N_EXTENSIONSLOADED:
		m_pEL -> ServerEvent (SERVEREVT_ExtensionsLoaded);
		break;

	case DEX_SERVERISCLOSING:
		if (S_FALSE == m_pEL -> ServerEvent (SERVEREVT_ClosingServer))
			return true;		// jamand hat was dagegen
		break;

	case DEX_SERVERCLOSED:
		m_pEL -> ServerEvent (SERVEREVT_ServerClosed);
		break;

	case DEX_SIGHTTOSELECT:	// Sicht soll gewechselt werden
		{
			if (S_FALSE == m_pEL -> GeoViewEvent (GEOVIEWEVT_SelectingView, (LPVOID)lParam))
				return true;		// jamand hat was dagegen

			m_pEL -> ResetObjProps();
			m_pEL -> ResetClsProps();
		}
		break;

	case DEX_SIGHTSELECTED:	// Sicht wurde gewechselt
		m_pEL -> GeoViewEvent (GEOVIEWEVT_ViewSelected, (LPVOID)lParam);
		break;

	case DEX_PROJECTOPEN:	// GeoDB wurde eröffnet
		{
		char cbName[_MAX_PATH];

			RetrieveActiveProject(cbName);
			m_pEL -> ProjectEvent (PROJECTEVT_ProjectOpened, cbName);
		}
		break;

	case DEX_PROJECTCLOSE:	// GeoDB soll geschlossen werden
		{
		char cbName[_MAX_PATH];

			RetrieveActiveProject(cbName);
			if (S_FALSE == m_pEL -> ProjectEvent (PROJECTEVT_ClosingProject, cbName))
				return true;	// jemand hat was dagegen

			m_pEL -> ResetObjProps();
			m_pEL -> ResetClsProps();
		}
		break;

	case DEX_ISCLOSEDPROJECT:
		m_pEL -> ProjectEvent (PROJECTEVT_ProjectClosed, NULL);
		break;	
#endif // WIN32

	default:
		break;
	}
#endif // _DEBUG

return false;		// einfach weiterleiten
}

///////////////////////////////////////////////////////////////////////////////
// Handler für interne Notifications

// noop -----------------------------------------------------------------------
LRESULT ExtDirisWindow::OnNotUsedNotification (LPARAM lParam)
{
	return false;
}

// DEX_SETNEWPALETTE: HintergrundFarbe hinzufügen -----------------------------
LRESULT ExtDirisWindow::doNfySetNewPalette (LPARAM lParam)
{
	ExpandPalette (*(HPALETTE *)lParam, Color(BLACK));
	ExpandPalette (*(HPALETTE *)lParam, Color(WHITE));
	return ExpandPalette (*(HPALETTE *)lParam, DBO().GetBkColor());
}

// DEX_RESCALE: Header neu lesen ----------------------------------------------
LRESULT ExtDirisWindow::doNfyReScale (LPARAM lParam)
{
	return DBO().ReScale (this);		
}

// DEX_REREADIDENTS: IdentTree neu aufbauen -----------------------------------
LRESULT ExtDirisWindow::doNfyReReadIdents (LPARAM lParam)
{
	return DBO().ReReadIdents();	
}		

// DEX_REREADCONTAINER: DBContainer neu lesen/setzen --------------------------
LRESULT ExtDirisWindow::doNfyReReadContainer (LPARAM lParam)
{
	if (IsValidActiveView()) {
	ObjContainer OC = DBO().DB().DBCont(true).InflateCont(10);
		
		SetExtend (OC);
	}

return false;	// immer weiterschicken
}

// DEX_REREADSIGHTS: Sichtmenu initialisieren ---------------------------------
LRESULT ExtDirisWindow::doNfyReReadViews (LPARAM lParam)
{
	if (IsValidActiveView()) {	// Sichten neu einlesen
	bool fDraw = DBO().DeleteAllSightItems (MainMenu());

		if (DBO().InitSightMenu (MainMenu(), (bool)lParam) || fDraw) 
			DrawMenuBar (Handle (API_WINDOW_HWND));
	}

return false;		// immer weiterleiten
}

// DEX_SETACTIVETOOL: DeleteMenu aktivieren/passivieren -----------------------
LRESULT ExtDirisWindow::doNfyHandleDeleteMenu (LPARAM lParam)
{
	HandleDeleteMenu ((int)lParam == NUMSCHERE);
	return false;
}	

// DEX_OBJECTTODELETE: vor Löschen aus Fenstern nehmen ------------------------
LRESULT ExtDirisWindow::doNfyHandleDeleteObject (LPARAM lParam)
{
	HandleDeleteObject ((LONG)lParam);
	return false;
}

// DEX_IDENTWASMODIFIED: nach umklassifizieren nachführen ---------------------
LRESULT ExtDirisWindow::doNfyIdentModified (LPARAM lParam)
{
	HandleModifyIdent ((long)lParam);
	return false;
}

// DEX_QUERYRECHOBJECT: was soll in einem ROfenster angezeigt werden ----------
LRESULT ExtDirisWindow::doNfyQueryRechObject (LPARAM lParam)
{
RECHOBJECT *pRO = (RECHOBJECT *)lParam;
CTable t(DBO().Idents().IdentTree());

	if (t.Find (&pRO -> lIdent)) {
	CIdentifikatorLock l(t);
	
		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (!l -> GetSearchAble (OTypToBits(ObjTyp(pRO -> iOTyp))))
			pRO -> iFlags = ROHideFlags;
	}

return false;
}

// DEX_TXICHANGED: PBD geändert (Idents) --------------------------------------
LRESULT ExtDirisWindow::doNfyTXIChanged (LPARAM lParam)
{
	if (IsValidActiveView())
		DBO().PbdDB().UpdateIdents (lParam);
	DEX_RefreshLegend();
	DEX_RepaintLegend();

return false;
}

// DEX_TXMCHANGED: PBD geändert (Merkmale) ------------------------------------
LRESULT ExtDirisWindow::doNfyTXMChanged (LPARAM lParam)
{
	if (IsValidActiveView())
		DBO().PbdDB().UpdateMCodes (lParam);

return false;
}
		
// DEX_TXRCHANGED: PBD geändert (Relationen) ----------------------------------
LRESULT ExtDirisWindow::doNfyTXRChanged (LPARAM lParam)
{
	if (IsValidActiveView())
		DBO().PbdDB().UpdateRCodes (lParam);

return false;
}
