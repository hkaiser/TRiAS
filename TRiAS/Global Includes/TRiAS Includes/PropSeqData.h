// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 17.10.2000 08:35:20 
//
// @doc
// @module PropSeqData.h | Kontextinfo für PropertySequence

#if !defined(_PROPSEQDATA_H__5890D8DA_D564_4E79_A72C_8AD908B31545__INCLUDED_)
#define _PROPSEQDATA_H__5890D8DA_D564_4E79_A72C_8AD908B31545__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Kontextinfo: FensterHandle des HauptFensters (HWND), aus welchem Befehl 
// ausgelöst wurde

// ClipBoardFormate
const char c_cbMainWindow[] = "MainWindow";

//
// FORMATETC
const FORMATETC c_feMainWindow = {
	RegisterClipboardFormat (c_cbMainWindow),		// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_HGLOBAL,									// DWORD tymed
};

#endif // !defined(_PROPSEQDATA_H__5890D8DA_D564_4E79_A72C_8AD908B31545__INCLUDED_)
