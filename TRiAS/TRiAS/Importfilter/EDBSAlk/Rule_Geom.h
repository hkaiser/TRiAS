// Rule_Geom.h: Schnittstelle für die Klasse CRule_Geom.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RULE_GEOM_H__7C9A5A73_A3C2_11D3_8E60_00105AF354F9__INCLUDED_)
#define AFX_RULE_GEOM_H__7C9A5A73_A3C2_11D3_8E60_00105AF354F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRule_Geom : public CObject  
{
	CString		m_strKey;
	long		m_lImportMode;
	CString		m_strObjectClassTRiAS;
	bool		m_tObjektartBestimmtObjektartBI;
	bool		m_tImport;

public:
	CRule_Geom( const char *strKey );
	virtual ~CRule_Geom();
	CString		&Key( void ) { return m_strKey; }
	long		&ImportMode( void ) { return m_lImportMode; }
	bool		&ObjektartBestimmtObjektartBI( void ) { return m_tObjektartBestimmtObjektartBI; }
	CString		&ObjectClassTRiAS( void ) { return m_strObjectClassTRiAS; }
	void		Import( bool tImport ) { m_tImport = tImport; }
	bool		Import( void )		{ return m_tImport; }
};

#endif // !defined(AFX_RULE_GEOM_H__7C9A5A73_A3C2_11D3_8E60_00105AF354F9__INCLUDED_)
