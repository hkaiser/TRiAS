///////////////////////////////////////////////////////////////////////////
// @doc 
// @module NativeIdent.h | Description goes here

#if !defined(_NATIVEIDENT_H__F52F6044_942F_11D1_BA07_080036D63803__INCLUDED_)
#define _NATIVEIDENT_H__F52F6044_942F_11D1_BA07_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <basetsd.h>

#include <risdb.h>
#include <xtension.h>
#include <NativePbd.h>

#include <idl/TRiASExpression.h>

#include <ospace/std/set>
#include <ospace/std/vector>

struct ITRiASMDSMap;

namespace trias_nativeident {

///////////////////////////////////////////////////////////////////////////////
// Zugriff auf Identifikator-Daten in TRiAS-Datenbank

class _TRIAS01_ENTRY CNativeIdent
{
private:
	HPROJECT m_hPr;			// Projekt-Handle
	LONG m_lIdent;			// TargetIdentifikator
	DWORD m_dwTypes;		// interessierende Objekttypen
	LONG m_lRecNo;			// zugehörige Satznummer
	bool m_fReportPbdErrors;	// entstehende Pbd-Fehler melden/nicht melden

protected:
	static HRESULT EnumObjectsIdlEx (
			HPROJECT hPr, LONG lIdent, LONG lRecNo, DWORD dwTypes,
			HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData, 
			BOOL fVerifyType = FALSE);
	static DWORD GetObjectType (struct obl &rOBLSatz);

// Enumeration aller Objekte, um diese zu zählen und Typen festzustellen
	struct CCountObjectsCallBack
	{
		DWORD *m_pdwTypes;
		LONG *m_plCnts;
	};
	static HRESULT CALLBACK CountObjects (INT_PTR lObject, DWORD dwType, UINT_PTR dwData);

// Enumeration aller Objekte, um die Objektnummern aufzusammeln
	struct CStoreObjectsCallBackSet
	{
		DWORD m_dwTypes;
		set<INT_PTR> *m_pObjs;
		LONG *m_plCnts;
		HPROJECT m_hPr;
		ITRiASExpression *m_pIExpr;
	};
	struct CStoreObjectsCallBackSetDesc
	{
		DWORD m_dwTypes;
		set<INT_PTR, greater<INT_PTR> > *m_pObjs;
		LONG *m_plCnts;
		HPROJECT m_hPr;
		ITRiASExpression *m_pIExpr;
	};

	struct CStoreObjectsCallBackVector
	{
		DWORD m_dwTypes;
		vector<INT_PTR> *m_pObjs;
		LONG *m_plCnts;
		HPROJECT m_hPr;
		ITRiASExpression *m_pIExpr;
	};
	static HRESULT CALLBACK StoreObjectsVector (INT_PTR lObject, DWORD dwType, UINT_PTR dwData);
	static HRESULT CALLBACK StoreObjectsSet (INT_PTR lObject, DWORD dwType, UINT_PTR dwData);
	static HRESULT CALLBACK StoreObjectsSetDesc (INT_PTR lObject, DWORD dwType, UINT_PTR dwData);

	static HRESULT CALLBACK StorePBDMCodes (INT_PTR lMCode, UINT_PTR dwData);
	static HRESULT CALLBACK StorePBDIdents (INT_PTR lIdent, UINT_PTR dwData);
	static HRESULT CALLBACK StorePBDIdentsEx (INT_PTR lIdent, DWORD dwTypes, UINT_PTR dwData);

	HRESULT ObjectHasIdent (INT_PTR lONr);
	DWORD GetObjectType (INT_PTR lONr);

public:
		CNativeIdent (HPROJECT hPr, LONG lIdent = 0L, DWORD dwTypes = 0, BOOL fCreate = FALSE);
		~CNativeIdent() {}

	static HRESULT EnumIdents (HPROJECT hPr, HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData);
	static HRESULT EnumIdentsDB (HPROJECT hPr, HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData);
	static HRESULT EnumRelatedMCodes (HPROJECT hPr, HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData);

	static HRESULT FillWithIdents (HPROJECT hPr, struct ITRiASMDSMap *pIMap, bool fNoCase);

	static HRESULT FindFromName (HPROJECT hPr, LPCSTR pcName, VARIANT_BOOL fCaseSensitive = VARIANT_TRUE, INT_PTR *plIdent = NULL);

	enum LOOKUPSPEED {
		LOOKUPSPEED_IMMEDIATE = 1,
		LOOKUPSPEED_INFINITE = 2,
	};
	HRESULT GetObjectTypesAndCounts (LOOKUPSPEED rgSpeed, DWORD &dwTypes, /*size_is(4)*/long *plObjCnts = NULL);	// liefert Objekttypen
	HRESULT GetObjects (DWORD dwTypes, vector<INT_PTR> &rObjs, /*size_is(4)*/long *plObjCnts = NULL, ITRiASExpression *pIExpr = NULL);		// liefert alle Objektnummern
	HRESULT GetObjects (DWORD dwTypes, set<INT_PTR> &rObjs, /*size_is(4)*/long *plObjCnts = NULL, ITRiASExpression *pIExpr = NULL);			// liefert alle Objektnummern
	HRESULT GetObjects (DWORD dwTypes, set<INT_PTR, greater<INT_PTR> > &rObjs, /*size_is(4)*/long *plObjCnts = NULL, ITRiASExpression *pIExpr = NULL);			// liefert alle Objektnummern
	HRESULT GetObjectsFromGuid (DWORD dwTypes, vector<INT_PTR> &rObjs, /*size_is(4)*/long *plObjCnts = NULL, ITRiASExpression *pIExpr = NULL);
	HRESULT HasObjects();

	HRESULT EnumObjects (HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData);
	HRESULT EnumObjectsFromGuid (HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData);

	HRESULT GetName (LPSTR pBuffer, int iLen);				// KurzText liefern
	HRESULT GetNameDB (LPSTR pBuffer, int iLen, BOOL fMakeDefault = TRUE, BOOL fCorrectName = TRUE);
	HRESULT GetDescription (LPSTR pBuffer, int iLen);		// LangText liefern
	HRESULT GetDescriptionDB (LPSTR pBuffer, int iLen, BOOL fMakeDefault = TRUE, BOOL fCorrectName = TRUE);
	HRESULT GetOKS (LPSTR pBuffer, int iLen);				// OKS liefern
	HRESULT GetOKSDB (LPSTR pBuffer, int iLen);				// OKS liefern (mit Zugriff auf GeoDB)
	HRESULT GetReadOnly (BOOL *pfReadOnly);
	HRESULT GetSystem (BOOL *pfSystem);
	HRESULT GetFullType(DWORD *pdwTypes);
	DWORD GetFullTypeDB();

	HRESULT MakeDefaultName (LPSTR pBuffer, int iLen);		// Default-KurzText liefern

	HRESULT SetName (LPCSTR pcName);						// KurzText setzen
	HRESULT SetDescription (LPCSTR pcDesc);					// LangText setzen
	HRESULT SetOKS (LPCSTR pcOKS);							// OKS setzen
	HRESULT SetReadOnly (BOOL fReadOnly);
	HRESULT SetSystem (BOOL fSystem);

	HRESULT Delete(bool fDeleteAllObjects = false);			// aus BeschreibungsDB entfernen

	void ReportPbdErrors (BOOL fReport) { m_fReportPbdErrors = (fReport ? true : false); }
	BOOL GetReportPbdErrors() { return m_fReportPbdErrors ? TRUE : FALSE; }

	HRESULT GetTextMerkmal (long lMCode, os_string &rStr);	// Merkmal lesen
	HRESULT PutTextMerkmal (long lMCode, LPCSTR pcNewText);	// Merkmal schreiben
	HRESULT DeleteTextMerkmal (long lMCode);				// Merkmal löschen

	HRESULT GetIdentGUID (struct _GUID *pGuid);
	HRESULT SetIdentGUID (const _GUID &rGuid);
	static HRESULT FindIdentFromGUID (HPROJECT hPr, const _GUID &rGuid, INT_PTR *plIdent);

	HRESULT GetCreationDate (DATE *pdCreate);
	HRESULT GetModificationDate (DATE *pdCreate);

	BOOL operator!() { return (0 == m_lIdent || 0 == m_lRecNo) ? TRUE : FALSE; }
	INT_PTR GetIdent() { return m_lIdent; }
	DWORD GetTypes() { return m_dwTypes; }
};

} // namespace trias_nativeident

#endif // !defined(_NATIVEIDENT_H__F52F6044_942F_11D1_BA07_080036D63803__INCLUDED_)
