// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "pbasic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CGMPoint properties

/////////////////////////////////////////////////////////////////////////////
// CGMPoint operations

double CGMPoint::GetX()
{
	double result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CGMPoint::SetX(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CGMPoint::GetY()
{
	double result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CGMPoint::SetY(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CGMPoint::GetZ()
{
	double result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CGMPoint::SetZ(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}


/////////////////////////////////////////////////////////////////////////////
// CGMPoints properties

/////////////////////////////////////////////////////////////////////////////
// CGMPoints operations

long CGMPoints::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH CGMPoints::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

void CGMPoints::Add(LPDISPATCH Point, const VARIANT& index)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Point, &index);
}

void CGMPoints::Remove(const VARIANT& index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &index);
}

/////////////////////////////////////////////////////////////////////////////
// CGMPointGeometry properties

/////////////////////////////////////////////////////////////////////////////
// CGMPointGeometry operations

LPDISPATCH CGMPointGeometry::GetOrigin()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void CGMPointGeometry::SetRefOrigin(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}


/////////////////////////////////////////////////////////////////////////////
// CGMLineGeometry properties

/////////////////////////////////////////////////////////////////////////////
// CGMLineGeometry operations

LPDISPATCH CGMLineGeometry::GetStart()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void CGMLineGeometry::SetRefStart(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH CGMLineGeometry::GetEnd()
{
	LPDISPATCH result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void CGMLineGeometry::SetRefEnd(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}


/////////////////////////////////////////////////////////////////////////////
// CGMPolylineGeometry properties

/////////////////////////////////////////////////////////////////////////////
// CGMPolylineGeometry operations

LPDISPATCH CGMPolylineGeometry::GetPoints()
{
	LPDISPATCH result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// CGMPolygonGeometry properties

/////////////////////////////////////////////////////////////////////////////
// CGMPolygonGeometry operations

LPDISPATCH CGMPolygonGeometry::GetPoints()
{
	LPDISPATCH result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// CGMBoundaryGeometry properties

/////////////////////////////////////////////////////////////////////////////
// CGMBoundaryGeometry operations

LPDISPATCH CGMBoundaryGeometry::GetExterior()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void CGMBoundaryGeometry::SetRefExterior(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH CGMBoundaryGeometry::GetHoles()
{
	LPDISPATCH result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// CGMGeometryCollection properties

/////////////////////////////////////////////////////////////////////////////
// CGMGeometryCollection operations

long CGMGeometryCollection::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH CGMGeometryCollection::Item(const VARIANT& index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&index);
	return result;
}

void CGMGeometryCollection::Add(LPDISPATCH geometry, const VARIANT& index)
{
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 geometry, &index);
}

void CGMGeometryCollection::Remove(const VARIANT& index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &index);
}


/////////////////////////////////////////////////////////////////////////////
// CGMTextPointGeometry properties

/////////////////////////////////////////////////////////////////////////////
// CGMTextPointGeometry operations

LPDISPATCH CGMTextPointGeometry::GetOrigin()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void CGMTextPointGeometry::SetRefOrigin(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

double CGMTextPointGeometry::GetRotation()
{
	double result;
	InvokeHelper(0x60030000, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CGMTextPointGeometry::SetRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x60030000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long CGMTextPointGeometry::GetAlignment()
{
	long result;
	InvokeHelper(0x60030002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CGMTextPointGeometry::SetAlignment(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60030002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CGMTextPointGeometry::GetRichText()
{
	CString result;
	InvokeHelper(0x60030004, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CGMTextPointGeometry::SetRichText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60030004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString CGMTextPointGeometry::GetText()
{
	CString result;
	InvokeHelper(0x60030006, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CGMTextPointGeometry::SetText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60030006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

short CGMTextPointGeometry::GetFormat()
{
	short result;
	InvokeHelper(0x60030008, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

void CGMTextPointGeometry::GetNormalUnitVector(double* ui, double* uj, double* uk)
{
	static BYTE parms[] =
		VTS_PR8 VTS_PR8 VTS_PR8;
	InvokeHelper(0x60030009, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ui, uj, uk);
}

void CGMTextPointGeometry::SetNormalUnitVector(double ui, double uj, double uk)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x6003000a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ui, uj, uk);
}
