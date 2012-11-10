///////////////////////////////////////////////////////////////////////////////
// Classes 
class CToolTipButton : public CButton
{
private: 
	UINT m_uiResID;

public:
  CToolTipButton(UINT uiResID);
  BOOL Create ();

protected:
  //{{AFX_VIRTUAL(CToolTipButton)
	public:
  virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

  //{{AFX_MSG(CToolTipButton)
	//}}AFX_MSG

  DECLARE_MESSAGE_MAP()
  BOOL m_bFirstCall;
  BOOL m_fTTCreated;
  CToolTipCtrl m_ToolTip;
};
