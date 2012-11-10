#ifndef _EXPALL_H
#define _EXPALL_H

DefineSmartInterface(ObjectManagement);

class CExportImportProject : 
	public CMacroFileScript2,
	public IExportImportProject,
	public CComObjectRoot,
	public CComCoClass<CExportImportProject, &CLSID_ExportImportProject>
{
public:
	CExportImportProject();
	~CExportImportProject();

	BEGIN_COM_MAP(CExportImportProject)
		COM_INTERFACE_ENTRY(IPersistFile)
		COM_INTERFACE_ENTRY(IScriptProperty)
		COM_INTERFACE_ENTRY(IExportImportProject)
	END_COM_MAP()

	// *** IPersistFile
	STDMETHOD(Save)				(LPCOLESTR pszFileName, BOOL fRemember);        
	STDMETHOD(Load)				(LPCOLESTR pszFileName, DWORD dwMode);        
	// *** IPersist-Method ***
	STDMETHOD(GetClassID)(LPCLSID pClsID) { *pClsID = CLSID_ExportImportProject; return S_OK; } 
	// *** IExportImportProject
	STDMETHOD_(void, SetManagement)	(IObjectManagement*);
	STDMETHOD(GetTexts)(LPSTR **lplplpstrRelTexts, UINT & uiTexts);

	DECLARE_REGISTRY_RESOURCEID(IDR_EXPORTIMPORTSCRIPT_REG)
	
private:
	WObjectManagement m_IObjectManagement;

protected:
	HRESULT SaveAll (LPCOLESTR pszFileName, BOOL fRemember);
	HRESULT SaveSubs (HANDLE fh);
	HRESULT SaveSuper (HANDLE fh);
	HRESULT SaveText(HANDLE fh, LPCSTR lpcstrText);
	HRESULT SaveEnd (HANDLE fh);

	HRESULT LoadTextOnly(LPSTR *lplpstrText, HANDLE fh);
	HRESULT LoadAll	(LPCOLESTR pszFileName, DWORD dwMode);
	HRESULT LoadSuper(LPCSTR lpcstrText, LPSTR *lplpstrNext);
	HRESULT LoadWholeText(LPCSTR lpcstrText);
	HRESULT LoadSubs(LPSTR lpstrText);
	HRESULT LoadSub(LPSTR lpstrNext, LPSTR *lplpstrNextNext);

	HRESULT WriteSplitBetweenFiles(HANDLE fh, LPCSTR lpcstrFileName);
	int FindStringPosition(LPCSTR lpcstrText, LPCSTR lpcstrSub, LPSTR *lplpstrNext);
	HRESULT GetSubTexts(LPSTR **lplplpstrRelTexts, UINT & uiTexts);

	HRESULT WriteBeginLabel(HANDLE fh);
	HRESULT ReadBeginLabel(LPSTR, LPSTR*);
	HRESULT Compile	(LPCSTR, ebHCODE *phCode);
	HRESULT SaveCodeOnly(HANDLE fh);
	HRESULT SaveCode(HANDLE fh, ebHCODE hCode);
	HRESULT SaveHeader(HANDLE fh, ebFILEHEADER & rHead, ebHCODE hCode);

	list<os_string> m_listRelatedTexts;
};

#endif //_EXPALL_H