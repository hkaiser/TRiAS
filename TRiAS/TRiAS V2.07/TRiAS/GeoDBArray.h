///////////////////////////////////////////////////////////////////////////
// ArrayContainer, der alle derzeit geöffneten DatenBanken enthält 
// GeoDBArray.h

#if !defined(_GEODBARRAY_H__A37D826B_4A3F_11d1_96DC_00A024D6F582__INCLUDED_)
#define _GEODBARRAY_H__A37D826B_4A3F_11d1_96DC_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CGeoDBArray : 
	public CArrayContainer 
{
private:
	class GeoDBLock *m_pActDB;
	int m_iActDB;
	
protected:
	void UserDelete (void *);
	
public:
		CGeoDBArray (void);
		~CGeoDBArray (void);
		
	int FAddItem (bool fActivate = true);
	bool FDelItem (int iIndex = -1);
	int FFindItem (HPROJECT iDBDesc);
		
	int FActivateItem (int iIndex);
	int FActiveDB (void) { return m_iActDB; }
		
	GeoDB &DB (int iIndex);
	GeoDB &DB (HPROJECT hPr);
	inline GeoDB &DB (void);

	HPROJECT IsOpened (LPCSTR pcName);
};
DeclareLock (CGeoDBArray, GeoDB);

inline GeoDB &CGeoDBArray::DB(void) 
{
	if (NULL != m_pActDB) 
		return *((GeoDB *)(*m_pActDB));
	return DB(-1);
}

#endif // !defined(_GEODBARRAY_H__A37D826B_4A3F_11d1_96DC_00A024D6F582__INCLUDED_)
