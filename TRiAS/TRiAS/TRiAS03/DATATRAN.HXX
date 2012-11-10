/*
 * DATATRAN.HXX
 * Data Transfer Object
 *
 * Definitions, classes, and prototypes for a DLL that provides
 * data transfer objects.
 *
 * Copyright (c)1993 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Software Design Engineer
 * Microsoft Systems Developer Relations
 *
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _DATATRAN_HXX_
#define _DATATRAN_HXX_


//DATATRAN.CXX
void FAR PASCAL ObjectDestroyed(void);


//This class factory object creates Data Transfer Objects.

class __far CDataTransferClassFactory : public IClassFactory
    {
    protected:
        ULONG           m_cRef;

    public:
        CDataTransferClassFactory(void);
        ~CDataTransferClassFactory(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, LPLPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IClassFactory members
        STDMETHODIMP         CreateInstance(LPUNKNOWN, REFIID
                                 , LPLPVOID);
        STDMETHODIMP         LockServer(BOOL);
    };

typedef CDataTransferClassFactory FAR *LPCDataTransferClassFactory;

#endif //_DATATRAN_HXX_
