// Wrapperklasse für eindimensionale ebARRAY's --------------------------------
// File: EBARRAY.HXX

#if !defined(_EBARRAY_HXX)
#define _EBARRAY_HXX

class CEbArray {
protected:
	ebHSUB m_hArr;
	ebHTHREAD m_hThread;
	
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
		
	bool ReDim (long lCnt);
	
friend class CEbLock;
};

class CEbLock {
protected:
	CEbArray &m_reba;
	long m_lDim;			// größter möglicher Index
	ebLPARRAY m_pArray;
	ebLPVOID m_pData;
	
public:
		CEbLock (CEbArray &eba);
		~CEbLock (void);

inline	bool operator! (void) { return m_pData == NULL; }
inline	operator ebLPARRAY (void) { return m_pArray; }
inline	long Size (void) { return m_lDim +1; }
};

// typspezifischer Lock -------------------------------------------------------
#define DeclareEbLock(typ)							\
class CEbLock##typ : public CEbLock {						\
public:										\
		CEbLock##typ (CEbArray &eba) : CEbLock (eba) {}			\
										\
inline	typ &operator[] (LONG lIndex)						\
		{ return ((typ *)m_pData)[lIndex <= m_lDim ? lIndex : 0]; }	\
inline	operator typ * (void) { return (typ *)m_pData; }			\
};

#endif // _EBARRAY_HXX
