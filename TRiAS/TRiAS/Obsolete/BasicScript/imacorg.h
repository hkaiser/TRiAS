// Costuminterfaces fuer Kommandoobjektverwaltung
// File: IMACORG.H

#if !defined(_IMACORG_H)
#define _IMACORG_H

#include <ospace/header.h>

#undef  INTERFACE
#define INTERFACE   ITriasMenuExt

// 0796384D-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ITriasMenuExt, 0x0796384DL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(ITriasMenuExt, IUnknown)
{
    // *** IUnknown methods ***
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID * ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    STDMETHOD(QueryContextMenu)(THIS_
                                HMENU hmenu,
                                UINT indexMenu,
                                UINT idCmdFirst,
                                UINT idCmdLast,
                                UINT uFlags) PURE;

    STDMETHOD(InvokeCommand)(THIS_
                             LPCMINVOKECOMMANDINFO lpici) PURE;

    STDMETHOD(GetCommandString)(THIS_
                                UINT        idCmd,
                                UINT        uType,
                                UINT      * pwReserved,
                                LPSTR       pszName,
                                UINT        cchMax) PURE;
};

typedef ITriasMenuExt* LPTRIASMENUEXT;

#undef INTERFACE
#define INTERFACE ICommand
                
// 07963844-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ICommand, 0x07963844L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(ICommand, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;
// *** Command methods
	STDMETHOD (InitCommand) (THIS_) PURE;
	STDMETHOD (FireEvent) (THIS_ UINT uiID) PURE;
	STDMETHOD (GetDescription) (THIS_ LPSTR, UINT, bool &fMacro) PURE;	

};
typedef ICommand* LPCOMMAND;

DefineSmartInterface(Command);

#undef INTERFACE
#define INTERFACE IProcess
                
// 07963842-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IProcess, 0x07963842L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IProcess, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** Command methods
	STDMETHOD (MenuSelect) (THIS_) PURE;
	STDMETHOD (MenuInit) (THIS_) PURE;
	STDMETHOD (MenuCommand) (THIS_ UINT uiID) PURE;	
// *** Notification methods
	STDMETHOD (Notification) (THIS_) PURE;	
	STDMETHOD (WindowsNotification) (THIS_) PURE;	
};
typedef IProcess* LPPROCESS;

DefineSmartInterface(Process);

#undef INTERFACE
#define INTERFACE IAnalyse
                
// 07963841-3123-101C-BB62-00AA0018497C
// DEFINE_GUID(IID_IAnalyse, 0x07963841L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IAnalyse, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IAnalyse methods ***	
	STDMETHOD (GetMenuStructure) (THIS_ HMENU hMenu) PURE;
};
typedef IAnalyse* LPANALYSE;

DefineSmartInterface(Analyse);

#undef INTERFACE
#define INTERFACE IAnpassen
                
// 07963845-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IAnpassen, 0x07963845L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IAnpassen, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IAnalyse methods ***	
	STDMETHOD (ReadMenu) (CWnd *pTC) PURE;
	STDMETHOD(SetNewMenu)(	UINT uiPreID, 
							UINT uiSucID, 
							UINT &uiNewID,
							LPCSTR pNew, 
							LPCSTR pNewMenuEntry,
							bool fMacro) PURE;
	STDMETHOD (SetNewMenuEntry) (	UINT uiID, 
									LPCSTR pNew) PURE;
	STDMETHOD (GetDescription) (LPSTR pc, UINT uiLen,
								UINT uiMenuID, bool &fMacro) PURE;
	STDMETHOD (DeleteItem) (UINT uiID) PURE;
	STDMETHOD_(void, GetNewMacroID)(UINT *puiID) PURE;
	STDMETHOD_(void, SetNewMacroID)(UINT uiID) PURE;
};
typedef IAnpassen* LPANPASSEN;

DefineSmartInterface(Anpassen);

#undef INTERFACE
#define INTERFACE IListElement

struct IListElement;
DefineSmartInterface(ListElement);

// 07963846-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IEnumWListElement, 0x07963846L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DefineEnumerator(WListElement);
DefineSmartEnumerator(WListElement);

// 07963840-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IListElement, 0x07963840L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IListElement, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;
// *** Command methods
	STDMETHOD (Insert) (THIS_	IListElement *pILstEl, 
								IListElement *pILstEl_After) PURE;
	STDMETHOD (Insert) (THIS_ LPCSTR strMenuName, UINT uiID) PURE;
	STDMETHOD (Get) (THIS_ LPSTR strMenuName, int iLen, UINT *puiID) PURE;
	STDMETHOD (GetEnum) (THIS_ IEnum<WListElement> ** ppIEn) PURE;
	STDMETHOD (SetMenu) (HMENU hMenu) PURE;
	STDMETHOD (GetMenu) (HMENU *phMenu) PURE;
	STDMETHOD (ClearItem) (IListElement *pILE) PURE;
};
typedef IListElement* LPLISTELEMENT;

#undef INTERFACE
#define INTERFACE ISave

// 0796384B-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ISave, 0x0796384BL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(ISave, IPersistStorage)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** ISave methods ***	
	STDMETHOD (SaveFile) (THIS) PURE;
	STDMETHOD (LoadFile) (THIS) PURE;
	STDMETHOD (InsertMenu)(HMENU hMenu) PURE;
	STDMETHOD (SaveToStorage) (bool fClearDirty) PURE;
	STDMETHOD (LoadFromStorage) (void) PURE;
	STDMETHOD (DestroyStorage) (int IDS) PURE;

// *** IPersistStorage methods 
	STDMETHOD (GetClassID) (LPCLSID pClsID) PURE;
	STDMETHOD (IsDirty) (void) PURE;
    STDMETHOD (InitNew) (LPSTORAGE) PURE;
	STDMETHOD (Load)(LPSTORAGE) PURE;
	STDMETHOD (Save) (LPSTORAGE, BOOL) PURE;
	STDMETHOD (SaveCompleted) (LPSTORAGE) PURE;
	STDMETHOD (HandsOffStorage) (void) PURE;

};
typedef ISave* LPSAVE;

DefineSmartInterface(Save);

#undef INTERFACE
#define INTERFACE ICommands

// 07963843-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_ICommands, 0x07963843L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(ICommands, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** ICommands methods ***
/*	STDMETHOD (GetMenuItems) (THIS_ HMENU) PURE;	
	STDMETHOD (GetEnum) (THIS_ IEnum<WListElement> ** ppIEn) PURE;
	STDMETHOD (InsertMenuItem) (LPCSTR cMenuEntry, 
								UINT uiMenuID, 
								IListElement *pILstEl_ListItem_Up,
								IListElement *pILE_After) PURE;
	STDMETHOD (InsertCommand) (	LPCSTR pcMacroName, 
								UINT uiMenuID, bool fMacro) PURE;
	STDMETHOD (GetDescription) (LPSTR pc, UINT uiLen,
								UINT uiMenuID, 
								bool &fMacro) PURE;
	STDMETHOD (FireEvent) (UINT uiMenuID) PURE;
	STDMETHOD (DeleteItem) (UINT uiID,
							IListElement *pILstEl_Up,
							IListElement *pILE) PURE;
	STDMETHOD (SaveFile) (THIS) PURE;
	STDMETHOD (LoadFile) (THIS) PURE;
	STDMETHOD (InsertMenu)(THIS_ HMENU hMenu, LPCSTR pcExtMenuEntry) PURE;
*/
 };
typedef ICommands* LPCOMMANDS;

DefineSmartInterface(Commands);

// 0796384A-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IPersistBStream, 0x0796384AL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IPersistBStream, IPersist)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;
// *** Command methods
	STDMETHOD (GetClassID) (THIS_ CLSID *pClassID) PURE;	
	STDMETHOD (Load) (THIS_ os_bstream *stream) PURE;
	STDMETHOD (Save) (THIS_ os_bstream *stream) PURE;
};
typedef IPersistBStream* LPPERSISTBSTREAM;

DefineSmartInterface(PersistBStream);
DefineSmartInterface(PersistStream);

#endif // _IMACORG_H



