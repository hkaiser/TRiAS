// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 18.01.2001 22:43:19 
//
// @doc
// @module mitab_capi_ex.h | Additional functions for the mitab C-API

#if !defined(_MITAB_CAPI_EX_H__16435B91_50A1_4FC2_B9B1_57890D24DBCB__INCLUDED_)
#define _MITAB_CAPI_EX_H__16435B91_50A1_4FC2_B9B1_57890D24DBCB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// retrieve width of a field
MITAB_DLL int MITAB_STDCALL mitab_c_get_field_width( mitab_handle handle, int field );

// Get the text string on a TABFC_Text object
MITAB_DLL const char * MITAB_STDCALL mitab_c_get_text( mitab_feature feature );

// Get a TABFC_Text text properties
MITAB_DLL double MITAB_STDCALL mitab_c_get_text_angle( mitab_feature feature );
MITAB_DLL TABTextJust MITAB_STDCALL mitab_c_get_text_alignment( mitab_feature feature );

// get minimum bounding rect of a feature
MITAB_DLL bool MITAB_STDCALL mitab_c_get_mbr( mitab_feature feature, double &rdXMin, double &rdYMin, double &rdXMax, double &rdYMax);

// get raw coordinates
MITAB_DLL const OGRRawPoint * MITAB_STDCALL mitab_c_get_raw_coords (mitab_feature feature, int iPart = 0);

#endif // !defined(_MITAB_CAPI_EX_H__16435B91_50A1_4FC2_B9B1_57890D24DBCB__INCLUDED_)
