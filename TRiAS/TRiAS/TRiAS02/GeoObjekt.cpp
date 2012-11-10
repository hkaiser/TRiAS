// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 06/11/1998 10:00:20 PM
//
// @doc
// @module GeoObjekt.cpp  Elementare Geometrie-Objekte

#include "trias02p.hxx"

#if !defined(_FORCE_LEGACY_CODE)

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(Dispatch);						// WDispatch
DefineSmartInterface(EnumVARIANT);					// WEnumVARIANT
DefineSmartInterface(TRiASCSGeometryProperties);	// WTRiASCSGeometryProperties

DefineSmartInterface2(_DGMPoints, IID__DGMPoints);	// W_DGMPoints
DefineSmartInterface2(_DGMGeometryCollection, IID__DGMGeometryCollection);	// W_DGMGeometryCollection
DefineSmartInterface2(_DGMRectangleGeometry, IID__DGMRectangleGeometry);	// W_DGMRectangleGeometry

/////////////////////////////////////////////////////////////////////////////
// Methoden für OBJECTCONTAINER 
ObjContainer::ObjContainer (KoOrd XMin, KoOrd XMax, KoOrd YMin, KoOrd YMax) 
{
	if (XMin < XMax) {
		if (YMin < YMax)
			m_oc.SetRect (XMin, YMin, XMax, YMax);
		else
			m_oc.SetRect (XMin, YMax, XMax, YMin);
	} else {
		if (YMin < YMax)
			m_oc.SetRect (XMax, YMin, XMin, YMax);
		else
			m_oc.SetRect (XMax, YMax, XMin, YMin);
	}
}

ObjContainer::ObjContainer (Punkt Pt, Ausdehnung A) 
{
KoOrd XMin = Pt.GetX(); 
KoOrd YMin = Pt.GetY();
KoOrd XMax = Pt.GetX() + A.GetBreite();
KoOrd YMax = Pt.GetY() + A.GetHoehe();

	if (XMin < XMax) {
		if (YMin < YMax)
			m_oc.SetRect (XMin, YMin, XMax, YMax);
		else
			m_oc.SetRect (XMin, YMax, XMax, YMin);
	} else {
		if (YMin < YMax)
			m_oc.SetRect (XMax, YMin, XMin, YMax);
		else
			m_oc.SetRect (XMax, YMax, XMin, YMin);
	}
}

ObjContainer::ObjContainer (Punkt Pt1, Punkt Pt2) 
{
KoOrd XMin = Pt1.GetX(); 
KoOrd XMax = Pt2.GetX();
KoOrd YMin = Pt1.GetY(); 
KoOrd YMax = Pt2.GetY();

	if (XMin < XMax) {
		if (YMin < YMax)
			m_oc.SetRect (XMin, YMin, XMax, YMax);
		else
			m_oc.SetRect (XMin, YMax, XMax, YMin);
	} else {
		if (YMin < YMax)
			m_oc.SetRect (XMax, YMin, XMin, YMax);
		else
			m_oc.SetRect (XMax, YMax, XMin, YMin);
	}
}

ObjContainer::ObjContainer (const ObjContainer &OC) 
	: m_oc(const_cast<ObjContainer &>(OC).m_oc)
{
}

// Memberfunktionen -----------------------------------------------------------
ObjContainer ObjContainer::InflateCont (int iPercent) 
{
// Werte, um die Container vergrößert werden soll 
KoOrd dXMin = XMin();
KoOrd dXMax = XMax();
KoOrd dYMin = YMin();
KoOrd dYMax = YMax();
KoOrd dX = ((dXMax-dXMin)*iPercent)/200;
KoOrd dY = ((dYMax-dYMin)*iPercent)/200;

	return ObjContainer (dXMin-dX, dXMax+dX, dYMin-dY, dYMax+dY);
}

// ObjContainer direkt verändern ----------------------------------------------
ObjContainer & ObjContainer::ShiftCont (Ausdehnung &A) 
{
	SetXMin(XMin() + A.GetBreite());
	SetXMax(XMax() + A.GetBreite());
	SetYMin(YMin() + A.GetHoehe());
	SetYMax(YMax() + A.GetHoehe());
	return *this;
}

// Verschnitt zweier ObjContainer testen --------------------------------------
bool ObjContainer::operator ^ (ObjContainer &OC) 
{
	if (XMin() > OC.XMax() || XMax() < OC.XMin() ||
		YMin() > OC.YMax() || YMax() < OC.YMin()) 
	{
	// ObjContainer überschneiden sich nicht
		return false;
	}
	return true;
}

// Gemeinsamen Container berechnen --------------------------------------------
ObjContainer ObjContainer::operator + (ObjContainer &OC) const 
{
KoOrd lXMin = XMin();
KoOrd lXMax = XMax();
KoOrd lYMin = YMin();
KoOrd lYMax = YMax();

	if (XMin() > OC.XMin()) lXMin = OC.XMin();
	if (XMax() < OC.XMax()) lXMax = OC.XMax();
	if (YMin() > OC.YMin()) lYMin = OC.YMin();
	if (YMax() < OC.YMax()) lYMax = OC.YMax();

	return ObjContainer(lXMin, lXMax, lYMin, lYMax);
}

void ObjContainer::operator += (ObjContainer &OC) 
{
// zuerst die Maximalwerte behandeln (CSRect ist intern Punkt + Ausdehnung)
	if (XMax() < OC.XMax()) SetXMax(OC.XMax());
	if (XMin() > OC.XMin()) SetXMin(OC.XMin());
	if (YMax() < OC.YMax()) SetYMax(OC.YMax());
	if (YMin() > OC.YMin()) SetYMin(OC.YMin());
}

// Container miteinander verschneiden und gemeinsame Fläche liefern -----------
ObjContainer ObjContainer::operator & (ObjContainer &OC) const
{
KoOrd lXMin = XMin();
KoOrd lXMax = XMax();
KoOrd lYMin = YMin();
KoOrd lYMax = YMax();

	if (XMin() < OC.XMin()) lXMin = OC.XMin();
	if (XMax() > OC.XMax()) lXMax = OC.XMax();
	if (YMin() < OC.YMin()) lYMin = OC.YMin();
	if (YMax() > OC.YMax()) lYMax = OC.YMax();

	return ObjContainer(lXMin, lXMax, lYMin, lYMax);
}


void ObjContainer::operator &= (ObjContainer &OC) 
{
// zuerst die Maximalwerte behandeln (CSRect ist intern Punkt + Ausdehnung)
	if (XMax() > OC.XMax()) SetXMax(OC.XMax());
	if (XMin() < OC.XMin()) SetXMin(OC.XMin());
	if (YMax() > OC.YMax()) SetYMax(OC.YMax());
	if (YMin() < OC.YMin()) SetYMin(OC.YMin());
}


// Liefert, ob der erste der ObjContainer vollständig innerhalb des 
// Zweiten liegt
bool operator < (ObjContainer &O1, ObjContainer &O2)
{
	return (O1.XMin() > O2.XMin() && O1.XMax() < O2.XMax() &&
			O1.YMin() > O2.YMin() && O1.YMax() < O2.YMax());
}

// Liefert, ob der erste der ObjContainer vollständig außerhalb des 
// Zweiten liegt
bool operator > (ObjContainer &O1, ObjContainer &O2)
{
	return (O1.XMin() < O2.XMin() && O1.XMax() > O2.XMax() &&
			O1.YMin() < O2.YMin() && O1.YMax() > O2.YMax());
}

// Liefert, ob der erste der ObjContainer vollständig innerhalb des 
// Zweiten liegt (oder Gleichheit)
bool operator <= (ObjContainer &O1, ObjContainer &O2)
{
	return (O1.XMin() >= O2.XMin() && O1.XMax() <= O2.XMax() &&
			O1.YMin() >= O2.YMin() && O1.YMax() <= O2.YMax());
}

// Liefert, ob der erste der ObjContainer vollständig außerhalb des 
// Zweiten liegt (oder Gleichheit)
bool operator >= (ObjContainer &O1, ObjContainer &O2)
{
	return (O1.XMin() <= O2.XMin() && O1.XMax() >= O2.XMax() &&
			O1.YMin() <= O2.YMin() && O1.YMax() >= O2.YMax());
}

Ausdehnung ObjContainer::operator - (ObjContainer &OC)
{
	return Ausdehnung (((XMax()+XMin()) - (OC.XMax()+OC.XMin()))/2,
					   ((YMax()+YMin()) - (OC.YMax()+OC.YMin()))/2);
}

/////////////////////////////////////////////////////////////////////////////
// Kante
Kante &Kante::operator =(const Kante &rhs)
{
	if (&rhs != this) {
		m_line = rhs.m_line;
		m_oc = rhs.m_oc;
	}
	return *this;
}

// interne Variablenwerte liefern
ObjContainer Kante::GetCont (void)
{
	return m_oc.IsValid() ? ObjContainer(m_oc) : ObjContainer();
}

// gemeinsamen Container erzeugen
ObjContainer Kante::maxCont (const ObjContainer &rOC)
{
KoOrd lXMin = rOC.XMin();
KoOrd lXMax = rOC.XMax();
KoOrd lYMin = rOC.YMin();
KoOrd lYMax = rOC.YMax();

	COM_TRY {
	W_DGMPoints pts;
	double dKoords[3];
	long lCnt = 0;

		THROW_FAILED_HRESULT(m_line -> get_Points(pts.ppi()));
		THROW_FAILED_HRESULT(pts -> get_Count(&lCnt));
		for (long i = 1; i <= lCnt; i++) {
			THROW_FAILED_HRESULT(pts -> GetPoint (i, dKoords));

		// Container aufbauen
			if (dKoords[0] < lXMin) lXMin = dKoords[0];
			if (dKoords[0] > lXMax) lXMax = dKoords[0];
			if (dKoords[1] < lYMin) lYMin = dKoords[1];
			if (dKoords[1] > lYMax) lYMax = dKoords[1];
		}
	} COM_CATCH_RETURN(ObjContainer());
	return ObjContainer(lXMin, lXMax, lYMin, lYMax);
}

// kleinsten gemeinsamen Container bilden
ObjContainer Kante::minCont (const ObjContainer &rOC)
{
KoOrd lXMin = rOC.XMin();
KoOrd lXMax = rOC.XMax();
KoOrd lYMin = rOC.YMin();
KoOrd lYMax = rOC.YMax();

	COM_TRY {
	W_DGMPoints pts;
	double dKoords[3];
	long lCnt = 0;

		THROW_FAILED_HRESULT(m_line -> get_Points(pts.ppi()));
		THROW_FAILED_HRESULT(pts -> get_Count(&lCnt));
		for (long i = 1; i <= lCnt; i++) {
			THROW_FAILED_HRESULT(pts -> GetPoint (i, dKoords));

		// Container aufbauen
			if (dKoords[0] > lXMin) lXMin = dKoords[0];
			if (dKoords[0] < lXMax) lXMax = dKoords[0];
			if (dKoords[1] > lYMin) lYMin = dKoords[1];
			if (dKoords[1] < lYMax) lYMax = dKoords[1];
		}
	} COM_CATCH_RETURN(ObjContainer());
	return ObjContainer(lXMin, lXMax, lYMin, lYMax);
}

void Kante::GetKante (KoOrd x[], KoOrd y[], long &rlCnt)
{
	COM_TRY {
	W_DGMPoints pts;
	double dKoords[3];
	long lCnt = 0;

		THROW_FAILED_HRESULT(m_line -> get_Points(pts.ppi()));
		THROW_FAILED_HRESULT(pts -> get_Count(&lCnt));

	long lToCopy = min(rlCnt, lCnt);

		TX_ASSERT(TIsValidAddress(x, lToCopy*sizeof(KoOrd), true));
		TX_ASSERT(TIsValidAddress(y, lToCopy*sizeof(KoOrd), true));

		for (long i = 0; i < lToCopy; i++) {
			THROW_FAILED_HRESULT(pts -> GetPoint (i+1, dKoords));
			x[i] = dKoords[0];
			y[i] = dKoords[1];
		}

	// Anzahl der kopierten Koordinaten liefern
		rlCnt = lToCopy;
	} COM_CATCH_NORETURN;
}

// interne Werte modifizieren Punkt(e) hinzufügen
void Kante::AddPunkt (const Kante &rK, long lAnzahl, long lIndex)
{
	COM_TRY {
	W_DGMPoints pts;

		THROW_FAILED_HRESULT(m_line -> get_Points(pts.ppi()));
		for (long i = 0; i < lAnzahl; i++) 
		{
		Punkt &rpt = rK.SP(i);
		W_DGMPoint pt (CLSID_TRiASCSPoint);
		
			THROW_FAILED_HRESULT(pt -> put_X(rpt.GetX()));
			THROW_FAILED_HRESULT(pt -> put_Y(rpt.GetY()));
			THROW_FAILED_HRESULT(pts -> Add (pt, CComVariant(lIndex++)));
		}
	} COM_CATCH_NORETURN;
}

void Kante::AddPunkt (KoOrd x[], KoOrd y[], long lAnzahl, long lIndex)
{
	COM_TRY {
	W_DGMPoints pts;

		THROW_FAILED_HRESULT(m_line -> get_Points(pts.ppi()));
		for (long i = 0; i < lAnzahl; i++) 
		{ 
		Punkt rpt (x[i], y[i]);
		W_DGMPoint pt (CLSID_TRiASCSPoint);
		
			THROW_FAILED_HRESULT(pt -> put_X(rpt.GetX()));
			THROW_FAILED_HRESULT(pt -> put_Y(rpt.GetY()));
			THROW_FAILED_HRESULT(pts -> Add (pt, CComVariant(lIndex++)));
		}
	} COM_CATCH_NORETURN;
}

void Kante::SetCont (KoOrd lCont[])
{
	TX_ASSERT(m_oc.IsValid());

	if (m_oc.IsValid()) {
	// zuerst die Maximalwerte behandeln (CSRect ist intern Punkt + Ausdehnung)
		m_oc.put_XMax(lCont[1]);
		m_oc.put_XMin(lCont[0]);
		m_oc.put_YMax(lCont[3]);
		m_oc.put_YMin(lCont[2]);
	}
}

namespace {
	inline HRESULT GetPointCount (IDispatch *pIDisp, long *plCnt)
	{
	W_DGMPolylineGeometry geom(pIDisp);
	W_DGMPoints pts;

		RETURN_FAILED_HRESULT(geom -> get_Points(pts.ppi()));
		RETURN_FAILED_HRESULT(pts -> get_Count(plCnt));
		return S_OK;
	}
}

// Anzahl der Stützpunkte
long Kante::ASP (void) const
{
long lCnt = 0;

	COM_TRY {
		THROW_FAILED_HRESULT(GetPointCount(m_line, &lCnt));
	} COM_CATCH_RETURN(0);
	return lCnt;
}

// Stützpunkt n liefern
Punkt Kante::SP (long n) const
{
double dKoords[3];

	COM_TRY {
	W_DGMPoints pts;

		THROW_FAILED_HRESULT(m_line -> get_Points(pts.ppi()));

#if defined(_DEBUG)
	long lCnt = 0;

		THROW_FAILED_HRESULT(pts -> get_Count(&lCnt));
		TX_ASSERT(0 <= n && n < lCnt);
#endif // _DEBUG

		THROW_FAILED_HRESULT(pts -> GetPoint (n+1, dKoords));
		return Punkt(dKoords[0], dKoords[1]);

	} COM_CATCH_RETURN(Punkt());
}

// Stützpunkt n konvertiert liefern
Point Kante::SP (CONVERTPROC pFcn, long n) const
{
double dKoords[3];

	COM_TRY {
	W_DGMPoints pts;

		THROW_FAILED_HRESULT(m_line -> get_Points(pts.ppi()));

#if defined(_DEBUG)
	long lCnt = 0;

		THROW_FAILED_HRESULT(pts -> get_Count(&lCnt));
		TX_ASSERT(0 <= n && n < lCnt);
#endif // _DEBUG

		THROW_FAILED_HRESULT(pts -> GetPoint (n+1, dKoords));

	} COM_CATCH_RETURN(Point());
	return pFcn (dKoords[0], dKoords[1]);
}

/////////////////////////////////////////////////////////////////////////////
// Masche
Masche &Masche::operator =(const Masche &rhs)
{
	if (&rhs != this) {
		m_area = rhs.m_area;
		m_oc = rhs.m_oc;
	}
	return *this;
}

long Masche::ASP (long **pplCnts)
{
long lCnt = 0;

	COM_TRY {
		if (m_area.IsBoundary()) {
		// Fläche hat Inseln (Löcher)
		W_DGMBoundaryGeometry geom(m_area);
		WDispatch exterior;

			THROW_FAILED_HRESULT(geom -> get_Exterior(exterior.ppi()));
			THROW_FAILED_HRESULT(GetPointCount(exterior, &lCnt));

		W_DGMGeometryCollection coll;
		WEnumVARIANT Enum;

			THROW_FAILED_HRESULT(geom -> get_Holes(coll.ppi()));
			THROW_FAILED_HRESULT(coll -> get_NewEnum (Enum.ppu()));

		// Anzahl der Stützpunkte in jeder Einzelkontur
			if (NULL != pplCnts) {
			long lCntHoles = 0;

				THROW_FAILED_HRESULT(coll -> get_Count(&lCntHoles));
				*pplCnts = (long *)CoTaskMemAlloc((lCntHoles+1)*sizeof(long));
				if (NULL == pplCnts)
					_com_issue_error(E_OUTOFMEMORY);
				(*pplCnts)[0] = lCnt;
			}

		CComVariant var;
		long i = 1;

			for (Enum -> Reset(); S_OK == Enum -> Next(1, CLEARED(&var), NULL); /**/) {
				if (FAILED(var.ChangeType(VT_DISPATCH)))
					continue;

			long lCurr = 0;

				THROW_FAILED_HRESULT(GetPointCount (V_DISPATCH(&var), &lCurr));
				if (NULL != pplCnts)
					(*pplCnts)[i++] = lCurr;
				lCnt += lCurr;
			}

		} else {
		// Fläche besitzt nur eine Außenkontur
			THROW_FAILED_HRESULT(GetPointCount(m_area, &lCnt));

		// Einzelauflistung der KonturStützpunktZahlen liefern
			if (NULL != pplCnts) {
				*pplCnts = (long *)CoTaskMemAlloc(sizeof(long));
				if (NULL == pplCnts)
					_com_issue_error(E_OUTOFMEMORY);
				(*pplCnts)[0] = lCnt;
			}
		}
	} COM_CATCH_RETURN(0);
	return lCnt;
}

/////////////////////////////////////////////////////////////////////////////
// ContainerOperationen

namespace geometry_containers {
	HRESULT maxCont (IDispatch *pIDisp, ObjContainer &rOC)
	{
	KoOrd lXMin = rOC.XMin();
	KoOrd lXMax = rOC.XMax();
	KoOrd lYMin = rOC.YMin();
	KoOrd lYMax = rOC.YMax();

		COM_TRY {
		W_DGMPolygonGeometry geom(pIDisp);
		W_DGMPoints pts;
		double dKoords[3];
		long lCnt = 0;

			THROW_FAILED_HRESULT(geom -> get_Points(pts.ppi()));
	 		THROW_FAILED_HRESULT(pts -> get_Count(&lCnt));
			for (long i = 1; i <= lCnt; i++) {
				THROW_FAILED_HRESULT(pts -> GetPoint (i, dKoords));

			// Container aufbauen
				if (dKoords[0] < lXMin) lXMin = dKoords[0];
				if (dKoords[0] > lXMax) lXMax = dKoords[0];
				if (dKoords[1] < lYMin) lYMin = dKoords[1];
				if (dKoords[1] > lYMax) lYMax = dKoords[1];
			}
		} COM_CATCH;

		rOC = ObjContainer(lXMin, lXMax, lYMin, lYMax);
		return S_OK;
	}

	HRESULT minCont (IDispatch *pIDisp, ObjContainer &rOC)
	{
	KoOrd lXMin = rOC.XMin();
	KoOrd lXMax = rOC.XMax();
	KoOrd lYMin = rOC.YMin();
	KoOrd lYMax = rOC.YMax();

		COM_TRY {
		W_DGMPolygonGeometry geom(pIDisp);
		W_DGMPoints pts;
		double dKoords[3];
		long lCnt = 0;

			THROW_FAILED_HRESULT(geom -> get_Points(pts.ppi()));
			THROW_FAILED_HRESULT(pts -> get_Count(&lCnt));
			for (long i = 1; i <= lCnt; i++) {
				THROW_FAILED_HRESULT(pts -> GetPoint (i, dKoords));

			// Container aufbauen
				if (dKoords[0] > lXMin) lXMin = dKoords[0];
				if (dKoords[0] < lXMax) lXMax = dKoords[0];
				if (dKoords[1] > lYMin) lYMin = dKoords[1];
				if (dKoords[1] < lYMax) lYMax = dKoords[1];
			}
		} COM_CATCH;

		rOC = ObjContainer(lXMin, lXMax, lYMin, lYMax);
		return S_OK;
	}
}

// umschließendes Rechteck
ObjContainer Masche::maxCont (const ObjContainer &rOC)
{
	COM_TRY {
	ObjContainer OC = rOC;

		if (m_area.IsBoundary()) {
		// Fläche mit Löchern
		W_DGMBoundaryGeometry geom(m_area);
		WDispatch exterior;
		long lCnt = 0;

			THROW_FAILED_HRESULT(geom -> get_Exterior(exterior.ppi()));
			THROW_FAILED_HRESULT(GetPointCount(exterior, &lCnt));

		W_DGMGeometryCollection coll;
		WEnumVARIANT Enum;

			THROW_FAILED_HRESULT(geom -> get_Holes(coll.ppi()));
			THROW_FAILED_HRESULT(coll -> get_NewEnum (Enum.ppu()));

		CComVariant var;

			for (Enum -> Reset(); S_OK == Enum -> Next(1, CLEARED(&var), NULL); /**/) {
				if (FAILED(var.ChangeType(VT_DISPATCH)))
					continue;

				THROW_FAILED_HRESULT(geometry_containers::maxCont (V_DISPATCH(&var), OC));
			}
			return OC;
		} else {
		// lediglich Außenkontur
			THROW_FAILED_HRESULT(geometry_containers::maxCont(m_area, OC));
			return OC;
		}
	} COM_CATCH_RETURN(ObjContainer());
}

// kleinster gemeinsamer Rechtecksbereich
ObjContainer Masche::minCont (const ObjContainer &rOC)
{
	COM_TRY {
	ObjContainer OC = rOC;

		if (m_area.IsBoundary()) {
		// Fläche mit Löchern
		W_DGMBoundaryGeometry geom(m_area);
		WDispatch exterior;
		long lCnt = 0;

			THROW_FAILED_HRESULT(geom -> get_Exterior(exterior.ppi()));
			THROW_FAILED_HRESULT(GetPointCount(exterior, &lCnt));

		W_DGMGeometryCollection coll;
		WEnumVARIANT Enum;

			THROW_FAILED_HRESULT(geom -> get_Holes(coll.ppi()));
			THROW_FAILED_HRESULT(coll -> get_NewEnum (Enum.ppu()));

		CComVariant var;

			for (Enum -> Reset(); S_OK == Enum -> Next(1, CLEARED(&var), NULL); /**/) {
				if (FAILED(var.ChangeType(VT_DISPATCH)))
					continue;

				THROW_FAILED_HRESULT(geometry_containers::minCont (V_DISPATCH(&var), OC));
			}
			return OC;
		} else {
		// lediglich Außenkontur
			THROW_FAILED_HRESULT(geometry_containers::minCont(m_area, OC));
			return OC;
		}
	} COM_CATCH_RETURN(ObjContainer());
}

ObjContainer Masche::GetCont (void)
{
	return ObjContainer(m_oc);
}

void Masche::SetCont (KoOrd lCont[])
{
// zuerst die Maximalwerte behandeln (CSRect ist intern Punkt + Ausdehnung)
	if (m_oc.IsValid()) {
		m_oc.put_XMax(lCont[1]);
		m_oc.put_XMin(lCont[0]);
		m_oc.put_YMax(lCont[3]);
		m_oc.put_YMin(lCont[2]);
	}
}

// liefert Kantenanzahl
long Masche::KantenAnz (void) 
{
long lCnt = 0;

	if (m_area.IsBoundary()) {
		COM_TRY {
		W_DGMBoundaryGeometry geom(m_area);
		W_DGMGeometryCollection coll;

			THROW_FAILED_HRESULT(geom -> get_Holes(coll.ppi()));
			THROW_FAILED_HRESULT(coll -> get_Count(&lCnt));
		} COM_CATCH_RETURN(lCnt);
		lCnt++;			// Außenkontur hinzufügen

	} else {
		lCnt = 1;		// nur Außenkontur
	}
	return lCnt;
}

// Kante n liefern
Kante Masche::KA (long n)
{
	COM_TRY {
		if (m_area.IsBoundary()) {
		W_DGMBoundaryGeometry geom(m_area);
		WDispatch disp;

			if (0 == n) {
				THROW_FAILED_HRESULT(geom -> get_Exterior(disp.ppi()));
				return Kante(disp, m_oc);		// Container des gesamten Objektes entspricht dem der Außenkontur
			}

		W_DGMGeometryCollection coll;

			THROW_FAILED_HRESULT(geom -> get_Holes(coll.ppi()));

#if defined(_DEBUG)
		long lCnt = 0;

			THROW_FAILED_HRESULT(coll -> get_Count(&lCnt));
			TX_ASSERT(0 < n && n <= lCnt);		// Holes enthält lediglich Inseln
#endif // _DEBUG

			THROW_FAILED_HRESULT(coll -> Item (CComVariant(n), disp.ppi()));
			return Kante(disp);				
		} else {
			TX_ASSERT(0 == n);
			return Kante (m_area, m_oc);
		}
	} COM_CATCH_RETURN(Kante());
}

// Kante(n) hinzufügen
HRESULT Masche::AddKante (long lLen, KoOrd *pdX, KoOrd *pdY, int iIndex)
{
	COM_TRY {
	// evtl. erst in Boundary konvertieren
		if (!m_area.IsBoundary()) {
		W_DGMPolylineGeometry pline(m_area);
		CCSBoundaryGeometry bound (true);		// make real boundary object
		W_DGMPoints ptssrc, ptsdest;

			THROW_FAILED_HRESULT(pline -> get_Points (ptssrc.ppi()));

		W_DGMBoundaryGeometry geom(bound);
		WDispatch ext;

			THROW_FAILED_HRESULT(geom -> get_Exterior(ext.ppi()));
			THROW_FAILED_HRESULT(W_DGMPolylineGeometry(ext) -> get_Points (ptsdest.ppi()));
		
		long lCnt  = 0;
		double dKoords[3];

			THROW_FAILED_HRESULT(ptssrc -> get_Count(&lCnt));
			for (long i = 1; i <= lCnt; i++) {
				THROW_FAILED_HRESULT(ptssrc -> GetPoint (i, dKoords));
				THROW_FAILED_HRESULT(ptsdest -> SetPoint (i, dKoords));
			}
			m_area = bound;
		} 

	// jetzt Kante hinzufügen
	W_DGMBoundaryGeometry geom(m_area);
	W_DGMGeometryCollection coll;

		THROW_FAILED_HRESULT(geom -> get_Holes(coll.ppi()));

	CCSLineGeometry line (lLen, pdX, pdY);

		if (-1 == iIndex) {
			THROW_FAILED_HRESULT(coll -> Add(line));	// ans Ende
		} else {
			THROW_FAILED_HRESULT(coll -> Add(line, CComVariant(iIndex)));
		}

	// Container neu berechnen
	__Interface<ITRiASSimpleRectangle> cont;

		WTRiASCSGeometryProperties(m_area) -> get_Envelope(cont.ppi());	// Container berechnen
		m_oc.Assign(cont);

	} COM_CATCH;
	return S_OK;
}

// Kreis
void Ellipsen::GetEllipse (KoOrd x[], KoOrd y[], long &rlCnt)
{
	TX_ASSERT(TIsValidAddress(x, rlCnt*sizeof(KoOrd), true));
	TX_ASSERT(TIsValidAddress(y, rlCnt*sizeof(KoOrd), true));

// erster Punkt ist Mittelpunkt, zweiter ist ein beliebiger Punkt 
// auf der Ellipse, dritter ein anderer auf der Ellipse
	x[0] = MP().GetX();
	y[0] = MP().GetY();
	if (rlCnt > 1) {
		x[1] = x[0] + Xa();
		y[1] = y[0];
		if (rlCnt> 2) {
			x[2] = x[0];
			y[2] = y[0] + Xb();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// GeoObjekt und abgeleitete Klassen

// Geometrie in Feldern bereitstellen 
long GeoPunkt::RetrievePureGeometrie (KoOrd **pX, KoOrd **pY, long **pKCnt)
{
	if (NULL == pX || NULL == pY) return 0L;

	COM_TRY {
		ATLTRY(*pX = new KoOrd [1]);
		ATLTRY(*pY = new KoOrd [1]);
		if (NULL == *pX || NULL == *pY) {
			DELETE_OBJ (*pX);
			db_error (EC_NOMEMORY, RC_QueryObjGeometrie);
			_com_issue_error(E_OUTOFMEMORY);
		}

	// Geometrie holen
		(*pX)[0] = GetX();
		(*pY)[0] = GetY();

	} COM_CATCH_RETURN(0L);
	return 1;	// ein Stützpunkt
}

_DGMGeometry *GeoPunkt::GetGeometry (bool fAddRef)
{
	return Punkt::GetGeometry (fAddRef);
}

long GeoKante::RetrievePureGeometrie (KoOrd **pX, KoOrd **pY, long **pKCnt)
{
long lCnt = 0;

	if (NULL == pX || NULL == pY) return 0L;
	COM_TRY {
	
		lCnt = ASP();
		ATLTRY(*pX = new KoOrd [lCnt]);
		ATLTRY(*pY = new KoOrd [lCnt]);
		if (NULL == *pX || NULL == *pY) {
			DELETE_OBJ (*pX);
			db_error (EC_NOMEMORY, RC_QueryObjGeometrie);
			_com_issue_error(E_OUTOFMEMORY);
		}
		GetKante (*pX, *pY, lCnt);		// Geometrie holen

	} COM_CATCH_RETURN(0L);
	return lCnt;
}

_DGMGeometry *GeoKante::GetGeometry (bool fAddRef)
{
	return Kante::GetGeometry (fAddRef);
}

long GeoFlaeche::RetrievePureGeometrie (KoOrd **pX, KoOrd **pY, long **pKCnt)
{
long lCnt = 0;

	if (NULL == pX || NULL == pY) 
		return 0L;

	COM_TRY {
	long j = 0;
	long iKCnt = KantenAnz();

		if (pKCnt) {
			ATLTRY(*pKCnt = new long [iKCnt]);
			if (NULL == *pKCnt) {
				db_error (EC_NOMEMORY, RC_QueryObjGeometrie);
				_com_issue_error(E_OUTOFMEMORY);
			}
		}
		for (long i = 0; i < iKCnt; i++) {
		long lCurr = KA(i).ASP();

			j += lCurr;
			if (pKCnt) 
				(*pKCnt)[i] = lCurr; 
		}

	// Felder anlegen
		lCnt = j;
		ATLTRY(*pX = new KoOrd [lCnt]);
		ATLTRY(*pY = new KoOrd [lCnt]);
		if (NULL == *pX || NULL == *pY) {
			if (pKCnt) DELETE_OBJ (*pKCnt);
			DELETE_OBJ (*pX);
			db_error (EC_NOMEMORY, RC_QueryObjGeometrie);
			_com_issue_error(E_OUTOFMEMORY);
		}

	// Geometrie lesen
		j = 0;
		for (i = 0; i < iKCnt; i++) {
		long actSize = lCnt - j;
			
			KA(i).GetKante (&(*pX)[j], &(*pY)[j], actSize);
			j += actSize;
		}

	} COM_CATCH_RETURN(0L);
	return lCnt;
}

_DGMGeometry *GeoFlaeche::GetGeometry (bool fAddRef)
{
	return Masche::GetGeometry (fAddRef);
}

long GeoKreis::RetrievePureGeometrie (KoOrd **pX, KoOrd **pY, long **pKCnt)
{
long lCnt = 2;

	if (NULL == pX || NULL == pY) return 0L;
	COM_TRY {
		ATLTRY(*pX = new KoOrd [2]);
		ATLTRY(*pY = new KoOrd [2]);
		if (NULL == *pX || NULL == *pY) {
			DELETE_OBJ (*pX);
			db_error (EC_NOMEMORY, RC_QueryObjGeometrie);
			_com_issue_error(E_OUTOFMEMORY);
		}
		GetEllipse (*pX, *pY, lCnt);		// Geometrie holen

	} COM_CATCH_RETURN(0L);
	return lCnt;		// Mittelpunkt und Punkt auf Kreis
}

_DGMGeometry *GeoKreis::GetGeometry (bool fAddRef)
{
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// Objekttyp abfragen
ObjTyp GeoPunkt::isA (void) { return OT_PUNKT; }
ObjTyp GeoKante::isA (void) { return OT_KANTE; }
ObjTyp GeoFlaeche::isA (void) { return OT_FLAECHE; }
ObjTyp GeoKreis::isA (void) { return OT_KREIS; }

GEOMETRYTYPE GeoPunkt::GType() { return GEOMETRYTYPE_Point; }
GEOMETRYTYPE GeoKante::GType() { return GEOMETRYTYPE_Line; }
GEOMETRYTYPE GeoFlaeche::GType() { return m_area.IsBoundary() ? GEOMETRYTYPE_Boundary : GEOMETRYTYPE_Area; }
GEOMETRYTYPE GeoKreis::GType() { return GEOMETRYTYPE_Area; }

/////////////////////////////////////////////////////////////////////////////
// Objektcontainer besorgen
bool GeoPunkt::GetObjContainer (ObjContainer &rOC)
{
	rOC = GetCont();
	return true;
}

bool GeoKante::GetObjContainer (ObjContainer &rOC)
{
	rOC = GetCont();
	return true;
}

bool GeoFlaeche::GetObjContainer (ObjContainer &rOC)
{
	rOC = GetCont();
	return true;
}

bool GeoKreis::GetObjContainer (ObjContainer &rOC)
{
	rOC = GetCont();
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// 

#endif // !defined(_FORCE_LEGACY_CODE)
