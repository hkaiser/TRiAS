// BeispielErweiterungsklasse, um den gesamten Mechanismus zu dokumentieren
// File: EDITOBJ.HXX

#if !defined(_EDITOBJ_HXX)
#define _EDITOBJ_HXX

class IdentList;	// lediglich deklarieren
class ShiftRectangleObject;
class Punkt;

class EditObjExtension : public CTriasExtension {
private:
	short _iPktTool;	// Nummer des PunktWerkzeuges
	short _ShowPointSem;	// PointMenu ist angezeigt
	short _isActive;	// Erweiterung ist scharf 
	
	short _RightButtonSem;	// MaustastenSynchronisation
	short _LeftButtonSem;
	
	IdentList *_pIL;
	ShiftRectangleObject *_pSRO;	// ShiftRechteck

	long _lLastId;		// letzter gewählter Identifikator

protected:
// überladene virtuelle Funktion(en)
	STDMETHOD_(bool, InitExtension) (THIS_ short iMode);
	STDMETHOD_(bool, UnLoadExtension) (THIS);
	STDMETHOD_(bool, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(bool, MenuCommand) (THIS_ UINT uiMenuID, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);
	STDMETHOD_(LRESULT, WindowsNotification) (THIS_ UINT wMsg, WPARAM wParam, LPARAM lParam);

#if defined(WIN32)
	HRESULT BeginUndoForModPoint (OBJGEOMETRIE &rOG, IUndoRedoModifyObject **ppIUndo, LPCRECT pcRc);
	HRESULT BeginUndoForDelPoint (LONG lONr, IUndoRedoModifyObject **ppIUndo);
	HRESULT EndoUndoForPoint (IUndoRedoModifyObject *pIUndo);

	bool RemoveToolbarButton (void);
	int InstallToolbarButton (void);
#endif // WIN32

public:
// Konstruktor / Destruktor
		EditObjExtension (void);
		~EditObjExtension (void);

	Bool FindPointObjFromPoint (Point &Pt, Bool iCorrect = TRUE);
	void ShowPointMenu (Point Pt);
	void TrackPointObjectMenu (pWindow pW, pWindow pWCoord, Point Pt);
	
	void MovePointObj (Point, Bool = TRUE);
	Bool SavePointObj (void);

	Bool CreatePointObj (void);
	Bool DeletePointObj (void);
	Bool EditPointObj (void);
	Bool EditPointObj (long, Punkt &, HWND = 0);
};

#endif 	// _EDITOBJ_HXX
