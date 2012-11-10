// Precompiled Header für IMPASC.EXT ------------------------------------------
// File: FEATUREP.HXX

#if !defined(_FEATUREP_HXX)
#define _FEATUREP_HXX

#if !defined(WIN32)
#error "Bitte unter 32-Bit übersetzen";
#endif 

#include <windows.h>
#include <ole2.h>
#include <string>	// strings für CommonView
#include <stdlib.h>

// STL-related stuff
#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#include <stl.h>
#include <ostring.h>
#include <ospace\threads.h>

#include <commonvu.hxx>         // CommonVu - eigene Klassendeklarationen

#include <errcodes.hxx>         // FehlerCodes
#include <xtension.h>           // Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>		// Konstanten und Datenstrukturen

#include <eieruhr.hxx>

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <ixtensnw.hxx>		// InterfaceWrapper

#include <xtencunk.hxx>		// InterfaceImplementation der BasisKlasse
#include <xtsnguid.h>
#include <xtsnaux.hxx>

#include "feature.hxx"		// die Erweiterung selbst

#include "enumonr.hxx"

// Min-Funktion, dan macro aus stdlib offensichtlich überladen ist
template<class T>
inline T tmin (T a, T b) { return (a > b) ? b : a; }

#endif // _FEATUREP_HXX
