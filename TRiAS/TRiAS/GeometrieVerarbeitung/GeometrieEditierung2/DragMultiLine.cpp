// Definitionen: Implementation von DragMultiLine
// File: DragMultiLine.cpp
// W. Mörtl


#include "GeoEditP.h"

#include "DragMultiLine.h"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor
CDragMultiLine::CDragMultiLine (void)
{
    m_pDrawWnd = g_pTE->MVWind();
    m_pStartPt = NULL;
    m_iLineCount = 0;
	m_bScroll = false;
}


// --------------------------------------------------------------------------------------------
// Destruktor
CDragMultiLine::~CDragMultiLine (void)
{
    if (0 == m_iLineCount)	// bei Punktobjekten
    	return;

    if (m_ppDLO)	// nur vorsichtshalber (ist hier vielleicht nicht mehr nötig, da die
    {				// gleiche Aktion in DragTerminate() erfolgt)
    	for (int i = 0; i < m_iLineCount; i++)
    		if (m_ppDLO[i])
    		{
    			delete (m_ppDLO[i]);	// DrawObjecte freigeben
    			m_ppDLO[i] = NULL;
    		}
	 	DELETE_VEC (m_ppDLO);
    }

	DELETE_VEC (m_pStartPt);

} // ~CDragMultiLine



///////////////////////////////////////////////////////////////////////////////////////////////
// Memberfunktionen
// Hinzufügen eines weiteren Startpunktes (wenn er noch nicht in m_pStartPt enthalten ist)
// da in den meisten Fällen Punkte im m_pStartPt-Vektor mehrfach vorkommen würden, werden nur 
// die Punkte berücksichtigt, die echt neu sind (anderenfalls käme es durch das invertierte
// Zeichnen zu einem ungewollten Löschen der Linien)
STDMETHODIMP CDragMultiLine::AddStartPoint (POINT PT)
{
    if (NULL == m_pStartPt)		// m_pStartPt enthält noch keinen Startpunkt
    {
		DELETE_VEC (m_pStartPt);
    	m_pStartPt = new Point[1];
    	if (! m_pStartPt)
    	{
    		DEX_Error (RC_DragMultiLine, EC_NOMEMORY);
    		return E_OUTOFMEMORY;
    	}
    }
    else						// m_pStartPt enthält schon mindestens einen Startpunkt
    {
    	// Testen, ob PT in m_pStartPt schon enthalten ist
    	for (int i = 0; i < m_iLineCount; i++)
    		if (m_pStartPt[i].X() == PT.x && m_pStartPt[i].Y() == PT.y)
    		{
    			_ASSERTE (m_iLineCount > 0);
    			return S_FALSE;		// PT gibt es schon in m_pStartPt
    		}

    Point* pNewStPt = NULL;

    	pNewStPt = new Point[m_iLineCount+1];
    	if (! pNewStPt)
    	{
    		DEX_Error (RC_DragMultiLine, EC_NOMEMORY);
    		return E_OUTOFMEMORY;
    	}

    	for (i = 0; i < m_iLineCount; i++)
    		pNewStPt[i] = m_pStartPt[i];	// bisherigen Stand kopieren

	 	DELETE_VEC (m_pStartPt);
    	m_pStartPt = pNewStPt;
    }

    m_pStartPt[m_iLineCount].X() = PT.x;	// PT hinzunehmen
    m_pStartPt[m_iLineCount].Y() = PT.y;
    m_iLineCount++;

    return S_OK;

} // AddStartPoint


// --------------------------------------------------------------------------------------------
// Erzeugung von mehreren Linien, die bei Mausbewegung an der Mausspitze nachgezogen werden
STDMETHODIMP CDragMultiLine::ConstructDragLines (void)
{
    if (0 == m_iLineCount)
    	return S_FALSE;

    m_ppDLO = new DragLineObject*[m_iLineCount];

    if (! m_ppDLO)
    {
    	DEX_Error (RC_DragMultiLine, EC_NOMEMORY);
    	return E_OUTOFMEMORY;
    }

    for (int i = 0; i < m_iLineCount; i++)
    {
    	m_ppDLO[i] = new DragLineObject (m_pStartPt[i]);	// m_pStartPt[i] ist der
    														//  Anfangspunkte einer Linie
    	if (! m_ppDLO[i])
    	{
    		DEX_Error (RC_DragMultiLine, EC_NOMEMORY);
    		return E_OUTOFMEMORY;
    	}

    	m_ppDLO[i]->ChangeRop (ROP_Invert);		// das von m_ppDLO[i] überzeichnete Gebiet wird
    											//  invertiert
    }

    return S_OK;

} // ConstructDragLines


// --------------------------------------------------------------------------------------------
// zieht bei Mausbewegung mehrere Linien an der Mausspitze nach, nachdem linke Maustaste
// gedrückt und eventl. wieder losgelassen wurde;
// bIsPaint == TRUE bedeutet, daß aktuell der Hintergrund gezeichnet wird
STDMETHODIMP CDragMultiLine::SetEndPoint (POINT PTEnd, BOOL bIsPaint, BOOL bWithDel)
{
    if (0 == m_iLineCount)	// bei Punktobjekt
    	return S_FALSE;

    if (bIsPaint)
    	return S_FALSE;

    _ASSERTE (m_ppDLO != NULL);

    for (int i = 0; i < m_iLineCount; i++)
    {
    	if (NULL == m_ppDLO[i]) continue;
		if (bWithDel)
    		m_pDrawWnd->Draw (m_ppDLO[i]);	// alte Lage durch invertiertes Neuzeichnen löschen
    	m_ppDLO[i]->Process ((Point&)PTEnd);// PTEnd ist der Endpunkt der zu zeichnenden Linie
    										// (Anfangspunkt wurde bei "new" vereinbart)
    	m_pDrawWnd->Draw (m_ppDLO[i]);		// neue Lage zeichnen
    }

    return S_OK;

} // SetEndPoint


// --------------------------------------------------------------------------------------------
// löscht die letzte Lage auf dem Bildschirm OHNE erneut zu zeichnen
// bIsPaint == TRUE bedeutet, daß aktuell der Hintergrund gezeichnet wird
STDMETHODIMP CDragMultiLine::DeleteLastSituation (BOOL bIsPaint)
{
    if (bIsPaint)
    	return S_FALSE;

    _ASSERTE (m_ppDLO != NULL);

    for (int i = 0; i < m_iLineCount; i++)
    {
    	if (NULL == m_ppDLO[i]) continue;
    	m_pDrawWnd->Draw (m_ppDLO[i]);		// alte Lage durch invertiertes Neuzeichnen löschen
    }

    return S_OK;

} // DeleteLastSituation


// --------------------------------------------------------------------------------------------
// die Startpunkte werden in x- bzw. y-Richtung um die Offsets lOffsetX bzw. lOffsetY
// verschoben
STDMETHODIMP CDragMultiLine::ModStartPoints (POINT* pStartPT, int iLineCount)
{
	// die Startpunktkorrektur erfolgt beim Scrollen schon in EditWithScrolling(), ist also
	// hier umsonst; außerdem kann sie an dieser Stelle zu Ungenauigkeiten führen, da die neuen
	// Startpunkte pStartPT mit BSKoordinaten() ermittelt werden, was zum Scrolling-lOffset
	// eine Differenz von 1 ergeben kann (29.06.99)
	if (m_bScroll)
	{
		m_bScroll = false;
		return S_OK;
	}

    if (NULL == m_pStartPt)		// m_pStartPt enthält noch keinen Startpunkt
		return E_UNEXPECTED;

	if (m_iLineCount != iLineCount)
		return E_INVALIDARG;

   	for (int i = 0; i < m_iLineCount; i++)
	{
		m_pStartPt[i] = ((Point*)pStartPT)[i];
    	m_ppDLO[i]->ChangePosition (m_pStartPt[i]);
	}

	return S_OK;

} // ModStartPoints


// --------------------------------------------------------------------------------------------
// rechte Maustaste (und im Fehlerfall auch bei linker Maustaste) losgelassen
STDMETHODIMP CDragMultiLine::DragTerminate (void)
{
    if (0 == m_iLineCount)	// bei Punktobjekt
    	return S_FALSE;

    if (m_ppDLO)
    {
    	for (int i = 0; i < m_iLineCount; i++)
    		if (m_ppDLO[i])
    		{
    			delete (m_ppDLO[i]);		// DrawObjecte freigeben
    			m_ppDLO[i] = NULL;
    		}

	 	DELETE_VEC (m_ppDLO);
    }
    return S_OK;

} // DragTerminate


// --------------------------------------------------------------------------------------------
// Verschieben der zu zeichnenden Linien und des Cursors beim Scrollen
STDMETHODIMP CDragMultiLine::EditWithScrolling (long lOffset, BOOL bHorz)
{
    if (NULL == m_pStartPt)		// m_pStartPt enthält noch keinen Startpunkt
		return S_FALSE;

   	for (int i = 0; i < m_iLineCount; i++)
	{
		if (bHorz)
			m_pStartPt[i].X() += lOffset;
		else
			m_pStartPt[i].Y() -= lOffset;

    	m_ppDLO[i]->ChangePosition (m_pStartPt[i]);
	}

	m_bScroll = true;	// Startpunktkorrektur ausgeführt

POINT PT;	// Cursorposition vor dem Scrollen

	if (GetCursorPos (&PT))
	{
		if (bHorz)
			PT.x += lOffset;
		else
			PT.y += lOffset;
		SetCursorPos (PT.x, PT.y);
		return S_OK;
	}

	return E_FAIL;

} // EditWithScrolling
