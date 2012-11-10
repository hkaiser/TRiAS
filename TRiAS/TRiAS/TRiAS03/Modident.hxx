// Dialog, welcher einen Ident auswählbar macht, um Objekte umzuklassifizieren
// File: MODIDENT.HXX

#if !defined(_MODIDENT_HXX)
#define _MODIDENT_HXX

#include <selidlvc.hxx>
#include "propactb.hxx"	// JG

class CModifyIdentDlg : 
	public CPropertyPage,
	public CPropertyActionExtUsage
{
private:
	DWORD m_dwFlags;

	CheckBox m_cbAddToView;
	PushButton m_pbDefine;
	CSelIdentListViewWindow *m_pIdents;
	FixedText m_ftAdjustIdent;
	CheckBox m_cbAdjustIdent;

	LONG m_lResult;			// selektierter Ident
	bool m_fAddToView;
	bool m_fShowConnections;
	bool m_fCheckMode;
	bool m_fCheckModeChecked;
	int m_iCopyMode;		// 0: umklassifizieren, 1: kopieren + umklassifizieren
							// 2: kopieren, wenn andere Datenquelle, sonst umklassifizieren

	IEnum<LONG> *m_pIEnumObjs;
	class CModIDPropAct *m_pParent;

	void AdjustOK (bool fDisableNext = false);
	void AdjustCheckMode();

protected:
	void WindowInit (Event);

	void OnItemChanged (NotifyEvt);
	int OnSetActive (NotifyEvt);
	int OnWizFinish (NotifyEvt);
	int OnWizNext (NotifyEvt);
	void OnCancel (NotifyEvt);
//	void OnClick (NotifyEvt);
	void HelpRequest(HelpRequestEvt);
	void ButtonClick (ControlEvt e);

// ZugriffsFunktionen auf ausgewählte Identifikatoren
	bool GetSelectedIdent (long &rlIdent);
	int GetItemCount (void);

	bool PrepareResult (void);

	HRESULT RetrieveObjClassDesc (LONG lIdent, os_string &rStrOKS, os_string &rStrKText, os_string &rStrLText);
	HRESULT EnsureObjClass (HPROJECT hPrCls, LPCSTR pcOKS, LPCSTR pcKText, LPCSTR pcLText, LONG lONr, LONG *plIdent);
	friend DWORD __stdcall EnsureUnique (INT_PTR lIdent, DWORD dwTypes, UINT_PTR dwData);

// Konstruktor nicht direkt rufen
	CModifyIdentDlg (CModIDPropAct *pParent, ResID uiRes, LPCSTR pcCaption);

	bool FInit (void);

public:
// Destruktor/Initialisierung
	~CModifyIdentDlg (void);
	static CModifyIdentDlg *CreateInstance (CModIDPropAct *pParent, ResID resID, LPCSTR pcCaption);
	
	HPROPSHEETPAGE CreatePage (void) { return CPropertyPage::CreatePage(); }

	void SetFlags (DWORD dwFlags);
	bool ReInitList();

// InitialisierungsFuntkion zur anfänglichen Selektion einzelner Einträge
	int SelectIdent (long lIdent, bool fSel = true);
	void PrepareResultIdent();

	void SetSelectedIdent (long lIdent) { m_lResult = lIdent; }
	long GetSelectedIdent (void) { return m_lResult; }

	void SetAddToView (bool fAddToView) { m_fAddToView = fAddToView; }
	bool GetAddToView (void) { return m_fAddToView; }

	void SetShowConnections (bool fShowConnections) { m_fShowConnections = fShowConnections; }
	bool GetShowConnections (void) { return m_fShowConnections; }

	void SetCopyMode (int iCopyMode) { m_iCopyMode = iCopyMode; }

	HRESULT SetEnumLONG (IEnum<LONG> *pIEnum);		// übergibt zu modifizierende Objektmenge
	HRESULT GetEnumLONG (IEnum<LONG> **ppIEnum);	// Fragt den Dialog nach seinen Daten 

	HRESULT GetInputEnumLONG (IEnum<LONG> **ppIEnum)
	{
		if (NULL != m_pIEnumObjs)
			return m_pIEnumObjs -> QueryInterface(IID_IEnumLONG, (LPVOID *)ppIEnum);
		return E_UNEXPECTED;
	}

	void SetCheckMode (BOOL fCheckMode, BOOL fCheckModeChecked)
	{
		m_fCheckMode = fCheckMode;
		m_fCheckModeChecked = fCheckModeChecked;
		AdjustCheckMode();
	}
	void GetCheckMode (BOOL &rfCheckMode, BOOL &rfCheckModeChecked)
	{
		rfCheckMode = m_fCheckMode;
		rfCheckModeChecked = m_fCheckModeChecked;
	}

// Sonstiges
	void SetDirty (bool fDirty);
};

#endif // _MODIDENT_HXX

