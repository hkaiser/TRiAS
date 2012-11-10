#ifndef _RUNSCORG_H
#define _RUNSCORG_H

DefineSmartInterface(RunningObject);

class CRunScripts
{
	map< os_string, WRunningObject, less < os_string > >					m_mapScripts;
	typedef map< os_string, WRunningObject, less < os_string > >			script_map;

	multimap< os_string, WRunningObject, less < os_string > >			m_mapThreads;
	typedef multimap< os_string, WRunningObject, less < os_string > >	thread_mmap;
	
	script_map::iterator	m_itS;
	thread_mmap::iterator	m_it;
	
	HRESULT		DeleteAll		(void);
	HRESULT		DeleteScript	(LPCSTR);
	HRESULT		DeleteEntries	(IRunningObject*);
	HRESULT		AddEntry		(IRunningObject*, LPCSTR pcThreadEntry);
	HRESULT		AddScript		(IRunningObject*, LPCSTR pcScriptName);

public:
	CRunScripts(void);
	~CRunScripts();

	HRESULT		Delete			(LPCSTR pcScriptName);
	HRESULT		Add				(IRunningObject*, LPCSTR pcScriptName);
	HRESULT		AddEntries		(IRunningObject*);
	HRESULT		NextFromEntry	(LPCSTR pcThreadEntry, IRunningObject**);
	HRESULT		NextScriptName	(LPSTR pcScriptName, short iLen, IRunningObject**);
	HRESULT		Find			(LPCSTR pcScriptName, IRunningObject **ppIRO = NULL);
	void		Reset();
	HRESULT		ReleaseAllManagements (void);
};

#endif // _RUNSCORG_H