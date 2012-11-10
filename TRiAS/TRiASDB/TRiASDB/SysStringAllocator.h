// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/08/1998 02:44:29 PM
//
// @doc
// @module SysStringAllocator.h | StlAllocator für BSTR's

#if !defined(_SYSSTRINGALLOCATOR_H__5962CB65_8E9D_11D2_9EFC_006008447800__INCLUDED_)
#define _SYSSTRINGALLOCATOR_H__5962CB65_8E9D_11D2_9EFC_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/stl/allocimp.h>

// Allocator, der Speicher über ::SysAllocString/::SysFreeString verwaltet
class os_sysstring_allocator : 
	public os_allocator_impl
{
	void *allocate (size_t size, size_t n = 1, const void* hint = 0)
	{
		_ASSERTE(size == sizeof(unsigned short));
		return ::SysAllocStringLen (NULL, n);
	}
	void deallocate (void *p)
	{
		::SysFreeString((BSTR)p);
	}
	void *raw_allocate (size_t size, size_t n = 1, const void* hint = 0)
	{
		_ASSERTE(size == sizeof(unsigned short));
		return ::SysAllocStringLen (NULL, n);
	}
	void raw_deallocate (void *p)
	{
		::SysFreeString((BSTR)p);
	}
};

#endif // !defined(_SYSSTRINGALLOCATOR_H__5962CB65_8E9D_11D2_9EFC_006008447800__INCLUDED_)
