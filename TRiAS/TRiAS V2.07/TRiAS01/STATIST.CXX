/* Dummy-Datendefinitionen fuer Statistikuntersuchungen         */
/* File: STATIST.C              last update: 21. November 1989  */

#include "trias01p.hxx"

#if defined(STATISTICS)

int write_cnt = 0;      /* Zaehler fuer Schreibzugriffe */
int read_cnt = 0;       /* Zaehler fuer Lesezugriffe */
int open_cnt = 0;       /* Zaehler fuer Dateioperation: Oeffnen */
int close_cnt = 0;      /* Zaehler fuer Dateioperationen: Schlieszen */
int statistics = 0;

#endif // STATISTICS
 
