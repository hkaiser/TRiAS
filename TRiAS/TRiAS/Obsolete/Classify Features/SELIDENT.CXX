// Auswahl aller Objekte verschiedener Objektklassen --------------------------
// File: SELIDENT.CXX

#include "featurep.hxx"
#include "feature.h"

#include "selidlst.hxx"
#include "selident.hxx"

// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable: 4355)

CSelectIdentDlg :: CSelectIdentDlg (pWindow pW, ResID uiDlg)
		 : DialogWindow (pW, uiDlg),
		   m_pbOK (this, IDOK),
		   m_pbHelp (this, IDHELP),
		   m_pbSelAll (this, IDB_SELALLCLASSES),
		   m_cbFeatures (this, IDC_FEATURES)
{
	m_pIdents = NULL;
	
	m_pbHelp.Disable();
	m_pbOK.Disable();
	m_pbSelAll.Disable();
}

#pragma warning (default: 4355)

CSelectIdentDlg :: ~CSelectIdentDlg (void)
{
	DELETE (m_pIdents);
}

CSelectIdentDlg *CSelectIdentDlg :: CreateInstance (pWindow pW, ResID uiDlg)
{
CEierUhr Wait (pW);
CSelectIdentDlg *pDlg = new CSelectIdentDlg (pW, uiDlg);

	if (pDlg == NULL || !pDlg -> FInit()) {
		DELETE (pDlg);
		return NULL;
	}
	
return pDlg;
}

bool CSelectIdentDlg :: FInit (void)
{
// IdentifikatorListBox füllen
	m_pIdents = CSelIdentList :: CreateInstance (this, IDL_SELECTIDENTS);
	if (m_pIdents == NULL) return false;

// verfügbare Merkmale anzeigen
	FillMerkmale();

// Button SelectAll richten
	if (m_pIdents -> GetCount())
		m_pbSelAll.Enable();
	
return true;
}

// EventHandler ---------------------------------------------------------------
void CSelectIdentDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg (1);
		break;
		
	case IDCANCEL:
		EndDlg (0);	// abbrechen
		break;
		
	case IDB_SELALLCLASSES:	// alle markieren
		m_pIdents -> ChangeSelected (Range (0, m_pIdents -> GetCount() -1));
		AdjustOK();
		break;
		
	case IDHELP:
		break;
	}
}


void CSelectIdentDlg :: ListBoxSel (ControlEvt)
{
	AdjustOK();
}


// HilfsRoutinen --------------------------------------------------------------
void CSelectIdentDlg :: AdjustOK (void)
{
	if (!m_pIdents || m_pIdents -> GetNoSelected() == 0 || 
	    m_cbFeatures.GetCurrentIndex() == -1)
		m_pbOK.Disable();
	else
		m_pbOK.Enable();
}


// AbfrageRoutinen ------------------------------------------------------------
bool CSelectIdentDlg :: GetFirstIdent (long &rlIdent, short &riOTyp)
{
	if (m_pIdents) 
		return m_pIdents -> GetFirstIdent (rlIdent, riOTyp);
		
return false;
}


bool CSelectIdentDlg :: GetNextIdent (long &rlIdent, short &riOTyp)
{
	if (m_pIdents) 
		return m_pIdents -> GetNextIdent (rlIdent, riOTyp);
		
return false;
}

bool CSelectIdentDlg :: SelectIdent (long lIdent, short iOTyp, bool fSel)
{
	if (m_pIdents) {
	bool fResult = m_pIdents -> SelectIdent (lIdent, iOTyp, fSel);

		AdjustOK();
		return fResult;
	}
		
return false;
}

ULONG CSelectIdentDlg :: GetMCode (void)
{
int iIndex = m_cbFeatures.GetCurrentIndex();

	if (iIndex == -1) return 0L;
	
char cbBuffer[_MAX_PATH];

	m_cbFeatures.GetString (cbBuffer, iIndex, _MAX_PATH);

return strtoul (cbBuffer, NULL, DEX_GetMkBase());
}

// verfügbare Merkmale anzeigen -----------------------------------------------
char *GetPBDText (long lMCode, char *pText)
{
        if (lMCode == -1L) return "";

PBDDATA pbdData;

        INITSTRUCT (pbdData, PBDDATA);
        pbdData.pbdTyp = 'm';
        pbdData.pbdCode = lMCode;
        pbdData.pbdKText = pText;
        pbdData.pbdKTextLen = 33;

        if (DEX_GetPBDData (pbdData) != EC_OKAY) {
                return "";
        }
        pText[32] = '\0';

return pText;
}

extern "C" _XTENSN_EXPORT PASCAL FillMCode (long lMCode, bool, void *pData)
{
ComboBox *pCB = (ComboBox *)pData;
char cbKText[33];
char cbBuffer[_MAX_PATH];

	if (DEX_GetMkBase() == 10)
		wsprintf (cbBuffer, "%ld:%s", lMCode, GetPBDText (lMCode, cbKText));
	else
		wsprintf (cbBuffer, "0x%lx:%s", lMCode, GetPBDText (lMCode, cbKText));
	pCB -> AddString (cbBuffer);
	
return true;
}

bool CSelectIdentDlg :: FillMerkmale (void)
{
ENUMNOKEY ENK;

	ENK.eFcn = (ENUMNOKEYPROC)FillMCode;
	ENK.ePtr = &m_cbFeatures;

return DEX_EnumMCodes (ENK);
}
