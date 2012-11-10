// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.11.1999 16:41:24 
//
// @doc
// @module ImToolsApi.h | Decorating ImTools API functions

#if !defined(_IMTOOLS_H__88E6B9E9_D2ED_424B_A6AB_FC7B698CB28A__INCLUDED_)
#define _IMTOOLS_H__88E6B9E9_D2ED_424B_A6AB_FC7B698CB28A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if !defined(_LIB)
#ifdef IMTOOLS_EXPORTS
#define IMTOOLS_API __declspec(dllexport)
#else
#define IMTOOLS_API __declspec(dllimport)
#endif
#else
#define IMTOOLS_API 
#endif // !defined(_LIB)

///////////////////////////////////////////////////////////////////////////////
// additional config stuff

// use memory mapped files for VFB's (virtual frame buffers)
#define _USE_MMFS_FOR_VFB

// use optional memory mapped files for VFB's (virtual frame buffers)
#define _USE_MMFS_FOR_VFB_OPTIONAL

#if !defined(_USE_MMFS_FOR_VFB)
#undef _USE_MMFS_FOR_VFB_OPTIONAL		// (use only with _USE_MMFS_FOR_VFB)
#endif // !defined(_USE_MMFS_FOR_VFB)

// include support for GeoTIFF's
#define _USE_LIBGEOTIFF

///////////////////////////////////////////////////////////////////////////////
// additional global headers
#include <AggressiveOptimize.h>

#endif // !defined(_IMTOOLS_H__88E6B9E9_D2ED_424B_A6AB_FC7B698CB28A__INCLUDED_)
