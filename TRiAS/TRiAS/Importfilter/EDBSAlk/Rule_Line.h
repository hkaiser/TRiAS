// Rule_Line.h: Schnittstelle für die Klasse CRule_Line.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RULE_LINE_H__7C9A5A74_A3C2_11D3_8E60_00105AF354F9__INCLUDED_)
#define AFX_RULE_LINE_H__7C9A5A74_A3C2_11D3_8E60_00105AF354F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRule_Line : public CObject  
{
	CString		m_strKey;
	bool		m_tFunktionDerLinieBestimmtObjektklasse_Hauptgeometrie;
	long		m_lImportmodus_Hauptgeometrie;
	long		m_lObjektkategorie_Hauptgeometrie;
	CString		m_strObjektklasse_Hauptgeometrie;
	long		m_lImportmodus_Zusatzgeometrie;
	bool		m_tObjektartBestimmtObjektklasse_Zusatzgeometrie;
	long		m_lObjektkategorie_Zusatzgeometrie;
	CString		m_strObjektklasse_Zusatzgeometrie;

public:
	CRule_Line( const char *strKey );
	virtual ~CRule_Line();
	CString		&Key( void ) { return m_strKey; }
	long		&Importmodus_Hauptgeometrie( void ) { return m_lImportmodus_Hauptgeometrie; }
	bool		&FunktionDerLinieBestimmtObjektklasse_Hauptgeometrie( void ) { return m_tFunktionDerLinieBestimmtObjektklasse_Hauptgeometrie; }
	long		&Importmodus_Zusatzgeometrie( void ) { return m_lImportmodus_Zusatzgeometrie; }
	CString		&Objektklasse_Hauptgeometrie( void ) { return m_strObjektklasse_Hauptgeometrie; }
	CString		&Objektklasse_Zusatzgeometrie( void ) { return m_strObjektklasse_Zusatzgeometrie; }

};

#endif // !defined(AFX_RULE_LINE_H__7C9A5A74_A3C2_11D3_8E60_00105AF354F9__INCLUDED_)
