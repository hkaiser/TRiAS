// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 09.06.2001 16:48:33 
//
// @doc
// @module OrderByPredicates.h | Declaration of the OrderByPredicates classes

#if !defined(_ORDERBYPREDICATES_H__51379C9D_BFDA_4781_800C_595C30A1332A__INCLUDED_)
#define _ORDERBYPREDICATES_H__51379C9D_BFDA_4781_800C_595C30A1332A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <Com/Thunk.h>

///////////////////////////////////////////////////////////////////////////////
// aufsteigendes sortieren von Zeichenketten
class COrderByPredAsc :
	public binary_function<CTRiASOleDBRowT<CTRiASOleDBRowset>, 
		CTRiASOleDBRowT<CTRiASOleDBRowset>, bool>
{
public:
	COrderByPredAsc(INT_PTR hPr, ULONG ulColumn) : 
		m_hPr(hPr), m_ulColumn(ulColumn+1) 
	{
		_ASSERTE(m_ulColumn >= 2);
	}
	~COrderByPredAsc() 
	{
	}

	typedef int (__cdecl *COMPAREPROC)(const void *, const void *);
	typedef CCDeclThunkImpl<COrderByPredAsc, COMPAREPROC> CCompareHook;

	int __cdecl invcompare (void *plhs, void *prhs)
	{
	int iReturn = compare (plhs, prhs);

		if (iReturn < 0)
			return 1;
		if (iReturn > 0)
			return -1;
		return 0;
	}
	int __cdecl compare (void *plhs, void *prhs)
	{
	CTRiASOleDBRowT<CTRiASOleDBRowset> &lhs = 
		*reinterpret_cast<CTRiASOleDBRowT<CTRiASOleDBRowset> *>(plhs);
	CTRiASOleDBRowT<CTRiASOleDBRowset> &rhs = 
		*reinterpret_cast<CTRiASOleDBRowT<CTRiASOleDBRowset> *>(prhs);

		lhs.EnsureData(m_hPr, m_ulColumn);
		rhs.EnsureData(m_hPr, m_ulColumn);

		if (lhs.IsNullColumn(m_ulColumn))
			return -1;		// NULL ist immer am kleinsten
		else {
			if (rhs.IsNullColumn(m_ulColumn))
				return 1;
			return wcscmp ((BSTR)lhs.GetColumnData(m_ulColumn), 
				(BSTR)rhs.GetColumnData(m_ulColumn));
		}
	}

private:
	INT_PTR m_hPr;
	ULONG m_ulColumn;
};

///////////////////////////////////////////////////////////////////////////////
// aufsteigendes sortieren von Objektnummern
class COrderByPredAscONr :
	public binary_function<CTRiASOleDBRowT<CTRiASOleDBRowset>, 
		CTRiASOleDBRowT<CTRiASOleDBRowset>, bool>
{
public:
	COrderByPredAscONr(INT_PTR hPr, ULONG ulColumn) : 
		m_hPr(hPr), m_ulColumn(ulColumn+1) 
	{
		_ASSERTE(m_ulColumn >= 2);
	}
	~COrderByPredAscONr() 
	{
	}

	typedef int (__cdecl *COMPAREPROC)(const void *, const void *);
	typedef CCDeclThunkImpl<COrderByPredAscONr, COMPAREPROC> CCompareHook;

	int __cdecl invcompare (void *plhs, void *prhs)
	{
	int iReturn = compare (plhs, prhs);

		if (iReturn < 0)
			return 1;
		if (iReturn > 0)
			return -1;
		return 0;
	}
	int __cdecl compare (void *plhs, void *prhs)
	{
	CTRiASOleDBRowT<CTRiASOleDBRowset> &lhs = 
		*reinterpret_cast<CTRiASOleDBRowT<CTRiASOleDBRowset> *>(plhs);
	CTRiASOleDBRowT<CTRiASOleDBRowset> &rhs = 
		*reinterpret_cast<CTRiASOleDBRowT<CTRiASOleDBRowset> *>(prhs);

		lhs.EnsureData(m_hPr, m_ulColumn);
		rhs.EnsureData(m_hPr, m_ulColumn);

		_ASSERTE(!lhs.IsNullColumn(m_ulColumn) && !rhs.IsNullColumn(m_ulColumn));
		return *(INT_PTR *)lhs.GetColumnData(m_ulColumn) - *(INT_PTR *)rhs.GetColumnData(m_ulColumn);
	}

private:
	INT_PTR m_hPr;
	ULONG m_ulColumn;
};

///////////////////////////////////////////////////////////////////////////////
// aufsteigendes sortieren von Binärdaten
class COrderByPredAscBin :
	public binary_function<CTRiASOleDBRowT<CTRiASOleDBRowset>, 
		CTRiASOleDBRowT<CTRiASOleDBRowset>, bool>
{
public:
	COrderByPredAscBin(INT_PTR hPr, ULONG ulColumn) : 
		m_hPr(hPr), m_ulColumn(ulColumn+1) 
	{
		_ASSERTE(m_ulColumn >= 2);
	}
	~COrderByPredAscBin() 
	{
	}

	typedef int (__cdecl *COMPAREPROC)(const void *, const void *);
	typedef CCDeclThunkImpl<COrderByPredAscBin, COMPAREPROC> CCompareHook;

	int __cdecl invcompare (void *plhs, void *prhs)
	{
	int iReturn = compare (plhs, prhs);

		if (iReturn < 0)
			return 1;
		if (iReturn > 0)
			return -1;
		return 0;
	}
	int __cdecl compare (void *plhs, void *prhs)
	{
	CTRiASOleDBRowT<CTRiASOleDBRowset> &lhs = 
		*reinterpret_cast<CTRiASOleDBRowT<CTRiASOleDBRowset> *>(plhs);
	CTRiASOleDBRowT<CTRiASOleDBRowset> &rhs = 
		*reinterpret_cast<CTRiASOleDBRowT<CTRiASOleDBRowset> *>(prhs);

		lhs.EnsureData(m_hPr, m_ulColumn);
		rhs.EnsureData(m_hPr, m_ulColumn);

	ULONG ulLen = const_cast<CTRiASOleDBRowT<CTRiASOleDBRowset> &>(lhs).GetDataLen (m_ulColumn);

		_ASSERTE(!lhs.IsNullColumn(m_ulColumn) && !rhs.IsNullColumn(m_ulColumn));
		return memcmp ((BSTR)lhs.GetColumnData(m_ulColumn), (BSTR)rhs.GetColumnData(m_ulColumn), ulLen);
	}

private:
	INT_PTR m_hPr;
	ULONG m_ulColumn;
};

#endif // !defined(_ORDERBYPREDICATES_H__51379C9D_BFDA_4781_800C_595C30A1332A__INCLUDED_)
