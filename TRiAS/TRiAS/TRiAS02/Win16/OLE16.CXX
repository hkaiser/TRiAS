// CoTaskMemAlloc und CoTaskMemFree für 16Bit ---------------------------------
// File: OLE16.CXX

#include "trias02p.hxx"

#include "ole16.h"		// Definitionen für 16Bit

#if !defined(WIN32)		// nur für 16Bit

STDAPI_(LPVOID) CoTaskMemAlloc (LONG cb)
{
LPMALLOC pIMalloc = NULL;

	if (FAILED(CoGetMalloc (MEMCTX_TASK, &pIMalloc)))
		return NULL;
		
LPVOID pNew = pIMalloc -> Alloc (cb);

	pIMalloc -> Release();
	
return pNew;
}


STDAPI_(void) CoTaskMemFree(LPVOID pv)
{
LPMALLOC pIMalloc = NULL;

	if (SUCCEEDED(CoGetMalloc (MEMCTX_TASK, &pIMalloc))) {
		pIMalloc -> Free (pv);		
		pIMalloc -> Release();
	}
}


STDAPI_(LPVOID) CoTaskMemRealloc (LPVOID pv, ULONG cb)
{
LPMALLOC pIMalloc = NULL;

	if (FAILED(CoGetMalloc (MEMCTX_TASK, &pIMalloc)))
		return NULL;
		
LPVOID pNew = pIMalloc -> Realloc (pv, cb);

	pIMalloc -> Release();
	
return pNew;
}

#endif // WIN32
