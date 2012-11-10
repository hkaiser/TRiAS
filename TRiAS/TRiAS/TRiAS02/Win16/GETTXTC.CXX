/* Lesen der Textinformationen in der *.DBT                             */
/* File: GETTXTC.C              last update: 05. Juni 1990              */

#ifdef MSWIND
#include <windows.h>
#endif
#include "dbtypes.h"
#include "dioexter.h"
#include "errdef.h"
#include "risdb.h"

long FUNCTYPE
gettxt_ (kod, madr, lt, mi)
long *mi;               /* Merkmalsinfo */
long *kod;              /* irc */
long *lt;               /* Anfang in mi */
long *madr;             /* Satznummer in '.dbt' */
{
DB_ADDR dba;
struct dbt dbt_satz;    /* Satz der Datei '.dbt' */
register short i;
long wf, j;
register int flag = FALSE;

        dba.file_no = DBT;
        dba.rec_no = *madr;
        j = 0;
        for (;;) {
	int irc;

                if ((irc = z_readrec (&dba, &dbt_satz)) != S_OKAY) 
                        return (-irc);
                if (flag == FALSE) {
                        wf = ((INT *)(dbt_satz.info))[0];
                        if (mi[1]+wf+3 > mi[0]) {
                                *kod = -1;
                                return S_OKAY;
                        }
                } else {
                        mi[*lt + j++ -1] = ((INT *)(dbt_satz.info))[0];
                }
                for (i = 1; i < 10; ++i) {
                        if (j == wf) break;
                        mi[*lt + j++ -1] = ((INT *)(dbt_satz.info))[i];
                }
                flag = TRUE;
                if (dbt_satz.zndbt == 0) break;
                dba.rec_no = dbt_satz.zndbt;
        }
        *kod = 0;
        mi[1] += wf+3;
        mi[*lt-2] = wf;
                        
return S_OKAY;
}

