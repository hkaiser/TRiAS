// Methoden für Klassen ObjNrKnoten und ObjNrBaum
// File: NUMTREE.CXX
// W. Mörtl


#include "abstandp.hxx"

#include "numtree.hxx"


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
void* _ABSTAND_EXPORT ObjNrGetKey (void* pObj)
{
	return pObj;
}


// ---------------------------------------------------------------------------------------------------
// ObjNrKnoten werden in ObjNrBaum nach aufsteigenden Objektnummern sortiert;
// Die beiden Pointer-Parameter werden durch ObjNrGetKey erzeugt, der erste zeigt auf den mittels
// Create neu einzufügenden Knoten, der zweite auf die schon im Baum vorhandenen Knoten, beginnend
// bei der Wurzel
int _ABSTAND_EXPORT ObjNrCompare (void* pKey1, void* pKey2)
{
	_ASSERTE (NULL != pKey1);
	_ASSERTE (NULL != pKey2);

ObjNrKnoten* pK1 = (ObjNrKnoten*) pKey1;
ObjNrKnoten* pK2 = (ObjNrKnoten*) pKey2;
long lONr1 = pK1 -> GetONr();
long lONr2 = pK2 -> GetONr();

	_ASSERTE (lONr1 != 0);
	_ASSERTE (lONr1 != -1);
	_ASSERTE (lONr2 != 0);
	_ASSERTE (lONr2 != -1);

	if (lONr1 < lONr2) return -1;	// Vergleich zweier Objektnummern
	if (lONr1 > lONr2) return 1;

	return 0;			// zwei gleiche Objektnummern können bei Find() auftreten
} // ObjNrCompare





// ===================================================================================================
// Methoden für Klasse ObjNrBaum
// ---------------------------------------------------------------------------------------------------
// Ruf eines korrekten Destruktors, wenn ein Objekt freigegeben werden soll
void _ABSTAND_EXPORT ObjNrBaum :: UserDelete (void* pObj)
{
	_ASSERTE (NULL != pObj);

	((ObjNrKnoten*)pObj) -> ~ObjNrKnoten();
} // ObjNrBaum


// ---------------------------------------------------------------------------------------------------
// Knoten in ObjNrBaum einfügen
bool ObjNrBaum :: InsertK (long lONr)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

ObjNrKnotenOptCreator KC (*this);

	// Makro zum Eintragen eines ObjNrKnoten in Baumklasse KC
	if (ContCreate (KC, ObjNrKnoten) (lONr))
		return true;
	else
	{
		DEX_Error (RC_NumTree, EC_NOMEMORY);
		return false;
	}
} // InsertK


// ---------------------------------------------------------------------------------------------------
// Objektnummer lONr ist Element des ObjNrBaumes (true), sonst false
bool ObjNrBaum :: MemberK (long lONr)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

CTable tab (*this);

	if (tab.Find (&lONr))
	{
	ObjNrKnotenLock kl (tab);

		if (kl)
			return true;
		else
			DEX_Error (RC_NumTree, EC_SYSERROR);
	}
	return false;
} // MemberK


// ---------------------------------------------------------------------------------------------------
// Objektnummer lONr in ObjNrBaumes löschen
bool ObjNrBaum :: DeleteK (long lONr)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

bool toDelete = false;
CTable tab (*this);

	if (tab.Find (&lONr))
	{
	ObjNrKnotenLock kl (tab);

		if (kl)
			toDelete = true;
		else
    		DEX_Error (RC_NumTree, EC_SYSERROR);
	}

	if (toDelete)
	{
		tab.Delete();
		return true;	// Objektnummer gelöscht
	}
	return false;		// Objektnummer nicht gefunden und damit nicht gelöscht
} // DeleteK
