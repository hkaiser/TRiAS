// Dialogfenster zur Einstellung des Drucklayouts -----------------------------
// File: PRNTLAYT.HXX

#if !defined(_PRNTLAYT_HXX)
#define _PRNTLAYT_HXX

#define HEADLINELENGTH	_MAX_PATH
#define INBUFFLEN		_MAX_PATH
#define CNT_MASSTAB		16

// DatenTypen, die PrintLayout beschreiben ------------------------------------
#if !defined(LAYOUTSTYLES)
#define LAYOUTSTYLES

enum FrameStyle {
	FSNoFrame,		// kein Rahmen
	FSSimpleFrame,		// einfache dünne Linie
	FSThickFrame,		// einfache dicke Linie
	FSDoubleFrame,		// innen dünn außen dick
	FSTripleFrame,		// dünn, dick dünn
};

enum LegendStyle {
	LSNoLegend,		// keine Legende
	LSSimpleLegend,		// normale Legende
};

enum MasstabStyle {
	MSNoMasstab,		// keine Maßstabsausgabe
	MSSimpleMasstab,	// einfaches ZahlenFormat
};
#endif

class PrintLayout {
public:
// SeitenRänder in [mm]
	Rectangle *m_plFullRect;		// Blattgrenzen

// Beschreibung der verschiedenen Bereiche (alle Maáe in [mm])
	FrameStyle m_plfsRahmen;		// Rahmen zeichnen
	LegendStyle m_pllsLegende;	// Legende zeichnen
	Rectangle *m_plRcLegende;	// für Legende vorgesehener Bereich
	bool m_pliHeadLine;		// Überschrift generieren
	char *m_pllpHeadLine;		// zu generierende Überschrift
	Rectangle *m_plRcHeadLine;	// für Überschrift vorgesehener Bereich 
	MasstabStyle m_plmsMasstab;	// Maßstab ausgeben
	Rectangle *m_plRcMasstab;	// für Maßstab vorgesehener Bereich

// Kartenausschnitt
	Rectangle *m_plRcSpiegel;
	ObjContainer *m_plOCSpiegel;
	long m_lMasstab;		// Maßstab
	
	Rectangle *m_plrcPageSize;	// DruckBereich
	Rectangle *m_plrcPageBase;	// BezugsMaße
	
	Rectangle *m_plRcLogo;		// LogoBereich (Überschrift)
	Rectangle *m_plRcFirmLogo[MAX_LOGOFELD];	// LogoBereiche (unten)

	bool m_fLegendOnly;

// Konstruktor legt Speicher lediglich an
		PrintLayout (void) {}
		~PrintLayout (void);	// gesamten Speicher freigeben
};

// STL-related stuff ----------------------------------------------------------
#define NOMINMAX
#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)		// debug info truncated
#include <ospace/std/list>

#include <shlobj.h>
#include <xtsnguid.h>
#include <regprop.hxx>
#include <funcs03.h>
#include <dirisole.h>

#include "updnedit.h"

///////////////////////////////////////////////////////////////////////////////
// verwendete Interfaces
DefineSmartInterface(Storage);
DefineSmartInterface(DataObject);

class CPrintLayoutSheet : public CPropertySheetExt {
public:
		CPrintLayoutSheet (pWindow pWnd)
			: CPropertySheetExt (ResString (IDS_PRNTLAYOUTCAPTION_NOPRINTER, 64), pWnd, PSH_NOAPPLYNOW)
		{}
		~CPrintLayoutSheet (void) {}

	HRESULT LoadPages (IDataObject *pIDO, LPCSTR pcKey, LPCSTR pcSubKey)
		{ return LoadExtPagesFromRegistry (HKEY_CLASSES_ROOT, pcKey, pcSubKey, pIDO, NULL); }
};

class CPrintLayoutDlg : public CPropertyPage 
{
private:
	bool m_isValid;
	bool m_fSysMode;		// DEX_QueryMode & QMSysAdmin

// DruckSeitenLayout
//	DoublePairEdit m_LinksOben;			// Bildausschnitt
//	DoublePairEdit m_rechtsUnten;
	DoubleNumEdit m_ObenHoch, m_ObenRechts;		// Bildausschnitt
	DoubleNumEdit m_UntenHoch, m_UntenRechts;
	ComboBox m_Masstab;
	RadioButton m_RKoord, m_RMasstab;

	CSpinControl m_SizeX, m_SizeY;				// SeitenLayout
	CSpinControl m_RandOben, m_RandLinks;		// Ränder
	CSpinControl m_RandRechts, m_RandUnten;

// DruckOptionen
	CheckBox m_CBLegende, m_CBMasstab;
	CheckBox m_CBRahmen, m_CBHeadLine;
	CheckBox m_CBLegendOnly;

	SingleLineEdit m_HeadLine;

// Buttons
	PushButton m_Default;
	PushButton m_pbSelect;		// Drucker auswählen

	long m_actMasstab;
	ObjContainer m_ocActRect;	// aktueller Bildausschnitt
	
	Dimension m_PageSize;		// Größe der gesamten Seite
	DoublePair m_DotsPerMM;

	CoordTrans *m_pCT;			// Koordinatentransformation
	char *m_pInBuff;			// allgemeiner Ein-AusgabePuffer

	PrinterPars &m_rPP;			// aktueller Printer
	void MakeCaption (void);	// Caption berichtigen

	CLegSizeCache m_PrLayout;	// Zugriff auf Printlayout
	WDataObject m_DataObj;

protected:
	LRESULT Dispatch (Event e);

	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	void EditFocusChg (EditFocusChgEvt);
	void VertScroll (ScrollEvt) ;
	void WindowInit (Event);
	void OnCancel (NotifyEvt e);
	bool OnOK (NotifyEvt e);

	long GetMasstab (short iIndex);

private:
	void EvalSizeX (bool fRecalc = true);
	void EvalSizeY (void);
	void EvalRechtsUnten (void);
	void EvalMasstab (void);

	void PostFocus (Control *pCtrl, Control *pCtrlAct = NULL);

// KartenSpiegel
	Rectangle *GetPaperCanvas (void);	// GesamtBlattSpiegelGröße
	ObjContainer *GetExtend (void);		// BereichsGrenze

// Überschrift
	char* GetHeadLine (void);
	Rectangle *GetHeadLineRect (void);
	bool GetHeadLineFlag (void) { return m_CBHeadLine.isChecked(); }

// Maßstabsangabe
	MasstabStyle GetMasstabType (void)
		{ return m_CBMasstab.isChecked() ? MSSimpleMasstab : MSNoMasstab; }
	Rectangle *GetMasstabRect (void);

// Legende
	LegendStyle GetLegendType (void) 
		{ return m_CBLegende.isChecked() ? LSSimpleLegend : LSNoLegend; }
	Rectangle *GetLegendeRect (void);
	Rectangle *GetLogoRect (void);
	Rectangle *GetFirmLogoRect (int iCnt);
	long GetFirmLogoHeight (long lBaseHeight);

// Gesamtbereich
	Rectangle *GetFullRect (void);
	FrameStyle GetFrameType (void) 
		{ return m_CBRahmen.isChecked() ? FSSimpleFrame : FSNoFrame; }
	Rectangle *GetPageSize (void);
	Rectangle *GetPageBase (void);

	bool GetValue (DoubleNumEdit &, double &, DoubleNumEdit &, double &);

public:
		CPrintLayoutDlg (const ObjContainer &, CoordTrans *, PrinterPars &);
		~CPrintLayoutDlg (void);

	bool Init (void);	// weitere Initialisierungen
	
	CoordTrans *& pCT (void) { return m_pCT; }
	PrintLayout *GetLayout (void);

	PrinterPars &Pars (void) { return m_rPP; }

	void SaveEntries (void);

	HRESULT GetDataObject (IDataObject **ppIDO);
	HRESULT SetNewPrinterData (void);
};

///////////////////////////////////////////////////////////////////////////////
// Zwischenspeichern der aktuellen Bildschirm-Einstellungen
class CDBOContext {
private:
	DatenBasisObjekt &m_rDBO;
	Point m_ptAspect;
	Window *m_pW;

	ObjContainer m_oc;
	Rectangle m_rcEA;

public:
	CDBOContext (pWindow pW, DatenBasisObjekt &rDBO, Point ptAspect) 
		: m_pW(pW), m_rDBO(rDBO), m_ptAspect(ptAspect)
		{
			m_rcEA = rDBO.EA();
			m_oc = rDBO.GetExtend();
		}
	~CDBOContext (void)
		{
			m_rDBO.SetEA(m_rcEA);
			m_rDBO.Scale(m_pW, m_oc, m_ptAspect);
		}
};

#endif // _PRNTLAYT_HXX

