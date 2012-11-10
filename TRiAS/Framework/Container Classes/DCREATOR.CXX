// Datenstrukturen mit 2 Containern -- Memberfunktionen
// File: DCREATOR.CXX

#include "contpre.hxx"
#include <dcreator.hxx>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if defined(_DEBUG) && defined(WIN32)
void CDCreator :: AssertValid (void) const
{
	CLock::AssertValid();
}
#endif

// Konstruktor
_DLLENTRY CDCreator :: CDCreator (CContainer &c1, CContainer &c2) 
#if !defined(WIN32)
		     : CLock (c1.GetFreeStore (), 0), 
#else
		     : CLock (0),
#endif
	    cont1 (c1), cont2 (c2) 
{
	TX_ASSERT(&c1 != &c2);		// nicht die gleichen Container
}

// Destruktor
_DLLENTRY CDCreator :: ~CDCreator (void) 
{
CContainer :: CSyncThread Sync (&cont1);

// noch offenes Element in Container einfügen
	if (GetHandle()) {
		if (cont1.Insert (GetHandle(), P()))		
		// nur einfügen, wenn eindeutig (cont1) ist UniqueTree
			cont2.Insert (GetHandle(), P());
	}
}

void * _DLLENTRY CDCreator :: Alloc (size_t size) 
{
	TX_ASSERT_VALID_CONT(this);

CContainer :: CSyncThread Sync (&cont1);

// evtl. noch offenes Element in Container einspeichern
	if (GetHandle()) Insert();

// nächstes Element anlegen
#if !defined(WIN32)
	if (GetFreeStore ())
	// in bestimmten Freestore einspeichern
		GetHandle() = GetFreeStore() -> Alloc (size);
	else
#endif
	// in aktuellem Freestore einspeichern
		GetHandle() = (FSHandle) new char [size];

// Element im Speicher festlegen
	lock();

return P();	// Zeiger auf Element liefern
}

#if _MSC_VER >= 1200
void _DLLENTRY CDCreator :: Free (void *pMem) 
{
	TX_ASSERT_VALID_CONT(this);
	if (NULL != pMem)
		delete [] pMem;
}
#endif // _MSC_VER >= 1200

BOOL _DLLENTRY CDCreator :: Insert (void) 
{
	TX_ASSERT_VALID_CONT(this);

CContainer :: CSyncThread Sync (&cont1);
BOOL iCmp;

	if (iCmp = cont1.Insert (GetHandle(), P())) {
	// nur einspeichern, wenn eindeutiger Schlüssel und kein Fehler
	BOOL iCmp2 = cont2.Insert (GetHandle(), P());

		if (iCmp != iCmp2) iCmp = iCmp2;
	}

	Unlock();				// Lock aufheben
	GetHandle() = 0;			// kein Element mehr 'offen'

return iCmp;
}


