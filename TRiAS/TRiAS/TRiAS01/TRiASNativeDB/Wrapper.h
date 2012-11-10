// $Header: $
// Copyright© 2001 Hartmut Kaiser, All rights reserved
// Created: 11.04.2001 11:27:02 
//
// @doc
// @module Wrapper.h | Definition of smart interface wrapper classes

#if !defined(_WRAPPER_H__B8904B78_7079_412C_B3CA_3D820DCAEF54__INCLUDED_)
#define _WRAPPER_H__B8904B78_7079_412C_B3CA_3D820DCAEF54__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// system interfaces
DefineSmartInterface(Storage);

///////////////////////////////////////////////////////////////////////////////
// local interfaces
DefineSmartInterface(TRiASEnumNativeIdents);
DefineSmartInterface(TRiASEnumNativeObjects);
DefineSmartInterface(TRiASEnumNativeAttributes);

#endif // !defined(_WRAPPER_H__B8904B78_7079_412C_B3CA_3D820DCAEF54__INCLUDED_)
