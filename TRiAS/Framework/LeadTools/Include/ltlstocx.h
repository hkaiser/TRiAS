#ifndef APPEARANCE_FLAT
#define APPEARANCE_FLAT   0
#define APPEARANCE_THREED 1
#endif

// ActiveX error codes
#include "L_OcxErr.h"

// L_SUPPORT_XXX constants
#include "ltlck_.h"

   typedef enum
   {
      ALLOWSELECTION_NONE = 0,
      ALLOWSELECTION_SINGLE,
      ALLOWSELECTION_MULTI,
   } ImageListAllowSelectionConstants;

   typedef enum
   {
      SELECTIONSTYLE_SELECTCOLOR = 0,
      SELECTIONSTYLE_PRESSEDBUTTON,
      SELECTIONSTYLE_USERBITMAP,
   } ImageListSelectionStyleConstants;

   typedef enum
   {
      SCROLLSTYLE_VERTICAL = 0,
      SCROLLSTYLE_HORIZONTAL,
   } ImageListScrollStyleConstants;

   typedef enum {
      SCALEMODE_USER,
      SCALEMODE_TWIP,
      SCALEMODE_POINT,
      SCALEMODE_PIXEL,
      SCALEMODE_CHAR,
      SCALEMODE_INCH,
      SCALEMODE_MM,
      SCALEMODE_CM,
   } ImageListScaleModeConstants;

/*
   typedef enum {
      BITONALSCALING_NORMAL,
      BITONALSCALING_FAVORBLACK,
      BITONALSCALING_SCALETOGRAY,
      BITONALSCALING_MAX,
   } ImageListBitonalScalingConstants;

   typedef enum {
      PAINTSCALING_NORMAL,
      PAINTSCALING_RESAMPLE,
      PAINTSCALING_BICUBIC,
      PAINTSCALING_MAX,
   } ImageListPaintScalingConstants;

   typedef enum {
      PAINTDITHER_ORDERED,
      PAINTDITHER_DIFFUSION,
      PAINTDITHER_MAX,
   } ImageListPaintDitherConstants;
*/