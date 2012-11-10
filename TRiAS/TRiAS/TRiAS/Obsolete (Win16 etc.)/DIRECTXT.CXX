// Alter Typ einer Erweiterung ------------------------------------------------
// File: DIRECTXT.CXX

Extension::ExtensionType CDirectExtension :: isA (void) { return DirectExt; }
HDEX CDirectExtension :: hLib (void) { return m_pDLL ? (HDEX)m_pDLL -> hLib() : 0; }

CDirectExtension :: CDirectExtension (HWND hWnd, LPCSTR pExtName, 
				      LPCSTR pDLLName, int toLoad)
	       : Extension (hWnd, pExtName, pDLLName, toLoad)
{
	m_pDLL = NULL;
	if (toLoad != false) {
		m_pDLL = new DLLBind (pDLLName);
		if (m_pDLL == NULL) {
			db_error (EC_NOMEMORY, RC_ctExtension);
			m_hWnd = 0;
			m_pExtEntry = NULL;
			return;
		}
		m_pExtEntry = (DEXENTRY)m_pDLL -> GetProcAddress (ResString (IDS_EXTENTRYNAME, 20));
	} else {
	// Extension nicht anbinden
		m_pExtEntry = NULL;
	}
}

CDirectExtension :: CDirectExtension (HWND hWnd, LPCSTR pExtName, 
				      DLLBind *pDLL, LPCSTR pDLLName, 
				      bool toLoad)
	       : Extension (hWnd, pExtName, pDLLName, toLoad)
{
	m_pDLL = pDLL;		// übernimmt Pointer
	if (toLoad != false) 
		m_pExtEntry = (DEXENTRY)m_pDLL -> GetProcAddress (ResString (IDS_EXTENTRYNAME, 20));
	else 	// Extension nicht anbinden
		m_pExtEntry = NULL;
}

CDirectExtension :: CDirectExtension (CDirectExtension &rExt)
		  : Extension (rExt), 
		    m_pExtEntry (rExt.m_pExtEntry), m_pDLL (rExt.m_pDLL)
{
	rExt.m_pExtEntry = NULL;
	rExt.m_pDLL = NULL;
}

CDirectExtension :: ~CDirectExtension (void)
{
// wenn DLL noch geladen ist, dann UnLoad() abarbeiten
	if (m_pDLL) {
		if (hLib() != 0) 
			UnLoad();
		m_pExtEntry = NULL;
		delete m_pDLL;
		m_pDLL = NULL;
	}
}

HDEX CDirectExtension :: Load (TRIASLOADEX &DL) 
{
	if (m_pDLL == NULL) {
	// DLL noch nicht angebunden
		m_pDLL = new DLLBind (DLLName().c_str());
		if (m_pDLL == NULL) {
			db_error (EC_NOMEMORY, RC_LoadExtension);
			m_hWnd = 0;
			m_pExtEntry = NULL;
			return 0;
		}
	}
	if (!isLoaded() || m_pExtEntry == NULL) {
		SetLoaded (DL.m_iMode);
		m_pExtEntry = (DEXENTRY)m_pDLL -> GetProcAddress (ResString (IDS_EXTENTRYNAME, 20));
	}
	if (m_pExtEntry != NULL) {
		if ((*m_pExtEntry)(hWnd(), DEX_LOADEXTENSION, (WPARAM)hLib(), (LPARAM)&DL) != 0)
			return 0;
	} else
		return 0;

return hLib();
}

bool CDirectExtension :: UnLoad (void) 
{
	if (isLoaded() && m_pExtEntry != NULL) {
	bool fResult = (bool)(*m_pExtEntry)(hWnd(), DEX_UNLOADEXTENSION, 0, 0);
	
		SetLoaded (fResult ? 0 : isLoaded());
		return fResult;
	}

return false;
}

bool CDirectExtension :: Init (short iMode, ITriasXtensionSite *) 
{
	if (isLoaded() && m_pExtEntry != NULL) 
		return (*m_pExtEntry)(hWnd(), DEX_INITEXTENSION, iMode, 0) != 0;

return false;
}

LRESULT CDirectExtension :: Notify (HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	if (Entry()) return (*Entry())(hWnd, uiMsg, wParam, lParam);

return false;
}

bool CDirectExtension :: MenuInit (MenuInitEvt e, HWND hWndOR) 
{
	if (m_pExtEntry != NULL) {
	NakedEvt &ne = (NakedEvt &)(Event &)e;

		return (*m_pExtEntry)(hWnd(), DEX_MENUINIT, ne.wparam(), 
				MAKELONG(LOWORD(ne.lparam()), hWndOR)) != 0;
	}

return false;
}

bool CDirectExtension :: MenuSelect (MenuSelectEvt e, HWND) 
{
	if (m_pExtEntry != NULL) {
	NakedEvt &ne = (NakedEvt &)(Event &)e;

		return (*m_pExtEntry)(hWnd(), ne.wmsg(), 
			LOWORD(ne.wparam())-MenuOffset(), ne.lparam()) != 0;
	}

return false;
}

bool CDirectExtension :: MenuCommand (MenuCommandEvt e, HWND hORWnd) 
{
	if (m_pExtEntry != NULL) {
	NakedEvt &ne = (NakedEvt &)(Event &)e;

		return (*m_pExtEntry)(hWnd(), ne.wmsg(), 
			LOWORD(ne.wparam())-MenuOffset(), (LPARAM)(void *)hORWnd) != 0;
	}

return false;
}

int CDirectExtension :: GetCapability (WPARAM iCapType)
{
	if (m_pExtEntry != NULL) 
		return (int)(*m_pExtEntry)(hWnd(), DEX_CAPABILITIES, iCapType, 0L);

return false;
}	

bool CDirectExtension :: EnumObjPropFuncs (ENUMOBJPROPDATA *pEOPD, LONG)
{
	if (!GetCapability (DEXCAP_OBJPROPFUNCS)) return true;
	if (m_pExtEntry != NULL) 
		return (bool)(*m_pExtEntry)(hWnd(), DEX_ENUMEXTENSIONPROP, 0, (LPARAM)pEOPD);

return false;
}

char *CDirectExtension :: InvokePropFunc (INVOKEOBJPROPDATA *pIOPD)
{
	if (m_pExtEntry != NULL)
		return (char *)(m_pExtEntry)(hWnd(), DEX_INVOKEOBJPROPFUNC, 0, (LPARAM)pIOPD);

return NULL;
}


char *CDirectExtension :: GetHelpText (GETHELPTEXTDATA *pGHTD)
{
	if (m_pExtEntry != NULL)
		return (char *)(m_pExtEntry)(hWnd(), DEX_OBJPROPGETHELPTEXT, 0, (LPARAM)pGHTD);

return NULL;
}

