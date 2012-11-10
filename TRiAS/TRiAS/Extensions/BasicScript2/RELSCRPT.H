#ifndef _RELSCRPT_H
#define _RELSCRPT_H

struct IObjectManagement;
struct IStreamInfo;	
class CRunScripts;

class CRelScripts 
{
public:
	CRelScripts();
	virtual ~CRelScripts();
	// Für den Zugriff von aussen, wenn Projekt entladen wird
	bool SetStorageManagement(IObjectManagement	*pIObjMan, IStreamInfo *pIStrI);
	void ResetStorageManagement(void);

	///////////////////////////////////
	// Bekanntmachung von Zusatzmodulen, 
	HRESULT Add			(LPCSTR lpcstrSuperItem);// Einfügen eines Superitems 
	HRESULT Delete		(LPCSTR lpcstrSuperItem);
	// Zugriff von aussen Rückruffunktion
	HRESULT GetItem		(LPCSTR lpcstrSuperItem, ebHSCRIPT hScript,	LPSTR lpstrName, UINT uiLen, LPSTR *lplp);// SubItemText geben lassen
	HRESULT GetItem		(LPCSTR lpcstrSuperItem, LPCSTR lpcstrEntry, LPSTR lpstrSubItem, UINT uiLen, ebHSCRIPT *phScript);// SubItemScript geben lassen	
private:
	// Aufbewahrung der untergeordneten Scripts, "long" eigentlich RunningScriptsOrg
	map< os_string, long, less < os_string > >			m_mapRelatedScripts;

	typedef map< os_string, long, less < os_string> >	MapRelScripts;
	typedef map< os_string, long, less < os_string> >::iterator MapRelScriptsIt;

	IObjectManagement	*m_pIObjectManagement;
	IStreamInfo			*m_pIStreamInfo;

	void DeleteRunningScriptsOrg(void);
	void ReleaseManagements(void);

	HRESULT CreateObject(REFIID riid, IRunningObject **ppIR);
	HRESULT AddScript	(LPCSTR lpcstrSuperItem);// Einfügen eines Superitems 
	HRESULT DeleteItem	(LPCSTR lpcstrSuperItem, LPCSTR lpcstrSubItem);
	HRESULT SetItems	(LPCSTR lpcstrSuper);
	HRESULT SetItem		(ebHCODE hCode, LPCSTR lpcstrSuperItem, LPCSTR lpcstrName);// SubItem geben lassen
	HRESULT GetScript	(LPCSTR lpcstrSuperItem, LPCSTR lpcstrEntry, ebHSCRIPT *);
	HRESULT GetName		(LPCSTR lpcstrSuperItem, ebHSCRIPT, LPSTR lpstrSubItem, UINT uiLen);
	HRESULT GetText		(LPCSTR lpcstrSuperItem, ebHSCRIPT, LPSTR *lplpstr);// liefert den Text zum Script
	HRESULT	CreateScript		(CRunScripts *pRunScriptsOrg, ebHCODE hCode, LPCSTR lpcstrSubItem, IRunningObject **);
	HRESULT FindScriptHandle	(CRunScripts *pRunScriptsOrg, LPCSTR lpcstrEntry, ebHSCRIPT *);
	HRESULT FindScriptName		(CRunScripts *pRunScriptsOrg, ebHSCRIPT, LPSTR lpstrSubItem, UINT uiLen);
	HRESULT FindScriptText		(CRunScripts *pRunScriptsOrg, ebHSCRIPT, LPSTR *lplpstr);
	HRESULT IsLoad		(LPCSTR lpcstrScriptName);

	bool	FoundMoreDefinitions(LPCSTR lpcstrEntry);
};

#endif //_RELSCRPT_H
