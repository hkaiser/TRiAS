

#ifndef _msvcdll_h_ /* Sat Oct 12 11:16:55 1996 */
#define _msvcdll_h_


#if defined(BUILD_DLL)
#    define YACL_BASE     _declspec(dllexport)
#    define YACL_BASEFUNC _declspec(dllexport)
#elif defined(USE_YACL_DLL)
#    define YACL_BASE     _declspec(dllimport)
#    define YACL_BASEFUNC _declspec(dllimport)
#endif


#endif /* _msvcdll_h_ */
