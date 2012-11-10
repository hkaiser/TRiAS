// Allgemeine Manifestkonstanten ----------------------------------------------
// File: ABSTANDM.HXX

#if !defined(_ABSTANDM_HXX)
#define _ABSTANDM_HXX

#define _ABSTAND_EXPORT

#if defined(__ABSTANDDLL__)
#define _ABSTAND_ENTRY	__declspec(dllexport)
#else 	// __ABSTANDDLL__
#define _ABSTAND_ENTRY	__declspec(dllimport)
#endif	// __ABSTANDDLL__

#endif // _ABSTANDM_HXX
