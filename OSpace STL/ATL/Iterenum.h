// InputIterator on IEnumXXX --------------------------------------------------
// File: ITERENUM.H

#if !defined(_ITERENUM_H)
#define _ITERENUM_H

#if _MSC_VER < 1100
#include <ospace/com/iterenum.wobase.h>
#else

#include <ospace/com/smartif.h>
#if !defined(OS_NO_STREAM_SUPPORT)
#include <ospace/header.h>
#endif // OS_NO_STREAM_SUPPORT

///////////////////////////////////////////////////////////////////////////////
// Templates, welche einen (COM-)Enumerator für einen beliebigen Datentyp 
// erzeugen und der eine zusätzliche Funktion zum Hinzufügen von neuen 
// Elementen enthält.
///////////////////////////////////////////////////////////////////////////////
// Interfacedeklaration 
//
// Die folgenden Templates setzen voraus, daß ein entsprechender GUID
// definiert und verfügbar ist. So benötigt man z.B. für einen IEnum<LONG>
// den definierten GUID IID_IEnumLONG.
//
template <class T>
class IEnum : public IUnknown 
{
public:
	typedef T enum_t;

// *** IUnknown methods
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS) PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;
	
// *** IEnum<T> methods
	STDMETHOD(Next) (THIS_ ULONG celt, T *rgelt, ULONG *pceltFetched) PURE;
	STDMETHOD(Skip) (THIS_ ULONG celt) PURE;
	STDMETHOD(Reset) (THIS) PURE;
	STDMETHOD(Clone) (THIS_ IEnum<T> ** ppenum) PURE;

	STDMETHOD_(ULONG, Count) (void) PURE;
	STDMETHOD(AddItem) (THIS_ const T &item) PURE;
	STDMETHOD(Clear) (THIS) PURE;
};

///////////////////////////////////////////////////////////////////////////////
// Neuere Variante eines normalen Enumerators mit Zugriff über Index
template <class T>
class IEnum2 : public IUnknown 
{
public:
	typedef T enum_t;

// *** IUnknown methods
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS) PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;
	
// *** IEnum<T> methods
	STDMETHOD(Next) (THIS_ ULONG celt, T *rgelt, ULONG *pceltFetched) PURE;
	STDMETHOD(Skip) (THIS_ ULONG celt) PURE;
	STDMETHOD(Reset) (THIS) PURE;
	STDMETHOD(Clone) (THIS_ IEnum2<T> ** ppenum) PURE;

// *** IEnum2<T> methods
	STDMETHOD(Count) (THIS_ ULONG *pulCount) PURE;
	STDMETHOD(GetItem) (THIS_ long lIndex, T *pitem) PURE;
	STDMETHOD(AddItem) (THIS_ const T &item, long lIndex /* = -1 */) PURE;
	STDMETHOD(RemoveItem) (THIS_ long lIndex /* = -1 */) PURE;
	STDMETHOD(Clear) (THIS) PURE;
};

///////////////////////////////////////////////////////////////////////////////
// Wrapperklasse für IID_XXX
#if !defined(DefineEnumIIDWrapper)
#define DefineEnumIIDWrapper(Type)								\
	class CIID_##Type##Enum {									\
	public:														\
	static const IID & iid (void) { return IID_IEnum##Type; }	\
	static const IID *piid (void) { return &IID_IEnum##Type ; }	\
	}
#define DefineEnumIIDWrapper2(Type,_IID)						\
	class CIID_##Type##Enum {									\
	public:														\
	static const IID & iid (void) { return _IID; }				\
	static const IID *piid (void) { return &_IID; }				\
	}
#endif // DefineEnumIIDWrapper

///////////////////////////////////////////////////////////////////////////////
// Synchronisationsobject für Enumeratoren 
#if _ATL_VER < 0x0110
template<typename ThreadModel = CComThreadModel>
class CSyncEnum 
{
private:
	ThreadModel::ObjectCriticalSection m_cs;

public:
		CSyncEnum () { m_cs.Init(); }
		~CSyncEnum () { m_cs.Term(); }

	void Lock() { m_cs.Lock(); }
	void Unlock() { m_cs.Unlock(); }
};

template<typename ThreadModel = CComThreadModel>
class CLockEnum {
private:
	CSyncEnum<ThreadModel> &m_rSync;

public:
		CLockEnum (CSyncEnum<ThreadModel> &rSync) : m_rSync(rSync) { rSync.Lock(); }
		~CLockEnum () { m_rSync.Unlock(); }
};

#else

// die neue ATL enthält alles was wir brauchen
template<typename ThreadModel = CComObjectThreadModel>
class CLockEnum {
private:
	ThreadModel::AutoCriticalSection &m_rSync;

public:
		CLockEnum (ThreadModel::AutoCriticalSection &rSync) : m_rSync(rSync) { rSync.Lock(); }
		~CLockEnum () { m_rSync.Unlock(); }
};

#endif 

///////////////////////////////////////////////////////////////////////////////
// Implementation des geforderten IEnum<XXX>
//
// Als TemplateParameter müssen gegeben sein:
//		T:			Datentyp der Enumeriert werden soll (z.B. LONG)
//		C:			STL-Container, auf dessen Grundlage der Enumerator realisiert
//					wird (set, multiset, vector, list oder deque)
//					z.B. vector<LONG>
//
// Diese Klasse kann wie ein normaler Enumerator verwendet werden.
//
template<typename T, typename C, typename Base = IEnum<T>, typename ThreadModel = CComObjectThreadModel>
class __EnumeratorBase : public Base
{
public:
	typedef C cont_t;
	typedef T item_t;
	typedef cont_t::iterator iterator;
	typedef cont_t::const_iterator const_iterator;
	typedef __EnumeratorBase<T, C, Base, ThreadModel> self;
	typedef __EnumeratorBase<T, C, Base, ThreadModel> base_self;
#if _ATL_VER < 0x0110
	typedef CSyncEnum<ThreadModel> sync_t;
#else
	typedef ThreadModel::AutoCriticalSection sync_t;
#endif
	typedef ThreadModel threadmodel_t;

protected:
	cont_t m_data;
	iterator m_itcur;
	sync_t m_sync;
	bool m_fIsDirty;

	bool eoi_reached (void) MASKED_NOTHROW() { return m_itcur == m_data.end(); }
	bool isempty (void) MASKED_NOTHROW() { return m_data.size() == 0; }
	bool isdirty (void) MASKED_NOTHROW() { return m_fIsDirty ? true : false; }
	void setdirty (bool fFlag) MASKED_NOTHROW() { m_fIsDirty = fFlag ? true : false; }

public:
		__EnumeratorBase (void) MASKED_NOTHROW() { setdirty(false); Reset(); }
		__EnumeratorBase (const self & x_) MASKED_NOTHROW() : m_sync(), m_data(x_.m_data), m_itcur(m_data.begin())
			{	// clones target
			CLockEnum<ThreadModel> SyncMe(m_sync);

				Reset();
				if (!isempty() && !const_cast<self &>(x_).eoi_reached()) {
				cont_t::size_type n = 0;
				cont_t::const_iterator it = x_.m_data.begin();
				cont_t::const_iterator itcur = x_.m_itcur;

					distance (it, itcur, n);
					advance (m_itcur, n);
				} 
				setdirty(true);
			}
		virtual ~__EnumeratorBase (void) MASKED_NOTHROW() {}
		virtual base_self *Construct (void) = 0;
		virtual sync_t *get_sync_object() { return &m_sync; }

// *** IEnum<X> methods
	STDMETHODIMP Next (ULONG celt, T *rgelt, ULONG *pceltFetched) MASKED_NOTHROW() 
		{
		CLockEnum<ThreadModel> SyncMe(m_sync);
		DWORD cReturn = 0L;

			if (pceltFetched) *pceltFetched = 0L;
			if (NULL == rgelt || m_data.end() == m_itcur) 
				return ResultFromScode (S_FALSE);
        			
			while (m_itcur != m_data.end() && 0 < celt) {
				*rgelt = *m_itcur;
				rgelt++; m_itcur++;	// weiterzählen
				celt--;
				cReturn++;
			}
			if (pceltFetched) 
				*pceltFetched = (cReturn - celt);	// gelieferte Werte

			return NOERROR;
		}
	STDMETHODIMP Skip (ULONG dwSkip) MASKED_NOTHROW() 
		{
			if (0 == dwSkip) return NOERROR;

		CLockEnum<ThreadModel> SyncMe(m_sync);
		iterator it = m_itcur;

			while (it != m_data.end()) {
				++it;
				if (--dwSkip == 0) {
					m_itcur = it;
					return NOERROR;
				}
			}
			return S_FALSE;
		}
	STDMETHODIMP Reset (void) MASKED_NOTHROW() 
		{
			m_itcur = isempty() ? m_data.end() : m_data.begin();
			return NOERROR;
		}
	STDMETHODIMP Clone (IEnum<T> **ppenum) MASKED_NOTHROW() 
		{
		CLockEnum<ThreadModel> SyncMe(m_sync);

			*ppenum = NULL;		// für alle Fälle

		base_self *pEnum = Construct();		// Enumerator bilden (standalone)

			if (pEnum == NULL) return E_OUTOFMEMORY;
			*ppenum = pEnum;
			return NOERROR;
		}

// *** IEnum<X> methods
	STDMETHODIMP_(ULONG) Count (void) MASKED_NOTHROW() { CLockEnum<ThreadModel> SyncMe(m_sync); return m_data.size(); }
	STDMETHODIMP AddItem (const T &item)
		{ 
		CLockEnum<ThreadModel> SyncMe(m_sync); 
		cont_t::size_type cnt = m_data.size();

			m_data.insert(m_data.end(), item); 
			return (cnt == m_data.size()) ? S_FALSE : setdirty(true), S_OK; 
		}
	STDMETHODIMP Clear (void)
		{ 
		CLockEnum<ThreadModel> SyncMe(m_sync);
		bool fEmpty = isempty();
		
			setdirty(true);
			m_data.erase (m_data.begin(), m_data.end()); 
			m_itcur = m_data.end();		// kein aktuelles Item mehr
			return fEmpty ? S_FALSE : NOERROR;
		}
};

///////////////////////////////////////////////////////////////////////////////
// Implementation des geforderten IEnum2<XXX>
//
// Als TemplateParameter müssen gegeben sein:
//		T:			Datentyp der Enumeriert werden soll (z.B. LONG)
//		C:			STL-Container, auf dessen Grundlage der Enumerator realisiert
//					wird (set, multiset, vector, list oder deque)
//					z.B. vector<LONG>
//
// Diese Klasse kann wie ein normaler Enumerator verwendet werden.
//
template<typename T, typename C, typename Base = IEnum2<T>, typename ThreadModel = CComObjectThreadModel>
class __EnumeratorBase2 : public Base
{
public:
	typedef C cont_t;
	typedef T item_t;
	typedef cont_t::iterator iterator;
	typedef cont_t::const_iterator const_iterator;
	typedef __EnumeratorBase2<T, C, Base, ThreadModel> self;
	typedef __EnumeratorBase2<T, C, Base, ThreadModel> base_self;
#if _ATL_VER < 0x0110
	typedef CSyncEnum<ThreadModel> sync_t;
#else
	typedef ThreadModel::AutoCriticalSection sync_t;
#endif
	typedef ThreadModel threadmodel_t;

protected:
	cont_t m_data;
	iterator m_itcur;
	sync_t m_sync;
	bool m_fIsDirty;

	bool eoi_reached (void) MASKED_NOTHROW() { return m_itcur == m_data.end(); }
	bool isempty (void) MASKED_NOTHROW() { return m_data.size() == 0; }
	bool isdirty (void) MASKED_NOTHROW() { return m_fIsDirty ? true : false; }
	void setdirty (bool fFlag) MASKED_NOTHROW() { m_fIsDirty = fFlag ? true : false; }

public:
		__EnumeratorBase2 (void) MASKED_NOTHROW() { setdirty(false); Reset(); }
		__EnumeratorBase2 (const self & x_) MASKED_NOTHROW() : m_sync(), m_data(x_.m_data), m_itcur(m_data.begin())
			{	// clones target
			CLockEnum<ThreadModel> SyncMe(m_sync);

				Reset();
				if (!isempty() && !const_cast<self &>(x_).eoi_reached()) {
				cont_t::size_type n = 0;
				cont_t::const_iterator it = x_.m_data.begin();
				cont_t::const_iterator itcur = x_.m_itcur;

					distance (it, itcur, n);
					advance (m_itcur, n);
				} 
				setdirty(true);
			}
		virtual ~__EnumeratorBase2 (void) MASKED_NOTHROW() {}
		virtual base_self *Construct (void) = 0;
		virtual sync_t *get_sync_object() { return &m_sync; }

// *** IEnum<X> methods
	STDMETHODIMP Next (ULONG celt, T *rgelt, ULONG *pceltFetched) MASKED_NOTHROW() 
		{
		CLockEnum<ThreadModel> SyncMe(m_sync);
		DWORD cReturn = 0L;

			if (pceltFetched) *pceltFetched = 0L;
			if (NULL == rgelt || m_data.end() == m_itcur) 
				return ResultFromScode (S_FALSE);
        			
			while (m_itcur != m_data.end() && 0 < celt) {
				*rgelt = *m_itcur;
				rgelt++; m_itcur++;	// weiterzählen
				celt--;
				cReturn++;
			}
			if (pceltFetched) 
				*pceltFetched = (cReturn - celt);	// gelieferte Werte

			return NOERROR;
		}
	STDMETHODIMP Skip (ULONG dwSkip) MASKED_NOTHROW() 
		{
			if (0 == dwSkip) return NOERROR;

		CLockEnum<ThreadModel> SyncMe(m_sync);
		iterator it = m_itcur;

			while (it != m_data.end()) {
				++it;
				if (--dwSkip == 0) {
					m_itcur = it;
					return NOERROR;
				}
			}
			return S_FALSE;
		}
	STDMETHODIMP Reset (void) MASKED_NOTHROW() 
		{
			m_itcur = isempty() ? m_data.end() : m_data.begin();
			return NOERROR;
		}
	STDMETHODIMP Clone (IEnum2<T> **ppenum) MASKED_NOTHROW() 
		{
		CLockEnum<ThreadModel> SyncMe(m_sync);

			*ppenum = NULL;		// für alle Fälle

		base_self *pEnum = Construct();		// Enumerator bilden (standalone)

			if (pEnum == NULL) return E_OUTOFMEMORY;
			*ppenum = pEnum;
			return NOERROR;
		}

// *** IEnum<X> methods
	STDMETHODIMP Count (ULONG *plCnt) MASKED_NOTHROW() 
		{ 
			if (NULL == plCnt) return E_POINTER;

		CLockEnum<ThreadModel> SyncMe(m_sync); 

			*plCnt = m_data.size(); 
			return S_OK;
		}
	STDMETHODIMP GetItem (long lIndex, T *pitem)
		{
		CLockEnum<ThreadModel> SyncMe(m_sync); 
		
			if (lIndex < 0 || C::size_type(lIndex) >= m_data.size()) 
				return E_INVALIDARG;

		iterator it = m_data.begin();

			advance (it, lIndex);
			*pitem = *it;
			return S_OK;
		}
	STDMETHODIMP AddItem (const T &item, long lIndex)
		{
		CLockEnum<ThreadModel> SyncMe(m_sync); 
		
			if (-1 == lIndex)
				m_data.insert(m_data.end(), item);
			else if (0 <= lIndex && C::size_type(lIndex) < m_data.size()) {
			iterator it = m_data.begin();

				advance (it, lIndex);
				m_data.insert(it, item);
			} else
				return E_INVALIDARG;
			setdirty(true); 
			return S_OK; 
		}
	STDMETHODIMP RemoveItem (long lIndex)
		{
		CLockEnum<ThreadModel> SyncMe(m_sync); 

			if (-1 == lIndex)
				lIndex = m_data.size()-1;	// letztes Item entfernen

			if (lIndex < 0 || C::size_type(lIndex) >= m_data.size()) 
				return E_INVALIDARG;

		iterator it = m_data.begin();

			advance (it, lIndex);
			if (it == m_itcur)		// wenn aktuelles Item gelöscht wird
				m_itcur = m_data.end();
			m_data.erase(it);
			setdirty(true); 
			return S_OK;
		}
	STDMETHODIMP Clear (void) MASKED_NOTHROW() 
		{ 
		CLockEnum<ThreadModel> SyncMe(m_sync);
		bool fEmpty = isempty();
		
			setdirty(true);
			m_data.erase (m_data.begin(), m_data.end()); 
			m_itcur = m_data.end();		// kein aktuelles Item mehr
			return fEmpty ? S_FALSE : NOERROR;
		}
};

///////////////////////////////////////////////////////////////////////////////
// BasisInterface für Enumerator mit Suchfunktionalität
template <class K, class T>
class IEnumEx : public IUnknown 
{
public:
	typedef K enumkey_t;
	typedef T enum_t;

// *** IUnknown methods
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS) PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;
	
// *** IEnum<T> methods
	STDMETHOD(Next) (THIS_ ULONG celt, T *rgelt, ULONG *pceltFetched) PURE;
	STDMETHOD(Skip) (THIS_ ULONG celt) PURE;
	STDMETHOD(Reset) (THIS) PURE;
	STDMETHOD(Clone) (THIS_ IEnumEx<K, T> ** ppenum) PURE;

// *** IEnumEx<K, T>
	STDMETHOD(Count) (THIS_ ULONG *plCnt) PURE;
	STDMETHOD(AddItem) (THIS_ const K &key, const T &item) PURE;
	STDMETHOD(Clear) (THIS) PURE;
	STDMETHOD(FindItem) (THIS_ const K &key, T *pitem) PURE;
	STDMETHOD(RemoveItem) (THIS_ const K &key) PURE;
};

///////////////////////////////////////////////////////////////////////////////
// Implementation des geforderten IEnum<XXX>
//
// Als TemplateParameter müssen gegeben sein:
//		T:			Datentyp der Enumeriert werden soll (z.B. BSTR's, sortiert nach LONG's)
//		K:			Datentyp, nach dem sortiert werden soll (z.B. LONG)
//		C:			STL-Container, auf dessen Grundlage der Enumerator realisiert
//					wird (map, multimap) z.B. map<LONG, BSTR, less<LONG> >
//
// Diese Klasse kann wie ein normaler Enumerator verwendet werden.
//
template<typename T, typename C, typename Base = IEnumEx<C::key_type, C::mapped_type>, typename ThreadModel = CComObjectThreadModel >
class __EnumeratorBaseTarget : public Base
{
public:
	typedef C cont_t;
	typedef T item_t;
	typedef cont_t::key_type key_type;
	typedef cont_t::mapped_type mapped_type;
	typedef cont_t::iterator iterator;
	typedef cont_t::const_iterator const_iterator;
	typedef __EnumeratorBaseTarget<T, C, Base, ThreadModel> self;
	typedef __EnumeratorBaseTarget<T, C, Base, ThreadModel> base_self;
#if _ATL_VER < 0x0110
	typedef CSyncEnum<ThreadModel> sync_t;
#else
	typedef ThreadModel::AutoCriticalSection sync_t;
#endif
	typedef ThreadModel threadmodel_t;

protected:
	cont_t m_data;
	iterator m_itcur;
	sync_t m_sync;
	bool m_fIsDirty;

	bool eoi_reached (void) MASKED_NOTHROW() { return m_itcur == m_data.end(); }
	bool isempty (void) MASKED_NOTHROW() { return m_data.size() == 0; }
	bool isdirty (void) MASKED_NOTHROW() { return m_fIsDirty ? true : false; }
	void setdirty (bool fFlag) MASKED_NOTHROW() { m_fIsDirty = fFlag ? true : false; }

public:
		__EnumeratorBaseTarget (void) MASKED_NOTHROW() { setdirty(false); Reset(); }
		__EnumeratorBaseTarget (const self & x_) MASKED_NOTHROW() : m_sync(), m_data(x_.m_data), m_itcur(m_data.begin())
			{	// clones target
			CLockEnum<ThreadModel> SyncMe(m_sync);

				Reset();
				if (!isempty() && !const_cast<self &>(x_).eoi_reached()) {
				cont_t::size_type n = 0;
				cont_t::const_iterator it = x_.m_data.begin();
				cont_t::const_iterator itcur = x_.m_itcur;

					distance (it, itcur, n);
					advance (m_itcur, n);
				} 
				setdirty(true);
			}
		virtual ~__EnumeratorBaseTarget (void) MASKED_NOTHROW() {}
		virtual base_self *Construct (void) = 0;
		virtual sync_t *get_sync_object() { return &m_sync; }

// *** IEnum<X> methods
	STDMETHODIMP Next (ULONG celt, mapped_type *rgelt, ULONG *pceltFetched) MASKED_NOTHROW() 
		{
		CLockEnum<ThreadModel> SyncMe(m_sync);
		DWORD cReturn = 0L;

			if (pceltFetched) *pceltFetched = 0L;
			if (NULL == rgelt || m_data.end() == m_itcur) 
				return ResultFromScode (S_FALSE);
        			
			while (m_itcur != m_data.end() && 0 < celt) {
				*rgelt = (*m_itcur).second;
				rgelt++; m_itcur++;	// weiterzählen
				celt--;
				cReturn++;
			}
			if (pceltFetched) 
				*pceltFetched = (cReturn - celt);	// gelieferte Werte

			return NOERROR;
		}
	STDMETHODIMP Skip (ULONG dwSkip) MASKED_NOTHROW() 
		{
			if (0 == dwSkip) return NOERROR;

		CLockEnum<ThreadModel> SyncMe(m_sync);
		iterator it = m_itcur;

			while (it != m_data.end()) {
				++it;
				if (--dwSkip == 0) {
					m_itcur = it;
					return NOERROR;
				}
			}
			return S_FALSE;
		}
	STDMETHODIMP Reset (void) MASKED_NOTHROW() 
		{
			m_itcur = isempty() ? m_data.end() : m_data.begin();
			return NOERROR;
		}
	STDMETHODIMP Clone (IEnumEx<key_type, mapped_type> **ppenum) MASKED_NOTHROW() 
		{
		CLockEnum<ThreadModel> SyncMe(m_sync);

			*ppenum = NULL;		// für alle Fälle

		base_self *pEnum = Construct();		// Enumerator bilden (standalone)

			if (pEnum == NULL) return E_OUTOFMEMORY;
			*ppenum = pEnum;
			return NOERROR;
		}

// *** IEnumEx<X, Y> methods
	STDMETHODIMP Count (ULONG *plCnt) MASKED_NOTHROW() 
		{ 
			if (NULL == plCnt) return E_POINTER;

		CLockEnum<ThreadModel> SyncMe(m_sync); 

			*plCnt = m_data.size(); 
			return S_OK;
		}
	STDMETHODIMP AddItem (const key_type& key, const mapped_type &item) MASKED_NOTHROW() 
		{ CLockEnum<ThreadModel> SyncMe(m_sync); m_data.insert(key, item); setdirty(true); return NOERROR; }
	STDMETHODIMP Clear (void) MASKED_NOTHROW() 
		{ 
		CLockEnum<ThreadModel> SyncMe(m_sync);
		bool fEmpty = isempty();
		
			m_data.erase (m_data.begin(), m_data.end()); 
			m_itcur = m_data.end();		// kein aktuelles Item mehr
			setdirty(true);
			return fEmpty ? S_FALSE : NOERROR;
		}
	STDMETHODIMP FindItem (const key_type &key, mapped_type *pItem)
	{
		if (NULL == pItem) return E_POINTER;

	CLockEnum<ThreadModel> SyncMe(m_sync); 
	iterator it = m_data.find (key); 
	
		if (it != m_data.end()) {
			*pItem = (*it).second;
			return S_OK;
		}
		return S_FALSE;
	}
	STDMETHODIMP RemoveItem (const key_type &key)
	{
	CLockEnum<ThreadModel> SyncMe(m_sync); 
	iterator it = m_data.find (key); 
	
		if (it != m_data.end()) {
			if (it == m_itcur) 
				m_itcur = m_data.end();		// kein aktuelles Item mehr
			m_data.erase (it);
			setdirty(true); 
			return S_OK;
		}
		return S_FALSE; 
	}
};

///////////////////////////////////////////////////////////////////////////////
// Nicht Aggregierbarer Enumerator 
template<class T, class ID, class C, class Base = __EnumeratorBase<T, C, IEnum<T> > >
class __Enumerator : public Base
{
protected:
	LONG m_dwRefCnt;

public:
	typedef __Enumerator<T, ID, C, Base> self;
	typedef Base::threadmodel_t threadmodel_t;
	typedef Base::sync_t sync_t;

		__Enumerator (void) MASKED_NOTHROW() : m_dwRefCnt(1) {}
		__Enumerator (const self & x_) MASKED_NOTHROW() : m_dwRefCnt(1), base_self (x_) {}
		~__Enumerator (void) MASKED_NOTHROW() {}
	
	Base::base_self *Construct (void) MASKED_NOTHROW() 
		{
//		CLockEnum<threadmodel_t> SyncMe(m_sync); 
		base_self *p = NULL; 
			
			ATLTRY(p = new self (*this)); 
			return p;
		}

// *** IUnknown methods
	STDMETHODIMP QueryInterface (REFIID riid, LPVOID *ppvObj) MASKED_NOTHROW() 
		{
			if (riid == ID::iid() || riid == IID_IUnknown) 
				{ *ppvObj = this; AddRef(); return NOERROR; }
			return ResultFromScode(E_NOINTERFACE);
		}
#if _ATL_VER < 0x0110
	STDMETHODIMP_(ULONG) AddRef (void)
		{ return CComThreadModel::Increment(&m_dwRefCnt); }
	STDMETHODIMP_(ULONG) Release (void)
		{ if (CComThreadModel::Decrement(&m_dwRefCnt) == 0) { delete this; return 0L; } return m_dwRefCnt; }
#else
	STDMETHODIMP_(ULONG) AddRef (void) MASKED_NOTHROW() 
		{ return threadmodel_t::Increment(&m_dwRefCnt); }
	STDMETHODIMP_(ULONG) Release (void) MASKED_NOTHROW() 
		{ if (threadmodel_t::Decrement(&m_dwRefCnt) == 0) { delete this; return 0L; } return m_dwRefCnt; }
#endif 

#if !defined(OS_NO_STREAM_SUPPORT)
	friend void os_write (os_bstream &rStream, const self &rcEnum);
	friend void os_read (os_bstream &rStream, self &rEnum);

	OS_POLY_FUNCTION((self *));
#endif // OS_NO_STREAM_SUPPORT
};

///////////////////////////////////////////////////////////////////////////////
// Nicht Aggregierbarer Enumerator (mit explizitem ThreadModel)
template<
	typename T, 
	typename ID, 
	typename C, 
	typename ThreadModel = CComObjectThreadModel, 
	typename Base = __EnumeratorBase<T, C, IEnum<T>, ThreadModel> 
>
class __EnumeratorEx : public Base
{
protected:
	LONG m_dwRefCnt;

public:
	typedef __EnumeratorEx<T, ID, C, ThreadModel, Base> self;

		__EnumeratorEx (void) MASKED_NOTHROW() : m_dwRefCnt(1) {}
		__EnumeratorEx (const self & x_) MASKED_NOTHROW() : m_dwRefCnt(1), base_self (x_) {}
		~__EnumeratorEx (void) MASKED_NOTHROW() {}
	
	Base::base_self *Construct (void) MASKED_NOTHROW() 
		{
		CLockEnum<ThreadModel> SyncMe(m_sync); 
		base_self *p = NULL; 
			
			ATLTRY(p = new self (*this)); 
			return p;
		}

// *** IUnknown methods
	STDMETHODIMP QueryInterface (REFIID riid, LPVOID *ppvObj) MASKED_NOTHROW() 
		{
			if (riid == ID::iid() || riid == IID_IUnknown) 
				{ *ppvObj = this; AddRef(); return NOERROR; }
			return ResultFromScode(E_NOINTERFACE);
		}

	STDMETHODIMP_(ULONG) AddRef (void) MASKED_NOTHROW() 
		{ return ThreadModel::Increment(&m_dwRefCnt); }
	STDMETHODIMP_(ULONG) Release (void) MASKED_NOTHROW() 
		{ if (ThreadModel::Decrement(&m_dwRefCnt) == 0) { delete this; return 0L; } return m_dwRefCnt; }

#if !defined(OS_NO_STREAM_SUPPORT)
	friend void os_write (os_bstream &rStream, const self &rcEnum);
	friend void os_read (os_bstream &rStream, self &rEnum);

	OS_POLY_FUNCTION((self *));
#endif // OS_NO_STREAM_SUPPORT
};

#if !defined(OS_NO_STREAM_SUPPORT)
///////////////////////////////////////////////////////////////////////////////
// bstream-Funktionen lediglich deklarieren, selbige müssen für jede Instanz 
// separat instanziiert werden
template<class T, class ID, class C, class Base = IEnum<T> >
void os_write (os_bstream &, const __Enumerator<T, ID, C, Base> &);

template<class T, class ID, class C, class Base = IEnum<T> >
void os_read (os_bstream &, __Enumerator<T, ID, C, Base> &);

OS_POLY_CLASS_T4(__Enumerator);
OS_STREAM_OPERATORS_T4(__Enumerator);
#endif // OS_NO_STREAM_SUPPORT

///////////////////////////////////////////////////////////////////////////////
// Aggregierbarer Enumerator 
template<class T, class ID, class C, class Base = __EnumeratorBase<T, C, IEnum<T> > >
class __AggEnumerator : public Base
{
protected:
	WUnknown IUnk;		// controlling unknown

public:
	typedef __AggEnumerator<T, ID, C, Base> self;

		__AggEnumerator (IUnknown *pIUnk) MASKED_NOTHROW() : IUnk(pIUnk) {}
		__AggEnumerator (const self & x_) MASKED_NOTHROW() : IUnk(_x.IUnk), base_self (x_) {}
		~__AggEnumerator (void) MASKED_NOTHROW() {}
	
	Base::base_self *Construct (void) MASKED_NOTHROW() 
		{
		CLockEnum<CComObjectThreadModel> SyncMe(m_sync); 
		base_self *p = NULL; 
			
			ATLTRY(p = new self (*this)); 
			return p;
		}

// *** IUnknown methods (delegating IUnknown)
	STDMETHODIMP QueryInterface (REFIID riid, LPVOID *ppvObj) MASKED_NOTHROW() 
		{	
			if (riid == ID::iid())	// our interface
				{ *ppvObj = this; AddRef(); return NOERROR; }
			return IUnk -> QueryInterface (riid, ppvObj); 
		}
	STDMETHODIMP_(ULONG) AddRef (void) { return IUnk -> AddRef(); }
	STDMETHODIMP_(ULONG) Release (void)	{ return IUnk -> Release(); }

#if !defined(OS_NO_STREAM_SUPPORT)
	friend void os_write (os_bstream &rStream, const self &rcEnum);
	friend void os_read (os_bstream &rStream, self &rEnum);

	OS_POLY_FUNCTION((self *));
#endif // OS_NO_STREAM_SUPPORT
};

///////////////////////////////////////////////////////////////////////////////
// Aggregierbarer Enumerator (mit explizitem ThreadModel)
template<
	typename T, 
	typename ID, 
	typename C, 
	typename ThreadModel = CComObjectThreadModel, 
	typename Base = __EnumeratorBase<T, C, IEnum<T>, ThreadModel> 
>
class __AggEnumeratorEx : public Base
{
protected:
	WUnknown IUnk;		// controlling unknown

public:
	typedef __AggEnumeratorEx<T, ID, C, ThreadModel, Base> self;

		__AggEnumeratorEx (IUnknown *pIUnk) MASKED_NOTHROW() : IUnk(pIUnk) {}
		__AggEnumeratorEx (const self & x_) MASKED_NOTHROW() : IUnk(_x.IUnk), base_self (x_) {}
		~__AggEnumeratorEx (void) MASKED_NOTHROW() {}
	
	Base::base_self *Construct (void) MASKED_NOTHROW() 
		{
		CLockEnum<ThreadModel> SyncMe(m_sync); 
		base_self *p = NULL; 
			
			ATLTRY(p = new self (*this)); 
			return p;
		}

// *** IUnknown methods (delegating IUnknown)
	STDMETHODIMP QueryInterface (REFIID riid, LPVOID *ppvObj) MASKED_NOTHROW() 
		{	
			if (riid == ID::iid())	// our interface
				{ *ppvObj = this; AddRef(); return NOERROR; }
			return IUnk -> QueryInterface (riid, ppvObj); 
		}
	STDMETHODIMP_(ULONG) AddRef (void) { return IUnk -> AddRef(); }
	STDMETHODIMP_(ULONG) Release (void)	{ return IUnk -> Release(); }

#if !defined(OS_NO_STREAM_SUPPORT)
	friend void os_write (os_bstream &rStream, const self &rcEnum);
	friend void os_read (os_bstream &rStream, self &rEnum);

	OS_POLY_FUNCTION((self *));
#endif // OS_NO_STREAM_SUPPORT
};

#if !defined(OS_NO_STREAM_SUPPORT)
///////////////////////////////////////////////////////////////////////////////
// bstream-Funktionen lediglich deklarieren, selbige müssen für jede Instanz 
// separat instanziiert werden
template<class T, class ID, class C, class Base = IEnum<T> >
void os_write (os_bstream &, const __AggEnumerator<T, ID, C, Base> &);

template<class T, class ID, class C, class Base = IEnum<T> >
void os_read (os_bstream &, __AggEnumerator<T, ID, C, Base> &);

OS_POLY_CLASS_T4(__AggEnumerator);
OS_STREAM_OPERATORS_T4(__AggEnumerator);
#endif // OS_NO_STREAM_SUPPORT

///////////////////////////////////////////////////////////////////////////////
// Makros, welches StandardImplementationen für einen Enumerator definieren
//
// Normaler (nicht sortierender) Enumerator: über list<Type> --> NEnumXXX
//
#define DefineEnumerator(Type)					\
	typedef __Enumerator<Type, __CIID<&__uuidof(IEnum##Type)>, list<Type> > NEnum##Type;
#define DefineEnumerator2(Type,IID)				\
	typedef __Enumerator<Type, __CIID<&IID>, list<Type> > NEnum##Type;

#define DefineEnumeratorAggr(Type)				\
	typedef __AggEnumerator<Type, __CIID<&__uuidof(IEnum##Type)>, list<Type> > NEnumAggr##Type;
#define DefineEnumeratorAggr2(Type,IID)			\
	typedef __AggEnumerator<Type, __CIID<&IID>, list<Type> > NEnumAggr##Type;

//
// Sortierender Enumerator:	über set<Type, less<Type> > --> SEnumXXX
//
#define DefineSortingEnumerator(Type)			\
	typedef __Enumerator<Type, __CIID<&__uuidof(IEnum##Type)>, set<Type,less<Type> > > SEnum##Type
#define DefineSortingEnumerator2(Type,IID)		\
	typedef __Enumerator<Type, __CIID<&IID>, set<Type,less<Type> > > SEnum##Type

#define DefineSortingEnumeratorAggr(Type)		\
	typedef __AggEnumerator<Type, __CIID<&__uuidof(IEnum##Type)>, set<Type,less<Type> > > SEnumAggr##Type
#define DefineSortingEnumeratorAggr2(Type,IID)	\
	typedef __AggEnumerator<Type, __CIID<&IID>, set<Type,less<Type> > > SEnumAggr##Type

//
// InterfaceWrapper für einen TemplateEnumerator
//
#define DefineSmartEnumerator(Type)		\
	typedef __Interface<IEnum<Type>, __CIID<&__uuidof(IEnum##Type)>, CComPtr<IEnum<Type> > > WEnum##Type;
#define DefineSmartEnumerator2(Type,IID)	\
	typedef __Interface<IEnum<Type>, __CIID<&IID>, CComPtr<IEnum<Type> > > WEnum##Type;

///////////////////////////////////////////////////////////////////////////////
// Template, welches aus einem (COM-)Enumerator einen Input-Iterator macht
//
// Auf diese Art und Weise kann ein normaler (COM-)Enumerator als Datenquelle
// für beliebige STL-Algorithmen fungieren, die mindestens einen InputIterator 
// benötigen.
// Diese Klasse ist in Analogie zum istream_iterator zu verwenden.
//
// Als TemplateParameter müssen gegeben sein:
//		T:			Datentyp der Enumeriert werden soll (z.B. LONG)
//		piid:		Pointer auf zugehörigen GUID (z.B. &IID_IEnumLONG)
//		Distance:	DistanceType (s.a. istream_iterator, i.a. ptrdiff_t)
//
// ACHTUNG: Man kann die Elemente des unterliegenden Enumerators lediglich
//			einmal durchgehen (eben ein InputIterator) !
//
template <class T, class ID, class Distance>
class ienum_iterator : public input_iterator<T, Distance>
{
public:
	typedef IEnum<T> enum_t;
	typedef ienum_iterator<T, ID, Distance> self;

protected:
	__Interface<enum_t, ID, CComPtr<enum_t> > enumerator;
	T value;
	bool end_marker;

	// ACHTUNG: Der Destruktor der Klasse T muß das Objekt so hinterlassen,
	//			daß ein zweiter Destruktoraufruf nach einem evtl. 
	//			fehlgeschlagenes Next keinen Schaden anrichten kann.
	void read (void) MASKED_NOTHROW() 
		{
			value.~T();			// vorheriges Objekt explizit zerlegen
			end_marker = (S_OK != enumerator -> Next (1, &value, NULL)) ? true : false; 
		}

public:
	ienum_iterator (void) MASKED_NOTHROW() : enumerator(), end_marker(true) {}
	ienum_iterator (enum_t *pIEnum) MASKED_NOTHROW() : enumerator(pIEnum), end_marker(true) 
		{ enumerator->Reset(); read(); }
	ienum_iterator (IUnknown *pIUnk) MASKED_THROW(_com_error) : enumerator(pIUnk), end_marker(true)	// throws HRESULT
		{ enumerator->Reset(); read(); }

	const T & operator * (void) const MASKED_NOTHROW() { return value; }

	self& operator++ (void)	MASKED_NOTHROW() { read(); return *this; }
	self operator++ (int) MASKED_NOTHROW() { self tmp = *this; read(); return tmp; }

	bool operator == (const self & x_) const MASKED_NOTHROW() 
		{ 
			return enumerator == x_.enumerator && end_marker == x_.end_marker ||
				   end_marker == true && x_.end_marker == true;
		}
	bool operator != (const self & x_) const MASKED_NOTHROW() 
		{ return !(*this == x_); }
};

///////////////////////////////////////////////////////////////////////////////
// Makro, das für einen vorgegebenen Enumerator einen InputIterator definiert
//
#define DefineEnumInputIterator(Type)		\
	typedef ienum_iterator<Type, __CIID<&__uuidof(IEnum##Type)>, ptrdiff_t> InEnum##Type;
#define DefineEnumInputIterator2(Type,IID)		\
	typedef ienum_iterator<Type, __CIID<&IID>, ptrdiff_t> InEnum##Type;

///////////////////////////////////////////////////////////////////////////////
// Template, welches einem (COM-)Enumerator einen Output-Iterator verpaßt 
//
// Diese TemplateKlasse läßt sich nur in Verbindung mit einem IEnum<XXX> (s.o.)
// verwenden, da auf die Funktion AddItem zurückgeriffen wird, die nicht 
// standardmäßig bei (COM-)Enumeratoren vorhanden ist.
// Diese Klasse ist in Analogie zum ostream_iterator zu verwenden.
//
// Ein mit diesem Template generierter OutputIterator kann in Verbindung mit
// allen STL-Algorithmen verwendet werden, die mindestens einen OutputIterator
// erwarten (z.B. 3. Parameter von copy()).
//
// Als TemplateParameter müssen gegeben sein:
//		T:			Datentyp der Enumeriert werden soll (z.B. LONG)
//		piid:		Pointer auf zugehörigen GUID (z.B. &IID_IEnumLONG)
//
template <class T, class ID>
class oenum_iterator : public output_iterator
{
public:
	typedef IEnum<T> enum_t;
	typedef oenum_iterator<T, ID> self;

protected:
	__Interface<enum_t, ID, CComPtr<enum_t> > enumerator;

public:
	oenum_iterator (void) MASKED_NOTHROW() : enumerator() {}
	oenum_iterator (enum_t *pIEnum) MASKED_NOTHROW() : enumerator(pIEnum) {}
	oenum_iterator (IUnknown *pIUnk) MASKED_THROW(_com_error) : enumerator(pIUnk) {}	// throws hr
	oenum_iterator (const self &iter) MASKED_NOTHROW() : enumerator(iter.enumerator) {}

    self& operator = (const T& value) MASKED_NOTHROW() 
		{ enumerator -> AddItem (value); return *this; }
	self& operator * (void) MASKED_NOTHROW() { return *this; }
	self& operator++ (void)	MASKED_NOTHROW() { return *this; }
	self operator++ (int) MASKED_NOTHROW() { return *this; }
};

/////////////////////////////////////////////////////////////////////////////
// Spezieller Output-Iterator, der zusätzliches Predikat prüft
template<class T, class ID, class pred>
class oenum_iterator_if :
	public oenum_iterator<T, ID>
{
public:
	typedef IEnum<T> enum_t;
	typedef oenum_iterator_if<T, ID, pred> self;
	typedef oenum_iterator<T, ID> base;

public:
	oenum_iterator_if (void) MASKED_NOTHROW() : base() {}
	oenum_iterator_if (enum_t *pIEnum, pred p) MASKED_NOTHROW() : base(pIEnum) {}
	oenum_iterator_if (IUnknown *pIUnk) MASKED_THROW(_com_error) : base(pIUnk) {}	// throws hr
	oenum_iterator_if (const self &iter) MASKED_NOTHROW() : base(iter.enumerator) {}

    self& operator= (const T& value) MASKED_NOTHROW() 
		{ if (pred()(value)) enumerator -> AddItem (value); return *this; }
	self& operator * (void) MASKED_NOTHROW() { return *this; }
	self& operator++ (void)	MASKED_NOTHROW() { return *this; }
	self operator++ (int) MASKED_NOTHROW() { return *this;	}
};

///////////////////////////////////////////////////////////////////////////////
// Makros, die für einen vorgegebenen Enumerator einen OutputIterator definiert
//
#define DefineEnumOutputIterator(Type)	\
	typedef oenum_iterator<Type, __CIID<&__uuidof(IEnum##Type)> > OutEnum##Type;
#define DefineEnumOutputIterator2(Type,IID)	\
	typedef oenum_iterator<Type, __CIID<&IID> > OutEnum##Type;

#define DefineEnumOutputIteratorIf(Type,Pred)	\
	typedef oenum_iterator_if<Type, __CIID<&__uuidof(IEnum##Type)>, Pred> OutEnumIf##Type;
#define DefineEnumOutputIteratorIf2(Type,Pred,IID)	\
	typedef oenum_iterator_if<Type, __CIID<&IID>, Pred> OutEnumIf##Type;

#endif // _MSC_VER < 1100

#endif // _ITERENUM_H


