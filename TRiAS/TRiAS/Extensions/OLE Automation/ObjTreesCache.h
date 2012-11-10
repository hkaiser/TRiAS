// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 23.11.2000 15:07:11 
//
// @doc
// @module ObjTreesCache.h | Declaration of the <c CObjTreesCache> class

#if !defined(_OBJTREESCACHE_H__E94AEA02_0FF8_4BB6_B5CC_1C2BECF9B836__INCLUDED_)
#define _OBJTREESCACHE_H__E94AEA02_0FF8_4BB6_B5CC_1C2BECF9B836__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// repräsentiert ein gecachtes Objekt
class CObjCacheItem
{
public:
	CObjCacheItem (INT_PTR hONr) : m_hONr(hONr), m_fRecentlyUsed(true) {}
	~CObjCacheItem() {}

	INT_PTR GetONr() { return m_hONr; }
	bool WasRecentlyUsed() { return m_fRecentlyUsed; }
	void SetRecentlyUsed(bool fUsed) { m_fRecentlyUsed = fUsed; }
	
private:
	INT_PTR m_hONr;
	bool m_fRecentlyUsed;
};

///////////////////////////////////////////////////////////////////////////////
// Map hält die Objektnummern der gecachten Objekte
class CObjCache :
	public map<INT_PTR, CObjCacheItem, less<INT_PTR> >
{
public:
	CObjCache(int iCacheSize) : 
		m_itlast (end()), m_iCacheSize(iCacheSize) 
	{
#if defined(_DEBUG)
		m_iMaxCacheSize = 0;
		m_iCacheAccesses = 0;
		m_iCacheHits = 0;
#endif // defined(_DEBUG)
	}
	~CObjCache() 
	{
		D_OUTF3(2, 
			"CObjCache::~CObjCache: max cache size: %ld, ", m_iMaxCacheSize,
			"cache accesses: %ld, ", m_iCacheAccesses,
			"cache hits: %ld", m_iCacheHits);
	}

// properties
	iterator GetLastIt() { return (m_itlast == end()) ? begin() : m_itlast; }
	bool HasReachedLimit() { return (size() >= m_iCacheSize) ? true : false; }
	
// methods
	iterator AdvanceIt()
	{
		if (m_itlast == end() || ++m_itlast == end())
			m_itlast = begin();
		return m_itlast;
	}
	
	bool HasObject (INT_PTR hONr) 
	{
#if defined(_DEBUG)
		++m_iCacheAccesses;
#endif // defined(_DEBUG)

	iterator it = find(hONr);

		if (it == end())
			return false;

#if defined(_DEBUG)
		++m_iCacheHits;
#endif // defined(_DEBUG)
		(*it).second.SetRecentlyUsed(true);
		return true;
	}
	void ReleaseItem(iterator it) 
	{ 
	// Sicherstellen, daß Iterator nicht ins Leere zeigt
		if (it == m_itlast) {
			_ASSERTE(m_itlast != end());
			if (++m_itlast == end())
				m_itlast = begin();
		}

	// Eintrag löschen
		erase(it); 

	// wenns der letzte Eintrag war
		if (0 == size())
			m_itlast = end();
	}
	void AddItem(INT_PTR hObj) 
	{ 
		insert(hObj, hObj); 
		m_itlast = end();		// auf den letzten stellen
#if defined(_DEBUG)
		m_iMaxCacheSize = max(m_iMaxCacheSize, size());
#endif // defined(_DEBUG)
	}

	bool RemoveItem (INT_PTR hONr) 
	{
	iterator it = find(hONr);

		if (it == end())
			return false;

		ReleaseItem(it);
		return true;
	}
		
private:
	iterator m_itlast;
	size_type m_iCacheSize;
	
#if defined(_DEBUG)
	size_type m_iMaxCacheSize;
	size_type m_iCacheAccesses;
	size_type m_iCacheHits;
#endif // defined(_DEBUG)
};

///////////////////////////////////////////////////////////////////////////////
// der eigentliche Cache
class CObjTreesCache
{
public:
	CObjTreesCache (class CObjTrees &rTrees, int iCacheSize) :
		m_rTrees(rTrees), m_Cache(iCacheSize)
	{
	}
	~CObjTreesCache() 
	{
	}
	bool CacheHit(INT_PTR hObj);
	bool RemoveItem (INT_PTR hObj)
	{
		return m_Cache.RemoveItem(hObj);
	}

private:
	CObjTrees &m_rTrees;
	CObjCache m_Cache;
};

#endif // !defined(_OBJTREESCACHE_H__E94AEA02_0FF8_4BB6_B5CC_1C2BECF9B836__INCLUDED_)
