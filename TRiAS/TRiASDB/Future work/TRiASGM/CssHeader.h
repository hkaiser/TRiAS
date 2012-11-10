///////////////////////////////////////////////////////////////////////////
// @doc 
// @module CssHeader.h | GM-Koordinatensystem aus Datenbank-Headereinträgen
// erzeugen

#if !defined(_CSSHEADER_H__D553EE42_AF8E_11D1_859C_00600875138A__INCLUDED_)
#define _CSSHEADER_H__D553EE42_AF8E_11D1_859C_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <HeaderEntry.h>

const double PI = 3.141592653589793;

///////////////////////////////////////////////////////////////////////////////
// SMartIF's
DefineSmartInterfaceEx(GMCoordSystem);

///////////////////////////////////////////////////////////////////////////////
// CCSSHeader
class CCSSHeader
{
private:
	HPROJECT m_hPr;
	WGMCoordSystem m_CS;

	CSBaseStorageConstants m_rgType;
	CSGeodeticDatumConstants m_rgDatum;

	CSProjectionAlgorithmConstants m_rgProj;
	double m_dMeridian;
	double m_dFalseX;
	long m_lZone;

	bool m_fIsUserDefined;
	bool m_fIsTransverseMercator;

protected:
	double RetrieveMeridian();
	double RetrieveFalseX(long &rlZone);

public:
	CCSSHeader (HPROJECT hPr, IGMCoordSystem *pCSS);
	~CCSSHeader();

	bool InitCoordTransform();

// Zugriffsfunktionen
	bool IsTransverseMercator() { return m_fIsTransverseMercator; }
	bool IsUserDefined() { return m_fIsUserDefined; }

	CSBaseStorageConstants BaseStorageType() { return m_rgType; }
	CSGeodeticDatumConstants GetGeodDatum() { return m_rgDatum; }
	CSProjectionAlgorithmConstants GetProjection() { return m_rgProj; }

	double GetMeridian() { return (m_dMeridian * PI) / 180.0; }		// rad!
	double GetFalseX() { return m_dFalseX; }
	long GetZone() { return m_lZone; }

// für Projektionen
	double GetMetricDistVal();		// Genauigkeit (Entfernung)
	CComBSTR GetMetricUnitStr();	// Maßeinheit (Entfernung)

// für geodätische css
	double GetAngleDistVal();		// Genauigkeit (Winkel)
	CComBSTR GetAngleUnitStr();		// Maßeinheit (Winkel)
};

#endif // !defined(_CSSHEADER_H__D553EE42_AF8E_11D1_859C_00600875138A__INCLUDED_)
