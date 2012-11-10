// Deklarationen: Dialog für Modifikation von Stützpunktkoordinaten
// File: EditCoordDlg.h
// W. Mörtl
      
      
#ifndef _EDITCOORDDLG_H
#define _EDITCOORDDLG_H


#include "BmpBtn.h"			// CBmpButton

#include "SmartInterfaces.h"


///////////////////////////////////////////////////////////////////////////////////////////////
class CEditCoordDlg : public CPropertyPage
{
private:
	pWindow m_pVWnd;		// TRiAS-ViewFenster
	CoordTransX* m_pCT;		// KoordinatenTransformation

	DoubleNumEditX m_X, m_Y;

//	PushButton m_DeleteButton;
	CBmpButton m_DeleteButton;
	FixedText m_DeleteText;

	CEditDlg* m_pED;		// die zugehörige PropertySheet
	WObjektGeometrie m_wObj;// editiertes Objekt (Zeiger auf das Objekt, das in der
							//  PropertySheet gehalten wird)
	KoOrd m_lX;				// übergebene x-Koordinate
	KoOrd m_lY;				// übergebene y-Koordinate
	short m_iObjTyp;		// ObjektTyp,
	long m_lCnt;			//  Gesamtanzahl der Stützpunkte,
	short m_iKCnt;			//  Größe des Konturfeldes,
	KoOrd* m_plX;			//  Feld der x-Koordinaten,
	KoOrd* m_plY;			//  Feld der y-Koordinaten
	long* m_plCnt;			//  Anzahl der Stützpunkte in Konturen des editierten Objektes

	int m_XLen;				// Anzahl der Vorkomma-Ziffern von m_X } bei metrischen
	int m_YLen;				// Anzahl der Vorkomma-Ziffern von m_Y } Koordinaten
	bool m_bIntern;			// Editierfelder m_X bzw. m_Y werden intern (true) bzw. extern
							// durch Anwender beeinflußt
	bool m_bGeodMod;		// in m_X bzw. m_Y wurden bei geodätischer Datenbank
							// durch den Anwender Änderungen vorgenommen
		
	int m_iCloseCnt;		// Anzahl der gleichzeitig zu verlängernden Linienobjekte
	KoOrd* m_plCloseX;		// Koordinaten der Endpunkte aller zu verlängernden Linienobjekte
	KoOrd* m_plCloseY;		// (werden für das Zuziehen und für den Test, ob Fortsetzen möglich
							// ist, benötigt)
	bool m_bContBt;			// Zustand des ContinueButton retten
	bool m_bIslBt;			// Zustand des IsIslandButton retten
	bool m_bOKBt;			// Zustand des OKButton retten

	long m_lComONr;			// Objektnummer des Objektes, von dem bei CommonBorder die
							// Stützpunkte zu übernehmen sind


	bool StandardWerte (int iCloseCnt, KoOrd* plCloseX, KoOrd* plCloseY, KoOrd x, KoOrd y);
	void EditChange (ControlEvt e);
	bool ControlsSetting (void);
	void DeleteButtonAction (void);
	void ButtonSettingAfterDelete (void);
	void TestClosedLine (void);
		
protected:
	void WindowInit (Event e);
	void ButtonClick (ControlEvt e);
	BOOL OnOK (NotifyEvt);
	BOOL OnSetActive (NotifyEvt);
	BOOL OnKillActive (NotifyEvt);
	BOOL DrawEntireItem (DrawItemEvt);	// Element vollständig malen
	BOOL DrawItemFocus (DrawItemEvt);	// Element mit Focus zeichnen
	BOOL DrawItemSelect (DrawItemEvt);	// Element ausgewählt zeichnen

public:
	// Konstruktor/Destruktor
		CEditCoordDlg (int iCloseCnt, KoOrd* plCloseX, KoOrd* plCloseY, KoOrd x = -1,
					   KoOrd y = -1);
		~CEditCoordDlg (void);

	// Memberfunktionen
	bool PunktKorrigieren (void);

};

#endif  // _EDITCOORDDLG_H
