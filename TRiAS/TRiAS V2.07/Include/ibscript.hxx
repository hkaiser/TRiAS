// Interfacedeklaration für Schnittstelle zu BScript-Erweiterung --------------
// File: IBSCRIPT.HXX

#if !defined(_IBSCRIPT_HXX)
#define _IBSCRIPT_HXX

#if _MSC_VER < 1100 && !defined(DECLSPEC_UUID)
#define DECLSPEC_UUID(x)
#endif // _MSC_VER < 1100 && !defined(DECLSPEC_UUID)

#undef INTERFACE
#define INTERFACE IExtendBScript

// 0796380A-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IExtendBScript, 0x0796380AL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

#if defined(EBWIN32)

// Die Größe der Felder in BSPARAM muß der Anzahl der zu übergebenenden Parameter 
// plus eins (für den Rückgabewert) entsprechen. Der Rückgabewert wird durch die
// ersten Feldelemente repräsentiert. Für Subroutinen (kein Rückgabewert) müssen
// die ersten FeldElemente Null sein.
typedef struct tagBSPARAM {		// Parameter für FireEvent
	ebPARAM *pTypes;	// TypenFeld der Parameters
	LPVOID *pValues;		// Zeigerfeld auf Parameter
} BSPARAM;

#endif // EBWIN32

interface DECLSPEC_UUID("0796380A-3123-101C-BB62-00AA0018497C")
IExtendBScript : public IUnknown
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IExtendBScript methods
	STDMETHOD(RegisterExtModule)(THIS_ LPCSTR lpModule) PURE;
	STDMETHOD(FireEvent)(THIS_ LPCSTR lpEntry, int iNumParams, struct tagBSPARAM *pPars) PURE;
	STDMETHOD(RunText)(THIS_ LPCSTR lpText, LPCSTR lpEntry, int iNumParams, struct tagBSPARAM *pPars) PURE;
	STDMETHOD(RunCode)(THIS_ HINSTANCE hInst, int iResID, LPCSTR lpEntry, int iNumParams, struct tagBSPARAM *pPars) PURE;
	STDMETHOD(RunScript)(THIS_ LPCSTR lpName) PURE;
	STDMETHOD(StopScript)(THIS_ LPCSTR lpName) PURE;

	STDMETHOD(RunTextEx)(THIS_ LPCSTR lpText, LPCSTR lpName, LPCSTR lpEntry, int iNumParams, struct tagBSPARAM *pPars, BOOL fBreakAfterExec) PURE;
	STDMETHOD(RunCodeEx)(THIS_ HINSTANCE hInst, int iResID, LPCSTR lpName, LPCSTR lpEntry, int iNumParams, struct tagBSPARAM *pPars, BOOL fBreakAfterExec) PURE;
	STDMETHOD(ExecuteMethod)(THIS_ LPCSTR lpName, LPCSTR lpEntry, int iNumParams, struct tagBSPARAM *pPars, BOOL fBreakAfterExec) PURE;
};
typedef IExtendBScript *LPEXTENDBSCRIPT;

#endif // _IBSCRIPT_HXX
