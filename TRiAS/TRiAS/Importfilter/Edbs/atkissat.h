//	Datei:	AtkisSat.h
//	Stand:	30.08.1995
//	Autor:	Denkewitz
//	(c) 1995 uve GmbH FEZ Potsdam

class CAtkisSatz : public CObject
{
public:
	BOOL OF_BI_PunktGueltig( short, short );
	char SplineKennung( short lnr );
	BOOL HatObjekte( int );
	enum start	{	AKND, AEND, BKRT, BINF, BSPE,
					FEIN, FAEN, FLOE, FALG	};

private:
	enum typ	{	ULQA0000, IBENKRT,  ULOTEX,   ULOBNN,
					ULTANN,   ULBENFOL, ULBENGEO, ULBENOBJ,
					ULOALK,   ULPUNN };

	BOOL		m_bGueltig;
	BOOL		m_bKomplett;
	start		m_eStart;
	typ			m_eTyp;
	CString		m_strBuffer;

	CKoordPaar	m_StartPunkt;
	BOOL		m_bObjektDaten;
	BOOL		m_bAttrSatz;
	CObArray	m_Linien;
	CObArray	m_Objekte;
	CObArray	m_Infos;

	char		m_AttrObjNr[8];
	char		m_AttrOTNr[4];
	char		m_AttrPruef[4];
	short		m_AttrAnzahl;
	CString		m_Attribute;

	BOOL		m_fIsFloeDelta;		// #HK011114

public:			CAtkisSatz();
				~CAtkisSatz();

	BOOL		Gueltig()	{ return m_bGueltig; }
	BOOL		Komplett()	{ return m_bKomplett; }
	void		Lesen( const char* );
	start		Start()		{ return m_eStart; }
	typ			Typ()		{ return m_eTyp; }

	BOOL		ObjektDaten()		{ return m_bObjektDaten; }
	double		GrundPunktHoch()	{ return m_StartPunkt.Hoch(); }
	double		GrundPunktRechts()	{ return m_StartPunkt.Rechts(); }
	short		AnzahlLinien()		{ return m_Linien.GetSize(); }
	const char	*ArtGeometrie( short );
	short		AnzahlPunkte( short );
	short		NumFktParam( short );
	const char	*ObjektNummerRechts( short, short );
	const char	*ObjektteilNummerRechts( short, short );
	const char	*LinienTeilungRechts( short, short );
	const char	*Folie( short, short );
	const char	*ObjektArt( short, short );
	const char	*ObjektNummerLinks( short, short );
	const char	*ObjektteilNummerLinks( short, short );
	const char	*LinienTeilungLinks( short, short );
	double		EndPunktHoch( short );
	double		EndPunktRechts( short );

	BOOL		ObjFkt( short );
	const char	*OF_Folie( short );
	const char	*OF_Objektart( short );
	const char	*OF_Aktuali( short );
	const char	*OF_Objekttyp( short );
	const char	*OF_Objektnummer( short );
	const char	*OF_Modelltyp( short );
	const char	*OF_Datum( short );
	const char	*OF_Aender( short );
	short		OF_AnzahlBesInfo( short );
	short		OF_BI_Anzahl( short, short );
	const char	*OF_BI_Art( short, short );
	const char	*OF_BI_Kartentyp( short, short );
	const char	*OF_BI_Objektart( short, short );
	const char	*OF_BI_Text( short, short );
	const char	*OF_BI_ArtGeo( short, short );
	const char	*OF_BI_ObjTeilNr( short, short );
	BOOL		OF_BI_GeoAngaben( short, short );
	double		OF_BI_Koord1Hoch( short, short );
	double		OF_BI_Koord1Rechts( short, short );
	double		OF_BI_Koord2Hoch( short, short );
	double		OF_BI_Koord2Rechts( short, short );
	double		OF_BI_Koord3Hoch( short, short );
	double		OF_BI_Koord3Rechts( short, short );

	BOOL		AttributSatz()		{ return m_bAttrSatz; }
	const char	*AttrObjNr()		{ return m_AttrObjNr; }
	const char	*AttrObjTeilNr()	{ return m_AttrOTNr; }
	const char	*AttrPruefZeichen()	{ return m_AttrPruef; }
	short		AttrAnzahl()		{ return m_AttrAnzahl; }
	const char	*Attribute()		{ return (const char*)m_Attribute; }

	double		LinienPunktHoch( short, short );
	double		LinienPunktRechts( short, short );

	BOOL		IsFloeDelta() { return m_fIsFloeDelta; }

protected:
	void ALK_Punktdaten( const char* );
	void		AnfangsSatz( const char* );
	void		EndeSatz( const char* );
	void		DatenSatz( const char* );
	void		LoeschSatz (LPCSTR);

	void		AuftragsKennSatz( const char* );
	void		ObjektDaten( const char* );
	void		ALK_Daten( const char* );
	void		AttributSatz( const char* );

	void		GrundrissKennDaten( const char* );

DECLARE_SERIAL( CAtkisSatz )
};
