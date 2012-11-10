// Definition von bool als Datentyp -------------------------------------------
// File: BOOL.H

#if !defined(_BOOL_H)
#define _BOOL_H

#ifdef __cplusplus

#if (_MSC_VER <= 1020) || _FORCE_BOOL_DEFINE		// nur für 'alte' Versionen
#if !defined(_BOOL_DEFINED)

#undef bool
#undef true
#undef false

#define bool    int
#define true    (1)
#define false   (0)

#define _BOOL_DEFINED
#define OS_OMIT_BOOL    // für OSpace

#endif // _BOOL_DEFINED
#endif // (_MSC_VER <= 1020) || _FORCE_BOOL_DEFINE

#endif  /* __cplusplus */

#endif // _BOOL_H
