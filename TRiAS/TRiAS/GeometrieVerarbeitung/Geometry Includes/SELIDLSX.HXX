// Eine Listbox, die alle Identifikator/Objekttypen der Datenbasis enthält ----
// File: SELIDLSX.HXX

#if !defined(_SELIDLSX_HXX)
#define _SELIDLSX_HXX

class _GEOMETR_ENTRY CSelIdentListX : public MultiSelListBox {
private:
	char *m_pBuff;
	short m_iIdBase;
	ulong m_ulLastIdent;
	short m_iLastTypes;
	
	bool DecodeEntry (short iIndex, ulong &rulIdent, short &riOTyp);
	short GetOTyp (short ch);
	
public:
// Konstruktor/Destruktor/Initialisierung
		CSelIdentListX (pDialogWindow pW, ResID uiRes);
		~CSelIdentListX (void);
		
//	bool FInit (void);
	bool FInit (bool bShowRO);	// 21.09.99
	
//static CSelIdentListX *CreateInstance (pDialogWindow pW, ResID uiRes);
static CSelIdentListX *CreateInstance (pDialogWindow pW, ResID uiRes, bool bShowRO);	// 21.09.99

// ZugriffsFunktionen auf ausgewählte Identifikatoren
	bool GetFirstIdent (ulong &rulIdent, short &riOTyp);
	bool GetNextIdent (ulong &rulIdent, short &riOTyp);

// Initialisierungsfunktion der anfangs ausgewählten Idents
	bool SelectIdent (ulong ulIdent, short iOTyp, bool fSel = true);
};

#endif // _SELIDLSX_HXX
 
