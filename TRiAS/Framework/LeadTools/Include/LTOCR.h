
/*
   ltOCR.h - LEAD OCR Module header file
   Copyright (c) 1991-2001 by LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTOCR_H_
#define _LTOCR_H_

#define _HEADER_ENTRY_
#include "ltpck.h"

#include "L_OCRERR.H"

/*----------------------------------------------------------------------------+
|                          DEFINES SECTION                                    |
+----------------------------------------------------------------------------*/

/*Language Information Defines */
typedef enum
{
   ALL_LANGUAGE_GROUPS_INFO = 0,
   LANGUAGE_SUB_GROUP_INFO,
   CURRENT_LANGUAGE_SUB_GROUP_INFO,
   CURRENT_LANGUAGE_GROUP_CHARACTERS,
} LANGUAGEINFOFLAGS;

typedef enum
{
   LANG_GRP_ID_LATIN2   =1250,
   LANG_GRP_ID_CYRILLIC =1251,
   LANG_GRP_ID_LATIN1   =1252,
   LANG_GRP_ID_GREEK    =1253,
   LANG_GRP_ID_TURKISH  =1254,
   LANG_GRP_ID_BALTIC   =1257 
} LANGUAGE_GROUP_IDS;

typedef enum
{
   LANG_PACK_ID_ASCIIENG     =47,
   /*[latin1] */
   LANG_PACK_ID_ENGLISH      =1,
   LANG_PACK_ID_GERMAN       =2,
   LANG_PACK_ID_FRENCH       =3,
   LANG_PACK_ID_SPANISH      =4,
   LANG_PACK_ID_ITALIAN      =5,
   LANG_PACK_ID_DUTCH        =6,
   LANG_PACK_ID_SWEDISH      =7,
   LANG_PACK_ID_NORSK        =8,
   LANG_PACK_ID_FINNISH      =9,
   LANG_PACK_ID_DANISH       =10,
   LANG_PACK_ID_PORT         =11,
   LANG_PACK_ID_CATALAN      =37,
   LANG_PACK_ID_AFRIKAANS    =50,
   LANG_PACK_ID_AYMARA       =52,
   LANG_PACK_ID_BASQUE       =53,
   LANG_PACK_ID_BRETON       =54,
   LANG_PACK_ID_FAROESE      =57,
   LANG_PACK_ID_FLEMISH      =58,
   LANG_PACK_ID_FRIULIAN     =59,
   LANG_PACK_ID_GAELIC       =60,
   LANG_PACK_ID_GALICIAN     =61,
   LANG_PACK_ID_GREENLANDIC  =62,
   LANG_PACK_ID_ICELANDIC    =64,
   LANG_PACK_ID_INDONESIAN   =65,
   LANG_PACK_ID_LATIN        =67,
   LANG_PACK_ID_MALAYSIAN    =72,
   LANG_PACK_ID_PIGINENGLISH =73,
   LANG_PACK_ID_SWAHILI      =78,
   LANG_PACK_ID_TAHITIAN     =79,
   LANG_PACK_ID_WELSH        =81,
   LANG_PACK_ID_FRISIANW     =82,
   LANG_PACK_ID_ZULU         =83,

   /* [latin2] */
   LANG_PACK_ID_POLISH       =32,
   LANG_PACK_ID_CZECH        =33,
   LANG_PACK_ID_HUNGAR       =34,
   LANG_PACK_ID_ROMANIAN     =40,
   LANG_PACK_ID_ALBANIAN     =51,
   LANG_PACK_ID_CROATIAN     =56,
   LANG_PACK_ID_SORBIANL     =70,
   LANG_PACK_ID_SBCROATIAN   =75,
   LANG_PACK_ID_SLOVAK       =76,
   LANG_PACK_ID_SLOVENIAN    =77,
   LANG_PACK_ID_SORBIANU     =80,

   /* [cyrillic] */
   LANG_PACK_ID_RUSSIAN      =13,
   LANG_PACK_ID_UKRANIAN     =38,
   LANG_PACK_ID_BYELORUSSIAN =39,
   LANG_PACK_ID_BULGARIAN    =55,
   LANG_PACK_ID_MACEDONIANC  =71,
   LANG_PACK_ID_SERBIAN      =74,

   /*[greek] */
   LANG_PACK_ID_GREEK        =36,

   /* [turkish] */
   LANG_PACK_ID_TURKISH      =35,
   LANG_PACK_ID_KURDISHLAT   =66,

   /* [baltic] */
   LANG_PACK_ID_ESTONIAN     =49,
   LANG_PACK_ID_HAWAIIAN     =63,
   LANG_PACK_ID_LATVIAN      =68,
   LANG_PACK_ID_LITHUANIAN   =69,
} LANGUAGE_IDS;

#define PROCESS_PAGE_OCR      0x001
#define PROCESS_PAGE_ORIENT   0x002
#define PROCESS_PAGE_SKEW     0x004
#define PROCESS_PAGE_USERDATA 0x008

#define SEGMENT_FIND_LOCKED   0x001
#define SEGMENT_FIND_ALL      0x002
#define SEGMENT_MASK_IMAGE    0x004

typedef enum
{
   EXPORT_PAGE = 1,
   EXPORT_PAGE_TEXT,
   EXPORT_PAGE_PICTURE,
} EXPORT_IMAGEFLAGS;

typedef enum 
{
   DEFAULT_IMAGE = 0,
   BINARY_IMAGE  = 0x01,
   GRAY4_IMAGE   = 0x02,
   GRAY8_IMAGE   = 0x04,
   COLOR4_IMAGE  = 0x08,
   COLOR8_IMAGE  = 0x10,
   COLOR24_IMAGE = 0x20
} IMAGECOLOR;

typedef enum
{
   PAGE_BASIC = 0,
   PAGE_BILEVEL,
} PAGETYPE;

typedef enum
{
   PAGE_IN_MEMORY = 0,
   PAGE_ON_DISK,
   PAGE_IN_LIMBO,
   PAGE_IN_BITBUCKET,
} PAGE_MEMORY;

#define GET_FIRST_SEGMENT  0x001
#define GET_NEXT_SEGMENT   0x002

typedef enum
{
   SEG_NO_TYPE = 0,
   SEG_IGNORE_TYPE,
   SEG_IMAGE_TYPE,
   SEG_TEXT_TYPE,
   SEG_VRULE_TYPE,
   SEG_HRULE_TYPE,
   SEG_TYPE_PASTLAST,
} SEGMENT_TYPE;

typedef enum
{
   SEG_NO_SUBTYPE = 0,
   SEG_SUB_TABLE,
   SEG_SUB_HEADLINE,
   SEG_SUB_TIMESTAMP,
   SEG_SUB_LINEART,
   SEG_SUB_HALFTONE,
   SEG_SUB_INSET,
   SEG_SUB_CAPTION,
   SEG_SUB_PAGE_FOOTER,
   SEG_SUB_PAGE_HEADER,
   SEG_SUB_VRULING,
   SEG_SUB_HRULING,
   SEG_SUB_NOISE,
   SEG_SUB_CELL,
   SEG_SUB_RESERVED,
   SEG_SUB_PASTLAST,
} SEGMENT_SUBTYPE;

typedef enum
{
   FG_WHITE = 0,
   FG_BLACK,
   FG_UNKNOWN,
   FG_PASTLAST,
} TEXT_FGCOLOR;

typedef enum
{
   GRAMMAR_WORD = 0,
   GRAMMAR_LINE,
   GRAMMAR_PASTLAST,
} GRAMMARMODE;

typedef enum
{
   LEX_PREFERENCE = 0,
   LEX_ABSOLUTE,
   LEX_MODE_PASTLAST
} LEXICAL_MODE;

#define SEG_HIT_BACKGROUND          0x0001
#define SEG_HIT_FOREGROUND          0x0002
#define SEG_HIT_PRIMARY             0x0004
#define SEG_HIT_SEGMENT             0x0008
#define SEG_HIT_MASK                0x0010
#define SEG_HIT_ALL                 0x00FF

#define SEG_EXCLUDE_HIT_NONE        0x0100
#define SEG_EXCLUDE_HIT_WHITETEXT   0x0200
#define SEG_EXCLUDE_HIT_TRANSPARENT 0x0400

#define RECOGNIZE_ALL_PAGES      0x002

#define RECOGNIZE_NONE           0x004
#define RECOGNIZE_AUTO           0x008
#define RECOGNIZE_DOTMATRIX      0x010
#define RECOGNIZE_FAX            0x020
#define RECOGNIZE_NEWSPAPER      0x040

typedef enum
{
   TEXT_CONV_AMI_PRO_20 = 1,
   TEXT_CONV_AMI_PRO_30,
   TEXT_CONV_ASCII_SMART,
   TEXT_CONV_ASCII_STD,
   TEXT_CONV_ASCII_STD_DOS,
   TEXT_CONV_ASCII_STRIPPED,
   TEXT_CONV_CSV_ASCII,
   TEXT_CONV_CSV_ASCII_TAB,
   TEXT_CONV_DBASE_IV,
   TEXT_CONV_DCA_RTF,
   TEXT_CONV_DCA_RFT = 10,
   TEXT_CONV_DISPLAY_WRITE_5,
   TEXT_CONV_EXCEL_MAC_30_70,
   TEXT_CONV_EXCEL_30,
   TEXT_CONV_EXCEL_40,
   TEXT_CONV_EXCEL_50,
   TEXT_CONV_EXCEL_97,
   TEXT_CONV_FRAMEMAKER,
   TEXT_CONV_SIMPLE_HTML = 19,
   TEXT_CONV_INTERLEAF = 21,
   TEXT_CONV_LOTUS123,
   TEXT_CONV_LOTUS_WORD_PRO,
   TEXT_CONV_MULTIMATE_ADV,
   TEXT_CONV_POSTSCRIPT,
   TEXT_CONV_PROF_WRITE_20,
   TEXT_CONV_PROF_WRITE_22,
   TEXT_CONV_QUATRO_PRO_4_WIN,
   TEXT_CONV_RTF_MAC,
   TEXT_CONV_WIN_WRITE,
   TEXT_CONV_WORD_4_WIN_2X,
   TEXT_CONV_WORD_60,
   TEXT_CONV_WORD_70,
   TEXT_CONV_WORD_97,
   TEXT_CONV_WORDPERFECT_42,
   TEXT_CONV_WORDPERFECT_51,
   TEXT_CONV_WORDPERFECT_60,
   TEXT_CONV_WORDPERFECT_61,
   TEXT_CONV_WORDPERFECT_70,
   TEXT_CONV_WORDSTAR,

   /* The PDF format is supported only for output Latin1 */
   TEXT_CONV_ADOBE_PDF_NORM,     /* Adobe PDF "Normal" */
   TEXT_CONV_ADOBE_PDF_WORDIM,   /* Adobe PDF "Normal" with images for suspect words. See L_OCRGetPDFThreshold */
   TEXT_CONV_ADOBE_PDF_IMGPTEXT, /* Adobe PDF original image on top of invisible text.
                                    Currently only black and white images are output regardless of input page type */
   TEXT_CONV_ADOBE_PDF_IMGONLY,  /* Adobe PDF original image only. 
                                    Currently only black and white images are output regardless of input page type. */

   TEXT_CONV_ASCII_SMART_DOS = 45,
   TEXT_CONV_ASCII_STRIPPED_DOS,
   TEXT_CONV_MS_WORKS,
   TEXT_CONV_WORDPERFECT_80,

   TEXT_OUT_XDOC_LITE = 1001,
   TEXT_OUT_XDOC,
   TEXT_OUT_ISO,
   TEXT_OUT_UNICODE,
   TEXT_OUT_8BIT,
} TEXT_CONVTYPE;

#define GET_RESULT_TEXT_STYLES      0x001
#define GET_RESULT_PICS             0x002
#define GET_RESULT_RECOG_PAGES      0x004
#define GET_RESULT_LAST_RECOG_PAGE  0x008

typedef enum
{
   VERIFMODE_CHARACTER,
   VERIFMODE_WORD
} VERIFMODE_VAL;

#define GET_SUGGEST_FILE_NAME          0x001
#define GET_FIRST_ALTERNATE_SPELLING   0x002
#define GET_NEXT_ALTERNATE_SPELLING    0x004

typedef enum
{
   VERIFY_RESPONSE_ACCEPT = 0,
   VERIFY_RESPONSE_ACCEPTWORD,

   VERIFY_RESPONSE_CANCEL,
   VERIFY_RESPONSE_CHANGECURRENT,
   VERIFY_RESPONSE_JOINLEFT,
   VERIFY_RESPONSE_JOINRIGHT,
   VERIFY_RESPONSE_NOISE,
   VERIFY_RESPONSE_MOVELEFT,
   VERIFY_RESPONSE_MOVERIGHT,
   VERIFY_RESPONSE_TURNOFF,
   VERIFY_RESPONSE_UNDO,
} TEXT_VERIFY_CMD;

#define VERIFY_FLAG_NONE                  0
#define VERIFY_FLAG_RULER                 0x001
#define VERIFY_FLAG_WRDCNTX               0x002
#define VERIFY_FLAG_WRDRGST               0x004
#define VERIFY_FLAG_REVVIDEO              0x008
#define VERIFY_FLAG_SHOW_ENTIRE_IMAGE     0x100

typedef enum
{
   DRAW_INVERT = 0,
   DRAW_SHOWSTRING,
   DRAW_ERASE,
   DRAW_OUTLINE,
   DRAW_PASTLAST,
} DRAW_COMMAND;

typedef enum
{
   XDOC_OPTYP_STRING = 1,
   XDOC_OPTYP_NUM,
   XDOC_OPTYP_CHAR,
} XDOC_OPTYP;

typedef enum
{
   FIND_FIRST_TABLE = 0,
   FIND_NEXT_TABLE,
} SEGMENT_TABLE;

#define DEFAULTREGION   0
#define NEXTUNUSED      2011

typedef enum
{
   OCR_DLG_OKSTR = 0, /* Accept All */
   OCR_DLG_CANCELSTR,

   OCR_DLG_MOVE_RIGHTSTR,
   OCR_DLG_MOVE_LEFTSTR,
   OCR_DLG_JOIN_RIGHTSTR,
   OCR_DLG_JOIN_LEFTSTR,
   OCR_DLG_ACCEPT_WORDSTR,
   OCR_DLG_ACCEPT_GROUP,
   OCR_DLG_MARK_AS_NOISESTR,
   OCR_DLG_UNDOSTR,
   OCR_DLG_ZOOM_IN,
   OCR_DLG_ZOOM_OUT,
} VERIFY_DLGSTR;

typedef enum
{
   EVENT_OCR = 0,
   EVENT_ORIENT,
   EVENT_DESKEW,
   EVENT_FINDSEG,
   EVENT_SEGMENT,
   EVENT_FORMDETECT,
   EVENT_WHITENBACKGROUND,
   EVENT_TEXTTINTDETECT,
   EVENT_OCRCANCEL,
   EVENT_OCRACQUIRING,
   EVENT_RECOGNIZING,
   EVENT_PREPROCESS,
   EVENT_TEXT_OUTPUT,
   EVENT_REGION_MAPPING,
   EVENT_AWAITING_DRAW,
   EVENT_AWAITING_VERIFIER,
   EVENT_ANALYZING_PAGE,
   EVENT_OCRERROR,
   EVENT_TEXTCONVERT,
} PROGRESS_EVENTTYPE;

/*----------------------------------------------------------------------------+
|                          TYPEDEF SECTION                                    |
+----------------------------------------------------------------------------*/
typedef HANDLE L_HOCR;

typedef struct _tagLangInfo
{
   L_CHAR L_FAR *   pszName;
   L_INT32          lID;
   L_BOOL           bAvailable;
   L_BOOL           bInstalled;
} LANGINFO, L_FAR * pLANGINFO;

typedef struct _tagLangIds
{
   L_INT32          lLangGrpId;
   L_INT32 L_FAR *  plLangId;
   L_INT            nLangIdCount;
} LANGIDS, L_FAR * pLANGIDS;

typedef struct _tagExportOptions
{
   EXPORT_IMAGEFLAGS imgFlags;
   IMAGECOLOR        ImgClr;
   L_INT             nXRes;
   L_INT             nYRes;
   L_INT             nPageIndex;
} EXPORTOPTIONS, L_FAR * pEXPORTOPTIONS;

typedef struct _tagPageInfo
{
   L_INT             nBackgroundCount;
   L_INT             nForegroundCount;
   L_INT             nHeight;
   L_INT             nWidth;
   L_UINT32          ulMemUsed;
   L_INT             nXRes;
   L_INT             nYRes;
   PAGE_MEMORY       MemType;
   PAGETYPE          Type;
   L_INT             nSegCount;
} PAGEINFO, L_FAR * pPAGEINFO;

typedef struct _tagCellDescriptor
{
   L_BOOL            bBottomEdge;
   L_BOOL            bLeftEdge;
   L_BOOL            bRightEdge;
   L_BOOL            bTopEdge;
   L_INT32           lBottomRow;
   L_INT32           lTopRow;
   L_INT32           lLeftCol;
   L_INT32           lRightCol;
} CELLDESCRIPTOR, L_FAR * pCELLDESCRIPTOR;

typedef struct _tagImageDescriptor
{
   L_INT32           lStripHeight;
   IMAGECOLOR        OutType;
   L_INT             nOutputScale;
   L_INT             nXRes;
   L_INT             nYRes;
} IMAGEDESCRIPTOR, L_FAR * pIMAGEDESCRIPTOR;

typedef struct _tagLexicalInfo
{
   L_BOOL            bAddReplace;
   L_INT32           lCodePage;
   L_INT32           lNumLangs;
   L_UINT32          ulConstraintId;
   L_INT32 L_FAR *   plLangIds;
   L_CHAR L_FAR *    pszCharSet;
   L_CHAR L_FAR *    pszPattern;
   L_CHAR L_FAR *    pszWordList;
   GRAMMARMODE       GrammarMode;
   LEXICAL_MODE      LexMode;
} LEXICALINFO, L_FAR * pLEXICALINFO;

typedef struct _tagColumn
{
   L_INT32           lLeftEdge;
   L_INT32           lRightEdge;
} COLUMN, L_FAR * pCOLUMN;

typedef struct _tagRow
{
   L_INT32           lBottomEdge;
   L_INT32           lTopEdge;
} ROW, L_FAR * pROW;

typedef struct _tagTableDescriptor
{
   L_BOOL            bOneLineRows;
   L_INT32           lNumCells;
   L_INT32           lNumCols;
   L_INT32           lNumRows;
   pCOLUMN           pColumns;
   pROW              pRows;
   L_INT32 L_FAR *   plCellIDs;
} TABLEDESCRIPTOR, L_FAR * pTABLEDESCRIPTOR;

typedef struct _tagSegmentInfo
{
   L_INT32           lId;
   L_INT32           lStackingOrder;
   L_BOOL            bTransparent;
   SEGMENT_TYPE      SegType;
   L_CHAR L_FAR *    pszName;
   L_CHAR L_FAR *    pszPrefix;
   L_CHAR L_FAR *    pszSuffix;
   TEXT_FGCOLOR      FGTextClr;
   L_INT             nXRes;
   L_INT             nYRes;
   RECT              rcOuterFrame;
   L_INT32           lOutOrder;
   L_INT             nRectCount;
   RECT *            prcRects;
   SEGMENT_SUBTYPE   SegSubType;
   CELLDESCRIPTOR    CellDescriptor;
   IMAGEDESCRIPTOR   ImageDescriptor;
   LEXICALINFO       LexicalInfo;
   TABLEDESCRIPTOR   TableDescriptor;
} SEGMENTINFO, L_FAR * pSEGMENTINFO;

typedef struct _tagSegHitOptions
{
   POINT             ptHit;
   RECT              rcHitSearch;
   L_UINT            uFlags;
   L_BOOL            bHitPoint;
} SEGHITOPTIONS, L_FAR * pSEGHITOPTIONS;


typedef struct _tagOcrInfo
{
   L_INT32           lCurrentSegment;
   L_DOUBLE          dSkewAngleEst;
   L_DOUBLE          dSkewAngleValue;
   L_INT             nSkewConfidence;
   L_DOUBLE          dRotateAngle;
   L_INT             nRecogChars;
   L_INT             nSeenChars;
   L_INT             nRecogWords;
   L_INT             nSeenWords;
   L_INT             nDonePercent;
   L_INT             nTotSegments;
   L_INT             nImageSegments;
   L_INT             nTextSegments;
} OCRINFO, L_FAR * pOCRINFO;

typedef struct _tagOperatingOptions
{
   L_INT             nVerifyThreshold;
   VERIFMODE_VAL     VerifyMode;
   L_INT             nAcceptThreshold;
   L_INT             nQuesThreshold;
   L_BOOL            bUseHdrFtr;
   L_BOOL            bUseMetric;
   L_BOOL            bUseForceSingleCol;
   L_CHAR            szHtmlSupDir[100];
   L_CHAR            szHtmlTitle[256];
   L_BOOL            bUseXDocCharBox;
   L_BOOL            bUseXDocChrConfidence;
   L_BOOL            bUseXDocWBoxPix;
   L_BOOL            bUseXDocWrdBox;
   L_BOOL            bUseXDocWrdConfidence;
   L_BOOL            bEnablePageRecompose;
   L_BOOL            bUseFormsMarkup;
   L_CHAR            cLeftSingleQuote;
   L_CHAR            cRightSingleQuote;
   L_CHAR            cLeftDbleQuote;
   L_CHAR            cRightDbleQuote;
   L_CHAR            cQuestionableChar;
   L_CHAR            cUnrecognizedChar;
   L_CHAR            cDecimalChar;
   L_CHAR            cThousandsChar;
} OPERATINGOPTIONS, L_FAR * pOPERATINGOPTIONS;

typedef struct _tagVerifyOptions
{
   L_BOOL            bEnableVerification;
   L_BOOL            bEnableDrawFeedback;
   L_BOOL            bCharMode;
   L_INT32           lDispWidth;
   L_INT32           lDispHeight;
   L_UINT32          ulFlags;
   L_BOOL            bShowDlg;
   HWND              hParentWnd;
} VERIFYOPTIONS, L_FAR * pVERIFYOPTIONS;

typedef struct _tagVerifyInfo
{
   RECT              rcWord;
   RECT              rcChar;
   L_CHAR L_FAR *    pszWord;
   L_CHAR L_FAR *    pszChar;
} VERIFYINFO, L_FAR * pVERIFYINFO;

typedef struct _tagDrawCommand
{
   RECT              rcDraw;
   L_CHAR L_FAR *    pszDrawString;
   DRAW_COMMAND      Cmd;
} DRAWCOMMAND, L_FAR * pDRAWCOMMAND;

typedef struct _tagPaintVerifyOpt
{
   L_UINT32          ulFlags;
   L_INT             nWidth;
   L_INT             nHeight;
} PAINTVERIFYOPT, L_FAR * pPAINTVERIFYOPT;

typedef struct _tagXDocMarkupOper
{
   XDOC_OPTYP        Type;
   union
   {
      L_INT32        lOper;
      L_UINT32       ulChOper;
      L_CHAR L_FAR * pszOper;
   } VALUE;
} XDOCMARKUPOPER, L_FAR * pXDOCMARKUPOPER;

typedef struct _tagXDocMod
{
   L_UINT32          ulCode;
   L_UINT32          ulMarkupOperCount;
   pXDOCMARKUPOPER   pXDocOper;
} XDOCMOD, L_FAR * pXDOCMOD;

typedef struct _tagOCRProcAnalysis
{
   L_INT32     lPageOrient;
   L_INT32     lSkewAngle;
} OCRPROCANALYSIS, L_FAR * pOCRPROCANALYSIS;

/*----------------------------------------------------------------------------+
|                       CALLBACKS SECTION                                     |
+----------------------------------------------------------------------------*/

typedef L_BOOL (pEXT_CALLBACK OCRPROGRESSCB) (
                                 PROGRESS_EVENTTYPE   ProgressID,
                                 L_INT                nProgressPercent,
                                 L_VOID L_FAR *       pUserData);

typedef L_BOOL (pEXT_CALLBACK VERIFYCALLBACK) (
                                 L_UCHAR L_FAR* puVerifyData,
                                 pVERIFYINFO    pVerifyInfo,
                                 L_VOID L_FAR * pUserData);

typedef L_BOOL (pEXT_CALLBACK DRAWCALLBACK) (
                                 pDRAWCOMMAND   pDrawCmd,
                                 L_INT32        lCmdCount,
                                 L_VOID L_FAR * pUserData);

typedef L_BOOL (pEXT_CALLBACK XDOCPARSECB) (
                                 pXDOCMOD       pXDocMod,
                                 LPCTSTR        pszSearchText,
                                 L_VOID L_FAR * pUserData);

/*----------------------------------------------------------------------------+
|                       FUNCTIONS SECTION                                     |
+----------------------------------------------------------------------------*/

/* Start/shut down OCR functions */
L_INT EXT_FUNCTION L_OCRStartUp(L_HOCR L_FAR * phOCR, L_CHAR L_FAR * pszKey);

L_INT EXT_FUNCTION L_OCRShutDown(L_HOCR L_FAR * phOCR);

/* Language functions */
L_INT EXT_FUNCTION L_OCRGetLangsInfo(
                           L_HOCR            hOCR,
                           LANGUAGEINFOFLAGS LangInfo,
                           L_INT32           lLangID,
                           pLANGINFO *       ppLangInfo,
                           L_INT L_FAR *     pnLangCount,
                           L_CHAR L_FAR **   ppszCharsGrp);

L_INT EXT_FUNCTION L_OCRSetActiveLanguages(
                           L_HOCR            hOCR,
                           pLANGIDS          pLangIds);

/* Page processing */
L_INT EXT_FUNCTION L_OCRProcessPage(
                           L_HOCR            hOCR,
                           L_INT             nPageIndex,
                           L_UINT            uProcessFlags,
                           pOCRPROCANALYSIS  pOcrProc);

L_INT EXT_FUNCTION L_OCRSplitPage(
                           L_HOCR            hOCR,
                           L_INT             nPageIndex,
                           PRECT             prcPage1,
                           PRECT             prcPage2,
                           L_BOOL            bAutoSplit);

/* Page adding functions */
L_INT EXT_FUNCTION L_OCRAddPageFromBitmap(
                           L_HOCR            hOCR,
                           pBITMAPHANDLE     pBitmap,
                           L_INT             nPageIndex);

L_INT EXT_FUNCTION L_OCRAddPagesFromBitmapList(
                           L_HOCR            hOCR,
                           HBITMAPLIST       hList,
                           L_INT             nPageIndex);

L_INT EXT_FUNCTION L_OCRAddPagesFromFile(
                           L_HOCR            hOCR,
                           L_CHAR L_FAR *    pszFileName,
                           L_INT             nPageIndex,
                           L_INT             nOrder,
                           pLOADFILEOPTION   pLoadOptions,
                           pFILEINFO         pFileInfo,
                           L_BOOL            bAddAllPages);

L_INT EXT_FUNCTION L_OCRAddPagesFromMemoryFile(
                           L_HOCR            hOCR,
                           L_CHAR L_FAR *    pBuffer,
                           L_INT             nPageIndex,
                           L_INT             nOrder,
                           L_INT32           nBufferSize,
                           pLOADFILEOPTION   pLoadOptions,
                           pFILEINFO         pFileInfo);

/* Page exporting functions */
L_INT EXT_FUNCTION L_OCRExportPageAsBitmap(
                           L_HOCR            hOCR,
                           pBITMAPHANDLE     pBitmap,
                           pEXPORTOPTIONS    pExportOpts);

L_INT EXT_FUNCTION L_OCRExportPagesAsBitmapList(
                           L_HOCR            hOCR,
                           pHBITMAPLIST      phList,
                           pEXPORTOPTIONS    pExportOpts);

L_INT EXT_FUNCTION L_OCRExportPagesAsFile(
                           L_HOCR            hOCR,
                           L_CHAR L_FAR *    pszFileName,
                           pEXPORTOPTIONS    pExportOpts,
                           L_INT             nFormat,
                           L_INT             nBitsPerPixel,
                           L_INT             nQFactor,
                           pSAVEFILEOPTION   pSaveOptions,
                           L_BOOL            bSaveAllPages);

L_INT EXT_FUNCTION L_OCRExportPagesAsMemoryFile(
                           L_HOCR            hOCR,
                           HANDLE L_FAR *    phHandle,
                           pEXPORTOPTIONS    pExportOpts,
                           L_INT             nFormat,
                           L_INT             nBitsPerPixel,
                           L_INT             nQFactor,
                           L_UINT32 L_FAR *  puSize,
                           pSAVEFILEOPTION   pSaveOptions,
                           L_BOOL            bSaveAllPages);

/* Remove page function */
L_INT EXT_FUNCTION L_OCRRemovePage(
                           L_HOCR            hOCR,
                           L_INT             nPageIndex);

/* Getting page information function */
L_INT EXT_FUNCTION L_OCRGetPageCount(
                           L_HOCR            hOCR,
                           L_INT L_FAR *     pnPageCount);

L_INT EXT_FUNCTION L_OCRGetPageInfo(
                           L_HOCR            hOCR,
                           pPAGEINFO         pPageInfo,
                           L_INT             nPageIndex);

/* Segment utility functions */
L_INT EXT_FUNCTION L_OCRSegmentPage(
                           L_HOCR            hOCR,
                           L_INT             nPageIndex,
                           L_UINT32          ulFlags);

L_INT EXT_FUNCTION L_OCRExportSegment(
                           L_HOCR            hOCR,
                           pBITMAPHANDLE     pBitmap,
                           L_INT             nPageIndex,
                           L_INT32           lSegmentId);

L_INT EXT_FUNCTION L_OCRSegmentHit(
                           L_HOCR            hOCR,
                           L_INT             nPageIndex,
                           pSEGHITOPTIONS    pSegHitOptions,
                           L_INT32 L_FAR *   plSegID,
                           L_INT L_FAR *     pnSegCount);

L_INT EXT_FUNCTION L_OCRFindSegmentTable(
                           L_HOCR            hOCR,
                           L_INT             nPageIndex,
                           SEGMENT_TABLE     Flags,
                           pSEGMENTINFO      pSegInfo);

/* Getting/Setting segment information functions */
L_INT EXT_FUNCTION L_OCRGetSegmentInfo(
                           L_HOCR            hOCR,
                           L_INT             nPageIndex,
                           L_UINT            uFlags,
                           pSEGMENTINFO      pSegmentInfo);

L_INT EXT_FUNCTION L_OCRSetSegment(
                           L_HOCR            hOCR,
                           L_INT             nPageIndex,
                           pSEGMENTINFO      pSegmentInfo,
                           L_BOOL            bAddSegment);

L_INT EXT_FUNCTION L_OCRFreeSegmentInfo(
                           L_HOCR            hOCR,
                           pSEGMENTINFO      pSegmentInfo);

L_INT EXT_FUNCTION L_OCRRemoveSegment(
                           L_HOCR            hOCR,
                           L_INT             nPageIndex,
                           L_INT32           lSegmentID);

/* Recognition functions */
L_INT EXT_FUNCTION L_OCRRecognize(
                           L_HOCR            hOCR,
                           L_INT             nPageIndex,
                           L_UINT32          ulFlags);

L_INT EXT_FUNCTION L_OCRRecognizeSegment(
                           L_HOCR            hOCR,
                           L_INT             nPageIndex,
                           L_INT32           lSegmentID,
                           TEXT_CONVTYPE     TextOutType,
                           L_UINT32          ulFlags,
                           L_CHAR L_FAR *    pszSegText,
                           L_INT L_FAR *     pnSegTextLen);

L_INT EXT_FUNCTION L_OCRSaveDoc(
                           L_HOCR            hOCR,
                           L_UINT32          ulFlags,
                           TEXT_CONVTYPE     TextOutType,
                           L_CHAR L_FAR *    pszOutFileName,
                           L_CHAR L_FAR *    pszStylePrefix);

/* Training utility functions */
L_INT EXT_FUNCTION L_OCRSetTrainingData(
                           L_HOCR            hOCR,
                           L_UCHAR L_FAR *   pucData,
                           L_INT32           lDataLength);

L_INT EXT_FUNCTION L_OCRGetTrainingData(
                           L_HOCR            hOCR,
                           L_UCHAR L_FAR *   pucData,
                           L_INT32 L_FAR *   plDataLength);

L_INT EXT_FUNCTION L_OCRSetTrainingFile(
                           L_HOCR            hOCR,
                           L_CHAR L_FAR *    pszFileName);

L_INT EXT_FUNCTION L_OCRLoadTrainingFile(
                           L_HOCR            hOCR,
                           L_CHAR L_FAR *    pszFileName);

/* Recognition utility functions */
L_INT EXT_FUNCTION L_OCRGetSuggestion(
                           L_HOCR            hOCR,
                           L_INT             nPageIndex,
                           L_UINT            uFlags,
                           L_CHAR L_FAR *    pszWord,
                           L_CHAR L_FAR *    pszSuggest,
                           L_INT32 L_FAR *   plSuggestSize);

L_INT EXT_FUNCTION L_OCRSetVerificationResponse(
                           L_HOCR            hOCR,
                           L_CHAR L_FAR *    pszCorrection,
                           TEXT_VERIFY_CMD   VerifyCmd);

L_INT EXT_FUNCTION L_OCRSetVerificationOptions(
                           L_HOCR            hOCR,
                           pVERIFYOPTIONS    pVerifyOpt,
                           VERIFYCALLBACK    pfnVerifyCB,
                           L_VOID L_FAR *    pVerifyData,
                           DRAWCALLBACK      pfnDrawCB,
                           L_VOID L_FAR *    pDrawData);

L_INT EXT_FUNCTION L_OCRPaintVerificationImage(
                           L_HOCR            hOCR,
                           HDC               hDC,
                           pPAINTVERIFYOPT   pPaintVerifyOpt);

/* OCR Information/status and Set/Get options */
L_INT EXT_FUNCTION L_OCRGetInfo(
                           L_HOCR            hOCR,
                           pOCRINFO          pOcrInfo);

L_INT EXT_FUNCTION L_OCRGetOperatingOptions(
                           L_HOCR            hOCR,
                           pOPERATINGOPTIONS pOpOptions);

L_INT EXT_FUNCTION L_OCRSetOperatingOptions(
                           L_HOCR            hOCR,
                           pOPERATINGOPTIONS pOpOptions);

L_INT EXT_FUNCTION L_OCRSetProgressFunction(
                           L_HOCR            hOCR,
                           OCRPROGRESSCB     pfnCallback,
                           L_VOID L_FAR *    pUserData);

/* Parsing XDoc/XDocLite function */
L_INT EXT_FUNCTION L_OCRParseXDoc(
                           L_HOCR            hOCR,
                           L_CHAR L_FAR *    pszFileName,
                           L_INT             nPageIndex,
                           XDOCPARSECB       pfnCallback,
                           L_VOID L_FAR *    pUserData);

/* Custom Verification dialog functions */
L_INT EXT_FUNCTION L_OCRDlgSetString(
                           L_HOCR            hOCR,
                           VERIFY_DLGSTR     VerifyStr,
                           L_CHAR L_FAR *    pszCaption);

L_INT EXT_FUNCTION L_OCRDlgGetString(
                           L_HOCR            hOCR,
                           VERIFY_DLGSTR     VerifyStr,
                           L_CHAR L_FAR *    pszCaption);

L_INT EXT_FUNCTION L_OCRDlgGetStringLen(
                           L_HOCR            hOCR,
                           VERIFY_DLGSTR     VerifyStr,
                           L_UINT L_FAR*     puLen);

HFONT EXT_FUNCTION L_OCRDlgSetFont(
                           L_HOCR            hOCR,
                           HFONT             hFont);

/* Get/Set PDF Word Threshold*/
L_INT EXT_FUNCTION L_OCRGetPDFThreshold(
                           L_HOCR            hOCR,
                           L_INT L_FAR *     pnThreshold);

L_INT EXT_FUNCTION L_OCRSetPDFThreshold(
                           L_HOCR            hOCR,
                           L_INT             nThreshold);

#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif //_LTOCR_H_
