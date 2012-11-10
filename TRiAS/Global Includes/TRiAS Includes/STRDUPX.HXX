// Doppeln eines Strings mit new
// File: STRDUPX.HXX

#if !defined(_STRDUPX_HXX)
#define _STRDUPX_HXX

extern "C" {
	#include <string.h>
//	#include <protos.h>
}

#include <errcodes.hxx>     // für RC_STRINGDUP

inline int my_db_error (int RC, int EC)
{
	DEX_Error (RC, EC);

return EC;
}

inline char *StrDup (const char *cptr, short RCode = 0) 
{

char *newPtr = NULL;

	if (cptr != NULL) {
		newPtr = new char [strlen(cptr)+1];
		if (newPtr == NULL) 
			my_db_error (RCode ? RCode : RC_StringDup, EC_NOMEMORY);
		else
			strcpy (newPtr, cptr);
	}

return newPtr;

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
	    { DELETE_OBJ (_pStr); return (_pStr = StrDup (pNewStr, RC_ctStringDup)); }
};

#endif // _STRDUPX_HXX
