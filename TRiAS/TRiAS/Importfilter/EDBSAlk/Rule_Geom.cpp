// Rule_Geom.cpp: Implementierung der Klasse CRule_Geom.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "Rule_Geom.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CRule_Geom::CRule_Geom( const char *strKey)
{
	m_strKey = strKey;
	m_tImport = true;
}

CRule_Geom::~CRule_Geom()
{

}
