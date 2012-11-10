// Precompiled Header f�r GeoEdit.ext
// File: GeoEditP.cpp


#include <bool.h>		// Definition von bool als Datentyp
#include "GeoEditP.h"

// nachfolgende Dateien werden nur EINMAL geladen
#if _ATL_VER >= 0x0200
#include <atlimpl.cpp>
#else
#include <atlimpl11.h>
#endif // _ATL_VER

//#include "IGeoEdit.c"

// Da beim Linken IID_IEnumObjectsByNumber als redefiniert angez�hlt wird, habe ich die
// #include-Anweisung durch die nachfolgenden const-Anweisungen aus IGeoEdit.c ersetzt und
// IID_IEnumObjectsByNumber herauskommentiert.

//const IID IID_IEnumObjectsByNumber = {0x079638C5,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};

const IID IID_IEnumObjektGeometrie = {0x456c27f0,0xd22c,0x11d2,{0x88,0x52,0x00,0x10,0x4b,0xaf,0x1f,0x6b}};

const IID IID_IDragObject = {0x079638F0,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
const IID IID_ITopicalObjects = {0x71924702,0x40C2,0x11d1,{0x9B,0x1F,0x44,0x45,0x53,0x54,0x00,0x00}};
const IID IID_IEditExtensionSite = {0x079638FE,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
const IID IID_IEditExternalObjects = {0x71924704,0x40C2,0x11d1,{0x9B,0x1F,0x44,0x45,0x53,0x54,0x00,0x00}};
const IID IID_IEditOperation = {0x079638F2,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
const IID IID_IMenuHandling = {0x079638F8,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
const IID IID_IModifyClassSite = {0x079638F9,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
const IID IID_IModifyOperation = {0x079638FA,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
const IID IID_IRestrictLine = {0x3ce54290,0xc57d,0x11d2,{0x88,0x37,0x00,0x10,0x4b,0xaf,0x1f,0x6b}};
const IID IID_IRestrictCursor = {0x13a82791,0xcbf0,0x11d2,{0x88,0x3f,0x00,0x10,0x4b,0xaf,0x1f,0x6b}};

//const IID IID__DGMPoint = {0xCE361C90,0xB00C,0x11CF,{0xAB,0xEF,0x08,0x00,0x36,0x01,0xB7,0x69}};
//const IID IID__DGMGeometryDigitizeService = {0xDAF15B80,0xE3C5,0x11CF,{0xAB,0xFE,0x08,0x00,0x36,0x01,0xB7,0x69}};
//const IID IID__DGMGeometryEditService = {0x24BD4001,0xF12A,0x11CF,{0xAC,0x01,0x08,0x00,0x36,0x01,0xB7,0x69}};


const IID LIBID_GeoEditLib = {0x061D9CB3,0xB716,0x11D0,{0x95,0x68,0x00,0xA0,0x24,0xD6,0xF5,0x82}};


const CLSID CLSID_EnumObjektGeometrie = {0xE8579C71,0xD21F,0x11D2,{0x9B,0xBB,0x14,0x40,0x20,0x52,0x41,0x53}};

const CLSID CLSID_TopicalObjects = {0x71924703,0x40C2,0x11d1,{0x9B,0x1F,0x44,0x45,0x53,0x54,0x00,0x00}};
const CLSID CLSID_DragMultiLine = {0x079638FC,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
const CLSID CLSID_NewPoint = {0x079638F3,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
const CLSID CLSID_NewLine = {0x079638F4,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
const CLSID CLSID_NewArea = {0x079638F5,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
const CLSID CLSID_ObjectModify = {0x079638F7,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
const CLSID CLSID_VertexMove = {0x079638FB,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
const CLSID CLSID_VertexAdd = {0x71924705,0x40C2,0x11d1,{0x9B,0x1F,0x44,0x45,0x53,0x54,0x00,0x00}};
const CLSID CLSID_LineElongation = {0x71924707,0x40C2,0x11d1,{0x9B,0x1F,0x44,0x45,0x53,0x54,0x00,0x00}};
const CLSID CLSID_AreaPartition = {0x71924708,0x40C2,0x11d1,{0x9B,0x1F,0x44,0x45,0x53,0x54,0x00,0x00}};
const CLSID CLSID_IslandAdd = {0x7192470A,0x40C2,0x11d1,{0x9B,0x1F,0x44,0x45,0x53,0x54,0x00,0x00}};
const CLSID CLSID_MakeRectangular = {0x71924706,0x40C2,0x11d1,{0x9B,0x1F,0x44,0x45,0x53,0x54,0x00,0x00}};
const CLSID CLSID_ObjectMove = {0x71924709,0x40C2,0x11d1,{0x9B,0x1F,0x44,0x45,0x53,0x54,0x00,0x00}};
const CLSID CLSID_Designing = {0x8f2ca281,0xab87,0x11d2,{0x88,0x1a,0x00,0x10,0x4b,0xaf,0x1f,0x6b}};
const CLSID CLSID_RestrictLine = {0xd08560d0,0xc57b,0x11d2,{0x88,0x37,0x00,0x10,0x4b,0xaf,0x1f,0x6b}};
const CLSID CLSID_RestrictCursor = {0x13a82790,0xcbf0,0x11d2,{0x88,0x3f,0x00,0x10,0x4b,0xaf,0x1f,0x6b}};
const CLSID CLSID_CommonBorder = {0x12A72E58,0xB157,0x4D03,{0x92,0x97,0x73,0xA6,0x42,0x9E,0x13,0x1A}};

//const CLSID CLSID_GeometryDigitizeService = {0x71924700,0x40C2,0x11d1,{0x9B,0x1F,0x44,0x45,0x53,0x54,0x00,0x00}};
//const CLSID CLSID_GeometryEditService = {0x71924701,0x40C2,0x11d1,{0x9B,0x1F,0x44,0x45,0x53,0x54,0x00,0x00}};