// Liste der zu ladenden Erweiterungsmodule
// File: EXTLIST.H

#if !defined(_EXTLIST_H)
#define _EXTLIST_H

class CExtList : 
	public list<os_string>
{
private:
	iterator m_it;
	bool m_fVerbose;
	os_string m_strCurDir;

public:
		CExtList (LPCSTR pcIniName, bool fVerbose = false);
		~CExtList (void) {}

	void Reset (void);
	bool GetNext (os_string &rStr);
	bool GetVerbose() { return m_fVerbose; }
	LPCSTR GetCurDir() { return m_strCurDir.c_str(); }
};

#endif // _EXTLIST_H
