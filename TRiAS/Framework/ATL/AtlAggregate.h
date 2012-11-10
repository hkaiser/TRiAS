///////////////////////////////////////////////////////////////////////////////
// @doc 
// @module AtlAggregate.h | Spezielle Version der Aggregierungstemplates

#if !defined(_ATLAGGREGATE_H__1009B803_C8A8_11D1_85DA_00600875138A__INCLUDED_)
#define _ATLAGGREGATE_H__1009B803_C8A8_11D1_85DA_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// BEGIN_COM_MAP_EX is reqired if you want to use COM_INTERFACE_ENTRY_AGGREGATE_EX()
#define BEGIN_COM_MAP_EX(x) public: \
	static HRESULT WINAPI _DelegateEx(void* pv, REFIID iid, void** ppvObject, DWORD dw)\
	{\
		HRESULT hRes = E_POINTER;\
		IUnknown* p = *(IUnknown**)((DWORD)pv + dw);\
		if (p != NULL) hRes = p->QueryInterface(iid, ppvObject);\
		return hRes;\
	}\
	BEGIN_COM_MAP(x)

////////////////////////////////////////////////////////////////////////////////
// COM_INTERFACE_ENTRY_AGGREGATE_EX() et.al. must be used in conjunction with
// BEGIN_COM_MAP_EX()
#define COM_INTERFACE_ENTRY_AGGREGATE_EX(iid, punk)\
	{&iid,\
	(DWORD)offsetof(_ComMapClass, punk),\
	_DelegateEx},

#define COM_INTERFACE_ENTRY_AGGREGATE_BLIND_EX(punk)\
	{NULL,\
	(DWORD)offsetof(_ComMapClass, punk),\
	_DelegateEx},

/////////////////////////////////////////////////////////////////////////////
// 
template <class contained> class CComAggObjectEx;	// forward reference only

template <class Base> //Base must be derived from CComObjectRoot
class CComContainedObjectEx : public Base
{
public:
	typedef Base _BaseClass;

	CComContainedObjectEx(void* pv) 
	{
		m_pOuterUnknown = (IUnknown*)pv;
	}

	STDMETHOD_(ULONG, AddRef)() {return OuterAddRef();}
	STDMETHOD_(ULONG, Release)() {return OuterRelease();}
	STDMETHOD(QueryInterface)(REFIID iid, void ** ppvObject)
	{
	HRESULT hr = OuterQueryInterface(iid, ppvObject);

		if (E_POINTER == hr)	// Aggregate noch nicht fertig initialisiert
			hr = GetInnerUnknown() -> QueryInterface(iid, ppvObject);
		return hr;
	}

// GetControllingUnknown may be virtual if the Base class has declared
// DECLARE_GET_CONTROLLING_UNKNOWN()
	IUnknown* GetControllingUnknown() { return m_pOuterUnknown; }
	IUnknown* GetInnerUnknown()	{ return (CComAggObjectEx<Base> *)((BYTE *)this - offsetof(CComAggObjectEx<Base>, m_contained)); }
};

//contained is the user's class that derives from CComObjectRoot and whatever
//interfaces the user wants to support on the object
template <class contained>
class CComAggObjectEx :
	public IUnknown,
	public CComObjectRootEx< contained::_ThreadModel::ThreadModelNoCS >
{
public:
	typedef contained _BaseClass;
	CComAggObjectEx(void* pv) : m_contained(pv)
	{
		_Module.Lock();
	}
	//If you get a message that this call is ambiguous then you need to
	// override it in your class and call each base class' version of this
	HRESULT FinalConstruct()
	{
		CComObjectRootEx<contained::_ThreadModel::ThreadModelNoCS>::FinalConstruct();
		return m_contained.FinalConstruct();
	}
	void FinalRelease()
	{
		CComObjectRootEx<contained::_ThreadModel::ThreadModelNoCS>::FinalRelease();
		m_contained.FinalRelease();
	}
	// Set refcount to 1 to protect destruction
	~CComAggObjectEx()
	{
		m_dwRef = 1L;
		FinalRelease();
		_Module.Unlock();
	}

	STDMETHOD_(ULONG, AddRef)() {return InternalAddRef();}
	STDMETHOD_(ULONG, Release)()
	{
		ULONG l = InternalRelease();
		if (l == 0)
			delete this;
		return l;
	}
	STDMETHOD(QueryInterface)(REFIID iid, void ** ppvObject)
	{
		HRESULT hRes = S_OK;
		if (InlineIsEqualUnknown(iid))
		{
			*ppvObject = (void*)(IUnknown*)this;
			AddRef();
		}
		else
			hRes = m_contained._InternalQueryInterface(iid, ppvObject);
		return hRes;
	}
	CComContainedObjectEx<contained> m_contained;
};

#define DECLARE_AGGREGATABLE_EX(x) public:\
	typedef CComCreator2< CComCreator< CComObject< x > >, CComCreator< CComAggObjectEx< x > > > _CreatorClass;
#define DECLARE_ONLY_AGGREGATABLE_EX(x) public:\
	typedef CComCreator2< CComFailCreator<E_FAIL>, CComCreator< CComAggObjectEx< x > > > _CreatorClass;

#endif // !defined(_ATLAGGREGATE_H__1009B803_C8A8_11D1_85DA_00600875138A__INCLUDED_)
