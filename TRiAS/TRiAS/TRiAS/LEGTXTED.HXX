// LegendenText editieren -----------------------------------------------------
// File: LEGTXTED.HXX

#if !defined(_LEGTXTED_HXX)
#define _LEGTXTED_HXX

#include "triasres.h"

class CEditLegTextDlg : 
	public DialogWindow 
{
private:
	FixedText m_ftPrompt;
	MultiLineEdit m_mleText;
	PushButton m_pbOK;
#if defined(WIN16)
	PushButton m_pbHelp;
#endif // WIN16
	
	char *m_pBuffer;
	
protected:
	void ButtonClick (ControlEvt);
	void EditChange (ControlEvt);
	
public:
		CEditLegTextDlg (pWindow pW, UINT uiResCap, UINT uiResPrompt);
		~CEditLegTextDlg (void);
		
static CEditLegTextDlg *CreateInstance (
	pWindow pW, LPCSTR pText, UINT uiResCap = IDS_MODIFYLEGENTRYTEXT_CAP, UINT uiResPrompt = IDS_EDITLEGENTRYTEXT);

	BOOL FInit (LPCSTR pText);

inline	char *& GetNewText (void) { return m_pBuffer; }
};

char *ConvertToEscape (LPCSTR pText, LPCSTR srch);
char *ConvertFromEscape (LPCSTR pText, LPCSTR srch);

#endif // _LEGTXTED_HXX

