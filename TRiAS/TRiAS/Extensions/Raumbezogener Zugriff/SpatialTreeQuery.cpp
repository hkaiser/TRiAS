// SpatialTreeQuery.cpp : Implementation of CRaumzugriffApp and DLL registration.

#include "stdafx.h"
#include "Raumzugriff.h"

#include "SpatialTreeQuery.h"
#include "Hilfsfunktionen.h"
/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP CSpatialTreeQuery::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISpatialTreeQuery,
		&IID_IPersistStream,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSpatialTreeQuery::AddDim(
            VARIANT amin,
            VARIANT amax,
            VARTYPE vt)
        {
//            TRACE("Entering CSpatialTreeQuery::AddDim\n");
            
            if (AcceptVartype(vt))
            {
                m_vecMinValues.push_back(amin);
                m_vecMinValues[m_nDim].ChangeType(vt);
                m_vecMaxValues.push_back(amax);
                m_vecMaxValues[m_nDim].ChangeType(vt);
                m_vecVartypes.push_back(vt);
                m_nDim++;
                TRACE("CSpatialTreeQuery::AddDim Added %d.Dimension\n",m_nDim);
                return S_OK;
            }
            else 
            {
                TRACE("** CSpatialTreeQuery::Adddim ** <Invalid Argument 'vt'> **\n");
                return E_INVALIDARG;
            }
        }



STDMETHODIMP CSpatialTreeQuery::SetBorder(
            ULONG dim,
            VARIANT amin,
            VARIANT amax)
        {   
//            TRACE("Entering CSpatialTreeQuery::SetBorder\n");
            
            if ((dim<m_nDim)&&(dim>=0)&&AcceptVartype(amin.vt)&&AcceptVartype(amax.vt))
            {
                m_vecMinValues[dim]=amin;
                m_vecMinValues[dim].ChangeType(m_vecVartypes[dim]);
                m_vecMaxValues[dim]=amax;
                m_vecMaxValues[dim].ChangeType(m_vecVartypes[dim]);
                return S_OK;
            }
            else 
            {
                TRACE("** CSpatialTreeQuery::SetBorder ** <Invalid Argument> **\n");
                return E_INVALIDARG;
            }
        }

STDMETHODIMP CSpatialTreeQuery::GetBorder(
            ULONG dim,
            VARIANT* pmin,
            VARIANT* pmax)
        {   
//            TRACE("Entering CSpatialTreeQuery::GetBorder\n");

            ASSERT(pmin);
            if (NULL==pmin)
                return E_POINTER;
            ASSERT(pmax);
            if (NULL==pmax)
                return E_POINTER;

            if ((dim<m_nDim)&&(dim>=0))
            {
                *pmin=m_vecMinValues[dim];
                *pmax=m_vecMaxValues[dim];

                return S_OK;
            }
            else
            {
                TRACE("** CSpatialTreeQuery::GetBorder ** <Invalid Argument 'dim'> **\n");
                return E_INVALIDARG;
            }
        }

