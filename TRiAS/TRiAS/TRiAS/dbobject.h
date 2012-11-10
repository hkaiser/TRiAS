///////////////////////////////////////////////////////////////////////////
// <c DatenBasisObjekt> repräsentiert ein TRiAS-Project im Framework
// dbobject.h

#if !defined(_DBOBJECT_H__A37D8269_4A3F_11d1_96DC_00A024D6F582__INCLUDED_)
#define _DBOBJECT_H__A37D8269_4A3F_11d1_96DC_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#import "tlb/TRiASCs.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids
#import "tlb/TDBGeo.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids \
	exclude("IPersist", "IPersistMemory")

#include "GeoDBArray.h"
#include "minitpbd.hxx"

typedef struct tagOBJSTATISTIK OBJSTATISTIK;
typedef struct tagOBJGEOMETRIE OBJGEOMETRIE;
typedef struct tagENUMRECHTEXTMERKMAL ENUMRECHTEXTMERKMAL;
typedef struct tagENUMRECHGEOMETRIE ENUMRECHGEOMETRIE;
typedef struct tagVISINFO VISINFO;

class ExtShapeObject;
class ExtShapeObjectDCreator;
class CIdentifikator;
class CIdRefLock;
class VisInfo;
class CViewsTree;
class IrisWind;

///////////////////////////////////////////////////////////////////////////////
// SmartInterface's
DefineSmartInterface(TRiASProject);				// WTRiASProject
DefineSmartInterface(TRiASObjectHandleMap);		// WTRiASObjectHandleMap
DefineSmartInterface(TRiASObject);				// WTRiASObject
DefineSmartInterface(TRiASObjects);				// WTRiASObjects
DefineSmartInterface(TRiASFeature);				// WTRiASFeature
DefineSmartInterface(TRiASCSStorageService);	// WTRiASCSStorageService

///////////////////////////////////////////////////////////////////////////////
// Klasse um DB zu zeichnen 
class DatenBasisObjekt : 
	public ExtShapeObject,
	public Transformation,
	public ISupportErrorInfo,
	public IDispatchImpl<ITRiASConnectionEvents, &IID_ITRiASConnectionEvents, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public IDispatchImpl<ITRiASViewEvents, &IID_ITRiASViewEvents, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>,
	public IDispatchImpl<ICoordTransformEvents, &IID_ICoordTransformEvents, &LIBID_CoordTransLib,
		TYPELIB_CTF_VERSION_MAJOR, TYPELIB_CTF_VERSION_MINOR>,
	public CComObjectRootEx<CComSingleThreadModel>
{
private:
	PaintFlag _toPaint;             // darf gezeichnet werden
	ObjContainer _DBOCont;          // Container des zu zeichnenden Objekts
									// (aktueller Bildausschnitt)
#if defined(_FORCE_LEGACY_CODE)
	PBD_DB m_pbdDB;					// zugehörige PBD
#endif // _FORCE_LEGACY_CODE
	
// BitmapStreifen, die die aktuellen Punktsymbole enthalten
	class CBitmapBar *m_pBmp15sw;	// Punktsymbole
	class CBitmapBar *m_pBmp23sw;
	class CBitmapBar *m_pBmp32sw;
	bool m_fNewPnts;
	short m_iBmpCnt;				// Anzahl der Punktsymbole
	LONG m_lObjCnt;					// Objektanzahl in GeoDB
	LONG m_lActScale;
	int m_iActLayer;				// derzeit gezeichneter Layer eines Identifikators

	class CMapPunktID *m_pPunktIDs;			// PunktID <--> iIndex
	class CMapIdentToClass *m_pClsIdents;	// Idents <--> ObjektklassenSchlüssel

#if defined(_USE_FLICKERFREE_DRAWING)
	DWORD m_dwTicks;				// Zeit seit dem letzten AppExec beim Zeichnen
#endif // defined(_USE_FLICKERFREE_DRAWING)
					
public:
	CBitmapBar *GetBmp (unsigned int uiPntID, Dimension &dim) const;
	bool LoadBitmapBars (bool fLookAtHeader = true);

inline	bool FNewPnts (void) { return m_fNewPnts; }
inline	short FCntPnts (void) { return m_iBmpCnt; }
inline	CoOrd FHeight (unsigned int uiIndex) { return m_pBmp32sw -> FHeight (uiIndex); }
inline	CoOrd FWidth (unsigned int uiIndex) { return m_pBmp32sw -> FWidth (uiIndex); }
inline	int FGetIndex (WORD wPunktID) { return m_pPunktIDs -> FGetIndex (wPunktID); }
inline	WORD FGetPunktID (int iIndex) { return m_pPunktIDs -> FGetPunktID (iIndex); }
inline	CIndexMap &GetMap (void) const { return m_pPunktIDs -> GetMap(); }

inline int GetActLayer() { return m_iActLayer; }
inline void SetActLayer (int iActLayer) { m_iActLayer = iActLayer; }

protected:
	void DrawEx (DWORD);		// ganze DB Zeichnen
	ErrCode NextDraw (DWORD);	// weitere Male zeichnen
	ErrCode DrawObjectsIteratingIdent (CIdRef *pP, bool fGenerateLegendOnly, bool &rfForceDrawCallUp);
	ErrCode DrawObjectsIteratingObjects (CIdRef *pP, bool fGenerateLegendOnly, bool &rfForceDrawCallUp);
	
#if defined(_USE_FLICKERFREE_DRAWING)
	bool DoIdleLoop(bool fForceDrawCallUp);
#endif // defined(_USE_FLICKERFREE_DRAWING)

	CGeoDBArray *m_pGeoDBs;	// Liste der DatenBanken

	ObjektListe *_Shapes;	// Liste aller Objekte
	CIdTree *_Idents;		// Liste aller zu zeichnenden ViewItems
	CViewsTree *m_pViews;	// Baum mit allen Sichten

	Dimension _DotsPerMM;	// DotsPerMM des aktuellen Gerätes
	CoordTrans *_pCT;		// KoordinatenTransformation

// Menu, welches Ansichten enthält
	pMenu _SightMenu;		// Menu der Ansichten

	int _iDrawSem;			// diese DB wird derzeit gezeichnet
	POINT *m_ptsToDraw;		// 'globaler' TransformationsBuffer
	CSCOORD *m_pCoords;		// 'globaler' ZwischenPuffer für Koordinaten
	size_t m_lCntPts;		// Größe des TransformationsBuffers

#if defined(_USE_LEGACY_CODE)
	short m_IdentBase;		// Zahlensystem des Idents
	short m_MCodeBase;		// Zahlensystem der MCodes
#endif // _USE_LEGACY_CODE

	bool m_fPosTextAtBaseLine;	// Texte an Basislinie orientieren
	bool m_fCompatibility16;	// OKS ist identisch mit Ident

	bool m_fToClose;		// Projekt wird derzeit geschlossen
	bool m_fIsFile;			// repräsentiert Datei
	bool m_fIsOpening;		// wird derzeit geöffnet
	bool m_fIsDeletingView;	// eine Ansicht wird derzeit gelöscht
	bool m_fIsActiveProject;	// dieses Projekt ist z.Zt. das aktive
	bool m_fSavingDocument;	// true während speichern
	bool m_fLastDirty;		// Dirtyzustand bei der vorherigen Abfrage
	bool m_fLimitSearches;	// Recherchen auf aktuellen Bildausschnitt begrenzen
	bool m_fIgnoreSearchResultOptions;	// voreingestellte Recherchierbarkeit ignorieren

	Color m_cBkColor;		// HintergrundFarbe für dieses Projekt

	long m_lScaleMCode[VT_Text+1];	// MCodes für IdentScale
	long m_lObjGuidMCode;		// MCode für ObjektGuid (bis VERSION0500000B)

	IrisWind *m_pViewWnd;		// Zugehöriges ViewFenster
	WTRiASProject m_Prj;		// zugehöriges TRiASProject
	WTRiASObjectHandleMap m_ObjMap;		// HandleMap für Objekte
	WTRiASObjectHandleMap m_ObjsMap;	// HandleMap für Idents 
	WTRiASObjectHandleMap m_FeatMap;	// HandleMap für Objekteigenschaften 
	WTRiASCSStorageService m_Service;	// StorageService

	os_string m_strLastName;	// zuletzt angezeigte Objekteigenschaft

public:
// Funktion für den Zugriff auf die ObjectMap von TRiASDB
	HRESULT GetObjectFromMap (long lTarget, WTRiASObject &rif)
	{
	WUnknown Unk;
	HRESULT hr = m_ObjMap -> GetObject (lTarget, Unk.ppi());

		if (SUCCEEDED(hr))
			rif = Unk;
		return hr;
	}

// Funktion für den Zugriff auf die ObjectsMap von TRiASDB
	HRESULT GetObjectsFromMap (long lTarget, WTRiASObjects &rif)
	{
	WUnknown Unk;
	HRESULT hr = m_ObjsMap -> GetObject (lTarget, Unk.ppi());

		if (SUCCEEDED(hr))
			rif = Unk;
		return hr;
	}

// Funktion für den Zugriff auf die FeatureMap von TRiASDB
	HRESULT GetFeatureFromMap (long lTarget, WTRiASFeature &rif)
	{
	WUnknown Unk;
	HRESULT hr = m_FeatMap -> GetObject (lTarget, Unk.ppi());

		if (SUCCEEDED(hr)) 
			rif = Unk;
		return hr;
	}

	HPROJECT GetIdentParentHandle (INT_PTR lIdent, BOOL fMayFail = FALSE);
	HPROJECT GetIdentDBHandle (INT_PTR lIdent, HPROJECT hPr);
	HPROJECT GetObjectDBHandle (INT_PTR lONr, HPROJECT hPr = HACTCONNECTION);
	HPROJECT GetFeatureDBHandle (INT_PTR lMCode, HPROJECT hPr = HACTCONNECTION);
	HPROJECT GetObjectProject (ITRiASObject *pIObj);

// Zugriff auf StorageService
	HRESULT StorageToGeometry (VARIANT Blob, GEOMETRYTYPE *prgType, IDispatch **ppIGeometry)
	{
		_ASSERTE(m_Service.IsValid());
		return m_Service -> StorageToGeometry (Blob, prgType, ppIGeometry);
	}
	HRESULT GeometryToStorage (GEOMETRYTYPE rgType, IDispatch *pIGeometry, VARIANT *pBlob)
	{
		_ASSERTE(m_Service.IsValid());
		return m_Service -> GeometryToStorage (rgType, pIGeometry, pBlob);
	}
	HRESULT RetrieveType (IDispatch *pIGeometry, GEOMETRYTYPE *prgType)
	{
		_ASSERTE(m_Service.IsValid());
		return m_Service -> RetrieveType (pIGeometry, prgType);
	}

// öffentliche Memberwerte
	ObjContainer ExposedArea;       // ungültiger Bildschirmbereich

// Konstruktor
		DatenBasisObjekt (void);

public:
///////////////////////////////////////////////////////////////////////////////
// COM-Spezifika
	BEGIN_COM_MAP(DatenBasisObjekt)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(ITRiASConnectionEvents)
		COM_INTERFACE_ENTRY(ITRiASViewEvents)
		COM_INTERFACE_ENTRY(ICoordTransformEvents)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASConnectionEvents)
	END_COM_MAP()

	HRESULT FinalConstruct();
	void FinalRelease (void);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ICoordTransformEvents
	STDMETHOD(CoordParamsToChange)(IDispatch *pICoordSys, VARIANT_BOOL *pVal);
	STDMETHOD(ChangingCoordParams)(IDispatch *pICoordSys);
	STDMETHOD(ChangedCoordParams)(IDispatch *pICoordSys);

// ITRiASConnectionEvents
	STDMETHOD(CreatingConnection)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToCreate)(/*[in]*/ BSTR Name);
	STDMETHOD(ConnectionCreated)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(OpeningConnection)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToOpen)(/*[in]*/ BSTR Name);
	STDMETHOD(ConnectionOpened)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ClosingConnection)(/*[in]*/ IDispatch *pIConn, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToClose)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ConnectionClosed)(/*[in]*/ BSTR Name);
	STDMETHOD(DeletingConnection)(/*[in]*/ IDispatch *pIConn, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToDelete)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ConnectionDeleted)(/*[in]*/ BSTR Name);
	STDMETHOD(RenamingConnection)(/*[in]*/ BSTR OldName, /*[in]*/ BSTR NewName, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectionToRename)(/*[in]*/ BSTR OldName, /*[in]*/ BSTR NewName);
	STDMETHOD(ConnectionRenamed)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ChangingConnectedDatasource)(/*[in]*/ IDispatch *pIConn, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ConnectedDatasourceToChange)(/*[in]*/ IDispatch *pIConn);
	STDMETHOD(ConnectedDatasourceChanged)(/*[in]*/ IDispatch *pIConn);

// ITRiASViewEvents
	STDMETHOD(CreatingView)(/*[in]*/ BSTR Name, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ViewToCreate)(/*[in]*/ BSTR Name);
	STDMETHOD(ViewCreated)(/*[in]*/ IDispatch *pIView);
	STDMETHOD(ChangingView)(/*[in]*/ BSTR OldName, /*[in]*/ BSTR NewName, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ViewToChange)(/*[in]*/ BSTR Name, /*[in]*/ BSTR NewName);
	STDMETHOD(ViewChanged)(/*[in]*/ IDispatch *pIView);
	STDMETHOD(DeletingView)(/*[in]*/ IDispatch *pIView, /*[retval][out]*/ VARIANT_BOOL *pVal);
	STDMETHOD(ViewToDelete)(/*[in]*/ IDispatch *pIView);
	STDMETHOD(ViewDeleted)(/*[in]*/ BSTR Name);

///////////////////////////////////////////////////////////////////////////////
// Skalierung des Fensters
	bool Scale (Window *pW, ObjContainer &rOC, Point &rPt, Rectangle *pRc = NULL);
	bool SetActiveScaling (long lZoom, Rectangle &rRc, Rectangle &rCRc, ObjContainer &rOC);

// ggf. Impressum ausgeben
	bool DrawImpressum (HDC hDC, HDC hTargetDC, Rectangle rcCanvas);

private:
	typedef list<ObjContainer> CLoadedRects;

	CLoadedRects *m_pLoadedOC;
	bool m_fLoadMode;				// beim Zeichnen Objekte laden

public:
	bool IsLoadedRect (ObjContainer &rOC);		// Verwaltung der geladenen GeoDB-Bereiche
	bool AddLoadedRect (ObjContainer &rOC);
	void ResetLoadedRects (void);

	void SetLoadMode (bool fLoadMode) { m_fLoadMode = fLoadMode ? true : false; }
	bool GetLoadMode (void) { return m_fLoadMode; }

// Memberfunktionen
	Rectangle BoundingBox (void);
	HRESULT GetGI (long lObjNr, LPCSTR pcGeomName, ExtShapeObjectDCreator &rObjCr, ExtShapeObject **ppESO, ObjContainer *pOC = NULL, INT_PTR lIdent = 0L);
	HRESULT GetGI (long lObjNr, LPCSTR pcGeomName, GeoObjekt **ppGO, ObjContainer *pOC = NULL, INT_PTR lIdent = 0L);  // Geometrie aus DB lesen
	HRESULT GenerateGeoObjekt (GeoDB &rDB, INT_PTR lONr, INT_PTR lIdent, VARIANT &rvBlob, _DGMRectangleGeometry *pCont, GeoObjekt **ppGO);
	bool RetrieveGeometrie (GeoObjekt *pGO, OBJGEOMETRIE *pGS, CoordTrans *pCT, IUnknown *pICS);
	BOOL UnloadObject (INT_PTR lONr);

	ErrCode GetGIAll (CIdRefLock &, bool fTest, DWORD, bool &rfForceDrawCallUp);
	HRESULT KOGetGI (KomplexObjekt &, ExtShapeObjectDCreator &);
	PaintFlag toPaint (void) { return _toPaint; }

	HRESULT PutGI (GeoObjekt *pGO, bool fNewOTyp = false);			// Geometrie schreiben
	INT_PTR CreateObjTemplate (INT_PTR lIdent, int iObjTyp);

	void SetExtend (Window *pW, ObjContainer &rOC, Point &rPt, Rectangle *pRc = NULL);
	ObjContainer GetExtend(void) const { return ObjContainer(_DBOCont.XMin(), _DBOCont.XMax(), _DBOCont.YMin(), _DBOCont.YMax()); }
	PaintFlag SetPaintFlag (PaintFlag);

	void EveryDelete (void);

	ObjTyp isTyp (void);
	short GetActIdentObjTypes (LONG lIdent);

// Legende rücksetzen
	bool ResetLegend (LPCSTR pcView = NULL, INT_PTR lVMCode = 0L);
	
// liefert Objektliste
	ObjektListe &Shapes (void) const { return *_Shapes; }			// liefert ObjektListe
	CIdTree &Idents (void) const { return *_Idents; }				// liefert Id's
	ErrCode FillIdents (bool fRebuild = false);						// Idents füllen
	HRESULT ForceReLoad (RELOADDATABASE rgWhat = RELOADDATABASE_All);	// irgend was neu laden
	HRESULT RemoveIdentsFromCache (HPROJECT hPr);
	ErrCode FindId (long lIdent, long *plFlexNum, short *pOTyp = NULL, long *plObjCnts = NULL);

	inline GeoDB &DB (void) { return m_pGeoDBs -> DB(); }					// liefert DB
	inline GeoDB &DB (HPROJECT hPr) { return m_pGeoDBs -> DB(hPr); }		// liefert DB
//	inline GeoDB &DB (INT_PTR lIdent) { return DB(GetIdentParentHandle(lIdent)); }
	string GetProjectName (void);									// Liefert ProjektNamen
	inline UINT GetOpenCount()					// liefert Anzahl der geöffneten Connections
		{ return m_pGeoDBs ? m_pGeoDBs -> GetOpenCount() : 0; }
	inline CGeoDBArray & GetGeoDBs() const { return *m_pGeoDBs; }	// Liste der DatenBanken

#if defined(NOPRIORITY)
// Testen, ob dieses Objekt entspr. seinem Id gezeichnet werden soll
	bool toPaint (long Ident);
#endif

// Liefert GeoObjekt zu vorgegbener ON
	GeoObjekt *GetGeoObj (INT_PTR lONr, INT_PTR lIdent = 0);
	long PutGeoObj (GeoObjekt *, short iFlags);
	bool GetObjContainer (INT_PTR lONr, ObjContainer &rOC, IUnknown *pICS = NULL);
	bool ConvertObjContainer (ObjContainer &rOC, IUnknown *pICS = NULL);

// Funktionen zu Verwaltung der Ansichten
	pMenu SightMenu (void) { return _SightMenu; }

	bool InitSightMenu (pMenu pM, bool iStandard = true);
	bool AddItemToSightMenu (Window *pWnd, pMenu pM, LPCSTR pcView, LPCSTR pcConnFilter = NULL);
	bool AddItemToSightMenu (Window *pWnd, pMenu pM, LPCSTR pcView, UINT &ruiID);
	BOOL GetViewName (LPCSTR pcView, string &rStr);

	bool DeleteView (pMenu pM, LPCSTR pcView);
	bool DeleteSightMenuItem (Window *pWnd, pMenu pM, LPCSTR pcItem);
	bool DeleteAllSightItems (Window *pWnd, pMenu pM);

	bool SetActiveSightName (LPCSTR pcView);
	bool GetActiveSightName (LPSTR cbBuffer, int iLen = -1);
	bool HasActiveSight();

	bool SetDefaultSightName (LPCSTR pcView);
	bool GetDefaultSightName (LPSTR cbBuffer, int iLen = -1);

	bool GetViewConnectFilter(LPCSTR pcView, LPSTR pConnFilter, int iLen);
	bool SetViewConnectFilter(LPCSTR pcView, LPCSTR pcConnFilter);
	BOOL __stdcall EnumConnectionsForConnFilter(long hPr, BOOL, void *pData);

	HRESULT SetObjPropToShow (LPCSTR pcView, LPCSTR pcObjProp, int iFlags);
	HRESULT GetObjPropToShow (LPCSTR pcView, LPSTR pObjProp, int iLen, int *piFlags);

	bool CheckItemAsActive (LPCSTR pcView);
	bool UnCheckItemAsActive (void);

	ErrCode WriteSightIDs (LPCSTR pcSight, long *IDs, short numIDs, 
			       short *pTypInfo, LPCSTR pcTargetSight = NULL, 
			       short = 0, long = -1L);
	bool AddNewIdent (long newId, HPALETTE hPalette, short iFlags = 0, short iVTyp = TPAll, long lTargetId = -1L);

	bool EnumSights (BOOL (*pFcn)(char *, BOOL, void *), void *);
	
	bool ProcessMenuEvent (UINT uiMenuID);
	bool ProcessMenuEvent (LPCSTR pcView, bool fForce, bool fNotify = false);

///////////////////////////////////////////////////////////////////////////////
// AnsichtsFunktionalität

// Ansichts-Container
	ErrCode SetSichtCont (ObjContainer &rOC, LPCSTR pcView = NULL);
	ErrCode GetSichtCont (ObjContainer * = NULL, LPCSTR pcView = NULL);
	ErrCode DelSichtCont (LPCSTR pcView = NULL);
	bool hasSichtCont (LPCSTR pcView = NULL)
		{ return (EC_OKAY == GetSichtCont (NULL, pcView)) ? true : false; }

	bool ZoomInToObject (INT_PTR lONr);

// BezugsMaßstab
	double GetViewBMasstab (LPCSTR pcView = NULL);
	HRESULT SetViewBMasstab (double dMSt, LPCSTR pcView = NULL);
	HRESULT DelViewBMasstab (LPCSTR pcView = NULL);

// Textobjekte anzeigen/nicht anzeigen
	HRESULT SetShowTexts (bool fShowTexts, LPCSTR pcView = NULL);
	HRESULT GetShowTexts (bool &rfShowTexts, LPCSTR pcView = NULL);

// Enumerationsroutinen für Ansichten
	HRESULT EnumViewIdents (LPCSTR pcView, ENUMLONGKEYPROC pFcn, void *pData);
	HRESULT EnumViewIdentsEx (LPCSTR pcView, ENUMLONGKEYEXPROC pFcn, void *pData, DWORD dwData);

	int CreateView (LPCSTR pcView);
	int CreateViewOpt (LPCSTR pcView);
	bool ProjectHasView (LPCSTR pcView);
	bool RenameView (LPCSTR pcView, LPCSTR pcNewName);
	bool DeleteView (LPCSTR pcView, bool fDelAttribs = true);

	HPALETTE GetViewPalette (LPCSTR pcView, long *ppIDs = NULL, short iNumIDs = 0, short *pTypes = NULL);

#if defined(_FORCE_LEGACY_CODE)
	ErrCode SetViewAttribs (LPCSTR pcView, long lMerkmale, long lRelationen);
	ErrCode GetViewAttribs (LPCSTR pcView, long *plMerkmale, long *plRelationen);
#endif // _FORCE_LEGACY_CODE
	HRESULT SetViewAttribs (LPCSTR pcViewSrc, LPCSTR pcViewDest, ITRiASProperties *pIProps, ITRiASRelations *pIRels);
	HRESULT GetViewAttribs (LPCSTR pcView, ITRiASProperties **ppIProps, ITRiASRelations **ppIRels);
	HRESULT MoveViewAttribs (LPCSTR pcViewDest, LPCSTR pcViewSrc);

// Objektmengen in Ansichten verwalten
	bool AddIdentToView (LPCSTR pcView, long lIdent, int iOTypes);
	bool RemoveIdentFromView (LPCSTR pcView, long lIdent, int iOTypes, int iDefTypes = 0);
	bool ViewHasIdent (LPCSTR pcView, long lIdent, int iOTypes);
	bool GetViewIdents (LPCSTR pcView, long **ppIDs, short &numIDs, short **ppTypes = NULL);

	bool RetrieveVisInfo (LPCSTR pcView, long lIdent, short iVTyp, VISINFO &rVI, bool *pfDef = NULL);
	bool RetrieveVisInfo (LPCSTR pcView, long lIdent, short iVTyp, VisInfo **ppVI = NULL, bool *pfDef = NULL);
	ErrCode SaveVI (VisInfo *pVI, LPCSTR pcView, long lIdent, VisType iVTyp, int fBits = -1, bool fTemp = false);
	ErrCode SaveVI (LPCSTR pcView, CIdentifikator &rId);

	bool GetCompleteVisInfo (LPCSTR pcView, long lIdent, VisInfo **ppVI, int iOTypes, HPALETTE hPal = NULL, int *piGot = NULL, int *piDef = NULL);
	bool SetCompleteVisInfo (LPCSTR pcView, long lIdent, VisInfo **ppVI, int iOTypes);
	bool GetCompleteDefaultVisInfo (long lIdent, VisInfo **ppVI, int iOTypes, HPALETTE hPal = NULL, int *piGot = NULL, int *piDef = NULL);
	bool SetCompleteDefaultVisInfo (long lIdent, VisInfo **ppVI, int iOTypes);

// Objekttypen einer Ansicht abfragen
	HRESULT GetDefaultObjectTypes (INT_PTR lIdent, OBJECTTYPE *prgType);
	HRESULT GetObjectTypes (LPCSTR pcView, INT_PTR lIdent, OBJECTTYPE *prgType);

	bool _SightFlag;

	bool GetLimitSearches() { return m_fLimitSearches; }
	void SetLimitSearches (bool fFlag) { m_fLimitSearches = fFlag; }

	bool GetIgnoreSearchOptions() { return m_fIgnoreSearchResultOptions; }
	void SetIgnoreSearchOptions(bool fFlag) { m_fIgnoreSearchResultOptions = fFlag; }

///////////////////////////////////////////////////////////////////////////////
// Relationen
	ErrCode ModifyRelation (INT_PTR lPONr, INT_PTR lSONr, INT_PTR lRCode, int iRTyp, bool fUndo);
	ErrCode DeleteRelation (INT_PTR lPONr, INT_PTR lSONr, INT_PTR lRCode, int iRTyp, bool fUndo);
	BOOL EnumRelations (ENUMNOKEYLONGPROC pFcn, void *pData);
	BOOL EnumRelatedObjects (ENUMRELATIONOBJS *pERO);

///////////////////////////////////////////////////////////////////////////////
//
	HDC Handle (Service s) { return DrawObject :: Handle (s); }
	Dimension &DotsPerMM (void) { return _DotsPerMM; }
	HRGN CreatePaintRegion (HDC hDC, Rectangle &rcEA, long lONr);
	HRGN CreateObjectRegion (HDC hDC, GeoObjekt *pGO, CoOrd dY = 0, Rectangle *pRc = NULL);

// neue Geometrie 
	GeoObjekt *NewGI (GeoObjekt *) { return NULL; }
	bool ModIdent (long ONr, long newId, long oldId = -1L, short iTemp = 0);

// Zeichenattribute eines Objektes setzen/rücksetzen
	VisInfo *PresetAttributes (Window *pCanvas, long ONr);
	void ResetAttributes (void) {}
	bool ResetAttributes (long ONr, VisInfo *);

	CoordTrans * &pCT (void) { return _pCT; }

	bool QueryObjStatistik (HPROJECT hPr, OBJSTATISTIK *pOS);
	bool QueryObjGeometrie (HPROJECT hPr, OBJGEOMETRIE *pOG, IUnknown *pICS);
	bool ModObjGeometrie (HPROJECT hPr, OBJGEOMETRIE *pOG, IUnknown *pICS);
	bool GetTextObjektText (HPROJECT hPr, GETTEXTDATA *pGTD);
	bool PutTextObjektText (HPROJECT hPr, PUTTEXTDATA *pPTD);

	bool DeleteObjekt (INT_PTR ONr, bool fUndo = false);

	bool CloneObject (HPROJECT hPr, CLONEOBJECT *pCloneObj);
	
	GeoObjekt *MakeGI (OBJGEOMETRIE *, long *, long *);
	GeoObjekt *MakeGIObject (OBJGEOMETRIE *pGS, KoOrd *x, KoOrd *y);

	bool ChangeTextObjectText (LONG lONr, LPCSTR pcNewText);

	ObjTyp RetrieveObjTyp (long ONr);
	
	void EvalMasstab (Window *pW, double * = NULL);

	bool DeleteTempIdents (void);
	bool DeleteAllObjs (CIdentifikator *pId, short fToDelete, CIdentTable &tabObj, CONrTable &tabONr);

	bool GetObjPropDesc(INT_PTR lONr, LPSTR *ppObjDesc);

	bool ActivateSight (char *pSight);                      

	bool EnumRechTextMerkmal (ENUMRECHTEXTMERKMAL *);
	bool EnumRechGeometrie (ENUMRECHGEOMETRIE *);
	
	HRESULT SearchObjects (BSTR bstrCommand, BSTR bstrOutName, SAFEARRAY *pParam, 
		ObjFeld &rObjs, bool &rfFilteredColl, bool fFilterView = false, 
		LPCSTR pcView = NULL, INT_PTR lMCode = NULL);
	HRESULT SearchObjectsDataSource (GeoDB *pDB, BSTR bstrCommand, 
		ITRiASObjectsCollection *pIObjsColl, bool fFilterView, bool &rfFilteredColl, 
		SAFEARRAY *pParams, ITRiASObjects *pIObjsRes);

	bool isDrawing (void);
	void SavingDocument (bool fFlag) { m_fSavingDocument = fFlag; }

#if defined(_USE_LEGACY_CODE)
	short GetIdBase (void) { return m_IdentBase; }
	short GetMkBase (void) { return m_MCodeBase; }
	void SetIdBase (short newBase) { m_IdentBase = newBase; }
	void SetMkBase (short newBase) { m_MCodeBase = newBase; }
#endif // _USE_LEGACY_CODE

	bool RemoveTempIdents (void);
	ErrCode ReloadAllObjects (long lIdent);

	ErrCode ChangeVisInfo (long lIdent, short iVTyp, VISINFO &rVI, 
			       LPCSTR pcView = NULL, int fBits = -1, bool fForce = false);
	ErrCode ChangeVisInfo (CIdentifikator &rId, VisType iVTyp, 
			       VisInfo *pVI, LPCSTR pcView = NULL, int fBits = -1);

	HRESULT WriteBackVisInfos (void);
	HRESULT WriteBackVisInfo (CIdentifikator *pId, LPCSTR pcView, VisType iVTyp);

// Verwaltung der IdentMaßstabsBereiche
	bool RetrieveIdentScaleData (LPCSTR pcView, long lIdent, VisType rgVTyp, long *plUpper, long *plLower);
	bool SetIdentScaleData (LPCSTR pcView, long lIdent, VisType rgVTyp, long lUpper, long lLower);
	void ResetIdentScaleMCodes (bool fForce = false);

	ULONG QueryUnknownIdent (HPROJECT hPr);
	long FindObjFromName (char *);
		
// InitialisierungsFunktionen
	bool ReScale (Window *pW);
	bool ReReadIdents (void);

	bool QueryExposedOC (ObjContainer *pOC);
	bool QueryExposedArea (Rectangle *pRc);
	char *SetViewDesc (struct tagVIEWDESC *);
	char *QueryViewDesc (struct tagVIEWDESC *);
	
	void InitPbd (char *pDir, bool = false);
	ErrCode CloseDB (bool fCommit = true);
	ErrCode CloseConnection (GeoDB &rDB, bool fCommit = true);
	HRESULT OpenConnection (GeoDB &rDB, ITRiASConnection *pIConn);
	HRESULT AddConnection (IDispatch *pIConn);
	HRESULT RePrepareDBO (IrisWind *pWindow, Point ptAspect, HPROJECT hPr = HACTCONNECTION);

	bool SaveGeoDB (bool fAutoSave = false);
	bool SaveAsGeoDB (LPCSTR pcName);
	bool ExportAsGeoDB (LPCSTR pcName);

// Zugehöriges ViewWindow behandeln
	IrisWind *AttachViewWindow (IrisWind *pViewWnd);

inline IrisWind *DetachViewWindow (void) { return AttachViewWindow (NULL); }
inline IrisWind *GetViewWindow (void) { return m_pViewWnd; }

// Zugehöriges TRiASProject behandeln
	HRESULT AttachTRiASProject (ITRiASProject *pIPrj, ITRiASProject **ppIPrj = NULL);
	HRESULT DetachTRiASProject (ITRiASProject **ppIPrj = NULL)
		{ return AttachTRiASProject (NULL, ppIPrj); }
	HRESULT GetTRiASProject (ITRiASProject **ppIPrj);
	HRESULT ReReadHeader (void);

	inline bool IsValidDocument (void) 
	{ 
#if defined(_USE_LEGACY_CODE)
		if (!IsTRiASDBBased()) 
			return (!isClosing() && DB().isOpened()) ? true : false;
		else
#endif // _USE_LEGACY_CODE
			return (!isClosing() && HasOpenDB() && !isSaving()) ? true : false; 
	}
	inline bool HasOpenDB (void) 
		{ return m_pGeoDBs ? m_pGeoDBs -> HasOpenDB() : false; }
	inline bool IsValidConnection(HPROJECT hPr) 
		{ return (-1 == m_pGeoDBs -> FFindItem (hPr) || !DB(hPr).isOpened()) ? false : true; }
	inline bool IsValidProjectHandle (HPROJECT hPr)
		{ return ((HACTPROJECT == hPr) || (HACTCONNECTION == hPr) || IsValidConnection(hPr)) ? true : false; }

	HRESULT GetProjectStorage (IStorage **ppIStg);
	HRESULT GetDataSourceStorage (HPROJECT hPr, IStorage **ppIStg);
	HRESULT GetDataSourceDescription (HPROJECT hPr, char *pDesc);
	HRESULT GetDataSourceName (HPROJECT hPr, char *pName);
	HRESULT GetDataSourceShortName (HPROJECT hPr, char *pName);
	HRESULT GetTRiASConnection (HPROJECT hPr, ITRiASConnection **ppIConn);
	HRESULT RetrieveActiveProject (char *pBuffer, int iLen);
	ULONG GetDataSourceCount (LONG rgWhat);
	bool EnumDataSources (ENUMNOKEY *pK);
	bool EnumDataSourceHandles (ENUMNOKEYLONG *pK);
	HPROJECT GetDataSourceHandle (LPCSTR pcName);
	HPROJECT MakeDataSourceActive (HPROJECT hPr);
	HPROJECT GetDataSourceFromShortName (LPCSTR pcName);

	HRESULT GetRelatedDataSourceName (RELATEDDATASOURCENAME *pRDSN);

// Objektklassen einer Ansicht enumerieren
	bool EnumIdentViewsEx (ENUMLONGKEYEX *pENK);
	HRESULT GetViewCount (LONG *plCnt);

// Anzahl der definierten Objektklassen 
	HRESULT GetClassCount (LONG *plCnt);

// Export vornehmen
	ErrCode doExport (pWindow pW, ObjContainer *pOC = NULL, 
		class ObjFeld *pObjs = NULL, pWindow pWaitParent = NULL, bool fExportAll = false);

	bool isComFile (void);

	bool DeleteFeatures (LONG lONr);
	bool DeleteRelations (LONG lONr);

	bool ConvertRCToOC (double dX, double dY, KoOrd &rlX, KoOrd &rlY, bool fScale = false);
	bool ConvertOCToRC (KoOrd lX, KoOrd lY, double &rdX, double &rdY, bool fUnScale = false);
	bool ConvertRCToOCEx (double dX, double dY, KoOrd &rlX, 
		KoOrd &rlY, LPVOID pData, IUnknown *pICS = NULL, bool fScale = false);
	bool ConvertOCToRCEx (KoOrd lX, KoOrd lY, double &rdX, 
		double &rdY, LPVOID pData, IUnknown *pICS = NULL, bool fUnScale = false);

	long RetrieveIdent (LONG lONr, bool fForceNative = false);
	Color GetObjectColor (long lONr);
		
	Color GetBkColor (void) { return m_cBkColor; }
	void SetBkColor (Color cBkColor) { m_cBkColor = cBkColor; }

	bool isClosing (void) { return m_fToClose; }
	bool isOpeningOrClosing (void) { return m_fToClose || m_fIsOpening; }
	bool isSaving() { return m_fSavingDocument; }
	void toClose (bool fFlag = true) { m_fToClose = fFlag; }
	void isOpening (bool fFlag) { m_fIsOpening = fFlag; }
#if defined(_FORCE_LEGACY_CODE) || defined(_DEBUG)
	bool IsTRiASDBBased() { return m_Prj.IsValid(); }
#else
	bool IsTRiASDBBased() { return true; }		// was anderes gibts gar nicht mehr
#endif // defined(_FORCE_LEGACY_CODE) || defined(_DEBUG)
	bool GetROModeIdent (INT_PTR lIdent);
	bool GetROModeFeature (HPROJECT hPr, INT_PTR lMCode);
	HRESULT SetROModeIdent (INT_PTR lIdent, bool fROMode);
	HRESULT SetROModeFeature (INT_PTR lMCode, bool fROMode);
	bool GetSchemaUpdatable (HPROJECT hPr);
	INT_PTR GetFeatureIdent (INT_PTR lMCode);

	long GetClipRegionONr (LPCSTR pcView);
	bool SetClipRegionONr (CLIPOBJECTSET *pCOS);

// allgemeiner Merkmalszugriff
	LPCSTR QueryTextMerkmal (HPROJECT hPr, TARGETMERKMAL *pTM);
	ErrCode ModTextMerkmal (HPROJECT hPr, TARGETMERKMAL *pTM);

// Merkmale für Ansichten
	HRESULT PutMiTextSicht (LPCSTR pcView, LONG lMCode, LPSTR pText);
	HRESULT DelMiTextSicht (LPCSTR pcView, LONG lMCode);
	HRESULT GetMiTextSicht (LPCSTR pcView, LONG lMCode, LPSTR pText, short &riLen);
	BOOL EnumMiTextSicht (LPCSTR pcView, ENUMNOKEYPROC pFcn, void *pData);
	BOOL EnumMiTextSichtEx (LPCSTR pcView, DWORD dwData, ENUMNOKEYEXPROC pFcn, void *pData);

// Merkmale für Objektklassen (Idents)
	HRESULT PutMiTextIdent (LPCSTR pcView, INT_PTR lIdent, LONG lMCode, LPSTR pText);
	HRESULT DelMiTextIdent (LPCSTR pcView, INT_PTR lIdent, LONG lMCode);
	HRESULT GetMiTextIdent (LPCSTR pcView, INT_PTR lIdent, LONG lMCode, LPSTR pText, short &riLen);
	BOOL EnumMiTextIdent (LPCSTR pcView, INT_PTR lIdent, ENUMLONGKEYPROC pFcn, void *pData);
	BOOL EnumMiTextIdentEx (LPCSTR pcView, INT_PTR lIdent, DWORD dwData, ENUMLONGKEYEXPROC pFcn, void *pData);

// Merkmale für Objekte
	HRESULT GetObjectFeatures (INT_PTR lONr, ITRiASFeatures **ppIFeats, ITRiASObject **ppIObj = NULL);
	HRESULT PutMiTextObject (INT_PTR lONr, LONG lMCode, LPSTR pText);
	HRESULT DelMiTextObject (INT_PTR lONr, LONG lMCode);
	HRESULT GetMiTextObject (INT_PTR lONr, LONG lMCode, LPSTR pText, short &riLen);
	BOOL EnumMiTextObject (INT_PTR lONr, ENUMLONGKEYPROC pFcn, void *pData);
	BOOL EnumMiTextObjectEx (INT_PTR lONr, DWORD dwData, ENUMLONGKEYEXPROC pFcn, void *pData);
	BOOL EnumMiTextFeatures (ITRiASFeatures *pIFeats, DWORD dwTypes, ENUMLONGKEYEXPROC pFcn, void *pData, ITRiASObject *pIObj = NULL);
	HRESULT GetTextFeature (INT_PTR lObjs, INT_PTR *plFeat);

#if !defined(_FORCE_LEGACY_CODE)
	HRESULT GetObjectsFeatures (INT_PTR hObjs, ITRiASFeatures **ppIFeats, ITRiASObjects **ppIObjs = NULL);
	BOOL EnumMiTextObjectClassEx (INT_PTR hObjs, DWORD dwData, ENUMLONGKEYEXPROC pFcn, void *pData);
#endif // !defined(_FORCE_LEGACY_CODE)

// alle Attribute des Projektes
	BOOL EnumAllFeatures (ENUMNOKEYLONGPROC pFcn, void *pData);
	BOOL EnumAllFeaturesEx (ENUMNOKEYLONGEXPROC pFcn, DWORD dwData, void *pData);
	BOOL EnumAllFeaturesObjsEx (ENUMNOKEYLONGEXPROC pFcn, DWORD dwData, void *pData);

// Objektanzahl dieser GeoDB
	LONG CountObjects (void);
	LONG IncrementObjectCount (void);
	LONG DecrementObjectCount (void);
	LONG GetIdentObjectCount (IDENTOBJECTCOUNT *);
	LONG GetIdentObjectCountEx (IDENTOBJECTCOUNTEX *);

// Mapping Ident/Objektklassenschlüssel
	bool InitClsIdentMap (void);
	void DeleteClsIdentMap (void);
	HRESULT IdentFromClass(HPROJECT hPr, IDENTFROMCLASS *);
	HRESULT ClassFromIdent (HPROJECT hPr, CLASSFROMIDENT *);
	HRESULT ModObjClassCode (HPROJECT hPr, MODOBJCLASSCODE *);
	BOOL EnumClassProjects (LPCSTR pcClass, BOOL (CALLBACK *pFcn) (HPROJECT hPr, LPCSTR pcClass, UINT_PTR dwData), UINT_PTR dwData);

// Zuordnungsobjektklassen verwalten
	BOOL EnumObjectClasses (INT_PTR lONr, ENUMLONGKEYEXPROC pFcn, void *pData, DWORD dwData);
	BOOL IsObjectInClass (INT_PTR lIdent, INT_PTR lONr, INT_PTR *plONrMapped = NULL);

// Priorität ändern/abfragen
	HRESULT GetIdentPriority (IDENTPRIORITY *pData);
	HRESULT SetIdentPriority (IDENTPRIORITY *pData);

// Objekt hervorheben/wieder normal zeichnen
	bool ActivateObj (Window *pWnd, long lONr, COLORREF crAct, bool fAssoc = true);
	bool DeActivateObj (Window *pWnd, long lONr, bool fAssoc = true);

// ObjektGuid verwalten
	HRESULT GetObjectGuid (OBJECTGUID *pGuid);
	HRESULT FindObjectFromGuid (HPROJECT hPr, OBJECTGUID *pGuid);
	HRESULT SetObjectGuid (OBJECTGUID *pGuid);
	INT_PTR RetrieveObjGuidMCodeIdent (INT_PTR lIdent);

// BeschreibungsInfos verwalten
	bool SaveObjMCodeInPbd (LPCSTR pView, long lMCode, UINT uiResKT = 0, UINT uiResLT = 0, INT_PTR lONr = 0);
	bool SaveViewMCodeInPbd (LPCSTR pView, long lMCode, UINT uiResKT = 0, UINT uiResLT = 0, INT_PTR lONr = 0);
	bool SaveViewMCodeInPbd (LPCSTR pView, long lMCode, LPCSTR pcShort, LPCSTR pcLong, INT_PTR lONr = 0);
	bool SaveIdentMCodeInPbd (LPCSTR pView, long lMCode, UINT uiResKT = 0, UINT uiResLT = 0);

	long GetHeaderMCode (bool fGenerate, UINT resID, LPCSTR pView = NULL, UINT uiResKT = 0, UINT uiResLT = 0);
	long GetHeaderMCode (bool fGenerate, LPCSTR pcName, LPCSTR pView = NULL, LPCSTR pcShort = NULL, LPCSTR pcLong = NULL);
	long GetObjMCodeView (bool fGenerate, LPCSTR pView, long lVMCode, UINT uiResKT = 0, UINT uiResLT = 0, INT_PTR lONr = 0);
	long GetIdentMCodeView (bool fGenerate, LPCSTR pView, long lVMCode, UINT uiResKT = 0, UINT uiResLT = 0);
	INT_PTR FindMCodeFromKText (LPCSTR pcView, UINT uiResID);

	HRESULT GetNamedViewProperty (NAMEDVIEWPROPERTY *pNVP);
	HRESULT SetNamedViewProperty (NAMEDVIEWPROPERTY *pNVP);

///////////////////////////////////////////////////////////////////////////////
// Funktionen, die alle Connections verwenden
	BOOL EnumIdents (HPROJECT hPr, ENUMNOKEYLONGPROC pFcn, void *pData);
	BOOL EnumIdentsEx (HPROJECT hPr, ENUMNOKEYLONGEXPROC pFcn, void *pData, DWORD dwData);

	HRESULT GIWindow (ObjContainer &rOC, ObjFeld &rObjs, BOOL fExact, BOOL fFilterView, LPCSTR pcView = NULL);

	ObjContainer DBCont (bool fReRead = false);

	HPROJECT DBDesc();								// Projekthandle liefern
	bool GetTempMode();								// Projekt wurde temporär erzeugt
	LPCSTR GetDBName (LPSTR cbBuffer);				// Projektnamen liefern
	bool GetROMode();								// Echter Schreibschutz
	bool isCopy();									// wurde beim Öffnen kopiert
	bool isDirty(void);								// Projekt wurde modifiziert
	void SetDirty (bool fFlag = true);
	bool isOpened() { return (NULL != DBDesc()) ? true : false; }

	void SetActive (bool fFlag = true);
	bool IsActive (void);

	BOOL EnumIdentObjects (HPROJECT hPr, long lIdent, ENUMLONGKEYPROC pFcn, void *pData);
	BOOL EnumIdentObjectsEx (HPROJECT hPr, long lIdent, ENUMLONGKEYEXPROC pFcn, void *pData, DWORD dwData);

///////////////////////////////////////////////////////////////////////////////
// ProjektHeaderFunktionen
	ErrCode GetHeaderEntry (HPROJECT hPr, GEODBHDRENTRY *pHE);
	ErrCode SetHeaderEntry (HPROJECT hPr, GEODBHDRENTRY *pHE);
	ErrCode DeleteHeaderEntry (HPROJECT hPr, GEODBHDRENTRY *pHE);
	BOOL EnumHeaderData (HPROJECT hPr, ENUMNOKEYCALLBACK pFcn, void *pData);

	ErrCode MainInitPbd (GeoDB &rDB, UINT resID = 0, BOOL iEnterNewCode = FALSE, long lNewCode = -1L);
	long GetUniqueICode (HPROJECT hPr, BOOL fSystem = FALSE);
	long GetUniqueMCode (HPROJECT hPr, BOOL fSystem = FALSE);
	long GetUniqueRCode (void);
	long GetUniqueTempONr (void);

#if defined(_FORCE_LEGACY_CODE)
	long GetUniqueLong (unsigned int resID, long lFirstCode);
#endif // defined(_FORCE_LEGACY_CODE)

///////////////////////////////////////////////////////////////////////////////
// Connectionfilter
	HRESULT CreateConnectionFilter (CONNECTIONFILTER *pCF);
	HRESULT GetConnectionFilter (CONNECTIONFILTER *pCF);
	HRESULT DeleteConnectionFilter (CONNECTIONFILTER *pCF);
	BOOL EnumConnectionFilters (ENUMNOKEY *pENK);
	HRESULT AttachConnectionFilter (ATTACHCONNECTIONFILTER *pACF);
	HRESULT DetachConnectionFilter (ATTACHCONNECTIONFILTER *pACF);
	HRESULT GetAttachedConnectionFilter (GETATTACHEDCONNECTIONFILTER *pGACF);
	
	BOOL SetAllConnectionFilters(LPCSTR pcConnFilter);
	BOOL GetConnectionFilter (LPCSTR pcView , LPSTR pConnFilter, int iLen);
	BOOL SetConnectFilter(LPCSTR pcView, LPCSTR pcConnFilter);

///////////////////////////////////////////////////////////////////////////////
// MetaDatenzugriff
	long GetPBDVersion(HPROJECT hPr);
	ErrCode BeginTransaction(HPROJECT hPr);
	ErrCode BreakTransaction(HPROJECT hPr);
	ErrCode EndTransaction(HPROJECT hPr);

	ErrCode GetPBDData (HPROJECT hPr, PBDDATA *pData);
	ErrCode ModPBDData (HPROJECT hPr, PBDDATA *pData);
	ErrCode DelPBDData (HPROJECT hPr, PBDDATA *pData);
	BOOL EnumPBDData (HPROJECT hPr, long lKey, ENUMLONGKEYPROC pFcn, void *pData);

	HRESULT GetPBDDataIdent (HPROJECT hPr, PBDDATA *pData);
	HRESULT ModPBDDataIdent (HPROJECT hPr, PBDDATA *pData);
	HRESULT DelPBDDataIdent (HPROJECT hPr, PBDDATA *pData);
	BOOL EnumPBDDataIdent (HPROJECT hPr, ENUMLONGKEYPROC pFcn, void *pData);

	HRESULT GetTableName (TABLENAME *pTableName);

	HRESULT GetPBDDataMerkmal (HPROJECT hPr, PBDDATA *pData);
	HRESULT ModPBDDataMerkmal (HPROJECT hPr, PBDDATA *pData);
	HRESULT DelPBDDataMerkmal (HPROJECT hPr, PBDDATA *pData);
	BOOL EnumPBDDataMerkmal (HPROJECT hPr, ENUMLONGKEYPROC pFcn, void *pData);

// HelperFunktionen
	LPCSTR GetKurzText (INT_PTR lIdent, BOOL fAppendDataSource = FALSE) { return Idents().GetKurzText(lIdent, fAppendDataSource); }
	LPCSTR GetLangText (INT_PTR lIdent) { return Idents().GetLangText(lIdent); }

// 
	BOOL HandleImportMode (BOOL fImportMode);

///////////////////////////////////////////////////////////////////////////////
// 'globalen' TranformationsBuffer behandeln
	POINT *AllocDrawBuffer (size_t lCntPts);
	CSCOORD *GetCoordBuffer();
	void FreeDrawBuffer();

///////////////////////////////////////////////////////////////////////////////
// Bildausschnitt ins ClipBoard kopieren 
	ErrCode CopyToClipBoard (pWindow pW, Rectangle &Rc);

///////////////////////////////////////////////////////////////////////////////
// aktuellen Maßstab
inline long GetActScale (void) { return m_lActScale; }
inline void SetActScale (long lActScale) { m_lActScale = lActScale; }

// Scaling/UnScaling
	bool ScaleCTF (const double &rdX, const double &rdY, KoOrd *plX, KoOrd *plY)
		{ return (NULL != pCT()) ? pCT() -> Scale (rdX, rdY, plX, plY) : false; }
	bool UnScaleCTF (const KoOrd &rlX, const KoOrd &rlY, double *pdX, double *pdY)
		{ return (NULL != pCT()) ? pCT() -> UnScale (rlX, rlY, pdX, pdY) : false; }

// diverse Infos am Ende wegschreiben
	bool SaveHeader (void);

// zuletzt angezeigte Objekteigenschaft
	LPCSTR GetLastName() { return m_strLastName.c_str(); }
	void SetLastName(LPCSTR pcLastName) { m_strLastName = pcLastName; }

#if defined(_FORCE_LEGACY_CODE)
inline	PBD_DB &PbdDB (void) { return m_pbdDB; }
#endif // defined(_FORCE_LEGACY_CODE)

inline	void PosTextAtBaseLine (bool fPos) { m_fPosTextAtBaseLine = fPos; }
inline	bool PosTextAtBaseLine (void) { return m_fPosTextAtBaseLine; }
inline	void Compatibility (bool fFlag) { m_fCompatibility16 = fFlag; }
inline	bool Compatibility (void) { return m_fCompatibility16; }

// Implementation of IPersistStorage-related functionality
	HRESULT Save (IStorage *pIStg, BOOL fSameAsLoad);
	HRESULT SaveCompleted (IStorage *pIStg);
	HRESULT HandsOffStorage ();

// Destruktor
		~DatenBasisObjekt (void);
};

///////////////////////////////////////////////////////////////////////////////
// Flags fürs Zeichnen
const short GCFNormal 		= 0x00;
const short GCFAbort 		= 0x01;
const short GCFRepaint		= 0x02;
const short GCFAppClosed	= 0x04;

const UINT MAXSHOWNVIEWS = 20;		// max. Anzahl der Sichten im Menu

#endif // !defined(_DBOBJECT_H__A37D8269_4A3F_11d1_96DC_00A024D6F582__INCLUDED_)
