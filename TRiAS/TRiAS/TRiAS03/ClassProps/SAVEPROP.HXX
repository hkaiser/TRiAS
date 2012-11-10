// ActionProperty, alle verschiedenen Werte einer Objekteigenschaft zusammenstellt 
// File: SAVEPROP.HXX

#if !defined(_SAVEPROP_HXX)
#define _SAVEPROP_HXX

#include <propactn.h>
#include <selrlprp.h>

#include "propactb.hxx"
#include "clspropb.hxx"

class CSavePropValue : public CClassProperty {
private:
	class CImpPropAct : public CPropertyAction {
	private:
		LPCLASSPROPERTY m_pIClsProp;
		WTriasXtensionSite m_XtnSite;
		os_string m_strResult;

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

	friend class CSavePropValue;
	};
	CImpPropAct m_PropAct;

protected:
		CSavePropValue (ITriasXtensionSite *pIXtnSite);

	bool FInit (void);

public:
		~CSavePropValue (void);

static CSavePropValue *CreateInstance (ITriasXtensionSite *pIXtnSite);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);

// *** IClassProperty specific functions ***
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(Reset)(THIS);
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
			    LPSTR pHelpFile, ULONG *pulHelpCtx);
};

#endif // _SAVEPROP_HXX
