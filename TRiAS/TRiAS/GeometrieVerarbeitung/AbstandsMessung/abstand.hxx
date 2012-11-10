// Erweiterungsklasse für "Abstandsmessung"
// File: ABSTAND.HXX
// W. Mörtl

#if !defined (_ABSTAND_HXX)
#define _ABSTAND_HXX


#include "SmartInterfaces.h"

///////////////////////////////////////////////////////////////////////////////
// LizensierungsKlasse
#if defined(_DEBUG)
extern "C" bool g_fGlobalLic;
#else
#define g_fGlobalLic false
#endif // defined(_DEBUG)

class CMyLicense
{
protected:
	static BOOL VerifyLicenseKey(BSTR bstr)
	{
	CComBSTR bstrKey;

		USES_CONVERSION;
		if ((GetLicenseKey (0, &bstrKey) && !wcscmp (bstrKey, bstr)) ||
			 ::SetLicensed (OLE2A(bstr)))
		{
			return TRUE;
		}
		return FALSE;
	}

	static BOOL GetLicenseKey (DWORD, BSTR *pBstr) 
	{
	CComBSTR bstrKey (_MAX_PATH, (LPCOLESTR)NULL);

		if (!::GetLicenseKey (bstrKey.m_str, _MAX_PATH))
			return FALSE;

		*pBstr = bstrKey.Detach(); 
		return TRUE;
	}

	static BOOL IsLicenseValid() { return g_fGlobalLic || ::GetLicensed(); }
};

///////////////////////////////////////////////////////////////////////////////////////////////
class AbstandExtension : public IExtendAbstand2,
						 public CTriasExtension,
						 public CComCoClass<AbstandExtension, &CLSID_Abstand>
{
private:
	HWND _hWnd;

	ERRHANDLER m_oldEH;		// alte Fehlerbehandlungs-Methode

	int m_iButtonIndex;		// Index für Buttonstellung in der Toolbar "Werkzeuge"

	ITRiASUIOwner* m_pIUIOwner;
	TBBUTTON m_tb;

	short m_iMode;			// Parameter von InitExtension()

	CoordTransX* m_pCT;		// Klasse für KoordinatenTransformation
	IdentList* m_pIL;		// Identifikatorliste
	bool m_bSight;			// eine/keine Sicht wurde ausgewählt (true/false)
	char m_cGenau;			// Anzahl der Nachkommastellen für Anzeige des Abstandes

	int _iAbstTool;		// Nummer des neuen Werkzeuges "Abstand"
	bool _isActive;			// Erweiterung ist nicht/aktiviert (false/true)
	bool _bProj;			// kein/ein Projekt geöffnet (false/true)

	bool _RightButtonSem;	// MaustastenSynchronisation
	bool _LeftButtonSem;
	bool _LeftButtonUp;		// linke Maustaste wurde losgelassen (true)

	AbstandsWerte* m_pAWDlg;	// Dialogbox für die Ergebnisse der Abstandsmessung
	bool _bWinOn;			// Dialogbox nicht/angelegt (false/true)
	bool _bWinAnz;			// Dialogbox ist nicht/angezeigt (false/true)
//	bool m_bMenIt;			// MenuItem nicht/installiert (false/true)

	DoublePair _AP, _EP;	// Anfangs- bzw. Endpunkt für Abstandsmessung (im ASC-Format)
	DragLineObject* _DRO;	// zu zeichnende Linie

	long m_lONrAO;		// Objektnummer des aktivierten (blinkenden) Objektes
	int m_iOT;		// Objekttyp des aktivierten Objektes
	int m_piAnz [3];	// Anzahl der selektierten (markierten) Objekte in den geöffneten
						// Recherchefenstern
						// m_piAnz[0]  Anzahl der selektierten Objekte außer dem aktivierten
						//             (blinkenden) Objekt
						// m_piAnz[1]  Anzahl der selektierten Flächen (evtl. einschl. einer
						//             aktivierten Fläche)
						// m_piAnz[2]  Anzahl der selektierten Kanten (evtl. einschl. einer
						//             aktivierten Kante)

	ObjNrBaum* m_NrKPunkte;	// Baum für Objektnummern der Kilometrierungspunkte
	ObjNrBaum* m_NrTeile;	// Baum für Objektnummern der Teilkanten
	bool m_MenPktLoe;		// Menüpunkt für Löschen der Kilometrierungspunkte nicht/aktiviert
							// (false/true)
	bool m_MenTeilLoe;		// Menüpunkt für Löschen der Teilkanten nicht/aktiviert
							// (false/true)
	bool m_bMenuDelP;		// Kilometrierungspunkte werden über Menüpunkt
							// "Kilometrierungspunkte löschen" gelöscht
	bool m_bMenuDelT;		// Teilkanten werden über Menüpunkt "Teilabschnitte löschen"
							// gelöscht
	ObjRechteck m_KC;		// umschreibendes Rechteck des Kilometrierungsbereiches
	ulong m_ulKMIdent;		// Identifikator für Kilometrierungspunkte
	bool m_bText;			// Text an Kilometrierungspunkt anhängen ja/nein

	WExtendBuffer m_wBuffer;// Interface für Ankopplung von Buffer.ext

	// Memberfunktionen
	bool InitAndOPEN (int iMode);
	void UnLoadAndCLOSE (void);

	double AbstandPunktPunkt (EPunkt* pP1, EPunkt* pP2);
	double AbstandPunktLinie (long lONr1, EPunkt* pP, long lONr2, EKante* pK, DistTyp dtTyp);
	double AbstandLinieLinie (long lONr1, EKante* pK1, long lONr2, EKante* pK2, DistTyp dtTyp);
	double MaxMinAbstandLinieLinie (EKante* pK1, EKante* pK2, DistTyp dtTyp);
	double AbstandMitte (long lONr1, long lONr2);
	double AbstandPunktKanteAuto (EPunkt* pP, long lONr, EKante* pK);
	double AbstandKanteKanteAuto (long lONr1, EKante* pK1, long lONr2, EKante* pK2);
	double AbstandPunktKanteStuetz (EPunkt* pP, EKante* pK);
	double AbstandPunktKanteExakt (EPunkt* pP, EKante* pK);
	double AbstandStuetzpunkte (long lONr1, long lONr2);
	bool LinienKilometrierung (IObjektGeometrie* pIOG, KoOrd lXA, KoOrd lYA, KoOrd lXE,
								KoOrd lYE, double dDistanz, double dTextStartWert, bool bTeil);
	bool FlaechenKilometrierung (IObjektGeometrie* pIOG, KoOrd lXA, KoOrd lYA, KoOrd lXE,
								KoOrd lYE, double dDistanz, double dTextStartWert, bool bTeil);
	bool AppendTextObject (long lKMONr, KoOrd x, KoOrd y, double dTextWert);
	bool TeilkanteAnTRiAS (HPROJECT hPr, IObjektGeometrie* pITK, ulong ulIdent);
	bool KilometrPunktSetzen (HPROJECT hPr, KoOrd x, KoOrd y, double dTextWert);
	void BereichZeichnen (void);
	HRESULT SmallestDistance (IObjektGeometrie* pTK, Side Seite, double* pdAbst);
	HRESULT GetStartStopCoords (IObjektGeometrie* pGK, Side Seite, double dAbst,
						   DoublePair dUF, KoOrd& lXAv, KoOrd& lYAv, KoOrd& lXEv, KoOrd& lYEv);
	void GetStartStopIndexes (IObjektGeometrie* pGO, KoOrd lXAv, KoOrd lYAv, KoOrd lXEv,
							  KoOrd lYEv, long& lAInd, long& lEInd);
	HRESULT CreateShiftedLinePart (IObjektGeometrie* pGF, long lAInd, long lEInd, Side Seite,
								   ulong ulIdent, IObjektGeometrie** ppIOGOut);
	HRESULT BufferInterface (IUnknown** ppIBuffer);
				
protected:
// überladene virtuelle Funktionen
	STDMETHOD_(BOOL, InitExtension) (short iMode);
	STDMETHOD_(BOOL, MenuInit) (HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuCommand) (UINT uiMenuID, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (WPARAM wParam, LPARAM lParam);
	STDMETHOD_(LRESULT, WindowsNotification) (UINT wMsg, WPARAM wParam, LPARAM lParam);
	STDMETHOD_(BOOL, UnLoadExtension) (void);

// weitere Memberfunktionen
	bool InstallToolbarButton (void);
	bool RemoveToolbarButton (void);
	void AbstandAnzeigen (void);
	void LMouseButtonDn (Point& Pt);
	void LMouseDrag (Point& Pt);
	void LMouseButtonUp (void);
	void RMouseButtonDn (void);
	void RestSpeichern (void);
	bool ReadCoordPrecision (void);

	bool _GetDebugOutputFlag (void);

public:
// Konstruktor / Destruktor
		AbstandExtension (void);
		~AbstandExtension (void);

	BEGIN_COM_MAP(AbstandExtension)		// Makro
		COM_INTERFACE_ENTRY(ITriasXtension2)
		COM_INTERFACE_ENTRY(ITriasXtension)
		COM_INTERFACE_ENTRY(IExtendAbstand2)
	END_COM_MAP()
	DECLARE_NO_REGISTRY()

	DECLARE_NOT_AGGREGATABLE_SINGLE(AbstandExtension, g_pTE)
	DECLARE_CLASSFACTORY2(CMyLicense)

// Memberfunktion
	// Test, ob eine Sicht selektiert ist
	bool IsSightSelected (void) { return m_bSight; } 

	// Objektnummer des aktivierten (blinkenden) Objektes zurückgeben
	long ONrAO (void) const { return m_lONrAO; }

	// Abstand zwischen den umschließenden Rechtecken zweier Objekte
	double AbstandRechtecke (long lONr1, long lONr2);

	HRESULT TeilKante (IObjektGeometrie* pIOGIn, KoOrd& lXA, KoOrd& lYA, KoOrd& lXE,
					   KoOrd& lYE, double& dDistanz, IObjektGeometrie** ppIOGOut);

	HRESULT EntfernungVomAnfang_Geom (IObjektGeometrie* pIOG, KoOrd* plX, KoOrd* plY,
									  double* pdAbst);

	// Erzeugen einer verschobenen Teilkante
	HRESULT VerschobeneTeilKante (IObjektGeometrie* pIOGIn, KoOrd lXA, KoOrd lYA,
	   double dLaenge, Side Seite, double* pdAbst, ulong ulIdent, IObjektGeometrie** ppIOGOut);


// IUnknown methods
	HRESULT AbstandObjOKlasse (long lONr, ulong ulIdent, double* pdAbst, DistTyp dtTyp,
							   ExtrAbst exAbst, long* plONr);
	HRESULT AbstandObjObj_ONr (long lONr1, long lONr2, double* pdAbst,
							   DistTyp dtTyp = DISTTYP_MIDDLE, ExtrAbst exAbst = ABST_MIN);
	HRESULT AbstandObjObj_Geom (IObjektGeometrie* pIOG1, IObjektGeometrie* pIOG2,
				   double* pdAbst, DistTyp dtTyp = DISTTYP_MIDDLE, ExtrAbst exAbst = ABST_MIN);

// IExtendAbstand2-Methoden
	STDMETHOD_ (HRESULT, DistanceObjObj_ONr) (LONG lONr1, LONG lONr2, double* pdAbst,
											  DistTyp dtTyp, ExtrAbst exAbst);
	STDMETHOD_ (HRESULT, DistanceObjObj_Geom) (IObjektGeometrie* pIOG1,
					  IObjektGeometrie* pIOG2, double* pdAbst, DistTyp dtTyp, ExtrAbst exAbst);
	// kleinster bzw. größter Abstand der Objekte einer ulIdent-Objektklasse
	STDMETHOD_ (HRESULT, DistanceObjOClass_ONr) (LONG lONr, ULONG ulIdent, double* pdAbst,
												 DistTyp dtTyp, ExtrAbst exAbst, LONG* plONr);
	STDMETHOD_ (HRESULT, DistanceObjOClass_Geom) (IObjektGeometrie* pIOG, ULONG ulIdent,
								  double* pdAbst, DistTyp dtTyp, ExtrAbst exAbst, LONG* plONr);
	STDMETHOD_ (HRESULT, LinePart) (IObjektGeometrie* pIOGIn, LONG lXA, LONG lYA, LONG lXE,
									LONG lYE, double dDist, IObjektGeometrie** ppIOGOut);
	STDMETHOD_ (HRESULT, DistanceFromOrigin_Geom) (IObjektGeometrie* pIOG, LONG* plX,
												   LONG* plY, double* pdAbst);
	STDMETHOD_ (HRESULT, ShiftedLinePart) (IObjektGeometrie* pIOGIn, LONG lXA, LONG lYA,
										   double dLaenge, Side Seite, double* pdAbst,
										   ULONG ulIdent, IObjektGeometrie** ppIOGOut);
};


// Struktur für Datenübergabe der Routine ObjektAbstand()
struct AbstDat
{
	long lBONr;			// Objektnummer des Bezugsobjektes
	DistTyp dtTyp;		// Form der Abstandsbestimmung
	ExtrAbst exAbst;	// der kleinste / größte Abstand ist zu bestimmen
	double dAbst;		// gesuchter Abstand
	long lEONr;			// Nummer des Objektes mit dem kleinsten / größten Abstand
};

#endif  // _ABSTAND_HXX
