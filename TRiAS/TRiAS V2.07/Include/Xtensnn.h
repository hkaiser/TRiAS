// Notifikationen -------------------------------------------------------------
// File: XTENSNN.H
// @doc
// @module XTENSNN.H | Enthält die Definition aller Makro's und Funktionen, die 
// für den bequemen Einsatz der Notifikationen von und an <tr> verwendet werden 
// können.
// @topic Notifikationen | Notifikationen sind spezielle Messages von <tr> an alle
// Erweiterungen, die eine bestimmte Notifikation angefordert (registriert) haben.
// Notifikationen geben Auskunft über bestimmte Ereignisse in <tr>, die in erster 
// Linie aus Nutzer-Interaktionen resultieren. Sie sind wichtig, damit Erweiterungen
// ständig über interne Programmzustände in <tr> auf dem laufenden gehalten werden 
// können.

#if !defined(_XTENSNN_H)
#define _XTENSNN_H

#include <pshpack1.h>

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(__XT)       // Module in DLL's
#if defined(__DEXPROCS)

extern DEXEXTENSIONPROC g_pDexExtensionProc;
extern DEXEXTENSIONPROC g_pDexxExtensionProc;
extern DEXNOTIFICATIONPROC g_pDexNotificationProc;

LRESULT WINAPI DexNotificationProc (WPARAM w, LPARAM l);
LRESULT WINAPI DexPostNotificationProc (WPARAM w, LPARAM l);
LRESULT WINAPI DexNotificationProcEx (WPARAM w, LPARAM l, bool fPost);

#else	// __DEXPROCS

// in den DLL's bleibt erstmal alles beim alten
#define DexNotificationProc(w,l) ::SendMessage(__hWndM,__DexNotify,(WPARAM)w,(LPARAM)l)
#define DexPostNotificationProc(w,l) ::PostMessage(__hWndM,__DexNotify,(WPARAM)w,(LPARAM)l)
	
#endif	// __DEXPROCS

#else	// Hauptmodul

// im Hauptmodul wird direkt eine exportierte Funktion gerufen
_TRIAS_ENTRY LRESULT WINAPI EXPORTTRIAS DexNotificationProc (WPARAM w, LPARAM l);
_TRIAS_ENTRY LRESULT WINAPI EXPORTTRIAS DexPostNotificationProc (WPARAM w, LPARAM l);
_TRIAS_ENTRY LRESULT WINAPI EXPORTTRIAS DexNotificationProcEx (WPARAM w, LPARAM l, bool fPost);

extern bool g_fDiagnostics;

#endif


#define DEXN_ErrorMessage(R,EC,RC,pD)	\
	{ ERRORMESSAGE __e; __e.emiErrCode=(short)EC;__e.emiRoutine=(short)RC;__e.empData=pD;	\
	R=(ErrCode)DexNotificationProc((WPARAM)DEX_ERRORMESSAGE,(LPARAM)&__e); }

#define DEXN_PostObjectDeActivated(l)	\
	DexPostNotificationProc((WPARAM)DEX_OBJECTDEACTIVATED,(LPARAM)l)
#define DEXN_PostObjectSelected(l)		\
	DexPostNotificationProc((WPARAM)DEX_OBJECTSELECTED,(LPARAM)l)
#define DEXN_PostObjectUnSelected(l)	\
	DexPostNotificationProc((WPARAM)DEX_OBJECTUNSELECTED,(LPARAM)l)
#define DEXN_PostObjectActivated(l)		\
	DexPostNotificationProc((WPARAM)DEX_OBJECTACTIVATED,(LPARAM)l)

#define DEXN_ObjectSelected(l)		\
	DexNotificationProc((WPARAM)DEX_OBJECTSELECTED,(LPARAM)l)
#define DEXN_ObjectUnSelected(l)	\
	DexNotificationProc((WPARAM)DEX_OBJECTUNSELECTED,(LPARAM)l)
#define DEXN_ObjectActivated(l)		\
	DexNotificationProc((WPARAM)DEX_OBJECTACTIVATED,(LPARAM)l)
#define DEXN_ObjectDeActivated(l)	\
	DexNotificationProc((WPARAM)DEX_OBJECTDEACTIVATED,(LPARAM)l)
#define DEXN_ObjectAddedToList(l)	\
	DexNotificationProc((WPARAM)DEX_ADDOBJECTTOLIST,(LPARAM)l)
#define DEXN_ObjectDeletedFromList(l)	\
	DexNotificationProc((WPARAM)DEX_REMOVEOBJECTFROMLIST,(LPARAM)l)

#define DEXN_QueryRechObject(l)		\
	(bool)DexNotificationProc((WPARAM)DEX_QUERYRECHOBJECT,(LPARAM)&(l))

#define DEXN_OpenProject(l)		\
	DexNotificationProc((WPARAM)DEX_PROJECTOPEN,(LPARAM)(void *)l)
#define DEXN_ViewCreated(l)		\
	DexNotificationProc((WPARAM)DEX_N_VIEWCREATED,(LPARAM)(l))
#define DEXN_ViewDeleted(l)		\
	DexNotificationProc((WPARAM)DEX_N_VIEWDELETED,(LPARAM)(l))
#define DEXN_CloseProject(l)		\
	DexNotificationProc((WPARAM)DEX_PROJECTCLOSE,(LPARAM)(void *)l)
#define DEXN_ProjectToClose(l)		\
	DexNotificationProc((WPARAM)DEX_N_PROJECTTOCLOSE,(LPARAM)(LPCSTR)(l))
#define DEXN_isClosedProject(l)		\
	DexNotificationProc((WPARAM)DEX_ISCLOSEDPROJECT,(LPARAM)(LPCSTR)(l))

#define DEXN_isCreatedProject(l)	\
	DexNotificationProc((WPARAM)DEX_CREATENEWGEODB,(LPARAM)(l))

#define DEXN_SightSelected(l)		\
	DexNotificationProc((WPARAM)DEX_SIGHTSELECTED,(LPARAM)l)
#define DEXN_SightToSelect(l)		\
	DexNotificationProc((WPARAM)DEX_SIGHTTOSELECT,(LPARAM)l)
#define DEXN_SightToDelete(l)		\
	DexNotificationProc((WPARAM)DEX_DELETEVIEW,(LPARAM)l)
#define DEXN_SightDeleted(l)		\
	DexNotificationProc((WPARAM)DEX_SIGHTDELETED,(LPARAM)l)
#define DEXN_SightCreated(l)		\
	DexNotificationProc((WPARAM)DEX_VIEWCREATED,(LPARAM)&(l))
#define DEXN_ScalingChanged(l)		\
	DexNotificationProc((WPARAM)DEX_N_SCALINGCHANGED,(LPARAM)(l))

#define DEXN_DeletingObject(l)		\
	(bool)DexNotificationProc((WPARAM)DEX_OBJECTTODELETE,(LPARAM)l)
#define DEXN_ObjectDeleted(l)		\
	DexNotificationProc((WPARAM)DEX_DELOBJECT,(LPARAM)l)
#define DEXN_ObjectToDelete(l)		\
	DexNotificationProc((WPARAM)DEX_N_TODELETEOBJECT,(LPARAM)l)

#define DEXN_DrawIdentifikator(l)	\
	(short)DexNotificationProc((WPARAM)DEX_DRAWIDENT,(LPARAM)l)
#define DEXN_DrawObject(l)		\
	(short)DexNotificationProc((WPARAM)DEX_DRAWOBJECT,(LPARAM)&(l))
#define DEXN_DrawIdentifikatorEx(l)	\
	DexNotificationProc((WPARAM)DEX_DRAWIDENTEX,(LPARAM)&(l))
#define DEXN_DrawObjectEx(l)		\
	DexNotificationProc((WPARAM)DEX_DRAWOBJECT,(LPARAM)&(l))

#if defined(WIN32)
#define DEXN_ObjWndFocusChanged(hWnd,iFlag)	\
	DexNotificationProc((iFlag)?(WPARAM)DEX_GOTOBJWNDFOCUS:(WPARAM)DEX_LOSTOBJWNDFOCUS,(LPARAM)(void *)hWnd)
#else
#define DEXN_ObjWndFocusChanged(hWnd,iFlag)	\
	DexPostNotificationProc((WPARAM)DEX_OBJWNDFOCUSCHANGED,(LPARAM)MAKELONG(iFlag,hWnd))
#endif
#define DEXN_PostRechObjWindowCreated(hWnd)	\
	DexPostNotificationProc((WPARAM)DEX_CREATEOBJEKTINFO,(LPARAM)(void *)(hWnd))
#define DEXN_RechObjWindowCreated(hWnd)	\
	DexNotificationProc((WPARAM)DEX_CREATEOBJEKTINFO,(LPARAM)(void *)(hWnd))
#define DEXN_RechObjWindowClosed(hWnd)	\
	(bool)DexNotificationProc((WPARAM)DEX_OBJWNDCLOSED,(LPARAM)(void *)(hWnd))

#define DEXN_PBDIdentsChanged()	\
	DexNotificationProc((WPARAM)DEX_TXICHANGED,0L)
#define DEXN_PBDMCodesChanged()	\
	DexNotificationProc((WPARAM)DEX_TXMCHANGED,0L)
#define DEXN_PBDRCodesChanged()	\
	DexNotificationProc((WPARAM)DEX_TXRCHANGED,0L)
#define DEXN_PBDIdentChanged(l)	\
	DexNotificationProc((WPARAM)DEX_TXICHANGED,(LPARAM)(l))
#define DEXN_PBDMCodeChanged(l)	\
	DexNotificationProc((WPARAM)DEX_TXMCHANGED,(LPARAM)(l))
#define DEXN_PBDRCodeChanged(l)	\
	DexNotificationProc((WPARAM)DEX_TXRCHANGED,(LPARAM)(l))

#define DEXN_SetNewPalette(l)	\
	DexNotificationProc((WPARAM)DEX_SETNEWPALETTE,(LPARAM)(void *)&(l))
#define DEXN_EraseBackGround(phDC)	\
	DexNotificationProc((WPARAM)DEX_ERASEBKGND,(LPARAM)(phDC))
#define DEXN_PaintTopLayer(phDC)	\
	DexNotificationProc((WPARAM)DEX_PAINTTOPLAYER,(LPARAM)(phDC))
	
#define DEXN_ActiveToolChanged(l)	\
	DexPostNotificationProc((WPARAM)DEX_SETACTIVETOOL,(LPARAM)l)

#define DEXN_ServerInitialized()	\
	DexPostNotificationProc((WPARAM)DEX_INITIALIZEDSERVER,0)
#define DEXN_ExtensionsLoaded()	\
	(bool)DexNotificationProc((WPARAM)DEX_N_EXTENSIONSLOADED,0)
#define DEXN_UIReady()	\
	(bool)DexNotificationProc((WPARAM)DEX_N_UIREADY,0)
#define DEXN_ServerIsClosing()		\
	(bool)DexNotificationProc((WPARAM)DEX_SERVERISCLOSING,0)
#define DEXN_ServerClosed()		\
	(bool)DexNotificationProc((WPARAM)DEX_SERVERCLOSED,0)
	
#define DEXN_ReScale()			\
	(bool)DexNotificationProc((WPARAM)DEX_RESCALE,0)
#define DEXN_ReReadIdents()		\
	(bool)DexNotificationProc((WPARAM)DEX_REREADIDENTS,0)
#define DEXN_ReReadContainer()		\
	DexNotificationProc((WPARAM)DEX_REREADCONTAINER,0)
#define DEXN_ReReadSights(l)		\
	DexNotificationProc((WPARAM)DEX_REREADSIGHTS,(LPARAM)l)

#define DEXN_IdentDeleted(l)		\
	(bool)DexNotificationProc((WPARAM)DEX_DELETEIDENT,(LPARAM)l)
#define DEXN_DeletingIdent(l)		\
	(bool)DexNotificationProc((WPARAM)DEX_IDENTTODELETE,(LPARAM)l)

#define DEXN_EmbeddingHandled()		\
	(bool)DexNotificationProc((WPARAM)DEX_HANDLEEMBEDDING,(LPARAM)0L)
#define DEXN_AutomationHandled()	\
	(bool)DexNotificationProc((WPARAM)DEX_HANDLEAUTOMATION,(LPARAM)0L)
#define DEXN_TipOfTheDay(l)	\
	(bool)DexNotificationProc((WPARAM)DEX_N_TIPOFTHEDAY,(LPARAM)(l))

#define DEXN_IdentToModify(l)		\
	(bool)DexNotificationProc((WPARAM)DEX_MODIFYINGIDENT,(LPARAM)l)
#define DEXN_IdentModified(l)		\
	(bool)DexNotificationProc((WPARAM)DEX_IDENTWASMODIFIED,(LPARAM)l)

#define DEXN_FeatureModified(l)		\
	(bool)DexNotificationProc((WPARAM)DEX_MODIFYMERKMAL,(LPARAM)l)

#define DEXN_CoordFormatChanged()		\
	(bool)DexNotificationProc((WPARAM)DEX_COORDFORMATWASCHANGED,(LPARAM)0L)

#define DEXN_GeoDBisDirty(l)	\
	DexNotificationProc((WPARAM)DEX_SETGEODBDIRTY,(LPARAM)l)

#define DEXN_DialogBegin(l)	\
	DexNotificationProc((WPARAM)DEX_BEGINDIALOG,(LPARAM)(void *)l)
#define DEXN_DialogEnd(l)	\
	DexNotificationProc((WPARAM)DEX_ENDDIALOG,(LPARAM)(void *)l)

#define DEXN_ChangingObject(l)	\
	DexNotificationProc((WPARAM)DEX_CHANGINGOBJECT,(LPARAM)l)
#define DEXN_ObjectChanged(l)	\
	DexNotificationProc((WPARAM)DEX_OBJECTCHANGED,(LPARAM)l)

#define DEXN_ReReadHeader()		\
	(bool)DexNotificationProc((WPARAM)DEX_HEADERREREAD,0)
#define DEXN_ReReadHeaderEx(l)		\
	(bool)DexNotificationProc((WPARAM)DEX_HEADERREREAD,(LPARAM)(l))

#define DEXN_SaveSameStorage(pStgSave)	\
	(HRESULT)DexNotificationProc((WPARAM)DEX_N_SAVESAMESTORAGE,(LPARAM)(pStgSave))
#define DEXN_SaveOtherStorage(pStgSave)	\
	(HRESULT)DexNotificationProc((WPARAM)DEX_N_SAVEOTHERSTORAGE,(LPARAM)(pStgSave))
#define DEXN_SaveCompleted(pStgSave)	\
	(HRESULT)DexNotificationProc((WPARAM)DEX_N_SAVECOMPLETED,(LPARAM)(pStgSave))
#define DEXN_HandsOffStorage()	\
	(HRESULT)DexNotificationProc((WPARAM)DEX_N_HANDSOFFSTORAGE,0)
#define DEXN_RenamingFile(l)	\
	(HRESULT)DexNotificationProc((WPARAM)DEX_N_RENAMINGFILE,(LPARAM)(l))
#define DEXN_FileRenamed(l)	\
	(HRESULT)DexNotificationProc((WPARAM)DEX_N_FILERENAMED,(LPARAM)(l))

#define DEXN_ScrollingHorz(l)	\
	(HRESULT)DexNotificationProc((WPARAM)DEX_N_SCROLLING_HORZ,(l))
#define DEXN_ScrollingVert(l)	\
	(HRESULT)DexNotificationProc((WPARAM)DEX_N_SCROLLING_VERT,(l))

#define DEXN_PrintingProject()	\
	(bool)DexNotificationProc((WPARAM)DEX_N_PRINTINGPROJECT,0)
#define DEXN_ProjectPrinted()	\
	(bool)DexNotificationProc((WPARAM)DEX_N_PROJECTPRINTED,0)

#define DEXN_ShowToolTips(l)	\
	DexNotificationProc((WPARAM)DEX_N_SHOWTOOLTIPS,(LPARAM)(l))
#define DEXN_EnableCoolLook(l)	\
	DexNotificationProc((WPARAM)DEX_N_ENABLECOOLLOOK,(LPARAM)(l))
#define DEXN_ShowProjectWizard(l)	\
	DexNotificationProc((WPARAM)DEX_N_SHOWPROJECTWIZARD,(LPARAM)(l))

#define DEXN_AddedObjectProperty()	\
	DexNotificationProc((WPARAM)DEX_N_ADDEDOBJECTPROPERTY,0)
#define DEXN_AddedClassProperty()	\
	DexNotificationProc((WPARAM)DEX_N_ADDEDCLASSPROPERTY,0)
#define DEXN_RemovedObjectProperty()	\
	DexNotificationProc((WPARAM)DEX_N_REMOVEDOBJECTPROPERTY,0)
#define DEXN_RemovedClassProperty()	\
	DexNotificationProc((WPARAM)DEX_N_REMOVEDCLASSPROPERTY,0)

///////////////////////////////////////////////////////////////////////////////
// Notifikationen, die von Erweiterungen verschickt werden
#define DEXN_ScriptingEngineActive()	\
	DexNotificationProc((WPARAM)DEX_N_SCRIPTINGENGINEACTIVE,0)

// #WM970814
#define DEXN_ObjectSplitted(l)	\
	DexNotificationProc((WPARAM)DEX_N_OBJECTSPLITTED,(LPARAM)&(l))
#define DEXN_ObjectCreated(l)	\
	DexNotificationProc((WPARAM)DEX_N_OBJECTCREATED,(LPARAM)(l))

#if defined(__cplusplus)
}
#endif

#include <poppack.h>

#endif // _XTENSNN_H
