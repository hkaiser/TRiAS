#ifndef _RUNSCORG_H
#define _RUNSCORG_H

class CRunScriptsOrg
{
	map< os_string, ebHSCRIPT, less < os_string > >					m_mapScripts;
	typedef map< os_string, ebHSCRIPT, less < os_string > >			script_map;

	multimap< os_string, ebHSCRIPT, less < os_string > >			m_mapThreads;
	typedef multimap< os_string, ebHSCRIPT, less < os_string > >	thread_mmap;
	
	script_map::iterator											m_itS;
	thread_mmap::iterator											m_it;
	
	ebHSCRIPT	m_hScriptAutoStart;

	HRESULT		OutputRunningThreads(short iCnt);
	HRESULT		IsThreadRunning		(ebHSCRIPT hScript);

	HRESULT		DeleteAll	(void);
	HRESULT		DeleteEntry	(ebHSCRIPT hScript);
	HRESULT		DeleteScript(ebHSCRIPT hScript);
	HRESULT		AddEntry (ebHSCRIPT hScript, LPCSTR pcThreadEntry);
	HRESULT		AddScript(ebHSCRIPT hScript, LPCSTR pcScriptName);

	void		ToUpper(LPSTR lpstr);

public:
	CRunScriptsOrg(void);
	~CRunScriptsOrg();

	void SetAutoStart	(ebHSCRIPT hScript) { ASSERT(hScript); m_hScriptAutoStart = hScript; }
	ebHSCRIPT GetAutoStart	(void) { return m_hScriptAutoStart; }
	
	HRESULT		Delete	(ebHSCRIPT hScript);
	HRESULT		Add		(ebHSCRIPT hScript, LPCSTR pcScriptName);
	HRESULT		FindNext(ebHSCRIPT *phScript, LPCSTR pcThreadEntry, bool fFirst);
	HRESULT		FindNext(LPSTR pcScriptName, short iLen, ebHSCRIPT *phScript);
	HRESULT		Find	(LPCSTR pcScriptName, ebHSCRIPT *phScript);
	HRESULT		EndThreadRunning(ebHSCRIPT hScript);
};

#endif // _RUNSCORG_H