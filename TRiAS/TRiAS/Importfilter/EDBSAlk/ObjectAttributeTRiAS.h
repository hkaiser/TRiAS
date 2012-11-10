// ObjectAttributeTRiAS.h: Schnittstelle für die Klasse CObjectAttributeTRiAS.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECTATTRIBUTETRIAS_H__7BA629A3_A0B6_11D3_8E5B_00105AF354F9__INCLUDED_)
#define AFX_OBJECTATTRIBUTETRIAS_H__7BA629A3_A0B6_11D3_8E5B_00105AF354F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CObjectAttributeTRiAS : public CObject  
{
	unsigned long	m_ulAttributeIdent;
	CString			m_strAttributeName;
	CString			m_strAttributeDescription;
public:
	CObjectAttributeTRiAS( CString strAttributeName );
	virtual ~CObjectAttributeTRiAS();
	unsigned long	&Ident( void ) { return m_ulAttributeIdent; }
	CString			&Name( void ) { return m_strAttributeName; }
	CString			&Description( void ) { return m_strAttributeDescription; }

};

#endif // !defined(AFX_OBJECTATTRIBUTETRIAS_H__7BA629A3_A0B6_11D3_8E5B_00105AF354F9__INCLUDED_)
