// @doc
// @module DBUTIL.CPP | Allgemeine Makrodefinitionen et.al.

#include "StdAfx.h"

#include "resource.h"

#include <Com/SafeArray.h>
#include <ospace/file/path.h>

#include "Wrapper.h"			// SmartIF's
#include "Strings.h"			// StringKonstanten
#include "TRiASDBDispIds.h"		// Dispatch Ids

#include "TRiASDBApp.h"			// application object

#import "tlb/Helper.tlb" \
	raw_interfaces_only raw_dispinterfaces no_namespace named_guids \
	exclude("IParseRegularExpression", "IParseStringPairs", "IComposeStringPairs") \
	exclude("IParseStringPairs2")

///////////////////////////////////////////////////////////////////////////////
// ÷ffnen/Erzeugen eines SubStorages
HRESULT GetSubStorage (
	IStorage *pIRootStg, LPCOLESTR poleName, REFCLSID rClsId,
	IStorage **ppIStg, bool fCreate)
{
	if (NULL == ppIStg) return E_POINTER;
	if (NULL == pIRootStg) return E_INVALIDARG;

WStorage IStg;
HRESULT hr = E_FAIL;
bool fSetDirty = false;

	{
	bool fRO = false;

		hr = pIRootStg -> OpenStorage (poleName, NULL, 
							STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 
							NULL, 0L, IStg.ppi());
		if (FAILED(hr)) {
			if (STG_E_FILENOTFOUND == GetScode(hr) && fCreate) {
			// existiert nicht, evtl. neu erzeugen
				hr = pIRootStg -> CreateStorage (poleName, 
									STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED|STGM_CREATE, 
									0L, 0L, IStg.ppi());
				if (SUCCEEDED(hr))
					hr = ::WriteClassStg (IStg, rClsId);
				
				fSetDirty = true;

			} else if (STG_E_ACCESSDENIED == GetScode(hr)) {
			// mit Schreibschutz versuchen
				hr = pIRootStg -> OpenStorage (poleName, NULL, 
								STGM_READ|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 
								NULL, 0L, IStg.ppi());
				fRO = true;
			} else
				return hr;
		} 

		if (SUCCEEDED(hr)) {
		CLSID clsId;

			hr = ::ReadClassStg (IStg, &clsId);
			if (FAILED(hr)) return hr;

			if (!IsEqualCLSID(clsId, rClsId) && !IsEqualCLSID(clsId, CLSID_NULL))
			{
				return E_FAIL;
			}

			if (IsEqualCLSID(clsId, CLSID_NULL) && !fRO) {
				hr = ::WriteClassStg (IStg, rClsId);
				fSetDirty = true;
			}
		}
	}
	if (FAILED(hr)) return hr;

	*ppIStg = IStg.detach();
	return fSetDirty ? S_FALSE : S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ÷ffnen/Erzeugen des SubStreames
HRESULT GetSubStream (
	IStorage *pIRootStg, LPCOLESTR poleName, IStream **ppIStm, bool fCreate)
{
	if (NULL == ppIStm) return E_POINTER;
	if (NULL == pIRootStg) return E_INVALIDARG;

WStream IStm;
HRESULT hr = S_OK;

	if (fCreate) {
		hr = pIRootStg -> CreateStream (poleName, 
						STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_CREATE, 
						0L, 0L, IStm.ppi());
	} else {
		hr = pIRootStg -> OpenStream (poleName, NULL, 
						STGM_READWRITE|STGM_SHARE_EXCLUSIVE, 0L, IStm.ppi());
	}
	if (FAILED(hr)) return hr;

	*ppIStm = IStm.detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// FormatMessage aus MessageTable in ein CString
void __cdecl FormatMessage(CString &rStr, UINT uiError, ...)
{
// format message into temporary buffer lpszTemp
DWORD dwFlags = FORMAT_MESSAGE_FROM_HMODULE|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER;
LPTSTR lpszTemp = NULL;
va_list argList;

	va_start(argList, uiError);
	if (::FormatMessage (dwFlags, _Module.GetResourceInstance(), uiError, 0, (LPTSTR)&lpszTemp, 0, &argList) == 0 ||
		lpszTemp == NULL)
	{
#if defined(_DEBUG)
		dwFlags = FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_IGNORE_INSERTS;

	DWORD dwError = GetLastError();

		::FormatMessage (dwFlags, NULL, dwError, 0, (LPTSTR)&lpszTemp, 0, NULL);
		rStr = lpszTemp;
#else
		rStr = g_cbNoMemory;
#endif // _DEBUG
	}
	else	// assign lpszTemp into the resulting string and free lpszTemp
		rStr = lpszTemp;

	if (lpszTemp) LocalFree(lpszTemp);
	va_end(argList);
}

///////////////////////////////////////////////////////////////////////////////
// Spezielle Messagebox mit Formatiermˆglichkeiten
int __cdecl VMessageBox (UINT uiCaption, UINT uiType, UINT uiText, ...)
{
CString strCap, strText;

	VERIFY(strCap.LoadString (uiCaption));
	VERIFY(strText.LoadString (uiText));

CString strOut;
LPTSTR pcOut = NULL;

	ATLTRY(pcOut = strOut.GetBufferSetLength(_MAX_PATH*4));
	if (NULL != pcOut) {
	va_list params;

		va_start (params, uiText);
	//lint --e(534)
		wvsprintf (pcOut, strText, params);
		va_end (params);

		return AfxGetMainWnd() -> MessageBox (pcOut, strCap, uiType);
	}
	return AfxGetMainWnd() -> MessageBox (strText, strCap, uiType);
}

int __cdecl VMessageBox (LPCSTR pcCaption, UINT uiType, UINT uiText, ...)
{
CString strText;

	VERIFY(strText.LoadString (uiText));

CWnd Wnd;
CString strOut;
LPTSTR pcOut = NULL;

	ATLTRY(pcOut = strOut.GetBufferSetLength(_MAX_PATH*4));
	if (NULL != pcOut) {
	va_list params;

		va_start (params, uiText);
	//lint --e(534)
		wvsprintf (pcOut, strText, params);
		va_end (params);

		return AfxGetMainWnd() -> MessageBox (pcOut, pcCaption, uiType);
	}
	return AfxGetMainWnd() -> MessageBox (strText, pcCaption, uiType);
}

///////////////////////////////////////////////////////////////////////////////
// Formatierfunktionen
os_string __cdecl FakeTRiASName (UINT resID, ...)
{
CString strText;

	VERIFY(strText.LoadString (resID));

	COM_TRY {
	CString strOut;
	LPTSTR pcOut = strOut.GetBufferSetLength(_MAX_PATH*4);
	va_list params;

		va_start (params, resID);
	//lint --e(534)
		wvsprintf (pcOut, strText, params);
		va_end (params);
		return os_string(pcOut);
	
	} COM_CATCH_IGNORE;		// irgendein Fehler

	return os_string((LPCSTR)strText);
}

os_string __cdecl FakeTRiASName (LPCSTR pcTempl, ...)
{
	COM_TRY {
	CString strOut;
	LPTSTR pcOut = strOut.GetBufferSetLength(_MAX_PATH*4);
	va_list params;

		va_start (params, pcTempl);
	//lint --e(534)
		wvsprintf (pcOut, pcTempl, params);
		va_end (params);
		return os_string(pcOut);
	
	} COM_CATCH_IGNORE;		// irgendein Fehler

	return os_string(pcTempl);
}

///////////////////////////////////////////////////////////////////////////////
// Radix-Konvertierung

long Hex2Dec (long lHex)		// not very useful
{
char cbBuffer[32];
	 
//lint --e(534)
	_ltot (lHex, cbBuffer, 16);
	return _tcstol (cbBuffer, NULL, 10);
}

long Dec2Hex (long lDec)		// very useful
{
char cbBuffer[32];
	 
//lint --e(534)
	_ltot (lDec, cbBuffer, 10);
	return _tcstol (cbBuffer, NULL, 16);
}

///////////////////////////////////////////////////////////////////////////////
// OBJECTTYPE zu TRiAS-Objektbits konvertieren

DWORD OBJECTTYPEToBits (OBJECTTYPE rgType)
{
DWORD dwResult = 0L;

	if (rgType & OBJECTTYPE_Point) 
		dwResult |= OTPunkt;
	if (rgType & OBJECTTYPE_Line)
		dwResult |= OTLinie;
	if (rgType & OBJECTTYPE_Area)
		dwResult |= OTFlaeche;
	if (rgType & OBJECTTYPE_Text)
		dwResult |= OTText;
	if (rgType & OBJECTTYPE_Complex)
		dwResult |= OTKO;

	return dwResult;
}

// Objektbits zu OBJECTTYPE konvertieren

OBJECTTYPE BitsToOBJECTTYPE (DWORD dwTypes)
{
DWORD dwResult = OBJECTTYPE_Unknown;

	if (dwTypes & OTPunkt)
		dwResult |= OBJECTTYPE_Point;
	if (dwTypes & OTLinie)
		dwResult |= OBJECTTYPE_Line;
	if (dwTypes & OTFlaeche)
		dwResult |= OBJECTTYPE_Area;
	if (dwTypes & OTText)
		dwResult |= OBJECTTYPE_Text;

	return (OBJECTTYPE)dwResult;
}

/////////////////////////////////////////////////////////////////////////////
// FileHandling
bool TestFileRO (LPCSTR pcName, BOOL &rRO)
{
DWORD dwAttr = ::GetFileAttributes (pcName);

	if ((DWORD)-1 == dwAttr)
		return false;

	rRO = (FILE_ATTRIBUTE_READONLY & dwAttr) ? TRUE : FALSE;
	return true;
}

// stellt fest, ob das angegebene Verzeichnis die Besonderheiten eines Novell-Verzeichnisses 
// besitzt (sharingcontrol nicht selbst machen)
// vorerst wird dieser Test an Hand der Existenz einer Datei 'TRiAS.Dir' erledigt
bool IsNovellDrive (BSTR bstrName)
{
#if defined(_USE_BADLY_HACKED_NOVELL_PATCH)
extern DWORD g_dwFlags;

	if (!(g_dwFlags & REG_USE_NOVELLTESTCODE))
		return false;	// nicht auf 'Novell' testen

	USES_CONVERSION;

os_path path (OLE2A(bstrName));

	path.filename("TRiAS.Dir");
	return ((DWORD)-1 == ::GetFileAttributes (os_string(path).c_str())) ? false : true;
#else
	return false;
#endif // defined(_USE_BADLY_HACKED_NOVELL_PATCH)
}

/////////////////////////////////////////////////////////////////////////////
// Handle der zugehˆrigen Datenbank holen
HRESULT RetrieveDBHandle (IUnknown *pIObj, HPROJECT *phPr)
{
	COM_TRY {
	WTRiASDatabase Parent;

		THROW_FAILED_HRESULT(FindSpecificParent(pIObj, Parent.ppi()))
		THROW_FAILED_HRESULT(Parent -> get_Handle ((INT_PTR *)phPr));

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Supportfunktionen f¸r RechercheFunktionalit‰t
namespace {
	int iMatchCompleteLen = wcslen (SEARCHCOMMAND_MatchComplete);
	int iMatchRegExprLen = wcslen (SEARCHCOMMAND_MatchRegExpr);
	int iMatchLikeLen = wcslen (SEARCHCOMMAND_MatchLike);
	int iExistanceOnlyLen = wcslen (SEARCHCOMMAND_ExistanceOnly);
}

int MainModeFromSearchCommand (BSTR bstrCommand)
{
int iSearchMode = 0;

	if (!wcsncmp (bstrCommand, SEARCHCOMMAND_MatchComplete, iMatchCompleteLen))
		iSearchMode = SMExactMatch;
	else if (!wcsncmp (bstrCommand, SEARCHCOMMAND_MatchRegExpr, iMatchRegExprLen))
		iSearchMode = SMRegularExpression;	
	else if (!wcsncmp (bstrCommand, SEARCHCOMMAND_MatchLike, iMatchLikeLen))
		iSearchMode = SMInexactMatch;	
	else if (!wcsncmp (bstrCommand, SEARCHCOMMAND_ExistanceOnly, iExistanceOnlyLen))
		iSearchMode = SMExistanceOnly;	

	_ASSERTE(0 != iSearchMode);
	return iSearchMode;		// im Zweifelsfall vollst‰ndig testen
}

inline 
ULONG HasOptionValue (IParseStringPairs *pIPairs, LPCOLESTR pcoleOption, ULONG lDefaultVal)
{
CComBSTR bstrValue;

	if (S_OK == pIPairs-> get_Value (CComBSTR(pcoleOption), CLEARED(&bstrValue)))
		return wcstoul (bstrValue, NULL, 10);
	return lDefaultVal;
}

DefineSmartInterface(ParseStringPairs);

int ModeFromSearchCommand (BSTR bstrCommand)
{
int iSearchMode = 0;

	COM_TRY {
	wchar_t *pTmp = wcschr (bstrCommand, L';');		// Optionen vorhanden ?
	CComBSTR bstrMain;

		if (NULL == pTmp) 
			iSearchMode = MainModeFromSearchCommand(bstrCommand);		// hier ist alles klar
		else {
			bstrMain = CComBSTR(pTmp-bstrCommand, bstrCommand);
			iSearchMode = MainModeFromSearchCommand (bstrMain);

		WParseStringPairs Parse (CLSID_ParseStringPairs);	// throws hr
		CComBSTR bstrVal;
		long lPairs = 0;

			THROW_FAILED_HRESULT(Parse -> put_Pattern(CComBSTR(g_cbCollatePattern)));
			THROW_FAILED_HRESULT(Parse -> Parse(CComBSTR(pTmp), &lPairs));

		// evtl. Optionen verfeinern
			if (SMExactMatch == iSearchMode) {
				if (HasOptionValue (Parse, SEARCHOPTION_PartialMatch, 0))
					iSearchMode = SMSubstringMatch;
				if (HasOptionValue (Parse, SEARCHOPTION_PartialMatchBOB, 0))
					iSearchMode = SMSubStringStartMatch;
			} 
			else if (SMRegularExpression == iSearchMode) {
				if (HasOptionValue (Parse, SEARCHOPTION_PartialMatch, 0))
					iSearchMode = SMSubstringMatch;
			}
			else if (SMSubRegularExpression == iSearchMode) {
				iSearchMode = SMSubstringMatch;
			}

			if (HasOptionValue (Parse, SEARCHOPTION_IgnoreCase, 0))
				iSearchMode |= SMIgnoreCase;
			if (HasOptionValue (Parse, SEARCHOPTION_NegateResult, 0))
				iSearchMode |= SMNegateResult;
		}
	} COM_CATCH_RETURN(0);

	_ASSERTE(0 != iSearchMode);
	return iSearchMode;
}

///////////////////////////////////////////////////////////////////////////////
// Rechercheparameter liefern
HRESULT RetrieveSearchParams (BSTR bstrCommand, SAFEARRAY *pParams, BSTR *pbstrPattern, int *piMode)
{
	COM_TRY {
	CSafeArray sa(VT_VARIANT);

		if (NULL == pParams || !sa.Attach (pParams, true)) 
			return E_INVALIDARG;

	CSafeArrayLock<VARIANT> lock(sa);
	CComVariant vPattern;

		_ASSERTE(lock.Size() >= 1);		// mindestens 1 Element muﬂ gegeben sein
		if (FAILED(vPattern.ChangeType (VT_BSTR, &lock[0])))
			return E_INVALIDARG;

	CComBSTR bstrPattern (V_BSTR(&vPattern));

		*pbstrPattern = bstrPattern.Detach();
		if (NULL != piMode)
			*piMode = ModeFromSearchCommand(bstrCommand);

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// eine beliebige Resource laden
BYTE *ReadResource (int iResID, DWORD &dwResSize, HINSTANCE hInstance)
{
	if (NULL == hInstance)
		hInstance = _Module.GetResourceInstance();

BYTE *lpResult = NULL;

//  Resource laden
HRSRC hFindRes = FindResource (hInstance, MAKEINTRESOURCE (iResID), MAKEINTRESOURCE (ID_DBDTEMPLATE));
HGLOBAL hRes = LoadResource (hInstance, hFindRes);

	if (!hFindRes || !hRes) return NULL;

//  Resource im Speicher festhalten
BYTE *lpResource = (BYTE *)LockResource (hRes);

	if (lpResource) {	    // wenn Resource erfolgreich geladen
	// Resource in Buffer kopieren
		if ((dwResSize = SizeofResource (hInstance, hFindRes)) == 0)
			return NULL;

	// einfach umkopieren
		ATLTRY(lpResult = new BYTE [dwResSize]);
		if (NULL == lpResult) return NULL;

		CopyMemory(lpResult, lpResource, dwResSize);

	// Resource wieder freigeben
		UnlockResource (hRes);
		FreeResource (hRes);
	} else {
	// Resource existiert nicht
		FreeResource (hRes);
		return NULL;
	}
	return lpResult;
}

