// Drag'n Drop Source/Target für Objektrecherchefenster
// File: DDORWND.H

#if !defined(_DDORWND_H)
#define _DDORWND_H

///////////////////////////////////////////////////////////////////////////////
// DropSourceObject für ObjektRechercheFenster
class CORWndDropSource :
	public IDropSource,
	public CComObjectRoot
//	public CComObjectBase<&CLSID_ORWndDropSource>
{
private:
	ObjektInfo *m_pBack;	// zugehöriges ORFenster
	DWORD m_dwFlags;		// DragModi (MouseBttns)

public:
	BEGIN_COM_MAP(CORWndDropSource)
		COM_INTERFACE_ENTRY(IDropSource)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CORWndDropSource)		// class factory

		CORWndDropSource() { m_pBack = NULL; m_dwFlags = 0L; }
		~CORWndDropSource() {}

	bool FInit (ObjektInfo *pBack, DWORD dwFlags = MK_LBUTTON);

// *** IDropSource interface members
	STDMETHOD(QueryContinueDrag) (THIS_ BOOL fEscapePressed, DWORD grfKeyState);
	STDMETHOD(GiveFeedback) (THIS_ DWORD dwEffect);
};

///////////////////////////////////////////////////////////////////////////////
// DropTargetObject für ObjektRechercheFenster
class CORWndDropTarget :
	public IDropTarget,
	public CComObjectRoot
//	public CComObjectBase<&CLSID_ORWndDropTarget>
{
private:
	ObjektInfo *m_pBack;			// Rückverweis auf ORWnd
	WDataObject m_DataObject;		// Daten der DragDropOperation

	UINT m_uiLastTest;
	DWORD m_dwLastKeyState;			// KeyState der letzte D&D Aktion

	UINT m_uiVertScroll;
	DWORD m_dwLastTime;

public:
	BEGIN_COM_MAP(CORWndDropTarget)
		COM_INTERFACE_ENTRY(IDropTarget)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CORWndDropTarget)		// class factory

		CORWndDropTarget() :
			m_dwLastKeyState(0) 
		{ 
			m_pBack = NULL; 
		}
		~CORWndDropTarget() {}

	bool FInit (ObjektInfo *pBack);

// *** IDropTarget interface members
	STDMETHOD(DragEnter) (THIS_ IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffekt);
	STDMETHOD(DragOver) (THIS_ DWORD grfKeyState, POINTL pt, DWORD *pdwEffekt);
	STDMETHOD(DragLeave) (THIS);
	STDMETHOD(Drop) (THIS_ IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffekt);

// sonstige ZugriffsFunktionen
	void SetVertScrollCode (UINT uiCode) { m_uiVertScroll = uiCode; }
	UINT GetVertScrollCode (void) { return m_uiVertScroll; }

	void SetLastTest (UINT uiTest) { m_uiLastTest = uiTest; }
	UINT GetLastTest (void) { return m_uiLastTest; }

	void SetLastTime (DWORD dwTime) { m_dwLastTime = dwTime; }
	void ResetLastTime (void) { m_dwLastTime = 0L; }
	DWORD GetLastTime (void) { return m_dwLastTime; }

	DWORD GetScrollDelay (void) { return g_dwScrollDelay; }
};

#endif // _DDORWND_H
