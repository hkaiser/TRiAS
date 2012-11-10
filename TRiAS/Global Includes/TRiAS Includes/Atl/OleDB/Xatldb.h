// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 27.06.2001 13:08:33 
//
// @doc
// @module Xatldb.h | Wrapper for corrected AtlDB.h header file

#if _ATL_VER >= 0x0700
#include <Atl/OleDb/xatldb7.h>
#else
#include <Atl/OleDb/xatldb6.h>
#endif // _ATL_VER >= 0x0700
