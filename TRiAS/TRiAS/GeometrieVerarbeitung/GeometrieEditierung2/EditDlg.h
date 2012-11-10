// Deklarationen: PropertySheet für EditierDialog
// File: EditDlg.h
// W. Mörtl
      

      
#ifndef _EDITDLG_H
#define _EDITDLG_H


#include "SmartInterfaces.h"
#include "PropExt.h"	// CEditObjectSheet


///////////////////////////////////////////////////////////////////////////////////////////////
class CEditDlg : public CEditObjectSheet
{
private:
	WEditExtensionSite m_wEdExSite;	// Interface von CGeoEditExtension für EditierOperationen

	PushButton m_OK, m_Cancel, m_Apply, m_Help;
	PushButton* m_pIslandButton;
	PushButton* m_pContinueButton;
	HFONT m_hF;					// Windows-Font eines Buttons

	WObjektGeometrie m_wObj;	// editiertes Objekt
	short m_iObjTyp;			// ObjektTyp,
	long m_lCnt;				//  Gesamtanzahl der Stützpunkte,
	short m_iKCnt;				//  Größe des Konturfeldes,
	long* m_plCnt;				//  Anzahl der Stützpunkte in Konturen

	bool m_bClosedLine;			// das neueditierte oder eines der zu verlängernden
								// Linienobjekte ist geschlossen (true)
	bool m_bCoordMod;			// Koordinaten wurden durch den Anwender in der
								// CEditCoordDlg-Page verändert

	long m_lComONr;				// Objektnummer des Objektes, von dem bei CommonBorder die
								// Stützpunkte zu übernehmen sind
	int m_iGrabCnt;				// Anzahl der GrabPunkte (für CommonBorder)
	bool m_bDelBttn;			// DeleteButton in CEditCoordDlg-Page wurde betätigt (true)


	void IslandButtonAction (void);
	bool AreaClose (void);

protected:
	void WindowInit (Event e);	
	void ButtonClick (ControlEvt e);

public:
	// Konstruktor/Destruktor
		CEditDlg (LPCSTR pszCaption, IObjektGeometrie* pIOG, long lComONr, int* piGrabCnt);
		~CEditDlg (void);

	// Zugriff auf Member
	const WObjektGeometrie& GetObject (void) const { return m_wObj; }
	void SetIslandButton (bool bEnable = true)
						  { bEnable ? m_pIslandButton->Enable() : m_pIslandButton->Disable(); }
	void SetContinueButton (bool bEnable = true)
					  { bEnable ? m_pContinueButton->Enable() : m_pContinueButton->Disable(); }
	void SetOKButton (bool bEnable = true) { bEnable ? m_OK.Enable() : m_OK.Disable(); }
	void SetCoordMod (bool bCoordMod) { m_bCoordMod = bCoordMod; }
	bool GetCoordMod (void) { return m_bCoordMod; }
	long GetComONr (void) { return m_lComONr; }
	void SetGrabCnt (int iGrabCnt) { m_iGrabCnt = iGrabCnt; }
	int GetGrabCnt (void) { return m_iGrabCnt; }
	void SetDelBttn (bool bDelBttn) { m_bDelBttn = bDelBttn; }
	bool GetDelBttn (void) { return m_bDelBttn; }

	// weitere Memberfunktionen
	void SetClosedLine (bool bClosedLine) { m_bClosedLine = bClosedLine; }
	bool GetClosedLine (void) { return m_bClosedLine; }
	bool IsContinueEnable (void);
	bool IsIslandEnable (void);
	bool IsOKEnable (void);
};

#endif  // _EDITDLG_H
