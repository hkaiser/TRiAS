// Special inline functions
// File: InlinesFuncs.h

#if !defined(_INLINEFUNCS_H)
#define _INLINEFUNCS_H

// Message an TRiAS weiterleiten, ohne, daﬂ es zu Rekursionen kommt -----------
extern "C" DEXDISPATCHPROC g_pDexDispatchProc;

inline 
LRESULT PASCAL ForwardMsgToTRiAS (HWND hWnd, UINT uiMsg, WPARAM w = 0L, LPARAM l = 0L)
{
	if (g_pDexDispatchProc)
		return (*g_pDexDispatchProc)(hWnd, uiMsg, w, l);

	ASSERT(false);
	return false;
}

#endif // _INLINEFUNCS_H
