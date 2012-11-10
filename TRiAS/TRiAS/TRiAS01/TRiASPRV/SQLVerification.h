// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 22.05.2001 08:24:57 
//
// @doc
// @module SQLVerification.h | Declaration of several verification functions

#if !defined(_SQLVERIFICATION_H__7C6281C6_5860_46F7_81D3_A5932934792B__INCLUDED_)
#define _SQLVERIFICATION_H__7C6281C6_5860_46F7_81D3_A5932934792B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"

///////////////////////////////////////////////////////////////////////////////
// Objekttypen
#if !defined(OTPunkt)
#define OTPunkt			0x01
#define OTLinie			0x02
#define OTFlaeche		0x04
#define OTText			0x08
#define OTKO			0x10
#define OTSachObjekt	0x20	// zusätzliches Flag (BLOB - Flag)
#define OTAll	(OTPunkt|OTLinie|OTFlaeche|OTText)
#endif // !defined(OTPunkt)

enum wkbGeometryType
{
    wkbUnknown = 0,
    wkbPoint = 1,
    wkbLineString = 2,
    wkbPolygon = 3,
    wkbMultiPoint = 4,
    wkbMultiLineString = 5,
    wkbMultiPolygon = 6,
    wkbGeometryCollection = 7,
    wkbNone = 100,
    wkbPoint25D = 0x8001,
    wkbLineString25D = 0x8002,
    wkbPolygon25D = 0x8003
};

///////////////////////////////////////////////////////////////////////////////
// required data
typedef struct tagOBJTYPEDATA {
	UINT uiResId;
	LPCOLESTR pcoleObjTypeName;
	UINT uiResIdDesc;
	LPCOLESTR pcoleGeomName;
	DWORD dwType;
	UINT uiOGCType;
} OBJTYPEDATA;

extern OBJTYPEDATA __declspec(selectany) s_rgTypes[] = {
	{ IDS_POINTS, L"POINTS", IDS_POINTGEOMETRY, L"OGIS_GEOMETRY_POINT", OTPunkt, wkbPoint, },
	{ IDS_LINES, L"LINES", IDS_LINEGEOMETRY, L"OGIS_GEOMETRY_LINE", OTLinie, wkbLineString, },
	{ IDS_AREAS, L"AREAS", IDS_AREAGEOMETRY, L"OGIS_GEOMETRY_AREA", OTFlaeche, wkbPolygon, },
	{ IDS_TEXTS, L"TEXTS", IDS_TEXTGEOMETRY, L"OGIS_GEOMETRY_TEXT", OTText, wkbPoint },
};

///////////////////////////////////////////////////////////////////////////////
// Sicherstellen, daß eine Tabelle in der From clause aufgeführt ist
inline
bool VerifyTableIsGiven (IParser *pIParser, BSTR bstrTableName)
{
// Liste der abgefragten Tabellen holen
CComPtr<ISelectStmt> Select;

	RETURN_FAILED_HRESULT(pIParser -> get_SelectStmt(&Select));

CComPtr<ITableIdentList> TableIdentList;

	RETURN_FAILED_HRESULT(Select -> get_TableIdentList(&TableIdentList));
	if (TableIdentList == NULL) return false;

CComPtr<IUnknown> UnkEnum;

	RETURN_FAILED_HRESULT(TableIdentList -> get__NewEnum(&UnkEnum));

CComQIPtr<IEnumVARIANT> Tables(UnkEnum);
CComVariant v;
CComBSTR bstrT(bstrTableName);

	_ASSERTE(Tables != NULL);
	for (Tables -> Reset(); S_OK == Tables -> Next(1, &v, NULL); /**/) {
		_ASSERTE(V_ISDISPATCH(&v));

	CComQIPtr<ITableIdent> Table = V_DISPATCH(&v);
	CComBSTR bstrTable, bstrAlias;
	INT_PTR lIdent = NULL;

		if (Table == NULL) return false;

	// TabellenNamen vergleichen
		RETURN_FAILED_HRESULT(Table -> get_Name(&bstrTable));
		bstrTable = RemoveQuotes(bstrTable);
		if (VarBstrCmp(bstrTable.m_str, bstrT.m_str, LOCALE_USER_DEFAULT, 0) == VARCMP_EQ)
			return true;

	// ggf. wird nach Alias gesucht
		if (S_OK == Table -> get_Alias(&bstrAlias)) {
			bstrAlias = RemoveQuotes(bstrAlias);
			if (VarBstrCmp(bstrAlias.m_str, bstrT.m_str, LOCALE_USER_DEFAULT, 0) == VARCMP_EQ)
				return true;
		}
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// herauslösen des Objekttypes aus dem kombinierten Tabellennamen
inline
HRESULT SplitTableName (CComBSTR &rbstrTableName, DWORD *pdwOGCType = NULL, DWORD *pdwTRiASTypes = NULL)
{
	_ASSERTE(NULL != rbstrTableName.m_str);

LPCOLESTR pT = wcsrchr(rbstrTableName, TABLE_OBJTYPE_DELIMITER);

	if (NULL != pdwOGCType)
		*pdwOGCType = 0;
	if (NULL != pdwTRiASTypes)
		*pdwTRiASTypes = 0;

	if (NULL == pT) {
	// kein Geometriezusatz am Tablename --> alle Typen
		if (NULL != pdwTRiASTypes)
			*pdwTRiASTypes = OTAll;
		return S_FALSE;
	}
		
int iLen = wcslen(pT) - (TABLE_OBJTYPE_DELIMITER_STR_PREFIX_LEN+TABLE_OBJTYPE_DELIMITER_STR_POSTFIX_LEN);

	if (iLen > 0) {
		for (int i = 0; i < _countof(s_rgTypes); ++i) {
			if (*(pT + 1) != TABLE_OBJTYPE_DELIMITER_PREFIX)
				continue;		// Geometrietyp ist als '(TYP)' angehängt

			if (!wcsncmp (pT+TABLE_OBJTYPE_DELIMITER_STR_PREFIX_LEN, s_rgTypes[i].pcoleObjTypeName, iLen)) {
				rbstrTableName = CComBSTR(pT-rbstrTableName, rbstrTableName).Detach();
				if (NULL != pdwOGCType)
					*pdwOGCType = s_rgTypes[i].uiOGCType;
				if (NULL != pdwTRiASTypes)
					*pdwTRiASTypes = s_rgTypes[i].dwType;
				return S_OK;
			}
		}
	}

// kein Geometriezusatz am Tablename --> alle Typen
	if (NULL != pdwTRiASTypes)
		*pdwTRiASTypes = OTAll;
	return S_OK;
}

#endif // !defined(_SQLVERIFICATION_H__7C6281C6_5860_46F7_81D3_A5932934792B__INCLUDED_)
