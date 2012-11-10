// StatusDialog ---------------------------------------------------------------
// File: STATUS.HXX

#if !defined(_STATUS_HXX)
#define _STATUS_HXX

#define NUMLASTTIMES	5

#if defined(WIN32)

#if defined (_USE_TIMEGETTIME)
#include <dllbind.hxx>

class CWinMMBind :
	public DLLBind 
{
private:
	typedef DWORD (WINAPI * TIMEGETTIMEPROC)(void);

	TIMEGETTIMEPROC m_pTimeGetTime;
	bool m_fIsValid;

public:
		CWinMMBind (void);

	DWORD timeGetTime (void);
	bool IsValid (void) { return m_fIsValid; }
};

#endif // _USE_TIMEGETTIME

// WIN32 Version mit ProgressControl ------------------------------------------
class CStatusDlg : 
	public ModeLessDialog 
{
private:
	LONG m_lRangeMin;
	LONG m_lRange;
	LONG m_lActPos;
	LONG m_lLastSetting;

	time_t m_tStartTime;
	time_t m_tUpdateTime;
	time_t m_tActTime;
	time_t m_tTimes[NUMLASTTIMES];

	long m_lKoeff;
	
	bool m_fWasInterrupted;
	bool m_fTimeShown;
	bool m_fIsShown;
	bool m_fUpdate;
	bool m_fAVIStarted;
	bool m_fDoNotShowTimeAnyFurther;
	bool m_fTimeWasShownOnce;

	DWORD m_dwFlags;	

	PushButton CancelButton;
	CProgressCtrl m_gStatus;
	CAnimateCtrl m_aviAction;
	
	FixedText m_ftFile;
	FixedText m_ftFileName;
	FixedText m_ftStatus;
	FixedText m_ftResult;
	FixedText m_ftTimeText;
	FixedText m_ftTime;

	string m_strStatusText;

protected:
	void ButtonClick (ControlEvt);
	LRESULT Dispatch (Event e);

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

	bool FInit (LONG ulMin, LONG ulMax, DWORD dwFlags, bool fFlagsOnly = false);
	bool HandleFlags (DWORD dwFlags);

	int SetPos (ULONG lPos);
	bool Break (void) { 
		CallAppExec (ExecWhileEvent);  // bei Windows nachfragen

		// JG MsgQueue leeren
		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, /*PM_NOEVENTS |*/ PM_REMOVE))
			   DispatchMessage(&msg);

		return m_fWasInterrupted; 
	}

	LONG GetActPos (void) { return m_lLastSetting; }

	HRESULT GetRange (ULONG *plMin, ULONG *plMax);
	DWORD GetFlags (void) { return m_dwFlags; }
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
