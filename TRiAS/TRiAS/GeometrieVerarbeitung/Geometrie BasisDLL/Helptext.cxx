// Control, welches zur Anzeige eines Hilfetextes in Dialogfenstern eingesetzt werden kann
// File: HELPTEXT.CXX
// H. Kaiser


#include "GeometrP.hxx"

#include <stdarg.h>		// va_list, va_start() für 16-Bit-Variante
#include <resstrg.h>	// IDS_ARIAL

#include "helptxtx.hxx"



// Initialisierung, Konstruktor/Destruktor ------------------------------------
CHelpTextX :: CHelpTextX (pDialogWindow pW, ResID resID)
							: FixedText (pW, resID)
{
#if _TRiAS_VER < 0x0300
	m_fFontChanged = FALSE;
	m_pFont = NULL;
#endif // _TRiAS_VER < 0x0300
	m_pBuff = NULL;
}


CHelpTextX :: ~CHelpTextX (void)
{
	DELETE_OBJ (m_pBuff);
#if _TRiAS_VER < 0x0300
	if (m_fFontChanged) {
		m_pFont = ChangeFont (m_pFont);
		DELETE_OBJ (m_pFont);
	}
#endif // _TRiAS_VER < 0x0300
}


bool CHelpTextX :: FInit (void)
{
// Bufferbereich anlegen
	m_pBuff = new char [4*_MAX_PATH];
	if (m_pBuff == NULL)
		return FALSE;

#if _TRiAS_VER < 0x0300
	if (IsWin40()) return true;

// Font für BeschreibungsBox generieren
ResString rsArial (IDS_ARIAL, 20);

#if !defined(_TRIAS_OLDIMPLEMENTATION2)
	m_pFont = new CVFont (Swiss, Dimension (0, -11), rsArial);
#else
	m_pFont = new Font (Swiss, Dimension (0, -11), rsArial);
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
	if (m_pFont) {
		m_pFont = ChangeFont (m_pFont);
		m_fFontChanged = TRUE;
	}
#endif // _TRiAS_VER < 0x0300
	
	return TRUE;
}


CHelpTextX * CHelpTextX :: CreateInstance (pDialogWindow pW, ResID resID)
{
CHelpTextX *pHT = new CHelpTextX (pW, resID);

	if (pHT == NULL || !pHT -> FInit()) {
		DELETE_OBJ (pHT);
		return NULL;
	}
	
return pHT;
}


// Eigentliche Funktionalität -------------------------------------------------
// Setzt den BeschreibungsText entsprechend dem ResourceText ------------------
void CHelpTextX :: SetHelpText (ResID uiRes)
{
ResString rsT (uiRes, _MAX_PATH);

	SetText (rsT.Addr());
}


void CHelpTextX :: SetHelpTextV (ResID uiRes, ...)
{
	if (m_pBuff == NULL) {
		SetHelpText (uiRes);
		return;
	}
	
ResString rsT (uiRes, _MAX_PATH);
va_list vaArgs;

	va_start (vaArgs, uiRes);
	wvsprintf (m_pBuff, rsT.Addr(), vaArgs);	
	va_end (vaArgs);
	
	SetText (m_pBuff);
}


