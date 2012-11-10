// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/26/1998 12:13:22 PM
//
// @doc
// @module PerfData.h | Declaration of the <c CPerfData> class

#if !defined(_PERFDATA_H__8FE6106A_9A8D_11D2_9F08_006008447800__INCLUDED_)
#define _PERFDATA_H__8FE6106A_9A8D_11D2_9F08_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols
#include "PerfObjects.h"

#include <pshpack8.h>

///////////////////////////////////////////////////////////////////////////////
// Struktur des SharedMemFiles
#define MAX_SIZEOF_INSTANCE_NAME    _MAX_PATH+1
#define MAX_SIZEOF_DATA_NAME		33

// sonstige Konstanten
#define SHARED_MEMORY_OBJECT_NAME   (TEXT("TRiAS_PERF_DATA"))
#define SHARED_MEMORY_MUTEX_NAME    (TEXT("TRiAS_PERF_DATA_MUTEX"))
#define SHARED_MEMORY_MUTEX_TIMEOUT ((DWORD)1000L)
#define SHARED_MEMORY_ITEM_COUNT    10		// 10 gleichzeitige Applikationen
#define SHARED_MEMORY_ITEM_SIZE		16484	// erstmal 16kByte als Maximum annehmen

#define SHARED_MEMORY_OBJECT_SIZE   (sizeof(APPMEM_DATA_HEADER) + (SHARED_MEMORY_ITEM_COUNT * (SHARED_MEMORY_ITEM_SIZE + sizeof(APPMEM_INSTANCE))))

typedef struct _APPMEM_DATA_HEADER {
    DWORD dwInstanceCount;			// number of entries In Use
    DWORD dwFirstInUseOffset;		// offset from mem base
    DWORD dwFirstFreeOffset;		// offset from mem base
	DWORD dwReserved;				// protect against misalignment
} APPMEM_DATA_HEADER, *PAPPMEM_DATA_HEADER;

typedef struct _APPMEM_INSTANCE {
	DWORD dwOffsetOfNext;			// offset from mem base to next item in list
	DWORD dwProcessId;				// id of process using this instance
	WCHAR wcszInstanceName[MAX_SIZEOF_INSTANCE_NAME];	// SZ instance name
	WCHAR wcszDataName[MAX_SIZEOF_DATA_NAME];			// SZ data name
	ULONG ulObjectCount;			// count of object definitions
	DWORD dwSpaceNeeded;			// Gesamtgröße des genutzten Speichers (für alle Objekte)
	union {
		double dDummy;				// protect against misalignment
		BYTE bytePerfData[SHARED_MEMORY_ITEM_SIZE];		// ab hier die eigentlichen Daten (müssen auf 8-Byte Grenze ausgerichtet sein)
	};
} APPMEM_INSTANCE, *PAPPMEM_INSTANCE;

#define FIRST_FREE(base)    ((PAPPMEM_INSTANCE)((LPBYTE)(base) + ((PAPPMEM_DATA_HEADER)(base))->dwFirstFreeOffset))
#define FIRST_INUSE(base)   ((PAPPMEM_INSTANCE)((LPBYTE)(base) + ((PAPPMEM_DATA_HEADER)(base))->dwFirstInUseOffset))
#define APPMEM_INST(base, offset)   ((PAPPMEM_INSTANCE)((LPBYTE)(base) + (DWORD)(offset)))

#include <poppack.h>

LONG GetSharedMemoryDataHeader (HANDLE *phAppMemSharedMemory, HANDLE *phAppMemMutex, APPMEM_DATA_HEADER **ppDataHeader, BOOL bReadOnlyAccess);
BOOL ReleaseSharedMemory(HANDLE *phAppMemSharedMemory, HANDLE *phAppMemMutex, APPMEM_DATA_HEADER **ppDataHeader, APPMEM_INSTANCE **ppAppData);

/////////////////////////////////////////////////////////////////////////////
// CPerfContext
IMPLEMENT_CLASSFACTORY_NAMED_SINGLETON(CPerfContext);

class ATL_NO_VTABLE CPerfContext : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CPerfContext, &CLSID_PerfContext>,
	public ISupportErrorInfo,
	public IPersistMemory,
	public IPerfContextHelper,
	public IDispatchImpl<IPerfContext, &IID_IPerfContext, &LIBID_PerfMon>
{
public:
	CPerfContext() :
		m_Locale(LOCALE_NEUTRAL), m_Mode(PERFMONSTARTMODE_Unknown), m_fIsDirty(false), 
		m_pDataHeader(NULL), m_pAppData(NULL),
		m_hAppMemSharedMemory(NULL), m_hAppMemMutex(NULL),
		m_ulIndex(0), m_BaseNameIndex(0), m_BaseHelpIndex(1)
	{
	}

	DECLARE_CLASSFACTORY_NAMED_SINGLETON(CPerfContext)
	DECLARE_GET_OBJECT_NAME()
//	DECLARE_NO_REGISTRY()

	DECLARE_REGISTRY_RESOURCEID(IDR_PERFDATA)
//	DECLARE_CLASSFACTORY_SINGLETON(CPerfContext)
//	DECLARE_NOT_AGGREGATABLE(CPerfContext)

	BEGIN_COM_MAP(CPerfContext)
		COM_INTERFACE_ENTRY(IPerfContext)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IPerfContextHelper)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IPersistMemory)
		COM_INTERFACE_ENTRY2(IPersist, IPersistMemory)
	END_COM_MAP()

	HRESULT FinalConstruct()
	{
		return m_Objs.LocalCreateInstance (CLSID_PerfObjects);
	}
	void FinalRelease()
	{
	}

// IPersist
	STDMETHOD(GetClassID)(CLSID *pClassID);

// IPersistMemory
	STDMETHOD(IsDirty)();
	STDMETHOD(Load)(void *pvMem, ULONG cbSize);
	STDMETHOD(Save)(void *pvMem, BOOL fClearDirty, ULONG cbSize);
	STDMETHOD(GetSizeMax)(ULONG *pcbSize);
	STDMETHOD(InitNew)();

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IPerfContextHelper
	DECLARE_PROPERTY_GET(BaseHelpIndex, ULONG);
	DECLARE_PROPERTY_GET(BaseNameIndex, ULONG);

	STDMETHOD(UnlockMemory)();
	STDMETHOD(LockMemory)(/*[in]*/ DWORD dwTimeOut);
	STDMETHOD(RegeneratePerfData)();
	STDMETHOD(GetNextBaseIndex)(/*[out, retval]*/ ULONG *pVal);

// IPerfContext
public:
	STDMETHOD(UpdatePerfData)();
	DECLARE_PROPERTY_GET(Mode, PERFMONSTARTMODE);
	DECLARE_PROPERTY_ACCESS(Locale, LCID);
	STDMETHOD(get_Objects)(/*[out, retval]*/ IPerfObjects **pVal);

	STDMETHOD(AddPerformanceObject)(/*[in]*/ BSTR Name, /*[in]*/ BSTR Desc, /*[in]*/ BSTR HelpText, /*[out, retval]*/ IPerfObject **ppIObj);
	STDMETHOD(UnRegister)();
	STDMETHOD(Register)();
	STDMETHOD(Stop)();
	STDMETHOD(Start)(/*[in]*/ PERFMONSTARTMODE rgMode);

protected:
	BOOL InitSharedMemory (LPCOLESTR pcName);
	BOOL ReleaseSharedMemory();
	LONG GetSharedMemoryDataHeader (BOOL bReadOnlyAccess);

	HRESULT GenerateIniFile (os_string &rStrIniName, os_string &rStrSymName);

private:
	WPerfObjects m_Objs;
	LCID m_Locale;
	PERFMONSTARTMODE m_Mode;
	bool m_fIsDirty;

// shared memory data
	struct _APPMEM_DATA_HEADER *m_pDataHeader;
	struct _APPMEM_INSTANCE *m_pAppData;
	HANDLE  m_hAppMemSharedMemory;		// Handle of counter Shared Memory
	HANDLE  m_hAppMemMutex;				// sync mutex for memory
	CComBSTR m_bstrName;

	ULONG m_ulIndex;
	ULONG m_BaseNameIndex;
	ULONG m_BaseHelpIndex;
};

///////////////////////////////////////////////////////////////////////////////
// Helperklasse für Verwaltung des Speicherzugriffs
class CLockMutex
{
public:
	CLockMutex (HANDLE hMtx, DWORD dwTimeOut = SHARED_MEMORY_MUTEX_TIMEOUT) 
		: m_hMtx(hMtx), m_lStatus(ERROR_SUCCESS)
	{
		if (NULL != m_hMtx) 
			m_lStatus = ::WaitForSingleObject (m_hMtx, dwTimeOut);
	}
	~CLockMutex ()
	{
		if (ERROR_SUCCESS == m_lStatus && NULL != m_hMtx)
			::ReleaseMutex (m_hMtx);
	}

	LONG Status() { return m_lStatus; }

private:
	HANDLE m_hMtx;
	LONG m_lStatus;
};

#endif // !defined(_PERFDATA_H__8FE6106A_9A8D_11D2_9F08_006008447800__INCLUDED_)
