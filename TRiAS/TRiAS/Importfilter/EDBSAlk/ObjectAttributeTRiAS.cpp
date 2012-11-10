// ObjectAttributeTRiAS.cpp: Implementierung der Klasse CObjectAttributeTRiAS.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "ObjectAttributeTRiAS.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CObjectAttributeTRiAS::CObjectAttributeTRiAS( CString strAttributeName )
{
	m_ulAttributeIdent = 0;
	m_strAttributeName = strAttributeName;
}

CObjectAttributeTRiAS::~CObjectAttributeTRiAS()
{

}
