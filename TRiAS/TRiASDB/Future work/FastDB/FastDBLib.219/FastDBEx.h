// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 27.02.2000 11:23:00 
//
// @doc
// @module FastDBEx.h | Declaration of additional FastDB macros

#if !defined(_FASTDBEX_H__096CE4CB_1C21_4578_96AE_E1556F152968__INCLUDED_)
#define _FASTDBEX_H__096CE4CB_1C21_4578_96AE_E1556F152968__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// zusätzliche Macros
#define KEY2(x, index, name) \
    *dbDescribeField(new dbFieldDescriptor(name, (char*)&x-(char*)this, \
                                           sizeof(x), index), x)

#define FIELD2(x, name) KEY2(x, 0, name)

// raw binary field
#define RAWFIELD2(x, name) \
    *dbDescribeRawField(new dbFieldDescriptor(name, (char*)&x-(char*)this, \
                                              sizeof(x), 0))

#define REGISTER_IN2(table, database, name) \
    dbTableDescriptor* dbGetTableDescriptor(table*) \
      { return &table::dbDescriptor; }            \
    static dbFieldDescriptor* dbDescribeComponentsOf##table() \
      { return ((table*)0)->dbDescribeComponents(NULL); }     \
    dbTableDescriptor table::dbDescriptor(name, database, sizeof(table), \
                                          &dbDescribeComponentsOf##table)

#define REGISTER2(table, name) REGISTER_IN2(table, NULL, name)
#define REGISTER_UNASSIGNED2(table, name) REGISTER_IN2(table, DETACHED_TABLE, name)

///////////////////////////////////////////////////////////////////////////////
// Libraries einbinden
#if defined(_DEBUG)
#pragma comment (lib, "FastDBd.lib")
#else
#pragma comment (lib, "FastDB.lib")
#endif // defined(_DEBUG)

#endif // !defined(_FASTDBEX_H__096CE4CB_1C21_4578_96AE_E1556F152968__INCLUDED_)
