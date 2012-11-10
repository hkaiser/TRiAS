////////////////////////////////////////////////////////////////
// Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// See debug.cpp
// 
#ifdef _DEBUG

//////////////////
// Implements TRACEFN macro.
// Don't ever use directly, just use TRACEFN
//
class CTraceFn {
private:
	static int	nIndent;	// current indent level
	friend void AFX_CDECL AfxTrace(LPCTSTR lpszFormat, ...);
public:
	CTraceFn()  { nIndent++; }
	~CTraceFn() { nIndent--; }
};

// NOTE: YOU MUST NOT USE TRACEFN IN A ONE-LINE IF STATEMENT!
// This will fail:
//
// if (foo)
//    TRACEFN(...)
//
// Instead, you must enclose the TRACE in squiggle-brackets
//
// if (foo) {
//		TRACEFN(...)
// }
//
#define TRACEFN CTraceFn __fooble; TRACE

// Goodies to get names of things.
//
extern CString sDbgName(CWnd* pWnd); // get name of window
extern CString sDbgName(UINT uMsg);	 // get name of WM_ message

#ifdef REFIID

struct DBGINTERFACENAME {
	const IID* piid;	// ptr to GUID
	LPCSTR name;		// human-readable name of interface
};

// Change this to whatever interfaces you want to track
// Default is none
//
extern DBGINTERFACENAME* _pDbgInterfaceNames; 

extern CString sDbgName(REFIID iid);	// get name of COM interface

#endif // REFIID

#else // Not _DEBUG

#define sDbgName(x)	CString()
#define TRACEFN TRACE

#endif

// Macro casts to LPCTSTR for use with TRACE/printf/CString::Format
//
#define DbgName(x) (LPCTSTR)sDbgName(x)
