// OLE2AUTO BasicScript-Erweiterung -------------------------------------------
// File: OLBSEXTP.RC

#include <eb.h>
                                                         
//
// Registration Data Block - this contains information used by Basic to
// manage this extension.
//
EXTENSIONINFO RCDATA LOADONCALL DISCARDABLE
BEGIN
	1			// TRUE if this DLL needs to stay resident
	"uve GmbH FEZ Potsdam -- TRiAS Makroprogrammierung, V@A.@B\0"
END

//
// Prototype table - this table describes all the extensions defined by
// this extension module.
//
BUILTINS RCDATA LOADONCALL DISCARDABLE
BEGIN
	OBJECT_BEGIN
	///////////////////////////////////////////////////////////////////////////
	// base object for all TRiAS-specific objects
		"BaseObject\0", 1, "\0"
		OBJECT_PROPGET, "isA\0", 2, TYP_LONG, 0, 0
		OBJECT_PROPGET, "Parent\0", 3, TYP_APPOBJECT, "BaseObject\0", 0, 0
		OBJECT_PROPGET, "Application\0", 4, TYP_APPOBJECT, ".Application\0", 0, 0
		OBJECT_PROPGET, "IDispatch\0", 317, TYP_OLEOBJECT, 0, 0
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// TRiAS application object
		".Application\0", 296, "BaseObject\0"
		OBJECT_PROPGET | OBJECT_DEFAULT, "Value\0", 5, TYP_STRING, 0, 0
		OBJECT_PROPGET, "Version\0", 362, TYP_STRING, 0, 0
		OBJECT_PROPGET, "Name$\0", 6, TYP_STRING, 0, 0
		OBJECT_PROPGET, "Name\0", 6, TYP_STRING, 0, 0
		OBJECT_PROPGET, "StartupPath$\0", 7, TYP_STRING, 0, 0
		OBJECT_PROPGET, "StartupPath\0", 7, TYP_STRING, 0, 0
		OBJECT_PROPGET, "DefaultFilePath$\0", 8, TYP_STRING, 0, 0
		OBJECT_PROPGET, "DefaultFilePath\0", 8, TYP_STRING, 0, 0
		OBJECT_PROPSET, "DefaultFilePath$\0", 9, 1, 1, TYP_STRING
		OBJECT_PROPSET, "DefaultFilePath\0", 9, 1, 1, TYP_STRING
		OBJECT_PROPGET, "FullName$\0", 10, TYP_STRING, 0, 0
		OBJECT_PROPGET, "FullName\0", 10, TYP_STRING, 0, 0

		OBJECT_PROPGET, "Visible\0", 11, TYP_INTEGER, 0, 0
		OBJECT_PROPSET, "Visible\0", 12, 1, 1, TYP_INTEGER
		OBJECT_PROPGET, "Interactive\0", 303, TYP_INTEGER, 0, 0
		OBJECT_PROPSET, "Interactive\0", 304, 1, 1, TYP_INTEGER
		
		OBJECT_PROPGET, "Left\0", 305, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Left\0", 306, 1, 1, TYP_LONG
		OBJECT_PROPGET, "Top\0", 307, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Top\0", 308, 1, 1, TYP_LONG
		OBJECT_PROPGET, "Width\0", 309, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Width\0", 310, 1, 1, TYP_LONG
		OBJECT_PROPGET, "Height\0", 311, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Height\0", 312, 1, 1, TYP_LONG

		OBJECT_PROPGET, "StatusBar$\0", 313, TYP_STRING, 0, 0
		OBJECT_PROPGET, "StatusBar\0", 313, TYP_STRING, 0, 0
		OBJECT_PROPSET, "StatusBar$\0", 314, 1, 1, TYP_STRING
		OBJECT_PROPSET, "StatusBar\0", 314, 1, 1, TYP_STRING

		OBJECT_PROPGET, "Caption$\0", 315, TYP_STRING, 0, 0
		OBJECT_PROPGET, "Caption\0", 315, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Caption$\0", 316, 1, 1, TYP_STRING
		OBJECT_PROPSET, "Caption\0", 316, 1, 1, TYP_STRING

		OBJECT_FUNCTION, "GetDocuments\0", 15, TYP_APPOBJECT, "GeoDocuments\0", 0, 0
		OBJECT_PROPGET, "Documents\0", 15, TYP_APPOBJECT, "GeoDocuments\0", 0, 0
		OBJECT_FUNCTION, "GetActiveDocument\0", 20, TYP_APPOBJECT, "GeoDocument\0", 0, 0
		OBJECT_PROPGET, "ActiveDocument\0", 20, TYP_APPOBJECT, "GeoDocument\0", 0, 0
		
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "NewDocument\0", 13, TYP_APPOBJECT, "GeoDocument\0", 1, 4, TYP_STRING, "FileName\0", TYP_VARIANT, "UserName\0", TYP_VARIANT, "PassWord\0", TYP_VARIANT, "Mode\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "OpenDocument\0", 14, TYP_APPOBJECT, "GeoDocument\0", 1, 4, TYP_STRING, "FileName\0", TYP_VARIANT, "UserName\0", TYP_VARIANT, "PassWord\0", TYP_VARIANT, "Mode\0"

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetDocument\0", 16, TYP_APPOBJECT, "GeoDocument\0", 1, 2, TYP_VARIANT, "Document\0", TYP_VARIANT, "Mode\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "AddDocument\0", 17, TYP_APPOBJECT, "GeoDocument\0", 1, 1, TYP_STRING, "FileName\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "AddDocument\0", 17, 1, 1, TYP_STRING, "FileName\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "MakeActive\0", 18, TYP_APPOBJECT, "GeoDocument\0", 1, 1, TYP_STRING, "FileName\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "MakeActive\0", 18, 1, 1, TYP_STRING, "FileName\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "CloseDocument\0", 19, 1, 1, TYP_STRING, "FileName\0"

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "Advise\0", 325, TYP_LONG, 1, 1, TYP_OLEOBJECT, "AdviseSink\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "Unadvise\0", 326, 1, 1, TYP_LONG, "Cookie\0"

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "AddObjectProperty\0", 328, TYP_LONG, 1, 1, TYP_OLEOBJECT, "Property\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "RemoveObjectProperty\0", 329, 1, 1, TYP_LONG, "Cookie\0"

		OBJECT_PROPGET, "ToolBars\0", 363, TYP_APPOBJECT, "ToolBars\0", 0, 0
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetToolBar\0", 364, TYP_APPOBJECT, "ToolBar\0", 1, 1, TYP_STRING, "ToolBar\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "AddToolBar\0", 365, TYP_APPOBJECT, "ToolBar\0", 1, 2, TYP_STRING, "ToolBar\0", TYP_VARIANT, "Style\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "RemoveToolBar\0", 366, 1, 1, TYP_STRING, "ToolBar\0"

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "LoadExtension\0", 439, TYP_BOOLEAN, 1, 2, TYP_STRING, "ProgID\0", TYP_VARIANT, "Mode\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "UnLoadExtension\0", 440, TYP_BOOLEAN, 1, 1, TYP_STRING, "ProgID\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "UnLoadExtension\0", 440, 1, 1, TYP_STRING, "ProgID\0"

		OBJECT_ENDDEF                    

	///////////////////////////////////////////////////////////////////////////
	// GeoDocuments collection
		"GeoDocuments\0", 1, "BaseObject\0"
		OBJECT_FUNCTION|OBJECT_DEFAULT, "Item\0", 21, TYP_APPOBJECT, "GeoDocument\0", 1, 1, TYP_VARIANT
		OBJECT_PROPGET, "Count\0", 22, TYP_LONG, 0, 0
		OBJECT_FUNCTION, "Add\0", 23, TYP_APPOBJECT, "GeoDocument\0", 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "Add\0", 23, 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "Remove\0", 24, 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "Refresh\0", 257, 0, 0
				
		OBJECT_FUNCTION, "New\0", 25, TYP_APPOBJECT, "GeoDocument\0", 1, 4, TYP_STRING, TYP_VARIANT, TYP_VARIANT, TYP_VARIANT
		OBJECT_COMMAND, "New\0", 25, 1, 4, TYP_STRING, TYP_VARIANT, TYP_VARIANT, TYP_VARIANT
		OBJECT_FUNCTION, "Open\0", 26, TYP_APPOBJECT, "GeoDocument\0", 1, 4, TYP_STRING, TYP_VARIANT, TYP_VARIANT, TYP_VARIANT
		OBJECT_COMMAND, "Open\0", 26, 1, 4, TYP_STRING, TYP_VARIANT, TYP_VARIANT, TYP_VARIANT
		
	// For..Each
		OBJECT_PROPGET, ".NewEnum\0", 166, TYP_APPOBJECT, "GeoDocuments\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 167, TYP_APPOBJECT, "GeoDocument\0", 0, 0
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// GeoDocument: TRiAS project
		"GeoDocument\0", 1, "BaseObject\0"
		OBJECT_PROPGET|OBJECT_DEFAULT, "Value\0", 27, TYP_STRING, 0, 0
		OBJECT_PROPGET, "Name$\0", 28, TYP_STRING, 0, 0
		OBJECT_PROPGET, "Name\0", 28, TYP_STRING, 0, 0
		OBJECT_PROPGET, "Path$\0", 29, TYP_STRING, 0, 0
		OBJECT_PROPGET, "Path\0", 29, TYP_STRING, 0, 0
		OBJECT_PROPGET, "FullName$\0", 30, TYP_STRING, 0, 0
		OBJECT_PROPGET, "FullName\0", 30, TYP_STRING, 0, 0
		OBJECT_PROPGET, "ActiveViewName$\0", 31, TYP_STRING, 0, 0
		OBJECT_PROPGET, "ActiveViewName\0", 31, TYP_STRING, 0, 0
		OBJECT_PROPSET, "ActiveViewName$\0", 302, 1, 1, TYP_STRING
		OBJECT_PROPSET, "ActiveViewName\0", 302, 1, 1, TYP_STRING
		OBJECT_PROPGET, "GeoObjectCount\0", 297, TYP_LONG, 0, 0
		OBJECT_PROPGET, "GeoViewCount\0", 298, TYP_LONG, 0, 0
		OBJECT_PROPGET, "GeoClassCount\0", 299, TYP_LONG, 0, 0

	// methods
		OBJECT_COMMAND, "CloseIt\0", 32, 0, 2, TYP_VARIANT, TYP_VARIANT
		OBJECT_COMMAND, "Save\0", 33, 0, 0
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "SaveAs\0", 34, 1, 1, TYP_STRING, "FileName\0"

		OBJECT_FUNCTION, "GetViews\0", 35, TYP_APPOBJECT, "GeoViews\0", 0, 0
		OBJECT_PROPGET, "Views\0", 35, TYP_APPOBJECT, "GeoViews\0", 0, 0

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetView\0", 36, TYP_APPOBJECT, "GeoView\0", 1, 2, TYP_STRING, "ViewName\0", TYP_VARIANT, "Mode\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "AddView\0", 37, TYP_APPOBJECT, "GeoView\0", 1, 1, TYP_STRING, "ViewName\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "AddView\0", 37, 1, 1, TYP_STRING, "ViewName\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "ReplaceView\0", 38, TYP_APPOBJECT, "GeoView\0", 1, 1, TYP_STRING, "ViewName\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "ReplaceView\0", 38, 1, 1, TYP_STRING, "ViewName\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "RemoveView\0", 39, 1, 1, TYP_STRING, "ViewName\0"

		OBJECT_FUNCTION, "GetClasses\0", 40, TYP_APPOBJECT, "GeoClasses\0", 0, 2, TYP_VARIANT, TYP_VARIANT
		OBJECT_PROPGET, "Classes\0", 40, TYP_APPOBJECT, "GeoClasses\0", 0, 0

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetClass\0", 41, TYP_APPOBJECT, "GeoClass\0", 1, 2, TYP_VARIANT, "Class\0", TYP_VARIANT, "DataSource\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "AddClass\0", 42, TYP_APPOBJECT, "GeoClass\0", 1, 2, TYP_VARIANT, "Class\0", TYP_VARIANT, "DataSource\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "AddClass\0", 42, 1, 2, TYP_VARIANT, "Class\0", TYP_VARIANT, "DataSource\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "ReplaceClass\0", 43, TYP_APPOBJECT, "GeoClass\0", 1, 1, TYP_VARIANT, "Class\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "ReplaceClass\0", 43, 1, 1, TYP_VARIANT, "Class\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "RemoveClass\0", 44, 1, 1, TYP_VARIANT, "Class\0"

		OBJECT_FUNCTION, "GetObjects\0", 45, TYP_APPOBJECT, "GeoObjects\0", 0, 2, TYP_VARIANT, TYP_VARIANT
		OBJECT_PROPGET, "Objects\0", 45, TYP_APPOBJECT, "GeoObjects\0", 0, 0
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "QueryObjects\0", 466, TYP_APPOBJECT, "GeoObjects\0", 0, 3, TYP_VARIANT, "Feature\0", TYP_VARIANT, "ToSearch\0", TYP_VARIANT, "Mode\0"

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetObject\0", 46, TYP_APPOBJECT, "GeoObject\0", 1, 2, TYP_VARIANT, "Object\0", TYP_VARIANT, "Mode\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "AddObject\0", 47, 0, 2, TYP_VARIANT, "Object\0", TYP_VARIANT, "Class\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "AddObject\0", 47, TYP_APPOBJECT, "GeoObject\0", 0, 2, TYP_VARIANT, "Object\0", TYP_VARIANT, "Class\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "ReplaceObject\0", 48, TYP_APPOBJECT, "GeoObject\0", 1, 1, TYP_VARIANT, "Object\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "ReplaceObject\0", 48, 1, 1, TYP_VARIANT, "Object\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "RemoveObject\0", 49, 1, 1, TYP_VARIANT, "Object\0"

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetHeaderEntry\0", 50, TYP_STRING, 1, 1, TYP_STRING, "Key\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "SetHeaderEntry\0", 51, TYP_INTEGER, 2, 2, TYP_STRING, "Key\0", TYP_STRING, "Value\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "SetHeaderEntry\0", 51, 2, 2, TYP_STRING, "Key\0", TYP_STRING, "Value\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "RemoveHeaderEntry\0", 447, 1, 1, TYP_STRING, "Key\0"

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetHeaderEntryEx\0", 50, TYP_STRING, 2, 2, TYP_STRING, "DataSource\0", TYP_STRING, "Key\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "SetHeaderEntryEx\0", 51, TYP_INTEGER, 3, 3, TYP_STRING, "DataSource\0", TYP_STRING, "Key\0", TYP_STRING, "Value\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "SetHeaderEntryEx\0", 51, 3, 3, TYP_STRING, "DataSource\0", TYP_STRING, "Key\0", TYP_STRING, "Value\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "RemoveHeaderEntryEx\0", 447, 2, 2, TYP_STRING, "DataSource\0", TYP_STRING, "Key\0"

		OBJECT_COMMAND | PROTO_NAMEDPARMS, "RePaint\0", 52, 0, 4, TYP_DOUBLE, "Left\0", TYP_DOUBLE, "Bottom\0", TYP_DOUBLE, "Right\0", TYP_DOUBLE, "Top\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "ReBuild\0", 53, 0, 1, TYP_VARIANT, "FullRebuild\0"

		OBJECT_FUNCTION, "GetGeoObjectWins\0", 146, TYP_APPOBJECT, "GeoObjectWins\0", 0, 2, TYP_VARIANT, TYP_VARIANT
		OBJECT_PROPGET, "ObjectWins\0", 146, TYP_APPOBJECT, "GeoObjectWins\0", 0, 0

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetGeoObjectWin\0", 54, TYP_APPOBJECT, "GeoObjectWin\0", 1, 2, TYP_VARIANT, "Window\0", TYP_VARIANT, "Mode\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "AddGeoObjectWin\0", 159, TYP_APPOBJECT, "GeoObjectWin\0", 1, 1, TYP_VARIANT, "Window\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "AddGeoObjectWin\0", 159, 1, 1, TYP_VARIANT, "Window\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "RemoveGeoObjectWin\0", 160, 1, 1, TYP_VARIANT, "Window\0"

		OBJECT_FUNCTION, "CreateGeoObjectsCollection\0", 263, TYP_APPOBJECT, "GeoObjects\0", 0, 0

		OBJECT_PROPGET, "RefScale\0", 371, TYP_LONG, 0, 0
		OBJECT_PROPSET, "RefScale\0", 372, 1, 1, TYP_LONG

		OBJECT_PROPSET, "IsDirty\0", 415, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "IsDirty\0", 416, TYP_BOOLEAN, 0, 0

		OBJECT_PROPSET, "PreventRepaint\0", 429, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "PreventRepaint\0", 430, TYP_BOOLEAN, 0, 0

		OBJECT_PROPGET, "ContextDataSource\0", 448, TYP_STRING, 0, 0
		OBJECT_FUNCTION, "GetConnections\0", 470, TYP_APPOBJECT, "Connections\0", 0, 0
		OBJECT_PROPGET, "Connections\0", 470, TYP_APPOBJECT, "Connections\0", 0, 0

		OBJECT_ENDDEF                    

	///////////////////////////////////////////////////////////////////////////
	// GeoViews collection
		"GeoViews\0", 1, "BaseObject\0"
		OBJECT_FUNCTION | OBJECT_DEFAULT, "Item\0", 21, TYP_APPOBJECT, "GeoView\0", 1, 1, TYP_VARIANT
		OBJECT_PROPGET, "Count\0", 22, TYP_LONG, 0, 0
		OBJECT_FUNCTION, "Add\0", 23, TYP_APPOBJECT, "GeoView\0", 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "Add\0", 23, 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "Remove\0", 24, 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "Refresh\0", 258, 0, 0

	// For..Each
		OBJECT_PROPGET, ".NewEnum\0", 171, TYP_APPOBJECT, "GeoViews\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 172, TYP_APPOBJECT, "GeoView\0", 0, 0
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// GeoView: eine Ansicht
		"GeoView\0", 1, "BaseObject\0"
		OBJECT_PROPGET | OBJECT_DEFAULT, "Value\0", 55, TYP_STRING,0,0
		OBJECT_PROPGET, "Name$\0", 56, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name$\0", 57, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Name\0", 56, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name\0", 57, 1, 1, TYP_STRING

		OBJECT_FUNCTION, "GetClipObject\0", 322, TYP_APPOBJECT, "GeoObject\0", 0, 0
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "SetClipObject\0", 323, TYP_BOOLEAN, 1, 1, TYP_APPOBJECT, "GeoObject\0", "ClipObject\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "SetClipObject\0", 323, 1, 1, TYP_APPOBJECT, "GeoObject\0", "ClipObject\0"
		OBJECT_COMMAND, "ResetClipObject\0", 396, 0, 0

		OBJECT_FUNCTION, "GetClasses\0", 58, TYP_APPOBJECT, "GeoClasses\0", 0, 2, TYP_VARIANT, TYP_VARIANT
		OBJECT_PROPGET, "Classes\0", 58, TYP_APPOBJECT, "GeoClasses\0", 0, 0

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetClass\0", 59, TYP_APPOBJECT, "GeoClass\0", 1, 3, TYP_VARIANT, "Class\0", TYP_VARIANT, "ObjTypes\0", TYP_VARIANT, "Mode\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "AddClass\0", 60, TYP_APPOBJECT, "GeoClass\0", 1, 2, TYP_VARIANT, "Class\0", TYP_VARIANT, "ObjTypes\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "AddClass\0", 60, 1, 2, TYP_VARIANT, "Class\0", TYP_VARIANT, "ObjTypes\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "ReplaceClass\0", 61, TYP_APPOBJECT, "GeoClass\0", 1, 2, TYP_VARIANT, "Class\0", TYP_VARIANT, "ObjTypes\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "ReplaceClass\0", 61, 1, 2, TYP_VARIANT, "Class\0", TYP_VARIANT, "ObjTypes\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "RemoveClass\0", 62, 1, 2, TYP_VARIANT, "Class\0", TYP_VARIANT, "ObjTypes\0"

		OBJECT_FUNCTION, "GetObjects\0", 63, TYP_APPOBJECT, "GeoObjects\0", 0, 2, TYP_VARIANT, TYP_VARIANT
		OBJECT_PROPGET, "Objects\0", 63, TYP_APPOBJECT, "GeoObjects\0", 0, 0

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetObject\0", 64, TYP_APPOBJECT, "GeoObject\0", 1, 2, TYP_VARIANT, "Object\0", TYP_VARIANT, "Mode\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "AddObject\0", 65, TYP_APPOBJECT, "GeoObject\0", 1, 1, TYP_VARIANT, "Object\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "AddObject\0", 65, 1, 1, TYP_VARIANT, "Object\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "ReplaceObject\0", 66, TYP_APPOBJECT, "GeoObject\0", 1, 1, TYP_VARIANT, "Object\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "ReplaceObject\0", 66, 1, 1, TYP_VARIANT, "Object\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "RemoveObject\0", 67, 1, 1, TYP_VARIANT, "Object\0"

		OBJECT_FUNCTION, "GetFeatures\0", 68, TYP_APPOBJECT, "GeoFeatures\0", 0, 2, TYP_VARIANT, TYP_VARIANT
		OBJECT_PROPGET, "Features\0", 68, TYP_APPOBJECT, "GeoFeatures\0", 0, 0

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetFeature\0", 69, TYP_APPOBJECT, "GeoFeature\0", 1, 2, TYP_VARIANT, "Feature\0", TYP_VARIANT, "Mode\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "AddFeature\0", 70, TYP_APPOBJECT, "GeoFeature\0", 1, 1, TYP_VARIANT, "Feature\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "AddFeature\0", 70, 1, 1, TYP_VARIANT, "Feature\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "ReplaceFeature\0", 71, TYP_APPOBJECT, "GeoFeature\0", 1, 1, TYP_VARIANT, "Feature\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "ReplaceFeature\0", 71, 1, 1, TYP_VARIANT, "Feature\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "RemoveFeature\0", 72, 1, 1, TYP_VARIANT, "Feature\0"

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetObjectsInRect\0", 157, TYP_APPOBJECT, "GeoObjects\0", 2, 4, TYP_DOUBLE, "X\0", TYP_DOUBLE, "Y\0", TYP_DOUBLE, "XMax\0", TYP_DOUBLE, "YMax\0"

		OBJECT_PROPGET, "RefScale\0", 373, TYP_LONG, 0, 0
		OBJECT_PROPSET, "RefScale\0", 374, 1, 1, TYP_LONG

		OBJECT_PROPGET, "Scale\0", 375, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Scale\0", 376, 1, 1, TYP_LONG

		OBJECT_PROPGET, "Description$\0", 377, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Description$\0", 378, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Description\0", 377, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Description\0", 378, 1, 1, TYP_STRING

		OBJECT_COMMAND | PROTO_NAMEDPARMS, "GetActRect\0", 425, 4, 4, 
			TYP_DOUBLE|TYP_MODSPARM, "X\0", TYP_DOUBLE|TYP_MODSPARM, "Y\0", 
			TYP_DOUBLE|TYP_MODSPARM, "XMax\0", TYP_DOUBLE|TYP_MODSPARM, "YMax\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "SetActRect\0", 426, 2, 4, 
			TYP_DOUBLE, "X\0", TYP_DOUBLE, "Y\0", TYP_DOUBLE, "XMax\0", TYP_DOUBLE, "YMax\0"

		OBJECT_COMMAND | PROTO_NAMEDPARMS, "GetConstraintRect\0", 427, 4, 4, 
			TYP_DOUBLE|TYP_MODSPARM, "X\0", TYP_DOUBLE|TYP_MODSPARM, "Y\0", 
			TYP_DOUBLE|TYP_MODSPARM, "XMax\0", TYP_DOUBLE|TYP_MODSPARM, "YMax\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "SetConstraintRect\0", 428, 2, 4, 
			TYP_DOUBLE, "X\0", TYP_DOUBLE, "Y\0", TYP_DOUBLE, "XMax\0", TYP_DOUBLE, "YMax\0"


		OBJECT_ENDDEF                    

	///////////////////////////////////////////////////////////////////////////
	// GeoClasses collection
		"GeoClasses\0", 1, "BaseObject\0"
		OBJECT_FUNCTION | OBJECT_DEFAULT, "Item\0", 21, TYP_APPOBJECT, "GeoClass\0", 1, 1, TYP_VARIANT
		OBJECT_PROPGET, "Count\0", 22, TYP_LONG, 0, 0
		OBJECT_FUNCTION, "Add\0", 23, TYP_APPOBJECT, "GeoClass\0", 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "Add\0", 23, 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "Remove\0", 24, 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "Refresh\0", 259, 0, 0

		// For..Each
		OBJECT_PROPGET, ".NewEnum\0", 173, TYP_APPOBJECT, "GeoClasses\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 174, TYP_APPOBJECT, "GeoClass\0", 0, 0
		OBJECT_ENDDEF

	// GeoClass: eine Objektklasse
		"GeoClass\0", 1, "BaseObject\0"
		OBJECT_PROPGET, "Value\0", 73, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Value\0", 458, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Name$\0", 74, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name$\0", 75, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Name\0", 74, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name\0", 75, 1, 1, TYP_STRING
		OBJECT_PROPGET, "FullName$\0", 76, TYP_STRING, 0, 0
		OBJECT_PROPSET, "FullName$\0", 77, 1, 1, TYP_STRING
		OBJECT_PROPGET, "FullName\0", 76, TYP_STRING, 0, 0
		OBJECT_PROPSET, "FullName\0", 77, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Updatable\0", 449, TYP_BOOLEAN, 0, 0
		OBJECT_PROPSET, "Updatable\0", 450, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "IsQueryDef\0", 456, TYP_BOOLEAN, 0, 0

		OBJECT_FUNCTION, "GetViews\0", 78, TYP_APPOBJECT, "GeoViews\0", 0, 1, TYP_INTEGER
		OBJECT_PROPGET, "Views\0", 78, TYP_APPOBJECT, "GeoViews\0", 0, 0

		OBJECT_FUNCTION, "GetObjects\0", 79, TYP_APPOBJECT, "GeoObjects\0", 0, 2, TYP_VARIANT, TYP_VARIANT
		OBJECT_PROPGET, "Objects\0", 79, TYP_APPOBJECT, "GeoObjects\0", 0, 0

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetObject\0", 80, TYP_APPOBJECT, "GeoObject\0", 1, 2, TYP_VARIANT, "Object\0", TYP_VARIANT, "Mode\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "AddObject\0", 81, TYP_APPOBJECT, "GeoObject\0", 1, 1, TYP_VARIANT, "Object\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "AddObject\0", 81, 1, 1, TYP_VARIANT, "Object\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "ReplaceObject\0", 82, TYP_APPOBJECT, "GeoObject\0", 1, 1, TYP_VARIANT, "Object\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "ReplaceObject\0", 82, 1, 1, TYP_VARIANT, "Object\0" 
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "RemoveObject\0", 83, 1, 1, TYP_VARIANT, "Object\0"

		OBJECT_FUNCTION, "GetFeatures\0", 84, TYP_APPOBJECT, "GeoFeatures\0", 0, 2, TYP_VARIANT, TYP_VARIANT
		OBJECT_PROPGET, "Features\0", 84, TYP_APPOBJECT, "GeoFeatures\0", 0, 0

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetFeature\0", 85, TYP_APPOBJECT, "GeoFeature\0", 1, 2, TYP_VARIANT, "Feature\0", TYP_VARIANT, "Mode\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "AddFeature\0", 86, TYP_APPOBJECT, "GeoFeature\0", 1, 1, TYP_VARIANT, "Feature\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "AddFeature\0", 86, 1, 1, TYP_VARIANT, "Feature\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "ReplaceFeature\0", 87, TYP_APPOBJECT, "GeoFeature\0", 1, 1, TYP_VARIANT, "Feature\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "ReplaceFeature\0", 87, 1, 1, TYP_VARIANT, "Feature\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "RemoveFeature\0", 88, 1, 1, TYP_VARIANT, "Feature\0"

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetObjectsInRect\0", 158, TYP_APPOBJECT, "GeoObjects\0", 2, 4, TYP_DOUBLE, "X\0", TYP_DOUBLE, "Y\0", TYP_DOUBLE, "XMax\0", TYP_DOUBLE, "YMax\0"

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetPointVisInfo\0", 241, TYP_APPOBJECT, "PointVisInfo\0", 0, 1, TYP_VARIANT, "View\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetLineVisInfo\0", 242, TYP_APPOBJECT, "LineVisInfo\0", 0, 1, TYP_VARIANT, "View\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetAreaVisInfo\0", 243, TYP_APPOBJECT, "AreaVisInfo\0", 0, 1, TYP_VARIANT, "View\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetTextVisInfo\0", 244, TYP_APPOBJECT, "TextVisInfo\0", 0, 1, TYP_VARIANT, "View\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "SetVisInfo\0", 245, 1, 2, TYP_APPOBJECT, "PointVisInfo\0", "VisInfo\0", TYP_VARIANT, "View\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "SetVisInfo\0", 245, 1, 2, TYP_APPOBJECT, "LineVisInfo\0", "VisInfo\0", TYP_VARIANT, "View\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "SetVisInfo\0", 245, 1, 2, TYP_APPOBJECT, "AreaVisInfo\0", "VisInfo\0", TYP_VARIANT, "View\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "SetVisInfo\0", 245, 1, 2, TYP_APPOBJECT, "TextVisInfo\0", "VisInfo\0", TYP_VARIANT, "View\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "SetVisInfo\0", 245, 1, 2, TYP_APPOBJECT, "VisInfo\0", "VisInfo\0", TYP_VARIANT, "View\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "ResetVisInfo\0", 398, 1, 2, TYP_INTEGER, "ObjType\0", TYP_VARIANT, "View\0"

		OBJECT_PROPGET | OBJECT_DEFAULT, "Code\0", 353, TYP_LONG, 0, 0

	// Name der Connection, zu der diese Objektklasse gehört
		OBJECT_PROPGET, "ConnectionName\0", 445, TYP_STRING, 0, 0

	// Objekteigenschaften der zu dieser Objektklasse gehörenden Objekte
		OBJECT_FUNCTION, "GetObjectFeatures\0", 451, TYP_APPOBJECT, "GeoFeatures\0", 0, 2, TYP_VARIANT, TYP_VARIANT
		OBJECT_PROPGET, "ObjectFeatures\0", 451, TYP_APPOBJECT, "GeoFeatures\0", 0, 0

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetObjectFeature\0", 452, TYP_APPOBJECT, "GeoFeature\0", 1, 2, TYP_VARIANT, "Feature\0", TYP_VARIANT, "Mode\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "AddObjectFeature\0", 453, TYP_APPOBJECT, "GeoFeature\0", 1, 1, TYP_VARIANT, "Feature\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "AddObjectFeature\0", 453, 1, 1, TYP_VARIANT, "Feature\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "ReplaceObjectFeature\0", 454, TYP_APPOBJECT, "GeoFeature\0", 1, 1, TYP_VARIANT, "Feature\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "ReplaceObjectFeature\0", 454, 1, 1, TYP_VARIANT, "Feature\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "RemoveObjectFeature\0", 455, 1, 1, TYP_VARIANT, "Feature\0"

		OBJECT_ENDDEF                    

	///////////////////////////////////////////////////////////////////////////
	// GeoObjects
		"GeoObjects\0", 246, "BaseObject\0"
		OBJECT_FUNCTION | OBJECT_DEFAULT, "Item\0", 21, TYP_APPOBJECT, "GeoObject\0", 1, 1, TYP_VARIANT
		OBJECT_PROPGET, "Count\0", 22, TYP_LONG, 0, 0
		OBJECT_FUNCTION, "Add\0", 23, TYP_APPOBJECT, "GeoObject\0", 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "Add\0", 23, 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "Remove\0", 24, 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "Refresh\0", 260, 0, 0

	// For..Each
		OBJECT_PROPGET, ".NewEnum\0", 175, TYP_APPOBJECT, "GeoObjects\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 176, TYP_APPOBJECT, "GeoObject\0", 0, 0

	// weitere Methoden
		OBJECT_FUNCTION, "CreateGeoObjectWin\0", 89, TYP_APPOBJECT, "GeoObjectWin\0", 0, 1, TYP_INTEGER

		OBJECT_FUNCTION, "GeometryAND\0", 181, TYP_APPOBJECT, "GeoObjects\0", 1, 1, TYP_APPOBJECT, "GeoClass\0"
		OBJECT_FUNCTION, "GeometryOR\0", 182, TYP_APPOBJECT, "GeoObjects\0", 1, 1, TYP_APPOBJECT, "GeoClass\0"
		OBJECT_FUNCTION, "GeometryIntersection\0", 181, TYP_APPOBJECT, "GeoObjects\0", 1, 1, TYP_APPOBJECT, "GeoClass\0"
		OBJECT_FUNCTION, "GeometryUnion\0", 182, TYP_APPOBJECT, "GeoObjects\0", 1, 1, TYP_APPOBJECT, "GeoClass\0"

		OBJECT_FUNCTION, "Intersection\0", 252, TYP_APPOBJECT, "GeoObjects\0", 1, 1, TYP_APPOBJECT, "GeoObjects\0"
		OBJECT_FUNCTION, "Union\0", 253, TYP_APPOBJECT, "GeoObjects\0", 1, 1, TYP_APPOBJECT, "GeoObjects\0"
		OBJECT_FUNCTION, "Difference\0", 254, TYP_APPOBJECT, "GeoObjects\0", 1, 1, TYP_APPOBJECT, "GeoObjects\0"
		OBJECT_FUNCTION, "SymmetricDifference\0", 255, TYP_APPOBJECT, "GeoObjects\0", 1, 1, TYP_APPOBJECT, "GeoObjects\0"

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GeometryLinesUnion\0", 247, TYP_APPOBJECT, "GeoObjects\0", 1, 3, TYP_APPOBJECT, "GeoClass\0", "Class\0", TYP_VARIANT, "FillGap\0", TYP_VARIANT, "AsArea\0"
//		OBJECT_FUNCTION, "GeometryLinesUnion\0", 395, TYP_APPOBJECT, "GeoObjects\0", 0, 5, TYP_VARIANT, TYP_VARIANT, TYP_VARIANT, TYP_VARIANT, TYP_VARIANT

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetObjectsInRect\0", 301, TYP_APPOBJECT, "GeoObjects\0", 2, 4, TYP_DOUBLE, "X\0", TYP_DOUBLE, "Y\0", TYP_DOUBLE, "XMax\0", TYP_DOUBLE, "YMax\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "MakeGeoClass\0", 457, TYP_APPOBJECT, "GeoClass\0", 1, 1, TYP_STRING, "NameOrOks\0"

		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// GeoObject
		"GeoObject\0", 1, "BaseObject\0"
		OBJECT_PROPGET | OBJECT_DEFAULT, "Value\0", 90, TYP_LONG, 0, 0
		OBJECT_PROPGET, "Name$\0", 91, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name$\0", 92, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Name\0", 91, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name\0", 92, 1, 1, TYP_STRING

		OBJECT_PROPGET, "ObjType\0", 93, TYP_INTEGER, 0, 0
		OBJECT_PROPGET, "ObjClass\0", 94, TYP_APPOBJECT, "GeoClass\0", 0, 0
		
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "ObjDistance\0", 95, TYP_DOUBLE, 1, 3, TYP_APPOBJECT, "GeoObject\0", "Object\0", TYP_INTEGER, "Mode\0", TYP_INTEGER, "MinMax\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "ClassDistance\0", 96, TYP_DOUBLE, 1, 4, TYP_APPOBJECT, "GeoClass\0", "Class\0", TYP_APPOBJECT | TYP_MODSPARM, "GeoObject\0", "Object\0", TYP_INTEGER, "Mode\0", TYP_INTEGER, "MinMax\0"

		OBJECT_COMMAND | PROTO_NAMEDPARMS, "GetGeometry\0", 97, 2, 2, TYP_DOUBLE|TYP_MODSPARM, "X\0", TYP_DOUBLE|TYP_MODSPARM, "Y\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetGeometry\0", 97, TYP_INTEGER, 2, 2, TYP_DOUBLE|TYP_MODSPARM, "X\0", TYP_DOUBLE|TYP_MODSPARM, "Y\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "GetGeometry\0", 98, 1, 5, TYP_LONG|TYP_MODSPARM, "Count\0", TYP_ARRAYDOUBLE, "X\0", TYP_ARRAYDOUBLE, "Y\0", TYP_INTEGER|TYP_MODSPARM, "ContCnt\0", TYP_ARRAYLONG, "Contour\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetGeometry\0", 98, TYP_INTEGER, 1, 5, TYP_LONG|TYP_MODSPARM, "Count\0", TYP_ARRAYDOUBLE, "X\0", TYP_ARRAYDOUBLE, "Y\0", TYP_INTEGER|TYP_MODSPARM, "ContCnt\0", TYP_ARRAYLONG, "Contour\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "GetGeometryRect\0", 300, 4, 4, TYP_DOUBLE|TYP_MODSPARM, "Left\0", TYP_DOUBLE|TYP_MODSPARM, "Bottom\0", TYP_DOUBLE|TYP_MODSPARM, "Right\0", TYP_DOUBLE|TYP_MODSPARM, "Top\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetGeometryRect\0", 300, TYP_INTEGER, 4, 4, TYP_DOUBLE|TYP_MODSPARM, "Left\0", TYP_DOUBLE|TYP_MODSPARM, "Bottom\0", TYP_DOUBLE|TYP_MODSPARM, "Right\0", TYP_DOUBLE|TYP_MODSPARM, "Top\0"

		OBJECT_COMMAND | PROTO_NAMEDPARMS, "PutGeometry\0", 99, 3, 4, TYP_INTEGER, "ObjTyp\0", TYP_DOUBLE, "X\0", TYP_DOUBLE, "Y\0", TYP_LONG, "Mode\0" 
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "PutGeometry\0", 99, TYP_INTEGER, 3, 4, TYP_INTEGER, "ObjTyp\0", TYP_DOUBLE, "X\0", TYP_DOUBLE, "Y\0", TYP_LONG, "Mode\0" 
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "PutGeometry\0", 100, 3, 5, TYP_INTEGER, "ObjTyp\0", TYP_ARRAYDOUBLE, "X\0", TYP_ARRAYDOUBLE, "Y\0", TYP_LONG, "Mode\0", TYP_ARRAYLONG, "Contour\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "PutGeometry\0", 100, TYP_INTEGER, 3, 5, TYP_INTEGER, "ObjTyp\0", TYP_ARRAYDOUBLE, "X\0", TYP_ARRAYDOUBLE, "Y\0", TYP_LONG, "Mode\0", TYP_ARRAYLONG, "Contour\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "PutGeometry\0", 465, 4, 5, TYP_INTEGER, "ObjTyp\0", TYP_ARRAYDOUBLE, "X\0", TYP_ARRAYDOUBLE, "Y\0", TYP_ARRAYLONG, "Contour\0", TYP_LONG, "Mode\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "PutGeometry\0", 465, TYP_INTEGER, 4, 5, TYP_INTEGER, "ObjTyp\0", TYP_ARRAYDOUBLE, "X\0", TYP_ARRAYDOUBLE, "Y\0", TYP_ARRAYLONG, "Contour\0", TYP_LONG, "Mode\0"

		OBJECT_FUNCTION, "GetText$\0", 101, TYP_STRING, 0, 0
		OBJECT_FUNCTION, "GetText\0", 101, TYP_STRING, 0, 0
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "PutText\0", 102, TYP_BOOLEAN, 1, 1, TYP_STRING, "Text\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "PutText\0", 102, 1, 1, TYP_STRING, "Text\0"

	// Objekteigenschaften
		OBJECT_FUNCTION, "GetFeatures\0", 103, TYP_APPOBJECT, "GeoFeatures\0", 0, 2, TYP_VARIANT, TYP_VARIANT
		OBJECT_PROPGET, "Features\0", 103, TYP_APPOBJECT, "GeoFeatures\0", 0, 0

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetFeature\0", 104, TYP_APPOBJECT, "GeoFeature\0", 1, 3, TYP_VARIANT, "Feature\0", TYP_VARIANT, "Mode\0", TYP_VARIANT, "Props\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "AddFeature\0", 105, TYP_APPOBJECT, "GeoFeature\0", 1, 3, TYP_VARIANT, "Feature\0", TYP_VARIANT, "Props\0", TYP_VARIANT, "OptData\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "AddFeature\0", 105, 1, 3, TYP_VARIANT, "Feature\0", TYP_VARIANT, "Props\0", TYP_VARIANT, "OptData\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "ReplaceFeature\0", 106, TYP_APPOBJECT, "GeoFeature\0", 1, 1, TYP_VARIANT, "Feature\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "ReplaceFeature\0", 106, 1, 1, TYP_VARIANT, "Feature\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "RemoveFeature\0", 107, 1, 1, TYP_VARIANT, "Feature\0"

		OBJECT_FUNCTION, "Feature\0", 294, TYP_VARIANT, 1, 1, TYP_STRING
		OBJECT_PROPSET, "Feature\0", 295, 2, 2, TYP_STRING, TYP_VARIANT
		OBJECT_FUNCTION, "Feature$\0", 294, TYP_VARIANT, 1, 1, TYP_STRING
		OBJECT_PROPSET, "Feature$\0", 295, 2, 2, TYP_STRING, TYP_VARIANT

		OBJECT_COMMAND | PROTO_NAMEDPARMS, "RePaint\0", 108, 0, 1, TYP_INTEGER, "Complete\0"

	// topologische Relationen
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "TopRelation\0", 145, TYP_INTEGER, 1, 1, TYP_APPOBJECT, "GeoObject\0", "Object\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetTopRelationObjects\0", 163, TYP_APPOBJECT, "GeoObjects\0", 1, 1, TYP_INTEGER, "TopRel\0"
		
	// Objektoperationen
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetBufferObjects\0", 164, TYP_APPOBJECT, "GeoObjects\0", 1, 4, TYP_DOUBLE, "Width\0", TYP_VARIANT, "Count\0", TYP_VARIANT, "FullCircle\0", TYP_VARIANT, "Class\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetBufferObjectEx\0", 431, TYP_APPOBJECT, "GeoObject\0", 1, 5, TYP_DOUBLE, "Width\0", TYP_VARIANT, "FullCircle\0", TYP_VARIANT, "Side\0", TYP_VARIANT, "ConvexMode\0", TYP_VARIANT, "Precision\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetCircleBufferObjects\0", 165, TYP_APPOBJECT, "GeoObjects\0", 1, 4, TYP_DOUBLE, "Width\0", TYP_VARIANT, "Count\0", TYP_VARIANT, "FullCircle\0", TYP_VARIANT, "Class\0"

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetIntersectObjects\0", 168, TYP_APPOBJECT, "GeoObjects\0", 1, 2, TYP_APPOBJECT, "GeoObject\0", "Object\0", TYP_VARIANT, "Mode\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetIntersectObjects\0", 169, TYP_APPOBJECT, "GeoObjects\0", 1, 2, TYP_APPOBJECT, "GeoObjects\0", "Objects\0", TYP_VARIANT, "Mode\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetIntersectObjectsClass\0", 170, TYP_APPOBJECT, "GeoObjects\0", 1, 2, TYP_APPOBJECT, "GeoClass\0", "Class\0", TYP_VARIANT, "Mode\0"

		OBJECT_FUNCTION, "GeometryAND\0", 183, TYP_APPOBJECT, "GeoObjects\0", 1, 2, TYP_APPOBJECT, "GeoObject\0", TYP_VARIANT
		OBJECT_FUNCTION, "GeometryOR\0", 184, TYP_APPOBJECT, "GeoObjects\0", 1, 2, TYP_APPOBJECT, "GeoObject\0", TYP_VARIANT
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GeometryIntersection\0", 183, TYP_APPOBJECT, "GeoObjects\0", 1, 2, TYP_APPOBJECT, "GeoObject\0", "Object\0", TYP_VARIANT, "Class\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GeometryUnion\0", 184, TYP_APPOBJECT, "GeoObjects\0", 1, 2, TYP_APPOBJECT, "GeoObject\0", "Object\0", TYP_VARIANT, "Class\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GeometryXOR\0", 414, TYP_APPOBJECT, "GeoObjects\0", 1, 1, TYP_APPOBJECT, "GeoObjects\0", "Objects\0"

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetCommonContourObjects\0", 248, TYP_APPOBJECT, "GeoObjects\0", 1, 3, TYP_APPOBJECT, "GeoObjects\0", "Objects\0", TYP_VARIANT, "Class\0", TYP_VARIANT, "Mode\0"

	// VisInfo (objektbezogen)
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetPointVisInfo\0", 239, TYP_APPOBJECT, "PointVisInfo\0", 0, 1, TYP_VARIANT, "VisInfo\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetLineVisInfo\0", 240, TYP_APPOBJECT, "LineVisInfo\0", 0, 1, TYP_VARIANT, "VisInfo\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetAreaVisInfo\0", 249, TYP_APPOBJECT, "AreaVisInfo\0", 0, 1, TYP_VARIANT, "VisInfo\0"
		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "GetTextVisInfo\0", 250, TYP_APPOBJECT, "TextVisInfo\0", 0, 1, TYP_VARIANT, "VisInfo\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "SetVisInfo\0", 251, 1, 2, TYP_APPOBJECT, "PointVisInfo\0", "VisInfo\0", TYP_VARIANT, "View\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "SetVisInfo\0", 251, 1, 2, TYP_APPOBJECT, "LineVisInfo\0", "VisInfo\0", TYP_VARIANT, "View\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "SetVisInfo\0", 251, 1, 2, TYP_APPOBJECT, "AreaVisInfo\0", "VisInfo\0", TYP_VARIANT, "View\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "SetVisInfo\0", 251, 1, 2, TYP_APPOBJECT, "TextVisInfo\0", "VisInfo\0", TYP_VARIANT, "View\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "SetVisInfo\0", 251, 1, 2, TYP_APPOBJECT, "VisInfo\0", "VisInfo\0", TYP_VARIANT, "View\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "ResetVisInfo\0", 397, 0, 1, TYP_VARIANT, "View\0"

	// Selektion/Aktivierung in ORFenstern
		OBJECT_FUNCTION, "Selected\0", 349, TYP_BOOLEAN, 0, 1, TYP_VARIANT
		OBJECT_PROPSET, "Selected\0", 350, 1, 2, TYP_VARIANT, TYP_BOOLEAN
		OBJECT_FUNCTION, "Activated\0", 351, TYP_BOOLEAN, 0, 1, TYP_VARIANT
		OBJECT_PROPSET, "Activated\0", 352, 1, 2, TYP_VARIANT, TYP_BOOLEAN

		OBJECT_COMMAND | PROTO_NAMEDPARMS, "Hilight\0", 407, 1, 1, TYP_LONG, "Color\0"
		OBJECT_COMMAND, "UnHilight\0", 408, 0, 0

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "ShiftGeometrySegment\0", 411, 
			TYP_APPOBJECT, "GeoObject\0", 2, 14, TYP_DOUBLE, "DestX\0", TYP_DOUBLE, "DestY\0",
			TYP_VARIANT, "TargetBeginX\0", TYP_VARIANT, "TargetBeginY\0", 
			TYP_VARIANT, "TargetEndX\0", TYP_VARIANT, "TargetEndY\0", 
			TYP_VARIANT, "MoveDir\0", TYP_VARIANT, "ContinueBegin\0", TYP_VARIANT, "ContinueEnd\0", TYP_VARIANT, "Eps\0",
			TYP_VARIANT, "ClipXMin\0", TYP_VARIANT, "ClipYMin\0", 
			TYP_VARIANT, "ClipXMax\0", TYP_VARIANT, "ClipYMax\0"

		OBJECT_PROPGET, "Guid\0", 412, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Guid\0", 413, 1, 1, TYP_STRING

		OBJECT_FUNCTION | PROTO_NAMEDPARMS, "MakeRectangular\0", 419, TYP_APPOBJECT, "GeoObjects\0", 0, 5, 
			TYP_VARIANT, "RefLine\0", TYP_VARIANT, "Eps90\0", TYP_VARIANT, "Eps180\0", 
			TYP_VARIANT, "EpsCom\0", TYP_VARIANT, "CommonObjects\0"
		OBJECT_COMMAND | PROTO_NAMEDPARMS, "MakeRectangular\0", 419, 0, 5, 
			TYP_VARIANT, "RefLine\0", TYP_VARIANT, "Eps90\0", TYP_VARIANT, "Eps180\0",  
			TYP_VARIANT, "EpsCom\0", TYP_VARIANT, "CommonObjects\0"
	
	// abhängige Textobjekte
		OBJECT_FUNCTION, "GetRelatedObject\0", 420, TYP_APPOBJECT, "GeoObject\0", 0, 0
		OBJECT_FUNCTION, "CreateObjectRelation\0", 421, TYP_BOOLEAN, 1, 1, TYP_APPOBJECT, "GeoObject\0"
		OBJECT_COMMAND, "CreateObjectRelation\0", 421, 1, 1, TYP_APPOBJECT, "GeoObject\0"
		OBJECT_COMMAND, "RemoveObjectRelation\0", 422, 0, 0
		OBJECT_FUNCTION, "RemoveObjectRelation\0", 422, TYP_APPOBJECT, "GeoObject\0", 0, 0

	// GeometrieBereinigung
		OBJECT_FUNCTION, "AnalyzeGeometry\0", 423, TYP_BOOLEAN, 0, 0
		OBJECT_FUNCTION, "AnalyzeGeometryObject\0", 424, TYP_BOOLEAN, 1, 2, TYP_APPOBJECT, "GeoObject\0", TYP_VARIANT

	// Objekt einblenden/Ausblenden
		OBJECT_PROPGET, "Visible\0", 433, TYP_BOOLEAN, 0, 0
		OBJECT_FUNCTION, "Visible\0", 433, TYP_BOOLEAN, 1, 1, TYP_STRING
		OBJECT_PROPSET, "Visible\0", 434, 1, 1, TYP_BOOLEAN
		OBJECT_PROPSET, "Visible\0", 434, 2, 2, TYP_STRING, TYP_BOOLEAN

	// UniqueID bzw. UniqueID der Ursprungsobjekte
		OBJECT_PROPGET, "UniqueID\0", 435, TYP_STRING, 0, 0
		OBJECT_PROPSET, "UniqueID\0", 436, 1, 1, TYP_STRING
		OBJECT_PROPGET, "OldUniqueID\0", 437, TYP_STRING, 0, 0
		OBJECT_PROPSET, "OldUniqueID\0", 438, 1, 1, TYP_STRING

	// Name der Connection, zu der diese Objektklasse gehört
		OBJECT_PROPGET, "ConnectionName\0", 446, TYP_STRING, 0, 0

	// Objekt doppeln
		OBJECT_FUNCTION, "CloneObject\0", 475, TYP_APPOBJECT, "GeoObject\0", 0, 1, TYP_VARIANT
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// GeoFeatures
		"GeoFeatures\0", 1, "BaseObject\0"
		OBJECT_FUNCTION|OBJECT_DEFAULT, "Item\0", 21, TYP_APPOBJECT, "GeoFeature\0", 1, 1, TYP_VARIANT
		OBJECT_PROPGET, "Count\0", 22, TYP_LONG, 0, 0
		OBJECT_FUNCTION, "Add\0", 23, TYP_APPOBJECT, "GeoFeature\0", 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "Add\0", 23, 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "Remove\0", 24, 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "Refresh\0", 261, 0, 0

		// For..Each
		OBJECT_PROPGET, ".NewEnum\0", 177, TYP_APPOBJECT, "GeoFeatures\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 178, TYP_APPOBJECT, "GeoFeature\0", 0, 0
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// GeoFeature
		"GeoFeature\0", 1, "BaseObject\0"
		OBJECT_PROPGET | OBJECT_DEFAULT, "Value\0", 109, TYP_STRING, 0, 0
		OBJECT_PROPGET, "Name$\0", 110, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name$\0", 111, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Name\0", 110, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name\0", 111, 1, 1, TYP_STRING
		OBJECT_PROPGET, "FullName$\0", 112, TYP_STRING, 0, 0
		OBJECT_PROPSET, "FullName$\0", 113, 1, 1, TYP_STRING
		OBJECT_PROPGET, "FullName\0", 112, TYP_STRING, 0, 0
		OBJECT_PROPSET, "FullName\0", 113, 1, 1, TYP_STRING
		
		OBJECT_PROPGET, "Feature$\0", 114, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Feature$\0", 115, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Feature\0", 114, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Feature\0", 115, 1, 1, TYP_STRING

		OBJECT_PROPGET, "Flags\0", 339, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Flags\0", 340, 1, 1, TYP_LONG

		OBJECT_PROPGET, "ConfigData\0", 370, TYP_VARIANT, 0, 0

		OBJECT_FUNCTION, "GetViews\0", 147, TYP_APPOBJECT, "GeoViews\0", 0, 0
		OBJECT_PROPGET, "Views\0", 147, TYP_APPOBJECT, "GeoViews\0", 0, 0

		OBJECT_FUNCTION, "GetClasses\0", 148, TYP_APPOBJECT, "GeoClasses\0", 0, 2, TYP_VARIANT, TYP_VARIANT
		OBJECT_PROPGET, "Classes\0", 148, TYP_APPOBJECT, "GeoClasses\0", 0, 2, TYP_VARIANT, TYP_VARIANT

		OBJECT_FUNCTION, "GetObjects\0", 149, TYP_APPOBJECT, "GeoObjects\0", 0, 2, TYP_VARIANT, TYP_VARIANT
		OBJECT_PROPGET, "Objects\0", 149, TYP_APPOBJECT, "GeoObjects\0", 0, 2, TYP_VARIANT, TYP_VARIANT
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// GeoObjectWins
		"GeoObjectWins\0", 1, "BaseObject\0"
		OBJECT_FUNCTION | OBJECT_DEFAULT, "Item\0", 21, TYP_APPOBJECT, "GeoObjectWin\0", 1, 1, TYP_VARIANT
		OBJECT_PROPGET, "Count\0", 22, TYP_LONG, 0, 0
		OBJECT_FUNCTION, "Add\0", 23, TYP_APPOBJECT, "GeoObjectWin\0", 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "Add\0", 23, 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "Remove\0", 24, 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "Refresh\0", 262, 0, 0
		OBJECT_PROPGET, "ActGeoObjectWin\0", 318, TYP_APPOBJECT, "GeoObjectWin\0", 0, 0

	// For..Each
		OBJECT_PROPGET, ".NewEnum\0", 179, TYP_APPOBJECT, "GeoObjectWins\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 180, TYP_APPOBJECT, "GeoObjectWin\0", 0, 0
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// GeoObjectWin
		"GeoObjectWin\0", 1, "BaseObject\0"
		OBJECT_PROPGET | OBJECT_DEFAULT, "Value\0", 116, TYP_LONG, 0, 0
		OBJECT_PROPGET, "Name$\0", 117, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name$\0", 118, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Name\0", 117, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name\0", 118, 1, 1, TYP_STRING

		OBJECT_PROPGET, "Visible\0", 161, TYP_INTEGER, 0, 0
		OBJECT_PROPSET, "Visible\0", 162, 1, 1, TYP_INTEGER
		
		OBJECT_FUNCTION, "GetClasses\0", 121, TYP_APPOBJECT, "GeoClasses\0", 0, 2, TYP_VARIANT, TYP_VARIANT
		OBJECT_PROPGET, "Classes\0", 121, TYP_APPOBJECT, "GeoClasses\0", 0, 0

		OBJECT_FUNCTION, "GetClass\0", 122, TYP_APPOBJECT, "GeoClass\0", 1, 2, TYP_VARIANT, TYP_VARIANT
		OBJECT_FUNCTION, "AddClass\0", 123, TYP_APPOBJECT, "GeoClass\0", 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "AddClass\0", 123, 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "RemoveClass\0", 124, 1, 1, TYP_VARIANT

		OBJECT_FUNCTION, "GetObjects\0", 125, TYP_APPOBJECT, "GeoObjects\0", 0, 2, TYP_VARIANT, TYP_VARIANT
		OBJECT_PROPGET, "Objects\0", 125, TYP_APPOBJECT, "GeoObjects\0", 0, 0

		OBJECT_FUNCTION, "GetObject\0", 126, TYP_APPOBJECT, "GeoObject\0", 1, 2, TYP_VARIANT, TYP_VARIANT
		OBJECT_FUNCTION, "AddObject\0", 127, TYP_APPOBJECT, "GeoObject\0", 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "AddObject\0", 127, 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "RemoveObject\0", 128, 1, 1, TYP_VARIANT

		OBJECT_FUNCTION, "AddMenuItem\0", 129, TYP_INTEGER, 3, 4, TYP_INTEGER, TYP_INTEGER, TYP_STRING, TYP_STRING
		OBJECT_FUNCTION, "GetSelectedObjects\0", 256, TYP_APPOBJECT, "GeoObjects\0", 0, 0

		OBJECT_FUNCTION, "GetActObject\0", 119, TYP_APPOBJECT, "GeoObject\0", 0, 0 
		OBJECT_FUNCTION, "SetActObject\0", 120, TYP_BOOLEAN, 1, 1, TYP_APPOBJECT, "GeoObject\0"
		OBJECT_COMMAND, "SetActObject\0", 120, 1, 1, TYP_APPOBJECT, "GeoObject\0"
		
		OBJECT_PROPGET, "Left\0", 354, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Left\0", 355, 1, 1, TYP_LONG
		OBJECT_PROPGET, "Top\0", 356, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Top\0", 357, 1, 1, TYP_LONG
		OBJECT_PROPGET, "Width\0", 358, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Width\0", 359, 1, 1, TYP_LONG
		OBJECT_PROPGET, "Height\0", 360, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Height\0", 361, 1, 1, TYP_LONG

		OBJECT_COMMAND, "SetActive\0", 417, 0, 0
		OBJECT_FUNCTION, "IsActive\0", 418, TYP_BOOLEAN, 0, 0

		OBJECT_COMMAND, "SetShownFeature\0", 432, 1, 1, TYP_STRING
		OBJECT_ENDDEF
		
	///////////////////////////////////////////////////////////////////////////
	// VisualisierungsInfo
		"VisInfo\0", 1, "BaseObject\0"
		OBJECT_PROPGET, "Style\0", 185, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Style\0", 186, 1, 1, TYP_LONG
		OBJECT_PROPGET, "Priority\0", 187, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Priority\0", 188, 1, 1, TYP_LONG
		OBJECT_PROPGET, "Name$\0", 189, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name$\0", 190, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Name\0", 189, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name\0", 190, 1, 1, TYP_STRING
		OBJECT_PROPGET, "MainColor\0", 191, TYP_LONG, 0, 0
		OBJECT_PROPSET, "MainColor\0", 192, 1, 1, TYP_LONG
		OBJECT_PROPGET, "Changed\0", 399, TYP_INTEGER, 0, 0
		OBJECT_PROPSET, "Changed\0", 400, 1, 1, TYP_INTEGER
		OBJECT_PROPGET, "Visible\0", 441, TYP_INTEGER, 0, 0
		OBJECT_PROPSET, "Visible\0", 442, 1, 1, TYP_INTEGER
		OBJECT_PROPGET, "Locatable\0", 443, TYP_INTEGER, 0, 0
		OBJECT_PROPSET, "Locatable\0", 444, 1, 1, TYP_INTEGER
		OBJECT_ENDDEF

		"PointVisInfo\0", 283, "VisInfo\0"
		OBJECT_PROPGET, "SizeX\0", 193, TYP_LONG, 0, 0
		OBJECT_PROPSET, "SizeX\0", 194, 1, 1, TYP_LONG
		OBJECT_PROPGET, "SizeY\0", 195, TYP_LONG, 0, 0
		OBJECT_PROPSET, "SizeY\0", 196, 1, 1, TYP_LONG
		OBJECT_PROPGET, "Rotate\0", 197, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Rotate\0", 198, 1, 1, TYP_LONG
		OBJECT_PROPGET, "BkColor\0", 199, TYP_LONG, 0, 0
		OBJECT_PROPSET, "BkColor\0", 200, 1, 1, TYP_LONG
		OBJECT_ENDDEF

		"LineVisInfo\0", 284, "VisInfo\0"
		OBJECT_PROPGET, "Width\0", 201, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Width\0", 202, 1, 1, TYP_LONG
		OBJECT_ENDDEF

		"AreaVisInfo\0", 285, "VisInfo\0"
		OBJECT_PROPGET, "Width\0", 203, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Width\0", 204, 1, 1, TYP_LONG
		OBJECT_PROPGET, "Opaque\0", 205, TYP_BOOLEAN, 0, 0
		OBJECT_PROPSET, "Opaque\0", 206, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "BkContour\0", 207, TYP_BOOLEAN, 0, 0
		OBJECT_PROPSET, "BkContour\0", 208, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "BkColor\0", 209, TYP_LONG, 0, 0
		OBJECT_PROPSET, "BkColor\0", 210, 1, 1, TYP_LONG
		OBJECT_ENDDEF

		"TextVisInfo\0", 286, "VisInfo\0"
		OBJECT_PROPGET, "SizeX\0", 211, TYP_LONG, 0, 0
		OBJECT_PROPSET, "SizeX\0", 212, 1, 1, TYP_LONG
		OBJECT_PROPGET, "SizeY\0", 213, TYP_LONG, 0, 0
		OBJECT_PROPSET, "SizeY\0", 214, 1, 1, TYP_LONG
		OBJECT_PROPGET, "Bold\0", 215, TYP_BOOLEAN, 0, 0
		OBJECT_PROPSET, "Bold\0", 216, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "Italic\0", 217, TYP_BOOLEAN, 0, 0
		OBJECT_PROPSET, "Italic\0", 218, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "Underline\0", 219, TYP_BOOLEAN, 0, 0
		OBJECT_PROPSET, "Underline\0", 220, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "StrikeThrough\0", 221, TYP_BOOLEAN, 0, 0
		OBJECT_PROPSET, "StrikeThrough\0", 222, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "AlignStyle\0", 223, TYP_INTEGER, 0, 0
		OBJECT_PROPSET, "AlignStyle\0", 224, 1, 1, TYP_INTEGER
		OBJECT_PROPGET, "FrameStyle\0", 225, TYP_INTEGER, 0, 0
		OBJECT_PROPSET, "FrameStyle\0", 226, 1, 1, TYP_INTEGER
		OBJECT_PROPGET, "Rotate\0", 227, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Rotate\0", 228, 1, 1, TYP_LONG
		OBJECT_PROPGET, "Slant\0", 229, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Slant\0", 230, 1, 1, TYP_LONG
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// Toolbars
		"ToolBars\0", 1, "BaseObject\0"
		OBJECT_FUNCTION | OBJECT_DEFAULT, "Item\0", 21, TYP_APPOBJECT, "ToolBar\0", 1, 1, TYP_VARIANT
		OBJECT_PROPGET, "Count\0", 22, TYP_LONG, 0, 0
		OBJECT_FUNCTION, "Add\0", 23, TYP_APPOBJECT, "ToolBar\0", 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "Add\0", 23, 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "Remove\0", 24, 1, 1, TYP_VARIANT
		OBJECT_COMMAND, "Refresh\0", 367, 0, 0

	// For..Each
		OBJECT_PROPGET, ".NewEnum\0", 368, TYP_APPOBJECT, "ToolBars\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 369, TYP_APPOBJECT, "ToolBar\0", 0, 0

		OBJECT_COMMAND, "SaveState\0", 379, 0, 2, TYP_VARIANT, TYP_VARIANT
		OBJECT_COMMAND, "LoadState\0", 380, 0, 2, TYP_VARIANT, TYP_VARIANT
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// Toolbar
		"ToolBar\0", 264, "BaseObject\0"
		OBJECT_PROPGET, "Visible\0", 266, TYP_BOOLEAN, 0, 0
		OBJECT_PROPSET, "Visible\0", 267, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "Name$\0", 279, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name$\0", 280, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Name\0", 279, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name\0", 280, 1, 1, TYP_STRING
		OBJECT_PROPGET, "DockState\0", 281, TYP_INTEGER, 0, 0
		OBJECT_PROPSET, "DockState\0", 282, 1, 1, TYP_INTEGER

		OBJECT_COMMAND, "Remove\0", 268, 0, 0
		OBJECT_COMMAND, "InsertButton\0", 278, 2, 2, TYP_INTEGER, TYP_APPOBJECT, "ToolBarButton\0"

		OBJECT_PROPGET, "Left\0", 331, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Left\0", 332, 1, 1, TYP_LONG
		OBJECT_PROPGET, "Top\0", 333, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Top\0", 334, 1, 1, TYP_LONG
		OBJECT_PROPGET, "Width\0", 335, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Width\0", 336, 1, 1, TYP_LONG
		OBJECT_PROPGET, "Height\0", 337, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Height\0", 338, 1, 1, TYP_LONG

		OBJECT_PROPGET, "CtrlID\0", 381, TYP_INTEGER, 0, 0
		OBJECT_PROPSET, "CtrlID\0", 382, 1, 1, TYP_INTEGER

		OBJECT_PROPGET, "Style\0", 403, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Style\0", 404, 1, 1, TYP_LONG
		OBJECT_PROPGET, "StyleEx\0", 405, TYP_LONG, 0, 0
		OBJECT_PROPSET, "StyleEx\0", 406, 1, 1, TYP_LONG

		OBJECT_ENDDEF

		"Image\0", 385, "\0"
		OBJECT_PROPGET|OBJECT_DEFAULT, "Handle\0", 386, TYP_LONG, 0, 0
		OBJECT_PROPGET, "hPal\0", 387, TYP_LONG, 0, 0
		OBJECT_PROPSET, "hPal\0", 388, 1, 1, TYP_LONG
		OBJECT_PROPGET, "Type\0", 389, TYP_INTEGER, 0, 0
		OBJECT_PROPGET, "Width\0", 390,  TYP_LONG, 0, 0
		OBJECT_PROPGET, "Height\0", 391, TYP_LONG, 0, 0
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// ToolBarButton
		"ToolBarButton\0", 265, "BaseObject\0"
		OBJECT_PROPGET, "Name$\0", 269, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name$\0", 270, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Name\0", 269, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Name\0", 270, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Helptext$\0", 271, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Helptext$\0", 272, 1, 1, TYP_STRING
		OBJECT_PROPGET, "Helptext\0", 271, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Helptext\0", 272, 1, 1, TYP_STRING
		OBJECT_PROPGET, "State\0", 273, TYP_INTEGER, 0, 0
		OBJECT_PROPSET, "State\0", 274, 1, 1, TYP_INTEGER
		OBJECT_PROPGET, "Style\0", 275, TYP_INTEGER, 0, 0
		OBJECT_PROPSET, "Style\0", 276, 1, 1, TYP_INTEGER

//		OBJECT_COMMAND, "AttachImage\0", 277, 1, 3, TYP_LONG, TYP_VARIANT, TYP_VARIANT
//		OBJECT_COMMAND, "AttachImage\0", 384, 1, 3, TYP_STRING, TYP_VARIANT, TYP_VARIANT
		OBJECT_COMMAND, "AttachImage\0", 383, 1, 3, TYP_APPOBJECT, "Image\0", TYP_VARIANT, TYP_VARIANT

		OBJECT_PROPSET, "Value\0", 324, 1, 1, TYP_BOOLEAN
		OBJECT_PROPGET, "CmdID\0", 409, TYP_LONG, 0, 0
		OBJECT_PROPSET, "CmdID\0", 410, 1, 1, TYP_LONG
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// PropertyAction
		"PropertySequence\0", 287, "\0"
		OBJECT_PROPGET, "Description\0", 288, TYP_STRING, 0, 0
		OBJECT_PROPGET, "Description$\0", 288, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Description\0", 289, 1, 1, TYP_STRING
		OBJECT_PROPSET, "Description$\0", 289, 1, 1, TYP_STRING
		OBJECT_COMMAND, "AddAction\0", 290, 1, 2, TYP_STRING, TYP_VARIANT
		OBJECT_COMMAND, "AddAction\0", 291, 1, 1, TYP_APPOBJECT, "PropertySequence\0"
		OBJECT_COMMAND, "AddAction\0", 291, 1, 1, TYP_APPOBJECT, "PropertyChoice\0"
		OBJECT_COMMAND, "AddAction\0", 291, 1, 1, TYP_APPOBJECT, "JoinPropertyActions\0"
		OBJECT_COMMAND, "AddAction\0", 291, 1, 1, TYP_APPOBJECT, "SplitPropertyActions\0"
		OBJECT_FUNCTION, "DoActions\0", 292, TYP_APPOBJECT, "GeoObjects\0", 0, 1, TYP_APPOBJECT, "GeoObjects\0"
		OBJECT_COMMAND, "DoActions\0", 293, 0, 1, TYP_APPOBJECT, "GeoObjects\0"
		OBJECT_COMMAND, "Save\0", 319, 0, 0
		OBJECT_FUNCTION, "Save\0", 319, TYP_BOOLEAN, 0, 0
		OBJECT_FUNCTION, "Load\0", 320, TYP_BOOLEAN, 1, 1, TYP_STRING
		OBJECT_FUNCTION, "Init\0", 321, TYP_BOOLEAN, 0, 0
		OBJECT_COMMAND, "Init\0", 321, 0, 0
		OBJECT_FUNCTION, "RedoActions\0", 401, TYP_APPOBJECT, "GeoObjects\0", 0, 1, TYP_APPOBJECT, "GeoObjects\0"
		OBJECT_COMMAND, "RedoActions\0", 402, 0, 1, TYP_APPOBJECT, "GeoObjects\0"
		OBJECT_ENDDEF

		"PropertyChoice\0", 327, "PropertySequence\0"
		OBJECT_ENDDEF

		"JoinPropertyActions\0", 471, "PropertySequence\0"
		OBJECT_ENDDEF

		"SplitPropertyActions\0", 472, "PropertySequence\0"
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// StatusIndicator
		"StatusIndicator\0", 341, "\0"
		OBJECT_PROPGET, "Caption\0", 345, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Caption\0", 346, 1, 1, TYP_STRING
		OBJECT_FUNCTION|OBJECT_DEFAULT, "Field\0", 347, TYP_STRING, 1, 1, TYP_INTEGER
		OBJECT_PROPSET|OBJECT_DEFAULT, "Field\0", 348, 2, 2, TYP_INTEGER, TYP_STRING

		OBJECT_COMMAND, "Restart\0", 342, 3, 3, TYP_LONG, TYP_LONG, TYP_LONG
		OBJECT_FUNCTION, "SetPosition\0", 343, TYP_INTEGER, 1, 1, TYP_LONG
		OBJECT_COMMAND, "SetPosition\0", 343, 1, 1, TYP_LONG
		OBJECT_FUNCTION, "WasCanceled\0", 344, TYP_BOOLEAN, 0, 0

		OBJECT_COMMAND, "Show\0", 473, 0, 0
		OBJECT_COMMAND, "Hide\0", 474, 0, 0
		OBJECT_ENDDEF

	// Kompatibilität zu externer Schnittstelle
		"ProgressIndicator\0", 341, "StatusIndicator\0"
		OBJECT_COMMAND|OBJECT_DEFAULT, "ChangeText\0", 463, 2, 2, TYP_INTEGER, TYP_STRING
		OBJECT_FUNCTION|OBJECT_DEFAULT, "RetrieveText\0", 464, TYP_STRING, 1, 1, TYP_INTEGER
		OBJECT_FUNCTION, "IsCanceled\0", 344, TYP_BOOLEAN, 0, 0
		OBJECT_FUNCTION, "InitNew\0", 459, TYP_LONG, 1, 1, TYP_LONG
		OBJECT_COMMAND, "InitNew\0", 459, 1, 1, TYP_LONG
		OBJECT_PROPGET, "Flags\0", 461, TYP_LONG, 0, 0
		OBJECT_PROPSET, "Flags\0", 460, 1, 1, TYP_LONG
		OBJECT_FUNCTION, "IncrementPosition\0", 462, TYP_LONG, 0, 0
		OBJECT_COMMAND, "IncrementPosition\0", 462, 0, 0
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// Connections
		"Connections\0", 1, "\0"
		OBJECT_FUNCTION | OBJECT_DEFAULT, "Item\0", 21, TYP_APPOBJECT, "Connection\0", 1, 1, TYP_VARIANT
		OBJECT_PROPGET, "Count\0", 22, TYP_LONG, 0, 0

	// For..Each
		OBJECT_PROPGET, ".NewEnum\0", 467, TYP_APPOBJECT, "Connections\0", 0, 0
		OBJECT_PROPGET, ".Next\0", 468, TYP_APPOBJECT, "Connection\0", 0, 0
		
		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// Connection
		"Connection\0", 1, "\0"
		OBJECT_PROPGET | OBJECT_DEFAULT, "Name\0", 469, TYP_STRING, 0, 0
		OBJECT_PROPGET, "Name$\0", 469, TYP_STRING, 0, 0

		OBJECT_ENDDEF

	OBJECT_END

	PROTO_BEGIN
		PROTO_FUNC "CDoc\0", 130, TYP_APPOBJECT, "GeoDocument\0", 1, 1, TYP_APPOBJECT,  "BaseObject\0"
		PROTO_FUNC "CView\0", 131, TYP_APPOBJECT, "GeoView\0", 1, 1, TYP_APPOBJECT,  "BaseObject\0"
		PROTO_FUNC "CObj\0", 132, TYP_APPOBJECT, "GeoObject\0", 1, 1, TYP_APPOBJECT,  "BaseObject\0"
		PROTO_FUNC "CCls\0", 133, TYP_APPOBJECT, "GeoClass\0", 1, 1, TYP_APPOBJECT,  "BaseObject\0"
		PROTO_FUNC "CFeat\0", 134, TYP_APPOBJECT, "GeoFeature\0", 1, 1, TYP_APPOBJECT,  "BaseObject\0"
		PROTO_FUNC "CObjWin\0", 150, TYP_APPOBJECT, "GeoObjectWin\0", 1, 1, TYP_APPOBJECT,  "BaseObject\0"

		PROTO_FUNC "CDocs\0", 151, TYP_APPOBJECT, "GeoDocuments\0", 1, 1, TYP_APPOBJECT,  "BaseObject\0"
		PROTO_FUNC "CViews\0", 152, TYP_APPOBJECT, "GeoViews\0", 1, 1, TYP_APPOBJECT,  "BaseObject\0"
		PROTO_FUNC "CObjs\0", 153, TYP_APPOBJECT, "GeoObjects\0", 1, 1, TYP_APPOBJECT,  "BaseObject\0"
		PROTO_FUNC "CClss\0", 154, TYP_APPOBJECT, "GeoClasses\0", 1, 1, TYP_APPOBJECT,  "BaseObject\0"
		PROTO_FUNC "CFeats\0", 155, TYP_APPOBJECT, "GeoFeatures\0", 1, 1, TYP_APPOBJECT,  "BaseObject\0"
		PROTO_FUNC "CObjWins\0", 156, TYP_APPOBJECT, "GeoObjectWins\0", 1, 1, TYP_APPOBJECT,  "BaseObject\0"

/*	Die folgenden Funktionen werden nicht mehr benötigt, da der BasicCompiler
	jetzt auch selbst 'downcasten' kann.
		PROTO_FUNC "CBase\0", 135, TYP_APPOBJECT, "BaseObject\0", 1, 1, TYP_APPOBJECT,  "GeoDocument\0"
		PROTO_DUPFUNC "CBase\0", 135, TYP_APPOBJECT, "BaseObject\0", 1, 1, TYP_APPOBJECT,  "GeoView\0"
		PROTO_DUPFUNC "CBase\0", 135, TYP_APPOBJECT, "BaseObject\0", 1, 1, TYP_APPOBJECT,  "GeoObject\0"
		PROTO_DUPFUNC "CBase\0", 135, TYP_APPOBJECT, "BaseObject\0", 1, 1, TYP_APPOBJECT,  "GeoClass\0"
		PROTO_DUPFUNC "CBase\0", 135, TYP_APPOBJECT, "BaseObject\0", 1, 1, TYP_APPOBJECT,  "GeoFeature\0"
		PROTO_DUPFUNC "CBase\0", 135, TYP_APPOBJECT, "BaseObject\0", 1, 1, TYP_APPOBJECT,  "GeoObjectWin\0"
		PROTO_DUPFUNC "CBase\0", 135, TYP_APPOBJECT, "BaseObject\0", 1, 1, TYP_APPOBJECT,  "PointVisInfo\0"
		PROTO_DUPFUNC "CBase\0", 135, TYP_APPOBJECT, "BaseObject\0", 1, 1, TYP_APPOBJECT,  "LineVisInfo\0"
		PROTO_DUPFUNC "CBase\0", 135, TYP_APPOBJECT, "BaseObject\0", 1, 1, TYP_APPOBJECT,  "AreaVisInfo\0"
		PROTO_DUPFUNC "CBase\0", 135, TYP_APPOBJECT, "BaseObject\0", 1, 1, TYP_APPOBJECT,  "TextVisInfo\0"

		PROTO_DUPFUNC "CBase\0", 135, TYP_APPOBJECT, "BaseObject\0", 1, 1, TYP_APPOBJECT,  "GeoDocuments\0"
		PROTO_DUPFUNC "CBase\0", 135, TYP_APPOBJECT, "BaseObject\0", 1, 1, TYP_APPOBJECT,  "GeoViews\0"
		PROTO_DUPFUNC "CBase\0", 135, TYP_APPOBJECT, "BaseObject\0", 1, 1, TYP_APPOBJECT,  "GeoObjects\0"
		PROTO_DUPFUNC "CBase\0", 135, TYP_APPOBJECT, "BaseObject\0", 1, 1, TYP_APPOBJECT,  "GeoClasses\0"
		PROTO_DUPFUNC "CBase\0", 135, TYP_APPOBJECT, "BaseObject\0", 1, 1, TYP_APPOBJECT,  "GeoFeatures\0"
		PROTO_DUPFUNC "CBase\0", 135, TYP_APPOBJECT, "BaseObject\0", 1, 1, TYP_APPOBJECT,  "GeoObjectWins\0"
*/
	// TRiASApplication methods/functions
		PROTO_FUNC "Value$\0", 5, TYP_STRING,0,0
		PROTO_FUNC "Value\0", 5, TYP_STRING,0,0
		PROTO_FUNC "Name$\0", 6, TYP_STRING, 0, 0
		PROTO_FUNC "Name\0", 6, TYP_STRING, 0, 0
		PROTO_FUNC "StartupPath$\0", 7, TYP_STRING, 0, 0
		PROTO_FUNC "StartupPath\0", 7, TYP_STRING, 0, 0
		PROTO_FUNC "DefaultFilePath$\0", 8, TYP_STRING, 0, 0
		PROTO_CMD  "DefaultFilePath$\0", 136, 1, 1, TYP_STRING
		PROTO_FUNC "DefaultFilePath\0", 8, TYP_STRING, 0, 0
		PROTO_CMD  "DefaultFilePath\0", 136, 1, 1, TYP_STRING
		PROTO_FUNC "FullName$\0", 10, TYP_STRING, 0, 0
		PROTO_FUNC "FullName\0", 10, TYP_STRING, 0, 0
		PROTO_FUNC "Visible\0", 11, TYP_INTEGER, 0, 0
		PROTO_CMD  "Visible\0", 137, 1, 1, TYP_INTEGER

		PROTO_FUNC "GetDocuments\0", 15, TYP_APPOBJECT, "GeoDocuments\0", 0, 0

		PROTO_FUNC "NewDocument\0", 138, TYP_APPOBJECT, "GeoDocument\0", 1, 4, TYP_STRING, TYP_VARIANT, TYP_VARIANT, TYP_VARIANT
		PROTO_FUNC "OpenDocument\0", 139, TYP_APPOBJECT, "GeoDocument\0", 1, 4, TYP_STRING, TYP_VARIANT, TYP_VARIANT, TYP_VARIANT
		PROTO_FUNC "GetDocument\0", 140, TYP_APPOBJECT, "GeoDocument\0", 1, 2, TYP_STRING, TYP_VARIANT
		PROTO_FUNC "GetActiveDocument\0", 20, TYP_APPOBJECT, "GeoDocument\0", 0, 0
		PROTO_FUNC "AddDocument\0", 141, TYP_APPOBJECT, "GeoDocument\0", 1, 1, TYP_STRING
		PROTO_FUNC "MakeActive\0", 142, TYP_APPOBJECT, "GeoDocument\0", 1, 1, TYP_STRING
		PROTO_CMD  "CloseDocument\0", 143, 1, 1, TYP_STRING

	// Farbkonvertierung/Initialisierung
		PROTO_FUNC "RGB\0", 231, TYP_LONG, 3, 3, TYP_INTEGER, TYP_INTEGER, TYP_INTEGER
		PROTO_FUNC "Red\0", 232, TYP_INTEGER, 1, 1, TYP_LONG
		PROTO_FUNC "Green\0", 233, TYP_INTEGER, 1, 1, TYP_LONG
		PROTO_FUNC "Blue\0", 234, TYP_INTEGER, 1, 1, TYP_LONG
		PROTO_FUNC "HSB\0", 235, TYP_LONG, 3, 3, TYP_INTEGER, TYP_INTEGER, TYP_INTEGER
		PROTO_FUNC "Hue\0", 236, TYP_INTEGER, 1, 1, TYP_LONG
		PROTO_FUNC "Saturation\0", 237, TYP_INTEGER, 1, 1, TYP_LONG
		PROTO_FUNC "Brightness\0", 238, TYP_INTEGER, 1, 1, TYP_LONG

		PROTO_FUNC, "LoadPicture\0", 392, TYP_APPOBJECT, "Image\0", 0, 1, TYP_VARIANT
		PROTO_FUNC, "LoadResPicture\0", 393, TYP_APPOBJECT, "Image\0", 1, 3, TYP_LONG, TYP_VARIANT, TYP_VARIANT
		PROTO_FUNC, "LoadResString\0", 394, TYP_STRING, 1, 2, TYP_LONG, TYP_VARIANT

	// helperfunction
		PROTO_CMD "SetDebug\0", 144, 1, 1, TYP_INTEGER

// last entry used: 475

	///////////////////////////////////////////////////////////////////////////
	// ServerEvent-Notifications
		PROTO_ENTRYFUNC "OnClosingServer\0", TYP_BOOLEAN, 0, 0
		PROTO_ENTRYCMD "OnServerToClose\0", 0, 0
		PROTO_ENTRYCMD "OnShowToolTips\0", 1, 1, TYP_BOOLEAN

	// ProjectEvent-Notifications
		PROTO_ENTRYCMD "OnDocumentOpened\0", 1, 1, TYP_APPOBJECT, "GeoDocument\0"
		PROTO_ENTRYFUNC "OnClosingDocument\0", TYP_BOOLEAN, 1, 1, TYP_APPOBJECT, "GeoDocument\0"
		PROTO_ENTRYCMD "OnDocumentToClose\0", 1, 1, TYP_APPOBJECT, "GeoDocument\0"
		PROTO_ENTRYCMD "OnDocumentClosed\0", 0, 0
		PROTO_ENTRYCMD "OnSetDocumentDirty\0", 2, 2, TYP_APPOBJECT, "GeoDocument\0", TYP_BOOLEAN
		PROTO_ENTRYCMD "OnChangedCoordFormat\0", 0, 0
		PROTO_ENTRYCMD "OnChangedHeader\0", 2, 2, TYP_APPOBJECT, "GeoDocument\0", TYP_STRING
		PROTO_ENTRYCMD "OnObjectSplitted\0", 3, 3, TYP_APPOBJECT, "GeoObject\0", TYP_APPOBJECT, "GeoObject\0", TYP_APPOBJECT, "GeoObject\0"

	// ViewEvent-Notification
		PROTO_ENTRYFUNC, "OnSelectingView\0", TYP_BOOLEAN, 1, 1, TYP_APPOBJECT, "GeoView\0"
		PROTO_ENTRYCMD, "OnViewSelected\0", 1, 1, TYP_APPOBJECT, "GeoView\0"
		PROTO_ENTRYFUNC, "OnDeletingView\0", TYP_BOOLEAN, 1, 1, TYP_APPOBJECT, "GeoView\0"
		PROTO_ENTRYCMD, "OnViewDeleted\0", 2, 2, TYP_APPOBJECT, "GeoDocument\0", TYP_STRING
		PROTO_ENTRYCMD, "OnViewCreated\0", 1, 1, TYP_APPOBJECT, "GeoView\0"
		PROTO_ENTRYCMD, "OnZoomChanged\0", 1, 1, TYP_LONG
		PROTO_ENTRYCMD, "OnPaintingView\0", 0, 0
		PROTO_ENTRYCMD, "OnViewPainted\0", 0, 0

	// ObjectEvent-Notifikationen
		PROTO_ENTRYCMD, "OnObjectSelected\0", 1, 1, TYP_APPOBJECT, "GeoObject\0"
		PROTO_ENTRYCMD, "OnObjectUnSelected\0", 1, 1, TYP_APPOBJECT, "GeoObject\0"
		PROTO_ENTRYCMD, "OnObjectActivated\0", 1, 1, TYP_APPOBJECT, "GeoObject\0"
		PROTO_ENTRYCMD, "OnObjectDeActivated\0", 1, 1, TYP_APPOBJECT, "GeoObject\0"
		PROTO_ENTRYFUNC, "OnDeletingObject\0", TYP_BOOLEAN, 1, 1, TYP_APPOBJECT, "GeoObject\0"
		PROTO_ENTRYCMD, "OnObjectToDelete\0", 1, 1, TYP_APPOBJECT, "GeoObject\0"
		PROTO_ENTRYCMD, "OnGeometryChanged\0", 1, 1, TYP_APPOBJECT, "GeoObject\0"
		PROTO_ENTRYFUNC, "OnChangingGeometry\0", TYP_BOOLEAN, 1, 1, TYP_APPOBJECT, "GeoObject\0"
		PROTO_ENTRYCMD, "OnObjectCreated\0", 1, 1, TYP_APPOBJECT, "GeoObject\0"

	// GeoObjWinEvent-Notifikationen
		PROTO_ENTRYCMD, "OnObjectWinCreated\0", 1, 1, TYP_APPOBJECT, "GeoObjectWin\0"
		PROTO_ENTRYFUNC, "OnObjectWinToDestroy\0", TYP_BOOLEAN, 1, 1, TYP_APPOBJECT, "GeoObjectWin\0"
		PROTO_ENTRYCMD, "OnObjectWinGotFocus\0", 1, 1, TYP_APPOBJECT, "GeoObjectWin\0"
		PROTO_ENTRYCMD, "OnObjectWinLostFocus\0", 1, 1, TYP_APPOBJECT, "GeoObjectWin\0"

	PROTO_END

	CONST_BEGIN
	// vordefiniertes TRiAS Object variable
		TYP_APPOBJECT, "TRiAS\0", ".Application\0", 1L

	// RTTI
		TYP_LONG, "RTTI_Unknown\0", 0L
		TYP_LONG, "RTTI_Application\0", 1L
		TYP_LONG, "RTTI_GeoDocument\0", 2L
		TYP_LONG, "RTTI_GeoDocuments\0", 3L
		TYP_LONG, "RTTI_GeoView\0", 4L
		TYP_LONG, "RTTI_GeoViews\0", 5L
		TYP_LONG, "RTTI_GeoClass\0", 6L
		TYP_LONG, "RTTI_GeoClasses\0", 7L
		TYP_LONG, "RTTI_GeoObject\0", 8L
		TYP_LONG, "RTTI_GeoObjects\0", 9L
		TYP_LONG, "RTTI_GeoFeature\0", 10L
		TYP_LONG, "RTTI_GeoFeatures\0", 11L
		TYP_LONG, "RTTI_GeoObjectWin\0", 12L
		TYP_LONG, "RTTI_GeoObjectWins\0", 13L
		TYP_LONG, "RTTI_VisInfo\0", 14L			// 0x0000000E
		TYP_LONG, "RTTI_PointVisInfo\0", 65550L	// 0x0001000E
		TYP_LONG, "RTTI_LineVisInfo\0", 131086L	// 0x0002000E
		TYP_LONG, "RTTI_AreaVisInfo\0", 196622L	// 0x0003000E
		TYP_LONG, "RTTI_TextVisInfo\0", 262158L	// 0x0004000E
		TYP_LONG, "RTTI_ToolBar\0", 15L
		TYP_LONG, "RTTI_ToolBars\0", 16L
		TYP_LONG, "RTTI_ToolBarButton\0", 17L
		TYP_LONG, "RTTI_ToolBarButtons\0", 18L
	
	// OPENMODE
		TYP_INTEGER, "OPENMODE_Normal\0", 0
		TYP_INTEGER, "OPENMODE_ReadOnly\0", 1
		TYP_INTEGER, "OPENMODE_NoDefaultView\0", 2
		TYP_INTEGER, "OPENMODE_HideDocument\0", 4
		TYP_INTEGER, "OPENMODE_16BitCompatible\0", 8256	// 0x2040
		
		TYP_INTEGER, "OPEN_Normal\0", 0
		TYP_INTEGER, "OPEN_ReadOnly\0", 1
		TYP_INTEGER, "OPEN_NoDefaultView\0", 2
		TYP_INTEGER, "OPEN_HideDocument\0", 4
		
	// DOCMODE
		TYP_INTEGER, "DOCMODE_Get\0", 0 
		TYP_INTEGER, "DOCMODE_Replace\0", 1 
		TYP_INTEGER, "DOCMODE_Add\0", 2 
		TYP_INTEGER, "DOCMODE_Remove\0", 3 
		
		TYP_INTEGER, "DOC_Get\0", 0 
		TYP_INTEGER, "DOC_Replace\0", 1 
		TYP_INTEGER, "DOC_Add\0", 2 
		TYP_INTEGER, "DOC_Remove\0", 3 
		
	// VIEWMODE
		TYP_INTEGER, "VIEWMODE_Get\0", 0 
		TYP_INTEGER, "VIEWMODE_Replace\0", 1 
		TYP_INTEGER, "VIEWMODE_Add\0", 2 
		TYP_INTEGER, "VIEWMODE_Remove\0", 3 
		
		TYP_INTEGER, "VIEW_Get\0", 0 
		TYP_INTEGER, "VIEW_Replace\0", 1 
		TYP_INTEGER, "VIEW_Add\0", 2 
		TYP_INTEGER, "VIEW_Remove\0", 3 
		
	// GEOCLASSMODE
		TYP_INTEGER, "GEOCLASSMODE_Get\0", 0 
		TYP_INTEGER, "GEOCLASSMODE_Replace\0", 1 
		TYP_INTEGER, "GEOCLASSMODE_Add\0", 2 
		TYP_INTEGER, "GEOCLASSMODE_Remove\0", 3 
		
		TYP_INTEGER, "CLS_Get\0", 0 
		TYP_INTEGER, "CLS_Replace\0", 1 
		TYP_INTEGER, "CLS_Add\0", 2 
		TYP_INTEGER, "CLS_Remove\0", 3 
		
	// GEOOBJECTMODE
		TYP_INTEGER, "GEOOBJECTMODE_Get\0", 0 
		TYP_INTEGER, "GEOOBJECTMODE_Replace\0", 1 
		TYP_INTEGER, "GEOOBJECTMODE_Add\0", 2 
		TYP_INTEGER, "GEOOBJECTMODE_Remove\0", 3 

		TYP_INTEGER, "OBJ_Get\0", 0 
		TYP_INTEGER, "OBJ_Replace\0", 1 
		TYP_INTEGER, "OBJ_Add\0", 2 
		TYP_INTEGER, "OBJ_Remove\0", 3 

	// GEOFEATUREMODE
		TYP_INTEGER, "GEOFEATUREMODE_Get\0", 0 
		TYP_INTEGER, "GEOFEATUREMODE_Replace\0", 1 
		TYP_INTEGER, "GEOFEATUREMODE_Add\0", 2 
		TYP_INTEGER, "GEOFEATUREMODE_Remove\0", 3 

		TYP_INTEGER, "FEAT_Get\0", 0 
		TYP_INTEGER, "FEAT_Replace\0", 1 
		TYP_INTEGER, "FEAT_Add\0", 2 
		TYP_INTEGER, "FEAT_Remove\0", 3 

	// GEOOBJECTMODE
		TYP_INTEGER, "GEOOBJWINMODE_Get\0", 0 
		TYP_INTEGER, "GEOOBJWINMODE_Replace\0", 1 
		TYP_INTEGER, "GEOOBJWINMODE_Add\0", 2 
		TYP_INTEGER, "GEOOBJWINMODE_Remove\0", 3 

		TYP_INTEGER, "OBJWIN_Get\0", 0 
		TYP_INTEGER, "OBJWIN_Replace\0", 1 
		TYP_INTEGER, "OBJWIN_Add\0", 2 
		TYP_INTEGER, "OBJWIN_Remove\0", 3 

	// Distance Type
		TYP_INTEGER, "DISTTYPE_Min\0", 0
		TYP_INTEGER, "DISTTYPE_Max\0", 1
		TYP_INTEGER, "DISTTYPE_MaxMin\0", 2
		TYP_INTEGER, "DISTTYPE_MinMax\0", 3
		
		TYP_INTEGER, "DISTTYPE_Auto\0", 0	// automatische Entscheidung über die Form der Abstandsbestimmung
		TYP_INTEGER, "DISTTYPE_Middle\0", 1	// Abstand zwischen den Containermittelpunken der beiden Objekte
		TYP_INTEGER, "DISTTYPE_Vertex\0", 2	// kürzeste Entfernung zwischen je einem Stützpunkt
		TYP_INTEGER, "DISTTYPE_Exact\0", 3	// kürzeste Entfernung bei Berücksichtigung der Punkte zwischen den Stützpunkten

		TYP_INTEGER, "DT_Min\0", 0
		TYP_INTEGER, "DT_Max\0", 1
		TYP_INTEGER, "DT_MaxMin\0", 2
		TYP_INTEGER, "DT_MinMax\0", 3
		
		TYP_INTEGER, "DT_Auto\0", 0	
		TYP_INTEGER, "DT_Middle\0", 1
		TYP_INTEGER, "DT_Vertex\0", 2
		TYP_INTEGER, "DT_Exact\0", 3	

	// Objekt Typen
		TYP_INTEGER, "OBJTYPE_Point\0", 1
		TYP_INTEGER, "OBJTYPE_Line\0", 2
		TYP_INTEGER, "OBJTYPE_Area\0", 4
		TYP_INTEGER, "OBJTYPE_Circle\0", 4
		TYP_INTEGER, "OBJTYPE_Complex\0", 16
		TYP_INTEGER, "OBJTYPE_Text\0", 8
		TYP_INTEGER, "OBJTYPE_Unknown\0", 0

		TYP_INTEGER, "OBJECTTYPE_Point\0", 1
		TYP_INTEGER, "OBJECTTYPE_Line\0", 2
		TYP_INTEGER, "OBJECTTYPE_Area\0", 4
		TYP_INTEGER, "OBJECTTYPE_Circle\0", 4
		TYP_INTEGER, "OBJECTTYPE_Complex\0", 16
		TYP_INTEGER, "OBJECTTYPE_Text\0", 8
		TYP_INTEGER, "OBJECTTYPE_Unknown\0", 0

		TYP_INTEGER, "OT_Point\0", 1
		TYP_INTEGER, "OT_Line\0", 2
		TYP_INTEGER, "OT_Area\0", 4
		TYP_INTEGER, "OT_Circle\0", 4
		TYP_INTEGER, "OT_Complex\0", 16
		TYP_INTEGER, "OT_Text\0", 8
		TYP_INTEGER, "OT_Unknown\0", 0

	// Modify Geometry
    	TYP_LONG, "MODGEOMETRY_ModObject\0", 4L
    	TYP_LONG, "MODGEOMETRY_ForceGeometry\0", 32L
    	TYP_LONG, "MODGEOMETRY_AddToView\0", 64L
		TYP_LONG, "MODGEOMETRY_GeometryIsTested\0", 16384L	// internal use only !
    	TYP_LONG, "MODGEOMETRY_NoMemoryObject\0", 32768L
 
    	TYP_LONG, "MODGEOMETRYMODE_ModObject\0", 4L
    	TYP_LONG, "MODGEOMETRYMODE_ForceGeometry\0", 32L
    	TYP_LONG, "MODGEOMETRYMODE_AddToView\0", 64L
		TYP_LONG, "MODGEOMETRYMODE_GeometryIsTested\0", 16384L	// internal use only !
    	TYP_LONG, "MODGEOMETRYMODE_NoMemoryObject\0", 32768L
 
    	TYP_LONG, "MG_ModObject\0", 4L
    	TYP_LONG, "MG_ForceGeometry\0", 32L
    	TYP_LONG, "MG_AddToView\0", 64L
		TYP_LONG, "MG_GeometryIsTested\0", 16384L			// internal use only !
    	TYP_LONG, "MG_NoMemoryObject\0", 32768L

	// Create GeoObjects Window mode
		TYP_INTEGER, "CREATEOBJECTWIN_HideObjNr\0", 1
		TYP_INTEGER, "CREATEOBJECTWIN_HideIdent\0", 2
		TYP_INTEGER, "CREATEOBJECTWIN_HideObjTyp\0", 4
		TYP_INTEGER, "CREATEOBJECTWIN_HideText\0", 8
		TYP_INTEGER, "CREATEOBJECTWIN_SortObjNr\0", 16
		TYP_INTEGER, "CREATEOBJECTWIN_SortIdent\0", 32
		TYP_INTEGER, "CREATEOBJECTWIN_SortObjTyp\0", 64
		TYP_INTEGER, "CREATEOBJECTWIN_SortText\0", 128
		TYP_INTEGER, "CREATEOBJECTWIN_CreateHidden\0", 512

		TYP_INTEGER, "COW_HideObjNr\0", 1
		TYP_INTEGER, "COW_HideIdent\0", 2
		TYP_INTEGER, "COW_HideObjTyp\0", 4
		TYP_INTEGER, "COW_HideText\0", 8
		TYP_INTEGER, "COW_SortObjNr\0", 16
		TYP_INTEGER, "COW_SortIdent\0", 32
		TYP_INTEGER, "COW_SortObjTyp\0", 64
		TYP_INTEGER, "COW_SortText\0", 128
		TYP_INTEGER, "COW_CreateHidden\0", 512

	// Topologische Relationen
		TYP_INTEGER, "TOPRELATION_InnerObject\0", 0
		TYP_INTEGER, "TOPRELATION_OuterObject\0", 1
		TYP_INTEGER, "TOPRELATION_InnerOuterObject\0", 2
		TYP_INTEGER, "TOPRELATION_Unknown\0", 3

		TYP_INTEGER, "TR_Inner\0", 0
		TYP_INTEGER, "TR_Outer\0", 1
		TYP_INTEGER, "TR_InnerOuter\0", 2
		TYP_INTEGER, "TR_Unknown\0", 3

		TYP_LONG, "TOPRELATION_Within\0", 256L			// 0x0100
		TYP_LONG, "TOPRELATION_Contains\0", 512L		// 0x0200
		TYP_LONG, "TOPRELATION_Overlaps\0", 1024L		// 0x0400
		TYP_LONG, "TOPRELATION_Crosses\0", 2048L		// 0x0800
		TYP_LONG, "TOPRELATION_Touches\0", 4096L		// 0x1000
		TYP_LONG, "TOPRELATION_Equal\0", 8192L			// 0x2000
		TYP_LONG, "TOPRELATION_Disjoint\0", 16384L		// 0x4000
		TYP_LONG, "TOPRELATION_Intersects\0", 16128L	// 0x3f00
		TYP_LONG, "TOPRELATION_Unclear\0", 32768L		// 0x8000

	// Buffering
		TYP_INTEGER, "BUFFERING_Ring\0", 0
		TYP_INTEGER, "BUFFERING_FullArea\0", 1
	
		TYP_INTEGER, "BUF_Ring\0", 0
		TYP_INTEGER, "BUF_FullArea\0", 1

		TYP_INTEGER, "CONVEXMODE_Arc\0", 0
		TYP_INTEGER, "CONVEXMODE_Kite\0", 1
		TYP_INTEGER, "CONVEXMODE_Tip\0", 2
		TYP_INTEGER, "CONVEXMODE_Plain\0", 3

		TYP_INTEGER, "BUFFERING_Left\0", 0
		TYP_INTEGER, "BUFFERING_Right\0", 1
		TYP_INTEGER, "BUFFERING_Both\0", 2

	// Objektoperationen
		TYP_INTEGER, "OBJOPER_InnerParts\0", 1
		TYP_INTEGER, "OBJOPER_OuterParts\0", 2
		TYP_INTEGER, "OBJOPER_InnerOuterParts\0", 3
		TYP_INTEGER, "OBJOPER_ContourParts\0", 4

		TYP_INTEGER, "OP_InnerParts\0", 1
		TYP_INTEGER, "OP_OuterParts\0", 2
		TYP_INTEGER, "OP_InnerOuterParts\0", 3
		TYP_INTEGER, "OP_ContourParts\0", 4

		TYP_INTEGER, "OBJOPERMODE_InnerParts\0", 1
		TYP_INTEGER, "OBJOPERMODE_OuterParts\0", 2
		TYP_INTEGER, "OBJOPERMODE_InnerOuterParts\0", 3
		TYP_INTEGER, "OBJOPERMODE_ContourParts\0", 4

	// Operationen der Geometriebereinigung
		TYP_INTEGER, "GEOREIN_Nothing\0", 0
		TYP_INTEGER, "GEOREIN_First\0", 1
		TYP_INTEGER, "GEOREIN_Second\0", 2
		TYP_INTEGER, "GEOREIN_Both\0", 3

	// ShiftGeometrySegment
		TYP_INTEGER, "MOVEDIR_Up\0", 0
		TYP_INTEGER, "MOVEDIR_Down\0", 1

	// AlignStyle
		TYP_INTEGER, "ALIGNSTYLE_Left\0", 0
		TYP_INTEGER, "ALIGNSTYLE_Centre\0", 1
		TYP_INTEGER, "ALIGNSTYLE_Right\0", 2
		TYP_INTEGER, "ALIGNSTYLE_Full\0", 3

	// FrameStyle
		TYP_INTEGER, "FRAMESTYLE_NoFrame\0", 0
		TYP_INTEGER, "FRAMESTYLE_Simple\0", 1
		TYP_INTEGER, "FRAMESTYLE_Rounded\0", 2
		TYP_INTEGER, "FRAMESTYLE_TargetColor\0", 4

	// Toolbar-Dockstate
		TYP_INTEGER, "DOCKSTATE_Floating\0", 0
		TYP_INTEGER, "DOCKSTATE_DockedLeft\0", 1
		TYP_INTEGER, "DOCKSTATE_DockedRight\0", 2
		TYP_INTEGER, "DOCKSTATE_DockedTop\0", 3
		TYP_INTEGER, "DOCKSTATE_DockedBottom\0", 4

	// Toolbar Style
		TYP_LONG, "TOOLBARSTYLE_AlignLeft\0", 4096L		// 0x1000
		TYP_LONG, "TOOLBARSTYLE_AlignTop\0", 8192L		// 0x2000
		TYP_LONG, "TOOLBARSTYLE_AlignRight\0", 16384L	// 0x4000
		TYP_LONG, "TOOLBARSTYLE_AlignBottom\0", 32768L	// 0x8000
		TYP_LONG, "TOOLBARSTYLE_AlignAny\0", 61440L		// 0xF000

		TYP_LONG, "TOOLBARSTYLE_BorderLeft\0", 256L		// 0x0100
		TYP_LONG, "TOOLBARSTYLE_BorderTop\0", 512L		// 0x0200
		TYP_LONG, "TOOLBARSTYLE_BorderRight\0", 1024L	// 0x0400
		TYP_LONG, "TOOLBARSTYLE_BorderBottom\0", 2048L	// 0x0800
		TYP_LONG, "TOOLBARSTYLE_BorderAny\0", 3840L		// 0x0F00

		TYP_LONG, "TOOLBARSTYLE_Tooltips\0", 16L		// 0x0010
		TYP_LONG, "TOOLBARSTYLE_FlyBy\0", 32L			// 0x0020
		TYP_LONG, "TOOLBARSTYLE_FloatMulti\0", 64L		// 0x0040
		TYP_LONG, "TOOLBARSTYLE_Border3d\0", 128L		// 0x0080
		TYP_LONG, "TOOLBARSTYLE_HideInplace\0", 8L		// 0x0008
		TYP_LONG, "TOOLBARSTYLE_SizeDynamic\0", 4L		// 0x0004
		TYP_LONG, "TOOLBARSTYLE_SizeFixed\0", 2L		// 0x0002
		TYP_LONG, "TOOLBARSTYLE_Floating\0", 1L			// 0x0001

	// ToolbarButtonStyle
		TYP_INTEGER, "BUTTONSTYLE_Button\0", 0
		TYP_INTEGER, "BUTTONSTYLE_Separator\0", 1
		TYP_INTEGER, "BUTTONSTYLE_Check\0", 2
		TYP_INTEGER, "BUTTONSTYLE_Group\0", 4
		TYP_INTEGER, "BUTTONSTYLE_CheckGroup\0", 6
		TYP_INTEGER, "BUTTONSTYLE_DropDown\0", 8
		TYP_INTEGER, "BUTTONSTYLE_NoKickIdle\0", 32768

	// ToolbarButtonState
		TYP_INTEGER, "BUTTONSTATE_Disabled\0", 0
		TYP_INTEGER, "BUTTONSTATE_Checked\0", 1
		TYP_INTEGER, "BUTTONSTATE_Pressed\0", 2
		TYP_INTEGER, "BUTTONSTATE_Enabled\0", 4
		TYP_INTEGER, "BUTTONSTATE_Hidden\0", 8
		TYP_INTEGER, "BUTTONSTATE_Indeterminate\0", 16
		TYP_INTEGER, "BUTTONSTATE_Wrap\0", 32
		TYP_INTEGER, "BUTTONSTATE_Ellipses\0", 64
		TYP_INTEGER, "BUTTONSTATE_NoKickIdle\0", 32768

	// FEATURETYPE
		TYP_LONG, "FEATURETYPE_ReadOnly\0", 0L
		TYP_LONG, "FEATURETYPE_WriteAble\0", 1L
		TYP_LONG, "FEATURETYPE_System\0", 2L

	// StatusIndicator
		TYP_LONG, "STATUS_ShowField1\0", 2L
		TYP_LONG, "STATUS_ShowField2\0", 4L
		TYP_LONG, "STATUS_ShowField3\0", 8L
		TYP_LONG, "STATUS_ShowField4\0", 16L		// 0x10L

		TYP_LONG, "STATUS_ShowTime\0", 32L			// 0x20L
		TYP_LONG, "STATUS_AdjustPercents\0", 64L	// 0x40L
		TYP_LONG, "STATUS_ShowAllFields\0", 127L	// 0x007FL

		TYP_LONG, "STATUS_CopyAVI\0", 4096L			// 0x1000L
		TYP_LONG, "STATUS_MoveAVI\0", 8192L			// 0x2000L
		TYP_LONG, "STATUS_DeleteAVI\0", 12288L		// 0x3000L
		TYP_LONG, "STATUS_ResetCancel\0", 32768L	// 0x8000L

	// Kompatibilität mit externer Schnittstelle
		TYP_LONG, "PIFLAGS_CAPTION\0", 1L
		TYP_LONG, "PIFLAGS_FILE\0", 2L
		TYP_LONG, "PIFLAGS_FILENAME\0", 4L
		TYP_LONG, "PIFLAGS_STATUS\0", 8L
		TYP_LONG, "PIFLAGS_RESULT\0", 16L			// 0x10L
		TYP_LONG, "PIFLAGS_TIME\0", 32L				// 0x20L
		TYP_LONG, "PIFLAGS_ADJUSTPERCENT\0", 64L	// 0x40L
		TYP_LONG, "PIFLAGS_INIT_SHOWWINDOW\0", 128L	// 0x100L
		TYP_LONG, "PIFLAGS_AVI_COPY\0", 4096L		// 0x1000L
		TYP_LONG, "PIFLAGS_AVI_MOVE\0", 8192L		// 0x2000L
		TYP_LONG, "PIFLAGS_AVI_DELETE\0", 12288L	// 0x3000L
		TYP_LONG, "PIFLAGS_ALL\0", 127L				// 0x7fL
		TYP_LONG, "PIFLAGS_RESETCANCEL\0", 32768L	// 0x8000L

	// REFLINE
		TYP_LONG, "REFLINE_Rectangular\0", 0L
		TYP_LONG, "REFLINE_Common\0", 1L
		TYP_LONG, "REFLINE_Longest\0", 2L
		TYP_LONG, "REFLINE_Southern\0", 3L

	// DEBUG
		TYP_INTEGER, "DebugOn\0", 1
		TYP_INTEGER, "DebugOff\0", 0

	// Modi für LoadResType
		TYP_INTEGER, "vbResBitmap\0", 0
		TYP_INTEGER, "vbResIcon\0", 1
		TYP_INTEGER, "vbResCursor\0", 2

	// vordefinierte ToolBarButton Konstanten
		TYP_LONG, "Tool1\0", 12010L
		TYP_LONG, "Tool2\0", 12011L
		TYP_LONG, "Tool3\0", 12012L
		TYP_LONG, "Tool4\0", 12013L
		TYP_LONG, "Tool5\0", 12014L
		TYP_LONG, "Tool6\0", 12015L
		TYP_LONG, "Tool7\0", 12016L
		TYP_LONG, "Tool8\0", 12017L
		TYP_LONG, "Tool9\0", 12018L
		TYP_LONG, "Tool10\0", 12019L
		TYP_LONG, "Tool11\0", 12020L
		TYP_LONG, "Tool12\0", 12021L
		TYP_LONG, "Tool13\0", 12022L
		TYP_LONG, "Tool14\0", 12023L
		TYP_LONG, "Tool15\0", 12024L
		TYP_LONG, "Tool16\0", 12025L
		TYP_LONG, "Tool17\0", 12026L
		TYP_LONG, "Tool18\0", 12027L
		TYP_LONG, "Tool19\0", 12028L
		TYP_LONG, "Tool20\0", 12029L
		TYP_LONG, "Tool21\0", 12030L
		TYP_LONG, "Tool22\0", 12031L
		TYP_LONG, "Tool23\0", 12032L
		TYP_LONG, "Tool24\0", 12033L
		TYP_LONG, "Tool25\0", 12034L
		TYP_LONG, "Tool26\0", 12035L
		TYP_LONG, "Tool27\0", 12036L
		TYP_LONG, "Tool28\0", 12037L
		TYP_LONG, "Tool29\0", 12038L
		TYP_LONG, "Tool30\0", 12039L
		TYP_LONG, "Tool31\0", 12040L
		TYP_LONG, "Tool32\0", 12041L
		TYP_LONG, "Tool33\0", 12042L
		TYP_LONG, "Tool34\0", 12043L
		TYP_LONG, "Tool35\0", 12044L
		TYP_LONG, "Tool36\0", 12045L
		TYP_LONG, "Tool37\0", 12046L
		TYP_LONG, "Tool38\0", 12047L
		TYP_LONG, "Tool39\0", 12048L
		TYP_LONG, "Tool40\0", 12049L
		TYP_LONG, "Tool41\0", 12050L
		TYP_LONG, "Tool42\0", 12051L
		TYP_LONG, "Tool43\0", 12052L
		TYP_LONG, "Tool44\0", 12053L
		TYP_LONG, "Tool45\0", 12054L
		TYP_LONG, "Tool46\0", 12055L
		TYP_LONG, "Tool47\0", 12056L
		TYP_LONG, "Tool48\0", 12057L
		TYP_LONG, "Tool49\0", 12058L
		TYP_LONG, "Tool50\0", 12059L
		TYP_LONG, "Tool51\0", 12060L
		TYP_LONG, "Tool52\0", 12061L
		TYP_LONG, "Tool53\0", 12062L
		TYP_LONG, "Tool54\0", 12063L
		TYP_LONG, "Tool55\0", 12064L
		TYP_LONG, "Tool56\0", 12065L
		TYP_LONG, "Tool57\0", 12066L
		TYP_LONG, "Tool58\0", 12067L
		TYP_LONG, "ToolCount\0", 58L

	CONST_END

	TABLE_END
END
