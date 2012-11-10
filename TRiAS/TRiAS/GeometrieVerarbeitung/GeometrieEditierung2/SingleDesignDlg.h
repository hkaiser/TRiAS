// Deklarationen: Dialogfenster für Bildung von einfachen Hilfslinien
// File: SingleDesignDlg.h
// W. Mörtl

#ifndef _SINGLEDESIGNDLG_H
#define _SINGLEDESIGNDLG_H



///////////////////////////////////////////////////////////////////////////////////////////////
class CSingleDesignDlg : public CPropertyPage
{
private:
	class CDesignDlg* m_pDesDlg;	// die zugehörige PropertySheet

	RadioButton m_RBttnSegment, m_RBttnLine, m_RBttnCircle;
	RadioButton m_RBttnAngle90, m_RBttnAngleFree;
	DoubleNumEditX m_Angle, m_Length;
	FixedText m_TextLength;

	bool m_bWithAngle;		// Winkel aktivieren (true); Winkel wird deaktiviert, wenn das
							// Bezugsobjekt ein Punktobjekt ist bzw. bisher nur 1 Stützpunkt
							// von einem Linienobjekt oder einer Flächenkontur editiert wurde
	RestrType m_ResType;	// Form der Konstruktionshilfslinie (STRECKE, GERADE, KREIS)
	bool m_bValidAngle;		// es wurde ein GÜLTIGER Winkel vorgegeben (true)
	bool m_bRightAngle;		// rechter Winkel (true)
	double m_dRelAngle;		// Winkel für Hilfslinie
	bool m_bValidLength;	// es wurde eine GÜLTIGE Länge vorgegeben (true)
	double m_dLength;		// Länge der Hilfslinie

	bool m_bIntern;			// Editierfelder m_Angle bzw. m_Length werden intern (true) bzw.
							// extern (false) durch Anwender modifiziert

// Memberfunktionen	
	void ControlsSetting (void);
	bool AdjustOK (void);
//	bool GetStringParameter (DoubleNumEditX* pEingWert, string& sParam);

protected:
	void WindowInit (Event e);	
	BOOL OnOK (NotifyEvt);
	BOOL OnSetActive (NotifyEvt);
	LRESULT Dispatch (Event e);
	BOOL OnKillActive (NotifyEvt);
	void ButtonClick (ControlEvt e);	// Reaktion bei Button-Betätigung
	void EditChange (ControlEvt e);		// Reaktion bei Änderungen im Editierfenster

public:
		CSingleDesignDlg (RestrType ResType, bool bRightAngle, double dRelAngle,
						  double dLength, bool bWithAngle);
		~CSingleDesignDlg (void);

// weitere Memberfunktionen
	RestrType GetRestrTyp (void) { return m_ResType; }
	bool GetAngleTyp (void) { return m_bRightAngle; }
	double GetRelAngle (void) { return m_dRelAngle; }
	double GetLength (void) { return m_dLength; }
};

#endif // _SINGLEDESIGNDLG_H
