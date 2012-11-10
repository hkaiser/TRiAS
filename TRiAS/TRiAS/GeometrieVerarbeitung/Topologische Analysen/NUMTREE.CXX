// Methoden für Klassen ObjNrKnoten und ObjNrBaum
// File: NumTree.cxx
// W. Mörtl


#include "TopoRelP.hxx"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif




// ===================================================================================================
// Methoden für Klasse ObjNrKnoten
// ---------------------------------------------------------------------------------------------------
// friend-Funktionen
// bekommt als Parameter den Pointer auf ein im Baum "ObjNrBaum" hängendes Objekt und muß
// Pointer auf Schlüssel liefern
void* _TOPOREL_EXPORT ObjNrGetKey (void* pObj)
{
	return &((ObjNrKnoten*)pObj)->m_lONr;
}

// ---------------------------------------------------------------------------------------------------
// ObjNrKnoten werden in ObjNrBaum nach aufsteigenden Objektnummern sortiert;
// Die beiden Pointer-Parameter werden durch ObjNrGetKey erzeugt, der erste zeigt auf den mittels
// Create neu einzufügenden Knoten, der zweite auf die schon im Baum vorhandenen Knoten, beginnend
// bei der Wurzel
int ObjNrCompare(long lONr1, long lONr2)
{
	_ASSERTE (0 != lONr1);
	_ASSERTE (-1 != lONr1);
	_ASSERTE (0 != lONr2);
	_ASSERTE (-1 != lONr2);

	if (lONr1 < lONr2) return -1;	// Vergleich zweier Objektnummern
	if (lONr1 > lONr2) return 1;

	return 0;	// zwei gleiche Objektnummern können bei Find() auftreten
}




// ===================================================================================================
// Methoden für Klasse ObjNrBaum
// ---------------------------------------------------------------------------------------------------
// Ruf eines korrekten Destruktors, wenn ein Objekt freigegeben werden soll
void _TOPOREL_EXPORT ObjNrBaum :: UserDelete (void* pObj)
{
	_ASSERTE (NULL != pObj);

	delete (ObjNrKnoten*)pObj;
} // ObjNrBaum


// ---------------------------------------------------------------------------------------------------
// Knoten in ObjNrBaum einfügen, wenn die Objektnummer noch nicht vorhanden ist, sonst den
// Häufigkeitszähler inkrementieren
//  lRefObjCount: Anzahl der Referenzobjekte
bool ObjNrBaum :: InsertK (long lONr, long lRefObjCount)
{
	_ASSERTE (0 != lONr);
	_ASSERTE (-1 != lONr);

ObjNrBaumTable tab (*this);

	if (1 == lRefObjCount)	// es gibt nur EIN Referenzobjekt
	{
	ObjNrKnotenCreator KC (*this);

		// Makro zum Eintragen eines ObjNrKnoten in Baumklasse KC
		if (0 != KC.InsertPtr(new ObjNrKnoten(lONr)))
			return true;

		DEX_Error (RC_NumTree, EC_NOMEMORY);
	}

	else					// es gibt mehrere Referenzobjekte
	{
		if (tab.Find (&lONr))
		{
		ObjNrKnotenLock kl (tab);

			if (kl)
			{
				kl->IncCounter();
				return true;
			}

			DEX_Error (RC_NumTree, EC_SYSERROR);
		}

		else
		{
		ObjNrKnotenCreator KC (*this);

			if (0 != KC.InsertPtr(new ObjNrKnoten(lONr)))
				return true;

			DEX_Error (RC_NumTree, EC_NOMEMORY);
		}
	}

	return false;

} // InsertK


// ---------------------------------------------------------------------------------------------------
// Objektnummer lONr ist schon Element des ObjNrBaumes (true), sonst false
bool ObjNrBaum :: MemberK (long lONr)
{
	_ASSERTE (0 != lONr);
	_ASSERTE (-1 != lONr);

ObjNrBaumTable tab (*this);

	if (tab.Find (&lONr))
	{
	ObjNrKnotenLock kl (tab);

		if (kl)
			return true;

		DEX_Error (RC_MemberKTopo, EC_SYSERROR);
	}
	return false;

} // MemberK


// ---------------------------------------------------------------------------------------------------
// liefert Häufigkeitszähler von Objektnummer lONr
long ObjNrBaum :: GetCounter (long lONr)
{
	_ASSERTE (0 != lONr);
	_ASSERTE (-1 != lONr);

ObjNrBaumTable tab (*this);

	if (tab.Find (&lONr))
	{
	ObjNrKnotenLock kl (tab);

		if (kl)
			return kl->GetCounter();

		DEX_Error (RC_NumTree, EC_SYSERROR);
	}

	DEX_Error (RC_NumTree, EC_NOON);
	return -1;

} // GetCounter
