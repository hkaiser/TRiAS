// ErgebnisDialog -------------------------------------------------------------
// File: RESULT.HXX

#if !defined(_RESULT_HXX)
#define _RESULT_HXX

class CResultDlg : public DialogWindow {
private:
	FixedText m_ftTexts;
	FixedText m_ftPoints;
	FixedText m_ftLines;
	FixedText m_ftAreas;
	FixedText m_ftKomplex;

	FixedText m_ftWithErrors;
	FixedText m_ftImported;
	FixedText m_ftNotImported;

public:
	FixedText m_ftTime;

protected:
	void ButtonClick (ControlEvt);

	void SetFixedNumber (long lCnt, FixedText &ft);

public:
		CResultDlg (pWindow);
		~CResultDlg (void);

	void SetTexts (long lCnt);
	void SetPoints (long lCnt);
	void SetLines (long lCnt);
	void SetAreas (long lCnt);
	void SetKomplex (long lCnt);

	void SetWithErrors (long lCnt);
	void SetImported (long lCnt);
	void SetNotImported (long lCnt);
};

#endif // _RESULT_HXX
