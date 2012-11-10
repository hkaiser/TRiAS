// Erweiterter Pen, der Mehrfach-Linien erzeugen kann -------------------------
// File: EPEN.CXX

#include "trias02p.hxx"

#include "epen.hxx"

// Daten, die die verschiedenen Pentypen verschlüsseln ------------------------
// 1. Breitenverhältnisse der einzelnen Linien (von außen nach innen)
static short EPenW1[] = { 1000 };		// normale Linie
static short EPenW2[] = { 1000, 600, };		// DoppelLinien
static short EPenW3[] = { 1000, 600, 100, };	// DreifachLinien

// 2. GesamtStrukturBeschreibung für alle LinienTypen
static EPEN EPens[] = {
// normale LinienTypen
	{ 1, EPenW1, 0, 0, 0, 0 },	// SolidLine
	{ 1, EPenW1, 0, 0, 0, 0 },	// Dashed
	{ 1, EPenW1, 0, 0, 0, 0 },	// Dotted
	{ 1, EPenW1, 0, 0, 0, 0 },	// Dash_Dot
	{ 1, EPenW1, 0, 0, 0, 0 },	// Dash_Dot_Dot
	{ 1, EPenW1, 0, 0, 0, 0 },	// ClearLine
	{ 1, EPenW1, 0, 0, 0, 0 },	// InsideFrameLine

	{ 2, EPenW2, 1, RGB (0, 0, 0), 3, 0 },	// ExtLineStyle1
	{ 2, EPenW2, 0, RGB (0, 0, 0), 3, 0 },	// ExtLineStyle2
	{ 3, EPenW3, 1, RGB (0, 0, 0), 5, 0 },	// ExtLineStyle3

	{ 2, EPenW2, 1, RGB (255, 255, 255), 3, 0 },	// ExtLineStyle4
	{ 2, EPenW2, 0, RGB (255, 255, 255), 3, 0 },	// ExtLineStyle5
	{ 3, EPenW3, 1, RGB (255, 255, 255), 5, 0 },	// ExtLineStyle6

	{ 3, EPenW3, 1, RGB (0, 0, 0), 5, 1 },		// ExtLineStyle7
	{ 3, EPenW3, 1, RGB (255, 255, 255), 5, 1 },	// ExtLineStyle8
};
#define NUMEPENS (sizeof(EPens)/sizeof(EPens[0]))


// Berechnet real zu verwendende Breite der Linie -----------------------------
/*static*/
uint ExtPen::EPenWidth (StdLineStyle els, short &iWidth, short &iCnt)
{
	if ((short)els < 0 || (short)els >= NUMEPENS)
		els = SolidLine;	// ParameterTest

	iCnt = EPens[els].iCnt;	// Anzahl der Linien setzen

	if (iWidth == -1) 
		iWidth = EPens[els].minW;	// DefaultBreite verwenden
	else if (iWidth < 0)
		iWidth = -iWidth;

	if (iWidth >= EPens[els].minW)
		return (uint)(((long)iWidth * EPens[els].pW[EPens[els].iAct])/1000L); 

	iCnt = 1;	// Komplexlinie zu dick, normale Linie zeichnen
	return (uint)iWidth;
}

// Liefert Style für den unterliegenden Pen -----------------------------------
static StdLineStyle EPenStyle (StdLineStyle els)
{
	if (els > InsideFrameLine) 
		return InsideFrameLine;
	return els;
}

// Konstruktoren --------------------------------------------------------------
ExtPen :: ExtPen (StdLineStyle els, short iWidth, Color C)
	: Pen (EPenStyle (els), EPenWidth (els, iWidth, m_iCnt), C)
{
	m_iAct = EPens[els].iAct;
	m_fInv = EPens[els].fInv;
	m_iWidth = iWidth;
	m_C = C;
	if (iWidth >= 0 && iWidth < EPens[els].minW) {
		m_iAct = 0;
		m_fInv = 0;
	}
	m_els = (ExtLineStyle)els;
	m_pBlackPen = NULL;
	m_pColorPen = NULL;
	m_locColor = *(Color *)&EPens[els].C;
}

ExtPen :: ~ExtPen (void)
{
	DELETE (m_pColorPen);
	DELETE (m_pBlackPen);
}

// Liefert Handle des aktuellen Layers ----------------------------------------
HPEN ExtPen :: GetHandle (short iLayer)
{
	if (iLayer < 0 || iLayer > m_iCnt -1)
		return Pen :: Handle (API_PEN_HPEN);

// bei Bedarf FarbPen generieren
uint iWidth = (uint)(((long)m_iWidth * EPens[m_els].pW[iLayer])/1000L);
StdLineStyle locStyle = iWidth > 1 ? InsideFrameLine : SolidLine;

	DELETE (m_pColorPen);
	if (m_fInv ? (iLayer != m_iAct) : (iLayer == m_iAct)) {
		m_pColorPen = new Pen (EPenStyle((StdLineStyle)m_els), iWidth, m_C);
		if (m_pColorPen)
			return m_pColorPen -> Handle (API_PEN_HPEN);
	}

// ansonsten Pen mit der vordefinierten Farbe erzeugen
	DELETE (m_pBlackPen);
	m_pBlackPen = new Pen (locStyle, iWidth, m_locColor);
	if (m_pBlackPen) 
		return m_pBlackPen -> Handle (API_PEN_HPEN);

return (HPEN)0;
}
