// Zeichnen eines GeoDB-Ausschnittes in einen beliebigen hDC ------------------
// File: RENDERDB.CXX

#include "triaspre.hxx"

#include <xtensnxx.h>

#if defined(WIN32)
#include <dirisole.h>
#include "extmain3.hxx"
#endif

#include "renderdb.hxx"

//extern Window *CurrActW;
extern bool PrintEFlag;

// Funktion, welche einen vorgegebenen GeoDBAusschnitt auf einem beliebigen ---
// hDC ausgibt
BOOL ExtDirisWindow :: RenderGeoDB (RENDERGEODB *pRDB)
{
#if defined(WIN32)
	if (m_pView) 
		return m_pView -> RenderGeoDB (pRDB);

	return false;
#else
	if (pRDB -> m_hDC == 0) return FALSE;	// Fehlerhafte Parameter
	if (pRDB -> m_hTargetDC == 0)
		pRDB -> m_hTargetDC = pRDB -> m_hDC;
		
Dimension dimDots = GetDotsPerMM (pRDB -> m_hTargetDC);
Rectangle rcC = EvalCanvasRect (&pRDB -> m_rclFrame, dimDots);
Rectangle rcClip = EvalCanvasRect (&pRDB -> m_rclClipBox, dimDots);
				
CDirisDCWindow CDCWnd (pRDB, DBO(), rcC, rcClip);	// erstmal nur aktuelle Sicht

	CDCWnd.OldWnd (this);
//	CurrActW = &CDCWnd;
	CDCWnd.Render (CDCWnd.ClipRect());		// eigentliches Zeichnen
//	CurrActW = CDCWnd.OldWnd();

// Fenster neu skalieren (aus Bildschirm zurückschalten)
	DBO().Scale (this, DBO().GetExtend(), AspectRatio);

return TRUE;
#endif // WIN32
}

#if defined(WIN32)
#if 0
void ShiftRect (RECTL &rc)
{
RECTL rcT = rc;

	rc.top = 0;
	rc.left = 0;
	rc.right = rcT.right - rcT.left;
	rc.bottom = -(rcT.top - rcT.bottom);
}
#endif

bool IrisWind :: RenderGeoDB (RENDERGEODB *pRDB)
{
	if (pRDB -> m_hDC == 0) return FALSE;	// Fehlerhafte Parameter
	if (pRDB -> m_hTargetDC == 0)
		pRDB -> m_hTargetDC = pRDB -> m_hDC;

//	ShiftRect (pRDB -> m_rclFrame);

Dimension dimDots = GetDotsPerMM (pRDB -> m_hTargetDC);
Rectangle rcC = EvalCanvasRect (&pRDB -> m_rclFrame, dimDots);
Rectangle rcClip = EvalCanvasRect (&pRDB -> m_rclClipBox, dimDots);
				
CDirisDCWindow CDCWnd (pRDB, DBO(), rcC, rcClip);	// erstmal nur aktuelle Sicht

	CDCWnd.OldWnd (this);
	CDCWnd.Render (CDCWnd.ClipRect());		// eigentliches Zeichnen

// Fenster neu skalieren (aus Bildschirm zurückschalten)
	DBO().Scale (this, DBO().GetExtend(), AspectRatio);
	DBO().EvalMasstab (this);		// Masstabskoeffizienten berechnen

return TRUE;
}
#endif // WIN32

// Routine, welches das Rendering durchführt ----------------------------------
BOOL CDirisDCWindow :: DCExpose (CDCExposeEvt e) 
{
// --> ExposedArea ist der aktuelle Streifen, CanvasRect die PapierGröße
	m_rDBO.Scale (this, m_ocExtend, m_ptAspect, &m_rcActRect);
	m_rDBO.SetEA (m_rcActRect);

Rectangle eRc = e.GetExposedArea();

	DrawEx ((DrawObject *)&m_rDBO, (DWORD)&eRc);
	return TRUE;
}


// Kontruktor/Destruktor des CDCWindow's --------------------------------------
static Rectangle MakeCDCCanvas (Rectangle &rcR);

#pragma warning (disable: 4270)

CDirisDCWindow :: CDirisDCWindow (RENDERGEODB *pRDB, DatenBasisObjekt &rDBO,
				  Rectangle &rcC, Rectangle &rcClip)
		: CDCWindow (pRDB -> m_hDC, MakeCDCCanvas(rcC), pRDB -> m_hTargetDC),
		  m_rDBO (rDBO)
{
HDC hDC = (HDC)Handle(API_WINDOW_TARGETHDC);

// TargetDC-Parameter feststellen
	m_ptAspect = GetAspectRatio (hDC);

// auszugebender DB-Ausschnitt
	m_ocExtend.XMin() = pRDB -> m_rclGeoDB.left;
	m_ocExtend.XMax() = pRDB -> m_rclGeoDB.right;
	m_ocExtend.YMax() = pRDB -> m_rclGeoDB.top;
	m_ocExtend.YMin() = pRDB -> m_rclGeoDB.bottom;
	
// Ausschnitt im ZielKontext
	m_rcActRect = rcC;
	m_rcClipRect = rcClip;
}

#pragma warning (default: 4270)

CDirisDCWindow :: ~CDirisDCWindow (void)
{
	// nothing to do
}

// AspectRatio des hDC holen --------------------------------------------------
Point GetAspectRatio (HDC hDC) 
{
CoOrd LogPixelsX = (CoOrd)GetDeviceCaps (hDC, LOGPIXELSX);
CoOrd LogPixelsY = (CoOrd)GetDeviceCaps (hDC, LOGPIXELSY);

	return Point (LogPixelsX, LogPixelsY);
}

// Berechnen des Ausgaberechtecks aus den gegebenen HIMETRIC- Koordinaten -----
inline CoOrd HiToDots (long lVal, CoOrd dpmm)
{
	return CoOrd ((lVal * long(dpmm))/100L);
}

Rectangle EvalCanvasRect (RECTL *prclR, Dimension dimDotsPerMM)
{
	if (prclR == NULL) return Rectangle (0, 0, 0, 0);
		
Rectangle rcRet (
		HiToDots (prclR -> top, dimDotsPerMM.Height()),
		HiToDots (prclR -> left, dimDotsPerMM.Width()),
		HiToDots (prclR -> bottom, dimDotsPerMM.Height()),
		HiToDots (prclR -> right, dimDotsPerMM.Width())
	);
	
return rcRet;
}

// Das CanvasRechteck des CDCWindows muß von 0 bis zur maximalen Koordinate
// gehen, damit der CommonVu-Blödsinn ausgeglichen werden kann
static Rectangle MakeCDCCanvas (Rectangle &rcR)
{
	return Rectangle (rcR.Top()-rcR.Bottom(), rcR.Left(), 0, rcR.Right());
}


