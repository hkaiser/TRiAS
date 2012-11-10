// Manifestkonstanten für Trias02 ---------------------------------------------
// File BSCRIPTM.HXX

#if !defined(_BSCRIPTM_HXX)
#define _BSCRIPTM_HXX

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

#define BSCRIPTEXPORT	__export
#define _ENTRY		/*__export*/
#define _BSCRIPT_ENTRY

#else // WIN16

#define BSCRIPTEXPORT

#if defined(__BSCRIPTDLL__)
#define _ENTRY		__declspec(dllimport)
#define _BSCRIPT_ENTRY	__declspec(dllexport)
#else 	// __BSCRIPTDLL__
#define _ENTRY		__declspec(dllimport)
#define _BSCRIPT_ENTRY	__declspec(dllimport)
#endif	// __BSCRIPTDLL__

#endif	// WIN16

#endif  // _BSCRIPTM_HXX
