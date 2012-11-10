//	Datei:	KoorPaar.cpp
//	Stand:	30.08.1995
//	Autor:	Denkewitz
//	(c) 1995 uve GmbH FEZ Potsdam

#include "stdafx.h"
#include "trif.hpp"
#include "koorpaar.h"

CKoordPaar :: CKoordPaar()
{	m_dblHoch = m_dblRechts = 0.0;
	m_bGueltig = FALSE;
}	// Konstruktion

CKoordPaar :: CKoordPaar( const char *txt )
{	Setzen( txt );
}	// Konstruktion

CKoordPaar :: ~CKoordPaar()
{
}	// Destruktion

void CKoordPaar :: Setzen( const char *txt )
{
//	CString		H, R, P;
	const char	*pos = txt;
	double	dblHoch, dblRechts;
	short	faktor = 1;
	short	i;

	// Format des KoordinatenPaares in txt:
	//		rrhhr_h_rrrrrrhhhhhh in ATKIS
	//		rrhhrrhhrrrrrrhhhhhh in ALK
	//		+hhhhhhhhh+rrrrrrrrr in Soldner-Berlin
	dblHoch = 0.0;
	dblRechts = 0.0;
	if ( g_pMetaData->m_sKoordinatensystem == 0 ) {
		if( *txt == '+' || *txt == '-' )
			g_pMetaData->m_sKoordinatensystem = 3;
		else if( *txt+5 == ' ' )
			g_pMetaData->m_sKoordinatensystem = 2;
		else
			g_pMetaData->m_sKoordinatensystem = 1;
	}
	if( g_pMetaData->m_dKoeff11 == 0 ) {
		if( *txt == '+' || *txt == '-' ) {
			g_pMetaData->m_dKoeffEDBS = 0.001;
			g_pMetaData->m_dKoeff11 = 0.001;
		}
		else if( *txt+5 == ' ' ) {
			g_pMetaData->m_dKoeffEDBS = 0.01;
			g_pMetaData->m_dKoeff11 = 0.01;
		}
		else {
			g_pMetaData->m_dKoeffEDBS = 0.001;
//			g_pMetaData->m_dKoeff11 = 0.001;
			g_pMetaData->m_dKoeff11 = 0.01;
		}
		g_pMetaData->m_dKoeff22 = g_pMetaData->m_dKoeff11;
	}

	if ( g_pMetaData->m_sKoordinatensystem == 3 ) {	// Soldner-Berlin
		faktor = 1;
		if ( *pos == '-' )
			faktor = -1;
		pos++;
		for ( i = 0; i < 9; i++ )
			dblHoch = dblHoch * 10 + *pos++ - '0';
		dblHoch *= faktor;

		faktor = 1;
		if ( *pos == '-' )	faktor = -1;
		pos++;
		for ( i = 0; i < 9; i++ )
			dblRechts = dblRechts * 10 + *pos++ - '0';
		dblRechts *= faktor;
	}
	else if ( g_pMetaData->m_sKoordinatensystem == 2 ) {	//ATKIS
 		dblRechts = dblRechts * 10 + *pos++ - '0';
		dblRechts = dblRechts * 10 + *pos++ - '0';

		dblHoch = dblHoch * 10 + *pos++ - '0';
		dblHoch = dblHoch * 10 + *pos++ - '0';

		dblRechts = dblRechts * 10 + *pos++ - '0';
		pos++;
		dblRechts = dblRechts * 10 + *pos++ - '0';

		dblHoch = dblHoch * 10 + *pos++ - '0';
		pos++;
		dblHoch = dblHoch * 10 + *pos++ - '0';

		dblRechts = dblRechts * 10 + *pos++ - '0';
		dblRechts = dblRechts * 10 + *pos++ - '0';
		dblRechts = dblRechts * 10 + *pos++ - '0';
		dblRechts = dblRechts * 10 + *pos++ - '0';
		dblRechts = dblRechts * 10 + *pos++ - '0';
		dblRechts = dblRechts * 10 + *pos++ - '0';

		dblHoch = dblHoch * 10 + *pos++ - '0';
		dblHoch = dblHoch * 10 + *pos++ - '0';
		dblHoch = dblHoch * 10 + *pos++ - '0';
		dblHoch = dblHoch * 10 + *pos++ - '0';
		dblHoch = dblHoch * 10 + *pos++ - '0';
		dblHoch = dblHoch * 10 + *pos++ - '0';
	}
	else if ( g_pMetaData->m_sKoordinatensystem == 1 ) {	//ALK
 		dblRechts = dblRechts * 10 + *pos++ - '0';
		dblRechts = dblRechts * 10 + *pos++ - '0';

		dblHoch = dblHoch * 10 + *pos++ - '0';
		dblHoch = dblHoch * 10 + *pos++ - '0';

		dblRechts = dblRechts * 10 + *pos++ - '0';
		dblRechts = dblRechts * 10 + *pos++ - '0';

		dblHoch = dblHoch * 10 + *pos++ - '0';
		dblHoch = dblHoch * 10 + *pos++ - '0';

		dblRechts = dblRechts * 10 + *pos++ - '0';
		dblRechts = dblRechts * 10 + *pos++ - '0';
		dblRechts = dblRechts * 10 + *pos++ - '0';
		dblRechts = dblRechts * 10 + *pos++ - '0';
		dblRechts = dblRechts * 10 + *pos++ - '0';
		dblRechts = dblRechts * 10 + *pos++ - '0';

		dblHoch = dblHoch * 10 + *pos++ - '0';
		dblHoch = dblHoch * 10 + *pos++ - '0';
		dblHoch = dblHoch * 10 + *pos++ - '0';
		dblHoch = dblHoch * 10 + *pos++ - '0';
		dblHoch = dblHoch * 10 + *pos++ - '0';
		dblHoch = dblHoch * 10 + *pos++ - '0';
	}

	if( g_pMetaData->m_sRH == 0 ) {
		if( *txt == '+' || *txt == '-' )
			g_pMetaData->m_sRH = -1;
		else
			g_pMetaData->m_sRH = 1;
	}

//	dblHoch *= g_pMetaData->m_dKoeff11;
//	dblRechts *= g_pMetaData->m_dKoeff22;
	dblHoch *= g_pMetaData->m_dKoeffEDBS;
	dblRechts *= g_pMetaData->m_dKoeffEDBS;

	if( g_pMetaData->m_sRH == -1 ) {
		m_dblHoch = dblRechts;
		m_dblRechts = dblHoch;
	}
	else if ( g_pMetaData->m_sRH == 1 ) {
		m_dblHoch = dblHoch;
		m_dblRechts = dblRechts;
	}

	if( g_pMetaData->m_lOffsetX == -1 )
		g_pMetaData->m_lOffsetX = 1000000L * (long)(m_dblRechts / 1000000);
	if( g_pMetaData->m_lOffsetY == -1 )
		g_pMetaData->m_lOffsetY = 1000000L * (long)(m_dblHoch / 1000000);
	m_bGueltig = TRUE;

}	// Setzen

void CKoordPaar::Reset()
{
	m_dblHoch = 0;
	m_dblRechts = 0;
	m_bGueltig = FALSE;
}

BOOL CKoordPaar::Gueltig()
{
	return m_bGueltig;
}
