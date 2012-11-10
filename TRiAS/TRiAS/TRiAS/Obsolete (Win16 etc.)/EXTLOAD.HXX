// Klassendefinitionen fuer Laden- und Entfernen- Dlg von ErweiterungsDLLs
// File EXTLOAD.HXX


#if !defined(_EXTLOAD_HXX)
#define _EXTLOAD_HXX

class ExtLoadDLLDlg : public DialogWindow {
private:
	MultiSelListBox LoadList;
	PushButton OKButton, CancelButton, HelpButton;
	CheckBox PreLoad;

	char *m_pExtName;	// Bezeichner der ExtensionDLL
	char *m_pDLLName;	// DLL-PfadName
	char *m_pBuffer;
	unsigned int m_fUnLoadable : 1;

	EXTENSIONFLAG m_rgFlags;

	ExtensionList &m_rEL;	// Verweis auf ExtensionList

	bool GetNames (short iIndex);

protected:
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	void ListBoxClk (ControlEvt);

public:
		ExtLoadDLLDlg (pWindow, ExtensionList &);
		~ExtLoadDLLDlg (void);

static ExtLoadDLLDlg *CreateInstance (pWindow, ExtensionList &);

	bool FInit (void);

// sonstige Member
	char * &GetExtName (void) const { return (char *&)m_pExtName; }
	char * &GetDLLName (void) const { return (char *&)m_pDLLName; }
	bool isUnLoadable (void) { return m_fUnLoadable ? true : false; }

	bool GetFirstExtName (void);
	bool GetNextExtName (void);
	
	void SetPreLoadStatus (void);
	bool GetPreLoadStatus (void);

	EXTENSIONFLAG GetFlags (void) { return m_rgFlags; }
};

class ExtUnLoadDLLDlg : public DialogWindow {
private:
	MultiSelListBox UnLoadList;
	PushButton OKButton, CancelButton, HelpButton;

	char *m_pExtName;
	char *m_pDLLName;
	char *m_pBuffer;
	
	ExtensionList &m_rEL;

	bool GetNames (short iIndex);

protected:
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	void ListBoxClk (ControlEvt);

public:
		ExtUnLoadDLLDlg (pWindow, ExtensionList &);
		~ExtUnLoadDLLDlg (void);

static ExtUnLoadDLLDlg *CreateInstance (pWindow, ExtensionList &);

	bool FInit (void);

// sonstige Member
	char * &GetExtName (void) const { return (char *&)m_pExtName; }
	char * &GetDLLName (void) const { return (char *&)m_pDLLName; }

	bool GetFirstExtName (void);
	bool GetNextExtName (void);
};


#endif // _EXTLOAD_HXX

