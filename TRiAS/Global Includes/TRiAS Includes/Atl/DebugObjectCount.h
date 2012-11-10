// @doc 
// @module DebugObjectCount.h | Zählen der Objekte eines Typs

#if !defined(_DEBUGOBJECTCOUNT_H__72794DC7_BF64_11D2_95B5_006008447800__INCLUDED_)
#define _DEBUGOBJECTCOUNT_H__72794DC7_BF64_11D2_95B5_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(_ATLX_DEBUG_OBJECTCOUNT)

template<class T>
class CTrackCount
{
public:
	CTrackCount()
		: m_ulCount(0)
	{
	}
	~CTrackCount()
	{
		if (0 != m_ulCount)
			ATLTRACE("\t%s: pending object count: %ld\r\n", m_strName.c_str(), m_ulCount);
	}
	int Increment() 
	{ 
		return ++m_ulCount; 
	}
	int Decrement() 
	{ 
		return --m_ulCount; 
	}
	void SetName (LPCSTR pcName) 
	{ 
		m_strName = pcName; 
	}

private:
	ULONG m_ulCount;
	os_string m_strName;
};

template<class T>
class CObjectCount
{
public:
	CObjectCount() 
	{
		m_ulObjCount.Increment();
	}
	~CObjectCount() 
	{
		m_ulObjCount.Decrement();
	}

	static CTrackCount<T> m_ulObjCount;
};

template<class T> 
CTrackCount<T> CObjectCount<T>::m_ulObjCount = CTrackCount<T>();	// hier werden die Objekte gezählt

#define _ATLX_DEBUG_OBJECTCOUNT_IMPL(x)	\
	CObjectCount<x> __ObjCnt; \
	static void WINAPI ObjectMain (bool bStarting) \
		{ if (bStarting) CObjectCount<x>::m_ulObjCount.SetName(#x); }

#else

#define _ATLX_DEBUG_OBJECTCOUNT_IMPL(x)	/**/

#endif // defined(_ATLX_DEBUG_OBJECTCOUNT) 

#endif // !defined(_DEBUGOBJECTCOUNT_H__72794DC7_BF64_11D2_95B5_006008447800__INCLUDED_)
