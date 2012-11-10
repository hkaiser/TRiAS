// $Header: $
// Copyright© 1999-2003 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 27.01.2003 20:14:49 
//
// @doc
// @module NativeConnectionFilter.cpp | ConnectionFilter support for TRiAS databases

#include "trias01p.hxx"

#include "resource.h"

#include <ospace/utility/autoptr.h>

#include <math.h>
#include <float.h>
#include <GMObjects/GMObjects.h>

#include <dbmsg.hmc>
#include <ciid.h>
#include <ActDB.h>
#include <Array.h>
#include <ErrInst.hxx>
#include <DBTypes.h>
#include <NativeObject.h>

#include "ObjectGiST.h"
#include "RectangleOps.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

namespace trias_nativeobject {

///////////////////////////////////////////////////////////////////////////////
// Testen, ob Objekt etwas mit dem ConnectFilter zu tun hat
HRESULT CNativeObject::ApplyConnectFilterPoint(LPCSTR pcName, CONNECTFILTEREX *pFilter)
{
	if (!m_fIsValid)
		return E_UNEXPECTED;

#if defined(_DEBUG)
DWORD dwType = 0;

	RETURN_FAILED_HRESULT(GetObjectType (&dwType));
	_ASSERTE(dwType == OTPunkt || dwType == OTText);		// gegebenes Objekt ist wirklich Punkt-/TextObjekt
#endif // _DEBUG

CActDB ActDB(m_hPr);
DB_ADDR_OBL dbaOBL(m_hPr, m_lONr);
struct obl OBLSatz;
ErrCode RC;

	__ReadHR(dbaOBL, OBLSatz);
	if (0 == OBLSatz.zokp)
		return HRESULT_FROM_ERRCODE(EC_STATUSERROR);		// falscher Objekttyp

DB_ADDR dbapol(m_hPr);
struct pol POLSatz;

	dbapol.file_no = POL;
	dbapol.rec_no = OBLSatz.zokp;
	__ReadHR (dbapol, POLSatz);

// wenn außerhalb des benötigten Bereiches, dann wieder raus (S_FALSE)
	switch(pFilter -> m_iMode) {
	case CF_Rectangle_OverlappedContainers:
	case CF_Rectangle_ContainedContainers:
	case CF_Rectangle_OverlappedPoints:
	case CF_Rectangle_ContainedPoints:
	case CF_Rectangle_OverlappedObjects:
	case CF_Rectangle_ContainedObjects:
	// überlappend oder vollständig im Rechteck enthalten
		if (!PointInRect(POLSatz.kpkrd.px, POLSatz.kpkrd.py, pFilter))
			return S_FALSE;
		break;

	case CF_Polygon_OverlappedContainers:
	case CF_Polygon_ContainedContainers:
	case CF_Polygon_OverlappedPoints:
	case CF_Polygon_ContainedPoints:
	case CF_Polygon_ContainedObjects:
	case CF_Polygon_OverlappedObjects:
		{
		bool fInner = false;
		
			RETURN_FAILED_HRESULT(PunktLage(POLSatz.kpkrd.px, POLSatz.kpkrd.py, 
				pFilter, fInner));
			if (!fInner)
				return S_FALSE;
		}
		break;

	default:
		_ASSERTE(!"Wrong CF_... constant");
		break;
	}
	return S_OK;	// Punkt ist innerhalb
}

HRESULT CNativeObject::ApplyConnectFilterLine(LPCSTR pcName, CONNECTFILTEREX *pFilter)
{
	if (!m_fIsValid)
		return E_UNEXPECTED;

#if defined(_DEBUG)
DWORD dwType = 0;

	RETURN_FAILED_HRESULT(GetObjectType (&dwType));
	_ASSERTE(dwType == OTLinie);		// gegebenes Objekt ist wirklich LinienObjekt
#endif // _DEBUG

CActDB ActDB(m_hPr);
DB_ADDR_OBL dbaOBL(m_hPr, m_lONr);
struct obl OBLSatz;
ErrCode RC;

	__ReadHR(dbaOBL, OBLSatz);
	if (0 == OBLSatz.zovol)
		return HRESULT_FROM_ERRCODE(EC_STATUSERROR);		// falscher Objekttyp

// Container besorgen
double dCont[4];

	RETURN_FAILED_HRESULT(GetKantenCont (OBLSatz.zovol, dCont));
	switch(pFilter -> m_iMode) {
	case CF_Rectangle_OverlappedContainers:
	// überlappende Rechtecke
		if (Disjoint(dCont, pFilter))
			return S_FALSE;	// disjoint containers
		break;

	case CF_Rectangle_OverlappedPoints:
	case CF_Rectangle_OverlappedObjects:
	// überlappend: Stützstrecken mit rechteckigem Filter
		{
			if (Disjoint(dCont, pFilter))
				return S_FALSE;	// disjoint containers

		// alle Stützstrecken des zu untersuchenden Objektes durchgehen 
		double_v vecX, vecY;
		ulong_v vecKnt;

			RETURN_FAILED_HRESULT(GetLineGeometry(pcName, vecX, vecY));

		double_i itx = vecX.begin();
		double_i ity = vecY.begin();
		bool fInside = PointInRect(*itx, *ity, pFilter);
		bool fInsideNext = PointInRect(*++itx, *++ity, pFilter);

			if (!fInside && !fInsideNext) {
				double_i endx = vecX.end();
				while (!fInsideNext && itx != endx) 
					fInsideNext = PointInRect(*++itx, *++ity, pFilter);
			}
			if (fInside || fInsideNext)
				return S_OK;	// wenigstens ein Stützpunkt liegt drin

		// jetzt kann noch eine Stützstrecke das Rechteck schneiden
			for (long i = 1; i < vecX.size(); ++i) {
				if (!Disjoint (vecX[i-1], vecY[i-1], vecX[i], vecY[i], pFilter)) {
					if (Intersection(vecX[i-1], vecY[i-1], vecX[i], vecY[i], 
							pFilter->m_dXMin, pFilter->m_dYMin, pFilter->m_dXMin, pFilter->m_dYMax) ||
						Intersection(vecX[i-1], vecY[i-1], vecX[i], vecY[i], 
							pFilter->m_dXMin, pFilter->m_dYMax, pFilter->m_dXMax, pFilter->m_dYMax) ||
						Intersection(vecX[i-1], vecY[i-1], vecX[i], vecY[i], 
							pFilter->m_dXMax, pFilter->m_dYMax, pFilter->m_dXMax, pFilter->m_dYMin) ||
						Intersection(vecX[i-1], vecY[i-1], vecX[i], vecY[i], 
							pFilter->m_dXMax, pFilter->m_dYMin, pFilter->m_dXMin, pFilter->m_dYMin))
					{
						return S_OK;
					}
				}
			}
			return S_FALSE;
		}
		break;

	case CF_Rectangle_ContainedContainers:
	// vollständig im Rechteck enthalten
		if (!Inside(dCont, pFilter))
			return S_FALSE;
		break;

	case CF_Rectangle_ContainedPoints:
	case CF_Rectangle_ContainedObjects:
	// Stützstrecken vollständig in rechteckigem Filter enthalten
		{
			if (!Inside(dCont, pFilter))
				return S_FALSE;

		// alle Stützstrecken des zu untersuchenden Objektes durchgehen 
		double_v vecX, vecY;
		ulong_v vecKnt;

			RETURN_FAILED_HRESULT(GetLineGeometry(pcName, vecX, vecY));

		double_i itx = vecX.begin();
		double_i ity = vecY.begin();
		bool fInside = PointInRect(*itx, *ity, pFilter);
		bool fInsideNext = PointInRect(*++itx, *++ity, pFilter);

			if (fInside && fInsideNext) {
				double_i endx = vecX.end();
				while (fInsideNext && itx != endx) 
					fInsideNext = PointInRect(*++itx, *++ity, pFilter);
			}
			if (!fInside || !fInsideNext)
				return S_FALSE;	// wenigstens ein Stützpunkt liegt draußen
		}
		break;

	case CF_Polygon_OverlappedContainers:
		{
		// wenn sich nicht mal die Container überlappen, dann gleich raus
			if (Disjoint(dCont, pFilter))
				return S_FALSE;	// disjoint containers

			if (Contain(dCont, pFilter))
				return S_OK;	// Filter ist vollständig überlappt

		// wenn wenigstens ein Eckpunkt drinliegt, ist das Objekt drin
		bool fInner = false;
		
			RETURN_FAILED_HRESULT(PunktLage(dCont[XMIN_IDX], dCont[YMIN_IDX], pFilter, fInner));
			if (fInner) return S_OK;
			RETURN_FAILED_HRESULT(PunktLage(dCont[XMIN_IDX], dCont[YMAX_IDX], pFilter, fInner));
			if (fInner) return S_OK;
			RETURN_FAILED_HRESULT(PunktLage(dCont[XMAX_IDX], dCont[YMAX_IDX], pFilter, fInner));
			if (fInner) return S_OK;
			RETURN_FAILED_HRESULT(PunktLage(dCont[XMAX_IDX], dCont[YMIN_IDX], pFilter, fInner));
			if (!fInner) return S_FALSE;
		}
		break;

	case CF_Polygon_OverlappedPoints:
	case CF_Polygon_OverlappedObjects:
	// überlappend: Stützstrecken in Polygonfilter
		{
			using namespace trias_gist;

			if (Disjoint(dCont, pFilter))
				return S_FALSE;	// disjoint containers

		// alle Stützstrecken des zu untersuchenden Objektes durchgehen 
		// (Außenkontur genügt)
		double_v vecX, vecY;
		ulong_v vecKnt;
		bool fIntersects = false;
		double *pX = pFilter->m_pX;
		double *pY = pFilter->m_pY;

			RETURN_FAILED_HRESULT(GetLineGeometry(pcName, vecX, vecY));
			for (long i = 1; !fIntersects && i < vecX.size(); ++i) {
			GiSTcursor *cursor = pFilter->m_prsTree->Search(vecX[i-1], vecX[i], 
				vecY[i-1], vecY[i]);
			auto_ptr<GiSTentry> entry (cursor->Next());

				while (NULL != entry.get()) {
				GiSTpage k = entry->Ptr();

					if (Intersection(pX[k-1], pY[k-1], pX[k], pY[k], 
						vecX[i-1], vecY[i-1], vecX[i], vecY[i]))
					{
						fIntersects = true;
						break;		// while
					}
					entry = auto_ptr<GiSTentry>(cursor->Next());
				}
			}
			if (fIntersects)
				return S_OK;		// es gibt (mindestens) einen Schnitt

		// einen Punkt auf inerhalb testen
		bool fInner = false;

			RETURN_FAILED_HRESULT(PunktLage(vecX[0], vecY[0], pFilter, fInner));
			if (!fInner) return S_FALSE;			// alles außerhalb
		}
		break;

	case CF_Polygon_ContainedContainers:
		{
		// wenn Container nicht enthalten ist, dann ist das Objekt auch nicht drin
			if (!Inside(dCont, pFilter))
				return S_FALSE;

		// wenn wenigstens ein Eckpunkt draußenliegt, ist das Objekt draußen
		bool fInner = false;
		
			RETURN_FAILED_HRESULT(PunktLage(dCont[XMIN_IDX], dCont[YMIN_IDX], pFilter, fInner));
			if (!fInner) return S_FALSE;
			RETURN_FAILED_HRESULT(PunktLage(dCont[XMIN_IDX], dCont[YMAX_IDX], pFilter, fInner));
			if (!fInner) return S_FALSE;
			RETURN_FAILED_HRESULT(PunktLage(dCont[XMAX_IDX], dCont[YMAX_IDX], pFilter, fInner));
			if (!fInner) return S_FALSE;
			RETURN_FAILED_HRESULT(PunktLage(dCont[XMAX_IDX], dCont[YMIN_IDX], pFilter, fInner));
			if (!fInner) return S_FALSE;
		}
		break;

	case CF_Polygon_ContainedPoints:
	case CF_Polygon_ContainedObjects:
	// Stützstrecken in Polygonfilter enthalten
		{
			using namespace trias_gist;

		// wenn der Container nicht vollständig im Suchcontainer liegt, dann 
		// liegt das Objekt auch nicht drin
			if (!Inside(dCont, pFilter))
				return S_FALSE;

		// alle Stützstrecken des zu untersuchenden Objektes durchgehen 
		// (Außenkontur genügt)
		double_v vecX, vecY;
		bool fIntersects = false;
		double *pX = pFilter->m_pX;
		double *pY = pFilter->m_pY;

			RETURN_FAILED_HRESULT(GetLineGeometry(pcName, vecX, vecY));
			for (long i = 1; !fIntersects && i < vecX.size(); ++i) {
			GiSTcursor *cursor = pFilter->m_prsTree->Search(vecX[i-1], vecX[i], 
				vecY[i-1], vecY[i]);
			auto_ptr<GiSTentry> entry (cursor->Next());

				while (NULL != entry.get()) {
				GiSTpage k = entry->Ptr();

					if (Intersection(pX[k-1], pY[k-1], pX[k], pY[k], 
						vecX[i-1], vecY[i-1], vecX[i], vecY[i]))
					{
						fIntersects = true;
						break;				// while
					}
					entry = auto_ptr<GiSTentry>(cursor->Next());
				}
			}
			if (fIntersects)
				return S_FALSE;		// es gibt (mindestens) einen Schnitt

		// einen Punkt auf inerhalb testen
		bool fInner = false;

			RETURN_FAILED_HRESULT(PunktLage(vecX[0], vecY[0], pFilter, fInner));
			if (!fInner) return S_FALSE;		// alles außerhalb
		}
		break;

	default:
		_ASSERTE(!"Wrong CF_... constant");
		break;
	}
	return S_OK;
}

HRESULT CNativeObject::ApplyConnectFilterArea(LPCSTR pcName, CONNECTFILTEREX *pFilter)
{
	if (!m_fIsValid)
		return E_UNEXPECTED;

#if defined(_DEBUG)
DWORD dwType = 0;

	RETURN_FAILED_HRESULT(GetObjectType (&dwType));
	_ASSERTE(dwType == OTFlaeche);		// gegebenes Objekt ist wirklich FlächenObjekt
#endif // _DEBUG

CActDB ActDB(m_hPr);
DB_ADDR_OBL dbaOBL(m_hPr, m_lONr);
struct obl OBLSatz;
ErrCode RC;

	__ReadHR(dbaOBL, OBLSatz);

	if (0 == OBLSatz.zovoma)
		return HRESULT_FROM_ERRCODE(EC_STATUSERROR);		// falscher Objekttyp

DB_ADDR dbamal(m_hPr);
struct mal mal;

	dbamal.file_no = MAL;
	dbamal.rec_no = OBLSatz.zovoma;
	__ReadHR (dbamal, mal);

// Container besorgen
double dCont[4];

	RETURN_FAILED_HRESULT(GetMaschenCont (mal.zmkfm, dCont));
	switch(pFilter -> m_iMode) {
	case CF_Rectangle_OverlappedContainers:
	// überlappende Rechtecke
		if (Disjoint(dCont, pFilter))
			return S_FALSE;	// disjoint containers
		break;

	case CF_Rectangle_OverlappedPoints:
	case CF_Rectangle_OverlappedObjects:
	// überlappend: Stützstrecken mit rechteckigem Filter
		{
			if (Disjoint(dCont, pFilter))
				return S_FALSE;	// disjoint containers

		// alle Stützstrecken des zu untersuchenden Objektes durchgehen 
		// (Außenkontur genügt)
		double_v vecX, vecY;
		ulong_v vecKnt;

			RETURN_FAILED_HRESULT(GetAreaGeometry(pcName, vecX, vecY, vecKnt));

		double_i itx = vecX.begin();
		double_i ity = vecY.begin();
		bool fInside = PointInRect(*itx, *ity, pFilter);
		bool fInsideNext = PointInRect(*++itx, *++ity, pFilter);

			if (!fInside && !fInsideNext) {
				double_i endx = vecX.end();
				while (!fInsideNext && itx != endx) 
					fInsideNext = PointInRect(*++itx, *++ity, pFilter);
			}
			if (fInside || fInsideNext)
				return S_OK;	// wenigstens ein Stützpunkt liegt drin

		// kein Schnitt vorhanden, also einen Punkt auf innerhalb testen
			fInside = PointInRect(vecX[0], vecY[0], pFilter);
			if (fInside) return S_OK;			// alles innerhalb

		// immer noch kein Schnitt also Ecken des Rechtecks gegen Objekt testen
			RETURN_FAILED_HRESULT(PunktLage(pFilter->m_dXMin, pFilter->m_dYMin, 
				vecX.begin(), vecY.begin(), vecKnt[0], fInside));
			if (fInside) return S_OK;			// RechtecksEcke innerhalb
			RETURN_FAILED_HRESULT(PunktLage(pFilter->m_dXMin, pFilter->m_dYMax, 
				vecX.begin(), vecY.begin(), vecKnt[0], fInside));
			if (fInside) return S_OK;			// RechtecksEcke innerhalb
			RETURN_FAILED_HRESULT(PunktLage(pFilter->m_dXMax, pFilter->m_dYMax, 
				vecX.begin(), vecY.begin(), vecKnt[0], fInside));
			if (fInside) return S_OK;			// RechtecksEcke innerhalb
			RETURN_FAILED_HRESULT(PunktLage(pFilter->m_dXMax, pFilter->m_dYMin, 
				vecX.begin(), vecY.begin(), vecKnt[0], fInside));
			if (!fInside) return S_FALSE;		// nicht überdeckt
		}
		break;

	case CF_Rectangle_ContainedContainers:
	// vollständig im Rechteck enthalten
		if (!Inside(dCont, pFilter))
			return S_FALSE;
		break;

	case CF_Rectangle_ContainedPoints:
	case CF_Rectangle_ContainedObjects:
	// Stützstrecken vollständig in rechteckigem Filter enthalten
		{
			if (!Inside(dCont, pFilter))
				return S_FALSE;

		// alle Stützstrecken des zu untersuchenden Objektes durchgehen 
		// (Außenkontur genügt)
		double_v vecX, vecY;
		ulong_v vecKnt;

			RETURN_FAILED_HRESULT(GetAreaGeometry(pcName, vecX, vecY, vecKnt));

		double_i itx = vecX.begin();
		double_i ity = vecY.begin();
		bool fInside = PointInRect(*itx, *ity, pFilter);
		bool fInsideNext = PointInRect(*++itx, *++ity, pFilter);

			if (fInside && fInsideNext) {
				double_i endx = vecX.end();
				while (fInsideNext && itx != endx) 
					fInsideNext = PointInRect(*++itx, *++ity, pFilter);
			}
			if (!fInside || !fInsideNext)
				return S_FALSE;	// wenigstens ein Stützpunkt liegt draußen
		}
		break;

	case CF_Polygon_OverlappedContainers:
		{
		// wenn sich nicht mal die Container überlappen, dann gleich raus
			if (Disjoint(dCont, pFilter))
				return S_FALSE;	// disjoint containers

			if (Contain(dCont, pFilter))
				return S_OK;	// Filter ist vollständig überlappt

		// wenn wenigstens ein Eckpunkt drinliegt, ist das Objekt drin
		bool fInner = false;

			RETURN_FAILED_HRESULT(PunktLage(dCont[XMIN_IDX], dCont[YMIN_IDX], pFilter, fInner));
			if (fInner) return S_OK;
			RETURN_FAILED_HRESULT(PunktLage(dCont[XMIN_IDX], dCont[YMAX_IDX], pFilter, fInner));
			if (fInner) return S_OK;
			RETURN_FAILED_HRESULT(PunktLage(dCont[XMAX_IDX], dCont[YMAX_IDX], pFilter, fInner));
			if (fInner) return S_OK;
			RETURN_FAILED_HRESULT(PunktLage(dCont[XMAX_IDX], dCont[YMIN_IDX], pFilter, fInner));
			if (!fInner) return S_FALSE;
		}
		break;

	case CF_Polygon_OverlappedPoints:
	case CF_Polygon_OverlappedObjects:
	// überlappend: Stützstrecken in Polygonfilter
		{
			using namespace trias_gist;

			if (Disjoint(dCont, pFilter))
				return S_FALSE;	// disjoint containers

		// alle Stützstrecken des zu untersuchenden Objektes durchgehen 
		// (Außenkontur genügt)
		double_v vecX, vecY;
		ulong_v vecKnt;
		bool fIntersects = false;
		double *pX = pFilter->m_pX;
		double *pY = pFilter->m_pY;

			RETURN_FAILED_HRESULT(GetAreaGeometry(pcName, vecX, vecY, vecKnt));
			for (long i = 1; !fIntersects && i < vecKnt[0]; ++i) {
			GiSTcursor *cursor = pFilter->m_prsTree->Search(vecX[i-1], vecX[i], 
				vecY[i-1], vecY[i]);
			auto_ptr<GiSTentry> entry (cursor->Next());

				while (NULL != entry.get()) {
				GiSTpage k = entry->Ptr();

					if (Intersection(pX[k-1], pY[k-1], pX[k], pY[k], 
						vecX[i-1], vecY[i-1], vecX[i], vecY[i]))
					{
						fIntersects = true;
						break;		// while
					}
					entry = auto_ptr<GiSTentry>(cursor->Next());
				}
			}
			if (fIntersects)
				return S_OK;		// es gibt (mindestens) einen Schnitt

		// kein Schnitt vorhanden, also einen Punkt auf innerhalb testen
		bool fInner = false;

			RETURN_FAILED_HRESULT(PunktLage(vecX[0], vecY[0], pFilter, fInner));
			if (fInner) return S_OK;			// alles innerhalb

			RETURN_FAILED_HRESULT(PunktLage(pFilter->m_pX[0], pFilter->m_pY[0], 
				vecX.begin(), vecY.begin(), vecKnt[0], fInner));
			if (!fInner) return S_FALSE;		// nicht überdeckt
		}
		break;

	case CF_Polygon_ContainedContainers:
		{
		// wenn Container nicht enthalten ist, dann ist das Objekt auch nicht drin
			if (!Inside(dCont, pFilter))
				return S_FALSE;

		// wenn wenigstens ein Eckpunkt draußenliegt, ist das Objekt draußen
		bool fInner = false;

			RETURN_FAILED_HRESULT(PunktLage(dCont[XMIN_IDX], dCont[YMIN_IDX], pFilter, fInner));
			if (!fInner) return S_FALSE;
			RETURN_FAILED_HRESULT(PunktLage(dCont[XMIN_IDX], dCont[YMAX_IDX], pFilter, fInner));
			if (!fInner) return S_FALSE;
			RETURN_FAILED_HRESULT(PunktLage(dCont[XMAX_IDX], dCont[YMAX_IDX], pFilter, fInner));
			if (!fInner) return S_FALSE;
			RETURN_FAILED_HRESULT(PunktLage(dCont[XMAX_IDX], dCont[YMIN_IDX], pFilter, fInner));
			if (!fInner) return S_FALSE;
		}
		break;

	case CF_Polygon_ContainedPoints:
	case CF_Polygon_ContainedObjects:
	// Stützstrecken in Polygonfilter enthalten
		{
			using namespace trias_gist;

		// wenn der Container nicht vollständig im Suchcontainer liegt, dann 
		// liegt das Objekt auch nicht drin
			if (!Inside(dCont, pFilter))
				return S_FALSE;

		// alle Stützstrecken des zu untersuchenden Objektes durchgehen 
		// (Außenkontur genügt)
		double_v vecX, vecY;
		ulong_v vecKnt;
		bool fIntersects = false;
		double *pX = pFilter->m_pX;
		double *pY = pFilter->m_pY;

			RETURN_FAILED_HRESULT(GetAreaGeometry(pcName, vecX, vecY, vecKnt));
			for (long i = 1; !fIntersects && i < vecKnt[0]; ++i) {
			GiSTcursor *cursor = pFilter->m_prsTree->Search(vecX[i-1], vecX[i], 
				vecY[i-1], vecY[i]);
			auto_ptr<GiSTentry> entry (cursor->Next());

				while (NULL != entry.get()) {
				GiSTpage k = entry->Ptr();

					if (Intersection(pX[k-1], pY[k-1], pX[k], pY[k], 
						vecX[i-1], vecY[i-1], vecX[i], vecY[i]))
					{
						fIntersects = true;
						break;				// while
					}
					entry = auto_ptr<GiSTentry>(cursor->Next());
				}
			}
			if (fIntersects)
				return S_FALSE;		// es gibt (mindestens) einen Schnitt

		// keinen Schnitt gefunden, also einen Punkt auf innerhalb testen
		bool fInner = false;

			RETURN_FAILED_HRESULT(PunktLage(vecX[0], vecY[0], pFilter, fInner));
			if (!fInner) return S_FALSE;		// alles außerhalb
		}
		break;

	default:
		_ASSERTE(!"Wrong CF_... constant");
		break;
	}
	return S_OK;
}

HRESULT CNativeObject::ApplyConnectFilter(LPCSTR pcName, CONNECTFILTEREX *pFilter)
{
	_ASSERTE(NULL != pFilter);
	_ASSERTE(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

HRESULT hr = S_OK;
DWORD dwType = 0;

	RETURN_FAILED_HRESULT(GetObjectType (&dwType));
	switch (dwType) {
	case OTPunkt:
	case OTText:
	// Punktobjekte
		hr = ApplyConnectFilterPoint (pcName, pFilter);
		break;

	case OTLinie:
	// Linienobjekte
		hr = ApplyConnectFilterLine (pcName, pFilter);
		break;

	case OTFlaeche:
	// Flächenobjekte
		hr = ApplyConnectFilterArea (pcName, pFilter);
		break;

	default:
	// Komplexobjekte etc.
		hr = E_INVALIDARG;
		break;
	}
	return hr;
}

} // namespace trias_nativeobject

