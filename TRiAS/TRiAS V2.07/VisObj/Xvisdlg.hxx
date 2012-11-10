// Dialogfenster zur Auswahl einer Symbolisierungsart -------------------------
// File: XVISDLG.HXX


#if !defined(_XVISDLG_HXX)
#define _XVISDLG_HXX

class CExtVisDlg : public DialogWindow {
private:
	PushButton m_pbOK;
#if !defined(WIN32)
	PushButton m_pbHelp;
#endif //!WIN32
	TabularListBox m_lbVisModules;
	
	ResourceFile &m_rRF;

	char *m_pModuleName;
	short m_iObjTyp;
		
#if defined(WIN32)
	bool LoadVisModuleRegistry (LPCSTR pcKey);
#endif //!WIN32
	short FillListBox (void);
	
protected:
	void ButtonClick (ControlEvt e);
	void ListBoxClk (ControlEvt e);
	
public:
		CExtVisDlg (pWindow pW, ResourceFile *pRF, short iVisTyp = VTDefault);
		~CExtVisDlg (void);
		
	short FInit ();
	char *& GetModuleName (void) { return m_pModuleName; }
};


#endif // _XVISDLG_HXX



