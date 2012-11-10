// Eine ListViewCtrl, das alle RelationesCodes der Beschreibungs-Datenbasis enthält 
// File: SELRELST.HXX

#if !defined(_SELRELST_HXX)
#define _SELRELST_HXX

class CSelPBDRelationList : public CListViewCtrl {
private:
	char *m_pBuff;
	ResourceFile &m_rRF;
	
	bool DecodeEntry (int iIndex, long &rlIdent, short &riOTyp);
	short GetRTyp (LPCSTR pTyp);

protected:
	void FitColumn (int iCol);

public:
// Konstruktor/Destruktor/Initialisierung
		CSelPBDRelationList (pDialogWindow pW, ResID uiRes, 
				     ResourceFile &rRF);
		~CSelPBDRelationList (void);
		
	bool InitControl (void);

	bool GetSelectedRCode (long &rlRCode, short &riRTyp);
};

#endif // _SELRELST_HXX
 
