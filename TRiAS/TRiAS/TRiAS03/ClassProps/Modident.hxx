// Dialog, welcher einen Ident auswählbar macht, um Objekte umzuklassifizieren
// File: MODIDENT.HXX

#if !defined(_MODIDENT_HXX)
#define _MODIDENT_HXX

#include <selidlvc.hxx>

class CEnumObjectNumbers;

class CModifyIdentDlg : public CPropertyPage { 
private:
	DWORD m_dwFlags;

	CheckBox m_cbAddToView;
	PushButton m_pbDefine;
	CSelIdentListView *m_pIdents;
	LONG m_lResult;			// selektierter Ident
	bool m_fAddToView;

	CEnumObjectNumbers *m_pIEnumObjs;

	void AdjustOK (bool fDisableNext = false);

protected:
	void WindowInit (Event);

	void OnItemChanged (NotifyEvt);
	int OnSetActive (NotifyEvt);
	int OnWizFinish (NotifyEvt);
	int OnWizNext (NotifyEvt);
	void OnCancel (NotifyEvt);
	void OnClick (NotifyEvt);
	void HelpRequest(HelpRequestEvt);

// ZugriffsFunktionen auf ausgewählte Identifikatoren
	bool GetSelectedIdent (long &rlIdent);
	int GetItemCount (void);

	bool PrepareResult (void);

// Konstruktor nicht direkt rufen
		CModifyIdentDlg (ResID uiRes, LPCSTR pcCaption, DWORD dwFlags);

	bool FInit (void);
	
public:
// Destruktor/Initialisierung
		~CModifyIdentDlg (void);
		
static CModifyIdentDlg *CreateInstance (ResID resID, LPCSTR pcCaption, DWORD dwFlags);
	
// InitialisierungsFuntkion zur anfänglichen Selektion einzelner Einträge
	bool SelectIdent (long lIdent, bool fSel = true);

	HRESULT SetEnumLONG (IEnum<LONG> *pIEnum);		// übergibt zu modifizierende Objektmenge
	HRESULT GetEnumLONG (IEnum<LONG> **ppIEnum);	// Fragt den Dialog nach seinen Daten 
};

#endif // _MODIDENT_HXX

