// ToolBarButton.cpp

#include "fakemfcp.hxx"
#include "fakemfc.h"

#include <toolguid.h>
#include <itoolbar.h>
#include <dirisole.h>
#include <oleguid.h>
#include <itriasap.h>

#include <eb.h>
#include <BildObj.h>

#include "Wrapper.h"		// SmartInterfaces
#include "Picture.h"
#include "fakemfc.hxx"

#include "ToolBarButton.h"
#if _TRiAS_VER < 0x0400
#include "OlePro32Wrap.h"
#endif // _TRiAS_VER < 0x0400

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// benötigte SmartInterfaces
DefineSmartInterface2(DTRiASCmdUI, IID_DTRiASCmdUI);
DefineSmartInterface(Dispatch);
DefineSmartInterface(GetTRiASApplication);

///////////////////////////////////////////////////////////////////////////////
// ein IPicture aus einer Bitmap erzeugen
HRESULT CreatePicture (HBITMAP hBmp, HPALETTE hPal, bool fOwn, IPictureDisp **ppIDisp)
{
#if _TRiAS_VER < 0x0400
COlePro32Bind Wrap;		// OlePro32.dll dynamisch laden und binden

	if (!Wrap.IsValid()) return E_UNEXPECTED;
#endif // _TRiAS_VER < 0x0400

PICTDESC pdesc;
WDispatch Disp;

	pdesc.cbSizeofstruct = sizeof(pdesc);
	pdesc.picType = PICTYPE_BITMAP;
	pdesc.bmp.hbitmap = hBmp;
	pdesc.bmp.hpal = hPal;

#if _TRiAS_VER < 0x0400
HRESULT hr = Wrap.OleCreatePictureIndirect (&pdesc, IID_IPictureDisp, fOwn, (LPVOID *)ppIDisp);
#else
HRESULT hr = ::OleCreatePictureIndirect (&pdesc, IID_IPictureDisp, fOwn, (LPVOID *)ppIDisp);
#endif // _TRiAS_VER < 0x0400

	if (FAILED(hr)) {
		::DeleteObject (hBmp);
		return hr;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// hier geht's los
HRESULT CToolBarButton::FinalConstruct (void)
{ 
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	try {
	WGetTRiASApplication GetApp (CLSID_OleAutoExtension);
	WDispatch App;

		THROW_FAILED_HRESULT(GetApp -> GetApplication (IID_IDispatch, App.ppv()));

		THROW_FAILED_HRESULT(put_Application (App));
		THROW_FAILED_HRESULT(put_Parent (App));
	
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	memset (&m_tb, 0, sizeof(TBBUTTON));
	m_tb.idCommand = (int)LOWORD(this); 
	m_tb.fsStyle = TBSTYLE_BUTTON;

	m_iCnt = 0;
	m_iOffset = -1;

	m_lMutex = -1;

CBitmap Bmp;

	if (Bmp.LoadMappedBitmap(ID_MACROBUTTON)) {
		m_iCnt = 16;
	
	HRESULT hr = CreatePicture ((HBITMAP)Bmp.Detach(), NULL, true, m_PictDisp.ppi());

		if (FAILED(hr)) return hr;
	}

	try {
		m_strName = TEXT("ToolBarButton");
		m_strDesc = TEXT("ToolBarButton\nToolBarButton");
	} catch (...) {
		return E_OUTOFMEMORY;
	}

return TxGetExtension() -> m_pXtnSite -> GetXtension (CLSID_MacroScriptExtension, IID_IExtendBScript, m_EvtSink.ppv());
}

STDMETHODIMP CToolBarButton::get_Properties (DTRiASProperties **ppIProps)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	ATLTRACENOTIMPL("CToolBarButton::get_Properties");
}

STDMETHODIMP CToolBarButton::CreateProperty (VARIANT vName, VARIANT vType, VARIANT vValue, DTRiASProperty **ppIProp)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	ATLTRACENOTIMPL("CToolBarButton::CreateProperty ");
}

/////////////////////////////////////////////////////////////////////////////
// IControlToolBarButton specific functions
STDMETHODIMP CToolBarButton::get_isA (long *plRTTI)
{
	if (NULL == plRTTI)	return E_POINTER;

	*plRTTI = RTTI_ToolBarButton;

return NOERROR;
}

STDMETHODIMP CToolBarButton::get_Name (BSTR *pbstrName)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	USES_CONVERSION;
	if (NULL == pbstrName)	return E_POINTER;
	
	*pbstrName = SysAllocString (A2OLE(m_strName.c_str()));
	if (NULL == *pbstrName)	return E_OUTOFMEMORY;
	
	return NOERROR;
}

STDMETHODIMP CToolBarButton::put_Name (BSTR bstrName)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	USES_CONVERSION;
	m_strName = OLE2A(bstrName);
	return NOERROR;
}

STDMETHODIMP CToolBarButton::get_Width (long *piWidth)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == piWidth)	return E_POINTER;

	if (m_tb.fsStyle & TBSTYLE_SEP)
		*piWidth = m_tb.iBitmap;
	else 
		*piWidth = 0;

return NOERROR;
}

STDMETHODIMP CToolBarButton::put_Width (long iWidth)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (m_tb.fsStyle & TBSTYLE_SEP) {
		m_tb.iBitmap = iWidth;
		return NOERROR;
	}

return S_FALSE;
}

STDMETHODIMP CToolBarButton::get_HelpText (BSTR *pbstrHelpText)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	USES_CONVERSION;
	if (NULL == pbstrHelpText)	return E_POINTER;
	
	*pbstrHelpText = SysAllocString (A2OLE(m_strDesc.c_str()));
	if (NULL == *pbstrHelpText)	return E_OUTOFMEMORY;
	
	return NOERROR;
}

STDMETHODIMP CToolBarButton::put_HelpText (BSTR bstrHelpText)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	USES_CONVERSION;
	m_strDesc = OLE2A(bstrHelpText);
	return NOERROR;
}

STDMETHODIMP CToolBarButton::get_CmdID (int *piCmdID)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == piCmdID) return E_POINTER;
	
	*piCmdID = m_tb.idCommand;
	return NOERROR;
}

STDMETHODIMP CToolBarButton::put_CmdID (int iCmdID)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	m_tb.idCommand = iCmdID;
	return NOERROR;
}

STDMETHODIMP CToolBarButton::get_Style (BUTTONSTYLE *pdwStyle)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == pdwStyle) return E_POINTER;
	
	*pdwStyle = (BUTTONSTYLE)m_tb.fsStyle;
	return NOERROR;
}

STDMETHODIMP CToolBarButton::put_Style (BUTTONSTYLE dwStyle)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	m_tb.fsStyle = dwStyle;

	if (BUTTONSTYLE_SEPARATOR == dwStyle && 	
		m_tb.idCommand == (int)LOWORD(this))
	{
	// Id wurde noch nicht gesetzt
		m_tb.idCommand = 0;		// Separatoren haben (normalerweise) uiCmd == 0
	}

	return NOERROR;
}

STDMETHODIMP CToolBarButton::get_State (BUTTONSTATE *pdwState)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == pdwState) return E_POINTER;
	
	*pdwState = (BUTTONSTATE)m_tb.fsState;
	return NOERROR;
}

STDMETHODIMP CToolBarButton::put_State (BUTTONSTATE dwState)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	m_tb.fsState = dwState;
	return NOERROR;
}

STDMETHODIMP CToolBarButton::GetImage (long *phBitmap, int *piCnt, int *piOffset)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == phBitmap) return E_POINTER;

	if (BUTTONSTYLE_SEPARATOR == m_tb.fsStyle)
		return E_FAIL;		// Separatoren haben keine Bitmap

CPicture Pict (m_PictDisp, false);

	ATLTRY(*phBitmap = Pict.GetHandle());
	if (NULL != piCnt) *piCnt = m_iCnt;
	if (NULL != piOffset) *piOffset = m_iOffset;

	return (NULL != *phBitmap) ? NOERROR : E_FAIL;
}

HRESULT CToolBarButton::RetrieveBitmap (VARIANT &vPicture)
{
CComVariant vArg;
HRESULT hr = vArg.ChangeType (VT_DISPATCH, &vPicture);

	if (SUCCEEDED(hr)) {
		hr = V_DISPATCH(&vArg) -> QueryInterface(IID_IPictureDisp, m_PictDisp.ppv());
		if (FAILED(hr)) return hr;

		m_iOffset = 0;
		m_iCnt = 1;
		return S_OK;
	}

	hr = vArg.ChangeType (VT_I4, &vPicture);		// BitmapHandle ?
	if (SUCCEEDED(hr)) {
		hr = CreatePicture ((HBITMAP)V_I4(&vArg), NULL, false, m_PictDisp.ppi());
		if (FAILED(hr)) return hr;

		m_iOffset = 0;
		m_iCnt = 1;
		return S_OK;
	}

	hr = vArg.ChangeType (VT_BSTR, &vPicture);	// DateiName ?
	if (SUCCEEDED(hr)) {
	CBildObjekt bmp;

		USES_CONVERSION;
	
	HBITMAP hBmp = bmp.ReadFile (OLE2A(V_BSTR(&vArg)));

		if (NULL != hBmp) {
			hr = CreatePicture (bmp.Detach(), bmp.DetachHPal(), true, m_PictDisp.ppi());
			if (FAILED(hr)) return hr;

			m_iOffset = 0;
			m_iCnt = 1;
			return S_OK;
		}
	}

	return E_INVALIDARG;
}

STDMETHODIMP CToolBarButton::AttachImage (VARIANT vPicture, VARIANT vIndex, VARIANT vSizeX)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

HRESULT hr = RetrieveBitmap (vPicture);

	if (FAILED(hr)) return hr;

// Argumente konvertieren
CComVariant vArg;
long lIndex = -1;
long lSizeX = 0;

	hr = vArg.ChangeType (VT_I4, &vIndex);
	if (SUCCEEDED(hr)) lIndex = V_I4(&vArg);

	hr = vArg.ChangeType (VT_I4, &vSizeX);
	if (SUCCEEDED(hr)) lSizeX = V_I4(&vArg);

	if (lIndex >= 0 && 0 == lSizeX)
		return E_INVALIDARG;	// Größe muß gegeben sein

// wenn kein Index gegeben ist, dann die Bitmap direkt verwenden
	if (lIndex < 0) return S_OK;

// ansonsten generieren des gewünschten Ausschnittes
// ...
	m_PictDisp.Assign(NULL);		// wieder freigeben
	return E_NOTIMPL;
}

STDMETHODIMP CToolBarButton::put_Value (VARIANT_BOOL fClick)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (!fClick) return E_INVALIDARG;

BUTTONSTATE rgState;
HRESULT hr = get_State (&rgState);

	if (FAILED(hr)) return hr;
	if (!(rgState & BUTTONSTATE_ENABLED))
		return E_FAIL;

	return FireCommand (m_tb.idCommand, CN_COMMAND);
}

/////////////////////////////////////////////////////////////////////////////
// DToolBarUIOwner methods 
STDMETHODIMP CToolBarButton::SetToolBarUIOwnerSite (int uiID, DControlToolBar *pIToolBar)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	return E_NOTIMPL;
}

STDMETHODIMP CToolBarButton::UpdateUI (DTRiASCmdUI *pICmdUI)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == (IUnknown *)m_EvtSink) return E_UNEXPECTED;

// nur einmal gleichzeitig barbeiten
CInterlockedSync Sync (&m_lMutex);

	if (!Sync.IsFirst()) return E_FAIL;

// durchzuführende Aktion
ebPARAM Pars[2];
LPVOID cbParam[2];

	Pars[0].wType = 0;		// no return value
	Pars[0].szExtType[0] = '\0';
	cbParam[0] = NULL;

	Pars[1].wType = TYP_APPOBJECT;
	strcpy (Pars[1].szExtType, TEXT("ToolBarButton"));

DControlToolBarButton *pITB = (DControlToolBarButton *)this;

	pITB -> AddRef();		// BUGBUG: BasicScript ruft Release() nach Routine
	cbParam[1] = &pITB;

BSPARAM bs = { Pars, cbParam };
string str = m_strName + TEXT("_Update");
HRESULT hr = m_EvtSink -> FireEvent (str.c_str(), 1, &bs);

//	if (S_OK != hr) // nur, wenn kein Erfolg (s.o.)
		pITB -> Release();	// jetzt immer (#HK960926)
	
// in jedem Fall UI selbst richten
	try {
//	WDTRiASCmdUI DispUI (pICmdUI);		// throws hr
	BUTTONSTATE rgState;

		hr = pITB -> get_State (&rgState);
		if (FAILED(hr)) _com_issue_error(hr);

		pICmdUI -> put_IsEnabled (rgState & BUTTONSTATE_ENABLED);
		pICmdUI -> put_CheckState (rgState & BUTTONSTATE_CHECKED ? 1 : 0);

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return hr;
}

STDMETHODIMP CToolBarButton::GetDescription (int, BSTR *pbstrDesc)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == (IUnknown *)m_EvtSink) return E_UNEXPECTED;

// nur einmal gleichzeitig barbeiten
CInterlockedSync Sync (&m_lMutex);

	if (!Sync.IsFirst()) return E_FAIL;

// durchzuführende Aktion
ebPARAM Pars[1];
LPVOID cbParam[1];
LPSTR pStr = NULL;

	Pars[0].wType = TYP_STRING; //|TYP_MODSPARM;
	Pars[0].szExtType[0] = '\0';
	cbParam[0] = &pStr;

BSPARAM bs = { Pars, cbParam };
string str = m_strName + TEXT("_Select");
HRESULT hr = m_EvtSink -> FireEvent (str.c_str(), 0, &bs);

	USES_CONVERSION;
	if (S_OK == hr) {
		if (NULL != pStr) {
			*pbstrDesc = SysAllocString (A2OLE(pStr));
			CoTaskMemFree (pStr);
			if (NULL == *pbstrDesc)
				hr = E_OUTOFMEMORY;
		} else
			hr = E_OUTOFMEMORY;
	}

	if (S_OK != hr)	{	// vordefinierten Text liefern
		if (NPOS != m_strDesc.find('\n'))
			*pbstrDesc = SysAllocString (A2OLE(m_strDesc.c_str()));
		else {
		string str = m_strDesc + "\n" + m_strDesc;

			*pbstrDesc = SysAllocString (A2OLE(str.c_str()));
		}
		if (NULL != *pbstrDesc)
			hr = NOERROR;
	}

return hr;
}

STDMETHODIMP CToolBarButton::FireCommand (int, int nCode)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (nCode != CN_COMMAND) return S_FALSE;			// nur WM_COMMAND's bearbeiten
	if (NULL == (IUnknown *)m_EvtSink) return E_UNEXPECTED;

// nur einmal gleichzeitig barbeiten
CInterlockedSync Sync (&m_lMutex);

	if (!Sync.IsFirst()) return E_FAIL;

// durchzuführende Aktion
ebPARAM Pars = { 0, '\0' };
LPVOID pParam = NULL;
BSPARAM bs = { &Pars, &pParam };
string str = m_strName + TEXT("_Click");

	return m_EvtSink -> FireEvent (str.c_str(), 0, &bs);
}

///////////////////////////////////////////////////////////////////////////////
// ISupportErrorInfo methods
STDMETHODIMP CToolBarButton::InterfaceSupportsErrorInfo (REFIID riid)
{
	if (InlineIsEqualGUID(riid, IID_DControlToolBarButton) ||
		InlineIsEqualGUID(riid, IID_DToolBarUIOwner))
	{
		return S_OK;
	}
	return S_FALSE;
}

// IControlToolBarButton specific functions
STDMETHODIMP CToolBarButton::ButtonInfo (BYTE *pData)
{
	if (NULL == pData) return E_POINTER;

TBBUTTON *pBttn = reinterpret_cast<TBBUTTON *>(pData);

	*pBttn = m_tb;		// bitweises kopieren
	if (0 != pBttn -> dwData)
		reinterpret_cast<IUnknown *>(pBttn -> dwData) -> AddRef();
	return S_OK;
}

