// Routinen zur Druckerverwaltung und zum Drucken
// File: PRINTER.CXX

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

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// extern Window *CurrActW;

extern bool PrintEFlag;
extern bool LegendToRepaint;

bool GenerateLegendOnly = false;	// PseudoZeichnen, um genaue Legende zu haben

static short iBandNo = 0;

// lokale Funktionen ----------------------------------------------------------
bool IrisWind::PrintGraphics (char *pJobName, const ObjContainer &rOC) 
{
// Notification rumschicken und Fragen, ob gedruckt werden darf
	if (DEXN_PrintingProject())
		return false;	// jemand hat was dagegen

// PrintLayout einstellen
CEierUhr Wait (this, CursorPath(g_cbCursorPrint));
PrinterPars PP;		// nur für alle Fälle

	if (NULL == m_pPD) {
		try {
		// DefaultPrinter einstellen, wenn dieser nicht verfügbar ist, dann wird 
		// das im DruckDialog ausgewertet
			m_pPD = new PrinterPars();				// erstmal nur anlegen
			m_pPD -> InitFromDefaultPrinter();
		
		} catch (bad_alloc) {
			m_pPD = NULL;		
		}
	}

CPrintLayoutSheet Sheet (this);
CPrintLayoutDlg PLDlg (rOC, DBO().pCT(), m_pPD ? *m_pPD : PP);
WDataObject DataObj;

	PLDlg.GetDataObject (DataObj.ppi());	// Fehler nicht fatal	
	Sheet.AddPage (&PLDlg);

string strKey (g_cbDocSubKey);

	strKey += string(g_cbDel) + g_cbPrintLayout;
	Sheet.LoadPages (DataObj, g_cbDocKey, strKey.c_str());	// zusätzliche Pages aus Registry laden

	Wait.Hide();
	Sheet.Show(Centre);

int fResult = Sheet.Result();

	CoFreeUnusedLibraries();			// DLL's wieder freigeben
	if (0 == fResult || IDCANCEL == fResult) 
		return false;			// abgebrochen

// Drucken beginnen
PrintLayout *pPL = PLDlg.GetLayout();

	if (NULL == pPL) return false;

	PLDlg.SaveEntries();				// letzte Einträge speichern

CEierUhr Wait1 (this, CursorPath(g_cbCursorPrint));
IrisPrinter p (pJobName, pPL, DBO(), m_pPD ? *m_pPD : PP);

	Wait1.Hide();
	DELETE (pPL);					// Speicher wieder freigeben

CDBOContext Ctx (this, DBO(), AspectRatio);			// Bildschirm-Einstellung verwalten

	Disable();                      // Hauptfenster passivieren
	m_pPrinter = &p;
	PrintEFlag = false;             // MenuPunkt passivieren

	if (p.isValid()) {
	// PrinterAbortBox anzeigen
		try {
		string strDevice (p.DeviceName());

			strDevice += ResString (IDS_ONPRINTERPORT, 16);
			strDevice += p.PortName();

			p.m_pABox = new PrintAbort (this, &p, strDevice.c_str());
			p.m_pABox -> SetStatus (ResString (IDS_PRINTGEN, 60));
			p.m_pABox -> Show();        // AbortBox anzeigen
			App :: Exec (ExecWhileEvent);

		// Ausgabe starten
			iBandNo = 0;
			if (IsWin40() || IsWinNT())
				p.Start();	// Win95, WinNT: no banding required
			else
				p.StartBanding();

		} catch(bad_alloc) {
			PrintEFlag = true;
			m_pPrinter = NULL;
			Enable();
			db_error (EC_NOMEMORY, RC_PrintGraphics);
			SetFocus();
			return false;
		}
	}

// Normalzustand wieder herstellen
	PrintEFlag = true;		// MenuPunkt wieder aktiv
	m_pPrinter = NULL;		// fertig mit Drucken

	Enable();				// Fenster wieder zu gebrauchen
	SetFocus();

// wir sind fertig mit drucken
	DEXN_ProjectPrinted();

return true;
}

// Eigentliche DruckRoutine ---------------------------------------------------
bool IrisPrinter :: PrinterExpose (PrinterExposeEvt e) 
{
// --> ActRect ist die Papiergröße, ExposedArea der aktuelle Streifen
	m_rDBO.Scale (this, m_Extend, m_Aspect, &m_ActRect);
	m_rDBO.SetEA (m_ActRect);		// für Legende gesamtes Papier
	
// generieren der Legende
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
		m_pLO = CLegendeObjekt :: CreateInstance (this, m_rDBO, pLRc, &Pars());
		if (m_pLO) {
			m_pLO -> SetBaseValues (m_rcPageBase, Handle (API_WINDOW_TARGETHDC));	// Blattgröße mitteilen
			m_pLO -> FitLegendSize (pLRc, Handle (API_WINDOW_TARGETHDC));
		}
	}

// ClipGrenzen festlegen
Rectangle rcT1 = e.GetExposedArea();

	if (rcT1.Left() == rcT1.Right() || rcT1.Right() == rcT1.Bottom())
		m_rDBO.SetEA (m_ActRect);		// kein Banding
	else {
	Rectangle rcT2 = m_ActRect & rcT1;

		m_rDBO.SetEA (rcT2);
	}

// Drucken der Grafik
	GenerateLegendOnly = false;
	if (!m_fLegendOnly) DrawEx ((DrawObject *)&m_rDBO, 0);

// Legende ausgeben
	if (m_pLO != NULL) DrawEx (m_pLO, NULL);	
	else
		m_lsLegende = LSNoLegend; // Fehler: keine Legende ausgeben

CLegSizeCache Cache;

	if (Cache.FInit(Pars())) {
	long lWidthB = (long)(((m_rcPageBase.Right()-m_rcPageBase.Left())*100L)/m_DotsPerMM.Width());
	long lHeightB = (long)(((m_rcPageBase.Top()-m_rcPageBase.Bottom())*100L)/m_DotsPerMM.Height());

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
	if (m_msMasstab != MSNoMasstab) PaintMasstab (Cache);

// Druckbereich markieren
	PaintEdges (m_rcPageSize);
	if (!Cache.NoTRiASLogo())			// nur nicht, wenn explizit nicht erwünscht
		PaintTRiASLogo (m_RcFrame);		// TRiAS® am unteren Rand

// Rahmen etc. zeichnen
	if (m_fsFrame != FSNoFrame) {
	int iWidth = 40;		// 0.4 mm

		PaintRahmen (m_RcFrame, iWidth);
		if (m_iHeadLine) PaintRahmen (m_RcHeadLine, iWidth);
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

// Status anzeigen
	{
	char OutBuff[80];

		wsprintf (OutBuff, ResString(IDS_PRINTBAND, 50).Addr(), 
			  ++iBandNo, 1);
		m_pABox -> SetStatus (OutBuff); 
	}

return false;		// nur eine Seite drucken
}

// Drucken eines kleinen TRiAS-Logos rechts unten außerhalb des Rahmens -------
void IrisPrinter :: PaintTRiASLogo (Rectangle &rRC)
{
HDC hDC = Handle (API_WINDOW_HDC);					// PrinterHDC
HDC hTargetDC = Handle (API_WINDOW_TARGETHDC);		// TargetDC
CoOrd iPtHeight = (CoOrd)(((long)m_DotsPerMM.Y()*3176L)/10000L);	// 1pt
CoOrd iHeight = (rRC.Top()-rRC.Bottom())/300;

// Höhe mit 6Pt bzw. 10 Pt begrenzen
	if (iHeight < 6*iPtHeight) iHeight = 6*iPtHeight;
	else if (iHeight > 10*iPtHeight) iHeight = 10*iPtHeight;

Dimension dimFont (0, -iHeight);
ResString rsArial (IDS_ARIAL, 20);
Font locFont (Swiss, dimFont, rsArial);
pFont pF = ChangeFont (&locFont);
RECT rcHL;
CoOrd iTop = rRC.Bottom() - iHeight/6; 

	SetRect (&rcHL, rRC.Left(), iTop, rRC.Right(), iTop);

// Text ausrichten, Textgröße bestimmen, Text ausgeben
	Justify (hDC, hTargetDC, g_cbTRiAS, NULL, &rcHL, ATRight, false);
	Justify (hDC, hTargetDC, g_cbTRiAS, NULL, &rcHL, ATRight, true);

	ChangeFont (pF);
}

// Drucken der Überschrift ----------------------------------------------------
void IrisPrinter :: PaintHeadLine (Rectangle &rRC, LPCSTR pText) 
{
HDC hDC = Handle (API_WINDOW_HDC);			// PrinterHDC
HDC hTargetDC = Handle (API_WINDOW_TARGETHDC);		// TargetDC

// Formatieren der Kopfzeile, Iteration beginnend ab max. FontGröße
CoOrd iDelta = (CoOrd)(((long)m_DotsPerMM.Y()*3176L)/10000L);	// in Schritten zu 1 Pt
CoOrd iExtLeading = ((rRC.Top() - rRC.Bottom())*3) / 20;
CoOrd dX = (rRC.Right() - rRC.Left()) / 20;
ResString rsArial (IDS_ARIAL, 20);
RECT rcHL;
Dimension dimFont (0, -(iExtLeading * 8 + iDelta));

	{
	CoOrd iTop = rRC.Top() - iExtLeading;
	CoOrd iWidth = rRC.Right() - rRC.Left() - 2*dX;
	CoOrd iHeight = rRC.Top() - rRC.Bottom() - 2*iExtLeading;

		do {	// mindestens ein mal
			dimFont.Height() += iDelta;	// immer kleiner werden

		Font locFont (Swiss, dimFont, rsArial);

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
	Font locFont (Swiss, dimFont, rsArial);

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

void IrisPrinter :: PaintMasstab (CLegSizeCache &rCache)
{
HDC hDC = Handle (API_WINDOW_HDC);			// PrinterHDC

// Text ausgeben
char cbBuffer[_MAX_PATH];
ResString resMasstab (IDS_PRINTLAYOUTMASSTAB, 20);

	wsprintf (cbBuffer, "%s %s1:%ld", resMasstab.Addr(),
		  m_fRounded ? "ca. " : "", m_lMasstab);

long lTop = rCache.MasstabVorHoehe (2*(long)m_DotsPerMM.Height());
long lBottom = rCache.MasstabNachHoehe (2*(long)m_DotsPerMM.Height());
long lLeft = rCache.KastenVorBreite (2*(long)m_DotsPerMM.Width());
long lRight = rCache.KastenNachBreite (2*(long)m_DotsPerMM.Width());

// Font holen
ResString rsArial (IDS_ARIAL, 20);
bool fBold = false;
bool fItalic = false;
bool fUnderline = false;
string strFontName = rsArial.Addr();
int iFamily = Swiss;
int iSizeY = 12;

	rCache.MasstabFont (iFamily, strFontName, iSizeY, 	
			    fBold, fItalic, fUnderline);

Font MFont ((StdFamily)iFamily, Dimension(0, -iSizeY), strFontName.c_str());
	
	if (fBold) MFont.SetBold();
	if (fItalic) MFont.SetItalic();
	if (fUnderline) MFont.SetUnderline();

pFont pF = ChangeFont (&MFont);

Point pt (CoOrd(m_RcMasstab.Left() + lLeft), CoOrd(m_RcMasstab.Top() - lTop)); 
CoOrd lWidth = (CoOrd)(m_RcMasstab.Right()-m_RcMasstab.Left()-lLeft-lRight);
Rectangle rcSize (pt, Dimension (lWidth, 0));
string strDesc;		// Stand vom ... (BeschreibungsInfo im MaßstabsFeld)

	if (rCache.MasstabDesc (strDesc)) {
		Justify (hDC, hDC, strDesc.c_str(), NULL, (RECT *)&rcSize, ATRight, true);
		rcSize.Bottom() = rcSize.Top();	// nächste Zeile
	} 

CoOrd iLine = Justify (hDC, hDC, cbBuffer, NULL, (RECT *)&rcSize, ATLeft, true);

// Meander konfigurieren
long lWidthM = (64L*lWidth)/100L;		// erste Näherung
long M = (long)(((lWidthM/m_DotsPerMM.Width())*m_lMasstab)/1000);	// entsprechende Länge in [m]
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
	if (M > 53) 		{ iTyp = 3; lMax = 8; }
	for (int i = 0; i <= iZ; i++)
		lMax *= 10;

	lWidthM = (long)((1000*m_DotsPerMM.Width()*lMax)/m_lMasstab);

// Bereich berechnen, in dem Meander dargestellt werden soll
CoOrd iTop = CoOrd(rcSize.Bottom() - rCache.MasstabZwischenHoehe (2*(long)m_DotsPerMM.Height()));
Point ptM (rcSize.Left(), iTop);
CoOrd dY = CoOrd((iTop-(m_RcMasstab.Bottom() + lBottom))/2);

	PaintMeander (hDC, iTyp, ptM, CoOrd(lWidthM), CoOrd(dY), CoOrd(rCache.MeanderDicke(35)), lMax, iZ, iLine);
	ChangeFont (pF);
}

// Meander zeichnen, Bezugspunkt ist links oben -------------------------------
#define NUMMEANDERS	4
#define MEANDERSTEPS	7

static int s_ibMeander[NUMMEANDERS][MEANDERSTEPS] = {
	{ 0,  2,   5,  10,  25,  50, 100, },
	{ 0,  5,  10,  25,  50, 100, 200, },
	{ 0, 12,  25,  50, 100, 200, 400, },
	{ 0, 25,  50, 100, 200, 400, 800, },
};

void IrisPrinter :: PaintMeander (HDC hDC, int iTyp, Point pt, int dX, int dY, 
				  int iWidth, long lMax, int iZ, int iLine)
{
	TX_ASSERT(0 <= iTyp && NUMMEANDERS > iTyp);

long lScale = s_ibMeander[iTyp][MEANDERSTEPS-1];
CoOrd iDots = (CoOrd)((m_DotsPerMM.X()+m_DotsPerMM.Y())/2);	// mittlere Dots/mm
HPEN hOldPen = (HPEN)::SelectObject (hDC, 
			::CreatePen (PS_SOLID, (iWidth*iDots)/100, RGB(0, 0, 0)));
UINT uiAlign = ::SetTextAlign (hDC, TA_TOP|TA_CENTER);
bool fUp = true;	// am Anfang geht's hoch
char cbBuffer[64];

	::MoveToEx (hDC, pt.X(), pt.Y()-dY, NULL);
	::TextOut (hDC, pt.X(), pt.Y()-(dY+iLine/2), "0", 1);

	for (int i = 0; i < MEANDERSTEPS-1; i++) {
	long lY = pt.Y() - (fUp ? 0 : dY);

		::LineTo (hDC, CoOrd(pt.X() + (s_ibMeander[iTyp][i]*long(dX))/lScale), CoOrd(lY));
		::LineTo (hDC, CoOrd(pt.X() + (s_ibMeander[iTyp][i+1]*long(dX))/lScale), CoOrd(lY));
		if ((MEANDERSTEPS - 2) == i) {
			if (1 == lMax)		// Spezialfall 1
				strcpy (cbBuffer, "0.5 m");
			else if (1000 == lMax)	// Spezialfall 2
				strcpy (cbBuffer, "500 m");
			else			// normale Behandlung
				wsprintf (cbBuffer, "%ld %sm", iZ < 2 ? lMax/2 : lMax/2000, iZ < 2 ? "" : "k");
			::TextOut (hDC, CoOrd(pt.X() + (s_ibMeander[iTyp][i]*long(dX))/lScale), 
					CoOrd(pt.Y()-(dY+iLine/2)), 
				   cbBuffer, strlen(cbBuffer));
		}
		fUp = !fUp;
	}
	::LineTo (hDC, pt.X() + dX, pt.Y());

	wsprintf (cbBuffer, "%ld %sm", iZ < 2 ? lMax : lMax/1000, iZ < 2 ? "" : "k");
	::TextOut (hDC, pt.X() + dX, pt.Y()-(dY+iLine/2), cbBuffer, strlen(cbBuffer));

	::SetTextAlign (hDC, uiAlign);
	::DeleteObject (SelectObject (hDC, hOldPen));
}

// Drucken eines Rechteckes ---------------------------------------------------
void IrisPrinter :: PaintRahmen (Rectangle &rRC, int iWidth) 
{
HDC hDC = Handle (API_WINDOW_HDC);			// PrinterHDC
CoOrd iDots = (CoOrd)((m_DotsPerMM.X()+m_DotsPerMM.Y())/2);	// mittlere Dots/mm
HPEN hOldPen = (HPEN)SelectObject (hDC, 
			CreatePen (PS_SOLID, (iWidth*iDots)/100, RGB(0, 0, 0)));
HBRUSH hOldBr = (HBRUSH)SelectObject (hDC, GetStockObject (HOLLOW_BRUSH));

	DrawRectangle (hDC, rRC.Left(), rRC.Top(), rRC.Right(), rRC.Bottom());
	DeleteObject (SelectObject (hDC, hOldPen));
	SelectObject (hDC, hOldBr);
}

// Füllen eines Rechteckes ----------------------------------------------------
void IrisPrinter :: FillRahmen (Rectangle &rRC) 
{
HDC hDC = Handle (API_WINDOW_HDC);			// PrinterHDC
HPEN hOldPen = (HPEN)SelectObject (hDC, CreatePen (PS_NULL, 0, RGB(0, 0, 0)));
HBRUSH hOldBr = (HBRUSH)SelectObject (hDC, GetStockObject (WHITE_BRUSH));

	DrawRectangle (hDC, rRC.Left(), rRC.Top(), rRC.Right(), rRC.Bottom());
	DeleteObject (SelectObject (hDC, hOldPen));
	SelectObject (hDC, hOldBr);
}

// Ecken des bedruckbaren Bereiches ausgeben ----------------------------------
void IrisPrinter :: PaintEdges (Rectangle &rRC) 
{
HDC hDC = Handle (API_WINDOW_HDC);			// PrinterHDC
COLORREF crBlack = RGB (0, 0, 0);

	SetPixel (hDC, rRC.Left(), rRC.Top(), crBlack);
	SetPixel (hDC, rRC.Right(), rRC.Top(), crBlack);
	SetPixel (hDC, rRC.Left(), rRC.Bottom(), crBlack);
	SetPixel (hDC, rRC.Right(), rRC.Bottom(), crBlack);
}


// Ausgabe eines FirmenLogoBereiches -----------------------------------------
void IrisPrinter :: PaintFirmLogo (CLegSizeCache &rCache, Rectangle &rRc, int iCnt)
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

// Berechnen der verschiedenen FirmenLogoBereiche -----------------------------
bool IrisPrinter :: CalcLinksObenRect (CLegSizeCache &rCache, Rectangle &rRc, 
				       int iCnt, Rectangle *prc)
{
	TX_ASSERT (NULL != prc);

long lHeight = rCache.LogoFeldHoehe (0, LL_SUB_ITEM_LinksOben, iCnt);
long lWidth = rCache.LogoFeldBreite (0, LL_SUB_ITEM_LinksOben, iCnt);
	
	if (lHeight <= 0 || lWidth <= 0) return false;		// nicht gegeben

long lTop = rCache.LogoVorHoehe (2*(long)m_DotsPerMM.Height());
long lLeft = rCache.LogoVorBreite (2*(long)m_DotsPerMM.Width());

	prc -> Top() = CoOrd(rRc.Top() - lTop);
	prc -> Left() = CoOrd(rRc.Left() + lLeft);
	prc -> Bottom() = CoOrd(prc -> Top() - lHeight);
	prc -> Right() = CoOrd(prc -> Left() + lWidth);

return true;
}

bool IrisPrinter :: CalcRechtsObenRect (CLegSizeCache &rCache, Rectangle &rRc, 
					int iCnt, Rectangle *prc)
{
	TX_ASSERT (NULL != prc);

long lHeight = rCache.LogoFeldHoehe (0, LL_SUB_ITEM_RechtsOben, iCnt);
long lWidth = rCache.LogoFeldBreite (0, LL_SUB_ITEM_RechtsOben, iCnt);
	
	if (lHeight <= 0 || lWidth <= 0) return false;		// nicht gegeben

long lTop = rCache.LogoVorHoehe (2*(long)m_DotsPerMM.Height());
long lRight = rCache.LogoNachBreite (2*(long)m_DotsPerMM.Width());

	prc -> Top() = CoOrd(rRc.Top() - lTop);
	prc -> Bottom() = CoOrd(prc -> Top() - lHeight);
	prc -> Right() = CoOrd(rRc.Right() - lRight);
	prc -> Left() = CoOrd(prc -> Right() - lWidth);

return true;
}

bool IrisPrinter :: CalcLinksUntenRect (CLegSizeCache &rCache, Rectangle &rRc, 
				int iCnt, Rectangle *prc)
{
	TX_ASSERT (NULL != prc);

long lHeight = rCache.LogoFeldHoehe (0, LL_SUB_ITEM_LinksUnten, iCnt);
long lWidth = rCache.LogoFeldBreite (0, LL_SUB_ITEM_LinksUnten, iCnt);
	
	if (lHeight <= 0 || lWidth <= 0) return false;		// nicht gegeben

long lBottom = rCache.LogoNachHoehe (2*(long)m_DotsPerMM.Height());
long lLeft = rCache.LogoVorBreite (2*(long)m_DotsPerMM.Width());

	prc -> Bottom() = CoOrd(rRc.Bottom() + lBottom);
	prc -> Top() = CoOrd(prc -> Bottom() + lHeight);
	prc -> Left() = CoOrd(rRc.Left() + lLeft);
	prc -> Right() = CoOrd(prc -> Left() + lWidth);

return true;
}

bool IrisPrinter :: CalcRechtsUntenRect (CLegSizeCache &rCache, Rectangle &rRc, 
				int iCnt, Rectangle *prc)
{
	TX_ASSERT (NULL != prc);

long lHeight = rCache.LogoFeldHoehe (0, LL_SUB_ITEM_RechtsUnten, iCnt);
long lWidth = rCache.LogoFeldBreite (0, LL_SUB_ITEM_RechtsUnten, iCnt);
	
	if (lHeight <= 0 || lWidth <= 0) return false;		// nicht gegeben

long lBottom = rCache.LogoNachHoehe (2*(long)m_DotsPerMM.Height());
long lRight = rCache.LogoNachBreite (2*(long)m_DotsPerMM.Width());

	prc -> Bottom() = CoOrd(rRc.Bottom() + lBottom);
	prc -> Top() = CoOrd(prc -> Bottom() + lHeight);
	prc -> Right() = CoOrd(rRc.Right() - lRight);
	prc -> Left() = CoOrd(prc -> Right() - lWidth);

return true;
}

// Ausgabe eines Bereiches eines FirmenLogos ----------------------------------
bool IrisPrinter :: PaintFirmLogoFeld (CLegSizeCache &rCache, Rectangle &rRc, 
				       int rgPos, int iCnt, bool fOpaque)
{
// Font holen
bool fBold = false;
bool fItalic = false;
bool fUnderline = false;
string strFontName = ResString(IDS_ARIAL, 20).Addr();
int iFamily = Swiss;
int iSizeY = 12;

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

bool IrisPrinter :: PaintTextRect (LPCSTR pcText, int rgPos,
			Rectangle &rRc, int iFamily, LPCSTR pcFont, int iSizeY, 
			bool fBold, bool fItalic, bool fUnderline, bool fOpaque)
{
HDC hDC = Handle (API_WINDOW_HDC);			// PrinterHDC
HDC hTargetDC = Handle (API_WINDOW_TARGETHDC);		// TargetDC
AlignType rgAT = ATLeft;

	if (LL_SUB_ITEM_RechtsOben == rgPos || LL_SUB_ITEM_RechtsUnten == rgPos)
		rgAT = ATRight;

// Formatieren der Textzeile, Iteration beginnend ab max. FontGröße
CoOrd iDelta = (CoOrd)(((long)m_DotsPerMM.Y()*3176L)/10000L);	// in Schritten zu 1 Pt
RECT rcHL;
Dimension dimFont (0, -(iSizeY + iDelta));

	{
	CoOrd iTop = rRc.Top();
	CoOrd iWidth = rRc.Right() - rRc.Left();
	CoOrd iHeight = rRc.Top() - rRc.Bottom();

		do {	// mindestens ein mal
			dimFont.Height() += iDelta;	// immer kleiner werden

		Font locFont (StdFamily(iFamily), dimFont, pcFont);

			if (fBold) locFont.SetBold();	// Fett
			if (fItalic) locFont.SetItalic();
			if (fUnderline) locFont.SetUnderline();

		pFont pF = ChangeFont (&locFont);

			SetRect (&rcHL, rRc.Left(), iTop, rRc.Right(), iTop);

		// Text ausrichten, Textgröße bestimmen
		CoOrd iLine = Justify (hDC, hTargetDC, pcText, NULL, &rcHL, rgAT, false);

			ChangeFont (pF);
			if (-1 == iLine) return false;		// kein Text da

		} while (dimFont.Height() < 0 && 
			 ((rcHL.top - rcHL.bottom > iHeight) || 
			  (rcHL.right - rcHL.left > iWidth))
			);

		if (dimFont.Height() >= 0) return false;	// Text zu lang, nicht darstellbar
	}

// Text ausgeben
	{
	Font locFont (StdFamily(iFamily), dimFont, pcFont);

		if (fBold) locFont.SetBold();	// Fett
		if (fItalic) locFont.SetItalic();
		if (fUnderline) locFont.SetUnderline();

	pFont pF = ChangeFont (&locFont);
	CoOrd iH = rcHL.top-rcHL.bottom;	// am unteren BereichsRand positionieren
	int iBkMode = SetBkMode (hDC, fOpaque ? OPAQUE : TRANSPARENT);

		SetRect (&rcHL, rRc.Left(), rRc.Bottom()+iH, rRc.Right(), rRc.Bottom());
		Justify (hDC, hTargetDC, pcText, NULL, &rcHL, rgAT, true);
		SetBkMode (hDC, iBkMode);

		ChangeFont (pF);
	}

return true;
}

// Konstruktor ----------------------------------------------------------------
IrisPrinter :: IrisPrinter (char *jobName, PrintLayout *pPL, 
				DatenBasisObjekt &rDBO, PrinterPars &rPD) 
	     : BandingPrinter (jobName, &rPD),
		   m_rDBO (rDBO), m_Idents (rDBO.Idents()),
	       m_pbdDB (rDBO.PbdDB()),
	       m_rPD (rPD)
{
	m_pABox = NULL;		// AbortBox - zeiger nullsetzen
	m_fLogo = false;
	m_fLegendOnly = pPL -> m_fLegendOnly;

// LegendeObjekt noch nicht vorhanden
	m_pLO = NULL;

// FormatierungsInfo setzen
	m_DotsPerMM = Pars().GetDotsPerMM();		// ScalingParameter
	m_Aspect = Pars().GetAspectRatio();

	m_ActRect = *(pPL -> m_plRcSpiegel);		// SeitenLayout merken
	m_Extend = *(pPL -> m_plOCSpiegel);
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

//	m_fHLFontSizeSet = false;
}

// Destruktor -----------------------------------------------------------------
IrisPrinter :: ~IrisPrinter (void) 
{
	DELETE (m_pABox);
	if (m_pLO && m_pLO -> m_pR) {	// Legende-Rechteck wieder freigeben
		delete m_pLO -> m_pR;
		m_pLO -> m_pR = NULL;
	}
	DELETE (m_pLO);
	DELETE (m_lpHeadLine);
}


// ----------------------------------------------------------------------------
// FehlerFunktion, alle Fehler sind fatal
bool IrisPrinter :: PrinterError (PrinterErrorEvt) 
{
	return false;
}

#if !defined(WIN32)
bool IrisWind :: PrinterMode (void) 
{
	if (m_pPD) m_pPD -> SetUp();

return true;
}
#endif // !WIN32
