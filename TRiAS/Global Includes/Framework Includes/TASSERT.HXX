// ASSERT's für TRiAS ---------------------------------------------------------
// File: TASSERT.H

#if !defined(_TASSERT_H)
#define _TASSERT_H

#if !defined(TX_TRACE)

#if defined(WIN32)

#if !defined(BASED_CODE)
#define BASED_CODE
#endif

_CTR_ENTRY32 void CDECL ExtTrace (LPCTSTR lpszFormat, ...);
_CTR_ENTRY32 BOOL WINAPI IsWin31 (void);
_CTR_ENTRY32 BOOL WINAPI IsWin40 (void);
_CTR_ENTRY32 BOOL WINAPI IsWin41 (void);
_CTR_ENTRY32 BOOL WINAPI IsWin50 (void);
_CTR_ENTRY32 BOOL WINAPI IsWin32s (void);
_CTR_ENTRY32 BOOL WINAPI IsWinNT (void);
#define _NOVERSION

#if defined(_DEBUG)
#define TX_TRACE			::ExtTrace
#define TX_TRACE0(sz)           	::ExtTrace(TEXT(sz))
#define TX_TRACE1(sz, p1)       	::ExtTrace(TEXT(sz), p1)
#define TX_TRACE2(sz, p1, p2)   	::ExtTrace(TEXT(sz), p1, p2)
#define TX_TRACE3(sz, p1, p2, p3)  	::ExtTrace(TEXT(sz), p1, p2, p3)
#define TX_ASSERT(f)	do { 	\
			if (!(f) && AssertFailedLine(#f, THIS_FILE,__LINE__))	\
				DebugBreak(); \
			} while(0)
#define TX_VERIFY(f)	TX_ASSERT(f)
#else // _DEBUG
#define TX_TRACE			1 ? (void)0 : ::ExtTrace
#define TX_TRACE0(sz)              
#define TX_TRACE1(sz, p1)
#define TX_TRACE2(sz, p1, p2)
#define TX_TRACE3(sz, p1, p2, p3)
#define TX_ASSERT(f)
#define TX_VERIFY(f)	(f)
#endif // _DEBUG

#define TX_ASSERT_POINTER(p, type) \
	TX_ASSERT(((p) != NULL) && TIsValidAddress((p), sizeof(type), false))
#define TX_ASSERT_NULL_OR_POINTER(p, type) \
	TX_ASSERT(((p) == NULL) || TIsValidAddress((p), sizeof(type), false))

_CTR_ENTRY32 BOOL WINAPI TIsValidString(LPCSTR lpsz, int nLength = -1);
_CTR_ENTRY32 BOOL WINAPI TIsValidAddress(const void* lp, UINT nBytes, BOOL bReadWrite = true);
_CTR_ENTRY32 BOOL WINAPI TIsValidIUnknown (const void *lp);

_CTR_ENTRY32 BOOL WINAPI AssertFailedLine(LPCSTR lpszExpr, LPCSTR lpszFileName, int nLine);
_CTR_ENTRY32 BOOL WINAPI VerboseAssertFailedLine (LPCSTR lpszExpr, LPCSTR lpszFileName, int nLine);

#if defined(_CPPUNWIND)
#define TX_TRY(x) try{x;} catch(...) {}
#else
#define TX_TRY(x) x;
#endif
	
#else // WIN32

#if !defined(BASED_CODE)
#define BASED_CODE __based(__segname("_CODE"))
#endif

inline void ExtTrace (LPCSTR, ...) {}

#define TX_TRACE			1 ? (void)0 : ::ExtTrace
#define TX_TRACE0(sz)              
#define TX_TRACE1(sz, p1)
#define TX_TRACE2(sz, p1, p2)
#define TX_TRACE3(sz, p1, p2, p3)
#define TX_ASSERT(f)

#define TX_ASSERT_POINTER(p, type) 
#define TX_ASSERT_NULL_OR_POINTER(p, type) 

#endif // WIN32

#endif // !TX_TRACE

#endif // _TASSERT_H
