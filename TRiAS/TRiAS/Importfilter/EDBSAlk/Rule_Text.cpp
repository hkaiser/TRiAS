// Rule_Text.cpp: Implementierung der Klasse CRule_Text.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "Rule_Text.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CRule_Text::CRule_Text( const char *strKey )
{
	m_strKey = strKey;
}

CRule_Text::~CRule_Text()
{

}
