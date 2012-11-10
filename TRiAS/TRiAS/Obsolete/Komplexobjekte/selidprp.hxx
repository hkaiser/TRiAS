// ActionProperty, welche Ident/Objekttypen auswählt und zusammenstellt -------
// File: SELIDPRP.HXX

#if !defined(_SELIDPRP_HXX)
#define _SELIDPRP_HXX

#include <propactn.h>
#include <selidprp.h>

#include "propactb.hxx"
#include "clspropb.hxx"

class CSelIDPropAct : public CClassProperty {
private:
	class CImpPropAct : public CPropertyAction {
	private:
		class CSelectIdentDlg *m_pCfgDlg;
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

	friend class CSelIDPropAct;
	};
	CImpPropAct m_PropAct;

protected:
		CSelIDPropAct (void);

	bool FInit (void);

public:
		~CSelIDPropAct (void);

static CSelIDPropAct *CreateInstance (void);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);

// *** IClassProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(Reset)(THIS);
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile, ULONG *pulHelpCtx);
};

#endif // _SELIDPRP_HXX
