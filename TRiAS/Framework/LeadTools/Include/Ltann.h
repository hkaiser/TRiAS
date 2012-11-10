/*
   LTANN.H - annotation module header file
   Copyright (c) 1991-2000 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTANN_H_
#define _LTANN_H_

#include "ltkrn.h"
#include "ltfil.h"
#include "ltdis.h"

#define _HEADER_ENTRY_
#include "ltpck.h"

/*
   object types
*/
typedef enum tagANNOBJECTTYPE 
{
   ANNOBJECT_CONTAINER = 0,
   ANNOBJECT_POINTER = 1,
   ANNOBJECT_AUDIO = 2,
   ANNOBJECT_BUTTON = 3,
   ANNOBJECT_ELLIPSE = 4,
   ANNOBJECT_FREEHAND = 5,
   ANNOBJECT_HILITE = 6,
   ANNOBJECT_HOTSPOT = 7,
   ANNOBJECT_LINE = 8,
   ANNOBJECT_NOTE = 9,
   ANNOBJECT_POLYGON = 10,
   ANNOBJECT_POLYLINE = 11,
   ANNOBJECT_RECT = 12,
   ANNOBJECT_REDACT = 13,
   ANNOBJECT_STAMP = 14,
   ANNOBJECT_TEXT = 15,
   ANNOBJECT_AUTOMATION = 16,
   ANNOBJECT_RULER = 17,
   ANNOBJECT_CROSSPRODUCT = 18,
   ANNOBJECT_POINT = 19,
   ANNOBJECT_PROTRACTOR = 20,
   ANNOBJECT_VIDEO = 21,
   ANNOBJECT_PUSHPIN = 22,
   ANNOBJECT_FREEHANDHOTSPOT = 23,

   ANNOBJECT_LAST,            // last automation object defined
} ANNOBJECTTYPE, L_FAR*pANNOBJECTTYPE;

/*
   defined used in L_AnnSetAutoMenuItemEnable/L_AnnGetAutoMenuItemEnable
*/
#define ANNOBJECT_ALL               -1

/*
   automation text items
*/
enum {
/*
   automation menu text
*/
   ANNAUTOTEXT_MENU_UNDO,
   ANNAUTOTEXT_MENU_CUT,
   ANNAUTOTEXT_MENU_COPY,
   ANNAUTOTEXT_MENU_PASTE,
   ANNAUTOTEXT_MENU_DELETE,
   ANNAUTOTEXT_MENU_SELECTALL,
   ANNAUTOTEXT_MENU_BRINGTOFRONT,
   ANNAUTOTEXT_MENU_SENDTOBACK,
   ANNAUTOTEXT_MENU_DEFAULTPROPERTIES,
   ANNAUTOTEXT_MENU_SELECTEDPROPERTIES,
   ANNAUTOTEXT_MENU_CONTAINERPROPERTIES,
   ANNAUTOTEXT_MENU_POINTERPROPERTIES,
   ANNAUTOTEXT_MENU_AUDIOPROPERTIES,
   ANNAUTOTEXT_MENU_BUTTONPROPERTIES,
   ANNAUTOTEXT_MENU_ELLIPSEPROPERTIES,
   ANNAUTOTEXT_MENU_FREEHANDPROPERTIES,
   ANNAUTOTEXT_MENU_HILITEPROPERTIES,
   ANNAUTOTEXT_MENU_HOTSPOTPROPERTIES,
   ANNAUTOTEXT_MENU_LINEPROPERTIES,
   ANNAUTOTEXT_MENU_NOTEPROPERTIES,
   ANNAUTOTEXT_MENU_POLYGONPROPERTIES,
   ANNAUTOTEXT_MENU_POLYLINEPROPERTIES,
   ANNAUTOTEXT_MENU_RECTANGLEPROPERTIES,
   ANNAUTOTEXT_MENU_REDACTPROPERTIES,
   ANNAUTOTEXT_MENU_STAMPPROPERTIES,
   ANNAUTOTEXT_MENU_TEXTPROPERTIES,
   ANNAUTOTEXT_MENU_AUTOMATIONPROPERTIES,
   ANNAUTOTEXT_MENU_RULERPROPERTIES,
   ANNAUTOTEXT_MENU_CROSSPRODUCTPROPERTIES,
   ANNAUTOTEXT_MENU_POINTPROPERTIES,
   ANNAUTOTEXT_MENU_PROTRACTORPROPERTIES,
   ANNAUTOTEXT_MENU_VIDEOPROPERTIES,
   ANNAUTOTEXT_MENU_PUSHPINPROPERTIES,
   ANNAUTOTEXT_MENU_FREEHANDHOSPOTPROPERTIES,

   ANNAUTOTEXT_MENU_LINE,
   ANNAUTOTEXT_MENU_FILL,
   ANNAUTOTEXT_MENU_FOREGROUNDCOLOR,
   ANNAUTOTEXT_MENU_BACKGROUNDCOLOR,
   ANNAUTOTEXT_MENU_FONT,
   ANNAUTOTEXT_MENU_BITMAP,
   ANNAUTOTEXT_MENU_TEXT,
   ANNAUTOTEXT_MENU_FILE,
   ANNAUTOTEXT_MENU_ROP2,
   ANNAUTOTEXT_MENU_TRANSPARENT,
   ANNAUTOTEXT_MENU_LOCK,
   ANNAUTOTEXT_MENU_UNLOCK,
   ANNAUTOTEXT_MENU_LOCKALL,
   ANNAUTOTEXT_MENU_UNLOCKALL,
   ANNAUTOTEXT_MENU_HYPERLINK,
   ANNAUTOTEXT_MENU_NOTEBACKGROUNDCOLOR,
   ANNAUTOTEXT_MENU_REDACTBACKGROUNDCOLOR,
   ANNAUTOTEXT_MENU_HILITEBACKGROUNDCOLOR,
   ANNAUTOTEXT_MENU_HOTSPOTMETAFILE,
   ANNAUTOTEXT_MENU_RULER,

   ANNAUTOTEXT_MENU_BUTTONFONT,
   ANNAUTOTEXT_MENU_GROUP,
   ANNAUTOTEXT_MENU_UNGROUP,
   ANNAUTOTEXT_MENU_NODES,
   ANNAUTOTEXT_MENU_PROTRACTOR,
   ANNAUTOTEXT_MENU_NAME,

   ANNAUTOTEXT_MENU_METAFILE,
   ANNAUTOTEXT_MENU_SECONDARYFILE,
   ANNAUTOTEXT_MENU_TRANSPARENTCOLOR,
   ANNAUTOTEXT_MENU_DELETENODE,
   ANNAUTOTEXT_MENU_ADDNODE,
   ANNAUTOTEXT_MENU_CAPTURE,

/*
   toolbar rubber stamps menu text
*/
   ANNAUTOTEXT_MENU_STAMP_APPROVED,
   ANNAUTOTEXT_MENU_STAMP_ASSIGNED,
   ANNAUTOTEXT_MENU_STAMP_CHECKED,
   ANNAUTOTEXT_MENU_STAMP_CLATPRV,
   ANNAUTOTEXT_MENU_STAMP_COPY,
   ANNAUTOTEXT_MENU_STAMP_DRAFT,
   ANNAUTOTEXT_MENU_STAMP_EXTENDED,
   ANNAUTOTEXT_MENU_STAMP_FAX,
   ANNAUTOTEXT_MENU_STAMP_FAXED,
   ANNAUTOTEXT_MENU_STAMP_IMPORTANT,
   ANNAUTOTEXT_MENU_STAMP_INVOICE,
   ANNAUTOTEXT_MENU_STAMP_NOTICE,
   ANNAUTOTEXT_MENU_STAMP_OFFICIAL,
   ANNAUTOTEXT_MENU_STAMP_ONFILE,
   ANNAUTOTEXT_MENU_STAMP_PAID,
   ANNAUTOTEXT_MENU_STAMP_PASSED,
   ANNAUTOTEXT_MENU_STAMP_PENDING,
   ANNAUTOTEXT_MENU_STAMP_PROCESSED,
   ANNAUTOTEXT_MENU_STAMP_RECEIVED,
   ANNAUTOTEXT_MENU_STAMP_REJECTED,
   ANNAUTOTEXT_MENU_STAMP_RELEASE,
   ANNAUTOTEXT_MENU_STAMP_SENT,
   ANNAUTOTEXT_MENU_STAMP_SHIPPED,
   ANNAUTOTEXT_MENU_STAMP_TOPSECRET,
   ANNAUTOTEXT_MENU_STAMP_URGENT,
   ANNAUTOTEXT_MENU_STAMP_VOID,

/*
   automation line dialog text
*/
   ANNAUTOTEXT_LINE_CAPTION,
   ANNAUTOTEXT_LINE_WIDTH,
   ANNAUTOTEXT_LINE_STYLE,
   ANNAUTOTEXT_LINE_OK,
   ANNAUTOTEXT_LINE_CANCEL,
   ANNAUTOTEXT_LINE_APPLY,

   ANNAUTOTEXT_LINE_SOLID,
   ANNAUTOTEXT_LINE_DASH,
   ANNAUTOTEXT_LINE_DOT,
   ANNAUTOTEXT_LINE_DASHDOT,
   ANNAUTOTEXT_LINE_DASHDOTDOT,
   ANNAUTOTEXT_LINE_NULL,

/*
   automation fill dialog text
*/
   ANNAUTOTEXT_FILL_CAPTION,
   ANNAUTOTEXT_FILL_MODE,
   ANNAUTOTEXT_FILL_PATTERNS,
   ANNAUTOTEXT_FILL_POLYGON,
   ANNAUTOTEXT_FILL_OK,
   ANNAUTOTEXT_FILL_CANCEL,
   ANNAUTOTEXT_FILL_APPLY,

   ANNAUTOTEXT_FILL_TRANSPARENT,
   ANNAUTOTEXT_FILL_TRANSLUCENT,
   ANNAUTOTEXT_FILL_OPAQUE,

   ANNAUTOTEXT_FILL_SOLID,
   ANNAUTOTEXT_FILL_BACKWARDDIAGONAL,
   ANNAUTOTEXT_FILL_CROSS,
   ANNAUTOTEXT_FILL_DIAGONALCROSS,
   ANNAUTOTEXT_FILL_FORWARDDIAGONAL,
   ANNAUTOTEXT_FILL_HORIZONTAL,
   ANNAUTOTEXT_FILL_VERTICAL,

   ANNAUTOTEXT_FILL_WINDING,
   ANNAUTOTEXT_FILL_ALTERNATE,

/*
   automation text dialog text
*/
   ANNAUTOTEXT_TEXT_CAPTION,
   ANNAUTOTEXT_TEXT_OK,
   ANNAUTOTEXT_TEXT_CANCEL,
   ANNAUTOTEXT_TEXT_APPLY,

/*
   automation audio file dialog text
*/
   ANNAUTOTEXT_AUDIOFILE_CAPTION,
   ANNAUTOTEXT_AUDIOFILE_FILTER,

/*
   automation stamp file dialog text
*/
   ANNAUTOTEXT_STAMPFILE_CAPTION,
   ANNAUTOTEXT_STAMPFILE_FILTER,

/*
   automation hotspot file dialog text
*/
   //ANNAUTOTEXT_HOTSPOTFILE_CAPTION,
   //ANNAUTOTEXT_HOTSPOTFILE_FILTER,

/*
   automation point file dialog text
*/
   ANNAUTOTEXT_POINTFILE_CAPTION,
   ANNAUTOTEXT_POINTFILE_FILTER,

/*
   automation audio file dialog text
*/
   ANNAUTOTEXT_VIDEOFILE_CAPTION,
   ANNAUTOTEXT_VIDEOFILE_FILTER,

/*
   automation pushpin file dialog text
*/
   ANNAUTOTEXT_PUSHPINFILE_CAPTION,
   ANNAUTOTEXT_PUSHPINFILE_FILTER,
   ANNAUTOTEXT_PUSHPINSECONDARYFILE_CAPTION,
   ANNAUTOTEXT_PUSHPINSECONDARYFILE_FILTER,

/*
   automation default item text
*/
   ANNAUTOTEXT_ITEM_DEFAULTTEXT,

/*
   automation ROP2 dialog text
*/
   ANNAUTOTEXT_ROP2_CAPTION,
   ANNAUTOTEXT_ROP2_TEXT,
   ANNAUTOTEXT_ROP2_OK,
   ANNAUTOTEXT_ROP2_CANCEL,
   ANNAUTOTEXT_ROP2_APPLY,
   ANNAUTOTEXT_ROP2_COPY,
   ANNAUTOTEXT_ROP2_AND,
   ANNAUTOTEXT_ROP2_XOR,

/*
   automation Lock dialog text
*/
   ANNAUTOTEXT_LOCK_CAPTION,
   ANNAUTOTEXT_LOCK_TEXT,
   ANNAUTOTEXT_LOCK_OK,
   ANNAUTOTEXT_LOCK_CANCEL,

/*
   automation Unlock dialog text
*/
   ANNAUTOTEXT_UNLOCK_CAPTION,
   ANNAUTOTEXT_UNLOCK_TEXT,
   ANNAUTOTEXT_UNLOCK_OK,
   ANNAUTOTEXT_UNLOCK_CANCEL,

/*
   automation Ruler dialog text
*/
   ANNAUTOTEXT_RULER_CAPTION,
   ANNAUTOTEXT_RULER_UNITS,
   ANNAUTOTEXT_RULER_ABBREV,
   ANNAUTOTEXT_RULER_PRECISION,
   ANNAUTOTEXT_RULER_LENGTH,
   ANNAUTOTEXT_RULER_OK,
   ANNAUTOTEXT_RULER_CANCEL,
   ANNAUTOTEXT_RULER_APPLY,

   ANNAUTOTEXT_RULER_INCHES,
   ANNAUTOTEXT_RULER_FEET,
   ANNAUTOTEXT_RULER_YARDS,
   ANNAUTOTEXT_RULER_MICROMETERS,
   ANNAUTOTEXT_RULER_MILIMETERS,
   ANNAUTOTEXT_RULER_CENTIMETERS,
   ANNAUTOTEXT_RULER_METERS,
   ANNAUTOTEXT_RULER_TWIPS,
   ANNAUTOTEXT_RULER_POINTS,
   ANNAUTOTEXT_RULER_PIXELS,

   ANNAUTOTEXT_RULER_SHOWLENGTH,
   ANNAUTOTEXT_RULER_SHOWGAUGE,

/*
   automation Nodes dialog text
*/
   ANNAUTOTEXT_NODES_CAPTION,
   ANNAUTOTEXT_NODES_DISPLAYNODES,
   ANNAUTOTEXT_NODES_GAP,
   ANNAUTOTEXT_NODES_OK,
   ANNAUTOTEXT_NODES_CANCEL,
   ANNAUTOTEXT_NODES_APPLY,

/*
   automation Protractor dialog text
*/
   ANNAUTOTEXT_PROTRACTOR_CAPTION,
   ANNAUTOTEXT_PROTRACTOR_ACUTE,
   ANNAUTOTEXT_PROTRACTOR_UNITS,
   ANNAUTOTEXT_PROTRACTOR_ABBREV,
   ANNAUTOTEXT_PROTRACTOR_PRECISION,
   ANNAUTOTEXT_PROTRACTOR_ARCRADIUS,
   ANNAUTOTEXT_PROTRACTOR_OK,
   ANNAUTOTEXT_PROTRACTOR_CANCEL,
   ANNAUTOTEXT_PROTRACTOR_APPLY,

   ANNAUTOTEXT_PROTRACTOR_DEGREES,
   ANNAUTOTEXT_PROTRACTOR_RADIANS,

   /*
   automation Name dialog text
   */
   ANNAUTOTEXT_NAME_CAPTION,
   ANNAUTOTEXT_NAME_SHOW,
   ANNAUTOTEXT_NAME_OFFSET,
   ANNAUTOTEXT_NAME_OFFSET_X,
   ANNAUTOTEXT_NAME_OFFSET_Y,
   ANNAUTOTEXT_NAME_RESTRICT,
   ANNAUTOTEXT_NAME_OK,
   ANNAUTOTEXT_NAME_CANCEL,
   ANNAUTOTEXT_NAME_APPLY,

/*
   automation default item text
*/
   ANNAUTOTEXT_ITEM_DEFAULTNAME,

/*
   automation Play Video dialog text
*/
   ANNAUTOTEXT_PLAYVIDEO_CAPTION,
   ANNAUTOTEXT_PLAYVIDEO_BALANCE,
   ANNAUTOTEXT_PLAYVIDEO_VOLUME,
   ANNAUTOTEXT_PLAYVIDEO_SPEED,

   ANNAUTOTEXT_PLAYVIDEO_TIP_PLAY,
   ANNAUTOTEXT_PLAYVIDEO_TIP_PAUSE,
   ANNAUTOTEXT_PLAYVIDEO_TIP_STOP,
   ANNAUTOTEXT_PLAYVIDEO_TIP_REWIND,
   ANNAUTOTEXT_PLAYVIDEO_TIP_FORWARD,
   ANNAUTOTEXT_PLAYVIDEO_TIP_PREVMARK,
   ANNAUTOTEXT_PLAYVIDEO_TIP_NEXTMARK,
   ANNAUTOTEXT_PLAYVIDEO_TIP_NEXTFRAME,
   ANNAUTOTEXT_PLAYVIDEO_TIP_PREVFRAME,
   ANNAUTOTEXT_PLAYVIDEO_TIP_STARTSEL,
   ANNAUTOTEXT_PLAYVIDEO_TIP_ENDSEL,

/*
   automation stamp metafile dialog text
*/
   ANNAUTOTEXT_STAMPMETAFILE_CAPTION,
   ANNAUTOTEXT_STAMPMETAFILE_FILTER,

/*
   automation hotspot metafile dialog text
*/
   ANNAUTOTEXT_HOTSPOTMETAFILE_CAPTION,
   ANNAUTOTEXT_HOTSPOTMETAFILE_FILTER,

/*
   toolbar buttons tooltip text
*/
   ANNAUTOTEXT_TOOLTIP_SELECT,
   ANNAUTOTEXT_TOOLTIP_LINE,
   ANNAUTOTEXT_TOOLTIP_RECT,
   ANNAUTOTEXT_TOOLTIP_ELLIPSE,
   ANNAUTOTEXT_TOOLTIP_POLYLINE,
   ANNAUTOTEXT_TOOLTIP_POLYGON,
   ANNAUTOTEXT_TOOLTIP_POINTER,
   ANNAUTOTEXT_TOOLTIP_FREEHAND,
   ANNAUTOTEXT_TOOLTIP_HILITE,
   ANNAUTOTEXT_TOOLTIP_REDACT,
   ANNAUTOTEXT_TOOLTIP_TEXT,
   ANNAUTOTEXT_TOOLTIP_NOTE,
   ANNAUTOTEXT_TOOLTIP_STAMP,
   ANNAUTOTEXT_TOOLTIP_RUBBERSTAMP,
   ANNAUTOTEXT_TOOLTIP_HOTSPOT,
   ANNAUTOTEXT_TOOLTIP_FREEHANDHOTSPOT,
   ANNAUTOTEXT_TOOLTIP_AUDIO,
   ANNAUTOTEXT_TOOLTIP_BUTTON,
   ANNAUTOTEXT_TOOLTIP_RULER,
   ANNAUTOTEXT_TOOLTIP_CROSSPRODUCT,
   ANNAUTOTEXT_TOOLTIP_POINT,
   ANNAUTOTEXT_TOOLTIP_PROTRACTOR,
   ANNAUTOTEXT_TOOLTIP_VIDEO,
   ANNAUTOTEXT_TOOLTIP_PUSHPIN,

/*
   automation transparent color dialog text
*/
   ANNAUTOTEXT_TRANSPARENTCOLOR_CAPTION,
   ANNAUTOTEXT_TRANSPARENTCOLOR_COLORARRAYFRAME,
   ANNAUTOTEXT_TRANSPARENTCOLOR_CURRENTCOLORFRAME,
   ANNAUTOTEXT_TRANSPARENTCOLOR_COLOR,
   ANNAUTOTEXT_TRANSPARENTCOLOR_RED,
   ANNAUTOTEXT_TRANSPARENTCOLOR_GREEN,
   ANNAUTOTEXT_TRANSPARENTCOLOR_BLUE,
   ANNAUTOTEXT_TRANSPARENTCOLOR_OK,
   ANNAUTOTEXT_TRANSPARENTCOLOR_CANCEL,

/*
   automation capture file dialog text
*/
   ANNAUTOTEXT_CAPTUREFILE_CAPTION,
   ANNAUTOTEXT_CAPTUREFILE_FILTER,

/*
   automation capture dialog text
*/
   ANNAUTOTEXT_CAPTUREWINDOW_CAPTION,
   ANNAUTOTEXT_CAPTURE_CAPTION,
   ANNAUTOTEXT_CAPTURE_CAPTUREDRIVERS,
   ANNAUTOTEXT_CAPTURE_VIDEODIALOGS,
   ANNAUTOTEXT_CAPTURE_VIDEOFORMAT,
   ANNAUTOTEXT_CAPTURE_VIDEODISPLAY,
   ANNAUTOTEXT_CAPTURE_VIDEOSOURCE,
   ANNAUTOTEXT_CAPTURE_VIDEOCOMPRESSION,
   ANNAUTOTEXT_CAPTURE_DISPLAYMODE,
   ANNAUTOTEXT_CAPTURE_NONE,
   ANNAUTOTEXT_CAPTURE_NONEOVERLAY,
   ANNAUTOTEXT_CAPTURE_PREVIEW,
   ANNAUTOTEXT_CAPTURE_PREVIEWFRAMESPERSEC,
   ANNAUTOTEXT_CAPTURE_OPTIONS,
   ANNAUTOTEXT_CAPTURE_TIMELIMIT,
   ANNAUTOTEXT_CAPTURE_CAPTUREFRAMESPERSEC,
   ANNAUTOTEXT_CAPTURE_STARTCAPTURE,
   ANNAUTOTEXT_CAPTURE_ENDCAPTURE,
   ANNAUTOTEXT_CAPTURE_FRAMESCAPTURED,
   ANNAUTOTEXT_CAPTURE_AUDIOOPTIONS,
   ANNAUTOTEXT_CAPTURE_CAPTUREAUDIO,
   ANNAUTOTEXT_CAPTURE_SYNCAUDIO,
   ANNAUTOTEXT_CAPTURE_CAPTUREFILE,
   ANNAUTOTEXT_CAPTURE_BROWSE,
   ANNAUTOTEXT_CAPTURE_FILESIZE,
   ANNAUTOTEXT_CAPTURE_OK,
   ANNAUTOTEXT_CAPTURE_CANCEL,

   ANNAUTOTEXT_CAPTURE_WAV_1M08,
   ANNAUTOTEXT_CAPTURE_WAV_1S08,
   ANNAUTOTEXT_CAPTURE_WAV_1M16,
   ANNAUTOTEXT_CAPTURE_WAV_1S16,
   ANNAUTOTEXT_CAPTURE_WAV_2M08,
   ANNAUTOTEXT_CAPTURE_WAV_2S08,
   ANNAUTOTEXT_CAPTURE_WAV_2M16,
   ANNAUTOTEXT_CAPTURE_WAV_2S16,
   ANNAUTOTEXT_CAPTURE_WAV_4M08,
   ANNAUTOTEXT_CAPTURE_WAV_4S08,
   ANNAUTOTEXT_CAPTURE_WAV_4M16,
   ANNAUTOTEXT_CAPTURE_WAV_4S16,
   
   ANNAUTOTEXT_CAPTURE_DEFAULTNAME,
   ANNAUTOTEXT_CAPTURE_NODRIVERS,

   ANNAUTOTEXT_DIALOG_FONT,

   ANNAUTOTEXT_MAX,
};

#define ANNMENU_DISABLED   0
#define ANNMENU_ENABLED    1
#define ANNMENU_DEFAULT    2

/*
   save/clipboard formats
*/
#define ANNFMT_NATIVE   0
#define ANNFMT_WMF      1
#define ANNFMT_TIFFTAG  2     /* Save all Lead info */
#define ANNFMT_WANGTAG  3     /* Wang annotation compatibility mode */
#define ANNFMT_ENCODED  4     /* Encoded native format (better security, smaller file size) */

/*
   Value of the Annotation Tag
*/
#define ANNTAG_TIFF           32932

/*
   toolbar buttons
*/
#define ANNTOOL_SELECT           0
#define ANNTOOL_LINE             1
#define ANNTOOL_RECT             2
#define ANNTOOL_ELLIPSE          3
#define ANNTOOL_POLYLINE         4
#define ANNTOOL_POLYGON          5
#define ANNTOOL_POINTER          6
#define ANNTOOL_FREEHAND         7
#define ANNTOOL_HILITE           8
#define ANNTOOL_REDACT           9
#define ANNTOOL_TEXT             10
#define ANNTOOL_NOTE             11
#define ANNTOOL_STAMP            12
#define ANNTOOL_BUTTON           13
#define ANNTOOL_HOTSPOT          14
#define ANNTOOL_AUDIO            15
#define ANNTOOL_RULER            16
#define ANNTOOL_CROSSPRODUCT     17
#define ANNTOOL_POINT            18
#define ANNTOOL_PROTRACTOR       19
#define ANNTOOL_VIDEO            20
#define ANNTOOL_PUSHPIN          21
#define ANNTOOL_FREEHANDHOTSPOT  22

#define ANNTOOL_STAMP_FIRST      23    /* define that marks the first rubber stamp */
#define ANNTOOL_STAMP_APPROVED   23
#define ANNTOOL_STAMP_ASSIGNED   24
#define ANNTOOL_STAMP_CHECKED    25
#define ANNTOOL_STAMP_CLATPRV    26
#define ANNTOOL_STAMP_COPY       27
#define ANNTOOL_STAMP_DRAFT      28
#define ANNTOOL_STAMP_EXTENDED   29
#define ANNTOOL_STAMP_FAX        30
#define ANNTOOL_STAMP_FAXED      31
#define ANNTOOL_STAMP_IMPORTANT  32
#define ANNTOOL_STAMP_INVOICE    33
#define ANNTOOL_STAMP_NOTICE     34
#define ANNTOOL_STAMP_OFFICIAL   35
#define ANNTOOL_STAMP_ONFILE     36
#define ANNTOOL_STAMP_PAID       37
#define ANNTOOL_STAMP_PASSED     38
#define ANNTOOL_STAMP_PENDING    39
#define ANNTOOL_STAMP_PROCESSED  40
#define ANNTOOL_STAMP_RECEIVED   41
#define ANNTOOL_STAMP_REJECTED   42
#define ANNTOOL_STAMP_RELEASE    43
#define ANNTOOL_STAMP_SENT       44
#define ANNTOOL_STAMP_SHIPPED    45
#define ANNTOOL_STAMP_TOPSECRET  46
#define ANNTOOL_STAMP_URGENT     47
#define ANNTOOL_STAMP_VOID       48
#define ANNTOOL_STAMP_LAST       48  /* define that marks the last rubber stamp */

#define ANNTOOL_LAST             48

#define ANNTOOL_USER             0x0100 // first user defined tool
#define ANNTOOL_USERLAST         0x0200 // last allowed user tools

#define ISVALIDTOOL(nTool) (((nTool) >= ANNTOOL_SELECT && (nTool) <= ANNTOOL_LAST) || ((nTool) >= ANNTOOL_USER && (nTool) <= ANNTOOL_USERLAST))

/*
   data structures
*/
typedef struct _ANNPOINT
{
   L_DOUBLE x;
   L_DOUBLE y;
} ANNPOINT, L_FAR *pANNPOINT;

typedef struct _ANNRECT
{
   L_DOUBLE left;
   L_DOUBLE top;
   L_DOUBLE right;
   L_DOUBLE bottom;
} ANNRECT, L_FAR *pANNRECT;

/*
   toolbar defines/structures
*/

#define ANNBUTTON_MULTIPLE    0x0001   // if this flag is set, then the pButtonArray defines the button

typedef struct _ANNTOOL
{
   L_UINT         uTool;
   L_INT          nMenuTextID;          // used if uMenuTextID >= 0
   L_TCHAR L_FAR*  pMenuText;            // used if uMenuTextID == -1
} ANNTOOL, L_FAR*pANNTOOL;

typedef struct _ANNBUTTON
{
   L_UINT         uFlags;

   L_UINT         uTool;

   L_UINT         uToolCount;
   pANNTOOL       pTools;

   pBITMAPHANDLE  pBitmapUp;
   pBITMAPHANDLE  pBitmapDown;
#ifdef WIN32
   L_INT          nToolTipTextID;       // used if uToolTipTextID >= 0
   L_TCHAR L_FAR*  pToolTipText;         // used if uToolTipTextID == -1
#endif
} ANNBUTTON, L_FAR*pANNBUTTON;

typedef struct _ANNTOOLBARINFO
{
   L_UINT   uButtons;
   L_UINT   uRows;
   L_UINT   uColumns;
} ANNTOOLBARINFO, L_FAR*pANNTOOLBARINFO;

/* 
   width and height of the toolbar bitmaps
*/
#define TOOLBARIMAGECX 16
#define TOOLBARIMAGECY 15

/* 
   width and height of the toolbar buttons
*/
#define TOOLBARBUTTONCX 24
#define TOOLBARBUTTONCY 22

/*
   messages
*/
#define WM_LTANNEVENT      (WM_USER + 512)
#define WM_LTANNHYPERLINK  (WM_USER + 513)   // message used internally by LEADTOOLS ActiveX

/*
   wParam = event id
   lParam = specific event data
*/
#define LTANNEVENT_TOOLCHECKED   0
#define LTANNEVENT_TOOLCREATE    1
#define LTANNEVENT_TOOLDESTROY   2
#define LTANNEVENT_ACTIVATE      3
#define LTANNEVENT_DEACTIVATE    4
#define LTANNEVENT_INSERT        5
#define LTANNEVENT_REMOVE        6
#define LTANNEVENT_AUTOBEGINSET  7
#define LTANNEVENT_AUTOENDSET    8
#define LTANNEVENT_AUTOCLICKED   9
#define LTANNEVENT_AUTOCHANGED   10
#define LTANNEVENT_AUTOITEMCHANGED  11
#define LTANNEVENT_AUTOSELECT    12
#define LTANNEVENT_LOCKED        13
#define LTANNEVENT_UNLOCKED      14
#define LTANNEVENT_HYPERLINK     15
#define LTANNEVENT_HYPERLINKMENU 16
#define LTANNEVENT_LBUTTONDOWN   17
#define LTANNEVENT_MOUSEMOVE     18
#define LTANNEVENT_LBUTTONUP     19
#define LTANNEVENT_MENU          20
#define LTANNEVENT_AUTOITEMCHANGING 21
#define LTANNEVENT_RESERVED1        22  //Reserved for internal use

/* 
   allowed range for user defined menus
*/
#define LTANNEVENT_MENUFIRST     0x0100
#define LTANNEVENT_MENULAST      0x01FF

#ifndef HANDLE_MSG
#define HANDLE_MSG(hwnd, message, fn)    \
    case (message): return HANDLE_##message((hwnd), (wParam), (lParam), (fn))
#endif

/* LRESULT Cls_OnLtAnnEvent(HWND hwnd, int id, LPARAM lParam); */
#define HANDLE_WM_LTANNEVENT(hwnd, wParam, lParam, fn) \
      (LRESULT)(DWORD)(fn)(hwnd, (int) wParam, lParam)
#define FORWARD_WM_LTANNEVENT(hwnd, id, lParam, fn) \
    (LRESULT)(DWORD)(fn)((hwnd), WM_LTANNEVENT, (int) (id), (LPARAM) (lParam))

/*
   line styles
*/
#define ANNLINE_SOLID         0
#define ANNLINE_DASH          1
#define ANNLINE_DOT           2
#define ANNLINE_DASHDOT       3
#define ANNLINE_DASHDOTDOT    4
#define ANNLINE_NULL          5

/*
   fill patterns
*/
#define ANNPATTERN_SOLID         0
#define ANNPATTERN_BDIAGONAL     1
#define ANNPATTERN_CROSS         2
#define ANNPATTERN_DIAGCROSS     3
#define ANNPATTERN_FDIAGONAL     4
#define ANNPATTERN_HORIZONTAL    5
#define ANNPATTERN_VERTICAL      6

/*
   fill mode
*/
#define ANNMODE_TRANSPARENT   0
#define ANNMODE_TRANSLUCENT   1
#define ANNMODE_OPAQUE        2

/*
   poly fill mode
*/
#define ANNPOLYFILL_WINDING   0
#define ANNPOLYFILL_ALTERNATE 1

/*
   define states
*/
#define ANNDEFINE_BEGINSET    0
#define ANNDEFINE_BEGINMOVE   1
#define ANNDEFINE_BEGINROTATE 2
#define ANNDEFINE_BEGINRESIZE 3
#define ANNDEFINE_BEGINSELECT 4
#define ANNDEFINE_APPEND      5
#define ANNDEFINE_UPDATE      6
#define ANNDEFINE_END         7
#define ANNDEFINE_BEGINMOVESELECTED    8
#define ANNDEFINE_BEGINROTATESELECTED  9
#define ANNDEFINE_BEGINRESIZESELECTED  10
#define ANNDEFINE_BEGINMOVEPOINT       11
#define ANNDEFINE_BEGINMOVENAME        12

/*
   active states
*/
#define ANNACTIVE_DISABLED    0
#define ANNACTIVE_ENABLED     1

/*
   hittest results
*/
#define ANNHIT_NONE           0
#define ANNHIT_BODY           1
#define ANNHIT_HANDLE         2
#define ANNHIT_NAME           3

/*
   user modes
*/
#define ANNUSER_DESIGN        0
#define ANNUSER_RUN           1

/*
   flags for set functions
*/
#define ANNFLAG_SELECTED       0x0001
#define ANNFLAG_NOTCONTAINER   0x0002
#define ANNFLAG_NOTTHIS        0x0004
#define ANNFLAG_RECURSE        0x0008
#define ANNFLAG_NOINVALIDATE   0x0010
#define ANNFLAG_CHECKMENU      0x0020
#define ANNFLAG_USER           0x0040

/*
   toolbar create alignment
*/
#define ANNTOOLALIGN_LEFT     0x0000
#define ANNTOOLALIGN_RIGHT    0x0001
#define ANNTOOLALIGN_TOP      0x0000
#define ANNTOOLALIGN_BOTTOM   0x0002

/*
   ROP2 values
*/
#define ANNROP2_COPY          0
#define ANNROP2_AND           1
#define ANNROP2_XOR           2

/*
   Hyperlink types
*/
#define ANNLINK_NONE          0
#define ANNLINK_LTANNEVENT    1
#define ANNLINK_USERMSG       2
#define ANNLINK_RUN           3
#define ANNLINK_WEBPAGE       4

/*
   Distance units
*/
#define ANNUNIT_INCHES        0
#define ANNUNIT_FEET          1
#define ANNUNIT_YARDS         2
#define ANNUNIT_MICROMETERS   3
#define ANNUNIT_MILIMETERS    4
#define ANNUNIT_CENTIMETERS   5
#define ANNUNIT_METERS        6
#define ANNUNIT_TWIPS         7
#define ANNUNIT_POINTS        8
#define ANNUNIT_PIXELS        9

/*
   Angle units
*/
#define ANNANGLE_DEGREES      0
#define ANNANGLE_RADIANS      1

/* 
   Metafile types 
*/

enum
{
   ANNMETAFILE_USER = 0x7FFF,    // user-defined metafiles
   ANNMETAFILE_APPROVED = 0,     // predefined metafiles
   ANNMETAFILE_ASSIGNED,
   ANNMETAFILE_CHECKED,
   ANNMETAFILE_CLATPRV,
   ANNMETAFILE_COPY,
   ANNMETAFILE_DRAFT,
   ANNMETAFILE_EXTENDED,
   ANNMETAFILE_FAX,
   ANNMETAFILE_FAXED,
   ANNMETAFILE_IMPORTANT,
   ANNMETAFILE_INVOICE,
   ANNMETAFILE_NOTICE,
   ANNMETAFILE_OFFICIAL,
   ANNMETAFILE_ONFILE,
   ANNMETAFILE_PAID,
   ANNMETAFILE_PASSED,
   ANNMETAFILE_PENDING,
   ANNMETAFILE_PROCESSED,
   ANNMETAFILE_RECEIVED,
   ANNMETAFILE_REJECTED,
   ANNMETAFILE_RELEASE,
   ANNMETAFILE_SENT,
   ANNMETAFILE_SHIPPED,
   ANNMETAFILE_TOPSECRET,
   ANNMETAFILE_URGENT,
   ANNMETAFILE_VOID,
   ANNMETAFILE_HOTSPOT,       

   ANNMETAFILE_LAST,             // last predefined metafile
};

/*
   Show flags
*/

#define ANNSHOW_LENGTH  0x0001
#define ANNSHOW_GAUGE   0x0002

/*
   object handle
*/
typedef HANDLE HANNOBJECT;
typedef HANNOBJECT L_FAR *pHANNOBJECT;

/*
   structure passed to the mouse notifications
*/

typedef struct _ANNMOUSEPOS
{
   L_BOOL   fDoubleClick;  /* valid only for LTANNEVENT_LBUTTONDOWN */
   POINT    pt;
   L_UINT   uKeyFlags;
   L_BOOL   fUpdatePos;    /* if TRUE, the mouse cursor is updated */
} ANNMOUSEPOS, L_FAR*pANNMOUSEPOS;

/*
   automation option flags
*/

#define ANNAUTO_TABBEDDIALOG      0x0001   /* display tabbed dialog boxes */
#define ANNAUTO_REVERSEEDITKEYS   0x0002   /* CTRL+ENTER exits edit box, ENTER creates new line */

/* 
   defines and structures that describe parameter for LTANNEVENT_AUTOCHANGING notification event
*/

#define SUCCESS_CHANGE     1  // change the object
#define SUCCESS_NOCHANGE   2  // do not change the object

typedef enum tagANNCHANGETYPE
{
   ANNCHANGE_DELETE,       // the object is being deleted
   ANNCHANGE_ROTATE,       // the object is being rotated
} ANNCHANGETYPE, L_FAR*pANNCHANGETYPE;

typedef struct tagANNCHANGEPARAM
{
   L_INT          nSize;            // size of this structure
   HANNOBJECT     hObject;          // object being changed.
   ANNCHANGETYPE  uChange;          // the type of change being performed
   L_INT          nChange;          // set to TRUE to allow the modification, set to FALSE to disable it
   L_DOUBLE       dAngle;           // valid if the object is being rotated
} ANNCHANGEPARAM, L_FAR*pANNCHANGEPARAM;


typedef struct tagANNFILEINFO
{
   L_INT32     nSize;
   L_INT32     nOffset;
   L_INT32     nVersion;
   L_UINT      uFormat;          //ANNFMT_NATIVE,ANNFMT_WMF	,ANNFMT_ENCODED   
   L_INT32     nTotalPages;
   L_INT32     nReserved;
} ANNFILEINFO, L_FAR*pANNFILEINFO;


/*
   callback typedefs
*/
typedef L_INT (pEXT_CALLBACK ANNENUMCALLBACK) (HANNOBJECT hObject, L_VOID L_FAR * pUserData);

/*
   function prototypes
*/

L_INT EXT_FUNCTION L_AnnBringToFront (HANNOBJECT hObject);

L_INT EXT_FUNCTION L_AnnClipboardReady(L_BOOL L_FAR *pfReady);

L_INT EXT_FUNCTION L_AnnCopy(HANNOBJECT hSource,
                                 pHANNOBJECT phDest);

L_INT EXT_FUNCTION L_AnnCopyFromClipboard(HWND hWnd,
                                          pHANNOBJECT phContainer);

L_INT EXT_FUNCTION L_AnnCopyToClipboard(HANNOBJECT hObject,
                                        L_UINT uFormat,
                                        L_BOOL fSelected,
                                        L_BOOL fEmpty,
                                        L_BOOL fCheckMenu);

L_INT EXT_FUNCTION L_AnnCutToClipboard(HANNOBJECT hObject,
                                        L_UINT uFormat,
                                        L_BOOL fSelected,
                                        L_BOOL fEmpty,
                                        L_BOOL fCheckMenu);


L_INT EXT_FUNCTION L_AnnCreate (L_UINT uObjectType,
                                 pHANNOBJECT phObject);

L_INT EXT_FUNCTION L_AnnCreateContainer (HWND hWnd,
                                          pANNRECT pRect,
                                          L_BOOL fVisible,
                                          pHANNOBJECT phObject);
L_INT EXT_FUNCTION L_AnnCreateItem (HANNOBJECT hContainer,
                                     L_UINT uObjectType,
                                     L_BOOL fVisible,
                                     pHANNOBJECT phObject);

L_INT EXT_FUNCTION L_AnnCreateToolBar(HWND hwndParent,
                                      LPPOINT pPoint,
                                      L_UINT uAlign,
                                      L_BOOL fVisible,
                                      HWND L_FAR *phWnd,
                                      L_UINT uButtons,
                                      pANNBUTTON pButtons);

L_INT EXT_FUNCTION L_AnnDefine (HANNOBJECT hObject,
                                 LPPOINT pPoint,
                                 L_UINT uState);

L_INT EXT_FUNCTION L_AnnDeletePageOffset(L_INT fd,	
                                         L_INT32 nOffset,
                                         L_INT32 nPage);
L_INT EXT_FUNCTION L_AnnDeletePage(L_TCHAR L_FAR * pFile, 
                                   L_INT32 nPage);

L_INT EXT_FUNCTION L_AnnDeletePageMemory (HGLOBAL hMem, L_UINT32 *puMemSize, L_INT32 nPage);


L_INT EXT_FUNCTION L_AnnDestroy (HANNOBJECT hObject,
                                 L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnDraw (HDC hDC,
                               LPRECT prcInvalid,
                               HANNOBJECT hObject);
L_INT EXT_FUNCTION L_AnnEnumerate (HANNOBJECT hObject,
                                    ANNENUMCALLBACK pfnCallback,
                                    L_VOID L_FAR * pUserData,
                                    L_UINT uFlags,
                                    L_TCHAR L_FAR*pUserList);

L_INT EXT_FUNCTION L_AnnFileInfo (L_TCHAR *pszFile, 
                                  pANNFILEINFO pAnnFileInfo);

L_INT EXT_FUNCTION L_AnnFileInfoOffset (L_INT fd, 
                                        pANNFILEINFO pAnnFileInfo);

L_INT EXT_FUNCTION L_AnnFileInfoMemory (L_UCHAR L_FAR * pMem, 
                                        L_UINT32 uMemSize, 
                                        pANNFILEINFO pAnnFileInfo);


L_INT EXT_FUNCTION L_AnnFlip(HANNOBJECT hObject,
                                    pANNPOINT pCenter,
                                    L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnGetActiveState (HANNOBJECT hObject,
                                         L_UINT L_FAR * puState);
L_INT EXT_FUNCTION L_AnnGetAutoContainer (HANNOBJECT hObject,
                                          pHANNOBJECT phContainer);
L_INT EXT_FUNCTION L_AnnGetAutoDrawEnable (HANNOBJECT hObject,
                                          L_BOOL L_FAR *pfEnable);

L_INT EXT_FUNCTION L_AnnGetAutoMenuEnable (HANNOBJECT hObject,
                                          L_BOOL L_FAR *pfEnable);

L_INT EXT_FUNCTION L_AnnGetAutoText (HANNOBJECT hObject,
                                     L_UINT uItem,
                                     L_TCHAR L_FAR *pText);

L_INT EXT_FUNCTION L_AnnGetAutoTextLen (HANNOBJECT hObject,
                                     L_UINT uItem,
                                     L_UINT L_FAR * puLen);

L_INT EXT_FUNCTION L_AnnGetBackColor (HANNOBJECT hObject,
                                       COLORREF L_FAR * pcrBack);
L_INT EXT_FUNCTION L_AnnGetBitmap (HANNOBJECT hObject,
                                    pBITMAPHANDLE pBitmap);
L_INT EXT_FUNCTION L_AnnGetBitmapDpiX(HANNOBJECT hObject,
                                      L_DOUBLE  L_FAR*pdDpiX);
L_INT EXT_FUNCTION L_AnnGetBitmapDpiY(HANNOBJECT hObject,
                                      L_DOUBLE  L_FAR*pdDpiY);

L_INT EXT_FUNCTION L_AnnGetBoundingRect (HANNOBJECT hObject, 
                                         LPRECT pRect, 
                                         LPRECT pRectName);


L_INT EXT_FUNCTION L_AnnGetContainer (HANNOBJECT hObject,
                                       pHANNOBJECT phContainer);
L_INT EXT_FUNCTION L_AnnGetDistance(HANNOBJECT hObject,
                                    L_DOUBLE L_FAR*pdDistance,
                                    L_DOUBLE L_FAR*pdDistance2);
L_INT EXT_FUNCTION L_AnnGetDpiX (HANNOBJECT hObject,
                                 L_DOUBLE L_FAR * pdDpiX);
L_INT EXT_FUNCTION L_AnnGetDpiY (HANNOBJECT hObject,
                                 L_DOUBLE L_FAR * pdDpiY);
L_INT EXT_FUNCTION L_AnnGetFillMode (HANNOBJECT hObject,
                                      L_UINT L_FAR * puFillMode);
L_INT EXT_FUNCTION L_AnnGetFillPattern (HANNOBJECT hObject,
                                         L_UINT L_FAR * puFillPattern);
L_INT EXT_FUNCTION L_AnnGetFontBold (HANNOBJECT hObject,
                                      L_BOOL L_FAR * pfFontBold);
L_INT EXT_FUNCTION L_AnnGetFontItalic (HANNOBJECT hObject,
                                        L_BOOL L_FAR * pfFontItalic);
L_INT EXT_FUNCTION L_AnnGetFontName (HANNOBJECT hObject,
                                      L_TCHAR L_FAR * pFontName);
L_INT EXT_FUNCTION L_AnnGetFontNameLen (HANNOBJECT hObject,
                                         L_UINT L_FAR * puLen);
L_INT EXT_FUNCTION L_AnnGetFontSize (HANNOBJECT hObject,
                                      L_DOUBLE L_FAR * pdFontSize);
L_INT EXT_FUNCTION L_AnnGetFontStrikeThrough (HANNOBJECT hObject,
                                        L_BOOL L_FAR * pfFontStrikeThrough);
L_INT EXT_FUNCTION L_AnnGetFontUnderline (HANNOBJECT hObject,
                                           L_BOOL L_FAR * pfFontUnderline);
L_INT EXT_FUNCTION L_AnnGetForeColor (HANNOBJECT hObject,
                                       COLORREF L_FAR * pcrFore);
L_INT EXT_FUNCTION L_AnnGetGaugeLength(HANNOBJECT hObject,
                                       L_DOUBLE L_FAR*pdLength);
L_INT EXT_FUNCTION L_AnnGetHyperlink (HANNOBJECT hObject,
                                       L_UINT L_FAR*puType,
                                       L_UINT L_FAR*puMsg,
                                       WPARAM L_FAR*pwParam,
                                       L_TCHAR L_FAR*pLink);
L_INT EXT_FUNCTION L_AnnGetHyperlinkLen (HANNOBJECT hObject,
                                       L_UINT L_FAR*puLen);
L_INT EXT_FUNCTION L_AnnGetHyperlinkMenuEnable(HANNOBJECT hObject,
                              L_BOOL L_FAR*pfEnable);
L_INT EXT_FUNCTION L_AnnGetLineStyle (HANNOBJECT hObject,
                                       L_UINT L_FAR * puLineStyle);
L_INT EXT_FUNCTION L_AnnGetLineWidth (HANNOBJECT hObject,
                                       L_DOUBLE L_FAR * pdLineWidth);
L_INT EXT_FUNCTION L_AnnGetLocked (HANNOBJECT hObject, 
                                   L_BOOL L_FAR * pfLocked);
L_INT EXT_FUNCTION L_AnnGetOffsetX (HANNOBJECT hObject,
                                     L_DOUBLE L_FAR * pdOffsetX);
L_INT EXT_FUNCTION L_AnnGetOffsetY (HANNOBJECT hObject,
                                     L_DOUBLE L_FAR * pdOffsetY);
L_INT EXT_FUNCTION L_AnnGetPointCount (HANNOBJECT hObject,
                                     L_UINT L_FAR *puCount);
L_INT EXT_FUNCTION L_AnnGetPoints (HANNOBJECT hObject,
                                     pANNPOINT pPoints);
L_INT EXT_FUNCTION L_AnnGetPolyFillMode (HANNOBJECT hObject,
                                      L_UINT L_FAR * puPolyFillMode);
L_INT EXT_FUNCTION L_AnnGetRect (HANNOBJECT hObject, 
                                 pANNRECT pRect, 
                                 pANNRECT pRectName);
L_INT EXT_FUNCTION L_AnnGetROP2 (HANNOBJECT hObject,
                                  L_UINT L_FAR*puRop2);
L_INT EXT_FUNCTION L_AnnGetScalarX (HANNOBJECT hObject,
                                     L_DOUBLE L_FAR * pdScalarX);
L_INT EXT_FUNCTION L_AnnGetScalarY (HANNOBJECT hObject,
                                     L_DOUBLE L_FAR * pdScalarY);
L_INT EXT_FUNCTION L_AnnGetSelectCount (HANNOBJECT hObject,
                                      L_UINT L_FAR *puCount);
L_INT EXT_FUNCTION L_AnnGetSelected (HANNOBJECT hObject,
                                      L_BOOL L_FAR * pfSelected);
L_INT EXT_FUNCTION L_AnnGetSelectItems(HANNOBJECT hObject, 
                                       pHANNOBJECT pItems);
L_INT EXT_FUNCTION L_AnnGetSelectRect(HANNOBJECT hObject,
                                       LPRECT pRect);
L_INT EXT_FUNCTION L_AnnGetTag (HANNOBJECT hObject,
                                 L_UINT32 L_FAR * puTag);
L_INT EXT_FUNCTION L_AnnGetText (HANNOBJECT hObject,
                                  L_TCHAR L_FAR * pText);
L_INT EXT_FUNCTION L_AnnGetTextLen (HANNOBJECT hObject,
                                     L_UINT L_FAR * puLen);
L_INT EXT_FUNCTION L_AnnGetTool (HANNOBJECT hObject,
                                    L_UINT L_FAR * puTool);
L_INT EXT_FUNCTION L_AnnGetToolBarButtonVisible(HWND hwndToolBar,
                                     L_UINT uButton,
                                     L_BOOL L_FAR *pfVisible);
L_INT EXT_FUNCTION L_AnnGetToolBarChecked (HWND hwndToolBar,
                                     L_UINT L_FAR *puChecked);
L_INT EXT_FUNCTION L_AnnGetTransparent (HANNOBJECT hObject,
                                  L_BOOL L_FAR*pbTransparent);
L_INT EXT_FUNCTION L_AnnGetType (HANNOBJECT hObject,
                                  L_UINT L_FAR * puObjectType);
L_INT EXT_FUNCTION L_AnnGetTopContainer (HANNOBJECT hObject,
                                  pHANNOBJECT phContainer);
L_INT EXT_FUNCTION L_AnnGetUnit(HANNOBJECT hObject,
                                L_UINT L_FAR*puUnit,
                                L_TCHAR L_FAR*pUnitAbbrev,
                                L_UINT L_FAR*puPrecision);
L_INT EXT_FUNCTION L_AnnGetUnitLen(HANNOBJECT hObject,
                                   L_UINT L_FAR*puLen);
L_INT EXT_FUNCTION L_AnnGetUserMode (HANNOBJECT hObject,
                                      L_UINT L_FAR * puMode);
L_INT EXT_FUNCTION L_AnnGetVisible (HANNOBJECT hObject,
                                     L_BOOL L_FAR * pfVisible);
L_INT EXT_FUNCTION L_AnnGetWnd (HANNOBJECT hObject,
                                 HWND L_FAR * phWnd);
L_INT EXT_FUNCTION L_AnnHitTest (HANNOBJECT hObject,
                                  LPPOINT pPoint,
                                  L_UINT L_FAR * puResult,
                                  pHANNOBJECT phObjectHit);
L_INT EXT_FUNCTION L_AnnInsert (HANNOBJECT hContainer,
                                 HANNOBJECT hObject,
                                 L_BOOL fStripContainer);
L_INT EXT_FUNCTION L_AnnGetItem (HANNOBJECT hContainer,
                                 pHANNOBJECT phItem);
L_INT EXT_FUNCTION L_AnnLoad (L_TCHAR L_FAR * pFile,
                               pHANNOBJECT phObject,
                               pLOADFILEOPTION pLoadOptions);
L_INT EXT_FUNCTION L_AnnLoadOffset (L_INT fd,
                               L_INT32 nOffset,
                               L_UINT32 nLength,
                               pHANNOBJECT phObject,
                               pLOADFILEOPTION pLoadOptions);
L_INT EXT_FUNCTION L_AnnLoadMemory (L_UCHAR L_FAR * pMem,
                               L_UINT32 uMemSize,
                               pHANNOBJECT phObject,
                               pLOADFILEOPTION pLoadOptions);
L_INT EXT_FUNCTION L_AnnLock (HANNOBJECT hObject, 
                              L_TCHAR L_FAR* pLockKey, 
                              L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnMove(HANNOBJECT hObject,
                               L_DOUBLE dDx,
                               L_DOUBLE dDy,
                               L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnPrint(HDC hDC,
                              LPRECT prcBounds,
                              HANNOBJECT hObject);
L_INT EXT_FUNCTION L_AnnRealize(pBITMAPHANDLE pBitmap,
                               LPRECT prcBounds,
                               HANNOBJECT hObject,
                               L_BOOL fRedactOnly);
L_INT EXT_FUNCTION L_AnnResize(HANNOBJECT hObject,
                               L_DOUBLE dFactorX,
                               L_DOUBLE dFactorY,
                               pANNPOINT pCenter,
                               L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnReverse(HANNOBJECT hObject,
                               pANNPOINT pCenter,
                               L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnRemove (HANNOBJECT hObject);
L_INT EXT_FUNCTION L_AnnRotate(HANNOBJECT hObject,
                               L_DOUBLE dAngle,
                               pANNPOINT pCenter,
                               L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSave (L_TCHAR L_FAR * pFile,
                               HANNOBJECT hObject,
                               L_UINT uFormat,
                               L_BOOL fSelected,
                               pSAVEFILEOPTION pSaveOptions);
L_INT EXT_FUNCTION L_AnnSaveOffset (L_INT fd,
                               L_INT32 nOffset,
                               L_UINT32 L_FAR *puSizeWritten,
                               HANNOBJECT hObject,
                               L_UINT uFormat,
                               L_BOOL fSelected,
                               pSAVEFILEOPTION pSaveOptions);
L_INT EXT_FUNCTION L_AnnSaveMemory (HANNOBJECT hObject,
                               L_UINT uFormat,
                               L_BOOL fSelected,
                               HGLOBAL L_FAR *phMem,
                               L_UINT32 L_FAR * puMemSize,
                               pSAVEFILEOPTION pSaveOptions);
L_INT EXT_FUNCTION L_AnnSaveTag(HANNOBJECT hObject,
                               L_UINT uFormat,
                               L_BOOL fSelected);
L_INT EXT_FUNCTION L_AnnSelectPoint(HANNOBJECT hObject,
                                     LPPOINT pPoint);
L_INT EXT_FUNCTION L_AnnSelectRect(HANNOBJECT hObject,
                                     LPRECT pRect);
L_INT EXT_FUNCTION L_AnnSendToBack (HANNOBJECT hObject);

L_INT EXT_FUNCTION L_AnnSetActiveState (HANNOBJECT hObject,
                                         L_UINT uState);
L_INT EXT_FUNCTION L_AnnSetAutoContainer (HANNOBJECT hObject,
                                          HANNOBJECT hContainer);
L_INT EXT_FUNCTION L_AnnSetAutoDrawEnable (HANNOBJECT hObject,
                                          L_BOOL fEnable);
L_INT EXT_FUNCTION L_AnnSetAutoMenuEnable (HANNOBJECT hObject,
                                          L_BOOL fEnable);
L_INT EXT_FUNCTION L_AnnSetAutoText (HANNOBJECT hObject,
                                     L_UINT uItem,
                                     L_TCHAR L_FAR *pText);
L_INT EXT_FUNCTION L_AnnSetBackColor (HANNOBJECT hObject,
                                       COLORREF crBack,
                                       L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetBitmap (HANNOBJECT hObject,
                                    pBITMAPHANDLE pBitmap,
                                    L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetBitmapDpiX(HANNOBJECT hObject,
                                      L_DOUBLE  dDpiX,
                                      L_UINT    uFlags);
L_INT EXT_FUNCTION L_AnnSetBitmapDpiY(HANNOBJECT hObject,
                                      L_DOUBLE  dDpiY,
                                      L_UINT    uFlags);
L_INT EXT_FUNCTION L_AnnSetDpiX(HANNOBJECT hObject,
                                 L_DOUBLE dDpiX,
                                 L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetDpiY(HANNOBJECT hObject,
                                 L_DOUBLE dDpiY,
                                 L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetFillMode (HANNOBJECT hObject,
                                      L_UINT uFillMode,
                                      L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetFillPattern (HANNOBJECT hObject,
                                         L_UINT uFillPattern,
                                         L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetFontBold (HANNOBJECT hObject,
                                      L_BOOL fFontBold,
                                      L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetFontItalic (HANNOBJECT hObject,
                                        L_BOOL fFontItalic,
                                        L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetFontName (HANNOBJECT hObject,
                                      L_TCHAR L_FAR * pFontName,
                                      L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetFontSize (HANNOBJECT hObject,
                                      L_DOUBLE dFontSize,
                                      L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetFontStrikeThrough (HANNOBJECT hObject,
                                               L_BOOL fFontStrikeThrough,
                                               L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetFontUnderline (HANNOBJECT hObject,
                                           L_BOOL fFontUnderline,
                                           L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetForeColor (HANNOBJECT hObject,
                                       COLORREF crFore,
                                       L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetGaugeLength(HANNOBJECT hObject,
                                       L_DOUBLE dLength,
                                       L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetHyperlink (HANNOBJECT hObject,
                                       L_UINT uType,
                                       L_UINT uMsg,
                                       WPARAM wParam,
                                       L_TCHAR L_FAR*pLink,
                                       L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetHyperlinkMenuEnable(HANNOBJECT hObject,
                            L_BOOL fEnable,
                            L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetLineStyle (HANNOBJECT hObject,
                                       L_UINT uLineStyle,
                                       L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetLineWidth (HANNOBJECT hObject,
                                       L_DOUBLE dLineWidth,
                                       L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetOffsetX(HANNOBJECT hObject,
                                  L_DOUBLE dOffsetX,
                                  L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetOffsetY(HANNOBJECT hObject,
                                  L_DOUBLE dOffsetY,
                                  L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetPoints (HANNOBJECT hObject,
                                    pANNPOINT pPoints,
                                    L_UINT uCount);
L_INT EXT_FUNCTION L_AnnSetPolyFillMode (HANNOBJECT hObject,
                                      L_UINT uPolyFillMode,
                                      L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetROP2 (HANNOBJECT hObject,
                                      L_UINT uROP2,
                                      L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetRect (HANNOBJECT hObject,
                                  pANNRECT pRect);
L_INT EXT_FUNCTION L_AnnSetSelected (HANNOBJECT hObject,
                                      L_BOOL fSelected,
                                      L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetScalarX(HANNOBJECT hObject,
                                 L_DOUBLE dScalarX,
                                 L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetScalarY(HANNOBJECT hObject,
                                 L_DOUBLE dScalarY,
                                 L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetTag (HANNOBJECT hObject,
                                 L_UINT32 uTag,
                                 L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetText (HANNOBJECT hObject,
                                  L_TCHAR L_FAR * pText,
                                  L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetTool (HANNOBJECT hObject,
                                 L_UINT uTool);
L_INT EXT_FUNCTION L_AnnSetToolBarButtonVisible(HWND hwndToolBar,
                                  L_UINT uButton,
                                  L_BOOL fVisible);
L_INT EXT_FUNCTION L_AnnSetToolBarChecked(HWND hwndToolBar,
                                  L_UINT uChecked);
L_INT EXT_FUNCTION L_AnnSetTransparent (HANNOBJECT hObject,
                                      L_BOOL bTransparent,
                                      L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetUndoDepth (HANNOBJECT hObject,
                                      L_UINT uLevels);
L_INT EXT_FUNCTION L_AnnSetUnit(HANNOBJECT hObject,
                                L_UINT uUnit,
                                L_TCHAR L_FAR* pUnitAbbrev,
                                L_UINT uPrecision,
                                L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnSetUserMode (HANNOBJECT hObject,
                                      L_UINT uMode);
L_INT EXT_FUNCTION L_AnnSetVisible (HANNOBJECT hObject,
                                     L_BOOL fVisible,
                                     L_UINT uFlags,
                                     L_TCHAR L_FAR*pUserList);
L_INT EXT_FUNCTION L_AnnSetWnd (HANNOBJECT hObject,
                                 HWND hWnd);
L_INT EXT_FUNCTION L_AnnShowLockedIcon (HANNOBJECT hObject,
                                     L_BOOL bShow,
                                     L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnUndo (HANNOBJECT hObject);
L_INT EXT_FUNCTION L_AnnUnlock (HANNOBJECT hObject, 
                              L_TCHAR L_FAR* pUnlockKey, 
                              L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnUnrealize(pBITMAPHANDLE pBitmap, 
                                LPRECT prcBounds, 
                                HANNOBJECT hObject, 
                                L_BOOL fSelected);



L_INT EXT_FUNCTION L_AnnSetNodes(HANNOBJECT hObject, 
                                 L_BOOL bShowNodes, 
                                 L_UINT uGapNodes, 
                                 L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnGetNodes(HANNOBJECT hObject, 
                                 L_BOOL L_FAR*pbShowNodes, 
                                 L_UINT L_FAR*puGapNodes);
L_INT EXT_FUNCTION L_AnnSetProtractorOptions(HANNOBJECT hObject, 
                                        L_BOOL  bAcute,
                                        L_UINT  uUnit,
                                        L_TCHAR L_FAR*pszAbbrev,
                                        L_UINT  uPrecision,
                                        L_DOUBLE dArcRadius,
                                        L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnGetProtractorOptions(HANNOBJECT hObject,
                                        L_BOOL  L_FAR*pbAcute,
                                        L_UINT  L_FAR*puUnit,
                                        L_UINT L_FAR*puAbbrevLen,
                                        L_TCHAR L_FAR*pszAbbrev,
                                        L_UINT  L_FAR*puPrecision,
                                        L_DOUBLE L_FAR*pdArcRadius);
L_INT EXT_FUNCTION L_AnnSetName (HANNOBJECT    hObject, 
                                 L_BOOL        bShowName, 
                                 L_TCHAR L_FAR *pText,
                                 pANNPOINT     pNameOffset,
                                 L_BOOL        bNameRestrict,
                                 L_UINT        uFlags);

/*
L_INT EXT_FUNCTION L_AnnSetNameAutoAdjust(HANNOBJECT hObject, 
                                          L_BOOL bAutoAdjust, 
                                          L_UINT uFlags);

L_INT EXT_FUNCTION L_AnnSetNameOffset(HANNOBJECT hObject, 
                                      pANNPOINT pNameOffset, 
                                      L_UINT uFlags);
                                      */

L_INT EXT_FUNCTION L_AnnGetName (HANNOBJECT     hObject, 
                                 L_BOOL L_FAR  *pbShowName, 
                                 L_UINT L_FAR  *puNameLen, 
                                 L_TCHAR L_FAR  *pName,
                                    pANNPOINT      pNameOffset,
                                    L_BOOL L_FAR  *pbNameRestrict);


//L_INT EXT_FUNCTION L_AnnGetNameOffset(HANNOBJECT hObject, pANNPOINT pAnnPointOffset);

L_INT EXT_FUNCTION L_AnnSetShowFlags (HANNOBJECT hObject,
                                       L_UINT uShowFlags,
                                       L_UINT uFlags);
L_INT EXT_FUNCTION L_AnnGetShowFlags (HANNOBJECT hObject,
                                       L_UINT L_FAR*puShowFlags);

L_INT EXT_FUNCTION L_AnnGetAngle(HANNOBJECT hObject,
                                 L_DOUBLE L_FAR*pdAngle);

/* newest functions */

L_INT EXT_FUNCTION L_AnnSetMetafile (HANNOBJECT hObject, 
                                     HMETAFILE hMetafile, 
                                     L_UINT uType, 
                                     L_UINT uFlags);

L_INT EXT_FUNCTION L_AnnGetMetafile (HANNOBJECT hObject, 
                                     HMETAFILE L_FAR*phMetafile);

L_INT EXT_FUNCTION L_AnnSetPredefinedMetafile(L_UINT uType, 
                                              HMETAFILE hMetafile);

L_INT EXT_FUNCTION L_AnnGetPredefinedMetafile(L_UINT uType, 
                                              HMETAFILE L_FAR*phMetafile,
                                              L_BOOL L_FAR*pbEnhanced);

L_INT EXT_FUNCTION L_AnnSetSecondaryBitmap (HANNOBJECT hObject, 
                                            pBITMAPHANDLE pBitmap, 
                                            L_UINT uFlags);

L_INT EXT_FUNCTION L_AnnGetSecondaryBitmap (HANNOBJECT hObject, 
                                            pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_AnnSetAutoMenuItemEnable(HANNOBJECT hObject, 
                                              L_INT nObjectType, 
                                              L_UINT uItem, 
                                              L_UINT uEnable, 
                                              L_UINT uFlags,
                                              L_TCHAR L_FAR*pUserList);

L_INT EXT_FUNCTION L_AnnGetAutoMenuItemEnable(HANNOBJECT hObject, 
                                              L_INT nObjectType, 
                                              L_UINT uItem, 
                                              L_UINT L_FAR*puEnable);

L_INT EXT_FUNCTION L_AnnSetAutoMenuState(HANNOBJECT hObject, 
                                         L_INT nObjectType, 
                                         L_UCHAR L_FAR*pEnable, 
                                         L_UCHAR L_FAR*pEnableFlags, 
                                         L_UINT uBits, 
                                         L_UINT uFlags);

L_INT EXT_FUNCTION L_AnnGetAutoMenuState(HANNOBJECT hObject, 
                                         L_INT nObjectType, 
                                         L_UCHAR L_FAR*pEnable, 
                                         L_UCHAR L_FAR*pEnableFlags, 
                                         L_UINT uBits);

L_INT EXT_FUNCTION L_AnnSetUser(HANNOBJECT hObject, 
                                L_TCHAR L_FAR*pOldUser, 
                                L_TCHAR L_FAR*pNewUser, 
                                L_UINT uFlags);

L_INT EXT_FUNCTION L_AnnSetToolBarButtons(HWND hwndToolBar,
                                          pANNBUTTON pButtons,
                                          L_UINT uButtons);

L_INT EXT_FUNCTION L_AnnGetToolBarButtons(HWND hwndToolBar,
                                          pANNBUTTON pButtons,
                                          L_UINT L_FAR*puButtons);

L_INT EXT_FUNCTION L_AnnFreeToolBarButtons(pANNBUTTON pButtons,
                                           L_UINT uButtons);

L_INT EXT_FUNCTION L_AnnGetToolBarInfo(HWND hwndToolBar,
                                       pANNTOOLBARINFO pInfo);

L_INT EXT_FUNCTION L_AnnSetToolBarColumns(HWND hwndToolBar,
                                          L_UINT uColumns);

L_INT EXT_FUNCTION L_AnnSetToolBarRows(HWND hwndToolBar,
                                          L_UINT uColumns);

L_INT EXT_FUNCTION L_AnnSetAutoDefaults(HANNOBJECT hAutomation, 
                                        HANNOBJECT hObject, 
                                        L_UINT uFlags);

L_INT EXT_FUNCTION L_AnnSetTransparentColor (HANNOBJECT hObject, 
                                             COLORREF crTransparent, 
                                             L_UINT uFlags);

L_INT EXT_FUNCTION L_AnnGetTransparentColor (HANNOBJECT hObject, 
                                             COLORREF L_FAR * pcrTransparent);

L_INT EXT_FUNCTION L_AnnGetUndoDepth (HANNOBJECT hObject,
                                      L_UINT L_FAR*puUsedLevels,
                                      L_UINT L_FAR*puMaxLevels);

L_INT EXT_FUNCTION L_AnnGroup (HANNOBJECT hObject, 
                               L_UINT uFlags, 
                               L_TCHAR L_FAR*pUserList);

L_INT EXT_FUNCTION L_AnnUngroup (HANNOBJECT hObject, 
                               L_UINT uFlags, 
                               L_TCHAR L_FAR*pUserList);

#ifdef WIN32
L_INT EXT_FUNCTION L_AnnSetAutoOptions (HANNOBJECT hObject,
                                        L_UINT uFlags);

L_INT EXT_FUNCTION L_AnnGetAutoOptions (HANNOBJECT hObject,
                                        L_UINT L_FAR *puFlags);
#endif

L_INT EXT_FUNCTION L_AnnGetObjectFromTag (HANNOBJECT hContainer,
                                          L_UINT uFlags,
                                          L_UINT32 uTag,
                                          pHANNOBJECT phTagObject);

L_INT EXT_FUNCTION L_AnnGetRgnHandle(HANNOBJECT hObject,
                                    pRGNXFORM pXForm,
                                    HRGN L_FAR *phRgn);

L_INT EXT_FUNCTION L_AnnGetArea(HANNOBJECT hObject, 
                                L_UINT32 L_FAR*puCount);

L_INT EXT_FUNCTION L_AnnSetAutoDialogFontSize(HANNOBJECT hObject,
                                        L_INT   nFontSize);

L_INT EXT_FUNCTION L_AnnGetAutoDialogFontSize(HANNOBJECT hObject,
                                        L_INT L_FAR* pnFontSize);

L_INT EXT_FUNCTION L_AnnSetGrouping(HANNOBJECT hObject,
                                    L_BOOL bAutoGroup,
                                    L_UINT uFlags);

L_INT EXT_FUNCTION L_AnnGetGrouping(HANNOBJECT hObject,
                                    L_BOOL L_FAR* pbAutoGroup);

L_INT EXT_FUNCTION L_AnnSetAutoBackColor(HANNOBJECT hObject,
                                         L_UINT uObjectType,
                                         COLORREF crBack);

L_INT EXT_FUNCTION L_AnnGetAutoBackColor(HANNOBJECT hObject,
                                         L_UINT uObjectType,
                                         COLORREF L_FAR*pcrBack);

L_INT EXT_FUNCTION L_AnnAddUndoNode(HANNOBJECT hObject);

L_INT EXT_FUNCTION L_AnnSetAutoUndoEnable(HANNOBJECT hObject,
                                          L_BOOL      bEnable);

L_INT EXT_FUNCTION L_AnnGetAutoUndoEnable(HANNOBJECT hObject,
                                          L_BOOL L_FAR*pbEnable);

L_INT EXT_FUNCTION L_AnnSetToolBarParent(HWND hwndToolBar, HWND hwndParent);

#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif                          /* _LTANN_H_ */
