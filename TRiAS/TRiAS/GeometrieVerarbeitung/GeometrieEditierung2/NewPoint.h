// Deklarationen: Editierung eines neuen Punktobjektes
// File: NewPoint.h
// W. Mörtl

#ifndef _NEWPOINT_H_
#define _NEWPOINT_H_


#include "SmartInterfaces.h"


///////////////////////////////////////////////////////////////////////////////////////////////
// Klasse für die Editierung eines neuen Punktobjektes
// IEditOperation ist das Interface, das alle EditierOperationen für die GeoEdit-Erweiterung
// bereitstellen, d.h. das Interface, über das die GeoEdit-Erweiterung die EditierOperationen
// rufen kann (Gegen-Interface zu IEditExtensionSite)
class CNewPoint : public IEditOperation,
				  public ITRiASNotificationSink,
				  public ITRiASSysNotificationSink,
				  public CComObjectRoot,
				  public CComCoClass<CNewPoint, &CLSID_NewPoint>
{
private:
	WTriasXtensionSite m_Site;		// TRiAS-Kontext
    DWORD m_dwCookieN;				// Nummer des ConnectionPoint für ITRiASNotificationSink
	DWORD m_dwCookieSN;				// Nummer des ConnectionPoint für ITRiASSysNotificationSink
    pWindow m_pVWnd;				// TRiAS-ViewFenster
    bool m_bIsPaint;				// Hintergrund (durch GEOVIEWEVT_PaintingView bzw.
    								// GEOVIEWEVT_ViewPainted ausgelöst) wird gezeichnet (true)

	bool m_RightButtonSem;			// Synchronisation für die rechte Maustaste, um sicher zu
									//  stellen, daß "Down" und "Up" im gleichen Fenster kommen
	LPARAM m_lParamOld;				// letzte Mausposition
	CursPos m_OldCP;				// bisherige CursorPosition
	CursPos m_NewCP;				// aktuelle CursorPosition

	WEditExtensionSite m_wEdExSite;	// Interface von CGeoEditExtension für EditierOperationen
	WTopicalObjects m_wTopObjs;		// Interface der Klasse CTopicalObjects
	WEnumObjektGeometrie m_wAllTObjs;// die ausgewählten Objekte

	WObjektGeometrie m_wObj;		// ObjektGeometrie des neuen Punktobjektes
	LPARAM m_lParam;				// LPARAM-Wert, bei dem rechte Maustaste gedrückt wurde

	WRestrictLine m_wRestrLine1;	// Interface zu Konstruktionshilfslinie
	WRestrictLine m_wRestrLine2;	// Interface zu Konstruktionshilfslinie
	WRestrictCursor m_wRestrictCursor;// der abgetrennte, auf einer Hilfslinie nachgezogene Cursor
	POINT m_PTCur;					// aktuelle Cursorposition auf einer Konstruktionshilfslinie
	bool m_bMessBox;				// bei 2 Hilfslinien wurde eine MessageBox angezeigt (true)

	// Memberfunktionen
	HRESULT DisconnectFromServer (void);

	HRESULT KeyDown (WPARAM wParam);
	HRESULT KeyUp (WPARAM wParam);
	HRESULT MouseMove (HWND hWnd, LPARAM lParam);
	void RightMouseDown (LPARAM lParam);
	HRESULT RightMouseUp (void);
	HRESULT LeftDoubleClick (LPARAM lParam);
	HRESULT Grabbing (KoOrd& PktX, KoOrd& PktY);
	HRESULT ShowDialogForPoint (void);
	void DrawObjBackground (void);

public:
	// Konstruktor, Destruktor
	CNewPoint (void);
	~CNewPoint (void) {};

	DECLARE_REGISTRY_RESOURCEID(IDR_NEWPOINT)

	BEGIN_COM_MAP(CNewPoint)
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

#endif //_NEWPOINT_H_
