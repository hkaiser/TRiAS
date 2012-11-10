// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 17.03.2002 10:47:04 
//
// @doc
// @module MapCtrlImpl.h | Declaration of the <c CMapCtrlImpl> class

#if !defined(__MAPCTRL_IMPL_H__B6AFCF11_1A64_11d2_8F7D_0060085FC1CE)
#define __MAPCTRL_IMPL_H__B6AFCF11_1A64_11d2_8F7D_0060085FC1CE

#import "MapCtrl.tlb" \
	no_namespace \
	raw_dispinterfaces \
	raw_interfaces_only \
	named_guids \
	no_implementation
#import "TRiASCS.tlb" \
	raw_interfaces_only	\
	raw_dispinterfaces	\
	no_implementation	\
	no_namespace		\
	named_guids

#include <ospace/file/path.h>
#include "McKinney/OleType.h"
#include "MapCtrlTree.h"

#define	CHECKINPOINTER(p) {_ASSERTE(p); if(!p) return E_POINTER;}

class ATL_NO_VTABLE ITopoMapImpl : 
	public ITopoMap 
{
protected:
	GCPList	m_listOfGCP;
	CComQIPtr<ITRiASCS, &IID_ITRiASCS> m_pCS;
	CComQIPtr<ITRiASCSGCS, &IID_ITRiASCSGCS> m_pGCS;
	CComQIPtr<ITRiASCSPCS, &IID_ITRiASCSPCS> m_pPCS;

// KK001108 - Die Differenzen am Rand (x, y, z = 0) sammmeln
	GCPList m_DiffPoints;

public:
	ITopoMapImpl() 
	{
	CComQIPtr<ITRiASCS, &IID_ITRiASCS> p;
	
		HRESULT	hr = p.CoCreateInstance(CLSID_TRIASCS);
		if (S_OK == hr) {
			m_pCS = p;
			try {
				p->get_GeographicCS(&m_pGCS);
				p->get_ProjectedCS(&m_pPCS);
			} catch(...) {
				_ASSERTE( NULL );
			}
		}
	}
	STDMETHOD(GetCoordSystem)(IUnknown** ppCoordSystem) 
	{
		CHECKINPOINTER(ppCoordSystem);
	
	HRESULT hr = E_FAIL;
	
		if(!!m_pCS) {
			*ppCoordSystem = m_pCS;
			(*ppCoordSystem)->AddRef();
			hr = S_OK;
		} 
		else {
			*ppCoordSystem = NULL;
		}
		return hr;
	}
	STDMETHOD(PutCoordSystem)(IUnknown *pICS)
	{
		CHECKINPOINTER(pICS);
		try {
			m_pCS.Release();
			m_pGCS.Release();
			m_pPCS.Release();

			m_pCS = pICS;
			m_pCS->get_GeographicCS(&m_pGCS);
			m_pCS->get_ProjectedCS(&m_pPCS);
		} 
		catch(...) {
			_ASSERTE(FALSE);
			return E_UNEXPECTED;
		}
		return S_OK;
	}
	STDMETHOD(GetImageFileFilter)(BSTR* pFilter) 
	{
		CHECKINPOINTER(pFilter);

	CComBSTR strT;

		VERIFY(strT.LoadString(_Module.GetResourceInstance(), IDS_TIFFFILTER));
		*pFilter = strT.Detach();
		return S_OK;
	}
	STDMETHOD(GetAltFileFilter)(BSTR* pFilter) 
	{
		CHECKINPOINTER(pFilter);
		*pFilter = NULL;
		return S_FALSE;
	}
	STDMETHOD(GetDisplayName)(BSTR * strDisplay) 
	{
		CHECKINPOINTER(strDisplay);
		*strDisplay = NULL;
		return S_OK;
	}
	STDMETHOD(CheckPictureFile)(ITopoPict* pServer, long* pValid) 
	{
		CHECKINPOINTER(pValid);

	CComVariant	v;
	CComVariant	vDbl;
	double	W, H;
	HRESULT	hr = E_FAIL;

		m_listOfGCP.erase(m_listOfGCP.begin(), m_listOfGCP.end());
		try {
			for(;;) {
				if (S_OK != pServer->GetTagValue (256, &v) ||
					S_OK != ::VariantChangeType(&vDbl, &v, 0, VT_R8))
					break;
				W = vDbl.dblVal;

				if (S_OK != pServer->GetTagValue(257, &v) ||
					S_OK != ::VariantChangeType(&vDbl, &v, 0, VT_R8))
					break;
				H = vDbl.dblVal;

			// GCP's in der Reihenfolge LinksUnten, RechtsUnten, RechtsOben, LinksOben
			// danach ggf. die restlichen
				m_listOfGCP.push_back(GCP(GEOPOINT(), GEOPOINT(0, H, 0)));
				m_listOfGCP.push_back(GCP(GEOPOINT(), GEOPOINT(W, H, 0)));
				m_listOfGCP.push_back(GCP(GEOPOINT(), GEOPOINT(W, 0, 0)));
				m_listOfGCP.push_back(GCP(GEOPOINT(), GEOPOINT(0, 0, 0)));
				*pValid = TRUE;
				hr = S_OK;
				break;
			}
		} catch(...) {
			hr = E_UNEXPECTED;
		}
		return hr;
	}
	STDMETHOD(CheckAltFile)(BSTR strFileName, long* pValid) 
	{
		CHECKINPOINTER(pValid);
		*pValid = TRUE;
		return S_OK;
	}
	STDMETHOD(GetNameAndIdent)(BSTR bstrPathName, BSTR *pbstrName, BSTR *pbstrIdent) 
	{
		USES_CONVERSION;

	os_path fullname = OLE2A(bstrPathName);

		*pbstrName = ::SysAllocString(A2OLE(fullname.base().c_str()));
		*pbstrIdent = ::SysAllocString(A2OLE(fullname.base().c_str()));
		return S_OK;
	}
	STDMETHOD(HaveNomenclatur)(long* pHaveNomenclatur) 
	{
		CHECKINPOINTER(pHaveNomenclatur);
		*pHaveNomenclatur = FALSE;
		return S_OK;
	}
	STDMETHOD(PrepareFinalData)(/* [out][in] */ long * bHavePrepared) 
	{
		CHECKINPOINTER(bHavePrepared);
		*bHavePrepared = (m_listOfGCP.size() >= 4) ? TRUE : FALSE;
		return S_OK;
	}
	STDMETHOD(GetCoordinates)(/*[out]*/ SAFEARRAY** ppCoordinates) 
	{
		CHECKINPOINTER(ppCoordinates);
		HRESULT hr = E_FAIL;
		try {
		MC::ArrayDouble	coords(MC::Dim(3*m_listOfGCP.size()));
		UINT arrIdx, coord;

			coords.Lock();
			for (coord = 0, arrIdx = 0; coord < m_listOfGCP.size(); coord++) {
			GEOPOINT gp = m_listOfGCP[coord].m_ptGeoCoord;

				coords[arrIdx++] = gp.X;
				coords[arrIdx++] = gp.Y;
				coords[arrIdx++] = gp.Z;
			}
			coords.Unlock();
			*ppCoordinates = *coords;
			hr = S_OK;
		} catch(...) {
			hr = E_UNEXPECTED;
		}
		return hr;
	}
	STDMETHOD(GetRefPoints)(/*[out]*/ SAFEARRAY** ppCoordinates) 
	{
		CHECKINPOINTER(ppCoordinates);
		HRESULT hr = E_FAIL;
		try {
		MC::ArrayDouble	coords(MC::Dim (3*m_listOfGCP.size()));
		UINT arrIdx, coord;

			coords.Lock();
			for (coord = 0, arrIdx = 0; coord < m_listOfGCP.size(); coord++) {
			GEOPOINT gp = m_listOfGCP[coord].m_ptPictPoint;

				coords[arrIdx++] = gp.X;
				coords[arrIdx++] = gp.Y;
				coords[arrIdx++] = gp.Z;
			}
			coords.Unlock();
			*ppCoordinates = *coords;
			hr = S_OK;

		} catch(...) {
			hr = E_UNEXPECTED;
		}
		return hr;
	}
	STDMETHOD(NeedFixPoints)(/*[in,out]*/ long* pNeedPoints) 
	{
		CHECKINPOINTER(pNeedPoints);
		*pNeedPoints = FALSE;
		return S_OK;
	}
	STDMETHOD(PutFixPoints)(/*[in]*/ SAFEARRAY* ppCoordinates) 
	{
		CHECKINPOINTER(ppCoordinates)
		_ASSERTE(m_listOfGCP.size() >= 4);
	
	HRESULT hr = E_FAIL;

		try {
		MC::ArrayDouble	geoPoints(ppCoordinates);
		UINT arrIdx, coord;
		
			_ASSERTE( geoPoints.Elements() == 4 * 3 );
			geoPoints.Lock();
			for( coord = 0, arrIdx = 0; coord < 4; coord++ ) {
			GEOPOINT gp;

				gp.X = geoPoints[arrIdx++];
				gp.Y = geoPoints[arrIdx++];
				gp.Z = geoPoints[arrIdx++];
				m_listOfGCP[coord].m_ptGeoCoord = gp;
			}
			geoPoints.Unlock();
			hr = S_OK;

		} catch(...) {
			hr = E_UNEXPECTED;
		}
		return hr;
	}

// KK001108
	STDMETHOD(GetDifferenz)(/*[out]*/ SAFEARRAY** ppCoordinates) 
	{
		CHECKINPOINTER(ppCoordinates);
		HRESULT hr = E_FAIL;
		try {
		MC::ArrayDouble	coords(MC::Dim(3*m_DiffPoints.size()));
		UINT	arrIdx, coord;

			coords.Lock();
			for( coord = 0, arrIdx = 0; coord < 4; coord++ ) {
			GEOPOINT gp = m_DiffPoints[coord].m_ptGeoCoord;

				coords[arrIdx++] = gp.X;
				coords[arrIdx++] = gp.Y;
				coords[arrIdx++] = gp.Z;
			}
			coords.Unlock();
			*ppCoordinates = *coords;
			hr = S_OK;
		} catch(...) {
			hr = E_UNEXPECTED;
		}
		return hr;
	}
	STDMETHOD(GetAltFileTyp)(/*[in,out]*/ BSTR* pTyp) 
	{
		CHECKINPOINTER(pTyp);
		*pTyp = NULL;
		return S_FALSE;
	}
	STDMETHOD(HaveMultiMap)(/*[out]*/long* pHaveMultiMap) 
	{
		CHECKINPOINTER(pHaveMultiMap);
		*pHaveMultiMap = FALSE;
		return S_OK;
	}

// #HK020318
	STDMETHOD(BitmapIndex)(/*[out, retval]*/ long *plIndex)
	{
		CHECKINPOINTER(plIndex);
		*plIndex = IMG_MAPPICT;		// StandardIcon
		return S_OK;
	}
	STDMETHOD(CorrectName)(/*[in]*/ BSTR bstrDestDir, /*[in]*/ BSTR bstrName, 
		/*[out, retval]*/ BSTR *pbstrToWrite)
	{
		CHECKINPOINTER(pbstrToWrite);
		*pbstrToWrite = ::SysAllocString(bstrName);
		return S_OK;
	}
	STDMETHOD(CorrectDirectory)(/*[in]*/ BSTR bstrDestDir, /*[out, retval]*/ BSTR *pbstrToWrite)
	{
		CHECKINPOINTER(pbstrToWrite);
		*pbstrToWrite = ::SysAllocString(bstrDestDir);
		return S_OK;
	}
	STDMETHOD(CopyFlags)(/*[out, retval]*/ COPYFLAG *prgFlags)
	{
		CHECKINPOINTER(prgFlags);
		*prgFlags = COPYFLAG_Default;
		return S_OK;
	}
	STDMETHOD(GetDescription)(/*[out, retval]*/ BSTR *prgFlags)
	{
		CHECKINPOINTER(prgFlags);
		*prgFlags = NULL;
		return E_NOTIMPL;
	}
	STDMETHOD(GetDefaultFileTyp)(/*[in,out]*/ BSTR* pbstrTyp) 
	{
		CHECKINPOINTER(pbstrTyp);
		*pbstrTyp = NULL;

	CComBSTR bstrFilter;
	HRESULT hr = GetImageFileFilter(&bstrFilter);

		if (FAILED(hr))
			return hr;

	wchar_t *pcoleDot = wcsrchr(bstrFilter, L'.');

		if (NULL != pcoleDot) {
		CComBSTR bstrTyp (4, pcoleDot);
		
			*pbstrTyp = bstrTyp.Detach(); 
		}
		return S_OK;
	}
	STDMETHOD(MakeFullName)(BSTR bstrBaseDir, BSTR *pbstrFullName)
	{
		CHECKINPOINTER(pbstrFullName);
		*pbstrFullName = ::SysAllocString(bstrBaseDir);
		return S_OK;
	}

// #HK021018
	STDMETHOD(NeedsCoordSystem)(VARIANT_BOOL *pfNeedsCoordSys)
	{
		CHECKINPOINTER(pfNeedsCoordSys);
		*pfNeedsCoordSys = VARIANT_FALSE;
		return S_OK;
	}
};

#endif //__MAPCTRL_IMPL_H__B6AFCF11_1A64_11d2_8F7D_0060085FC1CE
