// OLE2AUTO BScript-Erweiterung ---------------------------------------------
// File: OLEBSEXT.CXX

#include "precomp.hxx"

#include <ospace/file/path.h>
#include <Com/ComBool.h>

#include <dirisole.h>

#include "Strings.h"
#include "oleguid.h"
#include "bscrerr.h"
#include "oleautor.h"
#include "jumptab.h"
				
#include "olebsext.hxx"			// function  prototypes

#include "docarray.hxx"
#include "enumdocs.hxx"
#include "doc.hxx"

#include "viewarry.hxx"
#include "enuviews.hxx"
#include "view.hxx"

#include "clsarray.hxx"
#include "enumclss.hxx"
#include "class.hxx"
#include "classes.hxx"

#include "objarray.hxx"
#include "enumobjs.hxx"
#include "obj.hxx"
#include "objs.hxx"

#include "ftsarray.hxx"
#include "enumfts.hxx"
#include "feat.hxx"
#include "fts.hxx"

#include "obwarray.hxx"
#include "enumobws.hxx"
#include "objwin.hxx"
#include "objwins.hxx"

#include "array.hxx"
#include "ebarray.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ManageDocumentContext);

inline HRESULT SetCtxDataSource (ebHTHREAD hThread, _DDocument *pDoc)
{
INT_PTR hPrCtx = ebThread_GetLong (hThread, SETLONG_HPROJECT);		// Kontext-Datenquelle

	if (HACTCONNECTION == reinterpret_cast<HPROJECT>(hPrCtx))
		hPrCtx = reinterpret_cast<INT_PTR>(DEX_GetDataSourceHandle());

// dieses QI schlägt bei remote Objekten fehl 
WManageDocumentContext Ctx;

	if (SUCCEEDED(pDoc -> QueryInterface(Ctx.ppi())))
	{
		RETURN_FAILED_HRESULT(Ctx -> SetCtxHandle (hPrCtx));
	}
	return S_OK;
}

HRESULT GetCtxDataSource (ebHTHREAD hThread, _DDocument *pDoc, BSTR *pbstrCtx)
{
INT_PTR hPrCtx = ebThread_GetLong (hThread, SETLONG_HPROJECT);		// Kontext-Datenquelle

	if (HACTCONNECTION == reinterpret_cast<HPROJECT>(hPrCtx)) {
	// dieses QI schlägt bei remote Objekten fehl 
	WManageDocumentContext Ctx;

		if (SUCCEEDED(pDoc -> QueryInterface(Ctx.ppi())))
		{
			RETURN_FAILED_HRESULT(Ctx -> GetCtxHandle (&hPrCtx));
		}

	// NotAnker
		if (HACTCONNECTION == reinterpret_cast<HPROJECT>(hPrCtx)) 
			hPrCtx = reinterpret_cast<INT_PTR>(DEX_GetDataSourceHandle());
	}

// den Namen dieser Datenquelle geben lassen
char cbBuffer[_MAX_PATH];

	if (!DEX_GetDataSourceShortName ((HPROJECT)hPrCtx, cbBuffer))
		return E_UNEXPECTED;

CComBSTR bstrCtx (cbBuffer);

	*pbstrCtx = bstrCtx.Detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// benötige Interfaces
DefineSmartInterface(Dispatch);								// WDispatch
DefineSmartInterface(EnumVARIANT);							// WEnumVARIANT

DefineSmartInterface2(DTRiASBaseClass, IID_DTRiASBaseClass);	// WDTRiASBaseClass

DefineSmartInterface2(DDocument, IID_DDocument);			// WDDocument
DefineSmartInterface2(DDocuments, IID_DDocuments);			// WDDocuments

DefineSmartInterface2(DView, IID_DView);					// WDView
DefineSmartInterface2(DViews, IID_DViews);					// WDViews

DefineSmartInterface2(DGeoObject, IID_DGeoObject);			// WDGeoObject
DefineSmartInterface2(DGeoObjects, IID_DGeoObjects);		// WDGeoObjects

DefineSmartInterface2(DGeoClass, IID_DGeoClass);			// WDGeoClass
DefineSmartInterface2(DGeoClasses, IID_DGeoClasses);		// WDGeoClasses

DefineSmartInterface2(DGeoFeature, IID_DGeoFeature);		// WDGeoFeature
DefineSmartInterface2(DGeoFeatures, IID_DGeoFeatures);		// WDGeoFeatures

DefineSmartInterface2(DGeoObjectWin, IID_DGeoObjectWin);	// WDGeoObjectWin
DefineSmartInterface2(DGeoObjectWins, IID_DGeoObjectWins);	// WDGeoObjectWins

DefineSmartInterface(TRiASConnections);						// WTRiASConnections
DefineSmartInterface(TRiASConnection);						// WTRiASConnection

///////////////////////////////////////////////////////////////////////////////
// globale Daten

int g_fDebugScript = true;

// HelperFunction -------------------------------------------------------------
#if !defined(_DEBUG)
inline 
#endif // _DEBUG
LPUNKNOWN GetObjectOrApp (ebARGS lpArgs)
{
DWORD dwObj = ebGetObject (lpArgs, 1);

	if (dwObj == 1) 
		return ((OLE2AutoExtension *)g_pTE) -> AppDisp();
	
	return LPUNKNOWN (dwObj);
}

///////////////////////////////////////////////////////////////////////////////
// Wrapper füe ebCreateStringX
inline ebHSUB ebAPI ebCreateStringX (ebHTHREAD hThread, ebLPCSTR lpStr)
{
ebHSUB hStr = ebCreateString (hThread, lpStr);

	if (!hStr) {
		ebRuntimeError (hThread, FALSE, ERR_OUTOFMEMORY, NULL);
		ASSERT(NULL != hStr);		// should not return
	}
	return hStr;
}

inline ebHSUB ebAPI ebCreateStringX (ebHTHREAD hThread, LPOLESTR lpoleStr)
{
	USES_CONVERSION;

ebHSUB hStr = ebCreateString (hThread, OLE2A(lpoleStr));

	if (!hStr) {
		ebRuntimeError (hThread, FALSE, ERR_OUTOFMEMORY, NULL);
		ASSERT(NULL != hStr);		// should not return
	}
	return hStr;
}

///////////////////////////////////////////////////////////////////////////////
// Make Ole-VARIANT from ebVARIANT 
namespace {
	class CEbString 
	{
	public:
		CEbString(ebHOBJECT hObject, ebHSUB hStr) :
			m_hObj(hObject), m_hSub(hStr)
		{
			m_pStr = ebLockString (hObject, hStr);
		}
		~CEbString()
		{
			ebUnlockString (m_hObj, m_hSub);
		}
		operator const char *() { return m_pStr; }
		const char *GetString() { return m_pStr; }
		
		operator bool () { return !!(*this); }
		bool operator! () { return (NULL == m_pStr) ? true : false; }

	private:
		LPTSTR m_pStr;
		ebHOBJECT m_hObj;
		ebHSUB m_hSub;
	};
}

CComVariant MakeVARIANT (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs, int iArg)
{
CComVariant vResult;

	if (iArg > iNumArgs) 
		return CComVariant(DISP_E_PARAMNOTFOUND, VT_ERROR);			// parameter not given
	
ebVARIANT v;

	ebGetVariantEx (lpArgs, iArg, &v);

	switch (v.Type) {
	case TYP_BOOLEAN:	// VT_BOOL
	case TYP_INTEGER:	// VT_I2
	case TYP_LONG:		// VT_I4
	case TYP_SINGLE:	// VT_R4
	case TYP_DOUBLE:	// VT_R8
	case TYP_CURRENCY:	// VT_CY
	case TYP_DATE:		// VT_DATE
		return CComVariant ((VARIANT &)v);
		
	case TYP_ERROR:		// VT_ERROR
		if (ebHIWORD(v.u.l) & 0x0002) 
			return CComVariant(DISP_E_PARAMNOTFOUND, VT_ERROR);		// parameter was skipped
		return CComVariant ((VARIANT &)v);
		
	case TYP_STRING:	// VT_BSTR
		{
		CEbString Str (hThread, v.u.h);
		
			if (!Str) 
				break;
			return CComVariant(Str.GetString());
		}
		break;
		
	case TYP_OLEOBJECT:	// VT_DISPATCH
		return CComVariant(ebGetDispatch (hThread, v.u.o));

	case TYP_APPOBJECT:
		return CComVariant(reinterpret_cast<IUnknown *>(v.u.o));

	default:
		break;
	}

	_ASSERTE(FALSE);
	return CComVariant(DISP_E_PARAMNOTFOUND, VT_ERROR);		// not supported yte
}

// Make ebVARIANT from Ole-VARIANT --------------------------------------------
ebVARIANT MakeebVARIANT (ebHTHREAD hThread, VARIANT &v)
{
ebVARIANT vResult;

	switch (V_VT(&v)) {
	case VT_BOOL:		// TYP_BOOLEAN
	case VT_I2:			// TYP_INTEGER
	case VT_I4:			// TYP_LONG
	case VT_R4:			// TYP_SINGLE
	case VT_R8:			// TYP_DOUBLE
	case VT_CY:			// TYP_CURRENCY
	case VT_DATE:		// TYP_DATE
		vResult = (ebVARIANT &)v;
		break;
		
	case VT_ERROR:		// TYP_ERROR
		if (V_ERROR(&v) == DISP_E_PARAMNOTFOUND) {
			vResult.Type = TYP_ERROR;
			vResult.u.l = MAKELONG(ebHIWORD(vResult.u.l) | 0x0002, 0);	// parameter was skipped
		} else
			vResult = (ebVARIANT &)v;
		break;
		
	case VT_BSTR:		// TYP_STRING
		vResult.Type = TYP_STRING;
		vResult.u.h = ebCreateStringX (hThread, V_BSTR(&v));
		break;
		
	case VT_DISPATCH:	// TYP_OLEOBJECT
		vResult.Type = TYP_OLEOBJECT;
		vResult.u.o = ebCreateOleId (hThread, V_DISPATCH(&v));
		break;

	case VT_UNKNOWN:	// TYP_APPOBJECT:
		vResult.Type = TYP_APPOBJECT;
		vResult.u.o = reinterpret_cast<DWORD>(V_UNKNOWN(&v));
		if (NULL != V_UNKNOWN(&v)) 
			V_UNKNOWN(&v) -> AddRef();
		break;

	default:
		vResult.Type = TYP_EMPTY;
		vResult.u.l = 0L;
		break;
	}
	return vResult;
}


// Convert RTTI to readable string --------------------------------------------
static LPCSTR pRTTI[] = {
	"Unknown",
	"Application",
	"GeoDocument",
	"GeoDocuments",
	"GeoView",
	"GeoViews",
	"GeoClass",
	"GeoClasses",
	"GeoObject",
	"GeoObjects",
	"GeoFeature",
	"GeoFeatures",
	"GeoObjectWin",
	"GeoObjectWins",
	"VisInfo",
	"ToolBar",
	"ToolBars",
	"ToolBarButton",
	"ToolBarButtons",
	"TRiASProperty",
	"TRiASProperties",
	"TRiASConnection",
	"TRiASConnections",
};

inline LPCTSTR StringFromRTTI (LONG iRTTI) { return pRTTI[LOWORD(iRTTI)]; }

///////////////////////////////////////////////////////////////////////////////
// Macht aus einem IUnknown eine Objektnummer
HRESULT GetObjectNumber (VARIANT &rV)
{
	COM_TRY {
	CComVariant v;

		if (SUCCEEDED(v.ChangeType (VT_DISPATCH, &rV))) {
		WDGeoObject IObj(V_DISPATCH(&v));	// throws hr
		LONG lONr = INVALID_ONR;

			THROW_FAILED_HRESULT(IObj -> get_Value(&lONr));

		CComVariant vONr (lONr);

			return vONr.Detach (&rV);
		} 
//		THROW_FAILED_HRESULT(v.ChangeType (VT_I4, &rV));

	} COM_CATCH;
	return S_OK;
}

// ----------------------------------------------------------------------------
// TRiAS_not_supported
// ----------------------------------------------------------------------------
void TRiAS_not_supported (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
// Fehler in Form einer MsgBox melden oder 'On Error' rufen
CString str;

	str.Format (IDS_NOTSUPPORTED, g_cbTRiAS);
	ebRuntimeError (hThread, true, TRIASERR_NOTSUPPORTED, str);
}

// ----------------------------------------------------------------------------
// refcnt_BaseObject
// ----------------------------------------------------------------------------
void refcnt_BaseObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE_SYS(refcnt_BaseObject);

	switch (iNumArgs) {
	case OBJECT_REFNEW:
	// error message ?
		ebSetObject (lpArgs, 0, NULL);
		break;
		
	case OBJECT_REFINC:
		GetObjectOrApp (lpArgs) -> AddRef();
		break;
		
	case OBJECT_REFDEC:
		GetObjectOrApp (lpArgs) -> Release();
		break;
	}
}

// ----------------------------------------------------------------------------
// refcnt_GeoObjects
// ----------------------------------------------------------------------------
void refcnt_GeoObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE_SYS(refcnt_GeoObjects);

	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
		// Aktives Dokument verwenden
		CGeoDoc *pDoc = NULL;
		
			((OLE2AutoExtension *)g_pTE) -> App() -> FGetDocDisp (NULL, &pDoc);
			if (NULL != pDoc) {
			_DGeoObjects *pIObjs = NULL;
				
				pDoc -> CreateNewGeoObjects (&pIObjs);
				ebSetObject (lpArgs, 0, (DWORD)pIObjs);
			}
		}
		break;
		
	case OBJECT_REFINC:
		((IUnknown *)ebGetObject (lpArgs, 1)) -> AddRef();
		break;
		
	case OBJECT_REFDEC:
		((IUnknown *)ebGetObject (lpArgs, 1)) -> Release();
		break;
	}
}

// test for RTTI-typemismatch -------------------------------------------------
bool isTypeMismatch (ebHTHREAD hThread, ebARGS lpArgs, int iRTTI, bool fCmpMainOnly = true)
{
DTRiASBaseClass *pIBase = (DTRiASBaseClass *)ebGetObject (lpArgs, 1);
LONG lRTTI = RTTI_Unknown;
char cbBuffer[128];
bool fFlag = false;

	try {
		if (fCmpMainOnly) {
			if (FAILED(pIBase -> get_isA(&lRTTI)) || LOWORD(lRTTI) != LOWORD((LONG)iRTTI)) {
				wsprintf (cbBuffer, "Type mismatch: %s -> %s", 
					  StringFromRTTI (lRTTI), StringFromRTTI (iRTTI));
				fFlag = true;
			}
		} else {
			if (FAILED(pIBase -> get_isA(&lRTTI)) || lRTTI != (LONG)iRTTI) {
				wsprintf (cbBuffer, "Type mismatch (subtypes ?): %s -> %s", 
					  StringFromRTTI (lRTTI), StringFromRTTI (iRTTI));
				fFlag = true;
			}
		}
	} catch (...) {
		wsprintf (cbBuffer, "Bad base pointer, expected: %s", StringFromRTTI (iRTTI));
		fFlag = true;
	}

	if (fFlag) {
		ebRuntimeError (hThread, true, TRIASERR_TYPEMISMATCH, cbBuffer);
		return true;	// ebRuntimeError never returns
	}
				
return false;
}		

// ----------------------------------------------------------------------------
// propget_BaseObject_isA
// ----------------------------------------------------------------------------
void propget_BaseObject_isA (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_BaseObject_isA);

_DTRiASBaseClass *pIBase = (_DTRiASBaseClass *)GetObjectOrApp (lpArgs);
LONG lRTTI = RTTI_Unknown;

	pIBase -> get_isA(&lRTTI);
	ebSetLong (lpArgs, 0, lRTTI);
}



// ----------------------------------------------------------------------------
// propget_BaseObject_Parent
// ----------------------------------------------------------------------------
void propget_BaseObject_Parent (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_BaseObject_Parent);

_DTRiASBaseClass *pIBase = (_DTRiASBaseClass *)GetObjectOrApp (lpArgs);
IDispatch *pIDisp = NULL;
HRESULT hr = pIBase -> get_Parent (&pIDisp); 

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) {
	_DTRiASBaseClass *pIParent = NULL;
	
		hr = pIDisp -> QueryInterface (IID_DTRiASBaseClass, (LPVOID *)&pIParent);
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)pIParent);			
		pIDisp -> Release();
	}
}


// ----------------------------------------------------------------------------
// propget_BaseObject_Application
// ----------------------------------------------------------------------------
void propget_BaseObject_Application (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_BaseObject_Application);

// no need to implement (restricted access)
	ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// propget_BaseObject_IDispatch
// ----------------------------------------------------------------------------
void propget_BaseObject_IDispatch (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_BaseObject_IDispatch);

	try {
	WDispatch Disp ((_DTRiASBaseClass *)GetObjectOrApp (lpArgs));
	ebDWORD dwId = ebCreateOleId (hThread, Disp.detach());
	ebDWORD dwOldId = ebGetOleObject (lpArgs, 0);

		if (dwOldId) 
			ebFreeOleId (hThread, dwOldId);
		ebSetOleObject (lpArgs, 0, dwId);
		
	} catch (...) {
		TRACE("Couldn't QI IDispatch from _DTRiASBaseClass\n");
	}
}


// ----------------------------------------------------------------------------
// refcnt_Application
// ----------------------------------------------------------------------------
void refcnt_Application (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE_SYS(refcnt_Application);
	/* nothing to do: Application exists independently from BasicScript */
}

// ----------------------------------------------------------------------------
// propget_Application_Value
// ----------------------------------------------------------------------------
void propget_Application_Value (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Application_Value);

CComBSTR bstrValue;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> AppDisp() -> get_Value (CLEARED(&bstrValue));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr)) {
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrValue));
	} else
		ebSetString (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propget_Application_Version
// ----------------------------------------------------------------------------
void propget_Application_Version (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Application_Version);

CComBSTR bstrValue;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> AppDisp() -> get_Version (CLEARED(&bstrValue));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr)) {
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrValue));
	} else
		ebSetString (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propget_Application_Name
// ----------------------------------------------------------------------------
void propget_Application_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Application_Name);

CComBSTR bstrValue;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> AppDisp() -> get_Name(CLEARED(&bstrValue));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr)) {
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrValue));
	} else
		ebSetString (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// propget_Application_StartupPath
// ----------------------------------------------------------------------------
void propget_Application_StartupPath (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Application_StartupPath);

CComBSTR bstrPath;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> AppDisp() -> get_StartupPath(CLEARED(&bstrPath));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr)) {
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrPath));
	} else
		ebSetString (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// propget_Application_Path
// ----------------------------------------------------------------------------
void propget_Application_Path (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Application_Path);

CComBSTR bstrPath;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> AppDisp() -> get_DefaultFilePath(CLEARED(&bstrPath));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr)) {
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrPath));
	} else
		ebSetString (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// propset_Application_Path
// ----------------------------------------------------------------------------

void propset_Application_Path (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_Application_Path);

ebHSUB hStr = ebGetString (lpArgs, 2);
CComBSTR bstrPath (ebLockString (hThread, hStr));
	
	((OLE2AutoExtension *)g_pTE) -> AppDisp() -> put_DefaultFilePath (bstrPath);
	ebUnlockString (hThread, hStr);
}


// ----------------------------------------------------------------------------
// propget_Application_FullName
// ----------------------------------------------------------------------------

void propget_Application_FullName (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Application_FullName);

CComBSTR bstrValue;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> AppDisp() -> get_FullName(CLEARED(&bstrValue));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr)) {
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrValue));
	} else
		ebSetString (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// propget_Application_Visible
// ----------------------------------------------------------------------------
void propget_Application_Visible (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Application_Visible);

VARIANT_BOOL iVisible = 0;

	((OLE2AutoExtension *)g_pTE) -> AppDisp() -> get_Visible(&iVisible);
	ebSetInt (lpArgs, 0, iVisible);
}


// ----------------------------------------------------------------------------
// propset_Application_Visible
// ----------------------------------------------------------------------------
void propset_Application_Visible (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_Application_Visible);

	((OLE2AutoExtension *)g_pTE) -> AppDisp() -> put_Visible (ebGetInt (lpArgs, 2));
}




// ----------------------------------------------------------------------------
// function_Application_NewDocument
// ----------------------------------------------------------------------------
void function_Application_NewDocument (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Application_NewDocument);

ebHSUB hStr = ebGetString (lpArgs, 2);
CComBSTR bstrName (ebLockString (hThread, hStr));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant v3 (MakeVARIANT (hThread, iNumArgs, lpArgs, 4));
CComVariant v4 (MakeVARIANT (hThread, iNumArgs, lpArgs, 5));

WDDocument Doc;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> AppDisp() -> NewDocument (bstrName, v2, v3, v4, Doc.ppi());

	ebUnlockString (hThread, hStr);
	ebSetObject (lpArgs, 0, NULL);

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Doc.detach());
}

// ----------------------------------------------------------------------------
// function_Application_OpenDocument
// ----------------------------------------------------------------------------
void function_Application_OpenDocument (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Application_OpenDocument);

ebHSUB hStr = ebGetString (lpArgs, 2);
CComBSTR bstrName (ebLockString (hThread, hStr));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant v3 (MakeVARIANT (hThread, iNumArgs, lpArgs, 4));
CComVariant v4 (MakeVARIANT (hThread, iNumArgs, lpArgs, 5));

WDDocument Doc;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> AppDisp() -> OpenDocument (bstrName, v2, v3, v4, Doc.ppi());

	ebUnlockString (hThread, hStr);
	ebSetObject (lpArgs, 0, NULL);

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Doc.detach());
}


// ----------------------------------------------------------------------------
// propget_Application_GetDocuments
// ----------------------------------------------------------------------------
void propget_Application_GetDocuments (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Application_GetDocuments);

WDDocuments Docs;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> AppDisp() -> get_Documents(Docs.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Docs.detach());
}

// ----------------------------------------------------------------------------
// function_Application_GetDocument
// ----------------------------------------------------------------------------
void function_Application_GetDocument (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Application_GetDocument);

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));

WDDocument Doc;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> AppDisp() -> GetDocument (v1, v2, Doc.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Doc.detach());
}

// ----------------------------------------------------------------------------
// function_Application_AddDocument
// ----------------------------------------------------------------------------
void function_Application_AddDocument (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Application_AddDocument);

CComVariant v2;

	V_VT(&v2) = VT_I4;	// Add ??? now
	V_I4(&v2) = DOCMODE_Add;
		
ebHSUB hStr = ebGetString (lpArgs, 2);
CComVariant v1 (ebLockString (hThread, hStr));

WDDocument Doc;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> AppDisp() -> GetDocument (v1, v2, Doc.ppi());

	ebUnlockString (hThread, hStr);
	if (NULL != lpArgs[0]) {		// nur, wenn nicht method
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Doc.detach());
		else
			ebSetObject (lpArgs, 0, NULL);
	}
}

// ----------------------------------------------------------------------------
// function_Application_MakeActive
// ----------------------------------------------------------------------------
void function_Application_MakeActive (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Application_MakeActive);

CComVariant v2;
	
	V_VT(&v2) = VT_I4;	
	V_I4(&v2) = DOCMODE_Replace;
		
ebHSUB hStr = ebGetString (lpArgs, 2);
CComVariant v1 (ebLockString (hThread, hStr));

WDDocument Doc;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> AppDisp() -> GetDocument (v1, v2, Doc.ppi());

	ebUnlockString (hThread, hStr);

	if (NULL != lpArgs[0]) {		// nur, wenn nicht method
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Doc.detach());
		else
			ebSetObject (lpArgs, 0, NULL);
	}
}


// ----------------------------------------------------------------------------
// command_Application_CloseDocument
// ----------------------------------------------------------------------------
void command_Application_CloseDocument (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_Application_CloseDocument);

CComVariant v2;
	
	V_VT(&v2) = VT_I4;
	V_I4(&v2) = DOCMODE_Remove;

ebHSUB hStr = ebGetString (lpArgs, 2);
CComVariant v1 (ebLockString (hThread, hStr));
WDDocument Doc;

	((OLE2AutoExtension *)g_pTE) -> AppDisp() -> GetDocument (v1, v2, Doc.ppi());
	ebUnlockString (hThread, hStr);
}

// ----------------------------------------------------------------------------
// propget_Application_GetActiveDocument
// ----------------------------------------------------------------------------
void propget_Application_GetActiveDocument (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Application_GetActiveDocument);

WDDocument Doc;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> AppDisp() -> get_ActiveDocument(Doc.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Doc.detach());
	else 
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// function_Application_Advise
// ----------------------------------------------------------------------------
void function_Application_Advise (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Application_Advise);

LONG dwCookie = 0L;
ebDWORD dwId = ebGetOleObject (lpArgs, 2);
WDispatch Disp ((IDispatch *)ebGetDispatch (hThread, dwId));

	((OLE2AutoExtension *)g_pTE) -> AppDisp() -> Advise (Disp, &dwCookie);
	ebSetLong (lpArgs, 0, dwCookie);
}

// ----------------------------------------------------------------------------
// command_Application_Unadvise
// ----------------------------------------------------------------------------
void command_Application_Unadvise (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_Application_Unadvise);

	((OLE2AutoExtension *)g_pTE) -> AppDisp() -> UnAdvise (ebGetLong(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// function_Application_AddPropertyFunction
// ----------------------------------------------------------------------------
void function_Application_AddPropertyFunction (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Application_AddPropertyFunction);

LONG dwCookie = 0L;
ebDWORD dwId = ebGetOleObject (lpArgs, 2);
WDispatch Disp ((IDispatch *)ebGetDispatch (hThread, dwId));

	((OLE2AutoExtension *)g_pTE) -> AppDisp() -> AddObjectProperty (Disp, &dwCookie);
	ebSetLong (lpArgs, 0, dwCookie);
}

// ----------------------------------------------------------------------------
// command_Application_RemovePropertyFunction
// ----------------------------------------------------------------------------
void command_Application_RemovePropertyFunction (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_Application_RemovePropertyFunction);

	((OLE2AutoExtension *)g_pTE) -> AppDisp() -> RemoveObjectProperty (ebGetLong(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// propset_Application_StatusBar
// ----------------------------------------------------------------------------
void propset_Application_StatusBar (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_Application_StatusBar);

ebHSUB hStr = ebGetString (lpArgs, 2);
CComBSTR bstr (ebLockString (hThread, hStr));

	((OLE2AutoExtension *)g_pTE) -> AppDisp() -> put_StatusBar (bstr);
	ebUnlockString (hThread, hStr);
}

// ----------------------------------------------------------------------------
// propget_Application_Caption
// ----------------------------------------------------------------------------
void propget_Application_Caption (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Application_Caption);

CComBSTR bstrValue;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> AppDisp() -> get_Caption (CLEARED(&bstrValue));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr)) {
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrValue));
	} else
		ebSetString (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propset_Application_Caption
// ----------------------------------------------------------------------------
void propset_Application_Caption (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_Application_Caption);

ebHSUB hStr = ebGetString (lpArgs, 2);
CComBSTR bstr (ebLockString (hThread, hStr));

	((OLE2AutoExtension *)g_pTE) -> AppDisp() -> put_Caption (bstr);
	ebUnlockString (hThread, hStr);
}

// ----------------------------------------------------------------------------
// propget_Application_Left
// ----------------------------------------------------------------------------
void propget_Application_Left (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Application_Left);

long lLeft = 0;

	((OLE2AutoExtension *)g_pTE) -> AppDisp() -> get_Left (&lLeft);
	ebSetLong (lpArgs, 0, lLeft);
}

// ----------------------------------------------------------------------------
// propset_Application_Left
// ----------------------------------------------------------------------------
void propset_Application_Left (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_Application_Left);
	((OLE2AutoExtension *)g_pTE) -> AppDisp() -> put_Left (ebGetLong(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// propget_Application_Top
// ----------------------------------------------------------------------------
void propget_Application_Top (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Application_Top);

long lTop = 0;

	((OLE2AutoExtension *)g_pTE) -> AppDisp() -> get_Top (&lTop);
	ebSetLong (lpArgs, 0, lTop);
}

// ----------------------------------------------------------------------------
// propset_Application_Top
// ----------------------------------------------------------------------------
void propset_Application_Top (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_Application_Top);
	((OLE2AutoExtension *)g_pTE) -> AppDisp() -> put_Top (ebGetLong(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// propget_Application_Width
// ----------------------------------------------------------------------------
void propget_Application_Width (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Application_Width);

long lWidth = 0;

	((OLE2AutoExtension *)g_pTE) -> AppDisp() -> get_Width (&lWidth);
	ebSetLong (lpArgs, 0, lWidth);
}

// ----------------------------------------------------------------------------
// propset_Application_Width
// ----------------------------------------------------------------------------
void propset_Application_Width (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_Application_Width);
	((OLE2AutoExtension *)g_pTE) -> AppDisp() -> put_Width (ebGetLong(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// propget_Application_Height
// ----------------------------------------------------------------------------
void propget_Application_Height (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Application_Height);

long lHeight = 0;

	((OLE2AutoExtension *)g_pTE) -> AppDisp() -> get_Height (&lHeight);
	ebSetLong (lpArgs, 0, lHeight);
}

// ----------------------------------------------------------------------------
// function_Application_LoadExtension
// ----------------------------------------------------------------------------
void function_Application_LoadExtension (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Application_LoadExtension);

ebHSUB hStr = ebGetString (lpArgs, 2);
CComBSTR bstrName (ebLockString (hThread, hStr));
CComVariant vMode (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
#if _TRiAS_VER < 0x0300
CComVariant vtMissing (DISP_E_PARAMNOTFOUND);

	V_VT(&vtMissing) = VT_ERROR;
#endif // _TRiAS_VER < 0x0300
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> AppDisp() -> LoadExtension (bstrName, vMode, vtMissing);

	ebSetBool (lpArgs, 0, SUCCEEDED(hr) ? ebTRUE : ebFALSE);
	ebUnlockString (hThread, hStr);
}

// ----------------------------------------------------------------------------
// function_Application_UnLoadExtension
// ----------------------------------------------------------------------------
void function_Application_UnLoadExtension (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Application_UnLoadExtension);

ebHSUB hStr = ebGetString (lpArgs, 2);
CComBSTR bstrName (ebLockString (hThread, hStr));
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> AppDisp() -> UnloadExtension (bstrName);

	if (NULL != lpArgs[0])		// als Funktion gerufen
		ebSetBool (lpArgs, 0, SUCCEEDED(hr) ? ebTRUE : ebFALSE);
	ebUnlockString (hThread, hStr);
}

// ----------------------------------------------------------------------------
// propset_Application_Height
// ----------------------------------------------------------------------------
void propset_Application_Height (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_Application_Height);
	((OLE2AutoExtension *)g_pTE) -> AppDisp() -> put_Height (ebGetLong(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// propget_Collection_Item
// ----------------------------------------------------------------------------
void propget_Collection_Item (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Collection_Item);

_DTRiASCollection *pIColl = (_DTRiASCollection *)ebGetObject (lpArgs, 1);
CComVariant v (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
WDispatch Disp;
HRESULT hr = pIColl -> Item (v, Disp.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) {
		try {
		WDTRiASBaseClass IItem (Disp);		// throws hr
	
			ebSetObject (lpArgs, 0, (DWORD)IItem.detach());
		} catch (...) {
			TRACE("Could not QI _DTRiASBaseClassItem from IDispatch\n");
		}
	}
}


// ----------------------------------------------------------------------------
// propget_Collection_Count
// ----------------------------------------------------------------------------
void propget_Collection_Count (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Collection_Count);

LONG lCount = 0;
_DTRiASCollection *pIColl = (_DTRiASCollection *)ebGetObject (lpArgs, 1);
HRESULT hr = pIColl -> get_Count(&lCount);

	ebSetLong (lpArgs, 0, 0);
	if (SUCCEEDED(hr))
		ebSetLong (lpArgs, 0, lCount);
}


// ----------------------------------------------------------------------------
// function_Collection_Add
// ----------------------------------------------------------------------------
void function_Collection_Add (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Collection_Add);

WDispatch Disp;
CComVariant vArg (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
HRESULT hr  = ((_DTRiASCollection *)ebGetObject (lpArgs, 1)) -> Add (vArg, Disp.ppi());

	if (NULL != lpArgs[0]) {
		ebSetObject (lpArgs, 0, NULL);
		if (SUCCEEDED(hr)) {
			try {
			WDTRiASBaseClass Ibcls (Disp);
		
				ebSetObject (lpArgs, 0, (DWORD)Ibcls.detach());
			} catch (...) {
				TRACE("Couldn't QI _DTRiASBaseClass from IDispatch\n");
			}
		}
	}
}


// ----------------------------------------------------------------------------
// command_Collection_Remove
// ----------------------------------------------------------------------------
void command_Collection_Remove (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_Collection_Remove);

CComVariant vArg (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));

	((_DTRiASCollection *)ebGetObject (lpArgs, 1)) -> Remove (vArg);
}


// ----------------------------------------------------------------------------
// function_Documents_New
// ----------------------------------------------------------------------------
void function_Documents_New (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Documents_New);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Documents))
		return;

ebHSUB hStr = ebGetString (lpArgs, 2);
CComBSTR bstrName (ebLockString (hThread, hStr));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant v3 (MakeVARIANT (hThread, iNumArgs, lpArgs, 4));
CComVariant v4 (MakeVARIANT (hThread, iNumArgs, lpArgs, 5));

WDDocument Doc;
HRESULT hr = ((DDocuments *)ebGetObject (lpArgs, 1)) -> New(bstrName, v2, v3, v4, Doc.ppi());

	ebUnlockString (hThread, hStr);
	if (NULL != lpArgs[0]) {	// nur, wenn nicht method
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Doc.detach());
		else
			ebSetObject (lpArgs, 0, NULL);
	}
}

// ----------------------------------------------------------------------------
// function_Documents_Open
// ----------------------------------------------------------------------------
void function_Documents_Open (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Documents_Open);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Documents))
		return;

ebHSUB hStr = ebGetString (lpArgs, 2);
CComBSTR bstrName (ebLockString (hThread, hStr));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant v3 (MakeVARIANT (hThread, iNumArgs, lpArgs, 4));
CComVariant v4 (MakeVARIANT (hThread, iNumArgs, lpArgs, 5));

WDDocument Doc;
HRESULT hr = ((DDocuments *)ebGetObject (lpArgs, 1)) -> Open(bstrName, v2, v3, v4, Doc.ppi());

	ebUnlockString (hThread, hStr);
	if (NULL != lpArgs[0]) {	// nur, wenn nicht method
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Doc.detach());
		else
			ebSetObject (lpArgs, 0, NULL);
	}
}

// ----------------------------------------------------------------------------
// propget_Documents_NewEnum
// ----------------------------------------------------------------------------
void propget_Documents_NewEnum (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Documents_NewEnum);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Documents))
		return;

WUnknown IUnk;	
HRESULT hr = ((_DDocuments *)ebGetObject (lpArgs, 1)) -> _NewEnum(IUnk.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) {
		try {
		WEnumVARIANT IDocs (IUnk);		// throws hr
	
			ebSetObject (lpArgs, 0, (DWORD)IDocs.detach());
		} catch (...) {
			TRACE("Could not QI IEnumVARIANT from IUnknown\n");
		}
	}
}		

// ----------------------------------------------------------------------------
// propget_Documents_Next
// ----------------------------------------------------------------------------
void propget_Documents_Next (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Documents_Next);

// nächstes Item aus Enumerator geben lassen
CComVariant v;
HRESULT hr = ((IEnumVARIANT *)ebGetObject (lpArgs, 1)) -> Next (1, &v, NULL);
_DDocument *pIDoc = (_DDocument *)ebGetObject (lpArgs, 0);

	RELEASE(pIDoc);
	ebSetObject (lpArgs, 0, NULL);

	if (S_OK == hr) {
	CComVariant vDisp;

		hr = VariantChangeType (&vDisp, &v, 0, VT_DISPATCH);
		if (SUCCEEDED(hr) && NULL != V_DISPATCH(&vDisp)) {
			hr = V_DISPATCH(&vDisp) -> QueryInterface (IID_DDocument, (LPVOID *)&pIDoc);
			if (SUCCEEDED(hr)) 
				ebSetObject (lpArgs, 0, (DWORD)pIDoc);
		}
	}
}

// ----------------------------------------------------------------------------
// function_GeoObjects_CreateGeoObjectWin
// ----------------------------------------------------------------------------
void function_GeoObjects_CreateGeoObjectWin (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObjects_CreateGeoObjectWin);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjects))
		return;
		
CComVariant vFlag (iNumArgs > 1 ? ebGetInt (lpArgs, 2) : 0, VT_I4);
	
WDGeoObjectWin Win;
HRESULT hr = ((DGeoObjects *)ebGetObject (lpArgs, 1)) -> CreateGeoObjectWin (vFlag, Win.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Win.detach());			
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// function_GeoObjects_GeometryAND
// ----------------------------------------------------------------------------
void function_GeoObjects_GeometryAND (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObjects_GeometryAND);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjects))
		return;

WDGeoObjects Objs;
HRESULT hr = ((DGeoObjects *)ebGetObject (lpArgs, 1)) -> GeometryIntersection ((DGeoClass *)ebGetObject (lpArgs, 2), Objs.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// function_GeoObjects_GeometryOR
// ----------------------------------------------------------------------------
void function_GeoObjects_GeometryOR (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObjects_GeometryOR);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjects))
		return;

WDGeoObjects Objs;
HRESULT hr = ((DGeoObjects *)ebGetObject (lpArgs, 1)) -> GeometryUnion ((DGeoClass *)ebGetObject (lpArgs, 2), Objs.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// function_GeoObject_GeometryXOR
// ----------------------------------------------------------------------------
void function_GeoObject_GeometryXOR (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_GeometryXOR);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

WDGeoObjects Objs;
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> GeometryXOR ((DGeoObjects *)ebGetObject (lpArgs, 2), Objs.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// function_GeoObjects_SetIntersection
// ----------------------------------------------------------------------------
void function_GeoObjects_SetIntersection (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObjects_SetIntersection);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjects))
		return;

WDGeoObjects Objs;
HRESULT hr = ((DGeoObjects *)ebGetObject (lpArgs, 1)) -> Intersection ((DGeoObjects *)ebGetObject (lpArgs, 2), Objs.ppi());

	if (SUCCEEDED(hr))
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);		// some error
}

// ----------------------------------------------------------------------------
// function_GeoObjects_SetUnion
// ----------------------------------------------------------------------------
void function_GeoObjects_SetUnion (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObjects_SetUnion);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjects))
		return;

WDGeoObjects Objs;
HRESULT hr = ((DGeoObjects *)ebGetObject (lpArgs, 1)) -> Union ((DGeoObjects *)ebGetObject (lpArgs, 2), Objs.ppi());

	if (SUCCEEDED(hr))
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);		// some error
}

// ----------------------------------------------------------------------------
// function_GeoObjects_SetDifference
// ----------------------------------------------------------------------------
void function_GeoObjects_SetDifference (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObjects_SetDifference);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjects))
		return;

WDGeoObjects Objs;
HRESULT hr = ((DGeoObjects *)ebGetObject (lpArgs, 1)) -> Difference ((DGeoObjects *)ebGetObject (lpArgs, 2), Objs.ppi());

	if (SUCCEEDED(hr))
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);		// some error
}

// ----------------------------------------------------------------------------
// function_GeoObjects_SetSymmetricDifference
// ----------------------------------------------------------------------------
void function_GeoObjects_SetSymmetricDifference (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObjects_SetSymmetricDifference);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjects))
		return;

WDGeoObjects Objs;
HRESULT hr = ((DGeoObjects *)ebGetObject (lpArgs, 1)) -> SymmetricDifference ((DGeoObjects *)ebGetObject (lpArgs, 2), Objs.ppi());

	if (SUCCEEDED(hr))
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);		// some error
}

// ----------------------------------------------------------------------------
// GeometryLinesUnion_GeoObjects_function
// ----------------------------------------------------------------------------
void GeometryLinesUnion_GeoObjects_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(GeometryLinesUnion_GeoObjects_function);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjects))
		return;

WDGeoObjects Objs;
DGeoClass *pICls = (DGeoClass *)ebGetObject (lpArgs, 2);
CComVariant vFillGap (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant vAsArea (MakeVARIANT (hThread, iNumArgs, lpArgs, 4));
HRESULT hr = ((DGeoObjects *)ebGetObject (lpArgs, 1)) -> _GeometryLinesUnion (pICls, vFillGap, vAsArea, Objs.ppi());

	if (SUCCEEDED(hr))
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);		// some error
}

// ----------------------------------------------------------------------------
// propget_GeoObjects_NewEnum
// ----------------------------------------------------------------------------
void propget_GeoObjects_NewEnum (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObjects_NewEnum);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjects))
		return;

WUnknown IUnk;
HRESULT hr = ((_DGeoObjects *)ebGetObject (lpArgs, 1)) -> _NewEnum(IUnk.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) {
		try {
		WEnumVARIANT IObjs (IUnk);		// throw hr
	
			ebSetObject (lpArgs, 0, (DWORD)IObjs.detach());
		} catch (...) {
			TRACE("Could not QI IEnumVARIANT from IUnknown\n");
		}
	}
}

// ----------------------------------------------------------------------------
// propget_GeoObjects_Next
// ----------------------------------------------------------------------------
void propget_GeoObjects_Next (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObjects_Next);

// nächstes Item aus Enumerator geben lassen
VARIANT v;
HRESULT hr = ((IEnumVARIANT *)ebGetObject (lpArgs, 1)) -> Next (1, &v, NULL);
_DGeoObject *pIObj = (_DGeoObject *)ebGetObject (lpArgs, 0);

	RELEASE(pIObj);
	ebSetObject (lpArgs, 0, NULL);

	if (S_OK == hr) {
	VARIANT vDisp;

		VariantInit(&vDisp);
		hr = VariantChangeType (&vDisp, &v, 0, VT_DISPATCH);

		if (SUCCEEDED(hr) && NULL != V_DISPATCH(&vDisp)) {
			hr = V_DISPATCH(&vDisp) -> QueryInterface (IID_DGeoObject, (LPVOID *)&pIObj);
			if (SUCCEEDED(hr)) 
				ebSetObject (lpArgs, 0, (DWORD)pIObj);
			VariantClear (&vDisp);
		}
		VariantClear (&v);
	}
}

// ----------------------------------------------------------------------------
// function_GeoObjects_GetObjectsInWindow
// ----------------------------------------------------------------------------
void function_GeoObjects_GetObjectsInWindow (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObjects_GetObjectsInWindow);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjects))
		return;

WDGeoObjects Objs;
CComVariant vXMax(iNumArgs > 3 ? ebGetDouble (lpArgs, 4) : ebGetDouble (lpArgs, 2));
CComVariant vYMax(iNumArgs > 4 ? ebGetDouble (lpArgs, 5) : ebGetDouble (lpArgs, 3));
HRESULT hr = ((DGeoObjects *)ebGetObject (lpArgs, 1)) -> GetObjectsInRect (ebGetDouble (lpArgs, 2), ebGetDouble (lpArgs, 3), vXMax, vYMax, Objs.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// function_GeoObjects_MakeGeoClass
// ----------------------------------------------------------------------------
void function_GeoObjects_MakeGeoClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObjects_MakeGeoClass);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjects))
		return;

WDGeoClass Cls;
ebHSUB hStr = ebGetString (lpArgs, 2);
CComBSTR bstrName (ebLockString (hThread, hStr));
HRESULT hr = ((DGeoObjects *)ebGetObject (lpArgs, 1)) -> MakeGeoClass (bstrName, Cls.ppi());

	ebUnlockString (hThread, hStr);
	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Cls.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propget_GeoViews_NewEnum
// ----------------------------------------------------------------------------
void propget_GeoViews_NewEnum (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoViews_NewEnum);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoViews))
		return;

WUnknown IUnk;
HRESULT hr = ((_DViews *)ebGetObject (lpArgs, 1)) -> _NewEnum(IUnk.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) {
		try {
		WEnumVARIANT IViews (IUnk);		// throws hr;
	
			ebSetObject (lpArgs, 0, (DWORD)IViews.detach());
		} catch (...) {
			TRACE("Could not QI IEnumVARIANT from IUnknown\n");
		}
	}
}

// ----------------------------------------------------------------------------
// propget_GeoViews_Next
// ----------------------------------------------------------------------------
void propget_GeoViews_Next (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoViews_Next);

// nächstes Item aus Enumerator geben lassen
VARIANT v;
HRESULT hr = ((IEnumVARIANT *)ebGetObject (lpArgs, 1)) -> Next (1, &v, NULL);
_DView *pIView = (_DView *)ebGetObject (lpArgs, 0);

	RELEASE(pIView);
	ebSetObject (lpArgs, 0, NULL);

	if (S_OK == hr) {
	VARIANT vDisp;

		VariantInit(&vDisp);
		hr = VariantChangeType (&vDisp, &v, 0, VT_DISPATCH);

		if (SUCCEEDED(hr) && NULL != V_DISPATCH(&vDisp)) {
			hr = V_DISPATCH(&vDisp) -> QueryInterface (IID_DView, (LPVOID *)&pIView);
			if (SUCCEEDED(hr)) 
				ebSetObject (lpArgs, 0, (DWORD)pIView);
			VariantClear (&vDisp);
		}
		VariantClear (&v);
	}
}

// ----------------------------------------------------------------------------
// propget_GeoClasses_NewEnum
// ----------------------------------------------------------------------------
void propget_GeoClasses_NewEnum (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoClasses_NewEnum);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClasses))
		return;

WUnknown IUnk;
HRESULT hr = ((_DGeoClasses *)ebGetObject (lpArgs, 1)) -> _NewEnum(IUnk.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) {
		try {
		WEnumVARIANT IClss (IUnk);		// throws hr
	
			ebSetObject (lpArgs, 0, (DWORD)IClss.detach());
		} catch(...) {
			TRACE("Could not QI IEnumVARIANT from IUnknown\n");
		}
	}
}

// ----------------------------------------------------------------------------
// propget_GeoClasses_Next
// ----------------------------------------------------------------------------
void propget_GeoClasses_Next (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoClasses_Next);

// nächstes Item aus Enumerator geben lassen
VARIANT v;
HRESULT hr = ((IEnumVARIANT *)ebGetObject (lpArgs, 1)) -> Next (1, &v, NULL);
_DGeoClass *pICls = (_DGeoClass *)ebGetObject (lpArgs, 0);

	RELEASE(pICls);
	ebSetObject (lpArgs, 0, NULL);

	if (S_OK == hr) {
	VARIANT vDisp;

		VariantInit(&vDisp);
		hr = VariantChangeType (&vDisp, &v, 0, VT_DISPATCH);

		if (SUCCEEDED(hr) && NULL != V_DISPATCH(&vDisp)) {
			hr = V_DISPATCH(&vDisp) -> QueryInterface (IID_DGeoClass, (LPVOID *)&pICls);
			if (SUCCEEDED(hr)) 
				ebSetObject (lpArgs, 0, (DWORD)pICls);
			VariantClear (&vDisp);
		}
		VariantClear (&v);
	}
}

// ----------------------------------------------------------------------------
// propget_GeoFeatures_NewEnum
// ----------------------------------------------------------------------------
void propget_GeoFeatures_NewEnum (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoFeatures_NewEnum);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoFeatures))
		return;

WUnknown IUnk;
HRESULT hr = ((_DGeoFeatures *)ebGetObject (lpArgs, 1)) -> _NewEnum(IUnk.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) {
		try {
		WEnumVARIANT IFts (IUnk);
	
			ebSetObject (lpArgs, 0, (DWORD)IFts.detach());
		} catch(...) {
			TRACE("Could not QI IEnumVARIANT from IUnknown\n");
		}
	}
}

// ----------------------------------------------------------------------------
// propget_GeoFeatures_Next
// ----------------------------------------------------------------------------
void propget_GeoFeatures_Next (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoFeatures_Next);

// nächstes Item aus Enumerator geben lassen
VARIANT v;
HRESULT hr = ((IEnumVARIANT *)ebGetObject (lpArgs, 1)) -> Next (1, &v, NULL);
_DGeoFeature *pIFeat = (_DGeoFeature *)ebGetObject (lpArgs, 0);

	RELEASE(pIFeat);
	ebSetObject (lpArgs, 0, NULL);

	if (S_OK == hr) {
	VARIANT vDisp;

		VariantInit(&vDisp);
		hr = VariantChangeType (&vDisp, &v, 0, VT_DISPATCH);

		if (SUCCEEDED(hr) && NULL != V_DISPATCH(&vDisp)) {
			hr = V_DISPATCH(&vDisp) -> QueryInterface (IID_DGeoFeature, (LPVOID *)&pIFeat);
			if (SUCCEEDED(hr)) 
				ebSetObject (lpArgs, 0, (DWORD)pIFeat);
			VariantClear (&vDisp);
		}
		VariantClear (&v);
	}
}

// ----------------------------------------------------------------------------
// propget_GeoObjectWins_NewEnum
// ----------------------------------------------------------------------------
void propget_GeoObjectWins_NewEnum (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObjectWins_NewEnum);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWins))
		return;

WUnknown IUnk;
HRESULT hr = ((_DGeoObjectWins *)ebGetObject (lpArgs, 1)) -> _NewEnum(IUnk.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) {
		try {
		WEnumVARIANT IWnds (IUnk);		// throws hr
	
			ebSetObject (lpArgs, 0, (DWORD)IWnds.detach());
		} catch (...) {
			TRACE("Could not QI IEnumVARIANT from IUnknown\n");
		}
	}
}

// ----------------------------------------------------------------------------
// propget_GeoObjectWins_Next
// ----------------------------------------------------------------------------
void propget_GeoObjectWins_Next (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObjectWins_Next);

// nächstes Item aus Enumerator geben lassen
VARIANT v;
HRESULT hr = ((IEnumVARIANT *)ebGetObject (lpArgs, 1)) -> Next (1, &v, NULL);
_DGeoObjectWin *pIWnd = (_DGeoObjectWin *)ebGetObject (lpArgs, 0);

	RELEASE(pIWnd);
	ebSetObject (lpArgs, 0, NULL);

	if (S_OK == hr) {
	VARIANT vDisp;

		VariantInit(&vDisp);
		hr = VariantChangeType (&vDisp, &v, 0, VT_DISPATCH);

		if (SUCCEEDED(hr) && NULL != V_DISPATCH(&vDisp)) {
			hr = V_DISPATCH(&vDisp) -> QueryInterface (IID_DGeoObjectWin, (LPVOID *)&pIWnd);
			if (SUCCEEDED(hr)) 
				ebSetObject (lpArgs, 0, (DWORD)pIWnd);
			VariantClear (&vDisp);
		}
		VariantClear (&v);
	}
}

// ----------------------------------------------------------------------------
// propget_Document_Value
// ----------------------------------------------------------------------------
void propget_Document_Value (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Document_Value);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

CComBSTR bstrValue;		
HRESULT hr = ((_DDocument *)ebGetObject (lpArgs, 1)) -> get_Value(CLEARED(&bstrValue));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr)) {
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrValue));
	} else
		ebSetString (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// propget_Document_Name
// ----------------------------------------------------------------------------
void propget_Document_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Document_Name);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

CComBSTR bstrValue;
HRESULT hr = ((_DDocument *)ebGetObject (lpArgs, 1)) -> get_Name(CLEARED(&bstrValue));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr)) {
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrValue));
	} else
		ebSetString (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propget_Document_Path
// ----------------------------------------------------------------------------
void propget_Document_Path (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Document_Path);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

CComBSTR bstrPath;
HRESULT hr = ((_DDocument *)ebGetObject (lpArgs, 1)) -> get_Path(CLEARED(&bstrPath));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr)) {
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrPath));
	} else
		ebSetString (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propget_Document_FullName
// ----------------------------------------------------------------------------
void propget_Document_FullName (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Document_FullName);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

CComBSTR bstrValue;		
HRESULT hr = ((_DDocument *)ebGetObject (lpArgs, 1)) -> get_FullName(CLEARED(&bstrValue));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr)) {
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrValue));
	} else
		ebSetString (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// propget_Document_GetActiveView
// ----------------------------------------------------------------------------
void propget_Document_GetActiveView (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Document_GetActiveView);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;
		
	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

CComBSTR bstrView;	
HRESULT hr = ((_DDocument *)ebGetObject (lpArgs, 1)) -> get_ActiveViewName (CLEARED(&bstrView));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr)) {
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrView));
	} else
		ebSetString (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propset_Document_ActiveView
// ----------------------------------------------------------------------------
void propset_Document_ActiveView (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_Document_ActiveView);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

ebHSUB hStr = ebGetString (lpArgs, 2);		// 1st argument
CComBSTR bstrView (ebLockString (hThread, hStr));

	if (bstrView) {
		SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));
		((_DDocument *)ebGetObject (lpArgs, 1)) -> put_ActiveViewName (bstrView);
	}
	ebUnlockString (hThread, hStr);
}

// ----------------------------------------------------------------------------
// propget_Document_GeoObjectCount 
// ----------------------------------------------------------------------------
void propget_Document_GeoObjectCount (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Document_GeoObjectCount);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;
		
	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

long lCnt = 0L;
HRESULT hr = ((_DDocument *)ebGetObject (lpArgs, 1)) -> get_ObjectCount (&lCnt);

	if (FAILED(hr))
		lCnt = 0L;

	ebSetLong (lpArgs, 0, lCnt);
}

// ----------------------------------------------------------------------------
// propget_Document_GeoViewCount 
// ----------------------------------------------------------------------------
void propget_Document_GeoViewCount (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Document_GeoViewCount);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;
		
	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

long lCnt = 0L;
HRESULT hr = ((_DDocument *)ebGetObject (lpArgs, 1)) -> get_ViewCount (&lCnt);

	if (FAILED(hr))
		lCnt = 0L;

	ebSetLong (lpArgs, 0, lCnt);
}

// ----------------------------------------------------------------------------
// propget_Document_GeoClassCount 
// ----------------------------------------------------------------------------
void propget_Document_GeoClassCount (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Document_GeoClassCount);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;
		
	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

long lCnt = 0L;
HRESULT hr = ((_DDocument *)ebGetObject (lpArgs, 1)) -> get_ClassCount (&lCnt);

	if (FAILED(hr))
		lCnt = 0L;

	ebSetLong (lpArgs, 0, lCnt);
}

// ----------------------------------------------------------------------------
// command_Document_CloseIt
// ----------------------------------------------------------------------------
void command_Document_CloseIt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_Document_CloseIt);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));

	ebSignal (hThread, true);
	((_DDocument *)ebGetObject (lpArgs, 1)) -> CloseIt(v1, v2);
	ebSignal (hThread, false);
}

// ----------------------------------------------------------------------------
// command_Document_Save
// ----------------------------------------------------------------------------
void command_Document_Save (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_Document_Save);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));
	((_DDocument *)ebGetObject (lpArgs, 1)) -> Save();
}


// ----------------------------------------------------------------------------
// command_Document_SaveAs
// ----------------------------------------------------------------------------
void command_Document_SaveAs (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_Document_SaveAs);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

ebHSUB hStr = ebGetString (lpArgs, 2);
CComBSTR bstrName (ebLockString (hThread, hStr));
	
	((_DDocument *)ebGetObject (lpArgs, 1)) -> SaveAs(bstrName);
	
	ebUnlockString (hThread, hStr);
}


// ----------------------------------------------------------------------------
// function_Document_GetViews
// ----------------------------------------------------------------------------
void function_Document_GetViews (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Document_GetViews);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

WDViews Views;
HRESULT hr = ((DDocument *)ebGetObject (lpArgs, 1)) -> GetViews (Views.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Views.detach());
}


// ----------------------------------------------------------------------------
// function_Document_GetView
// ----------------------------------------------------------------------------
void function_Document_GetView (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Document_GetView);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

ebHSUB hStr = ebGetString (lpArgs, 2);
CComBSTR bstrName (ebLockString (hThread, hStr));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));

WDView View;
HRESULT hr = ((_DDocument *)ebGetObject (lpArgs, 1)) -> GetView (bstrName, v2, View.ppi());

	ebUnlockString (hThread, hStr);
	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)View.detach());
}


// ----------------------------------------------------------------------------
// function_Document_AddView
// ----------------------------------------------------------------------------
void function_Document_AddView (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Document_AddView);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

ebHSUB hStr = ebGetString (lpArgs, 2);
CComBSTR bstrName (ebLockString (hThread, hStr));
CComVariant v2;
	
	V_VT(&v2) = VT_I4;	// Add: default ohne create
	V_I4(&v2) = VIEWMODE_Add;

WDView View;
HRESULT hr = ((DDocument *)ebGetObject (lpArgs, 1)) -> GetView (bstrName, v2, View.ppi());

	ebUnlockString (hThread, hStr);

	if (NULL != lpArgs[0]) {	// nur, wenn nicht method
		ebSetObject (lpArgs, 0, NULL);
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)View.detach());
	}
}


// ----------------------------------------------------------------------------
// function_Document_ReplaceView
// ----------------------------------------------------------------------------
void function_Document_ReplaceView (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Document_ReplaceView);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

ebHSUB hStr = ebGetString (lpArgs, 2);
CComBSTR bstrName (ebLockString (hThread, hStr));
CComVariant v2;
	
	V_VT(&v2) = VT_I4;	// Add: default ohne create
	V_I4(&v2) = VIEWMODE_Replace;

WDView View;
HRESULT hr = ((DDocument *)ebGetObject (lpArgs, 1)) -> GetView (bstrName, v2, View.ppi());

	ebUnlockString (hThread, hStr);

	if (NULL != lpArgs[0]) {	// nur, wenn nicht method
		ebSetObject (lpArgs, 0, NULL);
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)View.detach());
	}
}


// ----------------------------------------------------------------------------
// command_Document_RemoveView
// ----------------------------------------------------------------------------
void command_Document_RemoveView (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_Document_RemoveView);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

ebHSUB hStr = ebGetString (lpArgs, 2);
CComBSTR bstrName (ebLockString (hThread, hStr));
CComVariant v2;

	V_VT(&v2) = VT_I4;
	V_I4(&v2) = VIEWMODE_Remove;

WDView Dummy;

	((DDocument *)ebGetObject (lpArgs, 1)) -> GetView (bstrName, v2, Dummy.ppi());
	ebUnlockString (hThread, hStr);
}


// ----------------------------------------------------------------------------
// function_Document_GetClasses
// ----------------------------------------------------------------------------
void function_Document_GetClasses (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Document_GetClasses);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

WDGeoClasses Clss;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((DDocument *)ebGetObject (lpArgs, 1)) -> GetClasses (v1, v2, Clss.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Clss.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_Document_GetClass
// ----------------------------------------------------------------------------
void function_Document_GetClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Document_GetClass);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

WDGeoClass Cls;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant v3 (GEOCLASSMODE_Get, VT_I4);
HRESULT hr = ((DDocument *)ebGetObject (lpArgs, 1)) -> GetClassEx (v1, v2, v3, Cls.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Cls.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// function_Document_AddClass
// ----------------------------------------------------------------------------
void function_Document_AddClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Document_AddClass);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

WDGeoClass Cls;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((DDocument *)ebGetObject (lpArgs, 1)) -> AddClass (v1, v2, Cls.ppi());

	if (NULL != lpArgs[0]) {	// nur, wenn nicht method
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Cls.detach());			
		else
			ebSetObject (lpArgs, 0, NULL);
	}
}

// ----------------------------------------------------------------------------
// function_Document_ReplaceClass
// ----------------------------------------------------------------------------
void function_Document_ReplaceClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Document_ReplaceClass);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

WDGeoClass Cls;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (GEOCLASSMODE_Replace, VT_I4);

HRESULT hr = ((DDocument *)ebGetObject (lpArgs, 1)) -> GetClass (v1, v2, Cls.ppi());

	if (NULL != lpArgs[0]) {	// nur, wenn nicht method
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Cls.detach());
		else
			ebSetObject (lpArgs, 0, NULL);
	}
}

// ----------------------------------------------------------------------------
// command_Document_RemoveClass
// ----------------------------------------------------------------------------
void command_Document_RemoveClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_Document_RemoveClass);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (GEOCLASSMODE_Remove, VT_I4);

WDGeoClass Dummy;

	((DDocument *)ebGetObject (lpArgs, 1)) -> GetClass (v1, v2, Dummy.ppi());
}


// ----------------------------------------------------------------------------
// function_Document_GetObjects
// ----------------------------------------------------------------------------
void function_Document_GetObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Document_GetObjects);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

WDGeoObjects Objs;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((DDocument *)ebGetObject (lpArgs, 1)) -> GetObjects (v1, v2, Objs.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// function_Document_QueryObjects
// ----------------------------------------------------------------------------
void function_Document_QueryObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Document_QueryObjects);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

WDGeoObjects Objs;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant v3 (MakeVARIANT (hThread, iNumArgs, lpArgs, 4));
HRESULT hr = ((DDocument *)ebGetObject (lpArgs, 1)) -> QueryObjects (v1, v2, v3, Objs.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// function_Document_GetObject
// ----------------------------------------------------------------------------
void function_Document_GetObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Document_GetObject);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

WDGeoObject Obj;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));	
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));

	if (FAILED(GetObjectNumber(v1)))
		return;

HRESULT hr = ((DDocument *)ebGetObject (lpArgs, 1)) -> GetObject (v1, v2, Obj.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Obj.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_Document_AddObject
// ----------------------------------------------------------------------------
void function_Document_AddObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Document_AddObject);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

WDGeoObject Obj;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));

	if (FAILED(GetObjectNumber(v1)))
		return;

HRESULT hr = ((DDocument *)ebGetObject (lpArgs, 1)) -> AddObject (v1, v2, Obj.ppi());

	if (NULL != lpArgs[0]) {
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Obj.detach());
		else
			ebSetObject (lpArgs, 0, NULL);
	}
}


// ----------------------------------------------------------------------------
// function_Document_ReplaceObject
// ----------------------------------------------------------------------------
void function_Document_ReplaceObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Document_ReplaceObject);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (GEOOBJECTMODE_Replace, VT_I4);

	if (FAILED(GetObjectNumber(v1)))
		return;

WDGeoObject Obj;
HRESULT hr = ((DDocument *)ebGetObject (lpArgs, 1)) -> GetObject (v1, v2, Obj.ppi());

	if (NULL != lpArgs[0]) {
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Obj.detach());
		else
			ebSetObject (lpArgs, 0, NULL);
	}
}


// ----------------------------------------------------------------------------
// command_Document_RemoveObject
// ----------------------------------------------------------------------------
void command_Document_RemoveObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_Document_RemoveObject);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));	
CComVariant v2 (GEOOBJECTMODE_Remove, VT_I4);

	if (FAILED(GetObjectNumber(v1)))
		return;

WDGeoObject Dummy;

	((DDocument *)ebGetObject (lpArgs, 1)) -> GetObject (v1, v2, Dummy.ppi());
}


// ----------------------------------------------------------------------------
// function_Document_GetHeaderEntry
// ----------------------------------------------------------------------------
void function_Document_GetHeaderEntry (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Document_GetHeaderEntry);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

	if (2 == iNumArgs) {
	ebHSUB hStr = ebGetString (lpArgs, 2);
	CComBSTR bstrKey (ebLockString (hThread, hStr));
	CComBSTR bstrText;
	HRESULT hr = ((_DDocument *)ebGetObject (lpArgs, 1)) -> GetHeaderEntry(bstrKey, CLEARED(&bstrText));

		ebFreeString (hThread, ebGetString (lpArgs, 0));
		if (SUCCEEDED(hr)) {
			ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrText));
		} else
			ebSetString (lpArgs, 0, NULL);
		
		ebUnlockString (hThread, hStr);
	}
	else if (3 == iNumArgs) {
	ebHSUB hStr1 = ebGetString (lpArgs, 2);
	CComBSTR bstrDataSource (ebLockString (hThread, hStr1));
	ebHSUB hStr2 = ebGetString (lpArgs, 3);
	CComBSTR bstrKey (ebLockString (hThread, hStr2));

	CComBSTR bstrText;
	HRESULT hr = ((_DDocument *)ebGetObject (lpArgs, 1)) -> GetHeaderEntryEx(bstrDataSource, bstrKey, CLEARED(&bstrText));

		ebFreeString (hThread, ebGetString (lpArgs, 0));
		if (SUCCEEDED(hr)) {
			ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrText));
		} else
			ebSetString (lpArgs, 0, NULL);
		
		ebUnlockString (hThread, hStr2);
		ebUnlockString (hThread, hStr1);
	}
	else {
		_ASSERTE(SUCCEEDED(E_INVALIDARG));
	}
}

// ----------------------------------------------------------------------------
// function_Document_SetHeaderEntry
// ----------------------------------------------------------------------------
void function_Document_SetHeaderEntry (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Document_SetHeaderEntry);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

	if (3 == iNumArgs) {
	ebHSUB hStr1 = ebGetString (lpArgs, 2);
	CComBSTR bstrKey (ebLockString (hThread, hStr1));
	ebHSUB hStr2 = ebGetString (lpArgs, 3);
	CComVariant vVal(ebLockString (hThread, hStr2));

	HRESULT hr = ((_DDocument *)ebGetObject (lpArgs, 1)) -> SetHeaderEntry (bstrKey, vVal);

		if (NULL != lpArgs[0])
			ebSetInt (lpArgs, 0, SUCCEEDED(hr) ? ebTRUE : ebFALSE);

		ebUnlockString (hThread, hStr2);
		ebUnlockString (hThread, hStr1);
	}
	else if (4 == iNumArgs) {
	ebHSUB hStr1 = ebGetString (lpArgs, 2);
	CComBSTR bstrDataSource (ebLockString (hThread, hStr1));
	ebHSUB hStr2 = ebGetString (lpArgs, 3);
	CComBSTR bstrKey (ebLockString (hThread, hStr2));
	ebHSUB hStr3 = ebGetString (lpArgs, 4);
	CComVariant vVal(ebLockString (hThread, hStr3));

	HRESULT hr = ((_DDocument *)ebGetObject (lpArgs, 1)) -> SetHeaderEntryEx (bstrDataSource, bstrKey, vVal);

		if (NULL != lpArgs[0])
			ebSetInt (lpArgs, 0, SUCCEEDED(hr) ? ebTRUE : ebFALSE);

		ebUnlockString (hThread, hStr3);
		ebUnlockString (hThread, hStr2);
		ebUnlockString (hThread, hStr1);
	}
	else {
		_ASSERTE(SUCCEEDED(E_INVALIDARG));
	}

}

// ----------------------------------------------------------------------------
// function_Document_RemoveHeaderEntry
// ----------------------------------------------------------------------------
void function_Document_RemoveHeaderEntry (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Document_RemoveHeaderEntry);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

CComVariant v2;

	V_VT(&v2) = VT_ERROR;
	V_ERROR(&v2) = DISP_E_PARAMNOTFOUND;

	if (2 == iNumArgs) {
	// Ohne Datenquelle: Parameter ist Key
		SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

	ebHSUB hStr1 = ebGetString (lpArgs, 2);
	CComBSTR bstrKey (ebLockString (hThread, hStr1));

	HRESULT hr = ((_DDocument *)ebGetObject (lpArgs, 1)) -> SetHeaderEntry (bstrKey, v2);

		if (NULL != lpArgs[0])
			ebSetInt (lpArgs, 0, SUCCEEDED(hr) ? true : false);

		ebUnlockString (hThread, hStr1);
	} 
	else if (3 == iNumArgs) {
	// mit Datenquelle: Parameter1 ist Datenquelle, Parameter2 ist Key
	ebHSUB hStr1 = ebGetString (lpArgs, 2);
	CComBSTR bstrDataSource (ebLockString (hThread, hStr1));
	ebHSUB hStr2 = ebGetString (lpArgs, 3);
	CComBSTR bstrKey (ebLockString (hThread, hStr2));

	HRESULT hr = ((_DDocument *)ebGetObject (lpArgs, 1)) -> SetHeaderEntryEx(bstrDataSource, bstrKey, v2);

		if (NULL != lpArgs[0])
			ebSetInt (lpArgs, 0, SUCCEEDED(hr) ? true : false);

		ebUnlockString (hThread, hStr2);
		ebUnlockString (hThread, hStr1);
	}
	else {
		_ASSERTE(SUCCEEDED(E_INVALIDARG));
	}
}

// ----------------------------------------------------------------------------
// command_Document_RePaint
// ----------------------------------------------------------------------------

void command_Document_RePaint (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_Document_RePaint);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

CComVariant vXMin, vXMax, vYMin, vYMax;

	V_VT(&vXMin) = 	V_VT(&vXMax) = V_VT(&vYMin) = V_VT(&vYMax) = VT_R8;
	if (iNumArgs > 1) 
		V_R8(&vXMin) = ebGetDouble (lpArgs, 2);
	else {
		V_VT(&vXMin) = VT_ERROR;
		V_ERROR(&vXMin) = DISP_E_PARAMNOTFOUND;
	}
	V_R8(&vYMin) = iNumArgs > 2 ? ebGetDouble (lpArgs, 3) : -1.0;
	V_R8(&vXMax)= iNumArgs > 3 ? ebGetDouble (lpArgs, 4) : -1.0;
	V_R8(&vYMax) = iNumArgs > 4 ? ebGetDouble (lpArgs, 5) : -1.0;

	if (V_R8(&vXMin) == 0.0) V_R8(&vXMin) = -1.0;
	((_DDocument *)ebGetObject (lpArgs, 1)) -> RePaint (vXMin, vYMin, vXMax, vYMax);
}


// ----------------------------------------------------------------------------
// command_Document_ReBuild
// ----------------------------------------------------------------------------

void command_Document_ReBuild (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_Document_ReBuild);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

CComVariant v (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));

	((_DDocument *)ebGetObject (lpArgs, 1)) -> ReBuild(v);
}


// ----------------------------------------------------------------------------
// function_Document_GetGeoObjectWins
// ----------------------------------------------------------------------------
void function_Document_GetGeoObjectWins (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Document_GetGeoObjectWins);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

WDGeoObjectWins Wins;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((DDocument *)ebGetObject (lpArgs, 1)) -> GetGeoObjectWins (v1, v2, Wins.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Wins.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_Document_GetGeoObjectWin
// ----------------------------------------------------------------------------
void function_Document_GetGeoObjectWin (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Document_GetGeoObjectWin);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

WDGeoObjectWin Win;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((DDocument *)ebGetObject (lpArgs, 1)) -> GetGeoObjectWin (v1, v2, Win.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Win.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_Document_AddGeoObjectWin
// ----------------------------------------------------------------------------
void function_Document_AddGeoObjectWin (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_Document_AddGeoObjectWin);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

WDGeoObjectWin Win;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));	
CComVariant v2 (GEOOBJWINMODE_Add, VT_I4);
HRESULT hr = ((DDocument *)ebGetObject (lpArgs, 1)) -> GetGeoObjectWin (v1, v2, Win.ppi());

	if (NULL != lpArgs[0]) {
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Win.detach());
		else
			ebSetObject (lpArgs, 0, NULL);
	}
}


// ----------------------------------------------------------------------------
// command_Document_RemoveGeoObjectWin
// ----------------------------------------------------------------------------
void command_Document_RemoveGeoObjectWin (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_Document_RemoveGeoObjectWin);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

WDGeoObjectWin Win;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));	
CComVariant v2 (GEOOBJWINMODE_Remove, VT_I4);

	((DDocument *)ebGetObject (lpArgs, 1)) -> GetGeoObjectWin (v1, v2, Win.ppi());
}

// ----------------------------------------------------------------------------
// CreateGeoObjectsCollection_Document_command
// ----------------------------------------------------------------------------
void CreateGeoObjectsCollection_Document_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(CreateGeoObjectsCollection_Document_command);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

WDGeoObjects Objs;		// Ergebnis
HRESULT hr = ((DDocument *)ebGetObject (lpArgs, 1)) -> CreateGeoObjectsCollection (Objs.ppi());

	if (SUCCEEDED(hr))
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);		// some error
}

// ----------------------------------------------------------------------------
// propget_Document_RefScale
// ----------------------------------------------------------------------------
void propget_Document_RefScale (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Document_RefScale);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

LONG lRefScale = 0;
HRESULT hr = ((DDocument *)ebGetObject (lpArgs, 1)) -> get_RefScale(&lRefScale);

	ebSetLong (lpArgs, 0, 0);
	if (SUCCEEDED(hr))
		ebSetLong (lpArgs, 0, lRefScale);
}

// ----------------------------------------------------------------------------
// propset_Document_RefScale
// ----------------------------------------------------------------------------
void propset_Document_RefScale (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_Document_RefScale);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));
	((DDocument *)ebGetObject (lpArgs, 1)) -> put_RefScale(ebGetLong(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// propget_Document_IsDirty
// ----------------------------------------------------------------------------
void propget_Document_IsDirty (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Document_IsDirty);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

VARIANT_BOOL fIsDirty = VARIANT_FALSE;
HRESULT hr = ((DDocument *)ebGetObject (lpArgs, 1)) -> get_IsDirty (&fIsDirty);

	ebSetBool (lpArgs, 0, fIsDirty);
}

// ----------------------------------------------------------------------------
// propset_Document_IsDirty
// ----------------------------------------------------------------------------
void propset_Document_IsDirty (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_Document_IsDirty);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));
	((DDocument *)ebGetObject (lpArgs, 1)) -> put_IsDirty (ebGetBool(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// propset_Document_CanRepaint
// ----------------------------------------------------------------------------
void propset_Document_CanRepaint (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_Document_CanRepaint);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));
	((DDocument *)ebGetObject (lpArgs, 1)) -> put_PreventRepaint (ebGetBool(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// propget_Document_CanRepaint
// ----------------------------------------------------------------------------
void propget_Document_CanRepaint (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Document_CanRepaint);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

	SetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1));

VARIANT_BOOL fIsDirty = VARIANT_FALSE;
HRESULT hr = ((DDocument *)ebGetObject (lpArgs, 1)) -> get_PreventRepaint (&fIsDirty);

	ebSetBool (lpArgs, 0, fIsDirty);
}

// ----------------------------------------------------------------------------
// propget_Document_ContextDataSource
// ----------------------------------------------------------------------------
void propget_Document_ContextDataSource (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Document_ContextDataSource);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

CComBSTR bstrCtx;

	if (SUCCEEDED(GetCtxDataSource (hThread, (_DDocument *)ebGetObject (lpArgs, 1), &bstrCtx)))
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrCtx));
	else
		ebSetString (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propget_Document_Connections
// ----------------------------------------------------------------------------
void propget_Document_Connections (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Document_Connections);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Document))
		return;

WTRiASConnections Conns;
HRESULT hr = ((DDocument *)ebGetObject (lpArgs, 1)) -> get_Connections (Conns.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Conns.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propget_Connections_NewEnum
// ----------------------------------------------------------------------------
void propget_Connections_NewEnum (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Connections_NewEnum);

WUnknown IUnk;	
HRESULT hr = ((ITRiASConnections *)ebGetObject (lpArgs, 1)) -> _NewEnum(IUnk.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) {
		try {
		WEnumVARIANT Enum (IUnk);		// throws hr
	
			ebSetObject (lpArgs, 0, (DWORD)Enum.detach());
		} catch (...) {
			TRACE("Could not QI IEnumVARIANT from IUnknown\n");
		}
	}
}

// ----------------------------------------------------------------------------
// propget_Connections_Next
// ----------------------------------------------------------------------------
void propget_Connections_Next (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Connections_Next);

// nächstes Item aus Enumerator geben lassen
CComVariant v;
HRESULT hr = ((IEnumVARIANT *)ebGetObject (lpArgs, 1)) -> Next (1, &v, NULL);
ITRiASConnection *pIConn = (ITRiASConnection *)ebGetObject (lpArgs, 0);

	RELEASE(pIConn);

	ebSetObject (lpArgs, 0, NULL);
	if (S_OK == hr) {
	CComVariant vDisp;

		hr = vDisp.ChangeType (VT_DISPATCH, &v);
		if (SUCCEEDED(hr) && NULL != V_DISPATCH(&vDisp)) {
		WTRiASConnection Conn;

			hr = V_DISPATCH(&vDisp) -> QueryInterface (Conn.ppi());
			if (SUCCEEDED(hr)) 
				ebSetObject (lpArgs, 0, (DWORD)Conn.detach());
		}
	}
}

// ----------------------------------------------------------------------------
// propget_Connection_Name
// ----------------------------------------------------------------------------
void propget_Connection_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_Connection_Name);

CComBSTR bstrValue;
HRESULT hr = ((ITRiASConnection *)ebGetObject (lpArgs, 1)) -> get_Name (CLEARED(&bstrValue));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr))
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrValue));
	else
		ebSetString (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propget_View_Value
// ----------------------------------------------------------------------------
void propget_View_Value (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_View_Value);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

CComBSTR bstrValue;		
HRESULT hr = ((_DView *)ebGetObject (lpArgs, 1)) -> get_Value(CLEARED(&bstrValue));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr)) 
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrValue));
	else
		ebSetString (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propget_View_Name
// ----------------------------------------------------------------------------
void propget_View_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_View_Name);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

CComBSTR bstrValue;
HRESULT hr = ((_DView *)ebGetObject (lpArgs, 1)) -> get_Name(CLEARED(&bstrValue));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr))
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrValue));
	else
		ebSetString (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propset_View_Name
// ----------------------------------------------------------------------------
void propset_View_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_View_Name);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;
		
_DView *pIView = (_DView *)ebGetObject (lpArgs, 1);
ebHSUB hStr = ebGetString (lpArgs, 2);		// 1st argument
CComBSTR bstrValue (ebLockString (hThread, hStr));

	if (bstrValue)
		pIView -> put_Name (bstrValue);
		
	ebUnlockString (hThread, hStr);
}

// ----------------------------------------------------------------------------
// propget_View_Desc
// ----------------------------------------------------------------------------
void propget_View_Desc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_View_Desc);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

CComBSTR bstrValue;
HRESULT hr = ((DView *)ebGetObject (lpArgs, 1)) -> get_Description (CLEARED(&bstrValue));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr))
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrValue));
	else
		ebSetString (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propset_View_Desc
// ----------------------------------------------------------------------------
void propset_View_Desc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_View_Desc);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;
		
	USES_CONVERSION;

ebHSUB hStr = ebGetString (lpArgs, 2);		// 1st argument
CComBSTR bstrValue = SysAllocString (A2OLE(ebLockString (hThread, hStr)));

	if (NULL != (BSTR)bstrValue)
		((DView *)ebGetObject (lpArgs, 1)) -> put_Description (bstrValue);
		
	ebUnlockString (hThread, hStr);
}

// ----------------------------------------------------------------------------
// propget_View_ClipObject
// ----------------------------------------------------------------------------
void propget_View_ClipObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_View_ClipObject);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

WDGeoObject Obj;
HRESULT hr = ((DView *)ebGetObject (lpArgs, 1)) -> GetClipObject(Obj.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Obj.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}
		
// ----------------------------------------------------------------------------
// propset_View_ClipObject
// ----------------------------------------------------------------------------
void propset_View_ClipObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_View_ClipObject);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

HRESULT hr = ((DView *)ebGetObject (lpArgs, 1)) -> SetClipObject((DGeoObject *)ebGetObject (lpArgs, 2));

	if (NULL != lpArgs[0]) {	// nur, wenn Funktion
		if (SUCCEEDED(hr)) 
			ebSetBool (lpArgs, 0, -1);
		else
			ebSetBool (lpArgs, 0, 0);
	}
}
		
// ----------------------------------------------------------------------------
// propset_View_ResetClipObject
// ----------------------------------------------------------------------------
void propset_View_ResetClipObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_View_ResetClipObject);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

	((DView *)ebGetObject (lpArgs, 1)) -> ResetClipObject();
}

// ----------------------------------------------------------------------------
// function_View_GetClasses
// ----------------------------------------------------------------------------
void function_View_GetClasses (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_View_GetClasses);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

WDGeoClasses Clss;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((DView *)ebGetObject (lpArgs, 1)) -> GetClasses (v1, v2, Clss.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Clss.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_View_GetClass
// ----------------------------------------------------------------------------
void function_View_GetClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_View_GetClass);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

WDGeoClass Cls;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant v3 (MakeVARIANT (hThread, iNumArgs, lpArgs, 4));
HRESULT hr = ((DView *)ebGetObject (lpArgs, 1)) -> GetClass (v1, v2, v3, Cls.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Cls.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_View_AddClass
// ----------------------------------------------------------------------------
void function_View_AddClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_View_AddClass);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

WDGeoClass Cls;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant v3 (GEOCLASSMODE_Add, VT_I4); 

HRESULT hr = ((DView *)ebGetObject (lpArgs, 1)) -> GetClass (v1, v2, v3, Cls.ppi());

	if (NULL != lpArgs[0]) {
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Cls.detach());
		else
			ebSetObject (lpArgs, 0, NULL);
	}
}


// ----------------------------------------------------------------------------
// function_View_ReplaceClass
// ----------------------------------------------------------------------------
void function_View_ReplaceClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_View_ReplaceClass);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

WDGeoClass Cls;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant v3 (GEOCLASSMODE_Replace, VT_I4); 

HRESULT hr = ((DView *)ebGetObject (lpArgs, 1)) -> GetClass (v1, v2, v3, Cls.ppi());

	if (NULL != lpArgs[0]) {
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Cls.detach());
		else
			ebSetObject (lpArgs, 0, NULL);
	}
}


// ----------------------------------------------------------------------------
// command_View_RemoveClass
// ----------------------------------------------------------------------------
void command_View_RemoveClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_View_RemoveClass);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant v3 (GEOCLASSMODE_Remove, VT_I4); 
WDGeoClass Dummy;

	((DView *)ebGetObject (lpArgs, 1)) -> GetClass (v1, v2, v3, Dummy.ppi());
}


// ----------------------------------------------------------------------------
// function_View_GetObjects
// ----------------------------------------------------------------------------
void function_View_GetObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_View_GetObjects);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

WDGeoObjects Objs;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((DView *)ebGetObject (lpArgs, 1)) -> GetObjects (v1, v2, Objs.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_View_GetObject
// ----------------------------------------------------------------------------
void function_View_GetObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_View_GetObject);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));	

	if (FAILED(GetObjectNumber(v1)))
		return;

WDGeoObject Obj;
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((DView *)ebGetObject (lpArgs, 1)) -> GetObject (v1, v2, Obj.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Obj.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_View_AddObject
// ----------------------------------------------------------------------------
void function_View_AddObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_View_AddObject);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));	

	if (FAILED(GetObjectNumber(v1)))
		return;

WDGeoObject Obj;
CComVariant v2(GEOOBJECTMODE_Add);
HRESULT hr = ((DView *)ebGetObject (lpArgs, 1)) -> GetObject (v1, v2, Obj.ppi());

	if (NULL != lpArgs[0]) {
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Obj.detach());
		else
			ebSetObject (lpArgs, 0, NULL);
	}
}


// ----------------------------------------------------------------------------
// function_View_ReplaceObject
// ----------------------------------------------------------------------------
void function_View_ReplaceObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_View_ReplaceObject);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));	
CComVariant v2 (GEOOBJECTMODE_Replace, VT_I4);

	if (FAILED(GetObjectNumber(v1)))
		return;

WDGeoObject Obj;
HRESULT hr = ((DView *)ebGetObject (lpArgs, 1)) -> GetObject (v1, v2, Obj.ppi());

	if (NULL != lpArgs[0]) {
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Obj.detach());
		else
			ebSetObject (lpArgs, 0, NULL);
	}
}


// ----------------------------------------------------------------------------
// command_View_RemoveObject
// ----------------------------------------------------------------------------
void command_View_RemoveObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_View_RemoveObject);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));	
CComVariant v2 (GEOOBJECTMODE_Remove, VT_I4);

	if (FAILED(GetObjectNumber(v1)))
		return;

WDGeoObject Dummy;

	((DView *)ebGetObject (lpArgs, 1)) -> GetObject (v1, v2, Dummy.ppi());
}


// ----------------------------------------------------------------------------
// function_View_GetFeatures
// ---------------------------------------------------------------------------
void function_View_GetFeatures (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_View_GetFeatures);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

WDGeoFeatures Feats;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((DView *)ebGetObject (lpArgs, 1)) -> GetFeatures (v1, v2, Feats.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Feats.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_View_GetFeature
// ----------------------------------------------------------------------------
void function_View_GetFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_View_GetFeature);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

WDGeoFeature Feat;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((DView *)ebGetObject (lpArgs, 1)) -> GetFeature (v1, v2, Feat.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Feat.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_View_AddFeature
// ----------------------------------------------------------------------------
void function_View_AddFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_View_AddFeature);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

WDGeoFeature Feat;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (FEATUREMODE_Add, VT_I4);
HRESULT hr = ((DView *)ebGetObject (lpArgs, 1)) -> GetFeature (v1, v2, Feat.ppi());

	if (NULL != lpArgs[0]) {
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Feat.detach());
		else
			ebSetObject (lpArgs, 0, NULL);
	}
}


// ----------------------------------------------------------------------------
// function_View_ReplaceFeature
// ----------------------------------------------------------------------------
void function_View_ReplaceFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_View_ReplaceFeature);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

WDGeoFeature Feat;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (FEATUREMODE_Replace, VT_I4);
HRESULT hr = ((DView *)ebGetObject (lpArgs, 1)) -> GetFeature (v1, v2, Feat.ppi());

	if (NULL != lpArgs[0]) {
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Feat.detach());
		else
			ebSetObject (lpArgs, 0, NULL);
	}
}


// ----------------------------------------------------------------------------
// command_View_RemoveFeature
// ----------------------------------------------------------------------------
void command_View_RemoveFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_View_RemoveFeature);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

WDGeoFeature Feat;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (FEATUREMODE_Remove, VT_I4);

	((DView *)ebGetObject (lpArgs, 1)) -> GetFeature (v1, v2, Feat.ppi());
}

// ----------------------------------------------------------------------------
// function_View_GetObjectsInWindow
// ----------------------------------------------------------------------------
void function_View_GetObjectsInWindow (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_View_GetObjectsInWindow);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

WDGeoObjects Objs;
CComVariant vXMax(iNumArgs > 3 ? ebGetDouble (lpArgs, 4) : ebGetDouble (lpArgs, 2));
CComVariant vYMax(iNumArgs > 4 ? ebGetDouble (lpArgs, 5) : ebGetDouble (lpArgs, 3));
HRESULT hr = ((DView *)ebGetObject (lpArgs, 1)) -> GetObjectsInRect (ebGetDouble (lpArgs, 2), ebGetDouble (lpArgs, 3), vXMax, vYMax, Objs.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else 
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propget_View_RefScale
// ----------------------------------------------------------------------------
void propget_View_RefScale (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_View_RefScale);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

LONG lRefScale = 0;
HRESULT hr = ((DView *)ebGetObject (lpArgs, 1)) -> get_RefScale(&lRefScale);

	ebSetLong (lpArgs, 0, 0);
	if (SUCCEEDED(hr))
		ebSetLong (lpArgs, 0, lRefScale);
}

// ----------------------------------------------------------------------------
// propset_View_RefScale
// ----------------------------------------------------------------------------
void propset_View_RefScale (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_View_RefScale);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

	((DView *)ebGetObject (lpArgs, 1)) -> put_RefScale(ebGetLong(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// propget_View_Scale
// ----------------------------------------------------------------------------
void propget_View_Scale (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_View_Scale);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

LONG lScale = 0;
HRESULT hr = ((DView *)ebGetObject (lpArgs, 1)) -> get_Scale(&lScale);

	ebSetLong (lpArgs, 0, 0);
	if (SUCCEEDED(hr))
		ebSetLong (lpArgs, 0, lScale);
}

// ----------------------------------------------------------------------------
// propset_View_Scale
// ----------------------------------------------------------------------------
void propset_View_Scale (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_View_Scale);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

	((DView *)ebGetObject (lpArgs, 1)) -> put_Scale(ebGetLong(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// command_View_GetConstraintRect
// ----------------------------------------------------------------------------
void command_View_GetConstraintRect (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_View_GetConstraintRect);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

double dX = 0.0;
double dY = 0.0;
CComVariant dXMax (0.0);
CComVariant dYMax (0.0);

	((DView *)ebGetObject (lpArgs, 1)) -> GetConstraintRect(&dX, &dY, &dXMax, &dYMax);

// Ergebnisse liefern
	ebSetDouble (lpArgs, 2, dX);
	ebSetDouble (lpArgs, 3, dY);
	if (SUCCEEDED(dXMax.ChangeType (VT_R8)))
		ebSetDouble (lpArgs, 4, V_R8(&dXMax));
	else
		ebSetDouble (lpArgs, 4, 0.0);
	
	if (SUCCEEDED(dYMax.ChangeType (VT_R8)))
		ebSetDouble (lpArgs, 5, V_R8(&dYMax));
	else
		ebSetDouble (lpArgs, 5, 0.0);
}

// ----------------------------------------------------------------------------
// command_View_SetConstraintRect
// ----------------------------------------------------------------------------
void command_View_SetConstraintRect (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_View_SetConstraintRect);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

CComVariant vXMax (iNumArgs > 3 ? ebGetDouble (lpArgs, 4) : ebGetDouble (lpArgs, 2));
CComVariant vYMax (iNumArgs > 4 ? ebGetDouble (lpArgs, 5) : ebGetDouble (lpArgs, 3));

	((DView *)ebGetObject (lpArgs, 1)) -> SetConstraintRect(ebGetDouble (lpArgs, 2), ebGetDouble (lpArgs, 3), vXMax, vYMax);
}

// ----------------------------------------------------------------------------
// command_View_GetActRect
// ----------------------------------------------------------------------------
void command_View_GetActRect (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_View_GetActRect);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

double dX = 0.0;
double dY = 0.0;
CComVariant dXMax (0.0);
CComVariant dYMax (0.0);

	((DView *)ebGetObject (lpArgs, 1)) -> GetActRect(&dX, &dY, &dXMax, &dYMax);

// Ergebnisse liefern
	ebSetDouble (lpArgs, 2, dX);
	ebSetDouble (lpArgs, 3, dY);
	if (SUCCEEDED(dXMax.ChangeType (VT_R8)))
		ebSetDouble (lpArgs, 4, V_R8(&dXMax));
	else
		ebSetDouble (lpArgs, 4, 0.0);
	
	if (SUCCEEDED(dYMax.ChangeType (VT_R8)))
		ebSetDouble (lpArgs, 5, V_R8(&dYMax));
	else
		ebSetDouble (lpArgs, 5, 0.0);
}

// ----------------------------------------------------------------------------
// command_View_SetActRect
// ----------------------------------------------------------------------------
void command_View_SetActRect (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_View_SetActRect);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoView))
		return;

CComVariant vXMax (iNumArgs > 3 ? ebGetDouble (lpArgs, 4) : ebGetDouble (lpArgs, 2));
CComVariant vYMax (iNumArgs > 4 ? ebGetDouble (lpArgs, 5) : ebGetDouble (lpArgs, 3));

	((DView *)ebGetObject (lpArgs, 1)) -> SetActRect(ebGetDouble (lpArgs, 2), ebGetDouble (lpArgs, 3), vXMax, vYMax);
}

// ----------------------------------------------------------------------------
// propget_GeoClass_Value
// ----------------------------------------------------------------------------
void propget_GeoClass_Value (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoClass_Value);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

CComBSTR bstrValue;
HRESULT hr = ((_DGeoClass *)ebGetObject (lpArgs, 1)) -> get_Value(CLEARED(&bstrValue));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr))
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrValue));
	else
		ebSetString (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propset_GeoClass_Value
// ----------------------------------------------------------------------------
void propset_GeoClass_Value (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_GeoClass_Value);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;
		
_DGeoClass *pIGeoClass = (_DGeoClass *)ebGetObject (lpArgs, 1);
ebHSUB hStr = ebGetString (lpArgs, 2);		// 1st argument
CComBSTR bstrValue (ebLockString (hThread, hStr));

	if (bstrValue)
		pIGeoClass -> put_Value (bstrValue);
		
	ebUnlockString (hThread, hStr);
}

// ----------------------------------------------------------------------------
// propget_GeoClass_Name
// ----------------------------------------------------------------------------

void propget_GeoClass_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoClass_Name);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

CComBSTR bstrValue;
HRESULT hr = ((_DGeoClass *)ebGetObject (lpArgs, 1)) -> get_Name(CLEARED(&bstrValue));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr))
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrValue));
	else
		ebSetString (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// propset_GeoClass_Name
// ----------------------------------------------------------------------------

void propset_GeoClass_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_GeoClass_Name);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;
		
_DGeoClass *pIGeoClass = (_DGeoClass *)ebGetObject (lpArgs, 1);
ebHSUB hStr = ebGetString (lpArgs, 2);		// 1st argument
CComBSTR bstrValue (ebLockString (hThread, hStr));

	if (bstrValue)
		pIGeoClass -> put_Name (bstrValue);
		
	ebUnlockString (hThread, hStr);
}


// ----------------------------------------------------------------------------
// propget_GeoClass_FullName
// ----------------------------------------------------------------------------

void propget_GeoClass_FullName (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoClass_FullName);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

CComBSTR bstrValue;
HRESULT hr = ((_DGeoClass *)ebGetObject (lpArgs, 1)) -> get_FullName(CLEARED(&bstrValue));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr))
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrValue));
	else
		ebSetString (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// propset_GeoClass_FullName
// ----------------------------------------------------------------------------

void propset_GeoClass_FullName (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_GeoClass_FullName);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;
		
_DGeoClass *pIGeoClass = (_DGeoClass *)ebGetObject (lpArgs, 1);
ebHSUB hStr = ebGetString (lpArgs, 2);		// 1st argument
CComBSTR bstrValue (ebLockString (hThread, hStr));
	
	pIGeoClass -> put_FullName (bstrValue);
	ebUnlockString (hThread, hStr);
}


// ----------------------------------------------------------------------------
// function_GeoClass_GetViews
// ----------------------------------------------------------------------------

void function_GeoClass_GetViews (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoClass_GetViews);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

CComVariant v1; 
	
	V_VT(&v1) = VT_I2;
	V_I2(&v1) = iNumArgs > 1 ? ebGetInt (lpArgs, 2) : (OTPunkt|OTLinie|OTFlaeche|OTText);
	
WDViews Views;
HRESULT hr = ((DGeoClass *)ebGetObject (lpArgs, 1)) -> GetViews (v1, Views.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Views.detach());
}


// ----------------------------------------------------------------------------
// function_GeoClass_GetObjects
// ----------------------------------------------------------------------------
void function_GeoClass_GetObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoClass_GetObjects);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

WDGeoObjects Objs;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((_DGeoClass *)ebGetObject (lpArgs, 1)) -> GetObjects (v1, v2, Objs.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_GeoClass_GetObject
// ----------------------------------------------------------------------------
void function_GeoClass_GetObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoClass_GetObject);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));

	if (FAILED(GetObjectNumber(v1)))
		return;

WDGeoObject Obj;
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((DGeoClass *)ebGetObject (lpArgs, 1)) -> GetObject (v1, v2, Obj.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Obj.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_GeoClass_AddObject
// ----------------------------------------------------------------------------
void function_GeoClass_AddObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoClass_AddObject);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));	
CComVariant v2 (GEOOBJECTMODE_Add, VT_I4); 

	if (FAILED(GetObjectNumber(v1)))
		return;

WDGeoObject Obj;
HRESULT hr = ((DGeoClass *)ebGetObject (lpArgs, 1)) -> GetObject (v1, v2, Obj.ppi());

	if (NULL != lpArgs[0]) {
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Obj.detach());
		else
			ebSetObject (lpArgs, 0, NULL);
	}
}


// ----------------------------------------------------------------------------
// function_GeoClass_ReplaceObject
// ----------------------------------------------------------------------------
void function_GeoClass_ReplaceObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoClass_ReplaceObject);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));	
CComVariant v2 (GEOOBJECTMODE_Replace, VT_I4);

	if (FAILED(GetObjectNumber(v1)))
		return;

WDGeoObject Obj;
HRESULT hr = ((DGeoClass *)ebGetObject (lpArgs, 1)) -> GetObject (v1, v2, Obj.ppi());

	if (NULL != lpArgs[0]) {
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Obj.detach());
		else
			ebSetObject (lpArgs, 0, NULL);
	}
}


// ----------------------------------------------------------------------------
// command_GeoClass_RemoveObject
// ----------------------------------------------------------------------------
void command_GeoClass_RemoveObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_GeoClass_RemoveObject);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));	

	if (FAILED(GetObjectNumber(v1)))
		return;

WDGeoObject Dummy;
CComVariant v2 (GEOOBJECTMODE_Remove, VT_I4);

	((DGeoClass *)ebGetObject (lpArgs, 1)) -> GetObject (v1, v2, Dummy.ppi());
}


// ----------------------------------------------------------------------------
// function_GeoClass_GetFeatures
// ----------------------------------------------------------------------------
void function_GeoClass_GetFeatures (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoClass_GetFeatures);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

WDGeoFeatures Feats;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((DGeoClass *)ebGetObject (lpArgs, 1)) -> GetFeatures (v1, v2, Feats.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Feats.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_GeoClass_GetFeature
// ----------------------------------------------------------------------------
void function_GeoClass_GetFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoClass_GetFeature);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

WDGeoFeature Feat;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((DGeoClass *)ebGetObject (lpArgs, 1)) -> GetFeature (v1, v2, Feat.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Feat.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_GeoClass_AddFeature
// ----------------------------------------------------------------------------
void function_GeoClass_AddFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoClass_AddFeature);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

WDGeoFeature Feat;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (FEATUREMODE_Add, VT_I4);
HRESULT hr = ((DGeoClass *)ebGetObject (lpArgs, 1)) -> GetFeature (v1, v2, Feat.ppi());

	if (NULL != lpArgs[0]) {
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Feat.detach());
		else
			ebSetObject (lpArgs, 0, NULL);
	}
}


// ----------------------------------------------------------------------------
// function_GeoClass_ReplaceFeature
// ----------------------------------------------------------------------------
void function_GeoClass_ReplaceFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoClass_ReplaceFeature);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

WDGeoFeature Feat;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (FEATUREMODE_Replace, VT_I4);
HRESULT hr = ((DGeoClass *)ebGetObject (lpArgs, 1)) -> GetFeature (v1, v2, Feat.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Feat.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// command_GeoClass_RemoveFeature
// ----------------------------------------------------------------------------
void command_GeoClass_RemoveFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_GeoClass_RemoveFeature);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

WDGeoFeature Dummy;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (FEATUREMODE_Remove, VT_I4);

	((DGeoClass *)ebGetObject (lpArgs, 1)) -> GetFeature (v1, v2, Dummy.ppi());
}


// ----------------------------------------------------------------------------
// function_GeoClass_GetObjectFeatures
// ----------------------------------------------------------------------------
void function_GeoClass_GetObjectFeatures (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoClass_GetObjectFeatures);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

WDGeoFeatures Feats;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((DGeoClass *)ebGetObject (lpArgs, 1)) -> GetObjectFeatures (v1, v2, Feats.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Feats.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_GeoClass_GetObjectFeature
// ----------------------------------------------------------------------------
void function_GeoClass_GetObjectFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoClass_GetObjectFeature);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

WDGeoFeature Feat;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((DGeoClass *)ebGetObject (lpArgs, 1)) -> GetObjectFeature (v1, v2, Feat.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Feat.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_GeoClass_AddObjectFeature
// ----------------------------------------------------------------------------
void function_GeoClass_AddObjectFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoClass_AddObjectFeature);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

WDGeoFeature Feat;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (FEATUREMODE_Add, VT_I4);
HRESULT hr = ((DGeoClass *)ebGetObject (lpArgs, 1)) -> GetObjectFeature (v1, v2, Feat.ppi());

	if (NULL != lpArgs[0]) {
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Feat.detach());
		else
			ebSetObject (lpArgs, 0, NULL);
	}
}


// ----------------------------------------------------------------------------
// function_GeoClass_ReplaceObjectFeature
// ----------------------------------------------------------------------------
void function_GeoClass_ReplaceObjectFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoClass_ReplaceObjectFeature);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

WDGeoFeature Feat;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (FEATUREMODE_Replace, VT_I4);
HRESULT hr = ((DGeoClass *)ebGetObject (lpArgs, 1)) -> GetObjectFeature (v1, v2, Feat.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Feat.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// command_GeoClass_RemoveObjectFeature
// ----------------------------------------------------------------------------
void command_GeoClass_RemoveObjectFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_GeoClass_RemoveObjectFeature);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

WDGeoFeature Dummy;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (FEATUREMODE_Remove, VT_I4);

	((DGeoClass *)ebGetObject (lpArgs, 1)) -> GetObjectFeature (v1, v2, Dummy.ppi());
}


// ----------------------------------------------------------------------------
// function_GeoClass_GetObjectsInWindow
// ----------------------------------------------------------------------------
void function_GeoClass_GetObjectsInWindow (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoClass_GetObjectsInWindow);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

WDGeoObjects Objs;
CComVariant vXMax (iNumArgs > 3 ? ebGetDouble (lpArgs, 4) : ebGetDouble (lpArgs, 2));
CComVariant vYMax (iNumArgs > 4 ? ebGetDouble (lpArgs, 5) : ebGetDouble (lpArgs, 3));
HRESULT hr = ((DGeoClass *)ebGetObject (lpArgs, 1)) -> GetObjectsInRect (ebGetDouble (lpArgs, 2), ebGetDouble (lpArgs, 3), vXMax, vYMax, Objs.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propget_GeoClass_Code
// ----------------------------------------------------------------------------
void propget_GeoClass_Code (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoClass_Code);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

ULONG ulIdent = 0;
HRESULT hr = ((_DGeoClass *)ebGetObject (lpArgs, 1)) -> get_Code((LONG *)&ulIdent);

	if (SUCCEEDED(hr)) 
		ebSetLong (lpArgs, 0, ulIdent);
}

// ----------------------------------------------------------------------------
// propget_GeoClass_Connection
// ----------------------------------------------------------------------------
void propget_GeoClass_Connection (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoClass_Connection);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

WTRiASConnection Conn;
HRESULT hr = ((_DGeoClass *)ebGetObject (lpArgs, 1)) -> get_Connection (Conn.ppi());

	ebSetLong (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) {
	CComBSTR bstrName;

		if (SUCCEEDED(Conn -> get_Name (&bstrName))) 
			ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrName));
	}
}

// ----------------------------------------------------------------------------
// propget_GeoClass_Updatable
// ----------------------------------------------------------------------------
void propget_GeoClass_Updatable (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoClass_Updatable);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

CComBool fValue;
HRESULT hr = ((_DGeoClass *)ebGetObject (lpArgs, 1)) -> get_Updatable(&fValue);

	if (SUCCEEDED(hr))
		ebSetBool (lpArgs, 0, fValue ? ebTRUE : ebFALSE);
	else
		ebSetBool (lpArgs, 0, ebFALSE);
}

// ----------------------------------------------------------------------------
// propget_GeoClass_IsQueryDef
// ----------------------------------------------------------------------------
void propget_GeoClass_IsQueryDef (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoClass_IsQueryDef);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

CComBool fValue;
HRESULT hr = ((_DGeoClass *)ebGetObject (lpArgs, 1)) -> get_IsQueryDef(&fValue);

	if (SUCCEEDED(hr))
		ebSetBool (lpArgs, 0, fValue ? ebTRUE : ebFALSE);
	else
		ebSetBool (lpArgs, 0, ebFALSE);
}

// ----------------------------------------------------------------------------
// propset_GeoClass_Updatable
// ----------------------------------------------------------------------------
void propset_GeoClass_Updatable (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_GeoClass_Updatable);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

CComBool fValue (ebGetBool (lpArgs, 2));		// 1st argument

	((_DGeoClass *)ebGetObject (lpArgs, 1)) -> put_Updatable (fValue);
}

// ----------------------------------------------------------------------------
// propget_GeoObject_Value
// ----------------------------------------------------------------------------
void propget_GeoObject_Value (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObject_Value);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

LONG lONr = INVALID_ONR;

	((_DGeoObject *)ebGetObject (lpArgs, 1)) -> get_Value (&lONr);
	ebSetLong (lpArgs, 0, lONr);
}

// ----------------------------------------------------------------------------
// propget_GeoObject_Name
// ----------------------------------------------------------------------------
void propget_GeoObject_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObject_Name);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

CComBSTR bstrName;
HRESULT hr = ((_DGeoObject *)ebGetObject (lpArgs, 1)) -> get_Name(CLEARED(&bstrName));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (bstrName)
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrName));
	else
		ebSetString (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// propset_GeoObject_Name
// ----------------------------------------------------------------------------
void propset_GeoObject_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_GeoObject_Name);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;
		
_DGeoObject *pIGeoObject = (_DGeoObject *)ebGetObject (lpArgs, 1);
ebHSUB hStr = ebGetString (lpArgs, 2);		// 1st argument
CComBSTR bstrName = SysAllocString (WideString(ebLockString (hThread, hStr)));
	
	pIGeoObject -> put_Name (bstrName);
	ebUnlockString (hThread, hStr);
}


// ----------------------------------------------------------------------------
// propget_GeoObject_ObjType
// ----------------------------------------------------------------------------
void propget_GeoObject_ObjType (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObject_ObjType);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

OBJECTTYPE rgOTyp = OBJECTTYPE_Unknown;

	((_DGeoObject *)ebGetObject (lpArgs, 1)) -> get_ObjType (&rgOTyp);
	ebSetInt (lpArgs, 0, (int)rgOTyp);
}

// ----------------------------------------------------------------------------
// propget_GeoObject_ObjClass
// ----------------------------------------------------------------------------
void propget_GeoObject_ObjClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObject_ObjClass);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;
		
WDGeoClass Cls;
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> get_ObjClass (Cls.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Cls.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_GeoObject_ObjDistance
// ----------------------------------------------------------------------------
void function_GeoObject_ObjDistance (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_ObjDistance);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;
		
DGeoObject *pIGeoObject = (DGeoObject *)ebGetObject (lpArgs, 1);
CComVariant vMode (iNumArgs > 2 ? ebGetInt (lpArgs, 3) : 0, VT_I4);
CComVariant vMinMax (iNumArgs > 3 ? ebGetInt (lpArgs, 4) : 0, VT_I4);

double dDist = -1.0;
HRESULT hr = pIGeoObject -> ObjDistance ((DGeoObject *)ebGetObject (lpArgs, 2), vMode, vMinMax, &dDist);

	if (FAILED(hr))
		dDist = -1.0;
	ebSetDouble (lpArgs, 0, dDist);
}

// ----------------------------------------------------------------------------
// function_GeoObject_ClassDistance
// ----------------------------------------------------------------------------
void function_GeoObject_ClassDistance (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_ClassDistance);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;
		
DGeoObject *pIGeoObject = (DGeoObject *)ebGetObject (lpArgs, 1);
CComVariant vObj;
CComVariant vMode (iNumArgs > 3 ? ebGetInt (lpArgs, 4) : 0, VT_I4);
CComVariant vMinMax (iNumArgs > 4 ? ebGetInt (lpArgs, 5) : 0, VT_I4);

double dDist = -1.0;	
HRESULT hr = pIGeoObject -> ClassDistance ((DGeoClass *)ebGetObject(lpArgs, 2), &vObj, vMode, vMinMax, &dDist);

	if (FAILED(hr)) dDist = -1.0;

	if (iNumArgs > 2) {
	DTRiASBaseClass *pObj = (DTRiASBaseClass *)ebGetObject (lpArgs, 3);
	
		if (pObj != NULL && (DWORD)pObj != 1L) 
			pObj -> Release();
		ebSetObject (lpArgs, 3, NULL);
		
		hr = vObj.ChangeType (VT_DISPATCH);
		if (SUCCEEDED(hr) && NULL != V_DISPATCH(&vObj)) {
		WDGeoObject Obj;
		
			hr = V_DISPATCH(&vObj) -> QueryInterface (IID_DGeoObject, Obj.ppv());
			if (SUCCEEDED(hr)) 
				ebSetObject (lpArgs, 3, (DWORD)Obj.detach());
		}
	}
	ebSetDouble (lpArgs, 0, dDist);
}

// ----------------------------------------------------------------------------
// function_GeoObject_GetGeometry1
// ----------------------------------------------------------------------------
void function_GeoObject_GetGeometry1 (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_GetGeometry1);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;
		
_DGeoObject *pIGeoObject = (_DGeoObject *)ebGetObject (lpArgs, 1);
double dblX, dblY;
OBJECTTYPE iOTyp = OBJECTTYPE_Unknown;
HRESULT hr = pIGeoObject -> GetGeometryPt (&dblX, &dblY, &iOTyp);

	if (SUCCEEDED(hr)) {
		ebSetDouble (lpArgs, 2, dblX);
		ebSetDouble (lpArgs, 3, dblY);
	}

	if (NULL != lpArgs[0]) {
		if (SUCCEEDED(hr)) 
			ebSetInt (lpArgs, 0, iOTyp);	// liefert ObjektTyp
		else
			ebSetInt (lpArgs, 0, OBJECTTYPE_Unknown);
	}
}

// ----------------------------------------------------------------------------
// function_GeoObject_GetGeometry2
// ----------------------------------------------------------------------------
DeclareSafeLock(double);	// SAFEARRAY-Zugriff
DeclareSafeLock(long);

DeclareEbLock(double);		// ebARRAY-Zugriff
DeclareEbLock(long);

#pragma function (memcpy)

static bool CopyEbGeometry (ebHTHREAD hThread, long lCnt, ebHSUB hArr, VARIANT &v)
{
	if (V_VT(&v) != (VT_ARRAY|VT_R8) || hArr == NULL) 
		return false;
	
// BasicFeld entsprechend vergrößern
CEbArraydouble eba (hThread, hArr);

	if (!eba.ReDim (lCnt)) 
		return false;
	
// Daten umkopieren
CSafeArray sa (VT_R8);
bool fResult = false;

	sa.Attach (V_ARRAY(&v));
	{
	CLockdouble l (sa);
	CEbLockdouble ebl (eba);
	
		if (!(!l || !ebl)) {
			memcpy ((double *)ebl, l, size_t(sizeof(double)*lCnt));
			fResult = true;
		}
	} // Lock's aufheben
	sa.Detach();
    return fResult;
}

static bool CopyEbContures (ebHTHREAD hThread, short iKCnt, ebHSUB hArr, VARIANT &v)
{
	if (V_VT(&v) != (VT_ARRAY|VT_I4) || hArr == NULL) 
		return false;
	
// BasicFeld entsprechend vergrößern
CEbArraylong eba (hThread, hArr);

	if (!eba.ReDim (iKCnt)) 
		return false;
	
// Daten umkopieren
CSafeArray sa (VT_R8);
bool fResult = false;

	sa.Attach (V_ARRAY(&v));
	{
	CLocklong l (sa);
	CEbLocklong ebl (eba);
	
		if (!(!l || !ebl)) {
			memcpy ((long *)ebl, l, size_t(sizeof(long)*iKCnt));
			fResult = true;
		}
	} // Lock's aufheben
	sa.Detach();
    return fResult;
}

void function_GeoObject_GetGeometry2 (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_GetGeometry2);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;
		
_DGeoObject *pIGeoObject = (_DGeoObject *)ebGetObject (lpArgs, 1);
CComVariant vXArr, vYArr;	// Koordinatenfelder
long lCnt = 0;
OBJECTTYPE rgOType = OBJECTTYPE_Unknown;
HRESULT hr = NOERROR;

	{
	CComVariant vKCnt, vC;
	
		hr = pIGeoObject -> GetGeometry (&lCnt, &vXArr, &vYArr, &vKCnt, &vC, &rgOType);
		if (iNumArgs > 4 && SUCCEEDED(hr) && rgOType != OBJECTTYPE_Unknown) {
			ebSetInt (lpArgs, 5, V_I2(&vKCnt));
			if (iNumArgs > 5)
				CopyEbContures (hThread, V_I2(&vKCnt), ebGetArray (lpArgs, 6), vC);
		}
	}	// Variants aufräumen

	if (SUCCEEDED(hr) && rgOType != OBJECTTYPE_Unknown) {
		ebSetLong (lpArgs, 2, lCnt);
		if (iNumArgs > 2)
			CopyEbGeometry (hThread, lCnt, ebGetArray (lpArgs, 3), vXArr);
		if (iNumArgs > 3)
			CopyEbGeometry (hThread, lCnt, ebGetArray (lpArgs, 4), vYArr);
	}
	if (lpArgs[0])	// nur wenn als Function gerufen wurde
		ebSetInt (lpArgs, 0, rgOType);	// liefert ObjektTyp
}

// ----------------------------------------------------------------------------
// function_GeoObject_GetGeometryRect
// ----------------------------------------------------------------------------
void function_GeoObject_GetGeometryRect (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_GetGeometryRect);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;
		
_DGeoObject *pIGeoObject = (_DGeoObject *)ebGetObject (lpArgs, 1);
double dXMin = 0.0;
double dXMax = 0.0;
double dYMin = 0.0;
double dYMax = 0.0;
OBJECTTYPE rgOTyp = OBJECTTYPE_Unknown;

	pIGeoObject -> GetGeometryRect (&dXMin, &dYMin, &dXMax, &dYMax, &rgOTyp);

// Resultate setzen
	if (lpArgs[0])	// nur wenn als Function gerufen wurde
		ebSetInt (lpArgs, 0, (int)rgOTyp);
	ebSetDouble (lpArgs, 2, dXMin);
	ebSetDouble (lpArgs, 3, dYMin);
	ebSetDouble (lpArgs, 4, dXMax);
	ebSetDouble (lpArgs, 5, dYMax);
}

// ----------------------------------------------------------------------------
// function_GeoObject_PutGeometry1
// ----------------------------------------------------------------------------
void function_GeoObject_PutGeometry1 (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_PutGeometry1);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;
		
_DGeoObject *pIGeoObject = (_DGeoObject *)ebGetObject (lpArgs, 1);
CComVariant vMode; 

	V_VT(&vMode) = VT_I4;
	V_I4(&vMode) = iNumArgs > 4 ? ebGetLong (lpArgs, 5) : MODGEOMETRY_ModObject;
	
VARIANT_BOOL fResult = 0;
HRESULT hr = pIGeoObject -> PutGeometryPt (
				(OBJECTTYPE)ebGetInt (lpArgs, 2), ebGetDouble (lpArgs, 3), 
				ebGetDouble (lpArgs, 4), vMode, &fResult);

	if (FAILED(hr)) fResult = 0;
	if (NULL != lpArgs[0])
		ebSetInt (lpArgs, 0, fResult);	// liefert true/false
}


// ----------------------------------------------------------------------------
// function_GeoObject_PutGeometry2
// ----------------------------------------------------------------------------
static bool CopyGeometry (ebHTHREAD hThread, VARIANT &v, ebHSUB hArr)
{
	if (hArr == NULL) return false;
	
// VARIANT-Feld erzeugen
CEbArraydouble eba (hThread, hArr);
CEbLockdouble ebl (eba);

	if (!ebl) return false;
	
CSafeArray sa (VT_R8, ebl.Size());

// Daten umkopieren
bool fResult = false;

	{
	CLockdouble l (sa);
	
		if (!(!l) && l.Size() == ebl.Size()) {
		// Koordinaten umkopieren
			memcpy (l, (double *)ebl, size_t(sizeof(double)* ebl.Size()));
			fResult = true;

		// Variant setzen
			V_VT(&v) = VT_ARRAY|VT_R8;
			V_ARRAY(&v) = sa.Detach();
		} 
	} // Lock aufheben

return fResult;
}

static bool CopyContures (ebHTHREAD hThread, VARIANT &v, ebHSUB hArr)
{
	if (hArr == NULL) return false;
	
// VARIANT-Feld erzeugen
CEbArraylong eba (hThread, hArr);
CEbLocklong ebl (eba);

	if (!ebl) return false;
	
CSafeArray sa (VT_I4, ebl.Size());

// Daten umkopieren
bool fResult = false;

	{
	CLocklong l (sa);
	
		if (!(!l) && l.Size() == ebl.Size()) {
		// Koordinaten umkopieren
			memcpy (l, (long *)ebl, size_t(sizeof(long)* ebl.Size()));
			fResult = true;

		// Variant setzen
			V_VT(&v) = VT_ARRAY|VT_I4;
			V_ARRAY(&v) = sa.Detach();
		} 
	} // Lock aufheben

return fResult;
}

void function_GeoObject_PutGeometry2 (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_PutGeometry2);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;
		
_DGeoObject *pIGeoObject = (_DGeoObject *)ebGetObject (lpArgs, 1);
CComVariant vXArr, vYArr, vC, vMode;
VARIANT_BOOL fResult = false;

// Initialisierungen
	if (NULL != lpArgs[0])
		ebSetInt (lpArgs, 0, false);	// liefert true/false

// Parameter erzeugen
OBJECTTYPE rgOTyp = (OBJECTTYPE)ebGetInt (lpArgs, 2);	// gewünschter ObjektTyp

	if (!CopyGeometry (hThread, vXArr, ebGetArray (lpArgs, 3)) ||
	    !CopyGeometry (hThread, vYArr, ebGetArray (lpArgs, 4))) 
	{
		return;
	}
		
	V_VT(&vMode) = VT_I4;
	V_I4(&vMode) = iNumArgs > 4 ? ebGetLong (lpArgs, 5) : MODGEOMETRY_ModObject;	// gewünschte Operation
	
	if (iNumArgs > 5) {			// KonturFeld
		if (CopyContures (hThread, vC, ebGetArray (lpArgs, 6)))
			fResult = true;
	} else
		fResult = true;

	if (fResult) {
	HRESULT hr = pIGeoObject -> PutGeometry (rgOTyp, vXArr, vYArr, vC, vMode, &fResult);

		if (FAILED(hr))
			fResult = false;
	}
		
	if (NULL != lpArgs[0])
		ebSetInt (lpArgs, 0, fResult);	// liefert true/false
}

// ----------------------------------------------------------------------------
// function_GeoObject_PutGeometry3
// ----------------------------------------------------------------------------

// 'richtiges' PutGeometry (Parameter entsprechen jetzt Automation-Schnittstelle)
void function_GeoObject_PutGeometry3 (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_PutGeometry3);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;
		
_DGeoObject *pIGeoObject = (_DGeoObject *)ebGetObject (lpArgs, 1);
CComVariant vXArr, vYArr, vC, vMode;
VARIANT_BOOL fResult = false;

// Initialisierungen
	if (NULL != lpArgs[0])
		ebSetInt (lpArgs, 0, false);	// liefert true/false

// Parameter erzeugen
OBJECTTYPE rgOTyp = (OBJECTTYPE)ebGetInt (lpArgs, 2);	// gewünschter ObjektTyp

	if (!CopyGeometry (hThread, vXArr, ebGetArray (lpArgs, 3)) ||
	    !CopyGeometry (hThread, vYArr, ebGetArray (lpArgs, 4))) 
	{
		return;
	}
		
	if (CopyContures (hThread, vC, ebGetArray (lpArgs, 5)))
		fResult = true;

	V_VT(&vMode) = VT_I4;
	V_I4(&vMode) = iNumArgs > 5 ? ebGetLong (lpArgs, 6) : MODGEOMETRY_ModObject;	// gewünschte Operation
	
	if (fResult) {
	HRESULT hr = pIGeoObject -> PutGeometry (rgOTyp, vXArr, vYArr, vC, vMode, &fResult);

		if (FAILED(hr))
			fResult = false;
	}
	if (NULL != lpArgs[0])
		ebSetInt (lpArgs, 0, fResult);	// liefert true/false
}

// ----------------------------------------------------------------------------
// function_GeoObject_GetText
// ----------------------------------------------------------------------------
void function_GeoObject_GetText (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_GetText);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	ebSetString (lpArgs, 0, NULL);
	
CComBSTR bstrText;
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> GetText(CLEARED(&bstrText));

	if (SUCCEEDED(hr)) 
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrText));
}

// ----------------------------------------------------------------------------
// function_GeoObject_PutText
// ----------------------------------------------------------------------------
void function_GeoObject_PutText (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_PutText);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

ebHSUB hStr = ebGetString (lpArgs, 2);
CComBSTR bstrText (ebLockString (hThread, hStr));

	ebUnlockString (hThread, hStr);	

HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> PutText (bstrText);

	if (NULL != lpArgs[0]) 		// nur, wenn nicht method
		ebSetBool (lpArgs, 0, SUCCEEDED(hr) ? ebTRUE : ebFALSE);
}

// ----------------------------------------------------------------------------
// function_GeoObject_GetFeatures
// ----------------------------------------------------------------------------
void function_GeoObject_GetFeatures (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_GetFeatures);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

WDGeoFeatures Feats;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> GetFeatures (v1, v2, Feats.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Feats.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}



// ----------------------------------------------------------------------------
// function_GeoObject_GetFeature
// ----------------------------------------------------------------------------
void function_GeoObject_GetFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_GetFeature);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant v3 (MakeVARIANT (hThread, iNumArgs, lpArgs, 4));

WDGeoFeature Feat;
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> GetFeature (v1, v2, v3, Feat.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Feat.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_GeoObject_AddFeature
// ----------------------------------------------------------------------------
void function_GeoObject_AddFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_AddFeature);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant v3 (MakeVARIANT (hThread, iNumArgs, lpArgs, 4));

WDGeoFeature Feat;
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> AddFeature (v1, v2, v3, Feat.ppi());

	if (NULL != lpArgs[0]) {
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Feat.detach());
		else
			ebSetObject (lpArgs, 0, NULL);
	}
}

// ----------------------------------------------------------------------------
// function_GeoObject_ReplaceFeature
// ----------------------------------------------------------------------------
void function_GeoObject_ReplaceFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_ReplaceFeature);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (FEATUREMODE_Replace, VT_I4);
CComVariant v3; 

WDGeoFeature Feat;
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> GetFeature (v1, v2, v3, Feat.ppi());

	if (NULL != lpArgs[0]) {
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Feat.detach());
		else
			ebSetObject (lpArgs, 0, NULL);
	}
}

// ----------------------------------------------------------------------------
// command_GeoObject_RemoveFeature
// ----------------------------------------------------------------------------
void command_GeoObject_RemoveFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_GeoObject_RemoveFeature);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));	

	((DGeoObject *)ebGetObject (lpArgs, 1)) -> RemoveFeature (v1);
}

// ----------------------------------------------------------------------------
// command_GeoObject_RePaint
// ----------------------------------------------------------------------------
void command_GeoObject_RePaint (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_GeoObject_RePaint);

CComVariant vFlag;

	V_VT(&vFlag) = VT_BOOL;
	V_BOOL(&vFlag) = iNumArgs > 1 ? (ebGetInt (lpArgs, 2) ? -1 : 0) : 0;

	((_DGeoObject *)ebGetObject (lpArgs, 1)) -> RePaint (vFlag);
}

// ----------------------------------------------------------------------------
// function_GeoObject_TopRelation
// ----------------------------------------------------------------------------
void function_GeoObject_TopRelation (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_TopRelation);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;
		
TOPRELATION rgRTyp = TOPRELATION_Unknown;

	((DGeoObject *)ebGetObject (lpArgs, 1)) -> TopRelation ((DGeoObject *)ebGetLong(lpArgs, 2), &rgRTyp);
	ebSetInt (lpArgs, 0, (int)rgRTyp);		// liefert Topologische Relation
}

// ----------------------------------------------------------------------------
// function_GeoObject_GetTopRelationObjects
// ----------------------------------------------------------------------------
void function_GeoObject_GetTopRelationObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_GetTopRelationObjects);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

TOPRELATION rgRTyp = (TOPRELATION)ebGetInt (lpArgs, 2);
WDGeoObjects Objs;
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> GetTopRelationObjects (rgRTyp, Objs.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// function_GeoObject_GetBufferObjects
// ----------------------------------------------------------------------------
void function_GeoObject_GetBufferObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_GetBufferObjects);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant v3 (MakeVARIANT (hThread, iNumArgs, lpArgs, 4));
CComVariant v4 (MakeVARIANT (hThread, iNumArgs, lpArgs, 5));

WDGeoObjects Objs;
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> GetBufferObjects (ebGetDouble (lpArgs, 2), v2, v3, v4, Objs.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// function_GeoObject_GetBufferObjectsEx
// ----------------------------------------------------------------------------
void function_GeoObject_GetBufferObjectsEx (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_GetBufferObjects);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant v3 (MakeVARIANT (hThread, iNumArgs, lpArgs, 4));
CComVariant v4 (MakeVARIANT (hThread, iNumArgs, lpArgs, 5));
CComVariant v5 (MakeVARIANT (hThread, iNumArgs, lpArgs, 6));

WDGeoObject Obj;
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> GetBufferObjectEx (ebGetDouble (lpArgs, 2), v2, v3, v4, v5, Obj.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Obj.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// function_GeoObject_GetCircleBufferObjects
// ----------------------------------------------------------------------------
void function_GeoObject_GetCircleBufferObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_GetCircleBufferObjects);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant v3 (MakeVARIANT (hThread, iNumArgs, lpArgs, 4));
CComVariant v4 (MakeVARIANT (hThread, iNumArgs, lpArgs, 5));

WDGeoObjects Objs;
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> GetCircleBufferObjects (ebGetDouble (lpArgs, 2), v2, v3, v4, Objs.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_GeoObject_GetIntersectObjects
// ----------------------------------------------------------------------------
void function_GeoObject_GetIntersectObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_GetIntersectObjects);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));

WDGeoObjects Objs;
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> GetIntersectObjects ((DGeoObject *)ebGetObject (lpArgs, 2), v2, Objs.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_GeoObject_GetIntersectObjectsColl
// ----------------------------------------------------------------------------
void function_GeoObject_GetIntersectObjectsColl (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_GetIntersectObjectsColl);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));

WDGeoObjects Objs;
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> GetIntersectObjectsCollection ((DGeoObjects *)ebGetObject (lpArgs, 2), v2, Objs.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_GeoObject_GetIntersectObjectsClass
// ----------------------------------------------------------------------------
void function_GeoObject_GetIntersectObjectsClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_GetIntersectObjectsClass);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

CComVariant vMode (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));

WDGeoObjects Objs;
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> GetIntersectObjectsClass ((DGeoClass *)ebGetObject (lpArgs, 2), vMode, Objs.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// function_GeoObject_GeometryAND
// ----------------------------------------------------------------------------
void function_GeoObject_GeometryAND (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_GeometryAND);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));

WDGeoObjects Objs;
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> GeometryIntersection ((DGeoObject *)ebGetObject(lpArgs, 2), v1, Objs.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// function_GeoObject_GeometryOR
// ----------------------------------------------------------------------------
void function_GeoObject_GeometryOR (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_GeometryOR);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));

WDGeoObjects Objs;
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> GeometryUnion ((DGeoObject *)ebGetObject (lpArgs, 2), v1, Objs.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// GetCommonContourObjects_GeoObject_function
// ----------------------------------------------------------------------------
void GetCommonContourObjects_GeoObject_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(GetCommonContourObjects_GeoObject_function);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

WDGeoObjects Objs;
CComVariant vIdent (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant vMode (MakeVARIANT (hThread, iNumArgs, lpArgs, 4));
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> GetCommonContourObjects ((DGeoObjects *)ebGetObject (lpArgs, 2), vIdent, vMode, Objs.ppi());

	if (SUCCEEDED(hr))
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);		// some error
}

// ----------------------------------------------------------------------------
// propget_GeoObject_Feature
// ----------------------------------------------------------------------------
void propget_GeoObject_Feature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObject_Feature);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

ebHSUB hStr = ebGetString (lpArgs, 2);			// Name der Objekteigenschaft
CComBSTR bstr (ebLockString (hThread, hStr));
CComVariant vValue;
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> get_Feature (bstr, &vValue);

	if (SUCCEEDED(hr)) {
	ebVARIANT v = MakeebVARIANT (hThread, vValue);	// Wert

		ebSetVariant (lpArgs, 0, &v);
		ebFreeVariant (hThread, &v);
	}
	ebUnlockString (hThread, hStr);
}

// ----------------------------------------------------------------------------
// propset_GeoObject_Feature
// ----------------------------------------------------------------------------
void propset_GeoObject_Feature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_GeoObject_Feature);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

ebHSUB hStr = ebGetString (lpArgs, 2);			// Name der Objekteigenschaft
CComBSTR bstr (ebLockString (hThread, hStr));
CComVariant vValue (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));	// Wert
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> put_Feature (bstr, vValue);

	ebUnlockString (hThread, hStr);
}

// ----------------------------------------------------------------------------
// propget_GeoObject_Selected
// ----------------------------------------------------------------------------
void propget_GeoObject_Selected (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObject_Selected);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
VARIANT_BOOL fSelected = false;
HRESULT hr = ((_DGeoObject *)ebGetObject (lpArgs, 1)) -> get_Selected (v1, &fSelected);

	ebSetBool (lpArgs, 0, fSelected ? -1 : 0);
}

// ----------------------------------------------------------------------------
// propset_GeoObject_Selected
// ----------------------------------------------------------------------------
void propset_GeoObject_Selected (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_GeoObject_Selected);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

VARIANT_BOOL fSelected = ebGetBool (lpArgs, 2) ? VARIANT_TRUE : 0;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));

	((_DGeoObject *)ebGetObject (lpArgs, 1)) -> put_Selected (v1, fSelected);
}

// ----------------------------------------------------------------------------
// propget_GeoObject_Activated
// ----------------------------------------------------------------------------
void propget_GeoObject_Activated (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObject_Activated);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
VARIANT_BOOL fActivated = false;
HRESULT hr = ((_DGeoObject *)ebGetObject (lpArgs, 1)) -> get_Activated (v1, &fActivated);

	ebSetBool (lpArgs, 0, fActivated ? -1 : 0);
}

// ----------------------------------------------------------------------------
// propset_GeoObject_Activated
// ----------------------------------------------------------------------------
void propset_GeoObject_Activated (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_GeoObject_Activated);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

VARIANT_BOOL fActivated = ebGetBool (lpArgs, 2) ? VARIANT_TRUE : 0;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));

	((_DGeoObject *)ebGetObject (lpArgs, 1)) -> put_Activated (v1, fActivated);
}

// ----------------------------------------------------------------------------
// cmd_GeoObject_Hilight
// ----------------------------------------------------------------------------
void cmd_GeoObject_Hilight (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(cmd_GeoObject_Hilight);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

TRIASCOLOR crAct = (TRIASCOLOR)ebGetLong (lpArgs, 2);

	((DGeoObject *)ebGetObject (lpArgs, 1)) -> Hilight (crAct);
}

// ----------------------------------------------------------------------------
// cmd_GeoObject_UnHilight
// ----------------------------------------------------------------------------
void cmd_GeoObject_UnHilight (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(cmd_GeoObject_UnHilight);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

	((DGeoObject *)ebGetObject (lpArgs, 1)) -> UnHilight();
}

// ----------------------------------------------------------------------------
// function_GeoObject_MakeRectangular
// ----------------------------------------------------------------------------
void function_GeoObject_MakeRectangular (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_MakeRectangular);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

WDGeoObjects Objs;
CComVariant vRefLine (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant vEps90 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant vEps180 (MakeVARIANT (hThread, iNumArgs, lpArgs, 4));
CComVariant vEpsCom (MakeVARIANT (hThread, iNumArgs, lpArgs, 5));
CComVariant vCommonObjs (MakeVARIANT (hThread, iNumArgs, lpArgs, 6));

HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> MakeRectangular (
					vRefLine, vEps90, vEps180, vEpsCom, vCommonObjs, Objs.ppi());

	if (NULL != lpArgs[0]) {	// nur, wenn Funktion
		if (SUCCEEDED(hr))
			ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
		else
			ebSetObject (lpArgs, 0, NULL);		// some error
	}
}

// ----------------------------------------------------------------------------
// function_GeoObject_ShiftGeometrySection
// ----------------------------------------------------------------------------
void function_GeoObject_ShiftGeometrySection (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_ShiftGeometrySection);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

WDGeoObject Obj;
CComVariant vTargetBeginX (MakeVARIANT (hThread, iNumArgs, lpArgs, 4));
CComVariant vTargetBeginY (MakeVARIANT (hThread, iNumArgs, lpArgs, 5));
CComVariant vTargetEndX (MakeVARIANT (hThread, iNumArgs, lpArgs, 6));
CComVariant vTargetEndY (MakeVARIANT (hThread, iNumArgs, lpArgs, 7));
CComVariant vMoveDir (MakeVARIANT (hThread, iNumArgs, lpArgs, 8));
CComVariant vContinueBegin (MakeVARIANT (hThread, iNumArgs, lpArgs, 9));
CComVariant vContinueEnd (MakeVARIANT (hThread, iNumArgs, lpArgs, 10));
CComVariant vEps (MakeVARIANT (hThread, iNumArgs, lpArgs, 11));
CComVariant vXMin (MakeVARIANT (hThread, iNumArgs, lpArgs, 12));
CComVariant vYMin (MakeVARIANT (hThread, iNumArgs, lpArgs, 13));
CComVariant vXMax (MakeVARIANT (hThread, iNumArgs, lpArgs, 14));
CComVariant vYMax (MakeVARIANT (hThread, iNumArgs, lpArgs, 15));

HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> ShiftGeometrySegment (
							ebGetDouble (lpArgs, 2), ebGetDouble (lpArgs, 3),
							vTargetBeginX, vTargetBeginY, vTargetEndX, vTargetEndY, 
							vMoveDir, vContinueBegin, vContinueEnd, vEps,
							vXMin, vYMin, vXMax, vYMax, Obj.ppi());

	if (SUCCEEDED(hr))
		ebSetObject (lpArgs, 0, (DWORD)Obj.detach());
	else
		ebSetObject (lpArgs, 0, NULL);		// some error
}

// ----------------------------------------------------------------------------
// propget_GeoObject_Guid
// ----------------------------------------------------------------------------
void propget_GeoObject_Guid (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObject_Guid);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

CComBSTR bstrName;
HRESULT hr = ((_DGeoObject *)ebGetObject (lpArgs, 1)) -> get_Guid(CLEARED(&bstrName));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (bstrName)
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrName));
	else
		ebSetString (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propset_GeoObject_Guid
// ----------------------------------------------------------------------------
void propset_GeoObject_Guid (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_GeoObject_Guid);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

_DGeoObject *pIGeoObject = (_DGeoObject *)ebGetObject (lpArgs, 1);
ebHSUB hStr = ebGetString (lpArgs, 2);		// 1st argument
CComBSTR bstrName (ebLockString (hThread, hStr));
	
	pIGeoObject -> put_Guid (bstrName);
	ebUnlockString (hThread, hStr);
}

// ----------------------------------------------------------------------------
// propget_GeoObject_UniqueID
// ----------------------------------------------------------------------------
void propget_GeoObject_UniqueID (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObject_UniqueID);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

CComBSTR bstrName;
HRESULT hr = ((_DGeoObject *)ebGetObject (lpArgs, 1)) -> get_UniqueID(CLEARED(&bstrName));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (bstrName)
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrName));
	else
		ebSetString (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propset_GeoObject_UniqueID
// ----------------------------------------------------------------------------
void propset_GeoObject_UniqueID (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_GeoObject_UniqueID);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

_DGeoObject *pIGeoObject = (_DGeoObject *)ebGetObject (lpArgs, 1);
ebHSUB hStr = ebGetString (lpArgs, 2);		// 1st argument
CComBSTR bstrName (ebLockString (hThread, hStr));
	
	pIGeoObject -> put_UniqueID (bstrName);
	ebUnlockString (hThread, hStr);
}

// ----------------------------------------------------------------------------
// propget_GeoObject_OldUniqueID
// ----------------------------------------------------------------------------
void propget_GeoObject_OldUniqueID (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObject_OldUniqueID);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

CComBSTR bstrName;
HRESULT hr = ((_DGeoObject *)ebGetObject (lpArgs, 1)) -> get_OldUniqueID(CLEARED(&bstrName));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (bstrName)
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrName));
	else
		ebSetString (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propset_GeoObject_OldUniqueID
// ----------------------------------------------------------------------------
void propset_GeoObject_OldUniqueID (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_GeoObject_OldUniqueID);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

_DGeoObject *pIGeoObject = (_DGeoObject *)ebGetObject (lpArgs, 1);
ebHSUB hStr = ebGetString (lpArgs, 2);		// 1st argument
CComBSTR bstrName (ebLockString (hThread, hStr));
	
	pIGeoObject -> put_OldUniqueID (bstrName);
	ebUnlockString (hThread, hStr);
}

// ----------------------------------------------------------------------------
// function_GeoObject_GetRelatedObject
// ----------------------------------------------------------------------------
void function_GeoObject_GetRelatedObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_GetRelatedObject);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

WDGeoObject Obj;
HRESULT hr = ((_DGeoObject *)ebGetObject (lpArgs, 1)) -> GetRelatedObject(Obj.ppi());

	if (SUCCEEDED(hr))
		ebSetObject (lpArgs, 0, (DWORD)Obj.detach());
	else
		ebSetObject (lpArgs, 0, NULL);		// some error
}

// ----------------------------------------------------------------------------
// cmd_GeoObject_CreateRelatedObject
// ----------------------------------------------------------------------------
void cmd_GeoObject_CreateRelatedObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_CreateRelatedObject);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

_DGeoObject *pIGeoObject = (_DGeoObject *)ebGetObject (lpArgs, 2);
HRESULT hr = ((_DGeoObject *)ebGetObject (lpArgs, 1)) -> CreateObjectRelation(pIGeoObject);

	if (NULL != lpArgs[0]) {	// nur, wenn Funktion
		if (SUCCEEDED(hr))
			ebSetBool (lpArgs, 0, ebTRUE);
		else
			ebSetBool (lpArgs, 0, ebFALSE);		// some error
	}
}

// ----------------------------------------------------------------------------
// function_GeoObject_RemoveRelatedObject
// ----------------------------------------------------------------------------
void function_GeoObject_RemoveRelatedObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_RemoveRelatedObject);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;
	
WDGeoObject Obj;
HRESULT hr = ((_DGeoObject *)ebGetObject (lpArgs, 1)) -> RemoveObjectRelation(Obj.ppi());

	if (NULL != lpArgs[0]) {	// nur, wenn Funktion
		if (SUCCEEDED(hr))
			ebSetObject (lpArgs, 0, (DWORD)Obj.detach());
		else
			ebSetObject (lpArgs, 0, NULL);		// some error
	}
}

// ----------------------------------------------------------------------------
// function_GeoObject_AnalyzeGeometry
// ----------------------------------------------------------------------------
void function_GeoObject_AnalyzeGeometry (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_AnalyzeGeometry);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

VARIANT_BOOL fSuccess = VARIANT_FALSE;
HRESULT hr = ((_DGeoObject *)ebGetObject (lpArgs, 1)) -> AnalyzeGeometry(&fSuccess);

	ebSetBool (lpArgs, 0, fSuccess ? ebTRUE : ebFALSE);
}

// ----------------------------------------------------------------------------
// function_GeoObject_AnalyzeGeometryObject
// ----------------------------------------------------------------------------
void function_GeoObject_AnalyzeGeometryObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_AnalyzeGeometryObject);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;
	
VARIANT_BOOL fSuccess = VARIANT_FALSE;
_DGeoObject *pIGeoObject = (_DGeoObject *)ebGetObject (lpArgs, 2);
CComVariant vMode (MakeVARIANT(hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((_DGeoObject *)ebGetObject (lpArgs, 1)) -> AnalyzeGeometryObject(pIGeoObject, vMode, &fSuccess);

	ebSetBool (lpArgs, 0, fSuccess ? ebTRUE : ebFALSE);
}

// ----------------------------------------------------------------------------
// propget_GeoObject_Visible
// ----------------------------------------------------------------------------
void propget_GeoObject_Visible (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObject_Visible);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

ebHSUB hStr = NULL;
CComVariant vView (DISP_E_PARAMNOTFOUND, VT_ERROR);

	if (iNumArgs > 1) {		// wenn Ansichtsname gegeben ist
		hStr = ebGetString (lpArgs, 2);			// Name der Ansicht
		vView = CComVariant(ebLockString (hThread, hStr));
	}

VARIANT_BOOL fValue;
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> get_Visible (vView, &fValue);

	if (SUCCEEDED(hr)) 
		ebSetBool (lpArgs, 0, fValue ? ebTRUE : ebFALSE);

	if (NULL != hStr)
		ebUnlockString (hThread, hStr);
}	

// ----------------------------------------------------------------------------
// propset_GeoObject_Visible
// ----------------------------------------------------------------------------
void propset_GeoObject_Visible (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_GeoObject_Visible);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

VARIANT_BOOL fValue = ebGetBool (lpArgs, 2) ? VARIANT_TRUE : VARIANT_FALSE;
ebHSUB hStr = NULL;
CComVariant vView (DISP_E_PARAMNOTFOUND, VT_ERROR);

	if (iNumArgs > 2) {		// wenn Ansichtsname gegeben ist
		hStr = ebGetString (lpArgs, 3);			// Name der Ansicht
		vView = CComVariant(ebLockString (hThread, hStr));
	}

	((DGeoObject *)ebGetObject (lpArgs, 1)) -> put_Visible (vView, fValue);
	if (NULL != hStr)
		ebUnlockString (hThread, hStr);
}	

// ----------------------------------------------------------------------------
// propget_GeoObject_Connection
// ----------------------------------------------------------------------------
void propget_GeoObject_Connection (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObject_Connection);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

WTRiASConnection Conn;
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> get_Connection (Conn.ppi());

	ebSetLong (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) {
	CComBSTR bstrName;

		if (SUCCEEDED(Conn -> get_Name (&bstrName))) 
			ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrName));
	}
}

// ----------------------------------------------------------------------------
// function_GeoObject_CloneObject
// ----------------------------------------------------------------------------
void function_GeoObject_CloneObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObject_CloneObject);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;

WDGeoObject NewObj;
CComVariant vCls (MakeVARIANT(hThread, iNumArgs, lpArgs, 2));
HRESULT hr = ((_DGeoObject *)ebGetObject (lpArgs, 1)) -> CloneObject (vCls, NewObj.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)NewObj.detach());
}

// ----------------------------------------------------------------------------
// propget_GeoFeature_Value
// ----------------------------------------------------------------------------
void propget_GeoFeature_Value (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoFeature_Value);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoFeature))
		return;

CComBSTR bstrValue;		
HRESULT hr = ((_DGeoFeature *)ebGetObject (lpArgs, 1)) -> get_Value(CLEARED(&bstrValue));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr))
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrValue));
	else
		ebSetString (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propget_GeoFeature_Name
// ----------------------------------------------------------------------------
void propget_GeoFeature_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoFeature_Name);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoFeature))
		return;

CComBSTR bstrValue;
HRESULT hr = ((_DGeoFeature *)ebGetObject (lpArgs, 1)) -> get_Name(CLEARED(&bstrValue));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr)) 
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrValue));
	else
		ebSetString (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// propset_GeoFeature_Name
// ----------------------------------------------------------------------------

void propset_GeoFeature_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_GeoFeature_Name);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoFeature))
		return;
		
_DGeoFeature *pIGeoFeature = (_DGeoFeature *)ebGetObject (lpArgs, 1);
ebHSUB hStr = ebGetString (lpArgs, 2);		// 1st argument
CComBSTR bstrValue (ebLockString (hThread, hStr));

	if (bstrValue)
		pIGeoFeature -> put_Name (bstrValue);
		
	ebUnlockString (hThread, hStr);
}


// ----------------------------------------------------------------------------
// propget_GeoFeature_FullName
// ----------------------------------------------------------------------------

void propget_GeoFeature_FullName (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoFeature_FullName);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoFeature))
		return;

CComBSTR bstrValue;
HRESULT hr = ((_DGeoFeature *)ebGetObject (lpArgs, 1)) -> get_FullName(CLEARED(&bstrValue));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr))
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrValue));
	else
		ebSetString (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// propset_GeoFeature_FullName
// ----------------------------------------------------------------------------

void propset_GeoFeature_FullName (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_GeoFeature_FullName);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoFeature))
		return;
		
_DGeoFeature *pIGeoFeature = (_DGeoFeature *)ebGetObject (lpArgs, 1);
ebHSUB hStr = ebGetString (lpArgs, 2);		// 1st argument
CComBSTR bstrValue (ebLockString (hThread, hStr));
	
	pIGeoFeature -> put_FullName (bstrValue);
	ebUnlockString (hThread, hStr);
}


// ----------------------------------------------------------------------------
// propget_GeoFeature_Feature
// ----------------------------------------------------------------------------
void propget_GeoFeature_Feature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoFeature_Feature);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoFeature))
		return;

CComBSTR bstrValue;
HRESULT hr = ((_DGeoFeature *)ebGetObject (lpArgs, 1)) -> get_Feature(CLEARED(&bstrValue));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr))
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrValue));
	else
		ebSetString (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propset_GeoFeature_Feature
// ----------------------------------------------------------------------------
void propset_GeoFeature_Feature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_GeoFeature_Feature);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoFeature))
		return;
		
_DGeoFeature *pIGeoFeature = (_DGeoFeature *)ebGetObject (lpArgs, 1);
ebHSUB hStr = ebGetString (lpArgs, 2);		// 1st argument
CComBSTR bstrValue (ebLockString (hThread, hStr));
	
	pIGeoFeature -> put_Feature (bstrValue);
	ebUnlockString (hThread, hStr);
}

// ----------------------------------------------------------------------------
// propget_GeoFeature_Flags
// ----------------------------------------------------------------------------
void propget_GeoFeature_Flags (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoFeature_Flags);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoFeature))
		return;
		
_DGeoFeature *pIGeoFeature = (_DGeoFeature *)ebGetObject (lpArgs, 1);
PROPERTYCAPS dwFlags = PROPERTYCAPS_UNKNOWN;

	if (SUCCEEDED(pIGeoFeature -> get_Flags (&dwFlags)))
		ebSetLong (lpArgs, 0, DWORD(dwFlags));
}

// ----------------------------------------------------------------------------
// propset_GeoFeature_Flags
// ----------------------------------------------------------------------------
void propset_GeoFeature_Flags (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_GeoFeature_Flags);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoFeature))
		return;
		
	((_DGeoFeature *)ebGetObject (lpArgs, 1))->put_Flags ((PROPERTYCAPS)ebGetLong (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// function_GeoFeature_GetViews
// ----------------------------------------------------------------------------
void function_GeoFeature_GetViews (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoFeature_GetViews);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoFeature))
		return;

WDViews Views;
HRESULT hr = ((_DGeoFeature *)ebGetObject (lpArgs, 1)) -> GetViews (Views.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Views.detach());
}

// ----------------------------------------------------------------------------
// function_GeoFeature_GetClasses
// ----------------------------------------------------------------------------
void function_GeoFeature_GetClasses (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoFeature_GetClasses);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoFeature))
		return;

WDGeoClasses Clss;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((DGeoFeature *)ebGetObject (lpArgs, 1)) -> GetClasses (v1, v2, Clss.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Clss.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// function_GeoFeature_GetObjects
// ----------------------------------------------------------------------------
void function_GeoFeature_GetObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoFeature_GetObjects);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoFeature))
		return;

WDGeoObjects Objs;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((DGeoFeature *)ebGetObject (lpArgs, 1)) -> GetObjects (v1, v2, Objs.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propget_GeoFeature_ConfigData
// ----------------------------------------------------------------------------
void propget_GeoFeature_ConfigData (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoFeature_ConfigData);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoFeature))
		return;

DGeoFeature *pIGeoFeature = (DGeoFeature *)ebGetObject (lpArgs, 1);
CComVariant vData;

	if (FAILED(pIGeoFeature -> get_ConfigData (&vData))) {
		V_VT(&vData) = VT_ERROR;
		V_ERROR(&vData) = DISP_E_PARAMNOTFOUND;
	}

ebVARIANT vebData = MakeebVARIANT (hThread, vData);

	ebSetVariant (lpArgs, 0, &vebData);
}

// ----------------------------------------------------------------------------
// propget_GeoObjectWins_ActGeoObjectWin
// ----------------------------------------------------------------------------
void propget_GeoObjectWins_ActGeoObjectWin (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObjectWins_ActGeoObjectWin);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWins))
		return;

WDGeoObjectWin Win;
HRESULT hr = ((DGeoObjectWins *)ebGetObject (lpArgs, 1)) -> get_ActGeoObjectWin (Win.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Win.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propget_GeoObjectWin_Value
// ----------------------------------------------------------------------------
void propget_GeoObjectWin_Value (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObjectWin_Value);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

LONG lhWnd = NULL;

	((DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> get_Value(&lhWnd);
	ebSetLong (lpArgs, 0, lhWnd);
}


// ----------------------------------------------------------------------------
// propget_GeoObjectWin_Name
// ----------------------------------------------------------------------------
void propget_GeoObjectWin_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObjectWin_Name);
 
	// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

CComBSTR bstrValue;
HRESULT hr = ((DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> get_Name(CLEARED(&bstrValue));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(hr)) 
		ebSetString (lpArgs, 0, ebCreateStringX (hThread, bstrValue));
	else
		ebSetString (lpArgs, 0, NULL);		
}


// ----------------------------------------------------------------------------
// propput_GeoObjectWin_Name
// ----------------------------------------------------------------------------
void propput_GeoObjectWin_Name (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propput_GeoObjectWin_Name);
 
	// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

_DGeoObjectWin *pIGeoObjectWin = (_DGeoObjectWin *)ebGetObject (lpArgs, 1);
ebHSUB hStr = ebGetString (lpArgs, 2);		// 1st argument
CComBSTR bstrValue (ebLockString (hThread, hStr));

	if (bstrValue)
		pIGeoObjectWin -> put_Name (bstrValue);
		
	ebUnlockString (hThread, hStr);
}


// ----------------------------------------------------------------------------
// propget_GeoObjectWin_Visible
// ----------------------------------------------------------------------------
void propget_GeoObjectWin_Visible (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObjectWin_Visible);

	// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

VARIANT_BOOL fVisible = false;
HRESULT hr = ((_DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> get_Visible(&fVisible);

	ebSetInt (lpArgs, 0, fVisible);
}


// ----------------------------------------------------------------------------
// propset_GeoObjectWin_Visible
// ----------------------------------------------------------------------------
void propset_GeoObjectWin_Visible (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_GeoObjectWin_Visible);

	// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

	((_DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> put_Visible (ebGetInt (lpArgs, 2));
}



// ----------------------------------------------------------------------------
// propget_GeoObjectWin_ActGeoObject
// ----------------------------------------------------------------------------
void propget_GeoObjectWin_ActGeoObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObjectWin_ActGeoObject);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;
 
WDGeoObject Obj;
HRESULT hr = ((DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> GetActObject (Obj.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Obj.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// propput_GeoObjectWin_ActGeoObject
// ----------------------------------------------------------------------------
void propput_GeoObjectWin_ActGeoObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propput_GeoObjectWin_ActGeoObject);
 
	// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

HRESULT hr = ((DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> SetActObject((DGeoObject *)ebGetObject (lpArgs, 2));

	if (NULL != lpArgs[0]) {	// nur, wenn Funktion
		if (SUCCEEDED(hr)) 
			ebSetBool (lpArgs, 0, -1);
		else
			ebSetBool (lpArgs, 0, 0);
	}
}


// ----------------------------------------------------------------------------
// function_GeoObjectWin_GetClasses
// ----------------------------------------------------------------------------
void function_GeoObjectWin_GetClasses (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObjectWin_GetClasses);
 
	// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

WDGeoClasses Clss;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> GetClasses (v1, v2, Clss.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Clss.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_GeoObjectWin_GetClass
// ----------------------------------------------------------------------------
void function_GeoObjectWin_GetClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObjectWin_GetClass);
 
	// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

WDGeoClass Cls;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> GetClass (v1, v2, Cls.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Cls.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// function_GeoObjectWin_AddClass
// ----------------------------------------------------------------------------
void function_GeoObjectWin_AddClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObjectWin_AddClass);
 
	// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

WDGeoClass Cls;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (GEOCLASSMODE_Add, VT_I4);

HRESULT hr = ((DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> GetClass (v1, v2, Cls.ppi());

	if (NULL != lpArgs[0]) {
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Cls.detach());
		else
			ebSetObject (lpArgs, 0, NULL);
	}	
}

// ----------------------------------------------------------------------------
// command_GeoObjectWin_RemoveClass
// ----------------------------------------------------------------------------
void command_GeoObjectWin_RemoveClass (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_GeoObjectWin_RemoveClass);
 
	// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (GEOCLASSMODE_Remove, VT_I4);

WDGeoClass Dummy;

	((DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> GetClass (v1, v2, Dummy.ppi());
}


// ----------------------------------------------------------------------------
// function_GeoObjectWin_GetObjects
// ----------------------------------------------------------------------------
void function_GeoObjectWin_GetObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObjectWin_GetObjects);
 
	// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

WDGeoObjects Objs;
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> GetObjects (v1, v2, Objs.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// function_GeoObjectWin_GetObject
// ----------------------------------------------------------------------------
void function_GeoObjectWin_GetObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObjectWin_GetObject);
 
	// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));	

	if (FAILED(GetObjectNumber(v1)))
		return;

WDGeoObject Obj;
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
HRESULT hr = ((DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> GetObject (v1, v2, Obj.ppi());

	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Obj.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// function_GeoObjectWin_AddObject
// ----------------------------------------------------------------------------
void function_GeoObjectWin_AddObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObjectWin_AddObject);
 
	// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

CComVariant v2 (GEOOBJECTMODE_Add, VT_I4);
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));

	if (FAILED(GetObjectNumber(v1)))
		return;

WDGeoObject Obj;
HRESULT hr = ((DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> GetObject (v1, v2, Obj.ppi());

	if (NULL != lpArgs[0]) {
		if (SUCCEEDED(hr)) 
			ebSetObject (lpArgs, 0, (DWORD)Obj.detach());
		else
			ebSetObject (lpArgs, 0, NULL);
	}
}

// ----------------------------------------------------------------------------
// command_GeoObjectWin_SetShownFeature
// ----------------------------------------------------------------------------
void command_GeoObjectWin_SetShownFeature (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_GeoObjectWin_SetShownFeature);
 
	// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

ebHSUB hStr = ebGetString (lpArgs, 2);
CComBSTR bstrFeat (ebLockString (hThread, hStr));
	
	((DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> SetShownFeature (bstrFeat);
	ebUnlockString (hThread, hStr);
}


// ----------------------------------------------------------------------------
// command_GeoObjectWin_RemoveObject
// ----------------------------------------------------------------------------
void command_GeoObjectWin_RemoveObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_GeoObjectWin_RemoveObject);
 
	// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

CComVariant v2(GEOOBJECTMODE_Remove, VT_I4);
CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));

	if (FAILED(GetObjectNumber(v1)))
		return;

WDGeoObject Dummy;

	((DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> GetObject (v1, v2, Dummy.ppi());
}


// ----------------------------------------------------------------------------
// function_GeoObjectWin_AddMenuItem
// ----------------------------------------------------------------------------
void function_GeoObjectWin_AddMenuItem (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObjectWin_AddMenuItem);
 
	// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

CComVariant vHelpText;

ebHSUB hStr1 = ebGetString (lpArgs, 4);
CComBSTR bstrText (ebLockString (hThread, hStr1));
ebHSUB hStr2 = NULL;

	if (iNumArgs > 4) {
		hStr2 = ebGetString (lpArgs, 5);
		V_VT(&vHelpText) = VT_BSTR;
		V_BSTR(&vHelpText) = SysAllocString (WideString(ebLockString (hThread, hStr2)));
	} else {
		V_VT(&vHelpText) = VT_ERROR;
		V_ERROR(&vHelpText) = DISP_E_PARAMNOTFOUND;
	}

HRESULT hr = ((_DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> AddMenuItem (
									ebGetInt (lpArgs, 2), ebGetInt (lpArgs, 3),
									bstrText, vHelpText);

	ebSetInt (lpArgs, 0, SUCCEEDED(hr) ? -1 : false);

	ebUnlockString (hThread, hStr1);
	if (NULL != hStr2) ebUnlockString (hThread, hStr2);
}

// ----------------------------------------------------------------------------
// GetSelectedObjects_GeoObjectWin_function
// ----------------------------------------------------------------------------
void GetSelectedObjects_GeoObjectWin_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(GetSelectedObjects_GeoObjectWin_function);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

WDGeoObjects Objs;
HRESULT hr = ((DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> GetSelectedObjects (Objs.ppi());

	if (SUCCEEDED(hr))
		ebSetObject (lpArgs, 0, (DWORD)Objs.detach());
	else
		ebSetObject (lpArgs, 0, NULL);		// some error
}

// ----------------------------------------------------------------------------
// propget_GeoObjectWin_Left
// ----------------------------------------------------------------------------
void propget_GeoObjectWin_Left (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObjectWin_Left);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

long lLeft = 0;

	((_DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> get_Left (&lLeft);
	ebSetLong (lpArgs, 0, lLeft);
}

// ----------------------------------------------------------------------------
// propset_GeoObjectWin_Left
// ----------------------------------------------------------------------------
void propset_GeoObjectWin_Left (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_GeoObjectWin_Left);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

	((_DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> put_Left (ebGetLong(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// propget_GeoObjectWin_Top
// ----------------------------------------------------------------------------
void propget_GeoObjectWin_Top (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObjectWin_Top);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

long lTop = 0;

	((_DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> get_Top (&lTop);
	ebSetLong (lpArgs, 0, lTop);
}

// ----------------------------------------------------------------------------
// propset_GeoObjectWin_Top
// ----------------------------------------------------------------------------
void propset_GeoObjectWin_Top (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_GeoObjectWin_Top);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

	((_DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> put_Top (ebGetLong(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// propget_GeoObjectWin_Width
// ----------------------------------------------------------------------------
void propget_GeoObjectWin_Width (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObjectWin_Width);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

long lWidth = 0;

	((_DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> get_Width (&lWidth);
	ebSetLong (lpArgs, 0, lWidth);
}

// ----------------------------------------------------------------------------
// propset_GeoObjectWin_Width
// ----------------------------------------------------------------------------
void propset_GeoObjectWin_Width (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_GeoObjectWin_Width);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

	((_DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> put_Width (ebGetLong(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// propget_GeoObjectWin_Height
// ----------------------------------------------------------------------------
void propget_GeoObjectWin_Height (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_GeoObjectWin_Height);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

long lHeight = 0;

	((_DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> get_Height (&lHeight);
	ebSetLong (lpArgs, 0, lHeight);
}

// ----------------------------------------------------------------------------
// propset_GeoObjectWin_Height
// ----------------------------------------------------------------------------
void propset_GeoObjectWin_Height (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_GeoObjectWin_Height);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

	((_DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> put_Height (ebGetLong(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// command_GeoObjectWin_SetActive
// ----------------------------------------------------------------------------
void command_GeoObjectWin_SetActive (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_GeoObjectWin_SetActive);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

	((_DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> SetActive();
}

// ----------------------------------------------------------------------------
// function_GeoObjectWin_IsActive
// ----------------------------------------------------------------------------
void function_GeoObjectWin_IsActive (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_GeoObjectWin_IsActive);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWin))
		return;

VARIANT_BOOL fIsActive = VARIANT_FALSE;

	((_DGeoObjectWin *)ebGetObject (lpArgs, 1)) -> IsActive (&fIsActive);
	ebSetBool (lpArgs, 0, fIsActive);
}

// ----------------------------------------------------------------------------
// func_FDoc
// ----------------------------------------------------------------------------
void func_FDoc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(func_FDoc);

_DTRiASBaseClass *pIBase = (_DTRiASBaseClass *)GetObjectOrApp (lpArgs);

	ebSetObject (lpArgs, 0, NULL);

LONG lRTTI = RTTI_Unknown;

	if (SUCCEEDED(pIBase -> get_isA(&lRTTI)) && lRTTI == RTTI_Document) {
		ebSetObject (lpArgs, 0, (DWORD)pIBase);
		pIBase -> AddRef();
	}
}


// ----------------------------------------------------------------------------
// func_FView
// ----------------------------------------------------------------------------

void func_FView (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(func_FView);

_DTRiASBaseClass *pIBase = (_DTRiASBaseClass *)GetObjectOrApp (lpArgs);

	ebSetObject (lpArgs, 0, NULL);

LONG lRTTI = RTTI_Unknown;

	if (SUCCEEDED(pIBase -> get_isA(&lRTTI)) && lRTTI == RTTI_GeoView) {
		ebSetObject (lpArgs, 0, (DWORD)pIBase);
		pIBase -> AddRef();
	}
}


// ----------------------------------------------------------------------------
// func_FObj
// ----------------------------------------------------------------------------

void func_FObj (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(func_FObj);

_DTRiASBaseClass *pIBase = (_DTRiASBaseClass *)GetObjectOrApp (lpArgs);

	ebSetObject (lpArgs, 0, NULL);

LONG lRTTI = RTTI_Unknown;

	if (SUCCEEDED(pIBase -> get_isA(&lRTTI)) && lRTTI == RTTI_GeoObject) {
		ebSetObject (lpArgs, 0, (DWORD)pIBase);
		pIBase -> AddRef();
	}
}


// ----------------------------------------------------------------------------
// func_FCls
// ----------------------------------------------------------------------------

void func_FCls (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(func_FCls);

_DTRiASBaseClass *pIBase = (_DTRiASBaseClass *)GetObjectOrApp (lpArgs);

	ebSetObject (lpArgs, 0, NULL);

LONG lRTTI = RTTI_Unknown;

	if (SUCCEEDED(pIBase -> get_isA(&lRTTI)) && lRTTI == RTTI_GeoClass) {
		ebSetObject (lpArgs, 0, (DWORD)pIBase);
		pIBase -> AddRef();
	}
}


// ----------------------------------------------------------------------------
// func_FFeat
// ----------------------------------------------------------------------------

void func_FFeat (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(func_FFeat);

_DTRiASBaseClass *pIBase = (_DTRiASBaseClass *)GetObjectOrApp (lpArgs);

	ebSetObject (lpArgs, 0, NULL);

LONG lRTTI = RTTI_Unknown;

	if (SUCCEEDED(pIBase -> get_isA(&lRTTI)) && lRTTI == RTTI_GeoFeature) {
		ebSetObject (lpArgs, 0, (DWORD)pIBase);
		pIBase -> AddRef();
	}
}


// ----------------------------------------------------------------------------
// func_FObjWin
// ----------------------------------------------------------------------------

void func_FObjWin (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(func_FObjWin);

_DTRiASBaseClass *pIBase = (_DTRiASBaseClass *)GetObjectOrApp (lpArgs);

	ebSetObject (lpArgs, 0, NULL);

LONG lRTTI = RTTI_Unknown;

	if (SUCCEEDED(pIBase -> get_isA(&lRTTI)) && lRTTI == RTTI_GeoObjectWin) {
		ebSetObject (lpArgs, 0, (DWORD)pIBase);
		pIBase -> AddRef();
	}
}




// ----------------------------------------------------------------------------
// func_FDocs
// ----------------------------------------------------------------------------

void func_FDocs (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(func_FDocs);

_DTRiASBaseClass *pIBase = (_DTRiASBaseClass *)GetObjectOrApp (lpArgs);

	ebSetObject (lpArgs, 0, NULL);

LONG lRTTI = RTTI_Unknown;

	if (SUCCEEDED(pIBase -> get_isA(&lRTTI)) && lRTTI == RTTI_Documents) {
		ebSetObject (lpArgs, 0, (DWORD)pIBase);
		pIBase -> AddRef();	
	}
}


// ----------------------------------------------------------------------------
// func_FViews
// ----------------------------------------------------------------------------

void func_FViews (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(func_FViews);

_DTRiASBaseClass *pIBase = (_DTRiASBaseClass *)GetObjectOrApp (lpArgs);

	ebSetObject (lpArgs, 0, NULL);

LONG lRTTI = RTTI_Unknown;

	if (SUCCEEDED(pIBase -> get_isA(&lRTTI)) && lRTTI == RTTI_GeoViews) {
		ebSetObject (lpArgs, 0, (DWORD)pIBase);
		pIBase -> AddRef();
	}
}


// ----------------------------------------------------------------------------
// func_FObjs
// ----------------------------------------------------------------------------

void func_FObjs (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(func_FObjs);

_DTRiASBaseClass *pIBase = (_DTRiASBaseClass *)GetObjectOrApp (lpArgs);

	ebSetObject (lpArgs, 0, NULL);

LONG lRTTI = RTTI_Unknown;

	if (SUCCEEDED(pIBase -> get_isA(&lRTTI)) && lRTTI == RTTI_GeoObjects) {
		ebSetObject (lpArgs, 0, (DWORD)pIBase);
		pIBase -> AddRef();
	}
}


// ----------------------------------------------------------------------------
// func_FClss
// ----------------------------------------------------------------------------

void func_FClss (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(func_FClss);

_DTRiASBaseClass *pIBase = (_DTRiASBaseClass *)GetObjectOrApp (lpArgs);

	ebSetObject (lpArgs, 0, NULL);

LONG lRTTI = RTTI_Unknown;

	if (SUCCEEDED(pIBase -> get_isA(&lRTTI)) && lRTTI == RTTI_GeoClasses) {
		ebSetObject (lpArgs, 0, (DWORD)pIBase);
		pIBase -> AddRef();
	}
}


// ----------------------------------------------------------------------------
// func_FFeats
// ----------------------------------------------------------------------------

void func_FFeats (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(func_FFeats);

_DTRiASBaseClass *pIBase = (_DTRiASBaseClass *)GetObjectOrApp (lpArgs);

	ebSetObject (lpArgs, 0, NULL);

LONG lRTTI = RTTI_Unknown;

	if (SUCCEEDED(pIBase -> get_isA(&lRTTI)) && lRTTI == RTTI_GeoFeatures) {
		ebSetObject (lpArgs, 0, (DWORD)pIBase);
		pIBase -> AddRef();
	}
}


// ----------------------------------------------------------------------------
// func_FObjWins
// ----------------------------------------------------------------------------

void func_FObjWins (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(func_FObjWins);

_DTRiASBaseClass *pIBase = (_DTRiASBaseClass *)GetObjectOrApp (lpArgs);

	ebSetObject (lpArgs, 0, NULL);

LONG lRTTI = RTTI_Unknown;

	if (SUCCEEDED(pIBase -> get_isA(&lRTTI)) && lRTTI == RTTI_GeoObjectWins) {
		ebSetObject (lpArgs, 0, (DWORD)pIBase);
		pIBase -> AddRef();	
	}
}


// ----------------------------------------------------------------------------
// func_FBase
// ----------------------------------------------------------------------------

void func_FBase (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(func_FBase);

_DTRiASBaseClass *pIBase = (_DTRiASBaseClass *)GetObjectOrApp (lpArgs);

	ebSetObject (lpArgs, 0, (DWORD)pIBase);
	pIBase -> AddRef();	
}


// ----------------------------------------------------------------------------
// cmd_Path
// ----------------------------------------------------------------------------

void cmd_Path (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(cmd_Path);

ebHSUB hStr = ebGetString (lpArgs, 1);
CComBSTR bstrPath (ebLockString (hThread, hStr));
	
	((OLE2AutoExtension *)g_pTE) -> AppDisp() -> put_DefaultFilePath (bstrPath);
	ebUnlockString (hThread, hStr);
}

// ----------------------------------------------------------------------------
// cmd_Visible
// ----------------------------------------------------------------------------
void cmd_Visible (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(cmd_Visible);
	((OLE2AutoExtension *)g_pTE) -> AppDisp() -> put_Visible (ebGetInt (lpArgs, 1));
}

// ----------------------------------------------------------------------------
// func_NewDocument
// ----------------------------------------------------------------------------
void func_NewDocument (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(func_NewDocument);

ebHSUB hStr = ebGetString (lpArgs, 1);
CComBSTR bstrName (ebLockString (hThread, hStr));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v3 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant v4 (MakeVARIANT (hThread, iNumArgs, lpArgs, 4));

WDDocument Doc;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> AppDisp() -> NewDocument (bstrName, v2, v3, v4, Doc.ppi());

	ebUnlockString (hThread, hStr);
	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Doc.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// func_OpenDocument
// ----------------------------------------------------------------------------
void func_OpenDocument (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(func_OpenDocument);

ebHSUB hStr = ebGetString (lpArgs, 1);
CComBSTR bstrName (ebLockString (hThread, hStr));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v3 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant v4 (MakeVARIANT (hThread, iNumArgs, lpArgs, 4));

WDDocument Doc;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> AppDisp() -> OpenDocument (bstrName, v2, v3, v4, Doc.ppi());

	ebUnlockString (hThread, hStr);
	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Doc.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// func_GetDocument
// ----------------------------------------------------------------------------
void func_GetDocument (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(func_GetDocument);

ebHSUB hStr = ebGetString (lpArgs, 1);
CComVariant v1 (ebLockString (hThread, hStr));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));

WDDocument Doc;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> AppDisp() -> GetDocument (v1, v2, Doc.ppi());

	ebUnlockString (hThread, hStr);
	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Doc.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}


// ----------------------------------------------------------------------------
// func_AddDocument
// ----------------------------------------------------------------------------
void func_AddDocument (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(func_AddDocument);

CComVariant v2;

	V_VT(&v2) = VT_I4;	// Add ??? now
	V_I4(&v2) = DOCMODE_Add;
		
ebHSUB hStr = ebGetString (lpArgs, 1);
CComVariant v1 (ebLockString (hThread, hStr));

WDDocument Doc;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> AppDisp() -> GetDocument (v1, v2, Doc.ppi());

	ebUnlockString (hThread, hStr);
	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Doc.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// func_MakeActive
// ----------------------------------------------------------------------------
void func_MakeActive (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(func_MakeActive);

CComVariant v2;
	
	V_VT(&v2) = VT_I4;	
	V_I4(&v2) = DOCMODE_Replace;
		
ebHSUB hStr = ebGetString (lpArgs, 1);
CComVariant v1 (ebLockString (hThread, hStr));

WDDocument Doc;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> AppDisp() -> GetDocument (v1, v2, Doc.ppi());

	ebUnlockString (hThread, hStr);
	if (SUCCEEDED(hr)) 
		ebSetObject (lpArgs, 0, (DWORD)Doc.detach());
	else
		ebSetObject (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// cmd_CloseDocument
// ----------------------------------------------------------------------------
void cmd_CloseDocument (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(cmd_CloseDocument);

CComVariant v2;
	
	V_VT(&v2) = VT_I4;
	V_I4(&v2) = DOCMODE_Remove;

ebHSUB hStr = ebGetString (lpArgs, 1);
CComVariant v1 (ebLockString (hThread, hStr));
WDDocument Doc; 

	((OLE2AutoExtension *)g_pTE) -> AppDisp() -> GetDocument (v1, v2, Doc.ppi());
	ebUnlockString (hThread, hStr);
}

// ----------------------------------------------------------------------------
// help_SetDebug
// ----------------------------------------------------------------------------
void help_SetDebug (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE_SYS(help_SetDebug);

	g_fDebugScript = ebGetInt (lpArgs, 1) ? true : false;
}

// ----------------------------------------------------------------------------
// Refresh_Documents_command
// ----------------------------------------------------------------------------
void Refresh_Documents_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Refresh_Documents_command);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_Documents))
		return;
	((_DDocuments *)ebGetObject (lpArgs, 1)) -> Refresh();
}

// ----------------------------------------------------------------------------
// Refresh_GeoObjects_command
// ----------------------------------------------------------------------------
void Refresh_GeoObjects_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Refresh_GeoObjects_command);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjects))
		return;
	((_DGeoObjects *)ebGetObject (lpArgs, 1)) -> Refresh();
}

// ----------------------------------------------------------------------------
// Refresh_GeoClasses_command
// ----------------------------------------------------------------------------
void Refresh_GeoClasses_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Refresh_GeoClasses_command);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClasses))
		return;
	((_DGeoClasses *)ebGetObject (lpArgs, 1)) -> Refresh();
}

// ----------------------------------------------------------------------------
// Refresh_GeoViews_command
// ----------------------------------------------------------------------------
void Refresh_GeoViews_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Refresh_GeoViews_command);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoViews))
		return;
	((_DViews *)ebGetObject (lpArgs, 1)) -> Refresh();
}

// ----------------------------------------------------------------------------
// Refresh_GeoObjectWins_command
// ----------------------------------------------------------------------------
void Refresh_GeoObjectWins_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Refresh_GeoObjectWins_command);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObjectWins))
		return;
	((_DGeoObjectWins *)ebGetObject (lpArgs, 1)) -> Refresh();
}

// ----------------------------------------------------------------------------
// Refresh_GeoFeatures_command
// ----------------------------------------------------------------------------
void Refresh_GeoFeatures_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Refresh_GeoFeatures_command);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoFeatures))
		return;
	((_DGeoFeatures *)ebGetObject (lpArgs, 1)) -> Refresh();
}

///////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------
// This routine is the entry point used by the EBRUN.DLL module to execute 
// an external routine.
//
// parameters:	hThread		pointer to reserved structure
//			wCmdNum		ID of the extension routine as it appears in the
//						prototype table
//			iNumArgs	number of arguments passed to this routine
//			lpArgs		pointer to an array of pointers to the arguments
//
// returns:		nothing
// ----------------------------------------------------------------------------

extern "C"
void ebCALLBACK _XTENSN_EXPORT RuntimeCallback(ebHTHREAD hThread, WORD wCmdNum, int iNumArgs, ebARGS lpArgs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

#if defined(_DEBUG)
// ScriptNamen für Debugzwecke hier ablegen
LPCSTR pcScriptName = reinterpret_cast<LPCSTR>(ebThread_GetLong (hThread, SETLONG_NAME));
#endif // defined(_DEBUG)

// call the extension routine via the jump table
	try {
		if (wCmdNum >= g_iExtFcnsOffset && wCmdNum < g_iExtFcnsLast)
			(*g_pExtFcns[wCmdNum - g_iExtFcnsOffset])(hThread, iNumArgs, lpArgs);
		else 
			TRiAS_not_supported (hThread, iNumArgs, lpArgs);

		return;		// ok
	} catch (...) {
		;			// do nothing here
	}

// Fehler in Form einer MsgBox melden oder 'On Error' rufen
CString str;

	str.Format (IDS_GENERALERROR, g_cbTRiAS);
	ebRuntimeError (hThread, true, TRIASERR_GENERALERROR, str);
}


// --------------------------------------------------------------------------
// Init - this routine is called when the DLL is loaded. If this routien
// returns FALSE, then the extension will not be loaded. 
//
// parameters:	none
//
// returns:		true		success initializing
//			false		unable to initialize
// --------------------------------------------------------------------------
#if defined(WIN32)
#define LOADLIBRARY_FAILED(x) (x == 0)
#else
#define LOADLIBRARY_FAILED(x) (x <= HINSTANCE_ERROR)
#endif

extern "C"
bool _XTENSN_EXPORT ebCALLBACK Init (ebHINSTANCE hInst)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

// Sprungverteiler anlegen
	g_pExtFcns = InitJumpTable (g_iExtFcnsOffset, g_iExtFcnsLast);
	if (NULL == g_pExtFcns)
		return false;

#if defined(DYNAMIC_BASIC)
// BasicScript laden 
char szModule[_MAX_PATH];

	GetModuleFileName (hInst, szModule, _MAX_PATH);

os_path path (szModule);

	path.filename (PRODUCT_PUB_NAME ebMODEXT);

// #HK990620 work around WinNT4 LoadProcess bug
char szModuleShort[_MAX_PATH];
int cbShortName = GetShortPathName (os_string(path).c_str(), szModuleShort, _MAX_PATH);
LPCSTR pcModule = NULL;

	if (cbShortName == _MAX_PATH)
		return;
	pcModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? m_strName.c_str() : szModuleShort;

	g_hBScript = LoadLibrary (PRODUCT_PUB_NAME ebMODEXT);	// RunTime binden

	if (LOADLIBRARY_FAILED(g_hBScript))
		g_hBScript = NULL;
		
return g_hBScript != NULL;
#else
return true;
#endif // DYNAMIC_BASIC
}

// --------------------------------------------------------------------------
// This function is called immediately before the extension DLL is removed
// from memory. It can perform any cleanup that the DLL may need to perform.
// --------------------------------------------------------------------------
extern "C"
void _XTENSN_EXPORT ebCALLBACK Term (ebHINSTANCE hInst)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

#if defined(DYNAMIC_BASIC)
// BasicScript freigeben
	if (g_hBScript != NULL) {
		FreeLibrary (g_hBScript);
		g_hBScript = NULL;
	}
#endif // DYNAMIC_BASIC

// JumpTable wieder freigeben
	FreeJumpTable (g_pExtFcns);
}

