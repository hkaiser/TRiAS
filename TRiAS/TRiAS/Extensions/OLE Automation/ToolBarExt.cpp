///////////////////////////////////////////////////////////////////////////////
// ToolBarExt.cpp: ToolBar support

#include "precomp.hxx"

#include <toolguid.h>			// ToolBarSupport
#include <itoolbar.h>
#include <dtoolbar.h>

#include "oleautor.h"
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
DefineSmartInterface(EnumVARIANT);			// WEnumVARIANT
DefineSmartInterface(PersistStreamInit);	// WPersistStreamInit

DefineSmartInterface2(DControlToolBar, IID_DControlToolBar);	// WDControlToolBar
DefineSmartInterface2(DControlToolBars, IID_DControlToolBars);	// WDControlToolBars
DefineSmartInterface2(DControlToolBarButton, IID_DControlToolBarButton);	// WDControlToolBarButton
DefineSmartInterface2(DToolBarUIOwner, IID_DToolBarUIOwner);	// WDControlToolBarButton

///////////////////////////////////////////////////////////////////////////////
// globale Daten/Funktionen
extern int g_fDebugScript;

long g_lTBCnt = 1;		// Zähler der neuen Toolbars

bool isTypeMismatch (ebHTHREAD hThread, ebARGS lpArgs, int iRTTI, bool fCmpMainOnly = true);
CComVariant MakeVARIANT (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs, int iArg);

// ----------------------------------------------------------------------------
// refcnt_ToolBar
// ----------------------------------------------------------------------------
void refcnt_ToolBar (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE_SYS(refcnt_ToolBar);

	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
			ebSetObject (lpArgs, 0, NULL);		// für alle Fälle

		// in TRiAS-Objekthierarchie einbinden
			try {
			WDControlToolBar ToolBar;
			CString strName;

				USES_CONVERSION;
				strName.Format (IDS_NEWTOOLBARNAME, g_lTBCnt);
				InterlockedIncrement (&g_lTBCnt);

			CComVariant vStyle (DISP_E_PARAMNOTFOUND, VT_ERROR);

				THROW_FAILED_HRESULT(((OLE2AutoExtension *)g_pTE) -> AppDisp() -> AddToolBar (A2OLE(strName), vStyle, ToolBar.ppi()));
				ebSetObject (lpArgs, 0, (DWORD)ToolBar.detach());

			} catch (_com_error&) {
				return;
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
// Visible_ToolBar_propget
// ----------------------------------------------------------------------------
void Visible_ToolBar_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Visible_ToolBar_propget);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBar))
		return;

VARIANT_BOOL fVisible = false;

	((DControlToolBar *)ebGetObject (lpArgs, 1)) -> get_Visible (&fVisible);
	ebSetBool (lpArgs, 0, fVisible);
}

// ----------------------------------------------------------------------------
// Visible_ToolBar_propset
// ----------------------------------------------------------------------------
void Visible_ToolBar_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Visible_ToolBar_propset);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBar))
		return;

	((DControlToolBar *)ebGetObject (lpArgs, 1)) -> put_Visible (ebGetBool (lpArgs, 2));
	DEX_KickIdle();
}

// ----------------------------------------------------------------------------
// Name_ToolBar_propget
// ----------------------------------------------------------------------------
void Name_ToolBar_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Name_ToolBar_propget);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBar))
		return;

CComBSTR bstr;
HRESULT hr = ((DControlToolBar *)ebGetObject (lpArgs, 1)) -> get_Name (CLEARED(&bstr));

	if (FAILED(hr))	{
		ebSetString (lpArgs, 0, NULL);
		return;
	}

	USES_CONVERSION;
	ebSetString (lpArgs, 0, ebCreateString (hThread, OLE2A(bstr)));
}

// ----------------------------------------------------------------------------
// Name_ToolBar_propset
// ----------------------------------------------------------------------------
void Name_ToolBar_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Name_ToolBar_propset);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBar))
		return;

	USES_CONVERSION;

ebHSUB hStr = ebGetString (lpArgs, 2);

	if (NULL != hStr) {
	LPSTR lpstr = ebLockString (hThread, hStr);
	 
		((DControlToolBar *)ebGetObject (lpArgs, 1)) -> put_Name (A2OLE(lpstr));
		ebUnlockString (hThread, hStr);

		DEX_KickIdle();
	}
}

// ----------------------------------------------------------------------------
// DockState_ToolBar_propget
// ----------------------------------------------------------------------------
void DockState_ToolBar_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(DockState_ToolBar_propget);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBar))
		return;

DOCKSTATE ds = (DOCKSTATE)0;

	((DControlToolBar *)ebGetObject (lpArgs, 1)) -> get_DockState (&ds);
	ebSetInt (lpArgs, 0, (int)ds);
}

// ----------------------------------------------------------------------------
// DockState_ToolBar_propset
// ----------------------------------------------------------------------------
void DockState_ToolBar_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(DockState_ToolBar_propset);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBar))
		return;

	((DControlToolBar *)ebGetObject (lpArgs, 1)) -> put_DockState ((DOCKSTATE)ebGetInt (lpArgs, 2));
	DEX_KickIdle();
}

// ----------------------------------------------------------------------------
// Remove_ToolBar_command
// ----------------------------------------------------------------------------
void Remove_ToolBar_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Remove_ToolBar_command);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBar))
		return;

	((DControlToolBar *)ebGetObject (lpArgs, 1)) -> Remove();
}

// ----------------------------------------------------------------------------
// InsertButton_ToolBar_command
// ----------------------------------------------------------------------------
void InsertButton_ToolBar_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(InsertButton_ToolBar_command);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBar))
		return;

	try {
	int iIndex = ebGetInt (lpArgs, 2);
//	WDispatch Bttn ((DControlToolBarButton *)ebGetObject (lpArgs, 3));	// throws hr
	WDControlToolBarButton Bttn ((DControlToolBarButton *)ebGetObject (lpArgs, 3));
	WDToolBarUIOwner BttnOwner (Bttn);

		((DControlToolBar *)ebGetObject (lpArgs, 1)) -> InsertButton (iIndex, Bttn, BttnOwner, NULL);
		DEX_KickIdle();
	} catch (_com_error&) {
		return;
	}
}

// ----------------------------------------------------------------------------
// propget_ToolBar_Left
// ----------------------------------------------------------------------------
void propget_ToolBar_Left (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_ToolBar_Left);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBar))
		return;

long lLeft = 0;

	((DControlToolBar *)ebGetObject (lpArgs, 1)) -> get_Left (&lLeft);
	ebSetLong (lpArgs, 0, lLeft);
}

// ----------------------------------------------------------------------------
// propset_ToolBar_Left
// ----------------------------------------------------------------------------
void propset_ToolBar_Left (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_ToolBar_Left);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBar))
		return;

	((DControlToolBar *)ebGetObject (lpArgs, 1)) -> put_Left (ebGetLong(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// propget_ToolBar_Top
// ----------------------------------------------------------------------------
void propget_ToolBar_Top (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_ToolBar_Top);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBar))
		return;

long lTop = 0;

	((DControlToolBar *)ebGetObject (lpArgs, 1)) -> get_Top (&lTop);
	ebSetLong (lpArgs, 0, lTop);
}

// ----------------------------------------------------------------------------
// propset_ToolBar_Top
// ----------------------------------------------------------------------------
void propset_ToolBar_Top (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_ToolBar_Top);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBar))
		return;

	((DControlToolBar *)ebGetObject (lpArgs, 1)) -> put_Top (ebGetLong(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// propget_ToolBar_Width
// ----------------------------------------------------------------------------
void propget_ToolBar_Width (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_ToolBar_Width);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBar))
		return;

long lWidth = 0;

	((DControlToolBar *)ebGetObject (lpArgs, 1)) -> get_Width (&lWidth);
	ebSetLong (lpArgs, 0, lWidth);
}

// ----------------------------------------------------------------------------
// propset_ToolBar_Width
// ----------------------------------------------------------------------------
void propset_ToolBar_Width (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_ToolBar_Width);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBar))
		return;

	((DControlToolBar *)ebGetObject (lpArgs, 1)) -> put_Width (ebGetLong(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// propget_ToolBar_Height
// ----------------------------------------------------------------------------
void propget_ToolBar_Height (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_ToolBar_Height);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBar))
		return;

long lHeight = 0;

	((DControlToolBar *)ebGetObject (lpArgs, 1)) -> get_Height (&lHeight);
	ebSetLong (lpArgs, 0, lHeight);
}

// ----------------------------------------------------------------------------
// propset_ToolBar_Height
// ----------------------------------------------------------------------------
void propset_ToolBar_Height (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_ToolBar_Height);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBar))
		return;

	((DControlToolBar *)ebGetObject (lpArgs, 1)) -> put_Height (ebGetLong(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// propget_ToolBar_CtrlID
// ----------------------------------------------------------------------------
void propget_ToolBar_CtrlID (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_ToolBar_CtrlID);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBar))
		return;

int lCtrlID = 0;

	((DControlToolBar *)ebGetObject (lpArgs, 1)) -> get_CtrlID (&lCtrlID);
	ebSetLong (lpArgs, 0, lCtrlID);
}

// ----------------------------------------------------------------------------
// propset_ToolBar_CtrlID
// ----------------------------------------------------------------------------
void propset_ToolBar_CtrlID (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_ToolBar_CtrlID);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBar))
		return;

	((DControlToolBar *)ebGetObject (lpArgs, 1)) -> put_CtrlID (ebGetInt(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// propget_ToolBar_Style
// ----------------------------------------------------------------------------
void propget_ToolBar_Style (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_ToolBar_Style);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBar))
		return;

long lStyle = 0;

	((DControlToolBar *)ebGetObject (lpArgs, 1)) -> get_Style (&lStyle);
	ebSetLong (lpArgs, 0, lStyle);
}

// ----------------------------------------------------------------------------
// propset_ToolBar_Style
// ----------------------------------------------------------------------------
void propset_ToolBar_Style (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_ToolBar_Style);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBar))
		return;

	((DControlToolBar *)ebGetObject (lpArgs, 1)) -> put_Style (ebGetLong(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// propget_ToolBar_StyleEx
// ----------------------------------------------------------------------------
void propget_ToolBar_StyleEx (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_ToolBar_StyleEx);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBar))
		return;

long lStyleEx = 0;

	((DControlToolBar *)ebGetObject (lpArgs, 1)) -> get_StyleEx (&lStyleEx);
	ebSetLong (lpArgs, 0, lStyleEx);
}

// ----------------------------------------------------------------------------
// propset_ToolBar_StyleEx
// ----------------------------------------------------------------------------
void propset_ToolBar_StyleEx (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propset_ToolBar_StyleEx);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBar))
		return;

	((DControlToolBar *)ebGetObject (lpArgs, 1)) -> put_StyleEx (ebGetLong(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// refcnt_ToolBarButton
// ----------------------------------------------------------------------------
void refcnt_ToolBarButton (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE_SYS(refcnt_GeoObjects);

	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
			ebSetObject (lpArgs, 0, NULL);		// für alle Fälle

			try {
			WDControlToolBarButton ToolBarBttn(CLSID_TRiASToolBarButton);
			WDispatch Disp;

				THROW_FAILED_HRESULT(((OLE2AutoExtension *)g_pTE) -> App() -> GetDispatchIF (Disp.ppi()));
				THROW_FAILED_HRESULT(ToolBarBttn -> put_Application (Disp));
				THROW_FAILED_HRESULT(ToolBarBttn -> put_Parent (Disp));
							
				ebSetObject (lpArgs, 0, (DWORD)ToolBarBttn.detach());

			} catch (_com_error&) {
				return;
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
// Name_ToolBarButton_propget
// ----------------------------------------------------------------------------
void Name_ToolBarButton_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Name_ToolBarButton_propget);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBarButton))
		return;

CComBSTR bstr;
HRESULT hr = ((DControlToolBarButton *)ebGetObject (lpArgs, 1)) -> get_Name (CLEARED(&bstr));

	if (FAILED(hr))	{
		ebSetString (lpArgs, 0, NULL);
		return;
	}

	USES_CONVERSION;
	ebSetString (lpArgs, 0, ebCreateString (hThread, OLE2A(bstr)));
}

// ----------------------------------------------------------------------------
// Name_ToolBarButton_propset
// ----------------------------------------------------------------------------
void Name_ToolBarButton_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Name_ToolBarButton_propset);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBarButton))
		return;

	USES_CONVERSION;

ebHSUB hStr = ebGetString (lpArgs, 2);

	if (NULL != hStr) {
	LPSTR lpstr = ebLockString (hThread, hStr);
	 
		((DControlToolBarButton *)ebGetObject (lpArgs, 1)) -> put_Name (A2OLE(lpstr));
		ebUnlockString (hThread, hStr);
	}
}

// ----------------------------------------------------------------------------
// Helptext_ToolBarButton_propget
// ----------------------------------------------------------------------------
void Helptext_ToolBarButton_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Helptext_ToolBarButton_propget);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBarButton))
		return;

CComBSTR bstr;
HRESULT hr = ((DControlToolBarButton *)ebGetObject (lpArgs, 1)) -> get_HelpText (CLEARED(&bstr));

	if (FAILED(hr))	{
		ebSetString (lpArgs, 0, NULL);
		return;
	}

	USES_CONVERSION;
	ebSetString (lpArgs, 0, ebCreateString (hThread, OLE2A(bstr)));
}

// ----------------------------------------------------------------------------
// Helptext_ToolBarButton_propset
// ----------------------------------------------------------------------------
void Helptext_ToolBarButton_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Helptext_ToolBarButton_propset);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBarButton))
		return;

	USES_CONVERSION;

ebHSUB hStr = ebGetString (lpArgs, 2);

	if (NULL != hStr) {
	LPSTR lpstr = ebLockString (hThread, hStr);
	 
		((DControlToolBarButton *)ebGetObject (lpArgs, 1)) -> put_HelpText (A2OLE(lpstr));
		ebUnlockString (hThread, hStr);
	}
}

// ----------------------------------------------------------------------------
// State_ToolBarButton_propget
// ----------------------------------------------------------------------------
void State_ToolBarButton_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(State_ToolBarButton_propget);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBarButton))
		return;

BUTTONSTATE bs = (BUTTONSTATE)0;

	((DControlToolBarButton *)ebGetObject (lpArgs, 1)) -> get_State (&bs);
	ebSetInt (lpArgs, 0, (int)bs);
}

// ----------------------------------------------------------------------------
// State_ToolBarButton_propset
// ----------------------------------------------------------------------------
void State_ToolBarButton_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(State_ToolBarButton_propset);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBarButton))
		return;

int iState = ebGetInt(lpArgs, 2);

	((DControlToolBarButton *)ebGetObject (lpArgs, 1)) -> put_State ((BUTTONSTATE)(iState & ~BUTTONSTATE_NOKICKIDLE));
	if (!(iState & BUTTONSTATE_NOKICKIDLE)) 
		DEX_KickIdle();
}

// ----------------------------------------------------------------------------
// CmdID_ToolBarButton_propget
// ----------------------------------------------------------------------------
void CmdID_ToolBarButton_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(CmdID_ToolBarButton_propget);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBarButton))
		return;

int iCmdID = 0;

	((DControlToolBarButton *)ebGetObject (lpArgs, 1)) -> get_CmdID (&iCmdID);
	ebSetLong (lpArgs, 0, iCmdID);
}

// ----------------------------------------------------------------------------
// CmdID_ToolBarButton_propset
// ----------------------------------------------------------------------------
void CmdID_ToolBarButton_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(CmdID_ToolBarButton_propset);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBarButton))
		return;

int iCmdID = ebGetLong(lpArgs, 2);

	((DControlToolBarButton *)ebGetObject (lpArgs, 1)) -> put_CmdID (iCmdID);
}

// ----------------------------------------------------------------------------
// Style_ToolBarButton_propget
// ----------------------------------------------------------------------------
void Style_ToolBarButton_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Style_ToolBarButton_propget);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBarButton))
		return;

BUTTONSTYLE bs = (BUTTONSTYLE)0;

	((DControlToolBarButton *)ebGetObject (lpArgs, 1)) -> get_Style (&bs);
	ebSetInt (lpArgs, 0, (int)bs);
}

// ----------------------------------------------------------------------------
// Style_ToolBarButton_propset
// ----------------------------------------------------------------------------
void Style_ToolBarButton_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Style_ToolBarButton_propset);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBarButton))
		return;

int iStyle = ebGetInt(lpArgs, 2);

	((DControlToolBarButton *)ebGetObject (lpArgs, 1)) -> put_Style ((BUTTONSTYLE)(iStyle & ~BUTTONSTYLE_NOKICKIDLE));
	if (!(iStyle & BUTTONSTYLE_NOKICKIDLE)) 
		DEX_KickIdle();
}

// ----------------------------------------------------------------------------
// AttachImage_ToolBarButton_command
// ----------------------------------------------------------------------------
void AttachImage_ToolBarButton_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(AttachImage_ToolBarButton_command);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBarButton))
		return;

CComVariant vPicture;

	V_VT(&vPicture) = VT_I4;
	V_I4(&vPicture) = ebGetLong (lpArgs, 2);

CComVariant vIndex (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant vSizeX (MakeVARIANT (hThread, iNumArgs, lpArgs, 4));

	((DControlToolBarButton *)ebGetObject (lpArgs, 1)) -> AttachImage (vPicture, vIndex, vSizeX);
}

// ----------------------------------------------------------------------------
// AttachImage_ToolBarButton_command3
// ----------------------------------------------------------------------------
void AttachImage_ToolBarButton_command3 (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(AttachImage_ToolBarButton_command3);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBarButton))
		return;

ebHSUB hStr = ebGetString (lpArgs, 2);
CComVariant vPicture(ebLockString (hThread, hStr));

CComVariant vIndex (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant vSizeX (MakeVARIANT (hThread, iNumArgs, lpArgs, 4));

	((DControlToolBarButton *)ebGetObject (lpArgs, 1)) -> AttachImage (vPicture, vIndex, vSizeX);
}

// ----------------------------------------------------------------------------
// AttachImage_ToolBarButton_command2
// ----------------------------------------------------------------------------
void AttachImage_ToolBarButton_command2 (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(AttachImage_ToolBarButton_command2);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBarButton))
		return;

VARIANT vPicture;

	V_VT(&vPicture) = VT_DISPATCH;
	V_DISPATCH(&vPicture) = (IDispatch *)ebGetObject (lpArgs, 2);

CComVariant vIndex (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
CComVariant vSizeX (MakeVARIANT (hThread, iNumArgs, lpArgs, 4));

	((DControlToolBarButton *)ebGetObject (lpArgs, 1)) -> AttachImage (vPicture, vIndex, vSizeX);
}

// ----------------------------------------------------------------------------
// Value_ToolBarButton_propset
// ----------------------------------------------------------------------------
void Value_ToolBarButton_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Value_ToolBarButton_propset);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBarButton))
		return;

	((DControlToolBarButton *)ebGetObject (lpArgs, 1)) -> put_Value ((VARIANT_BOOL)ebGetBool(lpArgs, 2));
}

// ----------------------------------------------------------------------------
// Refresh_ToolBars_command
// ----------------------------------------------------------------------------
void Refresh_ToolBars_command (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(Refresh_ToolBars_command);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBars))
		return;
	((DControlToolBars *)ebGetObject (lpArgs, 1)) -> Refresh();
}

// ----------------------------------------------------------------------------
// ToolBars_Application_propget
// ----------------------------------------------------------------------------
void ToolBars_Application_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(ToolBars_Application_propget);

	try {
	WDControlToolBars Bars;

		THROW_FAILED_HRESULT(((OLE2AutoExtension *)g_pTE) -> AppDisp() -> get_ToolBars (Bars.ppi()));
		ebSetObject (lpArgs, 0, (DWORD)Bars.detach());
	
	} catch (_com_error&) {
		ebSetObject (lpArgs, 0, 0);
	}
}

// ----------------------------------------------------------------------------
// GetToolBar_Application_func
// ----------------------------------------------------------------------------
void GetToolBar_Application_func (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(GetToolBar_Application_func);

	try {
	ebHSUB hStr = ebGetString (lpArgs, 2);
	CComBSTR bstrName (ebLockString (hThread, hStr));
	WDControlToolBar Bar;

		THROW_FAILED_HRESULT(((OLE2AutoExtension *)g_pTE) -> AppDisp() -> GetToolBar (bstrName, Bar.ppi()));
		
		ebUnlockString (hThread, hStr);
		ebSetObject (lpArgs, 0, (DWORD)Bar.detach());
	
	} catch (_com_error&) {
		ebSetObject (lpArgs, 0, 0);
	}
}

// ----------------------------------------------------------------------------
// AddToolBar_Application_func
// ----------------------------------------------------------------------------
void AddToolBar_Application_func (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(AddToolBar_Application_func);

	try {
	ebHSUB hStr = ebGetString (lpArgs, 2);
	CComBSTR bstrName (ebLockString (hThread, hStr));
	CComVariant vStyle (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
	WDControlToolBar Bar;

		THROW_FAILED_HRESULT(((OLE2AutoExtension *)g_pTE) -> AppDisp() -> AddToolBar (bstrName, vStyle, Bar.ppi()));
		
		ebUnlockString (hThread, hStr);
		ebSetObject (lpArgs, 0, (DWORD)Bar.detach());
	
	} catch (_com_error&) {
		ebSetObject (lpArgs, 0, 0);
	}
}

// ----------------------------------------------------------------------------
// RemoveToolBar_Application_cmd
// ----------------------------------------------------------------------------
void RemoveToolBar_Application_cmd (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(RemoveToolBar_Application_cmd);

	try {
	ebHSUB hStr = ebGetString (lpArgs, 2);
	CComBSTR bstrName (ebLockString (hThread, hStr));

		THROW_FAILED_HRESULT(((OLE2AutoExtension *)g_pTE) -> AppDisp() -> RemoveToolBar (bstrName));
		
		ebUnlockString (hThread, hStr);

	} catch (_com_error&) {
		;
	}
}

// ----------------------------------------------------------------------------
// propget_ToolBars_NewEnum
// ----------------------------------------------------------------------------
void propget_ToolBars_NewEnum (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_ToolBars_NewEnum);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBars))
		return;

WUnknown IUnk;	
HRESULT hr = ((DControlToolBars *)ebGetObject (lpArgs, 1)) -> _NewEnum(IUnk.ppi());

	ebSetObject (lpArgs, 0, NULL);
	if (SUCCEEDED(hr)) {
		try {
		WEnumVARIANT Bars (IUnk);		// throws hr
	
			Bars -> Reset();
			ebSetObject (lpArgs, 0, (DWORD)Bars.detach());
		} catch (_com_error&) {
			TRACE("Could not QI IEnumVARIANT from IUnknown\n");
		}
	}
}		

// ----------------------------------------------------------------------------
// propget_ToolBars_Next
// ----------------------------------------------------------------------------
void propget_ToolBars_Next (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_ToolBars_Next);

// nächstes Item aus Enumerator geben lassen
CComVariant v;
HRESULT hr = ((IEnumVARIANT *)ebGetObject (lpArgs, 1)) -> Next (1, &v, NULL);
DControlToolBar *pIBar = (DControlToolBar *)ebGetObject (lpArgs, 0);

	RELEASE(pIBar);
	ebSetObject (lpArgs, 0, NULL);

	if (S_OK == hr) {
		hr = v.ChangeType (VT_DISPATCH);
		if (SUCCEEDED(hr) && NULL != V_DISPATCH(&v)) {
			hr = V_DISPATCH(&v) -> QueryInterface (IID_DControlToolBar, (LPVOID *)&pIBar);
			if (SUCCEEDED(hr)) 
				ebSetObject (lpArgs, 0, (DWORD)pIBar);
		}
	}
}

// ----------------------------------------------------------------------------
// propget_ToolBars_Next
// ----------------------------------------------------------------------------
void cmd_ToolBars_SaveState (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_ToolBars_NewEnum);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBars))
		return;

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));

	((DControlToolBars *)ebGetObject (lpArgs, 1)) -> SaveState (v1, v2);
	DEX_KickIdle();
}

// ----------------------------------------------------------------------------
// propget_ToolBars_Next
// ----------------------------------------------------------------------------
void cmd_ToolBars_LoadState (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(propget_ToolBars_NewEnum);

// Test for typemismatch
	if (g_fDebugScript && isTypeMismatch (hThread, lpArgs, RTTI_ToolBars))
		return;

CComVariant v1 (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));

	((DControlToolBars *)ebGetObject (lpArgs, 1)) -> LoadState (v1, v2);
}

