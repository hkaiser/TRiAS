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

#endif // _BSCREXT_HXX
