// Basisklasse für IPropertyAction 
// File: PropActBase.h

#if !defined(_PROPACTBASE_H)
#define _PROPACTBASE_H

///////////////////////////////////////////////////////////////////////////////
// CPropertyActionBase immer nur als Basisklasse für die konkrete Implementation
// eines PropertyAction-Objektes verwenden.
// 
// Die benötigten Funktionen müssen überladen werden, alle nicht überladenen
// Funktionen liefern E_NOTIMPL. Funktionen, die überladen werden müssen,
// sind hier noch PURE (= 0).

class CPropertyActionBase : 
	public IPropertyAction2,
	public IClassProperty,
	public IPropertyInfo,
	public IPersistStreamInit
{
protected:
		CPropertyActionBase() {}	// nur als Basisklasse verwenden
		~CPropertyActionBase() {}

public:
// IPropertyAction methods
	STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
				    LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt);
	STDMETHOD (PreConfigPages) (THIS_ IDataObject *pIDataObject, DWORD dwFlags);
	STDMETHOD (BeginAction) (THIS_ IProgressIndicator *pIProgInd);
	STDMETHOD (DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
	STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

// *** IPropertyAction2 methods
	STDMETHOD (InitFromData) (THIS_ IDataObject *pIDO, BOOL fCreate, DWORD dwReserved);

// IClassProperty specific functions
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags) PURE;
	STDMETHOD(Reset)(THIS);
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
						LPSTR pHelpFile, ULONG *pulHelpCtx);
	STDMETHOD(Eval)(THIS_ IEnumLONG *pEnumObj, LPSTR pBuffer, 
					ULONG ulLen, ULONG *pulWritten);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);

// IPropertyInfo specific functions 
	STDMETHOD(SetPropName) (THIS_ LPCSTR pBuffer) PURE;
	STDMETHOD(SetHelpInfo) (THIS_ LPCSTR pBuffer, LPCSTR pHelpFile, ULONG ulHelpCtx);

// IPersist methods
	STDMETHOD(GetClassID) (THIS_ CLSID *pClsID) PURE;

// IPersistStreamInit methods
	STDMETHOD(IsDirty)(THIS) PURE;
	STDMETHOD(Load)(THIS_ LPSTREAM pStm);
	STDMETHOD(Save)(THIS_ LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER FAR* pcbSize);
	STDMETHOD(InitNew)(THIS) PURE;
};

#endif // _PROPACTBASE_H
