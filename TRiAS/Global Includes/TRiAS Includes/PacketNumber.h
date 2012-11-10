// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.11.2000 13:13:56 
//
// @doc
// @module PacketNumber.h | Declaration of the <c CPacketNumber> class

#if !defined(_PACKETNUMBER_H__5054641A_1C2C_4D69_9D81_F0CBFA790141__INCLUDED_)
#define _PACKETNUMBER_H__5054641A_1C2C_4D69_9D81_F0CBFA790141__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Funktionen, die BegleitNummern der Datenpakete schreiben/lesen
const char c_cbPacketNumber[] = "PacketNumber";

// FORMATETC
const FORMATETC c_fePacketNumber = {
	RegisterClipboardFormat (c_cbPacketNumber),		// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_ISTREAM,									// DWORD tymed
};

#endif // !defined(_PACKETNUMBER_H__5054641A_1C2C_4D69_9D81_F0CBFA790141__INCLUDED_)
