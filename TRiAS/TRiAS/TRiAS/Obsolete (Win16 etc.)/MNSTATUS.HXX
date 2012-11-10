// StatusZeile für das TRiAS-Hauptfenster -------------------------------------
// File: MNSTATUS.HXX

#if !defined(_MNSTATUS_HXX)
#define _MNSTATUS_HXX

class CControlBar : public ControlWindow {
protected:
	LRESULT Default (Event e);

virtual	bool OnSizeParent (SIZEPARENTPARAMS *);

public:
		CControlBar (Control *pCtrl);
		~CControlBar (void);
};

class CTRiASStatus : public CControlBar {
private:

protected:

public:
		CTRiASStatus (void);
		~CTRiASStatus (void);

	operator CStatusBarCtrl &() const { return m_sbMain; }
};

#endif // _MNSTATUS_HXX
