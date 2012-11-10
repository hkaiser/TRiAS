#ifndef _RUNEBOBS_H
#define _RUNEBOBS_H
#endif //_RUNEBOBS_H

DefineEnumerator2(LONG, IID_IEnumLONG);

class CRunBreakPoint;

class NEnumlong : public NEnumLONG
{
public:
	void ClearItem (long &item) { 
		list<long>::iterator it = m_data.begin();
			while (*it != item && it != m_data.end()) it++;
			m_data.erase (it); 
	}
};

class CRunningObject : 	
	public CComObjectRoot,
	public CProjectScript2,
	public IRunningObject
{
public:
	CRunningObject();
	virtual ~CRunningObject();

	BEGIN_COM_MAP(CRunningObject)
		COM_INTERFACE_ENTRY(IRunningObject)
		COM_INTERFACE_ENTRY(IObjManHelper)
		COM_INTERFACE_ENTRY(IPersist)
		COM_INTERFACE_ENTRY(IBSProperty)
		COM_INTERFACE_ENTRY(ITreeItem)
	END_COM_MAP()

//////////////////////////////////////////////////////////////////////
// *** IRunningObject methods
	STDMETHOD(LinkScript)		(void);
	STDMETHOD(CanAddString)		(void) { return S_FALSE; }
	STDMETHOD(CreateScript)		(CebInstance *pInst, ebHCODE hCode);
	STDMETHOD(RunEntry)			(LPCSTR pEntry, int iNumParams, BSPARAM *pPars, BOOL fBreak, INT_PTR hPrCtx, INT_PTR hInst);
	STDMETHOD(RunScript)		(void);
	STDMETHOD(EndThreads)		(void);
	STDMETHOD(EnumEntries)		(LPSTR lpstr, UINT uiLen, ebBOOL *pfNext);
	STDMETHOD(SetAutoStart)		(DWORD dw);
	STDMETHOD(SetExtension)		(BOOL f) { m_fExtension = f; return S_OK; }
	STDMETHOD(IsExtension)		(void) { return m_fExtension ? S_OK : S_FALSE; }
	STDMETHOD(GetAutoStart)		(DWORD *p) { *p = m_dwAuto; return S_OK; }
	STDMETHOD_(void, SetManagement)	(IObjectManagement*, IStreamInfo*, REFIID riid, LPCSTR lpc);

//////////////////////////////////////////////////////////////////////
// *** IObjManHelper
	STDMETHOD(Delete)			(void);

//////////////////////////////////////////////////////////////////////
// *** IBSProperty
	STDMETHOD(SetScript)		(CebScript *pScript);
	STDMETHOD(GetScript)		(CebScript **ppScript);
	STDMETHOD(SetThread)		(CebThread *);
	STDMETHOD(GetThread)		(CebThread **);

protected:
	CebScript		*	m_pScript;
	ebHENUM				m_hEnum;
	DWORD				m_dwAuto; 
	BOOL				m_fExtension; 
	CRunBreakPoint *	m_pSuspendDeb;
	NEnumlong			m_EnumRunningThreads;
	BOOL				m_fInterrupt;

	HRESULT SetEntryInfo (CebEntryInfo & EI, LPCSTR pEntry, int iNumParams, BSPARAM *pPars);
	HRESULT UnLoad (void);
	HRESULT Load (void);
	HRESULT Main (void);
	HRESULT IsThreadRunning(void);
	HRESULT EndThreadRunning(void);
	HRESULT OutputRunningThreads (short iCnt);
	HRESULT MessageInterrupt (LPCSTR lpcstrEntry);
	HRESULT GetScript(LPCSTR lpcstrScriptName, REFIID riid, BOOL fCreateTemp);
	HRESULT GetProperty (LPCSTR lpcstr, LPSTR *ppcMacroText, ebHCODE *phCode, LPSTR **lplplpstr, UINT & uiCnt);
	HRESULT RunThread(CebThread & Thread, LPCSTR lpcstrEntry);
	HRESULT OnDemandDebugger (LPCSTR lpcstr, CRunBreakPoint **ppSuspendDeb);
	virtual void SetRuntimeErrorProc(CebThread & Thread);
	HRESULT DeleteThread(CebThread *pCompareThread);
};

class CRunningObjectFile : public CRunningObject
{
public:
	CRunningObjectFile()  : CRunningObject(){ return; }
	virtual ~CRunningObjectFile() { return; }

	STDMETHOD(CanAddString)	(void) { return S_OK; }
	STDMETHOD(SetAutoStart)	(DWORD dw);
	STDMETHOD(Delete)		(void);
	virtual void SetRuntimeErrorProc(CebThread & Thread);
};
class CRunningFilterObject : public CRunningObject
{
	//////////////////////////////////////////////////////////////////////
	// *** IObjManHelper
	STDMETHOD(New)		(LPSTR *ppcMacroText);
	STDMETHOD(Delete)	(void);	
	STDMETHOD(Save)		(LPSTR pText, ebHCODE hCode, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag);
	virtual void SetRuntimeErrorProc(CebThread & Thread);
};


class CRunningObjectsHelper
{
public:
	// Construction/Destruction
	CRunningObjectsHelper(CebInstance *pInst);
	virtual ~CRunningObjectsHelper();

	static CRunningObjectsHelper* CreateRunningObjectsHelper(CebInstance *pInst);

	CRunScripts	*	GetRunningScripts (void);
	CRelScripts *	GetRelScripts (void);

	void	ResetManagement(void);
	HRESULT InitLinkAndStorage(IObjectManagement *pIOM, IStreamInfo *pISI);

	HRESULT SwitchRelated (void);
	HRESULT AddRelated (LPCSTR lpcstrScriptName);
	HRESULT	DeleteRelated (LPCSTR lpcstrScriptName);
	HRESULT RunScript (LPCSTR lpcstrMacroName, int fAutoStart, REFIID riid, BOOL fCreateTemp);
	HRESULT	LinkScript (LPCSTR lpcstrMacroName, ebHCODE hCode, IObjectManagement *pIOM);
	HRESULT StopScript (LPCSTR lpcstrMacroName);
	HRESULT SetAutoStart (LPCSTR lpcstrMacroName, DWORD dw);
	HRESULT GetAutoStart (LPCSTR lpcstrMacroName, DWORD *pdw);
	HRESULT CanAddString (LPCSTR lpcstrMacroName);
	HRESULT StopAllScripts (void);
	HRESULT	RunEntry (LPCSTR lpcstrMacroName, LPCSTR pEntry, int iNumParams, BSPARAM *pPars, BOOL fPreBreak, INT_PTR hPrCtx = NULL, INT_PTR hInst = NULL);
	HRESULT RunEntry (LPCSTR pEntry, LPCSTR lpcstr, ebHCODE hCode, int iNumParams, BSPARAM *pPars, BOOL fPreBreak, LPCSTR pcMacroName = NULL, INT_PTR hPrCtx = NULL, INT_PTR hInst = NULL);
	HRESULT RunKeptEntry (LPCSTR pEntry, int iNumParams, BSPARAM *pPars);
	HRESULT	IsRunning (LPCSTR lpcstrMacroName) { return Find(lpcstrMacroName); }
	HRESULT FindNext (LPSTR lpstrScriptName, short iLen, IRunningObject **);
	HRESULT Delete (LPCSTR lpcstr);
	BOOL	GetOpenProject (void);
	HRESULT	MessageNoCode(LPCSTR lpcstrText, ebHCODE *phCode, LPCSTR);
	HRESULT EntryExists (LPCSTR pEntry, int iNumParams, BSPARAM *pPars);
	
private:
	BOOL FInit(void);
	void ResetContainer(void);

	CebInstance *		m_pInst; 
	IObjectManagement *	m_pOM; 
	IStreamInfo *		m_pISI;
	CRelScripts		*	m_pRelScripts;
	CRunScripts		*	m_pRunningScripts;
	BOOL				m_fFireEventIsRun;

	HRESULT CreateObject(REFCLSID rClsid, IRunningObject **ppIR);

	HRESULT Add		(IRunningObject *, LPCSTR lpcstrMacroName);
	HRESULT Find	(LPCSTR lpcstrScriptName, IRunningObject **ppIRO = NULL);

	HRESULT UnLoad	(LPCSTR lpcstrMacroName);

	HRESULT Compile		(ebCOMPILESTRUCT & CompileStruct, LPCSTR lpText);
	HRESULT SetHomeDir	(LPCSTR lpcstr);
};

