#if !defined(MSWIND) && !defined(__386__)
#if !defined(FAR)
#define FAR _far
#endif
#elif (defined(__WATCOMC__) && defined(__386__)) || defined(WIN32)
// alle Speichermodellspezifika herausnehmen
#if !defined(FAR)
#define FAR
#undef _far
#undef far
#undef _huge
#undef huge
#define _far
#define far
#define _huge 
#define huge
#endif
#endif

#if !defined(FUNCTYPE)
#if defined(DLL)
#define FUNCTYPE _pascal
#else
#define FUNCTYPE _cdecl
#endif
#endif

