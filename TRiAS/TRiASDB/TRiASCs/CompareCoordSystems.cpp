// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.10.1999 12:56:09
//
// @doc
// @module CompareCoordSystems.cpp | Vergleichen zweier Koordinatensysteme

#include "StdAfx.h"

#include "LibCTF/LibCTFImpl.h"
#include "TRiASCsImpl.h"
#include "CompareCoordSystems.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

namespace compare_cs {

#define RETURN_NOT_EQUAL(x) {HRESULT __hr__ = (x); if (S_FALSE == __hr__) return S_FALSE; THROW_FAILED_HRESULT(__hr__) };

///////////////////////////////////////////////////////////////////////////////
// diverse Parameter verschiedener Kordinatensysteme vergleichen
	template<class CS, class T, class pred>
	HRESULT IsEqual (CS *pICS1, CS *pICS2, pred f, T *)
	{
		COM_TRY {
		T Val1 = T(0);
		T Val2 = T(0);

			THROW_FAILED_HRESULT((pICS1 ->* f)(&Val1));
			THROW_FAILED_HRESULT((pICS2 ->* f)(&Val2));
			if (Val1 != Val2)
				return S_FALSE;			// nicht identisch

		} COM_CATCH;
		return S_OK;
	}

	template<class CS, class T1, class T2, class pred>
	HRESULT IsEqual2 (CS *pICS1, CS *pICS2, pred f, T1 par, T2 *)
	{
		COM_TRY {
		T2 Val1 = T2(0);
		T2 Val2 = T2(0);

			THROW_FAILED_HRESULT((pICS1 ->* f)(par, &Val1));
			THROW_FAILED_HRESULT((pICS2 ->* f)(par, &Val2));
			if (memcmp (&Val1, &Val2, sizeof(T2)))
				return S_FALSE;			// nicht identisch

		} COM_CATCH;
		return S_OK;
	}

///////////////////////////////////////////////////////////////////////////////
// Vergleichen des unterliegenden geodätischen Koordinatensystems
	HRESULT EqualGeodCoordSystems (ITRiASCSGCS *pIGCS1, ITRiASCSGCS *pIGCS2)
	{
		COM_TRY {
			if (NULL == pIGCS1 || NULL == pIGCS2)
				return S_FALSE;		// nichts zu vergleichen, also nicht identisch

			RETURN_NOT_EQUAL(IsEqual (pIGCS1, pIGCS2, ITRiASCSGCS::get_GeodeticDatum, (TRIASCSGEODETICDATUM *)NULL));
			RETURN_NOT_EQUAL(IsEqual (pIGCS1, pIGCS2, ITRiASCSGCS::get_Ellipsoid, (TRIASCSELLIPSOID *)NULL));
			RETURN_NOT_EQUAL(IsEqual (pIGCS1, pIGCS2, ITRiASCSGCS::get_PrimeMeridian, (TRIASCSPRIMEMERIDIAN *)NULL));
			RETURN_NOT_EQUAL(IsEqual (pIGCS1, pIGCS2, ITRiASCSGCS::get_UnitOfAngle, (TRIASCSUNITOFANGLE *)NULL));

		} COM_CATCH;
		return S_OK;
	}

	HRESULT EqualGeodCoordSystems (ITRiASCS *pICS1, ITRiASCS *pICS2)
	{
		COM_TRY {
		WTRiASCSGCS GCS1, GCS2;

			THROW_FAILED_HRESULT(pICS1 -> get_GeographicCS(GCS1.ppi()));
			THROW_FAILED_HRESULT(pICS2 -> get_GeographicCS(GCS2.ppi()));
			RETURN_NOT_EQUAL(EqualGeodCoordSystems (GCS1, GCS2));

		} COM_CATCH;
		return S_OK;
	}

// Projektion vergleichen
	HRESULT EqualProjections (ITRiASCSPCS *pIPCS1, ITRiASCSPCS *pIPCS2)
	{
		COM_TRY {
			if (NULL == pIPCS1 || NULL == pIPCS2)
				return S_FALSE;		// nichts zu vergleichen, also nicht identisch

			RETURN_NOT_EQUAL(IsEqual (pIPCS1, pIPCS2, ITRiASCSPCS::get_ProjectionAlgorithm, (TRIASCSPROJECTIONALGORITHM *)NULL));
			RETURN_NOT_EQUAL(IsEqual (pIPCS1, pIPCS2, ITRiASCSPCS::get_UnitOfLength, (TRIASCSUNITOFLENGTH *)NULL));
			for (int p = 0; p < tcsPP_SizeOfParameterSet; ++p)
			{
				RETURN_NOT_EQUAL(IsEqual2 (pIPCS1, pIPCS2, ITRiASCSPCS::get_ProjectionParameter, TRIASCSPROJECTIONPARAMETER(p), (double *)NULL));
			}

		} COM_CATCH;
		return S_OK;
	}

	HRESULT EqualProjections (ITRiASCS *pICS1, ITRiASCS *pICS2)
	{
		COM_TRY {
		TRIASCSTYPE rgType1, rgType2;

			THROW_FAILED_HRESULT(pICS1 -> get_CoordSystemType(&rgType1));
			THROW_FAILED_HRESULT(pICS2 -> get_CoordSystemType(&rgType2));

			if (rgType1 != tcsCS_Projected || rgType2 != tcsCS_Projected)
				return (rgType1 == rgType2) ? S_OK : S_FALSE;

		// Projektionen nur dann testen, wenn die Koordinatensysteme projektiv sind :-)
		WTRiASCSPCS PCS1, PCS2;

			THROW_FAILED_HRESULT(pICS1 -> get_ProjectedCS(PCS1.ppi()));
			THROW_FAILED_HRESULT(pICS2 -> get_ProjectedCS(PCS2.ppi()));
			RETURN_NOT_EQUAL(EqualProjections (PCS1, PCS2));

		} COM_CATCH;
		return S_OK;
	}
};

///////////////////////////////////////////////////////////////////////////////
// Vergleichen zweier Koordinatensysteme auf Identität
HRESULT EqualCoordSystems (ITRiASCS *pICS1, ITRiASCS *pICS2)
{
	using namespace compare_cs;
	COM_TRY {
		if (NULL == pICS1 || NULL == pICS2)
			return S_FALSE;		// nichts zu vergleichen, also nicht identisch

		RETURN_NOT_EQUAL(IsEqual (pICS1, pICS2, ITRiASCS::get_CoordSystemType, (TRIASCSTYPE *)NULL));
		RETURN_NOT_EQUAL(EqualGeodCoordSystems (pICS1, pICS2));
		RETURN_NOT_EQUAL(EqualProjections (pICS1, pICS2));

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Vergleichen der BezugsEllipsoiden zweier Koordinatensysteme
HRESULT EqualDatum (ITRiASCS *pICS1, ITRiASCS *pICS2)
{
	using namespace compare_cs;
	COM_TRY {
		if (NULL == pICS1 || NULL == pICS2)
			return S_FALSE;		// nichts zu vergleichen, also nicht identisch

		RETURN_NOT_EQUAL(EqualGeodCoordSystems (pICS1, pICS2));
	} COM_CATCH;
	return S_OK;
}

