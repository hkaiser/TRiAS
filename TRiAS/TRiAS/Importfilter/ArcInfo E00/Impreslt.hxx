// Fenster, welches das ImportErgebnis anzeigt ---------------------------------
// File: IMPRESLT.HXX

#if !defined(_IMPRESLT_HXX)
#define _IMPRESLT_HXX

class ImportResult : public DialogWindow {
private:
    FixedText TextCnt, LineCnt, AreaCnt, PointCnt, SumCnt, TableCnt, TimeText,
    		  NotImported, ReducedImported, BugImported;

protected:
    void __export ButtonClick (ControlEvt) { EndDlg (); }

public:
    ImportResult (pWindow pParent, ResourceFile *pRF, DWORD dwParseTime,
				  char *pCoverName);
    ~ImportResult (void) {}
};

#endif // _IMPRESLT_HXX
