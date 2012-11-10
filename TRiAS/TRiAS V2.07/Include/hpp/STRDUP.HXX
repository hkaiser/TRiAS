// Doppeln eines Strings mit new
// File: STRDUP.HXX

#if !defined(_STRDUP_HXX)
#define _STRDUP_HXX

extern "C" {
	#include <string.h>
	#include <protos.h>
}

#include <errcodes.hxx>     // für RC_STRINGDUP

inline char *StrDup (const char *cptr, short RCode = 0) 
{
char *newPtr = NULL;

	if (cptr != NULL) {
		newPtr = new char [strlen(cptr)+1];
		if (newPtr == NULL)
                {
                        DEX_Error (RCode ? RCode : RC_StringDup, EC_NOMEMORY);
                }
		else
                        lstrcpy (newPtr, cptr);
	}

return newPtr;
}

inline void StrFree (char *cptr)
{
	if (cptr) delete cptr;
}

// als Scoping class zu gebrauchen
class StringDup {
private:
//  Attribute
    pchar _pStr;

public:
//  Konstruktor/Destruktor
	StringDup (void) { _pStr = NULL; }
	StringDup (pchar pString, Bool iCopy = TRUE) { 
		if (iCopy) _pStr = StrDup (pString, RC_ctStringDup);
		else  _pStr = pString; 
	}
	~StringDup (void)   { DELETE_VEC (_pStr); }

// 	weitere Member
	short Len (void)	{ return strlen (_pStr); }
	pchar Upper (void)	{ return strupr (_pStr); }
	pchar Lower (void)	{ return strlwr (_pStr); }
	// pchar Replace (pchar pNewStr) { DELETE_VEC (_pStr); return (_pStr = StrDup (pNewStr, RC_ctStringDup)); }

//	Operatoren
    operator const char * (void)  { return _pStr; }
    Bool operator == (const char *pT) { return pT && _pStr && (lstrcmp (pT, _pStr) == 0) ? TRUE : FALSE; }
	pchar Ptr (void)	{ return _pStr; }
	Bool operator ! (void)	{ return _pStr == NULL; }
	operator Bool (void)	{ return _pStr != NULL; }
	pchar Replace (char *pString, Bool bCopy = True) 
		{ DELETE_VEC (_pStr); return bCopy ? (_pStr = StrDup (pString, RC_ctStringDup)) : (_pStr = pString); }
};

#endif // _STRDUP_HXX
