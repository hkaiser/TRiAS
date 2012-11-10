// Rule_Info.h: Schnittstelle für die Klasse CRule_Info.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RULE_INFO_H__7C9A5A75_A3C2_11D3_8E60_00105AF354F9__INCLUDED_)
#define AFX_RULE_INFO_H__7C9A5A75_A3C2_11D3_8E60_00105AF354F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRule_Info : public CObject  
{
	CString		m_strKey;
	bool		m_tAutoRule;

	bool		m_tObjektartBI_bestimmt_Objektklasse_Hauptgeometrie;
	CString		m_strObjectClassTRiAS_Hauptgeometrie;
	
	long		m_lImportmodus_Detailgeometrie;
	bool		m_tObjektart_bestimmt_Objektklasse_Detailgeometrie;
	long		m_lObjektkategorie_Detailgeometrie;
	CString		m_strObjektklasse_Detailgeometrie;

	long		m_lImportmodus_Text;
	CString		m_strKonvertierung_Text;
	long		m_lObjektkategorie_Text;
	CString		m_strObjectClassTRiAS_Text;

	long		m_lImportmodus_Attr;
	CString		m_strKonvertierung_Attr;
	CString		m_strAttributeName;

public:
	CRule_Info( const char *strKey );
	virtual ~CRule_Info();
	CString		&Key( void ) { return m_strKey; }
	bool		&AutoRule( void ) { return m_tAutoRule; }

	bool		&ObjektartBI_bestimmt_Objektklasse_Hauptgeometrie( void ) { return m_tObjektartBI_bestimmt_Objektklasse_Hauptgeometrie; }
	CString		&ObjectClassTRiAS_Hauptgeometrie( void ) { return m_strObjectClassTRiAS_Hauptgeometrie; }

	long		&Importmodus_Detailgeometrie( void ) { return m_lImportmodus_Detailgeometrie; }
	bool		&Objektart_bestimmt_Objektklasse_Detailgeometrie( void ) { return m_tObjektart_bestimmt_Objektklasse_Detailgeometrie; }
	long		&Objektkategorie_Detailgeometrie( void ) { return m_lObjektkategorie_Detailgeometrie; }
	CString		&Objektklasse_Detailgeometrie( void ) { return m_strObjektklasse_Detailgeometrie; }

	long		&Importmodus_Text( void ) { return m_lImportmodus_Text; }
	CString		&Konvertierung_Text( void ) { return m_strKonvertierung_Text; }
	long		&Objektkategorie_Text( void ) { return m_lObjektkategorie_Text; }
	CString		&Objektklasse_Text( void ) { return m_strObjectClassTRiAS_Text; }

	long		&Importmodus_Attr( void ) { return m_lImportmodus_Attr; }
	CString		&Konvertierung_Attr( void ) { return m_strKonvertierung_Attr; }
	CString		&AttributeName( void ) { return m_strAttributeName; }

public:

};

#endif // !defined(AFX_RULE_INFO_H__7C9A5A75_A3C2_11D3_8E60_00105AF354F9__INCLUDED_)
