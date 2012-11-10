// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "testdispatchdriver.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// ITestObjekt properties

/////////////////////////////////////////////////////////////////////////////
// ITestObjekt operations

void ITestObjekt::get_value(DISPID id, VARIANT* pmin);
{
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(id, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pmin);
}
