// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 01.09.99 11:50:03
//
// @doc
// @module NativeMerkmal.cpp | Implementation of the <c CNativeMerkmal> class

#include "trias01p.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#include "resource.h"
#include "Strings.h"

#include <ospace/string/regexp.h>
#include <ospace/std/set>
#include <ospace/std/memory>

#include <strdup.hxx>
#include <ActDB.h>
#include <switchkc.h>
#include <ErrInst.hxx>
#include <NativeMerkmal.h>
#include <NativePbd.h>
#include <NativeObject.h>
#include <HeaderEntry.h>

#include <Com/ComBool.h>

#import "tlb/TRiASMDS.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids 

#include "syncdb.hxx"
#include "ConnectFilterWrappers.h"

extern "C" HINSTANCE g_hInstance;
extern int g_rgStartMode;		// STARTMODE_Normal

/////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
DefineSmartInterface(TRiASMDSMap);
DefineSmartInterface(TRiASMDSStringColl);
DefineSmartInterface(EnumVARIANT);

const CComBSTR g_bstrNil(L"");

using namespace trias_nativepbd;

/////////////////////////////////////////////////////////////////////////////
// Wrapperfunktionen für den Umgang mit den globalen Maps
namespace trias_nativemerkmal_map {
	class CAttachNumber
		: public os_regexp
	{
	public:
		CAttachNumber() : m_iCurrNumber(0), m_iStartAt(0) { pattern(".*(\\([[:digit:]]+\\))\\'"); }

		bool HasNumbering (BSTR bstrToTest)
		{
			USES_CONVERSION;

			try {
			// Eingabezeichenkette analysieren
			os_string strToTest (OLE2A(bstrToTest));
			int iMatched = match(strToTest);

				if (iMatched <= 0) 
					return false; 

				if (group(1).size() > 0) {
					m_iCurrNumber = atol (group(1).to_string().c_str());
					m_iStartAt = group(1).position() -2;	// " (" wieder wegschneiden
				} 
			} catch (...) {
				m_iCurrNumber = 0;
				m_iStartAt = 0;
			}
			return m_iCurrNumber != 0 ? true : false;
		}
		int GetCurrentNumber()
		{
			return m_iCurrNumber;
		}
		HRESULT CorrectNumbering (BSTR bstrKey, BSTR *pbstrNewKey)
		{
			if (NULL == pbstrNewKey)
				return E_POINTER;
			*pbstrNewKey = NULL;
			if (m_iCurrNumber == 0)
				return E_UNEXPECTED;

			USES_CONVERSION;

		os_string strKey (OLE2A(bstrKey));
		char cbCnt[32];

			strKey = strKey.substr(0, m_iStartAt) + " (";
			strKey += _ltoa (m_iCurrNumber+1, cbCnt, 10);
			strKey += ')';

		CComBSTR bstrRes(strKey.c_str());

			*pbstrNewKey = bstrRes.Detach();
			return S_OK;
		}

	private:
		int m_iCurrNumber;
		int m_iStartAt;
	};

	HRESULT InsertEntry (ITRiASMDSMap *pIMap, LONG lMCode, BSTR bstrShort, 
		BSTR bstrLong, DWORD dwType, bool fNoCase, INT_PTR lIdent)
	{
		if (!(g_rgStartMode & 0x01)) {		// STARTMODE_SysAdmin
		// im SysAdminMode alle Merkmale durchlassen
			if (CNativePbdMerkmal::PBDFEATURETYPE_Object != (dwType & CNativePbdMerkmal::PBDFEATURETYPE_TypeMask))
				return S_OK;		// lediglich Objektmerkmale bearbeiten
		}
		TX_ASSERT(NULL != pIMap);

	wchar_t cbBuffer[64];
	CComBSTR bstrMk (_ltow (lMCode, cbBuffer, 10));
	bool fModified = false;

		if (NULL != bstrShort && ::SysStringLen (bstrShort) > 0) {
		WTRiASMDSStringColl Coll;
		CComBSTR bstr (bstrShort);
		long lSearchMode = mdsSM_Compare|mdsSM_SrchName;

			if (fNoCase)
				lSearchMode |= mdsSM_NoCase;	// ggf. ohne Unterscheidung

			if (0 != lIdent) {
				bstr.Append(_ltow (lIdent, cbBuffer, 16));
				lSearchMode |= mdsSM_SrchLong;
			}
			while (S_OK == pIMap -> Search (bstr, lSearchMode, Coll.ppi())) {
			CAttachNumber AN;

				if (AN.HasNumbering (bstr)) {
				// nicht der erste doppelte
				CComBSTR bstrT (bstr);

					TX_VERIFY(SUCCEEDED(AN.CorrectNumbering (bstrT, CLEARED(&bstr))));
				} 
				else {

					bstr = bstrShort;
					bstr += L" (1)";
				}
				fModified = true;
			} 
			if (fModified)
				bstrShort = bstr;
		}

	CComBSTR bstrIdent(_ltow (lIdent, cbBuffer, 16));

		RETURN_FAILED_HRESULT(pIMap -> SetAt (bstrMk, bstrShort, bstrLong, bstrIdent, CComVariant(dwType, VT_I4)));
		return S_OK;
	}

	inline 
	HRESULT RetrieveEntry (ITRiASMDSMap *pIMap, LONG lMCode, 
		BSTR *pbstrShort = NULL, BSTR *pbstrLong = NULL, DWORD *pdwType = NULL, INT_PTR *plIdent = NULL)
	{
		TX_ASSERT(NULL != pIMap);
		TX_ASSERT(NULL != pbstrShort || NULL != pbstrLong || NULL != pdwType);	// sonst ist's sinnlos

	wchar_t cbBuffer[64];
	CComBSTR bstrMk (_ltow (lMCode, cbBuffer, 10));
	CComVariant v;
	HRESULT hr = E_FAIL;
	CComBSTR bstrShort, bstrLong, bstrIdent;

		if (SUCCEEDED(hr = pIMap -> GetAt (bstrMk, pbstrShort ? pbstrShort : &bstrShort, pbstrLong ? pbstrLong : &bstrLong, &bstrIdent, &v))) {
			if (NULL != pdwType && SUCCEEDED(v.ChangeType (VT_I4)))
				*pdwType = V_I4(&v);
			if (NULL != plIdent)
				*plIdent = wcstoul(bstrIdent, NULL, 16);
			return S_OK;
		}
		return hr;
	}

	inline
	HRESULT RemoveEntry (ITRiASMDSMap *pIMap, LONG lMCode)
	{
		TX_ASSERT(NULL != pIMap);

	wchar_t cbBuffer[64];
	CComBSTR bstrMk (_ltow (lMCode, cbBuffer, 10));

		return pIMap -> RemoveAt (bstrMk);
	}

	inline
	HRESULT ReplaceShort (ITRiASMDSMap *pIMap, LONG lMCode, BSTR bstrShort)
	{
		TX_ASSERT(NULL != pIMap);

	wchar_t cbBuffer[64];
	CComBSTR bstrMk (_ltow (lMCode, cbBuffer, 10));
	CComBSTR bstrLong;
	CComVariant v;
	CComBSTR bstrShortOld, bstrDummy;

		if (SUCCEEDED(pIMap -> GetAt (bstrMk, &bstrShortOld, &bstrLong, &bstrDummy, &v)))
			pIMap -> RemoveAt (bstrMk);
		return pIMap -> SetAt (bstrMk, bstrShort, bstrLong, NULL, v);
	}

	inline
	HRESULT ReplaceLong (ITRiASMDSMap *pIMap, LONG lMCode, BSTR bstrLong)
	{
		TX_ASSERT(NULL != pIMap);

	wchar_t cbBuffer[64];
	CComBSTR bstrMk (_ltow (lMCode, cbBuffer, 10));
	CComBSTR bstrName, bstrShort, bstrLongOld, bstrDummy;
	CComVariant v;

		if (SUCCEEDED(pIMap -> GetAt (bstrMk, &bstrShort, &bstrLongOld, &bstrDummy, &v)))
			pIMap -> RemoveAt (bstrMk);
		return pIMap -> SetAt (bstrMk, bstrShort, bstrLong, NULL, v);
	}

	inline
	HRESULT ReplaceType (ITRiASMDSMap *pIMap, LONG lMCode, DWORD dwType)
	{
		TX_ASSERT(NULL != pIMap);

	wchar_t cbBuffer[64];
	CComBSTR bstrMk (_ltow (lMCode, cbBuffer, 10));
	CComBSTR bstrName, bstrShort, bstrLong, bstrDummy;
	CComVariant v (dwType, VT_I4), vDummy;

		if (SUCCEEDED(pIMap -> GetAt (bstrMk, &bstrShort, &bstrLong, &bstrDummy, &vDummy)))
			pIMap -> RemoveAt (bstrMk);
		return pIMap -> SetAt (bstrMk, bstrShort, bstrLong, NULL, v);
	}

	inline
	HRESULT ReplaceIdent (ITRiASMDSMap *pIMap, LONG lMCode, INT_PTR lIdent)
	{
		TX_ASSERT(NULL != pIMap);

	wchar_t cbBuffer[64];
	CComBSTR bstrMk (_ltow (lMCode, cbBuffer, 10));
	CComBSTR bstrIdent (_ltow (lIdent, cbBuffer, 16));
	CComBSTR bstrName, bstrShort, bstrLong, bstrDummy;
	CComVariant vType;

		if (SUCCEEDED(pIMap -> GetAt (bstrMk, &bstrShort, &bstrLong, &bstrDummy, &vType)))
			pIMap -> RemoveAt (bstrMk);
		return pIMap -> SetAt (bstrMk, bstrShort, bstrLong, bstrIdent, vType);
	}

	inline
	HRESULT FindFromName (ITRiASMDSMap *pIMap, BSTR bstrName, INT_PTR lIdent = 0, 
		bool fCaseSensitive = true, INT_PTR *plMCode = NULL, bool fIdentAttribs = false)
	{
	// Kurztext wiederfinden
		if (NULL == bstrName || 0 == ::SysStringLen(bstrName)) 
			return E_UNEXPECTED;

	WTRiASMDSStringColl Coll;
	long lSearchMode = mdsSM_Compare|mdsSM_SrchName;

		if (!fCaseSensitive)
			lSearchMode |= mdsSM_NoCase;	// Groß-/Kleinschreibung ignorieren

	CComBSTR bstr (bstrName);
	CComBSTR bstrIdent;

		if (0 != lIdent) {
		wchar_t cbBuffer[64];

			bstrIdent = _ltow (lIdent, cbBuffer, 16);
			bstr.AppendBSTR(bstrIdent);
			lSearchMode |= mdsSM_SrchLong;
		}

		_ASSERTE(0 == lIdent || bstrIdent.Length() > 0);
		if (S_OK == pIMap -> Search (bstr, lSearchMode, Coll.ppi())) {
		WUnknown UnkEnum;

			RETURN_FAILED_HRESULT(Coll -> _NewEnum(UnkEnum.ppi()));

		bool fFound = false;
		bool fFoundCorrect = false;

		WEnumVARIANT Enum(UnkEnum);
		CComBSTR bstrMk;
		CComVariant v;

			RETURN_FAILED_HRESULT(Enum -> Reset());
			for (Enum -> Reset(); S_OK == Enum -> Next(1, CLEARED(&v), NULL); /**/) {
				_ASSERTE(VT_BSTR == V_VT(&v));

			CComBSTR bstrShort, bstrLong, bstrId;
			CComVariant vType;

				RETURN_FAILED_HRESULT(pIMap -> GetAt (V_BSTR(&v), &bstrShort, &bstrLong, &bstrId, &vType));
				if (0 != lIdent) {
				// Attribut für bestimmte Objektklasse gesucht
					if (bstrIdent == bstrId) {
					// die gesuchte Objektklasse gefunden
						fFound = true;
						fFoundCorrect = true;
						bstrMk = V_BSTR(&v);
						break;
					}
					else if (!fIdentAttribs || 0 == wcstoul(bstrId, NULL, 16)) {
					// alte Datenquelle oder allgemeines Attribut: Ident ganz ignorieren 
						fFound = true;
						bstrMk = V_BSTR(&v);
						if (!fIdentAttribs) {
							fFoundCorrect = true;
							break;		// gefunden
						}
					}
				}
				else {
				// allgemeines Attribut gesucht
					fFound = true;			// den letzten und besten gefunden
					bstrMk = V_BSTR(&v);
					if (!fIdentAttribs || 0 == wcstoul(bstrId, NULL, 16)) {
						fFoundCorrect = true;
						break;		// ohne Ident gesucht, ohne Ident gefunden oder alte Datenquelle
					}
				}
			}
			
			if (!fFound)
				return HRESULT_FROM_ERRCODE(WC_NOTFOUND);

			if (NULL != plMCode)
				*plMCode = _wtol(bstrMk);
			return fFoundCorrect ? S_OK : S_FALSE;
		}

	// allgemeines Attribut suchen
		lSearchMode &= ~mdsSM_SrchLong;
		if (S_OK == pIMap -> Search (bstrName, lSearchMode, Coll.ppi())) {
		WUnknown UnkEnum;

			RETURN_FAILED_HRESULT(Coll -> _NewEnum(UnkEnum.ppi()));

		bool fFound = false;
		WEnumVARIANT Enum(UnkEnum);
		CComBSTR bstrMk;
		CComVariant v;

			RETURN_FAILED_HRESULT(Enum -> Reset());
			for (Enum -> Reset(); S_OK == Enum -> Next(1, CLEARED(&v), NULL); /**/) {
				_ASSERTE(VT_BSTR == V_VT(&v));

			CComBSTR bstrShort, bstrLong, bstrId;
			CComVariant vType;

				RETURN_FAILED_HRESULT(pIMap -> GetAt (V_BSTR(&v), &bstrShort, &bstrLong, &bstrId, &vType));

			// allgemeines Attribut gesucht
				fFound = true;			// den letzten und besten gefunden
				bstrMk = V_BSTR(&v);
				break;					// ohne Ident gefunden oder alte Datenquelle
			}
			
			if (!fFound)
				return HRESULT_FROM_ERRCODE(WC_NOTFOUND);

			if (NULL != plMCode)
				*plMCode = _wtol(bstrMk);
			return (0 != lIdent) ? S_FALSE : S_OK;
		}
		return HRESULT_FROM_ERRCODE(WC_NOTFOUND);
	}
}

namespace trias_nativemerkmal {


CNativeMerkmal::CNativeMerkmal (HPROJECT hPr, LONG lMCode, BOOL fCreate)
	: m_hPr(hPr), m_lRecNo(0L), m_lMCode(lMCode), m_rgTarget(FEATURETARGET_Object)
{
	Initialize(fCreate);
}

CNativeMerkmal::CNativeMerkmal (HPROJECT hPr, FEATURETARGET rgTarget, LONG lMCode, BOOL fCreate)
	: m_hPr(hPr), m_lRecNo(0L), m_lMCode(lMCode), m_rgTarget(rgTarget)
{
	Initialize(fCreate);
}

HRESULT CNativeMerkmal::Initialize (BOOL fCreate)
{
// Feststellen, ob Ident bereits existiert
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	m_fReportPbdErrors = false;		// default: keine Fehler melden

	if (0 != m_lMCode) {
	CActDB ActDB(m_hPr);
	DB_ADDR dbaMKL (m_hPr);			// gesuchte DatenBankadresse

		dbaMKL.file_no = MKL;

	ErrInstall EI (WC_NOTFOUND);
	ErrCode RC = (ErrCode)z_keyfind (&dbaMKL, MK, (LPVOID)&m_lMCode);

		if (EC_OKAY == RC)
			m_lRecNo = dbaMKL.rec_no;			// gesuchter Satz
		else if (WC_NOTFOUND == RC && fCreate) {
		// neuen IDL-Satz anlegen
		struct mkl MKLSatz;

			MKLSatz.mk = m_lMCode;
			__NewHR(dbaMKL, MKLSatz);
			m_lRecNo = dbaMKL.rec_no;			// neuer Satz
		} 
		else if (EC_OKAY != RC)
			return HRESULT_FROM_ERRCODE(RC);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// KurzText (Bezeichner) lesen
HRESULT CNativeMerkmal::GetName (LPSTR pBuffer, int iLen)				// KurzText liefern
{
	TX_ASSERT(NULL != pBuffer && iLen > 0);

	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (m_hPr, &hPrPbd))			// keine Pbd zugeordnet
		return MakeDefaultName (pBuffer, iLen);

WTRiASMDSMap Map;
CComBSTR bstr;

	USES_CONVERSION;
	RETURN_FAILED_HRESULT(GetMCodeMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));

HRESULT hr = trias_nativemerkmal_map::RetrieveEntry (Map, m_lMCode, &bstr);

	if (SUCCEEDED(hr) && NULL != bstr.m_str && bstr.Length() > 0) {
		TX_ASSERT(TIsValidAddress(pBuffer, iLen));
		strncpy (pBuffer, OLE2A(bstr), iLen-1);
		pBuffer[iLen-1] = '\0';
		return S_OK;
	}
	return MakeDefaultName (pBuffer, iLen);
}

HRESULT CNativeMerkmal::GetNameDB (LPSTR pBuffer, int iLen, BOOL fMakeDefault, BOOL fCorrectName)
{
	TX_ASSERT(NULL != pBuffer && iLen > 0);

	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (m_hPr, &hPrPbd))			// keine Pbd zugeordnet
		return fMakeDefault ? MakeDefaultName (pBuffer, iLen) : E_UNEXPECTED;

CNativePbdMerkmal Merkmal (hPrPbd, m_lMCode, NULL, GetReportPbdErrors(), fCorrectName);

	if (!Merkmal) 
		return fMakeDefault ? MakeDefaultName (pBuffer, iLen) : HRESULT_FROM_ERRCODE(WC_NOTFOUND);

LPCSTR pcKText = Merkmal.GetKurzText();

	if (NULL != pcKText && strlen(pcKText) > 0) {
		TX_ASSERT(TIsValidAddress(pBuffer, iLen));
		strncpy (pBuffer, pcKText, iLen-1);
		pBuffer[iLen-1] = '\0';
		return S_OK;
	}
	return fMakeDefault ? MakeDefaultName (pBuffer, iLen) : HRESULT_FROM_ERRCODE(WC_NOTFOUND);
}

HRESULT CNativeMerkmal::SetName (LPCSTR pcNewName)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (m_hPr, &hPrPbd))
		return E_UNEXPECTED;		// keine Pbd zugeordnet

CNativePbdMerkmal Merkmal (hPrPbd, m_lMCode, NULL, GetReportPbdErrors());

	RETURN_FAILED_HRESULT(Merkmal.SetKurzText (pcNewName));
	RETURN_FAILED_HRESULT(Merkmal.SaveInPBD());

WTRiASMDSMap Map;

	USES_CONVERSION;
	RETURN_FAILED_HRESULT(GetMCodeMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));
	RETURN_FAILED_HRESULT(trias_nativemerkmal_map::ReplaceShort (Map, m_lMCode, CComBSTR(pcNewName)));

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Langtext lesen
HRESULT CNativeMerkmal::GetDescription (LPSTR pBuffer, int iLen)		// LangText liefern
{
	TX_ASSERT(NULL != pBuffer && iLen > 0);

	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (m_hPr, &hPrPbd))			// keine Pbd zugeordnet
		return E_UNEXPECTED;

WTRiASMDSMap Map;
CComBSTR bstr;

	USES_CONVERSION;
	RETURN_FAILED_HRESULT(GetMCodeMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));

HRESULT hr = trias_nativemerkmal_map::RetrieveEntry (Map, m_lMCode, NULL, &bstr);

	if (SUCCEEDED(hr) && NULL != bstr.m_str && bstr.Length() > 0) {
		TX_ASSERT(TIsValidAddress(pBuffer, iLen));
		strncpy (pBuffer, OLE2A(bstr), iLen-1);
		pBuffer[iLen-1] = '\0';
		return S_OK;
	}
	return MakeDefaultName (pBuffer, iLen);
}

HRESULT CNativeMerkmal::GetDescriptionDB (LPSTR pBuffer, int iLen, BOOL fMakeDefault, BOOL fCorrectName)
{
	TX_ASSERT(NULL != pBuffer && iLen > 0);

	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (m_hPr, &hPrPbd))
		return E_UNEXPECTED;		// keine Pbd zugeordnet

CNativePbdMerkmal Merkmal (hPrPbd, m_lMCode, NULL, GetReportPbdErrors(), fCorrectName);

	if (!Merkmal)
		return fMakeDefault ? MakeDefaultName (pBuffer, iLen) : HRESULT_FROM_ERRCODE(WC_NOTFOUND);

	if (NULL == Merkmal.GetLangText (pBuffer, iLen))
		return fMakeDefault ? MakeDefaultName (pBuffer, iLen) : ::GetLastError();
	return S_OK;
}

HRESULT CNativeMerkmal::SetDescription (LPCSTR pcNewDesc)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (m_hPr, &hPrPbd))
		return E_UNEXPECTED;		// keine Pbd zugeordnet

CNativePbdMerkmal Merkmal (hPrPbd, m_lMCode, NULL, GetReportPbdErrors());

	RETURN_FAILED_HRESULT(Merkmal.SetLangText (pcNewDesc));
	RETURN_FAILED_HRESULT(Merkmal.SaveInPBD());

WTRiASMDSMap Map;

	RETURN_FAILED_HRESULT(GetMCodeMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));
	RETURN_FAILED_HRESULT(trias_nativemerkmal_map::ReplaceLong (Map, m_lMCode, CComBSTR(pcNewDesc)));

	return S_OK;
}

DWORD CNativeMerkmal::GetFullType()
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (m_hPr, &hPrPbd))			// keine Pbd zugeordnet
		return E_UNEXPECTED;

WTRiASMDSMap Map;
CComBSTR bstr;
DWORD dwType = 0;

	if (SUCCEEDED(GetMCodeMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()))) 
		trias_nativemerkmal_map::RetrieveEntry (Map, m_lMCode, NULL, NULL, &dwType);		// bei Fehler liefert die Funktion '0'
	return dwType;
}

///////////////////////////////////////////////////////////////////////////////
// DefaultKText erzeugen
HRESULT CNativeMerkmal::MakeDefaultName (LPSTR pBuffer, int iLen)				// KurzText liefern
{
	TX_ASSERT(NULL != pBuffer && iLen > 0);

char cbBuffer[TEXTLEN+1];
char cbOut[_MAX_PATH];

	if (!::LoadString (g_hInstance, IDS_DEFAULTMERKMALKTEXT, cbBuffer, sizeof(cbBuffer)))
		return E_UNEXPECTED;
	wsprintf (cbOut, cbBuffer, m_lMCode);

	TX_ASSERT(TIsValidAddress(pBuffer, iLen));
	TX_ASSERT(iLen <= sizeof(cbOut));

	strncpy (pBuffer, cbOut, iLen-1);
	pBuffer[iLen-1] = '\0';
	return S_FALSE;			// kein Beschreibungstext vorhanden
}

///////////////////////////////////////////////////////////////////////////////
// aus Pbd entfernen
HRESULT CNativeMerkmal::Delete(bool fDeleteAllAttribs)
{
// gibt es noch Instanzen dieses Attributes
vector<INT_PTR> Objs;

	if (fDeleteAllAttribs && SUCCEEDED(GetObjects(Objs)) && Objs.size() > 0) {
	// alle existierenden Instanzen löschen
		using namespace trias_nativeheader;
		using namespace trias_nativeobject;

	BOOL fTextObjMCode = (m_lMCode == GetHeaderLong (m_hPr, g_cbTextObjMCode, 99999100L, 10)) ? TRUE : FALSE;

		for (vector<INT_PTR>::iterator it = Objs.begin(); it != Objs.end(); ++it) {
		CNativeObject Obj (m_hPr, *it);

			Obj.DeleteTextMerkmal(m_lMCode, fTextObjMCode);
		}
	}

// nun auch aus Pbd herauslöschen
HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (m_hPr, &hPrPbd))
		return S_OK;		// keine Pbd zugeordnet

// jetzt wirklich löschen
CNativePbdMerkmal Merkmal (hPrPbd, m_lMCode, NULL, GetReportPbdErrors());

	RETURN_FAILED_HRESULT(Merkmal.DeleteInPBD());

WTRiASMDSMap Map;

	RETURN_FAILED_HRESULT(GetMCodeMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));
	RETURN_FAILED_HRESULT(trias_nativemerkmal_map::RemoveEntry (Map, m_lMCode));
	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
// Merkmalscode aus Text finden
/*static*/
HRESULT CNativeMerkmal::FindMerkmal (HPROJECT hPr, LPCSTR pcItem, LONG *plMCode)
{
HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (hPr, &hPrPbd))			// keine Pbd zugeordnet
		return E_UNEXPECTED;

WTRiASMDSMap Map;
WTRiASMDSStringColl Coll;

	RETURN_FAILED_HRESULT(GetMCodeMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));
	if (SUCCEEDED(Map -> Search (CComBSTR(pcItem), mdsSM_Compare|mdsSM_SrchShort, Coll.ppi())))
	{
	WUnknown UnkEnum;
	CComVariant v;

		RETURN_FAILED_HRESULT(Map -> _NewEnum (UnkEnum.ppi()));

	WEnumVARIANT Enum(UnkEnum);

		RETURN_FAILED_HRESULT(Enum -> Reset()); 
		RETURN_FAILED_HRESULT(Enum -> Next (1, CLEARED(&v), NULL));

		RETURN_FAILED_HRESULT(v.ChangeType (VT_BSTR));

	CComBSTR bstrMk;
	CComBSTR bstrLong, bstrDummy;
	CComVariant vDummy;

		RETURN_FAILED_HRESULT(Map -> GetAt (V_BSTR(&v), &bstrMk, &bstrLong, &bstrDummy, &vDummy));
		*plMCode = _wtol (bstrMk);
		return S_OK;
	}
	return HRESULT_FROM_ERRCODE(WC_NOTFOUND);
}

///////////////////////////////////////////////////////////////////////////////
// Merkmalstyp setzen
HRESULT CNativeMerkmal::SetTyp (int rgType)
{
HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (m_hPr, &hPrPbd))			// keine Pbd zugeordnet
		return E_UNEXPECTED;

// in Pbd nachführen
CNativePbdMerkmal Merkmal (hPrPbd, m_lMCode, NULL, GetReportPbdErrors());

	rgType &= CNativePbdMerkmal::PBDFEATURETYPE_TypeMask;				// auf Typ begrenzen
	Merkmal.SetTyp (rgType);
	RETURN_FAILED_HRESULT(Merkmal.SaveInPBD());

// lokal in Map austauschen
WTRiASMDSMap Map;
DWORD dwType = 0;

	RETURN_FAILED_HRESULT(GetMCodeMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));

	trias_nativemerkmal_map::RetrieveEntry (Map, m_lMCode, NULL, NULL, &dwType);
	dwType = (dwType & ~CNativePbdMerkmal::PBDFEATURETYPE_TypeMask) | rgType;
	RETURN_FAILED_HRESULT(trias_nativemerkmal_map::ReplaceType (Map, m_lMCode, dwType));

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ReadOnlyMode setzen
HRESULT CNativeMerkmal::SetReadOnly (BOOL fReadOnly)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (m_hPr, &hPrPbd))			// keine Pbd zugeordnet
		return E_UNEXPECTED;

// in Pbd nachführen
CNativePbdMerkmal Merkmal (hPrPbd, m_lMCode, NULL, GetReportPbdErrors());

	Merkmal.SetReadOnly (fReadOnly);
	RETURN_FAILED_HRESULT(Merkmal.SaveInPBD());

// lokal in Map austauschen
WTRiASMDSMap Map;
DWORD dwType = 0;

	RETURN_FAILED_HRESULT(GetMCodeMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));

	trias_nativemerkmal_map::RetrieveEntry (Map, m_lMCode, NULL, NULL, &dwType);
	dwType = (dwType & ~CNativePbdMerkmal::PBDFEATURETYPE_ReadOnly) | (fReadOnly ? CNativePbdMerkmal::PBDFEATURETYPE_ReadOnly : 0);
	RETURN_FAILED_HRESULT(trias_nativemerkmal_map::ReplaceType (Map, m_lMCode, dwType));

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// SystemMode setzen
HRESULT CNativeMerkmal::SetSystem (BOOL fSystem)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (m_hPr, &hPrPbd))			// keine Pbd zugeordnet
		return E_UNEXPECTED;

// in Pbd nachführen
CNativePbdMerkmal Merkmal (hPrPbd, m_lMCode, NULL, GetReportPbdErrors());

	Merkmal.SetSystem (fSystem);
	RETURN_FAILED_HRESULT(Merkmal.SaveInPBD());

// lokal in Map austauschen
WTRiASMDSMap Map;
DWORD dwType = 0;

	RETURN_FAILED_HRESULT(GetMCodeMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));

	trias_nativemerkmal_map::RetrieveEntry (Map, m_lMCode, NULL, NULL, &dwType);
	dwType = (dwType & ~CNativePbdMerkmal::PBDFEATURETYPE_System) | (fSystem ? CNativePbdMerkmal::PBDFEATURETYPE_System : 0);
	RETURN_FAILED_HRESULT(trias_nativemerkmal_map::ReplaceType (Map, m_lMCode, dwType));

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert alle Merkmale dieser Datenbank
/*static*/
HRESULT CNativeMerkmal::EnumMerkmale (
	HPROJECT hPr, HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData)
{
	TX_ASSERT(NULL != hPr);
	SYNC_DBACCESS (g_pDbMutex, hPr);

HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (hPr, &hPrPbd))			// keine Pbd zugeordnet
		return E_UNEXPECTED;

WTRiASMDSMap Map;
CComBSTR bstr;

	USES_CONVERSION;
	RETURN_FAILED_HRESULT(GetMCodeMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));

WUnknown UnkEnum;
CComVariant v;
bool iRC = true;

	RETURN_FAILED_HRESULT(Map -> _NewEnum (UnkEnum.ppi()));

WEnumVARIANT Enum(UnkEnum);

	for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
	CComVariant vType;
	DWORD dwType = 0;
	CComBSTR bstrName, bstrShort, bstrLong, bstrDummy;

		vType.vt = VT_I4;
		if (FAILED(v.ChangeType (VT_BSTR)) || FAILED(Map -> GetAt (V_BSTR(&v), &bstrName, &bstrLong, &bstrDummy, &vType)))
		{
			TX_ASSERT(FALSE);
			continue;
		}
		if (SUCCEEDED(vType.ChangeType (VT_I4)))
			dwType = V_I4(&vType);

	// Callback aufrufen
		TX_ASSERT(0 != _wtol (V_BSTR(&v)));
		iRC = SUCCEEDED(pFcn (_wtol (V_BSTR(&v)), dwType, dwData)) ? true : false;
		if (!iRC) break;
	}
	return iRC ? S_OK : S_FALSE;
}

/*static*/
HRESULT CNativeMerkmal::EnumMerkmaleDB (
	HPROJECT hPr, HRESULT (CALLBACK *pFcn)(INT_PTR, UINT_PTR), UINT_PTR dwData)
{
	TX_ASSERT(NULL != hPr);
	SYNC_DBACCESS (g_pDbMutex, hPr);

CActDB ActDB(hPr);
DB_ADDR dbaMKL (hPr);
ErrInstall EI (WC_NOTFOUND);	// Fehler WC_NOTFOUND ignorieren

// ersten ID suchen
HRESULT hr = S_OK;
ErrCode RC = (ErrCode)z_keyfirst (&dbaMKL, MK);

	if (RC != EC_OKAY) {
	// Fehler aufgetreten
		if (RC == WC_NOTFOUND) 
			return S_FALSE;					// nichts gefunden: OK
		return HRESULT_FROM_ERRCODE(RC);	// sonstiger Fehler
	}

// für alle weiteren ID's
bool iNext = true;
bool iRC = true;

	while (iNext && iRC) {
	INT_PTR lMCode = 0;
	DWORD dwTypes = 0;

	// MCode aus Schlüsseldatei lesen
		RC = (ErrCode)z_keyread (hPr, &lMCode);
		if (RC != EC_OKAY) break;

	// nächsten Schlüssel suchen
		RC = (ErrCode)z_keynext (&dbaMKL, MK);
		if (RC != EC_OKAY)
			iNext = false;

		{
		CKeyContext keyCtx;

		// Callback aufrufen
			iRC = SUCCEEDED(pFcn (lMCode, dwData)) ? true : false;
			ActDB.ReActivate();
		}
	}
	if (RC == WC_NOTFOUND) 
		RC = EC_OKAY;           // nichts mehr gefunden: OK

	return (EC_OKAY == RC) ? (iRC ? S_OK : S_FALSE) : HRESULT_FROM_ERRCODE(RC);
}

///////////////////////////////////////////////////////////////////////////////
// MerkmalsMap mit allen derzeit existierenden Merkmalen füllen
namespace {
	typedef struct tagFILLMERKMALEDATA {
        HPROJECT m_hPr;
		HPROJECT m_hPbdPr;
		ITRiASMDSMap *m_pIMap;
		set<INT_PTR> *m_pMCodes;
		bool m_fFillMap;
		bool m_fNoCase;
	} FILLMERKMALEDATA;
};

/*static*/
HRESULT CALLBACK CNativeMerkmal::StorePBDMerkmale (INT_PTR lMCode, UINT_PTR dwData)
{
FILLMERKMALEDATA *pFMD = reinterpret_cast<FILLMERKMALEDATA *>(dwData);
WTRiASMDSMap Map (pFMD -> m_pIMap);

	if (!pFMD -> m_fFillMap) {
	// jetzt nur noch nicht dagewesene MCodes durchlassen
		if (pFMD -> m_pMCodes -> find(lMCode) != pFMD -> m_pMCodes -> end())
			return S_FALSE;	// den hatten wir schon
	}

// alle dagewesenen aufsammeln
	pFMD -> m_pMCodes -> insert (lMCode);

CComBSTR bstrShort;
CComBSTR bstrLong;
char cbBuffer[_MAX_PATH];

CNativePbdMerkmal PbdMerkmal (pFMD -> m_hPbdPr, lMCode, NULL, FALSE);

	bstrShort = PbdMerkmal.GetKurzText();		// Kurztext (unverfälscht)
	if (NULL != PbdMerkmal.GetLangText (cbBuffer, sizeof(cbBuffer)))
		bstrLong = cbBuffer;					// Langtext (unverfälscht)

// an dieser Stelle Eindeutigkeit des Kurztextes gewährleisten
DWORD dwFullType = PbdMerkmal.GetFullType();

	if (!pFMD -> m_fFillMap)
		dwFullType |= CNativePbdMerkmal::PBDFEATURETYPE_PbdOnly;

// wenn Datenbank RO ist, dann ists auch dieses Merkmal
BOOL fRO = TRUE;

    GetROMode(pFMD->m_hPr, &fRO);
    if (fRO)
		dwFullType |= CNativePbdMerkmal::PBDFEATURETYPE_ReadOnly;
        
	return trias_nativemerkmal_map::InsertEntry (Map, lMCode, bstrShort, bstrLong, dwFullType, pFMD -> m_fNoCase, PbdMerkmal.GetIdent());
}

/*static*/
HRESULT CNativeMerkmal::FillWithMCodes (HPROJECT hPr, ITRiASMDSMap *pIMap, bool fNoCase)
{
	TX_ASSERT(NULL != hPr);
	SYNC_DBACCESS (g_pDbMutex, hPr);

HPROJECT hPrPbd = NULL;

	if (!GetRelatedProject (hPr, &hPrPbd))			// keine Pbd zugeordnet
		return E_UNEXPECTED;

FILLMERKMALEDATA FMD;
set<INT_PTR> MCodes;

    FMD.m_hPr = hPr;
	FMD.m_hPbdPr = hPrPbd;
	FMD.m_pIMap = pIMap;
	FMD.m_pMCodes = &MCodes;
	FMD.m_fFillMap = true;
	FMD.m_fNoCase = fNoCase;

HRESULT hr = EnumMerkmaleDB (hPr, StorePBDMerkmale, reinterpret_cast<UINT_PTR>(&FMD));

	if (FAILED(hr))
		return hr;	// abgebrochen oder Fehler

	FMD.m_fFillMap = false;
	return CNativePbdMerkmal::EnumPBDData(hPrPbd, StorePBDMerkmale, reinterpret_cast<UINT_PTR>(&FMD));
}

/*static*/ 
HRESULT CNativeMerkmal::FindFromName (HPROJECT hPr, LPCSTR pcName, INT_PTR lIdent, VARIANT_BOOL fCaseSensitive, INT_PTR *plMCode)
{
	_ASSERTE(NULL != hPr);
	SYNC_DBACCESS (g_pDbMutex, hPr);

HPROJECT hPrPbd = NULL;
WTRiASMDSMap Map;
bool fIdentAttribs = (LocGetDBVersion(hPr) >= VERSION05000013) ? true : false;

	if (!GetRelatedProject (hPr, &hPrPbd))			// keine Pbd zugeordnet
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(GetMCodeMap (hPrPbd, __uuidof(ITRiASMDSMap), Map.ppv()));
	return trias_nativemerkmal_map::FindFromName (Map, CComBSTR(pcName), lIdent, CComBool(fCaseSensitive), plMCode, fIdentAttribs);
}

///////////////////////////////////////////////////////////////////////////////
// Enumeration aller Objekte eines MCodes und ggf. eines Idents in aufsteigender
// Reihenfolge der Werte
HRESULT CNativeMerkmal::ObjectHasIdent (INT_PTR lONr, INT_PTR lIdent)
{
trias_nativeobject::CNativeObject Obj (m_hPr, lONr);
INT_PTR lObjIdent = 0;

	if (!Obj) return E_INVALIDARG;
	RETURN_FAILED_HRESULT(Obj.GetIdent(&lObjIdent))
	return (lIdent == lObjIdent) ? S_OK : S_FALSE;
}

// wegen BUG bis jetzt (#HK000113) evtl. Korrekturcode rufen
HRESULT CNativeMerkmal::CondCorrectFDBTError (struct kdbt &rKDBTSatz, long lRecNo)
{
ErrCode RC = EC_OKAY;
ErrInstall EB (EC_INVADDR);
DB_ADDR dbaVOM (m_hPr, VOM, rKDBTSatz.zmivom);
struct vom VOMSatz;

	RC = (ErrCode)z_readrec (&dbaVOM, &VOMSatz);
	if (EC_OKAY != RC) {
		if (EC_INVADDR != RC)
			return HRESULT_FROM_ERRCODE(RC);

	// hier versuchen den Fehler zu beheben (Folgesatz wurde als 1. Satz gespeichert,
	// und wurde hier irrtümlicherweise gefunden
	DB_ADDR dbaKDBT(m_hPr, KDBT, lRecNo);
	DB_ADDR dbaFDBT(m_hPr, FDBT, lRecNo);

		__DisposeHR(dbaKDBT, rKDBTSatz);
		__NewHR(dbaFDBT, rKDBTSatz);
		_ASSERTE(dbaFDBT.rec_no == lRecNo);		// Satznummer darf sich nicht geändert haben
		return S_FALSE;
	}
	return S_OK;	// kein Fehler
}

HRESULT CNativeMerkmal::EndOfRangeReached (INT_PTR lONr, LPCSTR pcEnd, int iSrchLen, RANGEENUM rgMode)
{
	TX_ASSERT(NULL != pcEnd && iSrchLen > 0);

char cbKey[SIZEOF_KDBT_INFO];		// sizeof(kdbt::info)
ErrCode RC = EC_OKAY;
int iCmp = 0;

	if (iSrchLen <= SIZEOF_KDBT_INFO) {
	// Endwert ist kürzer als key
		RC = (ErrCode)z_keyread(m_hPr, cbKey);
		if (EC_OKAY != RC) return HRESULT_FROM_ERRCODE(RC);
	
		iCmp = strncmp (cbKey, pcEnd, iSrchLen);
	} 
	else {
	// Endwert ist länger als normaler key, also vollständigen Text vergleichen
	char *pFullText = NULL;
	HRESULT hr = GetTextMerkmal (m_hPr, m_lMCode, lONr, OBL_OLD, &pFullText);

		if (FAILED(hr)) {
			DELETE_OBJ(pFullText);
			return hr;
		}
		iCmp = strcmp (pFullText, pcEnd);
		DELETE_OBJ(pFullText);
	}
	if (iCmp < 0)
		return S_FALSE;		// noch nicht der letzte
	if (iCmp == 0)			// paßt genau, daher von Flags abhängig
		return (RANGEENUM_EXCLUSIVEEND & rgMode) ? S_OK : S_FALSE;
	return S_OK;			// garantiert drüber
}

DWORD CNativeMerkmal::GetObjectType (INT_PTR lONr)
{
DB_ADDR_OBL dbaOBL (m_hPr, lONr);
struct obl OBLSatz;

	if (EC_OKAY != z_readrec(&dbaOBL, &OBLSatz))
		return 0;		// Error, unlknown object type

	if (OBLSatz.status & (SB_TEXTOBJ|SB_TEXTOBJIND)) 
		return OTText;
	if (OBLSatz.status & SB_SACHOBJ) 
		return OTSachObjekt;
	if (OBLSatz.rmaske & OREL) 
		return OTKO;

	if (OBLSatz.zokp) 
		return OTPunkt;
	if (OBLSatz.zovol) 
		return OTLinie;
	if (OBLSatz.zovoma) 
		return OTFlaeche;

	return 0;
}

/*static*/
HRESULT CALLBACK CNativeMerkmal::StoreObjectsVector (INT_PTR lObject, DWORD dwType, UINT_PTR dwData)
{
vector<INT_PTR> *pCont = reinterpret_cast<vector<INT_PTR> *>(dwData);

	COM_TRY {
		pCont -> push_back(lObject);
	} COM_CATCH;
	return S_OK;
}

HRESULT CNativeMerkmal::GetObjects (
	vector<INT_PTR> &rObjs, INT_PTR lIdent, LPCSTR pcStart, LPCSTR pcEnd, RANGEENUM rgMode)
{
	return EnumObjects (StoreObjectsVector, reinterpret_cast<UINT_PTR>(&rObjs), lIdent, pcStart, pcEnd, rgMode);
}

HRESULT CNativeMerkmal::EnumObjects(
	HRESULT (CALLBACK *pFcn)(INT_PTR, DWORD, UINT_PTR), UINT_PTR dwData, INT_PTR lIdent,
	LPCSTR pcStart, LPCSTR pcEnd, RANGEENUM rgMode)
{
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (LocGetDBVersion(m_hPr) < VERSION0500000B)
		return E_NOTIMPL;

	TX_ASSERT(NULL == pcEnd || !(RANGEENUM_PREFIX & rgMode));		// mit Endwert keine Prefixprüfung

// ACHTUNG Oem<-->Ansi mismatch ! Key ist 'Oem' und Merkmal aus GetTextMerkmal ist bereits 'Ansi'
int iSrchLen = 0;
auto_ptr<char> pOemStart (StrDupF (pcStart));

	if (NULL != pOemStart.get()) 
		CharToOem (pcStart, pOemStart.get());

auto_ptr<char> pOemEnd (StrDupF (pcEnd));

	if (NULL != pOemEnd.get()) {
		CharToOem (pcEnd, pOemEnd.get());
		iSrchLen = strlen(pOemEnd.get());
	}

// bei RANGEENUM_PREFIX wird der Vergleich einfach auf die Länge des Startwertes begrenzt
	if (RANGEENUM_PREFIX & rgMode && NULL != pOemStart.get())
		iSrchLen = strlen(pOemStart.get());

// Start finden
CActDB ActDB(m_hPr);
ErrCode RC = EC_OKAY;
HRESULT hr = S_OK;

DB_ADDR dbaKDBT(m_hPr, KDBT);
DB_ADDR dbaVOM(m_hPr, VOM);
DB_ADDR dbaMKL(m_hPr, MKL);
struct kdbt KDBTSatz;
struct vom VOMSatz;
struct mkl MKLSatz;

	if (NULL == pcStart) {
	// mit dem ersten Anfangen
	ErrInstall EI (WC_NOTFOUND);

		RC = (ErrCode)z_keyfirst(&dbaKDBT, INFO);
	}
	else {
	// mit dem gewünschten anfangen
	ErrInstall EI (WC_NOTFOUND);

		RC = (ErrCode)z_keyfind (&dbaKDBT, INFO, (void *)pOemStart.get());
		if (WC_NOTFOUND == RC) {
		// auf den vorhergehenden positioniert
			if (!(RANGEENUM_PREFIX & rgMode)) {
				RC = (ErrCode)z_keynext (&dbaKDBT, INFO);
				if (EC_OKAY != RC)
					return HRESULT_FROM_ERRCODE(WC_NOTFOUND);
			}
		}
		else if (RANGEENUM_EXCLUSIVESTART & rgMode) {
			RC = (ErrCode)z_keynext (&dbaKDBT, INFO);
			if (EC_OKAY != RC)
				return HRESULT_FROM_ERRCODE(WC_NOTFOUND);
		}
	}
	if (EC_OKAY != RC)
		return HRESULT_FROM_ERRCODE(RC);					// nichts gefunden o.ä.

// MCode und Ident etc. sicherstellen
ErrInstall EI (WC_NOTFOUND);

	do {
	// eigentliche Daten einlesen
	bool fAdvanced = false;

		__ReadHR(dbaKDBT, KDBTSatz);

	// wegen BUG bis jetzt (#HK000113) evtl. Korrekturcode rufen
		if (S_OK == CondCorrectFDBTError (KDBTSatz, dbaKDBT.rec_no)) {
		// zugehörigen Verbindungssatz lesen
			dbaVOM.rec_no = KDBTSatz.zmivom;
			__ReadHR(dbaVOM, VOMSatz);

		// MerkmalsCode besorgen, dazu MKL lesen
			dbaMKL.rec_no = VOMSatz.zvommk;
			__ReadHR(dbaMKL, MKLSatz);

		// gefundenen Satz in der Liste speichern, wenn MCode stimmt
			if (MKLSatz.mk == m_lMCode) {
				if (!(VOMSatz.zvomo & (IDL_MERKMAL|SICHT_MERKMAL))) {
				bool fMatch = true;		// für !SMExact haben wir's gefunden
				
				// ggf. Ident auswerten
					if (0 == lIdent || S_OK == ObjectHasIdent(VOMSatz.zvomo, lIdent)) {
					// Feststellen, ob aktueller Wert noch kleiner(gleich) dem Endwert ist
						if (NULL != pOemEnd.get()) {
							if (S_OK == EndOfRangeReached(VOMSatz.zvomo, pOemEnd.get(), iSrchLen, rgMode))
								return S_OK;		// Ende der Vorstellung
						}

					// nächstes Merkmal suchen
						if ((RC = (ErrCode)z_keynext (&dbaKDBT, INFO)) != EC_OKAY) {
							if (RC == WC_NOTFOUND && (RANGEENUM_EXCLUSIVEEND & rgMode)) 
								return S_OK;	// der aktuelle ist der letzte
							return HRESULT_FROM_ERRCODE(RC);
						}
						fAdvanced = true;

					// dieses Objekt gehört zur Ergebnismenge
						{
						CKeyContext keyCtx;

							hr = trias_connectfilter::EnumObjectsWrapper (m_hPr, VOMSatz.zvomo, 
								GetObjectType(VOMSatz.zvomo), pFcn, dwData);
							if (S_OK != hr) return hr;

							ActDB.ReActivate();
						}
						if (WC_NOTFOUND == RC)
							return S_OK;		// das war der letzte
					}
				}
			}
		}

	// nächstes Merkmal suchen
		if (!fAdvanced) {
		// wenn's noch nicht passiert ist ...
			if ((RC = (ErrCode)z_keynext (&dbaKDBT, INFO)) != EC_OKAY) {
				if (RC == WC_NOTFOUND) 
					return S_OK;
				return HRESULT_FROM_ERRCODE(RC);
			}
		}

	} while (TRUE);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// CreationDate und ModificationDate behandeln
HRESULT CNativeMerkmal::GetCreationDate(DATE *pdCreate)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (NULL == pdCreate)
		return E_POINTER;
	*pdCreate = 0;

	if (0 == m_lMCode || 0 == m_lRecNo)
		return E_UNEXPECTED;

	if (LocGetDBVersion(m_hPr) < VERSION05000013)
		return S_FALSE;

// IdentSatz lesen
CActDB ActDB(m_hPr);
DB_ADDR dbaMKL (m_hPr, MKL, m_lRecNo);
struct mkl MKLSatz;
ErrCode RC;		// FehlerCode

	__ReadHR (dbaMKL, MKLSatz);
	*pdCreate = MKLSatz.mklcreate;
	return S_OK;
}

HRESULT CNativeMerkmal::GetModificationDate(DATE *pdCreate)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (NULL == pdCreate)
		return E_POINTER;
	*pdCreate = 0;

	if (0 == m_lMCode || 0 == m_lRecNo)
		return E_UNEXPECTED;

	if (LocGetDBVersion(m_hPr) < VERSION05000013)
		return S_FALSE;

// IdentSatz lesen
CActDB ActDB(m_hPr);
DB_ADDR dbaMKL (m_hPr, MKL, m_lRecNo);
struct mkl MKLSatz;
ErrCode RC;		// FehlerCode

	__ReadHR (dbaMKL, MKLSatz);
	*pdCreate = MKLSatz.mklmodify;
	return S_OK;
}

} // namespace trias_nativemerkmal
