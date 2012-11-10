/////////////////////////////////////////////////////////////////////////////
// DObjectProperty wrapper class

#if !defined(_countof)
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif // !_countof

// Namen der DispFunktionen
const LPCOLESTR s_pcoleObjPropNames[] = 
{
	L"Cumulation", 
	L"Count", 
	L"PropertyName",
	L"PropertyFlags", 
	L"HelpInfo", 
	L"Reset",
	L"Eval", 
	L"SetValue",
	L"GetProperty",
	L"Init",
	L"SetProperty",
};

const LPCOLESTR s_pcoleAltObjPropNames[] = 
{
	L"DObjectProperty_Cumulation", 
	L"DObjectProperty_Count", 
	L"DObjectProperty_PropertyName",
	L"DObjectProperty_PropertyFlags", 
	L"DObjectProperty_HelpInfo", 
	L"DObjectProperty_Reset",
	L"DObjectProperty_Eval", 
	L"DObjectProperty_SetValue",
	L"DObjectProperty_GetProperty",
	L"DObjectProperty_Init",
	L"DWriteAbleObjectProperty_SetProperty",
};

#define DISPID_GETCUMULATION		0
#define DISPID_GETCOUNT				1
#define DISPID_GETPROPERTYNAME		2
#define DISPID_GETPROPERTYFLAGS		3
#define DISPID_HELPINFO				4
#define DISPID_RESET				5
#define DISPID_EVAL					6
#define DISPID_SET					7
#define DISPID_GETPROPERTY			8
#define DISPID_INIT					9
#define DISPID_SETPROPERTY			10

class COleObjectProperty :
	public IObjectProperty2,
	public COleDispatchDriver,
	public CComObjectRoot
{
public:
		COleObjectProperty();
		~COleObjectProperty();

// dieses Objekt ist gleichzeitig Objekteigenschaft selbst
	static HRESULT WINAPI _Choice (void *pThis, REFIID iid, void **ppvObject, DWORD dw);
	BEGIN_COM_MAP(COleObjectProperty)
		COM_INTERFACE_ENTRY(IObjectProperty)
		COM_INTERFACE_ENTRY_FUNC(IID_IObjectProperty2, 
					offsetofclass(IObjectProperty2, _ComMapClass),
					_Choice)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(COleObjectProperty)

	HRESULT FInit (IDispatch *pIDisp);
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

	HRESULT Init (_DApplication *pIApp, BOOL *pfSuccess);

private:
// DispatchID's 
	LCID m_lcid;
	DISPID m_dwDispId[_countof(s_pcoleObjPropNames)];
	CGeoDoc *m_pDoc;
};

