#ifndef _RUNERR_H
#define _RUNERR_H

class CRunErr 
{
private:
	CString		m_strText;
	CString		m_strName;
	bool		m_fRunModal;
	bool		m_fRTError;

	CBScriptDebug	*m_pScriptDebugger;
	LPUNKNOWN		m_pOperateScripts;

	HRESULT EnableTriasWindow(bool fEnable);
	HWND	GetDebuggerWnd(void);
	HRESULT CreateDebugger (void);

public:	
		CRunErr	(LPUNKNOWN pOp, LPCSTR pT, const CString & strName);
		~CRunErr(void);

	HRESULT OnDemandBreakpoint(CebScript *pScript, CebThread *pThread);
	HRESULT OnDemandRuntimeError(ebWORD wLinNr);
};

#endif // _RUNERR_H