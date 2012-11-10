// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 02/23/1999 10:52:13 PM
//
// @doc
// @module InMemoryBlobSupport.h | Objekt in BLOB speichern bzw. aus BLOB erzeugen
// dabei InMemoryStream verwenden

#if !defined(_INMEMORYBLOBSUPPORT_H__7CD55717_6427_11D2_9EDE_006008447800__INCLUDED_)
#define _INMEMORYBLOBSUPPORT_H__7CD55717_6427_11D2_9EDE_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Com/CStructHelper.h>
#include <Com/MemoryHelper.h>
#include <Com/InMemoryStream.h>

///////////////////////////////////////////////////////////////////////////////
// Helper
inline void Clear (BLOB *pData) { TIDY(pData, pBlobData); }
typedef CStruct<BLOB> CBlob;

///////////////////////////////////////////////////////////////////////////////
// benötigte SmartIF's
DefineSmartInterface(Stream);

///////////////////////////////////////////////////////////////////////////////
// Objekt in einen durch den Standard-Allocator (CoTaskMemAlloc) angelegten 
// Speicherbereich als BLOB (Size+Daten) ablegen
inline
HRESULT OleSafeToBlob (IPersistStream *pObj, BLOB *pBlob)
{
	if (NULL == pBlob)
		return E_POINTER;

// Objekt in einen Speicherblock speichern
CMallocMem<BYTE> Mem;
WStream Strm;

	RETURN_FAILED_HRESULT(CreateStreamOnTaskMem (NULL, TRUE, Strm.ppi()));
	RETURN_FAILED_HRESULT(OleSaveToStream (pObj, Strm));
	RETURN_FAILED_HRESULT(GetTaskMemFromStream (Strm, TRUE, reinterpret_cast<void **>(&Mem)));

// BLOB im Speicher zusammenbauen
	pBlob -> cbSize = Mem.GetSize();
	pBlob -> pBlobData = Mem.Detach();

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Objekt aus einem durch den Standard-Allocator (CoTaskMemAlloc) angelegten 
// BLOB (Size+Daten) erzeugen und initialisieren
inline
HRESULT OleLoadFromBlob (BLOB *pBlob, REFIID riid, void **ppvObj)
{
	if (NULL == pBlob)
		return E_POINTER;

// Objekt aus dem gegebenen Speicherblock auslesen
WStream Strm;
HRESULT hr = CreateStreamOnTaskMem (pBlob -> pBlobData, FALSE, Strm.ppi());

	if (SUCCEEDED(hr))
		hr = OleLoadFromStream (Strm, riid, ppvObj);
	return hr;
}

#endif // !defined(_INMEMORYBLOBSUPPORT_H__7CD55717_6427_11D2_9EDE_006008447800__INCLUDED_)
