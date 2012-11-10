// Fuktionen, die bei Notifikationen gerufen werden ---------------------------
// File EXTFCNSN.HXX
//
// 03.03.2001 18:40:26
//		Added: support for DEX_N_HIDEORSHOWPROJECTWINDOW

#if !defined(_EXTFCNSN_HXX)
#define _EXTFCNSN_HXX

#if defined(DECLAREMAPFUNCTIONS_NOTIFY)

///////////////////////////////////////////////////////////////////////////////
// nicht belegte Notification
	LRESULT OnNotUsedNotification (LPARAM lParam);	// noop

///////////////////////////////////////////////////////////////////////////////
// interne NotifikationsBearbeitung
	LRESULT doNfySetNewPalette (LPARAM lParam);		// DEX_SETNEWPALETTE
	LRESULT doNfyReScale (LPARAM lParam);			// DEX_RESCALE
	LRESULT doNfyReReadIdents (LPARAM lParam);		// DEX_REREADIDENTS
	LRESULT doNfyReReadContainer (LPARAM lParam);	// DEX_REREADCONTAINER
	LRESULT doNfyReReadViews (LPARAM lParam);		// DEX_REREADSIGHTS
	LRESULT doNfyReReadHeader (LPARAM lParam);		// DEX_HEADERREREAD
	LRESULT doNfyReReadObjectProps (LPARAM lParam);	// DEX_N_REREADOBJPROPS
	LRESULT doNfyHandleDeleteMenu (LPARAM lParam);	// DEX_SETACTIVETOOL
	LRESULT doNfyHandleDeletingObject (LPARAM lParam);	// DEX_OBJECTTODELETE
	LRESULT doNfyHandleObjectDeleted (LPARAM lParam);	// DEX_DELOBJECT
	LRESULT doNfyIdentToModify (LPARAM lParam);		// DEX_MODIFYINGIDENT
	LRESULT doNfyIdentModified (LPARAM lParam);		// DEX_IDENTWASMODIFIED
	LRESULT doNfyFeatureSetModified (LPARAM lParam);	// DEX_N_MODIFYMERKMALSET
	LRESULT doNfyHandleToDeleteObject (LPARAM lParam);	// DEX_N_TODELETEOBJECT
	LRESULT doNfyQueryRechObject (LPARAM lParam);	// DEX_QUERYRECHOBJECT
	LRESULT doNfyTXIChanged (LPARAM lParam);		// DEX_TXICHANGED
	LRESULT doNfyTXMChanged (LPARAM lParam);		// DEX_TXMCHANGED
	LRESULT doNfyTXRChanged (LPARAM lParam);		// DEX_TXRCHANGED
	LRESULT doNfyViewCreated (LPARAM lParam);		// DEX_VIEWCREATED
	LRESULT doNfyViewDeleted (LPARAM lParam);		// DEX_SIGHTDELETED
	LRESULT doNfyDeleteView (LPARAM lParam);		// DEX_DELETEVIEW
	LRESULT doNfyORWndFocusChanged (LPARAM lParam);	// DEX_GOTOBJWNDFOCUS
	LRESULT doNfyUpdateCoordFormat (LPARAM lParam);	// DEX_COORDFORMATWASCHANGED
	LRESULT doNfySetDirty (LPARAM lParam);			// DEX_SETGEODBDIRTY
	LRESULT doNfyExtensionsLoaded (LPARAM lParam);	// DEX_N_EXTENSIONSLOADED
	LRESULT doNfyInitialized (LPARAM lParam);		// DEX_INITIALIZEDSERVER
	LRESULT doNfyClosingApp (LPARAM lParam);		// DEX_SERVERISCLOSING
	LRESULT doNfyAppClosed (LPARAM lParam);			// DEX_SERVERCLOSED
	LRESULT doNfySelectingView (LPARAM lParam);		// DEX_SIGHTTOSELECT
	LRESULT doNfyViewSelected (LPARAM lParam);		// DEX_SIGHTSELECTED
	LRESULT doNfyProjectOpened (LPARAM lParam);		// DEX_PROJECTOPEN
	LRESULT doNfyClosingProject (LPARAM lParam);	// DEX_ISCLOSEDPROJECT
	LRESULT doNfyProjectClosed (LPARAM lParam);		// DEX_PROJECTCLOSE
	LRESULT doNfyProjectToClose (LPARAM lParam);	// DEX_N_PROJECTTOCLOSE
	LRESULT doNfyScalingChanged (LPARAM lParam);	// DEX_N_SCALINGCHANGED
	LRESULT doNfyShowToolTips (LPARAM lParam);		// DEX_N_SHOWTOOLTIPS
	LRESULT doNfyPaintingView (LPARAM lParam);		// DEX_ERASEBKGND
	LRESULT doNfyViewPainted (LPARAM lParam);		// DEX_PAINTTOPLAYER
	LRESULT doNfyFeatureModified (LPARAM lParam);	// DEX_MODIFYMERKMAL
	LRESULT doNfyFeatureModifiedEx (LPARAM lParam);	// DEX_N_MODIFYMERKMAL
// Objektrecherchefenster
	LRESULT doNfyObjectSelected (LPARAM lParam);	// DEX_OBJECTSELECTED
	LRESULT doNfyObjectUnselected (LPARAM lParam);	// DEX_OBJECTUNSELECTED
	LRESULT doNfyObjectActivated (LPARAM lParam);	// DEX_OBJECTACTIVATED
	LRESULT doNfyObjectDeactivated (LPARAM lParam);	// DEX_OBJECTDEACTIVATED
	LRESULT doNfyCreateORWnd (LPARAM lParam);		// DEX_CREATEOBJEKTINFO
	LRESULT doNfyCloseORWnd (LPARAM lParam);		// DEX_OBJWNDCLOSED
	LRESULT doNfyRenamingFile (LPARAM lParam);		// DEX_N_RENAMINGFILE
	LRESULT doNfyFileRenamed (LPARAM lParam);		// DEX_N_FILERENAMED
	LRESULT doNfyObjectChanged (LPARAM lParam);		// DEX_OBJECTCHANGED
	LRESULT doNfyChangingObject (LPARAM lParam);	// DEX_CHANGINGOBJECT
	LRESULT doNfyObjectCreated (LPARAM lParam);		// DEX_N_OBJECTCREATED
	LRESULT doNfyScrollingVert (LPARAM lParam);		// DEX_N_SCROLLING_VERT
	LRESULT doNfyScrollingHorz (LPARAM lParam);		// DEX_N_SCROLLING_HORZ
#if !defined(WIN16)
	LRESULT doNfySetFocus (LPARAM lParam);			// DEX_GOTOBJWNDFOCUS
	LRESULT doNfyKillFocus (LPARAM lParam);			// DEX_LOSTOBJWNDFOCUS
	LRESULT doNfyChangedObjectProperties (LPARAM lParam);	// DEX_N_...OBJECTPROPERTY
	LRESULT doNfyObjectSplitted (LPARAM lParam);	// DEX_OBJECTSPLITTED
#endif // WIN16

// #HK010303
	LRESULT doNfyProjectWindowShownOrHidden(LPARAM lParam);	// DEX_N_HIDEORSHOWPROJECTWINDOW

// #HK021217
	LRESULT doNfyAddingObject(LPARAM lParam);		// DEX_N_ADDINGOBJECT
	LRESULT doNfyObjectToAdd(LPARAM lParam);		// DEX_N_OBJECTTOADD
	LRESULT doNfyObjectAdded(LPARAM lParam);		// DEX_N_OBJECTADDED

#endif // DECLAREMAPFUNCTIONS_NOTIFY

#endif // _EXTFCNSN_HXX
