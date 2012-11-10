// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.10.1999 13:18:40 
//
// @doc
// @module ContainerWrapper.h | Declaration of the <c CContainerWrapper> class

#if !defined(_CONTAINERWRAPPER_H__3F3DE28F_D284_4809_BBDD_04CB6DAEAFED__INCLUDED_)
#define _CONTAINERWRAPPER_H__3F3DE28F_D284_4809_BBDD_04CB6DAEAFED__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/std/map>
#include <ospace/std/vector>
#include <ospace/std/algorithm>

#include <Atl/_Resource_guard.h>

namespace container_wrappers {

///////////////////////////////////////////////////////////////////////////////
// lediglich aus Kompatibilitätsgründen  definieren
typedef enum tagCONTFLAGS {
	CFNoSpecial 	= 0x00,
	CFAutoDelete 	= 0x01,
	CFUniqueKey 	= 0x02,
	CFSyncThreads	= 0x04,
	CFAll			= 0x07,
	CFDefault		= tagCONTFLAGS(CFAutoDelete|CFSyncThreads),
} CONTFLAG;

///////////////////////////////////////////////////////////////////////////////
// neue Implementation für CArrayContainer
template<class T, class CS = CComObjectThreadModel::AutoCriticalSection>
class CArrayOnStl :
	public resource_guard<vector<T>, CS>
{
public:
	typedef vector<T>::referent_type value_type;
	typedef vector<T>::referent_type referent_type;
	typedef vector<T>::iterator iterator;
	typedef vector<T>::const_iterator const_iterator;
	typedef vector<T> _resources_vector_t;
	typedef resource_guard<_resources_vector_t, CS>::guard guard_t;

	typedef vector<T> base_t;
	typedef CS cs_t;

protected:
	virtual void UserDelete (void *pdata) = 0;

public:
	CArrayOnStl(int iInitSize, CONTFLAG rgFlag) 
	{
	}
	~CArrayOnStl() {}

	ULONG Count() { return size(); }
	bool Delete (iterator it, bool fDelete = true)
	{
	guard_t guard (Guard());

		if (it != (*guard).end()) {
			if (fDelete) 
				UserDelete (*it);

		size_t iCnt = (*guard).size();

			(*guard).erase (it);
			return (*guard).size() == iCnt-1;
		}
		return false;
	}
	void EveryDelete()
	{
	guard_t guard (Guard());

		for (iterator it = (*guard).begin(); it != (*guard).end(); ++it)	// alles freigeben
			UserDelete (*it);
		(*guard).clear();				// und aus map löschen
	}
	bool Insert (referent_type data)
	{
	guard_t guard (Guard());
	
		(*guard).push_back (data);
		return true;
	} 

	bool Goto (ULONG lIndex, iterator *pit)
	{
	guard_t guard (Guard());

		*pit = (*guard).begin();
		advance (*pit, lIndex);
		return *pit != (*guard).end();
	}

	iterator begin() { guard_t guard (Guard()); return (*guard).begin(); }
	iterator end() { guard_t guard (Guard()); return (*guard).end(); }
};

///////////////////////////////////////////////////////////////////////////////
// die folgenden KJlassen helfen die unterschiedlichen Schlüssel-Anwendungen zu
// verwalten ('LPCSTR' aber 'ULONG' wird zu 'LPCSTR' aber 'ULONG *')
template<class T>
class key_converter :
	public unary_function<void *, T>
{
public:
	T operator() (void *pKey) { return *reinterpret_cast<T *>(pKey); }
};

template<>
class key_converter<LPCSTR> :
	public unary_function<void *, LPCSTR>
{
public:
	LPCSTR operator() (void *pKey) { return reinterpret_cast<LPCSTR>(pKey); }
};

// neue Implementation für CTree/COptTree
typedef void * (* CTTREEGETKEYFCN) (void *);
typedef int (* CTTREECMPKEYFCN)(void *, void *);

template<class BaseMap, class CS = CComObjectThreadModel::AutoCriticalSection>
class CTreeOnStlBase :
	public resource_guard<BaseMap, CS>
{
public:
	typedef BaseMap::key_type key_type;
	typedef BaseMap::referent_type referent_type;
	typedef BaseMap::value_type value_type;
	typedef BaseMap::iterator iterator;
	typedef BaseMap::const_iterator const_iterator;
	typedef BaseMap _resources_map_t;
	typedef resource_guard<_resources_map_t, CS>::guard guard_t;
	typedef key_type (*get_key_function)(const referent_type);
	typedef int (*cmp_key_function)(const key_type *, const key_type *);

	typedef BaseMap base_t;
	typedef CS cs_t;

protected:
	virtual void UserDelete (void *pdata) = 0;

public:
	CTreeOnStlBase(CTTREEGETKEYFCN gkf) :
		m_pGetKeyFcn(get_key_function(gkf))
	{
	}
	~CTreeOnStlBase() {}

	ULONG Count() 
	{ 
	guard_t guard (Guard());
		
		return (*guard).size(); 
	}
	bool Delete (iterator it, bool fDelete = true)
	{
	guard_t guard (Guard());

		if (it != (*guard).end()) {
			if (fDelete) 
				UserDelete ((*it).second);

		size_t iCnt = (*guard).size();

			(*guard).erase (it);
			return (*guard).size() == iCnt-1;
		}
		return false;
	}
	void EveryDelete()
	{
	guard_t guard (Guard());

		for (iterator it = (*guard).begin(); it != (*guard).end(); ++it)	// alles freigeben
			UserDelete ((*it).second);
		(*guard).clear();				// und aus map löschen
	}
	bool Find (key_type key, iterator *pit)
	{
	guard_t guard (Guard());
	iterator it = (*guard).find (key);

		*pit = it;
		return it != (*guard).end();
	}
	bool FindFirst (key_type key, iterator *pit) { return Find (key, pit); }

	virtual bool Insert (key_type key, referent_type data, iterator *pit = NULL) = 0;
	virtual bool Insert (referent_type data, iterator *pit = NULL) = 0;
#if defined(_USE_UNSAFE_REINSERT)
	bool ReInsert (key_type key, size_t iSize, iterator *pit) 
	{
	guard_t guard (Guard());
	referent_type data = (*pit != end()) ? (**pit).second : referent_type(0);

		if (!Delete (*pit, false)) 
			return false;
//		memcpy ((*(**pit).second.GetKeyFcn())(), &key, iSize);	// neuen Key reinkopieren !?
		return Insert (key, data, pit); 
	}
#endif // defined(_USE_UNSAFE_REINSERT)

	get_key_function GetKeyFcn() { return m_pGetKeyFcn; }

	iterator begin() { guard_t guard (Guard()); return (*guard).begin(); }
	iterator end() { guard_t guard (Guard()); return (*guard).end(); }

private:
	get_key_function m_pGetKeyFcn;
};

template<class K, class D, class cmp = less<K>, class CS = CComObjectThreadModel::AutoCriticalSection>
class CTreeOnStl :
	public CTreeOnStlBase<multimap<K, D, cmp>, CS>
{
public:
	CTreeOnStl(CTTREEGETKEYFCN gkf, CTTREECMPKEYFCN, CONTFLAG) :
		CTreeOnStlBase<multimap<K, D, cmp>, CS>(gkf)
	{
	}
	explicit CTreeOnStl(CTTREEGETKEYFCN gkf) :
		CTreeOnStlBase<multimap<K, D, cmp>, CS>(gkf)
	{
	}
	~CTreeOnStl() {}

	bool Insert (key_type key, referent_type data, iterator *pit = NULL)
	{
	guard_t guard (Guard());
	iterator it = (*guard).insert (value_type (key, data));

		if (NULL != pit)
			*pit = it;
		return it != (*guard).end();
	} 
	bool Insert (referent_type data, iterator *pit = NULL)
	{
	const key_type key = key_converter<K>()((void *)(*GetKeyFcn())(data));
	guard_t guard (Guard());
	iterator it = (*guard).insert (value_type (key, data));

		if (NULL != pit)
			*pit = it;
		return it != (*guard).end();
	} 

	bool FindNext (key_type key, iterator *pit) 
	{
	guard_t guard (Guard()); 

		_ASSERTE((*pit) != (*guard).end());
		++(*pit);
		if ((**pit).first != (key))
			*pit = (*guard).end();
		return *pit != (*guard).end();
	}
};

template<class K, class D, class cmp = less<K>, class CS = CComObjectThreadModel::AutoCriticalSection>
class CUniqueTreeOnStl :
	public CTreeOnStlBase<map<K, D, cmp>, CS>
{
public:
	CUniqueTreeOnStl(CTTREEGETKEYFCN gkf, CTTREECMPKEYFCN, CONTFLAG) :
		CTreeOnStlBase<map<K, D, cmp>, CS>(gkf)
	{
	}
	~CUniqueTreeOnStl() {}

	bool Insert (key_type key, referent_type data, iterator *pit = NULL)
	{
	guard_t guard (Guard());
	pair<iterator, bool> p = (*guard).insert (value_type (key, data));

		if (NULL != pit)
			*pit = p.first;
		return p.second;
	}
	bool Insert (referent_type data, iterator *pit = NULL)
	{
	const key_type key = key_converter<K>()((void *)(*GetKeyFcn())(data));
	guard_t guard (Guard());
	pair<iterator, bool> p = (*guard).insert (value_type (key, data));

		if (NULL != pit)
			*pit = p.first;
		return p.second;
	}

	bool FindNext (key_type key, iterator *pit) 
	{ 
	guard_t guard (Guard());

		_ASSERTE((*pit) != (*guard).end());
		*pit = (*guard).end(); 
		return false; 
	}	// no second entry
};

///////////////////////////////////////////////////////////////////////////////
// Navigator-äquivalent 
template<class T>
class CNavigatorOnStl
{
public:
	typedef T::referent_type referent_type;

public:
	CNavigatorOnStl (T &rCont) : m_rCont(rCont), m_it(rCont.begin()) {}

	void Reset (void) { m_it = m_rCont.begin(); }
	bool First (void) { m_it = m_rCont.begin(); return m_it != m_rCont.end(); }
	bool Valid (void) const { return m_it != m_rCont.end(); }
	bool Next (void) { return ++m_it != m_rCont.end(); }
	virtual bool Delete (void) 
	{ 
	T::iterator it = m_it;		// auf den nächsten Satz zeigen

		++it;
		if (m_rCont.Delete(m_it)) {
			m_it = it; 
			return true;
		}
		return false;
	}

	virtual referent_type lock() = 0;

protected:
	T &m_rCont;
	T::iterator m_it;
};

///////////////////////////////////////////////////////////////////////////////
// Navigatoräquivalent für SeqContainer
template<class T>
class CRingOnStl :
	public CNavigatorOnStl<T>
{
public:
	typedef T::value_type value_type;
	typedef T::referent_type referent_type;

public:
	CRingOnStl(T &rCont) : CNavigatorOnStl<T>(rCont) {}
	~CRingOnStl() {}

	bool Goto (ULONG lIndex) { return m_rCont.Goto (lIndex, &m_it); }
	bool Delete (void) 
	{ 
		return m_rCont.Delete(m_it);
	}

	referent_type lock() { _ASSERTE(Valid()); return (*m_it); }
};

///////////////////////////////////////////////////////////////////////////////
// Navigatoräquivalent für KeyContainer
template<class T>
class CTableOnStl :
	public CNavigatorOnStl<T>
{
public:
	typedef T::key_type key_type;
	typedef T::referent_type referent_type;
	typedef key_converter<T::key_type> pred;

public:
	CTableOnStl(T &rCont) : CNavigatorOnStl<T>(rCont) {}
	~CTableOnStl() {}

	bool Find (void *pKey) { return m_rCont.Find (pred()(pKey), &m_it); }
	bool FindFirst (void *pKey) { return m_rCont.FindFirst (pred()(pKey), &m_it); }
	bool FindNext (void *pKey) { return m_rCont.FindNext (pred()(pKey), &m_it); }

#if defined(_USE_UNSAFE_REINSERT)
	bool ReInsert (void *pKey, size_t iSize) { return m_rCont.ReInsert (pred()(pKey), iSize, &m_it); }
#endif // defined(_USE_UNSAFE_REINSERT)

	referent_type lock() { _ASSERTE(Valid()); return (*m_it).second; }
};

///////////////////////////////////////////////////////////////////////////////
// Deklaration der zusätzlich notwendigen Klassen 
template<class T>
class CLockOnStl
{
public:
	typedef T::referent_type referent_type;

public:
	CLockOnStl (CNavigatorOnStl<T> &rNav) : m_rNav(rNav) {}

	referent_type operator -> () { return m_rNav.lock(); } 
	operator referent_type() { return m_rNav.lock(); } 
	bool operator ! () { return NULL == m_rNav.lock(); }

private:
	CNavigatorOnStl<T> &m_rNav;
};

///////////////////////////////////////////////////////////////////////////////
// Helperklasse für das Erzeugen eines neuen Elementes
class CCreator {};	// placeholder only

template<class T>
class CCreatorOnStl :
	public CCreator
{
public:
	typedef T::referent_type referent_type;

public:
	CCreatorOnStl (T &rCont) : m_rCont(rCont) {}
	~CCreatorOnStl () {}

	referent_type InsertPtr (referent_type data)
	{
		if (!m_rCont.Insert (data))
			return referent_type(0);
		return data;
	}

private:
	T &m_rCont;
};

///////////////////////////////////////////////////////////////////////////////
// Wrapper für CSyncThread, welche jetzt durch _resource_guard ersetzt ist
template<class T>
class CSyncThreadOnStl 
{
public:
	template<class Y>
	CSyncThreadOnStl(Y *pTarget) : 
		m_guard(pTarget -> Guard()) {}

protected:
	T::guard_t m_guard;
};

}	// namespace container_wrappers

///////////////////////////////////////////////////////////////////////////////
// Vergleichsoperator
#define DefineCmpForTree(name,func,type) \
	class name##Cmp : public binary_function<type, type, bool> \
	{ public: bool operator() (const type &x, const type &y) const { return func(x, y) < 0; } };

///////////////////////////////////////////////////////////////////////////////
// Defines um klassische Container zu simulieren
#define DeclareOptLockStl(cont,elem) \
	typedef container_wrappers::CTableOnStl<cont> cont##Table; \
	typedef container_wrappers::CLockOnStl<cont> elem##Lock; \
	typedef container_wrappers::CCreatorOnStl<cont> elem##Creator; \
	typedef container_wrappers::CSyncThreadOnStl<cont> cont##Sync; 

#define DeclareLockStl(cont,elem) \
	typedef container_wrappers::CRingOnStl<cont> cont##Ring; \
	typedef container_wrappers::CLockOnStl<cont> elem##Lock; \
	typedef container_wrappers::CCreatorOnStl<cont> elem##Creator; \
	typedef container_wrappers::CSyncThreadOnStl<cont> cont##Sync; 
	
#endif // !defined(_CONTAINERWRAPPER_H__3F3DE28F_D284_4809_BBDD_04CB6DAEAFED__INCLUDED_)
