// Memberroutinen für PasswordDialog ------------------------------------------
// File: PWDIALOG.CXX

#include "triaspre.hxx"

#include "pwdialog.hxx"


// Konstruktor ---------------------------------------------------------------
#pragma warning (disable: 4355)

PassWordDlg :: PassWordDlg (pWindow pW, uint Res) 
	     : DialogWindow (pW, PWDIALOG),
	       OKButton (this, IDB_PWOK),
	       SLE_PassWord (this, IDE_PASSWORD),
	       PwdPrompt (this, ResID (Res))
{
	memset (_PassWord, '\0', PASSWDLEN+1);		// Password löschen
	SLE_PassWord.SetTextLimit (PASSWDLEN);		// Zeichen begrenzen
}


#pragma warning (default: 4355)

// Memberfunktionen -----------------------------------------------------------
void PassWordDlg :: ButtonClick (ControlEvt e) 
{
	switch ((uint)e.GetControlID()) {
	case IDB_PWOK:		// OK - PassWord eingegeben
		SLE_PassWord.GetText (_PassWord, PASSWDLEN);
		EndDlg (1);
		break;
	}
}

