// EditControl fuer die Eingabe von numerischen Werten und Trennzeichen

//#include "xtensnp.hxx"
#include "GeometrP.hxx"

#include <ctype.h>
#include <numeditx.hxx>

// ----------------------------------------------------------------------------
// Ein Numedit ist geeignet eine IntegerZahl (long) einzulesen ----------------
// ----------------------------------------------------------------------------

// Konstruktoren --------------------------------------------------------------
NumEditX :: NumEditX (pDialogWindow p, ResID r, short iBase) 
	 : ControlWindow (new SingleLineEdit (p, r))
{
	m_NEM = NEM_Test;
	m_iBase = iBase;
}

NumEditX :: NumEditX (pWindow parent, uint id, Point p, Dimension d, short iBase) 
	 : ControlWindow (new SingleLineEdit (parent, id, p, d)) 
{ 
	m_NEM = NEM_Test;
	m_iBase = iBase;
}

// neue EventHandler für NumEditXs ---------------------------------------------
void _XTENSN_EXPORT NumEditX :: KeyDown (KeyEvt e) 
{
char inChar = e.ASCIIChar();

	if (inChar == '\0' || iscntrl(inChar) ||	// Steuerzeichen
	    inChar == '-'  ||				// unäres Minus
	    ( (m_iBase == 10) ? isdigit(inChar) : isxdigit(inChar) )) 
	    // numerisches Zeichen
	{
	// Event weiterleiten
		Default ((Event &)e); 
	} else
		MessageBeep (0);	// FehlerBeep
}

class NakedWindow : public Window {
public:
	HWND Handle (Service s = NULL) { return Window :: Handle (s); }
};

void _XTENSN_EXPORT NumEditX :: FocusChange (FocusChangeEvt e) 
{
	if (!e.gotFocus() && m_NEM == NEM_Test) {	// wenn Focus verloren geht
	// Prüfroutine rufen
	BOOL sFlag;
	int oldVal = GetValue (&sFlag);	// eingegebenen Wert holen

		if (sFlag) {
		// kein Fehler
		int newVal = PostValidate (oldVal);	// Wert korrigieren

			if (newVal != oldVal) {
				SetValue (newVal);	// evtl. neuen Wert setzen
				MessageBeep (0);	// piepsen
			}
		} else {
			SetValue (0);		// fehlerhafte Eingabe 
			MessageBeep (0);
		}

	// Workaround der Win31-Hacke keinen EN_KILLFOCUS Event zu generieren
	// ------------------------------------------------------------------
#if !defined(WIN32)
		if (LOWORD(GetVersion()) >= 0x030a) {
			SendMessage (((NakedWindow *)GetParent()) -> Handle(), 
				    WM_COMMAND, GetID(), 
				    MAKELONG (Handle (), EN_KILLFOCUS));
		}
#else
		SendMessage (((NakedWindow *)GetParent()) -> Handle(), 
				WM_COMMAND, MAKELONG (GetID(), EN_KILLFOCUS),
				(LPARAM)Handle());
#endif
	// ------------------------------------------------------------------
	}
	ControlWindow :: FocusChange (e);	// und weiterleiten
}

// Default - Validierungsfunktion ---------------------------------------------
int NumEditX :: PostValidate (int Value) 
{
	return Value;		// keinerlei Validierung
}

// Destruktor -----------------------------------------------------------------
NumEditX :: ~NumEditX (void) 
{
	delete (SingleLineEdit *)GetControl();
}

// diverse Memberfunktionen ---------------------------------------------------
void NumEditX :: GetText (char *Buff, uint Len) 
{
	GetEditControl() -> GetText (Buff, Len);
}

void NumEditX :: SetText (const char *Buff) 
{
	GetEditControl() -> SetText (Buff);
}

void NumEditX :: SetTextLimit (uint nchars) 
{
	GetEditControl() -> SetTextLimit (nchars);
}

int NumEditX :: GetTextLen (void) 
{
	return GetEditControl() -> GetTextLen ();
}

int NumEditX :: GetValue (BOOL *pFlag) 
{
	return GetDlgItemInt (((NakedWindow *)GetParent()) -> Handle(),
				GetID(), pFlag, true);
}

void NumEditX :: SetValue (int newVal) 
{
	SetDlgItemInt (((NakedWindow *)GetParent()) -> Handle(), 
			GetID(), newVal, true);
}

NumEditX :: NumEditMode NumEditX :: SetNumEditMode (NumEditX :: NumEditMode newNEM) 
{
NumEditMode oldNEM = m_NEM;

	m_NEM = newNEM;

return oldNEM;
}

void NumEditX :: SetStyle (ulong newStyles) 
{
	GetEditControl() -> SetStyle (newStyles);
}
