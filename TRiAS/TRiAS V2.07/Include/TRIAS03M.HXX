// Manifestkonstanten für Trias03 ---------------------------------------------
// File TRIAS03M.HXX

#if !defined(_TRIAS03M_HXX)
#define _TRIAS03M_HXX

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

#define EXPORT03	__export
#define _ENTRY		/*__export*/
#define _TRIAS03_ENTRY

#else // WIN32

#define EXPORT03

#if defined(__TRIAS03DLL__)
#define _ENTRY		__declspec(dllimport)
#define _TRIAS03_ENTRY	__declspec(dllexport)
#else 	// __TRIAS03DLL__
#define _ENTRY		__declspec(dllimport)
#define _TRIAS03_ENTRY	__declspec(dllimport)
#endif	// __TRIAS03DLL__

#endif	// WIN32

#endif  // _TRIAS03M_HXX
