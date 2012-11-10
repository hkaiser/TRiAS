// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 03.06.2002 16:35:25 
//
// @doc
// @module VidCtrl.h | Declaration of the <c CVidCtrlExtension> class

#if !defined(_VIDCTRL_H__E03B8A1D_502D_4FA4_B065_C9B0ACD843EE__INCLUDED_)
#define _VIDCTRL_H__E03B8A1D_502D_4FA4_B065_C9B0ACD843EE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols
#include "VideoPaneWindowImpl.h"

///////////////////////////////////////////////////////////////////////////////
// LizensierungsKlasse
#if defined(_DEBUG)
extern "C" bool g_fGlobalLic;
#else
#define g_fGlobalLic false
#endif // defined(_DEBUG)

class CMyLicense
{
protected:
	static BOOL VerifyLicenseKey(BSTR bstr)
	{
	CComBSTR bstrKey;

		USES_CONVERSION;
		if ((GetLicenseKey (0, &bstrKey) && !wcscmp (bstrKey, bstr)) ||
			 ::SetLicensed (OLE2A(bstr)))
		{
			return TRUE;
		}
		return FALSE;
	}

	static BOOL GetLicenseKey (DWORD, BSTR *pBstr) 
	{
	CComBSTR bstrKey (_MAX_PATH, (LPCOLESTR)NULL);

		if (!::GetLicenseKey (bstrKey.m_str, _MAX_PATH))
			return FALSE;

		*pBstr = bstrKey.Detach(); 
		return TRUE;
	}

	static BOOL IsLicenseValid() { return g_fGlobalLic || ::GetLicensed(); }
};

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(HotSpot);

/////////////////////////////////////////////////////////////////////////////
// CVidCtrlExtension
class ATL_NO_VTABLE CVidCtrlExtension : 
	public CComCoClass<CVidCtrlExtension, &CLSID_VidCtrl>,
	public CTriasExtension,
	public IVideoControl
{
public:
	CVidCtrlExtension() :
		m_pVideoPane(NULL)
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_VIDEOPANETAB)
	DECLARE_NOT_AGGREGATABLE_SINGLE(CVidCtrlExtension, g_pTE)
	DECLARE_CLASSFACTORY2(CMyLicense)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CVidCtrlExtension)
		COM_INTERFACE_ENTRY(IVideoControl)
		COM_INTERFACE_ENTRY_CHAIN(CTriasExtension)
	END_COM_MAP()

// Docking support
	bool IsBarActive() { return (NULL != m_pVideoPane) ? true : false; }
	bool CreateBar();
	bool ShowBar();
	bool FreeBar();

// Notification handlers
	HRESULT OnProjectToClose();
	void OnMouseMove(CPoint ptScreen);

// Toolbar verwalten
	HRESULT InitToolbar();
	HRESULT FreeToolbar();

// Positionskreuz verwalten
	HRESULT ShowTurtle();
	HRESULT HideTurtle();

// ITriasXtension
public:
	STDMETHOD_(BOOL, InitExtension) (short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (void);
	STDMETHOD_(LRESULT, Notification) (WPARAM wParam, LPARAM lParam);
	STDMETHOD_(LRESULT, WindowsNotification) (UINT wMsg, WPARAM wParam, LPARAM lParam);

// IVideoControl
	STDMETHOD(TrackObject)(/*[in]*/ INT_PTR hObject);
	
private:
	CVideoPaneWindowImpl *m_pVideoPane;
	WHotSpot m_Turtle;
};

#endif // !defined(_VIDCTRL_H__E03B8A1D_502D_4FA4_B065_C9B0ACD843EE__INCLUDED_)
