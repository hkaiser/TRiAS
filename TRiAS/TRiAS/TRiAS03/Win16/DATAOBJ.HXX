/*
 * DATAOBJ.H
 * Data Transfer Object Chapter 7
 *
 * Copyright (c)1993 Microsoft Corporation, All Right Reserved
 *
 * Kraig Brockschmidt, Software Design Engineer
 * Microsoft Systems Developer Relations
 *
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _DATAOBJ_HXX_
#define _DATAOBJ_HXX_

#if !defined(_LPFNDESTROY_DEFINED)
#define _LPFNDESTROY_DEFINED
// Type for an object-destroyed callback
typedef void (FAR PASCAL *LPFNDESTROYED)(void);
#endif // _LPFNDESTROY_DEFINED

/*
 * Structure to describe a specific rendering that our user wants
 * us to maintain.
 */

typedef struct __far tagRENDERING
    {
    FORMATETC       fe;             //The format
    STGMEDIUM       stm;            //The actual data
    LPUNKNOWN       pUnkOrg;        //The real owner
    } RENDERING, FAR *LPRENDERING;



/*
 * The DataObject object is implemented in its own class with its
 * own IUnknown to support aggregation.  It contains one
 * CImpIDataObject object that we use to implement the externally
 * exposed interfaces.
 */

//DATAOBJ.CXX

class __far CImpIDataObject;
typedef class CImpIDataObject FAR *LPIMPIDATAOBJECT;

class __far CDataObject : public IUnknown
    {
    friend class CImpIDataObject;

    protected:
        ULONG               m_cRef;
        LPUNKNOWN           m_pUnkOuter;
        LPFNDESTROYED       m_pfnDestroy;

        HWND                m_hList;        //Listbox of RENDERINGs

        //Contained interface implemetation
        LPIMPIDATAOBJECT    m_pIDataObject;

    public:
        CDataObject(LPUNKNOWN, LPFNDESTROYED);
        ~CDataObject(void);

        BOOL FInit(void);
        void Purge(void);

        //Non-delegating object IUnknown
        STDMETHODIMP         QueryInterface(REFIID, LPLPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);
    };

typedef CDataObject FAR *LPCDataObject;



/*
 * Interface implementations for the CDataObject object.
 */

class __far CImpIDataObject : public IDataObject
    {
    private:
        ULONG           m_cRef;
        LPCDataObject   m_pObj;
        LPUNKNOWN       m_pUnkOuter;

    public:
        CImpIDataObject(LPCDataObject, LPUNKNOWN);
        ~CImpIDataObject(void);

        //IUnknown members that delegate to m_pUnkOuter.
        STDMETHODIMP         QueryInterface(REFIID, LPLPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IDataObject members
        STDMETHODIMP GetData(LPFORMATETC, LPSTGMEDIUM);
        STDMETHODIMP GetDataHere(LPFORMATETC, LPSTGMEDIUM);
        STDMETHODIMP QueryGetData(LPFORMATETC);
        STDMETHODIMP GetCanonicalFormatEtc(LPFORMATETC, LPFORMATETC);
        STDMETHODIMP SetData(LPFORMATETC, STGMEDIUM FAR *, BOOL);
        STDMETHODIMP EnumFormatEtc(DWORD, LPENUMFORMATETC FAR *);
        STDMETHODIMP DAdvise(FORMATETC FAR *, DWORD
            ,  LPADVISESINK, DWORD FAR *);
        STDMETHODIMP DUnadvise(DWORD);
        STDMETHODIMP EnumDAdvise(LPENUMSTATDATA FAR *);
    };


class __far CEnumFormatEtc : public IEnumFORMATETC
    {
    private:
        ULONG           m_cRef;
        LPUNKNOWN       m_pUnkRef;
        LPFORMATETC     m_prgfe;
        ULONG           m_iCur;
        ULONG           m_cItems;

    public:
        CEnumFormatEtc(LPUNKNOWN);
        ~CEnumFormatEtc(void);

        BOOL FInit(HWND);

        //IUnknown members that delegate to m_pUnkOuter.
        STDMETHODIMP         QueryInterface(REFIID, LPLPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IEnumFORMATETC members
        STDMETHODIMP Next(ULONG, LPFORMATETC, ULONG FAR *);
        STDMETHODIMP Skip(ULONG);
        STDMETHODIMP Reset(void);
        STDMETHODIMP Clone(IEnumFORMATETC FAR * FAR *);
    };


typedef CEnumFormatEtc FAR *LPCEnumFormatEtc;

#endif //_DATAOBJ_HXX_
