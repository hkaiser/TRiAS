// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 02.11.2000 16:14:18 
//
// @doc
// @module MapImport.h | Declaration of the <c CMapImport> class

// MapImport.h : Declaration of the CMapImport

#if !defined(_MAPIMPORT_H__E52CB9BE_7A63_4AB6_9860_9A5C361EA4B8__INCLUDED_)
#define _MAPIMPORT_H__E52CB9BE_7A63_4AB6_9860_9A5C361EA4B8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <istatus.h>

#include "resource.h"       // main symbols
#include "ImportDlg.h"

///////////////////////////////////////////////////////////////////////////////
// LizensierungsKlasse
#if defined(_DEBUG)
extern "C" bool g_fGlobalLic;
#else
#define g_fGlobalLic false
#endif // defined(_DEBUG)

class CMyLicense
{
protected:
	static BOOL VerifyLicenseKey(BSTR bstr)
	{
	CComBSTR bstrKey;

		USES_CONVERSION;
		if ((GetLicenseKey (0, &bstrKey) && !wcscmp (bstrKey, bstr)) ||
			 ::SetLicensed (OLE2A(bstr)))
		{
			return TRUE;
		}
		return FALSE;
	}

	static BOOL GetLicenseKey (DWORD, BSTR *pBstr) 
	{
	CComBSTR bstrKey (_MAX_PATH, (LPCOLESTR)NULL);

		if (!::GetLicenseKey (bstrKey.m_str, _MAX_PATH))
			return FALSE;

		*pBstr = bstrKey.Detach(); 
		return TRUE;
	}

	static BOOL IsLicenseValid() { return g_fGlobalLic || ::GetLicensed(); }
};

/////////////////////////////////////////////////////////////////////////////
// CMapImport
class ATL_NO_VTABLE CMapImport : 
	public CComCoClass<CMapImport, &CLSID_MapImport>,
	public CTriasExtension 
{
private:
	CString	 m_strDstDir;				// Name des Zielverzeichnisses

// KK010314
	bool	InstallMainMenu(void);
	void	RemoveMainMenu(void);

// KK001122
	bool	DoMultiImport( CMapImportDlg& dlg );
	bool	OnMultiMap( CMapImportDlg& , const char * );
	bool	OnMultiTag(CMapImportDlg& dlg);
	bool	OnReduceMap(CMapImportDlg& dlg);
	bool	OnMapCoordinate(CMapImportDlg& );
	bool	OnMultiDoc( CMapImportDlg& ) ;

	bool	DoTheImport( CMapImportDlg& dlg );
	bool	WriteProfileString(LPCSTR lpszSection, LPCSTR lpszEntry, LPCSTR lpszValue);
	CString GetMyProfileString(LPCSTR lpszSection, LPCSTR lpszEntry, LPCSTR lpszDefault) ;

	bool DoImport(CMapImportDlg& dlg, long &rlNum, DWORD dwNoReduce, 
		IProgressIndicator *pProgressIndicator, LPCTSTR pcMap);

	HRESULT SetObjVisInfo (long lIdent, long lONr, long lMCode);

public:
	CMapImport();

	DECLARE_NOT_AGGREGATABLE_SINGLE(CMapImport, g_pTE)
	DECLARE_REGISTRY_RESOURCEID(IDR_MAPIMPORT)
	DECLARE_CLASSFACTORY2(CMyLicense)

	BEGIN_COM_MAP(CMapImport)
		COM_INTERFACE_ENTRY(IUnknown)
		COM_INTERFACE_ENTRY_CHAIN(CTriasExtension)
	END_COM_MAP()

	BEGIN_MSG_MAP(CMapImport)
		COMMAND_ID_HANDLER(ID_MAPIMPORT, OnMapImport )
	END_MSG_MAP()
	
protected:
	HOBJECT CreateArea (HOBJECTS ident, long nCoords, double *pX, double *pY, ITRiASCS*pICS);
	HOBJECT CreatePoint (HOBJECTS ident, double X, double Y, ITRiASCS *pICS);
	bool ModifyObjectFeature (HOBJECT objNum, HFEATURE lMCode, CString &rString);
	bool SetObjectFeature (HFEATURE &rlMCode, HOBJECTS lIdent, CString &rString);
	HOBJECTS GetIdentifikator(HPROJECT hPr, CString &iString, CString &tString);

protected:
	LRESULT OnMapImport(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

public:
/////////////////////////////////////////////////////////////////////////////
// IMapImport

// ITriasXtension
public:
	STDMETHOD_(BOOL, InitExtension) (short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (void);

	STDMETHOD_(BOOL, MenuCommand) (THIS_ UINT uiMenuID, HWND hWnd) 
	{
		LRESULT	lResult;
		WORD	nfyCode = 0;
		WPARAM	wp = MAKELONG( uiMenuID, nfyCode );
		return ProcessWindowMessage(__hWndM, WM_COMMAND, wp, (LPARAM) hWnd, lResult );
	}

};

#endif // !defined(_MAPIMPORT_H__E52CB9BE_7A63_4AB6_9860_9A5C361EA4B8__INCLUDED_)
