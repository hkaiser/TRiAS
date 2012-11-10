// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 01.04.2000 18:00:39 
//
// @doc
// @module CompressedStream.h | Declaration of the <c CCompressedStream> class

#if !defined(_COMPRESSEDSTREAM_H__BA1E2597_8284_46D2_98B4_F112DA4F4B0A__INCLUDED_)
#define _COMPRESSEDSTREAM_H__BA1E2597_8284_46D2_98B4_F112DA4F4B0A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(_USE_COMPRESSED_STREAM)
#include <Atl/DebugObjectCount.h>		// globale Objektzähler für einzeöne Objekttypen
#include <Atl/CieThis.h>

#include "obj32/TRiAS321.h"				// main symbols

#include "FreeMapForCompressedStream.h"
#include "MapOffsetsForCompressedStream.h"

///////////////////////////////////////////////////////////////////////////////
// {102524FF-BA73-4897-A7A1-E9A8ED02A01D}
extern "C" const IID __declspec(selectany) CLSID_CompressedStream = 
	{0x102524ff,0xba73,0x4897,{0xa7,0xa1,0xe9,0xa8,0xed,0x02,0xa0,0x1d}};

/////////////////////////////////////////////////////////////////////////////
// CCompressedStream
class ATL_NO_VTABLE CCompressedStream : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCompressedStream, &CLSID_CompressedStream>,
	public IStream
{
public:
	CCompressedStream() :
		m_ulSeekPos(0), m_fIsInitialized(false)
	{
	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CCompressedStream)

	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE(CCompressedStream)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CCompressedStream)
		COM_INTERFACE_ENTRY(IStream)
		COM_INTERFACE_ENTRY(ISequentialStream)
		COM_INTERFACE_ENTRY_THIS()
	END_COM_MAP()

// IStream
public:
	STDMETHOD(Seek)(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition);
	STDMETHOD(SetSize)(ULARGE_INTEGER libNewSize);
	STDMETHOD(CopyTo)(IStream *pstm, ULARGE_INTEGER cb, ULARGE_INTEGER *pcbRead, ULARGE_INTEGER *pcbWritten);
	STDMETHOD(Commit)(DWORD grfCommitFlags);
	STDMETHOD(Revert)(void);
	STDMETHOD(LockRegion)(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
	STDMETHOD(UnlockRegion)(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
	STDMETHOD(Stat)(STATSTG *pstatstg, DWORD grfStatFlag);
	STDMETHOD(Clone)(IStream **ppstm);

// ISequentialStream
	STDMETHOD(Read)(void *pv, ULONG cb, ULONG *pcbRead);
	STDMETHOD(Write)(const void *pv, ULONG cb, ULONG *pcbWritten);

// Initialisierung
	HRESULT Initialize (IStream *pIStrm, ULONG uiBlockSize);
	HRESULT Initialize (const CCompressedStream &rhs);

// sonstige Zugriffsroutinen
	const CMapOffsets & GetMapOffsets() const { return m_MapOffsets; }
	const CFreeMapForCompressedStream & GetFreeMap() const { return m_FreeMap; }
	ULONG GetSeekPos() const { return m_ulSeekPos; }

	HRESULT GetTargetStream(IStream **ppIStm)
	{
		if (NULL == ppIStm)
			return E_POINTER;
		if (!m_Strm.IsValid())
			return E_UNEXPECTED;
		return (*ppIStm = m_Strm) -> AddRef(), S_OK;
	}

protected:
	LONG GetEndOfData() { return 0L; }
	LONG GetCompressedEndOfData() { return m_FreeMap.GetEndOfStream(); }

	HRESULT ReadLocal (void *pv, ULONG cb, bool fReadForPartialWrite = false);

	HRESULT InitNew (ULONG ulBlockSize);
	HRESULT Load (IStream *pIStream);
	HRESULT Save (IStream *pIStream);

private:
	CMapOffsets m_MapOffsets;		// Offset/Size Paare dieses Streams
	CFreeMapForCompressedStream m_FreeMap;

	__Interface<IStream> m_Strm;	// darunterliegender Stream
	ULONG m_ulSeekPos;				// derzeitige logische Position
	bool m_fIsInitialized;

#if defined(_DEBUG)
public:
	os_string m_strStrmName;
#endif // Defined(_DEBUG)
};
#endif // defined(_USE_COMPRESSED_STREAM)

///////////////////////////////////////////////////////////////////////////////
// API's
#if defined(_DEBUG)
HRESULT CreateCompressedStream (IStream *pIStrmIn, ULONG ulBlockSize, IStream **ppIStrmOut, LPCSTR pcStrmName = NULL);
#else
HRESULT CreateCompressedStream (IStream *pIStrmIn, ULONG ulBlockSize, IStream **ppIStrmOut);
#endif // defined(_DEBUG)

#endif // !defined(_COMPRESSEDSTREAM_H__BA1E2597_8284_46D2_98B4_F112DA4F4B0A__INCLUDED_)
