


#ifndef _watcmdll_h_ /* Sat Oct 12 11:16:34 1996 */
#define _watcmdll_h_


#if defined(BUILD_DLL)
#    if defined(__MS_WINDOWS__) || defined(WINDOWS) || defined(__MS_WIN32__)
#        define YACL_BASE     __export
#        define YACL_BASEFUNC __export
#    elif defined(__OS2__)
#        define YACL_BASE     _export
#        define YACL_BASEFUNC _export
#    endif
#elif defined(USE_YACL_DLL) && defined(__MS_WIN32__)
#    define YACL_BASE     _import
#    define YACL_BASEFUNC _import
#endif


#endif /* _watcmdll_h_ */
