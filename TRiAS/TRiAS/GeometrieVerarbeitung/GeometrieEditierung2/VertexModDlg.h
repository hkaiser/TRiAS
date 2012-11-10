// Deklarationen: Dialogfenster für manuelle Modifizierung von Stützpunkten
// File: VertexModDlg.h
// W. Mörtl

#ifndef _VERTEXMODDLG_H
#define _VERTEXMODDLG_H


#include "SmartInterfaces.h"



///////////////////////////////////////////////////////////////////////////////////////////////
class CVertexModifyDlg : public DialogWindow
{
private:
	CoordTransX* m_pCT;

	DoubleNumEditX m_X, m_Y;
	PushButton m_OKButton, m_DeleteButton;
	
	int m_XLen;		// Anzahl der Vorkomma-Ziffern von m_X } bei metrischen
	int m_YLen;		// Anzahl der Vorkomma-Ziffern von m_Y } Koordinaten
	bool m_bIntern;		// Editierfelder m_X bzw. m_Y werden intern (true) bzw. extern durch
						// Anwender beeinflußt

// Memberfunktionen	
	void StandardWerte (KoOrd x, KoOrd y, bool bDel);

protected:
	void ButtonClick (ControlEvt e);	// Reaktion bei Button-Betätigung
	void EditChange (ControlEvt e);		// Reaktion bei Änderungen im Editierfenster

public:
		CVertexModifyDlg (KoOrd x, KoOrd y, bool bDel = true);
		~CVertexModifyDlg (void);

// weitere Memberfunktionen
	bool GetCoordinates (KoOrd& ResultX, KoOrd& ResultY);
	void SetPosition (Point RMPt);
};

#endif // _VERTEXMODDLG_H
