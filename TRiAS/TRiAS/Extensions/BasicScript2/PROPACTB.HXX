// Basisklasse für IPropertyAction --------------------------------------------
// File: PROPACTB.HXX

#if !defined(_PROPACTB_HXX)
#define _PROPACTB_HXX

/////////////////////////////////////////////////////////////////////////////
// Überladen der InitNew-Funktion, um zu verhindern, daß diese Funktion mit
// IPersistStreamInit::InitNew zusammenfällt

class XPersistPropertyBag :
	public IPersistPropertyBag
{
public:
	STDMETHOD(InitNew)(THIS) { return PersistPropertyBag_InitNew(); }
	STDMETHOD(PersistPropertyBag_InitNew)(THIS) PURE;
};

///////////////////////////////////////////////////////////////////////////////
// CPropertyAction immer nur als Basisklasse für die konkrete Implementation
// eines PropertyAction-Objektes verwenden.
// 
// Die benötigten Funktionen müssen überladen werden, alle nicht überladenen
// Funktionen liefern E_NOTIMPL. Funktionen, die überladen werden müssen,
// sind hier noch PURE (= 0).
class CPropertyAction : 
	public IPropertyAction2,
//	public IPropertyAction,
	public IClassProperty,
	public IPropertyInfo,
	public IPersistStreamInit,
	public XPersistPropertyBag
{
protected:
		CPropertyAction() : m_fNoShow (false) {}	// nur als Basisklasse verwenden
		~CPropertyAction() {}

	HRESULT InitFromDataFormatETC (IDataObject *pIDO, const FORMATETC *pcfmt);

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
	STDMETHOD(SetPropInfo) (THIS_ LPCSTR pBuffer, DWORD dwFlags) PURE;
	STDMETHOD(SetHelpInfo) (THIS_ LPCSTR pBuffer, LPCSTR pHelpFile, ULONG ulHelpCtx);

// IPersist methods
	STDMETHOD(GetClassID) (THIS_ CLSID *pClsID) PURE;

// IPersistStreamInit methods
	STDMETHOD(IsDirty)(THIS) PURE;
	STDMETHOD(Load)(THIS_ LPSTREAM pStm);
	STDMETHOD(Save)(THIS_ LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER FAR* pcbSize);
	STDMETHOD(InitNew)(THIS) PURE;

// IPersistPropertyBag
	STDMETHOD(Load)(THIS_ IPropertyBag *pBag, IErrorLog *pLog);
	STDMETHOD(Save)(THIS_ IPropertyBag *pBag, BOOL fClearDirty, BOOL fSaveAllProperties);
	STDMETHOD(PersistPropertyBag_InitNew)(THIS);

// diverse ZugriffsFunmktionen
	IUnknown *GetUnknown() { return (IPropertyAction *)this; }
	bool IsNoShow() { return m_fNoShow; }

protected:
	bool m_fNoShow;
};

///////////////////////////////////////////////////////////////////////////////
// Versionskontrolle
#define PROPACTB_VERSION_1_0_0	0x00000001
#define PROPACTB_ACTVERSION		PROPACTB_VERSION_1_0_0

#endif // _PROPACTB_HXX
