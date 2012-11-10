// string standard header 
#ifndef _TSTRING_
#define _TSTRING_

#include <defines.hpp>
#include <exceptio.hpp>

// class string
class string {
public:
	string (void) { _Tidy(); }
	string (size_t _N, capacity _C) 
		{ _Tidy(), m_iRes = _N;
		if (_C == default_size) assign ('\0', _N); }
	string (const string &_X, size_t _P = 0, size_t _N = NPOS)
		{ _Tidy(), assign (_X, _P, _N); }
	string (const char *_S, size_t _N = NPOS)
		{ _Tidy(), assign (_S, _N); }
	string (char _C, size_t _N = 1)
		{ _Tidy(), assign (_C, _N); }
	string (unsigned char _C, size_t _N = 1)
		{ _Tidy(), assign ((char)_C, _N); }
#if _HAS_SIGNED_CHAR
	string (signed char _C, size_t _N = 1)
		{ _Tidy(), assign ((char)_C, _N); }
#endif // _HAS_SIGNED_CHAR
	~string (void) { _Tidy (1); }
	
	string &append (const string &, size_t = 0, size_t = NPOS);
	string &append (const char *, size_t = NPOS);
	string &append (char, size_t = 1);

	string &assign (const string &, size_t = 0, size_t = NPOS);
	string &assign (const char *, size_t = NPOS);
	string &assign (char, size_t = 1);

	string &insert (size_t, const string &, size_t = 0, size_t = NPOS);
	string &insert (size_t, const char *, size_t = NPOS);
	string &insert (size_t, char, size_t = 1);

	string &replace (size_t, size_t, const string &, size_t = 0, size_t = NPOS);
	string &replace (size_t, size_t, const char *, size_t = NPOS);
	string &replace (size_t, size_t, char, size_t = 1);

	string &operator= (const string &_X) { return (assign (_X)); }
	string &operator= (const char *_S) { return (assign (_S)); }
	string &operator= (char _C) { return (assign (_C)); }

	string &operator+= (const string &_X) { return (append (_X)); }
	string &operator+= (const char *_S) { return (append (_S)); }
	string &operator+= (char _C) { return (append (_C)); }

	char get_at (size_t) const;
	void put_at (size_t, char);
	char operator[] (size_t _N) const { return (m_pPtr[_N]); }
	char &operator[] (size_t _N) { return (m_pPtr[_N]); }

	const char *c_str (void) const { return m_pPtr != 0 ? m_pPtr : ""; }
	size_t length (void) const { return (m_iLen); }
	string &remove (size_t = 0, size_t = NPOS);
	void resize (size_t _N, char _C = 0)
		{ _N <= m_iLen ? remove (_N) : append (_C, _N - m_iLen); }
	size_t adjustlen (void)
		{ size_t n = strlen(m_pPtr); if (n < m_iLen) remove(n); return n; }
	size_t reserve (void) const { return (m_iRes); }
	void reserve (size_t _N) { if (m_pPtr == 0) m_iRes = _N; }
	size_t copy (char *, size_t, size_t = 0);

	size_t find (const string &_X, size_t _P = 0) const
		{ return (find (_X.c_str(), _P, _X.length())); }
	size_t find (const char *_S, size_t _P = 0, size_t _N = NPOS) const;
	size_t find (char _C, size_t _P = 0) const
		{ return (find ((const char *)&_C, _P, 1)); }

	size_t rfind (const string &_X, size_t _P = NPOS) const
		{ return (rfind (_X.c_str(), _P, _X.length())); }
	size_t rfind (const char *_S, size_t _P = NPOS, size_t _N = NPOS) const;
	size_t rfind (char _C, size_t _P = NPOS) const
		{ return (rfind ((const char *)&_C, _P, 1)); }

	size_t find_first_of (const string &_X, size_t _P = 0) const
		{ return (find_first_of (_X.c_str(), _P, _X.length())); }
	size_t find_first_of (const char *_S, size_t _P = 0, size_t _N = NPOS) const;
	size_t find_first_of (char _C, size_t _P = 0) const
		{ return (find ((const char *)&_C, _P, 1)); }

	size_t find_last_of (const string &_X, size_t _P = NPOS) const
		{ return (find_last_of (_X.c_str(), _P, _X.length())); }
	size_t find_last_of (const char *_S, size_t _P = NPOS, size_t _N = NPOS) const;
	size_t find_last_of (char _C, size_t _P = NPOS) const
		{ return (rfind ((const char *)&_C, _P, 1)); }

	size_t find_first_not_of (const string &_X, size_t _P = 0) const
		{ return (find_first_not_of (_X.c_str(), _P, _X.length())); }
	size_t find_first_not_of(const char *_S, size_t _P = 0, size_t _N = NPOS) const;
	size_t find_first_not_of(char _C, size_t _P = 0) const
		{ return (find_first_not_of ((const char *)&_C, _P, 1)); }
	
	size_t find_last_not_of (const string &_X, size_t _P = NPOS) const
		{ return (find_last_not_of (_X.c_str(), _P, _X.length())); }
	size_t find_last_not_of (const char *_S, size_t _P = NPOS, size_t _N = NPOS) const;
	size_t find_last_not_of (char _C, size_t _P = NPOS) const
		{ return (find_last_not_of ((const char *)&_C, _P, 1)); }
		
	string substr (size_t _P = 0, size_t _N = NPOS) const
		{ return (string (*this, _P, _N)); }
		
	int compare (const string &, size_t = 0, size_t = NPOS) const;	
	int compare (const char *, size_t = 0, size_t = NPOS) const;	
	int compare (char, size_t = 0, size_t = 1) const;	
	
private:
	bool _Grow (size_t, bool = 0);
	void _Tidy (bool = 0);
	void _Xlen (void) const { lengtherror("string too long").raise(); }
	void _Xran (void) const { outofrange("invalid string position").raise(); }
	char *m_pPtr;
	size_t m_iLen, m_iRes;
};
inline string operator+ (const string &_L, const string &_R) 
	{ return (string(_L) += _R); }
inline string operator+ (const char *_L, const string &_R) 
	{ return (string(_L) += _R); }
inline string operator+ (char _L, const string &_R) 
	{ return (string(_L) += _R); }
inline string operator+ (const string &_L, const char *_R) 
	{ return (string(_L) += _R); }
inline string operator+ (const string &_L, char _R) 
	{ return (string(_L) += _R); }

inline bool operator== (const string &_L, const string &_R)
	{ return (_L.compare(_R) == 0); }
inline bool operator== (const char *_L, const string &_R)
	{ return (_R.compare(_L) == 0); }
inline bool operator== (char _L, const string &_R)
	{ return (_R.compare(_L) == 0); }
inline bool operator== (const string &_L, const char *_R)
	{ return (_L.compare(_R) == 0); }
inline bool operator== (const string &_L, char _R)
	{ return (_L.compare(_R) == 0); }

inline bool operator!= (const string &_L, const string &_R)
	{ return (!(_L == _R)); }
inline bool operator!= (const char *_L, const string &_R)
	{ return (!(_L == _R)); }
inline bool operator!= (char _L, const string &_R)
	{ return (!(_L == _R)); }
inline bool operator!= (const string &_L, const char *_R)
	{ return (!(_L == _R)); }
inline bool operator!= (const string &_L, char _R)
	{ return (!(_L == _R)); }

#if defined(_INC_IOS)	// nur wenn iostream.h einbezogen wurde
istream & operator>> (istream &, string&);
istream & getline(istream &, string &, char = '\n');
inline ostream & operator<< (ostream &_O, const string & _X)
	{ return (_O.write(_X.c_str(), _X.length())); }
#endif

#endif // _TSTRING_
