// Regular expressions --------------------------------------------------------
// File: REXPSTR.H

#if !defined(_REXPSTR_H)
#define _REXPSTR_H

/////////////////////////////////////////////////////////////////////
//	CRegExpString
//	-	supports string matching with regular expressions
/////////////////////////////////////////////////////////////////////

#define	NBRA	9
#define	NEXPR	256 			// max. size of compiled regex - string

#define DEF_EOF '\0'			// default EOF - character

class	CRegExpString 
#if defined(__MFC__)
	: public CObject
#endif
{
private:
	BYTE *	m_pszExprBuf;		// buffer for compiled expr - string
	BYTE *	m_pszExprBufEnd;	// end of buffer
	BYTE *	m_pszExprBufCurr;	// current position in compiled expr - string
	char **	m_pszBrackSList;	// list of opened brackets
	char **	m_pszBrackEList;	// list of closed brackets
	int	m_nRegErr;
	char *	m_pszRegErr;
	bool	m_bIsSed;		// 'sed(1)' use this Class
	bool	m_bIsCircf;		// expr. string starts with circumflex '^'
	bool	m_bIsNoDelim;		// expr. string has no delimiter
	char	m_nEof;			// EOF - marker for expr. - string
	int	m_nLow;
	int	m_nSize;

	void	Setup (void);
	bool	Initialize (bool fMatchCase);
	void	Clear (void);

	bool	Advance (const char * string, BYTE * exprBuf);
	void	GetRange (BYTE * string);
	bool	Ecmp (char * str1, char * str2, int count);

	char *	m_pszStart;
	char *	m_pszMatchStart;
	char *	m_pszMatchEnd;

	bool	m_fSubMatch;		// nur bis Ende des RegExp testen
	bool	m_fMatchCase;

public:
	CRegExpString (void);
	CRegExpString (const char * instring, char seof = DEF_EOF, bool fMatchCase = true);
	~CRegExpString (void);

	bool	Compare (const char * string, bool fSubMatch = false);
	char *	Value (int nIndex);
	int	Error (void) { return m_nRegErr; }
	char *	ErrorPos (void) { return m_pszRegErr; }
	char *	Matched (void) { return m_pszMatchStart; }
	char *	MatchEnd (void) { return m_pszMatchEnd; }

	char *	Index (char *pStr, char **pLast = NULL);

	bool	Compile (const char * instring, char seof = DEF_EOF, bool fMatchCase = true);

#ifdef	_DEBUG_REGEXP
public:
	void	Dump (void);
protected:
	void	DumpCCHR (BYTE*& cp);
	void	DumpCCL (BYTE*& cp);
	void	DumpRange (BYTE*& cp);
	void	Fill (void);
#endif
};

#endif // _REXPSTR_H
