/////////////////////////////////////
// fakename.cpp
// Routinen zum ändern des angezeigten Programmnamens 

#include "pheader.h"	// the precompiled header
#include "fakename.h"	// our header

#include <registrx.hxx>	// the registryclasses
// #include "ODBCEXT.HPP"	// the extension header

char g_cbTRiAS[_MAX_PATH];						// the cached AppName
const char g_cbCopyrightName[] = TEXT("TRiAS"); // a defaultval
const char g_cbTRiASName[] = TEXT("TRiASName");	// where i'll get the Name from
const char g_cbRegConfig[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Config"); // c above
const TCHAR g_cbNil[] = TEXT("");

void InitFakeName()
{
// unseren aktuellen Namen besorgen
	{
	CCurrentUser regCfg (g_cbRegConfig, false, KEY_READ);
	DWORD dwSize = _MAX_PATH;

		if (!regCfg.GetSubSZ (g_cbTRiASName, g_cbTRiAS, dwSize))
			strcpy (g_cbTRiAS, g_cbCopyrightName);		// default
	}
}

CString FakeName (UINT resID)
{
	TRY 
	{
		CString resTempl; 
		resTempl.LoadString (resID);
		return FakeName(resTempl); 
	} 
	CATCH (CMemoryException, e) 
	{
	// irgendein Fehler
		return CString(g_cbNil);
	} END_CATCH;
}

CString FakeName (LPCTSTR pcTempl)
{
	TRY 
	{
		CString strRes;
		strRes.Format(pcTempl, g_cbTRiAS);
		return CString(strRes);
	} 
	CATCH (CMemoryException, e) 
	{
	// irgendein Fehler
		return CString(g_cbNil);
	} END_CATCH;
}

CString FakeName (CWnd* pWnd)
{
	if (pWnd)
	{
		try {
			CString strResult;
			pWnd->GetWindowText(strResult);
			strResult = FakeName(strResult);
			pWnd->SetWindowText(strResult);
			return CString(strResult);
		} catch (...) {
		}
	}
	return CString(g_cbNil);
}