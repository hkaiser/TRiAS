///////////////////////////////////////////////////////////////////////////
// CopyFileApp.h

#if !defined(_COPYFILEAPP_H__93A86B97_546C_11D1_96FC_00A024D6F582__INCLUDED_)
#define _COPYFILEAPP_H__93A86B97_546C_11D1_96FC_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
// Diese Applikation wird von CThisApp repräsentiert

class CThisApp 
{
private:
	HINSTANCE m_hInstance;	

// Kommandozeile auswerten
	bool m_fNoLogo;			// Logo ausgeben
	int m_iFirst;
	int m_iMax;

	char m_iAppendChar;
	char *m_pOptArg;
	int m_iOptIndex;
	int m_iOptError;
	int m_iInOpt;

	string m_strInFile;

protected:
	int PrintUsage (void);
	string LoadStringRes (UINT uiID);
	int GetNextOption (int argc, char *argv[], char *optstring);

public:
	CThisApp (void);
	~CThisApp (void) {}

// properties
	HINSTANCE Handle(void) { return m_hInstance; }
	int OptIndex (void) { return m_iOptIndex; }
	
	bool NoLogo (void) { return m_fNoLogo; }
	int GetMaxCount() { return m_iMax; }
	int GetFirstCount() { return m_iFirst; }
	char GetAppendChar() { return m_iAppendChar; }

	bool doWork(LPCSTR pcInput);

// methods
	bool PrintStartupLogo (void);
	int AnalyzeCmdLine (int iArgc, char *cbArgv[]);
};

#endif // !defined(_COPYFILEAPP_H__93A86B97_546C_11D1_96FC_00A024D6F582__INCLUDED_)
