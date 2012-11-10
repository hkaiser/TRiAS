// PropertySheets mit dem TRiAS®-Framework ------------------------------------
// File: PROPSHTS.HXX

#if !defined(_PROPSHTS_HXX)
#define _PROPSHTS_HXX

class _TF_ENTRY32 CPropertyPage : public DialogWindow {
private:
	void Show (ShowState);		// darf nicht gerufen werden

public:
		CPropertyPage (ResID nTemplate, LPCSTR pCaption = NULL);
		~CPropertyPage (void);

// CancelToClose: Changes the Cancel button to read Close after an unrecoverable change in the page of a modal property sheet.
	void CancelToClose (void);
// SetModified: Call to activate or deactivate the Apply Now button.
	void SetModified (bool bChanged = true);

// OnCancel: Called by the framework when the Cancel button is clicked.
virtual	void OnCancel (ControlEvt e);
// OnOK: Called by the framework when the OK, Apply Now, or Close button is clicked.
virtual bool OnOK (ControlEvt e);
// OnSetActive: Called by the framework when the page is made the active page.
virtual int OnSetActive (ControlEvt e);
// OnKillActive: Called by the framework when the current page is no longer the active page. Perform data validation here.
virtual bool OnKillActive (ControlEvt e);
};

class _TF_ENTRY32 CPropertySheet : public Window {
public:
		CPropertySheet (LPCSTR pszCaption, Window *pParentWnd = NULL, 
				UINT iSelectPage = 0);
		~CPropertySheet (void);

// GetPageCount: Retrieves the number of pages in the property sheet.
	int GetPageCount (void);
// GetPage: Retrieves a pointer to the specified page.
	CPropertyPage* GetPage (int nPage) const;

// Show: Displays a modal property sheet.
	void Show (ShowState = Normal);
// AddPage: Adds a page to the property sheet.
	void AddPage (CPropertyPage *pPage);
// RemovePage: Removes a page from the property sheet.
	void RemovePage (CPropertyPage *pPage);
	void RemovePage (int nPage);
// EndDialog: Terminates the property sheet.
	void EndDialog (int nEndID = 0);
// SetCurSel: Aktivieren einer Seite
	void SetCurSel (CPropertyPage *pPage);
	void SetCurSel (int nPage);
// Apply: löst 'Apply' aus
	void Apply (void);
};

#endif // _PROPSHTS_HXX
