// Deklarationen: Klassen "CTopicalObject", "CGeoObjs" und "CTopicalObjects"
// File: TopicalObjects.h
// H. Kaiser, W. Mörtl


#ifndef __TOPICALOBJECTS_H_
#define __TOPICALOBJECTS_H_


#include "SmartInterfaces.h"

#include "objgguid.h"	// CLSID_ObjektGeometrie, IID_IInitObjektGeometrie



///////////////////////////////////////////////////////////////////////////////////////////////
// Klasse, die eine ObjektGeometrie gemeinsam mit einem Zähler verwaltet
class CTopicalObject 
{
private:
	WObjektGeometrie m_Obj;	// ObjektGeometrie selbst
	LONG m_lCnt;			// zählt, wie oft dieses Objekt selektiert wurde
	BOOL m_bIsTemporary;	// temporäres Objekt (TRUE)

public:
	CTopicalObject (void)
		: m_lCnt(0), m_bIsTemporary(FALSE)
	{
	}

	CTopicalObject (LONG lONr) throw (_com_error &)
		: m_lCnt(0), m_bIsTemporary(FALSE)
	{
	// neue IObjektGeometrie erzeugen und ...
	WInitObjektGeometrie Obj (CLSID_ObjektGeometrie);	// throws_com_error

		THROW_FAILED_HRESULT(Obj->InitObjGeometry (lONr));	// ... initialisieren
		m_Obj = Obj;	// throws_com_error
	}

	CTopicalObject (IObjektGeometrie* pIOG) 
		: m_lCnt(0), m_bIsTemporary(TRUE)
	{
		m_Obj = pIOG;
	}

// CopyConstructor
	CTopicalObject (const CTopicalObject& rObj)
		: m_lCnt(rObj.GetRefCount()), m_Obj(rObj.GetObject()),
		  m_bIsTemporary (rObj.GetTemporary())
	{
	}

// Zuweisungsoperator
	CTopicalObject& operator= (const CTopicalObject& rObj) 
	{
		m_lCnt = rObj.GetRefCount();
		m_Obj = rObj.GetObject();
		m_bIsTemporary = rObj.GetTemporary();
		return *this;
	}

// Erhöht/erniedrigt Zähler der aktuellen Selektionen
	LONG Select (void) { return ++m_lCnt; }
	LONG UnSelect (void) { return --m_lCnt; }

// Zugriff auf Member
	LONG GetRefCount (void) const { return m_lCnt; }
	const WObjektGeometrie &GetObject (void) const { return m_Obj; }
	BOOL GetTemporary() const { return m_bIsTemporary; }
};




///////////////////////////////////////////////////////////////////////////////////////////////
// Liste von IObjektGeometrien
class CGeoObjs 
{
private:
	typedef map<LONG, CTopicalObject, less<LONG> > CObjectMap;
	CObjectMap m_Objs;

	ITopicalObjects *m_pIObjs;	// Rückverweis (kein AddRef!)

public:
		CGeoObjs (ITopicalObjects *pIObjs)
			: m_pIObjs(pIObjs) {}
		~CGeoObjs() {}

// liefert Enumerator mit allen ObjektGeometrie'n
	HRESULT GetEnumObjects (IEnumUnknown **ppIEnum);

// liefert Enumerator für alle derzeit gespeicherten Objekte
	HRESULT GetEnumObjectsByNumber (IEnumObjectsByNumber** ppIEnum);
	HRESULT GetEnumObjektGeometrie (IEnumObjektGeometrie** ppIEnum, bool bAll = true);

// testet, ob lONr-Objekt in der Liste enthalten ist
	HRESULT IsObject (long lONr, BOOL* pbContain);
	HRESULT IsObject (IObjektGeometrie *pIOG, BOOL* pbContain);

// fügt ein neues Objekt zur Liste hinzu (bzw. erhöht Zähler)
	HRESULT AddObject (LONG lONr);
	HRESULT AddObject (IObjektGeometrie *pIOG);

// erniedrigt Zähler eines Objektes und entfernt dieses aus der Liste,
// wenn der Zähler auf 0 gegangen ist
	HRESULT RemoveObject (LONG lONr);
	HRESULT RemoveObject (IObjektGeometrie *pIOG);

// entfernt ein Objekt aus der Liste, unabhängig davon, ob der Zähler
// bereits 0 ist oder nicht
	HRESULT DeleteObject (LONG lONr);
	HRESULT DeleteObject (IObjektGeometrie *pIOG);

// entfernt Objekte aus der Liste
	HRESULT DeleteObjects (bool bAll = true);

// liefert Rechteck von Objekten aus der Liste
	HRESULT GetObjectsRectangle (KoOrd* plXmin, KoOrd* plXmax, KoOrd* plYmin, KoOrd* plYmax,
								 bool bAll = true);

// Objektgeometrie aus TRiAS neu einlesen
	HRESULT ChangeObject (LONG lONr);

// Anzahl der in m_Objs befindlichen ObjektGeometrie'n
	LONG Count (void) { return m_Objs.size(); }
};



///////////////////////////////////////////////////////////////////////////////////////////////
// CTopicalObjects
class CTopicalObjects : public ITopicalObjects,
						public ITRiASNotificationSink,
						public CComObjectRoot,
						public CComCoClass<CTopicalObjects, &CLSID_TopicalObjects>
{
private:
	DWORD m_dwCookie;
	WTriasXtensionSite m_Site;	// TRiAS-Kontext

	RECT m_rcHintergrund;		// Hintergrundbereich für Zeichen
	bool m_bIsPaint;			// Hintergrund (durch GEOVIEWEVT_PaintingView bzw.
								// GEOVIEWEVT_ViewPainted ausgelöst) wird gezeichnet (true)

	CGeoObjs m_TopObjs;			// Liste der ausgewählten Objekte

	bool m_bMarkVis;			// Stützpunktmarkierungen sichtbar machen (true)
	int m_iUMarkGr;				// Untergrenze der Pixelanzahl (in x- und y-Richtung) für
								//  Stützpunktmarkierungen
	int m_iOMarkGr;				// Obergrenze der Pixelanzahl (in x- und y-Richtung) für
								//  Stützpunktmarkierungen
	long m_lMBX;				// Größe einer Stützpunktmarkierung (in DB-Koordinaten) in
	long m_lMBY;				//  x- bzw. y-Richtung
	Color m_FillMC;				// Farbe des Stützpunktmarkierungen
	Color m_FirstMC;			// Randfarbe der 1. Stützpunktmarkierungen
	Color m_LastMC;				// Randfarbe der letzten Stützpunktmarkierungen
	int m_iThick;				// Stärke des (andersfarbigen) Randes
	long m_lEpsilon;			// Epsilon für Cursor-Umschaltung
	EPunkt m_GrabPkt;			// Stützpunkt, in dessen Markierungsquadrat sich der Cursor
								//  befindet

	// Memberfunktionen
	HRESULT DisconnectFromServer (void);

	STDMETHOD (MarkerVisibility) (IObjektGeometrie* pIOG, bool bVisible = true);
	void MarkerInDBCoords (Point Pt);
	STDMETHOD (MarkerTracing) (void);
	STDMETHOD (MarkerUpToDate) (long lONr, bool bVisible = true);
	bool IsPaint (void) { return m_bIsPaint; }
	bool GrabToClosedLine (IObjektGeometrie* pIOG, KoOrd lStartPktX, KoOrd lStartPktY,
						   KoOrd lEndPktX, KoOrd lEndPktY);
	bool KonturIndex (KoOrd x, KoOrd y, IObjektGeometrie* pIOG, long lEpsilon, short& iKInd);
	HRESULT GetBelowObjects (IEnumObjektGeometrie** ppBelowObjs);
	bool IsAlreadyContact (IObjektGeometrie* pIOG, int iKInd1, int iKInd2);

public:
	CTopicalObjects (void);
	~CTopicalObjects (void) {};

	DECLARE_REGISTRY_RESOURCEID(IDR_TOPICALOBJECTS)

	BEGIN_COM_MAP(CTopicalObjects)
		COM_INTERFACE_ENTRY(ITRiASNotificationSink)
		COM_INTERFACE_ENTRY(ITopicalObjects)
	END_COM_MAP()


// ITopicalObjects
	STDMETHOD (SetXtensionSite)(IUnknown *pISite);
	STDMETHOD (InitWithSelectedObjects) (void);
	STDMETHOD (InitWithExternalObjects) (IEnumObjectsByNumber* pIEnum);
	STDMETHOD (AddTopicalObjectGeometry) (IUnknown* pIOG);
	STDMETHOD (GetEnumTopicalObjects)(IEnumObjectsByNumber** ppIEnum);
	STDMETHOD (GetEnumTopicalObjectsGeometry)(BOOL bAll, IEnumObjektGeometrie** ppIEnum);
	STDMETHOD (IsTopicalObject) (long lONr, BOOL* pbContain);
	STDMETHOD (IsTopicalObjectGeometry) (IUnknown* pIOG, BOOL* pbContain);
	STDMETHOD (DeleteTopicalObject) (long lONr);
	STDMETHOD (DeleteTopicalObjectGeometry) (IUnknown* pIOG);
	STDMETHOD (DeleteTopicalObjects) (BOOL bAll);
	STDMETHOD (GetTopicalObjectsRectangle) (BOOL bAll, LONG* plXmin, LONG* plXmax,
											LONG* plYmin, LONG* plYmax);
	STDMETHOD (GetCount) (long* plCnt);
	STDMETHOD (GetObjTypes) (int* piAllOT);
	STDMETHOD (GetMarkerSizeBS) (int* piMS);
	STDMETHOD (GetMarkerSizeDB) (long* plMBX, long* plMBY)
								 { *plMBX = m_lMBX; *plMBY = m_lMBY; return S_OK; }
	STDMETHOD (GetEpsilon) (long* plEps) { *plEps = m_lEpsilon; return S_OK; }
	STDMETHOD (SetMarkVis) (BOOL bMarkVis) { m_bMarkVis = bMarkVis; return S_OK; }
	STDMETHOD (VerticesIndicate) (void);
	STDMETHOD (VerticesUnIndicate) (void);
	STDMETHOD (CursorAtTopicalObjects) (CursPos* pCP, BOOL* pbSpezCP, long* plGrabX,
										long* plGrabY, IEnumObjektGeometrie** ppBelowObjs);
	STDMETHOD (CursorInSomeTopObjects) (IEnumObjektGeometrie* pIObj, BOOL bInBorder,
										CursPos* pCP);
	STDMETHOD (CursorInMarkerSomeTopObjects) (IEnumObjektGeometrie* pIObj, CursPos* pCP);
	STDMETHOD (CursorForAreaPartition) (IUnknown* pIOG, CursPos* pCP, long* plGrabX,
										long* plGrabY);
	STDMETHOD (CursorForIslandAdd) (IEnumObjektGeometrie* pIObj, BOOL bInBorder, CursPos* pCP);
	STDMETHOD (NewVertexWithGrab) (POINT* pMPT, IDragObject* pDO, long* plGrabPktX,
								   long* plGrabPktY, IEnumObjektGeometrie** ppBelowObjs);
	STDMETHOD (IsGrabAllowable) (long lStartPktX, long lStartPktY, long lEndPktX,
								 long lEndPktY, IEnumObjektGeometrie* pStBelowObjs,
								 IEnumObjektGeometrie* pAbBelowObjs, long lEpsilon);
	STDMETHOD (IsPaint) (BOOL* pbIsPaint) { *pbIsPaint = m_bIsPaint; return S_OK; }


// ITRiASNotificationSink
	STDMETHOD(ServerEvent) (SERVEREVT se);
	STDMETHOD(ProjectEvent) (long hPr, PROJECTEVT pe, VARIANT vProj);
	STDMETHOD(GeoViewEvent) (long hPr, GEOVIEWEVT ve, VARIANT vData);
	STDMETHOD(GeoClassEvent) (long hPr, GEOCLASSEVT ce, long ulIdent);
	STDMETHOD(GeoObjectEvent) (long hPr, GEOOBJECTEVT oe, long lONr);
	STDMETHOD(GeoFeatureEvent) (long hPr, GEOFEATUREEVT fe, long ulMCode);
	STDMETHOD(GeoRelationEvent) (long hPr, GEORELATIONEVT re, long ulRCode);
	STDMETHOD(ObjectWindowEvent) (OBJWNDEVT oe, long hORWnd);
};

#endif //__TOPICALOBJECTS_H_
