// Verwalten der Registry-Keys
// File: relkey.cpp

#include "bnaimpp.hpp"

#include "bnapars.h"
#include "relkey.hxx"

#pragma warning(disable: 4273)
int __cdecl lstrcmp (void *p1, void *p2)
{
	return strcmp((char *)p1, (char *)p2); 
}

///////////////////////////////////////////////////////////////////////////////
// Member für Klasse TR_OBJ 
TR_OBJ::TR_OBJ (char const *pKurzText, short iTyp) :
	m_strKurzText(pKurzText), _iTyp(iTyp)
{
}

TR_OBJ::~TR_OBJ (void) 
{
}

///////////////////////////////////////////////////////////////////////////////
// Memberfunktionen für TR_OCLTree 
TR_OBJTree::TR_OBJTree (void) 
	 : CTree (GetKText, CmpKTexts)
{
}

TR_OBJTree::~TR_OBJTree (void) 
{
	EveryDelete();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT TR_OBJTree::UserDelete (void *pObj) 
{
	((TR_OBJ *)pObj) -> TR_OBJ::~TR_OBJ();
}

// Zugriffsfunktionen auf Baumelemente 
void _XTENSN_EXPORT *GetKText (void *pObj) 
{
	return const_cast<char *>((((TR_OBJ *)pObj) -> KurzText()));
}

int _XTENSN_EXPORT CmpKTexts (void *pObj1, void *pObj2) 
{
	return lstrcmp(pObj1, pObj2);
}

////////////////////////////////////////////////////////////////////////////
// Member für Klasse TR_OKS 
TR_OKS::TR_OKS (const char *pKey, const char *pWert) :
	m_strKey(pKey), m_strWert(pWert)
{
}

TR_OKS::~TR_OKS (void) 
{
}

//----------------------------------------------------------------
bool TR_OKS::SetWert (const char *pWert) 
{
	if (NULL == pWert)
		return false;

	m_strWert = pWert;
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Memberfunktionen für TR_OKSTree 
TR_OKSTree::TR_OKSTree (void) 
	 : CTree (GetOKS, StrCmp)
{
}

TR_OKSTree::~TR_OKSTree (void) 
{
	EveryDelete();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT TR_OKSTree::UserDelete (void *pObj) 
{
	((TR_OKS *)pObj) -> TR_OKS::~TR_OKS();
}

// Zugriffsfunktionen auf Baumelemente 
void _XTENSN_EXPORT *GetOKS (void *pObj) 
{
	return (void *)(((TR_OKS *)pObj) -> Key());
}

//int _XTENSN_EXPORT CmpOKSs (void *pObj1, void *pObj2) 
//{
//	return strcmp((char const *)pObj1, (char const *)pObj2);
//}

///////////////////////////////////////////////////////////////////////////////
// Member für Klasse TR_Layer
TR_Layer::TR_Layer (const char *pBNAText, long lIdent, DWORD dwObjType,
		bool fImportAttributes) :
	m_strBNAText(pBNAText), m_dwObjType(dwObjType)
{
//	_iAbgleich = false;
	memset(&_lIdent, '\0', sizeof(_lIdent));
	memset(&m_fImportAttributes, '\0', sizeof(m_fImportAttributes));

	if (0L != lIdent) {
//	HPROJECT hPr = DEX_GetObjectsProject(lIdent);
//	char cbOKS[MAX_OKS_LENX];
//
//		ClassFromIdentX (lIdent, cbOKS);
//		m_strOKS = cbOKS;

	int iIndex = OTypToIndex(dwObjType);

		m_strKurzText[iIndex] = pBNAText;
		_lIdent[iIndex] = lIdent;
//		_iAbgleich = true;
	}
}

TR_Layer::~TR_Layer (void) 
{
}

void TR_Layer::AddType (ULONG lIdent, DWORD dwType) 
{ 
	m_dwObjType |= (dwType & OTAll); 

	if (0L != lIdent) {
	int iIndex = OTypToIndex(dwType);

		m_strKurzText[iIndex] = m_strBNAText;
		_lIdent[iIndex] = lIdent;
	}
//	_iAbgleich = true;
}

/*static*/
int TR_Layer::OTypToIndex(DWORD dwObjType)
{
	switch (dwObjType) {
	case OTPunkt:
		return 0;

	case OTLinie:
		return 1;

	case OTFlaeche:
		return 2;

	case OTText:
		return 3;
	}

// es muß genau ein Objekttyp gegeben sein
	_ASSERTE(FALSE);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////
//
int TR_Layer::SetKurzText (DWORD dwType, const char *pKurzText, HPROJECT hPr) 
{
	if (NULL == pKurzText || '\0' == *pKurzText)
		return false;

// KK020725
//	ULONG lIdent = ClassIsDefined(pKurzText);
	ULONG lIdent = ClassIsDefined(pKurzText, hPr);

	if (0 == lIdent)
		return false;		// Objektklasse muß existieren

int iIndex = OTypToIndex(dwType);

	_ASSERTE(dwType & m_dwObjType);

	m_strKurzText[iIndex] = pKurzText;
	_lIdent[iIndex] = lIdent;
	m_fImportAttributes[iIndex] = true;
	return true;
}

bool TR_Layer::GetImportAttributes(DWORD dwType)
{
	return m_fImportAttributes[OTypToIndex(dwType)];
}

void TR_Layer::SetImportAttributes(bool fImportAttributes, DWORD dwType)
{
	m_fImportAttributes[OTypToIndex(dwType)] = fImportAttributes;
}

/////////////////////////////////////////////////////////////////////////////////
//int TR_Layer::SetOKS (const char *pOKS) 
//{
//	if (NULL == pOKS || '\0' == *pOKS)
//		return false;
//
//	m_strOKS = pOKS;
//	return true;
//}
//
/////////////////////////////////////////////////////////////////////////////////
//int TR_Layer::SetIdent (long lIdent) 
//{
//	if (0L == lIdent)
//		return false;
//
//HPROJECT hPr = DEX_GetObjectsProject(lIdent);
//char cbOKS[MAX_OKS_LENX];
//
//	ClassFromIdentX (lIdent, cbOKS);
//	m_strOKS = cbOKS;
//
//	_lIdent = lIdent;
//	_iAbgleich = true;
//	return true;
//}

///////////////////////////////////////////////////////////////////////////////
// Memberfunktionen für TR_LayerTree 
TR_LayerTree::TR_LayerTree (void) :
	 CTree (GetLayer, StrCmp)
{
}

TR_LayerTree::~TR_LayerTree (void) 
{
	EveryDelete ();	// alle Elemente des Baumes freigeben
}

void _XTENSN_EXPORT TR_LayerTree::UserDelete (void *pObj) 
{
	((TR_Layer *)pObj) -> TR_Layer::~TR_Layer();
}

// Zugriffsfunktionen auf Baumelemente 
void _XTENSN_EXPORT *GetLayer (void *pObj) 
{
	return (void *) (((TR_Layer *)pObj) -> BNAText());
}

//int _XTENSN_EXPORT CmpLayer (void *pObj1, void *pObj2) 
//{
//	return strcmp((char const *)pObj1, (char const *)pObj2);
//}
