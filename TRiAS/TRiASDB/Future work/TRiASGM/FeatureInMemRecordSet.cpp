// @doc 
// @module FeatureInMemRecordSet.cpp | Tabelle der Geomtriefelder und -Typen

#include "stdafx.h"

#include <GFWSysTbl.h>

#include <Array.h>
#include <xtension.h>
#include <HeaderEntry.h>

#include "Strings.h"
#include "FeatureInMemRecordSet.h"

/////////////////////////////////////////////////////////////////////////////
// globale Funktionen
long GetGeometryType (DWORD dwTypes, BOOL *pfHasTexts = NULL);

/////////////////////////////////////////////////////////////////////////////
// 
CFeatureInMemRecordSet::CFeatureInMemRecordSet(BSTR bstrName)
{
	USES_CONVERSION;

	SetSourceDatabase(bstrName);
	SetSourceTable(CComBSTR(GFWFeaturesTableName));
}

CFeatureInMemRecordSet::~CFeatureInMemRecordSet()
{
}

namespace {

GFWFieldInfo g_Fields[] = 
{
	{ NULL, gdbText, 1, 0, 0L, gdbSortNeutral, NULL, NULL, NULL, NULL, 0L, 0L, },	// Ident
	{ NULL, gdbLong, 2, 0, 0L, gdbSortNeutral, NULL, NULL, NULL, NULL, 0L, 0L, },	// Types
	{ NULL, gdbText, 3, 0, 0L, gdbSortNeutral, NULL, NULL, NULL, NULL, 0L, 0L, },	// KText
	{ NULL, gdbText, 4, 0, 0L, gdbSortNeutral, NULL, NULL, NULL, NULL, 0L, 0L, },	// LText
};

LPCSTR g_cbFieldNames[] =
{
	g_cbName,
	g_cbGeometryType,
	g_cbPrimaryGeometryFieldName,
	g_cbDescription,
};

} // namespace

HRESULT CFeatureInMemRecordSet::Initialize()
{
// Initialize object
	RETURN_FAILED_HRESULT(GMCInMemoryRecordset::Initialize());

// add fields
	try {
	// Feldnamen initialisieren
		for (int i = 0; i < _countof(g_Fields); i++) {
			g_Fields[i].m_Name = CComBSTR(g_cbFieldNames[i]).Detach();
			g_Fields[i].m_SourceField = CComBSTR(g_cbFieldNames[i]).Detach();
		}

	// Felder definieren
		THROW_FAILED_HRESULT(SetMetadata (_countof(g_Fields), g_Fields));

	} catch (_com_error &e) {
		for (int i = 0; i < _countof(g_Fields); i++) {
			SysFreeString(g_Fields[i].m_Name);
			g_Fields[i].m_Name = NULL;
			SysFreeString(g_Fields[i].m_SourceField);
			g_Fields[i].m_SourceField = NULL;
		}
		return _COM_ERROR(e);
	}

// Speicher wieder freigeben
	for (int i = 0; i < _countof(g_Fields); i++) {
		SysFreeString(g_Fields[i].m_Name);
		g_Fields[i].m_Name = NULL;
		SysFreeString(g_Fields[i].m_SourceField);
		g_Fields[i].m_SourceField = NULL;
	}

	return S_OK;
}

HRESULT CFeatureInMemRecordSet::AddRecord (
	LPCSTR pcName, DWORD dwTypes, LPCSTR pcGeoFieldName, LPCSTR pcDesc)
{
	try {
	BOOL fHasTexts = FALSE;
	long lType = GetGeometryType(dwTypes, &fHasTexts);

		ASSERT(!fHasTexts);		// Texte dürfen nicht mit was anderem kombiniert sein
		if (lType == -1 && strcmp(pcGeoFieldName, g_cbNil))
			return S_OK;		// 'leere' Objektklasse

//		if (0 == lType)
//			lType = -1L;

	CSafeArray sa (VT_VARIANT, _countof(g_Fields));

		{
		CSafeArrayLock<VARIANT> lock(sa);
		
			if (gdbGraphicsText == lType) {
			CComVariant v1(pcName);
			CComVariant v2(gdbGraphic);
			CComVariant v3(pcGeoFieldName);
			CComVariant v4(g_cbSpace);

				THROW_FAILED_HRESULT(v1.Detach(lock));
				THROW_FAILED_HRESULT(v2.Detach(lock+1));
				THROW_FAILED_HRESULT(v3.Detach(lock+2));
				THROW_FAILED_HRESULT(v4.Detach(lock+3));
			} else {
			CComVariant v1(pcName);
			CComVariant v2(lType);
			CComVariant v3(pcGeoFieldName);
			CComVariant v4((NULL != pcDesc && '\0' != *pcDesc) ? pcDesc : g_cbSpace);

				THROW_FAILED_HRESULT(v1.Detach(lock));
				THROW_FAILED_HRESULT(v2.Detach(lock+1));
				THROW_FAILED_HRESULT(v3.Detach(lock+2));
				THROW_FAILED_HRESULT(v4.Detach(lock+3));
			}
		}
		
		THROW_FAILED_HRESULT(GMCInMemoryRecordset::AddRecord (sa));

	} catch (_com_error &e) {
		ASSERT(_COM_ERROR(e));
		return _COM_ERROR(e);
	}
	return S_OK;
}

