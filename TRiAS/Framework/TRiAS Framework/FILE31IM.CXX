//  Copyright (c) 1992 Trischford Limited 
//  ( A wholly owned subsidary of Computer Associates International, Inc)
//  All Rights Reserved
//

#include "tfrmpre.hxx"

#include <commdlg.h>
#include <win31imp.hxx>

#include <string.h>

#define FILTER_STRING 	"Alle Dateien (*.*)|*.*|"
#define STDDLG_BUFFERLEN	(255*_MAX_PATH)

//#define STATIC_OFN

#if defined(CHECK_HEAP)
#include <malloc.h>
bool HEAPCHECK (void)
{
int iStatus = _heapchk();

	if (iStatus != _HEAPOK) 
		return false;

return true;
}
#else
#define HEAPCHECK()
#endif

CStdDialog_Win31 :: CStdDialog_Win31 (void) 
{
}

CStdDialog_Win31 :: ~CStdDialog_Win31 (void)
{
}


bool CStdDialog_Win31 :: Show (void)		// PlatzHalter
{
	return true;
}

#if defined(STATIC_OFN)
static OPENFILENAME s_Ofn;
#endif //STATIC_OFN

// BasisKlasse für OpenFileDlg und SaveAsDlg ----------------------------------
CStdFileDlg_Win31 :: CStdFileDlg_Win31 (HWND hW, char *initial_path)
{
	m_iResult = false;
	
#if !defined(STATIC_OFN)
	m_pOfn = new OPENFILENAME;	
	if (!m_pOfn) return;
#else
	m_pOfn = &s_Ofn;
#endif // STATIC_OFN

	memset (m_pOfn, '\0', sizeof(OPENFILENAME));
	
// OPENFILENAME initialisieren
#if _WIN32_WINNT >= 0x0500
	m_pOfn -> lStructSize = sizeof (OPENFILENAME_SIZE_VERSION_400);
#else
	m_pOfn -> lStructSize = sizeof (OPENFILENAME);
#endif // _WIN32_WINNT >= 0x0500
	m_pOfn -> hwndOwner		= hW;
	m_pOfn -> lpfnHook		= NULL;
	m_pOfn -> hInstance 		= 0;
	m_pOfn -> lpstrCustomFilter	= NULL;
	
// location of full path for m_Result 
	m_pOfn -> lpstrFile	= new char [STDDLG_BUFFERLEN+1];
	if (NULL != m_pOfn -> lpstrFile) {
		m_pOfn -> lpstrFile[0] = '\0';
		m_pOfn -> nMaxFile = STDDLG_BUFFERLEN;
	} else
		m_pOfn -> nMaxFile = 0;

// location of file name only for Result 
	m_pOfn -> nMaxFileTitle		= 0;
	m_pOfn -> lpstrFileTitle	= NULL;
	m_pOfn -> lpstrTitle		= NULL;
	m_pOfn -> Flags				= OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	m_pOfn -> nFilterIndex		= 1;
	
	m_isOpen = false;

	if (m_pOfn -> lpstrFile == NULL) return;
	
	if (strlen (initial_path))
		strcpy (m_pOfn -> lpstrFile, initial_path);
	else
		strcpy (m_pOfn -> lpstrFile, ".\\*.*");

// find default extension
char *fulldesc = strrchr (m_pOfn -> lpstrFile, '|');
char *initial_ext = fulldesc != NULL ? strchr (fulldesc, '.') : 
				       strrchr (m_pOfn -> lpstrFile, '.');
char *pDefExt = NULL;
char *pFilters = NULL;

	if (fulldesc) *fulldesc = '\0';
	
	if (initial_ext && initial_ext[0] && initial_ext[1]) {
	int ext_len = strlen (++initial_ext);  // skip first '.'
	int hasWildCard = 0;

	// Check for WildCards
		for (int i = 0; i < ext_len; i++)
 			if ((initial_ext[i] == '*') || (initial_ext[i] == '?'))
				hasWildCard = 1;

	// Set as default extension if there are no wildcards 
		if (!hasWildCard && (pDefExt = new char[ext_len +1]))
			strcpy (pDefExt, initial_ext);

	// Set up filter string
		pFilters = new char[strlen (FILTER_STRING) + _MAX_PATH + (ext_len+3) * 2];
		if (strcmp (initial_ext , "*") != 0)	// its not the standard wildcard
			wsprintf (pFilters, "%s|*.%s|%s", m_pOfn -> lpstrFile, 
							  initial_ext, FILTER_STRING);
		else
			strcpy (pFilters, FILTER_STRING);
	} else {
	// Set up standard filter string
		pFilters = new char[strlen (FILTER_STRING) + 1 ];
	   	strcpy (pFilters, FILTER_STRING);
	}

	if (pFilters) {				
	char chWildChar = pFilters[strlen (pFilters)-1];    // Grab the wild character
	int wCtr = 0;

		while (pFilters[wCtr]) {
			if (pFilters[wCtr] == chWildChar) pFilters[wCtr]=0;
			wCtr++;
		}
	}

// sonstige Member initialisieren
	m_pOfn -> lpstrDefExt		= pDefExt;
	m_pOfn -> lpstrFilter		= pFilters;

	memset (m_pOfn -> lpstrFile, '\0', STDDLG_BUFFERLEN);
}

CStdFileDlg_Win31 :: ~CStdFileDlg_Win31 (void)
{
	if (m_pOfn) {
		if (m_pOfn -> lpstrDefExt) delete (char *)m_pOfn -> lpstrDefExt;
		if (m_pOfn -> lpstrFilter) delete (char *)m_pOfn -> lpstrFilter;
		if (m_pOfn -> lpstrFile) delete (char *)m_pOfn -> lpstrFile;
		if (m_pOfn -> lpstrTitle) delete (char *)m_pOfn -> lpstrTitle;
#if !defined(STATIC_OFN)
		delete m_pOfn;
#endif
	}
}

void CStdFileDlg_Win31 :: GetFileName (char *pBuff, int n)
{
	if (m_pOfn && m_pOfn -> lpstrFile && m_pOfn -> lpstrFile[0]) {
	// Gesamtlänge feststellen
	int iLen = 0;
	LPSTR pT = m_pOfn -> lpstrFile;

		do {
		int i = strlen (pT)+1;

			iLen += i;
			pT += i;
		} while (iLen <= STDDLG_BUFFERLEN && '\0' != *pT);

	int iMax = min (n, iLen+1);

		if (iMax >= 1) {
			memcpy (pBuff, m_pOfn -> lpstrFile, iMax);

			pBuff[iMax-1] = '\0';	// mit 2 NullBytes abschließen
			if (iMax > 1) 
				pBuff[iMax-2] = '\0';
		} 
	} else
		pBuff[0] = '\0';
}

int CStdFileDlg_Win31 :: GetFileNameLen()
{ 
	if (m_pOfn && m_pOfn -> lpstrFile && m_pOfn -> lpstrFile[0]) {
	int iLen = 0;
	LPSTR pT = m_pOfn -> lpstrFile;

		do {
		int i = strlen (pT)+1;

			iLen += i;
			pT += i;
		} while (iLen <= STDDLG_BUFFERLEN && '\0' != *pT);

		return iLen +1; 
	} else
		return 0; 
}

bool CStdFileDlg_Win31 :: Show (void)
{
	if (m_pOfn == NULL) return false;

char *pFileTitle = new char [_MAX_PATH+1];

	if (pFileTitle == NULL) return false;

	pFileTitle[0] = '\0';
	m_pOfn -> lpstrFileTitle	= pFileTitle;
	m_pOfn -> nMaxFileTitle		= _MAX_PATH;
	
	if (m_isOpen) {
		if (!(m_iResult = GetOpenFileName (m_pOfn))) {
			m_pOfn -> lpstrFile[0] = '\0';
			delete [] pFileTitle;
			return false;
		}
	} else {
		if (!(m_iResult = GetSaveFileName (m_pOfn))) {
			m_pOfn -> lpstrFile[0] = '\0';
			delete [] pFileTitle;
			return false;
        	}
	}
	delete [] pFileTitle;

return true;
}

// HookFunktion setzen --------------------------------------------------------
// HilfsFunktion 
extern "C" {

inline void AssignHook (HOOKFCNCALLBACK &pHF, HOOKFCN pF)
{
	pHF = (HOOKFCNCALLBACK)pF;
}

}	// extern "C"
	

void CStdFileDlg_Win31 :: SetHookFcn (HOOKFCN pF)
{
	if (pF == NULL || m_pOfn == NULL) return;
	
	AssignHook (m_pOfn -> lpfnHook, pF);
	m_pOfn -> Flags |= OFN_ENABLEHOOK;
}


// anderes Template setzen ----------------------------------------------------
void CStdFileDlg_Win31 :: SetTemplate (HGLOBAL hDlgRes)
{
	if (hDlgRes == 0 || m_pOfn == NULL) return;
	
	m_pOfn -> hInstance = (HINSTANCE)hDlgRes;
	m_pOfn -> lpTemplateName = NULL;
	m_pOfn -> Flags &= ~OFN_ENABLETEMPLATE;
	m_pOfn -> Flags |= OFN_ENABLETEMPLATEHANDLE;
}
	

void CStdFileDlg_Win31 :: SetTemplate (HINSTANCE hInst, const char *pRcs)
{
	if (hInst == 0 || pRcs == NULL || m_pOfn == NULL) return;
	
	m_pOfn -> hInstance = hInst;
	m_pOfn -> lpTemplateName = pRcs;
	m_pOfn -> Flags &= ~OFN_ENABLETEMPLATEHANDLE;
	m_pOfn -> Flags |= OFN_ENABLETEMPLATE;
}
	

long CStdFileDlg_Win31 :: Flags (void) 
{ 
	return m_pOfn ? m_pOfn -> Flags : 0; 
}


void CStdFileDlg_Win31 :: AddFlags (long newFlags) 
{ 
	if (m_pOfn) m_pOfn -> Flags |= newFlags; 
}
	

void CStdFileDlg_Win31 :: SetCustomData (DWORD lData) 
{ 
	if (m_pOfn) m_pOfn -> lCustData = lData;
}
	

void CStdFileDlg_Win31 :: SetFilterIndex (int iFIndex) 
{ 
	if (m_pOfn) m_pOfn -> nFilterIndex = iFIndex;
}
	

int CStdFileDlg_Win31 :: GetFilterIndex (void) 
{ 
	if (m_pOfn) return m_pOfn -> nFilterIndex;

return 0;
}

void CStdFileDlg_Win31 :: SetCaption (const char *lpCaption)
{
	if (m_pOfn && lpCaption) {
		if (m_pOfn -> lpstrTitle == NULL) 
			m_pOfn -> lpstrTitle = new char [_MAX_PATH];
		if (m_pOfn -> lpstrTitle)
			strcpy ((char *)m_pOfn -> lpstrTitle, lpCaption);
	}
}	

void CStdFileDlg_Win31 :: SetFileName (const char *pName)
{
	if (m_pOfn && m_pOfn -> lpstrFile)
		strcpy (m_pOfn -> lpstrFile, pName);
}
                                         

void CStdFileDlg_Win31 :: SetInitialDir (const char *pPath)
{
	if (m_pOfn) {
	char *pEnd = (char *)&pPath[strlen(pPath)-1];
	 
		if (*pEnd == '\\') *pEnd = '\0';
		m_pOfn -> lpstrInitialDir = pPath;
	}
}


// Spezifische Konstruktoren --------------------------------------------------
void CStdFileDlg_Win31 :: SetFlags (long newFlags) 
{ 
	if (m_pOfn) m_pOfn -> Flags = newFlags; 
}
	

OpenDlg_Win31 :: OpenDlg_Win31 (HWND hwnd, char *c)
	       : CStdFileDlg_Win31 (hwnd, c)
{
	m_isOpen = true;
}

SaveAsDlg_Win31 :: SaveAsDlg_Win31 (HWND hwnd, char *c)
		 : CStdFileDlg_Win31 (hwnd, c)
{
	m_isOpen = false;
	if (m_pOfn) m_pOfn -> Flags |= OFN_HIDEREADONLY;
}


OpenDlg_Win31 :: ~OpenDlg_Win31 (void)
{
	// nothing to do
}

SaveAsDlg_Win31 :: ~SaveAsDlg_Win31 (void)
{
	// nothing to do
}


