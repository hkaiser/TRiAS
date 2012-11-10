// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.11.2000 21:11:16 
//
// @doc
// @module Esnecil.h | Declaration of the <c CEsnecil> class

#if !defined(_ESNECIL_H__D8C4BBC3_A1FF_45EE_B4EA_17FC8702B9D6__INCLUDED_)
#define _ESNECIL_H__D8C4BBC3_A1FF_45EE_B4EA_17FC8702B9D6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Helperklasse für die Lizensierung von TRiAS4
class CEsnecil
{
public:
	CEsnecil();
	~CEsnecil();

	bool VerifyOptions (unsigned long iOption);
	bool VerifyLevel (long lRequiredLevel);
	bool IsLevelEqual (long lLevelToCompare);
	bool IsDemoCopy();
	
	bool IsValid() { return m_fIsValid; }

#if defined(_DEBUG)
	unsigned long GetOptions();
	long GetLevel();
#endif // defined(_DEBUG)

protected:
	void Init();

private:
	unsigned long m_ulOptions;
	long m_lLevel;
	bool m_fIsValid;
};

///////////////////////////////////////////////////////////////////////////////
// Existierende Optionen
#define CKIOPTION_ARCVIEW			0x0001		// ArcView Import/Export
#define CKIOPTION_MAPINFO			0x0002		// MapInfo Import/Export
#define CKIOPTION_KOMPAKT			0x0004		// Gewässerkataster
#define CKIOPTION_ATKIS				0x0008		// Atkis Import
#define CKIOPTION_ALK				0x0010		// ALK Import
#define CKIOPTION_SABIS				0x0020		// SABiS Kopplung
#define CKIOPTION_RASTERIMPORT		0x0040		// Rasterkartenimport
#define CKIOPTION_GCOPRODUCTION		0x0080		// GCO Spezifika
#define CKIOPTION_INTERNAL_FEATURES	0x0100		// Interne Features

#define CKIOPTION_ALL		(	\
			CKIOPTION_ARCVIEW |	\
			CKIOPTION_MAPINFO | \
			CKIOPTION_KOMPAKT | \
			CKIOPTION_ATKIS |	\
			CKIOPTION_ALK |		\
			CKIOPTION_SABIS |	\
			CKIOPTION_RASTERIMPORT | \
			CKIOPTION_GCOPRODUCTION | \
			CKIOPTION_INTERNAL_FEATURES \
		)

#define CKIOPTION_MASK				0xFFFFFF	// 24 Bit für Optionen
#define CKIOPTION_MAXCOUNT			24

///////////////////////////////////////////////////////////////////////////////
// Existierende Levels
#define CKILEVEL_DEMO				0			// Demovariante

#if _TRiAS_VER < 0x0510
#define CKILEVEL_ANALYSE			1			// TRiAS4 Analyse
#define CKILEVEL_PLUS				2			// TRiAS4 Plus
#define CKILEVEL_ANALYSE_OBSOLETE	1			// TRiAS4 Analyse
#define CKILEVEL_PLUS_OBSOLETE		2			// TRiAS4 Plus
#define CKILEVEL_TRiAS				2			// gesamtes TRiAS
#define CKILEVEL_SERVICE			2			// mit Servicevertrag
#else
#define CKILEVEL_ANALYSE_OBSOLETE	1			// TRiAS4 Analyse (obsolete)
#define CKILEVEL_PLUS_OBSOLETE		2			// TRiAS4 Plus (obsolete)
#define CKILEVEL_ANALYSE			3			// TRiAS4 Analyse (obsolete)
#define CKILEVEL_PLUS				3			// TRiAS4 Plus (obsolete)
#define CKILEVEL_TRiAS				3			// gesamtes TRiAS
#define CKILEVEL_SERVICE			4			// mit Servicevertrag
#endif // _TRiAS_VER < 0x0510

#define CKILEVEL_MASK				0xFF		// 8 Bit für Level
#define MIN_CKILEVEL				CKILEVEL_DEMO
#define MAX_CKILEVEL				CKILEVEL_SERVICE

///////////////////////////////////////////////////////////////////////////////
// globale Instanz der Lizensierung-Helperklasse
extern CEsnecil m_esnecil;

///////////////////////////////////////////////////////////////////////////////
// Libraries einbinden
#if defined(_DEBUG)
#pragma comment(lib, "esnecild.lib")
#else
#pragma comment(lib, "esnecil.lib")
#endif // defined(_DEBUG)

#endif // !defined(_ESNECIL_H__D8C4BBC3_A1FF_45EE_B4EA_17FC8702B9D6__INCLUDED_)
