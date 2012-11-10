/*
 * DATAOBJ.CPP
 * Data Transfer Object Chapter 7
 *
 * Implementation of the CDataObject for the Data Transfer
 * Component Object.
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

extern LONG g_cObj;		// globaler ObjektZähler

/*
 * CDataObject::CDataObject
 * CDataObject::~CDataObject
 *
 * Parameters (Constructor):
 *  pUnkOuter       LPUNKNOWN of a controlling unknown.
 *  pfnDestroy      LPFNDESTROYED to call when object is destroyed.
 */

CDataObject::CDataObject (LPUNKNOWN pUnkOuter, LPFNDESTROYED pfnDestroy)
{
	m_cRef = 0;
	m_pUnkOuter = pUnkOuter;
	m_pfnDestroy = pfnDestroy;

	m_pIDataObject = NULL;
}


CDataObject::~CDataObject (void)
{
	if (NULL != m_pIDataObject)
		delete m_pIDataObject;

	Purge ();

	InterlockedDecrement (&g_cObj);		// ein Objekt weniger
}


/*
 * CDataObject::FInit
 *
 * Purpose:
 *  Performs any intiailization of a CDataObject that's prone to
 *  failure that we also use internally before exposing the object
 *  outside.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  bool            true if the function is successful,
 *                  false otherwise.
 */
bool CDataObject::FInit (void)
{
 // Allocate contained interfaces.
	m_pIDataObject = new CImpIDataObject (this, m_pUnkOuter ? m_pUnkOuter : this);
	if (NULL == m_pIDataObject) return false;

return true;
}


CDataObject *CDataObject::CreateInstance (LPUNKNOWN pUnkOuter, LPFNDESTROYED pfnDestroy)
{
	try {
	CDataObject *pDataObj = new CDataObject (pUnkOuter, pfnDestroy);

		if (NULL == pDataObj || !pDataObj -> FInit()) {
			DELETE(pDataObj);
			return NULL;
		}
		pDataObj -> AddRef();

		InterlockedIncrement (&g_cObj);		// ein Objekt mehr
		return pDataObj;
	} catch (...) {
		return NULL;
	}
}


/*
 * CDataObject::Purge
 *
 * Purpose:
 *  Cleans out all entries.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */
void CDataObject::Purge (void)
{
	for (CRenderData::iterator it = m_DataList.begin(); 
	     it != m_DataList.end(); it++) 
	{
	// Release the data completely being sure to reinstate the
	// original pUnkForRelease.
		(*it).m_stm.pUnkForRelease = (*it).m_UnkOrg;
		ReleaseStgMedium (&((*it).m_stm));
	}

	m_DataList.erase();
}


/*
 * CDataObject::QueryInterface
 * CDataObject::AddRef
 * CDataObject::Release
 *
 * Purpose:
 *  IUnknown members for CDataObject object.
 */

STDMETHODIMP CDataObject::QueryInterface (REFIID riid, LPVOID *ppv)
{
	*ppv = NULL;

	if (riid == IID_IUnknown)
		*ppv = (LPVOID) this;

	if (riid == IID_IDataObject)
		*ppv = (LPVOID) m_pIDataObject;

	if (NULL != *ppv) {
		LPUNKNOWN(*ppv)->AddRef ();
		return NOERROR;
	}

return ResultFromScode (E_NOINTERFACE);
}


STDMETHODIMP_ (ULONG) CDataObject::AddRef (void)
{
	return ++m_cRef;
}


STDMETHODIMP_ (ULONG) CDataObject::Release (void)
{
	TX_ASSERT(m_cRef > 0);

ULONG cRefT = --m_cRef;

	if (0L == m_cRef) {
		if (NULL != m_pfnDestroy)
			(*m_pfnDestroy)();
		delete this;
	}

return cRefT;
}
