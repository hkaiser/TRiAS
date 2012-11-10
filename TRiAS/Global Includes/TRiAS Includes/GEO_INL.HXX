// Inline-Funktionen für GEO_OBJEKTE ------------------------------------------
// File: GEO_INL.HXX

// IRISWIN: %W%	%E%

#ifndef _GEO_INL_HXX
#define _GEO_INL_HXX

typedef long KoOrd;

// Hilfsfunktionen ------------------------------------------------------------
inline short shortMin (short x, short y) { return (((x) < (y)) ? x : y); }
inline short shortMax (short x, short y) { return (((x) > (y)) ? x : y); }
inline long longMin (long x, long y) { return (((x) < (y)) ? x : y); }
inline long longMax (long x, long y) { return (((x) > (y)) ? x : y); }

inline KoOrd KoOrdAbs (KoOrd x) { return (((x) >= 0) ? (x) : -(x)); }
inline KoOrd KoOrdMin (KoOrd x, KoOrd y) { return (((x) < (y)) ? x : y); }
inline KoOrd KoOrdMax (KoOrd x, KoOrd y) { return (((x) > (y)) ? x : y); }

#endif // _GEO_INL_HXX
