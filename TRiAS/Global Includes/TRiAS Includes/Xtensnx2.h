// Messagebreaking-Makros fuer Extension-Schnittstelle ------------------------
// File: XTENSNX2.H
// @doc
// @module XTENSNX2.H | Enthält die Definition aller Makro's und Funktionen, die 
// für den bequemen Einsatz der Messages an <tr> verwendet werden können.

#if !defined(_XTENSNX2_H)
#define _XTENSNX2_H

#if defined(WIN16)
#undef NEWXTENSIONPROC
#endif // WIN16

#include <pshpack1.h>

///////////////////////////////////////////////////////////////////////////////
// Makros zur Vereinfachnung des Aufrufes verschiedener Funktionen über die
// ErweiterungsSchnittstelle
//
// Diese Macros gehen davon aus, daß das HauptFensterHandle in (globalen)
// Variable __hWndM und die beiden MessageWerte in den (globalen) Variablen
// __DexCmd und __DexReg gespeichert sind.
extern "C" HWND __hWndM;

extern "C" UINT __DexCmd;
extern "C" UINT __DexReg;
extern "C" UINT __DexUnReg;
extern "C" UINT __DexNotify;
extern "C" UINT __DexxCmd;

#if defined(__XT)       // Module in DLL's

#if defined(__DEXPROCS)
///////////////////////////////////////////////////////////////////////////////
// Die 'Messages' sind jetzt Rufe einer exportierten Funktion
extern "C" DEXEXTENSIONPROC2 g_pDexExtensionProc;
extern "C" DEXEXTENSIONPROC2 g_pDexxExtensionProc;
extern "C" DEXNOTIFICATIONPROC g_pDexNotificationProc;

extern "C" LRESULT WINAPI DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l);
#define DexORExtensionProc(h,w,l)		::SendMessage((h),__DexCmd,(WPARAM)(w),(LPARAM)(l))
// die vorherige Zeile wird bald ersetzt durch die folgenden: 
//LRESULT WINAPI DexORExtensionProc2 (HPROJECT hPr, HWND hWnd, WPARAM w, LPARAM l);
//#define DexORExtensionProc(h,w,l)		DexORExtensionProc2(hPr,(h),(WPARAM)(w),(LPARAM)(l))

#else	// __DEXPROCS
///////////////////////////////////////////////////////////////////////////////
// in den DLL's bleibt erstmal alles beim alten
#define DexExtensionProc(w,l)		::SendMessage(__hWndM,__DexCmd,(WPARAM)(w),(LPARAM)(l))
#define DexExtensionProc2(h,w,l)	::SendMessage(__hWndM,__DexCmd,(WPARAM)(w),(LPARAM)(l))
#define DexORExtensionProc(h,w,l)	::SendMessage((h),__DexCmd,(WPARAM)(w),(LPARAM)(l))
#endif 	// __DEXPROCS

#else	// __XT (HauptModul)

///////////////////////////////////////////////////////////////////////////////
// im Hauptmodul wird direkt eine exportierte Funktion gerufen
extern HINSTANCE hInstance;
extern "C" _TRIAS_ENTRY LRESULT WINAPI EXPORTTRIAS DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l);
#define DexORExtensionProc(h,w,l)	::SendMessage((h),__DexCmd,(WPARAM)(w),(LPARAM)(l))
// die vorherige Zeile wird bald ersetzt durch die folgenden: 
//LRESULT WINAPI DexORExtensionProc2 (HPROJECT hPr, HWND hWnd, WPARAM w, LPARAM l);
//#define DexORExtensionProc(h,w,l)		DexORExtensionProc2(hPr,(h),(WPARAM)(w),(LPARAM)(l))

extern "C" _TRIAS_ENTRY LRESULT WINAPI EXPORTTRIAS DexDispatchProc (HWND hWnd, UINT uiMsg, WPARAM w, LPARAM l);

#endif	// __XT

///////////////////////////////////////////////////////////////////////////////
// eigentliche MessageBreakingMakros ------------------------------------------

// Verwaltung von Erweiterungen -----------------------------------------------

// @func HMENU | DEX_InstallMenuItem | Installieren eines zusätzlichen Menupunktes in <tr>.
// @parm INSTALLMENUITEM & | rInstallItem | Referenz einer Struktur vom Typ <t INSTALLMENUITEM>.
// @rdesc Liefert das Handle des Popupmenus, in dem der Menupunkt installiert wurde bzw. im Fehlerfall NULL.
// @xref <t INSTALLMENUITEM>, <m DEX_MENUITEMINSTALL>
#define DEX_InstallMenuItem(l)          \
	(HMENU)DexExtensionProc((WPARAM)DEX_MENUITEMINSTALL,(LPARAM)&(l))

// @func void | DEX_RemoveMenuItem | Entfernen eines zusätzlich installierten 
// Menupunktes in <tr>
// @parm REMOVEMENUITEM & | rRemoveItem | Referenz einer Struktur vom Typ <t REMOVEMENUITEM>.
// @xref <t REMOVEMENUITEM>, <m DEX_MENUITEMREMOVE>
#define DEX_RemoveMenuItem(l)           \
	DexExtensionProc((WPARAM)DEX_MENUITEMREMOVE,(LPARAM)&(l))
#define DEX_ExternalLoadExtension(l)	\
	(HDEX)DexExtensionProc((WPARAM)DEX_LOADEXTENSION,(LPARAM)(l))
#define DEX_ExternalUnLoadExtension(l)	\
	(bool)DexExtensionProc((WPARAM)DEX_UNLOADEXTENSION,(LPARAM)(l))
#define DEX_ExternalLoadExtensionEx(l)	\
	(HDEX)DexExtensionProc((WPARAM)DEX_LOADEXTENSIONEX,(LPARAM)&(l))
#define DEX_ExternalUnLoadExtensionEx(l)	\
	(bool)DexExtensionProc((WPARAM)DEX_UNLOADEXTENSIONEX,(LPARAM)&(l))

// @func short | DEX_InstallTool | Installieren eines zusätzlichen Werkzeuges in <tr>.
// @parm INSTALLTOOL & | rInstallTool | Referenz auf Struktur vom Typ <t INSTALLTOOL>
// @rdesc Liefert den Werkzeug-ID des neu installierten Werkzeuges bzw. im Fehlerfall -1.
// @xref <t INSTALLTOOL>, <m DEX_TOOLINSTALL>
#define DEX_InstallTool(l)              \
	(short)DexExtensionProc((WPARAM)DEX_TOOLINSTALL,(LPARAM)&(l))

// @func void | DEX_RemoveTool | Enfernen eines zusätzlich installierten Werkzeuges in <tr>.
// @parm short | iToolID | Werkzeug-ID des zu entfernenden Werkzeuges.
// @xref <m DEX_TOOLREMOVE>
#define DEX_RemoveTool(l)               \
	DexExtensionProc((WPARAM)DEX_TOOLREMOVE,(LPARAM)l)

// Anfragen zu selektierten Objekten
#define DEX_GetPBDName(hPr,l)               \
	(char *)DexExtensionProc2(hPr,(WPARAM)DEX_QUERYACTIVEPBD,(LPARAM)(l))
#define DEX_ModPBDName(hPr,l)               \
	DexExtensionProc2(hPr,(WPARAM)DEX_MODIFYPBDNAME,(LPARAM)(l))
#define DEX_GetActiveObject(hWnd)       \
	(long)DexExtensionProc((WPARAM)DEX_QUERYACTIVEOBJECT,(LPARAM)(void *)hWnd)
#define DEX_ActivateAllObjects(hWnd)       \
	(bool)DexExtensionProc((WPARAM)DEX_ACTIVATEALLORWNDS,(LPARAM)(void *)hWnd)
#define DEX_ActiveObjectsCount()        \
	(short)DexExtensionProc((WPARAM)DEX_QUERYCNTACTIVEOBJECTS,0L)
#define DEXOR_SelectedObjectsCount(hWnd,l)      \
	DexORExtensionProc(hWnd,(WPARAM)DEX_QUERYCNTACTIVEOBJECTS,(LPARAM)l)
#define DEX_GetAllActiveObjects(l)      \
	DexExtensionProc((WPARAM)DEX_QUERYALLACTIVEOBJECTS,(LPARAM)(l))
#define DEXOR_AddObjectToList(hWnd,l)	\
	DexORExtensionProc(hWnd,(WPARAM)DEX_ADDOBJECTTOLIST,(LPARAM)(l))
#define DEXOR_RemoveFromListObject(hWnd,l)	\
	DexORExtensionProc(hWnd,(WPARAM)DEX_REMOVEOBJECTFROMLIST,(LPARAM)(l))
#define DEXOR_QueryRechercheStatus(hWnd,l)	\
	DexORExtensionProc(hWnd,(WPARAM)DEX_RECHOBJECTSTATUS,(LPARAM)&(l))
#define DEXOR_ActivateObject(hWnd,l)	\
	DexORExtensionProc(hWnd,(WPARAM)DEX_OBJECTACTIVATED,(LPARAM)(l))
#define DEXOR_SelectObject(hWnd,l)	\
	DexORExtensionProc(hWnd,(WPARAM)DEX_OBJECTSELECTED,(LPARAM)(l))
#define DEXOR_UnselectObject(hWnd,l)	\
	DexORExtensionProc(hWnd,(WPARAM)DEX_OBJECTUNSELECTED,(LPARAM)(l))
#define DEXOR_QuerySelectedObjectTypes(hWnd,iOTypes)	\
	(short)DexORExtensionProc(hWnd,(WPARAM)DEX_GETSELECTEDTYPES,(LPARAM)&(iOTypes))

// @func char * | DEX_GetActiveProject | Abfragen des vollen Namens des aktuellen Projektes.
// @parm char * | pProjectName | Pufferbereich, in dem der Name zurückgeliefert werden soll.
// @rdesc Liefert <p pProjectName> bzw. im Fehlerfall NULL.
// @xref <m DEX_QUERYACTIVEPROJECT>
#define DEX_GetActiveProject(l)         \
	(char *)DexExtensionProc((WPARAM)DEX_QUERYACTIVEPROJECT,(LPARAM)(l))
#define DEX_EnumProjects(l)	\
	(bool)DexExtensionProc((WPARAM)DEX_ENUMALLPROJECTS,(LPARAM)&(l))
#define DEX_GetProjectHandle(l)	\
	(HPROJECT)DexExtensionProc((WPARAM)DEX_PROJECTHANDLEFROMNAME,(LPARAM)(l))
#define DEX_MakeProjectActive(l)	\
	(HPROJECT)DexExtensionProc((WPARAM)DEX_PROJECTMAKEACTIVE,(LPARAM)(l))

// @func char * | DEX_GetActiveUser | Abfragen des Namens des Nutzers des aktuellen Projektes.
// @parm char * | pUserName | Pufferbereich, in dem der Name zurückgeliefert werden soll.
// @rdesc Liefert <p pUserName> bzw. im Fehlerfall NULL.
// @xref <m DEX_QUERYACTIVEUSER>
#define DEX_GetActiveUser(hPr,l)            \
	(char *)DexExtensionProc2(hPr,(WPARAM)DEX_QUERYACTIVEUSER,(LPARAM)(l))

// @func bool | DEX_GetROMode | Abfragen des Zugriffsmodes des aktuellen Projektes.
// @rdesc Liefert <t true> bei Schreibschutz und <t false> bei vollen Scheibrechten bzw. im Fehlerfall -1.
// @xref <m DEX_QUERYROMODE>
#define DEX_GetROMode(hPr)                 \
	(bool)DexExtensionProc2(hPr,(WPARAM)DEX_QUERYROMODE,0)

// @func char * | DEX_GetMainIniName | Abfragen des Namens der Initialisierungsdatei von <tr>.
// @parm char * | pIniName | Pufferbereich, in dem der volle Dateiname zurückgeliefert werden soll.
// @rdesc Liefert <p pIniName> bzw. im Fehlerfall NULL.
// @xref <m DEX_QUERYMAINININAME>
#define DEX_GetMainIniName(l)           \
	(char *)DexExtensionProc((WPARAM)DEX_QUERYMAINININAME,(LPARAM)(l))

// @func char * | DEX_GetActiveSight | Abfragen der aktuellen Ansicht des aktuellen Projektes.
// @parm char * | pViewName | Pufferbereich, in dem der Name der Ansicht zurückgeliefert werden soll.
// @rdesc Liefert <p pViewName> bzw. im Fehlerfall NULL.
// @xref <m DEX_QUERYACTIVESIGHT>
#define DEX_GetActiveSight(hPr,l)           \
	(char *)DexExtensionProc2(hPr,(WPARAM)DEX_QUERYACTIVESIGHT,(LPARAM)l)

// @func DWORD | DEX_GetDBVersion | Abfragen der Versionsnummer des aktuellen Projektes.
// @rdesc Liefert die Versionsnummer des aktuellen Projektes bzw. Null, wenn kein 
// aktuelles Projekt existiert.
// @xref <m DEX_QUERYGEODBVERSION>
#define DEX_GetDBVersion(hPr)              \
	DexExtensionProc2(hPr,(WPARAM)DEX_QUERYGEODBVERSION,(LPARAM)0)
#define DEX_GetActiveSightContainer(hPr,l)  \
	DexExtensionProc2(hPr,(WPARAM)DEX_QUERYACTSIGHTCONTAINER,(LPARAM)&(l))
#define DEX_SetActiveSightContainer(hPr,l)  \
	DexExtensionProc2(hPr,(WPARAM)DEX_SETACTSIGHTCONTAINER,(LPARAM)&(l))
#define DEX_GetActiveSelection(l)       \
	(bool)DexExtensionProc((WPARAM)DEX_QUERYACTIVESELECTION,(LPARAM)(l))
#define DEX_GetIdentVisInfo(hPr,l)          \
	(bool)DexExtensionProc2(hPr,(WPARAM)DEX_QUERYIDENTVISINFO,(LPARAM)&(l))
#define DEX_ModIdentVisInfo(hPr,l)          \
	(bool)DexExtensionProc2(hPr,(WPARAM)DEX_MODIFYIDENTVISINFO,(LPARAM)&(l))
#define DEX_ModVisInfoDialog(hPr,l)         \
	(ErrCode)DexExtensionProc2(hPr,(WPARAM)DEX_MODIFYVISINFODIALOG,(LPARAM)&(l))
	
#define DEX_GetNumOfOpenProjects()	\
	DexExtensionProc((WPARAM)DEX_QUERYOPENPROJECTS,0L)
#define DEX_OpenProject(l)              \
	(ErrCode)DexExtensionProc((WPARAM)DEX_PROJECTOPEN,(LPARAM)&(l))
#define DEX_CloseProject(l)		\
	DexExtensionProc((WPARAM)DEX_PROJECTCLOSE,(LPARAM)(l))
#define DEX_CloseProjectEx(l)           \
	DexExtensionProc((WPARAM)DEX_PROJECTCLOSEEX,(LPARAM)(l))
#define DEX_GetDefaultDataPath(l)	\
	(char *)DexExtensionProc((WPARAM)DEX_QUERYDEFAULTDATAPATH,(LPARAM)(l))
#define DEX_SetDefaultDataPath(l)	\
	DexExtensionProc((WPARAM)DEX_MODDEFAULTDATAPATH,(LPARAM)(l))
#define DEX_GetProjectCont(l)		\
	DexExtensionProc((WPARAM)DEX_QUERYPROJECTCONT,(LPARAM)&(l))
	
#define DEXI_isDrawing()                \
	DexExtensionProc((WPARAM)DEX_QUERYDRAWINGSTATUS,0L)
#define DEXI_isPrinting()               \
	DexExtensionProc((WPARAM)DEX_QUERYISPRINTING,0L)
#define DEXI_isAppWindowVisible()	\
	(bool)DexExtensionProc((WPARAM)DEX_QUERYMAINWINDOWVISIBLE,0L)

#define DEX_ShowAppWindow(l)		\
	DexExtensionProc((WPARAM)DEX_SHOWMAINWINDOW,(LPARAM)(l))
#define DEX_HideAppWindow()		\
	DexExtensionProc((WPARAM)DEX_HIDEMAINWINDOW,0L)
#define DEX_AppQuit(l)			\
	DexExtensionProc((WPARAM)DEX_QUITAPP,(LPARAM)(l))

// Anfragen zu einem konkreten Objekt -----------------------------------------
#define DEX_GetObjectType(l)            \
	(short)DexExtensionProc((WPARAM)DEX_QUERYOBJTYPE,(LPARAM)(l))
#define DEX_GetObjectStatus(l)          \
	(short)DexExtensionProc((WPARAM)DEX_QUERYOBJSTATUS,(LPARAM)(l))
#define DEX_GetKObjectRCode(l)          \
	DexExtensionProc((WPARAM)DEX_QUERYKOBJECTRCODE,(LPARAM)(l))
#define DEX_GetObjContainer(l,OC)       \
	DexExtensionProc((WPARAM)DEX_QUERYOBJCONTAINER,((*(long *)&OC=l),(LPARAM)&(OC)))
#define DEX_GetObjColor(l)      \
	DexExtensionProc((WPARAM)DEX_QUERYOBJCOLOR,(LPARAM)(l))
#define DEX_GetObjIdent(l)      \
	(long)DexExtensionProc((WPARAM)DEX_QUERYOBJIDENT,(LPARAM)l)
#define DEX_GetObjStatistik(St) \
	(bool)DexExtensionProc((WPARAM)DEX_QUERYOBJSTATISTIK,(LPARAM)&(St))
#define DEX_GetObjGeometrie(OG) \
	(bool)DexExtensionProc((WPARAM)DEX_QUERYOBJGEOMETRIE,(LPARAM)&(OG))
#define DEX_ModObjGeometrie(OG) \
	(bool)DexExtensionProc((WPARAM)DEX_MODIFYOBJGEOMETRIE,(LPARAM)&(OG))

// @func char * | DEX_GetTextMerkmal | Liefert ein Merkmal eines Objektes, eines 
// Identifikators oder einer Sicht.
// @parm TARGETMERKMAL & | rTargetFeature | Referenz auf Struktur vom Typ <t TARGETMERKMAL> 
// oder <t TARGETMERKMALEX>.
// @rdesc Liefert bei erfolgreichem Abschluß der Aktion den Zeiger auf den übergebenen 
// Zeichenkettenpuffer <mf TARGETMERKMAL.pMText>, im Fehlerfall NULL.
// @xref <m DEX_QUERYTEXTMERKMAL>, <t TARGETMERKMAL>, <t TARGETMERKMALEX>
#define DEX_GetTextMerkmal(l)   \
	(char *)DexExtensionProc((WPARAM)DEX_QUERYTEXTMERKMAL,(LPARAM)&(l))

// @func ErrCode | DEX_ModTextMerkmal | Schreiben oder Löschen eines Merkmales eines Objektes,
// eines Identifikators oder einer Sicht.
// @parm TARGETMERKMAL & | rTargetFeature | Referenz auf Struktur vom Typ <t TARGETMERKMAL> 
// oder <t TARGETMERKMALEX>.
// @rdesc Liefert einen <t ErrCode>, der im Fehlerfall Auskunft über die Fehlerursache 
// gibt.
// @xref <m DEX_MODIFYMERKMAL>, <t TARGETMERKMAL>, <t TARGETMERKMALEX>, <t ErrCode>
#define DEX_ModTextMerkmal(l)   \
	(ErrCode)DexExtensionProc((WPARAM)DEX_MODIFYMERKMAL,(LPARAM)&(l))

#define DEX_GetIdentObjTypes(l) \
	(short)DexExtensionProc((WPARAM)DEX_QUERYIDENTOBJTYPES,(LPARAM)(l))
#define DEX_GetIdentObjTypesActView(l)	\
	(short)DexExtensionProc((WPARAM)DEX_QUERYIDENTOBJTYPESACTVIEW,(LPARAM)(l))

#define DEX_isObjectVisible(l)	\
	(bool)DexExtensionProc((WPARAM)DEX_OBJECTISVISIBLE,(LPARAM)(l))

// @func bool | DEX_GetObjectName | Abfragen eines Objektnamens. In dem Fall, wenn für dieses 
// Objekt kein Objektname existeirt, wird der Unique Ident geliefert.
// @parm OBJECTFEATURE & | rObjFeature | Referenz auf Struktur vom Typ <t OBJECTFEATURE>.
// @rdesc Liefert bei erfolgreichem Abschluß der Aktion <t true>, im Fehlerfall <t false>.
// @xref <m DEX_QUERYOBJECTNAME>, <t OBJECTFEATURE>
#define DEX_GetObjectName(l)   \
	(char *)DexExtensionProc((WPARAM)DEX_QUERYOBJECTNAME,(LPARAM)&(l))

// @func bool | DEX_ModObjectName | Schreiben oder Löschen eines Objektnamens.
// @parm OBJECTFEATURE & | rObjFeature | Referenz auf Struktur vom Typ <t OBJECTFEATURE>.
// @rdesc Liefert bei erfolgreichem Abschluß der Aktion <t true>, im Fehlerfall <t false>.
// @xref <m DEX_SETOBJECTNAME>, <t OBJECTFEATURE>
#define DEX_ModObjectName(l)   \
	(ErrCode)DexExtensionProc((WPARAM)DEX_SETOBJECTNAME,(LPARAM)&(l))
	
#define DEX_FlushModifications()	\
	DexExtensionProc((WPARAM)DEX_FLUSHALLMODIFICATIONS,(LPARAM)0)
#define DEX_RebuildSight()      \
	(bool)DexExtensionProc((WPARAM)DEX_REBUILDVIEW,(LPARAM)0)
#define DEX_PostRebuildSight()      \
	PostMessage(__hWndM,__DexCmd,(WPARAM)DEX_REBUILDVIEW,0)
#define DEX_SelectNewSight(l)   \
	(bool)DexExtensionProc((WPARAM)DEX_SELNEWSIGHT,(LPARAM)l)
#define DEX_DeleteSight(l)	\
	(bool)DexExtensionProc((WPARAM)DEX_DELETEVIEW,(LPARAM)l)
#define DEX_GetViewDescription(l)	\
	DexExtensionProc((WPARAM)DEX_QUERYVIEWDESCRIPTION,(LPARAM)&(l))
#define DEX_SetViewDescription(l)	\
	DexExtensionProc((WPARAM)DEX_MODVIEWDESCRIPTION,(LPARAM)&(l))
	
// Modifikationsanforderungen für ein Objekt ----------------------------------
// *** the following are obsolete, don't use
#define DEX_MergeObjects(R,O1,O2,Id,RCode,iFlag)        \
	{ MERGEKOBJECT __m; __m.mObj1=O1;__m.mObj2=O2;__m.mIdent=Id;__m.mRCode=RCode;__m.mMerge=iFlag;  \
	R=DexExtensionProc((WPARAM)DEX_MERGEKOBJECTS,(LPARAM)&__m); }
#define DEX_DeleteONFromKObject(R,O1,O2)        \
	{ DELETEKOBJECT __d; __d.doKObj=O1;__d.doObj=O2;        \
	R=DexExtensionProc((WPARAM)DEX_DELETEOBJFROMKOBJECT,(LPARAM)&__d); }
// neuen Identifikator einfügen -----------------------------------------------
#define DEX_AddNewIdent(R,Id,iTmp,iVTyp)        \
	{ ADDNEWIDENT __a; __a.newIdent=Id;__a.iFlags=iTmp;__a.iTyp=iVTyp;      \
	R=DexExtensionProc((WPARAM)DEX_ADDNEWIDENT,(LPARAM)&__a); }
// *** end of obsolete macros

// Komplexobjekt bilden/bearbeiten/löschen ------------------------------------
#define DEX_ModKomplexObj(l)		\
	(LONG)DexExtensionProc((WPARAM)DEX_MERGEKOBJECTS,(LPARAM)&(l))
#define DEX_DelFromKomplexObj(l)	\
	(LONG)DexExtensionProc((WPARAM)DEX_DELETEOBJFROMKOBJECT,(LPARAM)&(l))
#define DEX_RegNewIdent(l)		\
	(LONG)DexExtensionProc((WPARAM)DEX_ADDNEWIDENT,(LPARAM)&(l))

#define DEX_isIdentUsed(l)      \
	(bool)DexExtensionProc((WPARAM)DEX_USEDIDENT,(LPARAM)(l))
#define DEX_isIdentUsedSight(l) \
	(bool)DexExtensionProc((WPARAM)DEX_USEDIDENTSIGHT,(LPARAM)(l))
#define DEX_isMCodeUsed(l)      \
	(bool)DexExtensionProc((WPARAM)DEX_USEDMCODE,(LPARAM)(l))
#define DEX_isRCodeUsed(l)      \
	(bool)DexExtensionProc((WPARAM)DEX_USEDRCODE,(LPARAM)(l))

// Enumerationsanforderungen --------------------------------------------------
#define DEX_EnumKObjects(R,ONr,fcn,ptr)                                 \
	{ ENUMLONGKEY __s; __s.eKey=ONr;__s.eFcn=fcn;__s.ePtr=ptr;      \
	R=DexExtensionProc((WPARAM)DEX_ENUMKOMPLOBJECTS,(LPARAM)&__s); }

#define DEX_EnumSelectedObjects(l)      \
	(bool)DexExtensionProc((WPARAM)DEX_ENUMSELECTEDOBJECTS,(LPARAM)&(l))
#define DEX_EnumSelectedObjectsEx(l)	\
	(bool)DexExtensionProc((WPARAM)DEX_ENUMSELECTEDOBJECTSEX,(LPARAM)&(l))
#define DEX_EnumAllORObjects(l)		\
	(bool)DexExtensionProc((WPARAM)DEX_RECHERCHEDOBJECTS,(LPARAM)&(l))

// @func bool | DEX_EnumIdentObjects | Enumerieren aller Objekte eines Identifikators.
// @parm ENUMLONGKEY & | rEnumLongKey | Referenz auf Struktur vom Typ <t ENUMLONGKEY>.
// @rdesc Liefert bei erfolgreichem Abschluß der Aktion <t true>, im Fehlerfall <t false>.
// @xref <m DEX_ENUMIDENTOBJS>, <t ENUMLONGKEY>
#define DEX_EnumIdentObjects(l)         \
	(bool)DexExtensionProc((WPARAM)DEX_ENUMIDENTOBJS,(LPARAM)&(l))

// @func bool | DEX_EnumIdentObjectsEx | Enumerieren aller Objekte eines 
// Identifikators unter zusätzlicher Berücksichtigung des Objekttypes.
// @parm ENUMLONGKEYEX & | rEnumLongKeyEx | Referenz auf Struktur vom Typ <t ENUMLONGKEYEX>.
// @rdesc Liefert bei erfolgreichem Abschluß der Aktion <t true>, im Fehlerfall <t false>.
// @xref <m DEX_ENUMIDENTOBJSEX>, <t ENUMLONGKEYEX>
#define DEX_EnumIdentObjectsEx(l)         \
	(bool)DexExtensionProc((WPARAM)DEX_ENUMIDENTOBJSEX,(LPARAM)&(l))

#define DEX_EnumSightIdents(l)          \
	(bool)DexExtensionProc((WPARAM)DEX_ENUMVIEWIDENTS,(LPARAM)&(l))
#define DEX_EnumSightIdentsEx(l)	\
	(bool)DexExtensionProc((WPARAM)DEX_ENUMVIEWIDENTSEX,(LPARAM)&(l))

#define DEX_EnumIdentSightsEx(l)	\
	(bool)DexExtensionProc((WPARAM)DEX_ENUMIDENTVIEWSEX,(LPARAM)&(l))

// @func bool | DEX_EnumIdents | Enumerieren aller Identifikatoren des aktuellen Projektes.
// @parm ENUMNOKEYLONG & | rEnumNoKey | Referenz auf Struktur vom Typ <t ENUMNOKEYLONG>.
// @rdesc Liefert bei erfolgreichem Abschluß der Aktion <t true>, im Fehlerfall <t false>.
// @xref <m DEX_ENUMALLIDENTS>, <t ENUMNOKEYLONG>
#define DEX_EnumIdents(l)               \
	(bool)DexExtensionProc((WPARAM)DEX_ENUMALLIDENTS,(LPARAM)&(l))

// @func bool | DEX_EnumIdentsEx | Enumerieren aller Identifikatoren des aktuellen Projektes
// unter zusätzlicher Berücksichtigung des Objekttypes.
// @parm ENUMNOKEYLONGEX & | rEnumNoKeyEx | Referenz auf Struktur vom Typ <t ENUMNOKEYLONGEX>.
// @rdesc Liefert bei erfolgreichem Abschluß der Aktion <t true>, im Fehlerfall <t false>.
// @xref <m DEX_ENUMALLIDENTSEX>, <t ENUMNOKEYLONGEX>
#define DEX_EnumIdentsEx(l)               \
	(bool)DexExtensionProc((WPARAM)DEX_ENUMALLIDENTSEX,(LPARAM)&(l))

#define DEXOR_EnumIdents(hWnd,l)               \
	(bool)DexORExtensionProc(hWnd,(WPARAM)DEX_ENUMALLIDENTS,(LPARAM)&(l))
#define DEXOR_EnumIdentsEx(hWnd,l)               \
	(bool)DexORExtensionProc(hWnd,(WPARAM)DEX_ENUMALLIDENTSEX,(LPARAM)&(l))

#define DEXOR_EnumIdentsSelected(hWnd,l)               \
	(bool)DexORExtensionProc(hWnd,(WPARAM)DEX_ENUMIDENTSSELECTED,(LPARAM)&(l))
#define DEXOR_EnumIdentsSelectedEx(hWnd,l)               \
	(bool)DexORExtensionProc(hWnd,(WPARAM)DEX_ENUMIDENTSSELECTEDEX,(LPARAM)&(l))

// @func bool | DEX_EnumObjektMerkmale | Enumerieren aller Objektmerkmale eines 
// vorgegebenen Objektes.
// @parm ENUMLONGKEY & | rEnumLongKey | Referenz auf Struktur vom Typ <t ENUMLONGKEY>.
// @rdesc Liefert im Normalfall <t true> und im Fehlerfall oder bei Abbruch der 
// Enumeration <t false>
// @xref <m DEX_ENUMMERKMALE>, <t ENUMLONGKEY>
#define DEX_EnumObjektMerkmale(l)       \
	(bool)DexExtensionProc((WPARAM)DEX_ENUMMERKMALE,(LPARAM)&(l))

// @func bool | DEX_EnumIdentMerkmale | Enumerieren aller Identifikatormerkmale eines 
// vorgegebenen Identifikators.
// @parm ENUMLONGKEY & | rEnumLongKey | Referenz auf Struktur vom Typ <t ENUMLONGKEY>.
// @rdesc Liefert im Normalfall <t true> und im Fehlerfall oder bei Abbruch der 
// Enumeration <t false>
// @xref <m DEX_ENUMMERKMALEIDENT>, <t ENUMLONGKEY>
#define DEX_EnumIdentMerkmale(l)        \
	(bool)DexExtensionProc((WPARAM)DEX_ENUMMERKMALEIDENT,(LPARAM)&(l))

// @func bool | DEX_EnumSichtMerkmale | Enumerieren aller Sichtmerkmale einer 
// vorgegebenen Sicht.
// @parm ENUMTEXTKEY & | rEnumTextKey | Referenz auf Struktur vom Typ <t ENUMTEXTKEY>.
// @rdesc Liefert im Normalfall <t true> und im Fehlerfall oder bei Abbruch der 
// Enumeration <t false>
// @xref <m DEX_ENUMMERKMALESICHT>, <t ENUMTEXTKEY>
#define DEX_EnumSichtMerkmale(l)        \
	(bool)DexExtensionProc((WPARAM)DEX_ENUMMERKMALESICHT,(LPARAM)&(l))

// @func bool | DEX_EnumObjektMerkmaleEx | Enumerieren aller Merkmale eines 
// vorgegebenen Objektes.
// @parm ENUMLONGKEYEX & | rEnumLongKey | Referenz auf Struktur vom Typ <t ENUMLONGKEYEX>.
// @rdesc Liefert im Normalfall <t true> und im Fehlerfall oder bei Abbruch der 
// Enumeration <t false>
// @xref <m DEX_ENUMMERKMALEEX>, <t ENUMLONGKEYEX>
#define DEX_EnumObjektMerkmaleEx(l)       \
	(bool)DexExtensionProc((WPARAM)DEX_ENUMMERKMALEEX,(LPARAM)&(l))

// @func bool | DEX_EnumIdentMerkmaleEx | Enumerieren aller Merkmale eines 
// vorgegebenen Identifikators.
// @parm ENUMLONGKEYEX & | rEnumLongKey | Referenz auf Struktur vom Typ <t ENUMLONGKEYEX>.
// @rdesc Liefert im Normalfall <t true> und im Fehlerfall oder bei Abbruch der 
// Enumeration <t false>
// @xref <m DEX_ENUMMERKMALEIDENTEX>, <t ENUMLONGKEYEX>
#define DEX_EnumIdentMerkmaleEx(l)        \
	(bool)DexExtensionProc((WPARAM)DEX_ENUMMERKMALEIDENTEX,(LPARAM)&(l))

// @func bool | DEX_EnumSichtMerkmaleEx | Enumerieren aller Merkmale einer 
// vorgegebenen Sicht.
// @parm ENUMTEXTKEYEX & | rEnumTextKey | Referenz auf Struktur vom Typ <t ENUMTEXTKEYEX>.
// @rdesc Liefert im Normalfall <t true> und im Fehlerfall oder bei Abbruch der 
// Enumeration <t false>
// @xref <m DEX_ENUMMERKMALESICHTEX>, <t ENUMTEXTKEYEX>
#define DEX_EnumSichtMerkmaleEx(l)        \
	(bool)DexExtensionProc((WPARAM)DEX_ENUMMERKMALESICHTEX,(LPARAM)&(l))

#define DEX_EnumSights(l)               \
	DexExtensionProc((WPARAM)DEX_ENUMALLSIGHTS,(LPARAM)&(l))
#define DEX_EnumMCodes(l)               \
	(bool)DexExtensionProc((WPARAM)DEX_ENUMALLMCODES,(LPARAM)&(l))
#define DEX_EnumMCodesEx(l)               \
	(bool)DexExtensionProc((WPARAM)DEX_ENUMALLMCODESEX,(LPARAM)&(l))
#define DEX_EnumHeaderEntries(l)	\
	DexExtensionProc((WPARAM)DEX_ENUMHEADER,(LPARAM)&(l))

// @func bool | DEX_EnumRechTextMerkmal | Enumerieren aller Objekte, die ein bestimmtes 
// Merkmal besitzen. 
// @parm ENUMRECHTEXTMERKMAL & | rRechTextMerkmal | Referenz auf Struktur vom Typ <t ENUMRECHTEXTMERKMAL>.
// @rdesc Liefert im Normalfall <t true> und im Fehlerfall oder bei Abbruch der 
// Enumeration <t false>.
// @xref <m DEX_ENUMTEXTMERKMALRECH>, <t ENUMRECHTEXTMERKMAL>
#define DEX_EnumRechTextMerkmal(l)      \
	(bool)DexExtensionProc((WPARAM)DEX_ENUMTEXTMERKMALRECH,(LPARAM)&(l))

#define DEX_EnumRechGeometrie(l)        \
	(bool)DexExtensionProc((WPARAM)DEX_ENUMRECHGEOMETRIE,(LPARAM)&(l))

#define DEX_EnumTopRelations(l)	\
	(bool)DexExtensionProc((WPARAM)DEX_ENUMTOPRELATIONS,(LPARAM)(l))
#define DEX_ModifyRelation(MR)	\
	(ErrCode)DexExtensionProc((WPARAM)DEX_MODRELATION,(LPARAM)&(MR))
#define DEX_DeleteRelation(DR)	\
	DexExtensionProc((WPARAM)DEX_DELRELATION,(LPARAM)&(DR))
	
#define DEX_RePaint()   \
	PostMessage(__hWndM,__DexCmd,(WPARAM)DEX_REPAINTALL,0)
#define DEX_RePaintWait()       \
	DexExtensionProc((WPARAM)DEX_REPAINTALL,0)
#define DEX_RePaintRect(l)                      \
	PostMessage(__hWndM,__DexCmd,(WPARAM)DEX_REPAINTRECT,(LPARAM)&(l))
#define DEX_RePaintRectWait(l)                  \
	DexExtensionProc((WPARAM)DEX_REPAINTRECT,(LPARAM)&(l))
#define DEX_RePaintObject(l)                  \
	DexExtensionProc((WPARAM)DEX_OBJECTREPAINT,(LPARAM)(l))

// Befehle an den ObjektBaum --------------------------------------------------
#define DEX_SetAttributes(lONr)         \
	DexExtensionProc((WPARAM)DEX_SETATTRIBUTES,(LPARAM)lONr)
#define DEX_ResetAttributes(lONr)       \
	DexExtensionProc((WPARAM)DEX_RESETATTRIBUTES,(LPARAM)lONr)

// Verwaltung der PBD ---------------------------------------------------------
#define DEX_GetPBDData(p)       \
	(ErrCode)DexExtensionProc((WPARAM)DEX_QUERYPBDDATA,(LPARAM)&(p))
#define DEX_DelPBDData(p)       \
	(ErrCode)DexExtensionProc((WPARAM)DEX_DELPBDDATA,(LPARAM)&(p))
#define DEX_ModPBDData(p)       \
	(ErrCode)DexExtensionProc((WPARAM)DEX_MODPBDDATA,(LPARAM)&(p))
#define DEX_BeginPBDTransaction() \
	DexExtensionProc((WPARAM)DEX_BEGINPBDTRANSACTION,0L)
#define DEX_BreakPBDTransaction() \
	DexExtensionProc((WPARAM)DEX_BREAKPBDTRANSACTION,0L)
#define DEX_EndPBDTransaction() \
	DexExtensionProc((WPARAM)DEX_ENDPBDTRANSACTION,0L)
#define DEX_GetPBDVersion()     \
	DexExtensionProc((WPARAM)DEX_QUERYPBDVERSION,0L)
#define DEX_EnumPBDData(l)              \
	(bool)DexExtensionProc((WPARAM)DEX_ENUMPBDDATA,(LPARAM)&(l))

// GeoDBHeader Verwalten ------------------------------------------------------
#define DEX_ReadGeoDBHdrEntry(l)        \
	(ErrCode)DexExtensionProc((WPARAM)DEX_READHEADER,(LPARAM)&(l))
#define DEX_WriteGeoDBHdrEntry(l)       \
	(ErrCode)DexExtensionProc((WPARAM)DEX_MODIFYHEADER,(LPARAM)&(l))
#define DEX_DeleteGeoDBHdrEntry(l)      \
	(ErrCode)DexExtensionProc((WPARAM)DEX_DELETEHEADER,(LPARAM)&(l))
#define DEX_GetUniqueICode()            \
	DexExtensionProc((WPARAM)DEX_GETUNIQUEICODE,(LPARAM)0)
#define DEX_GetUniqueMCode()            \
	DexExtensionProc((WPARAM)DEX_GETUNIQUEMCODE,(LPARAM)false)
#define DEX_GetUniqueSysMCode()         \
	DexExtensionProc((WPARAM)DEX_GETUNIQUEMCODE,(LPARAM)true)
#define DEX_GetUniqueRCode()            \
	DexExtensionProc((WPARAM)DEX_GETUNIQUERCODE,(LPARAM)0)
#define DEX_GetUniqueTempONr()          \
	DexExtensionProc((WPARAM)DEX_GETUNIQUETEMPON,(LPARAM)0)

#define DEX_GetActiveScaling(l)         \
	DexExtensionProc((WPARAM)DEX_QUERYACTSCALING,(LPARAM)&l)
#define DEX_OCtoDC(l)   \
	DexExtensionProc((WPARAM)DEX_OCTODC,(LPARAM)&(l))
#define DEX_DCtoOC(l)   \
	DexExtensionProc((WPARAM)DEX_DCTOOC,(LPARAM)&(l))
#define DEX_OCtoDCEx(l)   \
	DexExtensionProc((WPARAM)DEX_OCTODCEX,(LPARAM)&(l))
#define DEX_DCtoOCEx(l)   \
	DexExtensionProc((WPARAM)DEX_DCTOOCEX,(LPARAM)&(l))
#define DEX_OCtoRC(l)   \
	DexExtensionProc((WPARAM)DEX_OCTORC,(LPARAM)&(l))
#define DEX_RCtoOC(l)   \
	DexExtensionProc((WPARAM)DEX_RCTOOC,(LPARAM)&(l))

#define DEX_GetActiveTool()     \
	(short)DexExtensionProc((WPARAM)DEX_QUERYACTIVETOOL,0L)
#define DEX_ChangeActiveTool(l)     \
	(short)DexExtensionProc((WPARAM)DEX_SETACTIVETOOL,(l))
		
// Fehlerbehandlung -----------------------------------------------------------
#define DEX_ErrInstall(R,RC,EH,oEH)     \
	{ ERRINSTALL __EI; __EI.eiRC=RC;__EI.eiEH=(ERRHANDLER)EH;__EI.eioEH=(ERRHANDLER *)oEH;  \
	R=(ErrCode)DexExtensionProc((WPARAM)DEX_ERRINSTALL,(LPARAM)&__EI); }
#define DEX_ExtErrInstall(R,RC,EH,oEH,pD)       \
	{ EXTERRINSTALL __EI; __EI.eiRC=RC;__EI.eiEH=(ERRHANDLER)EH;__EI.eioEH=(ERRHANDLER *)oEH;__EI.dwData=pD;        \
	R=(ErrCode)DexExtensionProc((WPARAM)DEX_EXTERRINSTALL,(LPARAM)&__EI); }
#define DEX_SetError(R,RC,EC,pD)        \
	{ ERRORMESSAGE __E; __E.emiRoutine=RC;__E.emiErrCode=EC;__E.empData=pD; \
	R=(ErrCode)DexExtensionProc((WPARAM)DEX_SETERROR,(LPARAM)&__E); }

#define DEX_Error(RC,EC)        \
	{ ERRORMESSAGE __E; __E.emiRoutine=RC;__E.emiErrCode=EC;__E.empData=NULL; \
	  DexExtensionProc((WPARAM)DEX_SETERROR,(LPARAM)&__E); }

// ObjRechFenster aufmachen ---------------------------------------------------
#define DEX_CreateObjektInfo(l) \
	(HWND)DexExtensionProc((WPARAM)DEX_CREATEOBJEKTINFO,(LPARAM)&(l))

// Löschen eines Objektes -----------------------------------------------------
#define DEX_DeleteObject(l)     \
	(bool)DexExtensionProc((WPARAM)DEX_DELOBJECT,(LPARAM)l)
#define DEXOR_DeleteObject(hWnd,l)      \
	DexORExtensionProc(hWnd,(WPARAM)DEX_DELOBJECT,(LPARAM)l)

#if !defined(WIN16)
#define DEX_DeleteObjectEx(l)     \
	(bool)DexExtensionProc((WPARAM)DEX_DELOBJECTEX,(LPARAM)l)
#else
#define DEX_DeleteObjectEx(l)	DEX_DeleteObject(l)
#endif // WIN16

#define DEX_ModObjectIdent(l)   \
	(bool)DexExtensionProc((WPARAM)DEX_MODOBJIDENT,(LPARAM)&(l))
#define DEXOR_ModObjectIdent(hWnd,l)    \
	DexORExtensionProc(hWnd,(WPARAM)DEX_MODOBJIDENT,(LPARAM)&(l))

#if !defined(WIN16)
#define DEX_ModObjectIdentEx(l)   \
	(bool)DexExtensionProc((WPARAM)DEX_MODOBJIDENTEX,(LPARAM)&(l))
#define DEXOR_ModObjectIdentEx(hWnd,l)    \
	DexORExtensionProc(hWnd,(WPARAM)DEX_MODOBJIDENTEX,(LPARAM)&(l))
#else
#define DEX_ModObjectIdentEx		DEX_ModObjectIdent
#define DEXOR_ModObjectIdentEx		DEXOR_ModObjectIdent
#endif // WIN16

#define DEX_FindObjectsFromPoint(l)     \
	DexExtensionProc((WPARAM)DEX_FINDOBJECT,(LPARAM)&(l))

#define DEX_GetIdBase()         \
	(short)DexExtensionProc((WPARAM)DEX_QUERYIDENTBASE,0L)
#define DEX_GetMkBase()         \
	(short)DexExtensionProc((WPARAM)DEX_QUERYMCODEBASE,0L)

#define DEX_RemoveAllORWnds()   \
	DexExtensionProc((WPARAM)DEX_REMOVEORWND,0L)
#define DEX_RemoveORWnd(l)   \
	DexExtensionProc((WPARAM)DEX_REMOVEORWND,(LPARAM)(l))

#define DEX_CreateNewGeoDB(l)   \
	(ErrCode)DexExtensionProc((WPARAM)DEX_CREATENEWGEODB,(LPARAM)&(l))
#define DEX_CreateNewIdentsDB(l)        \
	(ErrCode)DexExtensionProc((WPARAM)DEX_CREATENEWIDENTSDB,(LPARAM)&(l))

#define DEX_GetActScaling(l)	\
	DexExtensionProc((WPARAM)DEX_QUERYACTSCALING,(LPARAM)&(l))

#define DEX_RenderGeoDB(l)	\
	DexExtensionProc((WPARAM)DEX_RENDERGEODB,(LPARAM)&(l))
#define DEX_GetExposedOC(l)	\
	DexExtensionProc((WPARAM)DEX_QUERYEXPOSEDOC,(LPARAM)&(l))
#define DEX_GetExposedArea(l)	\
	DexExtensionProc((WPARAM)DEX_QUERYEXPOSEDAREA,(LPARAM)&(l))

#define DEX_GetLastIdent()	\
	(long)DexExtensionProc((WPARAM)DEX_GETLASTIDENT,(LPARAM)0)
#define DEX_SetLastIdent(l)	\
	DexExtensionProc((WPARAM)DEX_SETLASTIDENT,(LPARAM)(l))

#define DEX_SaveLegend()	\
	DexExtensionProc((WPARAM)DEX_SAVELEGEND,0L)
#define DEX_ResetLegend()	\
	DexExtensionProc((WPARAM)DEX_RESETLEGEND,0L)
#define DEX_RefreshLegend()	\
	DexExtensionProc((WPARAM)DEX_REFRESHLEGEND,0L)
#define DEX_AddObjectToLegend(l)	\
	DexExtensionProc((WPARAM)DEX_ADDOBJECTTOLEGEND,(LPARAM)l)
#define DEX_RepaintLegend()	\
	DexExtensionProc((WPARAM)DEX_REPAINTLEGEND,0L)
#define DEX_IsLegendActive()	\
	(bool)DexExtensionProc((WPARAM)DEX_QUERYLEGENDACTIVE,0L)

// Relationen -----------------------------------------------------------------
#define DEX_EnumRelationObjects(l)	\
	DexExtensionProc((WPARAM)DEX_ENUMRELATIONOBJS,(LPARAM)&(l))

// OLE-Unterstützung ----------------------------------------------------------
#define DEX_GetProjectStorage(l)	\
	DexExtensionProc((WPARAM)DEX_QUERYPROJECTSTORAGE,(LPARAM)&(l))
#define DEX_GetActivePalette()	\
	(HPALETTE)DexExtensionProc((WPARAM)DEX_QUERYACTIVEPALETTE,0)

#define DEX_GetTextObjectText(l)	\
	(bool)DexExtensionProc((WPARAM)DEX_GETTEXTOBJECTTEXT,(LPARAM)&(l))

// Blinken in ORFenstern abschalten/zuschalten --------------------------------
#define DEX_CancelMode(l)	\
	DexExtensionProc((WPARAM)DEX_CANCELMODE,(LPARAM)(l))

// @func void | DEX_EnableDiagnostics | Erlaubt die Generierung der 
// Diagnose-Notifikationen, die zusätzliche Informationen über interne 
// Aktionen in <tr> liefern.
// @rdesc Liefert den vorhergehenden Zustand des Enable-Flags (<t true>, wenn
// die Diagnose-Notifikationen bereits erlaubt waren, und <t false>, wenn nicht).
// @xref <m DEX_DIAGNOSTICSENABLE>, <f DEX_DisableDiagnostics>
#define DEX_EnableDiagnostics()	\
	(bool)DexExtensionProc((WPARAM)DEX_DIAGNOSTICSENABLE,(LPARAM)true)

// @func void | DEX_DisableDiagnostics | Verbietet die Generierung der 
// Diagnose-Notifikationen, die zusätzliche Informationen über interne 
// Aktionen in <tr> liefern.
// @rdesc Liefert den vorhergehenden Zustand des Enable-Flags (<t true>, wenn
// die Diagnose-Notifikationen bereits erlaubt waren, und <t false>, wenn nicht).
// @xref <m DEX_DIAGNOSTICSENABLE>, <f DEX_EnableDiagnostics>
#define DEX_DisableDiagnostics()	\
	(bool)DexExtensionProc((WPARAM)DEX_DIAGNOSTICSENABLE,(LPARAM)false)
		
// @func ULONG | DEX_GetUnknownIdent | Liefert einen für das aktuelle Projekt
// eindeutigen Identifikator, der für Objekte mit unbekannter Objektklasse vergeben
// werden kann.
// @rdesc Liefert den gesuchten Identifikator. Im Fehlerfall liefert diese Funktion
// Null.
// @xref <m DEX_QUERYUNKNOWNIDENT>
#define DEX_GetUnknownIdent()		\
	DexExtensionProc((WPARAM)DEX_QUERYUNKNOWNIDENT,0L)

// @func long | DEX_GetONrFromObjName | Liefert für das aktuelle Projekt die 
// Objektnummer des Objektes mit einem bestimmten Objektnamen.
// @parm char * | pObjName | Pointer auf den Objektnamen des gesuchten Objektes.
// @rdesc Liefert die gesuchte Objektnummer bzw. im Fehlerfall -1L.
// @comm Wenn mehrere Objekte den gegebenen Objektnamen besitzen, so wird das erste
// Objekt geliefert, welches diesen Objektnamen besitzt. Werden all Objekte mit diesem
// Objektnamen benötigt, so sollte eine der Funktionen <f DEX_EnumObjektMerkmale> oder
// <f DEX_EnumObjektMerkmaleEx> im Zusammenhang mit der Funktion <f DEX_GetObjNameMCode>
// eingesetzt werden.
// @xref <m DEX_FINDOBJFROMNAME>
#define DEX_GetONrFromObjName(l)	\
	DexExtensionProc((WPARAM)DEX_FINDOBJFROMNAME,(LPARAM)(l))

// @func ULONG | DEX_GetObjNameMCode | Liefert für das aktuelle Projekt und eine 
// gegebenen Identifikator den Merkmalscode, unter dem für die Objekte dieses 
// Identifikators der Objektname abgelegt ist.
// @parm ULONG | lIdent | Identifikator, für dessen Objekte der Merkmalscode gesucht 
// wird.
// @rdesc Liefert den Merkmalscode, unter dem die Objektnamen der Objekte mit dem 
// Identifikator <p lIdent> abgespeichert sind. Im Fehlerfall liefert diese 
// Funktion Null.
// @xref <m DEX_QUERYOBJNAMEMCODE>
#define DEX_GetObjNameMCode(l)		\
	DexExtensionProc((WPARAM)DEX_QUERYOBJNAMEMCODE,(LPARAM)(l))

// @func ULONG | DEX_GetUniqueIdentMCode | Liefert für das aktuelle Projekt den 
// Merkmalscode, unter dem die Unique Idents der Objekte abgelegt ist.
// @rdesc Liefert den Merkmalscode, unter dem die Objekte ihren Unique Ident 
// abgespeichert haben.
// @xref <m DEX_QUERYUNIQUEIDENTMCODE>
#define DEX_GetUniqueIdentMCode()	\
	DexExtensionProc((WPARAM)DEX_QUERYUNIQUEIDENTMCODE,0L)

// @func bool | DEX_ReReadHeader | Liest diverse Headereinträge des aktuellen 
// Projektes neu ein.
// @rdesc Liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @xref <m DEX_HEADERREREAD>
#define DEX_ReReadHeader()		\
	(bool)DexExtensionProc((WPARAM)DEX_HEADERREREAD,0)

// Caption neu generieren -----------------------------------------------------
#define DEX_ReReadCaption()		\
	(bool)DexExtensionProc((WPARAM)DEX_CAPTIONREREAD,0)

// @func ULONG | DEX_GetIdentFromClassName | Liefert für eine gegebene Objektklasse
// den zugehörigen Identifikator.
// @rdesc Liefert den gesuchten Identifikator oder Null, wenn kein entsprechender
// Identifikator gefunden werden konnte.
// @parm char * | pClassName | Zeichenkette, die den Namen der Objektklasse
// enthält, für die der Identifikator (Schlüssel) gesucht wird.
// @xref <m DEX_FINDIDENTFROMNAME>, <m DEX_FINDIDENTFROMNAMECI>, 
// <f DEX_GetIdentFromClassNameCI>
#define DEX_GetIdentFromClassName(l)	\
	DexExtensionProc((WPARAM)DEX_FINDIDENTFROMNAME,(LPARAM)(l))
// @func ULONG | DEX_GetIdentFromClassNameCI | Liefert für eine gegebene Objektklasse
// den zugehörigen Identifikator. Groß-/Kleinschreibung wird dabei ignoriert.
// @rdesc Liefert den gesuchten Identifikator oder Null, wenn kein entsprechender
// Identifikator gefunden werden konnte.
// @parm char * | pClassName | Zeichenkette, die den Namen der Objektklasse
// enthält, für die der Identifikator (Schlüssel) gesucht wird.
// @xref <m DEX_FINDIDENTFROMNAME>, <m DEX_FINDIDENTFROMNAMECI>, 
// <f DEX_GetIdentFromClassName>
#define DEX_GetIdentFromClassNameCI(l)	\
	DexExtensionProc((WPARAM)DEX_FINDIDENTFROMNAMECI,(LPARAM)(l))

// @func ULONG | DEX_GetMCodeFromFeatureName | Liefert für ein gegebenes Merkmal
// den zugehörigen Merkmalscode.
// @rdesc Liefert den gesuchten Merkmalscode oder Null, wenn kein entsprechendes
// Merkmal gefunden werden konnte.
// @parm char * | pFeatureName | Zeichenkette, die den Namen des Merkmales
// enthält, für die der Merkmalscode (Schlüssel) gesucht wird.
// @xref <m DEX_FINDFEATUREFROMNAMECI>, <m DEX_FINDFEATUREFROMNAME>,
// <f DEX_GetMCodeFromFeatureNameCI>
#define DEX_GetMCodeFromFeatureName(l)	\
	DexExtensionProc((WPARAM)DEX_FINDFEATUREFROMNAME,(LPARAM)(l))
// @func ULONG | DEX_GetMCodeFromFeatureName | Liefert für ein gegebenes Merkmal
// den zugehörigen Merkmalscode. Groß-/Kleinschreibung wird dabei ignoriert.
// @rdesc Liefert den gesuchten Merkmalscode oder Null, wenn kein entsprechendes
// Merkmal gefunden werden konnte.
// @parm char * | pFeatureName | Zeichenkette, die den Namen des Merkmales
// enthält, für die der Merkmalscode (Schlüssel) gesucht wird.
// @xref <m DEX_FINDFEATUREFROMNAME>, <m DEX_FINDFEATUREFROMNAMECI>,
// <f DEX_GetMCodeFromFeatureName>
#define DEX_GetMCodeFromFeatureNameCI(l)	\
	DexExtensionProc((WPARAM)DEX_FINDFEATUREFROMNAMECI,(LPARAM)(l))

// @func bool | DEX_DeleteAllIdentObjects | Löscht alle Objekte eines Identifikators.
// @rdesc Liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @parm ULONG | lIdent | Identifikator, dessen Objekte gelöscht werden sollen.
// @xref <m DEX_DELETEIDENT>
#define DEX_DeleteAllIdentObjects(l)	\
	(bool)DexExtensionProc((WPARAM)DEX_DELETEIDENT,(LPARAM)(l))

// @func bool | DEX_CreateView | Legt eine neue Ansicht unter dem gegebenen Sichtnamen
// an. Wenn diese Ansicht bereits existiert, wird diese vorher gelöscht.
// @rdesc Liefert einen <t bool> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @parm char * | pViewName | Zeichenkette, die den Namen der neu zu erzeugenden 
// Ansicht enthält.
// @xref <m DEX_VIEWCREATE>, <f DEX_CreateViewOpt>
#define DEX_CreateView(l)		\
	(bool)DexExtensionProc((WPARAM)DEX_VIEWCREATE,(LPARAM)(l))

// @func bool | DEX_CreateViewOpt | Legt eine neue Ansicht unter dem gegebenen Sichtnamen
// an. Wenn diese Ansicht bereits existiert, macht diese Funktion nichts.
// @rdesc Liefert einen <t int> - Wert, der folgende Werte enthalten kann:
// @flag CVError | Ein Fehler ist aufgetreten.
// @flag CVCreated | Die Ansicht wurde erfolgreich neu erzeugt, da keine Ansicht 
// mit diesem Namen existierte.
// @flag CVExists | Die Ansicht wurde nicht angelegt, da bereits eine Ansicht mit 
// diesem Namen existiert.
// und Fehlerfall <t false>.
// @parm char * | pViewName | Zeichenkette, die den Namen der neu zu erzeugenden 
// Ansicht enthält.
// @xref <m DEX_VIEWCREATEOPT>, <f DEX_CreateView>
#define DEX_CreateViewOpt(l)		\
	(bool)DexExtensionProc((WPARAM)DEX_VIEWCREATEOPT,(LPARAM)(l))

// @func bool | DEX_RemoveIdentFromView | Enfernt eine Identifikator/Objekttyp-
// Kombination aus einer gegebenen Ansicht.
// @rdesc Liefert einen <t bool> -Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @parm VIEWIDENTOBJECT & | rViewIdentOTyp | Referenz einer Struktur vom 
// Typ <t VIEWIDENTOBJECT>, die die notwendigen Informationen enthält.
// @xref <t VIEWIDENTOBJECT>, <m DEX_DELETEIDENTFROMVIEW>
#define DEX_RemoveIdentFromView(l)	\
	(bool)DexExtensionProc((WPARAM)DEX_DELETEIDENTFROMVIEW,(LPARAM)&(l))

// @func bool | DEX_AddIdentFromView | Fügt eine Identifikator/Objekttyp-
// Kombination zu einer gegebenen Ansicht hinzu. Dabei wird die 
// Standardvisualisierung verwendet.
// @rdesc Liefert einen <t bool> -Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @parm VIEWIDENTOBJECT & | rViewIdentOTyp | Referenz einer Struktur vom 
// Typ <t VIEWIDENTOBJECT>, die die notwendigen Informationen enthält.
// @xref <t VIEWIDENTOBJECT>, <m DEX_IDENTADDTOVIEW>
#define DEX_AddIdentToView(l)	\
	(bool)DexExtensionProc((WPARAM)DEX_IDENTADDTOVIEW,(LPARAM)&(l))

// @func bool | DEX_RenameView | Ändert den Namen einer Ansicht.
// @rdesc Liefert einen <t bool> -Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @parm RENAMEVIEW & | rRenameView | Referenz einer Struktur vom 
// Typ <t RENAMEVIEW>, die sowohl den Namen der Ansicht vorgibt, die umbenannt 
// werden soll, als auch den neuen Namen.
// @xref <m DEX_VIEWRENAME>, <t RENAMEVIEW>
#define DEX_RenameView(l)		\
	(bool)DexExtensionProc((WPARAM)DEX_VIEWRENAME,(LPARAM)&(l))

// @func bool | DEX_ViewHasIdent | Stellt fest, ob eine gegebene Identifikator/Objekttyp-
// Kombination zu einer Ansicht gehört.
// @rdesc Liefert einen <t bool> -Wert, der Auskunft darüber gibt, ob Objekte
// des gegebenen Typs mit dem gegebenen Identifikator zu einer Ansicht gehören 
// oder nicht.
// @parm VIEWIDENTOBJECT & | riewIdentOTyp | Referenz einer Struktur vom 
// Typ <t VIEWIDENTOBJECT>, die die notwendigen Informationen enthält.
// @xref <t VIEWIDENTOBJECT>, <m DEX_HASVIEWIDENT>
#define DEX_ViewHasIdent(l)		\
	(bool)DexExtensionProc((WPARAM)DEX_HASVIEWIDENT,(LPARAM)&(l))

// @func bool | DEX_ViewHasObject | Stellt fest, ob ein gegebenes Objekt
// zu einer Ansicht gehört.
// @rdesc Liefert einen <t bool> -Wert, der Auskunft darüber gibt, ob das Objekt
// zu einer Ansicht gehört oder nicht.
// @parm VIEWIDENTOBJECT & | rViewIdentOTyp | Referenz einer Struktur vom 
// Typ <t VIEWIDENTOBJECT>, die die notwendigen Informationen enthält.
// @xref <t VIEWIDENTOBJECT>, <m DEX_HASVIEWOBJECT>
#define DEX_ViewHasObject(l)		\
	(bool)DexExtensionProc((WPARAM)DEX_HASVIEWOBJECT,(LPARAM)&(l))

// @func bool | DEX_ProjectHasView | Stellt fest, ob im aktuellen Projekt
// eine gegebene Ansicht definiert ist.
// @rdesc Liefert einen <t bool> -Wert, der Auskunft darüber gibt, ob die Ansicht
// zum aktuelle Projekt gehört oder nicht.
// @parm char * | pViewName | Pointer auf den Namen der Ansicht
// @xref <m DEX_HASPROJECTVIEW>
#define DEX_ProjectHasView(l)		\
	(bool)DexExtensionProc((WPARAM)DEX_HASPROJECTVIEW,(LPARAM)(l))

// @func bool | DEX_IsORWindow | Stellt fest, ob das Fenster, dessen Handle (HWND)
// übergeben wird ein gültiges Objektrecherche-Fenster ist.
// @rdesc Liefert einen <t bool> -Wert, der Auskunft darüber gibt, ob das Fenster
// ein gültiges Objektrecherch-fenster ist.
// @parm HWND | hORWnd | Handle des zu untersuchenden fensters
// @xref <m DEX_ISOBJWINDOW>
#define DEX_IsORWindow(hWnd)	\
	(bool)DexExtensionProc((WPARAM)DEX_ISOBJWINDOW,(LPARAM)(void *)hWnd)

// @func bool | DEX_QueryMode | Liefert den Wert des System-Administrationsflags.
// @rdesc Liefert einen <t bool> -Wert, der Auskunft darüber gibt, ob der
// aktuelle Nutzer über erweiterte Zugriffsrechte verfügt oder nicht.
// @xref <m DEX_QUERYADMINMODE>
#define DEX_QueryMode()		\
	(bool)DexExtensionProc((WPARAM)DEX_QUERYADMINMODE,0)

// @func bool | DEX_SetMode | Setzt den Wert des System-Administrationsflags 
// für den aktuelle Nutzer.
// @parm bool | fAdminFlag | Enthält den neuen Wert, der dem SystemAdminFlag des
// aktuellen Nutzers zugewiesen werden soll.
// @rdesc Liefert einen <t bool> -Wert, der Auskunft darüber gibt, ob der
// aktuelle Nutzer über erweiterte Zugriffsrechte verfügt hatte oder nicht.
// @xref <m DEX_SETADMINMODE>
#define DEX_SetMode(l)		\
	(bool)DexExtensionProc((WPARAM)DEX_SETADMINMODE,(LPARAM)(l))

#define DEX_SetDirtyGeoDB(l)	\
	DexExtensionProc((WPARAM)DEX_SETGEODBDIRTY,(LPARAM)l)
#define DEX_IsGeoDBDirty()		\
	(bool)DexExtensionProc((WPARAM)DEX_GETGEODBDIRTY,0L)

#define DEX_EnumORWindows(l)	\
	DexExtensionProc((WPARAM)DEX_ENUMOBJRECHWNDS,(LPARAM)&(l))

// SichtContainer (Begrenzungen) festlegen und abfragen
#define DEX_GetActViewContainer(l)	\
	(bool)DexExtensionProc((WPARAM)DEX_QUERYACTVIEWCONTAINER,(LPARAM)(l))
#define DEX_SetActViewContainer(l)	\
	(bool)DexExtensionProc((WPARAM)DEX_MODACTVIEWCONTAINER,(LPARAM)(l))

#if !defined(WIN16)

#define DEX_AddUndoRedo(l)	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_ADDUNDOREDOITEM,(LPARAM)l)
#define DEX_BeginUndoLevel(l)	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_UNDOLEVELBEGIN,(LPARAM)l)
#define DEX_EndUndoLevel()	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_UNDOLEVELEND,0L)
#define DEX_CancelUndoLevel(l)	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_UNDOLEVELCANCEL,(LPARAM)l)
#define DEX_CanUndoString(l)	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_QUERYCANUNDO,(LPARAM)l)
#define DEX_CanRedoString(l)	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_QUERYCANREDO,(LPARAM)l)

#define DEX_SaveSameStorage(pIStg)	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_N_SAVESAMESTORAGE,(LPARAM)(pIStg))
#define DEX_SaveOtherStorage(pIStg)	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_N_SAVEOTHERSTORAGE,(LPARAM)(pIStg))
#define DEX_SaveCompleted(pIStg)	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_N_SAVECOMPLETED,(LPARAM)(pIStg))
#define DEX_HandsOffStorage(pIStg)	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_N_HANDSOFFSTORAGE,(LPARAM)0L)

#define DEX_AttachPreTranslateMsgProc(l)	\
	(bool (*)(MSG *))DexExtensionProc((WPARAM)DEX_ATTACHPRETRANSLATEMSGPROC,(LPARAM)(l))
#define DEX_DetachPreTranslateMsgProc()		\
	(bool (*)(MSG *))DexExtensionProc((WPARAM)DEX_ATTACHPRETRANSLATEMSGPROC,(LPARAM)NULL)
#define DEX_AttachIdleProc(l)		\
	(bool (*)(LONG))DexExtensionProc((WPARAM)DEX_ATTACHIDLEPROC,(LPARAM)(l))
#define DEX_DetachIdleProc()		\
	(bool (*)(LONG))DexExtensionProc((WPARAM)DEX_ATTACHIDLEPROC,(LPARAM)NULL)

#define DEX_GetActiveViewWindow()	\
	(HWND)DexExtensionProc((WPARAM)DEX_QUERYACTIVEVIEWWINDOW,(LPARAM)0)

#define DEX_GetObjectProps(l)		\
	(HRESULT)DexExtensionProc((WPARAM)DEX_QUERYOBJECTPROPS,(LPARAM)(l))

#define DEX_SetMessageString(l)		\
	(bool)DexExtensionProc((WPARAM)DEX_SETSTRINGMESSAGE,(LPARAM)(l))

#endif // WIN16

#include <poppack.h>

#endif // _XTENSNX2_H
