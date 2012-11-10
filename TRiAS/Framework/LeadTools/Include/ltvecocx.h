#ifndef APPEARANCE_FLAT
   #define APPEARANCE_FLAT   0
   #define APPEARANCE_THREED 1
#endif

// ActiveX error codes
#include "L_OcxErr.h"

// L_SUPPORT_XXX constants
#include "ltlck_.h"

#ifndef FILE_PCX
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
#define FILE_JFIF                10 /* Jpeg File Interchange Format */
#define FILE_JTIF                11 /* Jpeg Tag Image File Format */
#define FILE_BIN                 12 /* Internal use */
#define FILE_HANDLE              13 /* Internal use */
#define FILE_OS2                 14 /* OS/2 BMP */
#define FILE_WMF                 15 /* Windows Meta File */
#define FILE_EPS                 16 /* Encapsulated Post Script */
#define FILE_TIFLZW              17 /* TIF Format with LZW compression */
#define FILE_LEAD                20 /* LEAD  Proprietary */
#define FILE_LEAD1JFIF           21 /* JPEG  4:1:1 */
#define FILE_LEAD1JTIF           22 /* JPEG  4:1:1 */
#define FILE_LEAD2JFIF           23 /* JPEG  4:2:2 */
#define FILE_LEAD2JTIF           24 /* JPEG  4:2:2 */
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
#define FILE_EXIF_JPEG           98 /* JPEG 4:2:2 compressed Exif file */
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
#define FILE_TIF_DXF             140
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
#define FILE_FAX_G3_1D_NOEOL     162  /* Raw CCITT compression--CCITT with no eol */
#define FILE_RAW_CCITT           (FILE_FAX_G3_1D_NOEOL)

#define FILE_JP2                 163   /* Jpeg2000 stream */
#define FILE_J2K                 164   /* Jpeg2000 file */
#define FILE_CMW                 165   /* Wavelet CMP */

#define FILE_TIF_J2K             166   /* TIFF Jpeg2000 stream */
#define FILE_TIF_CMW             167   /* TIFF Wavelet CMP */
#define FILE_MRC                 168   /* T44 (MRC) files */
#define FILE_GERBER              169   /* Gerber Vector */
#define FILE_WBMP                170
#define FILE_JFIF_LAB            171   /* JPEG CieLAB 4:4:4 */
#define FILE_LEAD1JFIF_LAB       172   /* JPEG CieLAB 4:1:1 */
#define FILE_LEAD2JFIF_LAB       173   /* JPEG CieLAB 4:2:2 */

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
#endif

#ifndef SCALEMODE_USER
   #define SCALEMODE_USER  0
   #define SCALEMODE_TWIP  1
   #define SCALEMODE_POINT 2
   #define SCALEMODE_PIXEL 3
   #define SCALEMODE_CHAR  4
   #define SCALEMODE_INCH  5
   #define SCALEMODE_MM    6
   #define SCALEMODE_CM    7
#endif

   typedef enum {
      VECTOR_POLYGON_POINT      = 0, // Draw only the edges points on polygons and lines.
      VECTOR_POLYGON_LINE       = 1, // Draw as wifeframe.
      VECTOR_POLYGON_FILL       = 2, // Draw solid polygons.
      VECTOR_POLYGON_FILL_RASTER_ALWAYS = 3, // Solid polygons and always draw raster objects.
   } VectorPolygonModeConstants;

   typedef enum {
      VECTOR_ENGINE_GDI         = 0,
      VECTOR_ENGINE_OPENGL      = 1,
      VECTOR_ENGINE_DIRECTX     = 2,
   } VectorEngineConstants;

   typedef enum {
      VECTOR_VIEWMODE_FIT       = 0,
      VECTOR_VIEWMODE_SNAP      = 1,
   } ViewModeConstants;

   typedef enum {
      VECTOR_ALL_OBJECTS        = 0x01,
      VECTOR_SELECTED_OBJECTS   = 0x02,
      VECTOR_CURRENT_OBJECT     = 0x04,
   } VectorObjectFlags;

   typedef enum {
      VECTOR_DLG_AUTOPROCESS    = 0x80000000,
      VECTOR_DLG_SHOWPREVIEW    = 0x40000000,
      VECTOR_DLG_SELECTED_ONLY        = 0x00000001,
      VECTOR_DLG_NO_RETURN_DUPLICATE  = 0x00000001,
   } VectorDlgFlags;

   typedef enum {
      VECTOR_BIND_VERTICES      = 0,
      VECTOR_UNBIND_VERTICES    = 1,
   } VertexBindModeConstants;

   typedef enum {
      /* Generic control strings */
      VECTOR_DLGSTRING_BUTTON_OK,
      VECTOR_DLGSTRING_BUTTON_CANCEL,
      VECTOR_DLGSTRING_BUTTON_HELP,
      VECTOR_DLGSTRING_CHECK_PREVIEW,

      /* Scale, Rotate, Translate, and Camera Dialog */
      VECTOR_DLGSTRING_TRANSFORM_SCALE_CAPTION,
      VECTOR_DLGSTRING_TRANSFORM_ROTATE_CAPTION,
      VECTOR_DLGSTRING_TRANSFORM_TRANSLATE_CAPTION,
      VECTOR_DLGSTRING_TRANSFORM_CAMERA_CAPTION,
      VECTOR_DLGSTRING_TRANSFORM_BUTTON_XUP,
      VECTOR_DLGSTRING_TRANSFORM_BUTTON_XDOWN,
      VECTOR_DLGSTRING_TRANSFORM_BUTTON_YUP,
      VECTOR_DLGSTRING_TRANSFORM_BUTTON_YDOWN,
      VECTOR_DLGSTRING_TRANSFORM_BUTTON_ZUP,
      VECTOR_DLGSTRING_TRANSFORM_BUTTON_ZDOWN,
      VECTOR_DLGSTRING_TRANSFORM_BUTTON_XUPCAMERA,
      VECTOR_DLGSTRING_TRANSFORM_BUTTON_XDOWNCAMERA,
      VECTOR_DLGSTRING_TRANSFORM_BUTTON_YUPCAMERA,
      VECTOR_DLGSTRING_TRANSFORM_BUTTON_YDOWNCAMERA,
      VECTOR_DLGSTRING_TRANSFORM_BUTTON_ZUPCAMERA,
      VECTOR_DLGSTRING_TRANSFORM_BUTTON_ZDOWNCAMERA,
      VECTOR_DLGSTRING_TRANSFORM_CHECK_ALL,
      VECTOR_DLGSTRING_TRANSFORM_CHECK_PERSPECTIVE,
      VECTOR_DLGSTRING_TRANSFORM_BUTTON_RESET,

      /* Render dialog */
      VECTOR_DLGSTRING_RENDER_CAPTION,
      VECTOR_DLGSTRING_RENDER_FRAME_LIGHTS,
      VECTOR_DLGSTRING_RENDER_CHECK_USELIGHTS,
      VECTOR_DLGSTRING_RENDER_BUTTON_AMBIENT,
      VECTOR_DLGSTRING_RENDER_FRAME_POLYGONMODE,
      VECTOR_DLGSTRING_RENDER_RADIO_POINT,
      VECTOR_DLGSTRING_RENDER_RADIO_LINE,
      VECTOR_DLGSTRING_RENDER_RADIO_FILL,

      /* View mode dialog */
      VECTOR_DLGSTRING_VIEWMODE_CAPTION,
      VECTOR_DLGSTRING_VIEWMODE_FRAME_VIEWMODE,
      VECTOR_DLGSTRING_VIEWMODE_RADIO_FIT,
      VECTOR_DLGSTRING_VIEWMODE_RADIO_SNAP,

      VECTOR_DLGSTRING_HITTEST_CAPTION,
      VECTOR_DLGSTRING_HITTEST_FRAME_DISTANCE,
      VECTOR_DLGSTRING_HITTEST_FRAME_OPTIONS,
      VECTOR_DLGSTRING_HITTEST_CHECK_CLOSEDFIGURES,
      VECTOR_DLGSTRING_HITTEST_CHECK_IGNORESELECTED,

      /* All layers dialog */
      VECTOR_DLGSTRING_ALLLAYERS_CAPTION,
      VECTOR_DLGSTRING_ALLLAYERS_BUTTON_NEW,
      VECTOR_DLGSTRING_ALLLAYERS_BUTTON_EDIT,
      VECTOR_DLGSTRING_ALLLAYERS_BUTTON_DELETE,
      VECTOR_DLGSTRING_ALLLAYERS_YES,
      VECTOR_DLGSTRING_ALLLAYERS_NO,
      VECTOR_DLGSTRING_ALLLAYERS_NAME,
      VECTOR_DLGSTRING_ALLLAYERS_ACTIVE,
      VECTOR_DLGSTRING_ALLLAYERS_VISIBLE,
      VECTOR_DLGSTRING_ALLLAYERS_LOCKED,

      /* Layer dialog */
      VECTOR_DLGSTRING_LAYER_CAPTION,
      VECTOR_DLGSTRING_LAYER_FRAME_NAME,
      VECTOR_DLGSTRING_LAYER_CHECK_ACTIVE,
      VECTOR_DLGSTRING_LAYER_CHECK_VISIBLE,
      VECTOR_DLGSTRING_LAYER_CHECK_LOCKED,

      /* General dialog */
      VECTOR_DLGSTRING_GENERAL_CAPTION,
      VECTOR_DLGSTRING_GENERAL_FRAME_SELECTION,
      VECTOR_DLGSTRING_GENERAL_CHECK_SELECTION,
      VECTOR_DLGSTRING_GENERAL_FRAME_RASTEROPERATION,

      /* ROP2 */
      VECTOR_DLGSTRING_GENERAL_ROP2_BLACKNESS,
      VECTOR_DLGSTRING_GENERAL_ROP2_NOTMERGEPEN,
      VECTOR_DLGSTRING_GENERAL_ROP2_MASKNOTPEN,
      VECTOR_DLGSTRING_GENERAL_ROP2_NOTCOPYPEN,
      VECTOR_DLGSTRING_GENERAL_ROP2_MASKPENNOT,
      VECTOR_DLGSTRING_GENERAL_ROP2_INVERT,
      VECTOR_DLGSTRING_GENERAL_ROP2_XORPEN,
      VECTOR_DLGSTRING_GENERAL_ROP2_NOTMASK,
      VECTOR_DLGSTRING_GENERAL_ROP2_MASKPEN,
      VECTOR_DLGSTRING_GENERAL_ROP2_NOTXORPEN,
      VECTOR_DLGSTRING_GENERAL_ROP2_NOP,
      VECTOR_DLGSTRING_GENERAL_ROP2_MERGENOTPEN,
      VECTOR_DLGSTRING_GENERAL_ROP2_COPYPEN,
      VECTOR_DLGSTRING_GENERAL_ROP2_MERGEPENNOT,
      VECTOR_DLGSTRING_GENERAL_ROP2_MERGEPEN,
      VECTOR_DLGSTRING_GENERAL_ROP2_WHITENESS,

      /* Pen dialog */
      VECTOR_DLGSTRING_PEN_CAPTION,
      VECTOR_DLGSTRING_PEN_FRAME_STYLE,
      VECTOR_DLGSTRING_PEN_FRAME_WIDTH,
      VECTOR_DLGSTRING_PEN_FRAME_COLOR,

      /* Pen styles */
      VECTOR_DLGSTRING_PEN_STYLE_SOLID,
      VECTOR_DLGSTRING_PEN_STYLE_DASH,
      VECTOR_DLGSTRING_PEN_STYLE_DOT,
      VECTOR_DLGSTRING_PEN_STYLE_DASHDOT,
      VECTOR_DLGSTRING_PEN_STYLE_DASHDOTDOT,
      VECTOR_DLGSTRING_PEN_STYLE_TRANSPARENT,
      VECTOR_DLGSTRING_PEN_STYLE_INSIDEFRAME,

      /* Brush dialog */
      VECTOR_DLGSTRING_BRUSH_CAPTION,
      VECTOR_DLGSTRING_BRUSH_FRAME_STYLE,
      VECTOR_DLGSTRING_BRUSH_FRAME_HATCH,
      VECTOR_DLGSTRING_BRUSH_FRAME_COLOR,

      /* Brush styles */
      VECTOR_DLGSTRING_BRUSH_STYLE_SOLID,
      VECTOR_DLGSTRING_BRUSH_STYLE_TRANSPARENT,
      VECTOR_DLGSTRING_BRUSH_STYLE_HATCHED,

      /* Brush hatched */
      VECTOR_DLGSTRING_BRUSH_HATCHED_HORIZONTAL,
      VECTOR_DLGSTRING_BRUSH_HATCHED_VERTICAL,
      VECTOR_DLGSTRING_BRUSH_HATCHED_FORWARDDIAGONAL,
      VECTOR_DLGSTRING_BRUSH_HATCHED_BACKWARDDIAGONAL,
      VECTOR_DLGSTRING_BRUSH_HATCHED_CROSS,
      VECTOR_DLGSTRING_BRUSH_HATCHED_DIAGONALCROSS,

      /* Vertex dialog */
      VECTOR_DLGSTRING_VERTEX_CAPTION,
      VECTOR_DLGSTRING_VERTEX_FRAME_LOCATION,

      /* Line dialog */
      VECTOR_DLGSTRING_LINE_CAPTION,
      VECTOR_DLGSTRING_LINE_FRAME_STARTPOINT,
      VECTOR_DLGSTRING_LINE_FRAME_ENDPOINT,

      /* Rectangle dialog */
      VECTOR_DLGSTRING_RECTANGLE_CAPTION,
      VECTOR_DLGSTRING_RECTANGLE_FRAME_STARTPOINT,
      VECTOR_DLGSTRING_RECTANGLE_FRAME_ENDPOINT,

      /* Poly Line dialog */
      VECTOR_DLGSTRING_POLYLINE_CAPTION,
      VECTOR_DLGSTRING_POLYLINE_FRAME_POINTS,
      VECTOR_DLGSTRING_POLYLINE_BUTTON_NEW,
      VECTOR_DLGSTRING_POLYLINE_BUTTON_DELETE,

      /* Poly Bezier dialog */
      VECTOR_DLGSTRING_POLYBEZIER_CAPTION,
      VECTOR_DLGSTRING_POLYBEZIER_FRAME_POINTS,
      VECTOR_DLGSTRING_POLYBEZIER_BUTTON_NEW,
      VECTOR_DLGSTRING_POLYBEZIER_BUTTON_DELETE,

      /* Polygon dialog */
      VECTOR_DLGSTRING_POLYGON_CAPTION,
      VECTOR_DLGSTRING_POLYGON_FRAME_POINTS,
      VECTOR_DLGSTRING_POLYGON_BUTTON_NEW,
      VECTOR_DLGSTRING_POLYGON_BUTTON_DELETE,
      VECTOR_DLGSTRING_POLYGON_FRAME_FILLMODE,
      VECTOR_DLGSTRING_POLYGON_RADIO_ALTERNATE,
      VECTOR_DLGSTRING_POLYGON_RADIO_WINDING,

      /* Ellipse dialog */
      VECTOR_DLGSTRING_ELLIPSE_CAPTION,
      VECTOR_DLGSTRING_ELLIPSE_FRAME_CENTER,
      VECTOR_DLGSTRING_ELLIPSE_FRAME_RADIUS,

      /* Circle dialog */
      VECTOR_DLGSTRING_CIRCLE_CAPTION,
      VECTOR_DLGSTRING_CIRCLE_FRAME_CENTER,
      VECTOR_DLGSTRING_CIRCLE_FRAME_RADIUS,

      /* Arc dialog */
      VECTOR_DLGSTRING_ARC_CAPTION,
      VECTOR_DLGSTRING_ARC_FRAME_CENTER,
      VECTOR_DLGSTRING_ARC_FRAME_RADIUS,
      VECTOR_DLGSTRING_ARC_FRAME_ANGLES,
      VECTOR_DLGSTRING_ARC_STATIC_START,
      VECTOR_DLGSTRING_ARC_STATIC_SWEEP,

      /* Text dialog */
      VECTOR_DLGSTRING_TEXT_CAPTION,
      VECTOR_DLGSTRING_TEXT_FRAME_POINT,
      VECTOR_DLGSTRING_TEXT_FRAME_HORIZONTAL,
      VECTOR_DLGSTRING_TEXT_FRAME_VERTICAL,
      VECTOR_DLGSTRING_TEXT_CHECK_HITTESTRECTANGLE,
      VECTOR_DLGSTRING_TEXT_FRAME_TEXT,
      VECTOR_DLGSTRING_TEXT_FRAME_FONT,
      VECTOR_DLGSTRING_TEXT_BUTTON_FONT,
      VECTOR_DLGSTRING_TEXT_STATIC_CHARWIDTH,
      VECTOR_DLGSTRING_TEXT_STATIC_CHARHEIGHT,

      /* Text alignment combo */
      VECTOR_DLGSTRING_TEXT_LEFT,
      VECTOR_DLGSTRING_TEXT_RIGHT,
      VECTOR_DLGSTRING_TEXT_HCENTER,
      VECTOR_DLGSTRING_TEXT_TOP,
      VECTOR_DLGSTRING_TEXT_BOTTOM,
      VECTOR_DLGSTRING_TEXT_VCENTER,

      /* Pie dialog */
      VECTOR_DLGSTRING_PIE_CAPTION,
      VECTOR_DLGSTRING_CHORD_CAPTION,
      VECTOR_DLGSTRING_PIE_FRAME_CENTER,
      VECTOR_DLGSTRING_PIE_FRAME_RADIUS,
      VECTOR_DLGSTRING_PIE_FRAME_ANGLES,
      VECTOR_DLGSTRING_PIE_STATIC_START,
      VECTOR_DLGSTRING_PIE_STATIC_SWEEP,

      /* Poly Draw dialog */
      VECTOR_DLGSTRING_POLYDRAW_CAPTION,
      VECTOR_DLGSTRING_POLYDRAW_FRAME_POINTS,
      VECTOR_DLGSTRING_POLYDRAW_BUTTON_NEW,
      VECTOR_DLGSTRING_POLYDRAW_BUTTON_DELETE,
      VECTOR_DLGSTRING_POLYDRAW_FRAME_TYPE,
      VECTOR_DLGSTRING_POLYDRAW_CHECK_CLOSEFIGURE,

      /* Poly Draw types */
      VECTOR_DLGSTRING_POLYDRAW_MOVETO,
      VECTOR_DLGSTRING_POLYDRAW_LINETO,
      VECTOR_DLGSTRING_POLYDRAW_BEZIERTO,

      /* Raster dialog */
      VECTOR_DLGSTRING_RASTER_CAPTION,
      VECTOR_DLGSTRING_RASTER_FRAME_POINT1,
      VECTOR_DLGSTRING_RASTER_FRAME_POINT2,
      VECTOR_DLGSTRING_RASTER_FRAME_BITMAP,

      /* Messages */
      VECTOR_DLGSTRING_VECTOR_IS_LOCKED,
      VECTOR_DLGSTRING_VECTOR_NOT_ENABLED,
      VECTOR_DLGSTRING_LAYER_NOT_FOUND,
      VECTOR_DLGSTRING_LAYER_ALREADY_EXISTS,
      VECTOR_DLGSTRING_NO_MEMORY,
      VECTOR_DLGSTRING_DELETELAYERQUERY,
      VECTOR_DLGSTRING_CANNOTFINISHOPERATION,
      VECTOR_DLGSTRING_CANNOTLOADBITMAP,
   } VectorDlgStringConstants;

   typedef enum
   {
      VECTOR_READYSTATE_UNINITIALIZED   = 0,
      VECTOR_READYSTATE_LOADING         = 1,
      VECTOR_READYSTATE_LOADED          = 2,
      VECTOR_READYSTATE_INTERACTIVE     = 3,
      VECTOR_READYSTATE_COMPLETE        = 4,
   }VectorReadyStateConstants;

   typedef enum
   {
      VECTOR_FLAGS_SELECTED_ONLY  = 1,
      VECTOR_FLAGS_REPLACE        = 2,
      VECTOR_FLAGS_RENAME_DUPLICATES       = 4,
      VECTOR_FLAGS_COPY_INTO_ACTIVE_LAYER  = 64,
      VECTOR_FLAGS_COPY_LAYERS_ONLY        = 128,
      VECTOR_FLAGS_ADD_UNDO_NODE           = 256,
   } VectorFlags;

   typedef enum
   {
      MARKER_PS_SOLID           = 0,
      MARKER_PS_DASH            = 1,
      MARKER_PS_DOT             = 2,
      MARKER_PS_DASHDOT         = 3,
      MARKER_PS_DASHDOTDOT      = 4,
      MARKER_PS_NULL            = 5,
      MARKER_PS_INSIDEFRAME     = 6,
   } MarkerPenStyles;

   typedef enum
   {
      MARKER_BS_SOLID           = 0,
      MARKER_BS_NULL            = 1,
      MARKER_BS_HOLLOW          = 1,
      MARKER_BS_HATCHED         = 2,
      MARKER_BS_PATTERN         = 3,
   } MarkerBrushStyles;

   typedef enum
   {
      MARKER_HS_BDIAGONAL       = 1,
      MARKER_HS_CROSS           = 2,
      MARKER_HS_DIAGCROSS       = 3, 
      MARKER_HS_FDIAGONAL       = 4,
      MARKER_HS_HORIZONTAL      = 5,
      MARKER_HS_VERTICAL        = 6,
   } MarkerBrushHatchStyles;

   typedef enum
   {
      VECTOR_HITTEST_CLOSEDFIGURES  = 1,
      VECTOR_HITTEST_IGNORESELECTED = 2,
   } HitTestOptions;

   typedef enum
   {
      VECTOR_POLY_WINDING		 = 0,
      VECTOR_POLY_ALTERNATE	 = 1,
   } VectorPolygonFillModes;

   typedef enum
   {
      VECTOR_TEXT_LEFT          = 0,
      VECTOR_TEXT_RIGHT         = 1,
      VECTOR_TEXT_HCENTER       = 2,
      VECTOR_TEXT_TOP           = 0,
      VECTOR_TEXT_BOTTOM        = 4,
      VECTOR_TEXT_VCENTER       = 8,
      VECTOR_TEXT_HITTESTRECT   = 16,
   } VectorTextFlags;

   typedef enum
   {
      VECTOR_PS_SOLID           = 0,
      VECTOR_PS_DASH            = 1,
      VECTOR_PS_DOT             = 2,
      VECTOR_PS_DASHDOT         = 3,
      VECTOR_PS_DASHDOTDOT      = 4,
      VECTOR_PS_NULL            = 5,
      VECTOR_PS_INSIDEFRAME     = 6,
   } VectorPenStyles;

   typedef enum
   {
      VECTOR_BS_SOLID           = 0,
      VECTOR_BS_NULL            = 1,
      VECTOR_BS_HOLLOW          = 1,
      VECTOR_BS_HATCHED         = 2,
   } VectorBrushStyles;

   typedef enum
   {
      VECTOR_HS_HORIZONTAL      = 0,
      VECTOR_HS_VERTICAL        = 1,
      VECTOR_HS_FDIAGONAL       = 2,
      VECTOR_HS_BDIAGONAL       = 3,
      VECTOR_HS_CROSS           = 4,
      VECTOR_HS_DIAGCROSS       = 5,
   } VectorBrushHatchStyles;

   typedef enum
   {
      VECTOR_PT_CLOSEFIGURE   =   0x01,
      VECTOR_PT_LINETO        =   0x02,
      VECTOR_PT_BEZIERTO      =   0x04,
      VECTOR_PT_MOVETO        =   0x06,
   } VectorPointType;

   typedef enum
   {
      VECTOR_OBJECT             = 0,
      VECTOR_VERTEX             = 1,         // 3D vertex in space.
      VECTOR_LINE               = 2,         // Line.
      VECTOR_RECTANGLE          = 3,         // Rectnagle.
      VECTOR_POLYLINE           = 4,         // Polyline.
      VECTOR_POLYBEZIER         = 5,         // Poly Bezier curve
      VECTOR_POLYGON            = 6,         // Multi-sided polygon.
      VECTOR_ELLIPSE            = 7,         // Ellipse.
      VECTOR_CIRCLE             = 8,         // Circle.
      VECTOR_ARC                = 9,         // Arc.
      VECTOR_ELLIPTICALARC      = 10,        // Elliptical arc.
      VECTOR_TEXT               = 11,        // Text.
      VECTOR_PIE                = 12,        // Pie.
      VECTOR_CHORD              = 13,        // Chord.
      VECTOR_POLYDRAW           = 14,        // Polydraw.
      VECTOR_RASTER             = 15,        // Raster.
      VECTOR_STOCK              = 16,        // Stock object from a library.
      VECTOR_CLONE              = 17,        // Clone.
   } VectorObjectType;

   typedef enum
   {
      VECTOR_R2_BLACK       = 1,
      VECTOR_R2_NOTMERGEPEN = 2,
      VECTOR_R2_MASKNOTPEN  = 3,
      VECTOR_R2_NOTCOPYPEN  = 4,
      VECTOR_R2_MASKPENNOT  = 5,
      VECTOR_R2_NOT         = 6,
      VECTOR_R2_XORPEN      = 7,
      VECTOR_R2_NOTMASKPEN  = 8,
      VECTOR_R2_MASKPEN     = 9,
      VECTOR_R2_NOTXORPEN   = 10,
      VECTOR_R2_NOP         = 11,
      VECTOR_R2_MERGENOTPEN = 12,
      VECTOR_R2_COPYPEN     = 13,
      VECTOR_R2_MERGEPENNOT = 14,
      VECTOR_R2_MERGEPEN    = 15,
      VECTOR_R2_WHITE       = 16,
   } VectorROPCode;

   typedef enum
   {
      VECTOR_RESET_ROTATE        = 0x00000001,
      VECTOR_RESET_SCALE         = 0x00000002,
      VECTOR_RESET_TRANSLATE     = 0x00000004,
      VECTOR_RESET_CAMERA        = 0x00000008,
      VECTOR_RESET_PARALLELOGRAM = 0x00000010,
      VECTOR_RESET_ORIGIN        = 0x00000020,
      VECTOR_RESET_PAN           = 0x00000040,
      VECTOR_RESET_ALL           = 0x0000007F,
   } VectorResetFlags;

   typedef enum
   {
      VECTOR_USERMODE_MANUAL = 0,
      VECTOR_USERMODE_AUTO = 1,
   } VectorUserModeConstants;

   typedef enum
   {
      VECTOR_AUTOMATION_SELTYPE_NONE,
      VECTOR_AUTOMATION_SELTYPE_ALL,
   } VectorAutomationSelType;

   typedef enum
   {
      VECTOR_CONTAINER_OBJECT_TYPE_NONE,
      VECTOR_CONTAINER_OBJECT_TYPE_POINT,
      VECTOR_CONTAINER_OBJECT_TYPE_LINE,
      VECTOR_CONTAINER_OBJECT_TYPE_SQUARE,
      VECTOR_CONTAINER_OBJECT_TYPE_RECT,
      VECTOR_CONTAINER_OBJECT_TYPE_CIRCLE,
      VECTOR_CONTAINER_OBJECT_TYPE_ELLIPSE,
      VECTOR_CONTAINER_OBJECT_TYPE_POLYLINE,
      VECTOR_CONTAINER_OBJECT_TYPE_BEZIER,
      VECTOR_CONTAINER_OBJECT_TYPE_ARC,
      VECTOR_CONTAINER_OBJECT_TYPE_TEXT,
      VECTOR_CONTAINER_OBJECT_TYPE_COUNT = 11
   } VectorContainerObjectType;

   typedef enum
   {
      VECTOR_CONTAINER_EVENT_DRAW,
      VECTOR_CONTAINER_EVENT_MSG,
      VECTOR_CONTAINER_EVENT_ERROR
   } VectorContainerEventType;

   typedef enum
   {
      VECTOR_CONTAINER_STATE_BEGIN,
      VECTOR_CONTAINER_STATE_PROCESS,
      VECTOR_CONTAINER_STATE_END,
      VECTOR_CONTAINER_STATE_ABORT
   } VectorContainerState;

   typedef enum
   {
      VECTOREVENT_USER = 0,
      VECTOREVENT_RESERVED = 10000,

      VECTOREVENT_FREE,
      VECTOREVENT_EMPTY,
      VECTOREVENT_COPY,
      VECTOREVENT_VIEWPORT,
      VECTOREVENT_PAN,
      VECTOREVENT_LOCKED,
      VECTOREVENT_BACKGROUND,
      VECTOREVENT_PALETTE,
      VECTOREVENT_VIEWMODE,

      VECTOREVENT_TRANSLATION,
      VECTOREVENT_ROTATION,
      VECTOREVENT_SCALE,
      VECTOREVENT_ORIGIN,
      VECTOREVENT_APPLYTRANSFORMATION,
      VECTOREVENT_ZOOMRECT,

      VECTOREVENT_BINDVERTICESMODE,
      VECTOREVENT_PARALLELOGRAM,

      VECTOREVENT_CAMERA,

      VECTOREVENT_METAFILE,

      VECTOREVENT_ATTACHTOWINDOW,

      VECTOREVENT_MARKER,

      VECTOREVENT_UNIT,         /* Reserved for internal use */

      VECTOREVENT_HITTEST,

      VECTOREVENT_POLYGONMODE,
      VECTOREVENT_USELIGHTS,
      VECTOREVENT_AMBIENTCOLOR,

      VECTOREVENT_COPYFROMCLIPBOARD,

      VECTOREVENT_ADDLAYER,
      VECTOREVENT_DELETELAYER,
      VECTOREVENT_EMPTYLAYER,
      VECTOREVENT_COPYLAYER,
      VECTOREVENT_SETLAYER,
      VECTOREVENT_SETACTIVELAYER,

      VECTOREVENT_ADDGROUP,
      VECTOREVENT_DELETEGROUP,
      VECTOREVENT_DELETEGROUPCLONES,
      VECTOREVENT_EMPTYGROUP,
      VECTOREVENT_COPYGROUP,
      VECTOREVENT_SETGROUP,

      VECTOREVENT_ADDOBJECT,
      VECTOREVENT_DELETEOBJECT,
      VECTOREVENT_COPYOBJECT,
      VECTOREVENT_SETOBJECT,
      VECTOREVENT_EXPLODEOBJECT,
      VECTOREVENT_SELECTOBJECT,
      VECTOREVENT_HIDEOBJECT,
      VECTOREVENT_OBJECTATTRIBUTES,
      VECTOREVENT_ADDOBJECTTOGROUP,

      VECTOREVENT_DUMPLOADVECTOR,

      VECTOREVENT_LOADFILE
   } VectorEventConstants;

   typedef enum
   {
      VECTOREVENT_STATUS_BEFORE,
      VECTOREVENT_STATUS_AFTER
   } VectorEventStatusConstants;

   typedef enum tagVectorCloneFlags
   {
      VECTOR_CLONE_USE_PEN    = 1,
      VECTOR_CLONE_USE_BRUSH  = 2,
      VECTOR_CLONE_USE_POINT_AS_ORIGIN = 4,
   } VectorCloneFlags;
