// Ausfuehren verschiedener Anforderungen aus einer Extension -----------------
// File: EXTMMSG2.CXX

#include "triaspre.hxx"

#include <dirisole.h>
#include "extmain3.hxx"

#include "tools.hxx"
#include "overview.hxx"
#include "legdinfo.hxx"
#include "legwind.hxx"
#if defined(OLD_COORDS)
#include "coords.hxx"
#endif // OLD_COORDS

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern HelpDisplay *IrisHD;	// HilfeFile

// sonstige FunktionsPrototypen ------------------------------------------------
ErrCode CreateNewDB (CREATEDB *pCDB, unsigned short iRes);
short OTypToBits (ObjTyp iOTyp);

#if defined(_DEBUG)	// inline bei NDEBUG

#include "TraceTRiAS.h"

// Funktion, wo alle Anforderungen aus einer Extension an Diris ankommen ------
LRESULT ExtDirisWindow :: FullFillWill (HPROJECT hPr, WPARAM wParam, LPARAM lParam)
{
	if (m_cbDexProcs) {	// über Sprungverteiler abwickeln
	register UINT uiMsg = wParam-m_i1stDexProc;
	
		if (uiMsg >= 0 && uiMsg < m_iDexProcsNum) {
			if (TRACE_NOTRACE != g_dwTraceLevel && g_dwTraceLevel >= m_pDumpInfos[uiMsg].m_iTraceLevel)
				TX_TRACE2("TRiAS:%s%s\r\n", m_pDumpInfos[uiMsg].m_pcMsgName, (this ->* m_pDumpInfos[uiMsg].m_pDumpProc)(hPr, lParam));
			return (this ->* m_cbDexProcs[uiMsg])(hPr, lParam);
		}
	}	

// ansonsten nach dem üblichen Schema
	switch (wParam) {
	case DEX_MENUITEMINSTALL:	return OnDexInstallMenuItem (hPr, lParam);
	case DEX_MENUITEMREMOVE:	return OnDexRemoveMenuItem (hPr, lParam);
	case DEX_TOOLINSTALL:		return OnDexInstallTool (hPr, lParam);
	case DEX_TOOLREMOVE:		return OnDexRemoveTool (hPr, lParam);
	case DEX_QUERYACTIVEPROJECT:	return OnDexQueryActiveProject (hPr, lParam);
	case DEX_QUERYACTIVEUSER:	return OnDexQueryActiveUser (hPr, lParam);
	case DEX_QUERYROMODE:		return OnDexQueryROMode (hPr, lParam);
	case DEX_QUERYGEODBVERSION:	return OnDexQueryGeoDBVersion (hPr, lParam);
	case DEX_QUERYACTIVEPBD:	return OnQueryActivePBD (hPr, lParam);
	case DEX_MODIFYPBDNAME:		return OnModifyPBDName (hPr, lParam);
	case DEX_QUERYMAINININAME:	return OnQueryMainIniName (hPr, lParam);
	case DEX_QUERYACTIVEOBJECT:	return OnQueryActiveObject (hPr, lParam);
	case DEX_QUERYACTIVEORWINDOW:	return OnQueryActiveORWindow (hPr, lParam);
	case DEX_QUERYCNTACTIVEOBJECTS:	return OnQueryCountORWindows (hPr, lParam);
	case DEX_QUERYCNTRECHERCHEDOBJECTS:	return OnQueryCountORObjects (hPr, lParam);
	case DEX_QUERYALLACTIVEOBJECTS:	return OnQueryAllActiveObjects (hPr, lParam);
	case DEX_QUERYACTIVESIGHT:	return OnQueryActiveView (hPr, lParam);
	case DEX_GETLASTIDENT:		return OnGetLastIdent (hPr, lParam);
	case DEX_SETLASTIDENT:		return OnSetLastIdent (hPr, lParam);
	case DEX_QUERYOBJIDENT:		return OnRetrieveIdent (hPr, lParam);
	case DEX_QUERYTEXTMERKMAL:	return OnQueryTextMerkmal (hPr, lParam);
	case DEX_QUERYOBJMERKMAL:	return OnQueryObjectFeature (hPr, lParam);
	case DEX_QUERYIDENTVISINFO:	return OnQueryIdentVisInfo (hPr, lParam);
	case DEX_QUERYOBJCOLOR:		return OnQueryObjectColor (hPr, lParam);
	case DEX_QUERYOBJTYPE:		return OnRetrieveOTyp (hPr, lParam);
	case DEX_QUERYOBJSTATUS:	return OnQueryObjectStatus (hPr, lParam);
	case DEX_QUERYOBJSTATISTIK:	return OnQueryObjectStatistics (hPr, lParam);
	case DEX_QUERYOBJGEOMETRIE:	return OnQueryObjectGeometry (hPr, lParam);
	case DEX_MODIFYOBJGEOMETRIE:	return OnModObjectGeometry (hPr, lParam);
	case DEX_QUERYKOBJECTRCODE:	return OnQueryKObjectRCode (hPr, lParam);
	case DEX_QUERYOBJCONTAINER:	return OnQueryObjContainer (hPr, lParam);
	case DEX_QUERYACTSIGHTCONTAINER:	return OnQueryActViewContainer (hPr, lParam);
	case DEX_SETACTSIGHTCONTAINER:	return OnSetActViewContainer (hPr, lParam);
	case DEX_QUERYACTIVESELECTION:	return OnQueryActSelection (hPr, lParam);
	case DEX_ADDNEWIDENT:		return OnAddNewIdent (hPr, lParam);
	case DEX_USEDIDENT:		return OnQueryIdentUsage (hPr, lParam);
	case DEX_USEDMCODE:		return OnQueryMCodeUsage (hPr, lParam);
	case DEX_USEDRCODE:		return OnQueryRCodeUsage (hPr, lParam);
	case DEX_DELOBJECT:		return OnDeleteObject (hPr, lParam);
	case DEX_MODOBJIDENT:		return OnModObjectIdent (hPr, lParam);
	case DEX_MODIFYMERKMAL:		return OnModTextMerkmal (hPr, lParam);
	case DEX_MODIFYIDENTVISINFO:	return OnModObjectVisInfo (hPr, lParam);
	case DEX_MODIFYVISINFODIALOG:	return OnVisInfoDialog (hPr, lParam);
	case DEX_MERGEKOBJECTS:		return OnMergeKObjects (hPr, lParam);
	case DEX_DELETEOBJFROMKOBJECT:	return OnDelObjectFromKObject (hPr, lParam);
	case DEX_FLUSHALLMODIFICATIONS:	return OnFlushModifications (hPr, lParam);
	case DEX_REBUILDVIEW:		return OnRebuildView (hPr, lParam);
	case DEX_REPAINTALL:		return OnRePaintAll (hPr, lParam);
	case DEX_REPAINTRECT:		return OnRePaintRect (hPr, lParam);
	case DEX_SELNEWSIGHT:		return OnSelectView (hPr, lParam);
	case DEX_DELETEVIEW:		return OnDeleteView (hPr, lParam);
	case DEX_CREATEOBJEKTINFO:	return OnCreateORWindow (hPr, lParam);
	case DEX_READHEADER:		return OnReadHeader (hPr, lParam);
	case DEX_MODIFYHEADER:		return OnModifyHeader (hPr, lParam);
	case DEX_DELETEHEADER:		return OnDeleteHeader (hPr, lParam);
	case DEX_ENUMHEADER:		return OnEnumHeader (hPr, lParam);
	case DEX_GETUNIQUEICODE:	return OnGetUniqueICode (hPr, lParam);
	case DEX_GETUNIQUEMCODE:	return OnGetUniqueMCode (hPr, lParam);
	case DEX_GETUNIQUERCODE:	return OnGetUniqueRCode (hPr, lParam);
	case DEX_GETUNIQUETEMPON:	return OnGetUniqueTempONr (hPr, lParam);
	case DEX_QUERYACTSCALING:	return OnQueryActScaling (hPr, lParam);
	case DEX_QUERYACTMASSTAB:	return OnQueryActMasstab (hPr, lParam);
	case DEX_CHANGEACTIVECOLOR:	return OnModActiveColor (hPr, lParam);
	case DEX_ENUMALLSIGHTS:		return OnEnumViews (hPr, lParam);
	case DEX_ENUMSIGHTOBJECTS:	return OnEnumViewObjects (hPr, lParam);
	case DEX_ENUMVIEWIDENTS:	return OnEnumSightIdents (hPr, lParam);
	case DEX_ENUMVIEWIDENTSEX:	return OnEnumSightIdentsEx (hPr, lParam);
	case DEX_ENUMMERKMALE:		return OnEnumObjectFeatures (hPr, lParam);
	case DEX_ENUMMERKMALEIDENT:	return OnEnumIdentFeatures (hPr, lParam);
	case DEX_ENUMMERKMALESICHT:	return OnEnumViewFeatures (hPr, lParam);
	case DEX_ENUMALLMCODES:		return OnEnumFeatureCodes (hPr, lParam);
	case DEX_ENUMSELECTEDOBJECTS:	return OnEnumSelObjects (hPr, lParam);
	case DEX_RECHERCHEDOBJECTS:	return OnEnumAllORObjects (hPr, lParam);
	case DEX_ENUMKOMPLOBJECTS:	return OnEnumKObjectMember (hPr, lParam);
	case DEX_ENUMIDENTOBJS:		return OnEnumIdentObjects (hPr, lParam);
	case DEX_ENUMIDENTOBJSEX:	return OnEnumIdentObjectsEx (hPr, lParam);
	case DEX_ENUMALLIDENTS:		return OnEnumIdents (hPr, lParam);
	case DEX_ENUMALLIDENTSEX:	return OnEnumIdentsEx (hPr, lParam);
	case DEX_ENUMTEXTMERKMALRECH:	return OnEnumTextMerkmal (hPr, lParam);
	case DEX_ENUMRECHGEOMETRIE:	return OnEnumGeometrie (hPr, lParam);
	case DEX_PROJECTOPEN:		return OnOpenProject (hPr, lParam);
	case DEX_PROJECTCLOSE:		return OnCloseProject (hPr, 0);
	case DEX_PROJECTCLOSEEX:	return OnCloseProject (hPr, lParam);
	case DEX_SETATTRIBUTES:		return OnSetAttributes (hPr, lParam);
	case DEX_RESETATTRIBUTES:	return OnResetAttributes (hPr, lParam);
	case DEX_BEGINPBDTRANSACTION:	return OnBeginPBDTransaction (hPr, lParam);
	case DEX_BREAKPBDTRANSACTION:	return OnBreakPBDTransaction (hPr, lParam);
	case DEX_ENDPBDTRANSACTION:	return OnEndPBDTransaction (hPr, lParam);
	case DEX_QUERYPBDVERSION:	return OnQueryPBDVersion (hPr, lParam);
	case DEX_QUERYPBDDATA:		return OnQueryPBDData (hPr, lParam);
	case DEX_MODPBDDATA:		return OnModPBDData (hPr, lParam);
	case DEX_DELPBDDATA:		return OnDelPBDData (hPr, lParam);
	case DEX_ENUMPBDDATA:		return OnEnumPBDData (hPr, lParam);
	case DEX_QUERYDRAWINGSTATUS:	return OnQueryDrawingStatus (hPr, lParam);
	case DEX_QUERYISPRINTING:	return OnQueryPrintingStatus (hPr, lParam);
	case DEX_OCTODCEX:		return OnOCtoDCEx (hPr, lParam);
	case DEX_OCTODC:		return OnOCtoDC (hPr, lParam);
	case DEX_DCTOOCEX:		return OnDCtoOCEx (hPr, lParam);
	case DEX_DCTOOC:		return OnDCtoOC (hPr, lParam);
	case DEX_QUERYACTIVETOOL:	return OnQueryActTool (hPr, lParam);
	case DEX_SETACTIVETOOL:		return OnSetActTool (hPr, lParam);
	case DEX_FINDOBJECT:		return OnEnumFoundObjects (hPr, lParam);
	case DEX_MODRELATION:		return OnModRelation (hPr, lParam);
	case DEX_DELRELATION:		return OnDelRelation (hPr, lParam);
	case DEX_ENUMRELATIONS:		return OnEnumRelations (hPr, lParam);
	case DEX_ENUMRELATIONOBJS:	return OnEnumObjectRelations (hPr, lParam);
	case DEX_QUERYIDENTBASE:	return OnQueryIdentBase (hPr, lParam);
	case DEX_QUERYMCODEBASE:	return OnQueryMCodeBase (hPr, lParam);
	case DEX_QUERYIDENTOBJTYPES:	return OnQueryIdentObjectTypes (hPr, lParam);
	case DEX_CREATENEWGEODB:	return OnCreateGeoDB (hPr, lParam);
	case DEX_CREATENEWIDENTSDB:	return OnCreatePBD (hPr, lParam);
	case DEX_SETERROR:		return OnSetError (hPr, lParam);
	case DEX_ERRINSTALL:		return OnErrInstall (hPr, lParam);
	case DEX_EXTERRINSTALL:		return OnExtErrInstall (hPr, lParam);
	case DEX_LOADEXTENSION:		return OnLoadExtension (hPr, lParam);
	case DEX_LOADEXTENSIONEX:	return OnExtLoadExtension (hPr, lParam);
	case DEX_UNLOADEXTENSION:	return OnUnLoadExtension (hPr, lParam);
	case DEX_UNLOADEXTENSIONEX:	return OnExtUnLoadExtension (hPr, lParam);
	case DEX_LOADEXTENSION2:	return OnLoadExtension2 (hPr, lParam);
	case DEX_UNLOADEXTENSION2:	return OnUnLoadExtension2 (hPr, lParam);
	case DEX_RENDERGEODB:		return OnRenderGeoDB (hPr, lParam);
	case DEX_QUERYEXPOSEDOC:	return OnQueryExposedOC (hPr, lParam);
	case DEX_QUERYEXPOSEDAREA:	return OnQueryExposedArea (hPr, lParam);
	case DEX_QUERYPROJECTSTORAGE:	return OnQueryIStorage (hPr, lParam);
	case DEX_QUERYACTIVEPALETTE:	return OnQueryActPalette (hPr, lParam);
	case DEX_SHOWMAINWINDOW:	return OnShowMainWindow (hPr, lParam);
	case DEX_HIDEMAINWINDOW:	return OnHideMainWindow (hPr, lParam);
	case DEX_QUERYMAINWINDOWVISIBLE:	return OnQueryMainWindowVisible (hPr, lParam);
	case DEX_QUITAPP:		return OnQuit (hPr, lParam);
	case DEX_QUERYDEFAULTDATAPATH:	return OnQueryDefaultDataPath (hPr, lParam);
	case DEX_MODDEFAULTDATAPATH:	return OnModDefaultDataPath (hPr, lParam);
	case DEX_REMOVEORWND:		return OnCloseORWindows (hPr, lParam);
	case DEX_SAVELEGEND:		return OnSaveLegend (hPr, lParam);
	case DEX_RESETLEGEND:		return OnResetLegend (hPr, lParam);
	case DEX_REFRESHLEGEND:		return OnRefreshLegend (hPr, lParam);
	case DEX_ADDOBJECTTOLEGEND:	return OnAddObjectToLegend (hPr, lParam);
	case DEX_REPAINTLEGEND:		return OnRepaintLegend (hPr, lParam);
	case DEX_GETTEXTOBJECTTEXT:	return OnGetTextObjectText (hPr, lParam);
	case DEX_PUTTEXTOBJECTTEXT:	return OnPutTextObjectText (hPr, lParam);
	case DEX_OBJECTISVISIBLE:	return OnIsObjectVisible (hPr, lParam);
	case DEX_ENUMTOPRELATIONS:	return OnEnumTopRelations (hPr, lParam);
	case DEX_QUERYOPENPROJECTS:	return OnNumOfOpenProjects (hPr, lParam);
	case DEX_QUERYVIEWDESCRIPTION:	return OnQueryViewDescription (hPr, lParam);
	case DEX_MODVIEWDESCRIPTION:	return OnSetViewDescription (hPr, lParam);
	case DEX_CANCELMODE:		return OnCancelMode (hPr, lParam);
	case DEX_QUERYPROJECTCONT:	return OnQueryProjectCont (hPr, lParam);
	case DEX_QUERYOBJECTNAME:	return OnQueryObjectFeatureSpec (hPr, lParam);
	case DEX_SETOBJECTNAME:		return OnSetObjectFeatureSpec (hPr, lParam);
	case DEX_DIAGNOSTICSENABLE:	return OnEnableDiagnostics (hPr, lParam);
	case DEX_ENUMMERKMALEEX:	return OnEnumObjectFeaturesEx (hPr, lParam);
	case DEX_ENUMMERKMALEIDENTEX:	return OnEnumIdentFeaturesEx (hPr, lParam);
	case DEX_ENUMMERKMALESICHTEX:	return OnEnumViewFeaturesEx (hPr, lParam);
	case DEX_QUERYUNKNOWNIDENT:	return OnQueryUnknownIdent (hPr, lParam);
	case DEX_FINDOBJFROMNAME:	return OnFindObjFromName (hPr, lParam);	
	case DEX_QUERYOBJNAMEMCODE:	return OnQueryObjNameMCode (hPr, lParam);
	case DEX_QUERYUNIQUEIDENTMCODE:	return OnQueryUniqueIdentMCode (hPr, lParam);
	case DEX_QUERYOLDUNIQUEIDENTMCODE:	return OnQueryOldUniqueIdentMCode (hPr, lParam);
	case DEX_HEADERREREAD:		return OnReReadHeader (hPr, lParam);
	case DEX_FINDIDENTFROMNAME:	return OnFindIdentFromName (hPr, lParam);
	case DEX_FINDIDENTFROMNAMECI:	return OnFindIdentFromNameCI (hPr, lParam);
	case DEX_DELETEIDENT:		return OnDeleteIdent (hPr, lParam);
	case DEX_VIEWCREATE:		return OnViewCreate (hPr, lParam);
	case DEX_VIEWCREATEOPT:		return OnViewCreateOpt (hPr, lParam);
	case DEX_DELETEIDENTFROMVIEW:	return OnRemoveIdentFromView (hPr, lParam);
	case DEX_VIEWRENAME:		return OnViewRename (hPr, lParam);
	case DEX_HASVIEWIDENT:		return OnHasViewIdent (hPr, lParam);
	case DEX_HASVIEWOBJECT:		return OnHasViewObject (hPr, lParam);
	case DEX_HASPROJECTVIEW:	return OnHasProjectView (hPr, lParam);
	case DEX_IDENTADDTOVIEW:	return OnAddIdentToView (hPr, lParam);
	case DEX_QUERYADMINMODE:	return OnQueryAdminMode (hPr, lParam);
	case DEX_SETADMINMODE:		return OnSetAdminMode (hPr, lParam);
#if defined(WIN32)
	case DEX_ADDUNDOREDOITEM:	return OnAddUndoRedo (hPr, lParam);
	case DEX_UNDOLEVELBEGIN:	return OnBeginUndoLevel (hPr, lParam);
	case DEX_UNDOLEVELEND:		return OnEndUndoLevel (hPr, lParam);
	case DEX_UNDOLEVELCANCEL:	return OnCancelUndoLevel (hPr, lParam);
	case DEX_DELOBJECTEX:		return OnDeleteObjectEx (hPr, lParam);
	case DEX_N_SAVESAMESTORAGE:	return OnSaveSameStorage (hPr, lParam);
	case DEX_N_SAVEOTHERSTORAGE:	return OnSaveOtherStorage (hPr, lParam);
	case DEX_N_HANDSOFFSTORAGE:	return OnHandsOffStorage (hPr, lParam);
	case DEX_N_SAVECOMPLETED:	return OnSaveCompleted (hPr, lParam);
	case DEX_ATTACHPRETRANSLATEMSGPROC: return OnAttachPreTranslateMsgProc (hPr, lParam);
	case DEX_ATTACHIDLEPROC:	return OnAttachIdleProc (hPr, lParam);
	case DEX_MODOBJIDENTEX:		return OnModObjectIdentEx (hPr, lParam);
	case DEX_QUERYOBJECTPROPS:	return OnGetObjectProps (hPr, lParam);
	case DEX_QUERYCANUNDO:		return OnQueryCanUndo (hPr, lParam);
	case DEX_QUERYCANREDO:		return OnQueryCanRedo (hPr, lParam);
	case DEX_SETSTRINGMESSAGE:	return OnSetMessageString (hPr, lParam);
	case DEX_SETSTRINGMESSAGENOKICKIDLE:	return OnSetMessageStringNoKickIdle (hPr, lParam);
	case DEX_KICKIDLELOOP:		return OnKickIdle (hPr, lParam);
	case DEX_QUERYOBJECTCOUNT:	return OnGetObjectCount (hPr, lParam);
	case DEX_QUERYCLASSCOUNT:	return OnGetClassCount (hPr, lParam);
	case DEX_QUERYVIEWCOUNT:	return OnGetViewCount (hPr, lParam);
	case DEX_QUERYHOLDZOOM:		return OnIsHoldZoomActive (hPr, lParam); 
	case DEX_HOLDZOOMSET:		return OnSetHoldZoom (hPr, lParam);	 
	case DEX_PROJECTNAMEFROMHANDLE:	return OnProjectNameFromHandle (hPr, lParam);
	case DEX_PROJECTOPENEX:		return OnOpenProjectEx (hPr, lParam);
	case DEX_QUERYINTERACTIVE:	return OnQueryInteractive (hPr, lParam);
	case DEX_IDENTFROMCLASS:	return OnIdentFromClass (hPr, lParam);
	case DEX_CLASSFROMIDENT:	return OnClassFromIdent (hPr, lParam);
	case DEX_MODOBJCLASSCODE:	return OnModObjClassCode (hPr, lParam);
	case DEX_SHOWOBJPROP:		return OnShowObjProp (hPr, lParam);
	case DEX_GETSHOWOBJPROP:	return OnGetShowObjProp (hPr, lParam);
	case DEX_QUERYTRIASVERSION:	return OnGetTRiASVersion (hPr, lParam);
	case DEX_QUERYTRIASVERSIONLONG:	return OnGetTRiASVersionLong (hPr, lParam);
	case DEX_QUERYTRIASCAPTION:	return OnGetTRiASCaption (hPr, lParam);
	case DEX_MODIFYTRIASCAPTION:	return OnSetTRiASCaption (hPr, lParam);
	case DEX_QUERYIDENTPRIORITY:	return OnGetIdentPriority (hPr, lParam);
	case DEX_MODIFYIDENTPRIORITY:	return OnSetIdentPriority (hPr, lParam);
	case DEX_QUERYACTOBJPROP:	return OnGetActObjProp (hPr, lParam);
	case DEX_QUERYOBJECTGUID:	return OnGetObjectGuid (hPr, lParam);
	case DEX_FINDOBJECTGUID:	return OnFindObjectFromGuid (hPr, lParam);
	case DEX_SETOBJECTGUID:	return OnSetObjectGuid (hPr, lParam);
	case DEX_QUERYPREVENTREPAINT:	return OnQueryPreventRepaint (hPr, lParam);
	case DEX_PREVENTREPAINT:	return OnPreventRepaint (hPr, lParam);
	case DEX_QUERYACTASPECTRATIO:	return OnGetActiveAspect (hPr, lParam);
	case DEX_MODIFYIDENTSCALEDATA:	return OnModifyIdentScaleData (hPr, lParam);
	case DEX_QUERYIDENTSCALEDATA:	return OnGetIdentScaleData (hPr, lParam);
	case DEX_TESTIDENTSCALETOPAINT:	return OnTestIdentScaleToPaint (hPr, lParam);
#else
	case DEX_DELOBJECTEX:		return OnDeleteObject (hPr, lParam);
	case DEX_KICKIDLE:			return OnKickIdle(hPr, lParam);
#endif // WIN32
	case DEX_RCTOOC:		return OnRCtoOC (hPr, lParam);
	case DEX_OCTORC:		return OnOCtoRC (hPr, lParam);
	case DEX_ISOBJWINDOW:		return OnIsORWindow (hPr, lParam);
	case DEX_OBJECTREPAINT:		return OnRePaintObject (hPr, lParam);
	case DEX_ENUMIDENTVIEWSEX:	return OnEnumIdentViewsEx (hPr, lParam);
	case DEX_ACTIVATEALLORWNDS:	return OnActivateAllORWnds (hPr, lParam);
	case DEX_ENUMALLMCODESEX:	return OnEnumFeatureCodesEx (hPr, lParam);
	case DEX_FINDFEATUREFROMNAME:	return OnFindMCodeFromName(hPr, lParam);
	case DEX_FINDFEATUREFROMNAMECI:	return OnFindMCodeFromNameCI(hPr, lParam);
	case DEX_SETGEODBDIRTY:		return OnSetDirtyGeoDB (hPr, lParam);
	case DEX_ENUMALLPROJECTS:	return OnEnumProjects (hPr, lParam);
	case DEX_PROJECTHANDLEFROMNAME:	return OnGetProjectHandle (hPr, lParam);
	case DEX_PROJECTMAKEACTIVE:	return OnMakeProjectActive (hPr, lParam);
	case DEX_ENUMOBJRECHWNDS:	return OnEnumORWindows (hPr, lParam);
	case DEX_ENUMSELECTEDOBJECTSEX:	return OnEnumSelObjectsEx (hPr, lParam);
	case DEX_QUERYIDENTOBJTYPESACTVIEW:	return OnGetIdentObjTypesActView (hPr, lParam);
	case DEX_CAPTIONREREAD:		return OnReReadCaption (hPr, lParam);
	case DEX_GETGEODBDIRTY:		return OnIsGeoDBDirty(hPr, lParam);
	case DEX_QUERYLEGENDACTIVE:	return OnIsLegendActive(hPr, lParam);
	case DEX_QUERYACTVIEWCONTAINER:	return OnSetViewContainer (hPr, lParam);	
	case DEX_MODACTVIEWCONTAINER:	return OnGetViewContainer (hPr, lParam);	
	case DEX_SETACTSCALING:		return OnSetActiveScaling(hPr, lParam);
	case DEX_ACTIVEPROJECTTEST:	return OnTestActiveProject(hPr, lParam); 
	case DEX_ERASEVIEWCANVAS:	return OnCanvasErase(hPr, lParam);
	case DEX_QUERYCLIPOBJECT:	return OnGetClipObject (hPr, lParam);
	case DEX_CLIPOBJECTSET:		return OnSetClipObject (hPr, lParam);
	case DEX_QUERYACTIVEPROJECTHANDLE:	return OnGetActiveProjectHandle (hPr, lParam);
	case DEX_QUERYOVERVIEWACTIVE:	return OnIsOverviewActive(hPr, lParam);
	case DEX_QUERYCOMPATIBILITYMODE:	return OnIsCompatible(hPr, lParam);
	case DEX_OVERVIEWSAVE:		return OnSaveOverview (hPr, lParam);
	case DEX_QUERYIDENTOBJECTCOUNT:	return OnGetIdentObjectCount (hPr, lParam);
// #HK980527
	case DEX_ENUMEXTENSIONS:	return OnEnumExtensions (hPr, lParam);
	case DEX_QUERYEXTENSIONINFO:	return OnGetExtensionInfo (hPr, lParam);
	case DEX_QUERYEXTENSIONPTR:	return OnGetExtensionPtr (hPr, lParam);

// #HK980921
	case DEX_SETHAVETOINITOPFS:	return OnMustInitOPFs (hPr, lParam);
	case DEX_QUERYMUSTINITOPFS:	return OnGetMustInitOPFs (hPr, lParam);

	default:
		break;
	}

// alle, die nicht implementiert sind, piepsen
//	MessageBeep(0);
return OnNotDefinedMessage (hPr, lParam);
}
#endif // _DEBUG

// Aktuell aktives Projekt liefern ---------------------------------------------
char *ExtDirisWindow :: RetrieveActiveProject (char *pBuffer) 
{
	if (!IsValidActiveView() || DBO()./*isOpeningOr*/isClosing())
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
LRESULT ExtDirisWindow :: FullFillCPPWill (HPROJECT hPr, WPARAM wParam, LPARAM lParam)
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

