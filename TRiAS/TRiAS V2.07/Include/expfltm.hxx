// Manifestkonstanten für Exportfilter ----------------------------------------
// File EXPFLTM.HXX

#if !defined(_EXPFLTM_HXX)
#define _EXPFLTM_HXX

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

#define EXPORTFLT	__export
#define _ENTRY		/*__export*/
#define _EXPFLT_ENTRY

#else // WIN32

#define EXPORTFLT

#if defined(__EXPFLTDLL__)
#define _ENTRY		__declspec(dllimport)
#define _EXPFLT_ENTRY	__declspec(dllexport)
#else 	// __EXPFLTDLL__
#define _ENTRY		__declspec(dllimport)
#define _EXPFLT_ENTRY	__declspec(dllimport)
#endif	// __EXPFLTDLL__

#endif	// WIN32

#endif  // _EXPFLTM_HXX
