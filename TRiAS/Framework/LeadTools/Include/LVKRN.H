
/*
   LVKRN.H - LEAD Vector Dialog module header file
   Copyright (c) 1991-2000 LEAD Technologies, Inc.
   All Rights Reserved.
*/


#ifndef _LVKRN_H_
#define _LVKRN_H_


#include "lttyp.h"
#include "lterr.h"


#define _HEADER_ENTRY_
#include "ltpck.h"


/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Definitions.                                                         []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/


// View mode.
#define VECTOR_VIEWMODE_FIT                  (0)
#define VECTOR_VIEWMODE_SNAP                 (1)


// Vertices bind mode.
#define VECTOR_BIND_VERTICES                 (0)         // Bind vertices.
#define VECTOR_UNBIND_VERTICES               (1)         // Unbind vertices.


// Render engines.
#define VECTOR_ENGINE_GDI                    (0)         // GDI engine.
#define VECTOR_ENGINE_OPENGL                 (1)         // OpenGL engine.
#define VECTOR_ENGINE_DIRECTX                (2)         // DirectX engine.

// Engine flags.
#define VECTOR_ENGINE_DOUBLEBUFFER           (1)         // User double buffering.


#define VECTOR_MAX_NAME                      (41)        // Maximum size of a name string buffer.

#define VECTOR_PAINT_ERASEBKGND              (1)         // Paint flags

#define VECTOR_OBJECT_SELECTED               (1)
#define VECTOR_OBJECT_HIDDEN                 (2)
#define VECTOR_OBJECT_COMPOSITE              (4)
#define VECTOR_OBJECT_2STAGE_RENDERING       (8)         // This flag applies only to VECTORCIRCLE, VECTORELLIPSE,
                                                         // VECTORPIE, VECTORTEXT and VECTORPOLYDRAW
#define VECTOR_OBJECT_CLIP                   (16)        

// Polydraw flags 
#define VECTOR_POLYDRAW_FILL_WINDING          (0)
#define VECTOR_POLYDRAW_FILL_ALTERNATE        (32)



// Object types.
#define VECTOR_OBJECT                        (0)
#define VECTOR_VERTEX                        (1)         // 3D vertex in space.
#define VECTOR_LINE                          (2)         // Line.
#define VECTOR_RECTANGLE                     (3)         // Rectnagle.
#define VECTOR_POLYLINE                      (4)         // Polyline.
#define VECTOR_POLYBEZIER                    (5)         // Poly Bezier curve
#define VECTOR_POLYGON                       (6)         // Multi-sided polygon.
#define VECTOR_ELLIPSE                       (7)         // Ellipse.
#define VECTOR_CIRCLE                        (8)         // Circle.
#define VECTOR_ARC                           (9)         // Arc.
#define VECTOR_ELLIPTICALARC                 (10)        // Elliptical arc.
#define VECTOR_PIE                           (11)        // Pie.
#define VECTOR_CHORD                         (12)        // Chord.
#define VECTOR_POLYDRAW                      (13)        // Polydraw.
#define VECTOR_TEXT                          (14)        // Text.
#define VECTOR_RASTER                        (15)        // Raster.
#define VECTOR_STOCK                         (16)        // Stock object from a library.
#define VECTOR_CLONE                         (17)        // Group clone.


// Copy operation flags.
#define VECTOR_FLAGS_SELECTED_ONLY           (1)
#define VECTOR_FLAGS_REPLACE                 (2)
#define VECTOR_FLAGS_RENAME_DUPLICATES       (4)
#define VECTOR_FLAGS_COPY_INTO_ACTIVE_LAYER  (64)
#define VECTOR_FLAGS_COPY_LAYERS_ONLY        (128)
#define VECTOR_FLAGS_ADD_UNDO_NODE           (256)
#define VECTOR_FLAGS_TRANSFORMED             (512)
#define VECTOR_FLAGS_EXPLODE_TO_LINES        (1024)


// Polygon settongs flags.
#define VECTOR_POLYGON_POINT                 (0)         // Draw as points..
#define VECTOR_POLYGON_LINE                  (1)         // Draw as wifeframe.
#define VECTOR_POLYGON_FILL                  (2)         // Draw solid polygons.
#define VECTOR_POLYGON_FILL_RASTER_ALWAYS    (3)         // Solid polygons and always draw raster objects.


// Hit test options
#define VECTOR_HITTEST_CLOSEDFIGURES         (1)         // Check if hit test point is inside closed objects.
#define VECTOR_HITTEST_IGNORESELECTED        (2)         // Dont check for objects that are already selected.


// Marker options
#define VECTOR_MARKER_PEN_STYLE              (1)
#define VECTOR_MARKER_PEN_WIDTH              (2)
#define VECTOR_MARKER_PEN_COLOR              (4)
#define VECTOR_MARKER_BRUSH_STYLE            (8)
#define VECTOR_MARKER_BRUSH_COLOR            (16)


// Vector polygon fill modes
#define VECTOR_POLY_ALTERNATE                (ALTERNATE)
#define VECTOR_POLY_WINDING                  (WINDING)


// Text flags
#define VECTOR_TEXT_LEFT                     (0)
#define VECTOR_TEXT_RIGHT                    (1)
#define VECTOR_TEXT_HCENTER                  (2)
#define VECTOR_TEXT_TOP                      (0)
#define VECTOR_TEXT_BOTTOM                   (4)
#define VECTOR_TEXT_VCENTER                  (8)
#define VECTOR_TEXT_HITTESTRECT              (16)
#define VECTOR_TEXT_FORCECURVERENDERING      (32)


// Polydraw types
#define VECTOR_PT_CLOSEFIGURE                (PT_CLOSEFIGURE)
#define VECTOR_PT_LINETO                     (PT_LINETO)
#define VECTOR_PT_BEZIERTO                   (PT_BEZIERTO)
#define VECTOR_PT_MOVETO                     (PT_MOVETO)

// Maximum object size.
#define VECTOR_OBJECT_BUFFER_SIZE            (sizeof(VECTORRASTER))

// Clone flags
#define VECTOR_CLONE_USE_PEN                    (1)
#define VECTOR_CLONE_USE_BRUSH                  (2)
#define VECTOR_CLONE_USE_POINT_AS_ORIGIN        (4)
#define VECTOR_CLONE_USE_CHILDCLONE_ATTRIBUTES  (8)

// Clipping modes
#define VECTOR_CLIPMODE_COPY                 (RGN_COPY)
#define VECTOR_CLIPMODE_AND                  (RGN_AND)
#define VECTOR_CLIPMODE_DIFF                 (RGN_DIFF)
#define VECTOR_CLIPMODE_OR                   (RGN_OR)
#define VECTOR_CLIPMODE_XOR                  (RGN_XOR)

// Events
typedef enum
{
   VECTOR_EVENT_USER = 0,
   VECTOR_EVENT_RESERVED = 10000,

   VECTOR_EVENT_FREE,
   VECTOR_EVENT_EMPTY,
   VECTOR_EVENT_COPY,
   VECTOR_EVENT_VIEWPORT,
   VECTOR_EVENT_PAN,
   VECTOR_EVENT_LOCKED,
   VECTOR_EVENT_BACKGROUND,
   VECTOR_EVENT_PALETTE,
   VECTOR_EVENT_VIEWMODE,

   VECTOR_EVENT_TRANSLATION,
   VECTOR_EVENT_ROTATION,
   VECTOR_EVENT_SCALE,
   VECTOR_EVENT_ORIGIN,
   VECTOR_EVENT_APPLYTRANSFORMATION,
   VECTOR_EVENT_ZOOMRECT,

   VECTOR_EVENT_BINDVERTICESMODE,
   VECTOR_EVENT_PARALLELOGRAM,

   VECTOR_EVENT_CAMERA,

   VECTOR_EVENT_METAFILE,

   VECTOR_EVENT_ATTACHTOWINDOW,

   VECTOR_EVENT_MARKER,

   VECTOR_EVENT_UNIT,         /* Reserved for internal use */

   VECTOR_EVENT_HITTEST,

   VECTOR_EVENT_POLYGONMODE,
   VECTOR_EVENT_USELIGHTS,
   VECTOR_EVENT_AMBIENTCOLOR,

   VECTOR_EVENT_COPYFROMCLIPBOARD,

   VECTOR_EVENT_ADDLAYER,
   VECTOR_EVENT_DELETELAYER,
   VECTOR_EVENT_EMPTYLAYER,
   VECTOR_EVENT_COPYLAYER,
   VECTOR_EVENT_SETLAYER,
   VECTOR_EVENT_SETACTIVELAYER,

   VECTOR_EVENT_ADDGROUP,
   VECTOR_EVENT_DELETEGROUP,
   VECTOR_EVENT_DELETEGROUPCLONES,
   VECTOR_EVENT_EMPTYGROUP,
   VECTOR_EVENT_COPYGROUP,
   VECTOR_EVENT_SETGROUP,

   VECTOR_EVENT_ADDOBJECT,
   VECTOR_EVENT_DELETEOBJECT,
   VECTOR_EVENT_COPYOBJECT,
   VECTOR_EVENT_SETOBJECT,
   VECTOR_EVENT_EXPLODEOBJECT,
   VECTOR_EVENT_SELECTOBJECT,
   VECTOR_EVENT_HIDEOBJECT,
   VECTOR_EVENT_OBJECTATTRIBUTES,
   VECTOR_EVENT_ADDOBJECTTOGROUP,

   VECTOR_EVENT_DUMPLOADVECTOR,

   VECTOR_EVENT_LOADFILE, 

   VECTOR_EVENT_CREATENEWWINDOW,

   VECTOR_EVENT_INVERTCOLORS
}
VECTOR_EVENT, *pVECTOR_EVENT;


// Event status
typedef enum
{
   VECTOR_EVENT_STATUS_BEFORE,
   VECTOR_EVENT_STATUS_AFTER
}
VECTOR_EVENT_STATUS, *pVECTOR_EVENT_STATUS;

/* Reserved for internal use */
// Units
typedef enum
{
   VECTOR_UNIT_INCHES,
   VECTOR_UNIT_FEET,
   VECTOR_UNIT_YARDS,
   VECTOR_UNIT_MILES,
   VECTOR_UNIT_MICROMETERS,
   VECTOR_UNIT_MILIMETERS,
   VECTOR_UNIT_CENTIMETERS,
   VECTOR_UNIT_METERS,
   VECTOR_UNIT_KILOMETERS,
   VECTOR_UNIT_TWIPS,
   VECTOR_UNIT_POINTS,
   VECTOR_UNIT_PIXELS,
   VECTOR_UNIT_DUMMY = -1
}
VECTOR_UNIT;


/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Data structures.                                                     []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/

// VECTORARRAY: Generic array.
typedef struct _VECTORARRAY
{
   L_INT                   nSize;                     // Size of this structure. Used for versioning.
   L_INT                   nCount;                    // Number of elements in the array (Including deleted items).
   L_INT                   nActualCount;              // Number of elements in the array (Not including deleted items).
   L_UINT                  uTotalCount;               // Total items count (actual + free).
   L_INT                   nLastDeletedItem;          // Last deleted item.
   L_UINT32                dwDeleted;                 // Deleted item signature.
   L_UINT                  uMaxItemSize;              // Maximum item size in bytes. The array can have different items, this holds the size of the maximum one.
   L_UINT                  uIncCount;                 // Increment count. Number of items to be allocated when the array is filled and a new item is to be added.
   L_CHAR L_FAR           *pBuffer;                   // Memory buffer for holding actual array items.
}
VECTORARRAY, L_FAR *pVECTORARRAY;


// VECTORPOINT: Holds a 3D point in space.
typedef struct _VECTORPOINT
{
   L_DOUBLE                x;                         // x-component.
   L_DOUBLE                y;                         // y-component.
   L_DOUBLE                z;                         // z-component.
   L_INT32                 lTag;                      // User-defined data.
}
VECTORPOINT, L_FAR *pVECTORPOINT;

// Text rendering options.
typedef enum _VECTOR_TEXTRENDER
{
   VECTOR_TEXTRENDER_ASTEXT = 0,                      // try always to render the text as text object 
   VECTOR_TEXTRENDER_ASCURVES                         // render the text always as curves and lines 

}VECTOR_TEXTRENDER, *pVECTOR_TEXTRENDER;

// Anti-aliasing.
typedef struct _VECTOR_ANTIALIASING
{
   L_UINT   uThreshold;                              // which pixels to smooth, pixels with value above this is smoothed
                                                     // set to zero to prevent Anti-aliasing.
   L_UINT   uDim;                                    // dimension of the anti-aliasing mask ... 3 means 3X3
   L_UINT   uFilter;                                 // type of anti-aliasing ... see L_AntiAliasBitmap for values.

}VECTOR_ANTIALIASING, *pVECTOR_ANTIALIASING;

// VECTOR Display options.
typedef struct _VECTOR_DISPLAY_OPTIONS
{
   VECTOR_TEXTRENDER   TextRender;                  // text rendering options.
   VECTOR_ANTIALIASING AntiAliasing;                // anti-aliasing settings
   L_INT               nClipMode;                   // Clipping mode.
   
   L_DOUBLE            dwReserved;                  // must be zero. 

}VECTOR_DISPLAY_OPTIONS, *pVECTOR_DISPLAY_OPTIONS;


// VECTORPEN: Pen.
typedef struct _VECTORPEN
{
   L_INT                   nSize;                     // Size of this structure. Used for versioning.
   LOGPEN                  LogPen;                    // Windows LOGPEN structure defining the pen properties.
}
VECTORPEN, L_FAR *pVECTORPEN;


// VECTORBRUSH: Brush.
typedef struct _VECTORBRUSH
{
   L_INT                   nSize;                     // Size of this structure. Used for versioning.
   LOGBRUSH                LogBrush;                  // Windows LOGBRUSH structure defining the brush properties.
}
VECTORBRUSH, L_FAR *pVECTORBRUSH;


// VECTORFONT: Font.
typedef struct _VECTORFONT
{
   L_INT                   nSize;                     // Size of this structure. Used for versioning.
   LOGFONT                 LogFont;                   // Windows LOGFONT structure defining the font properties.
}
VECTORFONT, L_FAR *pVECTORFONT;


// VECTORBITMAP
typedef struct _VECTORBITMAP
{
   L_INT                   nSize;                     // Size of this structure. Used for versioning.
   BITMAPHANDLE            Bitmap;                    // LEAD bitmap handle.
}
VECTORBITMAP, L_FAR *pVECTORBITMAP;


// VECTORATTRIBUTES: Stors objects, points, pens, brushes, fonts and bitmap in one location.
typedef struct _VECTORATTRIBUTES
{
   L_INT                   nSize;                     // Size of this structure. Used for versioning.
   VECTORPOINT             Min;                       // Mimimum point.
   VECTORPOINT             Max;                       // Maximum point.
   VECTORPOINT             Origin;                    // Origin of current points.
   VECTORARRAY             aPoints;                   // Array of VECTORPOINT's.
   VECTORARRAY             aPens;                     // Array of VECTORPEN's.
   VECTORARRAY             aBrushes;                  // Array of VECTORBRUSH's.
   VECTORARRAY             aFonts;                    // Array of VECTORFONT's.
   VECTORARRAY             aBitmaps;                  // Array of VECTORBITMAP's.
}
VECTORATTRIBUTES, L_FAR *pVECTORATTRIBUTES;


// VECTORTRANSFORMATION: A place to hold all transformation variables.
typedef struct _VECTORTRANSFORMATION
{
   L_INT                   nSize;                     // Size of this structure. Used for versioning.
   VECTORPOINT             Scale;                     // Scale factors. 1.0 = 100%.
   VECTORPOINT             Rotation;                  // Rotation angles. x, y and z represent the rotation angles around the axes in degrees.
   VECTORPOINT             Translation;               // Translation values. x, y and z represent the translation values along the axes in logical units.
}
VECTORTRANSFORMATION, L_FAR *pVECTORTRANSFORMATION;


// VECTORCAMERA: Holds all data needed for a 3D-camera object.
typedef struct _VECTORCAMERA
{
   L_INT                   nSize;                     // Size of this structure. Used for versioning.
   L_DOUBLE                Theta;                     // Rotation angle around the Z-axis.
   L_DOUBLE                Phi;                       // Rotation angle off the Z-axis.
   VECTORPOINT             LookAt;                    // Look at.
   L_DOUBLE                Distance;                  // Distance.
   L_BOOL                  bPerspective;              // Use perspective projection?
}
VECTORCAMERA, L_FAR *pVECTORCAMERA;


// VECTORMARKER: Holds all data needed for a marker.
typedef struct _VECTORMARKER
{
   L_INT                   nSize;                     // Size of this structure. Used for versioning.
   L_UINT32                dwFlags;
   VECTORPEN               Pen;
   VECTORBRUSH             Brush;
}
VECTORMARKER, L_FAR *pVECTORMARKER;


/* Reserved for internal use */
// VECTORUNIT
typedef struct _VECTORUNIT
{
   L_INT                   nSize;                     // Size of this structure. Used for versioning.
   VECTOR_UNIT             Unit;                      // One of the VECTOR_UNIT_XXX types
   L_DOUBLE                Value;                     // Value for 1 point.
   L_CHAR                  szAbbrev[ VECTOR_MAX_NAME ];  // Abbreviation text
   L_UINT                  uPrecision;                // Flotaing point precision
}
VECTORUNIT, *pVECTORUNIT;


// VECTORHITTEST: Holds all vector test settings.
typedef struct _VECTORHITTEST
{
   L_INT                   nSize;                     // Size of this structure. Used for versioning.
   L_INT                   nDistance;                 // Distance from left and right of point in pixels.
   L_UINT32                dwFlags;                   // Flags, see VECTOR_HITTEST_XXX
}
VECTORHITTEST, L_FAR *pVECTORHITTEST;


// VECTORLAYER: Defines a layer.
typedef struct _VECTORLAYER
{
   L_INT                   nSize;                     // Size of this structure. Used for versioning.
   L_INT                   nId;                       // Layer Id.
}
VECTORLAYER, L_FAR *pVECTORLAYER;


// VECTORLAYERDESC:
typedef struct _VECTORLAYERDESC
{
   L_INT                   nSize;                     // Size of this structure. Used for versioning.
   L_CHAR                  szName[ VECTOR_MAX_NAME ]; // Layer name.
   L_BOOL                  bVisible;                  // Visibility.
   L_BOOL                  bLocked;                   // Locked.
   L_UINT32                dwTag;                     // User-defined tag.
}
VECTORLAYERDESC, L_FAR *pVECTORLAYERDESC;


// VECTORGROUP: Defines a group
typedef struct _VECTORGROUP
{
   L_INT                   nSize;                     // Size of this structure. Used for versioning.
   L_INT                   nId;                       // Group Id.
}
VECTORGROUP, *pVECTORGROUP;


// VECTORGROUPDESC:
typedef struct _VECTORGROUPDESC
{
   L_INT                   nSize;                     // Size of this structure. Used for versioning.
   L_CHAR                  szName[ VECTOR_MAX_NAME ]; // Group name.
   L_UINT32                dwTag;                     // User-defined tag.
}
VECTORGROUPDESC, *pVECTORGROUPDESC;



// VECTOROBJECT: Defines a single vector object.
typedef struct _VECTOROBJECT
{
   L_INT                   nSize;                     // Size of this structure. Used for versioning.
   L_INT                   nType;                     // Type of this object.
   L_INT                   nId;                       // Object ID.
   L_INT                   nLayerId;                  // Layer ID.
   L_INT                   nGroupId;                  // Group ID.
   L_INT                   nROP;                      // Object's ROP mode.
   L_BOOL                  dwFlags;                   // Flags
   DWORD                   dwTag;                     // User-defined tag.   
}
VECTOROBJECT, L_FAR *pVECTOROBJECT;

// VECTORTOOLTIPDESC: specifys how the toolkit should display a tooltip 
typedef struct _VECTORTOOLTIPDESC
{
   POINT        Point;
   LOGPEN       Pen;
   LOGBRUSH     Brush;
   LOGFONT      Font;

}VECTORTOOLTIPDESC, *pVECTORTOOLTIPDESC;

// VECTORTOOLTIPDESC: specifys how the toolkit should handle a click on a link-object.
typedef enum _VECTORLINKHANDLING
{
   VECTORLINKHANDLING_CURRENTWINDOW = 0,          // open in new window
   VECTORLINKHANDLING_NEWWINDOW                   // open in the current window

}VECTORLINKHANDLING, *pVECTORLINKHANDLING;

// VECTORLINKFILEINFO: specifys the target file of an object with a hyperlink
typedef struct _VECTORLINKFILEINFO
{
   L_CHAR szPath[ L_MAXPATH ];                    // path to the file
   
}VECTORLINKFILEINFO, *pVECTORLINKFILEINFO;

// VECTORLINKDESC: specifys the target of a hyperlink
typedef struct _VECTORLINKDESC
{
   L_BOOL bObject;                               // TRUE means the link points to a vector object 

   union
   {
      struct 
      {
         VECTOROBJECT       target;               // the target object if bObject is TRUE
         VECTORLINKHANDLING handling;             // specifys how the toolkit will handle link activation         

      }vectorobject;

      struct 
      {
         VECTORLINKFILEINFO target;               // information about the target file if bObject is FALSE
         HWND hwndParent;                         // Parent window if ( handling ) is VECTORLINKHANDLING_NEWWINDOW or if target is a file

      }fileobject;

   }tar;

}VECTORLINKDESC, *pVECTORLINKDESC;

// VECTOREVENT
typedef struct _VECTOREVENT
{
   L_INT                   nSize;                     // Size of this structure. Used for versioning.
   L_UINT                  uType;                     // Event type (One of VECTOR_EVENT_XXX)
   VECTOR_EVENT_STATUS     Status;                    // Status (before or after)
   L_INT                   nErrorCode;                // One of the Error Codes.
   pVECTOROBJECT           pObject;                   // The vector object
   L_VOID L_FAR           *pObjectDesc;               // Object descriptor.
   pVECTORLAYER            pLayer;                    // The vector layer.
   pVECTORLAYERDESC        pLayerDesc;                // Layer descriptor
   pVECTORGROUP            pGroup;                    // The vector group.
   pVECTORGROUPDESC        pGroupDesc;                // Group descriptor.
   pVECTORPOINT            pPoint1;                   // General point 1
   pVECTORPOINT            pPoint2;                   // General point 2
   L_UINT32                dwFlags;                   // Flags
   L_VOID L_FAR           *pUserData;                 // User data.
}
VECTOREVENT, L_FAR *pVECTOREVENT;


#ifndef FOR_LINUX
   typedef struct _VECTORHANDLE *pVECTORHANDLE;
   typedef L_INT ( pEXT_CALLBACK pVECTOREVENTPROC )( pVECTORHANDLE pVector, L_UINT uLevel, pVECTOREVENT pEvent, L_VOID L_FAR *pUserData );
#else
   struct _VECTORHANDLE;
   typedef L_INT ( pEXT_CALLBACK  pVECTOREVENTPROC )(struct _VECTORHANDLE* pVector, L_UINT uLevel, pVECTOREVENT pEvent, L_VOID L_FAR *pUserData );
#endif
typedef pVECTOREVENTPROC L_FAR *ppVECTOREVENTPROC;


// VECTORHANDLE: Vector handle.
typedef struct _VECTORHANDLE
{
   L_INT                   nSize;                     // Size of this structure. Used for versioning.
   L_UINT32                dwInit;                    // Reserved for internal use.
   L_BOOL                  bLocked;                   // If TRUE vector handle cannot be edited.
   L_INT                   nBindVerticesMode;         // Bind vertices mode.
   RECT                    rcViewport;                // Current viewport.
   POINT                   ptPan;                     // Current physical pan value.
   COLORREF                clrBackground;             // Background color.
   L_INT                   nActiveLayer;              // Current active layer.
   VECTORTRANSFORMATION    Transformation;            // Transformation values.
   VECTORCAMERA            Camera;                    // Camera settings.
   VECTORMARKER            Marker;                    // Marker settings.
   VECTORUNIT              Unit;                      // Unit settings. Reserved for internal use
   VECTORHITTEST           HitTest;                   // Hit test settings.
   L_INT                   nPolygonMode;              // Polygon view mode.
   L_UINT                  uViewMode;                 // View mode.
   L_BOOL                  bUseLights;                // Use lights
   COLORREF                clrAmbient;                // Ambient color.   
   VECTOR_DISPLAY_OPTIONS  DisplayOptions;            // Display options
   HPALETTE                hPalette;                  // Palette handle   
   VECTORATTRIBUTES        Attributes;                // Attributes of this vector handle.
   L_UINT32                dwFlags;                   // Flags. Reserved for internal use.
   VECTORARRAY             aLayers;                   // Layers inside this vector handle.
   VECTORARRAY             aGroups;                   // Groups inside this vector handle.
   VECTORARRAY             aObjectsToBeDeleted;       // Objects to be deleted.
   L_VOID L_FAR           *pEngine;                   // Rendering engine.
   L_INT                   nEngine;                   // Engine.
   L_VOID L_FAR           *pEngineFast;               // Fast engine.
   L_INT                   nEvent;                    // Reserved for internal use.   
   pVECTOREVENTPROC        pEventProc;                // Reserved for internal use.
   L_VOID                 *pEventProcUserData;        // Reserved for internal use.
}
VECTORHANDLE, L_FAR *pVECTORHANDLE;


// VECTORVERTEX: 3D vertex in space
typedef struct _VECTORVERTEX
{
   VECTOROBJECT            Object;
   VECTORPOINT             Point;                     // Location.
   VECTORPEN               Pen;                       // Pen.
}
VECTORVERTEX, L_FAR *pVECTORVERTEX;


// VECTORLINE: Line.
typedef struct _VECTORLINE
{
   VECTOROBJECT            Object;
   VECTORPOINT             Point[ 2 ];                // Start and end position.
   VECTORPEN               Pen;                       // Pen.
}
VECTORLINE, L_FAR *pVECTORLINE;


// VECTORRECTANGLE: Rectangle.
typedef struct _VECTORRECTANGLE
{
   VECTOROBJECT            Object;
   VECTORPOINT             Point[ 2 ];                // Top left and bottom right positions.
   VECTORPEN               Pen;                       // Pen.
   VECTORBRUSH             Brush;                     // Brush.
}
VECTORRECTANGLE, L_FAR *pVECTORRECTANGLE;


// VECTORCURVEOPENED: Opened curve (VECTOR_POLYLINE, VECTOR_POLYBEZIER).
typedef struct _VECTORCURVEOPENED
{
   VECTOROBJECT            Object;
   VECTORPOINT            *Point;                     // Points.
   L_INT                   nPointCount;               // Number of points in array.
   VECTORPEN               Pen;                       // Pen.
}
VECTORCURVEOPENED, L_FAR *pVECTORCURVEOPENED,
VECTORPOLYLINE, L_FAR *pVECTORPOLYLINE,
VECTORPOLYBEZIER, L_FAR *pVECTORPOLYBEZIER;


// VECTORCURVECLOSED: Closed curve (VECTOR_POLYGON).
typedef struct _VECTORCURVECLOSED
{
   VECTOROBJECT            Object;
   VECTORPOINT            *Point;                     // Points.
   L_INT                   nPointCount;               // Number of points in array.
   VECTORPEN               Pen;                       // Pen.
   VECTORBRUSH             Brush;                     // Brush.
   L_INT                   nPolyFillMode;             // Polygon fill mode (VECTOR_POLY_ALTERNATE or VECTOR_POLY_WINDING).
}
VECTORCURVECLOSED, L_FAR *pVECTORCURVECLOSED,
VECTORPOLYGON, L_FAR *pVECTORPOLYGON;


// VECTORELLIPSE: Ellipse (VECTOR_ELLIPSE).
typedef struct _VECTORELLIPSE
{
   VECTOROBJECT            Object;
   VECTORPOINT             Point;                     // Center.
   VECTORPEN               Pen;                       // Pen.
   VECTORBRUSH             Brush;                     // Brush.
   L_DOUBLE                xRadius;                   // x-Radius.
   L_DOUBLE                yRadius;                   // y-Radius;
}
VECTORELLIPSE, L_FAR *pVECTORELLIPSE;


// VECTORCIRCLE: Circle (VECTOR_CIRCLE).
typedef struct _VECTORCIRCLE
{
   VECTOROBJECT            Object;
   VECTORPOINT             Point;                     // Center.
   VECTORPEN               Pen;                       // Pen.
   VECTORBRUSH             Brush;                     // Brush.
   L_DOUBLE                Radius;                    // Radius.
}
VECTORCIRCLE, L_FAR *pVECTORCIRCLE;


// VECTORARC: Arc (VECTOR_ARC).
typedef struct _VECTORARC
{
   VECTOROBJECT            Object;
   VECTORPOINT             Point;                     // Center.
   VECTORPEN               Pen;                       // Pen.
   L_DOUBLE                Radius;                    // Radius.
   L_DOUBLE                StartAngle;                // Start angle in degrees.
   L_DOUBLE                SweepAngle;                // Sweep angle in degrees.
}
VECTORARC, L_FAR *pVECTORARC;


// VECTORTEXT: Text (VECTOR_TEXT).
typedef struct _VECTORTEXT
{
   VECTOROBJECT            Object;
   VECTORPOINT             Point;                     // Insertion point.
   L_CHAR L_FAR           *pszText;                   // The text itself.
   L_UINT32                dwFlags;                   // Flags.
   L_DOUBLE                CharHeight;                // Height.
   L_DOUBLE                CharWidth;                 // Width.
   VECTORPEN               Pen;                       // Pen.
   VECTORBRUSH             Brush;                     // Brush.
   VECTORFONT              Font;                      // Font.
}
VECTORTEXT, L_FAR *pVECTORTEXT;


// VECTORPIE and VECTORCHORD: Pie and chord section (VECTOR_PIE, VECTOR_CHORD).
typedef struct _VECTORPIE
{
   VECTOROBJECT            Object;
   VECTORPOINT             Point;                     // Center.
   VECTORPEN               Pen;                       // Pen.
   VECTORBRUSH             Brush;                     // Brush.
   L_DOUBLE                Radius;                    // Radius.
   L_DOUBLE                StartAngle;                // Start angle in degrees.
   L_DOUBLE                SweepAngle;                // Sweep angle in degrees.
}
VECTORPIE, L_FAR *pVECTORPIE,
VECTORCHORD, L_FAR *pVECTORCHORD;


// VECTORPOLYDRAW: Polydraw (VECTOR_POLYDRAW).
typedef struct _VECTORPOLYDRAW
{
   VECTOROBJECT            Object;
   VECTORPOINT            *Point;                     // Points array.
   L_INT                   nPointCount;               // Number of points in array.
   L_UCHAR L_FAR          *pbyType;                   // Types.
   VECTORPEN               Pen;                       // Pen.
   VECTORBRUSH             Brush;                     // Brush.
}
VECTORPOLYDRAW, L_FAR *pVECTORPOLYDRAW;


// VECTORRASTER: Raster (VECTOR_RASTER)
typedef struct _VECTORRASTER
{
   VECTOROBJECT            Object;
   VECTORPOINT             Point[ 2 ];                // Top left and bottom right positions.
   VECTORBITMAP            Bitmap;                    // Bitmap.
}
VECTORRASTER, L_FAR *pVECTORRASTER;


// VECTORSTOCK: Stock object (VECTOR_STOCK)
typedef struct _VECTORSTOCK
{
   VECTOROBJECT            Object;
   L_INT                   nId;                       // Stock object ID in its DLL.
   HINSTANCE               hInstDLL;                  // DLL's instance.
   L_CHAR L_FAR           *pszDLLName;                // DLL's name.
   VECTORPOINT             Point[ 2 ];                // Bounding parallelogram.
   VECTORPEN               Pen;                       // Pen.
   VECTORBRUSH             Brush;                     // Brush.
}
VECTORSTOCK, L_FAR *pVECTORSTOCK;


// VECTORCLONE: Clone object (VECTOR_CLONE)
typedef struct _VECTORCLONE
{
   VECTOROBJECT            Object;
   VECTORPOINT             Point;
   VECTORGROUP             Group;
   L_UINT32                dwFlags;
   VECTORPEN               Pen;
   VECTORBRUSH             Brush;
   VECTORPOINT             Scale;
   VECTORPOINT             Rotation;
}
VECTORCLONE, *pVECTORCLONE;


// VECTORELLIPTICALARC: Elliptical Arc (VECTOR_ELLIPTICALARC).
typedef struct _VECTORELLIPTICALARC
{
   VECTOROBJECT            Object;
   VECTORPOINT             Point;                     // Center.
   VECTORPEN               Pen;                       // Pen.
   L_DOUBLE                xRadius;                   // x-Radius.
   L_DOUBLE                yRadius;                   // y-Radius;
   L_DOUBLE                StartAngle;                // Start angle in degrees.
   L_DOUBLE                SweepAngle;                // Sweep angle in degrees.
}
VECTORELLIPTICALARC, L_FAR *pVECTORELLIPTICALARC;


/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Functions.                                                           []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/


/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  General functions.                                                   []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
L_INT EXT_FUNCTION L_VecInit( pVECTORHANDLE pVector );
L_INT EXT_FUNCTION L_VecFree( pVECTORHANDLE pVector );
L_INT EXT_FUNCTION L_VecEmpty( pVECTORHANDLE pVector );
L_BOOL EXT_FUNCTION L_VecIsEmpty( const pVECTORHANDLE pVector );
L_INT EXT_FUNCTION L_VecCopy( pVECTORHANDLE pDst, const pVECTORHANDLE pSrc, L_UINT32 dwFlags );

L_INT EXT_FUNCTION L_VecSetDisplayOptions( pVECTORHANDLE pVector, const pVECTOR_DISPLAY_OPTIONS pOptions );
L_INT EXT_FUNCTION L_VecGetDisplayOptions( pVECTORHANDLE pVector, pVECTOR_DISPLAY_OPTIONS pOptions );

L_INT EXT_FUNCTION L_VecInvertColors( pVECTORHANDLE pVector );

L_INT EXT_FUNCTION L_VecSetViewport( pVECTORHANDLE pVector, const RECT L_FAR *pViewport );
L_INT EXT_FUNCTION L_VecGetViewport( const pVECTORHANDLE pVector, RECT L_FAR *pViewport );

L_INT EXT_FUNCTION L_VecSetPan( pVECTORHANDLE pVector, const POINT L_FAR *pPan );
L_INT EXT_FUNCTION L_VecGetPan( const pVECTORHANDLE pVector, POINT L_FAR *pPan );

L_INT EXT_FUNCTION L_VecPaint( HDC hDC, const pVECTORHANDLE pVector, L_BOOL bEraseBkgnd );
L_INT EXT_FUNCTION L_VecRealize( pBITMAPHANDLE pBitmap, const pVECTORHANDLE pVetcor, L_BOOL bEraseBkgnd );

L_INT EXT_FUNCTION L_VecPaintDC( HDC hDC, const pVECTORHANDLE pVector, L_UINT uWidth, L_UINT uHeight, const RECT L_FAR *pSrc, const RECT L_FAR *pSrcClip, const RECT L_FAR *pDest, const RECT L_FAR *pDestClip, L_UINT32 dwFlags );

L_BOOL EXT_FUNCTION L_VecIs3D( const pVECTORHANDLE pVector);

L_BOOL EXT_FUNCTION L_VecIsLocked( const pVECTORHANDLE pVector );
L_INT EXT_FUNCTION L_VecSetLocked( pVECTORHANDLE pVector, L_BOOL bLock );

L_INT EXT_FUNCTION L_VecSetBackgroundColor( pVECTORHANDLE pVector, COLORREF Color );
COLORREF EXT_FUNCTION L_VecGetBackgroundColor( const pVECTORHANDLE pVector );

L_INT EXT_FUNCTION L_VecLogicalToPhysical( const pVECTORHANDLE pVector, POINT L_FAR *pDst, const pVECTORPOINT pSrc );
L_INT EXT_FUNCTION L_VecPhysicalToLogical( const pVECTORHANDLE pVector, pVECTORPOINT pDst, const POINT L_FAR *pSrc );

L_INT EXT_FUNCTION L_VecSetPalette( pVECTORHANDLE pVector, HPALETTE hPalette );
HPALETTE EXT_FUNCTION L_VecGetPalette( const pVECTORHANDLE pVector );

L_INT EXT_FUNCTION L_VecSetViewMode( pVECTORHANDLE pVector, L_INT nMode );
L_INT EXT_FUNCTION L_VecGetViewMode( const pVECTORHANDLE pVector );


/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Transformation function.                                             []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
L_INT EXT_FUNCTION L_VecSetTranslation( pVECTORHANDLE pVector, const pVECTORPOINT pTranslation, pVECTOROBJECT pObject, L_UINT32 dwFlags );
L_INT EXT_FUNCTION L_VecGetTranslation( const pVECTORHANDLE pVector, pVECTORPOINT pTranslation );

L_INT EXT_FUNCTION L_VecSetRotation( pVECTORHANDLE pVector, const pVECTORPOINT pRotation, pVECTOROBJECT pObject, const pVECTORPOINT pOrigin, L_UINT32 dwFlags );
L_INT EXT_FUNCTION L_VecGetRotation( const pVECTORHANDLE pVector, pVECTORPOINT pRotation);

L_INT EXT_FUNCTION L_VecSetScale( pVECTORHANDLE pVector, const pVECTORPOINT pScale, pVECTOROBJECT pObject, const pVECTORPOINT pOrigin, L_UINT32 dwFlags );
L_INT EXT_FUNCTION L_VecGetScale( const pVECTORHANDLE pVector, pVECTORPOINT pScale );

L_INT EXT_FUNCTION L_VecSetOrigin( pVECTORHANDLE pVector, const pVECTORPOINT pOrigin );
L_INT EXT_FUNCTION L_VecGetOrigin( const pVECTORHANDLE pVector, pVECTORPOINT pOrigin );

L_INT EXT_FUNCTION L_VecApplyTransformation( pVECTORHANDLE pVector );

L_INT EXT_FUNCTION L_VecZoomRect( pVECTORHANDLE pVector, const RECT *pRect );


/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Attributes functions.                                                []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
L_INT EXT_FUNCTION L_VecSetBindVerticesMode( pVECTORHANDLE pVector, L_INT nMode );
L_INT EXT_FUNCTION L_VecGetBindVerticesMode( const pVECTORHANDLE pVector );

L_INT EXT_FUNCTION L_VecSetParallelogram( pVECTORHANDLE pVector, const pVECTORPOINT pMin, const pVECTORPOINT pMax );
L_INT EXT_FUNCTION L_VecGetParallelogram( const pVECTORHANDLE pVector, pVECTORPOINT pMin, pVECTORPOINT pMax );

typedef L_INT ( pEXT_CALLBACK pVECTORENUMVERTICESPROC )( pVECTORHANDLE pVector, pVECTORPOINT pPoint, L_VOID L_FAR *pUserData );
L_INT EXT_FUNCTION L_VecEnumVertices( pVECTORHANDLE pVector, pVECTORENUMVERTICESPROC pEnumProc, L_VOID L_FAR *pUserData, L_UINT32 dwFlags );


/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Camera functions.                                                    []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
L_INT EXT_FUNCTION L_VecSetCamera( pVECTORHANDLE pVector, const pVECTORCAMERA pCamera );
L_INT EXT_FUNCTION L_VecGetCamera( const pVECTORHANDLE pVector, pVECTORCAMERA pCamera );


/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Metafile functions.                                                  []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
HMETAFILE EXT_FUNCTION L_VecConvertToWMF( HDC hDC, const pVECTORHANDLE pVector, const RECT L_FAR *pRect, L_UINT uDPI );
L_INT EXT_FUNCTION L_VecConvertFromWMF( HDC hDC, pVECTORHANDLE pVector, HMETAFILE hWMF );

#ifdef WIN32
HENHMETAFILE EXT_FUNCTION L_VecConvertToEMF( HDC hDC, const pVECTORHANDLE pVector, const RECT L_FAR *pRect, L_UINT uDPI );
L_INT EXT_FUNCTION L_VecConvertFromEMF( HDC hDC, pVECTORHANDLE pVector, HENHMETAFILE hEMF );
#endif   // WIN32


/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Engine functions.                                                    []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
L_INT EXT_FUNCTION L_VecGetEngine( const pVECTORHANDLE pVector );
L_INT EXT_FUNCTION L_VecAttachToWindow( HWND hWnd, pVECTORHANDLE pVector, L_INT nEngine, L_UINT32 dwFlags );


/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Marker functions.                                                    []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
L_INT EXT_FUNCTION L_VecSetMarker( pVECTORHANDLE pVector, const pVECTORMARKER pMarker );
L_INT EXT_FUNCTION L_VecGetMarker( const pVECTORHANDLE pVector, pVECTORMARKER pMarker );

/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Unit functions.                                                      []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
/* Reserved for internal use */
L_INT EXT_FUNCTION L_VecSetUnit( pVECTORHANDLE pVector, const pVECTORUNIT pUnit );
L_INT EXT_FUNCTION L_VecGetUnit( const pVECTORHANDLE pVector, pVECTORUNIT pUnit );
L_INT EXT_FUNCTION L_VecConvertPointToUnits( const pVECTORHANDLE pVector, pVECTORPOINT pptDst, const pVECTORPOINT pptSrc, VECTOR_UNIT UnitToUse );
L_INT EXT_FUNCTION L_VecConvertPointFromUnits( const pVECTORHANDLE pVector, pVECTORPOINT pptDst, const pVECTORPOINT pptSrc, VECTOR_UNIT UnitToUse );


/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Hit test functions.                                                  []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
L_INT EXT_FUNCTION L_VecSetHitTest( pVECTORHANDLE pVector, const pVECTORHITTEST pHitTest );
L_INT EXT_FUNCTION L_VecGetHitTest( const pVECTORHANDLE pVector, pVECTORHITTEST pHitTest );
L_INT EXT_FUNCTION L_VecHitTest( const pVECTORHANDLE pVector, const POINT L_FAR *pPoint, pVECTOROBJECT pObject );


/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Polygon functions.                                                   []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
L_INT EXT_FUNCTION L_VecSetPolygonMode( pVECTORHANDLE pVector, L_INT nMode );
L_INT EXT_FUNCTION L_VecGetPolygonMode( const pVECTORHANDLE pVector );

L_INT EXT_FUNCTION L_VecSetUseLights( pVECTORHANDLE pVector, L_BOOL bUseLights );
L_BOOL EXT_FUNCTION L_VecGetUseLights( const pVECTORHANDLE pVector );

L_INT EXT_FUNCTION L_VecSetAmbientColor( pVECTORHANDLE pVector, COLORREF Color );
COLORREF EXT_FUNCTION L_VecGetAmbientColor( const pVECTORHANDLE pVector );


/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Clipboard functions.                                                 []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
L_BOOL EXT_FUNCTION L_VecClipboardReady( L_VOID );

L_INT EXT_FUNCTION L_VecCopyToClipboard( HWND hWnd, const pVECTORHANDLE pVector, L_UINT32 dwFlags );
L_INT EXT_FUNCTION L_VecCopyFromClipboard( HWND hWnd, pVECTORHANDLE pVector, L_UINT32 dwFlags );


/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Layer functions.                                                     []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
L_INT EXT_FUNCTION L_VecAddLayer( pVECTORHANDLE pVector, const pVECTORLAYERDESC pLayerDesc, pVECTORLAYER pLayer, L_UINT32 dwFlags );
L_INT EXT_FUNCTION L_VecDeleteLayer( pVECTORHANDLE pVector, const pVECTORLAYER pLayer );
L_INT EXT_FUNCTION L_VecEmptyLayer( pVECTORHANDLE pVector, const pVECTORLAYER pLayer );
L_INT EXT_FUNCTION L_VecCopyLayer( pVECTORHANDLE pVectorDst, const pVECTORLAYER pLayerDst, const pVECTORHANDLE pVectorSrc, const pVECTORLAYER pLayerSrc, L_UINT32 dwFlags );

L_INT EXT_FUNCTION L_VecGetLayerByName( const pVECTORHANDLE pVector, const L_CHAR L_FAR *pszName, pVECTORLAYER pLayer );
L_INT EXT_FUNCTION L_VecGetLayerCount( const pVECTORHANDLE pVector );
L_INT EXT_FUNCTION L_VecGetLayerByIndex( const pVECTORHANDLE pVector, L_INT nIndex, pVECTORLAYER pLayer );
L_INT EXT_FUNCTION L_VecGetLayer( const pVECTORHANDLE pVector, const pVECTORLAYER pLayer, pVECTORLAYERDESC pLayerDesc );
L_INT EXT_FUNCTION L_VecFreeLayer( pVECTORLAYERDESC pLayerDesc);
L_INT EXT_FUNCTION L_VecSetLayer( pVECTORHANDLE pVector, const pVECTORLAYER pLayer, const pVECTORLAYERDESC pLayerDesc );

L_INT EXT_FUNCTION L_VecSetActiveLayer( pVECTORHANDLE pVector, const pVECTORLAYER pLayer );
L_INT EXT_FUNCTION L_VecGetActiveLayer( const pVECTORHANDLE pVector, pVECTORLAYER pLayer );

typedef L_INT ( pEXT_CALLBACK pVECTORENUMLAYERSPROC )( pVECTORHANDLE pVector, const pVECTORLAYER pLayer, L_VOID L_FAR *pUserData );
L_INT EXT_FUNCTION L_VecEnumLayers( pVECTORHANDLE pVector, pVECTORENUMLAYERSPROC pEnumProc, L_VOID L_FAR *pUserData );


/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Group functions.                                                     []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
L_INT EXT_FUNCTION L_VecAddGroup( pVECTORHANDLE pVector, const pVECTORGROUPDESC pGroupDesc, pVECTORGROUP pGroup, L_UINT32 dwFlags );
L_INT EXT_FUNCTION L_VecDeleteGroup( pVECTORHANDLE pVector, const pVECTORGROUP pGroup );
L_INT EXT_FUNCTION L_VecDeleteGroupClones( pVECTORHANDLE pVector, const pVECTORGROUP pGroup, L_UINT32 dwFlags );
L_INT EXT_FUNCTION L_VecEmptyGroup( pVECTORHANDLE pVector, const pVECTORGROUP pGroup );
L_INT EXT_FUNCTION L_VecCopyGroup( pVECTORHANDLE pVectorDst, const pVECTORGROUP pGroupDst, const pVECTORHANDLE pVectorSrc, const pVECTORGROUP pGroupSrc, L_UINT32 dwFlags );

L_INT EXT_FUNCTION L_VecGetGroupByName( const pVECTORHANDLE pVector, const L_CHAR L_FAR *pszName, pVECTORGROUP pGroup );
L_INT EXT_FUNCTION L_VecGetGroupCount( const pVECTORHANDLE pVector );
L_INT EXT_FUNCTION L_VecGetGroupByIndex( const pVECTORHANDLE pVector, L_INT nIndex, pVECTORGROUP pGroup );
L_INT EXT_FUNCTION L_VecGetGroup( const pVECTORHANDLE pVector, const pVECTORGROUP pGroup, pVECTORGROUPDESC pGroupDesc );
L_INT EXT_FUNCTION L_VecFreeGroup( pVECTORGROUPDESC pGroupDesc );
L_INT EXT_FUNCTION L_VecSetGroup( pVECTORHANDLE pVector, const pVECTORGROUP pGroup, const pVECTORGROUPDESC pGroupDesc );

typedef L_INT ( pEXT_CALLBACK pVECTORENUMGROUPSPROC )( pVECTORHANDLE pVector, const pVECTORGROUP pGroup, L_VOID L_FAR *pUserData );
L_INT EXT_FUNCTION L_VecEnumGroups( pVECTORHANDLE pVector, pVECTORENUMGROUPSPROC pEnumProc, L_VOID L_FAR *pUserData );


/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Object functions.                                                    []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
L_INT EXT_FUNCTION L_VecInitObject( pVECTOROBJECT pObject );
L_INT EXT_FUNCTION L_VecAddObject( pVECTORHANDLE pVector, const pVECTORLAYER pLayer, L_INT nType, const L_VOID L_FAR *pObjectDesc, pVECTOROBJECT pNewObject);
L_INT EXT_FUNCTION L_VecDeleteObject( pVECTORHANDLE pVector, const pVECTOROBJECT pObject, L_UINT32 dwFlags );
L_INT EXT_FUNCTION L_VecCopyObject( pVECTORHANDLE pVectorDst, const pVECTORLAYER pLayerDst, pVECTOROBJECT pObjectDst, const pVECTORHANDLE pVectorSrc, const pVECTOROBJECT pObjectSrc );

L_INT EXT_FUNCTION L_VecGetObject( const pVECTORHANDLE pVector, const pVECTOROBJECT pObject, L_INT nType, L_VOID L_FAR *pObjectDesc );
L_INT EXT_FUNCTION L_VecFreeObject( L_INT nType, L_VOID L_FAR *pObjectDesc );
L_INT EXT_FUNCTION L_VecSetObject( pVECTORHANDLE pVector, pVECTOROBJECT pObject, L_INT nType, const L_VOID L_FAR *pObjectDesc );
L_INT EXT_FUNCTION L_VecExplodeObject( pVECTORHANDLE pVector, const pVECTOROBJECT pObject, L_UINT32 dwFlags );
L_INT EXT_FUNCTION L_VecGetObjectParallelogram( const pVECTORHANDLE pVector, const pVECTOROBJECT pObject, pVECTORPOINT pMin, pVECTORPOINT pMax, L_UINT32 dwFlags );
L_INT EXT_FUNCTION L_VecGetObjectRect( const pVECTORHANDLE pVector, const pVECTOROBJECT pObject, RECT L_FAR *pRect, L_UINT32 dwFlags );
L_BOOL EXT_FUNCTION L_VecIsObjectInsideParallelogram( const pVECTORHANDLE pVector, const pVECTOROBJECT pObject, const pVECTORPOINT pMin, const pVECTORPOINT pMax, L_UINT32 dwFlags );
L_BOOL EXT_FUNCTION L_VecIsObjectInsideRect( const pVECTORHANDLE pVector, const pVECTOROBJECT pObject, const RECT L_FAR *pRect, L_UINT32 dwFlags );
L_INT EXT_FUNCTION L_VecSelectObject( const pVECTORHANDLE pVector, pVECTOROBJECT pObject, L_BOOL bSelect );
L_BOOL EXT_FUNCTION L_VecIsObjectSelected( const pVECTORHANDLE pVector, const pVECTOROBJECT pObject );
L_INT EXT_FUNCTION L_VecHideObject( const pVECTORHANDLE pVector, pVECTOROBJECT pObject, L_BOOL bHide );
L_BOOL EXT_FUNCTION L_VecIsObjectHidden( const pVECTORHANDLE pVector, const pVECTOROBJECT pObject );

typedef L_INT ( pEXT_CALLBACK pVECTORENUMOBJECTSPROC )( pVECTORHANDLE pVector, const pVECTOROBJECT pObject, L_VOID L_FAR *pUserData );
L_INT EXT_FUNCTION L_VecEnumObjects( pVECTORHANDLE pVector, pVECTORENUMOBJECTSPROC pEnumProc, L_VOID L_FAR *pUserData, L_UINT32 dwFlags );
L_INT EXT_FUNCTION L_VecEnumObjectsInLayer( pVECTORHANDLE pVector, const pVECTORLAYER pLayer, pVECTORENUMOBJECTSPROC pEnumProc, L_VOID L_FAR *pUserData, L_UINT32 dwFlags );

L_INT EXT_FUNCTION L_VecSetObjectAttributes( pVECTORHANDLE pVector, const pVECTOROBJECT pObject, const L_INT *pnROP, const pVECTORPEN pPen, const pVECTORBRUSH pBrush, const pVECTORFONT pFont, L_UINT32 dwFlags );
L_INT EXT_FUNCTION L_VecGetObjectAttributes( const pVECTORHANDLE pVector, const pVECTOROBJECT pObject, L_INT *pnROP, pVECTORPEN pPen, pVECTORBRUSH pBrush, pVECTORFONT pFont );

L_INT EXT_FUNCTION L_VecAddObjectToGroup( pVECTORHANDLE pVector, const pVECTORGROUP pGroup, L_INT nType, const L_VOID L_FAR *pObjectDesc, pVECTOROBJECT pNewObject );
L_INT EXT_FUNCTION L_VecEnumObjectsInGroup( pVECTORHANDLE pVector, const pVECTORGROUP pGroup, pVECTORENUMOBJECTSPROC pEnumProc, L_VOID L_FAR *pUserData, L_UINT32 dwFlags );

L_INT EXT_FUNCTION L_VecSetObjectTooltip( pVECTORHANDLE pVector, pVECTOROBJECT pObject, L_CHAR *pszTooltip );
L_UINT32 EXT_FUNCTION L_VecGetObjectTooltip( pVECTORHANDLE pVector, const pVECTOROBJECT pObject, L_CHAR *pBuffer, L_UINT32 uSize );
L_INT EXT_FUNCTION L_VecShowObjectTooltip( pVECTORHANDLE pVector, const pVECTOROBJECT pObject, pVECTORTOOLTIPDESC pTooltipDesc );
L_INT EXT_FUNCTION L_VecHideObjectTooltip( pVECTORHANDLE pVector, const pVECTOROBJECT pObject );

L_INT EXT_FUNCTION L_VecSetObjectViewContext( pVECTORHANDLE pVector, pVECTOROBJECT pObject, const pVECTORPOINT pMin, const pVECTORPOINT pMax );
L_INT EXT_FUNCTION L_VecGetObjectViewContext( pVECTORHANDLE pVector, const pVECTOROBJECT pObject, pVECTORPOINT pMin, pVECTORPOINT pMax );
L_INT EXT_FUNCTION L_VecRemoveObjectViewContext( pVECTORHANDLE pVector, pVECTOROBJECT pObject );

L_INT EXT_FUNCTION L_VecAddHyperlink( pVECTORHANDLE pVector, pVECTOROBJECT pObject, pVECTORLINKDESC pTarget );
L_INT EXT_FUNCTION L_VecSetHyperlink( pVECTORHANDLE pVector, pVECTOROBJECT pObject, L_UINT32 uIndex, pVECTORLINKDESC pTarget );
L_INT EXT_FUNCTION L_VecGetHyperlink( pVECTORHANDLE pVector, const pVECTOROBJECT pObject, L_UINT32 uIndex, pVECTORLINKDESC pTarget );
L_UINT32 EXT_FUNCTION L_VecGetHyperlinkCount( pVECTORHANDLE pVector, const pVECTOROBJECT pObject );
L_INT EXT_FUNCTION L_VecGotoHyperlink( pVECTORHANDLE pVector, const pVECTOROBJECT pObject, L_UINT32 uIndex );

L_INT EXT_FUNCTION L_VecSetObjectDescription( pVECTORHANDLE pVector, pVECTOROBJECT pObject, L_CHAR *pszTarget );
L_UINT32 EXT_FUNCTION L_VecGetObjectDescription( pVECTORHANDLE pVector, const pVECTOROBJECT pObject, L_CHAR *pBuffer, L_UINT32 uSize );


/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Event functions.                                                     []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
L_INT EXT_FUNCTION L_VecSetEventCallback( pVECTORHANDLE pVector, pVECTOREVENTPROC pProc, L_VOID L_FAR *pUserData, ppVECTOREVENTPROC pOldProc, L_VOID L_FAR **pOldUserData );
L_INT EXT_FUNCTION L_VecEvent( pVECTORHANDLE, pVECTOREVENT );

typedef L_INT (pEXT_FUNCTION fntypVecEvent)( pVECTORHANDLE, pVECTOREVENT );


#undef _HEADER_ENTRY_
#include "ltpck.h"


#endif   // _LVKRN_H_
