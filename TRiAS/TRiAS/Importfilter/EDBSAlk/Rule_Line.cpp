// Rule_Line.cpp: Implementierung der Klasse CRule_Line.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "Rule_Line.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CRule_Line::CRule_Line( const char *strKey )
{
	m_strKey = strKey;
	m_lImportmodus_Hauptgeometrie = 255;
	m_lImportmodus_Zusatzgeometrie = 0;
}

CRule_Line::~CRule_Line()
{

}
