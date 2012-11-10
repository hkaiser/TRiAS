// Rule_Info.cpp: Implementierung der Klasse CRule_Info.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "Rule_Info.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CRule_Info::CRule_Info( const char *strKey )
{
	m_strKey = strKey;
}

CRule_Info::~CRule_Info()
{

}
