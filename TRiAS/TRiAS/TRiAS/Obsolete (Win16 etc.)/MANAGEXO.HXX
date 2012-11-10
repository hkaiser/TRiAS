// Klassendefinition für das Erweiterung-Lade/Entlade Dialogfenster -----------
// File: MANAGEXT.HXX

#if !defined(_MANAGEXT_HXX)
#define _MANAGEXT_HXX

class CQueryExtensionNameDlg : public DialogWindow {
private:
	PushButton m_pbOK;
	SingleLineEdit m_sleExtName;
	FixedText m_ftQueryText;

protected:
	void ButtonClick (ControlEvt);
	void EditChange (ControlEvt);

public:
		CQueryExtensionNameDlg (pWindow, const string &);
		~CQueryExtensionNameDlg (void) {}

	bool GetExtName (string &strExtName);
};


class CManageExtDlg : public OwnerDrawDialogWindow {
private:
	CCheckListBox *m_pExtList;
	PushButton m_pbOK, m_pbCancel;
#if !defined(WIN32)
	PushButton m_pbHelp;
#endif // WIN32
	PushButton m_pbInstall, m_pbRemove;
	CheckBox m_cbShowAll;

	ExtensionList &m_rEL;	// Verweis auf ExtensionList
	int m_iCnt;

	char *m_pExtName;	// Bezeichner der Extension
	char *m_pDLLName;	// DLL-PfadName
	char *m_pBuffer;

	EXTENSIONFLAG m_rgFlags;

	unsigned int m_fToLoad : 1;
	unsigned int m_fToUnload : 1;
	unsigned int m_fClickHasToggled : 1;

	int m_iCurrIndex;	// derzeit aktiver Eintrag

	bool GetNames (int iIndex = LB_ERR);

	int InstallExtension (void);
	bool RemoveExtension (unsigned int uiID);

	bool InitExtList (bool fDelete = false);

protected:
	bool DrawEntireItem (DrawItemEvt);	// Element vollständig malen
	bool DrawItemFocus (DrawItemEvt);	// Element mit Focus zeichnen
	bool DrawItemSelect (DrawItemEvt);	// Element ausgewählt zeichnen
	bool DeleteItem (DeleteItemEvt);	// Element ist gelöscht

	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	void ListBoxClk (ControlEvt);		// DoppelKlick

public:
		CManageExtDlg (pWindow pW, ExtensionList &rEL);
		~CManageExtDlg (void);

static CManageExtDlg *CreateInstance (pWindow pW, ExtensionList &rEL);

	bool FInit (void);

// sonstige Member
	char * &GetExtName (void) const { return (char *&)m_pExtName; }
	char * &GetDLLName (void) const { return (char *&)m_pDLLName; }
	EXTENSIONFLAG GetFlags (void) { return m_rgFlags; }

	bool GetFirstExtName (void);
	bool GetNextExtName (void);

	bool toLoad (void) { return m_fToLoad ? true : false; }
	bool toUnload (void) { return m_fToUnload ? true : false; }

	bool isUnLoadable (void) { return m_rgFlags & EF_UnLoadable; }
};

bool FindExtNameFromDLLName (pWindow pW, string &strDLLName, string &strExtName,
			     const char *pShort);
bool CompareDLLName (string &strKey, string &strDLL);

#endif // _MANAGEXT_HXX
