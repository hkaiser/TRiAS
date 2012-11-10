// Fenster, welches, den ImportStatus anzeigt ---------------------------------
// File: RECHSTAT.HPP

#if !defined(_RECHSTAT_HPP)
#define _RECHSTAT_HPP

class RechercheStatus : public ModeLessDialog {
private:
    ulong _AllCnt;
    short _CurrVal;
    Bool _wasInterrupted;
    GaugeBox _Status;
	
protected:
    inline void ButtonClick (ControlEvt);

public:
	FixedText _ActionText;	
    RechercheStatus (pWindow pW, ResourceFile *pRF);
	~RechercheStatus (void) {}

	void SetParams (ulong AllCnt, char *pCaption, char *pActionText, ResourceFile *pRF);
    void SetValue (ulong newCnt, long ObjNr = 0);
    void SetMax (ulong AllCnt) { _AllCnt = AllCnt; }
    Bool Break (void) {
	App :: Exec (ExecWhileEvent);  // bei Windows nachfragen
	return _wasInterrupted;
    }
};

#endif // _RECHSTAT_HPP
