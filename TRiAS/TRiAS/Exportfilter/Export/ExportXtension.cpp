// @doc
// @module Export.cpp | Implementation of the <c CExportXtension> class

#include "stdafx.h"
#include "ExportImpl.h"

#include <xtension.h>		// Definition aller Erweiterungs- spezifischen
#include <xtensnx.h>		// Konstanten und Datenstrukturen

#include <ixtensn.hxx>		// Interfaces einer Erweiterung
#include <xtencatl.hxx>		// InterfaceImplementation der BasisKlasse
#include <xtsnaux.hxx>
#include <tstring>
#include <Registrx.hxx>


#include "ExportXtension.h"

#include <ipropseq.hxx>

#include <xtsnguid.h>
#include <SrChoice.h>
#include <selidprp.h>
#include <SelectExportObjectsGuid.h>

#include <hpp/waitcur.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// sonstiges
#define EXPORT_POSITION		2		// Position im Hauptmenu

#if defined(_USE_XML_GEOCOMPONENTS)
HRESULT LoadPropertySequence( const CComBSTR& strName, IPropertyActionSequence** ppPropertyActionSequence );
HRESULT SavePropertySequence( const CComBSTR& strName, IPropertyActionSequence* pPropertyActionSequence );
HRESULT CreateMainPropertySequence( const CComBSTR& strName, DWORD dwFlags, IPropertyActionSequence** ppPropertyActionSequence );
HRESULT CreateORPropertySequence( const CComBSTR& strName, DWORD dwFlags, IPropertyActionSequence** ppPropertyActionSequence );
#endif // defined(_USE_XML_GEOCOMPONENTS)

/////////////////////////////////////////////////////////////////////////////
// SmartIF's

DefineSmartInterface(PropertyActionSequence)
DefineSmartInterface(PropertyAction)
DefineSmartInterface(ClassProperty)
DefineSmartInterface(PropertyInfo)

/////////////////////////////////////////////////////////////////////////////
// Liefert den CLSID des TRiAS-Zusatzmodules Export
BOOL GetExtensionCLSID (CLSID &rClsID) 
{
	rClsID = CLSID_ExportXTension;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CExportXtension

/////////////////////////////////////////////////////////////////////////////
// InitExtension wird nach erfolgreichem Laden des Zusatzmodules gerufen 
STDMETHODIMP_(BOOL) CExportXtension::InitExtension (short iMode) 
{
	if (!CTriasExtension::InitExtension (iMode))
		return FALSE;
	/////////////////////////////////////////////////////////////////////////////
	// Menüpunkt im Hauptmenu austauschen
	m_iMainMenu = InstallMenuItem(IDM_EXPORTDATA, IDS_MENUENTRY, IMINormalMenu, EXTRA_MENU_POS, EXPORT_POSITION);
	RemoveMenuItem(IDM_EXPORT_ORIG, IMINormalMenu | IMIOrigMenuItem, EXTRA_MENU_POS);
	/////////////////////////////////////////////////////////////////////////////
	// Menüpunkt im OR-Menu austauschen
	m_iORMenu = InstallMenuItem(IDM_EXPORTDATA, IDS_ORMENUENTRY, IMIObjWnd, -1, 0 );
	RemoveMenuItem(IDM_EXPORT_ORIG, IMIObjWnd | IMIOrigMenuItem, -1 );

// unseren aktuellen Namen besorgen
	{
	CCurrentUser regCfg (KEY_READ, TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Config"));
	DWORD dwSize = _MAX_PATH;

		if (!regCfg.GetSubSZ ("TRiASName", g_szTRiAS, dwSize))
			strcpy (g_szTRiAS, "TRiAS®");		// default
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// UnLoadExtension wird vor dem Entladen des Zusatzmodules gerufen
STDMETHODIMP_(BOOL) CExportXtension::UnLoadExtension (void) 
{
	RemoveMenuItem (IDM_EXPORTDATA + MenuOffset(), IMINormalMenu | IMIOrigMenuItem, EXTRA_MENU_POS);
	RemoveMenuItem (IDM_EXPORTDATA + MenuOffset(), IMIObjWnd | IMIOrigMenuItem, OR_EXTRA_MENU_POS);
	return CTriasExtension::UnLoadExtension();
}

/////////////////////////////////////////////////////////////////////////////
// Menuhandling
STDMETHODIMP_(BOOL) CExportXtension::MenuCommand (WPARAM wParam, HWND hWnd) 
{
HRESULT	hr = E_FAIL;

	switch (wParam) {
	case IDM_EXPORTDATA: 
		{
		// KK991117
		CWaitCursor Wait;
		WXMLDocument pXMLDocument;

			m_bHaveXML = m_bHaveEngines = FALSE;
			if (SUCCEEDED(pXMLDocument.CreateInstance (CLSID_XMLDocument)))
				m_bHaveXML = TRUE;

			if (m_bHaveXML && S_OK == TestExistsEngine()) 
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

			hr = OnExportData ((NULL == hWnd) ? true : false);
			::CoFreeUnusedLibraries();
		}
		break;

	default:
		break;
	}
	return S_OK == hr ? TRUE : FALSE;
}

STDMETHODIMP_(BOOL) CExportXtension::MenuInit (HMENU hMenu, LPARAM lParam, HWND hWnd) 
{
	::EnableMenuItem (hMenu, IDM_EXPORTDATA + MenuOffset(), m_bHaveXML ? MF_ENABLED : MF_GRAYED);
	return TRUE;
}

// AFXPRIV.H:
#define WM_SETMESSAGESTRING 0x0362  // wParam = nIDS (or 0),
									// lParam = lpszOther (or NULL)

STDMETHODIMP_(BOOL) CExportXtension::MenuSelect (UINT uiMenuID, HMENU hMenu, HWND hWnd) 
{
	switch (uiMenuID) {
	case IDM_EXPORTDATA:
		{
//		return AfxGetMainWnd() -> SendMessage (WM_SETMESSAGESTRING, NULL == hWnd ? IDS_EXPORTDATA : IDS_OREXPORTDADA);
		CString str;

			VERIFY(str.LoadString(IDS_EXPORTDATA));
			return DEX_SetMessageString((LPCSTR)str);
		}

	default:
		break;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Menubefehle

#if defined(_USE_XML_GEOCOMPONENTS)
// Instantiieren der Geokomponenten über XML-Resource

HRESULT CExportXtension::OnExportData(bool bMainData) 
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
			VERIFY(bstrName.LoadString (IDS_EXPORTCAP));
			hr = Service -> RunActionSequence(reinterpret_cast<INT_PTR>(hWnd), CComBSTR("ExportDataOKS.xml"), 
					bstrName, CComBSTR(""), WProgressIndicator2(Status), NULL, VARIANT_FALSE, NULL);
		}
		else {
		// Menupunkt in einem Recherchefenster
			VERIFY(bstrName.LoadString (IDS_OREXPORTCAP));
			hr = Service -> RunActionSequence(reinterpret_cast<INT_PTR>(hWnd), CComBSTR("ExportDataORWnd.xml"), 
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
				VERIFY(strMessage.LoadString(IDS_NOEXPORT));
				AfxGetMainWnd()->MessageBox (strMessage, OLE2A(bstrName), MB_OK | MB_ICONERROR);
			}
//			Status -> WasCanceled();
			return hr;
		}

	} COM_CATCH;
	return S_OK;
}

#else

// bisherige, direkte Variante
#include <PropGuid.h>

HRESULT CExportXtension::OnExportData( bool bMainData ) 
{
	COM_TRY {
	DWORD dwFlags = 0L;
	CComBSTR strName;
	UINT nCaptID = bMainData ? IDS_EXPORTCAP : IDS_OREXPORTCAP;

		USES_CONVERSION;
		VERIFY(strName.LoadString (nCaptID));

	WPropertyActionSequence pPropertyActionSequence;

		if ((::GetKeyState(VK_SHIFT) & 0x8000 && ::GetKeyState(VK_CONTROL) & 0x8000) ||
			FAILED(LoadPropertySequence(strName, pPropertyActionSequence.ppi()))) 
		{
			if (bMainData) {
				RETURN_FAILED_HRESULT(CreateMainPropertySequence (strName, dwFlags, pPropertyActionSequence.ppi()));
			} else {
				RETURN_FAILED_HRESULT(CreateORPropertySequence (strName, dwFlags, pPropertyActionSequence.ppi()));
			}
		}

		ERROR_EXPR_FALSE(pPropertyActionSequence.IsValid(), E_FAIL);
	
	WProgressIndicator	pProgressIndicator(CLSID_ProgressIndicator);
	
		pProgressIndicator->InitNew( MWind()->GetSafeHwnd(), PIFLAG_RESULT);
	
	HRESULT hr = pPropertyActionSequence -> DoActions (MWind() -> GetSafeHwnd(), pProgressIndicator, NULL, NULL);

		if (E_ABORT == hr)
			return hr;

	// KK991126
		if (S_OK != hr) {
			if (CLASS_E_NOTLICENSED != hr) {
			// zusätzliche Meldung, nur wenn kein Lizensierungsfehler
			CString strCaption;
			CString strMessage;

				VERIFY(strCaption.LoadString(nCaptID));
				VERIFY(strMessage.LoadString(IDS_NOEXPORT));
				AfxGetMainWnd()->MessageBox (strMessage, strCaption, MB_OK | MB_ICONERROR);
			}
			pProgressIndicator->WasCanceled();
			return hr;
		}

		ERROR_FAILED_HRESULT(SavePropertySequence( strName, pPropertyActionSequence ), E_FAIL);
		DEX_SetDirtyGeoDB(true);

	} COM_CATCH;
	return S_OK;
}

static LPCOLESTR g_cbPropertySequences = L"PropertySequences";

static HRESULT MakeStreamname( const CComBSTR& strDescription, CComBSTR& strStreamname ) 
{
	TCHAR	_buf[32];
	USES_CONVERSION;
	LPCTSTR	lpszStreamname = W2A( strDescription );
	for( int i = 0; *lpszStreamname && i != _countof(_buf) - 1; ++i, ++lpszStreamname ) 
	{
		_buf[i] = isalnum(*lpszStreamname) ? *lpszStreamname : _T('_');
	}
	_buf[i] = _T('\0');
	strStreamname = _buf;
	return S_OK;
}

static HRESULT OpenStorage( LPCOLESTR lpoleStoragename, DWORD dwMode, IStorage* pParent, IStorage** ppIStorage ) 
{
	dwMode |= STGM_SHARE_EXCLUSIVE | STGM_TRANSACTED;
	return pParent->OpenStorage( lpoleStoragename, NULL, dwMode, NULL, 0, ppIStorage );
}

static HRESULT OpenPropSeqStorage( DWORD dwMode, IStorage** ppStorage ) 
{
	WStorage	pStorageRoot;
	WStorage	pStorage;
	HRESULT		hr;

// KK000107
	if ( !DEX_GetProjectStorage( *pStorageRoot.ppv() ) )
		return E_FAIL;

//	RETURN_FAILED_HRESULT( TRUE == DEX_GetProjectStorage( *pStorageRoot.ppv() ) );

	if( FAILED( hr = OpenStorage( g_cbPropertySequences, dwMode, pStorageRoot, pStorage.ppi() ) ) ) {
		if( !(STGM_WRITE & dwMode) && !(STGM_READWRITE & dwMode) )
			return E_FAIL;
		RETURN_FAILED_HRESULT( pStorageRoot->CreateStorage( g_cbPropertySequences, STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_TRANSACTED | STGM_CREATE, 0L, 0L, pStorage.ppi() ) );
		RETURN_FAILED_HRESULT( pStorage->SetClass( CLSID_PropertyActionSequence ) );
	}
	*ppStorage = pStorage.Detach();
	return S_OK;
}

HRESULT CreateMainPropertySequence( const CComBSTR& strSequenceName, DWORD dwFlags, IPropertyActionSequence** ppPropertyActionSequence ) 
{
WPropertyActionSequence	pPropertyActionSequence;

	COM_TRY {
	CComBSTR	strName;

		USES_CONVERSION;
	
		pPropertyActionSequence = WUnknown( CLSID_PropertyActionSequence );
		THROW_FAILED_HRESULT(WPersistStreamInit(pPropertyActionSequence) -> InitNew());
		THROW_FAILED_HRESULT(pPropertyActionSequence -> SetDescription( W2A(strSequenceName) ));

	WPropertyActionSequence Choice (CLSID_PropertyChoice);	// erste Seite enthält 2 PropPages

		THROW_FAILED_HRESULT(WPersistStreamInit(Choice) -> InitNew());

	WPropertyAction SelDataSrc (CLSID_SelectObjectsDatasource);	// Selektion aus Datenquellen

		VERIFY(strName.LoadString (IDS_DATASOURCE_NAME));
		THROW_FAILED_HRESULT(WPersistStreamInit(SelDataSrc) -> InitNew());
		THROW_FAILED_HRESULT(WClassProperty(SelDataSrc) -> GetPropInfo (NULL, 0, &dwFlags));
		THROW_FAILED_HRESULT(WPropertyInfo(SelDataSrc) -> SetPropInfo (W2A(strName), dwFlags));
		THROW_FAILED_HRESULT(Choice -> AddAction (SelDataSrc));

	WPropertyAction SelOKS (CLSID_SelectIdentObjTyp);			// Selektion über OKS/OTyp

		VERIFY(strName.LoadString (IDS_OKSOTYP_NAME));
		THROW_FAILED_HRESULT(WPersistStreamInit(SelOKS) -> InitNew());
		THROW_FAILED_HRESULT(WClassProperty(SelOKS) -> GetPropInfo (NULL, 0, &dwFlags));
		THROW_FAILED_HRESULT(WPropertyInfo(SelOKS) -> SetPropInfo (W2A(strName), dwFlags));
		THROW_FAILED_HRESULT(Choice -> AddAction (SelOKS));

		THROW_FAILED_HRESULT(pPropertyActionSequence -> AddAction (WPropertyAction(Choice)));		// erste Seite zur Folge hinzufügen

	WPropertyAction Export (CLSID_ExportPropertyAction);

		THROW_FAILED_HRESULT(WPersistStreamInit(Export) -> InitNew());
		THROW_FAILED_HRESULT(pPropertyActionSequence -> AddAction (Export));		// zweite Seite zur Folge hinzufügen
		*ppPropertyActionSequence = pPropertyActionSequence.Detach();

	} COM_CATCH;
	return S_OK;
}

HRESULT CreateORPropertySequence( const CComBSTR& strSequenceName, DWORD dwFlags, IPropertyActionSequence** ppPropertyActionSequence ) 
{
WPropertyActionSequence	pPropertyActionSequence;

	COM_TRY {
	CComBSTR	strName;

		USES_CONVERSION;
		pPropertyActionSequence = WUnknown( CLSID_PropertyActionSequence );
		THROW_FAILED_HRESULT(WPersistStreamInit(pPropertyActionSequence) -> InitNew());
		THROW_FAILED_HRESULT(pPropertyActionSequence -> SetDescription( W2A(strSequenceName) ));

	WPropertyAction ObjWnd(CLSID_SelectFromObjectWindow);

		THROW_FAILED_HRESULT(WPersistStreamInit(ObjWnd) -> InitNew());
		THROW_FAILED_HRESULT(pPropertyActionSequence -> AddAction (ObjWnd));		// zweite Seite zur Folge hinzufügen

	WPropertyAction Export (CLSID_ExportPropertyAction);

		THROW_FAILED_HRESULT(WPersistStreamInit(Export) -> InitNew());
		THROW_FAILED_HRESULT(pPropertyActionSequence -> AddAction (Export));		// zweite Seite zur Folge hinzufügen
		*ppPropertyActionSequence = pPropertyActionSequence.Detach();

	} COM_CATCH;
	return S_OK;
}

HRESULT LoadPropertySequence( const CComBSTR& strName, IPropertyActionSequence** ppPropertyActionSequence ) 
{
	WStorage	pStorage;
	CComBSTR	strStreamname;
	WStream		pStream;
	if( FAILED( OpenPropSeqStorage( STGM_READ, pStorage.ppi() ) ) )
		return E_FAIL;
	RETURN_FAILED_HRESULT( MakeStreamname( strName, strStreamname ) );
	if( FAILED( pStorage->OpenStream( strStreamname, NULL, STGM_READ | STGM_SHARE_EXCLUSIVE, 0, pStream.ppi() ) ) )
		return E_FAIL;
	WPropertyActionSequence	pPropertyActionSequence;
	RETURN_FAILED_HRESULT( ::OleLoadFromStream( pStream, pPropertyActionSequence.GetIID(), pPropertyActionSequence.ppv() ) );
	*ppPropertyActionSequence = pPropertyActionSequence.Detach();
	return S_OK;
}

HRESULT SavePropertySequence( const CComBSTR& strName, IPropertyActionSequence* pPropertyActionSequence ) 
{
	WStorage	pStorage;
	CComBSTR	strStreamname;
	WStream		pStream;
	if( FAILED( OpenPropSeqStorage( STGM_READWRITE, pStorage.ppi() ) ) )
		return E_FAIL;
	RETURN_FAILED_HRESULT( MakeStreamname( strName, strStreamname ) );
	if( FAILED( pStorage->OpenStream( strStreamname, NULL, STGM_CREATE | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, pStream.ppi() ) ) ) {
		RETURN_FAILED_HRESULT( pStorage->CreateStream( strStreamname, STGM_CREATE | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, pStream.ppi() ) );
	}
	WPersistStream		pPersistStream;
	RETURN_FAILED_HRESULT( pPropertyActionSequence->QueryInterface( pPersistStream.GetIID(), pPersistStream.ppv() ) );
	RETURN_FAILED_HRESULT( ::OleSaveToStream( pPersistStream, pStream ) );
	RETURN_FAILED_HRESULT( pStream->Commit( STGC_DEFAULT ) );
	RETURN_FAILED_HRESULT( pStorage->Commit( STGC_DEFAULT ) );
	return S_OK;
}

#endif // defined(_USE_XML_GEOCOMPONENTS)
