// ASSERT's für TRiAS ---------------------------------------------------------
// File: CONTASRT.H

#if !defined(_CONTASRT_H)
#define _CONTASRT_H

_CTR_ENTRY32 void CDECL ExtTrace (LPCTSTR lpszFormat, ...);
_CTR_ENTRY32 bool WINAPI DLLENTRY AssertFailedLine(LPCSTR lpszFileName, int nLine);

_CTR_ENTRY32 bool IsWin31 (void);
_CTR_ENTRY32 bool IsWin40 (void);
_CTR_ENTRY32 bool IsWin32s (void);
_CTR_ENTRY32 bool IsWinNT (void);

#if defined(__CV__)
#if defined(_DEBUG)
#define TX_TRACE			::ExtTrace
#define TX_TRACE0(sz)           	::ExtTrace(TEXT(sz))
#define TX_TRACE1(sz, p1)       	::ExtTrace(TEXT(sz), p1)
#define TX_TRACE2(sz, p1, p2)   	::ExtTrace(TEXT(sz), p1, p2)
#define TX_TRACE3(sz, p1, p2, p3)  	::ExtTrace(TEXT(sz), p1, p2, p3)
#define TX_ASSERT(f)	do { 	\
			if (!(f) && AssertFailedLine(THIS_FILE,__LINE__))	\
				DebugBreak(); 	\
			} while(0)
#else // _DEBUG
#define TX_TRACE			1 ? (void)0 : ::ExtTrace
#define TX_TRACE0(sz)              
#define TX_TRACE1(sz, p1)
#define TX_TRACE2(sz, p1, p2)
#define TX_TRACE3(sz, p1, p2, p3)
#define TX_ASSERT(f)
#endif

#define TX_ASSERT_POINTER(p, type) \
	TX_ASSERT(((p) != NULL) && TIsValidAddress((p), sizeof(type), false))
#define TX_ASSERT_NULL_OR_POINTER(p, type) \
	TX_ASSERT(((p) == NULL) || TIsValidAddress((p), sizeof(type), false))

_CTR_ENTRY32 bool WINAPI TIsValidString(LPCSTR lpsz, int nLength = -1);
_CTR_ENTRY32 bool WINAPI TIsValidAddress(const void* lp, UINT nBytes, bool bReadWrite = true);
_CTR_ENTRY32 bool WINAPI TIsValidIUnknown (const void *lp);

#endif //__CV__

#endif // _CONTASRT_H
