// Manifestkonstanten für Trias03 ---------------------------------------------
// File TRIASM.HXX

#if !defined(_TRIASM_HXX)
#define _TRIASM_HXX

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

#define EXPORTTRIAS	__export
#define _ENTRY		/*__export*/
#define _TRIAS_ENTRY

#else // WIN32

#define EXPORTTRIAS

#if defined(__TRIASEXE__)
#define _ENTRY		__declspec(dllimport)
#define _TRIAS_ENTRY	__declspec(dllexport)
#else 	// __TRIASEXE__
#define _ENTRY		__declspec(dllimport)
#define _TRIAS_ENTRY	__declspec(dllimport)
#endif	// __TRIASEXE__

#endif	// WIN32

#endif  // _TRIASM_HXX
