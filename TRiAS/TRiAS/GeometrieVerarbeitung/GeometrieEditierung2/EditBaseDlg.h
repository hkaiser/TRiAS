// Deklarationen: Dialog für die Grundfunktionen beim Editieren
// File: EditBaseDlg.h
// W. Mörtl
      
      
#ifndef _EDITBASEDLG_H
#define _EDITBASEDLG_H


#include "BmpBtn.h"			// CBmpButton

#include "SmartInterfaces.h"


///////////////////////////////////////////////////////////////////////////////////////////////
class CEditBaseDlg : public CPropertyPage
{
private:
	pWindow m_pVWnd;		// TRiAS-ViewFenster
	IdentList* m_pIL;		// Liste der Objektklassenschlüssel

	ComboBox m_IdentListe;
	CBmpButton m_CloseButton, m_CircleButton, m_ComBorderButton;
	FixedText m_OptionenText, m_ComBorderText, m_CircleText, m_CloseText;
	FixedIcon m_Border;
	            
	CEditDlg* m_pED;		// die zugehörige PropertySheet
	WObjektGeometrie m_wObj;// editiertes Objekt (Zeiger auf das Objekt, das in der
							//  PropertySheet gehalten wird)
	ulong m_ulIdent;		// selektierter Objektklassenschlüssel
	short m_iObjTyp;		// ObjektTyp,
	long m_lCnt;			//  Gesamtanzahl der Stützpunkte,
	short m_iKCnt;			//  Größe des Konturfeldes,
	KoOrd* m_plX;			//  Feld der x-Koordinaten,
	KoOrd* m_plY;			//  Feld der y-Koordinaten
	long* m_plCnt;			//  Anzahl der Stützpunkte in Konturen des editierten Objektes

	KoOrd* m_plGrabPktX;	// Koordinaten der GrabPunkte
	KoOrd* m_plGrabPktY;	//  (für CommonBorder)
	HRESULT m_hrComBorder;	// CommonBorder-Möglichkeit
	long m_lComONr;			// Objektnummer des Objektes, von dem bei CommonBorder die
							// Stützpunkte zu übernehmen sind
		
	int m_iCloseCnt;		// Anzahl der gleichzeitig zu verlängernden Linienobjekte
	KoOrd* m_plCloseX;		// Koordinaten der Endpunkte aller zu verlängernden Linienobjekte
	KoOrd* m_plCloseY;		// (werden für das Zuziehen und für den Test, ob Fortsetzen möglich
							// ist, benötigt)
	bool m_bNewEdit;		// Neueditierung (true) oder Modifikation (false)
	
	void TestClosedLine (void);
	void ListBoxSel (ControlEvt);
	
	void CloseButtonAction (void);
	void CircleButtonAction (void);
	HRESULT ComBorderButtonAction (void);
	HRESULT CommonBorderAtLine (IObjektGeometrie* pIOG, long* plIndex, MoveDir& MD);
	HRESULT CommonBorderAtArea (IObjektGeometrie* pIOG, long* plIndex, MoveDir& MD);
	bool ControlsSetting (void);

protected:
	void WindowInit (Event e);	
	void ButtonClick (ControlEvt e);
	BOOL OnOK (NotifyEvt);
	BOOL OnSetActive (NotifyEvt);
	BOOL OnKillActive (NotifyEvt);
	BOOL DrawEntireItem (DrawItemEvt);	// Element vollständig malen
	BOOL DrawItemFocus (DrawItemEvt);	// Element mit Focus zeichnen
	BOOL DrawItemSelect (DrawItemEvt);	// Element ausgewählt zeichnen
	LRESULT Dispatch(Event e);

	HOBJECTS DefineNewEntry();
	int InsertEntry (char const *pEntry, HOBJECTS lIdent);
	void AdjustOKButton();

public:
	// Konstruktor/Destruktor
		CEditBaseDlg (KoOrd* plGrabPktX, KoOrd* plGrabPktY, HRESULT hrComBorder, int iCloseCnt,
					  KoOrd* plCloseX, KoOrd* plCloseY, bool bNewEdit);
		~CEditBaseDlg (void);
};

#endif  // _EDITBASEDLG_H
