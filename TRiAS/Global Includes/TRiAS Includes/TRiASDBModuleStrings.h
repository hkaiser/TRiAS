// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 26.08.99 13:52:44 
//
// @doc
// @module TRiASDBModuleStrings.h | Definition of global string constants

#if !defined(_TRIASDBMODULESTRINGS_H__BD5260B0_5BAC_11D3_9504_0080C786297B__INCLUDED_)
#define _TRIASDBMODULESTRINGS_H__BD5260B0_5BAC_11D3_9504_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(__cplusplus)
extern "C" {
#endif // defined(__cplusplus)

// Properties der Connection
	__declspec(selectany) const unsigned short * CONNECTIONPROPERTIES_CSS = L"CTFService";

// Recherchekommandos für 'normale' Objekteigenschaften
	__declspec(selectany) const unsigned short * SEARCHCOMMAND_MatchComplete = L"MatchComplete";	// vollständige Übereinstimmung
	__declspec(selectany) const unsigned short * SEARCHCOMMAND_MatchRegExpr = L"MatchRegExpr";	// Regulären Ausdruck verwenden
	__declspec(selectany) const unsigned short * SEARCHCOMMAND_MatchLike = L"MatchLike";			// 'ungefähre' Übereinstimmung
	__declspec(selectany) const unsigned short * SEARCHCOMMAND_ExistanceOnly = L"ExistanceOnly";	// lediglich Existenz testen

// Recherchekommandos für Geometrie-Objekteigenschaften
	__declspec(selectany) const unsigned short * SEARCHCOMMAND_IntersectsWindow = L"IntersectsWindow";

// Zusätzliche Rechercheoptionen, die mit den SEARCHCOMMAND's kombiniert werden können
	__declspec(selectany) const unsigned short * SEARCHOPTION_PartialMatch = L"PartialMatch";	// Teilzeichenkette
	__declspec(selectany) const unsigned short * SEARCHOPTION_PartialMatchBOB = L"PartialMatchBOB"; // Teilzeichenkette am Anfang
	__declspec(selectany) const unsigned short * SEARCHOPTION_IgnoreCase = L"IgnoreCase";		// Groß-/Kleinschreibung ignorieren
	__declspec(selectany) const unsigned short * SEARCHOPTION_NegateResult = L"NegateResult";	// invertierte Objektmenge liefern

// Objekte dieser Objektklasse besitzen als eindeutiges Objektkennzeichen einen GUID
	__declspec(selectany) const unsigned short * FEATUREPROPERTY_HasObjectGuid = L"HasObjGuid";		

#if defined(__cplusplus)
} // extern "C" 
#endif // defined(__cplusplus)

#endif // !defined(_TRIASDBMODULESTRINGS_H__BD5260B0_5BAC_11D3_9504_0080C786297B__INCLUDED_)
