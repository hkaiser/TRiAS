// $Header: $
// Copyright© 1999-2001 VNS GmbH Potsdam, All rights reserved
// Created: 10.10.2001 08:06:21 
//
// @doc
// @module DeclareHandles.h | Declaration of the <c CDeclareHandles> class

#if !defined(_DECLAREHANDLES_H__D9C03A13_3C34_4333_84D6_E192E964FCDE__INCLUDED_)
#define _DECLAREHANDLES_H__D9C03A13_3C34_4333_84D6_E192E964FCDE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// ProjectHandle
#if defined(MSWIND) || defined(_WINDOWS)
#if !defined(_DEFINED_HPROJECT)
#define _DEFINED_HPROJECT
DECLARE_HANDLE(HPROJECT);
#define HACTPROJECT 	((HPROJECT)(-1))		// bezieht sich auf Projekt
#define HACTCONNECTION	((HPROJECT)(NULL))		// bezieht sich auf aktuelle Datenquelle
#if defined(__cplusplus)
inline HPROJECT Index2HPROJECT(int iIndex)
{
	return reinterpret_cast<HPROJECT>(iIndex+1);
}
inline int HPROJECT2Index(HPROJECT hPr)
{
	return reinterpret_cast<int>(hPr)-1;
}
#endif // defined(__cplusplus)
#endif
#else
#define HPROJECT int
#endif

///////////////////////////////////////////////////////////////////////////////
// Handletypen für Objektklassen, Objekte und Attribute
#if defined(_USE_REAL_HANDLES)
// neue Definitionen, die ein Mischen verhindern
#if !defined(_DEFINED_HOBJECTS)
#define _DEFINED_HOBJECTS
DECLARE_HANDLE(HOBJECTS);
#define INVALID_HOBJECTS ((HOBJECTS)(NULL))		// ungültige Handles
#endif // !defined(_DEFINED_HOBJECTS)

#if !defined(_DEFINED_HOBJECT)
#define _DEFINED_HOBJECT
DECLARE_HANDLE(HOBJECT);
#define INVALID_HOBJECT  ((HOBJECT)(NULL))
#endif // !defined(_DEFINED_HOBJECT)

#if !defined(_DEFINED_HFEATURE)
#define _DEFINED_HFEATURE
DECLARE_HANDLE(HFEATURE);
#define INVALID_HFEATURE ((HFEATURE)(NULL))
#endif // !defined(_DEFINED_HFEATURE)

#if !defined(_DEFINED_HRELATION)
#define _DEFINED_HRELATION
DECLARE_HANDLE(HRELATION);
#define INVALID_HRELATION ((HRELATION)(NULL))
#endif // !defined(_DEFINED_HFEATURE)

#if !defined(_DEFINED_HGENERIC)
#define _DEFINED_HGENERIC
DECLARE_HANDLE(HGENERIC);
#define INVALID_HGENERIC ((HGENERIC)(NULL))
#endif // !defined(_DEFINED_HFEATURE)

#else

// Übergangsdefinitionen für Handletypen
#if !defined(_DEFINED_HOBJECTS)
#define _DEFINED_HOBJECTS
typedef INT_PTR HOBJECTS;
#define INVALID_HOBJECTS ((HOBJECTS)(NULL))		// ungültige Handles
#endif // !defined(_DEFINED_HOBJECTS)

#if !defined(_DEFINED_HOBJECT)
#define _DEFINED_HOBJECT
typedef INT_PTR HOBJECT;
#define INVALID_HOBJECT  ((HOBJECT)(NULL))
#endif // !defined(_DEFINED_HOBJECT)

#if !defined(_DEFINED_HFEATURE)
#define _DEFINED_HFEATURE
typedef INT_PTR HFEATURE;
#define INVALID_HFEATURE ((HFEATURE)(NULL))
#endif // !defined(_DEFINED_HFEATURE)

#if !defined(_DEFINED_HRELATION)
#define _DEFINED_HRELATION
typedef INT_PTR HRELATION;
#define INVALID_HRELATION ((HRELATION)(NULL))
#endif // !defined(_DEFINED_HRELATION)

#if !defined(_DEFINED_HGENERIC)
#define _DEFINED_HGENERIC
typedef INT_PTR HGENERIC;
#define INVALID_HGENERIC ((HGENERIC)(NULL))
#endif // !defined(_DEFINED_HGENERIC)

#endif // defined(_USE_REAL_HANDLES)

#endif // !defined(_DECLAREHANDLES_H__D9C03A13_3C34_4333_84D6_E192E964FCDE__INCLUDED_)
