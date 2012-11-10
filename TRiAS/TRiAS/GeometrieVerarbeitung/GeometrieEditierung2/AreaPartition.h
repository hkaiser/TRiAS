// Deklarationen: Flächenobjekt	teilen
// File: AreaPartition.h
// W. Mörtl

#ifndef _AREAPARTITION_H_
#define _AREAPARTITION_H_


#include "SmartInterfaces.h"

#include "operguid.h"	// CLSID_GeometrieOperationen, IID_IExtendObjOper
#include "objgguid.h"	// CLSID_ObjektGeometrie, IID_IInitObjektGeometrie


///////////////////////////////////////////////////////////////////////////////////////////////
// Klasse für das Teilen einer Fläche
// IModifyOperation ist das Interface, das alle ModifyOperation's für die CObjectModify-Klasse
// bereitstellen, d.h. das Interface, über das die CObjectModify-Klasse die ModifyOperation's
// rufen kann (Gegen-Interface zu IModifyClassSite)
class CAreaPartition : public IModifyOperation,
					   public ITRiASNotificationSink,
					   public ITRiASSysNotificationSink,
					   public CComObjectRoot,
					   public CComCoClass<CAreaPartition, &CLSID_AreaPartition>
{
private:
	pWindow m_pVWnd;				// TRiAS-ViewFenster
	bool m_bIsPaint;				// Hintergrund (durch GEOVIEWEVT_PaintingView bzw.
									// GEOVIEWEVT_ViewPainted ausgelöst) wird gezeichnet (true)

	bool m_LeftButtonSem;			// Synchronisation für die linke bzw. rechte Maustaste, um
	bool m_RightButtonSem;			//  sicher zu stellen, daß "Down" und "Up" im gleichen
									//  Fenster kommen
	CursPos m_OldCP;				// bisherige CursorPosition
	CursPos m_NewCP;				// aktuelle CursorPosition

	WEditExtensionSite m_wEdExSite;	// Interface von CGeoEditExtension für EditierOperationen
	WTopicalObjects m_wTopObjs;		// Interface der Klasse CTopicalObjects

	WObjektGeometrie m_wAreaObj;	// ObjektGeometrie und
	long m_lONr;					//  Parameter der zu teilenden Fläche
	KoOrd* m_plX;
	KoOrd* m_plY;
	long* m_plCnt;
	WObjektGeometrie m_wSectLine;	// ObjektGeometrie der Schnittlinie
	Point m_LastPt;					// letzter aktuell editierter Punkt	(in BS-Koordinaten)
	WDragObject m_wDragObj;			// die aktuell nachgezogene Linie
	KoOrd m_lGrabX, m_lGrabY;		// GrabPunkt

	// Memberfunktionen
	HRESULT KeyDown (WPARAM wParam);
	HRESULT KeyUp (WPARAM wParam);
	HRESULT MouseMove (LPARAM lParam);
	HRESULT LeftMouseDown (LPARAM lParam);
	HRESULT LeftMouseUp (HWND hWnd);
	void RightMouseDown (LPARAM lParam);
	HRESULT RightMouseUp (HWND hWnd);
	HRESULT SectionDialog (void);
	HRESULT ContinueButtonAction (void);
	HRESULT AreaSplitting (void);

public:
	// Konstruktor, Destruktor
	CAreaPartition (void);
	~CAreaPartition (void);

	DECLARE_REGISTRY_RESOURCEID(IDR_AREAPARTITION)

	BEGIN_COM_MAP(CAreaPartition)
		COM_INTERFACE_ENTRY(ITRiASNotificationSink)
		COM_INTERFACE_ENTRY(ITRiASSysNotificationSink)
		COM_INTERFACE_ENTRY(IModifyOperation)
	END_COM_MAP()

	// IModifyOperation
	STDMETHOD (SetModifyClassSite) (IEditExtensionSite* pIEdExSite,	IModifyClassSite*);
	STDMETHOD (LineElongation) (IEnumObjektGeometrie* pModObjs, long lRMX, long lRMY);
	STDMETHOD (AreaPartition) (long lONr, POINT ptRM);
	STDMETHOD (IslandAddition) (IEnumObjektGeometrie*);
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

#endif //_AREAPARTITION_H_
