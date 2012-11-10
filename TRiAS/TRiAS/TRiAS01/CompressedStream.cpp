// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 01.04.2000 18:00:04
//
// @doc
// @module CompressedStream.cpp | Implementation of the <c CCompressedStream> class

#include "trias01p.hxx"

#if defined(_USE_COMPRESSED_STREAM)

#include <d_lib/d_lib.h>		// debug/tracing support
#include <ZLib/ZLibHelper.h>	// compression support

#include "CompressedStream.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(Stream);

///////////////////////////////////////////////////////////////////////////////
// define this for debugging stream buffers 
//#define _DEBUG_FILL_BUFFERS

/////////////////////////////////////////////////////////////////////////////
// CCompressedStream
STDMETHODIMP CCompressedStream::Seek (LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition)
{
	if (NULL != plibNewPosition && IsBadWritePtr ((void *)plibNewPosition, sizeof(ULARGE_INTEGER)))
		return STG_E_INVALIDPOINTER;

	switch (dwOrigin) {
	case STREAM_SEEK_SET:
	// Interpret as unsigned
		m_ulSeekPos = dlibMove.LowPart;
		break;

	case STREAM_SEEK_CUR:
		m_ulSeekPos += (LONG)dlibMove.LowPart;
		break;

	case STREAM_SEEK_END:
		m_ulSeekPos = GetEndOfData() + (LONG)dlibMove.LowPart;
		break;

	default:
		return STG_E_INVALIDFUNCTION;
	}

// Can't seek past the beginning, but the seek position can be past the end
	if (m_ulSeekPos < 0)
		m_ulSeekPos = 0;
	if (plibNewPosition)
		ULISet32(*plibNewPosition, m_ulSeekPos);
	return S_OK;
}

STDMETHODIMP CCompressedStream::SetSize (ULARGE_INTEGER libNewSize)
{
	return S_OK;
}

STDMETHODIMP CCompressedStream::CopyTo (IStream *pstm, ULARGE_INTEGER cb, ULARGE_INTEGER *pcbRead, ULARGE_INTEGER *pcbWritten)
{
WStream StrmOut (pstm);
CComObject<CCompressedStream> *pDest = NULL;

	if (SUCCEEDED(QueryImplementation(pstm, &pDest))) {
	// der ZielStream ist auch ein compressed stream
		RETURN_FAILED_HRESULT(pDest -> GetTargetStream(StrmOut.ppi()));
	}
	else {
	// neuen CompressedStream erzeugen
		RETURN_FAILED_HRESULT(CComObject<CCompressedStream>::CreateInstance (&pDest));
		StrmOut = pstm;
#if defined(_DEBUG)
		pDest -> m_strStrmName = m_strStrmName;
#endif // defined(_DEBUG)
	}
	_ASSERTE(NULL != pDest);
	_ASSERTE(0 == m_ulSeekPos);		// muß (logisch) am Anfang stehen

// unseren Stream an den Anfang setzen
LARGE_INTEGER uli;

	uli.QuadPart = 0;
	RETURN_FAILED_HRESULT(m_Strm -> Seek (uli, STREAM_SEEK_SET, NULL));

// jetzt alles umkopieren
#if defined(_DEBUG)
ULARGE_INTEGER uliRead;
ULARGE_INTEGER uliWritten;

	uliRead.QuadPart = 0;
	uliWritten.QuadPart = 0;
	RETURN_FAILED_HRESULT(m_Strm -> CopyTo (StrmOut, cb, &uliRead, &uliWritten));
	if (NULL != pcbRead)
		*pcbRead = uliRead;
	if (NULL != pcbWritten)
		*pcbWritten = uliWritten;
#else
	RETURN_FAILED_HRESULT(m_Strm -> CopyTo (StrmOut, cb, pcbRead, pcbWritten));
#endif // defined(_DEBUG)

// ZielCompressedStream initialisieren
	RETURN_FAILED_HRESULT(pDest -> Initialize (StrmOut, m_MapOffsets.GetBlockSize()));
	return S_OK;
}

STDMETHODIMP CCompressedStream::Commit (DWORD grfCommitFlags)
{
	if (!m_Strm.IsValid())
		return E_UNEXPECTED;

// Daten ans Ende des Streams wegschreiben
LARGE_INTEGER li;

	li.QuadPart = GetCompressedEndOfData();
	RETURN_FAILED_HRESULT(m_Strm -> Seek (li, STREAM_SEEK_SET, NULL));
	RETURN_FAILED_HRESULT(Save (m_Strm));

// das letzte LONG ist der Offset auf unsere Daten
	RETURN_FAILED_HRESULT(m_Strm -> Write (&li.LowPart, sizeof(LONG), NULL));

// Stream an dieser Stelle kappen
LARGE_INTEGER end;
ULARGE_INTEGER uli;

	end.QuadPart = 0;
	RETURN_FAILED_HRESULT(m_Strm -> Seek (end, STREAM_SEEK_CUR, &uli));
	RETURN_FAILED_HRESULT(m_Strm -> SetSize(uli));

	RETURN_FAILED_HRESULT(m_Strm -> Commit (grfCommitFlags));
	return S_OK;
}

STDMETHODIMP CCompressedStream::Revert (void)
{
	if (!m_Strm.IsValid())
		return E_UNEXPECTED;
	return m_Strm -> Revert();
}

STDMETHODIMP CCompressedStream::LockRegion (ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
{
	return E_NOTIMPL;
}

STDMETHODIMP CCompressedStream::UnlockRegion (ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
{
	return E_NOTIMPL;
}

STDMETHODIMP CCompressedStream::Stat (STATSTG *pstatstg, DWORD grfStatFlag)
{
	if (NULL == pstatstg || IsBadWritePtr (pstatstg, sizeof(STATSTG)))
		return STG_E_INVALIDPOINTER;

	ZeroMemory(pstatstg, sizeof(STATSTG));
	pstatstg -> type = STGTY_LOCKBYTES;
	ULISet32(pstatstg -> cbSize, GetEndOfData());
	return S_OK;
}

STDMETHODIMP CCompressedStream::Clone (IStream **ppstm)
{
	if (NULL == ppstm)
		return E_POINTER;
	else
		*ppstm = NULL;

CComObject<CCompressedStream> *pStream;
HRESULT hr = CComObject<CCompressedStream>::CreateInstance (&pStream);

	if (FAILED(hr)) return hr;

__Interface<IStream> strm (pStream);	// festhalten (pending AddRef)
__Interface<IStream> ClonedStrm;

	RETURN_FAILED_HRESULT(m_Strm -> Clone (ClonedStrm.ppi()));
	if (SUCCEEDED(pStream -> Initialize (ClonedStrm, m_MapOffsets.GetBlockSize()))) {
	// Kopie erfolgreich initialisiert
		*ppstm = strm.detach();

	LARGE_INTEGER li;
	
		LISet32 (li, m_ulSeekPos);
		return pStream -> Seek (li, STREAM_SEEK_SET, NULL);
	}
	return E_OUTOFMEMORY;
}

// ISequentialStream
HRESULT CCompressedStream::ReadLocal (void *pv, ULONG cb, bool fReadForPartialWrite)
{
	if (NULL == pv || IsBadWritePtr (pv, cb))
		return STG_E_INVALIDPOINTER;

BYTE *pBlock = reinterpret_cast<BYTE *>(pv);
BYTE *pNewBlock = NULL;
HRESULT hr = S_OK;

	COM_TRY {
	// evtl. muß nicht gesamter Block gelesen werden
		if (cb < m_MapOffsets.GetBlockSize()) {
		// die gesamten zu lesenden Daten müssen in einem Block liegen (yet)
			_ASSERTE(m_MapOffsets.AlignToBlockOffset(m_ulSeekPos) == m_MapOffsets.AlignToBlockOffset(m_ulSeekPos+cb));

			pNewBlock = new BYTE[m_MapOffsets.GetBlockSize()];
			pBlock = pNewBlock;
		} else {
		// zu lesender Block muß gespeichertem Block entsprechen
			_ASSERTE(fReadForPartialWrite || m_ulSeekPos == m_MapOffsets.AlignToBlockOffset(m_ulSeekPos));
		}

	// gesamten betreffenden Block lesen
	CMapOffsets::value_type p = m_MapOffsets.GetOffsetAndSize (m_ulSeekPos);

		if (p.IsValid()) {
		LARGE_INTEGER li;
		ULONG ulSize = 0;

			li.QuadPart = p.first;
			THROW_FAILED_HRESULT(m_Strm -> Seek (li, STREAM_SEEK_SET, NULL));
			THROW_FAILED_HRESULT(m_Strm -> Read (&ulSize, sizeof(ULONG), NULL));

		CGlobalMem Mem (ulSize);
		CGlobalMem::Lock<BYTE> MemLock(Mem);

			THROW_FAILED_HRESULT(m_Strm -> Read (MemLock, ulSize, NULL));

		CZLibWrapper ZLib (ulSize, MemLock);

			THROW_FAILED_HRESULT(ZLib.UnCompress(m_MapOffsets.GetBlockSize(), pBlock));

			if (cb < m_MapOffsets.GetBlockSize()) 
				memcpy (pv, &pBlock[m_ulSeekPos - m_MapOffsets.AlignToBlockOffset(m_ulSeekPos)], cb);
		} else
			hr = S_FALSE;		// EOF reached

	} COM_CATCH_OP(delete pNewBlock);

// alles ok
	delete pNewBlock;
	return hr;
}	
	
STDMETHODIMP CCompressedStream::Read (void *pv, ULONG cb, ULONG *pcbRead)
{
	if (NULL != pcbRead)
		*pcbRead = 0;		// sicherheitshalber

HRESULT hr;

	RETURN_FAILED_HRESULT(hr = ReadLocal (pv, cb));
	if (S_OK == hr) {
		m_ulSeekPos += cb;		// neue Streamposition
		if (NULL != pcbRead)
			*pcbRead = cb;
	}
	return hr;
}

STDMETHODIMP CCompressedStream::Write (const void *pv, ULONG cb, ULONG *pcbWritten)
{
	if (NULL == pv || IsBadReadPtr (pv, cb))
		return STG_E_INVALIDPOINTER;

	if (NULL != pcbWritten)
		*pcbWritten = 0;		// sicherheitshalber

BYTE *pBlock = (BYTE *)pv;
BYTE *pNewBlock = NULL;

	COM_TRY {
	// evtl. muß nicht gesamter Block geschrieben werden
		if (cb < m_MapOffsets.GetBlockSize()) {
		// die gesamten zu schreibenden Daten müssen in einem Block liegen (yet)
			_ASSERTE(m_MapOffsets.AlignToBlockOffset(m_ulSeekPos) == m_MapOffsets.AlignToBlockOffset(m_ulSeekPos+cb));

			pNewBlock = new BYTE[m_MapOffsets.GetBlockSize()];
			THROW_FAILED_HRESULT(ReadLocal (pNewBlock, m_MapOffsets.GetBlockSize(), true));

			memcpy (&pNewBlock[m_ulSeekPos - m_MapOffsets.AlignToBlockOffset(m_ulSeekPos)], pv, cb);
			pBlock = pNewBlock;
		} else {
		// zu schreibender Block muß einem Block im Stream entsprechen
			_ASSERTE(m_ulSeekPos == m_MapOffsets.AlignToBlockOffset(m_ulSeekPos));
		}

	// Daten komprimieren
	CZLibWrapper ZLib (m_MapOffsets.GetBlockSize(), pBlock);
	CGlobalMem ZLibMem;
	ULONG ulSize = 0;

		RETURN_FAILED_HRESULT(ZLib.Compress (&ulSize, &ZLibMem));
		_ASSERTE(ulSize <= CGlobalMem::Lock<BYTE>(ZLibMem).GetSize());

	// Daten wirklich wegschreiben
	CMapOffsets::value_type p = m_MapOffsets.GetOffsetAndSize (m_ulSeekPos);
	LARGE_INTEGER li;

		if (p.second >= ulSize+sizeof(ULONG)) {	
		// es ist noch genügend Platz da, einfach wieder dorthin schreiben
			li.QuadPart = p.first;
			THROW_FAILED_HRESULT(m_Strm -> Seek (li, STREAM_SEEK_SET, NULL));
			THROW_FAILED_HRESULT(m_Strm -> Write (&ulSize, sizeof(ULONG), NULL));
			THROW_FAILED_HRESULT(m_Strm -> Write (CGlobalMem::Lock<BYTE>(ZLibMem), ulSize, NULL));

#if defined(_DEBUG_FILL_BUFFERS)
		// Rest des Streams füllen
		vector<BYTE> buffer (p.second-(ulSize+sizeof(ULONG)), 0xcc);

			THROW_FAILED_HRESULT(m_Strm -> Write (buffer.begin(), buffer.size(), NULL));
#endif // defined(_DEBUG_FILL_BUFFERS)
		} 
		else {
		// der bisherige slot ist zu klein geworden oder slot existiert noch nicht, neuen slot anfordern
		CFreeMapForCompressedStream::value_type pfree;
		bool fNew = false;

			if (!m_FreeMap.Allocate (ulSize+sizeof(ULONG), pfree, fNew))
				return STG_E_MEDIUMFULL;
			_ASSERTE(pfree.second >= ulSize+sizeof(ULONG));	// angeforderter Platz muß ausreichend sein

			li.QuadPart = pfree.first;
			THROW_FAILED_HRESULT(m_Strm -> Seek (li, STREAM_SEEK_SET, NULL));
			THROW_FAILED_HRESULT(m_Strm -> Write (&ulSize, sizeof(ULONG), NULL));
			THROW_FAILED_HRESULT(m_Strm -> Write (CGlobalMem::Lock<BYTE>(ZLibMem), ulSize, NULL));

		// output diagnostics
			D_OUTF5(1,
				"TRiAS01: %s: ", m_strStrmName.c_str(),
				" reallocated existing slot for (real offset: %lx", m_ulSeekPos,
				(0 != p.second) ? ", old size: %ld)" : ", required size: %ld)", (0 != p.second) ? p.second : ulSize+sizeof(ULONG),
				fNew ? " got new (offset: %ld" : " got reused (offset: %ld" , pfree.first, ", size: %ld)", pfree.second);

#if defined(_DEBUG_FILL_BUFFERS)
		// Rest des Streams füllen
		vector<BYTE> buffer (pfree.second-(ulSize+sizeof(ULONG)), 0xcc);

			THROW_FAILED_HRESULT(m_Strm -> Write (buffer.begin(), buffer.size(), NULL));
#endif // defined(_DEBUG_FILL_BUFFERS)

		// neuen slot speichern
			m_MapOffsets.SetOffsetAndSize (m_ulSeekPos, pfree);

		// ggf. bisherigen slot freigeben
			if (0 != p.second) {
			// output diagnostics
				D_OUTF5(1,
					"TRiAS01: %s: ", m_strStrmName.c_str(),
					" freeing slot for (real offset: %lx", m_ulSeekPos, ", old size: %ld)", p.second,
					" freed (offset: %ld", p.first,	", size: %ld)", p.second);

#if defined(_DEBUG_FILL_BUFFERS)
			// freigewordenen slot im Stream füllen
			vector<BYTE> buffer (p.second, 0xdd);

				buffer[0] = 0xfd;		// erstes Byte kennzeichnen
				li.QuadPart = p.first;
				THROW_FAILED_HRESULT(m_Strm -> Seek (li, STREAM_SEEK_SET, NULL));
				THROW_FAILED_HRESULT(m_Strm -> Write (buffer.begin(), buffer.size(), NULL));
#endif // defined(_DEBUG_FILL_BUFFERS)

				m_FreeMap.Free (p);
			}
		}
	} COM_CATCH_OP(delete pNewBlock);

// alles ok
	delete pNewBlock;
	m_ulSeekPos += cb;		// neue Streamposition
	if (NULL != pcbWritten)
		*pcbWritten = cb;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Initialisierung
HRESULT CCompressedStream::Initialize (IStream *pIStrm, ULONG ulBlockSize)
{
	if (NULL == pIStrm || 0 == ulBlockSize)
		return E_INVALIDARG;

// Parameter speichern
	m_Strm = pIStrm;

// Datenstrukturen einlesen/initialisieren
LARGE_INTEGER li;
ULARGE_INTEGER uli;

	li.QuadPart = 0;
	uli.QuadPart = 0;
	RETURN_FAILED_HRESULT(m_Strm -> Seek (li, STREAM_SEEK_END, &uli));

// entweder ist der Stream noch leer (uli.Quadpart == 0), oder am Ende stehen unsere Daten
	if (0 == uli.QuadPart) {
	// neuer Stream, interne Datenstrukturen lediglich initialisieren
		RETURN_FAILED_HRESULT(InitNew(ulBlockSize));
	} else {
	// Stream ist nicht neu, einlesen unserer DatenStrukturen
	LONG lPos = 0;

		li.QuadPart = uli.QuadPart - sizeof(ULONG);
		RETURN_FAILED_HRESULT(m_Strm -> Seek (li, STREAM_SEEK_SET, NULL));
		RETURN_FAILED_HRESULT(m_Strm -> Read (&lPos, sizeof(LONG), NULL));	// das letzte LONG ist der Anfang

		_ASSERTE(0 < lPos);
		li.QuadPart = lPos;
		RETURN_FAILED_HRESULT(m_Strm -> Seek (li, STREAM_SEEK_SET, NULL));
		RETURN_FAILED_HRESULT(Load (m_Strm));
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Kopie eines anderen komprimierten Streams anlegen
HRESULT CCompressedStream::Initialize (const CCompressedStream &rhs)
{
	COM_TRY {
		m_ulSeekPos = rhs.GetSeekPos();
		m_MapOffsets = rhs.GetMapOffsets();
		m_FreeMap = rhs.GetFreeMap();
		m_fIsInitialized = true;
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Speichern/Laden/Initialisieren
HRESULT CCompressedStream::InitNew(ULONG ulBlockSize)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;

	m_ulSeekPos = 0;

	RETURN_FAILED_HRESULT(m_MapOffsets.Initialize(ulBlockSize));
	RETURN_FAILED_HRESULT(m_FreeMap.Initialize());
	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CCompressedStream::Load (IStream *pIStrm)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;

	m_ulSeekPos = 0;

	RETURN_FAILED_HRESULT(m_MapOffsets.Load (pIStrm));	// Anzahl der Offsets und Offsets selbst lesen
	RETURN_FAILED_HRESULT(m_FreeMap.Load (pIStrm));		// Leerstellen einlesen

	m_fIsInitialized = true;
	return S_OK;
}

HRESULT CCompressedStream::Save (IStream *pIStrm)
{
	if (!m_fIsInitialized)
		return E_UNEXPECTED;

	D_OUTF(1, "TRiAS01: MapOffsets::Save: %s", m_strStrmName.c_str());
	RETURN_FAILED_HRESULT(m_MapOffsets.Save (pIStrm));	// Offsets wegschreiben

	D_OUTF(1, "TRiAS01: FreeMap::Save: %s", m_strStrmName.c_str());
	RETURN_FAILED_HRESULT(m_FreeMap.Save (pIStrm));		// Leerstellen wegschreiben
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// API's
#if defined(_DEBUG)
HRESULT CreateCompressedStream (IStream *pIStrmIn, ULONG ulBlockSize, IStream **ppIStrmOut, LPCSTR pcStrmName)
#else
HRESULT CreateCompressedStream (IStream *pIStrmIn, ULONG ulBlockSize, IStream **ppIStrmOut)
#endif // defined(_DEBUG)
{
	if (NULL == ppIStrmOut)
		return E_POINTER;
	else
		*ppIStrmOut = NULL;

CComObject<CCompressedStream> *pStream = NULL;
HRESULT hr = CComObject<CCompressedStream>::CreateInstance (&pStream);

	if (SUCCEEDED(hr)) {
		pStream -> Initialize(pIStrmIn, ulBlockSize);
		(*ppIStrmOut = static_cast<IStream *>(pStream)) -> AddRef();

#if defined(_DEBUG)
		pStream -> m_strStrmName = (NULL != pcStrmName) ? pcStrmName : "";
#endif // defined(_DEBUG)
	}
	return hr;
}
#else // defined(_USE_COMPRESSED_STREAM)
#if defined(_DEBUG)
HRESULT CreateCompressedStream (IStream *pIStrmIn, ULONG ulBlockSize, IStream **ppIStrmOut, LPCSTR pcStrmName)
#else
HRESULT CreateCompressedStream (IStream *pIStrmIn, ULONG ulBlockSize, IStream **ppIStrmOut)
#endif // defined(_DEBUG)
{
	return E_NOTIMPL;
}
#endif // defined(_USE_COMPRESSED_STREAM)
