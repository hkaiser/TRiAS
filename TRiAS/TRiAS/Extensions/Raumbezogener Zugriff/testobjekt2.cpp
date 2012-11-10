// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "testobjekt2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CTestObjekt2 properties

/////////////////////////////////////////////////////////////////////////////
// CTestObjekt2 operations

unsigned long CTestObjekt2::AddRef()
{
	unsigned long result;
	InvokeHelper(0x60000001, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

unsigned long CTestObjekt2::Release()
{
	unsigned long result;
	InvokeHelper(0x60000002, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

void CTestObjekt2::put_xmin(const VARIANT& varmin)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &varmin);
}

void CTestObjekt2::put_xmax(const VARIANT& varmax)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &varmax);
}

void CTestObjekt2::get_xmin(VARIANT* pmin)
{
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pmin);
}

void CTestObjekt2::get_xmax(VARIANT* pmax)
{
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pmax);
}
