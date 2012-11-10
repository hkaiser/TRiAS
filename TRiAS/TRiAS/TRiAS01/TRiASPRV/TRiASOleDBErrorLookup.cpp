// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 31.05.2001 20:27:35 
//
// @doc
// @module TRiASOleDBErrorLookup.cpp | Definition of the <c CTRiASOleDBErrorLookup> class

#include "StdAfx.h"

#include "TRiASOleDBErrorLookup.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASOleDBErrorLookup

// Implementation of GetErrorDescription
STDMETHODIMP CTRiASOleDBErrorLookup::GetErrorDescription(
	HRESULT hrError, DWORD dwLookupID, DISPPARAMS *pdispparams, LCID lcid, 
	BSTR *pbstrSource, BSTR *pbstrDescription)
{
	if (NULL == pbstrSource)
		return E_POINTER;
	*pbstrSource = NULL;

	if (NULL == pbstrDescription)
		return E_POINTER;
	*pbstrDescription = NULL;

	if (!s_mapDynErrors.GetEntry (dwLookupID, pbstrDescription)) {
	char *pMsgBuf = NULL;	// hold text of the error message that we build
	BOOL bSuccess = FormatMessage (
				FORMAT_MESSAGE_FROM_HMODULE |		// get the message from the DLL
				FORMAT_MESSAGE_ALLOCATE_BUFFER |	// allocate the msg buffer for us 
				FORMAT_MESSAGE_ARGUMENT_ARRAY |		// lpArgs is an array of 32-bit values
				64,									// line length for the messages
				_Module.GetResourceInstance(),		// the messagetable DLL handle
				dwLookupID,							// message ID
				LANG_USER_DEFAULT,					// language ID as defined in .mc file
				(LPTSTR) &pMsgBuf,					// address of pointer to buffer for message
				MAX_MSG_LENGTH,						// maximum size of the message buffer
				NULL								// lpArgs array of insert strings for the message
			);

		if (!bSuccess) {
			bSuccess = FormatMessage (
					FORMAT_MESSAGE_FROM_HMODULE |
					FORMAT_MESSAGE_FROM_SYSTEM |		// get the message from the system
					FORMAT_MESSAGE_ALLOCATE_BUFFER |	// allocate the msg buffer for us 
					FORMAT_MESSAGE_ARGUMENT_ARRAY |		// lpArgs is an array of 32-bit values
					64,									// line length for the messages
					_Module.GetResourceInstance(),		// the messagetable DLL handle
					FACILITY_WIN32 == HRESULT_FACILITY(hrError) ? 
						HRESULT_CODE(hrError) :
						hrError,						// message ID
					LANG_USER_DEFAULT,					// language ID as defined in .mc file
					(LPTSTR) &pMsgBuf,					// address of pointer to buffer for message
					MAX_MSG_LENGTH,						// maximum size of the message buffer
					NULL								// lpArgs array of insert strings for the message
				);
		}
		_ASSERTE(!bSuccess || NULL != pMsgBuf);

		*pbstrDescription = CComBSTR(bSuccess ? pMsgBuf : "<Unknown error>").Detach();
		if (NULL != pMsgBuf)
			LocalFree((HLOCAL)pMsgBuf);
	}

	*pbstrSource = CComBSTR(L"[TRiASOleDB]").Detach();
	return S_OK;
}

// Implementation of GetHelpInfo
STDMETHODIMP CTRiASOleDBErrorLookup::GetHelpInfo(
	HRESULT hrError, DWORD dwLookupID, LCID lcid, BSTR *pbstrHelpFile, DWORD *pdwHelpContext)
{
	if (NULL == pbstrHelpFile || NULL == pdwHelpContext) {
		if (NULL != pbstrHelpFile)
			*pbstrHelpFile = NULL;
		if (NULL != pdwHelpContext)
			*pdwHelpContext = 0L;
		return E_INVALIDARG;
	}

CComBSTR bstrHelpFile("TRiASOleDB.hlp");

	*pbstrHelpFile = bstrHelpFile.Detach();
	if (NULL == *pbstrHelpFile)
		return E_OUTOFMEMORY;
	*pdwHelpContext = dwLookupID;
	return S_OK;
}

// Implementation of ReleaseErrors
STDMETHODIMP CTRiASOleDBErrorLookup::ReleaseErrors(const DWORD dwDynamicErrorID)
{
	s_mapDynErrors.RemoveId (dwDynamicErrorID);
	return S_OK;
}

