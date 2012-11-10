// Editieren von TextObjekten -------------------------------------------------
// File: EDITTEXT.CXX

#include "triaspre.hxx"

#include "triasres.h"
#include "strings.h"
#include "edittext.hxx"

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char *ConvertToNL (LPCSTR pText);
char *ConvertFromNL (LPCSTR pText);
char *ConvertToEscape (LPCSTR pText, LPCSTR srch);
char *ConvertFromEscape (LPCSTR pText, LPCSTR srch);

// Konstruktor ----------------------------------------------------------------

typedef struct tagFILLIDENTDATA {
	ComboBox *m_pCB;
	HPROJECT m_hPr;
} FILLIDENTDATA;

extern "C" 
BOOL EXPORTTRIAS WINAPI FillIdentsListBox (long lIdent, BOOL, void *pData)
{
PBDDATA pbdData;
char cbBuffer[_MAX_PATH] = { '\0' };
ComboBox *pFI = ((FILLIDENTDATA *)pData) -> m_pCB;
HPROJECT hPrToMatch = ((FILLIDENTDATA *)pData) -> m_hPr;

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = cbBuffer;
	pbdData.pbdKTextLen = sizeof(cbBuffer) -1;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);
	
HPROJECT hPr = DEX_GetObjectsProject(lIdent);

	TX_ASSERT(HACTCONNECTION != hPr);
	if (HACTCONNECTION != hPrToMatch && hPr != hPrToMatch)
		return TRUE;		// nur Idents der gegebenen Datenquelle

	if (DEX_GetROModeEx(hPr) || DEX_GetROModeIdent(lIdent))
		return TRUE;		// keine schreibgesch¸tzten Objektklassen
		
char outBuff[_MAX_PATH] = { '\0' };

	if (SUCCEEDED(ClassFromIdent (lIdent, outBuff, sizeof(outBuff)))) {
		strcat (outBuff, g_cbColon);
		strcat (outBuff, cbBuffer);

	// wenn mehr als eine Datenquelle geˆffnet ist, dann den Namen der zugehˆrigen 
	// in Klammern hintendran h‰ngen
		if (DEX_GetOpenConnectionCount (QDCAllOpen|QDCCountQueryDefs) > 1) {
			if (NULL != DEX_GetDataSourceShortName (hPr, cbBuffer)) {
				strcat (outBuff, " (");
				strcat (outBuff, cbBuffer);
				strcat (outBuff, ")");
			}
		}
	
	int iIndex = pFI -> AddString (outBuff);

		pFI -> SetItemData (iIndex, lIdent);
	}
	return TRUE;	// weitermachen
}

#pragma warning (disable:4355)

EditTextObjektDialog :: EditTextObjektDialog (
	pWindow pW, const char *oldText, Punkt &ptPkt, long lIdent, CoordTrans *pCTF, HPROJECT hPr) 
		: DialogWindow (pW, EDITTEXTDIALOG),
		  NewText (this, IDE_NEWTEXT),
		  m_dneX (this, IDE_COORDX),
		  m_dneY (this, IDE_COORDY),
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

// sonstige Initialisierungen
	m_pNewText = NULL;	// Member initialisieren

// EditControl initialisieren
	if (oldText) {
	char *pText = ConvertToNL (const_cast<char *>(oldText));

		if (pText) {
			NewText.SetText (pText);
			delete pText;
		}
	}

// Variablen initialisieren
	m_dneX.SetNumEditMode (NumEdit :: NEM_NoTest);
	m_dneY.SetNumEditMode (NumEdit :: NEM_NoTest);

	m_pOutBuff = new char [_MAX_PATH];
	if (ptPkt.GetX() != -1 && ptPkt.GetY() != -1 && m_pOutBuff) {
		if (m_pCTF) {
		double X, Y;

#if defined(_KOORD_ISDOUBLE)
			X = ptPkt.GetX();
			Y = ptPkt.GetY();
#else
			m_pCTF -> UnScale (ptPkt.GetX(), ptPkt.GetY(), &X, &Y);
			m_pCTF -> Transform (&X, &Y);
#endif // _KOORD_ISDOUBLE
			m_pCTF -> CoordTransToStringEx (X, Y, TRUE, m_pOutBuff, 64);
			m_dneX.SetText (m_pOutBuff);
			m_pCTF -> CoordTransToStringEx (X, Y, FALSE, m_pOutBuff, 64);
			m_dneY.SetText (m_pOutBuff);
		} else {
			m_dneX.SetText (ltoa (ptPkt.GetX(), m_pOutBuff, 10));
			m_dneY.SetText (ltoa (ptPkt.GetY(), m_pOutBuff, 10));
		}
	}
	
// ComboBox f¸llen
	if (m_pOutBuff) {
	ENUMLONGKEY ELK;
	FILLIDENTDATA FID;

		FID.m_pCB = &m_cbIdents;
		FID.m_hPr = hPr;
		memset (&ELK, '\0', sizeof (ENUMLONGKEY));
		ELK.eKey = 'i';
		ELK.eFcn = (ENUMLONGKEYPROC)FillIdentsListBox;
		ELK.ePtr = &FID;
		DEX_EnumPBDData (ELK);

		if (lIdent != -1L && SUCCEEDED(ClassFromIdent (lIdent, m_pOutBuff, _MAX_PATH))) {
		int iIndex = m_cbIdents.FindString (m_pOutBuff);
		
			if (iIndex != -1) 
				m_cbIdents.ChangeCurrentIndex (iIndex);

		}
	}
	if (-1 != lIdent && 0 != lIdent && DEX_GetROModeIdent(lIdent)) {
		m_cbIdents.Disable();		// Objektklasse kann nicht modifiziert werden
		NewText.SetRO (true);		// Text kann auch nicht modifiziert werden
	}
	AdjustOK();
}

#pragma warning (default:4355)

EditTextObjektDialog :: ~EditTextObjektDialog (void)
{
	DELETE_OBJ (m_pNewText);
	DELETE_OBJ (m_pOutBuff);
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
	// keine der Koordinaten wurde ge‰ndert             
		return FALSE;

char cbInBuff[64];
char cbInBuffY[64];

	if (m_pCTF) {
	double X, Y;

		m_dneX.GetText (cbInBuff, 64);
		m_dneY.GetText (cbInBuffY, 64);

		m_pCTF -> CoordTransToValueEx (cbInBuff, cbInBuffY, X, Y);
#if defined(_KOORD_ISDOUBLE)
		ResultPkt.SetX(X);
		ResultPkt.SetY(Y);
#else
		m_pCTF -> InvTransform (&X, &Y);
		m_pCTF -> Scale (X, Y, ResultPkt);
#endif // _KOORD_ISDOUBLE
	} else {
		m_dneX.GetText (cbInBuff, 64);
		ResultPkt.SetX(atol (cbInBuff));
		m_dneY.GetText (cbInBuff, 64);
		ResultPkt.SetY(atol (cbInBuff));
	}

	return TRUE;
}


BOOL EditTextObjektDialog :: GetIdent (long &rlIdent)
{
int iIndex = m_cbIdents.GetCurrentIndex();

	if (-1 != iIndex) {
	long lIdent = m_cbIdents.GetItemData (iIndex);

		if (lIdent != m_lIdent) {
			rlIdent = lIdent;
			return TRUE;
		}
	}
	return FALSE;	// Identifikator nicht ge‰ndert
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
char *ConvertFromNL (LPCSTR pText)
{
	if (pText == NULL) return NULL;

char *pNewText = new char [2 * strlen (pText) +1];

// alle abschlieﬂenden \r\n entfernen
char *pTmp = const_cast<char *>(&pText[strlen(pText)-1]);

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
			} else if (*pText != '\r')
				*pTmp++ = *pText;
			pText++;
		}
		*pTmp = '\0';
	}
	return pNewText;
}

char *ConvertToNL (LPCSTR pText)
{
	if (pText == NULL) return NULL;

char *pNewText = new char [strlen(pText) +3];
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

///////////////////////////////////////////////////////////////////////////////
// Konvertierung der internen Zeichendarstellung 
char *ConvertFromEscape (LPCSTR pText, LPCSTR srch)
{
	if (pText == NULL) return NULL;

char *pNewText = new char [2 * strlen (pText) +1];

// alle abschlieﬂenden \r\n entfernen
char *pTmp = const_cast<char *>(&pText[strlen(pText)-1]);

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
			} else if (NULL != strchr (srch, *pText)) {
				*pTmp++ = '\\';
				*pTmp++ = *pText;
			}

			pText++;
		}
		*pTmp = '\0';
	}

return pNewText;
}

char *ConvertToEscape (LPCSTR pText, LPCSTR srch)
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
			} else if (*pText == '\\' && NULL != strchr(srch, *(pText+1))) {
				*pTmp++ = *(pText+1);
				pText += 2;
			} else
				*pTmp++ = *pText++;
		}
		*pTmp = '\0';
	}

	return pNewText;
}

