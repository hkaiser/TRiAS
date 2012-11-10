#ifndef _MACROORG_H
#define _MACROORG_H

class CMacroOrg : public IUnknown
{
	friend class CImpISave;
	friend class CImpIAnpassen;
	friend class CImpIAnalyse;
	friend class CImpIProcess;

protected:
	ULONG       m_cRef;      //Interface reference count
	LPUNKNOWN 	m_pIUnk;
	
private:
	HRESULT FInit(IScriptContainer *pISC);				

// other functions
	CImpICommands * GetCommands(void);
	UINT GetOffset(void) { return m_uiOffset; }

	LPIMPIPROCESS	m_pIProcess;
	LPIMPIANALYSE	m_pIAnalyse;  // alle aggregiert
	LPIMPIANPASSEN	m_pIAnpassen;
	LPIMPISAVE		m_pISave;
	LPIMPICOMMANDS	m_pICommands; // nicht aggregiert

	UINT			m_uiOffset;
	
public:
	static  CMacroOrg* Create (LPUNKNOWN pIUnk, UINT uiOffset, 
						   IScriptContainer *pISC);
		                               
	CMacroOrg (LPUNKNOWN pIUnk, UINT uiOffset);
	~CMacroOrg();

/* IUnknown methods */
	STDMETHOD(QueryInterface)(REFIID riid, void FAR* FAR* ppv);
	STDMETHOD_(unsigned long, AddRef)(void);
    STDMETHOD_(unsigned long, Release)(void);

};
                                 
#endif // _MACROORG_H

