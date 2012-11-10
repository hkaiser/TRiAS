/*
   LTWND.H - bitmap window class module header file
   Copyright (c) 1991-2000 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTWND_H_
#define _LTWND_H_

#include "ltkrn.h"

#define _HEADER_ENTRY_
#include "ltpck.h"

/*
   window class name
*/
#define L_BITMAPCLASS TEXT("LTWND12N")

/*
   class messages
*/
#define L_BM_LOAD             (WM_USER + 0)
#define L_BM_SAVE             (WM_USER + 1)
#define L_BM_FREE             (WM_USER + 2)
#define L_BM_FLIP             (WM_USER + 3)
#define L_BM_ROTATE           (WM_USER + 4)
#define L_BM_INTENSITY        (WM_USER + 5)
#define L_BM_REVERSE          (WM_USER + 6)
#define L_BM_INFO             (WM_USER + 7)
#define L_BM_GETPALETTE       (WM_USER + 8)
#define L_BM_SETSTYLE         (WM_USER + 9)

#define L_BM_GETBITMAP        (WM_USER + 10)
#define L_BM_SETBITMAP        (WM_USER + 11)
#define L_BM_AVERAGE          (WM_USER + 12)
#define L_BM_MEDIAN           (WM_USER + 13)
#define L_BM_CONTRAST         (WM_USER + 14)
#define L_BM_HUE		         (WM_USER + 15)
#define L_BM_SATURATION       (WM_USER + 16)
#define L_BM_GRAYSCALE        (WM_USER + 17)
#define L_BM_HALFTONE         (WM_USER + 18)
#define L_BM_HISTOEQ          (WM_USER + 19)
#define L_BM_INVERT           (WM_USER + 20)
#define L_BM_SPATIALFLT       (WM_USER + 21)
#define L_BM_MOSAIC           (WM_USER + 22)
#define L_BM_POSTERIZE        (WM_USER + 23)
#define L_BM_SETZOOM          (WM_USER + 24)
#define L_BM_RESIZE           (WM_USER + 25)
#define L_BM_COLORRES         (WM_USER + 26)
#define L_BM_SHARPEN          (WM_USER + 27)
#define L_BM_SETIMAGERECT     (WM_USER + 28)
#define L_BM_COPY             (WM_USER + 29)
#define L_BM_PASTE            (WM_USER + 30)
#define L_BM_COPYBITMAP       (WM_USER + 31)
#define L_BM_TWAINSELECT      (WM_USER + 32)
#define L_BM_TWAINACQUIRE     (WM_USER + 33)
#define L_BM_BITMAPCHANGED    (WM_USER + 34)
#define L_BM_SETBITMAPCLIP    (WM_USER + 35)
#define L_BM_FOCUSEDZOOM      (WM_USER + 36)
#define L_BM_ADDNOISE         (WM_USER + 37)
#define L_BM_CLEAR            (WM_USER + 38)
#define L_BM_FILL             (WM_USER + 39)
#define L_BM_GAMMACORRECT     (WM_USER + 40)
#define L_BM_RESAMPLE         (WM_USER + 41)
#define L_BM_SHEAR            (WM_USER + 42)
#define L_BM_INTENSITYDETECT  (WM_USER + 43)
#define L_BM_BINARYFLT        (WM_USER + 44)
#define L_BM_DESKEW           (WM_USER + 45)
#define L_BM_DESPECKLE        (WM_USER + 46)
#define L_BM_PRINT            (WM_USER + 47)

/*
   class notification messages
*/
#define L_BN_CHANGE     0
#define L_BN_UPDATE     1
#define L_BN_HSCROLL    2
#define L_BN_VSCROLL    3
#define L_BN_SETFOCUS   4
#define L_BN_KILLFOCUS  5
#define L_BN_CLICKED    6
#define L_BN_DBLCLK     7
#define L_BN_PAINTED    8

/*
   class style flags
*/
#define L_BS_SIZEIMAGE    0x00000001   /* Resize image to fit the window */
#define L_BS_ORDERRGB     0x00000002   /* Load high color image in RGB order */
#define L_BS_THUMBTRACK   0x00000004   /* Track the thumb position when using
                                          scroll bars */
#define L_BS_SIZEWINDOW   0x00000008   /* Resize window to the image size */
#define L_BS_CENTER       0x00000010   /* Center the image */
#define L_BS_FIXEDPALETTE 0x00000020   /* Use the fixed palette */
#define L_BS_BKGNDPALETTE 0x00000040   /* Palette should be forced to the
                                          background */
#define L_BS_NOPOSTQUIT   0x00000080   /* WM_QUIT message should not be
                                          posted on WM_DESTROY */
#define L_BS_MDICHILD     0x00000100   /* The Window is an MDI Child */

/*
   data structures
*/
typedef struct tagLEADBITMAPCOLORRES
{
   L_INT StructSize;
   L_INT BitsPerPixel;
   L_UINT32 Flags;
   LPRGBQUAD pPalette;
   L_UINT Colors;
} LEADBITMAPCOLORRES, far * pLEADBITMAPCOLORRES;

typedef struct tagLEADBITMAPLOAD
{
   L_INT StructSize;
   L_TCHAR Name[L_MAXPATH];
   pLOADFILEOPTION pOptions;
} LEADBITMAPLOAD, L_FAR * pLEADBITMAPLOAD;

typedef struct tagLEADBITMAPSAVE
{
   L_INT StructSize;
   L_TCHAR Name[L_MAXPATH];
   L_INT Format;
   L_INT QFactor;
   L_INT BitsPerPixel;
   pSAVEFILEOPTION pOptions;
} LEADBITMAPSAVE, L_FAR * pLEADBITMAPSAVE;

typedef struct tagLEADBITMAPINFO
{
   L_INT StructSize;
   L_INT Width;
   L_INT Height;
   L_INT Pixels;
} LEADBITMAPINFO, L_FAR * pLEADBITMAPINFO;

typedef struct tagLEADBITMAPFFOCUSEDZOOM
{
   L_INT StructSize;
   L_UINT Factor;
   L_BOOL Center;
   L_INT XFocus;
   L_INT YFocus;
} LEADBITMAPFOCUSEDZOOM, L_FAR * pLEADBITMAPFOCUSEDZOOM;

typedef struct tagLEADBITMAPSHEAR
{
   L_INT StructSize;
   L_INT nAngle;
   L_BOOL fHorizontal;
   COLORREF crFill;
} LEADBITMAPSHEAR, L_FAR * pLEADBITMAPSHEAR;

typedef struct tagLEADBITMAPPRINT
{
   L_INT StructSize;
   HDC hDC;
   L_INT nXPos;
   L_INT nYPos;
   L_INT nXSize;
   L_INT nYSize;
   L_BOOL fEndDoc;
} LEADBITMAPPRINT, L_FAR * pLEADBITMAPPRINT;

/*
   function prototypes
*/
L_VOID EXT_FUNCTION L_UseBitmapClass (L_VOID);

#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif                          /* _LTWND_H_ */
