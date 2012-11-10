// Deklarationen: Dialogfenster für die Auswahl der Fixpunkte für Hilfslinien
// File: FixPointsDlg.h
// W. Mörtl

#ifndef _FIXPOINTSDLG_H
#define _FIXPOINTSDLG_H



///////////////////////////////////////////////////////////////////////////////////////////////
class CFixPointsDlg : public CPropertyPage
{
private:
    CoordTransX* m_pCT;	// KoordinatenTransformation

	RadioButton m_RBttnClick, m_RBttnEnd1, m_RBttnEnd2, m_RBttnMiddle;
	FixedText m_RWertK, m_HWertK, m_RWert1, m_HWert1, m_RWert2, m_HWert2, m_RWertM, m_HWertM;

	// übergebene Koordinaten
	KoOrd m_lRWK, m_lHWK, m_lRW1, m_lHW1, m_lRW2, m_lHW2, m_lRWM, m_lHWM;
	EPunkt m_FixPkt;	// der ausgewählte Fixpunkt

	// Memberfunktionen	
	void ControlsSetting (void);
	void TextForEndpoints (void);

protected:
	void WindowInit (Event e);	
	BOOL OnSetActive (NotifyEvt);
	BOOL OnKillActive (NotifyEvt);

public:
		CFixPointsDlg (KoOrd lRWK, KoOrd lHWK, KoOrd lRW1, KoOrd lHW1, KoOrd lRW2, KoOrd lHW2);
		~CFixPointsDlg (void);

	// Memberfunktionen	
	EPunkt GetFixPoint (void) { return m_FixPkt; }
};

#endif // _FIXPOINTSDLG_H
