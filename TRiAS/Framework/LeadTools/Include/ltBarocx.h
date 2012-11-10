   typedef enum {
      BARCODE_NORMAL       = 1,
      BARCODE_ERRORCHECK   = 2,
   } BARCODE_STATUS;

   typedef enum {
      BARCODE_USECOLORS   = 0x0200,
      BARCODE_TRANSPARENT = 0x0400,
   } BARCODE_COLOR_FLAGS;

   typedef enum {
      BARCODE_MARKERS      = 0x0001,
      BARCODE_BLOCK_SEARCH = 0x0002,
      BARCODE_RETURNCHECK  = 0x1000,
   } BARCODE_RWFLAGS_1D;

   typedef enum
   {
      BARCODE_JUSTIFYRIGHT   = 0x0010,
      BARCODE_JUSTIFYHCENTER = 0x0020,
   } BARCODE_WFALGS_1D;

   typedef enum {
      BARCODE_TRUNCATE            = 0x0010,
      BARCODE_MSGAPPEND           = 0x0020,
      BARCODE_INITREADER          = 0x0040,
      BARCODE_COLROWASLIMITS      = 0x0080,
      BARCODE_DISABLE_COMPRESSOPN = 0x0100,
   } BARCODE_WFLAGS_CODEONE_PDF;

   typedef enum {
      BARCODE_SCANLINES_PER_PIXELS = 0,
      BARCODE_INCHES               = 1,
      BARCODE_MILLIMETERS          = 2,
   } BARCODE_UNITS;

   typedef enum {
      BARCODE_DIR_LEFT_TO_RIGHT  = 0x001,
      BARCODE_DIR_RIGHT_TO_LEFT  = 0x002,
      BARCODE_DIR_TOP_TO_BOTTOM  = 0x004,
      BARCODE_DIR_BOTTOM_TO_TOP  = 0x008,

      BARCODE_DIR_SKEW           = 0x010,
      BARCODE_DIR_HORIZONTAL     = 0x020,
      BARCODE_DIR_VERTICAL       = 0x040,
      BARCODE_DIR_DIAGONAL       = 0x080,
   } BARCODE_DIRECTION;

   typedef enum {
      BARCODE_JUSTIFY_RIGHT      = 0x1000,
      BARCODE_JUSTIFY_H_CENTER   = 0x2000,
      BARCODE_JUSTIFY_BOTTOM     = 0x4000,
      BARCODE_JUSTIFY_V_CENTER   = 0x8000,
   } BARCODE_JUSTIFICATION;

   typedef enum {
      BARCODE_PDF417_ECCLEVEL_0     = 0x0001,
      BARCODE_PDF417_ECCLEVEL_1     = 0x0002,
      BARCODE_PDF417_ECCLEVEL_2     = 0x0004,
      BARCODE_PDF417_ECCLEVEL_3     = 0x0008,
      BARCODE_PDF417_ECCLEVEL_4     = 0x0010,
      BARCODE_PDF417_ECCLEVEL_5     = 0x0020,
      BARCODE_PDF417_ECCLEVEL_6     = 0x0040,
      BARCODE_PDF417_ECCLEVEL_7     = 0x0080,
      BARCODE_PDF417_ECCLEVEL_8     = 0x0100,
      BARCODE_PDF417_ECCUSE_PERCENT = 0x0FFF,
   } BARCODE_PDF417_ECCLEVEL;

   typedef enum {
      BARCODE_1D_EAN_13          = 0x00000001,
      BARCODE_1D_EAN_8           = 0x00000002,
      BARCODE_1D_UPC_A           = 0x00000004,
      BARCODE_1D_UPC_E           = 0x00000008,
      BARCODE_1D_CODE_3_OF_9     = 0x00000010,
      BARCODE_1D_CODE_128        = 0x00000020,
      BARCODE_1D_CODE_I2_OF_5    = 0x00000040,
      BARCODE_1D_CODA_BAR        = 0x00000080,
      BARCODE_1D_UCCEAN_128      = 0x00000100,
      BARCODE_1D_READ_ANYTYPE    = 0x00000FF0,
   } BARCODE_1D_TYPES;

   typedef enum {
      BARCODE_R_CODEONE_A_TO_H   = 0x00000200,
      BARCODE_R_CODEONE_T        = 0x00000400,
      BARCODE_R_CODEONE_S        = 0x00000800,
      BARCODE_R_CODEONE_ANYTYPE  = 0x00001000,
   } BARCODE_CODEONE_READ_TYPES;

   typedef enum {
      BARCODE_PDF417             = 0x00002000,
   } BARCODE_PDF_TYPES;

   typedef enum {
      BARCODE_CODEONE_DEF        = 0x00004000,
      BARCODE_CODEONE_TDEF       = 0x00008000,
      BARCODE_CODEONE_SDEF       = 0x00010000,
      BARCODE_CODEONE_A          = 0x00020000,
      BARCODE_CODEONE_B          = 0x00040000,
      BARCODE_CODEONE_C          = 0x00080000,
      BARCODE_CODEONE_D          = 0x00100000,
      BARCODE_CODEONE_E          = 0x00200000,
      BARCODE_CODEONE_F          = 0x00400000,
      BARCODE_CODEONE_G          = 0x00800000,
      BARCODE_CODEONE_H          = 0x01000000,
      BARCODE_CODEONE_T16        = 0x02000000,
      BARCODE_CODEONE_T32        = 0x04000000,
      BARCODE_CODEONE_T48        = 0x08000000,
      BARCODE_CODEONE_S10        = 0x10000000,
      BARCODE_CODEONE_S20        = 0x20000000,
      BARCODE_CODEONE_S30        = 0x40000000,
   } BARCODE_CODEONE_WRITE_TYPES;

   typedef enum
   {
      BARCODE_RETURNCORRUPT               = 0x080,

      BARCODE_PDF_READ_MODE_0             = 0x0000,
      BARCODE_PDF_READ_MODE_1             = 0x1000,
      BARCODE_PDF_READ_MODE_2             = 0x2000,
      BARCODE_PDF_READ_MODE_3_BASIC       = 0x3000,
      BARCODE_PDF_READ_MODE_3_EXTENDED    = 0x7000,

      BARCODE_PDF_READ_MACRO_OPTION_0     = 0x00010000,
      BARCODE_PDF_READ_MACRO_OPTION_1     = 0x00020000,
      BARCODE_PDF_READ_MACRO_OPTION_2     = 0x00040000,
      BARCODE_PDF_READ_MACRO_OPTION_3     = 0x00080000,
      BARCODE_PDF_READ_MACRO_OPTION_4     = 0x00100000,
      BARCODE_PDF_READ_MACRO_OPTION_5     = 0x00200000,
      BARCODE_PDF_READ_MACRO_OPTION_6     = 0x00400000,
      BARCODE_PDF_READ_MACRO_OPTION_79AZ  = 0x00800000,
   } BARCODE_RFALGS_PDF;

   typedef enum
   {
      BARCODE_DM_DEF             = 0x00000101, /* Use Default DataMatrix Size */
      BARCODE_DM_10x10           = 0x00000102,
      BARCODE_DM_12x12           = 0x00000103,
      BARCODE_DM_14x14           = 0x00000104,
      BARCODE_DM_16x16           = 0x00000105,
      BARCODE_DM_18x18           = 0x00000106,
      BARCODE_DM_20x20           = 0x00000107,
      BARCODE_DM_22x22           = 0x00000108,
      BARCODE_DM_24x24           = 0x00000109,
      BARCODE_DM_26x26           = 0x0000010A,
      BARCODE_DM_32x32           = 0x0000010B,
      BARCODE_DM_36x36           = 0x0000010C,
      BARCODE_DM_40x40           = 0x0000010D,
      BARCODE_DM_44x44           = 0x0000010E,
      BARCODE_DM_48x48           = 0x0000010F,
      BARCODE_DM_52x52           = 0x00000110,
      BARCODE_DM_64x64           = 0x00000111,
      BARCODE_DM_72x72           = 0x00000112,
      BARCODE_DM_80x80           = 0x00000113,
      BARCODE_DM_88x88           = 0x00000114,
      BARCODE_DM_96x96           = 0x00000115,
      BARCODE_DM_104x104         = 0x00000116,
      BARCODE_DM_120x120         = 0x00000117,
      BARCODE_DM_132x132         = 0x00000118,
      BARCODE_DM_144x144         = 0x00000119,
      BARCODE_DM_8x18            = 0x0000011A,
      BARCODE_DM_8x32            = 0x0000011B,
      BARCODE_DM_12x26           = 0x0000011C,
      BARCODE_DM_12x36           = 0x0000011D,
      BARCODE_DM_16x36           = 0x0000011E,
      BARCODE_DM_16x48           = 0x0000011F,
      BARCODE_DM_WRITE_RECTANGLE = 0x00000180, /* Write Rectangular Default Symbol */
   } BARCODE_WFALGS_DM;

   typedef enum
   {
      BARCODE_DM_READ_SQUARE     = 0x00010000,
      BARCODE_DM_READ_RECTANGLE  = 0x00020000,
      BARCODE_DM_READ_SMALL      = 0x00040000,
   } BARCODE_RFALGS_DM;

// L_SUPPORT_XXX constants
#include "ltlck_.h"

// ActiveX error codes
#include "L_OcxErr.h"
