// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 22.04.99 15:48:42 
//
// @doc
// @module PropertyActionBaseData.h | Declaration of some global data for
// a PropertyAction

#if !defined(_PROPERTYACTIONBASEDATA_H__A5291D94_F747_11D2_9BF5_247420524153__INCLUDED_)
#define _PROPERTYACTIONBASEDATA_H__A5291D94_F747_11D2_9BF5_247420524153__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

// Erzeugte Infos im durchgereichten IDataObject ------------------------------
// 1. IEnumLONG mit allen selektierten Objekten. Dieser Enumerator ist in einen
// Stream serialisiert, der im CDataObject übergeben wird.
// 
// ClipBoardFormat
extern const TCHAR c_cbPASelectedObjects[];

//
// FORMATETC
extern const FORMATETC c_feSelectedObjects; 

///////////////////////////////////////////////////////////////////////////////
// InitialisierungsInfo für eine PropertyAction
// Wird durch ein gestreamten Variant gespeichert

// ClipBoardFormat
extern const TCHAR c_cbInitPropAct[];

//
// FORMATETC
extern const FORMATETC c_feInitPropAct;

#endif // !defined(_PROPERTYACTIONBASEDATA_H__A5291D94_F747_11D2_9BF5_247420524153__INCLUDED_)
