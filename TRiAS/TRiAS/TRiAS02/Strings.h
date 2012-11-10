// @doc
// @module Strings.h | Stringkonstanten

#if !defined(_STRINGS_H__5EA16684_5F37_11D1_B9E5_080036D63803__INCLUDED_)
#define _STRINGS_H__5EA16684_5F37_11D1_B9E5_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// Variable Strings (werden bei Startup)
extern TCHAR g_cbTRiAS[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
// Stringkonstanten Koordinatentransformation
extern const TCHAR g_cbFakeMFCKey[];		// TEXT("Software\\uve\\TRiAS\\Extensions\\TRiAS.FakeMFC.1\\Config");

extern const TCHAR g_cbDefault[];			// TEXT("DEFAULT");
extern const TCHAR g_cbCoordTransform[];	// TEXT("CoordTransform  ");
extern const TCHAR g_cbCTFExt[];			// TEXT(".CTF");
extern const TCHAR g_cbDefaultCTF[];		// TEXT("DEFAULT.CTF");
extern const TCHAR g_cbKoeff11[];			// TEXT("Koeff11         ");
extern const TCHAR g_cbKoeff12[];			// TEXT("Koeff12         ");
extern const TCHAR g_cbKoeff21[];			// TEXT("Koeff21         ");
extern const TCHAR g_cbKoeff22[];			// TEXT("Koeff22         ");
extern const TCHAR g_cbOffsetX[];			// TEXT("OffsetX         ");
extern const TCHAR g_cbOffsetY[];			// TEXT("OffsetY         ");

extern const TCHAR g_cbNoMemory[];			// TEXT("Kein Speicherplatz!");

extern const TCHAR g_cbCopyrightName[];		// TEXT("TRiAS®");
#if _TRiAS_VER < 0x0400
extern const TCHAR g_cbCopyrightNameT[];	// TEXT("InterTRiAS®");
#endif // _TRiAS_VER < 0x0400
extern const TCHAR g_cbTRiASName[];			// TEXT("TRiASName");
extern const TCHAR g_cbTRiASMode[];			// TEXT("TRiASMode");

extern const TCHAR g_cbOldName[];			// TEXT("OldName");

extern const TCHAR g_cbCTFService[];		// TEXT("CTFService");
extern const TCHAR g_cbStgService[];		// TEXT("StgService");

extern const TCHAR g_cbNil[];				// TEXT("");

extern const OLECHAR g_cbObjectsMap[];		// L"ObjectsMap";
extern const OLECHAR g_cbObjectMap[];		// L"ObjectMap";
extern const OLECHAR g_cbFeatureMap[];		// L"FeatureMap";
extern const OLECHAR g_cbGeometry[];		// L"Geometry";
extern const OLECHAR g_cbTRiASDataSource[];	// L"TRiASDataSource";
extern const OLECHAR g_cbGDODataSource[];	// L"GDODataSource";

extern const OLECHAR g_cbDefaultGeometry[];	// L"DefaultGeometry";

extern const TCHAR g_cbArial[];				// TEXT("Arial");

extern const TCHAR g_cbId[];				// TEXT("Id");
extern const TCHAR g_cbIdForce[];			// TEXT("IdForce");
extern const TCHAR g_cbStandard[];			// TEXT("Standard");
extern const TCHAR g_cbObjName[];			// TEXT("Objektname");
extern const TCHAR g_cbPrimaryKey[];		// TEXT("PrimaryKey");

#endif // !defined(_STRINGS_H__5EA16684_5F37_11D1_B9E5_080036D63803__INCLUDED_)
