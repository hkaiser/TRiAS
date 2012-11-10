// Manifestkonstanten für Xtensn.Lib ------------------------------------------
// File XTENSNM.HXX

#if !defined(_XTENSNM_HXX)
#define _XTENSNM_HXX

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

#define _XTENSN_EXPORT	__export
#define _ENTRY		/*__export*/
#define _XTENSN_ENTRY

#else // WIN32

#define _XTENSN_EXPORT

#if defined(__XTENSNDLL__)
#define _ENTRY		__declspec(dllimport)
#define _XTENSN_ENTRY	__declspec(dllexport)
#else 	// __XTENSNDLL__
#define _ENTRY		__declspec(dllimport)
#define _XTENSN_ENTRY	__declspec(dllimport)
#endif	// __XTENSNDLL__

#endif	// WIN32

#endif  // _XTENSNM_HXX
