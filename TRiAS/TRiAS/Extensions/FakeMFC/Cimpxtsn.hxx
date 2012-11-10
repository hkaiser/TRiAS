// Implementation des ITriasXtension ------------------------------------------
// File: CIMPXTSN.HXX

#if !defined(_CIMPXTSN_HXX)
#define _CIMPXTSN_HXX

// Dieses Interface ist vollständig delegierend. Die IUnknown-Funktionen
// werden an das controlling unknown weitergereicht, alle anderen (inhaltlichen)
// Funktionen erledigt das ErweiterungsObjekt selbst. das ist zwar etwas 
// umständlich, aber alle bisherigen Erweiterungen müssen lediglich recompiliert
// werden.
class CImpTriasXtension : 
	public ITriasXtension2 
#if defined(_USE_DRAG_N_DROP)
	, public ITRiASDropTarget
	, public IDragDropAction
#endif // defined(_USE_DRAG_N_DROP)
{
private:
#if defined(_DEBUG)
	DWORD m_dwRefCnt;	// reference count (debug purposes)
#endif // _DEBUG
	LPUNKNOWN m_pUnkOuter;
	class CFakeMFCExtension *m_pObj;

public:
		CImpTriasXtension (LPUNKNOWN pUnkOuter, CFakeMFCExtension *pObj);
		~CImpTriasXtension (void);

// *** IUnknown methods *** (delegates to m_pUnkOuter)
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** ITriasXtension specific functions *** (delegates to m_pObj)
	STDMETHOD_(HDEX, LoadExtension) (THIS_ TRIASLOADEX *pTL, HWND hWnd);
	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);
	STDMETHOD_(BOOL, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuSelect) (THIS_ UINT uiMenuID, HMENU hMenu, HWND hWnd);
	STDMETHOD_(BOOL, MenuCommand) (THIS_ WPARAM wParam, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);
	STDMETHOD_(LRESULT, WindowsNotification) (THIS_ UINT wMsg, WPARAM wParam, 
						  LPARAM lParam);
	STDMETHOD_(LRESULT, GetCapabilities) (THIS_ UINT uiCap);

// *** ITriasXtension2 specific functions *** (delegates to m_pObj)
	STDMETHOD(SetXtensionSite) (THIS_ ITriasXtensionSite *pXtnSite);

#if defined(_USE_DRAG_N_DROP)
// ITRiASDropTarget
	STDMETHOD(DragEnter) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	STDMETHOD(DragOver) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	STDMETHOD(DragLeave) (THIS_ DRAGDROPTYPE rgType, HWND hWnd);
	STDMETHOD(Drop) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);

// IDragDropAction
	STDMETHOD(BeginDragDrop) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, DWORD dwFlags, IDataObject *pIDO);
	STDMETHOD(DoDragDrop) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, IDataObject *pIDO, IDropSource *pISrc, DWORD dwOKEffects, DWORD *pdwEffect);
	STDMETHOD(EndDragDrop) (THIS_ DRAGDROPTYPE rgType, HWND hWnd, DWORD dwFlags);
#endif // defined(_USE_DRAG_N_DROP)
};

#endif // _CIMPXTSN_HXX
