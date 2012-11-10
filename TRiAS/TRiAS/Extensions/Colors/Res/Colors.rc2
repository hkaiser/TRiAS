// BScript-Erweiterung --------------------------------------------------------
// File: COLORSP.RC

#include <eb.h>
                                                         
//
// Registration Data Block - this contains information used by Basic to
// manage this extension.
//
EXTENSIONINFO RCDATA LOADONCALL DISCARDABLE
BEGIN
	1			// TRUE if this DLL needs to stay resident
	"Farbregelung und Farbkonvertierungsobjekte, V1.0\0"
END


//
// Prototype table - this table describes all the extensions defined by
// this extension module.
//
BUILTINS RCDATA LOADONCALL DISCARDABLE
BEGIN
	OBJECT_BEGIN

	///////////////////////////////////////////////////////////////////////////
	// Ein Farbwert, dargestellt durch DoubleWerte
		"DoubleColor\0", 1, "\0"

		// native properties
		OBJECT_PROPGET, "Red\0", 2, TYP_DOUBLE, 0, 0
		OBJECT_PROPGET, "Green\0", 3, TYP_DOUBLE, 0, 0
		OBJECT_PROPGET, "Blue\0", 4, TYP_DOUBLE, 0, 0
		OBJECT_PROPSET, "Red\0", 5, 1, 1, TYP_DOUBLE
		OBJECT_PROPSET, "Green\0", 6, 1, 1, TYP_DOUBLE
		OBJECT_PROPSET, "Blue\0", 7, 1, 1, TYP_DOUBLE

		// calculated properties
		OBJECT_PROPGET, "Hue\0", 8, TYP_DOUBLE, 0, 0
		OBJECT_PROPGET, "Saturation\0", 9, TYP_DOUBLE, 0, 0
		OBJECT_PROPGET, "Brightness\0", 10, TYP_DOUBLE, 0, 0
		OBJECT_PROPSET, "Hue\0", 11, 1, 1, TYP_DOUBLE
		OBJECT_PROPSET, "Saturation\0", 12, 1, 1, TYP_DOUBLE
		OBJECT_PROPSET, "Brightness\0", 13, 1, 1, TYP_DOUBLE

		// initialization functions
		OBJECT_COMMAND, "InitRGB\0", 14, 3, 3, TYP_DOUBLE, TYP_DOUBLE, TYP_DOUBLE
		OBJECT_COMMAND, "InitHSB\0", 15, 3, 3, TYP_DOUBLE, TYP_DOUBLE, TYP_DOUBLE

		OBJECT_PROPGET|OBJECT_DEFAULT, "RGB\0", 19, TYP_LONG, 0, 0
		OBJECT_PROPSET|OBJECT_DEFAULT, "RGB\0", 20, 1, 1, TYP_LONG

		OBJECT_PROPGET, "Complement\0", 21, TYP_APPOBJECT, "DoubleColor\0", 0, 0
		OBJECT_PROPGET, "Saturated\0", 22, TYP_APPOBJECT, "DoubleColor\0", 0, 0
		OBJECT_PROPGET, "Grayed\0", 23, TYP_APPOBJECT, "DoubleColor\0", 0, 0
		OBJECT_PROPGET, "Pure\0", 24, TYP_APPOBJECT, "DoubleColor\0", 0, 0

		OBJECT_ENDDEF

	///////////////////////////////////////////////////////////////////////////
	// Eine FarbSkala 
		"ColorLookUp\0", 16, "\0"
		// calculation
		OBJECT_FUNCTION, "GetColor\0", 18, TYP_APPOBJECT, "DoubleColor\0", 1, 1, TYP_INTEGER

		// initialization functions
		OBJECT_COMMAND, "Init\0", 17, 3, 4, TYP_INTEGER, TYP_APPOBJECT, "DoubleColor\0", TYP_APPOBJECT, "DoubleColor\0", TYP_VARIANT
		OBJECT_ENDDEF

	OBJECT_END

	CONST_BEGIN
		TYP_LONG, "DColor_Black\0", 0L
		TYP_LONG, "DColor_DarkGray\0", 4210752L		// 0x00404040
		TYP_LONG, "DColor_Gray\0", 8421504L			// 0x00808080
		TYP_LONG, "DColor_LightGray\0", 12632256L	// 0x00c0c0c0
		TYP_LONG, "DColor_White\0", 16777215L		// 0x00ffffff
		TYP_LONG, "DColor_Red\0", 255L				// 0x000000ff
		TYP_LONG, "DColor_Green\0", 65280L			// 0x0000ff00
		TYP_LONG, "DColor_Blue\0", 16711680L		// 0x00ff0000
		TYP_LONG, "DColor_Yellow\0", 65535L			// 0x0000ffff
		TYP_LONG, "DColor_Cyan\0", 16776960L		// 0x00ffff00
		TYP_LONG, "DColor_Magenta\0", 16711935L		// 0x00ff00ff
	CONST_END

	TABLE_END

// last entry used: 24
END
