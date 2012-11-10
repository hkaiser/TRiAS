// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 10/22/1998 03:20:42 PM
//
// @doc
// @module TRiASMainConfig.h | Konfigurationskonstanten für TRiAS-Main

#if !defined(_TRIASMAINCONFIG_H__2100523A_6792_11D2_9EDE_006008447800__INCLUDED_)
#define _TRIASMAINCONFIG_H__2100523A_6792_11D2_9EDE_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// globale Konfigurationskonstanten
//#define _MERGE_PROXYSTUB
//#define _USE_TRIAS_MESSAGES
#define __ATL_USED__				// ATL in diesem Projekt verwenden
#define __OSPACESTL_USED__			// OspaceSTL in diesem Projekt verwenden
#define __CV__

#if defined(_DEBUG)
#define _ATLX_ASSERT_ON_FAILURE
#define _CRTDBG_MAP_ALLOC			// track memory leaks
#define USE_DLIB					// DumpLib verwenden
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// lokale Konfigurationskonstanten
#define __TRIASEXE__
#define _GERMAN_RESOURCES			// deutsche Resourcen verwenden

//#define _USE_LEGACY_CODE			// zu V2.10 kompatiblen Code erzeugen

#define NOPROJEKTION
#define NOGITTER

#define DECLAREMAPFUNCTIONS
#define DECLAREMAPFUNCTIONS_NOTIFY

#define _USE_FLICKERFREE_DRAWING	// Flimmerfreies Zeichnen erlauben
#define _NEWORMENU					// neues Menu im Recherchefenster
#define _KOORD_ISDOUBLE				// intern double-Koordinaten verwenden
#define _USE_TRANSPARENT_PATTERNS	// durchsichtige Patterns sind implementiert
#define _USE_NEWVISINFO				// neue VisInfo-Objekte verwenden

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition rausnehmen, wenn die keine ClassFactories im cache 
// gehalten werden sollen (s. CLASSFACTORY_CACHE_BEGIN etc.)
#define _USE_CLASSFACTORY_CACHE

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition rausnehmen, wenn für den Objekt-Doppelbaum COptTree
// bzw. CDelTree verwendet werden sollen (ansonsten map/multimap)
#define _USE_MAP_FOR_OBJEKTLISTE

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition reinnehmen, wenn keine Assembleroptimierung an 
// den kritischen Stellen erfolgen soll
//#define _NO_ASSEMBLY_OPTIMIZATIONS

///////////////////////////////////////////////////////////////////////////////
// Die folgende Definition rausnehmen, wenn in OCtoDC die Koordinaten einzeln 
// aus einem TRiASCSPoints -Objekt geholt werden sollen
#define _USE_GETPOINT_N

///////////////////////////////////////////////////////////////////////////////
// optimize CTF.hxx (keep in sync with TRiAS02)
#define _CTF_USE_POINTMEMBER

#endif // !defined(_TRIASMAINCONFIG_H__2100523A_6792_11D2_9EDE_006008447800__INCLUDED_)

