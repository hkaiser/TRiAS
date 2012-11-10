// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 23.11.2001 10:58:23 
//
// @doc
// @module ObjectPropertyInSeq.h | Declaration of the <c CObjectPropertyInSeq> class

#if !defined(_OBJECTPROPERTYINSEQ_H__378FDC75_9A5C_4E6D_8041_6DC22DB38303__INCLUDED_)
#define _OBJECTPROPERTYINSEQ_H__378FDC75_9A5C_4E6D_8041_6DC22DB38303__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Funktionen, die anzuzeigende Objekteigenschaften schreiben/lesen
const char c_cbDestObjectProperty[] = "DestObjectProperty";

// FORMATETC
const FORMATETC c_feDestObjectProperty = {
	RegisterClipboardFormat (c_cbDestObjectProperty),		// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_ISTREAM,									// DWORD tymed
};

#endif // !defined(_OBJECTPROPERTYINSEQ_H__378FDC75_9A5C_4E6D_8041_6DC22DB38303__INCLUDED_)
