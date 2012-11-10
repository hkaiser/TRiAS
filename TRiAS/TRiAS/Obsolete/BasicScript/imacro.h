// Costuminterfaces fuer Macroscriptverwaltung
// File: IMACRO.H

#if !defined(_IMACRO_H)
#define _IMACRO_H

#undef INTERFACE
#define INTERFACE IEnumScripts
                
struct IScript;                
// 07963813-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IEnumScripts, 0x07963813L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IEnumScripts, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IEnumUnknown methods
	STDMETHOD (Next) (THIS_ ULONG celt, LPUNKNOWN *rgelt, ULONG *pceltFetched) PURE;
	STDMETHOD (Skip) (THIS_ ULONG celt) PURE;
	STDMETHOD (Reset) (THIS) PURE;
	STDMETHOD (Clone) (THIS_ IEnumScripts **ppenm) PURE;
	
// *** EnumMacroScript methods
	STDMETHOD (FindByName) (LPCSTR pName, LPUNKNOWN *ppUnk) PURE;
};
typedef IEnumScripts *LPENUMSCRIPTS;


// Costumint. fuer Klasse CMacroscript

#undef INTERFACE
#define INTERFACE IScriptContainer

// 0796380F-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(CLSID_ScriptContainer, 0x0796380FL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// 07963811-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IScriptContainer, 0x07963811L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IScriptContainer, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IMacroScript specific functions ***
	STDMETHOD_(HRESULT, InitStorages) (LPSTORAGE pIRootStor, LPCSTR pPath ) PURE;
	STDMETHOD_(HRESULT, NewSubStorage) (LPSTORAGE pIRootStorage, 
									LPSTORAGE *ppISubStorage) PURE;
	
	STDMETHOD_(HRESULT, Commit) (DWORD grfCommitFlags, bool fAsk) PURE;
	STDMETHOD_(HRESULT, IsDirty) (void) PURE;
	STDMETHOD_(HRESULT, SetNotCommit) (bool fNotCommit) PURE;
	STDMETHOD_(HRESULT, GetEnumScripts) (IEnumScripts **penum) PURE;
	
	STDMETHOD_(HRESULT, GetScriptInfo) (LPCSTR pcName, DWORD *pdwInfo) PURE; 

	STDMETHOD_(HRESULT, DelScript) (LPCSTR pcName) PURE;
	STDMETHOD_(HRESULT, CreateScript) (LPCSTR pcName) PURE;

	STDMETHOD_(HRESULT, GetScript) (LPCSTR pcName, LPSTR *ppMacroText,
									ebHCODE *pebhCode) PURE;
	STDMETHOD_(HRESULT, SetScript) (LPCSTR pcName, LPSTR pText, ebHCODE ebhCode, 
					DWORD dwSaveFlag) PURE; 
	STDMETHOD (GetebInst) (CebInstance **ppInst) PURE;
};
typedef IScriptContainer * LPSCRIPTCONTAINER;

DefineSmartInterface(ScriptContainer);

// Costumint. fuer Klasse CMacros

#undef INTERFACE
#define INTERFACE IScript

// 07963810-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(CLSID_Script, 0x07963810L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// 07963812-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IScript, 0x07963812L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IScript, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IMacros specific functions ***
	STDMETHOD_(HRESULT, GetName) (THIS_ LPSTR pScName, ULONG ulSize) PURE;
	STDMETHOD_(HRESULT, SetName) (THIS_ LPCSTR pScName) PURE;

};
typedef IScript * LPSCRIPT;

#define CC_SCRIPT 0x0001
#define CC_CODE   0x0002
#define CC_SYMBOL 0x0004
#define CC_CONST  0x0008 
#define CC_ALL    0x000F 

#endif _IMACRO_H


