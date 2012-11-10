// EditControl fuer die Eingabe von numerischen Werten und Trennzeichen
// File: NUMEDIT.CXX

#include "trias03p.hxx"

#include <ctype.h>
#include <numedit.hxx>

// ----------------------------------------------------------------------------
// Ein Numedit ist geeignet eine IntegerZahl (long) einzulesen ----------------
// ----------------------------------------------------------------------------

// Konstruktoren --------------------------------------------------------------
NumEdit :: NumEdit (pDialogWindow p, ResID r, short iBase) 
	 : ControlWindow (new SingleLineEdit (p, r))
{
	m_NEM = NEM_Test;
	m_iBase = iBase;
}

NumEdit :: NumEdit (pWindow parent, uint id, Point p, Dimension d, short iBase) 
	 : ControlWindow (new SingleLineEdit (parent, id, p, d)) 
{ 
	m_NEM = NEM_Test;
	m_iBase = iBase;
}

// neue EventHandler für NumEdits ---------------------------------------------
void EXPORT03  NumEdit :: KeyDown (KeyEvt e) 
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

void EXPORT03  NumEdit :: FocusChange (FocusChangeEvt e) 
{
	if (!e.gotFocus() && m_NEM == NEM_Test) {	// wenn Focus verloren geht
	// Prüfroutine rufen
	Bool sFlag;
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
		if (LOWORD(GetVersion()) >= 0x030a) {
			SendMessage (((NakedWindow *)GetParent()) -> Handle(), 
				    WM_COMMAND, GetID(), 
				    MAKELONG (Handle (), EN_KILLFOCUS));
		}
	// ------------------------------------------------------------------
	}
	ControlWindow :: FocusChange (e);	// und weiterleiten
}

// Default - Validierungsfunktion ---------------------------------------------
int NumEdit :: PostValidate (int Value) 
{
	return Value;		// keinerlei Validierung
}

// Destruktor -----------------------------------------------------------------
NumEdit :: ~NumEdit (void) 
{
	delete (SingleLineEdit *)GetControl();
}

// diverse Memberfunktionen ---------------------------------------------------
void NumEdit :: GetText (char *Buff, uint Len) 
{
	GetEditControl() -> GetText (Buff, Len);
}

void NumEdit :: SetText (const char *Buff) 
{
	GetEditControl() -> SetText (Buff);
}

void NumEdit :: SetTextLimit (uint nchars) 
{
	GetEditControl() -> SetTextLimit (nchars);
}

int NumEdit :: GetTextLen (void) 
{
	return GetEditControl() -> GetTextLen ();
}

int NumEdit :: GetValue (Bool *pFlag) 
{
BOOL fFlag = FALSE;

	return GetDlgItemInt (((NakedWindow *)GetParent()) -> Handle(),
				GetID(), pFlag ? pFlag : &fFlag, TRUE);
}

void NumEdit :: SetValue (int newVal) 
{
	SetDlgItemInt (((NakedWindow *)GetParent()) -> Handle(), 
			GetID(), newVal, TRUE);
}

NumEdit :: NumEditMode NumEdit :: SetNumEditMode (NumEdit :: NumEditMode newNEM) 
{
NumEditMode oldNEM = m_NEM;

	m_NEM = newNEM;

return oldNEM;
}

void NumEdit :: SetStyle (ulong newStyles) 
{
	GetEditControl() -> SetStyle (newStyles);
}

///////////////////////////////////////////////////////////////////////////////
// #HK970211
bool NumEdit::isModified (void) 
{
	return GetEditControl() -> isModified();
}

void NumEdit::SetModified (bool fModified) 
{
	GetEditControl() -> SetModified(fModified);
}
