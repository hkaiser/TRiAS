// Allgemeine Manifestkonstanten ----------------------------------------------
// File: RASTERM.HXX

#if !defined(_RASTERM_HXX)
#define _RASTERM_HXX

#define _RASTER_EXPORT

#if defined(__RASTERDLL__)
#define _RASTER_ENTRY   __declspec(dllexport)
#else   // __RASTERDLL__
#define _RASTER_ENTRY   __declspec(dllimport)
#endif  // __RASTERDLL__

#endif // _RASTERM_HXX
