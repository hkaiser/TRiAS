// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.07.99 21:27:44
//
// @doc
// @module QueryDefUtil.cpp | Implementation of the <c CQueryDefUtil> class

#include <StdAfx.h>

///////////////////////////////////////////////////////////////////////////////
// FormatMessage aus MessageTyble in ein CString
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
// Spezielle Messagebox mit Formatiermöglichkeiten
int __cdecl VMessageBox (UINT uiCaption, UINT uiType, UINT uiText, ...)
{
CString strCap, strText;

	VERIFY(strCap.LoadString (uiCaption));
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

		return Wnd.MessageBox (pcOut, strCap, uiType);
	}
	return Wnd.MessageBox (strText, strCap, uiType);
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

		return Wnd.MessageBox (pcOut, pcCaption, uiType);
	}
	return Wnd.MessageBox (strText, pcCaption, uiType);
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

///////////////////////////////////////////////////////////////////////////////
// Sammeln aller selektierten Objektes eines oder aller Recherchefenster
namespace {
	BOOL CALLBACK EnumSelectedObjects (long lONr, BOOL, void *pData)
	{
		*reinterpret_cast<insert_iterator<CSelectedObjects> *>(pData) = lONr;
		return TRUE;
	}
}

bool CollectSelectedObjects (HWND hWnd, insert_iterator<CSelectedObjects> it)
{
ENUMLONGKEY ELK;

	ELK.eKey = reinterpret_cast<INT_PTR>(hWnd);
	ELK.eFcn = reinterpret_cast<ENUMLONGKEYPROC>(EnumSelectedObjects);
	ELK.ePtr = reinterpret_cast<void *>(&it);
	return DEX_EnumSelectedObjects(ELK) ? true : false;
}

