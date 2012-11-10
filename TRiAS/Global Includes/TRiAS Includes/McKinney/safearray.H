#ifndef _SAFEARRAY_H_D9F3E660_235C_11d2_8F8E_0060085FC1CE
#define _SAFEARRAY_H_D9F3E660_235C_11d2_8F8E_0060085FC1CE

#if !defined(_OLETYPE_H_D9F3E660_235C_11d2_8F8E_0060085FC1CE)
#error "You must include this file with OleType.h"
#endif

// Dim class encapsulates an array dimension
//@B Dim
class Dim : public SAFEARRAYBOUND
{
public:
	Dim(long iLo, long iHi)
	{ cElements = abs(iHi - iLo) + 1; lLbound = iLo; }
	Dim(long c)
	{ cElements = c; lLbound = 0; }
	const Dim & operator=(const Dim & dim) 
	{ cElements = dim.cElements; lLbound = dim.lLbound; return *this; }
	const Dim & operator=(long c) 
	{ cElements = c; lLbound = 0; return *this; }
	~Dim() {}
	long Elements() { return cElements; }
	long LBound() { return lLbound; }
	long UBound() { return lLbound + cElements - 1; }
};
//@E Dim

// Warning: Unused bit from fFeatures field could be used someday
const WORD VTA_CONSTRUCTED = 0x80;

// SafeArray container class for OLE types

//@B SafeArray1
template<class T, VARTYPE vt> 
class SafeArray  {
	int	m_lockCount;
public:
	// Constructors
	SafeArray();
	SafeArray(SAFEARRAY * psaSrc);
	SafeArray(const Dim & dim);
    // Copy constructor
	SafeArray(const SafeArray & saSrc);

	// Destructor
	~SafeArray(); 

	// Operator equal
	const SafeArray & operator=(const SafeArray & saSrc);
	const SafeArray &operator=(const SAFEARRAY* saSrc );
	bool Attach( SAFEARRAY *psa );
	bool Assign( SAFEARRAY *psa );
	SAFEARRAY* Detach();

	// Indexing
	T & Get(long i);
	T & Set(T & t, long i);
	T & operator[](const long i);    // C++ style (0-indexed)
	T & operator()(const long i);    // Basic style (LBound-indexed)
//@E SafeArray1

	// Type casts
	SAFEARRAY* operator*() const;
	SAFEARRAY* operator&() const;
	SAFEARRAY** ppa();
	operator SAFEARRAY(); 
	operator SAFEARRAY() const; 
	operator Variant(); 
	operator Variant() const; 

	// Operations
	Boolean ReDim(Dim & dim);
	long LBound();
	long UBound();
	long Elements();
	long Dimensions();
    Boolean IsSizable();
	void Lock();
	void Unlock();

//@B SafeArray2
private:
	SAFEARRAY * psa;
	bool	m_bIsAttached;
	bool	m_bIsConstructed;
    void Destroy();
    Boolean IsConstructed();
    void Constructed(Boolean f);
	void DetachOrDestroy( );
};
//@E SafeArray2

// Private helpers

template<class T, VARTYPE vt>
inline SAFEARRAY* SafeArray<T,vt>::Detach() {
	while( m_lockCount ) {
		Unlock();
	}
	m_bIsAttached = false;
	m_bIsConstructed = false;
	SAFEARRAY * _psa = psa;
	psa = NULL;
	return _psa;
}

template<class T, VARTYPE vt> 
inline void SafeArray<T,vt>::DetachOrDestroy() {
	while( m_lockCount ) {
		Unlock();
	}
	if( m_bIsAttached ) {
		m_bIsAttached = false;
	} else if( m_bIsConstructed ) {
		m_bIsConstructed = false;
		HRESULT hres = ::SafeArrayDestroy(psa);
	    if (hres) throw hres;
	}
	psa = NULL;
}

template<class T, VARTYPE vt> 
inline void SafeArray<T,vt>::Destroy() {
	DetachOrDestroy();
}

template<class T, VARTYPE vt> 
inline Boolean SafeArray<T,vt>::IsConstructed() {
    return m_bIsConstructed; //(psa->fFeatures & VTA_CONSTRUCTED) ? True : False;
}

template<class T, VARTYPE vt> 
inline void SafeArray<T,vt>::Constructed(Boolean f) {
	m_bIsConstructed = f;
}

// Constructors
template<class T, VARTYPE vt> 
inline SafeArray<T,vt>::SafeArray() 
	: psa(NULL)
	, m_bIsAttached(false)
	, m_lockCount(0)
{ 
    Dim dim(0);
	psa = SafeArrayCreate(vt, 1, &dim); 
    Constructed(True);
    if (psa == NULL) _com_issue_error(E_OUTOFMEMORY);
}


template<class T, VARTYPE vt> 
inline SafeArray<T,vt>::SafeArray(SAFEARRAY * psaSrc)
	: psa(NULL)
	, m_bIsAttached(false)
	, m_lockCount(0)
{ 
    if (SafeArrayGetDim(psaSrc) != 1)
		_com_issue_error(E_INVALIDARG);
	HRESULT hr = ::SafeArrayCopy( psaSrc, &psa );
	if( hr )
		_com_issue_error(hr);
    Constructed(True);
//    psa = psaSrc; 
}

template<class T, VARTYPE vt> 
inline SafeArray<T,vt>::SafeArray(const SafeArray & saSrc)
	: psa(NULL)
	, m_bIsAttached(false)
	, m_lockCount(0)
{
    HRESULT hres = SafeArrayCopy(saSrc.psa, &psa);
    Constructed(True);
    if (hres) _com_issue_error(hres);
}


template<class T, VARTYPE vt> 
inline SafeArray<T,vt>::SafeArray( const Dim& dim) : psa(NULL), m_bIsAttached( false ), m_lockCount(0)
{
	psa = SafeArrayCreate(vt, 1, (SAFEARRAYBOUND*)(&dim) ); 
    Constructed(True);
    if (psa == NULL) _com_issue_error(E_OUTOFMEMORY);
} 

// Destructor
template<class T, VARTYPE vt> 
inline SafeArray<T,vt>::~SafeArray() {
	DetachOrDestroy();
} 

template<class T, VARTYPE vt> 
bool SafeArray<T,vt>::Attach( SAFEARRAY *psaSrc ) {
	DetachOrDestroy();
	if( 1 != ::SafeArrayGetDim( psaSrc ) )
		return false;
	if( !psaSrc )
		return false;
	psa = psaSrc;
	m_bIsAttached = true;
	return true;
}

template<class T, VARTYPE vt> 
bool SafeArray<T,vt>::Assign( SAFEARRAY *psaSrc ) {
	DetachOrDestroy();
	if( !psaSrc )
		return false;
	if( 1 != ::SafeArrayGetDim( psaSrc ) )
		return false;
	if( !psaSrc )
		return false;
	psa = psaSrc;
	Constructed(True);
	return true;
}
	
// Operator = 
template<class T, VARTYPE vt> 
const SafeArray<T,vt> & SafeArray<T,vt>::operator=(const SafeArray & saSrc) {
	DetachOrDestroy();
    HRESULT hres = SafeArrayCopy(saSrc.psa, &psa);
    Constructed(True);
    if (hres) _com_issue_error(hres);
    return *this;
}

template<class T, VARTYPE vt> 
const SafeArray<T,vt> & SafeArray<T,vt>::operator=(const SAFEARRAY* saSrc ) {
	DetachOrDestroy();
    HRESULT hres = SafeArrayCopy((SAFEARRAY*) saSrc, &psa);
    Constructed(True);
    if (hres) _com_issue_error(hres);
    return *this;
}

// Type casts
template<class T, VARTYPE vt> 
inline SafeArray<T,vt>::operator SAFEARRAY() {
    return *psa; 
}

template<class T, VARTYPE vt> 
SafeArray<T,vt>::operator SAFEARRAY() const {
//    static SAFEARRAY * psaT;
	SAFEARRAY psaT;// = NULL;
    ::SafeArrayCopy(psa, &psaT);
//    psaT->fFeatures &= ~VTA_CONSTRUCTED;
    return psaT;
}

template<class T, VARTYPE vt> 
SAFEARRAY* SafeArray<T,vt>::operator *() const {
	SAFEARRAY	*p = NULL;
	HRESULT hr = ::SafeArrayCopy( psa, &p );
	if( hr )
		_com_issue_error(hr);
	return p;
}

template<class T, VARTYPE vt> 
SAFEARRAY** SafeArray<T,vt>::ppa() {
	DetachOrDestroy();
	Constructed(True);
	return &psa;
}

template<class T, VARTYPE vt> 
SAFEARRAY* SafeArray<T,vt>::operator&() const {
	return psa;
}

template<class T, VARTYPE vt> 
SafeArray<T,vt>::operator Variant() {
    return Variant(psa);
}

template<class T, VARTYPE vt> 
SafeArray<T,vt>::operator Variant() const {
    Variant v(psa);
    return v;
}

// Indexing
template<class T, VARTYPE vt> 
T & SafeArray<T,vt>::Get(long i) {
	static T tRes;
	HRESULT hres = ::SafeArrayGetElement(psa, &i, &tRes);
	if (hres) _com_issue_error(hres);
	return tRes;
}

//@B Indexing
template<class T, VARTYPE vt> 
inline T & SafeArray<T,vt>::Set(T & t, long i) {
	HRESULT hres = ::SafeArrayPutElement(psa, &i, (T *)&t);
	if (hres) _com_issue_error(hres);
    return t;
}

template<class T, VARTYPE vt> 
inline T & SafeArray<T,vt>::operator[](const long i) {
    if (i < 0 || i > Elements() - 1)
		_com_issue_error(DISP_E_BADINDEX);
	return ((T*)psa->pvData)[i];
}

template<class T, VARTYPE vt> 
T & SafeArray<T,vt>::operator()(const long i) {
    if (i < LBound() || i > UBound())
		_com_issue_error(DISP_E_BADINDEX);
	return ((T*)psa->pvData)[i - LBound()];
}
//@E Indexing

// Operations
template<class T, VARTYPE vt> 
Boolean SafeArray<T,vt>::ReDim(Dim &dim) {
    if (!IsSizable()) {
        return False;
    }
	HRESULT hres = ::SafeArrayRedim(psa, &dim);
	if (hres) _com_issue_error(hres);
    return True;
}

template<class T, VARTYPE vt> 
long SafeArray<T,vt>::LBound() {
	long iRes;
	HRESULT hres = ::SafeArrayGetLBound(psa, 1, &iRes);
	if (hres) _com_issue_error(hres);
	return iRes;
}

template<class T, VARTYPE vt> 
inline long SafeArray<T,vt>::Elements() {
	return psa->rgsabound[0].cElements;
}

template<class T, VARTYPE vt> 
long SafeArray<T,vt>::UBound() {
	long iRes;
	HRESULT hres = SafeArrayGetUBound(psa, 1, &iRes);
	if (hres) _com_issue_error(hres);
	return iRes;
}

template<class T, VARTYPE vt> 
inline long SafeArray<T,vt>::Dimensions() {
	return 1;
}

template<class T, VARTYPE vt> 
inline Boolean SafeArray<T,vt>::IsSizable() {
    return (psa->fFeatures & FADF_FIXEDSIZE) ? False : True;
}

template<class T, VARTYPE vt>
inline void SafeArray<T,vt>::Lock() {
	HRESULT hres = ::SafeArrayLock(psa);
	if (hres) _com_issue_error(hres);
	++m_lockCount;
}

template<class T, VARTYPE vt>
inline void SafeArray<T,vt>::Unlock() {
	_ASSERTE(m_lockCount);
	if(!m_lockCount)
		return;
	HRESULT hres = ::SafeArrayUnlock(psa);
	if (hres) _com_issue_error(hres);
	--m_lockCount;
}

#endif // _SAFEARRAY_H_D9F3E660_235C_11d2_8F8E_0060085FC1CE
