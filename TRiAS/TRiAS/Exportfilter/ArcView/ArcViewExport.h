// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 03.07.2000 10:40:04 
//
// @doc
// @module ArcViewExport.h | Declaration of the <c CArcViewExport> class

#if !defined(_ARCVIEWEXPORT_H__F17ED7FE_C060_4067_915B_174D4A0A276C__INCLUDED_)
#define _ARCVIEWEXPORT_H__F17ED7FE_C060_4067_915B_174D4A0A276C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__)
#endif

#include "ExportHelper.h"

///////////////////////////////////////////////////////////////////////////////
// Versionsnummern
const long SHP_VERSION = 0x0100L;
const long LASTKNOWN_SHP_VERSION = SHP_VERSION;

/////////////////////////////////////////////////////////////////////////////
// CArcViewExport

class ATL_NO_VTABLE CArcViewExport :
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CArcViewExport, &CLSID_ArcViewExport>,
	public IDispatchImpl<IArcViewExport, &IID_IArcViewExport, &LIBID_ArcViewExport>,
	public CErrSupport<CArcViewExport, &IID_IArcViewExport>,
	public CPersistStreamInitImpl<CArcViewExport, &CLSID_ArcViewExport>,
	public CTRiASOEProxyImpl<CArcViewExport, &CLSID_ArcViewExport>,
	public CExportHelper
{
private:
	DECLARE_ERRSUPPORTENTRY(CArcViewExport, &IID_IArcViewExport);

public:
	CArcViewExport() :
		CTRiASOEProxyImpl_t(IDS_DISPLAYNAME, IDS_DEFEXT)
	{
	}
	HRESULT FinalConstruct() 
	{
		COM_TRY {
			ERROR_FAILED_HRESULT(CExtDataEngineImpl_t_FinalConstruct(), E_FAIL);
		} COM_CATCH;
		return S_OK;
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_ARCVIEWEXPORT)
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_CLASSFACTORY2(CVerifyExportLicense)

	BEGIN_COM_MAP(CArcViewExport)
		COM_INTERFACE_ENTRY(ITRiASExtDataEngine)
		COM_INTERFACE_ENTRY(IArcViewExport)
		COM_INTERFACE_ENTRY2(IDispatch, IArcViewExport)
		COM_INTERFACE_ENTRY_CHAIN(CExtDataEngineImpl_t)
		COM_INTERFACE_ENTRY_CHAIN(CPersistStreamInitImpl_t)
		COM_INTERFACE_ENTRY_CHAIN(CTRiASOEProxyImpl_t)
	END_COM_MAP()

	BEGIN_CATEGORY_MAP(CArcViewExport)
		IMPLEMENTED_CATEGORY(CATID_TRiASExportModule)
	END_CATEGORY_MAP()

	BEGIN_EXTDATAENGINECAPABILITY_MAP(CArcViewExport)
		EXTDATAENGINECAPABILITY_ENTRY(L"CanExportStandalone", FALSE)
		EXTDATAENGINECAPABILITY_ENTRY(L"CanSpecifyTransformation", FALSE)
		EXTDATAENGINECAPABILITY_ENTRY(L"CanSeparateOutput", FALSE)
		EXTDATAENGINECAPABILITY_ENTRY(L"NeedRawCoordinates", FALSE)
		EXTDATAENGINECAPABILITY_ENTRY(L"OutputIsDirectory", TRUE)
		EXTDATAENGINECAPABILITY_ENTRY(L"EC_StandardMerkmale", FALSE)
		EXTDATAENGINECAPABILITY_ENTRY(L"EC_MerkmalDescription", TRUE)
		EXTDATAENGINECAPABILITY_ENTRY(L"EC_IdentDescription", FALSE)
		EXTDATAENGINECAPABILITY_ENTRY(L"EC_Relationen", FALSE)
		EXTDATAENGINECAPABILITY_ENTRY(L"*", FALSE)
	END_EXTDATAENGINECAPABILITY_MAP()

// IArcViewExport
public:
// ITRiASExtDataEngine
	STDMETHOD(ExportData)(IDispatch * pXMLDocument) 
	{
		return E_NOTIMPL;
	}
	STDMETHOD(ImportData)(IDispatch * * ppXMLDocument) 
	{
		return E_NOTIMPL;
	}

// CExportDefaultInterfaceImpl
	ErrCode ExportBegin(char *lpFileName, OFSTRUCT &of, OutMode OutFlag, HWND hWnd, const char* lpszDatasource);
// KK001023
//	ErrCode ExportIdentDescription(OFSTRUCT &of, const char* lpszOKS, const char* pcShort, const char* pcLong, const long lVisType, const VISINFO *pVI);
	ErrCode ExportIdentDescription(OFSTRUCT &of, const char* lpszOKS, const char* pcShort, const char* pcLong, const long lVisType, const VISINFO *pVI, long lIdent);

	ErrCode ExportMerkmalDescription(long lMCode, char *pbuf, short iTyp, short iLen);
	ErrCode ExportComment (OFSTRUCT &of, const char *pcComment);
	ErrCode ExportHeader(OFSTRUCT &of, const char *pcHeader);
	ErrCode ExportDescriptionEx(OFSTRUCT &of, LPCSTR lpKeyInfo, LPCSTR lpDescString, DWORD dwStyle);
	ErrCode ExportTrailer(OFSTRUCT &of, const char *lpTrailerString);
	ErrCode ExportData(OFSTRUCT &of, GSTRUCT &GS, MFELD *MF, RSTRUCT *pRS, LPCTSTR pUIdent, LPCTSTR lpszGUID, LPCTSTR pParentClass);
	ErrCode ExportEnd(OFSTRUCT &of);
	ErrCode ExportBreak(OFSTRUCT &of);

// CPersistStreamInitImpl
	HRESULT	OnInitNew();
	HRESULT LoadData(LPSTREAM pStm, DWORD dwVersion);
	HRESULT SaveData(LPSTREAM pStm, BOOL bClearDirty);
	LONGLONG GetDataSize();

// IPersistStreamInit etc.
	static DWORD GetSignature() { const char *s = "ASHP"; return *((DWORD*)s); }
	static DWORD GetVersion() { return LASTKNOWN_SHP_VERSION; }

protected:
	HRESULT GetShortDesc(long lIdent, os_string &rStrShort);
	HRESULT GetOKS(long lIdent, os_string &rStrOKS);
};

namespace {
///////////////////////////////////////////////////////////////////////////////
// sämtliche Sonderzeichen ('.', '/', '\\' etc.) im Namen ersetzen
	inline
	os_string CorrectName (LPCSTR pcName)
	{
	os_string strName (pcName);
	size_t iLen = strName.size();

		for (int i = 0; i < iLen; i++) {
		char c = strName[i];

			switch (c) {
			case '.':
			case '\\':
			case '/':
			case ':':
			case '!':
				strName[i] = '_';
				break;

			case '\0':		// Ende des Strings
				break;

			default:
				if (c > ' ')
					strName[i] = c;
				else
					strName[i] = '_';
				break;
			}
		}
		return strName;
	}
}

#endif // !defined(_ARCVIEWEXPORT_H__F17ED7FE_C060_4067_915B_174D4A0A276C__INCLUDED_)

