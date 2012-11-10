// Erweiterungsklasse für "Geometrie-Editierung"
// File: GEOEDIT.HXX
// W. Mörtl

#if !defined(_GEOEDIT_HXX)
#define _GEOEDIT_HXX


#include <TRiASHelper.h>	// tagPIFLAGS in "ProgressProxy.h"
#include "progstat.h"		// BaseProgressStatus
#include "ProgressProxy.h"	// CProxyIProgressIndicator2

#include "SmartInterfaces.h"
EXTERN_C const CLSID CLSID_GeometrieEditierung;



class GeometrieBaum;
class GeoEditExtension : public ITRiASDropTarget,
						 public CTriasExtension,
						 public CComConnectionPointContainerImpl,
						 public CComCoClass<GeoEditExtension, &CLSID_GeometrieEditierung>
{
private:
	CProxyIProgressIndicator2 m_PPI;
	DWORD m_dwCookie;				// Nummer des ConnectionPoint

//	CEditDropTarget* m_pEDropTarget;// Interface

	IExtendGeoRein* m_pIGeoRein;	// für Ankopplung von georein.ext	
	bool m_bGeoRein;				// Ankopplung von georein.ext noch nicht erfolgt (false)
	IExtendObjOper* m_pIObjOper;	// für Ankopplung von objoper.ext
	bool m_bObjOper;				// Ankopplung von objoper.ext noch nicht erfolgt (false)

	RECT m_rcHintergrund;	// rechteckiger Hintergrundbereich, der neu gezeichnet wird
	bool m_bHgrZeichnen1;	// Hintergrund (durch DEX_ERASEBKGND bzw. DEX_PAINTTOPLAYER ausgelöst)
							//  wird/wurde (true/false) gezeichnet
	bool m_bHgrZeichnen2;	// Hintergrund (durch Update() ausgelöst) wird/wurde (true/false) gezeichnet

	IdentList* m_pIL;	// Identifikatorliste
	CoordTransX* m_pCT;	// Klasse für Zugriff auf Header-Informationen
	bool m_bSight;		// eine/keine Sicht wurde ausgewählt (true/false)

	bool _isActive;		// Erweiterung ist nicht/aktiviert (false/true)
	short _iNeuTool1;	// Nummer des neuen Werkzeuges "Punkteditierung"
	short _iNeuTool2;	// Nummer des neuen Werkzeuges "Linieneditierung"
	short _iNeuTool3;	// Nummer des neuen Werkzeuges "Flächeneditierung"
	short _iNeuTool4;	// Nummer des neuen Werkzeuges "Geometriemodifizierung"
	bool _bProj;		// kein/ein Projekt geöffnet (false/true)

	bool _RightButtonSem;	// MaustastenSynchronisation
	bool _LeftButtonSem;
	Point m_PtOld;		// letzte Mausposition
	bool _KD;			// true,  wenn RegisterNotification (WM_KEYDOWN, false)
						// false, wenn UnRegisterNotification (WM_KEYDOWN, false)
	bool _KU;			// true,  wenn RegisterNotification (WM_KEYUP, false)
						// false, wenn UnRegisterNotification (WM_KEYUP, false)
	bool _LD;			// true,  wenn RegisterNotification (WM_LBUTTONDOWN, false)
						// false, wenn UnRegisterNotification (WM_LBUTTONDOWN, false)
	bool _LU;			// true,  wenn RegisterNotification (WM_LBUTTONUP, false)
						// false, wenn UnRegisterNotification (WM_LBUTTONUP, false)
	bool _RD;			// true,  wenn RegisterNotification (WM_RBUTTONDOWN, false)
						// false, wenn UnRegisterNotification (WM_RBUTTONDOWN, false)
	bool _RU;			// true,  wenn RegisterNotification (WM_RBUTTONUP, false)
						// false, wenn UnRegisterNotification (WM_RBUTTONUP, false)
	bool _MM;			// true,  wenn RegisterNotification (WM_MOUSEMOVE, false)
						// false, wenn UnRegisterNotification (WM_MOUSEMOVE, false) angewählt wurde

	EObjekt* _pEO;		// neu zu erfassendes ElementarObjekt
	ObjTyp _OTyp;		// Objekttyp (Punkt, Linie, Fläche)
	Punkt m_LastPunkt;	// letzter aktuell editierter Punkt
	double m_AktLaenge;	// Länge der aktuellen Strecke
	double m_AktGesLaenge;	// aktuelle Gesamtlänge einer editierten Linie
	double m_AktDreieck;	// Flächeninhalt der aktuellen Dreiecksfläche
	double m_AktInsel;		// Flächeninhalt der aktuellen Insel
	double m_AktGesFlaeche;	// aktueller Gesamtflächeninhalt einer editierten Fläche
	char* _pcONText;	// Objektname des neu zu erfassenden Objektes
	bool _bIns;			// der nächste editierte Punkt ist Beginn einer neuen Insel (true)
	
	HMENU m_hSubMenu;	// MenuHandle nach Druck der rechten Maustaste bei Modifizieren von Objekten
	Point _ptRM;		// Punkt, bei dem rechte Maustaste gedrückt wurde
	Point _ptMS;		// aktuelle Mausspitze
	DragLineObject* _DRO;	// zu zeichnende Linie (in dragline.cxx)
	DragLineObject* _DRO1;	// zu zeichnende Linie
	DragLineObject* _DRO2;	//  für Banding (in dragline.cxx)

	GeometrieBaum* m_pGB;	// Baum für Geometrien der selektierten (markierten) Objekte
	IObjektGeometrie* m_pIOG;// Geometrie des Objektes, auf dessen Stützpunkte bzw.
							//  Strecken Cursor zeigt
	long m_lInd;			// (fortlaufender) Index des Stützpunktes bzw. der Strecke,
							//  auf dem/der der Cursor zeigt
	Marker* m_pMk;			// Markierunsquadrat, auf das Cursor zeigt
	Point _PV;				// vorhergehender Stützpunkt (in BS-Koordinaten)
	Point _PN;				// nachfolgender Stützpunkt (in BS-Koordinaten)
	EObjekt* m_pMarkObj;	// Objekt, in dem sich Cursur befindet
	short m_iOT;			// Typ des Objektes, aus dem m_pMarkObj gebildet wurde
	long m_lGrabONr;		// Nummer des Objektes, an das angegrabt wird
	Punkt m_GrabPkt;		// Punkt, an den angegrabt wird
	IObjektGeometrie* m_pVerlLin;	// Linie, die verlängert werden soll
	bool m_bAnf;			// Linienobjekt wird am Anfang/Ende verlängert (true/false)

	EObjekt* m_pFT;		// Fläche, die geteilt werden soll (entspricht dem über das Interface geholten m_pIOG)
	IObjektGeometrie* m_pMesser;// Objekt (Kante) für Teilung von Flächenobjekten

	Curs m_CurForm;			// aktuelle Cursorform
	Curs m_CurFormOld;		// vorhergehende Cursorform
	Pointer* m_SternCursor;	// eigener Cursor, wenn Cursor auf Stützpunkt (Geometrie-Modifizierung)
	Pointer* m_TrennCursor;	// eigener Cursor, wenn Cursor auf Strecke
	Pointer* m_KreuzCursor;	// eigener Cursor, wenn Cursor auf Stützpunkt und CTRL-Taste gedrückt
	Pointer* m_InnerhCursor;// eigener Cursor, wenn Cursor innerhalb eines markierten Objektes
	Pointer* m_FangCursor;	// eigener Cursor, wenn Cursor auf Stützpunkt (Stützpunkt-Angraben)
	Pointer* m_OldCursor;	// vorhergehender eigener Cursor

	Dimension m_dimDots;	// Pixel pro Millimeter für den Bildschirm
	short m_iUMarkGr;		// Untergrenze der Pixelanzahl (in x- und y-Richtung) für Marker
	short m_iOMarkGr;		// Obergrenze der Pixelanzahl (in x- und y-Richtung) für Marker
	long m_lMBX;			// Größe eines Markers (in DB-Koordinaten) in x- bzw.
	long m_lMBY;			//  y-Richtung
	long m_lEpsilon;		// Epsilon für Cursor-Umschaltung

	Point m_StartPt;		// Startpunkt (in BS-Koordinaten) bei Drag-and-Drop
	bool m_bIsDropSource;	// Unterscheidung, ob bei DragDrop aus Hauptfenster (true)
							// oder woanders (z.B. Recherchefenster oder Legende) heraus
							// gezogen wurde
	short m_iVerz;			// Verzögerung in Pixel bei DragDropStart

	// Member für Drag-And-Drop
	short m_iAnzVO;				// Anzahl der verschobenen Objekte
	long* m_plObjNrVO;			// Objektnummern der verschobenen Objekte
	POINTL m_ptlOld;			// Punkt (in Fensterkoordinaten), bei dem Objektumriß zu löschen ist
	Point* m_pPolyPoly;			// Vektor mit Stützpunktkoordinaten in BS-Format,
	int* m_piPolyCounts;		//  einzelne Stützpunktanzahl und

	// Memberfunktionen
	bool InitAndOPEN (void);
	void UnLoadAndCLOSE (void);

	bool KeyDown (WPARAM wPar);
	bool KeyUp (WPARAM wPar);
	bool LeftMouseDown (Point Pt);
	bool LeftMouseUp (Point Pt);
	bool MouseMove (Point Pt);
	bool RightMouseDown (Point Pt);
	bool RightMouseUp (void);

	Punkt NeuerPunktMitGrab (Point& Pt, short iAnz = 1);
	void BereichZeichnen (IObjektGeometrie* pIOG);
	void GeometrienErgaenzen (void);
	void AnzRuecksetzen (void);
	void StuetzpunktVerschieben (void);
	bool StuetzpunktVerschieben2 (Punkt& Pkt, IObjektGeometrie* pIOG, long lInd, Rectangle& Rec);
	void StuetzpunktLoeschen (void);
	void StuetzpunktHinzufuegen (Point Pt);
	bool ModObjSpeicherung (IObjektGeometrie* pIOG, Punkt& ModPkt, long& lInd, TestRicht trRicht,
							Rectangle& Rec);
	bool LinienobjektVerlaengern (void);
	bool idb_SpeichernLinienVerl (NeuEditDlg* pNED);
	void NeuerCursor (Curs CurForm = PFEIL, Pointer* pCursor = NULL);
	bool DeleteAllow (void);
	void StatuszeileModifizieren (Curs CurForm);
	CursPosit CursorpositionGesamtTest (IObjektGeometrie** ppIOG, long& lInd);
	CursPosit CursorpositionTest (Punkt& Pkt, IObjektGeometrie* pIOG, long& lInd);
	CursPosit CursorpositionTestPunkt (KoOrd* plXK, KoOrd* plYK, Punkt& Pkt, long lONr, long& lInd);
	CursPosit CursorpositionTestKante (KoOrd* plXK, KoOrd* plYK, long lSPAnz, Punkt& Pkt, long lONr,
									 long& lInd);
	CursPosit CursorpositionTestFlaeche (IObjektGeometrie* pIOG, KoOrd* plXK, KoOrd* plYK, long lSPAnz,
									   Punkt& Pkt, long lONr, long& lInd);
	bool PunktInMarker (Punkt& Pkt, KoOrd XK, KoOrd YK);
	bool PunktAnStrecke (Punkt& Pkt, KoOrd x1, KoOrd y1, KoOrd x2, KoOrd y2, KoOrd& lAbst);
	bool SchnittlinieBilden (void);
	bool InselLoeschen (void);
	Rectangle InselParameter (short iKontInd, KoOrd* plXI, KoOrd* plYI);
	HRESULT InselLoeschenSpeicherung (Rectangle Rec);
	void ObjektLoeschen (void);
	bool FlaecheTeilen (void);
	Punkt PunktAufKontur (Point Pt);
	void FensterNeueObjekte (POINT pt, long* plNeuObjNr, short iAnzNeuObj);
	void GeoReinInterface (void);
	bool StuetzpunkteTestenGrab (Point Pt);
	bool WeitereObjekteTesten (Punkt& Pkt1, Punkt& Pkt2, Rectangle& Rec);
	bool MarkierungenTestenGrab (Punkt& Pkt, IObjektGeometrie* pIOG);
	bool StuetzpunkteTesten2 (Punkt& Pkt, IObjektGeometrie* pIOG, long& lInd);
	void MarkerInDBK (Point Pt);
	void AktuelleWerteAnzeigen (Point Pt);
	bool DreieckInhalt (Point Pt);
	bool NeueKante (void);
	bool NeueFlaeche (void);
	short GroesseMarkQuadrat (void);
	bool EindeutigesObjekt (void);
	bool MerkmalLesen (long lONr, long lMerkCode, char* pcMText, short iPLaeng);
	bool MerkmalSchreiben (short iTTyp, long lONr, long lMCode, const char* pcText);
//	bool MerkmaleKopieren (long lONr1, long lONr2, char* pcErg = NULL, bool bUeber = true,
//						   bool bGeoErr = false, bool bClear = false, bool bSect = false);

// Memberfunktionen für Drag-And-Drop
	HRESULT CreateStreamOnHGlobalFromIUnknown (IUnknown* pIUnk, IStream** ppIStream);
	HRESULT SetEnumLONGData (IEnum<LONG>* pEnum, IDataObject* pDataObj);
	bool SelObjLoeschen (IEnum<LONG>* pEnum);
	HRESULT SetObjNummern (IEnum<LONG>* pEnum);
	bool MultiRectangle (long* plObjNr, long lObjAnz, Rectangle& Rec);
	bool PointSymbolSize (long lONr, int& iPixX, int& iPixY);
	HRESULT DoDragDropAction (DWORD dwFlags);

	HRESULT InitProgressIndicator (IProgressIndicator2* pPI, ResID uiTitel, ResID uiAdjust,
								   ulong ulMaxPos, ulong ulMinPos = 1);
	HRESULT RegisterPI (IProgressIndicator2* pPI);
	HRESULT UnRegisterPI (void);

	void RegisterNotificationM (UINT wMsg, bool isLocal, bool& bRN);
	void UnRegisterNotificationM (UINT wMsg, bool isLocal, bool& bURN);

	HRESULT GetObjNummern (IDataObject* pIDataSource);
	bool UmrissVektor (void);

protected:
// überladene virtuelle Funktionen
	STDMETHOD_(bool, MenuInit) (HMENU hMenu, LPARAM lParam, HWND);
	STDMETHOD_(bool, InitExtension) (short iMode);
	STDMETHOD_(bool, UnLoadExtension) (void);
	STDMETHOD_(bool, MenuCommand) (UINT uiMenuID, HWND);
	STDMETHOD_(LRESULT, Notification) (WPARAM wPar, LPARAM lPar);
	STDMETHODIMP_(LRESULT) WindowsNotification (UINT wMsg, WPARAM wPar, LPARAM lPar);

// weitere Memberfunktionen
	bool InstallToolbarButtons (void);
	bool RemoveToolbarButton (void);
	void LRMouseButtonDn (Point& Pt);
	void LMouseDrag (Point& Pt);
	void LMouseButtonUp (void);
	void RMouseButtonDn (void);
	void BandingStart (bool bVor, bool bNach);
	void Banding (Point& Pt);
	void BandingStop (void);
	void ObjektZeichnen (void);
	Point DialogPosit (ObjContainer* pOC, Dimension);
	ObjContainer EObjContainer (EObjekt* pEO);
	void idb_Speichern (NeuEditDlg*);
	Point idb_Fortsetzen (void);
	bool LeftMouseDownNew (Point Pt);
	bool RightMouseUpNew (Point Pt);
	void CursorWechselNewGrab (Point Pt);
	bool LeftMouseDownModify (Point Pt);
	bool CursorUeberMarkObjekt (Point Pt);
	void LeftMouseUpModify (Point Pt);
	bool RightMouseDownModify (void);
	bool RightMouseUpModify (Point Pt);
	void CursorWechselMod (void);
	void CursorWechselModGrab (Point Pt, Curs CurForm, Pointer* pCursor);
	bool FlaechenteilungsDialog (void);
	bool StuetzpunkteMarkieren (void);
	bool StuetzpunkteTesten (Point, IObjektGeometrie**, long&);
	Rectangle AusschnittFuerZeichnen (IObjektGeometrie* pIOG, Punkt& ModPkt, long lInd);
	void AusschnittErmitteln (IObjektGeometrie* pIOG, Punkt& ModPkt, long lInd, Point& PLO, Point& PRU);
	bool StuetzpunkteDeMarkieren (void);

	void ObjectModifyMenu (pWindow pW, Point Pt, uint resID);
	void EditVertex (IObjektGeometrie* pIOG, long lInd);

	bool _GetDebugOutputFlag (void);

public:
// Konstruktor / Destruktor
		GeoEditExtension (void);
		~GeoEditExtension (void);

// Memberfunktion
	bool IsSightSelected (void) { return m_bSight; } 

// weitere Memberfunktionen
	bool MarkierungenBearbeiten (IObjektGeometrie* pIOG, bool = true);
	bool PointInMarker (Point, Marker*);
	void MoveMarker (Point);
	bool MarkierungenTesten (Punkt, IObjektGeometrie* pIOG, long&);
	bool GeometrieInBaum (long lONr);
	bool GeometrieAusBaum (long lONr);

// Memberfunktionen für Drag-And-Drop
	bool IsDropSource (void);
	bool FQueryDrop (void);
	bool MoveObjectsBuild (long* plAltObjNr, short iAnzVO, POINT ptZiel, bool bCopy);
	bool MoveTextObject (bool bCopy, long lAltObjNr, KoOrd XDiff, KoOrd YDiff,
						 long& lNeuObjNr);
	bool RestoreTextDependence (bool bCopy, long* plAltObjNr, long* plNeuObjNr, short iAnzVO);
	bool AddToORWindow (long lAltObjNr, long lNeuObjNr);
	bool FensterVerschobeneObjekte (long* plNeuObjNr, short iAnzVO, Rectangle Rec);
	bool GiveFeedBack (Point* pPolyPoly, int* piPolyCounts, long lAnz, POINTL ptlZiel);
	bool PunktSymbolGroesse (IObjektGeometrie* pIOG, int& iPixX, int& iPixY);

// IUnknown methods
//	STDMETHODIMP QueryInterface (REFIID riid, LPVOID* ppv);


	BEGIN_COM_MAP(GeoEditExtension)		// Makro
		COM_INTERFACE_ENTRY(ITriasXtension2)
		COM_INTERFACE_ENTRY(ITriasXtension)
		COM_INTERFACE_ENTRY(ITRiASDropTarget)
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
	END_COM_MAP()
	DECLARE_NO_REGISTRY()

	DECLARE_NOT_AGGREGATABLE_SINGLE(GeoEditExtension, g_pTE)

	BEGIN_CONNECTION_POINT_MAP(GeoEditExtension)	// Makro
		CONNECTION_POINT_ENTRY(m_PPI)
	END_CONNECTION_POINT_MAP()

	// ITRiASDropTarget-Methoden (unterscheiden sich in den Parametern von den IDropTarget-Methoden
	// dadurch, daß die ersten beiden Parameter hinzugekommen sind)
	STDMETHOD (DragEnter) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, IDataObject* pIDataSource,
						   DWORD grfKeyState, POINTL ptl, DWORD* pdwEffekt);
	STDMETHOD (DragOver) (THIS_ DRAGDROPTYPE rgType, HWND hWnd,	DWORD grfKeyState, POINTL ptl,
						  DWORD* pdwEffekt);
	STDMETHOD (DragLeave) (THIS_ DRAGDROPTYPE rgType, HWND hWnd);
	STDMETHOD (Drop) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, IDataObject* pIDataSource,
					  DWORD grfKeyState, POINTL ptl, DWORD* pdwEffekt);

};

#endif  // _GEOEDIT_HXX
