// @doc 
// @module ImageHelpDebug.cpp | Debughelper, um ZeilenNummern und Funktionsnamen zu finden

#include <Atl/ImageHelpDebug.h>

///////////////////////////////////////////////////////////////////////////////
//
CPEDebug::CPEDebug() :
	m_fIsInitialized(false), m_fTriedToInitialize(false),
	m_pSymbol(NULL)
{
}

CPEDebug::~CPEDebug()
{
	m_SymEngine.SymCleanup();
	DELETE_OBJ(m_pSymbol);
}

bool CPEDebug::Initialize()
{
	if (m_fIsInitialized)
		return true;				// nur einmal initialisieren
	else if (m_fTriedToInitialize)
		return false;				// schon mal versucht, jedoch fehlgeschlagen
	m_fTriedToInitialize = true;

// Since the largest symbol that the MS code generators can handle
//  is 256 that is all that is needed.
	ATLTRY(m_pSymbol = (IMAGEHLP_SYMBOL *)new BYTE [sizeof(IMAGEHLP_SYMBOL) + 256]);
	if (NULL == m_pSymbol) return false;

// SymbolEngine initialisieren
	if (m_SymEngine.SymInitialize (GetCurrentProcess(), NULL, TRUE)) {
    //  Set the symbol engine to load line information.  This must be
    //  because the symbol engine does not load source-lines by default.
    //  I also turn on the OMAP lookups so that the super-special OMAP
    //  moved blocks will get looked at as well.  Trust me, don't ask.
	    SymSetOptions (SymGetOptions() | SYMOPT_LOAD_LINES | SYMOPT_OMAP_FIND_NEAREST);
		m_fIsInitialized = true;
		return true;
	}
	return false;
}

const TCHAR g_cbNil[] = TEXT("");

bool CPEDebug::DumpDebugInfo (
	const BYTE* pCaller, CString &rModule, CString &rFile, CString &rFunc, int *piLineNo)
{
	rModule = g_cbNil;
	rFile = g_cbNil;
	rFunc = g_cbNil;

// Try and find the module. If this cannot be found, then it is no
//  use looking anything else up.
CImageHlp_Module cMod ;
BOOL bModFound = m_SymEngine.SymGetModuleInfo (reinterpret_cast<DWORD>(pCaller), &cMod);

	if (!bModFound) return false;
	rModule = cMod.ImageName;		// get the module name

// Look up the symbol information.
DWORD dwDummy = 0;				// function/line displacement
bool bRet = m_SymEngine.SymGetSymFromAddr (reinterpret_cast<DWORD>(pCaller), &dwDummy, m_pSymbol);

	if (!bRet) return true;		// bis hierhin ok
	rFunc = (LPCSTR)(m_pSymbol -> Name);

// Look up the line stuff.
CImageHlp_Line LineInfo;

	bRet = m_SymEngine.SymGetLineFromAddr (reinterpret_cast<DWORD>(pCaller), &dwDummy, &LineInfo);
	if (!bRet) return true;
	rFile = LineInfo.FileName;
	*piLineNo = LineInfo.LineNumber;

	return true;
}
