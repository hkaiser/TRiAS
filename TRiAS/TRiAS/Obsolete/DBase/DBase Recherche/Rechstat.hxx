// Fenster, welches, den ExportStatus anzeigt ---------------------------------
// File: RECHSTAT.HXX

#if !defined(_RECHSTAT_HXX)
#define _RECHSTAT_HXX

class RechercheStatus : public ModeLessDialog {
private:
    long _AllCnt;
    short _CurrVal;
    GaugeBox _Status;
    FixedText GroupCount;
    Bool _wasInterrupted;

protected:
    void ButtonClick (ControlEvt) { _wasInterrupted = True; }

public:
    RechercheStatus (pWindow pW, ResourceFile &RF, long AllCnt = 1);
    ~RechercheStatus (void);

    void SetValue (long newCnt);
    void SetMax (long AllCnt) { _AllCnt = AllCnt; }
    void SetGroupText (short Cnt = 0);
    Bool Break (void) {
	App :: Exec (ExecWhileEvent);  // bei Windows nachfragen
	return _wasInterrupted;
    }
};

#endif // _RECHSTAT_HXX
