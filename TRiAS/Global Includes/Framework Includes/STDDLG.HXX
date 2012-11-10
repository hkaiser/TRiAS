// CommonDialog Wrapperklassen ------------------------------------------------
// File: STDDLG.HXX

#if !defined(_CStdDLG_HXX)
#define _CStdDLG_HXX

#include <commonvu.hxx>

class _TF_ENTRY32 CStdDialog 
{
protected:
	void *implementor;
	
     		CStdDialog (void);
public:
	BOOL	Show (void);

	virtual	~CStdDialog (void);
};

extern "C" {
#if !defined(COMMONDLGHOOKFCN)
#define COMMONDLGHOOKFCN

	typedef UINT (*HOOKFCN)(HWND, UINT, WPARAM, LPARAM);
	typedef UINT (PASCAL *HOOKFCNCALLBACK)(HWND, UINT, WPARAM, LPARAM);
#endif
}


class _TF_ENTRY32 CStdFileDlg : public CStdDialog
{
protected:
 		CStdFileDlg (void);

public:
	void	GetFileName (char *, int length = -1); 
	int	GetFileNameLen (void); 	// filename length includes null terminator

	long Flags (void);
	void SetFlags (long lFlags);
	void AddFlags (long lFlags);
	void SetHookFcn (HOOKFCN pF);
	void SetTemplate (HGLOBAL hDlgRes);
	void SetTemplate (HINSTANCE hInst, const char *pRcs);
	void SetCustomData (DWORD lData);
	void SetCaption (const char *);
	void SetFileName (const char *pName);
	void SetInitialDir (const char *pPath);
	
	BOOL Result (void);		// liefert Result der Aktion

// FilterIndex in m_pOfn
	void SetFilterIndex (int iIndex = 1);
	int GetFilterIndex (void);	

		~CStdFileDlg (void);
};

class _TF_ENTRY32 COpenDialog : public CStdFileDlg
{
public:
		COpenDialog (pWindow Parent, char *FileSpec = "*.*");
		~COpenDialog (void);
};

class _TF_ENTRY32 CSaveAsDialog : public CStdFileDlg
{
public:
		CSaveAsDialog (pWindow Parent, char *SaveDirectory = "");
		~CSaveAsDialog (void);
};

class _TF_ENTRY32 CStdColorDlg : public CStdDialog
{
protected:
		CStdColorDlg (void) ;
public:
	Color GetColor (void);

		~CStdColorDlg (void);
};

// globale Funktionen ---------------------------------------------------------
// Fenster zentrieren
void _TF_ENTRY32 CentreWindow (HWND hWndParent, HWND hWnd);
void _TF_ENTRY32 CentreWindow (pWindow pWndParent, pWindow pWnd);

#endif
