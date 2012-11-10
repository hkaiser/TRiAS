// Messagebreaking-Makros fuer Extension-Schnittstelle ------------------------
// File: XTENSNX.H
// @doc
// @module XTENSNX.H | Enthält die Definition aller Makro's und Funktionen, die 
// für den bequemen Einsatz der Messages an <tr> verwendet werden können.

#if !defined(_XTENSNX_H)
#define _XTENSNX_H

#if defined(WIN16)
#undef NEWXTENSIONPROC
#endif // WIN16

#include <DeclareHandles.h>
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

#if defined(__XT)		// Module in DLL's

#if defined(__DEXPROCS)
///////////////////////////////////////////////////////////////////////////////
// Die 'Messages' sind jetzt Rufe einer exportierten Funktion
extern "C" DEXEXTENSIONPROC g_pDexExtensionProc;
extern "C" DEXEXTENSIONPROC2 g_pDexExtensionProc2;
extern "C" DEXEXTENSIONPROC g_pDexxExtensionProc;
extern "C" DEXNOTIFICATIONPROC g_pDexNotificationProc;

#if !defined(NEWXTENSIONPROC)
#if defined(_DEBUG) // !_DEBUG: inline
extern "C" LRESULT WINAPI DexExtensionProc (WPARAM w, LPARAM l);
extern "C" LRESULT WINAPI DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l);
#endif // _DEBUG
#define DexORExtensionProc(h,w,l)		::SendMessage((h),__DexCmd,(WPARAM)(w),(LPARAM)(l))
#else	// NEWXTENSIONPROC
extern "C" LRESULT WINAPI DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l);
#define DexExtensionProc(w,l)			::DexExtensionProc2(NULL,w,l)
#define DexORExtensionProc(h,w,l)		::SendMessage((h),__DexCmd,(WPARAM)(w),(LPARAM)(l))
// die vorherige Zeile wird bald ersetzt durch die folgenden: 
//LRESULT WINAPI DexORExtensionProc2 (HPROJECT hPr, HWND hWnd, WPARAM w, LPARAM l);
//#define DexORExtensionProc(h,w,l) 	DexORExtensionProc2(hPr,(h),(WPARAM)(w),(LPARAM)(l))
#endif	// NEWXTENSIONPROC

#else	// __DEXPROCS
///////////////////////////////////////////////////////////////////////////////
// in den DLL's bleibt erstmal alles beim alten
#define DexExtensionProc(w,l)		::SendMessage(__hWndM,__DexCmd,(WPARAM)(w),(LPARAM)(l))
#define DexExtensionProc2(h,w,l)	::SendMessage(__hWndM,__DexCmd,(WPARAM)(w),(LPARAM)(l))
#define DexORExtensionProc(h,w,l)	::SendMessage((h),__DexCmd,(WPARAM)(w),(LPARAM)(l))
#endif	// __DEXPROCS

#else	// __XT (HauptModul)

///////////////////////////////////////////////////////////////////////////////
// im Hauptmodul wird direkt eine exportierte Funktion gerufen

#if !defined(NEWXTENSIONPROC)
extern "C" _TRIAS_ENTRY LRESULT WINAPI EXPORTTRIAS DexExtensionProc (WPARAM w, LPARAM l);
extern "C" _TRIAS_ENTRY LRESULT WINAPI EXPORTTRIAS DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l);
#define DexORExtensionProc(h,w,l)	::SendMessage((h),__DexCmd,(WPARAM)(w),(LPARAM)(l))
#else	// NEWXTENSIONPROC
extern HINSTANCE hInstance;
extern "C" _TRIAS_ENTRY LRESULT WINAPI EXPORTTRIAS DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l);
inline LRESULT DexExtensionProc(WPARAM w, LPARAM l)
{
	return ::DexExtensionProc2(NULL, w, l);
}
#define DexORExtensionProc(h,w,l)	::SendMessage((h),__DexCmd,(WPARAM)(w),(LPARAM)(l))
// die vorherige Zeile wird bald ersetzt durch die folgenden: 
//LRESULT WINAPI DexORExtensionProc2 (HPROJECT hPr, HWND hWnd, WPARAM w, LPARAM l);
//#define DexORExtensionProc(h,w,l) 	DexORExtensionProc2(hPr,(h),(WPARAM)(w),(LPARAM)(l))
#endif	// NEWXTENSIONPROC

extern "C" _TRIAS_ENTRY LRESULT WINAPI EXPORTTRIAS DexDispatchProc (HWND hWnd, UINT uiMsg, WPARAM w, LPARAM l);

#endif	// __XT

///////////////////////////////////////////////////////////////////////////////
// eigentliche MessageBreakingMakros ------------------------------------------

// Verwaltung von Erweiterungen -----------------------------------------------

// @func HMENU | DEX_InstallMenuItem | Installieren eines zusätzlichen Menupunktes in <tr>.
// @parm INSTALLMENUITEM & | rInstallItem | Referenz einer Struktur vom Typ <t INSTALLMENUITEM>.
// @rdesc Liefert das Handle des Popupmenus, in dem der Menupunkt installiert wurde bzw. im Fehlerfall NULL.
// @xref <t INSTALLMENUITEM>, <m DEX_MENUITEMINSTALL>
#define DEX_InstallMenuItem(l)			\
	(HMENU)DexExtensionProc((WPARAM)DEX_MENUITEMINSTALL,(LPARAM)&(l))

// @func void | DEX_RemoveMenuItem | Entfernen eines zusätzlich installierten 
// Menupunktes in <tr>
// @parm REMOVEMENUITEM & | rRemoveItem | Referenz einer Struktur vom Typ <t REMOVEMENUITEM>.
// @xref <t REMOVEMENUITEM>, <m DEX_MENUITEMREMOVE>
#define DEX_RemoveMenuItem(l)			\
	DexExtensionProc((WPARAM)DEX_MENUITEMREMOVE,(LPARAM)&(l))

#define DEX_ExternalLoadExtension(l)	\
	(HDEX)DexExtensionProc((WPARAM)DEX_LOADEXTENSION,(LPARAM)(l))
#define DEX_ExternalUnLoadExtension(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_UNLOADEXTENSION,(LPARAM)(l))
#define DEX_ExternalLoadExtensionEx(l)	\
	(HDEX)DexExtensionProc((WPARAM)DEX_LOADEXTENSIONEX,(LPARAM)&(l))
#define DEX_ExternalUnLoadExtensionEx(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_UNLOADEXTENSIONEX,(LPARAM)&(l))
#define DEX_ExternalLoadExtension2(l)	\
	(HDEX)DexExtensionProc((WPARAM)DEX_LOADEXTENSION2,(LPARAM)&(l))
#define DEX_ExternalUnLoadExtension2(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_UNLOADEXTENSION2,(LPARAM)&(l))

#define DEX_EnumExtensions(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMEXTENSIONS,(LPARAM)&(l))
#define DEX_GetExtensionInfo(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYEXTENSIONINFO,(LPARAM)&(l))
#define DEX_GetExtensionPtr(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYEXTENSIONPTR,(LPARAM)&(l))

// @func short | DEX_InstallTool | Installieren eines zusätzlichen Werkzeuges in <tr>.
// @parm INSTALLTOOL & | rInstallTool | Referenz auf Struktur vom Typ <t INSTALLTOOL>
// @rdesc Liefert den Werkzeug-ID des neu installierten Werkzeuges bzw. im Fehlerfall -1.
// @xref <t INSTALLTOOL>, <m DEX_TOOLINSTALL>
#define DEX_InstallTool(l)				\
	(short)DexExtensionProc((WPARAM)DEX_TOOLINSTALL,(LPARAM)&(l))

// @func void | DEX_RemoveTool | Enfernen eines zusätzlich installierten Werkzeuges in <tr>.
// @parm short | iToolID | Werkzeug-ID des zu entfernenden Werkzeuges.
// @xref <m DEX_TOOLREMOVE>
#define DEX_RemoveTool(l)				\
	DexExtensionProc((WPARAM)DEX_TOOLREMOVE,(LPARAM)l)

#define DEX_GetPBDName(l)				\
	(char *)DexExtensionProc((WPARAM)DEX_QUERYACTIVEPBD,(LPARAM)(l))
#define DEX_ModPBDName(l)				\
	DexExtensionProc((WPARAM)DEX_MODIFYPBDNAME,(LPARAM)(l))
#define DEX_GetMetaName(hPr,l)				 \
	(char *)DexExtensionProc2(hPr,(WPARAM)DEX_QUERYACTIVEPBD,(LPARAM)(l))
#define DEX_ModMetaName(hPr,l)				 \
	DexExtensionProc2(hPr,(WPARAM)DEX_MODIFYPBDNAME,(LPARAM)(l))

///////////////////////////////////////////////////////////////////////////////
// Anfragen zu selektierten Objekten
#define DEX_GetActiveObject(hWnd)		\
	(long)DexExtensionProc((WPARAM)DEX_QUERYACTIVEOBJECT,(LPARAM)(void *)hWnd)
#define DEX_ActivateAllObjects(hWnd)	   \
	(BOOL)DexExtensionProc((WPARAM)DEX_ACTIVATEALLORWNDS,(LPARAM)(void *)hWnd)
#define DEX_ActiveObjectsCount()		\
	(short)DexExtensionProc((WPARAM)DEX_QUERYCNTACTIVEOBJECTS,0L)
#define DEXOR_SelectedObjectsCount(hWnd,l)		\
	DexORExtensionProc(hWnd,(WPARAM)DEX_QUERYCNTACTIVEOBJECTS,(LPARAM)l)
#define DEXOR_RefreshEntry(hWnd,l)		\
	DexORExtensionProc(hWnd,(WPARAM)DEX_REFRESHENTRY,(LPARAM)(l))
#define DEXOR_RefreshAllEntries(hWnd)		\
	DexORExtensionProc(hWnd,(WPARAM)DEX_REFRESHENTRY,(LPARAM)0)
#define DEX_RefreshEntry(l)		\
	DexExtensionProc((WPARAM)DEX_REFRESHENTRY,(LPARAM)(l))
#define DEX_RefreshAllEntries()		\
	DexExtensionProc((WPARAM)DEX_REFRESHENTRY,(LPARAM)0)
#define DEX_GetAllActiveObjects(l)		\
	DexExtensionProc((WPARAM)DEX_QUERYALLACTIVEOBJECTS,(LPARAM)(l))
#define DEXOR_AddObjectToList(hWnd,l)	\
	DexORExtensionProc(hWnd,(WPARAM)DEX_ADDOBJECTTOLIST,(LPARAM)(l))
#define DEXOR_RemoveFromListObject(hWnd,l)	\
	DexORExtensionProc(hWnd,(WPARAM)DEX_REMOVEOBJECTFROMLIST,(LPARAM)(l))
#define DEXOR_ReplaceObjectInList(hWnd,l)	\
	DexORExtensionProc(hWnd,(WPARAM)DEX_REPLACEOBJECTINLIST,(LPARAM)&(l))
#define DEXOR_AddObjectToListEx(hWnd,l) \
	DexORExtensionProc(hWnd,(WPARAM)DEX_ADDOBJECTTOLISTEX,(LPARAM)(l))
#define DEXOR_RemoveFromListObjectEx(hWnd,l)	\
	DexORExtensionProc(hWnd,(WPARAM)DEX_REMOVEOBJECTFROMLISTEX,(LPARAM)(l))
#define DEXOR_ReplaceObjectInListEx(hWnd,l) \
	DexORExtensionProc(hWnd,(WPARAM)DEX_REPLACEOBJECTINLISTEX,(LPARAM)&(l))
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
#define DEXOR_SetObjectProperty(hWnd,l) \
	(BOOL)DexORExtensionProc(hWnd,(WPARAM)DEX_SHOWOBJPROP,(LPARAM)&(l))
#define DEXOR_SetText(hWnd,l)	\
	(BOOL)DexORExtensionProc(hWnd,(WPARAM)DEX_SETTEXT,(LPARAM)(l))

// @func char * | DEX_GetActiveProject | Abfragen des vollen Namens des aktuellen Projektes.
// @parm char * | pProjectName | Pufferbereich, in dem der Name zurückgeliefert werden soll.
// @rdesc Liefert <p pProjectName> bzw. im Fehlerfall NULL.
// @xref <m DEX_QUERYACTIVEPROJECT>, <m DEX_ACTIVEPROJECTTEST>, <f DEX_TestActiveProject>
#define DEX_GetActiveProject(l) 		\
	(char *)DexExtensionProc2(HACTPROJECT,(WPARAM)DEX_QUERYACTIVEPROJECT,(LPARAM)(l))
#define DEX_GetActiveProjectPtr(l)		\
	(BOOL)DexExtensionProc2(HACTPROJECT,(WPARAM)DEX_QUERYACTIVEPROJECTPTR,(LPARAM)&(l))

// @func char * | DEX_GetDataSourceName | Abfragen des vollen Namens einer Datenquelle.
// @parm char * | pProjectName | Pufferbereich, in dem der Name zurückgeliefert werden soll.
// @rdesc Liefert <p pProjectName> bzw. im Fehlerfall NULL.
// @xref <m DEX_QUERYACTIVEPROJECT>, <m DEX_ACTIVEPROJECTTEST>, <f DEX_TestActiveProject>
#define DEX_GetDataSourceName(hPr,l)	\
	(BOOL)DexExtensionProc2(hPr,(WPARAM)DEX_QUERYACTIVEPROJECT,(LPARAM)(l))
// @func char * | DEX_GetDataSourceDesc | Abfragen des Beschreibungstextes einer Datenquelle.
// @parm char * | pDesc | Pufferbereich, in dem der Beschreibungstext zurückgeliefert werden soll.
// @rdesc Liefert <p pDesc> bzw. im Fehlerfall NULL.
// @xref <m DEX_QUERYPROJECTDESC>
#define DEX_GetDataSourceDesc(hPr,l)	\
	(BOOL)DexExtensionProc2(hPr,(WPARAM)DEX_QUERYPROJECTDESC,(LPARAM)(l))
// @func char * | DEX_GetDataSourceShortName | Abfragen des Bezeichners einer Datenquelle.
// @parm char * | pDesc | Pufferbereich, in dem der Bezeichner zurückgeliefert werden soll.
// @rdesc Liefert <p pDesc> bzw. im Fehlerfall NULL.
// @xref <m DEX_QUERYDATASOURCENAME>
#define DEX_GetDataSourceShortName(hPr,l)	\
	(BOOL)DexExtensionProc2(hPr,(WPARAM)DEX_QUERYDATASOURCENAME,(LPARAM)(l))
#define DEX_GetDataSourcePtr(hPr,l)		\
	(BOOL)DexExtensionProc2(hPr,(WPARAM)DEX_QUERYACTIVEPROJECTPTR,(LPARAM)&(l))

// @func char * | DEX_GetActiveProjectHandle | Abfragen des Handles des aktuellen Projektes.
// @rdesc Liefert <t HPROJECT> bzw. im Fehlerfall NULL.
// @xref <m DEX_QUERYACTIVEPROJECTHANDLE>, <m DEX_ACTIVEPROJECTTEST>, <f DEX_TestActiveProject>
#define DEX_GetActiveProjectHandle()	\
	(HPROJECT)DexExtensionProc2(HACTPROJECT,(WPARAM)DEX_QUERYACTIVEPROJECTHANDLE,(LPARAM)(0))
// @func char * | DEX_GetDataSourceHandle | Abfragen des Handles einer Datenquelle.
// @rdesc Liefert <t HPROJECT> bzw. im Fehlerfall NULL.
// @xref <m DEX_QUERYACTIVEPROJECTHANDLE>, <m DEX_ACTIVEPROJECTTEST>, <f DEX_TestActiveProject>
#define DEX_GetDataSourceHandle()	\
	(HPROJECT)DexExtensionProc((WPARAM)DEX_QUERYACTIVEPROJECTHANDLE,(LPARAM)(0))

// @func BOOL | DEX_TestActiveProject | Abfragen, ob ein aktuelles Projektes existiert.
// @rdesc Liefert bei existierendem aktuellem Projekt <t true>, ansonsten <t false>.
// @xref <m DEX_ACTIVEPROJECTTEST>, <m DEX_QUERYACTIVEPROJECT>, <f DEX_GetActiveProject>
#define DEX_TestActiveProject() 		\
	(BOOL)DexExtensionProc((WPARAM)DEX_ACTIVEPROJECTTEST,(LPARAM)(0))

#define DEX_EnumProjects(l) \
	(BOOL)DexExtensionProc2(HACTPROJECT,(WPARAM)DEX_ENUMALLPROJECTS,(LPARAM)&(l))
#define DEX_EnumDataSources(l) \
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMALLPROJECTS,(LPARAM)&(l))
#define DEX_EnumDataSourceHandles(l) \
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMALLPROJECTHANDLES,(LPARAM)&(l))

#define DEX_GetProjectHandle(l) \
	(HPROJECT)DexExtensionProc2(HACTPROJECT,(WPARAM)DEX_PROJECTHANDLEFROMNAME,(LPARAM)(l))
#define DEX_GetDataSourceHandleEx(l) \
	(HPROJECT)DexExtensionProc((WPARAM)DEX_PROJECTHANDLEFROMNAME,(LPARAM)(l))
#define DEX_GetDataSourceHandleFromShortName(l) \
	(HPROJECT)DexExtensionProc((WPARAM)DEX_PROJECTHANDLEFROMSHORTNAME,(LPARAM)(l))

// Achtung: Folgende Message liefert Pointer auf freizugebendes String
//			(mit CoTaskMemFree) !
#define DEX_GetProjectName(l)	\
	(LPCSTR)DexExtensionProc((WPARAM)DEX_PROJECTNAMEFROMHANDLE,(LPARAM)(l))

#define DEX_MakeProjectActive(l)	\
	(HPROJECT)DexExtensionProc2(HACTPROJECT,(WPARAM)DEX_PROJECTMAKEACTIVE,(LPARAM)(l))
#define DEX_MakeDataSourceActive(l)	\
	(HPROJECT)DexExtensionProc((WPARAM)DEX_PROJECTMAKEACTIVE,(LPARAM)(l))

// @func char * | DEX_GetActiveUser | Abfragen des Namens des Nutzers des aktuellen Projektes.
// @parm char * | pUserName | Pufferbereich, in dem der Name zurückgeliefert werden soll.
// @rdesc Liefert <p pUserName> bzw. im Fehlerfall NULL.
// @xref <m DEX_QUERYACTIVEUSER>
#define DEX_GetActiveUser(l)			\
	(char *)DexExtensionProc((WPARAM)DEX_QUERYACTIVEUSER,(LPARAM)(l))

// @func BOOL | DEX_GetROMode | Abfragen des Zugriffsmodes des aktuellen Projektes.
// @rdesc Liefert <t true> bei Schreibschutz und <t false> bei vollen Scheibrechten bzw. im Fehlerfall -1.
// @xref <m DEX_QUERYROMODE>
#define DEX_GetROMode() 				\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYROMODE,0)
#define DEX_GetROModeEx(hPr) 			\
	(BOOL)DexExtensionProc2(hPr,(WPARAM)DEX_QUERYROMODE,0)
#define DEX_GetSchemaUpdatableEx(hPr) 			\
	(BOOL)DexExtensionProc2(hPr,(WPARAM)DEX_QUERYSCHEMAUPDATABLE,0)

// @func BOOL | DEX_GetROModeIdent | Abfragen des Zugriffsmodes der übergebenen Objektklasse.
// @rdesc Liefert <t true> bei Schreibschutz und <t false> bei vollen Scheibrechten bzw. im Fehlerfall -1.
// @xref <m DEX_QUERYROMODEIDENT>
#define DEX_GetROModeIdent(l) 				\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYROMODEIDENT,l)
#define DEX_SetROModeIdent(l) 				\
	(BOOL)DexExtensionProc((WPARAM)DEX_MODIFYROMODEIDENT,(LPARAM)&(l))

// @func BOOL | DEX_GetROModeFeature | Abfragen des Zugriffsmodes der übergebenen Objekteigenschaft (nicht deren Wert!).
// @rdesc Liefert <t true> bei Schreibschutz und <t false> bei vollen Scheibrechten bzw. im Fehlerfall -1.
// @xref <m DEX_QUERYROMODEMCODE>
#define DEX_GetROModeFeature(l) 				\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYROMODEMCODE,l)
#define DEX_SetROModeFeature(l) 				\
	(BOOL)DexExtensionProc((WPARAM)DEX_MODIFYROMODEMCODE,(LPARAM)&(l))
// immer dann verwenden, wenn MCode evtl. noch keine Zuordnung zu einer Datenquelle hat
#define DEX_GetROModeFeatureEx(hPr,l) 				\
	(BOOL)DexExtensionProc2(hPr,(WPARAM)DEX_QUERYROMODEMCODE,l)
#define DEX_SetROModeFeatureEx(hPr,l) 				\
	(BOOL)DexExtensionProc2(hPr,(WPARAM)DEX_MODIFYROMODEMCODE,(LPARAM)&(l))

// @func BOOL | DEX_GetOpened | Abfragen, ob Datenquelle geöffnet ist.
// @rdesc Liefert <t true> wenn geöffnet und anderenfalls <t false>.
// @xref <m DEX_QUERYDATASOURCEOPEN>
#define DEX_GetOpened() 				\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYDATASOURCEOPEN,0)
#define DEX_GetOpenedEx(hPr) 			\
	(BOOL)DexExtensionProc2(hPr,(WPARAM)DEX_QUERYDATASOURCEOPEN,0)

// @func BOOL | DEX_GetTRiASDataSourceEx | Abfragen , ob Datenquelle eine <tr> -GeoDB ist.
// @rdesc Liefert <t true> wenn es eine <tr> GeoDb ist und ansonsten <t false>.
// @xref <m DEX_QUERYTRIASDATASOURCE>
#define DEX_GetTRiASDataSourceEx(hPr) 			\
	(BOOL)DexExtensionProc2(hPr,(WPARAM)DEX_QUERYTRIASDATASOURCE,0)

// @func BOOL | DEX_GetGDODataSourceEx | Abfragen, ob Datenquelle eine GDO-basierte GeoDB ist.
// @rdesc Liefert <t true> wenn es eine <tr> GeoDb ist und ansonsten <t false>.
// @xref <m DEX_QUERYGDODATASOURCE>
#define DEX_GetGDODataSourceEx(hPr) 			\
	(BOOL)DexExtensionProc2(hPr,(WPARAM)DEX_QUERYGDODATASOURCE,0)

// @func char * | DEX_GetMainIniName | Abfragen des Namens der Initialisierungsdatei von <tr>.
// @parm char * | pIniName | Pufferbereich, in dem der volle Dateiname zurückgeliefert werden soll.
// @rdesc Liefert <p pIniName> bzw. im Fehlerfall NULL.
// @xref <m DEX_QUERYMAINININAME>
#define DEX_GetMainIniName(l)			\
	(char *)DexExtensionProc((WPARAM)DEX_QUERYMAINININAME,(LPARAM)(l))

// @func char * | DEX_GetActiveSight | Abfragen der aktuellen Ansicht des aktuellen Projektes.
// @parm char * | pViewName | Pufferbereich, in dem der Name der Ansicht zurückgeliefert werden soll.
// @rdesc Liefert <p pViewName> bzw. im Fehlerfall NULL.
// @xref <m DEX_QUERYACTIVESIGHT>
#define DEX_GetActiveSight(l)			\
	(char *)DexExtensionProc((WPARAM)DEX_QUERYACTIVESIGHT,(LPARAM)l)

// @func DWORD | DEX_GetDBVersion | Abfragen der Versionsnummer des aktuellen Projektes.
// @rdesc Liefert die Versionsnummer des aktuellen Projektes bzw. Null, wenn kein 
// aktuelles Projekt existiert.
// @xref <m DEX_QUERYGEODBVERSION>
#define DEX_GetDBVersion()				\
	DexExtensionProc((WPARAM)DEX_QUERYGEODBVERSION,(LPARAM)0)
#define DEX_GetDBVersionEx(hPr)				\
	DexExtensionProc2(hPr,(WPARAM)DEX_QUERYGEODBVERSION,(LPARAM)0)

///////////////////////////////////////////////////////////////////////////////
// liefert Bereich der beim letzten Vergrößern aufgezogen wurde
#define DEX_GetActiveSightContainer(l)	\
	DexExtensionProc((WPARAM)DEX_QUERYACTSIGHTCONTAINER,(LPARAM)&(l))
#define DEX_SetActiveSightContainer(l)	\
	DexExtensionProc((WPARAM)DEX_SETACTSIGHTCONTAINER,(LPARAM)&(l))

///////////////////////////////////////////////////////////////////////////////
// liefert evtl. existierendes Selektionsrechteck als DBKoords
#define DEX_GetActiveSelection(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYACTIVESELECTION,(LPARAM)(l))

///////////////////////////////////////////////////////////////////////////////
// liefert evtl. existierendes Selektionsrechteck als CS-Koords
#define DEX_GetActiveSelectionEx(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYACTIVESELECTIONEX,(LPARAM)&(l))

///////////////////////////////////////////////////////////////////////////////
// liefert Fensterausdehnungen in DBKoords umgerechnet
#define DEX_GetWindowAsDbContainer(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYWINDOWASDBCONTAINER,(LPARAM)(l))

///////////////////////////////////////////////////////////////////////////////
// liefert Fensterausdehnungen in CS-Koords umgerechnet
#define DEX_GetWindowAsContainer(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYWINDOWASCONTAINER,(LPARAM)&(l))

///////////////////////////////////////////////////////////////////////////////
// 
#define DEX_GetIdentVisInfo(l)			\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYIDENTVISINFO,(LPARAM)&(l))
#define DEX_ModIdentVisInfo(l)			\
	(BOOL)DexExtensionProc((WPARAM)DEX_MODIFYIDENTVISINFO,(LPARAM)&(l))
#define DEX_ModVisInfoDialog(l) 		\
	(ErrCode)DexExtensionProc((WPARAM)DEX_MODIFYVISINFODIALOG,(LPARAM)&(l))
	
#define DEX_GetNumOfOpenProjects()	\
	DexExtensionProc((WPARAM)DEX_QUERYOPENPROJECTS,0L)
#define DEX_OpenProject(l)				\
	(ErrCode)DexExtensionProc((WPARAM)DEX_PROJECTOPEN,(LPARAM)&(l))
#define DEX_OpenProjectEx(l)			  \
	(ErrCode)DexExtensionProc((WPARAM)DEX_PROJECTOPENEX,(LPARAM)&(l))
#define DEX_CloseProject(l) 	\
	DexExtensionProc((WPARAM)DEX_PROJECTCLOSE,(LPARAM)(l))
#define DEX_CloseProjectEx(l)			\
	DexExtensionProc((WPARAM)DEX_PROJECTCLOSEEX,(LPARAM)(l))
#define DEX_GetDefaultDataPath(l)	\
	(char *)DexExtensionProc((WPARAM)DEX_QUERYDEFAULTDATAPATH,(LPARAM)(l))
#define DEX_SetDefaultDataPath(l)	\
	DexExtensionProc((WPARAM)DEX_MODDEFAULTDATAPATH,(LPARAM)(l))
#define DEX_GetProjectCont(l)		\
	DexExtensionProc((WPARAM)DEX_QUERYPROJECTCONT,(LPARAM)&(l))
	
#define DEXI_isDrawing()				\
	DexExtensionProc((WPARAM)DEX_QUERYDRAWINGSTATUS,0L)
#define DEXI_isPrinting()				\
	DexExtensionProc((WPARAM)DEX_QUERYISPRINTING,0L)
#define DEXI_isAppWindowVisible()	\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYMAINWINDOWVISIBLE,0L)
#define DEXI_isInteractive()		\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYINTERACTIVE,0L)

#define DEX_ShowAppWindow(l)		\
	DexExtensionProc((WPARAM)DEX_SHOWMAINWINDOW,(LPARAM)(l))
#define DEX_HideAppWindow() 	\
	DexExtensionProc((WPARAM)DEX_HIDEMAINWINDOW,0L)
#define DEX_AppQuit(l)			\
	DexExtensionProc((WPARAM)DEX_QUITAPP,(LPARAM)(l))

// Anfragen zu einem konkreten Objekt -----------------------------------------
#define DEX_GetObjectType(l)			\
	(short)DexExtensionProc((WPARAM)DEX_QUERYOBJTYPE,(LPARAM)(l))
#define DEX_GetObjectStatus(l)			\
	(short)DexExtensionProc((WPARAM)DEX_QUERYOBJSTATUS,(LPARAM)(l))
#define DEX_GetKObjectRCode(l)			\
	DexExtensionProc((WPARAM)DEX_QUERYKOBJECTRCODE,(LPARAM)(l))
#define DEX_GetObjContainer(l,OC)		\
	DexExtensionProc((WPARAM)DEX_QUERYOBJCONTAINER,((*(long *)&OC=l),(LPARAM)&(OC)))
#define DEX_GetObjColor(l)		\
	DexExtensionProc((WPARAM)DEX_QUERYOBJCOLOR,(LPARAM)(l))
#define DEX_GetObjContainerEx(OC)		\
	DexExtensionProc((WPARAM)DEX_QUERYOBJCONTAINEREX,(LPARAM)&(OC))

// @func INT_PTR | DEX_GetObjIdent | Liefert grundsätzlich den Identifikator des
// gegebenen Objektes bzw. den Identifikator des Objektes, auf welches durch die
// gegebene (Pseudo-)Objektnummer (vergeben durch eine Zuordnungsobjektklasse)
// Bezug genommen wird.
// @xref <m DEX_QUERYOBJIDENT>, <f DEX_GetObjIdentEx>
#define DEX_GetObjIdent(l)		\
	(HOBJECTS)DexExtensionProc((WPARAM)DEX_QUERYOBJIDENT,(LPARAM)l)
// @func INT_PTR | DEX_GetObjIdentEx | Liefert evtl. Identifikator einer Zuordnungsobjektklasse, 
// wenn die gegebene Objektnummer durch eine Zuordnungsobjektklasse vergeben wurde. Ansonsten
// wird der Identifikator des Datenbank-Objektes geliefert (s. <f DEX_GetObjIdent>) 
// @xref <m DEX_QUERYOBJIDENT>, <f DEX_GetObjIdent>
#define DEX_GetObjIdentEx(l)		\
	(HOBJECTS)DexExtensionProc2(HACTPROJECT,(WPARAM)DEX_QUERYOBJIDENT,(LPARAM)l)

#define DEX_GetObjStatistik(St) \
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYOBJSTATISTIK,(LPARAM)&(St))
#define DEX_GetObjGeometrie(OG) \
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYOBJGEOMETRIE,(LPARAM)&(OG))
#define DEX_ModObjGeometrie(OG) \
	(BOOL)DexExtensionProc((WPARAM)DEX_MODIFYOBJGEOMETRIE,(LPARAM)&(OG))
#define DEX_ModObjGeometrieEx(hPr, OG) \
	(BOOL)DexExtensionProc2(hPr,(WPARAM)DEX_MODIFYOBJGEOMETRIE,(LPARAM)&(OG))

// @func char * | DEX_GetTextMerkmal | Liefert ein Merkmal eines Objektes, eines 
// Identifikators oder einer Sicht.
// @parm TARGETMERKMAL & | rTargetFeature | Referenz auf Struktur vom Typ <t TARGETMERKMAL> 
// oder <t TARGETMERKMALEX>.
// @rdesc Liefert bei erfolgreichem Abschluß der Aktion den Zeiger auf den übergebenen 
// Zeichenkettenpuffer <mf TARGETMERKMAL.pMText>, im Fehlerfall NULL.
// @xref <m DEX_QUERYTEXTMERKMAL>, <t TARGETMERKMAL>, <t TARGETMERKMALEX>
#define DEX_GetTextMerkmal(l)	\
	(char *)DexExtensionProc((WPARAM)DEX_QUERYTEXTMERKMAL,(LPARAM)&(l))

// @func ErrCode | DEX_ModTextMerkmal | Schreiben oder Löschen eines Merkmales eines Objektes,
// eines Identifikators oder einer Sicht.
// @parm TARGETMERKMAL & | rTargetFeature | Referenz auf Struktur vom Typ <t TARGETMERKMAL> 
// oder <t TARGETMERKMALEX>.
// @rdesc Liefert einen <t ErrCode>, der im Fehlerfall Auskunft über die Fehlerursache 
// gibt.
// @xref <m DEX_MODIFYMERKMAL>, <t TARGETMERKMAL>, <t TARGETMERKMALEX>, <t ErrCode>
#define DEX_ModTextMerkmal(l)	\
	(ErrCode)DexExtensionProc((WPARAM)DEX_MODIFYMERKMAL,(LPARAM)&(l))

#define DEX_GetIdentObjTypes(l) \
	(short)DexExtensionProc((WPARAM)DEX_QUERYIDENTOBJTYPES,(LPARAM)(l))
#define DEX_GetIdentObjTypesActView(l)	\
	(short)DexExtensionProc((WPARAM)DEX_QUERYIDENTOBJTYPESACTVIEW,(LPARAM)(l))

#define DEX_isObjectVisible(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_OBJECTISVISIBLE,(LPARAM)(l))

// @func BOOL | DEX_GetObjectName | Abfragen eines Objektnamens. In dem Fall, wenn für dieses 
// Objekt kein Objektname existeirt, wird der Unique Ident geliefert.
// @parm OBJECTFEATURE & | rObjFeature | Referenz auf Struktur vom Typ <t OBJECTFEATURE>.
// @rdesc Liefert bei erfolgreichem Abschluß der Aktion <t true>, im Fehlerfall <t false>.
// @xref <m DEX_QUERYOBJECTNAME>, <t OBJECTFEATURE>
#define DEX_GetObjectName(l)   \
	(char *)DexExtensionProc((WPARAM)DEX_QUERYOBJECTNAME,(LPARAM)&(l))

// @func BOOL | DEX_ModObjectName | Schreiben oder Löschen eines Objektnamens.
// @parm OBJECTFEATURE & | rObjFeature | Referenz auf Struktur vom Typ <t OBJECTFEATURE>.
// @rdesc Liefert bei erfolgreichem Abschluß der Aktion <t true>, im Fehlerfall <t false>.
// @xref <m DEX_SETOBJECTNAME>, <t OBJECTFEATURE>
#define DEX_ModObjectName(l)   \
	(ErrCode)DexExtensionProc((WPARAM)DEX_SETOBJECTNAME,(LPARAM)&(l))
	
#define DEX_FlushModifications()	\
	DexExtensionProc((WPARAM)DEX_FLUSHALLMODIFICATIONS,(LPARAM)0)
#define DEX_RebuildSight()		\
	(BOOL)DexExtensionProc((WPARAM)DEX_REBUILDVIEW,(LPARAM)0)
#define DEX_PostRebuildSight()		\
	::PostMessage(__hWndM,__DexCmd,(WPARAM)DEX_REBUILDVIEW,0)
#define DEX_SelectNewSight(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_SELNEWSIGHT,(LPARAM)l)
#define DEX_DeleteSight(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_DELETEVIEW,(LPARAM)l)
#define DEX_GetViewDescription(l)	\
	DexExtensionProc((WPARAM)DEX_QUERYVIEWDESCRIPTION,(LPARAM)&(l))
#define DEX_SetViewDescription(l)	\
	DexExtensionProc((WPARAM)DEX_MODVIEWDESCRIPTION,(LPARAM)&(l))
	
// Modifikationsanforderungen für ein Objekt ----------------------------------
// *** the following are obsolete, don't use
#define DEX_MergeObjects(R,O1,O2,Id,RCode,iFlag)		\
	{ MERGEKOBJECT __m; __m.mObj1=O1;__m.mObj2=O2;__m.mIdent=Id;__m.mRCode=RCode;__m.mMerge=iFlag;	\
	R=DexExtensionProc((WPARAM)DEX_MERGEKOBJECTS,(LPARAM)&__m); }
#define DEX_DeleteONFromKObject(R,O1,O2)		\
	{ DELETEKOBJECT __d; __d.doKObj=O1;__d.doObj=O2;		\
	R=DexExtensionProc((WPARAM)DEX_DELETEOBJFROMKOBJECT,(LPARAM)&__d); }
// neuen Identifikator einfügen -----------------------------------------------
#define DEX_AddNewIdent(R,Id,iTmp,iVTyp)		\
	{ ADDNEWIDENT __a; __a.newIdent=Id;__a.iFlags=iTmp;__a.iTyp=iVTyp;		\
	R=DexExtensionProc((WPARAM)DEX_ADDNEWIDENT,(LPARAM)&__a); }
// *** end of obsolete macros
#define DEX_AddNewIdentEx(l)		\
	DexExtensionProc((WPARAM)DEX_ADDNEWIDENT,(LPARAM)&(l))

// Komplexobjekt bilden/bearbeiten/löschen ------------------------------------
#define DEX_ModKomplexObj(l)		\
	(LONG)DexExtensionProc((WPARAM)DEX_MERGEKOBJECTS,(LPARAM)&(l))
#define DEX_DelFromKomplexObj(l)	\
	(LONG)DexExtensionProc((WPARAM)DEX_DELETEOBJFROMKOBJECT,(LPARAM)&(l))
#define DEX_RegNewIdent(l)		\
	(LONG)DexExtensionProc((WPARAM)DEX_ADDNEWIDENT,(LPARAM)&(l))

#define DEX_isIdentUsed(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_USEDIDENT,(LPARAM)(l))
#define DEX_isIdentUsedSight(l) \
	(BOOL)DexExtensionProc((WPARAM)DEX_USEDIDENTSIGHT,(LPARAM)(l))
#define DEX_isIdentUsedEx(hPr,l)		\
	(BOOL)DexExtensionProc2(hPr,(WPARAM)DEX_USEDIDENT,(LPARAM)(l))
#define DEX_isIdentUsedSightEx(hPr,l) \
	(BOOL)DexExtensionProc2(hPr,(WPARAM)DEX_USEDIDENTSIGHT,(LPARAM)(l))
#define DEX_isMCodeUsed(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_USEDMCODE,(LPARAM)(l))
#define DEX_isRCodeUsed(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_USEDRCODE,(LPARAM)(l))

// Enumerationsanforderungen --------------------------------------------------
#define DEX_EnumKObjects(R,ONr,fcn,ptr) 								\
	{ ENUMLONGKEY __s; __s.eKey=ONr;__s.eFcn=fcn;__s.ePtr=ptr;		\
	R=DexExtensionProc((WPARAM)DEX_ENUMKOMPLOBJECTS,(LPARAM)&__s); }

#define DEX_EnumSelectedObjects(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMSELECTEDOBJECTS,(LPARAM)&(l))
#define DEX_EnumSelectedObjectsEx(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMSELECTEDOBJECTSEX,(LPARAM)&(l))
#define DEX_EnumAllORObjects(l) 	\
	(BOOL)DexExtensionProc((WPARAM)DEX_RECHERCHEDOBJECTS,(LPARAM)&(l))

// @func BOOL | DEX_EnumIdentObjects | Enumerieren aller Objekte eines Identifikators.
// @parm ENUMLONGKEY & | rEnumLongKey | Referenz auf Struktur vom Typ <t ENUMLONGKEY>.
// @rdesc Liefert bei erfolgreichem Abschluß der Aktion <t true>, im Fehlerfall <t false>.
// @xref <m DEX_ENUMIDENTOBJS>, <t ENUMLONGKEY>
#define DEX_EnumIdentObjects(l) 		\
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMIDENTOBJS,(LPARAM)&(l))

// @func BOOL | DEX_EnumIdentObjectsEx | Enumerieren aller Objekte eines 
// Identifikators unter zusätzlicher Berücksichtigung des Objekttypes.
// @parm ENUMLONGKEYEX & | rEnumLongKeyEx | Referenz auf Struktur vom Typ <t ENUMLONGKEYEX>.
// @rdesc Liefert bei erfolgreichem Abschluß der Aktion <t true>, im Fehlerfall <t false>.
// @xref <m DEX_ENUMIDENTOBJSEX>, <t ENUMLONGKEYEX>
#define DEX_EnumIdentObjectsEx(l)		  \
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMIDENTOBJSEX,(LPARAM)&(l))

#define DEX_EnumSightIdents(l)			\
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMVIEWIDENTS,(LPARAM)&(l))
#define DEX_EnumSightIdentsEx(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMVIEWIDENTSEX,(LPARAM)&(l))

#define DEX_EnumIdentSightsEx(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMIDENTVIEWSEX,(LPARAM)&(l))

// @func BOOL | DEX_EnumIdents | Enumerieren aller Identifikatoren des aktuellen Projektes.
// @parm ENUMNOKEYLONG & | rEnumNoKey | Referenz auf Struktur vom Typ <t ENUMNOKEYLONG>.
// @rdesc Liefert bei erfolgreichem Abschluß der Aktion <t true>, im Fehlerfall <t false>.
// @xref <m DEX_ENUMALLIDENTS>, <t ENUMNOKEYLONG>
#define DEX_EnumIdents(l)				\
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMALLIDENTS,(LPARAM)&(l))
#define DEX_EnumClasses(hPr,l)				\
	(BOOL)DexExtensionProc2(hPr,(WPARAM)DEX_ENUMALLIDENTS,(LPARAM)&(l))

// @func BOOL | DEX_EnumIdentsEx | Enumerieren aller Identifikatoren des aktuellen Projektes
// unter zusätzlicher Berücksichtigung des Objekttypes.
// @parm ENUMNOKEYLONGEX & | rEnumNoKeyEx | Referenz auf Struktur vom Typ <t ENUMNOKEYLONGEX>.
// @rdesc Liefert bei erfolgreichem Abschluß der Aktion <t true>, im Fehlerfall <t false>.
// @xref <m DEX_ENUMALLIDENTSEX>, <t ENUMNOKEYLONGEX>
#define DEX_EnumIdentsEx(l) 			  \
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMALLIDENTSEX,(LPARAM)&(l))
#define DEX_EnumClassesEx(hPr,l) 			  \
	(BOOL)DexExtensionProc2(hPr,(WPARAM)DEX_ENUMALLIDENTSEX,(LPARAM)&(l))

#define DEXOR_EnumIdents(hWnd,l)			   \
	(BOOL)DexORExtensionProc(hWnd,(WPARAM)DEX_ENUMALLIDENTS,(LPARAM)&(l))
#define DEXOR_EnumIdentsEx(hWnd,l)				 \
	(BOOL)DexORExtensionProc(hWnd,(WPARAM)DEX_ENUMALLIDENTSEX,(LPARAM)&(l))

#define DEXOR_EnumIdentsSelected(hWnd,l)			   \
	(BOOL)DexORExtensionProc(hWnd,(WPARAM)DEX_ENUMIDENTSSELECTED,(LPARAM)&(l))
#define DEXOR_EnumIdentsSelectedEx(hWnd,l)				 \
	(BOOL)DexORExtensionProc(hWnd,(WPARAM)DEX_ENUMIDENTSSELECTEDEX,(LPARAM)&(l))

// @func BOOL | DEX_EnumObjektMerkmale | Enumerieren aller Objektmerkmale eines 
// vorgegebenen Objektes.
// @parm ENUMLONGKEY & | rEnumLongKey | Referenz auf Struktur vom Typ <t ENUMLONGKEY>.
// @rdesc Liefert im Normalfall <t true> und im Fehlerfall oder bei Abbruch der 
// Enumeration <t false>
// @xref <m DEX_ENUMMERKMALE>, <t ENUMLONGKEY>
#define DEX_EnumObjektMerkmale(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMMERKMALE,(LPARAM)&(l))

// @func BOOL | DEX_EnumIdentMerkmale | Enumerieren aller Identifikatormerkmale eines 
// vorgegebenen Identifikators.
// @parm ENUMLONGKEY & | rEnumLongKey | Referenz auf Struktur vom Typ <t ENUMLONGKEY>.
// @rdesc Liefert im Normalfall <t true> und im Fehlerfall oder bei Abbruch der 
// Enumeration <t false>
// @xref <m DEX_ENUMMERKMALEIDENT>, <t ENUMLONGKEY>
#define DEX_EnumIdentMerkmale(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMMERKMALEIDENT,(LPARAM)&(l))

// @func BOOL | DEX_EnumSichtMerkmale | Enumerieren aller Sichtmerkmale einer 
// vorgegebenen Sicht.
// @parm ENUMTEXTKEY & | rEnumTextKey | Referenz auf Struktur vom Typ <t ENUMTEXTKEY>.
// @rdesc Liefert im Normalfall <t true> und im Fehlerfall oder bei Abbruch der 
// Enumeration <t false>
// @xref <m DEX_ENUMMERKMALESICHT>, <t ENUMTEXTKEY>
#define DEX_EnumSichtMerkmale(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMMERKMALESICHT,(LPARAM)&(l))

// @func BOOL | DEX_EnumObjektMerkmaleEx | Enumerieren aller Merkmale eines 
// vorgegebenen Objektes.
// @parm ENUMLONGKEYEX & | rEnumLongKey | Referenz auf Struktur vom Typ <t ENUMLONGKEYEX>.
// @rdesc Liefert im Normalfall <t true> und im Fehlerfall oder bei Abbruch der 
// Enumeration <t false>
// @xref <m DEX_ENUMMERKMALEEX>, <t ENUMLONGKEYEX>
#define DEX_EnumObjektMerkmaleEx(l) 	  \
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMMERKMALEEX,(LPARAM)&(l))

// @func BOOL | DEX_EnumObjektMerkmaleClassEx | Enumerieren aller Merkmale der Objekte einer 
// Objektklasse.
// @parm ENUMLONGKEYEX & | rEnumLongKey | Referenz auf Struktur vom Typ <t ENUMLONGKEYEX>.
// @rdesc Liefert im Normalfall <t true> und im Fehlerfall oder bei Abbruch der 
// Enumeration <t false>
// @xref <m DEX_ENUMMERKMALECLASSEX>, <t ENUMLONGKEYEX>
#define DEX_EnumObjektMerkmaleClassEx(l) 	  \
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMMERKMALECLASSEX,(LPARAM)&(l))

// @func BOOL | DEX_EnumIdentMerkmaleEx | Enumerieren aller Merkmale eines 
// vorgegebenen Identifikators.
// @parm ENUMLONGKEYEX & | rEnumLongKey | Referenz auf Struktur vom Typ <t ENUMLONGKEYEX>.
// @rdesc Liefert im Normalfall <t true> und im Fehlerfall oder bei Abbruch der 
// Enumeration <t false>
// @xref <m DEX_ENUMMERKMALEIDENTEX>, <t ENUMLONGKEYEX>
#define DEX_EnumIdentMerkmaleEx(l)		  \
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMMERKMALEIDENTEX,(LPARAM)&(l))

// @func BOOL | DEX_EnumSichtMerkmaleEx | Enumerieren aller Merkmale einer 
// vorgegebenen Sicht.
// @parm ENUMTEXTKEYEX & | rEnumTextKey | Referenz auf Struktur vom Typ <t ENUMTEXTKEYEX>.
// @rdesc Liefert im Normalfall <t true> und im Fehlerfall oder bei Abbruch der 
// Enumeration <t false>
// @xref <m DEX_ENUMMERKMALESICHTEX>, <t ENUMTEXTKEYEX>
#define DEX_EnumSichtMerkmaleEx(l)		  \
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMMERKMALESICHTEX,(LPARAM)&(l))

#define DEX_EnumSights(l)				\
	DexExtensionProc((WPARAM)DEX_ENUMALLSIGHTS,(LPARAM)&(l))
#define DEX_EnumMCodes(l)				\
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMALLMCODES,(LPARAM)&(l))
#define DEX_EnumMCodesEx(l) 			  \
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMALLMCODESEX,(LPARAM)&(l))
#define DEX_EnumMCodesObjs(l) 			  \
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMALLMCODESOBJS,(LPARAM)&(l))

#define DEX_EnumHdrEntries(l)	\
	DexExtensionProc2(HACTPROJECT,(WPARAM)DEX_ENUMHEADER,(LPARAM)&(l))
#define DEX_EnumHeaderEntries(hPr,l)	\
	DexExtensionProc2(hPr,(WPARAM)DEX_ENUMHEADER,(LPARAM)&(l))

// @func BOOL | DEX_EnumRechTextMerkmal | Enumerieren aller Objekte, die ein bestimmtes 
// Merkmal besitzen. 
// @parm ENUMRECHTEXTMERKMAL & | rRechTextMerkmal | Referenz auf Struktur vom Typ <t ENUMRECHTEXTMERKMAL>.
// @rdesc Liefert im Normalfall <t true> und im Fehlerfall oder bei Abbruch der 
// Enumeration <t false>.
// @xref <m DEX_ENUMTEXTMERKMALRECH>, <t ENUMRECHTEXTMERKMAL>
#define DEX_EnumRechTextMerkmal(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMTEXTMERKMALRECH,(LPARAM)&(l))

#define DEX_EnumRechGeometrie(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMRECHGEOMETRIE,(LPARAM)&(l))

#define DEX_EnumTopRelations(l) \
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMTOPRELATIONS,(LPARAM)(l))
#define DEX_ModifyRelation(MR)	\
	(ErrCode)DexExtensionProc((WPARAM)DEX_MODRELATION,(LPARAM)&(MR))
#define DEX_DeleteRelation(DR)	\
	(ErrCode)DexExtensionProc((WPARAM)DEX_DELRELATION,(LPARAM)&(DR))
	
#define DEX_RePaint()	\
	::PostMessage(__hWndM,__DexCmd,(WPARAM)DEX_REPAINTALL,0)
#define DEX_RePaintWait()			\
	DexExtensionProc((WPARAM)DEX_REPAINTALL,1)
#define DEX_RePaintRect(l)			\
	::PostMessage(__hWndM,__DexCmd,(WPARAM)DEX_REPAINTRECT,(LPARAM)&(l))
#define DEX_RePaintRectWait(l)		\
	DexExtensionProc((WPARAM)DEX_REPAINTRECT,(LPARAM)&(l))
#define DEX_RePaintObject(l)		\
	DexExtensionProc((WPARAM)DEX_OBJECTREPAINT,(LPARAM)(l))

#define DEX_IsPreventRepaintActive()	\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYPREVENTREPAINT,0)
#define DEX_SetPreventRepaint(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_PREVENTREPAINT,(LPARAM)(l))

// Befehle an den ObjektBaum --------------------------------------------------
#define DEX_SetAttributes(lONr) 		\
	DexExtensionProc((WPARAM)DEX_SETATTRIBUTES,(LPARAM)lONr)
#define DEX_ResetAttributes(lONr)		\
	DexExtensionProc((WPARAM)DEX_RESETATTRIBUTES,(LPARAM)lONr)

// Verwaltung der PBD ---------------------------------------------------------
#define DEX_BeginPBDTransaction()	\
	DexExtensionProc((WPARAM)DEX_BEGINPBDTRANSACTION,0L)
#define DEX_BreakPBDTransaction()	\
	DexExtensionProc((WPARAM)DEX_BREAKPBDTRANSACTION,0L)
#define DEX_EndPBDTransaction() 	\
	DexExtensionProc((WPARAM)DEX_ENDPBDTRANSACTION,0L)
#define DEX_GetPBDVersion()	\
	DexExtensionProc((WPARAM)DEX_QUERYPBDVERSION,0L)

#define DEX_GetPBDData(p)	\
	(ErrCode)DexExtensionProc((WPARAM)DEX_QUERYPBDDATA,(LPARAM)&(p))
#define DEX_DelPBDData(p)	\
	(ErrCode)DexExtensionProc((WPARAM)DEX_DELPBDDATA,(LPARAM)&(p))
#define DEX_ModPBDData(p)	\
	(ErrCode)DexExtensionProc((WPARAM)DEX_MODPBDDATA,(LPARAM)&(p))
#define DEX_EnumPBDData(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMPBDDATA,(LPARAM)&(l))
#define DEX_GetTableName(l)	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_QUERYTABLENAME,(LPARAM)&(l))

#define DEX_GetPBDDataEx(hPr,p)	\
	(ErrCode)DexExtensionProc2(hPr,(WPARAM)DEX_QUERYPBDDATA,(LPARAM)&(p))
#define DEX_DelPBDDataEx(hPr,p)	\
	(ErrCode)DexExtensionProc2(hPr,(WPARAM)DEX_DELPBDDATA,(LPARAM)&(p))
#define DEX_ModPBDDataEx(hPr,p)	\
	(ErrCode)DexExtensionProc2(hPr,(WPARAM)DEX_MODPBDDATA,(LPARAM)&(p))
#define DEX_EnumPBDDataEx(hPr,l)	\
	(BOOL)DexExtensionProc2(hPr,(WPARAM)DEX_ENUMPBDDATA,(LPARAM)&(l))

// GeoDBHeader Verwalten ------------------------------------------------------
#define DEX_ReadGeoDBHdrEntry(l)		\
	(ErrCode)DexExtensionProc2(HACTPROJECT,(WPARAM)DEX_READHEADER,(LPARAM)&(l))
#define DEX_WriteGeoDBHdrEntry(l)		\
	(ErrCode)DexExtensionProc2(HACTPROJECT,(WPARAM)DEX_MODIFYHEADER,(LPARAM)&(l))
#define DEX_DeleteGeoDBHdrEntry(l)		\
	(ErrCode)DexExtensionProc2(HACTPROJECT,(WPARAM)DEX_DELETEHEADER,(LPARAM)&(l))

#define DEX_ReadHeaderEntry(hPr,l)		  \
	(ErrCode)DexExtensionProc2(hPr,(WPARAM)DEX_READHEADER,(LPARAM)&(l))
#define DEX_WriteHeaderEntry(hPr,l) 	  \
	(ErrCode)DexExtensionProc2(hPr,(WPARAM)DEX_MODIFYHEADER,(LPARAM)&(l))
#define DEX_DeleteHeaderEntry(hPr,l)	  \
	(ErrCode)DexExtensionProc2(hPr,(WPARAM)DEX_DELETEHEADER,(LPARAM)&(l))
#define DEX_ReadGeoDBHdrEntryEx		DEX_ReadHeaderEntry
#define DEX_WriteGeoDBHdrEntryEx	DEX_WriteHeaderEntry
#define DEX_DeleteGeoDBHdrEntryEx	DEX_DeleteHeaderEntry

// TRiAS5: DEX_GetUniqueICode liefert den nächsten freien Ident und definiert 
// diesen als gültige Objektklasse
#define DEX_GetUniqueICode()			\
	(HOBJECTS)DexExtensionProc((WPARAM)DEX_GETUNIQUEICODE,(LPARAM)false)
#define DEX_GetUniqueICodeEx(hPr)			\
	(HOBJECTS)DexExtensionProc2(hPr,(WPARAM)DEX_GETUNIQUEICODE,(LPARAM)false)

// TRiAS5: DEX_GetUniqueSysICode liefert den nächsten freien Ident ohne selbigen 
// bereits zu definieren
#define DEX_GetUniqueSysICode() 		   \
	(HOBJECTS)DexExtensionProc((WPARAM)DEX_GETUNIQUEICODE,(LPARAM)true)
#define DEX_GetUniqueSysICodeEx(hPr) 		   \
	(HOBJECTS)DexExtensionProc2(hPr,(WPARAM)DEX_GETUNIQUEICODE,(LPARAM)true)

#define DEX_GetUniqueMCode()			\
	(HFEATURE)DexExtensionProc2(HACTPROJECT,(WPARAM)DEX_GETUNIQUEMCODE,(LPARAM)false)
#define DEX_GetUniqueSysMCode() 		\
	(HFEATURE)DexExtensionProc2(HACTPROJECT,(WPARAM)DEX_GETUNIQUEMCODE,(LPARAM)true)

// Die folgenden nicht verwenden, da diese zu Inkonsistenzen führen können!
//#define DEX_GetUniqueMCodeEx(hPr)			\
//	DexExtensionProc2(hPr,(WPARAM)DEX_GETUNIQUEMCODE,(LPARAM)false)
//#define DEX_GetUniqueSysMCodeEx(hPr) 		\
//	DexExtensionProc2(hPr,(WPARAM)DEX_GETUNIQUEMCODE,(LPARAM)true)

#define DEX_GetUniqueRCode()			\
	(HRELATION)DexExtensionProc((WPARAM)DEX_GETUNIQUERCODE,(LPARAM)0)
#define DEX_GetUniqueTempONr()			\
	(HRELATION)DexExtensionProc((WPARAM)DEX_GETUNIQUETEMPON,(LPARAM)0)

#define DEX_GetActiveScaling(l) 		\
	DexExtensionProc((WPARAM)DEX_QUERYACTSCALING,(LPARAM)&l)
#define DEX_GetActiveAspect(l)         \
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYACTASPECTRATIO,(LPARAM)&(l))
#define DEX_GetActiveZoom(l)				\
	DexExtensionProc((WPARAM)DEX_QUERYACTMASSTAB,(LPARAM)&l)
#define DEX_SetActiveZoom(l)			\
	DexExtensionProc((WPARAM)DEX_SETACTSCALING,(LPARAM)l)
#define DEX_OCtoDC(l)	\
	DexExtensionProc((WPARAM)DEX_OCTODC,(LPARAM)&(l))
#define DEX_DCtoOC(l)	\
	DexExtensionProc((WPARAM)DEX_DCTOOC,(LPARAM)&(l))
#define DEX_OCtoDCEx(l)   \
	DexExtensionProc((WPARAM)DEX_OCTODCEX,(LPARAM)&(l))
#define DEX_DCtoOCEx(l)   \
	DexExtensionProc((WPARAM)DEX_DCTOOCEX,(LPARAM)&(l))
#define DEX_OCtoRC(l)	\
	DexExtensionProc((WPARAM)DEX_OCTORC,(LPARAM)&(l))
#define DEX_RCtoOC(l)	\
	DexExtensionProc((WPARAM)DEX_RCTOOC,(LPARAM)&(l))

#define DEX_GetActiveTool() 	\
	(short)DexExtensionProc((WPARAM)DEX_QUERYACTIVETOOL,0L)
#define DEX_ChangeActiveTool(l) 	\
	(short)DexExtensionProc((WPARAM)DEX_SETACTIVETOOL,(l))
		
// Fehlerbehandlung -----------------------------------------------------------
#define DEX_ErrInstall(R,RC,EH,oEH) 	\
	{ ERRINSTALL __EI; __EI.eiRC=RC;__EI.eiEH=(ERRHANDLER)EH;__EI.eioEH=(ERRHANDLER *)oEH;	\
	R=(ErrCode)DexExtensionProc((WPARAM)DEX_ERRINSTALL,(LPARAM)&__EI); }
#define DEX_ExtErrInstall(R,RC,EH,oEH,pD)		\
	{ EXTERRINSTALL __EI; __EI.eiRC=RC;__EI.eiEH=(ERRHANDLER)EH;__EI.eioEH=(ERRHANDLER *)oEH;__EI.dwData=pD;		\
	R=(ErrCode)DexExtensionProc((WPARAM)DEX_EXTERRINSTALL,(LPARAM)&__EI); }
#define DEX_SetError(R,RC,EC,pD)		\
	{ ERRORMESSAGE __E; __E.emiRoutine=RC;__E.emiErrCode=EC;__E.empData=pD; \
	R=(ErrCode)DexExtensionProc((WPARAM)DEX_SETERROR,(LPARAM)&__E); }

#define DEX_Error(RC,EC)		\
	{ ERRORMESSAGE __E; __E.emiRoutine=RC;__E.emiErrCode=EC;__E.empData=NULL; \
	  DexExtensionProc((WPARAM)DEX_SETERROR,(LPARAM)&__E); }

// ObjRechFenster aufmachen ---------------------------------------------------
#define DEX_CreateObjektInfo(l) \
	(HWND)DexExtensionProc((WPARAM)DEX_CREATEOBJEKTINFO,(LPARAM)&(l))

// Löschen eines Objektes -----------------------------------------------------
#define DEX_DeleteObject(l) 	\
	(BOOL)DexExtensionProc((WPARAM)DEX_DELOBJECT,(LPARAM)l)
#define DEXOR_DeleteObject(hWnd,l)		\
	DexORExtensionProc(hWnd,(WPARAM)DEX_DELOBJECT,(LPARAM)l)

#if !defined(WIN16)
#define DEX_DeleteObjectEx(l)	  \
	(BOOL)DexExtensionProc((WPARAM)DEX_DELOBJECTEX,(LPARAM)l)
#define DEX_DeleteObjectRect(l)	  \
	(BOOL)DexExtensionProc((WPARAM)DEX_DELETEOBJECTUNDORECT,(LPARAM)&(l))
#else
#define DEX_DeleteObjectEx(l)	DEX_DeleteObject(l)
#endif // WIN16

#define DEX_ModObjectIdent(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_MODOBJIDENT,(LPARAM)&(l))
#define DEXOR_ModObjectIdent(hWnd,l)	\
	DexORExtensionProc(hWnd,(WPARAM)DEX_MODOBJIDENT,(LPARAM)&(l))

#if !defined(WIN16)
#define DEX_ModObjectIdentEx(l)   \
	(BOOL)DexExtensionProc((WPARAM)DEX_MODOBJIDENTEX,(LPARAM)&(l))
#define DEXOR_ModObjectIdentEx(hWnd,l)	  \
	DexORExtensionProc(hWnd,(WPARAM)DEX_MODOBJIDENTEX,(LPARAM)&(l))
#else
#define DEX_ModObjectIdentEx		DEX_ModObjectIdent
#define DEXOR_ModObjectIdentEx		DEXOR_ModObjectIdent
#endif // WIN16

///////////////////////////////////////////////////////////////////////////////
// Zuordnungsobjetklassen verwalten
#define DEX_AddObjectToClass(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_ADDOBJECT2CLASS,(LPARAM)&(l))
#define DEX_DelObjectFromClass(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_DELETEOBJECTFROMCLASS,(LPARAM)&(l))
#define DEX_IsObjectInClass(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_OBJECTISINCLASS,(LPARAM)&(l))
#define DEX_GetNativeObject(l)	\
	DexExtensionProc((WPARAM)DEX_QUERYNATIVEOBJECT,(LPARAM)(l))

// @func BOOL | DEX_EnumObjectClasses | Enumerieren aller Objekte eines Identifikators.
// @parm ENUMLONGKEYEX & | rEnumLongKey | Referenz auf Struktur vom Typ <t ENUMLONGKEYEX>.
// @rdesc Liefert bei erfolgreichem Abschluß der Aktion <t true>, im Fehlerfall <t false>.
// @xref <m DEX_ENUMCLASSESFROMOBJECT>, <t ENUMLONGKEYEX>
#define DEX_EnumObjectClasses(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMCLASSESFROMOBJECT,(LPARAM)&(l))

///////////////////////////////////////////////////////////////////////////////
// 
#define DEX_FindObjectsFromPoint(l) 	\
	DexExtensionProc((WPARAM)DEX_FINDOBJECT,(LPARAM)&(l))

#define DEX_GetIdBase() 		\
	(short)DexExtensionProc((WPARAM)DEX_QUERYIDENTBASE,0L)
#define DEX_GetMkBase() 		\
	(short)DexExtensionProc((WPARAM)DEX_QUERYMCODEBASE,0L)

#define DEX_RemoveAllORWnds()	\
	DexExtensionProc((WPARAM)DEX_REMOVEORWND,0L)
#define DEX_PostRemoveAllORWnds()	\
	::PostMessage(__hWndM,__DexCmd,(WPARAM)DEX_REMOVEORWND,0L)
#define DEX_RemoveORWnd(l)		\
	DexExtensionProc((WPARAM)DEX_REMOVEORWND,(LPARAM)(l))
#define DEX_GetActiveORWnd()	\
	(HWND)DexExtensionProc((WPARAM)DEX_QUERYACTIVEORWINDOW,(LPARAM)(0))
#define DEX_SetActiveORWnd(l)	\
	(HWND)DexExtensionProc((WPARAM)DEX_SETACTIVEORWINDOW,(LPARAM)(l))

#define DEX_CreateNewGeoDB(l)	\
	(ErrCode)DexExtensionProc((WPARAM)DEX_CREATENEWGEODB,(LPARAM)&(l))
#define DEX_CreateNewIdentsDB(l)		\
	(ErrCode)DexExtensionProc((WPARAM)DEX_CREATENEWIDENTSDB,(LPARAM)&(l))

#define DEX_RenderGeoDB(l)	\
	DexExtensionProc((WPARAM)DEX_RENDERGEODB,(LPARAM)&(l))
#define DEX_GetExposedOC(l) \
	DexExtensionProc((WPARAM)DEX_QUERYEXPOSEDOC,(LPARAM)&(l))
#define DEX_GetExposedArea(l)	\
	DexExtensionProc((WPARAM)DEX_QUERYEXPOSEDAREA,(LPARAM)&(l))

#define DEX_GetLastIdent()	\
	(long)DexExtensionProc((WPARAM)DEX_GETLASTIDENT,(LPARAM)0)
#define DEX_SetLastIdent(l) \
	DexExtensionProc((WPARAM)DEX_SETLASTIDENT,(LPARAM)(l))

#define DEX_SaveLegend()	\
	DexExtensionProc((WPARAM)DEX_SAVELEGEND,0L)
#define DEX_ResetLegend()	\
	DexExtensionProc((WPARAM)DEX_RESETLEGEND,0L)
#define DEX_RefreshLegend() \
	DexExtensionProc((WPARAM)DEX_REFRESHLEGEND,0L)
#define DEX_AddObjectToLegend(l)	\
	DexExtensionProc((WPARAM)DEX_ADDOBJECTTOLEGEND,(LPARAM)l)
#define DEX_RepaintLegend() \
	DexExtensionProc((WPARAM)DEX_REPAINTLEGEND,0L)
#define DEX_IsLegendActive()	\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYLEGENDACTIVE,0L)
#define DEX_MayOpenLegend() \
	(BOOL)DexExtensionProc((WPARAM)WM_QUERYMAYOPENLEGEND,0L)

// Relationen -----------------------------------------------------------------
#define DEX_EnumRelationObjects(l)	\
	DexExtensionProc((WPARAM)DEX_ENUMRELATIONOBJS,(LPARAM)&(l))

// OLE-Unterstützung ----------------------------------------------------------
#define DEX_GetProjectStorage(l)	\
	DexExtensionProc2(HACTPROJECT,(WPARAM)DEX_QUERYPROJECTSTORAGE,(LPARAM)&(l))
#define DEX_GetDataSourceStorage(hPr,l) \
	DexExtensionProc2(hPr,(WPARAM)DEX_QUERYPROJECTSTORAGE,(LPARAM)&(l))
#define DEX_GetActivePalette()	\
	(HPALETTE)DexExtensionProc((WPARAM)DEX_QUERYACTIVEPALETTE,0)

#define DEX_GetTextObjectText(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_GETTEXTOBJECTTEXT,(LPARAM)&(l))
#define DEX_PutTextObjectText(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_PUTTEXTOBJECTTEXT,(LPARAM)&(l))
#define DEX_GetTextFeature(l)		\
	(INT_PTR)DexExtensionProc((WPARAM)DEX_QUERYTEXTFEATURE,(LPARAM)(l))

// Blinken in ORFenstern abschalten/zuschalten --------------------------------
#define DEX_CancelMode(l)	\
	DexExtensionProc((WPARAM)DEX_CANCELMODE,(LPARAM)(l))

// @func void | DEX_EnableDiagnostics | Erlaubt die Generierung der 
// Diagnose-Notifikationen, die zusätzliche Informationen über interne 
// Aktionen in <tr> liefern.
// @rdesc Liefert den vorhergehenden Zustand des Enable-Flags (<t true>, wenn
// die Diagnose-Notifikationen bereits erlaubt waren, und <t false>, wenn nicht).
// @xref <m DEX_DIAGNOSTICSENABLE>, <f DEX_DisableDiagnostics>
#define DEX_EnableDiagnostics() \
	(BOOL)DexExtensionProc((WPARAM)DEX_DIAGNOSTICSENABLE,(LPARAM)true)

// @func void | DEX_DisableDiagnostics | Verbietet die Generierung der 
// Diagnose-Notifikationen, die zusätzliche Informationen über interne 
// Aktionen in <tr> liefern.
// @rdesc Liefert den vorhergehenden Zustand des Enable-Flags (<t true>, wenn
// die Diagnose-Notifikationen bereits erlaubt waren, und <t false>, wenn nicht).
// @xref <m DEX_DIAGNOSTICSENABLE>, <f DEX_EnableDiagnostics>
#define DEX_DisableDiagnostics()	\
	(BOOL)DexExtensionProc((WPARAM)DEX_DIAGNOSTICSENABLE,(LPARAM)false)
		
// @func ULONG | DEX_GetUnknownIdent | Liefert einen für das aktuelle Projekt
// eindeutigen Identifikator, der für Objekte mit unbekannter Objektklasse vergeben
// werden kann.
// @rdesc Liefert den gesuchten Identifikator. Im Fehlerfall liefert diese Funktion
// Null.
// @xref <m DEX_QUERYUNKNOWNIDENT>
#define DEX_GetUnknownIdent()		\
	DexExtensionProc((WPARAM)DEX_QUERYUNKNOWNIDENT,0L)
#define DEX_GetUnknownIdentEx(hPr)		\
	DexExtensionProc2(hPr,(WPARAM)DEX_QUERYUNKNOWNIDENT,0L)

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

// @func ULONG | DEX_GetObjNameMCode | Liefert für das aktuelle Projekt und einen 
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

// @func ULONG | DEX_GetObjNameMCode | Liefert für das aktuelle Projekt und einen 
// gegebenen Identifikator den Merkmalscode, unter dem für die Objekte dieses 
// Identifikators der ObjektGuid (PrimaryKey) abgelegt ist.
// @parm ULONG | lIdent | Identifikator, für dessen Objekte der Merkmalscode gesucht 
// wird.
// @rdesc Liefert den Merkmalscode, unter dem die Guids der Objekte mit dem 
// Identifikator <p lIdent> abgespeichert sind. Im Fehlerfall liefert diese 
// Funktion Null.
// @xref <m DEX_QUERYOBJNAMEMCODE>
#define DEX_GetObjGuidMCode(l)		\
	DexExtensionProc((WPARAM)DEX_QUERYOBJGUIDMCODE,(LPARAM)(l))

// @func ULONG | DEX_GetUniqueIdentMCode | Liefert für das aktuelle Projekt den 
// Merkmalscode, unter dem die Unique Idents der Objekte abgelegt ist.
// @rdesc Liefert den Merkmalscode, unter dem die Objekte ihren Unique Ident 
// abgespeichert haben.
// @xref <m DEX_QUERYUNIQUEIDENTMCODE>
#define DEX_GetUniqueIdentMCode()	\
	(ULONG)DexExtensionProc((WPARAM)DEX_QUERYUNIQUEIDENTMCODE,0L)
#define DEX_GetUniqueIdentMCodeEx(hPr)	\
	(ULONG)DexExtensionProc2(hPr,(WPARAM)DEX_QUERYUNIQUEIDENTMCODE,0L)

// @func ULONG | DEX_GetOldUniqueIdentMCode | Liefert für das aktuelle Projekt den 
// Merkmalscode, unter dem die ursprünglichen Unique Idents der Objekte abgelegt ist.
// @rdesc Liefert den Merkmalscode, unter dem die Objekte ihren ursprünglichen Unique Ident 
// abgespeichert haben.
// @xref <m DEX_QUERYOLDUNIQUEIDENTMCODE>
#define DEX_GetOldUniqueIdentMCode()	\
	(ULONG)DexExtensionProc((WPARAM)DEX_QUERYOLDUNIQUEIDENTMCODE,0L)
#define DEX_GetOldUniqueIdentMCodeEx(hPr)	\
	(ULONG)DexExtensionProc2(hPr,(WPARAM)DEX_QUERYOLDUNIQUEIDENTMCODE,0L)

// @func BOOL | DEX_ReReadHeader | Liest diverse Headereinträge des aktuellen 
// Projektes neu ein.
// @rdesc Liefert einen <t BOOL> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @xref <m DEX_HEADERREREAD>, <f DEX_ReReadHeaderEx>
#define DEX_ReReadHeader()		\
	(BOOL)DexExtensionProc((WPARAM)DEX_HEADERREREAD,0)

// @func BOOL | DEX_ReReadHeaderEx | Liest den angegebenen Headereintrag des 
// aktuellen Projektes neu ein.
// @rdesc Liefert einen <t BOOL> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @parm const char * | pHeaderEntry | Zeichenkette, die den Namen des neu einzulesenden
// Headereintrages vorgibt
// @xref <m DEX_HEADERREREAD>, <f DEX_ReReadHeader>
#define DEX_ReReadHeaderEx(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_HEADERREREAD,(LPARAM)(l))

// Caption neu generieren -----------------------------------------------------
#define DEX_ReReadCaption() 	\
	(BOOL)DexExtensionProc((WPARAM)DEX_CAPTIONREREAD,0)

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
#define DEX_GetIdentFromClassNameEx(hPr,l)	\
	DexExtensionProc2(hPr,(WPARAM)DEX_FINDIDENTFROMNAME,(LPARAM)(l))
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
#define DEX_GetIdentFromClassNameCIEx(hPr,l)	\
	DexExtensionProc2(hPr,(WPARAM)DEX_FINDIDENTFROMNAMECI,(LPARAM)(l))

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
#define DEX_GetMCodeFromFeatureNameEx(hPr,l)	\
	DexExtensionProc2(hPr,(WPARAM)DEX_FINDFEATUREFROMNAME,(LPARAM)(l))

// @func ULONG | DEX_GetMCodeFromFeatureNameCI | Liefert für ein gegebenes Merkmal
// den zugehörigen Merkmalscode. Groß-/Kleinschreibung wird dabei ignoriert.
// @rdesc Liefert den gesuchten Merkmalscode oder Null, wenn kein entsprechendes
// Merkmal gefunden werden konnte.
// @parm char * | pFeatureName | Zeichenkette, die den Namen des Merkmales
// enthält, für die der Merkmalscode (Schlüssel) gesucht wird.
// @xref <m DEX_FINDFEATUREFROMNAME>, <m DEX_FINDFEATUREFROMNAMECI>,
// <f DEX_GetMCodeFromFeatureName>
#define DEX_GetMCodeFromFeatureNameCI(l)	\
	DexExtensionProc((WPARAM)DEX_FINDFEATUREFROMNAMECI,(LPARAM)(l))
#define DEX_GetMCodeFromFeatureNameCIEx(hPr,l)	\
	DexExtensionProc2(hPr,(WPARAM)DEX_FINDFEATUREFROMNAMECI,(LPARAM)(l))

// @func BOOL | DEX_DeleteAllIdentObjects | Löscht alle Objekte eines Identifikators.
// @rdesc Liefert einen <t BOOL> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @parm ULONG | lIdent | Identifikator, dessen Objekte gelöscht werden sollen.
// @xref <m DEX_DELETEIDENT>
#define DEX_DeleteAllIdentObjects(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_DELETEIDENT,(LPARAM)(l))

// @func BOOL | DEX_CreateView | Legt eine neue Ansicht unter dem gegebenen Sichtnamen
// an. Wenn diese Ansicht bereits existiert, wird diese vorher gelöscht.
// @rdesc Liefert einen <t BOOL> - Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @parm char * | pViewName | Zeichenkette, die den Namen der neu zu erzeugenden 
// Ansicht enthält.
// @xref <m DEX_VIEWCREATE>, <f DEX_CreateViewOpt>
#define DEX_CreateView(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_VIEWCREATE,(LPARAM)(l))

// @func BOOL | DEX_CreateViewOpt | Legt eine neue Ansicht unter dem gegebenen Sichtnamen
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
	(BOOL)DexExtensionProc((WPARAM)DEX_VIEWCREATEOPT,(LPARAM)(l))

// @func BOOL | DEX_RemoveIdentFromView | Enfernt eine Identifikator/Objekttyp-
// Kombination aus einer gegebenen Ansicht.
// @rdesc Liefert einen <t BOOL> -Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @parm VIEWIDENTOBJECT & | rViewIdentOTyp | Referenz einer Struktur vom 
// Typ <t VIEWIDENTOBJECT>, die die notwendigen Informationen enthält.
// @xref <t VIEWIDENTOBJECT>, <m DEX_DELETEIDENTFROMVIEW>
#define DEX_RemoveIdentFromView(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_DELETEIDENTFROMVIEW,(LPARAM)&(l))

// @func BOOL | DEX_AddIdentToView | Fügt eine Identifikator/Objekttyp-
// Kombination zu einer gegebenen Ansicht hinzu. Dabei wird die 
// Standardvisualisierung verwendet.
// @rdesc Liefert einen <t BOOL> -Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @parm VIEWIDENTOBJECT & | rViewIdentOTyp | Referenz einer Struktur vom 
// Typ <t VIEWIDENTOBJECT>, die die notwendigen Informationen enthält.
// @xref <t VIEWIDENTOBJECT>, <m DEX_IDENTADDTOVIEW>
#define DEX_AddIdentToView(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_IDENTADDTOVIEW,(LPARAM)&(l))

// @func BOOL | DEX_RenameView | Ändert den Namen einer Ansicht.
// @rdesc Liefert einen <t BOOL> -Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @parm RENAMEVIEW & | rRenameView | Referenz einer Struktur vom 
// Typ <t RENAMEVIEW>, die sowohl den Namen der Ansicht vorgibt, die umbenannt 
// werden soll, als auch den neuen Namen.
// @xref <m DEX_VIEWRENAME>, <t RENAMEVIEW>
#define DEX_RenameView(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_VIEWRENAME,(LPARAM)&(l))

// @func BOOL | DEX_ViewHasIdent | Stellt fest, ob eine gegebene Identifikator/Objekttyp-
// Kombination zu einer Ansicht gehört.
// @rdesc Liefert einen <t BOOL> -Wert, der Auskunft darüber gibt, ob Objekte
// des gegebenen Typs mit dem gegebenen Identifikator zu einer Ansicht gehören 
// oder nicht.
// @parm VIEWIDENTOBJECT & | riewIdentOTyp | Referenz einer Struktur vom 
// Typ <t VIEWIDENTOBJECT>, die die notwendigen Informationen enthält.
// @xref <t VIEWIDENTOBJECT>, <m DEX_HASVIEWIDENT>
#define DEX_ViewHasIdent(l) 	\
	(BOOL)DexExtensionProc((WPARAM)DEX_HASVIEWIDENT,(LPARAM)&(l))

// @func BOOL | DEX_ViewHasObject | Stellt fest, ob ein gegebenes Objekt
// zu einer Ansicht gehört.
// @rdesc Liefert einen <t BOOL> -Wert, der Auskunft darüber gibt, ob das Objekt
// zu einer Ansicht gehört oder nicht.
// @parm VIEWIDENTOBJECT & | rViewIdentOTyp | Referenz einer Struktur vom 
// Typ <t VIEWIDENTOBJECT>, die die notwendigen Informationen enthält.
// @xref <t VIEWIDENTOBJECT>, <m DEX_HASVIEWOBJECT>
#define DEX_ViewHasObject(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_HASVIEWOBJECT,(LPARAM)&(l))

// @func long | DEX_GetClipObject | Liefert das für eine Ansicht gesetzte 
// Clipping Objekt.
// @rdesc Liefert die Objektnummer des Objektes, welches als Clipping-Objekt 
// für diese Ansicht gesetzt ist.
// @parm char * | pViewName | Name der zu untersuchenden Ansicht. Wenn gleich NULL, 
// dann aktuelle Ansicht untersuchen.
// @xref <m DEX_QUERYCLIPOBJECT>, <m DEX_CLIPOBJECTSET>
#define DEX_GetClipObject(l)		\
	(LONG)DexExtensionProc((WPARAM)DEX_QUERYCLIPOBJECT,(LPARAM)l)

// @func long | DEX_SetClipObject | Setzt für eine Ansicht das zu verwendende
// Clipping Objekt.
// @rdesc Liefert einen <t BOOL> -Wert, also im Normalfall <t true> 
// und Fehlerfall <t false>.
// @parm CLIPOBJECTSET & | rClipObjSet | Referenz einer Struktur vom 
// Typ <t CLIPOBJECTSET>
// @xref <m DEX_CLIPOBJECTSET>, <t CLIPOBJECTSET>, <m DEX_QUERYCLIPOBJECT>
#define DEX_SetClipObject(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_CLIPOBJECTSET,(LPARAM)&(l))

// @func BOOL | DEX_ProjectHasView | Stellt fest, ob im aktuellen Projekt
// eine gegebene Ansicht definiert ist.
// @rdesc Liefert einen <t BOOL> -Wert, der Auskunft darüber gibt, ob die Ansicht
// zum aktuelle Projekt gehört oder nicht.
// @parm char * | pViewName | Pointer auf den Namen der Ansicht
// @xref <m DEX_HASPROJECTVIEW>
#define DEX_ProjectHasView(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_HASPROJECTVIEW,(LPARAM)(l))

// @func BOOL | DEX_IsORWindow | Stellt fest, ob das Fenster, dessen Handle (HWND)
// übergeben wird ein gültiges Objektrecherche-Fenster ist.
// @rdesc Liefert einen <t BOOL> -Wert, der Auskunft darüber gibt, ob das Fenster
// ein gültiges Objektrecherch-fenster ist.
// @parm HWND | hORWnd | Handle des zu untersuchenden fensters
// @xref <m DEX_ISOBJWINDOW>
#define DEX_IsORWindow(hWnd)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_ISOBJWINDOW,(LPARAM)(void *)hWnd)

// @func DWORD | DEX_QueryMode | Liefert den Wert des System-Administrationsflags.
// @rdesc Liefert einen <t BOOL> -Wert, der Auskunft darüber gibt, ob der
// aktuelle Nutzer über erweiterte Zugriffsrechte verfügt oder nicht.
// @xref <m DEX_QUERYADMINMODE>
#define DEX_QueryMode() 	\
	(DWORD)DexExtensionProc((WPARAM)DEX_QUERYADMINMODE,0)

// @func BOOL | DEX_SetMode | Setzt den Wert des System-Administrationsflags 
// für den aktuelle Nutzer.
// @parm BOOL | fAdminFlag | Enthält den neuen Wert, der dem SystemAdminFlag des
// aktuellen Nutzers zugewiesen werden soll.
// @rdesc Liefert einen <t BOOL> -Wert, der Auskunft darüber gibt, ob der
// aktuelle Nutzer über erweiterte Zugriffsrechte verfügt hatte oder nicht.
// @xref <m DEX_SETADMINMODE>
#define DEX_SetMode(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_SETADMINMODE,(LPARAM)(l))

#define DEX_SetDirtyGeoDB(l)	\
	DexExtensionProc2(HACTPROJECT,(WPARAM)DEX_SETGEODBDIRTY,(LPARAM)l)
#define DEX_SetDirtyGeoDBEx(hPr,l)	\
	DexExtensionProc2(hPr,(WPARAM)DEX_SETGEODBDIRTY,(LPARAM)l)
#define DEX_IsGeoDBDirty()		\
	(BOOL)DexExtensionProc2(HACTPROJECT,(WPARAM)DEX_GETGEODBDIRTY,0L)
#define DEX_IsGeoDBDirtyEx(hPr)	\
	(BOOL)DexExtensionProc2(hPr,(WPARAM)DEX_GETGEODBDIRTY,0L)

#define DEX_EnumORWindows(l)	\
	DexExtensionProc((WPARAM)DEX_ENUMOBJRECHWNDS,(LPARAM)&(l))

// SichtContainer (Begrenzungen) festlegen und abfragen
#define DEX_GetActViewContainer(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYACTVIEWCONTAINER,(LPARAM)(l))
#define DEX_SetActViewContainer(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_MODACTVIEWCONTAINER,(LPARAM)(l))

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
#define DEX_SaveOtherStorage(pIStg) \
	(HRESULT)DexExtensionProc((WPARAM)DEX_N_SAVEOTHERSTORAGE,(LPARAM)(pIStg))
#define DEX_SaveCompleted(pIStg)	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_N_SAVECOMPLETED,(LPARAM)(pIStg))
#define DEX_HandsOffStorage(pIStg)	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_N_HANDSOFFSTORAGE,(LPARAM)0L)

#define DEX_AttachPreTranslateMsgProc(l)	\
	(BOOL (*)(MSG *))DexExtensionProc((WPARAM)DEX_ATTACHPRETRANSLATEMSGPROC,(LPARAM)(l))
#define DEX_DetachPreTranslateMsgProc() 	\
	(BOOL (*)(MSG *))DexExtensionProc((WPARAM)DEX_ATTACHPRETRANSLATEMSGPROC,(LPARAM)NULL)
#define DEX_AttachIdleProc(l)		\
	(BOOL (*)(LONG))DexExtensionProc((WPARAM)DEX_ATTACHIDLEPROC,(LPARAM)(l))
#define DEX_DetachIdleProc()		\
	(BOOL (*)(LONG))DexExtensionProc((WPARAM)DEX_ATTACHIDLEPROC,(LPARAM)NULL)

#define DEX_GetActiveViewWindow()	\
	(HWND)DexExtensionProc((WPARAM)DEX_QUERYACTIVEVIEWWINDOW,(LPARAM)0)

#define DEX_GetObjectProps(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYOBJECTPROPS,(LPARAM)(l))

#define DEX_SetMessageString(l) \
	(BOOL)DexExtensionProc((WPARAM)DEX_SETSTRINGMESSAGE,(LPARAM)(l))
#define DEX_SetMessageStringNoKickIdle(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_SETSTRINGMESSAGENOKICKIDLE,(LPARAM)(l))
#define DEX_UpdateStatusBar(l)	\
	DexExtensionProc((WPARAM)DEX_UPDATESTATUSBAR,(LPARAM)l)

#define DEX_CTFCanConfig()		\
	(BOOL)DexExtensionProc((WPARAM)DEX_CANCTFCONFIG,(LPARAM)0)

#define DEX_KickIdle()			\
	DexExtensionProc((WPARAM)DEX_KICKIDLELOOP,(LPARAM)0)
#define DEX_DoEventsWithIdle()			\
	DexExtensionProc((WPARAM)DEX_KICKIDLELOOP,(LPARAM)1)
#define DEX_ViewCanvasErase()	\
	DexExtensionProc((WPARAM)DEX_ERASEVIEWCANVAS,(LPARAM)0)

///////////////////////////////////////////////////////////////////////////////
// Statistikwerte abfragen
#define DEX_GetObjectCount()	\
	(long)DexExtensionProc((WPARAM)DEX_QUERYOBJECTCOUNT,(LPARAM)0)
#define DEX_GetIdentObjectCount(l)	\
	(long)DexExtensionProc((WPARAM)DEX_QUERYIDENTOBJECTCOUNT,(LPARAM)&(l))
#define DEXOR_GetIdentObjectCount(hWnd,l)	\
	(long)DexORExtensionProc(hWnd,(WPARAM)DEX_QUERYIDENTOBJECTCOUNT,(LPARAM)&(l))
#define DEX_GetClassCount() 	\
	(long)DexExtensionProc((WPARAM)DEX_QUERYCLASSCOUNT,(LPARAM)0)
#define DEX_GetViewCount()		\
	(long)DexExtensionProc((WPARAM)DEX_QUERYVIEWCOUNT,(LPARAM)0)

///////////////////////////////////////////////////////////////////////////////
// HoldZoomStatus
#define DEX_SetHoldZoom(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_HOLDZOOMSET,(LPARAM)l)
#define DEX_IsHoldZoomActive()		\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYHOLDZOOM,(LPARAM)0)

///////////////////////////////////////////////////////////////////////////////
// Ident <--> ObjektklassenSchlüssel
#define DEX_GetIdentFromClass(l)	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_IDENTFROMCLASS,(LPARAM)&(l))
#define DEX_GetClassFromIdent(l)	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_CLASSFROMIDENT,(LPARAM)&(l))
#define DEX_ModObjectClassCode(l)	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_MODOBJCLASSCODE,(LPARAM)&(l))

#define DEX_GetIdentFromClassEx(hPr,l)	\
	(HRESULT)DexExtensionProc2(hPr,(WPARAM)DEX_IDENTFROMCLASS,(LPARAM)&(l))
#define DEX_GetClassFromIdentEx(hPr,l)	\
	(HRESULT)DexExtensionProc2(hPr,(WPARAM)DEX_CLASSFROMIDENT,(LPARAM)&(l))
#define DEX_ModObjectClassCodeEx(hPr,l)	\
	(HRESULT)DexExtensionProc2(hPr,(WPARAM)DEX_MODOBJCLASSCODE,(LPARAM)&(l))

#define DEX_EnumClassProjects(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMPROJECTSFORCLASS,(LPARAM)&(l))

///////////////////////////////////////////////////////////////////////////////
// Im Recherchefenster angezeigte Objekteigenschaft (global)
#define DEX_SetActObjPropName(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_SHOWOBJPROP,(LPARAM)l)
#define DEX_GetActObjPropName(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_GETSHOWOBJPROP,(LPARAM)l)
#define DEX_GetActObjProp(l)	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_QUERYACTOBJPROP,(LPARAM)l)

///////////////////////////////////////////////////////////////////////////////
// Im Recherchefenster angezeigte Objekteigenschaft (sichtbezogen)
#define DEX_SetActObjPropEx(l)	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_SHOWOBJPROPEX,(LPARAM)&(l))
#define DEX_GetActObjPropEx(l)	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_QUERYOBJPROPEX,(LPARAM)&(l))

#define DEX_GetTRiASVersion(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYTRIASVERSION,(LPARAM)l)
#define DEX_GetTRiASVersionLong()	\
	DexExtensionProc((WPARAM)DEX_QUERYTRIASVERSIONLONG,0)

#define DEX_GetTRiASCaption(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYTRIASCAPTION,(LPARAM)l)
#define DEX_SetTRiASCaption(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_MODIFYTRIASCAPTION,(LPARAM)l)

#define DEX_GetIdentPriority(l) \
	(HRESULT)DexExtensionProc((WPARAM)DEX_QUERYIDENTPRIORITY,(LPARAM)&(l))
#define DEX_SetIdentPriority(l) \
	(HRESULT)DexExtensionProc((WPARAM)DEX_MODIFYIDENTPRIORITY,(LPARAM)&(l))

///////////////////////////////////////////////////////////////////////////////
// Objekte visuell selektieren/deselektieren
#define DEX_SelectObject(l) \
	(BOOL)DexExtensionProc((WPARAM)DEX_OBJECTSELECTED,(LPARAM)&(l))
#define DEX_UnselectObject(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_OBJECTUNSELECTED,(LPARAM)(l))

///////////////////////////////////////////////////////////////////////////////
// Overview
#define DEX_IsOverviewActive()	\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYOVERVIEWACTIVE,0L)
#define DEX_SaveOverview()	\
	DexExtensionProc((WPARAM)DEX_OVERVIEWSAVE,0L)
#define DEX_MayOpenOverview() \
	(BOOL)DexExtensionProc((WPARAM)WM_QUERYMAYOPENOVERVIEW,0L)

///////////////////////////////////////////////////////////////////////////////
// Testet 16Bit kompatibilitätsmode des Projektes
#define DEX_Is16BitCompatible() \
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYCOMPATIBILITYMODE,0L)

///////////////////////////////////////////////////////////////////////////////
// Verwaltung von ObjectGuids
#define DEX_GetObjectGuid(l)	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_QUERYOBJECTGUID,(LPARAM)&(l))
#define DEX_FindObjectFromGuid(l)	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_FINDOBJECTGUID,(LPARAM)&(l))
#define DEX_FindObjectFromGuidEx(hPr,l)	\
	(HRESULT)DexExtensionProc2(hPr,(WPARAM)DEX_FINDOBJECTGUID,(LPARAM)&(l))
#define DEX_SetObjectGuid(l)	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_SETOBJECTGUID,(LPARAM)&(l))

///////////////////////////////////////////////////////////////////////////////
// Verwaltung der AnfangsAnsicht
#define DEX_GetDefaultView(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYSTARTVIEW,(LPARAM)(l))
#define DEX_SetDefaultView(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_MODIFYSTARTVIEW,(LPARAM)(l))

///////////////////////////////////////////////////////////////////////////////
// Verwaltung der MRUItems
#define DEX_GetMRUItem(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYMRUITEM,(LPARAM)&(l))
#define DEX_RemoveMRUItem(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_DELETEMRUITEM,(LPARAM)&(l))
#define DEX_NewMRUItem(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_ADDMRUITEM,(LPARAM)&(l))

///////////////////////////////////////////////////////////////////////////////
// Verwaltung maßstabsbezognenes Ein/Ausblenden
#define DEX_GetIdentScaleData(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYIDENTSCALEDATA,(LPARAM)&(l))
#define DEX_SetIdentScaleData(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_MODIFYIDENTSCALEDATA,(LPARAM)&(l))
#define DEX_PaintIdentScaleData(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_TESTIDENTSCALETOPAINT,(LPARAM)&(l))

#define DEX_SetMustInitOPFs(l)	\
	DexExtensionProc((WPARAM)DEX_SETHAVETOINITOPFS,(LPARAM)l)
#define DEX_MustInitOPFs()		\
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYMUSTINITOPFS,0L)

///////////////////////////////////////////////////////////////////////////////
// NamedProperties
#define DEX_GetNamedViewProperty(l) \
	(HRESULT)DexExtensionProc((WPARAM)DEX_QUERYNAMEDVIEWPROPERTY,(LPARAM)&(l))
#define DEX_SetNamedViewProperty(l) \
	(HRESULT)DexExtensionProc((WPARAM)DEX_MODNAMEDVIEWPROPERTY,(LPARAM)&(l))

// Datenquellen-Handle von einem Objekthandle feststellen
#define DEX_GetObjectProject(l)	\
	(HPROJECT)DexExtensionProc((WPARAM)DEX_QUERYOBJECTPROJECT,(LPARAM)l)
// Datenquellen-Handle von einem Objektklassenhandle feststellen
#define DEX_GetObjectsProject(l) \
	(HPROJECT)DexExtensionProc((WPARAM)DEX_QUERYOBJECTSPROJECT,(LPARAM)l)
// Datenquellen-Handle von einer Objekteigenschaft feststellen (wenn möglich, sonst HACTCONNECTION)
#define DEX_GetFeatureProject(l) \
	(HPROJECT)DexExtensionProc((WPARAM)DEX_QUERYFEATUREPROJECT,(LPARAM)l)

///////////////////////////////////////////////////////////////////////////////
// anzuzeigende Koordinaten durchrufen
#define DEX_SetShownCoords(x,y)	\
	DexExtensionProc((WPARAM)DEX_MODIFYSHOWNCOORDS,(LPARAM)MAKELONG((x),(y)))

///////////////////////////////////////////////////////////////////////////////
// Anzahl der aktuell geöffneten Connections liefern
#define DEX_GetOpenConnectionCount(l)	\
	(ULONG)DexExtensionProc((WPARAM)DEX_QUERYDATASOURCECOUNT,(LPARAM)l)

///////////////////////////////////////////////////////////////////////////////
// NeuBeschreibungsdaten für neue Objects-Menge definieren
#define DEX_DefineNewObjectsDesc(l)	\
	(ULONG)DexExtensionProc((WPARAM)DEX_DEFINENEWOBJECTS,(LPARAM)&(l))

///////////////////////////////////////////////////////////////////////////////
// Das Feature-Handle für einen MCode liefern und v.v.
#define DEX_MapMCodeToHandle(hPr,l)	\
	(INT_PTR)DexExtensionProc2(hPr,(WPARAM)DEX_GETHANDLEFROMMCODE,(LPARAM)(l))
#define DEX_MapOrCreateMCodeToHandle(hPr,l)	\
	(BOOL)DexExtensionProc2(hPr,(WPARAM)DEX_MAPORCREATEHANDLEFROMMCODE,(LPARAM)&(l))
#define DEX_MapHandleToMCode(l)		\
	(INT_PTR)DexExtensionProc((WPARAM)DEX_GETMCODEFROMHANDLE,(LPARAM)(l))

///////////////////////////////////////////////////////////////////////////////
// aktuellen DatenquellenKontext einer Message abfragen
#define DEX_GetContextDataSource()	\
	(HPROJECT)DexExtensionProc((WPARAM)DEX_QUERYCONTEXTPROJECT,0L)

#endif // WIN16

///////////////////////////////////////////////////////////////////////////////
// Objekt aus Speicher entladen
#define DEX_UnloadObject(l)	\
	(BOOL)DexExtensionProc((WPARAM)DEX_UNLOADOBJECTFROMMEMORY,(LPARAM)(l))

///////////////////////////////////////////////////////////////////////////////
// Importmode ein/ausschalten
#define DEX_ImportMode(l) \
	(BOOL)DexExtensionProc((WPARAM)DEX_CHANGEIMPORTMODE,(LPARAM)(l))
#define DEX_NotificationMode(l) \
	(BOOL)DexExtensionProc((WPARAM)DEX_CHANGENOTIFICATIONMODE,(LPARAM)(l))
#define DEX_ChangeMRUMode(l) \
	(BOOL)DexExtensionProc((WPARAM)DEX_MRUMENUMODE,(LPARAM)(l))

///////////////////////////////////////////////////////////////////////////////
// Ursprünglicher Datenquellenname einer Ansicht
#define DEX_GetRelatedDataSourceName(l)	\
	(HRESULT)DexExtensionProc((WPARAM)DEX_RELATEDDATASOURCENAME,(LPARAM)&(l))

///////////////////////////////////////////////////////////////////////////////
// Liefert Ident, zu dem ein MCode gehört (für <tr> -Datenquelle wird immer 
// NULL geliefert - 'alle' Idents)
#define DEX_GetFeatureIdent(l) \
	(INT_PTR)DexExtensionProc((WPARAM)DEX_QUERYFEATUREIDENT, (LPARAM)(l))

///////////////////////////////////////////////////////////////////////////////
// Printersupport
#define DEX_UpdatePrinterSelection(l) \
	DexExtensionProc((WPARAM)DEX_UPDATEPRINTERSELECTION, (LPARAM)&(l))
#define DEX_ShowPrintLayoutDlg(l) \
	DexExtensionProc((WPARAM)DEX_SHOWPRINTLAYOUTDIALOG, (LPARAM)&(l))
#define DEX_PrintPreview(l) \
	DexExtensionProc((WPARAM)DEX_PREVIEWPRINT, (LPARAM)&(l))
#define DEX_EndPrintPreview(l) \
	DexExtensionProc((WPARAM)DEX_ENDPREVIEWPRINT, (LPARAM)&(l))

///////////////////////////////////////////////////////////////////////////////
// StartupDialog anzeigen (PostNotification)
#define DEX_ShowStartupDialog()		\
	(BOOL)DexPostNotificationProc((WPARAM)DEX_SHOWSTARTUPDIALOG, (LPARAM)0)

///////////////////////////////////////////////////////////////////////////////
// Objekt doppeln (evtl. in andere Datenquelle)
#define DEX_CloneObject(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_CLONEOBJECT, (LPARAM)&(l))
#define DEX_CloneObjectEx(hPr,l)		\
	(BOOL)DexExtensionProc2(hPr,(WPARAM)DEX_CLONEOBJECT, (LPARAM)&(l))

///////////////////////////////////////////////////////////////////////////////
// FaltStatus für ORWnds festlegen/abfragen
#define DEXOR_ToggleRollUp(hWnd, l)		\
	(BOOL)DexORExtensionProc(hWnd,(WPARAM)DEX_TOGGLEROLLUPSTATUS, (LPARAM)(l))
#define DEXOR_IsRolledUp(hWnd)		\
	(BOOL)DexORExtensionProc(hWnd,(WPARAM)DEX_QUERYROLLUPSTATUS, (LPARAM)0)

///////////////////////////////////////////////////////////////////////////////
// Lizensierung
#define DEX_VerifyLicenseLevel(l) \
	(BOOL)DexExtensionProc((WPARAM)DEX_VERIFYLICLEVEL,(LPARAM)&(l))
#define DEX_VerifyLicenseOption(l) \
	(BOOL)DexExtensionProc((WPARAM)DEX_VERIFYLICOPTION,(LPARAM)&(l))
#define DEX_ShowLicenseDenyDialog(l) \
	DexExtensionProc((WPARAM)DEX_SHOWDENYLICDLG,(LPARAM)&(l))
	
///////////////////////////////////////////////////////////////////////////////
// Objekt zeigen (Ausschnitt sinnvol auf Objekt einstellen)
#define DEX_ZoomInToObject(l) \
	(BOOL)DexExtensionProc((WPARAM)DEX_ZOOMIN2OBJECT,(LPARAM)(l))

///////////////////////////////////////////////////////////////////////////////
// aktuellen Objektbeschreibungs-String liefern (wie im Recherchefenster)
// gelieferten Wert mit CoTaskMemFree freigeben!
#define DEX_GetObjectDescriptionString(l) \
	(LPCSTR)DexExtensionProc((WPARAM)DEX_QUERYOBJECTDESCSTRING,(LPARAM)(l))

///////////////////////////////////////////////////////////////////////////////
// ProjectBar/OverViewBar Status Abfrage
#define DEX_IsProjectBarVisible(l) \
	(void)DexExtensionProc((WPARAM)WM_QUERYPROJECTBARACTIVE,(LPARAM)&(l))
#define DEX_IsOverViewBarVisible(l) \
	(void)DexExtensionProc((WPARAM)WM_QUERYOVERVIEWBARACTIVE,(LPARAM)&(l))
#define DEX_IsSABiSBarVisible(l) \
	(void)DexExtensionProc((WPARAM)WM_QUERYSABiSBARACTIVE,(LPARAM)&(l))
#define DEX_IsGenericBarVisible(l) \
	(void)DexExtensionProc((WPARAM)WM_QUERYGENERICBARACTIVE,(LPARAM)&(l))

///////////////////////////////////////////////////////////////////////////////
// Recherchen auf aktuellen Bildausschnitt begrenzen
#define DEX_GetLimitSearches() \
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYLIMITSEARCHES,(LPARAM)0)
#define DEX_SetLimitSearches(l) \
	(BOOL)DexExtensionProc((WPARAM)DEX_SETLIMITSEARCHES,(LPARAM)l)

///////////////////////////////////////////////////////////////////////////////
// Recherche-Einschränkungen (0bjektklassenbezogen) ignorieren
#define DEX_GetIgnoreSearchOptions() \
	(BOOL)DexExtensionProc((WPARAM)DEX_QUERYIGNORESEARCHOPTIONS,(LPARAM)0)
#define DEX_SetIgnoreSearchOptions(l) \
	(BOOL)DexExtensionProc((WPARAM)DEX_SETIGNORESEARCHOPTIONS,(LPARAM)l)

///////////////////////////////////////////////////////////////////////////////
// Blinkfarbe in ORWnds beeinflussen/abfragen
#define DEXOR_GetMarkColor(hWnd)		\
	(long)DexORExtensionProc(hWnd,(WPARAM)WM_QUERYMARKCOLOR,(LPARAM)0)
#define DEXOR_SetMarkColor(hWnd,l)		\
	(long)DexORExtensionProc(hWnd,(WPARAM)WM_CHANGEMARKCOLOR,(LPARAM)(l))

///////////////////////////////////////////////////////////////////////////////
// Quell-Recherchefenster der aktuellen Drag&Drop OPeration liefern
#define DEX_GetDropSourceORWnd() \
	(HWND)DexExtensionProc((WPARAM)WM_QUERYDROPSOURCEORWND,(LPARAM)0)

///////////////////////////////////////////////////////////////////////////////
// COM Interface zu einem Handle liefern
#define DEX_GetObjectPtr(l)		\
	(HRESULT)DexExtensionProc((WPARAM)DEX_QUERYOBJECTPTR,(LPARAM)&(l))
#define DEX_GetObjectsPtr(l)		\
	(HRESULT)DexExtensionProc((WPARAM)DEX_QUERYOBJECTSPTR,(LPARAM)&(l))
#define DEX_GetFeaturePtr(l)		\
	(HRESULT)DexExtensionProc((WPARAM)DEX_QUERYFEATUREPTR,(LPARAM)&(l))

///////////////////////////////////////////////////////////////////////////////
// Connectionfilter
#define DEX_CreateConnectionFilter(l)		\
	(HRESULT)DexExtensionProc((WPARAM)DEX_CREATECONNECTIONFILTER,(LPARAM)&(l))
#define DEX_DeleteConnectionFilter(l)		\
	(HRESULT)DexExtensionProc((WPARAM)DEX_DELETECONNECTIONFILTER,(LPARAM)&(l))
#define DEX_GetConnectionFilter(l)		\
	(HRESULT)DexExtensionProc((WPARAM)DEX_QUERYCONNECTIONFILTER,(LPARAM)&(l))
#define DEX_EnumConnectionFilters(l)		\
	(BOOL)DexExtensionProc((WPARAM)DEX_ENUMCONNECTIONFILTERS,(LPARAM)&(l))
#define DEX_AttachConnectionFilter(l)		\
	(HRESULT)DexExtensionProc((WPARAM)DEX_ATTACHCONNECTIONFILTER,(LPARAM)&(l))
#define DEX_DetachConnectionFilter(l)		\
	(HRESULT)DexExtensionProc((WPARAM)DEX_DETACHCONNECTIONFILTER,(LPARAM)&(l))
#define DEX_GetAttachedConnectionFilter(l)		\
	(HRESULT)DexExtensionProc((WPARAM)DEX_QUERYATTACHEDCONNECTIONFILTER,(LPARAM)&(l))
#define DEX_ShowCreateConnectionFilterDlg(l) \
	(int)DexExtensionProc((WPARAM)DEX_CREATECONNECTIONFILTER_DLG,(LPARAM)&(l))

#define DEX_ShowConnectionFilters(l) \
	(BOOL)DexExtensionProc((WPARAM)DEX_SHOWCONNECTFILTERS,(LPARAM)(l))
#define DEX_ConnectionFiltersShown(l) \
	(BOOL)DexExtensionProc((WPARAM)DEX_CONNECTFILTERSSHOWN,(LPARAM)&(l))

//////////////////////////////////////////////////////////////////////////////
// Ladbaren Befehl ausführen
#define DEX_ExecuteSequence() \
	(BOOL)DexExtensionProc((WPARAM)DEX_EXECUTECOMMANDSEQUENCE,0)
#define DEXOR_ExecuteSequence(hWnd) \
	(BOOL)DexORExtensionProc(hWnd,(WPARAM)DEX_EXECUTECOMMANDSEQUENCE,0)

#include <poppack.h>

#endif // _XTENSNX_H
