// Manifestkonstanten für CTF's -----------------------------------------------
// File CTFM.HXX

#if !defined(_CTFM_HXX)
#define _CTFM_HXX

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

#define EXPORTCTF	__export
#define _ENTRY		/*__export*/
#define _CTF_ENTRY

#else // WIN16

#define EXPORTCTF

#if defined(__CTF_DLL__)
#define _ENTRY		__declspec(dllimport)
#define _CTF_ENTRY	__declspec(dllexport)
#else 	// __CTF_DLL__
#define _ENTRY		__declspec(dllimport)
#define _CTF_ENTRY	__declspec(dllimport)
#endif	// __CTF_DLL__

#endif	// WIN16

#endif  // _CTFM_HXX
