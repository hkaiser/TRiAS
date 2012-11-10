   typedef enum
   {
      BROWSE_LOADING = 2, // used to indicate image is being loaded
      BROWSE_SKIPPED = 3, // used to indicate image was skipped b/c it was larger than the specified range
      BROWSE_PRELOAD = 4, // used to indicate image is about to be loaded
   } ThumbnailBrowseStatusConstants;

// ActiveX error codes
#include "L_OcxErr.h"

// L_SUPPORT_XXX constants
#include "ltlck_.h"

/*
   typedef enum{
      CRP_FIXEDPALETTE = 0x0001,
      CRP_OPTIMIZEDPALETTE = 0x0002,
      CRP_BYTEORDERBGR = 0x0004,
      CRP_BYTEORDERRGB = 0x0000,
      CRP_IDENTITYPALETTE = 0x0008,
      CRP_USERPALETTE = 0x0010,
      CRP_NETSCAPEPALETTE = 0x0040,
      CRP_BYTEORDERGRAY = 0x0080,
   }ThumbnailColorResPaletteConstants;

   typedef enum{
      CRD_NODITHERING = 0x0000,
      CRD_FLOYDSTEINDITHERING = 0x0001,
      CRD_STUCKIDITHERING = 0x0002,
      CRD_BURKESDITHERING = 0x0003,
      CRD_SIERRADITHERING = 0x0004,
      CRD_STEVENSONARCEDITHERING = 0x0005,
      CRD_JARVISDITHERING = 0x0006,
      CRD_ORDEREDDITHERING = 0x0007,
   }ThumbnailColorResDitherConstants;
*/
