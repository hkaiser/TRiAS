// Implementation of BasicScript-Extension functions (Geometrie-Editierung)
// File: GeoEditOutside.cpp
// H. Kaiser, W. Mörtl


#include "GeoEditP.h"

#include <eb.h>
#include <bscrerr.h>
#include <TraceMacros.h>

#include "GeoEditOutside.h"
#include "JumpTab.h"
#include "GeoEditR.h"

#include "SmartInterfaces.h"


#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if defined(_DEBUG)
//
// These flags could be set in
//	  HKEY_CURRENT_USER\Software\...\TRiAS\Extensions\TRiAS.OleAutomation.1\Config\TraceFlags
//
// TraceFlags:	0x01 - ADDREF_TRACE, RELEASE_TRACE
//				0x02 - CONSTRUCT_TRACE, DESTRUCT_TRACE
//				0x04 - BASIC_OP_TRACE
//				0x08 - BASIC_OP_TRACE_SYS
//
extern "C" DWORD locTraceFlags = 0;
#define TRACE(x)	TX_TRACE(x)
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// Benötigte SmartInterface's
DefineSmartInterface (EditExternalObjects);



///////////////////////////////////////////////////////////////////////////////////////////////
// Make Ole-VARIANT from ebVARIANT
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
				pIDisp->AddRef();
			V_DISPATCH(&vResult) = pIDisp;
		}
		break;

	case TYP_APPOBJECT:
		V_VT (&vResult) = VT_UNKNOWN;
		V_UNKNOWN(&vResult) = reinterpret_cast<IUnknown *>(v.u.o);
		if (NULL != V_UNKNOWN(&vResult)) 
			V_UNKNOWN(&vResult)->AddRef();
		break;

	default:
		VariantInit (&vResult);
		break;
	}

	return vResult;
}


// --------------------------------------------------------------------------------------------
// TRiAS_not_supported
// --------------------------------------------------------------------------------------------
void TRiAS_not_supported (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
// Fehler in Form einer MsgBox melden oder 'On Error' rufen
ResourceFile RF (g_pDLLName);
ResString resNotSupp (ResID(IDS_NOTSUPPORTED, &RF), 70);	// Eine nicht implementierte Basicfunktion wurde gerufen

	ebRuntimeError (hThread, true, TRIASERR_NOTSUPPORTED, resNotSupp);
}


// --------------------------------------------------------------------------------------------
// refcnt_geoedit
// --------------------------------------------------------------------------------------------
void refcnt_geoedit (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE (refcnt_geoedit);

	_ASSERTE (false);
}


// --------------------------------------------------------------------------------------------
// function_geoedit_AddObject
// --------------------------------------------------------------------------------------------
void function_geoedit_AddObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE (function_geoedit_AddObject);

	_ASSERTE (100L == ebGetObject (lpArgs, 1));

ebBOOL bRet = true;		// return-Wert

	try
	{
	WEditExternalObjects Edit (g_pTE);
	HRESULT hrRet = Edit->AddObject();

		if (FAILED(hrRet)) bRet = false;
	}
	catch (_com_error&)
	{
		bRet = false;
	}

	ebSetBool (lpArgs, 0, bRet);

} // function_geoedit_AddObject


// --------------------------------------------------------------------------------------------
// function_geoedit_GetObject
// --------------------------------------------------------------------------------------------
void function_geoedit_GetObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE (function_geoedit_GetObject);

	_ASSERTE (100L == ebGetObject (lpArgs, 1));

ebVARIANT varRet;	// return-Wert

	memset (&varRet, 0, sizeof(ebVARIANT));
	varRet.ExtType = ebGetAppObjExtType (hThread, "GeoObject", NULL);
	varRet.Type = TYP_APPOBJECT;

	try
	{
	WEditExternalObjects Edit (g_pTE);
	HRESULT hrRet = Edit->GetObject();	// ein Parameter muß das zurückgegebene Objekt enthalten

		if (SUCCEEDED(hrRet))
			// das zurückgegebene Objekt wObj in varRet eintragen
			/*varRet.u.o = reinterpret_cast<DWORD>(wObj.detach())*/;
		else
			varRet.u.l = 0L;	// bedeutet in BASIC "Nothing"
	}
	catch (_com_error&)
	{
		varRet.u.l = 0L;		// bedeutet in BASIC "Nothing"
	}

	ebSetVariant (lpArgs, 0, &varRet);

} // function_geoedit_GetObject


// --------------------------------------------------------------------------------------------
// function_geoedit_RemoveObject
// --------------------------------------------------------------------------------------------
void function_geoedit_RemoveObject (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE (function_geoedit_RemoveObject);

	_ASSERTE (100L == ebGetObject (lpArgs, 1));

ebBOOL bRet = true;		// return-Wert

	try
	{
	WEditExternalObjects Edit (g_pTE);
	HRESULT hrRet = Edit->RemoveObject();

		if (FAILED(hrRet)) bRet = false;
	}
	catch (_com_error&)
	{
		bRet = false;
	}

	ebSetBool (lpArgs, 0, bRet);

} // function_geoedit_RemoveObject


// --------------------------------------------------------------------------------------------
// function_geoedit_AddObjects
// --------------------------------------------------------------------------------------------
void function_geoedit_AddObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE (function_geoedit_AddObjects);

	_ASSERTE (100L == ebGetObject (lpArgs, 1));

ResourceFile RF (g_pDLLName);
ResString resNoObjs (ResID(IDS_NOGEOOBJECTS, &RF), 70);	// Der Parameter der BasicFunktion ist
														// nicht vom Typ "GeoObjects".
ebBOOL bRet = true;		// Rückkehrtwert (nur für BASIC-Function's)

	try
	{
	// im 2. Parameter werden die hinzuzufügenden Objekte übergeben
	CComVariant vObjs = MakeVARIANT (hThread, iNumArgs, lpArgs, 2);
	
		if (V_VT(&vObjs) != VT_UNKNOWN)
			ebRuntimeError(hThread, true, TRIASERR_TYPEMISMATCH, resNoObjs);

	WEditExternalObjects Edit (g_pTE);
	WDGeoObjects wObjs (V_UNKNOWN(&vObjs));
	HRESULT hrRet = Edit->AddObjects (wObjs);

		if (FAILED(hrRet)) bRet = false;
	}
	catch (_com_error& e)
	{
		if (E_NOINTERFACE == _COM_ERROR(e))
			ebRuntimeError (hThread, true, TRIASERR_TYPEMISMATCH, resNoObjs);
		bRet = false;
	}

	if (lpArgs[0] != NULL)		// nur für BASIC-Function's, jedoch nicht für BASIC-Sub's
		ebSetBool (lpArgs, 0, bRet);

} // function_geoedit_AddObjects


// --------------------------------------------------------------------------------------------
// function_geoedit_GetObjects
// --------------------------------------------------------------------------------------------
void function_geoedit_GetObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE (function_geoedit_GetObjects);

	_ASSERTE (100L == ebGetObject (lpArgs, 1));

ResourceFile RF (g_pDLLName);
ResString resNoObjs (ResID(IDS_NOGEOOBJECTS, &RF), 70);	// Der Parameter der BasicFunktion ist
														// nicht vom Typ "GeoObjects".
ebVARIANT varRet;	// return-Wert

	memset (&varRet, 0, sizeof(ebVARIANT));
	varRet.ExtType = ebGetAppObjExtType (hThread, "GeoObjects", NULL);
	varRet.Type = TYP_APPOBJECT;

	try
	{
	// im 2. Parameter sind die gewünschten Objekttypen der zurückzugebenden Objekte angegeben
	CComVariant vOTyps = MakeVARIANT (hThread, iNumArgs, lpArgs, 2);
	long lObjTypes = (OTPunkt|OTLinie|OTFlaeche|OTText);	

		if (SUCCEEDED (vOTyps.ChangeType (VT_I4)))	// läßt sich vOTyps in TYP_LONG konvertieren?
			lObjTypes = V_I4(&vOTyps);

	WEditExternalObjects Edit (g_pTE);
	WDGeoObjects wObjs;
	HRESULT hrRet = Edit->GetObjects ((IDispatch**)wObjs.ppi(), lObjTypes);

		if (SUCCEEDED(hrRet))
			varRet.u.o = reinterpret_cast<DWORD>(wObjs.detach());
		else
			varRet.u.l = 0L;	// bedeutet in BASIC "Nothing"
	}

	catch (_com_error &e)
	{
		if (E_NOINTERFACE == _COM_ERROR(e))
			// "true" im 2. Parameter bedeutet: absoluter Programmabbruch
			ebRuntimeError (hThread, true, TRIASERR_TYPEMISMATCH, resNoObjs);

		varRet.u.l = 0L;		// bedeutet in BASIC "Nothing"
	}

	ebSetVariant (lpArgs, 0, &varRet);

} // function_geoedit_GetObjects


// --------------------------------------------------------------------------------------------
// function_geoedit_RemoveObjects
// --------------------------------------------------------------------------------------------
void function_geoedit_RemoveObjects (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE (function_geoedit_RemoveObjects);

	_ASSERTE (100L == ebGetObject (lpArgs, 1));

ebBOOL bRet = true;		// Rückkehrtwert (nur für BASIC-Function's)

	try
	{
	WEditExternalObjects Edit (g_pTE);
	HRESULT hrRet = Edit->RemoveObjects();

		if (FAILED(hrRet)) bRet = false;
	}
	catch (_com_error&)
	{
		bRet = false;
	}

	if (lpArgs[0] != NULL)		// nur für BASIC-Function's, jedoch nicht für BASIC-Sub's
		ebSetBool (lpArgs, 0, bRet);

} // function_geoedit_RemoveObjects


///////////////////////////////////////////////////////////////////////////////////////////////
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

extern "C"
__declspec(dllexport) void ebCALLBACK RuntimeCallback (ebHTHREAD hThread, WORD wCmdNum,
													   int iNumArgs, ebARGS lpArgs)
{
// call the extension routine via the jump table
	if (wCmdNum >= g_iExtFcnsOffset && wCmdNum < g_iExtFcnsLast)
		(*g_pExtFcns[wCmdNum - g_iExtFcnsOffset])(hThread, iNumArgs, lpArgs);
	else 
		TRiAS_not_supported (hThread, iNumArgs, lpArgs);
}


// --------------------------------------------------------------------------------------------
// Init - this routine is called when the DLL is loaded. If this routien
// returns false, then the extension will not be loaded. 
//
// parameters:	none
//
// returns:		true		success initializing
//				false		unable to initialize
// --------------------------------------------------------------------------------------------
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
			ERROR_SUCCESS == regCfg.Open (regCfg, REG_COMPANY_KEY) &&
			ERROR_SUCCESS == regCfg.Open (regCfg, REG_PRODUCT_KEY) &&
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

// --------------------------------------------------------------------------------------------
// This function is called immediately before the extension DLL is removed
// from memory. It can perform any cleanup that the DLL may need to perform.
// --------------------------------------------------------------------------------------------
extern "C"
__declspec(dllexport) void ebCALLBACK Term (ebHINSTANCE hInst)
{
// JumpTable wieder freigeben
	FreeJumpTable (g_pExtFcns);
}
