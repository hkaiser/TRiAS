// Rule_Attr.cpp: Implementierung der Klasse CRule_Attr.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "Rule_Attr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CRule_Attr::CRule_Attr( const char *strKey )
{
	m_strKey = strKey;
}

CRule_Attr::~CRule_Attr()
{

}
