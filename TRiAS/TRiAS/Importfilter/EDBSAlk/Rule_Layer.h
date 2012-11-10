// Rule_Layer.h: Schnittstelle für die Klasse CRule_Layer.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RULE_LAYER_H__32694993_A329_11D3_8E5F_00105AF354F9__INCLUDED_)
#define AFX_RULE_LAYER_H__32694993_A329_11D3_8E5F_00105AF354F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRule_Layer : public CObject  
{
	CString		m_strFolie;
	CString		m_strKurztext;
	CString		m_strLangtext;
	CString		m_strObjectClassTRiAS;
	long		m_lImportMode;
	bool		m_tResolve;

public:
	CRule_Layer( const char* strDefinition );
	virtual ~CRule_Layer();
	CString		&Folie()			{ return m_strFolie; }
	CString		&Kurztext()			{ return m_strKurztext; }
	CString		&Langtext()			{ return m_strLangtext; }
	CString		&ObjectClassTRiAS()	{ return m_strObjectClassTRiAS; }
	long		&ImportMode( void ) { return m_lImportMode; }
	void			Resolve( bool tResolve ) { m_tResolve = tResolve; }
	bool			Resolve( void )		{ return m_tResolve; }

};

#endif // !defined(AFX_RULE_LAYER_H__32694993_A329_11D3_8E5F_00105AF354F9__INCLUDED_)
