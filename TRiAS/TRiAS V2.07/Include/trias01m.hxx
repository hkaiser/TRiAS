// Manifestkonstanten für Trias02 ---------------------------------------------
// File TRIAS01M.HXX

#if !defined(_TRIAS01M_HXX)
#define _TRIAS01M_HXX

#if !defined(FUNCTYPE)
#if !defined(WIN32)
#if defined(DLL)
#define FUNCTYPE __pascal
#else
#define FUNCTYPE __cdecl
#endif
#else // WIN32
#define FUNCTYPE
#endif // WIN32
#endif // FUNCTYPE

#if !defined(WIN32)

#define EXPORT01	__export
#define _ENTRY		/*__export*/
#define _TRIAS01_ENTRY

#else // WIN32

#define EXPORT01

#if defined(__TRIAS01DLL__)
#define _ENTRY		__declspec(dllimport)
#define _TRIAS01_ENTRY	__declspec(dllexport)
#else 	// __TRIAS02DLL__
#define _ENTRY		__declspec(dllimport)
#define _TRIAS01_ENTRY	__declspec(dllimport)
#endif	// __TRIAS02DLL__

#endif	// WIN32

#endif  // _TRIAS01M_HXX
