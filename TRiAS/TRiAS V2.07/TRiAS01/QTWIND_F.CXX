/* Windowzugriff 1-Dimensional (Punkte)                         */
/* Fortran-Schnittstelle (UNIX)                                 */
/* File: QTWIND_F.C                                             */

#include "trias01p.hxx"

#ifdef vms
#define qtwind_ qtwind
#endif

#if defined(unix) || defined(msdos) || defined(_WINDOWS)

extern "C" long FUNCTYPE EXPORT01 qtwind_ (HPROJECT hPr, long *cont, long (* fkt)(DB_ADDR *, ...), long *keyno)
// INT *cont;      /* Objektcontainer */
// INT (*fkt)(DB_ADDR *, ...);	/* Aktion */
// INT *keyno;     /* Schluesselnummer */
{
	return ((long)qwindow (hPr, (WINDOW *)cont, (long (*)(DB_ADDR *, ...))fkt, (short)*keyno));
}

#endif
