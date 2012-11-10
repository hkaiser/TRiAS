// TextRecherche parametrisieren

#if !defined(_TXTSRCHD_H)
#define _TXTSRCHD_H

#include <bmpbtn.hxx>

#include "propactb.hxx"
#include "ComboEditWnd.h"

///////////////////////////////////////////////////////////////////////////////
// PropertyPage für Textrecherche

///////////////////////////////////////////////////////////////////////////////
// SmartInterfaces et.al.

#if !defined(_DEFINED_OBJECTPROPS)
DefineSmartInterface(ObjectProperty);
DefineSmartInterface(ObjectProps);
#define _DEFINED_OBJECTPROPS
#endif // _DEFINED_OBJECTPROPS

#if !defined(_DEFINED_ENUMLONG)
#define _DEFINED_ENUMLONG
DefineSortingEnumerator(LONG);		// definiert SEnumLONG
DefineSmartEnumerator(LONG);		// definiert WEnumLONG (Wrapper für IEnum<LONG>)
#endif // CIID_LONGEnum
DefineEnumInputIterator(LONG);		// definiert InEnumLONG
DefineEnumOutputIterator(LONG);		// definiert OutEnumLONG

///////////////////////////////////////////////////////////////////////////////
// sonstige Typdefinitionen

class CCfgTextSearch : 
	public CPropertyPage,
	public CPropertyActionExtUsage
{
public:
	typedef list<os_string> CSearchList;
	
private:
	class CTextSearchEngine *m_pParent;
	CBmpButton m_SelRegExpr;
	CBmpButton m_SelObjProp;
	CheckBox m_cbCapital;
	CheckBox m_cbPartialMatch;
	CheckBox m_cbFuzzyMatch;
	CheckBox m_cbUseRegExpr;
	CheckBox m_cbTestBOB;
	CheckBox m_cbExistsOnly;
	CheckBox m_cbNegate;
	FixedText m_ftSearch;

	SingleLineEdit m_sleObjProp;
	ComboBox m_cbFindWhat;
	CComboEditWnd *m_pEdit;

	HMENU m_hMenu;
	DWORD m_dwFlags;
	BOOL m_fIsInitialized;

	SEnumLONG m_Objects;		// zu bearbeitende Objektmenge

// zu Controls gehörende Variablen
	WObjectProps m_Props;
	WObjectProperty m_ObjProp;

protected:
	LRESULT Dispatch (Event);
	void WindowInit (Event);
	void ButtonClick (ControlEvt);
	void MenuCommand (MenuCommandEvt);
	void EditChange (ControlEvt);
	void ListBoxSel (ControlEvt);

	int OnSetActive (NotifyEvt);
	void OnCancel (NotifyEvt);
	int OnWizNext (NotifyEvt);
	BOOL OnWizFinish (NotifyEvt);

	BOOL FInit (void) { return true; }
	BOOL ShowRegExprMenu (void);
	BOOL ShowObjPropDlg (void);

	void AdjustCheckBoxes(BOOL fRegExpr = true);
	void AddToSearchString (LPCSTR pcAdd, int iMoveCursor = 0);
	HRESULT RetrieveObjProp (LPCSTR, IObjectProps *pIProps, IObjectProperty **ppIOP);

	void DoUpdate (void);

// MenuCommands
	BOOL OnRegExprCommand (LPCSTR pcInsert, int iMove = 0);

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	BOOL AdjustOK (void);

	HRESULT GetMatchObject (DMatchString **ppIMatch);
	HRESULT GetMatchProperty (IObjectProperty **ppIOP);
	HRESULT TryToSearch (IObjectProperty *pIOP, ULONG ulCnt, IEnumObjectsByNumber **ppIEnum);

	HRESULT ResetEnumLONG (void);
	HRESULT GetEnumLONG (IEnum<LONG> **ppIEnumObjs);
	HRESULT SetEnumLONG (IEnum<LONG> *pIEnumObjs);

public:
		CCfgTextSearch (CTextSearchEngine *pParent, ResID uiDlg, LPCSTR pcCaption);
		~CCfgTextSearch (void);

static CCfgTextSearch *CreateInstance (CTextSearchEngine *pParent, ResID uiDlg, LPCSTR pcCaption);

	HPROPSHEETPAGE CreatePage (void) { return CPropertyPage::CreatePage(); }

public:
// Statusvariablen für Persistenz
	class CDlgStatus {
	public:
		BOOL m_fCapital;
		BOOL m_fPartialMatch;
		BOOL m_fFuzzyMatch;
		BOOL m_fUseRegExpr;
		BOOL m_fTestBOB;
		BOOL m_fExistsOnly;
		BOOL m_fNegate;

		os_string m_strObjProp;
		os_string m_strFindWhat;
		CSearchList m_lstFindWhat;

		void erase (void) 
		{ 
			m_strObjProp.erase();
			m_strFindWhat.erase();
			m_lstFindWhat.erase(m_lstFindWhat.begin(), m_lstFindWhat.end()); 
		}

		CDlgStatus (void) 
		{
			m_fCapital = m_fPartialMatch = m_fFuzzyMatch = false;
			m_fUseRegExpr = m_fTestBOB = m_fExistsOnly = false;
			m_fNegate = false;
		}
	};
	HRESULT InitWithData (CCfgTextSearch::CDlgStatus &rStatus);

private:
	CDlgStatus *m_pStatus;
};

#define MAXLASTITEMS	20		// Anzahl der gespeicherten letzten Suchstrings

#endif // _TXTSRCHD_H
