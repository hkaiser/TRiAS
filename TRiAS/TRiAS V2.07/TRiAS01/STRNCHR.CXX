/* Sting-Manipulationen                                         */
/* File: STRNCHR.C                                              */

#include "trias01p.hxx"

/* 'strchr' aber mit Laengenangabe                              */
char * FUNCTYPE strnchr (register char *ptr, register char z, register int len)
{
        if (*ptr == '\0') return NULL;
        while (len-- > 0) {
                if (*ptr == '\0') return NULL;
                if (*ptr == z) return ptr;
                ptr++;
        }

return NULL;
}

/* Finden des ersten Eintrages eines Zeichens (aber von hinten) */
extern "C" char * FUNCTYPE EXPORT01 strrlchr (char *ptr, char z)
{
register int len = strlen (ptr);
register char *rcptr = &ptr[len];

        while (len-- > 0) {
                --rcptr;
                if (*rcptr != z) break;
        }
        if (len < 0) return NULL;

return rcptr+1;
}


#if defined(WIN32)

inline OLECHAR *__ConvertStrAtoW (const char *strIn, OLECHAR *buf, UINT size)
{
	MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, strIn, -1, buf, size); 

return buf;
}


OLECHAR *ConvertStrAtoW (const char *strIn, OLECHAR *buf, UINT size)
{
	return __ConvertStrAtoW (strIn, buf, size);
}

OLECHAR *WideString (const char *strIn)
{
static OLECHAR buf[_MAX_PATH];

	if (NULL == strIn) return NULL;
	return (__ConvertStrAtoW (strIn, buf, _MAX_PATH));
}

inline char *__ConvertStrWtoA (const OLECHAR *strIn, char *buf, UINT size)
{
int badConversion = false;
  
	WideCharToMultiByte (CP_ACP, NULL, strIn, -1, buf, size, 
			     NULL, &badConversion);

return buf;
}

char *ConvertStrWtoA (const OLECHAR *strIn, char *buf, UINT size)
{
	return __ConvertStrWtoA (strIn, buf, size);
}

char *AnsiString (const OLECHAR *strIn)
{
static char buf[256];

	if (NULL == strIn) return NULL;
	return (__ConvertStrWtoA (strIn, buf, 256));
}

#endif
