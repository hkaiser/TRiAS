// Allgemeine Manifestkonstanten ----------------------------------------------
// File: ObjOperM.hxx

#if !defined(_OBJOPERM_HXX)
#define _OBJOPERM_HXX

#define _OBJOPER_EXPORT

#if defined(__OBJOPERDLL__)
#define _OBJOPER_ENTRY	__declspec(dllexport)
#else 	// __OBJOPERDLL__
#define _OBJOPER_ENTRY	__declspec(dllimport)
#endif	// __OBJOPERDLL__

#endif // _OBJOPERM_HXX
