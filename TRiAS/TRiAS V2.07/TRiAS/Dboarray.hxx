// ArrayContainer, der alle derzeit geöffneten Projekte enthält ---------------
// File: DBOARRAY.HXX

#if !defined(_DBOARRAY_HXX)
#define _DBOARRAY_HXX

class CDBOArray : public CArrayContainer 
{
private:
	class DatenBasisObjektLock *m_pActDBO;
	short m_iActDB;
	
protected:
	void UserDelete (void *);
	
public:
		CDBOArray (void);
		~CDBOArray (void);
		
	short FAddItem (const GeoDB &DB, unsigned int MTyp, pPen pP, 
			pBrush pB, bool fActivate = true);
	short FAddItem (bool fActivate = true);			// aktiviert automatisch
	bool FDelItem (short iIndex = -1);
	short FFindItem (HPROJECT iDBDesc);
		
	short FActivateItem (short iIndex);
	short FActiveDBO (void) { return m_iActDB; }
		
	DatenBasisObjekt &DBO (short iIndex);
	DatenBasisObjekt &DBO (HPROJECT hPr);
	inline DatenBasisObjekt &DBO (void);

	HPROJECT IsOpened (LPCSTR pcName);
};
DeclareLock (CDBOArray, DatenBasisObjekt);

inline DatenBasisObjekt &CDBOArray::DBO (void) 
{
	if (NULL != m_pActDBO) 
		return *((DatenBasisObjekt *)(*m_pActDBO));
	return DBO(-1);
}

#endif // _DBOARRAY_HXX
