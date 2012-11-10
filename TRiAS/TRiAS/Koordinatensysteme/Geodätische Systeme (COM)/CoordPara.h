///////////////////////////////////////////////////////////////////////////
// @doc 
// @module CoordPara.h | Description goes here

#if !defined(_COORDPARA_H__60CD3E73_A796_11D1_A05F_0060975566B4__INCLUDED_)
#define _COORDPARA_H__60CD3E73_A796_11D1_A05F_0060975566B4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


typedef enum tagCOORDTRANSFORMTYPE {
	CTF_Native = 0,
	CTF_Geodetical = CTF_Native,	// geodätische Koordinatendarstellung
	CTF_TransMercator = 1,		// Gauß/Krüger Koordinatendarstellung
} COORDTRANSFORMTYPE;

typedef enum tagCOORDTRANSFORMMODE {
	CTFMODE_AutoMeridian = 0,
	CTFMODE_SelectMeridian = 1,
} COORDTRANSFORMMODE;

/*
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
*/

#endif // !defined(_COORDPARA_H__60CD3E73_A796_11D1_A05F_0060975566B4__INCLUDED_)
