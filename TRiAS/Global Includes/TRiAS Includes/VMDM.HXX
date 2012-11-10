// Manifestkonstanten für Visualisierungsmodule -------------------------------
// File VMDM.HXX

#if !defined(_VMDM_HXX)
#define _VMDM_HXX

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

#define _VMD_EXPORT	__export
#define _ENTRY		/*__export*/
#define _VMD_ENTRY

#else // WIN16

#define _VMD_EXPORT

#if defined(__VMD_DLL__)
#define _ENTRY		__declspec(dllimport)
#define _VMD_ENTRY	__declspec(dllexport)
#else 	// __VMD_DLL__
#define _ENTRY		__declspec(dllimport)
#define _VMD_ENTRY	__declspec(dllimport)
#endif	// __VMD_DLL__

#endif	// WIN16

#endif  // _VMDM_HXX
