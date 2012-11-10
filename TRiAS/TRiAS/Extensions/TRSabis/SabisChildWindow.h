// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 14.03.2002 21:38:40 
//
// @doc
// @module SabisChildWindow.h | Declaration of the <c CSabisChildWindow> class

#ifndef __SABISCHILDWINDOW_H_
#define __SABISCHILDWINDOW_H_

#include "resource.h"       // main symbols
#include "triaschild.h"		// Window implementation

/////////////////////////////////////////////////////////////////////////////
// CSabisChildWindow
class ATL_NO_VTABLE CSabisChildWindow : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CSabisChildWindow, &CLSID_SabisChildWindow>,
	public IDispatchImpl<CommonChildWindow2, &IID_CommonChildWindow2, &LIBID_TRSABiS>
{
public:
	CSabisChildWindow() :
		m_Tag(_T(""))
	{
		m_pWnd = NULL;
	}

	~CSabisChildWindow()
	{
	// aufräumen
		if (NULL != m_pWnd) {			
			m_pWnd->DestroyWindow();
			delete m_pWnd;
		}
	}
	DECLARE_REGISTRY_RESOURCEID(IDR_SABISCHILDWINDOW)

	BEGIN_COM_MAP(CSabisChildWindow)
		COM_INTERFACE_ENTRY(CommonChildWindow2)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
	//	Erweiterung laden
	LOADEXTENSIONEX le;

		memset (&le, 0, sizeof (LOADEXTENSIONEX));
		le.m_pDesc = NULL;
		le.m_pName = "TRiAS.TRiASSabis.1";
		le.m_iMode = LEFullLoad;
		le.m_fGlobal = TRUE;		
	
		return (NULL != DEX_ExternalLoadExtensionEx (le)) ? S_OK : E_FAIL;
	}
	void FinalRelease()
	{
	LOADEXTENSIONEX le;

		memset (&le, 0, sizeof (LOADEXTENSIONEX));
		le.m_pDesc = NULL;
		le.m_pName = "TRiAS.TRiASSabis.1";
		le.m_iMode = LENoLoad;
		le.m_fGlobal = TRUE;		
		DEX_ExternalLoadExtensionEx (le);
	}

// CommonChildWindow2
public:
	STDMETHODIMP put_BackColor (long cBkColor);
	STDMETHODIMP get_BackColor (long *cBkColor);
	STDMETHODIMP put_Caption (BSTR bstrCaption);
	STDMETHODIMP get_Caption (BSTR *pbstrCaption);
	STDMETHODIMP put_Enabled (VARIANT_BOOL fEnabled);
	STDMETHODIMP get_Enabled (VARIANT_BOOL *pfEnabled);
	STDMETHODIMP get_Height (long *plHeight);
	STDMETHODIMP put_Height (long lHeight);
	STDMETHODIMP get_hWnd (long *phWnd);
	STDMETHODIMP put_Icon (VARIANT vPict);
	STDMETHODIMP get_Left (long *plLeft);
	STDMETHODIMP put_Left (long lLeft);
	STDMETHODIMP Move (long X, long Y);
	STDMETHODIMP OnKeyDown (short *KeyCode, short *Shift);
	STDMETHODIMP put_Tag (BSTR bstrTag);
	STDMETHODIMP get_Tag (BSTR *pbstrTag);
	STDMETHODIMP get_Top (long *plTop);
	STDMETHODIMP put_Top (long lTop);
	STDMETHODIMP put_Visible (VARIANT_BOOL fVisible);
	STDMETHODIMP get_Visible (VARIANT_BOOL *pfVisible);
	STDMETHODIMP get_Width (long *plWidth);
	STDMETHODIMP put_Width (long lWIdth);
	STDMETHODIMP get_WindowState (long *plState);
	STDMETHODIMP put_WindowState (long lState);

private:
	CComBSTR		m_Tag;		// Tag zur Kennzeichnung des Fensters
	CTRiASChild*	m_pWnd;

// priv. Accessors
private:
	CTRiASChild* GetWindow();	// Accessor und ClassFactory
	HRESULT GetWindowRect(CRect& rect);	// ermitteln des Envelopes von m_pWnd;
};

#endif //__SABISCHILDWINDOW_H_
