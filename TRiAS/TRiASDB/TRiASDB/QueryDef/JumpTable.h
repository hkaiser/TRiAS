// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.03.2000 19:21:40 
//
// @doc
// @module JumpTable.h | Declaration of the jumptable support

#if !defined(_JUMPTABLE_H__25643DA0_0AE6_4518_A38A_248D88F6FE7F__INCLUDED_)
#define _JUMPTABLE_H__25643DA0_0AE6_4518_A38A_248D88F6FE7F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// vorgegebene FunktionsTabellen (compilergeneriert)
//typedef LRESULT (CQueryDefExtension::*DEXMESSAGEPROC)(HPROJECT, LPARAM);

typedef struct tagDEXMESSAGEENTRY {
	WPARAM m_uiMsg;				// CommandID
	CQueryDefExtension::DEXMESSAGEPROC m_pProc;		// zugehörige Funktion
} DEXMESSAGEENTRY;

///////////////////////////////////////////////////////////////////////////////
// Sprungverteilertabelle
#if defined(_DEBUG)
#define EXTFCNENTRY(msg,fcn,t)			{msg,CQueryDefExtension::fcn}
#define EXTFCNENTRY2(msg,fcn,proc,t)	{msg,CQueryDefExtension::fcn}
#else
#define EXTFCNENTRY(msg,fcn,t)			{msg,CQueryDefExtension::fcn}
#define EXTFCNENTRY2(msg,fcn,proc,t)	{msg,CQueryDefExtension::fcn}
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// statische (compilergenerierte) Sprungverteilertabelle
const DEXMESSAGEENTRY DexMessageEntries[] = {
// in dieser Erweiterung definierte command handler
	EXTFCNENTRY(DEX_ADDOBJECT2CLASS, AddObjectToClass, TRACE_LEVEL4),
	EXTFCNENTRY(DEX_DELETEOBJECTFROMCLASS, DeleteObjectFromClass, TRACE_LEVEL4),
	EXTFCNENTRY(DEX_OBJECTISINCLASS, IsObjectInClass, TRACE_LEVEL4),
	EXTFCNENTRY(DEX_ENUMCLASSESFROMOBJECT, EnumObjectClasses, TRACE_LEVEL4),
	EXTFCNENTRY(DEX_QUERYNATIVEOBJECT, OnGetNativeObject, TRACE_LEVEL4),

// Messages, die abgefangen und u.U. hier implementiert werden
	EXTFCNENTRY(DEX_QUERYOBJIDENT, OnGetObjectIdent, TRACE_LEVEL4),
	EXTFCNENTRY(DEX_DELOBJECT, OnDeleteObject, TRACE_LEVEL4),
	EXTFCNENTRY(DEX_DELOBJECTEX, OnDeleteObjectEx, TRACE_LEVEL4),
	EXTFCNENTRY(DEX_DELETEOBJECTUNDORECT, OnDeleteObjectUndorect, TRACE_LEVEL4),
};

#endif // !defined(_JUMPTABLE_H__25643DA0_0AE6_4518_A38A_248D88F6FE7F__INCLUDED_)
