// Rule_Attr.h: Schnittstelle für die Klasse CRule_Attr.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RULE_ATTR_H__44168223_A184_11D3_8E5C_00105AF354F9__INCLUDED_)
#define AFX_RULE_ATTR_H__44168223_A184_11D3_8E5C_00105AF354F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRule_Attr : public CObject  
{
	CString		m_strKey;
	long		m_lImportMode;
	CString		m_strConvert;
	CString		m_strAttributeName;
public:
	CRule_Attr( const char *strKey );
	virtual ~CRule_Attr();
	CString		&Key( void ) { return m_strKey; }
	long		&ImportMode( void ) { return m_lImportMode; }
	CString		&Convert( void ) { return m_strConvert; }
	CString		&AttributeName( void ) { return m_strAttributeName; }

};

#endif // !defined(AFX_RULE_ATTR_H__44168223_A184_11D3_8E5C_00105AF354F9__INCLUDED_)
