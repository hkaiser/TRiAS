// StandardDialog zum oeffnen eines Projektes ---------------------------------
// File: OPENDB.HXX

#if !defined(_OPENDB_HXX)
#define _OPENDB_HXX

#if !defined(NOOPENDLG)

extern "C" {
	UINT EXPORTTRIAS CALLBACK OpenDBHookFcn (HWND, UINT, WPARAM, LPARAM);
#if !defined(WIN16)
	UINT EXPORTTRIAS APIENTRY OpenDB40HookFcn (HWND, UINT, WPARAM, LPARAM);
#endif
}

class CDBBaseDialog {
public:
		CDBBaseDialog (void) {}
		virtual ~CDBBaseDialog (void) {}

#if !defined(WIN16)
	virtual bool HandleNotifications (HWND hDlg, LPOFNOTIFY pofn);
#endif

friend UINT EXPORTTRIAS CALLBACK OpenDBHookFcn (HWND, UINT, WPARAM, LPARAM);
};

class CDBDialog : public CDBBaseDialog {
protected:
	char *m_pUser;		// eingegebener Nutzername
	char *m_pPasswd;	// eingegebenes PaßWord
	bool m_fForceUser;

	UINT m_iFileOKMessage;	// Message für OKButton

public:
		CDBDialog (bool fForceUser);
		~CDBDialog (void);

	char *GetUserName (char *pc = NULL, short = 0) const;	// liefert UserNamen
	char *GetPassWord (char *pc = NULL, short = 0) const;	// liefert Password

friend UINT EXPORTTRIAS CALLBACK OpenDBHookFcn (HWND, UINT, WPARAM, LPARAM);
};

class COpenDBDlg : public COpenDialog, public CDBDialog {
private:
	bool m_fIsComFile;	// aktuelle Selektion ist COM-Datei
			
public:
// Konstruktor (Initialisierung des Dialogfensters)
		COpenDBDlg (pWindow, LPCSTR pcTempl);
		~COpenDBDlg (void);

// Memberfunktionen
	char *GetFileSpec (char *pc = NULL, short iLen = 0)
		{ GetFileName (pc, iLen); return pc; }  // liefert FileNamen

	bool GetROMode (void) { return (bool)(Flags() & OFN_READONLY) != 0; }
	
	void SetComFile (bool fFlag) { m_fIsComFile = fFlag ? true : false; }
	bool IsComFile (void) { return m_fIsComFile; }

#if !defined(WIN16)
	bool HandleNotifications (HWND hDlg, LPOFNOTIFY pofn);
#endif

friend UINT EXPORTTRIAS CALLBACK OpenDBHookFcn (HWND, UINT, WPARAM, LPARAM);
};

class CNewDBDlg : public CSaveAsDialog, public CDBDialog {
public:
// Konstruktor (Initialisierung des Dialogfensters)
		CNewDBDlg (pWindow, LPCSTR pcTempl);
		~CNewDBDlg (void);

	char *GetFileSpec (char *pc = NULL, short iLen = 0)
		{ GetFileName (pc, iLen); return pc; }  // liefert FileNamen

// Memberfunktionen
#if !defined(WIN16)
	bool HandleNotifications (HWND hDlg, LPOFNOTIFY pofn);
#endif

friend UINT EXPORTTRIAS CALLBACK OpenDBHookFcn (HWND, UINT, WPARAM, LPARAM);
};

#if !defined(WIN16)
class CSaveAsDBDlg : public CSaveAsDialog, public CDBDialog {
public:
		CSaveAsDBDlg (pWindow pW, bool fSaveAsCopy, LPCSTR pcTempl);
		~CSaveAsDBDlg (void);

	char *GetFileSpec (char *pc = NULL, short iLen = 0)
		{ GetFileName (pc, iLen); return pc; }  // liefert FileNamen

friend UINT EXPORTTRIAS CALLBACK OpenDBHookFcn (HWND, UINT, WPARAM, LPARAM);
};
#endif // WIN16

#endif // NOOPENDLG

#endif // _OPENDB_HXX
