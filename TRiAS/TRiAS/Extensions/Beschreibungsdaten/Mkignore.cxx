// Container, der die im weiteren zu ignorierenden MerkmalsCodes enthaelt
// File: MKIGNORE.CXX

#include "idntsdbp.hxx"

#include "mkignore.hxx"

// Konstruktor/Destruktor -----------------------------------------------------
MCodeIgnoreList :: MCodeIgnoreList (void)
	         : CTree (GetLongKey, CmpLongKey)
{
	// nothing else
}

MCodeIgnoreList :: ~MCodeIgnoreList (void)
{
	EveryDelete ();
}

void MCodeIgnoreList :: UserDelete (void *pObj)
{
#if defined(__GWXX__)
	((IgnoreMCode *)pObj) -> IgnoreMCode :: ~IgnoreMCode();
#else
	((IgnoreMCode *)pObj) -> ~IgnoreMCode();
#endif
}

// sonstige Member ------------------------------------------------------------
bool MCodeIgnoreList :: Add (long MCode)
{
IgnoreMCodeCreator IMCr (*this);

	return ContCreate (IMCr, IgnoreMCode)(MCode) != NULL;
}

bool MCodeIgnoreList :: Find (long MCode)
{
CTable t (*this);

	return t.Find (&MCode);
}



