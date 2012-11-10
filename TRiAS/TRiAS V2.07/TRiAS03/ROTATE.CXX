/*********************************************************************

 ----  R O T B M P  -------- MS-Windows Application -----------------
                             ### Bitmap Rotation Algorithm ###

======================================================================

### Fast Version ###

----------------------------------------------------------------------

Copyright 1989 by
          Marcellus Buchheit, Buchheit software research
          Zaehringerstrasse 47, D-7500 Karlsruhe 1
          Phone (0) 721/37 67 76    (West Germany)

Release 1.00 of 89-Nov-16 --- All rights reserved.

*********************************************************************/

#include "trias03p.hxx"
#include <containr.hxx>

#include <stdlib.h>		// include all common declarations
#include <stdarg.h>
#include <math.h>

#include <funcs03.h>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NO_ROT_INLINES
#if !defined(NO_ROT_INLINES)
#define ROT_INLINE	inline
#else
#define ROT_INLINE
#endif

// type of bitmap offset
typedef struct tagBMOFFS {
	WORD *pu;		// pointer to current bitmap WORD
	int iW;			// relative index of bit within WORD (0..15)
} BMOFFS;

ROT_INLINE void CalcBitmapSize (POINT *pPts, GRADIENT rGradRot, int &rcxDest, int &rcyDest)
{
int iGrad = 2 * (rGradRot.y < 0) + (rGradRot.x < 0);	// set quadrant value

	switch (iGrad) {
	case 0:
	// 0..90 degree
		rcxDest = pPts[3].x - pPts[0].x;
		rcyDest = pPts[1].y - pPts[2].y;
		break;
	
	case 1:
	// 90..180 degree
		rcxDest = pPts[2].x - pPts[1].x;
		rcyDest = pPts[3].y - pPts[0].y;
		break;
	
	case 2:
	// 270..360 degree
		rcxDest = pPts[1].x - pPts[2].x;
		rcyDest = pPts[0].y - pPts[3].y;
		break;
	
	case 3:
	// 180..270 degree
		rcxDest = pPts[0].x - pPts[3].x;
		rcyDest = pPts[2].y - pPts[1].y;
		break;
	}		/* switch */
	rcxDest++;
	rcyDest++;	// one more because index difference

	TX_ASSERT(rcxDest > 0);
	TX_ASSERT(rcyDest > 0);

// iGrad1 and iGrad2 are now octant values:
// 0:  0..45   2:  90..135   4: 315..360   6: 225..270
// 1: 45..90   3: 135..180   5: 270..315   7: 180..225
}

ROT_INLINE bool CalcSrcCoords (int ix, int iy, int cxSrc, int cySrc, int cxDest2, int cyDest2,
			       GRADIENT &rGradRot, int sGradBase, LONG lRound, int &rix, int &riy)
{
// add absolute round factor, divide by gradient base
LONG l = (LONG)(ix - cxDest2) * rGradRot.x + (LONG)(iy - cyDest2) * rGradRot.y;

	rix = (int) ((l >= 0 ? l + lRound : l - lRound) / sGradBase) + (cxSrc-1)/2;

// Test, ob QuellKoordinaten innerhalb der Quelle liegen
	if (rix < 0 || rix >= cxSrc) return false;

// add absolute round factor, divide by gradient base
	l = (LONG)(iy - cyDest2) * rGradRot.x - (LONG)(ix - cxDest2) * rGradRot.y;
	riy = (int) ((l >= 0 ? l + lRound : l - lRound) / sGradBase) + (cySrc-1)/2;

// Test, ob QuellKoordinaten innerhalb der Quelle liegen
	if (riy < 0 || riy >= cySrc) return false;

return true;
}

// bitmap word selection mask
static WORD s_auMask[] = {
	0x0080, 0x0040, 0x0020, 0x0010, 0x0008, 0x0004, 0x0002, 0x0001,
	0x8000, 0x4000, 0x2000, 0x1000, 0x0800, 0x0400, 0x0200, 0x0100
};

// Feststellen, ob ein Bit gesetzt ist oder nicht -----------------------------
// geht davon aus, daﬂ ein Byte 8Bit hat
ROT_INLINE bool IsWhite (LPSTR pSrc, int iWidthBytes, int ix, int iy)
{
	return pSrc[((iWidthBytes * iy) + ix/8)] & s_auMask[ix%8];
}

// Berechnen der Grˆﬂe eines Rechteckes nach einer Drehung --------------------
bool PASCAL CalcRotatedSize (int xSrc, int ySrc, GRADIENT &rGradRot, int iBase, int &rxDest, int &ryDest)
{
POINT aptSrc[4], aptDest[4];
LONG lRound = iBase / 2;

	aptSrc[0].x = -(xSrc / 2);
	aptSrc[0].y = (ySrc - 1) / 2;
	aptSrc[1].x = (xSrc - 1) / 2;
	aptSrc[1].y = aptSrc[0].y;
	aptSrc[2].x = aptSrc[0].x;
	aptSrc[2].y = -(ySrc / 2);
	aptSrc[3].x = aptSrc[1].x;
	aptSrc[3].y = aptSrc[2].y;

// calculate destination corner points
	for (int i = 0; i < 4; i++) {
	// add absolute round factor, divide by gradient base
	LONG l = (LONG) aptSrc[i].x * rGradRot.x - (LONG) aptSrc[i].y * rGradRot.y;

		aptDest[i].x = (int) ((l >= 0 ? l + lRound : l - lRound) / iBase);

	// add absolute round factor, divide by gradient base
		l = (LONG) aptSrc[i].y * rGradRot.x + (LONG) aptSrc[i].x * rGradRot.y;
		aptDest[i].y = (int) ((l >= 0 ? l + lRound : l - lRound) / iBase);
	}			/* for */

// determine size of destination bitmap (rectangle: cxDest, cyDest)
	CalcBitmapSize (aptDest, rGradRot, rxDest, ryDest);

return true;
}

/*********************************************************************
	R o t a t e B i t m a p
======================================================================

This function creates a new bitmap object and copies the contents of
bitmap <hbmSrc> into this bitmap with a rotation by the gradient
vector <gradRot>. If the destination bitmap is created completely its
handle is returned. Otherwise all allocated data is removed and NULL
is returned.

Parameters
 hbmSrc .... is the handle of the bitmap which is to be rotated.
 gradRot ... contains the gradient vector values.
 sGradBase   is the base of the gradiant values (0..32767).

Return
 If the rotated bitmap is completely created, its handle is returned.
 Otherwise NULL is returned.

Comments
 Following conditions are TRUE (nearly)
  1) sin(rot-angle)=gradRot.y/usGradBase
  2) cos(rot-angle)=gradRot.x/usGradBase

*********************************************************************/

HBITMAP PASCAL RotateBitmap (HDC hTargetDC, HBITMAP hbmSrc, GRADIENT gradRot, 
			     int sGradBase, CoOrd *pX, CoOrd *pY)
{
BITMAP bmSrc;
HDC hdcDest;
HBITMAP hbmDest = NULL;
BITMAP bmDest;
int cxSrc, cySrc, cxDest, cyDest;	// bitmap rectangle size values

DWORD cbSrc, cbDest;			// size of bitmap data

LONG lRound = sGradBase / 2;		// round factor

LPSTR lpbSrcBlk = NULL;			// long pointer to bitmap source data block
LPSTR lpbSrcLine;			// pointer to start of source bitmap line
LPSTR lpbDestBlk = NULL;		// pointer to bitmap destination data block
int ix, iy;

	GetObject (hbmSrc, sizeof(BITMAP), &bmSrc);

// determine source corner points (index difference => round down)
	cxSrc = bmSrc.bmWidth;
	cySrc = bmSrc.bmHeight;
	cbSrc = (LONG) bmSrc.bmWidthBytes * bmSrc.bmHeight;
	if (HIWORD (cbSrc) != 0)
		goto labelRETERR;	// too complex

	CalcRotatedSize (cxSrc, cySrc, gradRot, sGradBase, cxDest, cyDest);

// create destination bitmap
	hbmDest = CreateBitmap (cxDest, cyDest, 1, 1, NULL);
	if (hbmDest == NULL) goto labelRETERR;	// memory too small

	GetObject (hbmDest, sizeof (BITMAP), (LPSTR) & bmDest);
	cbDest = (LONG) bmDest.bmWidthBytes * bmDest.bmHeight;
	if (HIWORD (cbDest) != 0) goto labelRETERR;	// too complex

// create memory object for source and destination bitmap
	lpbSrcBlk = new char[cbSrc];
	if (NULL == lpbSrcBlk) goto labelRETERR;	// memory too small
	lpbDestBlk = new char[cbDest];
	if (NULL == lpbDestBlk) goto labelRETERR;	// memory too small

// get bitmap data
	GetBitmapBits (hbmSrc, cbSrc, lpbSrcBlk);

// create memory display context for destination bitmap
	hdcDest = CreateCompatibleDC (hTargetDC);
	SelectObject (hdcDest, hbmDest);

// set destination bitmap to white color
	{
	WORD *lpuDest = (WORD *)lpbDestBlk;
	WORD cWord = (WORD)cbDest / 2;

		for (int i = 0; i < cWord; i++)
			*lpuDest++ = 0xFFFF;	// 0;
	} /* block */

///////////////////////////////////////////////////////////////////////////////
	lpbSrcLine = lpbDestBlk;

	for (iy = 0; iy < cyDest; iy++) {
	WORD *lpuSrc = (WORD *)lpbSrcLine;	// start of source line
	WORD *pSrcWord = NULL;			// current source word
	int iSrcBit = 15;			// current source bit within word
	int ixd, iyd;				// Koordinaten im QuellBild

		for (ix = 0; ix < cxDest; ix++) {
		// determine if point <bmoffs2> is black in source bitmap
			if (++iSrcBit > 15) {
			// get next source bitmap word
				pSrcWord = lpuSrc++;
				iSrcBit = 0;	// reset counter
			} // if

		// Koordinate ausrechnen
			if (!CalcSrcCoords (ix, iy, cxSrc, cySrc, cxDest/2, cyDest/2, gradRot, sGradBase, lRound, ixd, iyd))
				continue;	// auﬂerhalb des QuellBildes

		// wenn Pixel in Quelle Schwarz ist, dann in Ziel setzen
			if (!IsWhite (lpbSrcBlk, bmSrc.bmWidthBytes, ixd, iyd))
				*pSrcWord &= ~s_auMask[iSrcBit];		// set to black
		}

	// set source pointer to next line
		lpbSrcLine += bmDest.bmWidthBytes;
	}

///////////////////////////////////////////////////////////////////////////////

// set destination bitmap data
	SetBitmapBits (hbmDest, cbDest, lpbDestBlk);

// free allocated memory objects
	DeleteDC (hdcDest);
	goto labelRETURN;
	
labelRETERR:
// memory too small: free allocated objects
	if (hbmDest) {
		DeleteObject (hbmDest);
		hbmDest = NULL;
	}
	
labelRETURN:
	DELETE_OBJ(lpbSrcBlk);
	DELETE_OBJ(lpbDestBlk);

// Maﬂe der neuen Bitmap liefern
	if (NULL != pX) *pX = cxDest;
	if (NULL != pY) *pY = cyDest;

return hbmDest;
}				/* RotateBitmap() */

