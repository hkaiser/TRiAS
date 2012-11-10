// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 19.07.2002 09:14:00
//
// @doc
// @module Segment.cpp | Implementation of the <c CSegmentExtension> class

#include "stdafx.h"



#include <tstring>
#include <Registrx.hxx>

#include <TRiASHelper.h>
#include <Com/PropertyActionBase.h>

#include <ipropseq.hxx>

#include "Strings.h"
//#include <xtsnguid.h>

#include <SrChoice.h>
//#include <selidprp.h>

#include "Segment.h"
#include "SegmentExt.h"


#include <istatus.h>

#include <initguid.h>

#include <statguid.h>
#include <objgguid.h>		// CLSID_ObjektGeometrie, IID_IInitObjektGeometrie ...

#import	"tlb/TRiASCS.tlb"	\
	raw_interfaces_only		\
	, raw_native_types		\
	, no_namespace			\
	, named_guids 


//DefineSmartInterface(TRiASExtDataEngine)
//DefineSmartInterface(TRiASOEProxy)

DefineSmartInterface(TRiASCS)
DefineSmartInterface(TRiASCSGCS)
DefineSmartInterface(TRiASCSPCS)
DefineSmartInterface(TRiASCSTransform)

#include <Com\VariantHelpers.h>
#include <Com\ErrorMacros2.h>
#include <Com/DefSmartIf.h>

//EXTERN_C const CLSID CLSID_ProgressIndicator;

/////////////////////////////////////////////////////////////////////////////

//#include <Com/PropertyActionBase.h>
#include <com/XMLInterTRiAS.h>

DEFINE_GUID(CLSID_ProgressIndicator, 0x07963819L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DEFINE_GUID(CLSID_PropertySequenceService,0x92BB6B5E,0x3F46,0x4236,0xA0,0xB6,0xDD,0xDB,0xD6,0x32,0xCE,0x1D);

DefineSmartInterface(ProgressIndicator)
DefineSmartInterface(ProgressIndicator2)

DefineSmartInterface(PropertySequenceService)



/////////////////////////////////////////////////////////////////////////////


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// sonstiges
#define SEGMENT_POSITION		3		// Position im Hauptmenu
//#define IDM_SEGMENT_ORIG        801		// ursprünglicher TRiAS-MenuID 

#pragma warning(disable: 4192)	//automatically excluding 'I...' while importing type library '...'


HRESULT LoadPropertySequence( const CComBSTR& strName, IPropertyActionSequence** ppPropertyActionSequence );
HRESULT SavePropertySequence( const CComBSTR& strName, IPropertyActionSequence* pPropertyActionSequence );
HRESULT CreateMainPropertySequence( const CComBSTR& strName, DWORD dwFlags, IPropertyActionSequence** ppPropertyActionSequence );
HRESULT CreateORPropertySequence( const CComBSTR& strName, DWORD dwFlags, IPropertyActionSequence** ppPropertyActionSequence );


// SmartIF's
DefineSmartInterface(PropertyActionSequence)
DefineSmartInterface(PropertyAction)
DefineSmartInterface(ClassProperty)
DefineSmartInterface(PropertyInfo)


// Liefert den CLSID des TRiAS-Zusatzmodules Segment
BOOL GetExtensionCLSID (CLSID &rClsID)
{
	rClsID = CLSID_Segment;
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CSegmentExtension

// InitExtension Wird nach erfolgreichem Laden des Zusatzmodules gerufen 
STDMETHODIMP_(BOOL) CSegmentExtension::InitExtension (short iMode)
{
	if (!CTriasExtension::InitExtension (iMode))
		return FALSE;

//#pragma TODO("Add initialisation here!")

	/////////////////////////////////////////////////////////////////////////////
	// Menüpunkt im Hauptmenu austauschen
	m_iMainMenu = InstallMenuItem(IDM_SEGMENTING, IDS_MENUENTRY, IMINormalMenu, EXTRA_MENU_POS, SEGMENT_POSITION);
//	m_iMainMenu = InstallMenuItem(IDM_SEGMENTING, IDS_MENUENTRY, IMINormalMenu, EXTRA_MENU_POS, -1);
	/////////////////////////////////////////////////////////////////////////////
	// Menüpunkt im OR-Menu austauschen
	m_iORMenu = InstallMenuItem(IDM_SEGMENTING, IDS_ORMENUENTRY, IMIObjWnd, -1, 0 );

// unseren aktuellen Namen besorgen
	{
	CCurrentUser regCfg (KEY_READ, TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Config"));
	DWORD dwSize = _MAX_PATH;

		if (!regCfg.GetSubSZ ("TRiASName", g_szTRiAS, dwSize))
			strcpy (g_szTRiAS, "TRiAS®");		// default
	}

	return TRUE;
}

// UnLoadExtension wird vor dem entladen des Zusatzmodules gerufen
STDMETHODIMP_(BOOL) CSegmentExtension::UnLoadExtension (void)
{
#pragma TODO("Add clean up code here!")

	RemoveMenuItem (IDM_SEGMENTING + MenuOffset(), IMINormalMenu | IMIOrigMenuItem, EXTRA_MENU_POS);
	RemoveMenuItem (IDM_SEGMENTING + MenuOffset(), IMIObjWnd | IMIOrigMenuItem, OR_EXTRA_MENU_POS);

	return CTriasExtension::UnLoadExtension();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Menuhandling
STDMETHODIMP_(BOOL) CSegmentExtension::MenuCommand (WPARAM wParam, HWND hWnd) 
{
HRESULT	hr = E_FAIL;

	switch (wParam) {
	case IDM_SEGMENTING: 
		{
		CWaitCursor Wait;
		WXMLDocument pXMLDocument;

			m_bHaveXML = m_bHaveEngines = FALSE;
			if (SUCCEEDED(pXMLDocument.CreateInstance (CLSID_XMLDocument)))
				m_bHaveXML = TRUE;

			if (m_bHaveXML ) 
				m_bHaveEngines = TRUE;

			if (!m_bHaveXML || !m_bHaveEngines) {
			CString strCaption;
			CString strMessage;

				VERIFY(strCaption.LoadString(IDS_SHOWXMLERROR_CAP));
				VERIFY(strMessage.LoadString(IDS_NOXMLDOMPARSER));

			TCHAR _buf[_MAX_PATH];

				wsprintf( _buf, strMessage, g_szTRiAS);
				AfxGetMainWnd()->MessageBox(_buf, strCaption, MB_OK | MB_ICONERROR);
				return FALSE;
			}

			hr = OnSegmentData ((NULL == hWnd) ? true : false);
			::CoFreeUnusedLibraries();
		}
		break;

	default:
		break;
	}
	return S_OK == hr ? TRUE : FALSE;
}

STDMETHODIMP_(BOOL) CSegmentExtension::MenuInit (HMENU hMenu, LPARAM lParam, HWND hWnd) 
{
	::EnableMenuItem (hMenu, IDM_SEGMENTING + MenuOffset(),  m_bHaveXML ? MF_ENABLED : MF_GRAYED);
	return TRUE;
}

// AFXPRIV.H:
#define WM_SETMESSAGESTRING 0x0362  // wParam = nIDS (or 0),
									// lParam = lpszOther (or NULL)

STDMETHODIMP_(BOOL) CSegmentExtension::MenuSelect (UINT uiMenuID, HMENU hMenu, HWND hWnd) 
{
	switch (uiMenuID) {
	case IDM_SEGMENTING:
		{

			CString str;

			VERIFY(str.LoadString(IDS_SEGMENTDATA));
			return DEX_SetMessageString((LPCSTR)str);
		}

	default:
		break;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Menubefehle

// Instantiieren der Geokomponenten über XML-Resource

HRESULT CSegmentExtension::OnSegmentData(bool bMainData) 
{
	COM_TRY {
	HRESULT hr = S_OK;
	CComBSTR bstrName;

	WPropertySequenceService Service (CLSID_PropertySequenceService);
	WProgressIndicator Status (CLSID_ProgressIndicator);
	HWND hWnd = AfxGetMainWnd()->GetSafeHwnd();
	char cbBuffer[_MAX_PATH];

		GetModuleFileName(_Module.GetModuleInstance(), cbBuffer, sizeof(cbBuffer));
		Service -> put_ResourceModule(CComBSTR(cbBuffer));

		Status -> InitNew (hWnd, PIFLAG_RESULT);
		if (bMainData) {
		// Menupunkt im Hauptfenster
			VERIFY(bstrName.LoadString (IDS_SEGMENTCAP));
			hr = Service -> RunActionSequence(reinterpret_cast<INT_PTR>(hWnd), CComBSTR("SegmentDataOKS.xml"), 
					bstrName, CComBSTR(""), WProgressIndicator2(Status), NULL, VARIANT_FALSE, NULL);
		}
		else {
		// Menupunkt in einem Recherchefenster
			VERIFY(bstrName.LoadString (IDS_ORSEGMENTCAP));
			hr = Service -> RunActionSequence(reinterpret_cast<INT_PTR>(hWnd), CComBSTR("SegmentDataORWnd.xml"), 
					bstrName, CComBSTR(""), WProgressIndicator2(Status), NULL, VARIANT_FALSE, NULL);
		}

	// KK991126
		if (S_OK != hr) {
			if (E_ABORT == hr)
				return hr;

			if (CLASS_E_NOTLICENSED != hr) {
			// zusätzliche Meldung, nur wenn kein Lizensierungsfehler
			CString strMessage;

				USES_CONVERSION;
				VERIFY(strMessage.LoadString(IDS_NOWORKING));
				AfxGetMainWnd()->MessageBox (strMessage, OLE2A(bstrName), MB_OK | MB_ICONERROR);
			}
//			Status -> WasCanceled();
			return hr;
		}

	} COM_CATCH;
	return S_OK;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////