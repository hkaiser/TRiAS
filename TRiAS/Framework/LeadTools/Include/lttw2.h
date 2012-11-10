/*
   LTTW2.H - twain module header file
   Copyright (c) 1990-2001 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTTW2_H_
#define _LTTW2_H_

#include "twain.h"

// Error Codes
#define TWAIN_SUCCESS                  SUCCESS
#define TWAIN_SUCCESS_RETRY            TWAIN_SUCCESS + 1
#define TWAIN_SUCCESS_ABORT            TWAIN_SUCCESS + 2

// Default TWFF
#define TWFF_DEFAULT       99

// Function flags
// L_TwainSetProperties flags
#define LTWAIN_PROPERTIES_SET          1   // Set values as the current values
#define LTWAIN_PROPERTIES_RESET        2   // Reset values to their default values

// L_TwainGetProperties flags
#define LTWAIN_PROPERTIES_GETCURRENT   3   // Get the currently set values
#define LTWAIN_PROPERTIES_GETDEFAULT   4   // Get the default values

// L_TwainSetCapability flags
#define LTWAIN_CAPABILITY_SET          1   // Set values as the current values
#define LTWAIN_CAPABILITY_RESET        2   // Reset values to their default values

// L_TwainGetCapability flags
#define LTWAIN_CAPABILITY_GETCURRENT   3   // Get the currently set values
#define LTWAIN_CAPABILITY_GETDEFAULT   4   // Get the default values
#define LTWAIN_CAPABILITY_GETVALUES    5   // Enum available values

// L_TwainEnumCapabilities flags
#define LTWAIN_CAPABILITY_DONTGET      0   // Do not get the capability values

// L_TwainGetSources and L_TwainGetSources2 functions flags
#define LTWAIN_SOURCE_ENUMERATE_ALL       0x0000
#define LTWAIN_SOURCE_ENUMERATE_DEFAULT   0x0001

// L_TwainGetNumericContainerValue index values
#define LTWAIN_VALUE_COUNT                -1
#define LTWAIN_VALUE_CURRENT              -2
#define LTWAIN_VALUE_DEFAULT              -3
#define LTWAIN_VALUE_MINIMUM              -4
#define LTWAIN_VALUE_MAXIMUM              -5
#define LTWAIN_VALUE_STEPSIZE             -6

// L_TwainAcquire flags
#define LTWAIN_SHOW_USER_INTERFACE        0x0001
#define LTWAIN_MODAL_USER_INTERFACE       0x0002
#define LTWAIN_BITMAP_TYPE_DISK           0x0004
#define LTWAIN_USE_THREAD_MODE            0x0008
#define LTWAIN_CHECK_ALL_DEFAULT_BPP      0x0010

// L_TwainOpenTemplateFile 
#define LTWAIN_TEMPLATE_OPEN_READ         0
#define LTWAIN_TEMPLATE_OPEN_WRITE        1

// Flags for uTransferMode parameter of L_TwainAcquireMulti ...
#define LTWAIN_FILE_MODE                  0x001
#define LTWAIN_BUFFER_MODE                0x002
#define LTWAIN_NATIVE_MODE                0x004

// TWAINSESSION Handle
typedef HANDLE                HTWAINSESSION;
typedef HTWAINSESSION *       pHTWAINSESSION;

// TWAINTEMPLATEFILE Handle
typedef HANDLE                HTWAINTEMPLATEFILE;
typedef HTWAINTEMPLATEFILE *  pHTWAINTEMPLATEFILE;

// TWAIN structure LTWAINSOURCE
typedef struct _LTWAINSOURCE
{
   L_TCHAR *       pszTwainSourceName;
} LTWAINSOURCE, L_FAR * pLTWAINSOURCE;

// TWAIN structure LTWAINPROPERTYQUERY
typedef struct _LTWAINPROPERTYQUERY
{
   L_UINT         uType;
   union
   {
      pTW_ONEVALUE     pltwOneValue;
      pTW_RANGE        pltwRange;
      pTW_ENUMERATION  pltwEnumeration;
      pTW_ARRAY        pltwArray;
   };
} LTWAINPROPERTYQUERY, L_FAR * pLTWAINPROPERTYQUERY;

#define LTWAINPROPERTYQUERYSIZE sizeof (LTWAINPROPERTYQUERY)

// Properties structures
typedef struct _IMAGERESOLUTION
{
   L_INT    nUnitOfResolution;   // Unit of resolution in general (Meters, Inches, ...)
   L_INT    nBitsPerPixel;       // Bits per pixel of image
   L_FLOAT  fHorzResolution;     // Horizontal resolution of image
   L_FLOAT  fVertResolution;     // Vertical resolution of image
   L_FLOAT  fXScaling;           // Unit of resolution in the X direction
   L_FLOAT  fYScaling;           // Unit of resolution in the Y direction
   L_FLOAT  fRotationAngle;      // Rotation angle of scanned image
   L_FLOAT  fLeftMargin;         // Left margin of scanned image
   L_FLOAT  fRightMargin;        // Right margin of scanned image
   L_FLOAT  fTopMargin;          // Top margin of scanned image
   L_FLOAT  fBottomMargin;       // Bottom margin of scanned image
} IMAGERESOLUTION, L_FAR * pIMAGERESOLUTION;

#define IMAGERESOLUTIONSIZE sizeof (IMAGERESOLUTION)

typedef struct _DATATRANSFER
{
   L_INT    nFillOrder;          // CCITT decoding variable, can be MSB or LSB
   L_INT    nBufMemCompression;  // Compression used when using beffered memory transfer
   L_INT    nTransferMode;       // Data transfer mode, can be Native, Buffered memory, Disk File
   L_INT    nScanFileFormat;     // File format used when scanning, can be (BMP, JPEG, PICT, TIFF, XBM)
   L_INT    nMemBufSize;         // Maximum size to be used in the Buffered memory transfer mode
   L_BOOL   bSaveToOneFile;      // Used to save all scanned images to one MULTI PAGE file
   L_BOOL   bAppendToFile;       // Used to append images to an existing MULTI PAGE file
   L_BOOL   bDumpMemBufsToFile;  // Used to save the memory buffers in case memory buffered transfer is chosen to the file name below
   L_TCHAR  szFileName [250];    // The file used to save scanned images.
} DATATRANSFER, L_FAR * pDATATRANSFER;

#define DATATRANSFERSIZE sizeof (DATATRANSFER)

typedef struct _APPLICATIONDATA
{
   HWND     hWnd;                         // Window handle of an application, may not be NULL
   L_TCHAR  szManufacturerName [256];     // Application manufacturer name
   L_TCHAR  szAppProductFamily [256];     // Application product family
   L_TCHAR  szVersionInfo [32];           // Application version info
   L_TCHAR  szAppName [256];              // Application Name
#ifdef _UNICODE
   L_UINT16 uLanguage;
   L_UINT16 uCountry;
#endif
} APPLICATIONDATA, L_FAR * pAPPLICATIONDATA;

#define APPLICATIONDATASIZE sizeof (APPLICATIONDATA)

typedef struct _IMAGEEFFECTS
{
   L_INT    nPixFlavor;       // Pixel flavor, 0 for Chocolate, 1 for Vanilla
   L_INT    nColorScheme;     // Color scheme used, B/W, Gray256, RGB
   L_FLOAT  fHighLight;       // Highlight value
   L_FLOAT  fShadow;          // Shadow value
   L_FLOAT  fBrightness;      // Brightness value
   L_FLOAT  fContrast;        // Contrast value
   L_TCHAR  szHalfTone[32];   // Half tone pattern string
} IMAGEEFFECTS, L_FAR * pIMAGEEFFECTS;

#define IMAGEEFFECTSSIZE sizeof (IMAGEEFFECTS)

typedef struct _LTWAINPROPERTIES
{
   L_BOOL            bPaperSource;     // Paper Source used when scanning (auto feed)
   L_INT             nMaxNumOfPages;   // The maximum number of pages to scan
   L_INT             nDuplexScanning;  // Duplex scanning enable
   IMAGERESOLUTION   ImageRes;         // Image resolution structure
   DATATRANSFER      DataTransfer;     // Data transfer structure
   IMAGEEFFECTS      ImageEff;         // Image effects used
} LTWAINPROPERTIES, L_FAR * pLTWAINPROPERTIES;

#define LTWAINPROPERTIESSIZE sizeof (LTWAINPROPERTIES)

// Acquire list call back structure (user data)
typedef struct _ACQUIRELIST
{
   HBITMAPLIST hBitmap;
} ACQUIRELIST, L_FAR * pACQUIRELIST;

#define ACQUIRELISTSIZE sizeof (ACQUIRELIST)

typedef enum _LTWAINNUMERICTYPE
{
   TWAINNUMERICTYPE_TW_INT8      = TWTY_INT8,
   TWAINNUMERICTYPE_TW_INT16     = TWTY_INT16,
   TWAINNUMERICTYPE_TW_INT32     = TWTY_INT32,
   TWAINNUMERICTYPE_TW_UINT8     = TWTY_UINT8,
   TWAINNUMERICTYPE_TW_UINT16    = TWTY_UINT16,
   TWAINNUMERICTYPE_TW_UINT32    = TWTY_UINT32,
   TWAINNUMERICTYPE_TW_BOOL      = TWTY_BOOL,
   TWAINNUMERICTYPE_TW_FIX32     = TWTY_FIX32,
   TWAINNUMERICTYPE_TW_FRAME     = TWTY_FRAME,
   TWAINNUMERICTYPE_TW_STR32     = TWTY_STR32,
   TWAINNUMERICTYPE_TW_STR64     = TWTY_STR64,
   TWAINNUMERICTYPE_TW_STR128    = TWTY_STR128,
   TWAINNUMERICTYPE_TW_STR255    = TWTY_STR255,
   TWAINNUMERICTYPE_TW_STR1024   = TWTY_STR1024,
   TWAINNUMERICTYPE_TW_UNI512    = TWTY_UNI512
} LTWAINNUMERICTYPE;

// Save template strcutures
typedef struct _SAVETEMPALTE
{
   L_TCHAR *   lpszTemplateFile;
   L_UINT      uFlags;
   LPCTSTR     lpTemplate; 
   DLGPROC     lpDlgProc; 
   L_INT       nOKButtonID; 
} SAVETEMPLATE, L_FAR * pSAVETEMPLATE;

#define SAVETEMPLATESIZE sizeof(SAVETEMPLATE)

typedef struct _FASTCONFIG
{
   L_UINT   uTransferMode;
   L_INT    nFileFormat;
   L_UINT32 ulBufferSize; // -1 : means not available, or not tested yet.
   L_UINT   uTime;       // -1 : means not available, or not tested yet.
   L_INT    nBitsPerPixel;
   L_BOOL   bSuccess;
} FASTCONFIG, L_FAR * pFASTCONFIG;

// TWAIN structure LTWAINSOURCEINFO
typedef struct _LTWAINSOURCEINFO
{
   L_TCHAR *   pszTwnSourceName;
   L_TCHAR *   pszTwnProductFamily;
   L_TCHAR *   pszTwnManufacturer;
} LTWAINSOURCEINFO, L_FAR * pLTWAINSOURCEINFO;

#ifdef __cplusplus
extern "C"
{
#endif

// Callback function
typedef L_INT (pEXT_CALLBACK LTWAINBITMAPCALLBACK)(HTWAINSESSION hSession, pBITMAPHANDLE pBitmap, L_VOID * pUserData);
typedef L_INT (pEXT_CALLBACK LTWAINSOURCECALLBACK)(HTWAINSESSION hSession, pLTWAINSOURCE pSource, L_VOID * pUserData);
typedef L_INT (pEXT_CALLBACK LTWAINCAPABILITYCALLBACK)(HTWAINSESSION hSession, L_UINT uCap, pTW_CAPABILITY pCapabiltiy, L_VOID * pUserData);
typedef L_INT (pEXT_CALLBACK LTWAINSETPROPERTYCALLBACK)(HTWAINSESSION hSession, L_UINT uCap, L_INT nStatus, L_VOID * pValue, L_VOID * pUserData);
typedef L_INT (pEXT_CALLBACK LTWAINSAVECAPCALLBACK)(HTWAINSESSION hSession, pTW_CAPABILITY pCapability, L_VOID * pUserData);
typedef L_INT (pEXT_CALLBACK LTWAINSAVEERRORCALLBACK)(HTWAINSESSION hSession, pTW_CAPABILITY pCapability, L_UINT uError, L_VOID * pUserData);
typedef L_INT (pEXT_CALLBACK LTWAINFINDFASTCONFIG)(HTWAINSESSION hSession, pFASTCONFIG pResConfig, L_VOID *pUserData);
typedef L_INT (pEXT_CALLBACK LTWAINSOURCEINFOCALLBACK)(HTWAINSESSION hSession, pLTWAINSOURCEINFO pSourceInfo, L_VOID * pUserData);
typedef L_VOID (pEXT_CALLBACK LTWAINACQUIRECALLBACK)(HTWAINSESSION hSession, L_INT nPage, L_TCHAR L_FAR * pszFileName, L_BOOL bFinishScan, L_VOID *pUserData);

// Twain Functions
L_INT EXT_FUNCTION L_TwainInitSession (pHTWAINSESSION phSession, pAPPLICATIONDATA pAppData);
L_INT EXT_FUNCTION L_TwainEndSession (pHTWAINSESSION phSession);
L_INT EXT_FUNCTION L_TwainSetProperties (HTWAINSESSION hSession, pLTWAINPROPERTIES pltProperties, L_UINT uFlags, LTWAINSETPROPERTYCALLBACK pfnCallBack, L_VOID * pUserData);
L_INT EXT_FUNCTION L_TwainGetProperties (HTWAINSESSION hSession, pLTWAINPROPERTIES pltProperties, L_UINT uFlags);
L_INT EXT_FUNCTION L_TwainAcquireList (HTWAINSESSION hSession, HBITMAPLIST hBitmap, L_TCHAR * lpszTemplateFile, L_UINT uFlags);
L_INT EXT_FUNCTION L_TwainAcquire (HTWAINSESSION hSession, pBITMAPHANDLE pBitmap, LTWAINBITMAPCALLBACK pfnCallBack, L_UINT uFlags, L_TCHAR * lpszTemplateFile, L_VOID * pUserData);
L_INT EXT_FUNCTION L_TwainSelectSource (HTWAINSESSION hSession, pLTWAINSOURCE pltSource);
L_INT EXT_FUNCTION L_TwainGetSources (HTWAINSESSION hSession, LTWAINSOURCECALLBACK pfnCallBack, L_UINT uFlags, L_VOID * pUserData);
L_INT EXT_FUNCTION L_TwainQueryProperty (HTWAINSESSION hSession, L_UINT uCapability, pLTWAINPROPERTYQUERY* ppltProperty);
L_INT EXT_FUNCTION L_TwainStartCapsNeg (HTWAINSESSION hSession);
L_INT EXT_FUNCTION L_TwainEndCapsNeg (HTWAINSESSION hSession);
L_INT EXT_FUNCTION L_TwainSetCapability (HTWAINSESSION hSession, pTW_CAPABILITY pCapability, L_UINT uFlags);
L_INT EXT_FUNCTION L_TwainGetCapability (HTWAINSESSION hSession, pTW_CAPABILITY pCapability, L_UINT uFlags);
L_INT EXT_FUNCTION L_TwainEnumCapabilities (HTWAINSESSION hSession, LTWAINCAPABILITYCALLBACK pfnCallBack, L_UINT uFlags, L_VOID * pUserData);
L_INT EXT_FUNCTION L_TwainCreateNumericContainerOneValue (TW_CAPABILITY * pCapability, LTWAINNUMERICTYPE Type, L_UINT32 uValue);
L_INT EXT_FUNCTION L_TwainCreateNumericContainerRange (TW_CAPABILITY * pCapability, LTWAINNUMERICTYPE Type, L_UINT32 uMinValue, L_UINT32 uMaxValue, L_UINT32 uStepSize, L_UINT32 uDefaultValue, L_UINT32 uCurrentValue);
L_INT EXT_FUNCTION L_TwainCreateNumericContainerArray (TW_CAPABILITY * pCapability, LTWAINNUMERICTYPE Type, L_UINT32 uNumOfItems, L_VOID * pData);
L_INT EXT_FUNCTION L_TwainCreateNumericContainerEnum (TW_CAPABILITY * pCapability, LTWAINNUMERICTYPE Type, L_UINT32 uNumOfItems, L_UINT32 uCurrentIndex, L_UINT32 uDefaultIndex, L_VOID * pData);
L_INT EXT_FUNCTION L_TwainGetNumericContainerValue (TW_CAPABILITY * pCapability, L_INT nIndex, L_VOID ** ppValue);
L_INT EXT_FUNCTION L_TwainFreeContainer (TW_CAPABILITY * pCapability);
L_INT EXT_FUNCTION L_TwainFreePropQueryStructure (pLTWAINPROPERTYQUERY * ppltProperty);

L_INT EXT_FUNCTION L_TwainTemplateDlg (HTWAINSESSION hSession, L_TCHAR * lpszTemplateFile, LTWAINSAVECAPCALLBACK pfnCallBack, LTWAINSAVEERRORCALLBACK pfnErCallBack, L_VOID * pUserData);
L_INT EXT_FUNCTION L_TwainOpenTemplateFile (HTWAINSESSION hSession, HTWAINTEMPLATEFILE * phFile, L_TCHAR * lpszTemplateFile, L_UINT uAccess);
L_INT EXT_FUNCTION L_TwainAddCapabilityToFile (HTWAINSESSION hSession, HTWAINTEMPLATEFILE hFile, pTW_CAPABILITY pCapability);
L_INT EXT_FUNCTION L_TwainGetCapabilityFromFile (HTWAINSESSION hSession, HTWAINTEMPLATEFILE hFile, pTW_CAPABILITY * ppCapability, L_UINT uIndex);
L_INT EXT_FUNCTION L_TwainGetNumOfCapsInFile (HTWAINSESSION hSession, HTWAINTEMPLATEFILE hFile, L_UINT * puCapCount);
L_INT EXT_FUNCTION L_TwainCloseTemplateFile (HTWAINSESSION hSession, HTWAINTEMPLATEFILE hFile);

L_INT EXT_FUNCTION L_TwainGetExtendedImageInfo (HTWAINSESSION hSession, TW_EXTIMAGEINFO * ptwExtImgInfo);
L_INT EXT_FUNCTION L_TwainFreeExtendedImageInfoStructure (TW_EXTIMAGEINFO ** pptwExtImgInfo);
L_INT EXT_FUNCTION L_TwainLockContainer (TW_CAPABILITY * pCapability, void ** ppContainer);
L_INT EXT_FUNCTION L_TwainUnlockContainer (TW_CAPABILITY * pCapability);

L_INT EXT_FUNCTION L_TwainGetNumericContainerItemType (TW_CAPABILITY * pCapability, L_INT * pnItemType);
L_INT EXT_FUNCTION L_TwainGetNumericContainerINTValue (TW_CAPABILITY * pCapability, L_INT nIndex, L_INT * pnValue);
L_INT EXT_FUNCTION L_TwainGetNumericContainerUINTValue (TW_CAPABILITY * pCapability, L_INT nIndex, L_UINT * puValue);
L_INT EXT_FUNCTION L_TwainGetNumericContainerBOOLValue (TW_CAPABILITY * pCapability, L_INT nIndex, L_BOOL * pbValue);
L_INT EXT_FUNCTION L_TwainGetNumericContainerFIX32Value (TW_CAPABILITY * pCapability, L_INT nIndex, TW_FIX32 * ptwFix);
L_INT EXT_FUNCTION L_TwainGetNumericContainerFRAMEValue (TW_CAPABILITY * pCapability, L_INT nIndex, TW_FRAME * ptwFrame);
L_INT EXT_FUNCTION L_TwainGetNumericContainerSTRINGValue (TW_CAPABILITY * pCapability, L_INT nIndex, TW_STR1024 twString);
L_INT EXT_FUNCTION L_TwainGetNumericContainerUNICODEValue (TW_CAPABILITY * pCapability, L_INT nIndex, TW_UNI512 twUniCode);

L_INT EXT_FUNCTION L_TwainAcquireMulti(HTWAINSESSION         hSession,
                                       L_TCHAR L_FAR *       pszBaseFileName,
                                       L_UINT                uFlags,
                                       L_UINT                uTransferMode,
                                       L_INT                 nFormat,
                                       L_INT                 nBitsPerPixel,
                                       L_BOOL                bMultiPageFile,
                                       L_UINT32              uUserBufSize,
                                       L_BOOL                bUsePrefferedBuffer,
                                       LTWAINACQUIRECALLBACK pfnCallBack,
                                       L_VOID              * pUserData);

L_BOOL EXT_FUNCTION L_IsTwainAvailable(HWND hWnd);

L_INT EXT_FUNCTION L_TwainFindFastConfig(HTWAINSESSION        hSession,
                                         L_TCHAR L_FAR       * pszWorkingFolder,
                                         L_UINT               uFlags,
                                         L_INT                nBitsPerPixel,
                                         L_INT                nBufferIteration,
                                         pFASTCONFIG          pInFastConfigs,
                                         L_INT                nInFastConfigsCount,
                                         pFASTCONFIG        * ppTestConfigs,
                                         L_INT              * pnTestConfigsCount,
                                         pFASTCONFIG          pOutBestConfig,
                                         LTWAINFINDFASTCONFIG pfnCallBack,
                                         L_VOID             * pUserData);

L_INT EXT_FUNCTION L_TwainGetScanConfigs(HTWAINSESSION   hSession,
                                         L_INT           nBitsPerPixel,
                                         L_UINT          uTransferMode,
                                         L_INT           nBufferIteration,
                                         pFASTCONFIG    *ppFastConfig,
                                         L_INT          *pnFastConfigCount);

L_INT EXT_FUNCTION L_TwainFreeScanConfig(HTWAINSESSION   hSession,
                                         pFASTCONFIG    *ppFastConfig,
                                         L_INT           nFastConfigCount);

L_INT EXT_FUNCTION L_TwainGetSources2(HTWAINSESSION            hSession,
                                      LTWAINSOURCEINFOCALLBACK pfnCallBack,
                                      L_UINT                   uFlags,
                                      L_VOID                 * pUserData);

#ifdef __cplusplus
};
#endif

#endif
