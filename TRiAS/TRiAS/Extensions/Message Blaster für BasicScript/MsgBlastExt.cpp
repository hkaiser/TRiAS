// MsgBlastExt.cpp: Implementation of BasicScript-Extension functions

#include "stdafx.h"

#include "resource.h"

#include <eb.h>
#include <bscrerr.h>
#include <Trace.h>

#include "MsgBlastExt.h"
#include "Jumptab.h"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if defined(_DEBUG)
//
// WIN32: these flags could be set in
//	  HKEY_CURRENT_USER\Software\uve\TRiAS\Extensions\TRiAS.OleAutomation.1\Config\TraceFlags
//
// TraceFlags:	0x01 - ADDREF_TRACE, RELEASE_TRACE
//				0x02 - CONSTRUCT_TRACE, DESTRUCT_TRACE
//				0x04 - BASIC_OP_TRACE
//				0x08 - BASIC_OP_TRACE_SYS
//
extern "C" DWORD locTraceFlags = 0;
#endif

///////////////////////////////////////////////////////////////////////////////
// Benötigte SmartIF's
DefineSmartInterface(MessageMap);
DefineSmartInterface(MouseAction);

// Make Ole-VARIANT from ebVARIANT --------------------------------------------
VARIANT MakeVARIANT (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs, int iArg)
{
VARIANT vResult;

	if (iArg > iNumArgs) {
		V_VT(&vResult) = VT_ERROR;
		V_ERROR(&vResult) = DISP_E_PARAMNOTFOUND;
		return vResult;
	}
	
ebVARIANT v;

	ebGetVariantEx (lpArgs, iArg, &v);

	VariantInit (&vResult);
	switch (v.Type) {
	case TYP_BOOLEAN:	// VT_BOOL
	case TYP_INTEGER:	// VT_I2
	case TYP_LONG:		// VT_I4
	case TYP_SINGLE:	// VT_R4
	case TYP_DOUBLE:	// VT_R8
	case TYP_CURRENCY:	// VT_CY
	case TYP_DATE:		// VT_DATE
		vResult = (VARIANT &)v;
		break;
		
	case TYP_ERROR:		// VT_ERROR
		if (ebHIWORD(v.u.l) & 0x0002) {
			V_VT(&vResult) = VT_ERROR;	// parameter was skipped
			V_ERROR(&vResult) = DISP_E_PARAMNOTFOUND;
		} else
			vResult = (VARIANT &)v;
		break;
		
	case TYP_STRING:	// VT_BSTR
		{
		ebHSUB hStr = v.u.h;
		LPTSTR pT = ebLockString (hThread, hStr);
		
			if (pT) {
				USES_CONVERSION;
				V_VT(&vResult) = VT_BSTR;
				V_BSTR(&vResult) = SysAllocString (A2OLE(pT));
				ebUnlockString (hThread, hStr);
			}
		}
		break;
		
	case TYP_OLEOBJECT:	// VT_DISPATCH
		{
			V_VT (&vResult) = VT_DISPATCH;
		
		IDispatch *pIDisp = ebGetDispatch (hThread, v.u.o);

			if (pIDisp) 
				pIDisp -> AddRef();
			V_DISPATCH(&vResult) = pIDisp;
		}
		break;

	case TYP_APPOBJECT:
		V_VT (&vResult) = VT_UNKNOWN;
		V_UNKNOWN(&vResult) = reinterpret_cast<IUnknown *>(v.u.o);
		if (NULL != V_UNKNOWN(&vResult)) 
			V_UNKNOWN(&vResult) -> AddRef();
		break;

	default:
		VariantInit (&vResult);
		break;
	}

	return vResult;
}

// ----------------------------------------------------------------------------
// TRiAS_not_supported
// ----------------------------------------------------------------------------
void TRiAS_not_supported (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
// Fehler in Form einer MsgBox melden oder 'On Error' rufen
CString str;

	TRY {
		str.LoadString (IDS_NOTSUPPORTED);
	} CATCH (CMemoryException, e) {
		str = "No Memory!";
	} END_CATCH;

	ebRuntimeError (hThread, true, TRIASERR_NOTSUPPORTED, str);
}

// ----------------------------------------------------------------------------
// refcnt_MessageMap
// ----------------------------------------------------------------------------
void refcnt_MessageMap (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE_SYS(refcnt_MessageMap);

	switch (iNumArgs) {
	case OBJECT_REFNEW:
		ebSetObject (lpArgs, 0, NULL);		// für alle Fälle
		COM_TRY {
		WMessageMap Map (CLSID_MessageMap);	// throws hr

			ebSetObject (lpArgs, 0, (DWORD)Map.detach());

		} COM_CATCH_NORETURN;
		break;
		
	case OBJECT_REFINC:
		((IUnknown *)ebGetObject (lpArgs, 1)) -> AddRef();
		break;
		
	case OBJECT_REFDEC:
		((IUnknown *)ebGetObject (lpArgs, 1)) -> Release();
		break;
	}
}

// ----------------------------------------------------------------------------
// propget_MessageMap_Enabled
// ----------------------------------------------------------------------------
void propget_MessageMap_Enabled (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_MessageMap_Enabled);

WMessageMap Map ((IMessageMap *)ebGetObject (lpArgs, 1));
VARIANT_BOOL bVal;

	Map -> get_Enabled (&bVal);
	ebSetBool (lpArgs, 0, bVal);
}

// ----------------------------------------------------------------------------
// propset_MessageMap_Enabled
// ----------------------------------------------------------------------------
void propset_MessageMap_Enabled (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_MessageMap_Enabled);

WMessageMap Map ((IMessageMap *)ebGetObject (lpArgs, 1));
VARIANT_BOOL bVal = ebGetBool (lpArgs, 2);

	Map -> put_Enabled (bVal);
}

// ----------------------------------------------------------------------------
// propget_MessageMap_HasMsg
// ----------------------------------------------------------------------------
void propget_MessageMap_HasMsg (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_MessageMap_HasMsg);

WMessageMap Map ((IMessageMap *)ebGetObject (lpArgs, 1));
long lMsg = ebGetLong (lpArgs, 2);
VARIANT_BOOL bVal;

	Map -> get_HasMsg (lMsg, &bVal);
	ebSetBool (lpArgs, 0, bVal);
}

// ----------------------------------------------------------------------------
// propget_MessageMap_ToCall
// ----------------------------------------------------------------------------
void propget_MessageMap_ToCall (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_MessageMap_ToCall);

WMessageMap Map ((IMessageMap *)ebGetObject (lpArgs, 1));
long lMsg = ebGetLong (lpArgs, 2);
CComBSTR bstrToCall;

	Map -> get_ToCall (lMsg, &bstrToCall);

	ebFreeString (hThread, ebGetString (lpArgs, 0));

	USES_CONVERSION;
	if (!bstrToCall)
		ebSetString (lpArgs, 0, ebCreateString (hThread, OLE2A(bstrToCall)));
	else
		ebSetString (lpArgs, 0, NULL);
}

// ----------------------------------------------------------------------------
// propset_MessageMap_ToCall
// ----------------------------------------------------------------------------
void propset_MessageMap_ToCall (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_MessageMap_ToCall);

WMessageMap Map ((IMessageMap *)ebGetObject (lpArgs, 1));
long lMsg = ebGetLong (lpArgs, 2);
ebHSUB hStr = ebGetString (lpArgs, 3);			// ProzedurName
CComBSTR bstr (ebLockString (hThread, hStr));

	Map -> put_ToCall (lMsg, bstr);
	ebUnlockString (hThread, hStr);
}

// ----------------------------------------------------------------------------
// command_MessageMap_RemoveAll
// ----------------------------------------------------------------------------
void command_MessageMap_RemoveAll (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(command_MessageMap_RemoveAll);

WMessageMap Map ((IMessageMap *)ebGetObject (lpArgs, 1));

	Map -> RemoveAll();
}

// ----------------------------------------------------------------------------
// function_MessageMap_RemoveMessage
// ----------------------------------------------------------------------------
void function_MessageMap_RemoveMessage (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_MessageMap_RemoveMessage);

WMessageMap Map ((IMessageMap *)ebGetObject (lpArgs, 1));
long lMsg = ebGetLong (lpArgs, 2);
VARIANT_BOOL bVal;
HRESULT hr = Map -> RemoveMessage (lMsg, &bVal);

	if (NULL != lpArgs[0]) {		// nur, wenn nicht method
		if (SUCCEEDED(hr))
			ebSetBool (lpArgs, 0, bVal);
		else
			ebSetBool (lpArgs, 0, 0);
	}
}

// ----------------------------------------------------------------------------
// function_MessageMap_AddMessage
// ----------------------------------------------------------------------------
void function_MessageMap_AddMessage (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(function_MessageMap_AddMessage);

WMessageMap Map ((IMessageMap *)ebGetObject (lpArgs, 1));
long lMsg = ebGetLong (lpArgs, 2);
ebHSUB hStr = ebGetString (lpArgs, 3);			// ProzedurName
CComBSTR bstrToCall (ebLockString (hThread, hStr));
VARIANT_BOOL bVal;
HRESULT hr = Map -> AddMessage (lMsg, bstrToCall, &bVal);

	if (NULL != lpArgs[0]) {		// nur, wenn nicht method
		if (SUCCEEDED(hr))
			ebSetBool (lpArgs, 0, bVal);
		else
			ebSetBool (lpArgs, 0, 0);
	}
}

// ----------------------------------------------------------------------------
// refcnt_Mouse	
// ----------------------------------------------------------------------------
void refcnt_Mouse (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	switch (iNumArgs) {
	case OBJECT_REFNEW:
		ebSetObject (lpArgs, 0, NULL);		// für alle Fälle
		break;
		
	case OBJECT_REFINC:
//		((IUnknown *)ebGetObject(lpArgs, 1)) -> AddRef();
		ASSERT(ID_MOUSE_COOKIE == ebGetObject(lpArgs, 1));	// muß globales MouseObjekt sein
		break;
		
	case OBJECT_REFDEC:
//		((IUnknown *)ebGetObject(lpArgs, 1)) -> Release();
		ASSERT(ID_MOUSE_COOKIE == ebGetObject(lpArgs, 1));	// muß globales MouseObjekt sein
		break;
	}
}

// ----------------------------------------------------------------------------
// propget_Mouse_GetLastKey	
// ----------------------------------------------------------------------------
void propget_Mouse_GetLastKey (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	ASSERT(ID_MOUSE_COOKIE == ebGetObject(lpArgs, 1));	// muß globales MouseObjekt sein

	COM_TRY {
	WMouseAction Mouse (CLSID_MouseAction);		// singleton 
	long rgLastKey = (long) MOUSEKEY_Unknown;

		Mouse -> get_LastKey (&rgLastKey);
		ebSetLong (lpArgs, 0, (long)rgLastKey);
	} COM_CATCH_NORETURN;
}

// ----------------------------------------------------------------------------
// propfunc_Mouse_GetPoint	
// ----------------------------------------------------------------------------
void propfunc_Mouse_GetPoint (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	ASSERT(ID_MOUSE_COOKIE == ebGetObject(lpArgs, 1));	// muß globales MouseObjekt sein

	COM_TRY {
	ebHSUB hStrKey = ebGetString (lpArgs, 2);
	double dX = 0.0;
	double dY = 0.0;
	WMouseAction Mouse (CLSID_MouseAction);		// singleton 
	CComBSTR bstrPrompt (ebLockString (hThread, hStrKey));
	HRESULT hr = Mouse -> GetPoint (bstrPrompt, &dX, &dY);

		if (SUCCEEDED(hr)) {
			ebSetDouble (lpArgs, 3, dX);
			ebSetDouble (lpArgs, 4, dY);
			ebSetBool (lpArgs, 0,  ebTRUE);
		} else 
			ebSetBool (lpArgs, 0,  ebFALSE);

		if (hStrKey) 
			ebUnlockString (hThread, hStrKey);
	} COM_CATCH_NORETURN;
}

// ----------------------------------------------------------------------------
// propfunc_Mouse_GetPointDrag	
// ----------------------------------------------------------------------------
void propfunc_Mouse_GetPointDrag (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	ASSERT(ID_MOUSE_COOKIE == ebGetObject(lpArgs, 1));	// muß globales MouseObjekt sein

	COM_TRY {
	ebHSUB hStrKey = ebGetString (lpArgs, 2);
	double dX = 0.0;
	double dY = 0.0;
	WMouseAction Mouse (CLSID_MouseAction);		// singleton 
	CComBSTR bstrPrompt (ebLockString (hThread, hStrKey));
	HRESULT hr = Mouse -> GetPointDrag (bstrPrompt, &dX, &dY);

		if (SUCCEEDED(hr)) {
			ebSetDouble (lpArgs, 3, dX);
			ebSetDouble (lpArgs, 4, dY);
			ebSetBool (lpArgs, 0,  ebTRUE);
		} else 
			ebSetBool (lpArgs, 0,  ebFALSE);

		if (hStrKey) 
			ebUnlockString (hThread, hStrKey);
	} COM_CATCH_NORETURN;
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
__declspec(dllexport) void ebCALLBACK RuntimeCallback(ebHTHREAD hThread,WORD wCmdNum,int iNumArgs,ebARGS lpArgs)
{
// call the extension routine via the jump table
	if (wCmdNum >= g_iExtFcnsOffset && wCmdNum < g_iExtFcnsLast)
		(*g_pExtFcns[wCmdNum - g_iExtFcnsOffset])(hThread, iNumArgs, lpArgs);
	else 
		TRiAS_not_supported (hThread, iNumArgs, lpArgs);
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
#define LOADLIBRARY_FAILED(x) (x == 0)

extern "C"
__declspec(dllexport) bool ebCALLBACK Init (ebHINSTANCE hInst)
{
// Sprungverteiler anlegen
	g_pExtFcns = InitJumpTable (g_iExtFcnsOffset, g_iExtFcnsLast);
	if (NULL == g_pExtFcns)
		return false;

#if defined(_DEBUG)
	{	// Traceflags einlesen
	CRegKey regCfg;
	
		locTraceFlags = 0;
		if (ERROR_SUCCESS == regCfg.Open (HKEY_CURRENT_USER, TEXT("Software")) &&
			ERROR_SUCCESS == regCfg.Open (regCfg, TEXT("uve")) &&
			ERROR_SUCCESS == regCfg.Open (regCfg, TEXT("TRiAS")) &&
			ERROR_SUCCESS == regCfg.Open (regCfg, TEXT("Extensions")) &&
			ERROR_SUCCESS == regCfg.Open (regCfg, TEXT("TRiAS.OleAutomation.1")) &&
			ERROR_SUCCESS == regCfg.Open (regCfg, TEXT("Config")))
		{
			regCfg.QueryValue (locTraceFlags, TEXT("TraceFlags"));
		}
	}
#endif

	return true;
}

// --------------------------------------------------------------------------
// This function is called immediately before the extension DLL is removed
// from memory. It can perform any cleanup that the DLL may need to perform.
// --------------------------------------------------------------------------
extern "C"
__declspec(dllexport) void ebCALLBACK Term (ebHINSTANCE hInst)
{
// JumpTable wieder freigeben
	FreeJumpTable (g_pExtFcns);
}

