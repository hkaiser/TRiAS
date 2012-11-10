// Deklarationen: Design-Funktionen
// File: Designing.h
// W. Mörtl

#ifndef _DESIGNING_H_
#define _DESIGNING_H_


#include "SmartInterfaces.h"


///////////////////////////////////////////////////////////////////////////////////////////////
// Klasse für die Design-Funktionen
// IEditOperation ist das Interface, das alle EditierOperationen für die GeoEdit-Erweiterung
// bereitstellen, d.h. das Interface, über das die GeoEdit-Erweiterung die EditierOperationen
// rufen kann (Gegen-Interface zu IEditExtensionSite)
class CDesigning : public IEditOperation,
				   public ITRiASNotificationSink,
				   public ITRiASSysNotificationSink,
				   public CComObjectRoot,
				   public CComCoClass<CDesigning, &CLSID_Designing>
{
private:
    WTriasXtensionSite m_Site;		// TRiAS-Kontext
    DWORD m_dwCookieN;				// Nummer des ConnectionPoint für ITRiASNotificationSink
    DWORD m_dwCookieSN;				// Nummer des ConnectionPoint für ITRiASSysNotificationSink
    pWindow m_pVWnd;				// TRiAS-ViewFenster
    CoordTransX* m_pCT;				// KoordinatenTransformation
	DoublePair m_dpUF;				// Umrechnungsfaktor bei geodätischen Koordinaten
    bool m_bIsPaint;				// Hintergrund (durch GEOVIEWEVT_PaintingView bzw.
    								// GEOVIEWEVT_ViewPainted ausgelöst) wird gezeichnet (true)
    bool m_RightButtonSem;			// Synchronisation für die rechte Maustaste, um sicher zu
									// stellen, daß "Down" und "Up" im gleichen Fenster kommen
    LPARAM m_lParamOld;				// letzte Mausposition
    CursPos m_OldCP;				// bisherige CursorPosition
    CursPos m_NewCP;				// aktuelle CursorPosition

    WEditExtensionSite m_wEdExSite;	// Interface von CGeoEditExtension für EditierOperationen
    WTopicalObjects m_wTopObjs;		// Interface der Klasse CTopicalObjects
    WEnumObjektGeometrie m_wBelowObjs;// diejenigen der ausgewählten Objekte, die unter der
    								//  Mausspitze liegen

	Point m_ptRM;					// BS-Punkt, bei dem rechte Maustaste gedrückt wurde
	RestrType m_ResType;			// Form der Konstruktionshilfslinie (STRECKE, GERADE, KREIS)
	bool m_bRightAngle;				// im Dialog wurde "rechter Winkel" ausgewählt (true)
	double m_dRelAngle;				// Winkel für Hilfslinie aus der Dialogeingabe
	double m_dLength;				// Länge der Hilfslinie
	EPunkt m_FixPkt;				// der ausgewählte Fixpunkt
	WRestrictLine m_wRestrLine;		// Interface zu Konstruktionshilfslinie

    // Memberfunktionen
    HRESULT DisconnectFromServer (void);

    HRESULT MouseMove (LPARAM lParam);
    void RightMouseDown (LPARAM lParam);
    HRESULT RightMouseUp (void);
	HRESULT DesignRestrictLine (void);
    HRESULT RefreshCursorForm (void);
	bool IsRestrictLineAtVertex (IObjektGeometrie* pIOG, int iOT, long lCnt, long lPInd);
	bool RegardingCoordinates (IObjektGeometrie* pIOG, long lCnt, long lPInd, long lSInd,
							   KoOrd& x0, KoOrd& y0, KoOrd& x1, KoOrd& y1);
	double GradientAngle (double x0, double y0, double x1, double y1);
	HRESULT RepaintTemporaryObjects (void);
	bool OnePointInline (IObjektGeometrie* pIOG, int iOT, long lCnt, long lPInd);

public:
    // Konstruktor, Destruktor
    CDesigning (void);
    ~CDesigning (void);

    DECLARE_REGISTRY_RESOURCEID(IDR_DESIGNING)

    BEGIN_COM_MAP(CDesigning)
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

#endif //_DESIGNING_H_
