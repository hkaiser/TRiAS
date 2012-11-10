// Interfacedeklaration für Schnittstelle zu BScript-Erweiterung --------------
// File: BSCREXT.HXX

#if !defined(_BSCREXT_HXX)
#define _BSCREXT_HXX

// Ein ErweiterungsModule -----------------------------------------------------
class CExtendModule : public string {
public:
		CExtendModule (LPCTSTR pModule) : string (pModule) {}
		~CExtendModule (void) {}

	void GetModule (LPTSTR pModule) { if (pModule) strcpy (pModule, c_str()); }
};


// Liste, die einzubindende ModulNamen enthält --------------------------------
class CExtendModules : public CListContainer {
private:
	CRing m_navModules;

protected:
	void UserDelete (void *pObj);

public:
		CExtendModules (void);
		~CExtendModules (void);

// AbfrageFunktionen
	void Reset (void);
	bool GetNextModule (LPTSTR pModule);

// Module hinzufügen
	bool AddModule (LPCTSTR pModule);
};
DeclareLock (CExtendModules, CExtendModule);


// Implementation des Interfaces zur BScriptErweiterung -----------------------
class CMacroScriptExtension;

class CExtendBScript : public IExtendBScript {
private:
	DWORD m_dwRefCnt;
	CExtendModules m_Modules;
	CMacroScriptExtension *m_pIUnk;

protected:
		CExtendBScript (CMacroScriptExtension *pIUnk);
	
	bool FInit (void);

public:
// nur dynamisch über 'CreateInstance' zu generieren
static CExtendBScript *CreateInstance (CMacroScriptExtension *pIUnk);

		~CExtendBScript (void);

// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** IExtendBScript methods
	STDMETHOD(RegisterExtModule)(THIS_ LPCSTR pModule);
	STDMETHOD(FireEvent)(THIS_ LPCSTR pEntry, int iNumParams, BSPARAM *pPars);

	STDMETHOD(RunText)(THIS_ LPCSTR pText, LPCSTR pEntry, int iNumParams, BSPARAM *pPars);
	STDMETHOD(RunCode)(THIS_ HINSTANCE hInst, int iResID, LPCSTR pEntry, int iNumParams, BSPARAM *pPars);

// sonstige Member
	void Reset (void) { m_Modules.Reset(); }
	bool GetNextModule (LPTSTR pModule) 
		{ return m_Modules.GetNextModule (pModule); }
	ULONG Count (void) { return m_Modules.Count(); }
};

// Routine, über die die Module enumeriert werden -----------------------------
extern "C" ebBOOL ebCALLBACK ebGetNextModule (ebLPSTR lpFileName, long lParam);

#endif // _BSCREXT_HXX


