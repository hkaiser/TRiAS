// Memberfunktionen fuer ModID - Dialog ---------------------------------------
// File: NEWID.CXX

#include "triaspre.hxx"
		
#include <helptext.hxx>

#include "newid.h"
#include "newid.hxx"

#if !defined(WIN16)
const char IDENT_DELIMITER_CHAR = ' ';
#else
const char IDENT_DELIMITER_CHAR = ':';
#endif // WIN16

// globale Daten
extern HelpDisplay *IrisHD;

#if defined(WIN16)
extern bool IsWin40 (void);
#endif

// Konstruktor ---------------------------------------------------------------
#pragma warning (disable: 4355)

CNewIdentDlg :: CNewIdentDlg (pWindow pW)
	      : DialogWindow (pW, NEWIDENT),
	        m_pbOK (this, IDOK),
	        m_pbCancel (this, IDCANCEL),
#if defined(WIN16)
		m_pbHelp (this, IDB_NEWIDHELP),
#endif // WIN16
		m_bxOldId (this, IDBX_OLDIDENT),
		m_cbOldId (this, IDCB_OLDIDENT),
		m_cbNewId (this, IDCB_NEWIDENT)
{
	m_pOutBuff = NULL;
	m_iIdBase = DEX_GetIdBase();
	m_pHelpText = NULL;
	m_lLastIdent = -1L;
	
// Controls initialisieren
	m_bxOldId.SetChecked (FALSE);
	m_cbOldId.Disable();
}

#pragma warning (default: 4355)

CNewIdentDlg :: ~CNewIdentDlg (void)
{
	DELETE (m_pOutBuff);
	DELETE (m_pHelpText);
}


BOOL CNewIdentDlg :: FInit (long lOldIdent)
{
// ZeichenKettenBuffer anlegen
	m_pOutBuff = new char [_MAX_PATH];
	if (m_pOutBuff == NULL)
		return FALSE;

	m_pHelpText = CHelpText :: CreateInstance (this, IDT_DESCRIPTION, !IsWin40());
	if (m_pHelpText == NULL)
		return FALSE;
	
// ComboBoxen mit Idents füllen
	if (!FillOldIdents (lOldIdent) || 
	    !FillNewIdents(m_cbNewId, m_pHelpText, m_iIdBase, m_pOutBuff)) 
		return FALSE;
	
return TRUE;
}


CNewIdentDlg *CNewIdentDlg :: CreateInstance (pWindow pW, long lOldIdent)
{
CEierUhr Wait (pW);
CNewIdentDlg *pNIDlg = new CNewIdentDlg (pW);

	if (pNIDlg == NULL || !pNIDlg -> FInit (lOldIdent)) {
		DELETE (pNIDlg);
		return NULL;
	}
	pNIDlg -> AdjustOK();
		
return pNIDlg;
}

// Memberfunktionen -----------------------------------------------------------
extern "C" {

typedef struct tagFILLIDENTDATA {
	ComboBox *m_pCB;
	short m_iIdBase;
	char *m_pOutBuff;
} FILLIDENTDATA;


BOOL EXPORTTRIAS WINAPI FillIdentsCB (long lIdent, BOOL, void *pData)
{
PBDDATA pbdData;
char cbKText[33];
FILLIDENTDATA *pFI = (FILLIDENTDATA *)pData;

	memset (&pbdData, '\0', sizeof(PBDDATA));
	memset (cbKText, '\0', sizeof(cbKText));
	
	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = cbKText;
	pbdData.pbdKTextLen = sizeof(cbKText) -1;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);
	cbKText[32] = '\0';

	if (pFI -> m_iIdBase == 10) 
		wsprintf (pFI -> m_pOutBuff, "%08ld%c%s", lIdent, IDENT_DELIMITER_CHAR, pbdData.pbdKText);
	else
		wsprintf (pFI -> m_pOutBuff, "%08lx%c%s", lIdent, IDENT_DELIMITER_CHAR, pbdData.pbdKText);
		
	pFI -> m_pCB -> AddString (pFI -> m_pOutBuff);

return TRUE;	// weitermachen
}

} 	// extern "C"


// ComboBox mit allen existierenden Idents füllen -----------------------------
BOOL CNewIdentDlg :: FillOldIdents (long lIdent)
{
FILLIDENTDATA FID;

	FID.m_pCB = &m_cbOldId;
	FID.m_iIdBase = m_iIdBase;
	FID.m_pOutBuff = m_pOutBuff;
	
// das jeweils übergeordnete Fenster auffordern seine Idents zu liefern
ENUMNOKEYLONG ENK;
	
	ENK.eFcn = (ENUMLONGKEYPROC)FillIdentsCB;
	ENK.ePtr = &FID;
	DEXOR_EnumIdentsSelected (GetParent() -> Handle(), ENK);

	if (lIdent != -1L) {
		ultoa (lIdent, m_pOutBuff, m_iIdBase);
	
	short iIndex = m_cbNewId.FindString (m_pOutBuff);
	
		if (iIndex != -1)
			m_cbOldId.ChangeCurrentIndex (iIndex);
	}

return TRUE;
}


// ComboBox mit allen Idents der PBD füllen -----------------------------------
BOOL FillNewIdents (ComboBox &rCB, CHelpText *pHelpText, short iIdBase, char *pBuff)
{
FILLIDENTDATA FID;

	FID.m_pCB = &rCB;
	FID.m_iIdBase = iIdBase;
	FID.m_pOutBuff = pBuff;
	
ENUMLONGKEY ELK;
	
	memset (&ELK, '\0', sizeof (ENUMLONGKEY));
	ELK.eKey = 'i';
	ELK.eFcn = (ENUMLONGKEYPROC)FillIdentsCB;
	ELK.ePtr = &FID;
	if (!DEX_EnumPBDData (ELK))
		return FALSE;		// Fehler bei Enumeration

long lIdent = DEX_GetLastIdent();	// letzter neuer Identifikator

	if (lIdent != -1L) {
		ultoa (lIdent, pBuff, iIdBase);
	
	short iIndex = rCB.FindString (pBuff);
	
		if (iIndex != -1) {
			rCB.ChangeCurrentIndex (iIndex);
			pHelpText -> SetHelpTextV (IDS_NEWIDENT, strchr (pBuff, IDENT_DELIMITER_CHAR) +1);
			rCB.SetFocus();
		}
	}

return TRUE;
}


// EventHandler ---------------------------------------------------------------
void CNewIdentDlg :: ButtonClick (ControlEvt e) 
{
	switch ((uint)e.GetControlID()) {
	case IDOK:		// OK 
		m_lOldIdent = GetIdent (&m_cbOldId);
		m_lNewIdent = GetIdent (&m_cbNewId, TRUE);
		if (m_lNewIdent != -1L)
			DEX_SetLastIdent (m_lNewIdent);
		EndDlg (1);
		break;

	case IDCANCEL:
		EndDlg ();	// raus und vorbei
		break;

	case IDBX_OLDIDENT:
		{
		short iIndex = -1;
		
			if (m_bxOldId.isChecked()) {
				m_cbOldId.Enable();
				if (m_lLastIdent != -1L) {
					ultoa (m_lLastIdent, m_pOutBuff, m_iIdBase);
					iIndex = m_cbOldId.FindString (m_pOutBuff);
				}
				
			// HilfeText richten
				if (iIndex != -1) {
					m_cbOldId.ChangeCurrentIndex (iIndex);
					m_cbOldId.GetString (m_pOutBuff, iIndex, _MAX_PATH);
					m_pHelpText -> SetHelpTextV (IDS_OLDIDENT, strchr (m_pOutBuff, IDENT_DELIMITER_CHAR) +1);
				} else
					m_pHelpText -> SetHelpText (IDS_BOXOLDIDENT);
			} else {
				m_lLastIdent = GetIdent (&m_cbOldId, FALSE);
				m_cbOldId.ChangeCurrentIndex (-1);	// nichts mehr selektiert

				iIndex = m_cbNewId.GetCurrentIndex();
				if (iIndex != -1) {
					m_cbNewId.GetString (m_pOutBuff, iIndex, _MAX_PATH);
					m_cbNewId.SetText (m_pOutBuff);		// damit AdjustOK richtig geht
					m_pHelpText -> SetHelpTextV (IDS_NEWIDENT, strchr (m_pOutBuff, IDENT_DELIMITER_CHAR) +1);
				} else {
					m_pHelpText -> SetHelpText (IDS_BOXOLDIDENT);
					m_lLastIdent = -1L;
				}

				m_cbOldId.Disable();
			}
		}
		break;
		
	case IDB_NEWIDHELP:
		IrisHD -> Show (IDB_NEWIDHELP);
		break;
	}
}


void CNewIdentDlg :: ListBoxSel (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDCB_OLDIDENT:
		{
		short iIndex = m_cbOldId.GetCurrentIndex();
		
			if (iIndex != -1) {
				m_cbOldId.GetString (m_pOutBuff, iIndex, _MAX_PATH);
				m_pHelpText -> SetHelpTextV (IDS_OLDIDENT, strchr (m_pOutBuff, IDENT_DELIMITER_CHAR) +1);
			}
		}
		break;
		
	case IDCB_NEWIDENT:
		{
		short iIndex = m_cbNewId.GetCurrentIndex();
		
			if (iIndex != -1) {
				m_cbNewId.GetString (m_pOutBuff, iIndex, _MAX_PATH);
				m_cbNewId.SetText (m_pOutBuff);		// damit AdjustOK richtig geht
				m_pHelpText -> SetHelpTextV (IDS_NEWIDENT, strchr (m_pOutBuff, IDENT_DELIMITER_CHAR) +1);
			}
		}
		break;
	}
	AdjustOK();
}


void CNewIdentDlg :: EditChange (ControlEvt)
{
	AdjustOK (FALSE);
}


// Überprüfen, wenn ComboBoxen Focus erhalten haben ---------------------------
void CNewIdentDlg :: EditFocusChg (EditFocusChgEvt e)
{
	if (!((ComboFocusChgEvt &)e).gotFocus()) {
	// Focus abgegeben, Eingabe überprüfen
		if ((uint)e.GetControlID() == IDCB_NEWIDENT) {
			if (m_cbNewId.GetTextLen() > 0) {
			// Eingabe auf Gültigkeit testen
				m_cbNewId.GetText (m_pOutBuff, _MAX_PATH);
				for (char *pT = m_pOutBuff; *pT; pT++) {
					if ((m_iIdBase == 10) ? isdigit(*pT) : isxdigit(*pT)) 
						continue;
					if (*pT == IDENT_DELIMITER_CHAR) 
						break;	// normale Eingabe

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
			long lIdent = strtoul (m_pOutBuff, NULL, m_iIdBase);
			
				if (m_iIdBase == 10) 
					wsprintf (m_pOutBuff, "%08ld", lIdent);
				else
					wsprintf (m_pOutBuff, "%08lx", lIdent);

			short iIndex = m_cbNewId.FindString (m_pOutBuff);
			
				if (iIndex == -1)
					m_pHelpText -> SetHelpTextV (IDS_NEWIDENTKEY, m_pOutBuff);
				else {
					m_cbNewId.ChangeCurrentIndex (iIndex);
					m_cbNewId.GetString (m_pOutBuff, iIndex, _MAX_PATH);
					m_pHelpText -> SetHelpTextV (IDS_NEWIDENT, strchr (m_pOutBuff, IDENT_DELIMITER_CHAR) +1);
				}
			}
		}
		AdjustOK (FALSE);
		return;
	}
	
// Focus erhalten, Hilfetext setzen
	switch ((uint)e.GetControlID()) {
	case IDCB_OLDIDENT:
		{
		short iIndex = m_cbOldId.GetCurrentIndex();
		
			if (iIndex != -1) {
				m_cbOldId.GetString (m_pOutBuff, iIndex, _MAX_PATH);
				m_pHelpText -> SetHelpTextV (IDS_OLDIDENT, strchr (m_pOutBuff, IDENT_DELIMITER_CHAR) +1);
			}
		}
		break;
		
	case IDCB_NEWIDENT:
		{
		short iIndex = m_cbNewId.GetCurrentIndex();
		
			if (iIndex != -1) {
				m_cbNewId.GetString (m_pOutBuff, iIndex, _MAX_PATH);
				m_pHelpText -> SetHelpTextV (IDS_NEWIDENT, strchr (m_pOutBuff, IDENT_DELIMITER_CHAR) +1);
			} 
		}
		break;
	}
	AdjustOK();
}



long CNewIdentDlg :: GetIdent (ComboBox *pCB, BOOL fEdit)
{
short iIndex = pCB -> GetCurrentIndex();

	if (iIndex != -1) {
		pCB -> GetString (m_pOutBuff, iIndex, _MAX_PATH);
		return strtoul (m_pOutBuff, NULL, m_iIdBase);
	} else if (fEdit) {
		pCB -> GetText (m_pOutBuff, _MAX_PATH);
		return strtoul (m_pOutBuff, NULL, m_iIdBase);
	}
	
return -1L;
}


// OK-Knopf richten -----------------------------------------------------------
void CNewIdentDlg :: AdjustOK (BOOL fIndex)
{
// neuer Ident gegeben ?
short iIndex = m_cbNewId.GetCurrentIndex();

	if (m_cbNewId.GetTextLen() == 0 || (fIndex && iIndex == -1))
	{
		m_pbOK.Disable();
		return;
	}
	m_pbOK.Enable();	
}
