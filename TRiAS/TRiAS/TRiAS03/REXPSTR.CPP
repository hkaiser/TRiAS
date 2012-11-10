// Regular expressions --------------------------------------------------------
// File: REXPSTR.CPP

#include "stdafx.h"

#include <rexpstr.h>

#define	CNUL	'\0'

#define	CBRA	0x02				// 0x02 0000 0010
#define	CCHR	0x04				// 0x04 0000 0100
#define	CDOT	0x08				// 0x08 0000 1000
#define	CCL	0x0c				// 0x0c 0000 0110
#define	CDOL	0x14				// 0x14 0001 0010
#define	CCEOF	0x16				// 0x16 0001 0110
#define	CKET	0x18				// 0x18 0001 1000
#define	CBACK	0x24				// 0x24 0010 0100

#define	STAR	0x01				// 0x01 0000 0001
#define RNGE	0x03				// 0x03 0000 0011

static	BYTE	bittab[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

#define PLACE(c)		m_pszExprBufCurr[(BYTE)c>>3]|=bittab[(BYTE)c&0x07]
#define ISTHERE(eBuf,c)	(eBuf[(BYTE)c>>3]&bittab[(BYTE)c&0x07])

CRegExpString::CRegExpString ()
{
	Setup ();
}

CRegExpString::CRegExpString (const char * instring, char seof, bool fMatchCase)
{
	Setup ();
	Compile (instring, seof, fMatchCase);
}

CRegExpString::~CRegExpString ()
{
	Clear ();
}

void
CRegExpString::Setup ()
{
	m_pszExprBuf = NULL;
	m_pszBrackSList = NULL;
	m_pszBrackEList = NULL;
}

bool
CRegExpString::Initialize (bool fMatchCase)
{
	try {
		m_pszBrackSList = (char **) new char[ NBRA * sizeof (char *) ];
		m_pszBrackEList = (char **) new char[ NBRA * sizeof (char *) ];
		m_pszExprBuf = (BYTE *) new char[ NEXPR ];
	} catch (...) {
		return false;
	}

	m_pszExprBuf[0] = '\0';
	m_pszExprBufCurr = m_pszExprBuf;
	m_pszExprBufEnd = &m_pszExprBuf[ NEXPR ];
	m_bIsSed = false;
	m_bIsNoDelim = false;
	m_bIsCircf = false;
	m_nEof = DEF_EOF;
	m_nRegErr = 0;
	m_pszRegErr = NULL;

	m_fMatchCase = fMatchCase;

	return true;
}

void
CRegExpString::Clear ()
{
	if (m_pszExprBuf != NULL) delete[] m_pszExprBuf;
	if (m_pszBrackSList != NULL) delete[] m_pszBrackSList;
	if (m_pszBrackEList != NULL) delete[] m_pszBrackEList;
}

bool
CRegExpString::Compile (const char *instring, char seof, bool fMatchCase)
{

#define	GETC()		 ((!fMatchCase && isupper(*sp))?tolower(*sp++):(*sp++))
#define	PEEKC()		 ((!fMatchCase && isupper(*sp))?tolower(*sp):(*sp))
#define	UNGETC()	 (--sp)
#define	REXERROR(n)	{ \
		m_nRegErr = n; \
		m_pszRegErr = (sp == instring) ? sp : sp - 1; \
		return false; \
	}

	char	*sp;
	char	c;
	char	lc;
	BYTE	*lastep;
	int	cclcnt;
	BYTE	bracket[NBRA];
	BYTE	*bracketp;
	int	closed;
	int	i;
	int	n_Brackets;
	int	n_ClosedBrack;

	bool	neg;
	bool	commaFlag;

	Clear ();
	if (!Initialize (fMatchCase))
		return false;

	lastep = NULL;
	sp = (char*) instring;
	m_nEof = seof;

	c = GETC();
	if (c == m_nEof || c == '\n')
	{
		if (c == '\n')
		{
			UNGETC();
			m_bIsNoDelim = true;
		}
		if (*m_pszExprBufCurr == '\0' && !m_bIsSed)
			REXERROR(41);
	}
	bracketp = bracket;
	closed = n_Brackets = n_ClosedBrack = 0;
	if (c == '^')
		m_bIsCircf = true;
	else
		UNGETC();
	while (1)
	{
		if (m_pszExprBufCurr >= m_pszExprBufEnd)
			REXERROR(50);
		c = GETC();
		if (c != '*' &&  ( (c != '\\') ||  (PEEKC () != '{')))
			lastep = m_pszExprBufCurr;
		if (c == m_nEof)
		{
			*m_pszExprBufCurr++ = CCEOF;
			return true;
		}

		switch (c)
		{
		case '.':
			*m_pszExprBufCurr++ = CDOT;
			continue;

		case '\n':
			if (!m_bIsSed)
			{
				UNGETC();
				*m_pszExprBufCurr++ = CCEOF;
				m_bIsNoDelim = true;
				return true;
			}
			else
				REXERROR(36);

		case '*':
			if (lastep == NULL || *lastep == CBRA || *lastep == CKET)
				goto _lbl_defchar;
			*lastep |= STAR;
			continue;

		case '$':
			if (PEEKC () != m_nEof && PEEKC () != '\n')
				goto _lbl_defchar;
			*m_pszExprBufCurr++ = CDOL;
			continue;

		case '[':
			if (&m_pszExprBufCurr[17] >= m_pszExprBufEnd)
				REXERROR(50);

			*m_pszExprBufCurr++ = CCL;
			lc = '\0';
			for (i = 0; i < 16; i++)
				m_pszExprBufCurr[i] = 0x00;

			neg = false;
			if ( (c = GETC()) == '^')
			{
				neg = true;
				c = GETC();
			}

			do
			{
				if (c == '\0' || c == '\n')
					REXERROR(49);
				if (c == '-' && lc != '\0')
				{
					if ( (c = GETC()) == ']')
					{
						PLACE ('-');
						break;
					}
					while (lc < c)
					{
						PLACE (lc);
						lc++;
					}
				}
				lc = c;
				PLACE (c);
			} while ( (c = GETC()) != ']');
			if (neg == true)
			{
				for (cclcnt = 0; cclcnt < 16; cclcnt++)
					m_pszExprBufCurr[cclcnt] ^= 0xff;
				m_pszExprBufCurr[0] &= 0376;
			}
			m_pszExprBufCurr += 16;
			continue;

		case '\\':						// handles the special characters
			switch (c = GETC())
			{
			case '(':
				if (n_Brackets >= NBRA)
					REXERROR(43);
				*bracketp++ = (char) n_Brackets;
				*m_pszExprBufCurr++ = CBRA;
				*m_pszExprBufCurr++ = (char) n_Brackets++;
				continue;

			case ')':
				if (bracketp <= bracket || ++n_ClosedBrack != n_Brackets)
					REXERROR(42);
				*m_pszExprBufCurr++ = CKET;
				*m_pszExprBufCurr++ = *--bracketp;
				closed++;
				continue;

			case '{':
				if (lastep == NULL)
					goto _lbl_defchar;
				*lastep |= RNGE;
				commaFlag = false;
_lbl_nlim:
				c = GETC();
				i = 0;
				do
				{
					if (c >= '0' && c <= '9')
						i = 10 * i + c - '0';
					else
						REXERROR(16);
				} while ( ( (c = GETC()) != '\\') &&  (c != ','));
				if (i > 255)
					REXERROR(11);
				*m_pszExprBufCurr++ = (char) i;
				if (c == ',')
				{
					if (commaFlag == true)
						REXERROR(44);
					commaFlag = true;
					if ( (c = GETC()) == '\\')
						*m_pszExprBufCurr++ = 255;
					else
					{
						UNGETC();
						goto _lbl_nlim;			// get 2'nd number
					}
				}
				if (GETC() != '}')
					REXERROR(45);
				if (commaFlag == false)		// one number
					*m_pszExprBufCurr++ = (char) i;
				else
					if ( (m_pszExprBufCurr[-1] & 0377) <
						 (m_pszExprBufCurr[-2] & 0377)
						)
					REXERROR(46);
				continue;

			case '\n':
				REXERROR(36);

			case 'n':
				c = '\n';
				goto _lbl_defchar;

			default:
				if (c >= '1' && c <= '9')
				{
					if ((int)  (c -= '1') >= closed)
						REXERROR(25);
					*m_pszExprBufCurr++ = CBACK;
					*m_pszExprBufCurr++ = c;
					continue;
				}
			}

_lbl_defchar:		// Drop through to default to use \ to turn off special chars
		default:
			lastep = m_pszExprBufCurr;
			*m_pszExprBufCurr++ = CCHR;
			*m_pszExprBufCurr++ = c;
		}
	}
	return true;
}

bool
CRegExpString::Compare (const char * string, bool fSubMatch)
{
char	c;

	m_fSubMatch = fSubMatch;

	m_pszStart = (char*) string;
	m_pszMatchStart = NULL;

	if (Error ())
		return false;
	if (m_bIsCircf)
	{
		m_pszMatchStart = (char*) string;
		return (Advance (string, m_pszExprBuf));
	}
	if (*m_pszExprBuf == CCHR)				// fast check for first character */
	{
		c = m_pszExprBuf[1];
		do
		{
			if (m_fMatchCase) {
				if (*string != c)
					continue;
			} else {
			int c1 = isupper(*string) ? tolower(*string) : *string;

				if (c1 != c)
					continue;
			}
			if (Advance (string, m_pszExprBuf))
			{
				m_pszMatchStart = (char*) string;
				return true;
			}
		} while (*string++);
		return false;
	}
	do							// regular algorithm */
	{
		if (Advance (string, m_pszExprBuf))
		{
			m_pszMatchStart = (char*) string;
			return true;
		}
	} while (*string++);

return false;
}

bool
CRegExpString::Advance (const char *lp, BYTE *exprBuf)
{
#define	GET_LOWER(c) ((!m_fMatchCase && isupper(c)) ? tolower(c) : (c))

char *curlp;
char c;
char *bbeg;
int ct;

	while (1)
	{
		switch (*exprBuf++)
		{
		case CCHR:
			if (GET_LOWER(*lp) == (char) *exprBuf++) {
				lp++;
				continue;
			}
			return false;

		case CDOT:
			if (*lp++)
				continue;
			return false;

		case CDOL:
			if (*lp == '\0')
				return true;
			else
				return false;

//			if (*lp == '\0')
//				continue;		// ???
//			return false;

		case CCEOF:
			if (*lp == m_nEof || m_fSubMatch)
			{
				m_pszMatchEnd = (char*) lp;
				return true;
			}
			return false;

		case CCL:
			c = (char)(GET_LOWER(*lp) & 0177);
			lp++;
			if (ISTHERE (exprBuf, c))
			{
				exprBuf += 16;
				continue;
			}
			return false;

		case CBRA:
			m_pszBrackSList[*exprBuf++] = (char*) lp;
			continue;

		case CKET:
			m_pszBrackEList[*exprBuf++] = (char*) lp;
			continue;

		case CCHR|RNGE:
			c = *exprBuf++;
			GetRange (exprBuf);
			while (m_nLow--) {
				if (GET_LOWER(*lp) != c)
					return false;
				lp++;
			}
			curlp = (char*) lp;
			while (m_nSize--) {
				if (GET_LOWER(*lp) != c) {
					lp++;
					break;
				}
				lp++;
			}
			if (m_nSize < 0)
				lp++;
			exprBuf += 2;
			goto _lbl_star;

		case CDOT|RNGE:
			GetRange (exprBuf);
			while (m_nLow--) 
				if (*lp++ == '\0')
					return false;
			curlp = (char*) lp;
			while (m_nSize--) 
				if (*lp++ == '\0')
					break;
			if (m_nSize < 0)
				lp++;
			exprBuf += 2;
			goto _lbl_star;

		case CCL|RNGE:
			GetRange (exprBuf + 16);
			while (m_nLow--)
			{
				c = (char) (GET_LOWER(*lp) & 0x7f);
				lp++;
				if (!ISTHERE (exprBuf, c))
					return false;
			}
			curlp = (char*) lp;
			while (m_nSize--)
			{
				c = (char) (GET_LOWER(*lp) & 0x7f);
				lp++;
				if (!ISTHERE (exprBuf, c))
					break;
			}
			if (m_nSize < 0)
				lp++;
			exprBuf += 18;				// 16 ... CCL - Table, 2 ... Range
			goto _lbl_star;

		case CBACK:
			bbeg = m_pszBrackSList[ *exprBuf ];
			ct = m_pszBrackEList[ *exprBuf++ ] - bbeg;

			if (Ecmp (bbeg, (char*) lp, ct))
			{
				lp += ct;
				continue;
			}
			return false;

		case CBACK|STAR:
			bbeg = m_pszBrackSList[ *exprBuf ];
			ct = m_pszBrackEList[ *exprBuf++ ] - bbeg;
			curlp = (char*) lp;
			while (Ecmp (bbeg, (char*) lp, ct))
				lp += ct;

			while (lp >= curlp)
			{
				if (Advance (lp, exprBuf))
					return true;
				lp -= ct;
			}
			return false;

		case CDOT|STAR:
			curlp = (char*) lp;
			while (*lp++)
				;
			goto _lbl_star;

		case CCHR|STAR:
			curlp = (char*) lp;
			while (GET_LOWER(*lp) == (char) *exprBuf)
				lp++;
			lp++;
			exprBuf++;
			goto _lbl_star;

		case CCL|STAR:
			curlp = (char*) lp;
			do
			{
				c = (char) (GET_LOWER(*lp) & 0x7f);
				lp++;
			} while (ISTHERE (exprBuf, c));
			exprBuf += 16;
			goto _lbl_star;

_lbl_star:
			do
			{
				if (--lp == m_pszStart)
					break;
				if (Advance (lp, exprBuf))
					return true;
			} while (lp > curlp);
			return false;
		}
	}
}

void
CRegExpString::GetRange (BYTE * exprBuf)
{
	m_nLow = (int)(*exprBuf++ & 0x7f);
	m_nSize = (int)(*exprBuf == 0xff ? 20000 : (*exprBuf & 0x7f) - m_nLow);
}

bool
CRegExpString::Ecmp (char * a,	char * b, int count)
{
	while (count--) {
		if (*a++ != GET_LOWER(*b))
			return false;
		b++;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Index: Finden des ersten Vorkommens eines REX in einem String
char *CRegExpString :: Index (char *pStr, char **pLast)
{
	if (pLast) *pLast = NULL;

	while (!Compare (pStr, true)) {		// Substring finden
		if (*++pStr == m_nEof)
			return NULL;	// nichts gefunden
	}

	if (pLast) *pLast = MatchEnd();

return Matched();
}

#ifdef	_DEBUG_REGEXP

#include	<iostream.h>

void
CRegExpString::Dump ()
{
	BYTE	*cp;

	if (Error ())
		return;
	for (cp = m_pszExprBuf; cp != m_pszExprBufCurr;)
	{
		hex (cerr);
		cerr.width (2);
		cerr.fill ('0');
		cerr <<  ((int) *cp);

		cerr.width (15);
		cerr.fill (' ');

		switch (*cp++)
		{
		case CBRA	:	cerr << " CBRA"; break;
		case CCHR	:	cerr << " CCHR"; DumpCCHR (cp); break;
		case CDOT	:	cerr << " CDOT"; break;
		case CCL	:	cerr << " CCL"; DumpCCL (cp); break;
		case CDOL	:	cerr << " CDOL"; break;
		case CCEOF	:	cerr << " CCEOF"; break;
		case CKET	:	cerr << " CKET"; break;
		case CBACK	:	cerr << " CBACK"; break;

		case CBRA  | STAR :	cerr << " CBRA | STAR"; break;
		case CCHR  | STAR :	cerr << " CCHR | STAR"; DumpCCHR (cp); break;
		case CDOT  | STAR :	cerr << " CDOT | STAR"; break;
		case CCL   | STAR :	cerr << " CCL | STAR"; DumpCCL (cp); break;
		case CDOL  | STAR :	cerr << " CDOL | STAR"; break;
		case CCEOF | STAR :	cerr << " CCEOF | STAR"; break;
		case CKET  | STAR :	cerr << " CKET | STAR"; break;
		case CBACK | STAR :	cerr << " CBACK | STAR"; break;

		case CCHR  | RNGE :
			cerr << " CCHR | RNGE"; DumpCCHR (cp); DumpRange (cp); break;
		case CDOT  | RNGE :
			cerr << " CDOT | RNGE"; DumpRange (cp); break;
		case CCL   | RNGE :
			cerr << " CCL | RNGE"; DumpCCL (cp); DumpRange (cp); break;
		}
		cerr << endl;
	}
}

void
CRegExpString::DumpCCHR (BYTE*& cp)
{
	cerr << ' ' << *cp++;
}

void
CRegExpString::DumpCCL (BYTE*& cp)
{
	hex (cerr);
	cerr.fill ('0');

	for (int i = 0; i < 16; i++)
	{
		cerr << ' ';
		cerr.width (2);
		cerr <<  ((int) *cp++);
	}
}

void
CRegExpString::DumpRange (BYTE*& cp)
{
	dec (cerr);
	cerr.fill (' ');
	cerr.width (4); cerr <<  ((int) *cp++) << ',';
	cerr.width (4); cerr <<  ((int) *cp++);
}

#endif
