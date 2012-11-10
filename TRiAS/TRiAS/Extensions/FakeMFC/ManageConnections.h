// ManageConnections.h : header file
//

#if !defined(AFX_MANAGECONNECTIONS_H__AFEAD084_7006_11D1_9749_00A024D6F582__INCLUDED_)
#define AFX_MANAGECONNECTIONS_H__AFEAD084_7006_11D1_9749_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ListCtrlEx.h"
#include "ConnectParams.h"
#include "CoolBtn.h"
#include "PopupMenu.h"

/////////////////////////////////////////////////////////////////////////////
// DataItem, welches in Tree hängt

DefineSmartInterface(TRiASConnection);

enum DIRTYFLAG {
	DIRTYFLAG_NoChange = 0x00,
	DIRTYFLAG_DescriptionChanged = 0x01,
	DIRTYFLAG_ModeChanged = 0x02,
	DIRTYFLAG_StatusChanged = 0x04,
	DIRTYFLAG_NameChanged = 0x08,
	DIRTYFLAG_ConnectionFilterChanged = 0x10,
	DIRTYFLAG_Mask = 0x1f,

	DIRTYFLAG_ConnectionFilterChangedMask = 0x10,
	DIRTYFLAG_ConnectParamsInitialized = 0x100,
};

class CManageDataServerItem
	: public CConnectParams
{
protected:
	CString m_strPath;			// DateiPfad der GDatabase
	CString m_strDesc;			// KurzBezeichner
	CString m_strConnDesc;		// Beschreibung der Connection
	
	BOOL m_fIsOpened;
	BOOL m_fIsConnReadWrite;
	BOOL m_fIsSourceReadWrite;

	WTRiASConnection m_Conn;
	DIRTYFLAG m_rgIsDirty;

	DWORD m_dwPosBmp;

public:
		CManageDataServerItem() : 
			m_rgIsDirty(DIRTYFLAG_NoChange), m_dwPosBmp(IMG_GENERAL),
			m_fIsOpened(FALSE), m_fIsConnReadWrite(TRUE), m_fIsSourceReadWrite(TRUE)
		{
		}
		~CManageDataServerItem() {}

	CManageDataServerItem &operator= (const CManageDataServerItem &rhs)
	{
		*(CConnectParams *)this = (CConnectParams &)rhs;
		m_strPath = rhs.m_strPath;
		m_strDesc = rhs.m_strDesc;
		m_strConnDesc = rhs.m_strConnDesc;
		m_fIsOpened = rhs.m_fIsOpened;
		m_fIsConnReadWrite = rhs.m_fIsConnReadWrite;
		m_fIsSourceReadWrite = rhs.m_fIsSourceReadWrite;
		m_Conn = rhs.m_Conn;
		return *this;
	}

// inline Zugriff
	BOOL IsDriverReadWrite() { return m_fIsReadWrite; }
	CString GetName() { return m_strShortName; }

	BOOL IsOpened() { return m_fIsOpened; }
	BOOL IsConnReadWrite() { return m_fIsConnReadWrite; }
	BOOL IsSourceReadWrite() { return m_fIsSourceReadWrite; }

	CString GetDesc() { return m_strDesc; }
	CString GetConnDesc() { return m_strConnDesc; }
	CString GetPath() { return m_strPath; }
	CString GetStatusText()
	{
	CString ret;

		if (IsOpened()) {
			ATLTRY(ret.LoadString (IsConnReadWrite() ? IDS_READWRITE : IDS_READONLY));
		} else {
			ATLTRY(ret.LoadString (IDS_CLOSED));
		}
		return ret;
	}
	ITRiASConnection *GetConnection (BOOL fAddRef = FALSE) 
	{
		if (fAddRef) m_Conn -> AddRef();
		return m_Conn;
	}
	void SetPath(LPCSTR pcPath) { ATLTRY(m_strPath = pcPath); }
	void SetDesc(LPCSTR pcDesc) { ATLTRY(m_strDesc = pcDesc); }
	void SetConnDesc(LPCSTR pcDesc) { ATLTRY(m_strConnDesc = pcDesc); }

	void SetIsOpened(BOOL fIsOpened) { m_fIsOpened = fIsOpened; }
	void SetConnIsReadWrite(BOOL fIsRW) { m_fIsConnReadWrite = fIsRW; }
	void SetSourceIsReadWrite(BOOL fIsRW) { m_fIsSourceReadWrite = fIsRW; }

	void SetConnection (ITRiASConnection *pIConn) { m_Conn = pIConn; }

	void RemoveDirty (DIRTYFLAG rgDirty) { m_rgIsDirty = DIRTYFLAG(m_rgIsDirty & ~rgDirty); }
	void AddDirty (DIRTYFLAG rgDirty) { m_rgIsDirty = DIRTYFLAG(m_rgIsDirty | rgDirty); }
	DIRTYFLAG IsDirty() { return m_rgIsDirty; }

	void SetPosBmp (DWORD dwPosBmp) { m_dwPosBmp = dwPosBmp; }
	DWORD GetPosBmp() { return (m_rgIsDirty & DIRTYFLAG_ConnectParamsInitialized) ? m_dwPosBmp : IMG_GENERAL; }
};


/////////////////////////////////////////////////////////////////////////////
// ManageDataServerList window

class CManageDataServerList : 
	public CListCtrlEx
{
// Construction
public:
	CManageDataServerList();

// Attributes
public:

// Operations
public:
	BOOL InitListCrtl (void);		// Initialisierung
	HRESULT AddItemToTree (CManageDataServerItem *pItem);		// Item hinzufügen

	BOOL FillStringList (CStringList &rLst, CString &rStr, BOOL fIsReadWrite);
	int DecodeStatus (CString &rStr, BOOL fIsReadWrite);

	BOOL SetShortName (int iIndex, LPCSTR pcName);

	BOOL SetFileName (int iIndex, LPCSTR pcName);
	CString GetFileName (int iIndex);

	BOOL FillConnectFilterList (CStringList &rLst, CString &rStr);
	int DecodeConnectFilter(CString &rStr);
	BOOL SetConnectFilter (int iIndex, LPCSTR pcName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManageDataServerList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CManageDataServerList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CManageDataServerList)
	afx_msg void OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	CImageList m_ilImages;
	LONG m_lCnt;					// Zähler der Einträge
};


/////////////////////////////////////////////////////////////////////////////
// CManageConnections dialog

class CManageConnections : 
	public CDialog
{
// Construction
public:
	CManageConnections(CWnd* pParent = NULL);   // standard constructor
	~CManageConnections() 
	{
		DELETE_OBJ(m_pPopup);
	}

	BOOL IsValid() { return m_fIsValid; }
	void RefreshAfterDragAndDrop();

// Dialog Data
//	CDropMenuButton	m_FunctionMenu;
	//{{AFX_DATA(CManageConnections)
	enum { IDD = IDD_MANAGE_CONNECTIONS };
	CButton	m_pbOK;
	CButton	m_pbCancel;
	CManageDataServerList m_lvConnections;
	CCoolBtn m_pbActions;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManageConnections)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL InitConnectionList (int iItem = -1);
	BOOL FillListWithActualConnections();		// Liste füllen
	HRESULT LoadConnectParams (ITRiASConnection *pIConn, CManageDataServerItem *pItem);
	void AdjustButtons(int iItem);

	CString EnsureUniqueConnectionName (int iActItem, LPCSTR pcOrigName, LPCSTR pcFileName, BOOL *pfCorrected);
	HRESULT FindConnection (int iActItem, LPCSTR pcToSearch);
	BOOL IsConnectionDeleted (ITRiASConnection *pIConn);

public:
	BOOL IsConnectionDeleted (BSTR bstrName);

protected:
	// Generated message map functions
	//{{AFX_MSG(CManageConnections)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnItemChangedConnections(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndLabelEditConnections(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnPreparePopupMenu(WPARAM, LPARAM);
	afx_msg LRESULT OnDestroyPopupMenu(WPARAM, LPARAM);
	afx_msg void OnActions();
	afx_msg void OnRclickConnections(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg LRESULT OnShowInPlaceEdit (WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

// CoolButton verwalten
	void InitCoolButton(BOOL fMenuBtn);
	BOOL InitPopupMenu (CPopUpMenu *pPopup, BOOL fMenuBtn = FALSE);
	LRESULT ExecuteCommand (UINT uiCmd);

// Commands vom Button
	void OnRemoveConnection(int nItem);
	void OnAddConnection(int nItem);
	void OnEditName(int nItem);
	void OnEditDescription(int nItem);
	void OnOpenDataSource(int nItem);
	void OnCloseDataSource(int nItem);
	void OnToggleMode(int nItem);
	void OnSaveConnection(int nItem);
	void OnSaveAsConnection(int nItem);
	void OnSaveCopyAsConnection(int nItem);

private:
	typedef list<WTRiASConnection> CConnectionList;
	CConnectionList m_Deleted;
	CConnectionList m_Added;
	BOOL m_fIsValid;

// CoolButton verwalten
	UINT m_uiDefault;
	CPopUpMenu *m_pPopup;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANAGECONNECTIONS_H__AFEAD084_7006_11D1_9749_00A024D6F582__INCLUDED_)
