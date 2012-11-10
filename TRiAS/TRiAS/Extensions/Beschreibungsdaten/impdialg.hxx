// ImportDialog für PBD-Import ------------------------------------------------
// File: IMPDIALG.HXX

#if !defined(_IMPDIALG_HXX)
#define _IMPDIALG_HXX

#include <ospace/std/list>

// OptionsAbfrage ermöglichen -------------------------------------------------
class CImportPBDDlg : 
	public COpenDialog 
{
private:
	bool m_fDelete;
	bool m_fKeep;
	bool m_fReject;
	bool m_fAllDataSources;
	HPROJECT m_hPr;
	list<HPROJECT> m_listPrj;
	int m_iAllDS;
	int m_iOldDS;

public:
		CImportPBDDlg (pWindow pW, LPCSTR pcTempl);
		~CImportPBDDlg (void) {}

	LRESULT OnWmInitDialog (HWND hDlg, HWND hDlgP);
	LRESULT OnWmCommand (HWND hDlg, WPARAM wParam, LPARAM lParam);
	LRESULT OnCdnTypeChange (HWND hDlg);
	LRESULT FillDataSources (HWND hDlg);

	bool DeleteExisting (void) { return m_fDelete; }
	bool KeepExisting (void) { return m_fDelete ? false : m_fKeep; }
	bool RejectUnused (void) { return m_fReject; }
	bool ImportToAllDataSources() { return m_fAllDataSources; }

	HPROJECT GetHandle() { return m_hPr; }
	list<HPROJECT> &GetHandles() { return m_listPrj; }

	bool GetFileNames (list<os_string> &rNames, LPCSTR pcBuffer, int iCurrLen);
};

#endif // _IMPDIALG_HXX
