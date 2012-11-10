// Deklarationen: Verschieben eines Stützpunktes
// File: VertexMove.h
// W. Mörtl

#ifndef _VERTEXMOVE_H_
#define _VERTEXMOVE_H_


#include "SmartInterfaces.h"

#include "objgguid.h"	// CLSID_ObjektGeometrie, IID_IInitObjektGeometrie


///////////////////////////////////////////////////////////////////////////////////////////////
// Klasse für das Verschieben eines (gemeinsamen) Stützpunktes
// IModifyOperation ist das Interface, das alle ModifyOperation's für die CObjectModify-Klasse
// bereitstellen, d.h. das Interface, über das die CObjectModify-Klasse die ModifyOperation's
// rufen kann (Gegen-Interface zu IModifyClassSite)
class CVertexMove : public IModifyOperation,
					public ITRiASNotificationSink,
					public ITRiASSysNotificationSink,
					public CComObjectRoot,
					public CComCoClass<CVertexMove, &CLSID_VertexMove>
{
private:
	pWindow m_pVWnd;				// TRiAS-ViewFenster

	WEditExtensionSite m_wEdExSite;	// Interface von CGeoEditExtension für EditierOperationen
	WModifyClassSite m_wModClSite;	// Interface der Klasse CObjectModify
	WTopicalObjects m_wTopObjs;		// Interface der Klasse CTopicalObjects

	CursPos m_OldCP;				// bisherige CursorPosition
	CursPos m_NewCP;				// aktuelle CursorPosition
	Point m_ptMSp;					// BS-Koordinaten der Mausspitze
	KoOrd m_lMSpX, m_lMSpY;			// DB-Koordinaten der Mausspitze

	WEnumObjektGeometrie m_wBelowObjs;// diejenigen der ausgewählten Objekte, die zu BEGINN der
									//  Stützpunkt-Verschiebe-Aktion unter der Mausspitze lagen
	EPunkt m_ModPkt;				// Punkt, der verschoben werden soll
	WEnumObjektGeometrie m_wActBelowObjs;// diejenigen der ausgewählten Objekte, die AKTUELL
									// unter der Mausspitze liegen
	Marker* m_pMk;					// Markierungsquadrat des zu verschiebenden Punktes
	WDragObject m_wDragObj;			// das aktuell nachgezogene Linien-Tupel

	// Memberfunktionen
	HRESULT KeyDown (HWND hWnd, WPARAM wParam);
	HRESULT KeyUp (WPARAM wParam);
	HRESULT MouseMove (LPARAM lParam);
	HRESULT LeftMouseDown (void);
	bool LeftMouseUp (LPARAM lParam);

public:
	// Konstruktor, Destruktor
	CVertexMove (void);
	~CVertexMove (void);

	DECLARE_REGISTRY_RESOURCEID(IDR_VERTEXMOVE)

	BEGIN_COM_MAP(CVertexMove)
    	COM_INTERFACE_ENTRY(ITRiASNotificationSink)
		COM_INTERFACE_ENTRY(ITRiASSysNotificationSink)
		COM_INTERFACE_ENTRY(IModifyOperation)
	END_COM_MAP()

	// IModifyOperation
	STDMETHOD (SetModifyClassSite) (IEditExtensionSite* pIEdExSite,
									IModifyClassSite* pIModClSite);
	STDMETHOD (LineElongation) (IEnumObjektGeometrie*, long, long);
	STDMETHOD (AreaPartition) (long, POINT);
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

#endif //_VERTEXMOVE_H_
