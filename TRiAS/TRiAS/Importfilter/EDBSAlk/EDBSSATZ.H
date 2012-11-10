//	Datei:	EdbsSatz.h
//	Stand:	30.08.1995
//	Autor:	Denkewitz
//	(c) 1995 uve GmbH FEZ Potsdam

class CEdbsSatz : public CObject
{
	BOOL		m_bGueltig;
	CString		m_strDaten;

public:			CEdbsSatz();
				~CEdbsSatz();

	BOOL		Gueltig()	{ return m_bGueltig; }
	void		Lesen( class CArchive* );
	CString		Daten()		{ return m_strDaten; }

DECLARE_SERIAL( CEdbsSatz )
};
