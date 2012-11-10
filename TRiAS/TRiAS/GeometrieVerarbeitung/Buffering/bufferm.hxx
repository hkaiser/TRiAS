// Allgemeine Manifestkonstanten ----------------------------------------------
// File: BUFFERM.HXX

#if !defined(_BUFFERM_HXX)
#define _BUFFERM_HXX

#define _BUFFER_EXPORT

#if defined(__BUFFERDLL__)
#define _BUFFER_ENTRY	__declspec(dllexport)
#else 	// __BUFFERDLL__
#define _BUFFER_ENTRY	__declspec(dllimport)
#endif	// __BUFFERDLL__

#endif // _BUFFERM_HXX
