// ColorExt.cpp: Implementation of BasicScript-Extension functions

#include "stdafx.h"

#include <eb.h>
#include <bscrerr.h>
#include <Tracemacros.h>
#include "Colors.h"

#include "resource.h"
#include "Jumptab.h"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if defined(_DEBUG)
//
// WIN32: these flags could be set in
//	  HKEY_CURRENT_USER\Software\TRiAS\InterTRiAS\Extensions\TRiAS.OleAutomation.1\Config\TraceFlags
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
DefineSmartInterface(DoubleColor);
DefineSmartInterface(ColorLookUp);

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

///////////////////////////////////////////////////////////////////////////////
// DoubleColor

// ----------------------------------------------------------------------------
// refcnt_DoubleColor
// ----------------------------------------------------------------------------
void refcnt_DoubleColor (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE_SYS(refcnt_DoubleColor);

	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
			try {
			WDoubleColor DColor (CLSID_DoubleColor);	// throws hr

				ebSetObject (lpArgs, 0, (DWORD)DColor.detach());

			} catch (HRESULT) {
				TRACE("Couldn't create DoubleColor object");
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

// ----------------------------------------------------------------------------
// DoubleColor_RGB_propget
// ----------------------------------------------------------------------------
void DoubleColor_RGB_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(DoubleColor_RGB_propget);

long lValue = DCOLOR_BLACK;
WDoubleColor DColor ((IDoubleColor *)ebGetObject (lpArgs, 1));

	DColor -> get_RGB (&lValue);
	ebSetLong (lpArgs, 0, lValue);
}

// ----------------------------------------------------------------------------
// DoubleColor_RGB_propset
// ----------------------------------------------------------------------------
void DoubleColor_RGB_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(DoubleColor_RGB_propset);

WDoubleColor DColor ((IDoubleColor *)ebGetObject (lpArgs, 1));
long lValue = ebGetLong (lpArgs, 2);

	DColor -> put_RGB (lValue);
}

// ----------------------------------------------------------------------------
// DoubleColor_Red_propget
// ----------------------------------------------------------------------------
void DoubleColor_Red_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(DoubleColor_Red_propget);

double dValue = 0.0;
WDoubleColor DColor ((IDoubleColor *)ebGetObject (lpArgs, 1));

	DColor -> get_Red (&dValue);
	ebSetDouble (lpArgs, 0, dValue);
}

// ----------------------------------------------------------------------------
// DoubleColor_Green_propget
// ----------------------------------------------------------------------------
void DoubleColor_Green_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(DoubleColor_Green_propget);

double dValue = 0.0;
WDoubleColor DColor ((IDoubleColor *)ebGetObject (lpArgs, 1));

	DColor -> get_Green (&dValue);
	ebSetDouble (lpArgs, 0, dValue);
}

// ----------------------------------------------------------------------------
// DoubleColor_Blue_propget
// ----------------------------------------------------------------------------
void DoubleColor_Blue_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(DoubleColor_Blue_propget);

double dValue = 0.0;
WDoubleColor DColor ((IDoubleColor *)ebGetObject (lpArgs, 1));

	DColor -> get_Blue (&dValue);
	ebSetDouble (lpArgs, 0, dValue);
}

// ----------------------------------------------------------------------------
// DoubleColor_Hue_propget
// ----------------------------------------------------------------------------
void DoubleColor_Hue_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(DoubleColor_Hue_propget);

double dValue = 0.0;
WDoubleColor DColor ((IDoubleColor *)ebGetObject (lpArgs, 1));

	DColor -> get_Hue (&dValue);
	ebSetDouble (lpArgs, 0, dValue);
}

// ----------------------------------------------------------------------------
// DoubleColor_Saturation_propget
// ----------------------------------------------------------------------------
void DoubleColor_Saturation_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(DoubleColor_Saturation_propget);

double dValue = 0.0;
WDoubleColor DColor ((IDoubleColor *)ebGetObject (lpArgs, 1));

	DColor -> get_Saturation (&dValue);
	ebSetDouble (lpArgs, 0, dValue);
}

// ----------------------------------------------------------------------------
// DoubleColor_Brightness_propget
// ----------------------------------------------------------------------------
void DoubleColor_Brightness_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(DoubleColor_Brightness_propget);

double dValue = 0.0;
WDoubleColor DColor ((IDoubleColor *)ebGetObject (lpArgs, 1));

	DColor -> get_Brightness (&dValue);
	ebSetDouble (lpArgs, 0, dValue);
}

// ----------------------------------------------------------------------------
// DoubleColor_Red_propset
// ----------------------------------------------------------------------------
void DoubleColor_Red_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(DoubleColor_Red_propset);

WDoubleColor DColor ((IDoubleColor *)ebGetObject (lpArgs, 1));
double dValue = ebGetDouble (lpArgs, 2);

	DColor -> put_Red (dValue);
}

// ----------------------------------------------------------------------------
// DoubleColor_Green_propset
// ----------------------------------------------------------------------------
void DoubleColor_Green_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(DoubleColor_Green_propset);

WDoubleColor DColor ((IDoubleColor *)ebGetObject (lpArgs, 1));
double dValue = ebGetDouble (lpArgs, 2);

	DColor -> put_Green (dValue);
}

// ----------------------------------------------------------------------------
// DoubleColor_Blue_propset
// ----------------------------------------------------------------------------
void DoubleColor_Blue_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(DoubleColor_Blue_propset);

WDoubleColor DColor ((IDoubleColor *)ebGetObject (lpArgs, 1));
double dValue = ebGetDouble (lpArgs, 2);

	DColor -> put_Blue (dValue);
}

// ----------------------------------------------------------------------------
// DoubleColor_Hue_propset
// ----------------------------------------------------------------------------
void DoubleColor_Hue_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(DoubleColor_Hue_propset);

WDoubleColor DColor ((IDoubleColor *)ebGetObject (lpArgs, 1));
double dValue = ebGetDouble (lpArgs, 2);

	DColor -> put_Hue (dValue);
}

// ----------------------------------------------------------------------------
// DoubleColor_Saturation_propset
// ----------------------------------------------------------------------------
void DoubleColor_Saturation_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(DoubleColor_Saturation_propset);

WDoubleColor DColor ((IDoubleColor *)ebGetObject (lpArgs, 1));
double dValue = ebGetDouble (lpArgs, 2);

	DColor -> put_Saturation (dValue);
}

// ----------------------------------------------------------------------------
// DoubleColor_Brightness_propset
// ----------------------------------------------------------------------------
void DoubleColor_Brightness_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(DoubleColor_Brightness_propset);

WDoubleColor DColor ((IDoubleColor *)ebGetObject (lpArgs, 1));
double dValue = ebGetDouble (lpArgs, 2);

	DColor -> put_Brightness (dValue);
}

// ----------------------------------------------------------------------------
// DoubleColor_Complement_propget
// ----------------------------------------------------------------------------
void DoubleColor_Complement_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(DoubleColor_Complement_propget);

WDoubleColor DColor ((IDoubleColor *)ebGetObject (lpArgs, 1));
WDoubleColor Result;

	if (SUCCEEDED(DColor -> get_Complement (Result.ppi())))
		ebSetObject (lpArgs, 0, (DWORD)Result.detach());
}

// ----------------------------------------------------------------------------
// DoubleColor_Saturated_propget
// ----------------------------------------------------------------------------
void DoubleColor_Saturated_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(DoubleColor_Saturated_propget);

WDoubleColor DColor ((IDoubleColor *)ebGetObject (lpArgs, 1));
WDoubleColor Result;

	if (SUCCEEDED(DColor -> get_Saturated (Result.ppi())))
		ebSetObject (lpArgs, 0, (DWORD)Result.detach());
}

// ----------------------------------------------------------------------------
// DoubleColor_Grayed_propget
// ----------------------------------------------------------------------------
void DoubleColor_Grayed_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(DoubleColor_Grayed_propget);

WDoubleColor DColor ((IDoubleColor *)ebGetObject (lpArgs, 1));
WDoubleColor Result;

	if (SUCCEEDED(DColor -> get_Grayed (Result.ppi())))
		ebSetObject (lpArgs, 0, (DWORD)Result.detach());
}

// ----------------------------------------------------------------------------
// DoubleColor_Pure_propget
// ----------------------------------------------------------------------------
void DoubleColor_Pure_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(DoubleColor_Pure_propget);

WDoubleColor DColor ((IDoubleColor *)ebGetObject (lpArgs, 1));
WDoubleColor Result;

	if (SUCCEEDED(DColor -> get_Pure (Result.ppi())))
		ebSetObject (lpArgs, 0, (DWORD)Result.detach());
}

// ----------------------------------------------------------------------------
// DoubleColor_InitRGB_command
// ----------------------------------------------------------------------------
void DoubleColor_InitRGB_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(DoubleColor_InitRGB_command);

WDoubleColor DColor ((IDoubleColor *)ebGetObject (lpArgs, 1));
double dRed = ebGetDouble (lpArgs, 2);
double dGreen = ebGetDouble (lpArgs, 3);
double dBlue = ebGetDouble (lpArgs, 4);

	DColor -> InitRGB (dRed, dGreen, dBlue);
}

// ----------------------------------------------------------------------------
// DoubleColor_InitHSB_command
// ----------------------------------------------------------------------------
void DoubleColor_InitHSB_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(DoubleColor_InitHSB_command);

WDoubleColor DColor ((IDoubleColor *)ebGetObject (lpArgs, 1));
double dHue = ebGetDouble (lpArgs, 2);
double dSat = ebGetDouble (lpArgs, 3);
double dBright = ebGetDouble (lpArgs, 4);

	DColor -> InitRGB (dHue, dSat, dBright);
}

///////////////////////////////////////////////////////////////////////////////
// ColorLookUp

// ----------------------------------------------------------------------------
// refcnt_ColorLookUp
// ----------------------------------------------------------------------------
void refcnt_ColorLookUp (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE_SYS(refcnt_ColorLookUp);

	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
			try {
			WColorLookUp LookUp (CLSID_ColorLookUp);	// throws hr

				ebSetObject (lpArgs, 0, (DWORD)LookUp.detach());

			} catch (HRESULT) {
				TRACE("Couldn't create ColorLookUp object");
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

// ----------------------------------------------------------------------------
// ColorLookUp_Init_command
// ----------------------------------------------------------------------------
void ColorLookUp_Init_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(ColorLookUp_Init_command);

WColorLookUp LookUp ((IColorLookUp *)ebGetObject (lpArgs, 1));
int iCnt = ebGetInt (lpArgs, 2);
WDoubleColor Color1 ((IDoubleColor *)ebGetObject (lpArgs, 3));
WDoubleColor Color2 ((IDoubleColor *)ebGetObject (lpArgs, 4));
CComVariant vColor3 = MakeVARIANT (hThread, iNumArgs, lpArgs, 5);

	LookUp -> Init (iCnt, Color1, Color2, vColor3);
}

// ----------------------------------------------------------------------------
// ColorLookUp_GetColor_function
// ----------------------------------------------------------------------------
void ColorLookUp_GetColor_function (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(ColorLookUp_GetColor_function);

WColorLookUp LookUp ((IColorLookUp *)ebGetObject (lpArgs, 1));
int iIndex = ebGetInt (lpArgs, 2);
WDoubleColor Color;
HRESULT hr = LookUp -> get_Color (iIndex, Color.ppi());

	if (SUCCEEDED(hr))
		ebSetObject (lpArgs, 0, (DWORD)Color.detach());
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

