/////////////////////////////////////////////////////////////////////////////
// DObjectProperty wrapper class

DefineSmartInterface2(DObjectProperty, IID_DObjectProperty);

class COleObjectPropertyDual :
	public IObjectProperty2,
	public CComDualImpl<DSearchObjects, &IID_DSearchObjects, &LIBID_TRiAS, 
				TYPELIB_VERSION_MAJOR, TYPELIB_VERSION_MINOR>, 
	public CComObjectRoot
{
public:
	COleObjectPropertyDual();
	~COleObjectPropertyDual();

// dieses Objekt ist gleichzeitig Objekteigenschaft selbst
	static HRESULT WINAPI _ChoiceWritable (void *pThis, REFIID iid, void **ppvObject, DWORD dw);
	static HRESULT WINAPI _ChoiceSearchable (void *pThis, REFIID iid, void **ppvObject, DWORD dw);

	BEGIN_COM_MAP(COleObjectPropertyDual)
		COM_INTERFACE_ENTRY(IObjectProperty)
		COM_INTERFACE_ENTRY_FUNC(IID_IObjectProperty2, 
					offsetofclass(IObjectProperty2, _ComMapClass),
					_ChoiceWritable)
		COM_INTERFACE_ENTRY_FUNC(IID_IObjectProperty2, 
					offsetofclass(IObjectProperty2, _ComMapClass),
					_ChoiceSearchable)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(COleObjectPropertyDual)

	HRESULT FInit (DObjectProperty *pIObjProp);
	HRESULT InitDocumentDispatch (void);
	HRESULT ConvertResultString (CComVariant &vValue, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);

// Attributes
public:

// Operations
public:
// *** IObjectProperty2 methods
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx);
	STDMETHOD(Reset) (THIS);
	STDMETHOD(Eval)(THIS_ LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD(Set)(THIS_ LONG lONr, LPCSTR pcBuffer);

	HRESULT Init (DApplication *pIApp, BOOL *pfSuccess);

// DSearchObjects
	STDMETHOD(ConsiderSearch) (BSTR bstrToMatch, SEARCHMODE rgFlags, ULONG ulCnt);
	STDMETHOD(SearchObjects) (BSTR bstrToMatch, SEARCHMODE rgFlags, IEnumObjectsByNumber **ppvObj);

private:
// DispatchID's 
	CGeoDoc *m_pDoc;
	WDObjectProperty m_ObjProp;
	bool m_fWriteAble;
	bool m_fSearchAble;
};

