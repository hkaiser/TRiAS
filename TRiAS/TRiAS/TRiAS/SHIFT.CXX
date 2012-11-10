// ShiftRectangleObject fuer SchriftObjekte -----------------------------------
// File: SHIFT.CXX

#include "triaspre.hxx"
#include "triasres.h"

#include "shift.hxx"

// Memberfunktionen -----------------------------------------------------------
#pragma warning (disable:4355)

ShiftRectangleObject :: ShiftRectangleObject (Point &Pt, long ONr, Rectangle &R, pWindow pW) 
		      : _P (SolidLine, 1, Color ((ColorVal)128, (ColorVal)128, (ColorVal)128)),
			_B (ClearBrush),
			RectangleObject (Point (R.Left(), R.Bottom()),
				Dimension (R.Right()-R.Left(), R.Top()-R.Bottom()),
				&_P, &_B),
			CDragObject (this)
{
	_Pt = Pt;	// Bezugspunkt merken
	_ONr = ONr;	// ObjektNummer merken
	_R = R;		// altes umschließendes Rechteck
	
	m_fControl = false;
	m_fChanged = false;

#if !defined(WIN16)
	m_pOldPtr = NULL;
	m_pShiftPtr = NULL;
	m_pCopyPtr = NULL;
	m_pW = pW;

	if (NULL != pW) {
//		m_pShiftPtr = new Pointer (ResID (IDC_TEXTSHIFTCURSOR));
		m_pCopyPtr = new Pointer (ResID (IDC_TEXTCOPYCURSOR));

		m_pOldPtr = m_pW -> GetPointer();
		m_fAdjustPointer = true;
	}
#endif // WIN16
}

#pragma warning (default:4355)

void ShiftRectangleObject :: Process (Point newPt) 
{
#if !defined(WIN16)
	AdjustPointer();
#endif // WIN16

	if (newPt.X() != _Pt.X() || newPt.Y() != _Pt.Y()) {
		pt.X() += (newPt.X() - _Pt.X());
		pt.Y() += (newPt.Y() - _Pt.Y());
		_Pt = newPt;
		m_fChanged = true;
	}
}

void ShiftRectangleObject :: ProcessKey (KeyEvt) 
{
#if !defined(WIN16)
	AdjustPointer();
#endif // WIN16
}

bool ShiftRectangleObject :: isDirty (void)
{
	return m_fChanged;
}

bool ShiftRectangleObject :: ToProcessKey (void)
{
bool fMouse = GetAsyncKeyState (VK_LBUTTON) < 0 || GetAsyncKeyState (VK_RBUTTON) < 0;

	if (!fMouse) return false;	// nur, wenn Mouse nicht gedrückt

bool fControl = (GetAsyncKeyState (VK_CONTROL) < 0) ? true : false;

	return fControl != m_fControl;
}

DRAGTYPE ShiftRectangleObject :: isA (void)
{ 
	return DT_SHIFTRECTANGLE; 
}

ShiftRectangleObject :: ~ShiftRectangleObject (void)
{
#if !defined(WIN16)
	ResetPointer();
#endif // WIN16
}

#if !defined(WIN16)
bool ShiftRectangleObject :: AdjustPointer (void)
{
	if (!m_fAdjustPointer || NULL == m_pW) return false;

Pointer *pOld = m_pW -> GetPointer();

	m_fControl = (GetAsyncKeyState (VK_CONTROL) < 0) ? true : false;

	if (!m_fControl) {	// wieder normalen einstellen
		if (pOld != m_pOldPtr) {
			pOld = m_pW -> ChangePointer (m_pOldPtr);
			if (NULL != pOld) pOld -> Hide();
			if (NULL != m_pOldPtr)
				m_pOldPtr -> Show();
		}
	} else {
		if (pOld != m_pCopyPtr && NULL != m_pCopyPtr) {	// CopyCursor (mit [+])
			pOld = m_pW -> ChangePointer (m_pCopyPtr);
			if (NULL != pOld) 
				pOld -> Hide();
			m_pCopyPtr -> Show();
		}
	}

return true;
}

bool ShiftRectangleObject :: ResetPointer (void)
{
	if (NULL == m_pW) return false;

Pointer *pOld = m_pW -> GetPointer();

	if (pOld != m_pOldPtr) {
		pOld = m_pW -> ChangePointer (m_pOldPtr);
		if (NULL != pOld) pOld -> Hide();
		if (NULL != m_pOldPtr) 
			m_pOldPtr -> Show();
	}

//	DELETE(m_pShiftPtr);
	DELETE_OBJ(m_pCopyPtr);	

return true;
}

#endif // WIN16
