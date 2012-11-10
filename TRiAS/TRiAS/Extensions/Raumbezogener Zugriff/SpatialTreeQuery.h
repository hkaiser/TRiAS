// SpatialTreeQuery.h : Declaration of the CSpatialTreeQuery

#ifndef _SPATIALTREEQUERY
#define _SPATIALTREEQUERY

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// Raumzugriff

class CSpatialTreeQuery : 
	public CComDualImpl<ISpatialTreeQuery, &IID_ISpatialTreeQuery, &LIBID_RAUMZUGRIFFLib>, 
	public CComDualImpl<IPersistStream, &IID_IPersistStream, &LIBID_RAUMZUGRIFFLib>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CSpatialTreeQuery,&CLSID_CSpatialTreeQuery>
{
public:
	CSpatialTreeQuery(){
        TRACE("CSpatialTreeQuery::Constructor\n");
        m_nDim=0;}
    ~CSpatialTreeQuery() {TRACE("CSpatialTreeQuery::Destructor\n");}
BEGIN_COM_MAP(CSpatialTreeQuery)
	COM_INTERFACE_ENTRY2(IDispatch, ISpatialTreeQuery)
	COM_INTERFACE_ENTRY(ISpatialTreeQuery)
	COM_INTERFACE_ENTRY(IPersistStream)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(CSpatialTreeQuery) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation.  The default is to support it

DECLARE_REGISTRY_RESOURCEID(IDR_QUESTION)
// DECLARE_REGISTRY(CSpatialTreeQuery, _T("Raumzugriff.SpatialTreeQuery.1"), _T("Raumzugriff.SpatialTreeQuery"), IDS_SPATIALTREEQUERY_DESC, THREADFLAGS_BOTH)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(
            REFIID riid);

// ISpatialTreeQuery
	//	Dimension
    STDMETHOD(SetBorder)(
            ULONG dim,
            VARIANT amin,
            VARIANT amax);
 
    STDMETHOD(GetBorder)(
            ULONG dim,
            VARIANT* pmin,
            VARIANT* pmax);

// IPersistStream
    STDMETHOD(GetClassID)(
            struct _GUID *)
        {   TRACE("Entering CSpatialTreeQuestion::GetClassID");
            return E_NOTIMPL;}

    STDMETHOD(IsDirty)(
            void)
        {   TRACE("Entering CSpatialTreeQuestion::IsDirty");
            return E_NOTIMPL;}

    STDMETHOD(Load)(
            IStream     *pStm)
        {   TRACE("Entering CSpatialTreeQuestion::Load");
            return E_NOTIMPL;}

    STDMETHOD(Save)(
            IStream     *pStm,
            BOOL        fClearDirty)
        {   TRACE("Entering CSpatialTreeQuestion::Save");
            return E_NOTIMPL;}

    STDMETHOD(GetSizeMax)(
            ULARGE_INTEGER *pcbSize)
        {   TRACE("Entering CSpatialTreeQuestion::GetSizeMax");
            return E_NOTIMPL;}

    STDMETHOD(AddDim)(
            VARIANT amin,VARIANT amax,VARTYPE vt);

public:
    int m_nDim;
    vector <CComVariant>  m_vecMinValues,m_vecMaxValues;
    vector <VARTYPE>      m_vecVartypes;
};

#endif