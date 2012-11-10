// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 15.07.99 20:16:21
//
// @doc
// @module RunTimeObjectMapMgrImpl.cpp | Implementation of the <c CRunTimeObjectMapMgr> class

#if defined(_USE_RUNTIME_OBJECTMAP)

#include <Atl/RunTimeObjectMapMgr.h>

///////////////////////////////////////////////////////////////////////////////
// Maintains a vector array of _ATL_OBJMAP_ENTRY pointers. This can
// be used to generate a dynamic object map at run-time.

class CRunTimeObjectMapMgr
{
private:
	typedef vector<_ATL_OBJMAP_ENTRY *> CObjectMapVector;

	CObjectMapVector m_vecObjectMap;
	_ATL_OBJMAP_ENTRY *m_pATLObjectMap;

public:
	CRunTimeObjectMapMgr();
	~CRunTimeObjectMapMgr();

	void Add(_ATL_OBJMAP_ENTRY *pEntry);
	_ATL_OBJMAP_ENTRY *GenerateMap();
};

///////////////////////////////////////////////////////////////////////////////
// local variable for terminating an object map.
static _ATL_OBJMAP_ENTRY __lastObjectMapEntry__[1] = { END_OBJECT_MAP() 

///////////////////////////////////////////////////////////////////////////////
// Initialise member variables
CRunTimeObjectMapMgr::CRunTimeObjectMapMgr()
{
	m_pATLObjectMap = NULL;
}

///////////////////////////////////////////////////////////////////////////////
// Cleanup
CRunTimeObjectMapMgr::~CRunTimeObjectMapMgr()
{
	delete[] m_pATLObjectMap;
}

///////////////////////////////////////////////////////////////////////////////
// Adds an object map entry pointer to the vector array
void CRunTimeObjectMapMgr::Add (_ATL_OBJMAP_ENTRY* pEntry)
{
	ATLTRY(m_vecObjectMap.push_back (pEntry));
}

///////////////////////////////////////////////////////////////////////////////
// Generates a contiguous map of all of the object map entries.
_ATL_OBJMAP_ENTRY *CRunTimeObjectMapMgr::GenerateMap()
{
	if (m_pATLObjectMap == NULL) {
		Add(__lastObjectMapEntry__);

	int iSize = m_vecObjectMap.size();

		ATLTRY(m_pATLObjectMap = new _ATL_OBJMAP_ENTRY[iSize]);

		if (NULL != m_pATLObjectMap) {
			for (int iIndex = 0; iIndex < iSize; iIndex++)
				m_pATLObjectMap[iIndex] = *(m_vecObjectMap[iIndex]);
		}
	}
	return m_pATLObjectMap;
}

///////////////////////////////////////////////////////////////////////////////
// local pointer to a CRunTimeObjectMapMgr
static CRunTimeObjectMapMgr *pRunTimeObjectMapMgr = NULL;

///////////////////////////////////////////////////////////////////////////////
// Creates (if necessary) the run-time object manager, and adds the	entry to it.
void RegisterRunTimeObjectMapEntry (_ATL_OBJMAP_ENTRY *pEntry)
{
	if(pRunTimeObjectMapMgr == NULL) 
	{
		ATLTRY(pRunTimeObjectMapMgr = new CRunTimeObjectMapMgr);
	}

	if (NULL != pRunTimeObjectMapMgr)
		pRunTimeObjectMapMgr -> Add(pEntry);
}

///////////////////////////////////////////////////////////////////////////////
// delegates to the run-time object manager to get the object map.
_ATL_OBJMAP_ENTRY *GetRunTimeObjectMap()
{
_ATL_OBJMAP_ENTRY *pRunTimeMap = NULL;

	if (NULL != pRunTimeObjectMapMgr)
		pRunTimeMap = pRunTimeObjectMapMgr -> GenerateMap();

	if (NULL != pRunTimeMap)
		return pRunTimeMap;
	
	return __lastObjectMapEntry__;		// no entries at all
}

///////////////////////////////////////////////////////////////////////////////
// Cleans up an local CRunTimeObjectMapMgr during shutdown
class CRunTimeObjectMgrCaretaker
{
public:
	~CRunTimeObjectMgrCaretaker()
	{
		DELETE_OBJ(pRunTimeObjectMapMgr);
	}
};
static CRunTimeObjectMgrCaretaker rtomCaretaker;

#endif // defined(_USE_RUNTIME_OBJECTMAP)

