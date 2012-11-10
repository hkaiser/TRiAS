// debfdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDebFileDialog dialog

class CDebFileDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CDebFileDialog)

public:
	CDebFileDialog(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL,
		LPCSTR lpcstrCaption = NULL);

	bool GetLink(void) { return m_fCheckLink; }
	bool GetAutoStart(void) { return m_fAutoStart; }

protected:
	//{{AFX_MSG(CDebFileDialog)
	afx_msg void OnChecklink();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckauto();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool m_fOpen;
	bool m_fCheckLink;
	bool m_fAutoStart;
	CString m_strCaption;
};
