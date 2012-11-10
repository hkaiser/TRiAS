#ifndef _MACRO_H
#define _MACRO_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation der Klasse, die STORAGE widerspiegelt
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CBScriptDebug;

class CMacroScripts : public IUnknown
{
protected:
	ULONG       m_cRef;      //Interface reference count
	LPUNKNOWN 	m_pIUnk;
	
private:
	bool FInit();		
	
	CebInstance *m_pebInst;

	CImpIPersistStorage *m_pIPersistStorage;
	LPCIMPMACROSCRIPT m_pIMacroScripts;
	CEnumMacroScripts *m_pEnumScripts;

public:
static  CMacroScripts* CreateScript (LPUNKNOWN pIUnk, CebInstance *pebInst);
		                               
	HRESULT GetEnum (CEnumMacroScripts **ppEnumScripts); 
    LPCIMPMACROSCRIPT GetIMacroScripts (void) { return m_pIMacroScripts; } 
    CImpIPersistStorage * GetIPersistStorage (void) { return m_pIPersistStorage; }
         
	CMacroScripts (LPUNKNOWN pIUnk, CebInstance *pebInst);
	~CMacroScripts();

	HRESULT AddScript (LPCSTR pName, CMacro *pM)
		{ return m_pEnumScripts -> AddScript (pName, pM); }

	CebInstance * GetebInst (void) { return m_pebInst; }

/* IUnknown methods */
	STDMETHOD(QueryInterface)(REFIID riid, void FAR* FAR* ppv);
	STDMETHOD_(unsigned long, AddRef)(void);
    STDMETHOD_(unsigned long, Release)(void);
};

                                 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation der Klasse, die STREAM widerspiegelt
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


class CMacro : public IUnknown
{
protected:
        ULONG           m_cRef;      // Interface reference count
        LPUNKNOWN 	m_pIUnk;

private:
	bool FInit(void);		

	DWORD m_dwSaveFlag;
	
	CImpIPersistStream *m_pIPersistStream;
	CIMacrosImp *m_pIMacro;
	
	CString m_strMacroName;
public:
    	CMacro (LPUNKNOWN pIUnk);
    	~CMacro();

static CMacro* Create (LPUNKNOWN pIUnk);

	CString GetName (void);
	void SetName ( CString strN );

	void SetCompiled (DWORD dwFlag) { m_dwSaveFlag = dwFlag; } 
	DWORD GetCompiled (void) { return m_dwSaveFlag; }
				  

    CImpIPersistStream *  GetIPersistStream (void) { return m_pIPersistStream; }
    CIMacrosImp * GetIMacros (void) { return m_pIMacro; } 
    	
/* IUnknown methods */
	STDMETHOD(QueryInterface)(REFIID riid, void FAR* FAR* ppv);
	STDMETHOD_(unsigned long, AddRef)(void);
    STDMETHOD_(unsigned long, Release)(void);
};

class CMacroHelper : public CObject 
{
private:
	CString m_strName;
	CMacro* m_pM;                                       
public:
		CMacroHelper (LPCSTR pcName, CMacro *pM) :
				m_strName (pcName) 
		{    
			m_pM = pM; 
			m_pM -> AddRef();  
		}
		~CMacroHelper (void) { m_pM -> Release(); }

	CMacro * GetMacro (void) { return m_pM; }
	operator const CMacro* (void) { return m_pM; }
	operator const char * (void) { return m_strName; }
};
 
#endif // _MACRO_H

