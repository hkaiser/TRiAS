// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 06.12.2002 13:02:43 
//
// @doc    Konfigurationsdialog zu PropertyAction für Gitterbildung
// @module GitterDlg.h | Declaration of the <c CGitterDlg> class

#if !defined(_GITTERDLG_H__E09CBE0F_3A13_4791_9E77_5183142A38BA__INCLUDED_)
#define _GITTERDLG_H__E09CBE0F_3A13_4791_9E77_5183142A38BA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif


#include "RasterR.h"       // Hauptsymbole (Ressourcen)

#include <float.h>			// DBL_MAX




///////////////////////////////////////////////////////////////////////////////////////////////
// Zustand des Dialogs
typedef struct tagGRIDDATA
{
	bool bType;			// Gittertyp (Fläche: true, Linie: false)
//	double dTRV;		// Rechtswert oben (in Real-Koordinaten)
//	double dTHV;		// Hochwert oben
//	double dBRV;		// Rechtswert unten
//	double dBHV;		// Hochwert unten
	bool bRound;		// Runden (ja: true, nein: false)
	int iRoundListIndex;// Index in der Liste der Rundungswerte
	KoOrd lRoundValue;	// Rundungswert
	KoOrd lXWidth;		// Gitterbreite in x- bzw.
	KoOrd lYWidth;		//  y-Richtung
	double dTurnAngle;	// Drehwinkel

} GRIDDATA;



///////////////////////////////////////////////////////////////////////////////////////////////
// CGitterDlg Dialog

class CGitterDlg : public CPropertyPage
{
// Construction
public:
	CGitterDlg (ResID uiResID, LPCSTR pcCaption);
	~CGitterDlg();

// Dialog Data
	enum { IDD = IDD_GRIDOPTIONS };

// Overrides
public:
	int OnSetActive (NotifyEvt e);
	BOOL OnWizFinish (NotifyEvt e);
	int OnWizNext (NotifyEvt e);
	void WindowInit(Event e);
	void ButtonClick(ControlEvt e);
	void ListBoxSel (ControlEvt);
	void FillComboBox (void);

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	HRESULT SetSelectedInfo (GRIDDATA* pSelInfo, bool bNoShow = false);
	HRESULT GetSelectedInfo (GRIDDATA* pSelInfo, bool& bIsDirty);
	static CGitterDlg* CreateInstance (LPCSTR pcCaption);

	BOOL FInit();

	HPROPSHEETPAGE CreatePage() { return CPropertyPage::CreatePage(); }

	bool GetGridType (void) { return m_bType; }
	KoOrd GetXWidth (void) { return m_lXWidth; }
	KoOrd GetYWidth (void) { return m_lYWidth; }
	double GetAngle (void) { return m_dTurnAngle; }
	EPunkt GetPLO (void) { return m_PLO; }
	EPunkt GetPRU (void) { return m_PRU; }
//	EPunkt GetPRO (void) { return m_PRO; }
//	EPunkt GetPLU (void) { return m_PLU; }
	KoOrd* GetCont (void) { return m_lCO; }
	void SetWinHandle (HWND hWnd) { m_hWnd = hWnd; }


// Implementation
protected:
	void AdjustSheetButtons();
	BOOL GetDisableNextPage();

	void FinishButton (bool bFinish);
	void EditChange (ControlEvt e);

private:
	DWORD m_dwFlags;

	DoubleNumEditX m_TopRightValue, m_TopHightValue, m_BottomRightValue, m_BottomHighValue;
	CheckBox m_CBoxRound;
	ComboBox m_RoundValuesList;
	RadioButton m_RBttnArea, m_RBttnLine;
	NumEditX m_Horizontal, m_Vertical;
	DoubleNumEditX m_Angle;

	CoordTransX m_CTX;
	HWND m_hWnd;				// Handle des Fensters (Objektrecherchefenster oder Hauptfenster),
								//  aus dem die Gitterbildung ausgelöst wurde
	long m_lONr;				// Objektnummer des (evtl.) Objektes, für das Gitter gebildet werden soll
	KoOrd m_lCO[4];				// Container-Koordinaten des (evtl.) Objektes bzw. des
								//  allgemeinen Bereiches für die Gitterbildung
	bool m_bType;				// Gittertyp (Fläche: true, Linie: false)
	double m_dOrigTRV, m_dOrigTHV;	// ursprüngliche Rechts-, Hochwert oben und
	double m_dOrigBRV, m_dOrigBHV;	//  Rechts-, Hochwert unten des Bereiches in Real-Koordinaten
	double m_dTRV, m_dTHV;		// gerundete Rechts-, Hochwert oben und
	double m_dBRV, m_dBHV;		//  Rechts-, Hochwert unten des Bereiches in Real-Koordinaten
	EPunkt m_PLO, m_PRU;		// linker oberer und rechter unterer Punkt des Bereiches
								//  in DB-Koordinaten
//	EPunkt m_PRO, m_PLU;		// rechter oberer und linker unterer Punkt des Bereiches
//								//  in DB-Koordinaten
	bool m_bRound;				// Koordinaten runden (true)
	int m_iRoundListIndex;			// Index in der ComboBox
	KoOrd m_lRoundValue;		// Rundungswert für Koordinaten
	KoOrd m_lXWidth, m_lYWidth;	// Gitterbreite in x- bzw. y-Richtung
	KoOrd m_lOrigWidth;			// die erste automatisch errechnete Gitterbreite
	double m_dTurnAngle;		// Drehwinkel
	bool m_bDefXWidth;			// die automatische erzeugten default-Werte für die Gitterbreiten
	bool m_bDefYWidth;			//  (true) bzw. die vom Anwender editierten Werte (false)

	void GridPresetting (void);
	void OutputCoords (void);
	int InputWidth (NumEditX* pEingWert);
	void ContainerRotation (void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_GITTERDLG_H__E09CBE0F_3A13_4791_9E77_5183142A38BA__INCLUDED_)
