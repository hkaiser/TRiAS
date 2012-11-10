/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  LEAD LDKRN.                                                          []*/
/*[]                                                                       []*/
/*[]                                                                       []*/
/*[]  Copyright (c) 1991-2000  by LEAD Technologies, Inc.                  []*/
/*[]  All Rights Reserved.                                                 []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
#ifndef _LDKRN_H_
#define _LDKRN_H_

#ifdef __cplusplus
   #ifdef _LEAD_DOCUMENT_
      #define DOCUMENT_EXPORT __declspec(dllexport)
   #else
      #define DOCUMENT_EXPORT __declspec(dllimport)
   #endif
#endif

/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]                    INCLUDES                                           []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/

#ifndef STRICT
   #define STRICT
#endif

#include "lttyp.h"
#include "lterr.h"
#include "ltkrn.h"
#include "lvkrn.h"

#define _HEADER_ENTRY_
#include "ltpck.h"

/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]                    DEFINES                                            []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/

// edit mode defines 
#define   DOCEDIT_MODE_PREVIEW          0                // preview mode
#define   DOCEDIT_MODE_EDIT             1                // edit mode

/* FTP */ 
#define   DEFAULT_FTP_PORT              21

/* TAB */ 
#define   DEFAULT_TAB_SIZE              4
// callback command defines 
#define   DOCEDIT_CMD_UPDATECOMMANDS    0                // update command 

// editor status values 
#define   DOCEDIT_SUPPORTED	         0x1               // the feature is supported 
#define   DOCEDIT_ENABLED	            0x2               // the feature is enabled   
#define   DOCEDIT_ISON	               0x4               // the feature is set on  
#define   DOCEDIT_ISOFF                0x8               // the feature is set off

// justify values
#define   DOCEDIT_JUSTIFYCENTER        0                  // Justify center
#define   DOCEDIT_JUSTIFYRIGHT         1                  // Justify right  
#define   DOCEDIT_JUSTIFYLEFT          2                  // Justify left

#define  DOC_MAX_PASSWORD_LEN          64   

// bookmarks
#define     MAX_BOOKMARKNAME_LENGTH     255
#define     MAX_NUMBEROF_BOOKMARKS      255

// Events of the event CallBack
typedef enum
{
   DOC_EVENT_GETPASSWORD = 500   
}DOCUMENT_EVENT;

typedef enum _DOCEDIT_SAVE_IMAGETYPE
{
   DOCEDIT_SAVE_IMAGETYPE_GIF = 0,
   DOCEDIT_SAVE_IMAGETYPE_JPG,
   DOCEDIT_SAVE_IMAGETYPE_LTLIT,

}DOCEDIT_SAVE_IMAGETYPE, *pDOCEDIT_SAVE_IMAGETYPE;

/* Definitions */
#define DOCEDIT_DLG_AUTO_PROCESS                (0x80000000)


/* Dialog String Indices */
enum
{
   /* Generic control strings */
   DOCEDIT_DLGSTR_OK,
   DOCEDIT_DLGSTR_CANCEL,
   DOCEDIT_DLGSTR_HELP,

   /* Insert Vector/Raster dialog */
   DOCEDIT_DLGSTR_INSERT_RASTER_CAPTION,
   DOCEDIT_DLGSTR_INSERT_VECTOR_CAPTION,
   DOCEDIT_DLGSTR_INSERT_BUTTON_BROWSE,
   DOCEDIT_DLGSTR_INSERT_LABEL_WIDTH,
   DOCEDIT_DLGSTR_INSERT_LABEL_HEIGHT,
   DOCEDIT_DLGSTR_INSERT_LABEL_ALIGN,
   DOCEDIT_DLGSTR_INSERT_LABEL_HSPACE,
   DOCEDIT_DLGSTR_INSERT_LABEL_VSPACE,

   /* Insert dialog align combo */
   DOCEDIT_DLGSTR_INSERT_ALIGN_ABSBOTTOM,
   DOCEDIT_DLGSTR_INSERT_ALIGN_ABSMIDDLE,
   DOCEDIT_DLGSTR_INSERT_ALIGN_BASELINE,
   DOCEDIT_DLGSTR_INSERT_ALIGN_BOTTOM,
   DOCEDIT_DLGSTR_INSERT_ALIGN_LEFT,
   DOCEDIT_DLGSTR_INSERT_ALIGN_MIDDLE,
   DOCEDIT_DLGSTR_INSERT_ALIGN_RIGHT,
   DOCEDIT_DLGSTR_INSERT_ALIGN_TEXTTOP,
   DOCEDIT_DLGSTR_INSERT_ALIGN_TOP,

   /* Messages */
   DOCEDIT_DLGSTR_ERROR_NO_MEMORY,
   DOCEDIT_DLGSTR_ERROR_NO_BITMAP,
   DOCEDIT_DLGSTR_ERROR_MEMORY_TOO_LOW,
   DOCEDIT_DLGSTR_ERROR_FILE_LSEEK,
   DOCEDIT_DLGSTR_ERROR_FILE_WRITE,
   DOCEDIT_DLGSTR_ERROR_FILE_GONE,
   DOCEDIT_DLGSTR_ERROR_FILE_READ,
   DOCEDIT_DLGSTR_ERROR_INV_FILENAME,
   DOCEDIT_DLGSTR_ERROR_FILE_FORMAT,
   DOCEDIT_DLGSTR_ERROR_FILENOTFOUND,
   DOCEDIT_DLGSTR_ERROR_INV_RANGE,
   DOCEDIT_DLGSTR_ERROR_IMAGE_TYPE,

   DOCEDIT_DLGSTR_ERROR_INV_PARAMETER,
   DOCEDIT_DLGSTR_ERROR_FILE_OPEN,
   DOCEDIT_DLGSTR_ERROR_UNKNOWN_COMP,
   DOCEDIT_DLGSTR_ERROR_FEATURE_NOT_SUPPORTED,
   DOCEDIT_DLGSTR_ERROR_NOT_256_COLOR,

   DOCEDIT_DLGSTR_ERROR_DOC_NOT_INITIALIZED,
   DOCEDIT_DLGSTR_ERROR_DOC_HANDLE,
   DOCEDIT_DLGSTR_ERROR_DOC_EMPTY,
   DOCEDIT_DLGSTR_ERROR_DOC_INVALID_FONT,
   DOCEDIT_DLGSTR_ERROR_DOC_INVALID_PAGE,
   DOCEDIT_DLGSTR_ERROR_DOC_INVALID_RULE,
   DOCEDIT_DLGSTR_ERROR_DOC_INVALID_ZONE,
   DOCEDIT_DLGSTR_ERROR_DOC_TYPE_ZONE,
   DOCEDIT_DLGSTR_ERROR_DOC_INVALID_COLUMN,
   DOCEDIT_DLGSTR_ERROR_DOC_INVALID_LINE,
   DOCEDIT_DLGSTR_ERROR_DOC_INVALID_WORD,

   DOCEDIT_DLGSTR_ERROR_VECTOR_IS_LOCKED,
   DOCEDIT_DLGSTR_ERROR_VECTOR_IS_EMPTY,
   DOCEDIT_DLGSTR_ERROR_VECTOR_LAYER_NOT_FOUND,
   DOCEDIT_DLGSTR_ERROR_VECTOR_LAYER_IS_LOCKED,
   DOCEDIT_DLGSTR_ERROR_VECTOR_LAYER_ALREADY_EXISTS,
   DOCEDIT_DLGSTR_ERROR_VECTOR_OBJECT_NOT_FOUND,
   DOCEDIT_DLGSTR_ERROR_VECTOR_INVALID_OBJECT_TYPE,
   DOCEDIT_DLGSTR_ERROR_VECTOR_PEN_NOT_FOUND,
   DOCEDIT_DLGSTR_ERROR_VECTOR_BRUSH_NOT_FOUND,
   DOCEDIT_DLGSTR_ERROR_VECTOR_FONT_NOT_FOUND,
   DOCEDIT_DLGSTR_ERROR_VECTOR_BITMAP_NOT_FOUND,
   DOCEDIT_DLGSTR_ERROR_VECTOR_POINT_NOT_FOUND,
   DOCEDIT_DLGSTR_ERROR_VECTOR_CANT_ADD_TEXT,
   DOCEDIT_DLGSTR_ERROR_VECTOR_GROUP_NOT_FOUND,
   DOCEDIT_DLGSTR_ERROR_VECTOR_GROUP_ALREADY_EXISTS,

   DOCEDIT_DLGSTR_ERROR_DOCUMENT_NOT_ENABLED,
   DOCEDIT_DLGSTR_ERROR_MULTIMEDIA_NOT_ENABLED,
   DOCEDIT_DLGSTR_ERROR_MEDICAL_NOT_ENABLED,
   DOCEDIT_DLGSTR_ERROR_JBIG_NOT_ENABLED,
   DOCEDIT_DLGSTR_ERROR_JBIG_FILTER_MISSING,
   DOCEDIT_DLGSTR_ERROR_VECTOR_NOT_ENABLED,
   DOCEDIT_DLGSTR_ERROR_VECTOR_DXF_NOT_ENABLED,
   DOCEDIT_DLGSTR_ERROR_VECTOR_DWG_NOT_ENABLED,
   DOCEDIT_DLGSTR_ERROR_VECTOR_MISC_NOT_ENABLED,
   DOCEDIT_DLGSTR_ERROR_TAG_MISSING,
   DOCEDIT_DLGSTR_ERROR_VECTOR_DWF_NOT_ENABLED,
   DOCEDIT_DLGSTR_ERROR_PDF_NOT_ENABLED,

   DOCEDIT_DLGSTR_ERROR_CANNOTLOADBITMAP,
   DOCEDIT_DLGSTR_ERROR_CANNOTLOADVECTOR,

   /* Context Menu Items*/   
   DOCEDIT_DLGSTR_MENU_CUT,
   DOCEDIT_DLGSTR_MENU_COPY,
   DOCEDIT_DLGSTR_MENU_PASTE,
   DOCEDIT_DLGSTR_MENU_SELECTALL,
   DOCEDIT_DLGSTR_MENU_PRINT,
   DOCEDIT_DLGSTR_MENU_DELETE,

   DOCEDIT_DLGSTR_MAX
};

/* Ldkrn_.h */ 

// Object alignement with adjacent text
typedef enum 
{

   DOC_OBJTEXTALIGN_ABSBOTTOM =0,/*The bottom of the object is aligned with the absolute 
                              bottom of the surrounding text. The absolute bottom 
                              is equal to the baseline of the text minus the 
                              height of the largest descender in the text.  */
   DOC_OBJTEXTALIGN_ABSMIDDLE  ,/*The middle of the object is aligned with the middle of 
                              the surrounding text. The absolute middle is the 
                              midpoint between the absolute bottom and text 
                              top of the surrounding text. */
   DOC_OBJTEXTALIGN_BASELINE   ,/*The bottom of the object is aligned with the baseline 
                              of the surrounding text.  */
   DOC_OBJTEXTALIGN_BOTTOM     ,/*The bottom of the object is aligned  with the bottom of the 
                              surrounding text. The bottom is equal to the baseline 
                              minus the standard height of a descender in the text.*/
   DOC_OBJTEXTALIGN_LEFT       ,/*The object is aligned to the left of the surrounding text.
                              All preceding and subsequent text flows to the right 
                              of the object.  */
   DOC_OBJTEXTALIGN_MIDDLE     ,/*The middle of the object is aligned with the surrounding text.*/
   DOC_OBJTEXTALIGN_RIGHT      ,/*The object is aligned to the right of the surrounding text. 
                              All subsequent text flows to the left of the object.*/
   DOC_OBJTEXTALIGN_TEXTTOP    ,/*The top of the object is aligned with the absolute top of 
                              the surrounding text. The absolute top is the baseline 
                              plus the height of the largest ascender in the text.*/
   DOC_OBJTEXTALIGN_TOP         /*The top of the object is aligned  with the top of the text. 
                              The top of the text is the baseline plus the standard 
                              height of an ascender in the text.  */
} DOCUMENT_OBJTEXTALIGN;

// Text format 
typedef enum 
{
   DOC_TEXT_FORMAT_BOLD =0,       // text is bold
   DOC_TEXT_FORMAT_ITALIC,        // text is italic 
   DOC_TEXT_FORMAT_UNDERLINE,     // text is underlined 
   DOC_TEXT_FORMAT_STRIKETHROUGH, // text has a line through it 
   DOC_TEXT_FORMAT_OVERLINE,      // text has a line on top of it
   DOC_TEXT_FORMAT_ALLCAPITALS,   // all the coming text will be capitals 
   DOC_TEXT_FORMAT_SUPERSCRIPT,   // text is superscript
   DOC_TEXT_FORMAT_SUBSCRIPT,     // text is subscript   
   DOC_TEXT_FORMAT_DELETED,       // text is delted 
   DOC_TEXT_FORMAT_ANIMATED,      // text is animated(currently mapped to italic)
   DOC_TEXT_FORMAT_EMBOSS,        // text is emboss(currently mapped gray text) 
   DOC_TEXT_FORMAT_ENGRAVE,       // text is engrave(currently mapped gray text)
   DOC_TEXT_FORMAT_OUTLINE,       // text is outline(currently mapped to bold) 
   DOC_TEXT_FORMAT_SHADOW         // text is shadow(currently mapped to bold) 

} DOCUMENT_TEXT_FORMAT;

// A sub-catigory of the more general DOCUMENT_SIZEUNIT type 
typedef enum 
{
   DOC_SPECIALSIZEUNIT_PIXELS = 0   ,  // Pixels. 
   DOC_SPECIALSIZEUNIT_PERCENTAGE      // % Percentage     
} DOCUMENT_SPECIALSIZEUNIT;

#define FP_FONTFAMILYSIZE 32 //Font family string length 

// Length Units 
typedef enum 
{

   DOC_UNIT_PIXELS =1    ,  // Pixels. 
   DOC_UNIT_PERCENTAGE   ,  // % Percentage     
   DOC_UNIT_INCHES       ,  // Inches (1 inch = 2.54 centimeters). 
   DOC_UNIT_CENTIMETERS  ,  // Centimeters. 
   DOC_UNIT_MILLIMETERS  ,  // Millimeters. 
   DOC_UNIT_POINTS       ,  // Points (1 point = 1/72 inches). 
   DOC_UNIT_PICAS           // Picas (1 pica = 12 points). 
} DOCUMENT_SIZEUNIT;

// Font style
typedef enum 
{
   DOC_FONTSTYLE_NORMAL =1, //Font is normal. 
   DOC_FONTSTYLE_ITALIC   , //Font is italic. 
   DOC_FONTSTYLE_OBLIQUE    //Font is italic.  
} DOCUMENT_FONTSTYLE;

// Font variant 
typedef enum 
{
   DOC_FONTVARIANT_NORMAL =1    ,// Font is normal.  
   DOC_FONTVARIANT_SMALL_CAPS   // Font is in small capital letters. 
} DOCUMENT_FONTVARIANT ;

// Font weight 
typedef enum 
{
   
   DOC_FONTWEIGHT_NORMAL  =1  ,//Font is normal. 
   DOC_FONTWEIGHT_BOLD        ,//Font is bold. 
   DOC_FONTWEIGHT_BOLDER      ,//Font is heavier than regular bold. 
   DOC_FONTWEIGHT_LIGHTER     ,//Font is lighter than normal. 
   DOC_FONTWEIGHT_100         ,//Font is at least as light as the 200 weight. 
   DOC_FONTWEIGHT_200         ,//Font is at least as bold as the 100 weight
                           //and at least as light as the 300 weight. 
   DOC_FONTWEIGHT_300         ,//Font is at least as bold as the 200 weight and at least
                           //as light as the 400 weight. 
   DOC_FONTWEIGHT_400         ,//Font is normal. 
   DOC_FONTWEIGHT_500         ,//Font is at least as bold as the 400 weight and at least
                           //as light as the 600 weight. 
   DOC_FONTWEIGHT_600         ,//Font is at least as bold as the 500 weight and at least
                           //as light as the 700 weight. 
   DOC_FONTWEIGHT_700         ,//Font is bold. 
   DOC_FONTWEIGHT_800         ,//Font is at least as bold as the 700 weight and at least
                           //as light as the 900 weight. 
   DOC_FONTWEIGHT_900          //Font is at least as bold as the 800 weight. 
} DOCUMENT_FONTWEIGHT ;

// Text Direction
typedef enum 
{
   DOC_TEXTDIRECTION_LTR =1,   //Text flow is left-to-right. 
   DOC_TEXTDIRECTION_RTL       //Text flow is right-to-left. 
} DOCUMENT_TEXTDIRECTION;

// Text align
typedef enum 
{
   DOC_TEXTALIGN_LEFT  =1,//Text is aligned to the left. 
   DOC_TEXTALIGN_RIGHT   ,//Text is aligned to the right. 
   DOC_TEXTALIGN_CENTER  ,//Text is centered. 
   DOC_TEXTALIGN_JUSTIFY  //Text is justified. 
} DOCUMENT_TEXTALIGN ;

// Text decoration
typedef enum 
{
   
   DOC_TEXT_DECORATION_NONE =1          ,// Text has no decoration. 
   DOC_TEXT_DECORATION_UNDERLINE        ,// Text is underlined. 
   DOC_TEXT_DECORATION_OVERLINE         ,// Text has a line over it. 
   DOC_TEXT_DECORATION_LINE_THROUGH      // Text has a line drawn through it. 
} DOCUMENT_TEXT_DECORATION ;
// Text transform 
typedef enum 
{   
   DOC_TEXTTRANSFORM_NONE =1    ,//Text is not transformed. 
   DOC_TEXTTRANSFORM_CAPITALIZE ,//Transforms the first character of each word to uppercase. 
   DOC_TEXTTRANSFORM_UPPERCASE  ,//Transforms all the characters to uppercase. 
   DOC_TEXTTRANSFORM_LOWERCASE   //Transforms all the characters to lowercase. 
} DOCUMENT_TEXTTRANSFORM ;

// Vertical alignment 
typedef enum 
{   
   DOC_VERTICALALIGNMENT_BASELINE =1 ,//Aligns the contents of an object supporting vertical
                                  //alignement to the base line. 
   DOC_VERTICALALIGNMENT_SUB         ,//Vertically aligns the text to subscript. 
   DOC_VERTICALALIGNMENT_SUPER       ,//Vertically aligns the text to superscript. 
   DOC_VERTICALALIGNMENT_TOP         ,//Vertically aligns the contents of an object supporting
                                  //vertical alignement to the top of the object. 
   DOC_VERTICALALIGNMENT_MIDDLE      ,//Vertically aligns the contents of an object supporting 
                                  //vertical alignement to the middle of the object. 
   DOC_VERTICALALIGNMENT_BOTTOM      ,//Vertically aligns the contents of an object supporting vertical 
                                  //alignement to the bottom of the object. 
   DOC_VERTICALALIGNMENT_TEXT_TOP    ,//Vertically aligns the text of an object supporting vertical
                                  //alignement to the top of the object. 
   DOC_VERTICALALIGNMENT_TEXT_BOTTOM  //Vertically aligns the text of an object supporting 
                                  //vertical alignement to the bottom of the object. 
} DOCUMENT_VERTICALALIGNMENT ;

// On which side of the object the text will flow.
typedef enum 
{
   DOC_FLOATING_NONE =1     ,// Object displays where it appears in the text. 
   DOC_FLOATING_LEFT        ,// Text flows to the right of the object. 
   DOC_FLOATING_RIGHT       ,// Text flows to the left of the object. 
} DOCUMENT_FLOATING;

// used to specify whether the object allows floating objects on its left 
// and/or right sides, so that the next text displays past the floating objects.
typedef enum 
{
   DOC_CLEAR_NONE =1  ,//Floating objects are allowed on both sides. 
   DOC_CLEAR_LEFT     ,//Object is moved below any floating object on the left side. 
   DOC_CLEAR_RIGHT    ,//Object is moved below any floating object on the right side. 
   DOC_CLEAR_BOTH     ,//Object is moved below any floating object. 
} DOCUMENT_CLEAR;

// used to specify border styles 
typedef enum 
{
   DOC_BORDERSTYLE_NONE    = 1 ,//Border is not drawn, regardless of any border-width. 
   DOC_BORDERSTYLE_DOTTED      ,//Border is a dotted line
   DOC_BORDERSTYLE_DASHED      ,//Border is a dashed line
   DOC_BORDERSTYLE_SOLID       ,//Border is a solid line.    
   DOC_BORDERSTYLE_DOUBLE      ,//Border is a double line drawn on top of the background
                            //of the object. The sum of the two single lines and 
                            //the space between equals the border-width value.The border width
                            //must be at least 3 pixels wide to draw a double border. 
   DOC_BORDERSTYLE_GROOVE      ,//3-D groove is drawn in colors based on the value. 
   DOC_BORDERSTYLE_RIDGE       ,//3-D ridge is drawn in colors based on the value. 
   DOC_BORDERSTYLE_INSET       ,//3-D inset is drawn in colors based on the value. 
   DOC_BORDERSTYLE_OUTSET       //3-D outset is drawn in colors based on the value. 
} DOCUMENT_BORDERSTYLE;

// On which sides do we have borders 
typedef enum 
{
   DOC_BORDER_LEFT   =0x1, // we have a boder on the left   side 
   DOC_BORDER_RIGHT  =0x2, // we have a boder on the right  side 
   DOC_BORDER_TOP    =0x4, // we have a boder on the top    side 
   DOC_BORDER_BOTTOM =0x8  // we have a boder on the bottom side 
} DOCUMENT_BORDERS;

// Type of positioning of an object 
typedef enum 
{
   DOC_POSITIONINGTYPE_STATIC   = 1, //Object has no special positioning;
   DOC_POSITIONINGTYPE_ABSOLUTE    , //Object is positioned relative to parent element's 
                                 //position or to the page
                                 //borders  if its parent element is not positioned ,
                                 //using the top and left properties. 
   DOC_POSITIONINGTYPE_RELATIVE      //Object is positioned according to the normal flow, 
                                 //and then offset by the top and left properties. 
} DOCUMENT_POSITIONINGTYPE;

// Visibility of an object 
typedef enum 
{
   DOC_OBJECTVISIBILITY_VISIBLE= 1,  //Object is visible. 
   DOC_OBJECTVISIBILITY_HIDDEN       //Object is hidden. 
} DOCUMENT_OBJECTVISIBILITY;

/* Specifies how to manage the content of the object when the 
   content exceeds the height and/or width of the object.*/
typedef enum 
{
   DOC_OBJECTOVERFLOW_VISIBLE=1,//Content is not clipped, and scroll bars are not added(default). 
   DOC_OBJECTOVERFLOW_SCROLL   ,//Content is clipped, and scroll bars are added even if the
                            //content does not exceed the dimensions of the object. 
   DOC_OBJECTOVERFLOW_HIDDEN   ,//Content that exceeds the dimensions of the object is not shown. 
   DOC_OBJECTOVERFLOW_AUTO     ,//Content is clipped, and scrolling is added only when necessary. 
} DOCUMENT_OBJECTOVERFLOW;


// Where do you want this object be placed ?
typedef enum 
{
   DOC_OBJECT_ALIGN_LEFT =0,   // object will be aligned at the left of the page 
   DOC_OBJECT_ALIGN_RIGHT,     // object will be aligned at the right of the page 
   DOC_OBJECT_ALIGN_CENTER,    // object will be aligned at the center  of the page 
   DOC_OBJECT_ALIGN_NONE       // do not align the table 

} DOCUMENT_OBJECT_ALIGN;

// Where to place the caption of a table 
typedef enum 
{
   DOC_TABLECAPTIONALIGN_CENTER =0,
   DOC_TABLECAPTIONALIGN_BOTTOM   ,
   DOC_TABLECAPTIONALIGN_LEFT     ,
   DOC_TABLECAPTIONALIGN_RIGHT    ,
   DOC_TABLECAPTIONALIGN_TOP       
} DOCUMENT_TABLECAPTIONALIGN;

// What type of list do we have ?
typedef enum 
{
   DOC_LISTTYPE_NUMBERS =0        ,//Associate numbers with each item in a list. 
   DOC_LISTTYPE_LOWERCASE_LETTERS ,//Associate lowercase letters with each item in a list. 
   DOC_LISTTYPE_UPPERCASE_LETTERS ,//Associate uppercase letters with each item in a list. 
   DOC_LISTTYPE_LOWERCASE_ROMAN   ,//Associate Roman numerals with each item in a list. 
   DOC_LISTTYPE_UPPERCASE_ROMAN   ,//Associate Roman numerals with each item in a list. 
   DOC_LISTTYPE_DISC              ,//Associate a solid disc with each item in a list. 
   DOC_LISTTYPE_CIRCLE            ,//Associate a hollow circle with each item in a list. 
   DOC_LISTTYPE_SQUARE             //Associate a solid square with each item in a list. 
} DOCUMENT_LISTTYPE;

/*Type of image your are adding to the handle */
typedef enum  
{
   DOC_IMGTYPE_UNSPECIFIED,
   DOC_IMGTYPE_EMF,
   DOC_IMGTYPE_PNG,
   DOC_IMGTYPE_JPEG,   
   DOC_IMGTYPE_WMF,
   DOC_IMGTYPE_BMP
} DOCUMENT_IMGTYPE;

/* Type of bullets and numbering in a paragraph */
typedef enum 
{         
   DOC_PARLISTTYPE_UL_DISC=0               ,// filled circle
   DOC_PARLISTTYPE_UL_CIRCLE               ,// circle
   DOC_PARLISTTYPE_UL_SQUARE               ,// square 
   DOC_PARLISTTYPE_OL_NUMBERS              ,//(decimal numbers: 1, 2 ..)
   DOC_PARLISTTYPE_OL_LARGE_ROMAN_NUMERALS ,//(uppercase Roman numerals: I, II ..)
   DOC_PARLISTTYPE_OL_SMALL_ROMAN_NUMERALS ,//(lowercase Roman numerals: i, ii ..)
   DOC_PARLISTTYPE_OL_LARGE_LETTERS        ,//(uppercase alphabetic: A, B ..)
   DOC_PARLISTTYPE_OL_SMALL_LETTERS        ,//(lowercase alphabetic: a, b..)
   DOC_PARLISTTYPE_NON                     ,// par. has no bullets or numbering 
} DOCUMENT_PARLISTTYPE;

// List order
typedef enum 
{
   DOC_LISTORDER_ORDERED,// list is ordered 
   DOC_LISTORDER_UNORDERED // list is unordered 
} DOCUMENT_LISTORDER;

typedef enum _DOC_SENDBYMAILFORMAT
{
   DOC_SENDBYMAILFORMAT_TXT = 0,
   DOC_SENDBYMAILFORMAT_HTML,
   DOC_SENDBYMAILFORMAT_RTF,   

}DOC_SENDBYMAILFORMAT, *pDOC_SENDBYMAILFORMAT;

typedef enum _DOC_FTPUPLOADFORMAT
{
   DOC_FTPUPLOADFORMAT_TXT = 0,
   DOC_FTPUPLOADFORMAT_HTML,
   DOC_FTPUPLOADFORMAT_RTF,
   DOC_FTPUPLOADFORMAT_WORD97

}DOC_FTPUPLOADFORMAT, *pDOC_FTPUPLOADFORMAT;

/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]                    TYPES                                              []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/

// Document Handle
typedef struct _DOCHANDLE
{
   L_VOID * pHandleData;
} DOCHANDLE , * pDOCHANDLE ;

// table structure
typedef  struct TAG_DocEditTable
{
   L_UINT    uRows;              // number of table rows
   L_UINT    uColumns;           // number of table coloumns
   L_UINT    uCellWidth;         // cell width 
   L_UINT    uBorderSize;        // border size

}  DOCEDITTABLE,*pDOCEDITTABLE;

// valid format structure
typedef  struct TAG_VALIDFORMAT
{
   L_INT     nNumber;            // format numbers 
   L_CHAR ** ppFormat;           // array of valid format.

}  VALIDFORMAT,*pVALIDFORMAT;


// command structure
typedef  struct TAG_COMMANDDATA
{
   L_INT    nCmdID;              // command ID 
   L_CHAR*  pCommand;            // text of command 
   L_VOID*  pUserData;           // user data.

}  COMMANDDATA,*pCOMMANDDATA;

typedef  struct _DocBookmarks
{
   L_CHAR szBookmarks[ MAX_NUMBEROF_BOOKMARKS ] [ MAX_BOOKMARKNAME_LENGTH ];
   L_UINT32 uCount;

}DOCBOOKMARKS, *pDOCBOOKMARKS;

typedef struct _DOCEDIT_OPTIONS
{
   DOCEDIT_SAVE_IMAGETYPE SaveImageType;
      
}DOCEDIT_OPTIONS, *pDOCEDIT_OPTIONS;

typedef struct _DOCEDIT_IMAGECALLBACKINFO
{
   L_CHAR szPath[ L_MAXPATH ];
   
   L_INT32 nWidth;
   L_INT32 nHeight;
   L_VOID  *pUserData;

}DOCEDIT_IMAGECALLBACKINFO, *pDOCEDIT_IMAGECALLBACKINFO;

typedef struct _DOCEDIT_VECTORCALLBACKINFO
{
   L_CHAR szPath[ L_MAXPATH ];
   
   L_INT32 nWidth;
   L_INT32 nHeight;
   L_VOID  *pUserData;

}DOCEDIT_VECTORCALLBACKINFO, *pDOCEDIT_VECTORCALLBACKINFO;


// Events Callback 
typedef L_INT (pEXT_CALLBACK pDOCEVENTCALLBACK)(pDOCHANDLE pDocHandle,L_UINT uEventType,L_VOID *pEventData,L_VOID *pUserData );
typedef L_INT (pEXT_CALLBACK pDOCENUMIMAGESCALLBACK)( pDOCHANDLE pDoc, pDOCEDIT_IMAGECALLBACKINFO pImageInfo );
typedef L_INT (pEXT_CALLBACK pDOCENUMVECTORSCALLBACK)( pDOCHANDLE pDocHandle, pDOCEDIT_VECTORCALLBACKINFO pVectorInfo );

// Structure passed when document Event is DOC_EVENT_GETPASSWORD
typedef struct _DOCPASSWORDEVENT
{
   L_INT    nSize;
   L_CHAR   pszPassword[DOC_MAX_PASSWORD_LEN];
   
} DOCPASSWORDEVENTDATA, *pDOCPASSWORDEVENTDATA;

typedef struct _DOCPAGEMARGINS
{
   L_INT    nSize;
   L_FLOAT  fMarginLeft;
   L_FLOAT  fMarginRight;
   L_FLOAT  fMarginTop;
   L_FLOAT  fMarginBottom;

} DOCPAGEMARGINS , * pDOCPAGEMARGINS;


typedef struct _DOCEDITINSERTOPTIONS
{
   L_INT                 nWidth;
   L_INT                 nHeight;
   DOCUMENT_OBJTEXTALIGN ObjAlign;
   L_INT                 nHSpace;
   L_INT                 nVSpace;
}
DOCEDITINSERTOPTIONS, L_FAR *pDOCEDITINSERTOPTIONS;

/* Ldkrn_.h */ 
typedef struct _DOC_DOCIMAGEDATA
{
   L_CHAR L_FAR * pImageDataBuffer;/*Buffer containing 
   image data as it appears in the file (not as a raw bit map!)*/
   L_UINT               uSize;// size of the buffer                   
   L_INT                nWidth;// image width 
   L_INT                nHeight;// image height 
} DOC_DOCIMAGEDATA, *pDOC_DOCIMAGEDATA;

// define the properties of a table 
typedef struct _DOC_TABLEPROPERTIES
{
   DOCUMENT_SPECIALSIZEUNIT UnitsUsed    ;// units used with Cellpadding,Cellspacing,nHeight,nWidth
   DOCUMENT_OBJECT_ALIGN    TableAlign   ;// table alignement
   L_INT           nBodrerWidth ;// width (in pixels) of the border to be drawn around the table 
   L_INT           CellPadding  ;//Integer that specifies the amount of space between the border
   //and the content , note that this value depends on the value of UnitsUsed
   L_INT           CellSpacing  ;// Integer that specifies the amount of space between cells
   //note that this value depends on the value of UnitsUsed
   L_INT           nNumOfCols   ;// Integer that specifies the number of columns
   L_INT           nHeight      ;// Integer that specifies the height of the table,
   // if UnitsUsed = SPECIALSIZEUNIT_PERCENTAGE then this value is a percentage of 
   // the height of the parent object.
   L_INT           nWidth       ;// Integer that specifies the width of the table,
   // if UnitsUsed = SPECIALSIZEUNIT_PERCENTAGE then this value is a percentage of 
   // the width of the parent object.   
} DOC_TABLEPROPERTIES ,L_FAR * pDOC_TABLEPROPERTIES;

/* Used to define font properties in an object style */
typedef struct _DOC_FONTPROPERTIES
{
   TCHAR    fpFontFamily[FP_FONTFAMILYSIZE];    
   DOCUMENT_SIZEUNIT fpFontSizeUnit; // this value must be set if fpFontSize is set 
   L_FLOAT  fpFontSize;/* this value depends on the value of fpFontSizeUnit , if 
   fpFontSizeUnit is set to  UNIT_PERCENTAGE then this value is a percentage of the parent
   object's font size , for example if the parent is a pargraph then this is a 
   percent of the font size set for that pargraph */
   DOCUMENT_FONTSTYLE   fpFontStyle;
   DOCUMENT_FONTVARIANT fpFontVariant;
   DOCUMENT_FONTWEIGHT  fpFontWeight;
} DOC_FONTPROPERTIES, L_FAR * pDOC_FONTPROPERTIES;


/* Used to define text properties in an object style */

typedef struct _DOC_TEXTPROPERTIES
{      
   L_FLOAT  fTextIndent ; /* Text indent , if SizeUnit is set to UNIT_PERCENTAGE then 
   this value is a percentage of the width of the parent object. */
   DOCUMENT_TEXTALIGN TextAlign ;
   DOCUMENT_TEXT_DECORATION TextDecoration ; 
   DOCUMENT_TEXTTRANSFORM   TextTransform ;
   DOCUMENT_VERTICALALIGNMENT VerticalAlignment ;    
   DOCUMENT_SIZEUNIT SizeUnit;// this value must be set if either fTextIndent or fLineHeight is set 
   L_FLOAT  fLineHeight ; /* Distance between lines in the object, if SizeUnit is set 
   to UNIT_PERCENTAGE  then this value is a percentage of the height of the parent object. */
} DOC_TEXTPROPERTIES, L_FAR * pDOC_TEXTPROPERTIES;


/* used to define containg box properties in an object style */

typedef struct _DOC_BOXPROPERTIES
{
   L_FLOAT  fMarginTop ;/*height of the top margin of the object
   if SizeUnit is set to UNIT_PERCENTAGE then this value is a percentage of the 
   height of the parent object.*/   
   L_FLOAT  fMarginRight ;/*width of the right margin of the object if
    SizeUnit is set to UNIT_PERCENTAGE then this value is a 
   percentage of the width of the parent object.*/   
   L_FLOAT  fMarginLeft ;/* width of the left margin of the object. if SizeUnit is set 
   to UNIT_PERCENTAGE then this value is a percentage of the width of the parent object.*/   
   L_FLOAT  fMarginBottom ;/*height of the bottom margin of the object.If  SizeUnit is
   set to UNIT_PERCENTAGE then this value is a percentage of the height of the parent object.*/   
   L_FLOAT  fPaddingTop ;/*amount of space to insert between the top border of the object 
   and the content , if SizeUnit is set to UNIT_PERCENTAGE then this value is 
   a percentage of the width of the parent object.*/   
   L_FLOAT  fPaddingRight ;/*amount of space to insert between the right border of the object 
   and the content , if SizeUnit is set to UNIT_PERCENTAGE  then this 
   value is a percentage of the width of the parent object.*/   
   L_FLOAT  fPaddingLeft ;/*amount of space to insert between the left border of 
   the object and the content. If SizeUnit is set to UNIT_PERCENTAGE then this 
   value is a percentage of the width of the parent object.*/   
   L_FLOAT  fPaddingBottom ;/* amount of space to insert between the bottom border of the 
   object and the content. If SizeUnit is set to UNIT_PERCENTAGE then 
   this value is a percentage of the width of the parent object. */
   DOCUMENT_SIZEUNIT SizeUnit;// this value must be set if any of the other members is set    

} DOC_BOXPROPERTIES, L_FAR * pDOC_BOXPROPERTIES;


/* used to specify the properties of the borders of an object */
typedef struct _DOC_BORDERPROPERTIES
{  
   L_UINT32 uBorderFlags;/* specifies on which sides we have borders ,
   it's the oring of any of the following :
   BORDER_LEFT   boder on the left   side 
   BORDER_RIGHT  boder on the right  side 
   BORDER_TOP    boder on the top    side 
   BORDER_BOTTOM boder on the bottom side  */
   DOCUMENT_BORDERSTYLE BorderStyle    ;// style of the border    
   L_FLOAT     fBorderWidth   ;// width of the border    
   DOCUMENT_SIZEUNIT    BorderWidthSizeUnit ;// this value must be set if the border width is set 
   COLORREF    crBorderColor ;// color of the border                            
} DOC_BORDERPROPERTIES , L_FAR * pDOC_BORDERPROPERTIES;


typedef struct _DOC_POSITIONINGPROPERTIES
{
   DOCUMENT_FLOATING Float ;
   DOCUMENT_CLEAR    Clearing ;
   L_FLOAT  fWidth ;/*width of the object. If SizeUnit set to UNIT_PERCENTAGE  then this 
   value is a percentage of the width of the parent object.*/   
   L_FLOAT  fHeight;/*height of the object. If SizeUnit set to UNIT_PERCENTAGE  then this 
   value is a percentage of the height of the parent object.*/
   L_FLOAT  fLeft;/*position of the object relative to the left edge of the next 
   positioned object in the document, If SizeUnit is set to UNIT_PERCENTAGE then
   this value is a percentage of the width of the parent object. */   
   L_FLOAT  fTop;/*the position of the object relative to the top of the next positioned 
   object in the document . If  SizeUnit is set to UNIT_PERCENTAGE
   then this value is a percentage of the height of the parent object.*/
   DOCUMENT_SIZEUNIT SizeUnit;// this value must be set if fWidth,fHeight,fLeft or fRight  is set
   DOCUMENT_POSITIONINGTYPE PositioningType ;
   DOCUMENT_OBJECTVISIBILITY ObjectVisibility;
   DOCUMENT_OBJECTOVERFLOW   ObjectOverflow;/*how to manage the content of the object when the content 
   exceeds the height and/or width of the object.*/ 
   L_UINT   uZ_Index;// z-index

} DOC_POSITIONINGPROPERTIES , L_FAR * pDOC_POSITIONINGPROPERTIES;

// define the horizontal and vertical spacing properties of an object or image
typedef struct _HORVERSPACEPROP
{
   L_INT nHSpace; // amount of horizontal space for the object in pixels 
   L_INT nVSpace; // amount of vertical   space for the object in pixels 

} DOC_HORVERSPACEPROP , *pDOC_HORVERSPACEPROP;

typedef struct _HOBJECTSTYLE
{
   L_VOID *pData;

}HOBJECTSTYLE, *pHOBJECTSTYLE;

#define CLASS_ID_LENGTH  37

typedef struct _DOCEDIT_ACTIVEXINFO
{
   CHAR  clsid[ CLASS_ID_LENGTH ];
   L_INT nWidth;
   L_INT nHeight;
   DOCUMENT_OBJTEXTALIGN ObjAlign;
   L_INT nHSpace;
   L_INT nVSpace;

}DOCEDIT_ACTIVEXINFO, *pDOCEDIT_ACTIVEXINFO;

typedef struct DOCEDIT_ACTIVEXPARAMETER
{
   CHAR szName[ L_MAXPATH ];
   CHAR szValue[ L_MAXPATH ];

}DOCEDIT_ACTIVEXPARAMETER, *pDOCEDIT_ACTIVEXPARAMETER;


typedef struct _DOCEDIT_ACTIVEXPARAMS
{
   L_UINT uCount;
   pDOCEDIT_ACTIVEXPARAMETER pParamList;   

}DOCEDIT_ACTIVEXPARAMS, *pDOCEDIT_ACTIVEXPARAMS;

typedef struct _DOC_SENDBYMAILINFO
{   
   L_CHAR *pszSubject;
   L_CHAR *pszTo;
   L_CHAR *pszCc;
   L_CHAR *pszBcc;
   
   L_BOOL bAsAttachment;
   L_CHAR *pszAttachmentName;

   DOC_SENDBYMAILFORMAT SendFormat;

}DOC_SENDBYMAILINFO, *pDOC_SENDBYMAILINFO;




/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Functions.                                                           []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/

#ifdef __cplusplus
extern "C"
{
#endif

L_INT EXT_FUNCTION L_DocInit( pDOCHANDLE pDoc);
L_VOID EXT_FUNCTION L_DocFree( pDOCHANDLE pDoc);
L_INT EXT_FUNCTION L_DocSetOptions( pDOCHANDLE pDoc, pDOCEDIT_OPTIONS pOption );
L_INT EXT_FUNCTION L_DocGetOptions( pDOCHANDLE pDoc, pDOCEDIT_OPTIONS pOption );
L_INT EXT_FUNCTION L_DocSendbyMail( pDOCHANDLE pDoc,
                                    L_UINT32 *puStatusMode,                                     
                                    pDOC_SENDBYMAILINFO pSendInfo,
                                    L_BOOL bUserInterface
                                    );

L_INT EXT_FUNCTION L_DocSetImagesPathName( LPCSTR lpPathName );
L_INT EXT_FUNCTION L_DocGetImagesPathName( LPTSTR lpPathName );
L_INT EXT_FUNCTION L_DocSetVectorPathName( LPCSTR lpPathName );
L_INT EXT_FUNCTION L_DocGetVectorPathName( LPTSTR lpPathName );
L_INT EXT_FUNCTION L_DocSetEventCallBack( pDOCHANDLE pDoc, pDOCEVENTCALLBACK pDocEventCallback, L_VOID *pUserData );
pDOCEVENTCALLBACK EXT_FUNCTION L_DocGetEventCallBack( pDOCHANDLE pDoc, L_VOID **ppUserData );

typedef L_INT (  pEXT_CALLBACK pCOMMANDCALLBACK)( pCOMMANDDATA pCommandData );

L_INT EXT_FUNCTION L_DocEditSetMode( pDOCHANDLE  pDoc, L_UINT32* puStatusMode, L_INT nEditMode );
L_INT EXT_FUNCTION L_DocEditLock( pDOCHANDLE  pDoc, L_BOOL bLock );
L_INT EXT_FUNCTION L_DocIsEditLocked( pDOCHANDLE pDoc, L_BOOL *bLock );

L_INT EXT_FUNCTION L_DocEditCopy( pDOCHANDLE  pDoc, L_UINT32* puStatusMode );
L_INT EXT_FUNCTION L_DocEditCut( pDOCHANDLE pDoc, L_UINT32* puStatusMode );
L_INT EXT_FUNCTION L_DocEditDelete( pDOCHANDLE pDoc, L_UINT32* puStatusMode );
L_INT EXT_FUNCTION L_DocEditPaste( pDOCHANDLE pDoc, L_UINT32* puStatusMode );
L_INT EXT_FUNCTION L_DocEditRedo( pDOCHANDLE pDoc, L_UINT32* puStatusMode );
L_INT EXT_FUNCTION L_DocEditSelectAll( pDOCHANDLE pDoc, L_UINT32* puStatusMode );
L_INT EXT_FUNCTION L_DocEditUndo( pDOCHANDLE pDoc, L_UINT32* puStatusMode );

L_INT EXT_FUNCTION L_DocEditSetTabSize( pDOCHANDLE pDoc, L_INT nTabsize );
L_INT EXT_FUNCTION L_DocEditGetTabSize( pDOCHANDLE pDoc, L_INT *pnTabsize );

L_INT EXT_FUNCTION L_DocEditRemoveFormat( pDOCHANDLE pDoc, L_UINT32* puStatusMode );
L_INT EXT_FUNCTION L_DocEditGetValidFormat( pDOCHANDLE pDoc, L_UINT32* puStatusMode, pVALIDFORMAT pValidFormat );
L_INT EXT_FUNCTION L_DocEditSetFormat( pDOCHANDLE pDoc, L_UINT32* puStatusMode, L_CHAR * pFormat );
L_INT EXT_FUNCTION L_DocEditGetFormat( pDOCHANDLE pDoc, 
                                       L_UINT32* puStatusMode,
                                       L_CHAR * pFormat,
                                       L_INT nSize
                                       );



L_INT EXT_FUNCTION L_DocEditBold( pDOCHANDLE pDoc, L_UINT32* puStatusMode );

L_INT EXT_FUNCTION L_DocEditGetFontName( pDOCHANDLE pDoc, 
                                         L_UINT32* puStatusMode,
                                         L_CHAR* pFontName,
                                         L_INT nSize
                                         );
L_INT EXT_FUNCTION L_DocEditSetFontName( pDOCHANDLE pDoc, L_UINT32* puStatusMode, L_CHAR* pFontName );
L_INT EXT_FUNCTION L_DocEditGetFontSize( pDOCHANDLE pDoc, L_UINT32* puStatusMode, L_INT *pnSize );
L_INT EXT_FUNCTION L_DocEditSetFontSize( pDOCHANDLE pDoc, L_UINT32* puStatusMode, L_INT nSize );

L_INT EXT_FUNCTION L_DocEditItalic( pDOCHANDLE pDoc, L_UINT32* puStatusMode );
L_INT EXT_FUNCTION L_DocEditUnderLine( pDOCHANDLE  pDoc, L_UINT32* puStatusMode );

L_INT EXT_FUNCTION L_DocEditCreateHyperLink( pDOCHANDLE pDoc, L_UINT32* puStatusMode,  L_CHAR* pLink );
L_INT EXT_FUNCTION L_DocEditGetHyperLink( pDOCHANDLE pDoc, 
                                          L_UINT32* puStatusMode, 
                                          L_CHAR* pLink,
                                          L_INT nSize
                                          );
L_INT EXT_FUNCTION L_DocEditUnlink( pDOCHANDLE pDoc, L_UINT32* puStatusMode );

L_INT EXT_FUNCTION L_DocEditSetBackColor( pDOCHANDLE pDoc, L_UINT32* puStatusMode, COLORREF cColor );
L_INT EXT_FUNCTION L_DocEditGetBackColor( pDOCHANDLE pDoc, L_UINT32* puStatusMode, COLORREF* pcColor );
L_INT EXT_FUNCTION L_DocEditSetForeColor( pDOCHANDLE pDoc, L_UINT32* puStatusMode, COLORREF cColor );
L_INT EXT_FUNCTION L_DocEditGetForeColor( pDOCHANDLE pDoc, L_UINT32* puStatusMode, COLORREF* pcColor );

L_INT EXT_FUNCTION L_DocEditDeleteCells( pDOCHANDLE pDoc, L_UINT32* puStatusMode );
L_INT EXT_FUNCTION L_DocEditDeleteCols( pDOCHANDLE pDoc, L_UINT32* puStatusMode );
L_INT EXT_FUNCTION L_DocEditDeleteRows( pDOCHANDLE pDoc, L_UINT32* puStatusMode );
L_INT EXT_FUNCTION L_DocEditInsertCell( pDOCHANDLE pDoc, L_UINT32* puStatusMode );
L_INT EXT_FUNCTION L_DocEditInsertCol( pDOCHANDLE pDoc, L_UINT32* puStatusMode );
L_INT EXT_FUNCTION L_DocEditInsertRow( pDOCHANDLE pDoc, L_UINT32* puStatusMode );
L_INT EXT_FUNCTION L_DocEditInsertTable( pDOCHANDLE  pDoc, L_UINT32* puStatusMode, pDOCEDITTABLE pTable );
L_INT EXT_FUNCTION L_DocEditMergeCells( pDOCHANDLE pDoc, L_UINT32* puStatusMode );
L_INT EXT_FUNCTION L_DocEditSplitCell( pDOCHANDLE pDoc, L_UINT32* puStatusMode );

L_INT EXT_FUNCTION L_DocEditPrint( pDOCHANDLE pDoc, L_UINT32* puStatusMode ); 
L_INT EXT_FUNCTION L_DocEditDlgPrint( pDOCHANDLE pDoc, L_UINT32* puStatusMode ); 

L_INT EXT_FUNCTION L_DocEditJustify( pDOCHANDLE pDoc, L_UINT32* puStatusMode, L_INT nJustify );
L_INT EXT_FUNCTION L_DocEditShowBorders( pDOCHANDLE pDoc, L_UINT32* puStatusMode, L_BOOL bBorder );

L_INT EXT_FUNCTION L_DocEditDlgFind( pDOCHANDLE pDoc, L_UINT32* puStatusMode );

L_INT EXT_FUNCTION L_DocEditBullets( pDOCHANDLE pDoc, L_UINT32* puStatusMode );
L_INT EXT_FUNCTION L_DocEditNumbers( pDOCHANDLE pDoc, L_UINT32* puStatusMode );

L_INT EXT_FUNCTION L_DocEditIndentParagraph( pDOCHANDLE pDoc, L_UINT32* puStatusMode, L_BOOL bIndent );

L_INT EXT_FUNCTION L_DocEditSetWndColor( pDOCHANDLE pDoc, L_UINT32* puStatusMode, COLORREF Color );
L_INT EXT_FUNCTION L_DocEditGetWndColor( pDOCHANDLE pDoc, L_UINT32* puStatusMode, COLORREF* pColor );

L_INT EXT_FUNCTION L_DocEditSetCommandCallBack( pDOCHANDLE pDoc,
                                                L_UINT32* puStatusMode,
                                                pCOMMANDCALLBACK pCommandCallBack,
                                                L_VOID * pUserData
                                                );
L_INT EXT_FUNCTION L_DocEditGetWnd( pDOCHANDLE pDoc, L_UINT32* puStatusMode, HWND * phWnd );
L_INT EXT_FUNCTION L_DocEditDestroyWnd( pDOCHANDLE pDoc, L_UINT32* puStatusMode );
HWND  EXT_FUNCTION L_DocEditCreateWnd( pDOCHANDLE pDoc, 
                                       L_UINT32* puStatusMode,
                                       HWND hWndParent,
                                       RECT* pRect
                                       );

L_INT EXT_FUNCTION L_DocEditPreTranslateMessage( pDOCHANDLE pDoc, L_UINT32* puStatusMode, MSG* pMsg );

L_INT EXT_FUNCTION L_DocEditSetPageWidth( pDOCHANDLE pDoc, L_UINT32* puStatusMode, L_INT nWidth );
L_INT EXT_FUNCTION L_DocEditGetPageWidth( pDOCHANDLE pDoc, L_UINT32* puStatusMode, L_INT* pnWidth );
L_INT EXT_FUNCTION L_DocEditSetPageMargins( pDOCHANDLE pDoc, L_UINT32* puStatusMode, pDOCPAGEMARGINS pDocPageMargins );
L_INT EXT_FUNCTION L_DocEditGetPageMargins( pDOCHANDLE pDoc, L_UINT32* puStatusMode, pDOCPAGEMARGINS pDocPageMargins );

L_INT EXT_FUNCTION L_DocEditIsDirty( pDOCHANDLE pDoc, L_UINT32* puStatusMode, L_BOOL* pbDirty );

//L_INT EXT_FUNCTION L_DocEditRealize( pDOCHANDLE pDoc, L_UINT32* puStatusMode, pBITMAPHANDLE pBitmapHandle );

L_INT EXT_FUNCTION L_DocEditAddVectorDrawing( pDOCHANDLE pDoc,
                                              L_UINT32* puStatusMode,
                                              pVECTORHANDLE pVectorHandle,
                                              L_INT nWidth,
                                              L_INT nHeight,
                                              DOCUMENT_OBJTEXTALIGN ObjAlign,
                                              L_INT nHSpace,
                                              L_INT nVSpace
                                              );
L_INT EXT_FUNCTION L_DocEditAddVectorDrawingFile( pDOCHANDLE pDoc,
                                                  L_UINT32* puStatusMode,
                                                  L_CHAR *pszPath,
                                                  L_INT nWidth,
                                                  L_INT nHeight,
                                                  DOCUMENT_OBJTEXTALIGN ObjAlign,
                                                  L_INT nHSpace,
                                                  L_INT nVSpace
                                                  );
L_INT EXT_FUNCTION L_DocEditAddVectorDrawingMemory( pDOCHANDLE pDoc,
                                                    L_UINT32* puStatusMode,
                                                    L_CHAR *pData,
                                                    L_INT32 nSize,
                                                    L_INT nWidth,
                                                    L_INT nHeight,
                                                    DOCUMENT_OBJTEXTALIGN ObjAlign,
                                                    L_INT nHSpace,
                                                    L_INT nVSpace
                                                    );

L_INT EXT_FUNCTION L_DocEditAddRasterImage( pDOCHANDLE pDoc,
                                            L_UINT32* puStatusMode,
                                            pBITMAPHANDLE pBitmap,
                                            L_INT nWidth,
                                            L_INT nHeight,
                                            DOCUMENT_OBJTEXTALIGN ObjAlign,
                                            L_INT nHSpace,
                                            L_INT nVSpace
                                            );
L_INT EXT_FUNCTION L_DocEditAddRasterImageFile( pDOCHANDLE pDoc,
                                                L_UINT32* puStatusMode,
                                                L_CHAR *pszPath,
                                                L_INT nWidth,
                                                L_INT nHeight,
                                                DOCUMENT_OBJTEXTALIGN ObjAlign,
                                                L_INT nHSpace,
                                                L_INT nVSpace
                                                );
L_INT EXT_FUNCTION L_DocEditAddRasterImageMemory( pDOCHANDLE pDoc,
                                                  L_UINT32* puStatusMode,
                                                  L_CHAR *pData,
                                                  L_INT32 nSize,
                                                  L_INT nWidth,
                                                  L_INT nHeight,
                                                  DOCUMENT_OBJTEXTALIGN ObjAlign,
                                                  L_INT nHSpace,
                                                  L_INT nVSpace
                                                  );

L_INT EXT_FUNCTION L_DocEditInsertActiveX( pDOCHANDLE pDoc, 
                                           L_UINT32* puStatusMode, 
                                           pDOCEDIT_ACTIVEXINFO pActiveXInfo, 
                                           pDOCEDIT_ACTIVEXPARAMS pParameters 
                                           );

/* Image processing */ 
L_INT EXT_FUNCTION L_DocEditGetImage( pDOCHANDLE pDoc, L_UINT32* puStatusMode, pBITMAPHANDLE phBitmap );
L_INT EXT_FUNCTION L_DocEditSetImage( pDOCHANDLE pDoc, L_UINT32* puStatusMode, pBITMAPHANDLE phBitmap );

L_INT EXT_FUNCTION L_DocDlgInsertRaster( HWND hWnd, 
                                         pDOCHANDLE pDoc, 
                                         pBITMAPHANDLE pBitmap, 
                                         pDOCEDITINSERTOPTIONS pOptions, 
                                         L_UINT32 dwFlags 
                                         );
L_INT EXT_FUNCTION L_DocDlgInsertVector( HWND hWnd, 
                                         pDOCHANDLE pDoc, 
                                         pVECTORHANDLE pVector, 
                                         pDOCEDITINSERTOPTIONS pOptions, 
                                         L_UINT32 dwFlags 
                                         );

L_INT EXT_FUNCTION L_DocDlgFind( pDOCHANDLE pDoc, L_UINT32* puStatusMode );
L_INT EXT_FUNCTION L_DocDlgSetFindDlgIcon( HICON hNewIcon);
HICON EXT_FUNCTION L_DocDlgGetFindDlgIcon( );
L_INT EXT_FUNCTION L_DocDlgFont( pDOCHANDLE pDoc, L_UINT32* puStatusMode );
L_INT EXT_FUNCTION L_DocDlgGetStringLen( L_UINT32 uString, L_UINT *puLen );
L_INT EXT_FUNCTION L_DocDlgGetString( L_UINT32 uString, L_CHAR *pszString );
L_INT EXT_FUNCTION L_DocDlgSetString( L_UINT32 uString, L_CHAR *pszString );
HFONT EXT_FUNCTION L_DocDlgSetFont( HFONT hFont );

L_INT EXT_FUNCTION L_DocEditOverwriteText( pDOCHANDLE pDoc, L_UINT32* puStatusMode, L_BOOL bOverwrite );
L_INT EXT_FUNCTION L_DocEditInsertEndnote( pDOCHANDLE pDoc, L_UINT32* puStatusMode, L_CHAR *pszNote );


/* bookmarks */ 
L_INT EXT_FUNCTION L_DocEditAddBookmark( pDOCHANDLE pDoc, L_UINT32* puStatusMode, L_CHAR* pBookmark );
L_INT EXT_FUNCTION L_DocEditRemoveBookmark( pDOCHANDLE pDoc, L_UINT32* puStatusMode );
L_INT EXT_FUNCTION L_DocEditGetBookmarks( pDOCHANDLE pDoc, L_UINT32* puStatusMode, pDOCBOOKMARKS pBookmarks  );
L_INT EXT_FUNCTION L_DocEditGotoBookmark( pDOCHANDLE pDoc, L_UINT32* puStatusMode, L_CHAR* pBookmark );

/* Enumeration */ 
L_INT EXT_FUNCTION L_DocEnumImages( pDOCHANDLE pDoc, pDOCENUMIMAGESCALLBACK pEnumImages, L_VOID *pUserData );
L_INT EXT_FUNCTION L_DocEnumVectors( pDOCHANDLE pDoc, pDOCENUMVECTORSCALLBACK pEnumVectors, L_VOID *pUserData  );

/* Object style control */ 
L_INT EXT_FUNCTION L_DocStyleInit( pHOBJECTSTYLE pObjStyle );
L_INT EXT_FUNCTION L_DocStyleFree( pHOBJECTSTYLE pObjStyle );
L_INT EXT_FUNCTION L_DocStyleSetFontProperties( pHOBJECTSTYLE pObjStyle, pDOC_FONTPROPERTIES pFontProperties );
L_INT EXT_FUNCTION L_DocStyleSetTextProperties( pHOBJECTSTYLE pObjStyle, pDOC_TEXTPROPERTIES pTextProperties );
L_INT EXT_FUNCTION L_DocStyleSetBoxProperties( pHOBJECTSTYLE pObjStyle, pDOC_BOXPROPERTIES pBoxProperties );
L_INT EXT_FUNCTION L_DocStyleSetBorderProperties( pHOBJECTSTYLE pObjStyle, pDOC_BORDERPROPERTIES pBorderProperties );
L_INT EXT_FUNCTION L_DocStyleSetPositioningProperties( pHOBJECTSTYLE pObjStyle, pDOC_POSITIONINGPROPERTIES pPositioningProperties );
L_INT EXT_FUNCTION L_DocStyleSetTextColor( pHOBJECTSTYLE pObjStyle, COLORREF crTextColor );
L_INT EXT_FUNCTION L_DocStyleSetTextBackColor( pHOBJECTSTYLE pObjStyle, COLORREF crTextBgColor );
L_INT EXT_FUNCTION L_DocStyleSetClass( pHOBJECTSTYLE pObjStyle, LPCSTR pszClass );
L_INT EXT_FUNCTION L_DocStyleReset( pHOBJECTSTYLE pObjStyle );

/* Exports from LDocHandle */    
L_INT EXT_FUNCTION L_DocExBeginDocBody( pDOCHANDLE pDoc, pDOCPAGEMARGINS pDocPageMargins/* = NULL */ );
L_INT EXT_FUNCTION L_DocExInsertAsciiText( pDOCHANDLE pDoc, L_CHAR *pBuffer, L_UINT uSize );
L_INT EXT_FUNCTION L_DocExAddCharacter( pDOCHANDLE pDoc, L_CHAR cChar );
L_INT EXT_FUNCTION L_DocExInsertHtmlText( pDOCHANDLE pDoc, L_CHAR * pBuffer, L_UINT uSize );   
L_INT EXT_FUNCTION L_DocExInsertTab( pDOCHANDLE pDoc );

L_INT EXT_FUNCTION L_DocExAddImage( pDOCHANDLE pDoc, 
                                    LPCSTR lpImageFileName, 
                                    L_INT  nWidth, 
                                    L_INT  nHeight,
                                    LPCSTR lpClassName/* = NULL */, 
                                    LPCSTR lpId/* = NULL*/, 
                                    DOCUMENT_OBJTEXTALIGN ObjTextAlign/* = DOC_OBJTEXTALIGN_BASELINE*/,
                                    DOCUMENT_IMGTYPE ImgType/* = DOC_IMGTYPE_UNSPECIFIED */, 
                                    pDOC_HORVERSPACEPROP pHorVerSpaceProp/* =NULL*/, 
                                    pHOBJECTSTYLE pImgStyle/* = NULL */ 
                                    );

L_INT EXT_FUNCTION L_DocExAddImageMemory( pDOCHANDLE pDoc, 
                                          pDOC_DOCIMAGEDATA pImageData , 
                                          LPCSTR lpClassName/* = NULL */, 
                                          LPCSTR lpId/* = NULL*/ , 
                                          DOCUMENT_OBJTEXTALIGN ObjTextAlign/* = DOC_OBJTEXTALIGN_BASELINE*/, 
                                          DOCUMENT_IMGTYPE ImgType/* = DOC_IMGTYPE_UNSPECIFIED */,
                                          pDOC_HORVERSPACEPROP pHorVerSpaceProp/* =NULL */ , 
                                          pHOBJECTSTYLE pImgStyle/* = NULL*/ 
                                          );

L_INT EXT_FUNCTION L_DocExAddVector( pDOCHANDLE pDoc, 
                                     pVECTORHANDLE pVectorHandle, 
                                     L_INT nWidth, L_INT nHeight,
                                     LPCSTR lpClassName/* = NULL*/, 
                                     LPCSTR lpId/* = NULL*/, 
                                     DOCUMENT_OBJTEXTALIGN ObjTextAlign/* = DOC_OBJTEXTALIGN_BASELINE*/,
                                     pDOC_HORVERSPACEPROP pHorVerSpaceProp/* =NULL */, 
                                     pHOBJECTSTYLE pObjStyle/* = NULL */ 
                                     );

L_INT EXT_FUNCTION L_DocExBeginNewTextFormat( pDOCHANDLE pDoc, DOCUMENT_TEXT_FORMAT NewTextFormat );
L_INT EXT_FUNCTION L_DocExEndTextFormat( pDOCHANDLE pDoc, DOCUMENT_TEXT_FORMAT TextFormatToEnd );
L_INT EXT_FUNCTION L_DocExSetTextColor( pDOCHANDLE pDoc, COLORREF crTextColor );
L_INT EXT_FUNCTION L_DocExSetTextBackColor( pDOCHANDLE pDoc, COLORREF crTextBkgndColor );
L_INT EXT_FUNCTION L_DocExSetFontSize( pDOCHANDLE pDoc, L_UINT16 uFontSize );
L_INT EXT_FUNCTION L_DocExSetFontFamilyName( pDOCHANDLE pDoc, LPCSTR szFamilyName );
L_INT EXT_FUNCTION L_DocExBeginTable( pDOCHANDLE pDoc, 
                                      pDOC_TABLEPROPERTIES pTableProperties/* = NULL*/, 
                                      pHOBJECTSTYLE pTableStyle /* = NULL */,
                                      pHOBJECTSTYLE pCelleStyle/* = NULL */ 
                                      );
L_INT EXT_FUNCTION L_DocExEndTable( pDOCHANDLE pDoc );
L_INT EXT_FUNCTION L_DocExBeginRow( pDOCHANDLE pDoc );

L_INT EXT_FUNCTION L_DocExBeginCell( pDOCHANDLE pDoc, 
                                     L_INT nColSpan/* =0*/, 
                                     L_INT nRowSpan/* =0*/, 
                                     DOCUMENT_OBJECT_ALIGN CellAlign/*=DOC_OBJECT_ALIGN_LEFT */,
                                     L_INT  nWidth/* = 0*/, 
                                     DOCUMENT_SPECIALSIZEUNIT UnitsUsed/* =DOC_SPECIALSIZEUNIT_PIXELS */,
                                     pHOBJECTSTYLE pCelleStyle/* = NULL */ 
                                     );

L_INT EXT_FUNCTION L_DocExBeginNewList( pDOCHANDLE pDoc, 
                                        DOCUMENT_LISTTYPE ListType 
                                        );
L_INT EXT_FUNCTION L_DocExEndList( pDOCHANDLE pDoc );
L_INT EXT_FUNCTION L_DocExBeginListItem( pDOCHANDLE pDoc );

L_INT EXT_FUNCTION L_DocExInsertHypertextLink( pDOCHANDLE pDoc, 
                                               LPCSTR pszUrlName, 
                                               LPCSTR pszLinkText, 
                                               LPCSTR pszLinkImagePath 
                                               );

L_INT EXT_FUNCTION L_DocExBeginNewPar( pDOCHANDLE pDoc, 
                                       DOCUMENT_OBJECT_ALIGN ParAlign/* = DOC_OBJECT_ALIGN_LEFT*/, 
                                       pHOBJECTSTYLE pParStyle/* = NULL*/,
                                       LPCSTR pszClass/*=NULL*/, 
                                       DOCUMENT_PARLISTTYPE ParListType/* = DOC_PARLISTTYPE_NON*/,
                                       L_INT nListStartNum/* = 1*/ 
                                       );
L_INT EXT_FUNCTION L_DocExInsertQuotation( pDOCHANDLE pDoc, 
                                           LPCSTR pszQuotationString 
                                           );
L_INT EXT_FUNCTION L_DocExInsertLineBreak( pDOCHANDLE pDoc );

L_INT EXT_FUNCTION L_DocExBeginNewTextDirection( pDOCHANDLE pDoc, DOCUMENT_TEXTDIRECTION NewTextDirection );
L_INT EXT_FUNCTION L_DocExEndNewTextDirection( pDOCHANDLE pDoc );

L_INT EXT_FUNCTION L_DocExBeginNoLineBreak( pDOCHANDLE pDoc );
L_INT EXT_FUNCTION L_DocExEndNoLineBreak( pDOCHANDLE pDoc );
L_INT EXT_FUNCTION L_DocExInsertComment( pDOCHANDLE pDoc, LPCSTR pszCommentString );
L_INT EXT_FUNCTION L_DocExInsertHorizontalRule( pDOCHANDLE pDoc );

L_INT EXT_FUNCTION L_DocExBeginBlockContainer( pDOCHANDLE pDoc, pHOBJECTSTYLE pBlockContainerStyle/* = NULL*/, LPCSTR pszClass/*=NULL */ );
L_INT EXT_FUNCTION L_DocExEndBlockContainer( pDOCHANDLE pDoc );
L_INT EXT_FUNCTION L_DocExBeginInlineContainer( pDOCHANDLE pDoc, pHOBJECTSTYLE pInlineContainerStyle/* = NULL*/, LPCSTR pszClass/*=NULL */ );
L_INT EXT_FUNCTION L_DocExEndInlineContainer( pDOCHANDLE pDoc );

L_INT EXT_FUNCTION L_DocExSetTitle( pDOCHANDLE pDoc, LPCSTR pszTitleString );

L_INT EXT_FUNCTION L_DocExSetPageWidth( pDOCHANDLE pDoc, L_FLOAT fPageWidth );
L_INT EXT_FUNCTION L_DocExSetPageHeight( pDOCHANDLE pDoc, L_FLOAT fPageHeight );

L_INT EXT_FUNCTION L_DocExSetTabSize( pDOCHANDLE pDoc, L_UINT uTabSize );
L_INT EXT_FUNCTION L_DocExGetTabSize( pDOCHANDLE pDoc, L_UINT * puTabSize );

L_INT EXT_FUNCTION L_DocExRealizeData( pDOCHANDLE pDoc );

L_INT EXT_FUNCTION L_DocExBeginStyleSheet( pDOCHANDLE pDoc );
L_INT EXT_FUNCTION L_DocExEndStyleSheet( pDOCHANDLE pDoc );
L_INT EXT_FUNCTION L_DocExAddStyle( pDOCHANDLE pDoc, LPCSTR pszClass, pHOBJECTSTYLE pStyle );


L_INT EXT_FUNCTION L_DocExSetLockState( pDOCHANDLE pDoc, L_BOOL bLock );
L_INT EXT_FUNCTION L_DocExReserve( pDOCHANDLE pDoc, L_UINT32 dwResSize );
L_INT EXT_FUNCTION L_DocExGetUserPassword( pDOCHANDLE pDoc, 
                                           L_CHAR *pszUserPassword 
                                           );

/* FTP support */ 
L_INT EXT_FUNCTION L_DocFTPDlgSend( pDOCHANDLE pDoc, 
                                    L_UINT32* puStatusMode,
                                    pDOC_FTPUPLOADFORMAT pFormat,
                                    L_CHAR *pszServer,
                                    L_INT iPort,
                                    L_CHAR *pszUserName,
												 L_CHAR *pszPassword,                                         
                                    L_CHAR *pszRemote,
                                    L_CHAR *pszFolder
                                    );

L_INT EXT_FUNCTION L_DocFTPConnect( pDOCHANDLE pDoc, 
                                    L_UINT32* puStatusMode,
                                    L_CHAR *pszServer,
                                    L_INT iPort,
                                    L_CHAR *pszUserName,
												 L_CHAR *pszPassword 
                                    );

L_INT EXT_FUNCTION L_DocFTPDisconnect( pDOCHANDLE pDoc,
                                       L_UINT32* puStatusMode
                                       );

L_INT EXT_FUNCTION L_DocFTPChDir( pDOCHANDLE pDoc,
                                  L_UINT32* puStatusMode, 
                                  L_CHAR *pszDirectory
                                  );

L_INT EXT_FUNCTION L_DocFTPSend( pDOCHANDLE pDoc,
                                 L_UINT32* puStatusMode,
                                 DOC_FTPUPLOADFORMAT Format,
                                 L_CHAR *pszRemote
                                 );

#ifdef __cplusplus
};
#endif


#ifdef __cplusplus

class DOCUMENT_EXPORT LDocEditor
{
   private :
      static L_INT CommandCS(pCOMMANDDATA pCommandData);
      friend L_INT CALLBACK EnumImagesCallBack( pDOCHANDLE pDoc, 
                                                pDOCEDIT_IMAGECALLBACKINFO pImageInfo 
                                                );
      friend L_INT CALLBACK EnumVectorsCallBack( pDOCHANDLE pDoc, 
                                                 pDOCEDIT_VECTORCALLBACKINFO pVectorInfo 
                                                 );
      
      HANDLE       m_hFeedLoad;
      DOCHANDLE    m_hDocumentHandle;
      L_BOOL       m_bCallBackEnable ;
      L_VOID       *m_pImageUserData;
      L_VOID       *m_pVectorUserData;
   protected :
      virtual L_INT  CommandCallBack(pCOMMANDDATA pCommandData);
      
       
   public:
      LDocEditor();
      ~LDocEditor();

      L_INT  Initialize();
      L_INT  Free();

      virtual L_INT ImagesCallback( pDOCEDIT_IMAGECALLBACKINFO pImageInfo );
      virtual L_INT VectorsCallback( pDOCEDIT_VECTORCALLBACKINFO pVectorInfo );
      //realize function is not here .

      L_INT  SetMode(L_INT nEditMode,L_UINT32* puStatusMode=NULL);
      L_INT  Copy(L_UINT32* puStatusMode=NULL);
      L_INT  Cut (L_UINT32* puStatusMode=NULL);
      L_INT  Delete(L_UINT32* puStatusMode=NULL);
      L_INT  Paste(L_UINT32* puStatusMode=NULL);
      L_INT  Redo(L_UINT32* puStatusMode=NULL);
      L_INT  SelectAll(L_UINT32* puStatusMode=NULL);
      L_INT  Undo(L_UINT32* puStatusMode=NULL);
      L_INT  RemoveFormat(L_UINT32* puStatusMode=NULL);
      L_INT  Bold(L_UINT32* puStatusMode=NULL);
      L_INT  GetFontName(L_CHAR* pFontName,L_INT nSize,L_UINT32* puStatusMode=NULL);
      L_INT  SetFontName(L_CHAR* pFontName,L_UINT32* puStatusMode=NULL);
      L_INT  GetFontSize(L_INT *pnSize,L_UINT32* puStatusMode=NULL);
      L_INT  SetFontSize(L_INT nSize,L_UINT32* puStatusMode=NULL);
      L_INT  Italic(L_UINT32* puStatusMode=NULL);  
      L_INT  UnderLine(L_UINT32* puStatusMode=NULL); 
      L_INT  CreateHyperLink(L_CHAR* pLink,L_UINT32* puStatusMode=NULL);
      L_INT  GetHyperLink(L_CHAR* pLink,L_INT nSize,L_UINT32* puStatusMode=NULL);
      L_INT  Unlink(L_UINT32* puStatusMode=NULL);
      L_INT  SetBackColor(COLORREF cColor,L_UINT32* puStatusMode=NULL);
      L_INT  GetBackColor(COLORREF* pcColor,L_UINT32* puStatusMode=NULL);
      L_INT  GetForeColor(COLORREF* pcColor,L_UINT32* puStatusMode=NULL);
      L_INT  SetForeColor(COLORREF cColor,L_UINT32* puStatusMode=NULL);
      L_INT  DeleteCells (L_UINT32* puStatusMode=NULL);
      L_INT  DeleteCols  (L_UINT32* puStatusMode=NULL);
      L_INT  DeleteRows  (L_UINT32* puStatusMode=NULL);
      L_INT  InsertCell  (L_UINT32* puStatusMode=NULL);
      L_INT  InsertCol   (L_UINT32* puStatusMode=NULL);
      L_INT  InsertRow   (L_UINT32* puStatusMode=NULL);
      L_INT  InsertTable (pDOCEDITTABLE pTable,L_UINT32* puStatusMode=NULL);
      L_INT  MergeCells  (L_UINT32* puStatusMode=NULL);
      L_INT  SplitCell   (L_UINT32* puStatusMode=NULL);
      L_INT  Print       (L_UINT32* puStatusMode=NULL); 
      L_INT  DlgPrint    (L_UINT32* puStatusMode=NULL); 
      L_INT  Justify     (L_INT nJustify,L_UINT32* puStatusMode=NULL);
      L_INT  ShowBorders (L_BOOL bBorder,L_UINT32* puStatusMode=NULL);
      L_INT  DlgFind     (L_UINT32* puStatusMode=NULL);
      L_INT  Bullets     (L_UINT32* puStatusMode=NULL);
      L_INT  Numbers     (L_UINT32* puStatusMode=NULL);
      L_INT  IndentParagraph(L_BOOL bIndent,L_UINT32* puStatusMode=NULL);
      L_INT  SetWndColor (COLORREF Color,L_UINT32* puStatusMode=NULL);
      L_INT  GetWndColor (COLORREF* pColor,L_UINT32* puStatusMode=NULL);
      L_INT  SetFormat   (L_CHAR * pFormat,L_UINT32* puStatusMode=NULL);
      L_INT  GetFormat   (L_CHAR * pFormat,L_INT nSize,L_UINT32* puStatusMode=NULL);
      L_INT  GetValidFormat(pVALIDFORMAT  pValidFormat,L_UINT32* puStatusMode=NULL);
      L_BOOL EnableCommandCallBack(L_BOOL bEnable=TRUE);
      L_INT  GetWnd(HWND * phWnd,L_UINT32* puStatusMode=NULL);
      HWND   CreateWnd(HWND hWndParent,RECT* pRect,L_UINT32* puStatusMode=NULL);
      L_INT  DestroyWnd(L_UINT32* puStatusMode=NULL);
      L_INT  PreTranslateMessage(MSG* pMsg,L_UINT32* puStatusMode=NULL);
      L_INT  LoadFile(LPSTR pszFile, struct _LOADFILEOPTION /*pLOADFILEOPTION*/ *pLoadOptions );
      L_INT  LoadMemory(L_CHAR * pBuffer, L_UINT32 dwBufferSize, struct _LOADFILEOPTION /*pLOADFILEOPTION*/ *pLoadOptions );      
      L_INT  StartFeedLoad(struct _LOADFILEOPTION /*pLOADFILEOPTION*/ *pLoadOptions );
      L_INT  FeedLoad( L_CHAR *pInBuffer, L_UINT32 dwBufferSize);
      L_INT  StopFeedLoad(  );
      L_INT  SaveFile(LPSTR pszFile,L_INT nFormat,struct _SAVEFILEOPTION /*pSAVEFILEOPTION*/ *pSaveOptions);
      L_INT  SaveMemory(HANDLE *phHandle,L_INT nFormat,L_UINT32 *puSize,struct _SAVEFILEOPTION /*pSAVEFILEOPTION*/ *pSaveOptions);
      L_INT  SetPageWidth(L_INT  nWidth,L_UINT32* puStatusMode=NULL);
      L_INT  GetPageWidth(L_INT* pnWidth,L_UINT32* puStatusMode=NULL);
      L_INT  IsDirty(L_BOOL* pbIsDirty,L_UINT32* puStatusMode=NULL);
      L_INT  SetImagesPathName(LPCSTR lpPathName);
      L_INT  SetVectorPathName(LPCSTR lpPathName);
      //hsa7 L_INT  Realize(LBitmapBase *pLBitmap,L_UINT32* puStatusMode=NULL);

      L_INT  AddVectorDrawing(pVECTORHANDLE pVectorHandle, L_INT nWidth, L_INT nHeight, DOCUMENT_OBJTEXTALIGN ObjAlign, 
                              L_INT nHSpace, L_INT nVSpace, L_UINT32 *puStatusMode = NULL);
      L_INT  AddRasterImage(pBITMAPHANDLE pBitmap, L_INT nWidth, L_INT nHeight, DOCUMENT_OBJTEXTALIGN ObjAlign,
                            L_INT nHSpace, L_INT nVSpace, L_UINT32 *puStatusMode);

      L_INT  InsertRasterDlg(HWND hWnd, pBITMAPHANDLE pBitmap, pDOCEDITINSERTOPTIONS pOptions, L_UINT32 dwFlags);
      L_INT  InsertVectorDlg(HWND hWnd, pVECTORHANDLE pVector, pDOCEDITINSERTOPTIONS pOptions, L_UINT32 dwFlags);
      L_INT  FindDlg(L_UINT32 *puStatusMode=NULL);
      L_INT  SetFindDlgIcon(HICON hNewIcon);
      HICON  GetFindDlgIcon();
      L_INT  FontDlg(L_UINT32* puStatusMode=NULL);
      HFONT  SetFontDlg(HFONT hFont);
      L_UINT GetStringLen(L_UINT32 uString);
      L_INT  GetStringDlg(L_UINT32 uString, L_CHAR *pszString);
      L_INT  SetString(L_UINT32 uString, L_CHAR *pszString);

      /* Options */ 
      L_INT SetOptions( pDOCEDIT_OPTIONS pOption );
      L_INT GetOptions( pDOCEDIT_OPTIONS pOption );
      
      /* mail support */ 
      L_INT SendbyMail( pDOC_SENDBYMAILINFO pSendInfo = NULL,
                        L_BOOL bUserInterface = TRUE,
                        L_UINT32 *puStatusMode = NULL
                        );
      /* Edit locking */ 
      L_INT LockEdit( L_BOOL bLock = TRUE );
      L_INT IsEditLocked( L_BOOL *bLocked );
      
      /* tab size */ 
      L_INT SetTabSize( L_INT nTabsize = DEFAULT_TAB_SIZE );
      L_INT GetTabSize( L_INT *pnTabsize );

      /* vector/raster adding */ 
      L_INT AddVectorDrawingFile( L_CHAR                  *pszPath,
                                  L_INT                   nWidth,
                                  L_INT                   nHeight,
                                  DOCUMENT_OBJTEXTALIGN   ObjAlign = DOC_OBJTEXTALIGN_LEFT,
                                  L_INT                   nHSpace = 0,
                                  L_INT                   nVSpace = 0,
                                  L_UINT32*               puStatusMode = NULL
                                  );
      L_INT AddVectorDrawingMemory( L_CHAR                  *pData,
                                    L_INT32                 nSize,
                                    L_INT                   nWidth,
                                    L_INT                   nHeight,
                                    DOCUMENT_OBJTEXTALIGN   ObjAlign = DOC_OBJTEXTALIGN_LEFT,
                                    L_INT                   nHSpace = 0,
                                    L_INT                   nVSpace = 0,
                                    L_UINT32*               puStatusMode = NULL
                                    );
      L_INT AddRasterImageFile( L_CHAR               *pszPath,
                                L_INT                nWidth,
                                L_INT                nHeight,
                                DOCUMENT_OBJTEXTALIGN ObjAlign = DOC_OBJTEXTALIGN_LEFT,
                                L_INT                nHSpace = 0,
                                L_INT                nVSpace = 0,
                                L_UINT32*            puStatusMode = NULL
                                );
      L_INT AddRasterImageMemory( L_CHAR               *pData,
                                  L_INT32              nSize,
                                  L_INT                nWidth,
                                  L_INT                nHeight,
                                  DOCUMENT_OBJTEXTALIGN ObjAlign = DOC_OBJTEXTALIGN_LEFT,
                                  L_INT                nHSpace = 0,
                                  L_INT                nVSpace = 0,
                                  L_UINT32*            puStatusMode = NULL
                                  );
      /* Active X */ 
      L_INT InsertActiveX( pDOCEDIT_ACTIVEXINFO pActiveXInfo, 
                           pDOCEDIT_ACTIVEXPARAMS pParameters,
                           L_UINT32* puStatusMode = NULL
                           );
      /* Overwrite text */ 
      L_INT OverwriteText( L_BOOL bOverwrite = TRUE,
                           L_UINT32* puStatusMode = NULL
                           );

      /* End note */ 
      L_INT InsertEndnote( L_CHAR *pszNote,
                           L_UINT32* puStatusMode = NULL
                           );
      /* bookmarks */ 
      L_INT AddBookmark( L_CHAR* pBookmark ,
                         L_UINT32* puStatusMode = NULL
                         );
      L_INT RemoveBookmark( L_UINT32* puStatusMode = NULL );
      L_INT GetBookmarks( pDOCBOOKMARKS pBookmarks,
                          L_UINT32* puStatusMode = NULL
                          );
      L_INT GotoBookmark( L_CHAR* pBookmark,
                          L_UINT32* puStatusMode = NULL
                          );

      /* Enumeration */ 
      L_INT EnumImages( L_VOID *pUserData = NULL ); 
      L_INT EnumVectors( L_VOID *pUserData = NULL ); 

      /* Style Object */ 
      L_INT StyleInit( pHOBJECTSTYLE pObjStyle );
      L_INT StyleFree( pHOBJECTSTYLE pObjStyle );
      L_INT StyleSetFontProperties( pHOBJECTSTYLE pObjStyle, 
                                    pDOC_FONTPROPERTIES pFontProperties 
                                    );
      L_INT StyleSetTextProperties( pHOBJECTSTYLE pObjStyle, 
                                    pDOC_TEXTPROPERTIES pTextProperties 
                                    );
      L_INT StyleSetBoxProperties( pHOBJECTSTYLE pObjStyle, 
                                   pDOC_BOXPROPERTIES pBoxProperties 
                                   );
      L_INT StyleSetBorderProperties( pHOBJECTSTYLE pObjStyle, 
                                      pDOC_BORDERPROPERTIES pBorderProperties 
                                      );
      L_INT StyleSetPositioningProperties( pHOBJECTSTYLE pObjStyle, 
                                           pDOC_POSITIONINGPROPERTIES pPositioningProperties 
                                           );
      L_INT StyleSetTextColor( pHOBJECTSTYLE pObjStyle, 
                              COLORREF crTextColor 
                              );
      L_INT StyleSetTextBackColor( pHOBJECTSTYLE pObjStyle, 
                                         COLORREF crTextBgColor
                                         );
      L_INT StyleSetClass( pHOBJECTSTYLE pObjStyle, 
                           LPCSTR pszClass 
                           );
      L_INT StyleReset( pHOBJECTSTYLE pObjStyle );

      /* Exports from LDocHandle */    
      L_INT ExBeginDocBody( pDOCPAGEMARGINS pDocPageMargins = NULL );
      L_INT ExInsertAsciiText( L_CHAR * pBuffer,
                               L_UINT uSize 
                               );
      L_INT ExAddCharacter( L_CHAR cChar );
      L_INT ExInsertHtmlText( L_CHAR * pBuffer,
                              L_UINT uSize 
                              );   
      L_INT ExInsertTab( );
      L_INT ExAddImageMemory( pDOC_DOCIMAGEDATA pImageData , 
                              LPCSTR lpClassName = NULL , 
                              LPCSTR lpId = NULL , 
                              DOCUMENT_OBJTEXTALIGN ObjTextAlign = DOC_OBJTEXTALIGN_BASELINE, 
                              DOCUMENT_IMGTYPE ImgType = DOC_IMGTYPE_UNSPECIFIED ,
                              pDOC_HORVERSPACEPROP pHorVerSpaceProp = NULL  , 
                              pHOBJECTSTYLE pImgStyle = NULL 
                              );
      L_INT ExAddImage( LPCSTR lpImageFileName, 
                        L_INT  nWidth, 
                        L_INT  nHeight,
                        LPCSTR lpClassName = NULL , 
                        LPCSTR lpId = NULL, 
                        DOCUMENT_OBJTEXTALIGN ObjTextAlign = DOC_OBJTEXTALIGN_BASELINE,
                        DOCUMENT_IMGTYPE ImgType = DOC_IMGTYPE_UNSPECIFIED , 
                        pDOC_HORVERSPACEPROP pHorVerSpaceProp =NULL, 
                        pHOBJECTSTYLE pImgStyle = NULL  
                        );

      L_INT ExAddVector( pVECTORHANDLE pVectorHandle, 
                         L_INT nWidth, L_INT nHeight,
                         LPCSTR lpClassName = NULL, 
                         LPCSTR lpId = NULL, 
                         DOCUMENT_OBJTEXTALIGN ObjTextAlign = DOC_OBJTEXTALIGN_BASELINE,
                         pDOC_HORVERSPACEPROP pHorVerSpaceProp =NULL , 
                         pHOBJECTSTYLE pObjStyle = NULL  
                         );

      L_INT ExBeginNewTextFormat( DOCUMENT_TEXT_FORMAT NewTextFormat );
      L_INT ExEndTextFormat( DOCUMENT_TEXT_FORMAT TextFormatToEnd );
      L_INT ExSetTextColor( COLORREF crTextColor );
      L_INT ExSetTextBackColor( COLORREF crTextBkgndColor );
      L_INT ExSetFontSize( L_UINT16 uFontSize );
      L_INT ExSetFontFamilyName( LPCSTR szFamilyName );
      L_INT ExBeginTable( pDOC_TABLEPROPERTIES pTableProperties = NULL, 
                          pHOBJECTSTYLE pTableStyle  = NULL ,
                          pHOBJECTSTYLE pCelleStyle = NULL  
                          );
      L_INT ExEndTable( );
      L_INT ExBeginRow( );

      L_INT ExBeginCell( L_INT nColSpan =0, 
                         L_INT nRowSpan =0, 
                         DOCUMENT_OBJECT_ALIGN CellAlign = DOC_OBJECT_ALIGN_LEFT ,
                         L_INT  nWidth = 0, 
                         DOCUMENT_SPECIALSIZEUNIT UnitsUsed =DOC_SPECIALSIZEUNIT_PIXELS ,
                         pHOBJECTSTYLE pCelleStyle = NULL  
                         );
      L_INT ExBeginNewList( DOCUMENT_LISTTYPE ListType );
      L_INT ExEndList( );
      L_INT ExBeginListItem( );
      L_INT ExInsertHypertextLink( LPCSTR pszUrlName, 
                                   LPCSTR pszLinkText, 
                                   LPCSTR pszLinkImagePath 
                                   );
      L_INT ExBeginNewPar( DOCUMENT_OBJECT_ALIGN ParAlign = DOC_OBJECT_ALIGN_LEFT, 
                           pHOBJECTSTYLE pParStyle = NULL,
                           LPCSTR pszClass = NULL, 
                           DOCUMENT_PARLISTTYPE ParListType = DOC_PARLISTTYPE_NON,
                           L_INT nListStartNum = 1 
                           );
      L_INT ExInsertQuotation( LPCSTR pszQuotationString );
      L_INT ExInsertLineBreak( );
      L_INT ExBeginNewTextDirection( DOCUMENT_TEXTDIRECTION NewTextDirection );
      L_INT ExEndNewTextDirection( );
      L_INT ExBeginNoLineBreak( );
      L_INT ExEndNoLineBreak( );
      L_INT ExInsertComment( LPCSTR pszCommentString );
      L_INT ExInsertHorizontalRule( );
      L_INT ExBeginBlockContainer( pHOBJECTSTYLE pBlockContainerStyle = NULL,
                                   LPCSTR pszClass =NULL  
                                   );
      L_INT ExEndBlockContainer( );
      L_INT ExBeginInlineContainer( pHOBJECTSTYLE pInlineContainerStyle = NULL,
                                    LPCSTR pszClass = NULL  
                                    );
      L_INT ExEndInlineContainer( );
      L_INT ExSetTitle( LPCSTR pszTitleString );
      L_INT ExSetPageWidth( L_FLOAT fPageWidth );
      L_INT ExSetPageHeight( L_FLOAT fPageHeight );
      L_INT ExSetTabSize( L_UINT uTabSize );
      L_INT ExGetTabSize( L_UINT * puTabSize );
      L_INT ExRealizeData( );
      L_INT ExSetLockState( L_BOOL bLock );
      L_INT ExReserve( L_UINT32 dwResSize );
      L_INT ExBeginStyleSheet( );
      L_INT ExEndStyleSheet( );
      L_INT ExAddStyle( LPCSTR pszClass, 
                        pHOBJECTSTYLE pStyle 
                        );
      L_INT ExGetUserPassword( L_CHAR *pszUserPassword );

      /* FTP support */ 
      L_INT FTPDlgSend( pDOC_FTPUPLOADFORMAT pFormat = NULL,
                        L_CHAR *pszServer = NULL,
                        L_INT iPort = -1,
                        L_CHAR *pszUserName = NULL,
						       L_CHAR *pszPassword = NULL,                                         
                        L_CHAR *pszRemote = NULL,
                        L_CHAR *pszFolder = NULL,
                        L_UINT32* puStatusMode = NULL
                        );

      L_INT FTPConnect( L_CHAR *pszServer,
                        L_INT iPort,
                        L_CHAR *pszUserName,
						       L_CHAR *pszPassword,
                        L_UINT32* puStatusMode = NULL
                        );

      L_INT FTPDisconnect( L_UINT32* puStatusMode = NULL );

      L_INT FTPChDir( L_CHAR *pszDirectory,
                      L_UINT32* puStatusMode = NULL
                      );

      L_INT FTPSend( DOC_FTPUPLOADFORMAT Format,
                     L_CHAR *pszRemote,
                     L_UINT32* puStatusMode = NULL
                     );

      /* Image processing */ 
      L_INT GetImage( pBITMAPHANDLE phBitmap,
                      L_UINT32* puStatusMode = NULL
                      );

      L_INT SetImage( pBITMAPHANDLE phBitmap,
                      L_UINT32* puStatusMode = NULL
				          );

};
#endif //__cplusplus



#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif   // _LDKRN_H_
