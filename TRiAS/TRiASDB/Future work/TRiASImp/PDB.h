//	Declaration der PDB
//
//	Verwaltung der Klassenidentifikatoren und Merkmalsidentifikatoren.

class CPDB
{
	CMapStringToString	m_mapIdKurzText;
	CMapStringToString	m_mapIdLangText;
	CMapStringToString	m_mapMkKurzText;
	CMapStringToString	m_mapMkLangText;
	long				m_lIdBase;
	long				m_lMkBase;

public:
						CPDB();
						~CPDB();

	void				Reset();
	long&				IdBase();
	long&				MkBase();
	BOOL				GetIdentTexte( const char*, CString&, CString& );
	BOOL				GetMerkmalTexte( const char*, CString&, CString& );
	BOOL				SetIdentTexte( const char*, const char*, const char* );
	BOOL				SetMerkmalTexte( const char*, const char*, const char* );
};

inline long& CPDB::IdBase()
{	return m_lIdBase;
}

inline long& CPDB::MkBase()
{	return m_lMkBase;
}
