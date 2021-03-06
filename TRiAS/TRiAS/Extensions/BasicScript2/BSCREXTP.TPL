// BScript-Erweiterung --------------------------------------------------------
// File: BSCREXTP.RC

#include <eb.h>
                                                         
//
// Registration Data Block - this contains information used by Basic to
// manage this extension.
//
EXTENSIONINFO RCDATA LOADONCALL DISCARDABLE
BEGIN
	1			// TRUE if this DLL needs to stay resident
	"Zusätzliche Datentypen, V@A.@B\0"
END


//
// Prototype table - this table describes all the extensions defined by
// this extension module.
//
BUILTINS RCDATA LOADONCALL DISCARDABLE
BEGIN
	OBJECT_BEGIN
		"MapStringString\0", 1, "\0"
		OBJECT_FUNCTION, "Add\0", 2, TYP_INTEGER, 2, 2, TYP_STRING, TYP_STRING
		OBJECT_FUNCTION, "Delete\0", 3, TYP_INTEGER, 1, 1, TYP_STRING
		OBJECT_FUNCTION | OBJECT_DEFAULT, "Item$\0", 4, TYP_STRING, 1, 1, TYP_STRING
		OBJECT_FUNCTION, "Find$\0", 5, TYP_APPOBJECT, "StringString\0", 1, 1, TYP_STRING
		OBJECT_PROPGET, "Count\0", 6, TYP_LONG, 0, 0
		OBJECT_FUNCTION, "Add\0", 13, TYP_INTEGER, 1, 1, TYP_APPOBJECT, "StringString\0"
		OBJECT_ENDDEF

		"MapLongString\0", 7, "\0"
		OBJECT_FUNCTION, "Add\0", 8, TYP_INTEGER, 2, 2, TYP_LONG, TYP_STRING
		OBJECT_FUNCTION, "Delete\0", 9, TYP_INTEGER, 1, 1, TYP_LONG
		OBJECT_FUNCTION | OBJECT_DEFAULT, "Item$\0", 10, TYP_STRING, 1, 1, TYP_LONG
		OBJECT_FUNCTION, "Find$\0", 11, TYP_STRING, 1, 1, TYP_LONG
		OBJECT_PROPGET, "Count\0", 12, TYP_LONG, 0, 0
		OBJECT_ENDDEF

		"StringString\0", 14, "\0"
		OBJECT_PROPGET, "Key$\0", 15, TYP_STRING, 0, 0
		OBJECT_PROPGET, "Data$\0", 16, TYP_STRING, 0, 0
		OBJECT_PROPSET, "Data$\0", 17, 1, 1, TYP_STRING
		OBJECT_ENDDEF

	OBJECT_END

	PROTO_BEGIN
		PROTO_FUNC "Split\0", 18, TYP_APPOBJECT, "StringString\0", 2, 2, TYP_STRING, TYP_STRING

	// allgemeine StringManipulations-Funktionen
		PROTO_DUPFUNC "Split\0", 19, TYP_INTEGER, 3, 3, TYP_STRING, TYP_ARRAY | TYP_STRING, TYP_STRING
		PROTO_FUNC "Subst\0", 20, TYP_INTEGER, 3, 3, TYP_STRING, TYP_STRING | TYP_MODSPARM, TYP_STRING
		PROTO_FUNC "GSubst\0", 21, TYP_INTEGER, 3, 3, TYP_STRING, TYP_STRING | TYP_MODSPARM, TYP_STRING
		PROTO_FUNC "SubStr$\0", 22, TYP_STRING, 2, 3, TYP_STRING, TYP_INTEGER, TYP_INTEGER
		PROTO_FUNC "Match\0", 23, TYP_INTEGER, 2, 2, TYP_STRING, TYP_STRING

	// HexZahlen
		PROTO_FUNC "Val16\0", 24, TYP_LONG, 1, 1, TYP_STRING

	// Koordinatenumrechnung
		PROTO_FUNC "GeoGauK\0", 25, TYP_INTEGER, 6, 6, TYP_INTEGER, TYP_INTEGER, TYP_DOUBLE, TYP_DOUBLE, TYP_DOUBLE|TYP_MODSPARM, TYP_DOUBLE|TYP_MODSPARM
		PROTO_FUNC "GauGeoK\0", 26, TYP_INTEGER, 6, 6, TYP_INTEGER, TYP_INTEGER, TYP_DOUBLE, TYP_DOUBLE, TYP_DOUBLE|TYP_MODSPARM, TYP_DOUBLE|TYP_MODSPARM 
		PROTO_FUNC "GeoGauB\0", 27, TYP_INTEGER, 6, 6, TYP_INTEGER, TYP_INTEGER, TYP_DOUBLE, TYP_DOUBLE, TYP_DOUBLE|TYP_MODSPARM, TYP_DOUBLE|TYP_MODSPARM 
		PROTO_FUNC "GauGeoB\0", 28, TYP_INTEGER, 6, 6, TYP_INTEGER, TYP_INTEGER, TYP_DOUBLE, TYP_DOUBLE, TYP_DOUBLE|TYP_MODSPARM, TYP_DOUBLE|TYP_MODSPARM

		PROTO_CMD "SetBreakScript\0", 29, 1, 1, TYP_BOOLEAN		// Script abbrechen/nicht abbrechen
		PROTO_FUNC "GetAutoStart\0", 30, TYP_LONG, 0, 0
		PROTO_FUNC "IsExtension\0", 31, TYP_BOOLEAN, 0, 0	

		PROTO_FUNC "LoadResString\0", 32, TYP_STRING, 1, 1, TYP_LONG	

	// Prototypen, um falscher Eingabe vorzubeugen
		PROTO_ENTRYCMD, "BeginScript\0", 0, 0
		PROTO_ENTRYCMD, "EndScript\0", 0, 0 

	// Objekteigenschaften
		PROTO_ENTRYCMD, "BeginProperty\0", 0, 0
		PROTO_ENTRYCMD, "EndProperty\0", 0, 0 
		PROTO_ENTRYFUNC, "Count\0", TYP_LONG, 0, 0
		PROTO_ENTRYFUNC, "PropertyFlags\0", TYP_LONG, 0, 0
		PROTO_ENTRYFUNC, "Description\0", TYP_VARIANT, 0, 0
		PROTO_ENTRYFUNC, "Cumulation\0", TYP_VARIANT, 0, 0

	PROTO_END

	TABLE_END

// last entry used: 31
END
