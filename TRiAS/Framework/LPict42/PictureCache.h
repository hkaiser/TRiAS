// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 10.04.2002 15:12:28 
//
// @doc
// @module PictureCache.h | Declaration of the <c CPictureCache> class

#if !defined(_PICTURECACHE_H__5917788A_B932_432F_93E8_B55316217DA4__INCLUDED_)
#define _PICTURECACHE_H__5917788A_B932_432F_93E8_B55316217DA4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/std/map>
#include <ospace/std/memory>

///////////////////////////////////////////////////////////////////////////////
// repräsentiert ein gecachtes Objekt
template <typename CacheItemT>
class CCacheItem
{
public:
	CCacheItem (CacheItemT *pToCache) : 
		m_pToCache(pToCache), m_fRecentlyUsed(true) 
	{
	}
	~CCacheItem() 
	{
	}

	CacheItemT *GetCachedItem() { return m_pToCache; }
	bool WasRecentlyUsed() { return m_fRecentlyUsed; }
	void SetRecentlyUsed(bool fUsed) { m_fRecentlyUsed = fUsed; }
	void ReleaseItem() { if (NULL != m_pToCache) delete m_pToCache; m_pToCache = NULL; }

private:
	CacheItemT *m_pToCache;
	bool m_fRecentlyUsed;
};

///////////////////////////////////////////////////////////////////////////////
// Map hält die gecachten Objekte
#pragma warning (disable: 4355)		// this used in base member initializer

template <
	typename KeyT, 
	typename CacheT, 
	typename CntT = map<KeyT, CCacheItem<CacheT>, less<KeyT> >
>
class CCachedItems :
	public CntT
{
public:
	typedef CntT base_t;

	CCachedItems(int iCacheSize) : 
		m_itlast (this->end()), 
		m_iCacheSize(iCacheSize) 
	{
#if defined(_DEBUG)
		m_iMaxCacheSize = 0;
		m_iCacheAccesses = 0;
		m_iCacheHits = 0;
#endif // defined(_DEBUG)
	}
	~CCachedItems() 
	{
	}

// properties
	base_t::iterator GetLastIt() 
	{ 
		return (m_itlast == this->end()) ? this->begin() : m_itlast; 
	}
	bool HasReachedLimit() 
	{ 
		return (this->size() >= m_iCacheSize) ? true : false; 
	}
	
// methods
	base_t::iterator AdvanceIt()
	{
		if (m_itlast == this->end() || ++m_itlast == this->end())
			m_itlast = this->begin();
		return m_itlast;
	}
	
	CacheT *HasItem (KeyT const &rKey) 
	{
#if defined(_DEBUG)
		++m_iCacheAccesses;
#endif // defined(_DEBUG)

	base_t::iterator it = this->find(rKey);

		if (it == this->end())
			return NULL;

#if defined(_DEBUG)
		++m_iCacheHits;
#endif // defined(_DEBUG)

		(*it).second.SetRecentlyUsed(true);
		return (*it).second.GetCachedItem();
	}
	void ReleaseItem(base_t::iterator it) 
	{ 
	// Sicherstellen, daß Iterator nicht ins Leere zeigt
		if (it == m_itlast) {
			_ASSERTE(m_itlast != this->end());
			if (++m_itlast == this->end())
				m_itlast = this->begin();
		}

	// Eintrag löschen
		(*it).second.ReleaseItem();
		this->erase(it); 

	// wenns der letzte Eintrag war
		if (0 == this->size())
			m_itlast = this->end();
	}
	bool AddItem(KeyT const &rKey, CacheT *pItem) 
	{ 
	pair<base_t::iterator, bool> p = 
		this->insert(base_t::value_type(rKey, CCacheItem<CacheT>(pItem))); 

#if defined(_DEBUG)
		m_iMaxCacheSize = max(m_iMaxCacheSize, this->size());
#endif // defined(_DEBUG)
		return p.second;
	}
	
	CacheT *EnsureItem(KeyT const &rKey, bool fCreateNew = true)
	{
	CacheT *pItem = HasItem(rKey);		// organisiert CacheHit, wenn vorhanden

		if (NULL == pItem && fCreateNew) {
		// Item ist nicht bereits geladen
			if (HasReachedLimit()) {
			// versuchen, was rauszuwerfen
				for (base_t::iterator it = GetLastIt(); /**/; it = AdvanceIt()) {
					if (!(*it).second.WasRecentlyUsed()) {
						ReleaseItem(it);
						break;		// for
					} else
						(*it).second.SetRecentlyUsed (false);
				}
			} 

		// jetzt neu einfügen
		auto_ptr<CacheT> NewItem (new CacheT());

			if (AddItem(rKey, NewItem.get())) 
				return NewItem.release();
			return NULL;
		}
		return pItem;
	}

	void ReleaseItems()
	{
		for (base_t::iterator it = this->begin(); it != this->end(); ++it) 
			(*it).second.ReleaseItem();
		this->erase();
		m_itlast = this->end();
	}

private:
	base_t::iterator m_itlast;
	base_t::size_type m_iCacheSize;
	
#if defined(_DEBUG)
	base_t::size_type m_iMaxCacheSize;
	base_t::size_type m_iCacheAccesses;
	base_t::size_type m_iCacheHits;
#endif // defined(_DEBUG)
};

#endif // !defined(_PICTURECACHE_H__5917788A_B932_432F_93E8_B55316217DA4__INCLUDED_)
