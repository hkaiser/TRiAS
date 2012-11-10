// Deklarationen: Klasse für die Erweiterung "Geometrie-Editierung"
// File: GeoEdit.h

#ifndef _GEOEDIT_H
#define _GEOEDIT_H


#include "SmartInterfaces.h"

#include "operguid.h"	// CLSID_GeometrieOperationen, IID_IExtendObjOper
#include "objgguid.h"	// CLSID_ObjektGeometrie, IID_IInitObjektGeometrie
#include "EditGuid.h"	// CLSID_GeometrieEditierung2, IID_IExtendGeoEdit



///////////////////////////////////////////////////////////////////////////////////////////////
// IEditExtensionSite ist das Interface, das die GeoEdit-Erweiterung für die
// EditierOperationen (NewPoint, NewLine, ...) bereitstellt, d.h. das Interface, über das die
// EditierOperationen die GeoEdit-Erweiterung rufen können (Gegen-Interface zu
// IEditOperation);
// IEditExternalObjects ist das Interface, das die GeoEdit-Erweiterung bereitstellt, damit die 
// ausgewählten m_wTopObjs-Objekte beliebig vorgegeben werden können
class CGeoEditExtension : public CTriasExtension,
						  public IExtendGeoEdit,
						  public ITRiASDropTarget,						  
						  public IEditExtensionSite,
						  public IEditExternalObjects,
						  // hier evtl. noch weitere Interface's einfügen
						  public CComCoClass<CGeoEditExtension, &CLSID_GeometrieEditierung2>
{
private:
	bool m_bSight;			// eine Sicht wurde ausgewählt (true)
	bool m_bEditTBarInst;	// Editierwerkzeuge sind installiert (true)
	bool m_bDesignTBarInst;	// Designingwerkzeuge sind installiert (true)
	bool m_bExtActive;		// Erweiterung ist aktiviert (true)
	int m_iPrevTool;		// das vorher ausgewählte Werkzeug
	bool m_bVtIndicate;		// Stützpunkte sind markiert (true)

	WTRiASDropTarget m_wTDropTarget;	// Interface für Drag/Drop
	WEditOperation m_wEditOper;			// Interface zur aktuellen EditierOperation
	WEditOperation m_wParkEditOper;		// Interface zur geparkten EditierOperation
	WTopicalObjects m_wTopObjs;			// Interface der Klasse CTopicalObjects
	WExtendBScript m_wBScript;
	WExtendObjOper m_wObjOper;			// Interface für Ankopplung von ObjOper.ext

	CursForm m_CF;			// aktuelle CursorForm
	Pointer* m_EditCursor;	// eigener Cursor für Editierung
	Pointer* m_VertexCursor;// eigener Cursor, wenn Cursor auf Stützpunkt
							// (Geometrie-Modifizierung)
	Pointer* m_LineCursor;	// eigener Cursor, wenn Cursor auf Strecke
	Pointer* m_DeleteCursor;// eigener Cursor, wenn Cursor auf Stützpunkt und CTRL-Taste
							// gedrückt
	Pointer* m_InsideCursor;// eigener Cursor, wenn Cursor innerhalb eines ausgewählten Objektes
	Pointer* m_GrabCursor;	// eigener Cursor, wenn Cursor auf Stützpunkt (Stützpunkt-Angrabben)
	Pointer* m_OldCursor;	// vorhergehender eigener Cursor

	RECT m_REC;						// Position des letzten von mir hinzugefügten EditToolButton
	long m_lRegONr1;				// Objektnummmer des 1. Bezugsobjektes
	long m_lRegONr2;				// Objektnummmer des 2. Bezugsobjektes
    WRestrictLine m_wRestrLine1;	// Konstruktionshilfslinie zum 1. Bezugsobjekt
    WRestrictLine m_wRestrLine2;	// Konstruktionshilfslinie zum 2. Bezugsobjekt
	int m_iROInd;					// Index für Konstruktionshilfslinien
	bool m_bOpParked;				// eine EditierOperation ist geparkt (true)

	// Memberfunktionen
	HRESULT SetActiveTool (long lTool);
	HRESULT EditToolChecked (long lTool);
	bool CursorForEditTool (void);
	void ReactivateParkedOperation (void);
	void TerminateParkedOperation (void);
	void StatuszeileModifizieren (CursForm CF);
	HRESULT GetStartIndex (long lONr, RefLine rfLine, IEnumLONG* pEnumIn, long& lStartInd);
	HRESULT CommonLineWithRectObject (long lONr, KoOrd* plXK, KoOrd* plYK, long lCnt0,
			long& lStartInd);
	HRESULT CommonLine (long lONr, KoOrd* plXK, KoOrd* plYK, long lCnt0, IEnumLONG* pEnumIn,
			long& lStartInd);
	void LongestLine (KoOrd* plXK, KoOrd* plYK, long lCnt0, long& lStartInd);
	void SouthernmostLine (KoOrd* plXK, KoOrd* plYK, long lCnt0, long& lStartInd);
	HRESULT GiveLongestLine (IEnumLONG* pComCont, KoOrd& x0, KoOrd& y0, KoOrd& x1, KoOrd& y1);
	HRESULT VisualCommonContour (IEnumLONG* pComCont);
	HRESULT StartIndex (KoOrd* plXK, KoOrd* plYK, long lCnt0, KoOrd x0, KoOrd y0, KoOrd x1,
			KoOrd y1, long& lStartInd);

protected:
	HRESULT InstallEditToolbar (void);
	HRESULT RemoveEditToolbar (void);
	HRESULT InstallDesignToolbar (void);
	HRESULT RemoveDesignToolbar (void);

	bool RegisterBScriptExtension (void);

public:
// Die folgende Zeile nur, wenn aggregierte Erweiterung gefordert ist
//	DECLARE_AGGREGATABLE(CGeoEditExtension);

	BEGIN_COM_MAP(CGeoEditExtension)
		COM_INTERFACE_ENTRY(ITriasXtension2)	// immer mit eintragen
		COM_INTERFACE_ENTRY(ITriasXtension)		// immer mit eintragen
		COM_INTERFACE_ENTRY(ITRiASDropTarget)
		COM_INTERFACE_ENTRY(IExtendGeoEdit)
		COM_INTERFACE_ENTRY(IEditExtensionSite)
		COM_INTERFACE_ENTRY(IEditExternalObjects)
		// hier evtl. noch weitere Interface's eintragen
	END_COM_MAP()

// Die folgende Zeile einfügen, wenn der alte Mechanismus der Registrierung der Erweiterungen
// intakt bleibt
	DECLARE_NO_REGISTRY();
	DECLARE_NOT_AGGREGATABLE_SINGLE(CGeoEditExtension, g_pTE);

		CGeoEditExtension (void);

	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuCommand) (THIS_ WPARAM wParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuSelect) (THIS_ UINT uiMenuID, HMENU hMenu, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wMsg, LPARAM lParam);
	STDMETHOD_(LRESULT, WindowsNotification) (UINT wMsg, WPARAM, LPARAM);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);

	// Zugriff auf Member
	bool IsSightSelected (void) { return m_bSight; }
	long TopicalObjsCount (void);
	bool IsRestrictLineExist (void);
	bool IsOpParked (void) { return m_bOpParked; }
	bool ResetTopicalObjects();

	// weitere Memberfunktionen
	HRESULT RectangularObject (long lONr);

	// IExtendGeoEdit-Methoden
	STDMETHOD_ (HRESULT, MakeRectangular_ONr) (LONG lONr, RefLine rfLine, double dEps90,
					double dEps180, double dEpsCom, IEnumLONG* pEnumIn, IEnumLONG** ppEnumOut);

	// IEditExtensionSite-Methoden
	STDMETHOD (GetXtensionSite) (IUnknown** ppIUnk);
	STDMETHOD (GetMenuOffset) (UINT* pMenuOffset);
	STDMETHOD (SetCursor) (CursForm CF = CURSFORM_PFEIL, BOOL bPseudoMove = TRUE);
	STDMETHOD (GetCursor) (CursForm* pCursor);
	STDMETHOD (CreateInterfaceTO) (ITopicalObjects** ppITO);
	STDMETHOD (ShowEditDialog) (LPCSTR pcCapt, LPCSTR pcRegKey, ulong ulCnt, IUnknown** ppIOG,
				 int* piGrabCnt, long* pGrabPktX, long* pGrabPktY, HRESULT hrComBorder,
				 long lComONr, int iCloseCnt, long* plCloseX, long* plCloseY, int* piResult);
	STDMETHOD (StoreNewObject) (IUnknown* pIOG, BSTR bsObjName);
	STDMETHOD (ObjOperInterface) (IUnknown** ppIObjOper);
	STDMETHOD (GetRestrictLine) (IRestrictLine** ppRestrLine);
	STDMETHOD (SetRestrictLine) (long lRegONr, IRestrictLine* pRestrLine);
	STDMETHOD (DeleteRestrictLines) (void);

	// IEditExternalObjects-Methoden
	STDMETHOD (AddObject) (void);		// noch nicht ausgeführt
	STDMETHOD (GetObject) (void);		// noch nicht ausgeführt
	STDMETHOD (RemoveObject) (void);	// noch nicht ausgeführt
	STDMETHOD (AddObjects) (IDispatch* pIDisp);
	STDMETHOD (GetObjects) (IDispatch** ppIDisp, long lObjTypes);
	STDMETHOD (RemoveObjects) (void);

	// ITRiASDropTarget-Methoden (unterscheiden sich in den Parametern von den IDropTarget-Methoden
	// dadurch, daß die ersten beiden Parameter hinzugekommen sind)
	STDMETHOD (DragEnter) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, IDataObject* pIDataSource,
						   DWORD grfKeyState, POINTL ptl, DWORD* pdwEffekt);
	STDMETHOD (DragOver) (THIS_ DRAGDROPTYPE rgType, HWND hWnd,	DWORD grfKeyState, POINTL ptl,
						  DWORD* pdwEffekt);
	STDMETHOD (DragLeave) (THIS_ DRAGDROPTYPE rgType, HWND hWnd);
	STDMETHOD (Drop) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, IDataObject* pIDataSource,
					  DWORD grfKeyState, POINTL ptl, DWORD* pdwEffekt);

};

#endif // _GEOEDIT_H
