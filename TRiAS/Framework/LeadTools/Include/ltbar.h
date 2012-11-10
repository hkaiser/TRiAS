/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991, 2003 by LEAD Technologies, Inc.                         |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : BarCode                                                         |
| FILE NAME : ltbar.h                                                         |
| DESC      : Include common header files that are required to the poject.    |
+----------------------------------------------------------------------------*/
#ifndef _LTBAR_H_
#define _LTBAR_H_

#define _HEADER_ENTRY_
#include "ltpck.h"

/*----------------------------------------------------------------------------+
|                          DEFINES SECTION                                    |
+----------------------------------------------------------------------------*/

/* Bar Code Status */
#define BARCODE_NORMAL                    1
#define BARCODE_ERRORCHECK                2

/* Bar Code Colors Flags */
#define BARCODE_USECOLORS                 0x0200   /* for R/W */
#define BARCODE_TRANSPARENT               0x0400   /* for W only */

/* Linear Barcode Flags */
#define BARCODE_JUSTIFYRIGHT              0x0010   /* For W only */
#define BARCODE_JUSTIFYHCENTER            0x0020   /* For W only */
#define BARCODE_RETURNCHECK               0x1000   /* for R only */

/* Bar Code Read/Write Flags for 1D */
#define BARCODE_MARKERS                   0x0001
#define BARCODE_BLOCK_SEARCH              0x0002

/* Bar Code Write Flags for CodeOne and PDF417 */
#define BARCODE_TRUNCATE                  0x0010
#define BARCODE_MSGAPPEND                 0x0020
#define BARCODE_INITREADER                0x0040
#define BARCODE_COLROWASLIMITS            0x0080
#define BARCODE_DISABLE_COMPRESSOPN       0x0100

/* Units of measurment in an image */
#define BARCODE_SCANLINES_PER_PIXELS      0  /* Use scanlines/pixels */
#define BARCODE_INCHES                    1  /* Use Inches, you must multiply one inch by 100 */
#define BARCODE_MILLIMETERS               2  /* Use Millimeters */

/* Bar Code Direction, used for Read 1D and PDF417 */
#define BARCODE_DIR_LEFT_TO_RIGHT         0x001
#define BARCODE_DIR_RIGHT_TO_LEFT         0x002
#define BARCODE_DIR_TOP_TO_BOTTOM         0x004
#define BARCODE_DIR_BOTTOM_TO_TOP         0x008

#define BARCODE_DIR_SKEW                  0x010
#define BARCODE_DIR_HORIZONTAL            0x020
#define BARCODE_DIR_VERTICAL              0x040
#define BARCODE_DIR_DIAGONAL              0x080

/* Bar Code Justification for Write CodeOne and PDF417 */
#define BARCODE_JUSTIFY_RIGHT             0x1000
#define BARCODE_JUSTIFY_H_CENTER          0x2000
#define BARCODE_JUSTIFY_BOTTOM            0x4000
#define BARCODE_JUSTIFY_V_CENTER          0x8000

/* PDF417 ECC LEVEL Constants */
#define BARCODE_PDF417_ECCLEVEL_0         0x0001
#define BARCODE_PDF417_ECCLEVEL_1         0x0002
#define BARCODE_PDF417_ECCLEVEL_2         0x0004
#define BARCODE_PDF417_ECCLEVEL_3         0x0008
#define BARCODE_PDF417_ECCLEVEL_4         0x0010
#define BARCODE_PDF417_ECCLEVEL_5         0x0020
#define BARCODE_PDF417_ECCLEVEL_6         0x0040
#define BARCODE_PDF417_ECCLEVEL_7         0x0080
#define BARCODE_PDF417_ECCLEVEL_8         0x0100
#define BARCODE_PDF417_ECCUSE_PERCENT     0x0FFF

/* PDF Read Flags */
#define BARCODE_RETURNCORRUPT                0x080 /* R / PDF417 */

#define BARCODE_PDF_READ_MODE_0              0x0000
#define BARCODE_PDF_READ_MODE_1              0x1000
#define BARCODE_PDF_READ_MODE_2              0x2000
#define BARCODE_PDF_READ_MODE_3_BASIC        0x3000
#define BARCODE_PDF_READ_MODE_3_EXTENDED     0x7000

#define BARCODE_PDF_READ_MACRO_OPTION_0      0x00010000
#define BARCODE_PDF_READ_MACRO_OPTION_1      0x00020000
#define BARCODE_PDF_READ_MACRO_OPTION_2      0x00040000
#define BARCODE_PDF_READ_MACRO_OPTION_3      0x00080000
#define BARCODE_PDF_READ_MACRO_OPTION_4      0x00100000
#define BARCODE_PDF_READ_MACRO_OPTION_5      0x00200000
#define BARCODE_PDF_READ_MACRO_OPTION_6      0x00400000
#define BARCODE_PDF_READ_MACRO_OPTION_79AZ   0x00800000

/* Bar Code (1D) Read/Write Types */
#define BARCODE_1D_EAN_13                 0x00000001
#define BARCODE_1D_EAN_8                  0x00000002
#define BARCODE_1D_UPC_A                  0x00000004
#define BARCODE_1D_UPC_E                  0x00000008
#define BARCODE_1D_CODE_3_OF_9            0x00000010
#define BARCODE_1D_CODE_128               0x00000020
#define BARCODE_1D_CODE_I2_OF_5           0x00000040
#define BARCODE_1D_CODA_BAR               0x00000080
#define BARCODE_1D_UCCEAN_128             0x00000100

/* The following define used only for read any bar code (1D) type in the image */
#define BARCODE_1D_READ_ANYTYPE           0x00000FF0

/* Bar Code CodeOne Read Types */
#define BARCODE_R_CODEONE_A_TO_H          0x00000200
#define BARCODE_R_CODEONE_T               0x00000400
#define BARCODE_R_CODEONE_S               0x00000800
#define BARCODE_R_CODEONE_ANYTYPE         0x00001000

/* Bar Code PDF417 Read/Write Type */
#define BARCODE_PDF417                    0x00002000

/* Code One Write/Return Read Type Sub Types */
#define BARCODE_CODEONE_DEF               0x00004000
#define BARCODE_CODEONE_TDEF              0x00008000
#define BARCODE_CODEONE_SDEF              0x00010000
#define BARCODE_CODEONE_A                 0x00020000
#define BARCODE_CODEONE_B                 0x00040000
#define BARCODE_CODEONE_C                 0x00080000
#define BARCODE_CODEONE_D                 0x00100000
#define BARCODE_CODEONE_E                 0x00200000
#define BARCODE_CODEONE_F                 0x00400000
#define BARCODE_CODEONE_G                 0x00800000
#define BARCODE_CODEONE_H                 0x01000000
#define BARCODE_CODEONE_T16               0x02000000
#define BARCODE_CODEONE_T32               0x04000000
#define BARCODE_CODEONE_T48               0x08000000
#define BARCODE_CODEONE_S10               0x10000000
#define BARCODE_CODEONE_S20               0x20000000
#define BARCODE_CODEONE_S30               0x40000000

/* Bar Codes Major Types */
#define BARCODES_1D                       0x001
#define BARCODES_2D_READ                  0x002
#define BARCODES_2D_WRITE                 0x004
#define BARCODES_PDF_READ                 0x008
#define BARCODES_PDF_WRITE                0x010
#define BARCODES_DATAMATRIX_READ          0x020
#define BARCODES_DATAMATRIX_WRITE         0x040

/* DataMatrix Write / Return Read Type Sub Types */
#define BARCODE_DM_DEF                    0x00000101 /* Use Default DataMatrix Size */
#define BARCODE_DM_10x10                  0x00000102
#define BARCODE_DM_12x12                  0x00000103
#define BARCODE_DM_14x14                  0x00000104
#define BARCODE_DM_16x16                  0x00000105
#define BARCODE_DM_18x18                  0x00000106
#define BARCODE_DM_20x20                  0x00000107
#define BARCODE_DM_22x22                  0x00000108
#define BARCODE_DM_24x24                  0x00000109
#define BARCODE_DM_26x26                  0x0000010A
#define BARCODE_DM_32x32                  0x0000010B
#define BARCODE_DM_36x36                  0x0000010C
#define BARCODE_DM_40x40                  0x0000010D
#define BARCODE_DM_44x44                  0x0000010E
#define BARCODE_DM_48x48                  0x0000010F
#define BARCODE_DM_52x52                  0x00000110
#define BARCODE_DM_64x64                  0x00000111
#define BARCODE_DM_72x72                  0x00000112
#define BARCODE_DM_80x80                  0x00000113
#define BARCODE_DM_88x88                  0x00000114
#define BARCODE_DM_96x96                  0x00000115
#define BARCODE_DM_104x104                0x00000116
#define BARCODE_DM_120x120                0x00000117
#define BARCODE_DM_132x132                0x00000118
#define BARCODE_DM_144x144                0x00000119
#define BARCODE_DM_8x18                   0x0000011A
#define BARCODE_DM_8x32                   0x0000011B
#define BARCODE_DM_12x26                  0x0000011C
#define BARCODE_DM_12x36                  0x0000011D
#define BARCODE_DM_16x36                  0x0000011E
#define BARCODE_DM_16x48                  0x0000011F

#define BARCODE_DM_WRITE_RECTANGLE        0x00000180 /* Write Rectangular Default Symbol */

/* DataMatrix Read General Types */
#define BARCODE_DM_READ_SQUARE            0x00010000
#define BARCODE_DM_READ_RECTANGLE         0x00020000
#define BARCODE_DM_READ_SMALL             0x00040000

/*----------------------------------------------------------------------------+
|                       STRUCTURES SECTION                                    |
+----------------------------------------------------------------------------*/

typedef struct _tagBarCodeData
{
   L_INT             nGroup;              // used only for CodeOne and PDF417
   L_UINT32          ulType;
   L_INT             nUnits;
   RECT              rcBarLocation;
   L_INT             nSizeofBarCodeData;
   L_CHAR L_FAR *    pszBarCodeData;
   L_INT             nIndexDuplicate;     // for reading only
   L_INT             nTotalCount;         // for reading only
   L_INT             nDupCount;           // for reading only
} BARCODEDATA, L_FAR * pBARCODEDATA;

typedef struct _tagBarCodeColor
{
   DWORD       dwColorBar;
   DWORD       dwColorSpace;
} BARCODECOLOR, L_FAR * pBARCODECOLOR;

typedef struct _tagBarCode1D
{
   L_BOOL      bOutShowText;              // for writing only
   L_INT       nDirection;                // for reading only
   L_BOOL      bErrorCheck;
   L_INT       nGranularity;
   L_INT       nMinLength;
   L_INT       nMaxLength;
   L_INT       nWhiteLines;
} BARCODE1D, L_FAR * pBARCODE1D;

typedef struct _tagBarCodeReadPDF
{
   L_INT       nDirection;
} BARCODEREADPDF, L_FAR * pBARCODEREADPDF;

typedef struct _tagBarCodeWriteCodeOne
{
   L_INT       nElementX;
   L_INT       nElementY;
   L_INT       nJustify;
} BARCODEWRITECODEONE, L_FAR * pBARCODEWRITECODEONE;

typedef struct _tagBarCodeWritePDF
{
   L_UINT16    wEccPerc;
   L_UINT16    wEccLevel;
   L_UINT16    wAspectHeight;
   L_UINT16    wAspectWidth;
   L_UINT16    wModAspectRatio;
   L_UINT16    wColumns;
   L_UINT16    wRows;
   L_UINT16    wModule;
   L_INT       nJustify;
} BARCODEWRITEPDF, L_FAR * pBARCODEWRITEPDF;

typedef struct _tagBarCodeVersion
{
   L_UCHAR     Product[60];
   L_INT       MajorNumber;
   L_INT       MinorNumber;
   L_UCHAR     Date[16];
   L_UCHAR     Time[16];
} BARCODEVERSION, L_FAR * pBARCODEVERSION;

typedef struct _tagBARCODEWRITEDM
{
   L_INT       nSize;
   L_UINT32    ulFlags;
   L_CHAR      cGroupNumber;
   L_CHAR      cGroupTotal;
   L_UCHAR     cFileIDLo;
   L_UCHAR     cFileIDHi;
   L_INT       nXModule;
} BARCODEWRITEDM, L_FAR * pBARCODEWRITEDM;

/*----------------------------------------------------------------------------+
|                       FUNCTIONS SECTION                                     |
+----------------------------------------------------------------------------*/

L_INT EXT_FUNCTION L_BarCodeRead(pBITMAPHANDLE        pBitmap,
                                 RECT L_FAR *         prcSearch,
                                 L_UINT32             ulSearchType,
                                 L_INT                nUnits,
                                 L_UINT32             ulFlags,
                                 L_INT                nMultipleMaxCount,
                                 pBARCODE1D           pBarCode1D,
                                 pBARCODEREADPDF      pBarCodePDF,
                                 pBARCODECOLOR        pBarCodeColor,
                                 pBARCODEDATA L_FAR * ppBarCodeData);

L_INT EXT_FUNCTION L_BarCodeWrite(pBITMAPHANDLE        pBitmap,
                                  pBARCODEDATA         pBarCodeData,
                                  pBARCODECOLOR        pBarCodeColor,
                                  L_UINT32             ulFlags,
                                  pBARCODE1D           pBarCode1D,
                                  pBARCODEWRITECODEONE pBarCode2D,
                                  pBARCODEWRITEPDF     pBarCodePDF,
                                  LPRECT               lprcSize);

L_INT EXT_FUNCTION L_BarCodeWriteExt(pBITMAPHANDLE     pBitmap,
                                     pBARCODEDATA      pBarCodeData,
                                     pBARCODECOLOR     pBarCodeColor,
                                     L_UINT32          ulFlags,
                                     pBARCODE1D        pBarCode1D,
                                     pBARCODEWRITEPDF  pBarCodePDF,
                                     pBARCODEWRITEDM   pBarCodeDM,
                                     LPRECT            lprcSize);

L_VOID EXT_FUNCTION L_BarCodeFree(pBARCODEDATA L_FAR * ppBarCodeData);

L_BOOL EXT_FUNCTION L_BarCodeIsDuplicated(pBARCODEDATA pBarCodeDataItem);

L_INT EXT_FUNCTION L_BarCodeGetDuplicated(pBARCODEDATA pBarCodeDataItem);

L_INT EXT_FUNCTION L_BarCodeGetFirstDuplicated(pBARCODEDATA pBarCodeData,
                                               L_INT        nIndex);

L_INT EXT_FUNCTION L_BarCodeGetNextDuplicated(pBARCODEDATA pBarCodeData,
                                              L_INT        nCurIndex);

L_INT EXT_FUNCTION L_BarCodeInit (L_INT nMajorType);

L_VOID EXT_FUNCTION L_BarCodeExit (L_VOID);

L_INT EXT_FUNCTION L_BarCodeVersionInfo(pBARCODEVERSION pBarCodeVersion);

#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif //_LTBAR_H_
/*================================================================= EOF =====*/