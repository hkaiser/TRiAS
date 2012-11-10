//	Precompiled Header für EDBS-Import

#ifndef	_STDAFX_H_
#define _STDAFX_H_

#include <afxctl.h>
#include <afxext.h>

#ifndef WIN32
#include <ole16.h>
#endif	// WIN32

#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <containr.hxx>
#include <errcodes.hxx>         // FehlerCodes

#include <xtension.h>           // Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>		// Konstanten und Datenstrukturen

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <xtencunk.hxx>		// InterfaceImplementation der BasisKlasse
#include <xtsnaux.hxx>
#include <xtsnimp.hxx>		// ImportInterface

#include "import.hpp"		// ImportInterface
// #include "ascimp.hpp"		// die Erweiterung selbst

// #include "ascpars.h"
// #include "ascerrs.h"
// #include "input.h"

#endif	// _STDAFX_H_
