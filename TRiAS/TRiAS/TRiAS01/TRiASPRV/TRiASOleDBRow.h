// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 11.05.2001 09:31:48 
//
// @doc
// @module TRiASOleDBRow.h | Declaration of the <c CTRiASOleDBRowT> class

#if !defined(_TRIASOLEDBROW_H__EE778455_B50A_4B6F_B11C_2318CFE37E26__INCLUDED_)
#define _TRIASOLEDBROW_H__EE778455_B50A_4B6F_B11C_2318CFE37E26__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// eine Zeile eines durchschnittlichen ErgebnisRowsets
template<typename T>
class CTRiASOleDBRowT
{
public:
	CTRiASOleDBRowT(T &rRowset, INT_PTR lONr) :
		m_ppData(NULL), m_rRowset(rRowset)
	{
		AllocRowData(GetNumCols());
		AddRef();
		SetBookmark(lONr);
	}
	CTRiASOleDBRowT(const CTRiASOleDBRowT &rhs) :
		m_ppData(rhs.m_ppData), m_rRowset(rhs.m_rRowset)
	{
		AddRef();
	}
	~CTRiASOleDBRowT()
	{
		DisposeRowData();
	}

	CTRiASOleDBRowT &operator= (const CTRiASOleDBRowT &rhs) 
	{
		if (m_ppData != rhs.m_ppData) {
			DisposeRowData();
			m_ppData = rhs.m_ppData;
			AddRef();
		}
		return *this;
	}
	void Reset()
	{
		DisposeRowData();
	}

// Helperfunktionen fürs sortieren
	friend void swap (CTRiASOleDBRowT &lhs, CTRiASOleDBRowT &rhs)
	{
		_ASSERTE(&lhs.m_rRowset == &rhs.m_rRowset);		// müssen zum gleichen Rowset gehören
		swap (rhs.m_ppData, lhs.m_ppData);				// lediglich Daten vertauschen
	}
	friend void iter_swap (CTRiASOleDBRowT *plhs, CTRiASOleDBRowT *prhs)
	{
		_ASSERTE(&(plhs -> m_rRowset) == &(prhs -> m_rRowset));		// müssen zum gleichen Rowset gehören
		swap (plhs -> m_ppData, plhs -> m_ppData);					// lediglich Daten vertauschen
	}

// liefert immer 'richtige' Daten (NULL oder existierenden Wert
	void *GetColumnData (ULONG ulColumn) const
	{
		_ASSERTE(IsValidColumn(ulColumn));
		_ASSERTE(ColumnWasFetched(ulColumn));
		return (reinterpret_cast<void *>(COLUMN_IS_NULL) == m_ppData[ulColumn]) ? NULL : m_ppData[ulColumn];
	}

// Liefert die Länge der Daten einer Zelle
	ULONG GetDataLen (ULONG ulColumn)
	{
		return m_rRowset.GetDataLen(ulColumn-1, GetColumnData(ulColumn));
	}

// vergleichen des Inhaltes zweier Spalten
	bool CompareColumnData (ULONG ulColumn, void *pLeft, void *pRight)
	{
		if (NULL == pLeft && NULL == pRight)
			return true;
		
		if (NULL != pLeft && NULL != pRight) {
		ULONG ulLen = m_rRowset.GetDataLen(ulColumn-1, pLeft);

			if (ulLen != m_rRowset.GetDataLen(ulColumn-1, pRight))
				return false;

			if (!m_rRowset.MustIndirectCompareData(ulColumn-1))
				return 0 == memcpy(&pLeft, &pRight, ulLen);
			return 0 == memcmp(pLeft, pRight, ulLen);
		}

		return false;	// genau einer der Werte ist NULL
	}

// Bookmark setzen/lesen
	void SetBookmark (INT_PTR lONr)
	{
		_ASSERTE(NULL != m_ppData);
		((INT_PTR *)m_ppData)[1] = lONr;
		SetColumnWasFetched(1);
	}
	INT_PTR GetBookmark()
	{
		_ASSERTE(NULL != m_ppData);
		_ASSERTE(ColumnWasFetched(1));
		return ((INT_PTR *)m_ppData)[1];
	}

// wird aus Command oder Session gerufen
	template<typename T>
	static ATLCOLUMNINFO *GetColumnInfo(T *pThis, ULONG* pcCols)
	{
		return pThis -> GetRawColumnInfo(pcCols);
	}

protected:
	void AllocRowData(ULONG ulItemCount)
	{
		_ASSERTE(sizeof(ULONG) == sizeof(void *));
		m_ppData = (void **)CoTaskMemAlloc((ulItemCount+1) * sizeof(void *));
		memset (m_ppData, '\0', (ulItemCount+1) * sizeof(void *));
	}
	void DisposeRowData()
	{
		if (NULL != m_ppData) {
			if (0 == Release()) {
			// Feld[0]: RefCnt, Feld[1]: Bookmark
				for (ULONG ul = 2; ul < GetNumCols(); ++ul) 
					DisposeColumnData(m_ppData[ul]);

				CoTaskMemFree(m_ppData);
			}
			m_ppData = NULL;
		}
	}

// Speicher für eine Spalte verwalten
	void *AllocColumnData (void *pData, ULONG ulSize)
	{
		_ASSERTE(NULL != pData || 0 == ulSize);
		return (NULL != pData) ? (void *)SysAllocStringLen((OLECHAR *)pData, ulSize) : NULL;
	}
	void DisposeColumnData (void *& rpColData)
	{
		if (NULL != rpColData && reinterpret_cast<void *>(COLUMN_IS_NULL) != rpColData) {
			SysFreeString((BSTR)rpColData);
			rpColData = NULL;
		}
	}

// RefCnt für die gesamte Datenstruktur
	ULONG AddRef()
	{
		_ASSERTE(NULL != m_ppData);
		return ++((ULONG *)m_ppData)[0];
	}
	ULONG Release()
	{
		_ASSERTE(NULL != m_ppData);
		return --((ULONG *)m_ppData)[0];
	}

	bool IsValidColumn(ULONG ulColumn) const
	{
		return 0 < ulColumn && ulColumn <= GetNumCols();
	}

// Verwalten, ob Daten bereits gelesen wurden und NULL sind
	enum { COLUMN_IS_NULL = 0xFDFDFDFD,	};	// Spalte hat keine Daten

public:
	bool ColumnWasFetched(ULONG ulColumn) const
	{
		_ASSERTE(IsValidColumn(ulColumn));
		return NULL != m_ppData[ulColumn];
	}
	void SetColumnWasFetched (ULONG ulColumn)
	{
		_ASSERTE(IsValidColumn(ulColumn));
		if (NULL == m_ppData[ulColumn])
			m_ppData[ulColumn] = reinterpret_cast<void *>(COLUMN_IS_NULL);
	}
	bool IsNullColumn(ULONG ulColumn) const 
	{
		_ASSERTE(IsValidColumn(ulColumn));
		_ASSERTE(ColumnWasFetched(ulColumn));
		return reinterpret_cast<void *>(COLUMN_IS_NULL) == m_ppData[ulColumn];
	}

// Datenzugriff: Auslesen eines Wertes einer Spalte
	HRESULT GetData (INT_PTR hPr, ATLCOLUMNINFO *pColInfo, ULONG &rulSize, void *& rpData, 
		DBSTATUS &rdbStatus, DBBINDING *pBindCur)
	{
		_ASSERTE(NULL != pColInfo);

	ULONG ulColumn = pColInfo->iOrdinal;

		_ASSERTE(0 <= ulColumn && ulColumn < GetNumCols());

	// werden die Daten dieser Spalte zum ersten mal gebraucht ?
	HRESULT hr = S_OK;

		++ulColumn;		// Element 0 ist der ReferenzZähler
		hr = EnsureData (hPr, ulColumn, pBindCur);

	// Verweis auf Daten in Buffer kopieren
		if (FAILED(hr)) {
		// ColumnValue is NULL
			rpData = NULL;
			rulSize = 0;
			rdbStatus = DBSTATUS_S_ISNULL;
		}
		else {
			rulSize = 0;
			if (m_rRowset.MustIndirectGetData(ulColumn-1))
				rpData = &m_ppData[ulColumn];
			else
				rpData = m_ppData[ulColumn];

			if (NULL == rpData || reinterpret_cast<void *>(COLUMN_IS_NULL) == rpData) 
				rulSize = 0;
			else if (0 == rulSize)
				rulSize = m_rRowset.GetDataLen(ulColumn-1, rpData);			// sonstiges

			rdbStatus = (NULL != rpData && reinterpret_cast<void *>(COLUMN_IS_NULL) != rpData) ? DBSTATUS_S_OK : DBSTATUS_S_ISNULL;
		}
		return S_OK;
	}

// Modifizieren eines Wertes einer Spalte
	HRESULT SetData (INT_PTR hPr, ATLCOLUMNINFO *pColInfo, ULONG ulSize, void *pData, DBBINDING *pBindCur)
	{
		_ASSERTE(NULL != pColInfo);

	ULONG ulColumn = pColInfo->iOrdinal;

		_ASSERTE(0 <= ulColumn && ulColumn < GetNumCols());

	HRESULT hr = m_rRowset.GetHandler(ulColumn) -> StoreData(hPr, GetBookmark(), pBindCur, ulSize, pData);

		++ulColumn;		// Element 0 ist der ReferenzZähler
		if (SUCCEEDED(hr)) {
			DisposeColumnData (m_ppData[ulColumn]);
			m_ppData[ulColumn] = AllocColumnData(pData, ulSize);
		}
		return hr;
	}

// Vergleichen zweier Row's (Vergleichsoperator für 'SELECT DISTINCT' statements)
	HRESULT CompareRows (CTRiASOleDBRowT<T> &rhs)
	{
		if (this == &rhs)
			return S_OK;

	// Feld[0]: RefCnt, Feld[1]: Bookmark
	INT_PTR hPrjHandle = m_rRowset.GetProjectHandle();

		for (ULONG ul = 2; ul <= GetNumCols(); ++ul) {
			EnsureData (hPrjHandle, ul);
			rhs.EnsureData (hPrjHandle, ul);

			if (!CompareColumnData (ul, GetColumnData(ul), rhs.GetColumnData(ul)))
				return S_FALSE;		// nicht identisch
		}
		return S_OK;	// alles identisch
	}

	HRESULT EnsureData (INT_PTR hPrjHandle, ULONG ulColumn, DBBINDING *pBindCur = NULL)
	{
	HRESULT hr = S_OK;

		if (!ColumnWasFetched(ulColumn)) {
		// Bookmark enthält Objektnummer, FetchData liefert Pointer auf eigentliche Daten
			_ASSERTE(ulColumn >= 2);		// Bookmark ist schon da

		CComPtr<IHandleDataAccess> Handler (m_rRowset.GetHandler(ulColumn-1));

			if (Handler == NULL)		// no handler, no columndata
				return DB_E_NOCOLUMN;

			hr = Handler -> FetchData (hPrjHandle, GetBookmark(), pBindCur, &m_ppData[ulColumn]);
			SetColumnWasFetched(ulColumn);
		}
		return hr;
	}

// Anzahl der Spalten dieser Row (incl. lokalem Bookmark in Feldelement m_ppData[1])
	ULONG GetNumCols() const
	{
		return m_rRowset.GetNumCols() + (m_rRowset.GetUseBookmarks() ? 0 : 1);
	}

	bool IsValid() const
	{
		return NULL != m_ppData;
	}

private:
	void **m_ppData;	// eigentliche Werte 
	T &m_rRowset;		// zeigt auf den zugehörigen Rowset/Index
};

#endif // !defined(_TRIASOLEDBROW_H__EE778455_B50A_4B6F_B11C_2318CFE37E26__INCLUDED_)
