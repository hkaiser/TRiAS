// SpatialTree.h : Declaration of the CSpatialTree

#ifndef _SPATIALTREE
#define _SPATIALTREE

#include "resource.h"       // main symbols
#include "SpatialTreeQuery.h"
#include "raumguid.h"
#include "EnumUnknown.h"
#include "Hilfsfunktionen.h"

/////////////////////////////////////////////////////////////////////////////
// Raumzugriff

class DimensionMapEntry{
public:
    DISPID  m_nmin;
    DISPID  m_nmax;
    VARTYPE m_ncomptype;

    DimensionMapEntry(){m_nmin=0;m_nmax=0;m_ncomptype=VT_EMPTY;};
    DimensionMapEntry(DISPID amin,DISPID amax,VARTYPE acomptype);
};

DefineSmartInterface(Dispatch); // zu speichernde zeiger

//DefineSmartInterface(Unknown);  // zu speichernde SideInterfaces

class Objectentry{
public:
#ifdef _DEBUG
    char            m_a,m_b,m_c,m_d;    // Typ des Objektes
#endif

    WDispatch  m_Interface;
    ULONG      m_ID;
  
    Objectentry() {
#ifdef _DEBUG
    m_a = 'O';
    m_b = 'B';
    m_c = 'J';
    m_d = 'E';    // Typ des Objektes
#endif
//        TRACE("Objekteintrag::Constructor\n");
    }
    
    Objectentry(IDispatch* a_pInterface,ULONG a_ID)
        {
    #ifdef _DEBUG
        m_a = 'O';
        m_b = 'B';
        m_c = 'J';
        m_d = 'E';    // Typ des Objektes
    #endif

        m_Interface=a_pInterface;
        m_ID=a_ID;}

    ~Objectentry(){
        TRACE("Objekteintrag::Destructor\n");}
};

bool operator<(const Objectentry& x, const Objectentry& y);

class CSpatialTree;

// neu ab 2.7. 
class Objectentry_pless : public os_less<Objectentry*>
{
public:
    bool operator()( const Objectentry* x, const Objectentry* y ) const
      {
        // Input testen
        ASSERT(x);
        ASSERT(y);
        if (NULL == x)
            return TRUE;
        if (NULL == y)
            return FALSE;
        // eigentlichen Vergleich 
        // Einordnung anhand der ID_s
        return x->m_ID < y->m_ID;
      }
};

#define MAXBUCKETENTRIES 16
#define MAXBUCKETINDEX   MAXBUCKETENTRIES-1
//bool operator<(const Objectentry& x, const Objectentry& y);

class CKnoten;
typedef deque<Objectentry*> OBJLISTE;


class CKnoten{
public:
//    CKnoten() const = 0;
//    ~CKnoten() const = 0;
#ifdef _DEBUG
    char            m_a,m_b,m_c,m_d;    // Typ des Objektes
#endif

    virtual HRESULT Insert(Objectentry* pobj) {return E_NOTIMPL;};
    virtual HRESULT Delete(Objectentry* pobj,CKnoten* pcaller) {return E_NOTIMPL;};
    virtual HRESULT WriteToList(OBJLISTE& objlst) {return E_NOTIMPL;};
    virtual bool    IsLeaf() {return FALSE;};
    virtual HRESULT Getmin(CComVariant& aktmin,long disc){return E_NOTIMPL;};
    virtual HRESULT Getmax(CComVariant& aktmax,long disc){return E_NOTIMPL;};
    virtual HRESULT UpdateSon(CKnoten* alt,CKnoten* neu) {return E_NOTIMPL;};
    virtual HRESULT Intersection(	
            ISpatialTreeQuery*      pIQuestion,
            ISpatialTreeCallback*   pICallback,
            CEnumUnknown*           pReturn){return E_NOTIMPL;};
    virtual HRESULT Containment(	
            ISpatialTreeQuery*      pIQuestion,
            ISpatialTreeCallback*   pICallback,
            CEnumUnknown*           pReturn){return E_NOTIMPL;};
    virtual HRESULT Test()
    {return E_NOTIMPL;}
};  // end of CNode declaration


class CLeafnode:CKnoten
{
private:
    Objectentry*    m_vecpObj[MAXBUCKETENTRIES];
    long            m_nFill;
    CSpatialTree*   m_pSpatialTree;
public:
    CLeafnode(CSpatialTree* pSpatialTree);
    ~CLeafnode();
    virtual HRESULT Insert(Objectentry* pobj);
    virtual HRESULT Delete(Objectentry* pobj,CKnoten* pcaller);
    virtual HRESULT WriteToList(OBJLISTE& objlst);
    virtual bool    IsLeaf();
    virtual HRESULT Getmin(CComVariant& aktmin,long disc);
    virtual HRESULT Getmax(CComVariant& aktmax,long disc);
    virtual HRESULT UpdateSon(CKnoten* alt,CKnoten* neu);
    virtual HRESULT Intersection(	
            ISpatialTreeQuery*      pIQuestion,
            ISpatialTreeCallback*   pICallback,
            CEnumUnknown*           pReturn);
    virtual HRESULT Containment(	
            ISpatialTreeQuery*      pIQuestion,
            ISpatialTreeCallback*   pICallback,
            CEnumUnknown*           pReturn);
    virtual HRESULT Test()
    {
#ifdef _DEBUG
        ASSERT(m_nFill<=MAXBUCKETENTRIES);
//        ASSERT(m_nFill>MAXBUCKETENTRIES / 2);
        ASSERT(m_pSpatialTree);
#endif
        return S_OK;
    }

}; // end of CLeafnode declaration

class CInternalnode:CKnoten
{
private:
    CKnoten*        m_pHison;   // Zeiger zu größeren Werten 
    CKnoten*        m_pLoson;   // Zeiger zu kleineren Werten
    long            m_ndisc;    // nach welcher Dimension wird unterschieden
    CComVariant     m_discvalue;// entsprechender Wert 
    CComVariant     m_maxLoson; // Grenzen des überlappenden Bereiches
    CComVariant     m_minLoson; 
    CComVariant     m_maxHison;
    CComVariant     m_minHison; 
    
    CSpatialTree*   m_pSpatialTree;// zu welchem Baum gehöre ich (Dimensionsvector)

    HRESULT split(bool bHison);
    void Sort(OBJLISTE& templist);
    HRESULT Merge(bool bHison,CKnoten* pCaller);

public:
    CInternalnode(CSpatialTree* pSpatialTree);
    CInternalnode(CKnoten* loson,
              CKnoten* hison,
              long newDisc,
              CComVariant& newDiscval,
              CComVariant& newminhison,
              CComVariant& newmaxloson,
              CSpatialTree* pSpatialTree);
    CInternalnode(OBJLISTE& objlst,long dimension,CSpatialTree* pSpatialTree);
    ~CInternalnode();
    virtual HRESULT Insert(Objectentry* pobj);
    virtual HRESULT Delete(Objectentry* pobj,CKnoten* pcaller);
    virtual HRESULT WriteToList(OBJLISTE& objlst);
    virtual bool    IsLeaf();
    virtual HRESULT Getmin(CComVariant& aktmin,long disc);
    virtual HRESULT Getmax(CComVariant& aktmax,long disc);
    virtual HRESULT UpdateSon(CKnoten* alt,CKnoten* neu);
    virtual HRESULT Intersection(	
            ISpatialTreeQuery*      pIQuestion,
            ISpatialTreeCallback*   pICallback,
            CEnumUnknown*           pReturn);
    virtual HRESULT Containment(	
            ISpatialTreeQuery*      pIQuestion,
            ISpatialTreeCallback*   pICallback,
            CEnumUnknown*           pReturn);
    virtual HRESULT Test()
    {
#ifdef _DEBUG
        ASSERT(m_pHison);
        ASSERT(m_pLoson);
        ASSERT(m_pSpatialTree);
        HRESULT hr = m_pLoson->Test();
        if (FAILED(hr))
            return hr;
        hr = m_pHison->Test();
        if (FAILED(hr))
            return hr;
#endif
        return S_OK;
    }
}; // end of CInternalnode declaration
    
class CRootnode:CKnoten
{
private:
    CKnoten*        m_pSon;
    CSpatialTree*   m_pSpatialTree;
public:
    CRootnode(CSpatialTree* pSpatialTree);
    CRootnode(OBJLISTE& objlst,long dimension,CSpatialTree* pSpatialTree);
    ~CRootnode();
    virtual HRESULT Insert(Objectentry* pobj);
    virtual HRESULT Delete(Objectentry* pobj,CKnoten* pcaller);
    virtual HRESULT WriteToList(OBJLISTE& objlst);
    virtual bool    IsLeaf();
    virtual HRESULT Getmin(CComVariant& aktmin,long disc);
    virtual HRESULT Getmax(CComVariant& aktmax,long disc);
    virtual HRESULT UpdateSon(CKnoten* alt,CKnoten* neu);
    virtual HRESULT Intersection(	
            ISpatialTreeQuery*      pIQuestion,
            ISpatialTreeCallback*   pICallback,
            CEnumUnknown*           pReturn);
    virtual HRESULT Containment(	
            ISpatialTreeQuery*      pIQuestion,
            ISpatialTreeCallback*   pICallback,
            CEnumUnknown*           pReturn);
    virtual HRESULT Optimize();
    virtual HRESULT Test()
    {
#ifdef _DEBUG
        ASSERT(m_pSon);
        ASSERT(m_pSpatialTree);
        return  m_pSon->Test();
#endif
        return S_OK;
    }

}; // end of CRootnode declaration

   
class CSpatialTree : 
    public CComDualImpl<ISpatialTreeInit, &IID_ISpatialTreeInit, &LIBID_RAUMZUGRIFFLib>,
    public CComDualImpl<ISpatialTree, &IID_ISpatialTree, &LIBID_RAUMZUGRIFFLib>, 
	public CComDualImpl<IPersistStream, &IID_IPersistStream, &LIBID_RAUMZUGRIFFLib>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CSpatialTree,&CLSID_CSpatialTree>
{
public:
	CSpatialTree();
    ~CSpatialTree();
    HRESULT GetValues(
            IDispatch* pInterface,CComVariant& amin,CComVariant& amax,int i);
    bool    findIdinList(list<Objectentry*>& liste,list<Objectentry*>::iterator& i,ULONG id);
    bool    IntersectDim(IDispatch* pInterface,ISpatialTreeQuery* pIQuestion,ULONG dim);
    bool    Intersect(IDispatch* pInterface,ISpatialTreeQuery* pIQuestion);
    bool    ContainedDim(IDispatch* pInterface,ISpatialTreeQuery* pIQuestion,ULONG dim);
    bool    Contained(IDispatch* pInterface,ISpatialTreeQuery* pIQuestion);

BEGIN_COM_MAP(CSpatialTree)
	COM_INTERFACE_ENTRY2(IDispatch, ISpatialTree)
	COM_INTERFACE_ENTRY(ISpatialTreeInit)
    COM_INTERFACE_ENTRY(ISpatialTree)
	COM_INTERFACE_ENTRY(IPersistStream)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(CSpatialTree) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation.  The default is to support it

DECLARE_REGISTRY_RESOURCEID(IDR_TREEREG)

// DECLARE_REGISTRY(CSpatialTree, _T("Raumzugriff.SpatialTree.1"), _T("Raumzugriff.SpatialTree"), IDS_SPATIALTREE_DESC, THREADFLAGS_BOTH)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(
            REFIID riid);

// ISpatialTreeInit
    STDMETHOD(put_AddDimension)(
            DISPID  amin,
            DISPID  amax,
            VARTYPE comptype,
            int*    pIndex);

    STDMETHOD(put_SiteInterface)
        (IUnknown *pSiteInterface);

// ISpatialTree
    // basics
	STDMETHOD(Insert)(
            IDispatch* pnewObj,
            ULONG ObjNr);

    STDMETHOD(DeletebyNr)(
            ULONG ObjNr);

	//	statistics
	STDMETHOD(get_Count)(
            ULONG* pCount);

    STDMETHOD(get_Container)(
            ISpatialTreeQuery** ppIQuestion);

    STDMETHOD(get_Dimension)(
            ULONG* pDim);

    STDMETHOD(get_DimensionIDs)(
            ULONG       Dim,
            DISPID*     pmin,
            DISPID*     pmax,
            VARTYPE*    pcomptype);

    STDMETHOD(Optimize)(void);
        //	question
	STDMETHOD(Intersection)(
            ISpatialTreeQuery*      pIQuestion,
            ISpatialTreeCallback*   pICallback,
            IEnumUnknown**          ppReturn);

    STDMETHOD(Containment)(
            ISpatialTreeQuery*      pIQuestion,
            ISpatialTreeCallback*   pICallback,
            IEnumUnknown**          ppReturn);

// IPersistStream
    STDMETHOD(GetClassID)(
            struct _GUID *);

    STDMETHOD(IsDirty)(
            void);

    STDMETHOD(Load)(
            IStream     *pStm);

    STDMETHOD(Save)(
            IStream     *pStm,
            BOOL        fClearDirty);

    STDMETHOD(GetSizeMax)(
            ULARGE_INTEGER *pcbSize);

public:
  vector <DimensionMapEntry>    m_vecDimensionMap;
  CRootnode                     m_treeRoot;
  set<Objectentry*,
      Objectentry_pless>        m_treeID;
/*  list<Objectentry*>            m_treeID;*/
  int                           m_nDimension;
  WUnknown                      m_ISiteInterface;
//  CComObject<CSpatialTreeQuery> m_clContainer;
};


// für Vergleiche anhand der dimension
class LessObjOnDim
{
public:
    long m_dim;
    CSpatialTree* m_pSpatialTree;

    LessObjOnDim(long dim,CSpatialTree* pSpatialTree)
    {
        m_dim = dim;
        ASSERT(pSpatialTree);
        m_pSpatialTree = pSpatialTree;
    }

    bool operator()(Objectentry* x,Objectentry* y) const 
    {
//        return x->m_ID < y->m_ID;
        CComVariant xmin,xmax,xcent,ymin,ymax,ycent;
        
        ASSERT(m_pSpatialTree);
        if (NULL == m_pSpatialTree) 
            return TRUE;
        m_pSpatialTree->GetValues(x->m_Interface,xmin,xmax,m_dim);
        calculatecenter(xcent,xmin,xmax);
        m_pSpatialTree->GetValues(y->m_Interface,ymin,ymax,m_dim);
        calculatecenter(ycent,ymin,ymax);

        
        return xcent < ycent;
    }
};


#endif