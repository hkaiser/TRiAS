/* Testen, ob vorgegebene Zahl eine Primzahl ist                */
/* File: PRIM.C                 last update: 15. Februar 1990   */

#include "trias01p.hxx"

int FUNCTYPE isprim (short prim);

short FUNCTYPE prim (short pagesize) 
{
register short testprim = ((short)(1.2 * pagesize));

	while (isprim (testprim) != 0) testprim++;

return testprim;
}

int FUNCTYPE isprim (short prim) 
{
register int flag = 0;
register int i;

        for (i = 2; i <= prim/2; ++i) 
                if (!(prim % i)) flag = 1;

return flag;
}
