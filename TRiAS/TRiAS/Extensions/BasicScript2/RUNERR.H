#ifndef _RUNERR_H
#define _RUNERR_H

class CRunErr 
{
protected:
	CString		m_strName;
	CSplit*		m_pScriptDebugger;

	HRESULT EnableTriasWindow(BOOL fEnable);
	HWND	GetDebuggerWnd(void);

public:	
	CRunErr	(const CString & strName);
	virtual ~CRunErr(void);

	void	SetName(const CString & str) { m_strName = str; }
	virtual HRESULT OnDemandBreakpoint(CebScript *pScript, CebThread *pThread, IObjectManagement *pIOM, IStreamInfo *pISI) 
	{  return E_UNEXPECTED; };
	HRESULT CreateDebugger (UINT uiWMClose, BOOL fOpen, ebWORD wLineNr, IObjectManagement *pIOM, IStreamInfo *pISI);
};
class CRunBreakPoint : public CRunErr
{
public:	
	virtual ~CRunBreakPoint(void);
	CRunBreakPoint(const CString & strName) : CRunErr(strName) { return; } 

	virtual HRESULT OnDemandBreakpoint(CebScript *pScript, CebThread *pThread, IObjectManagement *pIOM, IStreamInfo *pISI);
};

#endif // _RUNERR_H