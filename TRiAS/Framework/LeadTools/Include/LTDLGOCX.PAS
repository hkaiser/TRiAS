unit LTDLGOCX;
interface

const

  {HelpEventConstants}
  DLG_HELP_FILEOPEN    = 1;
  DLG_HELP_FILEOPEN95  = 2;
  DLG_HELP_FILESAVE    = 3;
  DLG_HELP_FILESAVE95  = 4;
  DLG_HELP_COLORRES    = 5;
  DLG_HELP_GETANGLE    = 6;
  DLG_HELP_GETSIZE     = 7;
  DLG_HELP_GETFILTER   = 8;
  DLG_HELP_GETCHANGE   = 9; 
  DLG_HELP_GETRANGE    = 10; 
  DLG_HELP_GETGAMMA    = 11; 
  DLG_HELP_GETNOISE    = 12; 
  DLG_HELP_GETEMBOSS   = 13;
  DLG_HELP_WINDOWLEVEL = 14;
  DLG_HELP_GETEFFECT   = 15;
  DLG_HELP_GETSHAPE    = 16;
  DLG_HELP_GETTEXT     = 17;
  DLG_HELP_GETGRADIENT = 18;
  DLG_HELP_GETTRANSITION = 19;
  DLG_HELP_GETDIR      = 20;
  DLG_HELP_GETDIR95    = 21;
  DLG_HELP_GETRES      = 22;
  DLG_HELP_CONTOUR     = 23;

  {FilterTypeConstants}
  FLT_SPATIAL          = 0;
  FLT_BINARY           = 1;

  {FileOpenDlgConstants}
  DLG_FO_AUTOPROCESS    = $00000001; {Dlg should autoprocess image and fill the pBitmap}
  DLG_FO_PROGRESSIVE    = $00000002; {FileOpen Dlg should have Prog. File options}
  DLG_FO_MULTIPAGE      = $00000004; {FileOpen Dlg should have Multipage options}
  DLG_FO_LOADROTATED    = $00000008; {FileOpen Dlg should have Load Rotated option}
  DLG_FO_LOADCOMPRESSED = $00000010; {FileOpen Dlg should have Load 1-bit compressed option}
  DLG_FO_FILEINFO       = $00000020; {FileOpen Dlg should have FileInfo button}
  DLG_FO_SHOWPREVIEW    = $00000040; {FileOpen Dlg should have ThumbNail and should create the}
                                     {preview if none is stored in the file}
  DLG_FO_SHOWSTAMP      = $00000080; {* FileOpen Dlg should have ThumbNail and should only load} 
                                     {the preview stamp if one is stored in the file}
  DLG_FO_95STYLE        = $00000100; {* FileOpen Dlg should have Windows95 Explorer style look}
  DLG_FO_DELPAGE        = $00000200; {* FileOpen Dlg should have Delete Page button}
  DLG_FO_RESDLG         = $00000400; {* If AutoProcess, and format supports resolution, show GetRes dlg}
  DLG_FO_NOFILEMUSTEXIST     = $00000800; {* Do not verify that the path exists *}
  DLG_FO_NOPATHMUSTEXIST     = $00001000; {* Do not verify that the file exists *}
  DLG_GETRES_95CONTEXTHELP   = $00002000; {* GetRes Dlg should contain context sensitive help icon *}
  DLG_FO_FILEINFO_TOTALPAGES = $00004000; {* when filling FILEINFO, get TOTALPAGES *}
  DLG_FO_FILEINFO_PDFDLG	 = $00008000; {* If AutoProcess, and format is PDF , show PDF options dlg *}

  {FileSaveDlgConstants}
  DLG_FS_AUTOPROCESS  =  $00000001;   {Dlg should autoprocess image and fill the pBitmap}
  DLG_FS_PROGRESSIVE  =  $00000002;   {FileSave Dlg should have Prog. File options}
  DLG_FS_MULTIPAGE    =  $00000004;   {FileSave Dlg should have Multipage options }
  DLG_FS_STAMP        =  $00000008;   {FileSave Dlg should have save with stamp options}
  DLG_FS_QFACTOR      =  $00000010;   {FileSave Dlg should have QFactor option }
  DLG_FS_95STYLE      =  $00000020;   {FileSave Dlg should have Windows95 Explorer style look}
  DLG_FO_NOFILEMUSTEXIST   = $00000800; {Do not verify that the path exists}
  DLG_FO_NOPATHMUSTEXIST   = $00001000; {Do not verify that the file exists}
  DLG_GETRES_95CONTEXTHELP = $00002000; {GetRes Dlg should contain context sensitive help icon}

{ file save format option constants for L_DlgFileSave}
{ top-level formats }
   DLG_FS_LEAD24     = 0;   
   DLG_FS_LEAD8      = 1;
   DLG_FS_LEAD1BIT   = 2;
   DLG_FS_JFIF24     = 3;
   DLG_FS_JFIF16     = 4;
   DLG_FS_JFIF12     = 5;
   DLG_FS_JFIF8      = 6;
   DLG_FS_CALS       = 7;
   DLG_FS_PNG1       = 8;
   DLG_FS_PNG4       = 9;
   DLG_FS_PNG8       = 10;
   DLG_FS_PNG24      = 11;
   DLG_FS_PNG32      = 12;
   DLG_FS_DICOM8     = 13;
   DLG_FS_DICOM16    = 14;
   DLG_FS_DICOM24    = 15;
   DLG_FS_FAX        = 16;
   DLG_FS_EPS        = 17;
   DLG_FS_EXIF       = 18;
   DLG_FS_FPX24      = 19;
   DLG_FS_FPX8       = 20;
   DLG_FS_IMG        = 21;
   DLG_FS_GIF1       = 22;
   DLG_FS_GIF2       = 23;
   DLG_FS_GIF3       = 24;
   DLG_FS_GIF4       = 25;
   DLG_FS_GIF5       = 26;
   DLG_FS_GIF6       = 27;
   DLG_FS_GIF7       = 28;
   DLG_FS_GIF8       = 29;
   DLG_FS_IOCA       = 30;
   DLG_FS_MODCA      = 31;
   DLG_FS_PCT1       = 32;
   DLG_FS_PCT4       = 33;
   DLG_FS_PCT8       = 34;
   DLG_FS_PCT24      = 35;
   DLG_FS_MAC        = 36;
   DLG_FS_AWD        = 37;
   DLG_FS_MSP        = 38;
   DLG_FS_OS2BMP1    = 39;
   DLG_FS_OS2BMP4    = 40;
   DLG_FS_OS2BMP8    = 41;
   DLG_FS_OS2BMP24   = 42;
   DLG_FS_PCX1       = 43;
   DLG_FS_PCX4       = 44;
   DLG_FS_PCX8       = 45;
   DLG_FS_PCX24      = 46;
   DLG_FS_PSD1       = 47;
   DLG_FS_PSD8       = 48;
   DLG_FS_PSD24      = 49;
   DLG_FS_RAS1       = 50;
   DLG_FS_RAS4       = 51;
   DLG_FS_RAS8       = 52;
   DLG_FS_RAS24      = 53;
   DLG_FS_RAS32      = 54;
   DLG_FS_TGA8       = 55;
   DLG_FS_TGA16      = 56;
   DLG_FS_TGA24      = 57;
   DLG_FS_TGA32      = 58;
   DLG_FS_TIFF1      = 59;
   DLG_FS_TIFF2      = 60;
   DLG_FS_TIFF3      = 61;
   DLG_FS_TIFF4      = 62;
   DLG_FS_TIFF5      = 63;
   DLG_FS_TIFF6      = 64;
   DLG_FS_TIFF7      = 65;
   DLG_FS_TIFF8      = 66;
   DLG_FS_TIFF12     = 67;
   DLG_FS_TIFF16     = 68;
   DLG_FS_TIFF24     = 69;
   DLG_FS_TIFF32     = 70;
   DLG_FS_BMP1       = 71;
   DLG_FS_BMP4       = 72;
   DLG_FS_BMP8       = 73;
   DLG_FS_BMP16      = 74;
   DLG_FS_BMP24      = 75;
   DLG_FS_BMP32      = 76;
   DLG_FS_WFX        = 77;
   DLG_FS_WMF8       = 78;
   DLG_FS_WMF24      = 79;
   DLG_FS_EMF8       = 80;
   DLG_FS_EMF24      = 81;
   DLG_FS_WPG1       = 82;
   DLG_FS_WPG4       = 83;
   DLG_FS_WPG8       = 84;
   DLG_FS_ICO1       = 85;
   DLG_FS_ICO4       = 86;
   DLG_FS_ICO8       = 87;
   DLG_FS_ICO24      = 88;
   DLG_FS_CUR1       = 89;
   DLG_FS_CUR4       = 90;
   DLG_FS_CUR8       = 91;
   DLG_FS_CUR24      = 92;
   DLG_FS_JBIG1      = 93;
   DLG_FS_JBIG2      = 94;
   DLG_FS_JBIG3      = 95;
   DLG_FS_JBIG4      = 96;
   DLG_FS_JBIG5      = 97;
   DLG_FS_JBIG6      = 98;
   DLG_FS_JBIG7      = 99;
   DLG_FS_JBIG8      = 100;
   DLG_FS_CUT        = 101;
   DLG_FS_PPM        = 102;
   DLG_FS_PGM        = 103;
   DLG_FS_PBM        = 104;
   DLG_FS_IFF1       = 105;
   DLG_FS_IFF2       = 106;
   DLG_FS_IFF3       = 107;
   DLG_FS_IFF4       = 108;
   DLG_FS_IFF5       = 109;
   DLG_FS_IFF6       = 110;
   DLG_FS_IFF7       = 111;
   DLG_FS_IFF8       = 112;
   DLG_FS_IFF24      = 113;
   DLG_FS_XBM        = 114;
   DLG_FS_XPM8       = 115;
   DLG_FS_XPM16      = 116;
   DLG_FS_XPM24      = 117;
   DLG_FS_XPM32      = 118;
   DLG_FS_ITG        = 119;
   DLG_FS_TIFF48     = 120;
   DLG_FS_TIFF64     = 121;
   DLG_FS_FLC8       = 122;
   DLG_FS_ANI1       = 123;
   DLG_FS_ANI4       = 124;
   DLG_FS_ANI8       = 125;
   DLG_FS_ANI24      = 126;
   DLG_FS_XWD10_1    = 127;
   DLG_FS_XWD10_2    = 128;
   DLG_FS_XWD10_4    = 129;
   DLG_FS_XWD10_8    = 130;
   DLG_FS_XWD11_1    = 131;
   DLG_FS_XWD11_2    = 132;
   DLG_FS_XWD11_4    = 133;
   DLG_FS_XWD11_8    = 134;
   DLG_FS_XWD11_16   = 135;
   DLG_FS_XWD11_24   = 136;
   DLG_FS_XWD11_32   = 137;
   DLG_FS_SGI8       = 138;
   DLG_FS_SGI24      = 139;
   DLG_FS_SGI32      = 140;
   DLG_FS_CLP1       = 141;
   DLG_FS_CLP4       = 142;
   DLG_FS_CLP8       = 143;
   DLG_FS_CLP24      = 144;
   DLG_FS_RAW        = 145;
   DLG_FS_PDF1       = 146;
   DLG_FS_PDF2       = 147;
   DLG_FS_PDF4       = 148;
   DLG_FS_PDF8       = 149;
   DLG_FS_PDF24      = 150;
   DLG_FS_J2K8       = 151;
   DLG_FS_J2K24      = 152;
   DLG_FS_CMW8       = 153;
   DLG_FS_CMW24      = 154;
   DLG_FS_MAX        = 154;

{ FileSave sub-format values        }
{ LEAD CMP file subtypes (8,24-bit) }
 DLG_FS_SUB_CMP_NONPROGRESSIVE           = $0001;
 DLG_FS_SUB_CMP_PROGRESSIVE              = $0002;
{ JPEG file subtypes (24-bit)       }
 DLG_FS_SUB_JPEG24_YUV_444               = $0001;
 DLG_FS_SUB_JPEG24_YUV_422               = $0002;
 DLG_FS_SUB_JPEG24_YUV_411               = $0004;
 DLG_FS_SUB_JPEG24_PROG_444              = $0008;
 DLG_FS_SUB_JPEG24_PROG_422              = $0010;
 DLG_FS_SUB_JPEG24_PROG_411              = $0020;
 DLG_FS_SUB_JPEG24_LOSSLESS              = $0040;
{ JPEG file subtypes (12-bit)       }
 DLG_FS_SUB_JPEG12_YUV_400               = $0001;
 DLG_FS_SUB_JPEG12_LOSSLESS              = $0002;
{ JPEG file subtypes (8-bit)        }
 DLG_FS_SUB_JPEG8_YUV_400                = $0001;
 DLG_FS_SUB_JPEG8_PROG_400               = $0002;
 DLG_FS_SUB_JPEG8_LOSSLESS               = $0004;
{ JPEG 2000 file subtypes (8,24-bit)}
 DLG_FS_SUB_J2K_STREAM                   = $0001;
 DLG_FS_SUB_J2K_JP2                      = $0002;
{ DICOM file subtypes (8-bit)       }
 DLG_FS_SUB_DICOM_RLE_GRAY               = $0001;
 DLG_FS_SUB_DICOM_RLE_COLOR              = $0002;
 DLG_FS_SUB_DICOM_JPEG_GRAY              = $0004;
 DLG_FS_SUB_DICOM_LOSSLESSJPEG_GRAY      = $0008;
 DLG_FS_SUB_DICOM_JPEG_COLOR             = $0010;
 DLG_FS_SUB_DICOM_LOSSLESSJPEG_COLOR     = $0020;
{ RAW FAX, IOCA, & MODCA subtypes   }
 DLG_FS_SUB_FAX_G3_1D                    = $0001;
 DLG_FS_SUB_FAX_G3_2D                    = $0002;
 DLG_FS_SUB_FAX_G4                       = $0004;
{ EXIF file subtypes                }
 DLG_FS_SUB_EXIF_UNCOMPRESSEDRGB         = $0001;
 DLG_FS_SUB_EXIF_UNCOMPRESSEDYCC         = $0002;
 DLG_FS_SUB_EXIF_JPEG_411                = $0004;
 DLG_FS_SUB_EXIF_JPEG_422                = $0008;
{ EXIF file subtypes                }
 DLG_FS_SUB_FPX_UNCOMPRESSED             = $0001;
 DLG_FS_SUB_FPX_SINGLECOLOR              = $0002;
 DLG_FS_SUB_FPX_DEFQFACTOR               = $0004;
 DLG_FS_SUB_FPX_SPECQFACTOR              = $0008;
{ GIF file subtypes                 }
 DLG_FS_SUB_GIF_INTERLACED89A            = $0001;
 DLG_FS_SUB_GIF_NONINTERLACED89A         = $0002;
{ OS/2 BMP file subtypes            }
 DLG_FS_SUB_OS2_VER1                     = $0001;
 DLG_FS_SUB_OS2_VER2                     = $0002;
{ TIFF file subtypes (1-bit)        }
 DLG_FS_SUB_TIFF1_CCITT                  = $0001;
 DLG_FS_SUB_TIFF1_CCITT_G3_1D            = $0002;
 DLG_FS_SUB_TIFF1_CCITT_G3_2D            = $0004;
 DLG_FS_SUB_TIFF1_CCITT_G4               = $0008;
 DLG_FS_SUB_TIFF1_UNCOMPRESSEDRGB        = $0010;
 DLG_FS_SUB_TIFF1_RLERGB                 = $0020;
 DLG_FS_SUB_TIFF1_LZWRGB                 = $0040;
{ TIFF file subtypes (2,3,4,5,6,7-bit) }
 DLG_FS_SUB_TIFFOTHER_UNCOMPRESSED       = $0001;
 DLG_FS_SUB_TIFFOTHER_RLE                = $0002;
 DLG_FS_SUB_TIFFOTHER_LZW                = $0004;
{ TIFF file subtypes (8-bit)        }
 DLG_FS_SUB_TIFF8_UNCOMPRESSEDRGB        = $0001;
 DLG_FS_SUB_TIFF8_RLERGB                 = $0002;
 DLG_FS_SUB_TIFF8_JPEG_GRAY_YCC          = $0004;
 DLG_FS_SUB_TIFF8_LOSSLESSJPEG           = $0008;
 DLG_FS_SUB_TIFF8_LZWRGB                 = $0010;
 DLG_FS_SUB_TIFF8_JBIG                   = $0020;
 DLG_FS_SUB_TIFF8_CMP                    = $0040;
 DLG_FS_SUB_TIFF8_J2K                    = $0080;
 DLG_FS_SUB_TIFF8_CMW                    = $0100;
{ TIFF file subtypes (12-bit)       }
 DLG_FS_SUB_TIFF12_UNCOMPRESSED          = $0001;
 DLG_FS_SUB_TIFF12_LOSSLESSJPEG          = $0002;
{ TIFF file subtypes (16-bit)       }
 DLG_FS_SUB_TIFF16_UNCOMPRESSED          = $0001;
 DLG_FS_SUB_TIFF16_RLE                   = $0002;
 DLG_FS_SUB_TIFF16_LOSSLESSJPEG          = $0004;
 DLG_FS_SUB_TIFF16_LZW                   = $0008;
{ TIFF file subtypes (24-bit)       }
 DLG_FS_SUB_TIFF24_UNCOMPRESSEDRGB       = $0001;
 DLG_FS_SUB_TIFF24_UNCOMPRESSEDCMYK      = $0002;
 DLG_FS_SUB_TIFF24_UNCOMPRESSEDYCC       = $0004;
 DLG_FS_SUB_TIFF24_RLERGB                = $0008;
 DLG_FS_SUB_TIFF24_RLECMYK               = $0010;
 DLG_FS_SUB_TIFF24_RLEYCC                = $0020;
 DLG_FS_SUB_TIFF24_JPEG_YCC_444          = $0040;
 DLG_FS_SUB_TIFF24_JPEG_YCC_422          = $0080;
 DLG_FS_SUB_TIFF24_JPEG_YCC_411          = $0100;
 DLG_FS_SUB_TIFF24_LOSSLESSJPEG          = $0200;
 DLG_FS_SUB_TIFF24_LZWRGB                = $0400;
 DLG_FS_SUB_TIFF24_LZWCMYK               = $0800;
 DLG_FS_SUB_TIFF24_LZWYCC                = $1000;
 DLG_FS_SUB_TIFF24_CMP_NONPROGRESSIVE    = $2000;
 DLG_FS_SUB_TIFF24_CMP_PROGRESSIVE       = $4000;
 DLG_FS_SUB_TIFF24_J2K                   = $8000;
 DLG_FS_SUB_TIFF24_CMW                   = $10000;
{ TIFF file subtypes (32-bit)       }
 DLG_FS_SUB_TIFF32_UNCOMPRESSEDRGB       = $0001;
 DLG_FS_SUB_TIFF32_UNCOMPRESSEDCMYK      = $0002;
 DLG_FS_SUB_TIFF32_RLERGB                = $0004;
 DLG_FS_SUB_TIFF32_RLECMYK               = $0008;
 DLG_FS_SUB_TIFF32_LZWRGB                = $0010;
 DLG_FS_SUB_TIFF32_LZWCMYK               = $0020;
{ BMP file subtypes (4 and 8-bit only) }
 DLG_FS_SUB_BMP_UNCOMPRESSED             = $0001;
 DLG_FS_SUB_BMP_RLECOMPRESSED            = $0002;
{ WFX file subtypes                 }
 DLG_FS_SUB_WFX_CCITT_G3_1D              = $0001;
 DLG_FS_SUB_WFX_CCITT_G4                 = $0002;
{ PPM file subtypes                 }
 DLG_FS_SUB_PPM_ASCII                    = $0001;
 DLG_FS_SUB_PPM_BINARY                   = $0002;
{ PGM file subtypes }
 DLG_FS_SUB_PGM_ASCII                    = $0001;
 DLG_FS_SUB_PGM_BINARY                   = $0002;
{ PBM file subtypes }
 DLG_FS_SUB_PBM_ASCII                    = $0001;
 DLG_FS_SUB_PBM_BINARY                   = $0002;
{ IFF file subtypes }
{ All BitsPerPixel have subtypes }
 DLG_FS_SUB_IFF_ILBM_RLE                 = $0001;
 DLG_FS_SUB_IFF_CAT_RLE                  = $0002;
{ SGI file subtypes }
{ All BitsPerPixel have subtypes }
 DLG_FS_SUB_SGI_UNCOMPRESSED             = $0001;
 DLG_FS_SUB_SGI_RLECOMPRESSED            = $0002;
{ PDF file subtypes (1-bit)       }
 DLG_FS_SUB_PDF1_UNCOMPRESSED            = $0001;
 DLG_FS_SUB_PDF1_CCITT_G3_1D             = $0002;
 DLG_FS_SUB_PDF1_CCITT_G3_2D             = $0004;
 DLG_FS_SUB_PDF1_CCITT_G4                = $0008;
{ PDF file subtypes (8-bit)       }
 DLG_FS_SUB_PDF8_UNCOMPRESSED            = $0001;
 DLG_FS_SUB_PDF8_LOSSLESSJPEG            = $0002;
{ PDF file subtypes (24-bit)       }
 DLG_FS_SUB_PDF24_UNCOMPRESSED           = $0001;
 DLG_FS_SUB_PDF24_YUV_444                = $0002;
 DLG_FS_SUB_PDF24_YUV_422                = $0004;
 DLG_FS_SUB_PDF24_YUV_411                = $0008;

  {GetDirDlgConstants}
  DLG_GD_95STYLE       = $00000001; {GetDir Dlg should have Windows95 Explorer style look}
  DLG_GD_95CONTEXTHELP = $00000002; {Dlg should contain context sensitive help icon}

  {FileSaveDlgMultipageConstants}
  SAVE_OVERWRITE  = 0;
  SAVE_APPEND     = 1;
  SAVE_REPLACE    = 2;
  SAVE_INSERT     = 3;

  {ColorResDlgConstants}
  DLG_CR_SHOWPREVIEW  =   $00000001;   {shows preview of image }
  DLG_CR_AUTOPROCESS  =   $00000002;   {process the image on OK}
  DLG_CR_95CONTEXTHELP=   $10000000;   {Dlg should contain context sensitive help icon}

  DLG_CR_1BIT       =     $00000004;
  DLG_CR_2BIT       =     $00000008;
  DLG_CR_3BIT       =     $00000010;
  DLG_CR_4BIT       =     $00000020;
  DLG_CR_5BIT       =     $00000040;
  DLG_CR_6BIT       =     $00000080;
  DLG_CR_7BIT       =     $00000100;
  DLG_CR_8BIT       =     $00000200;
  DLG_CR_12BIT      =     $00000400;
  DLG_CR_16BIT      =     $00000800;
  DLG_CR_24BIT      =     $00001000;
  DLG_CR_32BIT      =     $00002000;
  DLG_CR_BITALL     =     $00003FFC;
                                   
  DLG_CR_DITHER_NONE      = $00004000;   { no dithering is an option }
  DLG_CR_DITHER_FLOYD     = $00008000;   { floyd dithering is an option }
  DLG_CR_DITHER_STUCKI    = $00010000;   { stucki dithering is an option }
  DLG_CR_DITHER_BURKES    = $00020000;   { burkes dithering is an option }
  DLG_CR_DITHER_SIERRA    = $00040000;   { sierra dithering is an option }
  DLG_CR_DITHER_STEVENSON = $00080000;   { stevenson dithering is an option }
  DLG_CR_DITHER_JARVIS    = $00100000;   { jarvis dithering is an option }
  DLG_CR_DITHER_CLUSTER   = $00200000;   { clustered dithering is an option }
  DLG_CR_DITHER_ORDERED   = $00400000;   { ordered dithering is an option }
  DLG_CR_DITHER_ALL       = $007FC000;   { All dithering methods are options }

  DLG_CR_PAL_FIXED     = $00800000;
  DLG_CR_PAL_OPTIMIZED = $01000000;
  DLG_CR_PAL_IDENTITY  = $02000000;
  DLG_CR_PAL_NETSCAPE  = $04000000;
  DLG_CR_PAL_ALL       = $07800000;

  DLG_CR_ORDER = $08000000;

  {ImgProcDlgConstants}
  DLG_IMG_AUTOPROCESS  =   $80000000;   { Dlg should autoprocess image and fill the pBitmap}
  DLG_IMG_SHOWPREVIEW  =   $40000000;   { ImageProcess Dlg should preview of image }
  DLG_IMG_HIDEBACKCOLOR=   $20000000;   { GetAngle Dlg should hide Background Color button }
  DLG_IMG_95CONTEXTHELP=   $10000000;   { Dlg should contain context sensitive help icon }
  DLG_IMG_SHOWRESIZEOPT=   $08000000;   { GetAngle Dlg should show resize options }

  DLG_IMG_RESIZE       =   $00000001;   { resize dialog}
  DLG_IMG_RESAMPLE     =   $00000002;   { resample dialog}
  DLG_IMG_ROTATE       =   $00000003;   { rotate dialog}
  DLG_IMG_SHEAR        =   $00000004;   { shear dialog }

  DLG_IMG_GRADIENT     =   $00000001;   { gradient dialog }
  DLG_IMG_LAPLACIAN    =   $00000002;   { laplacian dialog}
  DLG_IMG_SOBEL        =   $00000004;   { sobel dialog }
  DLG_IMG_PREWITT      =   $00000008;   { prewitt dialog}
  DLG_IMG_SHIFTDIFF    =   $00000010;   { shiftdiff dialog}
  DLG_IMG_LINESEG      =   $00000020;   { lineseg dialog  }
  DLG_IMG_EROSION      =   $00000040;   { erosion dialog  }
  DLG_IMG_DILATION     =   $00000080;   { dilation dialog }

  DLG_IMG_SHARPEN      =   $00000001;   { sharpen dialog  }
  DLG_IMG_BRIGHTNESS   =   $00000002;   { brightness dialog}
  DLG_IMG_CONTRAST     =   $00000004;   { contrast dialog }
  DLG_IMG_SATURATION   =   $00000008;   { saturation dialog}
  DLG_IMG_HISTOCONTRAST=   $00000010;   { histo contrast dialog}
  DLG_IMG_HUE          =   $00000020;   { hue dialog }
  DLG_IMG_HALFTONE     =   $00000040;   { halftone dialog }
  DLG_IMG_POSTERIZE    =   $00000080;   { posterize dialog}
  DLG_IMG_MOSAIC       =   $00000100;   { mosaic dialog }
  DLG_IMG_AVERAGE      =   $00000200;   { average dialog}
  DLG_IMG_MEDIAN       =   $00000400;   { median dialog }
  DLG_IMG_OILIFY       =   $00000800;   { oilify dialog }
  DLG_IMG_MIN          =   $00001000;   { min filter dialog}
  DLG_IMG_MAX          =   $00002000;   { max filter dialog}
  DLG_IMG_SOLARIZE     =   $00004000;   { solarize dialog }

  DLG_IMG_ADDNOISE     =   $0000001C;   { add noise dialog }
  DLG_IMG_GAMMACORRECT =   $0000001D;   { gamma correct dialog }
  DLG_IMG_EMBOSS       =   $0000001E;   { emboss filter dialog }
  DLG_IMG_INTENSITYDETECT =$0000001F;   { intensity detect dialog}

  {ImgProcDlgConstants}
  DLG_WL_SHOWPREVIEW   =   $00000001;   { shows preview of image }
  DLG_WL_AUTOPROCESS   =   $00000002;   { process the image on OK }
  DLG_WL_95CONTEXTHELP =   $00000004;   {Dlg should contain context sensitive help icon}

  {PaintEffectDlgConstants}
  DLG_EFX_SHOWPREVIEW      = $00000001;   { shows preview of image }
  DLG_EFX_AUTOPREVIEW      = $00000002;   { auto preview when options change }
  DLG_EFX_DELAY            = $00000004;   { effect delay is an option }
  DLG_EFX_GRAIN            = $00000008;   { effect grain is an option }
  DLG_EFX_PASSES           = $00000010;   { effect passes is an option }
  DLG_EFX_TRANSPARENT      = $00000020;   { transparency is an option }
  DLG_EFX_WAND             = $00000040;   { wand is an option }
  DLG_EFX_NO_TREEVIEW      = $00000080;   { DO NOT use TreeView }
  DLG_EFX_CLASS_NONE       = $00000100;   { no effect class is option }
  DLG_EFX_CLASS_WIPE       = $00000200;   { linear wipe class is option }
  DLG_EFX_CLASS_WIPERECT   = $00000400;   { rect wipe class is option }
  DLG_EFX_CLASS_WIPECIRCLE = $00000800;   { circle wipe class is option }
  DLG_EFX_CLASS_PUSH       = $00001000;   { push class is option }
  DLG_EFX_CLASS_SLIDE      = $00002000;   { slide class is option }
  DLG_EFX_CLASS_ROLL       = $00004000;   { roll class is option }
  DLG_EFX_CLASS_ROTATE     = $00008000;   { rotate class is option }
  DLG_EFX_CLASS_ZOOM       = $00010000;   { zoom class is option }
  DLG_EFX_CLASS_DRIP       = $00020000;   { drip class is option }
  DLG_EFX_CLASS_BLIND      = $00040000;   { blind class is option }
  DLG_EFX_CLASS_RANDOM     = $00080000;   { random class is option }
  DLG_EFX_CLASS_CHECK      = $00100000;   { check class is option }
  DLG_EFX_CLASS_BLOCKS     = $00200000;   { blocks class is option }
  DLG_EFX_CLASS_CIRCLE     = $00400000;   { circle class is option }
  DLG_EFX_CLASS_ELLIPSE    = $00800000;   { ellipse class is option }
  DLG_EFX_95CONTEXTHELP    = $01000000;   { Dlg should contain context sensitive help icon }

  {GradientDlgConstants}
  DLG_GRAD_SHOWPREVIEW           = $00000001;   { shows preview of image }
  DLG_GRAD_AUTOPREVIEW           = $00000002;   { auto preview when options change }
  DLG_GRAD_STARTCOLOR            = $00000004;   { start color is an option }
  DLG_GRAD_ENDCOLOR              = $00000008;   { end color is an option }
  DLG_GRAD_STEPS                 = $00000010;   { gradient steps is an option }
  DLG_GRAD_NO_TREEVIEW           = $00000020;   { DO NOT use TreeView }
  DLG_GRAD_CLASS_LINEAR          = $00000040;   { linear gradients are an option }
  DLG_GRAD_CLASS_ANGULAR         = $00000080;   { angular gradients are an option }
  DLG_GRAD_CLASS_RECTANGULAR     = $00000100;   { rectangular gradients are an option }
  DLG_GRAD_CLASS_ELLIPTICAL      = $00000200;   { elliptical gradients are an option }
  DLG_GRAD_CLASS_CONICAL         = $00000400;   { conical gradients are an option }
  DLG_GRAD_95CONTEXTHELP         = $00000800;   { Dlg should contain context sensitive help icon }

  {TransitionDlgConstants}
  DLG_TRANS_SHOWPREVIEW     = $00000001;   { shows preview of image }
  DLG_TRANS_AUTOPREVIEW     = $00000002;   { auto preview when options change }
  DLG_TRANS_FORECOLOR       = $00000004;   { forecolor is an option }
  DLG_TRANS_BACKCOLOR       = $00000008;   { backcolor is an option }
  DLG_TRANS_DELAY           = $00000010;   { transition delay is an option }
  DLG_TRANS_GRAIN           = $00000020;   { transition grain is an option }
  DLG_TRANS_EFFECT          = $00000040;   { paint effect is an option }
  DLG_TRANS_PASSES          = $00000080;   { transition passes is an option }
  DLG_TRANS_WAND            = $00000100;   { wand is an option }
  DLG_TRANS_TRANSPARENT     = $00000200;   { transparency is an option }
  DLG_TRANS_GRADIENT        = $00000400;   { gradient is an option }
  DLG_TRANS_95CONTEXTHELP   = $00000800;   { Dlg should contain context sensitive help icon }

  {ShapeDlgConstants}
  DLG_SHAPE_SHOWPREVIEW          = $00000001;   { shows preview of image }
  DLG_SHAPE_AUTOPREVIEW          = $00000002;   { auto preview when options change }
  DLG_SHAPE_BACKSTYLE            = $00000004;   { backstyle is an option }
  DLG_SHAPE_FILLSTYLE            = $00000008;   { fillstyle is an option }
  DLG_SHAPE_FORE_BACK_COLOR      = $00000010;   { fore and back colors are options }
  DLG_SHAPE_BORDERSTYLE          = $00000020;   { borderstyle is an option }
  DLG_SHAPE_BORDERWIDTH          = $00000040;   { border width is an option }
  DLG_SHAPE_BORDERCOLOR          = $00000080;   { bordercolor is an option }
  DLG_SHAPE_INNERSTYLE           = $00000100;   { innerbandstyle is an option }
  DLG_SHAPE_INNERWIDTH           = $00000200;   { innerband width is an option }
  DLG_SHAPE_INNER_HILITE_SHADOW  = $00000400;   { innerband colors are options }
  DLG_SHAPE_OUTERSTYLE           = $00000800;   { outerbandstyle is an option }
  DLG_SHAPE_OUTERWIDTH           = $00001000;   { outerband width is an option }
  DLG_SHAPE_OUTER_HILITE_SHADOW  = $00002000;   { outerband colors are options }
  DLG_SHAPE_SHADOWCOLOR          = $00004000;   { shadow color is an option }
  DLG_SHAPE_SHADOW_X_Y           = $00008000;   { shadow x and y are options }
  DLG_SHAPE_BROWSEIMAGE          = $00010000;   { browse image button is option }
  DLG_SHAPE_NO_TREEVIEW          = $00020000;   { DO NOT use TreeView }
  DLG_SHAPE_CLASS_SQUARE         = $00040000;   { squares are options }
  DLG_SHAPE_CLASS_RECTANGLE      = $00080000;   { rectangles are options }
  DLG_SHAPE_CLASS_PARALLELOGRAM  = $00100000;   { parallelograms are options }
  DLG_SHAPE_CLASS_TRAPEZOID      = $00200000;   { trapezoids are options }
  DLG_SHAPE_CLASS_TRIANGLE       = $00400000;   { triangles are options }
  DLG_SHAPE_CLASS_OTHER          = $00800000;   { other polygons are options }
  DLG_SHAPE_CLASS_CIRCLE         = $01000000;   { circles are options }
  DLG_SHAPE_CLASS_ELLIPSE        = $02000000;   { ellipses are options }
  DLG_SHAPE_CLASS_STAR           = $04000000;   { stars are options }
  DLG_SHAPE_CLASS_CROSS          = $08000000;   { crosses are options }
  DLG_SHAPE_CLASS_ARROW          = $10000000;   { arrows are options }
  DLG_SHAPE_95CONTEXTHELP        = $20000000;   { Dlg should contain context sensitive help icon }

  {TextDlgConstants}
  DLG_TEXT_SHOWPREVIEW           = $00000001;   { shows preview of image }
  DLG_TEXT_AUTOPREVIEW           = $00000002;   { auto preview when options change }
  DLG_TEXT_SAMPLETEXT            = $00000004;   { sample text edit box is an option }
  DLG_TEXT_STYLE                 = $00000008;   { text style is an option }
  DLG_TEXT_COLOR                 = $00000010;   { text color is an option }
  DLG_TEXT_BORDERCOLOR           = $00000020;   { bordercolor is an option }
  DLG_TEXT_ALIGN                 = $00000040;   { alignment is an option }
  DLG_TEXT_ANGLE                 = $00000080;   { angle is an option }
  DLG_TEXT_WORDWRAP              = $00000100;   { wordwrap is an option }
  DLG_TEXT_FONT                  = $00000200;   { font is an option }
  DLG_TEXT_FOREIMAGE             = $00000400;   { foreground image is an option }
  DLG_TEXT_BROWSEIMAGE           = $00000800;   { browse image button is option }
  DLG_TEXT_SHADOWCOLOR           = $00001000;   { shadow color is an option }
  DLG_TEXT_SHADOW_X_Y            = $00002000;   { shadow x and y are options }
  DLG_TEXT_95CONTEXTHELP         = $00004000;   { Dlg should contain context sensitive help icon }

  {FileDlgFlagConstants}
  DLG_OFN_OVERWRITEPROMPT = $00000002;  { FileSave will prompt if file exists }
  DLG_OFN_NOCHANGEDIR = $00000008;      { restore dir to original after close }
  DLG_OFN_ALLOWMULTI = $00000200;       { allow multiple files to be selected }

  {CountourFilterDlgConstants}
  DLG_CONTOUR_SHOWPREVIEW          = $00000001;   { shows preview of image }
  DLG_CONTOUR_AUTOPROCESS          = $00000002;   { AutoProcess on close   }
  DLG_CONTOUR_OPTION               = $00000004;   { Contour Option is an option }
  DLG_CONTOUR_THRESHOLD            = $00000008;   { Threshold is an option }
  DLG_CONTOUR_DELTADIRECTION       = $00000010;   { DeltaDirection is an option  }
  DLG_CONTOUR_MAXIMUMERROR         = $00000020;   { MaximumError is an option    }
  DLG_CONTOUR_95CONTEXTHELP        = $00000040;   { Dlg should contain context sensitive help icon }

  {CountourFilterDlgOptionFlags}
  DLG_CONTOUR_OPTION_THIN          = $00000001;
  DLG_CONTOUR_OPTION_LINK_BW       = $00000002;
  DLG_CONTOUR_OPTION_LINK_GRAY     = $00000004;
  DLG_CONTOUR_OPTION_LINK_COLOR    = $00000008;
  DLG_CONTOUR_OPTION_APPROX_COLOR  = $00000010;

  {CountourFilterDlgOptions}
  CONTOUR_THIN              = 0;
  CONTOUR_LINK_BLACKWHITE   = 1;
  CONTOUR_LINK_GRAY         = 2;
  CONTOUR_LINK_COLOR        = 3;
  CONTOUR_APPROX_COLOR      = 4;

{$I LEADLock.pas}

implementation
end.
