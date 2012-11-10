// Wrapper für OBJGEOMETRIE
// OBJGEOMW.H
// geklaut bei Hartmut; weiß er aber... ;-)

#if !defined(_OBJGEOMW_H)
#define _OBJGEOMW_H

class CObjGeometrie :
	public GEOMETRIEWITHCS
{
private:
	OBJGEOMETRIE m_OG;
	CComQIPtr<ITRiASCS, &IID_ITRiASCS> m_CS;

protected:
	void Tidy (void);

public:
		CObjGeometrie (ITRiASCS *pICS);
		~CObjGeometrie (void);

	bool InitObjGeometrie (bool fIsInitialized);
	bool FillObjGeometrie (long lONrToFill);

	void SetFlags(short dwFlags) { m_OG.iFlags = dwFlags; }
	short GetObjType() const { return m_OG.iObjTyp; }
	long GetCount() const { return m_OG.lCnt; }
	short GetCountourCount() const { return m_OG.iKCnt; }
	long GetContourPoints(int i = 0) const
	{
		_ASSERTE(NULL != m_OG.plCnt);
		_ASSERTE(0 <= i && i < m_OG.iKCnt);
		return m_OG.plCnt[i];
	}
	long *GetXAsLong() const { return (long *)m_OG.pdblX; }
	long *GetYAsLong() const { return (long *)m_OG.pdblY; }
	double *GetXAsDouble() const { return (double *)m_OG.pdblX; }
	double *GetYAsDouble() const { return (double *)m_OG.pdblY; }

	
	OBJGEOMETRIE &operator= (const OBJGEOMETRIE &rOG);
};

#endif // _OBJGEOMW_H
