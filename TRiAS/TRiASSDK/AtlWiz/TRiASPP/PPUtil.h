// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 28.08.99 22:04:50 
//
// @doc
// @module PPUtil.h | Utility functions and structures

#if !defined(_PPUTIL_H__CB358F02_5D83_11D3_9504_0080C786297B__INCLUDED_)
#define _PPUTIL_H__CB358F02_5D83_11D3_9504_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

// utility functions
inline ULONG atob (LPCSTR pcStr)
{
ULONG lResult = 0L;

	while (NULL != pcStr && '\0' != *pcStr) {
		_ASSERTE('0' == *pcStr || '1' == *pcStr);	// should be binary
		lResult = (lResult << 1) + *pcStr++ - '0';
	}
	return lResult;
}

// Data structures
typedef struct tagCONTROL {
	UINT uiBit;
	UINT uiResID;
	bool fCheck;
} CONTROL;

#endif // !defined(_PPUTIL_H__CB358F02_5D83_11D3_9504_0080C786297B__INCLUDED_)
