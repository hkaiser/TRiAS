// Deklaration: Abschnitt eines schon existierenden Objektes (Linien oder Flächenkontur) durch
//				einen Abschnitt eines anderen Objektes ersetzen

// File: CommonBorder.h
// W. Mörtl

#ifndef __COMMONBORDER_H_
#define __COMMONBORDER_H_


#include "SmartInterfaces.h"


///////////////////////////////////////////////////////////////////////////////////////////////
// Klasse für das Ersetzten eines Linienabschnittes
// IModifyOperation ist das Interface, das alle ModifyOperation's für die CObjectModify-Klasse
// bereitstellen, d.h. das Interface, über das die CObjectModify-Klasse die ModifyOperation's
// rufen kann (Gegen-Interface zu IModifyClassSite)
class ATL_NO_VTABLE CCommonBorder : public CComObjectRootEx<CComSingleThreadModel>,
									public ITRiASNotificationSink,
									public ITRiASSysNotificationSink,
									public CComCoClass<CCommonBorder, &CLSID_CommonBorder>,
									public IModifyOperation
{
public:
    // Konstruktor, Destruktor
    CCommonBorder (void);
    ~CCommonBorder (void);

	DECLARE_REGISTRY_RESOURCEID(IDR_COMMONBORDER)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CCommonBorder)
   		COM_INTERFACE_ENTRY(ITRiASNotificationSink)
		COM_INTERFACE_ENTRY(ITRiASSysNotificationSink)
		COM_INTERFACE_ENTRY(IModifyOperation)
	END_COM_MAP()

public:
	// IModifyOperation
	STDMETHOD(SetModifyClassSite)(IEditExtensionSite* pIEdExSite, IModifyClassSite*);
	STDMETHOD (LineElongation) (IEnumObjektGeometrie*, long, long);
	STDMETHOD (AreaPartition) (long, POINT);
	STDMETHOD (IslandAddition) (IEnumObjektGeometrie*);
	STDMETHOD (Rectangularity) (long, int, long, double, double, double, IEnumObjectsByNumber**);
	STDMETHOD (MakeCommonBorder) (IEnumObjektGeometrie* pModObjs, long lRMX, long lRMY);

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

private:
	pWindow m_pVWnd;					// TRiAS-ViewFenster

	WEditExtensionSite m_wEdExSite;		// Interface von CGeoEditExtension für EditierOperationen
	WTopicalObjects m_wTopObjs;			// Interface der Klasse CTopicalObjects
    WEnumObjektGeometrie m_wModObjs;	// die zu modifizierenden Objekte

	long m_lRMX;						// Koordinaten des
	long m_lRMY;						//  Punktes, bei dem das Menü gerufen wurde
	short m_iSrcOT;						// Objekttyp des Quell-Objektes
	KoOrd* m_plSrcX;					// Stützpunkte des Quell-Objektes
	KoOrd* m_plSrcY;
	bool m_bIsSrcClosed;				// Quell-Objekt ist eine Fläche bzw. geschlossene Kante (true)
	short m_iSrcCInd;					// Index der Quell-Kontur
	long m_lSrcAnfInd;					// 1. Index bzw.
	long m_lSrcEndInd;					//  letzter Index der Quell-Kante bzw. -Kontur
	EPunkt m_EndPkt1;					// die beiden Endpunkte des
	EPunkt m_EndPkt2;					//  zu übernehmenden Linienabschnittes
	long m_lSrcInd1;					// Indizes (ohne Richtung) der beiden
	long m_lSrcInd2;					//  Endpunkte bezgl. des Quell-Objektes
	long m_lSrcFromInd;					// Anfangs- und Endindex (gerichtet) des zu übernehmenden
	long m_lSrcToInd;					//  Linienabschnittes bezgl. des Quell-Objektes

	bool m_bFirstModObj;				// es wird das 1. zu modifizierende Objekt bearbeitet (true)
	long m_lModNextInd;					// Indizes des 1. zu modifizierenden Objektes
	short m_iModCInd;
	long m_lModInd1;
	long m_lModInd2;
	long m_lModAnfInd;
	long m_lModEndInd;
	
	long m_lCursEps;					// Epsilon für Cursor-Umschaltung
	int m_iMarkGr;						// Größe der Stützpunktmarkierungen
	Color m_colFill;					// aktuelle Füllfarbe der Stützpunktmarkierungen
	Color m_colInkFill;					// Sonderfüllfarbe der Stützpunktmarkierungen
	Color m_colBound;					// Sonderrandfarbe der Stützpunktmarkierungen
	int m_iBoundWidth;					// Sonderrandbreite der Stützpunktmarkierungen	
	KoOrd m_lXMin, m_lXMax, m_lYMin, m_lYMax;	// Bereich, der neu zu zeichnen ist


	// Memberfunktionen
	HRESULT KeyUp (WPARAM wParam);
	HRESULT WMChar (WPARAM wParam);

	HRESULT DetermineSourceObject (IObjektGeometrie** ppSrcObj);
	HRESULT DetermineAModifyObject (IObjektGeometrie** ppModObj);
	HRESULT DetermineBorderEndPoints (IObjektGeometrie* pModObj, IObjektGeometrie* pSrcObj);
	HRESULT GetEndPoint1 (long lStartInd, KoOrd* plModX, KoOrd* plModY, bool bIsModClosed);
	HRESULT GetEndPoint2 (long lStartInd, KoOrd* plModX, KoOrd* plModY, bool bIsModClosed);
	void FindShortestSection (void);
	void InkMarker (void);
	HRESULT ReplaceLinePart (void);
	HRESULT DetermineIndices (IObjektGeometrie* pModObj, KoOrd* plModX, KoOrd* plModY,
							 short iModOT, long& lModAnfInd, long& lModEndInd, long& lModFromInd,
							 long& lModToInd, long& lModNextInd, short& iModCInd);
	bool IsSameContour (long lModAnfInd, long lModEndInd, long lInd1, long lInd2,
						long lModNextInd);
	HRESULT SubModifyPoints (IObjektGeometrie* pModObj, KoOrd* plModX, KoOrd* plModY,
							 long lModAnfInd, long lModEndInd, long lModFromInd, long lModToInd,
							 short iModCInd, long& lToSubCnt);
	HRESULT AddModifyPoints (IObjektGeometrie* pModObj, long lModToInd, long lToSubCnt,
							 short iModCInd);
	HRESULT InsertPoint (IObjektGeometrie* pModObj, long l, long lModToInd, int iModCInd);
	HRESULT StoreCommonBorder (IObjektGeometrie* pModObj);
	void BuildScreenRectangle1 (KoOrd* plModX, KoOrd* plModY, long lModFromInd, long lModToInd);
	void BuildScreenRectangle2 (KoOrd lX, KoOrd lY);
	void DrawScreenRectangle (void);
};

#endif //__COMMONBORDER_H_
