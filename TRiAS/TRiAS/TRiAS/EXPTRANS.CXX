// Eingabefenster fuer zusaetzliche Koordinatentransformation
// File: EXPTRANS.CXX

#include "triaspre.hxx"

#include "exptrans.h"
#include "exptrans.hxx"

// Konstruktor ----------------------------------------------------------------
#pragma warning (disable:4355)

ExportTransDlg :: ExportTransDlg (pWindow pW, ObjContainer &OC, CoordTrans *pCTF)
		: DialogWindow (pW, TRANSFORMPARAMS),
		  _LX (this, IDE_DBLOBENRECHTS),
		  _LY (this, IDE_DBLOBENHOCH),
		  _RX (this, IDE_DBLUNTENRECHTS),
		  _RY (this, IDE_DBLUNTENHOCH),
		  _pCT (pCTF)
{
	_OX = _OY = 0.0;
	_KX = _KY = 1.0;

	xMin = OC.XMin();
	xMax = OC.XMax();
	yMin = OC.YMin();
	yMax = OC.YMax();

double xTMin, xTMax;
double yTMin, yTMax;

#if defined(_KOORD_ISDOUBLE)
	xTMin = xMin;
	yTMin = yMin;
	xTMax = xMax;
	yTMax = yMax;
#else
	pCT() -> UnScale (xMin, yMin, &xTMin, &yTMin);
	pCT() -> UnScale (xMax, yMax, &xTMax, &yTMax);
#endif // _KOORD_ISDOUBLE

#if !defined(WIN16)
LPVOID pData = NULL;

//	pCT() -> GetTransformParam (xTMin, yTMin, &pData);
	pCT() -> TransformEx (&xTMin, &yTMin, pData);
	pCT() -> TransformEx (&xTMax, &yTMax, pData);
	if (NULL != pData) CoTaskMemFree (pData);
#else
	pCT() -> Transform (&xTMin, &yTMin);
	pCT() -> Transform (&xTMax, &yTMax);
#endif // WIN32

// EditFenster initialisieren
	_LX.SetValue (xTMin);
	_LY.SetValue (yTMax);
	_RX.SetValue (xTMax);
	_RY.SetValue (yTMin);
}

#pragma warning (default:4355)

void ExportTransDlg :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {
	case IDCANCEL:
		EndDlg (0);	// Abbruch
		break;

	case IDOK:
		if (!ExportTransParams())
			break;	// Fehler
		EndDlg (1);	// ok und raus
		break;

	case IDB_EXPTRANSHELP:
		break;
	}
}


// Testen der EIngaebControls und berechnen der Parameter 
Bool ExportTransDlg :: ExportTransParams (void) 
{
double lx, ly, rx, ry;

	if (!_LX.GetValue (lx) || !_LY.GetValue (ly) ||
	    !_RX.GetValue (rx) || !_RY.GetValue (ry))
		return FALSE;	// Eingabe unvollständig

	if ((xMax - xMin == 0.0) || (yMax - yMin == 0.0))
		return FALSE;

// Koordinaten aus Weltkoordinaten zurücktransformieren
#if !defined(WIN16)
LPVOID pData = NULL;

//	pCT() -> GetInvTransformParam (lx, ly, &pData);
	pCT() -> InvTransformEx (&lx, &ly, pData);
	pCT() -> InvTransformEx (&rx, &ry, pData);
	if (NULL != pData) CoTaskMemFree (pData);
#else
	pCT() -> InvTransform (&lx, &ly);
	pCT() -> InvTransform (&rx, &ry);
#endif // WIN16

	_KX = (rx - lx)/(xMax - xMin);
	_KY = (ly - ry)/(yMax - yMin);

// isotrope Skalierung 
	if (fabs (_KX) < fabs (_KY)) {
	Bool sign = (_KX < 0);

		_KX = fabs (_KY);
		if (sign) _KX = -_KX;
	} else {
	Bool sign = (_KY < 0);

		_KY = fabs (_KX);
		if (sign) _KY = -_KY;
	}

	_OX = _KX * xMin - lx;
	_OY = _KY * yMin - ry;

return TRUE;
}

