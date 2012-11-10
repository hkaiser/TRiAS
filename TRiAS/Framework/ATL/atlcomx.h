///////////////////////////////////////////////////////////////////////////
// @doc 
// @module atlcomx.h | Debug-HilfsMacros und Debug-HilfsKlaasen

#if !defined(_ATLCOMX_H__5425EF25_D5D6_11D1_85EF_00600875138A__INCLUDED_)
#define _ATLCOMX_H__5425EF25_D5D6_11D1_85EF_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __cplusplus
	#error ATL requires C++ compilation (use a .cpp suffix)
#endif

#ifndef __ATLBASE_H__
	#error atlcomx.h requires atlbase.h to be included first
#endif

#ifndef ATL_NO_NAMESPACE
namespace ATL
{
#endif

#if !defined(TEST_E_POINTER)
#if defined(_DEBUG)
#define TEST_E_POINTER(s,p) \
	do{ \
		if(NULL==(p)) { \
			AtlTrace("%s has bad pointer parameter.",s); return E_POINTER; \
		} \
	}while(0) \

#else
#define TEST_E_POINTER(s,p) \
	do{ \
		if(NULL==(p)) return E_POINTER; \
	}while(0) \

#endif // _DEBUG
#endif // TEST_E_POINTER

#if defined(_ATLX_DEBUG_REFCOUNT)

//////////////////////////////////////////////////////////////////////////////
// CComDebugRefCountObj for object level ref counting

class CComDebugRefCountObj
{
public:
	CComDebugRefCountObj()
	{
		m_nRef = 0;
	}

	~CComDebugRefCountObj()
	{
		_ASSERTE(m_nRef == 0);
	}
	long m_nRef;
};

#define _ATLX_DEBUG_ADDREF_RELEASE_IMPL(className) \
public:\
	CComDebugRefCountObj _ref;\
	ULONG InternalAddRef()\
	{\
		_ThreadModel::Increment(&_ref.m_nRef);\
		ATLTRACE(_T("%s(0x%lx) %d>\n"), #className, this, _ref.m_nRef);\
		return CComObjectRootEx<CComObjectThreadModel>::InternalAddRef();\
	}\
	ULONG InternalRelease()\
	{\
		_ThreadModel::Decrement(&_ref.m_nRef);\
		ATLTRACE(_T("%s(0x%lx) %d<\n"), #className, this, _ref.m_nRef);\
		return CComObjectRootEx<CComObjectThreadModel>::InternalRelease();\
	}

#else
#define _ATLX_DEBUG_ADDREF_RELEASE_IMPL(className) 
#endif // _ATLX_DEBUG_REFCOUNT

/////////////////////////////////////////////////////////////////////////////
//	BEGIN_COM_MAP_NOQI() leaves out the _InternalQueryInterface() function
//	Define this function in your class as shown below and add any extra functionality that you need
//	HRESULT _InternalQueryInterface(REFIID iid, void** ppvObject)
//	{return InternalQueryInterface(this, _GetEntries(), iid, ppvObject);}
#define BEGIN_COM_MAP_NOQI(x) public: \
	typedef x _ComMapClass; \
	static HRESULT WINAPI _Cache(void* pv, REFIID iid, void** ppvObject, DWORD dw)\
	{\
		_ComMapClass* p = (_ComMapClass*)pv;\
		p->Lock();\
		HRESULT hRes = CComObjectRootBase::_Cache(pv, iid, ppvObject, dw);\
		p->Unlock();\
		return hRes;\
	}\
	IUnknown* GetUnknown() \
	{ _ASSERTE(_GetEntries()[0].pFunc == _ATL_SIMPLEMAPENTRY); return (IUnknown*)((int)this+_GetEntries()->dw); } \
	const static _ATL_INTMAP_ENTRY* WINAPI _GetEntries() { \
	static const _ATL_INTMAP_ENTRY _entries[] = { DEBUG_QI_ENTRY(x)

/////////////////////////////////////////////////////////////////////////////
//	COM_INTERFACE_ENTRY_EX() does the same job as COM_INTERFACE_ENTRY(),
//	but it uses __uuidof() rather than the IID_ constant
#if _MSC_VER >= 1100
#define COM_INTERFACE_ENTRY_EX(x)\
	{&__uuidof(x), \
	offsetofclass(x, _ComMapClass), \
	_ATL_SIMPLEMAPENTRY},
#else
#define COM_INTERFACE_ENTRY_EX(x)	COM_INTERFACE_ENTRY(x)
#endif // _MSC_VER >= 1100

#ifndef ATL_NO_NAMESPACE
}; //namespace ATL
#endif

#endif // !defined(_ATLCOMX_H__5425EF25_D5D6_11D1_85EF_00600875138A__INCLUDED_)
