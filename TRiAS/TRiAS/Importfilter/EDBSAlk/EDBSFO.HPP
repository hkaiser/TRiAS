///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			edbsfo.hpp
//
//	Stand:			15.11.1994
//	Beschreibung:	EDBS-Datei öffnen
//	Entwicklung:	15.11.94	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////

#ifndef	_EDBSFO_HPP
#define _EDBSFO_HPP

#include	<afxdlgs.h>

class COpenEDBSFile
{
public:
				COpenEDBSFile();
				~COpenEDBSFile();
	CString		GetPathName();

protected:
	CString*	m_strFileName;
};

#endif	// _EDBSFO_HPP
