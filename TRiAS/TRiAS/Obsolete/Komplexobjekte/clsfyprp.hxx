// PropertyAction für Classifikation nach Objekteigenschaft -------------------
// File: CLSFYPRP.HXX

#if !defined(_CLSFYPRP_HXX)
#define _CLSFYPRP_HXX

#include <propactn.h>
#include <clsfyprp.h>

#include "propactb.hxx"
#include "clspropb.hxx"

class CClsfyPropAct : public CClassProperty {
private:
	class CImpPropAct : public CPropertyAction {
	private:
		class CClassifyDlg *m_pCfgDlg;
		IClassProperty *m_pIClsProp;
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

	friend class CClsfyPropAct;
	};
	CImpPropAct m_PropAct;

protected:
		CClsfyPropAct (ITriasXtensionSite *pIXtnSite);

	bool FInit (void);

public:
		~CClsfyPropAct (void);

static CClsfyPropAct *CreateInstance (ITriasXtensionSite *pIXtnSite);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);

// *** IClassProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(Reset)(THIS);
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile, ULONG *pulHelpCtx);
};

#endif // _CLSFYPRP_HXX
