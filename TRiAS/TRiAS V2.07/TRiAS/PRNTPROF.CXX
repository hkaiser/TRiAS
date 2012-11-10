// Behandlung der Eintraege in der Projekt-INI fuer das Druck-Layout ----------
// File: PRNTPROF.CXX

#include "triaspre.hxx"

#include "triasres.h"
#include "prntprof.hxx"


// Konstruktor/Destruktor -----------------------------------------------------
PrintProfile :: PrintProfile (char *pUser)
	      : ProFile (m_pProfPath = GetProjectProfile())
{
ResString rsSection (IDS_PRINTLAYOUT, 30);

	m_pRS = new char [_MAX_PATH];
	if (m_pRS) 
		wsprintf (m_pRS, rsSection, pUser);
	m_pInBuff = new char [_MAX_PATH];
}


bool PrintProfile :: IsValid (void)
{
	return m_pRS != NULL && m_pInBuff != NULL;
}


PrintProfile :: ~PrintProfile (void)
{
	DELETE (m_pRS);
	DELETE (m_pInBuff);
	DELETE (m_pProfPath);
}


char *GetProjectProfile (void)
{
// aktuelles Projektverzeichnis besorgen
char *pLocDir = new char [_MAX_PATH];

	if (DEX_GetActiveProject (pLocDir) == NULL) {
	// noch kein Projekt eröffnet

		DELETE (pLocDir);
	}

return pLocDir;
}

// SupportFunktionen für den internen Gebrauch --------------------------------
short PrintProfile :: GetInt (unsigned int resID, short iDefault)
{
ResString Entry (resID, 30);
short iVal = GetPrivateProfileInt (m_pRS, Entry.Addr(), iDefault, _FullName);
			     
	if (iVal == iDefault) {		
	// Sektion mit NutzerNamen existiert nicht
	char *cptr; 
	
		if ((cptr = strchr (m_pRS, ':')) != NULL) {
			*cptr = '\0';		// User ausblenden
		
		short iRes = GetPrivateProfileInt (m_pRS, Entry.Addr(), 
						    iDefault, _FullName);
			*cptr = ':';
			return iRes;
		}
	}

return iVal;
}


void PrintProfile :: SetInt (unsigned int resID, short iVal)
{
ResString Entry (resID, 30);

	wsprintf (m_pInBuff, "%d", iVal);
	WritePrivateProfileString (m_pRS, Entry.Addr(), m_pInBuff, _FullName);
}


// konkrete Memberfunktionen -------------------------------------------------

// PapierRandEinstellung -----------------------------------------------------
bool PrintProfile :: GetRand (Rectangle &Rc)
{
ResString Rand (IDS_PRINTLAYOUTRAND, 30);

	GetPrivateProfileString (m_pRS, Rand.Addr(), "", 
				 m_pInBuff, _MAX_PATH, _FullName);
	if (*m_pInBuff == '\0') return false;
		
// Eintrag gegeben
	Rc.Left() = atoi (strtok (m_pInBuff, ","));
	Rc.Top() = atoi (strtok (NULL, ","));
	Rc.Right() = atoi (strtok (NULL, ","));
	Rc.Bottom() = atoi (strtok (NULL, ","));
	
return true;
}
            
void PrintProfile :: SetRand (Rectangle &Rc)
{
ResString Rand (IDS_PRINTLAYOUTRAND, 30);

	wsprintf (m_pInBuff, "%d,%d,%d,%d", 
		  Rc.Left(), Rc.Top(), Rc.Right(), Rc.Bottom());
	WritePrivateProfileString (m_pRS, Rand.Addr(), m_pInBuff, _FullName);
}


// Rahmen zeichnen/nicht zeichnen/RahmenTyp ----------------------------------
short PrintProfile :: GetRahmen (void) { return GetInt (IDS_PRINTLAYOUTRAHMEN); }
void PrintProfile :: SetRahmen (short iTyp) { SetInt (IDS_PRINTLAYOUTRAHMEN, iTyp); }

// Legende anzeigen/nicht anzeigen -------------------------------------------
bool PrintProfile :: GetLegende (void) { return (bool)GetInt (IDS_PRINTLAYOUTLEGENDE); }
void PrintProfile :: SetLegende (bool fPaint) { SetInt (IDS_PRINTLAYOUTLEGENDE, (short)fPaint); }
bool PrintProfile :: GetLegendOnly (void) { return (bool)GetInt (IDS_PRINTLAYOUTLEGENDEONLY); }
void PrintProfile :: SetLegendOnly (bool fPaint) { SetInt (IDS_PRINTLAYOUTLEGENDEONLY, (short)fPaint); }

// Maßstab ausgeben/nicht ausgeben -------------------------------------------
bool PrintProfile :: GetMasstab (void) { return (bool)GetInt (IDS_PRINTLAYOUTMASSTAB); }
void PrintProfile :: SetMasstab (bool fPaint) { SetInt (IDS_PRINTLAYOUTMASSTAB, (short)fPaint); }


// Überschrift ausgeben/ÜberschriftsText -------------------------------------
bool PrintProfile :: GetHeadLine (char *pBuffer, short iLen)
{
	if (pBuffer == NULL || !GetInt (IDS_PRINTLAYOUTHEADLINE)) return false;
	
ResString HeadLine (IDS_PRINTLAYOUTHEADLINE, 30);
char *cptr = NULL;

	GetPrivateProfileString (m_pRS, HeadLine.Addr(), "", 
				 m_pInBuff, _MAX_PATH, _FullName);
	if (*m_pInBuff == '\0') {
		*pBuffer = '\0';
		return false;
	}
	
	if ((cptr = strchr (m_pInBuff, ',')) == NULL)
		cptr = m_pInBuff-1;

	strncpy (pBuffer, cptr+1, iLen-1);
	pBuffer[iLen-1] = '\0';

return true;
}


void PrintProfile :: SetHeadLine (bool fPaint, char *pBuffer)
{
ResString HeadLine (IDS_PRINTLAYOUTHEADLINE, 30);

	wsprintf (m_pInBuff, "%d,%s", fPaint, pBuffer);
	WritePrivateProfileString (m_pRS, HeadLine.Addr(),
				   m_pInBuff, _FullName);
}


short PrintProfile :: GetAusschnitt (long &Li, long &Ob, long &Re, long &Un, long &M)
{
ResString Ausschnitt (IDS_PRINTLAYOUTAUSSCHNITT, 30);

	GetPrivateProfileString (m_pRS, Ausschnitt.Addr(), "", 
				 m_pInBuff, _MAX_PATH, _FullName);
	if (*m_pInBuff == '\0') return 0;
		
// Eintrag gegeben
short iTyp = atoi (strtok (m_pInBuff, ","));

	switch (iTyp) {
	case 1:		// LiOb-ReUn 
		Li = atol (strtok (NULL, ","));
		Ob = atol (strtok (NULL, ","));
		Re = atol (strtok (NULL, ","));
		Un = atol (strtok (NULL, ","));
		M = 0;
		break;
		
	case 2:		// LiOb-Masstab
		Li = atol (strtok (NULL, ","));
		Ob = atol (strtok (NULL, ","));
		M = atol (strtok (NULL, ","));
		break;
		
	default:
		return 0;	// keine Überschrift
	}
	
return iTyp;
}


void PrintProfile :: SetAusschnitt (long Li, long Ob, long Re, long Un)
{
ResString Ausschnitt (IDS_PRINTLAYOUTAUSSCHNITT, 30);

	wsprintf (m_pInBuff, "1,%ld,%ld,%ld,%ld", Li, Ob, Re, Un);
	WritePrivateProfileString (m_pRS, Ausschnitt.Addr(),
				   m_pInBuff, _FullName);
}


void PrintProfile :: SetAusschnitt (long Li, long Ob, long M)
{
ResString Ausschnitt (IDS_PRINTLAYOUTAUSSCHNITT, 30);

	wsprintf (m_pInBuff, "2,%ld,%ld,%ld", Li, Ob, M);
	WritePrivateProfileString (m_pRS, Ausschnitt.Addr(),
				   m_pInBuff, _FullName);
}


