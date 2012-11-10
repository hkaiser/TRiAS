// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 10/18/1998 10:52:13 PM
//
// @doc
// @module BlobSupport.h | Objekt in BLOB speichern bzw. aus BLOB erzeugen

#if !defined(_BLOBSUPPORT_H__7CD55717_6427_11D2_9EDE_006008447800__INCLUDED_)
#define _BLOBSUPPORT_H__7CD55717_6427_11D2_9EDE_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Com/CStructHelper.h>
#include <Com/MemoryHelper.h>

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

	COM_TRY {
	// Objekt in einen Speicherblock speichern
	HGLOBAL hGbl = NULL;
	WStream Strm;

		THROW_FAILED_HRESULT(CreateStreamOnHGlobal(NULL, TRUE, Strm.ppi()));
		THROW_FAILED_HRESULT(OleSaveToStream (pObj, Strm));
		THROW_FAILED_HRESULT(GetHGlobalFromStream (Strm, &hGbl));

	// Speicher für den neuen BLOB anfordern
	CGlobalMem::Lock<BYTE> MemLock(hGbl);
	CMallocMem<BYTE> Mem (MemLock.GetSize());			// throws E_OUTOFMEMORY

	// BLOB im Speicher zusammenbauen
		CopyMemory (Mem, MemLock, MemLock.GetSize());

		pBlob -> cbSize = MemLock.GetSize();
		pBlob -> pBlobData = Mem.Detach();

	} COM_CATCH;
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

HRESULT hr = S_OK;

	COM_TRY {
	// Globalen Speicher erzeugen
	CGlobalMem Mem (pBlob -> cbSize);	// throws E_OUTOFMEMORY

	// ObjektDaten aus BLOB herauskopieren
		{
		CGlobalMem::Lock<BYTE> MemLock(Mem);

			::CopyMemory (MemLock, pBlob -> pBlobData, MemLock.GetSize());
		}

	// Objekt aus dem gegebenen Speicherblock auslesen
	WStream Strm;

		hr = CreateStreamOnHGlobal (Mem.Handle(), FALSE, Strm.ppi());
		if (SUCCEEDED(hr))
			hr = OleLoadFromStream (Strm, riid, ppvObj);

	} COM_CATCH;
	return hr;
}

#endif // !defined(_BLOBSUPPORT_H__7CD55717_6427_11D2_9EDE_006008447800__INCLUDED_)
