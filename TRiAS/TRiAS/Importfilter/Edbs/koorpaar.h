//	Datei:	KoorPaar.h
//	Stand:	30.08.1995
//	Autor:	Denkewitz
//	(c) 1995 uve GmbH FEZ Potsdam

class CKoordPaar : public CObject
{
	double	m_dblHoch;
	double	m_dblRechts;
	BOOL    m_bGueltig;

public:
	BOOL Gueltig();
	void Reset();
			CKoordPaar();
			CKoordPaar( const char* );
			~CKoordPaar();
	double	Hoch()		{ return m_dblHoch; }
	double	Rechts()	{ return m_dblRechts; }
	void	Setzen( const char* );
};
   