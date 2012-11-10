// Auswahl der RechercheErgebnisse --------------------------------------------
// File: RECHRES.HXX

#if !defined(_RECHRES_HXX)
#define _RECHRES_HXX

#include <selidlvc.hxx>
#include <bmpbtn.hxx>

DefineSmartInterface(ObjectProperty);
DefineSmartInterface(ObjectProps);

class CRechResultDlg : 
	public DialogWindow 
{
private:
	DWORD m_fHideFlags;		// welche Info soll nicht angezeigt werden
	DWORD m_fSortFlags;		// nach welchem Feld soll sortiert werden
	DWORD m_fHideDataTips;	// WerteTips anzeigen

	CheckBox m_cbIdent;
	CheckBox m_cbObjTyp;
	CheckBox m_cbDataTips;
	CheckBox m_cbDataSource;
	CheckBox m_cbObjProp;

	PushButton m_pbOK;
	PushButton m_pbSelAll;	
	CSelIdentListViewWindow *m_pIdents;
	
	RadioButton m_rbObjTyp;		// Auswahl sortieren nach 
	RadioButton m_rbIdent;
	RadioButton m_rbOProp;

	CBmpButton m_SelObjProp;	// Objekteigenschaften
	SingleLineEdit m_sleObjProp;

	DatenBasisObjekt &m_rDBO;

// zu Controls gehörende Variablen
	WObjectProps m_Props;
	WObjectProperty m_ObjProp;
	string m_strActOProp;
	
protected:
	void ButtonClick (ControlEvt e);
	void OnDeleteItem (NotifyEvt e);
	void OnDeleteAllItems (NotifyEvt e);
	LRESULT Dispatch (Event e);
	BOOL OnNotify (NotifyEvt e);

	void AdjustOK (void);

	void AdjustRadios (short iSort);
	BOOL ShowObjPropDlg (void);
	HRESULT RetrieveObjProp (LPCSTR pcName, IObjectProps *pIProps, IObjectProperty **ppIOP);
	
public:
		CRechResultDlg (pWindow pW, DatenBasisObjekt &rDBO);
		~CRechResultDlg (void);
		
static CRechResultDlg *CreateInstance (pWindow pW, DatenBasisObjekt &rDBO, IObjectProps *pProps);

	bool FInit (IObjectProps *pProps);
	
// ZugriffsFunktionen auf ausgewählte Identifikatoren
	bool GetFirstIdent (long &rlIdent, short &riOTyp);
	bool GetNextIdent (long &rlIdent, short &riOTyp);
	bool SelectIdents (long lIdent, short iOTyp);

	UINT GetNoSelected (void) { return (*m_pIdents)->GetSelectedCount(); }

	string GetActOProp (void);
	void SetActOProp (LPCSTR pName);

inline DWORD GetHideFlags (void) { return m_fHideFlags|m_fSortFlags|m_fHideDataTips; }
	void SetHideFlags (DWORD iHideFlags);
};

#endif // _RECHRES_HXX
