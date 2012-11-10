// Dialogfenster, welches die Fehlerbehandlungsart abfragt --------------------
// File: VISERRDG.CXX

#include "visobjp.hxx"

#include <bmpbox.hxx>

#include "visobj.h"
#include "obj32/visres32.h"
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
		
// OKS besorgen
char cbOKS[_MAX_PATH];

	ClassFromIdentX (m_lIdent, cbOKS);

// IdentKurzText besorgen
PBDDATA pbdData;
char cbBuffer[_MAX_PATH] = { '\0' };

	memset (&pbdData, '\0', sizeof(PBDDATA));
	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = m_lIdent;
	pbdData.pbdKText = cbBuffer;
	pbdData.pbdKTextLen = sizeof(cbBuffer) -1;

	if (DEX_GetPBDData (pbdData) == EC_OKAY) {
		strcat (cbOKS, ":");
		strcat (cbOKS, cbBuffer);
	}

// wenn mehr als eine Datenquelle geöffnet ist, dann den Namen der zugehörigen 
// in Klammern hintendran hängen
	if (DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
	HPROJECT hPr = DEX_GetObjectsProject(m_lIdent);

		_ASSERTE(NULL != hPr);
		if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {
			strcat (cbOKS, " (");
			strcat (cbOKS, cbBuffer);
			strcat (cbOKS, ")");
		}
	}

// Mitteilung im Fenster generieren
	m_Message.GetText (lpBuffer, 255);
	wsprintf (lpNewBuffer, lpBuffer, pOTyp, cbOKS);
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

//	case IDB_IGNOREALWAYS:		// im weiteren ignorieren
//		EndDlg (3);	// ok
//		break;

	case IDB_AUTOASSIGN:
		EndDlg (3);				// automatisch Fraben zuweisen
		break;

	case IDB_IGNOREALLERRORS:
		EndDlg (4);		// im weiteren alles ignorieren
		break;
	}
}
