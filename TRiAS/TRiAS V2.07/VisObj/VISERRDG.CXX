// Dialogfenster, welches die Fehlerbehandlungsart abfragt --------------------
// File: VISERRDG.CXX

#include "visobjp.hxx"

#include <bmpbox.hxx>

#include "visobj.h"
#include "viserrdg.h"

#include "viserrdg.hxx"

// Konstruktor ----------------------------------------------------------------
#pragma warning (disable: 4355)

CVisErrorDlg :: CVisErrorDlg (pWindow pW, ResourceFile &RF,
			      ResID res, long lIdent, short iVTyp)
	      : DialogWindow (pW, res),
	      	m_RF (RF),
#if !defined(WIN32)
		m_HelpButton (this, IDB_VISERRORHELP),
#endif //!WIN32
		m_DefineButton (this, IDOK),
		m_Message (this, IDT_VISERRORMESSAGE),
		m_VLogo (this, ResID (IDF_VERRORLOGO, &RF), 
			       ResID (IDBMP_VERRORLOGO, &RF))
{
#if !defined(WIN32)
	m_HelpButton.Disable();		// Controls initialisieren
#endif //!WIN32
	m_lIdent = lIdent;
	m_iVTyp = iVTyp;
	if (iVTyp == VTDefault)
		m_DefineButton.Disable();	// VisTyp unbekannt
}

#pragma warning (default: 4355)

bool CVisErrorDlg :: Init (void)
{
// Text aktualisieren
char *lpBuffer = new char [256];
char *lpNewBuffer = new char [256];

	if (lpBuffer == NULL || lpNewBuffer == NULL) 
		return false;
		
// ObjekteTyp als Zeichenkette generieren
char pOTyp[20];
unsigned int uiRes = 0;

	switch (m_iVTyp) {
	case VTPunkt:	uiRes = IDS_PUNKTOBJEKT; break;
	case VTLinie:	uiRes = IDS_LINIENOBJEKT; break;
	case VTFlaeche:	uiRes = IDS_FLAECHENOBJEKT; break;
	case VTText:	uiRes = IDS_TEXTOBJEKT; break;
	case VTDefault:	uiRes = IDS_UNKNOWNOBJECT; break;
	}
	strcpy (pOTyp, ResString (ResID (uiRes, &m_RF), 30));
		
// IdentKurzText besorgen
PBDDATA pbdData;
char pKText[33];

	memset (&pbdData, '\0', sizeof(PBDDATA));
	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = m_lIdent;
	pbdData.pbdKText = pKText;
	pbdData.pbdKTextLen = sizeof(pKText) -1;

	if (DEX_GetPBDData (pbdData) != EC_OKAY) 
		ClassFromIdentX (m_lIdent, pKText);
		
	pKText[32] = '\0';

// Mitteilung im Fenster generieren
	m_Message.GetText (lpBuffer, 255);
	wsprintf (lpNewBuffer, lpBuffer, pOTyp, pKText);
	m_Message.SetText (lpNewBuffer);
	
	DELETE_OBJ (lpBuffer);
	DELETE_OBJ (lpNewBuffer);                     
	
return m_VLogo.Init();
}

void _XTENSN_EXPORT CVisErrorDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		if (GetKeyState (VK_CONTROL) < 0)
		// ControlTaste gedrückt
			EndDlg (2);
		else
			EndDlg (1);		// Definieren
		break;

	case IDCANCEL:
		EndDlg (0);		// ignorieren
		break;

	case IDB_VISERRORHELP:
		break;

	case IDB_IGNOREALWAYS:		// im weiteren ignorieren
		EndDlg (3);	// ok
		break;

	case IDB_IGNOREALLERRORS:
		EndDlg (4);		// im weiteren alles ignorieren
		break;
	}
}
