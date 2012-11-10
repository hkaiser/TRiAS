// Container, der die im weiteren zu ignorierenden Identifikatoren enthaelt
// File: IDIGNORE.CXX

#include "idntsdbp.hxx"
#include "idignore.hxx"

// Konstruktor/Destruktor -----------------------------------------------------
IdIgnoreList :: IdIgnoreList (void)
	      : CTree (GetLongKey, CmpLongKey)
{
	// nothing else
}

IdIgnoreList :: ~IdIgnoreList (void)
{
	EveryDelete ();
}

void IdIgnoreList :: UserDelete (void *pObj)
{
#if defined(__GWXX__)
	((IgnoreId *)pObj) -> IgnoreId :: ~IgnoreId();
#else
	((IgnoreId *)pObj) -> ~IgnoreId();
#endif
}

// sonstige Member ------------------------------------------------------------
bool IdIgnoreList :: Add (long Ident)
{
IgnoreIdCreator IICr (*this);

	return ContCreate (IICr, IgnoreId)(Ident) != NULL;
}

bool IdIgnoreList :: Find (long Ident)
{
CTable t (*this);

	return t.Find (&Ident);
}



void * _XTENSN_EXPORT GetLongKey (void *pObj)
{
	return pObj;
}

int _XTENSN_EXPORT CmpLongKey (void *pObj1, void *pObj2)
{
long lKey1 = *(long *)pObj1;
long lKey2 = *(long *)pObj2;

	if (lKey1 > lKey2) return 1;
	if (lKey1 < lKey2) return -1;
	return 0;
}

