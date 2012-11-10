// Allgemeine Manifestkonstanten ----------------------------------------------
// File: TopoRelM.hxx

#if !defined(_TOPORELM_HXX)
#define _TOPORELM_HXX

#define _TOPOREL_EXPORT

#if defined(__TOPORELDLL__)
#define _TOPOREL_ENTRY   __declspec(dllexport)
#else   // __TOPORELDLL__
#define _TOPOREL_ENTRY   __declspec(dllimport)
#endif  // __TOPORELDLL__

#endif // _TOPORELM_HXX
