// CfgDb.h: Schnittstelle für die Klasse CCfgDb.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CFGDB_H__BE00DF77_9C09_11D3_8E57_00105AF354F9__INCLUDED_)
#define AFX_CFGDB_H__BE00DF77_9C09_11D3_8E57_00105AF354F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCfgDb : public CObject
{
public:
	CCfgDb( const char* strConfigFile );
	virtual ~CCfgDb();
	CString m_strConfigFile;
	CString m_strConfigName;
	CString m_strConfigDescription;
	CString m_strShowCfgPage;
};

#endif // !defined(AFX_CFGDB_H__BE00DF77_9C09_11D3_8E57_00105AF354F9__INCLUDED_)
