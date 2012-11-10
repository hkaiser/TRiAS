// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 28.02.2000 19:42:37 
//
// @doc
// @module GigaBASEEx.h | Declaration of additional GigaBASE macros

#if !defined(_GIGABASEEX_H__8CF4421B_E0EE_4878_B3BF_532B8224E4FC__INCLUDED_)
#define _GIGABASEEX_H__8CF4421B_E0EE_4878_B3BF_532B8224E4FC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// zusätzliche Macros
#define KEY(x, index) \
    *dbDescribeField(new dbFieldDescriptor(#x, (char*)&x-(char*)this, \
                                           sizeof(x), index), x)

#define FIELD(x) KEY(x, 0)

// raw binary field
#define RAWFIELD(x) \
    *dbDescribeRawField(new dbFieldDescriptor(#x, (char*)&x-(char*)this, \
                                              sizeof(x), 0))

#ifdef __INSURE__
#define REGISTER_IN(table, database) \
    dbTableDescriptor* dbGetTableDescriptor(table*) \
      { return &table::dbDescriptor; }            \
    dbTableDescriptor table::dbDescriptor(#table, database, sizeof(table), \
                                       (new table)->dbDescribeComponents(NULL))
#else
#define REGISTER_IN(table, database) \
    dbTableDescriptor* dbGetTableDescriptor(table*) \
      { return &table::dbDescriptor; }            \
    dbTableDescriptor table::dbDescriptor(#table, database, sizeof(table), \
                                       ((table*)0)->dbDescribeComponents(NULL))

#endif
#define REGISTER(table) REGISTER_IN(table, NULL)

///////////////////////////////////////////////////////////////////////////////
// Libraries einbinden
#if defined(_DEBUG)
#pragma comment (lib, "GigaBASEd.lib")
#else
#pragma comment (lib, "GigaBASE.lib")
#endif // defined(_DEBUG)

#endif // !defined(_GIGABASEEX_H__8CF4421B_E0EE_4878_B3BF_532B8224E4FC__INCLUDED_)
