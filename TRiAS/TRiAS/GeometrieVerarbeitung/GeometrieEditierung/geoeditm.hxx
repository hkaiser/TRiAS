// Allgemeine Manifestkonstanten
// File: GEOEDITM.HXX

#if !defined(_GEOEDITM_HXX)
#define _GEOEDITM_HXX

#if !defined(WIN32)

#define _GEOEDIT_EXPORT	__export
#define _GEOEDIT_ENTRY

#else // WIN32

#define _GEOEDIT_EXPORT

#if defined(__GEOEDITDLL__)
#define _GEOEDIT_ENTRY	__declspec(dllexport)
#else 	// __GEOEDITDLL__
#define _GEOEDIT_ENTRY	__declspec(dllimport)
#endif	// __GEOEDITDLL__

#define __huge

#endif	// WIN32


#endif // _GEOEDITM_HXX
