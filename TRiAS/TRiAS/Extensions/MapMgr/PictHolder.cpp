#include "stdafx.h"
#include "MapMgrImpl.h"
#include "PictHolder.h"

/////////////////////////////////////////////////////////////////////////////
// CPictHolder

HRESULT CPictHolder::FinalConstruct() 
{
	return S_OK;
}

void CPictHolder::FinalRelease() 
{
	Close();
}

STDMETHODIMP CPictHolder::Close() 
{
	if( m_pPicture ) {
		m_pPicture->Detach();
		delete m_pPicture;
		m_pPicture = NULL;
	}
	if( CFile::hFileNull != m_fileOfPicture.m_hFile ) {
		m_fileOfPicture.Close();
		_ASSERTE( CFile::hFileNull == m_fileOfPicture.m_hFile );
	}
	return S_OK;
}

STDMETHODIMP CPictHolder::OpenPictureFile(BSTR strPicture) 
{
	Close();
	CString S( strPicture );
	if( !m_fileOfPicture.Open( S, CFile::modeRead | CFile::typeBinary ) )
		return E_FAIL;
	CRuntimeClass	*pRT;
	CPicture		*pPict = NULL;
	HRESULT	hr = E_FAIL;
	try {
		for(;;) {
			if( NULL == ( pRT = GetWritablePictureType( &m_fileOfPicture ) ) )
				break;
			pPict = (CPicture*) pRT->CreateObject();
			VERIFY( pPict->Attach( &m_fileOfPicture ) && pPict->ReadHeader() );
			m_pPicture = pPict;
			hr = S_OK;
			break;
		}
	} catch(...) {
		if( pPict )
			delete pPict;
		m_pPicture = NULL;
	}
	return hr;
}

STDMETHODIMP CPictHolder::GetTagValue(long tag, VARIANT* pValue) 
{
	if( !pValue )
		return E_POINTER;
	if( !m_pPicture )
		return E_FAIL;
	if( !m_pPicture )
		return E_FAIL;
	HRESULT	hr = E_FAIL;
	try {
		TAG	t;
		CComVariant	v;
		v.Clear();
		m_pPicture->GetTag( (PICT_PROPERTY)tag, t );
		switch( t.Type() ) {
		case _DOUBLE : v = t.dVal(); break;
		case _LONG : v = t.slVal(); break;
		case _SLONG : v = (long) t.ulVal(); break;
		case _SSHORT : v = t.ssVal(); break;
		case _ASCII : v = t.strVal(); break;
		}
		if( VT_EMPTY != v.vt ) {
			*pValue = v;
			hr = S_OK;
		}
	} catch(...) {
		hr = E_UNEXPECTED;
	}
	return hr;
}

STDMETHODIMP CPictHolder::GetGeoCodedPoints(SAFEARRAY **ppCoordinates,
	IUnknown **ppICS) 
{
	if (NULL == ppCoordinates || NULL == ppICS)
		return E_POINTER;

	*ppCoordinates = NULL;
	*ppICS = NULL;

GCPList listPts;

	if (!m_pPicture->GetGeoPoints(&listPts) || listPts.size() < 4)
		return E_UNEXPECTED;

	if (!m_pPicture->GetGeoPointCS(ppICS, listPts))
		return E_UNEXPECTED;

HRESULT hr = E_FAIL;

	try {
	MC::ArrayDouble	coords(MC::Dim(6 * listPts.size()));
	UINT arrIdx, coord;

		coords.Lock();
		for (coord = 0, arrIdx = 0; coord < 4; ++coord) {
		GEOPOINT gp = listPts[coord].m_ptGeoCoord;

			coords[arrIdx++] = gp.X;
			coords[arrIdx++] = gp.Y;
			coords[arrIdx++] = gp.Z;

		GEOPOINT gpPict = listPts[coord].m_ptPictPoint;

			coords[arrIdx++] = gpPict.X;
			coords[arrIdx++] = gpPict.Y;
			coords[arrIdx++] = gpPict.Z;
		}
		coords.Unlock();

		*ppCoordinates = *coords;
		hr = S_OK;

	} catch(...) {
		hr = E_UNEXPECTED;
	}
	return hr;
}

