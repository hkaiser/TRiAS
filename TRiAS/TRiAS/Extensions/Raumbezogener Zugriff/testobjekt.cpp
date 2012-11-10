// TestObjekt.cpp : Implementation of CRaumzugriffApp and DLL registration.

#include "stdafx.h"
#include "Raumzugriff.h"
#include "TestObjekt.h"

/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP CTestObjekt::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITestObjekt,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

CTestObjekt::CTestObjekt() 
        :m_varclxmin((long)0,VT_I4),
        m_varclxmax((long)0,VT_I4)
{
#ifdef _DEBUG
    m_a = 'T';
    m_b = 'E';
    m_c = 'S';
    m_d = 'T';    // Typ des Objektes
#endif

//    TRACE("CTestObjekt Constructor\n");
}

CTestObjekt::~CTestObjekt()
{
//    TRACE("CTestObjekt Destructor\n");
}

STDMETHODIMP CTestObjekt::put_xmin( 
            VARIANT min){   
//    TRACE("Entering CTestObjekt::put_xmin\n");
    m_varclxmin=min;
    return S_OK;}
        
STDMETHODIMP CTestObjekt::put_xmax( 
        VARIANT max){   
//    TRACE("Entering CTestObjekt::put_xmax\n");
    m_varclxmax=max;
    return S_OK;}
    
STDMETHODIMP CTestObjekt::get_xmin(
        VARIANT *pmin){
//    TRACE("Entering CTestObjekt::get_xmin\n");
    *pmin=m_varclxmin;
    return S_OK;}

STDMETHODIMP CTestObjekt::get_xmax(
        VARIANT *pmax){
//    TRACE("Entering CTestObjekt::get_xmax\n");
    *pmax=m_varclxmax;
    return S_OK;}
