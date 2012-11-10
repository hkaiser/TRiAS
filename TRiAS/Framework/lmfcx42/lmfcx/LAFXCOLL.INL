// Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1993 Microsoft Corporation,
// All rights reserved.

// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp and/or WinHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

// Inlines for LAFXCOLL.H

#ifdef _AFXCOLL_INLINE

////////////////////////////////////////////////////////////////////////////
// Inlines for CDoubleArray

_AFXCOLL_INLINE int CDoubleArray::GetSize() const
	{ return m_nSize; }
_AFXCOLL_INLINE int CDoubleArray::GetUpperBound() const
	{ return m_nSize-1; }
_AFXCOLL_INLINE void CDoubleArray::RemoveAll()
	{ SetSize(0); }
_AFXCOLL_INLINE double CDoubleArray::GetAt(int nIndex) const
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		return m_pData[nIndex]; }
_AFXCOLL_INLINE void CDoubleArray::SetAt(int nIndex, double newElement)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		m_pData[nIndex] = newElement; }
_AFXCOLL_INLINE double& CDoubleArray::ElementAt(int nIndex)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		return m_pData[nIndex]; }
_AFXCOLL_INLINE int CDoubleArray::Add(double newElement)
	{ int nIndex = m_nSize;
		SetAtGrow(nIndex, newElement);
		return nIndex; }
_AFXCOLL_INLINE double CDoubleArray::operator[](int nIndex) const
	{ return GetAt(nIndex); }
_AFXCOLL_INLINE double& CDoubleArray::operator[](int nIndex)
	{ return ElementAt(nIndex); }

////////////////////////////////////////////////////////////////////////////
// Inlines for CPointArray

_AFXCOLL_INLINE int CPointArray::GetSize() const
	{ return m_nSize; }
_AFXCOLL_INLINE int CPointArray::GetUpperBound() const
	{ return m_nSize-1; }
_AFXCOLL_INLINE void CPointArray::RemoveAll()
	{ SetSize(0); }
_AFXCOLL_INLINE POINT CPointArray::GetAt(int nIndex) const
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		return m_pData[nIndex]; }
_AFXCOLL_INLINE void CPointArray::SetAt(int nIndex, POINT newElement)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		m_pData[nIndex] = newElement; }
_AFXCOLL_INLINE POINT& CPointArray::ElementAt(int nIndex)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		return m_pData[nIndex]; }
_AFXCOLL_INLINE int CPointArray::Add(POINT newElement)
	{ int nIndex = m_nSize;
		SetAtGrow(nIndex, newElement);
		return nIndex; }
_AFXCOLL_INLINE POINT CPointArray::operator[](int nIndex) const
	{ return GetAt(nIndex); }
_AFXCOLL_INLINE POINT& CPointArray::operator[](int nIndex)
	{ return ElementAt(nIndex); }

////////////////////////////////////////////////////////////////////////////
// Inlines for CPointlArray

_AFXCOLL_INLINE int CPointlArray::GetSize() const
	{ return m_nSize; }
_AFXCOLL_INLINE int CPointlArray::GetUpperBound() const
	{ return m_nSize-1; }
_AFXCOLL_INLINE void CPointlArray::RemoveAll()
	{ SetSize(0); }
_AFXCOLL_INLINE POINTL CPointlArray::GetAt(int nIndex) const
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		return m_pData[nIndex]; }
_AFXCOLL_INLINE void CPointlArray::SetAt(int nIndex, POINTL newElement)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		m_pData[nIndex] = newElement; }
_AFXCOLL_INLINE POINTL& CPointlArray::ElementAt(int nIndex)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		return m_pData[nIndex]; }
_AFXCOLL_INLINE int CPointlArray::Add(POINTL newElement)
	{ int nIndex = m_nSize;
		SetAtGrow(nIndex, newElement);
		return nIndex; }
_AFXCOLL_INLINE POINTL CPointlArray::operator[](int nIndex) const
	{ return GetAt(nIndex); }
_AFXCOLL_INLINE POINTL& CPointlArray::operator[](int nIndex)
	{ return ElementAt(nIndex); }

////////////////////////////////////////////////////////////////////////////

_AFXCOLL_INLINE int CMapDWordToOb::GetCount() const
	{ return m_nCount; }
_AFXCOLL_INLINE BOOL CMapDWordToOb::IsEmpty() const
	{ return m_nCount == 0; }
_AFXCOLL_INLINE void CMapDWordToOb::SetAt(DWORD key, CObject* newValue)
 	{ (*this)[key] = newValue; }
_AFXCOLL_INLINE POSITION CMapDWordToOb::GetStartPosition() const
	{ return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
_AFXCOLL_INLINE UINT CMapDWordToOb::GetHashTableSize() const
	{ return m_nHashTableSize; }

////////////////////////////////////////////////////////////////////////////

_AFXCOLL_INLINE int CTree::GetLevel( ) const
	{ ASSERT_VALID( this ); return m_iLevel; }
_AFXCOLL_INLINE int CTree::GetItems( ) const
	{ ASSERT_VALID( this ); return m_nItems; }
_AFXCOLL_INLINE CTree* CTree::GetParent() const
	{ ASSERT_VALID( this ); return m_pParent; }
_AFXCOLL_INLINE CObject* CTree::GetObject( )
	{ ASSERT_VALID( this ); return m_pObject; }
_AFXCOLL_INLINE CObject* CTree::GetObject( LPCTSTR pszNode )
	{ ASSERT_VALID( this ); CTree	*pNode = GetNode( pszNode );
		return NULL != pNode ? pNode->GetObject() : NULL;
	}

#endif //_AFXCOLL_INLINE
