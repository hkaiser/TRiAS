// Fenster, welches das ImportErgebnis anzeigt ---------------------------------
// File: IMPRESLT.HPP

#if !defined(_IMPRESLT_HPP)
#define _IMPRESLT_HPP

class ImportResult : public DialogWindow {
private:
    FixedText TextCnt, LineCnt, AreaCnt, PointCnt, SumCnt, TimeText,
    		  NotImported, BugImported;

protected:
#ifdef WIN32
    void ButtonClick (ControlEvt) { EndDlg (); }
#else
	void __export ButtonClick (ControlEvt) { EndDlg (); }
#endif

public:
    ImportResult (pWindow pParent, ResourceFile *pRF, DWORD dwParseTime);
    ~ImportResult (void) {}
};

#endif // _IMPRESLT_HPP
