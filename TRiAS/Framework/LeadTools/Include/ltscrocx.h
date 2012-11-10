	typedef enum 
	{
	   SCR_CAP_ALL=0,
	   SCR_CAP_BITMAP=1,
	   SCR_CAP_ICON=2,
	   SCR_CAP_CURSOR=4
	}  ScreenCaptureResourceTypes;

	typedef enum 
	{
		SCR_CAP_EXEDLG_TABVIEW=0,
		SCR_CAP_EXEDLG_TREEVIEW
	}  ScreenCaptureExeDlgTypes;

   typedef enum 
	{
	   SCR_CAP_AREA_TRIANGLE=1,
	   SCR_CAP_AREA_RECT,
	   SCR_CAP_AREA_ROUNDRECT,
	   SCR_CAP_AREA_ELLIPSE,
	   SCR_CAP_AREA_POLYGON,
	   SCR_CAP_AREA_FREEHAND
	}  ScreenCaptureAreaTypes;

	typedef enum 
	{
	   SCR_CAP_CLIENT_AREA=1,
	   SCR_CAP_WINDOW,
	}  ScreenCaptureWindowTypes;

   #define CAPTURE_AREA_PATTERN_HORIZONTAL  0 /* ----- */
   #define CAPTURE_AREA_PATTERN_VERTICAL    1 /* ||||| */
   #define CAPTURE_AREA_PATTERN_FDIAGONAL   2 /* \\\\\ */
   #define CAPTURE_AREA_PATTERN_BDIAGONAL   3 /* ///// */
   #define CAPTURE_AREA_PATTERN_CROSS       4 /* +++++ */
   #define CAPTURE_AREA_PATTERN_DIAGCROSS   5 /* xxxxx */
   #define CAPTURE_AREA_PATTERN_SOLID       6 /*Solid Fill*/

   #define CAPTURE_AREA_LINE_SOLID          0 /* Solid   */
   #define CAPTURE_AREA_LINE_DASH           1 /* ------- */
   #define CAPTURE_AREA_LINE_DOT            2 /* ....... */
   #define CAPTURE_AREA_LINE_DASHDOT        3 /* _._._._ */
   #define CAPTURE_AREA_LINE_DASHDOTDOT     4 /* _.._.._ */

   #define CAPTURE_AREA_INFOWND_SIZE_TINY    -1
   #define CAPTURE_AREA_INFOWND_SIZE_SMALL   -2
   #define CAPTURE_AREA_INFOWND_SIZE_MEDIUM  -3
   #define CAPTURE_AREA_INFOWND_SIZE_LARGE   -4
   #define CAPTURE_AREA_INFOWND_SIZE_XLARGE  -5

   #define CAPTURE_AREA_INFOWND_POS_LEFT     -1
   #define CAPTURE_AREA_INFOWND_POS_RIGHT    -2
   #define CAPTURE_AREA_INFOWND_POS_TOP      -3
   #define CAPTURE_AREA_INFOWND_POS_BOTTOM   -4

   #define CAPTURE_AREA_SHOW_DRAWCURSOR	   0x0001
   #define CAPTURE_AREA_INCLUDE_CURSOR	      0x0002
   #define CAPTURE_AREA_ENABLE_KEYBOARD      0x0004
   #define CAPTURE_AREA_SHOW_OPAQUE_TEXT	   0x0008
   #define CAPTURE_AREA_SHOW_CURSORPOS	      0x0010
   #define CAPTURE_AREA_SHOW_CAPTURESIZE	   0x0020
   #define CAPTURE_AREA_SHOW_INFOWINDOW	   0x0040
   #define CAPTURE_AREA_SENSITIVE_INFOWINDOW 0x0080
   #define CAPTURE_AREA_BITMAP_WITH_REGION   0x0100
   #define CAPTURE_AREA_USE_DEFAULT_VALUES   0x0200

   // zooming factors (exclusive)
   #define CAPTURE_AREA_ZOOM_NORM	         1
   #define CAPTURE_AREA_ZOOM_BY2X	         2
   #define CAPTURE_AREA_ZOOM_BY3X	         3
   #define CAPTURE_AREA_ZOOM_BY4X	         4
   #define CAPTURE_AREA_ZOOM_BY5X	         5
   #define CAPTURE_AREA_ZOOM_BY6X	         6
   #define CAPTURE_AREA_ZOOM_BY7X	         7
   #define CAPTURE_AREA_ZOOM_BY8X	         8
   #define CAPTURE_AREA_ZOOM_BY9X	         9
   #define CAPTURE_AREA_ZOOM_BY10X	         10
   #define CAPTURE_AREA_ZOOM_BY11X	         11
   #define CAPTURE_AREA_ZOOM_BY12X	         12
   #define CAPTURE_AREA_ZOOM_BY13X	         13
   #define CAPTURE_AREA_ZOOM_BY14X	         14
   #define CAPTURE_AREA_ZOOM_BY15X	         15

   #define CAPTURE_OBJECT_INVERT	            0x0001
   #define CAPTURE_OBJECT_ENABLE_KEYBOARD    0x0002


// ActiveX error codes
#include "L_OcxErr.h"


   typedef enum{
   SCR_MOD_ALT     =    0x0001,
   SCR_MOD_CONTROL =    0x0002,
   SCR_MOD_SHIFT   =    0x0004,
   };

