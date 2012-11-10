// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 09.07.99 21:24:11 
//
// @doc
// @module ZlibHelper.h | Declaration of the <c CZlibWrapper> class

#if !defined(_ZLIBHELPER_H__DA70E7B0_3633_11D3_94FA_0080C786297B__INCLUDED_)
#define _ZLIBHELPER_H__DA70E7B0_3633_11D3_94FA_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ZLib/ZLib.h>
#if defined(_DEBUG)
#pragma comment(lib, "zlibd.lib")
#else
#pragma comment(lib, "zlibr.lib")
#endif // _DEBUG

#include <Com/MemoryHelper.h>

// Wrapperklasse für ZLib-Routinen 
class CZLibWrapper 
{
public:
	CZLibWrapper (ULONG ulSize, BYTE *pbData) :
		m_pInData(pbData), m_ulInSize(ulSize)
	{
		_ASSERTE(NULL != pbData);
	}

// komprimieren, liefert HGLOBAL der komprimierten Daten ab
	HRESULT Compress (ULONG *pulSize, HGLOBAL *phGbl, int iLevel = Z_DEFAULT_COMPRESSION)
	{
		_ASSERTE(NULL != phGbl && NULL != pulSize);
		COM_TRY {
		ULONG ulOutSize = m_ulInSize + m_ulInSize/100 + 112;
		CGlobalMem Mem (ulOutSize);

			{
			CGlobalMem::Lock<BYTE> MemLock(Mem);

				if (Z_OK != compress2 (MemLock, &ulOutSize, m_pInData, m_ulInSize, iLevel))
					return E_FAIL;
			}
			*phGbl = Mem.Detach();
			*pulSize = ulOutSize;

		} COM_CATCH;

		return S_OK;
	}

// dekomprimieren, liefert HGLOBAL der dekomprimierten Daten ab
	HRESULT UnCompress (ULONG ulOutSize, HGLOBAL *phGbl)
	{
		_ASSERTE(NULL != phGbl);

		COM_TRY {
		CGlobalMem Mem (ulOutSize);

			{
			CGlobalMem::Lock<BYTE> MemLock(Mem);

				if (Z_OK != uncompress (MemLock, &ulOutSize, m_pInData, m_ulInSize))
					return E_FAIL;
			}
			*phGbl = Mem.Detach();

		} COM_CATCH;
		return S_OK;
	}

// in vorgegebenem Datenbereich dekomprimieren
	HRESULT UnCompress (ULONG ulOutSize, BYTE *pBuffer)
	{
		_ASSERTE(NULL != pBuffer);
		if (Z_OK != uncompress (pBuffer, &ulOutSize, m_pInData, m_ulInSize))
			return E_FAIL;
		return S_OK;
	}

private:
	BYTE *m_pInData;
	ULONG m_ulInSize;
};

#endif // !defined(_ZLIBHELPER_H__DA70E7B0_3633_11D3_94FA_0080C786297B__INCLUDED_)
