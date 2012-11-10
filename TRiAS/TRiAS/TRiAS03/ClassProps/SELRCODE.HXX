// Auswahl einer Relation für das Bilden von Komplexobjekten ------------------
// File: SELRCODE.HXX

#if !defined(_SELRCODE_HXX)
#define _SELRCODE_HXX

class CSelectRCodeDlg : public CPropertyPage { 
private:
	DWORD m_dwFlags;
	class CSelPBDRelationList *m_pRCodes;
	class CSelPBDIdentList *m_pIdents;
	class CEnumObjectNumbers *m_pEnum;

	long m_lRCode;		// selektierte Relation
	short m_iRTyp;
	long m_lIdent;		// selektierter Identifikator

	void AdjustOK (bool fDisableNext = false);

protected:
	void ButtonClick (ControlEvt);
	void WindowInit (Event);

	void OnItemChanged (NotifyEvt);
	int OnSetActive (NotifyEvt);
	int OnWizFinish (NotifyEvt);
	int OnWizNext (NotifyEvt);
	void OnCancel (NotifyEvt);

	void OnClick (NotifyEvt);

// ZugriffsFunktionen auf ausgewählte Identifikatoren
	bool GetSelectedRCode (long &rlRCode, short &riRTyp);
	int GetSelectedCount (void);
	bool GetSelectedIdent (long &rlIdent);

	bool PrepareResult (void);

// Komplexobjekte/Hierachische Objekte bilden
	HRESULT CreateHierObject (IEnum<LONG> *pInEnum, LONG &rlKONr);
	HRESULT CreateKomplexObject (IEnum<LONG> *pInEnum, LONG &rlKONr);

// Konstruktor nicht direkt rufen
		CSelectRCodeDlg (ResID uiRes, LPCSTR pcCaption, DWORD dwFlags);

	bool FInit (ResourceFile &rRF);
	
public:
// Destruktor/Initialisierung
		~CSelectRCodeDlg (void);
		
static CSelectRCodeDlg *CreateInstance (UINT uiDlg, LPCSTR pcCaption, 
					DWORD dwFlags, ResourceFile &rRF);
	
// übergibt dem Dialog die Objekte, die verarbeitet werden sollen
	HRESULT SetEnumLONG (IEnum<LONG> *pInEnum, IPropertyTemplate *pITempl);

// Fragt den Dialog nach seinen Daten (gebildete Komplexobjekte)
	HRESULT GetEnumLONG (IEnum<LONG> **ppEnum);
};

#endif // _SELRCODE_HXX

