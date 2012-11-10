   typedef enum {
      DLG_HELP_FILEOPEN = 1,
      DLG_HELP_FILESAVE,
      DLG_HELP_COLORRES,
      DLG_HELP_GETANGLE,
      DLG_HELP_GETSIZE,
      DLG_HELP_GETFILTER,
      DLG_HELP_GETCHANGE,
      DLG_HELP_GETRANGE,
      DLG_HELP_GETGAMMA,
      DLG_HELP_GETNOISE,
      DLG_HELP_GETEMBOSS,
      DLG_HELP_WINDOWLEVEL,
      DLG_HELP_GETEFFECT,
      DLG_HELP_GETSHAPE,
      DLG_HELP_GETTEXT,
      DLG_HELP_GETGRADIENT,
      DLG_HELP_GETTRANSITION,
      DLG_HELP_GETDIR,
      DLG_HELP_GETRES,
      DLG_HELP_CONTOUR,
      DLG_HELP_HALFTONE,
      DLG_HELP_COLOR,
   }HelpEventConstants;

   typedef  enum {
      FLT_SPATIAL = 0,
      FLT_BINARY  = 1,
   }FilterTypeConstants;

   typedef  enum {
      DLG_FO_AUTOPROCESS         = 0x00000001,  /* Dlg should autoprocess image and fill the pBitmap */
      DLG_FO_PROGRESSIVE         = 0x00000002,  /* FileOpen Dlg should have Prog. File options */
      DLG_FO_MULTIPAGE           = 0x00000004,  /* FileOpen Dlg should have Multipage options */
      DLG_FO_LOADROTATED         = 0x00000008,  /* FileOpen Dlg should have Load Rotated option */
      DLG_FO_LOADCOMPRESSED      = 0x00000010,  /* FileOpen Dlg should have Load 1-bit compressed option */
      DLG_FO_FILEINFO            = 0x00000020,  /* FileOpen Dlg should have FileInfo button */
      DLG_FO_SHOWPREVIEW         = 0x00000040,  /* FileOpen Dlg should have ThumbNail and should create the */
                                                /* preview if none is stored in the file */
      DLG_FO_SHOWSTAMP           = 0x00000080,  /* FileOpen Dlg should have ThumbNail and should only load */
                                                /* the preview stamp if one is stored in the file */
      DLG_FO_DELPAGE             = 0x00000200,  /* FileOpen Dlg should have Delete Page button */
      DLG_FO_RESDLG              = 0x00000400,  /* If AutoProcess, and format supports resolution, show GetRes dlg */
      DLG_FO_NOFILEMUSTEXIST     = 0x00000800,  /* Do not verify that the path exists */
      DLG_FO_NOPATHMUSTEXIST     = 0x00001000,  /* Do not verify that the file exists */
      DLG_GETRES_95CONTEXTHELP   = 0x00002000,  /* GetRes Dlg should contain context sensitive help icon */
      DLG_FO_FILEINFO_TOTALPAGES = 0x00004000,  /* when filling FILEINFO, get TOTALPAGES */
      DLG_FO_FILEINFO_PDFDLG     = 0x00008000,  /* If AutoProcess, and format is PDF , show PDF options dlg */
      DLG_FO_ENABLESIZING        = 0x00010000,  /* Enable sizing for the dialog */
      DLG_PDFDLG_95CONTEXTHELP   = 0x00020000,  /* PDF Dlg should contain context sensitive help icon */
   }FileOpenDlgConstants;

   typedef  enum {
      DLG_FS_AUTOPROCESS         = 0x00000001,  /* Dlg should autoprocess image and fill the pBitmap */
      DLG_FS_PROGRESSIVE         = 0x00000002,  /* FileSave Dlg should have Prog. File options */
      DLG_FS_MULTIPAGE           = 0x00000004,  /* FileSave Dlg should have Multipage options */
      DLG_FS_STAMP               = 0x00000008,  /* FileSave Dlg should have save with stamp options */
      DLG_FS_QFACTOR             = 0x00000010,  /* FileSave Dlg should have QFactor option */
      DLG_FS_ENABLESIZING        = 0x00000100,  /* Enable sizing for the dialog */
   }FileSaveDlgConstants;

   typedef enum {
      DLG_GD_95CONTEXTHELP       = 0x00000002,  /* Dlg should contain context sensitive help icon */
   }GetDirDlgConstants;

   /* file save format option constants for L_DlgFileSave*/
   /* top-level formats */
   typedef  enum {
      DLG_FS_LEAD24 = 0,
      DLG_FS_LEAD8,
      DLG_FS_LEAD1BIT,
      DLG_FS_JFIF24,
      DLG_FS_JFIF16,
      DLG_FS_JFIF12,
      DLG_FS_JFIF8,
      DLG_FS_CALS,
      DLG_FS_PNG1,
      DLG_FS_PNG4,
      DLG_FS_PNG8,
      DLG_FS_PNG24,
      DLG_FS_PNG32,
      DLG_FS_DICOM8,
      DLG_FS_DICOM16,
      DLG_FS_DICOM24,
      DLG_FS_FAX,
      DLG_FS_EPS,
      DLG_FS_EXIF,
      DLG_FS_FPX24,
      DLG_FS_FPX8,
      DLG_FS_IMG,
      DLG_FS_GIF1,
      DLG_FS_GIF2,
      DLG_FS_GIF3,
      DLG_FS_GIF4,
      DLG_FS_GIF5,
      DLG_FS_GIF6,
      DLG_FS_GIF7,
      DLG_FS_GIF8,
      DLG_FS_IOCA,
      DLG_FS_MODCA,
      DLG_FS_PCT1,
      DLG_FS_PCT4,
      DLG_FS_PCT8,
      DLG_FS_PCT24,
      DLG_FS_MAC,
      DLG_FS_AWD,
      DLG_FS_MSP,
      DLG_FS_OS2BMP1,
      DLG_FS_OS2BMP4,
      DLG_FS_OS2BMP8,
      DLG_FS_OS2BMP24,
      DLG_FS_PCX1,
      DLG_FS_PCX4,
      DLG_FS_PCX8,
      DLG_FS_PCX24,
      DLG_FS_PSD1,
      DLG_FS_PSD8,
      DLG_FS_PSD24,
      DLG_FS_RAS1,
      DLG_FS_RAS4,
      DLG_FS_RAS8,
      DLG_FS_RAS24,
      DLG_FS_RAS32,
      DLG_FS_TGA8,
      DLG_FS_TGA16,
      DLG_FS_TGA24,
      DLG_FS_TGA32,
      DLG_FS_TIFF1,
      DLG_FS_TIFF2,
      DLG_FS_TIFF3,
      DLG_FS_TIFF4,
      DLG_FS_TIFF5,
      DLG_FS_TIFF6,
      DLG_FS_TIFF7,
      DLG_FS_TIFF8,
      DLG_FS_TIFF12,
      DLG_FS_TIFF16,
      DLG_FS_TIFF24,
      DLG_FS_TIFF32,
      DLG_FS_BMP1,
      DLG_FS_BMP4,
      DLG_FS_BMP8,
      DLG_FS_BMP16,
      DLG_FS_BMP24,
      DLG_FS_BMP32,
      DLG_FS_WFX,
      DLG_FS_WMF8,
      DLG_FS_WMF24,
      DLG_FS_EMF8,
      DLG_FS_EMF24,
      DLG_FS_WPG1,
      DLG_FS_WPG4,
      DLG_FS_WPG8,
      DLG_FS_ICO1,
      DLG_FS_ICO4,
      DLG_FS_ICO8,
      DLG_FS_ICO24,
      DLG_FS_CUR1,
      DLG_FS_CUR4,
      DLG_FS_CUR8,
      DLG_FS_CUR24,
      DLG_FS_JBIG1,
      DLG_FS_JBIG2,
      DLG_FS_JBIG3,
      DLG_FS_JBIG4,
      DLG_FS_JBIG5,
      DLG_FS_JBIG6,
      DLG_FS_JBIG7,
      DLG_FS_JBIG8,
      DLG_FS_CUT,
      DLG_FS_PPM,
      DLG_FS_PGM,
      DLG_FS_PBM,
      DLG_FS_IFF1,
      DLG_FS_IFF2,
      DLG_FS_IFF3,
      DLG_FS_IFF4,
      DLG_FS_IFF5,
      DLG_FS_IFF6,
      DLG_FS_IFF7,
      DLG_FS_IFF8,
      DLG_FS_IFF24,
      DLG_FS_XBM,
      DLG_FS_XPM8,
      DLG_FS_XPM16,
      DLG_FS_XPM24,
      DLG_FS_XPM32,
      DLG_FS_ITG,
      DLG_FS_TIFF48,
      DLG_FS_TIFF64,
      DLG_FS_FLC8,
      DLG_FS_ANI1,
      DLG_FS_ANI4,
      DLG_FS_ANI8,
      DLG_FS_ANI24,
      DLG_FS_XWD10_1,
      DLG_FS_XWD10_4,
      DLG_FS_XWD10_8,
      DLG_FS_XWD11_1,
      DLG_FS_XWD11_4,
      DLG_FS_XWD11_8,
      DLG_FS_XWD11_16,
      DLG_FS_XWD11_24,
      DLG_FS_XWD11_32,
      DLG_FS_SGI8,
      DLG_FS_SGI24,
      DLG_FS_SGI32,
      DLG_FS_CLP1,
      DLG_FS_CLP4,
      DLG_FS_CLP8,
      DLG_FS_CLP24,
      DLG_FS_RAW,
      DLG_FS_PDF1,
      DLG_FS_PDF2,
      DLG_FS_PDF4,
      DLG_FS_PDF8,
      DLG_FS_PDF24,
      DLG_FS_J2K8,
      DLG_FS_J2K24,
      DLG_FS_CMW8,
      DLG_FS_CMW24,
      DLG_FS_J2K12,
      DLG_FS_J2K16,
      DLG_FS_CMW12,
      DLG_FS_CMW16,

      DLG_FS_WBMP,
      DLG_FS_SCT24,

      DLG_FS_MAX,
   }DlgFileSaveFormatConstants;

   typedef  enum {
      /* FileSave sub-format values        */
      /* LEAD CMP file subtypes (8,24-bit) */
       DLG_FS_SUB_CMP_NONPROGRESSIVE           = 0x0001,
       DLG_FS_SUB_CMP_PROGRESSIVE              = 0x0002,
      /* JPEG file subtypes (24-bit)       */
       DLG_FS_SUB_JPEG24_YUV_444               = 0x0001,
       DLG_FS_SUB_JPEG24_YUV_422               = 0x0002,
       DLG_FS_SUB_JPEG24_YUV_411               = 0x0004,
       DLG_FS_SUB_JPEG24_PROG_444              = 0x0008,
       DLG_FS_SUB_JPEG24_PROG_422              = 0x0010,
       DLG_FS_SUB_JPEG24_PROG_411              = 0x0020,
       DLG_FS_SUB_JPEG24_LOSSLESS              = 0x0040,
      /* JPEG file subtypes (12-bit)       */
       DLG_FS_SUB_JPEG12_YUV_400               = 0x0001,
       DLG_FS_SUB_JPEG12_LOSSLESS              = 0x0002,
      /* JPEG file subtypes (8-bit)        */
       DLG_FS_SUB_JPEG8_YUV_400                = 0x0001,
       DLG_FS_SUB_JPEG8_PROG_400               = 0x0002,
       DLG_FS_SUB_JPEG8_LOSSLESS               = 0x0004,
      /* JPEG 2000 file subtypes (8,24-bit)*/
       DLG_FS_SUB_J2K_STREAM                   = 0x0001,
       DLG_FS_SUB_J2K_JP2                      = 0x0002,
      /* DICOM file subtypes (8-bit)       */
       DLG_FS_SUB_DICOM8_GRAY                  = 0x0001,
       DLG_FS_SUB_DICOM8_COLOR                 = 0x0002,
      /* DICOM file subtypes (Other-bit)   */
       DLG_FS_SUB_DICOM_RLE_GRAY               = 0x0001,
       DLG_FS_SUB_DICOM_RLE_COLOR              = 0x0002,
       DLG_FS_SUB_DICOM_JPEG_GRAY              = 0x0004,
       DLG_FS_SUB_DICOM_LOSSLESSJPEG_GRAY      = 0x0008,
       DLG_FS_SUB_DICOM_JPEG_COLOR             = 0x0010,
       DLG_FS_SUB_DICOM_LOSSLESSJPEG_COLOR     = 0x0020,
      /* RAW FAX, IOCA, & MODCA subtypes   */
       DLG_FS_SUB_FAX_G3_1D                    = 0x0001,
       DLG_FS_SUB_FAX_G3_2D                    = 0x0002,
       DLG_FS_SUB_FAX_G4                       = 0x0004,
      /* EXIF file subtypes                */
       DLG_FS_SUB_EXIF_UNCOMPRESSEDRGB         = 0x0001,
       DLG_FS_SUB_EXIF_UNCOMPRESSEDYCC         = 0x0002,
       DLG_FS_SUB_EXIF_JPEG_411                = 0x0004,
       DLG_FS_SUB_EXIF_JPEG_422                = 0x0008,
      /* FPX file subtypes                 */
       DLG_FS_SUB_FPX_UNCOMPRESSED             = 0x0001,
       DLG_FS_SUB_FPX_SINGLECOLOR              = 0x0002,
       DLG_FS_SUB_FPX_DEFQFACTOR               = 0x0004,
       DLG_FS_SUB_FPX_SPECQFACTOR              = 0x0008,
      /* GIF file subtypes                 */
       DLG_FS_SUB_GIF_INTERLACED89A            = 0x0001,
       DLG_FS_SUB_GIF_NONINTERLACED89A         = 0x0002,
      /* OS/2 BMP file subtypes            */
       DLG_FS_SUB_OS2_VER1                     = 0x0001,
       DLG_FS_SUB_OS2_VER2                     = 0x0002,
      /* TIFF file subtypes (1-bit)        */
       DLG_FS_SUB_TIFF1_CCITT                  = 0x0001,
       DLG_FS_SUB_TIFF1_CCITT_G3_1D            = 0x0002,
       DLG_FS_SUB_TIFF1_CCITT_G3_2D            = 0x0004,
       DLG_FS_SUB_TIFF1_CCITT_G4               = 0x0008,
       DLG_FS_SUB_TIFF1_UNCOMPRESSEDRGB        = 0x0010,
       DLG_FS_SUB_TIFF1_RLERGB                 = 0x0020,
       DLG_FS_SUB_TIFF1_LZWRGB                 = 0x0040,
      /* TIFF file subtypes (2,3,4,5,6,7-bit) */
       DLG_FS_SUB_TIFFOTHER_UNCOMPRESSED       = 0x0001,
       DLG_FS_SUB_TIFFOTHER_RLE                = 0x0002,
       DLG_FS_SUB_TIFFOTHER_LZW                = 0x0004,
      /* TIFF file subtypes (8-bit)        */
       DLG_FS_SUB_TIFF8_UNCOMPRESSEDRGB        = 0x0001,
       DLG_FS_SUB_TIFF8_RLERGB                 = 0x0002,
       DLG_FS_SUB_TIFF8_JPEG_GRAY_YCC          = 0x0004,
       DLG_FS_SUB_TIFF8_LOSSLESSJPEG           = 0x0008,
       DLG_FS_SUB_TIFF8_LZWRGB                 = 0x0010,
       DLG_FS_SUB_TIFF8_JBIG                   = 0x0020,
       DLG_FS_SUB_TIFF8_CMP                    = 0x0040,
       DLG_FS_SUB_TIFF8_J2K                    = 0x0080,
       DLG_FS_SUB_TIFF8_CMW                    = 0x0100,
      /* TIFF file subtypes (12-bit)       */
       DLG_FS_SUB_TIFF12_UNCOMPRESSED          = 0x0001,
       DLG_FS_SUB_TIFF12_RLE                   = 0x0002,
       DLG_FS_SUB_TIFF12_LOSSLESSJPEG          = 0x0004,
       DLG_FS_SUB_TIFF12_JPEG_GRAY_YCC         = 0x0008,
       DLG_FS_SUB_TIFF12_LZW                   = 0x0010,
       DLG_FS_SUB_TIFF12_J2K                   = 0x0020,
       DLG_FS_SUB_TIFF12_CMW                   = 0x0040,
      /* TIFF file subtypes (16-bit)       */
       DLG_FS_SUB_TIFF16_UNCOMPRESSED          = 0x0001,
       DLG_FS_SUB_TIFF16_RLE                   = 0x0002,
       DLG_FS_SUB_TIFF16_LOSSLESSJPEG          = 0x0004,
       DLG_FS_SUB_TIFF16_LZW                   = 0x0008,
       DLG_FS_SUB_TIFF16_J2K                   = 0x0010,
       DLG_FS_SUB_TIFF16_CMW                   = 0x0020,
      /* TIFF file subtypes (24-bit)       */
       DLG_FS_SUB_TIFF24_UNCOMPRESSEDRGB       = 0x0001,
       DLG_FS_SUB_TIFF24_UNCOMPRESSEDCMYK      = 0x0002,
       DLG_FS_SUB_TIFF24_UNCOMPRESSEDYCC       = 0x0004,
       DLG_FS_SUB_TIFF24_RLERGB                = 0x0008,
       DLG_FS_SUB_TIFF24_RLECMYK               = 0x0010,
       DLG_FS_SUB_TIFF24_RLEYCC                = 0x0020,
       DLG_FS_SUB_TIFF24_JPEG_YCC_444          = 0x0040,
       DLG_FS_SUB_TIFF24_JPEG_YCC_422          = 0x0080,
       DLG_FS_SUB_TIFF24_JPEG_YCC_411          = 0x0100,
       DLG_FS_SUB_TIFF24_LOSSLESSJPEG          = 0x0200,
       DLG_FS_SUB_TIFF24_LZWRGB                = 0x0400,
       DLG_FS_SUB_TIFF24_LZWCMYK               = 0x0800,
       DLG_FS_SUB_TIFF24_LZWYCC                = 0x1000,
       DLG_FS_SUB_TIFF24_CMP_NONPROGRESSIVE    = 0x2000,
       DLG_FS_SUB_TIFF24_CMP_PROGRESSIVE       = 0x4000,
       DLG_FS_SUB_TIFF24_J2K                   = 0x8000,
       DLG_FS_SUB_TIFF24_CMW                   = 0x00010000,
      /* TIFF file subtypes (32-bit)       */
       DLG_FS_SUB_TIFF32_UNCOMPRESSEDRGB       = 0x0001,
       DLG_FS_SUB_TIFF32_UNCOMPRESSEDCMYK      = 0x0002,
       DLG_FS_SUB_TIFF32_RLERGB                = 0x0004,
       DLG_FS_SUB_TIFF32_RLECMYK               = 0x0008,
       DLG_FS_SUB_TIFF32_LZWRGB                = 0x0010,
       DLG_FS_SUB_TIFF32_LZWCMYK               = 0x0020,
      /* TIFF file subtypes (48-bit)       */
       DLG_FS_SUB_TIFF48_UNCOMPRESSEDRGB       = 0x0001,
       DLG_FS_SUB_TIFF48_LZWRGB                = 0x0002,
      /* TIFF file subtypes (64-bit)       */
       DLG_FS_SUB_TIFF64_UNCOMPRESSEDRGB       = 0x0001,
       DLG_FS_SUB_TIFF64_LZWRGB                = 0x0002,
      /* BMP file subtypes (4 and 8-bit only) */
       DLG_FS_SUB_BMP_UNCOMPRESSED             = 0x0001,
       DLG_FS_SUB_BMP_RLECOMPRESSED            = 0x0002,
      /* WFX file subtypes                 */
       DLG_FS_SUB_WFX_CCITT_G3_1D              = 0x0001,
       DLG_FS_SUB_WFX_CCITT_G4                 = 0x0002,
      /* PPM file subtypes                 */
       DLG_FS_SUB_PPM_ASCII                    = 0x0001,
       DLG_FS_SUB_PPM_BINARY                   = 0x0002,
      /* PGM file subtypes */
       DLG_FS_SUB_PGM_ASCII                    = 0x0001,
       DLG_FS_SUB_PGM_BINARY                   = 0x0002,
      /* PBM file subtypes */
       DLG_FS_SUB_PBM_ASCII                    = 0x0001,
       DLG_FS_SUB_PBM_BINARY                   = 0x0002,
      /* IFF file subtypes */
      /* All BitsPerPixel have subtypes */
       DLG_FS_SUB_IFF_ILBM_RLE                 = 0x0001,
       DLG_FS_SUB_IFF_CAT_RLE                  = 0x0002,
      /* SGI file subtypes */
      /* All BitsPerPixel have subtypes */
       DLG_FS_SUB_SGI_UNCOMPRESSED             = 0x0001,
       DLG_FS_SUB_SGI_RLECOMPRESSED            = 0x0002,
      /* PDF file subtypes (1-bit)       */
       DLG_FS_SUB_PDF1_UNCOMPRESSED            = 0x0001,
       DLG_FS_SUB_PDF1_CCITT_G3_1D             = 0x0002,
       DLG_FS_SUB_PDF1_CCITT_G3_2D             = 0x0004,
       DLG_FS_SUB_PDF1_CCITT_G4                = 0x0008,
      /* PDF file subtypes (8-bit)       */
       DLG_FS_SUB_PDF8_UNCOMPRESSED            = 0x0001,
       DLG_FS_SUB_PDF8_LOSSLESSJPEG            = 0x0002,
      /* PDF file subtypes (24-bit)       */
       DLG_FS_SUB_PDF24_UNCOMPRESSED           = 0x0001,
       DLG_FS_SUB_PDF24_YUV_444                = 0x0002,
       DLG_FS_SUB_PDF24_YUV_422                = 0x0004,
       DLG_FS_SUB_PDF24_YUV_411                = 0x0008,
   }DlgFileSaveSubFormatConstants;

// possible values for uSaveMulti
#ifndef SAVE_OVERWRITE
#define SAVE_OVERWRITE 0
#define SAVE_APPEND    1
#define SAVE_REPLACE   2
#define SAVE_INSERT    3
#endif

   typedef  enum {
      DLG_CR_SHOWPREVIEW      = 0x00000001,  /* shows preview of image */
      DLG_CR_AUTOPROCESS      = 0x00000002,  /* process the image on OK */
      DLG_CR_95CONTEXTHELP    = 0x00000004,  /* Dlg should contain context sensitive help icon */

      DLG_CR_OPENPALFILEBTN   = 0x00000008,  /* Dlg should contain Open palett file button */
      DLG_CR_TOOL             = 0x00000010,  /* Dlg should contain toolbar in the dialog */
      DLG_CR_ORDER            = 0x00000020,  /* color order is an option */
   }ColorResDlgConstants;

   typedef  enum tagColorResFlags{
      CRF_FIXEDPALETTE           = 0x00000001, /* versus custom palette */
      CRF_OPTIMIZEDPALETTE       = 0x00000002, /* versus fixed palette */
      CRF_IDENTITYPALETTE        = 0x00000008, /* versus ALL 256 colors */
      CRF_FASTMATCHPALETTE       = 0x00000020, /* With user, for fast color match */
      CRF_NETSCAPEPALETTE        = 0x00000040, /* use netscape fixed palette */
      CRF_BYTEORDERBGR           = 0x00000004, /* versus RGB */
      CRF_BYTEORDERRGB           = 0x00000000, /* versus BGR */
      CRF_BYTEORDERGRAY          = 0x00000080, /* Convert to grayscale (12 & 16 bit only) */
      CRF_PALETTEOPTIONS         = 0x000003FF, /* Mask to find palette option */
      CRF_USERPALETTE            = 0x00000100, /* user generated palette */
      CRF_SLOWMATCH              = 0x00000200, /* use with CRF_OPTIMIZEDPALETTE to use a slower but more accurate match */
      CRF_FAVORPURECOLORS        = 0x00000400, /* Give colors that are very numerous palette entries of their own */

      CRF_NODITHERING            = 0x00000000, /* No Dithering */
      CRF_FLOYDSTEINDITHERING    = 0x00010000, /* Floyd Stein Dithering */
      CRF_STUCKIDITHERING        = 0x00020000, /* Stucki Dithering */
      CRF_BURKESDITHERING        = 0x00030000, /* Burkes Dithering */
      CRF_SIERRADITHERING        = 0x00040000, /* Sierra Dithering */
      CRF_STEVENSONARCEDITHERING = 0x00050000, /* Stevenson Arce Dithering */
      CRF_JARVISDITHERING        = 0x00060000, /* Jarvis Dithering */
      CRF_ORDEREDDITHERING       = 0x00070000, /* Ordered Dithering */
      CRF_CLUSTEREDDITHERING     = 0x00080000, /* Clustered Dithering */
      CRF_DITHERINGOPTIONS       = 0x00FF0000, /* Mask to find dither option */
   }ColorResFlags;

   typedef  enum {
      DLG_CR_1BIT             = 0x00000001,  /* 1-bit is an option */
      DLG_CR_2BIT             = 0x00000002,  /* 2-bit is an option */
      DLG_CR_3BIT             = 0x00000004,  /* 3-bit is an option */
      DLG_CR_4BIT             = 0x00000008,  /* 4-bit is an option */
      DLG_CR_5BIT             = 0x00000010,  /* 5-bit is an option */
      DLG_CR_6BIT             = 0x00000020,  /* 6-bit is an option */
      DLG_CR_7BIT             = 0x00000040,  /* 7-bit is an option */
      DLG_CR_8BIT             = 0x00000080,  /* 8-bit is an option */
      DLG_CR_12BIT            = 0x00000100,  /* 12-bit is an option */
      DLG_CR_16BIT            = 0x00000200,  /* 16-bit is an option */
      DLG_CR_24BIT            = 0x00000400,  /* 24-bit is an option */
      DLG_CR_32BIT            = 0x00000800,  /* 32-bit is an option */
      DLG_CR_48BIT            = 0x00001000,  /* 48-bit is an option */
      DLG_CR_64BIT            = 0x00002000,  /* 64-bit is an option */
      DLG_CR_BITALL           = 0x00003FFF,  /* All BitsPerPixel are options */
   }ColorResDlgBitConstants;

   typedef  enum {
      DLG_CR_DITHER_NONE      = 0x00004000,  /* no dithering is an option */
      DLG_CR_DITHER_FLOYD     = 0x00008000,  /* floyd dithering is an option */
      DLG_CR_DITHER_STUCKI    = 0x00010000,  /* stucki dithering is an option */
      DLG_CR_DITHER_BURKES    = 0x00020000,  /* burkes dithering is an option */
      DLG_CR_DITHER_SIERRA    = 0x00040000,  /* sierra dithering is an option */
      DLG_CR_DITHER_STEVENSON = 0x00080000,  /* stevenson dithering is an option */
      DLG_CR_DITHER_JARVIS    = 0x00100000,  /* jarvis dithering is an option */
      DLG_CR_DITHER_CLUSTER   = 0x00200000,  /* clustered dithering is an option */
      DLG_CR_DITHER_ORDERED   = 0x00400000,  /* ordered dithering is an option */
      DLG_CR_DITHER_ALL       = 0x007FC000,  /* All dithering methods are options */
   }ColorResDlgDitherConstants;

   typedef  enum {
      DLG_CR_PAL_FIXED        = 0x00800000,  /* fixed palette is an option */
      DLG_CR_PAL_OPTIMIZED    = 0x01000000,  /* fixed palette is an option */
      DLG_CR_PAL_IDENTITY     = 0x02000000,  /* identity palette is an option */
      DLG_CR_PAL_NETSCAPE     = 0x04000000,  /* netscape palette is an option */
      DLG_CR_PAL_SVGA         = 0x08000000,  /* SVGA palette is an option */
      DLG_CR_PAL_UNIFORM      = 0x10000000,  /* Uniform palette is an option */
      DLG_CR_PAL_MSIE         = 0x20000000,  /* MSIE palette is an option */
      DLG_CR_PAL_ALL          = 0x3F800000,  /* All palette options are options */
   }ColorResDlgPaletteConstants;

   typedef  enum {
      DLG_IMG_AUTOPROCESS     = 0x80000000,  /* Dlg should autoprocess image and fill the pBitmap */
      DLG_IMG_SHOWPREVIEW     = 0x40000000,  /* ImageProcess Dlg should preview of image */
      DLG_IMG_HIDEBACKCOLOR   = 0x20000000,  /* GetAngle Dlg should hide Background Color button */
      DLG_IMG_95CONTEXTHELP   = 0x10000000,  /* Dlg should contain context sensitive help icon */
      DLG_IMG_SHOWRESIZEOPT   = 0x08000000,  /* GetAngle Dlg should show resize options */
      DLG_IMG_INIT_DLG        = 0x04000000,  /* Initialize the width and height fields with the user data */

      DLG_IMG_TOOL            = 0x02000000,  /* GetAngle Dlg should show the toolbar */
      DLG_IMG_PERCENTAGE      = 0x01000000,  /* Image resize Dlg should Percentage value combo */
      DLG_IMG_IDENTICALVAL    = 0x00100000,  /* Image resize Dlg should Identical value check box */
      DLG_IMG_MAINTAINASPECT  = 0x00200000,  /* Dlg should Maintain aspect check box */
      DLG_IMG_RESOLUTIONGRP   = 0x00400000,  /* Image resize Dlg should Resolution group information */
      DLG_IMG_USESYSCOLORDLG  = 0x00800000,  /* Use windows color picker dialog */

      DLG_IMG_ROTATE          = 0x00000001,  /* rotate dialog */
      DLG_IMG_SHEAR           = 0x00000002,  /* shear dialog */

      DLG_IMG_GRADIENT        = 0x00000001,   /* gradient dialog */
      DLG_IMG_LAPLACIAN       = 0x00000002,   /* laplacian dialog */
      DLG_IMG_SOBEL           = 0x00000004,   /* sobel dialog */
      DLG_IMG_PREWITT         = 0x00000008,   /* prewitt dialog */
      DLG_IMG_SHIFTDIFF       = 0x00000010,   /* shiftdiff dialog */
      DLG_IMG_LINESEG         = 0x00000020,   /* lineseg dialog */
      DLG_IMG_EROSION         = 0x00000040,   /* erosion dialog */
      DLG_IMG_DILATION        = 0x00000080,   /* dilation dialog */

      DLG_IMG_SHARPEN         = 0x00000001,   /* sharpen dialog */
      DLG_IMG_BRIGHTNESS      = 0x00000002,   /* brightness dialog */
      DLG_IMG_CONTRAST        = 0x00000004,   /* contrast dialog */
      DLG_IMG_SATURATION      = 0x00000008,   /* saturation dialog */
      DLG_IMG_HISTOCONTRAST   = 0x00000010,   /* histo contrast dialog */
      DLG_IMG_HUE             = 0x00000020,   /* hue dialog */
      DLG_IMG_POSTERIZE       = 0x00000040,   /* posterize dialog */
      DLG_IMG_MOSAIC          = 0x00000080,   /* mosaic dialog */
      DLG_IMG_AVERAGE         = 0x00000100,   /* average dialog */
      DLG_IMG_MEDIAN          = 0x00000200,   /* median dialog */
      DLG_IMG_OILIFY          = 0x00000400,   /* oilify dialog */
      DLG_IMG_MIN             = 0x00000800,   /* min filter dialog */
      DLG_IMG_MAX             = 0x00001000,   /* max filter dialog */
      DLG_IMG_SOLARIZE        = 0x00002000,   /* solarize dialog */

      DLG_IMG_ADDNOISE        = 0x0000001C,   /* add noise dialog */
      DLG_IMG_GAMMACORRECT    = 0x0000001D,   /* gamma correct dialog */
      DLG_IMG_EMBOSS          = 0x0000001E,   /* emboss filter dialog */
      DLG_IMG_INTENSITYDETECT = 0x0000001F,   /* intensity detect dialog */

      DLG_IMG_TOOL_RESIZE       = 0x00004000,
      DLG_IMG_TOOL_ONSCREEN     = 0x00008000,
      DLG_IMG_TOOL_SHOWEFFECT   = 0x00010000,
      DLG_IMG_FORCELINKCHANNELS = 0x00020000,  // To Force the dialog to apply "Link all channels" all the times.
   }ImgProcDlgConstants;

   typedef  enum tagWindowLevelDlgConstants{
      DLG_WL_SHOWPREVIEW      = 0x00000001,  /* shows preview of image */
      DLG_WL_AUTOPROCESS      = 0x00000002,  /* process the image on OK */
      DLG_WL_95CONTEXTHELP    = 0x00000004,  /* Dlg should contain context sensitive help icon */
      DLG_WL_USESYSCOLORDLG   = 0x00000008,  /* Use windows color picker dialog */
   }WindowLevelDlgConstants;

// ActiveX error codes
#include "L_OcxErr.h"

   typedef  enum {
      DLG_EFX_SHOWPREVIEW      = 0x00000001,   /* shows preview of image */
      DLG_EFX_AUTOPREVIEW      = 0x00000002,   /* auto preview when options change */
      DLG_EFX_DELAY            = 0x00000004,   /* effect delay is an option */
      DLG_EFX_GRAIN            = 0x00000008,   /* effect grain is an option */
      DLG_EFX_PASSES           = 0x00000010,   /* effect passes is an option */
      DLG_EFX_TRANSPARENT      = 0x00000020,   /* transparency is an option */
      DLG_EFX_WAND             = 0x00000040,   /* wand is an option */
      DLG_EFX_NO_TREEVIEW      = 0x00000080,   /* DO NOT use TreeView */
      DLG_EFX_CLASS_NONE       = 0x00000100,   /* no effect class is option */
      DLG_EFX_CLASS_WIPE       = 0x00000200,   /* linear wipe class is option */
      DLG_EFX_CLASS_WIPERECT   = 0x00000400,   /* rect wipe class is option */
      DLG_EFX_CLASS_WIPECIRCLE = 0x00000800,   /* circle wipe class is option */
      DLG_EFX_CLASS_PUSH       = 0x00001000,   /* push class is option */
      DLG_EFX_CLASS_SLIDE      = 0x00002000,   /* slide class is option */
      DLG_EFX_CLASS_ROLL       = 0x00004000,   /* roll class is option */
      DLG_EFX_CLASS_ROTATE     = 0x00008000,   /* rotate class is option */
      DLG_EFX_CLASS_ZOOM       = 0x00010000,   /* zoom class is option */
      DLG_EFX_CLASS_DRIP       = 0x00020000,   /* drip class is option */
      DLG_EFX_CLASS_BLIND      = 0x00040000,   /* blind class is option */
      DLG_EFX_CLASS_RANDOM     = 0x00080000,   /* random class is option */
      DLG_EFX_CLASS_CHECK      = 0x00100000,   /* check class is option */
      DLG_EFX_CLASS_BLOCKS     = 0x00200000,   /* blocks class is option */
      DLG_EFX_CLASS_CIRCLE     = 0x00400000,   /* circle class is option */
      DLG_EFX_CLASS_ELLIPSE    = 0x00800000,   /* ellipse class is option */
      DLG_EFX_95CONTEXTHELP    = 0x01000000,   /* Dlg should contain context sensitive help icon */
      DLG_EFX_USESYSCOLORDLG   = 0x02000000,   /* Use windows color picker dialog */
   }PaintEffectDlgConstants;

   typedef  enum {
      DLG_GRAD_SHOWPREVIEW       = 0x00000001,  /* shows preview of image */
      DLG_GRAD_AUTOPREVIEW       = 0x00000002,  /* auto preview when options change */
      DLG_GRAD_STARTCOLOR        = 0x00000004,  /* start color is an option */
      DLG_GRAD_ENDCOLOR          = 0x00000008,  /* end color is an option */
      DLG_GRAD_STEPS             = 0x00000010,  /* gradient steps is an option */
      DLG_GRAD_NO_TREEVIEW       = 0x00000020,  /* DO NOT use TreeView */
      DLG_GRAD_CLASS_LINEAR      = 0x00000040,  /* linear gradients are an option */
      DLG_GRAD_CLASS_ANGULAR     = 0x00000080,  /* angular gradients are an option */
      DLG_GRAD_CLASS_RECTANGULAR = 0x00000100,  /* rectangular gradients are an option */
      DLG_GRAD_CLASS_ELLIPTICAL  = 0x00000200,  /* elliptical gradients are an option */
      DLG_GRAD_CLASS_CONICAL     = 0x00000400,  /* conical gradients are an option */
      DLG_GRAD_95CONTEXTHELP     = 0x00000800,  /* Dlg should contain context sensitive help icon */
      DLG_GRAD_USESYSCOLORDLG    = 0x00001000,  /* Use windows color picker dialog */
   }GradientDlgConstants;

   typedef  enum {
      DLG_TRANS_SHOWPREVIEW     = 0x00000001,   /* shows preview of image */
      DLG_TRANS_AUTOPREVIEW     = 0x00000002,   /* auto preview when options change */
      DLG_TRANS_FORECOLOR       = 0x00000004,   /* forecolor is an option */
      DLG_TRANS_BACKCOLOR       = 0x00000008,   /* backcolor is an option */
      DLG_TRANS_DELAY           = 0x00000010,   /* transition delay is an option */
      DLG_TRANS_GRAIN           = 0x00000020,   /* transition grain is an option */
      DLG_TRANS_EFFECT          = 0x00000040,   /* paint effect is an option */
      DLG_TRANS_PASSES          = 0x00000080,   /* transition passes is an option */
      DLG_TRANS_WAND            = 0x00000100,   /* wand is an option */
      DLG_TRANS_TRANSPARENT     = 0x00000200,   /* transparency is an option */
      DLG_TRANS_GRADIENT        = 0x00000400,   /* gradient is an option */
      DLG_TRANS_95CONTEXTHELP   = 0x00000800,   /* Dlg should contain context sensitive help icon */
      DLG_TRANS_USESYSCOLORDLG  = 0x00001000,   /* Use windows color picker dialog */
   }TransitionDlgConstants;

   typedef  enum {
      DLG_SHAPE_SHOWPREVIEW          = 0x00000001,   /* shows preview of image */
      DLG_SHAPE_AUTOPREVIEW          = 0x00000002,   /* auto preview when options change */
      DLG_SHAPE_BACKSTYLE            = 0x00000004,   /* backstyle is an option */
      DLG_SHAPE_FILLSTYLE            = 0x00000008,   /* fillstyle is an option */
      DLG_SHAPE_FORE_BACK_COLOR      = 0x00000010,   /* fore and back colors are options */
      DLG_SHAPE_BORDERSTYLE          = 0x00000020,   /* borderstyle is an option */
      DLG_SHAPE_BORDERWIDTH          = 0x00000040,   /* border width is an option */
      DLG_SHAPE_BORDERCOLOR          = 0x00000080,   /* bordercolor is an option */
      DLG_SHAPE_INNERSTYLE           = 0x00000100,   /* innerbandstyle is an option */
      DLG_SHAPE_INNERWIDTH           = 0x00000200,   /* innerband width is an option */
      DLG_SHAPE_INNER_HILITE_SHADOW  = 0x00000400,   /* innerband colors are options */
      DLG_SHAPE_OUTERSTYLE           = 0x00000800,   /* outerbandstyle is an option */
      DLG_SHAPE_OUTERWIDTH           = 0x00001000,   /* outerband width is an option */
      DLG_SHAPE_OUTER_HILITE_SHADOW  = 0x00002000,   /* outerband colors are options */
      DLG_SHAPE_SHADOWCOLOR          = 0x00004000,   /* shadow color is an option */
      DLG_SHAPE_SHADOW_X_Y           = 0x00008000,   /* shadow x and y are options */
      DLG_SHAPE_BROWSEIMAGE          = 0x00010000,   /* browse image button is option */
      DLG_SHAPE_NO_TREEVIEW          = 0x00020000,   /* DO NOT use TreeView */
      DLG_SHAPE_CLASS_SQUARE         = 0x00040000,   /* squares are options */
      DLG_SHAPE_CLASS_RECTANGLE      = 0x00080000,   /* rectangles are options */
      DLG_SHAPE_CLASS_PARALLELOGRAM  = 0x00100000,   /* parallelograms are options */
      DLG_SHAPE_CLASS_TRAPEZOID      = 0x00200000,   /* trapezoids are options */
      DLG_SHAPE_CLASS_TRIANGLE       = 0x00400000,   /* triangles are options */
      DLG_SHAPE_CLASS_OTHER          = 0x00800000,   /* other polygons are options */
      DLG_SHAPE_CLASS_CIRCLE         = 0x01000000,   /* circles are options */
      DLG_SHAPE_CLASS_ELLIPSE        = 0x02000000,   /* ellipses are options */
      DLG_SHAPE_CLASS_STAR           = 0x04000000,   /* stars are options */
      DLG_SHAPE_CLASS_CROSS          = 0x08000000,   /* crosses are options */
      DLG_SHAPE_CLASS_ARROW          = 0x10000000,   /* arrows are options */
      DLG_SHAPE_95CONTEXTHELP        = 0x20000000,   /* Dlg should contain context sensitive help icon */
      DLG_SHAPE_USESYSCOLORDLG       = 0x40000000,   /* Use windows color picker dialog */
   }ShapeDlgConstants;

   typedef  enum {
      DLG_TEXT_SHOWPREVIEW           = 0x00000001,   /* shows preview of image */
      DLG_TEXT_AUTOPREVIEW           = 0x00000002,   /* auto preview when options change */
      DLG_TEXT_SAMPLETEXT            = 0x00000004,   /* sample text edit box is an option */
      DLG_TEXT_STYLE                 = 0x00000008,   /* text style is an option */
      DLG_TEXT_COLOR                 = 0x00000010,   /* text color is an option */
      DLG_TEXT_BORDERCOLOR           = 0x00000020,   /* bordercolor is an option */
      DLG_TEXT_ALIGN                 = 0x00000040,   /* alignment is an option */
      DLG_TEXT_ANGLE                 = 0x00000080,   /* angle is an option */
      DLG_TEXT_WORDWRAP              = 0x00000100,   /* wordwrap is an option */
      DLG_TEXT_FONT                  = 0x00000200,   /* font is an option */
      DLG_TEXT_FOREIMAGE             = 0x00000400,   /* foreground image is an option */
      DLG_TEXT_BROWSEIMAGE           = 0x00000800,   /* browse image button is option */
      DLG_TEXT_SHADOWCOLOR           = 0x00001000,   /* shadow color is an option */
      DLG_TEXT_SHADOW_X_Y            = 0x00002000,   /* shadow x and y are options */
      DLG_TEXT_95CONTEXTHELP         = 0x00004000,   /* Dlg should contain context sensitive help icon */
      DLG_TEXT_USESYSCOLORDLG        = 0x00008000,   /* Use windows color picker dialog */
   }TextDlgConstants;

   typedef  enum {
      DLG_CONTOUR_SHOWPREVIEW       = 0x00000001,   /* shows preview of image */
      DLG_CONTOUR_AUTOPROCESS       = 0x00000002,   /* AutoProcess on close   */
      DLG_CONTOUR_OPTION            = 0x00000004,   /* Contour Option is an option */
      DLG_CONTOUR_THRESHOLD         = 0x00000008,   /* Threshold is an option */
      DLG_CONTOUR_DELTADIRECTION    = 0x00000010,   /* DeltaDirection is an option  */
      DLG_CONTOUR_MAXIMUMERROR      = 0x00000020,   /* MaximumError is an option    */
      DLG_CONTOUR_95CONTEXTHELP     = 0x00000040,   /* Dlg should contain context sensitive help icon */
      DLG_CONTOUR_TOOL              = 0x00000080,   /* Dlg should contain tool bar */
   }CountourFilterDlgConstants;

   typedef  enum {
       DLG_CONTOUR_OPTION_THIN          = 0x00000001,
       DLG_CONTOUR_OPTION_LINK_BW       = 0x00000002,
       DLG_CONTOUR_OPTION_LINK_GRAY     = 0x00000004,
       DLG_CONTOUR_OPTION_LINK_COLOR    = 0x00000008,
       DLG_CONTOUR_OPTION_APPROX_COLOR  = 0x00000010,
   }CountourFilterDlgOptionFlags;

#ifndef CONTOUR_VALUES
#define CONTOUR_VALUES
   typedef enum{
      DLG_CONTOUR_THIN              = 0,
      DLG_CONTOUR_LINK_BLACKWHITE   = 1,
      DLG_CONTOUR_LINK_GRAY         = 2,
      DLG_CONTOUR_LINK_COLOR        = 3,
      DLG_CONTOUR_APPROX_COLOR      = 4,
   } CountourFilterDlgOptions;
#endif

   typedef  enum {
      DLG_OFN_OVERWRITEPROMPT = 0x00000002,  /* FileSave will prompt if file exists */
      DLG_OFN_NOCHANGEDIR     = 0x00000008,  /* restore dir to original after close */
      DLG_OFN_ALLOWMULTI      = 0x00000200,  /* allow multiple files to be selected */
   }FileDlgFlagConstants;


// L_SUPPORT_XXX constants
#include "ltlck_.h"

   typedef  enum tagHalftoneDlgConstants{
      DLG_HALFTONE_SHOWPREVIEW   = 0X00000001,
      DLG_HALFTONE_AUTOPROCESS   = 0X00000002,
      DLG_HALFTONE_95CONTEXTHELP = 0X00000004,
      DLG_HALFTONE_TOOL          = 0X00000008,
   } HalftoneDlgConstants;

   typedef enum
   {
      /*
        Generic Control Strings
      */
      DLG_STRING_OKSTR=0,           /* OK button                           */
      DLG_STRING_CANCELSTR,         /* Cancel button                       */
      DLG_STRING_HELPSTR,           /* Help button                         */
      /*
        ColorRes Dialog Strings
      */
      /* ColorRes BitsPerPixel */
      DLG_STRING_CR1BIT,            /* ColorRes dialog 1-bit               */
      DLG_STRING_CR2BIT,            /* ColorRes dialog 2-bit               */
      DLG_STRING_CR3BIT,            /* ColorRes dialog 3-bit               */
      DLG_STRING_CR4BIT,            /* ColorRes dialog 4-bit               */
      DLG_STRING_CR5BIT,            /* ColorRes dialog 5-bit               */
      DLG_STRING_CR6BIT,            /* ColorRes dialog 6-bit               */
      DLG_STRING_CR7BIT,            /* ColorRes dialog 7-bit               */
      DLG_STRING_CR8BIT,            /* ColorRes dialog 8-bit               */
      DLG_STRING_CR12BIT,           /* ColorRes dialog 12-bit              */
      DLG_STRING_CR16BIT,           /* ColorRes dialog 16-bit              */
      DLG_STRING_CR24BIT,           /* ColorRes dialog 24-bit              */
      DLG_STRING_CR32BIT,           /* ColorRes dialog 32-bit              */
      /* Dithering */
      DLG_STRING_CRNONE,            /* ColorRes dialog No Dithering        */
      DLG_STRING_CRFLOYD,           /* ColorRes dialog Floyd Dithering     */
      DLG_STRING_CRSTUCKI,          /* ColorRes dialog Stucki Dithering    */
      DLG_STRING_CRBURKES,          /* ColorRes dialog Burkes Dithering    */
      DLG_STRING_CRSIERRA,          /* ColorRes dialog Sierra Dithering    */
      DLG_STRING_CRSTEVEN,          /* ColorRes dialog Stevenson Dithering */
      DLG_STRING_CRJARVIS,          /* ColorRes dialog Jarvis Dithering    */
      DLG_STRING_CRCLUSTER,         /* ColorRes dialog Cluster Dithering   */
      DLG_STRING_CRORDERED,         /* ColorRes dialog Ordered Dithering   */
      /* Palette */
      DLG_STRING_CRFIXEDPAL,        /* ColorRes dialog Fixed Palette       */
      DLG_STRING_CROPTIMIZEDPAL,    /* ColorRes dialog Optimized Palette   */
      DLG_STRING_CRIDENTITYPAL,     /* ColorRes dialog Identity Palette    */
      DLG_STRING_CRNETSCAPEPAL,     /* ColorRes dialog Netscape Palette    */
      /* Color Order */
      DLG_STRING_CRRGBORDER,        /* ColorRes dialog RGB Color Order     */
      DLG_STRING_CRBGRORDER,        /* ColorRes dialog BGR Color Order     */
      DLG_STRING_CRGRAYORDER,       /* ColorRes dialog Gray Color Order    */
      /* ColorRes Dlg Control Strings */
      DLG_STRING_CRCAPTION,         /* ColorRes dialog title caption       */
      DLG_STRING_CRBPP,             /* ColorRes dialog BitsPerPixel Label  */
      DLG_STRING_CRDITHER,          /* ColorRes dialog Diterhing Label     */
      DLG_STRING_CRPALETTE,         /* ColorRes dialog Palette Label       */
      DLG_STRING_CRORDER,           /* ColorRes dialog Color Order Label   */
      /*
        WindowLevel Dialog Strings
      */
      /* WindowLevel Dlg Control Strings */
      DLG_STRING_WLCAPTION,         /* WindowLevel dialog title caption    */
      DLG_STRING_WLLABEL,           /* WindowLevel dialog label            */
      DLG_STRING_WLRANGELABEL,      /* WindowLevel dialog range label      */
      DLG_STRING_WLINSIDE,          /* WindowLevel dialog inside label     */
      DLG_STRING_WLOUTSIDE,         /* WindowLevel dialog outside label    */
      DLG_STRING_WLCOLORSLABEL,     /* WindowLevel dialog colors label     */
      DLG_STRING_WLENDCOLORS,       /* WindowLevel dialog end color button */
      DLG_STRING_WLSTARTCOLORS,     /* WindowLevel dialog start color button*/
      /*
        Image Processing Dialogs
      */
      /* Filter Directions */
      DLG_STRING_FLTN,              /* Filter/Emboss dialog - North        */
      DLG_STRING_FLTNE,             /* Filter/Emboss dialog - North East   */
      DLG_STRING_FLTE,              /* Filter/Emboss dialog - East         */
      DLG_STRING_FLTSE,             /* Filter/Emboss dialog - Sourth East  */
      DLG_STRING_FLTS,              /* Filter/Emboss dialog - South        */
      DLG_STRING_FLTSW,             /* Filter/Emboss dialog - South West   */
      DLG_STRING_FLTW,              /* Filter/Emboss dialog - West         */
      DLG_STRING_FLTNW,             /* Filter/Emboss dialog - North West   */
      DLG_STRING_FLTDIAG,           /* Filter dialog - Diagonal            */
      DLG_STRING_FLTHORZ,           /* Filter dialog - Horizontal          */
      DLG_STRING_FLTVERT,           /* Filter dialog - Vertical            */
      DLG_STRING_FLTLTOR,           /* Filter dialog - Left To Right Diag. */
      DLG_STRING_FLTRTOL,           /* Filter dialog - Right To Left Diag. */
      DLG_STRING_FLT1,              /* Filter dialog - Filter 1            */
      DLG_STRING_FLT2,              /* Filter dialog - Filter 2            */
      DLG_STRING_FLT3,              /* Filter dialog - Filter 3            */
      DLG_STRING_FLTOMNI,           /* Filter dialog - Omni Directional    */
      /* Image Processing Dialog control strings */
      DLG_STRING_RESIZESTR,         /* Resize dialog title caption         */
      DLG_STRING_RESAMPLESTR,       /* Resample dialog title caption       */
      DLG_STRING_BICUBICSTR,        /* Bicubic Resize dialog title caption */
      DLG_STRING_CHANMASTER,        /* AddNoise dialog channel strings     */
      DLG_STRING_CHANRED,           /* AddNoise dialog channel strings     */
      DLG_STRING_CHANGREEN,         /* AddNoise dialog channel strings     */
      DLG_STRING_CHANBLUE,          /* AddNoise dialog channel strings     */
      DLG_STRING_PROCESSIMAGESTR,   /* Change dialog title if > 1 process                    */
      DLG_STRING_PROCESSSTR,        /* Change dialog process label if > 1 process            */
      DLG_STRING_SHARPENSTR,        /* Change dialog title/string for sharpen process        */
      DLG_STRING_BRIGHTNESSSTR,     /* Change dialog title/string for brightness process     */
      DLG_STRING_CONTRASTSTR,       /* Change dialog title/string for contrast process       */
      DLG_STRING_SATURATIONSTR,     /* Change dialog title/string for saturation process     */
      DLG_STRING_HISTOCONTRASTSTR,  /* Change dialog title/string for histo-contrast process */
      DLG_STRING_HUESTR,            /* Change dialog title/string for hue process            */
      DLG_STRING_HALFTONESTR,       /* Change dialog title/string for halftone process       */
      DLG_STRING_POSTERIZESTR,      /* Change dialog title/string for posterize process      */
      DLG_STRING_MOSAICSTR,         /* Change dialog title/string for mosaic process         */
      DLG_STRING_AVERAGESTR,        /* Change dialog title/string for average process        */
      DLG_STRING_MEDIANSTR,         /* Change dialog title/string for median process         */
      DLG_STRING_OILIFYSTR,         /* Change dialog title/string for oilify process         */
      DLG_STRING_MINFLTSTR,         /* Change dialog title/string for min filter process     */
      DLG_STRING_MAXFLTSTR,         /* Change dialog title/string for max filter process     */
      DLG_STRING_SOLARIZESTR,       /* Change dialog title/string for solarize process       */
      DLG_STRING_PERCENTAGESTR,     /* Change dialog value label for process that use percentages  */
      DLG_STRING_ANGLEDEGREESSTR,   /* Change dialog value label for process that use angles       */
      DLG_STRING_LEVELSSTR,         /* Change dialog value label for process that use levels       */
      DLG_STRING_TILESIZESTR,       /* Change dialog value label for process that use tile sizes   */
      DLG_STRING_SAMPLESIZESTR,     /* Change dialog value label for process that use sample sizes */
      DLG_STRING_THRESHOLDSTR,      /* Change dialog value label for process that use threshold    */
      DLG_STRING_ROTATESTR,         /* Rotate dialog title caption         */
      DLG_STRING_ROTATERESIZESTR,   /* Rotate dialog checkbox              */ 
      DLG_STRING_SHEARSTR,          /* Shear dialog title caption          */
      DLG_STRING_SHEARHORZSTR,      /* Shear dialog checkbox               */ 
      DLG_STRING_FLTVALSTR,         /* Filter dialog filter value label                      */
      DLG_STRING_FLTIMAGESTR,       /* Filter dialog title for > 1 filter                    */
      DLG_STRING_FLTTYPESTR,        /* Filter dialog filter type label, for > 1 filter       */
      DLG_STRING_GRADIENTFLTSTR,    /* Filter dialog title/string for Gradient filter        */
      DLG_STRING_LAPLACIANFLTSTR,   /* Filter dialog title/string for Laplacian filter       */
      DLG_STRING_SOBELFLTSTR,       /* Filter dialog title/string for Sobel filter           */
      DLG_STRING_PREWITTFLTSTR,     /* Filter dialog title/string for Prewitt filter         */
      DLG_STRING_SHIFTDIFFFLTSTR,   /* Filter dialog title/string for ShiftDifference filter */
      DLG_STRING_LINESEGFLTSTR,     /* Filter dialog title/string for LineSegment filter     */
      DLG_STRING_EROSIONFLTSTR,     /* Filter dialog title/string for Erosion filter         */
      DLG_STRING_DILATIONFLTSTR,    /* Filter dialog title/string for Dilation filter        */
      DLG_STRING_RESIZEASPECTSTR,   /* Resize dialog checkbox              */
      DLG_STRING_RESIZEWIDTHSTR,    /* Resize dialog width label           */
      DLG_STRING_RESIZEHEIGHTSTR,   /* Resize dialog height label          */
      DLG_STRING_ROTATEANGLESTR,    /* Rotate/Shear dialog angle label     */
      DLG_STRING_ROTATECOLORSTR,    /* Rotate/Shear dialog backcolor button*/
      DLG_STRING_EMBOSSSTR,         /* Emboss dialog title caption         */
      DLG_STRING_EMBOSSDIRSTR,      /* Emboss dialog direction label       */
      DLG_STRING_EMBOSSDEPTHSTR,    /* Emboss dialog depth label           */
      DLG_STRING_INTENSITYDETECTSTR,    /* IntensityDetect dialog title caption */
      DLG_STRING_INTENSITYDETECTLOWSTR, /* IntensityDetect low label            */
      DLG_STRING_INTENSITYDETECTHIGHSTR,/* IntensityDetect high label           */
      DLG_STRING_ADDNOISESTR,       /* AddNoise dialog title caption       */
      DLG_STRING_NOISELEVELSTR,     /* AddNoise dialog level label         */
      DLG_STRING_NOISECHANNELSTR,   /* AddNoise dialog channel label       */
      DLG_STRING_GAMMACORRECTSTR,   /* GammaCorrect dialog title caption   */
      DLG_STRING_GAMMAVALUESTR,     /* GammaCorrect dialog value label     */
      /*
        Contour Filter Dialog strings
      */
      /* Contour Filter Dialog control strings */
      DLG_STRING_CONTOURSTR,        /* ContourFilter dialog title caption  */
      DLG_STRING_CONTOUROPTIONSTR,  /* ContourFilter dialog option label   */
      DLG_STRING_CONTOURTHRESHOLDSTR,/* ContourFilter dialog threshold label*/
      DLG_STRING_CONTOURDELTADIRECTIONSTR,/* ContourFilter dialog deltadir label */
      DLG_STRING_CONTOURMAXIMUMERRORSTR,  /* ContourFilter dialog maxerr label   */
      /* contour options */
      DLG_STRING_CONTOURTHINSTR,
      DLG_STRING_CONTOURLINKBLACKWHITESTR,
      DLG_STRING_CONTOURLINKGRAYSCALESTR,
      DLG_STRING_CONTOURLINKCOLORSTR,
      DLG_STRING_CONTOURAPPROXCOLORSTR,
      /*
        3d Text Dialog strings
      */
      /* 3d Text Dialog option strings */
      DLG_STRING_TEXT_NOEFFECT,     /* 3d Text dialog effect strings       */
      DLG_STRING_TEXT_INSETLIGHT,
      DLG_STRING_TEXT_INSETXLIGHT,
      DLG_STRING_TEXT_INSETHEAVY,
      DLG_STRING_TEXT_INSETXHEAVY,
      DLG_STRING_TEXT_RAISEDLIGHT,
      DLG_STRING_TEXT_RAISEDXLIGHT,
      DLG_STRING_TEXT_RAISEDHEAVY,
      DLG_STRING_TEXT_RAISEDXHEAVY,
      DLG_STRING_TEXT_DROPSHADOW,
      DLG_STRING_TEXT_BLOCKSHADOW,
      DLG_STRING_TEXT_OUTLINEBLOCK,
      DLG_STRING_TEXT_ALIGNLEFT,    /* 3d Text dialog alignment strings    */
      DLG_STRING_TEXT_ALIGNHORZCENTER,
      DLG_STRING_TEXT_ALIGNRIGHT,
      DLG_STRING_TEXT_ALIGNTOP,
      DLG_STRING_TEXT_ALIGNVERTCENTER,
      DLG_STRING_TEXT_ALIGNBOTTOM,
      /* 3d Text Dialog control strings */
      DLG_STRING_TEXTOPTIONSSTR,    /* 3d Text dialog title caption        */
      DLG_STRING_TEXTPREVIEWSTR,    /* 3d Text dialog preview button label */
      DLG_STRING_TEXTSAMPLETEXTSTR, /* 3d Text dialog sample text label    */
      DLG_STRING_TEXTSTYLESTR,      /* 3d Text dialog style label          */
      DLG_STRING_TEXTCOLORSTR,      /* 3d Text dialog text color label     */
      DLG_STRING_TEXTBORDERCOLORSTR,/* 3d Text dialog border color label   */
      DLG_STRING_TEXTALIGNSTR,      /* 3d Text dialog alignment label      */
      DLG_STRING_TEXTANGLESTR,      /* 3d Text dialog angle label          */
      DLG_STRING_TEXTWORDWRAPSTR,   /* 3d Text dialog word wrap label      */
      DLG_STRING_TEXTFONTSTR,       /* 3d Text dialog font button label    */
      DLG_STRING_TEXTUSEFOREIMAGESTR,/* 3d Text dialog use foreground image label */
      DLG_STRING_TEXTFOREIMAGESTR,  /* 3d Text dialog image button label   */
      DLG_STRING_TEXTSHADOWSTR,     /* 3d Text dialog shadow label         */
      DLG_STRING_TEXTSHADOWCOLORSTR,/* 3d Text dialog shadow color label   */
      DLG_STRING_TEXTSHADOWXSTR,    /* 3d Text dialog shadow X label       */
      DLG_STRING_TEXTSHADOWYSTR,    /* 3d Text dialog shadow Y label       */
      /*
        Resolution Dialog strings
      */
      /* Resolution Dialog option strings */
      DLG_STRING_WMFRESPROMPT,      /* Resolution dialog WMF prompt/title  */
      DLG_STRING_WMFRESLABEL,       /* Resolution dialog WMF label         */
      DLG_STRING_PCDRESPROMPT,      /* Resolution dialog PCD prompt/title  */
      DLG_STRING_PCDRESLABEL,       /* Resolution dialog PCD label         */
      DLG_STRING_FPXRESPROMPT,      /* Resolution dialog FPX prompt/title  */
      DLG_STRING_FPXRESLABEL,       /* Resolution dialog FPX label         */
      DLG_STRING_JBIGRESPROMPT,     /* Resolution dialog JBIG prompt/title */
      DLG_STRING_JBIGRESLABEL,      /* Resolution dialog JBIG label        */
      DLG_STRING_RESOLUTIONWIDTHSTR,/* Resolution dialog width label       */
      DLG_STRING_RESOLUTIONHEIGHTSTR,/* Resolution dialog height label     */
      /*
        GetDirectory Dialog strings
      */
      DLG_STRING_GETDIRSELECTEDSTR,  /* GetDir dialog selected label           */
      DLG_STRING_GETDIR31DIRSTR,     /* GetDir 31-style dialog Directory label */
      DLG_STRING_GETDIR95DIRSTR,     /* GetDir 95-style dialog Directory label */
      DLG_STRING_GETDIR31FILETYPESTR,/* GetDir 31-style dialog FileType label  */
      DLG_STRING_GETDIR95FILETYPESTR,/* GetDir 95-style dialog FileType label  */
      DLG_STRING_GETDIRDRIVESSTR,    /* GetDir 31-style dialog Drives label    */
      DLG_STRING_GETDIROKSTR,        /* GetDir dialog OK button label          */
      DLG_STRINGS1_MAX,
   }DlgStrings1;

   typedef enum
   {
      /*
        FileOpen and FileSave Dialog strings
      */
      /* Progressive Passes strings */
      DLG_STRING_PROGMEANINGFUL=DLG_STRINGS1_MAX,     /* FileOpen/FileSave dialog passes strings*/
      DLG_STRING_PROGALL,
      DLG_STRING_PROG1,
      DLG_STRING_PROG2,
      DLG_STRING_PROG3,
      DLG_STRING_PROG4,
      DLG_STRING_PROG5,
      DLG_STRING_PROG6,
      DLG_STRING_PROG7,
      DLG_STRING_PROG8,
      DLG_STRING_PROG9,
      DLG_STRING_PROG10,
      /* FileOpen FileInfo Dialog strings */
      DLG_STRING_FILEINFOERRORSTRING,/* FileInfo dialog error msgbox prompt */
      DLG_STRING_FILEINFOERROR,      /* FileInfo dialog error msgbox title  */
      /* FileOpen FileInfo control strings */
      DLG_STRING_FILEINFORMATIONSTR,    /* FileInfo dialog title caption       */
      DLG_STRING_FILEINFO_FORMATSTR,
      DLG_STRING_FILEINFO_FILENAMESTR,
      DLG_STRING_FILEINFO_WIDTHSTR,
      DLG_STRING_FILEINFO_HEIGHTSTR,
      DLG_STRING_FILEINFO_BPPSTR,
      DLG_STRING_FILEINFO_SIZEDISKSTR,
      DLG_STRING_FILEINFO_SIZEMEMSTR,
      DLG_STRING_FILEINFO_COMPRESSIONSTR,
      DLG_STRING_FILEINFO_PAGESTR,
      /* file tags */
      DLG_STRING_FILEINFO_ARTISTSTR,
      DLG_STRING_FILEINFO_COPYRIGHTSTR,
      DLG_STRING_FILEINFO_DATETIMESTR,
      DLG_STRING_FILEINFO_DESCRIPTIONSTR,
      DLG_STRING_FILEINFO_HOSTCOMPUTERSTR,
      DLG_STRING_FILEINFO_MAKESTR,
      DLG_STRING_FILEINFO_MODELSTR,
      DLG_STRING_FILEINFO_DOCNAMESTR,
      DLG_STRING_FILEINFO_PAGENAMESTR,
      DLG_STRING_FILEINFO_SOFTWARESTR,
      DLG_STRING_FILEINFO_XRESOLUTIONSTR,
      DLG_STRING_FILEINFO_YRESOLUTIONSTR,
      /* dicom */
      DLG_STRING_FILEINFO_PATIENTNAMESTR,
      DLG_STRING_FILEINFO_PATIENTIDSTR,
      DLG_STRING_FILEINFO_PATIENTBIRTHDATESTR,
      DLG_STRING_FILEINFO_PATIENTSEXSTR,
      DLG_STRING_FILEINFO_STUDYINSTANCESTR,
      DLG_STRING_FILEINFO_STUDYDATESTR,
      DLG_STRING_FILEINFO_STUDYTIMESTR,
      DLG_STRING_FILEINFO_STUDYREFPHYSICIANSTR,
      DLG_STRING_FILEINFO_SERIESMODALITYSTR,
      DLG_STRING_FILEINFO_SERIESIDSTR,
      DLG_STRING_FILEINFO_SERIESNUMBERSTR,
      DLG_STRING_FILEINFO_LOSSLESSJPEG,
      DLG_STRING_FILEINFO_LOSSLESSJTIF,
      /* png */
      DLG_STRING_FILEINFO_WARNINGSTR,
      DLG_STRING_FILEINFO_DISCLAIMERSTR,
      /* FileSave Dialog Multipage Save Option Strings */
      DLG_STRING_OVERWRITESTR,       /* FileSave dialog overwrite string    */
      DLG_STRING_APPENDSTR,          /* FileSave dialog append string       */
      DLG_STRING_REPLACESTR,         /* FileSave dialog replace string      */
      DLG_STRING_INSERTSTR,          /* FileSave dialog insert string       */
      /* Delete page options strings */
      DLG_STRING_DELPAGEPROMPT,
      DLG_STRING_DELPAGETITLE,
      DLG_STRING_DELPAGEERROR,
      /* file format strings, used in FileOpen FileInfo Dialog */
      /* these correspond to the FILE_XXX file format constant */
      DLG_STRING_FILE_PCX,           /* PCX                    */
      DLG_STRING_FILE_GIF,           /* GIF                    */
      DLG_STRING_FILE_TIF,           /* TIFF                   */
      DLG_STRING_FILE_TGA,           /* TGA                    */
      DLG_STRING_FILE_CMP,           /* LEAD                   */
      DLG_STRING_FILE_BMP,           /* Win BMP                */
      DLG_STRING_FILE_JFIF,          /* JPEG 4:4:4             */
      DLG_STRING_FILE_JTIF,          /* JTIF 4:4:4             */
      DLG_STRING_FILE_LEAD1JFIF,     /* JPEG 4:1:1             */
      DLG_STRING_FILE_LEAD2JFIF,     /* JPEG 4:2:2             */
      DLG_STRING_FILE_LEAD1JTIF,     /* JTIF 4:1:1             */
      DLG_STRING_FILE_LEAD2JTIF,     /* JTIF 4:2:2             */
      DLG_STRING_FILE_OS2,           /* OS/2 BMP Version 1.0   */
      DLG_STRING_FILE_WMF,           /* Win Metafile           */
      DLG_STRING_FILE_EPS,           /* PostScript Raster      */
      DLG_STRING_FILE_TIFLZW,        /* TIFF                   */
      DLG_STRING_FILE_CCITT,         /* TIFF                   */
      DLG_STRING_FILE_CCITT_GROUP3_1DIM,/* TIFF                */
      DLG_STRING_FILE_CCITT_GROUP3_2DIM,/* TIFF                */
      DLG_STRING_FILE_CCITT_GROUP4,  /* TIFF                   */
      DLG_STRING_FILE_LEAD1BIT,      /* LEAD 1 bit             */
      DLG_STRING_FILE_CALS,          /* CALS Type 1            */
      DLG_STRING_FILE_CALS2,         /* CALS Type 2            */
      DLG_STRING_FILE_CALS3,         /* CALS Type 3            */
      DLG_STRING_FILE_CALS4,         /* CALS Type 4            */
      DLG_STRING_FILE_MAC,           /* MacPaint               */
      DLG_STRING_FILE_IMG,           /* GEM Image              */
      DLG_STRING_FILE_MSP,           /* MS Paint               */
      DLG_STRING_FILE_WPG,           /* WordPerfect            */
      DLG_STRING_FILE_RAS,           /* SUN Raster             */
      DLG_STRING_FILE_PCT,           /* Mac PICTURE            */
      DLG_STRING_FILE_PCD,           /* Photo CD               */
      DLG_STRING_FILE_AVI,           /* Windows AVI            */
      DLG_STRING_FILE_EPSTIFF,       /* PostScript TIFF        */
      DLG_STRING_FILE_EPSWMF,        /* Metafile PostScript    */
      DLG_STRING_FILE_FAX_G3_1D,     /* FAX G3 1D              */
      DLG_STRING_FILE_FAX_G3_2D,     /* FAX G3 2D              */
      DLG_STRING_FILE_FAX_G4,        /* FAX G4                 */
      DLG_STRING_FILE_WFX_G3_1D,     /* Winfax G3 1D           */
      DLG_STRING_FILE_WFX_G4,        /* Winfax G4              */
      DLG_STRING_FILE_ICA_G3_1D,     /* IBM IOCA (Wrapped) G31D*/
      DLG_STRING_FILE_ICA_G3_2D,     /* IBM IOCA (Wrapped) G32D*/
      DLG_STRING_FILE_ICA_G4,        /* IBM IOCA (Wrapped) G4  */
      DLG_STRING_FILE_OS2_2,         /* OS/2 BMP Version 2.0   */
      DLG_STRING_FILE_PNG,           /* CServe PNG             */
      DLG_STRING_FILE_PSD,           /* PhotoShop PSD          */
      DLG_STRING_FILE_RAWICA_G3_1D,  /* IBM IOCA (Raw) G31D    */
      DLG_STRING_FILE_RAWICA_G3_2D,  /* IBM IOCA (Raw) G32D    */
      DLG_STRING_FILE_RAWICA_G4,     /* IBM IOCA (Raw) G4      */
//   #ifdef WIN32   
      DLG_STRING_FILE_FPX,           /* Kodak FlashPix         */
      DLG_STRING_FILE_FPX_SINGLE_COLOR,/* Kodak FlashPix Single Color*/
      DLG_STRING_FILE_FPX_JPEG,      /* Kodak FlashPix - JPEG  */
      DLG_STRING_FILE_FPX_JPEG_QFACTOR,/* Kodak FlashPix - JPEG*/
//   #endif
      DLG_STRING_FILE_BMP_RLE,       /* Windows RLE BMP        */
      DLG_STRING_FILE_TIF_CMYK,      /* CMYK TIFF              */
      DLG_STRING_FILE_TIFLZW_CMYK,   /* CMYK TIFF              */
      DLG_STRING_FILE_TIF_PACKBITS,  /* TIFF                   */
      DLG_STRING_FILE_TIF_PACKBITS_CMYK,/* CMYK TIFF           */
      DLG_STRING_FILE_DICOM_GRAY,    /* DICOM Grayscale        */
      DLG_STRING_FILE_DICOM_COLOR,   /* DICOM Color            */
      DLG_STRING_FILE_DICOM_RLE_GRAY,/* RLE Grayscale          */
      DLG_STRING_FILE_DICOM_RLE_COLOR,/* RLE Color             */
      DLG_STRING_FILE_DICOM_JPEG_GRAY,/* JPEG Grayscale        */
      DLG_STRING_FILE_DICOM_JPEG_COLOR,/* JPEG Color           */
      DLG_STRING_FILE_WIN_ICO,       /* Windows ICON           */
      DLG_STRING_FILE_WIN_CUR,       /* Windows Cursor         */
      DLG_STRING_FILE_TIF_YCC,       /* YCbCr TIFF             */
      DLG_STRING_FILE_TIFLZW_YCC,    /* YCbCr TIFF             */
      DLG_STRING_FILE_TIF_PACKBITS_YCC,/* YCbCr TIFF           */
      DLG_STRING_FILE_EXIF,          /* Exif RGB TIFF          */
      DLG_STRING_FILE_EXIF_YCC,      /* Exif YCbCr TIFF        */
      DLG_STRING_FILE_EXIF_JPEG,     /* Exif JPEG              */
//   #ifdef WIN32   
      DLG_STRING_FILE_AWD,           /* Microsoft FAX          */
//   #endif
      DLG_STRING_FILE_EXIF_JPEG_411, /* JPEG 4:1:1 - Exif      */
//   #ifdef WIN32   
      DLG_STRING_FILE_EMF,           /* Enhanced Metafile      */
//   #endif
      DLG_STRING_FILE_JBIG,          /* JBIG                   */
      DLG_STRING_FILE_ICA_IBM_MMR,
      DLG_STRING_FILE_RAWICA_IBM_MMR,
      DLG_STRING_FILE_ANI,
      DLG_STRING_FILE_ANI_RLE,
      DLG_STRING_FILE_LASERDATA,
      DLG_STRING_FILE_INTERGRAPH_RLE,
      DLG_STRING_FILE_INTERGRAPH_VECTOR,
      DLG_STRING_FILE_DWG,
      DLG_STRING_FILE_CUT,
      DLG_STRING_FILE_PPM_ASCII,
      DLG_STRING_FILE_PPM_BINARY,
      DLG_STRING_FILE_PGM_ASCII,
      DLG_STRING_FILE_PGM_BINARY,
      DLG_STRING_FILE_PBM_ASCII,
      DLG_STRING_FILE_PBM_BINARY,
      DLG_STRING_FILE_IFF_ILBM,
      DLG_STRING_FILE_IFF_CAT,
      DLG_STRING_FILE_XBM,
      DLG_STRING_FILE_XPM,
      DLG_STRING_FILE_DXF,
      DLG_STRING_FILE_DUMMY,
      DLG_STRING_FILE_MPEG1,
      DLG_STRING_FILE_MPEG2,

      /* FileOpen Dialog control strings */
      DLG_STRING_FILEOPENOKSTR,               /* FileOpen OK button label          */
      /* 95 style */
      DLG_STRING_FILEOPEN95FILEINFOSTR,       /* FileOpen FileInfo button label    */
      DLG_STRING_FILEOPEN95LOADROTATEDSTR,    /* FileOpen Load Rotated label       */
      DLG_STRING_FILEOPEN95LOADCOMPRESSEDSTR, /* FileOpen Load Compressed label    */
      DLG_STRING_FILEOPEN95PROGPASSESSTR,     /* FileOpen Progressive Passes label */
      DLG_STRING_FILEOPEN95PAGENUMSTR,        /* FileOpen Page Number label        */
      DLG_STRING_FILEOPEN95DELETEPAGESTR,     /* FileOpen Delete Page button label */
      DLG_STRING_FILEOPEN95ENABLEPREVIEWSTR,  /* FileOpen Enable Preview label     */
      DLG_STRING_FILEOPEN95FILETYPESTR,       /* FileOpen File Type label          */
      DLG_STRING_FILEOPEN95DIRSTR,            /* FileOpen Folder label             */
      DLG_STRING_FILEOPEN95FILENAMESTR,       /* FileOpen File Name label          */
      /* 31 style */
      DLG_STRING_FILEOPEN31FILEINFOSTR,       /* FileOpen FileInfo button label    */
      DLG_STRING_FILEOPEN31LOADROTATEDSTR,    /* FileOpen Load Rotated label       */
      DLG_STRING_FILEOPEN31LOADCOMPRESSEDSTR, /* FileOpen Load Compressed label    */
      DLG_STRING_FILEOPEN31PROGPASSESSTR,     /* FileOpen Progressive Passes label */
      DLG_STRING_FILEOPEN31PAGENUMSTR,        /* FileOpen Page Number label        */
      DLG_STRING_FILEOPEN31DELETEPAGESTR,     /* FileOpen Delete Page button label */
      DLG_STRING_FILEOPEN31ENABLEPREVIEWSTR,  /* FileOpen Enable Preview label     */
      DLG_STRING_FILEOPEN31DRIVESSTR,         /* FileOpen Drive ListBox label      */
      DLG_STRING_FILEOPEN31FILETYPESTR,       /* FileOpen File Type label          */
      DLG_STRING_FILEOPEN31DIRSTR,            /* FileOpen Folder label             */
      DLG_STRING_FILEOPEN31FILENAMESTR,       /* FileOpen File Name label          */
      /* FileSave Dialog control strings */
      /* 95 style */
      DLG_STRING_FILESAVEOKSTR,               /* FileSave OK button label          */
      DLG_STRING_FILESAVE95FILETYPESTR,       /* FileSave File Type label          */
      DLG_STRING_FILESAVE95DIRSTR,            /* FileSave Folder label             */
      DLG_STRING_FILESAVE95FILENAMESTR,       /* FileSave File Name label          */
      DLG_STRING_FILESAVE95STAMPOPTIONSSTR,   /* FileSave stamp options label      */
      DLG_STRING_FILESAVE95SAVESTAMPSTR,      /* FileSave save stamp label         */
      DLG_STRING_FILESAVE95STAMP8STR,         /* FileSave 8-bit stamp label        */
      DLG_STRING_FILESAVE95STAMP24STR,        /* FileSave 24-bit stamp label       */
      DLG_STRING_FILESAVE95STAMPWIDTHSTR,     /* FileSave stamp width label        */
      DLG_STRING_FILESAVE95STAMPHEIGHTSTR,    /* FileSave stamp height label       */
      DLG_STRING_FILESAVE95SUBTYPESTR,        /* FileSave sub file type label      */
      DLG_STRING_FILESAVE95QFACTORSTR,        /* FileSave qfactor label            */
      DLG_STRING_FILESAVE95PROGOPTIONSSTR,    /* FileSave progressive save label   */
      DLG_STRING_FILESAVE95MULTIPAGESTR,      /* FileSave multipage save label     */
      DLG_STRING_FILESAVE95PAGENUMBERSTR,     /* FileSave page number label        */
      /* 31 style */
      DLG_STRING_FILESAVE31FILENAMESTR,       /* FileSave File Name label          */
      DLG_STRING_FILESAVE31DIRSTR,            /* FileSave Folder label             */
      DLG_STRING_FILESAVE31FILETYPESTR,       /* FileOpen File Type label          */
      DLG_STRING_FILESAVE31DRIVESSTR,         /* FileSave Drive ListBox label      */
      DLG_STRING_FILESAVE31MULTIPAGESTR,      /* FileSave multipage save label     */
      DLG_STRING_FILESAVE31PAGENUMBERSTR,     /* FileSave page number label        */
      DLG_STRING_FILESAVE31QFACTORSTR,        /* FileSave qfactor label            */
      DLG_STRING_FILESAVE31SUBTYPESTR,        /* FileSave sub file type label      */
      DLG_STRING_FILESAVE31STAMPOPTIONSSTR,   /* FileSave stamp options label      */
      DLG_STRING_FILESAVE31SAVESTAMPSTR,      /* FileSave save stamp label         */
      DLG_STRING_FILESAVE31STAMP8STR,         /* FileSave 8-bit stamp label        */
      DLG_STRING_FILESAVE31STAMP24STR,        /* FileSave 24-bit stamp label       */
      DLG_STRING_FILESAVE31STAMPWIDTHSTR,     /* FileSave stamp width label        */
      DLG_STRING_FILESAVE31STAMPHEIGHTSTR,    /* FileSave stamp height label       */
      DLG_STRING_FILESAVE31PROGOPTIONSSTR,    /* FileSave progressive save label   */
      /* FileSave File Format strings */
      /* NOTE: for top-level and sub-format strings, only the first 40 chars will be used! */
      /* for the top-level formats */
      DLG_STRING_LEAD24,
      DLG_STRING_LEAD8,
      DLG_STRING_LEAD1,
      DLG_STRING_JFIF24,
      DLG_STRING_JFIF16,
      DLG_STRING_JFIF12,
      DLG_STRING_JFIF8,
      DLG_STRING_CALS,
      DLG_STRING_PNG1,
      DLG_STRING_PNG4,
      DLG_STRING_PNG8,
      DLG_STRING_PNG24,
      DLG_STRING_PNG32,
      DLG_STRING_DICOM8,
      DLG_STRING_DICOM16,
      DLG_STRING_DICOM24,
      DLG_STRING_FAX,
      DLG_STRING_EPS,
      DLG_STRING_EXIF,
//   #ifdef WIN32   
      DLG_STRING_FPX24,
      DLG_STRING_FPX8,
//   #endif
      DLG_STRING_IMG,
      DLG_STRING_GIF1,
      DLG_STRING_GIF2,
      DLG_STRING_GIF3,
      DLG_STRING_GIF4,
      DLG_STRING_GIF5,
      DLG_STRING_GIF6,
      DLG_STRING_GIF7,
      DLG_STRING_GIF8,
      DLG_STRING_IOCA,
      DLG_STRING_MODCA,
      DLG_STRING_PCT1,
      DLG_STRING_PCT4,
      DLG_STRING_PCT8,
      DLG_STRING_PCT24,
      DLG_STRING_MAC,
//   #ifdef WIN32   
      DLG_STRING_AWD,
//   #endif
      DLG_STRING_MSP,
      DLG_STRING_OS2BMP1,
      DLG_STRING_OS2BMP4,
      DLG_STRING_OS2BMP8,
      DLG_STRING_OS2BMP24,
      DLG_STRING_PCX1,
      DLG_STRING_PCX4,
      DLG_STRING_PCX8,
      DLG_STRING_PCX24,
      DLG_STRING_PSD1,
      DLG_STRING_PSD8,
      DLG_STRING_PSD24,
      DLG_STRING_RAS1,
      DLG_STRING_RAS4,
      DLG_STRING_RAS8,
      DLG_STRING_RAS24,
      DLG_STRING_RAS32,
      DLG_STRING_TGA8,
      DLG_STRING_TGA16,
      DLG_STRING_TGA24,
      DLG_STRING_TGA32,
      DLG_STRING_TIFF1,
      DLG_STRING_TIFF2,
      DLG_STRING_TIFF3,
      DLG_STRING_TIFF4,
      DLG_STRING_TIFF5,
      DLG_STRING_TIFF6,
      DLG_STRING_TIFF7,
      DLG_STRING_TIFF8,
      DLG_STRING_TIFF12,
      DLG_STRING_TIFF16,
      DLG_STRING_TIFF24,
      DLG_STRING_TIFF32,
      DLG_STRING_BMP1,
      DLG_STRING_BMP4,
      DLG_STRING_BMP8,
      DLG_STRING_BMP16,
      DLG_STRING_BMP24,
      DLG_STRING_BMP32,
      DLG_STRING_WFX,
      DLG_STRING_WMF8,
      DLG_STRING_WMF24,
//   #ifdef WIN32   
      DLG_STRING_EMF8,
      DLG_STRING_EMF24,
//   #endif
      DLG_STRING_WPG1,
      DLG_STRING_WPG4,
      DLG_STRING_WPG8,
      DLG_STRING_ICO1,
      DLG_STRING_ICO4,
      DLG_STRING_ICO8,
      DLG_STRING_ICO24,
      DLG_STRING_CUR1,
      DLG_STRING_CUR4,
      DLG_STRING_CUR8,
      DLG_STRING_CUR24,
      DLG_STRING_JBIG1,
      DLG_STRING_JBIG2,
      DLG_STRING_JBIG3,
      DLG_STRING_JBIG4,
      DLG_STRING_JBIG5,
      DLG_STRING_JBIG6,
      DLG_STRING_JBIG7,
      DLG_STRING_JBIG8,
      DLG_STRING_CUT,
      DLG_STRING_PPM,
      DLG_STRING_PGM,
      DLG_STRING_PBM,
      DLG_STRING_IFF1,
      DLG_STRING_IFF2,
      DLG_STRING_IFF3,
      DLG_STRING_IFF4,
      DLG_STRING_IFF5,
      DLG_STRING_IFF6,
      DLG_STRING_IFF7,
      DLG_STRING_IFF8,
      DLG_STRING_IFF24,
      DLG_STRING_XBM,
      DLG_STRING_XPM8,
      DLG_STRING_XPM16,
      DLG_STRING_XPM24,
      DLG_STRING_XPM32,
      DLG_STRING_ITG,
      /* for the sub-formats */
      /* LEAD CMP file subtypes (8,24-bit) */
      DLG_STRING_SUB_CMP_NONPROGRESSIVE,
      DLG_STRING_SUB_CMP_PROGRESSIVE,
      /* JPEG file subtypes (24-bit)       */
      DLG_STRING_SUB_JPEG24_YUV_444,
      DLG_STRING_SUB_JPEG24_YUV_422,
      DLG_STRING_SUB_JPEG24_YUV_411,
      DLG_STRING_SUB_JPEG24_PROG_444,
      DLG_STRING_SUB_JPEG24_PROG_422,
      DLG_STRING_SUB_JPEG24_PROG_411,
      DLG_STRING_SUB_JPEG24_LOSSLESS,
      /* JPEG file subtypes (12-bit)       */
      DLG_STRING_SUB_JPEG12_YUV_400,
      DLG_STRING_SUB_JPEG12_LOSSLESS,
      /* JPEG file subtypes (8-bit)        */
      DLG_STRING_SUB_JPEG8_YUV_400,
      DLG_STRING_SUB_JPEG8_PROG_400,
      DLG_STRING_SUB_JPEG8_LOSSLESS,
      /* CALS file subtypes (1-bit)        */
      DLG_STRING_SUB_CALS,
      DLG_STRING_SUB_CALS2,
      DLG_STRING_SUB_CALS3,
      DLG_STRING_SUB_CALS4,
      /* DICOM file subtypes (8-bit)       */
      DLG_STRING_SUB_DICOM8_GRAY,
      DLG_STRING_SUB_DICOM8_COLOR,
      /* DICOM file subtypes (Other-bit)   */
      DLG_STRING_SUB_DICOM_RLE_GRAY,
      DLG_STRING_SUB_DICOM_RLE_COLOR,
      DLG_STRING_SUB_DICOM_JPEG_GRAY,
      DLG_STRING_SUB_DICOM_LOSSLESSJPEG_GRAY,
      DLG_STRING_SUB_DICOM_JPEG_COLOR,
      DLG_STRING_SUB_DICOM_LOSSLESSJPEG_COLOR,
      /* RAW FAX, IOCA, & MODCA subtypes   */
      DLG_STRING_SUB_FAX_G3_1D,
      DLG_STRING_SUB_FAX_G3_2D,
      DLG_STRING_SUB_FAX_G4,
      /* EXIF file subtypes                */
      DLG_STRING_SUB_EXIF_UNCOMPRESSEDRGB,
      DLG_STRING_SUB_EXIF_UNCOMPRESSEDYCC,
      DLG_STRING_SUB_EXIF_JPEG_411,
      DLG_STRING_SUB_EXIF_JPEG_422,
//   #ifdef WIN32   
      /* FPX file subtypes                 */
      DLG_STRING_SUB_FPX_UNCOMPRESSED,
      DLG_STRING_SUB_FPX_SINGLECOLOR,
      DLG_STRING_SUB_FPX_DEFQFACTOR,
      DLG_STRING_SUB_FPX_SPECQFACTOR,
//   #endif
      /* GIF file subtypes                 */
      DLG_STRING_SUB_GIF_INTERLACED89A,
      DLG_STRING_SUB_GIF_NONINTERLACED89A,
      /* OS/2 BMP file subtypes            */
      DLG_STRING_SUB_OS2_VER1,
      DLG_STRING_SUB_OS2_VER2,
      /* TIFF file subtypes (1-bit)        */
      DLG_STRING_SUB_TIFF1_CCITT,
      DLG_STRING_SUB_TIFF1_CCITT_G3_1D,
      DLG_STRING_SUB_TIFF1_CCITT_G3_2D,
      DLG_STRING_SUB_TIFF1_CCITT_G4,
      DLG_STRING_SUB_TIFF1_UNCOMPRESSEDRGB,
      DLG_STRING_SUB_TIFF1_RLERGB,
      DLG_STRING_SUB_TIFF1_LZWRGB,
      /* TIFF file subtypes (2,3,4,5,6,7-bit) */
      DLG_STRING_SUB_TIFFOTHER_UNCOMPRESSED,
      DLG_STRING_SUB_TIFFOTHER_RLE,
      DLG_STRING_SUB_TIFFOTHER_LZW,
      /* TIFF file subtypes (8-bit)        */
      DLG_STRING_SUB_TIFF8_UNCOMPRESSEDRGB,
      DLG_STRING_SUB_TIFF8_RLERGB,
      DLG_STRING_SUB_TIFF8_JPEG_GRAY_YCC,
      DLG_STRING_SUB_TIFF8_LOSSLESSJPEG,
      DLG_STRING_SUB_TIFF8_LZWRGB,
      /* TIFF file subtypes (12-bit)       */
      DLG_STRING_SUB_TIFF12_UNCOMPRESSED,
      DLG_STRING_SUB_TIFF12_LOSSLESSJPEG,
      /* TIFF file subtypes (16-bit)       */
      DLG_STRING_SUB_TIFF16_UNCOMPRESSED,
      DLG_STRING_SUB_TIFF16_RLE,
      DLG_STRING_SUB_TIFF16_LOSSLESSJPEG,
      DLG_STRING_SUB_TIFF16_LZW,
      /* TIFF file subtypes (24-bit)       */
      DLG_STRING_SUB_TIFF24_UNCOMPRESSEDRGB,
      DLG_STRING_SUB_TIFF24_UNCOMPRESSEDCMYK,
      DLG_STRING_SUB_TIFF24_UNCOMPRESSEDYCC,
      DLG_STRING_SUB_TIFF24_RLERGB,
      DLG_STRING_SUB_TIFF24_RLECMYK,
      DLG_STRING_SUB_TIFF24_RLEYCC,
      DLG_STRING_SUB_TIFF24_JPEG_YCC_444,
      DLG_STRING_SUB_TIFF24_JPEG_YCC_422,
      DLG_STRING_SUB_TIFF24_JPEG_YCC_411,
      DLG_STRING_SUB_TIFF24_LOSSLESSJPEG,
      DLG_STRING_SUB_TIFF24_LZWRGB,
      DLG_STRING_SUB_TIFF24_LZWCMYK,
      DLG_STRING_SUB_TIFF24_LZWYCC,
      /* TIFF file subtypes (32-bit)       */
      DLG_STRING_SUB_TIFF32_UNCOMPRESSEDRGB,
      DLG_STRING_SUB_TIFF32_UNCOMPRESSEDCMYK,
      DLG_STRING_SUB_TIFF32_RLERGB,
      DLG_STRING_SUB_TIFF32_RLECMYK,
      DLG_STRING_SUB_TIFF32_LZWRGB,
      DLG_STRING_SUB_TIFF32_LZWCMYK,
      /* BMP file subtypes (4 and 8-bit only) */
      DLG_STRING_SUB_BMP_UNCOMPRESSED,
      DLG_STRING_SUB_BMP_RLECOMPRESSED,
      /* WFX file subtypes                 */
      DLG_STRING_SUB_WFX_CCITT_G3_1D,
      DLG_STRING_SUB_WFX_CCITT_G4,
      /* PPM file subtypes                 */
      DLG_STRING_SUB_PPM_ASCII,
      DLG_STRING_SUB_PPM_BINARY,
      /* PGM file subtypes                 */
      DLG_STRING_SUB_PGM_ASCII,
      DLG_STRING_SUB_PGM_BINARY,
      /* PBM file subtypes                 */
      DLG_STRING_SUB_PBM_ASCII,
      DLG_STRING_SUB_PBM_BINARY,
      /* IFF file subtypes                 */
      DLG_STRING_SUB_IFF_ILBM_RLE,
      DLG_STRING_SUB_IFF_CAT_RLE,
      /* FileSave Dialog default extension strings */
      /* NOTE: for extension strings, only the first 3 chars will be used! */
      DLG_STRING_EXT_LEAD,
      DLG_STRING_EXT_JFIF,
      DLG_STRING_EXT_CALS,
      DLG_STRING_EXT_PNG,
      DLG_STRING_EXT_DICOM,
      DLG_STRING_EXT_FAX,
      DLG_STRING_EXT_EPS,
      DLG_STRING_EXT_EXIF,
//   #ifdef WIN32   
      DLG_STRING_EXT_FPX,
//   #endif
      DLG_STRING_EXT_IMG,
      DLG_STRING_EXT_GIF,
      DLG_STRING_EXT_IOCA,
      DLG_STRING_EXT_MODCA,
      DLG_STRING_EXT_PCT,
      DLG_STRING_EXT_MAC,
//   #ifdef WIN32   
      DLG_STRING_EXT_AWD,
//   #endif
      DLG_STRING_EXT_MSP,
      DLG_STRING_EXT_OS2BMP,
      DLG_STRING_EXT_PCX,
      DLG_STRING_EXT_PSD,
      DLG_STRING_EXT_RAS,
      DLG_STRING_EXT_TGA,
      DLG_STRING_EXT_TIFF,
      DLG_STRING_EXT_BMP,
      DLG_STRING_EXT_WFX,
      DLG_STRING_EXT_WMF,
//   #ifdef WIN32   
      DLG_STRING_EXT_EMF,
//   #endif
      DLG_STRING_EXT_WPG,
      DLG_STRING_EXT_ICO,
      DLG_STRING_EXT_CUR,
      DLG_STRING_EXT_JBIG,
      DLG_STRING_EXT_CUT,
      DLG_STRING_EXT_PPM,
      DLG_STRING_EXT_PGM,
      DLG_STRING_EXT_PBM,
      DLG_STRING_EXT_IFF,
      DLG_STRING_EXT_XBM,
      DLG_STRING_EXT_XPM,
      DLG_STRING_EXT_ITG,
      DLG_STRINGS2_MAX,
   }DlgStrings2;

   typedef enum
   {
      /*
        3d Shape Dialog strings
      */
      /* Shape Categories */
      DLG_STRING_SHAPE_SQUARES=DLG_STRINGS2_MAX,
      DLG_STRING_SHAPE_RECTS,
      DLG_STRING_SHAPE_PARALLELS,
      DLG_STRING_SHAPE_TRAPS,
      DLG_STRING_SHAPE_TRIANGLES,
      DLG_STRING_SHAPE_OTHERS,
      DLG_STRING_SHAPE_CIRCLES,
      DLG_STRING_SHAPE_ELLIPSES,
      DLG_STRING_SHAPE_STARS,
      DLG_STRING_SHAPE_CROSSES,
      DLG_STRING_SHAPE_ARROWS,
      /* Shape Styles */
      DLG_STRING_SHAPE_NORMAL,
      DLG_STRING_SHAPE_ROUNDED,
      DLG_STRING_SHAPE_LEFT,
      DLG_STRING_SHAPE_RIGHT,
      DLG_STRING_SHAPE_TOP,
      DLG_STRING_SHAPE_BOTTOM,
      DLG_STRING_SHAPE_EQ_LEFT,
      DLG_STRING_SHAPE_EQ_RIGHT,
      DLG_STRING_SHAPE_EQ_TOP,
      DLG_STRING_SHAPE_EQ_BOTTOM,
      DLG_STRING_SHAPE_IS_LEFT,
      DLG_STRING_SHAPE_IS_RIGHT,
      DLG_STRING_SHAPE_IS_TOP,
      DLG_STRING_SHAPE_IS_BOTTOM,
      DLG_STRING_SHAPE_RIGHT_LT,
      DLG_STRING_SHAPE_RIGHT_LB,
      DLG_STRING_SHAPE_RIGHT_RT,
      DLG_STRING_SHAPE_RIGHT_RB,
      DLG_STRING_OCTAGONSTR,
      DLG_STRING_DIAMONDSTR,
      DLG_STRING_PENTAGONSTR,
      DLG_STRING_HEXAGONSTR,
      DLG_STRING_LINESTR,
      /* NOTE: REGION IS OMITTED */
      DLG_STRING_SHAPE_90_LT,
      DLG_STRING_SHAPE_90_LB,
      DLG_STRING_SHAPE_90_RT,
      DLG_STRING_SHAPE_90_RB,
      DLG_STRING_SHAPE_180_L,
      DLG_STRING_SHAPE_180_R,
      DLG_STRING_SHAPE_180_T,
      DLG_STRING_SHAPE_180_B,
      DLG_STRING_SHAPE_270_LT,
      DLG_STRING_SHAPE_270_LB,
      DLG_STRING_SHAPE_270_RT,
      DLG_STRING_SHAPE_270_RB,
      DLG_STRING_SHAPE_4_POINT,
      DLG_STRING_SHAPE_5_POINT,
      DLG_STRING_SHAPE_8_POINT,
      DLG_STRING_SHAPE_16_POINT,
      DLG_STRING_SHAPE_24_POINT,
      DLG_STRING_SHAPE_324_POINT,
      DLG_STRING_SHAPE_SMALL,
      DLG_STRING_SHAPE_MEDIUM,
      DLG_STRING_SHAPE_LARGE,
      DLG_STRING_SHAPE_2WAY_LR,
      DLG_STRING_SHAPE_2WAY_TB,
      DLG_STRING_SHAPE_2WAY_LT,
      DLG_STRING_SHAPE_2WAY_LB,
      DLG_STRING_SHAPE_2WAY_RT,
      DLG_STRING_SHAPE_2WAY_RB,
      DLG_STRING_SHAPE_3WAY_LTR,
      DLG_STRING_SHAPE_3WAY_TRB,
      DLG_STRING_SHAPE_3WAY_LBR,
      DLG_STRING_SHAPE_3WAY_LTB,
      DLG_STRING_SHAPE_4WAY,
      /* Shape Styles */
      DLG_STRING_SHAPE_TRANSPARENT,
      DLG_STRING_SHAPE_OPAQUE,
      DLG_STRING_SHAPE_TRANSLUCENT,
      DLG_STRING_SHAPE_TILEDIMAGE,
      DLG_STRING_SHAPE_TRANSTILEDIMAGE,
      DLG_STRING_SHAPE_SOLIDFILL,
      DLG_STRING_SHAPE_TRANSFILL,
      DLG_STRING_SHAPE_HORZFILL,
      DLG_STRING_SHAPE_VERTFILL,
      DLG_STRING_SHAPE_FOREDIAGFILL,
      DLG_STRING_SHAPE_BACKDIAGFILL,
      DLG_STRING_SHAPE_CROSSFILL,
      DLG_STRING_SHAPE_DIAGCROSSFILL,
      DLG_STRING_SHAPE_TRANSBORDER,
      DLG_STRING_SHAPE_SOLIDBORDER,
      DLG_STRING_SHAPE_DASHBORDER,
      DLG_STRING_SHAPE_DOTBORDER,
      DLG_STRING_SHAPE_DASHDOTBORDER,
      DLG_STRING_SHAPE_DASHDOTDOTBORDER,
      DLG_STRING_SHAPE_INNEROUTERNONE,
      DLG_STRING_SHAPE_INNEROUTERINSET,
      DLG_STRING_SHAPE_INNEROUTERRAISED,
      /* 3d Shape Dialog control strings */
      DLG_STRING_SHAPEOPTIONSSTR,      /* 3d Shape Dialog title caption          */
      DLG_STRING_SHAPECATEGORYSTR,     /* 3d Shape Dialog category label         */
      DLG_STRING_SHAPESTYLESTR,        /* 3d Shape Dialog style label            */
      DLG_STRING_SHAPEPREVIEWSTR,      /* 3d Shape Dialog preview button label   */
      DLG_STRING_SHAPEBACKSTYLESTR,    /* 3d Shape Dialog background style label */
      DLG_STRING_SHAPEBACKIMAGESTR,    /* 3d Shape Dialog background image label */
      DLG_STRING_SHAPEFILLSTYLESTR,    /* 3d Shape Dialog fill style label       */
      DLG_STRING_SHAPEFORECOLORSTR,    /* 3d Shape Dialog foreground color label */
      DLG_STRING_SHAPEBACKCOLORSTR,    /* 3d Shape Dialog background color label */
      DLG_STRING_SHAPEBORDERSTYLESTR,  /* 3d Shape Dialog border style label     */
      DLG_STRING_SHAPEBORDERCOLORSTR,  /* 3d Shape Dialog border color label     */
      DLG_STRING_SHAPEBORDERWIDTHSTR,  /* 3d Shape Dialog border width label     */
      DLG_STRING_SHAPEINNERSTYLESTR,   /* 3d Shape Dialog inner style label      */
      DLG_STRING_SHAPEINNERHILITESTR,  /* 3d Shape Dialog inner hilite label     */
      DLG_STRING_SHAPEINNERSHADOWSTR,  /* 3d Shape Dialog inner shadow label     */
      DLG_STRING_SHAPEINNERWIDTHSTR,   /* 3d Shape Dialog inner width label      */
      DLG_STRING_SHAPEOUTERSTYLESTR,   /* 3d Shape Dialog outer style label      */
      DLG_STRING_SHAPEOUTERHILITESTR,  /* 3d Shape Dialog outer hilite label     */
      DLG_STRING_SHAPEOUTERSHADOWSTR,  /* 3d Shape Dialog outer shadow label     */
      DLG_STRING_SHAPEOUTERWIDTHSTR,   /* 3d Shape Dialog outer width label      */
      DLG_STRING_SHAPESHADOWSTR,       /* 3d Shape Dialog shadow label           */
      DLG_STRING_SHAPESHADOWCOLORSTR,  /* 3d Shape Dialog shadow color label     */
      DLG_STRING_SHAPESHADOWXSTR,      /* 3d Shape Dialog shadow x label         */
      DLG_STRING_SHAPESHADOWYSTR,      /* 3d Shape Dialog shadow y label         */
      /*
        Gradient Dialog strings
      */
      /* Gradient Categories */
      DLG_STRING_GRAD_LINE_CLASS,
      DLG_STRING_GRAD_ANGLE_CLASS,
      DLG_STRING_GRAD_RECT_CLASS,
      DLG_STRING_GRAD_ELLIPSE_CLASS,
      DLG_STRING_GRAD_CON_CLASS,
      /* Gradient Styles */
      DLG_STRING_GRAD_LINE_LTOR,
      DLG_STRING_GRAD_LINE_RTOL,
      DLG_STRING_GRAD_LINE_TTOB,
      DLG_STRING_GRAD_LINE_BTOT,
      DLG_STRING_GRAD_LINE_LTTORB,
      DLG_STRING_GRAD_LINE_LBTORT,
      DLG_STRING_GRAD_LINE_RTTOLB,
      DLG_STRING_GRAD_LINE_RBTOLT,
      DLG_STRING_GRAD_LINE2_LRTOC,
      DLG_STRING_GRAD_LINE2_CTOLR,
      DLG_STRING_GRAD_LINE2_TBTOC,
      DLG_STRING_GRAD_LINE2_CTOTB,
      DLG_STRING_GRAD_LINE2_LTRBTOC,
      DLG_STRING_GRAD_LINE2_CTOLTRB,
      DLG_STRING_GRAD_LINE2_RTLBTOC,
      DLG_STRING_GRAD_LINE2_CTORTLB,
      DLG_STRING_GRAD_ANGLE_TOLT,
      DLG_STRING_GRAD_ANGLE_TOLB,
      DLG_STRING_GRAD_ANGLE_TORT,
      DLG_STRING_GRAD_ANGLE_TORB,
      DLG_STRING_GRAD_ANGLE_FROMLT,
      DLG_STRING_GRAD_ANGLE_FROMLB,
      DLG_STRING_GRAD_ANGLE_FROMRT,
      DLG_STRING_GRAD_ANGLE_FROMRB,
      DLG_STRING_GRAD_RECT_TOC,
      DLG_STRING_GRAD_RECT_FROMC,
      DLG_STRING_GRAD_ELLIPSE_TOC,
      DLG_STRING_GRAD_ELLIPSE_FROMC,
      DLG_STRING_GRAD_CON_FROML,
      DLG_STRING_GRAD_CON_FROMR,
      DLG_STRING_GRAD_CON_FROMT,
      DLG_STRING_GRAD_CON_FROMB,
      DLG_STRING_GRAD_CON_FROMLT,
      DLG_STRING_GRAD_CON_FROMLB,
      DLG_STRING_GRAD_CON_FROMRT,
      DLG_STRING_GRAD_CON_FROMRB,
      /* Gradient Dialog control strings */
      DLG_STRING_GRADIENTOPTIONSSTR,    /* Gradient dialog title caption        */
      DLG_STRING_GRADIENTPREVIEWSTR,    /* Gradient dialog preview button label */
      DLG_STRING_GRADIENTCATEGORYSTR,   /* Gradient dialog category label       */
      DLG_STRING_GRADIENTSTYLESTR,      /* Gradient dialog style label          */
      DLG_STRING_GRADIENTSTARTCOLORSTR, /* Gradient dialog start color label    */
      DLG_STRING_GRADIENTENDCOLORSTR,   /* Gradient dialog end color label      */
      DLG_STRING_GRADIENTSTEPSSTR,      /* Gradient dialog steps label          */
      /*
        Transition Dialog strings
      */
      /* Transition options */
      DLG_STRING_TRANS_SOLIDFILL,
      DLG_STRING_TRANS_HORZFILL,
      DLG_STRING_TRANS_VERTFILL,
      DLG_STRING_TRANS_FOREDIAGFILL,
      DLG_STRING_TRANS_BACKDIAGFILL,
      DLG_STRING_TRANS_CROSSFILL,
      DLG_STRING_TRANS_DIAGCROSSFILL,
      DLG_STRING_TRANS_GRADIENTFILL,
      /* Transition Dialog control strings */
      DLG_STRING_TRANSITIONOPTIONSSTR,  /* Transition dialog title caption        */
      DLG_STRING_TRANSITIONPREVIEWSTR,  /* Transition dialog preview button label */
      DLG_STRING_TRANSITIONFILLSTR,     /* Transition dialog fill style label     */
      DLG_STRING_TRANSITIONGRADIENTSTR, /* Transition dialog gradient style label */
      DLG_STRING_TRANSITIONFORECOLORSTR,/* Transition dialog fore color label     */
      DLG_STRING_TRANSITIONBACKCOLORSTR,/* Transition dialog back color label     */
      DLG_STRING_TRANSITIONDELAYSTR,    /* Transition dialog delay label          */
      DLG_STRING_TRANSITIONGRAINSTR,    /* Transition dialog grain label          */
      DLG_STRING_TRANSITIONEFFECTSTR,   /* Transition dialog effect button label  */
      DLG_STRING_TRANSITIONTRANSPARENTSTR,/* Transition dialog transparent label  */
      DLG_STRING_TRANSITIONPASSESSTR,   /* Transition dialog passes label         */
      DLG_STRING_TRANSITIONWANDSTR,     /* Transition dialog wand label           */
      DLG_STRINGS3_MAX,
   }DlgStrings3;

   typedef enum
   {
      /*
        Paint Effect Dialog strings
      */
      /* Paint Effect Dialog control strings */
      DLG_STRING_EFFECTOPTIONSSTR=DLG_STRINGS3_MAX,      /* Paint Effect dialog title caption      */
      DLG_STRING_EFFECTCATEGORYSTR,     /* Paint Effect dialog category label     */
      DLG_STRING_EFFECTSTYLESTR,        /* Paint Effect dialog style label        */
      DLG_STRING_EFFECTPREVIEWSTR,      /* Paint Effect dialog preview label      */
      DLG_STRING_EFFECTDELAYSTR,        /* Paint Effect dialog delay label        */
      DLG_STRING_EFFECTGRAINSTR,        /* Paint Effect dialog grain label        */
      DLG_STRING_EFFECTPASSESSTR,       /* Paint Effect dialog passes label       */
      DLG_STRING_EFFECTWANDSTR,         /* Paint Effect dialog wand label         */
      DLG_STRING_EFFECTTRANSPARENTSTR,  /* Paint Effect dialog transparent label */
      /* Paint Effect Dialog effect class strings */
      DLG_STRING_EFFECT_NONE_CLASS,
      DLG_STRING_EFFECT_WIPE_CLASS,
      DLG_STRING_EFFECT_WIPE_RECTANGLE_CLASS,
      DLG_STRING_EFFECT_WIPE_CIRCLE_CLASS,
      DLG_STRING_EFFECT_PUSH_CLASS,
      DLG_STRING_EFFECT_SLIDE_CLASS,
      DLG_STRING_EFFECT_ROLL_CLASS,
      DLG_STRING_EFFECT_ROTATE_CLASS,
      DLG_STRING_EFFECT_ZOOM_CLASS,
      DLG_STRING_EFFECT_DRIP_CLASS,
      DLG_STRING_EFFECT_BLIND_CLASS,
      DLG_STRING_EFFECT_RANDOM_CLASS,
      DLG_STRING_EFFECT_CHECKERBOARD_CLASS,
      DLG_STRING_EFFECT_BLOCKS_CLASS,
      DLG_STRING_EFFECT_CIRCLE_CLASS,
      DLG_STRING_EFFECT_ELLIPSE_CLASS,
      /* Paint Effect Dialog effect strings */
      DLG_STRING_EFFECT_NONE,
      DLG_STRING_EFFECT_NO_PICTURE,

      DLG_STRING_EFFECT_WIPE_L_TO_R,
      DLG_STRING_EFFECT_WIPE_R_TO_L,
      DLG_STRING_EFFECT_WIPE_T_TO_B,
      DLG_STRING_EFFECT_WIPE_B_TO_T,
      DLG_STRING_EFFECT_WIPE_LT_TO_RB,
      DLG_STRING_EFFECT_WIPE_LB_TO_RT,
      DLG_STRING_EFFECT_WIPE_RT_TO_LB,
      DLG_STRING_EFFECT_WIPE_RB_TO_LT,
      DLG_STRING_EFFECT_WIPE_INTERH_L_TO_R_THEN_L_TO_R,
      DLG_STRING_EFFECT_WIPE_INTERV_T_TO_B_THEN_T_TO_B,
      DLG_STRING_EFFECT_WIPE_INTERH_L_TO_R_THEN_R_TO_L,
      DLG_STRING_EFFECT_WIPE_INTERV_T_TO_B_THEN_B_TO_T,
      DLG_STRING_EFFECT_WIPE_INTERV_L_TO_R_THEN_L_TO_R,
      DLG_STRING_EFFECT_WIPE_INTERV_R_TO_L_THEN_R_TO_L,
      DLG_STRING_EFFECT_WIPE_INTERH_T_TO_B_THEN_T_TO_B,
      DLG_STRING_EFFECT_WIPE_INTERH_B_TO_T_THEN_B_TO_T,
      DLG_STRING_EFFECT_WIPE_INTERV_L_TO_R_THEN_R_TO_L,
      DLG_STRING_EFFECT_WIPE_INTERV_R_TO_L_THEN_L_TO_R,
      DLG_STRING_EFFECT_WIPE_INTERH_T_TO_B_THEN_B_TO_T,
      DLG_STRING_EFFECT_WIPE_INTERH_B_TO_T_THEN_T_TO_B,
      DLG_STRING_EFFECT_WIPE_INTERH_L_TO_R_AND_R_TO_L,
      DLG_STRING_EFFECT_WIPE_INTERV_T_TO_B_AND_B_TO_T,
      DLG_STRING_EFFECT_WIPE_INTERV_L_AND_R_TO_C,
      DLG_STRING_EFFECT_WIPE_INTERV_C_TO_L_AND_R,
      DLG_STRING_EFFECT_WIPE_INTERH_T_AND_B_TO_C,
      DLG_STRING_EFFECT_WIPE_INTERH_C_TO_T_AND_B,
      DLG_STRING_EFFECT_WIPE_INTERV_L_AND_R_TO_C_THEN_C_TO_L_AND_R,
      DLG_STRING_EFFECT_WIPE_INTERV_C_TO_L_AND_R_THEN_L_AND_R_TO_C,
      DLG_STRING_EFFECT_WIPE_INTERH_T_AND_B_TO_C_THEN_C_TO_T_AND_B,
      DLG_STRING_EFFECT_WIPE_INTERH_C_TO_T_AND_B_THEN_T_AND_B_TO_C,
      DLG_STRING_EFFECT_WIPE2_LT_AND_RB_TO_C,
      DLG_STRING_EFFECT_WIPE2_LB_AND_RT_TO_C,
      DLG_STRING_EFFECT_WIPE2_C_TO_LT_AND_RB,
      DLG_STRING_EFFECT_WIPE2_C_TO_LB_AND_RT,
      DLG_STRING_EFFECT_WIPE2_LB_AND_RB_TO_T,
      DLG_STRING_EFFECT_WIPE2_LT_AND_RT_TO_B,
      DLG_STRING_EFFECT_WIPE2_RT_AND_RB_TO_L,
      DLG_STRING_EFFECT_WIPE2_LT_AND_LB_TO_R,
      DLG_STRING_EFFECT_WIPE2_L_T_TO_B_AND_R_B_TO_T,
      DLG_STRING_EFFECT_WIPE2_T_L_TO_R_AND_B_R_TO_L,
      DLG_STRING_EFFECT_WIPE4_CORNERS_OUT,
      DLG_STRING_EFFECT_WIPE4_C_TO_L_AND_R_THEN_T_AND_B,
      DLG_STRING_EFFECT_WIPE4_T_AND_B_THEN_L_AND_R_TO_C,
      DLG_STRING_EFFECT_WIPE4_L_L_L_L,
      DLG_STRING_EFFECT_WIPE4_L_L_L_R,
      DLG_STRING_EFFECT_WIPE4_L_L_L_T,
      DLG_STRING_EFFECT_WIPE4_L_L_L_B,
      DLG_STRING_EFFECT_WIPE4_L_L_R_L,
      DLG_STRING_EFFECT_WIPE4_L_L_R_R,
      DLG_STRING_EFFECT_WIPE4_L_L_R_T,
      DLG_STRING_EFFECT_WIPE4_L_L_R_B,
      DLG_STRING_EFFECT_WIPE4_L_L_T_L,
      DLG_STRING_EFFECT_WIPE4_L_L_T_R,
      DLG_STRING_EFFECT_WIPE4_L_L_T_T,
      DLG_STRING_EFFECT_WIPE4_L_L_T_B,
      DLG_STRING_EFFECT_WIPE4_L_L_B_L,
      DLG_STRING_EFFECT_WIPE4_L_L_B_R,
      DLG_STRING_EFFECT_WIPE4_L_L_B_T,
      DLG_STRING_EFFECT_WIPE4_L_L_B_B,
      DLG_STRING_EFFECT_WIPE4_L_R_L_L,
      DLG_STRING_EFFECT_WIPE4_L_R_L_R,
      DLG_STRING_EFFECT_WIPE4_L_R_L_T,
      DLG_STRING_EFFECT_WIPE4_L_R_L_B,
      DLG_STRING_EFFECT_WIPE4_L_R_R_L,
      DLG_STRING_EFFECT_WIPE4_L_R_R_R,
      DLG_STRING_EFFECT_WIPE4_L_R_R_T,
      DLG_STRING_EFFECT_WIPE4_L_R_R_B,
      DLG_STRING_EFFECT_WIPE4_L_R_T_L,
      DLG_STRING_EFFECT_WIPE4_L_R_T_R,
      DLG_STRING_EFFECT_WIPE4_L_R_T_T,
      DLG_STRING_EFFECT_WIPE4_L_R_T_B,
      DLG_STRING_EFFECT_WIPE4_L_R_B_L,
      DLG_STRING_EFFECT_WIPE4_L_R_B_R,
      DLG_STRING_EFFECT_WIPE4_L_R_B_T,
      DLG_STRING_EFFECT_WIPE4_L_R_B_B,
      DLG_STRING_EFFECT_WIPE4_L_T_L_L,
      DLG_STRING_EFFECT_WIPE4_L_T_L_R,
      DLG_STRING_EFFECT_WIPE4_L_T_L_T,
      DLG_STRING_EFFECT_WIPE4_L_T_L_B,
      DLG_STRING_EFFECT_WIPE4_L_T_R_L,
      DLG_STRING_EFFECT_WIPE4_L_T_R_R,
      DLG_STRING_EFFECT_WIPE4_L_T_R_T,
      DLG_STRING_EFFECT_WIPE4_L_T_R_B,
      DLG_STRING_EFFECT_WIPE4_L_T_T_L,
      DLG_STRING_EFFECT_WIPE4_L_T_T_R,
      DLG_STRING_EFFECT_WIPE4_L_T_T_T,
      DLG_STRING_EFFECT_WIPE4_L_T_T_B,
      DLG_STRING_EFFECT_WIPE4_L_T_B_L,
      DLG_STRING_EFFECT_WIPE4_L_T_B_R,
      DLG_STRING_EFFECT_WIPE4_L_T_B_T,
      DLG_STRING_EFFECT_WIPE4_L_T_B_B,
      DLG_STRING_EFFECT_WIPE4_L_B_L_L,
      DLG_STRING_EFFECT_WIPE4_L_B_L_R,
      DLG_STRING_EFFECT_WIPE4_L_B_L_T,
      DLG_STRING_EFFECT_WIPE4_L_B_L_B,
      DLG_STRING_EFFECT_WIPE4_L_B_R_L,
      DLG_STRING_EFFECT_WIPE4_L_B_R_R,
      DLG_STRING_EFFECT_WIPE4_L_B_R_T,
      DLG_STRING_EFFECT_WIPE4_L_B_R_B,
      DLG_STRING_EFFECT_WIPE4_L_B_T_L,
      DLG_STRING_EFFECT_WIPE4_L_B_T_R,
      DLG_STRING_EFFECT_WIPE4_L_B_T_T,
      DLG_STRING_EFFECT_WIPE4_L_B_T_B,
      DLG_STRING_EFFECT_WIPE4_L_B_B_L,
      DLG_STRING_EFFECT_WIPE4_L_B_B_R,
      DLG_STRING_EFFECT_WIPE4_L_B_B_T,
      DLG_STRING_EFFECT_WIPE4_L_B_B_B,
      DLG_STRING_EFFECT_WIPE4_R_L_L_L,
      DLG_STRING_EFFECT_WIPE4_R_L_L_R,
      DLG_STRING_EFFECT_WIPE4_R_L_L_T,
      DLG_STRING_EFFECT_WIPE4_R_L_L_B,
      DLG_STRING_EFFECT_WIPE4_R_L_R_L,
      DLG_STRING_EFFECT_WIPE4_R_L_R_R,
      DLG_STRING_EFFECT_WIPE4_R_L_R_T,
      DLG_STRING_EFFECT_WIPE4_R_L_R_B,
      DLG_STRING_EFFECT_WIPE4_R_L_T_L,
      DLG_STRING_EFFECT_WIPE4_R_L_T_R,
      DLG_STRING_EFFECT_WIPE4_R_L_T_T,
      DLG_STRING_EFFECT_WIPE4_R_L_T_B,
      DLG_STRING_EFFECT_WIPE4_R_L_B_L,
      DLG_STRING_EFFECT_WIPE4_R_L_B_R,
      DLG_STRING_EFFECT_WIPE4_R_L_B_T,
      DLG_STRING_EFFECT_WIPE4_R_L_B_B,
      DLG_STRING_EFFECT_WIPE4_R_R_L_L,
      DLG_STRING_EFFECT_WIPE4_R_R_L_R,
      DLG_STRING_EFFECT_WIPE4_R_R_L_T,
      DLG_STRING_EFFECT_WIPE4_R_R_L_B,
      DLG_STRING_EFFECT_WIPE4_R_R_R_L,
      DLG_STRING_EFFECT_WIPE4_R_R_R_R,
      DLG_STRING_EFFECT_WIPE4_R_R_R_T,
      DLG_STRING_EFFECT_WIPE4_R_R_R_B,
      DLG_STRING_EFFECT_WIPE4_R_R_T_L,
      DLG_STRING_EFFECT_WIPE4_R_R_T_R,
      DLG_STRING_EFFECT_WIPE4_R_R_T_T,
      DLG_STRING_EFFECT_WIPE4_R_R_T_B,
      DLG_STRING_EFFECT_WIPE4_R_R_B_L,
      DLG_STRING_EFFECT_WIPE4_R_R_B_R,
      DLG_STRING_EFFECT_WIPE4_R_R_B_T,
      DLG_STRING_EFFECT_WIPE4_R_R_B_B,
      DLG_STRING_EFFECT_WIPE4_R_T_L_L,
      DLG_STRING_EFFECT_WIPE4_R_T_L_R,
      DLG_STRING_EFFECT_WIPE4_R_T_L_T,
      DLG_STRING_EFFECT_WIPE4_R_T_L_B,
      DLG_STRING_EFFECT_WIPE4_R_T_R_L,
      DLG_STRING_EFFECT_WIPE4_R_T_R_R,
      DLG_STRING_EFFECT_WIPE4_R_T_R_T,
      DLG_STRING_EFFECT_WIPE4_R_T_R_B,
      DLG_STRING_EFFECT_WIPE4_R_T_T_L,
      DLG_STRING_EFFECT_WIPE4_R_T_T_R,
      DLG_STRING_EFFECT_WIPE4_R_T_T_T,
      DLG_STRING_EFFECT_WIPE4_R_T_T_B,
      DLG_STRING_EFFECT_WIPE4_R_T_B_L,
      DLG_STRING_EFFECT_WIPE4_R_T_B_R,
      DLG_STRING_EFFECT_WIPE4_R_T_B_T,
      DLG_STRING_EFFECT_WIPE4_R_T_B_B,
      DLG_STRING_EFFECT_WIPE4_R_B_L_L,
      DLG_STRING_EFFECT_WIPE4_R_B_L_R,
      DLG_STRING_EFFECT_WIPE4_R_B_L_T,
      DLG_STRING_EFFECT_WIPE4_R_B_L_B,
      DLG_STRING_EFFECT_WIPE4_R_B_R_L,
      DLG_STRING_EFFECT_WIPE4_R_B_R_R,
      DLG_STRING_EFFECT_WIPE4_R_B_R_T,
      DLG_STRING_EFFECT_WIPE4_R_B_R_B,
      DLG_STRING_EFFECT_WIPE4_R_B_T_L,
      DLG_STRING_EFFECT_WIPE4_R_B_T_R,
      DLG_STRING_EFFECT_WIPE4_R_B_T_T,
      DLG_STRING_EFFECT_WIPE4_R_B_T_B,
      DLG_STRING_EFFECT_WIPE4_R_B_B_L,
      DLG_STRING_EFFECT_WIPE4_R_B_B_R,
      DLG_STRING_EFFECT_WIPE4_R_B_B_T,
      DLG_STRING_EFFECT_WIPE4_R_B_B_B,
      DLG_STRING_EFFECT_WIPE4_T_L_L_L,
      DLG_STRING_EFFECT_WIPE4_T_L_L_R,
      DLG_STRING_EFFECT_WIPE4_T_L_L_T,
      DLG_STRING_EFFECT_WIPE4_T_L_L_B,
      DLG_STRING_EFFECT_WIPE4_T_L_R_L,
      DLG_STRING_EFFECT_WIPE4_T_L_R_R,
      DLG_STRING_EFFECT_WIPE4_T_L_R_T,
      DLG_STRING_EFFECT_WIPE4_T_L_R_B,
      DLG_STRING_EFFECT_WIPE4_T_L_T_L,
      DLG_STRING_EFFECT_WIPE4_T_L_T_R,
      DLG_STRING_EFFECT_WIPE4_T_L_T_T,
      DLG_STRING_EFFECT_WIPE4_T_L_T_B,
      DLG_STRING_EFFECT_WIPE4_T_L_B_L,
      DLG_STRING_EFFECT_WIPE4_T_L_B_R,
      DLG_STRING_EFFECT_WIPE4_T_L_B_T,
      DLG_STRING_EFFECT_WIPE4_T_L_B_B,
      DLG_STRING_EFFECT_WIPE4_T_R_L_L,
      DLG_STRING_EFFECT_WIPE4_T_R_L_R,
      DLG_STRING_EFFECT_WIPE4_T_R_L_T,
      DLG_STRING_EFFECT_WIPE4_T_R_L_B,
      DLG_STRING_EFFECT_WIPE4_T_R_R_L,
      DLG_STRING_EFFECT_WIPE4_T_R_R_R,
      DLG_STRING_EFFECT_WIPE4_T_R_R_T,
      DLG_STRING_EFFECT_WIPE4_T_R_R_B,
      DLG_STRING_EFFECT_WIPE4_T_R_T_L,
      DLG_STRING_EFFECT_WIPE4_T_R_T_R,
      DLG_STRING_EFFECT_WIPE4_T_R_T_T,
      DLG_STRING_EFFECT_WIPE4_T_R_T_B,
      DLG_STRING_EFFECT_WIPE4_T_R_B_L,
      DLG_STRING_EFFECT_WIPE4_T_R_B_R,
      DLG_STRING_EFFECT_WIPE4_T_R_B_T,
      DLG_STRING_EFFECT_WIPE4_T_R_B_B,
      DLG_STRING_EFFECT_WIPE4_T_T_L_L,
      DLG_STRING_EFFECT_WIPE4_T_T_L_R,
      DLG_STRING_EFFECT_WIPE4_T_T_L_T,
      DLG_STRING_EFFECT_WIPE4_T_T_L_B,
      DLG_STRING_EFFECT_WIPE4_T_T_R_L,
      DLG_STRING_EFFECT_WIPE4_T_T_R_R,
      DLG_STRING_EFFECT_WIPE4_T_T_R_T,
      DLG_STRING_EFFECT_WIPE4_T_T_R_B,
      DLG_STRING_EFFECT_WIPE4_T_T_T_L,
      DLG_STRING_EFFECT_WIPE4_T_T_T_R,
      DLG_STRING_EFFECT_WIPE4_T_T_T_T,
      DLG_STRING_EFFECT_WIPE4_T_T_T_B,
      DLG_STRING_EFFECT_WIPE4_T_T_B_L,
      DLG_STRING_EFFECT_WIPE4_T_T_B_R,
      DLG_STRING_EFFECT_WIPE4_T_T_B_T,
      DLG_STRING_EFFECT_WIPE4_T_T_B_B,
      DLG_STRING_EFFECT_WIPE4_T_B_L_L,
      DLG_STRING_EFFECT_WIPE4_T_B_L_R,
      DLG_STRING_EFFECT_WIPE4_T_B_L_T,
      DLG_STRING_EFFECT_WIPE4_T_B_L_B,
      DLG_STRING_EFFECT_WIPE4_T_B_R_L,
      DLG_STRING_EFFECT_WIPE4_T_B_R_R,
      DLG_STRING_EFFECT_WIPE4_T_B_R_T,
      DLG_STRING_EFFECT_WIPE4_T_B_R_B,
      DLG_STRING_EFFECT_WIPE4_T_B_T_L,
      DLG_STRING_EFFECT_WIPE4_T_B_T_R,
      DLG_STRING_EFFECT_WIPE4_T_B_T_T,
      DLG_STRING_EFFECT_WIPE4_T_B_T_B,
      DLG_STRING_EFFECT_WIPE4_T_B_B_L,
      DLG_STRING_EFFECT_WIPE4_T_B_B_R,
      DLG_STRING_EFFECT_WIPE4_T_B_B_T,
      DLG_STRING_EFFECT_WIPE4_T_B_B_B,
      DLG_STRING_EFFECT_WIPE4_B_L_L_L,
      DLG_STRING_EFFECT_WIPE4_B_L_L_R,
      DLG_STRING_EFFECT_WIPE4_B_L_L_T,
      DLG_STRING_EFFECT_WIPE4_B_L_L_B,
      DLG_STRING_EFFECT_WIPE4_B_L_R_L,
      DLG_STRING_EFFECT_WIPE4_B_L_R_R,
      DLG_STRING_EFFECT_WIPE4_B_L_R_T,
      DLG_STRING_EFFECT_WIPE4_B_L_R_B,
      DLG_STRING_EFFECT_WIPE4_B_L_T_L,
      DLG_STRING_EFFECT_WIPE4_B_L_T_R,
      DLG_STRING_EFFECT_WIPE4_B_L_T_T,
      DLG_STRING_EFFECT_WIPE4_B_L_T_B,
      DLG_STRING_EFFECT_WIPE4_B_L_B_L,
      DLG_STRING_EFFECT_WIPE4_B_L_B_R,
      DLG_STRING_EFFECT_WIPE4_B_L_B_T,
      DLG_STRING_EFFECT_WIPE4_B_L_B_B,
      DLG_STRING_EFFECT_WIPE4_B_R_L_L,
      DLG_STRING_EFFECT_WIPE4_B_R_L_R,
      DLG_STRING_EFFECT_WIPE4_B_R_L_T,
      DLG_STRING_EFFECT_WIPE4_B_R_L_B,
      DLG_STRING_EFFECT_WIPE4_B_R_R_L,
      DLG_STRING_EFFECT_WIPE4_B_R_R_R,
      DLG_STRING_EFFECT_WIPE4_B_R_R_T,
      DLG_STRING_EFFECT_WIPE4_B_R_R_B,
      DLG_STRING_EFFECT_WIPE4_B_R_T_L,
      DLG_STRING_EFFECT_WIPE4_B_R_T_R,
      DLG_STRING_EFFECT_WIPE4_B_R_T_T,
      DLG_STRING_EFFECT_WIPE4_B_R_T_B,
      DLG_STRING_EFFECT_WIPE4_B_R_B_L,
      DLG_STRING_EFFECT_WIPE4_B_R_B_R,
      DLG_STRING_EFFECT_WIPE4_B_R_B_T,
      DLG_STRING_EFFECT_WIPE4_B_R_B_B,
      DLG_STRING_EFFECT_WIPE4_B_T_L_L,
      DLG_STRING_EFFECT_WIPE4_B_T_L_R,
      DLG_STRING_EFFECT_WIPE4_B_T_L_T,
      DLG_STRING_EFFECT_WIPE4_B_T_L_B,
      DLG_STRING_EFFECT_WIPE4_B_T_R_L,
      DLG_STRING_EFFECT_WIPE4_B_T_R_R,
      DLG_STRING_EFFECT_WIPE4_B_T_R_T,
      DLG_STRING_EFFECT_WIPE4_B_T_R_B,
      DLG_STRING_EFFECT_WIPE4_B_T_T_L,
      DLG_STRING_EFFECT_WIPE4_B_T_T_R,
      DLG_STRING_EFFECT_WIPE4_B_T_T_T,
      DLG_STRING_EFFECT_WIPE4_B_T_T_B,
      DLG_STRING_EFFECT_WIPE4_B_T_B_L,
      DLG_STRING_EFFECT_WIPE4_B_T_B_R,
      DLG_STRING_EFFECT_WIPE4_B_T_B_T,
      DLG_STRING_EFFECT_WIPE4_B_T_B_B,
      DLG_STRING_EFFECT_WIPE4_B_B_L_L,
      DLG_STRING_EFFECT_WIPE4_B_B_L_R,
      DLG_STRING_EFFECT_WIPE4_B_B_L_T,
      DLG_STRING_EFFECT_WIPE4_B_B_L_B,
      DLG_STRING_EFFECT_WIPE4_B_B_R_L,
      DLG_STRING_EFFECT_WIPE4_B_B_R_R,
      DLG_STRING_EFFECT_WIPE4_B_B_R_T,
      DLG_STRING_EFFECT_WIPE4_B_B_R_B,
      DLG_STRING_EFFECT_WIPE4_B_B_T_L,
      DLG_STRING_EFFECT_WIPE4_B_B_T_R,
      DLG_STRING_EFFECT_WIPE4_B_B_T_T,
      DLG_STRING_EFFECT_WIPE4_B_B_T_B,
      DLG_STRING_EFFECT_WIPE4_B_B_B_L,
      DLG_STRING_EFFECT_WIPE4_B_B_B_R,
      DLG_STRING_EFFECT_WIPE4_B_B_B_T,
      DLG_STRING_EFFECT_WIPE4_B_B_B_B,
      DLG_STRING_EFFECT_WIPE4_LT_LT_LT_LT,
      DLG_STRING_EFFECT_WIPE4_LT_LT_LT_LB,
      DLG_STRING_EFFECT_WIPE4_LT_LT_LT_RT,
      DLG_STRING_EFFECT_WIPE4_LT_LT_LT_RB,
      DLG_STRING_EFFECT_WIPE4_LT_LT_LB_LT,
      DLG_STRING_EFFECT_WIPE4_LT_LT_LB_LB,
      DLG_STRING_EFFECT_WIPE4_LT_LT_LB_RT,
      DLG_STRING_EFFECT_WIPE4_LT_LT_LB_RB,
      DLG_STRING_EFFECT_WIPE4_LT_LT_RT_LT,
      DLG_STRING_EFFECT_WIPE4_LT_LT_RT_LB,
      DLG_STRING_EFFECT_WIPE4_LT_LT_RT_RT,
      DLG_STRING_EFFECT_WIPE4_LT_LT_RT_RB,
      DLG_STRING_EFFECT_WIPE4_LT_LT_RB_LT,
      DLG_STRING_EFFECT_WIPE4_LT_LT_RB_LB,
      DLG_STRING_EFFECT_WIPE4_LT_LT_RB_RT,
      DLG_STRING_EFFECT_WIPE4_LT_LT_RB_RB,
      DLG_STRING_EFFECT_WIPE4_LT_LB_LT_LT,
      DLG_STRING_EFFECT_WIPE4_LT_LB_LT_LB,
      DLG_STRING_EFFECT_WIPE4_LT_LB_LT_RT,
      DLG_STRING_EFFECT_WIPE4_LT_LB_LT_RB,
      DLG_STRING_EFFECT_WIPE4_LT_LB_LB_LT,
      DLG_STRING_EFFECT_WIPE4_LT_LB_LB_LB,
      DLG_STRING_EFFECT_WIPE4_LT_LB_LB_RT,
      DLG_STRING_EFFECT_WIPE4_LT_LB_LB_RB,
      DLG_STRING_EFFECT_WIPE4_LT_LB_RT_LT,
      DLG_STRING_EFFECT_WIPE4_LT_LB_RT_LB,
      DLG_STRING_EFFECT_WIPE4_LT_LB_RT_RT,
      DLG_STRING_EFFECT_WIPE4_LT_LB_RT_RB,
      DLG_STRING_EFFECT_WIPE4_LT_LB_RB_LT,
      DLG_STRING_EFFECT_WIPE4_LT_LB_RB_LB,
      DLG_STRING_EFFECT_WIPE4_LT_LB_RB_RT,
      DLG_STRING_EFFECT_WIPE4_LT_LB_RB_RB,
      DLG_STRING_EFFECT_WIPE4_LT_RT_LT_LT,
      DLG_STRING_EFFECT_WIPE4_LT_RT_LT_LB,
      DLG_STRING_EFFECT_WIPE4_LT_RT_LT_RT,
      DLG_STRING_EFFECT_WIPE4_LT_RT_LT_RB,
      DLG_STRING_EFFECT_WIPE4_LT_RT_LB_LT,
      DLG_STRING_EFFECT_WIPE4_LT_RT_LB_LB,
      DLG_STRING_EFFECT_WIPE4_LT_RT_LB_RT,
      DLG_STRING_EFFECT_WIPE4_LT_RT_LB_RB,
      DLG_STRING_EFFECT_WIPE4_LT_RT_RT_LT,
      DLG_STRING_EFFECT_WIPE4_LT_RT_RT_LB,
      DLG_STRING_EFFECT_WIPE4_LT_RT_RT_RT,
      DLG_STRING_EFFECT_WIPE4_LT_RT_RT_RB,
      DLG_STRING_EFFECT_WIPE4_LT_RT_RB_LT,
      DLG_STRING_EFFECT_WIPE4_LT_RT_RB_LB,
      DLG_STRING_EFFECT_WIPE4_LT_RT_RB_RT,
      DLG_STRING_EFFECT_WIPE4_LT_RT_RB_RB,
      DLG_STRING_EFFECT_WIPE4_LT_RB_LT_LT,
      DLG_STRING_EFFECT_WIPE4_LT_RB_LT_LB,
      DLG_STRING_EFFECT_WIPE4_LT_RB_LT_RT,
      DLG_STRING_EFFECT_WIPE4_LT_RB_LT_RB,
      DLG_STRING_EFFECT_WIPE4_LT_RB_LB_LT,
      DLG_STRING_EFFECT_WIPE4_LT_RB_LB_LB,
      DLG_STRING_EFFECT_WIPE4_LT_RB_LB_RT,
      DLG_STRING_EFFECT_WIPE4_LT_RB_LB_RB,
      DLG_STRING_EFFECT_WIPE4_LT_RB_RT_LT,
      DLG_STRING_EFFECT_WIPE4_LT_RB_RT_LB,
      DLG_STRING_EFFECT_WIPE4_LT_RB_RT_RT,
      DLG_STRING_EFFECT_WIPE4_LT_RB_RT_RB,
      DLG_STRING_EFFECT_WIPE4_LT_RB_RB_LT,
      DLG_STRING_EFFECT_WIPE4_LT_RB_RB_LB,
      DLG_STRING_EFFECT_WIPE4_LT_RB_RB_RT,
      DLG_STRING_EFFECT_WIPE4_LT_RB_RB_RB,
      DLG_STRING_EFFECT_WIPE4_LB_LT_LT_LT,
      DLG_STRING_EFFECT_WIPE4_LB_LT_LT_LB,
      DLG_STRING_EFFECT_WIPE4_LB_LT_LT_RT,
      DLG_STRING_EFFECT_WIPE4_LB_LT_LT_RB,
      DLG_STRING_EFFECT_WIPE4_LB_LT_LB_LT,
      DLG_STRING_EFFECT_WIPE4_LB_LT_LB_LB,
      DLG_STRING_EFFECT_WIPE4_LB_LT_LB_RT,
      DLG_STRING_EFFECT_WIPE4_LB_LT_LB_RB,
      DLG_STRING_EFFECT_WIPE4_LB_LT_RT_LT,
      DLG_STRING_EFFECT_WIPE4_LB_LT_RT_LB,
      DLG_STRING_EFFECT_WIPE4_LB_LT_RT_RT,
      DLG_STRING_EFFECT_WIPE4_LB_LT_RT_RB,
      DLG_STRING_EFFECT_WIPE4_LB_LT_RB_LT,
      DLG_STRING_EFFECT_WIPE4_LB_LT_RB_LB,
      DLG_STRING_EFFECT_WIPE4_LB_LT_RB_RT,
      DLG_STRING_EFFECT_WIPE4_LB_LT_RB_RB,
      DLG_STRING_EFFECT_WIPE4_LB_LB_LT_LT,
      DLG_STRING_EFFECT_WIPE4_LB_LB_LT_LB,
      DLG_STRING_EFFECT_WIPE4_LB_LB_LT_RT,
      DLG_STRING_EFFECT_WIPE4_LB_LB_LT_RB,
      DLG_STRING_EFFECT_WIPE4_LB_LB_LB_LT,
      DLG_STRING_EFFECT_WIPE4_LB_LB_LB_LB,
      DLG_STRING_EFFECT_WIPE4_LB_LB_LB_RT,
      DLG_STRING_EFFECT_WIPE4_LB_LB_LB_RB,
      DLG_STRING_EFFECT_WIPE4_LB_LB_RT_LT,
      DLG_STRING_EFFECT_WIPE4_LB_LB_RT_LB,
      DLG_STRING_EFFECT_WIPE4_LB_LB_RT_RT,
      DLG_STRING_EFFECT_WIPE4_LB_LB_RT_RB,
      DLG_STRING_EFFECT_WIPE4_LB_LB_RB_LT,
      DLG_STRING_EFFECT_WIPE4_LB_LB_RB_LB,
      DLG_STRING_EFFECT_WIPE4_LB_LB_RB_RT,
      DLG_STRING_EFFECT_WIPE4_LB_LB_RB_RB,
      DLG_STRING_EFFECT_WIPE4_LB_RT_LT_LT,
      DLG_STRING_EFFECT_WIPE4_LB_RT_LT_LB,
      DLG_STRING_EFFECT_WIPE4_LB_RT_LT_RT,
      DLG_STRING_EFFECT_WIPE4_LB_RT_LT_RB,
      DLG_STRING_EFFECT_WIPE4_LB_RT_LB_LT,
      DLG_STRING_EFFECT_WIPE4_LB_RT_LB_LB,
      DLG_STRING_EFFECT_WIPE4_LB_RT_LB_RT,
      DLG_STRING_EFFECT_WIPE4_LB_RT_LB_RB,
      DLG_STRING_EFFECT_WIPE4_LB_RT_RT_LT,
      DLG_STRING_EFFECT_WIPE4_LB_RT_RT_LB,
      DLG_STRING_EFFECT_WIPE4_LB_RT_RT_RT,
      DLG_STRING_EFFECT_WIPE4_LB_RT_RT_RB,
      DLG_STRING_EFFECT_WIPE4_LB_RT_RB_LT,
      DLG_STRING_EFFECT_WIPE4_LB_RT_RB_LB,
      DLG_STRING_EFFECT_WIPE4_LB_RT_RB_RT,
      DLG_STRING_EFFECT_WIPE4_LB_RT_RB_RB,
      DLG_STRING_EFFECT_WIPE4_LB_RB_LT_LT,
      DLG_STRING_EFFECT_WIPE4_LB_RB_LT_LB,
      DLG_STRING_EFFECT_WIPE4_LB_RB_LT_RT,
      DLG_STRING_EFFECT_WIPE4_LB_RB_LT_RB,
      DLG_STRING_EFFECT_WIPE4_LB_RB_LB_LT,
      DLG_STRING_EFFECT_WIPE4_LB_RB_LB_LB,
      DLG_STRING_EFFECT_WIPE4_LB_RB_LB_RT,
      DLG_STRING_EFFECT_WIPE4_LB_RB_LB_RB,
      DLG_STRING_EFFECT_WIPE4_LB_RB_RT_LT,
      DLG_STRING_EFFECT_WIPE4_LB_RB_RT_LB,
      DLG_STRING_EFFECT_WIPE4_LB_RB_RT_RT,
      DLG_STRING_EFFECT_WIPE4_LB_RB_RT_RB,
      DLG_STRING_EFFECT_WIPE4_LB_RB_RB_LT,
      DLG_STRING_EFFECT_WIPE4_LB_RB_RB_LB,
      DLG_STRING_EFFECT_WIPE4_LB_RB_RB_RT,
      DLG_STRING_EFFECT_WIPE4_LB_RB_RB_RB,
      DLG_STRING_EFFECT_WIPE4_RT_LT_LT_LT,
      DLG_STRING_EFFECT_WIPE4_RT_LT_LT_LB,
      DLG_STRING_EFFECT_WIPE4_RT_LT_LT_RT,
      DLG_STRING_EFFECT_WIPE4_RT_LT_LT_RB,
      DLG_STRING_EFFECT_WIPE4_RT_LT_LB_LT,
      DLG_STRING_EFFECT_WIPE4_RT_LT_LB_LB,
      DLG_STRING_EFFECT_WIPE4_RT_LT_LB_RT,
      DLG_STRING_EFFECT_WIPE4_RT_LT_LB_RB,
      DLG_STRING_EFFECT_WIPE4_RT_LT_RT_LT,
      DLG_STRING_EFFECT_WIPE4_RT_LT_RT_LB,
      DLG_STRING_EFFECT_WIPE4_RT_LT_RT_RT,
      DLG_STRING_EFFECT_WIPE4_RT_LT_RT_RB,
      DLG_STRING_EFFECT_WIPE4_RT_LT_RB_LT,
      DLG_STRING_EFFECT_WIPE4_RT_LT_RB_LB,
      DLG_STRING_EFFECT_WIPE4_RT_LT_RB_RT,
      DLG_STRING_EFFECT_WIPE4_RT_LT_RB_RB,
      DLG_STRING_EFFECT_WIPE4_RT_LB_LT_LT,
      DLG_STRING_EFFECT_WIPE4_RT_LB_LT_LB,
      DLG_STRING_EFFECT_WIPE4_RT_LB_LT_RT,
      DLG_STRING_EFFECT_WIPE4_RT_LB_LT_RB,
      DLG_STRING_EFFECT_WIPE4_RT_LB_LB_LT,
      DLG_STRING_EFFECT_WIPE4_RT_LB_LB_LB,
      DLG_STRING_EFFECT_WIPE4_RT_LB_LB_RT,
      DLG_STRING_EFFECT_WIPE4_RT_LB_LB_RB,
      DLG_STRING_EFFECT_WIPE4_RT_LB_RT_LT,
      DLG_STRING_EFFECT_WIPE4_RT_LB_RT_LB,
      DLG_STRING_EFFECT_WIPE4_RT_LB_RT_RT,
      DLG_STRING_EFFECT_WIPE4_RT_LB_RT_RB,
      DLG_STRING_EFFECT_WIPE4_RT_LB_RB_LT,
      DLG_STRING_EFFECT_WIPE4_RT_LB_RB_LB,
      DLG_STRING_EFFECT_WIPE4_RT_LB_RB_RT,
      DLG_STRING_EFFECT_WIPE4_RT_LB_RB_RB,
      DLG_STRING_EFFECT_WIPE4_RT_RT_LT_LT,
      DLG_STRING_EFFECT_WIPE4_RT_RT_LT_LB,
      DLG_STRING_EFFECT_WIPE4_RT_RT_LT_RT,
      DLG_STRING_EFFECT_WIPE4_RT_RT_LT_RB,
      DLG_STRING_EFFECT_WIPE4_RT_RT_LB_LT,
      DLG_STRING_EFFECT_WIPE4_RT_RT_LB_LB,
      DLG_STRING_EFFECT_WIPE4_RT_RT_LB_RT,
      DLG_STRING_EFFECT_WIPE4_RT_RT_LB_RB,
      DLG_STRING_EFFECT_WIPE4_RT_RT_RT_LT,
      DLG_STRING_EFFECT_WIPE4_RT_RT_RT_LB,
      DLG_STRING_EFFECT_WIPE4_RT_RT_RT_RT,
      DLG_STRING_EFFECT_WIPE4_RT_RT_RT_RB,
      DLG_STRING_EFFECT_WIPE4_RT_RT_RB_LT,
      DLG_STRING_EFFECT_WIPE4_RT_RT_RB_LB,
      DLG_STRING_EFFECT_WIPE4_RT_RT_RB_RT,
      DLG_STRING_EFFECT_WIPE4_RT_RT_RB_RB,
      DLG_STRING_EFFECT_WIPE4_RT_RB_LT_LT,
      DLG_STRING_EFFECT_WIPE4_RT_RB_LT_LB,
      DLG_STRING_EFFECT_WIPE4_RT_RB_LT_RT,
      DLG_STRING_EFFECT_WIPE4_RT_RB_LT_RB,
      DLG_STRING_EFFECT_WIPE4_RT_RB_LB_LT,
      DLG_STRING_EFFECT_WIPE4_RT_RB_LB_LB,
      DLG_STRING_EFFECT_WIPE4_RT_RB_LB_RT,
      DLG_STRING_EFFECT_WIPE4_RT_RB_LB_RB,
      DLG_STRING_EFFECT_WIPE4_RT_RB_RT_LT,
      DLG_STRING_EFFECT_WIPE4_RT_RB_RT_LB,
      DLG_STRING_EFFECT_WIPE4_RT_RB_RT_RT,
      DLG_STRING_EFFECT_WIPE4_RT_RB_RT_RB,
      DLG_STRING_EFFECT_WIPE4_RT_RB_RB_LT,
      DLG_STRING_EFFECT_WIPE4_RT_RB_RB_LB,
      DLG_STRING_EFFECT_WIPE4_RT_RB_RB_RT,
      DLG_STRING_EFFECT_WIPE4_RT_RB_RB_RB,
      DLG_STRING_EFFECT_WIPE4_RB_LT_LT_LT,
      DLG_STRING_EFFECT_WIPE4_RB_LT_LT_LB,
      DLG_STRING_EFFECT_WIPE4_RB_LT_LT_RT,
      DLG_STRING_EFFECT_WIPE4_RB_LT_LT_RB,
      DLG_STRING_EFFECT_WIPE4_RB_LT_LB_LT,
      DLG_STRING_EFFECT_WIPE4_RB_LT_LB_LB,
      DLG_STRING_EFFECT_WIPE4_RB_LT_LB_RT,
      DLG_STRING_EFFECT_WIPE4_RB_LT_LB_RB,
      DLG_STRING_EFFECT_WIPE4_RB_LT_RT_LT,
      DLG_STRING_EFFECT_WIPE4_RB_LT_RT_LB,
      DLG_STRING_EFFECT_WIPE4_RB_LT_RT_RT,
      DLG_STRING_EFFECT_WIPE4_RB_LT_RT_RB,
      DLG_STRING_EFFECT_WIPE4_RB_LT_RB_LT,
      DLG_STRING_EFFECT_WIPE4_RB_LT_RB_LB,
      DLG_STRING_EFFECT_WIPE4_RB_LT_RB_RT,
      DLG_STRING_EFFECT_WIPE4_RB_LT_RB_RB,
      DLG_STRING_EFFECT_WIPE4_RB_LB_LT_LT,
      DLG_STRING_EFFECT_WIPE4_RB_LB_LT_LB,
      DLG_STRING_EFFECT_WIPE4_RB_LB_LT_RT,
      DLG_STRING_EFFECT_WIPE4_RB_LB_LT_RB,
      DLG_STRING_EFFECT_WIPE4_RB_LB_LB_LT,
      DLG_STRING_EFFECT_WIPE4_RB_LB_LB_LB,
      DLG_STRING_EFFECT_WIPE4_RB_LB_LB_RT,
      DLG_STRING_EFFECT_WIPE4_RB_LB_LB_RB,
      DLG_STRING_EFFECT_WIPE4_RB_LB_RT_LT,
      DLG_STRING_EFFECT_WIPE4_RB_LB_RT_LB,
      DLG_STRING_EFFECT_WIPE4_RB_LB_RT_RT,
      DLG_STRING_EFFECT_WIPE4_RB_LB_RT_RB,
      DLG_STRING_EFFECT_WIPE4_RB_LB_RB_LT,
      DLG_STRING_EFFECT_WIPE4_RB_LB_RB_LB,
      DLG_STRING_EFFECT_WIPE4_RB_LB_RB_RT,
      DLG_STRING_EFFECT_WIPE4_RB_LB_RB_RB,
      DLG_STRING_EFFECT_WIPE4_RB_RT_LT_LT,
      DLG_STRING_EFFECT_WIPE4_RB_RT_LT_LB,
      DLG_STRING_EFFECT_WIPE4_RB_RT_LT_RT,
      DLG_STRING_EFFECT_WIPE4_RB_RT_LT_RB,
      DLG_STRING_EFFECT_WIPE4_RB_RT_LB_LT,
      DLG_STRING_EFFECT_WIPE4_RB_RT_LB_LB,
      DLG_STRING_EFFECT_WIPE4_RB_RT_LB_RT,
      DLG_STRING_EFFECT_WIPE4_RB_RT_LB_RB,
      DLG_STRING_EFFECT_WIPE4_RB_RT_RT_LT,
      DLG_STRING_EFFECT_WIPE4_RB_RT_RT_LB,
      DLG_STRING_EFFECT_WIPE4_RB_RT_RT_RT,
      DLG_STRING_EFFECT_WIPE4_RB_RT_RT_RB,
      DLG_STRING_EFFECT_WIPE4_RB_RT_RB_LT,
      DLG_STRING_EFFECT_WIPE4_RB_RT_RB_LB,
      DLG_STRING_EFFECT_WIPE4_RB_RT_RB_RT,
      DLG_STRING_EFFECT_WIPE4_RB_RT_RB_RB,
      DLG_STRING_EFFECT_WIPE4_RB_RB_LT_LT,
      DLG_STRING_EFFECT_WIPE4_RB_RB_LT_LB,
      DLG_STRING_EFFECT_WIPE4_RB_RB_LT_RT,
      DLG_STRING_EFFECT_WIPE4_RB_RB_LT_RB,
      DLG_STRING_EFFECT_WIPE4_RB_RB_LB_LT,
      DLG_STRING_EFFECT_WIPE4_RB_RB_LB_LB,
      DLG_STRING_EFFECT_WIPE4_RB_RB_LB_RT,
      DLG_STRING_EFFECT_WIPE4_RB_RB_LB_RB,
      DLG_STRING_EFFECT_WIPE4_RB_RB_RT_LT,
      DLG_STRING_EFFECT_WIPE4_RB_RB_RT_LB,
      DLG_STRING_EFFECT_WIPE4_RB_RB_RT_RT,
      DLG_STRING_EFFECT_WIPE4_RB_RB_RT_RB,
      DLG_STRING_EFFECT_WIPE4_RB_RB_RB_LT,
      DLG_STRING_EFFECT_WIPE4_RB_RB_RB_LB,
      DLG_STRING_EFFECT_WIPE4_RB_RB_RB_RT,
      DLG_STRING_EFFECT_WIPE4_RB_RB_RB_RB,

      DLG_STRING_EFFECT_WIPE_RECTANGLE_IN,
      DLG_STRING_EFFECT_WIPE_RECTANGLE_OUT,
      DLG_STRING_EFFECT_WIPE_RECTANGLE_INTER_IN_THEN_IN,
      DLG_STRING_EFFECT_WIPE_RECTANGLE_INTER_OUT_THEN_OUT,
      DLG_STRING_EFFECT_WIPE_RECTANGLE_INTER_IN_THEN_OUT,
      DLG_STRING_EFFECT_WIPE_RECTANGLE_INTER_OUT_THEN_IN,

      DLG_STRING_EFFECT_WIPE_CIRCLE_C_CW_FROM_L,
      DLG_STRING_EFFECT_WIPE_CIRCLE_C_CCW_FROM_L,
      DLG_STRING_EFFECT_WIPE_CIRCLE_C_CW_FROM_R,
      DLG_STRING_EFFECT_WIPE_CIRCLE_C_CCW_FROM_R,
      DLG_STRING_EFFECT_WIPE_CIRCLE_C_CW_FROM_T,
      DLG_STRING_EFFECT_WIPE_CIRCLE_C_CCW_FROM_T,
      DLG_STRING_EFFECT_WIPE_CIRCLE_C_CW_FROM_B,
      DLG_STRING_EFFECT_WIPE_CIRCLE_C_CCW_FROM_B,
      DLG_STRING_EFFECT_WIPE_CIRCLE_L_CCW_FROM_B,
      DLG_STRING_EFFECT_WIPE_CIRCLE_L_CW_FROM_T,
      DLG_STRING_EFFECT_WIPE_CIRCLE_R_CW_FROM_B,
      DLG_STRING_EFFECT_WIPE_CIRCLE_R_CCW_FROM_T,
      DLG_STRING_EFFECT_WIPE_CIRCLE_T_CCW_FROM_L,
      DLG_STRING_EFFECT_WIPE_CIRCLE_T_CW_FROM_R,
      DLG_STRING_EFFECT_WIPE_CIRCLE_B_CW_FROM_L,
      DLG_STRING_EFFECT_WIPE_CIRCLE_B_CCW_FROM_R,
      DLG_STRING_EFFECT_WIPE_CIRCLE2_C_CW_FROM_L_AND_FROM_R,
      DLG_STRING_EFFECT_WIPE_CIRCLE2_C_CCW_FROM_L_AND_FROM_R,
      DLG_STRING_EFFECT_WIPE_CIRCLE2_C_CW_FROM_T_AND_FROM_B,
      DLG_STRING_EFFECT_WIPE_CIRCLE2_C_CCW_FROM_T_AND_FROM_B,
      DLG_STRING_EFFECT_WIPE_CIRCLE2_L_CW_FROM_T_AND_CCW_FROM_B,
      DLG_STRING_EFFECT_WIPE_CIRCLE2_L_CCW_TO_T_AND_CW_TO_B,
      DLG_STRING_EFFECT_WIPE_CIRCLE2_R_CCW_FROM_T_AND_CW_FROM_B,
      DLG_STRING_EFFECT_WIPE_CIRCLE2_R_CW_TO_T_AND_CCW_TO_B,
      DLG_STRING_EFFECT_WIPE_CIRCLE2_T_CCW_FROM_L_AND_CW_FROM_R,
      DLG_STRING_EFFECT_WIPE_CIRCLE2_T_CW_TO_L_AND_CCW_TO_R,
      DLG_STRING_EFFECT_WIPE_CIRCLE2_B_CW_FROM_L_AND_CCW_FROM_R,
      DLG_STRING_EFFECT_WIPE_CIRCLE2_B_CCW_TO_L_AND_CW_TO_R,
      DLG_STRING_EFFECT_WIPE_CIRCLE4_C_CW_CCW_CCW_CW,
      DLG_STRING_EFFECT_WIPE_CIRCLE4_C_CCW_CW_CW_CCW,
      DLG_STRINGS4_MAX,
   }DlgStrings4;

   typedef enum
   {
      DLG_STRING_EFFECT_PUSH_R_TO_L=DLG_STRINGS4_MAX,
      DLG_STRING_EFFECT_PUSH_L_TO_R,
      DLG_STRING_EFFECT_PUSH_B_TO_T,
      DLG_STRING_EFFECT_PUSH_T_TO_B,
      DLG_STRING_EFFECT_PUSH2_T_R_TO_L_AND_B_L_TO_R,
      DLG_STRING_EFFECT_PUSH2_T_L_TO_R_AND_B_R_TO_L,
      DLG_STRING_EFFECT_PUSH2_L_B_TO_T_AND_R_T_TO_B,
      DLG_STRING_EFFECT_PUSH2_L_T_TO_B_AND_R_B_TO_T,
      DLG_STRING_EFFECT_PUSH4_L_L_L_L,
      DLG_STRING_EFFECT_PUSH4_L_L_L_R,
      DLG_STRING_EFFECT_PUSH4_L_L_L_T,
      DLG_STRING_EFFECT_PUSH4_L_L_L_B,
      DLG_STRING_EFFECT_PUSH4_L_L_R_L,
      DLG_STRING_EFFECT_PUSH4_L_L_R_R,
      DLG_STRING_EFFECT_PUSH4_L_L_R_T,
      DLG_STRING_EFFECT_PUSH4_L_L_R_B,
      DLG_STRING_EFFECT_PUSH4_L_L_T_L,
      DLG_STRING_EFFECT_PUSH4_L_L_T_R,
      DLG_STRING_EFFECT_PUSH4_L_L_T_T,
      DLG_STRING_EFFECT_PUSH4_L_L_T_B,
      DLG_STRING_EFFECT_PUSH4_L_L_B_L,
      DLG_STRING_EFFECT_PUSH4_L_L_B_R,
      DLG_STRING_EFFECT_PUSH4_L_L_B_T,
      DLG_STRING_EFFECT_PUSH4_L_L_B_B,
      DLG_STRING_EFFECT_PUSH4_L_R_L_L,
      DLG_STRING_EFFECT_PUSH4_L_R_L_R,
      DLG_STRING_EFFECT_PUSH4_L_R_L_T,
      DLG_STRING_EFFECT_PUSH4_L_R_L_B,
      DLG_STRING_EFFECT_PUSH4_L_R_R_L,
      DLG_STRING_EFFECT_PUSH4_L_R_R_R,
      DLG_STRING_EFFECT_PUSH4_L_R_R_T,
      DLG_STRING_EFFECT_PUSH4_L_R_R_B,
      DLG_STRING_EFFECT_PUSH4_L_R_T_L,
      DLG_STRING_EFFECT_PUSH4_L_R_T_R,
      DLG_STRING_EFFECT_PUSH4_L_R_T_T,
      DLG_STRING_EFFECT_PUSH4_L_R_T_B,
      DLG_STRING_EFFECT_PUSH4_L_R_B_L,
      DLG_STRING_EFFECT_PUSH4_L_R_B_R,
      DLG_STRING_EFFECT_PUSH4_L_R_B_T,
      DLG_STRING_EFFECT_PUSH4_L_R_B_B,
      DLG_STRING_EFFECT_PUSH4_L_T_L_L,
      DLG_STRING_EFFECT_PUSH4_L_T_L_R,
      DLG_STRING_EFFECT_PUSH4_L_T_L_T,
      DLG_STRING_EFFECT_PUSH4_L_T_L_B,
      DLG_STRING_EFFECT_PUSH4_L_T_R_L,
      DLG_STRING_EFFECT_PUSH4_L_T_R_R,
      DLG_STRING_EFFECT_PUSH4_L_T_R_T,
      DLG_STRING_EFFECT_PUSH4_L_T_R_B,
      DLG_STRING_EFFECT_PUSH4_L_T_T_L,
      DLG_STRING_EFFECT_PUSH4_L_T_T_R,
      DLG_STRING_EFFECT_PUSH4_L_T_T_T,
      DLG_STRING_EFFECT_PUSH4_L_T_T_B,
      DLG_STRING_EFFECT_PUSH4_L_T_B_L,
      DLG_STRING_EFFECT_PUSH4_L_T_B_R,
      DLG_STRING_EFFECT_PUSH4_L_T_B_T,
      DLG_STRING_EFFECT_PUSH4_L_T_B_B,
      DLG_STRING_EFFECT_PUSH4_L_B_L_L,
      DLG_STRING_EFFECT_PUSH4_L_B_L_R,
      DLG_STRING_EFFECT_PUSH4_L_B_L_T,
      DLG_STRING_EFFECT_PUSH4_L_B_L_B,
      DLG_STRING_EFFECT_PUSH4_L_B_R_L,
      DLG_STRING_EFFECT_PUSH4_L_B_R_R,
      DLG_STRING_EFFECT_PUSH4_L_B_R_T,
      DLG_STRING_EFFECT_PUSH4_L_B_R_B,
      DLG_STRING_EFFECT_PUSH4_L_B_T_L,
      DLG_STRING_EFFECT_PUSH4_L_B_T_R,
      DLG_STRING_EFFECT_PUSH4_L_B_T_T,
      DLG_STRING_EFFECT_PUSH4_L_B_T_B,
      DLG_STRING_EFFECT_PUSH4_L_B_B_L,
      DLG_STRING_EFFECT_PUSH4_L_B_B_R,
      DLG_STRING_EFFECT_PUSH4_L_B_B_T,
      DLG_STRING_EFFECT_PUSH4_L_B_B_B,
      DLG_STRING_EFFECT_PUSH4_R_L_L_L,
      DLG_STRING_EFFECT_PUSH4_R_L_L_R,
      DLG_STRING_EFFECT_PUSH4_R_L_L_T,
      DLG_STRING_EFFECT_PUSH4_R_L_L_B,
      DLG_STRING_EFFECT_PUSH4_R_L_R_L,
      DLG_STRING_EFFECT_PUSH4_R_L_R_R,
      DLG_STRING_EFFECT_PUSH4_R_L_R_T,
      DLG_STRING_EFFECT_PUSH4_R_L_R_B,
      DLG_STRING_EFFECT_PUSH4_R_L_T_L,
      DLG_STRING_EFFECT_PUSH4_R_L_T_R,
      DLG_STRING_EFFECT_PUSH4_R_L_T_T,
      DLG_STRING_EFFECT_PUSH4_R_L_T_B,
      DLG_STRING_EFFECT_PUSH4_R_L_B_L,
      DLG_STRING_EFFECT_PUSH4_R_L_B_R,
      DLG_STRING_EFFECT_PUSH4_R_L_B_T,
      DLG_STRING_EFFECT_PUSH4_R_L_B_B,
      DLG_STRING_EFFECT_PUSH4_R_R_L_L,
      DLG_STRING_EFFECT_PUSH4_R_R_L_R,
      DLG_STRING_EFFECT_PUSH4_R_R_L_T,
      DLG_STRING_EFFECT_PUSH4_R_R_L_B,
      DLG_STRING_EFFECT_PUSH4_R_R_R_L,
      DLG_STRING_EFFECT_PUSH4_R_R_R_R,
      DLG_STRING_EFFECT_PUSH4_R_R_R_T,
      DLG_STRING_EFFECT_PUSH4_R_R_R_B,
      DLG_STRING_EFFECT_PUSH4_R_R_T_L,
      DLG_STRING_EFFECT_PUSH4_R_R_T_R,
      DLG_STRING_EFFECT_PUSH4_R_R_T_T,
      DLG_STRING_EFFECT_PUSH4_R_R_T_B,
      DLG_STRING_EFFECT_PUSH4_R_R_B_L,
      DLG_STRING_EFFECT_PUSH4_R_R_B_R,
      DLG_STRING_EFFECT_PUSH4_R_R_B_T,
      DLG_STRING_EFFECT_PUSH4_R_R_B_B,
      DLG_STRING_EFFECT_PUSH4_R_T_L_L,
      DLG_STRING_EFFECT_PUSH4_R_T_L_R,
      DLG_STRING_EFFECT_PUSH4_R_T_L_T,
      DLG_STRING_EFFECT_PUSH4_R_T_L_B,
      DLG_STRING_EFFECT_PUSH4_R_T_R_L,
      DLG_STRING_EFFECT_PUSH4_R_T_R_R,
      DLG_STRING_EFFECT_PUSH4_R_T_R_T,
      DLG_STRING_EFFECT_PUSH4_R_T_R_B,
      DLG_STRING_EFFECT_PUSH4_R_T_T_L,
      DLG_STRING_EFFECT_PUSH4_R_T_T_R,
      DLG_STRING_EFFECT_PUSH4_R_T_T_T,
      DLG_STRING_EFFECT_PUSH4_R_T_T_B,
      DLG_STRING_EFFECT_PUSH4_R_T_B_L,
      DLG_STRING_EFFECT_PUSH4_R_T_B_R,
      DLG_STRING_EFFECT_PUSH4_R_T_B_T,
      DLG_STRING_EFFECT_PUSH4_R_T_B_B,
      DLG_STRING_EFFECT_PUSH4_R_B_L_L,
      DLG_STRING_EFFECT_PUSH4_R_B_L_R,
      DLG_STRING_EFFECT_PUSH4_R_B_L_T,
      DLG_STRING_EFFECT_PUSH4_R_B_L_B,
      DLG_STRING_EFFECT_PUSH4_R_B_R_L,
      DLG_STRING_EFFECT_PUSH4_R_B_R_R,
      DLG_STRING_EFFECT_PUSH4_R_B_R_T,
      DLG_STRING_EFFECT_PUSH4_R_B_R_B,
      DLG_STRING_EFFECT_PUSH4_R_B_T_L,
      DLG_STRING_EFFECT_PUSH4_R_B_T_R,
      DLG_STRING_EFFECT_PUSH4_R_B_T_T,
      DLG_STRING_EFFECT_PUSH4_R_B_T_B,
      DLG_STRING_EFFECT_PUSH4_R_B_B_L,
      DLG_STRING_EFFECT_PUSH4_R_B_B_R,
      DLG_STRING_EFFECT_PUSH4_R_B_B_T,
      DLG_STRING_EFFECT_PUSH4_R_B_B_B,
      DLG_STRING_EFFECT_PUSH4_T_L_L_L,
      DLG_STRING_EFFECT_PUSH4_T_L_L_R,
      DLG_STRING_EFFECT_PUSH4_T_L_L_T,
      DLG_STRING_EFFECT_PUSH4_T_L_L_B,
      DLG_STRING_EFFECT_PUSH4_T_L_R_L,
      DLG_STRING_EFFECT_PUSH4_T_L_R_R,
      DLG_STRING_EFFECT_PUSH4_T_L_R_T,
      DLG_STRING_EFFECT_PUSH4_T_L_R_B,
      DLG_STRING_EFFECT_PUSH4_T_L_T_L,
      DLG_STRING_EFFECT_PUSH4_T_L_T_R,
      DLG_STRING_EFFECT_PUSH4_T_L_T_T,
      DLG_STRING_EFFECT_PUSH4_T_L_T_B,
      DLG_STRING_EFFECT_PUSH4_T_L_B_L,
      DLG_STRING_EFFECT_PUSH4_T_L_B_R,
      DLG_STRING_EFFECT_PUSH4_T_L_B_T,
      DLG_STRING_EFFECT_PUSH4_T_L_B_B,
      DLG_STRING_EFFECT_PUSH4_T_R_L_L,
      DLG_STRING_EFFECT_PUSH4_T_R_L_R,
      DLG_STRING_EFFECT_PUSH4_T_R_L_T,
      DLG_STRING_EFFECT_PUSH4_T_R_L_B,
      DLG_STRING_EFFECT_PUSH4_T_R_R_L,
      DLG_STRING_EFFECT_PUSH4_T_R_R_R,
      DLG_STRING_EFFECT_PUSH4_T_R_R_T,
      DLG_STRING_EFFECT_PUSH4_T_R_R_B,
      DLG_STRING_EFFECT_PUSH4_T_R_T_L,
      DLG_STRING_EFFECT_PUSH4_T_R_T_R,
      DLG_STRING_EFFECT_PUSH4_T_R_T_T,
      DLG_STRING_EFFECT_PUSH4_T_R_T_B,
      DLG_STRING_EFFECT_PUSH4_T_R_B_L,
      DLG_STRING_EFFECT_PUSH4_T_R_B_R,
      DLG_STRING_EFFECT_PUSH4_T_R_B_T,
      DLG_STRING_EFFECT_PUSH4_T_R_B_B,
      DLG_STRING_EFFECT_PUSH4_T_T_L_L,
      DLG_STRING_EFFECT_PUSH4_T_T_L_R,
      DLG_STRING_EFFECT_PUSH4_T_T_L_T,
      DLG_STRING_EFFECT_PUSH4_T_T_L_B,
      DLG_STRING_EFFECT_PUSH4_T_T_R_L,
      DLG_STRING_EFFECT_PUSH4_T_T_R_R,
      DLG_STRING_EFFECT_PUSH4_T_T_R_T,
      DLG_STRING_EFFECT_PUSH4_T_T_R_B,
      DLG_STRING_EFFECT_PUSH4_T_T_T_L,
      DLG_STRING_EFFECT_PUSH4_T_T_T_R,
      DLG_STRING_EFFECT_PUSH4_T_T_T_T,
      DLG_STRING_EFFECT_PUSH4_T_T_T_B,
      DLG_STRING_EFFECT_PUSH4_T_T_B_L,
      DLG_STRING_EFFECT_PUSH4_T_T_B_R,
      DLG_STRING_EFFECT_PUSH4_T_T_B_T,
      DLG_STRING_EFFECT_PUSH4_T_T_B_B,
      DLG_STRING_EFFECT_PUSH4_T_B_L_L,
      DLG_STRING_EFFECT_PUSH4_T_B_L_R,
      DLG_STRING_EFFECT_PUSH4_T_B_L_T,
      DLG_STRING_EFFECT_PUSH4_T_B_L_B,
      DLG_STRING_EFFECT_PUSH4_T_B_R_L,
      DLG_STRING_EFFECT_PUSH4_T_B_R_R,
      DLG_STRING_EFFECT_PUSH4_T_B_R_T,
      DLG_STRING_EFFECT_PUSH4_T_B_R_B,
      DLG_STRING_EFFECT_PUSH4_T_B_T_L,
      DLG_STRING_EFFECT_PUSH4_T_B_T_R,
      DLG_STRING_EFFECT_PUSH4_T_B_T_T,
      DLG_STRING_EFFECT_PUSH4_T_B_T_B,
      DLG_STRING_EFFECT_PUSH4_T_B_B_L,
      DLG_STRING_EFFECT_PUSH4_T_B_B_R,
      DLG_STRING_EFFECT_PUSH4_T_B_B_T,
      DLG_STRING_EFFECT_PUSH4_T_B_B_B,
      DLG_STRING_EFFECT_PUSH4_B_L_L_L,
      DLG_STRING_EFFECT_PUSH4_B_L_L_R,
      DLG_STRING_EFFECT_PUSH4_B_L_L_T,
      DLG_STRING_EFFECT_PUSH4_B_L_L_B,
      DLG_STRING_EFFECT_PUSH4_B_L_R_L,
      DLG_STRING_EFFECT_PUSH4_B_L_R_R,
      DLG_STRING_EFFECT_PUSH4_B_L_R_T,
      DLG_STRING_EFFECT_PUSH4_B_L_R_B,
      DLG_STRING_EFFECT_PUSH4_B_L_T_L,
      DLG_STRING_EFFECT_PUSH4_B_L_T_R,
      DLG_STRING_EFFECT_PUSH4_B_L_T_T,
      DLG_STRING_EFFECT_PUSH4_B_L_T_B,
      DLG_STRING_EFFECT_PUSH4_B_L_B_L,
      DLG_STRING_EFFECT_PUSH4_B_L_B_R,
      DLG_STRING_EFFECT_PUSH4_B_L_B_T,
      DLG_STRING_EFFECT_PUSH4_B_L_B_B,
      DLG_STRING_EFFECT_PUSH4_B_R_L_L,
      DLG_STRING_EFFECT_PUSH4_B_R_L_R,
      DLG_STRING_EFFECT_PUSH4_B_R_L_T,
      DLG_STRING_EFFECT_PUSH4_B_R_L_B,
      DLG_STRING_EFFECT_PUSH4_B_R_R_L,
      DLG_STRING_EFFECT_PUSH4_B_R_R_R,
      DLG_STRING_EFFECT_PUSH4_B_R_R_T,
      DLG_STRING_EFFECT_PUSH4_B_R_R_B,
      DLG_STRING_EFFECT_PUSH4_B_R_T_L,
      DLG_STRING_EFFECT_PUSH4_B_R_T_R,
      DLG_STRING_EFFECT_PUSH4_B_R_T_T,
      DLG_STRING_EFFECT_PUSH4_B_R_T_B,
      DLG_STRING_EFFECT_PUSH4_B_R_B_L,
      DLG_STRING_EFFECT_PUSH4_B_R_B_R,
      DLG_STRING_EFFECT_PUSH4_B_R_B_T,
      DLG_STRING_EFFECT_PUSH4_B_R_B_B,
      DLG_STRING_EFFECT_PUSH4_B_T_L_L,
      DLG_STRING_EFFECT_PUSH4_B_T_L_R,
      DLG_STRING_EFFECT_PUSH4_B_T_L_T,
      DLG_STRING_EFFECT_PUSH4_B_T_L_B,
      DLG_STRING_EFFECT_PUSH4_B_T_R_L,
      DLG_STRING_EFFECT_PUSH4_B_T_R_R,
      DLG_STRING_EFFECT_PUSH4_B_T_R_T,
      DLG_STRING_EFFECT_PUSH4_B_T_R_B,
      DLG_STRING_EFFECT_PUSH4_B_T_T_L,
      DLG_STRING_EFFECT_PUSH4_B_T_T_R,
      DLG_STRING_EFFECT_PUSH4_B_T_T_T,
      DLG_STRING_EFFECT_PUSH4_B_T_T_B,
      DLG_STRING_EFFECT_PUSH4_B_T_B_L,
      DLG_STRING_EFFECT_PUSH4_B_T_B_R,
      DLG_STRING_EFFECT_PUSH4_B_T_B_T,
      DLG_STRING_EFFECT_PUSH4_B_T_B_B,
      DLG_STRING_EFFECT_PUSH4_B_B_L_L,
      DLG_STRING_EFFECT_PUSH4_B_B_L_R,
      DLG_STRING_EFFECT_PUSH4_B_B_L_T,
      DLG_STRING_EFFECT_PUSH4_B_B_L_B,
      DLG_STRING_EFFECT_PUSH4_B_B_R_L,
      DLG_STRING_EFFECT_PUSH4_B_B_R_R,
      DLG_STRING_EFFECT_PUSH4_B_B_R_T,
      DLG_STRING_EFFECT_PUSH4_B_B_R_B,
      DLG_STRING_EFFECT_PUSH4_B_B_T_L,
      DLG_STRING_EFFECT_PUSH4_B_B_T_R,
      DLG_STRING_EFFECT_PUSH4_B_B_T_T,
      DLG_STRING_EFFECT_PUSH4_B_B_T_B,
      DLG_STRING_EFFECT_PUSH4_B_B_B_L,
      DLG_STRING_EFFECT_PUSH4_B_B_B_R,
      DLG_STRING_EFFECT_PUSH4_B_B_B_T,
      DLG_STRING_EFFECT_PUSH4_B_B_B_B,

      DLG_STRING_EFFECT_SLIDE_R_TO_L,
      DLG_STRING_EFFECT_SLIDE_L_TO_R,
      DLG_STRING_EFFECT_SLIDE_B_TO_T,
      DLG_STRING_EFFECT_SLIDE_T_TO_B,
      DLG_STRING_EFFECT_SLIDE_LT_TO_RB,
      DLG_STRING_EFFECT_SLIDE_RT_TO_LB,
      DLG_STRING_EFFECT_SLIDE_LB_TO_RT,
      DLG_STRING_EFFECT_SLIDE_RB_TO_LT,
      DLG_STRING_EFFECT_SLIDE_INTERH_L_TO_R_AND_R_TO_L,
      DLG_STRING_EFFECT_SLIDE_INTERV_T_TO_B_AND_B_TO_T,
      DLG_STRING_EFFECT_SLIDE2_T_R_TO_L_AND_B_L_TO_R,
      DLG_STRING_EFFECT_SLIDE2_T_L_TO_R_AND_B_R_TO_L,
      DLG_STRING_EFFECT_SLIDE2_L_B_TO_T_AND_R_T_TO_B,
      DLG_STRING_EFFECT_SLIDE2_L_T_TO_B_AND_R_B_TO_T,
      DLG_STRING_EFFECT_SLIDE4_L_L_L_L,
      DLG_STRING_EFFECT_SLIDE4_L_L_L_R,
      DLG_STRING_EFFECT_SLIDE4_L_L_L_T,
      DLG_STRING_EFFECT_SLIDE4_L_L_L_B,
      DLG_STRING_EFFECT_SLIDE4_L_L_R_L,
      DLG_STRING_EFFECT_SLIDE4_L_L_R_R,
      DLG_STRING_EFFECT_SLIDE4_L_L_R_T,
      DLG_STRING_EFFECT_SLIDE4_L_L_R_B,
      DLG_STRING_EFFECT_SLIDE4_L_L_T_L,
      DLG_STRING_EFFECT_SLIDE4_L_L_T_R,
      DLG_STRING_EFFECT_SLIDE4_L_L_T_T,
      DLG_STRING_EFFECT_SLIDE4_L_L_T_B,
      DLG_STRING_EFFECT_SLIDE4_L_L_B_L,
      DLG_STRING_EFFECT_SLIDE4_L_L_B_R,
      DLG_STRING_EFFECT_SLIDE4_L_L_B_T,
      DLG_STRING_EFFECT_SLIDE4_L_L_B_B,
      DLG_STRING_EFFECT_SLIDE4_L_R_L_L,
      DLG_STRING_EFFECT_SLIDE4_L_R_L_R,
      DLG_STRING_EFFECT_SLIDE4_L_R_L_T,
      DLG_STRING_EFFECT_SLIDE4_L_R_L_B,
      DLG_STRING_EFFECT_SLIDE4_L_R_R_L,
      DLG_STRING_EFFECT_SLIDE4_L_R_R_R,
      DLG_STRING_EFFECT_SLIDE4_L_R_R_T,
      DLG_STRING_EFFECT_SLIDE4_L_R_R_B,
      DLG_STRING_EFFECT_SLIDE4_L_R_T_L,
      DLG_STRING_EFFECT_SLIDE4_L_R_T_R,
      DLG_STRING_EFFECT_SLIDE4_L_R_T_T,
      DLG_STRING_EFFECT_SLIDE4_L_R_T_B,
      DLG_STRING_EFFECT_SLIDE4_L_R_B_L,
      DLG_STRING_EFFECT_SLIDE4_L_R_B_R,
      DLG_STRING_EFFECT_SLIDE4_L_R_B_T,
      DLG_STRING_EFFECT_SLIDE4_L_R_B_B,
      DLG_STRING_EFFECT_SLIDE4_L_T_L_L,
      DLG_STRING_EFFECT_SLIDE4_L_T_L_R,
      DLG_STRING_EFFECT_SLIDE4_L_T_L_T,
      DLG_STRING_EFFECT_SLIDE4_L_T_L_B,
      DLG_STRING_EFFECT_SLIDE4_L_T_R_L,
      DLG_STRING_EFFECT_SLIDE4_L_T_R_R,
      DLG_STRING_EFFECT_SLIDE4_L_T_R_T,
      DLG_STRING_EFFECT_SLIDE4_L_T_R_B,
      DLG_STRING_EFFECT_SLIDE4_L_T_T_L,
      DLG_STRING_EFFECT_SLIDE4_L_T_T_R,
      DLG_STRING_EFFECT_SLIDE4_L_T_T_T,
      DLG_STRING_EFFECT_SLIDE4_L_T_T_B,
      DLG_STRING_EFFECT_SLIDE4_L_T_B_L,
      DLG_STRING_EFFECT_SLIDE4_L_T_B_R,
      DLG_STRING_EFFECT_SLIDE4_L_T_B_T,
      DLG_STRING_EFFECT_SLIDE4_L_T_B_B,
      DLG_STRING_EFFECT_SLIDE4_L_B_L_L,
      DLG_STRING_EFFECT_SLIDE4_L_B_L_R,
      DLG_STRING_EFFECT_SLIDE4_L_B_L_T,
      DLG_STRING_EFFECT_SLIDE4_L_B_L_B,
      DLG_STRING_EFFECT_SLIDE4_L_B_R_L,
      DLG_STRING_EFFECT_SLIDE4_L_B_R_R,
      DLG_STRING_EFFECT_SLIDE4_L_B_R_T,
      DLG_STRING_EFFECT_SLIDE4_L_B_R_B,
      DLG_STRING_EFFECT_SLIDE4_L_B_T_L,
      DLG_STRING_EFFECT_SLIDE4_L_B_T_R,
      DLG_STRING_EFFECT_SLIDE4_L_B_T_T,
      DLG_STRING_EFFECT_SLIDE4_L_B_T_B,
      DLG_STRING_EFFECT_SLIDE4_L_B_B_L,
      DLG_STRING_EFFECT_SLIDE4_L_B_B_R,
      DLG_STRING_EFFECT_SLIDE4_L_B_B_T,
      DLG_STRING_EFFECT_SLIDE4_L_B_B_B,
      DLG_STRING_EFFECT_SLIDE4_R_L_L_L,
      DLG_STRING_EFFECT_SLIDE4_R_L_L_R,
      DLG_STRING_EFFECT_SLIDE4_R_L_L_T,
      DLG_STRING_EFFECT_SLIDE4_R_L_L_B,
      DLG_STRING_EFFECT_SLIDE4_R_L_R_L,
      DLG_STRING_EFFECT_SLIDE4_R_L_R_R,
      DLG_STRING_EFFECT_SLIDE4_R_L_R_T,
      DLG_STRING_EFFECT_SLIDE4_R_L_R_B,
      DLG_STRING_EFFECT_SLIDE4_R_L_T_L,
      DLG_STRING_EFFECT_SLIDE4_R_L_T_R,
      DLG_STRING_EFFECT_SLIDE4_R_L_T_T,
      DLG_STRING_EFFECT_SLIDE4_R_L_T_B,
      DLG_STRING_EFFECT_SLIDE4_R_L_B_L,
      DLG_STRING_EFFECT_SLIDE4_R_L_B_R,
      DLG_STRING_EFFECT_SLIDE4_R_L_B_T,
      DLG_STRING_EFFECT_SLIDE4_R_L_B_B,
      DLG_STRING_EFFECT_SLIDE4_R_R_L_L,
      DLG_STRING_EFFECT_SLIDE4_R_R_L_R,
      DLG_STRING_EFFECT_SLIDE4_R_R_L_T,
      DLG_STRING_EFFECT_SLIDE4_R_R_L_B,
      DLG_STRING_EFFECT_SLIDE4_R_R_R_L,
      DLG_STRING_EFFECT_SLIDE4_R_R_R_R,
      DLG_STRING_EFFECT_SLIDE4_R_R_R_T,
      DLG_STRING_EFFECT_SLIDE4_R_R_R_B,
      DLG_STRING_EFFECT_SLIDE4_R_R_T_L,
      DLG_STRING_EFFECT_SLIDE4_R_R_T_R,
      DLG_STRING_EFFECT_SLIDE4_R_R_T_T,
      DLG_STRING_EFFECT_SLIDE4_R_R_T_B,
      DLG_STRING_EFFECT_SLIDE4_R_R_B_L,
      DLG_STRING_EFFECT_SLIDE4_R_R_B_R,
      DLG_STRING_EFFECT_SLIDE4_R_R_B_T,
      DLG_STRING_EFFECT_SLIDE4_R_R_B_B,
      DLG_STRING_EFFECT_SLIDE4_R_T_L_L,
      DLG_STRING_EFFECT_SLIDE4_R_T_L_R,
      DLG_STRING_EFFECT_SLIDE4_R_T_L_T,
      DLG_STRING_EFFECT_SLIDE4_R_T_L_B,
      DLG_STRING_EFFECT_SLIDE4_R_T_R_L,
      DLG_STRING_EFFECT_SLIDE4_R_T_R_R,
      DLG_STRING_EFFECT_SLIDE4_R_T_R_T,
      DLG_STRING_EFFECT_SLIDE4_R_T_R_B,
      DLG_STRING_EFFECT_SLIDE4_R_T_T_L,
      DLG_STRING_EFFECT_SLIDE4_R_T_T_R,
      DLG_STRING_EFFECT_SLIDE4_R_T_T_T,
      DLG_STRING_EFFECT_SLIDE4_R_T_T_B,
      DLG_STRING_EFFECT_SLIDE4_R_T_B_L,
      DLG_STRING_EFFECT_SLIDE4_R_T_B_R,
      DLG_STRING_EFFECT_SLIDE4_R_T_B_T,
      DLG_STRING_EFFECT_SLIDE4_R_T_B_B,
      DLG_STRING_EFFECT_SLIDE4_R_B_L_L,
      DLG_STRING_EFFECT_SLIDE4_R_B_L_R,
      DLG_STRING_EFFECT_SLIDE4_R_B_L_T,
      DLG_STRING_EFFECT_SLIDE4_R_B_L_B,
      DLG_STRING_EFFECT_SLIDE4_R_B_R_L,
      DLG_STRING_EFFECT_SLIDE4_R_B_R_R,
      DLG_STRING_EFFECT_SLIDE4_R_B_R_T,
      DLG_STRING_EFFECT_SLIDE4_R_B_R_B,
      DLG_STRING_EFFECT_SLIDE4_R_B_T_L,
      DLG_STRING_EFFECT_SLIDE4_R_B_T_R,
      DLG_STRING_EFFECT_SLIDE4_R_B_T_T,
      DLG_STRING_EFFECT_SLIDE4_R_B_T_B,
      DLG_STRING_EFFECT_SLIDE4_R_B_B_L,
      DLG_STRING_EFFECT_SLIDE4_R_B_B_R,
      DLG_STRING_EFFECT_SLIDE4_R_B_B_T,
      DLG_STRING_EFFECT_SLIDE4_R_B_B_B,
      DLG_STRING_EFFECT_SLIDE4_T_L_L_L,
      DLG_STRING_EFFECT_SLIDE4_T_L_L_R,
      DLG_STRING_EFFECT_SLIDE4_T_L_L_T,
      DLG_STRING_EFFECT_SLIDE4_T_L_L_B,
      DLG_STRING_EFFECT_SLIDE4_T_L_R_L,
      DLG_STRING_EFFECT_SLIDE4_T_L_R_R,
      DLG_STRING_EFFECT_SLIDE4_T_L_R_T,
      DLG_STRING_EFFECT_SLIDE4_T_L_R_B,
      DLG_STRING_EFFECT_SLIDE4_T_L_T_L,
      DLG_STRING_EFFECT_SLIDE4_T_L_T_R,
      DLG_STRING_EFFECT_SLIDE4_T_L_T_T,
      DLG_STRING_EFFECT_SLIDE4_T_L_T_B,
      DLG_STRING_EFFECT_SLIDE4_T_L_B_L,
      DLG_STRING_EFFECT_SLIDE4_T_L_B_R,
      DLG_STRING_EFFECT_SLIDE4_T_L_B_T,
      DLG_STRING_EFFECT_SLIDE4_T_L_B_B,
      DLG_STRING_EFFECT_SLIDE4_T_R_L_L,
      DLG_STRING_EFFECT_SLIDE4_T_R_L_R,
      DLG_STRING_EFFECT_SLIDE4_T_R_L_T,
      DLG_STRING_EFFECT_SLIDE4_T_R_L_B,
      DLG_STRING_EFFECT_SLIDE4_T_R_R_L,
      DLG_STRING_EFFECT_SLIDE4_T_R_R_R,
      DLG_STRING_EFFECT_SLIDE4_T_R_R_T,
      DLG_STRING_EFFECT_SLIDE4_T_R_R_B,
      DLG_STRING_EFFECT_SLIDE4_T_R_T_L,
      DLG_STRING_EFFECT_SLIDE4_T_R_T_R,
      DLG_STRING_EFFECT_SLIDE4_T_R_T_T,
      DLG_STRING_EFFECT_SLIDE4_T_R_T_B,
      DLG_STRING_EFFECT_SLIDE4_T_R_B_L,
      DLG_STRING_EFFECT_SLIDE4_T_R_B_R,
      DLG_STRING_EFFECT_SLIDE4_T_R_B_T,
      DLG_STRING_EFFECT_SLIDE4_T_R_B_B,
      DLG_STRING_EFFECT_SLIDE4_T_T_L_L,
      DLG_STRING_EFFECT_SLIDE4_T_T_L_R,
      DLG_STRING_EFFECT_SLIDE4_T_T_L_T,
      DLG_STRING_EFFECT_SLIDE4_T_T_L_B,
      DLG_STRING_EFFECT_SLIDE4_T_T_R_L,
      DLG_STRING_EFFECT_SLIDE4_T_T_R_R,
      DLG_STRING_EFFECT_SLIDE4_T_T_R_T,
      DLG_STRING_EFFECT_SLIDE4_T_T_R_B,
      DLG_STRING_EFFECT_SLIDE4_T_T_T_L,
      DLG_STRING_EFFECT_SLIDE4_T_T_T_R,
      DLG_STRING_EFFECT_SLIDE4_T_T_T_T,
      DLG_STRING_EFFECT_SLIDE4_T_T_T_B,
      DLG_STRING_EFFECT_SLIDE4_T_T_B_L,
      DLG_STRING_EFFECT_SLIDE4_T_T_B_R,
      DLG_STRING_EFFECT_SLIDE4_T_T_B_T,
      DLG_STRING_EFFECT_SLIDE4_T_T_B_B,
      DLG_STRING_EFFECT_SLIDE4_T_B_L_L,
      DLG_STRING_EFFECT_SLIDE4_T_B_L_R,
      DLG_STRING_EFFECT_SLIDE4_T_B_L_T,
      DLG_STRING_EFFECT_SLIDE4_T_B_L_B,
      DLG_STRING_EFFECT_SLIDE4_T_B_R_L,
      DLG_STRING_EFFECT_SLIDE4_T_B_R_R,
      DLG_STRING_EFFECT_SLIDE4_T_B_R_T,
      DLG_STRING_EFFECT_SLIDE4_T_B_R_B,
      DLG_STRING_EFFECT_SLIDE4_T_B_T_L,
      DLG_STRING_EFFECT_SLIDE4_T_B_T_R,
      DLG_STRING_EFFECT_SLIDE4_T_B_T_T,
      DLG_STRING_EFFECT_SLIDE4_T_B_T_B,
      DLG_STRING_EFFECT_SLIDE4_T_B_B_L,
      DLG_STRING_EFFECT_SLIDE4_T_B_B_R,
      DLG_STRING_EFFECT_SLIDE4_T_B_B_T,
      DLG_STRING_EFFECT_SLIDE4_T_B_B_B,
      DLG_STRING_EFFECT_SLIDE4_B_L_L_L,
      DLG_STRING_EFFECT_SLIDE4_B_L_L_R,
      DLG_STRING_EFFECT_SLIDE4_B_L_L_T,
      DLG_STRING_EFFECT_SLIDE4_B_L_L_B,
      DLG_STRING_EFFECT_SLIDE4_B_L_R_L,
      DLG_STRING_EFFECT_SLIDE4_B_L_R_R,
      DLG_STRING_EFFECT_SLIDE4_B_L_R_T,
      DLG_STRING_EFFECT_SLIDE4_B_L_R_B,
      DLG_STRING_EFFECT_SLIDE4_B_L_T_L,
      DLG_STRING_EFFECT_SLIDE4_B_L_T_R,
      DLG_STRING_EFFECT_SLIDE4_B_L_T_T,
      DLG_STRING_EFFECT_SLIDE4_B_L_T_B,
      DLG_STRING_EFFECT_SLIDE4_B_L_B_L,
      DLG_STRING_EFFECT_SLIDE4_B_L_B_R,
      DLG_STRING_EFFECT_SLIDE4_B_L_B_T,
      DLG_STRING_EFFECT_SLIDE4_B_L_B_B,
      DLG_STRING_EFFECT_SLIDE4_B_R_L_L,
      DLG_STRING_EFFECT_SLIDE4_B_R_L_R,
      DLG_STRING_EFFECT_SLIDE4_B_R_L_T,
      DLG_STRING_EFFECT_SLIDE4_B_R_L_B,
      DLG_STRING_EFFECT_SLIDE4_B_R_R_L,
      DLG_STRING_EFFECT_SLIDE4_B_R_R_R,
      DLG_STRING_EFFECT_SLIDE4_B_R_R_T,
      DLG_STRING_EFFECT_SLIDE4_B_R_R_B,
      DLG_STRING_EFFECT_SLIDE4_B_R_T_L,
      DLG_STRING_EFFECT_SLIDE4_B_R_T_R,
      DLG_STRING_EFFECT_SLIDE4_B_R_T_T,
      DLG_STRING_EFFECT_SLIDE4_B_R_T_B,
      DLG_STRING_EFFECT_SLIDE4_B_R_B_L,
      DLG_STRING_EFFECT_SLIDE4_B_R_B_R,
      DLG_STRING_EFFECT_SLIDE4_B_R_B_T,
      DLG_STRING_EFFECT_SLIDE4_B_R_B_B,
      DLG_STRING_EFFECT_SLIDE4_B_T_L_L,
      DLG_STRING_EFFECT_SLIDE4_B_T_L_R,
      DLG_STRING_EFFECT_SLIDE4_B_T_L_T,
      DLG_STRING_EFFECT_SLIDE4_B_T_L_B,
      DLG_STRING_EFFECT_SLIDE4_B_T_R_L,
      DLG_STRING_EFFECT_SLIDE4_B_T_R_R,
      DLG_STRING_EFFECT_SLIDE4_B_T_R_T,
      DLG_STRING_EFFECT_SLIDE4_B_T_R_B,
      DLG_STRING_EFFECT_SLIDE4_B_T_T_L,
      DLG_STRING_EFFECT_SLIDE4_B_T_T_R,
      DLG_STRING_EFFECT_SLIDE4_B_T_T_T,
      DLG_STRING_EFFECT_SLIDE4_B_T_T_B,
      DLG_STRING_EFFECT_SLIDE4_B_T_B_L,
      DLG_STRING_EFFECT_SLIDE4_B_T_B_R,
      DLG_STRING_EFFECT_SLIDE4_B_T_B_T,
      DLG_STRING_EFFECT_SLIDE4_B_T_B_B,
      DLG_STRING_EFFECT_SLIDE4_B_B_L_L,
      DLG_STRING_EFFECT_SLIDE4_B_B_L_R,
      DLG_STRING_EFFECT_SLIDE4_B_B_L_T,
      DLG_STRING_EFFECT_SLIDE4_B_B_L_B,
      DLG_STRING_EFFECT_SLIDE4_B_B_R_L,
      DLG_STRING_EFFECT_SLIDE4_B_B_R_R,
      DLG_STRING_EFFECT_SLIDE4_B_B_R_T,
      DLG_STRING_EFFECT_SLIDE4_B_B_R_B,
      DLG_STRING_EFFECT_SLIDE4_B_B_T_L,
      DLG_STRING_EFFECT_SLIDE4_B_B_T_R,
      DLG_STRING_EFFECT_SLIDE4_B_B_T_T,
      DLG_STRING_EFFECT_SLIDE4_B_B_T_B,
      DLG_STRING_EFFECT_SLIDE4_B_B_B_L,
      DLG_STRING_EFFECT_SLIDE4_B_B_B_R,
      DLG_STRING_EFFECT_SLIDE4_B_B_B_T,
      DLG_STRING_EFFECT_SLIDE4_B_B_B_B,
      DLG_STRING_EFFECT_SLIDE4_LT_LT_LT_LT,
      DLG_STRING_EFFECT_SLIDE4_LT_LT_LT_LB,
      DLG_STRING_EFFECT_SLIDE4_LT_LT_LT_RT,
      DLG_STRING_EFFECT_SLIDE4_LT_LT_LT_RB,
      DLG_STRING_EFFECT_SLIDE4_LT_LT_LB_LT,
      DLG_STRING_EFFECT_SLIDE4_LT_LT_LB_LB,
      DLG_STRING_EFFECT_SLIDE4_LT_LT_LB_RT,
      DLG_STRING_EFFECT_SLIDE4_LT_LT_LB_RB,
      DLG_STRING_EFFECT_SLIDE4_LT_LT_RT_LT,
      DLG_STRING_EFFECT_SLIDE4_LT_LT_RT_LB,
      DLG_STRING_EFFECT_SLIDE4_LT_LT_RT_RT,
      DLG_STRING_EFFECT_SLIDE4_LT_LT_RT_RB,
      DLG_STRING_EFFECT_SLIDE4_LT_LT_RB_LT,
      DLG_STRING_EFFECT_SLIDE4_LT_LT_RB_LB,
      DLG_STRING_EFFECT_SLIDE4_LT_LT_RB_RT,
      DLG_STRING_EFFECT_SLIDE4_LT_LT_RB_RB,
      DLG_STRING_EFFECT_SLIDE4_LT_LB_LT_LT,
      DLG_STRING_EFFECT_SLIDE4_LT_LB_LT_LB,
      DLG_STRING_EFFECT_SLIDE4_LT_LB_LT_RT,
      DLG_STRING_EFFECT_SLIDE4_LT_LB_LT_RB,
      DLG_STRING_EFFECT_SLIDE4_LT_LB_LB_LT,
      DLG_STRING_EFFECT_SLIDE4_LT_LB_LB_LB,
      DLG_STRING_EFFECT_SLIDE4_LT_LB_LB_RT,
      DLG_STRING_EFFECT_SLIDE4_LT_LB_LB_RB,
      DLG_STRING_EFFECT_SLIDE4_LT_LB_RT_LT,
      DLG_STRING_EFFECT_SLIDE4_LT_LB_RT_LB,
      DLG_STRING_EFFECT_SLIDE4_LT_LB_RT_RT,
      DLG_STRING_EFFECT_SLIDE4_LT_LB_RT_RB,
      DLG_STRING_EFFECT_SLIDE4_LT_LB_RB_LT,
      DLG_STRING_EFFECT_SLIDE4_LT_LB_RB_LB,
      DLG_STRING_EFFECT_SLIDE4_LT_LB_RB_RT,
      DLG_STRING_EFFECT_SLIDE4_LT_LB_RB_RB,
      DLG_STRING_EFFECT_SLIDE4_LT_RT_LT_LT,
      DLG_STRING_EFFECT_SLIDE4_LT_RT_LT_LB,
      DLG_STRING_EFFECT_SLIDE4_LT_RT_LT_RT,
      DLG_STRING_EFFECT_SLIDE4_LT_RT_LT_RB,
      DLG_STRING_EFFECT_SLIDE4_LT_RT_LB_LT,
      DLG_STRING_EFFECT_SLIDE4_LT_RT_LB_LB,
      DLG_STRING_EFFECT_SLIDE4_LT_RT_LB_RT,
      DLG_STRING_EFFECT_SLIDE4_LT_RT_LB_RB,
      DLG_STRING_EFFECT_SLIDE4_LT_RT_RT_LT,
      DLG_STRING_EFFECT_SLIDE4_LT_RT_RT_LB,
      DLG_STRING_EFFECT_SLIDE4_LT_RT_RT_RT,
      DLG_STRING_EFFECT_SLIDE4_LT_RT_RT_RB,
      DLG_STRING_EFFECT_SLIDE4_LT_RT_RB_LT,
      DLG_STRING_EFFECT_SLIDE4_LT_RT_RB_LB,
      DLG_STRING_EFFECT_SLIDE4_LT_RT_RB_RT,
      DLG_STRING_EFFECT_SLIDE4_LT_RT_RB_RB,
      DLG_STRING_EFFECT_SLIDE4_LT_RB_LT_LT,
      DLG_STRING_EFFECT_SLIDE4_LT_RB_LT_LB,
      DLG_STRING_EFFECT_SLIDE4_LT_RB_LT_RT,
      DLG_STRING_EFFECT_SLIDE4_LT_RB_LT_RB,
      DLG_STRING_EFFECT_SLIDE4_LT_RB_LB_LT,
      DLG_STRING_EFFECT_SLIDE4_LT_RB_LB_LB,
      DLG_STRING_EFFECT_SLIDE4_LT_RB_LB_RT,
      DLG_STRING_EFFECT_SLIDE4_LT_RB_LB_RB,
      DLG_STRING_EFFECT_SLIDE4_LT_RB_RT_LT,
      DLG_STRING_EFFECT_SLIDE4_LT_RB_RT_LB,
      DLG_STRING_EFFECT_SLIDE4_LT_RB_RT_RT,
      DLG_STRING_EFFECT_SLIDE4_LT_RB_RT_RB,
      DLG_STRING_EFFECT_SLIDE4_LT_RB_RB_LT,
      DLG_STRING_EFFECT_SLIDE4_LT_RB_RB_LB,
      DLG_STRING_EFFECT_SLIDE4_LT_RB_RB_RT,
      DLG_STRING_EFFECT_SLIDE4_LT_RB_RB_RB,
      DLG_STRING_EFFECT_SLIDE4_LB_LT_LT_LT,
      DLG_STRING_EFFECT_SLIDE4_LB_LT_LT_LB,
      DLG_STRING_EFFECT_SLIDE4_LB_LT_LT_RT,
      DLG_STRING_EFFECT_SLIDE4_LB_LT_LT_RB,
      DLG_STRING_EFFECT_SLIDE4_LB_LT_LB_LT,
      DLG_STRING_EFFECT_SLIDE4_LB_LT_LB_LB,
      DLG_STRING_EFFECT_SLIDE4_LB_LT_LB_RT,
      DLG_STRING_EFFECT_SLIDE4_LB_LT_LB_RB,
      DLG_STRING_EFFECT_SLIDE4_LB_LT_RT_LT,
      DLG_STRING_EFFECT_SLIDE4_LB_LT_RT_LB,
      DLG_STRING_EFFECT_SLIDE4_LB_LT_RT_RT,
      DLG_STRING_EFFECT_SLIDE4_LB_LT_RT_RB,
      DLG_STRING_EFFECT_SLIDE4_LB_LT_RB_LT,
      DLG_STRING_EFFECT_SLIDE4_LB_LT_RB_LB,
      DLG_STRING_EFFECT_SLIDE4_LB_LT_RB_RT,
      DLG_STRING_EFFECT_SLIDE4_LB_LT_RB_RB,
      DLG_STRING_EFFECT_SLIDE4_LB_LB_LT_LT,
      DLG_STRING_EFFECT_SLIDE4_LB_LB_LT_LB,
      DLG_STRING_EFFECT_SLIDE4_LB_LB_LT_RT,
      DLG_STRING_EFFECT_SLIDE4_LB_LB_LT_RB,
      DLG_STRING_EFFECT_SLIDE4_LB_LB_LB_LT,
      DLG_STRING_EFFECT_SLIDE4_LB_LB_LB_LB,
      DLG_STRING_EFFECT_SLIDE4_LB_LB_LB_RT,
      DLG_STRING_EFFECT_SLIDE4_LB_LB_LB_RB,
      DLG_STRING_EFFECT_SLIDE4_LB_LB_RT_LT,
      DLG_STRING_EFFECT_SLIDE4_LB_LB_RT_LB,
      DLG_STRING_EFFECT_SLIDE4_LB_LB_RT_RT,
      DLG_STRING_EFFECT_SLIDE4_LB_LB_RT_RB,
      DLG_STRING_EFFECT_SLIDE4_LB_LB_RB_LT,
      DLG_STRING_EFFECT_SLIDE4_LB_LB_RB_LB,
      DLG_STRING_EFFECT_SLIDE4_LB_LB_RB_RT,
      DLG_STRING_EFFECT_SLIDE4_LB_LB_RB_RB,
      DLG_STRING_EFFECT_SLIDE4_LB_RT_LT_LT,
      DLG_STRING_EFFECT_SLIDE4_LB_RT_LT_LB,
      DLG_STRING_EFFECT_SLIDE4_LB_RT_LT_RT,
      DLG_STRING_EFFECT_SLIDE4_LB_RT_LT_RB,
      DLG_STRING_EFFECT_SLIDE4_LB_RT_LB_LT,
      DLG_STRING_EFFECT_SLIDE4_LB_RT_LB_LB,
      DLG_STRING_EFFECT_SLIDE4_LB_RT_LB_RT,
      DLG_STRING_EFFECT_SLIDE4_LB_RT_LB_RB,
      DLG_STRING_EFFECT_SLIDE4_LB_RT_RT_LT,
      DLG_STRING_EFFECT_SLIDE4_LB_RT_RT_LB,
      DLG_STRING_EFFECT_SLIDE4_LB_RT_RT_RT,
      DLG_STRING_EFFECT_SLIDE4_LB_RT_RT_RB,
      DLG_STRING_EFFECT_SLIDE4_LB_RT_RB_LT,
      DLG_STRING_EFFECT_SLIDE4_LB_RT_RB_LB,
      DLG_STRING_EFFECT_SLIDE4_LB_RT_RB_RT,
      DLG_STRING_EFFECT_SLIDE4_LB_RT_RB_RB,
      DLG_STRING_EFFECT_SLIDE4_LB_RB_LT_LT,
      DLG_STRING_EFFECT_SLIDE4_LB_RB_LT_LB,
      DLG_STRING_EFFECT_SLIDE4_LB_RB_LT_RT,
      DLG_STRING_EFFECT_SLIDE4_LB_RB_LT_RB,
      DLG_STRING_EFFECT_SLIDE4_LB_RB_LB_LT,
      DLG_STRING_EFFECT_SLIDE4_LB_RB_LB_LB,
      DLG_STRING_EFFECT_SLIDE4_LB_RB_LB_RT,
      DLG_STRING_EFFECT_SLIDE4_LB_RB_LB_RB,
      DLG_STRING_EFFECT_SLIDE4_LB_RB_RT_LT,
      DLG_STRING_EFFECT_SLIDE4_LB_RB_RT_LB,
      DLG_STRING_EFFECT_SLIDE4_LB_RB_RT_RT,
      DLG_STRING_EFFECT_SLIDE4_LB_RB_RT_RB,
      DLG_STRING_EFFECT_SLIDE4_LB_RB_RB_LT,
      DLG_STRING_EFFECT_SLIDE4_LB_RB_RB_LB,
      DLG_STRING_EFFECT_SLIDE4_LB_RB_RB_RT,
      DLG_STRING_EFFECT_SLIDE4_LB_RB_RB_RB,
      DLG_STRING_EFFECT_SLIDE4_RT_LT_LT_LT,
      DLG_STRING_EFFECT_SLIDE4_RT_LT_LT_LB,
      DLG_STRING_EFFECT_SLIDE4_RT_LT_LT_RT,
      DLG_STRING_EFFECT_SLIDE4_RT_LT_LT_RB,
      DLG_STRING_EFFECT_SLIDE4_RT_LT_LB_LT,
      DLG_STRING_EFFECT_SLIDE4_RT_LT_LB_LB,
      DLG_STRING_EFFECT_SLIDE4_RT_LT_LB_RT,
      DLG_STRING_EFFECT_SLIDE4_RT_LT_LB_RB,
      DLG_STRING_EFFECT_SLIDE4_RT_LT_RT_LT,
      DLG_STRING_EFFECT_SLIDE4_RT_LT_RT_LB,
      DLG_STRING_EFFECT_SLIDE4_RT_LT_RT_RT,
      DLG_STRING_EFFECT_SLIDE4_RT_LT_RT_RB,
      DLG_STRING_EFFECT_SLIDE4_RT_LT_RB_LT,
      DLG_STRING_EFFECT_SLIDE4_RT_LT_RB_LB,
      DLG_STRING_EFFECT_SLIDE4_RT_LT_RB_RT,
      DLG_STRING_EFFECT_SLIDE4_RT_LT_RB_RB,
      DLG_STRING_EFFECT_SLIDE4_RT_LB_LT_LT,
      DLG_STRING_EFFECT_SLIDE4_RT_LB_LT_LB,
      DLG_STRING_EFFECT_SLIDE4_RT_LB_LT_RT,
      DLG_STRING_EFFECT_SLIDE4_RT_LB_LT_RB,
      DLG_STRING_EFFECT_SLIDE4_RT_LB_LB_LT,
      DLG_STRING_EFFECT_SLIDE4_RT_LB_LB_LB,
      DLG_STRING_EFFECT_SLIDE4_RT_LB_LB_RT,
      DLG_STRING_EFFECT_SLIDE4_RT_LB_LB_RB,
      DLG_STRING_EFFECT_SLIDE4_RT_LB_RT_LT,
      DLG_STRING_EFFECT_SLIDE4_RT_LB_RT_LB,
      DLG_STRING_EFFECT_SLIDE4_RT_LB_RT_RT,
      DLG_STRING_EFFECT_SLIDE4_RT_LB_RT_RB,
      DLG_STRING_EFFECT_SLIDE4_RT_LB_RB_LT,
      DLG_STRING_EFFECT_SLIDE4_RT_LB_RB_LB,
      DLG_STRING_EFFECT_SLIDE4_RT_LB_RB_RT,
      DLG_STRING_EFFECT_SLIDE4_RT_LB_RB_RB,
      DLG_STRING_EFFECT_SLIDE4_RT_RT_LT_LT,
      DLG_STRING_EFFECT_SLIDE4_RT_RT_LT_LB,
      DLG_STRING_EFFECT_SLIDE4_RT_RT_LT_RT,
      DLG_STRING_EFFECT_SLIDE4_RT_RT_LT_RB,
      DLG_STRING_EFFECT_SLIDE4_RT_RT_LB_LT,
      DLG_STRING_EFFECT_SLIDE4_RT_RT_LB_LB,
      DLG_STRING_EFFECT_SLIDE4_RT_RT_LB_RT,
      DLG_STRING_EFFECT_SLIDE4_RT_RT_LB_RB,
      DLG_STRING_EFFECT_SLIDE4_RT_RT_RT_LT,
      DLG_STRING_EFFECT_SLIDE4_RT_RT_RT_LB,
      DLG_STRING_EFFECT_SLIDE4_RT_RT_RT_RT,
      DLG_STRING_EFFECT_SLIDE4_RT_RT_RT_RB,
      DLG_STRING_EFFECT_SLIDE4_RT_RT_RB_LT,
      DLG_STRING_EFFECT_SLIDE4_RT_RT_RB_LB,
      DLG_STRING_EFFECT_SLIDE4_RT_RT_RB_RT,
      DLG_STRING_EFFECT_SLIDE4_RT_RT_RB_RB,
      DLG_STRING_EFFECT_SLIDE4_RT_RB_LT_LT,
      DLG_STRING_EFFECT_SLIDE4_RT_RB_LT_LB,
      DLG_STRING_EFFECT_SLIDE4_RT_RB_LT_RT,
      DLG_STRING_EFFECT_SLIDE4_RT_RB_LT_RB,
      DLG_STRING_EFFECT_SLIDE4_RT_RB_LB_LT,
      DLG_STRING_EFFECT_SLIDE4_RT_RB_LB_LB,
      DLG_STRING_EFFECT_SLIDE4_RT_RB_LB_RT,
      DLG_STRING_EFFECT_SLIDE4_RT_RB_LB_RB,
      DLG_STRING_EFFECT_SLIDE4_RT_RB_RT_LT,
      DLG_STRING_EFFECT_SLIDE4_RT_RB_RT_LB,
      DLG_STRING_EFFECT_SLIDE4_RT_RB_RT_RT,
      DLG_STRING_EFFECT_SLIDE4_RT_RB_RT_RB,
      DLG_STRING_EFFECT_SLIDE4_RT_RB_RB_LT,
      DLG_STRING_EFFECT_SLIDE4_RT_RB_RB_LB,
      DLG_STRING_EFFECT_SLIDE4_RT_RB_RB_RT,
      DLG_STRING_EFFECT_SLIDE4_RT_RB_RB_RB,
      DLG_STRING_EFFECT_SLIDE4_RB_LT_LT_LT,
      DLG_STRING_EFFECT_SLIDE4_RB_LT_LT_LB,
      DLG_STRING_EFFECT_SLIDE4_RB_LT_LT_RT,
      DLG_STRING_EFFECT_SLIDE4_RB_LT_LT_RB,
      DLG_STRING_EFFECT_SLIDE4_RB_LT_LB_LT,
      DLG_STRING_EFFECT_SLIDE4_RB_LT_LB_LB,
      DLG_STRING_EFFECT_SLIDE4_RB_LT_LB_RT,
      DLG_STRING_EFFECT_SLIDE4_RB_LT_LB_RB,
      DLG_STRING_EFFECT_SLIDE4_RB_LT_RT_LT,
      DLG_STRING_EFFECT_SLIDE4_RB_LT_RT_LB,
      DLG_STRING_EFFECT_SLIDE4_RB_LT_RT_RT,
      DLG_STRING_EFFECT_SLIDE4_RB_LT_RT_RB,
      DLG_STRING_EFFECT_SLIDE4_RB_LT_RB_LT,
      DLG_STRING_EFFECT_SLIDE4_RB_LT_RB_LB,
      DLG_STRING_EFFECT_SLIDE4_RB_LT_RB_RT,
      DLG_STRING_EFFECT_SLIDE4_RB_LT_RB_RB,
      DLG_STRING_EFFECT_SLIDE4_RB_LB_LT_LT,
      DLG_STRING_EFFECT_SLIDE4_RB_LB_LT_LB,
      DLG_STRING_EFFECT_SLIDE4_RB_LB_LT_RT,
      DLG_STRING_EFFECT_SLIDE4_RB_LB_LT_RB,
      DLG_STRING_EFFECT_SLIDE4_RB_LB_LB_LT,
      DLG_STRING_EFFECT_SLIDE4_RB_LB_LB_LB,
      DLG_STRING_EFFECT_SLIDE4_RB_LB_LB_RT,
      DLG_STRING_EFFECT_SLIDE4_RB_LB_LB_RB,
      DLG_STRING_EFFECT_SLIDE4_RB_LB_RT_LT,
      DLG_STRING_EFFECT_SLIDE4_RB_LB_RT_LB,
      DLG_STRING_EFFECT_SLIDE4_RB_LB_RT_RT,
      DLG_STRING_EFFECT_SLIDE4_RB_LB_RT_RB,
      DLG_STRING_EFFECT_SLIDE4_RB_LB_RB_LT,
      DLG_STRING_EFFECT_SLIDE4_RB_LB_RB_LB,
      DLG_STRING_EFFECT_SLIDE4_RB_LB_RB_RT,
      DLG_STRING_EFFECT_SLIDE4_RB_LB_RB_RB,
      DLG_STRING_EFFECT_SLIDE4_RB_RT_LT_LT,
      DLG_STRING_EFFECT_SLIDE4_RB_RT_LT_LB,
      DLG_STRING_EFFECT_SLIDE4_RB_RT_LT_RT,
      DLG_STRING_EFFECT_SLIDE4_RB_RT_LT_RB,
      DLG_STRING_EFFECT_SLIDE4_RB_RT_LB_LT,
      DLG_STRING_EFFECT_SLIDE4_RB_RT_LB_LB,
      DLG_STRING_EFFECT_SLIDE4_RB_RT_LB_RT,
      DLG_STRING_EFFECT_SLIDE4_RB_RT_LB_RB,
      DLG_STRING_EFFECT_SLIDE4_RB_RT_RT_LT,
      DLG_STRING_EFFECT_SLIDE4_RB_RT_RT_LB,
      DLG_STRING_EFFECT_SLIDE4_RB_RT_RT_RT,
      DLG_STRING_EFFECT_SLIDE4_RB_RT_RT_RB,
      DLG_STRING_EFFECT_SLIDE4_RB_RT_RB_LT,
      DLG_STRING_EFFECT_SLIDE4_RB_RT_RB_LB,
      DLG_STRING_EFFECT_SLIDE4_RB_RT_RB_RT,
      DLG_STRING_EFFECT_SLIDE4_RB_RT_RB_RB,
      DLG_STRING_EFFECT_SLIDE4_RB_RB_LT_LT,
      DLG_STRING_EFFECT_SLIDE4_RB_RB_LT_LB,
      DLG_STRING_EFFECT_SLIDE4_RB_RB_LT_RT,
      DLG_STRING_EFFECT_SLIDE4_RB_RB_LT_RB,
      DLG_STRING_EFFECT_SLIDE4_RB_RB_LB_LT,
      DLG_STRING_EFFECT_SLIDE4_RB_RB_LB_LB,
      DLG_STRING_EFFECT_SLIDE4_RB_RB_LB_RT,
      DLG_STRING_EFFECT_SLIDE4_RB_RB_LB_RB,
      DLG_STRING_EFFECT_SLIDE4_RB_RB_RT_LT,
      DLG_STRING_EFFECT_SLIDE4_RB_RB_RT_LB,
      DLG_STRING_EFFECT_SLIDE4_RB_RB_RT_RT,
      DLG_STRING_EFFECT_SLIDE4_RB_RB_RT_RB,
      DLG_STRING_EFFECT_SLIDE4_RB_RB_RB_LT,
      DLG_STRING_EFFECT_SLIDE4_RB_RB_RB_LB,
      DLG_STRING_EFFECT_SLIDE4_RB_RB_RB_RT,
      DLG_STRING_EFFECT_SLIDE4_RB_RB_RB_RB,
      DLG_STRINGS5_MAX,
   }DlgStrings5;

   typedef enum
   {
      DLG_STRING_EFFECT_ROLL_L_TO_R=DLG_STRINGS5_MAX,
      DLG_STRING_EFFECT_ROLL_R_TO_L,
      DLG_STRING_EFFECT_ROLL_T_TO_B,
      DLG_STRING_EFFECT_ROLL_B_TO_T,
      DLG_STRING_EFFECT_ROLL2_T_R_TO_L_AND_B_L_TO_R,
      DLG_STRING_EFFECT_ROLL2_T_L_TO_R_AND_B_R_TO_L,
      DLG_STRING_EFFECT_ROLL2_L_B_TO_T_AND_R_T_TO_B,
      DLG_STRING_EFFECT_ROLL2_L_T_TO_B_AND_R_B_TO_T,
      DLG_STRING_EFFECT_ROLL4_L_L_L_L,
      DLG_STRING_EFFECT_ROLL4_L_L_L_R,
      DLG_STRING_EFFECT_ROLL4_L_L_L_T,
      DLG_STRING_EFFECT_ROLL4_L_L_L_B,
      DLG_STRING_EFFECT_ROLL4_L_L_R_L,
      DLG_STRING_EFFECT_ROLL4_L_L_R_R,
      DLG_STRING_EFFECT_ROLL4_L_L_R_T,
      DLG_STRING_EFFECT_ROLL4_L_L_R_B,
      DLG_STRING_EFFECT_ROLL4_L_L_T_L,
      DLG_STRING_EFFECT_ROLL4_L_L_T_R,
      DLG_STRING_EFFECT_ROLL4_L_L_T_T,
      DLG_STRING_EFFECT_ROLL4_L_L_T_B,
      DLG_STRING_EFFECT_ROLL4_L_L_B_L,
      DLG_STRING_EFFECT_ROLL4_L_L_B_R,
      DLG_STRING_EFFECT_ROLL4_L_L_B_T,
      DLG_STRING_EFFECT_ROLL4_L_L_B_B,
      DLG_STRING_EFFECT_ROLL4_L_R_L_L,
      DLG_STRING_EFFECT_ROLL4_L_R_L_R,
      DLG_STRING_EFFECT_ROLL4_L_R_L_T,
      DLG_STRING_EFFECT_ROLL4_L_R_L_B,
      DLG_STRING_EFFECT_ROLL4_L_R_R_L,
      DLG_STRING_EFFECT_ROLL4_L_R_R_R,
      DLG_STRING_EFFECT_ROLL4_L_R_R_T,
      DLG_STRING_EFFECT_ROLL4_L_R_R_B,
      DLG_STRING_EFFECT_ROLL4_L_R_T_L,
      DLG_STRING_EFFECT_ROLL4_L_R_T_R,
      DLG_STRING_EFFECT_ROLL4_L_R_T_T,
      DLG_STRING_EFFECT_ROLL4_L_R_T_B,
      DLG_STRING_EFFECT_ROLL4_L_R_B_L,
      DLG_STRING_EFFECT_ROLL4_L_R_B_R,
      DLG_STRING_EFFECT_ROLL4_L_R_B_T,
      DLG_STRING_EFFECT_ROLL4_L_R_B_B,
      DLG_STRING_EFFECT_ROLL4_L_T_L_L,
      DLG_STRING_EFFECT_ROLL4_L_T_L_R,
      DLG_STRING_EFFECT_ROLL4_L_T_L_T,
      DLG_STRING_EFFECT_ROLL4_L_T_L_B,
      DLG_STRING_EFFECT_ROLL4_L_T_R_L,
      DLG_STRING_EFFECT_ROLL4_L_T_R_R,
      DLG_STRING_EFFECT_ROLL4_L_T_R_T,
      DLG_STRING_EFFECT_ROLL4_L_T_R_B,
      DLG_STRING_EFFECT_ROLL4_L_T_T_L,
      DLG_STRING_EFFECT_ROLL4_L_T_T_R,
      DLG_STRING_EFFECT_ROLL4_L_T_T_T,
      DLG_STRING_EFFECT_ROLL4_L_T_T_B,
      DLG_STRING_EFFECT_ROLL4_L_T_B_L,
      DLG_STRING_EFFECT_ROLL4_L_T_B_R,
      DLG_STRING_EFFECT_ROLL4_L_T_B_T,
      DLG_STRING_EFFECT_ROLL4_L_T_B_B,
      DLG_STRING_EFFECT_ROLL4_L_B_L_L,
      DLG_STRING_EFFECT_ROLL4_L_B_L_R,
      DLG_STRING_EFFECT_ROLL4_L_B_L_T,
      DLG_STRING_EFFECT_ROLL4_L_B_L_B,
      DLG_STRING_EFFECT_ROLL4_L_B_R_L,
      DLG_STRING_EFFECT_ROLL4_L_B_R_R,
      DLG_STRING_EFFECT_ROLL4_L_B_R_T,
      DLG_STRING_EFFECT_ROLL4_L_B_R_B,
      DLG_STRING_EFFECT_ROLL4_L_B_T_L,
      DLG_STRING_EFFECT_ROLL4_L_B_T_R,
      DLG_STRING_EFFECT_ROLL4_L_B_T_T,
      DLG_STRING_EFFECT_ROLL4_L_B_T_B,
      DLG_STRING_EFFECT_ROLL4_L_B_B_L,
      DLG_STRING_EFFECT_ROLL4_L_B_B_R,
      DLG_STRING_EFFECT_ROLL4_L_B_B_T,
      DLG_STRING_EFFECT_ROLL4_L_B_B_B,
      DLG_STRING_EFFECT_ROLL4_R_L_L_L,
      DLG_STRING_EFFECT_ROLL4_R_L_L_R,
      DLG_STRING_EFFECT_ROLL4_R_L_L_T,
      DLG_STRING_EFFECT_ROLL4_R_L_L_B,
      DLG_STRING_EFFECT_ROLL4_R_L_R_L,
      DLG_STRING_EFFECT_ROLL4_R_L_R_R,
      DLG_STRING_EFFECT_ROLL4_R_L_R_T,
      DLG_STRING_EFFECT_ROLL4_R_L_R_B,
      DLG_STRING_EFFECT_ROLL4_R_L_T_L,
      DLG_STRING_EFFECT_ROLL4_R_L_T_R,
      DLG_STRING_EFFECT_ROLL4_R_L_T_T,
      DLG_STRING_EFFECT_ROLL4_R_L_T_B,
      DLG_STRING_EFFECT_ROLL4_R_L_B_L,
      DLG_STRING_EFFECT_ROLL4_R_L_B_R,
      DLG_STRING_EFFECT_ROLL4_R_L_B_T,
      DLG_STRING_EFFECT_ROLL4_R_L_B_B,
      DLG_STRING_EFFECT_ROLL4_R_R_L_L,
      DLG_STRING_EFFECT_ROLL4_R_R_L_R,
      DLG_STRING_EFFECT_ROLL4_R_R_L_T,
      DLG_STRING_EFFECT_ROLL4_R_R_L_B,
      DLG_STRING_EFFECT_ROLL4_R_R_R_L,
      DLG_STRING_EFFECT_ROLL4_R_R_R_R,
      DLG_STRING_EFFECT_ROLL4_R_R_R_T,
      DLG_STRING_EFFECT_ROLL4_R_R_R_B,
      DLG_STRING_EFFECT_ROLL4_R_R_T_L,
      DLG_STRING_EFFECT_ROLL4_R_R_T_R,
      DLG_STRING_EFFECT_ROLL4_R_R_T_T,
      DLG_STRING_EFFECT_ROLL4_R_R_T_B,
      DLG_STRING_EFFECT_ROLL4_R_R_B_L,
      DLG_STRING_EFFECT_ROLL4_R_R_B_R,
      DLG_STRING_EFFECT_ROLL4_R_R_B_T,
      DLG_STRING_EFFECT_ROLL4_R_R_B_B,
      DLG_STRING_EFFECT_ROLL4_R_T_L_L,
      DLG_STRING_EFFECT_ROLL4_R_T_L_R,
      DLG_STRING_EFFECT_ROLL4_R_T_L_T,
      DLG_STRING_EFFECT_ROLL4_R_T_L_B,
      DLG_STRING_EFFECT_ROLL4_R_T_R_L,
      DLG_STRING_EFFECT_ROLL4_R_T_R_R,
      DLG_STRING_EFFECT_ROLL4_R_T_R_T,
      DLG_STRING_EFFECT_ROLL4_R_T_R_B,
      DLG_STRING_EFFECT_ROLL4_R_T_T_L,
      DLG_STRING_EFFECT_ROLL4_R_T_T_R,
      DLG_STRING_EFFECT_ROLL4_R_T_T_T,
      DLG_STRING_EFFECT_ROLL4_R_T_T_B,
      DLG_STRING_EFFECT_ROLL4_R_T_B_L,
      DLG_STRING_EFFECT_ROLL4_R_T_B_R,
      DLG_STRING_EFFECT_ROLL4_R_T_B_T,
      DLG_STRING_EFFECT_ROLL4_R_T_B_B,
      DLG_STRING_EFFECT_ROLL4_R_B_L_L,
      DLG_STRING_EFFECT_ROLL4_R_B_L_R,
      DLG_STRING_EFFECT_ROLL4_R_B_L_T,
      DLG_STRING_EFFECT_ROLL4_R_B_L_B,
      DLG_STRING_EFFECT_ROLL4_R_B_R_L,
      DLG_STRING_EFFECT_ROLL4_R_B_R_R,
      DLG_STRING_EFFECT_ROLL4_R_B_R_T,
      DLG_STRING_EFFECT_ROLL4_R_B_R_B,
      DLG_STRING_EFFECT_ROLL4_R_B_T_L,
      DLG_STRING_EFFECT_ROLL4_R_B_T_R,
      DLG_STRING_EFFECT_ROLL4_R_B_T_T,
      DLG_STRING_EFFECT_ROLL4_R_B_T_B,
      DLG_STRING_EFFECT_ROLL4_R_B_B_L,
      DLG_STRING_EFFECT_ROLL4_R_B_B_R,
      DLG_STRING_EFFECT_ROLL4_R_B_B_T,
      DLG_STRING_EFFECT_ROLL4_R_B_B_B,
      DLG_STRING_EFFECT_ROLL4_T_L_L_L,
      DLG_STRING_EFFECT_ROLL4_T_L_L_R,
      DLG_STRING_EFFECT_ROLL4_T_L_L_T,
      DLG_STRING_EFFECT_ROLL4_T_L_L_B,
      DLG_STRING_EFFECT_ROLL4_T_L_R_L,
      DLG_STRING_EFFECT_ROLL4_T_L_R_R,
      DLG_STRING_EFFECT_ROLL4_T_L_R_T,
      DLG_STRING_EFFECT_ROLL4_T_L_R_B,
      DLG_STRING_EFFECT_ROLL4_T_L_T_L,
      DLG_STRING_EFFECT_ROLL4_T_L_T_R,
      DLG_STRING_EFFECT_ROLL4_T_L_T_T,
      DLG_STRING_EFFECT_ROLL4_T_L_T_B,
      DLG_STRING_EFFECT_ROLL4_T_L_B_L,
      DLG_STRING_EFFECT_ROLL4_T_L_B_R,
      DLG_STRING_EFFECT_ROLL4_T_L_B_T,
      DLG_STRING_EFFECT_ROLL4_T_L_B_B,
      DLG_STRING_EFFECT_ROLL4_T_R_L_L,
      DLG_STRING_EFFECT_ROLL4_T_R_L_R,
      DLG_STRING_EFFECT_ROLL4_T_R_L_T,
      DLG_STRING_EFFECT_ROLL4_T_R_L_B,
      DLG_STRING_EFFECT_ROLL4_T_R_R_L,
      DLG_STRING_EFFECT_ROLL4_T_R_R_R,
      DLG_STRING_EFFECT_ROLL4_T_R_R_T,
      DLG_STRING_EFFECT_ROLL4_T_R_R_B,
      DLG_STRING_EFFECT_ROLL4_T_R_T_L,
      DLG_STRING_EFFECT_ROLL4_T_R_T_R,
      DLG_STRING_EFFECT_ROLL4_T_R_T_T,
      DLG_STRING_EFFECT_ROLL4_T_R_T_B,
      DLG_STRING_EFFECT_ROLL4_T_R_B_L,
      DLG_STRING_EFFECT_ROLL4_T_R_B_R,
      DLG_STRING_EFFECT_ROLL4_T_R_B_T,
      DLG_STRING_EFFECT_ROLL4_T_R_B_B,
      DLG_STRING_EFFECT_ROLL4_T_T_L_L,
      DLG_STRING_EFFECT_ROLL4_T_T_L_R,
      DLG_STRING_EFFECT_ROLL4_T_T_L_T,
      DLG_STRING_EFFECT_ROLL4_T_T_L_B,
      DLG_STRING_EFFECT_ROLL4_T_T_R_L,
      DLG_STRING_EFFECT_ROLL4_T_T_R_R,
      DLG_STRING_EFFECT_ROLL4_T_T_R_T,
      DLG_STRING_EFFECT_ROLL4_T_T_R_B,
      DLG_STRING_EFFECT_ROLL4_T_T_T_L,
      DLG_STRING_EFFECT_ROLL4_T_T_T_R,
      DLG_STRING_EFFECT_ROLL4_T_T_T_T,
      DLG_STRING_EFFECT_ROLL4_T_T_T_B,
      DLG_STRING_EFFECT_ROLL4_T_T_B_L,
      DLG_STRING_EFFECT_ROLL4_T_T_B_R,
      DLG_STRING_EFFECT_ROLL4_T_T_B_T,
      DLG_STRING_EFFECT_ROLL4_T_T_B_B,
      DLG_STRING_EFFECT_ROLL4_T_B_L_L,
      DLG_STRING_EFFECT_ROLL4_T_B_L_R,
      DLG_STRING_EFFECT_ROLL4_T_B_L_T,
      DLG_STRING_EFFECT_ROLL4_T_B_L_B,
      DLG_STRING_EFFECT_ROLL4_T_B_R_L,
      DLG_STRING_EFFECT_ROLL4_T_B_R_R,
      DLG_STRING_EFFECT_ROLL4_T_B_R_T,
      DLG_STRING_EFFECT_ROLL4_T_B_R_B,
      DLG_STRING_EFFECT_ROLL4_T_B_T_L,
      DLG_STRING_EFFECT_ROLL4_T_B_T_R,
      DLG_STRING_EFFECT_ROLL4_T_B_T_T,
      DLG_STRING_EFFECT_ROLL4_T_B_T_B,
      DLG_STRING_EFFECT_ROLL4_T_B_B_L,
      DLG_STRING_EFFECT_ROLL4_T_B_B_R,
      DLG_STRING_EFFECT_ROLL4_T_B_B_T,
      DLG_STRING_EFFECT_ROLL4_T_B_B_B,
      DLG_STRING_EFFECT_ROLL4_B_L_L_L,
      DLG_STRING_EFFECT_ROLL4_B_L_L_R,
      DLG_STRING_EFFECT_ROLL4_B_L_L_T,
      DLG_STRING_EFFECT_ROLL4_B_L_L_B,
      DLG_STRING_EFFECT_ROLL4_B_L_R_L,
      DLG_STRING_EFFECT_ROLL4_B_L_R_R,
      DLG_STRING_EFFECT_ROLL4_B_L_R_T,
      DLG_STRING_EFFECT_ROLL4_B_L_R_B,
      DLG_STRING_EFFECT_ROLL4_B_L_T_L,
      DLG_STRING_EFFECT_ROLL4_B_L_T_R,
      DLG_STRING_EFFECT_ROLL4_B_L_T_T,
      DLG_STRING_EFFECT_ROLL4_B_L_T_B,
      DLG_STRING_EFFECT_ROLL4_B_L_B_L,
      DLG_STRING_EFFECT_ROLL4_B_L_B_R,
      DLG_STRING_EFFECT_ROLL4_B_L_B_T,
      DLG_STRING_EFFECT_ROLL4_B_L_B_B,
      DLG_STRING_EFFECT_ROLL4_B_R_L_L,
      DLG_STRING_EFFECT_ROLL4_B_R_L_R,
      DLG_STRING_EFFECT_ROLL4_B_R_L_T,
      DLG_STRING_EFFECT_ROLL4_B_R_L_B,
      DLG_STRING_EFFECT_ROLL4_B_R_R_L,
      DLG_STRING_EFFECT_ROLL4_B_R_R_R,
      DLG_STRING_EFFECT_ROLL4_B_R_R_T,
      DLG_STRING_EFFECT_ROLL4_B_R_R_B,
      DLG_STRING_EFFECT_ROLL4_B_R_T_L,
      DLG_STRING_EFFECT_ROLL4_B_R_T_R,
      DLG_STRING_EFFECT_ROLL4_B_R_T_T,
      DLG_STRING_EFFECT_ROLL4_B_R_T_B,
      DLG_STRING_EFFECT_ROLL4_B_R_B_L,
      DLG_STRING_EFFECT_ROLL4_B_R_B_R,
      DLG_STRING_EFFECT_ROLL4_B_R_B_T,
      DLG_STRING_EFFECT_ROLL4_B_R_B_B,
      DLG_STRING_EFFECT_ROLL4_B_T_L_L,
      DLG_STRING_EFFECT_ROLL4_B_T_L_R,
      DLG_STRING_EFFECT_ROLL4_B_T_L_T,
      DLG_STRING_EFFECT_ROLL4_B_T_L_B,
      DLG_STRING_EFFECT_ROLL4_B_T_R_L,
      DLG_STRING_EFFECT_ROLL4_B_T_R_R,
      DLG_STRING_EFFECT_ROLL4_B_T_R_T,
      DLG_STRING_EFFECT_ROLL4_B_T_R_B,
      DLG_STRING_EFFECT_ROLL4_B_T_T_L,
      DLG_STRING_EFFECT_ROLL4_B_T_T_R,
      DLG_STRING_EFFECT_ROLL4_B_T_T_T,
      DLG_STRING_EFFECT_ROLL4_B_T_T_B,
      DLG_STRING_EFFECT_ROLL4_B_T_B_L,
      DLG_STRING_EFFECT_ROLL4_B_T_B_R,
      DLG_STRING_EFFECT_ROLL4_B_T_B_T,
      DLG_STRING_EFFECT_ROLL4_B_T_B_B,
      DLG_STRING_EFFECT_ROLL4_B_B_L_L,
      DLG_STRING_EFFECT_ROLL4_B_B_L_R,
      DLG_STRING_EFFECT_ROLL4_B_B_L_T,
      DLG_STRING_EFFECT_ROLL4_B_B_L_B,
      DLG_STRING_EFFECT_ROLL4_B_B_R_L,
      DLG_STRING_EFFECT_ROLL4_B_B_R_R,
      DLG_STRING_EFFECT_ROLL4_B_B_R_T,
      DLG_STRING_EFFECT_ROLL4_B_B_R_B,
      DLG_STRING_EFFECT_ROLL4_B_B_T_L,
      DLG_STRING_EFFECT_ROLL4_B_B_T_R,
      DLG_STRING_EFFECT_ROLL4_B_B_T_T,
      DLG_STRING_EFFECT_ROLL4_B_B_T_B,
      DLG_STRING_EFFECT_ROLL4_B_B_B_L,
      DLG_STRING_EFFECT_ROLL4_B_B_B_R,
      DLG_STRING_EFFECT_ROLL4_B_B_B_T,
      DLG_STRING_EFFECT_ROLL4_B_B_B_B,

      DLG_STRING_EFFECT_ROTATE_L_TO_R,
      DLG_STRING_EFFECT_ROTATE_R_TO_L,
      DLG_STRING_EFFECT_ROTATE_T_TO_B,
      DLG_STRING_EFFECT_ROTATE_B_TO_T,
      DLG_STRING_EFFECT_ROTATE4_L_L_L_L,
      DLG_STRING_EFFECT_ROTATE4_L_L_L_R,
      DLG_STRING_EFFECT_ROTATE4_L_L_L_T,
      DLG_STRING_EFFECT_ROTATE4_L_L_L_B,
      DLG_STRING_EFFECT_ROTATE4_L_L_R_L,
      DLG_STRING_EFFECT_ROTATE4_L_L_R_R,
      DLG_STRING_EFFECT_ROTATE4_L_L_R_T,
      DLG_STRING_EFFECT_ROTATE4_L_L_R_B,
      DLG_STRING_EFFECT_ROTATE4_L_L_T_L,
      DLG_STRING_EFFECT_ROTATE4_L_L_T_R,
      DLG_STRING_EFFECT_ROTATE4_L_L_T_T,
      DLG_STRING_EFFECT_ROTATE4_L_L_T_B,
      DLG_STRING_EFFECT_ROTATE4_L_L_B_L,
      DLG_STRING_EFFECT_ROTATE4_L_L_B_R,
      DLG_STRING_EFFECT_ROTATE4_L_L_B_T,
      DLG_STRING_EFFECT_ROTATE4_L_L_B_B,
      DLG_STRING_EFFECT_ROTATE4_L_R_L_L,
      DLG_STRING_EFFECT_ROTATE4_L_R_L_R,
      DLG_STRING_EFFECT_ROTATE4_L_R_L_T,
      DLG_STRING_EFFECT_ROTATE4_L_R_L_B,
      DLG_STRING_EFFECT_ROTATE4_L_R_R_L,
      DLG_STRING_EFFECT_ROTATE4_L_R_R_R,
      DLG_STRING_EFFECT_ROTATE4_L_R_R_T,
      DLG_STRING_EFFECT_ROTATE4_L_R_R_B,
      DLG_STRING_EFFECT_ROTATE4_L_R_T_L,
      DLG_STRING_EFFECT_ROTATE4_L_R_T_R,
      DLG_STRING_EFFECT_ROTATE4_L_R_T_T,
      DLG_STRING_EFFECT_ROTATE4_L_R_T_B,
      DLG_STRING_EFFECT_ROTATE4_L_R_B_L,
      DLG_STRING_EFFECT_ROTATE4_L_R_B_R,
      DLG_STRING_EFFECT_ROTATE4_L_R_B_T,
      DLG_STRING_EFFECT_ROTATE4_L_R_B_B,
      DLG_STRING_EFFECT_ROTATE4_L_T_L_L,
      DLG_STRING_EFFECT_ROTATE4_L_T_L_R,
      DLG_STRING_EFFECT_ROTATE4_L_T_L_T,
      DLG_STRING_EFFECT_ROTATE4_L_T_L_B,
      DLG_STRING_EFFECT_ROTATE4_L_T_R_L,
      DLG_STRING_EFFECT_ROTATE4_L_T_R_R,
      DLG_STRING_EFFECT_ROTATE4_L_T_R_T,
      DLG_STRING_EFFECT_ROTATE4_L_T_R_B,
      DLG_STRING_EFFECT_ROTATE4_L_T_T_L,
      DLG_STRING_EFFECT_ROTATE4_L_T_T_R,
      DLG_STRING_EFFECT_ROTATE4_L_T_T_T,
      DLG_STRING_EFFECT_ROTATE4_L_T_T_B,
      DLG_STRING_EFFECT_ROTATE4_L_T_B_L,
      DLG_STRING_EFFECT_ROTATE4_L_T_B_R,
      DLG_STRING_EFFECT_ROTATE4_L_T_B_T,
      DLG_STRING_EFFECT_ROTATE4_L_T_B_B,
      DLG_STRING_EFFECT_ROTATE4_L_B_L_L,
      DLG_STRING_EFFECT_ROTATE4_L_B_L_R,
      DLG_STRING_EFFECT_ROTATE4_L_B_L_T,
      DLG_STRING_EFFECT_ROTATE4_L_B_L_B,
      DLG_STRING_EFFECT_ROTATE4_L_B_R_L,
      DLG_STRING_EFFECT_ROTATE4_L_B_R_R,
      DLG_STRING_EFFECT_ROTATE4_L_B_R_T,
      DLG_STRING_EFFECT_ROTATE4_L_B_R_B,
      DLG_STRING_EFFECT_ROTATE4_L_B_T_L,
      DLG_STRING_EFFECT_ROTATE4_L_B_T_R,
      DLG_STRING_EFFECT_ROTATE4_L_B_T_T,
      DLG_STRING_EFFECT_ROTATE4_L_B_T_B,
      DLG_STRING_EFFECT_ROTATE4_L_B_B_L,
      DLG_STRING_EFFECT_ROTATE4_L_B_B_R,
      DLG_STRING_EFFECT_ROTATE4_L_B_B_T,
      DLG_STRING_EFFECT_ROTATE4_L_B_B_B,
      DLG_STRING_EFFECT_ROTATE4_R_L_L_L,
      DLG_STRING_EFFECT_ROTATE4_R_L_L_R,
      DLG_STRING_EFFECT_ROTATE4_R_L_L_T,
      DLG_STRING_EFFECT_ROTATE4_R_L_L_B,
      DLG_STRING_EFFECT_ROTATE4_R_L_R_L,
      DLG_STRING_EFFECT_ROTATE4_R_L_R_R,
      DLG_STRING_EFFECT_ROTATE4_R_L_R_T,
      DLG_STRING_EFFECT_ROTATE4_R_L_R_B,
      DLG_STRING_EFFECT_ROTATE4_R_L_T_L,
      DLG_STRING_EFFECT_ROTATE4_R_L_T_R,
      DLG_STRING_EFFECT_ROTATE4_R_L_T_T,
      DLG_STRING_EFFECT_ROTATE4_R_L_T_B,
      DLG_STRING_EFFECT_ROTATE4_R_L_B_L,
      DLG_STRING_EFFECT_ROTATE4_R_L_B_R,
      DLG_STRING_EFFECT_ROTATE4_R_L_B_T,
      DLG_STRING_EFFECT_ROTATE4_R_L_B_B,
      DLG_STRING_EFFECT_ROTATE4_R_R_L_L,
      DLG_STRING_EFFECT_ROTATE4_R_R_L_R,
      DLG_STRING_EFFECT_ROTATE4_R_R_L_T,
      DLG_STRING_EFFECT_ROTATE4_R_R_L_B,
      DLG_STRING_EFFECT_ROTATE4_R_R_R_L,
      DLG_STRING_EFFECT_ROTATE4_R_R_R_R,
      DLG_STRING_EFFECT_ROTATE4_R_R_R_T,
      DLG_STRING_EFFECT_ROTATE4_R_R_R_B,
      DLG_STRING_EFFECT_ROTATE4_R_R_T_L,
      DLG_STRING_EFFECT_ROTATE4_R_R_T_R,
      DLG_STRING_EFFECT_ROTATE4_R_R_T_T,
      DLG_STRING_EFFECT_ROTATE4_R_R_T_B,
      DLG_STRING_EFFECT_ROTATE4_R_R_B_L,
      DLG_STRING_EFFECT_ROTATE4_R_R_B_R,
      DLG_STRING_EFFECT_ROTATE4_R_R_B_T,
      DLG_STRING_EFFECT_ROTATE4_R_R_B_B,
      DLG_STRING_EFFECT_ROTATE4_R_T_L_L,
      DLG_STRING_EFFECT_ROTATE4_R_T_L_R,
      DLG_STRING_EFFECT_ROTATE4_R_T_L_T,
      DLG_STRING_EFFECT_ROTATE4_R_T_L_B,
      DLG_STRING_EFFECT_ROTATE4_R_T_R_L,
      DLG_STRING_EFFECT_ROTATE4_R_T_R_R,
      DLG_STRING_EFFECT_ROTATE4_R_T_R_T,
      DLG_STRING_EFFECT_ROTATE4_R_T_R_B,
      DLG_STRING_EFFECT_ROTATE4_R_T_T_L,
      DLG_STRING_EFFECT_ROTATE4_R_T_T_R,
      DLG_STRING_EFFECT_ROTATE4_R_T_T_T,
      DLG_STRING_EFFECT_ROTATE4_R_T_T_B,
      DLG_STRING_EFFECT_ROTATE4_R_T_B_L,
      DLG_STRING_EFFECT_ROTATE4_R_T_B_R,
      DLG_STRING_EFFECT_ROTATE4_R_T_B_T,
      DLG_STRING_EFFECT_ROTATE4_R_T_B_B,
      DLG_STRING_EFFECT_ROTATE4_R_B_L_L,
      DLG_STRING_EFFECT_ROTATE4_R_B_L_R,
      DLG_STRING_EFFECT_ROTATE4_R_B_L_T,
      DLG_STRING_EFFECT_ROTATE4_R_B_L_B,
      DLG_STRING_EFFECT_ROTATE4_R_B_R_L,
      DLG_STRING_EFFECT_ROTATE4_R_B_R_R,
      DLG_STRING_EFFECT_ROTATE4_R_B_R_T,
      DLG_STRING_EFFECT_ROTATE4_R_B_R_B,
      DLG_STRING_EFFECT_ROTATE4_R_B_T_L,
      DLG_STRING_EFFECT_ROTATE4_R_B_T_R,
      DLG_STRING_EFFECT_ROTATE4_R_B_T_T,
      DLG_STRING_EFFECT_ROTATE4_R_B_T_B,
      DLG_STRING_EFFECT_ROTATE4_R_B_B_L,
      DLG_STRING_EFFECT_ROTATE4_R_B_B_R,
      DLG_STRING_EFFECT_ROTATE4_R_B_B_T,
      DLG_STRING_EFFECT_ROTATE4_R_B_B_B,
      DLG_STRING_EFFECT_ROTATE4_T_L_L_L,
      DLG_STRING_EFFECT_ROTATE4_T_L_L_R,
      DLG_STRING_EFFECT_ROTATE4_T_L_L_T,
      DLG_STRING_EFFECT_ROTATE4_T_L_L_B,
      DLG_STRING_EFFECT_ROTATE4_T_L_R_L,
      DLG_STRING_EFFECT_ROTATE4_T_L_R_R,
      DLG_STRING_EFFECT_ROTATE4_T_L_R_T,
      DLG_STRING_EFFECT_ROTATE4_T_L_R_B,
      DLG_STRING_EFFECT_ROTATE4_T_L_T_L,
      DLG_STRING_EFFECT_ROTATE4_T_L_T_R,
      DLG_STRING_EFFECT_ROTATE4_T_L_T_T,
      DLG_STRING_EFFECT_ROTATE4_T_L_T_B,
      DLG_STRING_EFFECT_ROTATE4_T_L_B_L,
      DLG_STRING_EFFECT_ROTATE4_T_L_B_R,
      DLG_STRING_EFFECT_ROTATE4_T_L_B_T,
      DLG_STRING_EFFECT_ROTATE4_T_L_B_B,
      DLG_STRING_EFFECT_ROTATE4_T_R_L_L,
      DLG_STRING_EFFECT_ROTATE4_T_R_L_R,
      DLG_STRING_EFFECT_ROTATE4_T_R_L_T,
      DLG_STRING_EFFECT_ROTATE4_T_R_L_B,
      DLG_STRING_EFFECT_ROTATE4_T_R_R_L,
      DLG_STRING_EFFECT_ROTATE4_T_R_R_R,
      DLG_STRING_EFFECT_ROTATE4_T_R_R_T,
      DLG_STRING_EFFECT_ROTATE4_T_R_R_B,
      DLG_STRING_EFFECT_ROTATE4_T_R_T_L,
      DLG_STRING_EFFECT_ROTATE4_T_R_T_R,
      DLG_STRING_EFFECT_ROTATE4_T_R_T_T,
      DLG_STRING_EFFECT_ROTATE4_T_R_T_B,
      DLG_STRING_EFFECT_ROTATE4_T_R_B_L,
      DLG_STRING_EFFECT_ROTATE4_T_R_B_R,
      DLG_STRING_EFFECT_ROTATE4_T_R_B_T,
      DLG_STRING_EFFECT_ROTATE4_T_R_B_B,
      DLG_STRING_EFFECT_ROTATE4_T_T_L_L,
      DLG_STRING_EFFECT_ROTATE4_T_T_L_R,
      DLG_STRING_EFFECT_ROTATE4_T_T_L_T,
      DLG_STRING_EFFECT_ROTATE4_T_T_L_B,
      DLG_STRING_EFFECT_ROTATE4_T_T_R_L,
      DLG_STRING_EFFECT_ROTATE4_T_T_R_R,
      DLG_STRING_EFFECT_ROTATE4_T_T_R_T,
      DLG_STRING_EFFECT_ROTATE4_T_T_R_B,
      DLG_STRING_EFFECT_ROTATE4_T_T_T_L,
      DLG_STRING_EFFECT_ROTATE4_T_T_T_R,
      DLG_STRING_EFFECT_ROTATE4_T_T_T_T,
      DLG_STRING_EFFECT_ROTATE4_T_T_T_B,
      DLG_STRING_EFFECT_ROTATE4_T_T_B_L,
      DLG_STRING_EFFECT_ROTATE4_T_T_B_R,
      DLG_STRING_EFFECT_ROTATE4_T_T_B_T,
      DLG_STRING_EFFECT_ROTATE4_T_T_B_B,
      DLG_STRING_EFFECT_ROTATE4_T_B_L_L,
      DLG_STRING_EFFECT_ROTATE4_T_B_L_R,
      DLG_STRING_EFFECT_ROTATE4_T_B_L_T,
      DLG_STRING_EFFECT_ROTATE4_T_B_L_B,
      DLG_STRING_EFFECT_ROTATE4_T_B_R_L,
      DLG_STRING_EFFECT_ROTATE4_T_B_R_R,
      DLG_STRING_EFFECT_ROTATE4_T_B_R_T,
      DLG_STRING_EFFECT_ROTATE4_T_B_R_B,
      DLG_STRING_EFFECT_ROTATE4_T_B_T_L,
      DLG_STRING_EFFECT_ROTATE4_T_B_T_R,
      DLG_STRING_EFFECT_ROTATE4_T_B_T_T,
      DLG_STRING_EFFECT_ROTATE4_T_B_T_B,
      DLG_STRING_EFFECT_ROTATE4_T_B_B_L,
      DLG_STRING_EFFECT_ROTATE4_T_B_B_R,
      DLG_STRING_EFFECT_ROTATE4_T_B_B_T,
      DLG_STRING_EFFECT_ROTATE4_T_B_B_B,
      DLG_STRING_EFFECT_ROTATE4_B_L_L_L,
      DLG_STRING_EFFECT_ROTATE4_B_L_L_R,
      DLG_STRING_EFFECT_ROTATE4_B_L_L_T,
      DLG_STRING_EFFECT_ROTATE4_B_L_L_B,
      DLG_STRING_EFFECT_ROTATE4_B_L_R_L,
      DLG_STRING_EFFECT_ROTATE4_B_L_R_R,
      DLG_STRING_EFFECT_ROTATE4_B_L_R_T,
      DLG_STRING_EFFECT_ROTATE4_B_L_R_B,
      DLG_STRING_EFFECT_ROTATE4_B_L_T_L,
      DLG_STRING_EFFECT_ROTATE4_B_L_T_R,
      DLG_STRING_EFFECT_ROTATE4_B_L_T_T,
      DLG_STRING_EFFECT_ROTATE4_B_L_T_B,
      DLG_STRING_EFFECT_ROTATE4_B_L_B_L,
      DLG_STRING_EFFECT_ROTATE4_B_L_B_R,
      DLG_STRING_EFFECT_ROTATE4_B_L_B_T,
      DLG_STRING_EFFECT_ROTATE4_B_L_B_B,
      DLG_STRING_EFFECT_ROTATE4_B_R_L_L,
      DLG_STRING_EFFECT_ROTATE4_B_R_L_R,
      DLG_STRING_EFFECT_ROTATE4_B_R_L_T,
      DLG_STRING_EFFECT_ROTATE4_B_R_L_B,
      DLG_STRING_EFFECT_ROTATE4_B_R_R_L,
      DLG_STRING_EFFECT_ROTATE4_B_R_R_R,
      DLG_STRING_EFFECT_ROTATE4_B_R_R_T,
      DLG_STRING_EFFECT_ROTATE4_B_R_R_B,
      DLG_STRING_EFFECT_ROTATE4_B_R_T_L,
      DLG_STRING_EFFECT_ROTATE4_B_R_T_R,
      DLG_STRING_EFFECT_ROTATE4_B_R_T_T,
      DLG_STRING_EFFECT_ROTATE4_B_R_T_B,
      DLG_STRING_EFFECT_ROTATE4_B_R_B_L,
      DLG_STRING_EFFECT_ROTATE4_B_R_B_R,
      DLG_STRING_EFFECT_ROTATE4_B_R_B_T,
      DLG_STRING_EFFECT_ROTATE4_B_R_B_B,
      DLG_STRING_EFFECT_ROTATE4_B_T_L_L,
      DLG_STRING_EFFECT_ROTATE4_B_T_L_R,
      DLG_STRING_EFFECT_ROTATE4_B_T_L_T,
      DLG_STRING_EFFECT_ROTATE4_B_T_L_B,
      DLG_STRING_EFFECT_ROTATE4_B_T_R_L,
      DLG_STRING_EFFECT_ROTATE4_B_T_R_R,
      DLG_STRING_EFFECT_ROTATE4_B_T_R_T,
      DLG_STRING_EFFECT_ROTATE4_B_T_R_B,
      DLG_STRING_EFFECT_ROTATE4_B_T_T_L,
      DLG_STRING_EFFECT_ROTATE4_B_T_T_R,
      DLG_STRING_EFFECT_ROTATE4_B_T_T_T,
      DLG_STRING_EFFECT_ROTATE4_B_T_T_B,
      DLG_STRING_EFFECT_ROTATE4_B_T_B_L,
      DLG_STRING_EFFECT_ROTATE4_B_T_B_R,
      DLG_STRING_EFFECT_ROTATE4_B_T_B_T,
      DLG_STRING_EFFECT_ROTATE4_B_T_B_B,
      DLG_STRING_EFFECT_ROTATE4_B_B_L_L,
      DLG_STRING_EFFECT_ROTATE4_B_B_L_R,
      DLG_STRING_EFFECT_ROTATE4_B_B_L_T,
      DLG_STRING_EFFECT_ROTATE4_B_B_L_B,
      DLG_STRING_EFFECT_ROTATE4_B_B_R_L,
      DLG_STRING_EFFECT_ROTATE4_B_B_R_R,
      DLG_STRING_EFFECT_ROTATE4_B_B_R_T,
      DLG_STRING_EFFECT_ROTATE4_B_B_R_B,
      DLG_STRING_EFFECT_ROTATE4_B_B_T_L,
      DLG_STRING_EFFECT_ROTATE4_B_B_T_R,
      DLG_STRING_EFFECT_ROTATE4_B_B_T_T,
      DLG_STRING_EFFECT_ROTATE4_B_B_T_B,
      DLG_STRING_EFFECT_ROTATE4_B_B_B_L,
      DLG_STRING_EFFECT_ROTATE4_B_B_B_R,
      DLG_STRING_EFFECT_ROTATE4_B_B_B_T,
      DLG_STRING_EFFECT_ROTATE4_B_B_B_B,
      DLG_STRINGS6_MAX,
   }DlgStrings6;

   typedef enum
   {
      DLG_STRING_EFFECT_ZOOM_TO_C=DLG_STRINGS6_MAX,
      DLG_STRING_EFFECT_ZOOM_FROM_C,

      DLG_STRING_EFFECT_DRIP_T_TO_B,
      DLG_STRING_EFFECT_DRIP_B_TO_T,
      DLG_STRING_EFFECT_DRIP_L_TO_R,
      DLG_STRING_EFFECT_DRIP_R_TO_L,

      DLG_STRING_EFFECT_BLIND_T_TO_B,
      DLG_STRING_EFFECT_BLIND_L_TO_R,
      DLG_STRING_EFFECT_BLIND_GROWING_L_TO_R,
      DLG_STRING_EFFECT_BLIND_GROWING_R_TO_L,
      DLG_STRING_EFFECT_BLIND_GROWING_T_TO_B,
      DLG_STRING_EFFECT_BLIND_GROWING_B_TO_T,
      DLG_STRING_EFFECT_BLIND2_T_TO_B_AND_L_TO_R,

      DLG_STRING_EFFECT_RANDOM_BARS_R_TO_L,
      DLG_STRING_EFFECT_RANDOM_BARS_L_TO_R,
      DLG_STRING_EFFECT_RANDOM_BARS_B_TO_T,
      DLG_STRING_EFFECT_RANDOM_BARS_T_TO_B,
      DLG_STRING_EFFECT_RANDOM_LINES,
      DLG_STRING_EFFECT_RANDOM_BLOCKS,
      DLG_STRING_EFFECT_RANDOM_BLOCKS_R_TO_L,
      DLG_STRING_EFFECT_RANDOM_BLOCKS_L_TO_R,
      DLG_STRING_EFFECT_RANDOM_BLOCKS_B_TO_T,
      DLG_STRING_EFFECT_RANDOM_BLOCKS_T_TO_B,

      DLG_STRING_EFFECT_CHECKERBOARD_T_TO_B_THEN_T_TO_B,
      DLG_STRING_EFFECT_CHECKERBOARD_B_TO_T_THEN_B_TO_T,
      DLG_STRING_EFFECT_CHECKERBOARD_L_TO_R_THEN_L_TO_R,
      DLG_STRING_EFFECT_CHECKERBOARD_R_TO_L_THEN_R_TO_L,
      DLG_STRING_EFFECT_CHECKERBOARD_T_TO_B_THEN_B_TO_T,
      DLG_STRING_EFFECT_CHECKERBOARD_B_TO_T_THEN_T_TO_B,
      DLG_STRING_EFFECT_CHECKERBOARD_L_TO_R_THEN_R_TO_L,
      DLG_STRING_EFFECT_CHECKERBOARD_R_TO_L_THEN_L_TO_R,

      DLG_STRING_EFFECT_BLOCKS_T_TO_B,
      DLG_STRING_EFFECT_BLOCKS_B_TO_T,
      DLG_STRING_EFFECT_BLOCKS_L_TO_R,
      DLG_STRING_EFFECT_BLOCKS_R_TO_L,
      DLG_STRING_EFFECT_BLOCKS_SWIRL_CW_TO_C,
      DLG_STRING_EFFECT_BLOCKS_SWIRL_CW_FROM_C,
      DLG_STRING_EFFECT_BLOCKS_SWIRL_CCW_TO_C,
      DLG_STRING_EFFECT_BLOCKS_SWIRL_CCW_FROM_C,

      DLG_STRING_EFFECT_CIRCLE_C_IN,
      DLG_STRING_EFFECT_CIRCLE_C_OUT,
      DLG_STRING_EFFECT_CIRCLE_L_IN,
      DLG_STRING_EFFECT_CIRCLE_L_OUT,
      DLG_STRING_EFFECT_CIRCLE_R_IN,
      DLG_STRING_EFFECT_CIRCLE_R_OUT,
      DLG_STRING_EFFECT_CIRCLE_T_IN,
      DLG_STRING_EFFECT_CIRCLE_T_OUT,
      DLG_STRING_EFFECT_CIRCLE_B_IN,
      DLG_STRING_EFFECT_CIRCLE_B_OUT,
      DLG_STRING_EFFECT_CIRCLE_C_INTER_IN_THEN_IN,
      DLG_STRING_EFFECT_CIRCLE_C_INTER_OUT_THEN_OUT,
      DLG_STRING_EFFECT_CIRCLE_C_INTER_IN_THEN_OUT,
      DLG_STRING_EFFECT_CIRCLE_C_INTER_OUT_THEN_IN,
      DLG_STRING_EFFECT_CIRCLE_L_INTER_IN_THEN_IN,
      DLG_STRING_EFFECT_CIRCLE_L_INTER_OUT_THEN_OUT,
      DLG_STRING_EFFECT_CIRCLE_L_INTER_IN_THEN_OUT,
      DLG_STRING_EFFECT_CIRCLE_L_INTER_OUT_THEN_IN,
      DLG_STRING_EFFECT_CIRCLE_R_INTER_IN_THEN_IN,
      DLG_STRING_EFFECT_CIRCLE_R_INTER_OUT_THEN_OUT,
      DLG_STRING_EFFECT_CIRCLE_R_INTER_IN_THEN_OUT,
      DLG_STRING_EFFECT_CIRCLE_R_INTER_OUT_THEN_IN,
      DLG_STRING_EFFECT_CIRCLE_T_INTER_IN_THEN_IN,
      DLG_STRING_EFFECT_CIRCLE_T_INTER_OUT_THEN_OUT,
      DLG_STRING_EFFECT_CIRCLE_T_INTER_IN_THEN_OUT,
      DLG_STRING_EFFECT_CIRCLE_T_INTER_OUT_THEN_IN,
      DLG_STRING_EFFECT_CIRCLE_B_INTER_IN_THEN_IN,
      DLG_STRING_EFFECT_CIRCLE_B_INTER_OUT_THEN_OUT,
      DLG_STRING_EFFECT_CIRCLE_B_INTER_IN_THEN_OUT,
      DLG_STRING_EFFECT_CIRCLE_B_INTER_OUT_THEN_IN,
      DLG_STRING_EFFECT_CIRCLE_L_R_INTER,
      DLG_STRING_EFFECT_CIRCLE_T_B_INTER,
      DLG_STRING_EFFECT_CIRCLE2_L_R_OUT,
      DLG_STRING_EFFECT_CIRCLE2_L_R_IN,
      DLG_STRING_EFFECT_CIRCLE2_T_B_OUT,
      DLG_STRING_EFFECT_CIRCLE2_T_B_IN,

      DLG_STRING_EFFECT_ELLIPSE_C_IN,
      DLG_STRING_EFFECT_ELLIPSE_C_OUT,
      DLG_STRING_EFFECT_ELLIPSE_L_IN,
      DLG_STRING_EFFECT_ELLIPSE_L_OUT,
      DLG_STRING_EFFECT_ELLIPSE_R_IN,
      DLG_STRING_EFFECT_ELLIPSE_R_OUT,
      DLG_STRING_EFFECT_ELLIPSE_T_IN,
      DLG_STRING_EFFECT_ELLIPSE_T_OUT,
      DLG_STRING_EFFECT_ELLIPSE_B_IN,
      DLG_STRING_EFFECT_ELLIPSE_B_OUT,
      DLG_STRING_EFFECT_ELLIPSE_C_INTER_IN_THEN_IN,
      DLG_STRING_EFFECT_ELLIPSE_C_INTER_OUT_THEN_OUT,
      DLG_STRING_EFFECT_ELLIPSE_C_INTER_IN_THEN_OUT,
      DLG_STRING_EFFECT_ELLIPSE_C_INTER_OUT_THEN_IN,
      DLG_STRING_EFFECT_ELLIPSE_L_INTER_IN_THEN_IN,
      DLG_STRING_EFFECT_ELLIPSE_L_INTER_OUT_THEN_OUT,
      DLG_STRING_EFFECT_ELLIPSE_L_INTER_IN_THEN_OUT,
      DLG_STRING_EFFECT_ELLIPSE_L_INTER_OUT_THEN_IN,
      DLG_STRING_EFFECT_ELLIPSE_R_INTER_IN_THEN_IN,
      DLG_STRING_EFFECT_ELLIPSE_R_INTER_OUT_THEN_OUT,
      DLG_STRING_EFFECT_ELLIPSE_R_INTER_IN_THEN_OUT,
      DLG_STRING_EFFECT_ELLIPSE_R_INTER_OUT_THEN_IN,
      DLG_STRING_EFFECT_ELLIPSE_T_INTER_IN_THEN_IN,
      DLG_STRING_EFFECT_ELLIPSE_T_INTER_OUT_THEN_OUT,
      DLG_STRING_EFFECT_ELLIPSE_T_INTER_IN_THEN_OUT,
      DLG_STRING_EFFECT_ELLIPSE_T_INTER_OUT_THEN_IN,
      DLG_STRING_EFFECT_ELLIPSE_B_INTER_IN_THEN_IN,
      DLG_STRING_EFFECT_ELLIPSE_B_INTER_OUT_THEN_OUT,
      DLG_STRING_EFFECT_ELLIPSE_B_INTER_IN_THEN_OUT,
      DLG_STRING_EFFECT_ELLIPSE_B_INTER_OUT_THEN_IN,
      DLG_STRING_EFFECT_ELLIPSE_L_R_INTER,
      DLG_STRING_EFFECT_ELLIPSE_T_B_INTER,
      DLG_STRING_EFFECT_ELLIPSE2_L_R_OUT,
      DLG_STRING_EFFECT_ELLIPSE2_L_R_IN,
      DLG_STRING_EFFECT_ELLIPSE2_T_B_OUT,
      DLG_STRING_EFFECT_ELLIPSE2_T_B_IN,

      DLG_STRING_CR48BIT,
      DLG_STRING_CR64BIT,
      DLG_STRING_TIFF48,
      DLG_STRING_TIFF64,
      DLG_STRING_SUB_TIFF48_UNCOMPRESSEDRGB,
      DLG_STRING_SUB_TIFF48_LZWRGB,
      DLG_STRING_SUB_TIFF64_UNCOMPRESSEDRGB,
      DLG_STRING_SUB_TIFF64_LZWRGB,
      DLG_STRING_SUB_TIFF12_JPEG_GRAY_YCC,
      DLG_STRING_SUB_TIFF12_LZW,

      /* new in 11.5 - for rotate dialog box */
      DLG_STRING_ROTATENONESTR,
      DLG_STRING_ROTATERESAMPLESTR,
      DLG_STRING_ROTATEBICUBICSTR,

      /* new formats in 11.5 */
      DLG_STRING_FILE_FLI,
      DLG_STRING_FILE_FLC,
      DLG_STRING_FLC8,
      DLG_STRING_EXT_FLC,
      DLG_STRING_ANI1,
      DLG_STRING_ANI4,
      DLG_STRING_ANI8,
      DLG_STRING_ANI24,
      DLG_STRING_EXT_ANI,
      DLG_STRING_FILE_XWD10,
      DLG_STRING_FILE_XWD11,
      DLG_STRING_XWD10_1,
      DLG_STRING_XWD10_4,
      DLG_STRING_XWD10_8,
      DLG_STRING_XWD11_1,
      DLG_STRING_XWD11_4,
      DLG_STRING_XWD11_8,
      DLG_STRING_XWD11_16,
      DLG_STRING_XWD11_24,
      DLG_STRING_XWD11_32,
      DLG_STRING_EXT_XWD,
      DLG_STRING_FILE_CGM,
      DLG_STRING_FILE_DRW,
      DLG_STRING_FILE_PLT,
      DLG_STRING_SUB_TIFF1_JBIG,
      DLG_STRING_SUB_TIFFOTHER_JBIG,
      DLG_STRING_SUB_TIFF8_JBIG,
      DLG_STRING_SUB_TIFF8_CMP,
      DLG_STRING_SUB_TIFF24_CMP_NONPROGRESSIVE,
      DLG_STRING_SUB_TIFF24_CMP_PROGRESSIVE,
      DLG_STRING_FILE_TIF_CMP,
      DLG_STRING_FILE_TIF_JBIG,
      DLG_STRING_FILE_TIF_DXF,
      DLG_STRING_FILE_TIF_UNKNOWN,
      /* new formats in 12.0 */
      DLG_STRING_FILE_SGI,
      DLG_STRING_SGI8,
      DLG_STRING_SGI24,
      DLG_STRING_SGI32,
      DLG_STRING_EXT_SGI,
      /* SGI file subtypes */
      DLG_STRING_SUB_SGI_UNCOMPRESSED,
      DLG_STRING_SUB_SGI_RLECOMPRESSED,

      DLG_STRING_SUB_TIFF12_RLE,

      DLG_STRING_FILE_CLP,
      DLG_STRING_CLP1,
      DLG_STRING_CLP4,
      DLG_STRING_CLP8,
      DLG_STRING_CLP24,
      DLG_STRING_EXT_CLP,
      DLG_STRING_FILE_RAW,
      DLG_STRING_RAW,
      DLG_STRING_EXT_RAW,

      DLG_STRING_SUB_PDF1_UNCOMPRESSED,
      DLG_STRING_SUB_PDF1_CCITT_G3_1D,
      DLG_STRING_SUB_PDF1_CCITT_G3_2D,
      DLG_STRING_SUB_PDF1_CCITT_G4,

      DLG_STRING_SUB_PDF8_UNCOMPRESSED,
      DLG_STRING_SUB_PDF8_LOSSLESSJPEG,
      DLG_STRING_SUB_PDF24_UNCOMPRESSED,
      DLG_STRING_SUB_PDF24_YUV_444,
      DLG_STRING_SUB_PDF24_YUV_422,
      DLG_STRING_SUB_PDF24_YUV_411,
      DLG_STRING_FILE_PDF,
      DLG_STRING_PDF1,
      DLG_STRING_PDF2,
      DLG_STRING_PDF4,
      DLG_STRING_PDF8,
      DLG_STRING_PDF24,
      DLG_STRING_EXT_PDF,
      DLG_STRING_PDFCAPTION,
      DLG_STRING_PDFHRESOLUTION,
      DLG_STRING_PDFVRESOLUTION,
      DLG_STRING_PDFDISPLAYDEPTH, 
      DLG_STRING_PDFTEXTALPHA,
      DLG_STRING_PDFGRAPHICSALPHA,
      DLG_STRING_PDFDPI,
      DLG_STRING_PDFBPP,
      DLG_STRING_PDFBITS,
      DLG_STRING_J2K8,
      DLG_STRING_J2K24,
      DLG_STRING_CMW8,
      DLG_STRING_CMW24,
      DLG_STRING_SUB_J2K,
      DLG_STRING_SUB_JP2,
      DLG_STRING_EXT_EXIF_JPEG,
      DLG_STRING_EXT_J2K,
      DLG_STRING_EXT_JP2,
      DLG_STRING_EXT_CMW,
      DLG_STRING_FILE_CMW,
      DLG_STRING_FILE_J2K,
      DLG_STRING_FILE_JP2,
      DLG_STRING_J2KLOSSLESS,
      DLG_STRING_J2KCOMPRATIO,
      DLG_STRING_J2KTARGETSIZE,
      DLG_STRING_J2KQFACTOR,
      DLG_STRING_J2KQUALITY,
      DLG_STRING_J2KRESOLUTION1,
      DLG_STRING_J2KRESOLUTION2,
      DLG_STRING_J2KCOLOR,
      DLG_STRING_J2KPOSITION,
      DLG_STRING_FILESAVE95J2KCOMPRESSIONCONTROLLABEL,
      DLG_STRING_FILESAVE95J2KPROGRESSIONORDERLABEL,
      DLG_STRING_FILESAVE95J2KCOMPRESSIONRATIOLABEL,
      DLG_STRING_FILESAVE95J2KTARGETSIZELABEL,
      DLG_STRING_FILESAVE95J2KADVANCED,

      DLG_STRING_J2KCAPTION,

      DLG_STRING_J2KXOSIZLABEL,
      DLG_STRING_J2KYOSIZLABEL,
      DLG_STRING_J2KXTSIZLABEL,
      DLG_STRING_J2KYTSIZLABEL,
      DLG_STRING_J2KXTOSIZLABEL,
      DLG_STRING_J2KYTOSIZLABEL,
      DLG_STRING_J2KCOLORTRANSFORM,
      DLG_STRING_J2KDERIVEDQUANTIZATION,
      DLG_STRING_J2KUSESOPMARKER,
      DLG_STRING_J2KUSEEPFMARKER,
      DLG_STRING_J2KDECOMPLEVELLABEL,
      DLG_STRING_J2KGUARDBITSLABEL,
      DLG_STRING_J2KMANTISSALABEL,
      DLG_STRING_J2KEXPONENTLABEL,
      DLG_STRING_J2KCODEBLOCKWIDTHLABEL,
      DLG_STRING_J2KCODEBLOCKHEIGHTLABEL,
      DLG_STRING_J2KSELECTIVEACBYPASS,
      DLG_STRING_J2KRESETCONTEXT,
      DLG_STRING_J2KTERMINATION,
      DLG_STRING_J2KVERTICALLYCAUSAL,
      DLG_STRING_J2KPREDICTABLETERMINATION,
      DLG_STRING_J2KERRORRESILIENCE,
      DLG_STRING_J2KDEFAULT,
      DLG_STRING_J2KOFFSETANDTILING,
      DLG_STRING_J2KGENERAL1,
      DLG_STRING_J2KGENERAL2,
      DLG_STRING_J2KARITHMETICENCODER,
      DLG_STRING_J2KOKSTR,
      DLG_STRING_J2KCANCELSTR,
      DLG_STRING_FILE_TIF_J2K,
      DLG_STRING_FILE_TIF_CMW,
      DLG_STRING_SUB_TIFF8_J2K,
      DLG_STRING_SUB_TIFF8_CMW,
      DLG_STRING_SUB_TIFF24_J2K,
      DLG_STRING_SUB_TIFF24_CMW,
   
      DLG_STRING_SUB_TIFF12_J2K,
      DLG_STRING_SUB_TIFF12_CMW,
      DLG_STRING_SUB_TIFF16_J2K,
      DLG_STRING_SUB_TIFF16_CMW,
      DLG_STRING_J2K12,
      DLG_STRING_J2K16,
      DLG_STRING_CMW12,
      DLG_STRING_CMW16,

      DLG_STRING_SCB_PATHS,
      DLG_STRING_SCB_HISTORY,
      DLG_STRING_SCB_MYDOCUMENTS,
      DLG_STRING_SCB_DESKTOP,
      DLG_STRING_SCB_FAVORITES,
      DLG_STRING_SCB_OPTIONS,

      DLG_STRING_FILEINFO_ITEM,
      DLG_STRING_FILEINFO_VALUE,

      //Image dialogs
      DLG_STRING_BEFORESTR,
      DLG_STRING_AFTERSTR,

      DLG_STRING_NORMALSTR,
      DLG_STRING_INTERPOLATIONSTR,
      DLG_STRING_AUTOTRIMSTR,

      // Image Resize dialog
      DLG_STRING_GETSIZE,
      DLG_STRING_GETSIZE_ORIGINAL,
      DLG_STRING_GETSIZE_NEW,
      DLG_STRING_GETSIZE_IDENTICALVALUE,
      DLG_STRING_GETSIZE_WIDTH,
      DLG_STRING_GETSIZE_HEIGHT,
      DLG_STRING_GETSIZE_SIZE,
      DLG_STRING_GETSIZE_RESOLUTION,
      DLG_STRING_GETSIZE_HORIZONTAL,
      DLG_STRING_GETSIZE_VERTICAL,
      DLG_STRING_GETSIZE_METHOD,
      DLG_STRING_GETSIZE_NORMAL,
      DLG_STRING_GETSIZE_FAVORBLACK,
      DLG_STRING_GETSIZE_RESAMPLE,
      DLG_STRING_GETSIZE_BICUBIC,
      DLG_STRING_GETSIZE_MAINTAINAR,

      // color res dialog 
      DLG_STRING_COLORRES_OPENPALETTE,
      DLG_STRING_COLORRES_SVGA,
      DLG_STRING_COLORRES_UNIFORM,
      DLG_STRING_COLORRES_MSIE,
      DLG_STRING7_MAX
   }DlgStrings7;

   typedef enum
   {
      //the Color Picker page
      DLG_STRING_CLRPCKR = DLG_STRING7_MAX,
      DLG_STRING_CLRPCKR_NAME,
      DLG_STRING_CLRPCKR_RGB,
      DLG_STRING_CLRPCKR_HSB,
      DLG_STRING_CLRPCKR_HLS,
      DLG_STRING_CLRPCKR_CMY,
      DLG_STRING_CLRPCKR_CMYK,
      DLG_STRING_CLRPCKR_LAB,

      // the Canvas resize dialog
      DLG_STRING_CANVASRESIZE,
      DLG_STRING_CANVASRESIZE_SIZE,
      DLG_STRING_CANVASRESIZE_NEWWIDTH,
      DLG_STRING_CANVASRESIZE_NEWHEIGHT,
      DLG_STRING_CANVASRESIZE_MAINTAINAR,
      DLG_STRING_CANVASRESIZE_CURRENTWIDTH,
      DLG_STRING_CANVASRESIZE_CURRENTHIGHT,
      DLG_STRING_CANVASRESIZE_POSITION,
      DLG_STRING_CANVASRESIZE_HORIZENTAL,
      DLG_STRING_CANVASRESIZE_LEFT,
      DLG_STRING_CANVASRESIZE_RIGHT,
      DLG_STRING_CANVASRESIZE_VERTICAL,
      DLG_STRING_CANVASRESIZE_TOP,
      DLG_STRING_CANVASRESIZE_BOTTOM,
      DLG_STRING_CANVASRESIZE_CENTER,
      DLG_STRING_CANVASRESIZE_CUSTOM,
      DLG_STRING_CANVASRESIZE_BKGCOLOR,

      // Picturize dialog
      DLG_STRING_PICTURIZE,
      DLG_STRING_PICTURIZE_CELLWIDTH,
      DLG_STRING_PICTURIZE_CELLHEIGHT,
      DLG_STRING_PICTURIZE_OPTIONS,
      DLG_STRING_PICTURIZE_RESIZE,
      DLG_STRING_PICTURIZE_RESAMPLE,
      DLG_STRING_PICTURIZE_BESTFIT,

      // Browse for directory dialog <used internally>
      DLG_STRING_BROWSEDIRECTORY,
      DLG_STRING_BROWSEDIRECTORY_REFRESH,
      DLG_STRING_BROWSEDIRECTORY_SETTINGS,
      DLG_STRING_BROWSEDIRECTORY_DISPLAYDESK,
      DLG_STRING_BROWSEDIRECTORY_RCLKPOPUP,
      DLG_STRING_BROWSEDIRECTORY_ONLYSYSFILEFOLDER,
      DLG_STRING_BROWSEDIRECTORY_FILES,
      DLG_STRING_BROWSEDIRECTORY_NOTIFYERROR,

      //Common Menu Item
      DLG_STRING_HSBHUE,
      DLG_STRING_HSBWHEEL,
      DLG_STRING_HSBBRIGHT,
      DLG_STRING_RGBADDITIVE,
      DLG_STRING_CMYSUBTRACT,
      DLG_STRING_CMYKSUBTRACT,
      DLG_STRING_LABDEVICEIND,

      // the Palette Editor dialog 
      DLG_STRING_PALEDTR,
      DLG_STRING_PALEDTR_PALETTE,
      DLG_STRING_PALEDTR_IMAGECLR,
      DLG_STRING_PALEDTR_UNIFORM,
      DLG_STRING_PALEDTR_GRAYSCALE,
      DLG_STRING_PALEDTR_NETSCAPE,
      DLG_STRING_PALEDTR_MICROSOFTIE,
      DLG_STRING_PALEDTR_STANDERDVGA,
      DLG_STRING_PALEDTR_SYSTEMCOLOR,
      DLG_STRING_PALEDTR_REPLACE,
      DLG_STRING_PALEDTR_ADD,
      DLG_STRING_PALEDTR_ATTHEEND,
      DLG_STRING_PALEDTR_AFTERSELECTED,
      DLG_STRING_PALEDTR_BEFORESELECTED,
      DLG_STRING_PALEDTR_REMOVE,
      DLG_STRING_PALEDTR_CONFIRM,
      DLG_STRING_PALEDTR_FINDCLOSEST,
      DLG_STRING_PALEDTR_SORT,
      DLG_STRING_PALEDTR_HSB,
      DLG_STRING_PALEDTR_HUE,
      DLG_STRING_PALEDTR_SATURATION,
      DLG_STRING_PALEDTR_BRIGHTNESS,
      DLG_STRING_PALEDTR_RGBMNU,
      DLG_STRING_PALEDTR_REVERSE,
      DLG_STRING_PALEDTR_COLORMODEL,
      DLG_STRING_PALEDTR_PALETTEMNU,
      DLG_STRING_PALEDTR_NEW,
      DLG_STRING_PALEDTR_OPEN,
      DLG_STRING_PALEDTR_SAVE,
      DLG_STRING_PALEDTR_SAVEAS,
      DLG_STRING_PALEDTR_RGB,
      DLG_STRING_PALEDTR_HTML,
      DLG_STRING_PALEDTR_INDEX,
      DLG_STRING_PALEDTR_HTML_FORMAT,
      DLG_STRING_PALEDTR_RGB_FORMAT,
      DLG_STRING_PALEDTR_INDEX_FORMAT,
      // the error messages
      DLG_STRING_PALEDTR_ERR_SAVETITLE,
      DLG_STRING_PALEDTR_ERR_ERRORTITLE,
      DLG_STRING_PALEDTR_ERR_OPENTITLE,
      DLG_STRING_PALEDTR_ERR_WARNINGTITLE,

      DLG_STRING_PALEDTR_ERR_NOT_PALETTE,
      DLG_STRING_PALEDTR_ERR_LOSE_CHANGES,
      DLG_STRING_PALEDTR_ERR_NO_SELECTION,
      DLG_STRING_PALEDTR_ERR_FIND_CLOSEST,
      DLG_STRING_PALEDTR_ERR_NO_RIGHT_SEL,
      DLG_STRING_PALEDTR_ERR_ADD_SELECTION,
      DLG_STRING_PALEDTR_ERR_MAX_COLORS,
      DLG_STRING_PALEDTR_ERR_DUPLICATE_CLR,
      DLG_STRING_PALEDTR_ERR_DUPLCLR_NO_INDEX,
      DLG_STRING_PALEDTR_ERR_CONFIRM_REMOVE,
      DLG_STRING_PALEDTR_ERR_IN_RIGHT_PAN,
      DLG_STRING_PALEDTR_ERR_FIND_CLOSEST_SEL,
      DLG_STRING_PALEDTR_ERR_COUNT_DIFFER,
      DLG_STRING_PALEDTR_ERR_MULTIPLE_BY_ONE,

      // Optemizer dialogs
      DLG_STRING_PNGOPTIMIZER,
      DLG_STRING_GIFOPTIMIZER,
      DLG_STRING_JPEGOPTIMIZER,

      DLG_STRING_OPTIMIZER_UNCOMPRESSED,
      DLG_STRING_OPTIMIZER_COMPRESSED,
      DLG_STRING_OPTIMIZER_ERROR,
      DLG_STRING_OPTIMIZER_WAIT,

      DLG_STRING_OPTIMIZER_144KBS,
      DLG_STRING_OPTIMIZER_288KBS,
      DLG_STRING_OPTIMIZER_56KBS,
      DLG_STRING_OPTIMIZER_128KBS,
      DLG_STRING_OPTIMIZER_266KBS,
      DLG_STRING_OPTIMIZER_NEARESTCLRMATCH,
      DLG_STRING_OPTIMIZER_FLOYDSTEINBERG,
      DLG_STRING_OPTIMIZER_STUCKI,
      DLG_STRING_OPTIMIZER_BURKES,
      DLG_STRING_OPTIMIZER_SIERRA,
      DLG_STRING_OPTIMIZER_STEVENSON,
      DLG_STRING_OPTIMIZER_JARVUIS,
      DLG_STRING_OPTIMIZER_ORDERED,
      DLG_STRING_OPTIMIZER_CLUSTERED,
      DLG_STRING_OPTIMIZER_COLORS,
      DLG_STRING_OPTIMIZER_COLORDEPTH,
      DLG_STRING_OPTIMIZER_PALETTE,
      DLG_STRING_OPTIMIZER_AUTOMATIC,
      DLG_STRING_OPTIMIZER_FIXED,
      DLG_STRING_OPTIMIZER_CUSTOM,
      DLG_STRING_OPTIMIZER_DITHERING,
      DLG_STRING_OPTIMIZER_NUMOFCOLORS,
      DLG_STRING_OPTIMIZER_ADDWINCOLORS,
      DLG_STRING_OPTIMIZER_TRANSPARENCY,
      DLG_STRING_OPTIMIZER_ENABLED,
      DLG_STRING_OPTIMIZER_TOLERANCE,
      DLG_STRING_OPTIMIZER_TRANSPARENTCLR,
      DLG_STRING_OPTIMIZER_INFORMATIONS,
      DLG_STRING_OPTIMIZER_BAUDRATE,
      DLG_STRING_OPTIMIZER_ESTIMATEDTIME,
      DLG_STRING_OPTIMIZER_OPTIONS,
      DLG_STRING_OPTIMIZER_INTERLACED,
      DLG_STRING_OPTIMIZER_IMAGETYPE,
      DLG_STRING_OPTIMIZER_COMPRESSION, 
      DLG_STRING_OPTIMIZER_PROGRESSIVE,
      DLG_STRING_OPTIMIZER_SAVETHUMBNAIL,
      DLG_STRING_OPTIMIZER_YUV444,
      DLG_STRING_OPTIMIZER_YUV422,
      DLG_STRING_OPTIMIZER_YUV411,

      //Image Formats File Association Dialog
      DLG_STRING_FILEASS,
      DLG_STRING_FILEASS_FORMAT,
      DLG_STRING_FILEASS_DESCRP,

      DLG_STRING_FILEASS_SELECTALL,
      DLG_STRING_FILEASS_SELECTNONE,

      //Image Mapper dialog
      DLG_STRING_HTMLMAP,
      DLG_STRING_HTMLMAP_AREAINFO,
      DLG_STRING_HTMLMAP_URL,
      DLG_STRING_HTMLMAP_ALTTEXT,
      DLG_STRING_HTMLMAP_TARGET,
      DLG_STRING_HTMLMAP_OUTPUT,
      DLG_STRING_HTMLMAP_IMAGEFORMAT,
      DLG_STRING_HTMLMAP_JPGFORMAT,
      DLG_STRING_HTMLMAP_GIFFORMAT,
      DLG_STRING_HTMLMAP_PNGFORMAT,
      DLG_STRING_HTMLMAP_GENERATESEL,
      DLG_STRING_HTMLMAP_OPTIMIZED,
      DLG_STRING_HTMLMAP_ROLLOVER,
      DLG_STRING_HTMLMAP_EVENT,
      DLG_STRING_HTMLMAP_ONCLICK,
      DLG_STRING_HTMLMAP_ONDBLCLICK,
      DLG_STRING_HTMLMAP_ONMMOUSEDOWN,
      DLG_STRING_HTMLMAP_ONMMOUSEOVER,
      DLG_STRING_HTMLMAP_ONMMOUSEUP,
      DLG_STRING_HTMLMAP_ONMMOUSEOUT,
      DLG_STRING_HTMLMAP_ENABLED,
      DLG_STRING_HTMLMAP_IMAGE,
      DLG_STRING_HTMLMAP_CURSORPOSITION,
      DLG_STRING_HTMLMAP_CLOSE,

      //Image Mapper dialog Error Messages
      DLG_STRING_HTMLMAP_OUTMEM,
      DLG_STRING_HTMLMAP_PNF,
      DLG_STRING_HTMLMAP_FNF,
      DLG_STRING_HTMLMAP_FORMAT,
      DLG_STRING_HTMLMAP_ACCESSDENIED,
      DLG_STRING_HTMLMAP_ASSOCINCOMPLETE,
      DLG_STRING_HTMLMAP_DDEBUSY,
      DLG_STRING_HTMLMAP_DDEFAIL,
      DLG_STRING_HTMLMAP_DDETIMEOUT,
      DLG_STRING_HTMLMAP_DLLNOTFOUND,
      DLG_STRING_HTMLMAP_NOASSOC,
      DLG_STRING_HTMLMAP_OOM,
      DLG_STRING_HTMLMAP_SHARE,
      DLG_STRING_HTMLMAP_UNNONE,
      DLG_STRING_HTMLMAP_DEFAULT,

      // The New Dialog 
      DLG_STRING_NEW,
      DLG_STRING_NEW_NAME,
      DLG_STRING_NEW_WIDTH,
      DLG_STRING_NEW_HEIGHT,
      DLG_STRING_NEW_PIXELS,
      DLG_STRING_NEW_INCHES,
      DLG_STRING_NEW_CENTIMETERS,
      DLG_STRING_NEW_RESOLUTION,
      DLG_STRING_NEW_PIXELPERINCHE,
      DLG_STRING_NEW_PIXELPERCM,
      DLG_STRING_NEW_IMAGETYPE,
      DLG_STRING_NEW_2COLORS,
      DLG_STRING_NEW_16COLORS,
      DLG_STRING_NEW_256COLORS,
      DLG_STRING_NEW_256GRAYSCALE,
      DLG_STRING_NEW_65536COLORS,
      DLG_STRING_NEW_167MCOLORS,
      DLG_STRING_NEW_IMAGEMEMSIZE,
      DLG_STRING_NEW_BACKCOLOR,

      // Combine Image Dialog strings
      DLG_STRING_COMBINE,
      DLG_STRING_COMBINE_SOURCE1,
      DLG_STRING_COMBINE_SOURCE2,
      DLG_STRING_COMBINE_IMAGE,
      DLG_STRING_COMBINE_CHANEL,
      DLG_STRING_COMBINE_BLUE,
      DLG_STRING_COMBINE_RED,
      DLG_STRING_COMBINE_GREEN,
      DLG_STRING_COMBINE_INVERT,
      DLG_STRING_COMBINE_OPTIONS,
      DLG_STRING_COMBINE_FUNCTION,
      DLG_STRING_COMBINE_ADD,
      DLG_STRING_COMBINE_SUBT1,
      DLG_STRING_COMBINE_SUBT2,
      DLG_STRING_COMBINE_MULTI,
      DLG_STRING_COMBINE_DIV1,
      DLG_STRING_COMBINE_DIV2,
      DLG_STRING_COMBINE_MIN,
      DLG_STRING_COMBINE_MAX,
      DLG_STRING_COMBINE_AVERAGE,
      DLG_STRING_COMBINE_AND,
      DLG_STRING_COMBINE_OR,
      DLG_STRING_COMBINE_XOR,
      DLG_STRING_COMBINE_ALL,
      DLG_STRING_COMBINE_RESIZE,
      DLG_STRING_COMBINE_RESULTING,
      DLG_STRING_COMBINE_COLORDEPTH,

      //Halftone dialog 
      DLG_STRING_HALFTONE_TYPE,
      DLG_STRING_HALFTONE_PRINT,
      DLG_STRING_HALFTONE_VIEW,

      //Gamma Dialog
      DLG_STRING_GAMMA,
      DLG_STRING_GAMMA_RED,
      DLG_STRING_GAMMA_GREEN,
      DLG_STRING_GAMMA_BLUE,
      DLG_STRING_GAMMA_ALLCHNNELS,

      //Underlay dialog
      DLG_STRING_UNDERLAY,
      DLG_STRING_UNDERLAY_SETTINGS,
      DLG_STRING_UNDERLAY_STRETCHED,
      DLG_STRING_UNDERLAY_TILED,
      DLG_STRING_UNDERLAY_ERR,
      DLG_STRING_UNDERLAY_ERR_INITAL,

      //Selection Feather Dialog
      DLG_STRING_FEATHER,
      DLG_STRING_FEATHER_PLACEMENT,
      DLG_STRING_FEATHER_GROW,
      DLG_STRING_FEATHER_INSIDE,
      DLG_STRING_FEATHER_OUTSIDE,
      DLG_STRING_FEATHER_FACTORS,
      DLG_STRING_FEATHER_SIZE,
      DLG_STRING_FEATHER_SMOOTHNESS,
      DLG_STRING_FEATHER_FADERATE,
      DLG_STRING_FEATHER_AUTOFADERATE,

      // Add Border Dialog strings
      DLG_STRING_ADDBORDER,
      DLG_STRING_ADDBORDER_MARGINS,
      DLG_STRING_ADDBORDER_LEFT,
      DLG_STRING_ADDBORDER_RIGHT,
      DLG_STRING_ADDBORDER_TOP,
      DLG_STRING_ADDBORDER_BOTTOM,
      DLG_STRING_ADDBORDER_PLACEMENT,
      DLG_STRING_ADDBORDER_INSIDE,
      DLG_STRING_ADDBORDER_OUTSIDE,
      DLG_STRING_ADDBORDER_LOCKMARGINS,
      DLG_STRING_ADDBORDER_BORDERSTYLE,
      DLG_STRING_ADDBORDER_SAMEIMAGE,
      DLG_STRING_ADDBORDER_OPAQUE,
      DLG_STRING_ADDBORDER_GRADIENT,
      DLG_STRING_ADDBORDER_TILES,
      DLG_STRING_ADDBORDER_OPTIONS,
      DLG_STRING_ADDBORDER_INSIDEOUT,
      DLG_STRING_ADDBORDER_CENTEROUT1,
      DLG_STRING_ADDBORDER_CENTEROUT2,
      DLG_STRING_ADDBORDER_STARTCOLOR,
      DLG_STRING_ADDBORDER_ENDCOLOR,
      DLG_STRING_ADDBORDER_TILEIMAGE,
      DLG_STRING_ADDBORDER_PRESETS,
      DLG_STRING_ADDBORDER_USERDEFINE,
      DLG_STRING_ADDBORDER_SIMPLE,
      DLG_STRING_ADDBORDER_PRESET1,
      DLG_STRING_ADDBORDER_PRESET2,
      DLG_STRING_ADDBORDER_PRESET3,
      DLG_STRING_ADDBORDER_PRESET4,
      DLG_STRING_ADDBORDER_PRESET5,
      DLG_STRING_ADDBORDER_PRESET6,
      DLG_STRING_ADDBORDER_PRESET7,
      DLG_STRING_ADDBORDER_PRESET8,
      DLG_STRING_ADDBORDER_PRESET9,
      DLG_STRING_ADDBORDER_SHADOWS,
      DLG_STRING_ADDBORDER_NONESHADOWSLST,
      DLG_STRING_ADDBORDER_ADDSHADOWSLST,
      DLG_STRING_ADDBORDER_LEFTLST,
      DLG_STRING_ADDBORDER_RIGHTLST,
      DLG_STRING_ADDBORDER_SURROUNDLST,
      DLG_STRING_ADDBORDER_BUMPED,
      DLG_STRING_ADDBORDER_SIZE,
      DLG_STRING_ADDBORDER_EFFECT,
      DLG_STRING_ADDBORDER_NONEEFFECT,
      DLG_STRING_ADDBORDER_CURVEDIN,
      DLG_STRING_ADDBORDER_CURVEDOUT,
      DLG_STRING_ADDBORDER_RAISED,
      DLG_STRING_ADDBORDER_LOWERED,
      DLG_STRING_ADDBORDER_INTENSITY,
      DLG_STRING_ADDBORDER_SMOOTH,

      // Add Frame Dialog strings
      DLG_STRING_ADDFRAME,
      DLG_STRING_ADDFRAME_OPTIONS,
      DLG_STRING_ADDFRAME_PLACEMENT,
      DLG_STRING_ADDFRAME_INSIDE,
      DLG_STRING_ADDFRAME_OUTSIDE,
      DLG_STRING_ADDFRAME_FRAME,
      DLG_STRING_ADDFRAME_MASK,
      DLG_STRING_ADDFRAME_USEMASK,
      DLG_STRING_ADDFRAME_TOLERANCE,
      DLG_STRING_ADDFRAME_TRANSPARENTCOLOR,

      DLG_STRING_FILE_GERBER,
      DLG_STRING_FILE_WBMP,
      DLG_STRING_FILE_PTOCA,
      DLG_STRING_FILE_SCT,
      DLG_STRING_FILE_SCT24,
      DLG_STRING_FILE_PCL,
      DLG_STRING_FILE_AFP,
      DLG_STRING_FILE_SHP,
      DLG_STRING_SUB_ICA_UNCOMPRESSED,
      DLG_STRING_SUB_RAWICA_UNCOMPRESSED,

      // old file format but updated
      DLG_STRING_SUB_ICA_IBM_MMR,
      DLG_STRING_SUB_RAWICA_IBM_MMR,

      DLG_STRING_EXT_GERBER,
      DLG_STRING_EXT_WBMP,
      DLG_STRING_EXT_PTOCA, 
      DLG_STRING_EXT_SCT,
      DLG_STRING_EXT_PCL,
      DLG_STRING_EXT_AFP,
      DLG_STRING_EXT_SHP,

      DLG_STRING_SUB_JPEG24_LAB_444,
      DLG_STRING_SUB_JPEG24_LAB_422,
      DLG_STRING_SUB_JPEG24_LAB_411,

      DLG_STRING_PALEDTR_CLOSE,

      DLG_STRING_GETSIZE_WIDTHNEW,
      DLG_STRING_GETSIZE_HEIGHTNEW,
      DLG_STRING_GETSIZE_HORIZONTALNEW,
      DLG_STRING_GETSIZE_VERTICALNEW,

      DLG_STRING_FILE_SMP,
      DLG_STRING_EXT_SMP,
      DLG_STRING_SUB_SMP_CCITT_GROUP3_1D,
      DLG_STRING_SUB_SMP_CCITT_GROUP3_2D,
      DLG_STRING_SUB_SMP_CCITT_GROUP4,
      DLG_STRING_SUB_SMP_UNCOMPRESSED,

      DLG_STRING_SUB_TGA_RLE,
      DLG_STRING_SUB_TGA_UNCOMPRESSED,

      // The Strins of toolbar tooltip in the dialogs 
      DLG_STRING_TOOLTIP_ZOOMNORMALSTR = 3519,
      DLG_STRING_TOOLTIP_ZOOMTOFITSTR,
      DLG_STRING_CMWRESPROMPT,
      DLG_STRING_CMWRESLABEL,
      DLG_STRING_J2KRESPROMPT,
      DLG_STRING_J2KRESLABEL,

      DLG_STRING_MAX
   }DlgStrings8;
