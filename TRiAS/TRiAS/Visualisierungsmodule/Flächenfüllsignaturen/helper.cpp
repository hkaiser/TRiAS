// Allgemeine Routinen --------------------------------------------------------
// File: HELPER.CPP

#include "stdafx.h"

#include <limits.h>

// Konvertieren einer Koordinate aus Objekt in Bildschirmkoordinaten ----------
inline bool OCtoDC (long lX, long lY, CPoint *pPt)
{
COORDCONVERT cv;
CPoint pt (lX, lY);

	cv.lpPkt = (long *)&pt;
	cv.lpPt = pPt;

bool fResult = DEX_OCtoDC (cv);

	(pPt -> y)--;
	return fResult;
}

inline bool OCtoDCEx (long lX, long lY, CPoint &rPt)
{
COORDCONVERT cv;
CPoint pt (lX, lY);

	cv.lpPkt = (long *)&pt;
	cv.lpPt = &rPt;

return DEX_OCtoDCEx (cv);
}

// Konvertieren eines Koordinatenfeldes aus Objekt in Bildschirmkoordinaten ---
bool OCtoDC (const long *pX, const long *pY, int iCnt, CPoint *pPts, CRect &rrcBound)
{
	rrcBound = CRect (LONG_MAX, LONG_MAX, 0, 0);		// ltrb
	for (int i = 0; i < iCnt; i++) {
		rrcBound.left = min(rrcBound.left, pX[i]);
		rrcBound.right = max(rrcBound.right, pX[i]);
		rrcBound.top = min(rrcBound.top, pY[i]);
		rrcBound.bottom = max(rrcBound.bottom, pY[i]);

		if (!OCtoDC (pX[i], pY[i], &pPts[i]))
			return false;
	}

// ObjektContainer auch konvertieren (mit kippen)
	OCtoDCEx (rrcBound.left, rrcBound.top, rrcBound.TopLeft());
	OCtoDCEx (rrcBound.right, rrcBound.bottom, rrcBound.BottomRight());

return true;
}

///////////////////////////////////////////////////////////////////////////////
// Anzahl der Pixel/mm in beiden Koordinatenrichtungen für dieses Fenster -----
CSize GetDotsPerMM (HDC hDC) 
{
HDC hDCloc;
CSize dimD (0, 0);

	if (hDC != NULL) hDCloc = hDC;
	else			 hDCloc = ::GetDC(::GetDesktopWindow());

	switch (GetMapMode (hDCloc)) {
	default:		// MM_ANISOTROPIC/MM_ISOTROPIC
	case MM_TEXT:		// der bisherige Stand
		{
		int HorzSize = GetDeviceCaps (hDCloc, HORZSIZE);       // Breite in mm
		int VertSize = GetDeviceCaps (hDCloc, VERTSIZE);       // Höhe in mm
		int HorzRes = GetDeviceCaps (hDCloc, HORZRES);         // Breite in Dots
		int VertRes = GetDeviceCaps (hDCloc, VERTRES);         // Höhe in Dots

			dimD =  CSize(HorzRes/HorzSize, VertRes/VertSize);
		}
		break;

	case MM_HIMETRIC:	// [0.01 mm]
		dimD = CSize(100, 100);
		break;
		
	case MM_LOMETRIC:	// [0.1 mm]
		dimD = CSize(10, 10);
		break;
		
	case MM_HIENGLISH:	// [0.001 inch]
		dimD = CSize(40, 40);
		break;
		
	case MM_LOENGLISH:	// [0.01 inch]
		dimD = CSize(4, 4);
		break;
		
	case MM_TWIPS:
		dimD = CSize(57, 57);
		break;
	}

// DC bei Bedarf wieder freigeben
	if (hDC == NULL) ReleaseDC (GetDesktopWindow(), hDCloc);

return dimD;
}

