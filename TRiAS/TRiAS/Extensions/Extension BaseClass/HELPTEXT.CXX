// Control, welches zur Anzeige eines Hilfetextes in Dialogfenstern 
// eingesetzt werden kann
// File: HELPTEXT.HXX

#include "xtensnp.hxx"

#include <resstrg.h>
#include <stdarg.h>
#include <helptxtx.hxx>

// Initialisierung, Konstruktor/Destruktor ------------------------------------
CHelpTextX :: CHelpTextX (pDialogWindow pW, ResID resID)
	   : FixedText (pW, resID)
{
#if defined(_FORCE_LEGACY_CODE)
	m_fFontChanged = false;
	m_pFont = NULL;
#endif // _FORCE_LEGACY_CODE
	m_pBuff = NULL;
}


CHelpTextX :: ~CHelpTextX (void)
{
	DELETE_OBJ (m_pBuff);
#if defined(_FORCE_LEGACY_CODE)
	if (m_fFontChanged) {
		m_pFont = ChangeFont (m_pFont);
		DELETE_OBJ (m_pFont);
	}
#endif // _FORCE_LEGACY_CODE
}


bool CHelpTextX :: FInit (void)
{
// Bufferbereich anlegen
	m_pBuff = new char [4*_MAX_PATH];
	if (m_pBuff == NULL)
		return false;

#if defined(_FORCE_LEGACY_CODE)
#if defined(WIN32)
	if (IsWin40()) return true;
#endif // WIN32

// Font für BeschreibungsBox generieren
ResString rsArial (IDS_ARIAL, 20);

#if !defined(_TRIAS_OLDIMPLEMENTATION2)
	m_pFont = new CVFont (Swiss, Dimension (0, -12), rsArial);
#else
	m_pFont = new Font (Swiss, Dimension (0, -12), rsArial);
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
	if (m_pFont) {
		m_pFont = ChangeFont (m_pFont);
		m_fFontChanged = true;
	}
#endif // _FORCE_LEGACY_CODE

	return true;
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


