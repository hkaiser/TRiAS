// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 03.07.2000 11:21:03
//
// @doc
// @module ArcViewExp.cpp | Routinen zum schreiben des Shape-Formates

#include "stdafx.h"
#include "ArcViewImpl.h"

#include <Errinstx.hxx>

#include "../ExtDataEngineImpl.h"
#include "../CTRiASOEProxyImpl.h"

#include "ArcView.hmc"
#include "ArcViewExport.h"

HWND __hWndM = NULL;
UINT __DexCmd = 0;

///////////////////////////////////////////////////////////////////////////////
// Begin des DatenExports 
ErrCode CArcViewExport::ExportBegin(
	char *lpFileName, OFSTRUCT &of, OutMode OutFlag, HWND hWnd, const char *lpszDatasource) 
{
	if (SUCCEEDED(GetRootDir()))
		return EC_OKAY;
	
// FensterHandle merken
	USES_CONVERSION;

CComBSTR strDEXMessage;

	strDEXMessage.LoadString(IDS_DEXMESSAGE);
	__hWndM = hWnd;
	__DexCmd = RegisterWindowMessage(W2A(strDEXMessage));

// aktuelles Wurzelverzeichnis setzen
HRESULT hr = SetRootDir (lpFileName, OutFlag);

	if (FAILED(hr)) {
		SetLastError(hr);
		return EC_FAIL;
	}

// aktuelle Datenquelle setzen
	hr = SetDataSource (lpszDatasource);
	if (FAILED(hr)) {
		SetLastError(hr);
		return EC_FAIL;
	}
	return EC_OKAY;
}

///////////////////////////////////////////////////////////////////////////////
// Objektklassendefinition 
// KK001023
//ErrCode CArcViewExport::ExportIdentDescription(
//	OFSTRUCT &of, const char* lpszOKS, const char* pcShort, const char* pcLong, 
//	const long lVisType, const VISINFO *pVI) 
ErrCode CArcViewExport::ExportIdentDescription(
	OFSTRUCT &of, const char* lpszOKS, const char* pcShort, const char* pcLong, 
	const long lVisType, const VISINFO *pVI, long lIdent) 
{
	return EC_OKAY;
}

///////////////////////////////////////////////////////////////////////////////
// 
ErrCode CArcViewExport::ExportMerkmalDescription(long lMCode, char *pbuf, short iTyp, short iLen) 
{
	if (S_OK != m_DataSource.GetAttribute (lMCode)) {
	// erstes Attribut für diese Objektklasse
	HRESULT hr = m_DataSource.AddAttribute (lMCode, pbuf, iTyp, iLen);

		if (FAILED(hr)) {
			SetLastError(hr);
			return EC_FAIL;
		}
	}
	return EC_OKAY;
}

///////////////////////////////////////////////////////////////////////////////
// Ausgeben einer Kommentarzeile 
ErrCode CArcViewExport::ExportComment (OFSTRUCT &of, const char *pcComment) 
{
	return EC_OKAY;
}

///////////////////////////////////////////////////////////////////////////////
// Ausgeben der HeaderInformation 
ErrCode CArcViewExport::ExportHeader(OFSTRUCT &of, const char *pcHeader) 
{
	return EC_OKAY;
}

///////////////////////////////////////////////////////////////////////////////
// Ausgeben der BeschreibungsInformation (Properties)
ErrCode CArcViewExport::ExportDescriptionEx(OFSTRUCT &of, LPCSTR lpKeyInfo, LPCSTR lpDescString, DWORD dwStyle)
{
	return EC_OKAY;
}

///////////////////////////////////////////////////////////////////////////////
// Ausgeben der TrailerInformation 
ErrCode CArcViewExport::ExportTrailer(OFSTRUCT &of, const char *lpTrailerString)
{
	return EC_OKAY;
}

///////////////////////////////////////////////////////////////////////////////
// Ausgabe eines Geometrieobjektes mit Merkmalsinformation 
ErrCode CArcViewExport::ExportData(
	OFSTRUCT &of, GSTRUCT &GS, MFELD *pMF, RSTRUCT *, LPCTSTR pUIdent, 
	LPCTSTR lpszGUID, LPCTSTR pParentClass)
{
// über Identifikator der Objektes sicherstellen, daß ein entsprechender 
// Layer bereits existiert
CArcViewLayer *pLayer = NULL;
HRESULT hr = S_OK;
OBJECTTYPE rgType = ObjType2OBJECTTYPE(GS.Typ);

	if (S_OK != GetLayer (GS.Id, rgType, &pLayer)) {
	// KurzText festellen
	os_string strBuffer;

		if (FAILED(GetShortDesc (GS.Id, strBuffer))) {
			hr = GetOKS (GS.Id, strBuffer);
			if (FAILED(hr)) {
				SetLastError (hr);
				return EC_FAIL;
			}
		}

	// neuen Layer erzeugen
		hr = CreateLayer (GS.Id, strBuffer.c_str(), rgType, &pLayer);

	// sollte dieser Layer (vom Namen her) bereits existieren, dann diesen 
	// wiederverwenden
		if (hr == ARCVIEW_W_LAYERNAME_NOT_UNIQUE) 
			hr = GetLayer(strBuffer.c_str(), rgType, &pLayer);
		
		if (FAILED(hr)) {
			SetLastError(hr);
			return EC_FAIL;
		}
	}

// Attribute für diesen Layer wiederfinden
CArcViewLayerAttributes *pMap = NULL;

	if (S_OK != m_DataSource.GetAttributes(GS.Id, &pMap)) 
		m_DataSource.GetAttributes(NULL, &pMap);

// dieses Objekt exportieren
	hr = pLayer -> ExportData (&GS, pMF, pUIdent, pMap);
	if (FAILED(hr)) {
		SetLastError(hr);
		return EC_FAIL;
	}
	return EC_OKAY;
}

///////////////////////////////////////////////////////////////////////////////
// Ende des DatenExports 
ErrCode CArcViewExport::ExportEnd(OFSTRUCT &of)
{ 
	CloseAll();
	ResetRootDir();
	return EC_OKAY;
}

///////////////////////////////////////////////////////////////////////////////
// Abbrechen des Datenexportes 
ErrCode CArcViewExport::ExportBreak(OFSTRUCT &of)
{ 
// Datei löschen, damit keine Reste bleiben
	DeleteAllFiles();
	ResetRootDir();
	
// Objekt freigeben
	return EC_OKAY; 
} 

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
HRESULT CArcViewExport::GetShortDesc(long lIdent, os_string &rStrShort)
{
ErrInstall EI (WC_NOIDENT);
PBDDATA pbdData;
char cbBuffer[64];

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = cbBuffer;	// gesucht
	pbdData.pbdLText = NULL;
	pbdData.pbdKTextLen = sizeof(cbBuffer)-1;
	pbdData.pbdLTextLen = 0;

// PBD-Info holen
	pbdData.pbdKText[0] = '\0';
	DEX_GetPBDData (pbdData);
	if (pbdData.pbdKTextLen > 0) {
		rStrShort = pbdData.pbdKText;
		return S_OK;
	}
	return E_FAIL;
}

HRESULT CArcViewExport::GetOKS(long lIdent, os_string &rStrOKS)
{
// Variablen initialisieren
char cbBuffer[64];

	if (SUCCEEDED(ClassFromIdentX (lIdent, cbBuffer, sizeof(cbBuffer)))) {
		rStrOKS = cbBuffer;
		return S_OK;
	}
	return E_FAIL;
}
