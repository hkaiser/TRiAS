// StatusDialog ---------------------------------------------------------------
// File: STATUS.HXX

#if !defined(_STATUS_HXX)
#define _STATUS_HXX

#define NUMLASTTIMES	5

#if defined(WIN32)

// WIN32 Version mit ProgressControl ------------------------------------------
class CStatusDlg : public ModeLessDialog {
private:
	LONG m_lRangeMin;
	LONG m_lRange;
	LONG m_lActPos;

	time_t m_tStartTime;
	time_t m_tUpdateTime;
	time_t m_tActTime;
	time_t m_tTimes[NUMLASTTIMES];

	long m_lKoeff;
	
	bool m_fWasInterrupted;
	bool m_fTimeShown;
	bool m_fIsShown;
	bool m_fUpdate;

	DWORD m_dwFlags;	

	PushButton CancelButton;
	CProgressCtrl m_gStatus;
	
	FixedText m_ftFile;
	FixedText m_ftFileName;
	FixedText m_ftStatus;
	FixedText m_ftResult;
	FixedText m_ftTimeText;
	FixedText m_ftTime;

	string m_strStatusText;

protected:
	void ButtonClick (ControlEvt);

	bool SetTime (time_t lTime, string &rStr, bool fFullTime = true);
	bool IntegrateTime (time_t lTime, time_t &rlAvTime);
	bool UpdateTime (LONG, time_t);
	bool UpdateStatus (int iPercent);

public:
		CStatusDlg (pWindow, ResID uiRes);
		~CStatusDlg (void);

	HRESULT SetFile (LPCSTR);
	HRESULT SetFileName (LPCSTR);
	HRESULT SetStatus (LPCSTR);
	HRESULT SetStatusText (LPCSTR);
	HRESULT SetResult (LPCSTR);

	bool FInit (LONG ulMin, LONG ulMax, DWORD dwFlags);
	int SetPos (ULONG lPos);
	bool Break (void) { 
		CallAppExec (ExecWhileEvent);  // bei Windows nachfragen
		return m_fWasInterrupted; 
	}
};
#else

// 16 Bit Version mit GaugeBox ------------------------------------------------
class CStatusDlg : public ModeLessDialog {
private:
	LONG m_lRangeMin;
	LONG m_lRange;
	LONG m_lActPos;

	time_t m_tStartTime;
	time_t m_tUpdateTime;
	time_t m_tActTime;
	time_t m_tTimes[NUMLASTTIMES];

	long m_lKoeff;
	
	bool m_fWasInterrupted;
	bool m_fTimeShown;
	bool m_fIsShown;
	bool m_fUpdate;

	DWORD m_dwFlags;	

	PushButton CancelButton;
	GaugeBox m_gStatus;
	
	FixedText m_ftFile;
	FixedText m_ftFileName;
	FixedText m_ftResult;
	FixedText m_ftTimeText;
	FixedText m_ftTime;

	string m_strStatusText;

protected:
	void ButtonClick (ControlEvt);

	bool SetTime (time_t lTime, string &rStr, bool fFullTime = true);
	bool IntegrateTime (time_t lTime, time_t &rlAvTime);
	bool UpdateTime (LONG, time_t);
	bool UpdateStatus (int iPercent);

public:
		CStatusDlg (pWindow, ResID uiRes);
		~CStatusDlg (void);

	HRESULT SetFile (LPCSTR);
	HRESULT SetFileName (LPCSTR);
	HRESULT SetStatus (LPCSTR);
	HRESULT SetStatusText (LPCSTR);
	HRESULT SetResult (LPCSTR);

	bool FInit (LONG ulMin, LONG ulMax, DWORD dwFlags);
	int SetPos (ULONG lPos);
	bool Break (void) { 
		CallAppExec (ExecWhileEvent);  // bei Windows nachfragen
		return m_fWasInterrupted; 
	}
};
#endif

#define PI_MIN_UPDATETIME	500		// nur aller 500 ms Prozente ändern

#endif // _STATUS_HXX
