///////////////////////////////////////////////////////////////////////////
// @doc
// @module GeoUtil.h | Helperroutinen et. al.

#if !defined(_GEOUTIL_H__541311B4_9FE0_11D1_BA1E_080036D63803__INCLUDED_)
#define _GEOUTIL_H__541311B4_9FE0_11D1_BA1E_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
//
template<class T>
	inline HRESULT LoadItem (IStream * pIStm , T & rVal)
{
	return pIStm -> Read (& rVal , sizeof(T) , NULL);
}

template<class T>
	inline HRESULT SaveItem (IStream * pIStm , T Val)
{
	return pIStm -> Write (& Val , sizeof(T) , NULL);
}

///////////////////////////////////////////////////////////////////////////////
// Anzahl der Bytes für ein BSTR in einem Stream
inline
ULONG LenForStream (const CComBSTR & bstr)
{
	return (bstr.m_str ? ::SysStringByteLen(bstr.m_str) + sizeof(OLECHAR) : 0) + sizeof(ULONG);
}

void __cdecl FormatMessage(CString & rStr , UINT uiError , ...);

/////////////////////////////////////////////////////////////////////////////
// Support for IPersistMemory
/*
CTRiASCSBoundaryGeometry
CTRiASCSGeometryCollection
CTRiASCSLineGeometry
CTRiASCSOrientedPointGeometry
CTRiASCSPoint
CTRiASCSPointInCol
CTRiASCSPointGeometry
CTRiASCSPoints
CTRiASCSPolylineBase
CTRiASCSRectangleGeometry
CTRiASCSTextPointGeometry
CTRiASCSVector
*/

template<class T>
inline void SaveAndAdvance (void * & p , T x)
{
	memcpy (p , (void *) &x , sizeof(T));
	p = (BYTE *)p + sizeof(T);
}
inline void SaveAndAdvance (void * & p , void * px , unsigned int iSize)
{
	memcpy (p , px , iSize);
	p = (BYTE *)p + iSize;
}

template<class T>
inline void LoadAndAdvance (T & x , void * & p)
{
	memcpy ((void *) & x , p , sizeof(T));
	p = (BYTE *)p + sizeof(T);
}
inline void LoadAndAdvance (void * px , void * & p , unsigned int iSize)
{
	memcpy (px , p , iSize);
	p = (BYTE *)p + iSize;
}

/////////////////////////////////////////////////////////////////////////////
// HelperKlasse für ThreadSynchronisation
template<class ThreadModel>
class CLockCritSection
{
private:
	CComObjectRootEx<ThreadModel> & m_rObj;

public:
	CLockCritSection (CComObjectRootEx<ThreadModel> & rObj)
		: m_rObj(rObj) { m_rObj.Lock(); }
	~CLockCritSection() { m_rObj.Unlock(); }
};

typedef CLockCritSection<CComObjectThreadModel> CLockThread;

///////////////////////////////////////////////////////////////////////////////
// helper, um reine [out] Parameter sauber zu halten
inline BSTR * CLEARED (BSTR *pbstr)
{
	_ASSERTE(NULL != pbstr);
	if (NULL != pbstr)
	{
		::SysFreeString(*pbstr);
		*pbstr = NULL;
	}
	return pbstr;
}

inline VARIANT * CLEARED (CComVariant * pv)
{
	_ASSERTE(NULL != pv);
	pv -> Clear();
	return pv;
}

///////////////////////////////////////////////////////////////////////////////
// Punkt im Wkt Format an eine Zeichenkette dranhängen
inline HRESULT AppendPoint (CComBSTR &rbstr, double dX, double dY, bool fAppendComma = true)
{
CComVariant vX (dX);
CComVariant vY (dY);

	RETURN_FAILED_HRESULT(vX.ChangeType(VT_BSTR));
	RETURN_FAILED_HRESULT(vY.ChangeType(VT_BSTR));

	rbstr.AppendBSTR(V_BSTR(&vX));
	rbstr.Append(L" ");
	rbstr.AppendBSTR(V_BSTR(&vY));
	if (fAppendComma)
		rbstr.Append(L", ");
	return S_OK;
}

#endif // !defined(_GEOUTIL_H__541311B4_9FE0_11D1_BA1E_080036D63803__INCLUDED_)
