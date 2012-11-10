///////////////////////////////////////////////////////////////////////////
// @doc
// @module Strings.h | Stringkonstanten

#if !defined(_STRINGS_H__7417A5E9_AED0_11D1_859A_00600875138A__INCLUDED_)
#define _STRINGS_H__7417A5E9_AED0_11D1_859A_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// Initialisierungen
extern const TCHAR g_cbTriasExtensionMessage[];		// TEXT("TriasExtensionMessage");
extern const TCHAR g_cbTriasNotification[];			// TEXT("TriasNotification");
extern const TCHAR g_cbTriasCPPExtensionMessage[];	// TEXT("TriasCPPExtensionMessage");

extern const TCHAR g_cbMetaData[];					// TEXT("Beschreibungsdaten");
extern const TCHAR g_cbCompatibility16[];			// TEXT("Compatibility16");
extern const TCHAR g_cbIdentBaseHdr[];				// TEXT("IdentBase");

extern const TCHAR g_cbNil[];						// TEXT("");
extern const TCHAR g_cbSpace[];						// TEXT(" ");

///////////////////////////////////////////////////////////////////////////////
// Koordinatentransformation
extern const TCHAR g_cbCoordTransform[];			// TEXT("CoordTransform");
extern const TCHAR g_cbCoordMeridian[];				// TEXT("CoordMeridian");
extern const TCHAR g_cbCoordStrBreite[];			// TEXT("CoordStrBreite");
extern const TCHAR g_cbKoeff11[];					// TEXT("Koeff11");
extern const TCHAR g_cbKoeff12[];					// TEXT("Koeff12");
extern const TCHAR g_cbKoeff21[];					// TEXT("Koeff21");
extern const TCHAR g_cbKoeff22[];					// TEXT("Koeff22");
extern const TCHAR g_cbOffsetX[];					// TEXT("OffsetX");
extern const TCHAR g_cbOffsetY[];					// TEXT("OffsetY");

///////////////////////////////////////////////////////////////////////////////
// FeatureTable
extern const TCHAR g_cbName[];						// TEXT("Name");
extern const TCHAR g_cbGeometryType[];				// TEXT("GeometryType");
extern const TCHAR g_cbPrimaryGeometryFieldName[];	// TEXT("PrimaryGeometryFieldName");
extern const TCHAR g_cbDescription[];				// TEXT("Description")

extern const TCHAR g_cbGeometryField[];				// TEXT("Geometry");

///////////////////////////////////////////////////////////////////////////////
// Fehlermeldungen bei schweren Fehlern
extern const TCHAR g_cbNoMemory[];					// TEXT("Kein Speicherplatz!");

///////////////////////////////////////////////////////////////////////////////
// Globale Zeichenketten (nicht konstant)
extern TCHAR g_cbTRiAS[_MAX_PATH];
extern TCHAR g_cbProjects[_MAX_PATH];

extern TCHAR g_cbObjektNummer[32];		// TEXT("ObjektNummer");
extern TCHAR g_cbGeometry[32];			// TEXT("Geometry");
extern TCHAR g_cbObjektTyp[32];			// TEXT("Objekttyp");
extern TCHAR g_cbPunkt[32];				// TEXT("Punkt");
extern TCHAR g_cbLinie[32];				// TEXT("Linie");
extern TCHAR g_cbFlaeche[32];			// TEXT("Fläche");
extern TCHAR g_cbText[32];				// TEXT("Text");

extern TCHAR g_cbPunkte[32];			// TEXT("Punkte");
extern TCHAR g_cbLinien[32];			// TEXT("Linien");
extern TCHAR g_cbFlaechen[32];			// TEXT("Flächen");
extern TCHAR g_cbTexte[32];				// TEXT("Texte");

extern TCHAR g_cbIdentifikator[];		// TEXT("Identifikator");
extern TCHAR g_cbObjekttypen[];			// TEXT("Objekttypen");
extern TCHAR g_cbKurztext[];			// TEXT("Kurztext");
extern TCHAR g_cbLangtext[];			// TEXT("Langtext");

#endif // !defined(_STRINGS_H__7417A5E9_AED0_11D1_859A_00600875138A__INCLUDED_)
