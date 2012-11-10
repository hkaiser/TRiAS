// Deklarationen: Geometrie existierender Objekte modifizieren
// File: ObjectModify.h
// W. Mörtl

#ifndef _OBJECTMODIFY_H_
#define _OBJECTMODIFY_H_


#include "SmartInterfaces.h"

#include "reinguid.h"	// CLSID_GeometrieBereinigung, IID_IExtendGeoRein
#include "objgguid.h"	// CLSID_ObjektGeometrie, IID_IInitObjektGeometrie


///////////////////////////////////////////////////////////////////////////////////////////////
// Klasse für die Modifizierung der Geometrie existierender Objekte
// IEditOperation ist das Interface, das alle EditierOperationen für die GeoEdit-Erweiterung
// bereitstellen, d.h. das Interface, über das die GeoEdit-Erweiterung die EditierOperationen
// rufen kann (Gegen-Interface zu IEditExtensionSite);
// IMenuHandling ist das Interface, das nur die EditierOperationen für die GeoEdit-Erweiterung
// bereitstellen, die von der GeoEdit-Erweiterung über die MenüBehandlung informiert werden
// müssen
// IModifyClassSite ist das Interface, das die CObjectModify-Klasse für die ModifyOperation's
// (VertexMove, ...) bereitstellt, d.h. das Interface, über das die ModifyOperation's die
// CObjectModify-Klasse rufen kann (Gegen-Interface zu IModifyOperation)
class CObjectModify : public IEditOperation,
    				  public IMenuHandling,
    				  public IModifyClassSite,
    				  public ITRiASNotificationSink,
    				  public ITRiASSysNotificationSink,
    				  public CComObjectRoot,
    				  public CComCoClass<CObjectModify, &CLSID_ObjectModify>
{
private:
    WTriasXtensionSite m_Site;		// TRiAS-Kontext
    DWORD m_dwCookieN;				// Nummer des ConnectionPoint für ITRiASNotificationSink
    DWORD m_dwCookieSN;				// Nummer des ConnectionPoint für ITRiASSysNotificationSink
    pWindow m_pVWnd;				// TRiAS-ViewFenster

    WExtendGeoRein m_wGeoRein;		// Interface für Ankopplung von GeoRein.ext	
    bool m_bGeoRein;				// Ankopplung von GeoRein.ext ist erfolgt (true)

    bool m_LeftButtonSem;			// Synchronisation für die linke bzw. rechte Maustaste, um
    bool m_RightButtonSem;			//  sicher zu stellen, daß "Down" und "Up" im gleichen
    								//  Fenster kommen
    LPARAM m_lParamOld;				// letzte Mausposition
    CursPos m_OldCP;				// bisherige CursorPosition
    CursPos m_NewCP;				// aktuelle CursorPosition
  	BOOL m_bSpezCP;					// Cursor hat eine speziellen Position
    EPunkt m_GrabPkt;				// Stützpunkt, in dessen Marker sich der Cursor befindet
	Point m_ptRM;					// BS-Punkt, bei dem rechte Maustaste gedrückt wurde
  	EPunkt m_PktRM;					// DB-Punkt, bei dem rechte Maustaste gedrückt wurde
    long m_lEpsilon;				// Epsilon für Cursor-Umschaltung

    WEditExtensionSite m_wEdExSite;	// Interface von CGeoEditExtension für EditierOperationen
    WTopicalObjects m_wTopObjs;		// Interface der Klasse CTopicalObjects
    WEnumObjektGeometrie m_wBelowObjs;// diejenigen der ausgewählten Objekte, die unter der
    								//  Mausspitze liegen
    int m_iAllOT;					// Kombination der Typ(en) der ausgewählten Objekte
	long m_lBelowLACnt;				// Anzahl der unter der Mausspitze liegenden Linien und Flächen
	bool m_bRW;						// mindestens ein m_wBelowObjs-Objekt gehört zu einer
									// R/W-Objektklasse (true)

    WModifyOperation m_wModOper;	// Interface zur aktuellen ModifyOperation (wird durch
									//  "COM_INTERFACE_ENTRY(IModifyOperation)" z. B. in 
									//  AreaPartition.h gesetzt
    bool m_bStopLMUp;				// ModifyOperation bei LeftMouseUp beenden (true)
    bool m_bMenu;					// Menü wird angezeigt (true)

    long m_lAktONr;					// Objektnummer des aktivierten (blinkenden) Objektes, das
    								// rechtwinklig gemacht werden soll 
    int m_iRecKInd;					// Konturindex bei Rechtwinkligmachen
    long m_lRecStInd;				// niedrigster Stützpunktindex der Bezugsstrecke für
    								// Rechtwinkligmachen

protected:
    // Memberfunktionen (ObjectModify.cpp)
    HRESULT DisconnectFromServer (void);

    HRESULT KeyDown (long hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
    HRESULT KeyUp (long hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
	HRESULT WMChar (long hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
    HRESULT MouseMove (long hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
    HRESULT LeftMouseDown (long hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
    HRESULT LeftMouseUp (long hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
    HRESULT RightMouseDown (long hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
    HRESULT RightMouseUp (long hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
	HRESULT LeftDoubleClick (long hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
//	void WindowsTimer (WPARAM wParam);

    HRESULT GetBelowObjTypes (void);
    bool AllOpen (void);
	bool AllClosed (void);
    bool OneDataSource (void);
	HRESULT MenuSelfTouch (HMENU hMenu);
	HRESULT MenuCommonBorder (HMENU hMenu);
    void PluralTexts (HMENU hMenu, UINT uiMOffset);
    void ObjectModifyMenu (pWindow pW, Point Pt, uint resID);
    RECT SectorDefine (IObjektGeometrie* pIOG, long lModPktX, long lModPktY, long lInd,
    				   bool bVtDel);
    HRESULT GeoReinInterface (void);

    // Memberfunktionen (ObjectModifyFunc.cpp)
    HRESULT VertexMoveStart (long hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
    HRESULT VertexAddStart (long hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
    HRESULT ManualVertexModify (void);
    HRESULT ManualVertexAdd (void);
    HRESULT VertexDelete (void);
	HRESULT ActualVertexDelete (IObjektGeometrie* pIOG, long lInd, short& iKontInd,
							 Rectangle& AllRec, bool& bAllRecInit, bool& bMod, bool& bConti);
	HRESULT LineSplitting (void);
    HRESULT LineElongationStart (void);
	HRESULT LineToArea (void);				// #HK000208
    HRESULT AreaPartitionStart (void);
	HRESULT ObjectsCut (void);
	HRESULT SelfTouchCleaning (IObjektGeometrie* pIOG, RECT* pRec);
	HRESULT StoreNewLinepart (IObjektGeometrie* pOrigObj, IObjektGeometrie* pNewObj,
							  RECT* pRec);
    HRESULT IslandAddStart (void);
    HRESULT IslandsDelete (void);
	HRESULT AreaToLine (void);
    Rectangle IslandParameter (IObjektGeometrie* pIOG, int iKontInd, KoOrd* plXI,
    						   KoOrd* plYI);
    HRESULT MakeAreaRectangular (void);
    HRESULT CommonBorderStart (void);
    bool ObjectsDelete (void);

public:
    // Konstruktor, Destruktor
    CObjectModify (void);
    ~CObjectModify (void);

    DECLARE_REGISTRY_RESOURCEID(IDR_OBJECTMODIFY)

    BEGIN_COM_MAP(CObjectModify)
    	COM_INTERFACE_ENTRY(ITRiASNotificationSink)
    	COM_INTERFACE_ENTRY(ITRiASSysNotificationSink)
    	COM_INTERFACE_ENTRY(IEditOperation)
    	COM_INTERFACE_ENTRY(IMenuHandling)
    	COM_INTERFACE_ENTRY(IModifyClassSite)
    END_COM_MAP()

    // Memberfunktion
    HRESULT TestActObject (long lONr);

    // IEditOperation
    STDMETHOD (SetEditExtensionSite) (IEditExtensionSite* pIEdExSite);
	STDMETHOD (InformRestrictLinesState) (IRestrictLine*, IRestrictLine*);
	STDMETHOD (DeleteRestrictedCursor) (void);

    // IMenuHandling
    STDMETHOD (WorkMenuCommand) (WPARAM MenuItemID, HWND hWnd);
    STDMETHOD (WorkMenuInit) (HMENU hMenu, LPARAM lParam, HWND hWnd);
    STDMETHOD (WorkMenuSelect) (UINT uiMenuID, HMENU hMenu, HWND hWnd);

    // IModifyClassSite
    STDMETHOD (GetParameter) (long* plMPX, long* plMPY, IEnumObjektGeometrie** ppBelowObjs);
    STDMETHOD (SectorToDraw) (IUnknown* pIOG, long lModPktX, long lModPktY, long lInd,
							  BOOL bVtDel, RECT* pSector);
    STDMETHOD (ModObjSpeicherung) (IUnknown* pIOG, long lModPktX, long lModPktY, long lInd,
    							   BOOL bVtDel, TestRicht trRicht, RECT* pRec);
    STDMETHOD (SetGrabPoint) (long lGPX, long lGPY);
    STDMETHOD (RefreshCursorForm) (void);

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

#endif //_OBJECTMODIFY_H_
