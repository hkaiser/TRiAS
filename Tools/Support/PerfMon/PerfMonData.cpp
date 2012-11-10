// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/26/1998 07:29:20 PM
//
// @doc
// @module PerfMonData.cpp | Schnittstellendatei zu PerfMon

#include <StdAfx.h>

#include <winperf.h>
#include <Com/PerfMonContext.h>

#include "Wrapper.h"
#include "MemCtrs.h"

#include "PerfData.h"
#include "EventLogMacros.h"

#if defined(_DEBUG)
extern DWORD dwHaltOnStartup;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(PerfContextHelper);

///////////////////////////////////////////////////////////////////////////////
//  Function Prototypes
//
//      these are used to insure that the data collection functions
//      accessed by Perflib will have the correct calling format.
//
PM_OPEN_PROC    OpenPerformanceData;
PM_COLLECT_PROC CollectPerformanceData;
PM_CLOSE_PROC   ClosePerformanceData;

///////////////////////////////////////////////////////////////////////////////
// StringKonstanten
const OLECHAR g_cbAppName[] = L"PerfMonAdapter";
const TCHAR g_cbFirstCounter[] = TEXT("First Counter");
const TCHAR g_cbFirstHelp[] = TEXT("First Help");

const WCHAR GLOBAL_STRING[] = L"Global";
const WCHAR FOREIGN_STRING[] = L"Foreign";
const WCHAR COSTLY_STRING[] = L"Costly";
const WCHAR NULL_STRING[] = L"\0";    // pointer to null string

///////////////////////////////////////////////////////////////////////////////
// sonstiges
#define QUERY_GLOBAL    1
#define QUERY_ITEMS     2
#define QUERY_FOREIGN   3
#define QUERY_COSTLY    4

// test for delimiter, end of line and non-digit characters
// used by IsNumberInUnicodeList routine
#define DIGIT       1
#define DELIMITER   2
#define INVALID     3

inline int EvalThisChar (OLECHAR c, OLECHAR d) 
{
	if (c == d) 
		return DELIMITER;
	else if (c == 0) 
		return DELIMITER; 
	else if (c < (WCHAR)'0') 
		return INVALID;
	else if (c > (WCHAR)'9') 
		return INVALID;
	else
		return DIGIT;
}

///////////////////////////////////////////////////////////////////////////////
// globale Variablen
namespace {
	DWORD g_dwOpenCount = 0;				// count of "Open" threads
	BOOL g_bInitOK = FALSE;					// true = DLL initialized OK

	// App Mem counter data structures
	HANDLE g_hAppMemSharedMemory = NULL;	// Handle of counter Shared Memory
	HANDLE g_hAppMemMutex = NULL;			// sync mutex for memory

	APPMEM_DATA_HEADER *g_pDataHeader = NULL; // pointer to header of shared mem

	WPerfContextHelper g_Ctx;				// PerfDataObject
};

///////////////////////////////////////////////////////////////////////////////
// Routine Description:
//
//    This routine will open and map the memory used by the PerfMon DLL to
//    pass performance data in. This routine also initializes the data
//    structures used to pass data back to the registry
//
// Arguments:
//
//    Pointer to object ID of each device to be opened
//
// Return Value:
//
//    None.

DWORD APIENTRY OpenPerformanceData(LPWSTR lpDeviceNames)
{
LONG status = ERROR_SUCCESS;

//  Since WINLOGON is multi-threaded and will call this routine in
//  order to service remote performance queries, this library
//  must keep track of how many times it has been opened (i.e.
//  how many threads have accessed it). the registry routines will
//  limit access to the initialization routine to only one thread 
//  at a time so synchronization (i.e. reentrancy) should not be 
//  a problem
	if (!g_dwOpenCount) {
		COM_TRY {
			THROW_FAILED_HRESULT(CoInitialize(NULL));
			THROW_FAILED_HRESULT(_Module.InitGIT());		// GlobalInterfaceTable initialisieren

		WPerfContext Ctx;

			THROW_FAILED_HRESULT(PerfMonGetOrCreateContext (lpDeviceNames, Ctx.ppi()));
			g_Ctx = Ctx;
		} COM_CATCH;

	// open Eventlog interface
		g_hEventLog = OpenEventLog (g_cbAppName);

	// open/create shared memory used by the application to pass performance values
		status = GetSharedMemoryDataHeader (&g_hAppMemSharedMemory, &g_hAppMemMutex, &g_pDataHeader, TRUE); // only read access is required
		if (status != ERROR_SUCCESS) {
			REPORT_ERROR_DATA (status, LOG_USER, NULL, 0);
			return status;
		}
		g_bInitOK = TRUE;	// ok to use this function
	}

	g_dwOpenCount++;		// increment OPEN counter
	return ERROR_SUCCESS;	// for successful exit
}

// GetQueryType
//
//    returns the type of query described in the lpValue string so that
//    the appropriate processing method may be used
//
// Arguments
//
//    IN lpValue
//        string passed to PerfRegQuery Value for processing
//
// Return Value
//
//    QUERY_GLOBAL
//        if lpValue == 0 (null pointer)
//           lpValue == pointer to Null string
//           lpValue == pointer to "Global" string
//
//    QUERY_FOREIGN
//        if lpValue == pointer to "Foriegn" string
//
//    QUERY_COSTLY
//        if lpValue == pointer to "Costly" string
//
//    otherwise:
//
//    QUERY_ITEMS

DWORD GetQueryType (LPWSTR lpValue)
{
	if (NULL == lpValue) 
		return QUERY_GLOBAL;
	else if (0 == *lpValue) 
		return QUERY_GLOBAL;

// check for "Global" request
	if (!wcscmp (GLOBAL_STRING, lpValue))
		return QUERY_GLOBAL;

// check for "Foreign" request
	if (!wcscmp (FOREIGN_STRING, lpValue))
		return QUERY_FOREIGN;

// check for "Costly" request
	if (!wcscmp (COSTLY_STRING, lpValue))
		return QUERY_COSTLY;

// if not Global and not Foreign and not Costly,
// then it must be an item list
	return QUERY_ITEMS;
}

// IsNumberInUnicodeList
//
// Arguments:
//
//    IN dwNumber
//        DWORD number to find in list
//
//    IN lpwszUnicodeList
//        Null terminated, Space delimited list of decimal numbers
//
// Return Value:
//
//    TRUE:
//            dwNumber was found in the list of unicode number strings
//
//    FALSE:
//            dwNumber was not found in the list.
BOOL IsNumberInUnicodeList (DWORD dwNumber, LPWSTR lpwszUnicodeList)
{
DWORD   dwThisNumber;
WCHAR   *pwcThisChar;
BOOL    bValidNumber;
BOOL    bNewItem;
WCHAR   wcDelimiter;    // could be an argument to be more flexible

	if (lpwszUnicodeList == 0) return FALSE;    // null pointer, # not founde

	pwcThisChar = lpwszUnicodeList;
	dwThisNumber = 0;
	wcDelimiter = (WCHAR)' ';
	bValidNumber = FALSE;
	bNewItem = TRUE;

	while (TRUE) {
		switch (EvalThisChar (*pwcThisChar, wcDelimiter)) {
		case DIGIT:
		// if this is the first digit after a delimiter, then
		// set flags to start computing the new number
			if (bNewItem) {
				bNewItem = FALSE;
				bValidNumber = TRUE;
			}
			if (bValidNumber) {
				dwThisNumber *= 10;
				dwThisNumber += (*pwcThisChar - (WCHAR)'0');
			}
			break;

		case DELIMITER:
		// a delimter is either the delimiter character or the
		// end of the string ('\0') if when the delimiter has been
		// reached a valid number was found, then compare it to the
		// number from the argument list. if this is the end of the
		// string and no match was found, then return.
			if (bValidNumber) {
				if (dwThisNumber == dwNumber) 
					return TRUE;
				bValidNumber = FALSE;
			}
			if (*pwcThisChar == 0) 
				return FALSE;
			else {
				bNewItem = TRUE;
				dwThisNumber = 0;
			}
			break;

		case INVALID:
		// if an invalid character was encountered, ignore all
		// characters up to the next delimiter and then start fresh.
		// the invalid number is not compared.
			bValidNumber = FALSE;
			break;

		default:
			break;
		}
		pwcThisChar++;
	}
}

// Routine Description:
//
//    This routine will return the data for the Application memory counters
//
// Arguments:
//
//   IN       LPWSTR   lpValueName
//            pointer to a wide character string passed by registry.
//
//   IN OUT   LPVOID   *lppData
//         IN: pointer to the address of the buffer to receive the completed
//            PerfDataBlock and subordinate structures. This routine will
//            append its data to the buffer starting at the point referenced
//            by *lppData.
//         OUT: points to the first byte after the data structure added by this
//            routine. This routine updated the value at lppdata after appending
//            its data.
//
//   IN OUT   LPDWORD  lpcbTotalBytes
//         IN: the address of the DWORD that tells the size in bytes of the
//            buffer referenced by the lppData argument
//         OUT: the number of bytes added by this routine is writted to the
//            DWORD pointed to by this argument
//
//   IN OUT   LPDWORD  NumObjectTypes
//         IN: the address of the DWORD to receive the number of objects added
//            by this routine
//         OUT: the number of objects added by this routine is writted to the
//            DWORD pointed to by this argument
//
// Return Value:
//
//      ERROR_MORE_DATA if buffer passed is too small to hold data
//         any error conditions encountered are reported to the event log if
//         event logging is enabled.
//
//      ERROR_SUCCESS  if success or any other error. Errors, however are
//         also reported to the event log.
DWORD APIENTRY CollectPerformanceData(
	LPWSTR lpValueName, LPVOID *lppData, LPDWORD lpcbTotalBytes, LPDWORD lpNumObjectTypes)
{
	_ASSERTE(!dwHaltOnStartup);

//  Variables for reformating the data
void *pvBase = *lppData;

// before doing anything else, see if Open went OK
	if ((!g_bInitOK) || (g_pDataHeader == NULL)) {
	// unable to continue because open failed.
		*lpcbTotalBytes = (DWORD)0;
		*lpNumObjectTypes = (DWORD)0;
		return ERROR_SUCCESS;		// yes, this is a successful exit
	}

// see if this is a foreign (i.e. non-NT) computer data request
DWORD dwQueryType = ::GetQueryType (lpValueName);

	if (QUERY_FOREIGN == dwQueryType) {
	// this routine does not service requests for data from Non-NT computers
		*lpcbTotalBytes = (DWORD) 0;
		*lpNumObjectTypes = (DWORD) 0;
		return ERROR_SUCCESS;
	}

// update PerfData
	if (g_Ctx.IsValid())
		g_Ctx -> UpdatePerfData();

// if here, then this must be one for us so load data structures
ULONG ulObjectCount = 0;	// counter of object definitions

	{
	CLockMutex LockMtx (g_hAppMemMutex);
    
	// point to the first instance structure in the shared buffer
	APPMEM_INSTANCE *pThisAppInstanceData = FIRST_INUSE(g_pDataHeader);

		if (dwQueryType == QUERY_ITEMS){
		APPMEM_INSTANCE *pInstance = pThisAppInstanceData;
		BOOL fFound = FALSE;

			while (NULL != pInstance) {
			// alle definierten PerfMon-Instanzen durchgehen
			PERF_OBJECT_TYPE *pObject = (PERF_OBJECT_TYPE *)&pInstance -> bytePerfData[0];

				for (ULONG iCnt = 0; iCnt < pInstance -> ulObjectCount; ++iCnt) {
					if (::IsNumberInUnicodeList (pObject -> ObjectNameTitleIndex, lpValueName)) 
						fFound = TRUE;

				DWORD dwLen = pObject -> TotalByteLength;

					pObject = (PERF_OBJECT_TYPE *)((BYTE *)pObject + dwLen);	// next object definition
				}
				if (fFound)
					break;		// wenn gefunden, dann weiter

				if (0 != pInstance -> dwOffsetOfNext)
					pInstance = APPMEM_INST(g_pDataHeader, pInstance -> dwOffsetOfNext);
				else
					pInstance = NULL;		// last entry
			}

			if (!fFound) {
			// request received for data object not provided by this routine
				*lpcbTotalBytes = (DWORD)0;
				*lpNumObjectTypes = (DWORD)0;
				return ERROR_SUCCESS;
			}

		// eines der definierten Objekt ist gesucht
		// ...
		}

	// no defined instances, no fun
		if (0 == g_pDataHeader -> dwInstanceCount) {
			*lpcbTotalBytes = (DWORD)0;
			*lpNumObjectTypes = (DWORD)0;
			return ERROR_SUCCESS;
		}

	// calculate needed space for all instances
	ULONG ulSpaceNeeded = 0;
	APPMEM_INSTANCE *pInstance = pThisAppInstanceData;

		while (NULL != pInstance) {
			ulSpaceNeeded += pInstance -> dwSpaceNeeded;
			if (0 != pInstance -> dwOffsetOfNext)
				pInstance = APPMEM_INST(g_pDataHeader, pInstance -> dwOffsetOfNext);
			else
				pInstance = NULL;		// last entry
		}

		if (*lpcbTotalBytes < ulSpaceNeeded) {
		// not enough room so return nothing.
			*lpcbTotalBytes = (DWORD)0;
			*lpNumObjectTypes = (DWORD)0;
			return ERROR_MORE_DATA;
		}

	// copy the object & counter definition information
		pInstance = pThisAppInstanceData;
		while (NULL != pInstance) {
			memmove (*lppData, &pInstance -> bytePerfData[0], pInstance -> dwSpaceNeeded);
			ulObjectCount += pInstance -> ulObjectCount;
			*lppData = (BYTE *)(*lppData) + pInstance -> dwSpaceNeeded;

			if (0 != pInstance -> dwOffsetOfNext) 
				pInstance = APPMEM_INST(g_pDataHeader, pInstance -> dwOffsetOfNext);
			else
				pInstance = NULL;		// last entry
		}
	} // CLockMutex goes out of scope

// update arguments for return
    *lpNumObjectTypes = ulObjectCount;
    *lpcbTotalBytes = (DWORD)((BYTE *)(*lppData) - (BYTE *)pvBase);

    return ERROR_SUCCESS;
}

//Routine Description:
//
//    This routine closes the open handles to Application Memory
//        usage performance counters
//
//Arguments:
//
//    None.
//
//
//Return Value:
//
//    ERROR_SUCCESS

DWORD APIENTRY ClosePerformanceData()
{
	if ((--g_dwOpenCount) == 0) { // when this is the last thread...
		if (g_hAppMemSharedMemory != NULL) {
			::CloseHandle(g_hAppMemSharedMemory);
			g_hAppMemSharedMemory = NULL;
		}
		if (g_hAppMemMutex != NULL) {
			::CloseHandle(g_hAppMemMutex);
			g_hAppMemMutex = NULL;
		}
		g_pDataHeader = NULL;
		g_Ctx.Assign(NULL);

		CloseEventLog();
		CoUninitialize();
	}
	return ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
// HelperFunktionen für EventLog

HANDLE g_hEventLog = NULL;		// handle to event log
DWORD g_dwLogUsers = 0;			// counter of event log using routines
DWORD g_dwMsgLevel = 0;		// event logging detail level

// Reads the level of event logging from the registry and opens the
// channel to the event logger for subsequent event log entries.
HANDLE OpenEventLog (LPCOLESTR pcoleName)
{
HKEY hAppKey;
TCHAR LogLevelKeyName[] = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Perflib";
TCHAR LogLevelValueName[] = "EventLogLevel";

LONG lStatus;

DWORD dwLogLevel;
DWORD dwValueType;
DWORD dwValueSize;

// if global value of the logging level not initialized or is disabled,
// check the registry to see if it should be updated.
	if (!g_dwMsgLevel) {
		lStatus = RegOpenKeyEx (HKEY_LOCAL_MACHINE,	LogLevelKeyName, 0, KEY_READ, &hAppKey);
		dwValueSize = sizeof (dwLogLevel);

		if (lStatus == ERROR_SUCCESS) {
			lStatus = RegQueryValueEx (hAppKey,	LogLevelValueName, (LPDWORD)NULL, &dwValueType, (LPBYTE)&dwLogLevel, &dwValueSize);
			if (lStatus == ERROR_SUCCESS) {
				g_dwMsgLevel = dwLogLevel;
			} else {
				g_dwMsgLevel = MESSAGE_LEVEL_DEFAULT;
			}
			RegCloseKey (hAppKey);
		} else {
			g_dwMsgLevel = MESSAGE_LEVEL_DEFAULT;
		}
	}

	if (g_hEventLog == NULL){
		USES_CONVERSION;
		g_hEventLog = RegisterEventSource (
						(LPTSTR)NULL,	// Use Local Machine
						OLE2A(pcoleName));		// event log app name to find in registry

		if (g_hEventLog != NULL) {
			REPORT_INFORMATION (UTIL_LOG_OPEN, LOG_DEBUG);
		}
	}

	if (g_hEventLog != NULL) {
		g_dwLogUsers++;           // increment count of perfctr log users
	}
	return g_hEventLog;
}

// Closes the handle to the event logger if this is the last caller
void CloseEventLog ()
{
	if (g_hEventLog != NULL) {
		g_dwLogUsers--;         // decrement usage
		if (g_dwLogUsers <= 0) {    // and if we're the last, then close up log
			REPORT_INFORMATION (UTIL_CLOSING_LOG, LOG_DEBUG);
			DeregisterEventSource (g_hEventLog);
		}
	}
}
