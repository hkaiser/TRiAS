///////////////////////////////////////////////////////////////////////////////
// VisInfoExt.cpp: VisInfo support

#include "precomp.hxx"

#include <visinfo.h>

#include <vinfomfc.h>			// RGB<-->HSB support
#include <rgb_hsb.hxx>

#include "jumptab.h"
#include "olebsext.hxx"			// function  prototypes

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// benötige Interfaces
DefineSmartInterface(Dispatch);				// WDispatch

DefineSmartInterface2(DVisInfo, IID_DVisInfo);			// WDVisInfo
DefineSmartInterface2(DPointVisInfo, IID_DPointVisInfo);	// WDPointVisInfo
DefineSmartInterface2(DLineVisInfo, IID_DLineVisInfo);	// WDLineVisInfo
DefineSmartInterface2(DAreaVisInfo, IID_DAreaVisInfo);	// WDAreaVisInfo
DefineSmartInterface2(DTextVisInfo, IID_DTextVisInfo);	// WDTextVisInfo

///////////////////////////////////////////////////////////////////////////////
// globale Daten/Funktionen
extern int g_fDebugScript;

bool isTypeMismatch (ebHTHREAD hThread, ebARGS lpArgs, int iRTTI, bool fCmpMainOnly = true);
CComVariant MakeVARIANT (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs, int iArg);

///////////////////////////////////////////////////////////////////////////////
// VisualisierungsInfo

// ----------------------------------------------------------------------------
// refcnt_PointVisInfo
// ----------------------------------------------------------------------------
void refcnt_PointVisInfo (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE_SYS(refcnt_PointVisInfo);

	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
			ebSetObject (lpArgs, 0, NULL);		// für alle Fälle

		WDPointVisInfo PointVI;
		HRESULT hr = CoCreateInstance (CLSID_PointVisInfo, NULL, CLSCTX_INPROC_SERVER,
									   IID_DPointVisInfo, PointVI.ppv());

		// in TRiAS-Objekthierarchie einbinden
			{
			WDispatch Disp;

				hr = ((OLE2AutoExtension *)g_pTE) -> App() -> GetDispatchIF (Disp.ppi());
				if (SUCCEEDED(hr)) {
					hr = PointVI -> put_Application (Disp);
					hr = PointVI -> put_Parent (Disp);
				}
				if (FAILED(hr)) return;
			}
			ebSetObject (lpArgs, 0, (DWORD)PointVI.detach());
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
// refcnt_LineVisInfo
// ----------------------------------------------------------------------------
void refcnt_LineVisInfo (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE_SYS(refcnt_ToolBar);

	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
			ebSetObject (lpArgs, 0, NULL);		// für alle Fälle

		WDLineVisInfo LineVI;
		HRESULT hr = CoCreateInstance (CLSID_LineVisInfo, NULL, CLSCTX_INPROC_SERVER,
									   IID_DLineVisInfo, LineVI.ppv());

		// in TRiAS-Objekthierarchie einbinden
			{
			WDispatch Disp;

				hr = ((OLE2AutoExtension *)g_pTE) -> App() -> GetDispatchIF (Disp.ppi());
				if (SUCCEEDED(hr)) {
					hr = LineVI -> put_Application (Disp);
					hr = LineVI -> put_Parent (Disp);
				}
				if (FAILED(hr)) return;
			}
			ebSetObject (lpArgs, 0, (DWORD)LineVI.detach());
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
// refcnt_AreaVisInfo
// ----------------------------------------------------------------------------
void refcnt_AreaVisInfo (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE_SYS(refcnt_ToolBar);

	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
			ebSetObject (lpArgs, 0, NULL);		// für alle Fälle

		WDAreaVisInfo AreaVI;
		HRESULT hr = CoCreateInstance (CLSID_AreaVisInfo, NULL, CLSCTX_INPROC_SERVER,
									   IID_DAreaVisInfo, AreaVI.ppv());

		// in TRiAS-Objekthierarchie einbinden
			{
			WDispatch Disp;

				hr = ((OLE2AutoExtension *)g_pTE) -> App() -> GetDispatchIF (Disp.ppi());
				if (SUCCEEDED(hr)) {
					hr = AreaVI -> put_Application (Disp);
					hr = AreaVI -> put_Parent (Disp);
				}
				if (FAILED(hr)) return;
			}
			ebSetObject (lpArgs, 0, (DWORD)AreaVI.detach());
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
// refcnt_TextVisInfo
// ----------------------------------------------------------------------------
void refcnt_TextVisInfo (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE_SYS(refcnt_ToolBar);

	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
			ebSetObject (lpArgs, 0, NULL);		// für alle Fälle

		WDTextVisInfo TextVI;
		HRESULT hr = CoCreateInstance (CLSID_TextVisInfo, NULL, CLSCTX_INPROC_SERVER,
									   IID_DTextVisInfo, TextVI.ppv());

		// in TRiAS-Objekthierarchie einbinden
			{
			WDispatch Disp;

				hr = ((OLE2AutoExtension *)g_pTE) -> App() -> GetDispatchIF (Disp.ppi());
				if (SUCCEEDED(hr)) {
					hr = TextVI -> put_Application (Disp);
					hr = TextVI -> put_Parent (Disp);
				}
				if (FAILED(hr)) return;
			}
			ebSetObject (lpArgs, 0, (DWORD)TextVI.detach());
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
// Style_VisInfo_propget
// ----------------------------------------------------------------------------
void Style_VisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Style_VisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_VisInfo))
		return;

int iStyle = 0;

	((DVisInfo *)ebGetObject (lpArgs, 1)) -> get_Style (&iStyle);
	ebSetLong (lpArgs, 0, iStyle);
}

// ----------------------------------------------------------------------------
// Style_VisInfo_propset
// ----------------------------------------------------------------------------
void Style_VisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Style_VisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_VisInfo))
		return;

	((DVisInfo *)ebGetObject (lpArgs, 1)) -> put_Style (ebGetLong (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// Priority_VisInfo_propget
// ----------------------------------------------------------------------------
void Priority_VisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Priority_VisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_VisInfo))
		return;

int iPriority = 0;

	((DVisInfo *)ebGetObject (lpArgs, 1)) -> get_Priority (&iPriority);
	ebSetLong (lpArgs, 0, iPriority);
}

// ----------------------------------------------------------------------------
// Priority_VisInfo_propset
// ----------------------------------------------------------------------------
void Priority_VisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Priority_VisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_VisInfo))
		return;

	((DVisInfo *)ebGetObject (lpArgs, 1)) -> put_Priority (ebGetLong (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// Name_VisInfo_propget
// ----------------------------------------------------------------------------
void Name_VisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Name_VisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_VisInfo))
		return;

BSTR bstrName = 0;

	USES_CONVERSION;
	ebFreeString (hThread, ebGetString (lpArgs, 0));
	if (SUCCEEDED(((DVisInfo *)ebGetObject (lpArgs, 1)) -> get_Name (CLEARED(&bstrName)))) {
		ebSetString (lpArgs, 0, ebCreateString (hThread, OLE2A(bstrName)));
		SysFreeString (bstrName);
	} else
		ebSetString (lpArgs, 0, 0);
}

// ----------------------------------------------------------------------------
// Name_VisInfo_propset
// ----------------------------------------------------------------------------
void Name_VisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Name_VisInfo_propset);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_VisInfo))
		return;

	USES_CONVERSION;
	 
ebHSUB hStr = ebGetString (lpArgs, 2);
BSTR bstrName = SysAllocString (A2OLE(ebLockString (hThread, hStr)));

	ebUnlockString (hThread, hStr);
	if (NULL != bstrName) {
		((DVisInfo *)ebGetObject (lpArgs, 1)) -> put_Name (bstrName);
		SysFreeString (bstrName);
	}
}

// ----------------------------------------------------------------------------
// MainColor_VisInfo_propget
// ----------------------------------------------------------------------------
void MainColor_VisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(MainColor_VisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_VisInfo))
		return;

LONG crMain = 0;

	((DVisInfo *)ebGetObject (lpArgs, 1)) -> get_MainColor (&crMain);
	ebSetLong (lpArgs, 0, crMain);
}

// ----------------------------------------------------------------------------
// MainColor_VisInfo_propset
// ----------------------------------------------------------------------------
void MainColor_VisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(MainColor_VisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_VisInfo))
		return;

	((DVisInfo *)ebGetObject (lpArgs, 1)) -> put_MainColor (ebGetLong (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// Changed_VisInfo_propget
// ----------------------------------------------------------------------------
void Changed_VisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Changed_VisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_VisInfo))
		return;

int fChanged = 0;

	((DVisInfo *)ebGetObject (lpArgs, 1)) -> get_Changed (&fChanged);
	ebSetInt (lpArgs, 0, fChanged);
}

// ----------------------------------------------------------------------------
// Changed_VisInfo_propset
// ----------------------------------------------------------------------------
void Changed_VisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Changed_VisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_VisInfo))
		return;

	((DVisInfo *)ebGetObject (lpArgs, 1)) -> put_Changed (ebGetInt (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// Visible_VisInfo_propget
// ----------------------------------------------------------------------------
void Visible_VisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Visible_VisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_VisInfo))
		return;

int fChanged = 0;

	((DVisInfo *)ebGetObject (lpArgs, 1)) -> get_Visible (&fChanged);
	ebSetInt (lpArgs, 0, fChanged);
}

// ----------------------------------------------------------------------------
// Visible_VisInfo_propset
// ----------------------------------------------------------------------------
void Visible_VisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Visible_VisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_VisInfo))
		return;

	((DVisInfo *)ebGetObject (lpArgs, 1)) -> put_Visible (ebGetInt (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// Locatable_VisInfo_propget
// ----------------------------------------------------------------------------
void Locatable_VisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Locatable_VisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_VisInfo))
		return;

int fChanged = 0;

	((DVisInfo *)ebGetObject (lpArgs, 1)) -> get_Locatable (&fChanged);
	ebSetInt (lpArgs, 0, fChanged);
}

// ----------------------------------------------------------------------------
// Locatable_VisInfo_propset
// ----------------------------------------------------------------------------
void Locatable_VisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Locatable_VisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_VisInfo))
		return;

	((DVisInfo *)ebGetObject (lpArgs, 1)) -> put_Locatable (ebGetInt (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// SizeX_PointVisInfo_propget
// ----------------------------------------------------------------------------
void SizeX_PointVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(SizeX_PointVisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_PointVisInfo, false))
		return;

int iSizeX = 0;

	((DPointVisInfo *)ebGetObject (lpArgs, 1)) -> get_SizeX (&iSizeX);
	ebSetLong (lpArgs, 0, iSizeX);
}

// ----------------------------------------------------------------------------
// SizeX_PointVisInfo_propset
// ----------------------------------------------------------------------------
void SizeX_PointVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(SizeX_PointVisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_PointVisInfo, false))
		return;

	((DPointVisInfo *)ebGetObject (lpArgs, 1)) -> put_SizeX (ebGetLong (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// SizeY_PointVisInfo_propget
// ----------------------------------------------------------------------------
void SizeY_PointVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(SizeY_PointVisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_PointVisInfo, false))
		return;

int iSizeY = 0;

	((DPointVisInfo *)ebGetObject (lpArgs, 1)) -> get_SizeY (&iSizeY);
	ebSetLong (lpArgs, 0, iSizeY);
}

// ----------------------------------------------------------------------------
// SizeY_PointVisInfo_propset
// ----------------------------------------------------------------------------
void SizeY_PointVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(SizeY_PointVisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_PointVisInfo, false))
		return;

	((DPointVisInfo *)ebGetObject (lpArgs, 1)) -> put_SizeY (ebGetLong (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// Rotate_PointVisInfo_propget
// ----------------------------------------------------------------------------
void Rotate_PointVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Rotate_PointVisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_PointVisInfo, false))
		return;

int iRotate = 0;

	((DPointVisInfo *)ebGetObject (lpArgs, 1)) -> get_Rotate (&iRotate);
	ebSetLong (lpArgs, 0, iRotate);
}

// ----------------------------------------------------------------------------
// Rotate_PointVisInfo_propset
// ----------------------------------------------------------------------------
void Rotate_PointVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Rotate_PointVisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_PointVisInfo, false))
		return;

	((DPointVisInfo *)ebGetObject (lpArgs, 1)) -> put_Rotate (ebGetLong (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// BkColor_PointVisInfo_propget
// ----------------------------------------------------------------------------
void BkColor_PointVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(BkColor_PointVisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_PointVisInfo, false))
		return;

LONG crBk = 0;

	((DPointVisInfo *)ebGetObject (lpArgs, 1)) -> get_BkColor (&crBk);
	ebSetLong (lpArgs, 0, crBk);
}

// ----------------------------------------------------------------------------
// BkColor_PointVisInfo_propset
// ----------------------------------------------------------------------------
void BkColor_PointVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(BkColor_PointVisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_PointVisInfo, false))
		return;

	((DPointVisInfo *)ebGetObject (lpArgs, 1)) -> put_BkColor (ebGetLong (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// Width_LineVisInfo_propget
// ----------------------------------------------------------------------------
void Width_LineVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Width_LineVisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_LineVisInfo, false))
		return;

int iWidth = 0;

	((DLineVisInfo *)ebGetObject (lpArgs, 1)) -> get_Width (&iWidth);
	ebSetLong (lpArgs, 0, iWidth);
}

// ----------------------------------------------------------------------------
// Width_LineVisInfo_propset
// ----------------------------------------------------------------------------
void Width_LineVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Width_LineVisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_LineVisInfo, false))
		return;

	((DLineVisInfo *)ebGetObject (lpArgs, 1)) -> put_Width (ebGetLong (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// Width_AreaVisInfo_propget
// ----------------------------------------------------------------------------
void Width_AreaVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Width_AreaVisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_AreaVisInfo, false))
		return;

int iWidth = 0;

	((DAreaVisInfo *)ebGetObject (lpArgs, 1)) -> get_Width (&iWidth);
	ebSetLong (lpArgs, 0, iWidth);
}

// ----------------------------------------------------------------------------
// Width_AreaVisInfo_propset
// ----------------------------------------------------------------------------
void Width_AreaVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Width_AreaVisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_AreaVisInfo, false))
		return;

	((DAreaVisInfo *)ebGetObject (lpArgs, 1)) -> put_Width (ebGetLong (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// Opaque_AreaVisInfo_propget
// ----------------------------------------------------------------------------
void Opaque_AreaVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Opaque_AreaVisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_AreaVisInfo, false))
		return;

int fOpaque = false;

	((DAreaVisInfo *)ebGetObject (lpArgs, 1)) -> get_Opaque (&fOpaque);
	ebSetBool (lpArgs, 0, fOpaque);
}

// ----------------------------------------------------------------------------
// Opaque_AreaVisInfo_propset
// ----------------------------------------------------------------------------
void Opaque_AreaVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Opaque_AreaVisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_AreaVisInfo, false))
		return;

	((DAreaVisInfo *)ebGetObject (lpArgs, 1)) -> put_Opaque (ebGetBool (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// BkContour_AreaVisInfo_propget
// ----------------------------------------------------------------------------
void BkContour_AreaVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(BkContour_AreaVisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_AreaVisInfo, false))
		return;

int fBkContour = false;

	((DAreaVisInfo *)ebGetObject (lpArgs, 1)) -> get_BkContour (&fBkContour);
	ebSetBool (lpArgs, 0, fBkContour);
}

// ----------------------------------------------------------------------------
// BkContour_AreaVisInfo_propset
// ----------------------------------------------------------------------------
void BkContour_AreaVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(BkContour_AreaVisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_AreaVisInfo, false))
		return;

	((DAreaVisInfo *)ebGetObject (lpArgs, 1)) -> put_BkContour (ebGetBool (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// BkColor_AreaVisInfo_propget
// ----------------------------------------------------------------------------
void BkColor_AreaVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(BkColor_AreaVisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_AreaVisInfo, false))
		return;

LONG crBk = 0;

	((DAreaVisInfo *)ebGetObject (lpArgs, 1)) -> get_BkColor (&crBk);
	ebSetLong (lpArgs, 0, crBk);
}

// ----------------------------------------------------------------------------
// BkColor_AreaVisInfo_propset
// ----------------------------------------------------------------------------
void BkColor_AreaVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(BkColor_AreaVisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_AreaVisInfo, false))
		return;

	((DAreaVisInfo *)ebGetObject (lpArgs, 1)) -> put_BkColor (ebGetLong (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// SizeX_TextVisInfo_propget
// ----------------------------------------------------------------------------
void SizeX_TextVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(SizeX_TextVisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_TextVisInfo, false))
		return;

int iSizeX = 0;

	((DTextVisInfo *)ebGetObject (lpArgs, 1)) -> get_SizeX (&iSizeX);
	ebSetLong (lpArgs, 0, iSizeX);
}

// ----------------------------------------------------------------------------
// SizeX_TextVisInfo_propset
// ----------------------------------------------------------------------------
void SizeX_TextVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(SizeX_TextVisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_TextVisInfo, false))
		return;

	((DTextVisInfo *)ebGetObject (lpArgs, 1)) -> put_SizeX (ebGetLong (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// SizeY_TextVisInfo_propget
// ----------------------------------------------------------------------------
void SizeY_TextVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(SizeY_TextVisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_TextVisInfo, false))
		return;

int iSizeY = 0;

	((DTextVisInfo *)ebGetObject (lpArgs, 1)) -> get_SizeY (&iSizeY);
	ebSetLong (lpArgs, 0, iSizeY);
}

// ----------------------------------------------------------------------------
// SizeY_TextVisInfo_propset
// ----------------------------------------------------------------------------
void SizeY_TextVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(SizeY_TextVisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_TextVisInfo, false))
		return;

	((DTextVisInfo *)ebGetObject (lpArgs, 1)) -> put_SizeY (ebGetLong (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// Bold_TextVisInfo_propget
// ----------------------------------------------------------------------------
void Bold_TextVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Bold_TextVisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_TextVisInfo, false))
		return;

int fBold = false;

	((DTextVisInfo *)ebGetObject (lpArgs, 1)) -> get_Bold (&fBold);
	ebSetBool (lpArgs, 0, fBold);
}

// ----------------------------------------------------------------------------
// Bold_TextVisInfo_propset
// ----------------------------------------------------------------------------
void Bold_TextVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Bold_TextVisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_TextVisInfo, false))
		return;

	((DTextVisInfo *)ebGetObject (lpArgs, 1)) -> put_Bold (ebGetBool (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// Italic_TextVisInfo_propget
// ----------------------------------------------------------------------------
void Italic_TextVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Italic_TextVisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_TextVisInfo, false))
		return;

int fItalic = false;

	((DTextVisInfo *)ebGetObject (lpArgs, 1)) -> get_Italic (&fItalic);
	ebSetBool (lpArgs, 0, fItalic);
}

// ----------------------------------------------------------------------------
// Italic_TextVisInfo_propset
// ----------------------------------------------------------------------------
void Italic_TextVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Italic_TextVisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_TextVisInfo, false))
		return;

	((DTextVisInfo *)ebGetObject (lpArgs, 1)) -> put_Italic (ebGetBool (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// Underline_TextVisInfo_propget
// ----------------------------------------------------------------------------
void Underline_TextVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Underline_TextVisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_TextVisInfo, false))
		return;

int fUnderline = false;

	((DTextVisInfo *)ebGetObject (lpArgs, 1)) -> get_Underline (&fUnderline);
	ebSetBool (lpArgs, 0, fUnderline);
}

// ----------------------------------------------------------------------------
// Underline_TextVisInfo_propset
// ----------------------------------------------------------------------------
void Underline_TextVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Underline_TextVisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_TextVisInfo, false))
		return;

	((DTextVisInfo *)ebGetObject (lpArgs, 1)) -> put_Underline (ebGetBool (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// StrikeThrough_TextVisInfo_propget
// ----------------------------------------------------------------------------
void StrikeThrough_TextVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(StrikeThrough_TextVisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_TextVisInfo, false))
		return;

int fStrike = false;

	((DTextVisInfo *)ebGetObject (lpArgs, 1)) -> get_StrikeThrough (&fStrike);
	ebSetBool (lpArgs, 0, fStrike);
}

// ----------------------------------------------------------------------------
// StrikeThrough_TextVisInfo_propset
// ----------------------------------------------------------------------------
void StrikeThrough_TextVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(StrikeThrough_TextVisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_TextVisInfo, false))
		return;

	((DTextVisInfo *)ebGetObject (lpArgs, 1)) -> put_StrikeThrough (ebGetBool (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// AlignStyle_TextVisInfo_propget
// ----------------------------------------------------------------------------
void AlignStyle_TextVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(AlignStyle_TextVisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_TextVisInfo, false))
		return;

ALIGNSTYLE rgAlign = ALIGNSTYLE_Left;

	((DTextVisInfo *)ebGetObject (lpArgs, 1)) -> get_AlignStyle (&rgAlign);
	ebSetInt (lpArgs, 0, rgAlign);
}

// ----------------------------------------------------------------------------
// AlignStyle_TextVisInfo_propset
// ----------------------------------------------------------------------------
void AlignStyle_TextVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(AlignStyle_TextVisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_TextVisInfo, false))
		return;

	((DTextVisInfo *)ebGetObject (lpArgs, 1)) -> put_AlignStyle ((ALIGNSTYLE)ebGetInt (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// FrameStyle_TextVisInfo_propget
// ----------------------------------------------------------------------------
void FrameStyle_TextVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(FrameStyle_TextVisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_TextVisInfo, false))
		return;

FRAMESTYLE rgFrame = FRAMESTYLE_NoFrame;

	((DTextVisInfo *)ebGetObject (lpArgs, 1)) -> get_FrameStyle (&rgFrame);
	ebSetInt (lpArgs, 0, rgFrame);
}

// ----------------------------------------------------------------------------
// FrameStyle_TextVisInfo_propset
// ----------------------------------------------------------------------------
void FrameStyle_TextVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(FrameStyle_TextVisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_TextVisInfo, false))
		return;

	((DTextVisInfo *)ebGetObject (lpArgs, 1)) -> put_FrameStyle ((FRAMESTYLE)ebGetInt (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// Rotate_TextVisInfo_propget
// ----------------------------------------------------------------------------
void Rotate_TextVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Rotate_TextVisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_TextVisInfo, false))
		return;

int iRotate = 0;

	((DTextVisInfo *)ebGetObject (lpArgs, 1)) -> get_Rotate (&iRotate);
	ebSetLong (lpArgs, 0, iRotate);
}

// ----------------------------------------------------------------------------
// Rotate_TextVisInfo_propset
// ----------------------------------------------------------------------------
void Rotate_TextVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Rotate_TextVisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_TextVisInfo, false))
		return;

	((DTextVisInfo *)ebGetObject (lpArgs, 1)) -> put_Rotate (ebGetLong (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// Slant_TextVisInfo_propget
// ----------------------------------------------------------------------------
void Slant_TextVisInfo_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Slant_TextVisInfo_propget);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_TextVisInfo, false))
		return;

int iSlant = 0;

	((DTextVisInfo *)ebGetObject (lpArgs, 1)) -> get_Slant (&iSlant);
	ebSetLong (lpArgs, 0, iSlant);
}

// ----------------------------------------------------------------------------
// Slant_TextVisInfo_propset
// ----------------------------------------------------------------------------
void Slant_TextVisInfo_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Slant_TextVisInfo_propset);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_TextVisInfo, false))
		return;

	((DTextVisInfo *)ebGetObject (lpArgs, 1)) -> put_Slant (ebGetLong (lpArgs, 2));
}

// ----------------------------------------------------------------------------
// RGB_protofunc
// ----------------------------------------------------------------------------
void RGB_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(RGB_protofunc);
	ebSetLong (lpArgs, 0, RGB(ebGetInt (lpArgs, 1), ebGetInt (lpArgs, 2), ebGetInt (lpArgs, 3)));
}

// ----------------------------------------------------------------------------
// Red_protofunc
// ----------------------------------------------------------------------------
void Red_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Red_protofunc);
	ebSetInt (lpArgs, 0, GetRValue (ebGetLong(lpArgs, 1)));
}

// ----------------------------------------------------------------------------
// Green_protofunc
// ----------------------------------------------------------------------------
void Green_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Green_protofunc);
	ebSetInt (lpArgs, 0, GetGValue (ebGetLong(lpArgs, 1)));
}

// ----------------------------------------------------------------------------
// Blue_protofunc
// ----------------------------------------------------------------------------
void Blue_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Blue_protofunc);
	ebSetInt (lpArgs, 0, GetBValue (ebGetLong(lpArgs, 1)));
}

// ----------------------------------------------------------------------------
// HSB_protofunc
// ----------------------------------------------------------------------------
void HSB_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(HSB_protofunc);

	ebSetLong (lpArgs, 0, (DWORD &)HSBtoRGB (
			ebGetInt(lpArgs, 1), ebGetInt(lpArgs, 2), ebGetInt(lpArgs, 3)));
}

// ----------------------------------------------------------------------------
// Hue_protofunc
// ----------------------------------------------------------------------------
void Hue_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Hue_protofunc);

DWORD dwColor = ebGetLong (lpArgs, 1);

	ebSetInt (lpArgs, 0, GetHValue (RGBtoHSB ((Color &)dwColor)));
}

// ----------------------------------------------------------------------------
// Saturation_protofunc
// ----------------------------------------------------------------------------
void Saturation_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Saturation_protofunc);

DWORD dwColor = ebGetLong (lpArgs, 1);

	ebSetInt (lpArgs, 0, GetSValue (RGBtoHSB ((Color &)dwColor)));
}

// ----------------------------------------------------------------------------
// Brightness_protofunc
// ----------------------------------------------------------------------------
void Brightness_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Brightness_protofunc);

DWORD dwColor = ebGetLong (lpArgs, 1);

	ebSetInt (lpArgs, 0, GetVValue (RGBtoHSB ((Color &)dwColor)));
}

// ----------------------------------------------------------------------------
// GetPointVisInfo_GeoObject_func
// ----------------------------------------------------------------------------
void GetPointVisInfo_GeoObject_func (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(GetPointVisInfo_GeoObject_func);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;
		
WDVisInfo VisInfo;
CComVariant vView (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> GetVisInfo (vView, VisInfo.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) {
		try {
		WDPointVisInfo PVis (VisInfo);		// throws hr
	
			ebSetObject (lpArgs, 0, (DWORD)PVis.detach());
		} catch (_com_error&) {
			TRACE("Couldn't QI DPointVisInfo from IDispatch\n");
		}
	}
}

// ----------------------------------------------------------------------------
// GetLineVisInfo_GeoObject_func
// ----------------------------------------------------------------------------
void GetLineVisInfo_GeoObject_func (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(GetLineVisInfo_GeoObject_func);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;
		
WDVisInfo VisInfo;
CComVariant vView (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> GetVisInfo (vView, VisInfo.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) {
		try {
		WDLineVisInfo LVis (VisInfo);		// throws hr
	
			ebSetObject (lpArgs, 0, (DWORD)LVis.detach());
		} catch (_com_error&) {
			TRACE("Couldn't QI DLineVisInfo from IDispatch\n");
		}
	}
}

// ----------------------------------------------------------------------------
// GetAreaVisInfo_GeoObject_func
// ----------------------------------------------------------------------------
void GetAreaVisInfo_GeoObject_func (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(GetAreaVisInfo_GeoObject_func);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;
		
WDVisInfo VisInfo;
CComVariant vView (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> GetVisInfo (vView, VisInfo.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) {
		try {
		WDAreaVisInfo AVis (VisInfo);		// throws hr
	
			ebSetObject (lpArgs, 0, (DWORD)AVis.detach());
		} catch (_com_error&) {
			TRACE("Couldn't QI DAreaVisInfo from IDispatch\n");
		}
	}
}

// ----------------------------------------------------------------------------
// GetTextVisInfo_GeoObject_func
// ----------------------------------------------------------------------------
void GetTextVisInfo_GeoObject_func (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(GetTextVisInfo_GeoObject_func);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;
		
WDVisInfo VisInfo;
CComVariant vView (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
HRESULT hr = ((DGeoObject *)ebGetObject (lpArgs, 1)) -> GetVisInfo (vView, VisInfo.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) {
		try {
		WDTextVisInfo TVis (VisInfo);		// throws hr
	
			ebSetObject (lpArgs, 0, (DWORD)TVis.detach());
		} catch (_com_error&) {
			TRACE("Couldn't QI DTextVisInfo from IDispatch\n");
		}
	}
}

// ----------------------------------------------------------------------------
// SetVisInfo_GeoObject_cmd
// ----------------------------------------------------------------------------
void SetVisInfo_GeoObject_cmd (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(SetPointVisInfo_GeoObject_cmd);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;
		
WDVisInfo Vis ((DVisInfo *)ebGetObject (lpArgs, 2));
CComVariant vView (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));

	((_DGeoObject *)ebGetObject (lpArgs, 1)) -> SetVisInfo (Vis, vView);
}

// ----------------------------------------------------------------------------
// ResetVisInfo_GeoObject_cmd
// ----------------------------------------------------------------------------
void ResetVisInfo_GeoObject_cmd (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(ResetVisInfo_GeoObject_cmd);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoObject))
		return;
		
CComVariant vView (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));

	((_DGeoObject *)ebGetObject (lpArgs, 1)) -> ResetVisInfo (vView);
}

// ----------------------------------------------------------------------------
// GetPointVisInfo_GeoClass_func
// ----------------------------------------------------------------------------
void GetPointVisInfo_GeoClass_func (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(GetPointVisInfo_GeoClass_func);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;
		
WDVisInfo VisInfo;
CComVariant vView (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
HRESULT hr = ((DGeoClass *)ebGetObject (lpArgs, 1)) -> GetVisInfo (OBJECTTYPE_Point, vView, VisInfo.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) {
		try {
		WDPointVisInfo PVis (VisInfo);		// throws hr
	
			ebSetObject (lpArgs, 0, (DWORD)PVis.detach());
		} catch (_com_error&) {
			TRACE("Couldn't QI DPointVisInfo from IDispatch\n");
		}
	}
}

// ----------------------------------------------------------------------------
// GetLineVisInfo_GeoClass_func
// ----------------------------------------------------------------------------
void GetLineVisInfo_GeoClass_func (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(GetLineVisInfo_GeoClass_func);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;
		
WDVisInfo VisInfo;
CComVariant vView (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
HRESULT hr = ((DGeoClass *)ebGetObject (lpArgs, 1)) -> GetVisInfo (OBJECTTYPE_Line, vView, VisInfo.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) {
		try {
		WDLineVisInfo LVis (VisInfo);		// throws hr
	
			ebSetObject (lpArgs, 0, (DWORD)LVis.detach());
		} catch (_com_error&) {
			TRACE("Couldn't QI DLineVisInfo from IDispatch\n");
		}
	}
}

// ----------------------------------------------------------------------------
// GetAreaVisInfo_GeoClass_func
// ----------------------------------------------------------------------------
void GetAreaVisInfo_GeoClass_func (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(GetAreaVisInfo_GeoClass_func);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;
		
WDVisInfo VisInfo;
CComVariant vView (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
HRESULT hr = ((DGeoClass *)ebGetObject (lpArgs, 1)) -> GetVisInfo (OBJECTTYPE_Area, vView, VisInfo.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) {
		try {
		WDAreaVisInfo AVis (VisInfo);		// throws hr
	
			ebSetObject (lpArgs, 0, (DWORD)AVis.detach());
		} catch (_com_error&) {
			TRACE("Couldn't QI DAreaVisInfo from IDispatch\n");
		}
	}
}

// ----------------------------------------------------------------------------
// GetTextVisInfo_GeoClass_func
// ----------------------------------------------------------------------------
void GetTextVisInfo_GeoClass_func (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(GetTextVisInfo_GeoClass_func);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;
		
WDVisInfo VisInfo;
CComVariant vView (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
HRESULT hr = ((DGeoClass *)ebGetObject (lpArgs, 1)) -> GetVisInfo (OBJECTTYPE_Text, vView, VisInfo.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) {
		try {
		WDTextVisInfo TVis (VisInfo);		// throws hr
	
			ebSetObject (lpArgs, 0, (DWORD)TVis.detach());
		} catch (_com_error&) {
			TRACE("Couldn't QI DTextVisInfo from IDispatch\n");
		}
	}
}

// ----------------------------------------------------------------------------
// SetPointVisInfo_GeoClass_cmd
// ----------------------------------------------------------------------------
void SetVisInfo_GeoClass_cmd (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(SetVisInfo_GeoClass_cmd);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;
		
WDVisInfo Vis ((DVisInfo *)ebGetObject (lpArgs, 2));
CComVariant vView (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));

	((_DGeoClass *)ebGetObject (lpArgs, 1)) -> SetVisInfo (Vis, vView);
}

// ----------------------------------------------------------------------------
// ResetVisInfo_GeoClass_cmd
// ----------------------------------------------------------------------------
void ResetVisInfo_GeoClass_cmd (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(ResetVisInfo_GeoClass_cmd);
 
// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_GeoClass))
		return;

CComVariant vView (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));

	((_DGeoClass *)ebGetObject (lpArgs, 1)) -> ResetVisInfo ((OBJECTTYPE)ebGetInt(lpArgs, 2), vView);
}

