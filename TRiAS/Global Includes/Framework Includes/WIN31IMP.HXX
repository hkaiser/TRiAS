// ImplementorKlassen für CommonDialog WrapperKlassen -------------------------
// File: WIN31IMP.HXX

#if !defined(_WIN31IMP_HXX)
#define _WIN31IMP_HXX

extern "C" {
#if !defined(COMMONDLGHOOKFCN)
#define COMMONDLGHOOKFCN

	typedef UINT (*HOOKFCN)(HWND, UINT, WPARAM, LPARAM);
	typedef UINT (PASCAL *HOOKFCNCALLBACK)(HWND, UINT, WPARAM, LPARAM);
#endif
}

class Color;    

class CStdDialog_Win31 {
public:
		CStdDialog_Win31();
		~CStdDialog_Win31();
public:
	virtual bool Show (void);
};

class CStdColorDlg_Win31 : public  CStdDialog_Win31
{
protected:
	HWND hwnd;
	unsigned long CustomColors[16];
	unsigned long DefColor;
	long flags;

 		CStdColorDlg_Win31 (HWND hw, Color *c);
public:
	void GetColor (Color *);
	bool Show (void);

		~CStdColorDlg_Win31 (void);
};


class CStdFileDlg_Win31 : public  CStdDialog_Win31
{
protected:
	OPENFILENAME *m_pOfn;	// OPENFILENAME-Struktur
        short m_isOpen;		// OpenFileDlg oder SaveAsDlg ?
	bool m_iResult;		// Resultat aus COMMDLG.DLL

  		CStdFileDlg_Win31 (HWND hWnd, char *c);

public:
	void GetFileName (char *pBuff, int iLen);
	int  GetFileNameLen (void);
	bool Show (void);

	long Flags (void);
	void SetFlags (long newFlags);
	void AddFlags (long newFlags);
	void SetHookFcn (HOOKFCN pF);
	void SetTemplate (HGLOBAL hDlgRes);
	void SetTemplate (HINSTANCE hInst, const char *pRcs);
	void SetCustomData (DWORD lData);
	void SetCaption (const char *);
	void SetFileName (const char *pName);
	void SetInitialDir (const char *pPath);

	bool Result (void) { return m_iResult; }
		
	void SetFilterIndex (int iFIndex);
	int GetFilterIndex (void);

		~CStdFileDlg_Win31 (void);
};

class OpenDlg_Win31 : public CStdFileDlg_Win31 {
public:
		OpenDlg_Win31 (HWND, char *);
		~OpenDlg_Win31 (void);
};

class SaveAsDlg_Win31 : public CStdFileDlg_Win31 {
public:
		SaveAsDlg_Win31 (HWND, char *);
		~SaveAsDlg_Win31 (void);
};

#endif	// _WIN31IMP_HXX


