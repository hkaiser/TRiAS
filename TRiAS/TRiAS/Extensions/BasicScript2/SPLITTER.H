#ifndef _SPLITTER_H
#define _SPLITTER_H

class CBSSplitterWnd : public CSplitterWnd
{
	DECLARE_DYNAMIC(CBSSplitterWnd)

// Construction
public:
	CBSSplitterWnd();
	virtual ~CBSSplitterWnd();
public:
	//{{AFX_MSG(CBSSplitterWnd)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
};

#endif // _SPLITTER_H
