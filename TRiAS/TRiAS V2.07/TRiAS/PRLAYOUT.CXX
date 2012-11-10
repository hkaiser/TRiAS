// Profile-Routinen, die intelligent die Maße des Drucklayouts berechnen ------
// File: PRLAYOUT.CXX

#include "triaspre.hxx"

#include <stdio.h>
#include <printer.hxx>

#include <fnamestr.h>
#include "prlayhlp.hxx"
#include "prlayout.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Strings für Zugriff aus INI/Registry ---------------------------------------
static const char *s_szFormat[] = {
	TEXT(""),
	TEXT("QuerFormat"),
	TEXT("HochFormat"),
};

static const char *s_szItem[] = {
	TEXT(""),
	TEXT("Eintrag"),
	TEXT("LegendeKopf"),
	TEXT("Legende"),
	TEXT("Leerzeile"),
	TEXT("Maßstab"),
	TEXT("Meander"),
	TEXT("Signatur"),
	TEXT("Überschrift"),
	TEXT("Logo"),
	TEXT("LogoLinksOben"),
	TEXT("LogoLinksUnten"),
	TEXT("LogoRechtsOben"),
	TEXT("LogoRechtsUnten"),
};

static const char *s_szPosition[] = {
	TEXT(""),
	TEXT("Vor"),
	TEXT("Nach"),
	TEXT("Zwischen"),
};

static const char *s_szAttribute[] = {
	TEXT(""),
	TEXT("Breite"),
	TEXT("Höhe"),
	TEXT("Font"),
	TEXT("Beschreibung"),
	TEXT("Typ"),
	TEXT("Opaque"),
};

// Spezielle, nicht dokumentierte Einträge ------------------------------------
static const char s_szNoTRiASLogo[] = TEXT("NoTRiASLogo");

// Helperfunktionen -----------------------------------------------------------
static string BuildKey (LEGLAYOUT_ITEM rgItem, LEGLAYOUT_POSITION rgPos, 
			LEGLAYOUT_ATTRIBUTE rgAttr, int iCnt = 0)
{
	TX_ASSERT(0 < rgItem && LL_ITEM_MaxItem >= rgItem);
	TX_ASSERT(0 <= rgPos && LL_POSITION_MaxPosition >= rgPos);
	TX_ASSERT(0 < rgAttr && LL_ATTRIBUTE_MaxAttribute >= rgAttr);
	TX_ASSERT(0 <= iCnt && MAX_LOGOFELD >= iCnt);
		
string str = s_szItem[rgItem];

	str += s_szPosition[rgPos];
	str += s_szAttribute[rgAttr];

	if (iCnt > 0) str += char(iCnt + '0');

return str;
}

// Eigentliche Klasse ---------------------------------------------------------
CPrintLegLayout :: CPrintLegLayout (PrinterPars &rPP)
		 : m_rgFormat(LL_FORMAT_None), m_strBuffer(_MAX_PATH, default_size),
		   m_rPP(rPP), m_dimDots (rPP.GetDotsPerMM())
{
	m_strFile = TEXT("tlegend.ini");

char cbBuffer[_MAX_PATH];

	if (NULL != DEX_GetActiveProject (cbBuffer)) {
	string str = cbBuffer;

		m_strPrjFile = get_drive (str);
		m_strPrjFile += get_path (str);
		m_strPrjFile += get_name (str);
		m_strPrjFile += TEXT(".ini");
	}

	m_pFKoeffX = FKoeffX;
	m_pFKoeffY = FKoeffY;
}

CPrintLegLayout :: ~CPrintLegLayout (void)
{
	// nothing to do
}

CPrintLegLayout *CPrintLegLayout :: CreateInstance (PrinterPars &rPP)
{
CPrintLegLayout *pPL = new CPrintLegLayout (rPP);

	if (NULL == pPL || !pPL -> FInit()) {
		DELETE(pPL);
		return NULL;
	}

return pPL;
}

// Funktionen, die Skalierungskoeffizienten berechnen -------------------------
double FKoeffX (long lBase)
{
	return double(lBase-A4_WIDTH)/double(A0_WIDTH-A4_WIDTH);
}

double FKoeffY (long lBase)
{
	return double(lBase-A4_HEIGHT)/double(A0_HEIGHT-A4_HEIGHT);
}

#if defined(_DEBUG)	// sonst inline
double CPrintLegLayout :: kX (long lBase)
{
	TX_ASSERT(NULL != m_pFKoeffX);

return (*m_pFKoeffX)(lBase);
}

double CPrintLegLayout :: kY (long lBase)
{
	TX_ASSERT(NULL != m_pFKoeffX);

return (*m_pFKoeffY)(lBase);
}
#endif // _DEBUG

bool CPrintLegLayout :: FInit (void)
{
// Bestimmen, ob Hoch oder Querformat
Dimension dimPageSize = m_rPP.GetPageSize();
const DEVMODE *pDevMode = m_rPP.DeviceMode();

	TX_ASSERT(NULL != pDevMode);
	if (NULL == pDevMode) return false;

	if (pDevMode -> dmFields & DM_ORIENTATION) {	// Orientierung gegeben
		TX_ASSERT(pDevMode -> dmOrientation == DMORIENT_LANDSCAPE ||
			  pDevMode -> dmOrientation == DMORIENT_PORTRAIT);

		if (DMORIENT_PORTRAIT == pDevMode -> dmOrientation)
			m_rgFormat = LL_FORMAT_HochFormat;
		else
			m_rgFormat = LL_FORMAT_QuerFormat;
	}

// Koeffizienten berechenen (Funktionen vorbereiten)
	switch (m_rgFormat) {
	case LL_FORMAT_QuerFormat:
		m_pFKoeffX = FKoeffY;
		m_pFKoeffY = FKoeffX;
		break;
		
	case LL_FORMAT_HochFormat:
		m_pFKoeffX = FKoeffX;
		m_pFKoeffY = FKoeffY;
		break;

	default:
		m_pFKoeffX = FKoeffX;		// für alle Fälle
		m_pFKoeffY = FKoeffY;
		TX_ASSERT(false);
		break;
	}

return true;
}

long CPrintLegLayout :: Width (void)
{
	if (LL_FORMAT_QuerFormat == m_rgFormat) 
		return (long)m_dimDots.Height();
	else
		return (long)m_dimDots.Width();
}

long CPrintLegLayout :: Height (void)
{
	if (LL_FORMAT_HochFormat == m_rgFormat) 
		return (long)m_dimDots.Height();
	else
		return (long)m_dimDots.Width();
}

// liefert eine Breite aus der Legenden-Konfiguration -------------------------
long CPrintLegLayout :: GetValueXMM (long lDefault, long lBase, LEGLAYOUT_ITEM rgItem,
		LEGLAYOUT_POSITION rgPos, LEGLAYOUT_ATTRIBUTE rgAttr, int iCnt)
{
string str = BuildKey (rgItem, rgPos, rgAttr, iCnt);
long lA4 = 0L;
long lA0 = 0L;

	if (ReadLongs (str, lA4, lA0))
		return (lA4 + long(kX(lBase*100L)*(lA0-lA4)))/100L;
		
return lDefault;
}

long CPrintLegLayout :: GetValueX (long lDefault, long lBase, LEGLAYOUT_ITEM rgItem, 
		LEGLAYOUT_POSITION rgPos, LEGLAYOUT_ATTRIBUTE rgAttr, int iCnt)
{
string str = BuildKey (rgItem, rgPos, rgAttr, iCnt);
long lA4 = 0L;
long lA0 = 0L;

	if (ReadLongs (str, lA4, lA0))
		return (lA4 + long(kX(lBase)*(lA0-lA4)))*Width()/100L;
		
return lDefault;
}


// liefert eine Höhe aus der Legenden-Konfiguration ---------------------------
long CPrintLegLayout :: GetValueY (long lDefault, long lBase, LEGLAYOUT_ITEM rgItem, 
		LEGLAYOUT_POSITION rgPos, LEGLAYOUT_ATTRIBUTE rgAttr, int iCnt)
{
string str = BuildKey (rgItem, rgPos, rgAttr, iCnt);
long lA4 = 0L;
long lA0 = 0L;

	if (ReadLongs (str, lA4, lA0))
		return (lA4 + long(kY(lBase)*(lA0-lA4)))*Height()/100L;
		
return lDefault;
}

long CPrintLegLayout :: GetValueYAbs (long lDefault, long lBase, LEGLAYOUT_ITEM rgItem, 
		LEGLAYOUT_POSITION rgPos, LEGLAYOUT_ATTRIBUTE rgAttr)
{
string str = BuildKey (rgItem, rgPos, rgAttr);
long lA4 = 0L;
long lA0 = 0L;

	if (ReadLongs (str, lA4, lA0))
		return (lA4 + long(kY(lBase)*(lA0-lA4)));
		
return lDefault;
}

long CPrintLegLayout :: GetValueYMM (long lDefault, long lBase, LEGLAYOUT_ITEM rgItem,
		LEGLAYOUT_POSITION rgPos, LEGLAYOUT_ATTRIBUTE rgAttr, int iCnt)
{
string str = BuildKey (rgItem, rgPos, rgAttr, iCnt);
long lA4 = 0L;
long lA0 = 0L;

	if (ReadLongs (str, lA4, lA0))
		return (lA4 + long(kY(lBase*100L)*(lA0-lA4)))/100L;
		
return lDefault;
}

// Liefert die Parameter für einen Font ---------------------------------------
bool CPrintLegLayout :: GetFont (long lBase, LEGLAYOUT_ITEM rgItem, int &iFam, 
				 string &strName, int &iSizeY,
				 bool &fBold, bool &fItalic, bool &fUnderline,
				 int iCnt)
{
string str = BuildKey (rgItem, LL_POSITION_None, LL_ATTRIBUTE_Font, iCnt);
long lA4 = 0L;
long lA0 = 0L;

	if (!ReadString (str)) return false;

char cbBuffer[32];
int iConverted = sscanf (m_strBuffer.c_str(), "%ld;%ld;%d,\"%[^\"]\",%d,%d,%d", 
			 &lA4, &lA0, &iFam, cbBuffer, &fItalic, &fBold, &fUnderline);
				
	if (7 != iConverted) return false;

// Achtung lBase kommt in 0.01mm an, die Einträge der INI sind jedoch in Pt
	iSizeY = int(lA4 + (long)(kY(lBase)*(lA0-lA4)));	// Wert in Pt
	iSizeY = int(((iSizeY * 3176L)/10000L) * Height());	// Wert in Pixel

	strName = cbBuffer;

return true;
}

// Einlesen der Informationen aus der INI/Registry ----------------------------
bool CPrintLegLayout :: ReadString (string &strKey)
{
	m_strBuffer.resize (_MAX_PATH);

// zuerst in der Projekt-INI nachsehen
int iRead = GetPrivateProfileString (s_szFormat[m_rgFormat], strKey.c_str(), "", 
			(LPSTR)m_strBuffer.c_str(), _MAX_PATH, m_strPrjFile.c_str());

	if (0 == iRead)	{
	// wenn nicht gefunden, dann in TLEGEND.INI nachschauen
		iRead = GetPrivateProfileString (s_szFormat[m_rgFormat], 
				strKey.c_str(), "", (LPSTR)m_strBuffer.c_str(), 
				_MAX_PATH, m_strFile.c_str());
	}
	m_strBuffer.adjustlen();
	
return (0 != iRead) ? true : false;
}

// Eine Fontbeschreibung auswerten --------------------------------------------
pFont CPrintLegLayout :: MakeFont (int iFam, LPCSTR pcName, long lSize,
				   bool fBold, bool fItalic, bool fUnderline)
{
Dimension dim (0, CoOrd((lSize*3176L)/10000L));
pFont pF = new Font ((StdFamily)iFam, dim, pcName);

	if (NULL == pF) return NULL;
	
	if (fBold) pF -> SetBold();
	if (fUnderline) pF -> SetUnderline();
	if (fItalic) pF -> SetItalic();

return pF;
}

// Eine Streckenbeschreibung einlesen -----------------------------------------
bool CPrintLegLayout :: ReadLongs (string &strKey, long &rlA4, long &rlA0)
{
	if (!ReadString (strKey)) return false;

int iConverted = sscanf (m_strBuffer.c_str(), "%ld;%ld", &rlA4, &rlA0);
				
	return (2 == iConverted) ? true : false;
}

// Einen einzelnen Wert einlesen-----------------------------------------------
bool CPrintLegLayout :: ReadValue (string &strKey, long &rlVal)
{
	if (!ReadString (strKey)) return false;

int iConverted = sscanf (m_strBuffer.c_str(), "%ld", &rlVal);
				
	return (1 == iConverted) ? true : false;
}

long CPrintLegLayout :: GetSingleValue (long lDefault, LEGLAYOUT_ITEM rgItem, 
		LEGLAYOUT_POSITION rgPos, LEGLAYOUT_ATTRIBUTE rgAttr, int iCnt)
{
string str = BuildKey (rgItem, rgPos, rgAttr, iCnt);
long lValue = lDefault;

	if (!ReadValue (str, lValue))
		lValue = lDefault;

return lValue;
}

// Printer wurde modifiziert: neu initialiseren -------------------------------
bool CPrintLegLayout :: Refresh (void)
{
	m_dimDots = m_rPP.GetDotsPerMM();

return FInit();
}

// BeschreibungsInfo lesen ----------------------------------------------------
bool CPrintLegLayout :: GetString (string &rstr, LEGLAYOUT_ITEM rgItem,
		LEGLAYOUT_POSITION rgPos, LEGLAYOUT_ATTRIBUTE rgAttr, int iCnt)
{
string str = BuildKey (rgItem, rgPos, rgAttr, iCnt);

	if (!ReadString (str)) return false;
	rstr = m_strBuffer;

return true;
}

///////////////////////////////////////////////////////////////////////////////
// spezielle, nicht dokumentierte Einträge 
bool CPrintLegLayout :: NoTRiASLogo (void)
{
string str = s_szNoTRiASLogo;
long lFlag = true;

	if (ReadValue (str, lFlag))
		return lFlag ? true : false;

return false;		// kein Eintrag vorhanden, also ausgeben
}

///////////////////////////////////////////////////////////////////////////////
// Cache für LegendenGrößen
CLegSizeCache :: CLegSizeCache (void)
{
	m_fIsPrinter = false;
	m_pPrLayout = NULL;

	m_lBaseX = 0;
	m_lBaseY = 0;
}

bool CLegSizeCache :: FInit (PrinterPars &rPP)
{
	m_pPrLayout = CPrintLegLayout :: CreateInstance (rPP);
	if (NULL == m_pPrLayout) return false;
	
	m_fIsPrinter = true;		// Legende auf Drucker

return true;
}

CLegSizeCache :: ~CLegSizeCache (void)
{
	DELETE(m_pPrLayout);
}

bool CLegSizeCache :: Refresh (void)
{ 
	return (NULL != m_pPrLayout) ? m_pPrLayout -> Refresh() : true; 
}

void CLegSizeCache :: SetBaseValues (long lBaseX, long lBaseY)
{
	m_lBaseX = lBaseX;
	m_lBaseY = lBaseY;
}

// ZugriffsFunktionen auf LegendenMaße ----------------------------------------
long CLegSizeCache :: LegendeBreite (long lDefault, long lBase)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetValueXMM (lDefault, lBase, LL_ITEM_Legende);
}

long CLegSizeCache :: UeberschriftBreite (long lDefault, long lBase)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetValueXMM (lDefault, lBase, LL_ITEM_Ueberschrift);
}

long CLegSizeCache :: UeberschriftHoehe (long lDefault, long lBase)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetValueYMM (lDefault, lBase, LL_ITEM_Ueberschrift);
}

long CLegSizeCache :: LogoHoehe (long lDefault, long lBase, int iCnt)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetValueYMM (lDefault, lBase, 
		LL_ITEM_Logo, LL_POSITION_None, LL_ATTRIBUTE_Hoehe, iCnt);
}

///////////////////////////////////////////////////////////////////////////////
long CLegSizeCache :: UeberschriftTyp (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetSingleValue (lDefault, LL_ITEM_Ueberschrift, LL_POSITION_None, LL_ATTRIBUTE_Typ);
}

long CLegSizeCache :: LegendeVorHoehe (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetValueY (lDefault, m_lBaseY, LL_ITEM_Legende, LL_POSITION_Vor, LL_ATTRIBUTE_Hoehe);
}

long CLegSizeCache :: LegendeNachHoehe (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetValueY (lDefault, m_lBaseY, LL_ITEM_Legende, LL_POSITION_Nach, LL_ATTRIBUTE_Hoehe);
}

// MasstabsBox ----------------------------------------------------------------
long CLegSizeCache :: MasstabHoehe (long lDefault, long lBase)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetValueYMM (lDefault, lBase, LL_ITEM_Masstab);
}

long CLegSizeCache :: MasstabVorHoehe (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetValueY (lDefault, m_lBaseY, LL_ITEM_Masstab, LL_POSITION_Vor, LL_ATTRIBUTE_Hoehe);
}

long CLegSizeCache :: MasstabZwischenHoehe (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetValueY (lDefault, m_lBaseY, LL_ITEM_Masstab, LL_POSITION_Zwischen, LL_ATTRIBUTE_Hoehe);
}

long CLegSizeCache :: MasstabNachHoehe (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetValueY (lDefault, m_lBaseY, LL_ITEM_Masstab, LL_POSITION_Nach, LL_ATTRIBUTE_Hoehe);
}

// FontParameter für den LegendenKopftext einlesen ----------------------------
bool CLegSizeCache :: LegendeKopfFont (int &riFam, string &rstrName, int &riSizeY, 
				       bool &rfB, bool &rfI, bool &rfU)
{
	if (!m_fIsPrinter) return false;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);

return m_pPrLayout -> GetFont (m_lBaseY, LL_ITEM_LegendeKopf, riFam, 
			       rstrName, riSizeY, rfB, rfI, rfU);
}

// FontParameter  für einen normalen LegendenEintrag einlesen -----------------
bool CLegSizeCache :: KastenFont (int &riFam, string &rstrName, int &riSizeY, 
				  bool &rfB, bool &rfI, bool &rfU)
{
	if (!m_fIsPrinter) return false;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);

return m_pPrLayout -> GetFont (m_lBaseY, LL_ITEM_Kasten, riFam, 
			       rstrName, riSizeY, rfB, rfI, rfU);
}

bool CLegSizeCache :: MasstabFont (int &riFam, string &rstrName, int &riSizeY, 
				   bool &rfB, bool &rfI, bool &rfU)
{
	if (!m_fIsPrinter) return false;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);

return m_pPrLayout -> GetFont (m_lBaseY, LL_ITEM_Masstab, riFam, 
			       rstrName, riSizeY, rfB, rfI, rfU);
}

// Breiten verschiedener Zwischenräume ----------------------------------------
long CLegSizeCache :: KastenBreite (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetValueX (lDefault, m_lBaseX, 
			LL_ITEM_Signatur, LL_POSITION_None, LL_ATTRIBUTE_Breite);
}

long CLegSizeCache :: KastenVorBreite (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetValueX (lDefault, m_lBaseX, 
			LL_ITEM_Kasten, LL_POSITION_Vor, LL_ATTRIBUTE_Breite);
}

long CLegSizeCache :: KastenZwischenBreite (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetValueX (lDefault, m_lBaseX, 
			LL_ITEM_Kasten, LL_POSITION_Zwischen, LL_ATTRIBUTE_Breite);
}

long CLegSizeCache :: KastenNachBreite (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetValueX (lDefault, m_lBaseX, 
			LL_ITEM_Kasten, LL_POSITION_Nach, LL_ATTRIBUTE_Breite);
}

long CLegSizeCache :: LegendeKopfVorHoehe (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetValueY (lDefault, m_lBaseY, 
			LL_ITEM_LegendeKopf, LL_POSITION_Vor, LL_ATTRIBUTE_Hoehe);
}

long CLegSizeCache :: LegendeKopfNachHoehe (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetValueY (lDefault, m_lBaseY, 
			LL_ITEM_LegendeKopf, LL_POSITION_Nach, LL_ATTRIBUTE_Hoehe);
}

// Höhe eine Leerzeile --------------------------------------------------------
long CLegSizeCache :: LeerzeileHoehe (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetValueY (lDefault, m_lBaseY, 
			LL_ITEM_Leerzeile, LL_POSITION_None, LL_ATTRIBUTE_Hoehe);
}

// Zusätzlicher Platz vor und nach einer Zeile --------------------------------
long CLegSizeCache :: KastenVorHoehe (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetValueY (lDefault, m_lBaseY, 
			LL_ITEM_Kasten, LL_POSITION_Vor, LL_ATTRIBUTE_Hoehe);
}

long CLegSizeCache :: KastenNachHoehe (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetValueY (lDefault, m_lBaseY, 
			LL_ITEM_Kasten, LL_POSITION_Nach, LL_ATTRIBUTE_Hoehe);
}

// Höhe der Signatur relative zur sich ergebenden Fonthöhe --------------------
long CLegSizeCache :: KastenHoehe (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetValueYAbs (lDefault, m_lBaseY, 
			LL_ITEM_Signatur, LL_POSITION_None, LL_ATTRIBUTE_Hoehe);
}

// Beschreibung für MaßstabsBerecih lesen -------------------------------------
bool CLegSizeCache :: MasstabDesc (string &rstr)
{
	if (!m_fIsPrinter) return false;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetString (rstr, LL_ITEM_Masstab, 
				LL_POSITION_None, LL_ATTRIBUTE_Desc);
}

// Höhe der Signatur relative zur sich ergebenden Fonthöhe --------------------
long CLegSizeCache :: MeanderDicke (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetValueYAbs (lDefault, m_lBaseY, 
			LL_ITEM_Meander, LL_POSITION_None, LL_ATTRIBUTE_Breite);
}

// Beschreibung für Logobereich lesen -----------------------------------------
bool CLegSizeCache :: LogoText (string &rstr)
{
	if (!m_fIsPrinter) return false;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	return m_pPrLayout -> GetString (rstr, LL_ITEM_Ueberschrift, 
				LL_POSITION_None, LL_ATTRIBUTE_Desc);
}

// FirmenLogos (bis zu 4 Bereiche am unteren LegendenRand)
long CLegSizeCache :: LogoFeldHoehe (long lDefault, 
				LEGLAYOUT_SUB_ITEM rgPos, int iCnt)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	TX_ASSERT(rgPos >= 0 && rgPos < LL_SUB_ITEM_MaxSubItem);

return m_pPrLayout -> GetValueY (lDefault, m_lBaseY, 
			LEGLAYOUT_ITEM(LL_ITEM_LogoBase+rgPos+1), LL_POSITION_None, 
			LL_ATTRIBUTE_Hoehe, iCnt);
}

long CLegSizeCache :: LogoFeldBreite (long lDefault, 
				LEGLAYOUT_SUB_ITEM rgPos, int iCnt)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	TX_ASSERT(rgPos >= 0 && rgPos < LL_SUB_ITEM_MaxSubItem);

return m_pPrLayout -> GetValueX (lDefault, m_lBaseX, 
			LEGLAYOUT_ITEM(LL_ITEM_LogoBase+rgPos+1), LL_POSITION_None, 
			LL_ATTRIBUTE_Breite, iCnt);
}

bool CLegSizeCache :: LogoFeldFont (int &riFam, string &rstrName, int &riSizeY, 
				    bool &rfB, bool &rfI, bool &rfU, 
				    LEGLAYOUT_SUB_ITEM rgPos, int iCnt)
{
	if (!m_fIsPrinter) return false;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	TX_ASSERT(rgPos >= 0 && rgPos < LL_SUB_ITEM_MaxSubItem);

return m_pPrLayout -> GetFont (m_lBaseY, 
			LEGLAYOUT_ITEM(LL_ITEM_LogoBase+rgPos+1), riFam, 
			rstrName, riSizeY, rfB, rfI, rfU, iCnt);
}

bool CLegSizeCache :: LogoFeldDesc (string &rstr, 
				LEGLAYOUT_SUB_ITEM rgPos, int iCnt)
{
	if (!m_fIsPrinter) return false;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);
	TX_ASSERT(rgPos >= 0 && rgPos < LL_SUB_ITEM_MaxSubItem);

return m_pPrLayout -> GetString (rstr, 
			LEGLAYOUT_ITEM(LL_ITEM_LogoBase+rgPos+1), 
			LL_POSITION_None, LL_ATTRIBUTE_Desc, iCnt);
}

bool CLegSizeCache :: LogoFeldOpaque (int iCnt)
{
	if (!m_fIsPrinter) return false;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);

return (bool)m_pPrLayout -> GetSingleValue ((long)true, 
			LL_ITEM_Logo, LL_POSITION_None, LL_ATTRIBUTE_Opaque, iCnt);
}

// Randmaße gelten für alle FirmenLogoBereiche --------------------------------
long CLegSizeCache :: LogoVorBreite (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);

return m_pPrLayout -> GetValueX (lDefault, m_lBaseX, 
		LL_ITEM_Logo, LL_POSITION_Vor, LL_ATTRIBUTE_Breite);
}

long CLegSizeCache :: LogoZwischenBreite (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);

return m_pPrLayout -> GetValueX (lDefault, m_lBaseX, 
		LL_ITEM_Logo, LL_POSITION_Zwischen, LL_ATTRIBUTE_Breite);
}

long CLegSizeCache :: LogoNachBreite (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);

return m_pPrLayout -> GetValueX (lDefault, m_lBaseX, 
		LL_ITEM_Logo, LL_POSITION_Nach, LL_ATTRIBUTE_Breite);
}

long CLegSizeCache :: LogoVorHoehe (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);

return m_pPrLayout -> GetValueY (lDefault, m_lBaseY, 
		LL_ITEM_Logo, LL_POSITION_Vor, LL_ATTRIBUTE_Hoehe);
}

long CLegSizeCache :: LogoZwischenHoehe (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);

return m_pPrLayout -> GetValueY (lDefault, m_lBaseY, 
		LL_ITEM_Logo, LL_POSITION_Zwischen, LL_ATTRIBUTE_Hoehe);
}

long CLegSizeCache :: LogoNachHoehe (long lDefault)
{
	if (!m_fIsPrinter) return lDefault;	// Bildschirm

	TX_ASSERT(NULL != m_pPrLayout);

return m_pPrLayout -> GetValueY (lDefault, m_lBaseY, 
		LL_ITEM_Logo, LL_POSITION_Nach, LL_ATTRIBUTE_Hoehe);
}

///////////////////////////////////////////////////////////////////////////////
// spezielle, nicht dokumentierte Einträge ------------------------------------
bool CLegSizeCache :: NoTRiASLogo (void)
{
	TX_ASSERT(NULL != m_pPrLayout);

	return m_pPrLayout -> NoTRiASLogo();
}

