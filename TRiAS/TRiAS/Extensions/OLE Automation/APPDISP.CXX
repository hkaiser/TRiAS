// Eigentliche programmierSchnittstelle von Trias.Application -----------------
// File: APPDISP.CXX

#include "precomp.hxx"

#include <triastlb.h>		// TypeLibrary
#include <dirisole.h>
#include <fmfcguid.h>
#define ATL_NO_NAMESPACE
#include <ciid.h>

#include "oleautor.h"

#include "docarray.hxx"
#include "enumdocs.hxx"
#include "doc.hxx"
#include "docs.hxx"		// Documents.Collection

#include "TRiASNotify.h"
#include "TRiASNotifyDual.h"
#include "ObjectProperty.h"
#include "ObjectPropertyDual.h"
#include "connect.hxx"
#include "Strings.h"

#define __DToolBar_h__
#include <itoolbar.h>
#include <toolguid.h>

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#include <TRiASHelper.h>

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ObjectProperty);			// WTRiASLockFeature
DefineSmartInterface(InitInnerObject);			// WInitInnerObject

///////////////////////////////////////////////////////////////////////////////
// Guids etc.
EXTERN_C const CLSID __declspec(selectany) CLSID_FakeTRiASLockFeature = {0x26A3BD85,0x6D09,0x11D2,{0x9E,0xE7,0x00,0x60,0x08,0x44,0x78,0x00}};
EXTERN_C const IID __declspec(selectany) IID_IInitInnerObject = {0x58DAD7D6,0x6F34,0x11D2,{0x9E,0xEC,0x00,0x60,0x08,0x44,0x78,0x00}};

///////////////////////////////////////////////////////////////////////////////
// 
EXTERN_C const IID CLSID_TRiASToolBar;

DefineSmartInterface(Dispatch);
DefineSmartInterface2(DDocument, IID_DDocument);
//DefineSmartInterface(PersistStreamInit);
DefineSmartInterface2(DControlToolBar, IID_DControlToolBar);		// WDControlToolBar
DefineSmartInterface2(DControlToolBars, IID_DControlToolBars);		// WDControlToolBars

DefineSmartInterface(TRiASBarContainer);
DefineSmartInterface(TRiASBar);
DefineSmartInterface(ExtendBScript);				// WExtendBScript

///////////////////////////////////////////////////////////////////////////////
// ProgrammabilityInterfaceMethods 
// Properties dieses Interfaces 
STDMETHODIMP CTriasApp::get_isA (LONG *plRTTI)
{
	if (NULL == plRTTI) 
		return E_POINTER;
	*plRTTI = RTTI_Application;
	return NOERROR;
}

STDMETHODIMP CTriasApp::get_Value (BSTR *pbstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == pbstrValue) return E_POINTER;

CString rsAppValue;

	TRY {
		rsAppValue.Format (IDS_APPVALUE, g_cbTRiAS);
	} CATCH (CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH

	USES_CONVERSION;
	*pbstrValue = SysAllocString (A2OLE(rsAppValue));
	if (NULL == *pbstrValue)
		return E_OUTOFMEMORY;
			
return NOERROR;
}

STDMETHODIMP CTriasApp::get_Version (BSTR *pbstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == pbstrValue) return E_POINTER;

CString rsAppVersion;

	TRY {
	char *pT = rsAppVersion.GetBuffer(_MAX_PATH);
		
		if (!DEX_GetTRiASVersion (pT))
			AfxThrowMemoryException();
		rsAppVersion.ReleaseBuffer();

	} CATCH (CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH

	USES_CONVERSION;
	*pbstrValue = SysAllocString (A2OLE(rsAppVersion));
	if (NULL == *pbstrValue)
		return E_OUTOFMEMORY;
			
return NOERROR;
}

STDMETHODIMP CTriasApp::get_VersionLong (long *plValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == plValue) 
		return E_POINTER;

	*plValue = DEX_GetTRiASVersionLong();
	return S_OK;
}

STDMETHODIMP CTriasApp::get_Parent (IDispatch **ppIParent)
{
	return ((_DApplication *)this)->QueryInterface (IID_IDispatch, (LPVOID *)ppIParent);
}

STDMETHODIMP CTriasApp::get_Application (IDispatch **ppIApp)
{
	return ((_DApplication *)this)->QueryInterface (IID_IDispatch, (LPVOID *)ppIApp);
}

STDMETHODIMP CTriasApp::put_Parent (IDispatch *pIDisp)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTriasApp::put_Application (IDispatch *pIDisp)
{
	return E_NOTIMPL;
}

// DateiName der Applikation (ohne Pfad) --------------------------------------
STDMETHODIMP CTriasApp::get_Name (BSTR *pbstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == pbstrValue) return E_POINTER;

CString strName;

	TRY {
		strName.Format (IDS_FULLTRIASNAME, g_cbTRiAS);
	} CATCH (CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH

	*pbstrValue = SysAllocString (WideString(strName));
	if (NULL == *pbstrValue) 
		return E_OUTOFMEMORY;
	
return NOERROR;
}


// Besorgen des Verzeichnisses, aus dem Applikation gestartet wurde -----------
STDMETHODIMP CTriasApp::get_StartupPath (BSTR *pbstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == pbstrValue) return E_POINTER;

HINSTANCE hModule = GetModuleHandle (NULL);
char cbName[_MAX_PATH+1];
	
	GetModuleFileName (hModule, cbName, _MAX_PATH);	// ModuleNamen holen

string strName = cbName;

	strName = get_drive (strName) + get_path (strName);
	*pbstrValue = SysAllocString (WideString (strName.c_str()));
	if (NULL == *pbstrValue)
		return E_OUTOFMEMORY;

	return NOERROR;
}

// Aktuellen DatenPfad besorgen -----------------------------------------------
// (ist im Moment gleich dem aktuellen Verzeichnis) 
STDMETHODIMP CTriasApp::get_DefaultFilePath (BSTR *pbstrPath)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == pbstrPath) return E_POINTER;
	
// von Trias den aktuellen DatenPfad holen
char cbDefPath[_MAX_PATH+1];
	
	memset (cbDefPath, '\0', _MAX_PATH);
	if (DEX_GetDefaultDataPath (cbDefPath) != NULL) 
		*pbstrPath = SysAllocString (WideString(cbDefPath));
	if (NULL == *pbstrPath) 
		return E_OUTOFMEMORY;
	
return NOERROR;
}

STDMETHODIMP CTriasApp::put_DefaultFilePath (BSTR bstrPath)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == bstrPath) return E_UNEXPECTED;
		
// neuen Pfad einstellen
	DEX_SetDefaultDataPath (AnsiString(bstrPath));
	return NOERROR;		
}

// Pfad und Namen der Applikation holen ---------------------------------------
STDMETHODIMP CTriasApp::get_FullName (BSTR *pbstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == pbstrValue) return E_POINTER;

HINSTANCE hModule = GetModuleHandle(NULL);
char cbName[_MAX_PATH+1];

	GetModuleFileName (hModule, cbName, _MAX_PATH);	// ModuleNamen holen
	*pbstrValue = SysAllocString (WideString(cbName));
	if (NULL == *pbstrValue)
		return E_OUTOFMEMORY;
			
	return NOERROR;
}

STDMETHODIMP CTriasApp::get_Visible (VARIANT_BOOL *piVisible)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == piVisible) return E_POINTER;

// aktuellen Stand liefern
	*piVisible = DEXI_isAppWindowVisible() ? VARIANT_TRUE : VARIANT_FALSE;
	return NOERROR;
}

STDMETHODIMP CTriasApp::put_Visible (VARIANT_BOOL iVisible)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

// versuchen, Parameter auszuwerten
BOOL fIsVisible = DEXI_isAppWindowVisible();

// evtl. AnzeigeStatus der Applikation verändern
CWinApp *pApp = AfxGetApp();

	if (fIsVisible && !iVisible) {
		DEX_HideAppWindow();

		AfxOleSetUserCtrl(FALSE);
		if (NULL != pApp && NULL != pApp->m_pMainWnd)
			pApp->m_pMainWnd->EnableWindow(FALSE);
	}
	else if (!fIsVisible && iVisible) {
		if (NULL != pApp && NULL != pApp->m_pMainWnd)
			pApp->m_pMainWnd->EnableWindow(TRUE);
		AfxOleSetUserCtrl(TRUE);
		DEX_ShowAppWindow (SW_SHOW);
	}
	return NOERROR;
}

STDMETHODIMP CTriasApp::get_Interactive (VARIANT_BOOL *piInteractive)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == piInteractive) return E_POINTER;

	*piInteractive = DEXI_isInteractive() ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTriasApp::put_Interactive (VARIANT_BOOL iInteractive)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	return E_NOTIMPL;
}

// Projekt neu erzeugen und zur Liste der geöffneten Projekte hinzufügen ------
// Parameter:	vName	ProjektName (evtl. voller Pfad, sonst im StandardVerzeichnis)
// 		vUser	[optional] neu anzulegender Nutzer
//		vPassWd	[optional] für den Nutzer zu definierendes PassWord
//		vMode	[optional] OpenMode des neu erzeugten Projektes
//				s. enum OPENMODE
STDMETHODIMP CTriasApp::NewDocument (BSTR bstrName, VARIANT vUser, VARIANT vPassWd, VARIANT vMode, DDocument **ppIDoc)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	TEST_E_POINTER("CTriasApp::NewDocument", ppIDoc);

// Initialisierung der ArgumentVariants
CComVariant vArgUser; 
CComVariant vArgPassWd;
CComVariant vArgMode; 
	
// versuchen, Parameter auszuwerten
string strName (AnsiString(bstrName));
string strUser;		// default: kein NutzerName
string strPassWd;	// default: kein PassWort
short iMode = OPENMODE_Normal;	// default: normal eröffnen
	
	COM_TRY {
	// 2. UserName
	HRESULT hr = VariantChangeType (&vArgUser, &vUser, 0, VT_BSTR);

		if (SUCCEEDED(hr)) 
			strUser = AnsiString(V_BSTR(&vArgUser));
		else {
			hr = VariantChangeType (&vArgUser, &vUser, 0, VT_ERROR);
			if (SUCCEEDED(hr) && V_ERROR(&vArgUser) == DISP_E_PARAMNOTFOUND) {
			// Parameter ausgelassen, defaultwert verwenden (== pName)
				strUser = get_name (strName);
				strlwr (&strUser[0]);
			} else
				_com_issue_error(DISP_E_PARAMNOTFOUND);	// mit Fehler raus
		}

	// 3. PassWort
		hr = VariantChangeType (&vArgPassWd, &vPassWd, 0, VT_BSTR);
		if (SUCCEEDED(hr)) 
			strPassWd = AnsiString(V_BSTR(&vArgPassWd));
	
	// 4. Mode
		hr = VariantChangeType (&vArgMode, &vMode, 0, VT_I2);
		if (SUCCEEDED(hr)) 
			iMode = V_I2(&vArgMode);

	// DatenBasis mit gegebenen Parametern anlegen und evtl. eröffnen
		{
		CREATEDB cDB;
		CGeoDoc *pDoc = NULL;
		
			INITSTRUCT (cDB, CREATEDB);
			cDB.m_pName = (char *)strName.c_str();
			cDB.m_pUser = (char *)strUser.c_str();
			cDB.m_pPassWd = (char *)strPassWd.c_str();
			cDB.m_iMode = iMode;
			
		// GeoDB erzeugen
		ErrCode EC = DEX_CreateNewGeoDB(cDB);	// Projekt eröffnen

			if (EC != EC_OKAY) 		// Fehler aufgetreten
				_com_issue_error(ErrorFromErrCode (EC));
			
		// GeoDB eröffnen
			EC = DEX_OpenProject(cDB);	// Projekt eröffnen
			if (EC != EC_OKAY && EC != WC_RETURN)			// Fehler aufgetreten
				_com_issue_error(ErrorFromErrCode (EC));
			
		// Add to GeoDoc Tree
		WDDocument Doc;

			THROW_FAILED_HRESULT(FGetDocDisp (strName.c_str(), &pDoc, Doc.ppi(), DOCMODE_Add));
			*ppIDoc = Doc.detach();

			if (iMode & OPENMODE_HideDocument) {
			CWinApp *pApp = AfxGetApp();

				AfxOleSetUserCtrl(FALSE);
				if (NULL != pApp && NULL != pApp->m_pMainWnd)
					pApp->m_pMainWnd->EnableWindow(FALSE);
			}
			else {
				AfxOleSetUserCtrl(TRUE);
				DEX_RePaintWait();
			}
			return S_OK;		// raus hier
		} 

	} COM_CATCH;
	return E_UNEXPECTED;
}


// Projekt zur Liste der geöffneten Projekte hinzufügen -----------------------
// Parameter:	vName	ProjektName (evtl. voller Pfad, sonst im StandardVerzeichnis)
//		vUser	Projekt für diesen Nutzer eröffnen
//		vPassWd	[optional] NutzerPassWord
//		vMode	[optional] Modi beim Eröffnen des Projektes
STDMETHODIMP CTriasApp::OpenDocument (BSTR bstrName,
		VARIANT vUser, VARIANT vPassWd, VARIANT vMode, DDocument **ppIDoc)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	TEST_E_POINTER("CTriasApp::OpenDocument", ppIDoc);

// Initialisierung der ArgumentVariants
CComVariant vArgUser;
CComVariant vArgPassWd;
CComVariant vArgMode;

// versuchen, Parameter auszuwerten
string strName (AnsiString(bstrName));
string strUser;		// default: kein NutzerName
string strPassWd;	// default: kein PassWort
short iMode = OM_Normal;	// default: normal eröffnen
	
	try {
	// 2. UserName
	HRESULT hr = VariantChangeType (&vArgUser, &vUser, 0, VT_BSTR);

		if (SUCCEEDED(hr)) 
			strUser = AnsiString(V_BSTR(&vArgUser));
		else {
			hr = VariantChangeType (&vArgUser, &vUser, 0, VT_ERROR);
			if (SUCCEEDED(hr) && V_ERROR(&vArgUser) == DISP_E_PARAMNOTFOUND) {
			// Parameter ausgelassen, defaultwert verwenden (== pName)
				strUser = get_name (strName);
				strlwr (&strUser[0]);
			} else
				_com_issue_error(DISP_E_PARAMNOTFOUND);	// mit Fehler raus
		}

	// 3. PassWort
		hr = VariantChangeType (&vArgPassWd, &vPassWd, 0, VT_BSTR);
		if (SUCCEEDED(hr)) 
			strPassWd = AnsiString(V_BSTR(&vArgPassWd));
	
	// 4. Mode
		hr = VariantChangeType (&vArgMode, &vMode, 0, VT_I2);
		if (SUCCEEDED(hr)) 
			iMode = V_I2(&vArgMode);

	// DatenBasis mit gegebenen Parametern eröffnen
	WDDocument Doc;

		THROW_FAILED_HRESULT(OpenDocument (strName.c_str(), 
			strUser.c_str(), strPassWd.c_str(), iMode, 0, Doc.ppi()));
		*ppIDoc = Doc.detach();

		if (iMode & OPENMODE_HideDocument) {
		CWinApp *pApp = AfxGetApp();

			AfxOleSetUserCtrl(FALSE);
			if (NULL != pApp && NULL != pApp->m_pMainWnd)
				pApp->m_pMainWnd->EnableWindow(FALSE);
		}
		else {
			AfxOleSetUserCtrl(TRUE);
		}

	// hier durchfallen
	// ...
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}
	
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// DELETEDOCCOLLECTIONPROC 
extern "C" 
bool PASCAL _XTENSN_EXPORT DeleteDocFromApp (LPCSTR bName, CTriasApp *pApp)
{
	return pApp -> FInvDoc (bName);  // remove from collection only
}

// Liefert eine Collection von Docs  ----------------------
typedef struct tagENUMDOCDATA {
	CGeoDocCreator *m_pCr;
	LPUNKNOWN m_pUnk;
	CTriasApp *m_pApp;
} ENUMDOCDATA;

extern "C" 
BOOL PASCAL _XTENSN_EXPORT _GetDocsFromApp (LPCSTR bName, BOOL, void *pData)
{
ENUMDOCDATA *pEOD = (ENUMDOCDATA *)pData;
CGeoDoc *pDoc = NULL;
HRESULT hr = pEOD -> m_pApp -> FGetDocDisp (bName, &pDoc);

	if (SUCCEEDED(hr) && pEOD -> m_pCr -> InsertPtr (pDoc)) {
		ADDREF_CAST(_DDocument, pDoc);
		return true;
	}
	
return false;	
}

extern "C" 
int PASCAL _CreateDocApp (ENUMDOCDATA *pEDD, string &bName)
{
int iResult = CVExists;
CGeoDoc *pDoc = NULL;
HRESULT hr = pEDD -> m_pApp -> FGetDocDisp (bName.c_str(), &pDoc);

	if (FAILED(hr)) {
		hr = pEDD -> m_pApp -> FGetDocDisp (bName.c_str(), &pDoc, NULL, DOCMODE_Add);
		iResult = CVCreated;
	}
	if (SUCCEEDED(hr) && pEDD -> m_pCr -> InsertPtr (pDoc)) {
		ADDREF_CAST(_DDocument, pDoc);
		return iResult;
	}
	
return CVError;
}

///////////////////////////////////////////////////////////////////////////////
// INITDOCCOLLECTIONPROC 
extern "C" 
INITDOCSTATUS PASCAL GetDocsFromApp (
	LPUNKNOWN pUnk, CTriasApp *pApp, container_wrappers::CCreator &rCollCr, 
	DWORD, string *pbName)
{
ENUMDOCDATA EDD;

	EDD.m_pCr = (CGeoDocCreator *)&rCollCr;
	EDD.m_pUnk = pUnk;
	EDD.m_pApp = pApp;
	
	if (pbName == NULL) {			// Complete fill
		ENUMNOKEY ENK;
	
		ENK.eFcn = (ENUMNOKEYPROC)_GetDocsFromApp;	// zu rufende Funktion
		ENK.ePtr = &EDD;				// durchzureichende Daten

		if(DEX_EnumProjects (ENK))			// mit Docs füllen
           	return INITDOCSTATUS_Exists;
			
	} else {
	int iR = _CreateDocApp (&EDD, *pbName);
	
		if (iR == CVCreated) return INITDOCSTATUS_Created;
		if (iR == CVExists) return INITDOCSTATUS_Exists;
	}

return INITDOCSTATUS_Error;		
} 

// Liefert die Liste Documents ------------------------------------------------
STDMETHODIMP CTriasApp::get_Documents (DDocuments **ppIDocs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	TEST_E_POINTER("CTriasApp::get_Documents", ppIDocs);

CGeoDocs *pCGeoDocs = CGeoDocs::CreateInstance (
						(DApplication *)this, this, 
						GetDocsFromApp, NULL, DeleteDocFromApp);

	if (NULL == pCGeoDocs) return E_OUTOFMEMORY;
	
	*ppIDocs = (DDocuments *)pCGeoDocs;		// übernimmt AddRef 	
	return S_OK;
}

// Liefert ein Document -------------------------------------------------------
STDMETHODIMP CTriasApp::GetDocument (VARIANT vProj, VARIANT vMode, DDocument **ppIDoc)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	TEST_E_POINTER("CTriasApp::GetDocument", ppIDoc);

CComVariant vProjArg; 
HRESULT hr = vProjArg.ChangeType (VT_I4, &vProj);
LPCSTR pcName = NULL;
bool fToDelete = false;

	USES_CONVERSION;
	if (SUCCEEDED(hr)) {	// HPROJECT gegeben
	HPROJECT hPr = (HPROJECT)V_I4(&vProjArg);

		pcName = DEX_GetProjectName(hPr);
		fToDelete = true;
	} else {
		hr = vProjArg.ChangeType (VT_BSTR, &vProj);
		if (FAILED(hr)) return hr;

		pcName = OLE2A(V_BSTR(&vProjArg));
		if (NULL == pcName)
			return E_UNEXPECTED;
	}

CComVariant vArgMode; 
DOCMODE rgMode = DOCMODE_Get;

	hr = vArgMode.ChangeType (VT_I4, &vMode);
	if (SUCCEEDED(hr)) 
		rgMode = (DOCMODE)V_I4(&vArgMode);

	switch (rgMode) {
	case DOCMODE_Get:		// get Get Project
	case DOCMODE_Replace:	// make Project Active 
		{
		WDDocument Doc;
		HRESULT hr = FGetDocDisp (pcName, NULL, Doc.ppi(), rgMode);
					
			if (fToDelete)
				CoTaskMemFree ((LPVOID)pcName);

			if (FAILED(hr)) {
				if (hr != HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND)) 
					return hr;
				hr = S_FALSE;		// Projekt nicht vorhanden
				*ppIDoc = NULL;
			} else
				*ppIDoc = Doc.detach();
		}
		break;

	case  DOCMODE_Remove:	// Close Project 
		FDelDoc (pcName);
		if (NULL != ppIDoc)
			*ppIDoc = NULL;

		if (fToDelete)
			CoTaskMemFree ((LPVOID)pcName);
		break;
		
	default:
		break;	
	}
	return hr;
}

STDMETHODIMP CTriasApp::get_ActiveDocument (DDocument **ppIDoc)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	TEST_E_POINTER("CTriasApp::get_ActiveDocument", ppIDoc);

CString strActDoc; 

	TRY {
	char *pBuffer = strActDoc.GetBuffer (_MAX_PATH);

		if (!DEX_GetActiveProject(pBuffer)) {
			*ppIDoc = NULL;
			return S_FALSE;		// kein aktives Document
		}
		strActDoc.ReleaseBuffer();

	} CATCH (CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH	

	*ppIDoc = NULL;

HRESULT hr = FGetDocDisp (strActDoc, NULL, ppIDoc, DOCMODE_Get);

	if (FAILED(hr)) {
		if (hr != HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND)) 
			return hr;
		hr = S_FALSE;		// Projekt nicht vorhanden
	}
	return hr;
}

STDMETHODIMP CTriasApp::get_Left (long *plLeft)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == plLeft) 
		return E_POINTER;
	
	*plLeft = MoveSize (MOVESIZEACTION_GETLEFT);
	return NOERROR;
}

STDMETHODIMP CTriasApp::put_Left (long lLeft)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	MoveSize (MOVESIZEACTION_LEFT, lLeft);
	return NOERROR;
}

STDMETHODIMP CTriasApp::get_Top (long *plTop)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == plTop) 
		return E_POINTER;
	
	*plTop = MoveSize (MOVESIZEACTION_GETTOP);
	return NOERROR;
}

STDMETHODIMP CTriasApp::put_Top (long lTop)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	MoveSize (MOVESIZEACTION_TOP, 0, lTop);
	return NOERROR;
}

STDMETHODIMP CTriasApp::get_Width (long *plWidth)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == plWidth) 
		return E_POINTER;
	
	*plWidth = MoveSize (MOVESIZEACTION_GETWIDTH);
	return NOERROR;
}

STDMETHODIMP CTriasApp::put_Width (long lWidth)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	MoveSize (MOVESIZEACTION_WIDTH, 0, 0, lWidth);
	return NOERROR;
}

STDMETHODIMP CTriasApp::get_Height (long *plHeight)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == plHeight) 
		return E_POINTER;
	
	*plHeight = MoveSize (MOVESIZEACTION_GETHEIGHT);
	return NOERROR;
}

STDMETHODIMP CTriasApp::put_Height (long lHeight)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	MoveSize (MOVESIZEACTION_HEIGHT, 0, 0, 0, lHeight);
	return NOERROR;
}

/*
 * CTriasApp::MoveSize
 *
 * Purpose:
 *  Helper function for the Left, Top, Width, and Height properties
 *  that centralizes calls to GetWindowRect and SetWindowPos,
 *  reducing overall code somewhat.
 *
 * Parameters:
 *  iAction         MOVESIZEACTION enum value to indicate what
 *                  type of moving/sizing to perform
 *  x, y            long position coordinates;  x is only meaningful
 *                  with MOVESIZEACTION_LEFT, y only with _TOP
 *  cx, cy          long extents;  cx is only meaningful
 *                  with MOVESIZEACTION_WIDTH, cy only with _HEIGHT
 *
 * Return Value:
 *  long            The current x, y, cx, or cy value depending on
 *                  iAction being _GETLEFT, _GETTOP, _GETWIDTH, or
 *                  _GETHEIGHT.
 */

long CTriasApp::MoveSize (CTriasApp::MOVESIZEACTION iAction, long x, long y, long cx, long cy)
{
RECT rc;
long x1, y1, cx1, cy1;
UINT uFlags;
HWND hWnd = g_pTE -> hWnd();

	::GetWindowRect (hWnd, &rc);

CPoint pt1(rc.left, rc.top), pt2 (rc.right, rc.bottom);

	::ScreenToClient (GetParent(hWnd), &pt1);
	::ScreenToClient (GetParent(hWnd), &pt2);

//By default we'll do nothing
	x1 = pt1.x;
	y1 = pt1.y;
	cx1 = pt2.x-pt1.x;
	cy1 = pt2.y-pt1.y;
	uFlags = 0L;

	switch (iAction) {
	/*
	 * Each individual property modifies the appropriate
	 * variable x1, y1, cx1, cy1, as well as uFlags to set
	 * up SetWindowPos call.
	 */
	case MOVESIZEACTION_LEFT:
		x1 = x;
		uFlags = SWP_NOSIZE;
		break;

	case MOVESIZEACTION_TOP:
		y1 = y;
		uFlags = SWP_NOSIZE;
		break;

	case MOVESIZEACTION_WIDTH:
		cx1 = cx;
		uFlags = SWP_NOMOVE;
		break;

	case MOVESIZEACTION_HEIGHT:
		cy1 = cy;
		uFlags = SWP_NOMOVE;
		break;

	case MOVESIZEACTION_GETLEFT:
		return x1;

	case MOVESIZEACTION_GETTOP:
		return y1;

	case MOVESIZEACTION_GETWIDTH:
		return cx1;

	case MOVESIZEACTION_GETHEIGHT:
		return cy1;

	default:
		return 0;
	}

// We only get here on propety changes
	SetWindowPos (hWnd, NULL, (int)x1, (int)y1, (int)cx1, (int)cy1,
				  SWP_NOZORDER | SWP_NOACTIVATE | uFlags);

return 0;	// Irrelevant for property changes.
}

STDMETHODIMP CTriasApp::get_StatusBar (BSTR *pbstrText)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	return E_NOTIMPL;
}

STDMETHODIMP CTriasApp::put_StatusBar (BSTR bstrText)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	USES_CONVERSION;
	DEX_SetMessageString(OLE2A(bstrText));
	return NOERROR;
}

STDMETHODIMP CTriasApp::get_Caption (BSTR *pbstrText)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == pbstrText) return E_POINTER;

char cbBuffer[_MAX_PATH];
bool fOK = DEX_GetTRiASCaption(cbBuffer);
	
	USES_CONVERSION;
	*pbstrText = SysAllocString (A2OLE(cbBuffer));
	return fOK ? S_OK : S_FALSE;
}

STDMETHODIMP CTriasApp::put_Caption (BSTR bstrText)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// Methods 
STDMETHODIMP CTriasApp::Quit (VARIANT vt, int *piResult)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == piResult) return E_POINTER;

// Argument auswerten VT_BOOL ?
bool fCleanUp = false;
CComVariant vArg; 

	if (SUCCEEDED(vArg.ChangeType (VT_BOOL, &vt))) 
		fCleanUp = V_BOOL(&vArg) ? false : true;
	
// Applikation beenden (Abfrage auswerten)
	*piResult = DEX_AppQuit(fCleanUp) ? -1 : 0;
	return NOERROR;
}

// AdviseSinks registrieren, freigeben und verwalten --------------------------
DefineSmartInterface(TriasXtensionSite);
DefineSmartInterface(TRiASNotificationSink);
DefineSmartInterface(ObjectProperty);

HRESULT CTriasApp::CreateAndInitSink (
	ITriasXtensionSite *pISite, IDispatch *pIDispatch, DWORD *pdwCookie)
{
	try {
	CComObject<CTRiASNotificationSinkDisp> *pISink = NULL;

		THROW_FAILED_HRESULT(CComObject<CTRiASNotificationSinkDisp>::CreateInstance(&pISink));

	WTRiASNotificationSink Sink (pISink);		// RefCnt jetzt 1

		THROW_FAILED_HRESULT(pISink -> FInit (pIDispatch));
		THROW_FAILED_HRESULT(AtlAdvise (pISite, Sink, IID_ITRiASNotificationSink, pdwCookie));
			
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return S_OK;
}

HRESULT CTriasApp::CreateAndInitDualSink (
	ITriasXtensionSite *pISite, DTRiASNotificationSink *pDSink, DWORD *pdwCookie)
{
	try {
	CComObject<COleTRiASNotificationSinkDual> *pISink = NULL;

		THROW_FAILED_HRESULT(CComObject<COleTRiASNotificationSinkDual>::CreateInstance(&pISink));

	WTRiASNotificationSink Sink (pISink);		// RefCnt jetzt 1

		THROW_FAILED_HRESULT(pISink -> FInit (pDSink));
		THROW_FAILED_HRESULT(AtlAdvise (pISite, Sink, IID_ITRiASNotificationSink, pdwCookie));
			
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return S_OK;
}

HRESULT CTriasApp::FExternalConnect (IDispatch *pIDispatch, DWORD *pdwCookie)
{
	if (NULL == pdwCookie || NULL == pIDispatch) 
		return E_POINTER;

DTRiASNotificationSink *pISinkDual = NULL;
DWORD dwCookie = 0L;

	try {
	WTriasXtensionSite ISite;
	
		THROW_FAILED_HRESULT(g_pTE -> GetXtensionSite (ISite.ppi()));

	HRESULT hr = pIDispatch -> QueryInterface (IID_DTRiASNotificationSink, (LPVOID *)&pISinkDual);

		if (SUCCEEDED(hr)) {
		// Sink über das DTRiASNotificationSink anmelden

			THROW_FAILED_HRESULT(CreateAndInitDualSink (ISite, pISinkDual, &dwCookie));
			RELEASE(pISinkDual);

		} else if (E_NOINTERFACE == hr) {
		// normale Notifikationen anmelden (über IDispatch)

			THROW_FAILED_HRESULT(CreateAndInitSink (ISite, pIDispatch, &dwCookie));
		
		} else 
			_com_issue_error(hr);

	} catch (_com_error& hr) {
		RELEASE(pISinkDual);

		if (0 != dwCookie)
			FExternalDisconnect (dwCookie);
		return _COM_ERROR(hr);
	}

// Resultat liefern
	*pdwCookie = dwCookie;
	return S_OK;
}

STDMETHODIMP CTriasApp::Advise (IDispatch *pISink, long *plCookie)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == plCookie || NULL == pISink) 
		return E_POINTER;

	*plCookie = 0L;		// für alle Fälle

DWORD dwCookie = 0L;
WUnknown Unk (pISink);	// festhalten
HRESULT	hr = FExternalConnect (pISink, &dwCookie);

	if (SUCCEEDED(hr))
		*plCookie = (long)dwCookie;

	return hr;
}

HRESULT CTriasApp::FExternalDisconnect (DWORD dwCookie)
{
	ASSERT(0 != dwCookie);

WTriasXtensionSite ISite;
HRESULT hr = g_pTE -> GetXtensionSite (ISite.ppi());

	if (SUCCEEDED(hr)) 
		hr = AtlUnadvise (ISite, IID_ITRiASNotificationSink, dwCookie);

	return hr;
}

STDMETHODIMP CTriasApp::UnAdvise (long lCookie)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (0 != lCookie) 
		return FExternalDisconnect ((DWORD)lCookie);

return E_UNEXPECTED;
}

HRESULT CTriasApp::CreateAndInitDualObjProp (DObjectProperty *pDObjProp, LONG *plCookie)
{
	if (NULL == plCookie) return E_POINTER;
	*plCookie = 0L;

	COM_TRY {
	// Objekteigenschaft über ihr DObjectProperty einbinden
	WObjectProperty ObjProp;
	CComObject<COleObjectPropertyDual> *pIObjPropDual = NULL;

		THROW_FAILED_HRESULT(CComObject<COleObjectPropertyDual>::CreateInstance(&pIObjPropDual));
		ObjProp = pIObjPropDual;		// RefCnt jetzt 1
		THROW_FAILED_HRESULT(pIObjPropDual -> FInit (pDObjProp));

	// Aggregation mit dem unbekannten
	WObjectProperty Prop (ObjProp);
	WInitInnerObject FakeLock (CLSID_FakeTRiASLockFeature);

		FakeLock -> SetInnerObject (ObjProp, IID_IObjectProperty, Prop.ppu());
		if (!Prop.IsValid())
			Prop = ObjProp;

	// Objekteigenschaft registrieren und initialisieren
		*plCookie = ((OLE2AutoExtension *)g_pTE) -> AddPropertyFunction (Prop);
		if (0 == *plCookie) _com_issue_error(E_FAIL);

	BOOL fSuccess = true;

		pIObjPropDual -> Init (this, &fSuccess);	// Server-Initialisierung fehlgeschlagen
		if (!fSuccess) _com_issue_error(E_FAIL);
	
	} COM_CATCH;
	return S_OK;
}

HRESULT CTriasApp::CreateAndInitDispatchObjProp (IDispatch *pIDispatch, LONG *plCookie)
{
	if (NULL == plCookie) return E_POINTER;
	*plCookie = 0L;

	try {
	// Objekteigenschaft über ihr IDispatch einbinden
	WObjectProperty ObjProp;
	CComObject<COleObjectProperty> *pIObjProp = NULL;

		THROW_FAILED_HRESULT(CComObject<COleObjectProperty>::CreateInstance(&pIObjProp));
		ObjProp = pIObjProp;			// RefCnt jetzt 1
		THROW_FAILED_HRESULT(pIObjProp -> FInit (pIDispatch));

	// Aggregation mit dem unbekannten
	WObjectProperty Prop (ObjProp);
	WInitInnerObject FakeLock (CLSID_FakeTRiASLockFeature);

		FakeLock -> SetInnerObject (ObjProp, IID_IObjectProperty, Prop.ppu());
		if (!Prop.IsValid())
			Prop = ObjProp;

	// Objekteigenschaft registrieren und initialisieren
		*plCookie = ((OLE2AutoExtension *)g_pTE) -> AddPropertyFunction (Prop);
		if (0 == *plCookie) _com_issue_error(E_FAIL);

	BOOL fSuccess = true;

		pIObjProp -> Init (this, &fSuccess);	// Server-Initialisierung fehlgeschlagen
		if (!fSuccess) _com_issue_error(E_FAIL);
	
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return S_OK;
}

STDMETHODIMP CTriasApp::AddObjectProperty (IDispatch *pIDispatch, long *plCookie)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

LONG dwCookie = 0;
DObjectProperty *pDObjProp = NULL;

	try {
	HRESULT hr = pIDispatch -> QueryInterface (IID_DObjectProperty, (LPVOID *)&pDObjProp);

		if (SUCCEEDED(hr)) {
		// Objekteigenschaft über ihr DObjectProperty einbinden

			THROW_FAILED_HRESULT(CreateAndInitDualObjProp (pDObjProp, &dwCookie));
			RELEASE(pDObjProp);

		} else if (E_NOINTERFACE == hr) {
		// Objekteigenschaft über ihr IDispatch einbinden

			THROW_FAILED_HRESULT(CreateAndInitDispatchObjProp(pIDispatch, &dwCookie));
		
		} else 
			_com_issue_error(hr);

	} catch (_com_error& hr) {
		RELEASE(pDObjProp);
		if (0 != dwCookie)
			((OLE2AutoExtension *)g_pTE) -> RemovePropertyFunction (dwCookie);
		return _COM_ERROR(hr);
	}

// Resultat liefern
	*plCookie = dwCookie;
	return S_OK;
}

STDMETHODIMP CTriasApp::RemoveObjectProperty (long lCookie)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

bool fResult = ((OLE2AutoExtension *)g_pTE) -> RemovePropertyFunction ((ULONG)lCookie);

	return fResult ? S_OK : E_FAIL;
}

STDMETHODIMP CTriasApp::get_Properties (_DTRiASProperties **ppIProps)
{
	return E_NOTIMPL;
}

STDMETHODIMP CTriasApp::CreateProperty (VARIANT vName, VARIANT vType, VARIANT vValue, _DTRiASProperty **ppIProp)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// ToolbarHandling
STDMETHODIMP CTriasApp::get_ToolBars (DControlToolBars **ppIToolBars)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == ppIToolBars) return E_POINTER;
	*ppIToolBars = NULL;

	try {
	// Die Toolbars werden durch die FakeMFC-Erweiterung verwaltet
	WDControlToolBars Bars (CLSID_FakeMFCExtension);

		*ppIToolBars = Bars.detach();

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return S_OK;
}

STDMETHODIMP CTriasApp::GetToolBar (THIS_ BSTR bstrName, DControlToolBar **pToolBar)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == pToolBar) return E_POINTER;
	*pToolBar = NULL;

	try {
	// Die Toolbars werden durch die FakeMFC-Erweiterung verwaltet
	WDControlToolBars Bars (CLSID_FakeMFCExtension);
	CComVariant vName (bstrName);
	WDispatch Disp;

		THROW_FAILED_HRESULT(Bars -> Item (vName, Disp.ppi()));

	WDControlToolBar Bar (Disp);		// throws hr

		*pToolBar = Bar.detach();

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return S_OK;
}

STDMETHODIMP CTriasApp::AddToolBar (BSTR bstrName, VARIANT Style, DControlToolBar **ppToolBar)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == ppToolBar) return E_POINTER;

	*ppToolBar = NULL;		// für alle Fälle
	USES_CONVERSION;

	COM_TRY {
	WTRiASBarContainer BarCont (g_pTE -> m_pXtnSite);	// throws hr
	WTRiASBar Bar;

	// Style und Namen setzen, fertig initialisieren
	CComVariant vStyle;
	DWORD dwStyle = CBRS_ALIGN_TOP|CBRS_SIZE_DYNAMIC|CBRS_TOOLTIPS|
					CBRS_BORDER_ANY|CBRS_BORDER_3D|CBRS_FLYBY;

		if (SUCCEEDED(vStyle.ChangeType (VT_I4, &Style)))
			dwStyle = V_I4(&vStyle);

		if (!IsWin40())
			dwStyle &= ~CBRS_BORDER_3D;

	// PlausibilitätsTests
		if (!(dwStyle & CBRS_SIZE_FIXED|CBRS_SIZE_DYNAMIC))
			dwStyle |= CBRS_SIZE_DYNAMIC;
		if (!(dwStyle & CBRS_ALIGN_ANY))
			dwStyle |= CBRS_ALIGN_TOP;
		if (!(dwStyle & CBRS_ORIENT_ANY))
			dwStyle |= CBRS_ALIGN_TOP;

	// ToolBar erzeugen
		THROW_FAILED_HRESULT(BarCont -> AddTRiASBar (OLE2A(bstrName), dwStyle, 0, Bar.ppi()));

	WDControlToolBar ToolBar (Bar);	// throws hr

		THROW_FAILED_HRESULT(ToolBar -> put_Application ((IDispatch *)this));
		THROW_FAILED_HRESULT(ToolBar -> put_Parent ((IDispatch *)this));

		*ppToolBar = ToolBar.detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTriasApp::RemoveToolBar (BSTR bstrName)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	try {
	// Die Toolbars werden durch die FakeMFC-Erweiterung verwaltet
	WDControlToolBars Bars (CLSID_FakeMFCExtension);
	CComVariant vName (bstrName);

		THROW_FAILED_HRESULT(Bars -> Remove (vName));

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return S_OK;
}

STDMETHODIMP CTriasApp::RunScript (BSTR bstrName)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	USES_CONVERSION;
	COM_TRY {
	WExtendBScript BScript;

		THROW_FAILED_HRESULT(((OLE2AutoExtension *)g_pTE) -> GetIBScript  (BScript.ppi()));
		THROW_FAILED_HRESULT(BScript -> RunScript (OLE2A(bstrName)));

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTriasApp::StopScript (BSTR bstrName)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	USES_CONVERSION;
	COM_TRY {
	WExtendBScript BScript;

		THROW_FAILED_HRESULT(((OLE2AutoExtension *)g_pTE) -> GetIBScript  (BScript.ppi()));
		THROW_FAILED_HRESULT(BScript -> StopScript (OLE2A(bstrName)));

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTriasApp::CreateInstance (BSTR bstrProgID, IDispatch **ppIDisp)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == ppIDisp) 
		return E_POINTER;
	*ppIDisp = NULL;

	COM_TRY {
	WDispatch disp;
	CIID Guid (bstrProgID, CIID::INITCIID_InitFromProgId);

		if (!Guid || FAILED(disp.CreateInstance (Guid))) {
		// es ist ggf. ein DisplayString
		BIND_OPTS bindOPts;

			bindOPts.cbStruct = sizeof(bindOPts);
			bindOPts.grfFlags = 0;
			bindOPts.grfMode = STGM_READWRITE;
			bindOPts.dwTickCountDeadline = 0;

			THROW_FAILED_HRESULT(::CoGetObject(bstrProgID, &bindOPts, IID_IDispatch, disp.ppv()));
		}
		*ppIDisp = disp.detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTriasApp::LoadExtension (BSTR bstrProgID, VARIANT vargMode, VARIANT vargDispXtsn)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	USES_CONVERSION;

CComVariant vMode;
int iMode = LEFullLoad;

	if (SUCCEEDED(vMode.ChangeType (VT_I4, &vargMode)))
		iMode = V_I4(&vMode);

CComVariant vDispXtsn;
WUnknown Unk;

	if (SUCCEEDED(vDispXtsn.ChangeType (VT_UNKNOWN, &vargDispXtsn)))
		Unk = V_UNKNOWN(&vDispXtsn);

//	Erweiterung laden
LOADEXTENSION2 le;

	INITSTRUCT(le, LOADEXTENSION2);
	le.m_pDesc = NULL;
	le.m_pName = OLE2A(bstrProgID);
	le.m_iMode = iMode;
	le.m_fGlobal = TRUE;		
	le.m_pIUnk = Unk;
	if (NULL == DEX_ExternalLoadExtension2(le))
		return E_UNEXPECTED;

	return S_OK;
}

STDMETHODIMP CTriasApp::UnloadExtension (BSTR bstrProgID)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	USES_CONVERSION;

//	Erweiterung entladen
LOADEXTENSION2 le;

	INITSTRUCT(le, LOADEXTENSION2);
	le.m_pName = OLE2A(bstrProgID);
	le.m_iMode = LENoLoad;
	le.m_fGlobal = TRUE;		
	if (!DEX_ExternalUnLoadExtension2(le))
		return E_UNEXPECTED;
	return S_OK;
}

STDMETHODIMP CTriasApp::GetExtension (BSTR bstrProgID, IDispatch **ppIDisp)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == ppIDisp)
		return E_POINTER;

	*ppIDisp = NULL;		// für alle Fälle

EXTENSIONPTR Xtnsn;
IUnknown *pIUnk = NULL;

	USES_CONVERSION;
	INITSTRUCT(Xtnsn, EXTENSIONPTR);
	Xtnsn.pcDLLName = OLE2A(bstrProgID);
	Xtnsn.ppIUnk = &pIUnk;

	if (!DEX_GetExtensionPtr(Xtnsn) || NULL == pIUnk) 
		return S_OK;

	pIUnk -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);		// Fehler nicht auswerten
	pIUnk -> Release();
	return S_OK;
}

STDMETHODIMP CTriasApp::get_Tag (BSTR bstrTagName, VARIANT *pvTagData)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == bstrTagName || 0 == ::SysStringLen(bstrTagName))
		return E_INVALIDARG;
	if (NULL == pvTagData)
		return E_POINTER;

	return m_mapTags.GetTag(bstrTagName, pvTagData);
}

STDMETHODIMP CTriasApp::put_Tag (BSTR bstrTagName, VARIANT vTagData)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == bstrTagName || 0 == ::SysStringLen(bstrTagName))
		return E_INVALIDARG;

	if (VT_EMPTY == V_VT(&vTagData))
		return m_mapTags.DeleteTag(bstrTagName);

	return m_mapTags.AddTag(bstrTagName, vTagData);
}

