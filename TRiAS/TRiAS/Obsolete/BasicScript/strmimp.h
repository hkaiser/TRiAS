/*
 * IPERSTRM.H
 *
 * Definitions of a template IPersistStream interface
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


#ifndef _IPERSTRM_H_
#define _IPERSTRM_H_

#undef FARCLASS
#ifdef WIN32
#define FARCLASS
#else
#define FARCLASS  __far
#endif

class CBScriptDebug;
class FARCLASS CImpIPersistStorage;    
class CMacroScripts;
class CMacro;
class FARCLASS CImpIPersistStream;
typedef class CImpIPersistStream *LPCIMPIPERSISTSTREAM;

class FARCLASS CImpIPersistStream : public IPersistStream
{
private:
	bool m_fIsDirty;
	char *m_pText;                             
	int m_iLen;
	ebHCODE m_hCode;

	HRESULT LoadScript_FromDB (LPSTREAM pIStream, ebFILEHEADER &rHead);
	HRESULT LoadCode_FromDB (LPSTREAM pIStream, ebFILEHEADER &rHead);
	HRESULT SaveScript_InDB (LPSTREAM pIStream, DWORD dwFlag);
                                                                  
protected:
    ULONG           m_cRef;      //Interface reference count
    LPUNKNOWN       m_pUnkOuter; //For delegation
	CMacro 		*m_pMacro;

public:       
	CImpIPersistStream(LPUNKNOWN pUnkOuter, CMacro *pMacro);
	~CImpIPersistStream(void);

	HRESULT LoadHeader (LPSTREAM pIStream, ebFILEHEADER *pHeader);

	HRESULT GetCode(ebHCODE *phCode);
	HRESULT SetCode (ebHCODE hCode);

	void SetDirty (bool fDirty) { if (fDirty) m_fIsDirty = TRUE;
					else m_fIsDirty = TRUE;}					
	HRESULT SetScriptText (char *pText);
	HRESULT GetScriptText (LPSTR *ppText);

    STDMETHODIMP QueryInterface(REFIID, LPVOID FAR *);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

    STDMETHODIMP GetClassID(LPCLSID);

    STDMETHODIMP IsDirty(void);
    STDMETHODIMP Load(LPSTREAM);
    STDMETHODIMP Save(LPSTREAM, BOOL);
    STDMETHODIMP GetSizeMax(ULARGE_INTEGER FAR *);

};


#endif  //_IPERSTRM_H_

