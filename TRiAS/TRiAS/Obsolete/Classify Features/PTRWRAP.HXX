// Template, welches ein Interface für einen STL-Container verpackt -----------
// File: PTRWRAP.HXX

#if !defined(_PTRWRAP_HXX)
#define _PTRWRAP_HXX

#if !defined(ADDREF)
#define ADDREF(p) if(!p){} else {p->AddRef();}
#endif // ADDREF

#if !defined(RELEASE)
#define RELEASE(p) if(!p){} else {p->Release();p=NULL;}
#endif // RELEASE

template <class T>
class __W {		// InterFaceWrapper
private:
	T *m_pPtr;

public:
	__W (T *pPtr = NULL) : m_pPtr(pPtr) { ADDREF(pPtr); }
	__W (const __W<T> &rT)
		{ m_pPtr = rT.m_pPtr; ADDREF(m_pPtr); }
	~__W (void) { RELEASE(m_pPtr); }

	const T *operator->() const { return m_pPtr; }
	T *operator->() { return m_pPtr; }
	operator const T * () const { return m_pPtr; }
	operator T * () { return m_pPtr; }

	__W<T> &operator= (const __W<T> &rT)
		{ RELEASE(m_pPtr); m_pPtr = rT.m_pPtr; ADDREF(m_pPtr); return *this; }
	__W<T> &operator= (T *pPtr)
		{ RELEASE(m_pPtr); m_pPtr = pPtr; ADDREF(m_pPtr); return *this; }
};

template <class T>
bool operator== (const __W<T> &, const __W<T> &)
{
	return false;
}

template <class T>
bool operator< (const __W<T> &, const __W<T> &)
{
	return false;
}

#endif // _PTRWRAP_HXX
