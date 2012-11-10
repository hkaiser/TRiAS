// PropertyAction, welche Objekte auf einen auszuwählenden Ident umklassifiziert
// File: MODIDPRP.HXX

#if !defined(_MODIDPRP_HXX)
#define _MODIDPRP_HXX

#include <propactn.h>
#include <modidprp.h>

#include "propactb.hxx"		// CPropertyAction
#include "modident.hxx"		// CModifyIdentDlg

class CModIDPropAct : 
	public CPropertyAction,
	public CComObjectBase<&CLSID_ModifyIdent>
{
private:
	CModifyIdentDlg *m_pCfgDlg;

	bool m_fIsDirty;		// DirtyFlag
	bool m_fIsInitialized;	// ist fertig initialisiert

public:
	BEGIN_COM_MAP(CModIDPropAct)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersist)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CModIDPropAct)		// class factory

		CModIDPropAct (void);
		~CModIDPropAct (void);

static HRESULT CreateInstance (IClassProperty **ppIClsProp)
	{ return _CreatorClass::CreateInstance(NULL, IID_IClassProperty, (LPVOID *)ppIClsProp); }

// IClassProperty specific functions 
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
					    LPSTR pHelpFile, ULONG *pulHelpCtx);

// IPropertyAction methods
	STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
				LPARAM lParam, DWORD dwFlags, LPCSTR pcDesc, UINT *puiCnt);
	STDMETHOD (DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
	STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

// IPersist methods
	STDMETHOD(GetClassID)(THIS_ LPCLSID lpClassID);

// IPersistStreamInit methods
	STDMETHOD(IsDirty)(THIS);
	STDMETHOD(Load)(THIS_ LPSTREAM pStm);
	STDMETHOD(Save)(THIS_ LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER FAR* pcbSize);
	STDMETHOD(InitNew)(THIS);
};

#endif // _MODIDPRP_HXX
