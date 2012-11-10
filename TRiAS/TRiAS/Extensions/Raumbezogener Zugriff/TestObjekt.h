// SpatialTreeQuery.h : Declaration of the CSpatialTreeQuery


#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// Raumzugriff

class CTestObjekt : 
	public CComDualImpl<ITestObjekt, &IID_ITestObjekt, &LIBID_RAUMZUGRIFFLib>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CTestObjekt,&CLSID_CTestObjekt>
{
public:
#ifdef _DEBUG
    char            m_a,m_b,m_c,m_d;    // Typ des Objektes
#endif

    CTestObjekt();
    ~CTestObjekt();
BEGIN_COM_MAP(CTestObjekt)
	COM_INTERFACE_ENTRY2(IDispatch, ITestObjekt)
	COM_INTERFACE_ENTRY(ITestObjekt)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(CSpatialTreeQuery) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation.  The default is to support it

DECLARE_REGISTRY_RESOURCEID(IDR_TESTOBJEKT)
// DECLARE_REGISTRY(CSpatialTreeQuery, _T("Raumzugriff.SpatialTreeQuery.1"), _T("Raumzugriff.SpatialTreeQuery"), IDS_SPATIALTREEQUERY_DESC, THREADFLAGS_BOTH)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(
            REFIID riid);

// ISpatialTreeQuery
	//	Dimension
    STDMETHOD(put_xmin)( 
            VARIANT min);
        
    STDMETHOD(put_xmax)( 
            VARIANT max);
        
    STDMETHOD(get_xmin)(
            VARIANT *pmin);
    
    STDMETHOD(get_xmax)(
            VARIANT *pmax);

public:
protected:
    CComVariant m_varclxmin;
    CComVariant m_varclxmax;
};
