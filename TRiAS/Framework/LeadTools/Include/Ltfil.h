/*
   LTFIL.H - file module header file
   Copyright (c) 1991-2000 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTFIL_H_
#define _LTFIL_H_

#include "ltkrn.h"
#if !defined(_WIN32_WCE)
#include "lvkrn.h"
#include "ldkrn.h"
#endif /* _WIN32_WCE */

#define _HEADER_ENTRY_
#include "ltpck.h"

/*
   flags for L_LoadFile
*/
#define LOADFILE_ALLOCATE           0x00000001  /* Allocate image memory */
#define LOADFILE_STORE              0x00000002  /* Auto-store image lines */
#define LOADFILE_FIXEDPALETTE       0x00000004  /* Allow fixed palettes only */
#define LOADFILE_NOINTERLACE        0x00000008  /* Don't send interlaced lines */
#define LOADFILE_ALLPAGES           0x00000010  /* Load all file pages */
#define LOADFILE_NOINITBITMAP       0x00000020  /* Don't initialize the bitmap handle */
#define LOADFILE_COMPRESSED         0x00000040  /* Allow compressed 1 bit images */
#define LOADFILE_SUPERCOMPRESSED    0x00000080  /* Load 1-bit or 24-bit images supercompressed */

/*
   flags for L_SaveFile
*/
#define SAVEFILE_FIXEDPALETTE       0x00000001  /* Save with Fixed Palette */
#define SAVEFILE_OPTIMIZEDPALETTE   0x00000002  /* Save with Bitmap's Palette */
#define SAVEFILE_MULTIPAGE          0x00000004  /* Save as multipage */
#define SAVEFILE_GRAYOUTPUT         0x00000008  /* Save output bitmap as grayscale */

/*
   list of file types supported
*/
#define FILE_PCX                  1 /* ZSoft PCX */
#define FILE_GIF                  2 /* CompuServe GIF */
#define FILE_TIF                  3 /* Tagged Image File Format */
#define FILE_TGA                  4 /* Targa */
#define FILE_CMP                  5 /* LEAD CMP */
#define FILE_BMP                  6 /* Windows BMP */
#define FROM_BUFFER               7 /* Internal use */
#define FILE_BITMAP               9 /* Internal use */
#define FILE_JPEG                10 /* Jpeg File Interchange Format */
#define FILE_JFIF                FILE_JPEG
#define FILE_TIF_JPEG            11 /* Jpeg Tag Image File Format */
#define FILE_JTIF                FILE_TIF_JPEG
#define FILE_BIN                 12 /* Internal use */
#define FILE_HANDLE              13 /* Internal use */
#define FILE_OS2                 14 /* OS/2 BMP */
#define FILE_WMF                 15 /* Windows Meta File */
#define FILE_EPS                 16 /* Encapsulated Post Script */
#define FILE_TIFLZW              17 /* TIF Format with LZW compression */
#define FILE_LEAD                20 /* LEAD  Proprietary */
#define FILE_JPEG_411            21 /* JPEG  4:1:1 */
#define FILE_LEAD1JFIF           FILE_JPEG_411
#define FILE_TIF_JPEG_411        22 /* JPEG  4:1:1 */
#define FILE_LEAD1JTIF           FILE_TIF_JPEG_411
#define FILE_JPEG_422            23 /* JPEG  4:2:2 */
#define FILE_LEAD2JFIF           FILE_JPEG_422
#define FILE_TIF_JPEG_422        24 /* JPEG  4:2:2 */
#define FILE_LEAD2JTIF           FILE_TIF_JPEG_422
#define FILE_CCITT               25 /* TIFF  CCITT */
#define FILE_LEAD1BIT            26 /* LEAD 1 bit, lossless compression */
#define FILE_CCITT_GROUP3_1DIM   27 /* CCITT Group3 one dimension */
#define FILE_CCITT_GROUP3_2DIM   28 /* CCITT Group3 two dimensions */
#define FILE_CCITT_GROUP4        29 /* CCITT Group4 two dimensions */
#define FILE_LEAD_NOLOSS         30 /* LEAD  Proprietary Lossless */
#define FILE_LEAD1BITA           31 /* old LEAD 1 bit, lossless compression */

#define FILE_CALS                50
#define FILE_MAC                 51
#define FILE_IMG                 52
#define FILE_MSP                 53
#define FILE_WPG                 54
#define FILE_RAS                 55
#define FILE_PCT                 56
#define FILE_PCD                 57
#define FILE_DXF                 58
#define FILE_DXF_R12             FILE_DXF
#define FILE_AVI                 59
#define FILE_WAV                 60
#define FILE_FLI                 61
#define FILE_CGM                 62
#define FILE_EPSTIFF             63 /* EPS with TIFF Preview */
#define FILE_EPSWMF              64 /* EPS with Metafile Preview */
#define FILE_CMPNOLOSS           65
#define FILE_FAX_G3_1D           66
#define FILE_FAX_G3_2D           67
#define FILE_FAX_G4              68
#define FILE_WFX_G3_1D           69
#define FILE_WFX_G4              70
#define FILE_ICA_G3_1D           71
#define FILE_ICA_G3_2D           72
#define FILE_ICA_G4              73
#define FILE_OS2_2               74
#define FILE_PNG                 75
#define FILE_PSD                 76
#define FILE_RAWICA_G3_1D        77
#define FILE_RAWICA_G3_2D        78
#define FILE_RAWICA_G4           79
#define FILE_FPX                 80  /* FlashPix, no compression */
#define FILE_FPX_SINGLE_COLOR    81  /* FlashPix, compression 'single color' method */
#define FILE_FPX_JPEG            82  /* FlashPix, compression JPEG */
#define FILE_FPX_JPEG_QFACTOR    83  /* FlashPix, compression JPEG, specify qFactor */
#define FILE_BMP_RLE             84  /* compressed Windows BMP */
#define FILE_TIF_CMYK            85  /* TIFF no compression,      CMYK data */
#define FILE_TIFLZW_CMYK         86  /* TIFF LZW compression,     CMYK data */
#define FILE_TIF_PACKBITS        87  /* TIFF PackBits compression, RGB data */
#define FILE_TIF_PACKBITS_CMYK   88  /* TIFF PackBits compression, CMYK data */
#define FILE_DICOM_GRAY          89
#define FILE_DICOM_COLOR         90
#define FILE_WIN_ICO             91
#define FILE_WIN_CUR             92
#define FILE_TIF_YCC             93 /* TIFF YCbCr color space, no compression */
#define FILE_TIFLZW_YCC          94 /* TIFF YCbCr color space, LZW compression */
#define FILE_TIF_PACKBITS_YCC    95 /* TIFF YCbCr color space, PackBits compression */
#define FILE_EXIF                96 /* uncompressed RGB Exif file */
#define FILE_EXIF_YCC            97 /* uncompressed YCbCr Exif file */
#define FILE_EXIF_JPEG_422       98 /* JPEG 4:2:2 compressed Exif file */
#define FILE_EXIF_JPEG           FILE_EXIF_JPEG_422
#define FILE_AWD                 99 /* Microsoft Fax format */
#define FILE_FASTEST             100 /* for ISIS only! use the data as is, from the ISIS Scanner */
#define FILE_EXIF_JPEG_411       101 /* JPEG 4:1:1 compressed Exif file */

#define FILE_PBM_ASCII           102
#define FILE_PBM_BINARY          103
#define FILE_PGM_ASCII           104
#define FILE_PGM_BINARY          105
#define FILE_PPM_ASCII           106
#define FILE_PPM_BINARY          107
#define FILE_CUT                 108
#define FILE_XPM                 109
#define FILE_XBM                 110
#define FILE_IFF_ILBM            111
#define FILE_IFF_CAT             112
#define FILE_XWD                 113
#define FILE_CLP                 114
#define FILE_JBIG                115
#define FILE_EMF                 116
#define FILE_ICA_IBM_MMR         117 /* MO:DCA IBM MMR CCITT G32D */
#define FILE_RAWICA_IBM_MMR      118 /* IOCA IBM MMR CCITT G32D */
#define FILE_ANI                 119
#define FILE_LASERDATA           121   /* LaserData CCITT G4 */
#define FILE_INTERGRAPH_RLE      122   /* Intergraph RLE */
#define FILE_INTERGRAPH_VECTOR   123   /* Intergraph Vector */
#define FILE_DWG                 124

#define FILE_DICOM_RLE_GRAY      125
#define FILE_DICOM_RLE_COLOR     126
#define FILE_DICOM_JPEG_GRAY     127
#define FILE_DICOM_JPEG_COLOR    128

#define FILE_CALS4               129
#define FILE_CALS2               130
#define FILE_CALS3               131

#define FILE_XWD10               132
#define FILE_XWD11               133
#define FILE_FLC                 134
#define FILE_KDC                 135
#define FILE_DRW                 136
#define FILE_PLT                 137

#define FILE_TIF_CMP             138
#define FILE_TIF_JBIG            139
#define FILE_TIF_DXF_R13         140
#define FILE_TIF_DXF_R12         176
#define FILE_TIF_DXF             FILE_TIF_DXF_R13
#define FILE_TIF_UNKNOWN         141   /* TIFF file with unknown compression */

#define FILE_SGI                 142
#define FILE_SGI_RLE             143
#define FILE_VECTOR_DUMP         144
#define FILE_DWF                 145

/* under development */
#define FILE_RAS_PDF             146   /* Raster PDF uncompressed */
#define FILE_RAS_PDF_G3_1D       147   /* Raster PDF CCITT G3 1D compression */
#define FILE_RAS_PDF_G3_2D       148   /* Raster PDF CCITT G3 2D compression */
#define FILE_RAS_PDF_G4          149   /* Raster PDF CCITT G4 compression */
#define FILE_RAS_PDF_JPEG        150   /* Raster PDF JPEG 24-bit color 4:4:4 or grayscale 8-bit */
#define FILE_RAS_PDF_JPEG_422    151   /* Raster PDF JPEG 24-bit color 4:2:2 */
#define FILE_RAS_PDF_JPEG_411    152   /* Raster PDF JPEG 24-bit color 4:1:1 */

#define FILE_RAW                 153   /* Raw uncompressed data */

#define FILE_RASTER_DUMP         154
#define FILE_TIF_CUSTOM          155

#define FILE_RAW_RGB             156   /* Raw RGB */
#define FILE_RAW_RLE4            157   /* Raw RLE4 compressed 4-bit data */
#define FILE_RAW_RLE8            158   /* Raw RLE8 compressed 8-bit data */
#define FILE_RAW_BITFIELDS       159   /* Raw BITFIELD data--16 or 32 bit */
#define FILE_RAW_PACKBITS        160   /* Raw Packbits compression */
#define FILE_RAW_JPEG            161   /* Raw JPEG compression */
#define FILE_FAX_G3_1D_NOEOL     162   /* Raw CCITT compression--CCITT with no eol */
#define FILE_RAW_CCITT           (FILE_FAX_G3_1D_NOEOL)

#define FILE_JP2                 163   /* Jpeg2000 file */
#define FILE_J2K                 164   /* Jpeg2000 stream */
#define FILE_CMW                 165   /* Wavelet CMP */

#define FILE_TIF_J2K             166   /* TIFF Jpeg2000 stream */
#define FILE_TIF_CMW             167   /* TIFF Wavelet CMP */
#define FILE_MRC                 168   /* T44 (MRC) files */
#define FILE_GERBER              169   /* Gerber Vector */
#define FILE_WBMP                170
#define FILE_JPEG_LAB            171   /* JPEG CieLAB 4:4:4 */
#define FILE_JFIF_LAB            FILE_JPEG_LAB
#define FILE_JPEG_LAB_411        172   /* JPEG CieLAB 4:1:1 */
#define FILE_LEAD1JFIF_LAB       FILE_JPEG_LAB_411
#define FILE_JPEG_LAB_422        173   /* JPEG CieLAB 4:2:2 */
#define FILE_LEAD2JFIF_LAB       FILE_JPEG_LAB_422

/* File formats supported by the OCR module */
#define FILE_AMI_PRO_20             200   /* Ami Pro 2.0 */
#define FILE_AMI_PRO_30             201   /* Ami Pro 3.0 */
#define FILE_ASCII_SMART            202   /* ASCII Smart */
#define FILE_ASCII_STANDARD         203   /* ASCII Standard */
#define FILE_ASCII_STANDARD_DOS     204   /* ASCII Standard (DOS) */
#define FILE_ASCII_STRIPPED         205   /* ASCII Stripped */
#define FILE_DBASE_IV_10            206   /* dBase IV v1.0 */
#define FILE_DCA_RFT                207   /* DCA/RFT */
#define FILE_DCA_RFT_DW_5           208   /* DisplayWrite 5 */
#define FILE_EXCEL_MAC              209   /* Excel for the Macintosh */
#define FILE_EXCEL_30               210   /* Excel 3.0 */
#define FILE_EXCEL_40               211   /* Excel 4.0 */
#define FILE_EXCEL_50               212   /* Excel 5.0 */
#define FILE_EXCEL_OFFICE97         213   /* Excel Office 97 */
#define FILE_FRAMEMAKER             214   /* FrameMaker */
#define FILE_HTML_20                215   /* HTML (2.0 specification) */
#define FILE_HTML_EDITOR_20         216   /* HTML (SoftQuad Editor) */
#define FILE_HTML_NETSCAPE_20       217   /* HTML (Netscape additions) */
#define FILE_INTERLEAF              218   /* Interleaf */
#define FILE_LOTUS123               219   /* Lotus 1-2-3 */
#define FILE_LOTUS_WORD_PRO         220   /* Lotus Word Pro */
#define FILE_MULTIMATE_ADV_II       221   /* MultiMate Advantage II */
#define FILE_POSTSCRIPT             222   /* Postscript */
#define FILE_PROFESSIONAL_WRITE_20  223   /* Professional Write 2.0 */
#define FILE_PROFESSIONAL_WRITE_22  224   /* Professional Write 2.2 */
#define FILE_QUATTRA_PRO            225   /* Quattra Pro */
#define FILE_RTF                    226   /* Rich Text Format */
#define FILE_RTF_MAC                227   /* Rich Text Format (Macintosh) */
#define FILE_RTF_WORD_60            228   /* Rich Text Format (Word 6.0) */
#define FILE_WINDOWS_WRITE          229   /* Windows Write */
#define FILE_WORD_WINDOWS_2X        230   /* Word for Windows 2.X */
#define FILE_WORD_WINDOWS_60        231   /* Word for Windows 6.0 */
#define FILE_WORD_OFFICE97          232   /* Word Office 97 */
#define FILE_WORDPERFECT_DOS_42     233   /* WordPerfect 4.2 (DOS) */
#define FILE_WORDPERFECT_WINDOWS    234   /* WordPerfect (Windows) */
#define FILE_WORDPERFECT_WINDOWS_60 235   /* WordPerfect 6.0 (Windows) */
#define FILE_WORDPERFECT_WINDOWS_61 236   /* WordPerfect 6.1 (Windows) */
#define FILE_WORDPERFECT_WINDOWS_7X 237   /* WordPerfect 7X (Windows) */
#define FILE_WORDSTAR_WINDOWS_1X    238   /* WordStar 1.X (Windows) */
#define FILE_WORKS                  239   /* Works */
#define FILE_XDOC                   240   /* Xerox XDOC */

/* Other formats */
#define FILE_MOV                    241   /* Apple QuickTime */
#define FILE_MIDI                   242   /* MIDI music file */
#define FILE_MPEG1                  243   /* MPEG-1 file */
#define FILE_AU                     244   /* SUN sound file */
#define FILE_AIFF                   245   /* Apple/SGI sound file */
#define FILE_MPEG2                  246   /* MPEG-2 file */

#define FILE_SVG                    247   /* SVG */

#define FILE_NITF                   248   /* NITF */
#define FILE_PTOCA                  249   /* PTOCA */
#define FILE_SCT                    250
#define FILE_PCL                    251
#define FILE_AFP                    252
#define FILE_ICA_UNCOMPRESSED       253
#define FILE_RAWICA_UNCOMPRESSED    254
#define FILE_SHP                    255   /* ESRI */
#define FILE_SMP                    256
#define FILE_SMP_G3_1D              257   /*CCITT Group 3 1D*/
#define FILE_SMP_G3_2D              258   /*CCITT Group 3 2D*/
#define FILE_SMP_G4                 259   /*CCITT Group 4   */

#define FILE_VWPG                   260   /*vector WPG*/
#define FILE_CMX                    261

#define FILE_TGA_RLE                262   /* RLE Compressed TGA */

#define FILE_KDC_120                263
#define FILE_KDC_40                 264
#define FILE_KDC_50                 265
#define FILE_DCS                    266

#define FILE_PSP                    267
#define FILE_PSP_RLE                268

#define FILE_TIFX_JBIG              269
#define FILE_TIFX_JBIG_T43          270
#define FILE_TIFX_JBIG_T43_ITULAB   271
#define FILE_TIFX_JBIG_T43_GS       272
#define FILE_TIFX_FAX_G4            273
#define FILE_TIFX_FAX_G3_1D         274
#define FILE_TIFX_FAX_G3_2D         275
#define FILE_TIFX_JPEG              276

#define FILE_ECW                    277
#define FILE_RAS_RLE                288
#define FILE_SVG_EMBED_IMAGES       289
#define FILE_DXF_R13                290
#define FILE_CLP_RLE                291
#define FILE_DCR                    292

#define FILE_DICOM_J2K_GRAY         293
#define FILE_DICOM_J2K_COLOR        294

#define FILE_FIT                    295
#define FILE_CRW                    296
#define FILE_DWF_TEXT_AS_POLYLINE   297
#define FILE_CIN                    298
#define FILE_PCL_TEXT_AS_POLYLINE   299
#define FILE_EPSPOSTSCRIPT          300
#define FILE_INTERGRAPH_CCITT_G4    301

#define FILE_SFF                    302
#define FILE_IFF_ILBM_UNCOMPRESSED  303
#define FILE_IFF_CAT_UNCOMPRESSED   304
#define FILE_RTF_RASTER             305
#define FILE_SID                    306
#define FILE_WMZ                    307
#define FILE_DJVU                   308

/*
    compression type
*/
#define LEAD                      0 /* LEAD  Proprietary */
#define JFIF                      1 /* JPEG  4:4:4 */
#define JTIF                      2 /* JPEG  4:4:4 */
#define LEAD1JFIF                 3 /* JPEG  4:1:1 */
#define LEAD1JTIF                 4 /* JPEG  4:1:1 */
#define LEAD2JFIF                 5 /* JPEG  4:2:2 */
#define LEAD2JTIF                 6 /* JPEG  4:2:2 */

#define LEAD_0                    0 /* LEAD 1 bit, lossless compression */
#define LEAD_1                    1 /* LEAD 1 bit, excellent compression */

#define TIFF_CCITT                3 /* TIFF  CCITT */
#define TIFF_CCITTG3_FAX1D        4 /* CCITT Group3 one dimensional */
#define TIFF_CCITTG3_FAX2D        5 /* CCITT Group3 two dimensional */
#define TIFF_CCITTG4_FAX          6 /* CCITT Group4 two dimensional */

/*
   preset Q factors (for LEAD CMP only)
*/
#define PQ1           -1        /* Perfect quality option 1 */
#define PQ2           -2        /* Perfect quality option 2 */
#define QFS           -3        /* Quality far more important than size */
#define QMS           -4        /* Quality more important than size */
#define QS            -5        /* Quality and size are equally important */
#define SQS           -6        /* Size more important than quality -Sharp */
#define SQT           -7        /* Size more important than quality - Less
                                   Tilling */
#define MCQ           -8        /* Max Compression, keeping quality as good
                                   as possible */
#define MC            -9        /* Max compression */

/*
   flags for L_*Comment
   the following indicate the associated strings are nul terminated
*/
#define CMNT_SZARTIST               0  /* Person who created image. */
#define CMNT_SZCOPYRIGHT            1  /* Copyright notice. */
#define CMNT_SZDATETIME             2  /* "YYYY:MM:DD HH:MM:SS" format */
#define CMNT_SZDESC                 3  /* Description of image */
#define CMNT_SZHOSTCOMP             4  /* Computer/OP System in use. */
#define CMNT_SZMAKE                 5  /* Manufacturer of Equip. used to
                                          generate the image. */
#define CMNT_SZMODEL                6  /* Model Name/Number of Equip. ... */
#define CMNT_SZNAMEOFDOC            7  /* Doc name image was scanned from. */
#define CMNT_SZNAMEOFPAGE           8  /* Page name image was scanned from. */
#define CMNT_SZSOFTWARE             9  /* Name & Version of Software Packages
                                          used to gen the image. */
#define CMNT_SZPATIENTNAME          10 /* Patient name (DICOM) */
#define CMNT_SZPATIENTID            11 /* Patient ID (DICOM) */
#define CMNT_SZPATIENTBIRTHDATE     12 /* Patient birthdate (DICOM) */
#define CMNT_SZPATIENTSEX           13 /* Patient sex (DICOM) */
#define CMNT_SZSTUDYINSTANCE        14 /* Study instance ID (DICOM) */
#define CMNT_SZSTUDYDATE            15 /* Study date (DICOM) */
#define CMNT_SZSTUDYTIME            16 /* Study time (DICOM) */
#define CMNT_SZSTUDYREFERRINGPHYSICIAN 17 /* Referring physician (DICOM) */
#define CMNT_SZSERIESMODALITY       18 /* Series modality (DICOM) */
#define CMNT_SZSERIESID             19 /* Series ID (DICOM) */
#define CMNT_SZSERIESNUMBER         20 /* Series number (DICOM) */

/* Exif 1.0 and 1.1 comments */
#define CMNT_EXIFVERSION            21 /* Exif version */
#define CMNT_SZDATETIMEORIGINAL     22 /* Date and time the original image image is captured (Exif) */
#define CMNT_SZDATETIMEDIGITIZED    23 /* Date and time the file is generated (Exif) */
#define CMNT_SHUTTERSPEEDVALUE      24 /* Shutter speed (Exif) */
#define CMNT_APERTURE               25 /* Aperture value (Exif) */
#define CMNT_BRIGHTNESS             26 /* Brightness value (Exif) */
#define CMNT_EXPOSUREBIAS           27 /* Exposure bias (Exif) */
#define CMNT_MAXAPERTURE            28 /* Minimum lens f-number (Exif) */
#define CMNT_SUBJECTDISTANCE        29 /* Distance from lens to subject (m) (Exif) */
#define CMNT_METERINGMODE           30 /* Photometry mode (Exif) */
#define CMNT_LIGHTSOURCE            31 /* Light source (Exif) */ 
#define CMNT_FLASH                  32 /* Flash On/Off (Exif) */ 
#define CMNT_FOCALLENGTH            33 /* Focal length (Exif) */ 
#define CMNT_EXPOSURETIME           34 /* Exposure  (Exif) */
#define CMNT_FNUMBER                35 /* F-numnber (Exif) */
#define CMNT_MAKERNOTE              36 /* Maker note (Exif) */
#define CMNT_USERCOMMENT            37 /* User comment (Exif) */
#define CMNT_SZSUBSECTIME           38 /* Date Time subsec (Exif) */
#define CMNT_SZSUBSECTIMEORIGINAL   39 /* Date Time original subsec (Exif) */
#define CMNT_SZSUBSECTIMEDIGITIZED  40 /* Date Time digitized subsec (Exif) */

/* Exif 2.0 comments - comments introduced since Exif 1.1 */
#define CMNT_SUPPORTEDFLASHPIXVERSION  158   /* Supported FlashPix version (Exif) */
#define CMNT_COLORSPACE                159   /* Color space (Exif) */
#define CMNT_EXPOSUREPROGRAM           160   /* Exposure program (Exif) */
#define CMNT_SZSPECTRALSENSITIVITY     161   /* Spectral sensitivity (Exif) */
#define CMNT_ISOSPEEDRATINGS           162   /* ISO speed ratings (Exif) */
#define CMNT_OPTOELECTRICCOEFFICIENT   163   /* Optoelectric coefficient (Exif) */
#define CMNT_SZRELATEDSOUNDFILE        164   /* Related audio file (Exif) */
#define CMNT_FLASHENERGY               165   /* Flash energy (Exif) */
#define CMNT_SPATIALFREQUENCYRESPONSE  166   /* Spatial frequency response (Exif) */
#define CMNT_FOCALPLANEXRESOLUTION     167   /* Focal plane X Resolution (Exif) */
#define CMNT_FOCALPLANEYRESOLUTION     168   /* Focal plane Y Resolution (Exif) */
#define CMNT_SUBJECTLOCATION           169   /* Subject location (Exif) */
#define CMNT_EXPOSUREINDEX             170   /* Exposure index (Exif) */
#define CMNT_SENSINGMETHOD             171   /* Sensing method (Exif) */
#define CMNT_FILESOURCE                172   /* File source (Exif) */
#define CMNT_SCENETYPE                 173   /* Scene type (Exif) */
#define CMNT_CFAPATTERN                174   /* CFA Pattern (Exif) */

/* Exif 2.2 comments - comments introduced since Exif 2.0 */
#define CMNT_SUBJECTAREA               227
#define CMNT_CUSTOMRENDERED            228
#define CMNT_EXPOSUREMODE              229
#define CMNT_WHITEBALANCE              230
#define CMNT_DIGITALZOOMRATIO          231
#define CMNT_FOCALLENGTHIN35MMFILM     232
#define CMNT_SCENECAPTURETYPE          233
#define CMNT_GAINCONTROL               234
#define CMNT_CONTRAST                  235
#define CMNT_SATURATION                236
#define CMNT_SHARPNESS                 237
#define CMNT_DEVICESETTINGDESCRIPTION  238
#define CMNT_SUBJECTDISTANCERANGE      239
#define CMNT_SZIMAGEUNIQUEID           240

/* Exif 1.1 GPS comments */
#define CMNT_GPSVERSIONID              41
#define CMNT_GPSLATITUDEREF            42
#define CMNT_GPSLATITUDE               43
#define CMNT_GPSLONGITUDEREF           44
#define CMNT_GPSLONGITUDE              45
#define CMNT_GPSALTITUDEREF            46
#define CMNT_GPSALTITUDE               47
#define CMNT_GPSTIMESTAMP              48
#define CMNT_GPSSATELLITES             49
#define CMNT_GPSSTATUS                 50
#define CMNT_GPSMEASUREMODE            51
#define CMNT_GPSDOP                    52
#define CMNT_GPSSPEEDREF               53
#define CMNT_GPSSPEED                  54
#define CMNT_GPSTRACKREF               55
#define CMNT_GPSTRACK                  56
#define CMNT_GPSIMGDIRECTIONREF        57
#define CMNT_GPSIMGDIRECTION           58
#define CMNT_GPSMAPDATUM               59
#define CMNT_GPSDESTLATITUDEREF        60
#define CMNT_GPSDESTLATITUDE           61 
#define CMNT_GPSDESTLONGITUDEREF       62 
#define CMNT_GPSDESTLONGITUDE          63 
#define CMNT_GPSDESTBEARINGREF         64 
#define CMNT_GPSDESTBEARING            65 
#define CMNT_GPSDESTDISTANCEREF        66 
#define CMNT_GPSDESTDISTANCE           67 
/* Exif 2.2 comments - comments introduced since Exif 2.0 */
#define CMNT_GPSPROCESSINGMETHOD       241
#define CMNT_GPSAREAINFORMATION        242
#define CMNT_GPSDATESTAMP              243
#define CMNT_GPSDIFFERENTIAL           244


#define CMNT_FPXSUMMARYINFORMATION                    0x8001
#define CMNT_FPXTITLE                                     68
#define CMNT_FPXSUBJECT                                   69
#define CMNT_FPXAUTHOR                                    70
#define CMNT_FPXKEYWORDS                                  71
#define CMNT_FPXCOMMENTS                                  72
#define CMNT_FPXOLETEMPLATE                               73
#define CMNT_FPXLASTAUTHOR                                74
#define CMNT_FPXREVNUMBER                                 75
#define CMNT_FPXEDITTIME                                  76
#define CMNT_FPXLASTPRINTED                               77
#define CMNT_FPXCREATEDTM                                 78
#define CMNT_FPXLASTSAVEDTM                               79
#define CMNT_FPXPAGECOUNT                                 80
#define CMNT_FPXWORDCOUNT                                 81
#define CMNT_FPXCHARCOUNT                                 82
#define CMNT_FPXTHUMBNAIL                                 83
#define CMNT_FPXAPPNAME                                   84
#define CMNT_FPXSECURITY                                  85
#define CMNT_FPXSUMMARYINFORMATION1                   CMNT_FPXTITLE
#define CMNT_FPXSUMMARYINFORMATION2                   CMNT_FPXSECURITY
                                                      
#define CMNT_FPXFILESOURCEGROUP                       0x8002
#define CMNT_FPXFILESOURCE                                86
#define CMNT_FPXSCENETYPE                                 87
#define CMNT_FPXCREATIONPATH                              88
#define CMNT_FPXNAMEMANRELEASE                            89
#define CMNT_FPXUSERDEFINEDID                             90
#define CMNT_FPXORIGINALSHARPNESSAPPROXIMATION            91
#define CMNT_FPXFILESOURCEGROUP1                      CMNT_FPXFILESOURCE
#define CMNT_FPXFILESOURCEGROUP2                      CMNT_FPXORIGINALSHARPNESSAPPROXIMATION

#define CMNT_FPXINTELLECTUALPROPERTYGROUP             0x8004
#define CMNT_FPXCOPYRIGHT                                 92
#define CMNT_FPXLEGALBROKERFORORIGIMAGE                   93
#define CMNT_FPXLEGALBROKERFORDIGITALIMAGE                94
#define CMNT_FPXAUTHORSHIP                                95
#define CMNT_FPXINTELLECTUALPROPNOTES                     96
#define CMNT_FPXINTELLECTUALPROPERTYGROUP1            CMNT_FPXCOPYRIGHT
#define CMNT_FPXINTELLECTUALPROPERTYGROUP2            CMNT_FPXINTELLECTUALPROPNOTES

#define CMNT_FPXCONTENTDESCRIPTIONGROUP               0x8008
#define CMNT_FPXTESTTARGETINTHEIMAGE                      97
#define CMNT_FPXGROUPCAPTION                              98
#define CMNT_FPXCAPTIONTEXT                               99
#define CMNT_FPXPEOPLEINTHEIMAGE                         100
#define CMNT_FPXTHINGSINIMAGE                            101
#define CMNT_FPXDATEOFORIGINALIMAGE                      102
#define CMNT_FPXEVENTSINTHEIMAGE                         103
#define CMNT_FPXPLACESINTHE                              104
#define CMNT_FPXCONTENTDESCRIPTIONNOTES                  105
#define CMNT_FPXCONTENTDESCRIPTIONGROUP1              CMNT_FPXTESTTARGETINTHEIMAGE
#define CMNT_FPXCONTENTDESCRIPTIONGROUP2              CMNT_FPXCONTENTDESCRIPTIONNOTES

#define CMNT_FPXCAMERAINFORMATIONGROUP                0x8010
#define CMNT_FPXCAMERAMANUFACTURERNAME                   106
#define CMNT_FPXCAMERAMODELNAME                          107
#define CMNT_FPXCAMERASERIALNUMBER                       108
#define CMNT_FPXCAMERAINFORMATIONGROUP1               CMNT_FPXCAMERAMANUFACTURERNAME
#define CMNT_FPXCAMERAINFORMATIONGROUP2               CMNT_FPXCAMERASERIALNUMBER

#define CMNT_FPXPERPICTURECAMERASETTINGSGROUP         0x8020
#define CMNT_FPXCAPTUREDATE                              109
#define CMNT_FPXEXPOSURETIME                             110
#define CMNT_FPXFNUMBER                                  111
#define CMNT_FPXEXPOSUREPROGRAM                          112
#define CMNT_FPXBRIGHTNESSVALUE                          113
#define CMNT_FPXEXPOSUREBIASVALUE                        114
#define CMNT_FPXSUBJECTDISTANCE                          115
#define CMNT_FPXMETERINGMODE                             116
#define CMNT_FPXSCENEILLUMINANT                          117
#define CMNT_FPXFOCALLENGTH                              118
#define CMNT_FPXMAXIMUMAPERATUREVALUE                    119
#define CMNT_FPXFLASH                                    120
#define CMNT_FPXFLASHENERGY                              121
#define CMNT_FPXFLASHRETURN                              122
#define CMNT_FPXBACKLIGHT                                123
#define CMNT_FPXSUBJECTLOCATION                          124
#define CMNT_FPXEXPOSUREINDEX                            125
#define CMNT_FPXSPECIALEFFECTSOPTICALFILTER              126
#define CMNT_FPXPERPICTURENOTES                          127
#define CMNT_FPXPERPICTURECAMERASETTINGSGROUP1        CMNT_FPXCAPTUREDATE
#define CMNT_FPXPERPICTURECAMERASETTINGSGROUP2        CMNT_FPXPERPICTURENOTES

#define CMNT_FPXDIGITALCAMERACHARACTERIZATIONGROUP    0x8040
#define CMNT_FPXSENSINGMETHOD                            128
#define CMNT_FPXFOCALPLANEXRESOLUTION                    129
#define CMNT_FPXFOCALPLANEYRESOLUTION                    130
#define CMNT_FPXFOCALPLANERESOLUTIONUNIT                 131
#define CMNT_FPXSPACIALFREQUENCY                         132
#define CMNT_FPXCFAPATTERN                               133
#define CMNT_FPXSPECTRALSENSITIVITY                      134
#define CMNT_FPXISOSPEEDRATINGS                          135
#define CMNT_FPXOECF                                     136
#define CMNT_FPXDIGITALCAMERACHARACTERIZATIONGROUP1   CMNT_FPXSENSINGMETHOD
#define CMNT_FPXDIGITALCAMERACHARACTERIZATIONGROUP2   CMNT_FPXOECF

#define CMNT_FPXFILMDESCRIPTIONGROUP                  0x8080
#define CMNT_FPXFILMBRAND                                137
#define CMNT_FPXFILMCATEGORY                             138
#define CMNT_FPXFILMSIZEX                                139
#define CMNT_FPXFILMSIZEY                                140
#define CMNT_FPXFILMSIZEUNIT                             141
#define CMNT_FPXFILMROLLNUMBER                           142
#define CMNT_FPXFILMFRAMENUMBER                          143
#define CMNT_FPXFILMDESCRIPTIONGROUP1                 CMNT_FPXFILMBRAND
#define CMNT_FPXFILMDESCRIPTIONGROUP2                 CMNT_FPXFILMFRAMENUMBER

#define CMNT_FPXORIGINALDOCUMENTSCANDESCRIPTIONGROUP  0x8100
#define CMNT_FPXORIGINALSCANNEDIMAGESIZE                 144
#define CMNT_FPXORIGINALDOCUMENTSIZE                     145
#define CMNT_FPXORIGINALMEDIUM                           146
#define CMNT_FPXTYPEOFREFLECTIONORIGINAL                 147
#define CMNT_FPXORIGINALDOCUMENTSCANDESCRIPTIONGROUP1 CMNT_FPXORIGINALSCANNEDIMAGESIZE
#define CMNT_FPXORIGINALDOCUMENTSCANDESCRIPTIONGROUP2 CMNT_FPXTYPEOFREFLECTIONORIGINAL

#define CMNT_FPXSCANDEVICEPROPERTYGROUP               0x8200
#define CMNT_FPXSCANNERMANUFACTURERNAME                  148
#define CMNT_FPXSCANNERMODELNAME                         149
#define CMNT_FPXSCANNERSERIALNUMBER                      150
#define CMNT_FPXSCANSOFTWARE                             151
#define CMNT_FPXSCANSOFTWAREREVISIONDATE                 152
#define CMNT_FPXSERVICEBUREAUORGNAME                     153
#define CMNT_FPXSCANOPERATORID                           154
#define CMNT_FPXSCANDATE                                 155
#define CMNT_FPXLASTMODIFIEDDATE                         156
#define CMNT_FPXSCANNERPIXELSIZE                         157
#define CMNT_FPXSCANDEVICEPROPERTYGROUP1              CMNT_FPXSCANNERMANUFACTURERNAME
#define CMNT_FPXSCANDEVICEPROPERTYGROUP2              CMNT_FPXSCANNERPIXELSIZE

#define CMNT_SZTITLE                                     175 /* Title or caption for image */
#define CMNT_SZDISCLAIMER                                176 /* Legal Disclaimer */
#define CMNT_SZWARNING                                   177 /* Warning of nature of content */
#define CMNT_MISC                                        178 /* Miscellaneous comment */
#define CMNT_J2K_BINARY                                  179 /* Jpeg 2000 binary comment */
#define CMNT_J2K_LATIN                                   180 /* Jpeg 2000 latin comment */

/* IPTC comments */
#define IPTC_SEPARATOR                                1 /* '\001' is a separator used for repeatable comments */

#define CMNT_IPTC_FIRST                                  181   /* The first IPTC comment */
#define CMNT_IPTC_VERSION                                181   /* The version of IPTC comments (read-only) */
#define CMNT_IPTC_OBJECTTYPEREFERENCE                    182
#define CMNT_IPTC_OBJECTATTRIBUTEREFERENCE               183
#define CMNT_IPTC_OBJECTNAME                             184
#define CMNT_IPTC_EDITSTATUS                             185
#define CMNT_IPTC_EDITORIALUPDATE                        186
#define CMNT_IPTC_URGENCY                                187
#define CMNT_IPTC_SUBJECTREFERENCE                       188
#define CMNT_IPTC_CATEGORY                               189
#define CMNT_IPTC_SUPPLEMENTALCATEGORY                   190
#define CMNT_IPTC_FIXTUREIDENTIFIER                      191
#define CMNT_IPTC_KEYWORDS                               192
#define CMNT_IPTC_CONTENTLOCATIONCODE                    193
#define CMNT_IPTC_CONTENTLOCATIONNAME                    194
#define CMNT_IPTC_RELEASEDATE                            195
#define CMNT_IPTC_RELEASETIME                            196
#define CMNT_IPTC_EXPIRATIONDATE                         197
#define CMNT_IPTC_EXPIRATIONTIME                         198
#define CMNT_IPTC_SPECIALINSTRUCTIONS                    199
#define CMNT_IPTC_ACTIONADVISED                          200
#define CMNT_IPTC_REFERENCESERVICE                       201 
#define CMNT_IPTC_REFERENCEDATE                          202 
#define CMNT_IPTC_REFERENCENUMBER                        203 
#define CMNT_IPTC_DATECREATED                            204 
#define CMNT_IPTC_TIMECREATED                            205 
#define CMNT_IPTC_DIGITALCREATIONDATE                    206 
#define CMNT_IPTC_DIGITALCREATIONTIME                    207 
#define CMNT_IPTC_ORIGINATINGPROGRAM                     208 
#define CMNT_IPTC_PROGRAMVERSION                         209 
#define CMNT_IPTC_OBJECTCYCLE                            210
#define CMNT_IPTC_BYLINE                                 211
#define CMNT_IPTC_BYLINETITLE                            212
#define CMNT_IPTC_CITY                                   213
#define CMNT_IPTC_SUBLOCATION                            214
#define CMNT_IPTC_PROVINCE_STATE                         215
#define CMNT_IPTC_PRIMARYLOCATIONCODE                    216
#define CMNT_IPTC_PRIMARYLOCATIONNAME                    217
#define CMNT_IPTC_ORIGINALTRANSMISSIONREFERENCE          218
#define CMNT_IPTC_HEADLINE                               219
#define CMNT_IPTC_CREDIT                                 220
#define CMNT_IPTC_SOURCE                                 221
#define CMNT_IPTC_COPYRIGHT                              222
#define CMNT_IPTC_CONTACT                                223
#define CMNT_IPTC_CAPTION                                224
#define CMNT_IPTC_AUTHOR                                 225
#define CMNT_IPTC_LANGUAGEIDENTIFIER                     226
#define CMNT_IPTC_LAST                                   226   /* The last IPTC comment */

#define CMNT_LAST                   244 /* Last defined number for comments. */

#define CMNT_ALL                 0xFFFF

#define TAG_BYTE                    1
#define TAG_ASCII                   2
#define TAG_SBYTE                   6
#define TAG_UNDEFINED               7
#define TAG_SHORT                   3
#define TAG_SSHORT                  8
#define TAG_LONG                    4
#define TAG_SLONG                   9
#define TAG_FLOAT                   11
#define TAG_RATIONAL                5
#define TAG_SRATIONAL               10
#define TAG_DOUBLE                  12

#define GET_TAG_SIZE(pTagSize,uType,ulCount) \
   switch(uType)                    \
   {                                \
   case TAG_BYTE:                   \
   case TAG_ASCII:                  \
   case TAG_SBYTE:                  \
   case TAG_UNDEFINED:              \
      *(pTagSize) = 1L * (ulCount); \
      break;                        \
   case TAG_SHORT:                  \
   case TAG_SSHORT:                 \
      *(pTagSize) = 2L * (ulCount); \
      break;                        \
   case TAG_LONG:                   \
   case TAG_SLONG:                  \
   case TAG_FLOAT:                  \
      *(pTagSize) = 4L * (ulCount); \
      break;                        \
   case TAG_RATIONAL:               \
   case TAG_SRATIONAL:              \
   case TAG_DOUBLE:                 \
      *(pTagSize) = 8L * (ulCount); \
      break;                        \
   default:                         \
      *(pTagSize) = 0;              \
      break;                        \
   }

/*
    flags for L_SETLOADINFOCALLBACK
*/
#define LOADINFO_TOPLEFT      0x00000001 /* Image has TOP_LEFT View
                                            Perspective */
#define LOADINFO_ORDERRGB     0x00000002 /* Image has ORDERRGB Color Order */
#define LOADINFO_WHITEONBLACK 0x00000004 /* Image is white-on-black */
#define LOADINFO_LSB          0x00000008 /* Image is Least Significant Bit
                                            first fill order */
#define LOADINFO_TOPLEFT90    0x00000010 /* Image has TOP_LEFT90 View 
                                            Perspective */
#define LOADINFO_TOPLEFT270   0x00000020 /* Image has TOP_LEFT270 View 
                                            Perspective */
#define LOADINFO_REVERSE      0x00000040 /* Reverse (mirror) each line */

#define LOADINFO_TOPLEFT180   0x00000080 /* Image has TOP_LEFT180 View 
                                            Perspective */
#define LOADINFO_BOTTOMLEFT90    0x00000100 /* Image has BOTTOM_LEFT90 View 
                                            Perspective */
#define LOADINFO_BOTTOMLEFT180   0x00000200 /* Image has BOTTOM_LEFT180 View 
                                            Perspective */
#define LOADINFO_BOTTOMLEFT270   0x00000400 /* Image has BOTTOM_LEFT270 View 
                                            Perspective */
#define LOADINFO_PAD4            0x00000800 /* Each line is padded to a multiple of 4 bytes (raw data only) */

#define LOADINFO_PALETTE         0x00001000 /* For RAW data of 8 bpp or less, a palette is supplied in rgbQuad of LOADINFO*/

#define LOADINFO_BITFIELDS       0x00002000 /* For RAW BITFIELDS -- 3 color masks are specified in rgbColorMask of LOADINFO */
#define LOADINFO_ORDERGRAY       0x00004000 /* Image is grayscale */
#define LOADINFO_MOTOROLAORDER   0x00008000 /* Image bytes are in Motorola byte order (valid only for 16, 48 and 64-bit) */
#define LOADINFO_ORDERROMM       0x00010000 /* Image is ROMM */


/*
   LOADINFO structure
*/
typedef struct _LOADINFO
{
   L_INT Format;                /* File format: FILE_PCX, ... */
   L_INT Width;                 /* Image width */
   L_INT Height;                /* Image height */
   L_INT BitsPerPixel;          /* Bits per pixel */
   L_INT XResolution;           /* X resolution (DPI) */
   L_INT YResolution;           /* Y resolution (DPI) */
   L_UINT32 Offset;             /* Data offset */
   L_UINT32 Flags;              /* Special flags */

  //for RAW file filter */
   RGBQUAD        rgbQuad[256]; 

   //for RAW BITFIELDS - contains R,G,B color masks */
   L_UINT32       rgbColorMask[3];    

   // for RAW_PACKBITS */
   L_UINT32       uStripSize;             // size of strip after compression
   L_INT          nPhotoInt;              // TIFF tag  0-6  TIFF tag
   L_INT          nPlanarConfig;          // TIFF tag  1 = Chunky,  2 = Planar format
} LOADINFO, L_FAR * pLOADINFO;


/*
   flags that make up FILEINFO.Flags
*/
#define FILEINFO_INTERLACED            0x00000001
#define FILEINFO_PROGRESSIVE           0x00000002  /* progressive JPEG file */
#define FILEINFO_HAS_STAMP             0x00000004
#define FILEINFO_HAS_GLOBALBACKGROUND  0x00000008
#define FILEINFO_HAS_GLOBALPALETTE     0x00000010
#define FILEINFO_HAS_GLOBALLOOP        0x00000020
#define FILEINFO_COMPRESSED            0x00000040  /* the image can be loaded compressed */
#define FILEINFO_NOPALETTE             0x00000080  /* Grayscale TIF without a palette */
#define FILEINFO_ROTATED               0x00000100  /* Image with an extended ViewPerspective */
#define FILEINFO_SIGNED                0x00000200  /* Image with signed values for pixels */
#define FILEINFO_LOSSLESSJPEG          0x00000400  /* Internal flag, indicating that the JPEG file uses the lossless compression.
                                                      This flag will probably be removed in future versions */
#define FILEINFO_HAS_ALPHA             0x00000800  /* The file has alpha channel information */
#define FILEINFO_FORMATVALID           0x00001000  /* Only the format type is valid */
#define FILEINFO_INFOVALID             0x00002000  /* The whole FILEINFO structure is valid */
#define FILEINFO_LINK                  0x00004000  /* The file is a Windows 9x/NT link */
#define FILEINFO_IFDVALID              0x00008000  /* The IFD field is valid */
#define FILEINFO_USELOADINFO           0x00010000  /* Internal--do not use */
#define FILEINFO_NO_RESOLUTION         0x00020000  /* The file does not contain resolution information */

/*
   Flags for L_FileInfo (not to make up FILEINFO.Flags!)
*/

#define FILEINFO_TOTALPAGES            0x00000001  /* fill in FILEINFO.TotalPages */

/*
   structure used by L_FileInfo
*/
typedef struct struct_file_information
{
   L_INT    Format;              /* File format: FILE_PCX, ... */
   L_TCHAR  Name[16];            /* File name, including the Ext */
   L_INT    Width;               /* Image width */
   L_INT    Height;              /* Image height */
   L_INT    BitsPerPixel;        /* Bits per pixel */
   L_INT32  SizeDisk;            /* Size of file on disk */
   L_INT32  SizeMem;             /* Size of image in memory */
   L_TCHAR  Compression[20];     /* Compression method name */
   L_INT    ViewPerspective;     /* Image view prespective */
   L_INT    Order;               /* RGB order */
   L_INT    PageNumber;          /* Page number */
   L_INT    TotalPages;          /* Total number of pages present in the file */
   L_INT    XResolution;
   L_INT    YResolution;
   L_UINT32 Flags;               /* identifies file subtypes: progressive, interlaced */
   L_UINT   GlobalLoop;          /* Global animation loop count 0 = infinity */
   L_INT    GlobalWidth;         /* Global width */
   L_INT    GlobalHeight;        /* Global height */
   COLORREF GlobalBackground;    /* Global background color (see Flags) */
   RGBQUAD  GlobalPalette[256];  /* Global palette (see Flags) */
   L_UINT32 IFD;                 /* IFD offset (for TIF files only) */
   L_INT    Layers;              /* The number of layers in the file */
} FILEINFO, L_FAR * pFILEINFO;

/* helper macros for dealing with rotated bitmap info view perspectives */
#define INFOROTATED(pInfo) ((pInfo)->ViewPerspective == TOP_LEFT90 || (pInfo)->ViewPerspective == TOP_LEFT270 || (pInfo)->ViewPerspective == BOTTOM_LEFT90 || (pInfo)->ViewPerspective == BOTTOM_LEFT270)
#define INFOBASIC(pInfo) ((pInfo)->ViewPerspective == TOP_LEFT || (pInfo)->ViewPerspective == BOTTOM_LEFT)
#define INFOWIDTH(pInfo) (INFOROTATED(pInfo)?(pInfo)->Height:(pInfo)->Width)
#define INFOHEIGHT(pInfo) (INFOROTATED(pInfo)?(pInfo)->Width:(pInfo)->Height)

/*
   photo cd
*/
#define L_PCD_BASE_OVER_64   0  /* 64 x   96 */
#define L_PCD_BASE_OVER_16   1  /* 128 x  192 */
#define L_PCD_BASE_OVER_4    2  /* 256 x  384 */
#define L_PCD_BASE           3  /* 512 x  768 */
#define L_PCD_4BASE          4  /* 1024 x 1536 */
#define L_PCD_16BASE         5  /* 2048 x 3072 */

typedef struct pcdinfo
{
   L_INT resolution[6];
} PCDINFO, L_FAR * pPCDINFO;

/* structure for L_CreateThumbnailFromFile */
typedef struct thumboptions
{
   L_INT          nWidth;
   L_INT          nHeight;
   L_INT          nBits;
   L_UINT32       uCRFlags;
   L_BOOL         bMaintainAspect;
   L_BOOL         bForceSize;
   COLORREF       crBackColor;
   L_BOOL         bLoadStamp;
   L_BOOL         bResample;
} THUMBOPTIONS, L_FAR *pTHUMBOPTIONS;

/* New flags for the LOADFILEOPTION structure */
#define ELO_REVERSEBITS             0x00000001
#define ELO_GLOBALBACKGROUND        0x00000002
#define ELO_GLOBALPALETTE           0x00000004
#define ELO_GLOBALLOOP              0x00000008
#define ELO_ROTATED                 0x00000010 /* Load files with extended ViewPerspective - do not rotate them */
#define ELO_IGNOREVIEWTRANSFORMS    0x00000020 /* Load the image without the viewing transformations */
#define ELO_IGNORECOLORTRANSFORMS   0x00000040 /* Load the image without the color transformations */
#define ELO_SIGNED                  0x00000080 /* Load images with signed pixels without conversion */
#define ELO_DISABLEMMX              0x00000100 /* (JPEG only) Do not use MMX optimized code */
#define ELO_DISABLEP3               0x00000200 /* (JPEG only) Do not use P3-specific optimized code */
#define ELO_USEIFD                  0x00000400 /* (TIFF only) Use the IFD offset */
#define ELO_FORCECIELAB             0x00000800 /* (JPEG only) The file has CIELAB colorspace */
#define ELO_USEBADJPEGPREDICTOR     0x00001000 /* (JPEG only) Load lossless JPEG file using an incorrect predictor */
#define ELO_IGNOREPHOTOMETRICINTERP 0x00002000 /* (TIFF only) Use RGB colorspace instead of the 
                                                  PhotometricInterpretation stored in the file. Use this 
                                                  to disable the color conversion to RGB during the load process. */ 
#define ELO_FORCERGBFILE            0x00004000 /* (JPEG only) The file has RGB colorspace. */ 
#define ELO_MULTISPECTRALSCAN       0x00008000 /* Use uXXXScan values info when loading NITF files */
#define ELO_NOPALETTE               0x00010000 /* Use the new palette mechanism. Do not use GDI memory to store the palette */
#define ELO_FORCE_EPS_THUMBNAIL     0x00020000 /* (EPS only) Force loading of raster thumbnail data from postscript files */

/*
   Flags for the SAVEFILEOPTION structure
*/
#define ESO_REVERSEBITS          0x00000001
#define ESO_NOSUBFILETYPE        0x00000002
#define ESO_GLOBALBACKGROUND     0x00000004
#define ESO_GLOBALPALETTE        0x00000008
#define ESO_INTERLACED           0x00000010
#define ESO_GLOBALLOOP           0x00000020
#define ESO_NOPALETTE            0x00000040 /* save grayscale TIF without a palette */
#define ESO_SAVEWITHSTAMP        0x00000080 /* save a stamp if format supports it */
#define ESO_FIXEDPALETTESTAMP    0x00000100 /* save fixed palette stamps */
#define ESO_YCCSTAMP             0x00000200 /* save YCbCr stamps */
#define ESO_REPLACEPAGE          0x00000400 /* Replace the page specified by PageNumber */
#define ESO_INSERTPAGE           0x00000800 /* Insert image before the page specified by PageNumber */
#define ESO_JPEGSTAMP            0x00001000 /* save JPEG compressed stamps */
#define ESO_DISABLEMMX           0x00002000 /* Do not use MMX optimized code */
#define ESO_SAVEOLDJTIF          0x00004000 /* Write old style JTIF files */
#define ESO_NOPAGENUMBER         0x00008000 /* Do not save/update the PageNumber tag */
#define ESO_DISABLEP3            0x00010000 /* Do not use P3-specific optimized code */
#define ESO_USEIFD               0x00020000 /* Use the IFD offset */
#define ESO_MOTOROLAORDER        0x00040000 /* When possible, save files in Motorola byte order */
#define ESO_WITHOUTTIMESTAMP     0x00080000 /* save without time stamp*/ 

#define ESO_PDF_TEXT_ENCODING_NONE          0x00000000  /* PDF, no text encoding */
#define ESO_PDF_TEXT_ENCODING_ASCII_BASE85  0x00100000  /* PDF, ASCII BASE85 text encoding */
#define ESO_PDF_TEXT_ENCODING_ASCII_HEX     0x00200000  /* PDF, ASCII HEX text encoding */

#define ESO_PDF_TEXT_ENCODING_MASK           0x00300000  /* mask of the flags used for PDF text encoding */
#define ESO_PAD4                             0x00400000  /* Each line is padded to a multiple of 4 bytes (raw data only) */
#define ESO_PLT_BEZIER_CURVES                0x00800000  /* PLT filter should save bezier curves */
#define ESO_PDF_SAVE_USE_BITMAP_DPI          0x01000000  /* Use bitmap  DPI in calculating page dimensions when saving a PDF file . */
#define ESO_PHOTOMETRICINTERPRETATIONVALID   0x02000000
#define ESO_TILEINFOVALID                    0x04000000  /* Use TileWidth and TileHeight when saving TIFF files */
#define ESO_USEDITHERINGMETHOD               0x08000000  /* Use the DitheringMethod in the BITMAPHANDLE */
#define ESO_PRESERVEPALETTE                  0x10000000  /* Preserve the palette when saving TIFF CCITT files 
                                                            (might decrease compression ratio) */
#define ESO_PDF_SAVE_LOW_MEMORY_USAGE        0x20000000  /* Try to use less memory when creating a PDF file with JPEG or Fax compression*/
#define ESO_GENERATEGLOBALPALETTE   0x40000000  /* Generate global palette when saving GIF files */


// PhotometricInterpretation
typedef enum tagPHOTMTRICINTERP
{
   PME_MINISWHITE      =0  ,/* min value is white */
   PME_MINISBLACK      =1  ,/* min value is black */
   PME_RGB             =2  ,/* RGB color model */
   PME_PALETTE         =3  ,/* color map indexed */
   PME_MASK            =4  ,/* $holdout mask */
   PME_SEPARATED       =5  ,/* !color separations */
   PME_YCBCR           =6  ,/* !CCIR 601 */
   PME_CIELAB          =8   /* !1976 CIE L*a*b* */
} PHOTMTRICINTERP, L_FAR*pPHOTMTRICINTERP;


/*
   Values that can be used for LOADFILEOPTION.Passes. These values will
   generate default Progressive JPEG/CMP files (usually 10 passes/file) on 
   save and specifies how many passes to generate while decoding 
   Progressive JPEG/CMP files.
*/
#define CALLBACK_ONCE                0 /* callback just once at the end */
#define CALLBACK_WHEN_MEANINGFUL    -1 /* callback with only significant scans */
#define CALLBACK_ALWAYS             -2 /* callback with all scans */

typedef struct _LOADFILEOPTION
{
   L_UINT32 lSize;                     /* the size of the LOADFILEOPTION - use sizeof(LOADFILEOPTION) */
   L_INT    XResolution;
   L_INT    YResolution;
   L_UINT32 Flags;
   L_INT    Passes;
   L_INT    PageNumber;
   L_UINT   GlobalLoop;
   L_UINT32 IFD;
   L_UINT   uRedScan;   // the scan index of the red channel (NITF files only)
   L_UINT   uGreenScan; // the scan index of the green channel (NITF files only)
   L_UINT   uBlueScan;  // the scan index of the blue channel (NITF files only)
} LOADFILEOPTION, L_FAR * pLOADFILEOPTION;

typedef struct _SAVEFILEOPTION
{
   L_UINT32 lSize;                     /* the size of the SAVEFILEOPTION - use sizeof(SAVEFILEOPTION) */
   L_INT    Reserved1;
   L_INT    Reserved2;
   L_UINT32 Flags;
   L_INT    Passes;
   L_INT    PageNumber;
   L_INT    GlobalWidth;
   L_INT    GlobalHeight;
   L_UINT   GlobalLoop;
   COLORREF GlobalBackground;
   RGBQUAD  GlobalPalette[256];
   L_UINT   StampWidth;
   L_UINT   StampHeight;
   L_UINT   StampBits;

   // MPEG Specific Options -- Not set by user
   // These options can only be set with the Multimedia Toolkit

   L_BOOL            Constrained;
   L_BOOL            FieldPic;
   L_INT             FrameRate;
   L_INT             FramesGOP;
   L_INT             PelAspectRatio;
   L_INT             ProfileID;
   L_INT             LevelID;
   L_INT             ChromaFormat;
   L_INT             VideoFormat;
   L_INT             IntraDcPrec;
   L_INT32           BitRate; 
   L_CHAR            UserInfo[255];    // user defined data to be put in mpeg stream

   // end of the MPEG-specific options

   L_UINT32          IFD;
   L_TCHAR           szPassword[255];  // password for saving encrypted files
   PHOTMTRICINTERP   PhotometricInterpretation;
   L_UINT            TileWidth;
   L_UINT            TileHeight;
} SAVEFILEOPTION, L_FAR * pSAVEFILEOPTION;


typedef struct _SAVECUSTOMFILEOPTION
{
   L_UINT32 lSize;                        /* Size of the SAVECUSTOMFILEOPTION */
   L_UINT32 uFlags;                       /* Custom save options flags */
   L_INT    nTileWidth;                   /* Width of a tile */
   L_INT    nTileHeight;                  /* Height of a tile*/
   L_INT    nCompressionTag;              /* Compression Tag*/
   L_INT    nPlanarConfiguration;         /* Planar Configuration */
   L_INT    nPhotoMetricInterpretation;   /* Photo Metric Interpretation*/
} SAVECUSTOMFILEOPTION, L_FAR * pSAVECUSTOMFILEOPTION;

#define LOADCUSTOMFILEOPTION_FLIPTILES 0x0001

typedef struct _LOADCUSTOMFILEOPTION
{
   L_UINT32 lSize;/* Size of Structure */
   L_UINT32 uFlags;/* Custom load options flags */
} LOADCUSTOMFILEOPTION, L_FAR * pLOADCUSTOMFILEOPTION;

typedef struct _CUSTOMTILEINFO
{
   L_UINT32 lSize;/* Size of Structure */
   L_INT    nWidth;/* Width of tile to be compressed */
   L_INT    nHeight;/* Height of tile to be compressed */
   L_INT    nBitsPerPixel;/* Number of bits per pixel */
} CUSTOMTILEINFO, L_FAR * pCUSTOMTILEINFO;

/*
   flags for the FILEREADCALLBACK function
*/

#define FILEREAD_FIRSTPASS    0x0001
#define FILEREAD_LASTPASS     0x0002
#define FILEREAD_FIRSTROW     0x0004
#define FILEREAD_LASTROW      0x0008
#define FILEREAD_COMPRESSED   0x0010
#define FILEREAD_CLIPVERT     0x0020   // internal flag - data contains only the requested lines
#define FILEREAD_CLIPHORZ     0x0040   // internal flag - data contains only the requested columns

typedef struct _FILECOMMENTS
{
   L_INT           count;
   L_UCHAR L_FAR **pointer;
   L_UINT L_FAR   *size;
} FILECOMMENTS, L_FAR *LPFILECOMMENTS;

/*
   flags for the L_SaveFile and L_SaveFileOffset function
*/

typedef struct _DIMENSION
{
   L_UINT32 nWidth;
   L_UINT32 nHeight;
} DIMENSION, L_FAR*pDIMENSION;

typedef struct _FILETRANSFORMS {
   //AffineMatrix
   L_FLOAT a11, a12, a13, a14, a21, a22, a23, a24, a31, a32, a33, a34, a41, a42, a43, a44;
   //ColorTwistMatrix
   L_FLOAT byy, byc1, byc2, bc1y, bc1c1, bc1c2, bc2y, bc2c1, bc2c2;
   //ContrastAdjustment
   L_FLOAT fContrastAdjustment;
   //FilteringValue (Sharpness Adjustment)
   L_FLOAT fFilteringValue;
} FILETRANSFORMS, L_FAR  *pFILETRANSFORMS;

/*
   L_2DSetViewMode flags
*/
#define L2D_USE_BEST          0
#define L2D_USE_WIDTH_HEIGHT  1
#define L2D_USE_WIDTH         2
#define L2D_USE_HEIGHT        3

/*
   PLT Options
*/
typedef struct _FILEPLTOPTIONS
{
   L_INT             Size;
   L_INT             PenWidth[ 8 ];
   COLORREF          PenColor[ 8 ];
}
FILEPLTOPTIONS, L_FAR *pFILEPLTOPTIONS;


/*
   PDF Options
*/
#define FILEPDFOPTIONS_MAX_PASSWORD_LEN 64

/* PDF Options Flags */
#define PDF_DISABLE_CROPPING            0x00000001

typedef struct _FILEPDFOPTIONS
{
   L_INT    nSize                                        ;/*   The size of this structure */
   L_BOOL   bUseLibFonts                                 ;/*   Specifies whether to use the library installed fonts or system fonts, 
                                                               default is TRUE */
   L_INT    nXResolution                                 ;/*   Horizontal display resolution default is 96 */
   L_INT    nYResolution                                 ;/*   Vertical display resolution default is 96 */
   L_INT    nDisplayDepth                                ;/*   Bits per pixel for resulting bitmap, takes 1,4,8,24 default is 24 */
   L_INT    nTextAlpha                                   ;/*   Font Anti-Aliasing,takes 1(no anti-aliasing), 2 and 4 .Default is 4 */
   L_INT    nGraphicsAlpha                               ;/*   Graphics Anti-Aliasing takes 1,2,4.Default is 1 */
   L_CHAR   szPassword[FILEPDFOPTIONS_MAX_PASSWORD_LEN]  ;/*   Password to be used with encrypted PDF files */
   L_UINT32 uFlags;
}
FILEPDFOPTIONS , L_FAR * pFILEPDFOPTIONS;

/*
   RTF Options
*/

typedef struct _FILERTFOPTIONS
{
   L_INT    nSize                                        ;/*   The size of this structure */
   L_DOUBLE dTopMarg;
   L_DOUBLE dBottomMarg;
   L_DOUBLE dRightMarg;
   L_DOUBLE dLeftMarg;
   L_DOUBLE dPaperWidth;
   L_DOUBLE dPaperHeight;
}
FILERTFOPTIONS , L_FAR * pFILERTFOPTIONS;

/*
   PTK Options
*/

typedef struct _FILEPTKOPTIONS
{
   L_UINT   uStructSize;         /* the size of this structure */
	L_INT    nPTKResolution;      /* Display resolution default is 96*/
}
FILEPTKOPTIONS , L_FAR * pFILEPTKOPTIONS;


/*
   J2K/new CMP Options
*/
// Limitations imposed by the standard
#define J2K_MAX_COMPONENTS_NUM (3)
#define J2K_MAX_DECOMP_LEVEL (20)


// Progressions Order
#define J2K_LAYER_RESOLUTION_COMPONENT_POSITION 0 
#define J2K_RESOLUTION_LAYER_COMPONENT_POSITION 1 
#define J2K_RESOLUTION_POSITION_COMPONENT_LAYER 2 
#define J2K_POSITION_COMPONENT_RESOLUTION_LAYER 3 
#define J2K_COMPONENT_POSITION_RESOLUTION_LAYER 4

// Ways of controlling the compression
typedef enum tagJ2KCOMPRESSIONCONTROL
{
   J2K_COMPRESSION_LOSSLESS,     // lossless compression
   J2K_COMPRESSION_RATIO,        // use fCompressionRatio
   J2K_COMPRESSION_TARGETSIZE,   // use uTargetFileSize
   J2K_COMPRESSION_QFACTOR,      // use qFactor
} J2KCOMPRESSIONCONTROL, L_FAR*pJ2KCOMPRESSIONCONTROL;




// Ways of how to set the Region Of Interest 
typedef enum tagJ2KREGIONOFINTEREST
{
   J2K_USE_LEAD_REGION,          // Use LEAD bitmap region
   J2K_USE_OPTION_RECT,          // Use rcROI member of FILEJ2KOPTIONS
} J2KREGIONOFINTEREST, L_FAR*pJ2KREGIONOFINTEREST;



// Bit values for the code blocks
//
typedef struct _CodBlockStyle
{
   L_UINT   bSelectiveACBypass:1;
   L_UINT   bResetContextOnBoundaries:1;
   L_UINT   bTerminationOnEachPass:1;
   L_UINT   bVerticallyCausalContext:1;
   L_UINT   bPredictableTermination:1;
   L_UINT   bErrorResilienceSymbol:1;
   L_UINT   bReserved6:26;
} CodBlockStyle;

typedef struct _tagFILEJ2KOPTIONS
{
   L_INT    nSize;      // the size of this structure
   //<----------------------
   L_BOOL bUseColorTransform;
   L_BOOL bDerivedQuantization;
   J2KCOMPRESSIONCONTROL uCompressionControl;
   L_FLOAT  fCompressionRatio;
   L_UINT32 uTargetFileSize;
   //<------------------ SIZ_MARKER
   L_UINT32 uXOsiz;  // Horizontal offset from the origin of the reference grid to the left side of the image area.
   L_UINT32 uYOsiz;  // Vertical offset from the origin of the reference grid to the top side of the image area.
   L_UINT32 uXTsiz;  // Width of one reference tile with respect to the reference grid.
   L_UINT32 uYTsiz;  // Height of one reference tile with respect to the reference grid.
   L_UINT32 uXTOsiz; // Horizontal offset from the origin of the reference grid to the left side of the first tile.
   L_UINT32 uYTOsiz; // Vertical offset from the origin of the reference grid to the top side of the first tile.
   L_UINT32 uXRsiz  [J2K_MAX_COMPONENTS_NUM];  // Horizontal Sub_sampling Value
   L_UINT32 uYRsiz  [J2K_MAX_COMPONENTS_NUM];  // Vertical Sub_sampling Value 
   //<----------------- COD_MARKER
   L_UINT   uDecompLevel;   // Number of decomposition levels, dyadic decomposition (Zero Implies no transform )
   L_UINT   uProgressOrder; // Progressing Order
   L_INT    nCodBlockWidth; // 
   L_INT    nCodBlockHeight;
   CodBlockStyle CodBlockStyleFlags;
   //<------------------------ QCD_MARKER
   L_UINT   uGuardBits; 
   L_INT nDerivedBaseMantissa; 
   L_INT nDerivedBaseExponent;
   //---- Aditional Markers-------
   L_BOOL bUseSOPMarker;
   L_BOOL bUseEPHMarker;
   
   //<-- ROI ----
   J2KREGIONOFINTEREST uROIControl;
   L_BOOL  bUseROI;
   L_FLOAT fROIWeight;
   RECT    rcROI;
} FILEJ2KOPTIONS, L_FAR*pFILEJ2KOPTIONS;

/*
   callbacks
*/

typedef L_INT (pEXT_FUNCTION FLTLOADBUFFER) (L_CHAR *pInput, L_UINT32 nLength, L_CHAR *pOutput, L_INT nFormat, L_INT32 nWidth, L_INT32 nHeight, L_UINT32 nBitsPerPixel, L_VOID *pLeadHdr, L_UINT   uFlags);
typedef L_INT (pEXT_FUNCTION FLTSAVEBUFFER) (L_UCHAR L_FAR*pInput, LPBITMAPINFOHEADER pbiInput, L_UCHAR L_FAR*pOutput, L_UINT32 L_FAR*pdwSize, L_INT32 nQFactor, L_UINT uFlags, L_UINT nFormat, L_UCHAR L_FAR*pTopBuffer, L_INT nTopBufferHeight);

typedef struct tagJ2KVIDEOINFO
{
   int      nSize;
   int      nVersion;
   BOOL		bReversible; 
	BOOL		bUseColorTransform;
   int 		nMaxBytes;
   int      nBytePerLine;
   int      nBits;
   int      nColorSubSampling; // Type of the color component subsampling
   int      nQuality;
	DWORD	   uFrameWidth;       // Frame Width 
	DWORD	   uFrameHeight;      // Frame Height 
	DWORD	   uDecompLevel;      // Number of decomposition levels, dyadic decomposition (Zero Implies no transform )
	int 	   nTransform;	       // Wavelet Transform used ( Type of wavelet filter ex. 9x7 or 5x3 );
   int      nViewSize;
   int      nSIMD;  
} J2KVIDEOINFO, *pJ2KVIDEOINFO;


/*****************************************************************************/
/*                J2K Frame Decomporession External Function                 */
/*****************************************************************************/
typedef L_INT (pEXT_FUNCTION FLTJ2KDECOMPRESSFRAME) ( BYTE *pInData ,BYTE *pOutData ,pJ2KVIDEOINFO pJ2KInfo );



typedef L_INT (pEXT_CALLBACK COMPBUFFCALLBACK) (pBITMAPHANDLE, L_UCHAR L_FAR *, L_UINT, L_VOID L_FAR *);
typedef L_INT (pEXT_CALLBACK LOADINFOCALLBACK) (L_INT, pLOADINFO, L_VOID L_FAR*);
typedef L_INT (pEXT_CALLBACK FILEREADCALLBACK) (pFILEINFO, pBITMAPHANDLE, L_UCHAR L_FAR *, L_UINT, L_INT, L_INT, L_VOID L_FAR *);
typedef L_INT (pEXT_CALLBACK FILESAVECALLBACK) (pBITMAPHANDLE, L_UCHAR L_FAR *, L_UINT, L_UINT, L_VOID L_FAR *);
typedef L_INT (pEXT_CALLBACK SAVECUSTOMFILECALLBACK) (pCUSTOMTILEINFO pTileInfo,
                                                      L_UCHAR L_FAR*  pUncompressedBuffer,
                                                      L_UINT          UncompressedBufferSize ,
                                                      L_UCHAR L_FAR*  pCompressedBuffer,
                                                      L_UINT          CompressedBufferSize ,
                                                      L_UINT*         puActualBytesCompressed,
                                                      L_VOID L_FAR*   pUserData);

typedef L_INT (pEXT_CALLBACK LOADCUSTOMFILECALLBACK) (L_UCHAR L_FAR*    pCompressedTileBuffer,
                                                      L_UINT            uCompressedBufferSize,
                                                      L_UCHAR L_FAR*    pDeCompressedTileBuffer,
                                                      L_UINT            uDeCompressedBufferSize,
                                                      pCUSTOMTILEINFO   pTileInfo,
                                                      L_VOID L_FAR*     pUserData);

typedef L_INT (pEXT_CALLBACK SAVEBUFFERCALLBACK)
                                                     (
                                                      L_UINT32         uRequiredSize,
                                                      L_UCHAR          **ppBuffer,
                                                      L_UINT32 L_FAR   *pdwBufferSize,
                                                      L_VOID L_FAR     *pUserData);


#define DECOMPRESS_LSB           (LOADINFO_LSB)
#define DECOMPRESS_PAD4          (LOADINFO_PAD4)
#define DECOMPRESS_PALETTE       (LOADINFO_PALETTE)

#define DECOMPRESS_STRIPS             (0)  //compressed strip contains complete rows
#define DECOMPRESS_TILES              (2)

//Flags to indicate if beginning, end of a strip
#define DECOMPRESS_CHUNK_START        (1)
#define DECOMPRESS_CHUNK_END          (2)
#define DECOMPRESS_CHUNK_COMPLETE     (DECOMPRESS_CHUNK_START | DECOMPRESS_CHUNK_END)


typedef struct _STARTDECOMPRESSDATA
{
   L_INT32          nSize;            // for versioning-- use sizeof(STARTDECOMPRESSDATA)
   pBITMAPHANDLE    pBitmap;          // Pointer to the bitmap handle to load the image to
   L_UINT           uStripsOrTiles;   // DECOMPRESS_STRIPS -- indicates that we are decompressing strips of data
                                      // DECOMPRESS_TILES  -- indicates that we are decompressing tiles of data
                                      // The main difference is that strips have a width equal to the bitmap width
                                      // but tiles can have a width that is less than the bitmap width
                                      // Note that the pfnReadCallback (desribed below) is not fired for DECOMPRESS_TILES
   L_UINT           uFormat;	        // One of the following formats:
                                      //      FILE_JFIF      
                                      //      FILE_RAW_RLE4
                                      //      FILE_RAW_RLE8
                                      //      FILE_RAW_BITFIELDS
                                      //      FILE_RAW_PACKBITS
                                      //      FILE_RAW_CCITT
                                      //      FILE_FAX_G3_1D
                                      //      FILE_FAX_G3_2D
                                      //      FILE_FAX_G4
   L_INT            nWidth;           // Bitmap width
   L_INT            nHeight;          // Bitmap Height
   L_INT            nBitsPerPixel;    // Bits per pixel of raw data

   L_INT            nViewPerspective; // View perspective of raw data--one of the following constants:

                                      //      TOP_LEFT
                                      //      TOP_LEFT90
                                      //      TOP_LEFT180 
                                      //      TOP_LEFT270  
                                      //      BOTTOM_LEFT
                                      //      BOTTOM_LEFT90  
                                      //      BOTTOM_LEFT180      
                                      //      BOTTOM_LEFT270 

   L_INT            nRawOrder;        // Color order of 24-bit raw data (ORDER_RGB, ORDER_BGR)
                                      // Ignored if palettized
   L_INT            nLoadOrder;       // Desired color order after 24-bit image is loaded (Ignored if palettized)
            
   L_INT            nXResolution;     // Horizontal resolution, in dots per inch.
   L_INT            nYResolution;     // Vertical resolution, in dots per inch.

   FILEREADCALLBACK pfnReadCallback;  // Optional callback function for additional processing.
                                      // If you do not provide a callback function, use NULL as the value of this parameter.
                                      // If you do provide a callback function, use the function pointer as the value of this parameter.
                                      // The callback function must adhere to the function prototype described in FILEREADCALLBACK Function.

   RGBQUAD          Palette[256];     // Palette for uncompressed data that is 8 bits per pixel or less. 
                                      // Fill in the first 2^BitsPerPixel entries in this palette and include DECOMPRESS_PALETTE in the uFlags field.
   L_UINT32         uFlags;           // Any combination of the following flags:
                                      // DECOMPRESS_LSB          -- The least significant bit is filled first.
                                      // DECOMPRESS_PAD4         -- Each line is padded to a multiple of 4 bytes
                                      // DECOMPRESS_PALETTE      -- A palette is supplied in the rgbQuad field
   L_VOID          *pUserData;        //
   
   L_UINT32         rgbColorMask[3];  // Valid for FILE_RAW_BITFIELDS only - contains R,G,B color masks
                                      // rgbColorMask[0] is the red mask     
                                      // rgbColorMask[1] is the green mask     
                                      // rgbColorMask[2] is the blue mask  
                                      // For example, with 16-bit data arranged like (RRR RRGG GGGB BBBB), the masks would be
                                      //     rgbColorMask[0] = 0x7C00
                                      //     rgbColorMask[1] = 0x0E30
                                      //     rgbColorMask[2] = 0x001F   
                                      // For 32-bit data, the only valid data is (RRRR RRRR GGGG GGGG BBBB BBBB)
                                      //     rgbColorMask[0] = 0xFF0000
                                      //     rgbColorMask[1] = 0x00FF00
                                      //     rgbColorMask[2] = 0x0000FF   
   
   L_INT            nPhotoInt;        // For:
                                      //      FILE_RAW_CCITT, FILE_FAX_G3_1D, FILE_FAX_G3_2D, FILE_FAX_G4 
                                      //         0 = WhiteIsZero,  
                                      //         1 = BlackIsZero 
                                      //
                                      //      FILE_RAW_PACKBITS
                                      //         0 = WhiteIsZero,  
                                      //         1 = BlackIsZero 
                                      //         2 = There is no ColorMap (RGB)
                                      //         5 = Separated - CMYK
                                      //         6 = YC b C r color space
                                      //         8 = 1976 CIE L*a*b*

   L_INT            nPlanarConfig;    // For FILE_RAW_PACKBITS only
                                      //      1 = Chunky
                                      //      2 = Planar format

   L_UINT32         uReserved1;       // Reserved for future use
   
} STARTDECOMPRESSDATA, *pSTARTDECOMPRESSDATA;


typedef struct _DECOMPRESSDATA
{
   L_INT32        nSize;            // for versioning-- use sizeof(STARTDECOMPRESSDATA)
                                    //
   L_UCHAR       *pBuffer;          // pointer to raw compressed data
                                    //
   L_INT          nWidth;           // width of uncompressed strip/tile in bytes
                                    //    For strips, this is the width of the image
                                    //    For tiles, this is usually a fraction of the image width
                                    //    
   L_INT          nHeight;          // height of uncompressed strip/tile in bytes
                                    //    If the image consists of one single compressed strip (as with TWAIN), 
                                    //    this is the height of the image
                                    //
   L_UINT32       uOffset;          // offset of strip relative to buffer -- usually zero
   L_INT          nBufferSize;      // size of strip after compression  
                                    //    For TWAIN, this is the buffer size determined by DAT_SETUPMEMXFER
                                    //
   L_INT          nRow;             // Row offset of tile or strip
                                    //
   L_INT          nCol;             // Column offset of tile
                                    //    For strips, this value is ignored
                                    //
   L_UINT         uFlags;           // Flags used for tiles or strips
                                    //    DECOMPRESS_STRIP_START
                                    //    DECOMPRESS_STRIP_END
                                    //    DECOMPRESS_CHUNK_COMPLETE (note: this is DECOMPRESS_STRIP_START | DECOMPRESS_STRIP_END)
                                    // If pBuffer does not point to a full strip or tile you set uFlags to DECOMPRESS_STRIP_START 
                                    //    when the strip/tile begins and DECOMPRESS_STRIP_END when the strip/tile ends
                                    // If pBuffer points to a complete strip/tile, then set this to DECOMPRESS_CHUNK_COMPLETE
   L_INT          nReserved1;       // Reserved for future use
} DECOMPRESSDATA, *pDECOMPRESSDATA;


L_INT EXT_FUNCTION L_CompressBuffer (L_UCHAR L_FAR * pBuffer);

L_INT EXT_FUNCTION L_DeletePage(L_TCHAR L_FAR*pszFile, 
                                L_INT nPage,
                                L_UINT uFlags,
                                pSAVEFILEOPTION pSaveOptions);

L_INT EXT_FUNCTION L_EndCompressBuffer (L_VOID);

L_INT EXT_FUNCTION L_ReadLoadResolutions (L_TCHAR L_FAR *pszFile, 
                                     pDIMENSION pDimensions, 
                                     L_INT L_FAR *pDimensionCount,
                                     pLOADFILEOPTION pLoadOptions);

L_INT EXT_FUNCTION L_FeedLoad (HGLOBAL hLoad,
                                L_UCHAR L_FAR * pBuffer,
                                L_UINT32 dwBufferSize);

L_INT EXT_FUNCTION L_FileConvert (L_TCHAR L_FAR * pszFileSrc,
                                   L_TCHAR L_FAR * pszFileDst,
                                   L_INT nType,
                                   L_INT nWidth,
                                   L_INT nHeight,
                                   L_INT nBitsPerPixel,
                                   L_INT nQFactor,
                                   pLOADFILEOPTION pLoadOptions,
                                   pSAVEFILEOPTION pSaveOptions,
                                   pFILEINFO pFileInfo);

L_INT EXT_FUNCTION L_FileInfo (L_TCHAR L_FAR * pszFile,
                                pFILEINFO pFileInfo,
                                L_UINT uFlags,
                                pLOADFILEOPTION pLoadOptions);

L_INT EXT_FUNCTION L_FileInfoMemory (L_CHAR L_FAR * pBuffer,
                                      pFILEINFO pFileInfo,
                                      L_INT32 nBufferSize,
                                      L_UINT uFlags,
                                      pLOADFILEOPTION pLoadOptions);

L_INT EXT_FUNCTION L_GetComment (L_UINT uType,
                                  L_UCHAR L_FAR * pComment,
                                  L_UINT uLength);

L_INT EXT_FUNCTION L_GetLoadResolution (L_INT nFormat,
                                   L_UINT32 L_FAR *pWidth,
                                   L_UINT32 L_FAR *pHeight,
                                   pLOADFILEOPTION pLoadOptions);

L_INT EXT_FUNCTION L_GetFileCommentSize (L_TCHAR L_FAR *pszFile,
                                       L_UINT uType,
                                       L_UINT L_FAR *uLength,
                                       pLOADFILEOPTION pLoadOptions);

L_INT32 EXT_FUNCTION L_GetTag (L_UINT16 uTag,
                              L_UINT16 L_FAR*pType,
                              L_UINT32 L_FAR*pCount,
                              L_VOID L_FAR*pData);

L_INT EXT_FUNCTION L_LoadBitmap (L_TCHAR L_FAR * pszFile,
                                  pBITMAPHANDLE pBitmap,
                                  L_INT nBitsPerPixel,
                                  L_INT nOrder,
                                  pLOADFILEOPTION pLoadOptions,
                                  pFILEINFO pFileInfo);

L_INT EXT_FUNCTION L_LoadBitmapList (L_TCHAR L_FAR *lpszFile,
                                     pHBITMAPLIST phList,
                                     L_INT nBitsTo,
                                     L_INT nColorOrder,
                                     pLOADFILEOPTION pLoadOptions,
                                     pFILEINFO pFileInfo);

L_INT EXT_FUNCTION L_LoadBitmapMemory (L_CHAR L_FAR * pBuffer,
                                        pBITMAPHANDLE pBitmap,
                                        L_INT nBitsPerPixel,
                                        L_INT nOrder,
                                        L_INT32 nBufferSize,
                                        pLOADFILEOPTION pLoadOptions,
                                        pFILEINFO pFileInfo);

L_INT EXT_FUNCTION L_LoadFile (L_TCHAR L_FAR * pszFile,
                                pBITMAPHANDLE pBitmap,
                                L_INT nBitsPerPixel,
                                L_INT nOrder,
                                L_UINT uFlags,
                                FILEREADCALLBACK pfnCallback,
                                L_VOID L_FAR * pUserData,
                                pLOADFILEOPTION pLoadOptions,
                                pFILEINFO pFileInfo);

L_INT EXT_FUNCTION L_LoadFileTile (L_TCHAR L_FAR * pszFile,
                                   pBITMAPHANDLE pBitmap,
                                   L_INT nCol,
                                   L_INT nRow,
                                   L_UINT uWidth,
                                   L_UINT uHeight,
                                   L_INT nBitsPerPixel,
                                   L_INT nOrder,
                                   L_UINT uFlags,
                                   FILEREADCALLBACK pfnCallback,
                                   L_VOID L_FAR * pUserData,
                                   pLOADFILEOPTION pLoadOptions,
                                   pFILEINFO pFileInfo);

L_INT EXT_FUNCTION L_LoadMemoryTile(L_CHAR L_FAR *    pBuffer,
                                    pBITMAPHANDLE     pBitmap,
                                    L_INT             nCol,
                                    L_INT             nRow,
                                    L_UINT            uWidth,
                                    L_UINT            uHeight,
                                    L_INT             nBitsPerPixel,
                                    L_INT             nOrder,
                                    L_UINT            uFlags,
                                    FILEREADCALLBACK  pfnCallback,
                                    L_VOID L_FAR *    pUserData,
                                    L_INT32           nBufferSize,
                                    pLOADFILEOPTION   pLoadOptions,
                                    pFILEINFO         pFileInfo);

L_INT EXT_FUNCTION L_LoadFileOffset (L_INT fd,
                                      L_INT32 nOffsetBegin,
                                      L_INT32 nBytesToLoad,
                                      pBITMAPHANDLE pBitmap,
                                      L_INT nBitsPerPixel,
                                      L_INT nOrder,
                                      L_UINT uFlags,
                                      FILEREADCALLBACK pfnCallback,
                                      L_VOID L_FAR * pUserData,
                                      pLOADFILEOPTION pLoadOptions,
                                      pFILEINFO pFileInfo);

L_INT EXT_FUNCTION L_LoadMemory (L_CHAR L_FAR * pBuffer,
                                  pBITMAPHANDLE pBitmap,
                                  L_INT nBitsPerPixel,
                                  L_INT nOrder,
                                  L_UINT uFlags,
                                  FILEREADCALLBACK pfnCallback,
                                  L_VOID L_FAR * pUserData,
                                  L_INT32 nBufferSize,
                                  pLOADFILEOPTION pLoadOptions,
                                  pFILEINFO pFileInfo);

L_INT EXT_FUNCTION L_ReadFileComment (L_TCHAR L_FAR *pszFile,
                                       L_UINT uType,
                                       L_UCHAR L_FAR *pComment,
                                       L_UINT uLength,
                                       pLOADFILEOPTION pLoadOptions);

L_INT EXT_FUNCTION L_ReadFileCommentExt (L_TCHAR L_FAR *pszFile,
                                       L_UINT uType,
                                       LPFILECOMMENTS pComments,
                                       L_UCHAR L_HUGE *pBuffer,
                                       L_UINT L_FAR *uLength,
                                       pLOADFILEOPTION pLoadOptions);

L_INT EXT_FUNCTION L_ReadFileCommentMemory (L_CHAR L_FAR * pBuffer,
                                       L_UINT uType,
                                       L_UCHAR L_FAR * pComment,
                                       L_UINT uLength,
                                       L_INT32 nBufferSize,
                                       pLOADFILEOPTION pLoadOptions);

L_INT32 EXT_FUNCTION L_ReadFileTag (L_TCHAR L_FAR * pFile,
                                 L_UINT16 uTag,
                                 L_UINT16 L_FAR*pType,
                                 L_UINT32 L_FAR*pCount,
                                 L_VOID L_FAR*pData,
                                 pLOADFILEOPTION pLoadOptions);

L_INT32 EXT_FUNCTION L_ReadFileTagMemory (L_CHAR L_FAR * pBuffer,
                                 L_UINT16 uTag,
                                 L_UINT16 L_FAR*pType,
                                 L_UINT32 L_FAR*pCount,
                                 L_VOID L_FAR*pData,
                                 L_INT32  nBufferSize,
                                 pLOADFILEOPTION pLoadOptions);

L_INT EXT_FUNCTION L_ReadFileStamp (L_TCHAR L_FAR * pszFile,
                                    pBITMAPHANDLE pBitmap,
                                    pLOADFILEOPTION pLoadOptions);

L_INT EXT_FUNCTION L_SaveBitmap (L_TCHAR L_FAR * pszFile,
                                  pBITMAPHANDLE pBitmap,
                                  L_INT nFormat,
                                  L_INT nBitsPerPixel,
                                  L_INT nQFactor,
                                  pSAVEFILEOPTION pSaveOptions);

L_INT EXT_FUNCTION L_SaveBitmapBuffer(L_UCHAR L_FAR*pBuffer, 
                                      L_UINT32 uInitialBufferSize,
                                      L_UINT32 L_FAR *puFinalFileSize,
                                      pBITMAPHANDLE pBitmap,
                                      L_INT nFormat,
                                      L_INT nBitsPerPixel,
                                      L_INT nQFactor,
                                      SAVEBUFFERCALLBACK pfnSaveBufferCB,
                                      L_VOID L_FAR *lpUserData,
                                      pSAVEFILEOPTION pSaveOptions);


L_INT EXT_FUNCTION L_SaveBitmapList (L_TCHAR L_FAR *lpszFile,
                                  HBITMAPLIST hList,
                                  L_INT nFormat,
                                  L_INT nBits,
                                  L_INT nQFactor,
                                  pSAVEFILEOPTION pSaveOptions);

L_INT EXT_FUNCTION L_SaveBitmapMemory (HGLOBAL L_FAR * phHandle,
                                        pBITMAPHANDLE pBitmap,
                                        L_INT nFormat,
                                        L_INT nBitsPerPixel,
                                        L_INT nQFactor,
                                        L_UINT32 L_FAR * puSize,
                                        pSAVEFILEOPTION pSaveOptions);

L_INT EXT_FUNCTION L_SaveFile (L_TCHAR L_FAR * pszFile,
                                pBITMAPHANDLE pBitmap,
                                L_INT nFormat,
                                L_INT nBitsPerPixel,
                                L_INT nQFactor,
                                L_UINT uFlags,
                                FILESAVECALLBACK pfnCallback,
                                L_VOID L_FAR * pUserData,
                                pSAVEFILEOPTION pSaveOptions);

L_INT EXT_FUNCTION L_SaveFileBuffer(L_UCHAR L_FAR*pBuffer, 
                                    L_UINT32 uInitialBufferSize,
                                    L_UINT32 L_FAR *puFinalFileSize,
                                    pBITMAPHANDLE pBitmap,
                                    L_INT nFormat,
                                    L_INT nBitsPerPixel,
                                    L_INT nQFactor,
                                    L_UINT uFlags,
                                    FILESAVECALLBACK pfnFileSaveCB,
                                    SAVEBUFFERCALLBACK pfnSaveBufferCB,
                                    L_VOID L_FAR * lpUserData,
                                    pSAVEFILEOPTION pSaveOptions);

L_INT EXT_FUNCTION L_SaveFileMemory(HANDLE L_FAR *hHandle,
                                   pBITMAPHANDLE pBitmap,
                                   L_INT nFormat,
                                   L_INT nBitsPerPixel,
                                   L_INT nQFactor,
                                   L_UINT uFlags,
                                   FILESAVECALLBACK pFunction,
                                   L_VOID L_FAR * lpUserData,
                                   L_UINT32 L_FAR *uSize,
                                   pSAVEFILEOPTION pSaveOptions);

L_INT EXT_FUNCTION L_SaveFileTile (L_TCHAR L_FAR * pszFile,
                                   pBITMAPHANDLE pBitmap,
                                   L_INT nCol,
                                   L_INT nRow,
                                   FILESAVECALLBACK pfnCallback,
                                   L_VOID L_FAR * pUserData,
                                   pSAVEFILEOPTION pSaveOptions);

L_INT EXT_FUNCTION L_SaveFileOffset (L_INT fd,
                                      L_INT32 nOffsetBegin,
                                      L_INT32 L_FAR * nSizeWritten,
                                      pBITMAPHANDLE pBitmap,
                                      L_INT nFormat,
                                      L_INT nBitsPerPixel,
                                      L_INT nQFactor,
                                      L_UINT uFlags,
                                      FILESAVECALLBACK pfnCallback,
                                      L_VOID L_FAR * pUserData,
                                      pSAVEFILEOPTION pSaveOptions);

L_INT EXT_FUNCTION L_SetComment (L_UINT uType,
                                  L_UCHAR L_FAR * pComment,
                                  L_UINT uLength);

LOADINFOCALLBACK EXT_FUNCTION L_SetLoadInfoCallback (LOADINFOCALLBACK pfnCallback, 
                                                     L_VOID L_FAR*pUserData);

L_VOID L_FAR* EXT_FUNCTION L_GetLoadInfoCallbackData(L_VOID);

L_INT EXT_FUNCTION L_SetLoadResolution (L_INT nFormat,
                                  L_UINT32 nWidth,
                                  L_UINT32 nHeight);

L_INT EXT_FUNCTION L_SetTag( L_UINT16 uTag, 
                                 L_UINT16 uType,
                                 L_UINT32 uCount,
                                 L_VOID L_FAR*pData);

L_INT EXT_FUNCTION L_StartCompressBuffer (pBITMAPHANDLE pBitmap,
                                           COMPBUFFCALLBACK pfnCallback,
                                           L_UINT32 uInputBytes,
                                           L_UINT uOutputBytes,
                                           L_CHAR L_FAR * pOutputBuffer,
                                           L_INT nOutputType,
                                           L_INT nQFactor,
                                           L_VOID L_FAR * pUserData,
                                           pSAVEFILEOPTION pSaveOptions);


L_INT EXT_FUNCTION L_StartFeedLoad (pBITMAPHANDLE pBitmap,
                                     L_INT nBitsPerPixel,
                                     L_INT nOrder,
                                     L_UINT uFlags,
                                     FILEREADCALLBACK pfnCallback,
                                     L_VOID L_FAR * pUserData,
                                     HGLOBAL L_FAR * phLoad,
                                     pLOADFILEOPTION pLoadOptions,
                                     pFILEINFO pFileInfo);

L_INT EXT_FUNCTION L_StopFeedLoad (HGLOBAL hLoad);

L_INT EXT_FUNCTION L_WriteFileCommentExt (L_TCHAR L_FAR *pszFile,
                                       L_UINT uType,
                                       LPFILECOMMENTS pComments,
                                       pSAVEFILEOPTION pSaveOptions);

L_INT EXT_FUNCTION L_WriteFileStamp (L_TCHAR L_FAR * pszFile,
                                    pBITMAPHANDLE pBitmap,
                                    pSAVEFILEOPTION pSaveOptions);

L_INT EXT_FUNCTION L_SetSaveResolution (L_UINT uCount, 
                                        pDIMENSION pResolutions);

L_INT EXT_FUNCTION L_GetSaveResolution (L_UINT L_FAR*puCount, 
                                        pDIMENSION pResolutions);

L_INT EXT_FUNCTION L_GetDefaultLoadFileOption (pLOADFILEOPTION pLoadOptions, L_UINT32 uSize);

L_INT EXT_FUNCTION L_GetDefaultSaveFileOption (pSAVEFILEOPTION pSaveOptions, L_UINT32 uSize);

L_INT EXT_FUNCTION L_WriteFileTag(L_TCHAR L_FAR*pszFile,
                                  pSAVEFILEOPTION pSaveOptions);

L_INT EXT_FUNCTION L_WriteFileComment(L_TCHAR L_FAR*pszFile,
                                  pSAVEFILEOPTION pSaveOptions);

L_INT EXT_FUNCTION L_CreateThumbnailFromFile( L_TCHAR L_FAR * pszFile,
                                              pBITMAPHANDLE pBitmap,
                                              const pTHUMBOPTIONS pThumbOptions,
                                              FILEREADCALLBACK pfnCallback,
                                              L_VOID L_FAR * pUserData,
                                              pLOADFILEOPTION pLoadOptions,
                                              pFILEINFO pFileInfo );

L_INT EXT_FUNCTION L_GetJ2KOptions( pFILEJ2KOPTIONS pOptions, L_INT nSize );

L_INT EXT_FUNCTION L_GetDefaultJ2KOptions( pFILEJ2KOPTIONS pOptions, L_INT nSize );

L_INT EXT_FUNCTION L_SetJ2KOptions( const pFILEJ2KOPTIONS pOptions);

/* Lossless rotate functions and defines */
#define FILE_TRANSFORM_FLIP      0x0001
#define FILE_TRANSFORM_REVERSE   0x0002

#define FILE_TRANSFORM_ROTATE90  0x0004
#define FILE_TRANSFORM_ROTATE180 0x0008
#define FILE_TRANSFORM_ROTATE270 0x000C
#define FILE_TRANSFORM_ROTATEMASK   0x000C

typedef L_INT (pEXT_CALLBACK LEADMARKERCALLBACK) (L_UINT uMarker,
                                              L_UINT uMarkerSize,
                                              L_UCHAR L_FAR*pMarkerData,
                                              L_VOID L_FAR*pLEADUserData
                                             );

L_INT EXT_FUNCTION L_MarkerCallbackProxy(LEADMARKERCALLBACK pfnCallback,
                                         L_UINT uMarker,
                                         L_UINT uMarkerSize,
                                         L_UCHAR L_FAR*pMarkerData,
                                         L_VOID L_FAR*pLEADUserData
                                         );

typedef L_INT (pEXT_CALLBACK TRANSFORMFILECALLBACK) (L_UINT uMarker,
                                                     L_UINT uMarkerSize,
                                                     L_UCHAR L_FAR*pMarkerData,
                                                     L_VOID L_FAR*pUserData,
                                                     L_UINT uTransform,
                                                     LEADMARKERCALLBACK pfnLEADCallback,
                                                     L_VOID L_FAR*pLEADUserData
                                                     );

L_INT EXT_FUNCTION L_TransformFile (L_TCHAR L_FAR*pszFileSrc,
                                    L_TCHAR L_FAR*pszFileDst,
                                    L_UINT uTransform,
                                    TRANSFORMFILECALLBACK pfnCallback,
                                    L_VOID L_FAR*pUserData,
                                    pLOADFILEOPTION pLoadOptions);
/*
   Typedefs and defines used with extensions functions
*/
#if defined(__BORLANDC__)
        #define LTEXTENSION LTEXTENSION
#else
        #define LTEXTENSION EXTENSION
#endif
typedef struct tagEXTENSION
{
   LPWSTR      pName;      // the extension name (as Unicode)
   L_UINT32    uDataSize;  // the size of the extension data (0xFFFFFFFF if the extension is a stream)
   L_UCHAR L_FAR*pData;    // extension data. NULL for streams (if uDataSize is 0xFFFFFFFF)
   CLSID       *pClsid;    // CLSID describing the extension. Only valid if uDataSize is 0xFFFFFFFF
   L_UCHAR     ucDefault;  // internal use
} LTEXTENSION, L_FAR*pEXTENSION;

typedef struct tagEXTENSIONLIST
{
   L_UINT   uSize;         // size of the whole extension list
   L_UINT   uFlags;        // describes the type data contained in the extensions
   L_UINT   uCount;        // the number of extensions present in aList
   LTEXTENSION aList[1];   // the list of extensions
} EXTENSIONLIST, L_FAR*pEXTENSIONLIST;

/* Flags that make up EXTENSIONLIST.uFlags */
#define EXTENSION_STAMP    0x0001   // contains a stamp. Most likely suitable for LCD displays
#define EXTENSION_AUDIO    0x0002   // contains audio data

L_INT EXT_FUNCTION L_ReadFileExtensions (L_TCHAR L_FAR*pszFile,
                                          pEXTENSIONLIST L_FAR* ppExtensionList,
                                          pLOADFILEOPTION pLoadOptions);

L_INT EXT_FUNCTION L_FreeExtensions(pEXTENSIONLIST pExtensionList);

L_INT EXT_FUNCTION L_LoadExtensionStamp(pEXTENSIONLIST pExtensionList,
                                        pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_GetExtensionAudio(pEXTENSIONLIST pExtensionList,
                                       L_INT nStream,
                                       L_CHAR L_FAR* L_FAR*ppBuffer,
                                       L_UINT L_FAR*puSize);

L_INT EXT_FUNCTION L_StartDecompressBuffer(HGLOBAL *phDecompress,
                                           pSTARTDECOMPRESSDATA pStartDecompressData);

L_INT EXT_FUNCTION L_StopDecompressBuffer(HGLOBAL hDecompress);


L_INT EXT_FUNCTION L_DecompressBuffer(HGLOBAL hDecompress,
                                      pDECOMPRESSDATA pDecompressData);

/* These functions not ported to Windows CE */
#if !defined(_WIN32_WCE)
L_INT EXT_FUNCTION L_LoadBitmapResize(
                          L_TCHAR L_FAR * pszFile,        // name of the file to load 
                          pBITMAPHANDLE pSmallBitmap,    // pointer to the target bitmap handle 
                          L_INT nDestWidth,              // new width of the image 
                          L_INT nDestHeight,             // new height of the image 
                          L_INT nDestBits,               // new bits per pixel for the image 
                          L_UINT32 uFlags,               // SIZE_NORMAL, SIZE_RESAMPLE SIZE_BICUBIC	
                          L_INT nOrder,                  // color order for 16-, 24-, 32-, 48, and 64-bit bitmaps 
                          pLOADFILEOPTION pLoadOptions,  // pointer to optional extended load options 
                          pFILEINFO pFileInfo            // pointer to a structure 
                          );

L_INT EXT_FUNCTION L_ReadFileTransforms (L_TCHAR L_FAR *pszFile,
                                         pFILETRANSFORMS pTransforms,
                                         pLOADFILEOPTION pLoadOptions);

L_INT EXT_FUNCTION L_WriteFileTransforms (L_TCHAR L_FAR *pszFile,
                                          pFILETRANSFORMS pTransforms,
                                          L_INT nFlags,
                                          pSAVEFILEOPTION pSaveOptions);

L_INT EXT_FUNCTION L_GetPCDResolution (L_TCHAR L_FAR * pszFile,
                                        pPCDINFO pPCDInfo);

L_INT EXT_FUNCTION L_GetWMFResolution (L_INT L_FAR* lpResolution);
L_INT EXT_FUNCTION L_GetWMFResolutionEx (L_INT L_FAR* lpXResolution, L_INT L_FAR* lpYResolution);

L_INT EXT_FUNCTION L_SetPCDResolution (L_INT nResolution);

L_INT EXT_FUNCTION L_SetWMFResolution (L_INT nResolution);
L_INT EXT_FUNCTION L_SetWMFResolutionEx (L_INT nXResolution, L_INT nYResolution);

L_INT EXT_FUNCTION L_IgnoreFilters (L_TCHAR L_FAR*pszFilters);

L_INT EXT_FUNCTION L_PreLoadFilters (L_INT nFixedFilters, 
                                     L_INT nCachedFilters,
                                     L_TCHAR L_FAR*pszFilters);

L_INT EXT_FUNCTION L_SaveCustomFile(L_TCHAR L_FAR* pszFilename,
                                    pBITMAPHANDLE pBitmap,
                                    L_INT nFormat,
                                    L_INT nBitsPerPixel,
                                    L_INT nQFactor,
                                    L_UINT uFlags,
                                    pSAVEFILEOPTION pSaveOptions,
                                    pSAVECUSTOMFILEOPTION pSaveCustomFileOption,
                                    SAVECUSTOMFILECALLBACK pfnCallback,
                                    L_VOID L_FAR* pUserData);

L_INT EXT_FUNCTION L_LoadCustomFile (  L_TCHAR L_FAR * pszFile,
                                       pBITMAPHANDLE  pBitmap,
                                       L_INT nBitsPerPixel,
                                       L_INT nOrder,
                                       L_UINT uFlags,
                                       FILEREADCALLBACK pfnFileReadCallback,
                                       L_VOID L_FAR *  pFileReadCallbackUserData,
                                       pLOADFILEOPTION pLoadOptions,
                                       pFILEINFO pFileInfo,
                                       pLOADCUSTOMFILEOPTION   pLoadCustomFileOption,
                                       LOADCUSTOMFILECALLBACK  pfnLoadCustomFileCallback,
                                       L_VOID L_FAR*  pCustomCallbackUserData);

L_INT EXT_FUNCTION L_2DSetViewport(L_INT nWidth, 
                                   L_INT nHeight);

L_INT EXT_FUNCTION L_2DGetViewport(L_INT L_FAR*pnWidth, 
                                   L_INT L_FAR*pnHeight);

L_INT EXT_FUNCTION L_2DSetViewMode(L_INT nViewMode);

L_INT EXT_FUNCTION L_2DGetViewMode(L_VOID);

L_INT EXT_FUNCTION L_VecLoadFile(L_TCHAR L_FAR *pszFile, 
                                  pVECTORHANDLE pVector,
                                  pLOADFILEOPTION pLoadOptions,
                                  pFILEINFO pFileInfo);

L_INT EXT_FUNCTION L_VecLoadMemory (L_CHAR L_FAR * pBuffer,
                                    pVECTORHANDLE pVector,
                                    L_INT32 nBufferSize,
                                    pLOADFILEOPTION pLoadOptions,
                                    pFILEINFO pFileInfo);

L_INT EXT_FUNCTION L_VecStartFeedLoad ( pVECTORHANDLE pVector,
                                       HANDLE L_FAR *phLoad,
                                       pLOADFILEOPTION pLoadOptions,
                                       pFILEINFO pFileInfo);

L_INT EXT_FUNCTION L_VecFeedLoad(HANDLE hLoad,
                                L_UCHAR L_FAR *pInBuffer,
                                L_UINT32 dwBufferSize);

L_INT EXT_FUNCTION L_VecStopFeedLoad(HANDLE hLoad);

L_INT EXT_FUNCTION L_VecSaveFile(L_TCHAR L_FAR *pszFile, 
                                   pVECTORHANDLE pVector, 
                                   L_INT nFormat,
                                   pSAVEFILEOPTION pSaveOptions);

L_INT EXT_FUNCTION L_VecSaveMemory(HANDLE L_FAR *hHandle,
                                   pVECTORHANDLE pVector,
                                   L_INT nFormat,
                                   L_UINT32 L_FAR *uSize,
                                   pSAVEFILEOPTION pSaveOptions);

L_INT EXT_FUNCTION L_DocLoadFile(L_TCHAR L_FAR *pszFile, 
                                  pDOCHANDLE pDocument,
                                  pLOADFILEOPTION pLoadOptions);

L_INT EXT_FUNCTION L_DocLoadMemory (L_CHAR L_FAR * pBuffer,
                                    pDOCHANDLE pDocument,
                                    L_INT32 nBufferSize,
                                    pLOADFILEOPTION pLoadOptions);

L_INT EXT_FUNCTION L_DocStartFeedLoad ( pDOCHANDLE pDocument,
                                       HANDLE L_FAR *phLoad,
                                       pLOADFILEOPTION pLoadOptions);

L_INT EXT_FUNCTION L_DocFeedLoad(HANDLE hLoad,
                                L_UCHAR L_FAR *pInBuffer,
                                L_UINT32 dwBufferSize);

L_INT EXT_FUNCTION L_DocStopFeedLoad(HANDLE hLoad);

L_INT EXT_FUNCTION L_DocSaveFile(L_TCHAR L_FAR *pszFile, 
                                   pDOCHANDLE pDocument, 
                                   L_INT nFormat,
                                   pSAVEFILEOPTION pSaveOptions);

L_INT EXT_FUNCTION L_DocSaveMemory(HANDLE L_FAR *hHandle,
                                   pDOCHANDLE pDocument,
                                   L_INT nFormat,
                                   L_UINT32 L_FAR *uSize,
                                   pSAVEFILEOPTION pSaveOptions);

L_INT EXT_FUNCTION L_GetPLTOptions( pFILEPLTOPTIONS );

L_INT EXT_FUNCTION L_SetPLTOptions( const pFILEPLTOPTIONS );

L_INT EXT_FUNCTION L_GetPDFOptions( pFILEPDFOPTIONS, L_INT nSize );

L_INT EXT_FUNCTION L_SetPDFOptions( const pFILEPDFOPTIONS );

L_INT EXT_FUNCTION L_GetPDFInitDir( L_TCHAR L_FAR * pszInitDir, L_UINT uBufSize );

L_INT EXT_FUNCTION L_SetPDFInitDir( L_TCHAR L_FAR * pszInitDir );

L_INT EXT_FUNCTION L_GetRTFOptions( pFILERTFOPTIONS, L_INT nSize );

L_INT EXT_FUNCTION L_SetRTFOptions( const pFILERTFOPTIONS );

L_INT EXT_FUNCTION L_GetPTKOptions( pFILEPTKOPTIONS, L_UINT uStructSize );

L_INT EXT_FUNCTION L_SetPTKOptions( const pFILEPTKOPTIONS );

/* PSD layers functions and defines */
typedef struct _LAYERINFO
{
   L_INT32        lSize;                     /* the size of LAYERINFO - use sizeof(LAYERINFO) */
   L_INT32        nLayerLeft;
   L_INT32        nLayerTop;
   L_UCHAR        uOpacity;
   L_UCHAR        uClipping;
   L_CHAR         szBlendModeKey[4];
   pBITMAPHANDLE  pMaskBitmap;
} LAYERINFO, L_FAR * pLAYERINFO;

L_INT EXT_FUNCTION L_LoadLayer (L_TCHAR L_FAR* pszFile,
                                pBITMAPHANDLE pBitmap,
                                L_INT nBitsPerPixel,
                                L_INT nOrder,
                                L_INT nLayer,
                                pLAYERINFO pLayerInfo,
                                pLOADFILEOPTION pLoadOptions);

L_INT EXT_FUNCTION L_SaveBitmapWithLayers(L_TCHAR L_FAR* pszFile,
                                        pBITMAPHANDLE pBitmap,
                                        L_INT nFormat,
                                        L_INT nBitsPerPixel,
                                        L_INT nQFactor,
                                        HBITMAPLIST hLayers,
                                        pLAYERINFO pLayerInfo,
                                        L_INT nLayers,
                                        pSAVEFILEOPTION pSaveOptions);


#define AUTOCADFILES_COLORSCHEME_BLACKONWHITE   (0)
#define AUTOCADFILES_COLORSCHEME_WHITEONBLACK   (1)

L_INT EXT_FUNCTION L_GetAutoCADFilesColorScheme(L_UINT32 L_FAR* dwFlags);

L_INT EXT_FUNCTION L_SetAutoCADFilesColorScheme(L_UINT32 L_FAR dwFlags);

/* Vector font mapping support */ 
typedef L_INT (pEXT_CALLBACK VECTORFONTMAPPERCALLBACK)(pVECTORHANDLE pVector, LPLOGFONT pLogFont, L_VOID* pUserData);
L_INT EXT_FUNCTION L_VecAddFontMapper(VECTORFONTMAPPERCALLBACK pMapper, L_VOID* pUserData);

L_INT EXT_FUNCTION L_VecRemoveFontMapper(VECTORFONTMAPPERCALLBACK pMapper);

#endif /* _WIN32_WCE */

/* Macros and function dealing with markers start here */
#define MARKER_SOS   0xDA
#define MARKER_APP0  0xE0
#define MARKER_APP1  0xE1
#define MARKER_APP2  0xE2
#define MARKER_COM   0xFE

#define MARKER_RST0  0xD0
#define MARKER_RST7  0xD7

#define MARKER_SOI   0xD8
#define MARKER_EOI   0xD9

L_INT EXT_FUNCTION L_CreateMarkers(HANDLE L_FAR*phMarkers);

L_INT EXT_FUNCTION L_LoadMarkers(L_TCHAR L_FAR*pszFilename, 
                                 HANDLE L_FAR*phMarkers,
                                 L_UINT uFlags);

L_INT EXT_FUNCTION L_FreeMarkers(HANDLE hMarkers);

L_INT EXT_FUNCTION L_SetMarkers(HANDLE hMarkers, 
                                L_UINT uFlags);

L_INT EXT_FUNCTION L_GetMarkers(HANDLE L_FAR* phMarkers, 
                                L_UINT uFlags);

typedef L_INT (pEXT_CALLBACK ENUMMARKERSCALLBACK) (
                     L_UINT uMarker, 
                     L_UINT uMarkerSize, 
                     L_VOID L_FAR*pMarkerData, 
                     L_VOID L_FAR* pUserData, 
                     LEADMARKERCALLBACK pfnLEADCallback, 
                     L_VOID L_FAR* pLEADUserData);

L_INT EXT_FUNCTION L_EnumMarkers(HANDLE hMarkers, 
                                 L_UINT uFlags, 
                                 ENUMMARKERSCALLBACK pfnCallback, 
                                 L_VOID L_FAR*pUserData);

L_INT EXT_FUNCTION L_DeleteMarker(HANDLE hMarkers, 
                                  L_UINT uMarker, 
                                  L_INT nCount);

L_INT EXT_FUNCTION L_InsertMarker(HANDLE hMarkers, 
                                  L_UINT uIndex, 
                                  L_UINT uMarker, 
                                  L_UINT uMarkerSize, 
                                  L_UCHAR L_FAR*pMarkerData);

L_INT EXT_FUNCTION L_CopyMarkers(HANDLE L_FAR*phMarkersDst, 
                                 HANDLE hMarkersSrc);

L_INT EXT_FUNCTION L_GetMarkerCount(HANDLE hMarkers, 
                                    L_UINT L_FAR*puCount);

L_INT EXT_FUNCTION L_GetMarker(HANDLE hMarkers,
                               L_UINT uIndex,
                               L_UINT L_FAR*puMarker,
                               L_UINT L_FAR*puMarkerSize,
                               L_UCHAR L_FAR*pMarkerData);

L_INT EXT_FUNCTION L_DeleteMarkerIndex(HANDLE hMarkers, 
                                       L_UINT uIndex);

/* Macros and function dealing with markers end here */

/* Flags for L_WriteMetaData */
#define METADATA_COMMENTS     0x0001   /* Write comments */
#define METADATA_TAGS         0x0002   /* Write tags */
#define METADATA_MARKERS      0x0004   /* Write markers */
#define METADATA_ALL          0xFFFF   /* Write all metadata */

L_INT EXT_FUNCTION L_WriteFileMetaData (L_TCHAR L_FAR * pFile,
                                        L_UINT uFlags,
                                        pSAVEFILEOPTION pSaveFileOption);

#if defined(_WIN32_WCE)
   L_VOID EXT_FUNCTION L_RegisterCMP();
   L_VOID EXT_FUNCTION L_RegisterCMW();
   L_VOID EXT_FUNCTION L_RegisterBMP();
   L_VOID EXT_FUNCTION L_RegisterTIF();/* TIF requires FAX */
   L_VOID EXT_FUNCTION L_RegisterFAX();
   L_VOID EXT_FUNCTION L_RegisterGIF();
   L_VOID EXT_FUNCTION L_RegisterJ2K();
   L_VOID EXT_FUNCTION L_RegisterTGA();
   L_VOID EXT_FUNCTION L_RegisterPNG();
   L_VOID EXT_FUNCTION L_RegisterPCX();
   L_VOID EXT_FUNCTION L_RegisterXBM();
   L_VOID EXT_FUNCTION L_RegisterXPM();
#endif /* _WIN32_WCE */

#if defined(FOR_JUSTLIB)
   #ifdef __cplusplus
      #define USE_FILTER(name)                                      \
      extern "C" L_INT EXT_FUNCTION fltInfo##name(L_VOID L_FAR*ptr);\
      void USE_FILTER_##name()                                      \
      {                                                             \
         fltInfo##name(NULL);                                       \
      }
   #else
      #define USE_FILTER(name)                                      \
      extern L_INT EXT_FUNCTION fltInfo##name(L_VOID L_FAR*ptr);\
      void USE_FILTER_##name()                                      \
      {                                                             \
         fltInfo##name(NULL);                                       \
      }
   #endif
#endif /* FOR_JUSTLIB */

// the overlay callback is called to provide the overlay bitmap
typedef struct _FILEOVERLAYCALLBACKDATA
{
   L_TCHAR L_FAR* pszFilename;
   L_INT          nPageNumber;
   L_BOOL         bInfo;
   L_INT          nInfoWidth;
   L_INT          nInfoHeight;
   L_INT          nInfoXResolution;
   L_INT          nInfoYResolution;
   pBITMAPHANDLE  pLoadBitmap;
}
FILEOVERLAYCALLBACKDATA, L_FAR *pFILEOVERLAYCALLBACKDATA;

typedef L_INT (pEXT_FUNCTION OVERLAYCALLBACK) (pFILEOVERLAYCALLBACKDATA pOverlayCallbackData, L_VOID L_FAR*pUserData);

#define OVERLAY_LOADCALL   0x0001      // First try loading the overlay. call overlay callback if the load failed
#define OVERLAY_CALLLOAD   0x0002      // First call the overlay callback. Try loading the overlay file from disk
                                       // if the callback did not supply an overlay bitmap
#define OVERLAY_CALLONLY   0x0003      // Call the overlay callback. If there is no callback, there is no overlay.
#define OVERLAY_LOADONLY   0x0004      // Attempt to load the overlay bitmap from disk. If the call fails, there is no overlay.

L_INT EXT_FUNCTION L_SetOverlayCallback(OVERLAYCALLBACK pfnCallback, 
                                        L_VOID L_FAR*pUserData,
                                        L_UINT uFlags);

L_INT EXT_FUNCTION L_GetOverlayCallback(OVERLAYCALLBACK L_FAR*ppfnCallback, 
                                        L_VOID L_FAR*L_FAR*ppUserData,
                                        L_UINT L_FAR*puFlags);

#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif                          /* _LTFIL_H_ */
