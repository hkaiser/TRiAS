/* Funktionen yur Berechnung der Systemkonstanten               */
/* File: REPRTSYS.C                                             */

#include <stdio.h>
#include <time.h>
#include "dql.h"

short Year (void) {         /* Jahr - 1900 */
long clock;

        time (&clock);
        return ((localtime (&clock))->tm_year);
}

short Month (void) {        /* Monat 1..12 */
long clock;

        time (&clock);
        return ((localtime (&clock))->tm_mon);
}

short Day (void) {          /* Tag im Monat 1..31 */
long clock;

        time (&clock);
        return ((localtime (&clock))->tm_mday);
}

short W_day (void) {        /* Wochentag 0..6 (0: Sonntag) */
long clock;

        time (&clock);
        return ((localtime (&clock))->tm_wday);
}

short Y_day (void) {        /* Tag im Jahr 1..365 */
long clock;

        time (&clock);
        return ((localtime (&clock))->tm_yday);
}

short Hour (void) {         /* Stunde 0..23 */
long clock;

        time (&clock);
        return ((localtime (&clock))->tm_hour);
}

short Minute (void)  {      /* Minute 0..59 */
long clock;

        time (&clock);
        return ((localtime (&clock))->tm_min);
}

short Second (void) {       /* Sekunde 0..59 */
long clock;

        time (&clock);
        return ((localtime (&clock))->tm_sec);
}

