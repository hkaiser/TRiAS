// PropertyAction, welche Textobjekte mit Objekteigenschaft erzeugt
// File: TXTOBPRP.HXX

#if !defined(_TXTOBPRP_HXX)
#define _TXTOBPRP_HXX

#include <propactn.h>
#include <TxtObPrp.h>

#include "propactb.hxx"		// CPropertyAction
#include "CreaText.hxx"		// CCreateTextObjectsDlg

class CCreateTextObjectsPropAct : 
	public CPropertyAction,
	public CComObjectRoot,
	public CComCoClass<CCreateTextObjectsPropAct, &CLSID_CreateTextObjects>
{
private:
	CCreateTextObjectsDlg *m_pCfgDlg;
	string m_strDesc;

	bool m_fIsDirty;			// DirtyFlag
	bool m_fIsInitialized;		// ist fertig initialisiert
	bool m_fHasInitData;

	os_string m_strObjProp;		// Resultate
	bool m_fCreateDependend;
	bool m_fDeleteExistent;
	bool m_fDoNotMove;

public:
	BEGIN_COM_MAP(CCreateTextObjectsPropAct)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersist)
		COM_INTERFACE_ENTRY(IPropertyInfo)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CCreateTextObjectsPropAct)		// class factory
	DECLARE_STATIC_REGISTRY_RESOURCEID(IDR_PROPINFO_CREATETEXT_RGS)

		CCreateTextObjectsPropAct (void);
		~CCreateTextObjectsPropAct (void);

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

// sonstiges
	void SetDirty (bool fDirty = true);
};

#endif // _TXTOBPRP_HXX
