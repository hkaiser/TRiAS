// Manifestkonstanten für Trias02 ---------------------------------------------
// File TRIAS02M.HXX

#if !defined(_TRIAS02M_HXX)
#define _TRIAS02M_HXX

#if !defined(FUNCTYPE)
#if defined(WIN16)
#if defined(DLL)
#define FUNCTYPE __pascal
#else
#define FUNCTYPE __cdecl
#endif
#else // WIN16
#define FUNCTYPE
#endif // WIN16
#endif // FUNCTYPE

#if defined(WIN16)

#define EXPORT02	__export
#define _ENTRY		/*__export*/
#define _TRIAS02_ENTRY

#else // WIN16

#define EXPORT02

#if defined(__TRIAS02DLL__)
#define _ENTRY		__declspec(dllimport)
#define _TRIAS02_ENTRY	__declspec(dllexport)
#else 	// __TRIAS02DLL__
#define _ENTRY		__declspec(dllimport)
#define _TRIAS02_ENTRY	__declspec(dllimport)
#endif	// __TRIAS02DLL__

#endif	// WIN16

#endif  // _TRIAS02M_HXX
