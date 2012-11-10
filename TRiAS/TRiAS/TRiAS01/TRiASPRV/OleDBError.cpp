// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 31.05.2001 22:34:52 
//
// @doc
// @module OleDBError.cpp | Definition of the <c COleDBError> class

#include "StdAfx.h"
#include "OleDbError.h"

///////////////////////////////////////////////////////////////////////////////
// globale Liste aller derzeit aktiven dynamischen Fehler
CDynamicErrors<CComGlobalsThreadModel> s_mapDynErrors;

///////////////////////////////////////////////////////////////////////////////
// globale Fehlerbehandlungsroutine
HRESULT WINAPI OleDBError (
	HRESULT hrErr, REFCLSID rClsId, REFIID rIId, DWORD dwMinor, DWORD dwDynamicErrorID,
	DISPID dwDispId, DISPPARAMS *pDispParams)
{
// An error or warning occurred. Get the current error object. 
// If one does not exist, create a new one.
CComPtr<IErrorInfo> ErrorInfo;

	RETURN_FAILED_HRESULT(GetErrorInfo(0, &ErrorInfo));
	if (ErrorInfo == NULL) 
		RETURN_FAILED_HRESULT(ErrorInfo.CoCreateInstance(CLSID_EXTENDEDERRORINFO));

// Get an IErrorRecords interface pointer on the error object.
CComQIPtr<IErrorRecords> ErrorRecords (ErrorInfo);

	if (ErrorRecords == NULL)
		return E_NOINTERFACE;
	
// Fill in the ERRORINFO structure and add the error record.
	_ASSERTE(0 != dwMinor || 0 != dwDynamicErrorID);

ERRORINFO ErrorInfoData;

	ErrorInfoData.hrError = hrErr;
	ErrorInfoData.dwMinor = dwMinor;
	ErrorInfoData.clsid = rClsId;
	ErrorInfoData.iid = rIId;
	ErrorInfoData.dispid = dwDispId;
	RETURN_FAILED_HRESULT(ErrorRecords->AddErrorRecord(&ErrorInfoData, (0 != dwMinor) ? dwMinor : dwDynamicErrorID, pDispParams, NULL, dwDynamicErrorID));
	
// Call SetErrorInfo to pass the error object to the Automation DLL.
	RETURN_FAILED_HRESULT(SetErrorInfo(0, ErrorInfo));

	return hrErr;
}
