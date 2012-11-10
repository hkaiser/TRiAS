// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/26/1998 12:10:22 PM
//
// @doc
// @module PerfData.cpp | Implementation of the <c CPerfData> class

#include "stdafx.h"

#include <psapi.h>

#include <ospace/file/path.h>
#include <Com/PerfMonContext.h>

#include "MemCtrs.h"
#include "Wrapper.h"

#include "PerfData.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPerfContext

STDMETHODIMP CPerfContext::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPerfContext,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CPerfContext::GetClassID (CLSID *pClassID)
{
	if (NULL == pClassID) 
		return E_POINTER;

	*pClassID = GetObjectCLSID();
	return S_OK;
}

// IPersistMemory
STDMETHODIMP CPerfContext::IsDirty ()
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CPerfContext::Load (void *pvMem, ULONG cbSize)
{
	return E_NOTIMPL;
}

STDMETHODIMP CPerfContext::Save (void *pvMem, BOOL fClearDirty, ULONG cbSize)
{
// alle Objekte durchgehen und wegschreiben
	COM_TRY {
	CLockMutex Lock (m_hAppMemMutex);
	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(m_Objs -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, &v, NULL); /**/) {
			_ASSERTE(VT_DISPATCH == V_VT(&v));

		WPersistMemory PMObj (V_DISPATCH(&v));
		ULONG ulSize = 0;

			THROW_FAILED_HRESULT(PMObj -> GetSizeMax (&ulSize));
			if (ulSize > cbSize)
				return E_UNEXPECTED;
			THROW_FAILED_HRESULT(PMObj -> Save (pvMem, fClearDirty, ulSize));
			cbSize -= ulSize;		// verbleibender Platz
		}

	} COM_CATCH;

	_ASSERTE(0 == cbSize);
	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CPerfContext::GetSizeMax (ULONG *pcbSize)
{
// alle Objekte durchgehen und befragen
ULONG cbSize = 0L;

	*pcbSize = 0;
	COM_TRY {
	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(m_Objs -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, &v, NULL); /**/) {
			_ASSERTE(VT_DISPATCH == V_VT(&v));

		WPersistMemory PMObj (V_DISPATCH(&v));
		ULONG ulSize = 0;

			THROW_FAILED_HRESULT(PMObj -> GetSizeMax (&ulSize));
			cbSize += ulSize;		// benötigter Platz
		}

	} COM_CATCH;

	*pcbSize = cbSize;
	return S_OK;
}

STDMETHODIMP CPerfContext::InitNew()
{
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Interface properties

IMPLEMENT_PROPERTY_ACCESS(CPerfContext, Locale, LCID);
IMPLEMENT_PROPERTY_GET(CPerfContext, BaseNameIndex, ULONG);
IMPLEMENT_PROPERTY_GET(CPerfContext, BaseHelpIndex, ULONG);
IMPLEMENT_PROPERTY_GET(CPerfContext, Mode, PERFMONSTARTMODE);

STDMETHODIMP CPerfContext::get_Objects(IPerfObjects **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return E_POINTER;

WPerfObjects Objs (m_Objs);

	*pVal = Objs.detach();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Methods
STDMETHODIMP CPerfContext::Start(PERFMONSTARTMODE rgMode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// alles fertig initialisieren
	m_Mode = rgMode;
	m_BaseNameIndex = 0;
	m_BaseHelpIndex = 1;

	m_bstrName = GetObjectName();	// ContextBezeichner
	m_ulIndex = 0L;

	if (PERFMONSTARTMODE_Normal == m_Mode) {
	// StartIndex aus Registry lesen
	CRegKey key;

		USES_CONVERSION;
		if (ERROR_SUCCESS != key.Open (HKEY_LOCAL_MACHINE, TEXT("SYSTEM"), KEY_READ) ||
			ERROR_SUCCESS != key.Open (key, TEXT("CurrentControlSet"), KEY_READ) ||
			ERROR_SUCCESS != key.Open (key, TEXT("Services"), KEY_READ) ||
			ERROR_SUCCESS != key.Open (key, OLE2A(m_bstrName), KEY_READ) ||
			ERROR_SUCCESS != key.Open (key, TEXT("Performance"), KEY_READ))
		{
			return PERFMON_UNABLE_OPEN_DRIVER_KEY;
		}

	DWORD dwBaseName = 0;
	DWORD dwBaseHelp = 1;

		if (ERROR_SUCCESS != key.QueryValue (dwBaseName, TEXT("First Counter"))) 
			return PERFMON_UNABLE_READ_FIRST_COUNTER;
		if (ERROR_SUCCESS != key.QueryValue (dwBaseHelp, TEXT("First Help"))) 
			return PERFMON_UNABLE_READ_FIRST_HELP;

		m_BaseNameIndex = dwBaseName;
		m_BaseHelpIndex = dwBaseHelp;

	// shared memory initialisieren
		if (!InitSharedMemory(m_bstrName))
			return E_FAIL;
	} 
	else if (PERFMONSTARTMODE_Register == m_Mode) {
	// evtl. Shared memory freigeben, da lediglich registriert werden soll
		if (NULL != m_hAppMemSharedMemory)
			ReleaseSharedMemory();
	}
	return S_OK;
}

STDMETHODIMP CPerfContext::Stop()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// alle Objekte freigeben
	m_Objs.Assign(NULL);

// Speicher freigeben
	if (PERFMONSTARTMODE_Normal == m_Mode)
		ReleaseSharedMemory();

	m_Mode = PERFMONSTARTMODE_Unknown;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Registrieen der notwendigen Document-Keys
static _ATL_REGMAP_ENTRY regEntryMap[] = 
{
	{ L"APPNAME", NULL },
	{ NULL, NULL },		// EndeKennung
};

STDMETHODIMP CPerfContext::Register()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//	if (PERFMONSTARTMODE_Register != m_Mode)
//		return PERFMON_WRONG_STARTMODE;

	UnRegister();		// sicherheitshalber erstmal deregistrieren, evtl. Fehler ignorieren

// jetzt registrieren
	USES_CONVERSION;
	regEntryMap[0].szData = m_bstrName;
	RETURN_FAILED_HRESULT(_Module.UpdateRegistryFromResource(IDR_PERFMON, TRUE, regEntryMap));

// LinkageKey erzeugen
os_string strKey = os_string("SYSTEM\\CurrentControlSet\\Services\\") + OLE2A(m_bstrName) + "\\Linkage";
CRegKey key;
LONG lStatus = key.Open (HKEY_LOCAL_MACHINE, strKey.c_str());

	if (ERROR_SUCCESS != lStatus)
		return HRESULT_FROM_WIN32(lStatus);		//snh

	lStatus = RegSetValueEx (key, "Export", 0, REG_BINARY, (LPBYTE)(BSTR)m_bstrName, (m_bstrName.Length()*2)+1); 
	if (ERROR_SUCCESS != lStatus)
		return HRESULT_FROM_WIN32(lStatus);		// snh

// INI + Header erzeugen
os_string strIniName;
os_string strSymName;

	RETURN_FAILED_HRESULT(GenerateIniFile (strIniName, strSymName));

// lodctr ausführen
HINSTANCE hInst = ::ShellExecute (NULL, NULL, "lodctr", strIniName.c_str(), NULL, SW_HIDE);
char cbBuffer[_MAX_PATH];

	_ASSERTE(NULL != hInst);
	while (::GetModuleFileName (hInst, cbBuffer, sizeof(cbBuffer)) > 0)
		;	// warten, bis lodctr fertig ist

//	::DeleteFile(strIniName.c_str());
//	::DeleteFile(strSymName.c_str());
	return S_OK;
}

STDMETHODIMP CPerfContext::UnRegister()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
//	if (STARTMODE_UnRegister != m_Mode && STARTMODE_Register != m_Mode)
//		return PERFMON_WRONG_STARTMODE;

	USES_CONVERSION;

// unlodctr ausführen
HINSTANCE hInst = ::ShellExecute (NULL, NULL, "unlodctr", OLE2A(m_bstrName), NULL, SW_HIDE);
char cbBuffer[_MAX_PATH];

	_ASSERTE(NULL != hInst);
	while (::GetModuleFileName (hInst, cbBuffer, sizeof(cbBuffer)) > 0)
		;	// warten, bis unlodctr fertig ist

	regEntryMap[0].szData = m_bstrName;
	RETURN_FAILED_HRESULT(_Module.UpdateRegistryFromResource(IDR_PERFMON, FALSE, regEntryMap));

	return S_OK;
}

STDMETHODIMP CPerfContext::AddPerformanceObject(
	BSTR Name, BSTR Desc, BSTR HelpText, IPerfObject **ppIObj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIObj)
		return E_POINTER;

	COM_TRY {
	WPerfObject Object;
	
		THROW_FAILED_HRESULT(Object.LocalCreateInstance(CLSID_PerfObject));
		THROW_FAILED_HRESULT(WPersistMemory(Object) -> InitNew());

		THROW_FAILED_HRESULT(Object -> put_ContextName (m_bstrName));
		THROW_FAILED_HRESULT(Object -> put_Name (Name));
		THROW_FAILED_HRESULT(Object -> put_Description (Desc));
		THROW_FAILED_HRESULT(Object -> put_HelpText (HelpText));

		THROW_FAILED_HRESULT(m_Objs -> Append (Object));
		m_fIsDirty = true;

		*ppIObj = Object.detach();

	// alle Strukturen neu erzeugen
		THROW_FAILED_HRESULT(RegeneratePerfData());

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CPerfContext::GetNextBaseIndex(ULONG * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return E_POINTER;

	*pVal = m_ulIndex;
	m_ulIndex += 2;
	return S_OK;
}

STDMETHODIMP CPerfContext::LockMemory(DWORD dwTimeOut)
{
	if (NULL != m_hAppMemMutex) {
	LONG lStatus = ::WaitForSingleObject (m_hAppMemMutex, dwTimeOut);

		switch (lStatus) {
		case WAIT_OBJECT_0:
			return S_OK;

		case WAIT_TIMEOUT:
			return S_FALSE;	

		default:
			return HRESULT_FROM_WIN32(GetLastError());
		}
	}
	return S_FALSE;
}

STDMETHODIMP CPerfContext::UnlockMemory()
{
	if (NULL != m_hAppMemMutex)
		return (0 != ::ReleaseMutex (m_hAppMemMutex)) ? S_OK : HRESULT_FROM_WIN32(GetLastError());

	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Helper

namespace {
	class CProcessHelper 
	{
	public:
		CProcessHelper (DWORD dwPId)
			: m_hProcess(NULL)
		{
			m_hProcess = OpenProcess (PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwPId);
		}
		~CProcessHelper()
		{
		    if (NULL != m_hProcess)
				CloseHandle (m_hProcess);
		}

		bool operator! () { return NULL != m_hProcess; }
		HANDLE GetProcessHandle() { return m_hProcess; }

	private:
		HANDLE m_hProcess;
	};
} // namespace

BOOL GetProcessFileNameW (DWORD dwPId, wchar_t *pwcszName, int uiLen)
{
CProcessHelper Hlp (dwPId);

    if (!Hlp) return FALSE;

HMODULE hMod = NULL;
DWORD cbNeeded = 0;

    if (EnumProcessModules (Hlp.GetProcessHandle(), &hMod, sizeof(hMod), &cbNeeded))
        return GetModuleFileNameExW (Hlp.GetProcessHandle(), hMod, pwcszName, uiLen) > 0 ? TRUE : FALSE;

	return FALSE;
}

BOOL CPerfContext::InitSharedMemory (LPCOLESTR pcoleName)
{
// open & initialize shared memory file
	::SetLastError (ERROR_SUCCESS);   // just to clear it out

// open/create shared memory used by the application to pass performance values
LONG status = GetSharedMemoryDataHeader (FALSE);		// read/write access is required

// here the memory block should be initialized and ready for use
	if (status == ERROR_SUCCESS) {
	// erstmal nachsehen, ob es einen veralteten Block bzw. uns schon gibt
	APPMEM_INSTANCE *pInstance = FIRST_INUSE(m_pDataHeader);
	wchar_t wcszInstanceName[_MAX_PATH];

		::GetModuleFileNameW (NULL,	wcszInstanceName, _MAX_PATH);
		while (NULL != pInstance) {
		// in erster Linie müssen der Name und der Pfad stimmen
			if (!wcscmp (pInstance->wcszDataName, pcoleName) && 
				!_wcsicmp (pInstance->wcszInstanceName, wcszInstanceName)) 
			{
				if (pInstance -> dwProcessId == ::GetCurrentProcessId()) {
				// der ProzeßID stimmt auch, wir haben uns gefunden
					m_pAppData = pInstance;
					break;
				}
				else {
				// ProzeßID stimmt nicht, nachsehen, ob's evtl. eine bereits gestorbene Instanz ist
				wchar_t wcszProcessName[_MAX_PATH];

					if (!GetProcessFileNameW (pInstance -> dwProcessId, wcszProcessName, _MAX_PATH) ||
						_wcsicmp (wcszProcessName, wcszInstanceName)) 
					{
					// eine tote Instanz gefunden, wiederverwenden dieses Blocks
						m_pAppData = pInstance;

						m_pAppData->dwProcessId = ::GetCurrentProcessId();
						::GetModuleFileNameW (NULL,	m_pAppData->wcszInstanceName, _MAX_PATH);
						wcsncpy (m_pAppData->wcszDataName, pcoleName, MAX_SIZEOF_DATA_NAME);
						m_pAppData->wcszDataName[MAX_SIZEOF_DATA_NAME-1] = L'\0';
						break;
					}
				}
			}

			if (0 != pInstance -> dwOffsetOfNext)
				pInstance = APPMEM_INST(m_pDataHeader, pInstance -> dwOffsetOfNext);
			else
				pInstance = NULL;		// last entry
		}

	// wenn noch nicht gefunden, den nächsten freien Block verwenden
		if (NULL == m_pAppData && m_pDataHeader->dwFirstFreeOffset != 0) {
		// then there are blocks left so get the next free
			m_pAppData = FIRST_FREE(m_pDataHeader);

		// update free list to make next item the first in list
			m_pDataHeader->dwFirstFreeOffset = m_pAppData->dwOffsetOfNext;

		// insert the new item into the head of the in use list
			m_pAppData->dwOffsetOfNext = m_pDataHeader->dwFirstInUseOffset;
			m_pDataHeader->dwFirstInUseOffset = (DWORD)((LPBYTE)m_pAppData - (LPBYTE)m_pDataHeader);

		// now initialize this instance's data
			m_pAppData->dwProcessId = ::GetCurrentProcessId();
			::GetModuleFileNameW (NULL,	m_pAppData->wcszInstanceName, _MAX_PATH);
			wcsncpy (m_pAppData->wcszDataName, pcoleName, MAX_SIZEOF_DATA_NAME);
			m_pAppData->wcszDataName[MAX_SIZEOF_DATA_NAME-1] = L'\0';
			
			m_pDataHeader->dwInstanceCount++;    // increment count
		} 
		else {
		// no more free slots left
			m_pAppData = NULL;
			return FALSE;
		}
    } 
	else {
	// unable to open shared memory file
	// even though this is an error we should return true so as to 
	// not abort the application. No performance data will be 
	// collected though.
		m_pAppData = NULL;
		return FALSE;
    }
    return TRUE;
}

LONG CPerfContext::GetSharedMemoryDataHeader (BOOL bReadOnlyAccess)
{
	return ::GetSharedMemoryDataHeader (&m_hAppMemSharedMemory, &m_hAppMemMutex, &m_pDataHeader, bReadOnlyAccess);
}

BOOL CPerfContext::ReleaseSharedMemory()
{
	return ::ReleaseSharedMemory (&m_hAppMemSharedMemory, &m_hAppMemMutex, &m_pDataHeader, &m_pAppData);
}

HRESULT CPerfContext::GenerateIniFile (os_string &rStrIniName, os_string &rStrSymName)
{
char cbTempPath[_MAX_PATH];
char cbBuffer[_MAX_PATH];

	::GetTempPath (sizeof(cbTempPath), cbTempPath);
	::GetTempFileName (cbTempPath, "PFM", 0, cbBuffer);
	::DeleteFile (cbBuffer);
	rStrIniName = cbBuffer;

os_path path (rStrIniName);

	path.extension("ini");
	rStrIniName = (LPCSTR)path;

FILE *fpIni = fopen (rStrIniName.c_str(), "w+t");

	if (NULL == fpIni)
		return E_FAIL;

	::GetTempFileName (cbTempPath, "PFM", 0, cbBuffer);
	::DeleteFile (cbBuffer);
	rStrSymName = cbBuffer;
	path.extension("h");
	rStrSymName = (LPCSTR)path;

FILE *fpSym = fopen (rStrSymName.c_str(), "w+t");
HRESULT hr = E_FAIL;

	if (NULL != fpSym) {
		USES_CONVERSION;

	LANGID iLangID = PRIMARYLANGID(m_Locale);


		fprintf (fpIni, "[info]\n");
		fprintf (fpIni, "drivername=%ls\n", m_bstrName);
		fprintf (fpIni, "symbolfile=\"%s\"\n\n", path.filename().c_str());
		fprintf (fpIni, "[languages]\n");
		if (0 != iLangID && 9 != iLangID) {
		char cbLang[64];

			VERIFY(::GetLocaleInfo (m_Locale, LOCALE_SENGLANGUAGE, cbLang, sizeof(cbLang)) > 0);
			fprintf (fpIni, "%03d=%s\n", iLangID, cbLang);
		}
		fprintf (fpIni, "009=English\n");

	// für alle Objekte
		COM_TRY {
		WEnumVARIANT Enum;
		CComVariant v;

			THROW_FAILED_HRESULT(m_Objs -> _NewEnum (Enum.ppu()));

		// lediglich ObjektInfo wegschreiben
			fprintf (fpIni, "\n[objects]\n");
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &v, NULL); /**/) {
				_ASSERTE(VT_DISPATCH == V_VT(&v));

			WPerfObject Obj (V_DISPATCH(&v));
			CComBSTR bstrName;

				THROW_FAILED_HRESULT(Obj -> get_Name (&bstrName));
				bstrName.Append ("_obj");
				_wcsupr (bstrName);

			CComBSTR bstrDesc;

				THROW_FAILED_HRESULT(Obj -> get_Description (&bstrDesc));
				if (0 != iLangID && 9 != iLangID)
					fprintf (fpIni, "%ls_%03d_NAME=%ls\n", bstrName, iLangID, bstrDesc);
				fprintf (fpIni, "%ls_009_NAME=%ls\n", bstrName, bstrDesc);
			}

			fprintf (fpIni, "\n[text]\n");
		// gesamte Info wegschreiben
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &v, NULL); /**/) {
				_ASSERTE(VT_DISPATCH == V_VT(&v));

			WPerfObject Obj (V_DISPATCH(&v));
			CComBSTR bstrName;

				THROW_FAILED_HRESULT(Obj -> get_Name (&bstrName));
				bstrName.Append ("_obj");
				_wcsupr (bstrName);

			CComBSTR bstrDesc;
			CComBSTR bstrHelp;
			ULONG ulIndex = 0;

				THROW_FAILED_HRESULT(Obj -> get_Description (&bstrDesc));
				THROW_FAILED_HRESULT(Obj -> get_HelpText (&bstrHelp));
				THROW_FAILED_HRESULT(Obj -> get_BaseIndex (&ulIndex));
				if (0 != iLangID && 9 != iLangID) {
					fprintf (fpIni, "%ls_%03d_NAME=%ls\n", bstrName, iLangID, bstrDesc);
					fprintf (fpIni, "%ls_%03d_HELP=%ls\n", bstrName, iLangID, bstrHelp);
				}
				fprintf (fpIni, "%ls_009_NAME=%ls\n", bstrName, bstrDesc);
				fprintf (fpIni, "%ls_009_HELP=%ls\n", bstrName, bstrHelp);

				fprintf (fpSym, "#define %ls %d\n", bstrName, ulIndex);

			// alle counter dieses Objektes ausgeben
			WPerfCounterDefinitions Counters;

				THROW_FAILED_HRESULT(Obj -> get_CounterDefs (Counters.ppi()));

			WEnumVARIANT EnumCounters;
			CComVariant vCounter;

				THROW_FAILED_HRESULT(Counters -> _NewEnum (EnumCounters.ppu()));
				for (EnumCounters -> Reset(); S_OK == EnumCounters -> Next (1, &vCounter, NULL); /**/) {
					_ASSERTE(VT_DISPATCH == V_VT(&vCounter));

				WPerfCounterDefinition CounterDef (V_DISPATCH(&vCounter));

					THROW_FAILED_HRESULT(CounterDef -> get_Name (&bstrName));
					bstrName.Append ("_counter");
					_wcsupr (bstrName);

					THROW_FAILED_HRESULT(CounterDef -> get_Description (&bstrDesc));
					THROW_FAILED_HRESULT(CounterDef -> get_HelpText (&bstrHelp));
					THROW_FAILED_HRESULT(CounterDef -> get_BaseIndex (&ulIndex));
					if (0 != iLangID && 9 != iLangID) {
						fprintf (fpIni, "%ls_%03d_NAME=%ls\n", bstrName, iLangID, bstrDesc);
						fprintf (fpIni, "%ls_%03d_HELP=%ls\n", bstrName, iLangID, bstrHelp);
					}
					fprintf (fpIni, "%ls_009_NAME=%ls\n", bstrName, bstrDesc);
					fprintf (fpIni, "%ls_009_HELP=%ls\n", bstrName, bstrHelp);

					fprintf (fpSym, "#define %ls %d\n", bstrName, ulIndex);
				}
			}

		} COM_CATCH_OP(
			fclose(fpSym);
			fclose(fpIni);
		);
		hr = S_OK;
	}

// success
	fclose(fpSym);
	fclose(fpIni);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// alle Strukturen neu erzeugen und ins SharedMem übertragen
STDMETHODIMP CPerfContext::RegeneratePerfData()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_Mode != PERFMONSTARTMODE_Normal)
		return S_FALSE;		// nothing to do

	COM_TRY {
	CLockMutex Lock (m_hAppMemMutex);
	WPersistMemory PM (GetUnknown());
	ULONG ulSize = 0;

		THROW_FAILED_HRESULT(PM -> GetSizeMax(&ulSize));
		if (ulSize > SHARED_MEMORY_ITEM_SIZE)
			return E_FAIL;
		THROW_FAILED_HRESULT(PM -> Save (&m_pAppData -> bytePerfData[0], TRUE, ulSize));

	// Anzahl der Objektdefinitionen und Gesamtgröße setzen
	ULONG ulObjCount = 0;

		THROW_FAILED_HRESULT(m_Objs -> get_Count (&ulObjCount));
		m_pAppData -> ulObjectCount = ulObjCount;
		m_pAppData -> dwSpaceNeeded = ulSize;

	} COM_CATCH;
	return S_OK;
}

// lediglich alle Collect-counter durchgehen und Daten übernehmen
STDMETHODIMP CPerfContext::UpdatePerfData()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Globale Helper

///////////////////////////////////////////////////////////////////////////////
// SharedMemory anfordern und initialisieren
LONG GetSharedMemoryDataHeader (
	HANDLE *phAppMemSharedMemory, HANDLE *phAppMemMutex, 
	APPMEM_DATA_HEADER **ppDataHeader, BOOL bReadOnlyAccess)
{
LONG Status, MemStatus;
BOOL bFreeMutex;
PAPPMEM_INSTANCE pLastItem;
PAPPMEM_INSTANCE pAppData;
DWORD dwInstance;

	::SetLastError (ERROR_SUCCESS);   // just to clear it out

	*phAppMemSharedMemory = CreateFileMapping(
								INVALID_HANDLE_VALUE,     // to create a temp file
								NULL,                   // no security
								PAGE_READWRITE,         // to allow read & write access
								0,
								SHARED_MEMORY_OBJECT_SIZE,	// file size
								SHARED_MEMORY_OBJECT_NAME);	// object name

	MemStatus = GetLastError();    // to see if this is the first opening

// return error if unsuccessful
	if (*phAppMemSharedMemory == NULL) {
		Status = PERFMON_OPEN_FILE_MAPPING_ERROR;
		// this is fatal, if we can't get data then there's no
		// point in continuing.
	} else {
	// the application memory file was created/access successfully
	// so we need to get the sync. mutex before we use it
		*phAppMemMutex = CreateMutex (NULL, FALSE, SHARED_MEMORY_MUTEX_NAME);

	// if successful then wait for ownership, otherwise,
	// we'll just take our chances.

		if (*phAppMemMutex != NULL) {
			if (WaitForSingleObject (*phAppMemMutex, SHARED_MEMORY_MUTEX_TIMEOUT) == WAIT_FAILED) {
			// unable to obtain a lock
				bFreeMutex = FALSE;
			} else {
				bFreeMutex = TRUE;
			}
		} else {
			bFreeMutex = FALSE;
		}

		if (MemStatus != ERROR_ALREADY_EXISTS) {
		// this is the first access to the file so initialize the
		// instance count
			*ppDataHeader = (PAPPMEM_DATA_HEADER)MapViewOfFile(
												*phAppMemSharedMemory,  // shared mem handle
												FILE_MAP_WRITE,         // access desired
												0,                      // starting offset
												0,
												0);                     // map the entire object
			if (*ppDataHeader != NULL) {
			// if here, then pdwInstanceCount should be valid
			// so initialize the shared memory structure
			// clear memory block
				memset (*ppDataHeader, 0, SHARED_MEMORY_OBJECT_SIZE);

			// initialize application data header
				(*ppDataHeader)->dwInstanceCount = 0;       // no instances
				(*ppDataHeader)->dwFirstInUseOffset = 0;    // no busy items yet
				(*ppDataHeader)->dwFirstFreeOffset = (DWORD)((LPBYTE)&(*ppDataHeader)[1] - (LPBYTE)*ppDataHeader);

				pLastItem = FIRST_FREE((*ppDataHeader));

			// set pointers in each item of block
				pAppData = pLastItem + 1;
				for (dwInstance = (SHARED_MEMORY_ITEM_COUNT -1); dwInstance > 0; dwInstance--) {
					pLastItem->dwOffsetOfNext = (DWORD)((LPBYTE)pAppData - (LPBYTE)(*ppDataHeader));
					pLastItem = pAppData;
					pAppData++;
				}

				pAppData->dwOffsetOfNext = 0; // end of list
				Status = ERROR_SUCCESS;
			} else {
				Status = PERFMON_UNABLE_MAP_VIEW_OF_FILE;
			}
		} else {
		// the status is ERROR_ALREADY_EXISTS which is successful
			Status = ERROR_SUCCESS;
		}

	// see if Read Only access is required
		if (Status == ERROR_SUCCESS) {
		// by now the shared memory has already been initialized so
		// we if we don't need write access any more or if it has
		// already been opened, then open with the desired access
			*ppDataHeader = (PAPPMEM_DATA_HEADER)MapViewOfFile(
												*phAppMemSharedMemory,  // shared mem handle
												(bReadOnlyAccess ? FILE_MAP_READ : FILE_MAP_WRITE),    // access desired
												0,                      // starting offset
												0,
												0);                     // map the entire object
			if (*ppDataHeader == NULL) {
				Status = PERFMON_UNABLE_MAP_VIEW_OF_FILE;
			// this is fatal, if we can't get data then there's no
			// point in continuing.
			} else {
				Status = ERROR_SUCCESS;
			}
		}

	// done with the shared memory so free the mutex if one was
	// acquired
		if (bFreeMutex) {
			ReleaseMutex (*phAppMemMutex);
		}
	}
	return Status;
}

BOOL ReleaseSharedMemory(
	HANDLE *phAppMemSharedMemory, HANDLE *phAppMemMutex, 
	APPMEM_DATA_HEADER **ppDataHeader, APPMEM_INSTANCE **ppAppData)
{
BOOL bFreeMutex = FALSE;
PAPPMEM_INSTANCE pPrevItem = NULL;

// remove instance for this app
	if ((*ppAppData != NULL) && (*ppDataHeader != NULL)) {
	// lock memory block
		if (*phAppMemMutex != NULL) {
			if (WaitForSingleObject (*phAppMemMutex, SHARED_MEMORY_MUTEX_TIMEOUT) == WAIT_FAILED) {
			// unable to obtain a lock
				bFreeMutex = FALSE;
			} else {
				bFreeMutex = TRUE;
			}
		} else {
			bFreeMutex = FALSE;
		}

	// zero the fields out first
		(*ppAppData)->dwProcessId = 0;
		memset (&(*ppAppData)->wcszInstanceName[0], 0, (MAX_SIZEOF_INSTANCE_NAME * sizeof (WCHAR)));
		memset (&(*ppAppData)->wcszDataName[0], 0, (MAX_SIZEOF_DATA_NAME * sizeof (WCHAR)));

	// move from in use (busy) list back to the free list
		if (((*ppDataHeader)->dwFirstFreeOffset != 0) && ((*ppDataHeader)->dwFirstInUseOffset != 0)) {
		// find previous item in busy list
			if (FIRST_INUSE(*ppDataHeader) != *ppAppData) {
			// not the first so walk down the list
				pPrevItem = FIRST_INUSE(*ppDataHeader);
				while (APPMEM_INST(*ppDataHeader, pPrevItem->dwOffsetOfNext) != *ppAppData) {
					pPrevItem = APPMEM_INST(*ppDataHeader, pPrevItem->dwOffsetOfNext);
					if (pPrevItem->dwOffsetOfNext == 0) break; // end of list
				}
				if (APPMEM_INST(*ppDataHeader, pPrevItem->dwOffsetOfNext) == *ppAppData) {
					APPMEM_INST(*ppDataHeader, pPrevItem->dwOffsetOfNext)->dwOffsetOfNext = (*ppAppData)->dwOffsetOfNext;
				} else {
				// it was never in the busy list (?!?)
				}
			} else {
			// this is the first in the list so update it
				(*ppDataHeader)->dwFirstInUseOffset = (*ppAppData)->dwOffsetOfNext;
			}

		// here, pAppData has been removed from the InUse list and now
		// it must be inserted back at the beginning of the free list
			(*ppAppData)->dwOffsetOfNext = (*ppDataHeader)->dwFirstFreeOffset;
			(*ppDataHeader)->dwFirstFreeOffset = (DWORD)((LPBYTE)*ppAppData - (LPBYTE)*ppDataHeader);
		}

	// decrement instance counter
		(*ppDataHeader)->dwInstanceCount--;    // decrement count
	}

	if (bFreeMutex) {
		ReleaseMutex (*phAppMemMutex);
	}

// close shared memory file handle
	if (*phAppMemSharedMemory != NULL) {
		::CloseHandle (*phAppMemSharedMemory);
		*phAppMemSharedMemory = NULL;
	}
	if (*phAppMemMutex != NULL) {
		::CloseHandle(*phAppMemMutex);
		*phAppMemMutex = NULL;
	}

// clear pointers
	*ppDataHeader = NULL;
	*ppAppData = NULL;
	return TRUE;
}
