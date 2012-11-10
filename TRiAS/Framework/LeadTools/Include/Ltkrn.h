/*[]=====================================================================[]*/
/*[]     LeadTools Run Time Library - Version 9                          []*/
/*[]                                                                     []*/
/*[]                                                                     []*/
/*[]     Copyright (c) 1991-2000 LEAD Technologies, Inc.                 []*/
/*[]     All Rights Reserved.                                            []*/
/*[]=====================================================================[]*/

/*
   LTKRN.H - kernel module header file
*/

#ifndef _LTKRN_H_
#define _LTKRN_H_

#include "lttyp.h"
#include "lterr.h"

#define _HEADER_ENTRY_
#include "ltpck.h"

/*
   flags for L_UnlockSupport and L_IsSupportLocked
*/
// L_SUPPORT_XXX constants
#include "ltlck_.h"


#if !defined(_WIN32_WCE)
/*
   flags for L_CombineBitmapWarp
*/
#define CBW_BILINEAR   0x0001
#define CBW_RESERVED1  0x0002
#define CBW_RESERVED2  0x0004
#define CBW_RESERVED3  0x0008
#define CBW_RESERVED4  0x0010
#define CBW_RESERVED5  0x0020
#define CBW_RESERVED6  0x0040
#define CBW_RESERVED7  0x0080
#define CBW_RESERVED8  0x0100
#define CBW_RESERVED9  0x0200
#define CBW_ALLFLAGS   (CBW_BILINEAR| CBW_RESERVED1| CBW_RESERVED2 | CBW_RESERVED3 | CBW_RESERVED4 |CBW_RESERVED5 |CBW_RESERVED6 |CBW_RESERVED7 |CBW_RESERVED8 |CBW_RESERVED9)
#endif /* _WIN32_WCE */

/*
   flags for L_ScrambleBitmap
*/
#define SB_ENCRYPT    0x0001
#define SB_DECRYPT    0x0002
#define SB_INTERSECT  0x0004
#define SB_RESERVED3  0x0008
#define SB_RESERVED4  0x0010
#define SB_RESERVED5  0x0020
#define SB_RESERVED6  0x0040
#define SB_RESERVED7  0x0080
#define SB_RESERVED8  0x0100
#define SB_RESERVED9  0x0200
#define SB_ALLFLAGS   (SB_ENCRYPT| SB_DECRYPT| SB_INTERSECT | SB_RESERVED3 | SB_RESERVED4 |SB_RESERVED5 |SB_RESERVED6 |SB_RESERVED7 |SB_RESERVED8 |SB_RESERVED9)



/*
   flags for L_ColorResBitmap
*/
#define CRF_FIXEDPALETTE        0x0001 /* versus custom palette */
#define CRF_OPTIMIZEDPALETTE    0x0002 /* versus fixed palette */
#define CRF_IDENTITYPALETTE     0x0008 /* versus ALL 256 colors */
#define CRF_USERPALETTE         0x0010 /* user generated palette */
#define CRF_FASTMATCHPALETTE    0x0020 /* With user, for fast color match */
#define CRF_NETSCAPEPALETTE     0x0040 /* use netscape fixed palette */
#define CRF_BYTEORDERBGR        0x0004 /* versus RGB */
#define CRF_BYTEORDERRGB        0x0000 /* versus BGR */
#define CRF_BYTEORDERGRAY       0x0080 /* Convert to grayscale (12 & 16 bit only) */
#define CRF_PALETTEOPTIONS      0x03FF /* Mask to find palette option */
#define CRF_USERHPALETTE        0x0100 /* user generated palette */
#define CRF_SLOWMATCH           0x0200 /* use with CRF_OPTIMIZEDPALETTE to use a slower but more accurate match */
#define CRF_FAVORPURECOLORS     0x0400 /* Give colors that are very numerous palette entries of their own */
#define CRF_BYTEORDERROMM       0x0800 /* ROMM color space (BGR wide gamut) */

#define CRF_NODITHERING              0x00000000 /* No Dithering */
#define CRF_FLOYDSTEINDITHERING      0x00010000 /* Floyd Stein Dithering */
#define CRF_STUCKIDITHERING          0x00020000 /* Stucki Dithering */
#define CRF_BURKESDITHERING          0x00030000 /* Burkes Dithering */
#define CRF_SIERRADITHERING          0x00040000 /* Sierra Dithering */
#define CRF_STEVENSONARCEDITHERING   0x00050000 /* Stevenson Arce Dithering */
#define CRF_JARVISDITHERING          0x00060000 /* Jarvis Dithering */
#define CRF_ORDEREDDITHERING         0x00070000 /* Ordered Dithering */
#define CRF_CLUSTEREDDITHERING       0x00080000 /* Clustered Dithering */
#define CRF_DITHERINGOPTIONS         0x00FF0000 /* Mask to find dither option */

#define RGB_RESERVED                 0x01 /* Do not map to the entry */
#define RGB_EMPTY                    0x02 /* The entry is empty */

/*
   flags for L_CombineBitmap
*/
#define CB_SRC_NOP 0x00000000
#define CB_SRC_NOT 0x00000001
#define CB_SRC_0   0x00000002
#define CB_SRC_1   0x00000003
#define CB_DST_NOP 0x00000000
#define CB_DST_NOT 0x00000010
#define CB_DST_0   0x00000020
#define CB_DST_1   0x00000030
#define CB_OP_AND    0x00000000
#define CB_OP_OR     0x00000100
#define CB_OP_XOR    0x00000200
#define CB_OP_ADD    0x00000300
#define CB_OP_SUBSRC 0x00000400
#define CB_OP_SUBDST 0x00000500
#define CB_OP_MUL    0x00000600
#define CB_OP_DIVSRC 0x00000700
#define CB_OP_DIVDST 0x00000800
#define CB_OP_AVG    0x00000900
#define CB_OP_MIN    0x00000A00
#define CB_OP_MAX    0x00000B00
#define CB_RES_NOP 0x00000000
#define CB_RES_NOT 0x00001000
#define CB_RES_0   0x00002000
#define CB_RES_1   0x00003000

// useful define for copying the source to the destination
#define L_SRC_COPY (CB_DST_0 | CB_SRC_NOP | CB_OP_OR)

/*
   return values of L_IsGrayScaleBitmap
*/
#define GRAY_NO               0  /* not grayscale */
#define GRAY_ORDEREDNORMAL    1  /* contains a normally ordered grayscale palette */
#define GRAY_ORDEREDINVERSE   2  /* contains a reverse ordered grayscale palette */
#define GRAY_NOTORDERED       3  /* contains a non-ordered grayscale palette */

/*
   flags for L_VersionInfo
*/
#define TOOLKIT_LEVEL_DOCUMENT       0x00 /* Document Toolkit. */
#define TOOLKIT_LEVEL_RASTER         0x01 /* Raster Toolkit. */
#define TOOLKIT_LEVEL_MEDICAL        0x02 /* Medical Toolkit. */

/*
   Dithering methods. To be used for DitheringMethod in BITMAPHANDLE.
*/
#define NO_DITHERING              0
#define FLOYD_STEIN_DITHERING     1
#define STUCKI_DITHERING          2
#define BURKES_DITHERING          3
#define SIERRA_DITHERING          4
#define STEVENSON_ARCE_DITHERING  5
#define JARVIS_DITHERING          6
#define ORDERED_DITHERING         7
#define CLUSTERED_DITHERING       8
#define LAST_DITHERING            8

/*
   bitmap data colors order
*/
#define ORDER_RGB                0 /* RGB ordering */
#define ORDER_BGR                1 /* BGR ordering */
#define ORDER_GRAY               2 /* Gray pixels */
#define ORDER_RGBORGRAY          3 /* Valid only for L_LoadXXX functions - gray or RGB */
#define ORDER_BGRORGRAY          4 /* Valid only for L_LoadXXX functions - gray or BGR */
#define ORDER_ROMM               5 /* BGR Wide gamut format */
#define ORDER_BGRORGRAYORROMM    6 /* Valid only for L_LoadXXX functions - gray or BGR or ROMM */

/*
   view perspectives
*/
#define TOP_LEFT              0  /* Top-left of image is first in memory */
#define BOTTOM_LEFT           2  /* Bottom-left of image is first in memory */

#define TOP_RIGHT             1  /* Top-right of image is first in memory */
#define BOTTOM_LEFT180        1  /* TOP_RIGHT is BOTTOM_LEFT rotated clockwise by 180 degrees */
#define BOTTOM_RIGHT          3  /* Bottom-right of image is first in memory */
#define TOP_LEFT180           3  /* BOTTOM_RIGHT is TOP_LEFT rotated clockwise by 180 degrees */ 

#define RIGHT_TOP             4  /* First row is the right side, first column is top side */
#define TOP_LEFT90            4  /* RIGHT_TOP is TOP_LEFT rotated clockwise by 90 degrees */ 
#define LEFT_BOTTOM           8  /* First row is the left side, first column is top side */
#define TOP_LEFT270           8  /* LEFT_BOTTOM is TOP_LEFT rotated clockwise by 270 degrees */ 

#define LEFT_TOP              5  /* First row is the left side, first column is the top side */
#define BOTTOM_LEFT90         5  /* LEFT_TOP is BOTTOM_LEFT rotated clockwise by 90 degrees */
#define RIGHT_BOTTOM          7  /* First row is the right side, first column is the bottom side */
#define BOTTOM_LEFT270        7  /* RIGHT_BOTTOM is BOTTOM_LEFT rotated clockwise by 270 degrees */ 

/* helper macros for dealing with rotated bitmap view perspectives */
#define ISBASIC(pBitmap) ((pBitmap)->ViewPerspective == TOP_LEFT || (pBitmap)->ViewPerspective == BOTTOM_LEFT)
#define ISROTATED(pBitmap) ((pBitmap)->ViewPerspective == TOP_LEFT90 || (pBitmap)->ViewPerspective == TOP_LEFT270 || (pBitmap)->ViewPerspective == BOTTOM_LEFT90 || (pBitmap)->ViewPerspective == BOTTOM_LEFT270)
#define ISFLIPPED(pBitmap) ((pBitmap)->ViewPerspective == BOTTOM_LEFT || (pBitmap)->ViewPerspective == BOTTOM_LEFT90 || (pBitmap)->ViewPerspective == BOTTOM_LEFT180 || (pBitmap)->ViewPerspective == BOTTOM_LEFT270)
#define BITMAPWIDTH(pBitmap) (ISROTATED(pBitmap)?(pBitmap)->Height:(pBitmap)->Width)
#define BITMAPHEIGHT(pBitmap) (ISROTATED(pBitmap)?(pBitmap)->Width:(pBitmap)->Height)

/* helper macro to determine whether a bitmap is 12 or 16 bit grayscale */
#define ISGRAY(pBitmap) ((pBitmap)->Order == ORDER_GRAY)

/*
   memory allocation flags
*/
#define TYPE_CONV                0x0001   /* Use conventional memory first */
#define TYPE_USER                0x0002   /* Create a bitmap where the user maintains the data pointer */
#define TYPE_TILED               0x0004   /* Create tiled bitmap first */
#define TYPE_NOTILED             0x0008   /* Do not use tiled bitmaps */
#define TYPE_DISK                0x0080   /* Use Disk (if possible) */
#define TYPE_NODISK              0x0100   /* Do not use disk */
#define TYPE_COMPRESSED          0x0200   /* keep 1 bit images compressed in memory */
#define TYPE_SUPERCOMPRESSED     0x0400   /* keep 24 bit images compressed in memory - slow access */


/*
   playback handle
*/
typedef HANDLE HPLAYBACK;
typedef HPLAYBACK L_FAR *pHPLAYBACK;

/* 
   flags for L_SizeBitmap
*/

#define SIZE_NORMAL              0x0000
#define SIZE_FAVORBLACK          0x0001
#define SIZE_RESAMPLE            0x0002
#define SIZE_BICUBIC             0x0004

/* 
   flags for L_ConvertBufferExt
*/

#define CVT_SRCGRAY              0x0001
#define CVT_DSTGRAY              0x0002
#define CVT_SRCUSEBITS           0x0004
#define CVT_DSTUSEBITS           0x0008

/*
   flag that you can use to detect when a pixel color is 16 bit grayscale
*/

#define COLORREF_GRAY16          0x04000000L

/* 
   flags for L_RotateBitmap
*/

#define ROTATE_RESIZE            0x0001
#define ROTATE_RESAMPLE          0x0002
#define ROTATE_BICUBIC           0x0004

/*
   flags for L_StartResizeBitmap
*/
//-------- ColorRes flags
#define RES_ORDERRGB                0x00000000
#define RES_ORDERBGR                0x00000004
#define RES_ORDERGRAY               0x00000080
#define RES_ORDERROMM               0x00000800
//-------- Resize flags
#define RES_NORMAL                  0x00000000
#define RES_RESAMPLE                0x00000010
#define RES_BICUBIC                 0x00000020
//-------- Dithering flags
#define RES_NODITHERING             CRF_NODITHERING            //  0x00000000 /* No Dithering */
#define RES_FLOYDSTEINDITHERING     CRF_FLOYDSTEINDITHERING    //  0x00010000 /* Floyd Stein Dithering */
#define RES_STUCKIDITHERING         CRF_STUCKIDITHERING        //  0x00020000 /* Stucki Dithering */
#define RES_BURKESDITHERING         CRF_BURKESDITHERING        //  0x00030000 /* Burkes Dithering */
#define RES_SIERRADITHERING         CRF_SIERRADITHERING        //  0x00040000 /* Sierra Dithering */
#define RES_STEVENSONARCEDITHERING  CRF_STEVENSONARCEDITHERING //  0x00050000 /* Stevenson Arce Dithering */
#define RES_JARVISDITHERING         CRF_JARVISDITHERING        //  0x00060000 /* Jarvis Dithering */
#define RES_ORDEREDDITHERING        CRF_ORDEREDDITHERING       //  0x00070000 /* Ordered Dithering */
#define RES_CLUSTEREDDITHERING      CRF_CLUSTEREDDITHERING     //  0x00080000 /* Clustered Dithering */
#define RES_DITHERINGOPTIONS        CRF_DITHERINGOPTIONS       //  0x00FF0000 /* Mask to find dither option */

/*
   constants for L_ConvertToDIB
*/
#define DIB_BITMAPINFOHEADER 0
#define DIB_BITMAPV4HEADER   1
#define DIB_BITMAPV5HEADER   2    

/*
   compression types for L_ChangeBitmapCompression
*/
#define COMP_NONE             0
#define COMP_RLE              1
#define COMP_SUPER            2

/*
   Flags for L_SetBitmapMemoryInfo
*/
#define SETMEM_MEMORY         0x0001
#define SETMEM_TILESIZE       0x0002
#define SETMEM_TOTALTILES     0x0004
#define SETMEM_CONVTILES      0x0008
#define SETMEM_MAXTILEVIEWS   0x0010
#define SETMEM_TILEVIEWS      0x0020

/*
   Flags for L_SetMemoryThresholds
*/
#define MEM_TILEDTHRESHOLD 0x0001
#define MEM_MAXCONVSIZE    0x0002
#define MEM_TILESIZE       0x0004
#define MEM_CONVTILES      0x0008
#define MEM_CONVBUFFERS    0x0010
#define MEM_ALL            0x001F


/*
   BITMAPHANDLE structure
*/

typedef struct struct_LEAD_Bitmap
{
   union
   {
      struct struct_compressed_memory
      {
         HGLOBAL hData;          /* internal use */
         L_VOID L_HUGE*pData;    /* internal use */
      } Compressed;

      struct struct_window_memory
      {                         
         HGLOBAL hData;          /* Internal use */
         L_UCHAR L_FAR *pData;   /* Internal use */
      } Windows;

      struct struct_file_memory 
      {                         
         L_INT fd;               /* Internal use */
         L_UINT Available;       /* Internal use */
      } File;

      #if !defined(_WIN32_WCE)
      struct struct_tiled_memory
      {                         
         HGLOBAL hData;          /* Internal use */
         L_UCHAR L_FAR *pData;   /* Internal use */
      } Tiled;
      #endif

      struct struct_supercompressed_memory
      {
         HGLOBAL hData;          /* internal use */
         L_VOID L_HUGE*pData;    /* internal use */
      } SuperCompressed;
   } Addr;
   L_INT Width;                 /* Image width */
   L_INT Height;                /* Image height */
   L_INT BitsPerPixel;          /* Number of bits per pixel */
   L_UINT BytesPerLine;         /* Bytes per line, rounded by four */
   L_UINT32 CurrentPos;         /* Internal use */
   L_INT CurrentRow;            /* Internal use */
   struct struct_bitmap_flags
   {
      L_BITFIELD Allocated:1;          /* Is the bitmap allocated? */
      L_BITFIELD ConventionalMemory:1; /* allocated in conventional memory */
      L_BITFIELD DiskMemory:1;         /* allocated on disk */
      L_BITFIELD ProgressiveAvailable:1;        /* progressive format */
      L_BITFIELD LockedMemory:1;       /* Is memory locked in windows */
      L_BITFIELD Interlaced:1;         /* Interlaced format */
      L_BITFIELD WaitUserInput:1;      /* Playback wait for user input */
      L_BITFIELD Transparency:1;       /* Playback uses transparency */
      L_BITFIELD Compressed:1;         /* 1 bit RLE compressed data */
      L_BITFIELD Signed:1;             /* the pixel values are signed */
      L_BITFIELD Mirror:1;             /* this is a mirror of another image */
      L_BITFIELD UseLUT:1;             /* use pLUT for image processing */
      L_BITFIELD Global:1;             /* hData is HGLOBAL */
      L_BITFIELD UsePaintLUT:1;        /* Use PaintGamma, PaintContrast, PaintIntensity */
      L_BITFIELD Tiled:1;              /* Bitmap is stored as tiles */
      L_BITFIELD SuperCompressed:1;    /* Super compressed data */
      L_BITFIELD NoClip : 1;           /* Do not clip region */
      L_BITFIELD NewPalette:1;         /* If 1, Palette.pPalette contains the palette */
                                       /* If 0, Palette.hPalette contains the palette */
      L_BITFIELD Dummy:14;
   } Flags;

   L_INT nColors;                /* No. of possible colors in the bitmap */
   union
   {
      HPALETTE hPalette;         /* Handle to a palette */
      LPRGBQUAD pPalette;        /* Pointer to a RGBQUAD array */
   } Palette;

   L_INT ViewPerspective;        /* Is TOP_LEFT, BOTTOM_RIGHT, ... */
   L_INT Order;                  /* Is it ORDER_RGB, ORDER_BGR */
   L_UINT32 Size;                /* Size of the bitmap */
   L_VOID L_FAR *pDitherData;    /* Internal use */
   L_UINT DitheringMethod;       /* Which dithering method used */
   #if !defined(_WIN32_WCE)
   L_VOID L_FAR *pRgnInfo;       /* Internal use */
   #endif
   L_INT XResolution;            /* Bitmaps X resolution (DPI) */
   L_INT YResolution;            /* Bitmaps Y resolution (DPI) */
   L_INT Left;                   /* Left playback offset */
   L_INT Top;                    /* Top playback offset */
   L_UINT32 Delay;               /* Playback delay (ms) */
   COLORREF Background;          /* Playback background color */
   COLORREF Transparency;        /* Playback transparent color */
   L_UINT DisposalMethod;        /* Playback disposal method */
   L_INT   LowBit;               /* low bit set by L_WindowLevelBitmap */
   L_INT   HighBit;              /* high bit set by L_WindowLevelBitmap */
   RGBQUAD L_HUGE*pLUT;          /* LUT set by L_WindowLevel or L_WindowLevelBitmap */
   L_UINT32 LUTLength;           /* no of entries pointed by LUT */
   L_UINT32 DataOffset;          /* offset into hData */
   L_INT32  MinVal;              /* min val for a grayscale bitmap */
   L_INT32  MaxVal;              /* max val for a grayscale bitmap */
   L_INT    PaintLowBit;         /* low bit set by L_WindowLevelBitmap */
   L_INT    PaintHighBit;        /* high bit set by L_WindowLevelBitmap */
   L_UINT   PaintGamma;          /* Paint gamma value to be used during painting */
   L_INT   PaintContrast;        /* Paint contrast value to be used during painting */
   L_INT   PaintIntensity;       /* Paint intensity value to be used during painting */
   L_UCHAR L_FAR*pPaintLUT;      /* Paint LUT generated from PaintIntensity, PaintGamma, PaintIntensity */
   L_UINT32 Reserved;            /* reserved field, do not use */
} BITMAPHANDLE, L_FAR * pBITMAPHANDLE;

#if !defined(_WIN32_WCE)
/*
   version structure
*/
typedef struct struct_version_information
{
   L_UCHAR Product[60];         /* Product Name */
   L_INT Level;                 /* Toolkit Level (EXP, PRO, etc.) */
   L_INT MajorNumber;           /* Major Version Number */
   L_INT MinorNumber;           /* Minor Version Number */
   L_UCHAR Date[16];            /* Date of the Build */
   L_UCHAR Time[16];            /* Time of the Build */
} VERSIONINFO, L_FAR * pVERSIONINFO;
#endif

/*
   bitmap list handle
*/
typedef HANDLE HBITMAPLIST;
typedef HBITMAPLIST L_FAR *pHBITMAPLIST;

/*
   callback typedefs
*/
typedef L_INT (pEXT_CALLBACK COLORRESCALLBACK) (pBITMAPHANDLE, L_UCHAR L_FAR *, L_INT, L_VOID L_FAR *);
typedef L_INT (pEXT_CALLBACK COLORRESLISTCALLBACK) (pBITMAPHANDLE, L_UCHAR L_FAR *, L_UINT, L_UINT, L_INT, L_VOID L_FAR * );
typedef L_INT (pEXT_CALLBACK STATUSCALLBACK) (L_INT, L_VOID L_FAR*pUserData);
#if !defined(_WIN32_WCE)
typedef L_INT (pEXT_CALLBACK HOTKEYCALLBACK) (L_INT, L_UINT, L_VOID L_FAR*);
#endif

typedef L_INT (pEXT_CALLBACK REDIRECTOPEN) (L_TCHAR L_FAR *, L_INT, L_INT, L_VOID L_FAR*);
typedef L_UINT (pEXT_CALLBACK REDIRECTREAD) (L_INT, L_CHAR L_FAR *, L_INT, L_VOID L_FAR*);
typedef L_UINT (pEXT_CALLBACK REDIRECTWRITE) (L_INT, L_CHAR L_FAR *, L_INT, L_VOID L_FAR*);
typedef L_INT32 (pEXT_CALLBACK REDIRECTSEEK) (L_INT, L_INT32, L_INT, L_VOID L_FAR*);
typedef L_INT (pEXT_CALLBACK REDIRECTCLOSE) (L_INT, L_VOID L_FAR*);

#if !defined(_WIN32_WCE)
#define VECTOR_SUBSTITUTE_FONT_FOUND   0x0001
typedef L_INT (pEXT_CALLBACK VECSUBSTITUTEFONTCALLBACK) (L_CHAR L_FAR*, L_UINT32 dwFlags, L_VOID L_FAR*pUserData);
#endif

/*
   function prototypes
*/
L_VOID EXT_FUNCTION L_AccessBitmap (pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_AllocateBitmap (pBITMAPHANDLE pBitmap,
                                       L_UINT uMemory);

L_INT EXT_FUNCTION L_ChangeBitmapHeight (pBITMAPHANDLE pBitmap,
                                          L_INT nHeight);

L_INT EXT_FUNCTION L_ChangeBitmapViewPerspective(pBITMAPHANDLE pDstBitmap,
                                          pBITMAPHANDLE pSrcBitmap,
                                          L_INT   ViewPerspective);

L_INT EXT_FUNCTION L_ChangeFromDIB (pBITMAPHANDLE pBitmap,
                                     HGLOBAL hDIB);

HGLOBAL EXT_FUNCTION L_ChangeToDIB (pBITMAPHANDLE pBitmap);

HGLOBAL EXT_FUNCTION L_ChangeToDIB2(pBITMAPHANDLE pBitmap, L_UINT uType);

L_INT EXT_FUNCTION L_ClearBitmap (pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_ClearNegativePixels( pBITMAPHANDLE pBitmap );

L_INT EXT_FUNCTION L_ColorResBitmap (pBITMAPHANDLE pBitmapSrc,
                                      pBITMAPHANDLE pBitmapDst,
                                      L_INT nBitsPerPixel,
                                      L_UINT32 uFlags,
                                      LPRGBQUAD pPalette,
                                      HPALETTE hPalette,
                                      L_UINT uColors,
                                      COLORRESCALLBACK pfnCallback,
                                      L_VOID L_FAR * pUserData);

L_INT EXT_FUNCTION L_ColorResBitmapList (HBITMAPLIST hList,
                                      L_INT nBitsPerPixel,
                                      L_UINT32 uFlags,
                                      LPRGBQUAD pPalette,
                                      HPALETTE hPalette,
                                      L_UINT uColors);

L_INT EXT_FUNCTION L_ColorResBitmapListExt (HBITMAPLIST hList,
                                      L_INT nBitsPerPixel,
                                      L_UINT32 uFlags,
                                      L_RGBQUAD L_FAR * pPalette,
                                      HPALETTE hPalette,
                                      L_UINT uColors,
                                      COLORRESLISTCALLBACK pfnCallback,
                                      L_VOID L_FAR*pUserData);

L_INT EXT_FUNCTION L_CombineBitmap (pBITMAPHANDLE pBitmapDst,
                                     L_INT nXDst,
                                     L_INT nYDst,
                                     L_INT nWidth,
                                     L_INT nHeight,
                                     pBITMAPHANDLE pBitmapSrc,
                                     L_INT nXSrc,
                                     L_INT nYSrc,
                                     L_UINT32 uFlags);

L_INT EXT_FUNCTION L_CompressRow( L_UINT16 L_HUGE * pRunBuffer,
                                  L_UCHAR L_HUGE * pBuffer,
                                  L_INT nCol,
                                  L_INT nWidth);

L_INT EXT_FUNCTION L_CompressRows(  L_UINT16 L_HUGE*pRunBuffer,
                                    L_UCHAR L_HUGE*pBuffer,
                                    L_UINT nWidth,
                                    L_UINT nRows);

L_INT EXT_FUNCTION L_ConvertBuffer (L_UCHAR L_FAR * pBuffer,
                                     L_INT nWidth,
                                     L_INT nBitsPerPixelSrc,
                                     L_INT nBitsPerPixelDst,
                                     L_INT nOrderSrc,
                                     L_INT nOrderDst,
                                     LPRGBQUAD pPaletteSrc,
                                     LPRGBQUAD pPaletteDst);

L_INT EXT_FUNCTION L_ConvertBufferExt (L_UCHAR L_FAR * pBuffer,
                                     L_INT nWidth,
                                     L_INT nBitsPerPixelSrc,
                                     L_INT nBitsPerPixelDst,
                                     L_INT nOrderSrc,
                                     L_INT nOrderDst,
                                     LPRGBQUAD pPaletteSrc,
                                     LPRGBQUAD pPaletteDst,
                                     L_UINT  uFlags,
                                     L_INT   uLowBit,
                                     L_INT   uHighBit);

L_INT EXT_FUNCTION L_ConvertFromDIB (pBITMAPHANDLE pBitmap,
                                      BITMAPINFO L_FAR * pInfo,
                                      L_UCHAR L_FAR * pBits);

HGLOBAL EXT_FUNCTION L_ConvertToDIB (pBITMAPHANDLE pBitmap);

HGLOBAL EXT_FUNCTION L_ConvertToDIB2(pBITMAPHANDLE pBitmap, L_UINT uType);

L_INT EXT_FUNCTION L_CopyBitmap (pBITMAPHANDLE pBitmapDst,
                                 pBITMAPHANDLE pBitmapSrc);

L_INT EXT_FUNCTION L_CopyBitmap2 (pBITMAPHANDLE pBitmapDst,
                                  pBITMAPHANDLE pBitmapSrc,
                                  L_UINT uMemory);

L_INT EXT_FUNCTION L_CopyBitmapData (pBITMAPHANDLE pBitmapDst,
                                      pBITMAPHANDLE pBitmapSrc);

L_VOID EXT_FUNCTION L_CopyBitmapHandle (pBITMAPHANDLE pBitmapDst,
                                         pBITMAPHANDLE pBitmapSrc);

L_INT EXT_FUNCTION L_CopyBitmapListItems(pHBITMAPLIST phList,
                                        HBITMAPLIST hList,
                                        L_UINT uIndex,
                                        L_UINT uCount);

L_INT EXT_FUNCTION L_CopyBitmapRect (pBITMAPHANDLE pBitmapDst,
                                      pBITMAPHANDLE pBitmapSrc,
                                      L_INT nCol,
                                      L_INT nRow,
                                      L_UINT uWidth,
                                      L_UINT uHeight);

L_INT EXT_FUNCTION L_CopyBitmapRect2 (pBITMAPHANDLE pBitmapDst,
                                      pBITMAPHANDLE pBitmapSrc,
                                      L_INT nCol,
                                      L_INT nRow,
                                      L_UINT uWidth,
                                      L_UINT uHeight,
                                      L_UINT uMemory);

L_INT EXT_FUNCTION L_CreateBitmap (pBITMAPHANDLE pBitmap,
                                    L_UINT uMemory,
                                    L_UINT uWidth,
                                    L_UINT uHeight,
                                    L_UINT uBitsPerPixel,
                                    L_UINT uOrder,
                                    LPRGBQUAD pPalette,
                                    L_UINT uViewPerspective,
                                    L_UCHAR L_FAR*pData,
                                    L_UINT32 dwSize);

L_INT EXT_FUNCTION L_CreateBitmapList(pHBITMAPLIST phList);

L_UINT L_FAR *EXT_FUNCTION L_CreateUserMatchTable (LPRGBQUAD pPalette,
                                                   L_UINT uColors);

L_INT EXT_FUNCTION L_DefaultDithering (L_UINT uMethod);

L_INT EXT_FUNCTION L_DeleteBitmapListItems(HBITMAPLIST hList,
                                           L_UINT uIndex,
                                           L_UINT uCount);

L_INT EXT_FUNCTION L_DestroyBitmapList(HBITMAPLIST hList);

L_INT EXT_FUNCTION L_DitherLine (pBITMAPHANDLE pBitmap,
                                  L_UCHAR L_FAR * pBufferSrc,
                                  L_UCHAR L_FAR * pBufferDst);

L_INT EXT_FUNCTION L_CopyBitmapPalette(pBITMAPHANDLE pDstBitmap, 
                                      pBITMAPHANDLE pSrcBitmap);

HPALETTE EXT_FUNCTION L_DupBitmapPalette (pBITMAPHANDLE pBitmap);

HPALETTE EXT_FUNCTION L_DupPalette (HPALETTE hPalette);

L_INT EXT_FUNCTION L_ExpandRow(L_UINT16 L_HUGE * pRunBuffer, 
                               L_UCHAR L_HUGE * pBuffer, 
                               L_UINT nCol, 
                               L_INT nWidth);

L_INT EXT_FUNCTION L_ExpandRows( L_UINT16 L_HUGE *pRun, 
                                 L_UCHAR L_HUGE*pBuffer, 
                                 L_UINT nWidth, 
                                 L_UINT nRows);

L_INT EXT_FUNCTION L_FillBitmap (pBITMAPHANDLE pBitmap,
                                  COLORREF crFill);

L_INT EXT_FUNCTION L_FlipBitmap (pBITMAPHANDLE pBitmap);

L_VOID EXT_FUNCTION L_FreeBitmap (pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_FreeUserMatchTable (L_UINT L_FAR * pTable);

L_INT EXT_FUNCTION L_GetBitmapColors (pBITMAPHANDLE pBitmap,
                                       L_INT nIndex,
                                       L_INT nCount,
                                       LPRGBQUAD pPalette);

L_INT EXT_FUNCTION L_GetBitmapListCount(HBITMAPLIST hList,
                                           L_UINT L_FAR *puCount);

L_INT EXT_FUNCTION L_GetBitmapListItem(HBITMAPLIST hList,
                                       L_UINT uIndex,
                                       pBITMAPHANDLE pBitmap);

L_INT32 EXT_FUNCTION L_GetBitmapRow (pBITMAPHANDLE pBitmap,
                                      L_UCHAR L_FAR * pBuffer,
                                      L_INT nRow,
                                      L_UINT32 uBytes);

L_INT32 EXT_FUNCTION L_GetBitmapRowCol (pBITMAPHANDLE pBitmap,
                                         L_UCHAR L_FAR * pBuffer,
                                         L_INT nRow,
                                         L_INT nCol,
                                         L_UINT32 uBytes);

L_INT32 EXT_FUNCTION L_GetBitmapRowColCompressed (pBITMAPHANDLE pBitmap,
                                         L_UCHAR L_FAR * pWorkBuffer,
                                         L_UINT16 L_FAR * pRunBuffer,
                                         L_INT nRow,
                                         L_INT nCol,
                                         L_UINT32 uWidth);

L_INT EXT_FUNCTION L_GetBitmapRowCompressed (pBITMAPHANDLE pBitmap,
                                         L_UCHAR L_FAR * pWorkBuffer,
                                         L_UINT16 L_FAR * pRunBuffer,
                                         L_UINT nRow,
                                         L_UINT nLines);

L_INT EXT_FUNCTION L_GetFixedPalette (LPRGBQUAD pPalette,
                                       L_INT nBitsPerPixel);

COLORREF EXT_FUNCTION L_GetPixelColor (pBITMAPHANDLE pBitmap,
                                        L_INT nRow,
                                        L_INT nCol);

STATUSCALLBACK EXT_FUNCTION L_GetStatusCallBack (L_VOID L_FAR* L_FAR*ppUserData);

L_INT EXT_FUNCTION L_GrayScaleBitmap (pBITMAPHANDLE pBitmap,
                                      L_INT nBitsPerPixel);

L_INT EXT_FUNCTION L_InitBitmap (pBITMAPHANDLE pBitmap,
                                  L_INT nWidth,
                                  L_INT nHeight,
                                  L_INT nBitsPerPixel);

L_INT EXT_FUNCTION L_InsertBitmapListItem(HBITMAPLIST hList,
                                           L_UINT uIndex,
                                           pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_IsGrayScaleBitmap (pBITMAPHANDLE pBitmap);

L_BOOL EXT_FUNCTION L_IsSupportLocked (L_UINT uType);

L_INT EXT_FUNCTION L_PointFromBitmap(pBITMAPHANDLE pBitmap, 
                                     L_INT ViewPerspective, 
                                     L_INT L_FAR*px, 
                                     L_INT L_FAR*py);

L_INT EXT_FUNCTION L_PointToBitmap(pBITMAPHANDLE pBitmap,
                                   L_INT ViewPerspective,
                                   L_INT L_FAR*px,
                                   L_INT L_FAR*py);

L_INT EXT_FUNCTION L_PutBitmapColors (pBITMAPHANDLE pBitmap,
                                       L_INT nIndex,
                                       L_INT nCount,
                                       LPRGBQUAD pPalette);

L_INT32 EXT_FUNCTION L_PutBitmapRow (pBITMAPHANDLE pBitmap,
                                      L_UCHAR L_FAR * pBuffer,
                                      L_INT nRow,
                                      L_UINT32 uBytes);

L_INT32 EXT_FUNCTION L_PutBitmapRowCol (pBITMAPHANDLE pBitmap,
                                         L_UCHAR L_FAR * pBuffer,
                                         L_INT nRow,
                                         L_INT nCol,
                                         L_UINT32 uBytes);

L_INT32 EXT_FUNCTION L_PutBitmapRowColCompressed (pBITMAPHANDLE pBitmap,
                                         L_UCHAR L_FAR * pWorkBuffer,
                                         L_UINT16 L_FAR * pRunBuffer,
                                         L_INT nRow,
                                         L_INT nCol,
                                         L_UINT32 uWidth);

L_INT EXT_FUNCTION L_PutBitmapRowCompressed (pBITMAPHANDLE pBitmap,
                                         L_UCHAR L_FAR * pWorkBuffer,
                                         L_UINT16 L_FAR * pRunBuffer,
                                         L_UINT nRow,
                                         L_UINT nLines);

L_INT EXT_FUNCTION L_PutPixelColor (pBITMAPHANDLE pBitmap,
                                     L_INT nRow,
                                     L_INT nCol,
                                     COLORREF crColor);

L_INT EXT_FUNCTION L_RectFromBitmap(pBITMAPHANDLE pBitmap, 
                                    L_INT ViewPerspective,
                                    LPRECT lprc);

L_INT EXT_FUNCTION L_RectToBitmap(  pBITMAPHANDLE pBitmap, 
                                    L_INT nViewPerspective,
                                    LPRECT lprc);

L_VOID EXT_FUNCTION L_RedirectIO (REDIRECTOPEN pfnOpen,
                                   REDIRECTREAD pfnRead,
                                   REDIRECTWRITE pfnWrite,
                                   REDIRECTSEEK pfnSeek,
                                   REDIRECTCLOSE pfnClose,
                                   L_VOID L_FAR* pUserData);

L_VOID EXT_FUNCTION L_ReleaseBitmap (pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_RemoveBitmapListItem(HBITMAPLIST hList,
                                           L_UINT uIndex,
                                           pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_Resize (L_UCHAR L_FAR * pBuffer,
                              L_INT nRow,
                              L_INT nBitsPerPixel,
                              L_INT L_FAR * pXSize,
                              L_INT L_FAR * pYSize,
                              L_VOID L_FAR * pResizeData);

L_INT EXT_FUNCTION L_ResizeBitmap (pBITMAPHANDLE pBitmapSrc,
                                    pBITMAPHANDLE pBitmapDst);

L_INT EXT_FUNCTION L_ResizeBitmapExt (pBITMAPHANDLE pSrcBitmap,
                                    pBITMAPHANDLE pDestBitmap,
                                    L_UINT uFlags);

L_INT EXT_FUNCTION L_ReverseBitmap (pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_RotateBitmap (pBITMAPHANDLE pBitmap,
                                        L_INT32 nAngle,
                                        L_UINT uFlags,
                                        COLORREF crFill);

L_INT EXT_FUNCTION L_RotateBitmapViewPerspective (pBITMAPHANDLE pBitmap,
                                   L_INT nAngle);

L_INT EXT_FUNCTION L_SetBitmapDataPointer (pBITMAPHANDLE pBitmap, 
                                           L_UCHAR L_FAR*pData, 
                                           L_UINT32 dwSize);

L_INT EXT_FUNCTION L_SetBitmapListItem(HBITMAPLIST hList,
                                           L_UINT uIndex,
                                           pBITMAPHANDLE pBitmap);

STATUSCALLBACK EXT_FUNCTION L_SetStatusCallBack (STATUSCALLBACK pfnCallback, 
                                                 L_VOID L_FAR*pUserData);

L_UINT L_FAR *EXT_FUNCTION L_SetUserMatchTable (L_UINT L_FAR * pTable);

L_INT EXT_FUNCTION L_SizeBitmap(pBITMAPHANDLE pBitmap,
                                    L_INT nWidth,
                                    L_INT nHeight,
                                    L_UINT32 uFlags);

L_INT EXT_FUNCTION L_StartDithering (pBITMAPHANDLE pBitmap,
                                      LPRGBQUAD pPalette,
                                      L_UINT uColors);

L_INT EXT_FUNCTION L_StartResize (L_INT nOldWidth,
                                   L_INT nOldHeight,
                                   L_INT nNewWidth,
                                   L_INT nNewHeight,
                                   L_VOID L_FAR * L_FAR * ppResizeData);

L_INT EXT_FUNCTION L_StopDithering (pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_StopResize (L_VOID L_FAR * pResizeData);

COLORREF EXT_FUNCTION L_TranslateBitmapColor(pBITMAPHANDLE pBitmapDst,
                                             pBITMAPHANDLE pBitmapSrc,
                                             COLORREF crColor);

L_INT EXT_FUNCTION L_ToggleBitmapCompression(pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_TrimBitmap ( pBITMAPHANDLE pBitmap,
                                      L_INT nCol,
                                      L_INT nRow,
                                      L_UINT uWidth,
                                      L_UINT uHeight);

L_VOID EXT_FUNCTION L_UnlockSupport (L_UINT uType, L_TCHAR L_FAR * pKey);

L_INT EXT_FUNCTION L_FlipBitmapViewPerspective(pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_ReverseBitmapViewPerspective(pBITMAPHANDLE pBitmap);

typedef L_INT (pEXT_CALLBACK RESIZECALLBACK) (pBITMAPHANDLE, L_UCHAR L_FAR *, L_INT, L_INT, L_UINT32, L_VOID L_FAR *);

L_INT EXT_FUNCTION L_StartResizeBitmap(pBITMAPHANDLE pBitmap, 
                                       L_INT nNewWidth, 
                                       L_INT nNewHeight, 
                                       L_INT nNewBits,
                                       LPRGBQUAD pPalette, 
                                       L_INT nColors, 
                                       L_UINT32 uFlags, 
                                       RESIZECALLBACK pfnCallback, 
                                       L_VOID L_FAR*pCallbackData, 
                                       L_VOID L_FAR*L_FAR*ppResizeData);

L_INT EXT_FUNCTION L_GetResizedRowCol(L_VOID L_FAR*pResizeData, 
                                      L_UCHAR L_FAR*pBuffer,
                                      L_INT nRow,
                                      L_INT nCol,
                                      L_INT32 uBytes);

L_INT EXT_FUNCTION L_StopResizeBitmap(L_VOID L_FAR*pResizeData);

L_INT EXT_FUNCTION L_MoveBitmapListItems(pHBITMAPLIST phList,
                                        HBITMAPLIST hList,
                                        L_UINT uIndex,
                                        L_UINT uCount);

L_BOOL EXT_FUNCTION L_InitLEADTOOLS(HINSTANCE hInstance);
L_VOID EXT_FUNCTION L_QuitLEADTOOLS(L_BOOL bProcess);

L_INT EXT_FUNCTION L_ChangeBitmapCompression(pBITMAPHANDLE pBitmap, 
                                             L_INT nComp);

L_INT EXT_FUNCTION L_GetPixelData(pBITMAPHANDLE pBitmap, 
                                  L_VOID L_FAR*pData,
                                  L_INT nRow, 
                                  L_INT nCol, 
                                  L_INT nBytes);

L_INT EXT_FUNCTION L_PutPixelData(pBITMAPHANDLE pBitmap, 
                                  L_VOID L_FAR*pData,
                                  L_INT nRow, 
                                  L_INT nCol, 
                                  L_INT nBytes);

L_INT EXT_FUNCTION L_SetDefaultMemoryType(L_UINT uMemory);
L_INT EXT_FUNCTION L_GetDefaultMemoryType(L_UINT *puMemory);

L_INT EXT_FUNCTION L_SetMemoryThresholds(L_INT nTiledThreshold,
                                         L_INT nMaxConvSize,
                                         L_INT nTileSize,
                                         L_INT nConvTiles,
                                         L_INT nConvBuffers,
                                         L_UINT uFlags);

L_VOID EXT_FUNCTION L_GetMemoryThresholds(L_INT L_FAR*pnTiledThreshold,
                                          L_INT L_FAR*pnMaxConvSize,
                                          L_INT L_FAR*pnTileSize,
                                          L_INT L_FAR*pnConvTiles,
                                          L_INT L_FAR*pnConvBuffers);

L_INT EXT_FUNCTION L_SetBitmapMemoryInfo(pBITMAPHANDLE  pBitmap,
                                         L_UINT         uMemory,
                                         L_UINT         uTileSize,   
                                         L_UINT         uTotalTiles,
                                         L_UINT         uConvTiles,
                                         L_UINT         uMaxTileViews,
                                         L_UINT         uTileViews,
                                         L_UINT         uFlags);

L_INT EXT_FUNCTION L_GetBitmapMemoryInfo( pBITMAPHANDLE  pBitmap,
                                          L_UINT L_FAR*  puMemory,
                                          L_UINT L_FAR*  puTileSize,
                                          L_UINT L_FAR*  puTotalTiles,
                                          L_UINT L_FAR*  puConvTiles,
                                          L_UINT L_FAR*  puMaxTileViews,
                                          L_UINT L_FAR*  puTileViews);

L_INT EXT_FUNCTION L_SetTempDirectory(L_TCHAR L_FAR*pszTempDir);

L_INT EXT_FUNCTION L_GetTempDirectory(L_TCHAR L_FAR*pszTempDir, 
                                      L_UINT uSize);

STATUSCALLBACK EXT_FUNCTION L_GetCopyStatusCallBack (L_VOID L_FAR* L_FAR*ppUserData);
STATUSCALLBACK EXT_FUNCTION L_SetCopyStatusCallBack (STATUSCALLBACK pfnCallback, 
                                                     L_VOID L_FAR*pUserData);

L_INT EXT_FUNCTION L_SetBitmapPalette (pBITMAPHANDLE pBitmap, HPALETTE hPalette);
L_INT EXT_FUNCTION L_ScrambleBitmap(
                        pBITMAPHANDLE pBitmap, 
                        L_INT32 nColStart,
                        L_INT32 nRowStart,
                        L_INT32 nWidth,
                        L_INT32 nHeight,
                        L_UINT32 uKey,
                        L_UINT uFlags);

/* These functions not ported to Windows CE */
#if !defined(_WIN32_WCE)
L_INT EXT_FUNCTION L_CombineBitmapWarp(pBITMAPHANDLE pBitmapDst, 
                                       POINT ptDstArray[], 
                                       pBITMAPHANDLE  pBitmapSrc,
                                       POINT ptSrc,
                                       L_INT nSrcWidth,
                                       L_INT nSrcHeight,
                                       L_UINT uFlags);
HDC EXT_FUNCTION L_CreateLeadDC (pBITMAPHANDLE pBitmap);
L_BOOL EXT_FUNCTION L_DeleteLeadDC (HDC hDC);
L_INT EXT_FUNCTION L_GetBitmapAlpha (pBITMAPHANDLE pBitmap,
                                     pBITMAPHANDLE pAlpha);
L_INT EXT_FUNCTION L_SetBitmapAlpha (pBITMAPHANDLE pBitmap,
                                     pBITMAPHANDLE pAlpha);
L_INT EXT_FUNCTION L_SetHotKeyCallback(L_INT nHotKey, 
                                       L_UINT uHotKeyModifiers, 
                                       HOTKEYCALLBACK pfnHotKeyCallback, 
                                       L_VOID L_FAR* pUserData);
L_INT EXT_FUNCTION L_ShearBitmap (pBITMAPHANDLE pBitmap,
                                   L_INT nAngle,
                                   L_BOOL fHorizontal,
                                   COLORREF crFill);
L_INT EXT_FUNCTION L_VersionInfo (pVERSIONINFO pVersionInfo);
L_INT EXT_FUNCTION L_VecSetSubstituteFontCallback(VECSUBSTITUTEFONTCALLBACK pfnCallback, L_VOID L_FAR* pUserData);
L_INT EXT_FUNCTION L_VecGetSubstituteFontCallback(VECSUBSTITUTEFONTCALLBACK L_FAR* ppfnCallback, L_VOID L_FAR* L_FAR* pUserData);
#endif /*_WIN32_WCE*/

#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif                          /* _LTKRN_H_ */
