// PropertyAction, welche Objekte aus RechercheFenster auswählt und zusammenstellt
// File: DSTOBWND.HXX

#if !defined(_DSTOBWND_HXX)
#define _DSTOBWND_HXX

#include <propactn.h>
#include <dstobwnd.h>

#include "propactb.hxx"
#include "clspropb.hxx"

class CDestObjWndPropAct : public CClassProperty {
private:
	class CImpPropAct : public CPropertyAction {
	private:
		class CDestObjWndDlg *m_pCfgDlg;
		IClassProperty *m_pIClsProp;

	public:
			CImpPropAct (LPUNKNOWN pIUnk, IClassProperty *pIProp);
			~CImpPropAct (void);

	// *** IPropertyAction methods
		STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
					    LPARAM lParam, DWORD dwFlags, UINT *puiCnt);
		STDMETHOD (BeginAction) (THIS_ IProgressIndicator *pIProgInd);
		STDMETHOD (DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
		STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

	friend class CDestObjWndPropAct;
	};
	CImpPropAct m_PropAct;

protected:
		CDestObjWndPropAct (void);

	bool FInit (void);

public:
		~CDestObjWndPropAct (void);

static CDestObjWndPropAct *CreateInstance (void);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);

// *** IClassProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(Reset)(THIS);
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile, ULONG *pulHelpCtx);
};

#endif // _DSTOBWND_HXX
