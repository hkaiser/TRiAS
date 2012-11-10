///////////////////////////////////////////////////////////////////////////
// ArrayContainer, der alle derzeit geöffneten Projekte enthält 
// Dboarray.hxx

#if !defined(_DBOARRAY_HXX__A37D826A_4A3F_11d1_96DC_00A024D6F582__INCLUDED_)
#define _DBOARRAY_HXX__A37D826A_4A3F_11d1_96DC_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDBOArray : 
	public CArrayContainer 
{
private:
	class DatenBasisObjektLock *m_pActDBO;
	int m_iActDB;
	
protected:
	void UserDelete (void *);
	
public:
		CDBOArray (void);
		~CDBOArray (void);
		
	int FAddItem (bool fActivate = true);			// aktiviert automatisch
	bool FDelItem (int iIndex = -1);
	int FFindItem (HPROJECT iDBDesc);
		
	int FActivateItem (int iIndex);
	int FActiveDBO (void) { return m_iActDB; }
		
	DatenBasisObjekt &DBO (int iIndex);
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

#endif // !defined(_DBOARRAY_HXX__A37D826A_4A3F_11d1_96DC_00A024D6F582__INCLUDED_)
