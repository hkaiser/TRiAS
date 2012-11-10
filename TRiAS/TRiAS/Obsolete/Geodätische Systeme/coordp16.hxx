// EigenschaftsDialogfenster --------------------------------------------------
// File: COORDP16.HXX

#if !defined(_COORDP16_HXX)
#define _COORDP16_HXX

enum COORDTRANSFORMTYPE {
	CTF_Native = 0,
	CTF_Geodetical = CTF_Native,	// geodätische Koordinatendarstellung
	CTF_TransMercator = 1,			// Gauß/Krüger Koordinatendarstellung
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

#if !defined(WIN32)

class CCTFParams16 : public DialogWindow {
private:
// direkter Zugriff auf Parameter
	COORDTRANSFORMTYPE &m_rCTFType;
	COORDTRANSFORMMODE &m_rCTFMode;
	int &m_riMeridian;
	int &m_riStrBreite;

	int m_iMin3, m_iMax3;		// min/Max. Streifen dieser GeoDB
	int m_iMin6, m_iMax6;

	FixedText m_ftMeridian;
	ComboBox m_cbMeridian;
	FixedText m_ftStrBreite;
	ComboBox m_cbStrBreite;
	RadioButton m_rbNative;
	RadioButton m_rbTransMerc;
	CheckBox m_cbSave;
	RadioButton m_rbAutoMeridian;
	RadioButton m_rbSelectMeridian;

	void SwitchState (COORDTRANSFORMTYPE rgCTF, 
			COORDTRANSFORMMODE rgCFMode = CTFMODE_AutoMeridian);
	void FillMeridian (int iStrBreite, int iMeridian);
	void CalcMeridians (void);

protected:
	void ButtonClick (ControlEvt e);
	void ListBoxSel (ControlEvt e);

public:
		CCTFParams16 (pWindow pParent, ResID resID, COORDTRANSFORMTYPE &rCTF, 
			    COORDTRANSFORMMODE &rCTFMode, int &iM, int &iS);
		~CCTFParams16 (void);

	int GetMeridian (void);
	int GetStrBreite (void);
};
#endif // !WIN32

#endif // _COORDP16_HXX
