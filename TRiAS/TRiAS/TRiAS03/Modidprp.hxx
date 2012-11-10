// PropertyAction, welche Objekte auf einen auszuwählenden Ident umklassifiziert
// File: MODIDPRP.HXX

#if !defined(_MODIDPRP_HXX)
#define _MODIDPRP_HXX

#include <propactn.h>
#include <modidprp.h>

#include "propactb.hxx"		// CPropertyAction
#include "modident.hxx"		// CModifyIdentDlg

class CModIDPropAct : 
	public CPropertyActionExt,	// JG
	public CComObjectRoot,
	public IObjectWithSiteImpl<CModIDPropAct>,
	public CComCoClass<CModIDPropAct, &CLSID_ModifyIdent>
{
private:
	CModifyIdentDlg *m_pCfgDlg;
	string m_strDesc;

	bool m_fIsDirty;		// DirtyFlag
	bool m_fIsInitialized;	// ist fertig initialisiert

	long m_lIdent;			// Resultate
	bool m_fAddToView;
	bool m_fShowConnections;
	bool m_fHasInitData;

	BOOL m_fCheckMode;
	BOOL m_fCheckModeChecked;
	long m_iCopyMode;

public:
	BEGIN_COM_MAP(CModIDPropAct)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IPropertyAction3)
		COM_INTERFACE_ENTRY(IPersistPropertyBag)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPropertyInfo)
		COM_INTERFACE_ENTRY(IObjectWithSite)
	END_COM_MAP()

	DECLARE_AGGREGATABLE(CModIDPropAct)		// class factory
	DECLARE_STATIC_REGISTRY_RESOURCEID(IDR_PROPINFO_MODIDENT)

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
				LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt);
	STDMETHOD (PreConfigPages) (THIS_ IDataObject *pIDataObject, DWORD dwFlags);

	STDMETHOD (DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
	STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

// IPropertyInfo specific functions 
	STDMETHOD(SetPropInfo) (THIS_ LPCSTR pBuffer, DWORD dwFlags);

// IPersist methods
	STDMETHOD(GetClassID)(THIS_ LPCLSID lpClassID);

// IPersistStreamInit methods
	STDMETHOD(IsDirty)(THIS);
	STDMETHOD(Load)(THIS_ LPSTREAM pStm);
	STDMETHOD(Save)(THIS_ LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER *pcbSize);
	STDMETHOD(InitNew)(THIS);

// IPersistPropertyBag
	STDMETHOD(Load)(THIS_ IPropertyBag *pBag, IErrorLog *pLog);

// sonstiges
	void SetDirty (bool fDirty = true);
	HRESULT ReInitFromData();
};

///////////////////////////////////////////////////////////////////////////////
// Versionen des PersistStream-Formates
const long MODIDPRP_SIGNATURE = 0x5052504d;		// "MPRP";
const long MODIDPRP_VERSION_MINOR_MASK = 0xff;
const long MODIDPRP_VERSION_100 = 0x0100L;
const long LASTKNOWN_MODIDPRP_VERSION = MODIDPRP_VERSION_100;

#endif // _MODIDPRP_HXX
