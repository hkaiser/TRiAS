#include "FrameStatus.h"
#include "ToolBars.h"

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	WINDOWPLACEMENT m_wndPlacement;
	int m_nRestore;
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

//	CSplitterWnd	m_splitHorz;
	CFrameStatus	m_wndStatusBar;

	CTBObjects	m_tbObjects;
	CTBModes	m_tbModes;
	CTBMaps		m_tbMaps;

// Attributes
public:
	void LoadMapIdents( CMapMgrDoc* pDoc, LPCTSTR lpszSelectedItem );
	BOOL RestorePosition( int nCmdShow );
	BOOL SavePosition();

// Operations
public:

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnAppstart();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg void OnChangeMap( LPCTSTR lpszMapName );
	afx_msg void OnUpdateTime(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePictCoord(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePictSize(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};
