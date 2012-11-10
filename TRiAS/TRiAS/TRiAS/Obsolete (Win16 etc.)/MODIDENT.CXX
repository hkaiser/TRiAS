// Umklassifizieren aller Objekte verschiedener Objektklassen -----------------
// File: MODIDENT.CXX

#include "triaspre.hxx"
				
#include <selidlst.hxx>
#include <helptext.hxx>

#include "modident.h"
#include "modident.hxx"

#include "triasres.h"

#if !defined(WIN32)
extern bool IsWin40 (void);
#endif

// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable: 4355)

CModifyIdentDlg :: CModifyIdentDlg (pWindow pW)
		 : DialogWindow (pW, MODIFYIDENTSDLG),
		   m_pbOK (this, IDOK),
		   m_pbCancel (this, IDCANCEL),
#if !defined(WIN32)
		   m_pbHelp (this, IDHELP),
#endif // WIN32
		   m_cbNewId (this, IDCB_MODIDNEWIDENT)
{
	m_pIdents = NULL;
	m_pBuff = NULL;
	m_pHelpText = NULL;	
	m_iIdBase = DEX_GetIdBase();
	
#if !defined(WIN32)
	m_pbHelp.Disable();
#endif
	m_pbOK.Disable();
}

#pragma warning (default: 4355)

CModifyIdentDlg :: ~CModifyIdentDlg (void)
{
	DELETE (m_pIdents);
	DELETE (m_pBuff);
	DELETE (m_pHelpText);
}

CModifyIdentDlg *CModifyIdentDlg :: CreateInstance (pWindow pW)
{
CEierUhr Wait (pW);
CModifyIdentDlg *pDlg = new CModifyIdentDlg (pW);

	if (pDlg == NULL || !pDlg -> FInit()) {
		DELETE (pDlg);
		return NULL;
	}
	
return pDlg;
}

BOOL CModifyIdentDlg :: FInit (void)
{
// Buffer anlegen
	m_pBuff = new char [_MAX_PATH];
	if (m_pBuff == NULL) return FALSE;

	m_pHelpText = CHelpText :: CreateInstance (this, IDT_MODIDDESCRIPTION, !IsWin40());
	if (m_pHelpText == NULL)
		return FALSE;
	
// IdentifikatorListBox füllen
	m_pIdents = CSelIdentList :: CreateInstance (this, IDL_MODIFYIDENTSLIST);
	if (m_pIdents == NULL) return FALSE;
	
// Idents der PBD lesen und in Combobox anzeigen
	if (!FillNewIdents (m_cbNewId, m_pHelpText, m_iIdBase, m_pBuff)) 
		return FALSE;
	
return TRUE;
}

// EventHandler ---------------------------------------------------------------
void CModifyIdentDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		m_lNewIdent = GetIdent (&m_cbNewId, TRUE);
		if (m_lNewIdent != -1L)
			DEX_SetLastIdent (m_lNewIdent);
		EndDlg (1);
		break;
		
	case IDCANCEL:
		EndDlg (0);	// abbrechen
		break;
		
	case IDHELP:
		break;
	}
}


void CModifyIdentDlg :: ListBoxSel (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDL_MODIFYIDENTSLIST:
		m_pHelpText -> SetHelpText (IDS_MODIFYSELECTEDIDENTS);
		AdjustOK (FALSE);
		break;
	
	case IDCB_MODIDNEWIDENT:
		{
		short iIndex = m_cbNewId.GetCurrentIndex();
		
			if (iIndex != -1) {
				m_cbNewId.GetString (m_pBuff, iIndex, _MAX_PATH);
				m_cbNewId.SetText (m_pBuff);		// damit AdjustOK richtig geht
				m_pHelpText -> SetHelpTextV (IDS_NEWIDENT, strchr (m_pBuff, ':') +1);
			}
		}
		AdjustOK();
		break;
	}
}


void CModifyIdentDlg :: EditChange (ControlEvt)
{
	AdjustOK (FALSE);
}


// Überprüfen, wenn ComboBoxen Focus erhalten haben ---------------------------
void CModifyIdentDlg :: EditFocusChg (EditFocusChgEvt e)
{
	if (!((ComboFocusChgEvt &)e).gotFocus()) {
	// Focus abgegeben, Eingabe überprüfen
		if ((uint)e.GetControlID() == IDCB_MODIDNEWIDENT) {
			if (m_cbNewId.GetTextLen() > 0) {
			// Eingabe auf Gültigkeit testen
				m_cbNewId.GetText (m_pBuff, _MAX_PATH);
				for (char *pT = m_pBuff; *pT; pT++) {
					if ((m_iIdBase == 10) ? isdigit(*pT) : isxdigit(*pT)) 
						continue;
					if (*pT == ':') break;	// normale Eingabe

				// wenn Cancel aktiv ist, dann keine Fehlermeldung
					if (m_pbCancel.Handle() == GetFocus())
						return;
						
				// Fehlerhafte Eingabe
					m_pHelpText -> SetHelpText (IDS_BADIDENT);
					MessageBeep (0);
					m_cbNewId.SetFocus();
					return;
				}			
			
			// wenn Eingabe ok ist, dann versuchen Eintrag zu matchen
			long lIdent = strtoul (m_pBuff, NULL, m_iIdBase);
			
				if (m_iIdBase == 10) 
					wsprintf (m_pBuff, "%08ld", lIdent);
				else
					wsprintf (m_pBuff, "%08lx", lIdent);

			short iIndex = m_cbNewId.FindString (m_pBuff);
			
				if (iIndex == -1)
					m_pHelpText -> SetHelpTextV (IDS_NEWIDENTKEY, m_pBuff);
				else {
					m_cbNewId.ChangeCurrentIndex (iIndex);
					m_cbNewId.GetString (m_pBuff, iIndex, _MAX_PATH);
					m_pHelpText -> SetHelpTextV (IDS_NEWIDENT, strchr (m_pBuff, ':') +1);
				}
			}
		}
		AdjustOK (FALSE);
		return;
	}
	
// Focus erhalten, Hilfetext setzen
	switch ((uint)e.GetControlID()) {
	case IDCB_MODIDNEWIDENT:
		{
		short iIndex = m_cbNewId.GetCurrentIndex();
		
			if (iIndex != -1) {
				m_cbNewId.GetString (m_pBuff, iIndex, _MAX_PATH);
				m_pHelpText -> SetHelpTextV (IDS_NEWIDENT, strchr (m_pBuff, ':') +1);
			} 
		}
		break;
	}
	AdjustOK();
}



// HilfsRoutinen --------------------------------------------------------------
void CModifyIdentDlg :: AdjustOK (BOOL fIndex)
{
// neuer Ident gegeben ?
short iIndex = m_cbNewId.GetCurrentIndex();

	if (m_cbNewId.GetTextLen() == 0 || (fIndex && iIndex == -1))
	{
		m_pbOK.Disable();
		return;
	}

	if (!m_pIdents || m_pIdents -> GetNoSelected() == 0)
		m_pbOK.Disable();
	else
		m_pbOK.Enable();
}


// AbfrageRoutinen ------------------------------------------------------------
BOOL CModifyIdentDlg :: GetFirstIdent (long &rlIdent, short &riOTyp)
{
	if (m_pIdents) 
		return m_pIdents -> GetFirstIdent (rlIdent, riOTyp);
		
return FALSE;
}


BOOL CModifyIdentDlg :: GetNextIdent (long &rlIdent, short &riOTyp)
{
	if (m_pIdents) 
		return m_pIdents -> GetNextIdent (rlIdent, riOTyp);
		
return FALSE;
}


long CModifyIdentDlg :: GetIdent (ComboBox *pCB, BOOL fEdit)
{
short iIndex = pCB -> GetCurrentIndex();

	if (iIndex != -1) {
		pCB -> GetString (m_pBuff, iIndex, _MAX_PATH);
		return strtoul (m_pBuff, NULL, m_iIdBase);
	} else if (fEdit) {
		pCB -> GetText (m_pBuff, _MAX_PATH);
		return strtoul (m_pBuff, NULL, m_iIdBase);
	}
	
return -1L;
}


