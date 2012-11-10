#if !defined(__DOUBLEBUF_H__B82CDCD0_2495_11d3_9982_0060085FC1CE)
#define __DOUBLEBUF_H__B82CDCD0_2495_11d3_9982_0060085FC1CE

//////////////////////////////////////////////////////////////////////
// Struktur zum Umkonvertieren ANSI <-> OEM et v.V.
struct DOUBLEBUF {
	LPTSTR	m_pABuf;	// ANSI-Buffer
	LPTSTR	m_pOBuf;	// OEM-Buffer
	long	m_nBufLen;
	DOUBLEBUF()
		: m_pABuf(NULL)
		, m_pOBuf(NULL)
		, m_nBufLen(0)
	{
		Check(256);
	}
	~DOUBLEBUF() {
		delete[] m_pABuf;
		delete[] m_pOBuf;
	}
	HRESULT Check( long lRequest ) {
		if( lRequest <= m_nBufLen )
			return S_OK;
		delete[] m_pABuf; m_pABuf = NULL;
		delete[] m_pOBuf; m_pOBuf = NULL;
		m_pABuf = new TCHAR[lRequest];
		m_pOBuf = new TCHAR[lRequest];
		m_nBufLen = m_pABuf && m_pOBuf ? lRequest : 0;
		return m_nBufLen ? S_OK : E_OUTOFMEMORY;
	}
};

#endif // __DOUBLEBUF_H__B82CDCD0_2495_11d3_9982_0060085FC1CE
