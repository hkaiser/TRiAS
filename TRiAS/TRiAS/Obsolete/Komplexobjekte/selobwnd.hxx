// PropertyAction, welche Objekte aus RechercheFenster auswählt und zusammenstellt
// File: SELOBWND.HXX

#if !defined(_SELOBWND_HXX)
#define _SELOBWND_HXX

#include <propactn.h>
#include <selobwnd.h>

#include "propactb.hxx"
#include "clspropb.hxx"

class CSelObjWndPropAct : public CClassProperty {
private:
	class CImpPropAct : public CPropertyAction {
	private:
		class CSelectObjWndDlg *m_pCfgDlg;
		LPCLASSPROPERTY m_pIClsProp;

	public:
			CImpPropAct (LPUNKNOWN pIUnk, IClassProperty *pIProp);
			~CImpPropAct (void);

	// *** IPropertyAction methods
		STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
					    LPARAM lParam, DWORD dwFlags, UINT *puiCnt);
		STDMETHOD (BeginAction) (THIS_ IProgressIndicator *pIProgInd);
		STDMETHOD (DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
		STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

	friend class CSelObjWndPropAct;
	};
	CImpPropAct m_PropAct;

protected:
		CSelObjWndPropAct (void);

	bool FInit (void);

public:
		~CSelObjWndPropAct (void);

static CSelObjWndPropAct *CreateInstance (void);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);

// *** IClassProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(Reset)(THIS);
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile, ULONG *pulHelpCtx);
};

#endif // _SELOBWND_HXX
