// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 20.09.99 18:29:36 
//
// @doc
// @module MapCaches.h | Declaration of the <c CMapCaches> class

#if !defined(_MAPCACHES_H__862F8FEF_4789_4135_8B82_DCEB4D8E9D05__INCLUDED_)
#define _MAPCACHES_H__862F8FEF_4789_4135_8B82_DCEB4D8E9D05__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

class CMapCaches
{
public:
	CMapCaches() {}
	~CMapCaches() {}

	static HRESULT GetObjectsMap (ITRiASObjectHandleMap **ppIMap)
	{
		_ASSERTE(m_ObjsMap.IsValid());
		_ASSERTE(NULL != ppIMap);
		return (*ppIMap = m_ObjsMap) -> AddRef(), S_OK;
	}

	static HRESULT GetObjectMap (ITRiASObjectHandleMap **ppIMap)
	{
		_ASSERTE(m_ObjMap.IsValid());
		_ASSERTE(NULL != ppIMap);
		return (*ppIMap = m_ObjMap) -> AddRef(), S_OK;
	}

	static HRESULT GetFeatureMap (ITRiASObjectHandleMap **ppIMap)
	{
		_ASSERTE(m_FeatMap.IsValid());
		_ASSERTE(NULL != ppIMap);
		return  (*ppIMap = m_FeatMap) -> AddRef(), S_OK;
	}

	static HRESULT InitMapCaches()
	{
		COM_TRY {
			THROW_FAILED_HRESULT(m_ObjsMap.CreateInstance(CLSID_TRiASObjectsHandleMap));
			THROW_FAILED_HRESULT(m_ObjMap.CreateInstance(CLSID_TRiASObjectHandleMap));
			THROW_FAILED_HRESULT(m_FeatMap.CreateInstance(CLSID_TRiASFeatureHandleMap));
		} COM_CATCH;
		return S_OK;
	}
	static void FreeMapCaches()
	{
		m_ObjsMap.Assign(NULL);
		m_ObjMap.Assign(NULL);
		m_FeatMap.Assign(NULL);
	}

private:
	static __Interface<ITRiASObjectHandleMap> m_ObjsMap;
	static __Interface<ITRiASObjectHandleMap> m_ObjMap;
	static __Interface<ITRiASObjectHandleMap> m_FeatMap;
};

inline HRESULT InitMapCaches()
{
	return CMapCaches::InitMapCaches();
}

inline void FreeMapCaches()
{
	CMapCaches::FreeMapCaches();
}

inline HRESULT GetObjectsMap (ITRiASObjectHandleMap **ppIMap)
{
	return CMapCaches::GetObjectsMap(ppIMap);
}

inline HRESULT GetObjectMap (ITRiASObjectHandleMap **ppIMap)
{
	return CMapCaches::GetObjectMap(ppIMap);
}

inline HRESULT GetFeatureMap (ITRiASObjectHandleMap **ppIMap)
{
	return CMapCaches::GetFeatureMap(ppIMap);
}

#endif // !defined(_MAPCACHES_H__862F8FEF_4789_4135_8B82_DCEB4D8E9D05__INCLUDED_)
