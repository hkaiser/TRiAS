///////////////////////////////////////////////////////////////////////////////
// PictureExt.cpp: Image support

#include "precomp.hxx"

#include <toolguid.h>			// ToolBarSupport
#include <itoolbar.h>
#include <dtoolbar.h>
#include <BildObj.h>
#include <Picture.h>

#include "jumptab.h"
#include "olebsext.hxx"			// function  prototypes


#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// external functions
CComVariant MakeVARIANT (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs, int iArg);

// ----------------------------------------------------------------------------
// refcnt_Picture
// ----------------------------------------------------------------------------
void refcnt_Picture (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	switch (iNumArgs) {
	case OBJECT_REFNEW:
		ebSetObject (lpArgs, 0, 0L);		// not supported
		break;
		
	case OBJECT_REFINC:
		((IPictureDisp *)ebGetObject(lpArgs, 1)) -> AddRef();
		break;
		
	case OBJECT_REFDEC:
		((IPictureDisp *)ebGetObject(lpArgs, 1)) -> Release();
		break;
	}
}

// ----------------------------------------------------------------------------
// Handle_Picture_propget
// ----------------------------------------------------------------------------
void Handle_Picture_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	TRY {
	CPicture Pict ((IPictureDisp *)ebGetObject(lpArgs, 1), false);

		ebSetLong (lpArgs, 0, Pict.GetHandle());
	} CATCH (COleException, e) {
		ebSetLong (lpArgs, 0, 0);
	} CATCH (COleDispatchException, e) {
		ebSetLong (lpArgs, 0, 0);
	} END_CATCH
}

// ----------------------------------------------------------------------------
// hPal_Picture_propget
// ----------------------------------------------------------------------------
void hPal_Picture_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	TRY {
	CPicture Pict ((IPictureDisp *)ebGetObject(lpArgs, 1), false);

		ebSetLong (lpArgs, 0, Pict.GetHPal());
	} CATCH (COleException, e) {
		ebSetLong (lpArgs, 0, 0);
	} CATCH (COleDispatchException, e) {
		ebSetLong (lpArgs, 0, 0);
	} END_CATCH
}

// ----------------------------------------------------------------------------
// hPal_Picture_propset
// ----------------------------------------------------------------------------
void hPal_Picture_propset (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	TRY {
	CPicture Pict ((IPictureDisp *)ebGetObject(lpArgs, 1), false);

		Pict.SetHPal (ebGetLong (lpArgs, 2));
	} CATCH (COleException, e) {
		;
	} CATCH (COleDispatchException, e) {
		;
	} END_CATCH
}

// ----------------------------------------------------------------------------
// Type_Picture_propget
// ----------------------------------------------------------------------------
void Type_Picture_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	TRY {
	CPicture Pict ((IPictureDisp *)ebGetObject(lpArgs, 1), false);

		ebSetInt (lpArgs, 0, Pict.GetType());
	} CATCH (COleException, e) {
		ebSetInt (lpArgs, 0, 0);
	} CATCH (COleDispatchException, e) {
		ebSetInt (lpArgs, 0, 0);
	} END_CATCH
}

// ----------------------------------------------------------------------------
// Width_Picture_propget
// ----------------------------------------------------------------------------
void Width_Picture_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	TRY {
	CPicture Pict ((IPictureDisp *)ebGetObject(lpArgs, 1), false);

		ebSetLong (lpArgs, 0, Pict.GetWidth());
	} CATCH (COleException, e) {
		ebSetLong (lpArgs, 0, 0);
	} CATCH (COleDispatchException, e) {
		ebSetLong (lpArgs, 0, 0);
	} END_CATCH
}

// ----------------------------------------------------------------------------
// Height_Picture_propget
// ----------------------------------------------------------------------------
void Height_Picture_propget (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	TRY {
	CPicture Pict ((IPictureDisp *)ebGetObject(lpArgs, 1), false);

		ebSetLong (lpArgs, 0, Pict.GetHeight());
	} CATCH (COleException, e) {
		ebSetLong (lpArgs, 0, 0);
	} CATCH (COleDispatchException, e) {
		ebSetLong (lpArgs, 0, 0);
	} END_CATCH
}

// ----------------------------------------------------------------------------
// LoadPicture_protofunc
// Pict = LoadPicture([strFileName])
// ----------------------------------------------------------------------------
DefineSmartInterface(Dispatch);

void LoadPicture_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
CComVariant v (MakeVARIANT (hThread, iNumArgs, lpArgs, 1));

	ebSetObject (lpArgs, 0, (DWORD)NULL);
	if (SUCCEEDED(v.ChangeType (VT_BSTR))) {
	CBildObjekt bmp;
	
		USES_CONVERSION;
		if (!bmp.ReadFile (OLE2A(V_BSTR(&v)))) 
			return;

	PICTDESC pdesc;
	WDispatch Disp;

		pdesc.cbSizeofstruct = sizeof(pdesc);
		pdesc.picType = PICTYPE_BITMAP;
		pdesc.bmp.hbitmap = bmp.Detach();
		pdesc.bmp.hpal = bmp.DetachHPal();

		if (SUCCEEDED(OleCreatePictureIndirect (&pdesc, IID_IPictureDisp, true, Disp.ppv())))
			ebSetObject (lpArgs, 0, (DWORD)Disp.detach());
	}
}

// ----------------------------------------------------------------------------
// LoadResPicture_protofunc
// Pict = LoadResPicture(ResID, iType[, ResFile]))
// ----------------------------------------------------------------------------
HRESULT LoadPicture (int iType, UINT uiResID, bool fOwn, IDispatch **ppIDisp)
{
PICTDESC pdesc;

	pdesc.cbSizeofstruct = sizeof(pdesc);

	switch (iType) {
	case 0:		// vbResBitmap
		{
		CBitmap bmp;

			if (!bmp.LoadMappedBitmap (uiResID)) 
				return E_FAIL;

			pdesc.picType = PICTYPE_BITMAP;
			pdesc.bmp.hbitmap = (HBITMAP)bmp.Detach();
			pdesc.bmp.hpal = NULL;
		}
		break;

	case 1:		// vbResIcon
		{
		HICON hIcon = AfxGetApp() -> LoadIcon(uiResID);

			pdesc.picType = PICTYPE_ICON;
			pdesc.icon.hicon = hIcon;
		}
		break;

	case 2:		// vbResCursor
		{
		HCURSOR hCursor = AfxGetApp() -> LoadCursor(uiResID);

			pdesc.picType = PICTYPE_ICON;
			pdesc.icon.hicon = hCursor;
		}
		break;

	default:
		return E_INVALIDARG;
	}

	return OleCreatePictureIndirect (&pdesc, IID_IPictureDisp, fOwn, (LPVOID *)ppIDisp);
}

void LoadResPicture_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
long iResID = ebGetLong (lpArgs, 1);
CComVariant vType (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));
CComVariant v (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));
int iType = 0;

	if (SUCCEEDED(vType.ChangeType (VT_I2)))
		iType = V_I2(&vType);

	ebSetObject (lpArgs, 0, (DWORD)NULL);

	if (SUCCEEDED(v.ChangeType (VT_BSTR))) {
	// String aus gegebener Resource laden
		USES_CONVERSION;

	// #HK990625 work around WinNT4 LoadProcess bug
	char szModuleShort[_MAX_PATH];
	string strLong (OLE2A(V_BSTR(&v)));
	int cbShortName = GetShortPathName (strLong.c_str(), szModuleShort, _MAX_PATH);
	LPCSTR pcModule = NULL;

		if (cbShortName == _MAX_PATH)
			return;
		pcModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? strLong.c_str() : szModuleShort;

	HINSTANCE hInst = ::LoadLibrary(pcModule);

		if (NULL != hInst) {
		HINSTANCE hOldInst = AfxGetResourceHandle();

			AfxSetResourceHandle(hInst);
			{
			WDispatch Disp;

				if (SUCCEEDED(LoadPicture (iType, iResID, true, Disp.ppi())))
					ebSetObject (lpArgs, 0, (DWORD)Disp.detach());
			}
			AfxSetResourceHandle(hOldInst);
			::FreeLibrary(hInst);
		}
	} else {
	// String aus Standard-Resource laden
	WDispatch Disp;

		if (SUCCEEDED(LoadPicture (iType, iResID, true, Disp.ppi())))
			ebSetObject (lpArgs, 0, (DWORD)Disp.detach());
	}
}

// ----------------------------------------------------------------------------
// LoadResString_protofunc
// Str$ = LoadResSting(resID [, ResFile])
// ----------------------------------------------------------------------------
void LoadResString_protofunc (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
long iResID = ebGetLong (lpArgs, 1);
CComVariant v (MakeVARIANT (hThread, iNumArgs, lpArgs, 2));

	ebFreeString (hThread, ebGetString (lpArgs, 0));
	ebSetString(lpArgs, 0, NULL);

	if (v.ChangeType (VT_BSTR)) {
	// String aus gegebener Resource laden
		USES_CONVERSION;

	// #HK990625 work around WinNT4 LoadProcess bug
	char szModuleShort[_MAX_PATH];
	string strLong (OLE2A(V_BSTR(&v)));
	int cbShortName = GetShortPathName (strLong.c_str(), szModuleShort, _MAX_PATH);
	LPCSTR pcModule = NULL;

		if (cbShortName == _MAX_PATH)
			return;
		pcModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? strLong.c_str() : szModuleShort;

	HINSTANCE hInst = ::LoadLibrary(pcModule);

		if (NULL != hInst) {
		HINSTANCE hOldInst = AfxGetResourceHandle();

			AfxSetResourceHandle(hInst);
			{
			CString str;

				ATLTRY(str.LoadString (iResID));
				if (str.GetLength() > 0) 
					ebSetString(lpArgs, 0, ebCreateString (hThread, (LPCSTR)str));
			}
			AfxSetResourceHandle(hOldInst);
			::FreeLibrary(hInst);
		}
	} else {
	// String aus Standard-Resource laden
	CString str;

		ATLTRY(str.LoadString (iResID));
		if (str.GetLength() > 0) 
			ebSetString(lpArgs, 0, ebCreateString (hThread, (LPCSTR)str));
	}
}

