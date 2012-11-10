// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 02/18/1999 09:37:15 PM
//
// @doc 
// @module JumpTable.h | Sprungverteilertabelle für TRiAS-DEX_... commands

#if !defined(_JUMPTABLE_H__710B2C37_890F_11D2_9EFB_006008447800__INCLUDED_)
#define _JUMPTABLE_H__710B2C37_890F_11D2_9EFB_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// vorgegebene FunktionsTabellen (compilergeneriert)
typedef LRESULT (CIdentsDBExtension::*DEXMESSAGEPROC)(HPROJECT, LPARAM);
typedef LPCSTR (CIdentsDBExtension::*DEXMSGDUMPPROC)(HPROJECT, LPARAM);

typedef struct tagDEXMESSAGEENTRY {
	WPARAM m_uiMsg;				// CommandID
	DEXMESSAGEPROC m_pProc;		// zugehörige Funktion
} DEXMESSAGEENTRY;

///////////////////////////////////////////////////////////////////////////////
// eigentliche compilergenerierte Sprungverteilertabelle
#if defined(_DEBUG)
#define EXTFCNENTRY(msg,fcn,t)			{msg,CIdentsDBExtension::fcn}
#define EXTFCNENTRY2(msg,fcn,proc,t)	{msg,CIdentsDBExtension::fcn}
#else
#define EXTFCNENTRY(msg,fcn,t)			{msg,CIdentsDBExtension::fcn}
#define EXTFCNENTRY2(msg,fcn,proc,t)	{msg,CIdentsDBExtension::fcn}
#endif // _DEBUG

const DEXMESSAGEENTRY DexMessageEntries[] = {
	EXTFCNENTRY(DEX_DEFINENEWOBJECTS, OnDefineNewObjects, TRACE_LEVEL4),
};

#endif // !defined(_JUMPTABLE_H__710B2C37_890F_11D2_9EFB_006008447800__INCLUDED_)
