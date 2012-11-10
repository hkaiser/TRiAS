// File: ISCRPROP.H

#ifndef _ISCRPROP_H
#define _ISCRPROP_H

#if _MSC_VER < 1100 && !defined(DECLSPEC_UUID)
#define DECLSPEC_UUID(x)
#endif // _MSC_VER < 1100 && !defined(DECLSPEC_UUID)

#undef INTERFACE
#define INTERFACE IScriptProperty
                
// zum Abspeichern des Scriptes
struct IObjectManagement;
typedef struct tagebSaveStruct {
	ebHCODE hCode;
	LPSTR pText;
	DWORD dwSaveFlag;
	LPSTR *lplpstrRelScripts;
	UINT  uiCntRelScripts;
} ebSaveStruct;
typedef ebSaveStruct* LPSAVESTRUCT;

// 079638A0-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IScriptProperty, 0x079638A0L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
interface DECLSPEC_UUID("079638A0-3123-101C-BB62-00AA0018497C")
IScriptProperty : public IUnknown
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IScriptProperty methods
	STDMETHOD(Set)(LPSAVESTRUCT pStruct) PURE;
	STDMETHOD(Get)(LPSAVESTRUCT pStruct) PURE;
};

// 079638A1-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IStreamInfo, 0x079638A1L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
interface DECLSPEC_UUID("079638A1-3123-101C-BB62-00AA0018497C")
IStreamInfo : public IUnknown
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IStreamInfo methods
	STDMETHOD(Set)(BSTR bstr, DWORD) PURE;
	STDMETHOD(Get)(BSTR bstr, DWORD*) PURE;
	STDMETHOD(Rename)(BSTR bstr, BSTR bstrNew) PURE;
	STDMETHOD_(UINT,Count)() PURE;
	STDMETHOD_(UINT,GetManID)() PURE;
	STDMETHOD_(void,SetManID)(UINT) PURE;
};

#define MANID_GENERAL 1
#define MANID_OBJFEAT 2
#define MANID_FILTER  3

//DEFINE_GUID(IID_IAddScriptProperty, 0x079638ACL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
interface DECLSPEC_UUID("079638AC-3123-101C-BB62-00AA0018497C")
IAddScriptProperty : public IUnknown
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IAddScriptProperty methods ***
	STDMETHOD(SetName)	(LPCSTR) PURE;
	STDMETHOD(GetName)	(LPSTR, UINT) PURE;
	STDMETHOD(SetCooky)	(DWORD dwID) PURE;
	STDMETHOD(GetCooky)	(DWORD *pdwID) PURE;
	STDMETHOD(Install)	(void) PURE;
	STDMETHOD(Uninstall)(void) PURE;
};

interface DECLSPEC_UUID("e8281060-cadc-11d0-9e56-0020AF3712c3")
IRunningObject : public IUnknown
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IRunningScript methods
	STDMETHOD(LinkScript)		(void) PURE;
	STDMETHOD(CanAddString)		(void) PURE;
	STDMETHOD(RunEntry)			(LPCSTR pEntry, int iNumParams, BSPARAM *pPars, BOOL fBreak, INT_PTR hPrCtx, INT_PTR hInst) PURE;
	STDMETHOD(CreateScript)		(CebInstance *pInst, ebHCODE hCode) PURE;
	STDMETHOD(RunScript)		(void) PURE;
	STDMETHOD(EndThreads)		(void) PURE;
	STDMETHOD(EnumEntries)		(LPSTR lpstr, UINT uiLen, ebBOOL *pfNext) PURE;
	STDMETHOD(SetAutoStart)		(DWORD) PURE;
	STDMETHOD(GetAutoStart)		(DWORD *) PURE;
	STDMETHOD(SetExtension)		(BOOL) PURE;
	STDMETHOD(IsExtension)		(void)  PURE;
	STDMETHOD_(void, SetManagement)	(IObjectManagement*, IStreamInfo*, REFIID riid, LPCSTR) PURE;
};

interface DECLSPEC_UUID("e8281061-cadc-11d0-9e56-0020AF3712c3")
IObjManHelper : public IUnknown
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IObjManHelper-Methods ***
	STDMETHOD(Open) (LPSTR *, ebHCODE *, LPSTR **, UINT &, BOOL fTemp = false)  PURE;
	STDMETHOD(Import)(REFIID riid, LPCSTR, LPSTR *, ebHCODE *, LPSTR **, UINT &)   PURE;
	STDMETHOD(New)	(LPSTR *ppcMacroText)   PURE;
	STDMETHOD(Save) (LPSTR pText, ebHCODE hCode, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag)  PURE;
	STDMETHOD(SaveAs) (LPCSTR, LPSTR pText, ebHCODE hCode, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag)  PURE;
	STDMETHOD(Delete) (void)  PURE;
	STDMETHOD(Rename) (LPCSTR lpcstrNewName)  PURE;
	STDMETHOD(NewFunction) (LPCSTR lpcstrName, LPCSTR lpcstrDecl, LPCSTR lpcstrType, LPCSTR lpcstrParams, LPCSTR lpcstrComment, LPSTR *lplpstr) PURE;

	STDMETHOD(GetSaveAsFilters)	(LPSTR *)  PURE;
	STDMETHOD(GetFileExt)		(LPSTR *)  PURE;

	STDMETHOD_(void, SetInitNew)		(BOOL) PURE;
	STDMETHOD_(BOOL, GetInitNew)		(void) PURE;
	STDMETHOD_(void, SetDirty)			(BOOL fDirty) PURE;
	STDMETHOD_(BOOL, GetDirty)			(void) PURE;
	STDMETHOD_(void, SetEditOnly)		(BOOL) PURE;
	STDMETHOD_(BOOL, GetEditOnly)		(void) PURE;
	STDMETHOD(GetParentName)			(LPSTR, UINT) PURE;
	STDMETHOD(SetParentName)			(LPCSTR) PURE;
};

interface DECLSPEC_UUID("079638A3-3123-101C-BB62-00AA0018497C")
ITreeItem : public IUnknown
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;
	//  *** ITreeItem-Methods ***
	STDMETHOD_(BOOL, IsLabelEdit)		(void) PURE;
	STDMETHOD_(void, SetLabelEdit)		(BOOL) PURE;
	STDMETHOD_(BOOL, IsJustInsert)		(void)  PURE;
	STDMETHOD_(void, SetJustInsert)		(BOOL) PURE;
	STDMETHOD_(int,	AskSaveChanges)		(HWND, LPCSTR)  PURE;
	STDMETHOD_(void, GetInitCaretPos)	(int &, int &, int &)  PURE;
	STDMETHOD_(BOOL, IsSuperItem)		(void) PURE;
	STDMETHOD_(BOOL, CanLabelEdit)		(void) PURE;
	STDMETHOD_(int, GetPopUpMenuID)		(void) PURE;
	STDMETHOD_(int, GetImage)			(void) PURE;
	STDMETHOD(CreateInsertItem)(ITreeItem **pp, REFIID riid, LPCSTR lpcstrName, LPCSTR lpcstrDecl, LPCSTR lpcstrType, LPCSTR lpcstrParams, LPCSTR lpcstrComment, BOOL fSuper) PURE;
	STDMETHOD(IsFirstLevel)		(void) PURE;
	STDMETHOD(IsKeyLevel)		(void) PURE;
	STDMETHOD(IsScriptLevel)	(void) PURE;
	STDMETHOD(IsFunctionLevel)	(void) PURE;
};

interface DECLSPEC_UUID("e8281062-cadc-11d0-9e56-0020AF3712c3")
IBSProperty : public IUnknown
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;
	//  *** IBSScriptProperty ***
	STDMETHOD(SetScript)		(CebScript *) PURE;
	STDMETHOD(GetScript)		(CebScript **)  PURE;
	STDMETHOD(GetCode)			(ebHCODE*) PURE;
	STDMETHOD(SetCode)			(ebHCODE)  PURE; 
	STDMETHOD(SetThread)		(CebThread *) PURE;
	STDMETHOD(GetThread)		(CebThread **)  PURE;
	STDMETHOD(GetScriptName)	(LPSTR, UINT)   PURE;
	STDMETHOD(SetScriptName)	(LPCSTR lpcstr)  PURE;
};

interface DECLSPEC_UUID("07963843-3123-101C-BB62-00AA0018497C")
IExportImportProject : public IUnknown
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;
	//  *** IBSScriptProperty ***
	STDMETHOD_(void, SetManagement)	(IObjectManagement*) PURE;
	STDMETHOD(GetTexts)(LPSTR **lplplpstrRelTexts, UINT & uiTexts) PURE;
};

// für SaveStruct
#define CC_SCRIPT			0x0001
#define CC_CODE				0x0002
#define CC_ALL				0x0004
#define CC_RELATEDSCRIPTS	0x0008
#define CC_EXPORT			0x0020
#define CC_IMPORT			0x0100
#define CC_EXPORTALL		0x0200

#define GETFROMDISC			0x0010
#define SUPERITEM 			0x0080

#define OBJFEAT_INSTALLED	0x0040
#define OBJFEAT_UNINSTALLED	0xFFBF

#endif // _ISCRPROP_H