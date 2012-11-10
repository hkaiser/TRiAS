// TextSearchEngine.h : Declaration of the CTextSearchEngine

#include "propactb.hxx"
#include "txtsrchd.h"

class CTextSearchEngine : 
	public CPropertyActionExt,
	public CComObjectRoot,
	public CComCoClass<CTextSearchEngine, &CLSID_TextSearchEngine>
{
public:
		CTextSearchEngine();
		~CTextSearchEngine();

	BEGIN_COM_MAP(CTextSearchEngine)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStream)
		COM_INTERFACE_ENTRY(IPropertyInfo)
	END_COM_MAP()

	DECLARE_AGGREGATABLE(CTextSearchEngine)
	DECLARE_STATIC_REGISTRY_RESOURCEID(IDR_TEXTSEARCHENGINE)

public:
	void SetDirty (bool fFlag = true);

public:
// IPropertyAction methods
	STDMETHOD (AddConfigPages) (LPFNADDPROPSHEETPAGE lpfnAddPage, 
								LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt);
	STDMETHOD (PreConfigPages) (IDataObject *pIDataObject, DWORD dwFlags);
	STDMETHOD (BeginAction) (THIS_ IProgressIndicator *pIProgInd);
	STDMETHOD (DoAction) (IDataObject *pEnumObj, DWORD dwReserved);
	STDMETHOD (EndAction) (DWORD dwReserved, IDataObject **ppEnumObj);

// IClassProperty specific functions
	STDMETHOD(GetPropInfo) (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(HelpInfo) (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx);

// IPropertyInfo specific functions 
	STDMETHOD(SetPropInfo) (THIS_ LPCSTR pBuffer, DWORD dwFlags);

// IPersist methods
	STDMETHOD(GetClassID) (CLSID *pClsID);

// IPersistStreamInit methods
	STDMETHOD(IsDirty)(void);
	STDMETHOD(Load)(LPSTREAM pStm);
	STDMETHOD(Save)(LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER FAR* pcbSize);
	STDMETHOD(InitNew)(void);

private:
	bool m_fIsDirty;
	bool m_fIsInitialized;
	string m_strDesc;

	CCfgTextSearch *m_pCfgDlg;
	CCfgTextSearch::CDlgStatus m_Status;
};

