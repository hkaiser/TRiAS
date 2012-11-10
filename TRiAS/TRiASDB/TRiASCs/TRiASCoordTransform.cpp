// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.10.1999 11:27:55
//
// @doc
// @module TRiASCoordTransform.cpp | Implementation of the <c CTRiASCoordTransform> class

#include "stdafx.h"

#include <atl/ciid.h>
#include <McKinney/OleType.h>

#include "LibCTF/LibCTFImpl.h"

#include "TRiASCsImpl.h"
#include "TRiASCoordSystem.h"
#include "TRiASCSDatumTransformation.h"
#include "TRiASCoordTransform.h"
#include "CompareCoordSystems.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
//
HRESULT	CTRiASCoordTransform::FinalConstruct() 
{
	return S_OK;
}

void CTRiASCoordTransform::FinalRelease() 
{
	COM_TRY {
		m_mapOfCS.clear();
	} COM_CATCH_IGNORE;
}

///////////////////////////////////////////////////////////////////////////////
// die eigentliche Transformation ist immer In - Place
HRESULT CTRiASCoordTransform::Transform (REFGUID inCS, long nCoords, CSCOORD* pData)  
{
	USES_CONVERSION;
#ifdef _DEBUG
//	double XX = (pData->X * 180) / 3.1415926535897932384626433;
//	double YY = (pData->Y * 180) / 3.1415926535897932384626433;
//	XX -= 12.0;
//	YY -= 52.5;
//	XX = fabs(XX);
//	YY = fabs(YY);
//	if (XX < 0.05 && YY < 0.05)  _asm { int 3 }
#endif
	CSTRACE5 (_T("    @@@ CTRiASCoordTransform::Transform: %s %d %lf %lf %lf\n"), OLE2A ((CComBSTR) CIID(inCS)), nCoords, pData->X, pData->Y, pData->Z);

LPDispatchMap::iterator it = m_mapOfCS.find (inCS);

	ERROR_EXPR_TRUE (m_mapOfCS.end() == it, CST_E_COORDSYSTEMNOTFOUND);

	if ((*it).second.MustTransform()) {
	WTRiASCS csIn ((*it).second.GetTRiASCS());
	WTRiASCSTransformData trIn(csIn), trOut(m_pOutputCS);

	#if defined(_DEBUG)
		ERROR_EXPR_TRUE (!trIn, CST_E_INVALIDSOURCECOORDSYSTEM);
		ERROR_EXPR_TRUE (!trOut, CST_E_INVALIDDESTINATIONCOORDSYSTEM);
	#endif // defined_DEBUG)

	// Projektion rausrechnen
	WTRiASCSDatumTransformation	dTransIn;

		ERROR_FAILED_HRESULT (trIn -> TransformInverse (nCoords, pData), CST_E_INPUTTRANSFORMATIONFAILED);

	// evtl. Datumstransformation
		if ((*it).second.MustTransformDatum()) {
			ERROR_FAILED_HRESULT (csIn -> get_DatumTransformation (dTransIn.ppi()), CST_E_INVALIDSOURCECOORDSYSTEM);
			ERROR_FAILED_HRESULT (WTRiASCSTransformData(dTransIn) -> TransformInverse (nCoords, pData), CST_E_INPUTTRANSFORMATIONFAILED);
			if (!m_bDTransIntern) {
			WTRiASCSDatumTransformation	dTransOut;

				ERROR_FAILED_HRESULT (m_pOutputCS -> get_DatumTransformation (dTransOut.ppi()), CST_E_INVALIDDESTINATIONCOORDSYSTEM);
				ERROR_FAILED_HRESULT (WTRiASCSTransformData(dTransOut) -> Transform (nCoords, pData), CST_E_OUTPUTTRANSFORMATIONFAILED);
			}
		}

	// Projektion wieder reinrechnen
		ERROR_FAILED_HRESULT (trOut -> Transform (nCoords, pData), CST_E_OUTPUTTRANSFORMATIONFAILED);
	}

	CSTRACE5 (_T("    @@@ CTRiASCoordTransform::Transform: %s %d %lf %lf %lf\n"), OLE2A ((CComBSTR) CIID(inCS)), nCoords, pData->X, pData->Y, pData->Z);
	return S_OK;
}

HRESULT CTRiASCoordTransform::TransformInverse (REFGUID inCS, long nCoords, CSCOORD* pData) 
{
	USES_CONVERSION;
	CSTRACE5 (_T("    @@@ CTRiASCoordTransform::TransformInverse: %s %d %lf %lf %lf\n"), OLE2A ((CComBSTR) CIID(inCS)), nCoords, pData->X, pData->Y, pData->Z);

LPDispatchMap::iterator it = m_mapOfCS.find (inCS);

	ERROR_EXPR_TRUE (m_mapOfCS.end() == it, CST_E_COORDSYSTEMNOTFOUND);

	if ((*it).second.MustTransform()) {
	WTRiASCS csIn ((*it).second.GetTRiASCS());
	WTRiASCSTransformData trIn(csIn), trOut(m_pOutputCS);

	#if defined(_DEBUG)
		ERROR_EXPR_TRUE (!trIn, CST_E_INVALIDDESTINATIONCOORDSYSTEM);
		ERROR_EXPR_TRUE (!trOut, CST_E_INVALIDSOURCECOORDSYSTEM);
	#endif // defined(_DEBUG)

	// Projektion rausrechnen
		ERROR_FAILED_HRESULT (trOut -> TransformInverse (nCoords, pData), CST_E_INPUTTRANSFORMATIONFAILED);

	// evtl. Datumstransformation
		if ((*it).second.MustTransformDatum()) {
			if (!m_bDTransIntern) {
			WTRiASCSDatumTransformation	dTransOut;

				ERROR_FAILED_HRESULT (m_pOutputCS -> get_DatumTransformation (dTransOut.ppi()), CST_E_INVALIDDESTINATIONCOORDSYSTEM);
				ERROR_FAILED_HRESULT (WTRiASCSTransformData(dTransOut) -> TransformInverse (nCoords, pData), CST_E_INPUTTRANSFORMATIONFAILED);
			}
		
		WTRiASCSDatumTransformation	dTransIn;

			ERROR_FAILED_HRESULT (csIn -> get_DatumTransformation (dTransIn.ppi()), CST_E_INVALIDSOURCECOORDSYSTEM);
			ERROR_FAILED_HRESULT (WTRiASCSTransformData(dTransIn) -> Transform (nCoords, pData), CST_E_INPUTTRANSFORMATIONFAILED);
		}

	// Projektion wieder reinrechnen
		ERROR_FAILED_HRESULT (trIn -> Transform (nCoords, pData), CST_E_OUTPUTTRANSFORMATIONFAILED);
	}

	CSTRACE5 (_T("    @@@ CTRiASCoordTransform::TransformInverse: %s %d %lf %lf %lf\n"), OLE2A ((CComBSTR) CIID(inCS)), nCoords, pData->X, pData->Y, pData->Z);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASCSTransform

HRESULT	CTRiASCoordTransform::RemoveOutput() 
{
	if (!m_pOutputCS) 
		return S_FALSE;
	_ASSERTE (m_cookOutput);

	AtlUnadvise (m_pOutputCS, IID_ITRiASCSEvents, m_cookOutput);
	m_cookOutput = 0;
	m_pOutputCS.Assign(NULL);
	return S_OK;
}

HRESULT	CTRiASCoordTransform::RemoveInput (LPDispatchMap::iterator &it) 
{
	_ASSERTE(0 != (*it).second.GetCookie());
	AtlUnadvise ((*it).second.GetTRiASCS(), IID_ITRiASCSEvents, (*it).second.GetCookie());
	m_mapOfCS.erase (it);
	return S_OK;
}

STDMETHODIMP CTRiASCoordTransform::get_OutputCS (ITRiASCS **pVal) 
{
	CHECKOUTPOINTER (pVal);
	ERROR_EXPR_TRUE (!m_pOutputCS, CST_E_COORDSYSTEMNOTFOUND);

	*pVal = m_pOutputCS;
	if(*pVal)
		(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CTRiASCoordTransform::putref_OutputCS (ITRiASCS *pVal) 
{
	CHECKINPOINTER (pVal);
	COM_TRY {
		RemoveOutput();
	
	WTRiASCS cs (pVal);
		
		if (cs.IsValid()) {
		// neues Ausgabesystem setzen
			m_pOutputCS = cs;
			AtlAdvise (m_pOutputCS, GetUnknown(), IID_ITRiASCSEvents, &m_cookOutput);

		// mit allen Eingabesystemen vergleichen
			for (LPDispatchMap::iterator it = m_mapOfCS.begin(); it != m_mapOfCS.end(); ++it) {
				(*it).second.MustTransform (S_OK != EqualCoordSystems (m_pOutputCS, (*it).second.GetTRiASCS()));
				(*it).second.MustTransformDatum (S_OK != EqualDatum (m_pOutputCS, (*it).second.GetTRiASCS()));
			}
		}

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCoordTransform::AddInputCS (ITRiASCS *pCS) 
{
	COM_TRY {
	WTRiASCS trCS (pCS);
	CComBSTR strGUID;
	GUID guid;
	
		RETURN_FAILED_HRESULT (trCS -> get_GUID (CLEARED(strGUID)));
		RETURN_FAILED_HRESULT (::CLSIDFromString (strGUID, &guid));
	
	LPDispatchMap::iterator it = m_mapOfCS.find (guid);
	
		ERROR_EXPR_TRUE (m_mapOfCS.end() != it, CST_E_COORDSYSTEMALREADYPRESENT);
	
	DWORD dwCookie;
	
		AtlAdvise (trCS, GetUnknown(), IID_ITRiASCSEvents, &dwCookie);

	// Feststellen, ob überhaupt eine Transformation notwendig ist
	BOOL fMustTransform = (S_OK != EqualCoordSystems (m_pOutputCS, trCS)) ? TRUE : FALSE;
	BOOL fMustTransformDatum = (S_OK != EqualDatum (m_pOutputCS, trCS)) ? TRUE : FALSE;

		m_mapOfCS.insert (guid, DISPENTRY(trCS, dwCookie, fMustTransform, fMustTransformDatum));

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCoordTransform::ShutDown () 
{
	COM_TRY {
		RemoveOutput();
		while (m_mapOfCS.size() > 0) 
			RemoveInput (m_mapOfCS.begin());
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCoordTransform::RemoveInputCS (BSTR strGUID) 
{
	COM_TRY {
	GUID	guid;
	HRESULT	hr;

		ERROR_FAILED_HRESULT ((hr = ::CLSIDFromString (strGUID, &guid)), hr);

	LPDispatchMap::iterator it = m_mapOfCS.find (guid);

		ERROR_EXPR_TRUE (m_mapOfCS.end() == it, CST_E_COORDSYSTEMNOTFOUND);
		RemoveInput (it);

	} COM_CATCH;
	return S_OK;
}

template <class T> 
void _Add (list<T> &theList, const T &theItem) { theList.push_back (theItem); }

template<class Base, const IID *piid, class T, class Copy, class TT, class CollType = list<TT> >
class CComEnumWithItems
	: public CComEnumOnSTL<Base, piid, T, Copy, CollType>
{
private:
	struct Destroyer { 
		void operator() (T t) { Copy::destroy(&t); } 
	};
	CollType m_coll;

public:
	HRESULT	Init () 
	{
		return _CComEnum::Init (NULL, m_coll);
	}
	HRESULT	AddItem (T p)  
	{
	TT pCopy;
	
		Copy::copy (&pCopy, &p);
		_Add (m_coll, pCopy);
		return S_OK;
	}
};

typedef CComObject<CComEnumWithItems<IEnumVARIANT, &__uuidof(IEnumVARIANT), VARIANT, _Copy<VARIANT>, CComVariant> > CComEnumVARIANTList;
typedef CComEnumVARIANTList CComCSEnum;

template<class T>
class CopyCS 
{
private:
	T &m_t;

public:
	CopyCS (T &t) : m_t(t)
	{}
	void operator() (const pair<GUID, DISPENTRY> &i)  
	{
		m_t.AddItem (CComVariant(i.second.GetTRiASCS()));
	}
};

STDMETHODIMP CTRiASCoordTransform::get_Count (long* pCount)  
{
	CHECKOUTPOINTER (pCount);
	COM_TRY {
		*pCount = m_mapOfCS.size();
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCoordTransform::get__NewEnum (IUnknown** ppEnum)  
{
	COM_TRY {
	CComCSEnum *pEnum = NULL;
	
		RETURN_FAILED_HRESULT (CComCSEnum::CreateInstance (&pEnum));
		for_each (m_mapOfCS.begin(), m_mapOfCS.end(), CopyCS<CComCSEnum>(*pEnum));
		RETURN_FAILED_HRESULT (pEnum->Init());
		RETURN_FAILED_HRESULT (pEnum->QueryInterface (IID_IUnknown, reinterpret_cast<void**>(ppEnum)));
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCoordTransform::get_Item (VARIANT vGUID, VARIANT* pvTRiASCS)  
{
	CHECKOUTPOINTER (pvTRiASCS);
	COM_TRY {
		ERROR_FAILED_HRESULT (V_ISBSTR(&vGUID), E_INVALIDARG);

	GUID guid;
	HRESULT	hr;

		ERROR_FAILED_HRESULT((hr=::CLSIDFromString (V_BSTR(&vGUID), &guid)), hr);

	LPDispatchMap::iterator it = m_mapOfCS.find (guid);

		if (m_mapOfCS.end() == it)
			return CST_E_COORDSYSTEMNOTFOUND;

	CComVariant	vCS ((*it).second.GetTRiASCS());

		THROW_FAILED_HRESULT(vCS.Detach(pvTRiASCS));

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCoordTransform::Add (VARIANT vCS)  
{
	COM_TRY {
		ERROR_EXPR_FALSE (V_ISDISPATCH(&vCS) || V_ISUNKNOWN(&vCS), E_INVALIDARG);
	
	WTRiASCS pTRiASCS (V_ISDISPATCH(&vCS) ? V_DISPATCH(&vCS) : V_UNKNOWN(&vCS));
	
		THROW_FAILED_HRESULT (AddInputCS (pTRiASCS));
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCoordTransform::Remove (VARIANT vCS)  
{
	COM_TRY {
		ERROR_EXPR_FALSE(V_ISDISPATCH(&vCS) || V_ISUNKNOWN(&vCS), E_INVALIDARG);

	CComBSTR strGUID;
	WTRiASCS pTRiASCS (V_ISDISPATCH(&vCS) ? V_DISPATCH(&vCS) : V_UNKNOWN(&vCS));

		THROW_FAILED_HRESULT(pTRiASCS -> get_GUID(&strGUID));
		THROW_FAILED_HRESULT(RemoveInputCS (strGUID));
	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCoordTransform::CheckDatum (WTRiASCS& csIn, WTRiASCS& csOut)  
{
WTRiASCSDatumTransformation	dttIn, dttOut;
TRIASCSDTRANSALGORITHM dtaIn, dtaOut;

	ERROR_FAILED_HRESULT (csIn -> get_DatumTransformation (dttIn.ppi()), CST_E_INVALIDDESTINATIONCOORDSYSTEM);
	ERROR_FAILED_HRESULT (csOut -> get_DatumTransformation (dttOut.ppi()), CST_E_INVALIDDESTINATIONCOORDSYSTEM);
	ERROR_FAILED_HRESULT (dttIn -> get_TransformationAlgorithm (&dtaIn), CST_E_INVALIDSOURCECOORDSYSTEM);
	ERROR_FAILED_HRESULT (dttOut -> get_TransformationAlgorithm (&dtaOut), CST_E_INVALIDDESTINATIONCOORDSYSTEM);
	ERROR_EXPR_FALSE (dtaIn == dtaOut, CST_E_INCOMPATIBLEDATUMTRANSFORMATION);
	return S_OK;
}

STDMETHODIMP CTRiASCoordTransform::get_IsValid(BSTR strGUID, VARIANT_BOOL *pVal)  
{
	CHECKOUTPOINTER(pVal);
	COM_TRY {
	CIID guid (strGUID);

		ERROR_EXPR_TRUE (!guid, E_INVALIDARG);

	LPDispatchMap::iterator it = m_mapOfCS.find (guid);

		ERROR_EXPR_TRUE (m_mapOfCS.end() == it, CST_E_COORDSYSTEMNOTFOUND);
		ERROR_FAILED_HRESULT (WTRiASCSValidate((*it).second.GetTRiASCS()) -> IsValid(), CST_E_INVALIDSOURCECOORDSYSTEM);
		ERROR_FAILED_HRESULT (WTRiASCSValidate(m_pOutputCS) -> IsValid(), CST_E_INVALIDDESTINATIONCOORDSYSTEM);
		ERROR_FAILED_HRESULT (CheckDatum (WTRiASCS((*it).second.GetTRiASCS()), m_pOutputCS), CS_E_INVALIDDATUMTRANSFORMATION);

		*pVal = VARIANT_TRUE;
		
	} COM_CATCH;
	return S_OK;
}

DefineSmartInterface(TRiASCSValidateDatum)

STDMETHODIMP CTRiASCoordTransform::RecomputeTransformations() 
{
	_ASSERTE (!_T("'ITRiASCoordTransform->RecomputeTransformations' ist obsolete, bitte 'ITRiASCoordSystem->Recompute' verwenden!"));
	return E_NOTIMPL;		// nicht mehr rufen, läuft über TRiASCS->Reompute()
//	COM_TRY {
//		LPDispatchMap::iterator	i;
//		ERROR_FAILED_HRESULT (WTRiASCSValidate(m_pOutputCS)->RecomputeTransformation(NULL), CST_E_INVALIDDESTINATIONCOORDSYSTEM);
//		if (!m_bDTransIntern) {
//			// Datumstransformation in den Koordinatensystemen; diese müssen alles selbst berechnen
//			for (i = m_mapOfCS.begin(); i != m_mapOfCS.end(); i++) {
//				ERROR_FAILED_HRESULT (WTRiASCSValidate((*i).second.m_pCS)->RecomputeTransformation(NULL), CST_E_INVALIDSOURCECOORDSYSTEM);
//			}
//		} else {
//			// keine Datumstransformation in den Koordinatensystemen; machen wir hier selbst.
//			// dazu muß aber noch etwas vorbereitet werden...;-))
//			WTRiASCSDatumTransformation	dTransIn, dTransOut;
//			WTRiASCSGCS					gcsIn, gcsOut;
//			ERROR_FAILED_HRESULT (m_pOutputCS->get_DatumTransformation (dTransOut.ppi()), CST_E_INVALIDDESTINATIONCOORDSYSTEM);
//			ERROR_FAILED_HRESULT (m_pOutputCS->get_GeographicCS (gcsOut.ppi()), CST_E_INVALIDDESTINATIONCOORDSYSTEM);
//			for (i = m_mapOfCS.begin(); i != m_mapOfCS.end(); i++) {
//				ERROR_FAILED_HRESULT (WTRiASCSValidate((*i).second.m_pCS)->RecomputeTransformation(NULL), CST_E_INVALIDSOURCECOORDSYSTEM);
//				ERROR_FAILED_HRESULT (WTRiASCS((*i).second.m_pCS)->get_DatumTransformation (dTransIn.ppi()), CST_E_INVALIDDESTINATIONCOORDSYSTEM);
//				ERROR_FAILED_HRESULT (WTRiASCS((*i).second.m_pCS)->get_GeographicCS (gcsIn.ppi()), CST_E_INVALIDDESTINATIONCOORDSYSTEM);
//				ERROR_FAILED_HRESULT (WTRiASCSValidateDatum(dTransIn)->RecomputeDatumTransformation (gcsIn, gcsOut, dTransOut), CST_E_INCOMPATIBLEDATUMTRANSFORMATION);
//			}
//		}
//	} COM_CATCH;
//	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASCSTransform; kompatibel mit OLE-Automation

STDMETHODIMP CTRiASCoordTransform::Transform (BSTR strGUID, VARIANT pInPoints, VARIANT *pOutPoints) 
{
	CHECKINPOINTER(pOutPoints);
	COM_TRY {
	GUID guid;
	HRESULT	hr;

		ERROR_FAILED_HRESULT ((hr=::CLSIDFromString (strGUID, &guid)), hr);

	SAFEARRAY *pArray = NULL;

		ERROR_EXPR_FALSE (V_ISARRAY(&pInPoints) && V_R8(&pInPoints), E_INVALIDARG);
		pArray = V_ISBYREF (&pInPoints)  ? *pInPoints.pparray : pInPoints.parray;
		ERROR_EXPR_FALSE (NULL != pArray, E_INVALIDARG);

	MC::ArrayDouble	ptsIn(pArray);

//		ERROR_EXPR_FALSE (ptsIn.Attach (pArray), E_INVALIDARG);
		ERROR_EXPR_FALSE (0 == ptsIn.Elements() % 3, CST_E_INVALIDCOORDCOUNT);

	MC::ArrayDouble	ptsOut (MC::Dim (ptsIn.Elements()));
	double	*pdIn = &ptsIn[0];
	double	*pdOut = &ptsOut[0];

		memcpy (pdOut, pdIn, sizeof(double) * ptsIn.Elements());
		ptsIn.Detach();
		if (!SUCCEEDED ((hr = Transform (guid, ptsOut.Elements() / 3, (CSCOORD *)pdOut))))   
			return hr;

		::VariantInit (pOutPoints);
		V_VT(pOutPoints) = VT_R8 + VT_ARRAY;
		V_ARRAY(pOutPoints) = ptsOut.Detach();
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCoordTransform::TransformInverse (BSTR strGUID, VARIANT pInPoints, VARIANT *pOutPoints) 
{
	CHECKINPOINTER(pOutPoints);
	COM_TRY {
	GUID guid;
	HRESULT	hr;

		ERROR_FAILED_HRESULT ((hr=::CLSIDFromString (strGUID, &guid)), hr);

	SAFEARRAY *pSrcArray = NULL;

		ERROR_EXPR_FALSE (V_ISARRAY(&pInPoints) && V_R8(&pInPoints), E_INVALIDARG);
		pSrcArray = V_ISBYREF (&pInPoints)  ? *pInPoints.pparray : pInPoints.parray;
		ERROR_EXPR_FALSE (NULL != pSrcArray, E_INVALIDARG);

	MC::ArrayDouble	ptsIn(pSrcArray);

//		ERROR_EXPR_FALSE (ptsIn.Attach (pSrcArray), E_INVALIDARG);
		ERROR_EXPR_FALSE (0 == ptsIn.Elements() % 3, CST_E_INVALIDCOORDCOUNT);

	MC::ArrayDouble	ptsOut (MC::Dim (ptsIn.Elements()));
	double	*pdIn = &ptsIn[0];
	double	*pdOut = &ptsOut[0];

		memcpy (pdOut, pdIn, sizeof(double) * ptsIn.Elements());
		if (!SUCCEEDED ((hr = TransformInverse (guid, ptsIn.Elements() / 3, (CSCOORD *)pdOut))))   
			return hr;
			
		::VariantInit (pOutPoints);
		V_VT(pOutPoints) = VT_R8 + VT_ARRAY;
		V_ARRAY(pOutPoints) = ptsOut.Detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCoordTransform::GetGoodEnvelope(
	double *lowerLeftX, double *lowerLeftY, double *upperRightX, double *upperRightY)  
{
	CHECKINPOINTER(lowerLeftX);
	CHECKINPOINTER(lowerLeftY);
	CHECKINPOINTER(upperRightX);
	CHECKINPOINTER(upperRightY);

	COM_TRY {
		ERROR_FAILED_HRESULT (WTRiASCSValidate(m_pOutputCS)->IsValid (), CST_E_INVALIDDESTINATIONCOORDSYSTEM);

	CSetLocale	loc;
	CRegKey	rKey;

		if (0 == m_goodEnv[0].X && 0 == m_goodEnv[0].Y && 0 == m_goodEnv[1].X && 0 == m_goodEnv[1].Y) {
		CTRiASCCSKeys	keys (L"CoordinateSystems\\DefaultEnvelope");
		CComBSTR	strVal;
		HRESULT		hr;

			if (!SUCCEEDED (hr = keys.QueryValue (strVal, L""))) 
				keys.CopyHKLM2HKCU();

			{
				USES_CONVERSION;
				m_goodEnv[0].X = SUCCEEDED (keys.QueryValue (strVal, L"XMin")) ? atof (OLE2A (strVal)) : 6.0;
				m_goodEnv[0].Y = SUCCEEDED (keys.QueryValue (strVal, L"YMin")) ? atof (OLE2A (strVal)) : 40.0;
				m_goodEnv[1].X = SUCCEEDED (keys.QueryValue (strVal, L"XMax")) ? atof (OLE2A (strVal)) : 15.0;
				m_goodEnv[1].Y = SUCCEEDED (keys.QueryValue (strVal, L"YMax")) ? atof (OLE2A (strVal)) : 55.0;
			}
		}

	LPDispatchMap::iterator it = m_mapOfCS.find (m_guidWGS84.g);
	
		if (m_mapOfCS.end() == it) {
		WTRiASCS WGS84 (CLSID_TRiASCS);
		WTRiASCSGCS	gcs;
	
			WGS84 -> put_CoordSystemType (tcsCS_Geographic);
			WGS84 -> get_GeographicCS (gcs.ppi());
			gcs -> put_UnitOfAngle (tcsUOA_Degree);
	
		CComBSTR strGUID;
	
			WGS84 -> get_GUID (CLEARED(strGUID));
			::CLSIDFromString (strGUID, &m_guidWGS84.g);
			AddInputCS (WGS84);
			WGS84 -> Recompute();
		}
	
	CSCOORD	goodEnv[2];
	
		goodEnv[0] = m_goodEnv[0];
		goodEnv[1] = m_goodEnv[1];

		Transform (m_guidWGS84.c, 2, m_goodEnv, goodEnv);

		*lowerLeftX = goodEnv[0].X;
		*lowerLeftY = goodEnv[0].Y;
		*upperRightX = goodEnv[1].X;
		*upperRightY = goodEnv[1].Y;
	
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASCoordTransform::SetGoodEnvelope (
	double lowerLeftX, double lowerLeftY, double upperRightX, double upperRightY)  
{
	m_goodEnv[0].X = lowerLeftX;
	m_goodEnv[0].Y = lowerLeftY;
	m_goodEnv[1].X = upperRightX;
	m_goodEnv[1].Y = upperRightY;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASRawCoordTransform; direkte Transformation von Koordinatenfeldern

HRESULT CTRiASCoordTransform::Transform (CSID CoordSysGUID, long nCoords, CSCOORD* pInPoints, CSCOORD* pOutPoints)  
{
	ERROR_EXPR_FALSE (NULL != pInPoints, E_INVALIDARG);
	CHECKINPOINTER(pOutPoints);
	COM_TRY {
	_G g(CoordSysGUID);
	
		if (pOutPoints != pInPoints)	// do not transform inplace
			memcpy (pOutPoints, pInPoints, nCoords * sizeof(CSCOORD));
		return Transform (g.g, nCoords, pOutPoints);
	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCoordTransform::TransformInverse (CSID CoordSysGUID, long nCoords, CSCOORD* pInPoints, CSCOORD* pOutPoints)  
{
	ERROR_EXPR_FALSE (NULL != pInPoints, E_INVALIDARG);
	CHECKINPOINTER(pOutPoints);
	COM_TRY {
	_G g(CoordSysGUID);

		if (pOutPoints != pInPoints)	// do not transform inplace
			memcpy (pOutPoints, pInPoints, nCoords * sizeof(CSCOORD));
		return TransformInverse (g.g, nCoords, pOutPoints);
	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCoordTransform::ChangingCS(ITRiASCS* pCS, VARIANT_BOOL *canChange) 
{
	return S_OK;
}

HRESULT CTRiASCoordTransform::CSToChange(ITRiASCS* pCS)  
{
	return S_OK;
}

HRESULT CTRiASCoordTransform::RecomputePath (WTRiASCS& csIn, WTRiASCS& csOut, bool bDTransIntern)  
{
	ERROR_FAILED_HRESULT (WTRiASCSValidate(csIn)->RecomputeTransformation(NULL), CST_E_INVALIDSOURCECOORDSYSTEM);

	if (csOut.IsValid()) {
		ERROR_FAILED_HRESULT (WTRiASCSValidate(csOut)->RecomputeTransformation(NULL), CST_E_INVALIDSOURCECOORDSYSTEM);
		if (bDTransIntern)  {
		WTRiASCSDatumTransformation	dTransIn, dTransOut;
		WTRiASCSGCS gcsIn, gcsOut;

			ERROR_FAILED_HRESULT (csOut -> get_DatumTransformation (dTransOut.ppi()), CST_E_INVALIDDESTINATIONCOORDSYSTEM);
			ERROR_FAILED_HRESULT (csOut -> get_GeographicCS (gcsOut.ppi()), CST_E_INVALIDDESTINATIONCOORDSYSTEM);
			ERROR_FAILED_HRESULT (WTRiASCS(csIn) -> get_DatumTransformation (dTransIn.ppi()), CST_E_INVALIDDESTINATIONCOORDSYSTEM);
			ERROR_FAILED_HRESULT (WTRiASCS(csIn) -> get_GeographicCS (gcsIn.ppi()), CST_E_INVALIDDESTINATIONCOORDSYSTEM);
			ERROR_FAILED_HRESULT (WTRiASCSValidateDatum(dTransIn) -> RecomputeDatumTransformation (gcsIn, gcsOut, dTransOut), CST_E_INCOMPATIBLEDATUMTRANSFORMATION);
		}
	}
	return S_OK;
}

namespace {
	bool HasGeocentricTranslation (ITRiASCS *pICS)
	{
		_ASSERTE(NULL != pICS);

	WTRiASCSDatumTransformation	Trans;
	TRIASCSDTRANSALGORITHM rgAlgo;

		if (SUCCEEDED(pICS -> get_DatumTransformation (Trans.ppi()))) {
			Trans -> get_TransformationAlgorithm(&rgAlgo);
			return (rgAlgo == tcsDTA_GeocentricTranslations) ? true : false;
		}
		return false;	// im Zweifelsfalle eben bezweifeln
	}
}

HRESULT CTRiASCoordTransform::CSChanged(/*in]*/ ITRiASCS* pCS)  
{
// erstmal feststellen, ob eines der Koordinatensysteme nicht GeocentricTranslation
// eingestellt hat
	m_bDTransIntern = TRUE;
	if (m_pOutputCS.IsValid() && !HasGeocentricTranslation(m_pOutputCS))
		m_bDTransIntern = FALSE;

	if (m_bDTransIntern) {
		for (LPDispatchMap::iterator it = m_mapOfCS.begin(); it != m_mapOfCS.end(); ++it) 
		{
		WTRiASCS CS ((*it).second.GetTRiASCS());

			_ASSERTE(CS.IsValid());
			if (!HasGeocentricTranslation(CS)) {
				m_bDTransIntern = FALSE;
				break;
			}
		}
	}

// jetzt wirklich neu berechnen
CComBSTR strCsGUID;
GUID guidCs;

	RETURN_FAILED_HRESULT (pCS -> get_GUID (CLEARED(strCsGUID)));
	RETURN_FAILED_HRESULT (::CLSIDFromString (strCsGUID, &guidCs));

GUID guid = IID_NULL;

	if (m_pOutputCS.IsValid()) {
	CComBSTR strGUID;
		
		RETURN_FAILED_HRESULT (m_pOutputCS -> get_GUID (CLEARED(strGUID)));
		RETURN_FAILED_HRESULT (::CLSIDFromString (strGUID, &guid));
	}
	if (guid == guidCs) {
	// Ausgangskoordinatensystem wurde geändert
		for (LPDispatchMap::iterator it = m_mapOfCS.begin(); it != m_mapOfCS.end(); ++it) 
		{
		WTRiASCS CS ((*it).second.GetTRiASCS());

			RETURN_FAILED_HRESULT (RecomputePath (CS, m_pOutputCS, m_bDTransIntern));

		// Feststellen, ob überhaupt eine Transformation notwendig ist
		BOOL fMustTransform = (S_OK != EqualCoordSystems (m_pOutputCS, CS)) ? TRUE : FALSE;
		BOOL fMustTransformDatum = (S_OK != EqualDatum (m_pOutputCS, CS)) ? TRUE : FALSE;

			(*it).second.MustTransform(fMustTransform);
			(*it).second.MustTransformDatum(fMustTransformDatum);
		}
	} 
	else {
	// eines der Eingangsysteme wurde geändert
	LPDispatchMap::iterator it = m_mapOfCS.find (guidCs);
	
		ERROR_EXPR_TRUE (m_mapOfCS.end() == it, CST_E_COORDSYSTEMNOTFOUND);

	WTRiASCS CS ((*it).second.GetTRiASCS());
	
		RETURN_FAILED_HRESULT (RecomputePath (CS, m_pOutputCS, m_bDTransIntern));

	// Feststellen, ob überhaupt eine Transformation notwendig ist
	BOOL fMustTransform = (S_OK != EqualCoordSystems (m_pOutputCS, CS)) ? TRUE : FALSE;
	BOOL fMustTransformDatum = (S_OK != EqualDatum (m_pOutputCS, CS)) ? TRUE : FALSE;

		(*it).second.MustTransform(fMustTransform);
		(*it).second.MustTransformDatum(fMustTransformDatum);
	}
	return S_OK;
}
