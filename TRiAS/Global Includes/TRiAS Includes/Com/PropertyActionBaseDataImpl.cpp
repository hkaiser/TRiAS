// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 31.08.99 11:36:59
//
// @doc
// @module PropertyActionBaseDataImpl.cpp | Definition of some global data for
// a PropertyAction

#if !defined(_PROPERTYACTIONBASEDATAIMPL_CPP__DEBCECE8_B701_404B_883D_369E3884C61D__INCLUDED_)
#define _PROPERTYACTIONBASEDATAIMPL_CPP__DEBCECE8_B701_404B_883D_369E3884C61D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Com/PropertyActionBaseData.h>

// Erzeugte Infos im durchgereichten IDataObject ------------------------------
// 1. IEnumLONG mit allen selektierten Objekten. Dieser Enumerator ist in einen
// Stream serialisiert, der im CDataObject übergeben wird.
// 
// ClipBoardFormat
extern const TCHAR c_cbPASelectedObjects[] = TEXT("EnumSelectedObjects");

//
// FORMATETC
extern const FORMATETC c_feSelectedObjects = 
{
	RegisterClipboardFormat (c_cbPASelectedObjects),// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_ISTREAM,									// DWORD tymed
};

///////////////////////////////////////////////////////////////////////////////
// InitialisierungsInfo für eine PropertyAction
// Wird durch ein gestreamten Variant gespeichert

// ClipBoardFormat
extern const TCHAR c_cbInitPropAct[] = TEXT("InitPropActFromData");

extern const FORMATETC c_feInitPropAct = 
{
	RegisterClipboardFormat (c_cbInitPropAct),		// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_ISTREAM,									// DWORD tymed
};

#endif // !defined(_PROPERTYACTIONBASEDATAIMPL_CPP__DEBCECE8_B701_404B_883D_369E3884C61D__INCLUDED_)
