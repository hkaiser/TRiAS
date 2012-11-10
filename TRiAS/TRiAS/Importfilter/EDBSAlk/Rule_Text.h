// Rule_Text.h: Schnittstelle für die Klasse CRule_Text.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RULE_TEXT_H__44168227_A184_11D3_8E5C_00105AF354F9__INCLUDED_)
#define AFX_RULE_TEXT_H__44168227_A184_11D3_8E5C_00105AF354F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRule_Text : public CObject  
{
	CString		m_strKey;
	long		m_lImportMode;
	CString		m_strConvert;
	CString		m_strObjectClassTRiAS;
public:
	CRule_Text( const char *strKey );
	virtual ~CRule_Text();
	CString		&Key( void ) { return m_strKey; }
	CString		&Convert( void ) { return m_strConvert; }
	CString		&ObjectClassTRiAS( void ) { return m_strObjectClassTRiAS; }
	long &ImportMode() { return m_lImportMode; }
};

#endif // !defined(AFX_RULE_TEXT_H__44168227_A184_11D3_8E5C_00105AF354F9__INCLUDED_)
