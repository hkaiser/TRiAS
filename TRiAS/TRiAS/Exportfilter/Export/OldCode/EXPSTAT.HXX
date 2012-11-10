// Fenster, welches, den ExportStatus anzeigt ---------------------------------
// File: EXPSTAT.HXX

#if !defined(_EXPSTAT_HXX)
#define _EXPSTAT_HXX

// #if defined(WIN32)

#include <istatus.h>
#include <statguid.h>
#include <funcs03.h>

class ExportStatus {
private:
	LPPROGRESSINDICATOR m_pIStatus;

public:
		ExportStatus (pWindow pW, long AllCnt, LPCSTR pcFName);
		~ExportStatus (void);

	void SetValue (long newCnt, long lON = -1);
	bool Break (void);
	void Show (void) { SetValue(0); }
};

/*
#else

class ExportStatus : public ModeLessDialog {
private:
	long m_lAllCnt;
	Bool m_fWasInterrupted;
	char *m_pOutString;

	GaugeBox m_gStatus;
	PushButton CancelButton;

protected:
	void ButtonClick (ControlEvt);

public:
		ExportStatus (pWindow pW, long lAllCnt, LPCSTR pcFName);
		~ExportStatus (void);

	void SetValue (long newCnt, long ON = -1);
	Bool Break (void) { 
		App :: Exec (ExecWhileEvent);  // bei Windows nachfragen
		return m_fWasInterrupted; 
	}
};

#endif
*/
#endif // _EXPSTAT_HXX
