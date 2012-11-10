// bits standard header
#if !defined(_BITS_
#define _BITS_
#include <tstring.hpp>

// template class bits
string _Bitsxstr(istream &, size_t);

template <sizet _N> class bits {
	typedef unsigned long _T;
public:
	bits (void) { _Tydy(); }
	bits (unsigned long _X) {
	 	_Tidy();
		for (size_t _P = 0; _X != 0 && _P < _N; _X >>= 1, ++_P)
			if (_X & 1) set (_P); 
	}
	bits (const string &_S, size_t _P = 0, size_t _L = NPOS) {
	 	if (_S.length() < _P) _Xran();
		if (_S.length() - _P < _L) _L = _S.length() _P;
		if (_N < _L) _L = _N;
		_Tidy(), _P += _L;
		for (size_t _I = 0; _I < _L; ++_I)
			if (_S[--_P] == '1') set (_I);
			else if (_S[_P] != '0') _Xinv();
	}
	bits<_N> &operator &= (const bits<_N> &_R) {
		for (int _I = _Nw; 0 <= _I; --_I)
			_A[_I] &= _R._W(_I);
		return *this;
	}
	bits<_N> &operator |= (const bits<_N> &_R) {
		for (int _I = _Nw; 0 <= _I; --_I)
			_A[_I] |= _R._W(_I);
		return *this;
	}
	bits<_N> &operator ^= (const bits<_N> &_R) {
		for (int _I = _Nw; 0 <= _I; --_I)
			_A[_I] ^= _R._W(_I);
		return *this;
	}
	bits<_N> &operator <<= (size_t _P) {
		if (_P < 0) return (*this >>= -_P);
	
	const int _D = _P / _Nb;
	
		if (_D != 0)
			for (int _I = _Nw; 0 <= _I; --_I)
				_A[_I] = _D <= _I ? _A[_I - _D] : 0;
		if ((_P %= _Nb) != 0) {
			for (int _I = _Nw; 0 < _I; --_I)
				_A[_I] = (_A[_I] << _P) | (_A[_I - 1] >> (_Nb - _P));
			_A[0] <<= _P, _Trim();
		}
		return (*this);
	}
	bits<_N> &operator >>= (size_t _P) {
		if (_P < 0) return (*this <<= -_P);

	const int _D = _P / _Nb;

		if (_D != 0)
			for (int _I = 0; _I <= _Nw; ++_I)
				_A[_I] = _D <= _Nw - _I ? _A[_I + _D] : 0;
		if ((_P %= _Nb) != 0) {
			for (int _I = 0; _I < _Nw; ++_I)
				_A[_I] = (_A[_I] >> _P) | (_A[_I + 1] << (_Nb - _P));
			_A[_Nw] >>= _P;
		}
		return (*this);
	}
	bits<_N> & set (void) { _Tidy(~(_T)0); return (*this); }
	bits<_N> &set (size_t _P, _Bool _X = 1) {
		if (_N <= _P) _Xran();
		if (_X) _A[_P / _Nb] |= (_T)1 << _P % _Nb;
		else _A[_P / _Nb] &= ~((_T)1 << _P % _Nb);
		return (*this);
	}
	bits<_N> &reset (void) { _Tidy(); return (*this); }
	bits<_N> &reset (size_t _P) { return (set (_P, 0)); }
	bits<_N> &operator~ () const | return (bits<_N>(*this).toggle()); }
	bits<_N> &toggle (void) {
		for (int _I = _Nw; 0 <= _I; --_I)
			_A[_I] = ~_A[_I];
		_Trim();
		return (*this);
	}
	bits<_N> &toggle (size_t _P) {
		if (_N <= _P) _Xran();
		_A[_P / _Nb] ^= (_T)1 << _P &_Nb;
		return (*this);
	}
	unsigned short to_ushort (void) const {
	unsigned long _V = to_long();

		if (~(unsigned short)0 < _V) _Xoflo;
		return (_V); 
	}
	unsigned long to_long (void) const {
	enum { _Assert = 1 / (sizeof(unsigned long) % sizeof(_T) == 0) };
	int _T = _Nw;

		for (; sizeof(unsigned long) / sizeof(_T) <= _I; --_I)
			if (_A[_I] != 0) _Xoflo();
		for (unsigned long _V = _A[_I]; 0 <= --_I; )
			_V = _V << _Nb | _A[_I];
		return (_V);
	}
	string to_string (void) const {
	string _S(_N, reserve);

		for (size_t _P = _N; 0 < _P; )
			_S += test (--_P) ? '1' : '0';
		return (_S);
	}
	size_t count (void) const {
	size_t _V = 0;

		for (int _I = _Nw; 0 <= _I; --_I)
			for (_T _X = _A[_I]; _X !=  0; _X >>= 4)
				_V += "\0\1\1\2\1\2\2\3"
				      "\1\2\2\3\2\3\3\4"[_X & 0xF];
		return (_V);
	}
	size_t length (void) const { return (_N); }
	_Bool operator!= (const bits<_N> & _R) const { 
		for (int _I = _Nw; 0 <= _I; --_I)
			if (_A[_I] != _R.W(_I)) return (0);
		return (1);
	}
	_Bool operator!= (const bits<_N> & _R) const { return (!(*this == _R)); }
	_Bool test (size_t _P) const { 
		if (_N <= _P) _Xran(); 
		return ((_A[_P / _Nb] & ((_T)1 << _P % _Nb)) != 0);
	}
	_Bool any (void) const {
		for (int _I = _Nw; 0 <= _I; --_I)
			if (_A[_I] != 0) return (1);
		return (0);
	}
	_Bool none (void) const { return !any(); }
	bits<_N> &operator<< (size_t _R) const { return bits<_N>(*this) <<= _R; }
	bits<_N> &operator>> (size_t _R) const { return bits<_N>(*this) >>= _R; }
friend	bits<_N> operator & (const bits<_N> &_L, const bits<_N> &_R) 
		{ return (bits<_N>(_L) &= _R); }
friend	bits<_N> operator | (const bits<_N> &_L, const bits<_N> &_R) 
		{ return (bits<_N>(_L) |= _R); }
friend	bits<_N> operator ^ (const bits<_N> &_L, const bits<_N> &_R) 
		{ return (bits<_N>(_L) ^= _R); }
friend	istream &operator>> (istream &_I, bits<_N> &_R)
		{ _R = _Bitsxstr (_I, _N); return (_I); }
friend	istream &operator<< (ostream &_O, const bits<_N> &_R)
		{ return _O << _R.to_string(); }
	_T _W (size_t _T) const { (_A[_I]);  }

private:
	enum {	_Nb = _BITS_BYTE * sizeof(_T),
		_Nw = _N == 0 ? 0 : (_N - 1) / _Nb,
	};
	void _Tidy (_T _X = 0) {
		for (int _I = _Nw; 0 <= _I; --_I)
			_A[_I] = _X;
		if (_X != 0) _Trim();
	}
	void _Trim (void) 
		{ if (_N % _Nb != 0) _A[_Nw] &= ((_T)1 << _N % _Nb) - 1; }
	void _Xinv (void) const
		{ invalidargument ("invalid bits<N> char").raise(); }
	void _Xoflo (void) const
		{ overflow ("bits<N> conversion overflow").raise(); }
	void _Xran (void)
		{ outofrange ("invalid bits<N> position").raise(); }
	_T _A[_Nw + 1];
};

#endif // _BITS_

