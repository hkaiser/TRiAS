// Fuktionen, die bei externen Messages gerufen werden ------------------------
// File EXTFCNS.HXX

#if !defined(_EXTFCNS_HXX)
#define _EXTFCNS_HXX

#if defined(DECLAREMAPFUNCTIONS)
	LRESULT OnNotDefinedMessage (HPROJECT, LPARAM);	// Nicht definierte Message
	
// diese Funktionsdeklarationen sind lediglich f�r eine Datei notwendig
	LRESULT OnEnumGeometrie (HPROJECT, LPARAM);		// DEX_ENUMRECHGEOMETRIE	
	LRESULT OnEnumTextMerkmal (HPROJECT, LPARAM);	// DEX_ENUMTEXTMERKMALRECH	
	LRESULT OnRetrieveIdent (HPROJECT, LPARAM);		// DEX_QUERYOBJIDENT
	LRESULT OnRetrieveOTyp (HPROJECT, LPARAM);		// DEX_QUERYOBJTYPE
	LRESULT OnQueryTextMerkmal (HPROJECT, LPARAM);	// DEX_QUERYTEXTMERKMAL
	LRESULT OnModTextMerkmal (HPROJECT, LPARAM);	// DEX_MODIFYMERKMAL
	LRESULT OnEnumSightIdents (HPROJECT, LPARAM);	// DEX_ENUMVIEWIDENTS
	LRESULT OnEnumSightIdentsEx (HPROJECT, LPARAM);	// DEX_ENUMVIEWIDENTSEX
	LRESULT OnEnumIdents (HPROJECT, LPARAM);		// DEX_ENUMALLIDENTS
	LRESULT OnEnumIdentsEx (HPROJECT, LPARAM);		// DEX_ENUMALLIDENTSEX
	LRESULT OnEnumIdentObjects (HPROJECT, LPARAM);	// DEX_ENUMIDENTOBJS
	LRESULT OnEnumIdentObjectsEx (HPROJECT, LPARAM);	// DEX_ENUMIDENTOBJS
	LRESULT OnQueryObjContainer (HPROJECT, LPARAM);	// DEX_QUERYOBJCONTAINER
	LRESULT OnGetLastIdent (HPROJECT, LPARAM);		// DEX_GETLASTIDENT
	LRESULT OnSetLastIdent (HPROJECT, LPARAM);		// DEX_SETLASTIDENT
	LRESULT OnDeleteObject (HPROJECT, LPARAM);		// DEX_DELOBJECT
	LRESULT OnSaveLegend (HPROJECT, LPARAM);		// DEX_SAVELEGEND
	LRESULT OnResetLegend (HPROJECT, LPARAM);		// DEX_RESETLEGEND
	LRESULT OnRefreshLegend (HPROJECT, LPARAM);		// DEX_REFRESHLEGEND
	LRESULT OnAddObjectToLegend (HPROJECT, LPARAM);	// DEX_ADDOBJECTTOLEGEND
	LRESULT OnRepaintLegend (HPROJECT, LPARAM);		// DEX_REPAINTLEGEND
	LRESULT OnGetTextObjectText (HPROJECT, LPARAM);	// DEX_GETTEXTOBJECTTEXT
	LRESULT OnPutTextObjectText (HPROJECT, LPARAM);	// DEX_PUTTEXTOBJECTTEXT
	LRESULT OnIsObjectVisible (HPROJECT, LPARAM);	// DEX_OBJECTISVISIBLE
	LRESULT OnEnumTopRelations (HPROJECT, LPARAM);	// DEX_ENUMTOPRELATIONS
	LRESULT OnDexInstallMenuItem (HPROJECT, LPARAM);	// DEX_INSTALLMENUITEM
	LRESULT OnDexRemoveMenuItem (HPROJECT, LPARAM);	// DEX_REMOVEMENUITEM
	LRESULT OnDexInstallTool (HPROJECT, LPARAM);	// DEX_INSTALLTOOL
	LRESULT OnDexRemoveTool (HPROJECT, LPARAM);		// DEX_REMOVETOOL
	LRESULT OnDexQueryActiveProject (HPROJECT, LPARAM); // DEX_QUERYACTIVEPROJECT
	LRESULT OnDexQueryActiveUser (HPROJECT, LPARAM);	// DEX_QUERYACTIVEUSER
	LRESULT OnDexQueryROMode (HPROJECT, LPARAM);	// DEX_GETROMODE
	LRESULT OnDexQueryGeoDBVersion (HPROJECT, LPARAM); // DEX_QUERYGEODBVERSION
	LRESULT OnQueryActivePBD (HPROJECT, LPARAM);	// DEX_QUERYACTIVEPBD
	LRESULT OnModifyPBDName (HPROJECT, LPARAM);		// DEX_MODIFYPBDNAME
	LRESULT OnQueryMainIniName (HPROJECT, LPARAM);	// DEX_QUERYMAINININAME
	LRESULT OnQueryActiveObject (HPROJECT, LPARAM);	// DEX_QUERYACTIVEOBJECT
	LRESULT OnQueryActiveORWindow (HPROJECT, LPARAM);	// DEX_QUERYACTIVEORWINDOW
	LRESULT OnQueryCountORWindows (HPROJECT, LPARAM);	// DEX_QUERYCNTACTIVEOBJECTS
	LRESULT OnQueryCountORObjects (HPROJECT, LPARAM);	// DEX_QUERYCNTRECHERCHEDOBJECTS
	LRESULT OnQueryAllActiveObjects (HPROJECT, LPARAM); // DEX_QUERYALLACTIVEOBJECTS
	LRESULT OnQueryActiveView (HPROJECT, LPARAM);	// DEX_QUERYACTIVESIGHT
	LRESULT OnQueryObjectFeature (HPROJECT, LPARAM);	// DEX_QUERYOBJMERKMAL
	LRESULT OnQueryIdentVisInfo (HPROJECT, LPARAM);	// DEX_QUERYIDENTVISINFO
	LRESULT OnQueryObjectColor (HPROJECT, LPARAM);	// DEX_QUERYOBJCOLOR
	LRESULT OnQueryObjectStatus (HPROJECT, LPARAM);	// DEX_QUERYOBJSTATUS
	LRESULT OnQueryObjectStatistics (HPROJECT, LPARAM); // DEX_QUERYOBJSTATISTIK
	LRESULT OnQueryObjectGeometry (HPROJECT, LPARAM);	// DEX_QUERYOBJGEOMETRIE
	LRESULT OnModObjectGeometry (HPROJECT, LPARAM);	// DEX_MODIFYOBJGEOMETRIE
	LRESULT OnQueryKObjectRCode (HPROJECT, LPARAM);	// DEX_QUERYKOBJECTRCODE
	LRESULT OnQueryActViewContainer (HPROJECT, LPARAM); // DEX_QUERYACTSIGHTCONTAINER
	LRESULT OnSetActViewContainer (HPROJECT, LPARAM);	// DEX_SETACTSIGHTCONTAINER
	LRESULT OnQueryActSelection (HPROJECT, LPARAM);	// DEX_QUERYACTIVESELECTION
	LRESULT OnAddNewIdent (HPROJECT, LPARAM);		// DEX_ADDNEWIDENT
	LRESULT OnQueryIdentUsage (HPROJECT, LPARAM);	// DEX_USEDIDENT
	LRESULT OnQueryMCodeUsage (HPROJECT, LPARAM);	// DEX_USEDMCODE
	LRESULT OnQueryRCodeUsage (HPROJECT, LPARAM);	// DEX_USEDRCODE
	LRESULT OnModObjectIdent (HPROJECT, LPARAM);	// DEX_MODOBJIDENT
	LRESULT OnModObjectVisInfo (HPROJECT, LPARAM);	// DEX_MODIFYIDENTVISINFO
	LRESULT OnVisInfoDialog (HPROJECT, LPARAM);		// DEX_MODIFYVISINFODIALOG
	LRESULT OnMergeKObjects (HPROJECT, LPARAM);		// DEX_MERGEKOBJECTS
	LRESULT OnDelObjectFromKObject (HPROJECT, LPARAM); // DEX_DELETEOBJFROMKOBJECT
	LRESULT OnFlushModifications (HPROJECT, LPARAM);	// DEX_FLUSHALLMODIFICATIONS
	LRESULT OnRebuildView (HPROJECT, LPARAM);		// DEX_REBUILDVIEW
	LRESULT OnRePaintAll (HPROJECT, LPARAM);		// DEX_REPAINTALL
	LRESULT OnRePaintRect (HPROJECT, LPARAM);		// DEX_REPAINTRECT
	LRESULT OnSelectView (HPROJECT, LPARAM);		// DEX_SELNEWSIGHT
	LRESULT OnDeleteView (HPROJECT, LPARAM);		// DEX_DELETEVIEW
	LRESULT OnCreateORWindow (HPROJECT, LPARAM);	// DEX_CREATEOBJEKTINFO
	LRESULT OnReadHeader (HPROJECT, LPARAM);		// DEX_READHEADER
	LRESULT OnModifyHeader (HPROJECT, LPARAM);		// DEX_MODIFYHEADER
	LRESULT OnDeleteHeader (HPROJECT, LPARAM);		// DEX_DELETEHEADER
	LRESULT OnEnumHeader (HPROJECT, LPARAM);		// DEX_ENUMHEADER
	LRESULT OnGetUniqueICode (HPROJECT, LPARAM);	// DEX_GETUNIQUEICODE
	LRESULT OnGetUniqueMCode (HPROJECT, LPARAM);	// DEX_GETUNIQUEMCODE
	LRESULT OnGetUniqueRCode (HPROJECT, LPARAM);	// DEX_GETUNIQUERCODE
	LRESULT OnGetUniqueTempONr (HPROJECT, LPARAM);	// DEX_GETUNIQUETEMPON
	LRESULT OnQueryActScaling (HPROJECT, LPARAM);	// DEX_QUERYACTSCALING
	LRESULT OnQueryActMasstab (HPROJECT, LPARAM);	// DEX_QUERYACTMASSTAB
	LRESULT OnModActiveColor (HPROJECT, LPARAM);	// DEX_CHANGEACTIVECOLOR
	LRESULT OnEnumViews (HPROJECT, LPARAM);			// DEX_ENUMSIGHTS
	LRESULT OnEnumViewObjects (HPROJECT, LPARAM);	// DEX_ENUMSIGHTOBJECTS
	LRESULT OnEnumObjectFeatures (HPROJECT, LPARAM);	// DEX_ENUMMERKMALE
	LRESULT OnEnumIdentFeatures (HPROJECT, LPARAM);	// DEX_ENUMMERKMALEIDENT
	LRESULT OnEnumViewFeatures (HPROJECT, LPARAM);	// DEX_ENUMMERKMALESICHT
	LRESULT OnEnumObjectFeaturesEx (HPROJECT, LPARAM); // DEX_ENUMMERKMALEEX
	LRESULT OnEnumIdentFeaturesEx (HPROJECT, LPARAM);	// DEX_ENUMMERKMALEIDENTEX
	LRESULT OnEnumViewFeaturesEx (HPROJECT, LPARAM);	// DEX_ENUMMERKMALESICHTEX
	LRESULT OnEnumFeatureCodes (HPROJECT, LPARAM);	// DEX_ENUMALLMCODES
	LRESULT OnEnumSelObjects (HPROJECT, LPARAM);	// DEX_ENUMSELECTEDOBJECTS
	LRESULT OnEnumAllORObjects (HPROJECT, LPARAM);	// DEX_RECHERCHEDOBJECTS
	LRESULT OnEnumKObjectMember (HPROJECT, LPARAM);	// DEX_ENUMKOMPLOBJECTS
	LRESULT OnOpenProject (HPROJECT, LPARAM);		// DEX_PROJECTOPEN
	LRESULT OnCloseProject (HPROJECT, LPARAM);		// DEX_PROJECTCLOSE
	LRESULT OnSetAttributes (HPROJECT, LPARAM);		// DEX_SETATTRIBUTES
	LRESULT OnResetAttributes (HPROJECT, LPARAM);	// DEX_RESETATTRIBUTES
	LRESULT OnBeginPBDTransaction (HPROJECT, LPARAM);	// DEX_BEGINPBDTRANSACTION
	LRESULT OnBreakPBDTransaction (HPROJECT, LPARAM);	// DEX_BREAKPBDTRANSACTION
	LRESULT OnEndPBDTransaction (HPROJECT, LPARAM);	// DEX_ENDPBDTRANSACTION
	LRESULT OnQueryPBDVersion (HPROJECT, LPARAM);	// DEX_QUERYPBDVERSION
	LRESULT OnQueryPBDData (HPROJECT, LPARAM);		// DEX_QUERYPBDDATA
	LRESULT OnModPBDData (HPROJECT, LPARAM);		// DEX_MODPBDDATA
	LRESULT OnDelPBDData (HPROJECT, LPARAM);		// DEX_DELPBDDATA
	LRESULT OnEnumPBDData (HPROJECT, LPARAM);		// DEX_ENUMPBDDATA
	LRESULT OnQueryDrawingStatus (HPROJECT, LPARAM);	// DEX_QUERYDRAWINGSTATUS
	LRESULT OnQueryPrintingStatus (HPROJECT, LPARAM);	// DEX_QUERYISPRINTING
	LRESULT OnOCtoDCEx (HPROJECT, LPARAM);			// DEX_OCTODCEX
	LRESULT OnOCtoDC (HPROJECT, LPARAM);			// DEX_OCTODC
	LRESULT OnDCtoOCEx (HPROJECT, LPARAM);			// DEX_DCTOOCEX
	LRESULT OnDCtoOC (HPROJECT, LPARAM);			// DEX_DCTOOC
	LRESULT OnQueryActTool (HPROJECT, LPARAM);		// DEX_QUERYACTIVETOOL
	LRESULT OnSetActTool (HPROJECT, LPARAM);		// DEX_SETACTIVETOOL
	LRESULT OnEnumFoundObjects (HPROJECT, LPARAM);	// DEX_FINDOBJECT
	LRESULT OnModRelation (HPROJECT, LPARAM);		// DEX_MODRELATION
	LRESULT OnDelRelation (HPROJECT, LPARAM);		// DEX_DELRELATION
	LRESULT OnEnumRelations (HPROJECT, LPARAM);		// DEX_ENUMRELATIONS
	LRESULT OnEnumObjectRelations (HPROJECT, LPARAM);	// DEX_ENUMRELATIONOBJS
	LRESULT OnQueryIdentBase (HPROJECT, LPARAM);	// DEX_QUERYIDENTBASE
	LRESULT OnQueryMCodeBase (HPROJECT, LPARAM);	// DEX_QUERYMCODEBASE
	LRESULT OnQueryIdentObjectTypes (HPROJECT, LPARAM); // DEX_QUERYIDENTOBJTYPES
	LRESULT OnCreateGeoDB (HPROJECT, LPARAM);		// DEX_CREATENEWGEODB
	LRESULT OnCreatePBD (HPROJECT, LPARAM);			// DEX_CREATENEWIDENTSDB
	LRESULT OnSetError (HPROJECT, LPARAM);			// DEX_SETERROR
	LRESULT OnErrInstall (HPROJECT, LPARAM);		// DEX_ERRINSTALL
	LRESULT OnExtErrInstall (HPROJECT, LPARAM);		// DEX_EXTERRINSTALL
	LRESULT OnLoadExtension (HPROJECT, LPARAM);		// DEX_LOADEXTENSION
	LRESULT OnExtLoadExtension (HPROJECT, LPARAM);	// DEX_LOADEXTENSIONEX
	LRESULT OnUnLoadExtension (HPROJECT, LPARAM);	// DEX_UNLOADEXTENSION
	LRESULT OnExtUnLoadExtension (HPROJECT, LPARAM);	// DEX_UNLOADEXTENSIONEX
	LRESULT OnLoadExtension2 (HPROJECT, LPARAM);	// DEX_LOADEXTENSION2
	LRESULT OnUnLoadExtension2 (HPROJECT, LPARAM);	// DEX_UNLOADEXTENSION2
	LRESULT OnRenderGeoDB (HPROJECT, LPARAM);		// DEX_RENDERGEODB
	LRESULT OnQueryExposedOC (HPROJECT, LPARAM);	// DEX_QUERYEXPOSEDOC
	LRESULT OnQueryExposedArea (HPROJECT, LPARAM);	// DEX_QUERYEXPOSEDAREA
	LRESULT OnQueryIStorage (HPROJECT, LPARAM);		// DEX_QUERYPROJECTSTORAGE
	LRESULT OnQueryActPalette (HPROJECT, LPARAM);	// DEX_QUERYACTIVEPALETTE
	LRESULT OnShowMainWindow (HPROJECT, LPARAM);	// DEX_SHOWMAINWINDOW
	LRESULT OnHideMainWindow (HPROJECT, LPARAM);	// DEX_HIDEMAINWINDOW
	LRESULT OnQueryMainWindowVisible (HPROJECT, LPARAM); // DEX_QUERYMAINWINDOWVISIBLE
	LRESULT OnQuit (HPROJECT, LPARAM);				// DEX_QUITAPP
	LRESULT OnQueryDefaultDataPath (HPROJECT, LPARAM); // DEX_QUERYDEFAULTDATAPATH
	LRESULT OnModDefaultDataPath (HPROJECT, LPARAM);	// DEX_MODDEFAULTDATAPATH
	LRESULT OnCloseORWindows (HPROJECT, LPARAM);		// DEX_REMOVEORWND
	LRESULT OnNumOfOpenProjects (HPROJECT, LPARAM);	// DEX_QUERYOPENPROJECTS
	LRESULT OnQueryViewDescription (HPROJECT, LPARAM);	// DEX_QUERYVIEWDESCRIPTION
	LRESULT OnSetViewDescription (HPROJECT, LPARAM);	// DEX_MODVIEWDESCRIPTION
	LRESULT OnCancelMode (HPROJECT, LPARAM);		// DEX_CANCELMODE
	LRESULT OnQueryProjectCont (HPROJECT, LPARAM);	// DEX_QUERYPROJECTCONT
	LRESULT OnQueryObjectFeatureSpec (HPROJECT, LPARAM);	// DEX_QUERYOBJECTNAME
	LRESULT OnSetObjectFeatureSpec (HPROJECT, LPARAM);	// DEX_SETOBJECTNAME
	LRESULT OnEnableDiagnostics (HPROJECT, LPARAM);	// DEX_DIAGNOSTICSENABLE
	LRESULT OnQueryUnknownIdent (HPROJECT, LPARAM);	// DEX_GETUNKNOWNIDENT
	LRESULT OnFindObjFromName (HPROJECT, LPARAM);	// DEX_FINDOBJFROMNAME
	LRESULT OnQueryObjNameMCode (HPROJECT, LPARAM);	// DEX_QUERYOBJNAMEMCODE
	LRESULT OnQueryUniqueIdentMCode (HPROJECT, LPARAM);	// DEX_QUERYUNIQUEIDENTMCODE
	LRESULT OnQueryOldUniqueIdentMCode (HPROJECT, LPARAM);	// DEX_QUERYOLDUNIQUEIDENTMCODE
	LRESULT OnReReadHeader (HPROJECT, LPARAM);		// DEX_REREADHEADER
	LRESULT OnFindIdentFromName (HPROJECT, LPARAM);	// DEX_FINDIDENTFROMNAME
	LRESULT OnFindIdentFromNameCI (HPROJECT, LPARAM);	// DEX_FINDIDENTFROMNAMECI
	LRESULT OnDeleteIdent (HPROJECT, LPARAM);		// DEX_DELETEIDENT
	LRESULT OnViewCreate (HPROJECT, LPARAM);		// DEX_VIEWCREATE
	LRESULT OnViewCreateOpt (HPROJECT, LPARAM);		// DEX_VIEWCREATEOPT
	LRESULT OnRemoveIdentFromView (HPROJECT, LPARAM);	// DEX_DELETEIDENTFROMVIEW
	LRESULT OnViewRename (HPROJECT, LPARAM);		// DEX_VIEWRENAME
	LRESULT OnHasViewIdent (HPROJECT, LPARAM);		// DEX_HASVIEWIDENT
	LRESULT OnHasViewObject (HPROJECT, LPARAM);		// DEX_HASVIEWOBJECT
	LRESULT OnHasProjectView (HPROJECT, LPARAM);	// DEX_HASPROJECTVIEW
	LRESULT OnAddIdentToView (HPROJECT, LPARAM);	// DEX_IDENTADDTOVIEW
	LRESULT OnQueryAdminMode (HPROJECT, LPARAM);	// DEX_QUERYADMINMODE
	LRESULT OnSetAdminMode (HPROJECT, LPARAM);		// DEX_SETADMINMODE
#if defined(WIN32)
	LRESULT OnAddUndoRedo (HPROJECT, LPARAM);		// DEX_ADDUNDOREDOITEM
	LRESULT OnBeginUndoLevel (HPROJECT, LPARAM);	// DEX_UNDOLEVELBEGIN
	LRESULT OnEndUndoLevel (HPROJECT, LPARAM);		// DEX_UNDOLEVELEND
	LRESULT OnCancelUndoLevel (HPROJECT, LPARAM);	// DEX_UNDOLEVELCANCEL
	LRESULT OnDeleteObjectEx (HPROJECT, LPARAM);	// DEX_DELOBJECTEX
	LRESULT OnSaveSameStorage (HPROJECT, LPARAM);	// DEX_N_SAVESAMESTORAGE
	LRESULT OnSaveOtherStorage (HPROJECT, LPARAM);	// DEX_N_SAVEOTHERSTORAGE
	LRESULT OnHandsOffStorage (HPROJECT, LPARAM);	// DEX_N_HANDSOFFSTORAGE	
	LRESULT OnSaveCompleted (HPROJECT, LPARAM);		// DEX_N_SAVECOMPLETED
	LRESULT OnAttachPreTranslateMsgProc (HPROJECT, LPARAM);	// DEX_ATTACHPRETRANSLATEMSGPROC
	LRESULT OnAttachIdleProc (HPROJECT, LPARAM);	// DEX_ATTACHIDLEPROC
	LRESULT OnQueryActViewWindow (HPROJECT, LPARAM);	// DEX_QUERYACTIVEVIEWWINDOW
	LRESULT OnModObjectIdentEx (HPROJECT, LPARAM);	// DEX_MODOBJIDENTEX
	LRESULT OnGetObjectProps (HPROJECT, LPARAM);		// DEX_QUERYOBJECTPROPS
	LRESULT OnQueryCanUndo (HPROJECT, LPARAM);		// DEX_QUERYCANUNDO
	LRESULT OnQueryCanRedo (HPROJECT, LPARAM);		// DEX_QUERYCANREDO
	LRESULT OnSetMessageString (HPROJECT, LPARAM);	// DEX_SETSTRINGMESSAGE
	LRESULT OnSetMessageStringNoKickIdle (HPROJECT, LPARAM);	// DEX_SETSTRINGMESSAGENOKICKIDLE
	LRESULT OnCanCTFConfig (HPROJECT, LPARAM);		// DEX_CANCTFCONFIG
	LRESULT OnKickIdle (HPROJECT, LPARAM);			// DEX_KICKIDLE
	LRESULT OnIsHoldZoomActive (HPROJECT, LPARAM);	// DEX_QUERYHOLDZOOM
	LRESULT OnSetHoldZoom (HPROJECT, LPARAM);		// DEX_HOLDZOOMSET
	LRESULT OnProjectNameFromHandle (HPROJECT, LPARAM);	// DEX_PROJECTNAMEFROMHANDLE
	LRESULT OnOpenProjectEx (HPROJECT, LPARAM);		// DEX_PROJECTOPENEX
	LRESULT OnQueryInteractive (HPROJECT, LPARAM);		// DEX_QUERYINTERACTIVE
	LRESULT OnIdentFromClass (HPROJECT, LPARAM);	// DEX_IDENTFROMCLASS
	LRESULT OnClassFromIdent (HPROJECT, LPARAM);	// DEX_CLASSFROMIDENT
	LRESULT OnModObjClassCode (HPROJECT, LPARAM);	// DEX_MODOBJCLASSCODE
	LRESULT OnShowObjProp (HPROJECT, LPARAM);		// DEX_SHOWOBJPROP
	LRESULT OnGetShowObjProp (HPROJECT, LPARAM);	// DEX_GETSHOWOBJPROP
	LRESULT OnGetTRiASVersion (HPROJECT, LPARAM);	// DEX_QUERYTRIASVERSION
	LRESULT OnGetTRiASVersionLong (HPROJECT, LPARAM);	// DEX_QUERYTRIASVERSIONLONG
	LRESULT OnGetTRiASCaption (HPROJECT, LPARAM);	// DEX_QUERYTRIASCAPTION
	LRESULT OnSetTRiASCaption (HPROJECT, LPARAM);	// DEX_MODIFYTRIASCAPTION
	LRESULT OnGetIdentPriority (HPROJECT, LPARAM);	// DEX_QUERYIDENTPRIORITY
	LRESULT OnSetIdentPriority (HPROJECT, LPARAM);	// DEX_MODIFYIDENTPRIORITY
	LRESULT OnGetActObjProp (HPROJECT, LPARAM);		// DEX_QUERYACTOBJPROP
	LRESULT OnSelectObject (HPROJECT, LPARAM);		// DEX_OBJECTSELECTED
	LRESULT OnDeSelectObject (HPROJECT, LPARAM);	// DEX_OBJECTUNSELECTED
	LRESULT OnGetObjectGuid (HPROJECT, LPARAM);		// DEX_QUERYOBJECTGUID
	LRESULT OnFindObjectFromGuid (HPROJECT, LPARAM);		// DEX_FINDOBJECTGUID
	LRESULT OnSetObjectGuid (HPROJECT, LPARAM);		// DEX_SETOBJECTGUID
	LRESULT OnQueryPreventRepaint (HPROJECT, LPARAM);	// DEX_QUERYPREVENTREPAINT
	LRESULT OnPreventRepaint (HPROJECT, LPARAM);	// DEX_PREVENTREPAINT
	LRESULT OnGetActiveAspect (HPROJECT, LPARAM);	// DEX_QUERYACTASPECTRATIO
	LRESULT OnModifyIdentScaleData (HPROJECT, LPARAM);	// DEX_MODIFYIDENTSCALEDATA
	LRESULT OnGetIdentScaleData (HPROJECT, LPARAM);	// DEX_QUERYIDENTSCALEDATA
	LRESULT OnTestIdentScaleToPaint (HPROJECT, LPARAM);	// DEX_TESTIDENTSCALETOPAINT
#endif // WIN32
	LRESULT OnRCtoOC (HPROJECT, LPARAM);			// DEX_RCTOOC
	LRESULT OnOCtoRC (HPROJECT, LPARAM);			// DEX_OCTORC
	LRESULT OnIsORWindow (HPROJECT, LPARAM);		// DEX_ISOBJWINDOW
	LRESULT OnRePaintObject (HPROJECT, LPARAM);		// DEX_OBJECTREPAINT
	LRESULT OnEnumIdentViewsEx (HPROJECT, LPARAM);	// DEX_ENUMIDENTVIEWSEX
	LRESULT OnActivateAllORWnds (HPROJECT, LPARAM);	// DEX_ACTIVATEALLORWNDS
	LRESULT OnEnumFeatureCodesEx (HPROJECT, LPARAM);	// DEX_ENUMALLMCODESEX
	LRESULT OnFindMCodeFromName (HPROJECT, LPARAM);	// DEX_FINDFEATUREFROMNAME
	LRESULT OnFindMCodeFromNameCI (HPROJECT, LPARAM);	// DEX_FINDMCODEFROMNAMECI
	LRESULT OnSetDirtyGeoDB (HPROJECT, LPARAM);		// DEX_SETGEODBDIRTY
	LRESULT OnEnumProjects (HPROJECT, LPARAM);		// DEX_ENUMALLPROJECTS
	LRESULT OnGetProjectHandle (HPROJECT, LPARAM);	// DEX_PROJECTHANDLEFROMNAME
	LRESULT OnMakeProjectActive (HPROJECT, LPARAM);	// DEX_PROJECTMAKEACTIVE
	LRESULT	OnEnumORWindows (HPROJECT, LPARAM);		// DEX_ENUMOBJRECHWNDS
	LRESULT OnEnumSelObjectsEx (HPROJECT, LPARAM);	// DEX_ENUMSELECTEDOBJECTSEX
	LRESULT	OnGetIdentObjTypesActView (HPROJECT, LPARAM);	// DEX_QUERYIDENTOBJTYPESACTVIEW
	LRESULT OnReReadCaption (HPROJECT, LPARAM);		// DEX_CAPTIONREREAD
	LRESULT OnIsGeoDBDirty (HPROJECT, LPARAM);		// DEX_GETGEODBDIRTY
	LRESULT OnIsLegendActive (HPROJECT, LPARAM);	// DEX_QUERYLEGENDACTIVE
	LRESULT OnSetViewContainer (HPROJECT, LPARAM);	// DEX_QUERYACTVIEWCONTAINER
	LRESULT OnGetViewContainer (HPROJECT, LPARAM);	// DEX_MODACTVIEWCONTAINER
	LRESULT OnSetActiveScaling (HPROJECT, LPARAM);	// DEX_SETACTSCALING
	LRESULT OnTestActiveProject (HPROJECT, LPARAM);	// DEX_ACTIVEPROJECTTEST
	LRESULT OnCanvasErase (HPROJECT, LPARAM);		// DEX_ERASEVIEWCANVAS
	LRESULT OnGetObjectCount (HPROJECT, LPARAM);	// DEX_QUERYOBJECTCOUNT
	LRESULT OnGetClassCount (HPROJECT, LPARAM);		// DEX_QUERYCLASSCOUNT
	LRESULT OnGetViewCount (HPROJECT, LPARAM);		// DEX_QUERYVIEWCOUNT
	LRESULT OnGetClipObject (HPROJECT, LPARAM);		// DEX_QUERYCLIPOBJECT
	LRESULT OnSetClipObject (HPROJECT, LPARAM);		// DEX_CLIPOBJECTSET
	LRESULT OnGetActiveProjectHandle (HPROJECT, LPARAM);	// DEX_QUERYACTIVEPROJECTHANDLE
	LRESULT OnIsOverviewActive (HPROJECT, LPARAM);	// DEX_QUERYOVERVIEWACTIVE
	LRESULT OnIsCompatible (HPROJECT, LPARAM);		// DEX_QUERYCOMPATIBILITYMODE
	LRESULT OnSaveOverview (HPROJECT, LPARAM);		// DEX_OVERVIEWSAVE
	LRESULT OnGetIdentObjectCount (HPROJECT, LPARAM);	// DEX_QUERYIDENTOBJECTCOUNT

// #HK980527
	LRESULT OnEnumExtensions (HPROJECT, LPARAM);	// DEX_ENUMEXTENSIONS
	LRESULT OnGetExtensionInfo (HPROJECT, LPARAM);	// DEX_QUERYEXTENSIONINFO
	LRESULT OnGetExtensionPtr (HPROJECT, LPARAM);	// DEX_QUERYEXTENSIONPTR

// #HK980921
	LRESULT OnMustInitOPFs (HPROJECT, LPARAM);		// DEX_SETHAVETOINITOPFS
	LRESULT OnGetMustInitOPFs (HPROJECT, LPARAM);	// DEX_QUERYMUSTINITOPFS

#endif // DECLAREMAPFUNCTIONS

#endif // _EXTFCNS_HXX