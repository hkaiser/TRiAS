// Eigentliche Arbeit
// File: DOWORK.CPP

#include "bslp.h"

#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ospace/file/path.h>

#include "BslApp.h"

///////////////////////////////////////////////////////////////////////////////
// Fehler melden
void ebCALLBACK ReportCompilerError (
	long lParam, ebLPCTSTR lpErrorText, ebDWORD dwErrNum, ebWORD wLineNo, 
	ebWORD wCharPos, ebLPCTSTR lpSource, ebLPCTSTR lpHelpFile, ebDWORD dwHelpContext)
{
// alle newlines durch ' ' ersetzen
os_string strError = lpErrorText;
int iPos = 0;

	while (os_npos != (iPos = strError.find('\n', iPos)))
		strError[iPos] = ' ';

	fprintf(stderr, "%s(%d) : error B%04ld: %s\n", (char *)lParam, wLineNo, dwErrNum, strError.c_str());
}

///////////////////////////////////////////////////////////////////////////////
// Konstante suchen (und finden)
ebINT ebCALLBACK RetrieveDefine (long lParam, ebLPCSTR lpName, ebLPVOID lpDest)
{
CDefines *pMap = reinterpret_cast<CDefines *>(lParam);
CDefines::iterator it = pMap -> find (lpName);

	if (it != pMap -> end()) {
	const char *pcText = (*it).second.c_str();
	
		strcpy ((char *)lpDest, pcText);
		return TYP_STRING;
	}
	return TYP_EMPTY;	// not found
}

///////////////////////////////////////////////////////////////////////////////
// 
int CThisApp::CompileAndSave (CebInstance &rInst, char *pInFile)
{
// Dateinamen evtl. erzeugen und ausgeben
	if (0 == m_strOutFile.size()) {
	os_path str = os_string(pInFile);

		str.extension ("ebc");
		m_strOutFile = os_string(str);
	}
	fprintf (stdout, "%s\n", pInFile);

struct stat rgStat;
int iRes = stat (pInFile, &rgStat);

	if (0 != iRes || 0 == rgStat.st_size) {
		fprintf (stderr, "%s: File does not contain any information.\n", pInFile);
		return BCL_ERROR_STATFAILED;
	}

// Datei öffnen und einlesen
int fh = _lopen (pInFile, OF_READ|OF_SHARE_DENY_WRITE);

	if (-1 == fh) {
		fprintf (stderr, "%s: File does not exist.\n", pInFile);
		return BCL_ERROR_FILENOTFOUND;
	}

// Daten einlesen
char *pData = NULL;
ebCOMPILESTRUCT cs;

	try {
	// read in the data
		pData = new char [rgStat.st_size+1];
		memset (pData, '\0', rgStat.st_size+1);
		if (0 >= _lread (fh, pData, rgStat.st_size)) {
			fprintf (stderr, "%s: Could not read data.\n", pInFile);
			throw BCL_ERROR_READERROR;
		}

	// close input file
		if (0 <= fh) {
			_lclose (fh);
			fh = -1;
		}

	// compile the script
		memset (&cs, '\0', sizeof(ebCOMPILESTRUCT));
		cs.wVersion = CS_VERSION;
		cs.wFlags = CF_USELOCALERRORPROC|CF_USECONSTPROC;
		cs.lpText = pData;
		cs.hInstance = rInst.GetHandle();
		cs.lpfnError = ReportCompilerError;
		cs.ErrorData = (ebDWORD)pInFile;
		cs.lpfnConst = RetrieveDefine;
		cs.ConstData = (ebDWORD)&m_Defines;

	CebCompiler Comp;

		iRes = Comp.Compile (&cs);
		if (iRes == ebERR_COMPILERERROR) {
//			fprintf(stderr, "%s: Errors found, compilation aborted.\n", pInFile);
			throw BCL_ERROR_COMPILERERROR;
		} else if (0 != iRes) 
			throw iRes;

	// write back the compiled code
		fh = _lcreat (m_strOutFile.c_str(), 0);
		if (-1 == fh) {
			fprintf (stderr, "%s: Can't create output file.\n", m_strOutFile.c_str());
			throw BCL_ERROR_CANTCREATEOUTPUT;
		}

		iRes = WriteCodeAndText (fh, pData, cs.hCode);
		if (0 != iRes) throw iRes;

		if (NULL != cs.hCode) {
			ebCode_Free(cs.hCode);
			cs.hCode = NULL;
		}
		_lclose (fh);
		fh = -1;

	} catch (int iError) {
		if (0 <= fh) _lclose (fh);
		if (NULL != pData) delete pData;
		if (NULL != cs.hCode) ebCode_Free(cs.hCode);
		return iError;
	}

	return 0;		// no error
}

int CThisApp::WriteCodeAndText (int fh, char *pData, ebHCODE hCode)
{
// Header initialisieren und wegschreiben
ebFILEHEADER Head;

	Head.wVersion = FH_VERSION;
	Head.id = FH_ID;
	Head.dwCodeSz = ebCode_GetSize(hCode);
	Head.dwScriptSz = m_fCodeOnly ? 0 : strlen(pData);
	
	_lwrite (fh, (LPCSTR)&Head, sizeof(Head));	// Header schreiben
	
	Head.dwCode = _llseek (fh, 0L, SEEK_CUR);	// Code schreiben
	_hwrite (fh, (LPCSTR)ebCode_GetPointer(hCode), Head.dwCodeSz);
	
	if (!m_fCodeOnly) {							// Script schreiben
		Head.dwScript = _llseek (fh, 0L, SEEK_CUR);	
		_hwrite (fh, pData, Head.dwScriptSz);
	} else 
		Head.dwScript = 0;
	
	_llseek (fh, 0L, SEEK_SET);
	_lwrite (fh, (LPCSTR)&Head, sizeof(Head));	// Header nochmal schreiben
	
	return 0;
}
