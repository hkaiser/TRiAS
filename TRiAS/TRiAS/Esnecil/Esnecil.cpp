// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 09.11.2000 10:07:12 
//
// @doc
// @module Esnecil.cpp | Definition of the <c CEsnecil> class

#include "StdAfx.h"

#include <Esnecil.h>
#include <d_lib/d_lib.h>

///////////////////////////////////////////////////////////////////////////////
// globale Klasse wird bei Programmstart erzeugt und am Ende freigegeben
CEsnecil m_esnecil;

///////////////////////////////////////////////////////////////////////////////
// Initialisation
CEsnecil::CEsnecil() :
	m_ulOptions(0), m_lLevel(0), m_fIsValid(false)
{
	Init();
}

CEsnecil::~CEsnecil()
{
}

void CEsnecil::Init()
{
char cbBuffer[16], cbFormat[32], cbO[32], cbL[32];

// Format vorbereiten
	cbFormat[0] = '\0';
	for (int i = 0; i < 11; ++i)
		strcat (cbFormat, "%c");

// Options einlesen
	wsprintf (cbBuffer, cbFormat, '%', 'C', 'K', 'O', 'P', 'T', 'I', 'O', 'N', 'S', '%');
	ExpandEnvironmentStrings (cbBuffer, cbO, sizeof(cbO));
	m_ulOptions = strtoul (cbO, NULL, 10) & CKIOPTION_MASK;
	D_OUTF3(3, "TRiAS: Lizenz: %s: ", cbBuffer, "%s, ", cbO, "%lx", m_ulOptions);

	if (m_ulOptions & ~CKIOPTION_ALL)
		return;		// unbekannte Option 

// Level einlesen
	wsprintf (cbBuffer, cbFormat, '%', 'C', 'K', 'L', 'E', 'V', 'E', 'L', '%', '\0', '\0');
	ExpandEnvironmentStrings (cbBuffer, cbL, sizeof(cbL));
	m_lLevel = strtoul (cbL, NULL, 10) & CKILEVEL_MASK;
	D_OUTF3(3, "TRiAS: Lizenz: %s: ", cbBuffer, "%s, ", cbL, "%lx", m_lLevel);

	if (m_lLevel < MIN_CKILEVEL || m_lLevel > MAX_CKILEVEL)	// Gültigkeit testen
		return;		// unbekanntes Level

	if (CKILEVEL_ANALYSE_OBSOLETE == m_lLevel || 
		CKILEVEL_PLUS_OBSOLETE == m_lLevel)
	{
		return;		// obsolete Levels
	}

// jetzt ist alles gültig
	m_fIsValid = true;
}

///////////////////////////////////////////////////////////////////////////////
// Methods
bool CEsnecil::VerifyOptions (unsigned long iOptions) 
{ 
	return (IsValid() && (iOptions == (iOptions & m_ulOptions))) ? true : false; 
}

bool CEsnecil::VerifyLevel (long lRequiredLevel) 
{ 
	return (IsValid() && (lRequiredLevel <= m_lLevel)) ? true : false; 
}

bool CEsnecil::IsLevelEqual (long lLevelToCompare) 
{ 
	if (CKILEVEL_DEMO == lLevelToCompare)
		return IsDemoCopy();

	return (IsValid() && (lLevelToCompare == m_lLevel)) ? true : false; 
}

bool CEsnecil::IsDemoCopy()
{
	return (!IsValid() || m_lLevel == CKILEVEL_DEMO) ? true : false;
}

#if defined(_DEBUG)
unsigned long CEsnecil::GetOptions()
{
	return m_ulOptions;
}

long CEsnecil::GetLevel()
{
	return m_lLevel;
}
#endif // defined(_DEBUG)

