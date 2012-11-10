#include "stdafx.h"
#include "resource.h"
#include "ImportDlg.h"

/////////////////////////////////////////////////////////////////////////////////////////
static bool ReduceOneMapFile( LPCTSTR lpszInFile, LPCTSTR lpszOutFile, PICTSAMPLEPARAM &fp, int level) 
{
	BOOL	bRet;
	CMemBlock	memInput( Size4MB );
	CMemBlock	memOutput( Size2MB );

	CRuntimeClass	*pInRT;
	CRuntimeClass	*pOutRT = NULL;

	CPicture		*pInPict;
	CPicture		*pOutPict;

	CFile		fileInput;
	CFile		fileOutput;


	CPictSample	filter;

	if( fileInput.Open( lpszInFile, CFile::modeRead | CFile::typeBinary ) ) {
		pInRT = ::GetWritablePictureType( &fileInput );
		if( NULL == pOutRT )
			pOutRT = pInRT;
		if( NULL != pInRT && NULL != ( pInPict = (CPicture*) pInRT->CreateObject() ) ) {
			if( fileOutput.Open( lpszOutFile, CFile::modeReadWrite | CFile::modeCreate | CFile::typeBinary ) ) {
				VERIFY( NULL != ( pOutPict = (CPicture*) pOutRT->CreateObject() ) );
				if( pInPict->Attach( &fileInput ) && pInPict->ReadHeader() ) {
					if( pOutPict->Attach( &fileOutput ) ) {
						switch( pInPict->GetBitsPerSample() ) {
						case 1 : fp.sampleParam = 0; break;
//						case 8 : fp.sampleParam = level > 2 ? 3 : 0; break;     // #HK050104
//						case 8 : fp.sampleParam = level <= 2 ? 3 : 0; break;     // #HK050120
						case 8 : fp.sampleParam = 3; break;     // #HK050120
						}
						filter.SetFilterData( &fp.p );
						bRet = filter.Filter( pInPict, pOutPict );
						pOutPict->Detach();
					}
					pInPict->Detach();
				}
				fileOutput.Close();
				delete pOutPict;
			}
			delete pInPict;
		}
		fileInput.Close();
	}
	return TRUE == bRet ? 1 : 0;
}
///////////////////////////////////////////////////////////////////////////////////////


static bool ReduceOneFile( LPCTSTR lpszInFile, LPCTSTR lpszOutFile,PICTSAMPLEPARAM	&fp, CFilterProgress &progressItem ) {
	BOOL	bRet;
	CMemBlock	memInput( Size4MB );
	CMemBlock	memOutput( Size2MB );

	CRuntimeClass	*pInRT;
	CRuntimeClass	*pOutRT = NULL;

	CPicture		*pInPict;
	CPicture		*pOutPict;

	CFile		fileInput;
	CFile		fileOutput;

	CPictSample	filter;

	if( fileInput.Open( lpszInFile, CFile::modeRead | CFile::typeBinary ) ) {
		pInRT = ::GetWritablePictureType( &fileInput );
		if( NULL == pOutRT )
			pOutRT = pInRT;
		if( NULL != pInRT && NULL != ( pInPict = (CPicture*) pInRT->CreateObject() ) ) {
			if( fileOutput.Open( lpszOutFile, CFile::modeReadWrite | CFile::modeCreate | CFile::typeBinary ) ) {
				VERIFY( NULL != ( pOutPict = (CPicture*) pOutRT->CreateObject() ) );
				if( pInPict->Attach( &fileInput ) && pInPict->ReadHeader() ) {
					if( pOutPict->Attach( &fileOutput ) ) {
						switch( pInPict->GetBitsPerSample() ) {
						case 1 : fp.sampleParam = 0; break;
						case 8 : fp.sampleParam = 3; break;
						}
						filter.SetFilterData( &fp.p );
						progressItem.StartingFilter();
						bRet = filter.Filter( pInPict, pOutPict, &progressItem );
						progressItem.EndingFilter();
						pOutPict->Detach();
					}
					pInPict->Detach();
				}
				fileOutput.Close();
				delete pOutPict;
			}
			delete pInPict;
		}
		fileInput.Close();
	}
	return TRUE == bRet ? 0 : 1;
}

bool CMapImportDlg::ReduceInFile( CFilterProgress &progressChunk, CFilterProgress &progressItem ) {

	CPath	pathOfInPict, pathOfOutPict;
	CString	strOutPrefix;
	CString	S;
	CString	St;
	St.LoadString(IDS_MAPREDUCETITLE);
	pathOfInPict.Path( m_strSrcMap );
	pathOfOutPict.Path( m_strDstDir );
	pathOfOutPict.FileName( pathOfInPict.FileName() );
	strOutPrefix = pathOfOutPict.Prefix();

int irc = strcmp((LPCTSTR) pathOfInPict.Path(), (LPCTSTR) pathOfOutPict.Path());

	if (0 != irc) {	// Ein = Ausgabe
	DWORD dwAttr = GetFileAttributes((LPCTSTR) pathOfOutPict.Path());

	// Originaldatei einfach kopieren (wenn Datei noch nicht existiert)
		if ((DWORD)-1 == dwAttr &&
			!CopyFile ((LPCTSTR)pathOfInPict.Path(),(LPCTSTR) pathOfOutPict.Path(),FALSE)) 
		{
		DWORD dw = GetLastError();
		CString sText;
		TCHAR	fmtBuf[_MAX_PATH];

			sText.LoadString(IDS_ERRORCOPYFILE);
			wsprintf( fmtBuf, sText, dw );

			if ( ERROR_DISK_FULL == dw ) {
				sText.LoadString(IDS_ERRORDISKFULL);
				wsprintf( fmtBuf, _T("%s "), sText );
			}
			if ( ERROR_ACCESS_DENIED == dw ) {
				sText.LoadString(IDS_ERRORACCESSDENIED);
				wsprintf( fmtBuf, _T("%s "), sText );
			}
			::AfxMessageBox(fmtBuf);
			return false;
		}

	// ggf. Schreibschutz vom Ziel entfernen 
		dwAttr = GetFileAttributes((LPCTSTR) pathOfOutPict.Path());
		if (dwAttr & FILE_ATTRIBUTE_READONLY)
			SetFileAttributes((LPCTSTR) pathOfOutPict.Path(), dwAttr & ~FILE_ATTRIBUTE_READONLY);
	}

PICTSAMPLEPARAM	fp;

	INIT_FILTERSTRUCT( &fp, CPictSample );
	fp.sampleRate = 2;
	fp.sampleParam = 4;

int	i, max_i = (_T('e') - _T('a') + 1), max_ii = 200000;
TCHAR c;

	progressChunk.StartingFilter();
	for (c = _T('a'), i = 1; c < _T('f'); c++, i++) {
		pathOfOutPict.Prefix (strOutPrefix + c);
		S.Format( St, (LPCTSTR) pathOfInPict.FileName(), (LPCTSTR) pathOfOutPict.FileName() );
//		S.Format( _T("Größenreduktion:\r\nInput: %s\r\nOutput: %s"), (LPCTSTR) pathOfInPict.FileName(), (LPCTSTR) pathOfOutPict.FileName() );
		progressChunk.ReportingStatus( ( (double) i / max_i ) * 100, S );

	// nur runterrechnen, wenn Datei noch nicht existiert
	DWORD dwAttr = GetFileAttributes((LPCTSTR) pathOfOutPict.Path());

		if ((DWORD)-1 == dwAttr)
			ReduceOneFile(pathOfInPict.Path(), pathOfOutPict.Path(), fp, progressItem);

	// ggf. Schreibschutz vom Ziel entfernen 
		dwAttr = GetFileAttributes((LPCTSTR) pathOfOutPict.Path());
		if (dwAttr & FILE_ATTRIBUTE_READONLY)
			SetFileAttributes((LPCTSTR) pathOfOutPict.Path(), dwAttr & ~FILE_ATTRIBUTE_READONLY);

	// nächste Datei vorbereiten
		pathOfInPict.Path( pathOfOutPict.Path() );
	}
	progressChunk.EndingFilter();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////
//
bool CMapImportDlg::ReduceMapFile(void) 
{
CPath pathOfInPict, pathOfOutPict;
CString	strOutPrefix;
CString	S;

	pathOfInPict.Path( m_strSrcMap );
	pathOfOutPict.Path( m_strDstDir );
	pathOfOutPict.FileName( pathOfInPict.FileName() );
	strOutPrefix = pathOfOutPict.Prefix();

PICTSAMPLEPARAM	fp;

	INIT_FILTERSTRUCT( &fp, CPictSample );
	fp.sampleRate = 2;
	fp.sampleParam = 4;

int irc = strcmp((LPCTSTR) pathOfInPict.Path(), (LPCTSTR) pathOfOutPict.Path());

	if (0 != irc) {		// Ein != Ausgabe
	DWORD dwAttr = GetFileAttributes((LPCTSTR) pathOfOutPict.Path());

	// Originaldatei einfach kopieren (wenn Datei noch nicht existiert)
		if ((DWORD)-1 == dwAttr &&
			!CopyFile ((LPCTSTR)pathOfInPict.Path(),(LPCTSTR) pathOfOutPict.Path(),FALSE)) 
		{
		DWORD dwe = GetLastError();
		CString sText;
		TCHAR fmtBuf[_MAX_PATH];

			sText.LoadString(IDS_ERRORCOPYFILE);
			wsprintf( fmtBuf, sText, dwe );

			if ( ERROR_DISK_FULL == dwe ) {
				sText.LoadString(IDS_ERRORDISKFULL);
				wsprintf( fmtBuf, _T("%s "), sText );
			}
			if ( ERROR_ACCESS_DENIED == dwe ) {
				sText.LoadString(IDS_ERRORACCESSDENIED);
				wsprintf( fmtBuf, _T("%s "), sText );
			}

			::AfxMessageBox( fmtBuf );
			return false;
		}

	// ggf. Schreibschutz vom Ziel entfernen 
		dwAttr = GetFileAttributes((LPCTSTR) pathOfOutPict.Path());
		if (dwAttr & FILE_ATTRIBUTE_READONLY)
			SetFileAttributes((LPCTSTR) pathOfOutPict.Path(), dwAttr & ~FILE_ATTRIBUTE_READONLY);
	}

int	i, max_i = (_T('e') - _T('a') + 1), max_ii = 200000;
TCHAR c;
	
	for( c = _T('a'), i = 1; c < _T('f'); c++, i++ ) {
		pathOfOutPict.Prefix (strOutPrefix + c);

	// nur runterrechnen, wenn Datei noch nicht existiert
	DWORD dwAttr = GetFileAttributes((LPCTSTR) pathOfOutPict.Path());

		if ((DWORD)-1 == dwAttr &&		// nur, wenn Datei noch nicht existiert
			!ReduceOneMapFile (pathOfInPict.Path(), pathOfOutPict.Path(), fp, i))
		{
			return false;
		}

	// ggf. Schreibschutz vom Ziel entfernen 
		dwAttr = GetFileAttributes((LPCTSTR) pathOfOutPict.Path());
		if (dwAttr & FILE_ATTRIBUTE_READONLY)
			SetFileAttributes((LPCTSTR) pathOfOutPict.Path(), dwAttr & ~FILE_ATTRIBUTE_READONLY);

	// nächste Datei vorbereiten
		pathOfInPict.Path( pathOfOutPict.Path() );
	}
	
	return true;
}

