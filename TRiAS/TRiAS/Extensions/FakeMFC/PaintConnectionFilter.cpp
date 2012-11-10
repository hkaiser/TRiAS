// $Header: $
// Copyright© 1999-2003 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 17.01.2003 12:31:09 
//
// @doc
// @module PaintConnectionFilter.cpp | Definition of the <c CPaintConnectionFilter> class

#include "fakemfcp.hxx"

#include <ospace/utility/autoptr.h>

#include <Com/Thunk.h>
#include <CSRectGeom.h>

#include "PaintConnectionFilter.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(Dispatch);
DefineSmartInterface(TRiASSimplePoints);
DefineSmartInterface2(_DGMPoints, IID__DGMPoints);
DefineSmartInterface2(_DGMPolylineGeometry, IID__DGMPolylineGeometry);

///////////////////////////////////////////////////////////////////////////////
// Größen über Bezugsmaßstab umrechnen
inline 
long CPaintConnectionFilter::GetSizeToPaintX (double dSize)
{
	double dDelta = (dSize > 0) ? 0.5 : -0.5;
	return (long)(((m_dScale > 1.0) ? dSize*m_dXDotsPerMM / m_dScale : 
		dSize*m_dXDotsPerMM) + dDelta); 
}

inline 
long CPaintConnectionFilter::GetSizeToPaintY (double dSize)
{
	double dDelta = (dSize > 0) ? 0.5 : -0.5;
	return (long)(((m_dScale > 1.0) ? dSize*m_dYDotsPerMM / m_dScale : 
		dSize*m_dYDotsPerMM) + dDelta); 
}

///////////////////////////////////////////////////////////////////////////////
// 
CPaintConnectionFilter::CPaintConnectionFilter(HDC hDC, HDC hDCTarget)
:	m_hDC(hDC), m_hDCTarget(hDCTarget), m_dXDotsPerMM(0.0), m_dYDotsPerMM(0.0)
{
	GetDotsPerMM(m_hDC);
	DEX_GetActiveScaling(m_dScale);
}

void CPaintConnectionFilter::GetDotsPerMM(HDC hDC) 
{
HDC hDCloc = NULL;

	if (NULL != hDC) 
		hDCloc = hDC;
	else
		hDCloc = GetDC (GetDesktopWindow());

	switch (GetMapMode (hDCloc)) {
	default:		// MM_ANISOTROPIC/MM_ISOTROPIC
	case MM_TEXT:		// der bisherige Stand
		{
		int HorzSize = GetDeviceCaps (hDCloc, HORZSIZE);       // Breite in mm
		int VertSize = GetDeviceCaps (hDCloc, VERTSIZE);       // Höhe in mm
		int HorzRes = GetDeviceCaps (hDCloc, HORZRES);         // Breite in Dots
		int VertRes = GetDeviceCaps (hDCloc, VERTRES);         // Höhe in Dots

			if (0 != HorzSize && 0 != VertSize) {
				m_dXDotsPerMM = double(HorzRes)/double(HorzSize);
				m_dYDotsPerMM = double(VertRes)/double(VertSize);
			}
			else {
				m_dXDotsPerMM = m_dYDotsPerMM = 100.0;	// default HIMETRIC
			}
		}
		break;

	case MM_HIMETRIC:	// [0.01 mm]
		m_dXDotsPerMM = m_dYDotsPerMM = 100.;
		break;
		
	case MM_LOMETRIC:	// [0.1 mm]
		m_dXDotsPerMM = m_dYDotsPerMM = 10.0;
		break;
		
	case MM_HIENGLISH:	// [0.001 inch]
		m_dXDotsPerMM = m_dYDotsPerMM = 1000.0/2540.0;
		break;
		
	case MM_LOENGLISH:	// [0.01 inch]
		m_dXDotsPerMM = m_dYDotsPerMM = 100.0/2540.0;
		break;
		
	case MM_TWIPS:
		m_dXDotsPerMM = m_dYDotsPerMM = 20.0/0.3176;
		break;
	}

// DC bei Bedarf wieder freigeben
	if (hDC == NULL) 
		ReleaseDC (GetDesktopWindow(), hDCloc);
}

///////////////////////////////////////////////////////////////////////////////
// Einen räumlichen Verbindungsfilter zeichen

namespace {
// Enumerationsstruktur um festzustellen, ob ein bestimmter Filter an einer
// der Connections dranhängt.
	typedef struct tagCONNECTFILTERISATTACHED {
		char const *pcName;
		bool fIsAttached;
	} CONNECTFILTERISATTACHED;
}	// anonymous namspace

BOOL CPaintConnectionFilter::EnumConnections(long hPr, BOOL, void *pData)
{
CONNECTFILTERISATTACHED *pCFA = reinterpret_cast<CONNECTFILTERISATTACHED *>(pData);
char cbDataSourceName[_MAX_PATH];

	if (!DEX_GetDataSourceShortName(reinterpret_cast<HPROJECT>(hPr), cbDataSourceName))
		return TRUE;		// trotzdem weitermachen

GETATTACHEDCONNECTIONFILTER GACF;
char cbBuffer[_MAX_PATH];

	INITSTRUCT(GACF, GETATTACHEDCONNECTIONFILTER);
	GACF.pcConnName = cbDataSourceName;
	GACF.pName = cbBuffer;
	GACF.iLen = sizeof(cbBuffer);
	if (SUCCEEDED(DEX_GetAttachedConnectionFilter(GACF)) && 
		!strcmp(pCFA->pcName, GACF.pName)) 
	{
		pCFA -> fIsAttached = true;
		return FALSE;		// einer reicht
	}
	return TRUE;
}

namespace {

	inline
	HRESULT RCtoDC (IUnknown *pICS, double *pdPair, long *plPair)
	{
	// RC --> OC
	COORDTRANSFORMEX CT;

		INITSTRUCT(CT, COORDTRANSFORMEX);
		CT.m_rcPts = pdPair;
		CT.m_Pts = plPair;
		CT.m_pICS = pICS;
		if (!DEX_RCtoOC(CT))
			return E_FAIL;

	// OC --> DC
	COORDCONVERT CC;
	POINT ptOut;

		CC.lpPkt = plPair;
		CC.lpPt = &ptOut;
		if (!DEX_OCtoDCEx(CC))
			return E_FAIL;

		plPair[0] = ptOut.x;
		plPair[1] = ptOut.y;
		return S_OK;
	}

	class CDetachingDC : public CDC
	{
	public:
		~CDetachingDC() 
		{
			this->Detach();
		}
	};

}	// anonymous namespace

HRESULT CPaintConnectionFilter::Paint(CONNECTIONFILTER const *pConnFilter)
{
// feststellen ob der Filter irgendwo dranhängt
ENUMNOKEYLONG ENK;
CStdThunkImpl<CPaintConnectionFilter, ENUMNOKEYLONGPROC> 
	Thunk(this, &CPaintConnectionFilter::EnumConnections);
CONNECTFILTERISATTACHED CFA;

	CFA.pcName = pConnFilter->pcName;
	CFA.fIsAttached = false;

	ENK.eFcn = Thunk.GetThunk();
	ENK.ePtr = &CFA;
	DEX_EnumDataSourceHandles(ENK);

// Geometrie des Filters besorgen
	if (pConnFilter -> iMode & CF_Polygon_Flag) {
	// ConnFilter ist ein Polygon
    W_DGMPolylineGeometry line(WDispatch(pConnFilter->pIGeometry));
    W_DGMPoints Pts;
	long lCnt = 0;

		RETURN_FAILED_HRESULT(line -> get_Points(Pts.ppi()));
		RETURN_FAILED_HRESULT(Pts -> get_Count(&lCnt));
		
	auto_ptr<double> pCoords (new double[3*lCnt]);

		RETURN_FAILED_HRESULT(WTRiASSimplePoints(Pts) -> GetPoints(1, lCnt, pCoords.get()));

	// in Bildschirmkoordinaten umrechnen lassen
	auto_ptr<POINT> plPoints (new POINT[lCnt]);

		for (long l = 0; l < lCnt; ++l) {
		double *pActCoord = pCoords.get() + (3*l);
		double dPair[2] = { pActCoord[0], pActCoord[1]};
		POINT lPt = { 0, 0 };

			RETURN_FAILED_HRESULT(RCtoDC (pConnFilter->pICS, dPair, 
				(long *)&plPoints.get()[l]));
		}

	// und jetzt zeichnen
	CDetachingDC PaintDC;

		PaintDC.Attach(m_hDC);
		if (NULL != m_hDCTarget)
			PaintDC.SetAttribDC(m_hDCTarget);

	CPen pen;
	CBrush hollow;
	COLORREF refCol = CFA.fIsAttached ? RGB(255, 0, 0) : RGB(0, 0, 255);

		pen.CreatePen(PS_INSIDEFRAME, GetSizeToPaintX(0.5),	refCol);	// .5mm dick
		hollow.CreateStockObject(HOLLOW_BRUSH);

	CPen *pOldPen = PaintDC.SelectObject(&pen);
	CBrush *pOldBrush = PaintDC.SelectObject(&hollow);

		PaintDC.Polygon(plPoints.get(), lCnt);

	// Namen des Filters zeichnen
	long lHeight = GetSizeToPaintY(10*0.3176);

		if (lHeight > 3) {
		// Umschließendes Rechteck besorgen
		long lMin[2] = { LONG_MAX, LONG_MAX };
		long lMax[2] = { -LONG_MAX, -LONG_MAX };

			for (long i = 0; i < lCnt; ++i) {
			POINT &rpt = plPoints.get()[i];

				lMin[0] = min(lMin[0], rpt.x);
				lMin[1] = min(lMin[1], rpt.y);
				lMax[0] = max(lMax[0], rpt.x);
				lMax[1] = max(lMax[1], rpt.y);
			}
						
		CRect rc (lMin[0], lMax[1], lMax[0], lMin[1]);	// ltrb
		DWORD dwFlags = GetTextFlags(pConnFilter->pICS, rc);

			if (DWORD(-1) != dwFlags) {
			// jetzt gehts los
			CFont font;

				font.CreateFont(-lHeight, 0, 0, 0, FW_NORMAL,
					FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
					CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH|FF_SWISS, 
					"Verdana");
			CFont *pOldFont = PaintDC.SelectObject (&font);

				rc.DeflateRect(GetSizeToPaintX(1), -2*lHeight+GetSizeToPaintY(2), 
					GetSizeToPaintX(1), lHeight);
				PaintDC.SetTextColor(refCol);
				PaintDC.SetBkMode(TRANSPARENT);
				PaintDC.DrawText(pConnFilter->pcName, &rc, 
					DT_SINGLELINE|DT_END_ELLIPSIS|dwFlags|DT_NOCLIP);

				PaintDC.SelectObject(pOldFont);
			}
		}

		PaintDC.SelectObject(pOldBrush);
		PaintDC.SelectObject(pOldPen);
	}
	else {
	// ConnFilter ist ein Rechteck
	CCSRectangleGeometry Rect (WDispatch(pConnFilter->pIGeometry));
	double dMin[2] = { 0.0, 0.0 };
	double dMax[2] = { 0.0, 0.0 };

		RETURN_FAILED_HRESULT(Rect -> GetRect(&dMin[0], &dMin[1], &dMax[0], &dMax[1]));

	// in Bildschirmkoordinaten umrechnen lassen
	long lMin[2] = { 0, 0 };
	long lMax[2] = { 0, 0 };

		RETURN_FAILED_HRESULT(RCtoDC (pConnFilter->pICS, dMin, lMin));
		RETURN_FAILED_HRESULT(RCtoDC (pConnFilter->pICS, dMax, lMax));

	// und jetzt zeichnen
	CDetachingDC PaintDC;

		PaintDC.Attach(m_hDC);
		if (NULL != m_hDCTarget)
			PaintDC.SetAttribDC(m_hDCTarget);

	CPen pen;
	CBrush hollow;
	COLORREF refCol = CFA.fIsAttached ? RGB(255, 0, 0) : RGB(0, 0, 255);

		pen.CreatePen(PS_INSIDEFRAME, GetSizeToPaintX(0.5),	refCol);	// .5mm dick
		hollow.CreateStockObject(HOLLOW_BRUSH);

	CPen *pOldPen = PaintDC.SelectObject(&pen);
	CBrush *pOldBrush = PaintDC.SelectObject(&hollow);

		PaintDC.Rectangle(lMin[0], lMin[1], lMax[0], lMax[1]);

	long lHeight = GetSizeToPaintY(10*0.3176);

		if (lHeight > 3) {
		CRect rc (lMin[0], lMax[1], lMax[0], lMin[1]);	// ltrb
		DWORD dwFlags = GetTextFlags(pConnFilter->pICS, rc);

			if (DWORD(-1) != dwFlags) {
			CFont font;

				font.CreateFont(-lHeight, 0, 0, 0, FW_NORMAL,
					FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
					CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH|FF_SWISS, 
					"Verdana");
			CFont *pOldFont = PaintDC.SelectObject (&font);

				rc.DeflateRect(GetSizeToPaintX(1), -2*lHeight+GetSizeToPaintY(2), 
					GetSizeToPaintX(1), lHeight);
				PaintDC.SetTextColor(refCol);
				PaintDC.SetBkMode(TRANSPARENT);
				PaintDC.DrawText(pConnFilter->pcName, &rc, 
					DT_SINGLELINE|DT_END_ELLIPSIS|dwFlags|DT_NOCLIP);

				PaintDC.SelectObject(pOldFont);
			}
		}

		PaintDC.SelectObject(pOldBrush);
		PaintDC.SelectObject(pOldPen);
	}
	return S_OK;
}

DWORD CPaintConnectionFilter::GetTextFlags(IUnknown *pICS, CRect const &rrc)
{
GENERICCONTAINER GC;

	INITSTRUCT(GC, GENERICCONTAINER);
	GC.pICS = pICS;
	DEX_GetWindowAsContainer(GC);	// Fensterecken

// in Bildschirmkoordinaten umrechnen lassen
double dMin[2] = { GC.dXMin, GC.dYMin };
double dMax[2] = { GC.dXMax, GC.dYMax };
long lMin[2] = { 0, 0 };
long lMax[2] = { 0, 0 };

	if (FAILED(RCtoDC (pICS, dMin, lMin)) || FAILED(RCtoDC (pICS, dMax, lMax)))
		return DT_BOTTOM|DT_RIGHT;

CRect rc (lMin[0], lMin[1], lMax[0], lMax[1]);	// ltrb

	if (rc.PtInRect(rrc.BottomRight()))				// ru
		return DT_BOTTOM|DT_RIGHT;
	if (rc.PtInRect(CPoint(rrc.right, rrc.top)))	// ro
		return DT_TOP|DT_RIGHT;
	if (rc.PtInRect(rrc.TopLeft()))					// lo
		return DT_TOP|DT_LEFT;
	if (rc.PtInRect(CPoint(rrc.left, rrc.bottom)))	// lu
		return DT_BOTTOM|DT_LEFT;

	return DWORD(-1);
}
