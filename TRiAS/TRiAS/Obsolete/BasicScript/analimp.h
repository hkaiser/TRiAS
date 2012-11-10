#ifndef _ANALIMP_H
#define _ANALIMP_H

typedef class CImpIAnalyse *LPIMPIANALYSE;
class CMacroOrg;

class CImpIAnalyse : public IAnalyse
{
private:	
	HRESULT FInit();		

protected:
    ULONG           m_cRef;      //Interface reference count
    LPUNKNOWN       m_pUnkOuter; //For delegation      
    CMacroOrg		*m_pMacroOrg;

public:
	static CImpIAnalyse* Create(LPUNKNOWN pUnkOuter, CMacroOrg *pMacroOrg);
	
    CImpIAnalyse(LPUNKNOWN pUnkOuter, CMacroOrg* pMacroOrg);
    ~CImpIAnalyse();

	/* IUnknown methods */
	STDMETHOD(QueryInterface)(REFIID riid, void FAR* FAR* ppv);
	STDMETHOD_(unsigned long, AddRef)(void);
    STDMETHOD_(unsigned long, Release)(void);

    /* IAnalyse methods */
	STDMETHOD(GetMenuStructure)(HMENU hMenu);
};

#endif // _ANALIMP_H                   


