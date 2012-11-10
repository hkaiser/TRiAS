// Synchronisationsklasse für thread-sicheres Incrementieren eines Cookies
// File: SYNCCOOK.H

#if !defined(_SYNCCOOK_H)
#define _SYNCCOOK_H

class CSyncCookies : public CSyncMonitor {
public:
	CSyncCookies (void) : CSyncMonitor (true) {}
	~CSyncCookies (void) {}

inline	DWORD IncrementSynced (DWORD *pdwCookie) 
	{ CSyncThread Sync (this); return ++*pdwCookie; }
};

#endif // _SYNCCOOK_H
