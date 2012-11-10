// ToolBarButton.h

#include <itoolbar.h>
#include <dtoolbar.h>

#include <bscrguid.h>		// BSCRIPT.EXT
#include <ibscript.hxx>

/////////////////////////////////////////////////////////////////////////////
// CToolBarButton - Interfaces für IControlToolBarButton

DefineSmartInterface(ExtendBScript);
DefineSmartInterface(PictureDisp);

class CToolBarButton :
	public IControlToolBarButton,
	public ISupportErrorInfo,
	public CComDualImpl<DControlToolBarButton, &IID_DControlToolBarButton, &LIBID_ToolBarLib,
				TOOLBAR_TYPELIB_VERSION_MAJOR, TOOLBAR_TYPELIB_VERSION_MINOR>,
	public CComDualImpl<DToolBarUIOwner, &IID_DToolBarUIOwner, &LIBID_ToolBarLib,
				TOOLBAR_TYPELIB_VERSION_MAJOR, TOOLBAR_TYPELIB_VERSION_MINOR>,
	public CComObjectRoot,
	public CComCoClass<CToolBarButton, &CLSID_TRiASToolBarButton>
{
public:
		CToolBarButton() {}
		~CToolBarButton() {}

// unterstützte Interface's
	BEGIN_COM_MAP(CToolBarButton)
		COM_INTERFACE_ENTRY(IControlToolBarButton)
		COM_INTERFACE_ENTRY2(IDispatch, DControlToolBarButton)
		COM_INTERFACE_ENTRY_IID(IID_DControlToolBarButton, DControlToolBarButton)
		COM_INTERFACE_ENTRY_IID(IID_DTRiASBaseClass, DControlToolBarButton)
		COM_INTERFACE_ENTRY_IID(IID_DToolBarUIOwner, DToolBarUIOwner)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	DECLARE_AGGREGATABLE(CToolBarButton)
	DECLARE_REGISTRY_RESOURCEID(IDR_TOOLBARBTTN_RGS)		// registry

	HRESULT FinalConstruct (void);

public:
///////////////////////////////////////////////////////////////////////////////
// _ITRiASBaseClass methods
    STDMETHOD(get_isA)(THIS_ long *plRTTI);
	STDMETHOD(get_Parent)(THIS_ IDispatch **ppIDisp)
		{ return (NULL != (IDispatch *)m_Parent) ? m_Parent -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp) : E_UNEXPECTED; }
	STDMETHOD(put_Parent)(THIS_ IDispatch *pIDisp)
		{ m_Parent = pIDisp; return NOERROR; }
	STDMETHOD(get_Application)(THIS_ IDispatch **ppIDisp)
		{ return (NULL != (IDispatch *)m_App) ? m_App -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp) : E_UNEXPECTED; }
	STDMETHOD(put_Application)(THIS_ IDispatch *pIDisp)
		{ m_App = pIDisp; return NOERROR; }

	STDMETHOD(get_Properties) (THIS_ DTRiASProperties **ppIProps);
	STDMETHOD(CreateProperty) (THIS_ VARIANT vName, VARIANT vType, VARIANT vValue, DTRiASProperty **ppIProp);

// IControlToolBarButton specific functions
	STDMETHOD(ButtonInfo)(THIS_ TBBUTTON *pBttns);		// internal use only

// DControlToolBarButton specific functions
    STDMETHOD(get_Name)(THIS_ BSTR *pbstrName);
    STDMETHOD(put_Name)(THIS_ BSTR bstrName);
    STDMETHOD(get_Width)(THIS_ long *piWidth);
    STDMETHOD(put_Width)(THIS_ long iWidth);
    STDMETHOD(get_HelpText)(THIS_ BSTR *pbstrHelpText);
    STDMETHOD(put_HelpText)(THIS_ BSTR bstrHelpText);
    STDMETHOD(get_CmdID)(THIS_ int *piCmdID);
    STDMETHOD(put_CmdID)(THIS_ int iCmdID);
    STDMETHOD(get_Style)(THIS_ BUTTONSTYLE *pdwStyle);
    STDMETHOD(put_Style)(THIS_ BUTTONSTYLE dwStyle);
    STDMETHOD(get_State)(THIS_ BUTTONSTATE *pdwState);
    STDMETHOD(put_State)(THIS_ BUTTONSTATE dwState);
    STDMETHOD(GetImage)(THIS_ long *phBitmap, int *piCnt, int *piOffset);
    STDMETHOD(AttachImage)(THIS_ VARIANT vPicture, VARIANT iIndex, VARIANT vSizeX);
	STDMETHOD(put_Value)(THIS_ VARIANT_BOOL fClick);

// DToolBarUIOwner methods 
	STDMETHOD(SetToolBarUIOwnerSite)(THIS_ int uiID, DControlToolBar *pIToolBar);
	STDMETHOD(UpdateUI)(THIS_ DTRiASCmdUI *pICmdUI);
	STDMETHOD(GetDescription)(THIS_ int uiID, BSTR *pbstrDesc);
	STDMETHOD(FireCommand)(THIS_ int uiID, int nCode);

// ISupportErrorInfo methods
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

protected:
	HRESULT RetrieveBitmap (VARIANT &vPicture);

	CComPtr<IDispatch> m_Parent;
	CComPtr<IDispatch> m_App;
	WExtendBScript m_EvtSink;

	TBBUTTON m_tb;				// ToolBarButtonInfo
	string m_strName;
	string m_strDesc;

	WPictureDisp m_PictDisp;
	int m_iCnt;
	int m_iOffset;

// Synchronisation des Aufrufes der Routinen im Basic
	long m_lMutex;
};

///////////////////////////////////////////////////////////////////////////////
// Klasse, die erlaubt, nur einmal durch eine Routine zu gehen
class CInterlockedSync 
{
private:
	long *m_plMutex;
	long m_lResult;

public:
		CInterlockedSync (long *plMutex) : m_plMutex(plMutex)
			{ m_lResult = ::piInterlockedIncrement (plMutex); }
		~CInterlockedSync (void)
			{ ::piInterlockedDecrement (m_plMutex); }

	bool IsFirst (void) { return (0 == m_lResult) ? true : false; }
};
