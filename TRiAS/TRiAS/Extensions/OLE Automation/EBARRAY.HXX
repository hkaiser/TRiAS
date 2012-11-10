// Wrapperklasse für eindimensionale ebARRAY's --------------------------------
// File: EBARRAY.HXX

#if !defined(_EBARRAY_HXX)
#define _EBARRAY_HXX

///////////////////////////////////////////////////////////////////////////////
// Zugriff auf ebArray
template<class T> class CEbArray;	// forward declaration only

template<class T> 
class CEbLock 
{
protected:
	CEbArray<T> &m_reba;
	long m_lDim;			// größter möglicher Index
	ebLPARRAY m_pArray;
	T * m_pData;
	
public:
		inline CEbLock (CEbArray<T> &eba) : m_reba(eba)
		{
			m_pData = NULL;
			m_lDim = 0;
			m_pArray = m_reba.Lock();
					
			if (NULL != m_pArray) {
				m_pData = (T *)m_reba.AccessData (m_pArray);
				if (NULL == m_pData) {
					m_reba.UnAccessData (m_pArray);
					m_pArray = NULL;
				} else
					m_lDim = m_pArray -> Dim[0].wUpper - m_pArray -> Dim[0].wLower;
			}
		}
		inline ~CEbLock (void)
		{
			if (m_pData){
				if (m_pArray) m_reba.UnAccessData (m_pArray);
				m_reba.UnLock();
			}
		}

inline	bool operator! (void) { return m_pData == NULL; }
inline	operator ebLPARRAY (void) { return m_pArray; }
inline	long Size (void) { return m_lDim +1; }
inline	T &operator[] (LONG lIndex)	{ return m_pData[lIndex <= m_lDim ? lIndex : 0]; }
inline	operator T * (void) { return m_pData; }	
};

///////////////////////////////////////////////////////////////////////////////
// eigentliches ebArray
template<class T> 
class CEbArray 
{
private:
	ebHSUB m_hArr;
	ebHTHREAD m_hThread;

protected:
inline	ebLPARRAY Lock (void) { return (ebLPARRAY)ebLockBlk (m_hThread, m_hArr); }
inline	void UnLock (void) { ebUnlockBlk (m_hThread, m_hArr); }
inline	ebLPVOID AccessData (ebLPARRAY pArray)
		{ return ebLockArrayData (m_hThread, pArray); }
inline	void UnAccessData (ebLPARRAY pArray)
		{ ebUnlockArrayData (m_hThread, pArray); }

public:
	inline	CEbArray (ebHTHREAD hThread, ebHSUB hArr) :
			m_hThread(hThread), m_hArr(hArr) {}
	inline	~CEbArray (void) {}
		
	bool ReDim (long lCnt)
	{
	long lDim = 0;

		{	// testen, ob dieses Array bearbeitet werden kann
		CEbLock<T> l(*this);
		ebLPARRAY pArr = (ebLPARRAY )l;
			
			if (pArr -> bNumDims > 1) return false;
			lDim = pArr -> Dim[0].wUpper - pArr -> Dim[0].wLower;
			if (pArr -> bFlags & AF_FIXED && (lDim < lCnt))
				return false;
		} // Lock aufheben
		
		if (lDim < lCnt && ebRedimArray (m_hThread, m_hArr, int(lCnt)))
			return false;
		
	return true;
	}

friend class CEbLock<T>;
};

#define DeclareEbLock(typ)	\
	typedef CEbArray<typ> CEbArray##typ;	\
	typedef CEbLock<typ> CEbLock##typ;

#endif // _EBARRAY_HXX
