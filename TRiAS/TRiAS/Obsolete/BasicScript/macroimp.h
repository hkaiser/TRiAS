#ifndef _MACROIMP_H
#define _MACROIMP_H

typedef class CIMacroScriptImp *LPCIMPMACROSCRIPT;

class CMacro;
class CMacroScripts;

class CIMacroScriptImp : public IScriptContainer
{
private:	
	bool FInit();		

	HRESULT FInitStorages(LPCSTR pPathName, LPSTORAGE pIRootStorage,LPSTORAGE *ppISubStorage);
	HRESULT SetData (LPSTR pText, ebHCODE hCode, DWORD dwSaveFlag, CMacro *pM);
	HRESULT GetData (LPSTR *ppcMacroText, ebHCODE *pebhCode, CMacro *pM);
	HRESULT	OpenOrCreateStream(const CString & strMacroName, LPSTREAM *ppIStream);	
	DWORD GetScriptInfo (ebFILEHEADER *pHead);

	int AskSaveChanges (void);
	HRESULT DestroyStorage();

	LPSTORAGE m_pIRootStorage;			
	bool m_fNotCommit;
	bool m_fNew;

	LPSTREAM m_pIStream;

protected:
    ULONG           m_cRef;      //Interface reference count
    LPUNKNOWN       m_pUnkOuter; //For delegation      
    CMacro  		*m_pMacro;         
    CMacroScripts 	*m_pMacroScripts;

public:
	static CIMacroScriptImp* Create(LPUNKNOWN pUnkOuter, CMacroScripts* pMacroScripts);
	
    CIMacroScriptImp(LPUNKNOWN pUnkOuter, CMacroScripts* pMacroScripts);
    ~CIMacroScriptImp();

// *** IMacroScript specific functions ***                          
	STDMETHOD_(HRESULT, InitStorages) (LPSTORAGE pIRootStor, LPCSTR pPath );
	STDMETHOD_(HRESULT, NewSubStorage) (LPSTORAGE pIRootStorage, LPSTORAGE *ppISubStorage);
	STDMETHOD_(HRESULT, Commit) (DWORD grfCommitFlags, bool fAsk) ;
	STDMETHOD_(HRESULT, IsDirty) (void) ;
	STDMETHOD_(HRESULT, SetNotCommit) (bool fNotCommit) ;
	STDMETHOD_(HRESULT, GetEnumScripts) (IEnumScripts **penum);
	STDMETHOD_(HRESULT, GetScriptInfo) (LPCSTR pcName, DWORD *pdwInfo); 
	STDMETHOD_(HRESULT, DelScript) (LPCSTR pcName);
	STDMETHOD_(HRESULT, CreateScript) (LPCSTR pc);
	STDMETHOD_(HRESULT, GetScript) (LPCSTR pc, LPSTR *ppMacroText, ebHCODE *pebhCode) ;
	STDMETHOD_(HRESULT, SetScript) (LPCSTR pcName, LPSTR pText, ebHCODE hCode, DWORD dwSaveFlag); 
	STDMETHOD(GetebInst) (CebInstance **ppInst);

	/* IUnknown methods */
	STDMETHOD(QueryInterface)(REFIID riid, void FAR* FAR* ppv);
	STDMETHOD_(unsigned long, AddRef)(void);
    STDMETHOD_(unsigned long, Release)(void);
};

typedef class CIMacrosImp *LPCIMPMACROS;

class CIMacrosImp : public IScript
{
private:
	bool FInit();		
	CMacro *m_pMacro;
	CString m_strName;
	bool m_fNew;
	bool m_fNotCommit;
	LPSTREAM m_pIStream;

protected:
	ULONG           m_cRef;      //Interface reference count
	LPUNKNOWN       m_pUnkOuter; //For delegation

public:
	static CIMacrosImp* Create(LPUNKNOWN pUnkOuter, CMacro *pMacro);
				
	CString GetName (void);
	bool GetNew (void);
	HRESULT SetNew (bool fNew);
	bool GetNotCommit (void);
	HRESULT SetNotCommit (bool fCommit);

    CIMacrosImp(LPUNKNOWN pUnkOuter, CMacro *pMacro);
    ~CIMacrosImp();

	/* IUnknown methods */
	STDMETHOD(QueryInterface)(REFIID riid, void FAR* FAR* ppv);
	STDMETHOD_(unsigned long, AddRef)(void);
    STDMETHOD_(unsigned long, Release)(void);

// *** IMacros specific functions ***
	STDMETHOD_(HRESULT, GetName) (THIS_ LPSTR pScName, ULONG ulSize);
	STDMETHOD_(HRESULT, SetName) (THIS_ LPCSTR pScName);
};

HRESULT MakeFileName(LPCSTR pPathName, LPSTR pNameToUse, LPCSTR pcFileExt);
HRESULT MakeRootStorage(LPSTORAGE *ppIStorage, LPCSTR pPathName);
HRESULT MakeSubStorage(LPSTORAGE pIRootStorage, LPSTORAGE *ppISubStorage,
						const CString &strStorName, 
						bool &fNew, bool fDirect, CLSID clsID);
HRESULT TestclsID (LPSTORAGE pIStorage, const CLSID &clsID);

#endif // _MACROIMP_H                   



