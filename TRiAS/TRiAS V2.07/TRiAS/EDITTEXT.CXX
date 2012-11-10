// Editieren von TextObjekten -------------------------------------------------
// File: EDITTEXT.CXX

#include "triaspre.hxx"

#include "triasres.h"
#include "strings.h"
#include "edittext.hxx"

char *ConvertToNL (char *pText);
char *ConvertFromNL (char *pText);

// Konstruktor ----------------------------------------------------------------
extern "C" {

typedef struct tagFILLIDENTDATA {
	ComboBox *m_pCB;
	short m_iIdBase;
} FILLIDENTDATA;

BOOL EXPORTTRIAS WINAPI FillIdentsListBox (long lIdent, BOOL, void *pData)
{
PBDDATA pbdData;
char cbKText[33];
ComboBox *pFI = (ComboBox *)pData;

	memset (&pbdData, '\0', sizeof(PBDDATA));

	pbdData.dwSize = sizeof(PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = cbKText;
	pbdData.pbdKTextLen = sizeof(cbKText) -1;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);
	
	cbKText[sizeof(cbKText)-1] = '\0';	

char outBuff[80];

	if (SUCCEEDED(ClassFromIdent (lIdent, outBuff, sizeof(outBuff)))) 
	{
		strcat (outBuff, g_cbColon);
		strcat (outBuff, pbdData.pbdKText);
		pFI -> AddString (outBuff);
	}

return TRUE;	// weitermachen
}

}

#pragma warning (disable:4355)

EditTextObjektDialog :: EditTextObjektDialog (pWindow pW, char *oldText, 
			Punkt &ptPkt, long lIdent, CoordTrans *pCTF) 
		      : DialogWindow (pW, EDITTEXTDIALOG),
			NewText (this, IDE_NEWTEXT),
			m_dneX (this, IDE_COORDX),
			m_dneY (this, IDE_COORDY),
#if !defined(WIN32)
			m_pbHelp (this, IDB_EDITTEXTHELP),
#endif // WIN32
			OKButton (this, IDOK),
			CancelButton (this, IDCANCEL),
			m_cbIdents (this, IDCB_IDENTS),
			m_ftEditPrompt (this, IDT_EDITTEXTPROMPT),
			m_pCTF (pCTF)
{
CEierUhr Wait (this);

	m_lIdent = lIdent;
	
// Style vom MultilIneEdit erweitern
//	NewText.SetStyle (ES_WANTRETURN);
#if !defined(WIN32)
	m_pbHelp.Disable();
#endif // WIN32

// sonstige Initialisierungen
	m_pNewText = NULL;	// Member initialisieren

// EditControl initialisieren
	if (oldText) {
	char *pText = ConvertToNL (oldText);

		if (pText) {
			NewText.SetText (pText);
			delete pText;
		}
	}

// Variablen initialisieren
	m_dneX.SetNumEditMode (NumEdit :: NEM_NoTest);
	m_dneY.SetNumEditMode (NumEdit :: NEM_NoTest);

	m_pOutBuff = new char [_MAX_PATH];
	if (ptPkt.X() != -1 && ptPkt.Y() != -1 && m_pOutBuff) {
		if (m_pCTF) {
		double X, Y;

			m_pCTF -> UnScale (ptPkt.X(), ptPkt.Y(), &X, &Y);
			m_pCTF -> Transform (&X, &Y);
			m_pCTF -> CoordTransToStringEx (X, Y, TRUE, m_pOutBuff, 64);
			m_dneX.SetText (m_pOutBuff);
			m_pCTF -> CoordTransToStringEx (X, Y, FALSE, m_pOutBuff, 64);
			m_dneY.SetText (m_pOutBuff);
		} else {
			m_dneX.SetText (ltoa (ptPkt.X(), m_pOutBuff, 10));
			m_dneY.SetText (ltoa (ptPkt.Y(), m_pOutBuff, 10));
		}
	}
	
// ComboBox füllen
	if (m_pOutBuff) {
	ENUMLONGKEY ELK;
	
		memset (&ELK, '\0', sizeof (ENUMLONGKEY));
		ELK.eKey = 'i';
		ELK.eFcn = (ENUMLONGKEYPROC)FillIdentsListBox;
		ELK.ePtr = &m_cbIdents;
		DEX_EnumPBDData (ELK);

		if (lIdent != -1L && 
			SUCCEEDED(ClassFromIdent (lIdent, m_pOutBuff, _MAX_PATH))) 
		{
		short iIndex = m_cbIdents.FindString (m_pOutBuff);
		
			if (iIndex != -1) 
				m_cbIdents.ChangeCurrentIndex (iIndex);
		}
	}
	AdjustOK();
}

#pragma warning (default:4355)

EditTextObjektDialog :: ~EditTextObjektDialog (void)
{
	DELETE (m_pNewText);
	DELETE (m_pOutBuff);
}


void EditTextObjektDialog :: ButtonClick (ControlEvt e) 
{
	switch ((unsigned int)e.GetControlID ()) {
	case IDOK:		// neuer Text eingegeben, fertig
		{
		short sTextLen = NewText.GetTextLen();
		char *pTmp = new char [sTextLen +2];

			if (pTmp == NULL) {
				db_error (EC_NOMEMORY, RC_EditTextObjekt);
				EndDlg ();
				return;
			}
			NewText.GetText (pTmp, sTextLen +1);
			m_pNewText = ConvertFromNL (pTmp);
			delete pTmp;

			EndDlg (1);
		}
		break;

	case IDCANCEL:
		EndDlg ();	// abbrechen
		break;
	}
}

void EditTextObjektDialog :: EditChange (ControlEvt) 
{
	AdjustOK();
}


void EditTextObjektDialog :: ListBoxSel (ControlEvt) 
{
	AdjustOK();
}


// Neue Koordinaten abfragen --------------------------------------------------
BOOL EditTextObjektDialog :: GetPunkt (Punkt &ResultPkt)
{
	if (!m_dneX.GetEditControl() -> isModified() &&
	    !m_dneY.GetEditControl() -> isModified())
	// keine der Koordinaten wurde geändert             
		return FALSE;

char *pInBuff = new char [64];
char *pInBuffY = new char [64];

	if (pInBuff == NULL || NULL == pInBuffY) return FALSE;

	if (m_pCTF) {
	double X, Y;

		m_dneX.GetText (pInBuff, 64);
		m_dneY.GetText (pInBuffY, 64);

		m_pCTF -> CoordTransToValueEx (pInBuff, pInBuffY, X, Y);
		m_pCTF -> InvTransform (&X, &Y);
		m_pCTF -> Scale (X, Y, ResultPkt);
	} else {
		m_dneX.GetText (pInBuff, 64);
		ResultPkt.X() = atol (pInBuff);
		m_dneY.GetText (pInBuff, 64);
		ResultPkt.Y() = atol (pInBuff);
	}

	DELETE (pInBuff);

return TRUE;
}


BOOL EditTextObjektDialog :: GetIdent (long &rlIdent)
{
short iIndex = m_cbIdents.GetCurrentIndex();
long lIdent = -1L;

	if (iIndex == -1 || m_pOutBuff == NULL) 
		return FALSE;
	
	m_cbIdents.GetString (m_pOutBuff, iIndex, _MAX_PATH);
	IdentFromClass (m_pOutBuff, (ULONG *)&lIdent);
	if (lIdent == m_lIdent)
		return FALSE;		// Identifikator nicht geändert
		
	rlIdent = lIdent;
	
return TRUE;
}


BOOL EditTextObjektDialog :: AdjustOK (void)
{
	if (NewText.GetTextLen() <= 0 ||
	    m_cbIdents.GetCurrentIndex() == -1 ||
	    m_dneX.GetTextLen() <= 0 ||
	    m_dneY.GetTextLen() <= 0) 
	{
		OKButton.Disable();
		return FALSE;
	}
	OKButton.Enable();
	
return TRUE;
}

void EditTextObjektDialog::SetEditRO (BOOL fRO)
{
	NewText.SetRO (fRO);
	if (fRO) {
	ResString resEditPrompt(IDS_EDITPROMPT, 64);

		m_ftEditPrompt.SetText (resEditPrompt);
	}
}

// Konvertierung der internen Zeichendarstellung ------------------------------
char *ConvertFromEscape (char *pText, char srch)
{
	if (pText == NULL) return NULL;

char *pNewText = new char [2 * strlen (pText) +1];

// alle abschließenden \r\n entfernen
char *pTmp = &pText[strlen (pText) -1];

	while ((*pTmp == '\n' || *pTmp == '\r') && pTmp >= pText)
		pTmp--;

	*(pTmp+1) = '\0';	// wegschneiden

// Umkopieren und dabei konvertieren
	pTmp = pNewText;
	if (pNewText) {
		while (*pText) {
			if (*pText == '\n') {
				if (*(pText+1)) {
					*pTmp++ = '\\';
					*pTmp++ = 'n';
				} else {
					pText++;
					continue;
				}
			} else if (*pText != '\r') {
				*pTmp++ = *pText;
			} else if (*pText == srch) {
				*pTmp++ = '\\';
				*pTmp++ = srch;
			}

			pText++;
		}
		*pTmp = '\0';
	}

return pNewText;
}

char *ConvertToEscape (char *pText, char srch)
{
	if (pText == NULL) return NULL;

char *pNewText = new char [strlen (pText) +1];
char *pTmp = pNewText;

	if (pNewText) {
		while (*pText) {
			if (*pText == '\\' && *(pText+1) == 'n') {
				*pTmp++ = '\r';
				*pTmp++ = '\n';
				pText += 2;
			} else if (*pText == '\\' && *(pText+1) == srch) {
				*pTmp++ = srch;
				pText += 2;
			} else
				*pTmp++ = *pText++;
		}
		*pTmp = '\0';
	}

	return pNewText;
}


// Konvertierung der internen Zeichendarstellung ------------------------------
char *ConvertFromNL (char *pText)
{
	if (pText == NULL) return NULL;

char *pNewText = new char [2 * strlen (pText) +1];

// alle abschließenden \r\n entfernen
char *pTmp = &pText[strlen (pText) -1];

	while ((*pTmp == '\n' || *pTmp == '\r') && pTmp >= pText)
		pTmp--;

	*(pTmp+1) = '\0';	// wegschneiden

// Umkopieren und dabei konvertieren
	pTmp = pNewText;
	if (pNewText) {
		while (*pText) {
			if (*pText == '\n') {
				if (*(pText+1)) {
					*pTmp++ = '\\';
					*pTmp++ = 'n';
				} else {
					pText++;
					continue;
				}
			} else if (*pText != '\r') {
				*pTmp++ = *pText;
			}

			pText++;
		}
		*pTmp = '\0';
	}

return pNewText;
}

char *ConvertToNL (char *pText)
{
	if (pText == NULL) return NULL;

char *pNewText = new char [strlen (pText) +1];
char *pTmp = pNewText;

	if (pNewText) {
		while (*pText) {
			if (*pText == '\\' && *(pText+1) == 'n') {
				*pTmp++ = '\r';
				*pTmp++ = '\n';
				pText += 2;
			} else
				*pTmp++ = *pText++;
		}
		*pTmp = '\0';
	}

	return pNewText;
}


