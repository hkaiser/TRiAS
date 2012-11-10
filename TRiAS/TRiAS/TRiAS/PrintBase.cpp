// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.07.2000 22:07:02
//
// @doc
// @module PrintBase.cpp | Implementation of the <c CPrintBase> class

#include "triaspre.hxx"

#include "triasres.h"

#include <funcs03.h>
#include <rect.hxx>
#include <printer.hxx>

#include "strings.h"

#include "extmain3.hxx"
#include "prntabrt.hxx"
#include "prlayout.hxx"
#include "legdinfo.hxx"
#include "legende.hxx"
#include "prntlayt.hxx"

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern bool LegendToRepaint;
extern bool GenerateLegendOnly;

///////////////////////////////////////////////////////////////////////////////
// Initialisierung
CPrintBase::CPrintBase(PrintLayout *pPL, DatenBasisObjekt &rDBO) 
	: m_rDBO (rDBO), m_Idents (rDBO.Idents()), m_Ratio(10000, 10000)
{
// Formatierungsdaten
	m_fLogo = false;
	m_fLegendOnly = pPL -> m_fLegendOnly;

// LegendeObjekt noch nicht vorhanden
	m_pLO = NULL;

	SetActRect (*(pPL -> m_plRcSpiegel));		// SeitenLayout merken
	SetExtend (*(pPL -> m_plOCSpiegel));
	if ((m_lsLegende = pPL -> m_pllsLegende) != LSNoLegend) 
		m_RcLegende = *(pPL -> m_plRcLegende);
	if ((m_msMasstab = pPL -> m_plmsMasstab) != MSNoMasstab)
		m_RcMasstab = *(pPL -> m_plRcMasstab);
	if ((m_fsFrame = pPL -> m_plfsRahmen) != FSNoFrame)
		m_RcFrame = *(pPL -> m_plFullRect);
	if ((m_iHeadLine = pPL -> m_pliHeadLine) != 0) {
		if ((m_lpHeadLine = pPL -> m_pllpHeadLine) != NULL) 
			pPL -> m_pllpHeadLine = NULL;
		m_RcHeadLine = *(pPL -> m_plRcHeadLine);
	} else
		m_lpHeadLine = NULL;


	m_rcPageSize = *(pPL -> m_plrcPageSize);
	m_rcPageBase = *(pPL -> m_plrcPageBase);
	if (NULL != pPL -> m_plRcLogo) {
		m_rcLogo = *(pPL -> m_plRcLogo);
		m_fLogo = true;
	}

// Abmessungen der Logos am unteren Legendenrand
	for (int i = 0; i < MAX_LOGOFELD; i++) {
		if (NULL != pPL -> m_plRcFirmLogo[i]) {
			m_rcFirmLogos[i] = *(pPL -> m_plRcFirmLogo[i]);
			m_fLogos[i] = true;
		} else
			m_fLogos[i] = false;
	}

long M = m_lMasstab = pPL -> m_lMasstab;

// Maßstab ordentlicher machen (runden)
	if      (M >= 10000000L) M = ((M + 500000L) / 1000000L) * 1000000L;
	else if (M >=  1000000L) M = ((M +  50000L) /  100000L) *  100000L;
	else if (M >=   100000L) M = ((M +   5000L) /   10000L) *   10000L;
	else if (M >=    10000L) M = ((M +    500L) /    1000L) *    1000L;
	else if (M >=     1000L) M = ((M +     50L) /     100L) *     100L;
	else if (M >=      100L) M = ((M +      5L) /      10L) *      10L;

	if (m_lMasstab != M) {
		m_lMasstab = M;
		m_fRounded = true;
	} else
		m_fRounded = false;
}

CPrintBase::CPrintBase(PRINTLAYOUT *pPL, DatenBasisObjekt &rDBO, POINT &ptRatio) 
	: m_rDBO (rDBO), m_Idents (rDBO.Idents()), m_Ratio(ptRatio.x, ptRatio.y)
{
	m_fLegendOnly = pPL -> m_fLegendOnly;
	m_pLO = NULL;							// LegendeObjekt noch nicht vorhanden

	SetActRect ((Rectangle &)(pPL -> m_rcSpiegel));		// SeitenLayout merken
	SetExtend (ObjContainer(pPL -> m_dXMin, pPL -> m_dXMax, pPL -> m_dYMin, pPL -> m_dYMax));

// LegendenStyle
	m_lsLegende = (LegendStyle)pPL -> m_rgLegendStyle;
	if (LSNoLegend != m_lsLegende) {
		_ASSERTE(pPL -> m_fLegende);
		m_RcLegende = (Rectangle &)(pPL -> m_rcLegende);
	}

// MaßstabsStyle
	m_msMasstab = (MasstabStyle)pPL -> m_rgMasstab;
	if (MSNoMasstab != m_msMasstab) {
		_ASSERTE(pPL -> m_fMasstab);
		m_RcMasstab = (Rectangle &)(pPL -> m_rcMasstab);
	}

// RahmenStyle
	m_fsFrame = (FrameStyle)pPL -> m_rgRahmen;
	if (FSNoFrame != m_fsFrame) {
		_ASSERTE(pPL -> m_fFullRect);
		m_RcFrame = (Rectangle &)(pPL -> m_rcFullRect);
	}

// Überschrift
	m_iHeadLine = pPL -> m_fHasHeadline;
	if (m_iHeadLine && NULL != pPL -> m_pHeadline) {
		m_lpHeadLine = new char [strlen(pPL -> m_pHeadline)+1];
		strcpy (m_lpHeadLine, pPL -> m_pHeadline);

		_ASSERTE(pPL -> m_fHeadline);
		m_RcHeadLine = (Rectangle &)(pPL -> m_rcHeadline);
	} else
		m_lpHeadLine = NULL;

// sonstige Rechtecke
	m_rcPageSize = (Rectangle &)(pPL -> m_rcPageSize);
	m_rcPageBase = (Rectangle &)(pPL -> m_rcPageBase);
	if (pPL -> m_fLogo) {
		m_rcLogo = (Rectangle &)(pPL -> m_rcLogo);
		m_fLogo = true;
	} else
		m_fLogo = false;

// Abmessungen der Logos am unteren Legendenrand
	for (int i = 0; i < MAX_LOGOFELD; i++) {
		if (pPL -> m_fFirmLogo & (1 << i)) {
			m_rcFirmLogos[i] = (Rectangle &)(pPL -> m_rcFirmLogo[i]);
			m_fLogos[i] = true;
		} else
			m_fLogos[i] = false;
	}

long M = m_lMasstab = pPL -> m_lMasstab;

// Maßstab ordentlicher machen (runden)
	if      (M >= 10000000L) M = ((M + 500000L) / 1000000L) * 1000000L;
	else if (M >=  1000000L) M = ((M +  50000L) /  100000L) *  100000L;
	else if (M >=   100000L) M = ((M +   5000L) /   10000L) *   10000L;
	else if (M >=    10000L) M = ((M +    500L) /    1000L) *    1000L;
	else if (M >=     1000L) M = ((M +     50L) /     100L) *     100L;
	else if (M >=      100L) M = ((M +      5L) /      10L) *      10L;

	if (m_lMasstab != M) {
		m_lMasstab = M;
		m_fRounded = true;
	} else
		m_fRounded = false;
}

CPrintBase::~CPrintBase()
{
	if (m_pLO && m_pLO -> m_pR) {	// Legende-Rechteck wieder freigeben
		delete m_pLO -> m_pR;
		m_pLO -> m_pR = NULL;
	}
	DELETE_OBJ (m_pLO);
	DELETE_OBJ (m_lpHeadLine);
}

///////////////////////////////////////////////////////////////////////////////
// Das eigentliche Drucken/Druckvorschauen 
BOOL CPrintBase::Expose (Window *pW, Rectangle rcEA, PrinterPars &rPP)
{
// --> ActRect ist die Papiergröße, ExposedArea der aktuelle Streifen
Rectangle rcActRect (GetActRect()); 

	m_rDBO.SetExtend (pW, GetExtend(), GetAspect(), &rcActRect);
	m_rDBO.SetEA (rcActRect);		// für Legende gesamtes Papier
	
// generieren der Legende
HDC hDC = Handle (API_WINDOW_HDC);
HDC hTargetDC = Handle (API_WINDOW_TARGETHDC);

	if (m_lsLegende != LSNoLegend && m_pLO == NULL) {
	// nur beim ersten mal Legende generieren, aber vollständig
		LegendToRepaint = true;
		GenerateLegendOnly = true;	// PseudoZeichnen nur für Legende
		DrawEx ((DrawObject *)&m_rDBO, 0);
		LegendToRepaint = false;
		GenerateLegendOnly = false;

	Rectangle *pLRc = new Rectangle (m_RcLegende.Top(), m_RcLegende.Left(),
					 m_RcLegende.Bottom(), m_RcLegende.Right());
	
	// Legend speichern, damit aktueller Zustand gedruckt wird
		DEX_SaveLegend();
		m_pLO = CLegendeObjekt::CreateInstance (pW, m_rDBO, pLRc, &rPP);
		if (m_pLO) {
			m_pLO -> SetBaseValues (m_rcPageBase, hTargetDC);	// Blattgröße mitteilen
			m_pLO -> FitLegendSize (pLRc, hDC, hTargetDC);
		}
	}

// ClipGrenzen festlegen
Rectangle rcT1 (rcEA);

	if (rcT1.Left() == rcT1.Right() || rcT1.Top() == rcT1.Bottom())
		m_rDBO.SetEA (rcActRect);		// kein Banding
	else {
	Rectangle rcT2 = rcActRect & rcT1;

		m_rDBO.SetEA (rcT2);
	}

// Drucken der Grafik
	GenerateLegendOnly = false;
	if (!m_fLegendOnly) 
		DrawEx ((DrawObject *)&m_rDBO, 0);

// Legende ausgeben
	if (NULL != m_pLO) 
		DrawEx (m_pLO, NULL);	
	else
		m_lsLegende = LSNoLegend; // Fehler: keine Legende ausgeben

CLegSizeCache Cache;

	if (Cache.FInit(rPP)) {
	long lWidthB = MulDiv(m_rcPageBase.Width(), 100L, m_DotsPerMM.Width());
	long lHeightB = MulDiv(m_rcPageBase.Height(), 100L, m_DotsPerMM.Height());

		Cache.SetBaseValues (lWidthB, lHeightB);
	}

// Überschrift drucken
	if (m_lpHeadLine != NULL) 
		PaintHeadLine (m_RcHeadLine, m_lpHeadLine);

	if (m_fLogo) {
	string str;

		if (Cache.LogoText(str))
			PaintHeadLine (m_rcLogo, str.c_str());
	}

// Augeben der Texte der Logofelder am unteren Rand der Legende
	for (int i = 0; i < MAX_LOGOFELD; i++) {
		if (!m_fLogos[i]) 
			break;		// bis Logo nicht mehr gegeben ist
		PaintFirmLogo (Cache, m_rcFirmLogos[i], i+1);
	}

// Maßstab ausgeben
	if (m_msMasstab != MSNoMasstab) 
		PaintMasstab (Cache);

// Druckbereich markieren
	PaintEdges (m_rcPageSize);
	if (!Cache.NoTRiASLogo())			// nur nicht, wenn explizit nicht erwünscht
		PaintTRiASLogo (m_RcFrame);		// TRiAS® am unteren Rand

// Impressum ausgeben
Rectangle rcCanvas (m_RcFrame);

	if (m_lsLegende != LSNoLegend)
		rcCanvas.Right() -= m_RcLegende.Width();
	if (m_iHeadLine) 
		rcCanvas.Top() -= m_RcHeadLine.Height();
	m_rDBO.DrawImpressum (hDC, hTargetDC, rcCanvas);

// Rahmen etc. zeichnen
	if (m_fsFrame != FSNoFrame) {
	int iWidth = 40;		// 0.4 mm

		PaintRahmen (m_RcFrame, iWidth);
		if (m_iHeadLine) 
			PaintRahmen (m_RcHeadLine, iWidth);
		if (m_lsLegende != LSNoLegend) {
			if (m_msMasstab != MSNoMasstab)
				m_RcLegende.Bottom() -= (m_RcMasstab.Top() - m_RcMasstab.Bottom());
			PaintRahmen (m_RcLegende, iWidth);
		}
		for (int i = 0; i < MAX_LOGOFELD; i++) {
			if (m_fLogos[i]) 
				PaintRahmen (m_rcFirmLogos[i], iWidth);
		}
//		if (m_msMasstab != MSNoMasstab ||
//		    m_lsLegende != LSNoLegend) PaintRahmen (m_RcMasstab, iWidth);
	}
	return false;		// nur eine Seite drucken
}

///////////////////////////////////////////////////////////////////////////////
// Drucken eines kleinen TRiAS-Logos rechts unten außerhalb des Rahmens 
void CPrintBase::PaintTRiASLogo (Rectangle &rRC)
{
HDC hDC = Handle (API_WINDOW_HDC);					// PrinterHDC
HDC hTargetDC = Handle (API_WINDOW_TARGETHDC);		// TargetDC
CoOrd iPtHeight = MulDiv(m_DotsPerMM.Y(), 3176L, 10000L);	// 1pt
CoOrd iHeight = rRC.Height()/300;

// Höhe mit 6Pt bzw. 10 Pt begrenzen
	if (iHeight < 6*iPtHeight) 
		iHeight = 6*iPtHeight;
	else if (iHeight > 10*iPtHeight) 
		iHeight = 10*iPtHeight;

// ggf. auf Bildschirm umrechnen
//	iHeight = MulDiv(iHeight, m_Ratio.Height(), 10000);
	
Dimension dimFont (0, -iHeight);
ResString rsArial (IDS_ARIAL, 20);
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
CVFont locFont (Swiss, dimFont, rsArial);
#else
Font locFont (Swiss, dimFont, rsArial);
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
pFont pF = ChangeFont (&locFont);
CoOrd iTop = rRC.Bottom() - iHeight/6; 
Rectangle rcHL (iTop, rRC.Left(), iTop, rRC.Right());

// Text ausrichten, Textgröße bestimmen, Text ausgeben
	Justify (hDC, hTargetDC, g_cbTRiAS, NULL, (RECT *)&rcHL, ATRight, false);
	Justify (hDC, hTargetDC, g_cbTRiAS, NULL, (RECT *)&rcHL, ATRight, true);

	ChangeFont (pF);
}

///////////////////////////////////////////////////////////////////////////////
// Drucken der Überschrift 
void CPrintBase::PaintHeadLine (Rectangle &rRC, LPCSTR pText) 
{
HDC hDC = Handle (API_WINDOW_HDC);					// PrinterHDC
HDC hTargetDC = Handle (API_WINDOW_TARGETHDC);		// TargetDC

// Formatieren der Kopfzeile, Iteration beginnend ab max. FontGröße
CoOrd iDelta = MulDiv(m_DotsPerMM.Y(), 3176L, 10000L);	// in Schritten zu 1 Pt
CoOrd iExtLeading = MulDiv(rRC.Height(), 3000, 20000);
CoOrd dX = rRC.Width() / 20;
ResString rsArial (IDS_ARIAL, 20);
RECT rcHL;
Dimension dimFont (0, -(iExtLeading * 8 + iDelta));

	{
	CoOrd iTop = rRC.Top() - iExtLeading;
	CoOrd iWidth = rRC.Width() - 2*dX;
	CoOrd iHeight = rRC.Height() - 2*iExtLeading;

		do {	// mindestens ein mal
			dimFont.Height() += iDelta;	// immer kleiner werden

#if !defined(_TRIAS_OLDIMPLEMENTATION2)
		CVFont locFont (Swiss, dimFont, rsArial);
#else
		Font locFont (Swiss, dimFont, rsArial);
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)

			locFont.SetBold();	// Fett

		pFont pF = ChangeFont (&locFont);

			SetRect (&rcHL, rRC.Left()+dX, iTop, rRC.Right()-dX, iTop);

		// Text ausrichten, Textgröße bestimmen
		CoOrd iLine = Justify (hDC, hTargetDC, pText, NULL, &rcHL, ATLeft, false);

			ChangeFont (pF);
			if (-1 == iLine) return;		// kein Text da

		} while (dimFont.Height() < 0 && 
			 ((rcHL.top - rcHL.bottom > iHeight) || (rcHL.right - rcHL.left > iWidth)));

		if (dimFont.Height() >= 0) return;	// Text zu lang, nicht darstellbar
	}

// Text ausgeben
	{
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
	CVFont locFont (Swiss, dimFont, rsArial);
#else
	Font locFont (Swiss, dimFont, rsArial);
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)

		locFont.SetBold();	// natürlich fett

	pFont pF = ChangeFont (&locFont);
	short iLineCnt = 1;
	CoOrd iH = rcHL.top-rcHL.bottom;

		SetRect (&rcHL, rRC.Left()+dX, rRC.Bottom() + iExtLeading + iH, 
				rRC.Right()-dX, rRC.Bottom() + iExtLeading);
		Justify (hDC, hTargetDC, pText, NULL, &rcHL, ATLeft, false, &iLineCnt);
		Justify (hDC, hTargetDC, pText, NULL, &rcHL, iLineCnt <= 1 ? ATCentre : ATLeft, true);

		ChangeFont (pF);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Maßstabszahl ausgeben
#if _MSC_VER < 1300
#pragma optimize("", off)
#endif // _MSC_VER < 1300

void CPrintBase::PaintMasstab (CLegSizeCache &rCache)
{
HDC hDC = Handle (API_WINDOW_HDC);			// PrinterHDC
HDC hTargetDC = Handle (API_WINDOW_TARGETHDC);		// TargetDC
bool fOpaque = rCache.MasstabOpaque();

	if (fOpaque) 
		FillRahmen (m_RcMasstab);		// evtl. weiß füllen

// Text ausgeben
char cbBuffer[_MAX_PATH];
ResString resMasstab (IDS_PRINTLAYOUTMASSTAB, 20);

	wsprintf (cbBuffer, "%s %s1:%ld", resMasstab.Addr(), m_fRounded ? "ca. " : "", m_lMasstab);

long lTop = rCache.MasstabVorHoehe (2*m_DotsPerMM.Height());
long lBottom = rCache.MasstabNachHoehe (2*m_DotsPerMM.Height());
long lLeft = rCache.KastenVorBreite (2*m_DotsPerMM.Width());
long lRight = rCache.KastenNachBreite (2*m_DotsPerMM.Width());

// Font holen
ResString rsArial (IDS_ARIAL, 20);
bool fBold = false;
bool fItalic = false;
bool fUnderline = false;
string strFontName (rsArial.Addr());
int iFamily = Swiss;
int iSizeY = MulDiv(m_DotsPerMM.Y(), 12 * 3176L, 10000L);	// 12 pt

	rCache.MasstabFont (iFamily, strFontName, iSizeY, fBold, fItalic, fUnderline);
//	iSizeY = MulDiv(iSizeY, m_Ratio.Height(), 10000);		// ggf. in BildschirmKoords umrechnen
	
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
CVFont MFont ((StdFamily)iFamily, Dimension(0, -iSizeY), strFontName.c_str());
#else
Font MFont ((StdFamily)iFamily, Dimension(0, -iSizeY), strFontName.c_str());
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
	
	if (fBold) MFont.SetBold();
	if (fItalic) MFont.SetItalic();
	if (fUnderline) MFont.SetUnderline();

pFont pF = ChangeFont (&MFont);
int iBkMode = SetBkMode (hDC, fOpaque ? OPAQUE : TRANSPARENT);

Point pt (CoOrd(m_RcMasstab.Left() + lLeft), CoOrd(m_RcMasstab.Top() - lTop)); 
CoOrd lWidth = (CoOrd)(m_RcMasstab.Right()-m_RcMasstab.Left()-lLeft-lRight);
Rectangle rcSize (pt, Dimension (lWidth, 0));
string strDesc;		// Stand vom ... (BeschreibungsInfo im MaßstabsFeld)

	if (rCache.MasstabDesc (strDesc)) {
		Justify (hDC, hTargetDC, strDesc.c_str(), NULL, (RECT *)&rcSize, ATRight, true);
		rcSize.Bottom() = rcSize.Top();	// nächste Zeile
	} 

CoOrd iLine = Justify (hDC, hTargetDC, cbBuffer, NULL, (RECT *)&rcSize, ATLeft, true);

// Meander konfigurieren
long lWidthM = MulDiv(lWidth, 6400, 10000);		// erste Näherung
//long M = (long)(((lWidthM/m_DotsPerMM.Width())*m_lMasstab)/1000);
long M = MulDiv(lWidthM, m_lMasstab, m_DotsPerMM.Width()*1000);		// entsprechende Länge in [m]
int iZ = 0;	// Anzahl der Nachnullen

// auf zwei Vorkommastellen runden
	if      (M >= 10000000L) { M = ((M + 500000L) / 1000000L); iZ = 6; }
	else if (M >=  1000000L) { M = ((M +  50000L) /  100000L); iZ = 5; }
	else if (M >=   100000L) { M = ((M +   5000L) /   10000L); iZ = 4; }
	else if (M >=    10000L) { M = ((M +    500L) /    1000L); iZ = 3; }
	else if (M >=     1000L) { M = ((M +     50L) /     100L); iZ = 2; }
	else if (M >=      100L) { M = ((M +      5L) /      10L); iZ = 1; }

int iTyp = 0;
long lMax = 1;

	if (M > 13 && M <= 27)	{ iTyp = 1; lMax = 2; }
	if (M > 27 && M <= 53)	{ iTyp = 2; lMax = 4; }
	if (M > 53) 			{ iTyp = 3; lMax = 8; }
	for (int i = 0; i <= iZ; i++)
		lMax *= 10;

	lWidthM = MulDiv(1000*m_DotsPerMM.Width(), lMax, m_lMasstab);

// Bereich berechnen, in dem Meander dargestellt werden soll
CoOrd iTop = CoOrd(rcSize.Bottom() - rCache.MasstabZwischenHoehe (2*(long)m_DotsPerMM.Height()));
Point ptM (rcSize.Left(), iTop);
CoOrd dY = CoOrd(iTop - (m_RcMasstab.Bottom() + lBottom) - iLine);

	PaintMeander (hDC, iTyp, ptM, CoOrd(lWidthM), CoOrd(dY), CoOrd(rCache.MeanderDicke(35)), lMax, iZ, iLine);
	ChangeFont (pF);
	SetBkMode (hDC, iBkMode);
}

#if _MSC_VER < 1300
#pragma optimize("", on)
#endif // _MSC_VER < 1300

///////////////////////////////////////////////////////////////////////////////
// Meander zeichnen, Bezugspunkt ist links oben 
#define NUMMEANDERS		4
#define MEANDERSTEPS	7

static int s_ibMeander[NUMMEANDERS][MEANDERSTEPS] = 
{
	{ 0,  2,   5,  10,  25,  50, 100, },
	{ 0,  5,  10,  25,  50, 100, 200, },
	{ 0, 12,  25,  50, 100, 200, 400, },
	{ 0, 25,  50, 100, 200, 400, 800, },
};

void CPrintBase::PaintMeander (
	HDC hDC, int iTyp, Point pt, int dX, int dY, int iWidth, long lMax, int iZ, int iLine)
{
	TX_ASSERT(0 <= iTyp && NUMMEANDERS > iTyp);

long lScale = s_ibMeander[iTyp][MEANDERSTEPS-1];
CoOrd iDots = (CoOrd)((m_DotsPerMM.X()+m_DotsPerMM.Y())/2);	// mittlere Dots/mm
HPEN hOldPen = (HPEN)::SelectObject (hDC, ::CreatePen (PS_SOLID, MulDiv(iWidth, iDots, 100), RGB(0, 0, 0)));
UINT uiAlign = ::SetTextAlign (hDC, TA_TOP|TA_CENTER);
bool fUp = true;	// am Anfang geht's hoch
char cbBuffer[64];

	::MoveToEx (hDC, pt.X(), pt.Y()-dY, NULL);
	::TextOut (hDC, pt.X(), pt.Y()-(dY+iLine/3), "0", 1);

	for (int i = 0; i < MEANDERSTEPS-1; i++) {
	long lY = pt.Y() - (fUp ? 0 : dY);

		::LineTo (hDC, CoOrd(pt.X() + MulDiv(s_ibMeander[iTyp][i], dX, lScale)), CoOrd(lY));
		::LineTo (hDC, CoOrd(pt.X() + MulDiv(s_ibMeander[iTyp][i+1], dX, lScale)), CoOrd(lY));
		if ((MEANDERSTEPS - 2) == i) {
			if (1 == lMax)			// Spezialfall 1
				strcpy (cbBuffer, "0.5 m");
			else if (1000 == lMax)	// Spezialfall 2
				strcpy (cbBuffer, "500 m");
			else					// normale Behandlung
				wsprintf (cbBuffer, "%ld %sm", iZ < 2 ? lMax/2 : lMax/2000, iZ < 2 ? "" : "k");
			::TextOut (hDC, CoOrd(pt.X() + (s_ibMeander[iTyp][i]*long(dX))/lScale), 
					CoOrd(pt.Y()-(dY+iLine/3)), 
				   cbBuffer, strlen(cbBuffer));
		}
		fUp = !fUp;
	}
	::LineTo (hDC, pt.X() + dX, pt.Y());

	wsprintf (cbBuffer, "%ld %sm", iZ < 2 ? lMax : lMax/1000, iZ < 2 ? "" : "k");
	::TextOut (hDC, pt.X() + dX, pt.Y()-(dY+iLine/3), cbBuffer, strlen(cbBuffer));

	::SetTextAlign (hDC, uiAlign);
	::DeleteObject (SelectObject (hDC, hOldPen));
}

///////////////////////////////////////////////////////////////////////////////
// Drucken eines Rechteckes 
void CPrintBase::PaintRahmen (Rectangle &rRC, int iWidth) 
{
HDC hDC = Handle (API_WINDOW_HDC);			// PrinterHDC
CoOrd iDots = (CoOrd)((m_DotsPerMM.X()+m_DotsPerMM.Y())/2);	// mittlere Dots/mm
HPEN hOldPen = (HPEN)SelectObject (hDC, 
			CreatePen (PS_SOLID, MulDiv(iWidth, iDots, 100), RGB(0, 0, 0)));
HBRUSH hOldBr = (HBRUSH)SelectObject (hDC, GetStockObject (HOLLOW_BRUSH));

	DrawRectangle (hDC, rRC.Left(), rRC.Top(), rRC.Right(), rRC.Bottom());
	DeleteObject (SelectObject (hDC, hOldPen));
	SelectObject (hDC, hOldBr);
}

///////////////////////////////////////////////////////////////////////////////
// Füllen eines Rechteckes 
void CPrintBase::FillRahmen (Rectangle &rRC) 
{
HDC hDC = Handle (API_WINDOW_HDC);			// PrinterHDC
HPEN hOldPen = (HPEN)SelectObject (hDC, CreatePen (PS_NULL, 0, RGB(0, 0, 0)));
HBRUSH hOldBr = (HBRUSH)SelectObject (hDC, GetStockObject (WHITE_BRUSH));

	DrawRectangle (hDC, rRC.Left(), rRC.Top(), rRC.Right(), rRC.Bottom());
	DeleteObject (SelectObject (hDC, hOldPen));
	SelectObject (hDC, hOldBr);
}

///////////////////////////////////////////////////////////////////////////////
// Ecken des bedruckbaren Bereiches ausgeben 
void CPrintBase::PaintEdges (Rectangle &rRC) 
{
HDC hDC = Handle (API_WINDOW_HDC);			// PrinterHDC
COLORREF crBlack = RGB (0, 0, 0);

	SetPixel (hDC, rRC.Left(), rRC.Top(), crBlack);
	SetPixel (hDC, rRC.Right(), rRC.Top(), crBlack);
	SetPixel (hDC, rRC.Left(), rRC.Bottom(), crBlack);
	SetPixel (hDC, rRC.Right(), rRC.Bottom(), crBlack);
}

///////////////////////////////////////////////////////////////////////////////
// Ausgabe eines FirmenLogoBereiches 
void CPrintBase::PaintFirmLogo (CLegSizeCache &rCache, Rectangle &rRc, int iCnt)
{
Rectangle rc;
bool fOpaque = rCache.LogoFeldOpaque (iCnt);

	if (fOpaque) FillRahmen (rRc);		// evtl. weiß füllen
		
	if (CalcLinksObenRect (rCache, rRc, iCnt, &rc))
		PaintFirmLogoFeld (rCache, rc, LL_SUB_ITEM_LinksOben, iCnt, fOpaque);

	if (CalcRechtsObenRect (rCache, rRc, iCnt, &rc))
		PaintFirmLogoFeld (rCache, rc, LL_SUB_ITEM_RechtsOben, iCnt, fOpaque);

	if (CalcLinksUntenRect (rCache, rRc, iCnt, &rc))
		PaintFirmLogoFeld (rCache, rc, LL_SUB_ITEM_LinksUnten, iCnt, fOpaque);

	if (CalcRechtsUntenRect (rCache, rRc, iCnt, &rc))
		PaintFirmLogoFeld (rCache, rc, LL_SUB_ITEM_RechtsUnten, iCnt, fOpaque);
}

///////////////////////////////////////////////////////////////////////////////
// Berechnen der verschiedenen FirmenLogoBereiche 
BOOL CPrintBase::CalcLinksObenRect (
	CLegSizeCache &rCache, Rectangle &rRc, int iCnt, Rectangle *prc)
{
	TX_ASSERT (NULL != prc);

long lHeight = rCache.LogoFeldHoehe (0, LL_SUB_ITEM_LinksOben, iCnt);
long lWidth = rCache.LogoFeldBreite (0, LL_SUB_ITEM_LinksOben, iCnt);
	
	if (lHeight <= 0 || lWidth <= 0) 
		return false;		// nicht gegeben

long lTop = rCache.LogoVorHoehe (2*m_DotsPerMM.Height());
long lLeft = rCache.LogoVorBreite (2*m_DotsPerMM.Width());

	prc -> Top() = CoOrd(rRc.Top() - lTop);
	prc -> Left() = CoOrd(rRc.Left() + lLeft);
	prc -> Bottom() = CoOrd(prc -> Top() - lHeight);
	prc -> Right() = CoOrd(prc -> Left() + lWidth);
	return true;
}

BOOL CPrintBase::CalcRechtsObenRect (
	CLegSizeCache &rCache, Rectangle &rRc, int iCnt, Rectangle *prc)
{
	TX_ASSERT (NULL != prc);

long lHeight = rCache.LogoFeldHoehe (0, LL_SUB_ITEM_RechtsOben, iCnt);
long lWidth = rCache.LogoFeldBreite (0, LL_SUB_ITEM_RechtsOben, iCnt);
	
	if (lHeight <= 0 || lWidth <= 0) 
		return false;		// nicht gegeben

long lTop = rCache.LogoVorHoehe (2*m_DotsPerMM.Height());
long lRight = rCache.LogoNachBreite (2*m_DotsPerMM.Width());

	prc -> Top() = CoOrd(rRc.Top() - lTop);
	prc -> Bottom() = CoOrd(prc -> Top() - lHeight);
	prc -> Right() = CoOrd(rRc.Right() - lRight);
	prc -> Left() = CoOrd(prc -> Right() - lWidth);
	return true;
}

BOOL CPrintBase::CalcLinksUntenRect (
	CLegSizeCache &rCache, Rectangle &rRc, int iCnt, Rectangle *prc)
{
	TX_ASSERT (NULL != prc);

long lHeight = rCache.LogoFeldHoehe (0, LL_SUB_ITEM_LinksUnten, iCnt);
long lWidth = rCache.LogoFeldBreite (0, LL_SUB_ITEM_LinksUnten, iCnt);
	
	if (lHeight <= 0 || lWidth <= 0) 
		return false;		// nicht gegeben

long lBottom = rCache.LogoNachHoehe (2*m_DotsPerMM.Height());
long lLeft = rCache.LogoVorBreite (2*m_DotsPerMM.Width());

	prc -> Bottom() = CoOrd(rRc.Bottom() + lBottom);
	prc -> Top() = CoOrd(prc -> Bottom() + lHeight);
	prc -> Left() = CoOrd(rRc.Left() + lLeft);
	prc -> Right() = CoOrd(prc -> Left() + lWidth);
	return true;
}

BOOL CPrintBase::CalcRechtsUntenRect (
	CLegSizeCache &rCache, Rectangle &rRc, int iCnt, Rectangle *prc)
{
	TX_ASSERT (NULL != prc);

long lHeight = rCache.LogoFeldHoehe (0, LL_SUB_ITEM_RechtsUnten, iCnt);
long lWidth = rCache.LogoFeldBreite (0, LL_SUB_ITEM_RechtsUnten, iCnt);
	
	if (lHeight <= 0 || lWidth <= 0) 
		return false;		// nicht gegeben

long lBottom = rCache.LogoNachHoehe (2*m_DotsPerMM.Height());
long lRight = rCache.LogoNachBreite (2*m_DotsPerMM.Width());

	prc -> Bottom() = CoOrd(rRc.Bottom() + lBottom);
	prc -> Top() = CoOrd(prc -> Bottom() + lHeight);
	prc -> Right() = CoOrd(rRc.Right() - lRight);
	prc -> Left() = CoOrd(prc -> Right() - lWidth);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Ausgabe eines Bereiches eines FirmenLogos 
BOOL CPrintBase::PaintFirmLogoFeld (
	CLegSizeCache &rCache, Rectangle &rRc, int rgPos, int iCnt, BOOL fOpaque)
{
// Font holen
bool fBold = false;
bool fItalic = false;
bool fUnderline = false;
string strFontName = ResString(IDS_ARIAL, 20).Addr();
int iFamily = Swiss;
int iSizeY = MulDiv(m_DotsPerMM.Y(), 12 * 3176L, 10000L);	// 12pt

	if (!rCache.LogoFeldFont (iFamily, strFontName, iSizeY, 	
		     fBold, fItalic, fUnderline, LEGLAYOUT_SUB_ITEM(rgPos), iCnt))
	{
		return false;		// kein Font gegeben
	}

string strText;

	if (!rCache.LogoFeldDesc (strText, LEGLAYOUT_SUB_ITEM(rgPos), iCnt))
		return false;		// kein Text gegeben

	return PaintTextRect (strText.c_str(), rgPos, rRc, iFamily, strFontName.c_str(), 
		      iSizeY, fBold, fItalic, fUnderline, fOpaque);
}

///////////////////////////////////////////////////////////////////////////////
// einen Text in einem vorgegebenen Rechteck einpassen und ausgeben
BOOL CPrintBase::PaintTextRect (
	LPCSTR pcText, int rgPos, Rectangle &rRc, int iFamily, LPCSTR pcFont, int iSizeY, 
	BOOL fBold, BOOL fItalic, BOOL fUnderline, BOOL fOpaque)
{
HDC hDC = Handle (API_WINDOW_HDC);					// PrinterHDC
HDC hTargetDC = Handle (API_WINDOW_TARGETHDC);		// TargetDC
AlignType rgAT = ATLeft;

	if (LL_SUB_ITEM_RechtsOben == rgPos || LL_SUB_ITEM_RechtsUnten == rgPos)
		rgAT = ATRight;

// Formatieren der Textzeile, Iteration beginnend ab max. FontGröße
CoOrd iDelta = MulDiv(m_DotsPerMM.Y(), 3176L, 10000L);	// in Schritten zu 1 Pt
Rectangle rcHL;
Dimension dimFont (0, -(iSizeY + iDelta));

	{
	CoOrd iTop = rRc.Top();
	CoOrd iWidth = rRc.Width();
	CoOrd iHeight = rRc.Height();

		do {	// mindestens ein mal
			dimFont.Height() += iDelta;	// immer kleiner werden

#if !defined(_TRIAS_OLDIMPLEMENTATION2)
		CVFont locFont (StdFamily(iFamily), dimFont, pcFont);
#else
		Font locFont (StdFamily(iFamily), dimFont, pcFont);
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)

			if (fBold) locFont.SetBold();	// Fett
			if (fItalic) locFont.SetItalic();
			if (fUnderline) locFont.SetUnderline();

		pFont pF = ChangeFont (&locFont);

			rcHL = Rectangle(iTop, rRc.Left(), iTop, rRc.Right());

		// Text ausrichten, Textgröße bestimmen
		CoOrd iLine = Justify (hDC, hTargetDC, pcText, NULL, (RECT *)&rcHL, rgAT, false);

			ChangeFont (pF);
			if (-1 == iLine) return false;		// kein Text da

		} while (dimFont.Height() < 0 && (rcHL.Height() > iHeight || rcHL.Width() > iWidth) );

		if (dimFont.Height() >= 0) return false;	// Text zu lang, nicht darstellbar
	}

// Text ausgeben
	{
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
	CVFont locFont (StdFamily(iFamily), dimFont, pcFont);
#else
	Font locFont (StdFamily(iFamily), dimFont, pcFont);
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)

		if (fBold) locFont.SetBold();	// Fett
		if (fItalic) locFont.SetItalic();
		if (fUnderline) locFont.SetUnderline();

	pFont pF = ChangeFont (&locFont);
	CoOrd iH = rcHL.Height();			// am unteren BereichsRand positionieren
	int iBkMode = SetBkMode (hDC, fOpaque ? OPAQUE : TRANSPARENT);

		rcHL = Rectangle (rRc.Bottom()+iH, rRc.Left(), rRc.Bottom(), rRc.Right());
		Justify (hDC, hTargetDC, pcText, NULL, (RECT *)&rcHL, rgAT, true);
		SetBkMode (hDC, iBkMode);

		ChangeFont (pF);
	}
	return true;
}

