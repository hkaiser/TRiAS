// Container, der die im weiteren zu ignorierenden RelationsCodes enthaelt
// File: RKIGNORE.CXX

#include "idntsdbp.hxx"

#include "rkignore.hxx"

// Konstruktor/Destruktor -----------------------------------------------------
RCodeIgnoreList :: RCodeIgnoreList (void)
		 : CTree (GetLongKey, CmpLongKey)
{
	// nothing else
}

RCodeIgnoreList :: ~RCodeIgnoreList (void)
{
	EveryDelete ();
}

void RCodeIgnoreList :: UserDelete (void *pObj)
{
#if defined(__GWXX__)
	((IgnoreRC *)pObj) -> IgnoreRC :: ~IgnoreRC();
#else
	((IgnoreRC *)pObj) -> ~IgnoreRC();
#endif
}

// sonstige Member ------------------------------------------------------------
bool RCodeIgnoreList :: Add (long lRCode)
{
IgnoreRCCreator IRCr (*this);

	return ContCreate (IRCr, IgnoreRC)(lRCode) != NULL;
}

bool RCodeIgnoreList :: Find (long lRCode)
{
CTable t (*this);

	return t.Find (&lRCode);
}



