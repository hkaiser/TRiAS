// @doc 
// @module OKSInMemRecordSet.cpp | ObjektklassenTabelle

#include "stdafx.h"

#include <Array.h>
#include <xtension.h>
#include <HeaderEntry.h>

#include "Strings.h"
#include "OKSInMemRecordSet.h"

using namespace trias_nativeheader;

COKSInMemRecordSet::COKSInMemRecordSet(HPROJECT hPr, BSTR bstrName)
	: m_hPr(hPr)
{
	USES_CONVERSION;

	SetSourceDatabase(bstrName);
	SetSourceTable(A2OLE(g_cbMetaData));

char cbBuffer[_MAX_PATH];
CDBHeader Hdr (m_hPr, g_cbIdentBaseHdr);

	m_iIdBase = 16;
	if (SUCCEEDED(Hdr.GetHeaderEntry (cbBuffer, _countof(cbBuffer)))) 
		m_iIdBase = atol(cbBuffer);
	ASSERT(16 == m_iIdBase || 10 == m_iIdBase);
}

COKSInMemRecordSet::~COKSInMemRecordSet()
{
}

namespace {

GFWFieldInfo g_Fields[] = 
{
	{ NULL, gdbText, 1, 0, 0L, gdbSortNeutral, NULL, NULL, NULL, NULL, 0L, 0L, },	// Ident
	{ NULL, gdbText, 2, 0, 0L, gdbSortNeutral, NULL, NULL, NULL, NULL, 0L, 0L, },	// Types
	{ NULL, gdbText, 3, 0, 0L, gdbSortNeutral, NULL, NULL, NULL, NULL, 0L, 0L, },	// KText
	{ NULL, gdbText, 4, 0, 0L, gdbSortNeutral, NULL, NULL, NULL, NULL, 0L, 0L, },	// LText
};

LPCSTR g_cbFieldNames[] =
{
	g_cbIdentifikator,
	g_cbObjekttypen,
	g_cbKurztext,
	g_cbLangtext,
};

} // namespace

HRESULT COKSInMemRecordSet::Initialize()
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

HRESULT COKSInMemRecordSet::AddRecord (
	long lIdent, DWORD dwTypes, LPCSTR pcName, LPCSTR pcDesc)
{
	try {
	CSafeArray sa (VT_VARIANT, _countof(g_Fields));

		{
		CSafeArrayLock<VARIANT> lock(sa);
		char cbBuffer[32];

		CComVariant v1(ultoa (lIdent, cbBuffer, m_iIdBase));
		CComVariant v2(RetrieveObjectTypes(dwTypes).c_str());
		CComVariant v3(pcName);
		CComVariant v4(pcDesc);

			THROW_FAILED_HRESULT(v1.Detach(lock));
			THROW_FAILED_HRESULT(v2.Detach(lock+1));
			THROW_FAILED_HRESULT(v3.Detach(lock+2));
			THROW_FAILED_HRESULT(v4.Detach(lock+3));
		}
		
		THROW_FAILED_HRESULT(GMCInMemoryRecordset::AddRecord (sa));

	} catch (_com_error &e) {
		ASSERT(_COM_ERROR(e));
		return _COM_ERROR(e);
	}
	return S_OK;
}

os_string COKSInMemRecordSet::RetrieveObjectTypes (DWORD dwTypes)
{
os_string str;

	if (dwTypes & OTPunkt) 
		str = g_cbPunkte;

	if (dwTypes & OTLinie) {
		if (str.size() > 0)
			str += ", ";
		str += g_cbLinien;
	}
	if (dwTypes & OTFlaeche) {
		if (str.size() > 0)
			str += ", ";
		str += g_cbFlaechen;
	}
	if (dwTypes & OTText) {
		if (str.size() > 0)
			str += ", ";
		str += g_cbTexte;
	}
	return str;
}
