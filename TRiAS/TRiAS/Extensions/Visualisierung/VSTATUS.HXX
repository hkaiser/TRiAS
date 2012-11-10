// Fenster, welches, den ExportStatus anzeigt ---------------------------------
// File: VSTATUS.HXX

#if !defined(_VSTATUS_HXX)
#define _VSTATUS_HXX

class CStatus : public ModeLessDialog {
private:
	bool m_fWasInterrupted;
	GaugeBox m_gStatusGauge;
	FixedText m_ftComment;
	
	char *m_pView;
	short m_iIdBase;

protected:
	void ButtonClick (ControlEvt);

public:
		CStatus (pWindow pW, short iRange, 
			 ResourceFile *pRF, short iIdBase);
		~CStatus (void);

	void SetViewName (char *pView = NULL);
	void SetHandledItem (long lIdent, bool fRePaint = false);
	void SetHandledItem (char *pUIdent, bool fRePaint = false);
	
	void SetDeltaPos (short iCnt) { m_gStatusGauge.SetDeltaPos (iCnt); }
	void SetPosition (short iCnt) { m_gStatusGauge.SetPosition (iCnt); }

	bool Break (void) { 
		App :: Exec (ExecWhileEvent);  // bei Windows nachfragen
		return m_fWasInterrupted; 
	}
	void SetComment (char *pText) { m_ftComment.SetText (pText); }
	void GetComment (char *pBuffer, int iLen) { m_ftComment.GetText (pBuffer, iLen); }
};

#endif // _VSTATUS_HXX
