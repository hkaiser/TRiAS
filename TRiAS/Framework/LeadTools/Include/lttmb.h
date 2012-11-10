/*
   LTTMB.H - LEAD Thumbnail Browser module header file
   Copyright (c) 1991-2000 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTTMB_H_
#define _LTTMB_H_

#include "ltkrn.h"
#include "ltimg.h"
#include "ltfil.h"
//#include <stdlib.h>
#include <winerror.h>

#define _HEADER_ENTRY_
#include "ltpck.h"

/* callback typedefs */
typedef L_INT (pEXT_CALLBACK BROWSEDIRCALLBACK) (pBITMAPHANDLE, L_TCHAR L_FAR *, pFILEINFO, L_INT, L_INT, L_VOID L_FAR *);

#define BROWSE_LOADING 2 /* used to indicate image is being loaded */
#define BROWSE_SKIPPED 3 /* used to indicate image was skipped b/c
                            it was larger than the specified range */
#define BROWSE_PRELOAD 4 /* used to indicate image is about to be
                            loaded */

/* external prototypes */
L_INT EXT_FUNCTION L_BrowseDir( L_TCHAR L_FAR* pszPath,
                   L_TCHAR L_FAR* pszFilter,
                   L_INT nThumbWidth,
                   L_INT nThumbHeight,
                   L_INT nBits,
                   L_UINT32 uCRFlags,
                   L_BOOL bMaintainAspect,
                   L_BOOL bForceSize,
                   COLORREF crBackColor,
                   L_BOOL bLoadStamp,
                   L_BOOL bResample,
                   L_BOOL bStopOnError,
                   L_BOOL bIncludeSubDirs,
                   L_BOOL bExpandMultipage,
                   L_INT32 lSizeDisk,
                   L_INT32 lSizeMem,
                   BROWSEDIRCALLBACK pfnBrowseDirCB,
                   L_VOID L_FAR * pUserData );

#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif                          /* _LTTMB_H_ */



