#ifndef _DOS
#error  lafx_dos.h must only be included as the _DOS configuration file
#endif
#ifdef _WINDOWS
#error  lafx_dos.h must not be included with a _WINDOWS configuration
#endif

///////////////////////////////////////////////////////////////////////
// Windows-Typen auch unter DOS verfÅgbar machen
///////////////////////////////////////////////////////////////////////

typedef struct tagPOINT {
	int	x;
	int	y;
} POINT;

typedef struct tagSIZEL {
	long	cx;
	long	cy;
} SIZEL;

typedef struct tagPOINTL {
	long x;
	long y;
} POINTL;

typedef struct tagRECTL {
	long left;
	long top;
	long right;
	long bottom;
} RECTL;
