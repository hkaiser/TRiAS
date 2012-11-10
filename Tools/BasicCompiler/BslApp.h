// Diese Applikation
// File BSLAPP.H

#if !defined(_BSLAPP_H)
#define _BSLAPP_H

///////////////////////////////////////////////////////////////////////////////
// Diese Applikation wird von CThisApp repräsentiert
typedef map<os_string, os_string, less<os_string> > CDefines;

class CThisApp {
private:
	HINSTANCE m_hInstance;	

// Kommandozeile auswerten
	bool m_fNoLogo;			// Logo ausgeben
	bool m_fCodeOnly;		// Code Only
	bool m_fVerbose;		// verbose

	char *m_pOptArg;
	int m_iOptIndex;
	int m_iOptError;
	int m_iInOpt;

	os_string m_strOutFile;
	os_string m_strIniFile;

// SymbolTable für MacroKonstanten
	CDefines m_Defines;

protected:
	int PrintUsage (void);
	os_string LoadStringRes (UINT uiID);
	int GetNextOption (int argc, char *argv[], char *optstring);
	int WriteCodeAndText (int fh, char *pData, ebHCODE hCode);

	bool AddDefine (const char *pcDefine);
	bool RemoveDefine (const char *pcDefine);
	bool RemoveAllDefines (void);

public:
	CThisApp (void);
	~CThisApp (void) {}

// properties
	HINSTANCE Handle(void) { return m_hInstance; }
	int OptIndex (void) { return m_iOptIndex; }
	bool GetVerbose() { return m_fVerbose; }
	
	bool NoLogo (void) { return m_fNoLogo; }

// methods
	bool PrintStartupLogo (void);
	int AnalyzeCmdLine (int iArgc, char *cbArgv[]);
	int CompileAndSave (CebInstance &rInst, char *pInFile);
	os_string GenIniPath (void);
};

#endif // _BSLAPP_H
