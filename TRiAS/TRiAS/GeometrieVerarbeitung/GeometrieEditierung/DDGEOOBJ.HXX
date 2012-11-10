// Deklaration eines Interfaces für Erweiterung "GeometrieEditierung"
// Drag and Drop Source/Target für GeometrieObjekte
// File: DDGEOOBJ.HXX

#if !defined (_DDGEOOBJ_HXX)
#define _DDGEOOBJ_HXX



///////////////////////////////////////////////////////////////////////////////////////////////////
// DropSourceObject
class GeoEditExtension;
class CEditDropSource : public IDropSource
{
private:
	DWORD m_dwRefCnt;
	GeoEditExtension* m_pGeoEdit;
	DWORD m_dwFlags;			// DragModi (MouseBttns)

protected:
	CEditDropSource (void);

public:
	// nur dynamisch über "CreateInstance" zu generieren
	static CEditDropSource* CreateInstance (GeoEditExtension* pGeoEdit);
	bool FInit (GeoEditExtension* pGeoEdit, DWORD dwFlags = MK_LBUTTON);

		~CEditDropSource (void);

	// IUnknown-Methoden
	STDMETHOD_ (ULONG, AddRef) (THIS);
	STDMETHOD_ (ULONG, Release) (THIS);
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);

	// IDropSource-Methoden
	STDMETHOD(QueryContinueDrag) (THIS_ BOOL fEscapePressed, DWORD grfKeyState);
	STDMETHOD(GiveFeedback) (THIS_ DWORD dwEffect);
};
/*

///////////////////////////////////////////////////////////////////////////////////////////////////
// DropTargetObject
	DefineSmartInterface(DataObject);

class CEditDropTarget : public ITRiASDropTarget
{
private:
	DWORD m_dwRefCnt;
	GeoEditExtension* m_pGeoEdit;
	LPUNKNOWN m_pIUnk;
	short m_iAnzVO;				// Anzahl der verschobenen Objekte
	long* m_plObjNrVO;			// Objektnummern der verschobenen Objekte
	POINTL m_ptlOld;			// Punkt (in Fensterkoordinaten), bei dem Objektumriß zu löschen ist
	Point* m_pPolyPoly;			// Vektor mit Stützpunktkoordinaten in BS-Format,
	int* m_piPolyCounts;		//  einzelne Stützpunktanzahl und

	HRESULT GetObjNummern (IDataObject* pIDataSource);
	bool UmrissVektor (void);

protected:
	CEditDropTarget (LPUNKNOWN pIUnk, GeoEditExtension* pGeoEdit);

public:
	// nur dynamisch über "CreateInstance" zu generieren
	static CEditDropTarget* CreateInstance (LPUNKNOWN pIUnk, GeoEditExtension* pGeoEdit);
	bool FInit (void);

		~CEditDropTarget (void);

	// IUnknown-Methoden
	STDMETHOD_ (ULONG, AddRef) (THIS);
	STDMETHOD_ (ULONG, Release) (THIS);
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);

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
*/
#endif // _DDGEOOBJ_HXX
