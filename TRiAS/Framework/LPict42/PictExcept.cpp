#include "stdafx.h"
#include "LPictImpl.h"

#ifdef LAFX_PICT_SEG
#pragma code_seg(LAFX_PICT_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

static const LPCSTR rgszCPictExceptionCause[] = {
	_T("none")
	, _T("Missing Headerinfo")
	, _T("invalid Headerinfo")
	, _T("not supported Format")
	, _T("Filesize")
	, _T("Missing Stripinfo")			// errImageInfo			// Strip / Tile - Informationen fehlen
	, _T("Missing TileInfo")			// errImageLayout		// bei Tiled Images fehlt Breite und/oder Höhe
	, _T("not supported Colorspace")
	, _T("not supported Compression")
	, _T("Pictsize")
	, _T("not supported SamplesPerPixel")
	, _T("Memory Error")
	, _T("Datentyp Error")
	, _T("SubfileNotFound")
	, _T("not supported Orientation")
	, _T("invalid Filter param")
	, _T("cannot read source band")
	, _T("cannot read destination band")
	, _T("cannot write destination band")
	, _T("filter error")
	, _T("Could not draw picture transparently")
	, _T("Could not initialize LeadTools toolkit")
};

TCHAR szUnknown[] = _T("Unknown");

void AFXAPI LAfxThrowPictException(int cause /*=CPictException::none*/ , LPCTSTR lpszPictType /*=NULL*/, LPCTSTR lpszCause /*=NULL*/, LPCTSTR lpszPictName /*=NULL*/) {
#ifdef _DEBUG
	LPCSTR lpsz;
	if (cause >= 0 && cause < _countof(rgszCPictExceptionCause))
		lpsz = rgszCPictExceptionCause[cause];
	else
		lpsz = szUnknown;
	TRACE("CPicture exception: [%hs][%s][%s][%s]\n",
		lpsz,
		(lpszPictType == NULL) ? szUnknown : lpszPictType,
		(lpszCause == NULL) ? _T("") : lpszCause,
		(lpszPictName == NULL) ? szUnknown : lpszPictName
		);
#endif
	THROW(new CPictException(cause, lpszPictType, lpszCause, lpszPictName ));
}

void AFXAPI LAfxThrowPictMemException( CMemBlock *pBlock, HPBYTE pByte, long lSize /*=0*/, LPCTSTR lpszPictType /*= NULL*/, LPCTSTR lpszPictName /*= NULL*/ ) {
	CString	strMsg;

	strMsg.Format( _T("%s 0x%08lx 0x%08lx 0x%08lx 0x%08lx"), 
		(LPCTSTR) pBlock->GetBlockName(),
		(HPBYTE) *pBlock, pByte, pByte + lSize, ( (HPBYTE) *pBlock ) + pBlock->Size() );
	LAfxThrowPictException(CPictException::errMemory, lpszPictType, strMsg, lpszPictName );
}

//////////////////////////////////////////////////////////////////////////////
//	Exception
//////////////////////////////////////////////////////////////////////////////

CPictException::CPictException( int cause, LPCTSTR lpszPictType /*=NULL*/, LPCTSTR lpszCause /*=NULL*/, LPCTSTR lpszPictName /*=NULL*/ ) {
	m_cause = cause;
	m_strCause = lpszCause;
	m_strPictType = lpszPictType;
	m_strPictName = lpszPictName;
}

#ifdef _DEBUG
void CPictException::Dump(CDumpContext& dc) const {
	CObject::Dump(dc);
	AFX_DUMP0(dc, " m_cause = ");
	if (m_cause >= 0 && m_cause < sizeof(rgszCPictExceptionCause) / sizeof(LPCSTR)) {
		dc << rgszCPictExceptionCause[m_cause];
	} else {
		dc << szUnknown;
	}
}
#endif

#include	<strstrea.h>

namespace lpictdll {

static void ShowMessage( LPCTSTR lpszMessage ) {
	HANDLE	hStdErr;
	if( NULL != ( hStdErr = GetStdHandle( STD_ERROR_HANDLE ) ) )
		fprintf( stderr, "%s\n", lpszMessage );
	else
		::AfxMessageBox( lpszMessage );
}

void AFX_EXT_API ReportPictException( CPictException *e, LPCTSTR lpszAddInf /*= NULL*/ ) {
	CString	S;
	LPCSTR lpsz;
	ASSERT_VALID( e );
	ASSERT_KINDOF( CPictException, e );
	if (e->m_cause >= 0 && e->m_cause < _countof(rgszCPictExceptionCause))
		lpsz = rgszCPictExceptionCause[e->m_cause];
	else
		lpsz = szUnknown;
	S.Format("CPicture exception: [%hs][%s][%s][%s]\n",
		lpsz,
		(e->m_strPictType.IsEmpty()) ? szUnknown : (LPCTSTR) e->m_strPictType,
		(e->m_strCause.IsEmpty()) ? _T("") : (LPCTSTR) e->m_strCause,
		(e->m_strPictName.IsEmpty()) ? szUnknown : e->m_strPictName
		);
	ShowMessage( S );
}

void AFX_EXT_API ReportFileException( CFileException *e, LPCTSTR lpszAddInf /*= NULL*/ ) {
	strstream   s;
	s << "FileException: ";
	switch( e->m_cause ) {
	case CFileException::none				: s << "No error occurred"; break;
	case CFileException::generic			: s << "An unspecified error occurred."; break;
	case CFileException::fileNotFound		: s << "The file could not be located."; break;
	case CFileException::badPath			: s << "All or part of the path is invalid."; break;
	case CFileException::tooManyOpenFiles	: s << "The permitted number of open files was exceeded."; break;
	case CFileException::accessDenied		: s << "The file could not be accessed."; break;
	case CFileException::invalidFile		: s << "There was an attempt to use an invalid file handle."; break;
	case CFileException::removeCurrentDir	: s << "The current working directory cannot be removed."; break;
	case CFileException::directoryFull		: s << "There are no more directory entries."; break;
	case CFileException::badSeek			: s << "There was an error trying to set the file pointer."; break;
	case CFileException::hardIO				: s << "There was a hardware error."; break;
	case CFileException::sharingViolation	: s << "SHARE.EXE was not loaded, or a shared region was locked."; break;
	case CFileException::lockViolation		: s << "There was an attempt to lock a region that was already locked."; break;
	case CFileException::diskFull			: s << "The disk is full."; break;
	case CFileException::endOfFile			: s << "The end of file was reached."; break;
	default:	s << "?????"; break;
	}
	if( lpszAddInf ) {
		s << lpszAddInf;
	}
	s << '\0';
	ShowMessage( s.str( ) );
}

void AFX_EXT_API ReportMemoryException( CMemoryException *e, LPCTSTR lpszAddInf /*= NULL*/ ) {
	strstream   s;
	s << "MemoryException: ";
	s << '\0';
	ShowMessage( s.str( ) );
}

} // namespace lpictdll