// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 09.09.99 12:49:51 
//
// @doc
// @module PerfMonInstanceMap.h | Declaration of the <c CPerfMonInstanceMap> class

#if !defined(_PERFMONINSTANCEMAP_H__A2EC99BB_80F8_4672_B936_BE0D11E74D05__INCLUDED_)
#define _PERFMONINSTANCEMAP_H__A2EC99BB_80F8_4672_B936_BE0D11E74D05__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(_USE_PERFMON_COUNTERS)

#include <ospace/std/vector>
#import "tlb/PerfMon.tlb" raw_interfaces_only raw_dispinterfaces named_guids \
	exclude("INT_PTR") 

///////////////////////////////////////////////////////////////////////////////
// globaler PerfContext
namespace PerfMon {

DefineSmartInterface(PerfContext);

extern WPerfContext g_PerfCtx;

///////////////////////////////////////////////////////////////////////////////
// Daten der für ein PerfObject zu definierenden PerfCounter
typedef struct tagPERFCOUNTERDATA {
	LPCOLESTR pcoleName;			// Name der CounterMenge
	UINT uiDesc;					// Beschreibung
	UINT uiHelp;					// ganz lange Beschreibung
	PerfMon::DETAILLEVEL rgDetailLevel;		// Detaillevel
	PerfMon::COUNTERTYPE rgCounterType;		// Typ
	LONG lScale;					// voreingestellter Skalierungsfaktor
} PERFCOUNTERDATA;

#define BEGIN_PERFCOUNTERDATA_MAP(obj) static const PERFCOUNTERDATA g_CounterData##obj[] = {
#define END_PERFCOUNTERDATA_MAP() { NULL, 0L, 0L, 0L, 0L, 0L, }, };
#define PERCOUNTERDATA_ENTRY(name,desc,text,detail,typ,scale) { name, desc, text, detail, typ, scale, },

///////////////////////////////////////////////////////////////////////////////
// Daten der für ein PerfObject zu definierenden Instanzen
typedef struct tagPERFINSTANCEDATA {
	LPCOLESTR pcoleObjectName;		// Name des zugehörigen Objektes
	LPCOLESTR pcoleName;			// Name der PerfInstance
} PERFINSTANCEDATA;

#define BEGIN_PERFINSTANCE_MAP() static const PERFINSTANCEDATA g_InstanceData[] = {
#define END_PERFINSTANCE_MAP() { NULL, NULL, }, };
#define PERFINSTANCEDATA_ENTRY(name,inst) { L#name, L#inst, },

///////////////////////////////////////////////////////////////////////////////
// Daten der zu definierenden PerfObjects
typedef struct tagPERFOBJECTDATA {
	LPCOLESTR pcoleCounterName;		// Name der zugehörigen CounterMenge
	LPCOLESTR pcoleName;			// Name des PerfObjects
	UINT uiDesc;					// Beschreibung
	UINT uiHelp;					// ganz lange Beschreibung
	const PERFCOUNTERDATA *pPerfData;
} PERFOBJECTDATA;

#define BEGIN_PERFOBJECT_MAP() \
	const PerfMon::PERFOBJECTDATA *PerfMon::GetPerfObjectMap() { \
	static const PerfMon::PERFOBJECTDATA _entries[] = { 

#define PERFOBJECTDATA_ENTRY(name,counters,desc,text) { L#counters, name, desc, text, g_CounterData##counters, },

#define END_PERFOBJECT_MAP() \
	{ NULL, NULL, 0L, 0L, NULL, }, }; return _entries;}

///////////////////////////////////////////////////////////////////////////////
// function prototypes
HRESULT InstallPerfCounters(HINSTANCE hInstance);
HRESULT GetPerfCounter (LPCOLESTR pcoleObjName, LPCOLESTR pcoleInstName, LPCOLESTR pcoleCounterName, IPerfCounter **ppICount);

void RegisterPerfMonInstanceMapEntry(PERFINSTANCEDATA *pEntry);
const PERFINSTANCEDATA *GetPerfMonInstanceMap();
const PERFOBJECTDATA *GetPerfObjectMap();

///////////////////////////////////////////////////////////////////////////////
// Calls the global RegisterPerfMonInstanceMapEntry function to register an
// PerfMonInstance map entry in the dnamic list of entries
class CPerfMonInstanceMapUpdator
{
public:
	CPerfMonInstanceMapUpdator(PERFINSTANCEDATA* pEntry)
	{
		RegisterPerfMonInstanceMapEntry(pEntry);
	}
};

} // namespace PerfMon

///////////////////////////////////////////////////////////////////////////////
// Adds an instance map entry to the run-time list of entries
#define RT_PERFINSTANCEDATA_ENTRY(instname, objname) \
	static PerfMon::PERFINSTANCEDATA instname##objname##_run_time_instance_map_entry[1] = { { objname, L#instname, }, }; \
	static PerfMon::CPerfMonInstanceMapUpdator instname##objname##_run_time_instance_map_entry_updator(instname##objname##_run_time_instance_map_entry);

#else

///////////////////////////////////////////////////////////////////////////////
// alle Makros ausblenden
#define RT_PERFINSTANCEDATA_ENTRY(instname, objname) 

#endif // defined(_USE_PERFMON_COUNTERS)

#endif // !defined(_PERFMONINSTANCEMAP_H__A2EC99BB_80F8_4672_B936_BE0D11E74D05__INCLUDED_)
