// Manifestkonstanten für Xtensn.Lib ------------------------------------------
// File XTENSNM.HXX

#if !defined(_XTENSNM_HXX)
#define _XTENSNM_HXX

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

#define _XTENSN_EXPORT	__export
#define _ENTRY		/*__export*/
#define _XTENSN_ENTRY

#else // WIN16

#define _XTENSN_EXPORT

#if defined(__XTENSNDLL__)
#define _ENTRY		__declspec(dllimport)
#define _XTENSN_ENTRY	__declspec(dllexport)
#else 	// __XTENSNDLL__
#define _ENTRY		__declspec(dllimport)
#define _XTENSN_ENTRY	__declspec(dllimport)
#endif	// __XTENSNDLL__

#endif	// WIN16

#endif  // _XTENSNM_HXX
