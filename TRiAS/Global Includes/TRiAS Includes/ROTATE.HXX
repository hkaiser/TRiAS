// Rotieren einer s/w-Bitmap --------------------------------------------------
// File: ROTATE.H

#if !defined(_ROTATE_H)
#define _ROTATE_H

// window function parameter macros
#define P2LO LOWORD(lP2)
#define P2HI HIWORD(lP2)
#define LONGADDR(r) (LONG)(LPSTR)(r)


/* ===================================================================
   GRADIENT                                   angle vector description
   -------------------------------------------------------------------
   A gradient specifies the endpoint of a vector which has its start
   point in the origin (0,0) end its end point in the specified point
   <x,y>.
   
   x  is the x-coordinate of the endpoint of the angle vector
   y  is the y-coordinate of the endpoint of the angle vector
   ===================================================================
*/

typedef struct tagGRADIENT {
	int x;
 	int y;
} GRADIENT;

// bitmap rotation function ---------------------------------------------------
_TRIAS03_ENTRY HBITMAP PASCAL RotateBitmap (HDC hTargetDC, HBITMAP hbmSrc, 
				GRADIENT gradRot, int sGradBase, 
				CoOrd *pX = NULL, CoOrd *pY = NULL);
_TRIAS03_ENTRY bool PASCAL CalcRotatedSize (int xSrc, int ySrc, 
				GRADIENT &rGradRot, int iBase, 
				int &rxDest, int &ryDest);

#endif // _ROTATE_H
