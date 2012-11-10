// Verwalten der Knoten-Keys
// File: Segmkey.cpp

#include "stdafx.h"
#include "resource.h"
#include <containr.hxx>
#include "segmkey.hxx"

#pragma warning(disable: 4273)
int __cdecl lstrcmp (void *p1, void *p2)
{
	return strcmp((char *)p1, (char *)p2); 
}

///////////////////////////////////////////////////////////////////////////////
// Member für Klasse CSegKnoten
CSegKnoten::CSegKnoten (const char *pKeyText) :
	m_strKeyText(pKeyText)
{
	m_lONr = -1L;
}

CSegKnoten::~CSegKnoten (void) 
{
}

///////////////////////////////////////////////////////////////////////////////
// Memberfunktionen für CSegKnotenTree 
CSegKnotenTree::CSegKnotenTree (void) :
	 CTree (GetKnoten, StrCmp)
{
}

CSegKnotenTree::~CSegKnotenTree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT CSegKnotenTree::UserDelete (void *pObj) 
{
	((CSegKnoten *)pObj) -> CSegKnoten::~CSegKnoten();
}

// Zugriffsfunktionen auf Baumelemente 
void _XTENSN_EXPORT *GetKnoten (void *pObj) 
{
	return (void *) (((CSegKnoten *)pObj) -> KeyText());
}

//int _XTENSN_EXPORT CmpLayer (void *pObj1, void *pObj2) 
//{
//	return strcmp((char const *)pObj1, (char const *)pObj2);
//}
