// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.03.2000 19:23:41 
//
// @doc
// @module DexCommands.h | Declaration of the DexCommands implemented here

#if !defined(_DEXCOMMANDS_H__DDD9FD4D_8779_424E_97E3_2D29FF0590A8__INCLUDED_)
#define _DEXCOMMANDS_H__DDD9FD4D_8779_424E_97E3_2D29FF0590A8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// in dieser Erweiterung definierte command handler
	LRESULT AddObjectToClass (HPROJECT hPr, LPARAM lParam);			// DEX_ADDOBJECT2CLASS
	LRESULT DeleteObjectFromClass (HPROJECT hPr, LPARAM lParam);	// DEX_DELETEOBJECTFROMCLASS
	LRESULT IsObjectInClass (HPROJECT hPr, LPARAM lParam);			// DEX_OBJECTISINCLASS
	LRESULT EnumObjectClasses (HPROJECT hPr, LPARAM lParam);		// DEX_ENUMCLASSESFROMOBJECT
	LRESULT OnGetNativeObject (HPROJECT hPr, LPARAM lParam);		// DEX_QUERYNATIVEOBJECT

// Messages, die abgefangen und u.U. hier implementiert werden
	LRESULT OnGetObjectIdent (HPROJECT hPr, LPARAM lParam);			// DEX_QUERYOBJIDENT
	LRESULT OnDeleteObject (HPROJECT hPr, LPARAM lParam);			// DEX_DELOBJECT
	LRESULT OnDeleteObjectEx (HPROJECT hPr, LPARAM lParam);			// DEX_DELOBJECTEX
	LRESULT OnDeleteObjectUndorect (HPROJECT hPr, LPARAM lParam);	// DEX_DELETEOBJECTUNDORECT

// last resort
	LRESULT OnNotImplementedMessage (HPROJECT hPr, LPARAM lParam);

#endif // !defined(_DEXCOMMANDS_H__DDD9FD4D_8779_424E_97E3_2D29FF0590A8__INCLUDED_)
