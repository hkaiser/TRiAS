// Deklarationen: Editierung eines neuen Flächenobjektes
// File: NewArea.h
// W. Mörtl

#ifndef _NEWAREA_H_
#define _NEWAREA_H_


#include "SmartInterfaces.h"


///////////////////////////////////////////////////////////////////////////////////////////////
// Klasse für die Editierung eines neuen Flächenobjektes
// IEditOperation ist das Interface, das alle EditierOperationen für die GeoEdit-Erweiterung
// bereitstellen, d.h. das Interface, über das die GeoEdit-Erweiterung die EditierOperationen
// rufen kann (Gegen-Interface zu IEditExtensionSite)
class CNewArea : public IEditOperation,
    			 public ITRiASNotificationSink,
    			 public ITRiASSysNotificationSink,
    			 public CComObjectRoot,
    			 public CComCoClass<CNewArea, &CLSID_NewArea>
{
private:
    WTriasXtensionSite m_Site;		// TRiAS-Kontext
    DWORD m_dwCookieN;				// Nummer des ConnectionPoint für ITRiASNotificationSink
    DWORD m_dwCookieSN;				// Nummer des ConnectionPoint für ITRiASSysNotificationSink
    pWindow m_pVWnd;				// TRiAS-ViewFenster
    CoordTransX* m_pCT;				// KoordinatenTransformation
    bool m_bIsPaint;				// Hintergrund (durch GEOVIEWEVT_PaintingView bzw.
    								// GEOVIEWEVT_ViewPainted ausgelöst) wird gezeichnet (true)

    bool m_LeftButtonSem;			// Synchronisation für die linke bzw. rechte Maustaste, um
    bool m_RightButtonSem;			//  sicher zu stellen, daß "Down" und "Up" im gleichen
    								//  Fenster kommen
    LPARAM m_lParamOld;				// letzte Mausposition
    CursPos m_OldCP;				// bisherige CursorPosition
    CursPos m_NewCP;				// aktuelle CursorPosition

    WEditExtensionSite m_wEdExSite;	// Interface von CGeoEditExtension für EditierOperationen
    WTopicalObjects m_wTopObjs;		// Interface der Klasse CTopicalObjects
    WEnumObjektGeometrie m_wAllTObjs;// die ausgewählten Objekte

    WObjektGeometrie m_wObj;		// ObjektGeometrie des neuen Flächenobjektes
	LPARAM m_lParam;				// LPARAM-Wert, bei dem rechte Maustaste gedrückt wurde
    short m_iKCnt;					// Anzahl der schon editierten Konturen
    long m_lKSize;					// Größe der aktuell editierten Kontur
	Point m_FirstPt;				// erster Punkt der aktuell editierten Kontur in BS- bzw.
    EPunkt m_FirstPkt;				//  in DB-Koordinaten
	Point m_LastPt;					// letzter Punkt der aktuell editierten Kontur in BS- bzw.
    EPunkt m_LastPkt;				//  in DB-Koordinaten
	EPunkt m_pStartPkt[2];			// Startpunkte der zu zeichnenden Linien
	int m_iSPCnt;					// Anzahl der in m_pStartPkt gespeicherten Startpunkte
    WDragObject m_wDragObj;			// die aktuell nachgezogene Linie
    bool m_bCloseLineDelete;		// Linie löschen, die die editierte Fläche schließt
	bool m_bIsland;					// der nächste editierte Punkt ist Beginn einer (neuen)
    								// Insel (true)

    int m_iGrabCnt;					// Anzahl der hintereinander gegrabten Punkte (für
    								// CommonBorder)
    WEnumObjektGeometrie m_wGrabObjs;// die Linien- bzw. Flächenobjekte der m_wAllTObjs-Objekte,
    								// die alle in m_iGrabCnt gezählten GrabPunkte als
    								// Stützpunkte besitzen
    KoOrd* m_pGrabPktX;				// die Koordinaten der in
    KoOrd* m_pGrabPktY;				//  m_iGrabCnt gezählten GrabPunkte
    HRESULT m_hrComBorder;			// return-Wert bei Test auf CommonBorder-Möglichkeit
    long m_lComONr;					// Objektnummer des Objektes, von dem die gemeinsamen
    								// Stützpunkte bei CommonBorder übernommen werden können

    double m_dAktDreieck;			// Flächeninhalt der aktuellen Dreiecksfläche
    double m_dAktInsel;				// Flächeninhalt der aktuellen Insel
    double m_dAktGesFlaeche;		// aktueller Gesamtflächeninhalt einer editierten Fläche

	WRestrictLine m_wRestrLine1;	// Interface zu Konstruktionshilfslinie
	WRestrictLine m_wRestrLine2;	// Interface zu Konstruktionshilfslinie
	WRestrictCursor m_wRestrictCursor;// der abgetrennte, auf einer Hilfslinie nachgezogene Cursor
	bool m_bMessBox;				// bei 2 Hilfslinien wurde eine MessageBox angezeigt (true)
	bool m_bWithDel;				// beim Zeichnen einer nachgezogenen Linie die alte Lage
									// löschen (true)

    // Memberfunktionen
    HRESULT DisconnectFromServer (void);

    HRESULT KeyDown (HWND hWnd, WPARAM wParam);
    HRESULT KeyUp (WPARAM wParam);
    HRESULT MouseMove (LPARAM lParam);
    void LeftMouseDown (LPARAM lParam);
    HRESULT LeftMouseUp (void);
    void RightMouseDown (LPARAM lParam);
    HRESULT RightMouseUp (void);
	void LeftDoubleClick (void);
	HRESULT ShowDialogForArea (void);
    HRESULT NeueFlaeche (void);
	HRESULT Grabbing (void);
    HRESULT ContinueButtonAction (void);
    HRESULT IslandButtonAction (void);
    bool AktuelleWerteAnzeigen (Point Pt);
	HRESULT MouseMoveWithoutRestrictLines (LPARAM lParam);
	HRESULT MouseMoveWithRestrictLines (LPARAM lParam, BOOL bTopIsPaint);

public:
    // Konstruktor, Destruktor
    CNewArea (void);
    ~CNewArea (void);

    DECLARE_REGISTRY_RESOURCEID(IDR_NEWAREA)

    BEGIN_COM_MAP(CNewArea)
    	COM_INTERFACE_ENTRY(ITRiASNotificationSink)
    	COM_INTERFACE_ENTRY(ITRiASSysNotificationSink)
    	COM_INTERFACE_ENTRY(IEditOperation)
    END_COM_MAP()

    // IEditOperation
    STDMETHOD (SetEditExtensionSite) (IEditExtensionSite* pIEdExSite);
	STDMETHOD (InformRestrictLinesState) (IRestrictLine* pRestrLine1,
										  IRestrictLine* pRestrLine2);
	STDMETHOD (DeleteRestrictedCursor) (void);
    
    // ITRiASNotificationSink
    STDMETHOD(ServerEvent) (SERVEREVT se);
    STDMETHOD(ProjectEvent) (long hPr, PROJECTEVT pe, VARIANT vProj);
    STDMETHOD(GeoViewEvent) (long hPr, GEOVIEWEVT ve, VARIANT vData);
    STDMETHOD(GeoClassEvent) (long hPr, GEOCLASSEVT ce, long ulIdent);
    STDMETHOD(GeoObjectEvent) (long hPr, GEOOBJECTEVT oe, long lONr);
    STDMETHOD(GeoFeatureEvent) (long hPr, GEOFEATUREEVT fe, long ulMCode);
    STDMETHOD(GeoRelationEvent) (long hPr, GEORELATIONEVT re, long ulRCode);
    STDMETHOD(ObjectWindowEvent) (OBJWNDEVT oe, long hORWnd);
    
    // ITRiASSysNotificationSink
    STDMETHOD (WindowsMessage) (long hWnd, long uiMsg, long wParam, long lParam);

};

#endif //_NEWAREA_H_
