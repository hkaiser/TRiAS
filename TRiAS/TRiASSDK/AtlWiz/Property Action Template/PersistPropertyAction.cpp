// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.01.2000 22:31:21
//
// @doc
// @module PersistPropertyAction.cpp | Funktionen für das Schreiben/Lesen 
// einer ganzen PropertySequence im Projekt

#include <Com/PropertyActionBase.h>

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(Storage);
DefineSmartInterface(Stream);
DefineSmartInterface(PersistStream);
DefineSmartInterface(PropertyActionSequence);

namespace PropActBase {
// benötigte Stringkonstante
	static LPCOLESTR g_cbPropertySequences = L"PropertySequences";		// Names des SubStreams im Projekt

// lokale Helperfunktionen
	HRESULT MakeStreamName (BSTR bstrDescription, CComBSTR &bstrStreamName) 
	{
		USES_CONVERSION;

	TCHAR _buf[32];
	LPCTSTR	lpszStreamname = W2A(bstrDescription);

		for (int i = 0; *lpszStreamname && i != _countof(_buf) - 1; ++i, ++lpszStreamname) 
			_buf[i] = isalnum(*lpszStreamname) ? *lpszStreamname : _T('_');

		_buf[i] = _T('\0');
		bstrStreamName = _buf;
		return S_OK;
	}

	HRESULT OpenStorage (LPCOLESTR lpoleStoragename, DWORD dwMode, IStorage *pParent, IStorage **ppIStorage) 
	{
		dwMode |= STGM_SHARE_EXCLUSIVE | STGM_TRANSACTED;
		return pParent -> OpenStorage (lpoleStoragename, NULL, dwMode, NULL, 0, ppIStorage);
	}

	HRESULT OpenPropSeqStorage (DWORD dwMode, IStorage **ppStorage) 
	{
	WStorage StgRoot;
	WStorage Stg;

		if (!DEX_GetProjectStorage(*StgRoot.ppv()))
			return E_UNEXPECTED;

	HRESULT hr = OpenStorage (g_cbPropertySequences, dwMode, StgRoot, Stg.ppi());

		if (FAILED(hr)) {
			if (!(STGM_WRITE & dwMode) && !(STGM_READWRITE & dwMode))
				return hr;

			RETURN_FAILED_HRESULT(StgRoot -> CreateStorage (g_cbPropertySequences, STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_TRANSACTED | STGM_CREATE, 0L, 0L, Stg.ppi()));
			RETURN_FAILED_HRESULT(Stg -> SetClass (CLSID_PropertyActionSequence));
		}
		*ppStorage = Stg.detach();
		return S_OK;
	}

// Laden einer bestimmten PropertySequence
	HRESULT LoadPropertySequence (BSTR bstrName, IPropertyActionSequence **ppIPropertyActionSequence)
	{
		TEST_OUT_PARAM(ppIPropertyActionSequence);
		COM_TRY {
		WStorage Stg;

			if (FAILED(OpenPropSeqStorage (STGM_READ, Stg.ppi())))
				return E_FAIL;

		CComBSTR bstrStreamName;
		WStream	Strm;

			THROW_FAILED_HRESULT(MakeStreamName(bstrName, bstrStreamName));
			if (FAILED(Stg -> OpenStream (bstrStreamName, NULL, STGM_READ | STGM_SHARE_EXCLUSIVE, 0, Strm.ppi())))
				return E_FAIL;

		WPropertyActionSequence	Seq;

			THROW_FAILED_HRESULT(::OleLoadFromStream (Strm, Seq.GetIID(), Seq.ppv()));
			*ppIPropertyActionSequence = Seq.detach();

		} COM_CATCH;
		return S_OK;
	}

// Schreiben einer bestimmten PropertySequence
	HRESULT SavePropertySequence (BSTR bstrName, IPropertyActionSequence *pISeq)
	{
		COM_TRY {
		WStorage Stg;

			if (FAILED(OpenPropSeqStorage (STGM_READWRITE, Stg.ppi())))
				return E_FAIL;

		CComBSTR bstrStreamName;
		WStream Strm;

			THROW_FAILED_HRESULT(MakeStreamName (bstrName, bstrStreamName));
			if (FAILED(Stg -> OpenStream (bstrStreamName, NULL, STGM_CREATE | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, Strm.ppi()))) 
			{
				THROW_FAILED_HRESULT(Stg -> CreateStream (bstrStreamName, STGM_CREATE | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, Strm.ppi()));
			}
		
			THROW_FAILED_HRESULT(::OleSaveToStream (WPersistStream(pISeq), Strm));
			THROW_FAILED_HRESULT(Strm -> Commit (STGC_DEFAULT));
			THROW_FAILED_HRESULT(Stg -> Commit (STGC_DEFAULT));
		} COM_CATCH;
		return S_OK;
	}
}
