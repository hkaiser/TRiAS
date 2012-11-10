// Dialogfenster zur Einstellung des Drucklayouts -----------------------------
// File: PRNTLAYT.HXX

#if !defined(_PRNTLAYT_HXX)
#define _PRNTLAYT_HXX

#define HEADLINELENGTH	_MAX_PATH
#define INBUFFLEN		_MAX_PATH
#define CNT_MASSTAB		16

#include "LayoutStyles.h"
#include "DBOContext.h"

class PrintLayout 
{
public:
// SeitenRänder in [mm]
	Rectangle *m_plFullRect;		// Blattgrenzen

// Beschreibung der verschiedenen Bereiche (alle Maße in [mm])
	FrameStyle m_plfsRahmen;		// Rahmen zeichnen
	LegendStyle m_pllsLegende;		// Legende zeichnen
	Rectangle *m_plRcLegende;		// für Legende vorgesehener Bereich
	bool m_pliHeadLine;				// Überschrift generieren
	char *m_pllpHeadLine;			// zu generierende Überschrift
	Rectangle *m_plRcHeadLine;		// für Überschrift vorgesehener Bereich 
	MasstabStyle m_plmsMasstab;		// Maßstab ausgeben
	Rectangle *m_plRcMasstab;		// für Maßstab vorgesehener Bereich

// Kartenausschnitt
	Rectangle *m_plRcSpiegel;
	ObjContainer *m_plOCSpiegel;
	long m_lMasstab;				// Maßstab
	
	Rectangle *m_plrcPageSize;		// DruckBereich
	Rectangle *m_plrcPageBase;		// BezugsMaße
	
	Rectangle *m_plRcLogo;			// LogoBereich (Überschrift)
	Rectangle *m_plRcFirmLogo[MAX_LOGOFELD];	// LogoBereiche (unten)

	bool m_fLegendOnly;

// Konstruktor legt Speicher lediglich an
		PrintLayout (void) {}
		~PrintLayout (void);	// gesamten Speicher freigeben

// in/aus andere(n) Formate(n) konvertieren
	BOOL RetrieveLayout (PRINTLAYOUT *pLayout);
	BOOL Init (PRINTLAYOUT *pLayout);
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

///////////////////////////////////////////////////////////////////////////////
// PropertySheet entält gemeinsames für alle LayoutSeiten

#if defined(_USE_LEGEND_LAYOUT)
// Konstanten für Legendengröße und -position
enum PAPERFORMAT {
	PAPERFORMAT_Portrait = 0,		// Hochformat
	PAPERFORMAT_Landscape = 1,		// Querformat
};
enum LEGENDPOSITION {
	LEGENDPOSITION_Links = 0,
	LEGENDPOSITION_Rechts = 1,
	LEGENDPOSITION_HorzMask = 1,

	LEGENDPOSITION_Oben = 0,
	LEGENDPOSITION_Unten = 2,
	LEGENDPOSITION_VertMask = 2,

	LEGENDPOSITION_LO = LEGENDPOSITION(LEGENDPOSITION_Links|LEGENDPOSITION_Oben),
	LEGENDPOSITION_LU = LEGENDPOSITION(LEGENDPOSITION_Links|LEGENDPOSITION_Unten),
	LEGENDPOSITION_RO = LEGENDPOSITION(LEGENDPOSITION_Rechts|LEGENDPOSITION_Oben),
	LEGENDPOSITION_RU = LEGENDPOSITION(LEGENDPOSITION_Rechts|LEGENDPOSITION_Unten),

	LEGENDPOSITION_Mask = LEGENDPOSITION(LEGENDPOSITION_HorzMask|LEGENDPOSITION_VertMask),
};
enum SIZEINDEX {
	SIZEINDEX_100 = 0,
	SIZEINDEX_75 = 1,
	SIZEINDEX_50 = 2,
	SIZEINDEX_33 = 3,
	SIZEINDEX_25 = 4,
	SIZEINDEX_MAX = 5,
};
#endif // defined(_USE_LEGEND_LAYOUT)

///////////////////////////////////////////////////////////////////////////////
// zusätzliche Dialogseite für LegendenEinstellungen
class CPrintLayoutSheet : 
	public CPropertySheetExt 
{
public:
	CPrintLayoutSheet (pWindow pWnd) :
		CPropertySheetExt (ResString (IDS_PRNTLAYOUTCAPTION_NOPRINTER, 64), pWnd, PSH_NOAPPLYNOW)
	{
#if defined(_USE_LEGEND_LAYOUT)
		m_rgFormat = PAPERFORMAT_Portrait;
		m_rgPosition = LEGENDPOSITION_RO;
		m_rgSizeIndex = SIZEINDEX_100;
#endif // defined(_USE_LEGEND_LAYOUT)
	}
	~CPrintLayoutSheet (void) {}

	HRESULT LoadPages (IDataObject *pIDO, LPCSTR pcKey, LPCSTR pcSubKey, IUnknown *pIUnkSite)
		{ return LoadExtPagesFromRegistry (HKEY_CLASSES_ROOT, pcKey, pcSubKey, pIDO, NULL, pIUnkSite); }

#if defined(_USE_LEGEND_LAYOUT)
// Zugriff auf LegendenParameter
	PAPERFORMAT GetPaperFormat() { return m_rgFormat; }
	void SetPaperFormat (PAPERFORMAT rgFormat) { m_rgFormat = rgFormat; }

	LEGENDPOSITION GetLegendPosition() { return m_rgPosition; }
	void SetLegendPosition (LEGENDPOSITION rgPosition) { m_rgPosition = rgPosition; }

	SIZEINDEX GetSizeIndex() { return m_rgSizeIndex; }
	void SetSizeIndex (SIZEINDEX rgSizeIndex) { m_rgSizeIndex = rgSizeIndex; }

private:
	PAPERFORMAT m_rgFormat;
	LEGENDPOSITION m_rgPosition;
	SIZEINDEX m_rgSizeIndex;
#endif // defined(_USE_LEGEND_LAYOUT)
};

///////////////////////////////////////////////////////////////////////////////
// PrintLayout vorgeben
class CPrintLayoutDlg : 
	public CPropertyPage 
{
private:
	bool m_isValid;
	bool m_fSysMode;				// DEX_QueryMode & QMSysAdmin
	bool m_fPreview;

// DruckSeitenLayout: Controls
//	DoublePairEdit m_LinksOben;		// Bildausschnitt
//	DoublePairEdit m_rechtsUnten;
	DoubleNumEdit m_ObenHoch;
	DoubleNumEdit m_ObenRechts;		// Bildausschnitt
	DoubleNumEdit m_UntenHoch;
	DoubleNumEdit m_UntenRechts;
	ComboBox m_Masstab;
	RadioButton m_RKoord;
	RadioButton m_RMasstab;

	CSpinControl m_SizeX;			// SeitenLayout
	CSpinControl m_SizeY;
	CSpinControl m_RandOben;		// Ränder
	CSpinControl m_RandLinks;
	CSpinControl m_RandRechts;
	CSpinControl m_RandUnten;

// DruckOptionen
	CheckBox m_CBLegende;
	CheckBox m_CBMasstab;
	CheckBox m_CBRahmen;
	CheckBox m_CBHeadLine;
	CheckBox m_CBLegendOnly;

	SingleLineEdit m_HeadLine;

// Buttons
	PushButton m_Default;
	PushButton m_pbSelect;		// Drucker auswählen

// Variablen
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

	bool &m_rfLegend;			// 'Zeichenerklärung' aktiviert

protected:
	LRESULT Dispatch (Event e);

	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	void EditFocusChg (EditFocusChgEvt);
	void VertScroll (ScrollEvt) ;
	void WindowInit (Event);
	void OnCancel (NotifyEvt e);
	BOOL OnOK (NotifyEvt e);

	long GetMasstab (short iIndex);
	bool GetSelectedObjectsCont(double *pdXMin, double *pdXMax, double *pdYMin, double *pdYMax);

#if defined(_USE_LEGEND_LAYOUT)
// Legendenposition und -größe
	PAPERFORMAT GetPaperFormat() { return ((CPrintLayoutSheet *)GetPropertySheet()) -> GetPaperFormat(); }
	SIZEINDEX GetSizeIndex() { return ((CPrintLayoutSheet *)GetPropertySheet()) -> GetSizeIndex(); }
	LEGENDPOSITION GetLegendPosition() { return ((CPrintLayoutSheet *)GetPropertySheet()) -> GetLegendPosition(); }
#endif // defined(_USE_LEGEND_LAYOUT)

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
		CPrintLayoutDlg (const ObjContainer &, CoordTrans *, PrinterPars &, bool &rLegend, bool fPreview = false);
		~CPrintLayoutDlg (void);

	bool Init (void);	// weitere Initialisierungen
	
	CoordTrans *& pCT (void) { return m_pCT; }
	PrintLayout *GetLayout (void);

	PrinterPars &Pars (void) { return m_rPP; }

	void SaveEntries (void);

	HRESULT GetDataObject (IDataObject **ppIDO);
	HRESULT SetNewPrinterData (void);
};

#endif // _PRNTLAYT_HXX

