// CfgDb.cpp: Implementierung der Klasse CCfgDb.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "CfgDb.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CCfgDb::CCfgDb( const char* strConfigFile )
	: m_strShowCfgPage("")
{
	m_strConfigFile = strConfigFile;
}

CCfgDb::~CCfgDb()
{

}
