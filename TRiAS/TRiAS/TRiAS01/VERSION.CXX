// Liefert VersionsNummer fuer aktuelle Datenbasis
// File: VERSION.C

#include "trias01p.hxx"

#include <float.h>

#include <NativeIdent.h>
#include <NativeMerkmal.h>
#include <Versions.h>

#include "syncdb.hxx"
#include "DbmsVersion.h"

#import "tlb/TRiASMDS.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids 

#if defined(_USE_CONNECTFILTER)
#include "ObjectGiST.h"
#endif // defined(_USE_CONNECTFILTER)

///////////////////////////////////////////////////////////////////////////////
// 
DefineSmartInterface(TRiASMDSMap);

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

long FUNCTYPE LocGetDBVersion (HPROJECT hPr) 
{
	if (hPr == 0) {
	// aktuelles Projekt verwenden
		if (act_db != NULL) 
			return act_db -> db_version;
		else {
			TX_ASSERT(NULL != act_db);
			return 0L;
		}
	} else {
	// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if (db_p -> db_name != NULL || db_p -> db_pIStorage) 
			return db_p -> db_version;
		else {
			TX_ASSERT(db_p -> db_name != NULL || db_p -> db_pIStorage);
			return 0L;	// Fehler
		}
	}
	
return 0L;
}

long FUNCTYPE EXPORT01 GetDBVersion (HPROJECT hPr) 
{
	SYNC_DBACCESS (g_pDbMutex, hPr);
	return LocGetDBVersion (hPr);
}

long FUNCTYPE EXPORT01 GetDbmsVersion() 
{
	return MAKELONG(TRIASDBMS_BUILD, MAKEWORD(TRIASDBMS_RELEASE, TRIASDBMS_VERSION));
}

extern "C" 
BOOL FUNCTYPE EXPORT01 GetCopyMode (HPROJECT hPr, BOOL *pfRO)
{
	if (NULL == pfRO) return false;

	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (hPr == 0) {		// aktuelles Projekt verwenden
		if (act_db != NULL) {
			*pfRO = act_db -> db_fOpenedAsCopy;
			return true;
		}
	} else {			// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if (NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) {
			*pfRO = db_p -> db_fOpenedAsCopy;
			return true;
		}
	}

return false;	// nicht festzustellen
}

extern "C" 
BOOL FUNCTYPE EXPORT01 GetROMode (HPROJECT hPr, BOOL *pfRO)
{
	if (NULL == pfRO) return false;

	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (hPr == 0) {		// aktuelles Projekt verwenden
		if (act_db != NULL) {
			*pfRO = act_db -> db_fOpenedRO;
			return true;
		} 
	} else {			// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if (NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) {
			*pfRO = db_p -> db_fOpenedRO;
			return true;
		}
	}

	return false;	// nicht festzustellen
}

extern "C" 
BOOL FUNCTYPE EXPORT01 GetIsCompoundDB (HPROJECT hPr, BOOL *pfIsCompound)
{
	if (NULL == pfIsCompound) return false;

	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (hPr == 0) {		// aktuelles Projekt verwenden
		if (act_db != NULL) {
			*pfIsCompound = (NULL != act_db -> db_pIStorage) ? TRUE : FALSE;
			return true;
		} 
	} else {			// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if (NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) {
			*pfIsCompound = (NULL != db_p -> db_pIStorage) ? TRUE : FALSE;
			return true;
		}
	}

	return false;	// nicht festzustellen
}

extern "C"
BOOL FUNCTYPE CouldOpenTarget (HPROJECT hPr, BOOL *pfCouldOpen)
{
	if (NULL == pfCouldOpen) return false;
	SYNC_DBACCESS (g_pDbMutex, hPr);

	*pfCouldOpen = false;	// für alle Fälle

IStorage *pIStg = NULL;

	if (NULL == hPr) {		// aktuelles Projekt verwenden
		if (NULL != act_db && NULL != act_db -> db_pIStorage && NULL != act_db -> db_name) {
		HRESULT hr = StgOpenStorage (WideString(act_db -> db_name), NULL, 
									 STGM_TRANSACTED|STGM_READWRITE, 0, 0, &pIStg);
			if (SUCCEEDED(hr)) {
				pIStg -> Release();
				*pfCouldOpen = true; 
			}
			return true;
		} 
	} 
	else {			// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if (NULL != db_p -> db_name && NULL != db_p -> db_pIStorage) {
		HRESULT hr = StgOpenStorage (WideString(db_p -> db_name), NULL, 
									 STGM_TRANSACTED|STGM_READWRITE, 0, 0, &pIStg);
			if (SUCCEEDED(hr)) {
				pIStg -> Release();
				*pfCouldOpen = true; 
			}
			return true;
		}
	}

	return false;	// nicht festzustellen
}

extern "C" 
BOOL FUNCTYPE EXPORT01 IsDirty (HPROJECT hPr, BOOL *pfDirty)
{
	if (NULL == pfDirty) return false;

	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (hPr == 0) {		// aktuelles Projekt verwenden
		if (act_db != NULL) {
			*pfDirty = act_db -> db_fDirty;
			if (*pfDirty) return true;

		// jetzt noch related DB abfragen
		HPROJECT hPrRel = NULL;

			if (GetRelatedProject (hPr, &hPrRel) && NULL != hPrRel)
				return IsDirty (hPrRel, pfDirty);
			
			return true;
		}
	} 
	else {			// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if (NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) {
			*pfDirty = db_p -> db_fDirty;
			if (*pfDirty) return true;

		// jetzt noch related DB abfragen
		HPROJECT hPrRel = NULL;

			if (GetRelatedProject (hPr, &hPrRel) && NULL != hPrRel)
				return IsDirty (hPrRel, pfDirty);

			return true;
		}
	}
	return false;	// nicht festzustellen
}

extern "C" 
BOOL FUNCTYPE EXPORT01 SetDirty (HPROJECT hPr, BOOL fDirty)
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (hPr == 0) {		// aktuelles Projekt verwenden
		if (act_db != NULL) {
			act_db -> db_fDirty = fDirty;
			return true;
		}
	} 
	else {			// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if (NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) {
			db_p -> db_fDirty = fDirty;
			return true;
		}
	}
	return false;	// nicht festzustellen
}

///////////////////////////////////////////////////////////////////////////////
// Testen, ob eine DB geöffnet ist (HPROJECT ist noch gültig)
extern "C"
BOOL FUNCTYPE EXPORT01 IsOpened (HPROJECT hPr, BOOL *pfOpened)
{
	if (NULL == pfOpened) return false;

	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (NULL == hPr) {		// aktuelles Projekt verwenden
		if (NULL != act_db) {
			*pfOpened = (NULL != act_db -> db_name || NULL != act_db -> db_pIStorage) ? TRUE : FALSE;
			return true;
		}
	} 
	else {			// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		*pfOpened = (NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) ? TRUE : FALSE;
		return true;
	}

	return false;	// nicht festzustellen
}

///////////////////////////////////////////////////////////////////////////////
// zugehöriges Beschreibungsdaten-Projekt Setzen/Lesen
extern "C" 
BOOL FUNCTYPE EXPORT01 GetRelatedProject (HPROJECT hPr, HPROJECT *phPr)
{
	if (NULL == phPr) return false;

	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (hPr == 0) {		// aktuelles Projekt verwenden
		if (act_db != NULL) {
			*phPr = act_db -> db_hProjectRelated;
			return true;
		}
	} else {			// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if (NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) {
			*phPr = db_p -> db_hProjectRelated;
			return true;
		}
	}
	return false;	// nicht festzustellen
}

extern "C" 
BOOL FUNCTYPE EXPORT01 SetRelatedProject (HPROJECT hPr, HPROJECT hPrRel)
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (hPr == 0) {		// aktuelles Projekt verwenden
		if (act_db != NULL) {
			act_db -> db_hProjectRelated = hPrRel;
			return true;
		}
	} else {			// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if (NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) {
			db_p -> db_hProjectRelated = hPrRel;
			return true;
		}
	}
	return false;	// nicht festzustellen
}

///////////////////////////////////////////////////////////////////////////////
// zugehöriges übergeordnetes Projekt Lesen
extern "C" 
BOOL FUNCTYPE EXPORT01 GetTargetProject (HPROJECT hPr, HPROJECT *phPrTarget)
{
	if (NULL == phPrTarget) 
		return false;

	SYNC_DBACCESS (g_pDbMutex, hPr);
	if (0 != hPr) {
		for (int i = 0; i < MAXDB; i++) {
		DBASE *db_p = &db_table[i];
			
			if ((NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) &&
				hPr == db_p -> db_hProjectRelated)
			{
				*phPrTarget = (HPROJECT)(i+1);
				return true;
			}
		}
	}
	return false;	// nicht festzustellen
}

///////////////////////////////////////////////////////////////////////////////
// Liefert die zu dieser DB gehörende IdentMap
extern "C"
HRESULT FUNCTYPE EXPORT01 GetIdentMap (HPROJECT hPr, REFIID riid, LPVOID *ppIMap)
{
	if (NULL == ppIMap) return E_POINTER;
	*ppIMap = NULL;

	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (NULL == hPr) {		// aktuelles Projekt verwenden
		if (NULL != act_db) {
			if (NULL != act_db -> db_hProjectRelated)
				return E_UNEXPECTED;	// keine Pbd

			if (NULL == act_db -> db_pIIdentMap) {
				COM_TRY {
				WTRiASMDSMap Map (CLSID_TRiASMDSMap);
				HPROJECT hPrTarget = NULL;

					TX_VERIFY(GetTargetProject (hPr, &hPrTarget));
					THROW_FAILED_HRESULT(trias_nativeident::CNativeIdent::FillWithIdents (hPrTarget, Map, act_db -> db_fNoCaseIdents));
					act_db -> db_pIIdentMap = Map.detach();
				} COM_CATCH;
			}

			TX_ASSERT(NULL != act_db -> db_pIIdentMap);
			return act_db -> db_pIIdentMap -> QueryInterface (riid, ppIMap);
		}
	} else {			// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if (NULL != db_p -> db_hProjectRelated)
			return E_UNEXPECTED;	// keine Pbd

		if (NULL == db_p -> db_pIIdentMap) {
			COM_TRY {
			WTRiASMDSMap Map (CLSID_TRiASMDSMap);
			HPROJECT hPrTarget = NULL;

				TX_VERIFY(GetTargetProject (hPr, &hPrTarget));
				THROW_FAILED_HRESULT(trias_nativeident::CNativeIdent::FillWithIdents (hPrTarget, Map, db_p -> db_fNoCaseIdents));
				db_p -> db_pIIdentMap = Map.detach();
			} COM_CATCH;
		}

		TX_ASSERT(NULL != db_p -> db_pIIdentMap);
		return db_p -> db_pIIdentMap -> QueryInterface(riid, ppIMap);
	}
	return E_FAIL;	// nicht festzustellen
}

///////////////////////////////////////////////////////////////////////////////
// Liefert die zu dieser DB gehörende MCodeMap
extern "C"
HRESULT FUNCTYPE EXPORT01 GetMCodeMap (HPROJECT hPr, REFIID riid, LPVOID *ppIMap)
{
	if (NULL == ppIMap) return E_POINTER;
	*ppIMap = NULL;

	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (NULL == hPr) {		// aktuelles Projekt verwenden
		if (NULL != act_db) {
			if (NULL != act_db -> db_hProjectRelated)
				return E_UNEXPECTED;	// keine Pbd

			if (NULL == act_db -> db_pIMCodeMap) {
				COM_TRY {
				WTRiASMDSMap Map (CLSID_TRiASMDSMap);
				HPROJECT hPrTarget = NULL;

					TX_VERIFY(GetTargetProject (hPr, &hPrTarget));
					THROW_FAILED_HRESULT(trias_nativemerkmal::CNativeMerkmal::FillWithMCodes (hPrTarget, Map, act_db -> db_fNoCaseAttribs));
					act_db -> db_pIMCodeMap = Map.detach();
				} COM_CATCH;
			}

			TX_ASSERT(NULL != act_db -> db_pIMCodeMap);
			return act_db -> db_pIMCodeMap -> QueryInterface(riid, ppIMap);
		}
	} else {			// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if (NULL != db_p -> db_hProjectRelated)
			return E_UNEXPECTED;	// keine Pbd

		if (NULL == db_p -> db_pIMCodeMap) {
			COM_TRY {
			WTRiASMDSMap Map (CLSID_TRiASMDSMap);
			HPROJECT hPrTarget = NULL;

				TX_VERIFY(GetTargetProject (hPr, &hPrTarget));
				THROW_FAILED_HRESULT(trias_nativemerkmal::CNativeMerkmal::FillWithMCodes (hPrTarget, Map, db_p -> db_fNoCaseAttribs));
				db_p -> db_pIMCodeMap = Map.detach();
			} COM_CATCH;
		}

		TX_ASSERT(NULL != db_p -> db_pIMCodeMap);
		return db_p -> db_pIMCodeMap -> QueryInterface (riid, ppIMap);
	}
	return E_FAIL;	// nicht festzustellen
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen zur Verwaltung der Skalierungskoeffizienten
extern "C"
HRESULT FUNCTYPE EXPORT01 ReReadScaleKoeffs (HPROJECT hPr)
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (NULL == hPr) {		// aktuelles Projekt verwenden
		if (NULL != act_db) {
			act_db -> db_fKoeffsValid = FALSE;
			memset (&act_db -> db_Koeffs, '\0', sizeof(SCALEKOEFFS));
			return S_OK;
		}
	} else {				// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if (NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) {
			db_p -> db_fKoeffsValid = FALSE;
			memset (&db_p -> db_Koeffs, '\0', sizeof(SCALEKOEFFS));
			return S_OK;
		}
	}
	return E_FAIL;
}

extern "C"
HRESULT FUNCTYPE EXPORT01 GetScaleKoeffs (HPROJECT hPr, SCALEKOEFFS *pKoeffs)
{
	if (NULL == pKoeffs)
		return E_POINTER;

	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (NULL == hPr) {		// aktuelles Projekt verwenden
		if (NULL != act_db && act_db -> db_fKoeffsValid) {
			memcpy (pKoeffs, &act_db -> db_Koeffs, sizeof(SCALEKOEFFS));
			return S_OK;
		}
	} 
	else {				// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if ((NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) && db_p -> db_fKoeffsValid) {
			memcpy (pKoeffs, &db_p -> db_Koeffs, sizeof(SCALEKOEFFS));
			return S_OK;
		}
	}
	return E_FAIL;
}

extern "C"
HRESULT FUNCTYPE EXPORT01 SetScaleKoeffs (HPROJECT hPr, SCALEKOEFFS *pKoeffs)
{
	if (NULL == pKoeffs)
		return E_POINTER;

	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (NULL == hPr) {		// aktuelles Projekt verwenden
		if (NULL != act_db) {
			memcpy (&act_db -> db_Koeffs, pKoeffs, sizeof(SCALEKOEFFS));
			act_db -> db_fKoeffsValid = TRUE;
			return S_OK;
		}
	} 
	else {				// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if (NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) {
			memcpy (&db_p -> db_Koeffs, pKoeffs, sizeof(SCALEKOEFFS));
			db_p -> db_fKoeffsValid = TRUE;
			return S_OK;
		}
	}
	return E_FAIL;
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen zur Verwaltung des ConnectFilters
extern "C"
HRESULT FUNCTYPE EXPORT01 ResetConnectFilter (HPROJECT hPr)
{
#if defined(_USE_CONNECTFILTER)
	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (NULL == hPr) {		// aktuelles Projekt verwenden
		if (NULL != act_db) {
			act_db -> m_dbfConnectFilterValid = FALSE;
			act_db -> db_ConnectFilter.m_iMode = 0;
			act_db -> db_ConnectFilter.m_dXMin =
				act_db -> db_ConnectFilter.m_dXMax = 
				act_db -> db_ConnectFilter.m_dYMin = 
				act_db -> db_ConnectFilter.m_dYMax = 0.0;
			DELETE_VEC(act_db -> db_ConnectFilter.m_pX);
			DELETE_VEC(act_db -> db_ConnectFilter.m_pY);
			act_db -> db_ConnectFilter.m_lCnt = 0;
			DELETE_OBJ(act_db -> db_ConnectFilter.m_prsTree);
			return S_OK;
		}
	} 
	else {				// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if (NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) {
			db_p -> m_dbfConnectFilterValid = FALSE;
			db_p -> db_ConnectFilter.m_iMode = 0;
			db_p -> db_ConnectFilter.m_dXMin =
				db_p -> db_ConnectFilter.m_dXMax = 
				db_p -> db_ConnectFilter.m_dYMin = 
				db_p -> db_ConnectFilter.m_dYMax = 0.0;
			DELETE_VEC(db_p -> db_ConnectFilter.m_pX);
			DELETE_VEC(db_p -> db_ConnectFilter.m_pY);
			db_p -> db_ConnectFilter.m_lCnt = 0;
			DELETE_OBJ(db_p -> db_ConnectFilter.m_prsTree);
			return S_OK;
		}
	}
#endif // defined(_USE_CONNECTFILTER)
	return E_FAIL;
}

extern "C"
HRESULT FUNCTYPE EXPORT01 GetConnectFilter (HPROJECT hPr, CONNECTFILTEREX **ppFilter)
{
#if defined(_USE_CONNECTFILTER)
	if (NULL != ppFilter)
		*ppFilter = NULL;

	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (NULL == hPr) {		// aktuelles Projekt verwenden
		if (NULL != act_db && act_db -> m_dbfConnectFilterValid) {
			if (NULL != ppFilter)
				*ppFilter = &act_db -> db_ConnectFilter;
			return S_OK;
		}
	} 
	else {				// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if ((NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) && 
			db_p -> m_dbfConnectFilterValid) 
		{
			if (NULL != ppFilter)
				*ppFilter = &db_p -> db_ConnectFilter;
			return S_OK;
		}
	}
#endif // defined(_USE_CONNECTFILTER)
	return E_FAIL;
}

namespace {

	void CalculatePolygonContainer (double *pdX, double *pdY, long lCnt, CONNECTFILTEREX *pFilter)
	{
		pFilter->m_dXMin = pFilter->m_dYMin = DBL_MAX;
		pFilter->m_dXMax = pFilter->m_dYMax = -DBL_MAX;
		for (long i = 0; i < lCnt; ++i) {
			pFilter->m_dXMin = min(pFilter->m_dXMin, pdX[i]);
			pFilter->m_dYMin = min(pFilter->m_dYMin, pdY[i]);
			pFilter->m_dXMax = max(pFilter->m_dXMax, pdX[i]);
			pFilter->m_dYMax = max(pFilter->m_dYMax, pdY[i]);
		}
	}

	void InitRectContainer (double *pdX, double *pdY, long lCnt, CONNECTFILTEREX *pFilter)
	{
		_ASSERTE(2 == lCnt);
		pFilter->m_dXMin = pdX[0];
		pFilter->m_dYMin = pdY[0];
		pFilter->m_dXMax = pdX[1];
		pFilter->m_dYMax = pdY[1];
	}
}

extern "C"
HRESULT FUNCTYPE EXPORT01 SetConnectFilter (HPROJECT hPr, CONNECTFILTER *pFilter)
{
#if defined(_USE_CONNECTFILTER)
	if (NULL == pFilter)
		return E_POINTER;

	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (NULL == hPr) {		// aktuelles Projekt verwenden
		if (NULL != act_db) {
			(CONNECTFILTER &)act_db -> db_ConnectFilter = *pFilter;
			if (pFilter->m_iMode & CF_Polygon_Flag) {
				CalculatePolygonContainer(pFilter->m_pX, pFilter->m_pY, pFilter->m_lCnt, 
					&act_db -> db_ConnectFilter);
				ATLTRY(act_db -> db_ConnectFilter.m_prsTree = new CObjectGiST(pFilter));
				act_db -> m_dbfConnectFilterValid = 
					(NULL != act_db -> db_ConnectFilter.m_prsTree && 
						act_db -> db_ConnectFilter.m_prsTree->IsValid()) ? TRUE : FALSE;
			}
			else {
				InitRectContainer(pFilter->m_pX, pFilter->m_pY, pFilter->m_lCnt, 
					&act_db -> db_ConnectFilter);
				act_db -> db_ConnectFilter.m_prsTree = NULL;
				act_db -> m_dbfConnectFilterValid = TRUE;
			}
			return S_OK;
		}
	} 
	else {				// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if (NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) {
			(CONNECTFILTER &)db_p -> db_ConnectFilter = *pFilter;
			if (pFilter->m_iMode & CF_Polygon_Flag) {
				CalculatePolygonContainer(pFilter->m_pX, pFilter->m_pY, pFilter->m_lCnt, 
					&db_p -> db_ConnectFilter);
				ATLTRY(db_p -> db_ConnectFilter.m_prsTree = new CObjectGiST(pFilter));
				db_p -> m_dbfConnectFilterValid = 
					(NULL != db_p -> db_ConnectFilter.m_prsTree &&
						db_p -> db_ConnectFilter.m_prsTree->IsValid()) ? TRUE : FALSE;
			}
			else {
				InitRectContainer(pFilter->m_pX, pFilter->m_pY, pFilter->m_lCnt, 
					&db_p -> db_ConnectFilter);
				db_p -> db_ConnectFilter.m_prsTree = NULL;
				db_p -> m_dbfConnectFilterValid = TRUE;
			}
			return S_OK;
		}
	}
#endif // defined(_USE_CONNECTFILTER)
	return E_FAIL;
}

///////////////////////////////////////////////////////////////////////////////
// Verwalten des MCodes für den ObjGuid
extern "C"
HRESULT FUNCTYPE EXPORT01 GetPredefinedMCode (HPROJECT hPr, LONG *plMCode, PREDEFINEDMCODE rgWhich)
{
	if (NULL == plMCode)
		return E_POINTER;
	if (PREDEFINEDMCODE_LastDefined < rgWhich || rgWhich < 0)
		return E_INVALIDARG;

	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (NULL == hPr) {		// aktuelles Projekt verwenden
		if (NULL != act_db && 0L != act_db -> db_lMCode[rgWhich]) {
			*plMCode = act_db -> db_lMCode[rgWhich];
			return S_OK;
		}
	} 
	else {				// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if ((NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) && db_p -> db_lMCode[rgWhich]) {
			*plMCode = db_p -> db_lMCode[rgWhich];
			return S_OK;
		}
	}
	return E_FAIL;
}

extern "C"
HRESULT FUNCTYPE EXPORT01 SetPredefinedMCode (HPROJECT hPr, LONG lMCode, PREDEFINEDMCODE rgWhich)
{
	if (PREDEFINEDMCODE_LastDefined < rgWhich || rgWhich < 0)
		return E_INVALIDARG;

	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (NULL == hPr) {		// aktuelles Projekt verwenden
		if (NULL != act_db) {
			act_db -> db_lMCode[rgWhich] = lMCode;
			return S_OK;
		}
	} 
	else {				// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if (NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) {
			db_p -> db_lMCode[rgWhich] = lMCode;
			return S_OK;
		}
	}
	return E_FAIL;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert den Namen einer geöffneten Datenbank
extern "C"
HRESULT FUNCTYPE EXPORT01 GetDataBaseName (HPROJECT hPr, char *pBuffer, int iLen)
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (NULL == hPr) {		// aktuelles Projekt verwenden
		if (NULL != act_db) {
			_ASSERTE(NULL != act_db -> db_name);

		int iToCopy = max(size_t(iLen-1), strlen(act_db -> db_name));

			strncpy (pBuffer, act_db -> db_name, iToCopy);
			pBuffer[iToCopy] = '\0';
			return S_OK;
		}
	} 
	else {				// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if (NULL != db_p -> db_name) {
		int iToCopy = max(size_t(iLen-1), strlen(act_db -> db_name));

			strncpy (pBuffer, act_db -> db_name, iToCopy);
			pBuffer[iToCopy] = '\0';
			return S_OK;
		}
	}
	return E_FAIL;
}

///////////////////////////////////////////////////////////////////////////////
// NoCase Flag für Ident verwalten
extern "C" 
BOOL FUNCTYPE EXPORT01 GetIdentNoCase (HPROJECT hPr, BOOL *pfNoCase)
{
	if (NULL == pfNoCase) return false;

	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (hPr == 0) {		// aktuelles Projekt verwenden
		if (act_db != NULL) {
		HPROJECT hPrRel = NULL;

			if (GetRelatedProject(hPr, &hPrRel) && NULL != hPrRel) {
			short db_slot = (short)hPrRel -1;

				TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

				*pfNoCase = db_table[db_slot].db_fNoCaseIdents;
				return true;
			}
		}
	} else {			// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if (NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) {
		HPROJECT hPrRel = NULL;

			if (GetRelatedProject(hPr, &hPrRel) && NULL != hPrRel) {
				db_slot = (short)hPrRel -1;
				TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

				*pfNoCase = db_table[db_slot].db_fNoCaseIdents;
				return true;
			}
		}
	}
	return false;	// nicht festzustellen
}

extern "C" 
BOOL FUNCTYPE EXPORT01 SetIdentNoCase (HPROJECT hPr, BOOL fNoCase)
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (hPr == 0) {		// aktuelles Projekt verwenden
		if (act_db != NULL) {
		HPROJECT hPrRel = NULL;

			if (GetRelatedProject(hPr, &hPrRel) && NULL != hPrRel) {
			short db_slot = (short)hPrRel -1;

				TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

				db_table[db_slot].db_fNoCaseIdents = fNoCase;
				return true;
			}
		}
	} else {			// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if (NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) {
		HPROJECT hPrRel = NULL;

			if (GetRelatedProject(hPr, &hPrRel) && NULL != hPrRel) {
				db_slot = (short)hPrRel -1;
				TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

				db_table[db_slot].db_fNoCaseIdents = fNoCase;
				return true;
			}
		}
	}
	return false;	// nicht festzustellen
}

///////////////////////////////////////////////////////////////////////////////
// NoCase Flag für Attribs verwalten
extern "C" 
BOOL FUNCTYPE EXPORT01 GetAttribNoCase (HPROJECT hPr, BOOL *pfNoCase)
{
	if (NULL == pfNoCase) return false;

	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (hPr == 0) {		// aktuelles Projekt verwenden
		if (act_db != NULL) {
		HPROJECT hPrRel = NULL;

			if (GetRelatedProject(hPr, &hPrRel) && NULL != hPrRel) {
			short db_slot = (short)hPrRel -1;

				TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

				*pfNoCase = db_table[db_slot].db_fNoCaseAttribs;
				return true;
			}
		}
	} else {			// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if (NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) {
		HPROJECT hPrRel = NULL;

			if (GetRelatedProject(hPr, &hPrRel) && NULL != hPrRel) {
				db_slot = (short)hPrRel -1;
				TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

				*pfNoCase = db_table[db_slot].db_fNoCaseAttribs;
				return true;
			}
		}
	}
	return false;	// nicht festzustellen
}

extern "C" 
BOOL FUNCTYPE EXPORT01 SetAttribNoCase (HPROJECT hPr, BOOL fNoCase)
{
	SYNC_DBACCESS (g_pDbMutex, hPr);

	if (hPr == 0) {		// aktuelles Projekt verwenden
		if (act_db != NULL) {
		HPROJECT hPrRel = NULL;

			if (GetRelatedProject(hPr, &hPrRel) && NULL != hPrRel) {
			short db_slot = (short)hPrRel -1;

				TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

				db_table[db_slot].db_fNoCaseAttribs = fNoCase;
				return true;
			}
		}
	} else {			// gegebenes Projekt verwenden
	short db_slot = (short)hPr -1;

		TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

	DBASE *db_p = &db_table[db_slot];

		if (NULL != db_p -> db_name || NULL != db_p -> db_pIStorage) {
		HPROJECT hPrRel = NULL;

			if (GetRelatedProject(hPr, &hPrRel) && NULL != hPrRel) {
				db_slot = (short)hPrRel -1;
				TX_ASSERT(0 <= db_slot && db_slot < MAXDB);

				db_table[db_slot].db_fNoCaseAttribs = fNoCase;
				return true;
			}
		}
	}
	return false;	// nicht festzustellen
}

