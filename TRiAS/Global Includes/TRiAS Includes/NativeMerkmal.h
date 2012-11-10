// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 01.09.99 11:50:11 
//
// @doc
// @module NativeMerkmal.h | Declaration of the <c CNativeMerkmal> class

#if !defined(_NATIVEMERKMAL_H__B7B83A43_ECA0_11D1_8624_00600875138A__INCLUDED_)
#define _NATIVEMERKMAL_H__B7B83A43_ECA0_11D1_8624_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/std/set>
#include <ospace/std/vector>

#include <risdb.h>
#include <xtension.h>

struct ITRiASMDSMap;

namespace trias_nativemerkmal {

///////////////////////////////////////////////////////////////////////////////
// Zugriff auf Merkmals-Daten in TRiAS-Datenbank

class _TRIAS01_ENTRY CNativeMerkmal
{
public:
	enum FEATURETARGET {
		FEATURETARGET_Object = 'a',	// Merkmal eines Objektes
		FEATURETARGET_View = 'b',	// Merkmal einer Ansicht
		FEATURETARGET_Ident = 'c',	// Merkmal eines Identifikators
	};
	enum RANGEENUM {
		RANGEENUM_INCLUSIVESTART = 0,		// DBRANGE_INCLUSIVESTART
		RANGEENUM_INCLUSIVEEND = 0,			// DBRANGE_INCLUSIVEEND
		RANGEENUM_EXCLUSIVESTART = 0x01,	// DBRANGE_EXCLUSIVESTART
		RANGEENUM_EXCLUSIVEEND = 0x02,		// DBRANGE_EXCLUSIVEEND
		RANGEENUM_PREFIX = 0x08,			// DBRANGE_PREFIX

	// helper
		RANGEENUM_INCLUSIVEALL = 0,
		RANGEENUM_EXCLUSIVEALL = 0x03,
	};

private:
	HPROJECT m_hPr;				// Projekt-Handle
	INT_PTR m_lMCode;			// TargetMerkmal
	LONG m_lRecNo;				// zugehörige Satznummer
	FEATURETARGET m_rgTarget;	// targetTyp
	bool m_fReportPbdErrors;	// entstehende Pbd-Fehler melden/nicht melden

protected:
	static HRESULT CALLBACK StorePBDMerkmale (INT_PTR lMCode, UINT_PTR dwData);
	static HRESULT CALLBACK StoreObjectsVector (INT_PTR lObject, DWORD dwType, UINT_PTR dwData);

	HRESULT Initialize (BOOL fCreate);

	HRESULT CondCorrectFDBTError (struct kdbt &kdbt, long lRecNo);
	HRESULT ObjectHasIdent (INT_PTR lONr, INT_PTR lIdent);
	HRESULT EndOfRangeReached (INT_PTR lONr, LPCSTR pcEnd, int iSrchLen, RANGEENUM rgMode);
	DWORD GetObjectType (INT_PTR lONr);

public:
	CNativeMerkmal (HPROJECT hPr, LONG lMCode = 0L, BOOL fCreate = FALSE);
	CNativeMerkmal (HPROJECT hPr, FEATURETARGET rgTarget, LONG lMCode = 0L, BOOL fCreate = FALSE);
	~CNativeMerkmal() {}

	void ReportPbdErrors (BOOL fReport) { m_fReportPbdErrors = (fReport ? true : false); }
	BOOL GetReportPbdErrors() { return m_fReportPbdErrors ? TRUE : FALSE; }

	static HRESULT FillWithMCodes (HPROJECT hPr, ITRiASMDSMap *pIMap, bool fNoCase);
	static HRESULT EnumMerkmaleDB (HPROJECT hPr, HRESULT (CALLBACK *pFcn)(INT_PTR, UINT_PTR), UINT_PTR dwData);
	static HRESULT EnumMerkmale (HPROJECT hPr, HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData);
	static HRESULT FindMerkmal (HPROJECT hPr, LPCSTR pcItem, LONG *plMCode);

	static HRESULT FindFromName (HPROJECT hPr, LPCSTR pcName, INT_PTR lIdent = 0, VARIANT_BOOL fCaseSensitive = VARIANT_TRUE, INT_PTR *plMCode = NULL);

	HRESULT EnumObjects(HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData, INT_PTR lIdent = 0, LPCSTR pcStart = 0, LPCSTR pcEnd = 0, RANGEENUM dwMode = RANGEENUM_INCLUSIVEALL);

	HRESULT GetObjects (vector<INT_PTR> &rObjs, INT_PTR lIdent = 0, LPCSTR pcStart = NULL, LPCSTR pcEnd = NULL, RANGEENUM rgMode = RANGEENUM_INCLUSIVEALL);

	HRESULT GetName (LPSTR pBuffer, int iLen);				// KurzText liefern
	HRESULT GetNameDB (LPSTR pBuffer, int iLen, BOOL fMakeDefault = TRUE, BOOL fCorrectName = TRUE);
	HRESULT SetName (LPCSTR pcNewName);
	HRESULT GetDescription (LPSTR pBuffer, int iLen);		// LangText liefern
	HRESULT GetDescriptionDB (LPSTR pBuffer, int iLen, BOOL fMakeDefault = TRUE, BOOL fCorrectName = TRUE);
	HRESULT SetDescription (LPCSTR pcNewDesc);

	HRESULT SetTyp (int rgType);
	HRESULT SetReadOnly (BOOL fReadOnly);
	HRESULT SetSystem (BOOL fSystem);

	DWORD GetFullType();

	HRESULT Delete(bool fDeleteAllAttribs = false);

	HRESULT MakeDefaultName (LPSTR pBuffer, int iLen);		// Default-KurzText liefern

	HRESULT GetCreationDate (DATE *pdCreate);
	HRESULT GetModificationDate (DATE *pdCreate);

	BOOL operator! () { return (0 == m_lRecNo) ? TRUE : FALSE; }
};

} // namespace trias_nativemerkmal

#endif // !defined(_NATIVEMERKMAL_H__B7B83A43_ECA0_11D1_8624_00600875138A__INCLUDED_)
