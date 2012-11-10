// Deklaration: Innenkontur hinzufügen
// File: IslandAdd.h
// W. Mörtl

#ifndef _ISLANDADD_H_
#define _ISLANDADD_H_


#include "SmartInterfaces.h"

#include "objgguid.h"	// CLSID_ObjektGeometrie, IID_IInitObjektGeometrie



///////////////////////////////////////////////////////////////////////////////////////////////
// Klasse für das Hinzufügen von Innenkonturen
// IModifyOperation ist das Interface, das alle ModifyOperation's für die CObjectModify-Klasse
// bereitstellen, d.h. das Interface, über das die CObjectModify-Klasse die ModifyOperation's
// rufen kann (Gegen-Interface zu IModifyClassSite)
class CIslandAdd : public IModifyOperation,
    			   public ITRiASNotificationSink,
    			   public ITRiASSysNotificationSink,
    			   public CComObjectRoot,
    			   public CComCoClass<CIslandAdd, &CLSID_IslandAdd>
{
private:
    pWindow m_pVWnd;				// TRiAS-ViewFenster
    CoordTransX* m_pCT;				// KoordinatenTransformation
    bool m_bIsPaint;				// Hintergrund (durch GEOVIEWEVT_PaintingView bzw.
    								// GEOVIEWEVT_ViewPainted ausgelöst) wird gezeichnet (true)

    bool m_LeftButtonSem;			// Synchronisation für die linke bzw. rechte Maustaste, um
    bool m_RightButtonSem;			//  sicher zu stellen, daß "Down" und "Up" im gleichen
    								//  Fenster kommen
    CursPos m_OldCP;				// bisherige CursorPosition
    CursPos m_NewCP;				// aktuelle CursorPosition

    WEditExtensionSite m_wEdExSite;	// Interface von CGeoEditExtension für EditierOperationen
    WTopicalObjects m_wTopObjs;		// Interface der Klasse CTopicalObjects

    WEnumObjektGeometrie m_wBelowObjs;// m_wTopObjs-Flächenobjekte, die bei Aufruf dieser
    								// Operation unter der Mausspitze lagen
    WEnumObjektGeometrie m_wModObjs;// m_wBelowObjs-Flächenobjekte, zu denen eine Innenkontur
    								// hinzugefügt werden soll (Untermenge von m_wBelowObjs)
    WEnumObjektGeometrie m_wAndArea;// eine Durchschnittsfläche der m_wModObjs-Flächen
	long m_lAndONr;					// Objektnummer für Durchschnittsfläche m_wAndArea
    ulong m_ulModCnt;				// Anzahl der m_wModObjs-Flächenobjekte

    WObjektGeometrie m_wIsland;		// ObjektGeometrie der neuen Insel
    long m_lInSize;					// Anzahl der schon editierten Stützpunkte
	Point m_FirstPt;				// erster Punkt der aktuell editierten Kontur in BS- bzw.
    EPunkt m_FirstPkt;				//  in DB-Koordinaten
	Point m_LastPt;					// letzter Punkt der aktuell editierten Kontur in BS- bzw.
    EPunkt m_LastPkt;				//  in DB-Koordinaten
    WDragObject m_wDragObj;			// die aktuell nachgezogene Linie
    bool m_bCloseLineDelete;		// Linie löschen, die die editierte Insel schließt

    int m_iGrabCnt;					// Anzahl der hintereinander gegrabten Punkte (für
    								// CommonBorder)
    WEnumObjektGeometrie m_wGrabObjs;// die Linien- bzw. Flächenobjekte der ausgewählten
    								// Objekte, die alle in m_iGrabCnt gezählten GrabPunkte als
    								// Stützpunkte besitzen
    KoOrd* m_pGrabPktX;				// die Koordinaten der in
    KoOrd* m_pGrabPktY;				//  m_iGrabCnt gezählten GrabPunkte
    HRESULT m_hrComBorder;			// return-Wert bei Test auf CommonBorder-Möglichkeit
    long m_lComONr;					// Objektnummer des Objektes, von dem die gemeinsamen
    								// Stützpunkte bei CommonBorder übernommen werden können

    double m_dAktDreieck;			// Flächeninhalt der aktuellen Dreiecksfläche
    double m_dAktInsel;				// Flächeninhalt der aktuellen Insel
    double m_dAktGesFlaeche;		// aktueller Gesamtflächeninhalt einer Fläche, zu der eine
    								// neue Insel hinzugefügt werden soll

    // Memberfunktionen
    HRESULT KeyDown (WPARAM wParam);
    HRESULT KeyUp (WPARAM wParam);
    HRESULT MouseMove (HWND hWnd, LPARAM lParam);
    HRESULT LeftMouseDown (LPARAM lParam);
    HRESULT LeftMouseUp (void);
    void RightMouseDown (LPARAM lParam);
    HRESULT RightMouseUp (void);
	HRESULT LeftDoubleClick (void);
    HRESULT BuildModObjects (void);
    HRESULT BuildAndArea (void);
    void VisalAndArea (ulong ulIdent);
    HRESULT IsGrabAllowableForIslandAdd (IEnumObjektGeometrie* pIEnumOG);
    HRESULT NewIslandObject (void);
    HRESULT ContinueButtonAction (void);
    void IslandButtonAction (ulong ulIdent);
    HRESULT AddIsland (ulong ulIdent);
    HRESULT StoreAreaWithNewIsland (IObjektGeometrie* pIOG, ulong ulIdent);
    HRESULT SetStartingContents (void);
    bool AktuelleWerteAnzeigen (Point Pt);

public:
    // Konstruktor, Destruktor
    CIslandAdd (void);
    ~CIslandAdd (void);

    DECLARE_REGISTRY_RESOURCEID(IDR_ISLANDADD)

    BEGIN_COM_MAP(CIslandAdd)
    	COM_INTERFACE_ENTRY(ITRiASNotificationSink)
    	COM_INTERFACE_ENTRY(ITRiASSysNotificationSink)
    	COM_INTERFACE_ENTRY(IModifyOperation)
    END_COM_MAP()

    // IModifyOperation
    STDMETHOD (SetModifyClassSite) (IEditExtensionSite* pIEdExSite, IModifyClassSite*);
    STDMETHOD (LineElongation) (IEnumObjektGeometrie*, long, long);
    STDMETHOD (AreaPartition) (long, POINT);
    STDMETHOD (IslandAddition) (IEnumObjektGeometrie* pBelowObjs);
    STDMETHOD (Rectangularity) (long, int, long, double, double, double, IEnumObjectsByNumber**);
 	STDMETHOD (MakeCommonBorder) (IEnumObjektGeometrie*, long, long);

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

#endif // _ISLANDADD_H_
