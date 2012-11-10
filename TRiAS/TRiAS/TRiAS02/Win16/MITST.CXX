/*Translated by FOR_C, v3.2 (B), on 05/28/91 at 10:32:34 */
/*FOR_C Options SET: c=2 do=rt ftn=l op=i s=dvwo str=l */

#include <string.h>
#define TRUE (1)
#define FALSE (0)

#include "zforc.h"

long /*FUNCTION*/ FUNCTYPE
mitst(wi1, wi2, typ, tkz)
double *wi1, *wi2;
long int *typ;
char *tkz;
{
	/*       K.KURTH 25.04.89
	 *       AUFGABE:TEST DER WERTE WIi AUF TKZ */
	if (!strncmp (tkz, "LT", 2) && *wi2 < *wi1)
		return TRUE;
	if (!strncmp (tkz, "LE", 2) && *wi2 <= *wi1)
		return TRUE;
	if (!strncmp (tkz, "EQ", 2) && *wi2 == *wi1)
		return TRUE;
	if (!strncmp (tkz, "GE", 2) && *wi2 >= *wi1)
		return TRUE;
	if (!strncmp (tkz, "GT", 2) && *wi2 > *wi1)
		return TRUE;

return FALSE;
} /* end of function */

