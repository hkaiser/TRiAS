// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 18.05.2000 22:17:28 
//
// @doc
// @module StreamCast.h | Declaration of the <c stream_cast> class

#if !defined(_STREAMCAST_H__F68EBE00_5FA9_42F1_8F80_001AB1DA372A__INCLUDED_)
#define _STREAMCAST_H__F68EBE00_5FA9_42F1_8F80_001AB1DA372A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <strstrea.h>

template<typename Target, typename Source>
inline Target stream_cast(Source arg)
{
strstream interpreter;
Target result = Target();

	interpreter << arg;
	interpreter >> result;
	return result;
}

#endif // !defined(_STREAMCAST_H__F68EBE00_5FA9_42F1_8F80_001AB1DA372A__INCLUDED_)
