/*
 * enhstbar.h
 * Enhanced status bar
 * (c) Julian Smart, December 1996
 */

#ifndef ENHSTBARH
#define ENHSTBARH

#define IDC_BUTTON_LEFTARROW	2001
#define IDC_BUTTON_RIGHTARROW	2002
#define IDC_BUTTON_INFO			2003
#define IDC_PROGRESS_STATUS		2004

#define ENHSBAR_SCROLL_ARROWS	1
#define ENHSBAR_SCROLL_INFO		2
#define ENHSBAR_PROGRESS_BAR	4

class CStatusBarMessage;
class CEnhStatusBar : public CStatusBar
{
public:
	CEnhStatusBar();
	~CEnhStatusBar();

	virtual int OnToolHitTest( CPoint point, TOOLINFO* pTI ) const;
	virtual CString GetToolText(int i);
protected:
	int statusFlags;

	// Status line controls
	int			controlHeight;
	int			controlSpacing;
	int			arrowControlWidth;
	int			infoControlWidth;
	CBitmapButton	leftButton;
	CBitmapButton	rightButton;
	CBitmapButton	infoButton;
	CProgressCtrl	progressControl;

	// The pane the message-scrolling controls
	// will appear in
	int			scrollControlPane;
	// The pane the progress control will
	// appear in
	int			progressControlPane;

	POSITION		currentMessagePosition;
	CObList			messages;

public:
	BOOL		Create(CWnd *wnd, int flags, int progressPane = -1,
		int scrollPane = -1);
	CBitmapButton&	GetLeftButton() { return leftButton; }
	CBitmapButton&	GetRightButton() { return rightButton; }
	CBitmapButton&	GetInfoButton() { return infoButton; }
	CProgressCtrl&	GetProgressControl() { return progressControl; }

	virtual BOOL AddStatusBarButtons();
	virtual BOOL AddProgressControl();
	virtual BOOL AddCustomControls();
	virtual void DestroyControls();
	virtual void DestroyCustomControls();
	virtual void PositionControls();
	virtual void PositionCustomControls();
	
	// Message manipulation functions
	inline CObList& GetMessages() { return messages; }
	virtual BOOL RemoveMessage(CStatusBarMessage *msg, BOOL update = TRUE);
	virtual BOOL AddMessage(CStatusBarMessage *msg, BOOL update = TRUE, BOOL showThis = TRUE);
	virtual BOOL AddMessage(const CString& msg, BOOL update = FALSE, BOOL showThis = TRUE);
	virtual BOOL ClearMessages(BOOL update = TRUE);
	virtual BOOL UpdateStatusBarButtons(BOOL disable = FALSE);
	virtual void OnMessageLeft();
	virtual void OnMessageRight();
	virtual void OnMessageInfo(CStatusBarMessage *msg);
	virtual BOOL CanClickLeft();
	virtual BOOL CanClickRight();
	virtual BOOL CanClickInfo();

	virtual void ShowProgress(int i, int range = -1);
	virtual void ShowMessage(const CString& msg, int i = 0);

	inline int GetStatusFlags() { return statusFlags; }

	//{{AFX_MSG(CEnhStatusBar)
	afx_msg void OnLeftArrow();
	afx_msg void OnRightArrow();
	afx_msg void OnInfo();
	afx_msg void OnUpdateLeftArrow(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRightArrow(CCmdUI* pCmdUI);
	afx_msg void OnUpdateInfo(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CStatusBarMessage: public CObject
{
private:
	CString message;
public:
	CStatusBarMessage(const CString& str):
	  message(str)
	  {
	  }
	inline CString& GetMessage() { return message; }
};

#endif
