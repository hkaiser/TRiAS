#ifndef _MACRO_H
#define _MACRO_H

//////////////////////////////////////////////////////////////////////////////////////////
// Dient zum Speichern

class CMacroScript2 :
	public IPersistStream,
	public IScriptProperty,
	public IPersistStreamInit
{
protected:
	DWORD m_dwSaveFlag;
	BOOL m_fIsDirty;

	LPSTR m_pText;
	ebHCODE m_hCode;
	CString m_strScriptName;

	list<os_string> m_listRelatedScripts;

public:
	CString	GetScriptName(void) { return m_strScriptName; }

private:
	HRESULT	SetNameFromStream(LPSTREAM lpIStr);
	HRESULT LoadText(LPSTREAM pIStream, ebFILEHEADER & Header);
	HRESULT LoadCode(LPSTREAM pIStream, ebFILEHEADER & Header);
	HRESULT LoadAll (LPSTREAM pIStream, ebFILEHEADER & Header);
	HRESULT LoadHeader (LPSTREAM pIStream, ebFILEHEADER *pHeader);
	HRESULT SaveAll (LPSTREAM pIStream);
	HRESULT WriteRelatedScripts(LPSTREAM pIStream);
	HRESULT WriteRelatedScriptsOnly(LPSTREAM pIStream);
	HRESULT LoadRelatedScripts(LPSTREAM pIStream);
	UINT	RelScriptsCount(void);
	HRESULT CreateStream(LPSTORAGE lpIStorage, BSTR bstr, LPSTREAM *ppIStream);

	HRESULT SetRelatedOnly (LPSAVESTRUCT pSS);
	HRESULT SetCode (LPSAVESTRUCT pSS);
	HRESULT SetText (LPSAVESTRUCT pSS);
	HRESULT SetRelated (LPSAVESTRUCT pSS);
	HRESULT SetProperties (LPSAVESTRUCT pSS);

public:
	   	CMacroScript2(void);
   		~CMacroScript2(void);

	// IPersistStream
    STDMETHOD(IsDirty)(void);
    STDMETHOD(Load)(LPSTREAM);
    STDMETHOD(Save)(LPSTREAM, BOOL);
    STDMETHOD(GetSizeMax)(ULARGE_INTEGER FAR *);
// IPersistStreamInit
	STDMETHOD(InitNew)(void);
// IScriptProperty
	STDMETHOD(Set)(LPSAVESTRUCT);
	STDMETHOD(Get)(LPSAVESTRUCT);
};

class CMacroScript :
	public CMacroScript2,
	public CComObjectRoot,
	public CComCoClass<CMacroScript, &CLSID_Script>
{
public:
	CMacroScript() {}

	BEGIN_COM_MAP(CMacroScript)
		COM_INTERFACE_ENTRY(IPersistStream)
		COM_INTERFACE_ENTRY(IScriptProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
	END_COM_MAP()

	static HRESULT CreateInstance(IScriptProperty **pp)
		{ return _CreatorClass::CreateInstance(NULL, IID_IScriptProperty, (LPVOID *)pp); }

	DECLARE_REGISTRY_RESOURCEID(IDR_SCRIPT_REG)

	// *** IPersist-Method ***
	STDMETHOD(GetClassID)(LPCLSID pClsID); 
};

class CMacroFileScript2 :
	public IScriptProperty,
	public IPersistFile
{
protected:
	HANDLE		m_fhOpenFile;

	DWORD m_dwSaveFlag;
	BOOL m_fIsDirty;

	int	m_iState;

	LPSTR m_pText;
	ebHCODE m_hCode;
	CString		m_strScriptName;
	BOOL	m_fLoadWithHeader;

	list<os_string> m_listRelatedScripts;

public:
	CString	GetScriptName(void) { return m_strScriptName; }

protected:
	HRESULT SetNameFromFile		(LPCSTR);
	HRESULT	SaveTextOnly		(HANDLE fh);
	HRESULT GetFileHandle		(LPCOLESTR lpcolestr , BOOL fRemember, HANDLE *pfh);
	HRESULT CreateFile			(LPCOLESTR pszFileName, DWORD dwStrMode,HANDLE *pfh);
	UINT	RelScriptsCount		(void);
	HRESULT SaveAll				(HANDLE fh);
	HRESULT SaveCode			(HANDLE fh, ebFILEHEADER & rHead);
	HRESULT SaveText			(HANDLE fh, ebFILEHEADER & rHead);
	HRESULT SaveHeader			(HANDLE fh, ebFILEHEADER & rHead);
	HRESULT WriteRelatedScripts	(HANDLE fh, ebFILEHEADER & rHead);
	HRESULT WriteRelatedScriptsOnly(HANDLE fh);

	HRESULT LoadAll				(HANDLE fh, ebFILEHEADER & rH);
	HRESULT LoadText			(HANDLE fh, ebFILEHEADER & Header);
	HRESULT LoadCode			(HANDLE fh, ebFILEHEADER & Header);
	HRESULT LoadHeader			(HANDLE fh, ebFILEHEADER *pHeader);
	HRESULT LoadRelatedScripts	(HANDLE fh, ebFILEHEADER & Header);
	HRESULT LoadTextOnly		(HANDLE fh);
	
	HRESULT MapCreateFileModes	(DWORD dwMode, DWORD *pdwMode);
	HRESULT IsEmptyFile			(HANDLE fh);
	HRESULT CreateSaveFile		(LPCOLESTR pszFileName, HANDLE *pfh);

	HRESULT SetRelatedOnly		(LPSAVESTRUCT pSS);
	HRESULT SetCode				(LPSAVESTRUCT pSS);
	HRESULT SetText				(LPSAVESTRUCT pSS);
	HRESULT SetRelated			(LPSAVESTRUCT pSS);
	HRESULT SetProperties		(LPSAVESTRUCT pSS);


public:
	   	CMacroFileScript2(void);
   		~CMacroFileScript2(void);

// IPersistFile
	STDMETHOD(Load)				(LPCOLESTR pszFileName, DWORD dwMode);        
	STDMETHOD(Save)				(LPCOLESTR pszFileName, BOOL fRemember);        
	STDMETHOD(SaveCompleted)	(LPCOLESTR pszFileName);        
	STDMETHOD(GetCurFile)		(LPOLESTR __RPC_FAR *ppszFileName);
    STDMETHOD(IsDirty)			(void);
// IScriptProperty
	STDMETHOD(Set)(LPSAVESTRUCT);
	STDMETHOD(Get)(LPSAVESTRUCT);
};

#endif // _MACRO_H


class CMacroFileScript :
	public CMacroFileScript2,
	public CComObjectRoot,
	public CComCoClass<CMacroFileScript, &CLSID_FileScript>
{
public:
	CMacroFileScript() {}

	BEGIN_COM_MAP(CMacroFileScript)
		COM_INTERFACE_ENTRY(IScriptProperty)
		COM_INTERFACE_ENTRY(IPersistFile)
	END_COM_MAP()

	static HRESULT CreateInstance(IScriptProperty **pp)
		{ return _CreatorClass::CreateInstance(NULL, IID_IScriptProperty, (LPVOID *)pp); }

	DECLARE_REGISTRY_RESOURCEID(IDR_FILESCIPT_REG)

	// *** IPersist-Method ***
	STDMETHOD(GetClassID)(LPCLSID pClsID); 
};
