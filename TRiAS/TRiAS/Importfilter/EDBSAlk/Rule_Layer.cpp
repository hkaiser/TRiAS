// Rule_Layer.cpp: Implementierung der Klasse CRule_Layer.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "Rule_Layer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CRule_Layer::CRule_Layer( const char *strDefinition )
{
	m_strFolie = strDefinition;
	m_lImportMode = 1;
	m_tResolve = true;
}

CRule_Layer::~CRule_Layer()
{

}
