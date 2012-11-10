// sonstige Funktionen in Xtension-Bibliothek ---------------------------------
// File: XTSNAUX.HXX

#if !defined(_XTSNAUX_HXX)
#define _XTSNAUX_HXX

LPTSTR FAR PASCAL DtoA (LPTSTR String, LPTSTR Format, double Wert);

#if !defined(WIN16) 
#if !defined(OLE2ANSI)
// Zeichenkettenkonvertierung ANSI <--> UNICODE -------------------------------
#pragma warning (disable: 4273)		// inconsistent dll linkage.  dllexport assumed.
LPWSTR ConvertStrAtoW (const char *strIn, LPWSTR buf, UINT size);
LPWSTR WideString (const char *strIn);
char *ConvertStrWtoA (LPCWSTR strIn, char *buf, UINT size);
char *AnsiString (LPCWSTR strIn);
#pragma warning (default: 4273)
#else // OLE2ANSI
#define WideString(str) ((char *)(const char *)str)
#define AnsiString(str) ((char *)(const char *)str)
#endif // OLE2ANSI
#else // WIN16
#undef WideString
#undef AnsiString
#define WideString(str) ((char *)(const char *)str)
#define AnsiString(str) ((char *)(const char *)str)
#endif // WIN16

#if defined(__CV__) || defined(__WTL__)
#if defined(_DEBUG)
#if !defined(WIN16)
bool WINAPI ExtIsValidString (LPCWSTR lpsz, int nLength);
#endif
bool WINAPI ExtIsValidString (LPCSTR lpsz, int nLength);
bool WINAPI ExtIsValidAddress (const void* lp, UINT nBytes, bool bReadWrite);

bool WINAPI DEX_AssertFailedLine(LPCSTR lpszExpr, LPCSTR lpszFileName, int nLine);

#if defined(TX_TRACE)

#undef TX_TRACE
#undef TX_TRACE0
#undef TX_TRACE1
#undef TX_TRACE2
#undef TX_TRACE3
#undef TX_ASSERT
#undef TX_ASSERT_POINTER
#undef TX_ASSERT_NULL_OR_POINTER

#define _NOVERSION

#else // TX_TRACE

void CDECL ExtTrace (LPCTSTR lpszFormat, ...);

BOOL IsWin31 (void);
BOOL IsWin40 (void);
BOOL IsWin41 (void);
BOOL IsWin50 (void);
BOOL IsWin32s (void);
BOOL IsWinNT (void);

#endif // TX_TRACE

#if !defined(WIN16)

#if !defined(BASED_CODE)
#define BASED_CODE
#endif

#define TX_TRACE			::ExtTrace
#define TX_TRACE0(sz)           	::ExtTrace(TEXT(sz))
#define TX_TRACE1(sz, p1)       	::ExtTrace(TEXT(sz), p1)
#define TX_TRACE2(sz, p1, p2)   	::ExtTrace(TEXT(sz), p1, p2)
#define TX_TRACE3(sz, p1, p2, p3)  	::ExtTrace(TEXT(sz), p1, p2, p3)
#define TX_ASSERT(f)	do { 	\
			if (!(f) && DEX_AssertFailedLine(#f, THIS_FILE,__LINE__))	\
				DebugBreak(); 	\
			} while(0)

#define TX_ASSERT_POINTER(p, type) \
	TX_ASSERT(((p) != NULL) && ExtIsValidAddress((p), sizeof(type), FALSE))
#define TX_ASSERT_NULL_OR_POINTER(p, type) \
	TX_ASSERT(((p) == NULL) || ExtIsValidAddress((p), sizeof(type), FALSE))

#else // WIN16

#define TX_TRACE			1 ? (void)0 : ::ExtTrace
#define TX_TRACE0(sz)              
#define TX_TRACE1(sz, p1)
#define TX_TRACE2(sz, p1, p2)
#define TX_TRACE3(sz, p1, p2, p3)
#define TX_ASSERT(f)
#define TX_ASSERT_POINTER(p, type) 
#define TX_ASSERT_NULL_OR_POINTER(p, type) 

#endif // WIN16


#else // _DEBUG

#if defined(TX_TRACE)

#define _NOVERSION

#undef TX_TRACE
#undef TX_TRACE0
#undef TX_TRACE1
#undef TX_TRACE2
#undef TX_TRACE3
#undef TX_ASSERT
#undef TX_ASSERT_POINTER
#undef TX_ASSERT_NULL_OR_POINTER

#else

BOOL IsWin31 (void);
BOOL IsWin40 (void);
BOOL IsWin41 (void);
BOOL IsWin50 (void);
BOOL IsWin32s (void);
BOOL IsWinNT (void);

#endif // TX_TRACE

#define TX_TRACE			1 ? (void)0 : ::ExtTrace
#define TX_TRACE0(sz)              
#define TX_TRACE1(sz, p1)
#define TX_TRACE2(sz, p1, p2)
#define TX_TRACE3(sz, p1, p2, p3)
#define TX_ASSERT(f)
#define TX_ASSERT_POINTER(p, type) 
#define TX_ASSERT_NULL_OR_POINTER(p, type) 

#endif // _DEBUG

#else // __CV__

#undef TX_TRACE
#undef TX_TRACE0
#undef TX_TRACE1
#undef TX_TRACE2
#undef TX_TRACE3
#undef TX_ASSERT
#undef TX_ASSERT_POINTER
#undef TX_ASSERT_NULL_OR_POINTER

#if defined(_DEBUG)
#define TX_TRACE			TRACE
#define TX_TRACE0(sz)           	TRACE0(sz)
#define TX_TRACE1(sz, p1)       	TRACE1((sz),(p1))
#define TX_TRACE2(sz, p1, p2)   	TRACE2((sz),(p1),(p2))
#define TX_TRACE3(sz, p1, p2, p3)  	TRACE3((sz),(p1),(p2),(p3))
#define TX_ASSERT(f)			_ASSERTE(f)
#else // _DEBUG
#define TX_TRACE			TRACE
#define TX_TRACE0(sz)              
#define TX_TRACE1(sz, p1)
#define TX_TRACE2(sz, p1, p2)
#define TX_TRACE3(sz, p1, p2, p3)
#define TX_ASSERT(f)
#endif

#define TX_ASSERT_POINTER(p, type) \
	TX_ASSERT(((p) != NULL) && AfxIsValidAddress((p), sizeof(type), FALSE))
#define TX_ASSERT_NULL_OR_POINTER(p, type) \
	TX_ASSERT(((p) == NULL) || AfxIsValidAddress((p), sizeof(type), FALSE))

#if !defined(_TASSERT_H)
BOOL IsWin31 (void);
BOOL IsWin40 (void);
BOOL IsWin41 (void);
BOOL IsWin50 (void);
BOOL IsWin32s (void);
BOOL IsWinNT (void);
#endif // _TASSERT_H

#endif // __CV__

#undef ADDREF
#define ADDREF(p)	{if(p){(p)->AddRef();}}
#undef RELEASE
#define RELEASE(p)	{if(p){(p)->Release();(p)=NULL;}}

#undef ADDREF_CAST
#define ADDREF_CAST(t,p)	{if(p){((t*)p)->AddRef();}}
#undef RELEASE_CAST
#define RELEASE_CAST(t,p)	{if(p){((t*)p)->Release();}}
#undef RELEASE_NONULL
#define RELEASE_NONULL(p)	{if(p){(p)->Release();}}

// Hilfs-Funktionen für die RegDB ---------------------------------------------
#define EFNoFlags		0x00
#define EFInsertable	0x01		// not used here
#define EFPreLoad		0x02		// soll automatische geladen werden
#define EFUnLoadable	0x04		// darf entladen werden
#define EFVisible		0x08		// darf optional geladen werden
#define EFCanImport		0x10		// hat ImportInterface
#define EFDynImportCfg	0x20		// dynamische Importformatangabe

#define EFPriorityLoad1		0x0000		// PriorityLoadStufe: min
#define EFPriorityLoad2		0x1040
#define EFPriorityLoad3		0x2040
#define EFPriorityLoad4		0x3040
#define EFPriorityLoad5		0x4040
#define EFPriorityLoad6		0x5040
#define EFPriorityLoad7		0x6040
#define EFPriorityLoad8		0x7040		// PriorityLoadStufe: max
#define EFPriorityLoad		0x40		// vorrangig laden
#define EFPriorityLoadMask	0x7000

#define EFAggregate		0x80				// Erweiterung soll von TRiAS Aggregiert werden
#define EFRegisterToolBitmap	0x0100		// ToolBarBitmap32 registrieren (resID=1!)
#define EFDragDropTarget		0x0200		// Aggregierte Erweiterung unterstützt Drag'n Drop

// Funktionen, die SelfRegistering vereinfachen -------------------------------
bool WINAPI ExtOleRegisterTypeLib (HINSTANCE hInstance, REFGUID tlid,
	LPCTSTR pszFileName = NULL, LPCTSTR pszHelpDir = NULL);
bool WINAPI ExtOleUnregisterTypeLib (REFGUID tlid);
bool WINAPI ExtOleRegisterExtensionClass (HINSTANCE hInstance,
	REFCLSID clsid, LPCTSTR pszProgID, 
	UINT idTypeName, WORD wVerMajor = 1, WORD wVerMinor = 0, 
	int bFlags = EFNoFlags, GUID *ptlid = NULL);
bool WINAPI ExtOleUnregisterClass(REFCLSID clsid, LPCTSTR pszProgID);
bool WINAPI ExtOleRegisterImportClass (HINSTANCE hInstance, REFIID riid, 
	LPCTSTR pszProgID, UINT uiFormat, UINT uiExt, DWORD dwCaps = 0);

// sonstige helper ------------------------------------------------------------
bool WINAPI ExtOleRegisterHelperEx (LPCTSTR FAR* rglpszRegister,
	LPCTSTR FAR* rglpszSymbols, int nSymbols, bool bReplace, HKEY hkey);
bool WINAPI _ExtOleRegisterClass (HINSTANCE hInstance, REFCLSID clsid,
	LPCTSTR pszProgID, UINT idTypeName);
LONG _ExtRecursiveRegDeleteKey(HKEY hParentKey, LPTSTR szKeyName);

#if !defined(WIN16)
inline LONG piInterlockedIncrement (LONG *pVal) 
{ 
	if (IsWin32s()) return ++(*pVal);
	else return InterlockedIncrement (pVal); 
}
inline LONG piInterlockedDecrement (LONG *pVal) 
{
	if (IsWin32s()) return --(*pVal);
	else return InterlockedDecrement (pVal); 
}
#else
inline LONG piInterlockedIncrement (LONG *pVal) { return ++(*pVal); }
inline LONG piInterlockedDecrement (LONG *pVal) { return --(*pVal); }
#endif // WIN16

#endif // _XTSNAUX_HXX
