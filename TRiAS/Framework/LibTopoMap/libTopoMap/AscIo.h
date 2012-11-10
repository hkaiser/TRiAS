#ifndef __ASC_IO_H__
#define __ASC_IO_H__

/////////////////////////////////////////////////////////////////////////////
// ASC-File-Export

void WriteAscHeader( iostream& os, ASC_HEADER *pHeader );
void WriteAscTrailer( iostream& os );

struct tagASCRECORDINFO {
	LPCTSTR	pszEntryName;
	LPCTSTR	pszEntryText;
	int		iBase;
	int		iVersion;
	DWORD	dval;
	long	lval1;
	long	lval2;
	double	x;
	double	y;
};

const int nMaxAscLineLength = 256;		// including terminating NUL
const int nMaxMCodeLineLength = 69;

IOMANIPdeclare(tagASCRECORDINFO);

// ASC[?]R :
//  H - (H)eaderrecord
//  I - (I)dentrecord
//  C - (C)oordrecord
//  M - (M)Coderecord
//	T - Commen(t)record

OMANIP(tagASCRECORDINFO)	ASCHR( LPCTSTR pszHdrEntry, LPCTSTR pszEntryText = NULL );
OMANIP(tagASCRECORDINFO)	ASCHR( LPCTSTR pszHdrEntry, long lValue, int iBase = 10 );
OMANIP(tagASCRECORDINFO)	ASCIR( DWORD ident, long recno, long nPoints, int iBase = 10, int version = 5 );
OMANIP(tagASCRECORDINFO)	ASCMR( DWORD mCode, LPCTSTR pszRecordText, int iBase = 10 );
OMANIP(tagASCRECORDINFO)	ASCCR( double x, double y );
OMANIP(tagASCRECORDINFO)	ASCTR( LPCTSTR pszComment );

/////////////////////////////////////////////////////////////////////////////
// Parser für ASC - Dateien 

struct ASC_PARSERMAP_ENTRY;
class CAscParserBase;

#ifndef ASC_PARSERCALL
#define ASC_PARSERCALL
#endif
typedef void (ASC_PARSERCALL CAscParserBase::*ASC_PARSERFUNC)(void);

struct ASC_PARSERMAP {
#ifdef _AFXDLL
	const ASC_PARSERMAP* (PASCAL* pfnGetBaseMap)();
#else
	const ASC_PARSERMAP* pBaseMap;
#endif
	const ASC_PARSERMAP_ENTRY* lpEntries;
};

#ifdef _AFXDLL
#define	DECLARE_ASC_PARSERMAP( ) \
private: \
	static const ASC_PARSERMAP_ENTRY _mapEntries[]; \
protected: \
	static AFX_DATA const ASC_PARSERMAP parserMap; \
	static const ASC_PARSERMAP* PASCAL _GetBaseParserMap(); \
	virtual const ASC_PARSERMAP* GetParserMap() const; \

#else
#define	DECLARE_ASC_PARSERMAP( ) \
private: \
	static const ASC_PARSERMAP_ENTRY _mapEntries[]; \
protected: \
	static AFX_DATA const ASC_PARSERMAP parserMap; \
	virtual const ASC_PARSERMAP* GetParserMap() const; \

#endif

#ifdef _AFXDLL
#define BEGIN_ASC_PARSERMAP( theClass, baseClass ) \
	const ASC_PARSERMAP* PASCAL theClass::_GetBaseParserMap() \
		{ return &theClass::parserMap; } \
	const ASC_PARSERMAP* theClass::GetParserMap() const \
		{ return &theClass::parserMap; } \
	AFX_DATADEF const ASC_PARSERMAP theClass::parserMap = \
		{ &theClass::_GetBaseParserMap, &theClass::_mapEntries[0] }; \
	const ASC_PARSERMAP_ENTRY theClass::_mapEntries[] = \
		{ \

#else
#define BEGIN_ASC_PARSERMAP( theClass, baseClass ) \
	const ASC_PARSERMAP* theClass::GetParserMap() const \
		{ return &theClass::parserMap; } \
	AFX_DATADEF const ASC_PARSERMAPtheClass::parserMap = \
		{ &baseClass::parserMap, &theClass::_mapEntries[0] }; \
	const ASC_PARSERMAP_ENTRY theClass::_mapEntries[] = \
		{ \

#endif

#define	END_ASC_PARSERMAP() \
	{ NULL, 0, (ASC_PARSERFUNC) NULL } \
	};

enum AscTagType {
	AscTag_vs,			// void (LPCTSTR)
	AscTag_vss,			// void (LPCTSTR,LPCTSTR)
	AscTag_vwwi,		// void (DWORD,DWORD,int)
	AscTag_vws,			// void (DWORD,LPCTSTR)
	AscTag_vdd,			// void (double,double)
};

#define ON_HEADLINE( memberFxn ) \
	{ "H", AscTag_vs, (ASC_PARSERFUNC) (void (ASC_PARSERCALL CAscParserBase::*)(LPCTSTR)) &memberFxn },
#define ON_COMMENT( memberFxn ) \
	{ ";", AscTag_vs, (ASC_PARSERFUNC) (void (ASC_PARSERCALL CAscParserBase::*)(LPCTSTR)) &memberFxn },
#define ON_PDB_ENTRY( memberFxn ) \
	{ "D", AscTag_vss, (ASC_PARSERFUNC) (void (ASC_PARSERCALL CAscParserBase::*)(LPCTSTR,LPCTSTR)) &memberFxn },
#define ON_PROJPDB_ENTRY( memberFxn ) \
	{ "Entry", AscTag_vss, (ASC_PARSERFUNC) (void (ASC_PARSERCALL CAscParserBase::*)(LPCTSTR,LPCTSTR)) &memberFxn },
#define ON_SYSPDB_ENTRY( memberFxn ) \
	{ "EntryRoSys", AscTag_vss, (ASC_PARSERFUNC) (void (ASC_PARSERCALL CAscParserBase::*)(LPCTSTR,LPCTSTR)) &memberFxn },

#define ON_POINT( memberFxn ) \
	{ "P", AscTag_vwwi, (ASC_PARSERFUNC) (void (ASC_PARSERCALL CAscParserBase::*)(DWORD,DWORD,int)) &memberFxn },
#define ON_LINE( memberFxn ) \
	{ "L", AscTag_vwwi, (ASC_PARSERFUNC) (void (ASC_PARSERCALL CAscParserBase::*)(DWORD,DWORD,int)) &memberFxn },
#define ON_AREA( memberFxn ) \
	{ "F", AscTag_vwwi, (ASC_PARSERFUNC) (void (ASC_PARSERCALL CAscParserBase::*)(DWORD,DWORD,int)) &memberFxn },
#define ON_BOBJECT( memberFxn ) \
	{ "B", AscTag_vwwi, (ASC_PARSERFUNC) (void (ASC_PARSERCALL CAscParserBase::*)(DWORD,DWORD,int)) &memberFxn },

#define ON_REFERENZ( memberFxn ) \
	{ "R", AscTag_vws, (ASC_PARSERFUNC) (void (ASC_PARSERCALL CAscParserBase::*)(DWORD,LPCTSTR)) &memberFxn },
#define ON_MCODE( memberFxn ) \
	{ "M", AscTag_vws, (ASC_PARSERFUNC) (void (ASC_PARSERCALL CAscParserBase::*)(DWORD,LPCTSTR)) &memberFxn },
#define ON_COORD( memberFxn ) \
	{ "G", AscTag_vdd, (ASC_PARSERFUNC) (void (ASC_PARSERCALL CAscParserBase::*)(double,double)) &memberFxn },

class CAscParserBase : public CObject {
private:
	long		m_nChars;		// aktuelle Zeichenposition
	long		m_nLine;		// aktuelle Zeile
	istream*	m_pIs;
public:
	typedef enum {
		W_MISSINGQUOTE,
		W_UNEXPECTED_EOL,
		W_UNEXPECTED_COORD,
		W_UNEXPECTED_TOKEN,
		W_INVALID_CHARCOUNT,
		W_INVALID_COORDCOUNT
	} PARSERWARN;
	typedef enum {
		E_BADINPUT,
		E_INTERNAL,
		E_FATAL
	} PARSERERROR;

protected:
	int		CharPos();
	int		LinePos();
	virtual void	Warning( PARSERWARN wrn, int line, LPCTSTR restLine );
	virtual void	Error( PARSERERROR err, int line, LPCTSTR restLine );
	DWORD	strtol( LPCTSTR lpszString, int base = 10 );
	DWORD	strtol( LPCTSTR lpszStart, LPCTSTR lpszEnd, int base = 10 );

public:
	CAscParserBase();
	virtual ~CAscParserBase();

	virtual void Attach( istream& is );
	virtual BOOL Parse( );

protected:
	DECLARE_ASC_PARSERMAP()
};

inline int CAscParserBase::CharPos()
	{ return m_nChars; }
inline int CAscParserBase::LinePos()
	{ return m_nLine; }

struct ASC_PARSERMAP_ENTRY {
	LPCTSTR			ap_TagName;
	UINT			ap_Sig;
	ASC_PARSERFUNC	ap_TagFunc;
};

union ParserMapFunctions {
	ASC_PARSERFUNC	pfn;
	void (ASC_PARSERCALL CAscParserBase::*pfn_vs)(LPCTSTR);
	void (ASC_PARSERCALL CAscParserBase::*pfn_vss)(LPCTSTR,LPCTSTR);
	void (ASC_PARSERCALL CAscParserBase::*pfn_vwwi)(DWORD,DWORD,int);
	void (ASC_PARSERCALL CAscParserBase::*pfn_vws)(DWORD,LPCTSTR);
	void (ASC_PARSERCALL CAscParserBase::*pfn_vdd)(double,double);
};

/*************************************************************
  generische Parserfunktionen / -Map
	void OnComment( LPCTSTR lpszComment );
	void OnHeadline( LPCTSTR lpszHeadline );
	void OnPdbEntry( LPCTSTR lpszEntryName, LPCTSTR lpszEntryValue );
	void OnProjPdbEntry( LPCTSTR lpszEntryName, LPCTSTR lpszEntryValue );
	void OnSysPdbEntry( LPCTSTR lpszEntryName, LPCTSTR lpszEntryValue );
	void OnIdent( DWORD dwIdent, DWORD dwObjectNumber, int nCoords );
	void OnMCode( DWORD dwMCode, LPCTSTR lpszValue );
	void OnCoord( double X, double Y );

void CAscParser::OnComment( LPCTSTR lpszComment )
{}
void CAscParser::OnHeadline( LPCTSTR lpszHeadline )
{}
void CAscParser::OnPdbEntry( LPCTSTR lpszEntryName, LPCTSTR lpszEntryValue )
{}
void CAscParser::OnProjPdbEntry( LPCTSTR lpszEntryName, LPCTSTR lpszEntryValue )
{}
void CAscParser::OnSysPdbEntry( LPCTSTR lpszEntryName, LPCTSTR lpszEntryValue )
{}
void CAscParser::OnIdent( DWORD dwIdent, DWORD dwObjectNumber, int nCoords )
{}
void CAscParser::OnMCode( DWORD dwMCode, LPCTSTR lpszValue )
{}
void CAscParser::OnCoord( double X, double Y )
{}

BEGIN_ASC_PARSERMAP(CAscParser,CAscParserBase)
	ON_HEADLINE( OnHeadline )
	ON_COMMENT( OnComment )
	ON_PDB_ENTRY( OnPdbEntry )
	ON_PROJPDB_ENTRY( OnProjPdbEntry )
	ON_SYSPDB_ENTRY( OnSysPdbEntry )
	ON_IDENT( OnIdent )
	ON_MCODE( OnMCode )
	ON_COORD( OnCoord )
END_ASC_PARSERMAP()
***************************************************************/

#endif // __ASC_IO_H__
