// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 26.02.2001 14:27:33 
//
// @doc
// @module ObjectPropertyResult.h | Declaration of the <c CObjectPropertyResult> class

#if !defined(_OBJECTPROPERTYRESULT_H__AD4C8C4D_2A11_4DC0_8F74_BAC3B1380FCA__INCLUDED_)
#define _OBJECTPROPERTYRESULT_H__AD4C8C4D_2A11_4DC0_8F74_BAC3B1380FCA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Das Bezugsobjekt, für welches eine Objekteigenschaft berechnet wird
const char c_cbObjPropTarget[] = "ObjPropTarget";

// FORMATETC
const FORMATETC c_feObjPropTarget = {
	RegisterClipboardFormat (c_cbObjPropTarget),	// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_ISTREAM,									// DWORD tymed
};

///////////////////////////////////////////////////////////////////////////////
// Das Ergebnis der Berechnung einer Objekteigenschaft
const char c_cbObjPropResult[] = "ObjPropResult";

// FORMATETC
const FORMATETC c_feObjPropResult = {
	RegisterClipboardFormat (c_cbObjPropResult),	// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_ISTREAM,									// DWORD tymed
};

#endif // !defined(_OBJECTPROPERTYRESULT_H__AD4C8C4D_2A11_4DC0_8F74_BAC3B1380FCA__INCLUDED_)
