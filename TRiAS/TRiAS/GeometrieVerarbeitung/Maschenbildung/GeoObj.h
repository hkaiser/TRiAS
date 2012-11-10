// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 28.11.2002 12:28:49 
//
// @doc
// @module GeoObj.h | Declaration of the <c CGeoObj> class

#if !defined(_GEOOBJ_H__95354EEE_16CD_4ECC_A687_9C8CBAF1E6F2__INCLUDED_)
#define _GEOOBJ_H__95354EEE_16CD_4ECC_A687_9C8CBAF1E6F2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <boost/shared_ptr.hpp>

///////////////////////////////////////////////////////////////////////////////
// 
class CObjGeometrie : 
	public OBJGEOMETRIE
{
public:
	CObjGeometrie(long lONr_, double dTolerance)
	{
		INITSTRUCT(*this, OBJGEOMETRIE);
		lONr = lONr_;
		m_dKoeff = CalcKoeff(dTolerance);
	}
	CObjGeometrie() 
	{ 
		FreeObjGeometrie(); 
	}

	bool FInit (bool fStatisticsOnly = false);

	long GetONr() const { return lONr; }
	long GetIdent() const { return lIdent; }
	short GetObjTyp() const { return iObjTyp; }
	short GetKCnt() const { return iKCnt; }
	const long *GetplCnt() const { return plCnt; }
	long GetlCnt() const { return lCnt; }
	long GetplCnt(short iIndex)
	{
		_ASSERTE(OGFlaeche == GetObjTyp());
		_ASSERTE(0 <= iIndex && iIndex < GetKCnt());
		return plCnt[iIndex];
	}

	const double *X() const { return reinterpret_cast<const double *>(pdblX); }
	const double *Y() const { return reinterpret_cast<const double *>(pdblY); }
	double &X(long lIndex) 
	{
		_ASSERTE(0 <= lIndex && lIndex < GetlCnt()); 
		return reinterpret_cast<double *>(pdblX)[lIndex];
	}
	double &Y(long lIndex) 
	{
		_ASSERTE(0 <= lIndex && lIndex < GetlCnt()); 
		return reinterpret_cast<double *>(pdblY)[lIndex];
	}

	long GetXHash() const { return m_lXHash; }
	long GetYHash() const { return m_lYHash; }

protected:
	void FreeObjGeometrie()
	{
		DELETE_OBJ(pdblX);
		DELETE_OBJ(pdblY);
		DELETE_OBJ(plCnt);
	}

	bool AdjustLineGeometry();
	bool AdjustAreaGeometry();
	bool AdjustAreaGeometryKontur(int iKontur);
	bool AdjustIslands();
	inline void SwapKoords(long lIndex1, long lIndex2);

	static double CalcKoeff(double dKoeff);

private:
	long m_lXHash;
	long m_lYHash;
	double m_dKoeff;
};

///////////////////////////////////////////////////////////////////////////////
// Wrapperklasse
class CGObject 
{
private:
	boost::shared_ptr<CObjGeometrie> m_ogObj;
	bool m_fInitialized;
	double m_dTolerance;

public:
	CGObject (HOBJECT lONr, double dTolerance = 0.0);
	~CGObject() {}

	bool FInit (bool fStatisticsOnly = false)
	{ return (m_fInitialized = m_ogObj->FInit(fStatisticsOnly)); }

	long lONr() const { return m_ogObj->GetONr(); }
	long lIdent() const { return m_ogObj->GetIdent(); }
	short iObjTyp() const { return m_ogObj->GetObjTyp(); }
	short iKCnt() const { return m_ogObj->GetKCnt(); }
	const long *plCnt() const { return m_ogObj->GetplCnt(); }
	long lCnt() const { return m_ogObj->GetlCnt(); }

	long lCnt(short iIndex)
	{
		_ASSERTE(OGFlaeche == iObjTyp());
		_ASSERTE(0 <= iIndex && iIndex < iKCnt());
		return m_ogObj->GetplCnt(iIndex);
	}
//	const char * Text() const { return ((TEXTGEOMETRIE &)m_ogObj).pText; }

	const double *X() const { return m_ogObj->X(); }
	const double *Y() const { return m_ogObj->Y(); }
	double &X(long lIndex) 
	{
		_ASSERTE(0 <= lIndex && lIndex < lCnt()); 
		return m_ogObj->X(lIndex);
	}
	double &Y(long lIndex) 
	{
		_ASSERTE(0 <= lIndex && lIndex < lCnt()); 
		return m_ogObj->Y(lIndex);
	}
	bool IsValid() const { return m_fInitialized; }
	void SetValid(bool fFlag) { m_fInitialized = fFlag; }

	long GetXHash() const { return m_ogObj->GetXHash(); }
	long GetYHash() const { return m_ogObj->GetYHash(); }

	bool UseTolerance() const { return (0.0 != m_dTolerance) ? true : false; }
	double GetTolerance() const { return m_dTolerance; }
};

bool operator< (CGObject const &lhs, CGObject const &rhs);

#endif // !defined(_GEOOBJ_H__95354EEE_16CD_4ECC_A687_9C8CBAF1E6F2__INCLUDED_)
