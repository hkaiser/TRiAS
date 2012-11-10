// EigenschaftsDialogfenster --------------------------------------------------
// File: COORDPAR.HXX

#if !defined(_COORDPAR_HXX)
#define _COORDPAR_HXX

#include <numeditx.hxx>
#include <dblnumex.hxx>

enum COORDTRANSFORMMODE {
	CTFMODE_AutoMeridian = 0,
	CTFMODE_SelectMeridian = 1,
};

class CCTFParams : public CPropertyPage {
private:
// direkter Zugriff auf Parameter
	COORDTRANSFORMMODE &m_rCTFMode;
	int &m_riMeridian;
	int &m_riStrBreite;
	int &m_riPrec;
	double &m_rdScale;

	int m_iMin3, m_iMax3;		// min/Max. Streifen dieser GeoDB
	int m_iMin6, m_iMax6;

	ComboBox m_cbMeridian;
	ComboBox m_cbStrBreite;
	RadioButton m_rbAutoMeridian;
	RadioButton m_rbSelectMeridian;

	CSpinButtonCtrl m_sbPrec;
	SingleLineEdit m_slePrec;
	CSpinButtonCtrl m_sbScale;
	DoubleNumEditX m_dneScale;

	FixedText m_ftCoordSys;

	HFONT m_hFont;

	void SwitchState (COORDTRANSFORMMODE rgCTFMode = CTFMODE_AutoMeridian);
	void FillMeridian (int iStrBreite, int iMeridian);
	void CalcMeridians (void);

protected:
	void EditChange (ControlEvt e);
	bool OnOK (NotifyEvt e);
	void WindowInit (Event);
	void ButtonClick (ControlEvt e);
	void ListBoxSel (ControlEvt e);
	bool OnDeltaPos (NotifyEvt e);

public:
		CCTFParams (ResID resID, ResID resIDCap, COORDTRANSFORMMODE &rCTFMode, 
					int &iM, int &iS, int &riPrec, double &rdScale);
		~CCTFParams (void);

	int GetMeridian (void);
	int GetStrBreite (void);
	int GetPrecision (void)	{ return m_sbPrec.GetPos();	}
	double GetScaling (void);
};

#endif // _COORDPAR_HXX
