// Doppeln eines Strings mit new
// File: STRDUP.HXX

#if !defined(_STRDUP_HXX)
#define _STRDUP_HXX

#include <protos.h>
#include <errcodes.hxx>     // für RC_STRINGDUP

#include <new>

#if !defined(ATLTRY)
#define ATLTRY(x)	TX_TRY(x)
#if !defined(TX_TRY)
#error "Must define ATLTRY or TX_TRY!"
#endif // TX_TRY
#endif // ATLTRY

// helper für älteren Code
#define StrDup	StrDupF
#define StrFree	StrFreeF

// eigentliche Funktionalität
inline char *StrDupF (const char *cptr, short RCode = 0) 
{
char *newPtr = NULL;

	if (cptr != NULL) {
		ATLTRY(newPtr = new char [strlen(cptr)+1]);
		if (newPtr == NULL) 
			db_error (EC_NOMEMORY, RCode ? RCode : RC_StringDup);
		else
			strcpy (newPtr, cptr);
	}

return newPtr;
}

inline void StrFreeF (char *cptr)
{
	if (cptr) delete cptr;
}

#if defined(WIN32)

inline LPWSTR StrDupW (LPCWSTR cptr, short iRCode = 0) 
{
LPWSTR newPtr = NULL;

	if (cptr != NULL) {
		newPtr = (LPWSTR)CoTaskMemAlloc ((wcslen(cptr)+1)*sizeof(wchar_t)); 
		if (newPtr == NULL) 
			db_error (EC_NOMEMORY, iRCode ? iRCode : RC_StringDup);
		else
			wcscpy (newPtr, cptr);
	}

return newPtr;
}

inline LPWSTR StrDupW (char *cptr, short iRCode = 0) 
{
LPWSTR newPtr = NULL;

	if (cptr != NULL) {
		newPtr = (LPWSTR)CoTaskMemAlloc ((strlen(cptr)+1)*sizeof(wchar_t)); 
		if (newPtr == NULL) 
			db_error (EC_NOMEMORY, iRCode ? iRCode : RC_StringDup);
		else 
			wcscpy (newPtr, WideString (cptr));
	}

return newPtr;
}

inline void StrFreeW (LPWSTR cptr)
{
	if (cptr) CoTaskMemFree (cptr);
}

#else
#define StrDupW		StrDup
#define StrFreeW	StrFree
#endif // WIN32

// als Scoping class zu gebrauchen
class StringDup {
private:
//  Attribute
    pchar _pStr;

public:
//  Konstruktor/Destruktor
	StringDup (void) { _pStr = NULL; }
	StringDup (pchar pString, Bool iCopy = TRUE) { 
		if (iCopy) _pStr = StrDupF (pString, RC_ctStringDup);
		else  _pStr = pString; 
	}
	~StringDup (void)   { DELETE_OBJ (_pStr); }

//  weitere Member
	operator char * (void)	{ return _pStr; }
	pchar Ptr (void)	{ return _pStr; }
	Bool operator ! (void)	{ return _pStr == NULL; }
	operator Bool (void)	{ return ! *this; }
	short Len (void)	{ return strlen (_pStr); }
	pchar Upper (void)	{ return strupr (_pStr); }
	pchar Lower (void)	{ return strlwr (_pStr); }
	pchar Replace (pchar pNewStr)
	    { DELETE_OBJ(_pStr); return (_pStr = StrDupF (pNewStr, RC_ctStringDup)); }
};

#endif // _STRDUP_HXX
