// $Header: $
// Copyright© 1999-2003 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 17.01.2003 12:30:26 
//
// @doc
// @module PaintConnectionFilter.h | Declaration of the <c CPaintConnectionFilter> class

#if !defined(_PAINTCONNECTIONFILTER_H__9B8E9409_4D66_408D_99DB_21EEAA10DE4F__INCLUDED_)
#define _PAINTCONNECTIONFILTER_H__9B8E9409_4D66_408D_99DB_21EEAA10DE4F__INCLUDED_

class CPaintConnectionFilter
{
public:
	CPaintConnectionFilter(HDC hDC, HDC hDCTarget);

	HRESULT Paint(CONNECTIONFILTER const *pConnFilter);

protected:
	BOOL CALLBACK EnumConnections(long hPr, BOOL, void *pData);
	void GetDotsPerMM(HDC hDC);

	long GetSizeToPaintX (double dSize);
	long GetSizeToPaintY (double dSize);
	DWORD GetTextFlags(IUnknown *pICS, CRect const &rrc);

private:
	HDC m_hDC;
	HDC m_hDCTarget;

	double m_dXDotsPerMM;
	double m_dYDotsPerMM;
	double m_dScale;
};

#endif // !defined(_PAINTCONNECTIONFILTER_H__9B8E9409_4D66_408D_99DB_21EEAA10DE4F__INCLUDED_)
