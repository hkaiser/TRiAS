//	Datei:	KoorPaar.cpp
//	Stand:	30.08.1995
//	Autor:	Denkewitz
//	(c) 1995 uve GmbH FEZ Potsdam

#include "stdafx.h"
#include "koorpaar.h"

extern short g_iKoordFormat;
extern BOOL g_bKoordTauschen;

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

	if ( g_iKoordFormat == 1 )	// Soldner-Berlin
	{
		faktor = 1;
		if ( *pos == '-' )	faktor = -1;
		pos++;
		for ( i = 0; i < 9; i++ )
			dblHoch = dblHoch * 10 + *pos++ - '0';
		dblHoch *= faktor;
		dblHoch /= 1000.0;		// Koordinaten in mm

		faktor = 1;
		if ( *pos == '-' )	faktor = -1;
		pos++;
		for ( i = 0; i < 9; i++ )
			dblRechts = dblRechts * 10 + *pos++ - '0';
		dblRechts *= faktor;
		dblRechts /= 1000.0;	// Koordinaten in mm

		if ( g_bKoordTauschen )
		{
			m_dblHoch = dblRechts;
			m_dblRechts = dblHoch;
		}
		else
		{
			m_dblHoch = dblHoch;
			m_dblRechts = dblRechts;
		}
		m_bGueltig = TRUE;
	}
	else
	{
		dblRechts = dblRechts * 10 + *pos++ - '0';
		dblRechts = dblRechts * 10 + *pos++ - '0';

		dblHoch = dblHoch * 10 + *pos++ - '0';
		dblHoch = dblHoch * 10 + *pos++ - '0';

		dblRechts = dblRechts * 10 + *pos++ - '0';
		if ( *pos == ' ' )		pos++;
		else
		{	dblRechts = dblRechts * 10 + *pos++ - '0';
			faktor = 10;
		}

		dblHoch = dblHoch * 10 + *pos++ - '0';
		if ( *pos == ' ' )		pos++;
		else		dblHoch = dblHoch * 10 + *pos++ - '0';

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

		dblHoch /= 100.0;		// ATKIS mit 9 Digit ==> Meter!
		dblRechts /= 100.0;
		if ( faktor > 1 )
		{	dblHoch /= faktor;		// ALK mit 10 Digit ==> Meter!
			dblRechts /= faktor;
		}

		if ( g_bKoordTauschen )
		{
			m_dblHoch = dblRechts;
			m_dblRechts = dblHoch;
		}
		else
		{
			m_dblHoch = dblHoch;
			m_dblRechts = dblRechts;
		}
		m_bGueltig = TRUE;
	}
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
