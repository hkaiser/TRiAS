// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 15.07.99 19:48:51 
//
// @doc
// @module RunTimeObjectMapMgr.h | Declaration of the <c CRunTimeObjectMapMgr> class

#if !defined(_RUNTIMEOBJECTMAPMGR_H__8729DA00_3ADD_11D3_94FA_0080C786297B__INCLUDED_)
#define _RUNTIMEOBJECTMAPMGR_H__8729DA00_3ADD_11D3_94FA_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if !defined(_USE_RUNTIME_OBJECTMAP)

#define RT_OBJECT_ENTRY(clsid, cls)
#define RT_OBJECT_ENTRY2(clsid, cls, prefix)
#define RT_OBJECT_ENTRY_NON_CREATEABLE(cls)

#define RT_OBJECT_ENTRYEX(name)

#else // !defined(_USE_RUNTIME_OBJECTMAP)

#include <ospace/std/vector>

///////////////////////////////////////////////////////////////////////////////
// function prototypes
void RegisterRunTimeObjectMapEntry(_ATL_OBJMAP_ENTRY* pEntry);
_ATL_OBJMAP_ENTRY* GetRunTimeObjectMap();

///////////////////////////////////////////////////////////////////////////////
// Calls the global RegisterObjectMapEntry function to register an
// object map entry in the dnamic list of entries
class CRunTimeObjectMapUpdator
{
public:
	CRunTimeObjectMapUpdator(_ATL_OBJMAP_ENTRY* pEntry)
	{
		RegisterRunTimeObjectMapEntry(pEntry);
	}
};

///////////////////////////////////////////////////////////////////////////////
// Adds an object map entry to the run-time list of entries
#define RT_OBJECT_ENTRY(clsid, cls)\
	static _ATL_OBJMAP_ENTRY cls##_run_time_object_map_entry[1] = { OBJECT_ENTRY(clsid, cls) }; \
	static CRunTimeObjectMapUpdator cls##_run_time_object_map_entry_updator(cls##_run_time_object_map_entry);
#define RT_OBJECT_ENTRY2(clsid, cls, prefix)\
	static _ATL_OBJMAP_ENTRY prefix##cls##_run_time_object_map_entry[1] = { OBJECT_ENTRY(clsid, cls) }; \
	static CRunTimeObjectMapUpdator prefix##cls##_run_time_object_map_entry_updator(prefix##cls##_run_time_object_map_entry);
#define RT_OBJECT_ENTRYEX(name)\
	RT_OBJECT_ENTRY(CLSID_##name, C##name)

///////////////////////////////////////////////////////////////////////////////
// Adds an object map entry to the run-time list of entries; note that
// such objects cannot be created externally via CoCreateInstance!
#define RT_OBJECT_ENTRY_NON_CREATEABLE(cls)\
	static _ATL_OBJMAP_ENTRY cls##_run_time_object_map_entry[1] = { OBJECT_ENTRY_NON_CREATEABLE(cls) }; \
	static CRunTimeObjectMapUpdator cls##_run_time_object_map_entry_updator(cls##_run_time_object_map_entry);

#endif // !defined(_USE_RUNTIME_OBJECTMAP)

#endif // !defined(_RUNTIMEOBJECTMAPMGR_H__8729DA00_3ADD_11D3_94FA_0080C786297B__INCLUDED_)
