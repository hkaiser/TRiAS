// StatusDialog ---------------------------------------------------------------
// File: STATUS.HXX

#if !defined(_STATUS_HXX)
#define _STATUS_HXX

#define NUMLASTTIMES	5

class CStatusDlg : public ModeLessDialog {
private:
	long m_lRange;
	long m_lActPos;
	long m_lONr;
	long m_lActTime;
	long m_lTimes[NUMLASTTIMES];

	long m_lKoeff;
	
	bool m_fWasInterrupted;
	bool m_fTimeShown;

	PushButton CancelButton;
	CProgressCtrl m_gStatus;
	FixedText m_ftFileName;
	FixedText m_ftStatus;
	FixedText m_ftONr;
	FixedText m_ftTimeText;
	FixedText m_ftTime;

protected:
	void ButtonClick (ControlEvt);

	bool IntegrateTime (long lTime, long &rlAvTime);

public:
		CStatusDlg (pWindow);
		~CStatusDlg (void);

	bool FInit (long lSize, LPCSTR pFName);

	void SetPos (long lPos, long lONr);
	bool Break (void) { 
		App :: Exec (ExecWhileEvent);  // bei Windows nachfragen
		return m_fWasInterrupted; 
	}

friend	bool SetTime (long lCnt, FixedText &rft, bool fFullTime = true);
};


#endif // _STATUS_HXX
