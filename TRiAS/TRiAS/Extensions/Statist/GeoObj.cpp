// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.09.2000 11:26:38
//
// @doc
// @module GeoObj.cpp | Implementation of the <c CGObject> class

#include "StdAfx.h"

#include <math.h>
#include <float.h>
#include <ErrCodes.hxx>
#include <DblPair.hxx>

#include <igeometr.hxx>
#include <objgguid.h>
#include <trelguid.h>
#include <triastlb.h>

#include <SIUnits/stdModel.h>

#include "Statist.h"
#include "GeoObj.h"
#include "ConnectedCtf.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Quadrat berechnen
inline double Sqr (double x)
{
	return x * x;
}

///////////////////////////////////////////////////////////////////////////////
// sonstige locale inline Funktionen
inline si::Area GetUoA (si::Area &rArea, os_string &rstrUnit) 
{
	return ((CStatist *)g_pTE) -> GetUoA (rArea, rstrUnit);
}

inline si::Length GetUoL (si::Length &rLength, os_string &rstrUnit) 
{
	return ((CStatist *)g_pTE) -> GetUoL (rLength, rstrUnit);
}

inline CConnectedCtf *GetCTF()
{
	return ((CStatist *)g_pTE) -> GetCTF();
}

///////////////////////////////////////////////////////////////////////////////
// Konstruktor/Destruktor
CGObject::CGObject (LONG lONr)
{
	INITSTRUCT (m_ogObj, OBJGEOMETRIE);
	m_ogObj.lONr = lONr;
	if (0 != lONr)
		m_hPr = DEX_GetObjectProject(lONr);
	else
		m_hPr = HACTCONNECTION;
	m_fInitialized = false;
}

CGObject::CGObject (HPROJECT hPr)
{
	INITSTRUCT (m_ogObj, OBJGEOMETRIE);
	m_hPr = hPr;
	m_fInitialized = false;
}

CGObject::~CGObject (void)
{
	FreeObjGeometrie();	// Geometrie freigeben
}

// Objektgeometrie besorgen 
bool CGObject::FInit (bool fStatisticsOnly)
{
	if (m_fInitialized) 
		return true;

// Statistik anfordern
	if (!DEX_GetObjStatistik (m_ogObj))
		return false;

	if (fStatisticsOnly)
		return true;

// Felder anfordern
	m_ogObj.pdblX = new double [m_ogObj.lCnt];
	m_ogObj.pdblY = new double [m_ogObj.lCnt];
	if (m_ogObj.pdblX == NULL || m_ogObj.pdblY == NULL) 
		return false;
		
	if (m_ogObj.iKCnt > 0) {
		if (m_ogObj.iObjTyp == OGFlaeche) {
			m_ogObj.plCnt = new long [m_ogObj.iKCnt];
			if (m_ogObj.plCnt == NULL) 
				return false;
		} else if (m_ogObj.iObjTyp == OGText) {
			((TEXTGEOMETRIE &)m_ogObj).pText = new char [m_ogObj.iKCnt+1];
			if (((TEXTGEOMETRIE &)m_ogObj).pText == NULL) 
				return false;
		}
	}

	m_ogObj.iFlags |= OGConverted;
	if (DEX_GetObjGeometrie (m_ogObj)) {
		m_fInitialized = true;
		m_fGeometryTransformed = true;		// Geometrie sind RealKoordinaten
		return true;
	}
	return false;
}

void CGObject::FreeObjGeometrie (void)
{
	DELETE_OBJ(m_ogObj.pdblX);
	DELETE_OBJ(m_ogObj.pdblY);
	DELETE_OBJ(m_ogObj.plCnt);
}

// Objekt neu erzeugen
bool CGObject::CreateNewObject(int iObjTyp, long lCnt, double *pX, double *pY, long iKCnt, long *plCnt)
{
	m_ogObj.iObjTyp = iObjTyp;
	m_ogObj.lCnt = lCnt;
	m_ogObj.pdblX = pX;
	m_ogObj.pdblY = pY;
	m_ogObj.iKCnt = iKCnt;
	m_ogObj.plCnt = plCnt;
	m_ogObj.iFlags = OGConverted|(0 != m_ogObj.lONr ? OGModObject : OGNewObject);
	return DEX_ModObjGeometrieEx(m_hPr, m_ogObj) ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
// Attribute schreiben
BOOL CGObject::WriteUniqueIdent(LPCSTR pcUIdent)
{
	_ASSERTE(0 != lIdent());
	return WriteAttribute(DEX_GetUniqueIdentMCodeEx(m_hPr), pcUIdent);
}

BOOL CGObject::WriteOldUniqueIdent(LPCSTR pcOldUIdent)
{
	_ASSERTE(0 != lIdent());
	return WriteAttribute(DEX_GetOldUniqueIdentMCodeEx(m_hPr), pcOldUIdent);
}

BOOL CGObject::WriteObjectName(LPCSTR pcObjName)
{
	_ASSERTE(0 != lIdent());
	return WriteAttribute(DEX_GetObjNameMCode(lIdent()), pcObjName);
}

BOOL CGObject::WriteAttribute(INT_PTR lMCode, LPCSTR pcAttribute)
{
	_ASSERTE(0 != lONr());
	_ASSERTE(0 != lMCode && -1 != lMCode);

TARGETMERKMAL TM;

	INITSTRUCT(TM, TARGETMERKMAL);
	TM.lMCode = lMCode;
	TM.iTTyp = TT_Objekt;
	TM.lTarget = lONr();
	TM.pMText = const_cast<char *>(pcAttribute);
	TM.imaxLen = strlen(pcAttribute);
	return (EC_OKAY == DEX_ModTextMerkmal(TM)) ? TRUE : FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Attribute lesen
BOOL CGObject::ReadUniqueIdent(os_string &rstr)
{
	_ASSERTE(0 != lIdent());
	return ReadAttribute(DEX_GetUniqueIdentMCodeEx(m_hPr), rstr);
}

BOOL CGObject::ReadOldUniqueIdent(os_string &rstr)
{
	_ASSERTE(0 != lIdent());
	return ReadAttribute(DEX_GetOldUniqueIdentMCodeEx(m_hPr), rstr);
}

BOOL CGObject::ReadObjectName(os_string &rstr)
{
	_ASSERTE(0 != lIdent());
	return ReadAttribute(DEX_GetObjNameMCode(lIdent()), rstr);
}

BOOL CGObject::ReadAttribute(INT_PTR lMCode, os_string &rstr)
{
	_ASSERTE(0 != lONr());
	_ASSERTE(0 != lMCode && -1 != lMCode);

TARGETMERKMAL TM;
char cbBuffer[4*_MAX_PATH];

	INITSTRUCT(TM, TARGETMERKMAL);
	TM.lMCode = lMCode;
	TM.iTTyp = TT_Objekt;
	TM.lTarget = lONr();
	TM.pMText = cbBuffer;
	TM.imaxLen = sizeof(cbBuffer);
	if (NULL != DEX_GetTextMerkmal(TM)) {
		rstr = cbBuffer;
		return TRUE;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Schwerpunkt berechnen
HRESULT CGObject::CentroidOfPolygon (double *pdCentroidX, double *pdCentroidY)
{
	if (NULL == pdCentroidX || NULL == pdCentroidY)
		return E_POINTER;
	*pdCentroidX = 0.0;
	*pdCentroidY = 0.0;

	if (!IsValid() || OGFlaeche != iObjTyp())
		return E_INVALIDARG;

const double *pdX = X();
const double *pdY = Y();

	for (long i = 1; i < lCnt(); ++i) {
		*pdCentroidX += *(pdX + i-1);
		*pdCentroidY += *(pdY + i-1);
	}

	*pdCentroidX /= double(lCnt() - 1);
	*pdCentroidY /= double(lCnt() - 1);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Flächeninhalt einer einzelnen Kontur berechnen
/*static*/
si::Area CGObject::SubContentsArea (
	CConnectedCtf *pCT, const double *pdX, const double *pdY, long lCnt, void *pCTFData)
{
	if (0 >= lCnt || NULL == pdX || NULL == pdY) {
		_ASSERTE(0 < lCnt && NULL != pdX && NULL != pdY);
		return 0.0;
	}

DoublePair DP1;
DoublePair DP2;
DoublePair DP3;

	pCT -> MetricEx (pdX[lCnt-1], pdY[lCnt-1], &DP1.X(), &DP1.Y(), pCTFData);
	pCT -> MetricEx (pdX[1], pdY[1], &DP2.X(), &DP2.Y(), pCTFData);
	pCT -> MetricEx (pdX[lCnt-2], pdY[lCnt-2], &DP3.X(), &DP3.Y(), pCTFData);

si::Area dArea (DP1.X() * (DP2.Y() - DP3.Y()));

	for (long i = 1; i < lCnt-1; i++) {
		pCT -> MetricEx (pdX[i], pdY[i], &DP1.X(), &DP1.Y(), pCTFData);
		pCT -> MetricEx (pdX[i+1], pdY[i+1], &DP2.X(), &DP2.Y(), pCTFData);
		pCT -> MetricEx (pdX[i-1], pdY[i-1], &DP3.X(), &DP3.Y(), pCTFData);
		dArea += si::Area(DP1.X() * (DP2.Y() - DP3.Y()));
	}

	dArea /= 2.;
	return dArea;
}

///////////////////////////////////////////////////////////////////////////////
// Flächeninhalt
HRESULT CGObject::AreaOfPolygon (double *pdArea, os_string &rstrUnit, bool fAsMeter)
{
	if (NULL == pdArea)
		return E_POINTER;
	*pdArea = 0.0;

	if (!IsValid() || OGFlaeche != iObjTyp())
		return E_INVALIDARG;

// Bestimmen des Flächeinhalts
si::Area dObjArea;
CConnectedCtf *pCT = GetCTF();
LPVOID pData = NULL;
const double *pdX = X();
const double *pdY = Y();

	_ASSERTE(NULL != pCT);

	RETURN_FAILED_HRESULT(InvTransformCoords());	// Koordinaten müssen normalisiert vorliegen
	pCT -> GetMetricParam (pdX[0], pdY[0], &pData);

	if (1 < iKCnt()) {
	// Objekt hat Inseln
	long j = 0;
	const long *plK = plCnt();

		dObjArea = SubContentsArea (pCT, pdX, pdY, plK[0], pData);

		j = plK[0];
		for (long i = 1; i < iKCnt(); ++i) {
			dObjArea -= SubContentsArea (pCT, &pdX[j], &pdY[j], plK[i], pData);
			j += plK[i];
		}
		_ASSERTE(j == lCnt());

	} else
		dObjArea = SubContentsArea (pCT, pdX, pdY, lCnt(), pData);

	pCT -> FreeMetricParam (pData);

	if (fAsMeter) 
		*pdArea = dObjArea.pure();
	else
		*pdArea = dObjArea.measuredIn (GetUoA (dObjArea, rstrUnit));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// LinienLänge
HRESULT CGObject::LengthOfPolyline (double *pdLength, os_string &rstrUnit)
{
	if (NULL == pdLength)
		return E_POINTER;
	*pdLength = 0.0;

	if (!IsValid() || (OGLinie != iObjTyp() && OGFlaeche != iObjTyp()))
		return E_INVALIDARG;

	RETURN_FAILED_HRESULT(InvTransformCoords());	// Koordinaten müssen normalisiert vorliegen

si::Length dLength;
const double *pdX = X();
const double *pdY = Y();
CConnectedCtf *pCT = GetCTF();

	_ASSERTE(NULL != pCT);
	for (long i = 1; i < lCnt(); ++i) {
	DoublePair pt1 (pdX[i], pdY[i]);
	DoublePair pt2 (pdX[i-1], pdY[i-1]);

		dLength += si::Length(pCT -> CoordTransDistance(&pt1, &pt2));
	}
	
	*pdLength = dLength.measuredIn (GetUoL (dLength, rstrUnit));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Punkt der wirklich innerhalb einer Fläche liegt
HRESULT CGObject::InitRealAreaPoint (double *pdX, double *pdY)
{
	if (NULL == pdX || NULL == pdY)
		return E_POINTER;
	*pdX = 0.0;
	*pdY = 0.0;
	
	if (OGFlaeche != iObjTyp())
		return E_INVALIDARG;

	COM_TRY {
	double dX = 0.0;
	double dY = 0.0;
	WTriasXtensionSite Site;
	WExtendTopRel2 Top;

		THROW_FAILED_HRESULT(g_pTE -> GetXtensionSite (Site.ppi()));
		THROW_FAILED_HRESULT(Site -> GetXtension (CLSID_Topologie, IID_IExtendTopRel2, Top.ppv()));
		THROW_FAILED_HRESULT(Top -> GetPointInsideArea_ONr (lONr(), &dX, &dY));

	CConnectedCtf *pCT = GetCTF();
	
		_ASSERTE(NULL != pCT);
		pCT -> UnScale (KoOrd(dX), KoOrd(dY), pdX, pdY);
		pCT -> Transform (pdX, pdY);

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Koordinaten normalisieren
HRESULT CGObject::TransformCoords(bool fWithParam)
{
	if (m_fGeometryTransformed)
		return S_FALSE;		// Koordinaten sind bereits im richtigen Format

CConnectedCtf *pCT = GetCTF();

	_ASSERTE(NULL != pCT);

double *pdX = reinterpret_cast<double *>(m_ogObj.pdblX);
double *pdY = reinterpret_cast<double *>(m_ogObj.pdblY);

	if (fWithParam) {
	void *pData = NULL;

		pCT -> GetTransformParam(pdX[0], pdY[0], &pData);
		for (long i = 0; i < lCnt(); ++i)
			pCT -> TransformEx(&pdX[i], &pdY[i], pData);
		pCT -> FreeTransformParam(pData);
	}
	else {
		for (long i = 0; i < lCnt(); ++i)
			pCT -> Transform(&pdX[i], &pdY[i]);
	}

	m_fGeometryTransformed = true;
	return S_OK;
}

HRESULT CGObject::InvTransformCoords(bool fWithParam)
{
	if (!m_fGeometryTransformed)
		return S_FALSE;		// Koordinaten sind bereits im richtigen Format

CConnectedCtf *pCT = GetCTF();

	_ASSERTE(NULL != pCT);

double *pdX = reinterpret_cast<double *>(m_ogObj.pdblX);
double *pdY = reinterpret_cast<double *>(m_ogObj.pdblY);

	if (fWithParam) {
	void *pData = NULL;

		pCT -> GetInvTransformParam(pdX[0], pdY[0], &pData);
		for (long i = 0; i < lCnt(); ++i)
			pCT -> InvTransformEx(&pdX[i], &pdY[i], pData);
		pCT -> FreeInvTransformParam(pData);
	}
	else {
		for (long i = 0; i < lCnt(); ++i)
			pCT -> InvTransform(&pdX[i], &pdY[i]);
	}

	m_fGeometryTransformed = false;
	return S_OK;
}

HRESULT CGObject::GetObjContainer(double &rdXMin, double &rdXMax, 
	double &rdYMin, double &rdYMax)
{
double *pdX = reinterpret_cast<double *>(m_ogObj.pdblX);
double *pdY = reinterpret_cast<double *>(m_ogObj.pdblY);
double dXMin = DBL_MAX;
double dXMax = -DBL_MAX;
double dYMin = DBL_MAX;
double dYMax = -DBL_MAX;

	for (long i = 0; i < lCnt(); ++i) {
		dXMin = min(dXMin, pdX[i]);
		dYMin = min(dYMin, pdY[i]);
		dXMax = max(dXMax, pdX[i]);
		dYMax = max(dYMax, pdY[i]);
	}

	rdXMin = dXMin;
	rdXMax = dXMax;
	rdYMin = dYMin;
	rdYMax = dYMax;
	return S_OK;
}

