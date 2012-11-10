// Editieren des Textes eines Textobjektes ------------------------------------
// File: EDITTEXT.HXX

#if !defined(_EDITTEXT_HXX)
#define _EDITTEXT_HXX

#include "editro.hxx"		// EditControl, welches RO/nicht RO sein kann

class EditTextObjektDialog : 
	public DialogWindow 
{
private:
	CEditCondRO NewText;
	PushButton OKButton;
	PushButton CancelButton;
	DoubleNumEdit m_dneX;
	DoubleNumEdit m_dneY;
	ComboBox m_cbIdents;
	FixedText m_ftEditPrompt;

	CoordTrans *m_pCTF;

protected:
	char *m_pOutBuff;		// Bufferbereich
	char *m_pNewText;		// Eingegebener Text
	long m_lIdent;			// alter Ident
	
	void ButtonClick (ControlEvt);
	void EditChange (ControlEvt);
	void ListBoxSel (ControlEvt);
		
	BOOL AdjustOK (void);
	
public:
// Konstruktor/Destruktor
		EditTextObjektDialog (pWindow pW, char *oldText, Punkt &ptPkt, 
				      long lIdent, CoordTrans *pCTF = NULL);
		~EditTextObjektDialog (void);

	char *GetNewText (void) { return m_pNewText; }	// keine Kopie
	BOOL GetPunkt (Punkt &);
	BOOL GetIdent (long &rlIdent);

	void SetEditRO (BOOL fRO);
};


#endif // _EDITTEXT_HXX


