// Zeichnen eines GeoDB-Ausschnittes in einen beliebigen hDC ------------------
// File: RENDERDB.CXX

#include "triaspre.hxx"

#include <xtensnxx.h>

#include <dirisole.h>
#include <prntpars.hxx>

#include "extmain3.hxx"
#include "renderdb.hxx"
#include "DBOContext.h"

extern bool PrintEFlag;

// Funktion, welche einen vorgegebenen GeoDBAusschnitt auf einem beliebigen ---
// hDC ausgibt
BOOL ExtDirisWindow::RenderGeoDB (RENDERGEODB *pRDB)
{
#if !defined(WIN16)
	if (m_pView) 
		return m_pView -> RenderGeoDB (pRDB);

	return false;
#else
	if (pRDB -> m_hDC == 0) return FALSE;	// Fehlerhafte Parameter
	if (pRDB -> m_hTargetDC == 0)
		pRDB -> m_hTargetDC = pRDB -> m_hDC;

DoublePair dimD;
Dimension dimDots (GetDotsPerMM (pRDB -> m_hTargetDC), &dimD);
Rectangle rcC (EvalCanvasRect (&pRDB -> m_rclFrame, dimD));
Rectangle rcClip (EvalCanvasRect (&pRDB -> m_rclClipBox, dimD));
				
CDirisDCWindow CDCWnd (pRDB, DBO(), MakeCDCCanvas(rcC), rcClip);	// erstmal nur aktuelle Sicht

	CDCWnd.OldWnd (this);
//	CurrActW = &CDCWnd;
	CDCWnd.Render (CDCWnd.ClipRect());		// eigentliches Zeichnen
//	CurrActW = CDCWnd.OldWnd();

// Fenster neu skalieren (aus Bildschirm zurückschalten)
	DBO().SetExtend (this, DBO().GetExtend(), AspectRatio);

return TRUE;
#endif // WIN16
}

#if !defined(WIN16)
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

bool IrisWind::RenderGeoDB (RENDERGEODB *pRDB)
{
	if (NULL == pRDB -> m_hDC) 
		return FALSE;	// Fehlerhafter Parameter
	if (NULL == pRDB -> m_hTargetDC)
		pRDB -> m_hTargetDC = pRDB -> m_hDC;

	if (pRDB->dwSize == sizeof(RENDERGEODB2) && 
		((RENDERGEODB2 *)pRDB) -> m_iFlags & RDB_CoordsScaled)
	{
	KoOrd dXMin, dXMax, dYMin, dYMax;

		if (!DBO().UnScaleCTF (pRDB->m_rclGeoDB.left, pRDB->m_rclGeoDB.bottom, &dXMin, &dYMin) ||
			!DBO().UnScaleCTF (pRDB->m_rclGeoDB.right, pRDB->m_rclGeoDB.top, &dXMax, &dYMax))
		{
			return false;
		}

		pRDB->m_rclGeoDB.left = ToCoOrd(dXMin);
		pRDB->m_rclGeoDB.right = ToCoOrd(dXMax);
		pRDB->m_rclGeoDB.bottom = ToCoOrd(dYMin);
		pRDB->m_rclGeoDB.top = ToCoOrd(dYMax);
	}

DoublePair dimD;
Dimension dimDots (GetDotsPerMM (pRDB -> m_hTargetDC, &dimD));
Rectangle rcC (EvalCanvasRect (&pRDB -> m_rclFrame, dimD));
Rectangle rcClip (EvalCanvasRect (&pRDB -> m_rclClipBox, dimD));

CDBOContext Ctx (this, DBO(), AspectRatio);			// Bildschirm-Einstellung verwalten
CDirisDCWindow CDCWnd (pRDB, DBO(), MakeCDCCanvas(rcC), rcClip);	// erstmal nur aktuelle Sicht

//	CDCWnd.OldWnd (this);
	CDCWnd.Render (CDCWnd.ClipRect());		// eigentliches Zeichnen
	return true;
}
#endif // WIN16

// Routine, welches das Rendering durchführt ----------------------------------
BOOL CDirisDCWindow::DCExpose (CDCExposeEvt e) 
{
// --> ExposedArea ist der aktuelle Streifen, CanvasRect die PapierGröße
	m_rDBO.SetExtend (this, m_Extend, m_Aspect, &m_ActRect);
	m_rDBO.SetEA (m_ActRect);

Rectangle eRc (e.GetExposedArea());

	DrawEx ((DrawObject *)&m_rDBO, (DWORD)&eRc);
	return TRUE;
}

// Kontruktor/Destruktor des CDCWindow's --------------------------------------

#pragma warning (disable: 4270)

CDirisDCWindow::CDirisDCWindow (RENDERGEODB *pRDB, DatenBasisObjekt &rDBO, Rectangle &rcC, Rectangle &rcClip)
	: CDCWindow (pRDB -> m_hDC, rcC, pRDB -> m_hTargetDC), m_rDBO(rDBO)
{
HDC hDC = (HDC)Handle(API_WINDOW_TARGETHDC);

// TargetDC-Parameter feststellen
	m_Aspect = GetAspectRatio (hDC);

// auszugebender DB-Ausschnitt
	m_Extend.SetXMin(pRDB -> m_rclGeoDB.left);
	m_Extend.SetXMax(pRDB -> m_rclGeoDB.right);
	m_Extend.SetYMax(pRDB -> m_rclGeoDB.top);
	m_Extend.SetYMin(pRDB -> m_rclGeoDB.bottom);
	
// Ausschnitt im ZielKontext
	m_ActRect = rcC;
	m_ClipRect = rcClip;
}

#pragma warning (default: 4270)

CDirisDCWindow::~CDirisDCWindow (void)
{
}

// AspectRatio des hDC holen --------------------------------------------------
Point GetAspectRatio (HDC hDC) 
{
CoOrd LogPixelsX = (CoOrd)GetDeviceCaps (hDC, LOGPIXELSX);
CoOrd LogPixelsY = (CoOrd)GetDeviceCaps (hDC, LOGPIXELSY);

	return Point (LogPixelsX, LogPixelsY);
}

// Berechnen des Ausgaberechtecks aus den gegebenen HIMETRIC- Koordinaten -----
inline CoOrd HiToDots (long lVal, double dpmm)
{
	return ToCoOrd((double(lVal) * dpmm)/100.0);
}

Rectangle EvalCanvasRect (RECTL *prclR, DoublePair dimDotsPerMM)
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

///////////////////////////////////////////////////////////////////////////////
// Druckvorschau et.al.
int IrisWind::PrintPreview (PRINTPREVIEW *pPP)
{
RENDERGEODB *pRDB = pPP -> pRenderDb;

	if (NULL == pRDB -> m_hDC) 
		return FALSE;	// Fehlerhafter Parameter
	if (NULL == pRDB -> m_hTargetDC)
		pRDB -> m_hTargetDC = pRDB -> m_hDC;

// Druckerkontext besorgen (sollte identisch mit dem Bezugsdrucker der Vorschau sein)
PrinterPars PP;		// nur für alle Fälle

	if (NULL == m_pPD) {
	// DefaultPrinter einstellen, wenn dieser nicht verfügbar ist, dann wird 
	// das im DruckDialog ausgewertet (sollte)
		TX_TRY(m_pPD = new PrinterPars);				// erstmal nur anlegen
		if (NULL != m_pPD) 
			m_pPD -> InitFromDefaultPrinter();
	}

// diverse Koordinatenumrechnungen
DoublePair dimD;
Dimension dimDots (GetDotsPerMM (pRDB -> m_hTargetDC, &dimD));		// muß hier über DruckerDC rückgerechnet werden !
Rectangle rcC (EvalCanvasRect (&pRDB -> m_rclFrame, dimD));
Rectangle rcClip (EvalCanvasRect (&pRDB -> m_rclClipBox, dimD));

// DC steht genau auf dem Kopf (eigentlich steht er ja richtig herum, aber CommonVu dreht alles
// auf den Kopf)
HDC hDC = pRDB -> m_hDC;
SIZE szVExt;
POINT ptVOrg;

	GetViewportExtEx (hDC, &szVExt);
	GetViewportOrgEx (hDC, &ptVOrg);

// Viewport rumdrehen
int iSavedDC = SaveDC (hDC);

	SetViewportExtEx (hDC, szVExt.cx, -szVExt.cy, NULL);
	SetViewportOrgEx (hDC, ptVOrg.x, ptVOrg.y + rcC.Height(), NULL);

Rectangle rcCanvas = (Rectangle &)pPP -> pLayout -> m_rcSpiegel;

	LPtoDP (hDC, (POINT *)&rcCanvas, 2);

CDBOContext Ctx (this, DBO(), AspectRatio, false);					// Bildschirm-Einstellung verwalten
CPrintPreview PPWnd(pPP, DBO(), rcCanvas, rcClip, m_pPD ? *m_pPD : PP);	// erstmal nur aktuelle Sicht

	PPWnd.Render (/*PPWnd.ClipRect()*/Rectangle());		// eigentliches Zeichnen (gesamten Bereich zeichnen)
	RestoreDC (hDC, iSavedDC);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Beenden der Druckvorschau (freigeben der Daten)
int IrisWind::EndPrintPreview (PRINTPREVIEW *pPP)
{
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// hier passierts (code ist größtenteils von IrisPrinter::PrinterExpose kopiert)
BOOL CPrintPreview::DCExpose (CDCExposeEvt e)
{
	CDirisDCWindow::SetActRect(CPrintBase::GetActRect());
	CDirisDCWindow::SetAspect(CPrintBase::GetAspect());
	CDirisDCWindow::SetExtend(CPrintBase::GetExtend());

	return CPrintBase::Expose(this, e.GetExposedArea(), m_rPP);
}
