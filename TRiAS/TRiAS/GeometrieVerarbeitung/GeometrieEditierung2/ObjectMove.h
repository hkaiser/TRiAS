// Deklarationen: Interfaces für Erweiterung "GeometrieEditierung"
// Drag and Drop Source/Target für GeometrieObjekte
// File: ObjectMove.h

#ifndef _OBJECTMOVE_H
#define _OBJECTMOVE_H


#include <TRiASHelper.h>	// tagPIFLAGS in progstat.h, IProgressIndicator2
#include "progstat.h"		// BaseProgressStatus in ProgressProxy.h
#include "ProgressProxy.h"	// CProxyIProgressIndicator2

#include "SmartInterfaces.h"



///////////////////////////////////////////////////////////////////////////////////////////////
// Klasse für das Verschieben und Kopieren von Geometrie- und TextObjekten
// IEditOperation ist das Interface, das alle EditierOperationen für die GeoEdit-Erweiterung
// bereitstellen, d.h. das Interface, über das die GeoEdit-Erweiterung die EditierOperationen
// rufen kann (Gegen-Interface zu IEditExtensionSite)
class CObjectMove : public IEditOperation,
    				public ITRiASNotificationSink,
					public ITRiASSysNotificationSink,
					public ITRiASDropTarget,
#if defined(__ATL_20_USED__)
					public CProxyIProgressIndicator2<CObjectMove>,
					public IConnectionPointContainerImpl<CObjectMove>,
#else
					public CComConnectionPointContainerImpl,
#endif // defined(__ATL_20_USED__)
					public CComObjectRoot,
					public CComCoClass<CObjectMove, &CLSID_ObjectMove>
{
private:
	WTriasXtensionSite m_Site;		// TRiAS-Kontext
    DWORD m_dwCookieN;				// Nummer des ConnectionPoint für ITRiASNotificationSink
    DWORD m_dwCookieSN;				// Nummer des ConnectionPoint für ITRiASSysNotificationSink
	DWORD m_dwCookiePI;				// Nummer des ConnectionPoint für ProgressIndicators2
	pWindow m_pVWnd;				// TRiAS-ViewFenster
#if defined(__ATL_20_USED__)
	typedef CProxyIProgressIndicator2<CObjectMove> CPIProxy;
	CPIProxy *GetPIProxy() { return this; }
#else
	CProxyIProgressIndicator2 m_PPI;
	typedef CProxyIProgressIndicator2 CPIProxy;
	CPIProxy *GetPIProxy() { return &m_PPI; }
#endif // !defined(__ATL_20_USED__)

	bool m_LeftButtonSem;			// Synchronisation für die linke Maustaste
	LPARAM m_lParamOld;				// letzte Mausposition

	WEditExtensionSite m_wEdExSite;	// Interface von CGeoEditExtension für EditierOperationen
	WTopicalObjects m_wTopObjs;		// Interface der Klasse CTopicalObjects
//	WEnumObjectsByNumber m_wAllTObjs;// die ausgewählten Objekte
	WEnumObjektGeometrie m_wAllTObjs;// die ausgewählten Objekte

	Point m_StartPt;				// Startpunkt (in BS-Koordinaten) für Drag-and-Drop
	bool m_bIsDropSource;			// Unterscheidung, ob bei DragDrop aus Hauptfenster (true)
									// oder woanders (z.B. Recherchefenster oder Legende) heraus
									// gezogen wurde
	int m_iVerz;					// Verzögerung in Pixel bei DragDropStart
	int m_iAnzVO;					// Anzahl der verschobenen Objekte
	long* m_plObjNrVO;				// Objektnummern der verschobenen Objekte
	long* m_plNeuObjNr;				// Objektnummern der neuen Objekte
	POINTL m_ptlOld;				// Punkt (in Fensteroordinaten), bei dem Objektumriß zu
									// löschen ist
	Point* m_pPolyPoly;				// Vektor mit Stützpunktkoordinaten in BS-Format und
	int* m_piPolyCounts;			//  einzelne Stützpunktanzahl

	// Memberfunktionen
	HRESULT DisconnectFromServer (void);

	HRESULT MouseMove (LPARAM lParam);
	void LeftMouseDown (LPARAM lParam);
	void LeftMouseUp (void);

	HRESULT DoDragDropAction (DWORD dwFlags);
	HRESULT SetObjNummern (IEnum<LONG>* pEnum);
	HRESULT DeleteTopObjects (IEnum<LONG>* pEnum);
	void RefreshTopObjects (void);
	bool IsDropSource (void);
	HRESULT GetObjNummern (IDataObject* pIDataSource);
	bool UmrissVektor (void);
	bool GiveFeedBack (Point* pPolyPoly, int* piPolyCounts, long lAnz, POINTL ptlZiel);
	bool BuildMovedObjects (POINT ptZiel, bool bCopy);
	bool MultiRectangle (long* plObjNr, long lObjAnz, Rectangle& Rec);
//	bool PointSymbolSize (long lONr, int& iPixX, int& iPixY);
	bool MoveTextObject (bool bCopy, long lAltObjNr, KoOrd XDiff, KoOrd YDiff,
						 long& lNeuObjNr);
	bool RestoreTextDependence (bool bCopy);
	bool AddToORWindow (long lAltObjNr, long lNeuObjNr);

	HRESULT SetEnumLONGData (IEnum<LONG>* pEnum, IDataObject* pDataObj);
	HRESULT CreateStreamOnHGlobalFromIUnknown (IUnknown* pIUnk, IStream** ppIStream);
	HRESULT GetEnumLONGData (IDataObject *pIDataObj, IEnum<LONG>** ppIEnumOut = NULL);
	HRESULT CreateEnumLONGFromStream (IStream* pIStream, IEnum<LONG>** ppEnumOut);

	HRESULT InitProgressIndicator (IProgressIndicator2* pPI, ResID uiTitel, ResID uiAdjust,
								   ulong ulMaxPos, ulong ulMinPos = 1);
	HRESULT RegisterPI (IProgressIndicator2* pPI);
	HRESULT UnRegisterPI (void);

public:
	// Konstruktor, Destruktor
	CObjectMove (void);
	~CObjectMove (void);

	DECLARE_REGISTRY_RESOURCEID(IDR_OBJECTMOVE)

	BEGIN_COM_MAP(CObjectMove)
    	COM_INTERFACE_ENTRY(ITRiASNotificationSink)
		COM_INTERFACE_ENTRY(ITRiASSysNotificationSink)
		COM_INTERFACE_ENTRY(ITRiASDropTarget)
#if defined(__ATL_20_USED__)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
#else
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
#endif // !defined(__ATL_20_USED__)
		COM_INTERFACE_ENTRY(IEditOperation)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CObjectMove)	// Makro
#if defined(__ATL_20_USED__)
		CONNECTION_POINT_ENTRY(IID_IProgressIndicator2)
#else
		CONNECTION_POINT_ENTRY(m_PPI)
#endif // !defined(__ATL_20_USED__)
	END_CONNECTION_POINT_MAP()

	// IEditOperation
	STDMETHOD (SetEditExtensionSite) (IEditExtensionSite* pIEdExSite);
	STDMETHOD (InformRestrictLinesState) (IRestrictLine*, IRestrictLine*);
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

	// ITRiASDropTarget-Methoden (unterscheiden sich in den Parametern von den
	// IDropTarget-Methoden dadurch, daß die ersten beiden Parameter hinzugekommen sind)
	STDMETHOD (DragEnter) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, IDataObject* pIDataSource,
						   DWORD grfKeyState, POINTL ptl, DWORD* pdwEffekt);
	STDMETHOD (DragOver) (THIS_ DRAGDROPTYPE rgType, HWND hWnd,	DWORD grfKeyState, POINTL ptl,
						  DWORD* pdwEffekt);
	STDMETHOD (DragLeave) (THIS_ DRAGDROPTYPE rgType, HWND hWnd);
	STDMETHOD (Drop) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, IDataObject* pIDataSource,
					  DWORD grfKeyState, POINTL ptl, DWORD* pdwEffekt);

	// Memberfunktionen
	bool FQueryDrop (void);
};



///////////////////////////////////////////////////////////////////////////////////////////////
// DropSourceObject
class CEditDropSource : public IDropSource
{
private:
	DWORD m_dwRefCnt;
	CObjectMove* m_pObjMove;
	DWORD m_dwFlags;			// DragModi (MouseBttns)

protected:
	CEditDropSource (void);

public:
	// nur dynamisch über "CreateInstance" zu generieren
	static CEditDropSource* CreateInstance (CObjectMove* pObjMove);
	bool FInit (CObjectMove* pObjMove, DWORD dwFlags = MK_LBUTTON);

		~CEditDropSource (void);

	// IUnknown-Methoden
	STDMETHOD_ (ULONG, AddRef) (THIS);
	STDMETHOD_ (ULONG, Release) (THIS);
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);

	// IDropSource-Methoden
	STDMETHOD(QueryContinueDrag) (THIS_ BOOL fEscapePressed, DWORD grfKeyState);
	STDMETHOD(GiveFeedback) (THIS_ DWORD dwEffect);
};

#endif // _OBJECTMOVE_H
