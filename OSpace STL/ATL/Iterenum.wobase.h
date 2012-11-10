// InputIterator on IEnumXXX --------------------------------------------------
// File: ITERENUM.H

#if !defined(_ITERENUM_WOBASE_H)
#define _ITERENUM_WOBASE_H

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
// *** IUnknown methods
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS) PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;
	
// *** IEnum<T> methods
	STDMETHOD(Next) (THIS_ ULONG celt, T *rgelt, ULONG *pceltFetched) PURE;
	STDMETHOD(Skip) (THIS_ ULONG celt) PURE;
	STDMETHOD(Reset) (THIS) PURE;
	STDMETHOD(Clone) (THIS_ IEnum<T> ** ppenum) PURE;

// *** IEnumEx<T> methods
	STDMETHOD_(ULONG, Count) (void) PURE;
	STDMETHOD(AddItem) (THIS_ const T &item) PURE;
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
class CSyncEnum 
{
private:
	CComThreadModel::ObjectCriticalSection m_cs;

public:
		CSyncEnum () { m_cs.Init(); }
		~CSyncEnum () { m_cs.Term(); }

	void Lock() { m_cs.Lock(); }
	void Unlock() { m_cs.Unlock(); }
};

class CLockEnum {
private:
	CSyncEnum &m_rSync;

public:
		CLockEnum (CSyncEnum &rSync) : m_rSync(rSync) { rSync.Lock(); }
		~CLockEnum () { m_rSync.Unlock(); }
};

#else

// die neue ATL enthält alles was wir brauchen
class CLockEnum {
private:
	CComObjectThreadModel::AutoCriticalSection &m_rSync;

public:
		CLockEnum (CComObjectThreadModel::AutoCriticalSection &rSync) : m_rSync(rSync) { rSync.Lock(); }
		~CLockEnum () { m_rSync.Unlock(); }
};

#endif 

///////////////////////////////////////////////////////////////////////////////
// Implementation des geforderten IEnum<XXX>
//
// Als TemplateParameter müssen gegeben sein:
//		T:			Datentyp der Enumeriert werden soll (z.B. LONG)
//		piid:		Pointer auf zugehörigen GUID (z.B. &IID_IEnumLONG)
//		C:			STL-Container, auf dessen Grundlage der Enumerator realisiert
//					wird (set, multiset, vector, list oder deque)
//					z.B. vector<LONG>
//
// Diese Klasse kann wie ein normaler Enumerator verwendet werden.
//
template<class T, class C>
class __EnumeratorBase : public IEnum<T>
{
public:
	typedef C cont_t;
	typedef T item_t;
	typedef cont_t::iterator iterator;
	typedef cont_t::const_iterator const_iterator;
	typedef __EnumeratorBase<T, C> self;
	typedef __EnumeratorBase<T, C> base_self;
#if _ATL_VER < 0x0110
	typedef CSyncEnum sync_t;
#else
	typedef CComObjectThreadModel::AutoCriticalSection sync_t;
#endif

protected:
	cont_t m_data;
	iterator m_itcur;
	sync_t m_sync;
	bool m_fIsDirty;

	bool eoi_reached (void) throw() { return m_itcur == m_data.end(); }
	bool isempty (void) throw() { return m_data.size() == 0; }
	bool isdirty (void) throw() { return m_fIsDirty ? true : false; }
	void setdirty (bool fFlag) throw() { m_fIsDirty = fFlag ? true : false; }

public:
		__EnumeratorBase (void) throw() { setdirty(false); Reset(); }
		__EnumeratorBase (const self & x_) throw() : m_sync(), m_data(x_.m_data)
			{	// clones target
			CLockEnum SyncMe(m_sync);

				Reset();
				if (!isempty() && !const_cast<self &>(x_).eoi_reached()) {
				const_iterator it = m_data.begin();

					while (!(it == m_data.end()) && !(*it == *(x_.m_itcur)))
						it++;
				} 
				setdirty(true);
			}
		virtual ~__EnumeratorBase (void) throw() {}
		virtual base_self *Construct (void) = 0;

// *** IEnum<X> methods
	STDMETHODIMP Next (ULONG celt, T *rgelt, ULONG *pceltFetched) throw() 
		{
		CLockEnum SyncMe(m_sync);
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
	STDMETHODIMP Skip (ULONG dwSkip) throw() 
		{
			if (0 == dwSkip) return NOERROR;

		CLockEnum SyncMe(m_sync);
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
	STDMETHODIMP Reset (void) throw() 
		{
			m_itcur = isempty() ? m_data.end() : m_data.begin();
			return NOERROR;
		}
	STDMETHODIMP Clone (IEnum<T> **ppenum) throw() 
		{
		CLockEnum SyncMe(m_sync);

			*ppenum = NULL;		// für alle Fälle

		base_self *pEnum = Construct();		// Enumerator bilden (standalone)

			if (pEnum == NULL) return E_OUTOFMEMORY;
			*ppenum = pEnum;
			return NOERROR;
		}

// *** IEnumEx<X> methods
	STDMETHODIMP_(ULONG) Count (void) throw() { CLockEnum SyncMe(m_sync); return m_data.size(); }
	STDMETHODIMP AddItem (const T &item) throw() 
		{ CLockEnum SyncMe(m_sync); m_data.insert(m_data.end(), item); setdirty(true); return NOERROR; }
	STDMETHODIMP Clear (void) throw() 
		{ 
		CLockEnum SyncMe(m_sync);
		bool fEmpty = isempty();
		
			setdirty(true);
			m_data.erase (m_data.begin(), m_data.end()); 
			return fEmpty ? S_FALSE : NOERROR;
		}
};

///////////////////////////////////////////////////////////////////////////////
// Nicht Aggregierbarer Enumerator 
template<class T, class ID, class C>
class __Enumerator : public __EnumeratorBase<T, C>
{
protected:
	LONG m_dwRefCnt;

public:
	typedef __Enumerator<T, ID, C> self;

		__Enumerator (void) throw() : m_dwRefCnt(1) {}
		__Enumerator (const self & x_) throw() : m_dwRefCnt(1), base_self (x_) {}
		~__Enumerator (void) throw() {}
	
	base_self *Construct (void) throw() 
		{
		CLockEnum SyncMe(m_sync); 
		base_self *p = NULL; 
			
			ATLTRY(p = new self (*this)); 
			return p;
		}

// *** IUnknown methods
	STDMETHODIMP QueryInterface (REFIID riid, LPVOID *ppvObj) throw() 
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
	STDMETHODIMP_(ULONG) AddRef (void) throw() 
		{ return CComObjectThreadModel::Increment(&m_dwRefCnt); }
	STDMETHODIMP_(ULONG) Release (void) throw() 
		{ if (CComObjectThreadModel::Decrement(&m_dwRefCnt) == 0) { delete this; return 0L; } return m_dwRefCnt; }
#endif 

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
template<class T, class ID, class C>
void os_write (os_bstream &, const __Enumerator<T, ID, C> &);

template<class T, class ID, class C>
void os_read (os_bstream &, __Enumerator<T, ID, C> &);

OS_POLY_CLASS_T3(__Enumerator);
OS_STREAM_OPERATORS_T3(__Enumerator);
#endif // OS_NO_STREAM_SUPPORT

///////////////////////////////////////////////////////////////////////////////
// Aggregierbarer Enumerator 
template<class T, class ID, class C>
class __AggEnumerator : public __EnumeratorBase<T, C>
{
protected:
	WUnknown IUnk;		// controlling unknown

public:
	typedef __AggEnumerator<T, ID, C> self;

		__AggEnumerator (IUnknown *pIUnk) throw() : IUnk(pIUnk) {}
		__AggEnumerator (const self & x_) throw() : IUnk(_x.IUnk), base_self (x_) {}
		~__AggEnumerator (void) throw() {}
	
	base_self *Construct (void) throw() 
		{
		CLockEnum SyncMe(m_sync); 
		base_self *p = NULL; 
			
			ATLTRY(p = new self (*this)); 
			return p;
		}

// *** IUnknown methods (delegating IUnknown)
	STDMETHODIMP QueryInterface (REFIID riid, LPVOID *ppvObj) throw() 
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
template<class T, class ID, class C>
void os_write (os_bstream &, const __AggEnumerator<T, ID, C> &);

template<class T, class ID, class C>
void os_read (os_bstream &, __AggEnumerator<T, ID, C> &);

OS_POLY_CLASS_T3(__AggEnumerator);
OS_STREAM_OPERATORS_T3(__AggEnumerator);
#endif // OS_NO_STREAM_SUPPORT

///////////////////////////////////////////////////////////////////////////////
// Makros, welches StandardImplementationen für einen Enumerator definieren
//
// Normaler (nicht sortierender) Enumerator: über list<Type> --> NEnumXXX
//
#define DefineEnumerator(Type)					\
	DefineEnumIIDWrapper(Type);					\
	typedef __Enumerator<Type, CIID_##Type##Enum, list<Type> > NEnum##Type;
#define DefineEnumerator2(Type,IID)				\
	DefineEnumIIDWrapper2(Type,IID);			\
	typedef __Enumerator<Type, CIID_##Type##Enum, list<Type> > NEnum##Type;

#define DefineEnumeratorAggr(Type)				\
	DefineEnumIIDWrapper(Type);					\
	typedef __AggEnumerator<Type, CIID_##Type##Enum, list<Type> > NEnumAggr##Type;
#define DefineEnumeratorAggr2(Type,IID)			\
	DefineEnumIIDWrapper2(Type,IID);			\
	typedef __AggEnumerator<Type, CIID_##Type##Enum, list<Type> > NEnumAggr##Type;

//
// Sortierender Enumerator:	über set<Type, less<Type> > --> SEnumXXX
//
#define DefineSortingEnumerator(Type)			\
	DefineEnumIIDWrapper(Type);					\
	typedef __Enumerator<Type,CIID_##Type##Enum,set<Type,less<Type> > > SEnum##Type
#define DefineSortingEnumerator2(Type,IID)		\
	DefineEnumIIDWrapper2(Type,IID);			\
	typedef __Enumerator<Type,CIID_##Type##Enum,set<Type,less<Type> > > SEnum##Type

#define DefineSortingEnumeratorAggr(Type)		\
	DefineEnumIIDWrapper(Type);					\
	typedef __AggEnumerator<Type,CIID_##Type##Enum,set<Type,less<Type> > > SEnumAggr##Type
#define DefineSortingEnumeratorAggr2(Type,IID)	\
	DefineEnumIIDWrapper2(Type,IID);			\
	typedef __AggEnumerator<Type,CIID_##Type##Enum,set<Type,less<Type> > > SEnumAggr##Type

//
// InterfaceWrapper für einen TemplateEnumerator
//
#define DefineSmartEnumerator(Type)		\
	typedef __Interface<IEnum<Type>, CIID_##Type##Enum, CComPtr<IEnum<Type> > > WEnum##Type;

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
	void read (void) throw() 
		{
			value.~T();			// vorheriges Objekt explizit zerlegen
			end_marker = (S_OK != enumerator -> Next (1, &value, NULL)) ? true : false; 
		}

public:
	ienum_iterator (void) throw() : enumerator(), end_marker(true) {}
	ienum_iterator (enum_t *pIEnum) throw() : enumerator(pIEnum), end_marker(true) 
		{ enumerator->Reset(); read(); }
	ienum_iterator (IUnknown *pIUnk) throw(_com_error) : enumerator(pIUnk), end_marker(true)	// throws HRESULT
		{ enumerator->Reset(); read(); }

	const T & operator * (void) const throw() { return value; }

	self& operator++ (void)	throw() { read(); return *this; }
	self operator++ (int) throw() { self tmp = *this;	read();	return tmp;	}

	bool operator == (const self & x_) const throw() 
		{ 
			return enumerator == x_.enumerator && end_marker == x_.end_marker ||
				   end_marker == true && x_.end_marker == true;
		}
	bool operator != (const self & x_) const throw() 
		{ return !(*this == x_); }
};

///////////////////////////////////////////////////////////////////////////////
// Makro, das für einen vorgegebenen Enumerator einen InputIterator definiert
//
#define DefineEnumInputIterator(Type)		\
	typedef ienum_iterator<Type, CIID_##Type##Enum, ptrdiff_t> InEnum##Type;

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
	oenum_iterator (void) throw() : enumerator() {}
	oenum_iterator (enum_t *pIEnum) throw() : enumerator(pIEnum) {}
	oenum_iterator (IUnknown *pIUnk) throw(_com_error) : enumerator(pIUnk) {}	// throws hr
	oenum_iterator (const self &iter) throw() : enumerator(iter.enumerator) {}

    self& operator = (const T& value) throw() 
		{ enumerator -> AddItem (value); return *this; }
	self& operator * (void) throw() { return *this; }
	self& operator++ (void)	throw() { return *this; }
	self operator++ (int) throw() { return *this;	}
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
	oenum_iterator_if (void) throw() : base() {}
	oenum_iterator_if (enum_t *pIEnum, pred p) throw() : base(pIEnum) {}
	oenum_iterator_if (IUnknown *pIUnk) throw(_com_error) : base(pIUnk) {}	// throws hr
	oenum_iterator_if (const self &iter) throw() : base(iter.enumerator) {}

    self& operator= (const T& value) throw() 
		{ if (pred()(value)) enumerator -> AddItem (value); return *this; }
	self& operator * (void) throw() { return *this; }
	self& operator++ (void)	throw() { return *this; }
	self operator++ (int) throw() { return *this;	}
};

///////////////////////////////////////////////////////////////////////////////
// Makro, das für einen vorgegebenen Enumerator einen OutputIterator definiert
//
#define DefineEnumOutputIterator(Type)	\
	typedef oenum_iterator<Type, CIID_##Type##Enum> OutEnum##Type;
#define DefineEnumOutputIteratorIf(Type,Pred)	\
	typedef oenum_iterator_if<Type, CIID_##Type##Enum, Pred> OutEnumIf##Type;

#endif // _ITERENUM_WOBASE_H


