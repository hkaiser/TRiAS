// EigenschaftsDialogfenster --------------------------------------------------
// File: COORDPAR.HXX

#if !defined(_COORDPAR_HXX)
#define _COORDPAR_HXX

enum COORDTRANSFORMTYPE {
	CTF_Native = 0,
	CTF_Geodetical = CTF_Native,	// geodätische Koordinatendarstellung
	CTF_TransMercator = 1,		// Gauß/Krüger Koordinatendarstellung
};

enum COORDTRANSFORMMODE {
	CTFMODE_AutoMeridian = 0,
	CTFMODE_SelectMeridian = 1,
};

enum COORDTRANSELLIPSE {
	CTFELLIPSE_Unknown = 0x8000,
#if defined(ELLIPSE_BESSEL)
	CTFELLIPSE_Bessel = 0,
	CTFELLIPSE_Krassovsky = 1,
	CTFELLIPSE_Etrs89 = 2,
#elif defined(ELLIPSE_KRASSOVSKI)
	CTFELLIPSE_Krassovsky = 0,
	CTFELLIPSE_Etrs89 = 1,
	CTFELLIPSE_Bessel = 2,
#elif defined(ELLIPSE_ETRS89)
	CTFELLIPSE_Etrs89 = 0,
	CTFELLIPSE_Bessel = 1,
	CTFELLIPSE_Krassovsky = 2,
#else
#error "No Ellipse defined!"
#endif
};

class CCTFParams : 
	public CPropertyPage 
{
private:
// direkter Zugriff auf Parameter
	COORDTRANSFORMTYPE &m_rCTFType;
	COORDTRANSFORMMODE &m_rCTFMode;
	int &m_riMeridian;
	int &m_riStrBreite;
	int &m_riPrec;
	COORDTRANSELLIPSE &m_rrgChangeEllipse;

	int m_iMin3, m_iMax3;		// min/Max. Streifen dieser GeoDB
	int m_iMin6, m_iMax6;

	FixedText m_ftMeridian;
	ComboBox m_cbMeridian;
	FixedText m_ftStrBreite;
	ComboBox m_cbStrBreite;
	RadioButton m_rbNative;
	RadioButton m_rbTransMerc;
	RadioButton m_rbAutoMeridian;
	RadioButton m_rbSelectMeridian;
	
	FixedText m_ftCoordSystem;
	ComboBox m_cbCoordSystem;

	CSpinButtonCtrl m_sbPrec;
	SingleLineEdit m_slePrec;

	HFONT m_hFont;

	void SwitchState (COORDTRANSFORMTYPE rgCTF, 
			COORDTRANSFORMMODE rgCTFMode = CTFMODE_AutoMeridian);
	void FillMeridian (int iStrBreite, int iMeridian);
	void CalcMeridians (void);

protected:
	void EditChange (ControlEvt e);
	bool OnOK (NotifyEvt e);
	void WindowInit (Event);
	void ButtonClick (ControlEvt e);
	void ListBoxSel (ControlEvt e);

public:
		CCTFParams (ResID resID, ResID resIDCap, 
			COORDTRANSFORMTYPE &rCTF, COORDTRANSFORMMODE &rCTFMode, 
			int &iM, int &iS, int &riPrec, COORDTRANSELLIPSE &rfCE);
		~CCTFParams (void);

	int GetMeridian (void);
	int GetStrBreite (void);
	int GetPrecision (void)	{ return m_sbPrec.GetPos();	}
};

#endif // _COORDPAR_HXX
