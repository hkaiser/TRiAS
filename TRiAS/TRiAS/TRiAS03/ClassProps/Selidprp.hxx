// ActionProperty, welche Ident/Objekttypen auswählt und zusammenstellt -------
// File: SELIDPRP.HXX

#if !defined(_SELIDPRP_HXX)
#define _SELIDPRP_HXX

#include <propactn.h>
#include <selidprp.h>

#include "propactb.hxx"		// CPropertyAction
#include "selident.hxx"		// CSelectIdentDlg

class CSelIDPropAct : 
	public CPropertyAction,
	public CComObjectBase<&CLSID_SelectIdentObjTyp>
{
private:
	CSelectIdentDlg *m_pCfgDlg;

	bool m_fIsDirty;		// DirtyFlag
	bool m_fIsInitialized;	// ist fertig initialisiert

public:
	BEGIN_COM_MAP(CSelIDPropAct)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersist)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CSelIDPropAct)

		CSelIDPropAct (void);
		~CSelIDPropAct (void);

static HRESULT CreateInstance (IClassProperty **ppIClsProp)
	{ return _CreatorClass::CreateInstance(NULL, IID_IClassProperty, (LPVOID *)ppIClsProp); }

// IClassProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile, ULONG *pulHelpCtx);

// IPropertyAction methods
	STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
				LPARAM lParam, DWORD dwFlags, LPCSTR pcDesc, UINT *puiCnt);
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

#endif // _SELIDPRP_HXX
