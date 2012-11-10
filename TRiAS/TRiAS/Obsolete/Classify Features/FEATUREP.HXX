// Precompiled Header für IMPASC.EXT ------------------------------------------
// File: FEATUREP.HXX

#if !defined(_FEATUREP_HXX)
#define _FEATUREP_HXX

#include <windows.h>
#include <ole2.h>
#include <string>
#include <stdlib.h>

#if !defined(WIN32)
#include <shellapi.h>
#include <tchar.h>
#endif

#include <commonvu.hxx>         // CommonVu - eigene Klassendeklarationen

#include <containr.hxx>

#include <errcodes.hxx>         // FehlerCodes
#include <xtension.h>           // Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>		// Konstanten und Datenstrukturen
#include <strdupx.hxx>

#include <eieruhr.hxx>

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <xtencunk.hxx>		// InterfaceImplementation der BasisKlasse
#include <xtsnguid.h>
#include <xtsnaux.hxx>

#include "uidobj.hxx"	// KlassenDeklarationen
#include "uidobj.inl"	// Inline-Funktionen

#include "feature.hxx"		// die Erweiterung selbst

#endif // _FEATUREP_HXX
