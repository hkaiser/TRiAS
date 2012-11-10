// Eine Listbox, die alle Identifikator/Objekttypen der Datenbasis enthält ----
// File: SELIDLST.HXX

#if !defined(_SELIDLST_HXX)
#define _SELIDLST_HXX

class CSelIdentList : public CListViewCtrl {
private:
	char *m_pBuff;
	short m_iIdBase;
	long m_lLastIdent;
	short m_iLastTypes;
	int m_iCurrItem;

	ResourceFile &m_rRF;
	
	bool DecodeEntry (int iIndex, long &rlIdent, short &riOTyp);
	short GetOTyp (LPCSTR pTyp);

protected:
	int GetFirstSelected (void);
	int GetNextSelected (void);
	void FitColumn (int iCol);

public:
// Konstruktor/Destruktor/Initialisierung
		CSelIdentList (pDialogWindow pW, ResID uiRes, ResourceFile &rRF);
		~CSelIdentList (void);
		
	bool InitControl (void);

// ZugriffsFunktionen auf ausgewählte Identifikatoren
	bool GetFirstIdent (long &rlIdent, short &riOTyp);
	bool GetNextIdent (long &rlIdent, short &riOTyp);

// Initialisierungsfunktion der anfangs ausgewählten Idents
	bool SelectIdent (long lIdent, short iOTyp, bool fSel = TRUE);
	bool ChangeSelectedAll (bool fSel);
};

#endif // _SELIDLST_HXX
 
