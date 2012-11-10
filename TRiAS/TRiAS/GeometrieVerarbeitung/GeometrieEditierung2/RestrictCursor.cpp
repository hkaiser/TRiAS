// Definitionen: Nachziehen des vom Mauszeiger abgetrennten Cursors (in Kreuzform)
// File: RestrictCursor.cpp
// W. Mörtl


#include "GeoEditP.h"

#include "RestrictCursor.h"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor
CRestrictCursor::CRestrictCursor (void)
{
	m_pVWnd = g_pTE->MVWind();
	m_pRestrCur = NULL;
	m_MyDim = Dimension (iDPSize, iDPSize);
	m_bFirst = TRUE;
}


// --------------------------------------------------------------------------------------------
// Destruktor
CRestrictCursor::~CRestrictCursor (void)
{
//	UnDraw();
	DELETE_OBJ (m_pRestrCur);
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Memberfunktionen
// Erzeugung eines kreuzförmigen Cursors, der bei Mausbewegung auf einer Hilfslinie nachgezogen
// wird
STDMETHODIMP CRestrictCursor::ConstructRestrictCursor (void)
{
    m_pRestrCur = new DragCrossObject (Point(0,0), m_MyDim);

    if (! m_pRestrCur)
    {
    	DEX_Error (RC_RestrictCursor, EC_NOMEMORY);
    	return E_OUTOFMEMORY;
    }

	// das von m_pRestrCur überzeichnete Gebiet wird invertiert
   	m_pRestrCur->ChangeRop (ROP_Invert);
	return S_OK;

} // ConstructRestrictCursor


// --------------------------------------------------------------------------------------------
// zieht bei Mausbewegung kreuzförmigen Cursor auf einer Hilfslinie nach, nachdem linke
// Maustaste gedrückt und eventl. wieder losgelassen wurde;
// bIsPaint == TRUE bedeutet, daß aktuell der Hintergrund gezeichnet wird
STDMETHODIMP CRestrictCursor::SetPoint (POINT PTCent, BOOL bIsPaint)
{
    if (bIsPaint)
    	return S_FALSE;

	_ASSERTE (m_pRestrCur != NULL);

	// alte Lage durch invertiertes Neuzeichnen löschen, jedoch noch nicht beim 1. Aufruf von
	// SetPoint()
	if (m_bFirst)
		m_bFirst = FALSE;
	else
		m_pVWnd->DrawEx (m_pRestrCur, ROP_Invert);

	m_pRestrCur->ChangePosition ((Point&)PTCent);
	m_pVWnd->DrawEx (m_pRestrCur, ROP_Invert);	// Cursor an der neuen Position
	m_pVWnd->Update();							//  sofort zeichnen
	m_bDraw = true;

    return S_OK;

} // SetPoint


// --------------------------------------------------------------------------------------------
// Liefert das umschreibende Rechteck des Cursors
STDMETHODIMP CRestrictCursor::GetBoundingBox (RECT* pREC)
{
	*pREC = (RECT&)m_pRestrCur->BoundingBox();
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// Löscht den Cursor
STDMETHODIMP CRestrictCursor::UnDraw (void)
{
	if (m_bDraw)	// bisweilen kommen 2 UnDraw() hintereinander
	{
		m_pVWnd->DrawEx (m_pRestrCur, ROP_Invert);	// letzte Darstellung löschen
		m_pVWnd->Update();							//  sofort zeichnen
		m_bFirst = TRUE;
		m_bDraw = false;
	}
	return S_OK;
}
