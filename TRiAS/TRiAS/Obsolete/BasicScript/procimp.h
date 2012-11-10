#ifndef _PROCIMP_H
#define _PROCIMP_H

typedef class CImpIProcess *LPIMPIPROCESS;
class CMacroOrg;

class CImpIProcess : public IProcess
{
private:	
	HRESULT		FInit();		

	HRESULT		Run(void);
	LPIMPICOMMANDS	GetCommands(void);

protected:
    ULONG           m_cRef;      //Interface reference count
    LPUNKNOWN       m_pUnkOuter; //For delegation      
    CMacroOrg 		*m_pMacroOrg;

public:
	static CImpIProcess* Create(LPUNKNOWN pUnkOuter, CMacroOrg *pMacroOrg);
	
    CImpIProcess(LPUNKNOWN pUnkOuter, CMacroOrg* pMacroOrg);
    ~CImpIProcess();

	STDMETHOD_(HRESULT, MenuSelect) (void);
	STDMETHOD_(HRESULT, MenuInit) (void);
	STDMETHOD_(HRESULT, MenuCommand) (UINT uiID) ;
	
	STDMETHOD_(HRESULT, Notification) (void);
	
	STDMETHOD_(HRESULT, WindowsNotification) (void);

	/* IUnknown methods */
	STDMETHOD(QueryInterface)(REFIID riid, void FAR* FAR* ppv);
	STDMETHOD_(unsigned long, AddRef)(void);
    STDMETHOD_(unsigned long, Release)(void);
};

#endif // _PROCIMP_H                   


