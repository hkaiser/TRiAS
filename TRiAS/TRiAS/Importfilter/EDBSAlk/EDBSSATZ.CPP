//	Datei:	EdbsSatz.cpp
//	Stand:	30.08.1995
//	Autor:	Denkewitz
//	(c) 1995 uve GmbH FEZ Potsdam

#include "stdafx.h"
#include "edbssatz.h"

CEdbsSatz :: CEdbsSatz()
{
	m_bGueltig = FALSE;
}	// Konstruktion

CEdbsSatz :: ~CEdbsSatz()
{
}	// Destruktion

void CEdbsSatz :: Lesen( CArchive *pAr )
{
	CString		kopf;
	short		laenge;
	short		offset;
	char		buffer[2200];

	m_bGueltig = FALSE;

//	pAr -> Read( buffer, 4 );
//	buffer[4] = '\0';
//	kopf = buffer;
//	if ( kopf == "EDBS" ) m_bGueltig = TRUE;

	//	Bei DOS-Datensätzen kann hier noch der Rest vom vorher-
	//	gehenden Zeilenende stehen!

	while( pAr -> Read( buffer, 1 ) ) {
		if( !isspace( buffer[0] ) ) {
			if ( buffer[0] == 'E' ) {
				pAr -> Read( buffer, 3 );
				buffer[3] = '\0';
				if ( 0 == strcmp("DBS", buffer ) )
					m_bGueltig = TRUE;
			}
			break;
		}
	}

	if ( Gueltig()) {
		pAr -> Read( buffer, 4 );
		buffer[4] = '\0';
		laenge = atoi( buffer );
		pAr -> Read( buffer, 4 );
		buffer[4] = '\0';
		offset = atoi( buffer );	// wird ignoriert!

		if ( laenge <= 2000 )
		{	pAr -> Read( buffer, laenge );
			buffer[laenge] = '\0';
			m_strDaten = buffer;
		}

		// Zeilenende wegschlucken!
//		pAr -> Read( buffer, 2 );
//		if (( buffer[0] != '\r' ) || ( buffer[1] != '\n' ))
//			m_bGueltig = FALSE;
		pAr -> Read( buffer, 1 );
		if (( buffer[0] != '\r' ) && ( buffer[0] != '\n' ))
			m_bGueltig = FALSE;
	}
}

IMPLEMENT_SERIAL( CEdbsSatz, CObject, 0 )

