// Eine ListViewCtrl, das alle Identifikatoren der Beschreibungs-Datenbasis enthält 
// File: SELIDPBD.HXX

#if !defined(_SELIDPBD_HXX)
#define _SELIDPBD_HXX

class CSelPBDIdentList : public CListViewCtrl {
private:
	char *m_pBuff;
	ResourceFile &m_rRF;
	int m_iIdBase;
		
	bool DecodeEntry (int iIndex, long &rlIdent);

protected:
	void FitColumn (int iCol);

public:
// Konstruktor/Destruktor/Initialisierung
		CSelPBDIdentList (pDialogWindow pW, ResID uiRes, 
				  ResourceFile &rRF);
		~CSelPBDIdentList (void);
		
	bool InitControl (void);

	bool GetSelectedIdent (long &rlIdent);
};

#endif // _SELIDPBD_HXX
 
