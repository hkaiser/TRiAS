// Deklarationen: Dialogfenster bei Bildung einer Schnittlinie	für Flächenteilung
// File: IntersectLineDlg.h
// W. Mörtl

#ifndef _INTERSECTLINEDLG_H
#define _INTERSECTLINEDLG_H


#include "SmartInterfaces.h"


///////////////////////////////////////////////////////////////////////////////////////////////
class CIntersectionLineDlg : public DialogWindow
{
private:
	pWindow m_pVWnd;		// TRiAS-ViewFenster
	CoordTransX* m_pCT;

	DoubleNumEditX m_X, m_Y;
	PushButton m_OKButton, m_DeleteButton;
	
	WObjektGeometrie m_wSectLine;	// editierte Schnittlinie
	int m_XLen;		// Anzahl der Vorkomma-Ziffern von m_X } bei metrischen
	int m_YLen;		// Anzahl der Vorkomma-Ziffern von m_Y } Koordinaten
	bool m_bIntern;		// Editierfelder m_X bzw. m_Y werden intern (true) bzw. extern durch
						// Anwender beeinflußt
	bool m_bGeodMod;	// in m_X bzw. m_Y wurden bei geodätischer Datenbank durch den Anwender
						// Änderungen vorgenommen

// Memberfunktionen	
	void StandardWerte (void);
	void OKButtonAction (void);
	void DeleteButtonAction (void);
	void PunktKorrigieren (void);

protected:
	void ButtonClick (ControlEvt e);	// Reaktion bei Button-Betätigung
	void EditChange (ControlEvt e);		// Reaktion bei Änderungen im Editierfenster

public:
		CIntersectionLineDlg (IObjektGeometrie* pISectLine);
		~CIntersectionLineDlg (void);

// weitere Memberfunktionen
	bool GetCoordinates (KoOrd& ResultX, KoOrd& ResultY);
	// "const" in der nachfolgenden Deklaration wird vom Compiler gefordert
	void SetOKButtonText (const char* pcText) { m_OKButton.SetText (pcText); }
};

#endif // _INTERSECTLINEDLG_H
