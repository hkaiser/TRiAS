// @doc 
// @module Saveopt.hxx | Einstellung der Speicheroptionen

#if !defined(_SAVEOPT_HXX__2A3F6966_F353_11D2_9BEF_9A9220524153__INCLUDED_)
#define _SAVEOPT_HXX__2A3F6966_F353_11D2_9BEF_9A9220524153__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

class CSaveOptionsDlg : 
	public CPropertyPage
{
private:
	CSpinButtonCtrl m_scMinutes;
	CheckBox m_cbAutoSave;
	CheckBox m_cbTipOfTheDay;
	CheckBox m_cbStartDlg;
	CheckBox m_cbBackupFiles;
		
	SingleLineEdit m_sleMinutes;

	int m_iMinutes;
	Window *m_pW;
			
protected:
	void EditFocusChg (EditFocusChgEvt);
	void ButtonClick (ControlEvt e);
	void WindowInit (Event e);
	void VertScroll (ScrollEvt e);
	BOOL OnOK (NotifyEvt e);
		
public:
		CSaveOptionsDlg (pWindow);
		~CSaveOptionsDlg (void);

	int SaveDelta (void) { return m_iMinutes; }
};

#endif // !defined(_SAVEOPT_HXX__2A3F6966_F353_11D2_9BEF_9A9220524153__INCLUDED_)
