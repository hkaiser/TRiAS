// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.09.2000 11:29:13 
//
// @doc
// @module GeoObj.h | Declaration of the <c CGObject> class

#if !defined(_GEOOBJ_H__4DCE334A_F45E_49C0_99AE_BF4B8A2CBF23__INCLUDED_)
#define _GEOOBJ_H__4DCE334A_F45E_49C0_99AE_BF4B8A2CBF23__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <SIUnits/stdModel.h>

///////////////////////////////////////////////////////////////////////////////
// 
class CConnectedCtf;

class CGObject 
{
private:
	OBJGEOMETRIE m_ogObj;
	HPROJECT m_hPr;
	bool m_fInitialized;
	bool m_fGeometryTransformed;

protected:
	void FreeObjGeometrie (void);
	static si::Area CGObject::SubContentsArea (CConnectedCtf *pCT, const double *pdX, const double *pdY, long lCnt, void *pCTFData);

public:
	CGObject (LONG lONr);
	CGObject (HPROJECT hPr);
	~CGObject (void);

	bool FInit (bool fStatisticsOnly = false);

	bool CreateNewObject(int iObjTyp, long lCnt, double *pX, double *pY, long iKCnt, long *plCnt);
	BOOL WriteUniqueIdent (LPCSTR pcUIdent);
	BOOL WriteOldUniqueIdent (LPCSTR pcOldUIdent);
	BOOL WriteObjectName(LPCSTR pcObjName);
	BOOL WriteAttribute (INT_PTR lMCode, LPCSTR pcAttribute);

	BOOL ReadUniqueIdent (os_string &rstr);
	BOOL ReadOldUniqueIdent (os_string &rstr);
	BOOL ReadObjectName(os_string &rstr);
	BOOL ReadAttribute (INT_PTR lMCode, os_string &rstr);
	
	long lONr (void) { return m_ogObj.lONr; }
	long lIdent (void) { return m_ogObj.lIdent; }
	short iObjTyp (void) { return m_ogObj.iObjTyp; }
	long lCnt (void) { return m_ogObj.lCnt; }
	const double *X (void) { return reinterpret_cast<const double *>(m_ogObj.pdblX); }
	const double *Y (void) { return reinterpret_cast<const double *>(m_ogObj.pdblY); }
	short iKCnt (void) { return m_ogObj.iKCnt; }
	const long *plCnt (void) { return m_ogObj.plCnt; }
	const char * Text (void) { return ((TEXTGEOMETRIE &)m_ogObj).pText; }

	bool IsValid() { return m_fInitialized; }
	bool IsTransformed() { return m_fGeometryTransformed; }

// Flächen, Längen etc. berechnen
	HRESULT CentroidOfPolygon (double *pdX, double *pdY);
	HRESULT InitRealAreaPoint (double *pdX, double *pdY);
	HRESULT AreaOfPolygon (double *pdArea, os_string &rstrUnit, bool fAsMeter = false);
	HRESULT LengthOfPolyline (double *pdLength, os_string &rstrUnit);

// Koordinaten normalisieren
	HRESULT TransformCoords(bool fWithParam = false);
	HRESULT InvTransformCoords(bool fWithParam = false);

// Container berechnen
	HRESULT GetObjContainer(double &rdXMin, double &rdXMax, double &rdXYMin, double &rdYMax);
};

#endif // !defined(_GEOOBJ_H__4DCE334A_F45E_49C0_99AE_BF4B8A2CBF23__INCLUDED_)
