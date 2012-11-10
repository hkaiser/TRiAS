/*
 * IDATAOBJ.CPP
 * Data Transfer Object Chapter 7
 *
 * Implementation of the IDataObject interface for CDataObject.
 *
 * Copyright (c)1993 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Software Design Engineer
 * Microsoft Systems Developer Relations
 *
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "featurep.hxx"

#include <pdataobj.hxx>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*
 * CImpIDataObject::CImpIDataObject
 * CImpIDataObject::~CImpIDataObject
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIDataObject::CImpIDataObject (CDataObject *pObj, LPUNKNOWN pUnkOuter)
{
	m_cRef = 0;
	m_pObj = pObj;
	m_pUnkOuter = pUnkOuter;
}

CImpIDataObject::~CImpIDataObject (void)
{
}

/*
 * CImpIDataObject::QueryInterface
 * CImpIDataObject::AddRef
 * CImpIDataObject::Release
 *
 * Purpose:
 *  IUnknown members for CImpIDataObject object.
 */

STDMETHODIMP CImpIDataObject::QueryInterface (REFIID riid, LPVOID *ppv)
{
	return m_pUnkOuter -> QueryInterface (riid, ppv);
}


STDMETHODIMP_ (ULONG) CImpIDataObject::AddRef (void)
{
	++m_cRef;
	return m_pUnkOuter -> AddRef ();
}

STDMETHODIMP_ (ULONG) CImpIDataObject::Release (void)
{
	TX_ASSERT(m_cRef > 0);

	--m_cRef;
	return m_pUnkOuter -> Release ();
}


/*
 * CImpIDataObject::GetData
 *
 * Purpose:
 *  Retrieves data described by a specific FormatEtc into a StgMedium
 *  allocated by this function.  Used like GetClipboardData.
 *
 * Parameters:
 *  pFE             LPFORMATETC describing the desired data.
 *  pSTM            LPSTGMEDIUM in which to return the data.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */
STDMETHODIMP CImpIDataObject::GetData (LPFORMATETC pFE, LPSTGMEDIUM pSTM)
{
	if (NULL == pFE || NULL == pSTM)
		return ResultFromScode (DATA_E_FORMATETC);

CRenderData::iterator it = m_pObj -> m_DataList.begin();

	for (/**/; it != m_pObj -> m_DataList.end(); it++) {
	// Check if the requested FORMATETC is the same as one that we
	// already have. If so, then copy that STGMEDIUM to pSTM and
	// AddRef ourselves for pUnkForRelease.
		if (pFE -> cfFormat == (*it).m_fe.cfFormat
		    && (pFE -> tymed & (*it).m_fe.tymed)
		    && (pFE -> dwAspect == (*it).m_fe.dwAspect))
		{
			*pSTM = (*it).m_stm;
			
		// InterfacePointer richten (für ReleaseStgMedium)
			switch (pSTM -> tymed) {
			case TYMED_ISTREAM:
				pSTM -> pstm -> AddRef();
				break;

			case TYMED_ISTORAGE:
				pSTM -> pstg -> AddRef();
				break;

			default:
				break;
			}
			AddRef();
			return NOERROR;
		}
	}

return ResultFromScode (DATA_E_FORMATETC);
}


/*
 * CImpIDataObject::GetDataHere
 *
 * Purpose:
 *  Copies a piece of data in this data object to another
 *  STGMEDIUM.  This is only supported for TYMED_ISTORAGE.
 *
 * Parameters:
 *  pFE             LPFORMATETC describing the desired data.
 *  pSTM            LPSTGMEDIUM pointing to the medium into which
 *                  we copy.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */
STDMETHODIMP CImpIDataObject::GetDataHere (LPFORMATETC pFE, LPSTGMEDIUM pSTM)
{
	if (NULL == pFE || NULL == pSTM)
		return ResultFromScode (DATA_E_FORMATETC);

 // We only support IStorage
	if (!(TYMED_ISTORAGE & pFE -> tymed))
		return ResultFromScode (DATA_E_FORMATETC);

CRenderData::iterator it = m_pObj -> m_DataList.begin();

	for (/**/; it != m_pObj -> m_DataList.end(); it++) {
	// When we find a matching FORMATETC, we know we're only
	// looking for IStorage (we checked above), so use
	// IStorage::CopyTo to make the copy.
		if (pFE -> cfFormat == (*it).m_fe.cfFormat
		    && (pFE -> tymed & (*it).m_fe.tymed)
		    && (pFE -> dwAspect == (*it).m_fe.dwAspect))
		{
			pSTM -> tymed = TYMED_ISTORAGE;
			return (*it).m_stm.pstg -> CopyTo (NULL, NULL, NULL, pSTM -> pstg);
		}
	}

return ResultFromScode (DATA_E_FORMATETC);
}


/*
 * CImpIDataObject::QueryGetData
 *
 * Purpose:
 *  Tests if a call to GetData with this FormatEtc will provide
 *  any rendering; used like IsClipboardFormatAvailable.
 *
 * Parameters:
 *  pFE             LPFORMATETC describing the desired data.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */
STDMETHODIMP CImpIDataObject::QueryGetData (LPFORMATETC pFE)
{
	if (NULL == pFE) return ResultFromScode (S_FALSE);

CRenderData::iterator it = m_pObj -> m_DataList.begin();

	for (/**/; it != m_pObj -> m_DataList.end(); it++) {
	// Check if the requested FORMATETC is the same as one that we
	// already have.
		if (pFE -> cfFormat == (*it).m_fe.cfFormat
		    && (pFE -> tymed & (*it).m_fe.tymed)
		    && (pFE -> dwAspect == (*it).m_fe.dwAspect))
		{
			return NOERROR;
		}
	}

return ResultFromScode (S_FALSE);
}


/*
 * CImpIDataObject::SetData
 *
 * Purpose:
 *  Places data described by a FormatEtc and living in a StgMedium
 *  into the object.  The object may be responsible to clean up the
 *  StgMedium before exiting.
 *
 * Parameters:
 *  pFE             LPFORMATETC describing the data to set.
 *  pSTM            LPSTGMEDIUM containing the data.
 *  fRelease        BOOL indicating if this function is responsible
 *                  for freeing the data.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::SetData (LPFORMATETC pFE, STGMEDIUM *pSTM, bool fRelease)
{
 // We have to remain responsible for the data.
	if (!fRelease)
		return ResultFromScode (E_FAIL);

 // If we're handed NULLs, that means clean out the list.
	if (NULL == pFE || NULL == pSTM) {
		m_pObj -> m_DataList.erase();
		return NOERROR;
	}

// Here we take the rendering we're given and attach it to the end of the
// list.  We save the original pSTM->pUnkForRelease and replace it with our
// own such that each 'copy' of this data is actually just a reference count.
	try {
	CRendering *prn = new CRendering (*pFE, *pSTM, pSTM -> pUnkForRelease, this);

		if (NULL == prn) 
			return ResultFromScode (E_OUTOFMEMORY);
		m_pObj -> m_DataList.push_back(*prn);
	} catch (...) {
		TX_ASSERT(false);
		return ResultFromScode (E_OUTOFMEMORY);
	}

return NOERROR;
}




/*
 * CImpIDataObject::EnumFormatEtc
 *
 * Purpose:
 *  Returns an IEnumFORMATETC object through which the caller can
 *  iterate to learn about all the data formats this object can
 *  provide through either GetData[Here] or SetData.
 *
 * Parameters:
 *  dwDir           DWORD describing a data direction, either
 *                  DATADIR_SET or DATADIR_GET.
 *  ppEnum          LPENUMFORMATETC FAR * in which to return the
 *                  pointer to the enumerator.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::EnumFormatEtc (DWORD dwDir, LPENUMFORMATETC FAR * ppEnum)
{
CEnumFormatEtc *pEnum = NULL;

	*ppEnum = NULL;

// From an external point of view there are no SET formats, because we want to
// allow the user of this component object to be able to stuff ANY format in
// via Set.  Only external users will call EnumFormatEtc and they can only Get. 
	try {
		switch (dwDir) {
		case DATADIR_GET:
			pEnum = CEnumFormatEtc::CreateInstance (m_pObj -> m_DataList);
			break;

		case DATADIR_SET:
		default:
			pEnum = NULL;
			break;
		}
		if (NULL == pEnum)
			return ResultFromScode (E_FAIL);
	} catch (...) {
		TX_ASSERT(false);
		return ResultFromScode (E_FAIL);
	}

HRESULT hr = pEnum -> QueryInterface (IID_IEnumFORMATETC, (LPVOID *)ppEnum);
	
	pEnum -> Release();

return hr;
}


/*
 * CImpIDataObject::GetCanonicalFormatEtc
 * CImpIDataObject::DAdvise
 * CImpIDataObject::DUnadvise
 * CImpIDataObject::EnumDAdvise
 *
 * Trivial member functions.
 */

STDMETHODIMP CImpIDataObject::GetCanonicalFormatEtc (LPFORMATETC pFEIn, LPFORMATETC pFEOut) 
{
	return ResultFromScode (DATA_S_SAMEFORMATETC);
}

STDMETHODIMP CImpIDataObject::DAdvise (LPFORMATETC pFE, DWORD dwFlags, 
				       LPADVISESINK pIAdviseSink, LPDWORD pdwConn)
{
	return ResultFromScode (E_FAIL);
}

STDMETHODIMP CImpIDataObject::DUnadvise (DWORD dwConn)
{
	return ResultFromScode (E_FAIL);
}

STDMETHODIMP CImpIDataObject::EnumDAdvise (LPENUMSTATDATA *ppEnum)
{
	return ResultFromScode (E_FAIL);
}
