/*
 * IPERSTOR.H
 *
 * Definitions of a template IPersistStorage interface
 * implementation.
 *
 * Copyright (c)1993-1994 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Software Design Engineer
 * Microsoft Systems Developer Relations
 *
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IPERSTOR_H_
#define _IPERSTOR_H_

#undef FARCLASS
#ifdef WIN32
#define FARCLASS
#else
#define FARCLASS  __far
#endif

#ifndef _PSSTATE
typedef enum {
	PSSTATE_UNINIT,
	PSSTATE_WRITE,
	PSSTATE_ZOMBIE,
	PSSTATE_HANDSOFF
} PSSTATE;
#define _PSSTATE
#endif

class CBScriptDebug;
class FARCLASS CImpIPersistStorage;    
class CMacroScripts;
class CMacro;

typedef class CImpIPersistStorage *LPCIMPIPERSISTSTORAGE;

class FARCLASS CImpIPersistStorage : public IPersistStorage
{           
private:                                        
	HRESULT LoadStream (LPSTORAGE pIStorage, char *pMacroName);
protected:
#if defined(_DEBUG)
	ULONG           m_cRef;      //Interface reference count
#endif // _DEBUG

	LPVOID          m_pObj;      //Back pointer to the object
	LPUNKNOWN       m_pUnkOuter; //For delegation
	LPSTORAGE 	m_pISubStorage;
	CMacroScripts   *m_pMacroScripts;

	bool m_fIsDirty;
	short m_iState;
		
public:
	HRESULT EnumElements(LPSTORAGE pIStorage);
	HRESULT GetStorage (LPSTORAGE *ppIStorage);

	CImpIPersistStorage(LPUNKNOWN pUnkOuter, CMacroScripts *pMacroScripts);
    ~CImpIPersistStorage(void);

	STDMETHODIMP QueryInterface(REFIID, LPVOID FAR *);
	STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

    STDMETHODIMP GetClassID(LPCLSID);

    STDMETHODIMP IsDirty(void);
    STDMETHODIMP InitNew(LPSTORAGE);
    STDMETHODIMP Load(LPSTORAGE);
    STDMETHODIMP Save(LPSTORAGE, BOOL);
    STDMETHODIMP SaveCompleted(LPSTORAGE);
    STDMETHODIMP HandsOffStorage(void);

};


#endif  //_IPERSTOR_H_
