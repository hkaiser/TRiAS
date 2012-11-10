// LegendenText editieren -----------------------------------------------------
// File: LEGTXTED.HXX

#if !defined(_LEGTXTED_HXX)
#define _LEGTXTED_HXX

class CEditLegTextDlg : public DialogWindow {
private:
	MultiLineEdit m_mleText;
	PushButton m_pbOK;
#if !defined(WIN32)
	PushButton m_pbHelp;
#endif // WIN32
	
	char *m_pBuffer;
	
protected:
	void ButtonClick (ControlEvt);
	void EditChange (ControlEvt);
	
public:
		CEditLegTextDlg (pWindow);
		~CEditLegTextDlg (void);
		
static CEditLegTextDlg *CreateInstance (pWindow pW, char *pText);

	BOOL FInit (char *pText);

inline	char *& GetNewText (void) { return m_pBuffer; }
};

char *ConvertToEscape (char *pText, char srch);
char *ConvertFromEscape (char *pText, char srch);

#endif // _LEGTXTED_HXX

