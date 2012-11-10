// Fenster, welches, den ImportStatus anzeigt ---------------------------------
// File: RECHSTAT.HXX

#if !defined(_RECHSTAT_HXX)
#define _RECHSTAT_HXX

class RechercheStatus : public ModeLessDialog {
private:
    long _AllCnt;
    short _CurrVal;
    FixedText _Elem, _Elem2;

    Bool _wasInterrupted;
    GaugeBox _Status;

protected:
    void __export ButtonClick (ControlEvt) { _wasInterrupted = TRUE; }

public:
    RechercheStatus (pWindow pW, ResourceFile *pRF, long AllCnt = 0, 
					 pchar pCaption = NULL);
    ~RechercheStatus (void) {}

    void SetValue (long newCnt, long ObjNr = 0);
    void SetMax (long AllCnt) { _AllCnt = AllCnt; }
    Bool Break (void)	{
							App :: Exec (ExecWhileEvent);  // bei Windows nachfragen
							return _wasInterrupted;
						}
    void SetElemText (const char *pText) { _Elem.SetText (pText); }
	void SetElem2Text (const char  *pText) { _Elem2.SetText (pText); }
	void ReInit (long lMaxVal = 0, long lActVal = 0,
				 const char *pCaption = NULL, const char *pElemText = NULL, 
				 const char *pElem2Text = NULL);
};

#endif // _RECHSTAT_HXX
