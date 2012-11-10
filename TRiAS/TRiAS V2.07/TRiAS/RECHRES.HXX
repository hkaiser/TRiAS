// Auswahl der RechercheErgebnisse --------------------------------------------
// File: RECHRES.HXX

#if !defined(_RECHRES_HXX)
#define _RECHRES_HXX

class CSelIdentList;
class CRechResultDlg : public DialogWindow {
private:
	short m_fHideFlags;		// welche Info soll nicht angezeigt werden
	short m_fSortFlags;		// nach welchem Feld soll sortiert werden
	
	CheckBox m_cbObjNr;
	CheckBox m_cbIdent;
	CheckBox m_cbObjTyp;
#if !defined(WIN32)
	PushButton m_pbHelp;
#endif // WIN32
	PushButton m_pbOK;
	PushButton m_pbSelAll;	
	CSelIdentList *m_pIdents;
	
	RadioButton m_rbObjNr;		// Auswahl sortieren nach 
	RadioButton m_rbObjTyp;
	RadioButton m_rbIdent;
	RadioButton m_rbOProp;

	ComboBox m_cbObjProps;		// Objekteigenschaften

	DatenBasisObjekt &m_rDBO;

	void AdjustOK (void);
	void AdjustRadios (short iSort);
	
protected:
	void ButtonClick (ControlEvt e);
	
public:
		CRechResultDlg (pWindow pW, DatenBasisObjekt &rDBO);
		~CRechResultDlg (void);
		
static CRechResultDlg *CreateInstance (pWindow pW, DatenBasisObjekt &rDBO, LPENUMOBJPROPS pEnum);

	bool FInit (LPENUMOBJPROPS pEnum);
	
// ZugriffsFunktionen auf ausgewählte Identifikatoren
	bool GetFirstIdent (long &rlIdent, short &riOTyp);
	bool GetNextIdent (long &rlIdent, short &riOTyp);
	bool SelectIdents (long lIdent, short iOTyp);

	string GetActOProp (void);
	void SetActOProp (LPCSTR pName);

inline short GetHideFlags (void) { return m_fHideFlags|m_fSortFlags; }
	void SetHideFlags (short iHideFlags);
};

#endif // _RECHRES_HXX
