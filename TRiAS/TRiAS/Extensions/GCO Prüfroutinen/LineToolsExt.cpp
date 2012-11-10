// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 06.11.2002 09:25:38
//
// @doc
// @module LineTools.cpp | Implementation of the <c CLineToolsExtension> class

#include "stdafx.h"

#include "errorcode.h"

#include <tstring>
#include <Registrx.hxx>

#include <TRiASHelper.h>
#include <triastlb.h>
#include <Com/PropertyActionBase.h>

#include <ipropseq.hxx>

#include "Strings.h"

#include <SrChoice.h>

#include "LineTools.h"
#include "LineToolsExt.h"


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

#include <com/XMLInterTRiAS.h>

DEFINE_GUID(CLSID_ProgressIndicator, 0x07963819L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DEFINE_GUID(CLSID_PropertySequenceService,0x92BB6B5E,0x3F46,0x4236,0xA0,0xB6,0xDD,0xDB,0xD6,0x32,0xCE,0x1D);

DefineSmartInterface(ProgressIndicator)
DefineSmartInterface(ProgressIndicator2)

DefineSmartInterface(PropertySequenceService)


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// sonstiges
#define CODE_POSITION		-1		// Position im Hauptmenu

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


/////////////////////////////////////////////////////////////////////////////
// für XtensionBasisLib benötigte globale Funktionen

// Liefert den CLSID des TRiAS-Zusatzmodules LineTools
BOOL GetExtensionCLSID (CLSID &rClsID)
{
	rClsID = CLSID_LineTools;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CLineToolsExtension

// InitExtension Wird nach erfolgreichem Laden des Zusatzmodules gerufen 
STDMETHODIMP_(BOOL) CLineToolsExtension::InitExtension (short iMode)
{
	if (!CTriasExtension::InitExtension (iMode))
		return FALSE;

//#pragma TODO("Add initialisation here!")


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
STDMETHODIMP_(BOOL) CLineToolsExtension::UnLoadExtension (void)
{
//#pragma TODO("Add clean up code here!")

	return CTriasExtension::UnLoadExtension();
}


/////////////////////////////////////////////////////////////////////////////
// Menuhandling
STDMETHODIMP_(BOOL) CLineToolsExtension::MenuCommand (WPARAM wParam, HWND hWnd) 
{
HRESULT	hr = E_FAIL;

	switch (wParam) {

	case IDM_CODECHECK:				// Allgemeiner Code-Test
	case IDM_CODECHECKMULTI:		// Globaler Test
	case IDM_CHECKGEOMETRIE:		// Geometrietest
	case IDM_LINECHECK:				// Allgemeiner Strassen-Test
	case IDM_CLASSIFY:				// Allgemeine GCA-Hüllen
	case IDM_CLASSIFYWINDOW:		// Allgemeine GCA-Klassenfenster


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

			hr = OnCodeCheckData (wParam,(NULL == hWnd) ? true : false);
			::CoFreeUnusedLibraries();
		}
		break;

	default:
		break;
	}
	return S_OK == hr ? TRUE : FALSE;
}

STDMETHODIMP_(BOOL) CLineToolsExtension::MenuInit (HMENU hMenu, LPARAM lParam, HWND hWnd) 
{
	::EnableMenuItem (hMenu, IDM_CODECHECK + MenuOffset(),  m_bHaveXML ? MF_ENABLED : MF_GRAYED);
	::EnableMenuItem (hMenu, IDM_CODECHECKMULTI + MenuOffset(),  m_bHaveXML ? MF_ENABLED : MF_GRAYED);
	::EnableMenuItem (hMenu, IDM_CHECKGEOMETRIE + MenuOffset(),  m_bHaveXML ? MF_ENABLED : MF_GRAYED);
	::EnableMenuItem (hMenu, IDM_LINECHECK + MenuOffset(),  m_bHaveXML ? MF_ENABLED : MF_GRAYED);
	::EnableMenuItem (hMenu, IDM_CLASSIFY + MenuOffset(),  m_bHaveXML ? MF_ENABLED : MF_GRAYED);
	::EnableMenuItem (hMenu, IDM_CLASSIFYWINDOW + MenuOffset(),  m_bHaveXML ? MF_ENABLED : MF_GRAYED);
	return TRUE;
}

// AFXPRIV.H:
#define WM_SETMESSAGESTRING 0x0362  // wParam = nIDS (or 0),
									// lParam = lpszOther (or NULL)

STDMETHODIMP_(BOOL) CLineToolsExtension::MenuSelect (UINT uiMenuID, HMENU hMenu, HWND hWnd) 
{
	switch (uiMenuID) {
	case IDM_CODECHECK:
		{

			CString str;

			VERIFY(str.LoadString(IDS_CODECHECKCAP));
			return DEX_SetMessageString((LPCSTR)str);
		}

	case IDM_CODECHECKMULTI:
		{

			CString str;

			VERIFY(str.LoadString(IDS_CODECHECKMULTICAP));
			return DEX_SetMessageString((LPCSTR)str);
		}


	case IDM_CHECKGEOMETRIE:
		{

			CString str;

			VERIFY(str.LoadString(IDS_CHECKGEOMETRIECAP));
			return DEX_SetMessageString((LPCSTR)str);
		}

	case IDM_LINECHECK:
		{

			CString str;

			VERIFY(str.LoadString(IDS_LINECHECKCAP));
			return DEX_SetMessageString((LPCSTR)str);
		}

	case IDM_CLASSIFY:
		{

			CString str;

			VERIFY(str.LoadString(IDS_CLASSIFYCAP));
			return DEX_SetMessageString((LPCSTR)str);
		}

	case IDM_CLASSIFYWINDOW:
		{

			CString str;

			VERIFY(str.LoadString(IDS_CLASSIFYWINDOWCAP));
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

HRESULT CLineToolsExtension::OnCodeCheckData(WPARAM wParam, bool bMainData) 
{
	COM_TRY {

	HRESULT hr = S_OK;

	CComBSTR bstrNameM;
	CComBSTR bstrNameO;

	CComBSTR bstrCheckM;
	CComBSTR bstrCheckO;


	switch (wParam) {

	case IDM_CODECHECK: 
		{
			VERIFY(bstrCheckM.LoadString(IDS_CODECHECKXML));
			VERIFY(bstrCheckO.LoadString(IDS_ORCODECHECKXML));
			VERIFY(bstrNameM.LoadString (IDS_CODECHECKCAP));
			VERIFY(bstrNameO.LoadString (IDS_ORCODECHECKCAP));
			m_iMethod = PRF_CODE;

		}
		break;

 
	case IDM_CODECHECKMULTI:
		{
			VERIFY(bstrCheckM.LoadString(IDS_CODECHECKMULTIXML)) ;
			VERIFY(bstrCheckO.LoadString(IDS_ORCODECHECKMULTIXML));
			VERIFY(bstrNameM.LoadString (IDS_CODECHECKMULTICAP));
			VERIFY(bstrNameO.LoadString (IDS_ORCODECHECKMULTICAP));
			m_iMethod = PRF_DOPPELCODE;
		}
		break;


	case IDM_CHECKGEOMETRIE:
		{
			VERIFY(bstrCheckM.LoadString(IDS_CHECKGEOMETRIEXML)) ;
			VERIFY(bstrCheckO.LoadString(IDS_ORCHECKGEOMETRIEXML));
			VERIFY(bstrNameM.LoadString (IDS_CHECKGEOMETRIECAP));
			VERIFY(bstrNameO.LoadString (IDS_ORCHECKGEOMETRIECAP));
			m_iMethod = PRF_GEOMETRIE;
		}
		break;

	case IDM_LINECHECK: 
		{
			VERIFY(bstrCheckM.LoadString(IDS_LINECHECKXML));
			VERIFY(bstrCheckO.LoadString(IDS_ORLINECHECKXML));
			VERIFY(bstrNameM.LoadString (IDS_LINECHECKCAP));
			VERIFY(bstrNameO.LoadString (IDS_ORLINECHECKCAP));
			m_iMethod = PRF_CODE;

		}
		break;

	case IDM_CLASSIFY: 
		{
			VERIFY(bstrCheckM.LoadString(IDS_CLASSIFYXML));
			VERIFY(bstrCheckO.LoadString(IDS_ORCLASSIFYXML));
			VERIFY(bstrNameM.LoadString (IDS_CLASSIFYCAP));
			VERIFY(bstrNameO.LoadString (IDS_ORCLASSIFYCAP));
			m_iMethod = PRF_CODE;

		}
		break;

	case IDM_CLASSIFYWINDOW: 
		{
			VERIFY(bstrCheckM.LoadString(IDS_CLASSIFYWINDOWXML));
			VERIFY(bstrCheckO.LoadString(IDS_ORCLASSIFYWINDOWXML));
			VERIFY(bstrNameM.LoadString (IDS_CLASSIFYWINDOWCAP));
			VERIFY(bstrNameO.LoadString (IDS_ORCLASSIFYWINDOWCAP));
			m_iMethod = PRF_CODE;

		}
		break;


	default:
		break;
	}


	WPropertySequenceService Service (CLSID_PropertySequenceService);
	WProgressIndicator Status (CLSID_ProgressIndicator);
	HWND hWnd = AfxGetMainWnd()->GetSafeHwnd();
	char cbBuffer[_MAX_PATH];

		GetModuleFileName(_Module.GetModuleInstance(), cbBuffer, sizeof(cbBuffer));
		Service -> put_ResourceModule(CComBSTR(cbBuffer));

		Status -> InitNew (hWnd, PIFLAG_RESULT);
		if (bMainData) {

		// Menupunkt im Hauptfenster
			hr = Service -> RunActionSequence(reinterpret_cast<INT_PTR>(hWnd), bstrCheckM, 
					bstrNameM, CComBSTR(""), WProgressIndicator2(Status), NULL, VARIANT_FALSE, NULL);

		}
		else {
		// Menupunkt in einem Recherchefenster
			hr = Service -> RunActionSequence(reinterpret_cast<INT_PTR>(hWnd), bstrCheckO, 
					bstrNameO, CComBSTR(""), WProgressIndicator2(Status), NULL, VARIANT_FALSE, NULL);
		}


		if (S_OK != hr) {
			if (E_ABORT == hr)
				return hr;

			if (CLASS_E_NOTLICENSED != hr) {
			// zusätzliche Meldung, nur wenn kein Lizensierungsfehler
			CString strMessage;

				USES_CONVERSION;
				VERIFY(strMessage.LoadString(IDS_NOWORKING));

				if (bMainData) 
					AfxGetMainWnd()->MessageBox (strMessage, OLE2A(bstrNameM), MB_OK | MB_ICONERROR);
				else
					AfxGetMainWnd()->MessageBox (strMessage, OLE2A(bstrNameO), MB_OK | MB_ICONERROR);
			}

			return hr;
		}

	} COM_CATCH;
	return S_OK;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////