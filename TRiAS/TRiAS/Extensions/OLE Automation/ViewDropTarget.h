// DropTarget für View-Fenster
// File: VIEWDROPTARGET.H

#if !defined(_VIEWDROPTARGET_H)
#define _VIEWDROPTARGET_H

DefineSmartInterface(DataObject);

class CViewDropTarget :
	public IDropTarget,
	public CComObjectRoot
{
private:
	CGeoDoc *m_pDoc;
	OLE2AutoExtension *m_pExt;
	WDataObject m_DataSource;
	UINT m_uiButton;

public:
	BEGIN_COM_MAP(CViewDropTarget)
		COM_INTERFACE_ENTRY(IDropTarget)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CViewDropTarget)		// class factory

		CViewDropTarget(void) 
			: m_pDoc(NULL), m_pExt(NULL), m_uiButton(0) {}
		~CViewDropTarget(void) {}

	bool FInit (OLE2AutoExtension *pExt, CGeoDoc *pDoc) 
		{ 
			m_pExt = pExt; m_pDoc = pDoc; 
			return (NULL != m_pDoc) ? true : false; 
		}

// *** IDropTarget interface members
	STDMETHOD(DragEnter) (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffekt);
	STDMETHOD(DragOver) (DWORD grfKeyState, POINTL pt, DWORD *pdwEffekt);
	STDMETHOD(DragLeave) (void);
	STDMETHOD(Drop) (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffekt);

	bool IsSource (void) { return m_pDoc -> IsDocSource(); }
	bool IsSourceInstance (void) { return m_pExt -> IsSource(); }
};

#endif // _VIEWDROPTARGET_H

