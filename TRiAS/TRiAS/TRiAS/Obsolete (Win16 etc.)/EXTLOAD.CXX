// Memberfunktionen fuer die beiden Erweiterungs-DLL-Dialogfenster
// File: EXTLOAD.CXX

#include "triaspre.hxx"

#include "extload.h"
#include "extload.hxx"

// Konstruktoren/Destruktoren -------------------------------------------------
#pragma warning (disable:4355)

ExtLoadDLLDlg *ExtLoadDLLDlg :: CreateInstance (pWindow pW, ExtensionList &EL)
{
ExtLoadDLLDlg *pDlg = new ExtLoadDLLDlg (pW, EL);

	if (pDlg == NULL || !pDlg -> FInit()) {
		DELETE (pDlg);
		return NULL;
	}
	
return pDlg;
}


ExtLoadDLLDlg :: ExtLoadDLLDlg (pWindow pW, ExtensionList &EL)
	       : DialogWindow (pW, LOADLISTDLL),
		 OKButton (this, IDOK),
		 CancelButton (this, IDCANCEL),
		 HelpButton (this, IDB_LOADHELP),
		 LoadList (this, IDL_LOADLISTDLL),
		 PreLoad (this, IDCB_PRELOAD),
		 m_rEL (EL)
{
// Variablen initialisieren
	m_pExtName = NULL;
	m_pDLLName = NULL;
	m_pBuffer = NULL;
	m_fUnLoadable = false;

	m_rgFlags = (EXTENSIONFLAG)0;

// Controls initialisieren
	PreLoad.SetChecked (false);
	OKButton.Disable();
	HelpButton.Disable();
}


bool ExtLoadDLLDlg :: FInit (void)
{
// internen Buffer anlegen
	m_pBuffer = new char [_MAX_PATH];
	if (m_pBuffer == NULL) return false;

// alle noch nicht geladenen Erweiterungen nachladen
CTable r(m_rEL);

	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && !l -> isLoaded() && l -> isGlobal())
			LoadList.AddString (l -> ExtName().c_str());
	}
	LoadList.SetCaretIndex (-1);
	LoadList.SetFocus();

return true;
}

#pragma warning (default:4355)

ExtLoadDLLDlg :: ~ExtLoadDLLDlg (void)
{
	DELETE (m_pExtName);
	DELETE (m_pDLLName);
	DELETE (m_pBuffer);
}

void ExtLoadDLLDlg :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int) e.GetControlID()) {
	case IDOK:
		if (m_pExtName) {
			SetPreLoadStatus ();
			EndDlg (1);	// ok: raus
		}
		break;

	case IDCANCEL:
		EndDlg (0);	// abbrechen: raus
		break;

	case IDB_LOADHELP:
		break;

	case IDCB_PRELOAD:
		break;
	}
}

void ExtLoadDLLDlg :: ListBoxSel (ControlEvt)
{
short iIndex = LoadList.GetCaretIndex();

	if (iIndex != -1) {
	// Namen der aktuellen Extenson speichern
		GetNames (iIndex);

	// PreLoadStatus setzen
		PreLoad.SetChecked (GetPreLoadStatus());

	// OK-Knopf freigeben
		if (LoadList.GetNoSelected()) 
			OKButton.Enable();
		else 
			OKButton.Disable();
	}
}

bool ExtLoadDLLDlg :: GetNames (short iIndex)
{
	if (iIndex == -1) return false;
	
// Bezeichner der DLL holen
	DELETE (m_pExtName);
	DELETE (m_pDLLName);

	LoadList.GetString (m_pBuffer, iIndex, _MAX_PATH);
	m_pExtName = StrDup (m_pBuffer, RC_LoadListSel);	// Bezeichner holen
	m_pDLLName = m_rEL.RetrieveDLLName (m_pExtName);	// Namen der DLL holen
	m_fUnLoadable = m_rEL.GetFlags(m_pDLLName) & EF_UnLoadable;
		
	m_rgFlags = m_rEL.GetFlags(m_pDLLName);

return true;
}

void ExtLoadDLLDlg :: ListBoxClk (ControlEvt)
{
	if (m_pExtName) {
		SetPreLoadStatus ();
		EndDlg (1);	// ok: raus
	}
}

bool ExtLoadDLLDlg :: GetFirstExtName (void) 
{
	return GetNames (LoadList.GetFirstSelected());
}

bool ExtLoadDLLDlg :: GetNextExtName (void) 
{
	return GetNames (LoadList.GetNextSelected());
}


void ExtLoadDLLDlg :: SetPreLoadStatus (void)
{
/* 
ResString ExtSection (IDS_EXTENSION, 20);

	if (m_pExtName) {
	ProFile PF (ResString (IDS_PROFILE, 20));

		PF.SetPreLoad (m_pExtName, PreLoad.isChecked());
	}
*/
}

bool ExtLoadDLLDlg :: GetPreLoadStatus (void) 
{
/*
ResString ExtSection (IDS_EXTENSION, 20);

	if (m_pExtName) {
	ProFile PF (ResString (IDS_PROFILE, 20));

		return PF.GetPreLoad (m_pExtName);
	}
*/
return false;
}


// Dialogfenster zum Beseitigen einer Erweiterung aus dem Menu ----------------
ExtUnLoadDLLDlg *ExtUnLoadDLLDlg :: CreateInstance (pWindow pW, ExtensionList &EL)
{
ExtUnLoadDLLDlg *pDlg = new ExtUnLoadDLLDlg (pW, EL);

	if (pDlg == NULL || !pDlg -> FInit()) {
		DELETE (pDlg);
		return NULL;
	}
	
return pDlg;
}


#pragma warning (disable:4355)

ExtUnLoadDLLDlg :: ExtUnLoadDLLDlg (pWindow pW, ExtensionList &EL)
	         : DialogWindow (pW, UNLOADLISTDLL),
		   OKButton (this, IDOK),
		   CancelButton (this, IDCANCEL),
		   HelpButton (this, IDB_UNLOADHELP),
		   UnLoadList (this, IDL_UNLOADLISTDLL),
		   m_rEL (EL)
{
// Variablen initialisieren
	m_pExtName = NULL;
	m_pDLLName = NULL;
	m_pBuffer = NULL;

	OKButton.Disable();
	HelpButton.Disable();
}

#pragma warning (default:4355)

ExtUnLoadDLLDlg :: ~ExtUnLoadDLLDlg (void)
{
	DELETE (m_pExtName);
	DELETE (m_pDLLName);
	DELETE (m_pBuffer);
}


bool ExtUnLoadDLLDlg :: FInit (void) 
{
// Buffer anlegen
	m_pBuffer = new char [_MAX_PATH];
	if (m_pBuffer == NULL) return false;
	
// ListBox initialisieren -- alle geladenen Erweiterungen anzeigen
CTable r(m_rEL);
                                           
	for (r.First(); r.Valid(); r.Next()) {
	ExtensionLock l(r);

		if (l && l -> isLoaded() && l -> isGlobal() && (l -> GetFlags() & EF_UnLoadable))
			UnLoadList.AddString (l -> ExtName().c_str());
	}
	UnLoadList.SetCaretIndex (-1);
	UnLoadList.SetFocus();

return true;
}

void ExtUnLoadDLLDlg :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int) e.GetControlID()) {
	case IDOK:
		if (m_pExtName) 
			EndDlg (1);	// ok: raus
		break;

	case IDCANCEL:
		EndDlg (0);	// abbrechen: raus
		break;

	case IDB_LOADHELP:
		break;
	}
}

void ExtUnLoadDLLDlg :: ListBoxSel (ControlEvt)
{
short iIndex = UnLoadList.GetCaretIndex();

	if (iIndex != -1) {
	// Bezeichner der DLL holen
		GetNames (iIndex);
		
		if (UnLoadList.GetNoSelected()) 
			OKButton.Enable();
		else 
			OKButton.Disable();
	}
}

bool ExtUnLoadDLLDlg :: GetNames (short iIndex)
{
	if (iIndex == -1) return false;
	
// Bezeichner der DLL holen
	DELETE (m_pExtName);
	DELETE (m_pDLLName);

	UnLoadList.GetString (m_pBuffer, iIndex, _MAX_PATH);
	m_pExtName = StrDup (m_pBuffer, RC_UnLoadListSel);	// Bezeichner holen
	m_pDLLName = m_rEL.RetrieveDLLName (m_pExtName);	// Namen der DLL holen

return true;
}

bool ExtUnLoadDLLDlg :: GetFirstExtName (void) 
{
	return GetNames (UnLoadList.GetFirstSelected());
}

bool ExtUnLoadDLLDlg :: GetNextExtName (void) 
{
	return GetNames (UnLoadList.GetNextSelected());
}


void ExtUnLoadDLLDlg :: ListBoxClk (ControlEvt)
{
	if (m_pExtName)
		EndDlg(1);
}
