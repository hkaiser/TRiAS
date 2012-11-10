// Allgemeine Manifestkonstanten
// File: GEOREINM.HXX

#if !defined(_GEOREINM_HXX)
#define _GEOREINM_HXX

#define _GEOREIN_EXPORT

#if defined(__GEOREINDLL__)
#define _GEOREIN_ENTRY	__declspec(dllexport)
#else 	// __GEOREINDLL__
#define _GEOREIN_ENTRY	__declspec(dllimport)
#endif	// __GEOREINDLL__

#endif // _GEOREINM_HXX
