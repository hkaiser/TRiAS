// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.09.99 21:35:32 
//
// @doc
// @module PerfMonObjectCount.h | Declaration of the <c CPerfMonObjectCount> class

#if !defined(_PERFMONOBJECTCOUNT_H__FABD31C1_CCCD_45EB_BC11_734518F35583__INCLUDED_)
#define _PERFMONOBJECTCOUNT_H__FABD31C1_CCCD_45EB_BC11_734518F35583__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(_USE_PERFMON_COUNTERS)

#include <Com/PerfMonInstanceMap.h>

///////////////////////////////////////////////////////////////////////////////
// Hier behandelte Counter
extern __declspec(selectany) const wchar_t g_cbCounts[] = L"OBJ_COUNTS";	// ein PerfObject
extern __declspec(selectany) const wchar_t g_cbCount[] = L"OBJ_COUNT";		// Zähler für PerfObject "OBJ_COUNTS"
extern __declspec(selectany) const wchar_t g_cbAllocs[] = L"OBJ_ALLOCS";
extern __declspec(selectany) const wchar_t g_cbFrees[] = L"OBJ_FREES";

// 
template<class T>
class CPerfMonTrackCount
{
public:
	CPerfMonTrackCount()
#if defined(_ATLX_DEBUG_OBJECTCOUNT)
		: m_ulCount(0)
#endif // defined(_ATLX_DEBUG_OBJECTCOUNT)
	{
	}
	~CPerfMonTrackCount()
	{
#if defined(_ATLX_DEBUG_OBJECTCOUNT)
		if (0 != m_ulCount)
			ATLTRACE("\t%s: pending object count: %ld\r\n", m_strName.c_str(), m_ulCount);
#endif // defined(_ATLX_DEBUG_OBJECTCOUNT)
	}
	void Increment() 
	{ 
		if (m_ObjsExisting.IsValid()) m_ObjsExisting -> Step();
		if (m_ObjsAllocs.IsValid()) m_ObjsAllocs -> Step();
#if defined(_ATLX_DEBUG_OBJECTCOUNT)
		++m_ulCount; 
#endif // defined(_ATLX_DEBUG_OBJECTCOUNT)
	}
	void Decrement() 
	{ 
		if (m_ObjsExisting.IsValid()) m_ObjsExisting -> Increment(-1);
		if (m_ObjsFrees.IsValid()) m_ObjsFrees -> Step();
#if defined(_ATLX_DEBUG_OBJECTCOUNT)
		--m_ulCount; 
#endif // defined(_ATLX_DEBUG_OBJECTCOUNT)
	}
	void SetName (LPCSTR pcName) 
	{ 
#if defined(_ATLX_DEBUG_OBJECTCOUNT)
		m_strName = pcName; 
#endif // defined(_ATLX_DEBUG_OBJECTCOUNT)

	CComBSTR bstrName (pcName);

		PerfMon::GetPerfCounter (g_cbCounts, bstrName, g_cbCount, m_ObjsExisting.ppi());
		PerfMon::GetPerfCounter (g_cbCounts, bstrName, g_cbAllocs, m_ObjsAllocs.ppi());
		PerfMon::GetPerfCounter (g_cbCounts, bstrName, g_cbFrees, m_ObjsFrees.ppi());
	}
	void Reset()
	{
		m_ObjsExisting.Assign(NULL);
		m_ObjsAllocs.Assign(NULL);
		m_ObjsFrees.Assign(NULL);
	}

private:
#if defined(_ATLX_DEBUG_OBJECTCOUNT)
	ULONG m_ulCount;
	os_string m_strName;
#endif // defined(_ATLX_DEBUG_OBJECTCOUNT)

	__Interface<PerfMon::IPerfCounter> m_ObjsExisting;
	__Interface<PerfMon::IPerfCounter> m_ObjsAllocs;
	__Interface<PerfMon::IPerfCounter> m_ObjsFrees;
};

template<class T>
class CPerfMonObjectCount
{
public:
	CPerfMonObjectCount() 
	{
		m_ulObjCount.Increment();
	}
	~CPerfMonObjectCount() 
	{
		m_ulObjCount.Decrement();
	}

	static CPerfMonTrackCount<T> m_ulObjCount;
};

template<class T> 
CPerfMonTrackCount<T> CPerfMonObjectCount<T>::m_ulObjCount = CPerfMonTrackCount<T>();	// hier werden die Objekte gezählt

#define _COMX_PERF_OBJECTCOUNT_IMPL(x)	\
	CPerfMonObjectCount<x> __PerfMonObjCnt; \
	static void WINAPI ObjectMain (bool bStarting) \
		{ if (bStarting) CPerfMonObjectCount<x>::m_ulObjCount.SetName(#x); \
		  else CPerfMonObjectCount<x>::m_ulObjCount.Reset(); }

#else

#define _COMX_PERF_OBJECTCOUNT_IMPL(x) /**/

#endif // defined(_USE_PERFMON_COUNTERS)

#endif // !defined(_PERFMONOBJECTCOUNT_H__FABD31C1_CCCD_45EB_BC11_734518F35583__INCLUDED_)
