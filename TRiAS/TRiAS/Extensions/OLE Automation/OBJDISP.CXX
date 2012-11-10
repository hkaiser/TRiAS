// Eine Objekt (ProgrammierInterface) -----------------------------------
// File: OBJDISP.CXX

#include "precomp.hxx"

#include "oleautor.h"

#include <dirisole.h>
#include <operguid.h>
#include <buffguid.h>
#include <trelguid.h>
#include <editguid.h>

#include <ospace/com/iterenum.h>
#include <visinfo.h>

#include <objcontx.hxx>

#include "objarray.hxx"
#include "enumobjs.hxx"
#include "obj.hxx"
#include "objs.hxx"

#include "ftsarray.hxx"
#include "enumfts.hxx"
#include "feat.hxx"
#include "fts.hxx"

#include "array.hxx"		// CSafeArray
#include "objwin.hxx"

#import "tlb/triascs.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids
#import "tlb/tdbgeo.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

const int GUID_CCH = 39;

///////////////////////////////////////////////////////////////////////////////
// verwendete SmartInterface's etc.
DefineSortingEnumerator(LONG);			// SEnumLONG
DefineSmartInterface(EnumLONG);			// WEnumLONG
DefineSmartInterface(QueryEnumLONG);	// WQueryEnumLONG

DefineSmartInterface(ExtendObjOper);	// WExtendObjOper
DefineSmartInterface(ExtendTopRel2);	// WExtendTopRel2
DefineSmartInterface(ExtendBuffer);		// WExtendBuffer
DefineSmartInterface(ExtendGeoEdit);	// WExtendGeoEdit
DefineSmartInterface(ExtendAbstand2);	// WExtendAbstand2
DefineSmartInterface(ExtendGeoRein);	// WExtendGeoRein

DefineSmartInterface(Dispatch);			// WDispatch
DefineSmartInterface(VisObjExt);		// WVisObjExt
DefineSmartInterface2(DVisInfo, IID_DVisInfo);				// WDVisInfo

DefineSmartInterface2(DGeoObjectWin, IID_DGeoObjectWin);	// WDGeoObjectWin
DefineSmartInterface2(DGeoClass, IID_DGeoClass);			// WDGeoClass

DefineSmartInterface2(DGeoObject, IID_DGeoObject);			// WDGeoObject
DefineSmartInterface2(DGeoObjects, IID_DGeoObjects);		// WDGeoObjects

DefineSmartInterface(TRiASConnection);	// WTRiASConnection

DefineSmartInterface(TRiASCS);			// WTRiASCS
DefineSmartInterface(TRiASCSStorageService);	// WTRiASCSStorageService

// ProgrammierInterfaceFunktionen ---------------------------------------------
STDMETHODIMP CGeoObject::get_isA (LONG *plRTTI)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::get_isA");
	if (NULL == plRTTI) 
		return E_POINTER;
	*plRTTI = RTTI_GeoObject;
	return NOERROR;
}

STDMETHODIMP CGeoObject::get_Parent (IDispatch **ppIDisp)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::get_Parent");
	return m_pUnk -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);
}

STDMETHODIMP CGeoObject::get_Application (IDispatch **ppIDisp)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::get_Application");
	return ((_DApplication *)m_pApp) -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);
}

STDMETHODIMP CGeoObject::put_Parent (IDispatch *pIDisp)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::put_Parent");
	return E_NOTIMPL;
}

STDMETHODIMP CGeoObject::put_Application (IDispatch *pIDisp)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::put_Application");
	return E_NOTIMPL;
}

// Liefert den ObjektNummer dieses Objektes -----------------------------------
STDMETHODIMP CGeoObject::get_Value (long *plONr)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::get_Value");

	if (NULL == plONr)
		return E_POINTER;

	*plONr = GetValue();
	
return NOERROR;
}


// Liefert den Objektnamen dieses Objektes ------------------------------------
STDMETHODIMP CGeoObject::get_Name (BSTR *pbstrName)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::get_Name");

	if (NULL == pbstrName) return E_POINTER;

// Objekt nach Objektnamen fragen
	try {
		if (GetName()) {
			*pbstrName = SysAllocString (WideString(GetName()));
			if (NULL == *pbstrName) 
				_com_issue_error(E_OUTOFMEMORY);
		} else 
			_com_issue_error(E_UNEXPECTED);

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

return NOERROR;
}


// Setzt/löscht den Objektnamen dieses Objektes -------------------------------
STDMETHODIMP CGeoObject::put_Name (BSTR bstrName)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::put_Name");

	if (NULL == bstrName) return E_POINTER;

	if (!m_pDoc -> SetObjectName (GetValue(), AnsiString(bstrName)))
		return E_FAIL;

return NOERROR;
}

// Objekttyp aus Bits rauslösen, der erste gewinnt
short ObjTypeFromBits (short iBits)
{
short iSO = (OTSachObjekt & iBits) ? OGSachObjekt : 0;

	if (iBits & OTPunkt) return OGPunkt|iSO;
	if (iBits & OTLinie) return OGLinie|iSO;
	if (iBits & OTFlaeche) return OGFlaeche|iSO;
	if (iBits & OTText) return OGText|iSO;
	if (iBits & OTKO) return OGKO|iSO;

	return OGUnknown;
}

// Objekttyp immer als Bits nach draußen liefern, damit diese kombiniert werden können
OBJECTTYPE BitsFromObjType (short iObjType)
{
short iBits = 0;

	switch (iObjType) {
	case OGPunkt:
		iBits = OTPunkt;
		break;

	case OGLinie:
		iBits = OTLinie;
		break;

	case OGFlaeche:
	case OGKreis:
		iBits = OTFlaeche;
		break;

	case OGKO:
		iBits = OTKO;
		break;

	case OGLabel:
	case OGText:
		iBits = OTText;
		break;

	case OGUnknown:
		return OBJECTTYPE_Unknown;		// Fehler
	}

	if (iObjType & OGSachObjekt)
		iBits |= OTSachObjekt;

return (OBJECTTYPE)iBits;
}


STDMETHODIMP CGeoObject::get_ObjType (OBJECTTYPE *pObjType)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::get_ObjType");

	if (NULL == pObjType) return E_POINTER;

	*pObjType = BitsFromObjType (GetObjectType());
	return NOERROR;
}

STDMETHODIMP CGeoObject::get_ObjClass (DGeoClass **ppICls)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::get_ObjClass");

	TEST_E_POINTER("CGeoObject::get_ObjClass", ppICls);

CClass *pClass = m_pDoc -> FGetClassDisp (GetObjIdentEx(), ppICls, GEOCLASSMODE_Get);
			
	if (pClass == NULL) return E_UNEXPECTED;
	return S_OK;
}


// Liefert HeaderEintrag aus GeoDB Header -------------------------------------
STDMETHODIMP CGeoObject::ObjDistance (DGeoObject *pIObj, VARIANT vMode, VARIANT vMinMax, double *pdblDist)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::ObjDistance");

WExtendAbstand2 pIAbstand;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetIDistance (pIAbstand.ppi());

	if (FAILED(hr)) return hr;
		
// Abstand berechnen, dazu AbstandsErweiterung rufen
DistTyp rgType = DISTTYP_AUTO;
ExtrAbst rgMinMax = ABST_MIN;
CComVariant v;

	hr = VariantChangeType (&v, &vMode, 0, VT_I2);
	if (SUCCEEDED(hr)) rgType = (DistTyp)V_I2(&v);

	hr = VariantChangeType (&v, &vMinMax, 0, VT_I2);
	if (SUCCEEDED(hr)) rgMinMax = (ExtrAbst)V_I2(&v);

LONG lONr = INVALID_ONR;

	hr = pIObj -> get_Value (&lONr);
	if (FAILED(hr)) return hr;

	return pIAbstand -> DistanceObjObj_ONr (GetValue(), lONr, pdblDist, rgType, rgMinMax);
}


STDMETHODIMP CGeoObject::ClassDistance (DGeoClass *pICls, VARIANT *pvObj,
		VARIANT vModeArg, VARIANT vMinMaxArg, double *pdblDist)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::ClassDistance");

WExtendAbstand2 Abstand;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetIDistance (Abstand.ppi());

	if (FAILED(hr)) return hr;
		
// Abstand berechnen, dazu AbstandsErweiterung rufen
DistTyp rgType = DISTTYP_AUTO;
ExtrAbst rEAbst = ABST_MIN;
LONG lONr = INVALID_ONR;
ULONG lIdent = INVALID_IDENT;
CComVariant v;
	
	hr = VariantChangeType (&v, &vModeArg, 0, VT_I2);
	if (SUCCEEDED(hr)) rgType = (DistTyp)V_I2(&v);

	hr = VariantChangeType (&v, &vMinMaxArg, 0, VT_I2);
	if (SUCCEEDED(hr)) rEAbst = (ExtrAbst)V_I2(&v);

	VariantClear (pvObj);	// für alle Fälle
	hr = pICls -> get_Code ((LONG *)&lIdent);
	if (SUCCEEDED(hr)) {
		hr = Abstand -> DistanceObjOClass_ONr (
								GetValue(), lIdent, pdblDist, 
								rgType, rEAbst, &lONr); 
		if (SUCCEEDED(hr)) {
			V_VT(pvObj) = VT_DISPATCH;
			if (!m_pDoc -> FGetObjectDisp (lONr, (DGeoObject **)&V_DISPATCH(pvObj))) {
				V_VT(pvObj) = VT_ERROR;
				V_ERROR(&(*pvObj)) = E_UNEXPECTED;
			}
		}	
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Herauslösen eines TRiASCS aus einem Variant
HRESULT GetCSFromVariant (VARIANT &rvCS, ITRiASCS **ppICS)
{
	if (NULL == ppICS)
		return E_POINTER;
	*ppICS = NULL;

HRESULT hr = S_OK;

	COM_TRY {
	WTRiASCS CS;
	CComVariant v;

		if (VT_EMPTY == V_VT(&rvCS) && VT_NULL == V_VT(&rvCS)) {
			hr = S_FALSE;
		}
		if (SUCCEEDED(v.ChangeType(VT_UNKNOWN, &rvCS))) {
			THROW_FAILED_HRESULT(V_UNKNOWN(&v) -> QueryInterface(CS.ppi()));
		}
		else if (V_VT(&v) == (VT_ARRAY|VT_UI1)) {
		WTRiASCSStorageService StgSrv (CLSID_TRiASCSStorageService);
		WDispatch disp;

			THROW_FAILED_HRESULT(StgSrv -> StorageToObject(rvCS, disp.ppi()));
			CS = disp;
		}
		else if (SUCCEEDED(v.ChangeType(VT_BSTR, &rvCS))) {
			THROW_FAILED_HRESULT(CS.CreateInstance(CLSID_TRIASCS));
			THROW_FAILED_HRESULT(CS -> LoadFromFile(V_BSTR(&v)));
		}
		else {
			THROW_FAILED_HRESULT(E_INVALIDARG);
		}
		*ppICS = CS.detach();

	} COM_CATCH;
	return hr;
}

// Liefert ObjektTyp und Schwerpunktskoordinate eines Objektes ----------------
STDMETHODIMP CGeoObject::GetGeometryPt (double *pdblX, double *pdblY, 
	OBJECTTYPE *piOTyp)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::GetGeometryPt");

	if (NULL == piOTyp || NULL == pdblX || NULL == pdblY)
		return E_POINTER;

double dX = 0.0, dY = 0.0;

	if (GetGeometryPt (dX, dY)) {
		*pdblX = dX;
		*pdblY = dY;
		*piOTyp = BitsFromObjType(GetObjectType());
	} else {
		*piOTyp = OBJECTTYPE_Unknown;
		return S_FALSE;
	}

return NOERROR;
}

STDMETHODIMP CGeoObject::GetGeometryPtCS (VARIANT vCS, double *pdblX, 
	double *pdblY, OBJECTTYPE *piOTyp)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::GetGeometryPtCS");

	if (NULL == piOTyp || NULL == pdblX || NULL == pdblY)
		return E_POINTER;

WTRiASCS CS;
double dX = 0.0, dY = 0.0;

	RETURN_FAILED_HRESULT(GetCSFromVariant(vCS, CS.ppi()));
	if (GetGeometryPt (dX, dY, CS)) {
		*pdblX = dX;
		*pdblY = dY;
		*piOTyp = BitsFromObjType(GetObjectType());
	} else {
		*piOTyp = OBJECTTYPE_Unknown;
		return S_FALSE;
	}
	return NOERROR;
}

// ZugriffsKlassen auf CSafeArray ---------------------------------------------
DeclareSafeLock(double);
DeclareSafeLock(long);

STDMETHODIMP CGeoObject::GetGeometry (long *plCnt, VARIANT *pvXArr, 
	VARIANT *pvYArr, VARIANT *pvKCnt, VARIANT *pvConture, OBJECTTYPE *piOTyp)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::GetGeometry");

	if (NULL == plCnt || NULL == pvXArr || NULL == pvYArr || NULL == piOTyp)
		return E_POINTER;

	*plCnt = 0;		// für alle Fälle

// ObjektStatistik besorgen
short iKCnt = 0;
long lCnt = 0;
short iOTyp = GetStatistik (lCnt, iKCnt);

	*piOTyp = OBJECTTYPE_Unknown;
	if (iOTyp == OGUnknown) 
		return E_UNEXPECTED;

bool fResult = false;
CSafeArray saX (VT_R8, lCnt), saY (VT_R8, lCnt);	// Felder anlegen
CSafeArray saC (VT_I4, iKCnt);
	
	{
	CLockdouble X(saX), Y(saY);
	CLocklong C(saC);
		
		fResult = GetGeometry (iOTyp, lCnt, X, Y, iKCnt, C);
		if (!fResult) 
			return E_FAIL;
	} // Lock's aufheben
		
	*plCnt = lCnt;			// KoordinatenAnzahl
			
	VariantClear (pvXArr);		// FeldX
	V_VT(pvXArr) = VT_ARRAY|VT_R8;
	V_ARRAY(pvXArr) = saX.Detach();
		
	VariantClear (pvYArr);		// FeldY
	V_VT(pvYArr) = VT_ARRAY|VT_R8;
	V_ARRAY(pvYArr) = saY.Detach();
	
	if (NULL != pvKCnt) {
		V_VT(pvKCnt) = VT_I2;	// KonturAnzahl
		V_I4(pvKCnt) = iKCnt;
			
		if (pvConture) {	// KonturFeld
			VariantClear (pvConture);
			V_VT(pvConture) = VT_ARRAY|VT_I4;
			V_ARRAY(pvConture) = saC.Detach();
		}
	}
	*piOTyp = BitsFromObjType(iOTyp);

	return NOERROR;
}

STDMETHODIMP CGeoObject::GetGeometryCS (VARIANT vCS, long *plCnt, 
	VARIANT *pvXArr, VARIANT *pvYArr, VARIANT *pvKCnt, VARIANT *pvConture, 
	OBJECTTYPE *piOTyp)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::GetGeometryCS");

	if (NULL == plCnt || NULL == pvXArr || NULL == pvYArr || NULL == piOTyp)
		return E_POINTER;

	*plCnt = 0;		// für alle Fälle

// ObjektStatistik besorgen
short iKCnt = 0;
long lCnt = 0;
short iOTyp = GetStatistik (lCnt, iKCnt);

	*piOTyp = OBJECTTYPE_Unknown;
	if (iOTyp == OGUnknown) 
		return E_UNEXPECTED;

WTRiASCS CS;

	RETURN_FAILED_HRESULT(GetCSFromVariant(vCS, CS.ppi()));

bool fResult = false;
CSafeArray saX (VT_R8, lCnt), saY (VT_R8, lCnt);	// Felder anlegen
CSafeArray saC (VT_I4, iKCnt);
	
	{
	CLockdouble X(saX), Y(saY);
	CLocklong C(saC);
		
		fResult = GetGeometry (iOTyp, lCnt, X, Y, iKCnt, C, CS);
		if (!fResult) 
			return E_FAIL;
	} // Lock's aufheben
		
	*plCnt = lCnt;			// KoordinatenAnzahl
			
	VariantClear (pvXArr);		// FeldX
	V_VT(pvXArr) = VT_ARRAY|VT_R8;
	V_ARRAY(pvXArr) = saX.Detach();
		
	VariantClear (pvYArr);		// FeldY
	V_VT(pvYArr) = VT_ARRAY|VT_R8;
	V_ARRAY(pvYArr) = saY.Detach();
	
	if (NULL != pvKCnt) {
		V_VT(pvKCnt) = VT_I2;	// KonturAnzahl
		V_I4(pvKCnt) = iKCnt;
			
		if (pvConture) {	// KonturFeld
			VariantClear (pvConture);
			V_VT(pvConture) = VT_ARRAY|VT_I4;
			V_ARRAY(pvConture) = saC.Detach();
		}
	}
	*piOTyp = BitsFromObjType(iOTyp);
	return NOERROR;
}

bool RealCoords (LONG lX, LONG lY, double *pdblX, double *pdblY)
{
	TX_ASSERT(NULL != pdblX && NULL != pdblY);

COORDTRANSFORM CTF;
long lpt[2] = { lX, lY };
double dblpts[2];

	INITSTRUCT(CTF, COORDTRANSFORM);
	CTF.m_Pts = lpt;
	CTF.m_rcPts = dblpts;

	if (!DEX_OCtoRC(CTF))
		return false;

	*pdblX = dblpts[0];
	*pdblY = dblpts[1];

return true;
}

bool InternalCoords (double dblX, double dblY, LONG *plX, LONG *plY)
{
	TX_ASSERT(NULL != plX && NULL != plY);

COORDTRANSFORM CTF;
long lpt[2];
double dblpts[2] = { dblX, dblY };

	INITSTRUCT(CTF, COORDTRANSFORM);
	CTF.m_Pts = lpt;
	CTF.m_rcPts = dblpts;

	if (!DEX_RCtoOC (CTF))
		return false;

	*plX = lpt[0];
	*plY = lpt[1];
	return true;
}

STDMETHODIMP CGeoObject::GetGeometryRect ( 
	double *pdblXMin, double *pdblYMin, double *pdblXMax, double *pdblYMax,
	OBJECTTYPE *piOTyp)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::GetGeometryRect");

	if (NULL == piOTyp ||
		NULL == pdblXMin || NULL == pdblYMin || 
		NULL == pdblXMax || NULL == pdblYMax)
	{
		return E_POINTER;
	}

LONG lONr = GetValue();

	*piOTyp = BitsFromObjType(GetObjectType());
	*pdblXMin = 0.0;
	*pdblYMin = 0.0;
	*pdblXMax = 0.0;
	*pdblYMax = 0.0;
	if (INVALID_ONR == lONr) 
		return E_UNEXPECTED;

// ObjektContainer besorgen
long lCont[4];

	DEX_GetObjContainer (lONr, lCont);		// ObjektContainer holen

// Koordinaten transformieren
ObjContainer OC (lCont[0], lCont[1], lCont[2], lCont[3]);	// Container um unser Objekt

	if (!RealCoords (OC.XMin(), OC.YMin(), pdblXMin, pdblYMin) ||
		!RealCoords (OC.XMax(), OC.YMax(), pdblXMax, pdblYMax))
	{
		return E_UNEXPECTED;
	}

	return NOERROR;
}

STDMETHODIMP CGeoObject::GetGeometryRectCS ( 
	VARIANT vCS, double *pdblXMin, double *pdblYMin, double *pdblXMax, 
	double *pdblYMax, OBJECTTYPE *piOTyp)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::GetGeometryRectCS");

	if (NULL == piOTyp ||
		NULL == pdblXMin || NULL == pdblYMin || 
		NULL == pdblXMax || NULL == pdblYMax)
	{
		return E_POINTER;
	}

LONG lONr = GetValue();

	*piOTyp = BitsFromObjType(GetObjectType());
	*pdblXMin = 0.0;
	*pdblYMin = 0.0;
	*pdblXMax = 0.0;
	*pdblYMax = 0.0;
	if (INVALID_ONR == lONr) 
		return E_UNEXPECTED;

// Koordinatensystem instantiieren
WTRiASCS CS;

	RETURN_FAILED_HRESULT(GetCSFromVariant(vCS, CS.ppi()));

// ObjektContainer besorgen
OBJECTCONTAINER OC;

	INITSTRUCT (OC, OBJECTCONTAINER);
	OC.lONr = lONr;
	OC.pICS = CS;
	if (!DEX_GetObjContainerEx(OC))		// ObjektContainer holen
		return E_UNEXPECTED;

	*pdblXMin = OC.dXMin;
	*pdblYMin = OC.dYMin;
	*pdblXMax = OC.dXMax;
	*pdblYMax = OC.dYMax;
	return S_OK;
}

STDMETHODIMP CGeoObject::PutGeometryPt (
	OBJECTTYPE rgOTyp, double dX, double dY, VARIANT vMode, VARIANT_BOOL *pfResult)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::PutGeometryPt");

	if (NULL == pfResult) return E_POINTER;

CComVariant vModeArg; 
int iMode = MODGEOMETRY_ModObject;
HRESULT	hr = VariantChangeType (&vModeArg, &vMode, 0, VT_I4);

	if (SUCCEEDED(hr)) 
		iMode = V_I4(&vModeArg);

// iMode ist jetzt V_I4
	if (iMode & MODGEOMETRY_NoMemoryObject) {
		iMode &= ~MODGEOMETRY_NoMemoryObject;	// außen ists die 0x4000 und innen die 0x8000
		iMode |= OGNoMemoryObject;
	}

int iOTyp = ObjTypeFromBits (rgOTyp);
           
	*pfResult = PutGeometryPt (iOTyp, dX, dY, iMode) ? VARIANT_TRUE : VARIANT_FALSE;
	return NOERROR;
}

STDMETHODIMP CGeoObject::PutGeometry (OBJECTTYPE rgOTyp, 
	VARIANT vXArr, VARIANT vYArr, VARIANT vConture, 
	VARIANT vMode, VARIANT_BOOL *pfResult)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::PutGeometry");

	if (NULL == pfResult) return E_POINTER;

CComVariant vModeArg;
int iMode = MODGEOMETRY_ModObject;
HRESULT hr = VariantChangeType (&vModeArg, &vMode, 0, VT_I4);

	if (SUCCEEDED(hr)) 
		iMode = V_I4(&vModeArg);

// iMode ist jetzt V_I4
	if (iMode & MODGEOMETRY_NoMemoryObject) {
		iMode &= ~MODGEOMETRY_NoMemoryObject;	// außen ists die 0x4000 und innen die 0x8000
		iMode |= OGNoMemoryObject;
	}

	if ((V_VT(&vXArr) != (VT_ARRAY|VT_R8)) || (V_VT(&vYArr) != (VT_ARRAY|VT_R8)))
		return DISP_E_BADVARTYPE;

CSafeArray saX (VT_R8), saY (VT_R8);	// Felder anlegen
bool fResult = false;

	if (!saX.Attach(V_ARRAY(&vXArr), true) || !saY.Attach(V_ARRAY(&vYArr), true))
		return E_UNEXPECTED;

	{
	CLockdouble X(saX), Y(saY);
	CSafeArray *psaC = NULL;

		if (V_VT(&vConture) == (VT_ARRAY|VT_I4)) {
			psaC = new CSafeArray (VT_I4);
			if (psaC) psaC -> Attach (V_ARRAY(&vConture), true);
		} else
			psaC = new CSafeArray (VT_I4, 1);

		if (psaC) {
		CLocklong C(*psaC);

			if (!psaC -> IsAttached()) 
				*C = X.Size();

		int iOType = ObjTypeFromBits (rgOTyp);
		long lCnt = X.Size();

		// Punkte etc. haben nur eine Koordinate (evtl. unnötiges ReDim überflüssig machen)
			if (OGPunkt == iOType || OGText == iOType)
				lCnt = 1;	

			fResult = PutGeometry (iOType, lCnt, X, Y, short(C.Size()), C, iMode);
		} // Lock aufheben
		DELETE_OBJ (psaC);
	}
	*pfResult = fResult;
	return NOERROR;
}

STDMETHODIMP CGeoObject::PutGeometryPtCS (
	VARIANT vCS, OBJECTTYPE rgOTyp, double dX, double dY, VARIANT vMode, 
	VARIANT_BOOL *pfResult)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::PutGeometryPtCS");

	if (NULL == pfResult) return E_POINTER;

CComVariant vModeArg; 
int iMode = MODGEOMETRY_ModObject;
HRESULT	hr = VariantChangeType (&vModeArg, &vMode, 0, VT_I4);

	if (SUCCEEDED(hr)) 
		iMode = V_I4(&vModeArg);

// iMode ist jetzt V_I4
	if (iMode & MODGEOMETRY_NoMemoryObject) {
		iMode &= ~MODGEOMETRY_NoMemoryObject;	// außen ists die 0x4000 und innen die 0x8000
		iMode |= OGNoMemoryObject;
	}

int iOTyp = ObjTypeFromBits (rgOTyp);
WTRiASCS CS;

	RETURN_FAILED_HRESULT(GetCSFromVariant(vCS, CS.ppi()));
	*pfResult = PutGeometryPt (iOTyp, dX, dY, iMode, CS) ? VARIANT_TRUE : VARIANT_FALSE;
	return NOERROR;
}

STDMETHODIMP CGeoObject::PutGeometryCS (VARIANT vCS, OBJECTTYPE rgOTyp, 
	VARIANT vXArr, VARIANT vYArr, VARIANT vConture, 
	VARIANT vMode, VARIANT_BOOL *pfResult)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::PutGeometryCS");

	if (NULL == pfResult) return E_POINTER;

CComVariant vModeArg;
int iMode = MODGEOMETRY_ModObject;
HRESULT hr = VariantChangeType (&vModeArg, &vMode, 0, VT_I4);

	if (SUCCEEDED(hr)) 
		iMode = V_I4(&vModeArg);

// iMode ist jetzt V_I4
	if (iMode & MODGEOMETRY_NoMemoryObject) {
		iMode &= ~MODGEOMETRY_NoMemoryObject;	// außen ists die 0x4000 und innen die 0x8000
		iMode |= OGNoMemoryObject;
	}

	if ((V_VT(&vXArr) != (VT_ARRAY|VT_R8)) || (V_VT(&vYArr) != (VT_ARRAY|VT_R8)))
		return DISP_E_BADVARTYPE;

CSafeArray saX (VT_R8), saY (VT_R8);	// Felder anlegen
bool fResult = false;

	if (!saX.Attach(V_ARRAY(&vXArr), true) || !saY.Attach(V_ARRAY(&vYArr), true))
		return E_UNEXPECTED;

	{
	CLockdouble X(saX), Y(saY);
	CSafeArray *psaC = NULL;

		if (V_VT(&vConture) == (VT_ARRAY|VT_I4)) {
			psaC = new CSafeArray (VT_I4);
			if (psaC) psaC -> Attach (V_ARRAY(&vConture), true);
		} else
			psaC = new CSafeArray (VT_I4, 1);

		if (psaC) {
		CLocklong C(*psaC);

			if (!psaC -> IsAttached()) 
				*C = X.Size();

		int iOType = ObjTypeFromBits (rgOTyp);
		long lCnt = X.Size();

		// Punkte etc. haben nur eine Koordinate (evtl. unnötiges ReDim überflüssig machen
			if (OGPunkt == iOType || OGText == iOType)
				lCnt = 1;	

		WTRiASCS CS;

			RETURN_FAILED_HRESULT(GetCSFromVariant(vCS, CS.ppi()));
			fResult = PutGeometry (iOType, lCnt, X, Y, short(C.Size()), C, iMode, CS);
		} // Lock aufheben
		DELETE_OBJ (psaC);
	}
	*pfResult = fResult;
	return NOERROR;
}

STDMETHODIMP CGeoObject::GetText (BSTR *pbstrText)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::GetText");

int iOTyp = GetObjectType();

	if (OGText != iOTyp && OGLabel != iOTyp)
		return E_FAIL;		// nur Textobjekte behandeln (yet)

	if (GetTextObjectText (pbstrText))
		return S_OK;

	return E_FAIL;
}

STDMETHODIMP CGeoObject::PutText (BSTR bstrText)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::PutText");

int iOTyp = GetObjectType();

	if (OGText != iOTyp && OGLabel != iOTyp)
		return E_FAIL;		// nur Textobjekte behandeln (yet)

	if (PutTextObjectText (bstrText))
		return S_OK;
	
	return E_FAIL;
}

STDMETHODIMP CGeoObject::TopRelation (DGeoObject *pIObj, TOPRELATION *prgRTyp)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::TopRelation");

	TEST_E_POINTER("CGeoObject::TopRelation", prgRTyp);

	*prgRTyp = (TOPRELATION)REL_UNKLAR;

Relat rpType = REL_UNKLAR;
WExtendTopRel2 ITopoRel;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetITopoRel (ITopoRel.ppi());

	if (FAILED(hr)) return hr;
		
// Topologische Relation bestimmen
	if (SUCCEEDED(hr)) {
	LONG lONr = INVALID_ONR;

		hr = pIObj -> get_Value(&lONr);
		if (SUCCEEDED(hr))
			hr = ITopoRel -> TopoRelationObjObj_ONr (GetValue(), lONr, &rpType);

		if (SUCCEEDED(hr)) {
			*prgRTyp = (TOPRELATION)rpType;
			return S_OK;
		}
	}
	return hr;
}

// Liefert eine Collection von GeoObjects, die durch Buffering entstanden sind
inline bool _GetObjectsEnum (CGeoDoc *pDoc, LONG lONr, CGeoObjectCreator &rCollCr)
{
CGeoObject *pObject = pDoc -> FGetObjectDisp (lONr);

	if (NULL != pObject && NULL != rCollCr.InsertPtr (pObject)) 
		((_DGeoObject *)pObject) -> AddRef();

	return true;
}

// INITOBJCOLLECTIONPROC ------------------------------------------------------
extern "C" INITOBJSTATUS PASCAL GetObjectsFromEnum (
		LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
		container_wrappers::CCreator &rCollCr, DWORD dwData, long *plONr)
{
	if (plONr == NULL) {
	// fill all objects
	IEnumLONG *pIEnum = (IEnumLONG *)dwData;
	LONG lONr = INVALID_ONR;

		if (NULL == pIEnum)
			return INITOBJSTATUS_Exists;	// kein Enum-->leeres GeoObjects-Objekt

		for (pIEnum -> Reset(); S_OK == pIEnum -> Next (1, &lONr, NULL); /**/)
		{
			if (!_GetObjectsEnum (pDoc, lONr, (CGeoObjectCreator &)rCollCr))
				return INITOBJSTATUS_Error;
		}

		return INITOBJSTATUS_Exists;
	} else if (*plONr != INVALID_ONR) {
	// fill only one object
		if (_GetObjectsEnum (pDoc, *plONr, (CGeoObjectCreator &)rCollCr))
			return INITOBJSTATUS_Exists;
	} 

return INITOBJSTATUS_Error;		// error !
}

STDMETHODIMP CGeoObject::GetTopRelationObjects (TOPRELATION rgRelTyp, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::GetTopRelationObjects");

	TEST_E_POINTER("CGeoObject::GetTopRelationObjects", ppIObjs);

// TopoRelExtension nach allen entsprechenden Objekten befragen
WExtendTopRel2 TopoRel;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetITopoRel (TopoRel.ppi());

	if (FAILED(hr)) return hr;
		
// Topologische Relation bestimmen
IEnumLONG *pIEnum = NULL;

	if (SUCCEEDED(hr)) {
		hr = TopoRel -> GetObjectsObj_ONr (GetValue(), (enum Relat)rgRelTyp, &pIEnum);

		if (FAILED(hr)) {
			if (pIEnum) pIEnum -> Release();
			return hr;
		}
	}

// jetzt Collection der GeoObjects generieren
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(_DGeoObject *)this, m_pApp, m_pDoc,
							GetObjectsFromEnum, (DWORD)pIEnum, NULL);

// Resultat vorbereiten
	if (NULL == pCObjects) return E_OUTOFMEMORY;

// Enumerator freigeben	
	pCObjects -> m_dwData = NULL;
	if (pIEnum) pIEnum -> Release(); 

	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

STDMETHODIMP CGeoObject::GetBufferObjects (THIS_ double dWidth, 
	VARIANT vCount, VARIANT vFullCircle, VARIANT vIdent, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::GetBufferObjects");

	TEST_E_POINTER("CGeoObject::GetBufferObjects", ppIObjs);

// BufferExtension nach allen entsprechenden Objekten befragen
WExtendBuffer Buffer;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetIBuffer (Buffer.ppi());

	if (FAILED(hr)) return hr;
		
// Buffer um dieses Objekt legen, Objekte in Collection liefern
IEnumLONG *pIEnum = NULL;

// Parameter extrahieren
CComVariant vaCount;
CComVariant vaType;
CComVariant vaIdent;

int iCount = 1;
PuffBau rgBuffType = PBAU_RING;
ULONG ulIdent = INVALID_IDENT;

	if (SUCCEEDED(VariantChangeType (&vaCount, &vCount, NULL, VT_I2))) 
		iCount = V_I2(&vaCount);
	if (SUCCEEDED(VariantChangeType (&vaType, &vFullCircle, NULL, VT_I2))) 
		rgBuffType = (enum PuffBau)V_I2(&vaType);

	if (SUCCEEDED(vaIdent.ChangeType (VT_DISPATCH, &vIdent)) && NULL != V_DISPATCH(&vaIdent)) {
		try {
		// IDispatch (DGeoClass ?)
		WDGeoClass Cls (V_DISPATCH(&vaIdent));	// throws hr

			THROW_FAILED_HRESULT(Cls -> get_Code((LONG *)&ulIdent));

		} catch (_com_error &e) {
			return _COM_ERROR(e);
		}
	} else if (SUCCEEDED(vaIdent.ChangeType (VT_I4, &vIdent))) {
		ulIdent = V_I4(&vaIdent);
	} else
		ulIdent = GetObjIdentEx();

// jetzt gehts los
	if (SUCCEEDED(hr)) {
		hr = Buffer -> RealBuffering_ONr (
					GetValue(), dWidth, iCount, rgBuffType, 
					SFORM_PERM, ulIdent, &pIEnum);
		
		if (FAILED(hr)) {
			if (pIEnum) pIEnum -> Release();
			return hr;
		}
	}

// jetzt Collection der GeoObjects generieren
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(DGeoObject *)this, m_pApp, m_pDoc,
							GetObjectsFromEnum, (DWORD)pIEnum, NULL);

// Resultat vorbereiten
	if (NULL == pCObjects) return E_OUTOFMEMORY;

// Enumerator freigeben	
	pCObjects -> m_dwData = NULL;
	if (pIEnum) pIEnum -> Release(); 

	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

STDMETHODIMP CGeoObject::GetBufferObjectEx (
	double dblWidth, VARIANT vFullCircle, VARIANT vSide, VARIANT vConvexMode, 
	VARIANT vPrecision, DGeoObject **ppIObj)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::GetBufferObjectEx");

	TEST_E_POINTER("CGeoObject::GetBufferObjects", ppIObj);

// BufferExtension nach allen entsprechenden Objekten befragen
WExtendBuffer Buffer;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetIBuffer (Buffer.ppi());

	if (FAILED(hr)) return hr;
		
// Buffer um dieses Objekt legen, Objekte in Collection liefern
IEnumLONG *pIEnum = NULL;

// Parameter extrahieren
CComVariant vaType;
CComVariant vaSide;
CComVariant vaMode;
CComVariant vaPrec;

PuffBau rgBuffType = PBAU_RING;
BuffSide rgBuffSide = BUFF_BOTH;
ConvexMode rgConvexMode = BUFF_ARC;
double dPrec = dblWidth/10.0;

	if (SUCCEEDED(vaType.ChangeType (VT_I2, &vFullCircle))) 
		rgBuffType = (enum PuffBau)V_I2(&vaType);
	if (SUCCEEDED(vaSide.ChangeType (VT_I2, &vSide))) 
		rgBuffSide = (enum BuffSide)V_I2(&vaSide);
	if (SUCCEEDED(vaMode.ChangeType (VT_I2, &vConvexMode))) 
		rgConvexMode = (enum ConvexMode)V_I2(&vaMode);
	if (SUCCEEDED(vaPrec.ChangeType (VT_R8, &vPrecision))) 
		dPrec = V_R8(&vaPrec);

// jetzt gehts los
	if (SUCCEEDED(hr)) {
	LONG lNewONr = 0L;

		hr = Buffer -> WorkingBuffer_ONr (
					GetValue(), dblWidth, rgBuffType, rgBuffSide, rgConvexMode, dPrec, &lNewONr);
		if (SUCCEEDED(hr)) {
			if (!m_pDoc -> FGetObjectDisp (lNewONr, ppIObj)) 
				hr = E_UNEXPECTED;
		}	
	}
	return hr;
}

STDMETHODIMP CGeoObject::GetCircleBufferObjects (THIS_ double dWidth, 
	VARIANT vCount, VARIANT vFullCircle, VARIANT vIdent, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::GetCircleBufferObjects");

	TEST_E_POINTER("CGeoObject::GetCircleBufferObjects", ppIObjs);

// BufferExtension nach allen entsprechenden Objekten befragen
WExtendBuffer Buffer;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetIBuffer (Buffer.ppi());

	if (FAILED(hr)) return hr;
		
// Buffer um dieses Objekt legen, Objekte in Collection liefern
IEnumLONG *pIEnum = NULL;

// Parameter extrahieren
CComVariant vaCount;
CComVariant vaType;
CComVariant vaIdent;

int iCount = 1;
PuffBau rgBuffType = PBAU_VOLL;
ULONG ulIdent = INVALID_IDENT;

	if (SUCCEEDED(VariantChangeType (&vaCount, &vCount, NULL, VT_I2))) 
		iCount = V_I2(&vaCount);
	if (SUCCEEDED(VariantChangeType (&vaType, &vFullCircle, NULL, VT_I2))) 
		rgBuffType = (enum PuffBau)V_I2(&vaType);
	if (FAILED(VariantChangeType (&vaIdent, &vIdent, NULL, VT_I4))) 
		ulIdent = GetObjIdentEx();
	else
		ulIdent = V_I4(&vaIdent);

// jetzt gehts los
	if (SUCCEEDED(hr)) {
		hr = Buffer -> CircularBuffering_ONr (
					GetValue(), dWidth, iCount, rgBuffType, 
					SFORM_PERM, ulIdent, &pIEnum);
		
		if (FAILED(hr)) {
			if (pIEnum) pIEnum -> Release();
			return hr;
		}
	}

// jetzt Collection der GeoObjects generieren
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(DGeoObject *)this, m_pApp, m_pDoc,
							GetObjectsFromEnum, (DWORD)pIEnum, NULL);

// Resultat vorbereiten
	if (NULL == pCObjects)  return E_OUTOFMEMORY;

// Enumerator freigeben	
	pCObjects -> m_dwData = NULL;
	if (pIEnum) pIEnum -> Release(); 

	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

STDMETHODIMP CGeoObject::RePaint (VARIANT vComplete)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::RePaint");

VARIANTARG vFlag; VariantInit (&vFlag);

HRESULT hr = VariantChangeType (&vFlag, &vComplete, 0, VT_BOOL);
bool fComplete = true;

	if (SUCCEEDED(hr)) fComplete = V_BOOL(&vFlag);
	RePaint (fComplete);
	return NOERROR;
}



// DELETEFEATCOLLECTIONPROC ----------------------------------------------------
extern "C" 
bool PASCAL _XTENSN_EXPORT DeleteFeatureFromObject (LPCSTR bName, void *pObj)
{
	return ((CGeoObject *)pObj) -> FDelFeature (bName);
}


// Liefert eine Collection von GeoFeature's, die zu diesem Objekt gehören ----------------------
typedef struct tagENUMFEATUREDATA {
	CGeoFeatureBaseCreator *m_pCr;
	LPUNKNOWN m_pUnk;
	CTriasApp *m_pApp;
	CGeoDoc *m_pDoc;
	CGeoObject *m_pGeoObject;
	IObjectProperty *m_pIObjProp;
	DWORD m_dwFlags;
} ENUMFEATUREDATA;

extern "C" 
BOOL PASCAL _XTENSN_EXPORT _GetFeaturesFromObject (ENUMFEATUREDATA *pEFD)
{
char cbBuffer[_MAX_PATH+1];
DWORD dwFlags = (DWORD)PROPCAPS_NONE;
HRESULT hr = pEFD -> m_pIObjProp -> GetPropInfo (cbBuffer, _MAX_PATH, &dwFlags);

	if (FAILED(hr)) return false;

	if (dwFlags & PROPCAPS_INTERACTIVE)
		return true;	// interaqktive niemals nicht
	if ((PROPCAPS_NONE != pEFD -> m_dwFlags) && !(dwFlags & pEFD -> m_dwFlags))
		return true;	// welche, die wir nicht haben wollen auch nicht

CGeoFeatureBase *pFeature = pEFD -> m_pGeoObject -> FGetFeatureDisp (
					cbBuffer, NULL, (PROPCAPS)dwFlags, FEATUREMODE_Get, NULL, pEFD -> m_pIObjProp);

	if (pFeature && pEFD -> m_pCr -> InsertPtr (pFeature)) 
		((_DGeoFeature *)pFeature) -> AddRef(); 
	
	return true;
}

extern "C" 
INITFEATSTATUS PASCAL _CreateFeatureObject (ENUMFEATUREDATA *pEFD, string &bName)
{
CGeoFeatureBase *pFeature = pEFD -> m_pGeoObject -> FGetFeatureDisp (bName.c_str());
INITFEATSTATUS iResult = INITFEATSTATUS_Exists;

	if (pFeature == NULL) {
		pFeature = pEFD -> m_pGeoObject -> FGetFeatureDisp (
						bName.c_str(), NULL, PROPCAPS_NONE, FEATUREMODE_Add);
		iResult = INITFEATSTATUS_Created;
	}
	
	if (pFeature && pEFD -> m_pCr -> InsertPtr (pFeature)) {
		((_DGeoFeature *)pFeature) -> AddRef();
		return iResult;
	}
	return INITFEATSTATUS_Error;
}

// INITFEATCOLLECTIONPROC
extern "C" 
INITFEATSTATUS PASCAL GetFeaturesFromObject (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	void *pObj, container_wrappers::CCreator &rCollCr, DWORD dwData, 
	string *pbName, DWORD dwFlags)
{
ENUMFEATUREDATA EFD;

	EFD.m_pCr = (CGeoFeatureBaseCreator *)&rCollCr;
	EFD.m_pUnk = pUnk;
	EFD.m_pApp = pApp;
	EFD.m_pDoc = pDoc;
	EFD.m_pGeoObject = (CGeoObject *)pObj;
	EFD.m_pIObjProp = NULL;
	EFD.m_dwFlags = dwFlags;

	if (pbName == NULL) {							// Complete fill
	IEnumObjProps *pIEnum = NULL;
	HRESULT hr = pApp -> GetEnumObjProps ((long)dwData, &pIEnum);

		if (FAILED(hr)) return INITFEATSTATUS_Error;

	IObjectProperty *pIObjProp = NULL;
														 
		for (pIEnum -> Reset(); S_OK == pIEnum -> Next (1, (LPUNKNOWN *)&pIObjProp, NULL); /**/)
		{
			EFD.m_pIObjProp = pIObjProp;
			_GetFeaturesFromObject (&EFD);
			pIObjProp -> Release();
		}
		if (pIEnum) pIEnum -> Release(); 
		
		return INITFEATSTATUS_Exists;
	} else 
		return _CreateFeatureObject (&EFD, *pbName);

	return INITFEATSTATUS_Error;		
}

STDMETHODIMP CGeoObject::GetFeatures (VARIANT vFeatures, VARIANT /*vLogMode*/, DGeoFeatures **ppIFeats)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::GetFeatures");

	TEST_E_POINTER("CGeoObject::GetFeatures", ppIFeats);

CComVariant vWhich;
DWORD dwFlags = PROPCAPS_NONE;

	if (SUCCEEDED(vWhich.ChangeType (VT_I4, &vFeatures)))
		dwFlags = V_I4(&vWhich);

CGeoFeatures *pCFeatures = CGeoFeatures::CreateInstance (
							(DGeoObject *)this, m_pApp, m_pDoc,
							this, GetFeaturesFromObject, (DWORD)GetValue(),
							DeleteFeatureFromObject, dwFlags); 

	if (NULL == pCFeatures) return E_OUTOFMEMORY;

	*ppIFeats = (DGeoFeatures *)pCFeatures;
	return S_OK;
}

STDMETHODIMP CGeoObject::GetFeature (
	VARIANT vFeature, VARIANT vMode, VARIANT vProps, DGeoFeature **ppIFeat)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF1(1, "OleAuto: %s", "CGeoObject::GetFeature");

	TEST_E_POINTER("CGeoObject::GetFeature", ppIFeat);

CComVariant vArg, vArgMode, vArgProps;

HRESULT hr = vArgMode.ChangeType (VT_I4, &vMode);
FEATUREMODE rgMode = FEATUREMODE_Get;

	if (SUCCEEDED(hr)) 
		rgMode = (FEATUREMODE)V_I4(&vArgMode);
		
PROPCAPS rgProps = PROPCAPS_NONE;

	hr = vArgProps.ChangeType (VT_I4, &vProps);
	if (SUCCEEDED(hr))
		rgProps = (PROPCAPS)V_I4(&vArgProps);

	hr = vArg.ChangeType (VT_BSTR, &vFeature);	// Feature name as string
	if (SUCCEEDED(hr)) {
	string strName (AnsiString(V_BSTR(&vArg)));

	// wenn neu erzeugen, dann ohne Schreibschutz, ansonsten bringts keinen Sinn
		if (FEATUREMODE_Add == rgMode)
			rgProps = (PROPCAPS)(rgProps | PROPCAPS_NOTREADONLY);

		switch (rgMode) {
		case FEATUREMODE_Get:		// get default
		case FEATUREMODE_Replace:	// remove old, create new
		case FEATUREMODE_Add:		// create, if not existent
			{
			CGeoFeatureBase *pFeature = FGetFeatureDisp (
					strName.c_str(), ppIFeat, rgProps, rgMode);

				if (NULL == pFeature) 
					return E_UNEXPECTED;
			}
			break;

		case  FEATUREMODE_Remove:		// remove item  tut 
			FDelFeature (strName.c_str());
			*ppIFeat = NULL;
			break;
			
		default:
			return E_UNEXPECTED;
		}

		D_OUTF1(1, "%s", strName.c_str());
		return NOERROR;
	}

	return hr;
}

STDMETHODIMP CGeoObject::AddFeature (
	VARIANT vFeature, VARIANT vProps, VARIANT vOptData, DGeoFeature **ppIFeat)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF1(1, "OleAuto: %s", "CGeoObject::AddFeature");

	TEST_E_POINTER("CGeoObject::AddFeature", ppIFeat);

CComVariant vArg, vArgProps;

FEATUREMODE rgMode = FEATUREMODE_Add;
PROPCAPS rgProps = PROPCAPS_NONE;
HRESULT hr = vArgProps.ChangeType (VT_I4, &vProps);

	if (SUCCEEDED(hr))
		rgProps = (PROPCAPS)V_I4(&vArgProps);

	hr = vArg.ChangeType (VT_BSTR, &vFeature);	// Feature name as string
	if (SUCCEEDED(hr)) {

		USES_CONVERSION;

	string strName (OLE2A(V_BSTR(&vArg)));

		D_OUTF1(1, "%s", strName.c_str());

	CGeoFeatureBase *pFeature = FGetFeatureDisp (
			strName.c_str(), ppIFeat, rgProps, FEATUREMODE_Add, &vOptData);

		if (NULL == pFeature) 
			return E_UNEXPECTED;
	}
	return hr;
}

STDMETHODIMP CGeoObject::RemoveFeature (VARIANT vFeature)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::RemoveFeature");

CComVariant vArg;
HRESULT hr = vArg.ChangeType (VT_BSTR, &vFeature);	// Feature name as string

	if (FAILED(hr)) return hr;

	USES_CONVERSION;
	D_OUTF1(1, "%s", OLE2A(V_BSTR(&vArg)));
	return FDelFeature (OLE2A(V_BSTR(&vArg))) ? S_OK : E_FAIL;
}

// Liefert einen Enumerator, der ein Objekt enthält ---------------------------
HRESULT CGeoObject::GetEnumFromONr (LONG lONr, IEnumLONG **ppIEnum, bool fAddMe)
{
SEnumLONG *pEnumLONG = NULL;

	*ppIEnum = NULL;

	TRY {
		pEnumLONG = new SEnumLONG;
	} CATCH (CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH
	
	try {
	HRESULT hr = pEnumLONG -> AddItem (lONr);

		if (FAILED(hr))	_com_issue_error(hr);
		if (fAddMe) {
			hr = pEnumLONG -> AddItem (GetValue());
			if (FAILED(hr)) _com_issue_error(hr);
		}

	} catch (_com_error& hr) {
		DELETE_OBJ(pEnumLONG);
		return _COM_ERROR(hr);
	}

	*ppIEnum = (IEnumLONG *)pEnumLONG;		// übernimmt RefCnt

return NOERROR;
}

STDMETHODIMP CGeoObject::GetIntersectObjects (DGeoObject *pIObj, VARIANT vMode, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::GetIntersectObjects");

	TEST_E_POINTER("CGeoObject::GetIntersectObjects", ppIObjs);

// ObjOperExtension nach allen entsprechenden Objekten befragen
WExtendObjOper ObjOper;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetIObjOper (ObjOper.ppi());

	if (FAILED(hr)) return hr;
		
// Dieses Objekt als schneidendes verwenden, Objekte in Collection liefern
IEnumLONG *pIEnum = NULL;			// Resultat
WEnumLONG EnumIn;					// AusgangsMenge

// Parameter extrahieren
CComVariant vaMode;
int iMode = LINN;
LONG lONr = INVALID_ONR;

	hr = pIObj -> get_Value (&lONr);
	if (FAILED(hr)) return hr;

	hr = GetEnumFromONr (lONr, EnumIn.ppi());
	if (FAILED(hr)) return hr;

	if (SUCCEEDED(vaMode.ChangeType (VT_I2, &vMode))) 
		iMode = V_I2(&vaMode);
	if (0 == iMode) iMode = LINN;	// default ist innerhalb

// jetzt gehts los
	hr = ObjOper -> SectionObjObjs_ONr (GetValue(), EnumIn, 
									   iMode, SFORM_PERM, &pIEnum);
	if (FAILED(hr)) {
		if (pIEnum) pIEnum -> Release();
		return hr;
	}

// jetzt Collection der GeoObjects generieren
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(DGeoObject *)this, m_pApp, m_pDoc,
							GetObjectsFromEnum, (DWORD)pIEnum, NULL);

// Resultat vorbereiten
	if (NULL == pCObjects) return E_OUTOFMEMORY;

// Enumerator freigeben	
	pCObjects -> m_dwData = NULL;
	if (pIEnum) pIEnum -> Release(); 

	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

STDMETHODIMP CGeoObject::GetIntersectObjectsCollection (
	DGeoObjects *pIObjs, VARIANT vMode, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::GetIntersectObjectsCollection");

	TEST_E_POINTER("CGeoObject::GetIntersectObjectsCollection", ppIObjs);

// ObjOperExtension nach allen entsprechenden Objekten befragen
WExtendObjOper ObjOper;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetIObjOper (ObjOper.ppi());

	if (FAILED(hr)) return hr;
		
// Dieses Objekt als schneidendes verwenden, Objekte in Collection liefern
IEnumLONG *pIEnum = NULL;			// Resultat
WEnumLONG EnumIn;					// AusgangsMenge

// Parameter extrahieren
CComVariant vaMode;
int iMode = LINN;

// Objektmenge gegeben (DGeoObjects *)
	hr = GetEnumLongFromGeoObjects (pIObjs, EnumIn.ppi());
	if (FAILED(hr)) return hr;

	if (SUCCEEDED(vaMode.ChangeType (VT_I2, &vMode))) 
		iMode = V_I2(&vaMode);

// jetzt gehts los
	hr = ObjOper -> SectionObjObjs_ONr (GetValue(), EnumIn, 
									   iMode, SFORM_PERM, &pIEnum);
	if (FAILED(hr)) {
		if (pIEnum) pIEnum -> Release();
		return hr;
	}

// jetzt Collection der GeoObjects generieren
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(_DGeoObject *)this, m_pApp, m_pDoc,
							GetObjectsFromEnum, (DWORD)pIEnum, NULL);

// Resultat vorbereiten
	if (NULL == pCObjects)  return E_OUTOFMEMORY;

// Enumerator freigeben	
	pCObjects -> m_dwData = NULL;
	if (pIEnum) pIEnum -> Release(); 

	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

STDMETHODIMP CGeoObject::GetIntersectObjectsClass (
	DGeoClass *pICls, VARIANT vMode, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::GetIntersectObjectsClass");

	TEST_E_POINTER("CGeoObject::GetIntersectObjectsClass", ppIObjs);

// ObjOperExtension nach allen entsprechenden Objekten befragen
WExtendObjOper ObjOper;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetIObjOper (ObjOper.ppi());

	if (FAILED(hr)) return hr;
		
// Dieses Objekt als schneidendes verwenden, Objekte in Collection liefern
IEnumLONG *pIEnum = NULL;		// Resultat

// Parameter extrahieren
CComVariant vaMode;
int iMode = LINN;

	if (SUCCEEDED(vaMode.ChangeType (VT_I2, &vMode))) 
		iMode = V_I2(&vaMode);

ULONG ulIdent = INVALID_IDENT;

	hr = pICls -> get_Code((LONG *)&ulIdent);
	if (FAILED(hr)) return hr;

// jetzt gehts los
	hr = ObjOper -> SectionObjOClass_ONr (GetValue(), ulIdent, 
										 iMode, SFORM_PERM, &pIEnum);
	if (FAILED(hr)) {
		if (pIEnum) pIEnum -> Release();
		return hr;
	}

// jetzt Collection der GeoObjects generieren
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(DGeoObject *)this, m_pApp, m_pDoc,
							GetObjectsFromEnum, (DWORD)pIEnum, NULL);

// Resultat vorbereiten
	if (NULL == pCObjects) return E_OUTOFMEMORY;

// Enumerator freigeben	
	pCObjects -> m_dwData = NULL;
	if (pIEnum) pIEnum -> Release(); 

	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

STDMETHODIMP CGeoObject::GeometryIntersection (
	DGeoObject *pIObj, VARIANT vIdent, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::GeometryIntersection");

	TEST_E_POINTER("CGeoObject::GeometryIntersection", ppIObjs);

// ObjOperExtension nach allen entsprechenden Objekten befragen
WExtendObjOper ObjOper;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetIObjOper (ObjOper.ppi());

	if (FAILED(hr)) return hr;
		
// Dieses Objekt und das übergebene in Enumerator speichern
// Objekte in Collection liefern
IEnumLONG *pIEnum = NULL;		// Resultat
WEnumLONG EnumIn;

// Parameter extrahieren
CComVariant vaIdent; 
ULONG ulIdent = INVALID_IDENT;

	if (SUCCEEDED(vaIdent.ChangeType (VT_DISPATCH, &vIdent)) && NULL != V_DISPATCH(&vaIdent)) {
		try {
		// IDispatch (DGeoClass ?)
		WDGeoClass Cls (V_DISPATCH(&vaIdent));	// throws hr

			THROW_FAILED_HRESULT(Cls -> get_Code((LONG *)&ulIdent));

		} catch (_com_error &e) {
			return _COM_ERROR(e);
		}
	} else if (SUCCEEDED(vaIdent.ChangeType (VT_I4, &vIdent))) {
		ulIdent = V_I4(&vaIdent);
	} else
		ulIdent = GetObjIdentEx();

LONG lONr = INVALID_ONR;

	hr = pIObj -> get_Value (&lONr);
	if (FAILED(hr)) return hr;

	hr = GetEnumFromONr (lONr, EnumIn.ppi(), true);
	if (FAILED(hr)) return hr;

// jetzt gehts los
	hr = ObjOper -> AndArea (EnumIn, ulIdent, SFORM_PERM, &pIEnum);
	if (FAILED(hr)) {
		if (pIEnum) pIEnum -> Release();
		return hr;
	}

// jetzt Collection der GeoObjects generieren
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(DGeoObject *)this, m_pApp, m_pDoc,
							GetObjectsFromEnum, (DWORD)pIEnum, NULL);

// Resultat vorbereiten
	if (NULL == pCObjects) return E_OUTOFMEMORY;

// Enumerator freigeben	
	pCObjects -> m_dwData = NULL;
	if (pIEnum) pIEnum -> Release(); 

	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

STDMETHODIMP CGeoObject::GeometryUnion (DGeoObject *pIObj, VARIANT vIdent, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::GeometryUnion");

	TEST_E_POINTER("CGeoObject::GeometryUnion", ppIObjs);

// ObjOperExtension nach allen entsprechenden Objekten befragen
WExtendObjOper ObjOper;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetIObjOper (ObjOper.ppi());

	if (FAILED(hr)) return hr;
		
// Dieses Objekt und das übergebene in Enumerator speichern
// Objekte in Collection liefern
IEnumLONG *pIEnum = NULL;		// Resultat
WEnumLONG EnumIn;

// Parameter extrahieren
CComVariant vaIdent; 
ULONG ulIdent = INVALID_IDENT;

	if (SUCCEEDED(vaIdent.ChangeType (VT_DISPATCH, &vIdent)) && NULL != V_DISPATCH(&vaIdent)) {
		try {
		// IDispatch (DGeoClass ?)
		WDGeoClass Cls (V_DISPATCH(&vaIdent));	// throws hr

			THROW_FAILED_HRESULT(Cls -> get_Code((LONG *)&ulIdent));

		} catch (_com_error &e) {
			return _COM_ERROR(e);
		}
	} else if (SUCCEEDED(vaIdent.ChangeType (VT_I4, &vIdent))) {
		ulIdent = V_I4(&vaIdent);
	} else
		ulIdent = GetObjIdentEx();

LONG lONr = INVALID_ONR;

	hr = pIObj -> get_Value (&lONr);
	if (FAILED(hr)) return hr;

	hr = GetEnumFromONr (lONr, EnumIn.ppi(), true);
	if (FAILED(hr)) return hr;

// jetzt gehts los
	hr = ObjOper -> OrArea (EnumIn, ulIdent, SFORM_PERM, &pIEnum);
	if (FAILED(hr)) {
		if (pIEnum) pIEnum -> Release();
		return hr;
	}

// jetzt Collection der GeoObjects generieren
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(DGeoObject *)this, m_pApp, m_pDoc,
							GetObjectsFromEnum, (DWORD)pIEnum, NULL);

// Resultat vorbereiten
	if (NULL == pCObjects)  return E_OUTOFMEMORY;

// Enumerator freigeben	
	pCObjects -> m_dwData = NULL;
	if (pIEnum) pIEnum -> Release(); 

	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

STDMETHODIMP CGeoObject::GeometryXOR (DGeoObjects *pIObjs, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::GeometryXOR");

	TEST_E_POINTER("CGeoObject::GeometryXOR", ppIObjs);

// ObjOperExtension nach allen entsprechenden Objekten befragen
WExtendObjOper ObjOper;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetIObjOper (ObjOper.ppi());

	if (FAILED(hr)) return hr;
		
// Dieses Objekt und das übergebene in Enumerator speichern
// Objekte in Collection liefern
WEnumLONG EnumOut;		// Resultat
WEnumLONG EnumIn;

// Parameter extrahieren
	hr = GetEnumLongFromGeoObjects (pIObjs, EnumIn.ppi());
	if (FAILED(hr)) return hr;

// jetzt gehts los
	hr = ObjOper -> XorArea_ONr (GetValue(), EnumIn, SFORM_PERM, EnumOut.ppi());
	if (FAILED(hr)) return hr;

// jetzt Collection der GeoObjects generieren
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(DGeoObject *)this, m_pApp, m_pDoc,
							GetObjectsFromEnum, (DWORD)(IUnknown *)EnumOut, NULL);

// Resultat vorbereiten
	if (NULL == pCObjects)  return E_OUTOFMEMORY;

// Enumerator freigeben	
	pCObjects -> m_dwData = NULL;
	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

// VisualisierungsInfo bearbeiten ---------------------------------------------
HRESULT CGeoObject::GetVisInfoClsId (CLSID *pClsId)
{
	switch (GetObjectType()) {
	case OGPunkt:	*pClsId = CLSID_PointVisInfo; break;
	case OGLinie:	*pClsId = CLSID_LineVisInfo; break;
	case OGKreis:
	case OGFlaeche:	*pClsId = CLSID_AreaVisInfo; break;
	case OGLabel:
	case OGText:	*pClsId = CLSID_TextVisInfo; break;
	default:
		return E_FAIL;
	}

return NOERROR;
}

STDMETHODIMP CGeoObject::GetVisInfo (VARIANT vView, DVisInfo **ppIVisInfo)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::GetVisInfo");

	TEST_E_POINTER("CGeoObject::GetVisInfo", ppIVisInfo);

WDVisInfo VisInfo;

	try {
	CLSID ClsId;
	WVisObjExt VisExt;

		THROW_FAILED_HRESULT(GetVisInfoClsId (&ClsId));
		THROW_FAILED_HRESULT(((OLE2AutoExtension *)g_pTE) -> GetIVisInfo (VisExt.ppi()));
		THROW_FAILED_HRESULT(VisExt -> GetVisInfoObject (
			GetValue(), (VISINFOTYPE)GetObjectType(), vView, VisInfo.ppi()));

	// in die Hierarchie der TRiASObjekt einordnen
		{
		WDispatch Disp;

			THROW_FAILED_HRESULT(GetDispatchIF (Disp.ppi()));
			THROW_FAILED_HRESULT(VisInfo -> put_Parent (Disp));

			THROW_FAILED_HRESULT(m_pApp -> GetDispatchIF (Disp.ppi()));
			THROW_FAILED_HRESULT(VisInfo -> put_Application (Disp));
		}

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	*ppIVisInfo = VisInfo.detach();
	return S_OK;
}

STDMETHODIMP CGeoObject::SetVisInfo (DVisInfo *pIVisInfo, VARIANT vView)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::SetVisInfo");

	try {
	WDispatch Parent;
	WDispatch Disp;
	
		THROW_FAILED_HRESULT(pIVisInfo -> get_Parent (Parent.ppi()));
		THROW_FAILED_HRESULT(GetDispatchIF (Disp.ppi()));

	WVisObjExt VisExt;

		THROW_FAILED_HRESULT(((OLE2AutoExtension *)g_pTE) -> GetIVisInfo (VisExt.ppi()));
		THROW_FAILED_HRESULT(VisExt -> SetVisInfoObject (
			GetValue(), (VISINFOTYPE)GetObjectType(), pIVisInfo, 
			(Parent == Disp) ? VARIANT_TRUE : VARIANT_FALSE, vView));

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return NOERROR;
}

STDMETHODIMP CGeoObject::ResetVisInfo (VARIANT vView)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::ResetVisInfo");

	try {
	WVisObjExt VisExt;

		THROW_FAILED_HRESULT(((OLE2AutoExtension *)g_pTE) -> GetIVisInfo (VisExt.ppi()));
		THROW_FAILED_HRESULT(VisExt -> ResetVisInfoObject (
			GetValue(), (VISINFOTYPE)GetObjectType(), vView));

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}
	return S_OK;
}

STDMETHODIMP CGeoObject::GetCommonContourObjects (
	DGeoObjects *pIInObjs, VARIANT vIdent, VARIANT vResultMode, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::GetCommonContourObjects");

	TEST_E_POINTER("CGeoObject::GetCommonContourObjects", ppIObjs);

// ObjOperExtension nach allen entsprechenden Objekten befragen
WExtendObjOper ObjOper;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetIObjOper (ObjOper.ppi());

	if (FAILED(hr)) return hr;
		
// Dieses Objekt und das übergebene in Enumerator speichern
// Objekte in Collection liefern
IEnumLONG *pIEnum = NULL;		// Resultat
WEnumLONG EnumIn;

// Parameter extrahieren
CComVariant vaIdent;
ULONG ulIdent = INVALID_IDENT;

	if (SUCCEEDED(vaIdent.ChangeType (VT_DISPATCH, &vIdent)) && NULL != V_DISPATCH(&vaIdent)) {
		try {
		// IDispatch (DGeoClass ?)
		WDGeoClass Cls (V_DISPATCH(&vaIdent));	// throws hr

			THROW_FAILED_HRESULT(Cls -> get_Code((LONG *)&ulIdent));

		} catch (_com_error &e) {
			return _COM_ERROR(e);
		}
	} else if (SUCCEEDED(vaIdent.ChangeType (VT_I4, &vIdent))) {
		ulIdent = V_I4(&vaIdent);
	} else
		ulIdent = GetObjIdentEx();

	hr = GetEnumLongFromGeoObjects (pIInObjs, EnumIn.ppi());
	if (FAILED(hr)) return hr;

DWORD dwMode = LAUSS;
CComVariant vaArg;

	if (SUCCEEDED(vaArg.ChangeType (VT_I4, &vResultMode)))
		dwMode = V_I4(&vaArg);

// jetzt gehts los
	hr = ObjOper -> CommonContour_ONr (GetValue(), ulIdent, EnumIn, dwMode, SFORM_PERM, &pIEnum);
	if (FAILED(hr)) {
		if (pIEnum) pIEnum -> Release();
		return hr;
	}

// jetzt Collection der GeoObjects generieren
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
					(DGeoObject *)this, m_pApp, m_pDoc,
					GetObjectsFromEnum, (DWORD)pIEnum, NULL);

// Resultat vorbereiten
	if (pCObjects == NULL) return E_OUTOFMEMORY;

// Enumerator freigeben	
	pCObjects -> m_dwData = NULL;
	if (pIEnum) pIEnum -> Release(); 

	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

// DEXOR_QueryRechercheStatus
STDMETHODIMP CGeoObject::get_Selected (VARIANT vObjWin, VARIANT_BOOL *pfSelected)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::get_Selected");

	if (NULL == pfSelected) return E_POINTER;

HWND hWnd = NULL;
HRESULT hr = RetrieveHandle (vObjWin, &hWnd);

	if (FAILED(hr)) return hr;
	ASSERT(::IsWindow(hWnd) && DEX_IsORWindow(hWnd));

RECHOBJECT RO;

	INITSTRUCT (RO, RECHOBJECT);
	RO.lONr = GetValue();
	DEXOR_QueryRechercheStatus(hWnd, RO);

	*pfSelected = (RO.iFlags & RSSelected) ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

// DEXOR_SelectObject/DEXOR_UnselectObject
STDMETHODIMP CGeoObject::put_Selected (VARIANT vObjWin, VARIANT_BOOL fSelected)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::put_Selected");

HWND hWnd = NULL;
HRESULT hr = RetrieveHandle (vObjWin, &hWnd);

	if (FAILED(hr)) return hr;
	ASSERT(::IsWindow(hWnd) && DEX_IsORWindow(hWnd));

	if (fSelected)
		DEXOR_SelectObject(hWnd, GetValue());
	else
		DEXOR_UnselectObject(hWnd, GetValue());

	return S_OK;
}

// DEXOR_QueryRechercheStatus
STDMETHODIMP CGeoObject::get_Activated (VARIANT vObjWin, VARIANT_BOOL *pfActivated)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::get_Activated");

	if (NULL == pfActivated) return E_POINTER;

HWND hWnd = NULL;
HRESULT hr = RetrieveHandle (vObjWin, &hWnd);

	if (FAILED(hr)) return hr;
	ASSERT(::IsWindow(hWnd) && DEX_IsORWindow(hWnd));

RECHOBJECT RO;

	INITSTRUCT (RO, RECHOBJECT);
	RO.lONr = GetValue();
	DEXOR_QueryRechercheStatus(hWnd, RO);

	*pfActivated = (RO.iFlags & RSActivated) ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

// DEXOR_ActivateObject
STDMETHODIMP CGeoObject::put_Activated (VARIANT vObjWin, VARIANT_BOOL fActivated)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::put_Activated");

	if (!fActivated) return E_INVALIDARG;

HWND hWnd = NULL;
HRESULT hr = RetrieveHandle (vObjWin, &hWnd);

	if (FAILED(hr)) return hr;
	ASSERT(::IsWindow(hWnd) && DEX_IsORWindow(hWnd));

	DEXOR_ActivateObject(hWnd, GetValue());
	return S_OK;
}

HRESULT CGeoObject::RetrieveHandle (VARIANT &rvORWnd, HWND *phWnd)
{
	if (NULL == phWnd) return E_POINTER;

HRESULT hr = E_FAIL;

	*phWnd = NULL;		// initialisieren
	try {
	CComVariant vArg;
	
		hr = VariantChangeType (&vArg, &rvORWnd, 0, VT_DISPATCH);
		if (SUCCEEDED(hr) && NULL != V_DISPATCH(&vArg)) {
		// IDispatch des Fensters gegeben
		WDGeoObjectWin Win (V_DISPATCH(&vArg));	// throws hr

			return Win -> get_Value ((long *)phWnd);
		}

	// VT_I4 ist Fensterhndle
		hr = VariantChangeType (&vArg, &rvORWnd, 0, VT_I4);
		if (SUCCEEDED(hr) && ::IsWindow(HWND(V_I4(&vArg))) && DEX_IsORWindow(HWND(V_I4(&vArg)))) 
		{
			*phWnd = HWND(V_I4(&vArg));
			return S_OK;
		}

		hr = VariantChangeType (&vArg, &rvORWnd, 0, VT_BSTR);
		if (SUCCEEDED(hr)) {
		// Name des Fensters gegeben
			USES_CONVERSION;

		CGeoObjectWin *pWin = m_pDoc -> FGetObjWinDisp (OLE2A(V_BSTR(&vArg)));
		
			if (NULL == pWin) _com_issue_error(E_UNEXPECTED);
			*phWnd = pWin -> GetValue();
			return S_OK;
		}

	// Parameter weggelassen ?
		hr = VariantChangeType (&vArg, &rvORWnd, 0, VT_ERROR);
		if (SUCCEEDED(hr)) {
		// aktives/letztes aktives Fenster nehmen
			*phWnd = DEX_GetActiveORWnd();
			if (NULL == *phWnd) _com_issue_error(E_UNEXPECTED);
			return S_OK;
		}

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return hr;
}

STDMETHODIMP CGeoObject::get_Properties (_DTRiASProperties **ppIProps)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::get_Properties");
	return E_NOTIMPL;
}

STDMETHODIMP CGeoObject::CreateProperty (VARIANT vName, VARIANT vType, VARIANT vValue, _DTRiASProperty **ppIProp)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::CreateProperty");
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// Direktes lesen und schreiben von Objekteigenschaften
STDMETHODIMP CGeoObject::get_Feature (BSTR bstrName, VARIANT *pvValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::get_Feature");

	if (NULL == pvValue) return E_POINTER;

	USES_CONVERSION;

// existiert Objekteigenschaft ?
CGeoFeatureBase *pFeature = FGetFeatureDisp (OLE2A(bstrName));

	if (NULL == pFeature) return E_FAIL;

char *pValue = pFeature -> GetFeat();
CComBSTR bstr;

	if (NULL != pValue) 
		bstr = pValue;

	V_VT(pvValue) = VT_BSTR;
	V_BSTR(pvValue) = bstr.Detach();
	return (NULL == V_BSTR(pvValue)) ? E_OUTOFMEMORY : S_OK;
}

STDMETHODIMP CGeoObject::put_Feature (BSTR bstrName, VARIANT vValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::put_Feature");

	USES_CONVERSION;

FEATUREMODE rgMode = FEATUREMODE(FEATUREMODE_Get|FEATUREMODE_GetDoNotReadValue);
CGeoFeatureBase *pFeature = FGetFeatureDisp (OLE2A(bstrName), NULL, PROPCAPS_UNKNOWN, rgMode);

	if (NULL == pFeature) 
		return E_FAIL;		// Objekteigenschaft existiert nicht

CComVariant v;
HRESULT hr = v.ChangeType (VT_BSTR, &vValue);

	if (FAILED(hr)) return hr;

	return pFeature -> SetFeat (OLE2A(V_BSTR(&v)));
}

STDMETHODIMP CGeoObject::Hilight (TRIASCOLOR crAct)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::Hilight");

ACTIVATEOBJECT AO;

	INITSTRUCT(AO, ACTIVATEOBJECT);
	AO.lONr = GetValue();
	AO.crAct = crAct;
	return DEX_SelectObject(AO) ? S_OK : E_FAIL;
}

STDMETHODIMP CGeoObject::UnHilight (void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::UnHilight");

	DEX_UnselectObject(GetValue());
	return S_OK;
}

STDMETHODIMP CGeoObject::ShiftGeometrySegment (
		double DestX, double DestY, 
		VARIANT TargetBeginX, VARIANT TargetBeginY,	VARIANT TargetEndX, VARIANT TargetEndY,
		VARIANT vMD, VARIANT ContinueBegin, VARIANT ContinueEnd, VARIANT Eps,
		VARIANT ClipXMin, VARIANT ClipYMin, VARIANT ClipXMax, VARIANT ClipYMax, 
		DGeoObject **ppIObj)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::ShiftGeometrySegment");

	TEST_E_POINTER("CGeoObject::ShiftGeometrySegment", ppIObj);

// ObjOperExtension nach allen entsprechenden Objekten befragen
WExtendObjOper ObjOper;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetIObjOper (ObjOper.ppi());

	if (FAILED(hr)) return hr;

// Parameter umsetzen
LONG lX, lY;

	if (!InternalCoords (DestX, DestY, &lX, &lY))
		return E_INVALIDARG;

CComVariant vArgX, vArgY;
LONG lBeginX = 0, lBeginY = 0, lEndX = 0, lEndY = 0;

	if (SUCCEEDED(vArgX.ChangeType (VT_R8, &TargetBeginX)) && 
		SUCCEEDED(vArgY.ChangeType (VT_R8, &TargetBeginY)))
	{
		InternalCoords (V_R8(&vArgX), V_R8(&vArgY), &lBeginX, &lBeginY);
	}
	if (SUCCEEDED(vArgX.ChangeType (VT_R8, &TargetEndX)) && 
		SUCCEEDED(vArgY.ChangeType (VT_R8, &TargetEndY)))
	{
		InternalCoords (V_R8(&vArgX), V_R8(&vArgY), &lEndX, &lEndY);
	}

CComVariant vArg;
MoveDir rgMD = MOVEDIR_UP;

	if (SUCCEEDED(vArg.ChangeType (VT_I4, &vMD)))
		rgMD = (MoveDir)V_I4(&vArg);
	if (0 == rgMD) rgMD = MOVEDIR_UP;

CComVariant vbool;
VARIANT_BOOL fContBegin = VARIANT_TRUE, fContEnd = VARIANT_TRUE;

	if (SUCCEEDED(vbool.ChangeType (VT_BOOL, &ContinueBegin)))
		fContBegin = V_BOOL(&vbool);
	if (SUCCEEDED(vbool.ChangeType (VT_BOOL, &ContinueEnd)))
		fContEnd = V_BOOL(&vbool);

long lEps = 0;

	if (SUCCEEDED(vArg.ChangeType (VT_R8, &Eps))) {
	long dX1 = 0, dY1 = 0;
	long dX2 = 0, dY2 = 0;

		InternalCoords (DestX, DestY, &dX1, &dY1);
		InternalCoords (DestX+V_R8(&vArg), DestY+V_R8(&vArg), &dX2, &dY2);
		lEps = max (abs(dX2-dX1), abs(dY2-dY1));
	}

CComVariant vArgX2, vArgY2;
LONG lXMin = 0, lYMin = 0, lXMax = 0, lYMax = 0;

	if (SUCCEEDED(vArgX.ChangeType (VT_R8, &ClipXMin)) && 
		SUCCEEDED(vArgY.ChangeType (VT_R8, &ClipYMin)) &&
		SUCCEEDED(vArgX2.ChangeType (VT_R8, &ClipXMax)) && 
		SUCCEEDED(vArgY2.ChangeType (VT_R8, &ClipYMax)))
	{
		InternalCoords (V_R8(&vArgX), V_R8(&vArgY), &lXMin, &lYMin);
		if (!InternalCoords (V_R8(&vArgX2), V_R8(&vArgY2), &lXMax, &lYMax))
		{
			lXMin = 0;
			lYMin = 0;
		}
	}

// jetzt gehts los
LONG lONr = INVALID_ONR;

	hr = ObjOper -> LineShifting_ONr (GetValue(), lX, lY, lBeginX, lBeginY, lEndX, lEndY, rgMD,
									  fContBegin, fContEnd, lEps, lXMin, lYMin, lXMax, lYMax, &lONr);
	if (FAILED(hr)) return hr;

// zugehöriges DGeoObject besorgen
	return m_pDoc -> FGetGeoObject (lONr, ppIObj);
}

STDMETHODIMP CGeoObject::get_Guid (BSTR *Ident)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::get_Guid");

	TEST_E_POINTER("CGeoObject::get_UniqueID", Ident);

OBJECTGUID OUID;

	INITSTRUCT (OUID, OBJECTGUID);
	OUID.lONr = GetValue();
	if (SUCCEEDED(DEX_GetObjectGuid (OUID))) {
	CComBSTR bstr (GUID_CCH, (LPCOLESTR)NULL);

		if (!bstr) return E_OUTOFMEMORY;

	HRESULT hr = StringFromGUID2 (OUID.guid, bstr, GUID_CCH);

		if (FAILED(hr)) return hr;

		*Ident = bstr.Detach();
		return S_OK;
	}
	return E_FAIL;
}

STDMETHODIMP CGeoObject::put_Guid (BSTR Ident)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::put_Guid");

OBJECTGUID OUID;

	INITSTRUCT (OUID, OBJECTGUID);
	OUID.lONr = GetValue();

HRESULT hr = CLSIDFromString (Ident, &OUID.guid);

	if (FAILED(hr)) return hr;

	return DEX_SetObjectGuid (OUID);
}

STDMETHODIMP CGeoObject::get_UniqueID (BSTR *Ident)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::get_UniqueID");

	TEST_E_POINTER("CGeoObject::get_UniqueID", Ident);

#if defined(_FORCE_LEGACY_CODE)
long lMCode = DEX_GetUniqueIdentMCode();
#else
HPROJECT hPr = DEX_GetObjectProject(GetValue());
long lMCode = DEX_GetUniqueIdentMCodeEx(hPr);
#endif // _FORCE_LEGACY_CODE

	if (0 == lMCode)
		return E_UNEXPECTED;

char cbBuffer[KTEXTLEN] = { "\0" };
PBDDATA Data;

	INITSTRUCT(Data, PBDDATA);
	Data.pbdTyp = 'm';
	Data.pbdCode = lMCode;
	Data.pbdKText = cbBuffer;
	Data.pbdKTextLen = sizeof(cbBuffer)-1;
#if defined(_FORCE_LEGACY_CODE)
	if (EC_OKAY != DEX_GetPBDData(Data))
#else
	if (EC_OKAY != DEX_GetPBDDataEx(hPr, Data))
#endif // _FORCE_LEGACY_CODE
		return E_UNEXPECTED;

// existiert Objekteigenschaft ?
CGeoFeatureBase *pFeature = FGetFeatureDisp (cbBuffer);

	if (NULL == pFeature) return E_FAIL;

char *pValue = pFeature -> GetFeat();
CComBSTR bstr;

	if (NULL != pValue) 
		bstr = pValue;

	*Ident = bstr.Detach();
	return (NULL == *Ident) ? E_OUTOFMEMORY : S_OK;
}

STDMETHODIMP CGeoObject::put_UniqueID (BSTR Ident)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::put_UniqueID");

#if defined(_FORCE_LEGACY_CODE)
long lMCode = DEX_GetUniqueIdentMCode();
#else
HPROJECT hPr = DEX_GetObjectProject(GetValue());
long lMCode = DEX_GetUniqueIdentMCodeEx(hPr);
#endif // _FORCE_LEGACY_CODE

	if (0 == lMCode)
		return E_UNEXPECTED;

char cbBuffer[KTEXTLEN] = { "\0" };
PBDDATA Data;

	INITSTRUCT(Data, PBDDATA);
	Data.pbdTyp = 'm';
	Data.pbdCode = lMCode;
	Data.pbdKText = cbBuffer;
	Data.pbdKTextLen = sizeof(cbBuffer)-1;
#if defined(_FORCE_LEGACY_CODE)
	if (EC_OKAY != DEX_GetPBDData(Data))
#else
	if (EC_OKAY != DEX_GetPBDDataEx(hPr, Data))
#endif // _FORCE_LEGACY_CODE
		return E_UNEXPECTED;

// existiert Objekteigenschaft ?
CGeoFeatureBase *pFeature = FGetFeatureDisp (cbBuffer);

	if (NULL == pFeature) {
	CComVariant vData (lMCode);

		pFeature = FGetFeatureDisp (cbBuffer, NULL, PROPCAPS_NONE, FEATUREMODE_Add, &vData);
		if (NULL == pFeature)
			return E_FAIL;
	}

	USES_CONVERSION;
	return pFeature -> SetFeat (OLE2A(Ident), TRUE);
}

STDMETHODIMP CGeoObject::get_OldUniqueID (BSTR *Ident)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::get_OldUniqueID");

	TEST_E_POINTER("CGeoObject::get_OldUniqueID", Ident);

#if defined(_FORCE_LEGACY_CODE)
long lMCode = DEX_GetOldUniqueIdentMCode();
#else
HPROJECT hPr = DEX_GetObjectProject(GetValue());
long lMCode = DEX_GetOldUniqueIdentMCodeEx(hPr);
#endif // _FORCE_LEGACY_CODE

	if (0 == lMCode)
		return E_UNEXPECTED;

char cbBuffer[KTEXTLEN] = { "\0" };
PBDDATA Data;

	INITSTRUCT(Data, PBDDATA);
	Data.pbdTyp = 'm';
	Data.pbdCode = lMCode;
	Data.pbdKText = cbBuffer;
	Data.pbdKTextLen = sizeof(cbBuffer)-1;
#if defined(_FORCE_LEGACY_CODE)
	if (EC_OKAY != DEX_GetPBDData(Data))
#else
	if (EC_OKAY != DEX_GetPBDDataEx(hPr, Data))
#endif // _FORCE_LEGACY_CODE
		return E_UNEXPECTED;

// existiert Objekteigenschaft ?
CGeoFeatureBase *pFeature = FGetFeatureDisp (cbBuffer);

	if (NULL == pFeature) return E_FAIL;

char *pValue = pFeature -> GetFeat();
CComBSTR bstr;

	if (NULL != pValue) 
		bstr = pValue;

	*Ident = bstr.Detach();
	return (NULL == *Ident) ? E_OUTOFMEMORY : S_OK;
}

STDMETHODIMP CGeoObject::put_OldUniqueID (BSTR Ident)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::put_OldUniqueID");

#if defined(_FORCE_LEGACY_CODE)
long lMCode = DEX_GetOldUniqueIdentMCode();
#else
HPROJECT hPr = DEX_GetObjectProject(GetValue());
long lMCode = DEX_GetOldUniqueIdentMCodeEx(hPr);
#endif // _FORCE_LEGACY_CODE

	if (0 == lMCode)
		return E_UNEXPECTED;

char cbBuffer[KTEXTLEN] = { "\0" };
PBDDATA Data;

	INITSTRUCT(Data, PBDDATA);
	Data.pbdTyp = 'm';
	Data.pbdCode = lMCode;
	Data.pbdKText = cbBuffer;
	Data.pbdKTextLen = sizeof(cbBuffer)-1;
#if defined(_FORCE_LEGACY_CODE)
	if (EC_OKAY != DEX_GetPBDData(Data))
#else
	if (EC_OKAY != DEX_GetPBDDataEx(hPr, Data))
#endif // _FORCE_LEGACY_CODE
		return E_UNEXPECTED;

// existiert Objekteigenschaft ?
CGeoFeatureBase *pFeature = FGetFeatureDisp (cbBuffer);

	if (NULL == pFeature) {
	CComVariant vData (lMCode);

		pFeature = FGetFeatureDisp (cbBuffer, NULL, PROPCAPS_NONE, FEATUREMODE_Add, &vData);
		if (NULL == pFeature)
			return E_FAIL;
	}

	USES_CONVERSION;
	return pFeature -> SetFeat (OLE2A(Ident), TRUE);
}

STDMETHODIMP CGeoObject::MakeRectangular (
	VARIANT vRefLine, VARIANT vEps90, VARIANT vEps180, VARIANT vEpsCom,
	VARIANT vEnumCommon, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::MakeRectangular");

	TEST_E_POINTER("CGeoObject::MakeRectangular", ppIObjs);

// ObjOperExtension nach allen entsprechenden Objekten befragen
WExtendGeoEdit Edit;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetIEdit (Edit.ppi());

	if (FAILED(hr)) return hr;
		
// Dieses Objekt und das übergebene in Enumerator speichern
// Objekte in Collection liefern
IEnumLONG *pIEnum = NULL;		// Resultat
WEnumLONG EnumIn;

// Parameter extrahieren
CComVariant vaArg;
double dEps90 = 10.0, dEps180 = 7.0, dEpsCom = 0.0;

	if (SUCCEEDED(vaArg.ChangeType (VT_R8, &vEps90))) 
		dEps90 = V_R8(&vaArg);
	if (SUCCEEDED(vaArg.ChangeType (VT_R8, &vEps180))) 
		dEps180 = V_R8(&vaArg);
	if (SUCCEEDED(vaArg.ChangeType (VT_R8, &vEpsCom))) 
		dEpsCom = V_R8(&vaArg);

	if (SUCCEEDED(vaArg.ChangeType (VT_DISPATCH, &vEnumCommon)) && NULL != V_DISPATCH(&vaArg)) {
	WDGeoObjects Objs;

		hr = V_DISPATCH(&vaArg) -> QueryInterface (IID_DGeoObjects, Objs.ppv());
		if (FAILED(hr)) return hr;

		hr = GetEnumLongFromGeoObjects (Objs, EnumIn.ppi());
		if (FAILED(hr)) return hr;
	}

RefLine rgLine = (NULL != (IEnumLONG *)EnumIn) ? EDIT_COMMON : EDIT_LONGEST;

	if (SUCCEEDED(vaArg.ChangeType (VT_I4, &vRefLine)))
		rgLine = (RefLine)V_I4(&vaArg);

// jetzt gehts los
	hr = Edit -> MakeRectangular_ONr (GetValue(), rgLine, dEps90, dEps180, dEpsCom, EnumIn, &pIEnum);
	if (FAILED(hr)) {
		if (pIEnum) pIEnum -> Release();
		return hr;
	}

// jetzt Collection der GeoObjects generieren
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
					(DGeoObject *)this, m_pApp, m_pDoc,
					GetObjectsFromEnum, (DWORD)pIEnum, NULL);

// Resultat vorbereiten
	if (pCObjects == NULL) return E_OUTOFMEMORY;

// Enumerator freigeben	
	pCObjects -> m_dwData = NULL;
	if (pIEnum) pIEnum -> Release(); 

	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// diese Funktion liefert die ObjektNummer des abhängigen (Text-)Objektes 
extern "C" 
BOOL PASCAL FindLinkedObject (long lONr, long lRCode, short iRTyp, void *pData)
{
// angehängtes Textobjekt gefunden
	if (lRCode == -1L && iRTyp == RTBegleitO) {
		*(long *)pData = lONr;		// ObjektNummer merken
		return false;				// Enumeration abbrechen
	}

// zugehöriges Bezugsobjekt gefunden
	if (lRCode == -1L && iRTyp == RTBegleitU) {
		*(long *)pData = lONr;
		return false;
	}
	return true;
}

STDMETHODIMP CGeoObject::GetRelatedObject (DGeoObject **ppIObj)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::GetRelatedObject");

	TEST_E_POINTER("CGeoObject::GetRelatedObject", ppIObj);

// Relationen enumerieren
// Abhängiges Textobjekt (ONr und Geometrie) besorgen
long lONr = -1;	// abhängiges Textobjekt der Linie
ENUMRELATIONOBJS ERO;

	INITSTRUCT(ERO, ENUMRELATIONOBJS);
	ERO.lONr = GetValue();
	ERO.lRCode = -1L;		// Begleitrelation
	ERO.iRTyp = RTBegleitO|RTBegleitU;
	ERO.eFcn = (ENUMRELOBJPROC)FindLinkedObject;
	ERO.pData = &lONr;
	DEX_EnumRelationObjects (ERO);

	if (lONr == -1L) 	// kein abhängiges/übergeordnetes Objekt vorhanden
		return E_FAIL;

// zugehöriges DGeoObject besorgen
	return m_pDoc -> FGetGeoObject (lONr, ppIObj);
}

STDMETHODIMP CGeoObject::CreateObjectRelation (DGeoObject *pIObjIn)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::CreateObjectRelation");

	TEST_E_POINTER("CGeoObject::CreateObjectRelation", pIObjIn);

// ist übergebenes Objekt ein Textobjekt 
OBJECTTYPE rgType = OBJECTTYPE_Unknown;
bool fInvert = false;

	RETURN_FAILED_HRESULT(pIObjIn -> get_ObjType (&rgType));
	if (OBJECTTYPE_Text != rgType)
		fInvert = true;

// Relation erzeugen
LONG lTxtONr = INVALID_ONR;

	RETURN_FAILED_HRESULT(pIObjIn -> get_Value (&lTxtONr));

MODRELATION MR;

	INITSTRUCT (MR, MODRELATION);
	if (!fInvert) {
		MR.lPONr = GetValue();
		MR.lSONr = lTxtONr;
		MR.iRTyp = RTBegleitO;
	} else {
		MR.lPONr = lTxtONr;
		MR.lSONr = GetValue();
		MR.iRTyp = RTBegleitU;
	}
	MR.lRCode = -1L;		// Begleitrelation
	return (EC_OKAY == DEX_ModifyRelation(MR)) ? S_OK : E_FAIL;
}

STDMETHODIMP CGeoObject::RemoveObjectRelation(DGeoObject **ppIObj)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::RemoveObjectRelation");

	TEST_E_POINTER("CGeoObject::CreateObjectRelation", ppIObj);

// zugehöriges Objekt finden
WDGeoObject Obj;

	RETURN_FAILED_HRESULT(GetRelatedObject(Obj.ppi()));

// ist übergebenes Objekt ein Textobjekt 
OBJECTTYPE rgType = OBJECTTYPE_Unknown;
bool fInvert = false;

	RETURN_FAILED_HRESULT(Obj -> get_ObjType (&rgType));
	if (OBJECTTYPE_Text != rgType)
		fInvert = true;

// Relation erzeugen
LONG lTxtONr = INVALID_ONR;

	RETURN_FAILED_HRESULT(Obj -> get_Value (&lTxtONr));

// Relation auflösen
DELRELATION DR;	                            

	INITSTRUCT(DR, DELRELATION);
	if (!fInvert) {
		DR.lPONr = GetValue();
		DR.lSONr = lTxtONr;
		DR.iRTyp = RTBegleitO;
	} else {
		DR.lPONr = lTxtONr;
		DR.lSONr = GetValue();
		DR.iRTyp = RTBegleitU;
	}
	DR.lRCode = -1L;		// RelationsCode
    DEX_DeleteRelation(DR);

	*ppIObj = Obj.detach();
	return S_OK;
}

STDMETHODIMP CGeoObject::AnalyzeGeometry (VARIANT_BOOL *pbSuccess)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::AnalyzeGeometry");

	TEST_E_POINTER("CGeoObject::AnalyzeGeometry", pbSuccess);

// GeoReinExtension nach allen entsprechenden Objekten befragen
WExtendGeoRein GeoRein;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetIGeoRein (GeoRein.ppi());

	if (FAILED(hr)) return hr;

BOOL fSuccess = FALSE;

	RETURN_FAILED_HRESULT(GeoRein -> WholeAnalysis_ONr (GetValue(), &fSuccess));

	*pbSuccess = fSuccess ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CGeoObject::AnalyzeGeometryObject (DGeoObject *pIObjIn, VARIANT vargMode, VARIANT_BOOL *pbSuccess)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::AnalyzeGeometryObject");

	TEST_E_POINTER("CGeoObject::AnalyzeGeometryObject", pbSuccess);

// GeoReinExtension nach allen entsprechenden Objekten befragen
WExtendGeoRein GeoRein;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetIGeoRein (GeoRein.ppi());

	if (FAILED(hr)) return hr;

LONG lONr = INVALID_ONR;

	RETURN_FAILED_HRESULT(pIObjIn -> get_Value (&lONr));

ErrorTextMode rgMode = REIN_BOTH;
CComVariant vMode;

	if (SUCCEEDED(vMode.ChangeType (VT_I4, &vargMode)))
		rgMode = (ErrorTextMode)V_I4(&vMode);

BOOL fSuccess = FALSE;

	RETURN_FAILED_HRESULT(GeoRein -> InterObjectsAnalysis_ONr (GetValue(), lONr, rgMode, &fSuccess));

	*pbSuccess = fSuccess ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Objekt ein/ausblenden
STDMETHODIMP CGeoObject::get_Visible (VARIANT vView, VARIANT_BOOL *pfShown)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::get_Visible");

	TEST_E_POINTER("CGeoObject::get_Visible", pfShown);

WVisObjExt VisExt;
VARIANT_BOOL fIsShown = VARIANT_TRUE;

	RETURN_FAILED_HRESULT(((OLE2AutoExtension *)g_pTE) -> GetIVisInfo (VisExt.ppi()));
	RETURN_FAILED_HRESULT(VisExt -> GetObjectHiddenStatus (GetValue(), vView, &fIsShown));

	*pfShown = fIsShown;
	return S_OK;
}

STDMETHODIMP CGeoObject::put_Visible (VARIANT vView, VARIANT_BOOL fShown)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::put_Visible");

WVisObjExt VisExt;

	RETURN_FAILED_HRESULT(((OLE2AutoExtension *)g_pTE) -> GetIVisInfo (VisExt.ppi()));
	return VisExt -> SetObjectHiddenStatus (GetValue(), fShown, vView);
}

///////////////////////////////////////////////////////////////////////////////
// Connection
STDMETHODIMP CGeoObject::get_Connection (ITRiASConnection **ppIConn)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::get_Connection");

HPROJECT hPr = DEX_GetObjectProject (GetValue());

	if (HACTCONNECTION == hPr)
		return E_UNEXPECTED;

	if (!DEX_GetDataSourcePtr (hPr, *ppIConn)) {
		_ASSERTE(NULL == *ppIConn);
		return E_UNEXPECTED;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Objekt doppeln
STDMETHODIMP CGeoObject::CloneObject (VARIANT vClass, DGeoObject **ppIObj)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObject::CloneObject");

	if (NULL == ppIObj)
		return E_POINTER;
	*ppIObj = NULL;
	
	COM_TRY {
	CComVariant vCls;
	INT_PTR ulIdent = 0;

		if (SUCCEEDED(vCls.ChangeType (VT_DISPATCH, &vClass)) && NULL != V_DISPATCH(&vCls)) {
		// Objektklasse ist direkt gegeben
		WDGeoClass Cls (V_DISPATCH(&vCls));	// throws hr

			THROW_FAILED_HRESULT(Cls -> get_Code((LONG *)&ulIdent));
		} 
		else if (SUCCEEDED(vCls.ChangeType (VT_I4, &vClass))) {
			ulIdent = V_I4(&vCls);
		} else
			ulIdent = GetObjIdentEx();		// Objektklasse ist nicht gegeben

		_ASSERTE(0 != ulIdent);

	CLONEOBJECT CO;

		INITSTRUCT(CO, CLONEOBJECT);
		CO.lONrToCopy = GetValue();
		CO.lNewIdent = ulIdent;
		if (!DEX_CloneObject(CO))
			return S_FALSE;			// damit VB keine Probleme hat (*ppIObj ist NULL)

		_ASSERTE(0 != CO.lNewONr);
		if (0 == CO.lNewONr)
			return S_FALSE;			// damit VB keine Probleme hat (*ppIObj ist NULL)

	WDGeoObject Obj;
	CGeoObject *pNewObj = m_pDoc -> FGetObjectDisp (CO.lNewONr, Obj.ppi());

		if (NULL != pNewObj)
			*ppIObj = Obj.detach();

	} COM_CATCH;
	return S_OK;
}


