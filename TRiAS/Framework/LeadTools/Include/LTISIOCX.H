   typedef enum {
           ISIS_SHOWUI =  0x0001,
           ISIS_MULTI_NOSAVE =  0x0002,
   }ISISFlagsConstants;

   typedef enum {
            TAG_XRESOLUTION =                0x011A,
            TAG_YRESOLUTION =                0x011B,
            TAG_XPOSITION   =                0x011E,
            TAG_YPOSITION   =                0x011F,
            TAG_IMAGELENGTH =                0x0101,
            TAG_IMAGEWIDTH  =                0x0100,

            TAG_FEEDER      =                0x0503,
                TAG_FEEDER_FEED       =          0x00000001L,
                TAG_FEEDER_FLAT       =          0x00000002L,
                TAG_FEEDER_MANUAL     =          0x00000004L,
                TAG_FEEDER_TELLFEED   =          0x00010000L,
                TAG_FEEDER_TELLFLAT   =          0x00020000L,
                TAG_FEEDER_TELLSCAN   =          0x00040000L,
                TAG_FEEDER_CENTERFEED =          0x00080000L,
                TAG_FEEDER_CENTERFLAT =          0x00100000L,
                TAG_FEEDER_PAUSE      =          0x00200000L,

            TAG_SAMPLESPERPIXEL       =      0x0115,

            TAG_BITSPERSAMPLE         =      0x0102,

            TAG_CONTRAST              =      0x0501,
                TAG_CONTRAST_AUTO     =          0x0000,

            TAG_BRIGHTNESS             =     0x0502,
                TAG_BRIGHTNESS_AUTO    =         0xFFFFFFFD,
                TAG_BRIGHTNESS_DARKEN  =         0xFFFFFFFE,
                TAG_BRIGHTNESS_NORM    =         0xFFFFFFFF,
                TAG_BRIGHTNESS_LIGHTEN =         0x00000000,

            TAG_COMPRESSION            =     0x0103,
                TAG_COMPRESSION_NONE   =         0x0001,   /* no compression        */
                TAG_COMPRESSION_MG3    =         0x0002,   /* CCITT compression     */
                TAG_COMPRESSION_G3     =         0x0003,   /* CCITT G3 1-DIM        */
                TAG_COMPRESSION_G4     =         0x0004,   /* CCITT G4              */
                TAG_COMPRESSION_LZW    =         0x0005,   /* LZW compression       */
                TAG_COMPRESSION_JPEG   =         0x0006,   /* not supported by LEAD */
                TAG_COMPRESSION_PACK   =         0x8005,   /* not supported by LEAD */
                TAG_COMPRESSION_32771  =         0x8003,   /* packbits compression  */
                TAG_COMPRESSION_JBIG   =         0x8765,   /* not supported by LEAD */
                TAG_COMPRESSION_PCX    =         0xC350,   /* not supported by LEAD */
                TAG_COMPRESSION_4BYTE  =         0xC351,   /* not supported by LEAD */
                TAG_COMPRESSION_GIF    =         0xC355,   /* not supported by LEAD */
                TAG_COMPRESSION_BMP    =         0xC356,   /* not supported by LEAD */

            TAG_PLANARCONFIGURATION    =     0x011c,
                TAG_PLANARCONFIG_LINE  =         0x0001,
                TAG_PLANARCONFIG_LINE_PACK =     0x0001,
                TAG_PLANARCONFIG_PAGE  =         0x0002,
                TAG_PLANARCONFIG_LINE_UNPACK =   0x1388,

            TAG_SCANORIENTATION           =  0x0113,
                TAG_SCANORIENTATION_PORT  =  0x0001,  /*   0 degrees -- portait mode     */
                TAG_SCANORIENTATION_LAND  =  0x0002,  /*  90 degrees -- landscape mode   */
                TAG_SCANORIENTATION_180   =  0x0003,  /* 180 degrees                     */
                TAG_SCANORIENTATION_270   =  0x0004,  /* 270 degrees                     */
                TAG_SCANORIENTATION_PORTM =  0x0005,  /*   0 degrees -- flipped horizontally */
                TAG_SCANORIENTATION_LANDM =  0x0006,  /*  90 degrees -- flipped horizontally */
                TAG_SCANORIENTATION_180M  =  0x0007,  /* 180 degrees -- flipped horizontally */
                TAG_SCANORIENTATION_270M  =  0x0008,  /* 270 degrees -- flipped horizontally */

            TAG_MAXPAGES                  =  0x0504,

            TAG_SCANAHEAD                 =  0x050d,
                TAG_SCANAHEAD_NO          =      0x0000,
                TAG_SCANAHEAD_YES         =      0x0001,

            TAG_GAMMA                     =  0x050f,
                TAG_GAMMA_NORMAL          =      0x0000,
                TAG_GAMMA_AUTO            =      0x0000,
                TAG_GAMMA_DOWNLOAD1       =      0x0001,
                TAG_GAMMA_DOWNLOAD2       =      0x0002,
                TAG_GAMMA_DOWNLOAD3       =      0x0003,
                TAG_GAMMA_DOWNLOAD4       =      0x0004,
                TAG_GAMMA_DOWNLOAD5       =      0x0005,
                TAG_GAMMA_DOWNLOAD6       =      0x0006,
                TAG_GAMMA_CRT             =      0x0007,
                TAG_GAMMA_BOTTOMCLIP      =      0xFFFFFFFD,
                TAG_GAMMA_1TO1INVERT      =      0xFFFFFFFE,
                TAG_GAMMA_SCURVE          =      0xFFFFFFFF,
                TAG_GAMMA_SHARP_61        =      0x0001,
                TAG_GAMMA_SHARP_67        =      0x0002,
                TAG_GAMMA_SHARP_75        =      0x0003,
                TAG_GAMMA_SHARP_87        =      0x0004,
                TAG_GAMMA_1TO1            =      0x0005,
                TAG_GAMMA_BLUR_1_20       =      0x0006,
                TAG_GAMMA_BLUR_1_45       =      0x0007,
                TAG_GAMMA_BLUR_1_78       =      0x0008,
                TAG_GAMMA_BLUR_2_20       =      0x0009,

                TAG_SCANAHEAD_MAXPAGES  = 0x057c,
                TAG_SCANTYPE            = 0x0514,
                TAG_SCANTYPE_AUTOMATIC    =      0x0000,
                TAG_SCANTYPE_TRANSPARENCY =      0x0001,
                TAG_SCANTYPE_FLATBED      =      0x0002,
                TAG_SCANTYPE_FEEDER       =      0x0003,
                TAG_SCANTYPE_FRONTONLY    =      0x0003,
                TAG_SCANTYPE_DUPLEX       =      0x0004,
                TAG_SCANTYPE_FRONTBACK    =      0x0004,
                TAG_SCANTYPE_BACKFRONT    =      0x0005,
                TAG_SCANTYPE_BACKONLY     =      0x0006,

            TAG_PHOTOMETRICINTERPRETATION =  0x0106,
                TAG_PHOTOMETRIC_WHITE0    =      0x0000,
                TAG_PHOTOMETRIC_WHITE1    =      0x0001,
                TAG_PHOTOMETRIC_RGB       =      0x0002,
                TAG_PHOTOMETRIC_PALETTE   =      0x0003,
                TAG_PHOTOMETRIC_BGR       =      0x0120,

            TAG_PAGESIZE                  =  0x050e,
                
            ISIS_DEFAULT = -99,

   }ISISTagConstants;

// L_SUPPORT_XXX constants
#include "ltlck_.h"

   // ActiveX error codes
#include "L_OcxErr.h"
