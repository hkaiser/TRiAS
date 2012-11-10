/*
   LTTWN.H - twain module header file
   Copyright (c) 1991-2000 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTTWN_H_
#define _LTTWN_H_

#include "ltkrn.h"

#define _HEADER_ENTRY_
#include "ltpck.h"

/*
   Flags for L_TwainAcquireExt
*/
#define TWAIN_SHOWUI               0x0001 /* Show the User Interface */
#define TWAIN_SHOWSTATUS           0x0002 /* Show the Status Indicator, if it
                                             is selectable */
#define TWAIN_NATIVEXFER           0x0004 /* Use native transfer */
#define TWAIN_KEEPOPEN             0x0008 /* Keep the data source open */

#define TWAIN_UPDATE_DEFAULTS_ONLY 0x0010 /* Update only properties with the default values */
#define TWAIN_UPDATE_NON_DEFAULTS  0x0020 /* Update only properties with non-default values */
#define TWAIN_UPDATE_ALL (TWAIN_UPDATE_DEFAULTS_ONLY | TWAIN_UPDATE_NON_DEFAULTS)

#define TWAIN_QUICK_UPDATE         0x0040 /* Just update the settings to be used the next time you do TwainAcquire */
#define TWAIN_CACHE_SOURCE         0x0080 /* Scan once and keep the data source open after each scan - faster scanning */

#define TWAIN_FILEXFER             0x0100 /* Use file transfer */

/*
   Flags for TWAINPROPERTIES
*/
#define TWAIN_PIX_DEFAULT         -1   /* Use default type, bits per pixel. */
#define TWAIN_PIX_HALF             0   /* Halftone, 1 bit per pixel. */
#define TWAIN_PIX_GRAY             1   /* GrayScale, 4 or 8 bits per pixel,
                                          the largest supported value. */
#define TWAIN_PIX_RGB              2   /* Color, 24 bits per pixel. */
#define TWAIN_PIX_PALETTE          3   /* Color, 4 or 8 bits per pixel, the
                                          largest supported value. */
#define TWAIN_PIX_LAST             3

#define TWAIN_DEFAULT_BRIGHTNESS    2000
#define TWAIN_DEFAULT_CONTRAST      2000
#define TWAIN_DEFAULT_ORIENTATION   -1

#define TWAIN_FEEDER_DONTCARE       2

#define TWAIN_FORMAT_ABORT        -1
#define TWAIN_FORMAT_CONTINUE      1
#define TWAIN_FORMAT_SET           2

enum
{
   TWAIN_ROT0,
   TWAIN_ROT90,
   TWAIN_ROT180,
   TWAIN_ROT270,
   TWAIN_PORTRAIT = TWAIN_ROT0,
   TWAIN_LANDSCAPE = TWAIN_ROT270
};

/* Use the TWAIN source's default value */
#define TWAIN_DEFAULT               2000
/* The source does not support this feature */
#define TWAIN_UNSUPPORTED           2001

enum
{
   TWAIN_DUPLEX_NONE,
   TWAIN_DUPLEX_1PASS,
   TWAIN_DUPLEX_2PASS,
};

/*
 TWAIN.H file format constants--used for file mode transfer
*/
#ifndef TWFF_TIFF
#define TWFF_TIFF        0    /* Tagged Image File Format     */
#endif

#ifndef TWFF_PICT
#define TWFF_PICT        1    /* Macintosh PICT               */
#endif

#ifndef TWFF_BMP
#define TWFF_BMP         2    /* Windows Bitmap               */
#endif

#ifndef TWFF_XBM
#define TWFF_XBM         3    /* X-Windows Bitmap             */
#endif

#ifndef TWFF_JFIF
#define TWFF_JFIF        4    /* JPEG File Interchange Format */
#endif

#ifndef TWFF_FPX
#define TWFF_FPX         5    /* Flash Pix                    */
#endif

#ifndef TWFF_TIFFMULTI
#define TWFF_TIFFMULTI   6    /* Multi-page tiff file         */
#endif

#ifndef TWFF_PNG
#define TWFF_PNG         7
#endif

#ifndef TWFF_SPIFF
#define TWFF_SPIFF       8
#endif

#ifndef TWFF_EXIF
#define TWFF_EXIF        9
#endif

#define TWFF_DEFAULT   99


/*
   TWAIN Properties structure
*/
typedef struct tagTWAINPROPERTIES
{
   L_UINT32 lSize;                     /* the size of TWAINPROPERTIES - use sizeof(TWAINPROPERTIES) */
   L_TCHAR AppManufacturer[36];
   L_TCHAR AppProdFamily[36];
   L_TCHAR AppProdName[36];
   L_TCHAR SourceName[36];
   L_INT nMaxPages;
   L_INT nPixelType;
   L_INT nBits;
   L_INT nRes;
   L_INT32 nXPos;
   L_INT32 nYPos;
   L_INT32 nWidth;
   L_INT32 nHeight;
   L_INT    nBrightness;
   L_INT    nContrast;
   L_INT    nOrientation;
   L_INT    nFeederEnabled;   /* enable the auto feeder */
   L_INT    nEnableAutoFeed;  /* enable the automatic feeding */
   L_INT    nDuplex;          /* detect whether duplex scanning is possible */
   L_INT    nEnableDuplex;    /* enable the duplex scanning */
#ifdef WIN32
   L_UINT32 dwReserved[3];    /* reserved fields, do not use */
#else
   L_UINT32 dwReserved[4];    /* reserved fields, do not use */
#endif
} TWAINPROPERTIES, L_FAR * pTWAINPROPERTIES;

/*
   callback typedefs
*/
typedef L_INT (pEXT_CALLBACK ENUMSOURCECALLBACK) (L_TCHAR L_FAR *, L_INT, L_VOID L_FAR *);
typedef L_INT (pEXT_CALLBACK TWAINCALLBACK) (pBITMAPHANDLE, L_VOID L_FAR *);
typedef L_INT (pEXT_CALLBACK TWAINFILEFORMATCALLBACK) (L_UINT, L_BOOL, L_VOID L_FAR *);
typedef L_INT (pEXT_CALLBACK TWAINFILETRANSFERCALLBACK) (L_TCHAR L_FAR *,  L_VOID L_FAR *);

/*
   function prototypes
*/

L_INT EXT_FUNCTION L_TwainAcquire (HWND hWnd, pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_TwainAcquireExt (HWND hWnd,
                                       pBITMAPHANDLE pBitmap,
                                       L_UINT uFlags,
                                       TWAINCALLBACK pfnCallback,
                                       L_VOID L_FAR * pUserData);

L_INT EXT_FUNCTION L_TwainCloseSession(HWND hWnd);

L_INT EXT_FUNCTION L_TwainEnumSources (HWND hWnd,
                                        ENUMSOURCECALLBACK pfnCallback,
                                        L_VOID L_FAR * pUserData);

L_INT EXT_FUNCTION L_TwainSelect (HWND hWnd);

L_INT EXT_FUNCTION L_TwainSetProps (HWND hWnd, pTWAINPROPERTIES pTwain, L_UINT32 uFlags);
L_INT EXT_FUNCTION L_TwainGetProps (pTWAINPROPERTIES pTwain);

L_BOOL EXT_FUNCTION L_IsTwainAvailable(HWND hWnd);

L_INT EXT_FUNCTION L_TwainAcquireFile(  HWND hWnd,
                                        L_TCHAR L_FAR * pszFile,
                                        L_UINT uFormat,
                                        L_UINT uFlags,
                                        TWAINFILETRANSFERCALLBACK pFileTransferCallback,
                                        L_VOID L_FAR * lpUserDataFileTransfer,
                                        TWAINFILEFORMATCALLBACK pFileFormatCallback,
                                        L_VOID L_FAR * pUserDataFileFormat
                                       );

#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif                          /* _LTTWN_H_ */
