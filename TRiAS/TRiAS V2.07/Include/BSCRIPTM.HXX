// Manifestkonstanten für Trias02 ---------------------------------------------
// File BSCRIPTM.HXX

#if !defined(_BSCRIPTM_HXX)
#define _BSCRIPTM_HXX

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

#define BSCRIPTEXPORT	__export
#define _ENTRY		/*__export*/
#define _BSCRIPT_ENTRY

#else // WIN32

#define BSCRIPTEXPORT

#if defined(__BSCRIPTDLL__)
#define _ENTRY		__declspec(dllimport)
#define _BSCRIPT_ENTRY	__declspec(dllexport)
#else 	// __BSCRIPTDLL__
#define _ENTRY		__declspec(dllimport)
#define _BSCRIPT_ENTRY	__declspec(dllimport)
#endif	// __BSCRIPTDLL__

#endif	// WIN32

#endif  // _BSCRIPTM_HXX
