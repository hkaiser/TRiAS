/* Windowzugriff 2-Dimensional (Flaechen/Kanten)                */
/* Fortran-Schnittstelle (UNIX)                                 */
/* File: HTWIND_F.C                                             */

#include "trias01p.hxx"

#ifdef vms
#define htwind_ htwind
#endif

#if defined(unix) || defined(msdos) || defined(_WINDOWS)

extern "C" long FUNCTYPE EXPORT01 htwind_ (HPROJECT hPr, long *cont, long (* fkt)(DB_ADDR *, long *), long *keyno)
// INT *cont;      /* Objektcontainer */
// INT (*fkt)(DB_ADDR *, ...);	/* Aktion */
// INT *keyno;     /* Schluesselnummer */
{
	return ((long)hwindow (hPr, (WINDOW *)cont, (long (*)(DB_ADDR *,...))fkt, (short)*keyno));
}

#endif
