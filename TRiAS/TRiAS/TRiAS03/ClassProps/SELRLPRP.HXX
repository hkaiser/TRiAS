// ActionProperty, welche Ident/Objekttypen auswählt und zusammenstellt -------
// File: SELRLPRP.HXX

#if !defined(_SELRLPRP_HXX)
#define _SELRLPRP_HXX

#include <propactn.h>
#include <selrlprp.h>

#include "propactb.hxx"
#include "clspropb.hxx"

class CGenKomplexObj : public CClassProperty {
private:
	class CImpPropAct : public CPropertyAction {
	private:
		class CSelectRCodeDlg *m_pCfgDlg;
		LPCLASSPROPERTY m_pIClsProp;
		WTriasXtensionSite m_XtnSite;

	public:
			CImpPropAct (LPUNKNOWN pIUnk, IClassProperty *pIProp,
				     ITriasXtensionSite *pIXtnSite);
			~CImpPropAct (void);

	// *** IPropertyAction methods
		STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
					    LPARAM lParam, DWORD dwFlags, UINT *puiCnt);
		STDMETHOD (BeginAction) (THIS_ IProgressIndicator *pIProgInd);
		STDMETHOD (DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
		STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

	friend class CGenKomplexObj;
	};
	CImpPropAct m_PropAct;

protected:
		CGenKomplexObj (ITriasXtensionSite *pIXtnSite);

	bool FInit (void);

public:
		~CGenKomplexObj (void);

static CGenKomplexObj *CreateInstance (ITriasXtensionSite *pIXtnSite);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);

// *** IClassProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(Reset)(THIS);
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile, ULONG *pulHelpCtx);
};

#endif // _SELRLPRP_HXX
