// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 12/03/1998 08:09:28 PM
//
// @doc
// @module TRiASIconHandler.cpp | Implementation of the <c CTRiASIconHandler> class

#include "stdafx.h"

#include "TRiASICN.h"
#include "TRiASIconHandler.h"

EXTERN_C const CLSID CLSID_OleDocumentWrapper;
EXTERN_C const CLSID CLSID_DirisProject;

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(Storage);
DefineSmartInterface(Stream);

/////////////////////////////////////////////////////////////////////////////
// CTRiASIconHandler

// IExtractIcon Implementation 
STDMETHODIMP CTRiASIconHandler::GetIconLocation(
	UINT uFlags, LPSTR szIconFile, UINT cchMax, int *piIndex, UINT *pwFlags) 
{   
// alle Icons sind in unserem Module
TCHAR szModule[_MAX_PATH];

	GetModuleFileName (_Module.GetModuleInstance(), szModule, _MAX_PATH);

TCHAR szModuleShort[_MAX_PATH];
int cbShortName = GetShortPathName (szModule, szModuleShort, _MAX_PATH);
LPSTR pszModule;

	if (cbShortName == _MAX_PATH)
		return E_OUTOFMEMORY;
	pszModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? (szModule) : (szModuleShort);
	strcpy (szIconFile, pszModule);

//	*pwFlags = GIL_SIMULATEDOC;

// Typ der Datei testen
	if (S_OK != ::StgIsStorageFile (m_bstrFileName)) {
		*piIndex = IDI_BUCHICON1-1;		// .stb ?
		return S_OK;
	}

	COM_TRY {
	// die Datei ist eine StorageDatei
	WStorage Stg;

	// versuchen, Datei im Schreibmode zu öffnen, damit unter Umständen keine Kopie der Datei angelegt werden muß
	// lediglich, wenn das fehlschlägt, dann im Schreibschutzmode eine Kopie anlegen lassen und mit dieser
	// weiterarbeiten
		if (FAILED(::StgOpenStorage (m_bstrFileName, NULL, STGM_READWRITE|STGM_SHARE_DENY_WRITE|STGM_TRANSACTED, 0, 0, Stg.ppi())))
		{
			THROW_FAILED_HRESULT(::StgOpenStorage (m_bstrFileName, NULL, STGM_READ|STGM_TRANSACTED, 0, 0, Stg.ppi()));
		}

	// entscheiden, was es ist
	CLSID ClsId;

		THROW_FAILED_HRESULT(::ReadClassStg(Stg, &ClsId));
		if (IsEqualCLSID(ClsId, CLSID_OleDocumentWrapper))
			*piIndex = IDI_PROJECT-1;	// .riw
		else {
		// sollte .ris/.stb sein
			_ASSERTE(IsEqualCLSID(ClsId, CLSID_DirisProject));

		// Dictionary eröffnen
		WStream Strm;
		
			THROW_FAILED_HRESULT(Stg -> OpenStream (L"DatenBankStruktur", 0, STGM_READ|STGM_SHARE_EXCLUSIVE, 0, Strm.ppi()));
			
		// das vorletzte DWORD enthält die GeoDB-Version
		LARGE_INTEGER li;
		LARGE_INTEGER uli;

			li.QuadPart = 0;
			THROW_FAILED_HRESULT(Strm -> Seek (li, STREAM_SEEK_END, (ULARGE_INTEGER *)&uli));

			uli.QuadPart = uli.QuadPart - 3*sizeof(long);
			THROW_FAILED_HRESULT(Strm -> Seek (uli, STREAM_SEEK_SET, NULL));

		// 'alte' Varianten haben im letzten DWORD die Pagegröße (!= 0 und != 1) und im vorletzten 
		// die Version, 'neue' Varianten haben im vorletzten die Pagegröße und im drittletzten die
		// Version.
		DWORD Versions[3];

			memset (Versions, '\0', 3*sizeof(DWORD));
			THROW_FAILED_HRESULT(Strm -> Read (Versions, 3*sizeof(DWORD), NULL));
			if (0 != Versions[2] && 1 != Versions[2]) 
				*piIndex = (Versions[1] < 0x0500000F) ? IDI_BUCHICON2-1 : IDI_BUCHICON3-1;
			else {
				if (Versions[0] < 0x0500000F)
					*piIndex = IDI_BUCHICON2-1;
				else
					*piIndex = (0 != Versions[2]) ? IDI_BUCHICON4-1 : IDI_BUCHICON3-1;	// evtl. komprimiert
			}
		}
				
	} COM_CATCH_RETURN(S_FALSE);	// bei Fehler default Icon verwenden
	return S_OK;
} 
 
 
STDMETHODIMP CTRiASIconHandler::Extract(
	LPCSTR pszFile, UINT nIconIndex, HICON *phiconLarge, HICON *phiconSmall, UINT nIconSize) 
{ 
    return S_FALSE; 
} 
 
///////////////////////////////////////////////////////////////////////////////
// IPersistFile Implementation 
STDMETHODIMP CTRiASIconHandler::GetClassID(LPCLSID lpClassID) 
{ 
    return E_FAIL; 
} 
 
STDMETHODIMP CTRiASIconHandler::IsDirty() 
{ 
    return S_FALSE; 
} 
 
STDMETHODIMP CTRiASIconHandler::Load(LPCOLESTR lpszFileName, DWORD grfMode) 
{
	m_bstrFileName = lpszFileName;
    return NOERROR; 
} 
 
STDMETHODIMP CTRiASIconHandler::Save(LPCOLESTR lpszFileName, BOOL fRemember) 
{ 
    return E_FAIL; 
} 
 
STDMETHODIMP CTRiASIconHandler::SaveCompleted(LPCOLESTR lpszFileName) 
{ 
    return E_FAIL; 
} 
 
STDMETHODIMP CTRiASIconHandler::GetCurFile(LPOLESTR FAR* lplpszFileName) 
{ 
    return E_FAIL; 
} 
 
