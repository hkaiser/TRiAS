// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 23.09.2001 20:16:25 
//
// @doc
// @module CatSimpleCache.cpp | Definition of the <c CCatSimpleCache> class

#include "trias03p.hxx"
#include "trias03.h"

#include <Atl/Ciid.h>
#include <TrCatIDs.h>
#include <time.h>

#include "CatSimpleCache.h"

///////////////////////////////////////////////////////////////////////////////
// Component categories
// 19BBA822-01AA-4A90-B8E8-3F9D095A1216
EXTERN_C const CATID __declspec(selectany) CATID_TRiASStatistValue = 
	{ 0x19BBA822, 0x01AA, 0x4A90, 0xB8, 0xE8, 0x3F, 0x9D, 0x09, 0x5A, 0x12, 0x16 };

// 5784231F-3487-4EA9-ACE8-C5EADDB58794
EXTERN_C const CATID __declspec(selectany) CATID_TRiASStatistValuesContainer = 
	{ 0x5784231F, 0x3487, 0x4EA9, 0xAC, 0xE8, 0xC5, 0xEA, 0xDD, 0xB5, 0x87, 0x94 };

// 079639C6-3123-101C-BB62-00AA0018497C
EXTERN_C const CATID __declspec(selectany) CATID_TRiASDBEngine = 
	{ 0x079639C6, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C };

///////////////////////////////////////////////////////////////////////////////
// SmartIF's etc.
DefineEnumerator2(CLSID, IID_IEnumCLSID);

/////////////////////////////////////////////////////////////////////////////
// CCatSimpleCache

// Implementation des StdMgr's
HRESULT CCatSimpleCache::Aggr_EnumClassesOfCategories(
	ULONG cImplemented, CATID rgcatidImpl[], ULONG cRequired, CATID rgcatidReq[], IEnumCLSID **ppenumClsid)
{
	_ASSERTE(m_StdCatMgr.IsValid());

__Interface<ICatInformation> CatInfo;

	if (SUCCEEDED(m_StdCatMgr -> QueryInterface(CatInfo.ppi())))
		return CatInfo -> EnumClassesOfCategories(cImplemented, rgcatidImpl, cRequired, rgcatidReq, ppenumClsid);
	return E_NOINTERFACE;
}

// eigene Implementation, die ggf. auf einen existierenden Cache zurückgreift
STDMETHODIMP CCatSimpleCache::EnumClassesOfCategories(
	ULONG cImplemented, CATID rgcatidImpl[], ULONG cRequired, CATID rgcatidReq[], IEnumCLSID **ppenumClsid)
{
	if (cImplemented != 1 || cRequired != 0)	// das können wir nicht
		return Aggr_EnumClassesOfCategories(cImplemented, rgcatidImpl, cRequired, rgcatidReq, ppenumClsid);

	if (NULL == ppenumClsid)
		return E_POINTER;
	*ppenumClsid = NULL;

// Cache für diese ComCat sicher initialisieren und Enum auslesen
	if (S_OK != InitializeCache(rgcatidImpl[0], VARIANT_FALSE))
		return Aggr_EnumClassesOfCategories(cImplemented, rgcatidImpl, cRequired, rgcatidReq, ppenumClsid);

// eigenen Enumerator besorgen
__Interface<IEnumCLSID> Enum;

	RETURN_FAILED_HRESULT(EnumClassesOfCategoryFromCache(rgcatidImpl[0], Enum.ppi()));

	*ppenumClsid = Enum.detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ICatSimpleCache
STDMETHODIMP CCatSimpleCache::InitializeCache(CATID catidImpl, VARIANT_BOOL fForce)
{
// sicherstellen, das es eine ComCat von uns ist
	if (catidImpl != CATID_TRiASCoordsystem && 
		catidImpl != CATID_TRiASSelfRegister &&
		catidImpl != CATID_TRiASDBEngine &&
		catidImpl != CATID_TRiASExportModule &&
		catidImpl != CATID_TRiASImportModule &&
		catidImpl != CATID_TRiASGeoComponent &&
		catidImpl != CATID_TRiASGeoComponentContainer &&
		catidImpl != CATID_TRiASStatistValue &&
		catidImpl != CATID_TRiASStatistValuesContainer)
	{
		return S_FALSE;		// normalen Weg gehen
	}

// nachsehen, ob der Cache bereits initialisiert ist
	if (!fForce && S_OK == IsCacheInitialized (catidImpl)) 
		return S_OK;	// nothing to do

// Cache neu initialisieren 
	ClearCache (catidImpl);

__Interface<IEnumCLSID> Enum;
CIID Guid;
CRegKey regCfg, regCatIds;

	if (ERROR_SUCCESS != regCfg.Open(HKEY_CURRENT_USER, "Software") ||
		ERROR_SUCCESS != regCfg.Open(regCfg, REG_COMPANY_KEY) ||
		ERROR_SUCCESS != regCfg.Open(regCfg, REG_PRODUCT_KEY))
	{
		return E_FAIL;		// so weit sollten die Keys existieren
	}

// MasterKey sicherstellen
LONG lErrCode = ERROR_SUCCESS;

	if (ERROR_SUCCESS != (lErrCode = regCatIds.Open(regCfg, "Component Categories")) &&
		ERROR_SUCCESS != (lErrCode = regCatIds.Create(regCfg, "Component Categories")))
	{
		return HRESULT_FROM_WIN32(lErrCode);		// Key läßt sich nicht erzeugen
	}

// Komponentkategorie erzeugen
CRegKey regCatId;
CIID CatId (catidImpl);

	if (ERROR_SUCCESS != (lErrCode = regCatId.Open(regCatIds, os_string(CatId).c_str())) &&
		ERROR_SUCCESS != (lErrCode = regCatId.Create(regCatIds, os_string(CatId).c_str())))
	{
		return HRESULT_FROM_WIN32(lErrCode);		// Key läßt sich nicht erzeugen
	}

	regCatId.DeleteValue("LastAccess");
	RETURN_FAILED_HRESULT(Aggr_EnumClassesOfCategories(1, &catidImpl, 0, NULL, Enum.ppi()));
	for (Enum -> Reset(); S_OK == Enum -> Next(1, &Guid, NULL); /**/)
	{
	CRegKey regGuid;

		if (ERROR_SUCCESS != (lErrCode = regGuid.Open(regCatId, os_string(Guid).c_str())) && 
			ERROR_SUCCESS != (lErrCode = regGuid.Create(regCatId, os_string(Guid).c_str())))
		{
			return HRESULT_FROM_WIN32(lErrCode);	// Key läßt sich nicht erzeugen
		}
	}

// Cache als gültig kennzeichnen
	lErrCode = regCatId.SetValue(time(NULL), "LastAccess");		// Cache ist gültig
	return ERROR_SUCCESS == lErrCode ? S_OK : HRESULT_FROM_WIN32(lErrCode);
}

// IsCacheInitialized
STDMETHODIMP CCatSimpleCache::IsCacheInitialized(CATID catidImpl)
{
CRegKey regCatId;
CIID CatId (catidImpl);

	if (ERROR_SUCCESS != regCatId.Open(HKEY_CURRENT_USER, "Software") ||
		ERROR_SUCCESS != regCatId.Open(regCatId, REG_COMPANY_KEY) ||
		ERROR_SUCCESS != regCatId.Open(regCatId, REG_PRODUCT_KEY) ||
		ERROR_SUCCESS != regCatId.Open(regCatId, "Component Categories") ||
		ERROR_SUCCESS != regCatId.Open(regCatId, os_string(CatId).c_str()))
	{
		return S_FALSE;		// so weit sollten die Keys existieren
	}

DWORD dwTime = 0;

	if (ERROR_SUCCESS != regCatId.QueryValue(dwTime, "LastAccess") || dwTime == 0)
		return S_FALSE;		// Cache existent, aber nicht vollständig
	return S_OK;
}

// ClearCache
STDMETHODIMP CCatSimpleCache::ClearCache(CATID catidImpl)
{
CRegKey regCatId;
CIID CatId (catidImpl);

	if (ERROR_SUCCESS != regCatId.Open(HKEY_CURRENT_USER, "Software") ||
		ERROR_SUCCESS != regCatId.Open(regCatId, REG_COMPANY_KEY) ||
		ERROR_SUCCESS != regCatId.Open(regCatId, REG_PRODUCT_KEY) ||
		ERROR_SUCCESS != regCatId.Open(regCatId, "Component Categories"))
	{
		return S_FALSE;		// so weit sollten die Keys existieren
	}

LONG lErrCode = regCatId.RecurseDeleteKey(os_string(CatId).c_str());

	return ERROR_SUCCESS == lErrCode ? S_OK : HRESULT_FROM_WIN32(lErrCode);
}

// ClearCacheAll
STDMETHODIMP CCatSimpleCache::ClearCacheAll()
{
CRegKey regCatId;

	if (ERROR_SUCCESS != regCatId.Open(HKEY_CURRENT_USER, "Software") ||
		ERROR_SUCCESS != regCatId.Open(regCatId, REG_COMPANY_KEY) ||
		ERROR_SUCCESS != regCatId.Open(regCatId, REG_PRODUCT_KEY))
	{
		return S_FALSE;		// so weit sollten die Keys existieren
	}

LONG lErrCode = regCatId.RecurseDeleteKey("Component Categories");

	return ERROR_SUCCESS == lErrCode ? S_OK : HRESULT_FROM_WIN32(lErrCode);
}

// EnumClassesOfCategoryFromCache
STDMETHODIMP CCatSimpleCache::EnumClassesOfCategoryFromCache(CATID catidImpl, IEnumCLSID **ppenumClsid)
{
	if (NULL == ppenumClsid)
		return E_POINTER;
	*ppenumClsid = NULL;

	if (S_OK != IsCacheInitialized(catidImpl))
		return E_UNEXPECTED;

CRegKey regCatId;
CIID CatId (catidImpl);

	if (ERROR_SUCCESS != regCatId.Open(HKEY_CURRENT_USER, "Software") ||
		ERROR_SUCCESS != regCatId.Open(regCatId, REG_COMPANY_KEY) ||
		ERROR_SUCCESS != regCatId.Open(regCatId, REG_PRODUCT_KEY) ||
		ERROR_SUCCESS != regCatId.Open(regCatId, "Component Categories") ||
		ERROR_SUCCESS != regCatId.Open(regCatId, os_string(CatId).c_str()))
	{
		return S_FALSE;		// so weit sollten die Keys existieren
	}

// eigenen Enumerator besorgen
NEnumCLSID *pEnum = NULL;

	ATLTRY(pEnum = new NEnumCLSID);
	if (NULL == pEnum)
		return E_OUTOFMEMORY;

__Interface<IEnumCLSID> Enum(pEnum, false);		// Konstruktor hinterläßt RefCnt==1

// Registry durchgehen
DWORD dwIndex = 0;
char cbEnumKey[_MAX_PATH];

	while (ERROR_SUCCESS == ::RegEnumKey(regCatId, dwIndex++, cbEnumKey, _MAX_PATH)) {
	CIID Guid (cbEnumKey, CIID::INITCIID_InitFromGuid);

		if (Guid.IsValid())
			pEnum -> AddItem(Guid);
	}

	RETURN_FAILED_HRESULT(Enum -> Reset());
	*ppenumClsid = Enum.detach();
	return S_OK;
}
