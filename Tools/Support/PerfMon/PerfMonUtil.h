// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/28/1998 10:31:47 PM
//
// @doc
// @module PerfMonUtil.h | Helperfunktionen

#if !defined(_PERFMONUTIL_H__467452A4_9CBA_11D2_9F09_006008447800__INCLUDED_)
#define _PERFMONUTIL_H__467452A4_9CBA_11D2_9F09_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

/////////////////////////////////////////////////////////////////////////////
// Support for IPersistMemory
template<class T>
inline void SaveAndAdvance (void *& p, T x)
{
	memcpy (p, (void *)&x, sizeof(T));
	p = (BYTE *)p + sizeof(T); 
}
inline void SaveAndAdvance (void *& p, void *px, unsigned int iSize)
{
	memcpy (p, px, iSize);
	p = (BYTE *)p + iSize; 
}

inline size_t Distance (void *p1, void *p2)
{
	return (BYTE *)p1 - (BYTE *)p2;
}

inline void Advance (void *& p, size_t delta)
{
	p = (BYTE *)p + delta;
}

///////////////////////////////////////////////////////////////////////////////
// CounterGröße aus CounterTyp bestimmen
inline DWORD SizeFromType (DWORD rgType)
{
	switch (rgType & 0x0300) {
	case PERF_SIZE_DWORD:	return sizeof(DWORD);
	case PERF_SIZE_LARGE:	return sizeof(LARGE_INTEGER);
	case PERF_SIZE_ZERO:
	default:
		_ASSERTE(PERF_SIZE_VARIABLE_LEN != (rgType & 0x0300) && PERF_SIZE_ZERO != (rgType & 0x0300));	// not supported yet
	}
	return 0L;
}

//  Utility macro.  This is used to reserve a DWORD multiple of
//  bytes for Unicode strings embedded in the definitional data,
//  viz., object instance names.
//
#define DWORD_MULTIPLE(x) (((x+sizeof(DWORD)-1)/sizeof(DWORD))*sizeof(DWORD))

#endif // !defined(_PERFMONUTIL_H__467452A4_9CBA_11D2_9F09_006008447800__INCLUDED_)
