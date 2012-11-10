///////////////////////////////////////////////////////////////////////////
// @doc
// @module GenObjectMap.h | Declaration of the <c CGenObjectMap> class
// Eine allgemeine Klasse zur Zuordnung von Handles (long's) zu
// Objekten (IUnknown's)

#if !defined(_GENOBJECTMAP_H__4BCCE405_ACEC_11D1_8591_00600875138A__INCLUDED_)
#define _GENOBJECTMAP_H__4BCCE405_ACEC_11D1_8591_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ospace/thread.h>	// semaphore

#include "resource.h"       // main symbols
#include "TRiASDBGuids.h"
#include "FindInMapOrCreateObject.h"
#include "TRiASDBEngine.h"

/////////////////////////////////////////////////////////////////////////////
// Klasse, die durch CGenObjectMap gehalten wird
// Die in dieser Klasse enthaltenen IUnknown's werden u.U. nicht gehalten (_kein_ AddRef),
// d.h. die Objekt sind dann selbst zuständig, sich aus dieser Map zu entfernen.
class CGenObjectMapEntry
{
public:
	typedef CComObjectThreadModel::AutoCriticalSection _CritSec;

private:
	IUnknown *m_pIUnk;		// festgehaltenes Objekt
	ULONG m_uRefCnt;		// Anzahl der Referenzen auf dieses Objekt
	bool m_fAddRef;			// ist pIUnk AddRefed ?
	INT_PTR m_lHandle;		// OriginalHandle des Objektes in der GeoDB

protected:
	void AddRefUnknown(bool fAddRef) const 
		{ if (fAddRef && NULL != m_pIUnk) m_pIUnk -> AddRef();}
	void ReleaseUnknown() 
		{ if (m_fAddRef && NULL != m_pIUnk) m_pIUnk -> Release(); }

public:
	DECLARE_ONE_SIZE_PRIVATE_HEAP()

	CGenObjectMapEntry (IUnknown *pIUnk, INT_PTR lHandle, bool fAddRef = false)
		: m_pIUnk(pIUnk), m_uRefCnt(1), m_fAddRef(fAddRef), m_lHandle(lHandle)
	{
		AddRefUnknown(fAddRef); 
	}
	CGenObjectMapEntry (const CGenObjectMapEntry &rhs)
		: m_pIUnk(rhs.GetObject(rhs.KeepsAlive())), 
		  m_uRefCnt(rhs.GetRefCnt()), 
		  m_fAddRef(rhs.KeepsAlive()),
		  m_lHandle(rhs.Handle())
	{
	}
	~CGenObjectMapEntry ()
	{
		ReleaseUnknown(); 
	}
	CGenObjectMapEntry &operator= (const CGenObjectMapEntry &rhs)
	{
		if (&rhs != this) {
			ReleaseUnknown();
			m_pIUnk = rhs.GetObject(rhs.KeepsAlive()); 
			m_uRefCnt = rhs.GetRefCnt();
			m_fAddRef = rhs.KeepsAlive();
		}
		return *this;
	}

	ULONG AddRef() { return ++m_uRefCnt; }
	ULONG Release() { return --m_uRefCnt; }

	IUnknown *GetObject (bool fAddRef = true) const 
	{
		AddRefUnknown(fAddRef);
		return m_pIUnk;
	}
	ULONG GetRefCnt() const { return m_uRefCnt; }
	bool KeepsAlive() const { return m_fAddRef; }
	INT_PTR Handle() const { return m_lHandle; }
};

/////////////////////////////////////////////////////////////////////////////
// CGenObjectMap
class ATL_NO_VTABLE CGenObjectMap : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CReportErrorComCoClass<CGenObjectMap, &CLSID_GenObjectMap, &IID_ITRiASObjectHandleMap>, 
	public ITRiASPropertyCallback, 
	public IObjectWithName,
	public IDispatchImpl<ITRiASObjectHandleMap, &IID_ITRiASObjectHandleMap, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	typedef map<INT_PTR, CGenObjectMapEntry *, less<INT_PTR> > CObjectMap; 
	typedef map<INT_PTR, INT_PTR, less<INT_PTR> > CGeoHandleMap;

	CGenObjectMap()
		: m_CookieHolder(0), m_bstrName(g_cbNil)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CGenObjectMap)
	DECLARE_REGISTRY_RESOURCEID(IDR_GENOBJECTMAP)
	DECLARE_NOT_AGGREGATABLE(CGenObjectMap)
//	DECLARE_NO_REGISTRY()

	BEGIN_COM_MAP(CGenObjectMap)
		COM_INTERFACE_ENTRY(ITRiASObjectHandleMap)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ITRiASPropertyCallback)
		COM_INTERFACE_ENTRY(IObjectWithName)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	void FinalRelease()
	{
		DeleteCookieHolder();
		_ASSERTE(0 == m_CookieHolder);	// muß bereits abgemeldet sein
	}

protected:
// operators
	HRESULT InitCookieHolder()
	{
		_ASSERTE(0 == m_CookieHolder);		// nur einmal rufen
		_ASSERTE(NULL != g_pDBEngine);
		return g_pDBEngine -> InitCookieHolder(m_bstrName, (INT_PTR)0xE0000000L, &m_CookieHolder);
	}
	void DeleteCookieHolder()
	{
		if (NULL != g_pDBEngine) {
			_ASSERTE(0 != m_CookieHolder);		// muß initialisiert sein
			g_pDBEngine -> DeleteCookieHolder(m_CookieHolder);
			m_CookieHolder = 0L;
		}
	}
	INT_PTR GetNextCookie()
	{
		_ASSERTE(0 != m_CookieHolder);		// muß initialisiert sein
		_ASSERTE(NULL != g_pDBEngine);
		return g_pDBEngine -> GetNextCookie (m_CookieHolder);
	}

// ITRiASObjectHandleMap
public:
	STDMETHOD(ShutDown)();
	STDMETHOD(RemoveObject)(/*[in]*/ INT_PTR Handle, /*in, optional, defaultvalue()]*/ OBJECTMAPMODE Mode);
	STDMETHOD(GetObject)(/*[in]*/ INT_PTR Handle, /*[out, retval]*/ IUnknown **Object);
	STDMETHOD(GetObjectEx)(/*[in]*/ INT_PTR Handle, /*in, optional, defaultvalue()]*/ OBJECTMAPMODE Mode, /*[out, retval]*/ IUnknown **Object);
	STDMETHOD(GetObjectHandle)(/*[in]*/ VARIANT ObjName, /*[in]*/ IUnknown *Object, /*[in]*/ OBJECTMAPMODE rgMode, /*[out, retval]*/ INT_PTR *Handle);

// IObjectWithName
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);

// ITRiASPropertyCallback
	STDMETHOD(PutValue)(/*[in]*/ BSTR Name, VARIANT newVal);
	STDMETHOD(GetValue)(/*[in]*/ BSTR Name, VARIANT *pVal);
	STDMETHOD(PutType)(/*[in]*/ BSTR Name, PROPERTY_TYPE newVal);
	STDMETHOD(GetType)(/*[in]*/ BSTR Name, PROPERTY_TYPE *pVal);
	STDMETHOD(GetValueAndType)(/*[in]*/ BSTR Name, /*[out]*/ VARIANT *pVal, /*[out]*/ PROPERTY_TYPE *pType);
	STDMETHOD(PutValueAndType)(/*[in]*/ BSTR Name, /*[in]*/ VARIANT Val, /*[in]*/ PROPERTY_TYPE Type);
	STDMETHOD(Refresh)(/*[in]*/ BSTR Name);

protected:
// Helperklassen fürs automatische freigeben eines lock's
	class CReadLock
	{
	private:
		os_read_write_semaphore &m_rSem;

	public:
		CReadLock (os_read_write_semaphore &rSem)
			: m_rSem(rSem) { m_rSem.read_lock(); }
		~CReadLock() { m_rSem.read_unlock(); }
	};
	class CWriteLock
	{
	private:
		os_read_write_semaphore &m_rSem;

	public:
		CWriteLock (os_read_write_semaphore &rSem)
			: m_rSem(rSem) { m_rSem.write_lock(); }
		~CWriteLock() { m_rSem.write_unlock(); }
	};

	HRESULT RemoveIfApplicable (OBJECTMAPMODE rgMode, CObjectMap::iterator it, bool fRemoveFromDBMap);

private:
	os_read_write_semaphore m_sem;

	CObjectMap m_Map;
	CGeoHandleMap m_HandleMap;

	CComBSTR m_bstrName;			// CookieHolder-support
	INT_PTR m_CookieHolder;
};

#endif // !defined(_GENOBJECTMAP_H__4BCCE405_ACEC_11D1_8591_00600875138A__INCLUDED_)
