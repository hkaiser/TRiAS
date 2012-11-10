// DropTarget für View-Fenster
// File: VIEWDROP.H

#if !defined(_VIEWDROP_H)
#define _VIEWDROP_H

DefineSmartInterface(DataObject);

class CViewDropTarget :
	public IDropTarget,
	public CComObjectRoot
//	public CComObjectBase<&CLSID_ViewDropTarget>
{
private:
	IrisWind *m_pBack;
	WDataObject m_DataSource;

	UINT m_uiLastTest;

	UINT m_uiVertScroll;
	UINT m_uiHorzScroll;
	DWORD m_dwLastTime;

public:
	BEGIN_COM_MAP(CViewDropTarget)
		COM_INTERFACE_ENTRY(IDropTarget)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CViewDropTarget)		// class factory

		CViewDropTarget(void);
		~CViewDropTarget(void);

	bool FInit (IrisWind *pBack);

// *** IDropTarget interface members
	STDMETHODIMP DragEnter (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffekt);
	STDMETHODIMP DragOver (DWORD grfKeyState, POINTL pt, DWORD *pdwEffekt);
	STDMETHODIMP DragLeave (void);
	STDMETHODIMP Drop (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffekt);

// sonstige ZugriffsFunktionen
	void SetHorzScrollCode (UINT uiCode) { m_uiHorzScroll = uiCode; }
	void SetVertScrollCode (UINT uiCode) { m_uiVertScroll = uiCode; }
	UINT GetHorzScrollCode (void) { return m_uiHorzScroll; }
	UINT GetVertScrollCode (void) { return m_uiVertScroll; }

	void SetLastTest (UINT uiTest) { m_uiLastTest = uiTest; }
	UINT GetLastTest (void) { return m_uiLastTest; }

	void SetLastTime (DWORD dwTime) { m_dwLastTime = dwTime; }
	void ResetLastTime (void) { m_dwLastTime = 0L; }
	DWORD GetLastTime (void) { return m_dwLastTime; }

	DWORD GetScrollDelay (void) { return g_dwScrollDelay; }
};

#endif // _VIEWDROP_H

