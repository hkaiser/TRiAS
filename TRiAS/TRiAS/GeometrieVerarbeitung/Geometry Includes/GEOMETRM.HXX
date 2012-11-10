// Allgemeine Manifestkonstanten ----------------------------------------------
// File: GeometrM.hxx

#if !defined(_GEOMETRM_HXX)
#define _GEOMETRM_HXX

#define _GEOMETR_EXPORT

#if defined(__GEOMETRDLL__)
#define _GEOMETR_ENTRY	__declspec(dllexport)
#else 	// __GEOMETRDLL__
#define _GEOMETR_ENTRY	__declspec(dllimport)
#endif	// __GEOMETRDLL__

#endif // _GEOMETRM_HXX
