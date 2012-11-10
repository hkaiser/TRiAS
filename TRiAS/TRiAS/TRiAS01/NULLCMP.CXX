/* Routine, die Speicherbereich auf Null testet                 */
/* File: NULLCMP.C                                              */

#include "trias01p.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

int FUNCTYPE nullcmp (void *cptr, register int len)
{
#if defined(NULLCMP)
register char *pPtr = (char *)cptr;

	TX_ASSERT(TIsValidAddress(cptr, len, false));

        while (len-- > 0) 
                if (*pPtr++ != '\0') 
                        return (0);

return (1);
#else
return (0);	// immer ungleich null
#endif
}
