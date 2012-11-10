//==================================================
// MemDiff - Matt Pietrek 1999
// Microsoft Systems Journal, December 1999
// FILE: MemDiff.h
//==================================================

#if !defined(_MEMDIFF_H__F769C9ED_CF83_4047_952E_B96C542E730E__INCLUDED_)
#define _MEMDIFF_H__F769C9ED_CF83_4047_952E_B96C542E730E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

extern "C"
{

typedef BOOL (__stdcall *MDOUTPUTPROC)(LPCSTR pcOutStr, size_t uiLen);

//
// Call this function twice, once at the beginning of the
// desired code sequence, and again afterwards.  Save
// the handles for later.
//
HANDLE __stdcall  MDTakeSnapshot( HANDLE hProcess );

//
// Compares two snapshot handles.  The third param (pOutputFile)
// is a Pointer to a function, which manages the actual output
//
BOOL __stdcall MDCompareSnapshot(   HANDLE hSnapshot1,
                                    HANDLE hSnapshot2,
                                    MDOUTPUTPROC pOutputFile,
                                    bool fVerbose = false );

//
// When done with the snapshots, call this function to release them
//
BOOL __stdcall MDFreeSnapshot( HANDLE hSnapshot );

}

#endif // !defined(_MEMDIFF_H__F769C9ED_CF83_4047_952E_B96C542E730E__INCLUDED_)
